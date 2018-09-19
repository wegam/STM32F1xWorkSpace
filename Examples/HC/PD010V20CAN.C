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

#ifdef PD010V20CAN			//二路电机控制板

#include "PD010V20CAN.H"


u32 RunTime	=	0;

unsigned short	TextSize	=	0;
CanRxMsg RxMessage;
u8 PowerFlag	=	0;
u8 txBuffer[16]={0};
u8 tem	=	0;
u8 buff[20]={0};
u8 test[8]={0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08};
unsigned char arr	=	0;
unsigned char Set	=	0;
unsigned char arrBac	=	0;
//===============================================================================
//函数:	PD008V11_Configuration
//描述:	缓存架主配置程序
//返回:
//===============================================================================
void PD010V20CAN_Configuration(void)
{
	SYS_Configuration();							//系统配置系统运行时钟72M	

	GPIO_DeInitAll();									//将所有的GPIO关闭----V20170605

	RS232_Configuration();
	CAN_Configuration();

	SysTick_Configuration(1000);			//系统嘀嗒时钟配置72MHz,单位为uS----软件运行以定时扫描模式,定时时间为SysTickTime	
//	IWDG_Configuration(1000);					//独立看门狗配置	Tout-超时复位时间，单位ms	
	PWM_OUT(TIM2,PWM_OUTChannel1,1,900);			//系统运行LED灯 频率1HZ,占空比500/1000
}

//===============================================================================
//函数:	PD008V11_Server
//描述:	缓存架主服务程序
//返回:
//===============================================================================
void PD010V20CAN_Server(void)
{
	CAN_Server();
	
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
void RS232_Configuration(void)
{
	//-------------------------RS232通道2配置
	USART_DMA_ConfigurationNR	(USART1,115200,32);	//USART_DMA配置--查询方式，不开中断
	
	//-------------------------RS232通道1配置
	USART_DMA_ConfigurationNR	(USART2,115200,32);	//USART_DMA配置--查询方式，不开中断
	
	//-------------------------RS232通道2配置
	USART_DMA_ConfigurationNR	(USART3,115200,32);	//USART_DMA配置--查询方式，不开中断
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
void CAN_Configuration(void)
{
	CAN_Configuration_NR(100000);		//CAN1配置---标志位查询方式，不开中断
	//---------------滤波器组01：通用广播帧
	CAN_FilterInitConfiguration_StdData(0x01,0x00,0x0000);		//CAN滤波器配置---标准数据帧模式
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
void RS232_Server(void)
{



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
	unsigned char length	=	0;
	
	if(CAN_RX_DATA(&RxMessage))
	{
		arr++;
		
		length	=	RxMessage.DLC;

		txBuffer[0]=RxMessage.StdId&0XFF;
		
		memcpy(&txBuffer[1],&RxMessage.Data[0],length);
		
		Set	=	RxMessage.StdId&0XFF;
//		arr++;
		
		USART_DMAPrintfList (USART1,"Arr:%0.2d--Set:%0.2d\r\n",arr,Set);					//自定义printf串口DMA发送程序,后边的省略号就是可变参数
		
//		USART_DMASendList   (USART1,txBuffer,length+1);		//串口DMA链表发送程序，如果数据已经传入到DMA，返回Buffer大小，否则数据存入链表
//		USART_DMASendList   (USART2,txBuffer,length+1);		//串口DMA链表发送程序，如果数据已经传入到DMA，返回Buffer大小，否则数据存入链表
//		USART_DMASendList   (USART3,txBuffer,length+1);		//串口DMA链表发送程序，如果数据已经传入到DMA，返回Buffer大小，否则数据存入链表
	}
	else if(RunTime++>8000)
	{
		RunTime	=	0;
		if(arrBac==arr)
		{
			arrBac	=	0;
			arr			=	0;
		}
		else
		{
			arrBac	=	arr;
//			USART_DMAPrintfList (USART1,"Arr:%0.2d\r\n",arr);					//自定义printf串口DMA发送程序,后边的省略号就是可变参数
		}
		if(0	==	PowerFlag)
		{
			PowerFlag	=	1;
			memset(txBuffer,0xFF,16);
//			USART_DMAPrintfList (USART1,"POWERFLAG");					//自定义printf串口DMA发送程序,后边的省略号就是可变参数
			USART_DMASendList   (USART1,txBuffer,16);		//串口DMA链表发送程序，如果数据已经传入到DMA，返回Buffer大小，否则数据存入链表
//			USART_DMAPrintfList (USART1,"%0.2d--%0.2d",arr,Set);					//自定义printf串口DMA发送程序,后边的省略号就是可变参数
		}
		
//		USART_DMASendList   (USART1,txBuffer,20);		//串口DMA链表发送程序，如果数据已经传入到DMA，返回Buffer大小，否则数据存入链表
//		RunTime	=	0;
//		CAN_StdTX_DATA(0x08,8,test);			//CAN使用标准帧发送数据
	}
}


#endif
