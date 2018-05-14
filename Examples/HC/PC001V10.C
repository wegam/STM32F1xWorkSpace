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
/********************************开锁命令*************************************/
//	命令	SwitchID	锁号
//	锁1：07 ID 01	
//	锁2：07 ID 02
//	锁3：07 ID 03
//	锁4：07 ID 04

/********************************读数命令*************************************/
//	命令	SwitchID
//	05 ID	


#ifdef PC001V10				//托盘药盒主控板

#include "PC001V10.H"



#include "STM32_GPIO.H"
#include "STM32_SYS.H"
#include "STM32_SYSTICK.H"
#include "STM32_WDG.H"
#include "STM32_USART.H"
#include "STM32_PWM.H"
#include "STM32_CAN.H"
#include "STM32F10x_BitBand.H"


#include "LOCK.H"
#include "SWITCHID.H"
#include "STM32_USART.H"

#include "string.h"				//串和内存操作函数头文件
#include "stm32f10x_dma.h"



SWITCHID_CONF	SWITCHID;
u8 SwitchID	=	0;

u32 CAN_BaudRate	=	500000;

u32 GetBufferDelayTime;

u32 LockTestTime	=	0;
sLockSeDef LockSe1;
sLockSeDef LockSe2;
sLockSeDef LockSe3;
sLockSeDef LockSe4;




RS485_TypeDef SL485;

u8 SL485Flg	=	0;
u32 SL485TestTime	=	0;
u8 SL485TestData	=	0;
u8 SL485Rx[16]={0};
u8 SL485Re[16]={0};
u8 SL485Tx[16]={0};

u32 SYSLEDTime	=	0;

CanRxMsg RxMessage;				//CAN接收 
CanTxMsg TxMessage;				//CAN发送
u8 CanData[8]={0};
u8 CanFlag	=	0;
u16 CanCnt	=	0;
u16 CanTime	=	0;

