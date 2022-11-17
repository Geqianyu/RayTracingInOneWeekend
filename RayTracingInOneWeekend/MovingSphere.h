#ifndef _GQY_MOVEING_SPHERE_H_
#define _GQY_MOVEING_SPHERE_H_

#include <memory>

#include "RTIWeekend.h"
#include "Vec3.h"
#include "Ray.h"
#include "Material.h"
#include "Hittable.h"

class MovingSphere : public Hittable
{
public:
    MovingSphere();
    MovingSphere(point cen0, point cen1, double _time0, double _time1, double _radius, std::shared_ptr<Material> _material);
    ~MovingSphere();

    virtual bool hit(const ray& r, double t_min, double t_max, Hit_record& rec) const override;
    virtual bool bounding_box(double time0, double time1, AABB& output_box) const override;

    point center(double time) const;

public:
    point center0, center1;
    double time0, time1;
    double radius;
    std::shared_ptr<Material> mat_ptr;
};

#endif // !_GQY_MOVEING_SPHERE_H_
