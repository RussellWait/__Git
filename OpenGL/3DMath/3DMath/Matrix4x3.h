#ifndef __MATRIX4x3_H_INCLUDED__
#define __MATRIX4X3_H_INCLUDED__


class Vector3;
class EulerAngles;
class Quaternion;
class RotationMatrix;


// ����������һ��Ϊ [0.0f, 0.0f, 0.0f, 1.0f]��ת��
class Matrix4x3
{
public:
    // ��Ϊ��λ����
    void identity();

    // ֱ�ӷ���ƽ�Ʋ���
    void zeroTranslation();
    void setTranslation(const Vector3 &d);
    void setupTranslation(const Vector3 &d);

	// ����ִ�и��ռ�<->�ֲ��ռ�ľ���
	// �ٶ��ֲ��ռ���ָ����λ�úη�λ����λ������ʹ��ŷ���ǻ���ת�����ʾ��
	void setupLocalToParent(const Vector3 &pos, const EulerAngles &orient);
	void setupLocalToParent(const Vector3 &pos, const RotationMatrix &orient);
	void setupParentToLocal(const Vector3 &pos, const EulerAngles &orient);
	void setupParentToLocal(const Vector3 &pos, const RotationMatrix &orient);

	// ��������������ת�ľ���axis 1����x�ᣬ2����y�ᣬ3����z�ᣩ
	void setupRotate(int axis, float theta);

	// ��������������ת�ľ���
	void setupRotate(const Vector3 &axis, float theta);

	// ������ת���󣬽�λ������Ԫ����ʽ����
	void fromQuaternion(const Quaternion &q);

	// �������������ŵľ���
	void setupScale(const Vector3 &s);

	// ���������������ŵľ���
	void setupScaleAlongAxis(const Vector3 &axis, float k);

	// �����б����
	void setupShear(int axis, float s, float t);

	// ����ͶӰ����ͶӰƽ���ԭ��
	void setupProject(const Vector3 &n);

	// ���췴�����
	void setupReflect(int axis, float k = 0.0f);

	// ����������ƽ�淴��ľ���
	void setupReflect(const Vector3 &n);


    // ��������
    float m11, m12, m13;
    float m21, m22, m23;
    float m31, m32, m33;
    float tx, ty, tz;
};


// �����* �����任������Ӿ��󣬳˷���˳����������ر任��˳�����
Vector3 operator *(const Vector3 &p, const Matrix4x3 &m);
Matrix4x3 operator *(const Matrix4x3 &a, const Matrix4x3 &b);

// ����� *=
Vector3 &operator *=(Vector3 &p, const Matrix4x3 &m);
Matrix4x3 &operator *=(Matrix4x3 &a, const Matrix4x3 &b);

// ����3x3���ֵ�����ʽֵ
float determinant(const Matrix4x3 &m);

// ����������
Matrix4x3 inverse(const Matrix4x3 &m);

// ��ȡ�����ƽ�Ʋ���
Vector3 getTranslation(const Matrix4x3 &m);

// �Ӹ�����<->���ֲ���ȡλ��/��λ
Vector3 getPositionFromParentToLocalMatrix(const Matrix4x3 &m);
Vector3 getPositionFromLocalToParentMatrix(const Matrix4x3 &m);


#include "Matrix4x3.inl"


#endif // !__MATRIX4x3_H_INCLUDED__
