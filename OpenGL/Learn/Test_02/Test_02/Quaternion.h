#pragma once

class CVector3;
class CMatrix3X3;
class CMatrix4X4;


class CQuaternion
{
public:
	CQuaternion();
	CQuaternion(float fX, float fY, float fZ, float fW);
	CQuaternion(float *fpQuat);
	CQuaternion(const CQuaternion &rQuat);

	float Magnitude() const;
	void Normalize();

	float *Get();
	void FromEulers(float fX, float fY, float fZ);
	void FromEulers(float *fpAngles);
	void FromMatrix(CMatrix3X3 &rMat);
	CMatrix4X4 ToMatrix4() const;

private:
	float m_fQuat[4];

	friend CVector3;
	friend CMatrix3X3;
	friend CMatrix4X4;
};


#include "Quaternion.inl"
