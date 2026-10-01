// LookUpTable (LUT) para almacenar calculos trigonométricos para reducir el coste de CPU pasar de coordenadas Polares a Cartesianas

#include <array>
#include <cmath>


template <size_t ResolutionSteps = 1440> // 1440 entradas = resolución de 0.25º
class LookUpTable {
    private:
        std::array<float, ResolutionSteps> cos_table;
        std::array<float, ResolutionSteps> sin_table;

        static constexpr float DEG_TO_INDEX = static_cast<float>(ResolutionSteps) / 360.0; 

        float rad_converter(size_t input) const {
            float value = static_cast<float>(input) / DEG_TO_INDEX;
            return value * (M_PI/180);
        }
        size_t getIndex(float angle_deg) const {

            float norm_deg = std::fmod(angle_deg, 360.0f); //Normalización del ángulo [0.0, 360.0)

            if (norm_deg < 0.0f) {
                norm_deg += 360.0f;
            }


            size_t index = static_cast<size_t>(norm_deg * DEG_TO_INDEX);
            return index % ResolutionSteps;
        }

    public:
        LookUpTable() {

            for (size_t i = 0; i < ResolutionSteps; ++i) {
                float angle_rad = rad_converter(i);
                cos_table[i] = std::cos(angle_rad);
                sin_table[i] = std::sin(angle_rad);
            }
        }

        float cos(float angle_deg) const {
            return cos_table[getIndex(angle_deg)];
        }

        float sin(float angle_deg) const {
            return sin_table[getIndex(angle_deg)];
        }
};