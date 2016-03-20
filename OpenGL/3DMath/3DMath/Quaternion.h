#ifndef __QUATERNION_H_INCLUDED__
#define __QUATERNION_H_INCLUDED__


class Vector3;
class EulerAngles;


class Quaternion
{
public:
    // 置为单位四元数
    void identity();

    // 将四元数正则化
    void normalize();

    // 构造执行旋转的四元数
    void setToRotateAboutX(float theta);
    void setToRotateAboutY(float theta);
    void setToRotateAboutZ(float theta);
    void setToRotateAboutAxis(const Vector3 &axis, float theta);

    // 构造执行 物体-惯性 旋转的四元数，方位参数用欧拉角形式给出
    void setToRotateObjectToInertial(const EulerAngles &orientation);
    void setToRotateInertialToObject(const EulerAngles &orientation);

    // 叉乘
    Quaternion operator *(const Quaternion &q) const;

    // 赋值乘法
    Quaternion &operator *=(const Quaternion &q);

    // 提取旋转角和旋转轴
    float getRotationAngle() const;
    Vector3 getRotationAxis() const;


    // 公共数据
    float w, x, y, z;
};


// 四元数共轭
Quaternion conjugate(const Quaternion &q);

// 四元数点乘
float dotProduct(const Quaternion &q1, const Quaternion &q2);

// 四元数幂
Quaternion pow(const Quaternion &q, float exponent);

// 球面线性插值
Quaternion slerp(const Quaternion &q0, const Quaternion &q1, float t);


// 全局“单位”四元数
extern const Quaternion kQuaternionIdentity;


#endif // !__QUATERNION_H_INCLUDED__
