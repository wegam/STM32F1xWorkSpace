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

#ifdef PL001V20			//称重控制板--数码管

#include "PL001V20.H"

#include "STM32_GPIO.H"
#include "CD4511.H"
//#include "CD4511BM.H"
#include "STM32_PWM.H"
#include "STM32_SYS.H"
#include "STM32_SYSTICK.H"
#include "STM32F10x_BitBand.H"




#define	CD4511BM_DEBUG_TEST			//调试时数码管计数显示，正常使用时应该注释掉
#define	Test	0

PL001V20Def	PL001V20S;

u16 Time=0;
u16 data=0;


//CD4511Def CD4511;



/*******************************************************************************
*函数名		:	function
*功能描述	:	函数功能说明
*输入			: 
*输出			:	无
*返回值		:	无
*例程			:
*******************************************************************************/
void PL001V20_Configuration(void)
{
	SYS_Configuration();											//系统配置 STM32_SYS.H	
	
	Switch_Configuration();
	CD4511_Configuration();
	RS485_Configuration();
	CAN_Configuration();
	
	
	PWM_OUT(TIM2,PWM_OUTChannel1,1,500);
	SysTick_Configuration(1000);							//系统嘀嗒时钟配置72MHz,单位为uS
}

/*******************************************************************************
*函数名		:	function
*功能描述	:	函数功能说明
*输入			: 
*输出			:	无
*返回值		:	无
*例程			:
*******************************************************************************/
void PL001V20_Server(void)
{
	++Time;	
	if(Time>=50)
	{
		Time=0;	
		++data;		
	}
	if(data>999)
		data=0;
//	CD4511_WriteData(&PL001V20S.CD4511,data);		//BCD转换为Segment输出 只输出0~9
	CD4511_Server();
	Switch_Server();
	RS485_Server();
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
void Switch_Configuration(void)
{
	unsigned char Num	=	6;
	unsigned char i	=	0;
	unsigned char size1	=	0;
	unsigned char size2	=	0;
	
	unsigned long		*Port;
	unsigned long 	*Pin;					//GPIO_Pin_x
	
	size1	=	sizeof(&(PL001V20S.Switch.SW1_PORT))/4;
	size2	=	sizeof(&(PL001V20S.Switch.SW3_Pin))/4;
	
	Port	=	(unsigned long*)&(PL001V20S.Switch.SW1_PORT);
	Pin	=	(unsigned long*)&(PL001V20S.Switch.SW1_Pin);					//GPIO_Pin_x
	
	PL001V20S.Switch.NumOfSW	=	6;
	
	PL001V20S.Switch.SW1_PORT	=	GPIOB;
	PL001V20S.Switch.SW1_Pin	=	GPIO_Pin_8;
	
	PL001V20S.Switch.SW2_PORT	=	GPIOB;
	PL001V20S.Switch.SW2_Pin	=	GPIO_Pin_9;
	
	PL001V20S.Switch.SW3_PORT	=	GPIOB;
	PL001V20S.Switch.SW3_Pin	=	GPIO_Pin_10;
	
	PL001V20S.Switch.SW4_PORT	=	GPIOB;
	PL001V20S.Switch.SW4_Pin	=	GPIO_Pin_11;
	
	PL001V20S.Switch.SW5_PORT	=	GPIOB;
	PL001V20S.Switch.SW5_Pin	=	GPIO_Pin_12;
	
	PL001V20S.Switch.SW6_PORT	=	GPIOB;
	PL001V20S.Switch.SW6_Pin	=	GPIO_Pin_13;
	
	SwitchIdInitialize(&(PL001V20S.Switch));
	SWITCHID_Read(&(PL001V20S.Switch));
	
	for(i	=	0;i<Num;i++)
	{
		GPIO_Configuration_IPU	((GPIO_TypeDef*)(*Port), (unsigned short)*Pin);			//将GPIO相应管脚配置为上拉输入模式----V20170605
		Port	+=	size1+size2;
		Pin		+=	size1+size2;
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
void CD4511_Configuration(void)
{
	//Pin
	PL001V20S.CD4511.Port.A0_PORT=GPIOB;
	PL001V20S.CD4511.Port.A0_Pin=GPIO_Pin_0;
	
	PL001V20S.CD4511.Port.A1_PORT=GPIOB;
	PL001V20S.CD4511.Port.A1_Pin=GPIO_Pin_1;
	
	PL001V20S.CD4511.Port.A2_PORT=GPIOB;
	PL001V20S.CD4511.Port.A2_Pin=GPIO_Pin_2;
	
	PL001V20S.CD4511.Port.A3_PORT=GPIOB;
	PL001V20S.CD4511.Port.A3_Pin=GPIO_Pin_3;
	
	PL001V20S.CD4511.Port.Seg1_PORT=GPIOB;
	PL001V20S.CD4511.Port.Seg1_Pin=GPIO_Pin_15;
	
	PL001V20S.CD4511.Port.Seg2_PORT=GPIOB;
	PL001V20S.CD4511.Port.Seg2_Pin=GPIO_Pin_14;
	
	PL001V20S.CD4511.Port.Seg3_PORT=GPIOB;
	PL001V20S.CD4511.Port.Seg3_Pin=GPIO_Pin_5;
	
	CD4511_Initialize(&PL001V20S.CD4511);
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
	unsigned long BaudRate	=	0;
	unsigned char *RxdB	=	NULL;
	RS485_TypeDef *RS485_Info	=	NULL;
	
	//-------------------------RS485通道1配置
	PL001V20S.RS485A.BaudRate									=	19200;	
	PL001V20S.RS485A.RS485Cof.USARTx					=	USART2;
	PL001V20S.RS485A.RS485Cof.RS485_CTL_PORT	=	GPIOA;
	PL001V20S.RS485A.RS485Cof.RS485_CTL_Pin		=	GPIO_Pin_1;
	
	BaudRate		=	PL001V20S.RS485A.BaudRate;
	RxdB				=	PL001V20S.RS485A.RxdBuffer;
	RS485_Info	=	&(PL001V20S.RS485A.RS485Cof);
	RS485_DMA_ConfigurationNR	(RS485_Info,BaudRate,(u32*)RxdB,USARTBufferSize);	//USART_DMA配置--查询方式，不开中断,配置完默认为接收状态
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
	unsigned short	CANID			=	0;
	unsigned long		BaudRate	=	0;
	
	PL001V20S.CANBUS.BaudRate	=	50000;
	
	BaudRate	=	PL001V20S.CANBUS.BaudRate;
	CANID			=	(PL001V20S.Switch.nSWITCHID)&0xFFFF;
	
	CAN_Configuration_NR(BaudRate);		//CAN1配置---标志位查询方式，不开中断
	//---------------滤波器组01：通用广播帧
	CAN_FilterInitConfiguration_StdData(0x01,0x00,0xFFFF);		//CAN滤波器配置---标准数据帧模式
	//---------------滤波器组02：专用滤波器组
	CAN_FilterInitConfiguration_StdData(0x02,CANID,0xFFFF);		//CAN滤波器配置---标准数据帧模式
}
/*******************************************************************************
*函数名		:	function
*功能描述	:	函数功能说明
*输入			: 
*输出			:	无
*返回值		:	无
*例程			:
*******************************************************************************/
void CD4511_Server(void)
{
	CD4511_Process(&PL001V20S.CD4511);
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
void Switch_Server(void)
{
	unsigned short	SwitchID	=	0;
	SwitchID	=	SWITCHID_Read(&(PL001V20S.Switch));
	if(PL001V20S.Sys.SwitchID	!=	SwitchID)
	{
		PL001V20S.Sys.SwitchID	=	SwitchID;
		PL001V20_Configuration();								//拨码变化，重新配置整板
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
void RS485_Server(void)
{
	unsigned char 	RxNum			=	0;
	unsigned char 	*RxdB			=	NULL;
	unsigned char 	*RevB			=	NULL;
	unsigned char 	*TxdB			=	NULL;
	unsigned short	SwitchID	=	0;
	RS485_TypeDef 	*RS485_Info	=	NULL;
	
	SwitchID	=	PL001V20S.Sys.SwitchID;
	
	//-------------------------RS485通道1
	RxdB				=	PL001V20S.RS485A.RxdBuffer;
	RevB				=	PL001V20S.RS485A.RevBuffer;
	TxdB				=	PL001V20S.RS485A.TxdBuffer;
	RS485_Info	=	&(PL001V20S.RS485A.RS485Cof);	
	RxNum	=	RS485_ReadBufferIDLE(RS485_Info,(u32*)RevB,(u32*)RxdB);	//串口空闲模式读串口接收缓冲区，如果有数据，将数据拷贝到RevBuffer,并返回接收到的数据个数，然后重新将接收缓冲区地址指向RxdBuffer
	if(RxNum)
	{
		unsigned short Temp	=	0;
		Temp	=	RevB[1]*0xFF+RevB[0];
		CD4511_WriteData(&PL001V20S.CD4511,Temp);		//BCD转换为Segment输出 只输出0~9
		
		SysTick_DeleyuS(500);				//SysTick延时nuS
		memcpy(TxdB,RevB,RxNum);
//		RS485_DMASend(RS485_Info,(u32*)TxdB,RxNum);	//RS485-DMA发送程序
	}
#if Test
	if(SwitchID	==	0)
	{
		unsigned long		Time			=	0;
		Time	=	PL001V20S.RS485A.Time;
		if(Time%500	==	0)
		{
			PL001V20S.RS485A.Time	=0;
			RS485_DMASend(RS485_Info,(u32*)TxdB,16);	//RS485-DMA发送程序
		}
		PL001V20S.RS485A.Time	++;
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
void CAN_Server(void)
{
	unsigned char 	RxFlg			=	0;
	unsigned short	CANID			=	0;
	unsigned short	SwitchID	=	0;	
	CanRxMsg *RxMessage	=	NULL;	
	
	SwitchID	=	PL001V20S.Sys.SwitchID;
	RxMessage	=	&(PL001V20S.CANBUS.RxMessage);

	RxFlg	=	CAN_RX_DATA(RxMessage);									//检查CAN接收有无数据
	if(RxFlg)
	{
		unsigned short Temp	=	0;
		Temp	=	RxMessage->Data[0]*0xFF+RxMessage->Data[1];
		CD4511_WriteData(&PL001V20S.CD4511,Temp);		//BCD转换为Segment输出 只输出0~9
		if(SwitchID	==	0)
		{
			unsigned char TxData[8]	=	{0};		
			CANID			=	(PL001V20S.Switch.nSWITCHID)&0xFFFF;
			CAN_StdTX_DATA(CANID,8,TxData);			//CAN使用标准帧发送数据
		}
	}
#if Test
	if(SwitchID	==	0)
	{
		unsigned long		Time			=	0;		
		unsigned char TxData[8]	=	{0};	
		Time	=	PL001V20S.CANBUS.Time;	
		if(Time%500	==	0)
		{
			PL001V20S.CANBUS.Time	=0;
			CANID			=	(PL001V20S.Switch.nSWITCHID)&0xFFFF;
			CAN_StdTX_DATA(CANID,8,TxData);			//CAN使用标准帧发送数据
		}
		PL001V20S.CANBUS.Time	++;		
	}
#endif
}
#endif
