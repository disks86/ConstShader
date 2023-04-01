#pragma once

#include <vector>
#include <unordered_map>
#include <map>
#include <stack>
#include <memory>
#include <fstream>
#include <iostream>
#include <string>
#include <initializer_list>

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

    class shader
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

        template<typename... Args>
        void Push(spv::Op code, Args... args)
        {
            Push(code, args...);
        }

        template <class T>
        inline void Push(spv::Op code, std::initializer_list<T> arguments)
        {
            mFunctionDefinitionInstructions.push_back(Pack(arguments.size()+1, code)); //size,Type
            for( auto argument : arguments )
            {
                mFunctionDefinitionInstructions.push_back(argument1);
            }
        }

        public:
        constexpr shader()
        {

        }

        inline vk::UniqueShaderModule Compile(vk::Device& device)
        {
            //TODO: implement module construction
            return {};
        }
    };

}