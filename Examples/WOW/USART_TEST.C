#ifdef USART_TEST

#include "USART_TEST.H"

#include "STM32_USART.H"
#include "STM32_DMA.H"
#include "STM32_TIM.H"
#include "STM32_WDG.H"
#include "STM32_PWM.H"
#include "STM32_GPIO.H"
#include "STM32_SYS.H"
#include "STM32_SYSTICK.H"


#include	"stdio.h"			//用于printf
#include	"string.h"		//用于printf
#include	"stdarg.h"		//用于获取不确定个数的参数
#include	"stdlib.h"		//malloc动态申请内存空间


#define	BufferSize 1000		//DMA1缓冲大小

u32	num_temp=0;
u16	tema=0;

u32 DMASTAST=0;
ErrorStatus status = ERROR;

u8	txflg1=0;	//USART1发送标志
u16	tx1_tcont=0;	//USART1发送超时-计时

u8 rxBuffer1[BufferSize]={0};
u8 txBuffer1[BufferSize]={0};
u8 num=0;
u8 ch[512]="USART_BASIC_Configuration(USART_TypeDef* USARTx,u32 USART_BaudRate,u8 NVICPreemptionPriority,u8 NVIC_SubPriority)\n";

//u8 itf=0;
/*******************************************************************************
* 函数名		:	
* 功能描述	:	 
* 输入		:	
* 输出		:
* 返回 		:
*******************************************************************************/
void Usart_test_Configuration(void)
{
	SYS_Configuration();					//系统配置---打开系统时钟 STM32_SYS.H
	
	GPIO_DeInitAll();							//将所有的GPIO关闭----V20170605
	
	PWM_OUT(TIM2,PWM_OUTChannel1,1,900);						//PWM设定-20161127版本	
	
	USART_DMA_ConfigurationNR	(USART2,115200,BufferSize);	//USART_DMA配置--查询方式，不开中断
  
//  IWDG_Configuration(1000);			//独立看门狗配置---参数单位ms	
  
  SysTick_Configuration(1000);	//系统嘀嗒时钟配置72MHz,单位为uS
}
/*******************************************************************************
* 函数名		:	
* 功能描述	:	 
* 输入		:	
* 输出		:
* 返回 		:
*******************************************************************************/
void Usart_test_Server(void)
{	
	u16 Length	=	0;
	
	IWDG_Feed();								//独立看门狗喂狗
  USART_Status(USART2);		//串口状态检查
	Length	=	USART_ReadBufferIDLE	(USART2,rxBuffer1);	//串口空闲模式读串口接收缓冲区，如果有数据，将数据拷贝到RevBuffer,并返回接收到的数据个数
	if(Length)
	{
    memcpy(ch,rxBuffer1,Length);
    USART_DMASend			(USART2,ch,Length);	//串口DMA发送程序
//		memset(rxBuffer1,0xFF,Length);
	}
	tx1_tcont++;
	if(tx1_tcont>=100)
  {
		tx1_tcont=0;
    ch[0]  = 0;
//    USART_DMASend			(USART2,ch,16);	//串口DMA发送程序
    ch[0]  += 1;
    USART_DMAPrintf		(USART2,"%3d自定义printf串口DMA发送程序,后边的省略号就是可变参数\r\n",ch[0]);					//自定义printf串口DMA发送程序,后边的省略号就是可变参数
    ch[0]  += 1;
    USART_DMAPrintf		(USART2,"%3d自定义printf串口DMA发送程序,后边的省略号就是可变参数\r\n",ch[0]);					//自定义printf串口DMA发送程序,后边的省略号就是可变参数
    ch[0]  += 1;
    USART_DMAPrintf		(USART2,"%3d自定义printf串口DMA发送程序,后边的省略号就是可变参数\r\n",ch[0]);					//自定义printf串口DMA发送程序,后边的省略号就是可变参数
    ch[0]  += 1;
    USART_DMAPrintf		(USART2,"%3d自定义printf串口DMA发送程序,后边的省略号就是可变参数\r\n",ch[0]);					//自定义printf串口DMA发送程序,后边的省略号就是可变参数
    ch[0]  += 1;
    USART_DMAPrintf		(USART2,"%3d自定义printf串口DMA发送程序,后边的省略号就是可变参数\r\n",ch[0]);					//自定义printf串口DMA发送程序,后边的省略号就是可变参数
    ch[0]  += 1;
    USART_DMAPrintf		(USART2,"%3d自定义printf串口DMA发送程序,后边的省略号就是可变参数\r\n",ch[0]);					//自定义printf串口DMA发送程序,后边的省略号就是可变参数
//    ch[0]  += 1;
//    USART_DMAPrintf		(USART2,"%3d自定义printf串口DMA发送程序,后边的省略号就是可变参数\r\n",ch[0]);					//自定义printf串口DMA发送程序,后边的省略号就是可变参数
//    ch[0]  += 1;
//    USART_DMAPrintf		(USART2,"%3d自定义printf串口DMA发送程序,后边的省略号就是可变参数\r\n",ch[0]);					//自定义printf串口DMA发送程序,后边的省略号就是可变参数
//    ch[0]  += 1;
//    USART_DMAPrintf		(USART2,"%3d自定义printf串口DMA发送程序,后边的省略号就是可变参数\r\n",ch[0]);					//自定义printf串口DMA发送程序,后边的省略号就是可变参数
//    ch[0]  += 1;
//    USART_DMAPrintf		(USART2,"%3d自定义printf串口DMA发送程序,后边的省略号就是可变参数\r\n",ch[0]);					//自定义printf串口DMA发送程序,后边的省略号就是可变参数
//    ch[0]  += 1;
//    USART_DMAPrintf		(USART2,"%3d自定义printf串口DMA发送程序,后边的省略号就是可变参数\r\n",ch[0]);					//自定义printf串口DMA发送程序,后边的省略号就是可变参数
//    ch[0]  += 1;
//    USART_DMAPrintf		(USART2,"%3d自定义printf串口DMA发送程序,后边的省略号就是可变参数\r\n",ch[0]);					//自定义printf串口DMA发送程序,后边的省略号就是可变参数
//    ch[0]  += 1;
//    USART_DMAPrintf		(USART2,"%3d自定义printf串口DMA发送程序,后边的省略号就是可变参数\r\n",ch[0]);					//自定义printf串口DMA发送程序,后边的省略号就是可变参数
//    ch[0]  += 1;
//    USART_DMAPrintf		(USART2,"%3d自定义printf串口DMA发送程序,后边的省略号就是可变参数\r\n",ch[0]);					//自定义printf串口DMA发送程序,后边的省略号就是可变参数



  }

//		ch[0]	=	tx1_tcont;
//		ch[1]	=	tx1_tcont;
//    USART_DMAPrintf		(USART2,"%3d自定义printf串口DMA发送程序,后边的省略号就是可变参数\r\n",tx1_tcont);					//自定义printf串口DMA发送程序,后边的省略号就是可变参数
////    USART_Status(USART2);		//串口状态检查
//		USART_DMASend			(USART2,ch,10);	//串口DMA发送程序
    USART_TxServer(USART2);
//  }

	
}
void Usart_test(void)
{

}
#endif

