#include "Quaternion.h"
#include <cmath>
#include <memory.h>
#include "Matrix.h"


inline CQuaternion LERP(CQuaternion &rQuat0, CQuaternion &rQuat1, float fInterp)
{

}

inline CQuaternion SLERP(CQuaternion &rQuat0, CQuaternion &rQuat1, float fInterp)
{

}

inline CQuaternion::CQuaternion()
{

}

inline CQuaternion::CQuaternion(float fX, float fY, float fZ, float fW)
{

}

inline CQuaternion::CQuaternion(float *fpQuat)
{

}

inline CQuaternion::CQuaternion(const CQuaternion &rQuat)
{

}

inline float CQuaternion::Magnitude() const
{

}

inline void CQuaternion::Normalize()
{

}

inline float *CQuaternion::Get()
{

}

inline void CQuaternion::FromEulers(float fX, float fY, float fZ)
{

}

inline void CQuaternion::FromEulers(float *fpAngles)
{

}

inline void CQuaternion::FromMatrix(CMatrix3X3 &rMat)
{

}

inline CMatrix4X4 CQuaternion::ToMatrix4() const
{

}
