#ifndef _GQY_RAY_H_
#define _GQY_RAY_H_

#include "Vec3.h"

class ray
{
public:
    // 公有函数
    ray();
    ray(const point& originValue, const vec3& directionValue, double timeValue = 0.0);
    ~ray();

    point at(double t) const;

public:
    // 公有变量
    point origin;
    vec3 direction;
    double time;
};

#endif // !_GQY_RAY_H_