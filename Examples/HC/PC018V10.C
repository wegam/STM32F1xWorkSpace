#ifdef PC018V10

#include "PC018V10.H"
#include "HC_PHY.H"

#include "DS2401.h"	


#include "stm32f10x_exti.h"


#include "STM32_USART.H"
#include "STM32_SPI.H"
#include "STM32_PWM.H"
#include "STM32_GPIO.H"
#include "STM32_SYS.H"
#include "STM32_WDG.H"
#include "STM32_SYSTICK.H"
#include "STM32F10x_BitBand.H"


#include	"stdio.h"			//用于printf
#include	"string.h"		//用于printf
#include	"stdarg.h"		//用于获取不确定个数的参数
#include	"stdlib.h"		//malloc动态申请内存空间


#define	Board_SerialNum	0x0000		//PCB板号

#define	RS485_BaudRate		256000
#define	RS485_BufferSize	32

Borad_InfoDef	PC018V10_Info;
RS485_TypeDef	RS485_Info;

u8 RS485Txd[RS485_BufferSize]	=	{0};
u8 RS485Rxd[RS485_BufferSize]	=	{0};
u8 RS485Rev[RS485_BufferSize]	=	{0};

u8 ch[120]="USART_BASIC_Configuration(USART_TypeDef* USARTx,u32 USART_BaudRate,u8 NVICPreemptionPriority,u8 NVIC_SubPriority)\n";
u8 ch2[17]={0xC0,0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71};

u8 Seg7Buffer[16]={0x00};		//数码管驱动芯片数据缓冲区：包含命令和显示值

u32	SYSTIME	=	0;
u16	DisplayNum	=	0;			//数码管更新数值
u16	DisplayBac	=	0;			//数码显示数值
u16	DisplayTime	=	0;			//数码重更新显示时间----防止数据传输失败

void RS485_Configuration(void);			//RS485配置
	

void RS485_Server(void);						//RS485收发处理
void Seg7_Server(void);							//数码管显示更新

void WriteNumSeg7(unsigned short Num);		//向数码管写入数据
void WriteStatus(char StatusCode);				//向数码管写入状态
void Seg7_Test(void);		//数码管显示测试

/*******************************************************************************
* 函数名			:	function
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
*******************************************************************************/
u8 Seg7_Code[]=
{
	0x3F,			//A0:0
	0x06,			//A1:1
	0x5B,			//A2:2
	0x4F,			//A3:3
	0x66,			//A4:4
	0x6D,			//A5:5
	0x7D,			//A6:6
	0x07,			//A7:7
	0x7F,			//A8:8
	0x6F,			//A9:9
	0x77,			//A10:A
	0x7C,			//A11:B
	0x39,			//A12:C
	0x5E,			//A13:D
	0x79,			//A14:E
	0x71,			//A15:F
	0x50,			//A16:r
	0x5C,			//A17:o
	0x54,			//A18:n
	0x58,			//A19:c
	0x1C,			//A20:u
	0x38,			//A21:L
	0x73,			//A22:P
	0x40,			//A23:-
	0x30			//A24:I
};

//u8 itf=0;

