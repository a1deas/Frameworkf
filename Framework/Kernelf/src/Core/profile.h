#pragma once

#ifdef ENABLE_PROFILING
    #include "optick.h"

    #define FF_PROFILE_FRAME(name) OPTICK_FRAME(name)
    #define FF_PROFILE_SCOPE(...) OPTICK_EVENT(__VA_ARGS__)

#else
    #define FF_PROFILE_FRAME(name)
    #define FF_PROFILE_SCOPE(...)

#endif