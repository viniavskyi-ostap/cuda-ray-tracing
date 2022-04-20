//
// Created by Ostap Viniavskyi on 11.04.2022.
//
#include <cmath>
#include "utils.h"

constexpr double PI = 3.141592653589793238462643383279502884197169399375105820974944592307816406;

Vector3d random_unit_ball() {
    double phi = random_uniform(0., 2. * PI);
    double theta = random_uniform(0., PI);
    double r = random_uniform(0., 1.);
    double cos_phi = cos(phi), sin_phi = sin(phi);
    double cos_theta = cos(theta), sin_theta = sin(theta);

    return Vector3d{
            r * cos_phi * sin_theta,
            r * sin_phi * sin_theta,
            r * cos_theta
    };
}