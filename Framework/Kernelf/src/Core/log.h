#pragma once

#include "spdlog/spdlog.h"

namespace Ff
{
    /**
     * Logger that reports different types of messages in the console.
     */
    class Log
    {
    public:
        /**
         * Create logger.
         * @param loggerName logger's name.
         */
        Log(const std::string& loggerName);

        /** Get logger for further certain operations. */
        inline static std::shared_ptr<spdlog::logger>& getLogger() { return m_Logger; }

    private:
        static std::shared_ptr<spdlog::logger> m_Logger;
    };
} // namespace Ff

/** Grey trace log message, lowest level of importance. */
#define FFTRACE(...) Ff::Log::getLogger()->trace(__VA_ARGS__)
/** Green info log message. */
#define FFINFO(...) Ff::Log::getLogger()->info(__VA_ARGS__)
/** Yellow warning log message. */
#define FFWARN(...) Ff::Log::getLogger()->warn(__VA_ARGS__)
/** Red error log message. */
#define FFERROR(...) Ff::Log::getLogger()->error(__VA_ARGS__)
/** Red critical error message with the red background. */
#define FFFATAL(...) Ff::Log::getLogger()->critical(__VA_ARGS__)

/** Error log message that closes the application. */
#define FFABORT(...)      \
    FFERROR(__VA_ARGS__); \
    abort()

/** Error log message that closes the application with the certain condition. */
#define FFASSERT(condition)      \
    do                           \
    {                            \
        if (!(condition))        \
        {                        \
            FFABORT(#condition); \
        }                        \
    }                            \
    while (false)