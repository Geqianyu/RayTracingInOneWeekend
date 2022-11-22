
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
#include "AArect.h"
#include "Box.h"
#include "Constant_Medium.h"
#include "BVH.h"

color ray_color(const ray& r, const color& background, const Hittable& world, int depth)
{
    if (depth <= 0)
    {
        return color(0.0, 0.0, 0.0);
    }

    Hit_record rec;
    if (!world.hit(r, 0.001, rtiw::infinity, rec))
    {
        return background;
    }

    ray scattered;
    color attenuation;
    color emitted = rec.material_ptr->emitted(rec.u, rec.v, rec.p);

    if (!rec.material_ptr->scatter(r, rec, attenuation, scattered))
    {
        return emitted;
    }
    return emitted + attenuation * ray_color(scattered, background, world, depth - 1);
}

HittableList final_scene()
{
    HittableList boxes1;
    auto ground = std::make_shared<Lambertian>(color(0.48, 0.83, 0.53));

    const int boxes_per_side = 20;
    for (int i = 0; i < boxes_per_side; i++)
    {
        for (int j = 0; j < boxes_per_side; j++)
        {
            auto w = 100.0;
            auto x0 = -1000.0 + i * w;
            auto z0 = -1000.0 + j * w;
            auto y0 = 0.0;
            auto x1 = x0 + w;
            auto y1 = random_double(1, 101);
            auto z1 = z0 + w;

            boxes1.add(std::make_shared<Box>(point(x0, y0, z0), point(x1, y1, z1), ground));
        }
    }

    HittableList objects;

    objects.add(std::make_shared<BVH_Node>(boxes1, 0, 1));

    auto light = std::make_shared<Diffuse_Light>(color(7, 7, 7));
    objects.add(std::make_shared<XZ_Rect>(123, 423, 147, 412, 554, light));

    auto center1 = point(400, 400, 200);
    auto center2 = center1 + vec3(30, 0, 0);
    auto moving_sphere_material = std::make_shared<Lambertian>(color(0.7, 0.3, 0.1));
    objects.add(std::make_shared<MovingSphere>(center1, center2, 0, 1, 50, moving_sphere_material));

    objects.add(std::make_shared<Shpere>(point(260, 150, 45), 50, std::make_shared<Dielectric>(1.5)));
    objects.add(std::make_shared<Shpere>(point(0, 150, 145), 50, std::make_shared<Metal>(color(0.8, 0.8, 0.9), 1.0)));

    auto boundary = std::make_shared<Shpere>(point(360, 150, 145), 70, std::make_shared<Dielectric>(1.5));
    objects.add(boundary);
    objects.add(std::make_shared<Constant_Medium>(boundary, 0.2, color(0.2, 0.4, 0.9)));
    boundary = std::make_shared<Shpere>(point(0, 0, 0), 5000, std::make_shared<Dielectric>(1.5));
    objects.add(std::make_shared<Constant_Medium>(boundary, .0001, color(1, 1, 1)));

    auto emat = std::make_shared<Lambertian>(std::make_shared<Image_Texture>("earthmap.jpg"));
    objects.add(std::make_shared<Shpere>(point(400, 200, 400), 100, emat));
    auto pertext = std::make_shared<Noise_Texture>(0.1);
    objects.add(std::make_shared<Shpere>(point(220, 280, 300), 80, std::make_shared<Lambertian>(pertext)));

    HittableList boxes2;
    auto white = std::make_shared<Lambertian>(color(.73, .73, .73));
    int ns = 1000;
    for (int j = 0; j < ns; j++)
    {
        boxes2.add(std::make_shared<Shpere>(point::random(0, 165), 10, white));
    }

    objects.add(std::make_shared<Translate>(std::make_shared<Rotate_y>(std::make_shared<BVH_Node>(boxes2, 0.0, 1.0), 15), vec3(-100, 270, 395)));

    return objects;
}

HittableList cornell_smoke()
{
    HittableList objects;

    auto red = std::make_shared<Lambertian>(color(.65, .05, .05));
    auto white = std::make_shared<Lambertian>(color(.73, .73, .73));
    auto green = std::make_shared<Lambertian>(color(.12, .45, .15));
    auto light = std::make_shared<Diffuse_Light>(color(7, 7, 7));

    objects.add(std::make_shared<YZ_Rect>(0, 555, 0, 555, 555, green));
    objects.add(std::make_shared<YZ_Rect>(0, 555, 0, 555, 0, red));
    objects.add(std::make_shared<XZ_Rect>(113, 443, 127, 432, 554, light));
    objects.add(std::make_shared<XZ_Rect>(0, 555, 0, 555, 555, white));
    objects.add(std::make_shared<XZ_Rect>(0, 555, 0, 555, 0, white));
    objects.add(std::make_shared<XY_Rect>(0, 555, 0, 555, 555, white));

    std::shared_ptr<Hittable> box1 = std::make_shared<Box>(point(0, 0, 0), point(165, 330, 165), white);
    box1 = std::make_shared<Rotate_y>(box1, 15);
    box1 = std::make_shared<Translate>(box1, vec3(265, 0, 295));

    std::shared_ptr<Hittable> box2 = std::make_shared<Box>(point(0, 0, 0), point(165, 165, 165), white);
    box2 = std::make_shared<Rotate_y>(box2, -18);
    box2 = std::make_shared<Translate>(box2, vec3(130, 0, 65));

    objects.add(std::make_shared<Constant_Medium>(box1, 0.01, color(0, 0, 0)));
    objects.add(std::make_shared<Constant_Medium>(box2, 0.01, color(1, 1, 1)));

    return objects;
}

