//
// Created by Ostap Viniavskyi on 10.04.2022.
//

#include "camera.h"

using std::ostream;

ostream &operator<<(ostream &s, const camera_t &camera) {
    s << "Camera(\nf=" << camera.m_f << "\n"
      << "ccd_size=[" << camera.m_ccd_size[0] << ", " << camera.m_ccd_size[1] << "]\n"
      << "ccd_res=[" << camera.m_ccd_res[0] << ", " << camera.m_ccd_res[1] << "]\n"
      << "pp=[" << camera.m_pp[0] << ", " << camera.m_pp[1] << "]\n"
      << "R=[\n" << camera.m_R << "]\n"
      << "T=[" << camera.m_T.transpose() << "])";
    return s;
}

camera_t make_35mm_camera(uint32_t ccd_res_x, uint32_t ccd_res_y) {
    return camera_t{35., 36., 24, ccd_res_x, ccd_res_y};
}

void camera_t::look_at(const hittable_t* object){
    Vector3d temp = object->get_bounding_sphere_center();
    Vector3d new_z = (temp - m_T);

    // in attempt of looking at itself => no action needed
    if (new_z.norm() < 1e-8) return;

    double dist = new_z.norm();
    new_z /= dist;

    // set random vector to  Z-axis,
    temp << 0., 0., 1.;
    // if it is very close to newZ-axis not rotation needed

    if ((temp - new_z).norm() >= 1e-8){
        Vector3d new_y = new_z.cross(temp).normalized();
        Vector3d new_x = new_y.cross(new_z);
        m_R << new_x, new_y, new_z; // R = [X, Y, Z] - 3x3 matrix
    }

    // translate camera along new z axis so that object is visible
    const double dist_scale = 2.5;
    double r = object->get_bounding_sphere_radius();
    double new_dist = dist_scale * 2 * r * m_f / get_ccd_diagonal() + r;
    m_T = m_T + (dist - new_dist) * new_z;
}

