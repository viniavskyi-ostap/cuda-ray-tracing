//
// Created by Юрий Елисеев on 12.04.2022.
//

#ifndef RAY_TRACING_HITTABLE_H
#define RAY_TRACING_HITTABLE_H

#include "rays.h"
#include <Eigen/Dense>

using Eigen::Vector3d;

struct hit_record {
    Vector3d p;
    Vector3d normal;
};

class Hittable {
public:
    Hittable() = default;
    virtual ~Hittable() = default;
    [[nodiscard]] virtual bool intersect(const ray_t& ray, double t_min, double t_max, hit_record& record) const = 0;
};

#endif //RAY_TRACING_HITTABLE_H
