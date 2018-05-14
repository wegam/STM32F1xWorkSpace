/******************************** User_library *********************************
* 文件名 	: STM32_SDCard.H
* 作者   	: wegam@sina.com
* 版本   	: V
* 日期   	: 2016/01/01
* 说明   	: 
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/


#include "STM32_TIM.H"
#include "STM32_WOW.H"
//#include "STM32F10x_BitBand.H"



///* 定时器结构体 */
///* TIM Time Base Init structure definition */
//typedef struct
//{
//  u16 TIM_Prescaler;								//-------分频系数,=======取值0x0000~0xFFFF，用来分频TIM clock
//  u16 TIM_CounterMode;							//-------计数方式========TIM_CounterMode_Up(向上计数模式),TIM_CounterMode_Down(向下计数模式),
																			//-----------------------TIM_CounterMode_CenterAligned1(中央对齐模式1计数模式),TIM_CounterMode_CenterAligned2(中央对齐模式2计数模式),TIM_CounterMode_CenterAligned3(中央对齐模式3计数模式)
//  u16 TIM_Period;										//-------计数值==========下一个更新事件装入活动的自动重装载寄存器周期的值,取值0x0000~0xFFFF,计数TIM_Period+1个节拍后产生溢出
//  u16 TIM_ClockDivision;						//-------设定时间分割值===默认为0,特殊场合时TIM_ClockDivision用来做一段延时,TIM_CKD_DIV1,TIM_CKD_DIV2,TIM_CKD_DIV3
//  u8 TIM_RepetitionCounter;					//-------重复计数次数=====重复多少次溢出后才触发一次溢出中断，
//} TIM_TimeBaseInitTypeDef;


/*******************************************************************************
* 函数名		:	PWM_OUT	
* 功能描述	:		 
* 输入		:	PWM_Frequency 频率，单位Hz	
* 输出		:
* 返回 		:
*******************************************************************************/
void TIM_ConfigurationFreq(TIM_TypeDef* TIMx,u32 Frequency)		//定时器频率配置方式，最小频率1Hz,最大100KHz
{
	//*1,结构体定义
	//*2,变量定义
	//*3,管脚确认
	//*4,打开相应的时钟
	//*5,管脚配置（初始化）
	//*6,定时器配置（初始化）
	//*7,PWM输出配置（初始化）
	//*8,占空比配置	
		
	//*1,结构体定义***********************************************************************
	//1）============================结构体定义
//	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef	TIM_TimeBaseStructure;	//定时器结构体定义	
	RCC_ClocksTypeDef RCC_ClocksStatus;							//时钟状态---时钟值
	NVIC_InitTypeDef	NVIC_InitStructure;						//中断结构体
	
	//1）============================临时变量定义

//	u16 GPIO_Pin_n				=	PWM_Tim->PWM_BasicData.GPIO_Pin_n;
//	double PWM_Frequency	=	2*(PWM_Tim->PWM_BasicData.PWM_Frequency);
	
	u8 TIM_IRQChannel=0;
	u32	Tim_temp				=	2*Frequency;	//由于翻转需要双倍频率
	u32	TIMx_Frequency				=	0;			//	定时器时钟
	u16 TIMx_Prescaler				=	0	;			//	定时器时钟分频值		取值范围：0x0000~0xFFFF
  u16 TIMx_Period						=	0	;			//	定时器自动重装载值	取值范围：0x0000~0xFFFF



	//1）============================打开定时器时钟
	switch ((u32)TIMx)
	{
		case TIM1_BASE:
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
			TIM_IRQChannel=TIM1_UP_IRQChannel;	
			TIM_TimeBaseStructure.TIM_RepetitionCounter	=	0;
			break;
		
		case TIM2_BASE:
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
			TIM_IRQChannel=TIM2_IRQChannel;
			break;
		
		case TIM3_BASE:
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
			TIM_IRQChannel=TIM3_IRQChannel;
			break;
		
		case TIM4_BASE:
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
			TIM_IRQChannel=TIM4_IRQChannel;
			break;
		
		case TIM5_BASE:
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
			TIM_IRQChannel=TIM5_IRQChannel;
			break;
		
		case TIM6_BASE:
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);
			TIM_IRQChannel=TIM6_IRQChannel;
			break;
		
		case TIM7_BASE:
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);
			TIM_IRQChannel=TIM7_IRQChannel;
			break;
		
		case TIM8_BASE:
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);
			TIM_IRQChannel=TIM8_UP_IRQChannel;
			TIM_TimeBaseStructure.TIM_RepetitionCounter	=	0;
			break;
		
		default:
			break;		
	}
	//1）============================获取TIMx时钟频率
	//1）-----分频值及自动重装载值计算（PWM_Frequency 频率，单位Hz）
	//--------1MHz 1us=1000ns,1KHz 10us=10000ns
	RCC_GetClocksFreq(&RCC_ClocksStatus);	//获取时钟参数
	TIMx_Frequency = RCC_ClocksStatus.SYSCLK_Frequency;
	if ((((u32)TIMx)&APB2PERIPH_BASE) == APB2PERIPH_BASE)
  {
    TIMx_Frequency = RCC_ClocksStatus.PCLK2_Frequency;	//APB2
  }
  else
  {
    TIMx_Frequency = RCC_ClocksStatus.PCLK1_Frequency;	//APB1
  }
	//1）============================计算分频值和重装载值
