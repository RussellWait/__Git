#include <assert.h>
#include <math.h>

#include "MathUtil.h"
#include "Vector3.h"
#include "EulerAngles.h"
#include "Quaternion.h"
#include "RotationMatrix.h"


// 置为单位矩阵
inline void Matrix4x3::identity()
{
    m11 = 1.0f; m12 = 0.0f; m13 = 0.0f;
    m21 = 0.0f; m22 = 1.0f; m23 = 0.0f;
    m31 = 0.0f; m32 = 0.0f; m33 = 1.0f;
    tx = 0.0f; ty = 0.0f; tz = 1.0f;
}

// 将最后一行设为 [0.0f, 0.0f, 0.0f] 来取消矩阵的平移部分，线性变换部分不收影响
inline void Matrix4x3::zeroTranslation()
{
    tx = ty = tz = 0.0f;
}

// 将矩阵平移部分设为指定值，不改变线性变换部分
inline void Matrix4x3::setTranslation(const Vector3 &d)
{
    tx = d.x;
    ty = d.y;
    tz = d.z;
}

// 将矩阵平移部分设为指定值，线性变换部分设为单位矩阵
inline void Matrix4x3::setupTranslation(const Vector3 &d)
{
    m11 = 1.0f; m12 = 0.0f; m13 = 0.0f;
    m21 = 0.0f; m22 = 1.0f; m23 = 0.0f;
    m31 = 0.0f; m32 = 0.0f; m33 = 1.0f;
    tx = d.x; ty = d.y; tz = d.z;
}

inline void Matrix4x3::setupLocalToParent(const Vector3 &pos, const EulerAngles &orient)
{

}

inline void Matrix4x3::setupLocalToParent(const Vector3 &pos, const RotationMatrix &orient)
{

}

inline void Matrix4x3::setupParentToLocal(const Vector3 &pos, const EulerAngles &orient)
{

}

inline void Matrix4x3::setupParentToLocal(const Vector3 &pos, const RotationMatrix &orient)
{

}

// axis 1代表x轴，2代表y轴，3代表z轴
inline void Matrix4x3::setupRotate(int axis, float theta)
{

}

inline void Matrix4x3::setupRotate(const Vector3 &axis, float theta)
{

}

inline void Matrix4x3::fromQuaternion(const Quaternion &q)
{

}

inline void Matrix4x3::setupScale(const Vector3 &s)
{

}

// 沿任意方向缩放，这个缩放发生在一个穿过原点的平面上
inline void Matrix4x3::setupScaleAlongAxis(const Vector3 &axis, float k)
{

}

inline void Matrix4x3::setupShear(int axis, float s, float t)
{

}

inline void Matrix4x3::setupProject(const Vector3 &v)
{

}

inline void Matrix4x3::setupReflect(int axis, float k /* = 0.0f */)
{

}

inline void Matrix4x3::setupReflect(const Vector3 &v)
{

}

inline Vector3 operator *(const Vector3 &p, const Matrix4x3 &m)
{

}

inline Matrix4x3 operator *(const Matrix4x3 &a, const Matrix4x3 &b)
{

}

inline Vector3 &operator *=(Vector3 &p, const Matrix4x3 &m)
{

}

inline Matrix4x3 &operator *=(const Matrix4x3 &a, Matrix4x3 &b)
{

}

// 计算矩阵行列式，默认最后一行为 [0.0f, 0.0f, 0.0f, 1.0f]的转置
inline float determinant(const Matrix4x3 &m)
{

}

// 计算矩阵的逆，默认最后一列为 [0.0f, 0.0f, 0.0f, 1.0f]的转置
inline Matrix4x3 inverse(const Matrix4x3 &m)
{

}

inline Vector3 getTranslation(const Matrix4x3 &m)
{

}

inline Vector3 getPositionFromParentToLocalMatrix(const Matrix4x3 &m)
{

}

inline Vector3 getPositionFromLocalToParentMatrix(const Matrix4x3 &m)
{

}
