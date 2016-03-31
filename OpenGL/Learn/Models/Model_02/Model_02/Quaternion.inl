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

    if ( fDot < 0.0f )
    {
        rQuat1.m_fQuat[0] = -rQuat1.m_fQuat[0];
        rQuat1.m_fQuat[1] = -rQuat1.m_fQuat[1];
        rQuat1.m_fQuat[2] = -rQuat1.m_fQuat[2];
        rQuat1.m_fQuat[3] = -rQuat1.m_fQuat[3];
        fDot = -fDot;
    }

    if ( fDot < 1.00001f && fDot > 0.99999f )
    {
        return LERP(rQuat0, rQuat1, fInterp);
    }

    float fTheta = acosf(fDot);

    CQuaternion ret;
    ret.m_fQuat[0] = (rQuat0.m_fQuat[0] * sinf(fTheta * (1 - fInterp)) + rQuat1.m_fQuat[0] * sinf(fTheta * fInterp)) / sinf(fTheta);
    ret.m_fQuat[1] = (rQuat0.m_fQuat[1] * sinf(fTheta * (1 - fInterp)) + rQuat1.m_fQuat[1] * sinf(fTheta * fInterp)) / sinf(fTheta);
    ret.m_fQuat[2] = (rQuat0.m_fQuat[2] * sinf(fTheta * (1 - fInterp)) + rQuat1.m_fQuat[2] * sinf(fTheta * fInterp)) / sinf(fTheta);
    ret.m_fQuat[3] = (rQuat0.m_fQuat[3] * sinf(fTheta * (1 - fInterp)) + rQuat1.m_fQuat[3] * sinf(fTheta * fInterp)) / sinf(fTheta);

    return ret;
}

inline CQuaternion::CQuaternion()
{
    memset(m_fQuat, 0, sizeof(float[4]));
    m_fQuat[3] = 1.0f;
}

inline CQuaternion::CQuaternion(float fX, float fY, float fZ, float fW)
{
    m_fQuat[0] = fX;
    m_fQuat[1] = fY;
    m_fQuat[2] = fZ;
    m_fQuat[3] = fW;
}

inline CQuaternion::CQuaternion(float *fpQuat)
{
    memcpy(m_fQuat, fpQuat, sizeof(float[4]));
}

inline CQuaternion::CQuaternion(const CQuaternion &rQuat)
{
    *this = rQuat;
}

inline float CQuaternion::Magnitude() const
{
    return sqrtf(SQU(m_fQuat[0]) + SQU(m_fQuat[1]) + SQU(m_fQuat[2]) + SQU(m_fQuat[3]));
}

inline void CQuaternion::Normalize()
{
    float fInvMag = 1 / Magnitude();
    if ( 1.0f != fInvMag )
    {
        m_fQuat[0] *= fInvMag;
        m_fQuat[1] *= fInvMag;
        m_fQuat[2] *= fInvMag;
        m_fQuat[3] *= fInvMag;
    }
}

inline float *CQuaternion::Get()
{
    return m_fQuat;
}

inline void CQuaternion::FromEulers(float fX, float fY, float fZ)
{
    double dSY = sin(fZ * 0.5f);
    double dSP = sin(fY * 0.5f);
    double dSR = sin(fX * 0.5f);
    double dCY = cos(fZ * 0.5f);
    double dCP = cos(fY * 0.5f);
    double dCR = cos(fX * 0.5f);

    m_fQuat[0] = dSR * dCP * dCY - dCR * dSP * dSY;
    m_fQuat[1] = dCR * dSP * dCY + dSR * dCP * dSY;
    m_fQuat[2] = dCR * dCP * dSY - dSR * dSP * dCY;
    m_fQuat[3] = dCR * dCP * dCY + dSR * dSP * dSY;
}

inline void CQuaternion::FromEulers(float *fpAngles)
{
    FromEulers(fpAngles[0], fpAngles[1], fpAngles[2]);
}

