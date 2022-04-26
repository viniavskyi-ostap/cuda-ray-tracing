//
// Created by Ostap Viniavskyi on 20.04.2022.
//

#ifndef RAY_TRACING_RAYS_GEN_H
#define RAY_TRACING_RAYS_GEN_H

#include "rays.h"
#include "camera.h"
#include "hittable.h"


std::vector<ray_t> make_primary_rays(uint32_t w, uint32_t h, const camera_t &camera, size_t num_rays);
std::vector<ray_t> make_secondary_rays(const hit_record_t &record, size_t num_rays);

#endif //RAY_TRACING_RAYS_GEN_H
