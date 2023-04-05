#include <iostream>
#include <variant>

#include "constshader.h"

int main()
{    
     auto shader = cs::shader()
        .layout_location(0, cs::in, cs::_vec3, "inPos")
        .layout_location(1, cs::in, cs::_vec3, "inColor")
        .layout_binding(0,
        {
            cs::var(cs::_mat4,"projectionMatrix"),
            cs::var(cs::_mat4,"modelMatrix"),
            cs::var(cs::_mat4,"viewMatrix")
        }, "ubo")
        .layout_location(0, cs::out, cs::_vec3, "outColor")
        .layout_builtin(spv::BuiltInPosition, cs::out, cs::_vec4, "gl_Position");

    auto test = spv::BuiltInPosition;

    std::cout << "Hello World" << std::endl;
}