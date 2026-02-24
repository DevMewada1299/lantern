#include <cstdint>
#include <string>
#include <stdexcept>

namespace lantern {


    enum class DeviceType : uint8_t {
    CPU = 0,
    MPS = 1,
    };

    struct Device {
        DeviceType type;
        uint8_t index;

        constexpr Device() : type(DeviceType::CPU), index(0) {};
        constexpr Device(DeviceType t, uint8_t i) : type(t), index(i) {};

        static Device from_string(const std::string &s){
            if(s == "cpu"){
                return Device(DeviceType::CPU, 0);
            }
            if(s == "mps"){
                return Device(DeviceType::MPS, 1);
            }
            if(s.rfind("mps:",0) == 0){
               return Device(DeviceType::MPS, std::stoi(s.substr(4)));
            }
            throw std::invalid_argument("Unknow Device : " +  s);

        }

        bool is_mps() const {
            return type == DeviceType::MPS;
        };

        bool is_cpu() const {
            return type == DeviceType::CPU;
        }

        bool operator==(const Device& device) const {
            return type == device.type && index == device.index;

        }

        bool operator!=(const Device& device) const {
            return !(*this==device);
        }

        std::string str() const {
            switch(type){
                case DeviceType::CPU : return "CPU";
                case DeviceType::MPS : return "MPS";
            }
            return "unknown";
        }
    };

    inline constexpr Device kCPU { DeviceType::CPU, 0 };
    inline constexpr Device kMPS { DeviceType::MPS, 1 };


};