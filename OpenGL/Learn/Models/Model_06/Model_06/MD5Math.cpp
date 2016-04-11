#include "MD5.h"

#include <math.h>


// 计算四元数的W
void Quat_computeW(Quat4_t q)
{
    float t = 1.0f - (q[X] * q[X]) - (q[Y] * q[Y]) - (q[Z] * q[Z]);

    if ( t < 0.0f )
    {
        q[W] = 0.0f;
    }
    else
    {
        q[W] = -sqrt(t);
    }
}

// 四元数标准化
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

// 四元数乘法
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
    out[Z] =  (q[W] * v[Z]) + (q[X] * q[Y]) - (q[Y] * v[X]);
}

// 向量绕四元数旋转
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
