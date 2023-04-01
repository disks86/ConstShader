#include <iostream>

#include "constshader.h"

int main()
{
    constexpr auto test = cs::shader();

    std::cout << "Hello World" << std::endl;
}