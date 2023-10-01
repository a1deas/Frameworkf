#include "Core/log.h"
#include "shaderProgramOGL.h"
#include "glad/glad.h"
#include "FileSystem/file.h"

namespace Ff
{

    ShaderProgramOGL::ShaderProgramOGL(const ShaderProgramSpec& spec)
        : m_id(createShaderProgram(spec))
    {
    }

    ShaderProgramOGL::~ShaderProgramOGL()
    {
        if (m_id != 0)
            glDeleteProgram(m_id);
    }

    uint32_t ShaderProgramOGL::createShaderProgram(const ShaderProgramSpec& spec)
    {
        std::vector<uint32_t> shaders;
        if (!spec.vertexShaderPath.empty())
            shaders.push_back(compileShader(GL_VERTEX_SHADER, spec.vertexShaderPath.string()));
        if (!spec.fragmentShaderPath.empty())
            shaders.push_back(compileShader(GL_FRAGMENT_SHADER, spec.fragmentShaderPath.string()));
        if (!spec.computeShaderPath.empty())
            shaders.push_back(compileShader(GL_COMPUTE_SHADER, spec.computeShaderPath.string()));

        uint32_t program = glCreateProgram();

        for (uint32_t shader : shaders)
        {
            glAttachShader(program, shader);
        }

        // TODO: check link&validation status

        glLinkProgram(program);
        glValidateProgram(program);

        for (uint32_t shader : shaders)
        {
            glDetachShader(program, shader);
            glDeleteShader(shader);
        }

        return program;
    }

    uint32_t ShaderProgramOGL::compileShader(uint32_t type, const std::string& path)
    {
        unsigned int id     = glCreateShader(type);
        std::string  source = readFileToString(path);
        const char*  src    = source.c_str();
        glShaderSource(id, 1, &src, nullptr);
        glCompileShader(id);

        int result;
        glGetShaderiv(id, GL_COMPILE_STATUS, &result);

        if (result == GL_FALSE)
        {
            FFERROR("Failed to load {} shader(path: {})", type, path);
            glDeleteShader(id);
            return 0;
        }

        return id;
    }
} // namespace Ff