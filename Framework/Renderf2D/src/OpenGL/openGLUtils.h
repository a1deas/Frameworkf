#pragma once

#include <cstdint>

#include "glad/glad.h"

namespace Ff
{
    inline uint32_t getCurrentGLBinding(uint32_t type)
    {
        GLint out;
        glGetIntegerv(type, &out);
        return static_cast<uint32_t>(out);
    }
}