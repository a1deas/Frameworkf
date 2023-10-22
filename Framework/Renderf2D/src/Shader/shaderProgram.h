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
        ShaderProgram(const ShaderProgramSpec& spec);
        ~ShaderProgram();
        static std::shared_ptr<ShaderProgram> create(const ShaderProgramSpec& spec);

        uint32_t getId() const { return m_id; }
        int getUniformLocation(const char* name) const;

    private:
        static uint32_t createShaderProgram(const ShaderProgramSpec& spec);
        static uint32_t compileShader(uint32_t type, const std::string& source);

    private:
        mutable std::unordered_map<std::string, int> m_uniformLocations;
        uint32_t m_id{};
    };

} // namespace Ff