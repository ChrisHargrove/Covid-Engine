#pragma once

#include "spdlog/spdlog.h"
#include <memory>
#include <string>

namespace Covid
{
    class Logger
    {
    public:
        
        static void Init();
        static void Terminate();

        template<typename Format, typename... TArgs>
        inline static void EngineTrace(const Format &fmt, TArgs&& ...args)
        {
            s_EngineLogger->trace(fmt, args...);
        }

        template<typename Format, typename... TArgs>
        inline static void EngineInfo(const Format& fmt, TArgs&& ...args)
        {
            s_EngineLogger->info(fmt, args...);
        }

        template<typename Format, typename... TArgs>
        inline static void EngineDebug(const Format& fmt, TArgs&& ...args)
        {
            s_EngineLogger->debug(fmt, args...);
        }

        template<typename Format, typename... TArgs>
        inline static void EngineWarn(const Format& fmt, TArgs&& ...args)
        {
            s_EngineLogger->warn(fmt, args...);
        }

        template<typename Format, typename... TArgs>
        inline static void EngineError(const Format& fmt, TArgs&& ...args)
        {
            s_EngineLogger->error(fmt, args...);
        }

        template<typename Format, typename... TArgs>
        inline static void EngineCritical(const Format& fmt, TArgs&& ...args)
        {
            s_EngineLogger->critical(fmt, args...);
        }

        template<typename Format, typename... TArgs>
        inline static void Trace(const Format& fmt, TArgs&& ...args)
        {
            s_Logger->trace(fmt, args...);
        }

        template<typename Format, typename... TArgs>
        inline static void Info(const Format& fmt, TArgs&& ...args)
        {
            s_Logger->info(fmt, args...);
        }

        template<typename Format, typename... TArgs>
        inline static void Debug(const Format& fmt, TArgs&& ...args)
        {
            s_Logger->debug(fmt, args...);
        }

        template<typename Format, typename... TArgs>
        inline static void Warn(const Format& fmt, TArgs&& ...args)
        {
            s_Logger->warn(fmt, args...);
        }

        template<typename Format, typename... TArgs>
        inline static void Error(const Format& fmt, TArgs&& ...args)
        {
            s_Logger->error(fmt, args...);
        }

        template<typename Format, typename... TArgs>
        inline static void Critical(const Format& fmt, TArgs&& ...args)
        {
            s_Logger->critical(fmt, args..);
        }


    private:
        static std::shared_ptr<spdlog::logger> s_EngineLogger;
        static std::shared_ptr<spdlog::logger> s_Logger;
    };

}