//	TIMx_Frequency = 72000000;
	//*6.2.4,计算定时器参数*********************************************************************
	//Fsys==Fpwm*Count==Fpwm*(Prescaler*Period)	
	//	TIMx_Prescaler				=	72-1		;		// 	定时器时钟分频值
	//	TIMx_Period						=	1000-1	;		// 	定时器自动重装载值
	//	Tim_num1							=	0				;		//	临时变量1
	if(Tim_temp>100000)		//>100KHz
	{
		TIMx_Prescaler=0;
		TIMx_Period=(u16)(TIMx_Frequency/Tim_temp-1);
	}
	else if(Tim_temp>1000)	//>1KHz
	{
		TIMx_Prescaler=10-1;
		TIMx_Period=(u16)((TIMx_Frequency/Tim_temp)/10-1);
	}
	else if(Tim_temp>100)		//>100Hz
	{
		TIMx_Prescaler=100-1;
		TIMx_Period=(u16)((TIMx_Frequency/Tim_temp)/100-1);
	}
	else if(Tim_temp>10)		//>10Hz
	{
		TIMx_Prescaler=1000-1;
		TIMx_Period=(u16)((TIMx_Frequency/Tim_temp)/1000-1);
	}
	else if(Tim_temp<=10)		//<=10Hz
	{
		TIMx_Prescaler=2000-1;
		TIMx_Period=(u16)((TIMx_Frequency/Tim_temp)/2000-1);
	}
	
