#include "UartLogger.h"

//extern UART_HandleTypeDef huart1;
bool error = false;
static void uart_putstring(const uint8_t* string)
{
    //	HAL_StatusTypeDef status = HAL_UART_Transmit(&huart1, (uint8_t*)string, strlen(string), 0xffffff);            // send message via UART
    //	if(status!=HAL_OK){
    //		error = true;
    //	}
}
static void myvprint(const char* fmt, va_list argp)
{
    char string[200];
    if (0 < vsprintf(string, fmt, argp)) // build string
    {
        uart_putstring(string); // send message via UART
    }
}

static const char* level_names[] = {
    "TRACE",
    "DEBUG",
    "INFO",
    "WARN",
    "ERROR",
    "FATAL"
};
static const char* level_colors[] = {
    "\x1b[94m",
    "\x1b[36m",
    "\x1b[32m",
    "\x1b[33m",
    "\x1b[31m",
    "\x1b[35m"
};
static u8 last_log_level = 0;
static void log_log(bool append, bool terminate, int level, const char* file, const char* function, int line, const char* fmt, ...)
{
    if (append) {
        level = last_log_level;
    } else {
        last_log_level = level;
    }
#ifdef DEBUG_LEVEL
    va_list args;
    char buf[100] = { 0 };
    if (level >= DEBUG_LEVEL) {
        if (!append) {

            snprintf(buf,
                100,
                "%s%s %s%-5s\x1b[0m \x1b[90m%s:%s:%d:\x1b[0m ",
                buf,
                "\r\n",
                level_colors[level],
                level_names[level],
                file,
                function,
                line);
            uart_putstring(buf);
        }

        va_start(args, fmt);
        myvprint(fmt, args);
        va_end(args);
        if (terminate) {

            snprintf(buf,
                2,
                "\r\n",
                buf);
            uart_putstring(buf);
        }
    }
#endif
}

static void init()
{
}

const struct uartlogger UartLogger = {
    .init = init,
    .log_log = log_log,
};
