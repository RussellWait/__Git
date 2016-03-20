#ifndef __QUATERNION_H_INCLUDED__
#define __QUATERNION_H_INCLUDED__


class Vector3;
class EulerAngles;


class Quaternion
{
public:
    // ��Ϊ��λ��Ԫ��
    void identity();

    // ����Ԫ������
    void normalize();

    // ����ִ����ת����Ԫ��
    void setToRotateAboutX(float theta);
    void setToRotateAboutY(float theta);
    void setToRotateAboutZ(float theta);
    void setToRotateAboutAxis(const Vector3 &axis, float theta);

    // ����ִ�� ����-���� ��ת����Ԫ������λ������ŷ������ʽ����
    void setToRotateObjectToInertial(const EulerAngles &orientation);
    void setToRotateInertialToObject(const EulerAngles &orientation);

    // ���
    Quaternion operator *(const Quaternion &q) const;

    // ��ֵ�˷�
    Quaternion &operator *=(const Quaternion &q);

    // ��ȡ��ת�Ǻ���ת��
    float getRotationAngle() const;
    Vector3 getRotationAxis() const;


    // ��������
    float w, x, y, z;
};


// ��Ԫ������
Quaternion conjugate(const Quaternion &q);

// ��Ԫ�����
float dotProduct(const Quaternion &q1, const Quaternion &q2);

// ��Ԫ����
Quaternion pow(const Quaternion &q, float exponent);

// �������Բ�ֵ
Quaternion slerp(const Quaternion &q0, const Quaternion &q1, float t);


// ȫ�֡���λ����Ԫ��
extern const Quaternion kQuaternionIdentity;


#endif // !__QUATERNION_H_INCLUDED__
