
#include "AABB.h"

AABB::AABB()
{

}

AABB::AABB(const point& minimumValue, const point& maximumValue)
{
    minimum = minimumValue;
    maximum = maximumValue;
}

AABB::~AABB()
{

}

AABB surrounding_box(AABB box0, AABB box1)
{
    point small((std::min)(box0.minimum.x, box1.minimum.x), (std::min)(box0.minimum.y, box1.minimum.y), (std::min)(box0.minimum.z, box1.minimum.z));
    point big((std::max)(box0.maximum.x, box1.maximum.x), (std::max)(box0.maximum.y, box1.maximum.y), (std::max)(box0.maximum.z, box1.maximum.z));
    return AABB(small, big);
}

// bool AABB::hit(const ray& r, double t_min, double t_max) const
// {
//     auto tx0 = std::min((minimum.x - r.origin.x) / r.direction.x, (maximum.x - r.origin.x) / r.direction.x);
//     auto tx1 = std::max((minimum.x - r.origin.x) / r.direction.x, (maximum.x - r.origin.x) / r.direction.x);
//     t_min = std::max(tx0, t_min);
//     t_max = std::min(tx1, t_max);
//     if (t_max <= t_min)
//     {
//         return false;
//     }
//     auto ty0 = std::min((minimum.y - r.origin.y) / r.direction.y, (maximum.y - r.origin.y) / r.direction.y);
//     auto ty1 = std::max((minimum.y - r.origin.y) / r.direction.y, (maximum.y - r.origin.y) / r.direction.y);
//     t_min = std::max(ty0, t_min);
//     t_max = std::min(ty1, t_max);
//     if (t_max <= t_min)
//     {
//         return false;
//     }
//     auto tz0 = std::min((minimum.z - r.origin.z) / r.direction.z, (maximum.z - r.origin.z) / r.direction.z);
//     auto tz1 = std::max((minimum.z - r.origin.z) / r.direction.z, (maximum.z - r.origin.z) / r.direction.z);
//     t_min = std::max(tz0, t_min);
//     t_max = std::min(tz1, t_max);
//     if (t_max <= t_min)
//     {
//         return false;
//     }
// 
//     return true;
// }