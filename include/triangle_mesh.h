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

using Eigen::MatrixXd;
using Eigen::Vector3d;

struct Triangle {
    std::vector<Vector3d> vertexes;
    Vector3d normal;
};

class tri_mesh: public Hittable {
private:
    std::vector<Triangle> triangles;
public:
    tri_mesh() = delete;
    explicit tri_mesh(std::vector<Triangle> trg): triangles{std::move(trg)} {}
    bool intersect(const ray_t& ray, hit_record_t& record) override;
};

tri_mesh make_mesh_from_obj(const std::string& file_name);

#endif //RAY_TRACING_TRIANGLE_MESH_H

