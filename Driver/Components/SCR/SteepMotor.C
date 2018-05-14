/*********************************************
*步进电机驱动
*结构体参数配置形式
*驱动模式---计时
*特殊功能:超时,加速
*最高优先级:停止--任何情况下,有停止命令,优先执行停止
*其它:刹车
**********************************************/

#include "SteepMotor.H"

#include "STM32_GPIO.H"

#include "STM32_TIM.H"


//-----------------------------步进电机
/*******************************************************************************
*函数名			:	function
*功能描述		:	function
*输入				: 
*返回值			:	无
*修改时间		:	2018/01/02
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
void StepMotorConfiguration(SteepMotorDef *STEP_MOTOx)
{
	//==================配置脉冲输出管脚
	GPIO_Configuration_OPP50	(STEP_MOTOx->SetPulsPort,	STEP_MOTOx->SetPulsPin);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605
	//==================配置方向输出管脚
	GPIO_Configuration_OPP50	(STEP_MOTOx->SetDIRPort,	STEP_MOTOx->SetDIRPin);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605
	//==================配置定时器
	TIM_ConfigurationFreq(STEP_MOTOx->SetTIMx,STEP_MOTOx->SetFrequency);					//定时器频率配置方式，最小频率1Hz,最大100KHz
}
/*******************************************************************************
*函数名			:	function
*功能描述		:	function
*输入				: 
*返回值			:	无
*修改时间		:	2018/01/02
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
unsigned char StepMotorServer(SteepMotorDef *STEP_MOTOx)
{
	if((STEP_MOTOx->SetTIMx->SR & TIM_IT_Update)==TIM_IT_Update)			//表示定时中断---运行计数未完
	{
		if(STEP_MOTOx->GetPulsTotal>=STEP_MOTOx->SetPulsTotal)
		{
			STEP_MOTOx->SetTIMx->CR1 &= ((u16)0x03FE);		//CR1_CEN_Reset关闭定时器
//			TIM_Cmd(STEP_MOTOx->SetTIMx, DISABLE);
			STEP_MOTOx->SetPulsPort->BRR	=	STEP_MOTOx->SetPulsPin;		//输出低电平
			return 1;
		}
		else if(STEP_MOTOx->PulsFlag	!=	0)
		{
			STEP_MOTOx->PulsFlag	=	0;				//原状态为高电平
			STEP_MOTOx->SetPulsPort->BRR	=	STEP_MOTOx->SetPulsPin;
			STEP_MOTOx->GetPulsTotal++;				//输出脉冲计数
		}
		else if(STEP_MOTOx->PulsFlag	!=	1)
		{
			STEP_MOTOx->PulsFlag	=	1;				//原状态为低电平
			STEP_MOTOx->SetPulsPort->BSRR	=	STEP_MOTOx->SetPulsPin;			
		}
		
		//==============加减速处理
		if(STEP_MOTOx->SetPlusUp	&&	STEP_MOTOx->SetPlusUpNum	&&	(STEP_MOTOx->GetPulsTotal<STEP_MOTOx->SetPlusUpNum)	&&(STEP_MOTOx->PulsFlag	!=0))
		{
			STEP_MOTOx->SetFrequency+=STEP_MOTOx->SetPlusUp;
			TIM_SetFreq(STEP_MOTOx->SetTIMx,STEP_MOTOx->SetFrequency);		//设定频率
		}
		else if(STEP_MOTOx->SetPlusDown	&&	STEP_MOTOx->SetPlusDownNum	&&	((STEP_MOTOx->GetPulsTotal+STEP_MOTOx->SetPlusDownNum)>STEP_MOTOx->SetPulsTotal)	&&	(STEP_MOTOx->PulsFlag	!=0))
		{
			STEP_MOTOx->SetFrequency-=STEP_MOTOx->SetPlusDown;
			TIM_SetFreq(STEP_MOTOx->SetTIMx,STEP_MOTOx->SetFrequency);		//设定频率
		}
		STEP_MOTOx->SetTIMx->SR = (u16)~TIM_IT_Update;			//清除中断标志
		return 1;
	}
	return 0;
}
/*******************************************************************************
*函数名			:	function
*功能描述		:	function
*输入				: 
*返回值			:	无
*修改时间		:	2018/01/02
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
void StepMotorCW(SteepMotorDef *STEP_MOTOx,u16	SetFrequency,u16 SetPlusUp,u16 SetPlusUpNum,u16	SetPlusDown,u16	SetPlusDownNum,u32 SetPulsTotal)		//顺时针旋转
{
	if(SetFrequency==0	||	SetPulsTotal==0)
	{
		(STEP_MOTOx->SetPulsPort)->BRR	=	STEP_MOTOx->SetPulsPin;
		return;
	}
	else
	{
		(STEP_MOTOx->SetPulsPort)->BRR	=	STEP_MOTOx->SetDIRPin;		//低电平：顺时针转
		(STEP_MOTOx->SetPulsPort)->BRR	=	STEP_MOTOx->SetPulsPin;		//输出低电平
		
		STEP_MOTOx->SetFrequency		=	SetFrequency;							//起始输出频率
		STEP_MOTOx->SetPlusUp				=	SetPlusUp;								//加速频率间隔
		STEP_MOTOx->SetPlusUpNum		=	SetPlusUpNum;							//加速脉冲个数
		
		STEP_MOTOx->SetPlusDown			=	SetPlusDown;							//减速频率间隔
		STEP_MOTOx->SetPlusDownNum	=	SetPlusDownNum;						//减速脉冲个数
		
		STEP_MOTOx->SetPulsTotal		=	SetPulsTotal;							//需要输出脉冲总数
		
		
		STEP_MOTOx->RunFlag					=	0;												//0:未运行，1-定时器开启
		STEP_MOTOx->PulsFlag				=	0;												//一个脉冲上升沿和下降需要两个定时器中断
		
		STEP_MOTOx->GetFrequency		=	SetFrequency;							//频率 最小频率1Hz
		STEP_MOTOx->GetPlusUpNum		=	0;												//加速脉冲个数
		STEP_MOTOx->GetPulsTotal		=	0;												//已经输出脉冲计数

		TIM_SetFreq(STEP_MOTOx->SetTIMx,STEP_MOTOx->SetFrequency);		//设定频率
		
		STEP_MOTOx->SetTIMx->CR1 |= ((u16)0x0001);							//CR1_CEN_Set开启定时器

//		TIM_Cmd(STEP_MOTOx->SetTIMx, ENABLE);		
	}
}
/*******************************************************************************
*函数名			:	function
*功能描述		:	function
*输入				: 
*返回值			:	无
*修改时间		:	2018/01/02
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
void StepMotorCCW(SteepMotorDef *STEP_MOTOx,u16	SetFrequency,u16 SetPlusUp,u16 SetPlusUpNum,u16	SetPlusDown,u16	SetPlusDownNum,u32 SetPulsTotal)		//逆时针旋转
{
	if(SetFrequency==0	||	SetPulsTotal==0)
	{
		STEP_MOTOx->SetPulsPort->BRR	=	STEP_MOTOx->SetPulsPin;
		return;
	}
	else
	{
		STEP_MOTOx->SetDIRPort->BSRR	=	STEP_MOTOx->SetDIRPin;	//高电平：逆时针转
		STEP_MOTOx->SetPulsPort->BRR	=	STEP_MOTOx->SetPulsPin;		//输出低电平
		
		STEP_MOTOx->SetFrequency		=	SetFrequency;							//起始输出频率
		STEP_MOTOx->SetPlusUp				=	SetPlusUp;								//加速频率间隔
		STEP_MOTOx->SetPlusUpNum		=	SetPlusUpNum;							//加速脉冲个数
		
		STEP_MOTOx->SetPlusDown			=	SetPlusDown;							//减速频率间隔
		STEP_MOTOx->SetPlusDownNum	=	SetPlusDownNum;						//减速脉冲个数
		
		STEP_MOTOx->SetPulsTotal		=	SetPulsTotal;							//需要输出脉冲总数
		
		STEP_MOTOx->RunFlag					=	0;												//0:未运行，1-定时器开启
		STEP_MOTOx->PulsFlag				=	0;												//一个脉冲上升沿和下降需要两个定时器中断
		
		STEP_MOTOx->GetFrequency		=	SetFrequency;							//频率 最小频率1Hz
		STEP_MOTOx->GetPlusUpNum		=	0;												//加速脉冲个数
		STEP_MOTOx->GetPulsTotal		=	0;												//已经输出脉冲计数
		
		TIM_SetFreq(STEP_MOTOx->SetTIMx,STEP_MOTOx->SetFrequency);		//设定频率
		
		STEP_MOTOx->SetTIMx->CR1 |= ((u16)0x0001);							//CR1_CEN_Set开启定时器
//		TIM_Cmd(STEP_MOTOx->SetTIMx, ENABLE);		
	}
}
/*******************************************************************************
*函数名			:	function
*功能描述		:	function
*输入				: 
*返回值			:	无
*修改时间		:	2018/01/02
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
void StepMotorStop(SteepMotorDef *STEP_MOTOx)
{
	STEP_MOTOx->SetTIMx->CR1 &= ((u16)0x03FE);		//CR1_CEN_Reset关闭定时器
	STEP_MOTOx->SetPulsPort->BRR	=	STEP_MOTOx->SetPulsPin;		//输出低电平
	
	STEP_MOTOx->SetFrequency		=	0;						//起始输出频率
	STEP_MOTOx->SetPlusUp				=	0;						//加速频率间隔
	STEP_MOTOx->SetPlusUpNum		=	0;						//加速脉冲个数
	
	STEP_MOTOx->SetPlusDown			=	0;						//减速频率间隔
	STEP_MOTOx->SetPlusDownNum	=	0;						//减速脉冲个数
	
	STEP_MOTOx->SetPulsTotal		=	0;						//需要输出脉冲总数
	
	STEP_MOTOx->RunFlag					=	0;						//0:未运行，1-定时器开启
	STEP_MOTOx->PulsFlag				=	0;						//一个脉冲上升沿和下降需要两个定时器中断
	
	STEP_MOTOx->GetFrequency		=	0;						//频率 最小频率1Hz
	STEP_MOTOx->GetPlusUpNum		=	0;						//加速脉冲个数
	STEP_MOTOx->GetPulsTotal		=	0;						//已经输出脉冲计数
}
/*******************************************************************************
*函数名			:	function
*功能描述		:	function
*输入				: 
*返回值			:	无
*修改时间		:	2018/01/02
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
void StepMotorPause(SteepMotorDef *STEP_MOTOx)
{

}



