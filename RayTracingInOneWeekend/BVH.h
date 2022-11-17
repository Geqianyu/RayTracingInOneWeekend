#ifndef _GQY_BVH_H_
#define _GQY_BVH_H_

#include <algorithm>

#include "RTIWeekend.h"
#include "Hittable.h"
#include "HittableList.h"

class BVH_Node : public Hittable
{
public:
    BVH_Node();
    BVH_Node(const HittableList& list, double time0, double time1);
    BVH_Node(const std::vector<std::shared_ptr<Hittable>>& src_objects, size_t start, size_t end, double time0, double time1);
    ~BVH_Node();

    virtual bool hit(const ray& r, double t_min, double t_max, Hit_record& rec) const override;
    virtual bool bounding_box(double time0, double time1, AABB& output_box) const override;

public:
    std::shared_ptr<Hittable> left;
    std::shared_ptr<Hittable> right;
    AABB box;
};

inline bool box_compare(const std::shared_ptr<Hittable> a, const std::shared_ptr<Hittable> b, int axis)
{
    AABB box_a, box_b;
    if (!a->bounding_box(0, 0, box_a) || !b->bounding_box(0, 0, box_b))
    {
        std::cerr << "No bounding box in bvh_node constructor.\n";
    }
    bool result = false;
    switch (axis)
    {
    case 0:
        result = box_a.minimum.x < box_b.minimum.x;
        break;
    case 1:
        result = box_a.minimum.y < box_b.minimum.y;
        break;
    case 2:
        result = box_a.minimum.z < box_b.minimum.z;
        break;
    default:
        break;
    }
    return result;
}

bool box_x_compare(const std::shared_ptr<Hittable> a, const std::shared_ptr<Hittable> b);
bool box_y_compare(const std::shared_ptr<Hittable> a, const std::shared_ptr<Hittable> b);
bool box_z_compare(const std::shared_ptr<Hittable> a, const std::shared_ptr<Hittable> b);

#endif // !_GQY_BVH_H_
