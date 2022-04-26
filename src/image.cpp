//
// Created by Ostap Viniavskyi on 26.04.2022.
//

#include "image.h"

std::ostream &operator<<(std::ostream &s, const image_t &image) {
    for (uint32_t i = 0; i < image.m_height; ++i) {
        for (uint32_t j = 0; j < image.m_height; ++j) {
            s << image(i, j).transpose() << '\n';
        }
    }
    return s;
}

std::string image_to_ppm(const image_t &image) {
    uint16_t r, g, b;
    std::ostringstream buffer;
    uint32_t width = image.get_width(), height = image.get_height();

    // add image metadata
    buffer << "P3" << '\n';
    buffer << width << ' ' << height << '\n';
    buffer << IMAGE_MAX_VALUE << '\n';

    for (uint32_t h = 0; h < height; ++h) {
        for (uint32_t w = 0; w < width; ++w) {
            auto pixel_color = image(w, h);
            r = static_cast<uint16_t> (IMAGE_MAX_VALUE * pixel_color[0]);
            g = static_cast<uint16_t> (IMAGE_MAX_VALUE * pixel_color[1]);
            b = static_cast<uint16_t> (IMAGE_MAX_VALUE * pixel_color[2]);

            buffer << r << ' ' << g << ' ' << b << '\n';
        }
    }
    return buffer.str();
}