inline void CQuaternion::FromMatrix(CMatrix3X3 &rMat)
{
    float fTr = rMat.m_fMat[0] + rMat.m_fMat[4] + rMat.m_fMat[8] + 1.0f;

    if ( fTr > 0 )
    {
        float fS = 0.5f / sqrtf(fTr);

        m_fQuat[3] = 0.25f / fS;
        m_fQuat[0] = (rMat.m_fMat[7] - rMat.m_fMat[5]) * fS;
        m_fQuat[1] = (rMat.m_fMat[2] - rMat.m_fMat[6]) * fS;
        m_fQuat[2] = (rMat.m_fMat[3] - rMat.m_fMat[1]) * fS;
    }
    else if ( rMat.m_fMat[0] > rMat.m_fMat[4] && rMat.m_fMat[0] > rMat.m_fMat[8] )
    {
        float fS = 1 / (sqrt(rMat.m_fMat[0] - rMat.m_fMat[4] - rMat.m_fMat[8] + 1.0f) * 2);
        m_fQuat[0] = 0.5f * fS;
        m_fQuat[1] = (rMat.m_fMat[1] + rMat.m_fMat[3]) * fS;
        m_fQuat[2] = (rMat.m_fMat[2] + rMat.m_fMat[6]) * fS;
        m_fQuat[3] = (rMat.m_fMat[5] + rMat.m_fMat[7]) * fS;
    }
    else if ( rMat.m_fMat[4] > rMat.m_fMat[8] )
    {
        float fS = 1 / (sqrt(rMat.m_fMat[4] - rMat.m_fMat[0] - rMat.m_fMat[8] + 1.0f) * 2);
        m_fQuat[0] = (rMat.m_fMat[1] + rMat.m_fMat[3]) * fS;
        m_fQuat[1] = 0.5f * fS;
        m_fQuat[2] = (rMat.m_fMat[5] + rMat.m_fMat[7]) * fS;
        m_fQuat[3] = (rMat.m_fMat[2] + rMat.m_fMat[6]) * fS;
    }
    else
    {
        float fS = 1 / (sqrt(rMat.m_fMat[8] - rMat.m_fMat[0] - rMat.m_fMat[4] + 1.0f) * 2);
        m_fQuat[0] = (rMat.m_fMat[2] + rMat.m_fMat[6]) * fS;
        m_fQuat[1] = (rMat.m_fMat[5] + rMat.m_fMat[7]) * fS;
        m_fQuat[2] = 0.5f * fS;
        m_fQuat[3] = (rMat.m_fMat[1] + rMat.m_fMat[3]) * fS;
    }
}

inline CMatrix4X4 CQuaternion::ToMatrix4() const
{
    CMatrix4X4 Mat;

    Mat.m_fMat[0] = 1.0f - 2.0f * (SQU(m_fQuat[1]) + SQU(m_fQuat[2]));
    Mat.m_fMat[1] = 2.0f * m_fQuat[0] * m_fQuat[1] + 2.0f * m_fQuat[2] * m_fQuat[3];
    Mat.m_fMat[2] = 2.0f * m_fQuat[0] * m_fQuat[2] - 2.0f * m_fQuat[1] * m_fQuat[3];

    Mat.m_fMat[4] = 2.0f * m_fQuat[0] * m_fQuat[1] - 2.0f * m_fQuat[2] * m_fQuat[3];
    Mat.m_fMat[5] = 1.0f - 2.0f * (SQU(m_fQuat[0]) + SQU(m_fQuat[2]));
    Mat.m_fMat[6] = 2.0f * m_fQuat[1] * m_fQuat[2] + 2.0f * m_fQuat[0] * m_fQuat[3];

    Mat.m_fMat[8] = 2.0f * m_fQuat[2] * m_fQuat[0] + 2.0f * m_fQuat[1] * m_fQuat[3];
    Mat.m_fMat[9] = 2.0f * m_fQuat[1] * m_fQuat[2] - 2.0f * m_fQuat[0] * m_fQuat[3];
    Mat.m_fMat[10] = 1.0f - 2.0f * (SQU(m_fQuat[0]) + SQU(m_fQuat[1]));

    Mat.m_fMat[15] = 1.0f;

    return Mat;
}
