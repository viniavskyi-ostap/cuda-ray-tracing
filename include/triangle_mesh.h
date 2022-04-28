//
// Created by Юрий Елисеев on 12.04.2022.
//

#ifndef RAY_TRACING_TRIANGLE_MESH_H
#define RAY_TRACING_TRIANGLE_MESH_H
#include <utility>
#include <vector>
#include <Eigen/Core>
#include <fstream>
#include "hittable.h"
#include <cmath>
#include "triangle.h"
#include <array>

using Eigen::MatrixXd;
using Eigen::Vector3d;

class tri_mesh: public hittable_t {
private:
    std::vector<triangle_t> triangles;
public:
    tri_mesh() = delete;
    explicit tri_mesh(std::vector<triangle_t> trg): triangles{std::move(trg)} {}
    bool intersect(const ray_t& ray, hit_record_t& record) const override;
    Vector3d get_bounding_sphere_center() const override;
    double get_bounding_sphere_radius() const override;
};

tri_mesh make_mesh_from_obj(const std::string& file_name);

#endif //RAY_TRACING_TRIANGLE_MESH_H

