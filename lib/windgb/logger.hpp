#pragma once

#include <spdlog/spdlog.h>

namespace WindGB {

class Logger {
   public:
    static void init(const std::string& path = {});

    static spdlog::logger& get();
};

}  // namespace WindGB

#define LOG_TRACE(...) ::WindGB::Logger::get().trace(__VA_ARGS__)
#define LOG_DEBUG(...) ::WindGB::Logger::get().debug(__VA_ARGS__)
#define LOG_INFO(...) ::WindGB::Logger::get().info(__VA_ARGS__)
#define LOG_WARN(...) ::WindGB::Logger::get().warn(__VA_ARGS__)
#define LOG_ERROR(...) ::WindGB::Logger::get().error(__VA_ARGS__)
#define LOG_CRITICAL(...) ::WindGB::Logger::get().critical(__VA_ARGS__)