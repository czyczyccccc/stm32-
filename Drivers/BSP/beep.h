/*
 * beep.h
 *
 *  Created on: Aug 2, 2024
 *      Author: 13083
 */

#ifndef BSP_BEEP_H_
#define BSP_BEEP_H_

#include "../SYSTEM/sys/sys.h"

/******************************************************************************************/

/* 蜂鸣器控制,低电平触发（BEEP(0)） */
#define BEEP(x)         do{ x ? \
                            HAL_GPIO_WritePin(BEEP_GPIO_Port, BEEP_Pin, GPIO_PIN_SET) : \
                            HAL_GPIO_WritePin(BEEP_GPIO_Port, BEEP_Pin, GPIO_PIN_RESET); \
                        }while(0)

/* BEEP状态翻转 */
#define BEEP_TOGGLE()   do{ HAL_GPIO_TogglePin(BEEP_GPIO_Port, BEEP_Pin); }while(0)     /* BEEP = !BEEP */



#endif /* BSP_BEEP_H_ */
