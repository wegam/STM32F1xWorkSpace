/******************************** User_library *********************************
* �ļ��� 	: STM32_SDCard.H
* ����   	: wegam@sina.com
* �汾   	: V
* ����   	: 2016/01/01
* ˵��   	: 
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
	
	double PWM_Frequency;			//Ƶ�� ��СƵ��0.2Hz
	u16 	PWM_Updata;					//Ƶ�ʱ仯ռ�������������Ǽ���PWM_Updata���������һ�����Ƶ��
	u32 	PWM_RunUp;					//����/������Ҫ�Ĳ���
	u32 	PWM_Count;					//�����������ÿ��һ��������������һ���������ﵽPWM_Numֹͣ�������Ҫ�ٴ����ʱ����0�˼��������¿�ʼ����	
}PWM_BasicDataDef;
typedef struct
{
	u16 	PWM_Cycle ;						//����ֵ������PWM_Updata�����Ƶ��
	u32 	PWM_Pulse;						//����ֵ����������PWM_Count��ֹͣ���	
}PWM_RunDataDef;
typedef struct
{
//	PWM_BasicDataDef	PWM_BasicData;		//�������ݣ���Ҫ����ȫ������
	struct
	{
		TIM_TypeDef*	TIMx;
		GPIO_TypeDef*	GPIOx;			//x=A/B/C/D/E/F/G
		u16 GPIO_Pin_n;						//n=0~15;
		
		double PWM_Frequency;			//Ƶ�� ��СƵ��0.2Hz
		u16 	PWM_Updata;					//Ƶ�ʱ仯ռ�������������Ǽ���PWM_Updata���������һ�����Ƶ��
		u32 	PWM_RunUp;					//����/������Ҫ�Ĳ���
		u32 	PWM_Count;					//�����������ÿ��һ��������������һ���������ﵽPWM_Numֹͣ�������Ҫ�ٴ����ʱ����0�˼��������¿�ʼ����	
	}PWM_BasicData;		//�������ݣ���Ҫ����ȫ������
//	PWM_RunDataDef		PWM_RunData;			//���в���������Ҫ�����κβ���
	struct
	{
		u16 	PWM_Cycle ;					//����ֵ������PWM_Updata�����Ƶ��
		u32 	PWM_Pulse;					//����ֵ����������PWM_Count��ֹͣ���	
	}PWM_RunData;			//���в���������Ҫ�����κβ���
}PWM_TimDef;
extern u32 Tim1_Count;
extern u32 Tim2_Count;
extern u32 Tim3_Count;
extern u32 Tim4_Count;

//----------------------------------�̶����1/1000ռ�ձ�
void PWM_OUT(TIM_TypeDef* TIMx,PWM_OUTChannelTypeDef PWM_OUTChanneln,double PWM_Frequency ,u16 PWM_Ratio);	//PWM�趨-20161127�汾	ռ�ձ�1/1000

//----------------------------------�̶����1/1200ռ�ձ�
void PWM_OUT2(TIM_TypeDef* TIMx,PWM_OUTChannelTypeDef PWM_OUTChanneln,double PWM_Frequency ,u16 PWM_Ratio);	//PWM�趨-20161127�汾	ռ�ձ�1/1200
void SetPWM_Ratio(u16 PWM_Ratio);		//����ռ�ձ�---LED




//----------------------------------��ͨGPIO�̶�������������ռ�ձȹ̶�50%
void PWM_OUT_TIMConf(PWM_TimDef* PWM_Tim);									//PWM�������---���100KHz
void PWM_OUT_SetFre(PWM_TimDef* PWM_Tim,double PWM_Frequency);	//����Ƶ��
void PWM_OUT_SetCount(PWM_TimDef* PWM_Tim,u32 PWM_Count);			//�����������
u8 PWM_OUT_TIMServer(PWM_TimDef* PWM_Tim);									//PWM�������



#endif