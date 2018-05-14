#ifdef SysTick_TEST
#include "SysTick_TEST.H"


#include "SteepMotor.H"
#include "STM32_TIM.H"
#include "SWITCHID.H"
#include "STM32_WDG.H"
#include "STM32_EXTI.H"
#include "STM32_GPIO.H"
#include "STM32_PWM.H"
#include "STM32_SYS.H"
#include "STM32_SYSTICK.H"
#include "STM32_CAN.H"
#include "STM32F10x_BitBand.H"
u32 SYSTIME	=	0;
/*******************************************************************************
* 函数名		:	
* 功能描述	:	 
* 输入		:	
* 输出		:
* 返回 		:
*******************************************************************************/
void SysTick_TEST_Configuration(void)
{
	SYS_Configuration();						//系统配置 STM32_SYS.H	
	SysTick_DeleyS(2);						//SysTick延时nS
	SysTick_Configuration(1000);		//系统嘀嗒时钟配置72MHz,单位为uS----定时扫描PC006V21_Server
	GPIO_Configuration_OPP50	(GPIOA,	GPIO_Pin_0);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605
//	while(1)
//	{
////		SysTick_DeleyS(15);				//SysTick延时nuS
//		SysTick_DeleymS(100);								//
//		GPIO_Toggle	(GPIOA,	GPIO_Pin_0);		//将GPIO相应管脚输出翻转----V20170605
//	}
}

/*******************************************************************************
* 函数名		:	
* 功能描述	:	 
* 输入		:	
* 输出		:
* 返回 		:
*******************************************************************************/
void SysTick_TEST_Server(void)
{
	SYSTIME++;
	if(SYSTIME>=10000)
		SYSTIME	=0;
	if(SYSTIME%10==0)
	{
		SysTick_DeleyS(1);						//SysTick延时nS
		GPIO_Toggle	(GPIOA,	GPIO_Pin_0);		//将GPIO相应管脚输出翻转----V20170605
	}
}





#endif
