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
        _void=0,
        _bool=1,
        _int=2,
        _uint=3,
        _float=4,
        _double=5,
        _bvec2=6,
        _bvec3=7,
        _bvec4=8,
        _ivec2=9,
        _ivec3=10,
        _ivec4=11,
        _uvec2=12,
        _uvec3=13,
        _uvec4=14,
        _vec2=15,
        _vec3=16,
        _vec4=17,
        _dvec2=18,
        _dvec3=19,
        _dvec4=20,
        _mat2=21,
        _mat3=22,
        _mat4=23
    };

    struct type_definition;
    struct variable;
    struct expression;

    using operand = std::variant<variable,expression>;

    struct type_definition
        : std::vector<variable>
    {

    };

    struct variable
    {
        std::variant<std::monostate,data_type, type_definition> mType;
        std::string mName;

        inline variable()
        {
            
        }

        inline variable(const std::string& name)
         : mName(name)
        {
            
        }

        inline variable(data_type type, const std::string& name)
         : mType(type), mName(name)
        {
            
        }

        inline variable(type_definition& type, const std::string& name)
         : mType(type), mName(name)
        {
            
        }

        inline variable(data_type type)
         : mType(type)
        {
            
        }

        inline variable(type_definition& type)
         : mType(type)
        {
            
        }

        inline variable(const variable &obj)
            : mType(obj.mType), mName(obj.mName)
        {
            
        }

        inline variable(variable &&obj)
            : mType(obj.mType), mName(obj.mName)
        { 
            
        }

        inline void operator = (const variable &v) 
        { 
            mType = v.mType;
            mName = v.mName;
        }
    };

    struct expression
    {
        variable mResult;
        std::vector<variable> mArguments;
        spv::Op mOpCode;

        inline expression(std::initializer_list<variable> arguments)
         : mArguments(arguments)
        {

        }

        inline expression(variable result, std::initializer_list<variable> arguments)
         : mResult(result), mArguments(arguments)
        {
        }

        inline expression(const expression &obj)
            : mResult(obj.mResult), mArguments(obj.mArguments)
        {
            
        }

        inline expression(expression &&obj)
            : mResult(obj.mResult), mArguments(obj.mArguments)
        { 
            
        }

        inline expression& operator = (const expression &o) 
        { 
            mResult = mArguments.back();
            mArguments.pop_back();

            mArguments = o.mArguments;

            mOpCode = spv::OpStore;

            return (*this);
        }

    };

    expression var(const std::string& name)
    {
        return {variable(name)};
    }

    variable var(data_type type, const std::string& name)
    {
        return variable(type, name);
    }

    variable var(type_definition type, const std::string& name)
    {
        return variable(type, name);
    }

    struct layout_location_chunk
    {
        size_t mLocation;
        parameter_direction mDirection;
        type_definition mType;
        std::string mName;

        layout_location_chunk(size_t location, parameter_direction direction, type_definition& type, const std::string& name)
         : mLocation(location), mDirection(direction), mType(type), mName(name)
        {
 
        }

        layout_location_chunk(size_t location, parameter_direction direction, std::initializer_list<variable> type, const std::string& name)
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

        layout_binding_chunk(size_t binding, type_definition& type, const std::string& name)
         : mBinding(binding), mType(type), mName(name)
        {
        }

        layout_binding_chunk(size_t binding, std::initializer_list<variable> type, const std::string& name)
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

        layout_builtin_chunk(spv::BuiltIn builtIn, parameter_direction direction, type_definition& type, const std::string& name)
         : mBuiltIn(builtIn), mDirection(direction), mType(type), mName(name)
        {
 
        }

        layout_builtin_chunk(spv::BuiltIn builtIn, parameter_direction direction, std::initializer_list<variable> type, const std::string& name)
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

    struct function_chunk
    {
        type_definition mReturnType;
        std::string mName;
        std::vector<variable> mArguments;
        std::vector<expression> mExpressions;

        function_chunk(type_definition& returnType, const std::string& name, std::initializer_list<variable> arguments, std::initializer_list<expression> expressions)
         : mReturnType(returnType), mName(name), mArguments(arguments), mExpressions(expressions)
        {

        }

        function_chunk(std::initializer_list<variable> returnType, const std::string& name, std::initializer_list<variable> arguments, std::initializer_list<expression> expressions)
         : mName(name), mArguments(arguments), mExpressions(expressions)
        {
            mReturnType.append_range(returnType);
        }

        function_chunk(data_type returnType, const std::string& name, std::initializer_list<variable> arguments, std::initializer_list<expression> expressions)
         : mName(name), mArguments(arguments), mExpressions(expressions)
        {
            mReturnType.emplace_back(returnType);
        }

        function_chunk(const function_chunk &obj)
            : mReturnType(obj.mReturnType), mName(obj.mName), mArguments(obj.mArguments)
        {
            
        }

        function_chunk(function_chunk &&obj)
            : mReturnType(obj.mReturnType), mName(obj.mName), mArguments(obj.mArguments)
        { 
            
        }
    };

    using shader_chunk = std::variant<std::monostate, layout_location_chunk, layout_binding_chunk, layout_builtin_chunk, function_chunk>;

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

        inline shader& layout_location(size_t location, parameter_direction direction, type_definition& type, const std::string& name)
        {
            this->emplace_back(layout_location_chunk(location, direction, type, name));
            return (*this);
        }

        inline shader& layout_location(size_t location, parameter_direction direction, std::initializer_list<variable> type, const std::string& name)
        {
            this->emplace_back(layout_location_chunk(location, direction, type, name));
            return (*this);
        }

        inline shader& layout_location(size_t location, parameter_direction direction, data_type type, const std::string& name)
        {
            this->emplace_back(layout_location_chunk(location, direction, type, name));
            return (*this);
        }

        inline shader& layout_binding(size_t binding, type_definition& type, const std::string& name)
        {
            this->emplace_back(layout_binding_chunk(binding, type, name));
            return (*this);
        }

        inline shader& layout_binding(size_t binding, std::initializer_list<variable> type, const std::string& name)
        {
            this->emplace_back(layout_binding_chunk(binding, type, name));
            return (*this);
        }

        inline shader& layout_binding(size_t binding, data_type type, const std::string& name)
        {
            this->emplace_back(layout_binding_chunk(binding, type, name));
            return (*this);
        }

        inline shader& layout_builtin(spv::BuiltIn builtIn, parameter_direction direction, type_definition& type, const std::string& name)
        {
            this->emplace_back(layout_builtin_chunk(builtIn, direction, type, name));
            return (*this);
        }

        inline shader& layout_builtin(spv::BuiltIn builtIn, parameter_direction direction, std::initializer_list<variable> type, const std::string& name)
        {
            this->emplace_back(layout_builtin_chunk(builtIn, direction, type, name));
            return (*this);
        }

        inline shader& layout_builtin(spv::BuiltIn builtIn, parameter_direction direction, data_type type, const std::string& name)
        {
            this->emplace_back(layout_builtin_chunk(builtIn, direction, type, name));
            return (*this);
        }

        inline shader& function(type_definition& returnType, const std::string& name, std::initializer_list<variable> arguments, std::initializer_list<expression> expressions)
        {
            this->emplace_back(function_chunk(returnType, name, arguments, expressions));
            return (*this);
        }

        inline shader& function(std::initializer_list<variable>& returnType, const std::string& name, std::initializer_list<variable> arguments, std::initializer_list<expression> expressions)
        {
            this->emplace_back(function_chunk(returnType, name, arguments, expressions));
            return (*this);
        }

        inline shader& function(data_type returnType, const std::string& name, std::initializer_list<variable> arguments, std::initializer_list<expression> expressions)
        {
            this->emplace_back(function_chunk(returnType, name, arguments, expressions));
            return (*this);
        }

        inline vk::UniqueShaderModule Compile(vk::Device& device)
        {
            //TODO: implement module construction
            return {};
        }
    };
}