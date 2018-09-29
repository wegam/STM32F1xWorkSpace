#ifdef PC016V20Com				//单元控制板

#include "PC016V20Com.H"


#include "STM32_SYS.H"
#include "STM32_SYSTICK.H"
#include "STM32_WDG.H"
#include "STM32_PWM.H"


#include "STM32_CAN.H"
#include "STM32_USART.H"



#include "string.h"				//串和内存操作函数头文件

u8 Us1TTLrxbuff[128]={0};
u8 Us1TTLtxbuff[128]={0};

u8 Us3J1rxbuff[128]={0};
u8 Us3J1txbuff[128]={0};

u8 Us4J3rxbuff[128]={0};
u8 Us4J3txbuff[128]={0};

/*******************************************************************************
* 函数名		:	
* 功能描述	:	 
* 输入		:	
* 输出		:
* 返回 		:
*******************************************************************************/
void PC016V20Com_Configuration(void)
{
	
	SYS_Configuration();							//系统配置---打开系统时钟 STM32_SYS.H	
	GPIO_DeInitAll();									//将所有的GPIO关闭----V20170605
	

	USART_DMA_ConfigurationNR	(USART1,19200,128);	//USART_DMA配置--查询方式，不开中断
	USART_DMA_ConfigurationNR	(USART3,19200,128);	//USART_DMA配置--查询方式，不开中断
	USART_DMA_ConfigurationNR	(UART4,19200,128);	//USART_DMA配置--查询方式，不开中断
	
	PWM_OUT(TIM2,PWM_OUTChannel1,1,500);	//PWM设定-20161127版本

	IWDG_Configuration(2000);	//独立看门狗配置	Tout-超时复位时间，单位ms
	
	SysTick_Configuration(1000);					//系统嘀嗒时钟配置72MHz,单位为uS
	
}
/*******************************************************************************
* 函数名		:	
* 功能描述	:	 
* 输入		:	
* 输出		:
* 返回 		:
*******************************************************************************/
void PC016V20Com_Server(void)
{
//  u8 *buffer;
	unsigned short length;
	
	IWDG_Feed();								//独立看门狗喂狗
	
	length	=	USART_ReadBufferIDLE	(USART3,Us3J1rxbuff);	//串口空闲模式读串口接收缓冲区，如果有数据，将数据拷贝到RevBuffer,并返回接收到的数据个数
	if(length)
	{
		Us1TTLtxbuff[0]=0x01;
		memcpy(&Us1TTLtxbuff[1],Us3J1rxbuff,length);
		USART_DMASendList(USART1,Us1TTLtxbuff,length+1);		//串口DMA链表发送程序，如果数据已经传入到DMA，返回Buffer大小，否则数据存入链表
	}
	
	
	length	=	USART_ReadBufferIDLE	(UART4,Us4J3rxbuff);	//串口空闲模式读串口接收缓冲区，如果有数据，将数据拷贝到RevBuffer,并返回接收到的数据个数
	if(length)
	{
		Us1TTLtxbuff[0]=0x03;
		memcpy(&Us1TTLtxbuff[1],Us4J3rxbuff,length);
		USART_DMASendList(USART1,Us1TTLtxbuff,length+1);		//串口DMA链表发送程序，如果数据已经传入到DMA，返回Buffer大小，否则数据存入链表
	}
	
	
	length	=	USART_ReadBufferIDLE	(USART1,Us1TTLrxbuff);	//串口空闲模式读串口接收缓冲区，如果有数据，将数据拷贝到RevBuffer,并返回接收到的数据个数
	if(length)
	{
		if(Us1TTLrxbuff[0]==0x01)
		{
			memcpy(Us3J1txbuff,&Us1TTLrxbuff[1],length-1);
			USART_DMASendList(USART3,Us3J1txbuff,length-1);		//串口DMA链表发送程序，如果数据已经传入到DMA，返回Buffer大小，否则数据存入链表
		}
		else if(Us1TTLrxbuff[0]==0x03)
		{
			memcpy(Us4J3txbuff,&Us1TTLrxbuff[1],length-1);
			USART_DMASendList(UART4,Us4J3txbuff,length-1);		//串口DMA链表发送程序，如果数据已经传入到DMA，返回Buffer大小，否则数据存入链表
		}
	}
	

}

#endif
