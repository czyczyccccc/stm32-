/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    usart.c
  * @brief   This file provides code for the configuration
  *          of the USART instances.
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
#include "usart.h"

/* USER CODE BEGIN 0 */
#ifdef __GNUC__
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif

PUTCHAR_PROTOTYPE
{
	HAL_UART_Transmit(&huart1, (uint8_t*)&ch, 1, HAL_MAX_DELAY);
	return ch;
}


/* 接收缓冲, 最大USART_REC_LEN个字节. */
uint8_t g_usart_rx_buf[USART_REC_LEN];

/*  接收状态
 *  bit15，      接收完成标志
 *  bit14，      接收到0x0d
 *  bit13~0，    接收到的有效字节数目
*/
uint16_t g_usart_rx_sta = 0;

uint8_t g_rx_buffer[RXBUFFERSIZE];  /* HAL库使用的串口接收缓冲 */

UART_HandleTypeDef huart1;  /* UART句柄 */
UART_HandleTypeDef huart2;  /* UART句柄 */
/* USER CODE END 0 */

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;

/* USART1 init function */

void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */
  /* 该函数会开启接收中断：标志位UART_IT_RXNE，并且设置接收缓冲以及接收缓冲接收最大数据量 */
    HAL_UART_Receive_IT(&huart1, (uint8_t *)g_rx_buffer, RXBUFFERSIZE);
  /* USER CODE END USART1_Init 2 */

}
/* USART2 init function */



void HAL_UART_MspInit(UART_HandleTypeDef* huart)
{

  /* USER CODE BEGIN USART2_MspInit 1 */
    GPIO_InitTypeDef gpio_init_struct;

        if (huart->Instance == USART_UX)                            /* 如果是串口1，进行串口1 MSP初始化 */
        {
            USART_TX_GPIO_CLK_ENABLE();                             /* 使能串口TX脚时钟 */
            USART_RX_GPIO_CLK_ENABLE();                             /* 使能串口RX脚时钟 */
            USART_UX_CLK_ENABLE();                                  /* 使能串口时钟 */

            gpio_init_struct.Pin = USART_TX_GPIO_PIN;               /* 串口发送引脚号 */
            gpio_init_struct.Mode = GPIO_MODE_AF_PP;                /* 复用推挽输出 */
            gpio_init_struct.Pull = GPIO_PULLUP;                    /* 上拉 */
            gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;          /* IO速度设置为高速 */
            HAL_GPIO_Init(USART_TX_GPIO_PORT, &gpio_init_struct);

            gpio_init_struct.Pin = USART_RX_GPIO_PIN;               /* 串口RX脚 模式设置 */
            gpio_init_struct.Mode = GPIO_MODE_AF_INPUT;
            HAL_GPIO_Init(USART_RX_GPIO_PORT, &gpio_init_struct);   /* 串口RX脚 必须设置成输入模式 */

    #if USART_EN_RX
            HAL_NVIC_EnableIRQ(USART_UX_IRQn);                      /* 使能USART1中断通道 */
            HAL_NVIC_SetPriority(USART_UX_IRQn, 3, 3);              /* 组2，最低优先级:抢占优先级3，子优先级3 */
    #endif
        }
        else if (huart->Instance == ESP8266_UART_INTERFACE)                 /* 如果是ESP8266 UART */
        {
            ESP8266_UART_TX_GPIO_CLK_ENABLE();                              /* 使能UART TX引脚时钟 */
            ESP8266_UART_RX_GPIO_CLK_ENABLE();                              /* 使能UART RX引脚时钟 */
            ESP8266_UART_CLK_ENABLE();                                      /* 使能UART时钟 */

            gpio_init_struct.Pin    = ESP8266_UART_TX_GPIO_PIN;             /* UART TX引脚 */
            gpio_init_struct.Mode   = GPIO_MODE_AF_PP;                          /* 复用推挽输出 */
            gpio_init_struct.Pull   = GPIO_NOPULL;                              /* 无上下拉 */
            gpio_init_struct.Speed  = GPIO_SPEED_FREQ_HIGH;                     /* 高速 */
            HAL_GPIO_Init(ESP8266_UART_TX_GPIO_PORT, &gpio_init_struct);    /* 初始化UART TX引脚 */

            gpio_init_struct.Pin    = ESP8266_UART_RX_GPIO_PIN;             /* UART RX引脚 */
            gpio_init_struct.Mode   = GPIO_MODE_INPUT;                          /* 输入 */
            gpio_init_struct.Pull   = GPIO_NOPULL;                              /* 无上下拉 */
            gpio_init_struct.Speed  = GPIO_SPEED_FREQ_HIGH;                     /* 高速 */
            HAL_GPIO_Init(ESP8266_UART_RX_GPIO_PORT, &gpio_init_struct);    /* 初始化UART RX引脚 */

            HAL_NVIC_SetPriority(ESP8266_UART_IRQn, 0, 0);                  /* 抢占优先级0，子优先级0 */
            HAL_NVIC_EnableIRQ(ESP8266_UART_IRQn);                          /* 使能UART中断通道 */

            __HAL_UART_ENABLE_IT(huart, UART_IT_RXNE);                          /* 使能UART接收中断 */
  /* USER CODE END USART2_MspInit 1 */
  }
}


/* USER CODE BEGIN 1 */
/**
 * @brief       串口数据接收回调函数
                数据处理在这里进行
 * @param       huart:串口句柄
 * @retval      无
 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART1)                      /* 如果是串口1 */
    {
        if ((g_usart_rx_sta & 0x8000) == 0)             /* 接收未完成 */
        {
            if (g_usart_rx_sta & 0x4000)                /* 接收到了0x0d（即回车键） */
            {
                if (g_rx_buffer[0] != 0x0a)             /* 接收到的不是0x0a（即不是换行键） */
                {
                    g_usart_rx_sta = 0;                 /* 接收错误,重新开始 */
                }
                else                                    /* 接收到的是0x0a（即换行键） */
                {
                    g_usart_rx_sta |= 0x8000;           /* 接收完成了 */
                }
            }
            else                                        /* 还没收到0X0d（即回车键） */
            {
                if (g_rx_buffer[0] == 0x0d)
                    g_usart_rx_sta |= 0x4000;
                else
                {
                    g_usart_rx_buf[g_usart_rx_sta & 0X3FFF] = g_rx_buffer[0];
                    g_usart_rx_sta++;

                    if (g_usart_rx_sta > (USART_REC_LEN - 1))
                    {
                        g_usart_rx_sta = 0;             /* 接收数据错误,重新开始接收 */
                    }
                }
            }
        }

        HAL_UART_Receive_IT(&huart1, (uint8_t *)g_rx_buffer, RXBUFFERSIZE);
    }
}

/* USER CODE END 1 */
