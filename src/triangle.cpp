//
// Created by Юрий Елисеев on 23.04.2022.
//


#include "triangle.h"

constexpr float kEpsilon = 1e-8;

bool triangle_t::intersect(const ray_t &ray, hit_record_t &record) const {
    double is_parallel = normal.dot(ray.get_dir());
    if (std::abs(is_parallel) < kEpsilon)
        return false;
    double d_to_origin = -(normal.dot(vertexes[0]));
    double t = -(normal.dot(ray.get_orig()) + d_to_origin) / is_parallel;
    if (t < 0) return false;

    Vector3d intersection_point = ray.get_orig() + t * ray.get_dir();
    Vector3d inside_o_test;
    int next_idx;
    for (int i = 0; i <= 2; i++){
        next_idx = (i + 1) % 3;
        Vector3d edge = vertexes[next_idx] - vertexes[i];
        Vector3d v_p = intersection_point - vertexes[i];
        inside_o_test = edge.cross(v_p);
        if (normal.dot(inside_o_test) < 0)
            return false;
    }
    record.p = intersection_point;
    record.normal = normal;
    record.z = t;
    return true;
}
