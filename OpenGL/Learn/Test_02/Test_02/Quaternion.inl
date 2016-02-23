#include "Quaternion.h"
#include <cmath>
#include <memory.h>
#include "Matrix.h"


inline CQuaternion LERP(CQuaternion &rQuat0, CQuaternion &rQuat1, float fInterp)
{
    CQuaternion ret;
    ret.m_fQuat[0] = (rQuat1.m_fQuat[0] - rQuat0.m_fQuat[0]) * fInterp + rQuat0.m_fQuat[0];
    ret.m_fQuat[1] = (rQuat1.m_fQuat[1] - rQuat0.m_fQuat[1]) * fInterp + rQuat0.m_fQuat[1];
    ret.m_fQuat[2] = (rQuat1.m_fQuat[2] - rQuat0.m_fQuat[2]) * fInterp + rQuat0.m_fQuat[2];
    ret.m_fQuat[3] = (rQuat1.m_fQuat[3] - rQuat0.m_fQuat[3]) * fInterp + rQuat0.m_fQuat[3];
    ret.Normalize();

    return ret;
}

inline CQuaternion SLERP(CQuaternion &rQuat0, CQuaternion &rQuat1, float fInterp)
{
    float *q0 = rQuat0.Get();
    float *q1 = rQuat1.Get();
    float fDot = q0[0] * q1[0] + q0[1] * q1[1] + q0[2] * q1[2] + q0[3] * q1[3];

    if ( fDot )
    {
        rQuat1.m_fQuat[0] = -rQuat1.m_fQuat[0];
        rQuat1.m_fQuat[1] = -rQuat1.m_fQuat[1];
        rQuat1.m_fQuat[2] = -rQuat1.m_fQuat[2];
        rQuat1.m_fQuat[3] = -rQuat1.m_fQuat[3];
    }

    if (fDot < 1.00001f && fDot > 0.99999f)
    {
        return LERP(rQuat0, rQuat1, fInterp);
    }

    float fTheta = acosf(fDot);

    CQuaternion ret;
    ret.m_fQuat[0] = (rQuat0.m_fQuat[0] * sinf(fTheta * (1 - fInterp)) + rQuat1.m_fQuat[0] * sinf(fTheta * fInterp)) / sinf(fTheta);

}

inline CQuaternion::CQuaternion()
{

}

inline CQuaternion::CQuaternion(float fX, float fY, float fZ, float fW)
{

}

inline CQuaternion::CQuaternion(float *fpQuat)
{

}

inline CQuaternion::CQuaternion(const CQuaternion &rQuat)
{

}

inline float CQuaternion::Magnitude() const
{

}

inline void CQuaternion::Normalize()
{

}

inline float *CQuaternion::Get()
{

}

inline void CQuaternion::FromEulers(float fX, float fY, float fZ)
{

}

inline void CQuaternion::FromEulers(float *fpAngles)
{

}

inline void CQuaternion::FromMatrix(CMatrix3X3 &rMat)
{

}

inline CMatrix4X4 CQuaternion::ToMatrix4() const
{

}
