#ifdef EepromTest
#include "EepromTest.H"

#include "STM32_PWM.H"
#include "STM32_GPIO.H"
#include "STM32_SYS.H"
#include "STM32_WDG.H"
#include "STM32_SYSTICK.H"
#include "STM32_USART.H"
#include "STM32F10x_BitBand.H"


#include "AT24C02.H"
#include "I2C.H"	

#include	"stdio.h"			//用于printf
#include	"string.h"		//用于printf
#include	"stdarg.h"		//用于获取不确定个数的参数
#include	"stdlib.h"		//malloc动态申请内存空间


//#include "delay.h"
//#include "sys.h"
//#include "STM32_096OLED.h"
//#include "bmp.h"


sI2CDef At24c02;

unsigned	char ReadBuffer[5000]={0};
	
unsigned	short time=	0;

/*******************************************************************************
* 函数名		:	
* 功能描述	:	 
* 输入		:	
* 输出		:
* 返回 		:
*******************************************************************************/
void EepromTest_Configuration(void)
{

	SYS_Configuration();				//系统配置
	At24c02.SDA_Port	=	GPIOB;
	At24c02.SDA_Pin		=	GPIO_Pin_7;
	At24c02.SCL_Port	=	GPIOB;
	At24c02.SCL_Pin		=	GPIO_Pin_6;
	I2C_Configuration(&At24c02);	//启用锁--配置
	
	SysTick_Configuration(1000);	//系统嘀嗒时钟配置72MHz,单位为uS
	PWM_OUT(TIM2,PWM_OUTChannel1,1,900);						//PWM设定-20161127版本
	
}
/*******************************************************************************
* 函数名		:	
* 功能描述	:	 
* 输入		:	
* 输出		:
* 返回 		:
*******************************************************************************/
void EepromTest_Server(void)
{
	time++;
	if(time==1)
	{
		
		I2C_ReadBuffer(&At24c02,0,ReadBuffer,256);
	}
	else if(time==5000)
	{
		//memset(ReadBuffer,0x00,2048);
	}
	else if(time>=6000)
	{
		time=	0;
	}

}





#endif
