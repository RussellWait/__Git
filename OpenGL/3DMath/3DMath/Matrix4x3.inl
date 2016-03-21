#include <assert.h>
#include <math.h>

#include "MathUtil.h"
#include "Vector3.h"
#include "EulerAngles.h"
#include "Quaternion.h"
#include "RotationMatrix.h"


inline void Matrix4x3::identity()
{

}

inline void Matrix4x3::zeroTranslation()
{

}

inline void Matrix4x3::setTranslation(const Vector3 &d)
{

}

inline void Matrix4x3::setupTranslation(const Vector3 &d)
{

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

inline float determinant(const Matrix4x3 &m)
{

}

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
