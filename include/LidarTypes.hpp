#ifndef LIDAR_TYPES_HPP
#define LIDAR_TYPES_HPP


namespace Lidar {
    struct PolarPoint {
        float p;
        float angle;
    };

    struct alignas(16) Point2D { //Dejamos 8 bytes de padding para asegurar que se haga un único acceso a memoria
        float x;
        float y;
    };
}

#endif