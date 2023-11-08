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
extern UART_HandleTypeDef huart1;
const uint8_t Payload_On[] = {'N'};
const uint8_t Payload_Off[] = {'F'};
uint8_t operation = 0;

/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = { .name = "defaultTask",
		.stack_size = 128 * 4, .priority = (osPriority_t) osPriorityNormal, };
/* Definitions for myReceiveTask */
osThreadId_t myReceiveTaskHandle;
const osThreadAttr_t myReceiveTask_attributes = { .name = "myReceiveTask",
		.stack_size = 128 * 4, .priority = (osPriority_t) osPriorityLow, };
/* Definitions for mySendTask */
osThreadId_t mySendTaskHandle;
const osThreadAttr_t mySendTask_attributes = { .name = "mySendTask",
		.stack_size = 128 * 4, .priority = (osPriority_t) osPriorityLow, };

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
void ReceiveTask(void *argument);
void SendTask(void *argument);

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
	defaultTaskHandle = osThreadNew(StartDefaultTask, NULL,
			&defaultTask_attributes);

	/* creation of myReceiveTask */
	myReceiveTaskHandle = osThreadNew(ReceiveTask, NULL,
			&myReceiveTask_attributes);

	/* creation of mySendTask */
	mySendTaskHandle = osThreadNew(SendTask, NULL, &mySendTask_attributes);

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
void StartDefaultTask(void *argument) {
	/* USER CODE BEGIN StartDefaultTask */
	/* Infinite loop */
	for (;;) {
		osDelay(1000);
	}
	/* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_ReceiveTask */
/**
 * @brief Function implementing the myReceiveTask thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_ReceiveTask */
void ReceiveTask(void *argument) {
	/* USER CODE BEGIN ReceiveTask */
	/* Infinite loop */
	for (;;) {
		osDelay(1000);
	}
	/* USER CODE END ReceiveTask */
}

/* USER CODE BEGIN Header_SendTask */
/**
 * @brief Function implementing the mySendTask thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_SendTask */
void SendTask(void *argument) {
	/* USER CODE BEGIN SendTask */
	/* Infinite loop */
	for (;;) {
		if (operation == 0) {
			operation = 1;
			HAL_UART_Transmit(&huart1, Payload_On, 1, 10);
		} else {
			operation = 0;
			HAL_UART_Transmit(&huart1, Payload_Off, 1, 10);
		}
		HAL_GPIO_TogglePin(WHITE_LED_GPIO_Port, WHITE_LED_Pin);

		osDelay(500);
	}
	/* USER CODE END SendTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

