//
// Created by wangyz38535 on 2023/10/11.
//
#include "spdlog_wrapper.h"
#include "spdlog/spdlog.h"
#include "spdlog/cfg/env.h"  // support for loading levels from the environment variable
#include "spdlog/fmt/ostr.h" // support for user defined types

#include "spdlog/sinks/daily_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace spdlog
{

    static logger* logger_;

    void SpdlogInit(const char* name, const char* file_name, int h, int m, int lv, int flv)
    {
#ifdef USE_SPDLOG_
        QString folderPath = "logs";
        QDir dir;

        if (!dir.exists(folderPath)) {
            dir.mkpath(folderPath);
        }
        auto console_sink = std::make_shared<sinks::stdout_color_sink_mt>();
        console_sink->set_level(static_cast<level::level_enum>(lv));

        auto file_sink = std::make_shared<sinks::daily_file_sink_mt>(file_name, h, m);
        file_sink->set_level(static_cast<level::level_enum>(lv));

        logger_ = new logger(name, {console_sink, file_sink});
        logger_->set_level(static_cast<level::level_enum>(lv));
        logger_->flush_on(static_cast<level::level_enum>(flv));

        set_pattern("[%H:%M:%S %z] [thread %t] %v");
        //logger_->set_pattern("[%Y-%m-%d %H:%M:%S] [%n] [%^%l%$] [%s:%#] %v");
        //logger_->set_pattern("[%H:%M:%S %z] [%n] [%^---%L---%$] [thread %t] %v");

        SPDLOG_LOGGER_INFO(logger_, "test3 {}", 3);//会输出文件名和行号

#endif // USE_SPDLOG_

    }

    logger* logger_ptr()
    {
        return logger_;
    }
}
