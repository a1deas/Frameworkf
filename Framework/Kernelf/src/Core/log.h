#pragma once

#include "spdlog/spdlog.h"

namespace Ff
{
    class Log
    {
    public:
        Log(const std::string& loggerName);

        inline static std::shared_ptr<spdlog::logger>& getLogger() { return fLogger; }

    private:
        static std::shared_ptr<spdlog::logger> fLogger;
    };
} // namespace Ff

//Log macros
#define FFTRACE(...) Ff::Log::getLogger()->trace(__VA_ARGS__)
#define FFINFO(...) Ff::Log::getLogger()->info(__VA_ARGS__)
#define FFWARN(...) Ff::Log::getLogger()->warn(__VA_ARGS__)
#define FFERROR(...) Ff::Log::getLogger()->error(__VA_ARGS__)
#define FFFATAL(...) Ff::Log::getLogger()->critical(__VA_ARGS__)

#define FFABORT(...)      \
    FFERROR(__VA_ARGS__); \
    abort()