
#include <iostream>
#include <fstream>
#include <string>

#include "RTIWeekend.h"
#include "Color.h"
#include "HittableList.h"
#include "Sphere.h"
#include "Camera.h"
#include "Material.h"
#include "MovingSphere.h"

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

HittableList two_perlin_spheres()
{
    HittableList objects;
    auto pertext = std::make_shared<Noise_Texture>(4);

    objects.add(std::make_shared<Shpere>(point(0, -1000, 0), 1000, std::make_shared<Lambertian>(pertext)));
    objects.add(std::make_shared<Shpere>(point(0, 2, 0), 2, std::make_shared<Lambertian>(pertext)));

    return objects;
}

HittableList two_spheres()
{
    HittableList objects;
    auto checker = std::make_shared<Checker_Texture>(color(0.2, 0.3, 0.1), color(0.9, 0.9, 0.9));

    objects.add(std::make_shared<Shpere>(point(0, -10, 0), 10, std::make_shared<Lambertian>(checker)));
    objects.add(std::make_shared<Shpere>(point(0, 10, 0), 10, std::make_shared<Lambertian>(checker)));

    return objects;
}

HittableList random_scene()
{
    HittableList world;

    auto checker = std::make_shared<Checker_Texture>(color(0.2, 0.3, 0.1), color(0.9, 0.9, 0.9));
    auto ground_material = std::make_shared<Lambertian>(checker);
    world.add(std::make_shared<Shpere>(point(0, -1000, 0), 1000, std::make_shared<Lambertian>(checker)));

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
                    auto center2 = center + vec3(0, random_double(0, 0.5), 0);
                    world.add(std::make_shared<MovingSphere>(center, center2, 0.0, 1.0, 0.2, sphere_material));
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
    const int image_width = 400;
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    int samples_per_pixel = 100;
    std::string file_name = "../result/Moving_Sphere.ppm";
    std::ofstream out_file(file_name);

    HittableList world;

    point lookfrom;
    point lookat;
    vec3 vup(0, 1, 0);
    auto dist_to_focus = 10.0;
    auto vfov = 20.0;
    auto aperture = 0.0;

    switch (0)
    {
    case 1:
        world = random_scene();
        lookfrom = point(13, 2, 3);
        lookat = point(0, 0, 0);
        vfov = 20.0;
        aperture = 0.1;
        break;
    case 2:
        world = two_spheres();
        lookfrom = point(13, 2, 3);
        lookat = point(0, 0, 0);
        vfov = 20.0;
        break;
    default:
    case 3:
        world = two_perlin_spheres();
        lookfrom = point(13, 2, 3);
        lookat = point(0, 0, 0);
        vfov = 20.0;
        break;
    }

    Camera camera(lookfrom, lookat, vup, vfov, aspect_ratio, aperture, dist_to_focus, 0.0, 1.0);

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