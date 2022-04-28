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
    virtual ray_t scatter(const ray_t&, const hit_record_t&) const = 0;
    virtual Vector3d get_albedo() const = 0;
};

class diffuse_t: public material_t {
public:
    explicit diffuse_t(Vector3d color): albedo(std::move(color)){};
    ray_t scatter(const ray_t& r_in, const hit_record_t& rec) const override;
    Vector3d get_albedo() const override {return albedo;};
public:
    Vector3d albedo;
};

class metal_t: public material_t {
public:
    explicit metal_t(Vector3d color): albedo(std::move(color)){};
    ray_t scatter(const ray_t& r_in, const hit_record_t& rec) const override;
    Vector3d get_albedo() const override {return albedo;};
public:
    Vector3d albedo;
};

#endif //RAY_TRACING_MATERIAL_H
