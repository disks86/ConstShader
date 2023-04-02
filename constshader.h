#pragma once

#include <vector>
#include <map>
#include <initializer_list>
#include <variant>

#ifdef __linux__ 
#include <vulkan/vulkan.hpp>
#include <vulkan/vk_sdk_platform.h>
#include <spirv/1.2/spirv.hpp>
#include <spirv/1.2/GLSL.std.450.h>
#elif _WIN32
#include <vulkan/vulkan.hpp>
#include <vulkan/vk_platform.h>
#include <spirv-headers/spirv.hpp>
#include <spirv-headers/GLSL.std.450.h>
#else

#endif

#define PACK(c0, c1, c2, c3) \
    (((uint32_t)(uint8_t)(c0) << 24) | \
    ((uint32_t)(uint8_t)(c1) << 16) | \
    ((uint32_t)(uint8_t)(c2) << 8) | \
    ((uint32_t)(uint8_t)(c3)))

/*
Generator's magic number. It is associated with the tool that generated
the module. Its value does not affect any semantics, and is allowed to be 0.
Using a non-0 value is encouraged, and can be registered with
Khronos at https://www.khronos.org/registry/spir-v/api/spir-v.xml.
*/
#define SPIR_V_GENERATORS_NUMBER 0x00000000

namespace cs
{    
    enum parameter_direction
    {
        in=0,
        out=1
    };

    enum data_type
    {
        _bool=0,
        _int=1,
        _uint=2,
        _float=3,
        _double=4,
        _bvec2=5,
        _bvec3=6,
        _bvec4=7,
        _ivec2=8,
        _ivec3=9,
        _ivec4=10,
        _uvec2=11,
        _uvec3=12,
        _uvec4=13,
        _vec2=14,
        _vec3=15,
        _vec4=16,
        _dvec2=17,
        _dvec3=18,
        _dvec4=19,
        _mat2=20,
        _mat3=21,
        _mat4=22
    };

    struct layout_location_chunk
    {
        size_t mLocation;
        parameter_direction mDirection;
        data_type mType;
        std::string mName;

        layout_location_chunk(size_t location, parameter_direction direction, data_type type, const std::string& name)
         : mLocation(location), mDirection(direction), mType(type), mName(name)
        {
            //TODO: implement
        }

        layout_location_chunk(const layout_location_chunk &obj)
            : mLocation(obj.mLocation), mDirection(obj.mDirection), mType(obj.mType), mName(obj.mName)
        {
            
        }

        layout_location_chunk(layout_location_chunk &&obj)
            : mLocation(obj.mLocation), mDirection(obj.mDirection), mType(obj.mType), mName(obj.mName)
        { 
            
        }

    };

    using shader_chunk = std::variant<std::monostate, layout_location_chunk>;

    class shader
        : public std::vector<shader_chunk>
    {
        private:
        uint32_t mNextId = 1;
        inline uint32_t GetNextId()
        {
            return mNextId++;
        }

        inline void SkipIds(uint32_t numberToSkip)
        {
            mNextId += numberToSkip;
        }

        std::vector<uint32_t> mFunctionDefinitionInstructions;
        template<typename... Args>
        inline void Push(spv::Op code, Args... args)
        {
            Push(code, args...);
        }

        template <class T>
        inline void Push(spv::Op code, std::initializer_list<T> arguments)
        {
            mFunctionDefinitionInstructions.push_back(Pack(arguments.size()+1, code)); //size,Type
            for(auto argument : arguments)
            {
                mFunctionDefinitionInstructions.push_back(argument);
            }
        }

        public:

        inline shader& layout_location(size_t location, parameter_direction direction, data_type type, const std::string& name)
        {
            this->emplace_back(layout_location_chunk(location, direction, type, name));
            return (*this);
        }

        inline vk::UniqueShaderModule Compile(vk::Device& device)
        {
            //TODO: implement module construction
            return {};
        }
    };
}