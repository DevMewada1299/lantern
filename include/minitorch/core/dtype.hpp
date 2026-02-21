//
// Created by Dev Mewada on 2/20/26.
//

#ifndef DTYPE_HPP
#define DTYPE_HPP

#endif //DTYPE_HPP
#pragma once
#include <cstdint>
#include <cstddef>
#include <stdexcept>
#include <string>

namespace mt {
    enum class ScalarType : uint8_t {
        Float32  = 0,
        Float64  = 1,
        Float16  = 2,
        BFloat16 = 3,
        Int32    = 4,
        Int64    = 5,
        Int16    = 6,
        Int8     = 7,
        Bool     = 8,
        Undefined = 255,
    };

    constexpr size_t element_size(ScalarType t) {
        switch(t) {
            case ScalarType::Float64:
            case ScalarType::Int64:               return 8;
            case ScalarType::Float32:
            case ScalarType::Int32:               return 4;
            case ScalarType::Float16:
            case ScalarType::BFloat16:
            case ScalarType::Int16:               return 2;
            case ScalarType::Int8:
            case ScalarType::Bool:                return 1;
            default:                              return 0;
        }
    }

    inline std::string dtype_name(ScalarType t) {
        switch(t) {
            case ScalarType::Float32:  return "float32";
            case ScalarType::Float64:  return "float64";
            case ScalarType::Float16:  return "float16";
            case ScalarType::BFloat16: return "bfloat16";
            case ScalarType::Int32:    return "int32";
            case ScalarType::Int64:    return "int64";
            case ScalarType::Int16:    return "int16";
            case ScalarType::Int8:     return "int8";
            case ScalarType::Bool:     return "bool";
            default:                   return "undefined";
        }
    }

    template<ScalarType S>
struct ScalarTypeTrait;

    template<> struct ScalarTypeTrait<ScalarType::Float32>
    { using cpp_type = float;    static constexpr size_t size = 4; };
    template<> struct ScalarTypeTrait<ScalarType::Float64>
    { using cpp_type = double;   static constexpr size_t size = 8; };
    template<> struct ScalarTypeTrait<ScalarType::Int32>
    { using cpp_type = int32_t;  static constexpr size_t size = 4; };
    template<> struct ScalarTypeTrait<ScalarType::Int64>
    { using cpp_type = int64_t;  static constexpr size_t size = 8; };
    template<> struct ScalarTypeTrait<ScalarType::Int8>
    { using cpp_type = int8_t;   static constexpr size_t size = 1; };
    template<> struct ScalarTypeTrait<ScalarType::Bool>
    { using cpp_type = bool;     static constexpr size_t size = 1; };

    template<ScalarType S>
    using scalar_to_cpp_t = typename ScalarTypeTrait<S>::cpp_type;

}






