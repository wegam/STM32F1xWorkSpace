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

#ifdef PD003V11			//G,H版本智能药盒辅控板

#include "PD003V11.H"


#include "A3987.H"

#include "STM32F10x_BitBand.H"
#include "STM32_GPIO.H"
#include "STM32_SYS.H"
#include "STM32_SYSTICK.H"
#include "STM32_WDG.H"
#include "STM32_PWM.H"
#include "STM32_USART.H"

#include "string.h"				//串和内存操作函数头文件
#include "stm32f10x_dma.h"

#define RS485_Bus_RXEN	PA1=0			//rs485总线接收使能
#define RS485_Bus_TXEN	PA1=1			//rs485总线发送使能

#define BufferSize	8
//u8 txBuffer_PD[BufferSize]={0};				//USART2-TXBF
//u8 rxBuffer_PD[BufferSize]={0};				//USART2-RXBF

RS485_TypeDef RS4852;
RS485_TypeDef RS485_Sens;

A3987_Pindef	A3987_Pin1;			//步进电机1
A3987_Pindef	A3987_Pin2;			//步进电机2

u8 RevBuffer[BufferSize]={0};
u8 RxdBuffer[BufferSize]={0};
u8 TxdBuffer[BufferSize]={0};

u8 RevBuffer2[BufferSize]={0};
u8 RxdBuffer2[BufferSize]={0};
u8 TxdBuffer2[BufferSize]={0};

////盘点传感器1
//u8	PS11[6]={0xA0,0x01,0x61,0x00,0xC0,0x0D};
//u8	PS12[6]={0xA0,0x01,0x62,0x00,0xC3,0x0D};
//u8	PS13[6]={0xA0,0x01,0x63,0x00,0xC2,0x0D};
////盘点传感器2
//u8	PS21[6]={0xA0,0x02,0x61,0x00,0xC3,0x0D};
//u8	PS22[6]={0xA0,0x02,0x62,0x00,0xC0,0x0D};
//u8	PS23[6]={0xA0,0x02,0x63,0x00,0xC1,0x0D};


u16	DelayTime=0;


u16 Lock_Toggle_CNT=0;

//-----------盘点传感器
vu16 Stim;
vu8 Sstp;
vu8 Srun;
vu8 Stry;
vu8	Slen;
vu8	PS1F;		//传感器连接标志
vu8	PS2F;


u8 PC3Count	=	0;						//原点1计时
u8 PC12Count	=	0;					//原点2计时

//u8 PC3CountN	=	0;					//原点1计时
//u8 PC12CountN	=	0;					//原点2计时
vu8 start = 0;
u8 MOTOR_RUNFLAG1	=	1;
u8 MOTOR_RUNFLAG2	=	1;

u8 MOTOR_RUNFLAGOW1	=	0;	//电机转出原点传感器位置标志
u8 MOTOR_RUNFLAGOW2	=	0;	//电机转出原点传感器位置标志

void Lock_Toggle(void);			//双向电子锁控制
//void PD003VG_USART_Conf(void);
void USART2_RS485_Conf(void);
void Sens_RS485_Conf(void);
void PDSEND(u8 CMD);		//发送盘点传感器命令

u8 PSDATA(u8 CMD,u8 *Buffer);			//检测传感器收回的数据
void PrintfSstatus(u8 CMD,u8* Buffer);		//打印传感器状态信息
void InitPsFlag(void);		//初始化传感器变量

void PDCHECK(void);			//盘点传感器数据检测
u8 PDSTART(void);			//开始盘点
u8 GetData(void);			//读盘点数量


