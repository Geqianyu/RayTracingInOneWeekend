
#include "Hittable.h"

void Hit_record::set_face_normal(const ray& r, const vec3& outward_normal)
{
    front_face = dot(r.direction, outward_normal) < 0;
    normal = front_face ? outward_normal : -outward_normal;
}

Translate::Translate(std::shared_ptr<Hittable> p, const vec3& displacement) : ptr(p), offset(displacement)
{

}

Translate::~Translate()
{

}

bool Translate::hit(const ray& r, double t_min, double t_max, Hit_record& rec) const
{
    ray moved_r(r.origin - offset, r.direction, r.time);
    if (!ptr->hit(moved_r, t_min, t_max, rec))
    {
        return false;
    }

    rec.p += offset;
    rec.set_face_normal(moved_r, rec.normal);

    return true;
}

bool Translate::bounding_box(double time0, double time1, AABB& output_box) const
{
    if (!ptr->bounding_box(time0, time1, output_box))
    {
        return false;
    }

    output_box = AABB(output_box.minimum + offset, output_box.maximum + offset);

    return true;
}

Rotate_y::Rotate_y(std::shared_ptr<Hittable> p, double angle) : ptr(p)
{
    auto radians = degree_to_radians(angle);
    sin_theta = std::sin(radians);
    cos_theta = std::cos(radians);
    hasbox = ptr->bounding_box(0, 1, bbox);

    point min(rtiw::infinity, rtiw::infinity, rtiw::infinity);
    point max(-rtiw::infinity, -rtiw::infinity, -rtiw::infinity);

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                auto x = i * bbox.maximum.x + (1 - i) * bbox.minimum.x;
                auto y = j * bbox.maximum.x + (1 - j) * bbox.minimum.x;
                auto z = k * bbox.maximum.x + (1 - k) * bbox.minimum.x;

                auto newx = cos_theta * x + sin_theta * z;
                auto newz = -sin_theta * x + cos_theta * z;

                vec3 tester(newx, y, newz);

                min.x = std::min(min.x, tester.x);
                min.y = std::min(min.y, tester.y);
                min.z = std::min(min.z, tester.z);
                max.x = std::max(max.x, tester.x);
                max.y = std::max(max.y, tester.y);
                max.z = std::max(max.z, tester.z);
            }
        }
    }

    bbox = AABB(min, max);
}

Rotate_y::~Rotate_y()
{

}

bool Rotate_y::hit(const ray& r, double t_min, double t_max, Hit_record& rec) const
{
    auto origin = r.origin;
    auto direction = r.direction;

    origin.x = cos_theta * r.origin.x - sin_theta * r.origin.z;
    origin.z = sin_theta * r.origin.x + cos_theta * r.origin.z;

    direction.x = cos_theta * r.direction.x - sin_theta * r.direction.z;
    direction.z = sin_theta * r.direction.x + cos_theta * r.direction.z;

    ray rotated_r(origin, direction, r.time);

    if (!ptr->hit(rotated_r, t_min, t_max, rec))
    {
        return false;
    }

    auto p = rec.p;
    auto normal = rec.normal;

    p.x = cos_theta * rec.p.x + sin_theta * rec.p.z;
    p.z = -sin_theta * rec.p.x + cos_theta * rec.p.z;

    normal.x = cos_theta * rec.normal.x + sin_theta * rec.normal.z;
    normal.x = -sin_theta * rec.normal.x + cos_theta * rec.normal.z;

    rec.p = p;
    rec.set_face_normal(rotated_r, normal);

    return true;
}

bool Rotate_y::bounding_box(double time0, double time1, AABB& output_box) const
{
    output_box = bbox;
    return hasbox;
}