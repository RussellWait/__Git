#ifndef __MATHUTIL_H_INCLUDED__
#define __MATHUTIL_H_INCLUDED__


// ������pi�йصĳ���
const float kPi = 3.14159265f;
const float k2Pi = kPi * 2.0f;
const float kPiOver2 = kPi / 2.0f;
const float k1OverPi = 1.0f / kPi;
const float k1Over2Pi = 1.0f / k2Pi;

// ���Ƕȿ�����-pi��pi������
float wrapPi(float theta);

// ����ȫ�������Ǻ���
float safeAsin(float x);

float safeAcos(float x);

// ����Ƕȵ�sin��cosֵ
void sinCos(float *returnSin, float *returnCos, float theta);


#include "MathUtil.inl"


#endif // !__MATHUTIL_H_INCLUDED__
