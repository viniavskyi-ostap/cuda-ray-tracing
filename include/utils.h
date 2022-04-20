//
// Created by Ostap Viniavskyi on 11.04.2022.
//

#ifndef RAY_TRACING_UTILS_H
#define RAY_TRACING_UTILS_H

#include <random>
#include <Eigen/Dense>

using Eigen::Vector3d;

template<typename Numeric, typename Generator = std::mt19937>
Numeric random_uniform(Numeric from, Numeric to) {
    thread_local static Generator gen(std::random_device{}());

    using dist_type = typename std::conditional<
            std::is_integral<Numeric>::value,
            std::uniform_int_distribution<Numeric>,
            std::uniform_real_distribution<Numeric>
    >::type;

    thread_local static dist_type dist;

    return dist(gen, typename dist_type::param_type{from, to});
}

Vector3d random_unit_ball();

#endif //RAY_TRACING_UTILS_H
