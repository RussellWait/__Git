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
    // �Ƚ�pitch�任�� -pi �� pi
    pitch = wrapPi(pitch);

    // �ٽ�pitch�任�� -pi/2 �� pi/2
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

    // ���������
    if ( fabs(pitch) > kPiOver2 - 1e-4 )
    {
        // �������У��������ƴ�ֱ�����ת����heading
        heading += bank;
        bank = 0.0f;
    }
    else
    {
        // ������������bankת�������Ƽ���
        bank = wrapPi(bank);
    }

    // ��headingת�������Ƽ���
    heading = wrapPi(heading);
}

// �� ����-���Ա任 ��Ԫ����ŷ����
inline void EulerAngles::fromObjectToInertialQuaternion(const Quaternion &q)
{
    // ����sin(pitch)
    float sp = -2.0f * (q.y * q.z - q.w * q.x);

    // ���������
    if ( fabs(sp) > 0.9999f )
    {
        pitch = kPiOver2 * sp;
        heading = atan2(-q.x * q.z + q.w * q.y, 0.5f - q.y * q.y - q.z * q.z);
        bank = 0.0f;
    }
    else
    {
        // ����Ƕ�
        pitch = asin(sp);
        heading = atan2(q.x * q.z + q.w * q.y, 0.5f - q.x * q.x - q.y * q.y);
        bank = atan2(q.x * q.y + q.w * q.z, 0.5f - q.x * q.x - q.z * q.z);
    }
}

// �� ����-����任 ��Ԫ����ŷ����
inline void EulerAngles::fromInertialToObjectQuaternion(const Quaternion &q)
{
    // ����sin(pitch)
    float sp = -2.0f * (q.y * q.y + q.w * q.x);

    // ���������
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

// �� ����-��������ϵ�任 ����ŷ����
inline void EulerAngles::fromObjectToWorldMatrix(const Matrix4x3 &m)
{
    // ͨ��m32����sin(pitch)
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

// �� ʵ��-��������ϵ�任 ����ŷ����
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
    // ����sin(pitch)
    float sp = -m.m23;

    // ���������
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
