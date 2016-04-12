#include "MD5.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <gl/GL.H>
#include <gl/GLU.H>
#include <gl/GLAUX.H>


extern Vec3_t *vertexArray;
extern GLuint *vertexIndices;


static void BuildFrameSkeleton(const Joint_Info_t *jointInfos,      // ����hierarchy��Ϣ
                               const BaseFrame_Joint_t *baseFrame,  // �������
                               const float *animFrameData,          // �����������
                               MD5_Joint_t *skelFrame,              // �������
                               int num_joints)                      // ��������
{
    for ( int i = 0; i < num_joints; i++ )
    {
        const BaseFrame_Joint_t *baseJoint = &baseFrame[i];
        Vec3_t animatedPos;
        Quat4_t animatedOrient;
        int j = 0;

        memcpy(animatedPos, baseJoint->pos, sizeof(Vec3_t));
        memcpy(animatedOrient, baseJoint->orient, sizeof(Quat4_t));

        if ( jointInfos[i].flags & 1 )      // Tx
        {
            animatedPos[X] = animFrameData[jointInfos[i].startIndex + j];
            j++;
        }

        if ( jointInfos[i].flags & 2 )      // Ty
        {
            animatedPos[Y] = animFrameData[jointInfos[i].startIndex + j];
            j++;
        }

        if ( jointInfos[i].flags & 4 )      // Tz
        {
            animatedPos[Z] = animFrameData[jointInfos[i].startIndex + j];
            j++;
        }

        if ( jointInfos[i].flags & 8 )      // Qx
        {
            animatedOrient[X] = animFrameData[jointInfos[i].startIndex + j];
            j++;
        }

        if ( jointInfos[i].flags & 16 )     // Qy
        {
            animatedOrient[Y] = animFrameData[jointInfos[i].startIndex + j];
            j++;
        }

        if ( jointInfos[i].flags & 32 )     // Qz
        {
            animatedOrient[Z] = animFrameData[jointInfos[i].startIndex + j];
            j++;
        }

        Quat_computeW(animatedOrient);

        MD5_Joint_t *thisJoint = &skelFrame[i];

        // ��herarchy�еĹ����ĸ��ڵ�����������ǰ��������ܡ���parent��Ա
        int parent = jointInfos[i].parent;
        thisJoint->parent = parent;

        // �������������ֵ���ǰ��������ܡ���
        strcpy(thisJoint->name, jointInfos[i].name);

        if ( thisJoint->parent < 0 )
        {
            memcpy(thisJoint->pos, animatedPos, sizeof(Vec3_t));
            memcpy(thisJoint->orient, animatedOrient, sizeof(Quat4_t));
        }
        else
        {
            MD5_Joint_t *parentJoint = &skelFrame[parent];
            Vec3_t rPos;    // rotated position

            // add positions
            Quat_rotatePoint(parentJoint->orient, animatedPos, rPos);
            thisJoint->pos[X] = rPos[X] + parentJoint->pos[X];
            thisJoint->pos[Y] = rPos[Y] + parentJoint->pos[Y];
            thisJoint->pos[Z] = rPos[Z] + parentJoint->pos[Z];

            // concatenate rotations
            Quat_multQuat(parentJoint->orient, animatedOrient, thisJoint->orient);
            Quat_normalize(thisJoint->orient);
        }
    }
}

