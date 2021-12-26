#include <iostream>
#include <fstream>

#include "vec3.h"
#include "color.h"

int main() {
    // File so I don't need to redirect
    std::ofstream img_file;
    img_file.open("img.ppm");

    // Image
    const int width = 256;
    const int height = 256;

    // Render

    img_file << "P3\n" << width << ' ' << height << "\n255\n";

    for (int j = 0; j <= height; j++) {
        std::cerr << "\rScanlines remaining: " << (height-j) << ' ' << std::flush;
        for (int i = 0; i < width; i++) {
            color pixel_color(double(i) / (width-1), double(j) / (height-1), .25);
            write_color(img_file, pixel_color);
        }
    }

    std::cerr << "\nDone.\n";
    img_file.close();
    return 0;
}
