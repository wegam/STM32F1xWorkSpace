#ifdef Vl53l0x_TEST

#include "Vl53l0x_TEST.H"

#include "vl53l0x.h"


#include "STM32_PWM.H"
#include "STM32_GPIO.H"
#include "STM32_SYS.H"
#include "STM32_WDG.H"
#include "STM32_SYSTICK.H"
#include "STM32_USART.H"
#include "STM32F10x_BitBand.H"

stvl53l0xDef stvl53l0x;

//#include "STM32_SPI.H"
void APIConfiguration(void);

unsigned	short time=	0;
/*******************************************************************************
* 函数名		:	
* 功能描述	:	 
* 输入		:	
* 输出		:
* 返回 		:
*******************************************************************************/
void Vl53l0xTest_Configuration(void)
{	
//	SYS_Configuration();					//系统配置---打开系统时钟 STM32_SYS.H
  RCC_Configuration_HSI();
	
	GPIO_DeInitAll();							//将所有的GPIO关闭----V20170605
	
	SysTick_Configuration(1000);	//系统嘀嗒时钟配置72MHz,单位为uS
	
	APIConfiguration();
//	IWDG_Configuration(1000);			//独立看门狗配置---参数单位ms	
	
	PWM_OUT(TIM2,PWM_OUTChannel1,1,500);						//PWM设定-20161127版本
	
}
/*******************************************************************************
* 函数名		:	
* 功能描述	:	 
* 输入		:	
* 输出		:
* 返回 		:
*******************************************************************************/
void Vl53l0xTest_Server(void)
{
	if(time++>1000)
	{
		time	=	0;
		vl53l0x_ReadData();
	}
}
/*******************************************************************************
* 函数名			:	function
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
void APIConfiguration(void)
{
	stvl53l0x.Port.SDA_Port	=	GPIOA;	
	stvl53l0x.Port.SDA_Pin	=	GPIO_Pin_10;		//RXD
	
	stvl53l0x.Port.SCL_Port	=	GPIOA;
	stvl53l0x.Port.SCL_Pin	=	GPIO_Pin_9;			//TXD
	
	vl53l0x_Initialize(&stvl53l0x);
	
	vl53l0x_ReadData();
}	


#endif


