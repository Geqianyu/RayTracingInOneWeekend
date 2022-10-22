
#include <fstream>

#include "Color.h"

void write_color(std::ofstream& out_file, color pixel_color) {
    out_file << static_cast<int>(255.999 * pixel_color.r) << ' '
        << static_cast<int>(255.999 * pixel_color.g) << ' '
        << static_cast<int>(255.999 * pixel_color.b) << '\n';
}