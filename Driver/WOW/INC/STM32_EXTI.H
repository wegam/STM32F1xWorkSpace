/******************************** User_library *********************************
* 文件名 	: STM32_SDCard.H
* 作者   	: wegam@sina.com
* 版本   	: V
* 日期   	: 2016/01/01
* 说明   	: 
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/


#ifndef __STM32_EXTI_H
#define __STM32_EXTI_H


#include "stm32f10x_gpio.h"

typedef struct _Trigger_Line
{
	unsigned short Trigger_Line0:1;
	unsigned short Trigger_Line1:1;
	unsigned short Trigger_Line2:1;
	unsigned short Trigger_Line3:1;
	unsigned short Trigger_Line4:1;
	unsigned short Trigger_Line5:1;
	unsigned short Trigger_Line6:1;
	unsigned short Trigger_Line7:1;
	unsigned short Trigger_Line8:1;
	unsigned short Trigger_Line9:1;
	unsigned short Trigger_Line10:1;
	unsigned short Trigger_Line11:1;
	unsigned short Trigger_Line12:1;
	unsigned short Trigger_Line13:1;
	unsigned short Trigger_Line14:1;
	unsigned short Trigger_Line15:1;
}Trigger_LineType;

extern Trigger_LineType Trigger_Line;


void EXTI_Configuration_ITR		(GPIO_TypeDef* GPIOx, u16 GPIO_Pin);		//外部上升沿中断配置,抢占1，响应1--20171213
void EXTI_Configuration_ITF		(GPIO_TypeDef* GPIOx, u16 GPIO_Pin);		//外部下降沿中断配置,抢占1，响应1--20171213
void EXTI_Configuration_ITRF	(GPIO_TypeDef* GPIOx, u16 GPIO_Pin);		//外部边沿触发中断配置,抢占1，响应1--20171213




void EXTI_Server(void);
#endif


