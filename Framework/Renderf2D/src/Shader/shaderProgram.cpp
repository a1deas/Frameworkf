#include "Core/log.h"
#include "glad/glad.h"
#include "shaderProgram.h"
#include "graphicsContext.h"
#include "Shader/shaderProgram.h"
#include "FileSystem/file.h"

namespace Ff
{

    ShaderProgram::ShaderProgram(const ShaderProgramSpec& spec)
        : m_id(createShaderProgram(spec))
    {
    }

    ShaderProgram::~ShaderProgram()
    {
        if (m_id != 0)
            glDeleteProgram(m_id);
    }

    std::shared_ptr<ShaderProgram> ShaderProgram::create(const ShaderProgramSpec& spec)
    {
        switch (gRenderAPI)
        {
            case RenderAPI::OpenGL:
                return std::make_shared<ShaderProgram>(spec);
            case RenderAPI::None:
                FFABORT("UNKNOWN RENDERAPI");
        }
        return nullptr;
    }

    //Ultimate super mega grande common optimization for getUniformLocation();
    int ShaderProgram::getUniformLocation(const char* name) const
    {
        if (m_uniformLocations.contains(name))
            return m_uniformLocations[name];
        int location = glGetUniformLocation(m_id, name);
        if (location == -1)
        {
            FFWARN("Failed to find uniform location for: {}", name);
            return -1;
        }
        m_uniformLocations[name] = location;
        return location;
    }

    uint32_t ShaderProgram::createShaderProgram(const ShaderProgramSpec& spec)
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

    uint32_t ShaderProgram::compileShader(uint32_t type, const std::string& path)
    {
        unsigned int id = glCreateShader(type);
        std::string source = readFileToString(path);
        const char* src = source.c_str();
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