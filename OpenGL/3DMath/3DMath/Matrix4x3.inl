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
    RotationMatrix orientMatrix;
    orientMatrix.setup(orient);

    setupLocalToParent(pos, orientMatrix);
}

inline void Matrix4x3::setupLocalToParent(const Vector3 &pos, const RotationMatrix &orient)
{
    // ���ƾ������ת����
    // RotationMatrix.inl �е���ת����Ϊ ����->���壨��->�ֲ�����������Ҫת��
    m11 = orient.m11; m12 = orient.m21; m13 = orient.m31;
    m21 = orient.m12; m22 = orient.m22; m23 = orient.m32;
    m31 = orient.m13; m32 = orient.m23; m33 = orient.m33;

    // ƽ�Ʋ���
    tx = pos.x; ty = pos.y; tz = pos.z;
}

inline void Matrix4x3::setupParentToLocal(const Vector3 &pos, const EulerAngles &orient)
{
    RotationMatrix orientMatrix;
    orientMatrix.setup(orient);

    setupParentToLocal(pos, orientMatrix);
}

inline void Matrix4x3::setupParentToLocal(const Vector3 &pos, const RotationMatrix &orient)
{
    // ��ת����
    m11 = orient.m11; m12 = orient.m12; m13 = orient.m13;
    m21 = orient.m21; m22 = orient.m22; m23 = orient.m23;
    m31 = orient.m31; m32 = orient.m32; m33 = orient.m33;

    // ƽ�Ʋ���
    // һ����˵��������ռ䵽���Կռ�ֻ��Ҫƽ�Ƹ���������
    // ��������תʱ�ȷ����ģ�����������Ҫ��תƽ�Ʋ���
    // ����ȴ���ƽ�� -pos�ľ���T���ڴ�����ת����R���ٰ��������ӳ�TR��һ����
    tx = -(pos.x * m11 + pos.y * m21 + pos.z * m31);
    ty = -(pos.x * m12 + pos.y * m22 + pos.z * m32);
    tz = -(pos.x * m13 + pos.y * m23 + pos.z * m33);
}

// axis 1����x�ᣬ2����y�ᣬ3����z��
inline void Matrix4x3::setupRotate(int axis, float theta)
{
    // ��ȡ��ת�ǵ�sin��cosֵ
    float s, c;
    sinCos(&s, &c, theta);

    // �ж���ת��
    switch ( axis )
    {
        case  1:
        {
            m11 = 1.0f; m12 = 0.0f; m13 = 0.0f;
            m21 = 0.0f; m22 = c;    m23 = s;
            m31 = 0.0f; m32 = -s;   m33 = c;
        } break;

        case 2:
        {
            m11 = c;    m12 = 0.0f; m13 = -s;
            m21 = 0.0f; m22 = 1.0f; m23 = 0.0f;
            m31 = s;    m32 = 0.0f; m33 = c;
        } break;

        case 3:
        {
            m11 = c;    m12 = s;    m13 = 0.0f;
            m21 = -s;   m22 = c;    m23 = 0.0f;
            m31 = 0.0f; m32 = 0.0f; m33 = 1.0f;
        } break;

        default:
            assert(false);
    }

    tx = ty = tz = 0.0f;
}

inline void Matrix4x3::setupRotate(const Vector3 &axis, float theta)
{
    // �����ת���Ƿ�Ϊ��λ����
    assert(fabs(axis * axis - 1.0f) < 0.01);

    // ȡ����ת�ǵ�sin��cosֵ
    float s, c;
    sinCos(&s, &c, theta);

    // ����һЩ���õı��ʽ
    float a = 1.0f - c;
    float ax = a * axis.x;
    float ay = a * axis.y;
    float az = a * axis.z;

    // ����Ԫ�صĸ�ֵ
    m11 = ax * axis.x + c;
    m12 = ax * axis.y + axis.z * s;
    m13 = ax * axis.z - axis.y * s;

    m21 = ay * axis.x - axis.z * s;
    m22 = ay * axis.y + c;
    m23 = ay * axis.z + axis.x * s;

    m31 = az * axis.x + axis.y * s;
    m32 = az * axis.y - axis.x * s;
    m33 = az * axis.z + c;

    // ƽ�Ʋ���
    tx = ty = tz = 0.0f;
}

