//
// Created by Юрий Елисеев on 23.04.2022.
//


#include "triangle.h"
#define MOLLER_TRUMBORE

constexpr float kEpsilon = 1e-8;
//Möller-Trumbore algorithm
bool triangle_t::intersect(const ray_t &ray, hit_record_t &record) const {
#ifdef MOLLER_TRUMBORE
    Vector3d AB = vertexes[1] - vertexes[0];
    Vector3d AC = vertexes[2] - vertexes[0];
    Vector3d ray_dir = ray.get_dir();
    Vector3d ray_origin = ray.get_orig();

    //Compute determinant of matrix M (Cramer`s Rule)
    Vector3d vec_p = ray_dir.cross(AC);
    double det = AB.dot(vec_p);
    double inv_det = 1 / det;
    if (det < kEpsilon)
        return false;

    //Compute determinant of M_2 and calculate U coordinate
    // Translate triangle to the origin
    Vector3d vec_t = ray_origin - vertexes[0];
    double u = vec_t.dot(vec_p) * inv_det;
    if (u < 0 || u > 1)
        return false;

    //Calculate determinant of M_3 and V coordinate
    Vector3d vec_q = vec_t.cross(AB);
    double v = ray_dir.dot(vec_q) * inv_det;
    if (v < 0 || u + v > 1)
        return false;

    //Calculate determinant of M_1 and t coordinate
    double t = AC.dot(vec_q) * inv_det;
    if (t < 0)
        return false;
    record.p = ray_origin + t * ray_dir;
    record.z = t;
    record.normal = normal;
    return true;
#else
    double is_parallel = normal.dot(ray.get_dir());
    if (is_parallel < kEpsilon)
        return false;
    double d_to_origin = -(normal.dot(vertexes[0]));
    double t = -(normal.dot(ray.get_orig()) + d_to_origin) / is_parallel;

    if (t <= kEpsilon) return false;

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
#endif
}