void MotorCtr(void);		//电机控制
/*******************************************************************************
* 函数名		:	
* 功能描述	:	 
* 输入		:	
* 输出		:
* 返回 		:
*******************************************************************************/
void PD003V11_Configuration(void)
{
	SYS_Configuration();					//系统配置---打开系统时钟 STM32_SYS.H
	
	GPIO_DeInitAll();							//将所有的GPIO关闭----V20170605
	
	PD003V11_PinSet();
	
	
	
	SysTick_Configuration(100);	//系统嘀嗒时钟配置72MHz,单位为uS
	
//	IWDG_Configuration(1000);			//独立看门狗配置---参数单位ms	
	
	PWM_OUT(TIM2,PWM_OUTChannel1,1,1000);						//PWM设定-20161127版本
	
	
	
//	GPIO_Configuration_OPP50	(GPIOB,GPIO_Pin_12);			//将GPIO相应管脚配置为APP(复用推挽)输出模式，最大速度50MHz----V20170605
//	GPIO_Configuration_OPP50	(GPIOB,GPIO_Pin_13);			//将GPIO相应管脚配置为APP(复用推挽)输出模式，最大速度50MHz----V20170605
//	GPIO_Configuration_OPP50	(GPIOB,GPIO_Pin_14);			//将GPIO相应管脚配置为APP(复用推挽)输出模式，最大速度50MHz----V20170605
//	GPIO_Configuration_OPP50	(GPIOB,GPIO_Pin_15);			//将GPIO相应管脚配置为APP(复用推挽)输出模式，最大速度50MHz----V20170605
//	GPIO_Configuration_OPP50	(GPIOB,GPIO_Pin_1);			//将GPIO相应管脚配置为APP(复用推挽)输出模式，最大速度50MHz----V20170605

//	GPIO_ResetBits(A3987_Pin1.A3987_PUL_PORT,			A3987_Pin1.A3987_PUL_Pin);			//使能电机工作
//	GPIO_SetBits(A3987_Pin1.A3987_PUL_PORT,			A3987_Pin1.A3987_PUL_Pin);			//使能电机工作
//	
	USART2_RS485_Conf();
	
	Sens_RS485_Conf();
//	
//	RS485_Bus_TXEN;		//rs485总线接收使能
//	RS485_DMAPrintf(&RS485_Sens,"上电测试\n\r");						//自定义printf串口DMA发送程序,后边的省略号就是可变参数
	
//	USART_DMASend(USART3,(u32*)txBuffer_PD,BufferSize);			//自定义printf串口DMA发送程序
}
/*******************************************************************************
* 函数名		:	
* 功能描述	:	 
* 输入		:	
* 输出		:
* 返回 		:
*******************************************************************************/
void PD003V11_Server(void)
{	
	u16 len	=	0;
	IWDG_Feed();								//独立看门狗喂狗
	DelayTime++;
	if(DelayTime>=50000)
	{
		DelayTime	=	0;
		InitPsFlag();		//初始化传感器变量
//		MOTOR_RUNFLAG1	=	1;		//电机1运行标志
//		MOTOR_RUNFLAG2	=	1;		//电机1运行标志	
//		PDSEND(Srun);			//发送盘点传感器命令
//		if(++Srun	>=6)
//			Srun	=0;
	}
	PDCHECK();			//盘点传感器数据检测
	PDSTART();			//开始盘点
	GetData();			//读盘点数量
	MotorCtr();		//电机控制
	

}
/*******************************************************************************
* 函数名			:	function
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
*******************************************************************************/
void MotorCtr(void)		//电机控制
{
	if(!(start	==1||start	==4||start	==5))
	{
		return;
	}
	//-----------回归原点
	if(start==1)
	{
		if((PC3in==0	||	PC12in==0))
		{
			if(PC3in==0)
			{
				A3987_StepDriver(&A3987_Pin1);
			}
			if(PC12in==0)
			{
				A3987_StepDriver(&A3987_Pin2);
			}			
		}
		else
		{
			start=2;
		}
		return;
	}
	
	//-----------盘点	
	if(start==4)
	{
		if(PC3in	==1)			//原点1计时
		{
			MOTOR_RUNFLAGOW1	=0;
			A3987_StepDriver(&A3987_Pin1);
		}
		else
		{
			MOTOR_RUNFLAGOW1	=1;
		}
		if(PC12in	==1)			//原点1计时
		{
			MOTOR_RUNFLAGOW2	=0;
			A3987_StepDriver(&A3987_Pin2);
		}
		else
		{
			MOTOR_RUNFLAGOW2	=1;
		}
	}
	//-----------盘点	
	if(start==5)
	{
		if(PC3in	==1)			//原点1计时
		{
			MOTOR_RUNFLAGOW1	=0;			
		}
		else
		{
			A3987_StepDriver(&A3987_Pin1);
		}
		if(PC12in	==1)			//原点1计时
		{
			MOTOR_RUNFLAGOW2	=0;
		}
		else
		{
			A3987_StepDriver(&A3987_Pin2);
		}
	}
	
	if(MOTOR_RUNFLAGOW1==1	&&	MOTOR_RUNFLAGOW2	==1	&&start	==4)
	{
		start	=5;
	}
	if(MOTOR_RUNFLAGOW1==0	&&	MOTOR_RUNFLAGOW2	==0	&&start	==5)
	{
		start	=6;
	}


}
/*******************************************************************************
* 函数名			:	function
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
*******************************************************************************/
void PDCHECK(void)			//发送盘点传感器命令
{
//	Stry=	0;
	if(start!=0)
		return;
	Stim++;
	if(Stim>=500)
	{
//		Stry	=	0;
		Stim=0;
	}
	if(Stim	==100)
	{
		PDSEND(Srun);			//发送盘点传感器命令		
	}
	else if(Stim>=160)
	{
		Slen	=	RS485_ReadBufferIDLE(&RS485_Sens,(u32*)RevBuffer2,(u32*)RxdBuffer2);	
		if(Slen)
		{
			if(PSDATA(Srun,RevBuffer2))			//检测传感器收回的数据
			{
//				Stim	=	0;
				Stry	=	0;

				PrintfSstatus(Srun,RevBuffer2);		//打印传感器状态信息
//				RS485_DMASend(&RS4852,(u32*)RevBuffer2,Slen);					//自定义printf串口DMA发送程序,后边的省略号就是可变参数
				
				
				if(Srun	==	0)
				{
					PS1F	=	1;		//传感器连接标志
					Srun	=	3;
				}
				else if(Srun	==	3)
				{
					PS2F	=	1;		//传感器连接标志
				}				
				
				if(PS1F==1	&&	PS2F==1)
				{
					start	=	1;		//启动电机
				}
				else
				{
					start	=	0;
				}
			}
		}
		else
		{
			if(Stim	>=300)
			{
				Stim	=	0;
				if(Stry++==5)			//重复10次				
				{	
					Stry	=	0;
					if(Srun	==0	)		//传感器1无应答
					{
						start	=	0;
						RS485_DMAPrintf(&RS4852,"传感器1无响应\n\r");					//自定义printf串口DMA发送程序,后边的省略号就是可变参数
					}
					else if(Srun	==3)
					{
						PS2F	=	0;		//传感器连接标志
						RS485_DMAPrintf(&RS4852,"传感器2无响应\n\r");					//自定义printf串口DMA发送程序,后边的省略号就是可变参数
					}
				}
			}
		}
	}
}
/*******************************************************************************
* 函数名			:	function
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
*******************************************************************************/
u8 PDSTART(void)			//发送盘点传感器命令
{
//	Stry=	0;
	if(!(start==2||start==3))
	{
		return 0;
	}
	if(start	==2)
	{
			Srun	=	1;
			start	=	3;
	}
	Stim++;
	if(Stim>=500)
	{
//		Stry	=	0;
		Stim=0;
	}
	if(Stim	==100)
	{
		PDSEND(Srun);			//发送盘点传感器命令		
	}
	else if(Stim>=160)
	{
		Slen	=	RS485_ReadBufferIDLE(&RS485_Sens,(u32*)RevBuffer2,(u32*)RxdBuffer2);	
		if(Slen)
		{
			if(PSDATA(Srun,RevBuffer2))			//检测传感器收回的数据
			{
//				Stim	=	0;
				Stry	=	0;

				PrintfSstatus(Srun,RevBuffer2);		//打印传感器状态信息
				if(Srun	==	1)
				{
					Srun	=	4;
				}
				else if(Srun	==	4)
				{
					start	=	4;
//					RS485_DMAPrintf(&RS4852,"读数完成\n\r");					//自定义printf串口DMA发送程序,后边的省略号就是可变参数
//					return 1;
				}
			}
		}
		else
		{
			if(Stim	>=300)
			{
				Stim	=	0;
				if(Stry++==5)			//重复10次				
				{	
					Stry	=	0;
					if(Srun	==1	)		//传感器1无应答
					{
//						Srun	=	4;
						start	=	0;
						RS485_DMAPrintf(&RS4852,"传感器1盘点开始失败\n\r");					//自定义printf串口DMA发送程序,后边的省略号就是可变参数
					}
					else if(Srun	==4)
					{
						start	=	0;
						RS485_DMAPrintf(&RS4852,"传感器2盘点开始失败\n\r");					//自定义printf串口DMA发送程序,后边的省略号就是可变参数
					}
				}
			}
		}
	}
	return 0;
}
/*******************************************************************************
* 函数名			:	function
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
*******************************************************************************/
u8 GetData(void)			//读盘点数量
{
//	Stry=	0;
	if(!(start==6||start==7))
	{
		return 0;
	}
	if(start==6)
	{
			Srun	=	2;
			start	=	7;
	}
	Stim++;
	if(Stim>=500)
	{
//		Stry	=	0;
		Stim=0;
	}
	if(Stim	==100)
	{
		PDSEND(Srun);			//发送盘点传感器命令		
	}
	else if(Stim>=160)
	{
		Slen	=	RS485_ReadBufferIDLE(&RS485_Sens,(u32*)RevBuffer2,(u32*)RxdBuffer2);	
		if(Slen)
		{
			if(PSDATA(Srun,RevBuffer2))			//检测传感器收回的数据
			{
//				Stim	=	0;
				Stry	=	0;

				PrintfSstatus(Srun,RevBuffer2);		//打印传感器状态信息
				if(Srun	==	2)
				{
					Srun	=	5;
				}
				else if(Srun	==	5)
				{
					start	=	8;
//					RS485_DMAPrintf(&RS4852,"读数完成\n\r");					//自定义printf串口DMA发送程序,后边的省略号就是可变参数
					return 1;
				}
			}
		}
		else
		{
			if(Stim	>=300)
			{
				Stim	=	0;
				if(Stry++==5)			//重复10次				
				{	
					Stry	=	0;
					if(Srun	==2	)		//传感器1无应答
					{
//						Srun	=	5;
						start	=	0;
						RS485_DMAPrintf(&RS4852,"传感器1读数失败\n\r");					//自定义printf串口DMA发送程序,后边的省略号就是可变参数
					}
					else if(Srun	==5)
					{
						start	=	0;
						RS485_DMAPrintf(&RS4852,"传感器2读数失败\n\r");					//自定义printf串口DMA发送程序,后边的省略号就是可变参数
					}
				}
			}
		}
	}
	return 0;
}