//	TIMx_Prescaler=0;
//	TIMx_Period=(u16)(5-1);
	
	//6.3定时器初始化*********************************************************************
	TIM_TimeBaseStructure.TIM_Prescaler = TIMx_Prescaler; 				//设定分频值
	TIM_TimeBaseStructure.TIM_Period 		= TIMx_Period;        		//设定自动重装载值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;  				//不分割
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  		//向上计数
	TIM_TimeBaseInit(TIMx, &TIM_TimeBaseStructure);		//初始化	
		
	//*6,中断配置============================================================================
	NVIC_InitStructure.NVIC_IRQChannel = TIM_IRQChannel;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	/* Clear TIMx update pending flag[清除TIMx溢出中断] */
	TIM_ClearFlag(TIMx, TIM_FLAG_Update);

	/* Enable TIM2 Update interrupt [TIMx溢出中断允许]*/
	TIM_ITConfig(TIMx, TIM_IT_Update, ENABLE); 
	
	TIM_Cmd(TIMx, DISABLE); 									//使能TIM
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
void TIM_SetFreq(TIM_TypeDef* TIMx,u32 Frequency)		//设定频率
{
	
		
	//*1,结构体定义***********************************************************************
	//1）============================结构体定义

	RCC_ClocksTypeDef RCC_ClocksStatus;							//时钟状态---时钟值

	
	//1）============================临时变量定义


	u32	PWM_Frequency				=	2*Frequency;	//由于翻转需要双倍频率
//	u32 RCC_APB2Periph_GPIOx	=	0x00;		//x=A/B/C/D/E/F/G	
	u32	TIMx_Frequency				=	0;			//	定时器时钟
	u16 TIMx_Prescaler				=	0	;			//	定时器时钟分频值		取值范围：0x0000~0xFFFF
  u16 TIMx_Period						=	0	;			//	定时器自动重装载值	取值范围：0x0000~0xFFFF

//	TIMx->CR1 &= ((u16)0x03FE);		//CR1_CEN_Reset关闭定时器
	
	//1）============================获取TIMx时钟频率
	//1）-----分频值及自动重装载值计算（PWM_Frequency 频率，单位Hz）
	//--------1MHz 1us=1000ns,1KHz 10us=10000ns
	RCC_GetClocksFreq(&RCC_ClocksStatus);	//获取时钟参数
	TIMx_Frequency = RCC_ClocksStatus.SYSCLK_Frequency;
	if ((((u32)TIMx)&APB2PERIPH_BASE) == APB2PERIPH_BASE)
  {
    TIMx_Frequency = RCC_ClocksStatus.PCLK2_Frequency;	//APB2
  }
  else
  {
    TIMx_Frequency = RCC_ClocksStatus.PCLK1_Frequency;	//APB1
  }
	//1）============================计算分频值和重装载值
//	TIMx_Frequency = 72000000;
	//*6.2.4,计算定时器参数*********************************************************************
	//Fsys==Fpwm*Count==Fpwm*(Prescaler*Period)	
	//	TIMx_Prescaler				=	72-1		;		// 	定时器时钟分频值
	//	TIMx_Period						=	1000-1	;		// 	定时器自动重装载值
	//	Tim_num1							=	0				;		//	临时变量1
	if(PWM_Frequency<=500)		//<=500Hz
	{
		TIMx_Prescaler=2000;
		TIMx_Period=(u16)(TIMx_Frequency/TIMx_Prescaler/PWM_Frequency);
	}
	else if(PWM_Frequency<=1000)		//<=1KHz
	{
		TIMx_Prescaler=10;
		TIMx_Period=(u16)(TIMx_Frequency/TIMx_Prescaler/PWM_Frequency);
	}
	else if(PWM_Frequency<=5000)	//<=5KHz
	{
		TIMx_Prescaler=2;
		TIMx_Period=(u16)(TIMx_Frequency/TIMx_Prescaler/PWM_Frequency);
	}
	else	//>5KHz
	{
		TIMx_Prescaler=1;
		TIMx_Period=(u16)(TIMx_Frequency/TIMx_Prescaler/PWM_Frequency);
	}
//	else if(PWM_Frequency<100)		//>100kHz
//	{
//		TIMx_Prescaler=100-1;
//		TIMx_Period=(u16)((TIMx_Frequency/PWM_Frequency)/100-1);
//	}
//	else if(PWM_Frequency<10)		//>10Hz
//	{
//		TIMx_Prescaler=1000-1;
//		TIMx_Period=(u16)((TIMx_Frequency/PWM_Frequency)/1000-1);
//	}
//	else if(PWM_Frequency<=10)		//<=10Hz
//	{
//		TIMx_Prescaler=2000-1;
//		TIMx_Period=(u16)((TIMx_Frequency/PWM_Frequency)/2000-1);
//	}
	
//	if(PWM_Frequency>100000)		//>100KHz
//	{
//		TIMx_Prescaler=0;
//		TIMx_Period=(u16)(TIMx_Frequency/PWM_Frequency-1);
//	}
//	else if(PWM_Frequency>1000)	//>1KHz
//	{
//		TIMx_Prescaler=10-1;
//		TIMx_Period=(u16)((TIMx_Frequency/PWM_Frequency)/10-1);
//	}
//	else if(PWM_Frequency>100)		//>100Hz
//	{
//		TIMx_Prescaler=100-1;
//		TIMx_Period=(u16)((TIMx_Frequency/PWM_Frequency)/100-1);
//	}
//	else if(PWM_Frequency>10)		//>10Hz
//	{
//		TIMx_Prescaler=1000-1;
//		TIMx_Period=(u16)((TIMx_Frequency/PWM_Frequency)/1000-1);
//	}
//	else if(PWM_Frequency<=10)		//<=10Hz
//	{
//		TIMx_Prescaler=2000-1;
//		TIMx_Period=(u16)((TIMx_Frequency/PWM_Frequency)/2000-1);
//	}

//		TIMx_Prescaler=0;
//		TIMx_Period=(u16)(5-1);

	//6.3定时器初始化*********************************************************************
	
	
	
  /* Set the Prescaler value */
  TIMx->PSC = TIMx_Prescaler-1;
	
	
	
	/* Set the Autoreload value */
  TIMx->ARR = TIMx_Period-1;
	
	/*   */
//  TIMx->CNT = 0;										//清除计数

	/* Set or reset the UG Bit */
  TIMx->EGR = ((u16)0x0001);								//立即生效分频Prescaler
	
//	TIMx->CR1 |= ((u16)0x0001);							//CR1_CEN_Set开启定时器
}


