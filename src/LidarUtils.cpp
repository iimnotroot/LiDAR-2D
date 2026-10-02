#include "LidarUtils.hpp"
#include "LidarTypes.hpp"
#include <random>
#include <iostream>

namespace LidarUtils {

    void generatePolarPoints(std::vector<Lidar::PolarPoint> &vector, size_t max_points) {
        vector.reserve(max_points);
        
        std::random_device rd;
        std::mt19937 rng(rd());

        std::uniform_real_distribution<float> range_p(0.0, 100.0); // Ro va entre 0 y 100 metros
        std::uniform_real_distribution<float> range_angle(0.0, 360.0); // Angulo entre 0 y 360 grados

        size_t generated = 0;
        while (generated <= max_points) {
            Lidar::PolarPoint point = Lidar::PolarPoint{
                range_p(rng),
                range_angle(rng)
            };
            if (!LidarUtils::isValidPoint(point, 0.0f, 100.0f)) {
                continue;
            }
            vector.push_back(point);
            generated++;
        }
    }

    bool isValidPoint(const Lidar::PolarPoint &point, float minRange, float maxRange) {
        const bool isDistanceValid = (point.p >= minRange) && (point.p <= maxRange);
        const bool isAngleValid    = (point.angle >= 0.0f) && (point.angle <= 360.0f);

        return isDistanceValid && isAngleValid;
    }
}

