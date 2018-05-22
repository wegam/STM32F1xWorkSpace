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

#include "string.h"				//串和内存操作函数头文件
#include "stm32f10x_dma.h"


#include "SWITCHID.H"



PD002V30Def sPD002V30;

#define	I2CDataAddr		0		//I2C保存数量起始地址
//#define	I2CPageSize		8		//页大小，一页一通道，前4字节存数量，后4字节存单重


#define BufferSize	12
#define Bus485Size	64
#define Command_ReadData	(unsigned char)0x05
#define Command_SendData	(unsigned char)0x06
//#define	USART_TO_RS485		//USART转485，485转USART测试

//#define PD002V30TEST

unsigned long sysledcnt=0;			//系统运行指示灯扫描计数  0.5秒

u8 txBuffer1[BufferSize]={0};				//USART1-TXBF
u8 rxBuffer1[BufferSize]={0};				//USART1-RXBF
u8 txBuffer_PD[BufferSize]={0};			//USART1-TXBF
u8 rxBuffer_PD[BufferSize]={0};			//USART1-RXBF


u8	txflg1=0;	//USART1发送标志
u8	txflg3=0;	//485BUS发送标志

u16	tx1_tcont=0;
u16	tx3_tcont=0;


SWITCHID_CONF	SWITCHID;
u8 SwitchID=0;	//拔码开关地址

#define RS485_PD_RXEN		PA1=0				//rs485接收称重板使能
#define RS485_PD_TXEN		PA1=1				//rs485发送称重板使能

u8	RS485_PD_txAddr=0;						//发送序号
u8	RS485_PD_rxAddr=0;						//接收序号

RS485_TypeDef BUS485;
u8 Bus485Rx[Bus485Size+5]={0};
u8 Bus485Re[Bus485Size+5]={0};
u8 Bus485Tx[Bus485Size+5]={0};


u8 DebugRx[32]={0};
u8 DebugRe[32]={0};
u8 DebugTx[32]={0};



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
	
