// Convertidor de Puntos de un sistema LiDAR de polares a Cartesianas

#include "LookUpTable.hpp"
#include "CircularBuffer.hpp"
#include <iostream>
#include <vector>

struct PolarPoint {
    float p;
    float angle;
};

struct alignas(16) Point2D { //Dejamos 8 bytes de padding para asegurar que se haga un único acceso a memoria
    float x;
    float y;
};

class LidarConverter {
    private:
        inline static const LookUpTable<1440>  lut;

    public:
        LidarConverter() = default;

        /** @brief Convertir el punto LiDAR de coordenadas Polares a coordenadas Cartesianas
         *  @param polar Es la estructura de datos de Puntos Polares
         */

        Point2D convert(const PolarPoint &polar) const {
            return {
                polar.p * lut.cos(polar.angle),
                polar.p * lut.sin(polar.angle)
            };
        }

        /** @brief Convertir una ráfaga de Puntos LiDAR Polares en un vector de puntos LiDAR Cartesianos
         *  @param input Buffer Circular que contiene los puntos en polares
         *  @param output Vector que almacena todos los puntos en cartesianas
         */
        template <size_t Capacity>
        void convertBatch(CircularBuffer<PolarPoint, Capacity> &input, std::vector<Point2D> &output) {
            output.reserve(output.size() + input.size());

            while(!input.isEmpty()) {
                auto polar_point = input.pop();
                if (polar_point.has_value()) {
                    output.push_back(convert(polar_point.value()));
                } 

            }

        }
};