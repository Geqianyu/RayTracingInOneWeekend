#ifndef _GQY_AARECT_H_
#define _GQY_AARECT_H_

#include "RTIWeekend.h"
#include "Vec3.h"
#include "Hittable.h"

class XY_Rect : public Hittable
{
public:
    XY_Rect();
    XY_Rect(double _x0, double _x1, double _y0, double _y1, double _k, std::shared_ptr<Material> mat);
    ~XY_Rect();

    virtual bool hit(const ray& r, double t_min, double t_max, Hit_record& rec) const override;
    virtual bool bounding_box(double time0, double time1, AABB& output_box) const override;

public:
    std::shared_ptr<Material> mp;
    double x0, x1, y0, y1, k;
};

class XZ_Rect : public Hittable
{
public:
    XZ_Rect();
    XZ_Rect(double _x0, double _x1, double _z0, double _z1, double _k, std::shared_ptr<Material> mat);

    virtual bool hit(const ray& r, double t_min, double t_max, Hit_record& rec) const override;
    virtual bool bounding_box(double time0, double time1, AABB& output_box) const override;

public:
    std::shared_ptr<Material> mp;
    double x0, x1, z0, z1, k;
};

class YZ_Rect : public Hittable
{
public:
    YZ_Rect();
    YZ_Rect(double _y0, double _y1, double _z0, double _z1, double _k, std::shared_ptr<Material> mat);

    virtual bool hit(const ray& r, double t_min, double t_max, Hit_record& rec) const override;
    virtual bool bounding_box(double time0, double time1, AABB& output_box) const override;

public:
    std::shared_ptr<Material> mp;
    double y0, y1, z0, z1, k;
};

#endif // !_GQY_AARECT_H_
