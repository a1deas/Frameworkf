#pragma once

#include <iostream>
#include "Core/types.h"
namespace Ff
{
    struct ShaderProgramSpec
    {
        Path vertexShaderPath;
        Path fragmentShaderPath;
        Path computeShaderPath;
    };

    class ShaderProgram
    {
    public:
        virtual ~ShaderProgram() = default;
        static std::shared_ptr<ShaderProgram> create(const ShaderProgramSpec& spec);
    };

} // namespace Ff