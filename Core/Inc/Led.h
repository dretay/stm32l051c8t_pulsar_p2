/*
 * Led.h
 *
 *  Created on: Mar 7, 2021
 *      Author: drew
 */

#ifndef INC_LED_H_
#define INC_LED_H_

#include "Adc.h"
#include "Clock.h"
#include "UartLogger.h"
#include "main.h"
#include "types_shortcuts.h"
#include "util.h"
struct led {
    void (*init)(void);
    void (*draw)(void);
    void (*off)(void);
};

extern const struct led Led;

#endif /* INC_LED_H_ */
