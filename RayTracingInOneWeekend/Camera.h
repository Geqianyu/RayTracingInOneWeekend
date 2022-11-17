#ifndef _GQY_CAMERA_H_
#define _GQY_CAMERA_H_

#include "Vec3.h"
#include "Ray.h"

class Camera
{
public:
    // 公有函数
    Camera(point lookfrom, point lookat, vec3 vup, double vfov, double aspect_ratio, double aperture, double focus_dist, double time0Value = 0.0, double time1Value = 0.0);
    ~Camera();

    ray get_ray(double s, double t) const;

public:
    // 公有成员
    point origin;
    point lower_left_corner;
    vec3 horizontal;
    vec3 vertical;
    vec3 u, v, w;
    double lens_radius;
    double time0, time1;
};

#endif // !_GQY_CAMERA_H_
