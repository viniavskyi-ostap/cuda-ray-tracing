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

class hittable_t {
public:
    hittable_t() = default;
    ~hittable_t() = default;
    virtual bool intersect(const ray_t &ray, hit_record_t &record) const = 0;
    virtual Vector3d get_bounding_sphere_center() const = 0;
    virtual double get_bounding_sphere_radius() const = 0;
};

#endif //RAY_TRACING_HITTABLE_H
