#ifdef SteepMotorTest
#include "SteepMotorTest.H"


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


SteepMotor_Def	SteepMotor1;

u32 SYSTIME	=	0;
u8	Flg	=	0;

/*******************************************************************************
* 函数名		:	
* 功能描述	:	 
* 输入		:	
* 输出		:
* 返回 		:
*******************************************************************************/
void SteepMotorTest_Configuration(void)
{
	SYS_Configuration();						//系统配置 STM32_SYS.H	
	SysTick_DeleyS(2);						//SysTick延时nS
	SysTick_Configuration(1000);		//系统嘀嗒时钟配置72MHz,单位为uS----定时扫描PC006V21_Server
	Motor_Configuration();
}

/*******************************************************************************
* 函数名		:	
* 功能描述	:	 
* 输入		:	
* 输出		:
* 返回 		:
*******************************************************************************/
void SteepMotorTest_Server(void)
{
	if(StepMotorServer(&SteepMotor1))
	{
		SYSTIME	=	0;
		return;
	}
	SYSTIME++;
//	if(SYSTIME>=10000)
//		SYSTIME	=0;
	if(SYSTIME>=1000)
	{
		SYSTIME	=0;
//		StepMotorCW(&SteepMotor1,40000,1,10000,1,10000,22000);		//顺时针旋转
		
		if(Flg	==	0)
		{
			Flg	=	1;
			StepMotorCW(&SteepMotor1,40000,1,10000,1,10000,22000);		//顺时针旋转
		}
		else
		{
			Flg	=	0;
			StepMotorCCW(&SteepMotor1,4000,1,10000,1,10000,22000);		//顺时针旋转
		}
//		SteepMotor1.SetDIRPort->BRR	=	SteepMotor1.SetDIRPin;		//低电平：顺时针转
//		SteepMotor1.SetPulsPort->BSRR	=	SteepMotor1.SetPulsPin;		//低电平：顺时针转
//		StepMotorCW(&SteepMotor1,500,100,1000,1,50,1000);		//顺时针旋转
	}
	else if(SYSTIME%200==100)
	{
//		SteepMotor1.SetDIRPort->BSRR	=	SteepMotor1.SetDIRPin;		//低电平：顺时针转
//		SteepMotor1.SetPulsPort->BRR	=	SteepMotor1.SetPulsPin;		//低电平：顺时针转
//		StepMotorCCW(&SteepMotor1,500,100,1000,1,50,1000);		//顺时针旋转
	}
	
	
}


/*******************************************************************************
*函数名			:	function
*功能描述		:	function
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
void Motor_Configuration(void)
{
	SteepMotor1.SetTIMx			=	TIM1;
	
	SteepMotor1.SetPulsPort	=	GPIOA;
	SteepMotor1.SetPulsPin	=	GPIO_Pin_11;
	
	SteepMotor1.SetDIRPort	=	GPIOA;
	SteepMotor1.SetDIRPin		=	GPIO_Pin_12;
	
	SteepMotor1.SetFrequency	=	1000;
	
	StepMotorConfiguration(&SteepMotor1);		//
}



#endif
