#ifndef LIDAR_UTILS_HPP
#define LIDAR_UTILS_HPP

#include <vector>
#include "LidarTypes.hpp"

namespace LidarUtils {
    /** @brief Generates Random LiDAR Polar Points
     *  @param vector Vector where Polar Points will be added
     *  @param max_points Number of LiDAR Polar Points to generate
     */
    void generatePolarPoints(std::vector<Lidar::PolarPoint> &vector, size_t max_points);


    /** @brief Validates if a Polar Point falls outside distance and angle valid values
     *  @param point The Polar Point to validate
     *  @param minRange Minimum acceptable distance in meters (default: 0.0f)
     *  @param maxRange Maximum acceptable distance in meters (default: 100.0f)
     *  @return Return true if the point is valid, false otherwise
     */
    bool isValidPoint(const Lidar::PolarPoint &point, float minRange = 0.0f, float maxRange = 100.0f);
}

#endif