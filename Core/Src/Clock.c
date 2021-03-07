#include "Clock.h"

#if defined STM32L0xx_HAL_RTC_H
extern RTC_HandleTypeDef hrtc;
#endif

static s32 CURR_MINUTES, CURR_HOURS;
static bool TIME_MODIFIED = false;

static void commit_time()
{
    RTC_TimeTypeDef sTime = { 0 };
    sTime.Hours = CURR_HOURS;
    sTime.Minutes = CURR_MINUTES;
    sTime.Seconds = 0;
    sTime.TimeFormat = RTC_HOURFORMAT12_AM;
    sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
    sTime.StoreOperation = RTC_STOREOPERATION_RESET;
    if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN) != HAL_OK) {
        app_log_error("error setting time");
    }
}
static void increment_hour(u32 hours)
{
    app_log_debug("incrementing hours");
    CURR_HOURS += hours;
    if (CURR_HOURS > 12) {
        CURR_HOURS = 1;
    }
    commit_time();
}
static void increment_minute(u32 minutes)
{
    app_log_debug("incrementing minutes");
    CURR_MINUTES += minutes;
    if (CURR_MINUTES > 60) {
        CURR_MINUTES = 0;
        increment_hour(1);
    }
    commit_time();
}
static void init(void)
{
    RTC_DateTypeDef sdatestructureget;
    RTC_TimeTypeDef stimestructure;

    /* Get the RTC current Time */
    HAL_RTC_GetTime(&hrtc, &stimestructure, RTC_FORMAT_BIN);

    //even though we don't use it, have to fetch it to unlock the register
    HAL_RTC_GetDate(&hrtc, &sdatestructureget, RTC_FORMAT_BIN);

    CURR_HOURS = stimestructure.Hours;
    CURR_MINUTES = stimestructure.Minutes;
    app_log_debug("rtc init: %d:%d", CURR_HOURS, CURR_MINUTES);
}
static void loop()
{
    s32 hours = Clock.get_hours();
    s32 minutes = Clock.get_minutes();
    u8 hours_top = (hours / 10) % 10;
    u8 hours_bottom = hours % 10;
    u8 minutes_top = (minutes / 10) % 10;
    u8 minutes_bottom = minutes % 10;

    app_log_info("%d%d:%d%d", hours_top, hours_bottom, minutes_top, minutes_bottom);
}
static int get_minutes(void)
{
    return CURR_MINUTES;
}
static int get_hours(void)
{
    return CURR_HOURS;
}
const struct clock Clock = {
    .init = init,
    .loop = loop,
    .increment_hour = increment_hour,
    .increment_minute = increment_minute,
    .commit_time = commit_time,
    .get_minutes = get_minutes,
    .get_hours = get_hours
};
