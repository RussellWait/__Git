#include <assert.h>
#include <math.h>

#include "MathUtil.h"
#include "Vector3.h"
#include "EulerAngles.h"


const Quaternion kQuaternionIdentity = {1.0f, 0.0f, 0.0f, 0.0f};


inline void Quaternion::identity()
{
    w = 1.0f;
    x = y = z = 0.0f;
}

inline void Quaternion::normalize()
{
    float mag = (float)sqrt(w * w + x * x + y * y + z * z);

    if ( mag > 0.0f )
    {
        float oneOverMag = 1.0f / mag;
        w *= oneOverMag;
        x *= oneOverMag;
        y *= oneOverMag;
        z *= oneOverMag;
    }
    else
    {
        assert(false);
        identity();
    }
}

inline void Quaternion::setToRotateAboutX(float theta)
{
    float thetaOver2 = theta * 0.5f;

    w = cos(thetaOver2);
    x = sin(thetaOver2);
    y = 0.0f;
    z = 0.0f;
}

inline void Quaternion::setToRotateAboutY(float theta)
{
    float thetaOver2 = theta * 0.5f;

    w = cos(thetaOver2);
    x = 0.0f;
    y = sin(thetaOver2);
    z = 0.0f;
}

inline void Quaternion::setToRotateAboutZ(float theta)
{
    float thetaOver2 = theta * 0.5f;

    w = cos(thetaOver2);
    x = 0.0f;
    y = 0.0f;
    z = sin(thetaOver2);
}

inline void Quaternion::setToRotateAboutAxis(const Vector3 &axis, float theta)
{
    // ��ת������׼��
    assert(fabs(vectorMag(axis) - 1.0f) < 0.1);

    float thetaOver2 = theta * 0.5f;
    float sinThetaOver2 = sin(thetaOver2);

    w = cos(thetaOver2);
    x = axis.x * sinThetaOver2;
    y = axis.y * sinThetaOver2;
    z = axis.z *sinThetaOver2;
}

inline void Quaternion::setToRotateObjectToInertial(const EulerAngles &orientation)
{
    float sh, sp, sb;
    float ch, cp, cb;

    sinCos(&sh, &ch, orientation.heading * 0.5f);
    sinCos(&sp, &cp, orientation.pitch * 0.5f);
    sinCos(&sb, &cb, orientation.bank * 0.5f);

    w = ch * cp * cb + sh * sp * sb;
    x = ch * sp * cb + sh * cp * sb;
    y = sh * cp * cb - ch * sp * sb;
    z = ch * cp * sb - sh * sp * cb;
}

inline void Quaternion::setToRotateInertialToObject(const EulerAngles &orientation)
{
    float sh, sp, sb;
    float ch, cp, cb;

    sinCos(&sh, &ch, orientation.heading * 0.5f);
    sinCos(&sp, &cp, orientation.pitch * 0.5f);
    sinCos(&sb, &cb, orientation.bank * 0.5f);

    w = ch * cp *cb + sh * sp * sb;
    x = -ch * sp *cb - sh * cp * sb;
    y = ch * sp * sb - sh * cp * cb;
    z = sh * sp *cb - ch *cp * sb;
}

inline Quaternion Quaternion::operator *(const Quaternion &q) const
{
    Quaternion result;

    result.w = w * q.w - x * q.x - y * q.y - z * q.z;
    result.x = w * q.x + x * q.w + z * q.y - y * q.z;
    result.y = w * q.y + y * q.w + x * q.z - z * q.x;
    result.z = w * q.z + z * q.w + y * q.x - x * q.y;

    return result;
}

inline Quaternion &Quaternion::operator *=(const Quaternion &q)
{
    *this = *this * q;

    return *this;
}

inline float Quaternion::getRotationAngle() const
{
    return safeAcos(w) * 2.0f;
}

inline Vector3 Quaternion::getRotationAxis() const
{
    float sinThetaOver2Sq = 1.0f - w * w;

    // ��֤��ֵ��ȷ��
    if ( sinThetaOver2Sq <= 0.0f )
    {
        return Vector3(1.0f, 0.0f, 0.0f);
    }
    else
    {
        float oneOverSinThetaOver2 = 1.0f / sqrt(sinThetaOver2Sq);

        return Vector3(x * oneOverSinThetaOver2,
                       y * oneOverSinThetaOver2,
                       z * oneOverSinThetaOver2);
    }
}

inline Quaternion conjugate(const Quaternion &q)
{
    Quaternion result;
    result.w = q.w;
    result.x = -q.x;
    result.y = -q.y;
    result.z = -q.z;

    return result;
}

inline float dotProduct(const Quaternion &q1, const Quaternion &q2)
{
    return q1.w * q2.w + q1.x * q2.x + q1.y * q2.y + q1.z * q2.z;
}

inline Quaternion pow(const Quaternion &q, float exponent)
{
    if ( fabs(q.w) > 0.9999f )
    {
        return q;
    }

    float alpha = acos(q.w);
    float newAlpha = alpha * exponent;
    float mult = sin(newAlpha) / sin(alpha);

    Quaternion result;
    result.w = cos(newAlpha);
    result.x = q.x * mult;
    result.y = q.y * mult;
    result.z = q.z * mult;

    return result;

}

inline Quaternion slerp(const Quaternion &q0, const Quaternion &q1, float t)
{
    // ���߽�
    if ( t <= 0.0f )
    {
        return q0;
    }
    else if ( t >= 1.0f )
    {
        return q1;
    }

    // ������Ԫ���нǵ�cosֵ
    float cosOmega = dotProduct(q0, q1);

    // �����õ���������λ��Ԫ�������Ե��Ӧ��<= 1.0f;
    assert(cosOmega < 1.1f);

    // ������Ϊ����ʹ��-q1
    // ��Ԫ��q1��-q1������ͬ����ת�����ǿ��ܲ�����ͬ��slerp����
    float q1w = q1.w;
    float q1x = q1.x;
    float q1y = q1.y;
    float q1z = q1.z;

    if ( cosOmega < 0.0f)
    {
        q1w = -q1w;
        q1x = -q1x;
        q1y = -q1y;
        q1z = -q1z;
        cosOmega = -cosOmega;
    }

    float k0, k1;
    if (cosOmega > 0.9999f)
    {
        k0 = 1.0f - t;
        k1 = t;
    }
    else
    {
        float sinOmega = sqrt(1.0f - cosOmega * cosOmega);
        float omega = atan2(sinOmega, cosOmega);
        float oneOverSinOmega = 1.0f / sinOmega;

        k0 = sin((1.0f - t) * omega) * oneOverSinOmega;
        k1 = sin(t * omega) * oneOverSinOmega;
    }

    Quaternion result;
    result.w = k0 * q0.w + k1 * q1w;
    result.x = k0 * q0.x + k1 * q1x;
    result.y = k0 * q0.y + k1 * q1y;
    result.z = k0 * q0.z + k1 * q1z;

    return result;
}
