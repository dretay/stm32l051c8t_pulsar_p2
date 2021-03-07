#include "Led.h"

static void init()
{
    GPIO_RESET(S1);
    GPIO_RESET(S2);
    GPIO_RESET(S3);
    GPIO_RESET(S4);

    GPIO_RESET(A);
    GPIO_RESET(B);
    GPIO_RESET(C);
    GPIO_RESET(D);
    GPIO_RESET(E);
    GPIO_RESET(F);
    GPIO_RESET(G);
}
static inline void delay_us(u32 delay)
{
    for (int i = 0; i < delay; i++) {
        __asm__("nop");
    }
}

struct mask {
    u16 A_MASK;
    u16 B_MASK;
};
static struct mask digit_masks[] = {
    (struct mask) { .A_MASK = 0xF << 8, .B_MASK = 0xC << 12 }, //zero
    (struct mask) { .A_MASK = 0x1 << 9, .B_MASK = 0x1 << 15 }, //one
    (struct mask) { .A_MASK = 0x15 << 8, .B_MASK = 0xC << 12 }, //two
    (struct mask) { .A_MASK = 0x13 << 8, .B_MASK = 0xC << 12 }, //three
    (struct mask) { .A_MASK = 0x1A << 8, .B_MASK = 0x1 << 15 }, //four
    (struct mask) { .A_MASK = 0x1B << 8, .B_MASK = 0x1 << 14 }, //five
    (struct mask) { .A_MASK = 0x1F << 8, .B_MASK = 0x1 << 14 }, //six
    (struct mask) { .A_MASK = 0x1 << 9, .B_MASK = 0xC << 12 }, //seven
    (struct mask) { .A_MASK = 0x1F << 8, .B_MASK = 0xC << 12 }, //eight
    (struct mask) { .A_MASK = 0x1B << 8, .B_MASK = 0xC << 12 }, //nine
};
//3v = pitch black (30 delay)
//200mV = direct sunlight (80 delay)
static u32 LED_ON_FLOOR = 30;
static u32 LED_ON_MAX_SWING = 60;
static u32 MAX_BRIGHTNESS_READING = 3000;

static void draw()
{
    s32 hours = Clock.get_hours();
    s32 minutes = Clock.get_minutes();
    u8 hours_top = (hours / 10) % 10;
    u8 hours_bottom = hours % 10;
    u8 minutes_top = (minutes / 10) % 10;
    u8 minutes_bottom = minutes % 10;
    u32 brightness = Adc.get_brightness();
    u32 LED_ON_DELAY = LED_ON_FLOOR + (LED_ON_MAX_SWING * ((float)brightness / (float)MAX_BRIGHTNESS_READING));
    if (LED_ON_DELAY > (LED_ON_FLOOR + LED_ON_MAX_SWING)) {
        LED_ON_DELAY = (LED_ON_FLOOR + LED_ON_MAX_SWING);
    }
    app_log_info("%d%d:%d%d, %d/%d = %d", hours_top, hours_bottom, minutes_top, minutes_bottom, brightness, MAX_BRIGHTNESS_READING, LED_ON_DELAY);

    for (int i = 0; i < 4; i++) {
        //10:00
        //1,2,2,3,0
        //0 = rhs
        //1 = colon, 1's
        //2 = lhs
        //3 = middle

        switch (i) {
        case 0:
            GPIO_SET(S1);
            if (hours_top == 1) {
                GPIO_SET(A);
                GPIO_SET(D);
            }
            GPIO_SET(B);
            GPIO_SET(C);
            break;
        case 1:
            GPIO_SET(S2);
            GPIOA->BSRR = digit_masks[hours_bottom].A_MASK;
            GPIOB->BSRR = digit_masks[hours_bottom].B_MASK;
            break;
        case 2:
            GPIO_SET(S3);
            GPIOA->BSRR = digit_masks[minutes_top].A_MASK;
            GPIOB->BSRR = digit_masks[minutes_top].B_MASK;
            break;
        case 3:
            GPIO_SET(S4);
            GPIOA->BSRR = digit_masks[minutes_bottom].A_MASK;
            GPIOB->BSRR = digit_masks[minutes_bottom].B_MASK;
            break;
        }
        if (i == 0) {
            delay_us(LED_ON_DELAY / 3);
            GPIO_RESET(B);
            GPIO_RESET(C);
            delay_us((LED_ON_DELAY / 3) * 2);

        } else {
            delay_us(LED_ON_DELAY);
        }

        switch (i) {
        case 0:
            GPIO_RESET(S1);
            if (hours_top == 1) {
                GPIO_RESET(A);
                GPIO_RESET(D);
            }
            break;
        case 1:
            GPIO_RESET(S2);
            GPIOA->BRR = digit_masks[hours_bottom].A_MASK;
            GPIOB->BRR = digit_masks[hours_bottom].B_MASK;
            break;
        case 2:
            GPIO_RESET(S3);
            GPIOA->BRR = digit_masks[minutes_top].A_MASK;
            GPIOB->BRR = digit_masks[minutes_top].B_MASK;
            break;
        case 3:
            GPIO_RESET(S4);
            GPIOA->BRR = digit_masks[minutes_bottom].A_MASK;
            GPIOB->BRR = digit_masks[minutes_bottom].B_MASK;
            break;
        }
    }
}
static void off(void)
{
    GPIO_RESET(S1);
    GPIO_RESET(S2);
    GPIO_RESET(S3);
    GPIO_RESET(S4);
    GPIO_RESET(A);
    GPIO_RESET(B);
    GPIO_RESET(C);
    GPIO_RESET(D);
    GPIO_RESET(E);
    GPIO_RESET(F);
    GPIO_RESET(G);
}

const struct led Led = {
    .init = init,
    .draw = draw,
    .off = off
};
