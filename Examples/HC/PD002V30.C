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
#include "CS5530.H"
#include "74HC595.H"

#include "STM32F10x_BitBand.H"
#include "STM32_GPIO.H"
#include "STM32_SYS.H"
#include "STM32_SYSTICK.H"
#include "STM32_WDG.H"
#include "STM32_USART.H"
#include "STM32_PWM.H"

#include "string.h"				//串和内存操作函数头文件
#include "stm32f10x_dma.h"


#include "SWITCHID.H"
#include "AT24C02.H"


PD002V30Def sPD002V30;
#define BufferSize	12
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
u8 Bus485Rx[9]={0};
u8 Bus485Re[9]={0};
u8 Bus485Tx[9]={0};

u8 DebugRx[32]={0};
u8 DebugRe[32]={0};
u8 DebugTx[32]={0};


CS5530Def CS5530_1,CS5530_2,CS5530_3;
u32 Value_AD1=0;
u32 Value_AD2=0;

u32 Value_ADB1=0;
u32 Value_ADB2=0;

u8 swid=0;
u16 RunTime=0;
HC595_Pindef HC595_Conf;

u8 dnum1=1;
u8 dnum2=2;


sI2CDef sI2C;
unsigned char Tedata	=	0;
unsigned char Wedata	=	0;
unsigned char Buffer[16]={0};

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
	
	GPIO_Configuration_IPU	(GPIOA,GPIO_Pin_4);			//S1//将GPIO相应管脚配置为上拉输入模式----V20170605
	GPIO_Configuration_IPU	(GPIOA,GPIO_Pin_5);			//S2//将GPIO相应管脚配置为上拉输入模式----V20170605
	GPIO_Configuration_IPU	(GPIOA,GPIO_Pin_6);			//S3//将GPIO相应管脚配置为上拉输入模式----V20170605
	GPIO_Configuration_IPU	(GPIOA,GPIO_Pin_7);			//S4//将GPIO相应管脚配置为上拉输入模式----V20170605
	
	SwitchID_Configuration();
	
	Seg_Configuration();		//数码管接口配置
	
	SysTick_Configuration(1000);	//系统嘀嗒时钟配置72MHz,单位为uS
	
