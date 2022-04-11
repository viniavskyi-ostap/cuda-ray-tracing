//
// Created by Ostap Viniavskyi on 10.04.2022.
//

#include <iostream>
#include <Eigen/Dense>
#include "camera.h"
#include "rays.h"
#include "geom_utils.h"

using Eigen::MatrixXd;

int main() {
    auto cam = make_35mm_camera(1200, 800);
    auto R = eul2rot(0., 0., EIGEN_PI);
    cam.rotate(R).rotate(R).translate(Vector3d{1., 1., 2.});
    auto rays = make_rays(0, 0, cam, 5);
    for (const auto& ray: rays) {
        std::cout << ray << '\n';
    }
}