/*******************************************************************************
* 函数名			:	function
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
*******************************************************************************/
void InitPsFlag(void)		//初始化传感器变量
{	
	if(start==0	||	start==8)
	{
		//-----------盘点传感器
		Stim	=	0;
		Sstp	=	0;
		Srun	=	0;
		Stry	=	0;
		Slen	=	0;
		PS1F	=	0;		//传感器连接标志
		PS2F	=	0;
		
		
		//---------------步进电机
		MOTOR_RUNFLAG1	=	0;		//电机1运行标志
		MOTOR_RUNFLAG2	=	0;		//电机1运行标志
		
		MOTOR_RUNFLAGOW1	=	0;
		MOTOR_RUNFLAGOW2	=	0;
		start	=	0;
		
		//-----系统计时
		DelayTime	=	0;
		
	}	
}
/*******************************************************************************
* 函数名			:	function
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
*******************************************************************************/
void PDSEND(u8 CMD)			//发送盘点传感器命令
{
	//---------------------------盘点1
	if(CMD==0)
	{
		TxdBuffer2[0]=0xA0;
		TxdBuffer2[1]=0x01;
		TxdBuffer2[2]=0x61;
		TxdBuffer2[3]=0x00;
		TxdBuffer2[4]=0xC0;
		TxdBuffer2[5]=0x0D;
	}
	else if(CMD==1)
	{
		TxdBuffer2[0]=0xA0;
		TxdBuffer2[1]=0x01;
		TxdBuffer2[2]=0x62;
		TxdBuffer2[3]=0x00;
		TxdBuffer2[4]=0xC3;
		TxdBuffer2[5]=0x0D;
	}
	else if(CMD==2)
	{
		TxdBuffer2[0]=0xA0;
		TxdBuffer2[1]=0x01;
		TxdBuffer2[2]=0x63;
		TxdBuffer2[3]=0x00;
		TxdBuffer2[4]=0xC2;
		TxdBuffer2[5]=0x0D;
	}
	//---------------------------盘点2
	else if(CMD==3)
	{
		TxdBuffer2[0]=0xA0;
		TxdBuffer2[1]=0x02;
		TxdBuffer2[2]=0x61;
		TxdBuffer2[3]=0x00;
		TxdBuffer2[4]=0xC3;
		TxdBuffer2[5]=0x0D;
	}
	else if(CMD==4)
	{
		TxdBuffer2[0]=0xA0;
		TxdBuffer2[1]=0x02;
		TxdBuffer2[2]=0x62;
		TxdBuffer2[3]=0x00;
		TxdBuffer2[4]=0xC0;
		TxdBuffer2[5]=0x0D;
	}
	else if(CMD==5)
	{
		TxdBuffer2[0]=0xA0;
		TxdBuffer2[1]=0x02;
		TxdBuffer2[2]=0x63;
		TxdBuffer2[3]=0x00;
		TxdBuffer2[4]=0xC1;
		TxdBuffer2[5]=0x0D;
	}
	else
	{
		return;
	}
	RS485_DMASend(&RS485_Sens,(u32*)TxdBuffer2,6);

}
/*******************************************************************************
* 函数名			:	function
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
*******************************************************************************/
u8 PSDATA(u8 CMD,u8 *Buffer)			//检测传感器收回的数据
{
	//---------------------------盘点1
	if(CMD==0)
	{
		if(
			(Buffer[0]==0xA0)	&&
			(Buffer[1]==0x01)	&&
			(Buffer[2]==0x61)
			)
		return 1;
		else
			return 0;
	}
	else if(CMD==1)
	{
		if(
			(Buffer[0]==0xA0)	&&
			(Buffer[1]==0x01)	&&
			(Buffer[2]==0x62)
			)
		return 1;
		else
			return 0;
	}
	else if(CMD==2)
	{
		if(
			(Buffer[0]==0xA0)	&&
			(Buffer[1]==0x01)	&&
			(Buffer[2]==0x63)
			)
		return 1;
		else
			return 0;
	}
	//---------------------------盘点2
	else if(CMD==3)
	{
		if(
			(Buffer[0]==0xA0)	&&
			(Buffer[1]==0x02)	&&
			(Buffer[2]==0x61)
			)
		return 1;
		else
			return 0;
	}
	else if(CMD==4)
	{
		if(
			(Buffer[0]==0xA0)	&&
			(Buffer[1]==0x02)	&&
			(Buffer[2]==0x62)
			)
		return 1;
		else
			return 0;
	}
	else if(CMD==5)
	{
		if(
			(Buffer[0]==0xA0)	&&
			(Buffer[1]==0x02)	&&
			(Buffer[2]==0x63)
			)
		return 1;
		else
			return 0;
	}
	else
	{
		return 0;
	}
}

