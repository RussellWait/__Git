#ifndef __QUATERNION_H_INCLUDED__
#define __QUATERNION_H_INCLUDED__


class Vector3;
class EulerAngles;


// ʵ����3D�б�ʾ��λ�Ƶ���Ԫ��
class Quaternion
{
public:
    // ��Ϊ��λ��Ԫ��
    void identity();


    float w, x, y, z;
};


#endif // !__QUATERNION_H_INCLUDED__
