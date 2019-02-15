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

#ifdef PD002V30ADC				//称重托盘控制器---盒剂测距应用


#include "PD002V30ADC.H"


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


#define BusSize			12	//协议指令数据大小
#define Bus485Size	64


u8 SwitchID=0;	//拔码开关地址

#define RS485_PD_RXEN		PA1=0				//rs485接收称重板使能
#define RS485_PD_TXEN		PA1=1				//rs485发送称重板使能

unsigned	char ADCCH1SS3EN,ADCCH2SS4EN;   //通道选择标志
unsigned  char DataOutStrEn;              //数据输出标志，SW3为0输出十六进制，为1输出字符串
unsigned  char DataOutMMEn;               //数据输出类型，SW4为0输出原始数据，为1输出转换后的mm单位数据，16进制格式

unsigned  char Txbuffer[32]={0};

unsigned	short SYSLEDTime;
unsigned	short SwitchTime=0;
//void TEMPdelay(u32 time);
/*******************************************************************************
* 函数名		:	
* 功能描述	:	 
* 输入		:	
* 输出		:
* 返回 		:
*******************************************************************************/
void PD002V30ADC_Configuration(void)
{
	SYS_Configuration();					//系统配置---打开系统时钟 STM32_SYS.H
	
	GPIO_DeInitAll();							//将所有的GPIO关闭----V20170605	
	
	GPIO_Configuration_OPP2	(GPIOC,GPIO_Pin_1);			//BUZZER//将GPIO相应管脚配置为OD(开漏)输出模式，最大速度2MHz----V20170605
	
	SwitchID_Configuration();	

	CS5530_Configuration();					//CS5530初始化	
	
	PD002V30_USART_Cofiguration();
	
//	PWM_OUT(TIM2,PWM_OUTChannel1,2,500);						//PWM设定-20161127版本
	
	GPIO_Configuration_OPP50	(GPIOA,GPIO_Pin_0);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605
	
//	IWDG_Configuration(1000);			//独立看门狗配置---参数单位ms	
	
	SysTick_Configuration(1000);	//系统嘀嗒时钟配置72MHz,单位为uS
}
/*******************************************************************************
* 函数名		:	
* 功能描述	:	 
* 输入		:	
* 输出		:
* 返回 		:
*******************************************************************************/
void PD002V30ADC_Server(void)
{	
	USARTStatusDef	USARTStatus;
	
	IWDG_Feed();		//独立看门狗喂狗
	
	
	CS5530_Server();			//读取AD值

	if(SYSLEDTime++>500)			//运行LED灯
	{
		SYSLEDTime=0;
		GPIO_Toggle	(GPIOA,GPIO_Pin_0);		//将GPIO相应管脚输出翻转----V20170605
		
	}
	
	USARTStatus	=	USART_Status(MS200.BUS485.USARTx);		//串口状态检查
	if(0	==	USARTStatus.USART_IDLESTD)
	{
		RS485_PD_RXEN;
	}	
  

	if(SwitchTime++<1000)   //1秒查检一次拨码开关
  {
    return;
  }
  SwitchTime=0;
  
	SwitchID	=	SWITCHID_Read(&MS200.SWITCHID);
	{
		ADCCH1SS3EN	=	0;
		ADCCH2SS4EN	=	0;
    DataOutStrEn  = 0;
    DataOutMMEn = 0;
		//------------------未拨码，默认开启用双通道
		if(0	==	(SwitchID&0x03))
		{
			ADCCH1SS3EN	=	1;
			ADCCH2SS4EN	=	1;
		}
		//------------------拨码SW1，开启CH1SS3通道
		else if(1	==	(SwitchID&0x03))
		{
			ADCCH1SS3EN	=	1;
			ADCCH2SS4EN	=	0;
		}
		//------------------拨码SW2，开启CH2SS4通道
		else if(2	==	(SwitchID&0x03))
		{
			ADCCH1SS3EN	=	0;
			ADCCH2SS4EN	=	1;
		}
		//------------------拨码SW1，SW2，开启用双通道
		else if(3	==	(SwitchID&0x03))
		{
			ADCCH1SS3EN	=	1;
			ADCCH2SS4EN	=	1;
		}

    if(4  == (SwitchID&0x04))
    {
      DataOutStrEn  = 1;    //输出字符串16进制格式
    }
    else
    {
      DataOutStrEn  = 0;    //输出16进制
    }
    if(8  == (SwitchID&0x08))
    {
      DataOutMMEn  = 1;    //转换为mm输出
    }
    else
    {
      DataOutMMEn  = 0;    //输出原始AD值
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
	SwitchDef	*pInfo	=	&MS200.SWITCHID;
	
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
	RS485Def	*RS485	=	&MS200.BUS485;
	RS485->USARTx	=	USART2;
	RS485->RS485_CTL_PORT	=	GPIOA;
	RS485->RS485_CTL_Pin	=	GPIO_Pin_1;
	RS485_DMA_ConfigurationNR	(RS485,19200,Bus485Size);	//USART_DMA配置--查询方式，不开中断,配置完默认为接收状态	
	USART_DMA_ConfigurationNR	(USART1,115200,64);	//USART_DMA配置--查询方式，不开中断
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
  unsigned  long Ch1Data  = 0,Ch2Data=  0;
  unsigned  short TxNum = 0;
//  unsigned  char buffer[32]="CH1:";
  
  
  
  
	CS5530_Process(&MS200.CH1SS3.ADC);		//SS3接口，外面
	CS5530_Process(&MS200.CH2SS4.ADC);		//SS4接口，里面
	
  Ch1Data = MS200.CH1SS3.ADC.Data.WeighLive;    //通道1AD值
  Ch2Data = MS200.CH2SS4.ADC.Data.WeighLive;    //通道2AD值
  
//  Ch1Data = MS200.CH1SS3.ADC.Data.WeighFilt;    //通道1AD值--经过滤波
//  Ch2Data = MS200.CH2SS4.ADC.Data.WeighFilt;    //通道2AD值--经过滤波
  
  //---------------------------通道1输出
  if(ADCCH1SS3EN)
  {
    if((Ch1Data	!=0xFFFFFFFF)&&(Ch1Data	!=0x00))
    {
      if(DataOutStrEn)  //输出字符串
      {
        //-----------------转换数据为mm
        if(DataOutMMEn)
        {
          unsigned short temp = 0x1370;   //距离过短无法识别初始值
          if(Ch1Data>temp)
            Ch1Data =  Ch1Data-temp;
          else
            Ch1Data = 0;
          Ch1Data = Ch1Data/35;   //距离参数
          
          TxNum = RS485_DMAPrintf	(&MS200.BUS485,"CH1:%0.6dmm\r\n",Ch1Data);					//自定义printf串口DMA发送程序,后边的省略号就是可变参数
        }
        else
        {
          TxNum = RS485_DMAPrintf	(&MS200.BUS485,"CH1:%0.8X\r\n",Ch1Data);					//自定义printf串口DMA发送程序,后边的省略号就是可变参数
        }        
      }
      else
      {
        //-----------------转换数据为mm
        if(DataOutMMEn)
        {
          Ch1Data = (Ch1Data-300)/50;
        }
        //--------输出数据格式：43 48 31 xx xx xx xx 0D 0A   //数据内容低字节在前
        Txbuffer[0]='C';
        Txbuffer[1]='H';
        Txbuffer[2]='1';
        memcpy(&Txbuffer[3],&Ch1Data,4);
        Txbuffer[7] = '\r';
        Txbuffer[8] = '\n';
        TxNum = RS485_DMASend(&MS200.BUS485,Txbuffer,9);
      }
    }
    if(0  !=  TxNum)
      return;
    MS200.CH1SS3.ADC.Data.WeighLive	=	0;
    MS200.CH1SS3.ADC.Data.WeighFilt	=	0;
//    return;
  }
  //---------------------------通道2输出
  if(ADCCH2SS4EN)
  {
    if((Ch2Data	!=0xFFFFFFFF)&&(Ch2Data	!=0x00))
    {     
      if(DataOutStrEn)  //输出字符串
      {
        //-----------------转换数据为mm
        if(DataOutMMEn)
        {
          unsigned short temp = 0x1500;   //距离过短无法识别初始值
          if(Ch2Data>temp)
            Ch2Data =  Ch2Data-temp;
          else
            Ch2Data = 0;
          Ch2Data = Ch2Data/35;   //距离参数

          TxNum = RS485_DMAPrintf	(&MS200.BUS485,"CH2:%0.6dmm\r\n",Ch2Data);					//自定义printf串口DMA发送程序,后边的省略号就是可变参数
        }
        else
        {
          TxNum = RS485_DMAPrintf	(&MS200.BUS485,"CH2:%0.8X\r\n",Ch2Data);					//自定义printf串口DMA发送程序,后边的省略号就是可变参数
        }
      }
        
      else
      {
        //-----------------转换数据为mm
        if(DataOutMMEn)
        {
          unsigned short temp = 0x9F;   //距离过短无法识别初始值
          if(Ch2Data>temp)
            Ch2Data =  Ch2Data-temp;
          else
            Ch2Data = 0;
          Ch2Data = Ch2Data/33;   //距离参数
        }
        //--------输出数据格式：43 48 32 xx xx xx xx 0D 0A   //数据内容低字节在前
        Txbuffer[0]='C';
        Txbuffer[1]='H';
        Txbuffer[2]='2';
        memcpy(&Txbuffer[3],&Ch2Data,4);
        Txbuffer[7] = '\r';
        Txbuffer[8] = '\n';
        TxNum = RS485_DMASend(&MS200.BUS485,Txbuffer,9);
      }
    }
    if(0  !=  TxNum)
      return;
    MS200.CH2SS4.ADC.Data.WeighLive	=	0;
    MS200.CH2SS4.ADC.Data.WeighFilt	=	0;
  }  
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
