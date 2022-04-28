//
// Created by Юрий Елисеев on 12.04.2022.
//

constexpr float kEpsilon = 1e-8;
#include "triangle_mesh.h"

#include <utility>

bool tri_mesh::intersect(const ray_t &ray, hit_record_t &record) const {

    Vector3d p;
    Vector3d norm;
    double dist = std::numeric_limits<double>::infinity();
    hit_record_t tri_record;
    for (const auto &triangle: triangles) {
        if (triangle.intersect(ray, tri_record)) {
            if (tri_record.z < dist) {
                p = tri_record.p;
                norm = tri_record.normal;
                dist = tri_record.z;
            }
        }
    }
    if (std::isinf(dist))
        return false;
    record.p = p;
    record.normal = norm;
    record.z = dist;
    record.m_ptr = m_ptr;
    return true;
}

Vector3d tri_mesh::get_bounding_sphere_center() const {
    return Vector3d{0., 1., 0.};
}

double tri_mesh::get_bounding_sphere_radius() const {
    return 2.;
}


tri_mesh make_mesh_from_obj(const std::string& file_name, std::shared_ptr<material_t> mat){
    std::ifstream obj_file(file_name);
    std::string line;

    std::vector<Vector3d> vertices;
    std::vector<triangle_t> mesh_triangles;
    while (std::getline(obj_file, line)){
        std::string type;
        std::stringstream line_stream(line);

        line_stream >> type;
        if (type == "v") {
            double x, y, z;
            line_stream >> x >> y >> z;
            vertices.emplace_back(x, y, z);
        }
        if (type == "f"){
            std::vector<std::pair<int, int>> vertex_normal_idx;
            std::string token;
            while(line_stream >> token){
                std::string vertex_idx, skip, normal_idx;
                std::istringstream vertex_s(token);
                std::getline(vertex_s, vertex_idx, '/');
                std::getline(vertex_s, skip, '/');
                std::getline(vertex_s, normal_idx, '/');
                int v = std::stoi(vertex_idx);
                int n = std::stoi(normal_idx);
                v--; n--;
                vertex_normal_idx.emplace_back(v, n);
            }

            std::array<Vector3d, 3> tri_vertexes;
            for (size_t i = 0; i < vertex_normal_idx.size(); ++i)
                tri_vertexes[i] = vertices[vertex_normal_idx[i].first];

            triangle_t tri(tri_vertexes);
            mesh_triangles.push_back(tri);
        }
    }
    return tri_mesh(mesh_triangles, std::move(mat));
}