HittableList cornell_box()
{
    HittableList objects;

    auto red = std::make_shared<Lambertian>(color(.65, .05, .05));
    auto white = std::make_shared<Lambertian>(color(.73, .73, .73));
    auto green = std::make_shared<Lambertian>(color(.12, .45, .15));
    auto light = std::make_shared<Diffuse_Light>(color(15, 15, 15));

    objects.add(std::make_shared<YZ_Rect>(0, 555, 0, 555, 555, green));
    objects.add(std::make_shared<YZ_Rect>(0, 555, 0, 555, 0, red));
    objects.add(std::make_shared<XZ_Rect>(213, 343, 227, 332, 554, light));
    objects.add(std::make_shared<XZ_Rect>(0, 555, 0, 555, 0, white));
    objects.add(std::make_shared<XZ_Rect>(0, 555, 0, 555, 555, white));
    objects.add(std::make_shared<XY_Rect>(0, 555, 0, 555, 555, white));

    std::shared_ptr<Hittable> box1 = std::make_shared<Box>(point(0, 0, 0), point(165, 330, 165), white);
    box1 = std::make_shared<Rotate_y>(box1, 15);
    box1 = std::make_shared<Translate>(box1, vec3(265, 0, 295));
    objects.add(box1);
    std::shared_ptr<Hittable> box2 = std::make_shared<Box>(point(0, 0, 0), point(165, 165, 165), white);
    box2 = std::make_shared<Rotate_y>(box2, -18);
    box2 = std::make_shared<Translate>(box2, vec3(130, 0, 65));
    objects.add(box2);

    return objects;
}

HittableList earth()
{
    auto earth_texture = std::make_shared<Image_Texture>("earthmap.jpg");
    auto earth_surface = std::make_shared<Lambertian>(earth_texture);
    auto globe = std::make_shared<Shpere>(point(0, 0, 0), 2, earth_surface);

    return HittableList(globe);
}

HittableList simple_light()
{
    HittableList objects;

    auto pertext = std::make_shared<Noise_Texture>(4);
    objects.add(std::make_shared<Shpere>(point(0, -1000, 0), 1000, std::make_shared<Lambertian>(pertext)));
    objects.add(std::make_shared<Shpere>(point(0, 2, 0), 2, std::make_shared<Lambertian>(pertext)));

    auto difflight = std::make_shared<Diffuse_Light>(color(4, 4, 4));
    objects.add(std::make_shared<XY_Rect>(3, 5, 1, 3, -2, difflight));

    return objects;
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
    int image_width = 400;
    auto aspect_ratio = 16.0 / 9.0;
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
    color background(0, 0, 0);

    switch (0)
    {
    case 1:
        world = random_scene();
        background = color(0.70, 0.80, 1.00);
        lookfrom = point(13, 2, 3);
        lookat = point(0, 0, 0);
        vfov = 20.0;
        aperture = 0.1;
        break;
    case 2:
        world = two_spheres();
        background = color(0.70, 0.80, 1.00);
        lookfrom = point(13, 2, 3);
        lookat = point(0, 0, 0);
        vfov = 20.0;
        break;
    case 3:
        world = two_perlin_spheres();
        background = color(0.70, 0.80, 1.00);
        lookfrom = point(13, 2, 3);
        lookat = point(0, 0, 0);
        vfov = 20.0;
        break;
    case 4:
        world = earth();
        background = color(0.70, 0.80, 1.00);
        lookfrom = point(13, 2, 3);
        lookat = point(0, 0, 0);
        vfov = 20.0;
        break;
    case 5:
        world = simple_light();
        samples_per_pixel = 400;
        background = color(0, 0, 0);
        lookfrom = point(26, 3, 6);
        lookat = point(0, 2, 0);
        vfov = 20.0;
        break;
    case 6:
        world = cornell_box();
        aspect_ratio = 1.0;
        image_width = 600;
        samples_per_pixel = 200;
        background = color(0, 0, 0);
        lookfrom = point(278, 278, -800);
        lookat = point(278, 278, 0);
        vfov = 40.0;
        break;
    case 7:
        world = cornell_smoke();
        aspect_ratio = 1.0;
        image_width = 600;
        samples_per_pixel = 200;
        lookfrom = point(278, 278, -800);
        lookat = point(278, 278, 0);
        vfov = 40.0;
        break;
    default:
    case 8:
        world = final_scene();
        aspect_ratio = 1.0;
        image_width = 800;
        samples_per_pixel = 10000;
        background = color(0, 0, 0);
        lookfrom = point(478, 278, -600);
        lookat = point(278, 278, 0);
        vfov = 40.0;
        break;
    }

    int image_height = static_cast<int>(image_width / aspect_ratio);
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
                pixel_color += ray_color(r, background, world, max_depth);
            }
            write_color(out_file, pixel_color, samples_per_pixel);
        }
    }
    out_file.close();
    return 0;
}