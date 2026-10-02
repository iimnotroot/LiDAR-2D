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

        for (size_t i = 0; i < max_points; ++i) {
            Lidar::PolarPoint point = Lidar::PolarPoint{
                range_p(rng),
                range_angle(rng)
            };
            if (!LidarUtils::isValidPoint(point)) {
                continue;
            }
            vector.push_back(point);
            if (i>99990) {
                std::cout << "[!] New Polar Point gen " << vector[i].p << "m  " << vector[i].angle << "º " << i + 1 << "/" << max_points << "\n";
            }
        }
    }

    bool isValidPoint(const Lidar::PolarPoint &point, float minRange = 0.0f, float maxRange = 100.0f) {
        const bool isDistanceValid = (point.p >= minRange) && (point.p <= maxRange);
        const bool isAngleValid    = (point.angle >= 0.0f) && (point.angle <= 360.0f);

        return isDistanceValid && isAngleValid;
    }
}

