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

#ifdef PD002V30				//称重托盘控制器


#include "PD002V30.H"


#include "STM32F10x_BitBand.H"
#include "STM32_GPIO.H"
#include "STM32_SYS.H"
#include "STM32_SYSTICK.H"
#include "STM32_WDG.H"

#include "STM32_PWM.H"

#include 	"TOOL.H"

#include	"stdio.h"			//用于printf
#include	"string.h"		//用于printf
#include	"stdarg.h"		//用于获取不确定个数的参数
#include	"stdlib.h"		//malloc动态申请内存空间

#include "stm32f10x_dma.h"






PD002V30Def MS200;

#define	I2CDataAddr		0		//I2C保存数量起始地址
//#define	I2CPageSize		8		//页大小，一页一通道，前4字节存数量，后4字节存单重
#define	GetDataRetry		20	//获取数据最大重试次数
#define	RS485RetryTime	30	//485发送等待时间--单位ms
#define	RS485RetryCount	5		//485重发次数
#define BusSize			12	//协议指令数据大小
#define Bus485Size	64
#define Command_ReadData	(unsigned char)0x05
#define Command_SendData	(unsigned char)0x06
//#define	USART_TO_RS485		//USART转485，485转USART测试

//#define PD002V30TEST

#define	MinWeightPiece	50	//最低单重AD值，低于表示标定异常

u8 RS485RxBuf[Bus485Size]={0};	//485接收缓存
u8 RS485TxBuf[Bus485Size]={0};	//485发送缓存

//u8 Bus485Rx[Bus485Size+5]={0};
//u8 Bus485Re[Bus485Size+5]={0};
//u8 Bus485Tx[Bus485Size+5]={0};

unsigned long sysledcnt=0;			//系统运行指示灯扫描计数  0.5秒

u8 txBuffer1[BusSize]={0};				//USART1-TXBF
u8 rxBuffer1[BusSize]={0};				//USART1-RXBF
u8 txBuffer_PD[BusSize]={0};			//USART1-TXBF
u8 rxBuffer_PD[BusSize]={0};			//USART1-RXBF


u8	txflg1=0;	//USART1发送标志
u8	txflg3=0;	//485BUS发送标志

u16	tx1_tcont=0;
u16	tx3_tcont=0;



u8 SwitchID=0;	//拔码开关地址

#define RS485_PD_RXEN		PA1=0				//rs485接收称重板使能
#define RS485_PD_TXEN		PA1=1				//rs485发送称重板使能

//u8	RS485_PD_txAddr=0;						//发送序号
//u8	RS485_PD_rxAddr=0;						//接收序号





u8 DebugRx[64]={0};
u8 DebugRe[64]={0};
u8 DebugTx[4096]={0};
unsigned char Num	=	0;


u32 Value_AD1=0;
u32 Value_AD2=0;

u32 Value_ADB1=0;
u32 Value_ADB2=0;

u8 swid=0;
u16 RunTime=0;
HC595_Pindef HC595_Conf;

u8 dnum1=1;
u8 dnum2=2;


//sI2CDef sI2C;
unsigned char Tedata	=	0;
unsigned char Wedata	=	0;
//unsigned char Buffer[16]={0};

