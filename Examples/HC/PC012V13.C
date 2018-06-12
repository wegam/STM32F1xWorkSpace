#ifdef PC012V13

#include "PC012V13.H"


#include "stm32f10x_exti.h"

#include "SWITCHID.H"
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

SWITCHID_CONF	SWITCHID;
u8 SwitchID	=	0;


RS485_TypeDef  IN485,OUT485,PORT485A,PORT485B,PORT485C;
u8 RxdBuffe[16]={0};
u8 RevBuffe[16]={0};
u8 RxdBuffe1[8]={0};
u8 RevBuffe1[8]={0};
u8 RxdBuffe2[8]={0};
u8 RevBuffe2[8]={0};
u8 RxdBuffe3[8]={0};
u8 RevBuffe3[8]={0};

u8 U5Time	=	0;
u8 U5Num	=	0;
u8 RecByte	=	0;

void Switch_Configuration(void);	//拔码开关初始化及读数
void RS485_Configuration(void);		//RS485配置
void RS485_Server(void);
void UART5_Server(void);
/*******************************************************************************
* 函数名		:	
* 功能描述	:	 
* 输入		:	
* 输出		:
* 返回 		:
*******************************************************************************/
void PC012V13_Configuration(void)
{
	//========================系统时钟初始化
	SYS_Configuration();							//系统配置---打开系统时钟 STM32_SYS.H		
	//========================延时1秒，等待上电稳定
	Switch_Configuration();						//拔码开关初始化及读数
	RS485_Configuration();						//RS485配置
	//========================运行指示灯初始化：频率1秒，占空比500/1000
	PWM_OUT(TIM2,PWM_OUTChannel1,1,500);
	//========================SysTick初始化：用作周期扫描PC016V20_Server
	SysTick_Configuration(1000);	//系统嘀嗒时钟配置72MHz,单位为uS	
	//========================独立看门狗初始化：1秒	
	IWDG_Configuration(1000);					//独立看门狗配置---参数单位ms
}
/*******************************************************************************
* 函数名		:	PC016V20_Server
* 功能描述	:	1ms扫描周期 
* 输入		:	
* 输出		:
* 返回 		:
*******************************************************************************/
void PC012V13_Server(void)
{
	IWDG_Feed();								//独立看门狗喂狗
	
	SwitchID	=	SWITCHID_Read(&SWITCHID);		//
	
	RS485_Server();
	
	UART5_Server();

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
	u8 Num	=	0;
	Num	=	RS485_ReadBufferIDLE			(&PORT485B,RevBuffe2);	//串口空闲模式读串口接收缓冲区，如果有数据，将数据拷贝到RevBuffer,并返回接收到的数据个数，然后重新将接收缓冲区地址指向RxdBuffer
	if(Num)
	{
		RS485_DMASend	(&PORT485C,RevBuffe2,Num);	//RS485-DMA发送程序
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
void UART5_Server(void)
{
//	U5Time	=	0;
//	U5Num	=	0;
//	RecByte	=	0;
	unsigned char Num	=	0;
	
	U5Time++;
	
	Num	=	UART5ReceiveData(&RecByte);			//串口5读数据,返回0-无中断，返回1有中断无数据（发送中断），返回2-有中断有接收到数据
	if(Num	==	2)
	{
		RxdBuffe[U5Num]	=	RecByte;
		U5Num++;
		U5Time	=	0;
	}
	
	if(U5Time>=2)	//接收超时
	{
		if(U5Num)
		{
			GPIO_SetBits(GPIOB,	GPIO_Pin_3);
			memcpy(RevBuffe,RxdBuffe,U5Num);
			USART_Send(UART5,RevBuffe,U5Num);
			memset(RevBuffe,0xFF,U5Num);			
		}
		GPIO_ResetBits(GPIOB,	GPIO_Pin_3);
		U5Time	=	0;
		U5Num		=	0;
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
void Switch_Configuration(void)
{
	SWITCHID.NumOfSW	=	6;
	
	SWITCHID.SW1_PORT	=	GPIOB;
	SWITCHID.SW1_Pin	=	GPIO_Pin_15;
	
	SWITCHID.SW2_PORT	=	GPIOC;
	SWITCHID.SW2_Pin	=	GPIO_Pin_6;
	
	SWITCHID.SW3_PORT	=	GPIOC;
	SWITCHID.SW3_Pin	=	GPIO_Pin_7;
	
	SWITCHID.SW4_PORT	=	GPIOC;
	SWITCHID.SW4_Pin	=	GPIO_Pin_8;
	
	SWITCHID.SW5_PORT	=	GPIOC;
	SWITCHID.SW5_Pin	=	GPIO_Pin_9;
	
	SWITCHID.SW6_PORT	=	GPIOA;
	SWITCHID.SW6_Pin	=	GPIO_Pin_8;
	
	SwitchIdInitialize(&SWITCHID);
	
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
void RS485_Configuration(void)
{
	//IN485,OUT485,PORT485A,PORT485B,PORT485C;
	
//	IN485.USARTx=UART5;
//	IN485.RS485_CTL_PORT=GPIOB;
//	IN485.RS485_CTL_Pin=GPIO_Pin_3;	
//	RS485_DMA_ConfigurationNR	(&IN485,19200,(u32*)RxdBuffe,8);	//USART_DMA配置--查询方式，不开中断,配置完默认为接收状态
	
	GPIO_Configuration_OPP50	(GPIOB,	GPIO_Pin_3);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605
	GPIO_ResetBits(GPIOB,	GPIO_Pin_3);
	USART_ConfigurationIT(UART5,19200,1,1);	//USART_配置---常规中断方式
	
	
	OUT485.USARTx=UART4;
	OUT485.RS485_CTL_PORT=GPIOA;
	OUT485.RS485_CTL_Pin=GPIO_Pin_15;	
	RS485_DMA_ConfigurationNR	(&OUT485,19200,8);	//USART_DMA配置--查询方式，不开中断,配置完默认为接收状态	
	
	
	PORT485A.USARTx=USART3;
	PORT485A.RS485_CTL_PORT=GPIOB;
	PORT485A.RS485_CTL_Pin=GPIO_Pin_1;	
	RS485_DMA_ConfigurationNR	(&PORT485A,19200,8);	//USART_DMA配置--查询方式，不开中断,配置完默认为接收状态
	
	PORT485B.USARTx=USART2;
	PORT485B.RS485_CTL_PORT=GPIOA;
	PORT485B.RS485_CTL_Pin=GPIO_Pin_1;	
	RS485_DMA_ConfigurationNR	(&PORT485B,19200,8);	//USART_DMA配置--查询方式，不开中断,配置完默认为接收状态
	
	PORT485C.USARTx=USART1;
	PORT485C.RS485_CTL_PORT=GPIOA;
	PORT485C.RS485_CTL_Pin=GPIO_Pin_11;	
	RS485_DMA_ConfigurationNR	(&PORT485C,19200,8);	//USART_DMA配置--查询方式，不开中断,配置完默认为接收状态
}
//================

#endif

