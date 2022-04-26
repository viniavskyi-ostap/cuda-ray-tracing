//
// Created by Ostap Viniavskyi on 26.04.2022.
//

#ifndef RAY_TRACING_RAY_TRACING_H
#define RAY_TRACING_RAY_TRACING_H

#include <vector>
#include <Eigen/Dense>
#include "rays.h"
#include "hittable.h"
#include "image.h"
#include "camera.h"

using scene_t = std::vector<const hittable_t *>;

constexpr size_t RAYS_SPAWNED = 8;

Eigen::Vector3d trace_rays(const std::vector<ray_t> &rays, const scene_t &scene, uint8_t depth);

void render(image_t &image, const scene_t &scene, const camera_t &camera, int spawn_depth);

#endif //RAY_TRACING_RAY_TRACING_H
