#ifdef PC004V21HC				//单元控制板

#include "PC004V21HC.H"
#include "STM32F10x_BitBand.H"
#include "STM32_GPIO.H"
#include "STM32_SYS.H"
#include "STM32_SYSTICK.H"
#include "STM32_WDG.H"
#include "STM32_PWM.H"


#include "STM32_CAN.H"
#include "STM32_USART.H"
#include "STM32_TOOLS.H"		//数据校验工具

#include "HC_PHY.H"

#include "SWITCHID.H"


#include "string.h"				//串和内存操作函数头文件

//=============================RS485A总线端口(与上层/单元板通讯接口)
RS485Def gRS485Bus;			//与上层总线接口(网关板)
RS485Def gRS485lay;			//与下级总线接口(层板)	

SwitchDef gSwitch;
extern RS485FrameDef	*RS485Node;
/*******************************************************************************
* 函数名		:	
* 功能描述	:	 
* 输入		:	
* 输出		:
* 返回 		:
*******************************************************************************/
void PC004V21HC_Configuration(void)
{
	
	SYS_Configuration();							//系统配置---打开系统时钟 STM32_SYS.H	
	GPIO_DeInitAll();									//将所有的GPIO关闭----V20170605
	
	Communiction_Configuration();			//通讯接口配置：包含RS485,RS232,CAN
	Switch_Configuration();						//拨码开关配置
	Lock_Configuration();							//锁端口配置
	
	
	PWM_OUT(TIM2,PWM_OUTChannel1,1,800);	//PWM设定-20161127版本
	IWDG_Configuration(1000);							//独立看门狗配置---参数单位ms
	SysTick_Configuration(1000);					//系统嘀嗒时钟配置72MHz,单位为uS
}
/*******************************************************************************
* 函数名		:	
* 功能描述	:	 
* 输入		:	
* 输出		:
* 返回 		:
*******************************************************************************/
void PC004V21HC_Server(void)
{

}
/*******************************************************************************
* 函数名			:	Communiction_Configuration
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
void Communiction_Configuration(void)
{
	//=============================RS485Bus总线端口(与上层/单元板通讯接口)
	gRS485Bus.USARTx						=	RS485BusSerialPort;
	gRS485Bus.RS485_CTL_PORT		=	RS485BusCtlPort;
	gRS485Bus.RS485_CTL_Pin			=	RS485BusCtlPin;
	RS485_DMA_ConfigurationNR(&gRS485Bus,RS485BusBaudRate,RS485BusDataSize);			//USART_DMA配置--查询方式，不开中断,配置完默认为接收状态
	
	//=============================RS485Bus总线端口(与上层/单元板通讯接口)
	gRS485lay.USARTx						=	RS485laySerialPort;
	gRS485lay.RS485_CTL_PORT		=	RS485layCtlPort;
	gRS485lay.RS485_CTL_Pin			=	RS485layCtlPin;
	RS485_DMA_ConfigurationNR(&gRS485lay,RS485layBaudRate,RS485layDataSize);			//USART_DMA配置--查询方式，不开中断,配置完默认为接收状态
	
	//=============================RS232A端口(USART1)
	USART_DMA_ConfigurationNR	(RS232ASerialPort,RS232ABaudRate,RS232ADataSize);	//USART_DMA配置--查询方式，不开中断
	
	//=============================RS232B端口(USART3)
	USART_DMA_ConfigurationNR	(RS232BSerialPort,RS232BBaudRate,RS232BDataSize);	//USART_DMA配置--查询方式，不开中断
	
	//=============================CAN
	CAN_Configuration_NR(CANBaudRate);													//CAN1配置---标志位查询方式，不开中断
	CAN_FilterInitConfiguration_StdData(0X01,0X000,0X000);			//CAN滤波器配置---标准数据帧模式---不过滤
}
/*******************************************************************************
* 函数名			:	Communiction_Configuration
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
void Switch_Configuration(void)
{
	gSwitch.NumOfSW	=	8;
	
	gSwitch.SW1_PORT	=	GPIOxSW1;
	gSwitch.SW1_Pin		=	PinxSW1;
	
	gSwitch.SW2_PORT	=	GPIOxSW2;
	gSwitch.SW2_Pin		=	PinxSW2;
	
	gSwitch.SW3_PORT	=	GPIOxSW3;
	gSwitch.SW3_Pin		=	PinxSW3;
	
	gSwitch.SW4_PORT	=	GPIOxSW4;
	gSwitch.SW4_Pin		=	PinxSW4;
	
	gSwitch.SW5_PORT	=	GPIOxSW5;
	gSwitch.SW5_Pin		=	PinxSW5;
	
	gSwitch.SW6_PORT	=	GPIOxSW6;
	gSwitch.SW6_Pin		=	PinxSW6;
	
	gSwitch.SW7_PORT	=	GPIOxSW7;
	gSwitch.SW7_Pin		=	PinxSW7;
	
	gSwitch.SW8_PORT	=	GPIOxSW8;
	gSwitch.SW8_Pin		=	PinxSW8;
	
	SwitchIdInitialize(&gSwitch);
}
/*******************************************************************************
* 函数名			:	Communiction_Configuration
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
void Lock_Configuration(void)
{

}
#endif
