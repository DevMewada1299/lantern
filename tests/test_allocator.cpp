// test_allocator.cpp (in root directory)
#include <iostream>
#include "include/lantern/core/allocator.hpp"

int main() {
    using namespace lantern;

    std::cout << "=== Allocator Tests ===\n\n";

    // Get the singleton instance
    auto& alloc = CPUAllocator::instance();
    std::cout << "Allocator name: " << alloc.name() << "\n";
    std::cout << "Allocator device: " << alloc.device().str() << "\n";

    // Allocate memory
    void* ptr = alloc.allocate(1024);
    std::cout << "Allocated 1024 bytes at: " << ptr << "\n";

    // Check alignment
    uintptr_t addr = reinterpret_cast<uintptr_t>(ptr);
    std::cout << "Address: 0x" << std::hex << addr << std::dec << "\n";
    std::cout << "64-byte aligned? " << (addr % 64 == 0 ? "YES" : "NO") << "\n";

    // Use the memory
    float* fptr = static_cast<float*>(ptr);
    fptr[0] = 3.14f;
    fptr[1] = 2.71f;
    std::cout << "Wrote: " << fptr[0] << ", " << fptr[1] << "\n";

    // Free memory
    alloc.deallocate(ptr);
    std::cout << "Memory freed\n";

    // Test singleton (same instance)
    auto& alloc2 = CPUAllocator::instance();
    std::cout << "Same instance? " << (&alloc == &alloc2 ? "YES" : "NO") << "\n";

    std::cout << "\n✅ All allocator tests passed!\n";
    return 0;
}