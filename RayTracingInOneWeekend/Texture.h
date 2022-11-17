#ifndef _GQY_TEXTURE_H_
#define _GQY_TEXTURE_H_

#include "RTIWeekend.h"
#include "Vec3.h"
#include "Perlin.h"

class Texture
{
public:
    virtual color value(double u, double v, const point& p) const = 0;
};

class solid_color : public Texture
{
public:
    solid_color();
    solid_color(color c);
    solid_color(double red, double green, double blue);

    virtual color value(double u, double v, const point& p) const override;

private:
    color color_value;
};

class Checker_Texture : public Texture
{
public:
    Checker_Texture();
    Checker_Texture(std::shared_ptr<Texture> _even, std::shared_ptr<Texture> _odd);
    Checker_Texture(color c1, color c2);

    virtual color value(double u, double v, const point& p) const override;

public:
    std::shared_ptr<Texture> odd;
    std::shared_ptr<Texture> even;
};

class Noise_Texture : public Texture
{
public:
    Noise_Texture();
    Noise_Texture(double sc);
    ~Noise_Texture();

    virtual color value(double u, double v, const point& p) const override;

public:
    Perlin noise;
    double scale;
};

#endif // !_GQY_TEXTURE_H_
