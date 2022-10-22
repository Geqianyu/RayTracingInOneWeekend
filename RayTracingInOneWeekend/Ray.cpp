
#include "Ray.h"

ray::ray()
{

}

ray::ray(const point& originValue, const vec3& directionValue) : origin(originValue), direction(directionValue)
{

}

ray::~ray()
{

}

point ray::at(double t) const
{
    return origin + t * direction;
}