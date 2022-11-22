#ifndef _GQY_BOX_H_
#define _GQY_BOX_H_

#include "RTIWeekend.h"
#include "AArect.h"
#include "Hittable.h"
#include "HittableList.h"

class Box : public Hittable
{
public:
    Box();
    Box(const point& p0, const point& p1, std::shared_ptr<Material> ptr);
    ~Box();

    virtual bool hit(const ray& r, double t_min, double t_max, Hit_record& rec) const override;
    virtual bool bounding_box(double time0, double time1, AABB& output_box) const override;

public:
    point box_min;
    point box_max;
    HittableList sides;
};

#endif // !_GQY_BOX_H_
