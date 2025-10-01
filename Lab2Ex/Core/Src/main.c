/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2025 STMicroelectronics.
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "software_timer.h"
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
TIM_HandleTypeDef htim2;

/* USER CODE BEGIN PV */
int hour = 15, minute = 8, second = 55;
int index_led = 0;
const int MAX_LED = 4;
int  led_buffer[4] = {1,2,3,4};

const int MAX_LED_MATRIX = 8;
const int SIZEOF_MATRIX_BUFFER = 12;
int index_led_matrix = 0;
uint8_t matrix_buffer[12] = { 0x18, 0x24, 0x42, 0x42, 0x7E, 0x42, 0x42, 0x42, 0x00, 0x00, 0x00, 0x00 };
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM2_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void updateClockBuffer(){
	led_buffer[0] = hour / 10;
	led_buffer[1] = hour % 10;
	led_buffer[2] = minute / 10;
	led_buffer[3] = minute % 10;
}

void updateClockTime(){
	if (second >= 60){
		second = 0;
		minute++;
	}
	if (minute >= 60){
		minute = 0;
		hour++;
	}
	if (hour >= 24){
		hour = 0;
	}
}

void display7SEG(int num){
    switch(num){
    case 0:
        HAL_GPIO_WritePin(GPIOB, A_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOB, B_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOB, C_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOB, D_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOB, E_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOB, F_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOB, G_Pin, GPIO_PIN_SET);
        break;
    case 1:
        HAL_GPIO_WritePin(GPIOB, B_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOB, C_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOB, A_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOB, D_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOB, E_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOB, F_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOB, G_Pin, GPIO_PIN_SET);
        break;
    case 2:
        HAL_GPIO_WritePin(GPIOB, A_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOB, B_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOB, D_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOB, E_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOB, G_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOB, C_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOB, F_Pin, GPIO_PIN_SET);
        break;
    case 3:
        HAL_GPIO_WritePin(GPIOB, A_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOB, B_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOB, C_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOB, D_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOB, G_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOB, E_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOB, F_Pin, GPIO_PIN_SET);
        break;
    case 4:
        HAL_GPIO_WritePin(GPIOB, B_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOB, C_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOB, F_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOB, G_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOB, A_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOB, D_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOB, E_Pin, GPIO_PIN_SET);
        break;
    case 5:
        HAL_GPIO_WritePin(GPIOB, A_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOB, C_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOB, D_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOB, F_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOB, G_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOB, B_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOB, E_Pin, GPIO_PIN_SET);
        break;
    case 6:
        HAL_GPIO_WritePin(GPIOB, A_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOB, C_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOB, D_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOB, E_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOB, F_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOB, G_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOB, B_Pin, GPIO_PIN_SET);
        break;
    case 7:
        HAL_GPIO_WritePin(GPIOB, A_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOB, B_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOB, C_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOB, D_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOB, E_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOB, F_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOB, G_Pin, GPIO_PIN_SET);
        break;
    case 8:
        HAL_GPIO_WritePin(GPIOB, A_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOB, B_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOB, C_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOB, D_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOB, E_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOB, F_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOB, G_Pin, GPIO_PIN_RESET);
        break;
    case 9:
        HAL_GPIO_WritePin(GPIOB, A_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOB, B_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOB, C_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOB, D_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOB, F_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOB, G_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOB, E_Pin, GPIO_PIN_SET);
        break;
    default:
        // Tắt hết khi không hợp lệ
        HAL_GPIO_WritePin(GPIOB, A_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOB, B_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOB, C_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOB, D_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOB, E_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOB, F_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOB, G_Pin, GPIO_PIN_SET);
        break;
    }
}

void setEN(int num){
	switch(num){
	case 0:
		HAL_GPIO_WritePin(GPIOA, EN1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, EN2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, EN3_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, EN0_Pin, GPIO_PIN_RESET);
		break;
	case 1:
		HAL_GPIO_WritePin(GPIOA, EN0_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, EN2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, EN3_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, EN1_Pin, GPIO_PIN_RESET);
		break;
	case 2:
		HAL_GPIO_WritePin(GPIOA, EN0_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, EN1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, EN3_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, EN2_Pin, GPIO_PIN_RESET);
		break;
	case 3:
		HAL_GPIO_WritePin(GPIOA, EN0_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, EN1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, EN2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, EN3_Pin, GPIO_PIN_RESET);
		break;
	default :
		HAL_GPIO_WritePin(GPIOA, EN0_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, EN1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, EN2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, EN3_Pin, GPIO_PIN_SET);
		break;
	}
}

