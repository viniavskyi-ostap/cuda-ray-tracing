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

    double t = (-b - sqrt(dis));
    if (t < 0)
        return false;
    record.z = t;
    record.p = ray.get_orig() + t * ray.get_dir();
    record.normal = (record.p - center).normalized();
    return dis > 0;
}