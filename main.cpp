//
// Created by Ostap Viniavskyi on 10.04.2022.
//

#include <iostream>
#include <fstream>
#include <vector>

#include "image.h"
#include "camera.h"
#include "rays.h"
#include "rays_gen.h"
#include "geom_utils.h"
#include "hittable.h"
#include "sphere.h"
#include "triangle_mesh.h"
#include "triangle.h"

using Eigen::MatrixXd;
using Eigen::Vector3d;

using scene_t = std::vector<hittable_t *>;

constexpr size_t RAYS_SPAWNED = 8;
constexpr int RECURSION_DEPTH = 2;

Vector3d trace_rays(const std::vector<ray_t> &rays, const scene_t &scene, uint8_t depth) {
    if (depth == 0)
        return Vector3d{0., 0., 0.};

    const static Vector3d BACKGROUND{0.75, 0.85, 1.};

    auto color = Vector3d{0., 0., 0.};
    hit_record_t record, curr_record;
    bool has_hit;
    std::vector<ray_t> secondary_rays;

    for (const auto &ray: rays) {
        has_hit = false;
        curr_record.z = std::numeric_limits<double>::infinity();
        for (const hittable_t *object: scene) {
            if (object->intersect(ray, record)) {
                has_hit = true;
                if (record.z < curr_record.z)
                    curr_record = record;
            }
        }

        if (has_hit) {
            secondary_rays = make_secondary_rays(curr_record, RAYS_SPAWNED);
            color += 0.5 * trace_rays(secondary_rays, scene, depth - 1);
        } else {
            color += BACKGROUND;
        }
    }
    color /= rays.size();
    return color;
}

int main() {
    constexpr uint32_t width = 300, height = 200;
    tri_mesh mesh = make_mesh_from_obj("../data/teapot.obj");
    auto cam = make_35mm_camera(width, height);
    auto R = eul2rot(0., 0., EIGEN_PI);
    cam.translate(Vector3d{0, 0, -10});
    scene_t scene{&mesh};

    image_t image{width, height};
    for (size_t i = 0; i < width; ++i) {
        for (size_t j = 0; j < height; ++j) {
            auto rays = make_rays(i, j, cam, fRAYS_SPAWNED);
            auto color = trace_rays(rays, scene, RECURSION_DEPTH);
            image.set_pixel(i, j, color);
        }
    }

    std::ofstream f{"../data/image.ppm"};
    f << image_to_ppm(image);
    f.close();
    return 0;
}