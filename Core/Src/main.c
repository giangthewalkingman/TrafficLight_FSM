/* USER CODE BEGIN Header */

/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
// define states
#define Pgo 0
#define Wgo 1
#define Sgo 2
#define Wwait 3
#define Swait 4
#define Warn1 5
#define Off1 6
#define Warn2 7
#define Off2 8
#define Warn3 9
#define Off3 10
#define stopP 11
#define stopW 12
#define stopS 13

// define value of state
#define Pgo_val 0x127
#define Wgo_val 0x61
#define Sgo_val 0x109
#define Wwait_val 0xA1
#define Swait_val 0x111
#define Warn1_val 0x121
#define Off1_val 0x120
#define Warn2_val 0x121
#define Off2_val 0x120
#define Warn3_val 0x121
#define Off3_val 0x120
#define stopP_val 0x121
#define stopW_val 0x121
#define stopS_val 0x121
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

// Runs on STM32F103C8T6
// Use a table implementation of a Moore finite state machine to operate
// a traffic light.
// Truong Giang Nguyen
// Jan 10th, 2024
//
// walk button sensor connected to PB5 (1=button pressed)
// north facing car detector connected to PB4 (1=car present)
// east facing car detector connected to PB3 (1=car present)
//
// east facing red light connected to PA8
// east facing yellow light connected to PA7
// east facing green light connected to PA6
// north facing red light connected to PA5
// north facing yellow light connected to PA4
// north facing green light connected to PA3
// walk blue light connected to PA2
// walk green light connected to PA1
// walk red light connected to PA0

struct State {
	uint32_t out;
	unsigned long wait;
	uint32_t next[8]; //Index of the state
};
typedef const struct State Stype;

Stype fsm[14] = {
{0x127, 4000, {Pgo, Warn1, Warn1, Warn1, Pgo, Warn1, Warn1, Warn1}},
{0x61, 4000, {Wgo, Wgo, Wwait, Wwait, Wwait, Wwait, Wwait, Wwait}},
{0x109, 4000, {Sgo, Swait, Sgo, Swait, Swait, Swait, Swait, Swait}},
{0xA1, 1600, {stopW, stopW, stopW, stopW, stopW, stopW, stopW, stopW}},
{0x111, 1600, {stopS, stopS, stopS, stopS, stopS, stopS, stopS, stopS}},
{0x121, 300, {Off1, Off1, Off1, Off1, Off1, Off1, Off1, Off1}},
{0x120, 300, {Warn2, Warn2, Warn2, Warn2, Warn2, Warn2, Warn2, Warn2}},
{0x121, 300, {Off2, Off2, Off2, Off2, Off2, Off2, Off2, Off2}},
{0x120, 300, {Warn3, Warn3, Warn3, Warn3, Warn3, Warn3, Warn3, Warn3}},
{0x121, 300, {Off3, Off3, Off3, Off3, Off3, Off3, Off3, Off3}},
{0x120, 300, {stopP, stopP, stopP, stopP, stopP, stopP, stopP, stopP}},
{0x121, 250, {Pgo, Wgo, Sgo, Sgo, Pgo, Wgo, Sgo, Sgo}},
{0x121, 250, {Pgo, Wgo, Sgo, Sgo, Pgo, Pgo, Pgo, Pgo}},
{0x121, 250, {Pgo, Wgo, Sgo, Wgo, Pgo, Wgo, Pgo, Wgo}}
};

uint16_t S;
uint32_t Input = 0xFF;
uint32_t check_input_A;
uint32_t check_input_B;
uint32_t check_input_C;
uint32_t check_output;
uint32_t check_state;
uint32_t count=0;
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	S = Warn1;
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
  /* USER CODE BEGIN 2 */
  while(1) {
	  check_input_B = (GPIOB->IDR)&(0x38);
	  check_output = GPIOA->ODR;
	  GPIOA->ODR = (fsm[S].out)|((fsm[S].out & 0x100)<<1);
	  HAL_Delay(fsm[S].wait);
	  Input = ((GPIOB->IDR)>>3)&0x7;
	  S = fsm[S].next[Input];
	  count++;
  }
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
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
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL2;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
                          |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7
                          |GPIO_PIN_8|GPIO_PIN_9, GPIO_PIN_RESET);

  /*Configure GPIO pins : PC13 PC14 PC15 */
  GPIO_InitStruct.Pin = GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PA0 PA1 PA2 PA3
                           PA4 PA5 PA6 PA7
                           PA8 PA9 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
                          |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7
                          |GPIO_PIN_8|GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB3 PB4 PB5 */
  GPIO_InitStruct.Pin = GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

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
