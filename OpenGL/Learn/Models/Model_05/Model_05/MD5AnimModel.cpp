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


static void BuildFrameSkeleton(const Joint_Info_t *jointInfos,      // 接收hierarchy信息
                               const BaseFrame_Joint_t *baseFrame,  // 基础框架
                               const float *animFrameData,          // 动画框架数据
                               MD5_Joint_t *skelFrame,              // 骨骼框架
                               int num_joints)                      // 骨骼数量
{
    for ( int i = 0; i < num_joints; i++ )
    {
        const BaseFrame_Joint_t *baseJoint = &baseFrame[i];
        Vec3_t animatedPos;
        Quat4_t animatedOrient;
        int j = 0;

        memcpy(animatedPos, baseJoint->pos, sizeof(Vec3_t));
        memcpy(animatedOrient, baseJoint->orient, sizeof(Quat4_t));

        if ( jointInfos[i].flags & 1 )
        {
            animatedPos[X] = animFrameData[jointInfos[i].startIndex + j];
            j++;
        }

        if ( jointInfos[i].flags & 2 )
        {
            animatedPos[Y] = animFrameData[jointInfos[i].startIndex + j];
            j++;
        }

        if ( jointInfos[i].flags & 4 )
        {
            animatedPos[Z] = animFrameData[jointInfos[i].startIndex + j];
            j++;
        }

        if ( jointInfos[i].flags & 8 )
        {
            animatedOrient[X] = animFrameData[jointInfos[i].startIndex + j];
            j++;
        }

        if ( jointInfos[i].flags & 16 )
        {
            animatedOrient[Y] = animFrameData[jointInfos[i].startIndex + j];
            j++;
        }

        if ( jointInfos[i].flags & 32 )
        {
            animatedOrient[Z] = animFrameData[jointInfos[i].startIndex + j];
            j++;
        }

        Quat_computeW(animatedOrient);

        MD5_Joint_t *thisJoint = &skelFrame[i];

        // 将herarchy中的骨骼的父节点索引赋给当前“骨骼框架”的parent成员
        int parent = jointInfos[i].parent;
        thisJoint->parent = parent;

        // 拷贝骨骼的名字到当前“骨骼框架”中
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
            thisJoint->pos[0] = rPos[X] + parentJoint->pos[X];
            thisJoint->pos[1] = rPos[Y] + parentJoint->pos[Y];
            thisJoint->pos[2] = rPos[Z] + parentJoint->pos[Z];

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
    float               *animFrameData  = NULL;

    // 临时存放
    int version;
    int numAnimatedConponents;  // 动画组件参数的数量
    int frame_index;
    
    fp = fopen(fileName, "rb");
    if ( !fp )
    {
        fprintf(stderr, "error: couldn't open \"%s\"!\n", fileName);
        return FALSE;
    }

    while ( !feof(fp) )
    {
        fgets(buff, sizeof(buff), fp);
        if ( 1 == sscanf(buff, " MD5Version %d", &version) )
        {
            if ( 10 != version )
            {
                fclose(fp);
                return FALSE;
            }
        }
        else if ( 1 == sscanf(buff, " numFrames %d", &anim->num_frames) )
        {
            if ( anim->num_frames > 0 )
            {
                anim->skelFrames = (MD5_Joint_t **)malloc(sizeof(MD5_Joint_t *) * anim->num_frames);
                anim->bboxes = (MD5_BBox_t *)malloc(sizeof(MD5_BBox_t) * anim->num_frames);
            }
        }
        else if ( 1 == sscanf(buff, " numJoints %d", &anim->num_joints) )
        {
            if ( anim->num_joints > 0 )
            {
                for ( int i = 0; i < anim->num_frames; i++ )
                {
                    anim->skelFrames[i] = (MD5_Joint_t *)malloc(sizeof(MD5_Joint_t) * anim->num_joints);
                }

                jointInfos = (Joint_Info_t *)malloc(sizeof(Joint_Info_t) * anim->num_joints);
                baseFrame = (BaseFrame_Joint_t *)malloc(sizeof(BaseFrame_Joint_t) * anim->num_joints);
            }
        }
        else if ( 1 == sscanf(buff, " frameRate %d", &anim->frameRate) )
        {
            // ...
        }
        else if ( 1 == sscanf(buff, " numAnimatedComponents %d", &numAnimatedConponents) )
        {
            if ( numAnimatedConponents > 0 )
            {
                animFrameData = (float *)malloc(sizeof(float) * numAnimatedConponents);
            }
        }
        else if ( 0 == strncmp(buff, "hierarchy {", 11) )
        {
            for ( int i = 0; i < anim->num_joints; i++ )
            {
                fgets(buff, sizeof(buff), fp);
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
                fgets(buff, sizeof(buff), fp);
                sscanf(buff, " ( %f %f %f ) ( %f %f %f )",
                       &anim->bboxes[i].min[X], &anim->bboxes[i].min[Y], &anim->bboxes[i].min[Z],
                       &anim->bboxes[i].max[X], &anim->bboxes[i].max[Y], &anim->bboxes[i].max[Z]);
            }
        }
        else if ( 0 == strncmp(buff, "baseframe {", 10) )
        {
            for ( int i = 0; i < anim->num_joints; i++ )
            {
                fgets(buff, sizeof(buff), fp);
                if ( 6 == sscanf(buff, " (%f %f %f ) ( %f %f %f )",
                                    &baseFrame[i].pos[X], &baseFrame[i].pos[Y], &baseFrame[i].pos[Z],
                                    &baseFrame[i].orient[X], &baseFrame[i].orient[Y], &baseFrame[i].orient[Z]) )
                {
                    Quat_computeW(baseFrame[i].orient);
                }
            }
        }
        else if ( 1 == sscanf(buff, " frame %d", &frame_index) )
        {
            for ( int i = 0; i < numAnimatedConponents; i++ )
            {
                fscanf(fp, "%f", &animFrameData[i]);
            }

            BuildFrameSkeleton(jointInfos, baseFrame, animFrameData,
                               anim->skelFrames[frame_index], anim->num_joints);
        }
    }

    fclose(fp);

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
