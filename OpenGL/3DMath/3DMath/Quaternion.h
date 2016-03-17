#ifndef __QUATERNION_H_INCLUDED__
#define __QUATERNION_H_INCLUDED__


class Vector3;
class EulerAngles;


// ʵ����3D�б�ʾ��λ�Ƶ���Ԫ��
class Quaternion
{
public:
    // ��Ϊ��λ��Ԫ��
    void identity();

	// ����ִ����ת����Ԫ��
	void setToRotateAboutX(float theta);
	void setToRotateAboutY(float theta);
	void setToRotateAboutZ(float theta);
	void setToRotateAboutAxis(const Vector3 &axis, float theta);

	// ����ִ������-������ת����Ԫ������λ������ŷ�������Ƹ���
	void setToRotateObjectToInertial(const EulerAngles &orientation);
	void setToRotateInertialToObject(const EulerAngles &orientation);

	// ���
	Quaternion operator*(const Quaternion &a) const;

	// ��ֵ�˷�
	Quaternion operator*=(const Quaternion &a);

	// ����Ԫ������
	void normalize();

	// ��ȡ��ת�Ǻ���ת��
	float getRotationAngle() const;
	Vector3 getRotationAxis() const;


    float w, x, y, z;
};


// ��Ԫ�����
extern float dotProduct(const Quaternion &a, const Quaternion &b);

// �������Բ�ֵ
extern Quaternion slerp(const Quaternion &a, const Quaternion &b, float t);

// ������Ԫ��
extern Quaternion conjugate(const Quaternion &q);

// ��Ԫ����
extern Quaternion pow(const Quaternion &q, float exponent);



// ȫ�֡���λ����Ԫ��
extern const Quaternion kQuaternionIdentity;


#include "Quaternion.inl"


#endif // !__QUATERNION_H_INCLUDED__
