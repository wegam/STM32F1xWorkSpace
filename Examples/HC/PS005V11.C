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

#ifdef PS005V11				//智能药架称重LCD板---单称重

#include "PS005V11.H"

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

SPIDef stHC595Led;
SPIDef stHC595Sensor;
stCD4051Def	stCD4051H,stCD4051L;

unsigned	char	DspData	=	0;
unsigned  char  x,y;
unsigned	char DspBuffer[10]	=	{0x07,0xE0,0x0F,0xF0,0xFF,0xFF};
unsigned  short adcdata = 0;
unsigned  short time= 0;
unsigned	long*	pD	=	NULL;
void LEDTEST(void);
/*******************************************************************************
* 函数名		:	
* 功能描述	:	 
* 输入		:	
* 输出		:
* 返回 		:
*******************************************************************************/
void PS005V11_Configuration(void)
{
	SYS_Configuration();					//系统配置---打开系统时钟 STM32_SYS.H
	
	GPIO_DeInitAll();							//将所有的GPIO关闭----V20170605	
	
	RS485_Configuration();
	
//	DS18B20_Server();
	
	USART_Configuration();
	
	SysTick_DeleymS(500);				//SysTick延时nmS

	HC595_Configuration();
	
	CD4051_Configuration();	
	
	pD	=	(unsigned	long*)DspBuffer;
	*pD=0;
	
	SysTick_Configuration(1000);	//系统嘀嗒时钟配置72MHz,单位为uS
	
  ADC1_DiscConfigurationDMANR(1,ADC_Channel_8,ADC_SampleTime_7Cycles5);

	PWM_OUT(TIM2,PWM_OUTChannel1,2,500);	//PWM设定-20161127版本--运行指示灯
	
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
void PS005V11_Server(void)
{	
  static unsigned char i=0;

	
//	DspData++;
//	DspData	=	0;
 


		//LEDTEST();

//  DspBuffer[0]  = DspData;
  //SensorServer();
	LED_Write();
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
	stHC595Led.Port.SPIx	=	SPI1;
	stHC595Led.Port.CS_PORT	=	GPIOA;
	stHC595Led.Port.CS_Pin		=	GPIO_Pin_4;
	stHC595Led.Port.SPI_BaudRatePrescaler_x	=	SPI_BaudRatePrescaler_32;
	SPI_Initialize(&stHC595Led);
	
	//SPI_InitializeDMA(&stHC595Led);
	
	GPIO_Configuration_OPP50	(GPIOA,GPIO_Pin_4);					//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605
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
void LED_Write(void)
{
	unsigned char datah,datal;
	static unsigned	char line=0;
	if(line++>=3)
	{
		line=0;
		*pD+=1;
	}
	SPI_CS_LOW(&stHC595Led);
	//--------------------------SPI驱动
		datah	=	DspBuffer[line];
		datal	=	0xFF^(0x01<<line);		//行选择

		SPI_ReadWriteByteSPI(&stHC595Led,datah);
		SPI_ReadWriteByteSPI(&stHC595Led,datal);

	SPI_CS_HIGH(&stHC595Led);
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
void LEDTEST(void)
{
	static unsigned	char dspdata=0;
	unsigned	char	dspdatal=0;
	dspdata	=	0xFF;
	dspdatal	=	dspdata^0xFF;
	
	SPI_CS_LOW(&stHC595Led);
	SPI_ReadWriteByteSPI(&stHC595Led,dspdata);
	SPI_ReadWriteByteSPI(&stHC595Led,dspdatal);
	SPI_CS_HIGH(&stHC595Led);

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
