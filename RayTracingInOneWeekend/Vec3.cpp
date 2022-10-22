
#include "Vec3.h"

vec3::vec3() : x(0.0), y(0.0), z(0.0)
{

}

vec3::vec3(double valuex, double valuey, double valuez) : x(valuex), y(valuey), z(valuez)
{

}

vec3::~vec3()
{

}

vec3 vec3::operator-() const
{
    return vec3(-x, -y, -z);
}

vec3& vec3::operator+=(const vec3& v)
{
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}

vec3& vec3::operator*=(const double t)
{
    x *= t;
    y *= t;
    z *= t;
    return *this;
}

vec3& vec3::operator/=(const double t)
{
    x /= t;
    y /= t;
    z /= t;
    return *this;
}

double vec3::length() const
{
    return std::sqrt(length_squared());
}

double vec3::length_squared() const
{
    return x * x + y * y + z * z;
}

std::ostream& operator<<(std::ostream& out, const vec3& v)
{
    return out << v.x << ' ' << v.y << ' ' << v.z;
}

vec3 operator+(const vec3& u, const vec3& v)
{
    return vec3(u.x + v.x, u.y + v.y, u.z + v.z);
}

vec3 operator-(const vec3& u, const vec3& v)
{
    return vec3(u.x - v.x, u.y - v.y, u.z - v.z);
}

vec3 operator*(const vec3& u, const vec3& v)
{
    return vec3(u.x * v.x, u.y * v.y, u.z * v.z);
}

vec3 operator*(double t, const vec3& v)
{
    return vec3(t * v.x, t * v.y, t * v.z);
}

vec3 operator*(const vec3& v, double t)
{
    return t * v;
}

vec3 operator/(vec3 v, double t)
{
    return (1.0 / t) * v;
}

double dot(const vec3& u, const vec3& v)
{
    return u.x * v.x + u.y * v.y + u.z * v.z;
}

vec3 cross(const vec3& u, const vec3& v)
{
    return vec3(u.y * v.z - u.z * v.y,
        u.z * v.x - u.x * v.z,
        u.x * v.y - u.y * v.x);
}

vec3 unit_vector(vec3 v)
{
    return v / v.length();
}