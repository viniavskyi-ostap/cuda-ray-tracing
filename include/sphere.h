//
// Created by Юрий Елисеев on 22.04.2022.
//

#ifndef RAY_TRACING_SPHERE_H
#define RAY_TRACING_SPHERE_H

#include "hittable.h"
#include <Eigen/Dense>

using Eigen::Vector3d;
class material_t;

class sphere_t: public hittable_t {
public:
    Vector3d center;
    double radius;
    std::shared_ptr<material_t> m_ptr;

    sphere_t(Vector3d center, double r, std::shared_ptr<material_t> m): center{std::move(center)}, radius{r}, m_ptr(std::move(m)){};
    bool intersect(const ray_t &ray, hit_record_t &record) const override;
    Vector3d get_bounding_sphere_center() const override;
    double get_bounding_sphere_radius() const override;
};
#endif //RAY_TRACING_SPHERE_H
