#ifndef _GQY_PERLIN_H_
#define _GQY_PERLIN_H_

#include "RTIWeekend.h"
#include "Vec3.h"

class Perlin
{
public:
    Perlin();
    ~Perlin();

    double noise(const point& p) const;
    double turb(const point& p, int depth = 7) const;

private:

    static int* perlin_generate_perm();
    static void permute(int* p, int n);
    static double trilinear_interp(double c[2][2][2], double u, double v, double w);
    static double perlin_interp(vec3 c[2][2][2], double u, double v, double w);

private:
    static const int point_count = 256;
    int* perm_x;
    int* perm_y;
    int* perm_z;
    vec3* ranvec;
};

#endif // !_GQY_PERLIN_H_