//	PWM_OUT(TIM2,PWM_OUTChannel1,1,700);						//PWM设定-20161127版本
	
	CS5530_Configuration();				//CS5530初始化
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
	
	IWDG_Feed();								//独立看门狗喂狗
	
	RunTime++;
	if(RunTime	==	100)
	{
//		AT24C02_Write(&sI2C,0x00,Wedata);	
//		Tedata	=	AT24C02_Read(&sI2C,0x00);
		Buffer[0]	=	0x01;
		Buffer[1]	=	0x02;
		Buffer[2]	=	0x03;
		Buffer[3]	=	0x04;
		Buffer[4]	=	0x05;
		Buffer[5]	=	0x06;
		Buffer[6]	=	0x07;
		Buffer[7]	=	0x08;
		Buffer[8]	=	0x09;
//			AT24C02_WritePage(&sI2C,0x03,Buffer);
	}
	if(RunTime	==	200)
	{
		Tedata	=	0;
//		Tedata	=	AT24C02_Read(&sI2C,0x00);
		memset(Buffer,0x55,10);
//		AT24C02_ReadBuffer(&sI2C,0x00,Buffer,8);
	}
	
	if(RunTime>=10)
	{
		dnum1++;
		dnum2++;
		if(dnum1>9)
			dnum1=0;
		if(dnum2>9)
			dnum2=0;
		
		RunTime=0;
		Seg_Server();					//数码更新接口
		CS5530_Server();			//读取AD值

		Wedata++;
		if(Wedata>=0xFF)
			Wedata	=	0;
		
	}
	
	SwitchID	=	SWITCHID_Read(&SWITCHID);		//
	
	PD002V30_USART_Server();
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
	sI2C.SDA_Port	=	GPIOB;
	sI2C.SDA_Pin	=	GPIO_Pin_7;
	
	sI2C.SCL_Port	=	GPIOB;
	sI2C.SCL_Pin	=	GPIO_Pin_6;
	
	I2C_Configuration(&sI2C);		//启用锁--配置
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
void AT24C02_Server(void)
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
	RS485_DMA_ConfigurationNR	(&BUS485,19200,(u32*)Bus485Rx,9);	//USART_DMA配置--查询方式，不开中断,配置完默认为接收状态
	
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
	u8 Num	=	0;
	Num	=	RS485_ReadBufferIDLE			(&BUS485,(u32*)Bus485Re,(u32*)Bus485Rx);	//串口空闲模式读串口接收缓冲区，如果有数据，将数据拷贝到RevBuffer,并返回接收到的数据个数，然后重新将接收缓冲区地址指向RxdBuffer
	if(Num>5)
	{
		Bus485Tx[0]	=	SwitchID;
		memcpy(&Bus485Tx[1],&Value_AD1,4);
		memcpy(&Bus485Tx[5],&Value_AD2,4);
		RS485_DMASend(&BUS485,(u32*)Bus485Tx,9);	//RS485-DMA发送程序
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
	CS5530_1.Port.CS_PORT=GPIOB;
	CS5530_1.Port.CS_Pin=GPIO_Pin_12;
	
	CS5530_1.Port.SDI_PORT=GPIOB;
	CS5530_1.Port.SDI_Pin=GPIO_Pin_15;
	
	CS5530_1.Port.SDO_PORT=GPIOB;
	CS5530_1.Port.SDO_Pin=GPIO_Pin_14;
	
	CS5530_1.Port.SCLK_PORT=GPIOB;
	CS5530_1.Port.SCLK_Pin=GPIO_Pin_13;
	
	
	
//	CS5530_2.Port.CS_PORT=GPIOA;
//	CS5530_2.Port.CS_Pin=GPIO_Pin_8;
//	
//	CS5530_2.Port.SDI_PORT=GPIOB;
//	CS5530_2.Port.SDI_Pin=GPIO_Pin_15;
//	
//	CS5530_2.Port.SDO_PORT=GPIOB;
//	CS5530_2.Port.SDO_Pin=GPIO_Pin_14;
//	
//	CS5530_2.Port.SCLK_PORT=GPIOB;
//	CS5530_2.Port.SCLK_Pin=GPIO_Pin_13;
	
	CS5530_Initialize(&CS5530_1);
//	CS5530_Initialize(&CS5530_2);
}
/*******************************************************************************
* 函数名			:	
* 功能描述		: CS5530初始化
* 输入			: void
* 返回值			: void
*******************************************************************************/
void CS5530_Server(void)
{
	u32 temp1=0,temp2=0;
	temp1	=	CS5530_ReadData(&CS5530_1);		//读取AD值，如果返回0xFFFFFFFF,则未读取到24位AD值
//	temp2	=	CS5530_ReadData(&CS5530_2);		//读取AD值，如果返回0xFFFFFFFF,则未读取到24位AD值
	
	if(temp1>Value_AD1)
	{
		Value_ADB1	=	temp1	-	Value_AD1;
	}
	else
	{
		Value_ADB1	=	Value_AD1	-	temp1;
	}
	
	if(temp2>Value_AD2)
	{
		Value_ADB2	=	temp2	-	Value_AD2;
	}
	else
	{
		Value_ADB2	=	Value_AD2	-	temp2;
	}
	if(temp1!=0xFFFFFFFF)
	{
		USART_DMAPrintf	(USART1,"CH1:%0.8X\r\n",temp1>>2);					//自定义printf串口DMA发送程序,后边的省略号就是可变参数
	}
	Value_AD1	=	temp1;
	Value_AD2	=	temp2;
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
