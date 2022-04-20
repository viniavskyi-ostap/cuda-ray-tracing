//
// Created by Ostap Viniavskyi on 11.04.2022.
//
#include <iostream>

#include "rays.h"
using std::ostream;

ostream &operator<<(ostream &s, const ray_t &ray) {
    s << "Ray(orig=" << ray.m_orig.transpose() << ", dest=" << ray.m_dir.transpose() << ")";
    return s;
}