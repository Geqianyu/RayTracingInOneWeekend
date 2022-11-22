#ifndef _GQY_CONSTANT_MEDIUM_H_
#define _GQY_CONSTANT_MEDIUM_H_

#include "RTIWeekend.h"
#include "Vec3.h"
#include "Hittable.h"
#include "Material.h"
#include "Texture.h"

class Constant_Medium : public Hittable
{
public:
    Constant_Medium(std::shared_ptr<Hittable> b, double d, std::shared_ptr<Texture> a);
    Constant_Medium(std::shared_ptr<Hittable> b, double d, color c);
    ~Constant_Medium();

    virtual bool hit(const ray& r, double t_min, double t_max, Hit_record& rec) const override;
    virtual bool bounding_box(double time0, double time1, AABB& output_box) const override;

public:
    std::shared_ptr<Hittable> boundary;
    std::shared_ptr<Material> phase_function;
    double neg_inv_density;
};

#endif // !_GQY_CONSTANT_MEDIUM_H_