/*******************************************************************************
* 函数名			:	function
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
*******************************************************************************/
void PrintfSstatus(u8 CMD,u8* Buffer)		//打印传感器状态信息
{
	if(CMD	==0)
	{
		RS485_DMAPrintf(&RS4852,"传感器1准备完成\n\r");					//自定义printf串口DMA发送程序,后边的省略号就是可变参数
	}
	else if(CMD	==1)
	{
		RS485_DMAPrintf(&RS4852,"传感器1开始盘点\n\r");					//自定义printf串口DMA发送程序,后边的省略号就是可变参数
	}
	else if(CMD	==2)
	{
		RS485_DMAPrintf(&RS4852,"传感器1计数%d\n\r",Buffer[3]);					//自定义printf串口DMA发送程序,后边的省略号就是可变参数
	}
	
	//-----------------------------------
	else if(CMD	==3)
	{
		RS485_DMAPrintf(&RS4852,"传感器2准备完成\n\r");					//自定义printf串口DMA发送程序,后边的省略号就是可变参数
	}
	else if(CMD	==4)
	{
		RS485_DMAPrintf(&RS4852,"传感器2开始盘点\n\r");					//自定义printf串口DMA发送程序,后边的省略号就是可变参数
	}
	else if(CMD	==5)
	{
		RS485_DMAPrintf(&RS4852,"传感器2计数%d\n\r",Buffer[3]);					//自定义printf串口DMA发送程序,后边的省略号就是可变参数
	}
	else
		return;

}


