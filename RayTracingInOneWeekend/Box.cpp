
#include "Box.h"

Box::Box()
{

}

Box::Box(const point& p0, const point& p1, std::shared_ptr<Material> ptr)
{
    box_min = p0;
    box_max = p1;

    sides.add(std::make_shared<XY_Rect>(p0.x, p1.x, p0.y, p1.y, p1.z, ptr));
    sides.add(std::make_shared<XY_Rect>(p0.x, p1.x, p0.y, p1.y, p0.z, ptr));

    sides.add(std::make_shared<XZ_Rect>(p0.x, p1.x, p0.z, p1.z, p1.y, ptr));
    sides.add(std::make_shared<XZ_Rect>(p0.x, p1.x, p0.z, p1.z, p0.y, ptr));

    sides.add(std::make_shared<YZ_Rect>(p0.y, p1.y, p0.z, p1.z, p1.x, ptr));
    sides.add(std::make_shared<YZ_Rect>(p0.y, p1.y, p0.z, p1.z, p0.x, ptr));
}

Box::~Box()
{

}

bool Box::hit(const ray& r, double t_min, double t_max, Hit_record& rec) const
{
    return sides.hit(r, t_min, t_max, rec);
}

bool Box::bounding_box(double time0, double time1, AABB& output_box) const
{
    output_box = AABB(box_min, box_max);
    return true;
}