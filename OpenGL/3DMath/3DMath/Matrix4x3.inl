#include <assert.h>
#include <math.h>

#include "MathUtil.h"
#include "Vector3.h"
#include "EulerAngles.h"
#include "Quaternion.h"
#include "RotationMatrix.h"


// ��Ϊ��λ����
inline void Matrix4x3::identity()
{
    m11 = 1.0f; m12 = 0.0f; m13 = 0.0f;
    m21 = 0.0f; m22 = 1.0f; m23 = 0.0f;
    m31 = 0.0f; m32 = 0.0f; m33 = 1.0f;
    tx = 0.0f; ty = 0.0f; tz = 1.0f;
}

// �����һ����Ϊ [0.0f, 0.0f, 0.0f] ��ȡ�������ƽ�Ʋ��֣����Ա任���ֲ���Ӱ��
inline void Matrix4x3::zeroTranslation()
{
    tx = ty = tz = 0.0f;
}

// ������ƽ�Ʋ�����Ϊָ��ֵ�����ı����Ա任����
inline void Matrix4x3::setTranslation(const Vector3 &d)
{
    tx = d.x;
    ty = d.y;
    tz = d.z;
}

// ������ƽ�Ʋ�����Ϊָ��ֵ�����Ա任������Ϊ��λ����
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

// axis 1����x�ᣬ2����y�ᣬ3����z��
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

// �����ⷽ�����ţ�������ŷ�����һ������ԭ���ƽ����
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

// �����������ʽ��Ĭ�����һ��Ϊ [0.0f, 0.0f, 0.0f, 1.0f]��ת��
inline float determinant(const Matrix4x3 &m)
{

}

// ���������棬Ĭ�����һ��Ϊ [0.0f, 0.0f, 0.0f, 1.0f]��ת��
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
