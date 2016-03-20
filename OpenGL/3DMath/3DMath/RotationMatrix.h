#ifndef __ROTATIONMATRIX_H_INCLUDED__
#define __ROTATIONMATRIX_H_INCLUDED__


class Vector3;
class EulerAngles;
class Quaternion;


class RotationMatrix
{
public:
    // 置为单位矩阵
    void identity();

    // 根据指定的方位构造矩阵
    void setup(const EulerAngles &orientation);

    // 根据四元数构造矩阵
    void fromInertialToObjectQuaternion(const Quaternion &q);
    void fromObjectToInertialQuaternion(const Quaternion &q);

    // 执行旋转
    Vector3 inertialToObject(const Vector3 &v) const;
    Vector3 objectToInertial(const Vector3 &v) const;


    // 公共属性
    float m11, m12, m13;
    float m21, m22, m23;
    float m31, m32, m33;
};


#include "RotationMatrix.inl"


#endif // !__ROTATIONMATRIX_H_INCLUDED__
