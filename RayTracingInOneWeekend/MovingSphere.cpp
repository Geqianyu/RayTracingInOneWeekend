
#include "MovingSphere.h"

MovingSphere::MovingSphere() : time0(0.0), time1(0.0), radius(0.0)
{

}

MovingSphere::MovingSphere(point cen0, point cen1, double _time0, double _time1, double _radius, std::shared_ptr<Material> _material) : center0(cen0), center1(cen1), time0(_time0), time1(_time1), radius(_radius), mat_ptr(_material)
{

}

MovingSphere::~MovingSphere()
{

}

bool MovingSphere::hit(const ray& r, double t_min, double t_max, Hit_record& rec) const
{
    vec3 oc = r.origin - center(r.time);
    auto a = r.direction.length_squared();
    auto half_b = dot(oc, r.direction);
    auto c = oc.length_squared() - radius * radius;

    auto discriminant = half_b * half_b - a * c;
    if (discriminant < 0)
    {
        return false;
    }
    auto sqrtd = sqrt(discriminant);

    auto root = (-half_b - sqrtd) / a;
    if (root < t_min || t_max < root)
    {
        root = (-half_b + sqrtd) / a;
        if (root < t_min || t_max < root)
        {
            return false;
        }
    }

    rec.t = root;
    rec.p = r.at(rec.t);
    auto outward_normal = (rec.p - center(r.time)) / radius;
    rec.set_face_normal(r, outward_normal);
    rec.material_ptr = mat_ptr;

    return true;
}

bool MovingSphere::bounding_box(double time0, double time1, AABB& output_box) const
{
    AABB box0(center(time0) - vec3(radius, radius, radius), center(time0) + vec3(radius, radius, radius));
    AABB box1(center(time1) - vec3(radius, radius, radius), center(time1) + vec3(radius, radius, radius));
    output_box = surrounding_box(box0, box1);
    return true;
}

point MovingSphere::center(double time) const
{
    return center0 + ((time - time0) / (time1 - time0)) * (center1 - center0);
}