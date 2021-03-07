#pragma once

//stl libraries
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

//stm32 hal libraries
#ifdef STM32L051xx
#include "stm32l0xx_hal.h"
#else
#include "stm32f1xx_hal.h"
#endif
//project libraries
#include "types_shortcuts.h"

enum {
    LOG_TRACE,
    LOG_DEBUG,
    LOG_INFO,
    LOG_WARN,
    LOG_ERROR,
    LOG_FATAL
};

struct uartlogger {
    void (*init)(void);
    void (*log_log)(bool append, bool terminate, int level, const char* file, const char* function, int line, const char* fmt, ...);
};

extern const struct uartlogger UartLogger;

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#define app_log_trace(...) UartLogger.log_log(false, false, LOG_TRACE, __FILENAME__, __FUNCTION__, __LINE__, __VA_ARGS__)
#define app_log_debug(...) UartLogger.log_log(false, false, LOG_DEBUG, __FILENAME__, __FUNCTION__, __LINE__, __VA_ARGS__)
#define app_log_info(...) UartLogger.log_log(false, false, LOG_INFO, __FILENAME__, __FUNCTION__, __LINE__, __VA_ARGS__)
#define app_log_warn(...) UartLogger.log_log(false, false, LOG_WARN, __FILENAME__, __FUNCTION__, __LINE__, __VA_ARGS__)
#define app_log_error(...) UartLogger.log_log(false, false, LOG_ERROR, __FILENAME__, __FUNCTION__, __LINE__, __VA_ARGS__)
#define app_log_fatal(...) UartLogger.log_log(false, false, LOG_FATAL, __FILENAME__, __FUNCTION__, __LINE__, __VA_ARGS__)
#define app_log_append(...) UartLogger.log_log(true, false, LOG_DEBUG, __FILENAME__, __FUNCTION__, __LINE__, __VA_ARGS__)
#define app_log_end() UartLogger.log_log(true, true, LOG_DEBUG, __FILENAME__, __FUNCTION__, __LINE__, "\r\n")
