#include "MD5.h"

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <gl/GL.H>
#include <gl/GLU.H>
#include <gl/GLAUX.H>


// vertex array related suff
int max_verts = 0;
int max_tris = 0;

Vec3_t *vertexArray = NULL;
GLuint *vertexIndices = NULL;


// ������Ԫ����W
void Quat_computeW(Quat4_t q)
{
    float t = 1.0f - (q[X] * q[X]) - (q[Y] * q[Y]) - (q[Z] * q[Z]);

    if (t < 0.0f)
    {
        q[W] = 0.0f;
    }
    else
    {
        q[W] = -sqrt(t);
    }
}

// ��Ԫ����׼��
void Quat_normalize(Quat4_t q)
{
    float mag = sqrt((q[X] * q[X]) + (q[Y] * q[Y]) + (q[Z] * q[Z]) + (q[W] * q[W]));

    if ( mag > 0.0f )
    {
        float oneOverMag = 1.0f / mag;

        q[W] *= oneOverMag;
        q[X] *= oneOverMag;
        q[Y] *= oneOverMag;
        q[Z] *= oneOverMag;
    }
}

// ��Ԫ���˷�
void Quat_multQuat(const Quat4_t q1, const Quat4_t q2, Quat4_t out)
{
    out[W] = (q1[W] * q2[W]) - (q1[X] * q2[X]) - (q1[Y] * q2[Y]) - (q1[Z] * q2[Z]);
    out[X] = (q1[X] * q2[W]) + (q1[W] * q2[X]) + (q1[Y] * q2[Z]) - (q1[Z] * q2[Y]);
    out[Y] = (q1[Y] * q2[W]) + (q1[W] * q2[Y]) + (q1[Z] * q2[X]) - (q1[X] * q2[Z]);
    out[Z] = (q1[Z] * q2[W]) + (q1[W] * q2[Z]) + (q1[X] * q2[Y]) - (q1[Y] * q2[X]);
}

void Quat_multVec(const Quat4_t q, const Vec3_t v, Quat4_t out)
{
    out[W] = -(q[X] * v[X]) - (q[Y] * v[Y]) - (q[Z] * v[Z]);
    out[X] =  (q[W] * v[X]) + (q[Y] * v[Z]) - (q[Z] * v[Y]);
    out[Y] =  (q[W] * v[Y]) + (q[Z] * v[X]) - (q[X] * v[Z]);
    out[Z] =  (q[W] * v[Z]) + (q[X] * v[Y]) - (q[Y] * v[X]);
}

// ��������Ԫ����ת
void Quat_rotatePoint(const Quat4_t q, const Vec3_t in, Vec3_t out)
{
    Quat4_t tmp, inv, final;

    inv[X] = -q[X];
    inv[Y] = -q[Y];
    inv[Z] = -q[Z];
    inv[W] =  q[W];

    Quat_normalize(inv);

    Quat_multVec(q, in, tmp);
    Quat_multQuat(tmp, inv, final);

    out[X] = final[X];
    out[Y] = final[Y];
    out[Z] = final[Z];
}


