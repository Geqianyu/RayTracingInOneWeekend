#ifndef _GQY_TEXTURE_H_
#define _GQY_TEXTURE_H_

#include "RTIWeekend.h"
#include "Vec3.h"

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

    virtual color value(double u, double v, const point& p) const;

private:
    color color_value;
};

#endif // !_GQY_TEXTURE_H_
