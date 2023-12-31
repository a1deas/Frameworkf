#pragma once
#include <unordered_map>

#include "Shader/shaderProgram.h"

namespace Ff
{
    class ShaderProgramOGL : public ShaderProgram
    {
    public:
        ShaderProgramOGL(const ShaderProgramSpec& spec);
        ~ShaderProgramOGL();

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