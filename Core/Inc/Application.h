/*
 * Application.h
 *
 *  Created on: Mar 7, 2021
 *      Author: drew
 */

#ifndef INC_APPLICATION_H_
#define INC_APPLICATION_H_

#include "Adc.h"
#include "Clock.h"
#include "Led.h"
#include "PushButton.h"
#include "Timer.h"
#include "UartLogger.h"
#include "main.h"
#include "stm32l0xx_hal.h"
#include "types_shortcuts.h"
#include <stdio.h>

struct application {
    void (*init)(void);
    void (*loop)(void);
};

extern const struct application Application;

#endif /* INC_APPLICATION_H_ */
