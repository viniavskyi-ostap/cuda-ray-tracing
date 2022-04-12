//
// Created by Юрий Елисеев on 12.04.2022.
//

#ifndef RAY_TRACING_HITTABLE_H
#define RAY_TRACING_HITTABLE_H

#include "rays.h"
#include <Eigen/Dense>

using Eigen::Vector3d;

struct hit_record_t {
    Vector3d p;
    Vector3d normal;
    double z;
};

class Hittable {
public:
    Hittable() = default;
    ~Hittable() = default;
    virtual bool intersect(const ray_t& ray, hit_record_t& record) = 0;
};

#endif //RAY_TRACING_HITTABLE_H
