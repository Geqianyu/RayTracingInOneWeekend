#ifndef _GQY_AABB_H_
#define _GQY_AABB_H_

#include "RTIWeekend.h"
#include "Vec3.h"
#include "Ray.h"

class AABB
{
public:
    AABB();
    AABB(const point& minimumValue, const point& maximumValue);
    ~AABB();

    // bool hit(const ray& r, double t_min, double t_max) const;
    inline bool hit(const ray& r, double t_min, double t_max) const
    {
        auto invDx = 1.0f / r.direction.x;
        auto tx0 = (minimum.x - r.origin.x) * invDx;
        auto tx1 = (maximum.x - r.origin.x) * invDx;
        if (invDx < 0.0)
        {
            std::swap(tx0, tx1);
        }
        t_min = tx0 > t_min ? tx0 : t_min;
        t_max = tx1 < t_max ? tx1 : t_max;
        if (t_max <= t_min)
        {
            return false;
        }
        auto invDy = 1.0f / r.direction.y;
        auto ty0 = (minimum.y - r.origin.y) * invDy;
        auto ty1 = (maximum.y - r.origin.y) * invDy;
        if (invDy < 0.0)
        {
            std::swap(ty0, ty1);
        }
        t_min = ty0 > t_min ? ty0 : t_min;
        t_max = ty1 < t_max ? ty1 : t_max;
        if (t_max <= t_min)
        {
            return false;
        }
        auto invDz = 1.0f / r.direction.z;
        auto tz0 = (minimum.z - r.origin.z) * invDz;
        auto tz1 = (maximum.z - r.origin.z) * invDz;
        if (invDz < 0.0)
        {
            std::swap(tz0, tz1);
        }
        t_min = tz0 > t_min ? tz0 : t_min;
        t_max = tz1 < t_max ? tz1 : t_max;
        if (t_max <= t_min)
        {
            return false;
        }
        return true;
    }

public:
    point minimum;
    point maximum;
};

AABB surrounding_box(AABB box0, AABB box1);

#endif // !_GQY_AABB_H_
