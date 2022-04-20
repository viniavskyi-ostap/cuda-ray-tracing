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
private:
    Vector3d m_orig, m_dir;
public:
    ray_t(Vector3d orig, Vector3d dir) : m_orig(move(orig)), m_dir(move(dir)) { m_dir.normalize(); }
    explicit ray_t(Vector3d dir) : m_orig(Vector3d::Zero()), m_dir(move(dir)) { m_dir.normalize(); }

    Vector3d get_orig() const { return m_orig; }
    Vector3d get_dir() const { return m_dir; }

    friend std::ostream &operator<<(std::ostream &s, const ray_t &ray);

};

#endif //RAY_TRACING_RAYS_H
