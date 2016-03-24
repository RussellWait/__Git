#ifndef __MATRIX4x3_H_INCLUDED__
#define __MATRIX4X3_H_INCLUDED__


class Vector3;
class EulerAngles;
class Quaternion;
class RotationMatrix;


// 假设矩阵最后一行为 [0.0f, 0.0f, 0.0f, 1.0f]的转置
class Matrix4x3
{
public:
    // 置为单位矩阵
    void identity();

    // 直接访问平移部分
    void zeroTranslation();
    void setTranslation(const Vector3 &d);
    void setupTranslation(const Vector3 &d);

	// 构造执行父空间<->局部空间的矩阵
	// 假定局部空间在指定的位置何方位，该位可能是使用欧拉角或旋转矩阵表示的
	void setupLocalToParent(const Vector3 &pos, const EulerAngles &orient);
	void setupLocalToParent(const Vector3 &pos, const RotationMatrix &orient);
	void setupParentToLocal(const Vector3 &pos, const EulerAngles &orient);
	void setupParentToLocal(const Vector3 &pos, const RotationMatrix &orient);

	// 构造绕坐标轴旋转的矩阵（axis 1代表x轴，2代表y轴，3代表z轴）
	void setupRotate(int axis, float theta);

	// 构造绕任意轴旋转的矩阵
	void setupRotate(const Vector3 &axis, float theta);

	// 构造旋转矩阵，角位移由四元数形式给出
	void fromQuaternion(const Quaternion &q);

	// 构造沿坐标缩放的矩阵
	void setupScale(const Vector3 &s);

	// 构造沿任意轴缩放的矩阵
	void setupScaleAlongAxis(const Vector3 &axis, float k);

	// 构造切变矩阵
	void setupShear(int axis, float s, float t);

	// 构造投影矩阵，投影平面过原点
	void setupProject(const Vector3 &n);

	// 构造反射矩阵
	void setupReflect(int axis, float k = 0.0f);

	// 构造沿任意平面反射的矩阵
	void setupReflect(const Vector3 &n);


    // 公共属性
    float m11, m12, m13;
    float m21, m22, m23;
    float m31, m32, m33;
    float tx, ty, tz;
};


// 运算符* 用来变换点或连接矩阵，乘法的顺序从左向右沿变换的顺序进行
Vector3 operator *(const Vector3 &p, const Matrix4x3 &m);
Matrix4x3 operator *(const Matrix4x3 &a, const Matrix4x3 &b);

// 运算符 *=
Vector3 &operator *=(Vector3 &p, const Matrix4x3 &m);
Matrix4x3 &operator *=(Matrix4x3 &a, const Matrix4x3 &b);

// 计算3x3部分的行列式值
float determinant(const Matrix4x3 &m);

// 计算矩阵的逆
Matrix4x3 inverse(const Matrix4x3 &m);

// 提取矩阵的平移部分
Vector3 getTranslation(const Matrix4x3 &m);

// 从父矩阵<->父局部阵取位置/方位
Vector3 getPositionFromParentToLocalMatrix(const Matrix4x3 &m);
Vector3 getPositionFromLocalToParentMatrix(const Matrix4x3 &m);


#include "Matrix4x3.inl"


#endif // !__MATRIX4x3_H_INCLUDED__
