#include <iostream>
#include <fstream>

int main() {
    // File so I don't need to redirect
    std::ofstream img_file;
    img_file.open("img.ppm");

    // Image
    const int width = 256;
    const int height = 256;

    // Render

    img_file << "P3\n" << width << ' ' << height << "\n255\n";

    const double b = .25;

    for (int j = 0; j <= height; j++) {
        std::cerr << "\rScanlines remaining: " << (height-j) << ' ' << std::flush;
        for (int i = 0; i < width; i++) {
            double r = double(i) / (width-1);
            double g = double(j) / (height-1);

            int ir = static_cast<int>(255.999*r);
            int ig = static_cast<int>(255.999*g);
            int ib = static_cast<int>(255.999*b);

            img_file << ir << ' ' << ig << ' ' << ' ' << ib << '\n';
        }
    }

    std::cerr << "\nDone.\n";
    img_file.close();
    return 0;
}
