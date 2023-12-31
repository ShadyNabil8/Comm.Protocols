/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * File Name          : freertos.c
 * Description        : Code for freertos applications
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

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <spi.h>
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
/* USER CODE BEGIN Variables */
uint8_t operation01 = 0;
uint8_t operation02 = 0;

extern SPI_Chip_t chip1;
extern SPI_Chip_t chip2;

/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for myReceiveTask */
osThreadId_t myReceiveTaskHandle;
const osThreadAttr_t myReceiveTask_attributes = {
  .name = "myReceiveTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for mySendTask */
osThreadId_t mySendTaskHandle;
const osThreadAttr_t mySendTask_attributes = {
  .name = "mySendTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for mySendTask02 */
osThreadId_t mySendTask02Handle;
const osThreadAttr_t mySendTask02_attributes = {
  .name = "mySendTask02",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
void ReceiveTask01(void *argument);
void SendTask01(void *argument);
void SendTask02(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
	/* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
	/* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
	/* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
	/* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* creation of myReceiveTask */
  myReceiveTaskHandle = osThreadNew(ReceiveTask01, NULL, &myReceiveTask_attributes);

  /* creation of mySendTask */
  mySendTaskHandle = osThreadNew(SendTask01, NULL, &mySendTask_attributes);

  /* creation of mySendTask02 */
  mySendTask02Handle = osThreadNew(SendTask02, NULL, &mySendTask02_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
	/* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
	/* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
 * @brief  Function implementing the defaultTask thread.
 * @param  argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN StartDefaultTask */
	/* Infinite loop */
	for (;;) {
		osDelay(1000);
	}
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_ReceiveTask01 */
/**
 * @brief Function implementing the myReceiveTask thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_ReceiveTask01 */
void ReceiveTask01(void *argument)
{
  /* USER CODE BEGIN ReceiveTask01 */
	/* Infinite loop */
	for (;;) {
		osDelay(1000);
	}
  /* USER CODE END ReceiveTask01 */
}

/* USER CODE BEGIN Header_SendTask01 */
/**
 * @brief Function implementing the mySendTask thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_SendTask01 */
void SendTask01(void *argument)
{
  /* USER CODE BEGIN SendTask01 */
	/* Infinite loop */
	for (;;) {
		if (operation01 == 0) {
			HAL_SPI_SendByte('F', &chip1);
			operation01 = 1;
		} else {
			HAL_SPI_SendByte('N', &chip1);
			operation01 = 0;
		}
		osDelay(500);
	}
  /* USER CODE END SendTask01 */
}

/* USER CODE BEGIN Header_SendTask02 */
/**
 * @brief Function implementing the mySendTask02 thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_SendTask02 */
void SendTask02(void *argument)
{
  /* USER CODE BEGIN SendTask02 */
	/* Infinite loop */
	for (;;) {
		if (operation02 == 0) {
			HAL_SPI_SendByte('F', &chip2);
			operation02 = 1;
		} else {
			HAL_SPI_SendByte('N', &chip2);
			operation02 = 0;
		}
		HAL_GPIO_TogglePin(BUILTIN_LED_GPIO_Port, BUILTIN_LED_Pin);
		osDelay(500);

	}
  /* USER CODE END SendTask02 */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

