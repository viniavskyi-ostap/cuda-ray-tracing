//
// Created by Ostap Viniavskyi on 11.04.2022.
//

#ifndef RAY_TRACING_GEOM_UTILS_H
#define RAY_TRACING_GEOM_UTILS_H

#include <Eigen/Dense>

using Eigen::Matrix3d;
using Eigen::Vector3d;
using Vector2ui32 = Eigen::Matrix<uint32_t, 2, 1>;


// euler angles to rotation matrix R = R(Z)R(Y)R(X)
Matrix3d eul2rot(double x, double y, double z);

//homogenize 2D vector
template<typename T>
inline Vector3d homogenize(const Eigen::Matrix<T, 2, 1> &v) { return Vector3d{v[0], v[1], 1}; };

// rigid body motion
inline Vector3d transform3d(const Vector3d &v, const Matrix3d &R, const Vector3d &T) { return R * v + T; }
inline Vector3d &transform3d(Vector3d &v, const Matrix3d &R, const Vector3d &T) {
    v = R * v;
    v += T;
    return v;
}

#endif //RAY_TRACING_GEOM_UTILS_H