/*******************************************************************************
*函数名		: TIM_Configuration
*功能描述	:定时时间设定
*输入			:TIMx--TIMx--定时器号
						x可以为1,2,3,4,5,6,7或者8
						Prescaler---分频系数,(取值0x0000~0xFFFF)用来分频TIM clock
						Period	---计数值,(取值0x0000~0xFFFF),计数TIM_Period+1个节拍后产生溢?
						TIM_ClockDivision----设定时间分割值,(默认为0,特殊场合时TIM_ClockDivision用来做一段延时)
						TIM_CounterMode---计数方式
						TIM_RepetitionCounter---重复计数次数,(重复多少次溢出后才触发一次溢出中断)
*输出			:	无
*返回值		:	无
*例程			:
*******************************************************************************/
void TIM_Configuration(TIM_TypeDef* TIMx,u16 Prescaler,u16 Period)	//定时时间设定
{
	TIM_TimeBaseInitTypeDef	TIM_TimeBaseStructure;	//定时器结构体定义
	NVIC_InitTypeDef	NVIC_InitStructure;						//中断结构体
	u8 TIM_IRQChannel=0;
	//1)**********定义相关变量	
	switch (*(u32*)&TIMx)
	{
		case TIM1_BASE:
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
			TIM_IRQChannel=TIM1_UP_IRQChannel;
			break;
		
		case TIM2_BASE:
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
			TIM_IRQChannel=TIM2_IRQChannel;
			break;
		
		case TIM3_BASE:
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
			TIM_IRQChannel=TIM3_IRQChannel;
			break;
		
		case TIM4_BASE:
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
			TIM_IRQChannel=TIM4_IRQChannel;
			break;
		
		case TIM5_BASE:
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
			TIM_IRQChannel=TIM5_IRQChannel;
			break;
		
		case TIM6_BASE:
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);
			TIM_IRQChannel=TIM6_IRQChannel;
			break;
		
		case TIM7_BASE:
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);
			TIM_IRQChannel=TIM7_IRQChannel;
			break;
		
		case TIM8_BASE:
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);
			TIM_IRQChannel=TIM8_UP_IRQChannel;
			break;
		
		default:
			break;
		
	}
	
	TIMx_RCC_ENABLE(TIMx);													//打开相应定时器时钟
	//1)**********定义相关变量	
	TIM_TimeBaseStructure.TIM_Prescaler = Prescaler-1; 		// 设定分频值
	TIM_TimeBaseStructure.TIM_Period = Period-1;        	//设定自动重装载值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;  //不分割
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //向上计数
	//	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	//????,???????????????????-??????????
	TIM_TimeBaseInit(TIMx, &TIM_TimeBaseStructure);		//初始化
	//1)**********定义相关变量	
	TIM_ARRPreloadConfig(TIMx, ENABLE);
	TIM_Cmd(TIMx, ENABLE); 
	
	//1)**********定义相关变量	
	NVIC_InitStructure.NVIC_IRQChannel = TIM_IRQChannel;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	/* Clear TIMx update pending flag[清除TIMx溢出中断] */
	TIM_ClearFlag(TIMx, TIM_FLAG_Update);

	/* Enable TIM2 Update interrupt [TIMx溢出中断允许]*/
	TIM_ITConfig(TIMx, TIM_IT_Update, ENABLE); 

	/* TIM2 enable counter [使能TIMx计数]*/
	TIM_Cmd(TIMx, ENABLE);	//使能TIMx计数
}
/*******************************************************************************
*函数名		:TIMx_RCC_ENABLE
*功能描述	:打开相应定时器时钟
*输入			:TIMx--定时器号
						x可以为1,2,3,4,5,6,7或者8
*输出			:无
*返回值		:无
*例程			:TIMx_RCC_ENABLE(TIM1);
*******************************************************************************/
void TIMx_RCC_ENABLE(TIM_TypeDef* TIMx)	//打开相应定时器时钟
{
	assert_param(IS_TIM_ALL_PERIPH(TIMx)); 
	switch (*(u32*)&TIMx)
	{
		case TIM1_BASE:
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
			break;
		
		case TIM2_BASE:
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
			break;
		
		case TIM3_BASE:
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
			break;
		
		case TIM4_BASE:
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
			break;
		
		case TIM5_BASE:
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
			break;
		
		case TIM6_BASE:
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);
			break;
		
		case TIM7_BASE:
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);
			break;
		
		case TIM8_BASE:
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);
			break;
		
		default:
