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

#ifdef PS005V10				//智能药架称重LCD板---单称重

#include "PS005V10.H"

#include "STM32F10x_BitBand.H"
#include "STM32_GPIO.H"
#include "STM32_SYS.H"
#include "STM32_SYSTICK.H"
#include "STM32_WDG.H"
#include "STM32_PWM.H"
#include "STM32_USART.H"
#include "STM32_ADC.H"
#include "STM32_SPI.H"
#include "74HC595.H"
#include "CD4051.H"
#include "STM32_ADC.H"
#include "STM32_MCO.H"

#include "string.h"				//串和内存操作函数头文件
#include "stdlib.h"				//串和内存操作函数头文件
#include "stm32f10x_dma.h"

SPIDef stHC595SPI;
stCD4051Def	stCD4051H,stCD4051L;

unsigned	char	DspData	=	0;
unsigned  char  x,y;
unsigned	char DspBuffer[10]	=	{0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
unsigned  short adcdata = 0;
unsigned  short time= 0;
/*******************************************************************************
* 函数名		:	
* 功能描述	:	 
* 输入		:	
* 输出		:
* 返回 		:
*******************************************************************************/
void PS005V10_Configuration(void)
{
	SYS_Configuration();					//系统配置---打开系统时钟 STM32_SYS.H
	
	GPIO_DeInitAll();							//将所有的GPIO关闭----V20170605	
	
	RS485_Configuration();
	
//	DS18B20_Server();
	
	USART_Configuration();
	
	SysTick_DeleymS(500);				//SysTick延时nmS

	HC595_Configuration();
	
	CD4051_Configuration();	
	
	SysTick_Configuration(200);	//系统嘀嗒时钟配置72MHz,单位为uS
	
  ADC1_DiscConfigurationDMANR(1,ADC_Channel_8,ADC_SampleTime_7Cycles5);

	PWM_OUT(TIM2,PWM_OUTChannel1,4800000,500);	//PWM设定-20161127版本--运行指示灯
	
	PWM_OUT(TIM4,PWM_OUTChannel4,5000,990);	//PWM设定-20161127版本--运行指示灯
	
//	MCO_Initialize();
	
//	PWM_OUT(TIM1,PWM_OUTChannel1,2,500);	//PWM设定-20161127版本--运行指示灯
}
/*******************************************************************************
* 函数名		:	
* 功能描述	:	 
* 输入		:	
* 输出		:
* 返回 		:
*******************************************************************************/
void PS005V10_Server(void)
{	
  static char i=0;
//	DspData++;
//	DspData	=	0;
  
  if(i++>=3)
    i=0;
//  DspBuffer[0]  = DspData;
  SensorServer();
	HC595_Write(&DspBuffer[i],i);
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
void HC595_Configuration(void)
{
	stHC595SPI.Port.SPIx	=	SPI2;
	stHC595SPI.Port.CS_PORT	=	GPIOB;
	stHC595SPI.Port.CS_Pin		=	GPIO_Pin_12;
	stHC595SPI.Port.SPI_BaudRatePrescaler_x	=	SPI_BaudRatePrescaler_2;
	SPI_Initialize(&stHC595SPI);
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
void HC595_Write(unsigned	char* Buffer,unsigned	char len)
{
	unsigned char datah,datal;
	unsigned	char i=0;
	//--------------------------SPI驱动
	SPI_CS_LOW(&stHC595SPI);
//	for(i=0;i<len;i++)
//	{
		datah	=	Buffer[i];
		datal	=	datah^0xFF;
    datal	=	0xFF^(0x01<<len);
		SPI_ReadWriteByteSPI(&stHC595SPI,datah);
		SPI_ReadWriteByteSPI(&stHC595SPI,datal);
//	}
	SPI_CS_HIGH(&stHC595SPI);
	return;
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
void CD4051_Configuration(void)
{
	stCD4051H.Port.C_PORT	=	GPIOA;
	stCD4051H.Port.C_Pin	=	GPIO_Pin_15;
	
	stCD4051H.Port.B_PORT	=	GPIOB;
	stCD4051H.Port.B_Pin	=	GPIO_Pin_3;
	
	stCD4051H.Port.A_PORT	=	GPIOB;
	stCD4051H.Port.A_Pin	=	GPIO_Pin_4;
	
	stCD4051H.Port.EN_PORT	=	GPIOB;
	stCD4051H.Port.EN_Pin		=	GPIO_Pin_8;
	
	stCD4051L.Port.A_PORT		=	GPIOB;
	stCD4051L.Port.A_Pin		=	GPIO_Pin_5;
	
	stCD4051L.Port.B_PORT		=	GPIOB;
	stCD4051L.Port.B_Pin		=	GPIO_Pin_7;
	
	stCD4051L.Port.C_PORT		=	GPIOB;
	stCD4051L.Port.C_Pin		=	GPIO_Pin_6;
	
	stCD4051L.Port.EN_PORT	=	GPIOB;
	stCD4051L.Port.EN_Pin		=	GPIO_Pin_8;
	
	CD4051_Initialize(&stCD4051H);
	CD4051_Initialize(&stCD4051L);
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
void CD4051_SetSensor(unsigned	char x,unsigned char y)
{
	GPIO_SetBits(stCD4051H.Port.EN_PORT, stCD4051H.Port.EN_Pin);			//A/A0
	CD4051_WriteChannel(&stCD4051H,x);
	CD4051_WriteChannel(&stCD4051L,y);
	GPIO_ResetBits(stCD4051H.Port.EN_PORT, stCD4051H.Port.EN_Pin);			//A/A0
}
/*******************************************************************************
* 函数名			:	RS485_Server
* 功能描述		:	数据收发--获取AD值命令:FA F5 ID 01 ,上报数据格式：FB F6 ID B1 B2 B3 高位在前
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
void RS485_Server(void)			//通讯管理---负责信息的接收与发送
{
}
/*******************************************************************************
*函数名			:	function
*功能描述		:	function
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
void SensorServer(void)
{
  if(time++>10)
  {
    time  = 0;
    ADC1_DiscGetData(&adcdata);
    if(adcdata<0x0D40)
    {
      DspBuffer[y]|=0x01<<x;
    }
    else
    {
      
      DspBuffer[y]&=0xFF^(0x01<<x);
    }
    if(x++>=7)
    {
      x=0;
      if(y++>=3)
        y=0;
    }
    CD4051_SetSensor(x,y);
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
void RS485_Configuration(void)
{
//	RS485.USARTx=USART1;
//	RS485.RS485_CTL_PORT=GPIOA;
//	RS485.RS485_CTL_Pin=GPIO_Pin_11;
//	
//	RS485_DMA_ConfigurationNR	(&RS485,115200,Rs485Size);	//USART_DMA配置--查询方式，不开中断,配置完默认为接收状态
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
void USART_Configuration(void)
{
//	//1.6版本为USART1
//	USART_DMA_ConfigurationNR	(USART1,115200,Rs485Size);	//USART_DMA配置--查询方式，不开中断
	//1.7版本为UART4
//	USART_DMA_ConfigurationNR	(UART4,115200,10);	//USART_DMA配置--查询方式，不开中断
}



#endif
