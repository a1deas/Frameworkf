#include "Core/log.h"
#include "glad/glad.h"
#include "shaderProgram.h"
#include "graphicsContext.h"
#include "OpenGL/shaderProgramOGL.h"

namespace Ff
{
    std::shared_ptr<ShaderProgram> ShaderProgram::create(const ShaderProgramSpec& spec)
    {
        switch (gRenderAPI)
        {
            case RenderAPI::OpenGL:
                return std::make_shared<ShaderProgramOGL>(spec);
            case RenderAPI::None:
                FFABORT("UNKNOWN RENDERAPI");
        }
        return nullptr;
    }

} // namespace Ff