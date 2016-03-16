#include <math.h>


inline float wrapPi(float theta)
{
	theta += kPi;
	theta -= floor(theta * k1Over2Pi) * k2Pi;
	theta -= kPi;

	return theta;
}

inline float safeAcos(float x)
{
	if (x <= -1.0f)
	{
		return kPi;
	}
	else if (x >= 1.0f)
	{
		return 0.0f;
	}
	else
	{
		return acos(x);
	}
}

inline void sinCos(float *returnSin, float *returnCos, float theta)
{
	// 为了简单，我们直接使用标准三角函数
	// 注意在某些平台上可以做的更好一些
	*returnSin = sin(theta);
	*returnCos = cos(theta);
}
