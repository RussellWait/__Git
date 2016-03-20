#ifndef __MATRIX4x3_H_INCLUDED__
#define __MATRIX4X3_H_INCLUDED__


class Vector3;
class EulerAngles;
class Quaternion;
class RotationMatrix;


class Matrix4x3
{
public:
    // ��Ϊ��λ����
    void identity();

    // ֱ�ӷ���ƽ�Ʋ���
    void zeroTranslation();
    void setTranslation(const Vector3 &d);
    void setupTranslation(const Vector3 &d);




    // ��������
    float m11, m12, m13;
    float m21, m22, m23;
    float m31, m32, m33;
    float tx, ty, tz;
};


#include "Matrix4x3.inl"


#endif // !__MATRIX4x3_H_INCLUDED__
