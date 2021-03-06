#include "Matrix.h"


inline CVector3::CVector3()
{
    m_fVec[0] = 0.0f;
    m_fVec[1] = 0.0f;
    m_fVec[2] = 0.0f;
}

inline CVector3::CVector3(float fX, float fY, float fZ)
{
    m_fVec[0] = fX;
    m_fVec[1] = fY;
    m_fVec[2] = fZ;
}

inline float *CVector3::Get()
{
    return m_fVec;
}

inline void CVector3::Set(float *fpVec)
{
    m_fVec[0] = fpVec[0];
    m_fVec[1] = fpVec[1];
    m_fVec[2] = fpVec[2];
}

inline void CVector3::Transform3(const CMatrix4X4 &rMat)
{
    CVector3 tmp(m_fVec[0] * rMat.m_fMat[0] + m_fVec[1] * rMat.m_fMat[4] + m_fVec[2] * rMat.m_fMat[8],
                 m_fVec[0] * rMat.m_fMat[1] + m_fVec[1] * rMat.m_fMat[5] + m_fVec[2] * rMat.m_fMat[9],
                 m_fVec[0] * rMat.m_fMat[2] + m_fVec[1] * rMat.m_fMat[6] + m_fVec[2] * rMat.m_fMat[10]);

    *this = tmp;
}

inline void CVector3::Transform4(const CMatrix4X4 &rMat)
{
    CVector3 tmp(m_fVec[0] * rMat.m_fMat[0] + m_fVec[1] * rMat.m_fMat[4] + m_fVec[2] * rMat.m_fMat[8] + rMat.m_fMat[12],
                 m_fVec[0] * rMat.m_fMat[1] + m_fVec[1] * rMat.m_fMat[5] + m_fVec[2] * rMat.m_fMat[9] + rMat.m_fMat[13],
                 m_fVec[0] * rMat.m_fMat[2] + m_fVec[1] * rMat.m_fMat[6] + m_fVec[2] * rMat.m_fMat[10] + rMat.m_fMat[14]);

    *this = tmp;
}
