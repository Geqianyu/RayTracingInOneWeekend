
#include "Ray.h"

ray::ray()
{

}

ray::ray(const point& originValue, const vec3& directionValue, double timeValue) : origin(originValue), direction(directionValue), time(timeValue)
{

}

ray::~ray()
{

}

point ray::at(double t) const
{
    return origin + t * direction;
}