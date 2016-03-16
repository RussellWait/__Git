#ifndef __EULERANGLES_H_INCLUDED__
#define __EULERANGLES_H_INCLUDED__


class Quaternion;
class Matrix4x3;
class RotationMatrix;


// �������ڱ�ʾ heading-pitch-bank ŷ����ϵͳ
class EulerAngles
{
public:
    EulerAngles() {}

    EulerAngles(float h, float p, float b) :
        heading(h), pitch(p), bank(b) {}


    // ����
    void identity();

    // �任Ϊ�����Ƽ���ŷ����
    void canonize();

    // ����Ԫ��ת����ŷ����
    void fromObjectToInertialQuaternion(const Quaternion &q);
    void fromInertialToObjectQuaternion(const Quaternion &q);

    // �Ӿ���ת����ŷ����
    // ƽ�Ʋ��ֱ�ʡ�ԣ����Ҽ��������������
    void fromObjectToWorldMatrix(const Matrix4x3 &m);
    void fromWorldToObjectMatrix(const Matrix4x3 &m);

    // ����ת����ת����ŷ����
    void fromRotationMatrix(const RotationMatrix &m);


    float heading;
    float pitch;
    float bank;
};


// ȫ�ֵġ���λ��ŷ����
extern const EulerAngles kEulerAnglesIdentity;


#include "EulerAngles.inl"


#endif // !__EULERANGLES_H_INCLUDED__
