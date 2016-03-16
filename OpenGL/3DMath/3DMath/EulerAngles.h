#ifndef __EULERANGLES_H_INCLUDED__
#define __EULERANGLES_H_INCLUDED__


class Quaternion;
class Matrix4x3;
class RotationMatrix;


// 该类用于表示 heading-pitch-bank 欧拉角系统
class EulerAngles
{
public:
    EulerAngles() {}

    EulerAngles(float h, float p, float b) :
        heading(h), pitch(p), bank(b) {}


    // 置零
    void identity();

    // 变换为“限制集”欧拉角
    void canonize();

    // 从四元数转换到欧拉角
    void fromObjectToInertialQuaternion(const Quaternion &q);
    void fromInertialToObjectQuaternion(const Quaternion &q);

    // 从矩阵转换到欧拉角
    // 平移部分被省略，并且假设矩阵是正交的
    void fromObjectToWorldMatrix(const Matrix4x3 &m);
    void fromWorldToObjectMatrix(const Matrix4x3 &m);

    // 从旋转矩阵转换到欧拉角
    void fromRotationMatrix(const RotationMatrix &m);


    float heading;
    float pitch;
    float bank;
};


// 全局的“单位”欧拉角
extern const EulerAngles kEulerAnglesIdentity;


#include "EulerAngles.inl"


#endif // !__EULERANGLES_H_INCLUDED__
