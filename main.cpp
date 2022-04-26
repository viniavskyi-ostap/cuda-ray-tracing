//
// Created by Ostap Viniavskyi on 10.04.2022.
//

#include <fstream>
#include "sphere.h"
#include "triangle_mesh.h"
#include "geom_utils.h"
#include "ray_tracing.h"

//Materials, Look at, Better triangle intersection
int main() {
    constexpr uint32_t width = 360, height = 240;
    constexpr int RECURSION_DEPTH = 3;

    // make camera and image
    image_t image{width, height};
    auto cam = make_35mm_camera(width, height);
    cam.translate(Vector3d{0, 0, -25});

    // make scene
    sphere_t sphere{Vector3d{0, 5., 0}, 2.};
    tri_mesh mesh = make_mesh_from_obj("../data/teapot.obj");
    scene_t scene{&mesh, &sphere};

    render(image, scene, cam, RECURSION_DEPTH);

    // save output to PPM format image
    std::ofstream f{"../data/image.ppm"};
    f << image_to_ppm(image);
    f.close();
    return 0;
}