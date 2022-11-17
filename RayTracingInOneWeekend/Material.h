#ifndef _GQY_MATERIAL_H_
#define _GQY_MATERIAL_H_

#include "Vec3.h"
#include "Ray.h"
#include "Texture.h"

struct Hit_record;

class Material
{
public:
    Material();
    ~Material();

    virtual bool scatter(const ray& r_in, const Hit_record& rec, color& attenuation, ray& scattered) const = 0;
};

class Lambertian : public Material
{
public:
    Lambertian(const color& a);
    Lambertian(std::shared_ptr<Texture> a);
    ~Lambertian();

    virtual bool scatter(const ray& r_in, const Hit_record& rec, color& attenuation, ray& scattered) const override;

public:
    std::shared_ptr<Texture> albedo;
};

class Metal : public Material
{
public:
    Metal(const color& a, double f);
    ~Metal();

    virtual bool scatter(const ray& r_in, const Hit_record& rec, color& attenuation, ray& scattered) const override;

public:
    color albedo;
    double fuzz;
};

class Dielectric : public Material
{
public:
    Dielectric(double index_of_refraction);
    ~Dielectric();

    virtual bool scatter(const ray& r_in, const Hit_record& rec, color& attenuation, ray& scattere) const override;

private:
    static double reflectance(double cosine, double ref_idx);

public:
    double ir;
};

#endif // !_GQY_MATERIAL_H_
