#include "logger.hpp"

#include <spdlog/common.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace WindGB {

std::shared_ptr<spdlog::logger> g_logger = nullptr;

void Logger::init(const std::string& path) {
    if (g_logger != nullptr) {
        LOG_WARN("Logger already initialized.");
        return;
    }

    // Configure sinks
    std::vector<spdlog::sink_ptr> sinks;

#ifndef NDEBUG
    const auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    console_sink->set_level(spdlog::level::trace);
    console_sink->set_pattern("[%^%l%$] %v");
    sinks.push_back(console_sink);
#endif

    if (!path.empty()) {
        const auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(path, true);  // true = append
        file_sink->set_level(spdlog::level::info);
        file_sink->set_pattern("[%^%l%$] %v");
        sinks.push_back(file_sink);
    }

    g_logger = std::make_shared<spdlog::logger>("Luma logger", sinks.begin(), sinks.end());

    LOG_INFO("Logger initialized.");
}

spdlog::logger& Logger::get() {
    if (g_logger == nullptr) {
        throw std::runtime_error("Trying to get an initialized logger.");
    }

    return *g_logger;
}

}  // namespace WindGB