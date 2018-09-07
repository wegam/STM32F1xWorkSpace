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


#ifndef __STM32_PWM_H
#define __STM32_PWM_H



#include "stm32f10x_tim.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_nvic.h"

//#include "STM32_TIM.H"


typedef enum
{
  PWM_OUTChannel1	=	0,
	PWM_OUTChannel2,
	PWM_OUTChannel3,
	PWM_OUTChannel4,
} PWM_OUTChannelTypeDef;
typedef struct
{
	TIM_TypeDef*	TIMx;
	GPIO_TypeDef*	GPIOx;			//x=A/B/C/D/E/F/G
	u16 GPIO_Pin_n;						//n=0~15;
	
	double PWM_Frequency;			//频率 最小频率0.2Hz
	u16 	PWM_Updata;					//频率变化占计数个数，就是计数PWM_Updata个数后更新一次输出频率
	u32 	PWM_RunUp;					//加速/减速需要的步数
	u32 	PWM_Count;					//输出脉冲数，每计一周期脉冲数增加一个，计数达到PWM_Num停止输出，需要再次输出时则清0此计数，重新开始计数	
}PWM_BasicDataDef;
typedef struct
{
	u16 	PWM_Cycle ;						//计数值，到达PWM_Updata后更新频率
	u32 	PWM_Pulse;						//计数值，计数到达PWM_Count后停止输出	
}PWM_RunDataDef;
typedef struct
{
//	PWM_BasicDataDef	PWM_BasicData;		//配置数据，需要输入全部参数
	struct
	{
		TIM_TypeDef*	TIMx;
		GPIO_TypeDef*	GPIOx;			//x=A/B/C/D/E/F/G
		u16 GPIO_Pin_n;						//n=0~15;
		
		double PWM_Frequency;			//频率 最小频率0.2Hz
		u16 	PWM_Updata;					//频率变化占计数个数，就是计数PWM_Updata个数后更新一次输出频率
		u32 	PWM_RunUp;					//加速/减速需要的步数
		u32 	PWM_Count;					//输出脉冲数，每计一周期脉冲数增加一个，计数达到PWM_Num停止输出，需要再次输出时则清0此计数，重新开始计数	
	}PWM_BasicData;		//配置数据，需要输入全部参数
//	PWM_RunDataDef		PWM_RunData;			//运行参数，不需要输入任何参数
	struct
	{
		u16 	PWM_Cycle ;					//计数值，到达PWM_Updata后更新频率
		u32 	PWM_Pulse;					//计数值，计数到达PWM_Count后停止输出	
	}PWM_RunData;			//运行参数，不需要输入任何参数
}PWM_TimDef;
extern u32 Tim1_Count;
extern u32 Tim2_Count;
extern u32 Tim3_Count;
extern u32 Tim4_Count;

//----------------------------------固定输出1/1000占空比
void PWM_OUT(TIM_TypeDef* TIMx,PWM_OUTChannelTypeDef PWM_OUTChanneln,double PWM_Frequency ,u16 PWM_Ratio);	//PWM设定-20161127版本	占空比1/1000
void PWM_OUTRemap(TIM_TypeDef* TIMx,PWM_OUTChannelTypeDef PWM_OUTChanneln,double PWM_Frequency ,u16 PWM_Ratio);	//PWM设定-20161127版本	占空比1/1000
//----------------------------------固定输出1/1200占空比
void PWM_OUT2(TIM_TypeDef* TIMx,PWM_OUTChannelTypeDef PWM_OUTChanneln,double PWM_Frequency ,u16 PWM_Ratio);	//PWM设定-20161127版本	占空比1/1200
void SetPWM_Ratio(u16 PWM_Ratio);		//设置占空比---LED




//----------------------------------普通GPIO固定脉冲个数输出，占空比固定50%
void PWM_OUT_TIMConf(PWM_TimDef* PWM_Tim);									//PWM输出配置---最大100KHz
void PWM_OUT_SetFre(PWM_TimDef* PWM_Tim,double PWM_Frequency);	//设置频率
void PWM_OUT_SetCount(PWM_TimDef* PWM_Tim,u32 PWM_Count);			//设置输出个数
u8 PWM_OUT_TIMServer(PWM_TimDef* PWM_Tim);									//PWM输出配置



#endif
