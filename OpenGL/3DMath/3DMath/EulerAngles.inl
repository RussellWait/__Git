#include <math.h>

#include "MathUtil.h"
#include "Quaternion.h"
#include "Matrix4x3.h"
#include "RotationMatrix.h"


const EulerAngles kEulerAnglesIdentity(0.0f, 0.0f, 0.0f);


EulerAngles::EulerAngles() {}

EulerAngles::EulerAngles(float h, float p, float b)
{
    heading = h;
    pitch = p;
    bank = b;
}

inline void EulerAngles::identity()
{
    heading = pitch = bank = 0.0f;
}

inline void EulerAngles::canonize()
{
    // 先将pitch变换到 -pi 到 pi
    pitch = wrapPi(pitch);

    // 再将pitch变换到 -pi/2 到 pi/2
    if ( pitch < -kPiOver2 )
    {
        pitch = -kPi - pitch;
        heading += kPi;
        bank += kPi;
    }
    else if ( pitch > kPiOver2 )
    {
        pitch = kPi - pitch;
        heading += kPi;
        bank += kPi;
    }

    // 检查万向锁
    if ( fabs(pitch) > kPiOver2 - 1e-4 )
    {
        // 万向锁中，将所有绕垂直轴的旋转胡歌heading
        heading += bank;
        bank = 0.0f;
    }
    else
    {
        // 非万向锁，将bank转换到限制集中
        bank = wrapPi(bank);
    }

    // 将heading转换到限制集中
    heading = wrapPi(heading);
}

// 从 物体-惯性变换 四元数到欧拉角
inline void EulerAngles::fromObjectToInertialQuaternion(const Quaternion &q)
{
    // 计算sin(pitch)
    float sp = -2.0f * (q.y * q.z - q.w * q.x);

    // 检查万向锁
    if ( fabs(sp) > 0.9999f )
    {
        pitch = kPiOver2 * sp;
        heading = atan2(-q.x * q.z + q.w * q.y, 0.5f - q.y * q.y - q.z * q.z);
        bank = 0.0f;
    }
    else
    {
        // 计算角度
        pitch = asin(sp);
        heading = atan2(q.x * q.z + q.w * q.y, 0.5f - q.x * q.x - q.y * q.y);
        bank = atan2(q.x * q.y + q.w * q.z, 0.5f - q.x * q.x - q.z * q.z);
    }
}

// 从 惯性-物体变换 四元数到欧拉角
inline void EulerAngles::fromInertialToObjectQuaternion(const Quaternion &q)
{
    // 计算sin(pitch)
    float sp = -2.0f * (q.y * q.y + q.w * q.x);

    // 检查万向锁
    if ( fabs(sp) > 0.9999f )
    {
        pitch = kPiOver2 * sp;
        heading = atan2(-q.x * q.z - q.w * q.y, 0.5f - q.y * q.y - q.z * q.z);
        bank = 0.0f
    }
    else
    {
        pitch = asin(sp);
        heading = atan2(q.x * q.z - q.w * q.y, 0.5f - q.x * q.x - q.y * q.y);
        bank = atan2(q.x * q.y - q.w * q.z, 0.5f - q.x * q.x - q.z * q.z);
    }
}

// 从 物体-世界坐标系变换 矩阵到欧拉角
inline void EulerAngles::fromObjectToWorldMatrix(const Matrix4x3 &m)
{
    // 通过m32计算sin(pitch)
    float sp = -m.m32;

    if ( fabs(sp) > 0.9999f )
    {
        pitch = kPiOver2 * sp;
        heading = atan2(-m.m23, m.m11);
        bank = 0.0f;
    }
    else
    {
        heading = atan2(m.m31, m.m33);
        pitch = asin(sp);
        bank = atan2(m.m12, m.m22);
    }
}

// 从 实际-物体坐标系变换 矩阵到欧拉角
inline void EulerAngles::fromWorldToObjectMatrix(const Matrix4x3 &m)
{
    float sp = -m.m23;

    if ( fabs(sp) > 0.9999f )
    {
        pitch = kPiOver2 * sp;
        heading = atan2(-m.m31, m.m11);
        bank = 0.0f;
    }
    else
    {
        heading = atan2(m.m13, m.m33);
        pitch = asin(sp);
        bank = atan2(m.m21, m.m22);
    }
}

inline void EulerAngles::fromRotationMatrix(const RotationMatrix &m)
{
    // 计算sin(pitch)
    float sp = -m.m23;

    // 检查万向锁
    if ( fabs(sp) > 0.9999f )
    {
        pitch = kPiOver2 * sp;
        heading = atan2(-m.m31, m.m11);
        bank = 0.0f;
    }
    else
    {
        heading = atan2(m.m13, m.m33);
        pitch = asin(sp);
        bank = atan2(m.m21, m.m22);
    }
}
