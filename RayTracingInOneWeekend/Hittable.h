#ifndef _GQY_HITTABLE_H_
#define _GQY_HITTABLE_H_

#include "Ray.h"

struct Hit_record
{
    point p;
    vec3 normal;
    double t;
    bool front_face;

    void set_face_normal(const ray& r, const vec3& outward_normal);
};

class Hittable
{
public:
    // ¹«ÓÐº¯Êý
    virtual bool hit(const ray& r, double t_min, double t_max, Hit_record& rec) const = 0;
};

#endif // !_GQY_HITTABLE_H_
