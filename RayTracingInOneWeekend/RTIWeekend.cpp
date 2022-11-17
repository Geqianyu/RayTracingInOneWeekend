
#include "RTIWeekend.h"


double degree_to_radians(double degree)
{
    return degree * rtiw::PI / 180.0;
}

double random_double()
{
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}

double random_double(double min, double max)
{
    return min + (max - min) * random_double();
}

int random_int(int min, int max)
{
    return static_cast<int>(random_double(min, max + 1));
}

double clamp(double x, double min, double max)
{
    if (x < min) return min;
    if (x > max) return max;
    return x;
}