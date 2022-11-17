#ifndef _GQY_HITTABLE_H_
#define _GQY_HITTABLE_H_

#include <memory>

#include "AABB.h"
#include "Material.h"
#include "Ray.h"

struct Hit_record
{
    point p;
    vec3 normal;
    std::shared_ptr<Material> material_ptr;
    double t;
    double u;
    double v;
    bool front_face;

    void set_face_normal(const ray& r, const vec3& outward_normal);
};

class Hittable
{
public:
    // 公有函数
    virtual bool hit(const ray& r, double t_min, double t_max, Hit_record& rec) const = 0;
    virtual bool bounding_box(double time0, double time1, AABB& output_box) const = 0;
};

#endif // !_GQY_HITTABLE_H_