int ReadAnim(const char *fileName, MD5_Anim_t *anim)
{
    FILE                *fp             = NULL;
    char                buff[512];
    Joint_Info_t        *jointInfos     = NULL;
    BaseFrame_Joint_t   *baseFrame      = NULL;
    float               *animFrameData  = NULL; // ��ʱ���Frame n ���ݿ��е���Ϣ

    // ��ʱ���
    int version;
    int numAnimatedConponents;  // �����������������
    int frame_index;
    
    fp = fopen(fileName, "rb");
    if ( !fp )
    {
        fprintf(stderr, "error: couldn't open \"%s\"!\n", fileName);
        return FALSE;
    }

    while ( !feof(fp) )
    {
        // read whole line
        fgets(buff, sizeof(buff), fp);
        if ( 1 == sscanf(buff, " MD5Version %d", &version) )
        {
            if ( 10 != version )
            {
                // bad version
                fclose(fp);
                return FALSE;
            }
        }
        // ��ȡ���������������洢����������Χ����Ϣ�Ŀռ�
        else if ( 1 == sscanf(buff, " numFrames %d", &anim->num_frames) )
        {
            if ( anim->num_frames > 0 )
            {
                anim->skelFrames = (MD5_Joint_t **)malloc(sizeof(MD5_Joint_t *) * anim->num_frames);
                anim->bboxes = (MD5_BBox_t *)malloc(sizeof(MD5_BBox_t) * anim->num_frames);
            }
        }
        // ��ȡ�������������������������д�Ź�����Ϣ�Ŀռ�
        else if ( 1 == sscanf(buff, " numJoints %d", &anim->num_joints) )
        {
            if ( anim->num_joints > 0 )
            {
                for ( int i = 0; i < anim->num_frames; i++ )
                {
                    // ����ռ�
                    anim->skelFrames[i] = (MD5_Joint_t *)malloc(sizeof(MD5_Joint_t) * anim->num_joints);
                }
                // ��ʱ���hierarchy����Ϣ����Щ��Ϣ�ڹ�����ܽ���������Ҫ
                jointInfos = (Joint_Info_t *)malloc(sizeof(Joint_Info_t) * anim->num_joints);
                // ����������ܵ���Ϣ
                baseFrame = (BaseFrame_Joint_t *)malloc(sizeof(BaseFrame_Joint_t) * anim->num_joints);
            }
        }
        // ��ȡ��ܵ�֡�ٶ�
        else if ( 1 == sscanf(buff, " frameRate %d", &anim->frameRate) )
        {
            // ...
        }
        // ��ȡ�����������������������洢�ռ�
        else if ( 1 == sscanf(buff, " numAnimatedComponents %d", &numAnimatedConponents) )
        {
            if ( numAnimatedConponents > 0 )
            {
                animFrameData = (float *)malloc(sizeof(float) * numAnimatedConponents);
            }
        }
        // ��ȡhierarchy���ݿ��е���Ϣ
        else if ( 0 == strncmp(buff, "hierarchy {", 11) )
        {
            for ( int i = 0; i < anim->num_joints; i++ )
            {
                // read whole line
                fgets(buff, sizeof(buff), fp);
                // read joint info
                sscanf(buff, "%s %d %d %d",
                       jointInfos[i].name,
                       &jointInfos[i].parent,
                       &jointInfos[i].flags,
                       &jointInfos[i].startIndex);
            }
        }
        else if ( 0 == strncmp(buff, "bounds {", 8) )
        {
            for ( int i = 0; i < anim->num_frames; i++ )
            {
                // read whole line
                fgets(buff, sizeof(buff), fp);
                // read bounding box
                sscanf(buff, " ( %f %f %f ) ( %f %f %f )",
                       &anim->bboxes[i].min[X], &anim->bboxes[i].min[Y], &anim->bboxes[i].min[Z],
                       &anim->bboxes[i].max[X], &anim->bboxes[i].max[Y], &anim->bboxes[i].max[Z]);
            }
        }
        // ��ȡ����������ݿ������
        else if ( 0 == strncmp(buff, "baseframe {", 10) )
        {
            for ( int i = 0; i < anim->num_joints; i++ )
            {
                // read whole line
                fgets(buff, sizeof(buff), fp);
                // read base frame joint
                if ( 6 == sscanf(buff, " (%f %f %f ) ( %f %f %f )",
                                    &baseFrame[i].pos[X], &baseFrame[i].pos[Y], &baseFrame[i].pos[Z],
                                    &baseFrame[i].orient[X], &baseFrame[i].orient[Y], &baseFrame[i].orient[Z]) )
                {
                    // compute the w component
                    Quat_computeW(baseFrame[i].orient);
                }
            }
        }
        // ��ȡ����������ݿ��е���Ϣ������ÿһ������֡�Ĺ���������������֮�����ϵ
        else if ( 1 == sscanf(buff, " frame %d", &frame_index) )
        {
            // read frame data
            for ( int i = 0; i < numAnimatedConponents; i++ )
            {
                fscanf(fp, "%f", &animFrameData[i]);
            }
            // build frame skeleton from the collected data
            BuildFrameSkeleton(jointInfos, baseFrame, animFrameData,
                               anim->skelFrames[frame_index], anim->num_joints);
        }
    }

    fclose(fp);

    // free temporary allocated data
    if ( animFrameData )
    {
        free(animFrameData);
    }

    if ( baseFrame )
    {
        free(baseFrame);
    }

    if ( jointInfos )
    {
        free(jointInfos);
    }

    return TRUE;
}

void DrawAnim(MD5_Model_t *mdl, MD5_Anim_t *anim, int skelFrames_index)
{
    glColor3f(1.0f, 1.0f, 1.0f);

    int vertex_index;
    for ( int i = 0; i < mdl->num_meshes; i++ )
    {
        PremareMesh(&mdl->meshes[i], anim->skelFrames[skelFrames_index]);

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

void FreeAnim(MD5_Anim_t *anim)
{
    if ( anim->skelFrames )
    {
        for ( int i = 0; i < anim->num_frames; i++ )
        {
            if ( anim->skelFrames[i] )
            {
                free(anim->skelFrames[i]);
                anim->skelFrames[i] = NULL;
            }
        }

        free(anim->skelFrames);
        anim->skelFrames = NULL;
    }

    if ( anim->bboxes )
    {
        free(anim->bboxes);
        anim->bboxes = NULL;
    }
}
