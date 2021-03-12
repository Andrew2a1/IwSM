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
#include "stm32f1xx_hal.h"

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
#define lcd_d2_Pin GPIO_PIN_2
#define lcd_d2_GPIO_Port GPIOE
#define lcd_d3_Pin GPIO_PIN_3
#define lcd_d3_GPIO_Port GPIOE
#define lcd_d4_Pin GPIO_PIN_4
#define lcd_d4_GPIO_Port GPIOE
#define lcd_d5_Pin GPIO_PIN_5
#define lcd_d5_GPIO_Port GPIOE
#define lcd_d6_Pin GPIO_PIN_6
#define lcd_d6_GPIO_Port GPIOE
#define button2_Pin GPIO_PIN_13
#define button2_GPIO_Port GPIOC
#define joy_u_Pin GPIO_PIN_5
#define joy_u_GPIO_Port GPIOC
#define lcd_d7_Pin GPIO_PIN_7
#define lcd_d7_GPIO_Port GPIOE
#define lcd_rs_Pin GPIO_PIN_8
#define lcd_rs_GPIO_Port GPIOE
#define lcd_e_Pin GPIO_PIN_9
#define lcd_e_GPIO_Port GPIOE
#define lcd_rw_Pin GPIO_PIN_10
#define lcd_rw_GPIO_Port GPIOE
#define buzzer_Pin GPIO_PIN_13
#define buzzer_GPIO_Port GPIOE
#define led1_Pin GPIO_PIN_14
#define led1_GPIO_Port GPIOE
#define led2_Pin GPIO_PIN_15
#define led2_GPIO_Port GPIOE
#define joy_d_Pin GPIO_PIN_6
#define joy_d_GPIO_Port GPIOC
#define joy_r_Pin GPIO_PIN_7
#define joy_r_GPIO_Port GPIOC
#define joy_l_Pin GPIO_PIN_8
#define joy_l_GPIO_Port GPIOC
#define joy_ok_Pin GPIO_PIN_9
#define joy_ok_GPIO_Port GPIOC
#define button1_Pin GPIO_PIN_12
#define button1_GPIO_Port GPIOC
#define lcd_d0_Pin GPIO_PIN_0
#define lcd_d0_GPIO_Port GPIOE
#define lcd_d1_Pin GPIO_PIN_1
#define lcd_d1_GPIO_Port GPIOE
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
