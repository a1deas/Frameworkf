#pragma once

#include <iostream>
#include "Core/types.h"

namespace Ff
{
    /** Paths to different shaders. */
    struct ShaderProgramSpec
    {
        /** Path to the vertex shader. */
        Path vertexShaderPath;
        /** Path to the fragment(pixel) shader. */
        Path fragmentShaderPath;
        /** Path to the compute shader. */
        Path computeShaderPath;
    };

    class ShaderProgram
    {
    public:
        /** Specify shader program with the specific spec. */
        ShaderProgram(const ShaderProgramSpec& spec);
        /** Deletes shader program. */
        ~ShaderProgram();
        /** Factory that simplifies shader program creation. */
        static std::shared_ptr<ShaderProgram> create(const ShaderProgramSpec& spec);

        /** Returns shader program id. */
        uint32_t getId() const { return m_Id; }
        /** Returns uniform location. */
        int getUniformLocation(const char* name) const; // !

    private:
        static uint32_t createShaderProgram(const ShaderProgramSpec& spec);
        static uint32_t compileShader(uint32_t type, const std::string& source);

    private:
        mutable std::unordered_map<std::string, int> m_UniformLocations;
        uint32_t m_Id{};
    };

} // namespace Ff