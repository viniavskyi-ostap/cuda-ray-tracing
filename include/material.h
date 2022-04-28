//
// Created by Юрий Елисеев on 27.04.2022.
//

#ifndef RAY_TRACING_MATERIAL_H
#define RAY_TRACING_MATERIAL_H

#include "rays.h"
#include <Eigen/Dense>
#include <utility>

using Eigen::Vector3d;

struct hit_record_t;

class material_t {
public:
    explicit material_t(Vector3d color, size_t n): albedo{std::move(color)}, n_rays{n}{};
    [[nodiscard]] virtual ray_t scatter(const ray_t&, const hit_record_t&) const = 0;
    Vector3d get_albedo(){return albedo;};
protected:
    Vector3d albedo;
    size_t n_rays;
};

class diffuse_t: public material_t {
public:
    explicit diffuse_t(Vector3d color, size_t n): material_t{std::move(color), n}{};
    ray_t scatter(const ray_t& r_in, const hit_record_t& rec) const override;
};

class metal_t: public material_t {
public:
    explicit metal_t(Vector3d color, size_t n): material_t(std::move(color), n){};
    ray_t scatter(const ray_t& r_in, const hit_record_t& rec) const override;
};
#endif //RAY_TRACING_MATERIAL_H
