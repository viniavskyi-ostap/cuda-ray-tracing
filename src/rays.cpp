//
// Created by Ostap Viniavskyi on 11.04.2022.
//
#include <iostream>

#include "camera.h"
#include "utils.h"
#include "geom_utils.h"
#include "rays.h"

using Vector2ui32 = Eigen::Matrix<uint32_t, 2, 1>;
using std::vector;
using std::ostream;

ostream &operator<<(ostream &s, const ray_t &ray){
    s << "Ray(orig=" << ray.m_orig.transpose() << ", dest=" << ray.m_dest.transpose() << ")";
    return s;
}

vector<ray_t> make_rays(uint32_t w, uint32_t h, const camera_t &camera, size_t num_rays) {
    vector<ray_t> rays;
    rays.reserve(num_rays);

    double dx, dy;
    Vector3d dest;
    Vector2d dest_pixel = Vector2d::Zero();

    for (size_t i = 0; i < num_rays; ++i) {
        dx = random_uniform(0., 1.);
        dy = random_uniform(0., 1.);
        dest_pixel << w + dx, h + dy;
        dest = pixel2calibrated(dest_pixel, camera);

//      rotate to world coordinates
        transform3d(dest, camera.get_R(), camera.get_T());
        rays.emplace_back( dest);
    }
    return rays;
}