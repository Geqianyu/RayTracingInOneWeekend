
#include <iostream>
#include <fstream>
#include <string>

#include "RTIWeekend.h"
#include "Color.h"
#include "HittableList.h"
#include "Sphere.h"
#include "Camera.h"
#include "Material.h"

color ray_color(const ray& r, const Hittable& world, int depth)
{
    if (depth <= 0)
    {
        return color(0.0, 0.0, 0.0);
    }
    Hit_record rec;
    if (world.hit(r, 0.001, rtiw::infinity, rec))
    {
        ray scattered;
        color attenuation;
        if (rec.material_ptr->scatter(r, rec, attenuation, scattered))
        {
            return attenuation * ray_color(scattered, world, depth - 1);
        }
        return color(0, 0, 0);
    }
    vec3 unit_direction = unit_vector(r.direction);
    auto t = 0.5 * (unit_direction.y + 1.0);
    return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

HittableList random_scene()
{
    HittableList world;

    auto ground_material = std::make_shared<Lambertian>(color(0.5, 0.5, 0.5));
    world.add(std::make_shared<Shpere>(point(0, -1000, 0), 1000, ground_material));

    for (int a = -11; a < 11; a++)
    {
        for (int b = -11; b < 11; b++)
        {
            auto choose_mat = random_double();
            point center(a + 0.9 * random_double(), 0.2, b + 0.9 * random_double());

            if ((center - point(4, 0.2, 0)).length() > 0.9)
            {
                std::shared_ptr<Material> sphere_material;

                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = color::random() * color::random();
                    sphere_material = std::make_shared<Lambertian>(albedo);
                    world.add(std::make_shared<Shpere>(center, 0.2, sphere_material));
                }
                else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = color::random(0.5, 1);
                    auto fuzz = random_double(0, 0.5);
                    sphere_material = std::make_shared<Metal>(albedo, fuzz);
                    world.add(std::make_shared<Shpere>(center, 0.2, sphere_material));
                }
                else {
                    // glass
                    sphere_material = std::make_shared<Dielectric>(1.5);
                    world.add(std::make_shared<Shpere>(center, 0.2, sphere_material));
                }
            }
        }
    }

    auto material1 = std::make_shared<Dielectric>(1.5);
    world.add(std::make_shared<Shpere>(point(0, 1, 0), 1.0, material1));

    auto material2 = std::make_shared<Lambertian>(color(0.4, 0.2, 0.1));
    world.add(std::make_shared<Shpere>(point(-4, 1, 0), 1.0, material2));

    auto material3 = std::make_shared<Metal>(color(0.7, 0.6, 0.5), 0.0);
    world.add(std::make_shared<Shpere>(point(4, 1, 0), 1.0, material3));

    return world;
}


int main()
{
    int max_depth = 50;
    const int image_width = 1200;
    const auto aspect_ratio = 3.0 / 2.0;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    int samples_per_pixel = 500;
    std::string file_name = "../result/Image.ppm";
    std::ofstream out_file(file_name);

    HittableList world = random_scene();

    point lookfrom(13, 2, 3);
    point lookat(0, 0, 0);
    vec3 vup(0, 1, 0);
    auto dist_to_focus = 10.0;
    auto aperture = 0.1;

    Camera camera(lookfrom, lookat, vup, 20, aspect_ratio, aperture, dist_to_focus);

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
                pixel_color += ray_color(r, world, max_depth);
            }
            write_color(out_file, pixel_color, samples_per_pixel);
        }
    }
    out_file.close();
    return 0;
}