void TEMPdelay(u32 time);
/*******************************************************************************
* 函数名		:	
* 功能描述	:	 
* 输入		:	
* 输出		:
* 返回 		:
*******************************************************************************/
void PD002V30_Configuration(void)
{
	SYS_Configuration();					//系统配置---打开系统时钟 STM32_SYS.H
	
	GPIO_DeInitAll();							//将所有的GPIO关闭----V20170605	
	
	GPIO_Configuration_OPP2	(GPIOC,GPIO_Pin_1);			//BUZZER//将GPIO相应管脚配置为OD(开漏)输出模式，最大速度2MHz----V20170605
	
	SwitchID_Configuration();
	
	Seg_Configuration();		//数码管接口配置
	
	SysTick_Configuration(1000);	//系统嘀嗒时钟配置72MHz,单位为uS
	
	PWM_OUT(TIM2,PWM_OUTChannel1,1,700);						//PWM设定-20161127版本
	
	CS5530_Configuration();					//CS5530初始化
//	IWDG_Configuration(1000);			//独立看门狗配置---参数单位ms	
	
	PD002V30_USART_Cofiguration();
	
	AT24C02_Configuration();
	
	PWM_OUT(TIM2,PWM_OUTChannel1,1,900);						//PWM设定-20161127版本
}
/*******************************************************************************
* 函数名		:	
* 功能描述	:	 
* 输入		:	
* 输出		:
* 返回 		:
*******************************************************************************/
void PD002V30_Server(void)
{	
	
	IWDG_Feed();		//独立看门狗喂狗
#if 0	//测试串口收发
	
	Num	=	USART_ReadBufferIDLE(USART1,DebugRx);	//串口空闲模式读串口接收缓冲区，如果有数据，将数据拷贝到RevBuffer,并返回接收到的数据个数
	if(Num)
	{
		memcpy(DebugTx,DebugRx,Num);
		USART_DMASend	(USART1,DebugTx,Num);		//串口DMA发送程序		
	}
	USART_DMASend	(USART1,DebugTx,4096);		//串口DMA发送程序
	return;
#endif	
	
	CS5530_Server();			//读取AD值

//	PD002V30_RS485_Server();
	PD002V30_USART_Server();
//	PD002V30_CMD_Server();		//命令处理
//	PD002V30_WORK_Server();		//状态处理
	
//	RunTime++;

//	
//	if(RunTime>=10)
//	{
//		dnum1++;
//		dnum2++;
//		if(dnum1>9)
//			dnum1=0;
//		if(dnum2>9)
//			dnum2=0;
//		
//		RunTime=0;
//		Seg_Server();					//数码更新接口
////		CS5530_Server();		//读取AD值

//		Wedata++;
//		if(Wedata>=0xFF)
//			Wedata	=	0;		
//	}
	
	SwitchID	=	SWITCHID_Read(&MS200.SWITCHID);		//
	
	
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
void AT24C02_Configuration(void)
{
	sI2CDef	*Port	=	&MS200.AT24C02.Port;
	Port->SDA_Port	=	GPIOB;
	Port->SDA_Pin	=	GPIO_Pin_7;
	
	Port->SCL_Port	=	GPIOB;
	Port->SCL_Pin	=	GPIO_Pin_6;
	
	I2C_Configuration(Port);		//启用锁--配置
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
void AT24C02_SaveData(void)		//保存数据,一页一通道，前4字节存数量，后4字节存单重
{
	unsigned char Buffer[16]	=	{0};
	unsigned long	QuantityBac		=	0;		//数量值
	unsigned long	WeighPieBac		=	0;		//单重
	unsigned long	QuantityNew		=	0;		//数量值
	unsigned long	WeighPieNew		=	0;		//单重
	
	sI2CDef	*I2CPort	=	&MS200.AT24C02.Port;
	
	AT24C02_ReadBuffer(I2CPort,I2CDataAddr,Buffer,16);		//获取备份数据
	
	//通道1
	QuantityNew	=	MS200.CH1SS3.Data.Quantity;				//新数量值
	WeighPieNew	=	MS200.CH1SS3.Data.WeightPiece;		//新单重值
	
	memcpy((u8*)&QuantityBac,Buffer,4);							//数量值
	memcpy((u8*)&WeighPieBac,&Buffer[4],4);					//单重值
	
	if(((QuantityBac!=QuantityNew)||(WeighPieBac!=WeighPieNew))&&(WeighPieNew!=0))	//数量和单重都有变化
	{
		memcpy(Buffer,(u8*)&QuantityNew,4);						//数量值
		memcpy(&Buffer[4],(u8*)&WeighPieNew,4);				//单重值
		AT24C02_WritePage(I2CPort,I2CDataAddr,Buffer);						//一页一通道，前4字节存数量，后4字节存单重	
	}
	
	//通道2
	QuantityNew	=	MS200.CH2SS4.Data.Quantity;		//新数量值
	WeighPieNew	=	MS200.CH2SS4.Data.WeightPiece;		//新单重值
	
	memcpy((u8*)&QuantityBac,&Buffer[8],4);			//数量值
	memcpy((u8*)&WeighPieBac,&Buffer[12],4);		//单重值
	
	if(((QuantityBac!=QuantityNew)||(WeighPieBac!=WeighPieNew))&&(WeighPieNew!=0))	//数量和单重都有变化
	{
		memcpy(&Buffer[8],(u8*)&QuantityNew,4);			//数量值
		memcpy(&Buffer[12],(u8*)&WeighPieNew,4);	//单重值
		AT24C02_WritePage(I2CPort,I2CDataAddr+8,&Buffer[8]);						//一页一通道，前4字节存数量，后4字节存单重	
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
void AT24C02_ReadData(void)		//读数据,一页一通道，前4字节存数量，后4字节存单重
{
	unsigned char Buffer[8]	=	{0};
	unsigned long	QuantityBac		=	0;		//数量值
	unsigned long	WeighPieBac		=	0;		//单重
	unsigned long	WeighPieNew		=	0;		//单重
	
	sI2CDef	*I2CPort	=	&MS200.AT24C02.Port;
	
//	AT24C02_ReadBuffer(&sPD002V30.I2C.Port,I2CDataAddr,Buffer,16);		//获取备份数据
	//通道1
	WeighPieNew	=	MS200.CH1SS3.Data.WeightPiece;		//新单重值
	
	if(WeighPieNew==0)
	{
		AT24C02_ReadBuffer(I2CPort,I2CDataAddr,Buffer,8);		//获取备份数据
		memcpy((u8*)&QuantityBac,Buffer,4);			//数量值
		memcpy((u8*)&WeighPieBac,&Buffer[4],4);	//单重值
		
		if((WeighPieBac!=0xFFFFFFFF)||(WeighPieBac!=0))
		{
			MS200.CH1SS3.Data.Quantity	=	QuantityBac;		//新数量值
			MS200.CH1SS3.Data.WeightPiece	=	WeighPieBac;		//新单重值
		}
		else
		{
			//未标定
		}
	}
	//通道2
	WeighPieNew	=	MS200.CH2SS4.Data.WeightPiece;		//新单重值
	
	if(WeighPieNew==0)
	{
		AT24C02_ReadBuffer(I2CPort,I2CDataAddr+8,Buffer,8);		//获取备份数据
		memcpy((u8*)&QuantityBac,Buffer,4);			//数量值
		memcpy((u8*)&WeighPieBac,&Buffer[4],4);	//单重值
		if((WeighPieBac!=0xFFFFFFFF)||(WeighPieBac!=0))
		{
			MS200.CH2SS4.Data.Quantity		=	QuantityBac;		//新数量值
			MS200.CH2SS4.Data.WeightPiece	=	WeighPieBac;		//新单重值
		}
		else
		{
			//未标定
		}
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
void SwitchID_Configuration(void)
{
	SWITCHID_CONF	*pInfo	=	&MS200.SWITCHID;
	
	pInfo->NumOfSW	=	4;
	
	pInfo->SW1_PORT	=	GPIOA;
	pInfo->SW1_Pin	=	GPIO_Pin_4;
	
	pInfo->SW2_PORT	=	GPIOA;
	pInfo->SW2_Pin	=	GPIO_Pin_5;
	
	pInfo->SW3_PORT	=	GPIOA;
	pInfo->SW3_Pin	=	GPIO_Pin_6;
	
	pInfo->SW4_PORT	=	GPIOA;
	pInfo->SW4_Pin	=	GPIO_Pin_7;
	
	SwitchIdInitialize(pInfo);							//
	
	SwitchID	=	SWITCHID_Read(pInfo);		//
}
/*******************************************************************************
* 函数名			:	function
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
*******************************************************************************/
void PD002V30_USART_Cofiguration(void)
{
	RS485_TypeDef	*RS485	=	&MS200.BUS485;
	RS485->USARTx	=	USART2;
	RS485->RS485_CTL_PORT	=	GPIOA;
	RS485->RS485_CTL_Pin	=	GPIO_Pin_1;
	RS485_DMA_ConfigurationNR	(RS485,19200,Bus485Size);	//USART_DMA配置--查询方式，不开中断,配置完默认为接收状态	
	USART_DMA_ConfigurationNR	(USART1,115200,64);	//USART_DMA配置--查询方式，不开中断
}
/*******************************************************************************
* 函数名			:	function
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
*******************************************************************************/
void PD002V30_USART_Server(void)
{
	u32 temp1=0,temp2=0;	//串口打印
//	temp1	=	sPD002V30.ADCSS3CH1.Data.WeighFilt;
//	temp2	=	sPD002V30.ADCSS4CH2.Data.WeighFilt;
//	
//	sPD002V30.ADCSS3CH1.Data.WeighFilt	=	0xFFFFFFFF;
//	sPD002V30.ADCSS4CH2.Data.WeighFilt	=	0xFFFFFFFF;
//	temp1	=	MS200.CH1SS3.ADC.Data.WeighLive>>0;		//读取AD值，如果返回0xFFFFFFFF,则未读取到24位AD值		//SS3接口，外面
//	temp2	=	MS200.CH2SS4.ADC.Data.WeighLive>>0;		//读取AD值，如果返回0xFFFFFFFF,则未读取到24位AD值		//SS4接口，里面
	
	temp1	=	MS200.CH1SS3.ADC.Data.WeighLive>>0;		//读取AD值，如果返回0xFFFFFFFF,则未读取到24位AD值		//SS3接口，外面
	temp2	=	MS200.CH2SS4.ADC.Data.WeighLive>>0;		//读取AD值，如果返回0xFFFFFFFF,则未读取到24位AD值		//SS4接口，里面
	if((temp1!=0xFFFFFFFF)&&(temp2!=0xFFFFFFFF))
	{
		USART_DMAPrintf	(USART1,"CH1:%0.8X\r\nCH2:%0.8X\r\n",temp1>>2,temp2>>2);					//自定义printf串口DMA发送程序,后边的省略号就是可变参数
		return;
	}
	if((temp1!=0xFFFFFFFF)&&(Value_AD1!=temp1))
	{
		Value_AD1	=	temp1;
		USART_DMAPrintf	(USART1,"CH1:%0.8X\r\n",temp1>>2);					//自定义printf串口DMA发送程序,后边的省略号就是可变参数
	}
	if((temp2!=0xFFFFFFFF)&&(Value_AD2!=temp2))
	{
		Value_AD2	=	temp2;
		USART_DMAPrintf	(USART1,"CH2:%0.8X\r\n",temp2>>2);					//自定义printf串口DMA发送程序,后边的省略号就是可变参数
	}
}
/*******************************************************************************
* 函数名			:	function
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
*******************************************************************************/
void PD002V30_RS485_Server(void)
{
	PD002V30_RS485_Recv();		//RS485接收
	PD002V30_RS485_Send();		//RS485发送
//	Num	=	RS485_ReadBufferIDLE(RS485,RS485RxBuf);	//串口空闲模式读串口接收缓冲区，如果有数据，将数据拷贝到RevBuffer,并返回接收到的数据个数，然后重新将接收缓冲区地址指向RxdBuffer
//	if(Num)
//	{
//		MS200ProCCDef	MS200Pro;
//		u8 Address	=	0;
//		memcpy((u8*)&MS200Pro,RS485RxBuf,Num);
//		Address	=	MS200Pro.Address;
//		//======校验地址
//		if(((Address&0x07)	==SwitchID)||((Address&0x07)	==SwitchID+1))
//		{			
//			u8 Bcc8	=	0;
//			//数据校验：校验正确后应答
//			Bcc8	=	BCC8(&MS200Pro.SerialNumber,9);
//			if(Bcc8==MS200Pro.Bcc8)	//校验正确，需要应答
//			{
//				MS200.RS485Rx.Data.Retry	=	0;
//				MS200.RS485Rx.Data.Time		=	0;
//				
//				if(MS200Pro.Receipt!=0x0B)
//				{
//					memcpy((u8*)&MS200.RS485Rx.Pro,RS485RxBuf,Num);	//保存数据					
//					
//					PD002V30_RS485_Recv();
//					return;
//				}
//				else
//				{
//					MS200.RS485Rx.Pro.Cmd	=	APP_CMD_Null;		//上级应答，任务完成，命令清除
//					return;
//				}
//			}
//			
//		}
//	}
	
//	RS485_ReadBufferIDLE(&BUS485,(u32*)Bus485Re,(u32*)Bus485Rx);	
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
void PD002V30_RS485_Recv(void)
{
	u8 Num	=	0;
	RS485_TypeDef	*RS485Port	=	&MS200.BUS485;
	
	MS200ProCCDef	*Ack		=	&MS200.Ack;					//485接收缓存
	PD002V30CHDef			*Channel			=	&MS200.CH1SS3;		//SS3接口，外面
	
	MS200ProCCDef	*RxBuf1	=	&Channel->RS485Rx.Pro;			//485接收缓存
	MS200ProCCDef	*RxBuf2	=	&Channel->RS485Rx.Pro;			//485接收缓存
	
	MS200ProCCDef	*BcBuf1	=	&Channel->RS485Bc.Pro;			//485接收缓存
	MS200ProCCDef	*BcBuf2	=	&Channel->RS485Bc.Pro;			//485接收缓存
	
	MS200ProCCDef	*TxBuf1	=	&Channel->RS485Tx.Pro;			//485接收缓存
	MS200ProCCDef	*TxBuf2	=	&Channel->RS485Tx.Pro;			//485接收缓存	
	
	
	Num	=	RS485_ReadBufferIDLE(RS485Port,RS485RxBuf);	//串口空闲模式读串口接收缓冲区，如果有数据，将数据拷贝到RevBuffer,并返回接收到的数据个数，然后重新将接收缓冲区地址指向RxdBuffer
	if(Num>=BusSize)	//接收到数据
	{
		char	*Head;
		unsigned char	Bcc8	=	0;
		MS200ProCCDef	RxPro;		//协议接收缓存
		//======查找头标识符并判断
		Head	=	strchr((char*)RS485RxBuf,head1); 			//从左向右，查找s中最左边的匹配字符位置
		if(Head)	//查找到头标识符
		{
			memcpy((u8*)&RxPro,(u8*)Head,BusSize);	//复制
		}
		else
		{
			return;
		}
		//======地址判断
		if(((RxPro.Address&0x0F)!=SwitchID)&&((RxPro.Address&0x0F)!=SwitchID+1))
		{
			return;
		}
		//======BCC校验及数据存储
		Bcc8	=	BCC8((u8*)&RxPro.SerialNumber,9);		//BCC计算
		if(RxPro.Bcc8	==	Bcc8)
		{
			//======判断是否为应答信号
			if((RxPro.Address&0x0F)==SwitchID)
			{
				if(RxPro.Receipt	==	0x0B)		//应答信号
				{
					memset(TxBuf1,0x00,BusSize);						//销毁
					return;
				}
				else
				{
					
					memcpy(RxBuf1,&RxPro,BusSize);
					memcpy(BcBuf1,&RxPro,BusSize);
				}
			}
			else
			{
				if(RxPro.Receipt	==	0x0B)		//应答信号
				{
					memset(TxBuf2,0x00,BusSize);						//销毁
					return;
				}
				else
				{
					memcpy(RxBuf2,&RxPro,BusSize);
					memcpy(BcBuf2,&RxPro,BusSize);					
				}
			}
			memcpy(Ack,&RxPro,BusSize);
			Ack->Receipt	=	0x0A;
		}
		else
		{
		}
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
void PD002V30_RS485_Send(void)
{
	USARTStatusDef	Status	=	USART_IDLESTD;
	RS485_TypeDef 	RS485Info	=	MS200.BUS485;
	USART_TypeDef* 	USARTx	=	MS200.BUS485.USARTx;
	
	MS200ProCCDef			*Ack					=	&MS200.Ack;					//485接收缓存
	PD002V30CHDef			*Channel			=	&MS200.CH1SS3;		//SS3接口，外面	
	MS200ProCCDef			*Pro					=	&Channel->RS485Rx.Pro;
	RS485ProCCDef			*TxB					=	&Channel->RS485Tx;	//485发送缓存
	RS485ProCCDef			*Rxc					=	&Channel->RS485Bc;	//485接收备份缓存
//	CS5530Def 				*ADC					=	&Channel->ADC;		//	
//	PD002V30DataDef		*Data					=	&Channel->Data;
//	WorkStateDef			*WorkState		=	&Channel->WorkState;	//工作状态
//	PD002V30CmdDef 		Cmd						=	Pro->Cmd;							//命令位	
//	unsigned char			State					=	Pro->State;						//运行状态位
	
//	unsigned long			WeightBackUp	=	Data->WeightBackUp;		//操作前备份AD值
//	unsigned long			WeightNew			=	Data->WeightNew;			//操作后新AD值
//	unsigned long			Quantity			=	Data->Quantity;				//数量
//	unsigned long			WeightPiece		=	Data->WeightPiece;		//数量
	
	Status	=	USART_Status(RS485Info.USARTx);		//串口状态检查
	if(Status	!=	USART_IDLESTD)
	{
		return;
	}
	if(Ack->Head.h1	== head1)
	{
		PD002V30_Pro_Packet(Ack);		//协议打包
		RS485_DMASend(&RS485Info,(u8*)Ack,BusSize);	//RS485-DMA发送程序
		memset(Ack,0x00,BusSize);		//销毁数据
	}
	else if(TxB->Pro.Head.h1	== head1)
	{
		if(TxB->Data.Time	++>RS485RetryTime)	//延时等待
		{
			TxB->Data.Time	=	0;
			TxB->Data.Retry	++;
			PD002V30_Pro_Packet(&TxB->Pro);		//协议打包
			RS485_DMASend(&RS485Info,(u8*)&TxB->Pro,BusSize);	//RS485-DMA发送程序
			if(TxB->Data.Retry>=RS485RetryCount)
			{
				TxB->Data.Time	=	0;
				TxB->Data.Retry	=	0;
				memset(&TxB->Pro,0x00,BusSize);		//销毁数据
			}
		}
		
		
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
void PD002V30_Pro_Packet(MS200ProCCDef	*Pro)
{
	if(
		(Pro->Head.h1==head1)&&(Pro->Head.h2==head2)
	&&(Pro->Cmd!=0)
	&&(((Pro->Address&0x0F)==SwitchID)||((Pro->Address&0x0F)==SwitchID+1)))
	{
		Pro->Bcc8	=	BCC8(&Pro->SerialNumber,9);	//BCC计算
	}
	else
	{
		memset(Pro,0x00,BusSize);		//销毁数据
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
void PD002V30_CMD_Server(void)
{
	PD002V30CHDef			*Channel			=	&MS200.CH1SS3;
	MS200ProCCDef			*Pro					=	&Channel->RS485Rx.Pro;
	MS200ProCCDef			*Rxc					=	&Channel->RS485Bc.Pro;
	
	PD002V30DataDef		*Data					=	&Channel->Data;
	WorkStateDef			*WorkState		=	&Channel->WorkState;	//工作状态
	WorkRequstDef			*WorkRequst		=	&Channel->WorkRequst;	//请求类型
	PD002V30CmdDef 		Cmd						=	Pro->Cmd;							//命令位	
	unsigned char			State					=	Pro->State;						//运行状态位
	
	unsigned long			WeightBackUp	=	Data->WeightBackUp;		//操作前备份AD值
	unsigned long			WeightNew			=	Data->WeightNew;			//操作后新AD值
	unsigned long			Quantity			=	Data->Quantity;				//数量
	unsigned long			WeightPiece		=	Data->WeightPiece;				//数量
	
	
	//命令判断:根据命令操作
	switch(Cmd)
	{
		case APP_CMD_CTCLEAR:									//0x25清零
		{
				if(State	==	0x01)								//清零第一步，响应层控板，打开抽屉
				{	
					*WorkRequst	=	RequstIdle;				/*无数据请求*/
					*WorkState	=	StateSuspend;			/*不执行采样操作*/					
				}
				else if(State	==	0x02)						//清零第二步，清空药品，关闭抽屉，记录原点AD
				{
					Rxc->State	=	0x00;
					*WorkRequst	=	RequstIdle;						/*无数据请求*/
					*WorkState	=	StateClearI2CDataReq;	/*不执行采样操作*/
				}
			}
			break;		
		case APP_CMD_CTBIAODINGS1:						//0x26称重抽屉标定步骤1:放入一定数量的药品*/
		{
				if(State	==	0x01)								//设定第一步，响应层控板，打开抽屉
				{
					*WorkRequst	=	RequstBackupData;			/*请求备份操作前AD值*/	
					*WorkState	=	StateGetFiltDataReq;	/*请求获取滤波AD值*/
				}
				else if(State	==	0x02)	//设定第二步，放入药品，关闭抽屉，响应层控板
				{
					Rxc->State	=	0x00;
					*WorkRequst	=	RequstNewData;				/*请求备份操作后AD值*/	
					*WorkState	=	StateGetFiltDataReq;	/*请求获取滤波AD值*/
				}
			}
				break;
		case APP_CMD_CTBIAODINGS2:						//0x27称重抽屉标定步骤2:输入数量，计算单重，保存单重--标定*/
		{
				Data->Quantity	=	Pro->Data;
				*WorkRequst	=	RequstPiece;			/*请求获取单重AD值*/	
				*WorkState	=	StateSuspend;			/*请求保存备份EEPROM数值*/
			}
				break;
		case APP_CMD_CTJIAYAO:			//0x23称重抽屉加药*/
		{
				if(State	==	0x01)			//加药第一步，更新原点值，打开抽屉
				{
					if(Data->WeightPiece==0)
					{					
						AT24C02_ReadData();		//读数据,一页一通道，前4字节存数量，后4字节存单重
						if(Data->WeightPiece==0)		//未标定
						{
							return;			//未标定
						}
						else
						{
							
							*WorkRequst	=	RequstBackupData;			/*请求备份操作前AD值*/	
							*WorkState	=	StateGetFiltDataReq;	/*请求获取滤波AD值*/
						}
					}					
					else
					{
						*WorkRequst	=	RequstBackupData;			/*请求备份操作前AD值*/	
						*WorkState	=	StateGetFiltDataReq;	/*请求获取滤波AD值*/
					}
				}
				else if(State	==	0x02)	//加药第二步，关闭抽屉后计算剩余数量，保存数量，上报剩余数量
				{
					*WorkRequst	=	RequstQuantity;				/*请求获取数量*/	
					*WorkState	=	StateGetFiltDataReq;	/*请求获取滤波AD值*/
				}			
			}
				break;
		case APP_CMD_CTFAYAO:				//0x21称重抽屉发药*/
		{
				if(State	==	0x01)			//加药第一步，更新原点值，打开抽屉
				{
					if(Data->WeightPiece==0)
					{					
						AT24C02_ReadData();		//读数据,一页一通道，前4字节存数量，后4字节存单重
						if(Data->WeightPiece==0)		//未标定
						{
							return;			//未标定
						}
						else
						{
							*WorkRequst	=	RequstBackupData;			/*请求备份操作前AD值*/	
							*WorkState	=	StateGetFiltDataReq;	/*请求获取滤波AD值*/
						}
					}
					else
					{
						*WorkRequst	=	RequstBackupData;			/*请求备份操作前AD值*/	
						*WorkState	=	StateGetFiltDataReq;	/*请求获取滤波AD值*/
					}
				}
				else if(State	==	0x02)	//加药第二步，关闭抽屉后计算剩余数量，保存数量，上报剩余数量
				{
					*WorkRequst	=	RequstQuantity;				/*请求获取数量*/
					*WorkState	=	StateGetFiltDataReq;	/*请求获取滤波AD值*/
				}				
			}
		break;
		case APP_CMD_CTPANDIAN:			//0x22称重抽屉盘点*/
		{
				*WorkRequst	=	RequstQuantity;		/*请求获取数量*/
				*WorkState	=	StateSuspend;			/*不执行采样操作*/		
			}
			break;
		default:	return;
	}
	memset((char*)Pro,0x00,sizeof(MS200ProCCDef));
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
void PD002V30_WORK_Server(void)
{
	PD002V30CHDef			*Channel			=	&MS200.CH1SS3;		//SS3接口，外面	
//	MS200ProCCDef			*Pro					=	&Channel->RS485Rx.Pro;
	MS200ProCCDef			*TxB					=	&Channel->RS485Tx.Pro;	//485发送缓存
	MS200ProCCDef			*Rxc					=	&Channel->RS485Bc.Pro;	//485接收备份缓存
	CS5530Def 				*ADC					=	&Channel->ADC;		//	
	PD002V30DataDef		*Data					=	&Channel->Data;
	WorkRequstDef			*WorkRequst		=	&Channel->WorkRequst;	//请求类型
	WorkStateDef			*WorkState		=	&Channel->WorkState;	//工作状态
//	PD002V30CmdDef 		Cmd						=	Pro->Cmd;							//命令位	
//	unsigned char			State					=	Pro->State;						//运行状态位
	
	unsigned long			WeightBackUp	=	Data->WeightBackUp;		//操作前备份AD值
	unsigned long			WeightNew			=	Data->WeightNew;			//操作后新AD值
	unsigned short		Quantity			=	Data->Quantity;				//数量
	unsigned short		WeightPiece		=	Data->WeightPiece;		//单重
	//命令判断:根据命令操作
	switch(*WorkState)
	{
		case StateIdle:			/*空闲状态*/
		{
			return;
		}
		break;
		case StateSuspend:			/*空闲状态*/
		{
			memcpy(TxB,Rxc,BusSize);		//复制数据
			memset(Rxc,0x00,BusSize);		//销毁备份
			switch(*WorkRequst)
			{
				case RequstPiece :
					*WorkState	=	StateProcessDataExe;	/*执行计算*/
				break;
				default :
					*WorkState	=	StateIdle;		/*空闲状态*/
					return;
				break;
			}
		}
		break;
		case StateClearI2CDataReq:			/*请求清除备份EEPROM数值*/
		{
			//清除数据
			Data->Quantity			=	0;		//数量			
			Data->WeightPiece		=	0;		//单重
			Data->WeightBackUp	=	0;		//操作前备份AD值
			AT24C02_SaveData();					//保存数据,一页一通道，前4字节存数量，后4字节存单重
			
			memcpy(TxB,Rxc,BusSize);		//复制数据
			memset(Rxc,0x00,BusSize);		//销毁备份
			*WorkState	=	StateIdle;		/*空闲状态*/
			*WorkRequst	=	RequstIdle;		/*无数据请求*/
			return;
		}
		break;
		case StateReadI2CDataReq:		/*请求获取备份EEPROM数值*/
		{
			//清除数据
			Data->Quantity			=	0;		//数量			
			Data->WeightPiece		=	0;		//单重
			Data->WeightBackUp	=	0;		//操作前备份AD值
			AT24C02_ReadData();					//保存数据,一页一通道，前4字节存数量，后4字节存单重
			
			memcpy(TxB,Rxc,BusSize);		//复制数据
			memset(Rxc,0x00,BusSize);		//销毁备份
			*WorkState	=	StateIdle;		/*请求保存备份EEPROM数值*/
			*WorkRequst	=	RequstIdle;
			return;
		}
		break;
		case StateSaveI2CDataReq:		/*请求保存备份EEPROM数值*/
		{
			AT24C02_SaveData();					//保存数据,一页一通道，前4字节存数量，后4字节存单重
			
			memcpy(TxB,Rxc,BusSize);		//复制数据
			memset(Rxc,0x00,BusSize);		//销毁备份
			*WorkState	=	StateIdle;		/*请求保存备份EEPROM数值*/
			*WorkRequst	=	RequstIdle;
			return;
		}
		break;
		case StateGetFiltDataReq:			/*请求获取滤波AD值*/
		{
				Data->Time	=	0;
				ADC->Data.WeighFilt	=	0xFFFFFFFF;
				ADC->Data.Time	=	0;
				memset(&ADC->Data.Buffer,0xFF,DataNum);
				*WorkState	=	StateGetFiltDataWait;
			}
			break;		
		case StateGetFiltDataWait:		/*等待获取滤波AD值*/
		{	
			if(Data->Time++>=GetFiltDataDelayTime)
			{
				Data->Time	=	0;
				Data->Retry	=	0;
				*WorkState	=	StateGetFiltDataExe;
				return;
			}
			else
			{
				return;
			}
		}
				break;
		case StateGetFiltDataExe:		/*执行获取滤波AD值*/	
		{
			if(ADC->Data.WeighFilt	== 0xFFFFFFFF)		//获取稳定AD值
			{	
				if(Data->Time++>=GetFiltDataDelayTime)	//读一个AD130ms
				{
					if(Data->Retry++	>=GetDataRetry)	//重试最大值
					{
						Data->Time	=	0;
						Data->Retry	=	0;
						memset(Rxc,0x00,BusSize);		//销毁备份						
						*WorkState	=	StateIdle;		/*请求保存备份EEPROM数值*/
						return;
					}
					Data->Time	=	0;
					return;
				}
				return;
			}
			Data->Time	=	0;
			Data->Retry	=	0;	
			*WorkState	=	StateProcessDataExe;	/*执行计算*/
		}
		break;
		case StateProcessDataExe:	/*执行计算*/
		{
			*WorkState	=	StateIdle;		/*空闲状态*/					
			switch(*WorkRequst)
			{
				case RequstIdle:
						return;
				break;
				case RequstBackupData:
						Data->WeightNew			=	0;
						Data->WeightBackUp	=	ADC->Data.WeighFilt;
						*WorkRequst	=	RequstIdle;		/*无数据请求*/
				break;
				case RequstNewData:
					Data->WeightNew			=	ADC->Data.WeighFilt;
					*WorkRequst	=	RequstIdle;		/*无数据请求*/
				break;
				case RequstPiece:		//标定
					if(Data->Quantity	==0)
					{
						*WorkRequst				=	RequstIdle;		/*无数据请求*/
					}
					Data->WeightNew		=	ADC->Data.WeighFilt;
					if(Data->WeightNew	>	Data->WeightBackUp+MinWeightPiece)	//至少一支药的重量差
					{
						Data->WeightPiece	=	(Data->WeightNew-Data->WeightBackUp)/Data->Quantity;
					}
					else if(Data->WeightBackUp	>	Data->WeightNew+MinWeightPiece)
					{
						Data->WeightPiece	=	(Data->WeightBackUp-Data->WeightNew)/Data->Quantity;
					}
					if(Data->WeightPiece	<	MinWeightPiece)	//单重过小，放入药品数量不对或者未放入
					{
						//==========放入药品数量不对或者未放入
					}
					*WorkState				=	StateSaveI2CDataReq;	/*请求保存备份EEPROM数值*/
					*WorkRequst				=	RequstIdle;		/*无数据请求*/
				break;
				case RequstQuantity:	/*请求获取数量*/
					Data->WeightNew			=	ADC->Data.WeighFilt;	//获取到新AD
					Quantity						=	Data->Quantity;				//数量
					WeightPiece					=	Data->WeightPiece;		//单重
				
					if(Data->WeightPiece	<=	MinWeightPiece)	//未标定
					{
						return;
					}
					//变重
					if(Data->WeightNew	>	Data->WeightBackUp+MinWeightPiece)	//至少一支药的重量差
					{
						Data->Quantity	=	(Data->WeightNew-Data->WeightBackUp	+	Data->WeightPiece/5)/Data->WeightPiece;
						Data->Quantity	+=	Quantity;
					}
					//变轻
					else if(Data->WeightBackUp	>	Data->WeightNew+MinWeightPiece)
					{
						Data->Quantity	=	(Data->WeightBackUp	-	Data->WeightNew	+	Data->WeightPiece/5)/Data->WeightPiece;
						if(Quantity	>	Data->Quantity)
							Data->Quantity	=	Quantity	-	Data->Quantity;
						else
							Data->Quantity	=	0;
					}
					Rxc->State				=	0x00;
					Rxc->Data					=	Data->Quantity;
					*WorkState				=	StateSaveI2CDataReq;	/*请求保存备份EEPROM数值*/
					*WorkRequst				=	RequstIdle;		/*无数据请求*/
				break;
				default:break;					
			}
			memcpy(TxB,Rxc,BusSize);		//复制数据
			memset(Rxc,0x00,BusSize);		//销毁备份
			}
			break;
		default:	break;
	}
}
/*******************************************************************************
* 函数名			:	function
* 功能描述		: 获取拔码开关地址
* 输入			: void
* 返回值			: void
*******************************************************************************/
u8 PD002V30_GetSwitchID(void)
{
	u8 SwitchTemp=0;	

	SwitchTemp|=PA4in<<0;		//S1
	SwitchTemp|=PA5in<<1;		//S2
	SwitchTemp|=PA6in<<2;		//S3
	SwitchTemp|=PA7in<<3;		//S4
	
	SwitchTemp=~SwitchTemp;
	SwitchTemp=SwitchTemp&0x0F;
	
	return SwitchTemp;
}
/*******************************************************************************
* 函数名			:	PC001V21_GetBufferArray
* 功能描述		: 获取4个抽屉8个通道的AD值，一个一个抽屉获取
* 输入			: void
* 返回值			: void
*******************************************************************************/
u8 PD002V30_GetBufferArray(void)
{
	return 0;
}
/*******************************************************************************
* 函数名			:	
* 功能描述		: CS5530初始化
* 输入			: void
* 返回值			: void
*******************************************************************************/
void CS5530_Configuration(void)
{
	
	CS5530Def 		*CS5530	=	NULL;
	CS5530PortDef *Port		=	NULL;
	
	
	CS5530		=	&MS200.CH1SS3.ADC;
	Port			=	&CS5530->Port;
	//SS3接口，外面
	Port->CS_PORT=GPIOB;
	Port->CS_Pin=GPIO_Pin_12;
	
	Port->SDI_PORT=GPIOB;
	Port->SDI_Pin=GPIO_Pin_15;
	
	Port->SDO_PORT=GPIOB;
	Port->SDO_Pin=GPIO_Pin_14;
	
	Port->SCLK_PORT=GPIOB;
	Port->SCLK_Pin=GPIO_Pin_13;
	
	CS5530_Initialize(CS5530);	
	
	
	//SS4接口，里面
	CS5530		=	&MS200.CH2SS4.ADC;
	Port			=	&CS5530->Port;
	
	
	Port->CS_PORT=GPIOA;
	Port->CS_Pin=GPIO_Pin_8;
	
	Port->SDI_PORT=GPIOB;
	Port->SDI_Pin=GPIO_Pin_15;
	
	Port->SDO_PORT=GPIOB;
	Port->SDO_Pin=GPIO_Pin_14;
	
	Port->SCLK_PORT=GPIOB;
	Port->SCLK_Pin=GPIO_Pin_13;	
	
	CS5530_Initialize(CS5530);
}
/*******************************************************************************
* 函数名			:	
* 功能描述		: CS5530初始化
* 输入			: void
* 返回值			: void
*******************************************************************************/
void CS5530_Server(void)
{
#if 1
	CS5530_Process(&MS200.CH1SS3.ADC);		//SS3接口，外面
	CS5530_Process(&MS200.CH2SS4.ADC);		//SS4接口，里面
	
//	if(((CS5530_1.Data.WeighFilt	!=0xFFFFFFFF)&&(CS5530_2.Data.WeighFilt	!=0xFFFFFFFF))
//		&&((CS5530_1.Data.WeighFilt	!=0x00)&&(CS5530_2.Data.WeighFilt	!=0x00)))
//	{
//		USART_DMAPrintf	(USART1,"CH1:%0.8X\r\nCH2:%0.8X\r\n",CS5530_1.Data.WeighFilt,CS5530_2.Data.WeighFilt);					//自定义printf串口DMA发送程序,后边的省略号就是可变参数
//		CS5530_1.Data.WeighFilt	=	0;
//		CS5530_2.Data.WeighFilt	=	0;
//	}
	return;
#endif

#if 0	
	u32 temp1=0,temp2=0;

	temp1	=	CS5530_ReadData(&MS200.CH1SS3.ADC);		//读取AD值，如果返回0xFFFFFFFF,则未读取到24位AD值		//SS3接口，外面
//	temp2	=	CS5530_ReadData(&MS200.CH2SS4.ADC);		//读取AD值，如果返回0xFFFFFFFF,则未读取到24位AD值		//SS4接口，里面
	
//	temp2	=	CS5530_GetWeigh(&CS5530_1);		//获取稳定的AD值
//	temp1	=	CS5530_GetWeigh(&CS5530_2);		//获取稳定的AD值
	
//	if(temp1>Value_AD1)
//	{
//		Value_ADB1	=	temp1	-	Value_AD1;
//	}
//	else
//	{
//		Value_ADB1	=	Value_AD1	-	temp1;
//	}
//	
//	if(temp2>Value_AD2)
//	{
//		Value_ADB2	=	temp2	-	Value_AD2;
//	}
//	else
//	{
//		Value_ADB2	=	Value_AD2	-	temp2;
//	}
//	if(temp1!=0xFFFFFFFF)
//	{
////		USART_DMAPrintf	(USART1,"CH1:%0.8X\r\n",temp1>>2);					//自定义printf串口DMA发送程序,后边的省略号就是可变参数
//	}
	if((temp1!=0xFFFFFFFF)&&(temp2!=0xFFFFFFFF))
	{
		USART_DMAPrintf	(USART1,"CH1:%0.8X\r\nCH2:%0.8X\r\n",temp1>>0,temp2>>0);					//自定义printf串口DMA发送程序,后边的省略号就是可变参数
		return;
	}
	if(temp1!=0xFFFFFFFF)
	{
		Value_AD1	=	temp1;
		USART_DMAPrintf	(USART1,"CH1:%0.8X\r\n",temp1>>0);					//自定义printf串口DMA发送程序,后边的省略号就是可变参数
	}
	if(temp2!=0xFFFFFFFF)
	{
		Value_AD2	=	temp2;
		USART_DMAPrintf	(USART1,"CH2:%0.8X\r\n",temp2>>0);					//自定义printf串口DMA发送程序,后边的省略号就是可变参数
	}
	Value_AD1	=	temp1;
	Value_AD2	=	temp2;
#endif
}
/*******************************************************************************
* 函数名			:	function
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
*******************************************************************************/
void Seg_Configuration(void)			//数码管接口配置
{
	HC595_Conf.HC595_SDA_PORT=GPIOB;
	HC595_Conf.HC595_SDA_Pin=GPIO_Pin_5;
	
	HC595_Conf.HC595_SCK_PORT=GPIOB;
	HC595_Conf.HC595_SCK_Pin=GPIO_Pin_4;
	
	HC595_Conf.HC595_RCK_PORT=GPIOB;
	HC595_Conf.HC595_RCK_Pin=GPIO_Pin_3;
	HC595_PinConf(&HC595_Conf);
}
/*******************************************************************************
* 函数名			:	function
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
*******************************************************************************/
void Seg_Server(void)			//数码更新接口
{
	HC595_RCK_HIGH(&HC595_Conf);
//	SysTick_DeleymS(50);				//SysTick延时nmS
	HC595_WriteNumberN(&HC595_Conf,dnum1);		//反向信号写入---三极管反相
	HC595_WriteNumberN(&HC595_Conf,dnum2);		//反向信号写入---三极管反相
//	SysTick_DeleymS(50);				//SysTick延时nmS
	HC595_RCK_LOW(&HC595_Conf);
}
/*******************************************************************************
* 函数名			:	function
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
*******************************************************************************/
void TEMPdelay(u32 time)
{
	while(time--);
}
#endif
