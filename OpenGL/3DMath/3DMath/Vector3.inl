#include <math.h>


const Vector3 kZeroVector3(0.0f, 0.0f, 0.0f);


Vector3::Vector3() {}

Vector3::Vector3(const Vector3 &v)
{
    x = v.x;
    y = v.y;
    z = v.z;
}

Vector3::Vector3(float fX, float fY, float fZ)
{
    x = fX;
    y = fY;
    z = fZ;
}

inline void Vector3::zero()
{
    x = y = z = 0.0f;
}

inline void Vector3::normalize()
{
    float magsq = x*x + y*y + z*z;
    if (magsq > 0.0f)
    {
        float oneOverMag = 1.0f / sqrt(magsq);
        x *= oneOverMag;
        y *= oneOverMag;
        z *= oneOverMag;
    }
}

inline Vector3 &Vector3::operator =(const Vector3 &v)
{
    x = v.x;
    y = v.y;
    z = v.z;

    return *this;
}

inline bool Vector3::operator ==(const Vector3 &v) const
{
    return (x == v.x) && (y == v.y) && (z == v.z);
}

inline bool Vector3::operator !=(const Vector3 &v) const
{
    return (x != v.x) || (y != v.y) || (z != v.z);
}

inline Vector3 Vector3::operator -() const
{
    return Vector3(-x, -y, -z);
}

inline Vector3 Vector3::operator +(const Vector3 &v) const
{
    return Vector3(x + v.x, y + v.y, z + v.z);
}

inline Vector3 Vector3::operator -(const Vector3 &v) const
{
    return Vector3(x - v.x, y - v.y, z - v.z);
}

inline Vector3 Vector3::operator *(float k) const
{
    return Vector3(k * x, k * y, k * z);
}

inline Vector3 Vector3::operator /(float k) const
{
    float oneOverK = 1.0f / k;
    return Vector3(oneOverK * x, oneOverK * y, oneOverK * z);
}

inline Vector3 &Vector3::operator +=(const Vector3 &v)
{
    x += v.x;
    y += v.y;
    z += v.z;

    return *this;
}

inline Vector3 &Vector3::operator -=(const Vector3 &v)
{
    x -= v.x;
    y -= v.y;
    z -= v.z;

    return *this;
}

inline Vector3 &Vector3::operator *=(float k)
{
    x *= k;
    y *= k;
    z *= k;

    return *this;
}

inline Vector3 &Vector3::operator /=(float k)
{
    float oneOverK = 1.0f / k;
    x *= oneOverK;
    y *= oneOverK;
    z *= oneOverK;

    return *this;
}

inline float Vector3::operator *(const Vector3 &v) const
{
    return x * v.x + y * v.y + z * v.z;
}

inline float vectorMag(const Vector3 &v)
{
    return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

inline Vector3 crossProduct(const Vector3 &v1, const Vector3 &v2)
{
    return Vector3(v1.y * v2.z - v1.z * v2.y,
                   v1.z * v2.x - v1.x * v2.z,
                   v1.x * v2.y - v1.y * v2.x);
}

inline Vector3 operator *(float k, Vector3 &v)
{
    return Vector3(k * v.x, k * v.y, k * v.z);
}

inline float distance(const Vector3 &v1, const Vector3 &v2)
{
    float dx = v1.x - v2.x;
    float dy = v1.y - v2.y;
    float dz = v1.z - v2.z;

    return sqrt(dx * dx + dy * dy + dz * dz);
}
