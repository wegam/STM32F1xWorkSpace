#ifdef CAN_TEST


#include "CAN_TEST.H"

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
u8 CANdata[8]={0};
/*******************************************************************************
* 函数名		:	
* 功能描述	:	 
* 输入		:	
* 输出		:
* 返回 		:
*******************************************************************************/
void CAN_TEST_Configuration(void)
{
	SYS_Configuration();						//系统配置 STM32_SYS.H	
	CAN_Configuration_NR(100000);			//CAN1配置---标志位查询方式，不开中断--速率500K
	CAN_FilterInitConfiguration_StdData(0x05,0x08,0x00);	//CAN滤波器配置---标准数据帧模式
	SysTick_Configuration(1000);		//系统嘀嗒时钟配置72MHz,单位为uS----定时扫描PC006V21_Server
}
/*******************************************************************************
* 函数名		:	
* 功能描述	:	 
* 输入		:	
* 输出		:
* 返回 		:
*******************************************************************************/
void CAN_TEST_Server(void)
{
	SYSTIME++;
	if(SYSTIME>0xFFFFFF)
	{
		SYSTIME	=	0;
		
	}
	if(SYSTIME%100==0)															//传感器板---旋转电机开始运行时开始采集信号
	{
		CANdata[0]=0x0F;
		CANdata[1]=0x0E;
		CANdata[2]=0x0A;
		CANdata[3]=0x0B;
		
		CAN_StdTX_DATA(0x08,4,CANdata);			//CAN使用标准帧发送数据---发送传感器数据 0.5ms发送间隔
	}
}





#endif
