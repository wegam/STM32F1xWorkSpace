/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : PC001V21.c
* Author             : WOW
* Version            : V2.0.1
* Date               : 06/26/2017
* Description        : PC001V21层控制板.
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

#ifdef PD011V20			//8路电机控制板

#include "PD011V20.H"

#include "STM32_USART.H"
#include "STM32F10x_BitBand.H"
#include "STM32_GPIO.H"
#include "STM32_SYS.H"
#include "STM32_SYSTICK.H"
#include "STM32_WDG.H"
#include "STM32_PWM.H"

#include "string.h"				//串和内存操作函数头文件
#include "stm32f10x_dma.h"

#define RxBufferSize	128

u16 SensTestNum	=	0;

u8 RevBuffer1[RxBufferSize]={0};
u8 RxdBuffer1[RxBufferSize]={0};
u8 TxdBuffer1[RxBufferSize]={0};

u8 RevBuffer4[RxBufferSize]={0};
u8 RxdBuffer4[RxBufferSize]={0};
u8 TxdBuffer4[RxBufferSize]={0};

u8 RevBuffer2[RxBufferSize]={0};
u8 RxdBuffer2[RxBufferSize]={0};
u8 TxdBuffer2[RxBufferSize]={0};

u8 RevBuffer3[RxBufferSize]={0};
u8 RxdBuffer3[RxBufferSize]={0};
u8 TxdBuffer3[RxBufferSize]={0};

u16	SYSTime=0;							//循环计时变量
u16	RS485BTime=0;							//循环计时变量
u8 RS485NUM	=	0;
u16	DelayTime=0;
u8 testFlg=0;
u16	SensorData	=	0;
u16	SensorDataBac	=	0;
RS485_TypeDef RS485A,RS485B;

/*******************************************************************************
* 函数名		:	
* 功能描述	:	 
* 输入		:	
* 输出		:
* 返回 		:
*******************************************************************************/
void PD011V20_Configuration(void)
{
	SYS_Configuration();					//系统配置---打开系统时钟 STM32_SYS.H
	
	GPIO_DeInitAll();							//将所有的GPIO关闭----V20170605
	
	PD011V20_UsartConfiguration();
	PD011V20_GpioConfiguration();
	
	
//	RS485_RX_EN(&RS485_4);
	
	SysTick_Configuration(1000);	//系统嘀嗒时钟配置72MHz,单位为uS
	
//	IWDG_Configuration(1000);			//独立看门狗配置---参数单位ms	
	
	PWM_OUT(TIM2,PWM_OUTChannel1,1,500);						//PWM设定-20161127版本
}
/*******************************************************************************
* 函数名		:	
* 功能描述	:	 
* 输入		:	
* 输出		:
* 返回 		:
*******************************************************************************/
void PD011V20_Server(void)
{
	
	
	IWDG_Feed();								//独立看门狗喂狗
	SYSTime++;
	PD011V20_SensorServer();		//传感器接口
	
	if(SYSTime>=1000)
	{
		SYSTime=0;							//循环计时变量
		PD011V20_OutServer();		//输出接口
	}
	PD011V20_UsartServer();		//串口
	
	
}

