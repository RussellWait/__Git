#ifndef __QUATERNION_H_INCLUDED__
#define __QUATERNION_H_INCLUDED__


class Vector3;
class EulerAngles;


// 实现在3D中表示角位移的四元数
class Quaternion
{
public:
    // 置为单位四元数
    void identity();


    float w, x, y, z;
};


#endif // !__QUATERNION_H_INCLUDED__
