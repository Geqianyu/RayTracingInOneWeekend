
#include "Constant_Medium.h"

Constant_Medium::Constant_Medium(std::shared_ptr<Hittable> b, double d, std::shared_ptr<Texture> a) : boundary(b), neg_inv_density(-1 / d), phase_function(std::make_shared<Isotropic>(a))
{

}

Constant_Medium::Constant_Medium(std::shared_ptr<Hittable> b, double d, color c) : boundary(b), neg_inv_density(-1 / d), phase_function(std::make_shared<Isotropic>(c))
{

}

Constant_Medium::~Constant_Medium()
{

}

bool Constant_Medium::hit(const ray& r, double t_min, double t_max, Hit_record& rec) const
{
    const bool enableDebug = false;
    const bool debugging = enableDebug && random_double() < 0.00001;

    Hit_record rec1, rec2;

    if (!boundary->hit(r, -rtiw::infinity, rtiw::infinity, rec1))
    {
        return false;
    }

    if (!boundary->hit(r, rec1.t + 0.0001, rtiw::infinity, rec2))
    {
        return false;
    }

    if (debugging)
    {
        std::cerr << "\nt_min=" << rec1.t << ", t_max=" << rec2.t << '\n';
    }

    if (rec1.t < t_min)
    {
        rec1.t = t_min;
    }
    if (rec2.t > t_max)
    {
        rec2.t = t_max;
    }

    if (rec1.t >= rec2.t)
    {
        return false;
    }

    if (rec1.t < 0)
    {
        rec1.t = 0;
    }

    const auto ray_length = r.direction.length();
    const auto distance_inside_boundary = (rec2.t - rec1.t) * ray_length;
    const auto hit_distance = neg_inv_density * log(random_double());

    if (hit_distance > distance_inside_boundary)
    {
        return false;
    }

    rec.t = rec1.t + hit_distance / ray_length;
    rec.p = r.at(rec.t);

    if (debugging)
    {
        std::cerr << "hit_distance = " << hit_distance << '\n' << "rec.t = " << rec.t << '\n' << "rec.p = " << rec.p << '\n';
    }

    rec.normal = vec3(1, 0, 0);
    rec.front_face = true;
    rec.material_ptr = phase_function;

    return true;
}

bool Constant_Medium::bounding_box(double time0, double time1, AABB& output_box) const
{
    return boundary->bounding_box(time0, time1, output_box);
}