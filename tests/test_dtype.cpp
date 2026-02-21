// test_dtype_simple.cpp (in the root directory for now)
#include <iostream>
#include "minitorch/core/dtype.hpp"

int main() {
    using namespace mt;

    // Test 1: element_size at compile time
    constexpr size_t f32_size = element_size(ScalarType::Float32);
    std::cout << "Float32 size (compile-time): " << f32_size << "\n";

    // Test 2: element_size at runtime
    ScalarType t = ScalarType::Float64;
    std::cout << "Float64 size (runtime): " << element_size(t) << "\n";

    // Test 3: dtype names
    std::cout << "Float32 name: " << dtype_name(ScalarType::Float32) << "\n";
    std::cout << "Int64 name: " << dtype_name(ScalarType::Int64) << "\n";

    // Test 4: type traits
    using F32Type = scalar_to_cpp_t<ScalarType::Float32>;
    F32Type value = 3.14f;
    std::cout << "Type trait test, value: " << value << "\n";

    return 0;
}