void CAN_Server(void);
//PWM_TimDef PWM_Tim;
/*******************************************************************************
* 函数名		:	
* 功能描述	:	 
* 输入		:	
* 输出		:
* 返回 		:
*******************************************************************************/
void PC001V10_Configuration(void)
{
	SYS_Configuration();					//系统配置---打开系统时钟 STM32_SYS.H
	
	GPIO_DeInitAll();							//将所有的GPIO关闭----V20170605
		
	SysTick_Configuration(1000);		//系统嘀嗒时钟配置72MHz,单位为uS
	
//	IWDG_Configuration(1000);			//独立看门狗配置---参数单位ms	
	
	Lock_Configuration();
	
	SwitchID_Configuration();
	
	RS485_Configuration();
	
	GPIO_Configuration_OPP50	(GPIOC,	GPIO_Pin_9);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605
	
	CAN_Configuration_NR(CAN_BaudRate);				//CAN1配置---标志位查询方式，不开中断
	CAN_FilterInitConfiguration_StdData(0x01,		0x00,			0x00);			//CAN滤波器配置---标准数据帧模式---电机控制板接收外部控制命令接口
//	PWM_OUT(TIM2,PWM_OUTChannel1,1,900);						//PWM设定-20161127版本	
	
//	PWM_OUT_TIMConf(&PWM_Tim);									//PWM输出配置---最大100KHz
}
/*******************************************************************************
* 函数名		:	
* 功能描述	:	 
* 输入		:	
* 输出		:
* 返回 		:
*******************************************************************************/
void PC001V10_Server(void)
{	
//	IWDG_Feed();													//独立看门狗喂狗

	
	if(GetBufferDelayTime++>1000)			//100ms
	{
		GetBufferDelayTime	=	0;
		SwitchID	=	SWITCHID_Read(&SWITCHID);		//
	}
	LockTest();
	RS485_Server();
	CAN_Server();
	if(SYSLEDTime++>500)
	{
		SYSLEDTime	=	0;
		GPIO_Toggle	(GPIOC,	GPIO_Pin_9);		//将GPIO相应管脚输出翻转----V20170605
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
void CAN_Server(void)
{
	u8 status	=	0;		//CAN读取返回0表示无效
//	u8 CanFlag	=	0;
//	u16 CanCnt	=	0;
#if 0			//主机
	status	=	CAN_RX_DATA(&RxMessage);									//检查CAN接收有无数据
	if(status)
	{
		CanTime	=	0;
	}
	else
	{
		CanTime++;
		if(CanTime>=300)
		{
			memset(RxMessage.Data,0x00,8);
		}
		if(CanTime>=500)
		{
			CanTime	=	0;			
//			memset(CanData,0x55,8);
			CanData[0]	=	'M';
			CanData[1]	=	'A';
			CanData[2]	=	'S';
			CanData[3]	=	'T';
			CanData[4]	=	'E';
			CanData[5]	=	'R';
			CanData[6]	=	'M';
			CanData[7]	=	'M';
			CAN_StdTX_DATA(0xFA,8,CanData);			//CAN使用标准帧发送数据
		}
	}
#else		//从机
	status	=	CAN_RX_DATA(&RxMessage);									//检查CAN接收有无数据
	if(status)
	{
		CanTime	=	0;
//		memset(CanData,0x75,8);
		CanData[0]	=	'S';
		CanData[1]	=	'L';
		CanData[2]	=	'A';
		CanData[3]	=	'V';
		CanData[4]	=	'E';
		CanData[5]	=	'R';
		CanData[6]	=	'M';
		CanData[7]	=	'M';
		CAN_StdTX_DATA(0xBD,8,CanData);			//CAN使用标准帧发送数据
	}
	else
	{
		if(CanTime++>=200)
		{
			CanTime	=	0;
			memset(RxMessage.Data,0x00,8);
		}
	}
#endif
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
void RS485_Configuration(void)
{
	SL485.USARTx	=	USART2;
	SL485.RS485_CTL_PORT	= GPIOC;
	SL485.RS485_CTL_Pin		=	GPIO_Pin_8;
	RS485_DMA_ConfigurationNR	(&SL485,19200,(u32*)SL485Rx,9);	//USART_DMA配置--查询方式，不开中断,配置完默认为接收状态
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
void RS485_Server(void)
{
	u8	Num	=	0;	
//	Num	=	RS485_ReadBufferIDLE(&SL485,(u32*)SL485Re,(u32*)SL485Rx);	//串口空闲模式读串口接收缓冲区，如果有数据，将数据拷贝到RevBuffer,并返回接收到的数据个数，然后重新将接收缓冲区地址指向RxdBuffer
//	if(SL485TestTime++>2000)
//	{		
//		SL485TestTime	=	0;
//		if(Num>=2)
//		{
//			if(SL485TestData>200)
//			{
//				SL485TestData=0;
//			}
//			SL485TestData+=1;
//		}
//		else
//		{
//			if(SL485TestData>200)
//			{
//				SL485TestData=0;
//			}
//			SL485TestData+=2;
//		}
//		memset(SL485Tx,SL485TestData,9);
//		SL485Tx[0]	=	SwitchID;
//		RS485_DMASend	(&SL485,(u32*)SL485Tx,9);	//RS485-DMA发送程序		
//	}
	
//	u32 Bus485TestTime	=	0;
//	u8 Bus485TestData	=	0;

#if 1	
	
	Num	=	RS485_ReadBufferIDLE(&SL485,(u32*)SL485Re,(u32*)SL485Rx);	//串口空闲模式读串口接收缓冲区，如果有数据，将数据拷贝到RevBuffer,并返回接收到的数据个数，然后重新将接收缓冲区地址指向RxdBuffer
	if(Num)
	{
		SL485TestTime	=	0;
	}
	if(SL485TestTime++>1000)
	{		
		SL485TestTime	=	0;
		if(SL485TestData++>=100)
		{
			SL485TestData=0;
		}

		memset(SL485Tx,SL485TestData,9);
		SL485Tx[0]	=	SwitchID;
		RS485_DMASend	(&SL485,(u32*)SL485Tx,9);	//RS485-DMA发送程序		
	}

#else			//从机
	Num	=	RS485_ReadBufferIDLE(&SL485,(u32*)SL485Re,(u32*)SL485Rx);	//串口空闲模式读串口接收缓冲区，如果有数据，将数据拷贝到RevBuffer,并返回接收到的数据个数，然后重新将接收缓冲区地址指向RxdBuffer
	if(Num)
	{
		SL485Flg	=	1;
		SL485TestData	=	SL485Re[1]+1;
		SL485TestTime	=	0;
	}
	if(SL485Flg)
	{
		if(SL485TestTime++>50)
		{
			SL485Flg	=	0;
			SL485TestTime	=	0;
			
			memset(SL485Tx,SL485TestData,9);
			SL485Tx[0]	=	SwitchID;
			RS485_DMASend	(&SL485,(u32*)SL485Tx,9);	//RS485-DMA发送程序
		}
	}

	//============================================
#endif
	
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
void SwitchID_Configuration(void)
{
	SWITCHID.NumOfSW	=	8;
	
	SWITCHID.SW1_PORT	=	GPIOB;
	SWITCHID.SW1_Pin	=	GPIO_Pin_0;
	
	SWITCHID.SW2_PORT	=	GPIOB;
	SWITCHID.SW2_Pin	=	GPIO_Pin_1;
	
	SWITCHID.SW3_PORT	=	GPIOB;
	SWITCHID.SW3_Pin	=	GPIO_Pin_10;
	
	SWITCHID.SW4_PORT	=	GPIOB;
	SWITCHID.SW4_Pin	=	GPIO_Pin_11;
	
	SWITCHID.SW5_PORT	=	GPIOB;
	SWITCHID.SW5_Pin	=	GPIO_Pin_14;
	
	SWITCHID.SW6_PORT	=	GPIOB;
	SWITCHID.SW6_Pin	=	GPIO_Pin_15;
	
	SWITCHID.SW7_PORT	=	GPIOC;
	SWITCHID.SW7_Pin	=	GPIO_Pin_6;
	
	SWITCHID.SW8_PORT	=	GPIOC;
	SWITCHID.SW8_Pin	=	GPIO_Pin_7;
	
	SwitchIdInitialize(&SWITCHID);
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
void Lock_Configuration(void)
{

	LockSe1.DrGPIOx	=	GPIOC;
	LockSe1.DrGPIO_Pin_n	=	GPIO_Pin_1;
	
	LockSe1.SeGPIOx	=	GPIOC;
	LockSe1.SeGPIO_Pin_n	=	GPIO_Pin_3;
	LockInitialize(&LockSe1);		//启用锁--配置
	//------------------------------------------
	LockSe2.DrGPIOx	=	GPIOB;
	LockSe2.DrGPIO_Pin_n	=	GPIO_Pin_5;
	
	LockSe2.SeGPIOx	=	GPIOC;
	LockSe2.SeGPIO_Pin_n	=	GPIO_Pin_11;
	LockInitialize(&LockSe2);		//启用锁--配置
	//------------------------------------------
	
	LockSe3.DrGPIOx	=	GPIOC;
	LockSe3.DrGPIO_Pin_n	=	GPIO_Pin_10;
	
	LockSe3.SeGPIOx	=	GPIOA;
	LockSe3.SeGPIO_Pin_n	=	GPIO_Pin_1;
	LockInitialize(&LockSe3);		//启用锁--配置
	//------------------------------------------
	
	LockSe4.DrGPIOx	=	GPIOC;
	LockSe4.DrGPIO_Pin_n	=	GPIO_Pin_5;
	
	LockSe4.SeGPIOx	=	GPIOA;
	LockSe4.SeGPIO_Pin_n	=	GPIO_Pin_7;
	LockInitialize(&LockSe4);		//启用锁--配置
	//------------------------------------------

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
void LockTest(void)
{
	if(LockTestTime++>2000)			//100ms
	{
		LockTestTime	=	0;
		LockSetOn(&LockSe1,2000);		//打开锁
		LockSetOn(&LockSe2,2000);		//打开锁
		LockSetOn(&LockSe3,2000);		//打开锁
		LockSetOn(&LockSe4,2000);		//打开锁
	}
	LockServer(&LockSe1);
	LockServer(&LockSe2);
	LockServer(&LockSe3);
	LockServer(&LockSe4);
}
#endif
