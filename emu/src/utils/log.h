#pragma once

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

#include <memory>

class Log {
   public:
    static void Init(const std::string& path = {});

    static std::shared_ptr<spdlog::logger>& Get() { return s_Logger; }

    static void Disable();

   private:
    static std::shared_ptr<spdlog::logger> s_Logger;
};

#define LOG_TRACE(...) ::Log::Get()->trace(__VA_ARGS__)
#define LOG_DEBUG(...) ::Log::Get()->debug(__VA_ARGS__)
#define LOG_INFO(...) ::Log::Get()->info(__VA_ARGS__)
#define LOG_WARN(...) ::Log::Get()->warn(__VA_ARGS__)
#define LOG_ERROR(...) ::Log::Get()->error(__VA_ARGS__)
#define LOG_CRITICAL(...) ::Log::Get()->critical(__VA_ARGS__)