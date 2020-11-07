#include "Logger.h"

#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"

#include <chrono>

namespace Covid
{
    typedef spdlog::sinks::basic_file_sink_mt FileSink;

    std::shared_ptr<spdlog::logger> Logger::s_EngineLogger;
    std::shared_ptr<spdlog::logger> Logger::s_Logger;

    void Logger::Init()
    {
       std::shared_ptr<FileSink> filesink = std::make_shared<FileSink>("logs/covid.log");
       spdlog::flush_every(std::chrono::seconds(5));

       s_EngineLogger = spdlog::stdout_color_mt("COVID");
       s_EngineLogger->sinks().push_back(filesink);
       s_EngineLogger->set_level(spdlog::level::trace);
       s_EngineLogger->set_pattern("%^[%T] %n: %v%$");

       s_Logger = spdlog::stdout_color_mt("INFECTED");
       s_Logger->sinks().push_back(filesink);
       s_Logger->set_level(spdlog::level::trace);
       s_Logger->set_pattern("%^[%T] %n: %v%$");
    }

    void Logger::Terminate()
    {
        spdlog::shutdown();
    }
}