inline void Matrix4x3::fromQuaternion(const Quaternion &q)
{
	// ����һЩ���õ��ӱ��ʽ
	float ww = 2.0f * q.w;
	float xx = 2.0f * q.x;
	float yy = 2.0f * q.y;
	float zz = 2.0f * q.z;

	// ����Ԫ�صĸ�ֵ
	m11 = 1.0f - yy * q.y - zz * q.z;
	m12 = xx * q.y + ww * q.z;
	m13 = xx * q.z - ww * q.x;

	m21 = xx * q.y - ww * q.z;
	m22 = 1.0f - xx * q.x - zz * q.z;
	m23 = yy * q.z + ww *q.x;

	m31 = xx * q.z + ww * q.y;
	m32 = yy * q.z - ww * q.x;
	m33 = 1.0f - xx * q.x - yy * q.y;

	// ƽ�Ʋ���
	tx = ty = tz = 0.0f;
}

inline void Matrix4x3::setupScale(const Vector3 &s)
{
	m11 = s.x;	m12 = 0.0f;	m13 = 0.0f;
	m21 = 0.0f; m22 = s.y;	m23 = 0.0f;
	m31 = 0.0f; m32 = 0.0f; m33 = s.z;

	tx = ty = tz = 0.0f;
}

// �����ⷽ�����ţ�������ŷ�����һ������ԭ���ƽ����
inline void Matrix4x3::setupScaleAlongAxis(const Vector3 &axis, float k)
{
	float a = k - 1.0f;
	float ax = a * axis.x;
	float ay = a * axis.y;
	float az = a * axis.z;

	m11 = ax * axis.x + 1.0f;
	m22 = ay * axis.y + 1.0f;
	m33 = az * axis.z + 1.0f;

	m12 = m21 = ax * axis.y;
	m13 = m31 = ax * axis.z;
	m23 = m32 = ay * axis.z;

	tx = ty = tz = 0.0f;
}

inline void Matrix4x3::setupShear(int axis, float s, float t)
{
	switch ( axis )
	{
		case 1:
		{
				  m11 = 1.0f; m12 = s; m13 = t;
				  m21 = 0.0f; m22 = 1.0f; m23 = 0.0f;
				  m31 = 0.0f; m32 = 0.0f; m33 = 1.0f;
		} break;

		case 2:
		{
				  m11 = 1.0f; m12 = 0.0f; m13 = 0.0f;
				  m21 = s; m22 = 1.0f; m23 = t;
				  m31 = 0.0f; m32 = 0.0f; m33 = 1.0f;
		} break;

		case 3:
		{
				  m11 = 1.0f; m12 = 0.0f; m13 = 0.0f;
				  m21 = 0.0f; m22 = 1.0f; m23 = 0.0f;
				  m31 = s; m32 = t; m33 = 1.0f;
		} break;

		default:
			assert(false);
	}

	tx = ty = tz = 0.0f;
}

inline void Matrix4x3::setupProject(const Vector3 &n)
{
	// ���ѡ���Ƿ�Ϊ��λ����
	assert(fabs(n * n - 1.0f) < 0.01f);

	m11 = 1.0f - n.x * n.x;
	m22 = 1.0f - n.y * n.y;
	m33 = 1.0f - n.z * n.z;

	m12 = m21 = -n.x * n.y;
	m13 = m31 = -n.x * n.z;
	m23 = m32 = -n.y * n.z;

	tx = ty = tz = 0.0f;
}

inline void Matrix4x3::setupReflect(int axis, float k /* = 0.0f */)
{
	switch ( axis )
	{

		default:
			assert(false);
	}
}

inline void Matrix4x3::setupReflect(const Vector3 &n)
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