int ReadModel(const char *fileName, MD5_Model_t *mdl)
{
    FILE *fp;
    char buff[512];
    int version;
    int curr_mesh = 0;

    fp = fopen(fileName, "rb");
    if ( !fp )
    {
        fprintf(stderr, "error:couldn't open \"%s\"!\n", fileName);
        return 0;
    }

    while ( !feof(fp) )
    {
        fgets(buff, sizeof(buff), fp);
        // ���Ұ汾��
        if ( 1 == sscanf(buff, "MD5Version %d", &version) )
        {
            if ( 10 != version )
            {
                fclose(fp);
                return 0;
            }
        }
        // ��ȡJoints������Ϊ�����ռ�ͬʱ����
        else if ( 1 == sscanf(buff, "numJoints %d", &mdl->num_joints) )
        {
            if ( mdl->num_joints > 0 )
            {
                mdl->baseSkel = (MD5_Joint_t *)malloc(sizeof(MD5_Joint_t) * mdl->num_joints);
                memset(mdl->baseSkel, 0, sizeof(MD5_Joint_t) * mdl->num_joints);
            }
        }
        // ��ȡnumMeshes������Ϊ�����ռ�ͬʱ����
        else if ( 1 == sscanf(buff, "numMeshes %s", &mdl->num_meshes) )
        {
            if ( mdl->num_meshes > 0 )
            {
                mdl->meshes = (MD5_Mesh_t *)malloc(sizeof(MD5_Mesh_t) * mdl->num_meshes);
                memset(mdl->meshes, 0, sizeof(MD5_Mesh_t) * mdl->num_meshes);
            }
        }
        // ��ȡÿһ��joints����Ϣ
        else if ( 0 == strncmp(buff, "joints {", 8) )
        {
            for ( int i = 0; i < mdl->num_joints; i++ )
            {
                MD5_Joint_t *joint = &mdl->baseSkel[i];
                fgets(buff, sizeof(buff), fp);
                if ( 8 == sscanf(buff, "%s %d ( %f %f %f ) ( %f %f %f )",
                    joint->name, &joint->parent,
                    &joint->pos[X], &joint->pos[Y], &joint->pos[Z],
                    &joint->orient[X], &joint->orient[Y], &joint->orient[Z]) )
                {
                    Quat_computeW(joint->orient);
                }
            }
        }
        // ��ȡmesh�е���Ϣ�����ж��mesh��Ϣ�洢��mdl->meshes[]��
        // ������ÿһ��Ԫ����һ��mesh��������Ϣ
        else if ( 0 == strncmp(buff, "mesh {", 6) ) // �ж�mesh���ݿ�Ŀ�ʼ��
        {
            MD5_Mesh_t  *mesh           = &mdl->meshes[curr_mesh];
            int         vert_index      = 0;
            int         tri_index       = 0;
            int         weight_index    = 0;
            float       fdata[4];
            int         idata[3];

            // ��ȡ����洢·���ַ���
            // �ж��Ƿ񵽴�'}'��mesh���ݿ����
            while ( (buff[0] != '}') && !feof(fp) )
            {
                fgets(buff, sizeof(buff), fp);
                if ( strstr(buff, "shader ") )
                {
                    int quote = 0;
                    int j = 0;
                    // �ж��Ƿ��ҵ��������ţ�����Ǿͽ���forѭ��
                    for ( int i = 0; i < sizeof(buff) && (quote < 2); i++ )
                    {
                        if ( '\"' == buff[i] )
                        {
                            quote++;
                        }
                        // �������е��ַ�������mesh->shader[j]��
                        if ( (1 == quote) && '\"' != buff[i] )
                        {
                            mesh->shader[j] = buff[i];
                            j++;
                        }
                    }
                }
                // ��ȡ��������������洢�ռ�
                else if ( 1 == sscanf(buff, " numverts %d", &mesh->num_verts) )
                {
                    if ( mesh->num_verts > 0 )
                    {
                        mesh->vertices = (MD5_Vertex_t *)malloc(sizeof(MD5_Vertex_t) * mesh->num_verts);
                    }

                    if ( mesh->num_verts > max_verts )
                    {
                        max_verts = mesh->num_verts;
                    }
                }
                // ��ȡ���㵽�������Ĵ洢�ռ���
                else if ( 5 == sscanf(buff, " vert %d ( %f %f ) %d %d",
                    &vert_index,
                    &fdata[X], &fdata[Y],
                    &idata[X], &idata[Y]) )
                {
                    mesh->vertices[vert_index].st[X] = fdata[X];
                    mesh->vertices[vert_index].st[Y] = fdata[Y];
                    mesh->vertices[vert_index].start = idata[X];
                    mesh->vertices[vert_index].count = idata[Y];
                }
                // ��ȡ����������������洢�ռ�
                else if ( 1 == sscanf(buff, " numtris %d", &mesh->num_tris) )
                {
                    if ( mesh->num_tris > 0 )
                    {
                        mesh->triangles = (MD5_Triangle_t *)malloc(sizeof(MD5_Triangle_t) * mesh->num_tris);
                    }

                    if ( mesh->num_tris > max_tris )
                    {
                        max_tris = mesh->num_tris;
                    }
                }
                // ��ȡ��������Ϣ���������Ĵ洢�ռ��У�����Ϣ���������õ��Ķ����ڶ���洢�ռ��е��±�����
                else if ( 4 == sscanf(buff, " tri %d %d %d %d",
                    &tri_index,
                    &idata[X], &idata[Y], &idata[Z]) )
                {
                    mesh->triangles[tri_index].index[X] = idata[X];
                    mesh->triangles[tri_index].index[Y] = idata[Y];
                    mesh->triangles[tri_index].index[Z] = idata[Z];
                }
                else if ( 1 == sscanf(buff, " numweights %d", &mesh->num_weights) )
                {
                    if ( mesh->num_weights > 0 )
                    {
                        mesh->weights = (MD5_Weight_t *)malloc(sizeof(MD5_Weight_t) * mesh->num_weights);
                    }
                }
                else if ( 6 == sscanf(buff, " weight %d %d %f ( %f %f %f )",
                    &weight_index, &idata[X], &fdata[W],
                    &fdata[X], &fdata[Y], &fdata[Z]) )
                {
                    mesh->weights[weight_index].joint   = idata[X];
                    mesh->weights[weight_index].bias    = fdata[W];
                    mesh->weights[weight_index].pos[X]  = fdata[X];
                    mesh->weights[weight_index].pos[Y]  = fdata[Y];
                    mesh->weights[weight_index].pos[Z]  = fdata[Z];
                }
            }
            curr_mesh++;
        }
    }

    fclose(fp);

    return 1;
}

