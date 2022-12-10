/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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
#include "stm32f1xx_hal.h"
#include "PID.h"
#include "Encoder.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
typedef enum {MENU, REFLOW, PROFILE, PID, FINISH}screenState;

typedef struct{
	int soakTemp;
	int soakTime;
	int peakTemp;
	int reachedPeakTemp;
} Profile;
/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */
void menuScreen_static();
screenState menuScreen_dynamic(Encoder *encoder);
void reflowScreen_static();
screenState reflowScreen_dynamic(PIDController *pid, Profile *profile, Encoder *encoder);
void profileScreen_static(Profile *profile);
screenState profileScreen_dynamic(Profile *profile, Encoder *encoder);
void pidScreen_static(PIDController *pid);
screenState pidScreen_dynamic(PIDController *pid, Encoder *encoder);
screenState finishScreen_dynamic(Encoder *encoder);
/* USER CODE END EM */

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define TMP_CSS_Pin GPIO_PIN_4
#define TMP_CSS_GPIO_Port GPIOA
#define ENCA_Pin GPIO_PIN_10
#define ENCA_GPIO_Port GPIOB
#define ENCB_Pin GPIO_PIN_11
#define ENCB_GPIO_Port GPIOB
#define RB1_Pin GPIO_PIN_8
#define RB1_GPIO_Port GPIOA
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
