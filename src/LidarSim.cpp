#include <chrono>
#include <iostream>
#include <random>
#include <vector>
#include "LidarConverter.hpp"
#include "CircularBuffer.hpp"
#include <thread>
#include "LidarTypes.hpp"
#include "LidarUtils.hpp"

constexpr size_t MAX_POINTS = 100000;
constexpr size_t BUFFER_CAP = 1024;



void points_to_buff(Lidar::CircularBuffer<Lidar::PolarPoint, BUFFER_CAP> &buffer, const std::vector<Lidar::PolarPoint> &polarPoints )  {
    size_t last_idx = 0;
    
    while (true) {
        if (last_idx >= MAX_POINTS) { break; }
        buffer.push(polarPoints[last_idx]);
        std::cout << "Polar Point added to Circular Buffer! " << last_idx << " p: " << polarPoints[last_idx].p << " angle: " << polarPoints[last_idx].angle << " \n";
        last_idx += 1;
    }

    buffer.close();

    std::cout << "[!] Circular Buffer finished! " << "\n";
}

constexpr size_t BLOCK_SIZE = 256;

void polar_to_cart(Lidar::CircularBuffer<Lidar::PolarPoint, BUFFER_CAP> &buffer, std::vector<Lidar::Point2D> &cartPoints) {
    Lidar::LidarConverter lc;
    cartPoints.reserve(MAX_POINTS);

    std::vector<Lidar::PolarPoint> block;
    block.reserve(BLOCK_SIZE);
    
    while (true) {

        size_t n = buffer.blockPop(block, BLOCK_SIZE);

        if (n == 0) {
            break;        }

        for (size_t i = 0; i < n; ++i) {
            cartPoints.push_back(lc.convert(block[i]));
        }
    }

    std::cout << "[!] Cartesian Points added! " << cartPoints.size() << "\n";
    size_t idx = 99990;

    while (idx < MAX_POINTS) {
        std::cout << "[+] Cartesian Point: " << idx + 1 << " x: " << cartPoints[idx].x << " y: " << cartPoints[idx].y << "\n";
        idx += 1;
    }

}


int main() {

    std::vector<Lidar::PolarPoint> polarPoints;

    std::cout << "[1/3] Generating LiDAR Polar Points...\n";

    LidarUtils::generatePolarPoints(polarPoints, MAX_POINTS);

    Lidar::CircularBuffer<Lidar::PolarPoint, BUFFER_CAP> buffer;

    std::vector<Lidar::Point2D> cartPoints;

    std::cout << "[2/3] Trying to pass from LiDAR Polar Points to LiDAR Cartesian Points...\n";
    
    std::thread th1(points_to_buff, std::ref(buffer), std::cref(polarPoints));
    std::thread th2(polar_to_cart, std::ref(buffer), std::ref(cartPoints));

    th1.join();
    th2.join();

    return EXIT_SUCCESS;
}