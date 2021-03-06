#include "MD5.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


extern Vec3_t *vertexArray;
extern Vec2_t *textureArray;
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
    float               *animFrameData  = NULL; // 临时存放Frame n 数据块中的信息

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
        // 读取框架数量，并分配存储骨骼框架与包围盒信息的空间
        else if ( 1 == sscanf(buff, " numFrames %d", &anim->num_frames) )
        {
            if ( anim->num_frames > 0 )
            {
                anim->skelFrames = (MD5_Joint_t **)malloc(sizeof(MD5_Joint_t *) * anim->num_frames);
                anim->bboxes = (MD5_BBox_t *)malloc(sizeof(MD5_BBox_t) * anim->num_frames);
            }
        }
        // 读取骨骼的数量，并分配骨骼框架中存放骨骼信息的空间
        else if ( 1 == sscanf(buff, " numJoints %d", &anim->num_joints) )
        {
            if ( anim->num_joints > 0 )
            {
                for ( int i = 0; i < anim->num_frames; i++ )
                {
                    // 分配空间
                    anim->skelFrames[i] = (MD5_Joint_t *)malloc(sizeof(MD5_Joint_t) * anim->num_joints);
                }
                // 临时存放hierarchy中信息，这些信息在骨骼框架建立后不再需要
                jointInfos = (Joint_Info_t *)malloc(sizeof(Joint_Info_t) * anim->num_joints);
                // 基础骨骼框架的信息
                baseFrame = (BaseFrame_Joint_t *)malloc(sizeof(BaseFrame_Joint_t) * anim->num_joints);
            }
        }
        // 读取框架的帧速度
        else if ( 1 == sscanf(buff, " frameRate %d", &anim->frameRate) )
        {
            // ...
        }
        // 读取动画组件参数的数量并分配存储空间
        else if ( 1 == sscanf(buff, " numAnimatedComponents %d", &numAnimatedConponents) )
        {
            if ( numAnimatedConponents > 0 )
            {
                animFrameData = (float *)malloc(sizeof(float) * numAnimatedConponents);
            }
        }
        // 读取hierarchy数据块中的信息
        else if ( 0 == strncmp(buff, "hierarchy {", 11) )
        {
            for ( int i = 0; i < anim->num_joints; i++ )
            {
                // read whole line
                fgets(buff, sizeof(buff), fp);
                // read joint info
                sscanf(buff, " %s %d %d %d",
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
        // 读取基础框架数据块的数据
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
        // 读取动画框架数据块中的信息并建立每一个动画帧的骨骼矿机数据与骨骼之间的联系
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
    int vertex_index;
    for ( int i = 0; i < mdl->num_meshes; i++ )
    {
        if ( 1 == i || 2 == i )
        {
            continue;
        }

		PrepareMesh(&mdl->meshes[i], anim->skelFrames[skelFrames_index]);

        glBindTexture(GL_TEXTURE_2D, mdl->meshes[i].textures_h);

        // 初始化顶点与纹理数组
        glVertexPointer(3, GL_FLOAT, 0, vertexArray);
        glTexCoordPointer(2, GL_FLOAT, 0, textureArray);

        // 打开顶点与纹理数组功能
        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);

        // 绘画顶点数组中的内容
        glDrawElements(GL_TRIANGLES, mdl->meshes[i].num_tris * 3, GL_UNSIGNED_INT, vertexIndices);

        // 关闭顶点与纹理数组功能
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);
        glDisableClientState(GL_VERTEX_ARRAY);
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
