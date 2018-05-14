#ifdef TEST
#include "TEST.H"
#include "STM32F10x_BitBand.H"
#include "STM32_GPIO.H"
#include "STM32_SYS.H"
#include "STM32_SYSTICK.H"
#include "STM32_WDG.H"

u16 systimecount	=	0;
u8 runFlag	=	0;
/*******************************************************************************
* 函数名		:	
* 功能描述	:	 
* 输入		:	
* 输出		:
* 返回 		:
*******************************************************************************/
void TEST_Configuration(void)
{
	SYS_Configuration();
	SysTick_Configuration(1000);	//系统嘀嗒时钟配置72MHz,单位为uS
	
//	GPIO_Configuration0();
//	TIM_Configuration(TIM1,7200,3000);	//定时时间设定
//	PWM_Configuration(TIM2,7200,10000,51);
//	PWM_OUT(TIM1,PWM_OUTChannel1,20000,50);		//PWM设定
//	PWM_OUT(TIM2,PWM_OUTChannel1,20000,500);	//PWM设定
//	PWM_OUT(TIM3,PWM_OUTChannel1,5000,30);		//PWM设定
//	PWM_OUT(TIM3,PWM_OUTChannel2,5000,30);		//PWM设定
//	PWM_OUT(TIM3,PWM_OUTChannel3,1000,500);		//PWM设定
//	PWM_OUT(TIM4,PWM_OUTChannel1,20000,40);		//PWM设定
	
	PWM_OUT(TIM2,PWM_OUTChannel1,5000,500);		//PWM设定--SYS-LED
//	GPIO_Configuration_OPP50(GPIOB,	GPIO_Pin_0);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605
	GPIO_Configuration_OPP50(GPIOB,	GPIO_Pin_1);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605
	GPIO_Configuration_IPU(GPIOB,	GPIO_Pin_4);			//将GPIO相应管脚配置为上拉输入模式----V20170605
	GPIO_Configuration_IPU(GPIOB,	GPIO_Pin_5);			//将GPIO相应管脚配置为上拉输入模式----V20170605
	GPIO_Configuration_IPU(GPIOB,	GPIO_Pin_6);			//将GPIO相应管脚配置为上拉输入模式----V20170605
	GPIO_Configuration_IPU(GPIOB,	GPIO_Pin_7);			//将GPIO相应管脚配置为上拉输入模式----V20170605
	PB1	=	0;
//	PWM_OUT(TIM2,PWM_OUTChannel2,20000,500);	//PWM设定

	PWM_OUT_COUNT(TIM3,PWM_OUTChannel3,1000,500);		//电机脉冲频率
//	SetPWM_Num(TIM3,100);		//设置计数值

}
/*******************************************************************************
* 函数名		:	
* 功能描述	:	 
* 输入		:	
* 输出		:
* 返回 		:
*******************************************************************************/
void TEST_Server(void)
{
	if(PWM_CountServer()	==1)
	{
		if(Tim3_Count	==	0)
		{
			systimecount	=	0;
			runFlag	=	0;
		}
		return;
	}
	if(runFlag	==	1)
	{
		return;
	}
	systimecount++;
	if(systimecount>=2000)
	{
		SetPWM_Num(TIM3,1*(2500-1));		//设置计数值
		systimecount=0;
		runFlag	=	1;
//		GPIO_Toggle	(GPIOB,	GPIO_Pin_1);		//将GPIO相应管脚输出翻转----V20170605
	}
//	if(systimecount	==	0)
//	GPIO_Toggle	(GPIOB,	GPIO_Pin_0);		//将GPIO相应管脚输出翻转----V20170605
}





#endif
