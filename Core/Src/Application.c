#include "Application.h"

static int STOP_TIMER_HANDLE = -1;
static int MINUTE_INCREMENT_HANDLE = -1;
static int HOUR_INCREMENT_HANDLE = -1;
static u32 WAKE_MSECONDS = 1000;

extern void EXT_SystemClock_Config(void);

static void reset_stop_timer();

//static bool wake = false;

static void on_wake(void)
{
    //	wake = false;
    //reconfigure clock
    EXT_SystemClock_Config();

    //fetch time
    Clock.init();

    //start adc
    Adc.start();

    //start stop timer back up
    reset_stop_timer();

    //	HAL_NVIC_EnableIRQ(EXTI0_1_IRQn);
    //	HAL_NVIC_EnableIRQ(EXTI4_15_IRQn);
}
static void on_stop(void)
{
    app_log_debug("preparing for standby... ");

    Led.off();
    Adc.stop();
    app_log_debug("entering standby");
    HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON, PWR_STOPENTRY_WFI);
    on_wake();
}
static void stop_stop_timer()
{
    Timer.cancel(STOP_TIMER_HANDLE);
    STOP_TIMER_HANDLE = -1;
}
static void reset_stop_timer()
{
    app_log_debug("resetting shutdown timer... ");
    if (!Timer.reset(STOP_TIMER_HANDLE)) {
        app_log_append("creating shutdown timer");
        STOP_TIMER_HANDLE = Timer.in(WAKE_MSECONDS, on_stop);
    }
}

void hour_increment(void)
{
    if (HOUR_INCREMENT_HANDLE == -1) {
        HOUR_INCREMENT_HANDLE = Timer.every(500, hour_increment);
    }
    Clock.increment_hour(1);
    stop_stop_timer();
}
void hour_increment_stop(void)
{
    if (Timer.cancel(HOUR_INCREMENT_HANDLE)) {
        HOUR_INCREMENT_HANDLE = -1;
        reset_stop_timer();
        app_log_debug("stopped hour increment timer");
    } else {
        app_log_error("failed to stop hour increment timer");
    }
}

void minute_increment(void)
{
    if (MINUTE_INCREMENT_HANDLE == -1) {
        MINUTE_INCREMENT_HANDLE = Timer.every(500, minute_increment);
    }
    Clock.increment_minute(1);
    stop_stop_timer();
}
void minute_increment_fast(void)
{
    if (!Timer.cancel(MINUTE_INCREMENT_HANDLE)) {
        app_log_debug("failed to stop slow minute increment");
    }
    MINUTE_INCREMENT_HANDLE = Timer.every(500, minute_increment_fast);
    Clock.increment_minute(1);
}
void minute_increment_stop(void)
{
    if (Timer.cancel(MINUTE_INCREMENT_HANDLE)) {
        MINUTE_INCREMENT_HANDLE = -1;
        reset_stop_timer();
        app_log_debug("stopped minute increment timer");
    } else {
        app_log_error("failed to stop minute increment timer");
    }
}
void read_short_press(void)
{
    reset_stop_timer();
}

static void init(void)
{
    app_log_debug("application starting");

    PushButton.init();
    PushButton.register_button(
        (struct button_config) {
            .button_down_short = &hour_increment,
            .button_up = &hour_increment_stop,
            .gpio_pin = HR_SET_BTN_Pin,
            .gpio_port = HR_SET_BTN_GPIO_Port });
    PushButton.register_button(
        (struct button_config) {
            .button_down_short = &minute_increment,
            .button_up = &minute_increment_stop,
            .gpio_pin = MIN_SET_BTN_Pin,
            .gpio_port = MIN_SET_BTN_GPIO_Port });
    PushButton.register_button(
        (struct button_config) {
            .button_down_short = &read_short_press,
            .gpio_pin = READ_BTN_Pin,
            .gpio_port = READ_BTN_GPIO_Port });
    Clock.init();
    Timer.init();
    Adc.init();
    Led.init();
    Timer.every(50, PushButton.loop);
    //		Timer.every(1000, Clock.loop);
    Timer.every(200, Adc.poll);
    //	STOP_TIMER_HANDLE = Timer.in(WAKE_MSECONDS, on_stop);
    reset_stop_timer();
    //	HAL_PWREx_EnableLowPowerRunMode(); //set regulator to low power mode
    //	HAL_PWREx_EnableUltraLowPower(); //disable internal voltage reference
    //	HAL_PWR_EnterSTANDBYMode();
    //	HAL_PWREx_EnableFastWakeUp(); //controls whether to wait for internal voltage startup time
    //	__HAL_RCC_WAKEUPSTOP_CLK_CONFIG(RCC_STOP_WAKEUPCLOCK_MSI);
    //	Clock.increment_hour();
    app_log_debug("application started");
}
extern RTC_HandleTypeDef hrtc;
static void loop(void)
{
    Timer.tick();
    Led.draw();
}
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    app_log_trace("external interrupt triggered!");
    if (GPIO_Pin == HR_SET_BTN_Pin) {
        PushButton.signal_state_change(GPIO_Pin, false);
    }
    if (GPIO_Pin == MIN_SET_BTN_Pin) {
        PushButton.signal_state_change(GPIO_Pin, false);
    }
    if (GPIO_Pin == READ_BTN_Pin) {
        PushButton.signal_state_change(GPIO_Pin, false);
    }
}

const struct application Application = {
    .init = init,
    .loop = loop,

};
