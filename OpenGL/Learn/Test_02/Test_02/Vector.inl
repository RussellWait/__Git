#pragma once

#include "Vector.h"
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

inline void CVector3::Transform3(const CMatrix3X3 &mat)
{
    CVector3 tmp(mat.m_fMat[0] * m_fVec[0] + mat.m_fMat[3] * m_fVec[1] + mat.m_fMat[6] * m_fVec[2],
                 mat.m_fMat[1] * m_fVec[0] + mat.m_fMat[4] * m_fVec[1] + mat.m_fMat[7] * m_fVec[2],
                 mat.m_fMat[2] * m_fVec[0] + mat.m_fMat[5] * m_fVec[1] + mat.m_fMat[8] * m_fVec[2]);

    *this = tmp;
}

inline void CVector3::Transform3(const CMatrix4X4 &mat)
{
    CVector3 tmp(mat.m_fMat[0] * m_fVec[0] + mat.m_fMat[4] * m_fVec[1] + mat.m_fMat[8] * m_fVec[2],
                 mat.m_fMat[1] * m_fVec[0] + mat.m_fMat[5] * m_fVec[1] + mat.m_fMat[9] * m_fVec[2],
                 mat.m_fMat[2] * m_fVec[0] + mat.m_fMat[6] * m_fVec[1] + mat.m_fMat[10] * m_fVec[2]);

    *this = tmp;
}

inline void CVector3::Transform4(const CMatrix4X4 &mat)
{
    CVector3 tmp(mat.m_fMat[0] * m_fVec[0] + mat.m_fMat[4] * m_fVec[1] + mat.m_fMat[8] * m_fVec[2] + mat.m_fMat[12],
                 mat.m_fMat[1] * m_fVec[0] + mat.m_fMat[5] * m_fVec[1] + mat.m_fMat[9] * m_fVec[2] + mat.m_fMat[13],
                 mat.m_fMat[2] * m_fVec[0] + mat.m_fMat[6] * m_fVec[1] + mat.m_fMat[10] * m_fVec[2] + mat.m_fMat[14]);

    *this = tmp;
}
