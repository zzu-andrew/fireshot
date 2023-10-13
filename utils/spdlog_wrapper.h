//
// Created by wangyz38535 on 2023/10/11.
//

#ifndef QT_CLION_SPDLOG_WRAPPER_H
#define QT_CLION_SPDLOG_WRAPPER_H
#define SPDLOG_ACTIVE_LEVEL 0
#include "spdlog/spdlog.h"

namespace spdlog
{
    void SpdlogInit(const char* name, const char* file_name, int h, int m, int lv, int flv);
    logger* logger_ptr();
} // spdlog/wo

#ifdef USE_SPDLOG_

#define SPD_TRACE(fmt, ...)    spdlog::logger_ptr()->trace(fmt, ##__VA_ARGS__);
#define SPD_DEBUG(fmt, ...)   spdlog::logger_ptr()->debug(fmt, ##__VA_ARGS__);
#define SPD_INFO(fmt, ...)        spdlog::logger_ptr()->info(fmt, ##__VA_ARGS__);
#define SPD_WARN(fmt, ...)        spdlog::logger_ptr()->warn(fmt, ##__VA_ARGS__);
#define SPD_ERROR(fmt, ...)   spdlog::logger_ptr()->error(fmt, ##__VA_ARGS__);
#define SPD_CRITICAL(fmt, ...) spdlog::logger_ptr()->critical(fmt, ##__VA_ARGS__);
#define SPD_FUNCTION()    SPD_TRACE("function: {0} @ line: {1}", __FUNCTION__, __LINE__);
#define SPD_FLUSH()    spdlog::logger_ptr()->flush();
#else
#define SPD_TRACE(fmt, ...)
#define SPD_DEBUG(fmt, ...)
#define SPD_INFO(fmt, ...)
#define SPD_WARN(fmt, ...)
#define SPD_ERROR(fmt, ...)
#define SPD_CRITICAL(fmt, ...)
#define SPD_FUNCTION()
#define SPD_FLUSH()
#endif // USE_SPDLOG_


class spdlog_wrapper {

};


#endif //QT_CLION_SPDLOG_WRAPPER_H
