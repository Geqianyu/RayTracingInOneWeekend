
#include "Texture.h"

solid_color::solid_color()
{

}

solid_color::solid_color(color c) : color_value(c)
{

}

solid_color::solid_color(double red, double green, double blue) : solid_color(color(red, green, blue))
{

}

color solid_color::value(double u, double v, const point& p) const
{
    return color_value;
}

Checker_Texture::Checker_Texture()
{

}

Checker_Texture::Checker_Texture(std::shared_ptr<Texture> _even, std::shared_ptr<Texture> _odd) : even(_even), odd(_odd)
{

}

Checker_Texture::Checker_Texture(color c1, color c2) : even(std::make_shared<solid_color>(c1)), odd(std::make_shared<solid_color>(c2))
{

}

color Checker_Texture::value(double u, double v, const point& p) const
{
    auto sines = std::sin(10 * p.x) * std::sin(10 * p.y) * std::sin(10 * p.z);
    if (sines < 0)
    {
        return odd->value(u, v, p);
    }
    else
    {
        return even->value(u, v, p);
    }
}

Noise_Texture::Noise_Texture()
{

}

Noise_Texture::Noise_Texture(double sc) : scale(sc)
{

}

Noise_Texture::~Noise_Texture()
{

}

color Noise_Texture::value(double u, double v, const point& p) const
{
    return color(1, 1, 1) * 0.5 * (1 + sin(scale * p.z + 10 * noise.turb(p)));
}