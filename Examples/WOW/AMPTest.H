#ifndef __AMPTest_H
#define __AMPTest_H


//#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
//#include "stm32f10x_nvic.h"
//#include "stm32f10x_spi.h"

//#include "STM32_GPIO.H"


//#include	"stdio.h"			//用于printf
//#include	"string.h"			//用于printf
//#include	"stdarg.h"			//用于获取不确定个数的参数
//#include	"stdlib.h"			//malloc动态申请内存空间


#include "ff.h"			/* Declarations of FatFs API */

#define SD_CLK_SpeedL	0
#define SD_CLK_SpeedH	1

#define LCD_SD_CS_PORT				GPIOC
#define LCD_SD_CS_PIN					GPIO_Pin_6	

extern unsigned char STM32_LCD_Steep;			//程序运行阶段--LCD部分
extern unsigned char STM32_SD_Steep;			//程序运行阶段--SD卡部分


extern void AMPTest_Configuration(void);
extern void AMPTest_Server(void);

void USART_Server(void);

void RTC_Server(void);

void Power_Configuration(void);
void Power_Server(void);
void LCD_Server(void);			//显示服务相关


void SD_Configuration(void);
void LCD_Configuration(void);
void SSD1963_Init(void);

void ImageDisp(unsigned char* buffer,unsigned long len);

#endif
