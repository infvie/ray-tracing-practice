#include <iostream>
#include <fstream>

#include "utils.h"
#include "color.h"
#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"

color ray_color(const ray& r, const hittable& world, int depth) {
    hit_record rec;

    if (depth <= 0) {
        return color(0,0,0);
    }

    if (world.hit(r, .001, infinity, rec)) {
        point3 target = rec.p + rec.normal + random_in_hemisphere(rec.normal);
        return .5 * ray_color(ray(rec.p, target - rec.p), world, depth-1);
    }

    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5*(unit_direction.y() + 1.0);
    return (1.0-t)*color(1.0, 1.0, 1.0) + t*color(0.5, 0.7, 1.0);
}


int main() {
    // File so I don't need to redirect
    std::ofstream img_file;
    img_file.open("img.ppm");

    // Image
    const auto aspect_ratio = 16.0/9.0;
    const int width = 1080;
    const int height = static_cast<int>(width/aspect_ratio);
    const int samples_per_pixel = 100;
    const int max_depth = 10;

    // World
    hittable_list world;
    world.add(make_shared<sphere>(point3(0,0,-1), 0.5));
    world.add(make_shared<sphere>(point3(0,-100.5,-1), 100));

    // Camera
    camera cam;

    // Render

    img_file << "P3\n" << width << ' ' << height << "\n255\n";

    for (int j = 0; j < height; j++) {
        std::cerr << "\rScan Lines remaining: " << (height-1-j) << ' ' << std::flush;
        for (int i = 0; i < width; ++i) {
            color pixel_color(0,0,0);
            for (int s = 0; s < samples_per_pixel; ++s) {
                auto u = (i + random_double()) / (width-1);
                auto v = (height - j + random_double()) / (height-1);
                ray r = cam.get_ray(u, v);
                pixel_color += ray_color(r, world, max_depth);
            }
            write_color(img_file, pixel_color, samples_per_pixel);
        }
    }

    std::cerr << "\nDone.\n";
    img_file.close();
    return 0;
}
