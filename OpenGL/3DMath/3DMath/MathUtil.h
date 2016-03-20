#ifndef __MATHUTIL_H_INCLUDED__
#define __MATHUTIL_H_INCLUDED__


// 定义与pi有关的常量
const float kPi = 3.14159265f;
const float k2Pi = kPi * 2.0f;
const float kPiOver2 = kPi / 2.0f;
const float k1OverPi = 1.0f / kPi;
const float k1Over2Pi = 1.0f / k2Pi;

// 将角度控制在-pi到pi区间内
float wrapPi(float theta);

// “安全”反三角函数
float safeAsin(float x);

float safeAcos(float x);

// 计算角度的sin和cos值
void sinCos(float *returnSin, float *returnCos, float theta);


#include "MathUtil.inl"


#endif // !__MATHUTIL_H_INCLUDED__
