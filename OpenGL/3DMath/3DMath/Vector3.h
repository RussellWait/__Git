#ifndef __VECTOR3_H_INCLUDED__
#define __VECTOR3_H_INCLUDED__

class Vector3
{
public:
    // 构造函数
    Vector3();

    Vector3(const Vector3 &v);

    Vector3(float fX, float fY, float fZ);


    // 置零
    void zero();

    // 标准化
    void normalize();


    // 重载操作符
    Vector3 &operator =(const Vector3 &v);
    
    bool operator ==(const Vector3 &v) const;
    
    bool operator !=(const Vector3 &v) const;

    Vector3 operator -() const;

    Vector3 operator +(const Vector3 &v) const;

    Vector3 operator -(const Vector3 &v) const;

    Vector3 operator *(float k) const;

    Vector3 operator /(float k) const;

    Vector3 &operator +=(const Vector3 &v);

    Vector3 &operator -=(const Vector3 &v);

    Vector3 &operator *=(float k);

    Vector3 &operator /=(float k);

    float operator *(const Vector3 &v) const;


    // 公共数据
    float x, y, z;
};


// 向量模
float vectorMag(const Vector3 &v);

// 向量叉乘
Vector3 crossProduct(const Vector3 &v1, const Vector3 &v2);

// 标量左乘
Vector3 operator *(float k, Vector3 &v);

// 计算两点间距离
float distance(const Vector3 &v1, const Vector3 &v2);


// 提供一个全局零向量
extern const Vector3 kZeroVector3;


#include "Vector3.inl"


#endif // !__VECTOR3_H_INCLUDED__
