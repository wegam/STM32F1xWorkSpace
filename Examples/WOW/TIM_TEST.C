#ifdef TIM_TEST
#include "TIM_TEST.H"

#include "string.h"
#include "math.h"


#include "STM32_EXTI.H"
#include "STM32_USART.H"
#include "STM32_TIM.H"
#include "STM32_SYS.H"
#include "STM32_SYSTICK.H"
#include "STM32_GPIO.H"
#include "STM32F10x_BitBand.H"

#define RxBufferSize	16
#define Ncycle	0

PWM_TimDef 	PWM_Tim;
volatile GPIO_TypeDef* 	GPIOx;			//x=A/B/C/D/E/F/G
volatile TIM_TypeDef* 	TIMx;
volatile u32* p	=	0;
volatile u32 temp	=	0;
u16 systime	=	0;
volatile u16 Pin	=	0;

u16	RunFrequency			=	0;		//当前运行频率
/*******************************************************************************
* 函数名		:	
* 功能描述	:	 
* 输入		:	
* 输出		:
* 返回 		:
*******************************************************************************/
void TIM_TEST_Configuration(void)
{
	SYS_Configuration();				//系统配置
	GPIO_DeInitAll();													//将所有的GPIO关闭----V20170605
//	SysTick_Configuration(1000);	//系统嘀嗒时钟配置72MHz,单位为uS
	GPIO_Configuration_OPP50	(GPIOA,	GPIO_Pin_7);			//将GPIO相应管脚配置为APP(复用推挽)输出模式，最大速度50MHz----V20170605
	TIM_ConfigurationFreq(TIM1,40000);	//定时器频率配置方式，最小频率0.01Hz,最大100KHz
	
	TIM1->RCR = 100-1;
	
	TIM_Cmd(TIM1, ENABLE); 									//使能TIM
	
	RunFrequency			=	500;		//当前运行频率
}
/*******************************************************************************
* 函数名		:	
* 功能描述	:	 
* 输入		:	
* 输出		:
* 返回 		:
*******************************************************************************/
void TIM_TEST_Server(void)
{
//	RunFrequency	++;		//当前运行频率
//	if(RunFrequency>=5000000)
//		RunFrequency	=500;
	temp	--;		//当前运行频率
	if(temp<2)
	{
		temp	=100;
//		TIM1->RCR = temp;
	}
	if(temp%2	==	0)
	{
		TIM1->RCR = temp-1;
	}
	
	RunFrequency	++;		//当前运行频率
	if(RunFrequency>=50000)
		RunFrequency	=500;
	
	if(RunFrequency%10	==	0)
	{
//		TIM1->RCR = temp;
	TIM_SetFreq(TIM1,RunFrequency);		//设定频率
	}
	GPIO_Toggle	(GPIOA,	GPIO_Pin_7);		//将GPIO相应管脚输出翻转----V20170605
}


#endif
