//
// Created by Юрий Елисеев on 23.04.2022.
//

#ifndef RAY_TRACING_TRIANGLE_H
#define RAY_TRACING_TRIANGLE_H

#include "hittable.h"
#include <Eigen/Dense>
#include <utility>
#include <vector>
#include <cmath>
#include <array>

using Eigen::Vector3d;


class triangle_t {
public:
    std::array<Vector3d, 3> vertexes;
    Vector3d normal;

    explicit triangle_t(std::array<Vector3d, 3>  vrt): vertexes{std::move(vrt)}{
        Vector3d A = vertexes[1] - vertexes[0];
        Vector3d B = vertexes[2] - vertexes[0];
        normal = A.cross(B).normalized();
    }
    triangle_t(std::array<Vector3d, 3> vrt, Vector3d n): vertexes{std::move(vrt)}, normal(std::move(n)) {}
    bool intersect(const ray_t &ray, hit_record_t &record) const;
};

#endif //RAY_TRACING_TRIANGLE_H
