#ifndef __MATHUTIL_H_INCLUDED__
#define __MATHUTIL_H_INCLUDED__


const float kPi = 3.14159265f;
const float k2Pi = kPi * 2.0f;
const float kPiOver2 = kPi / 2.0f;
const float k1OverPi = 1.0f / kPi;
const float k1Over2Pi = 1.0f / k2Pi;


// 通过加适当的2pi倍数将角度限制在-pi到pi的区间内
float wrapPi(float theta);

// “安全”反三角函数
float safeAcos(float x);

// 计算角度的sin和cos值
// 在某些平台上，如果需要这两个值，同时计算要比分开计算快
inline void sinCos(float *returnSin, float *returnCos, float theta);


#include "MathUtil.inl"


#endif // !__MATHUTIL_H_INCLUDED__
