//
// Created by Юрий Елисеев on 12.04.2022.
//

#include "triangle_mesh.h"

bool tri_mesh::intersect(const ray_t &ray, hit_record_t &record) {

    Vector3d p;
    Vector3d norm;
    double dist = std::numeric_limits<double>::infinity();
    for (auto &triangle: triangles){
        double is_paralel = triangle.normal.dot(ray.m_dest);
        if (is_paralel == 0)
            continue;
        double d_to_origin = (-triangle.normal).dot(triangle.vertexes[0]);
        double t = -(triangle.normal.dot(ray.m_orig) + d_to_origin) / is_paralel;
        if (t < 0) continue;

        Vector3d intersection_point = ray.m_orig + t * ray.m_dest;

        Vector3d inside_o_test;
        for (int i = 0; i < 2; i++){
            Vector3d edge = triangle.vertexes[i+1 < 2 ? i+1: 0] - triangle.vertexes[i];
            Vector3d v_p = intersection_point - edge;
            inside_o_test = edge.cross(v_p);
            if (triangle.normal.dot(inside_o_test) < 0) continue;
        }

        if (t < dist)
        {
            p = intersection_point;
            norm = triangle.normal;
            dist = t;
        }
    }
    if (std::isinf(dist))
        return false;

    record.p = p;
    record.normal = norm;
    record.z = dist;
    return false;
}


tri_mesh make_mesh_from_obj(const std::string& file_name){
    std::ifstream obj_file(file_name);
    std::string line;
    std::cout << obj_file.is_open() << std::endl;

    std::vector<Vector3d> vertices;
    std::vector<Triangle> mesh_triangles;
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
                vertex_normal_idx.emplace_back(v, n);
            }

            std::vector<Vector3d> tri_vertexes;
            tri_vertexes.reserve(vertex_normal_idx.size());
            for (auto v_pair: vertex_normal_idx){
                tri_vertexes.push_back(vertices[v_pair.first]);
            }
            Vector3d edge_01(vertices[vertex_normal_idx[1].first] - vertices[vertex_normal_idx[0].first]);
            Vector3d edge_02(vertices[vertex_normal_idx[2].first] - vertices[vertex_normal_idx[0].first]);
            Vector3d face_norm = edge_01.cross(edge_02).normalized();
            Triangle tri;
            tri.vertexes = tri_vertexes;
            tri.normal = face_norm;
            mesh_triangles.push_back(tri);
        }
    }
    return tri_mesh(mesh_triangles);
}