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
    virtual color emitted(double u, double v, const point& p) const;
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

class Diffuse_Light : public Material
{
public:
    Diffuse_Light(std::shared_ptr<Texture> a);
    Diffuse_Light(color c);
    ~Diffuse_Light();

    virtual bool scatter(const ray& r_in, const Hit_record& rec, color& attenuation, ray& scattere) const override;
    virtual color emitted(double u, double v, const point& p) const override;

public:
    std::shared_ptr<Texture> emit;
};

class Isotropic : public Material
{
public:
    Isotropic(color c);
    Isotropic(std::shared_ptr<Texture> a);

    virtual bool scatter(const ray& r_in, const Hit_record& rec, color& attenuation, ray& scattered) const override;

public:
    std::shared_ptr<Texture> albedo;
};

#endif // !_GQY_MATERIAL_H_
