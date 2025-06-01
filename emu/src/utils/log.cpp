#include "log.h"

#include <spdlog/sinks/basic_file_sink.h>

std::shared_ptr<spdlog::logger> Log::s_Logger = nullptr;

void Log::Init(const std::string& path) {
    if (s_Logger != nullptr) {
        LOG_ERROR("Doctor logger already initialized.");
        return;
    }

    std::vector<spdlog::sink_ptr> sinks;
    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    console_sink->set_level(spdlog::level::debug);
    console_sink->set_pattern("[%^%l%$] %v");
    sinks.push_back(console_sink);

    if (!path.empty()) {
        auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(path, true);  // true = append
        file_sink->set_level(spdlog::level::trace);
        file_sink->set_pattern("[%^%l%$] %v");
        sinks.push_back(file_sink);
    }

    s_Logger = std::make_shared<spdlog::logger>("WindGB", sinks.begin(), sinks.end());
    s_Logger->set_level(spdlog::level::trace);
    s_Logger->flush_on(spdlog::level::info);

    spdlog::register_logger(s_Logger);
}

void Log::Disable() {
    for (auto& sink : s_Logger->sinks()) {
        sink->set_level(spdlog::level::off);
    }
}
