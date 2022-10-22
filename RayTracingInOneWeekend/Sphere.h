#ifndef _GQY_SHPERE_H_
#define _GQY_SHPERE_H_

#include "Hittable.h"
#include "Vec3.h"

class Shpere : public Hittable
{
public:
    // ���к���
    Shpere();
    Shpere(point centerValue, double radiusValue);
    ~Shpere();

    virtual bool hit(const ray& r, double t_min, double t_max, Hit_record& rec) const override;

public:
    // ���б���
    point center;
    double radius;
};

#endif // !_GQY_SHPERE_H_
