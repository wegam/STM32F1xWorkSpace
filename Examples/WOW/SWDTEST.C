/******************************** User_library *********************************
* 文件名 	: SWDTEST.C
* 作者   	: wegam@sina.com
* 版本   	: V
* 日期   	: 2017/04/16
* 说明   	: 
********************************************************************************
SPI_FLASH使用功能测试
1）需要宏定义 SPI_FLASH
2）使用USB_TEST 板测试
3）需要宏定义SPI引脚

*******************************************************************************/
#ifdef SWDTEST							//如果定义了A3987_TEST 此功能生效

#include "STM32F10x_BitBand.H"
#include "stm32f10x_nvic.h"


#include	"stdio.h"				//用于printf
#include	"string.h"			//用于printf
#include	"stdarg.h"			//用于获取不确定个数的参数
#include	"stdlib.h"			//malloc动态申请内存空间
	
#include	"stddef.h"
#include	"stdint.h"



#include "SWDTEST.H"

#include "swd.h"

#include "STM32_GPIO.H"
#include "STM32_SYS.H"
#include "STM32_SYSTICK.H"

unsigned short Time	=	0;
/*******************************************************************************
* 函数名		:	
* 功能描述	:	 
* 输入		:	
* 输出		:
* 返回 		:
*******************************************************************************/
void SWDTEST_Configuration(void)
{
	SYS_Configuration();					//系统配置---打开系统时钟 STM32_SYS.H
	
	GPIO_DeInitAll();							//将所有的GPIO关闭----V20170605
	
	SysTick_Configuration(1000);	//系统嘀嗒时钟配置72MHz,单位为uS
	
	GPIO_Configuration_OPP50	(SWDIO_PORT,SWDIO_PIN);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605
	GPIO_Configuration_OPP50	(SWCLK_PORT,SWCLK_PIN);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605
	
	SW_PinInit();
	
	SWJ_InitDebug();
}

/*******************************************************************************
* 函数名		:	
* 功能描述	:	 
* 输入		:	
* 输出		:
* 返回 		:
*******************************************************************************/
void SWDTEST_Server(void)		//CRC--TEST
{	
	if(Time++>1000)
	{
		Time	=	0;
		SWJ_InitDebug();
	}
}






























#endif
