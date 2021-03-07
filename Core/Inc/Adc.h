/*
 * Adc.h
 *
 *  Created on: Mar 7, 2021
 *      Author: drew
 */

#ifndef INC_ADC_H_
#define INC_ADC_H_

#include "stm32l0xx_hal.h"

#include "UartLogger.h"
#include "main.h"
#include "types_shortcuts.h"
#include "util.h"

#define ADC_DMA_SIZE 3

struct adc {
    void (*init)(void);
    void (*poll)(void);
    void (*start)(void);
    void (*stop)(void);
    u32 (*get_brightness)(void);
};

extern const struct adc Adc;

#endif /* INC_ADC_H_ */
