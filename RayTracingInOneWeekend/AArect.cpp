#include "AArect.h"

XY_Rect::XY_Rect()
{

}

XY_Rect::XY_Rect(double _x0, double _x1, double _y0, double _y1, double _k, std::shared_ptr<Material> mat) : x0(_x0), x1(_x1), y0(_y0), y1(_y1), k(_k), mp(mat)
{

}

XY_Rect::~XY_Rect()
{

}

bool XY_Rect::hit(const ray& r, double t_min, double t_max, Hit_record& rec) const
{
    auto t = (k - r.origin.z) / r.direction.z;
    if (t < t_min || t > t_max)
    {
        return false;
    }

    auto x = r.origin.x + t * r.direction.x;
    auto y = r.origin.y + t * r.direction.y;
    if (x < x0 || x > x1 || y < y0 || y > y1)
    {
        return false;
    }

    rec.u = (x - x0) / (x1 - x0);
    rec.v = (y - y0) / (y1 - y0);
    rec.t = t;
    auto outward_normal = vec3(0, 0, 1);
    rec.set_face_normal(r, outward_normal);
    rec.material_ptr = mp;
    rec.p = r.at(t);
    return true;
}

bool XY_Rect::bounding_box(double time0, double time1, AABB& output_box) const
{
    output_box = AABB(point(x0, y0, k - 0.0001), point(x1, y1, k + 0.0001));
    return true;
}

XZ_Rect::XZ_Rect()
{

}

XZ_Rect::XZ_Rect(double _x0, double _x1, double _z0, double _z1, double _k, std::shared_ptr<Material> mat) : x0(_x0), x1(_x1), z0(_z0), z1(_z1), k(_k), mp(mat)
{

}

bool XZ_Rect::hit(const ray& r, double t_min, double t_max, Hit_record& rec) const
{
    auto t = (k - r.origin.y) / r.direction.y;
    if (t < t_min || t > t_max)
    {
        return false;
    }

    auto x = r.origin.x + t * r.direction.x;
    auto z = r.origin.z + t * r.direction.z;
    if (x < x0 || x > x1 || z < z0 || z > z1)
    {
        return false;
    }

    rec.u = (x - x0) / (x1 - x0);
    rec.v = (z - z0) / (z1 - z0);
    rec.t = t;
    auto outward_normal = vec3(0, 1, 0);
    rec.set_face_normal(r, outward_normal);
    rec.material_ptr = mp;
    rec.p = r.at(t);
    return true;
}

bool XZ_Rect::bounding_box(double time0, double time1, AABB& output_box) const
{
    output_box = AABB(point(x0, k - 0.0001, z0), point(x1, k + 0.0001, z1));
    return true;
}

YZ_Rect::YZ_Rect()
{

}

YZ_Rect::YZ_Rect(double _y0, double _y1, double _z0, double _z1, double _k, std::shared_ptr<Material> mat) : y0(_y0), y1(_y1), z0(_z0), z1(_z1), k(_k), mp(mat)
{

}

bool YZ_Rect::hit(const ray& r, double t_min, double t_max, Hit_record& rec) const
{
    auto t = (k - r.origin.x) / r.direction.x;
    if (t < t_min || t > t_max)
    {
        return false;
    }

    auto y = r.origin.y + t * r.direction.y;
    auto z = r.origin.z + t * r.direction.z;
    if (y < y0 || y > y1 || z < z0 || z > z1)
    {
        return false;
    }

    rec.u = (y - y0) / (y1 - y0);
    rec.v = (z - z0) / (z1 - z0);
    rec.t = t;
    auto outward_normal = vec3(1, 0, 0);
    rec.set_face_normal(r, outward_normal);
    rec.material_ptr = mp;
    rec.p = r.at(t);
    return true;
}

bool YZ_Rect::bounding_box(double time0, double time1, AABB& output_box) const
{
    output_box = AABB(point(k - 0.0001, y0, z0), point(k + 0.0001, y1, z1));
    return true;
}