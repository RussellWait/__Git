#ifndef __ROTATIONMATRIX_H_INCLUDED__
#define __ROTATIONMATRIX_H_INCLUDED__


class Vector3;
class EulerAngles;
class Quaternion;


class RotationMatrix
{
public:
	// ÷√Œ™µ•Œªæÿ’Û
	void identity();





	float m11, m12, m13;
	float m21, m22, m23;
	float m31, m32, m33;
};


#endif // !__ROTATIONMATRIX_H_INCLUDED__
