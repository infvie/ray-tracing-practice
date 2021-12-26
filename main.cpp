#include <iostream>
#include <fstream>

#include "vec3.h"
#include "color.h"
#include "ray.h"

bool hit_sphere(const point3& center, double radius, const ray& r) {
    vec3 oc = r.origin() - center;
    auto a = dot(r.direction(), r.direction());
    auto b = 2.0 * dot(oc, r.direction());
    auto c = dot(oc,oc) - radius*radius;
    auto discriminant = b*b - 4*a*c;
    return (discriminant > 0);
}

color ray_color(const ray& r) {
    if (hit_sphere(point3(0,0,-1), .5, r))
        return {1.0,0,0};
    vec3 unit_dir = unit_vector(r.dir);
    auto t = 0.5*(unit_dir.y()+1);
    return (1.0-t)*color(1.0, 1.0, 1.0) + t*color(0.5, 0.7, 1);
}


int main() {
    // File so I don't need to redirect
    std::ofstream img_file;
    img_file.open("img.ppm");

    // Image
    const auto aspect_ratio = 16.0/9.0;
    const int width = 400;
    const int height = static_cast<int>(width/aspect_ratio);

    // Camera
    auto viewport_height = 2.0;
    auto viewport_width = aspect_ratio * viewport_height;
    auto focal_length = 1.0;

    auto origin = point3(0,0,0);
    auto horizontal = vec3(viewport_width, 0, 0);
    auto vertical = vec3(0, viewport_height, 0);
    auto lower_left_corner = origin - horizontal/2 - vertical/2 - vec3(0, 0, focal_length);

    // Render

    img_file << "P3\n" << width << ' ' << height << "\n255\n";

    for (int j = 0; j <= height; j++) {
        std::cerr << "\rScan Lines remaining: " << (height-j) << ' ' << std::flush;
        for (int i = 0; i < width; i++) {
            auto u = double(i) / (width-1);
            auto v = double(height-j) / (height-1);
            ray r(origin, lower_left_corner + u*horizontal + v*vertical - origin);
            color pixel_color = ray_color(r);
            write_color(img_file, pixel_color);
        }
    }

    std::cerr << "\nDone.\n";
    img_file.close();
    return 0;
}
