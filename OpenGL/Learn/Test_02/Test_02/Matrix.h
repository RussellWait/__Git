#pragma once

class CMatrix3X3
{
public:
    CMatrix3X3();
    float *Get();

private:
    float m_fMat[9];

    friend class CVector3;
    friend class CQuaternion;
};

class CMatrix4X4
{
public:
    CMatrix4X4();
    CMatrix4X4(const CMatrix4X4 &rMat);
    CMatrix4X4(float f11, float f12, float f13, float f14,
               float f21, float f22, float f23, float f24,
               float f31, float f32, float f33, float f34,
               float f41, float f42, float f43, float f44);

	float *Get();

    void Zero();
    void Identity();

    void SetRotation(float fX, float fY, float fZ);
    void SetRotation(float *fpRot);
    void InverseRotateVec(float *fpVec);

    void SetTranslation(float fX, float fY, float fZ);
    void SetTranslation(float *fpTrans);
    void InverseTranslateVec(float *fpVec);

	void FromQuaternion(CQuaternion &rQuat);

    const CMatrix4X4 operator *(const CMatrix4X4 &rMat) const;

private:
    float m_fMat[16];

    friend class CVector3;
    friend class CQuaternion;
};


#include "Matrix.inl"
