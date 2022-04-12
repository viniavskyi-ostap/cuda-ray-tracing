//
// Created by Ostap Viniavskyi on 10.04.2022.
//

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <Eigen/Core>
#include <Eigen/Geometry>
#include "camera.h"
#include "rays.h"
#include "geom_utils.h"
#include "hittable.h"
#include "triangle_mesh.h"

// F - 1-st is the index of a vertex, 2-nd texture coordinate, 3-rd index of a vertex normal

// class Mesh: Hittable {std::vector<vertex>, std::<indices>, std::vector<normals>}

using Eigen::MatrixXd;
using Eigen::Vector3d;

// Add shift from origin
// Add origin to camera as attribute
int main() {

    tri_mesh mesh = make_mesh_from_obj("../data/teapot.obj");
    auto cam = make_35mm_camera(1200, 800);
    auto R = eul2rot(0., 0., EIGEN_PI);
    cam.rotate(R).rotate(R).translate(Vector3d{13., 6., 3.});
    auto rays = make_rays(0, 0, cam, 5);

    hit_record_t r;
    ray_t new_ray(Vector3d{13., 6., 3.}, Vector3d(0, 0, 0));
    std::cout << mesh.intersect(new_ray, r) << std::endl;
}