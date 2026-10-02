#ifndef LIDAR_UTILS_HPP
#define LIDAR_UTILS_HPP

#include <vector>
#include "LidarTypes.hpp"

namespace LidarUtils {
    void generatePolarPoints(std::vector<Lidar::PolarPoint> &vector, size_t max_points);
}

#endif