#ifdef AMP01

#include "AMP01.H"

#include "string.h"				//串和内存操作函数头文件
//#include "stm32f10x_dma.h"



#include "STM32F10x_BitBand.H"
#include "STM32_GPIO.H"
#include "STM32_SYS.H"
#include "STM32_SYSTICK.H"
#include "STM32_WDG.H"
#include "STM32_PWM.H"
#include "STM32_USART.H"

#include 	"CRC.H"


RS485Def stRS485BS;   //usart2,pa1
RS485Def stRS485SL;   //uart4,pc12


#define ussize  128     //串口缓存大小
unsigned char u1txbuffer[ussize];
unsigned char u1rxbuffer[ussize];
unsigned char u2txbuffer[ussize];
unsigned char u2rxbuffer[ussize];
unsigned char u4txbuffer[ussize];
unsigned char u4rxbuffer[ussize];

unsigned  short seril=0;
//=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>
//->函数名		:	
//->功能描述	:	 
//->输入		:	
//->输出		:
//->返回 		:
//<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=
void AMP01_Configuration(void)
{	
  RCC_ClocksTypeDef RCC_ClocksStatus;							//时钟状态---时钟值
	SYS_Configuration();					//系统配置---打开系统时钟 STM32_SYS.H	

  COMM_Configuration();  
  
	PWM_OUT(TIM2,PWM_OUTChannel1,1,300);						//PWM设定-20161127版本
	
//  IWDG_Configuration(1000);													//独立看门狗配置---参数单位ms
  SysTick_Configuration(1000);    //系统嘀嗒时钟配置72MHz,单位为uS
}

//=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>
//->函数名		:	
//->功能描述	:	 
//->输入		:	
//->输出		:
//->返回 		:
//<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=
void AMP01_Server(void)
{
  USART_Server();
}
//=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>
//->函数名		:	
//->功能描述	:	 
//->输入		:	
//->输出		:
//->返回 		:
//<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=
void USART_Server(void)
{
  unsigned short RxNum  = 0;
  unsigned char str[]="串口接收到数据\r\n";
  RxNum = USART_ReadBufferIDLE(USART1,u1rxbuffer);
  if(RxNum)
  {
    memcpy(u1txbuffer,str,sizeof(str));
    memcpy(u2txbuffer,u1rxbuffer,RxNum);
    memcpy(u4txbuffer,u1rxbuffer,RxNum);
    
    USART_DMASend(USART1,u1txbuffer,sizeof(str)-1);		//串口DMA发送程序，如果数据已经传入到DMA，返回Buffer大小，否则返回0
    
    RS485_DMASend(&stRS485BS,u2txbuffer,RxNum);
    RS485_DMASend(&stRS485SL,u4txbuffer,RxNum);
  }
  RxNum = RS485_ReadBufferIDLE(&stRS485BS,u2rxbuffer);
  if(RxNum)
  {
    memcpy(u1txbuffer,u2rxbuffer,RxNum);
    USART_DMASend(USART1,u1txbuffer,RxNum);
  }
  RxNum = RS485_ReadBufferIDLE(&stRS485SL,u4rxbuffer);
  if(RxNum)
  {
    memcpy(u1txbuffer,u4rxbuffer,RxNum);
    USART_DMASend(USART1,u1txbuffer,RxNum);
  }
}
//=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>
//->函数名		:	
//->功能描述	:	 
//->输入		:	
//->输出		:
//->返回 		:
//<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=
void COMM_Configuration(void)
{
  unsigned short RxNum  = 0;
  USART_DMA_ConfigurationNR	(USART1,115200,ussize);	//USART_DMA配置--查询方式，不开中断

  //-----------------------------总线接口485
  stRS485BS.USARTx  = USART2;
  stRS485BS.RS485_CTL_PORT  = GPIOA;
  stRS485BS.RS485_CTL_Pin   = GPIO_Pin_1;
  RS485_DMA_ConfigurationNR			(&stRS485BS,115200,ussize);	//USART_DMA配置--查询方式，不开中断,配置完默认为接收状态
  //-----------------------------从机接口485
  stRS485SL.USARTx  = UART4;
  stRS485SL.RS485_CTL_PORT  = GPIOC;
  stRS485SL.RS485_CTL_Pin   = GPIO_Pin_12;
  RS485_DMA_ConfigurationNR			(&stRS485SL,115200,ussize);	//USART_DMA配置--查询方式，不开中断,配置完默认为接收状态
}
#endif
