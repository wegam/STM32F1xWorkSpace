#ifdef PWM_TEST
#include "PWM_TEST.H"

#include "string.h"
#include "math.h"


#include "STM32_EXTI.H"
#include "STM32_USART.H"

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
/*******************************************************************************
* 函数名		:	
* 功能描述	:	 
* 输入		:	
* 输出		:
* 返回 		:
*******************************************************************************/
void PWM_TEST_Configuration(void)
{
	SYS_Configuration();				//系统配置
	GPIO_DeInitAll();													//将所有的GPIO关闭----V20170605
	SysTick_Configuration(1000);	//系统嘀嗒时钟配置72MHz,单位为uS

	PWM_Tim.PWM_BasicData.GPIOx	=	GPIOB;
	PWM_Tim.PWM_BasicData.GPIO_Pin_n	=	GPIO_Pin_0;
	
	PWM_Tim.PWM_BasicData.TIMx	=	TIM1;
	PWM_Tim.PWM_BasicData.PWM_Frequency	=	100000;
	
	
	PWM_OUT_TIMConf(&PWM_Tim);			//PWM输出配置
	
	PWM_OUT_SetCount(&PWM_Tim,10);		//设置计数值
}
/*******************************************************************************
* 函数名		:	
* 功能描述	:	 
* 输入		:	
* 输出		:
* 返回 		:
*******************************************************************************/
void PWM_TEST_Server(void)
{
	if(PWM_OUT_TIMServer(&PWM_Tim)	==1)
	{
		systime	=	0;
	}
	else
	{
		systime++;
		if(systime>=2000)
		{
			systime	=	0;
			PWM_OUT_SetCount(&PWM_Tim,2500*Ncycle);		//设置计数值
		}
	}
	//========================
//	if(PWM_CountServer()	==1)
//	{
//	}
//	else
//	{
//		systime++;
//		if(systime>=100)
//		{
//			systime	=	0;
//			SetPWM_Num(TIM2,10);		//设置计数值
//		}
//	}
	
	

}


#endif
