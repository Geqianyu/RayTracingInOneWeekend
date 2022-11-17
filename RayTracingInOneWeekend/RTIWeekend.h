#ifndef _GQY_RAY_TRACING_IN_ONE_WEEKEND_
#define _GQY_RAY_TRACING_IN_ONE_WEEKEND_

#include <cmath>
#include <memory>
#include <limits>
#include <random>

namespace rtiw
{
    const double infinity = std::numeric_limits<double>::infinity();
    const double PI = std::asin(1.0) * 2.0;
}

double degree_to_radians(double degree);
double random_double();
double random_double(double min, double max);
int random_int(int min, int max);
double clamp(double x, double min, double max);

#endif // !_GQY_RAY_TRACING_IN_ONE_WEEKEND_
