/*
 * util.h
 *
 *  Created on: Mar 7, 2021
 *      Author: drew
 */

#ifndef INC_UTIL_H_
#define INC_UTIL_H_

#define GPIO_SET(x) \
  { HAL_GPIO_WritePin(LCD_##x##_GPIO_Port, LCD_##x##_Pin, GPIO_PIN_SET); }
#define GPIO_RESET(x) \
  { HAL_GPIO_WritePin(LCD_##x##_GPIO_Port, LCD_##x##_Pin, GPIO_PIN_RESET); }

#endif /* INC_UTIL_H_ */
