#ifdef SPItoUSART

#include "SPItoUSART.H"
#include "stm32f10x_exti.h"


#include "STM32_SPI.H"
#include "STM32_PWM.H"
#include "STM32_GPIO.H"
#include "STM32_SYS.H"
#include "STM32_WDG.H"
#include "STM32_SYSTICK.H"
#include "STM32F10x_BitBand.H"


u8 ch[120]="USART_BASIC_Configuration(USART_TypeDef* USARTx,u32 USART_BaudRate,u8 NVICPreemptionPriority,u8 NVIC_SubPriority)\n";
u8 ch2[17]={0xC0,0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71};
u8 ch3[17]={0xC0,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
u8 ch4[17]={0xC0};

u32	SYSTIME	=	0;
u32	DATA	=	0;

//u8 itf=0;
/*******************************************************************************
* 函数名		:	
* 功能描述	:	 
* 输入		:	
* 输出		:
* 返回 		:
*******************************************************************************/
void SPItoUSART_Configuration(void)
{
	SYS_Configuration();					//系统配置---打开系统时钟 STM32_SYS.H
	
	GPIO_DeInitAll();							//将所有的GPIO关闭----V20170605
	
	SysTick_Configuration(1000);	//系统嘀嗒时钟配置72MHz,单位为uS
	
	PWM_OUT(TIM2,PWM_OUTChannel1,1,500);

//	GPIO_Configuration(GPIOB,GPIO_Pin_4,GPIO_Mode_Out_PP,GPIO_Speed_50MHz);			//GPIO配置
	
	
//	PWM_Configuration(TIM2,7200,10000,50);

//	USART_DMA_Configuration(USART1,115200,1,1,(u32*)Usart_Test_Buffer,(u32*)Usart_Test_Buffer,DMA1_BufferSize);	//USART_DMA配置

	STM32_SPI_ConfigurationNR(SPI2);
//	SPI_DMA_Configuration(SPI2,&SPI_InitStructure,(u32*)SPI_Buffer,(u32*)SPI_Buffer,SPI_BUFFERSIZE);		//SPI_DMA配置

	

//	PWM_Configuration(TIM2,7200,200,20);
	STM32_SPI_ReadWriteData(SPI2,0x8F);
	STM32_SPI_ReadWriteData(SPI2,0x40);
//	STM32_SPI_ReadWriteData(SPI1,0xC0);
	
	ch3[0]=0xC0;
	ch4[0]=0xC0;

}
/*******************************************************************************
* 函数名		:	
* 功能描述	:	 
* 输入		:	
* 输出		:
* 返回 		:
*******************************************************************************/
void SPItoUSART_Server(void)
{
	SYSTIME++;
	if(SYSTIME>=100)
	{
		SYSTIME	=	0;
		DATA++;
		if(DATA>9999)
			DATA	=0;
		STM32_SPI_ReadWriteData(SPI2,0x40);
		
		ch4[1]=ch2[DATA/1000+1];
		ch4[3]=ch2[DATA%1000/100+1];
		ch4[5]=ch2[DATA%100/10+1];
		ch4[7]=ch2[DATA%10+1];
		
//		STM32_SPI_ReadWriteData(SPI2,0x8F);
//		STM32_SPI_ReadWriteData(SPI2,0x40);
		STM32_SPI_SendBuffer(SPI2,8,ch4);
	}
	
//	if(SYSTIME	==	0)
//	{
//		STM32_SPI_SendBuffer(SPI1,120,ch);
//	}
	
//	STM32_SPI_ReadWriteData(SPI2,0x8F);
//	STM32_SPI_ReadWriteData(SPI2,0x40);
//	STM32_SPI_SendBuffer(SPI2,4,ch3);
	
//	if(SYSTIME%3	==	0)
//	{
//		STM32_SPI_SendBuffer(SPI2,8,ch2);
//	}
//	else if(SYSTIME%3	==	1)
//	{
//		STM32_SPI_SendBuffer(SPI2,8,ch3);
//	}
//	else if(SYSTIME%3	==	2)
//	{
//		STM32_SPI_SendBuffer(SPI2,8,ch4);
//	}

}


#endif

