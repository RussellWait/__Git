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
	// Ϊ�˼򵥣�����ֱ��ʹ�ñ�׼���Ǻ���
	// ע����ĳЩƽ̨�Ͽ������ĸ���һЩ
	*returnSin = sin(theta);
	*returnCos = cos(theta);
}
