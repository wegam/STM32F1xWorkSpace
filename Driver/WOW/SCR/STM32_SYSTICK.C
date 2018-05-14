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



#include "STM32_WOW.H"
#include "STM32_SYSTICK.H"

#include "stm32f10x_rcc.h"
//#include "STM32F10x_BitBand.H"

#include <stdint.h>

RCC_ClocksTypeDef RCC_ClocksStatus;							//时钟状态---时钟值
unsigned int Load	=	0;		//保存原重装载值
unsigned int Ctrl	=	0;		//保存原控制参数
/*******************************************************************************
* 函数名		:	SysTick_Configuration
* 功能描述	:	系统嘀嗒时钟配置72MHz,单位为uS
* 输入		:	0<Time<= 1C71C7(1864135)
* 输出		:
* 返回 		:
*******************************************************************************/
void SysTick_Configuration(unsigned long Time)	//系统嘀嗒时钟配置72MHz,单位为uS
{	
	
	if(Time	==	0)
		return;
	RCC_GetClocksFreq(&RCC_ClocksStatus);	//获取时钟参数
	
	SysTick->CTRL &= 0xFFFFFFFD;									//SysTick_ITConfig(DISABLE);					//关闭中断
	SysTick->CTRL &= SysTick_Counter_Disable;			//SysTick_CounterCmd(SysTick_Counter_Disable);	//关闭计数
	SysTick->CTRL &= SysTick_CLKSource_HCLK_Div8;	//SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);			//系统时钟/8==9MHz
	SysTick->LOAD = ((RCC_ClocksStatus.SYSCLK_Frequency)/8000000)*Time;	//SysTick_SetReload(9*time);				//Time--uS  -8为了减小误差，不可以-9，防止Time==1的情况
	SysTick->CTRL |= ((u32)0x00000002);
	SysTick->CTRL |= SysTick_Counter_Enable;			//SysTick_CounterCmd(SysTick_Counter_Enable);	//使能计数
	SysTick->VAL = SysTick_Counter_Clear;					//SysTick_CounterCmd(SysTick_Counter_Clear);	//清除倒计数值
	
	SysTick->CTRL |= ((u32)0x00000002);	//开中断
	
	Load	=	SysTick->LOAD;							//获取原重装载值
	Ctrl	=	SysTick->CTRL&0x0000FFFF;		//获取原控制参数
	
////	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);					//系统时钟 72MHZ
//	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);			//系统时钟/8==9MHz
////	SysTick_SetReload(9);			//1uS
//	SysTick_SetReload((RCC_ClocksStatus.SYSCLK_Frequency/8000000)*Time);				//Time--uS
//	SysTick_ITConfig(DISABLE);					//关闭中断
//	SysTick_CounterCmd(SysTick_Counter_Enable);	//使能计数
//	SysTick_ITConfig(ENABLE);
//	
//	Load	=	SysTick->LOAD;							//获取原重装载值
//	Ctrl	=	SysTick->CTRL&0x0000FFFF;		//获取原控制参数
	
//	if(Time	==	0)
//		return;
////	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);					//系统时钟 72MHZ
//	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);			//系统时钟/8==9MHz
////	SysTick_SetReload(9);			//1uS
//	SysTick_SetReload(9*Time-1);				//Time--uS
//	SysTick_ITConfig(DISABLE);					//关闭中断
//	SysTick_CounterCmd(SysTick_Counter_Enable);	//使能计数
//	SysTick_ITConfig(ENABLE);
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
void SysTick_Server(void)				//嘀嗒时钟服务
{
	WOW_Server();	
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
void SysTick_DeleyuS(unsigned int Time)
{
	
	vu32 LOADTemp	=	0;			//SysTick重装载值寄存器--最大计数0xFFFFFF：Systick是一个递减的定时器，当定时器递减至0时，重载寄存器中的值就会被重装载，继续开始递减。
	
	if(Time	==	0)
		return;
	
	RCC_GetClocksFreq(&RCC_ClocksStatus);	//获取时钟参数
	
	SysTick->CTRL &= 0xFFFFFFFD;									//SysTick_ITConfig(DISABLE);					//关闭中断
	SysTick->CTRL &= SysTick_Counter_Disable;			//SysTick_CounterCmd(SysTick_Counter_Disable);	//关闭计数
//	SysTick->VAL = SysTick_Counter_Clear;					//SysTick_CounterCmd(SysTick_Counter_Clear);	//清除倒计数值
	SysTick->CTRL &= SysTick_CLKSource_HCLK_Div8;	//SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);			//系统时钟/8==9MHz
	SysTick->LOAD = (RCC_ClocksStatus.SYSCLK_Frequency/8000000)*Time;	//SysTick_SetReload(9*time);				//Time--uS  -8为了减小误差，不可以-9，防止Time==1的情况
	SysTick->CTRL |= SysTick_Counter_Enable;			//SysTick_CounterCmd(SysTick_Counter_Enable);	//使能计数
	SysTick->VAL = SysTick_Counter_Clear;					//SysTick_CounterCmd(SysTick_Counter_Clear);	//清除倒计数值
	
	while(SysTick->VAL	==	0);			//等待开始装载
	while(SysTick->VAL	!=	0);			//等待倒计数完成

	
	
	SysTick->LOAD	=	Load;			//恢复原控制参数
	SysTick->VAL = SysTick_Counter_Clear;					//SysTick_CounterCmd(SysTick_Counter_Clear);	//清除倒计数值
	SysTick->CTRL	=	Ctrl;			//恢复原控制参数
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
void SysTick_DeleymS(unsigned int Time)
{

	if(Time	==	0)
		return;
	
	RCC_GetClocksFreq(&RCC_ClocksStatus);	//获取时钟参数
	
	SysTick->CTRL &= 0xFFFFFFFD;									//SysTick_ITConfig(DISABLE);					//关闭中断
	SysTick->CTRL &= SysTick_Counter_Disable;			//SysTick_CounterCmd(SysTick_Counter_Disable);	//关闭计数
//	SysTick->VAL = SysTick_Counter_Clear;					//SysTick_CounterCmd(SysTick_Counter_Clear);	//清除倒计数值
	SysTick->CTRL &= SysTick_CLKSource_HCLK_Div8;	//SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);			//系统时钟/8==9MHz
	SysTick->LOAD = (((RCC_ClocksStatus.SYSCLK_Frequency)/8000));	//SysTick_SetReload(9*time);				//Time--mS  -8为了减小误差，不可以-9，防止Time==1的情况	
	SysTick->CTRL |= SysTick_Counter_Enable;			//SysTick_CounterCmd(SysTick_Counter_Enable);	//使能计数
	SysTick->VAL = SysTick_Counter_Clear;					//SysTick_CounterCmd(SysTick_Counter_Clear);	//清除倒计数值	
	while(Time)
	{
		while(SysTick->VAL	==	0);			//等待开始装载
		while(SysTick->VAL	!=	0);			//等待倒计数完成
		Time--;
	}	
	
	SysTick->LOAD	=	Load;			//恢复原控制参数
	SysTick->VAL = SysTick_Counter_Clear;					//SysTick_CounterCmd(SysTick_Counter_Clear);	//清除倒计数值
	SysTick->CTRL	=	Ctrl;			//恢复原控制参数
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
void SysTick_DeleyS(unsigned int Time)
{

	if(Time	==	0)
		return;
//	SysTick_DeleymS(Time*1000);
//	RCC_GetClocksFreq(&RCC_ClocksStatus);	//获取时钟参数
//	
	SysTick->CTRL &= 0xFFFFFFFD;									//SysTick_ITConfig(DISABLE);					//关闭中断
	SysTick->CTRL &= SysTick_Counter_Disable;			//SysTick_CounterCmd(SysTick_Counter_Disable);	//关闭计数
//	SysTick->VAL = SysTick_Counter_Clear;					//SysTick_CounterCmd(SysTick_Counter_Clear);	//清除倒计数值
	SysTick->CTRL &= SysTick_CLKSource_HCLK_Div8;	//SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);			//系统时钟/8==9MHz
//	SysTick->LOAD = (((RCC_ClocksStatus.SYSCLK_Frequency)/8));	//SysTick_SetReload(8M);				//Time--mS  -8为了减小误差，不可以-9，防止Time==1的情况
	SysTick->LOAD = 9000000;	//SysTick_SetReload(8M);				//Time--mS  -8为了减小误差，不可以-9，防止Time==1的情况	
	SysTick->CTRL |= SysTick_Counter_Enable;			//SysTick_CounterCmd(SysTick_Counter_Enable);	//使能计数
	SysTick->VAL = SysTick_Counter_Clear;					//SysTick_CounterCmd(SysTick_Counter_Clear);	//清除倒计数值
	while(Time)
	{
		while(SysTick->VAL	==	0);			//等待开始装载
		while(SysTick->VAL	!=	0);			//等待倒计数完成
		Time--;
	}
	
	SysTick->LOAD	=	Load;			//恢复原控制参数
	SysTick->VAL = SysTick_Counter_Clear;					//SysTick_CounterCmd(SysTick_Counter_Clear);	//清除倒计数值
	SysTick->CTRL	=	Ctrl;			//恢复原控制参数
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
void DeleyuS(unsigned int Time)
{
	Time	=	Time*4;
	while(Time--)
	{
		__nop();
		__nop();
		__nop();
		__nop();
		__nop();
		__nop();
		__nop();
		__nop();
		__nop();
//		__nop();
		
	}
}


