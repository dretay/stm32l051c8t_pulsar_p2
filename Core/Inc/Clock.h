/*
 * Clock.h
 *
 *  Created on: Mar 7, 2021
 *      Author: drew
 */

#ifndef INC_CLOCK_H_
#define INC_CLOCK_H_

#include "stm32l0xx_hal.h"

#include "UartLogger.h"
#include "types_shortcuts.h"

struct clock {
    void (*init)(void);
    void (*loop)(void);
    void (*increment_hour)(u32 hours);
    void (*increment_minute)(u32 minutes);
    void (*commit_time)(void);
    int (*get_hours)(void);
    int (*get_minutes)(void);
};

extern const struct clock Clock;

#endif /* INC_CLOCK_H_ */
