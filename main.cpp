//
// Created by Ostap Viniavskyi on 10.04.2022.
//

#include <fstream>
#include "sphere.h"
#include "triangle_mesh.h"
#include "geom_utils.h"
#include "ray_tracing.h"
#include "material.h"

//Materials, Look at, Better triangle intersection
int main() {
    constexpr uint32_t width = 360, height = 240;
    constexpr int RECURSION_DEPTH = 3;

    // make camera and image
    auto diffuse = std::make_shared<diffuse_t>(Vector3d(0.25, 0.25, 0.25));
    auto metal = std::make_shared<metal_t>(Vector3d(0.85, 0.85, 0.85));
    image_t image{width, height};
    auto cam = make_35mm_camera(width, height);
    cam.translate(Vector3d{0, 2, -10});
    // make scene
    sphere_t sphere{Vector3d{0, 5., 0}, 2., metal};
    sphere_t ground_sphere{Vector3d{0., -100., 0.}, 100., diffuse};
    tri_mesh mesh = make_mesh_from_obj("../data/teapot.obj", metal);
    scene_t scene{&ground_sphere, &mesh, &sphere};
    render(image, scene, cam, RECURSION_DEPTH);
    std::ofstream f{"../data/image.ppm"};
    f << image_to_ppm(image);
    f.close();
    return 0;
}