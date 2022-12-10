/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "PID.h"
#include "fonts.h"
#include "ssd1306.h"
#include "Encoder.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;

SPI_HandleTypeDef hspi1;

TIM_HandleTypeDef htim2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
static void MX_SPI1_Init(void);
static void MX_TIM2_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
  PIDController pid;
  Profile profile;
  Encoder encoder;

  Encoder_Init(&encoder, GPIOB, ENCA_Pin, ENCB_Pin);
  PIDController_Init(&pid);
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_SPI1_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
  SSD1306_Init();
  menuScreen_static();
  while (1)
  {
	  static screenState state = MENU;
	  switch(state){
	  case MENU:
		  state = menuScreen_dynamic(&encoder);
		  break;
	  case PROFILE:
		  state = profileScreen_dynamic(&profile, &encoder);
		  break;
	  case PID:
		  state = pidScreen_dynamic(&pid, &encoder);
		  break;
	  case REFLOW:
		  state = reflowScreen_dynamic(&pid, &profile, &encoder);
		  break;
	  case FINISH:
		  state = finishScreen_dynamic(&encoder);
		  break;
	  }
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 400000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES_RXONLY;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 7200-1;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 100-1;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */
  HAL_TIM_MspPostInit(&htim2);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(TMP_CSS_GPIO_Port, TMP_CSS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : TMP_CSS_Pin */
  GPIO_InitStruct.Pin = TMP_CSS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(TMP_CSS_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : ENCA_Pin ENCB_Pin */
  GPIO_InitStruct.Pin = ENCA_Pin|ENCB_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : RB1_Pin */
  GPIO_InitStruct.Pin = RB1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(RB1_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
void menuScreen_static(){
	  SSD1306_Clear();
	  SSD1306_GotoXY (0,3);
	  SSD1306_Puts ("  REFLOW", &Font_11x18, 1);
	  SSD1306_GotoXY (0, 24);
	  SSD1306_Puts ("  PROFILE", &Font_11x18, 1);
	  SSD1306_GotoXY (0, 45);
	  SSD1306_Puts ("  PID", &Font_11x18, 1);
	  SSD1306_UpdateScreen();
}
screenState menuScreen_dynamic(Encoder *encoder){
	static int menuSelect = 3;
	int encRead = 0;
	encRead = Encoder_Read(encoder, GPIOB);
	if (encRead != 0){
		if ((encRead == 1) && (menuSelect < 45)){
			menuSelect += 21;
		}
		else if ((encRead == -1) && (menuSelect > 3)){
			menuSelect -= 21;
		}
		SSD1306_GotoXY (0, menuSelect);
		SSD1306_Puts (">", &Font_11x18, 1);
		SSD1306_GotoXY (0, menuSelect - 21);
		SSD1306_Puts (" ", &Font_11x18, 1);
		SSD1306_GotoXY (0, menuSelect + 21);
		SSD1306_Puts (" ", &Font_11x18, 1);
		SSD1306_UpdateScreen();
	}
	if (HAL_GPIO_ReadPin(RB1_GPIO_Port, RB1_Pin) == GPIO_PIN_RESET){
		if (menuSelect == 3){
			return REFLOW;
		}
		else if (menuSelect == 24){
			return PROFILE;
		}
		else if (menuSelect == 45){
			return PID;
		}
	}
	return MENU;
}
void reflowScreen_static(){
	SSD1306_Clear();

}
screenState reflowScreen_dynamic(PIDController *pid, Profile *profile, Encoder *encoder){
	static uint16_t time = 1;
	if (HAL_GPIO_ReadPin(RB1_GPIO_Port, RB1_Pin) == GPIO_PIN_RESET){
		SSD1306_Clear();
		return FINISH;
	}
	HAL_Delay(1000);

	// NEED TO IMPLIMENT SPI COMMUNICATION WITH THERMOCOUPLE
	SSD1306_DrawPixel(time, time, SSD1306_COLOR_WHITE);
	time++;

}
void profileScreen_static(Profile *profile){
	char profileString[20];
	SSD1306_Clear();
	SSD1306_GotoXY (0,3);
	sprintf(profileString, "  Soak Temp: %u", profile->soakTemp);
	SSD1306_Puts (profileString, &Font_11x18, 1);
	SSD1306_GotoXY (0, 24);
	sprintf(profileString, "  Soak Time: %u", profile->soakTime);
	SSD1306_Puts (profileString, &Font_11x18, 1);
	SSD1306_GotoXY (0, 45);
	sprintf(profileString, "  Soak Temp: %u", profile->peakTemp);
	SSD1306_Puts (profileString, &Font_11x18, 1);
	SSD1306_UpdateScreen();
}
screenState profileScreen_dynamic(Profile *profile, Encoder *encoder){
	static uint16_t profileSelect = 3;
	char profileString[20];
	if (profileSelect == 3){
		profile->soakTemp += Encoder_Read(encoder, GPIOB);
		SSD1306_GotoXY (0,3);
		sprintf(profileString, "> Soak Temp: %u", profile->soakTemp);
		SSD1306_Puts (profileString, &Font_11x18, 1);
		SSD1306_UpdateScreen();
		if ((HAL_GPIO_ReadPin(RB1_GPIO_Port, RB1_Pin) == GPIO_PIN_RESET)){
			profileSelect = 24;
		}
	}
	if (profileSelect == 24){
		profile->soakTime += Encoder_Read(encoder, GPIOB);
		SSD1306_GotoXY (0,24);
		sprintf(profileString, "> Soak Time: %u", profile->soakTime);
		SSD1306_Puts (profileString, &Font_11x18, 1);
		SSD1306_UpdateScreen();
		if ((HAL_GPIO_ReadPin(RB1_GPIO_Port, RB1_Pin) == GPIO_PIN_RESET)){
			profileSelect = 45;
		}
	}
	if (profileSelect == 45){
		profile->peakTemp += Encoder_Read(encoder, GPIOB);
		SSD1306_GotoXY (0,45);
		sprintf(profileString, "> Peak Temp: %u", profile->peakTemp);
		SSD1306_Puts (profileString, &Font_11x18, 1);
		SSD1306_UpdateScreen();
		if ((HAL_GPIO_ReadPin(RB1_GPIO_Port, RB1_Pin) == GPIO_PIN_RESET)){
			return MENU;
		}
	}
}
void pidScreen_static(PIDController *pid){


}
screenState pidScreen_dynamic(PIDController *pid, Encoder *encoder){


}
screenState finishScreen_dynamic(Encoder *encoder){


}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
