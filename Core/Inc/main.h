/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
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
#include "stm32f4xx_hal.h"

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
#define ADC0_Pin GPIO_PIN_0
#define ADC0_GPIO_Port GPIOA
#define ADC1_Pin GPIO_PIN_1
#define ADC1_GPIO_Port GPIOA
#define ADC2_Pin GPIO_PIN_2
#define ADC2_GPIO_Port GPIOA
#define ADC3_Pin GPIO_PIN_3
#define ADC3_GPIO_Port GPIOA
#define ADC4_Pin GPIO_PIN_4
#define ADC4_GPIO_Port GPIOA
#define SDA5_Pin GPIO_PIN_8
#define SDA5_GPIO_Port GPIOE
#define SCL6_Pin GPIO_PIN_9
#define SCL6_GPIO_Port GPIOE
#define SDA6_Pin GPIO_PIN_10
#define SDA6_GPIO_Port GPIOE
#define SCL7_Pin GPIO_PIN_11
#define SCL7_GPIO_Port GPIOE
#define SDA7_Pin GPIO_PIN_12
#define SDA7_GPIO_Port GPIOE
#define A2_Pin GPIO_PIN_10
#define A2_GPIO_Port GPIOB
#define EN_M1_Pin GPIO_PIN_11
#define EN_M1_GPIO_Port GPIOB
#define SCL_Pin GPIO_PIN_13
#define SCL_GPIO_Port GPIOB
#define SDA_Pin GPIO_PIN_14
#define SDA_GPIO_Port GPIOB
#define SDA3_Pin GPIO_PIN_8
#define SDA3_GPIO_Port GPIOD
#define SCL4_Pin GPIO_PIN_9
#define SCL4_GPIO_Port GPIOD
#define SDA4_Pin GPIO_PIN_10
#define SDA4_GPIO_Port GPIOD
#define SCL5_Pin GPIO_PIN_11
#define SCL5_GPIO_Port GPIOD
#define RUN_LED_Pin GPIO_PIN_11
#define RUN_LED_GPIO_Port GPIOA
#define SCL1_Pin GPIO_PIN_0
#define SCL1_GPIO_Port GPIOD
#define SDA1_Pin GPIO_PIN_1
#define SDA1_GPIO_Port GPIOD
#define SCL2_Pin GPIO_PIN_2
#define SCL2_GPIO_Port GPIOD
#define SDA2_Pin GPIO_PIN_3
#define SDA2_GPIO_Port GPIOD
#define SCL3_Pin GPIO_PIN_7
#define SCL3_GPIO_Port GPIOD
#define A0_Pin GPIO_PIN_8
#define A0_GPIO_Port GPIOB
#define A1_Pin GPIO_PIN_9
#define A1_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
