
#ifndef __SteepMotor_H
#define __SteepMotor_H

#include "stm32f10x_gpio.h"
#include "stm32f10x_type.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_nvic.h"

typedef struct
{
	//====================配置参数：使用时需要配置
	TIM_TypeDef*	SetTIMx;				//使用到的定时器
	//--------------------脉冲输出
	GPIO_TypeDef*	SetPulsPort;		//GPIOx:x=A/B/C/D/E/F/G
	u16 SetPulsPin;									//GPIO_Pin_n:n=0~15;
	//--------------------方向输出
	GPIO_TypeDef*	SetDIRPort;			//GPIOx:x=A/B/C/D/E/F/G
	u16 SetDIRPin;								//GPIO_Pin_n:n=0~15;
	//--------------------输出频率
	u16	SetFrequency;				//频率 最小频率1Hz
	u16	SetPlusUp;					//加速频率间隔	
	u16	SetPlusUpNum;				//加速脉冲个数
	
	u16	SetPlusDown;				//减速频率间隔
	u16	SetPlusDownNum;			//减速脉冲个数
	u32	SetPulsTotal;				//需要输出脉冲总数
	//====================运行标志：
	u8	RunFlag;						//0:未运行，1-定时器开启
	u8	PulsFlag;						//一个脉冲上升沿和下降需要两个定时器中断
	//====================运行参数：运行变量
	u16	GetFrequency;				//频率 最小频率1Hz
	u16	GetPlusUpNum;				//加速脉冲个数
	u32	GetPulsTotal;				//已经输出脉冲计数
}SteepMotorDef;



void StepMotorConfiguration(SteepMotorDef *STEP_MOTOx);		//
unsigned char StepMotorServer(SteepMotorDef *STEP_MOTOx);	//


void StepMotorCW(SteepMotorDef *STEP_MOTOx,u16	SetFrequency,u16 SetPlusUp,u16 SetPlusUpNum,u16	SetPlusDown,u16	SetPlusDownNum,u32 SetPulsTotal);		//顺时针旋转
void StepMotorCCW(SteepMotorDef *STEP_MOTOx,u16	SetFrequency,u16 SetPlusUp,u16 SetPlusUpNum,u16	SetPlusDown,u16	SetPlusDownNum,u32 SetPulsTotal);		//逆时针旋转
void StepMotorStop(SteepMotorDef *STEP_MOTOx);



#endif


