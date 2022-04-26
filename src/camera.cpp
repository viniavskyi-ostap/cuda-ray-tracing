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
