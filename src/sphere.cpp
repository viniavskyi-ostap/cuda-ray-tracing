//
// Created by Юрий Елисеев on 22.04.2022.
//


#include "sphere.h"
#include <cmath>


bool sphere_t::intersect(const ray_t &ray, hit_record_t &record) const {
    Vector3d oc = ray.get_orig() - center;
    double b = oc.dot(ray.get_dir());
    double c = oc.dot(oc) - radius * radius;
    double dis = b * b - c;

    if (dis < 0)
        return false;

    double t = (-b - sqrt(dis));  // distance from ray origin to intersection point
    if (t < 0)  // look only on the positive direction
        return false;
    record.z = t;
    record.p = ray.get_orig() + t * ray.get_dir();
    record.normal = (record.p - center).normalized();
    return dis > 0;
}

Vector3d sphere_t::get_bounding_sphere_center() const {
    return center;
}

double sphere_t::get_bounding_sphere_radius() const {
    return radius;
}
