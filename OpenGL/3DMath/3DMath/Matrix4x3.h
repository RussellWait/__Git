#ifndef __MATRIX4x3_H_INCLUDED__
#define __MATRIX4X3_H_INCLUDED__


class Vector3;
class EulerAngles;
class Quaternion;
class RotationMatrix;


class Matrix4x3
{
public:
    // 置为单位矩阵
    void identity();

    // 直接访问平移部分
    void zeroTranslation();
    void setTranslation(const Vector3 &d);
    void setupTranslation(const Vector3 &d);




    // 公共属性
    float m11, m12, m13;
    float m21, m22, m23;
    float m31, m32, m33;
    float tx, ty, tz;
};


#include "Matrix4x3.inl"


#endif // !__MATRIX4x3_H_INCLUDED__
