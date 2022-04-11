//
// Created by Ostap Viniavskyi on 10.04.2022.
//

#ifndef RAY_TRACING_CAMERA_H
#define RAY_TRACING_CAMERA_H

#include <cctype>
#include <cmath>
#include <iostream>
#include <Eigen/Dense>


using Eigen::Vector2d, Eigen::Vector3d, Eigen::Matrix3d;
using Vector2ui32 = Eigen::Matrix<uint32_t, 2, 1>;
using std::move;

class camera_t {
private:
    double m_f; // physical focal length
    Vector2d m_ccd_size; // physical size of CCD
    Vector2ui32 m_ccd_res; // resolution of matrix in pixels
    Vector2d m_pp; //principal point in pixels
    Matrix3d m_R; // rotation in 3D space
    Vector3d m_T; // translation in 3D space

public:
    camera_t() = delete;

    camera_t( // full constructor
            double f, double ccd_size_x, double ccd_size_y,
            uint32_t ccd_res_x, uint32_t ccd_res_y,
            double pp_x, double pp_y,
            Matrix3d R, Vector3d T
    ) : m_f{f}, m_ccd_size{ccd_size_x, ccd_size_y},
        m_ccd_res(ccd_res_x, ccd_res_y), m_pp{pp_x, pp_y}, m_R{move(R)}, m_T{move(T)} {}

    camera_t( //set PP at image center
            double f, double ccd_size_x, double ccd_size_y,
            uint32_t ccd_res_x, uint32_t ccd_res_y,
            Matrix3d R, Vector3d T
    ) : m_f{f}, m_ccd_size{ccd_size_x, ccd_size_y},
        m_ccd_res(ccd_res_x, ccd_res_y),
        m_pp{static_cast<double>(ccd_res_x) / 2, static_cast<double>(ccd_res_y) / 2},
        m_R{move(R)}, m_T{move(T)} {};

    camera_t( // set (m_R, m_T) to identity and PP at image center
            double f, double ccd_size_x, double ccd_size_y,
            uint32_t ccd_res_x, uint32_t ccd_res_y
    ) : m_f{f}, m_ccd_size{ccd_size_x, ccd_size_y},
        m_ccd_res(ccd_res_x, ccd_res_y), m_pp{ccd_res_x / 2, ccd_res_y / 2},
        m_R{Matrix3d::Identity()}, m_T{Vector3d::Zero()} {};

    double get_f() const { return m_f; }
    double get_fx() const { return m_ccd_res[0] * m_f / m_ccd_size[0]; }
    double get_fy() const { return m_ccd_res[1] * m_f / m_ccd_size[1]; }

    double get_fov() const {
        return 2 * atan(0.5 * sqrt(m_ccd_size[0] * m_ccd_size[0] + m_ccd_size[1] * m_ccd_size[1]) / m_f);
    }
    double get_hfov() const { return 2 * atan(0.5 * m_ccd_size[0] / m_f); }
    double get_vfov() const { return 2 * atan(0.5 * m_ccd_size[1] / m_f); }

    Vector2ui32 get_image_res() const { return m_ccd_res; }
    double get_cx() const { return m_pp[0]; }
    double get_cy() const { return m_pp[1]; }

    void set_RT(Matrix3d R, Vector3d T) {
        set_R(move(R));
        set_T(move(T));
    }
    void set_R(Matrix3d R) { m_R = move(R); }
    void set_T(Vector3d T) { m_T = move(T); }
    Matrix3d get_R() const { return m_R; }
    Vector3d get_T() const { return m_T; }

    camera_t &rotate(const Matrix3d &R) {
        m_R *= R;
        return *this;
    }
    camera_t &translate(const Vector3d &T) {
        m_T += T;
        return *this;
    }

    friend std::ostream &operator<<(std::ostream &s, const camera_t &camera);
};

// utility functions for creating 35mm camera with 36x24mm^2 CCD
camera_t make_35mm_camera(uint32_t ccd_res_x, uint32_t ccd_res_y);
camera_t make_35mm_camera(uint32_t ccd_res_x, uint32_t ccd_res_y, Matrix3d R, Vector3d T);

// conversion between pixel and calibrated ray spaces
template<class T>
Vector3d pixel2calibrated(const Eigen::Matrix<T, 2, 1> &p, const camera_t &camera) {
    double fx = camera.get_fx(), fy = camera.get_fy();
    double cx = camera.get_cx(), cy = camera.get_cy();

    return Vector3d{(p[0] - cx) / fx, (p[1] - cy) / fy, 1};
}


Vector3d calibrated2pixel(Vector3d p, const camera_t &camera);

#endif //RAY_TRACING_CAMERA_H
