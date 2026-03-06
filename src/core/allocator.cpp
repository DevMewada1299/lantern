#include "../include/lantern/core/allocator.hpp"

namespace lantern {

    Allocator* get_allocator(Device device){

        switch (device.type) {
            case DeviceType::CPU:
                    return &CPUAllocator::instance();

            case DeviceType::MPS:
                throw std::runtime_error("MPS Allocator in works");
        }

        throw std::runtime_error("Unkown Device Type");
    }



}