#include "Matrix.h"
#include <windows.h>
#include <math.h>
#include <assert.h>


#define SQU(x)  (x) * (x)


/************************************************************************/
/* CMatrix3X3
/************************************************************************/
inline CMatrix3X3::CMatrix3X3()
{
    memset(m_fMat, 0, sizeof(float[9]));
}

inline float *CMatrix3X3::Get()
{
    return m_fMat;
}


/************************************************************************/
/* CMatrix4X4
/************************************************************************/
inline CMatrix4X4::CMatrix4X4()
{
    memset(m_fMat, 0, sizeof(float[16]));
}

inline CMatrix4X4::CMatrix4X4(const CMatrix4X4 &mat)
{
    *this = mat;
}

inline CMatrix4X4::CMatrix4X4(float f11, float f12, float f13, float f14,
                              float f21, float f22, float f23, float f24,
                              float f31, float f32, float f33, float f34,
                              float f41, float f42, float f43, float f44)
{
    m_fMat[0] = f11;
    m_fMat[1] = f12;
    m_fMat[2] = f13;
    m_fMat[3] = f14;
    m_fMat[4] = f21;
    m_fMat[5] = f22;
    m_fMat[6] = f23;
    m_fMat[7] = f24;
    m_fMat[8] = f31;
    m_fMat[9] = f32;
    m_fMat[10] = f33;
    m_fMat[11] = f34;
    m_fMat[12] = f41;
    m_fMat[13] = f42;
    m_fMat[14] = f43;
    m_fMat[15] = f44;
}

inline void CMatrix4X4::Zero()
{
    memset(m_fMat, 0, sizeof(float[16]));
}

inline void CMatrix4X4::Identity()
{
    Zero();
    m_fMat[0] = 1.0f;
    m_fMat[5] = 1.0f;
    m_fMat[10] = 1.0f;
    m_fMat[15] = 1.0f;
}

inline void CMatrix4X4::SetRotation(float fX, float fY, float fZ)
{
    double cx = cos(fX);
    double sx = sin(fX);
    double cy = cos(fY);
    double sy = sin(fY);
    double cz = cos(fZ);
    double sz = sin(fZ);

    m_fMat[0] = (float)(cy * cz);
    m_fMat[1] = (float)(cy * sz);
    m_fMat[2] = (float)(-sy);

    m_fMat[4] = (float)(sx * sy * cz - cx * sz);
    m_fMat[5] = (float)(sx * sy * sz + sx * cz);
    m_fMat[6] = (float)(cx * cy);

    m_fMat[8] = (float)(cx * sy * cz + sx * sz);
    m_fMat[9] = (float)(cx * sy * sz - sx * cz);
    m_fMat[10] = (float)(cx * cy);

    m_fMat[15] = 1.0f;
}

inline void CMatrix4X4::SetRotation(float *fpRot)
{
    SetRotation(fpRot[0], fpRot[1], fpRot[2]);
}

inline void CMatrix4X4::InverseRotateVec(float *fpVec)
{
    float tmp[3];

    tmp[0] = fpVec[0] * m_fMat[0] + fpVec[1] * m_fMat[1] + fpVec[2] * m_fMat[2];
    tmp[1] = fpVec[0] * m_fMat[4] + fpVec[1] * m_fMat[5] + fpVec[2] * m_fMat[6];
    tmp[2] = fpVec[0] * m_fMat[8] + fpVec[1] * m_fMat[9] + fpVec[2] * m_fMat[10];

    memcpy(fpVec, tmp, sizeof(float[3]));
}

inline void CMatrix4X4::SetTranslation(float fX, float fY, float fZ)
{
    m_fMat[12] = fX;
    m_fMat[13] = fY;
    m_fMat[14] = fZ;
}

inline void CMatrix4X4::SetTranslation(float *fpTrans)
{
    SetTranslation(fpTrans[0], fpTrans[1], fpTrans[2]);
}

inline void CMatrix4X4::InverseTranslateVec(float *fpVec)
{
    assert(fpVec);

    fpVec[0] -= m_fMat[12];
    fpVec[1] -= m_fMat[13];
    fpVec[2] -= m_fMat[14];
}

inline const CMatrix4X4 CMatrix4X4::operator *(const CMatrix4X4 &mat) const
{
    const float *m1 = m_fMat;
    const float *m2 = mat.m_fMat;

    return CMatrix4X4((m1[0] * m2[0] + m1[4] * m2[1] + m1[8] * m2[2] + m1[12] * m2[3]),
                      (m1[1] * m2[0] + m1[5] * m2[1] + m1[9] * m2[2] + m1[13] * m2[3]),
                      (m1[2] * m2[0] + m1[7] * m2[1] + m1[10] * m2[2] + m1[14] * m2[3]),
                      (m1[3] * m2[0] + m1[8] * m2[1] + m1[11] * m2[2] + m1[15] * m2[3]),
                      
                      (m1[0] * m2[4] + m1[4] * m2[5] + m1[8] * m2[6] + m1[12] * m2[7]),
                      (m1[1] * m2[4] + m1[5] * m2[5] + m1[9] * m2[6] + m1[13] * m2[7]),
                      (m1[2] * m2[4] + m1[6] * m2[5] + m1[10] * m2[6] + m1[14] * m2[7]),
                      (m1[3] * m2[4] + m1[7] * m2[5] + m1[11] * m2[6] + m1[15] * m2[7]),
                      
                      (m1[0] * m2[8] + m1[4] * m2[9] + m1[8] * m2[10] + m1[12] * m2[11]),
                      (m1[1] * m2[8] + m1[5] * m2[9] + m1[9] * m2[10] + m1[13] * m2[11]),
                      (m1[2] * m2[8] + m1[7] * m2[9] + m1[10] * m2[10] + m1[14] * m2[11]),
                      (m1[3] * m2[8] + m1[8] * m2[9] + m1[11] * m2[10] + m1[15] * m2[11]), 
                      
                      (m1[0] * m2[12] + m1[4] * m2[13] + m1[8] * m2[14] + m1[12] * m2[15]),
                      (m1[1] * m2[12] + m1[5] * m2[13] + m1[9] * m2[14] + m1[13] * m2[15]),
                      (m1[2] * m2[12] + m1[7] * m2[13] + m1[10] * m2[14] + m1[14] * m2[15]),
                      (m1[3] * m2[12] + m1[8] * m2[13] + m1[11] * m2[14] + m1[15] * m2[15]));
}
