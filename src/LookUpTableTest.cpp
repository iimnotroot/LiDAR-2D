#include "LookUpTable.hpp"
#include <iostream>

int main() {

    LookUpTable lut;

    std::cout << lut.cos(360) << "\n";
    std::cout << lut.cos(0) << "\n";
    std::cout << lut.cos(0.56) << "\n";
    std::cout << lut.cos(-180) << "\n";
    std::cout << lut.sin(360) << "\n";
    std::cout << lut.sin(0) << "\n";
    std::cout << lut.sin(0.56) << "\n";
    std::cout << lut.sin(-180) << "\n";

    return EXIT_SUCCESS;
}