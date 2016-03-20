#ifndef __ROTATIONMATRIX_H_INCLUDED__
#define __ROTATIONMATRIX_H_INCLUDED__


class Vector3;
class EulerAngles;
class Quaternion;


class RotationMatrix
{
public:
    // ��Ϊ��λ����
    void identity();

    // ����ָ���ķ�λ�������
    void setup(const EulerAngles &orientation);

    // ������Ԫ���������
    void fromInertialToObjectQuaternion(const Quaternion &q);
    void fromObjectToInertialQuaternion(const Quaternion &q);

    // ִ����ת
    Vector3 inertialToObject(const Vector3 &v) const;
    Vector3 objectToInertial(const Vector3 &v) const;


    // ��������
    float m11, m12, m13;
    float m21, m22, m23;
    float m31, m32, m33;
};


#include "RotationMatrix.inl"


#endif // !__ROTATIONMATRIX_H_INCLUDED__
