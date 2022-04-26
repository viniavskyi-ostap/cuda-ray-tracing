//
// Created by Ostap Viniavskyi on 20.04.2022.
//
#include "camera.h"
#include "utils.h"
#include "geom_utils.h"
#include "rays.h"
#include "rays_gen.h"

using Vector2ui32 = Eigen::Matrix<uint32_t, 2, 1>;
using std::vector;


vector<ray_t> make_primary_rays(uint32_t w, uint32_t h, const camera_t &camera, size_t num_rays) {
    vector<ray_t> rays;
    rays.reserve(num_rays);

    double dx, dy;
    Vector3d dest;
    Vector2d dest_pixel;

    for (size_t i = 0; i < num_rays; ++i) {
        dx = random_uniform(0., 1.);
        dy = random_uniform(0., 1.);
        dest_pixel << w + dx, h + dy;
        dest = pixel2calibrated(dest_pixel, camera);

        // rotate to world coordinates
        transform3d(dest, camera.get_R(), camera.get_T());
        rays.emplace_back(camera.get_T(), dest - camera.get_T());
    }
    return rays;
}

vector<ray_t> make_secondary_rays(const hit_record_t &record, size_t num_rays) {
    vector<ray_t> rays;
    rays.reserve(num_rays);

    for (size_t i = 0; i < num_rays; ++i)
        rays.emplace_back(record.p, record.normal + random_unit_ball());
    return rays;
}
