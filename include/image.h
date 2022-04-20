//
// Created by Ostap Viniavskyi on 12.04.2022.
//

#ifndef RAY_TRACING_IMAGE_H
#define RAY_TRACING_IMAGE_H

#include <cctype>
#include <string>
#include <Eigen/Dense>

using Eigen::Vector3d;

constexpr unsigned int IMAGE_MAX_VALUE = 255;

class image_t {
    constexpr static uint8_t IMAGE_CHANNELS = 3;
private:
    double *m_data;
    uint32_t m_width, m_height;
public:
    image_t(uint32_t width, uint32_t height) : m_data{new double[width * height * IMAGE_CHANNELS]},
                                               m_width{width}, m_height{height} {}
    ~image_t() { delete[] m_data; }

    uint32_t get_width() const { return m_width; }
    uint32_t get_height() const { return m_height; }

    double &operator()(uint32_t w, uint32_t h, uint8_t c) {
        return m_data[IMAGE_CHANNELS * (h * m_width + w) + c];
    }

    double operator()(uint32_t w, uint32_t h, uint8_t c) const {
        return m_data[IMAGE_CHANNELS * (h * m_width + w) + c];
    }

    Vector3d operator()(uint32_t w, uint32_t h) const {
        return Vector3d{
                this->operator()(w, h, 0),
                this->operator()(w, h, 1),
                this->operator()(w, h, 2)
        };
    }

    void set_pixel(uint32_t w, uint32_t h, const Vector3d &value) {
        for (uint8_t i = 0; i < IMAGE_CHANNELS; ++i) {
            this->operator()(w, h, i) = value[i];
        }
    }

    friend std::ostream &operator<<(std::ostream &s, const image_t &image) {
        for (uint32_t i = 0; i < image.m_height; ++i) {
            for (uint32_t j = 0; j < image.m_height; ++j) {
                s << image(i, j).transpose() << '\n';
            }
        }
        return s;
    }
};

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


#endif //RAY_TRACING_IMAGE_H
