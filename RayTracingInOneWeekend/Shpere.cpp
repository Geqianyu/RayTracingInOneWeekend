
#include "Sphere.h"

Shpere::Shpere() : radius(0.0)
{

}

Shpere::Shpere(point centerValue, double radiusValue, std::shared_ptr<Material> material) : center(centerValue), radius(radiusValue), material_ptr(material)
{

}

Shpere::~Shpere()
{

}

bool Shpere::hit(const ray& r, double t_min, double t_max, Hit_record& rec) const
{
    vec3 oc = r.origin - center;
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
    vec3 outward_normal = (rec.p - center) / radius;
    rec.set_face_normal(r, outward_normal);
    rec.material_ptr = material_ptr;

    return true;
}