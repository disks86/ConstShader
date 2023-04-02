#include <iostream>
#include <variant>

#include "constshader.h"

int main()
{    
     auto shader = cs::shader()
        .layout_location(0, cs::in, cs::_vec3, "inPos")
        .layout_location(1, cs::in, cs::_vec3, "inColor");

    std::cout << "Hello World" << std::endl;
}