/*******************************************************************************
* 函数名			:	function
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
*******************************************************************************/
void USART2_RS485_Conf(void)
{
	RS4852.USARTx=USART2;
	
	RS4852.RS485_CTL_PORT=GPIOA;
	RS4852.RS485_CTL_Pin=GPIO_Pin_1;
	
	RS485_DMA_ConfigurationNR	(&RS4852,115200,(u32*)RxdBuffer,BufferSize);	//USART_DMA配置--查询方式，不开中断
}
/*******************************************************************************
* 函数名			:	function
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
*******************************************************************************/
void Sens_RS485_Conf(void)
{
	RS485_Sens.USARTx=USART3;
	
	RS485_Sens.RS485_CTL_PORT=GPIOB;
	RS485_Sens.RS485_CTL_Pin=GPIO_Pin_1;
	
	RS485_DMA_ConfigurationNR	(&RS485_Sens,9600,(u32*)RxdBuffer2,BufferSize);	//USART_DMA配置--查询方式，不开中断
}
/*******************************************************************************
* 函数名		:	
* 功能描述	:	 
* 输入		:	
* 输出		:
* 返回 		:
*******************************************************************************/
void PD003V11_PinSet(void)
{	
	//步进电机1
	A3987_Pin1.A3987_PUL_PORT		=	GPIOA;
	A3987_Pin1.A3987_PUL_Pin		=	GPIO_Pin_8;
	
	A3987_Pin1.A3987_DIR_PORT		=	GPIOC;
	A3987_Pin1.A3987_DIR_Pin		=	GPIO_Pin_9;
	
	A3987_Pin1.A3987_EN_PORT		=	GPIOC;
	A3987_Pin1.A3987_EN_Pin			=	GPIO_Pin_8;
	
	A3987_Pin1.A3987_MS1_PORT		=	GPIOC;
	A3987_Pin1.A3987_MS1_Pin		=	GPIO_Pin_7;
	
	A3987_Pin1.A3987_MS2_PORT		=	GPIOC;
	A3987_Pin1.A3987_MS2_Pin		=	GPIO_Pin_6;
	
	A3987_PinConf(&A3987_Pin1);
	
//	PC9=1;
	
	//步进电机2
	A3987_Pin2.A3987_PUL_PORT		=	GPIOB;
	A3987_Pin2.A3987_PUL_Pin		=	GPIO_Pin_6;
	
	A3987_Pin2.A3987_DIR_PORT		=	GPIOB;
	A3987_Pin2.A3987_DIR_Pin		=	GPIO_Pin_5;
	
	A3987_Pin2.A3987_EN_PORT		=	GPIOB;
	A3987_Pin2.A3987_EN_Pin			=	GPIO_Pin_7;
	
	A3987_Pin2.A3987_MS1_PORT		=	GPIOB;
	A3987_Pin2.A3987_MS1_Pin		=	GPIO_Pin_8;
	
	A3987_Pin2.A3987_MS2_PORT		=	GPIOB;
	A3987_Pin2.A3987_MS2_Pin		=	GPIO_Pin_9;
	
	A3987_PinConf(&A3987_Pin2);
	


//	//传感器输入
//	GPIO_Configuration_INF(GPIOB,	GPIO_Pin_12);			//将GPIO相应管脚配置为浮空输入模式----V20170605
//	GPIO_Configuration_INF(GPIOB,	GPIO_Pin_13);			//将GPIO相应管脚配置为浮空输入模式----V20170605---中间传感器
//	GPIO_Configuration_INF(GPIOB,	GPIO_Pin_14);			//将GPIO相应管脚配置为浮空输入模式----V20170605---最外边传感器

		//原点传感器输入---原点1
		GPIO_Configuration_IPU(GPIOC,	GPIO_Pin_3);			//将GPIO相应管脚配置为浮空输入模式----V20170605---最外边传感器
		//原点传感器输入---原点2
		GPIO_Configuration_IPU(GPIOC,	GPIO_Pin_12);			//将GPIO相应管脚配置为浮空输入模式----V20170605---最外边传感器

//	//双向电子锁1
//	GPIO_Configuration_OPP50	(GPIOB,	GPIO_Pin_12);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605
//	GPIO_Configuration_OPP50	(GPIOB,	GPIO_Pin_13);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605
//	
//	//双向电子锁1
//	GPIO_Configuration_OPP50	(GPIOB,	GPIO_Pin_14);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605
//	GPIO_Configuration_OPP50	(GPIOB,	GPIO_Pin_15);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605
//	
//	//蜂鸣器
//	GPIO_Configuration_OPP50	(GPIOC,	GPIO_Pin_1);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605
//	
//	//运行灯
//	GPIO_Configuration_OPP50	(GPIOC,	GPIO_Pin_0);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605
	
	
}

/*******************************************************************************
* 函数名			:	function
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
*******************************************************************************/
void Lock_Toggle(void)
{
	Lock_Toggle_CNT++;
	if(Lock_Toggle_CNT>=5000)
	{
		Lock_Toggle_CNT=0;
		PB12=0;
		PB13=0;
		PB14=0;
		PB15=0;
	}
	else if(Lock_Toggle_CNT==100)
	{
		PB12=0;
		PB13=1;
		PB14=0;
		PB15=1;
		GPIO_Toggle	(GPIOC,	GPIO_Pin_1);	//蜂鸣器
		GPIO_Toggle	(GPIOC,	GPIO_Pin_0);	//运行灯
	}
	else if(Lock_Toggle_CNT==200)
	{
		PB12=1;
		PB13=0;
		PB14=1;
		PB15=0;		
	}
	else if(Lock_Toggle_CNT>=300)
	{
		PB12=0;
		PB13=0;
		PB14=0;
		PB15=0;
		
		PC1=0;		//蜂鸣器
		PC0=1;		//运行灯---关闭
	}

}
#endif