/*******************************************************************************
* 函数名		:	
* 功能描述	:	 
* 输入		:	
* 输出		:
* 返回 		:
*******************************************************************************/
void PD011V20_UsartConfiguration(void)
{	
	GPIO_Configuration_OPP50	(GPIOD,	GPIO_Pin_4);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605
	PD4=0;
	
	RS485B.USARTx=USART2;
	RS485B.RS485_CTL_PORT=GPIOA;
	RS485B.RS485_CTL_Pin=GPIO_Pin_1;
	
	RS485A.USARTx=UART4;
	RS485A.RS485_CTL_PORT=GPIOA;
	RS485A.RS485_CTL_Pin=GPIO_Pin_15;	
	
	RS485_DMA_ConfigurationNR	(&RS485B,19200,RxBufferSize);	//USART_DMA配置--查询方式，不开中断,配置完默认为接收状态
	RS485_DMA_ConfigurationNR	(&RS485A,19200,RxBufferSize);	//USART_DMA配置--查询方式，不开中断,配置完默认为接收状态
	
	USART_DMA_ConfigurationNR	(USART1,115200,RxBufferSize);	//USART_DMA配置--查询方式，不开中断
	USART_DMA_ConfigurationNR	(USART3,9600,RxBufferSize);	//USART_DMA配置--查询方式，不开中断
}
/*******************************************************************************
* 函数名			:	function
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
void PD011V20_GpioConfiguration(void)
{
	//传感器
	GPIO_Configuration_IPU	(GPIOE,	GPIO_Pin_All);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605
	//PMOS接口
	GPIO_Configuration_OPP50	(GPIOD,	GPIO_Pin_8);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605
	GPIO_Configuration_OPP50	(GPIOD,	GPIO_Pin_9);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605
	GPIO_Configuration_OPP50	(GPIOB,	GPIO_Pin_14);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605
	GPIO_Configuration_OPP50	(GPIOB,	GPIO_Pin_15);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605
	//电机接口
	GPIO_Configuration_OPP50	(GPIOD,	GPIO_Pin_15);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605
	GPIO_Configuration_OPP50	(GPIOD,	GPIO_Pin_13);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605
	GPIO_Configuration_OPP50	(GPIOD,	GPIO_Pin_11);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605
	GPIO_Configuration_OPP50	(GPIOD,	GPIO_Pin_14);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605
	GPIO_Configuration_OPP50	(GPIOD,	GPIO_Pin_12);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605
	GPIO_Configuration_OPP50	(GPIOD,	GPIO_Pin_10);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605
	
	GPIO_Configuration_OPP50	(GPIOC,	GPIO_Pin_4);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605
	GPIO_Configuration_OPP50	(GPIOB,	GPIO_Pin_0);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605
	GPIO_Configuration_OPP50	(GPIOB,	GPIO_Pin_12);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605
	GPIO_Configuration_OPP50	(GPIOC,	GPIO_Pin_5);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605
	GPIO_Configuration_OPP50	(GPIOB,	GPIO_Pin_1);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605
	GPIO_Configuration_OPP50	(GPIOB,	GPIO_Pin_13);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605
	
	GPIO_Configuration_OPP50	(GPIOD,	GPIO_Pin_7);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605
	GPIO_Configuration_OPP50	(GPIOC,	GPIO_Pin_9);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605
	GPIO_Configuration_OPP50	(GPIOC,	GPIO_Pin_7);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605
	GPIO_Configuration_OPP50	(GPIOA,	GPIO_Pin_8);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605
	GPIO_Configuration_OPP50	(GPIOC,	GPIO_Pin_8);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605
	GPIO_Configuration_OPP50	(GPIOC,	GPIO_Pin_6);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605
	
	GPIO_Configuration_OPP50	(GPIOD,	GPIO_Pin_0);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605
	GPIO_Configuration_OPP50	(GPIOD,	GPIO_Pin_3);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605
	GPIO_Configuration_OPP50	(GPIOD,	GPIO_Pin_5);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605
	GPIO_Configuration_OPP50	(GPIOD,	GPIO_Pin_1);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605
	GPIO_Configuration_OPP50	(GPIOD,	GPIO_Pin_4);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605
	GPIO_Configuration_OPP50	(GPIOD,	GPIO_Pin_6);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605
}
/*******************************************************************************
* 函数名			:	function
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
void PD011V20_UsartServer(void)		//串口
{
	u8 RxNum=0;
	if(RS485BTime++>=30)
	{
		RS485BTime	=	0;
		RS485NUM++;
		RS485_DMAPrintf(&RS485B,"RS485B发送测试数据%0.3d",RS485NUM);					//自定义printf串口DMA发送程序,后边的省略号就是可变参数
		RS485_DMAPrintf(&RS485A,"RS485A发送测试数据%0.3d",RS485NUM);					//自定义printf串口DMA发送程序,后边的省略号就是可变参数
	}
	RxNum=RS485_ReadBufferIDLE(&RS485B,RevBuffer2);	//串口空闲模式读串口接收缓冲区，如果有数据，将数据拷贝到RevBuffer,并返回接收到的数据个数，然后重新将接收缓冲区地址指向RxdBuffer
	if(RxNum)
	{
		RS485_DMAPrintf(&RS485B,"RS485B收到数据\r\n");					//自定义printf串口DMA发送程序,后边的省略号就是可变参数
		USART_DMAPrintf(USART1,"RS485B收到数据\r\n");						//RS485-DMA发送程序
	}
	RxNum=RS485_ReadBufferIDLE(&RS485A,RevBuffer4);					//串口空闲模式读串口接收缓冲区，如果有数据，将数据拷贝到RevBuffer,并返回接收到的数据个数，然后重新将接收缓冲区地址指向RxdBuffer
	if(RxNum)
	{
		RS485_DMAPrintf(&RS485A,"RS485A收到数据\r\n");					//自定义printf串口DMA发送程序,后边的省略号就是可变参数
		USART_DMAPrintf(USART1,"RS485A收到数据\r\n");						//RS485-DMA发送程序
	}
	if(SensorData	!=	SensorDataBac)
	{
		SensorDataBac	=	SensorData;
		if(SensorDataBac	!=	0xFFFF)
		USART_DMAPrintf(USART1,"传感器输入0x%0.4X\r\n",0xFFFF^SensorDataBac);						//RS485-DMA发送程序
	}
}
/*******************************************************************************
* 函数名			:	function
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
void PD011V20_SensorServer(void)		//传感器接口
{
	if(0	==	SYSTime%10)
	{
		SensTestNum++;
	}
//	GPIO_Toggle	(GPIOE,	GPIO_Pin_All);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605
//	GPIO_Write(GPIOE,~SensTestNum);
	SensorData	=	GPIO_ReadInputData(GPIOE);
}
/*******************************************************************************
* 函数名			:	function
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
void PD011V20_OutServer(void)		//输出接口
{	
//		GPIO_Toggle(GPIOB,	GPIO_Pin_13);		
	GPIO_Toggle	(GPIOD,	GPIO_Pin_8);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605
	GPIO_Toggle	(GPIOD,	GPIO_Pin_9);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605
	GPIO_Toggle	(GPIOB,	GPIO_Pin_14);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605
	GPIO_Toggle	(GPIOB,	GPIO_Pin_15);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605

	GPIO_Toggle	(GPIOD,	GPIO_Pin_15);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605
	GPIO_Toggle	(GPIOD,	GPIO_Pin_13);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605
	GPIO_Toggle	(GPIOD,	GPIO_Pin_11);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605
	GPIO_Toggle	(GPIOD,	GPIO_Pin_14);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605
	GPIO_Toggle	(GPIOD,	GPIO_Pin_12);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605
	GPIO_Toggle	(GPIOD,	GPIO_Pin_10);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605

	GPIO_Toggle	(GPIOC,	GPIO_Pin_4);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605
	GPIO_Toggle	(GPIOB,	GPIO_Pin_0);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605
	GPIO_Toggle	(GPIOB,	GPIO_Pin_12);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605
	GPIO_Toggle	(GPIOC,	GPIO_Pin_5);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605
	GPIO_Toggle	(GPIOB,	GPIO_Pin_1);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605
	GPIO_Toggle	(GPIOB,	GPIO_Pin_13);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605

	GPIO_Toggle	(GPIOD,	GPIO_Pin_7);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605
	GPIO_Toggle	(GPIOC,	GPIO_Pin_9);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605
	GPIO_Toggle	(GPIOC,	GPIO_Pin_7);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605
	GPIO_Toggle	(GPIOA,	GPIO_Pin_8);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605
	GPIO_Toggle	(GPIOC,	GPIO_Pin_8);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605
	GPIO_Toggle	(GPIOC,	GPIO_Pin_6);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605

	GPIO_Toggle	(GPIOD,	GPIO_Pin_0);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605
	GPIO_Toggle	(GPIOD,	GPIO_Pin_3);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605
	GPIO_Toggle	(GPIOD,	GPIO_Pin_5);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605
	GPIO_Toggle	(GPIOD,	GPIO_Pin_1);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605
	GPIO_Toggle	(GPIOD,	GPIO_Pin_4);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605
	GPIO_Toggle	(GPIOD,	GPIO_Pin_6);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605
}
#endif
