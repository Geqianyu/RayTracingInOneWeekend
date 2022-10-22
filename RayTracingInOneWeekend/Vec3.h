#ifndef _GQY_VEC3_H_
#define _GQY_VEC3_H_

#include <iostream>
#include <cmath>

class vec3
{
public:
    // 公有函数
    vec3();
    vec3(double valuex, double valuey, double valuez);
    ~vec3();

    vec3 operator-() const;
    vec3& operator+=(const vec3& v);
    vec3& operator*=(const double t);
    vec3& operator/=(const double t);

    double length() const;
    double length_squared() const;

public:
    // 公有变量
    double x;
    double y;
    double z;
    double& r = x;
    double& g = y;
    double& b = z;
};

std::ostream& operator<<(std::ostream& out, const vec3& v);
vec3 operator+(const vec3& u, const vec3& v);
vec3 operator-(const vec3& u, const vec3& v);
vec3 operator*(const vec3& u, const vec3& v);
vec3 operator*(double t, const vec3& v);
vec3 operator*(const vec3& v, double t);
vec3 operator/(vec3 v, double t);
double dot(const vec3& u, const vec3& v);
vec3 cross(const vec3& u, const vec3& v);
vec3 unit_vector(vec3 v);

using point = vec3;     // 3D point
using color = vec3;     // RGB color

#endif // !_GQY_VEC3_H_
