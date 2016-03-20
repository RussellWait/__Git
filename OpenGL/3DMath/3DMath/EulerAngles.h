#ifndef __EULERANGLES_H_INCLUDED__
#define __EULERANGLES_H_INCLUDED__


class Quaternion;
class Matrix4x3;
class RotationMatrix;


class EulerAngles
{
public:
    // 构造函数
    EulerAngles();

    EulerAngles(float h, float p, float b);


    // 置零
    void identity();

    // 变换为“限制集”欧拉角
    void canonize();

    // 从四元数转换到欧拉角
    void fromObjectToInertialQuaternion(const Quaternion &q);

    void fromInertialToObjectQuaternion(const Quaternion &q);

    // 从矩阵转换到欧拉角(平移部分被省略，并且假设矩阵是正交的)
    void fromObjectToWorldMatrix(const Matrix4x3 &m);

    void fromWorldToObjectMatrix(const Matrix4x3 &m);

    // 从旋转矩阵转换到欧拉角
    void fromRotationMatrix(const RotationMatrix &m);


    // 公共数据
    float heading;
    float pitch;
    float bank;
};


// 全局“单位”欧拉角
 const EulerAngles kEulerAnglesIdentity;


#include "EulerAngles.inl"


#endif // !__EULERANGLES_H_INCLUDED__
