#ifdef CS5530_DEMO

#include "CS5530_DEMO.H"

#include "TM1616.H"
#include "CS5530.H"

#include "STM32_PWM.H"
#include "STM32_GPIO.H"
#include "STM32_SYS.H"
#include "STM32_WDG.H"
#include "STM32_SYSTICK.H"
#include "STM32_USART.H"
#include "STM32F10x_BitBand.H"


//#include "stdio.h"
//#include "stm32f10x_type.h"
//#include "STM32_SPI.H"
//#include "STM32_PWM.H"
//#include "STM32_ADC.H"
//#include "STM32_USART.H"
//#include "STM32F10x_BitBand.H"
//#include "STM32_SYSTICK.H"

//#include "STM32_SPI.H"

/******************************MX25L4006E命令定义*******************************/


//sbit stb=P3^4;		//片选，在上升或下降沿初始化串行接口，随后等待接收指令。
//									//STB为低后的第一个字节作为指令，当处理指令时，当前其它处
//									//理被终止。当STB 为高时，CLK 被忽略
////_________________________________________________________________________________________________
//sbit clk=P3^0;		//时钟上升沿输入串行数据。
////__________________________________________________________________________________________________
//sbit dio=P3^1;	  	//在时钟上升沿输入串行数据，从低位开始。


unsigned long weigth=0;		

TM1616Def	TM1616_1,TM1616_2;
CS5530Def	CS5530;


u16 us=0;

/*******************************************************************************
* 函数名		:	
* 功能描述	:	 
* 输入		:	
* 输出		:
* 返回 		:
*******************************************************************************/
void CS5530Demo_Configuration(void)
{	
	SYS_Configuration();					//系统配置---打开系统时钟 STM32_SYS.H
	
	GPIO_DeInitAll();							//将所有的GPIO关闭----V20170605
	
	TM1616_Configuration();
	
	CS5530_Configuration();
	
	SysTick_Configuration(1000);	//系统嘀嗒时钟配置72MHz,单位为uS
	
//	IWDG_Configuration(1000);			//独立看门狗配置---参数单位ms	
	
	PWM_OUT(TIM2,PWM_OUTChannel1,1,500);						//PWM设定-20161127版本
	
	USART_DMA_ConfigurationNR	(USART2,115200,32);	//USART_DMA配置--查询方式，不开中断
	
//	TM1616_WriteByte(&TM1616_1,5);
	

}
/*******************************************************************************
* 函数名		:	
* 功能描述	:	 
* 输入		:	
* 输出		:
* 返回 		:
*******************************************************************************/
void CS5530Demo_Server(void)
{
	IWDG_Feed();								//独立看门狗喂狗
	TM1616_DIS();
}
/*******************************************************************************
*函数名			:	function
*功能描述		:	函数功能说明
*输入				: 
*返回值			:	无
*******************************************************************************/
void TM1616_Configuration(void)
{
	TM1616_1.CLK_PORT=GPIOB;
	TM1616_1.CLK_Pin=GPIO_Pin_12;
	
	TM1616_1.DIO_PORT=GPIOB;
	TM1616_1.DIO_Pin=GPIO_Pin_13;	
	
	TM1616_1.STB_PORT=GPIOB;
	TM1616_1.STB_Pin=GPIO_Pin_11;
	
	TM1616_2.CLK_PORT=GPIOB;
	TM1616_2.CLK_Pin=GPIO_Pin_2;
	
	TM1616_2.DIO_PORT=GPIOB;
	TM1616_2.DIO_Pin=GPIO_Pin_10;	
	
	TM1616_2.STB_PORT=GPIOB;
	TM1616_2.STB_Pin=GPIO_Pin_1;
	
	TM1616_Initialize(&TM1616_1);
	TM1616_Initialize(&TM1616_2);
}
/*******************************************************************************
*函数名			:	function
*功能描述		:	函数功能说明
*输入				: 
*返回值			:	无
*******************************************************************************/
void CS5530_Configuration(void)
{
	CS5530.Port.CS_PORT		=	GPIOA;
	CS5530.Port.CS_Pin		=	GPIO_Pin_4;
	
	CS5530.Port.SCLK_PORT	=	GPIOA;
	CS5530.Port.SCLK_Pin	=	GPIO_Pin_7;
	
	CS5530.Port.SDI_PORT	=	GPIOA;
	CS5530.Port.SDI_Pin		=	GPIO_Pin_5;
	
	CS5530.Port.SDO_PORT	=	GPIOA;
	CS5530.Port.SDO_Pin		=	GPIO_Pin_6;
	
	CS5530_Initialize(&CS5530);
	
	
//	CS5530.Port.CS_PORT		=	GPIOB;
//	CS5530.Port.CS_Pin		=	GPIO_Pin_12;
//	
//	CS5530.Port.SCLK_PORT	=	GPIOB;
//	CS5530.Port.SCLK_Pin	=	GPIO_Pin_13;
//	
//	CS5530.Port.SDI_PORT	=	GPIOB;
//	CS5530.Port.SDI_Pin		=	GPIO_Pin_15;
//	
//	CS5530.Port.SDO_PORT	=	GPIOB;
//	CS5530.Port.SDO_Pin		=	GPIO_Pin_14;
//	
//	CS5530_Initialize(&CS5530);
}

/*******************************************************************************
*函数名			:	function
*功能描述		:	函数功能说明
*输入				: 
*返回值			:	无
*******************************************************************************/
void TM1616_DIS(void)
{
	if(us++>=10)
	{
		us=0;
//		CS5530_Process(&CS5530);
//		if(weigth++>=655360)
//		{
//			weigth=0;
//		}
		weigth	=	CS5530_ReadData(&CS5530);		//获取稳定的AD值
//		weigth	=	CS5530.Data.WeighLive;		//获取稳定的AD值
		if((0xFFFFFFFF	!=	weigth)&&(0	!=	weigth))
		{
			TM1616_Display(&TM1616_1,weigth/10000);
			TM1616_Display(&TM1616_2,weigth%10000);
			USART_DMAPrintf	(USART2,"CH1:%0.8X\r\n",weigth>>2);					//自定义printf串口DMA发送程序,后边的省略号就是可变参数
		}
	}
}


#endif


