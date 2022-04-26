//
// Created by Юрий Елисеев on 22.04.2022.
//

#ifndef RAY_TRACING_SPHERE_H
#define RAY_TRACING_SPHERE_H

#include "hittable.h"
#include <Eigen/Dense>

using Eigen::Vector3d;

class sphere_t: public hittable_t {
public:
    Vector3d center;
    double radius;

    sphere_t(Vector3d center, double r): center{std::move(center)}, radius{r}{}
    bool intersect(const ray_t &ray, hit_record_t &record) const override;
};
#endif //RAY_TRACING_SPHERE_H
