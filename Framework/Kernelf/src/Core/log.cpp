#include "log.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Ff
{
    Log::Log(const std::string& loggerName)
    {
        spdlog::set_pattern("%^ -> [%n: %v%$]");
        m_Logger = spdlog::stdout_color_mt(loggerName);
    }

    std::shared_ptr<spdlog::logger> Log::m_Logger;
} // namespace Ff