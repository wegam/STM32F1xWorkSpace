#ifndef __PD010V20_H
#define __PD010V20_H

#include	"stdio.h"			//用于printf
#include	"string.h"		//用于printf
#include	"stdarg.h"		//用于获取不确定个数的参数
#include	"stdlib.h"		//malloc动态申请内存空间




#include "STM32_SYS.H"
#include "STM32_SYSTICK.H"
#include "STM32F10x_BitBand.H"

#include "STM32_GPIO.H"
#include "STM32_PWM.H"
#include "STM32_USART.H"
#include "STM32_CAN.H"
#include "STM32_WDG.H"







void PD010V20CAN_Configuration(void);
void PD010V20CAN_Server(void);


void RS232_Configuration(void);
void RS485_Configuration(void);
void CAN_Configuration(void);





void RS232_Server(void);
void RS485_Server(void);
void CAN_Server(void);

#endif

