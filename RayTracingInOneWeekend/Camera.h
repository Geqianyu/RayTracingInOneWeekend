#ifndef _GQY_CAMERA_H_
#define _GQY_CAMERA_H_

#include "Vec3.h"
#include "Ray.h"

class Camera
{
public:
    // 公有函数
    Camera();
    ~Camera();

    ray get_ray(double u, double v) const;

public:
    // 公有成员
    point origin;
    point lower_left_corner;
    vec3 horizontal;
    vec3 vertical;
};

#endif // !_GQY_CAMERA_H_