void update7SEG(int index){
	switch(index){
	case 0:
		display7SEG(led_buffer[0]);
		setEN(0);
		break;
	case 1:
		display7SEG(led_buffer[1]);
		setEN(1);
		break;
	case 2:
		display7SEG(led_buffer[2]);
		setEN(2);
		break;
	case 3:
		display7SEG(led_buffer[3]);
		setEN(3);
		break;
	default :
		display7SEG(led_buffer[MAX_LED]);
		setEN(MAX_LED);
		break;
	}
}

void displayLEDMatrix(int index){
	uint8_t value = matrix_buffer[index];
	// Quét từng hàng
	HAL_GPIO_WritePin(GPIOB, ROW_0_Pin, (value & (1<<0)) ? GPIO_PIN_SET : GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, ROW_1_Pin, (value & (1<<1)) ? GPIO_PIN_SET : GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, ROW_2_Pin, (value & (1<<2)) ? GPIO_PIN_SET : GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, ROW_3_Pin, (value & (1<<3)) ? GPIO_PIN_SET : GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, ROW_4_Pin, (value & (1<<4)) ? GPIO_PIN_SET : GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, ROW_5_Pin, (value & (1<<5)) ? GPIO_PIN_SET : GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, ROW_6_Pin, (value & (1<<6)) ? GPIO_PIN_SET : GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, ROW_7_Pin, (value & (1<<7)) ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

void updateLEDMatrix(int index){
    HAL_GPIO_WritePin(GPIOA, ENM0_Pin|ENM1_Pin|ENM2_Pin|ENM3_Pin|ENM4_Pin|ENM5_Pin|ENM6_Pin|ENM7_Pin, GPIO_PIN_RESET);

    switch(index){
      case 0:
        HAL_GPIO_WritePin(GPIOA, ENM0_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOA, ENM1_Pin|ENM2_Pin|ENM3_Pin|ENM4_Pin|ENM5_Pin|ENM6_Pin|ENM7_Pin, GPIO_PIN_RESET);
        displayLEDMatrix(0);
        break;
      case 1:
        HAL_GPIO_WritePin(GPIOA, ENM1_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOA, ENM0_Pin|ENM2_Pin|ENM3_Pin|ENM4_Pin|ENM5_Pin|ENM6_Pin|ENM7_Pin, GPIO_PIN_RESET);
        displayLEDMatrix(1);
        break;
      case 2:
        HAL_GPIO_WritePin(GPIOA, ENM2_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOA, ENM0_Pin|ENM1_Pin|ENM3_Pin|ENM4_Pin|ENM5_Pin|ENM6_Pin|ENM7_Pin, GPIO_PIN_RESET);
        displayLEDMatrix(2);
        break;
      case 3:
        HAL_GPIO_WritePin(GPIOA, ENM3_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOA, ENM0_Pin|ENM1_Pin|ENM2_Pin|ENM4_Pin|ENM5_Pin|ENM6_Pin|ENM7_Pin, GPIO_PIN_RESET);
        displayLEDMatrix(3);
        break;
      case 4:
        HAL_GPIO_WritePin(GPIOA, ENM4_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOA, ENM0_Pin|ENM1_Pin|ENM2_Pin|ENM3_Pin|ENM5_Pin|ENM6_Pin|ENM7_Pin, GPIO_PIN_RESET);
        displayLEDMatrix(4);
        break;
      case 5:
        HAL_GPIO_WritePin(GPIOA, ENM5_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOA, ENM0_Pin|ENM1_Pin|ENM2_Pin|ENM3_Pin|ENM4_Pin|ENM6_Pin|ENM7_Pin, GPIO_PIN_RESET);
        displayLEDMatrix(5);
        break;
      case 6:
        HAL_GPIO_WritePin(GPIOA, ENM6_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOA, ENM0_Pin|ENM1_Pin|ENM2_Pin|ENM3_Pin|ENM4_Pin|ENM5_Pin|ENM7_Pin, GPIO_PIN_RESET);
        displayLEDMatrix(6);
        break;
      case 7:
        HAL_GPIO_WritePin(GPIOA, ENM7_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOA, ENM0_Pin|ENM1_Pin|ENM2_Pin|ENM3_Pin|ENM4_Pin|ENM5_Pin|ENM6_Pin, GPIO_PIN_RESET);
        displayLEDMatrix(7);
        break;
      default :
    	HAL_GPIO_WritePin(GPIOA, ENM0_Pin|ENM1_Pin|ENM2_Pin|ENM3_Pin|ENM4_Pin|ENM5_Pin|ENM6_Pin|ENM7_Pin, GPIO_PIN_RESET);
    	break;
    }
}

void shiftleftMatrixBuffer(){
	uint8_t  first = matrix_buffer[0];
	for (int i = 0; i < SIZEOF_MATRIX_BUFFER - 1; ++i){
		matrix_buffer[i] = matrix_buffer[i+1];
	}
	matrix_buffer[SIZEOF_MATRIX_BUFFER - 1] = first;
}

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

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_Base_Start_IT(&htim2);
  /* USER CODE END 2 */
  setTimers(1000);
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  if (timer_flag[0] == 1){
		  second++;
		  HAL_GPIO_TogglePin(GPIOA, LED_BLINK_Pin);
		  HAL_GPIO_TogglePin(GPIOA, DOT_Pin);
		  updateClockTime();
		  updateClockBuffer();
		  setTimer(0,1000);
	  }

	  if (timer_flag[1] == 1){
		  update7SEG(index_led++);
		  index_led = index_led % MAX_LED;
		  setTimer(1,250);
	  }

	  if (timer_flag[2] == 1){
		  updateLEDMatrix(index_led_matrix++);
		  index_led_matrix %= 8;
		  setTimer(2,20);
	  }

	  if (timer_flag[3] == 1){
		  shiftleftMatrixBuffer();
		  setTimer(3,160);
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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
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

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 7999;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 9;
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
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

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
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, ENM0_Pin|ENM1_Pin|DOT_Pin|LED_BLINK_Pin
                          |EN0_Pin|EN1_Pin|EN2_Pin|EN3_Pin
                          |ENM2_Pin|ENM3_Pin|ENM4_Pin|ENM5_Pin
                          |ENM6_Pin|ENM7_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, A_Pin|B_Pin|C_Pin|ROW_2_Pin
                          |ROW_3_Pin|ROW_4_Pin|ROW_5_Pin|ROW_6_Pin
                          |ROW_7_Pin|D_Pin|E_Pin|F_Pin
                          |G_Pin|ROW_0_Pin|ROW_1_Pin, GPIO_PIN_SET);

  /*Configure GPIO pins : ENM0_Pin ENM1_Pin DOT_Pin LED_BLINK_Pin
                           EN0_Pin EN1_Pin EN2_Pin EN3_Pin
                           ENM2_Pin ENM3_Pin ENM4_Pin ENM5_Pin
                           ENM6_Pin ENM7_Pin */
  GPIO_InitStruct.Pin = ENM0_Pin|ENM1_Pin|DOT_Pin|LED_BLINK_Pin
                          |EN0_Pin|EN1_Pin|EN2_Pin|EN3_Pin
                          |ENM2_Pin|ENM3_Pin|ENM4_Pin|ENM5_Pin
                          |ENM6_Pin|ENM7_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : A_Pin B_Pin C_Pin ROW_2_Pin
                           ROW_3_Pin ROW_4_Pin ROW_5_Pin ROW_6_Pin
                           ROW_7_Pin D_Pin E_Pin F_Pin
                           G_Pin ROW_0_Pin ROW_1_Pin */
  GPIO_InitStruct.Pin = A_Pin|B_Pin|C_Pin|ROW_2_Pin
                          |ROW_3_Pin|ROW_4_Pin|ROW_5_Pin|ROW_6_Pin
                          |ROW_7_Pin|D_Pin|E_Pin|F_Pin
                          |G_Pin|ROW_0_Pin|ROW_1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	timer_run();
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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