/*******************************************************************************
* 函数名		:	
* 功能描述	:	 
* 输入		:	
* 输出		:
* 返回 		:
*******************************************************************************/
void PC018V10_Configuration(void)
{
	SYS_Configuration();					//系统配置---打开系统时钟 STM32_SYS.H
	RCC_Configuration_HSI();			//使用内部高速晶振
	
	GPIO_DeInitAll();							//将所有的GPIO关闭----V20170605
	
	SysTick_Configuration(1000);	//系统嘀嗒时钟配置72MHz,单位为uS
	
	PWM_OUT(TIM2,PWM_OUTChannel1,1,500);
	


	STM32_SPI_ConfigurationNR(SPI2);	//SPI配置---向数码管板发送数据
	RS485_Configuration();						//RS485配置


	Dallas_Init();
//	Dallas_GetID(SegArr);
	
}
/*******************************************************************************
* 函数名		:	
* 功能描述	:	 
* 输入		:	
* 输出		:
* 返回 		:
*******************************************************************************/
void PC018V10_Server(void)
{
	SYSTIME++;
	if(SYSTIME>=1)
	{
		SYSTIME	=	0;
		Seg7_Test();		//数码管显示测试
//		DisplayNum++;
//		if(DisplayNum>9999)
//			DisplayNum	=0;
//		WriteNumSeg7(DisplayNum);		//向数码管写入数据


		
//		RS485_DMAPrintf	(&RS485_Info,"自定义printf串口DMA发送程序,后边的省略号就是可变参数\t\n");					//自定义printf串口DMA发送程序,后边的省略号就是可变参数
//		Dallas_GetID(SegArr);
	}
//	Seg7_Server();						//数码管显示更新
	RS485_Server();						//RS485收发处理

}
/*******************************************************************************
* 函数名			:	RS485_Configuration
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: 
*******************************************************************************/
void RS485_Configuration(void)			//RS485配置
{
	RS485_Info.RS485_CTL_PORT	=	GPIOA;
	RS485_Info.RS485_CTL_Pin	=	GPIO_Pin_8;
	RS485_Info.USARTx	=	USART1;
	RS485_DMA_ConfigurationNR	(&RS485_Info,RS485_BaudRate,(u32*)RS485Rxd,RS485_BufferSize);	//USART_DMA配置--查询方式，不开中断,配置完默认为接收状态
}
/*******************************************************************************
* 函数名			:	function
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: 
*******************************************************************************/
void RS485_Server(void)							//RS485收发处理
{
	u16 Num	=	0;
	Num	=	RS485_ReadBufferIDLE(&RS485_Info,(u32*)RS485Rev,(u32*)RS485Rxd);	//串口空闲模式读串口接收缓冲区，如果有数据，将数据拷贝到RevBuffer,并返回接收到的数据个数，然后重新将接收缓冲区地址指向RxdBuffer
	if(Num)
	{
		DisplayNum	=	RS485Rev[0];
		DisplayNum	=	(DisplayNum<<8)+RS485Rev[1];
		memcpy(RS485Txd,RS485Rev,Num);									//复制数据
		RS485_DMASend	(&RS485_Info,(u32*)RS485Rev,Num);	//RS485-DMA发送程序
	}
}
/*******************************************************************************
* 函数名			:	function
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: 
*******************************************************************************/
void Seg7_Server(void)		//数码管显示更新
{
	//===============================如果数据有更新---立即更新
	if(DisplayBac	!=	DisplayNum)		
	{
		DisplayBac	=	DisplayNum;
		WriteNumSeg7(DisplayBac);		//向数码管写入数据
		DisplayTime	=	0;
	}
	
	//===============================每1S重新写入一次数据
	if(DisplayTime++	>=	1000)			
	{
		DisplayTime	=	0;
		WriteNumSeg7(DisplayBac);		//向数码管写入数据
		DisplayTime	=	0;
	}
}
/*******************************************************************************
* 函数名			:	function
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: 
*******************************************************************************/
void Seg7_Test(void)		//数码管显示测试
{
	DisplayNum++;
	if(DisplayNum>9999)
		DisplayNum	=0;
	WriteNumSeg7(DisplayNum);		//向数码管写入数据
}
/*******************************************************************************
* 函数名			:	function
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
*******************************************************************************/
void WriteNumSeg7(u16 Num)		//向数码管写入数据
{
	STM32_SPI_ReadWriteData(SPI2,0x8F);		//亮度 0x80（关）<0x88<0x89<0x8A<0x8B<0x8C<0x8D<0x8E<0x8F
	STM32_SPI_ReadWriteData(SPI2,0x40);		//地址模式  0x40-自增;0x44-固定地址
	Seg7Buffer[0]	=	0xC0;												//起始地址
	if(Num/1000	!=	0)
	{
		Seg7Buffer[1]=Seg7_Code[Num/1000];							//
		Seg7Buffer[3]=Seg7_Code[Num%1000/100];
		Seg7Buffer[5]=Seg7_Code[Num%100/10];
	}
	else if(Num/100	!= 0)
	{
		Seg7Buffer[1]=0x00;							//
		Seg7Buffer[3]=Seg7_Code[Num%1000/100];
		Seg7Buffer[5]=Seg7_Code[Num%100/10];
	}
	else if(Num/10	!= 0)
	{
		Seg7Buffer[1]=0x00;							//
		Seg7Buffer[3]=0x00;
		Seg7Buffer[5]=Seg7_Code[Num%100/10];
	}
	else
	{
		Seg7Buffer[1]=0x00;							//
		Seg7Buffer[3]=0x00;
		Seg7Buffer[5]=0x00;
	}
	Seg7Buffer[7]=Seg7_Code[Num%10];	
	STM32_SPI_SendBuffer(SPI2,8,Seg7Buffer);			//发送数据
}
/*******************************************************************************
* 函数名			:	function
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
*******************************************************************************/
void WriteStatus(char StatusCode)		//向数码管写入状态
{
	
	if(StatusCode	==	0)
	{
		return;
	}
	//状态1-------------"P-on"	//上电，未读取地址
	else if(StatusCode	==	1)	
	{
		STM32_SPI_ReadWriteData(SPI2,0x8F);		//亮度
		STM32_SPI_ReadWriteData(SPI2,0x40);		//地址自增
		Seg7Buffer[1]=Seg7_Code[22];									//
		Seg7Buffer[3]=Seg7_Code[23];
		Seg7Buffer[5]=Seg7_Code[17];
		Seg7Buffer[7]=Seg7_Code[18];
		STM32_SPI_SendBuffer(SPI2,8,Seg7Buffer);			//发送数据
	}
	//状态2-------------"ID-n"	//显示此窗口号
	else if(StatusCode	==	2)	
	{
		STM32_SPI_ReadWriteData(SPI2,0x8F);		//亮度
		STM32_SPI_ReadWriteData(SPI2,0x40);		//地址自增
		Seg7Buffer[1]=Seg7_Code[24];							//
		Seg7Buffer[3]=Seg7_Code[13];
		Seg7Buffer[5]=Seg7_Code[23];
		Seg7Buffer[7]=Seg7_Code[6];
		STM32_SPI_SendBuffer(SPI2,8,Seg7Buffer);			//发送数据
	}
	//状态3-------------"uP--"	//升级中
	else if(StatusCode	==	3)	
	{
		STM32_SPI_ReadWriteData(SPI2,0x8F);		//亮度
		STM32_SPI_ReadWriteData(SPI2,0x40);		//地址自增
		Seg7Buffer[1]=Seg7_Code[20];							//
		Seg7Buffer[3]=Seg7_Code[22];
		Seg7Buffer[5]=Seg7_Code[23];
		Seg7Buffer[7]=Seg7_Code[23];
		STM32_SPI_SendBuffer(SPI2,8,Seg7Buffer);			//发送数据
	}
	else
	{
		return;
	}
}



#endif

