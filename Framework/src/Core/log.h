#pragma once

#include "spdlog/spdlog.h"

#define FFTRACE(...) SPDLOG_TRACE(__VA_ARGS__)
#define FFINFO(...) SPDLOG_INFO(__VA_ARGS__)
#define FFWARN(...) SPDLOG_WARN(__VA_ARGS__)
#define FFERROR(...) SPDLOG_ERROR(__VA_ARGS__)
#define FFCRIT(...) SPDLOG_CRITICAL(__VA_ARGS__)