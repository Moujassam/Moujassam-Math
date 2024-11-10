#include <experimental/simd>
#include <iostream>
#include "Moujassam-math.hpp"
using namespace std::experimental::parallelism_v2;

int main() {
    // Native SIMD width
    simd<float, simd_abi::native<float>> native_simd;
    std::cout << "Native SIMD size: " << native_simd.size() << std::endl;

    // Fixed SIMD width of 4
    simd<float, simd_abi::fixed_size<4>> fixed_simd;
    std::cout << "Fixed SIMD size: " << fixed_simd.size() << std::endl;

    return 0;
}