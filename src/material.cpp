//
// Created by Юрий Елисеев on 27.04.2022.
//

#include "material.h"
#include "utils.h"
#include "hittable.h"


ray_t diffuse_t::scatter(const ray_t& r_in, const hit_record_t& rec) const {
    Vector3d scattered_dir = rec.normal + random_unit_ball();
    return {rec.p, scattered_dir};
}

ray_t metal_t::scatter(const ray_t& r_in, const hit_record_t &rec) const {
    Vector3d ref = reflect(r_in.get_dir(), rec.normal);
    return {rec.p, ref};
}
