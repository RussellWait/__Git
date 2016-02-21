#pragma once

#pragma pack(push, packing)
#pragma pack(1)


class CQuaternion;
class CMatrix3X3;
class CMatrix4X4;


class CVector3
{
public:
    CVector3();
    CVector3(float fX, float fY, float fZ);

    float *Get();
    void Set(float *fpVec);

    void Transform3(const CMatrix3X3 &mat);
    void Transform3(const CMatrix4X4 &mat);
    void Transform4(const CMatrix4X4 &mat);

private:
    float m_fVec[3];

    friend CQuaternion;
    friend CMatrix3X3;
    friend CMatrix4X4;
};


#include "Vector.inl"
