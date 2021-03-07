/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l0xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define HR_SET_BTN_Pin GPIO_PIN_13
#define HR_SET_BTN_GPIO_Port GPIOC
#define MIN_SET_BTN_Pin GPIO_PIN_0
#define MIN_SET_BTN_GPIO_Port GPIOA
#define LIGHT_SENSE_Pin GPIO_PIN_2
#define LIGHT_SENSE_GPIO_Port GPIOA
#define READ_BTN_Pin GPIO_PIN_7
#define READ_BTN_GPIO_Port GPIOA
#define LCD_A_Pin GPIO_PIN_14
#define LCD_A_GPIO_Port GPIOB
#define LCD_B_Pin GPIO_PIN_15
#define LCD_B_GPIO_Port GPIOB
#define LCD_D_Pin GPIO_PIN_8
#define LCD_D_GPIO_Port GPIOA
#define LCD_C_Pin GPIO_PIN_9
#define LCD_C_GPIO_Port GPIOA
#define LCD_E_Pin GPIO_PIN_10
#define LCD_E_GPIO_Port GPIOA
#define LCD_F_Pin GPIO_PIN_11
#define LCD_F_GPIO_Port GPIOA
#define LCD_G_Pin GPIO_PIN_12
#define LCD_G_GPIO_Port GPIOA
#define LCD_S4_Pin GPIO_PIN_15
#define LCD_S4_GPIO_Port GPIOA
#define LCD_S3_Pin GPIO_PIN_3
#define LCD_S3_GPIO_Port GPIOB
#define LCD_S2_Pin GPIO_PIN_4
#define LCD_S2_GPIO_Port GPIOB
#define LCD_S1_Pin GPIO_PIN_5
#define LCD_S1_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
