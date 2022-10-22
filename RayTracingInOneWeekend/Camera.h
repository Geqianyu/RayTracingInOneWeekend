#ifndef _GQY_CAMERA_H_
#define _GQY_CAMERA_H_

#include "Vec3.h"
#include "Ray.h"

class Camera
{
public:
    // ���к���
    Camera();
    ~Camera();

    ray get_ray(double u, double v) const;

public:
    // ���г�Ա
    point origin;
    point lower_left_corner;
    vec3 horizontal;
    vec3 vertical;
};

#endif // !_GQY_CAMERA_H_
