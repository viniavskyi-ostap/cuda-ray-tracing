//
// Created by Ostap Viniavskyi on 11.04.2022.
//

#include <cmath>
#include "geom_utils.h"

Matrix3d eul2rot(double x, double y, double z) {
    Matrix3d R;
    double cx = cos(x), cy = cos(y), cz = cos(z);
    double sx = sin(x), sy = sin(y), sz = sin(z);
    R << cy * cz, sx * sy * cz - cx * sz, cx * sy * sz - sx * cz,
            cy * sz, sx * sy * sz + cx * cz, cx * sy * sz - sx * cz,
            -sy, sx * cy, cx * cy;

    return R;
}


