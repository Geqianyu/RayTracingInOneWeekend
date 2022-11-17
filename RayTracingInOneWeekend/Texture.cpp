
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