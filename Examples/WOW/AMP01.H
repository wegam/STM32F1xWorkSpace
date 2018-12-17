#ifndef __AMP01_H
#define __AMP01_H


//#include "stm32f10x_gpio.h"
//#include "stm32f10x_rcc.h"
//#include "stm32f10x_nvic.h"
//#include "stm32f10x_spi.h"

//#include "STM32_GPIO.H"


//#include	"stdio.h"			//用于printf
//#include	"string.h"			//用于printf
//#include	"stdarg.h"			//用于获取不确定个数的参数
//#include	"stdlib.h"			//malloc动态申请内存空间





extern void AMP01_Configuration(void);
extern void AMP01_Server(void);

void USART_Server(void);


void COMM_Configuration(void);

#endif
