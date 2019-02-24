#ifdef IOTReaderTest

#include "IOTReaderTest.H"

#include "IOTReader.H"

#include "STM32_FLASH.H"

#include "STM32_PWM.H"
#include "STM32_GPIO.H"
#include "STM32_SYS.H"
#include "STM32_WDG.H"
#include "STM32_SYSTICK.H"
#include "STM32_USART.H"
#include "STM32F10x_BitBand.H"

#include	"stdio.h"			//用于printf
#include	"string.h"		//用于printf
#include	"stdarg.h"		//用于获取不确定个数的参数
#include	"stdlib.h"		//malloc动态申请内存空间


RS485Def RS485RD;   //usart2,pa1    //层板接口
#define datasize  140

unsigned char RxdLen=0;
unsigned char TxdLen=0;
unsigned char RxdBuffer[256];
unsigned char TxdBuffer[256]={0xAA,0x00,0x03,0x85,0x01,0x78,0xff,0xBB};
unsigned char KeyBuffer[6]={0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
unsigned short time=0;
unsigned char bfla=0;

/*******************************************************************************
* 函数名		:	
* 功能描述	:	 
* 输入		:	
* 输出		:
* 返回 		:
*******************************************************************************/
void IOTReaderTest_Configuration(void)
{
	SYS_Configuration();				//系统配置

  IOTReaderTestCOMM_Configuration();
    
	SysTick_Configuration(1000);	//系统嘀嗒时钟配置72MHz,单位为uS
	PWM_OUT(TIM2,PWM_OUTChannel1,1,990);						//PWM设定-20161127版本	
}
/*******************************************************************************
* 函数名		:	
* 功能描述	:	 
* 输入		:	
* 输出		:
* 返回 		:
*******************************************************************************/
void IOTReaderTest_Server(void)
{
  
  if(time++>200)
  {
    time=0;
//    if(IOTSec++>4)
//      IOTSec=0;

//    if(5<=bfla)
//    {      
//      if(bfla++>8)
//        bfla=0;
//      return;
//    }    
//    if(0==bfla)
//    {
//      RS485_DMA_ConfigurationNR(&RS485RD,9600,datasize);	//USART_DMA配置--查询方式，不开中断,配置完默认为接收状态
//      bfla=bfla+1;
//    }
//    else if(1==bfla)
//    {
//      RS485_DMA_ConfigurationNR(&RS485RD,19200,datasize);	//USART_DMA配置--查询方式，不开中断,配置完默认为接收状态
//      bfla=bfla+1;
//    }
//    else if(2==bfla)
//    {
//      RS485_DMA_ConfigurationNR(&RS485RD,38400,datasize);	//USART_DMA配置--查询方式，不开中断,配置完默认为接收状态
//      bfla=bfla+1;
//    }
//    else if(3==bfla)
//    {
//      RS485_DMA_ConfigurationNR(&RS485RD,57600,datasize);	//USART_DMA配置--查询方式，不开中断,配置完默认为接收状态
//      bfla=bfla+1;
//    }
//    else if(4==bfla)
//    {
//      RS485_DMA_ConfigurationNR(&RS485RD,115200,datasize);	//USART_DMA配置--查询方式，不开中断,配置完默认为接收状态
//      bfla=bfla+1;
//    }
    //TxdLen  = IOT5302WSetBaudrate(TxdBuffer);    //设置读卡器波特率
    TxdLen  = IOT5302WGetSNR(TxdBuffer);    //寻卡模式，获取UID
    RxdLen=RS485_DMASend(&RS485RD,TxdBuffer,TxdLen);
  }
	RxdLen=RS485_ReadBufferIDLE(&RS485RD,RxdBuffer);
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
void IOTReaderTestCOMM_Configuration(void)
{
  RS485RD.USARTx  = UART4;
  RS485RD.RS485_CTL_PORT  = GPIOC;
  RS485RD.RS485_CTL_Pin   = GPIO_Pin_12;
  RS485_DMA_ConfigurationNR(&RS485RD,19200,datasize);	//USART_DMA配置--查询方式，不开中断,配置完默认为接收状态
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
void IOTReaderTestCOMM_Server(void)
{

}


#endif
