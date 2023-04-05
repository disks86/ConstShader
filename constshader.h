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

    struct type_definition;
    struct var;

    struct type_definition
        : std::vector<var>
    {

    };

    struct var
    {
        std::variant<data_type, type_definition> mType;
        std::string mName;

        var(data_type type, const std::string& name)
         : mType(type), mName(name)
        {
            
        }

        var(type_definition type, const std::string& name)
         : mType(type), mName(name)
        {
            
        }

        var(data_type type)
         : mType(type)
        {
            
        }

        var(type_definition type)
         : mType(type)
        {
            
        }

        var(const var &obj)
            : mType(obj.mType), mName(obj.mName)
        {
            
        }

        var(var &&obj)
            : mType(obj.mType), mName(obj.mName)
        { 
            
        }
    };

    struct layout_location_chunk
    {
        size_t mLocation;
        parameter_direction mDirection;
        type_definition mType;
        std::string mName;

        layout_location_chunk(size_t location, parameter_direction direction, type_definition type, const std::string& name)
         : mLocation(location), mDirection(direction), mType(type), mName(name)
        {
 
        }

        layout_location_chunk(size_t location, parameter_direction direction, std::initializer_list<var> type, const std::string& name)
         : mLocation(location), mDirection(direction), mName(name)
        {
            mType.append_range(type);
        }

        layout_location_chunk(size_t location, parameter_direction direction, data_type type, const std::string& name)
         : mLocation(location), mDirection(direction), mName(name)
        {
            mType.emplace_back(type);
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

    struct layout_binding_chunk
    {
        size_t mBinding;
        parameter_direction mDirection;
        type_definition mType;
        std::string mName;

        layout_binding_chunk(size_t binding, type_definition type, const std::string& name)
         : mBinding(binding), mType(type), mName(name)
        {
        }

        layout_binding_chunk(size_t binding, std::initializer_list<var> type, const std::string& name)
         : mBinding(binding), mName(name)
        {
            mType.append_range(type);
        }

        layout_binding_chunk(size_t binding, data_type type, const std::string& name)
         : mBinding(binding), mName(name)
        {
            mType.emplace_back(type);
        }

        layout_binding_chunk(const layout_binding_chunk &obj)
            : mBinding(obj.mBinding), mType(obj.mType), mName(obj.mName)
        {
            
        }

        layout_binding_chunk(layout_binding_chunk &&obj)
            : mBinding(obj.mBinding), mType(obj.mType), mName(obj.mName)
        { 
            
        }

    };

    struct layout_builtin_chunk
    {
        spv::BuiltIn mBuiltIn;
        parameter_direction mDirection;
        type_definition mType;
        std::string mName;

        layout_builtin_chunk(spv::BuiltIn builtIn, parameter_direction direction, type_definition type, const std::string& name)
         : mBuiltIn(builtIn), mDirection(direction), mType(type), mName(name)
        {
 
        }

        layout_builtin_chunk(spv::BuiltIn builtIn, parameter_direction direction, std::initializer_list<var> type, const std::string& name)
         : mBuiltIn(builtIn), mDirection(direction), mName(name)
        {
            mType.append_range(type);
        }

        layout_builtin_chunk(spv::BuiltIn builtIn, parameter_direction direction, data_type type, const std::string& name)
         : mBuiltIn(builtIn), mDirection(direction), mName(name)
        {
            mType.emplace_back(type);
        }

        layout_builtin_chunk(const layout_builtin_chunk &obj)
            : mBuiltIn(obj.mBuiltIn), mDirection(obj.mDirection), mType(obj.mType), mName(obj.mName)
        {
            
        }

        layout_builtin_chunk(layout_builtin_chunk &&obj)
            : mBuiltIn(obj.mBuiltIn), mDirection(obj.mDirection), mType(obj.mType), mName(obj.mName)
        { 
            
        }

    };

    using shader_chunk = std::variant<std::monostate, layout_location_chunk, layout_binding_chunk, layout_builtin_chunk>;

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

        inline shader& layout_location(size_t location, parameter_direction direction, type_definition type, const std::string& name)
        {
            this->emplace_back(layout_location_chunk(location, direction, type, name));
            return (*this);
        }

        inline shader& layout_location(size_t location, parameter_direction direction, std::initializer_list<var> type, const std::string& name)
        {
            this->emplace_back(layout_location_chunk(location, direction, type, name));
            return (*this);
        }

        inline shader& layout_location(size_t location, parameter_direction direction, data_type type, const std::string& name)
        {
            this->emplace_back(layout_location_chunk(location, direction, type, name));
            return (*this);
        }

        inline shader& layout_binding(size_t binding, type_definition type, const std::string& name)
        {
            this->emplace_back(layout_binding_chunk(binding, type, name));
            return (*this);
        }

        inline shader& layout_binding(size_t binding, std::initializer_list<var> type, const std::string& name)
        {
            this->emplace_back(layout_binding_chunk(binding, type, name));
            return (*this);
        }

        inline shader& layout_binding(size_t binding, data_type type, const std::string& name)
        {
            this->emplace_back(layout_binding_chunk(binding, type, name));
            return (*this);
        }

        inline shader& layout_builtin(spv::BuiltIn builtIn, parameter_direction direction, type_definition type, const std::string& name)
        {
            this->emplace_back(layout_builtin_chunk(builtIn, direction, type, name));
            return (*this);
        }

        inline shader& layout_builtin(spv::BuiltIn builtIn, parameter_direction direction, std::initializer_list<var> type, const std::string& name)
        {
            this->emplace_back(layout_builtin_chunk(builtIn, direction, type, name));
            return (*this);
        }

        inline shader& layout_builtin(spv::BuiltIn builtIn, parameter_direction direction, data_type type, const std::string& name)
        {
            this->emplace_back(layout_builtin_chunk(builtIn, direction, type, name));
            return (*this);
        }

        inline vk::UniqueShaderModule Compile(vk::Device& device)
        {
            //TODO: implement module construction
            return {};
        }
    };
}