break;
		
	}
}
/*******************************************************************************
*函数名		: TIM_TIME_SET
*功能描述	:定时时间设定
*输入			:TIMx--TIMx--定时器号
					 x可以为1,2,3,4,5,6,7或者8
					Prescaler---分频系数,(取值0x0000~0xFFFF)用来分频TIM clock
					 Period	---计数值,(取值0x0000~0xFFFF),计数TIM_Period+1个节拍后产生溢出
					TIM_ClockDivision----设定时间分割值,(默认为0,特殊场合时TIM_ClockDivision用来做一段延时)
					TIM_CounterMode---计数方式
					TIM_RepetitionCounter---重复计数次数,(重复多少次溢出后才触发一次溢出中断)
*输出			:无
*返回值		:无
*例程			:
*******************************************************************************/
void TIM_TIME_SET(TIM_TypeDef* TIMx,u16 Prescaler,u16 Period)	//定时时间设定
{
	TIM_TimeBaseInitTypeDef	TIM_TimeBaseStructure;	//定时器结构体定义

	TIM_TimeBaseStructure.TIM_Prescaler = Prescaler-1; 		// 设定分频值
	TIM_TimeBaseStructure.TIM_Period = Period-1;        	//设定自动重装载值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;  //不分割
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //向上计数
	//	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	//????,???????????????????-??????????
	TIM_TimeBaseInit(TIMx, &TIM_TimeBaseStructure);		//初始化
//	TIM_PrescalerConfig(TIM2,Prescaler,TIM_PSCReloadMode_Update);
	TIM_ARRPreloadConfig(TIMx, ENABLE);
//	TIM_Cmd(TIM2, ENABLE);
//	TIM_SetCompare1(TIM2,4000);
}
/*******************************************************************************
*函数名		:TIM_Interrupt
*功能描述	:ADS1230管脚初始化
*输入			:无
*输出			:无
*返回值		:无
*例程			：
*******************************************************************************/
void TIM_Interrupt(TIM_TypeDef* TIMx,u16 Prescaler,u16 Period)
{
	NVIC_InitTypeDef	NVIC_InitStructure;
	u8 TIM_IRQChannel=0;
	assert_param(IS_TIM_ALL_PERIPH(TIMx)); 
	
	TIM_Configuration(TIMx,Prescaler,Period);
	
	switch (*(u32*)&TIMx)
	{
		case TIM1_BASE:
			TIM_IRQChannel=TIM1_UP_IRQChannel;
			break;
		
		case TIM2_BASE:
			TIM_IRQChannel=TIM2_IRQChannel;
			break;
		
		case TIM3_BASE:
			TIM_IRQChannel=TIM3_IRQChannel;
			break;
		
		case TIM4_BASE:
			TIM_IRQChannel=TIM4_IRQChannel;
			break;
		
		case TIM5_BASE:
			TIM_IRQChannel=TIM5_IRQChannel;
			break;
		
		case TIM6_BASE:
			TIM_IRQChannel=TIM6_IRQChannel;
			break;
		
		case TIM7_BASE:
			TIM_IRQChannel=TIM7_IRQChannel;
			break;
		
		case TIM8_BASE:
			TIM_IRQChannel=TIM8_UP_IRQChannel;
			break;
		
		default:
			break;
		
	}
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM_IRQChannel;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	/* Clear TIMx update pending flag[清除TIMx溢出中断] */
	TIM_ClearFlag(TIMx, TIM_FLAG_Update);

	/* Enable TIM2 Update interrupt [TIMx溢出中断允许]*/
	TIM_ITConfig(TIMx, TIM_IT_Update, ENABLE); 

	/* TIM2 enable counter [使能TIMx计数]*/
	TIM_Cmd(TIMx, ENABLE);	//使能TIMx计数
		
}
/*******************************************************************************
*函数名		:TIM_Server
*功能描述	:ADS1230管脚初始化
*输入			:无
*输出			:无
*返回值		:无
*例程			：
*******************************************************************************/
void TIM_Server(void)
{
	WOW_Server();															//服务函数
//	TIM_ClearFlag(TIM1, TIM_FLAG_Update);
//	TIM_ClearFlag(TIM2, TIM_FLAG_Update);
//	TIM_ClearFlag(TIM3, TIM_FLAG_Update);
//	TIM_ClearFlag(TIM4, TIM_FLAG_Update);
//	TIM_ClearFlag(TIM5, TIM_FLAG_Update);
//	TIM_ClearFlag(TIM6, TIM_FLAG_Update);
//	TIM_ClearFlag(TIM7, TIM_FLAG_Update);
//	TIM_ClearFlag(TIM8, TIM_FLAG_Update);
	
//	TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
//	TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
//	TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
//	TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
//	TIM_ClearITPendingBit(TIM5, TIM_IT_Update);
//	TIM_ClearITPendingBit(TIM6, TIM_IT_Update);
//	TIM_ClearITPendingBit(TIM7, TIM_IT_Update);
//	TIM_ClearITPendingBit(TIM8, TIM_IT_Update);
}






