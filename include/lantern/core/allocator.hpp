#pragma once
#include <cstddef>
#include <cstdlib>
#include <stdexcept>
#include <string>
#include "device.hpp"

namespace lantern{

    class Allocator{
        public:
            virtual ~Allocator() = default;
            virtual void* allocate(size_t nbytes) = 0;
            virtual void deallocate(void *ptr) = 0;
            virtual Device device() const = 0;
            virtual std::string name() const = 0;
    };

    class CPUAllocator final : public Allocator{
    public:
            void* allocate(size_t nbytes) override {

                if (nbytes == 0){
                    return nullptr;
                }

                void* ptr = nullptr;

                int err = posix_memalign(&ptr, 64, nbytes);

                if (err != 0 || ptr == nullptr){
                    throw std::bad_alloc();
                }

                return ptr;
            }

            void deallocate(void* ptr) override {
                ::free(ptr);
            }

            Device device() const override { return kCPU; }

            std::string name() const override { return  "CPUAllocator";}

            static CPUAllocator& instance() {
                static CPUAllocator alloc;
                return alloc;
            };

    private:
            CPUAllocator() = default;
    };

}