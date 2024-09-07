/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
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
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "event_groups.h"
#include "../../Drivers/SYSTEM/usart/usart.h"
#include "../../Drivers/BSP/rc522.h"
#include "../../Drivers/BSP/esp8266.h"
#include "../../Drivers/BSP/beep.h"
#include "../../Drivers/icode/oled.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
EventGroupHandle_t EventGroupHandler;	//事件标志组句�?

#define EVENTBIT_0	(1<<0)				//事件�?
#define EVENTBIT_1	(1<<1)
#define EVENTBIT_2	(1<<2)
#define EVENTBIT_ALL	(EVENTBIT_0|EVENTBIT_1|EVENTBIT_2)

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
int err=0;
int event_flag = 0;
extern char g_uart_rx_buf[ESP8266_UART_RX_BUF_SIZE];
extern uint16_t esp8266_cnt, esp8266_cntPre;

/* USER CODE END Variables */
/* Definitions for StartTask */
osThreadId_t StartTaskHandle;
const osThreadAttr_t StartTask_attributes = {
  .name = "StartTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal1,
};
/* Definitions for SG90Task */
osThreadId_t SG90TaskHandle;
const osThreadAttr_t SG90Task_attributes = {
  .name = "SG90Task",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal4,
};
/* Definitions for RC522TASK */
osThreadId_t RC522TASKHandle;
const osThreadAttr_t RC522TASK_attributes = {
  .name = "RC522TASK",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal1,
};
/* Definitions for esp8266Task */
osThreadId_t esp8266TaskHandle;
const osThreadAttr_t esp8266Task_attributes = {
  .name = "esp8266Task",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal1,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void Start_Task(void *argument);
void SG90_Task(void *argument);
void RC522_Task(void *argument);
void esp8266_Task(void *argument);

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
  /* creation of StartTask */
  StartTaskHandle = osThreadNew(Start_Task, NULL, &StartTask_attributes);

  /* creation of SG90Task */
  SG90TaskHandle = osThreadNew(SG90_Task, NULL, &SG90Task_attributes);

  /* creation of RC522TASK */
  RC522TASKHandle = osThreadNew(RC522_Task, NULL, &RC522TASK_attributes);

  /* creation of esp8266Task */
  esp8266TaskHandle = osThreadNew(esp8266_Task, NULL, &esp8266Task_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_Start_Task */
/**
  * @brief  Function implementing the StartTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_Start_Task */
void Start_Task(void *argument)
{
  /* USER CODE BEGIN Start_Task */
  /* Infinite loop */
	while(1)
	{
		if(err==3)
		{
			err = 0;
		  vTaskSuspend(RC522TASKHandle);
		  vTaskSuspend(esp8266TaskHandle);
		  printf("vTaskSuspend all tasks\r\n");
		  OLED_Clear();                         //清屏
		//上面的初始化以及清屏的代码在�?�?始处�?定要�?
		 OLED_ShowString(0,0,"try again in 3",16, 1);    //反相显示8X16字符�?
		 OLED_ShowString(0,4," minute",16, 1);
		  //延时后恢�?
		  vTaskDelay(180000);

		  OLED_Clear();                         //清屏
		//上面的初始化以及清屏的代码在�?�?始处�?定要�?
		  OLED_DrawBMP(0,0,32, 4,BMP1,1);//正相显示图片BMP1
		 OLED_DrawBMP(90,0,122, 4,BMP1,0);//正相显示图片BMP1

		  vTaskResume(RC522TASKHandle);
		  vTaskResume(esp8266TaskHandle);
		  printf("vTaskResume all tasks\r\n");
		}
		printf("err : %d\r\n" ,err);
		vTaskDelay(1000);
	}

  /* USER CODE END Start_Task */
}

/* USER CODE BEGIN Header_SG90_Task */
/**
* @brief Function implementing the SG90Task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_SG90_Task */
void SG90_Task(void *argument)
{
  /* USER CODE BEGIN SG90_Task */
  /* Infinite loop */
	volatile EventBits_t EventValue;
	while(1)
	{
		if(event_flag == 0)
			{
				event_flag = 1;
				taskENTER_CRITICAL();           //进入临界�?

				//创建事件�?
				EventGroupHandler=xEventGroupCreate();

				if(NULL!=EventGroupHandler)
					printf("EventGroupHandler success\r\n");

				taskEXIT_CRITICAL();            //�?出临界区
			}

		   EventValue = xEventGroupWaitBits(EventGroupHandler,EVENTBIT_ALL,pdTRUE,pdFALSE,portMAX_DELAY);

		   err =  0;
			printf("open door\r\n");

			 OLED_Clear();                         //清屏
			//上面的初始化以及清屏的代码在�?�?始处�?定要�?
			 OLED_ShowString(2,2,"OPEN",16, 1);    //反相显示8X16字符�?
			 OLED_DrawBMP(90,0,122, 4,BMP1,0);//正相显示图片BMP1

			 //模拟关门
			 vTaskDelay(2000);
			 OLED_Clear();                         //清屏
			//上面的初始化以及清屏的代码在�?�?始处�?定要�?
			  OLED_DrawBMP(0,0,32, 4,BMP1,1);//正相显示图片BMP1
			 OLED_DrawBMP(90,0,122, 4,BMP1,0);//正相显示图片BMP1
//			set_Angle(180);
//			delay_xms(1000);
//			delay_xms(1000);
//			set_Angle(0);
//			LCD_ShowString(80,150,260,16,16,"              ");

			vTaskDelay(100); //延时10ms，也就是10个时钟节�?

	}
  /* USER CODE END SG90_Task */
}

/* USER CODE BEGIN Header_RC522_Task */
/**
* @brief Function implementing the RC522TASK thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_RC522_Task */
void RC522_Task(void *argument)
{
  /* USER CODE BEGIN RC522_Task */
  /* Infinite loop */
	while(1)
	 {
		if(CardAuthState() == MI_OK)
		{
			if(CardJudge() == MI_OK)
			{
				//触发蜂鸣�?
//				BEEP(0);
//				vTaskDelay(100);
//				 BEEP(1);

				xEventGroupSetBits(EventGroupHandler,EVENTBIT_1);
				printf("rc522 success\r\n");

			}
			else
			{
//				BEEP(0);
//				vTaskDelay(100);
//				 BEEP(1);
//				 vTaskDelay(100);
//				BEEP(0);
//				vTaskDelay(100);
//				 BEEP(1);
//				 vTaskDelay(100);

			  printf("rc522 fail\r\n");
				err++;

			}



		}

		vTaskDelay(100); //延时10ms，也就是10个时钟节�?
	 }
  /* USER CODE END RC522_Task */
}

/* USER CODE BEGIN Header_esp8266_Task */
/**
* @brief Function implementing the esp8266Task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_esp8266_Task */
void esp8266_Task(void *argument)
{
  /* USER CODE BEGIN esp8266_Task */
  /* Infinite loop */
	int esp_falg = 0;
	while(1)
	{
		  if(esp8266_wait_receive() == ESP8266_EOK)
			{
				printf("receive: %s\r\n", g_uart_rx_buf);
				printf("receive: %d\r\n", esp8266_cnt);
				if(strstr(g_uart_rx_buf,"666" ) != NULL)
				{
//					BEEP(0);
//					vTaskDelay(100);
//					 BEEP(1);
					printf("esp open success\r\n");
					xEventGroupSetBits(EventGroupHandler,EVENTBIT_0);

				}
				else
				{
//					BEEP(0);
//					vTaskDelay(100);
//					 BEEP(1);
//					 vTaskDelay(100);
//					BEEP(0);
//					vTaskDelay(100);
//					 BEEP(1);
//					 vTaskDelay(100);
					if(esp_falg)
					{
						printf("esp fail\r\n");
						err++;
					}

					if(strstr(g_uart_rx_buf,"0,CONNECT" ) != NULL)
					{
						esp_falg = 1;
					}


				}

				esp8266_clear();
			}
		vTaskDelay(100);
	}
  /* USER CODE END esp8266_Task */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

