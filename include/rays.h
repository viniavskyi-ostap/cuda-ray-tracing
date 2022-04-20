//
// Created by Ostap Viniavskyi on 11.04.2022.
//

#ifndef RAY_TRACING_RAYS_H
#define RAY_TRACING_RAYS_H

#include <vector>
#include <iostream>
#include <Eigen/Dense>
#include "camera.h"

using std::move;
using Eigen::Vector3d;

class ray_t {
public:
    Vector3d m_orig, m_dir;
    ray_t(Vector3d orig, Vector3d dir) : m_orig(move(orig)), m_dir(move(dir)) {}
    explicit ray_t(Vector3d dir) : m_orig(Vector3d::Zero()), m_dir(move(dir)) {}

    friend std::ostream &operator<<(std::ostream &s, const ray_t &ray);

};


std::vector<ray_t> make_rays(uint32_t w, uint32_t h, const camera_t &camera, size_t num_rays);


#endif //RAY_TRACING_RAYS_H