//	PWM_OUT(TIM2,PWM_OUTChannel1,1,700);						//PWM设定-20161127版本
	
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

	
	CS5530_Server();			//读取AD值

	PD002V30_RS485_Server();
	PD002V30_USART_Server();
	
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
	
	SwitchID	=	SWITCHID_Read(&SWITCHID);		//
	
	
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
	sPD002V30.I2C.Port.SDA_Port	=	GPIOB;
	sPD002V30.I2C.Port.SDA_Pin	=	GPIO_Pin_7;
	
	sPD002V30.I2C.Port.SCL_Port	=	GPIOB;
	sPD002V30.I2C.Port.SCL_Pin	=	GPIO_Pin_6;
	
	I2C_Configuration(&sPD002V30.I2C.Port);		//启用锁--配置
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
	
	AT24C02_ReadBuffer(&sPD002V30.I2C.Port,I2CDataAddr,Buffer,16);		//获取备份数据
	//通道1
	QuantityNew	=	sPD002V30.ADCSS3CH1.Data.Quantity;		//新数量值
	WeighPieNew	=	sPD002V30.ADCSS3CH1.Data.WeighPie;		//新单重值
	memcpy((u8*)&QuantityBac,Buffer,4);			//数量值
	memcpy((u8*)&WeighPieBac,&Buffer[4],4);	//单重值
	
	if(((QuantityBac!=QuantityNew)||(WeighPieBac!=WeighPieNew))&&(WeighPieNew!=0))	//数量和单重都有变化
	{
		memcpy(Buffer,(u8*)&QuantityNew,4);			//数量值
		memcpy(&Buffer[4],(u8*)&WeighPieNew,4);	//单重值
		AT24C02_WritePage(&sPD002V30.I2C.Port,I2CDataAddr,Buffer);						//一页一通道，前4字节存数量，后4字节存单重	
	}
	
	//通道2
	QuantityNew	=	sPD002V30.ADCSS4CH2.Data.Quantity;		//新数量值
	WeighPieNew	=	sPD002V30.ADCSS4CH2.Data.WeighPie;		//新单重值
	memcpy((u8*)&QuantityBac,&Buffer[8],4);			//数量值
	memcpy((u8*)&WeighPieBac,&Buffer[12],4);		//单重值
	
	if(((QuantityBac!=QuantityNew)||(WeighPieBac!=WeighPieNew))&&(WeighPieNew!=0))	//数量和单重都有变化
	{
		memcpy(&Buffer[8],(u8*)&QuantityNew,4);			//数量值
		memcpy(&Buffer[12],(u8*)&WeighPieNew,4);	//单重值
		AT24C02_WritePage(&sPD002V30.I2C.Port,I2CDataAddr+8,&Buffer[8]);						//一页一通道，前4字节存数量，后4字节存单重	
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
	
//	AT24C02_ReadBuffer(&sPD002V30.I2C.Port,I2CDataAddr,Buffer,16);		//获取备份数据
	//通道1
	WeighPieNew	=	sPD002V30.ADCSS3CH1.Data.WeighPie;		//新单重值
	
	if(WeighPieNew==0)
	{
		AT24C02_ReadBuffer(&sPD002V30.I2C.Port,I2CDataAddr,Buffer,8);		//获取备份数据
		memcpy((u8*)&QuantityBac,Buffer,4);			//数量值
		memcpy((u8*)&WeighPieBac,&Buffer[4],4);	//单重值
		
		if((WeighPieBac!=0xFFFFFFFF)||(WeighPieBac!=0))
		{
			sPD002V30.ADCSS3CH1.Data.Quantity	=	QuantityBac;		//新数量值
			sPD002V30.ADCSS3CH1.Data.WeighPie	=	WeighPieBac;		//新单重值
		}
		else
		{
			//未标定
		}
	}
	//通道2
	WeighPieNew	=	sPD002V30.ADCSS4CH2.Data.WeighPie;		//新单重值
	
	if(WeighPieNew==0)
	{
		AT24C02_ReadBuffer(&sPD002V30.I2C.Port,I2CDataAddr+8,Buffer,8);		//获取备份数据
		memcpy((u8*)&QuantityBac,Buffer,4);			//数量值
		memcpy((u8*)&WeighPieBac,&Buffer[4],4);	//单重值
		if((WeighPieBac!=0xFFFFFFFF)||(WeighPieBac!=0))
		{
			sPD002V30.ADCSS4CH2.Data.Quantity	=	QuantityBac;		//新数量值
			sPD002V30.ADCSS4CH2.Data.WeighPie	=	WeighPieBac;		//新单重值
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
	SWITCHID.NumOfSW	=	4;
	
	SWITCHID.SW1_PORT	=	GPIOA;
	SWITCHID.SW1_Pin	=	GPIO_Pin_4;
	
	SWITCHID.SW2_PORT	=	GPIOA;
	SWITCHID.SW2_Pin	=	GPIO_Pin_5;
	
	SWITCHID.SW3_PORT	=	GPIOA;
	SWITCHID.SW3_Pin	=	GPIO_Pin_6;
	
	SWITCHID.SW4_PORT	=	GPIOA;
	SWITCHID.SW4_Pin	=	GPIO_Pin_7;
	
	SwitchIdInitialize(&SWITCHID);							//
	
	SwitchID	=	SWITCHID_Read(&SWITCHID);		//
}
/*******************************************************************************
* 函数名			:	function
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
*******************************************************************************/
void PD002V30_USART_Cofiguration(void)
{
	BUS485.USARTx	=	USART2;
	BUS485.RS485_CTL_PORT	=	GPIOA;
	BUS485.RS485_CTL_Pin	=	GPIO_Pin_1;
	RS485_DMA_ConfigurationNR	(&BUS485,19200,(u32*)Bus485Rx,Bus485Size);	//USART_DMA配置--查询方式，不开中断,配置完默认为接收状态
	
	USART_DMA_ConfigurationNR	(USART1,115200,(u32*)DebugRx,64);	//USART_DMA配置--查询方式，不开中断
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
	
	temp1	=	sPD002V30.ADCSS3CH1.Data.WeighLive>>0;		//读取AD值，如果返回0xFFFFFFFF,则未读取到24位AD值		//SS3接口，外面
	temp2	=	sPD002V30.ADCSS4CH2.Data.WeighLive>>0;		//读取AD值，如果返回0xFFFFFFFF,则未读取到24位AD值		//SS4接口，里面
	
//	temp1	=	CS5530_ReadData(&sPD002V30.ADCSS3CH1)>>2;		//读取AD值，如果返回0xFFFFFFFF,则未读取到24位AD值		//SS3接口，外面
//	temp2	=	CS5530_ReadData(&sPD002V30.ADCSS4CH2)>>2;		//读取AD值，如果返回0xFFFFFFFF,则未读取到24位AD值		//SS4接口，里面
	if((temp1!=0xFFFFFFFF)&&(temp2!=0xFFFFFFFF))
	{
		USART_DMAPrintf	(USART1,"CH1:%0.8X\r\nCH2:%0.8X\r\n",temp1,temp2);					//自定义printf串口DMA发送程序,后边的省略号就是可变参数
		return;
	}
	if(temp1!=0xFFFFFFFF)
	{
		Value_AD1	=	temp1;
		USART_DMAPrintf	(USART1,"CH1:%0.8X\r\n",temp1);					//自定义printf串口DMA发送程序,后边的省略号就是可变参数
	}
	if(temp2!=0xFFFFFFFF)
	{
		Value_AD2	=	temp2;
		USART_DMAPrintf	(USART1,"CH2:%0.8X\r\n",temp2);					//自定义printf串口DMA发送程序,后边的省略号就是可变参数
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
	u8 Num	=	0;
	Num	=	RS485_ReadBufferIDLE(&BUS485,(u32*)Bus485Re,(u32*)Bus485Rx);	//串口空闲模式读串口接收缓冲区，如果有数据，将数据拷贝到RevBuffer,并返回接收到的数据个数，然后重新将接收缓冲区地址指向RxdBuffer
	if(Num)
	{
		MS200ProCCDef	MS200Pro;
		u8 Address	=	0;
		memcpy((u8*)&MS200Pro,Bus485Re,Num);
		Address	=	MS200Pro.Address;
		//======校验地址
		if(((Address&0x0F)	==SwitchID)||((Address&0x0F)	==SwitchID+1))
		{			
			u8 Bcc8	=	0;
			//数据校验：校验正确后应答
			Bcc8	=	BCC8(&MS200Pro.SerialNumber,9);
			if(Bcc8==MS200Pro.Bcc8)	//校验正确，需要应答
			{
				sPD002V30.RS485.Data.Retry	=	0;
				sPD002V30.RS485.Data.Time		=	0;
				
				if(MS200Pro.Receipt!=0x0B)
				{
					memcpy((u8*)&sPD002V30.RS485.Pro,Bus485Re,Num);	//保存数据					
					
					PD002V30_RS485_Ack(&MS200Pro);
					return;
				}
				else
				{
					sPD002V30.RS485.Pro.Cmd	=	APP_CMD_Null;		//上级应答，任务完成，命令清除
					return;
				}
			}
			
		}
	}
	PD002V30_CMD_Server();		//命令处理
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
void PD002V30_RS485_Ack(MS200ProCCDef *RS485Data)
{
	SysTick_DeleymS(2);											//SysTick延时nmS
	RS485Data->Receipt	=		0x0A;			//向上应答
	RS485Data->Bcc8			=	BCC8(&RS485Data->SerialNumber,9);
	memcpy(Bus485Tx,(u32*)RS485Data,12);
	RS485_DMASend(&BUS485,(u32*)Bus485Tx,12);	//RS485-DMA发送程序
	SysTick_DeleymS(7);											//SysTick延时nmS
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
	unsigned char	State	=	sPD002V30.RS485.Pro.State;		//运行状态位
	PD002V30CmdDef Cmd	=	sPD002V30.RS485.Pro.Cmd;			//命令位	
	//命令判断:根据命令操作
	switch(Cmd)
	{
		case APP_CMD_CTCLEAR:					//清零
					if(State	==	0x01)			//清零第一步，响应层控板，打开抽屉
					{
						
						break;
					}
					else if(State	==	0x02)	//清零第二步，清空药品，关闭抽屉，记录原点AD
					{
						sPD002V30.RS485.Pro.State	=	0;
						sPD002V30.ADCSS3CH1.Flag.GetOri	=	1;		//获取原点标志
						sPD002V30.ADCSS3CH1.Data.WeighFilt	=0xFFFFFFFF;
						return;
					}
					else if(State	==0	&&	sPD002V30.ADCSS3CH1.Data.WeighFilt	!= 0xFFFFFFFF)
					{
						sPD002V30.ADCSS3CH1.Data.Origin	=	sPD002V30.ADCSS3CH1.Data.WeighFilt;
					}
					else
					{
						return;
					}
			break;
		case APP_CMD_CTBIAODINGS1:		/*称重抽屉标定步骤1:放入一定数量的药品*/
					if(State	==	0x01)			//设定第一步，响应层控板，打开抽屉
					{
						break;
					}
					else if(State	==	0x02)	//设定第二步，放入药品，关闭抽屉，响应层控板
					{
						sPD002V30.RS485.Pro.State	=	0;
						sPD002V30.ADCSS3CH1.Data.WeighFilt	=	0xFFFFFFFF;
						sPD002V30.ADCSS3CH1.Data.Quantity		=	0;
						sPD002V30.ADCSS3CH1.Data.WeighPie		=	0;
						return;
					}
					else if(State	==0	&&	sPD002V30.ADCSS3CH1.Data.WeighFilt	!= 0xFFFFFFFF)
					{
						break;
					}
					else
					{
						return;
					}
				break;
		case APP_CMD_CTBIAODINGS2:			/*称重抽屉标定步骤2:输入数量，计算单重，保存单重*/
				if((sPD002V30.ADCSS3CH1.Data.WeighFilt	!=0xFFFFFFFF)&&(sPD002V30.ADCSS3CH1.Data.WeighPie	==0))		//获取稳定AD值
				{
					unsigned long WeiT	=	sPD002V30.ADCSS3CH1.Data.WeighFilt	-	sPD002V30.ADCSS3CH1.Data.Origin;	//获取放入的药品后的药品总重量
					sPD002V30.ADCSS3CH1.Data.Quantity	=	sPD002V30.RS485.Pro.Data;														//数量
					sPD002V30.ADCSS3CH1.Data.WeighPie	=	(WeiT)/sPD002V30.ADCSS3CH1.Data.Quantity;						//计算单重
					sPD002V30.RS485.Pro.State	=	0;
					sPD002V30.ADCSS3CH1.Data.WeighFilt	=0xFFFFFFFF;
					
					AT24C02_SaveData();		//保存数据,一页一通道，前4字节存数量，后4字节存单重
				}
				else if(sPD002V30.ADCSS3CH1.Data.WeighPie	!=0)
				{
					break;
				}
				else
				{
					return;
				}
				break;
		case APP_CMD_CTJIAYAO:			/*称重抽屉加药*/
				if(State	==	0x01)			//加药第一步，更新原点值，打开抽屉
				{
					unsigned long	QuantityNew		=	0;		//数量值
					unsigned long	WeighPieNew		=	0;		//单重
					QuantityNew	=	sPD002V30.ADCSS3CH1.Data.Quantity;		//新数量值
					WeighPieNew	=	sPD002V30.ADCSS3CH1.Data.WeighPie;		//新单重值
	
					if(WeighPieNew==0)
					{					
						AT24C02_ReadData();		//读数据,一页一通道，前4字节存数量，后4字节存单重
						QuantityNew	=	sPD002V30.ADCSS3CH1.Data.Quantity;		//新数量值
						WeighPieNew	=	sPD002V30.ADCSS3CH1.Data.WeighPie;		//新单重值
						if(WeighPieNew==0)		//未标定
						{
							return;			//未标定
						}
						return;
					}					
					else if(sPD002V30.ADCSS3CH1.Data.WeighFilt	!=0xFFFFFFFF)		//获取稳定AD值
					{
						sPD002V30.ADCSS3CH1.Data.Origin	=	sPD002V30.ADCSS3CH1.Data.WeighFilt	-	sPD002V30.ADCSS3CH1.Data.Quantity*sPD002V30.ADCSS3CH1.Data.WeighPie;		//记录新原点值
						sPD002V30.ADCSS3CH1.Data.WeighFilt	=0xFFFFFFFF;
						sPD002V30.RS485.Data.Time	=	40;
						SysTick_DeleymS(8);											//SysTick延时nmS
//						sPD002V30.RS485.Pro.State	=	0;
						break;
					}
					else
					{
						return;
					}
				}
				else if(State	==	0x02)	//加药第二步，关闭抽屉后计算剩余数量，保存数量，上报剩余数量
				{
					if(sPD002V30.ADCSS3CH1.Data.WeighFilt	!=0xFFFFFFFF)		//获取稳定AD值
					{
						sPD002V30.RS485.Pro.State	=	0;
						if(sPD002V30.ADCSS3CH1.Data.WeighFilt>=(sPD002V30.ADCSS3CH1.Data.Origin	-	(sPD002V30.ADCSS3CH1.Data.WeighPie/10)))			//避免出现低于原点值
						{
							sPD002V30.ADCSS3CH1.Data.Quantity=(sPD002V30.ADCSS3CH1.Data.WeighFilt-sPD002V30.ADCSS3CH1.Data.Origin	+	(sPD002V30.ADCSS3CH1.Data.WeighPie/5))/sPD002V30.ADCSS3CH1.Data.WeighPie;
						}
						else
						{
							sPD002V30.ADCSS3CH1.Data.Quantity=0;
						}
						sPD002V30.RS485.Pro.Data	=	sPD002V30.ADCSS3CH1.Data.Quantity;		//485数据
						sPD002V30.ADCSS3CH1.Data.WeighFilt	=0xFFFFFFFF;
						sPD002V30.RS485.Data.Time	=	40;						
						AT24C02_SaveData();		//保存数据,一页一通道，前4字节存数量，后4字节存单重
					}
					else
					{
						return;
					}
				}
				else
				{
					break;
				}
				
				break;
		case APP_CMD_CTFAYAO:				/*称重抽屉发药*/
				if(State	==	0x01)			//加药第一步，更新原点值，打开抽屉
				{
					unsigned long	QuantityNew		=	0;		//数量值
					unsigned long	WeighPieNew		=	0;		//单重
					QuantityNew	=	sPD002V30.ADCSS3CH1.Data.Quantity;		//新数量值
					WeighPieNew	=	sPD002V30.ADCSS3CH1.Data.WeighPie;		//新单重值
	
					if(QuantityNew==0||WeighPieNew==0)
					{					
						AT24C02_ReadData();		//读数据,一页一通道，前4字节存数量，后4字节存单重
						QuantityNew	=	sPD002V30.ADCSS3CH1.Data.Quantity;		//新数量值
						WeighPieNew	=	sPD002V30.ADCSS3CH1.Data.WeighPie;		//新单重值
						if(WeighPieNew==0)		//未标定
						{
							return;			//未标定
						}
					}
					
					if(sPD002V30.ADCSS3CH1.Data.WeighFilt	!=0xFFFFFFFF)		//获取稳定AD值
					{
						sPD002V30.ADCSS3CH1.Data.Origin	=	sPD002V30.ADCSS3CH1.Data.WeighFilt	-	sPD002V30.ADCSS3CH1.Data.Quantity*sPD002V30.ADCSS3CH1.Data.WeighPie;		//记录新原点值
						sPD002V30.ADCSS3CH1.Data.WeighFilt	=0xFFFFFFFF;
						sPD002V30.RS485.Data.Time	=	40;
						SysTick_DeleymS(8);											//SysTick延时nmS
						break;
					}
					else
					{
						return;
					}
				}
				else if(State	==	0x02)	//加药第二步，关闭抽屉后计算剩余数量，保存数量，上报剩余数量
				{
					if(sPD002V30.ADCSS3CH1.Data.WeighFilt	!=0xFFFFFFFF)		//获取稳定AD值
					{
						sPD002V30.RS485.Pro.State	=	0;
						if(sPD002V30.ADCSS3CH1.Data.WeighFilt>=(sPD002V30.ADCSS3CH1.Data.Origin	-	(sPD002V30.ADCSS3CH1.Data.WeighPie/10)))			//避免出现低于原点值
						{
							sPD002V30.ADCSS3CH1.Data.Quantity=(sPD002V30.ADCSS3CH1.Data.WeighFilt-sPD002V30.ADCSS3CH1.Data.Origin	+	(sPD002V30.ADCSS3CH1.Data.WeighPie/5))/sPD002V30.ADCSS3CH1.Data.WeighPie;
						}
						else
						{
							sPD002V30.ADCSS3CH1.Data.Quantity=0;
						}
						sPD002V30.RS485.Pro.Data	=	sPD002V30.ADCSS3CH1.Data.Quantity;		//485数据
						sPD002V30.ADCSS3CH1.Data.WeighFilt	=0xFFFFFFFF;						
						AT24C02_SaveData();		//保存数据,一页一通道，前4字节存数量，后4字节存单重
						break;
					}
					else
					{
						return;
					}
				}
				else
				{
					break;
				}
				
				break;
		default:	return;
	}
	if(sPD002V30.RS485.Data.Retry<=3)
	{
		if(sPD002V30.RS485.Data.Time++>30)
		{
			sPD002V30.RS485.Data.Time	=	0;
			sPD002V30.RS485.Data.Retry++;
		}
		else
		{
			return;
		}
	}
	else
	{
		return;
	}
//	SysTick_DeleymS(8);											//SysTick延时nmS
	sPD002V30.RS485.Pro.Bcc8	=	BCC8(&sPD002V30.RS485.Pro.SerialNumber,9);	
	memcpy(Bus485Tx,(u32*)&sPD002V30.RS485.Pro,12);
	RS485_DMASend(&BUS485,(u32*)Bus485Tx,12);	//RS485-DMA发送程序
	SysTick_DeleymS(7);											//SysTick延时nmS
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
	//SS3接口，外面
	sPD002V30.ADCSS3CH1.Port.CS_PORT=GPIOB;
	sPD002V30.ADCSS3CH1.Port.CS_Pin=GPIO_Pin_12;
	
	sPD002V30.ADCSS3CH1.Port.SDI_PORT=GPIOB;
	sPD002V30.ADCSS3CH1.Port.SDI_Pin=GPIO_Pin_15;
	
	sPD002V30.ADCSS3CH1.Port.SDO_PORT=GPIOB;
	sPD002V30.ADCSS3CH1.Port.SDO_Pin=GPIO_Pin_14;
	
	sPD002V30.ADCSS3CH1.Port.SCLK_PORT=GPIOB;
	sPD002V30.ADCSS3CH1.Port.SCLK_Pin=GPIO_Pin_13;
	
	
	//SS4接口，里面
	sPD002V30.ADCSS4CH2.Port.CS_PORT=GPIOA;
	sPD002V30.ADCSS4CH2.Port.CS_Pin=GPIO_Pin_8;
	
	sPD002V30.ADCSS4CH2.Port.SDI_PORT=GPIOB;
	sPD002V30.ADCSS4CH2.Port.SDI_Pin=GPIO_Pin_15;
	
	sPD002V30.ADCSS4CH2.Port.SDO_PORT=GPIOB;
	sPD002V30.ADCSS4CH2.Port.SDO_Pin=GPIO_Pin_14;
	
	sPD002V30.ADCSS4CH2.Port.SCLK_PORT=GPIOB;
	sPD002V30.ADCSS4CH2.Port.SCLK_Pin=GPIO_Pin_13;	
	
	CS5530_Initialize(&sPD002V30.ADCSS3CH1);
	CS5530_Initialize(&sPD002V30.ADCSS4CH2);
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
	CS5530_Process(&sPD002V30.ADCSS3CH1);		//SS3接口，外面
	CS5530_Process(&sPD002V30.ADCSS4CH2);		//SS4接口，里面
	
//	if(((CS5530_1.Data.WeighFilt	!=0xFFFFFFFF)&&(CS5530_2.Data.WeighFilt	!=0xFFFFFFFF))
//		&&((CS5530_1.Data.WeighFilt	!=0x00)&&(CS5530_2.Data.WeighFilt	!=0x00)))
//	{
//		USART_DMAPrintf	(USART1,"CH1:%0.8X\r\nCH2:%0.8X\r\n",CS5530_1.Data.WeighFilt,CS5530_2.Data.WeighFilt);					//自定义printf串口DMA发送程序,后边的省略号就是可变参数
//		CS5530_1.Data.WeighFilt	=	0;
//		CS5530_2.Data.WeighFilt	=	0;
//	}
#endif

#if 0	
	u32 temp1=0,temp2=0;

	temp1	=	CS5530_ReadData(&CS5530_1);		//读取AD值，如果返回0xFFFFFFFF,则未读取到24位AD值		//SS3接口，外面
	temp2	=	CS5530_ReadData(&CS5530_2);		//读取AD值，如果返回0xFFFFFFFF,则未读取到24位AD值		//SS4接口，里面
	
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
		USART_DMAPrintf	(USART1,"CH1:%0.8X\r\nCH2:%0.8X\r\n",temp1>>2,temp2>>2);					//自定义printf串口DMA发送程序,后边的省略号就是可变参数
		return;
	}
	if(temp1!=0xFFFFFFFF)
	{
		Value_AD1	=	temp1;
		USART_DMAPrintf	(USART1,"CH1:%0.8X\r\n",temp1>>2);					//自定义printf串口DMA发送程序,后边的省略号就是可变参数
	}
	if(temp2!=0xFFFFFFFF)
	{
		Value_AD2	=	temp2;
		USART_DMAPrintf	(USART1,"CH2:%0.8X\r\n",temp2>>2);					//自定义printf串口DMA发送程序,后边的省略号就是可变参数
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
