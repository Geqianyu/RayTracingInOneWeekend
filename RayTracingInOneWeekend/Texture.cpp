
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
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

Image_Texture::Image_Texture() : data(nullptr), width(0), height(0), bytes_per_scanline(0)
{

}

Image_Texture::Image_Texture(const char* filename)
{
    auto components_per_pixel = bytes_per_pixel;

    data = stbi_load(filename, &width, &height, &components_per_pixel, components_per_pixel);

    if (!data)
    {
        std::cerr << "ERROR: Could not load texture image file '" << filename << "'.\n";
        width = height = 0;
    }

    bytes_per_scanline = bytes_per_pixel * width;
}

Image_Texture::~Image_Texture()
{
    delete data;
}

color Image_Texture::value(double u, double v, const point& p) const
{
    // If we have no texture data, then return solid cyan as a debugging aid.
    if (data == nullptr)
    {
        return color(0, 1, 1);
    }

    // Clamp input texture coordinates to [0,1] x [1,0]
    u = clamp(u, 0.0, 1.0);
    v = 1.0 - clamp(v, 0.0, 1.0);  // Flip V to image coordinates

    auto i = static_cast<int>(u * width);
    auto j = static_cast<int>(v * height);

    // Clamp integer mapping, since actual coordinates should be less than 1.0
    if (i >= width)  i = width - 1;
    if (j >= height) j = height - 1;

    const auto color_scale = 1.0 / 255.0;
    auto pixel = data + j * bytes_per_scanline + i * bytes_per_pixel;

    return color(color_scale * pixel[0], color_scale * pixel[1], color_scale * pixel[2]);
}