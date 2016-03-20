#ifndef __VECTOR3_H_INCLUDED__
#define __VECTOR3_H_INCLUDED__

class Vector3
{
public:
    // ���캯��
    Vector3();

    Vector3(const Vector3 &v);

    Vector3(float fX, float fY, float fZ);


    // ����
    void zero();

    // ��׼��
    void normalize();


    // ���ز�����
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


    // ��������
    float x, y, z;
};


// ����ģ
float vectorMag(const Vector3 &v);

// �������
Vector3 crossProduct(const Vector3 &v1, const Vector3 &v2);

// �������
Vector3 operator *(float k, Vector3 &v);

// ������������
float distance(const Vector3 &v1, const Vector3 &v2);


// �ṩһ��ȫ��������
extern const Vector3 kZeroVector3;


#include "Vector3.inl"


#endif // !__VECTOR3_H_INCLUDED__
