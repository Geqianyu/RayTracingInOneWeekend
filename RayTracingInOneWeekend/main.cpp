
#include <iostream>
#include <fstream>
#include <string>

#include "RTIWeekend.h"
#include "Color.h"
#include "HittableList.h"
#include "Sphere.h"
#include "Camera.h"

color ray_color(const ray& r, const Hittable& world)
{
    Hit_record rec;
    if (world.hit(r, 0, rtiw::infinity, rec))
    {
        return 0.5 * (rec.normal + color(1, 1, 1));
    }
    vec3 unit_direction = unit_vector(r.direction);
    auto t = 0.5 * (unit_direction.y + 1.0);
    return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

int main()
{
    const int image_width = 400;
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    int samples_per_pixel = 100;
    std::string file_name = "../result/Image.ppm";
    std::ofstream out_file(file_name);

    HittableList world;
    world.add(std::make_shared<Shpere>(point(0, 0, -1), 0.5));
    world.add(std::make_shared<Shpere>(point(0, -100.5, -1), 100));

    auto viewport_height = 2.0;
    auto viewport_width = aspect_ratio * viewport_height;
    auto focal_length = 1.0;

    Camera camera;

    out_file << "P3\n" << image_width << " " << image_height << " \n255\n";
    for (int j = image_height - 1; j >= 0; --j)
    {
        for (int i = 0; i < image_width; ++i)
        {
            color pixel_color(0, 0, 0);
            for (int s = 0; s < samples_per_pixel; ++s)
            {
                auto u = (i + random_double()) / (image_width - 1);
                auto v = (j + random_double()) / (image_height - 1);
                ray r = camera.get_ray(u, v);
                pixel_color += ray_color(r, world);
            }
            write_color(out_file, pixel_color, samples_per_pixel);
        }
    }
    return 0;
}