void DrawModel(const MD5_Model_t *mdl)
{
    glColor3f(1.0f, 1.0f, 1.0f);

    int vertex_index;

    for ( int i = 0; i < mdl->num_meshes; i++ )
    {
        PremareMesh(&mdl->meshes[i], mdl->baseSkel);

        for ( int j = 0; j < mdl->meshes[i].num_tris; j++ )
        {
            for ( int k = 0; k < 3; k++ )
            {
                vertex_index = mdl->meshes[i].triangles[j].index[k];
                glVertex3f(vertexArray[vertex_index][X], vertexArray[vertex_index][Y], vertexArray[vertex_index][Z]);
            }
        }
    }
}

void FreeModel(MD5_Model_t *mdl)
{
    if ( mdl->baseSkel )
    {
        free(mdl->baseSkel);
        mdl->baseSkel = NULL;
    }

    if ( mdl->meshes )
    {
        for ( int i = 0; i < mdl->num_meshes; i++ )
        {
            if ( mdl->meshes[i].vertices )
            {
                free(mdl->meshes[i].vertices);
                mdl->meshes[i].vertices = NULL;
            }

            if ( mdl->meshes[i].triangles )
            {
                free(mdl->meshes[i].triangles);
                mdl->meshes[i].triangles = NULL;
            }

            if ( mdl->meshes[i].weights )
            {
                free(mdl->meshes[i].weights);
                mdl->meshes[i].weights = NULL;
            }
        }

        free(mdl->meshes);
        mdl->meshes = NULL;
    }
}

// ƥ������
void PremareMesh(const MD5_Mesh_t *mesh, const MD5_Joint_t *joints)
{
    int i, j, k;

    // setup vertex indices
    for ( i = 0, k = 0; i < mesh->num_tris; i++ )
    {
        for ( j = 0; j < 3; j++, k++ )
        {
            vertexIndices[k] = mesh->triangles[i].index[j];
        }
    }

    // setup vertices
    for ( i = 0; i < mesh->num_verts; i++ )
    {
        Vec3_t finalVertex = {0.0f, 0.0f, 0.0f};

        // calculate final vertex to draw with weight
        for ( j = 0; j < mesh->vertices[i].count; j++ )
        {
            const MD5_Weight_t *weight = &mesh->weights[mesh->vertices[i].start + j];
            const MD5_Joint_t *joint = &joints[weight->joint];

            // calculate transformed vertex for this weight
            Vec3_t wv;
            Quat_rotatePoint(joint->orient, weight->pos, wv);

            // the sum of all weight->bias should be 1.0
            finalVertex[X] += (joint->pos[X] + wv[X]) * weight->bias;
            finalVertex[Y] += (joint->pos[Y] + wv[Y]) * weight->bias;
            finalVertex[Z] += (joint->pos[Z] + wv[Z]) * weight->bias;
        }

        vertexArray[i][X] = finalVertex[X];
        vertexArray[i][Y] = finalVertex[Y];
        vertexArray[i][Z] = finalVertex[Z];
    }
}

void AllocVertexArrays()
{
    vertexArray = (Vec3_t *)malloc(sizeof(Vec3_t) * max_verts);
    vertexIndices = (GLuint *)malloc(sizeof(GLuint) * max_tris * 3);
}

void FreeVertexArrays()
{
    if ( vertexArray )
    {
        free(vertexArray);
        vertexArray = NULL;
    }

    if ( vertexIndices )
    {
        free(vertexIndices);
        vertexIndices = NULL;
    }
}
