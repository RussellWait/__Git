#include <math.h>
#include <assert.h>

#include "MathUtil.h"
//#include "Vector3.h"
#include "EulerAngles.h"


const Quaternion kQuaternionIdentity = {1.0f, 0.0f, 0.0f, 0.0f};


void Quaternion::identity()
{

}

void Quaternion::setToRotateAboutX(float theta)
{

}

void Quaternion::setToRotateAboutY(float theta)
{

}

void Quaternion::setToRotateAboutZ(float theta)
{

}

void Quaternion::setToRotateAboutAxis(const Vector3 &axis, float theta)
{

}

void Quaternion::setToRotateObjectToInertial(const EulerAngles &orientation)
{

}

void Quaternion::setToRotateInertialToObject(const EulerAngles &orientation)
{

}

Quaternion Quaternion::operator*(const Quaternion &a) const
{

}

Quaternion Quaternion::operator*=(const Quaternion &a)
{

}

void Quaternion::normalize()
{

}

float Quaternion::getRotationAngle() const
{

}

Vector3 Quaternion::getRotationAxis() const
{

}


float dotProduct(const Quaternion &a, const Quaternion &b)
{

}

Quaternion slerp(const Quaternion &a, const Quaternion &b, float t)
{

}

Quaternion conjugate(const Quaternion &q)
{

}

Quaternion pow(const Quaternion &q, float exponent)
{

}
