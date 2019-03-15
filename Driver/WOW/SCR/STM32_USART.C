/******************************** User_library *********************************
* 文件名 	: STM32_SDCard.H
* 作者   	: wegam@sina.com
* 版本   	: V
* 日期   	: 2016/01/01
* 说明   	: 
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/


#include "STM32_USART.H"

#include "STM32_GPIO.H"
//#include "STM32_SYSTICK.H"
#include 	"LinkedList.H"

#include "stm32f10x_dma.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_nvic.h"
#include "stm32f10x_rcc.h"

#include	"stdio.h"			//用于printf
#include	"string.h"		//用于printf
#include	"stdarg.h"		//用于获取不确定个数的参数
#include	"stdlib.h"		//malloc动态申请内存空间


/*##############################################################################
################################################################################
设置波特率时的误差计算
--------------------------------------------------------------------------------
波特率				|fPCLK = 36MHz	误差%			|		fPCLK = 72MHz	误差%			|
--------------------------------------------------------------------------------
2400				|						0%						|						0%							
--------------------------------------------------------------------------------
9600				|						0%						|						0%								
--------------------------------------------------------------------------------
19200				|						0%						|						0%							
--------------------------------------------------------------------------------
57600				|						0%						|						0%							
--------------------------------------------------------------------------------
115200			|						0.15%					|						0%							
--------------------------------------------------------------------------------
230400			|						0.16%					|						0.16%							
--------------------------------------------------------------------------------
460800			|						0.16%					|						0.16%							
--------------------------------------------------------------------------------
921600			|						0.16%					|						0.16%							
--------------------------------------------------------------------------------
2250000			|						0%						|						0%							
--------------------------------------------------------------------------------

################################################################################
###############################################################################*/

//--------USART全局变量定义
#define	uRxSize		280				//默认串口DMA接收缓冲大小,如果配置时未输入缓存大小时使用的默认值
#define	uTxSize		uRxSize		//默认串口DMA发送缓冲大小
#define	uBaudRate	115200	//默认串口波特率
unsigned char uRx1Addr[uRxSize]	=	{0};					//串口1接收缓冲区地址::发送缓冲区地址在发送数据时设定，串口配置时借用接收缓冲区地址
unsigned char uRx2Addr[uRxSize]	=	{0};					//串口2接收缓冲区地址::发送缓冲区地址在发送数据时设定，串口配置时借用接收缓冲区地址
unsigned char uRx3Addr[uRxSize]	=	{0};					//串口3接收缓冲区地址::发送缓冲区地址在发送数据时设定，串口配置时借用接收缓冲区地址
unsigned char uRx4Addr[uRxSize]	=	{0};					//串口4接收缓冲区地址::发送缓冲区地址在发送数据时设定，串口配置时借用接收缓冲区地址

unsigned char uTx1Addr[uTxSize]	=	{0};					//串口1发送缓冲区地址::将待发送数据拷贝到此缓冲进行发送
unsigned char uTx2Addr[uTxSize]	=	{0};					//串口2发送缓冲区地址::将待发送数据拷贝到此缓冲进行发送
unsigned char uTx3Addr[uTxSize]	=	{0};					//串口3发送缓冲区地址::将待发送数据拷贝到此缓冲进行发送
unsigned char uTx4Addr[uTxSize]	=	{0};					//串口4发送缓冲区地址::将待发送数据拷贝到此缓冲进行发送

//unsigned char *uRx1Addr;					//串口1接收缓冲区地址::发送缓冲区地址在发送数据时设定，串口配置时借用接收缓冲区地址
//unsigned char *uRx2Addr;					//串口2接收缓冲区地址::发送缓冲区地址在发送数据时设定，串口配置时借用接收缓冲区地址
//unsigned char *uRx3Addr;					//串口3接收缓冲区地址::发送缓冲区地址在发送数据时设定，串口配置时借用接收缓冲区地址
//unsigned char *uRx4Addr;					//串口4接收缓冲区地址::发送缓冲区地址在发送数据时设定，串口配置时借用接收缓冲区地址

//unsigned char *uTx1Addr;					//串口1发送缓冲区地址::将待发送数据拷贝到此缓冲进行发送
//unsigned char *uTx2Addr;					//串口2发送缓冲区地址::将待发送数据拷贝到此缓冲进行发送
//unsigned char *uTx3Addr;					//串口3发送缓冲区地址::将待发送数据拷贝到此缓冲进行发送
//unsigned char *uTx4Addr;					//串口4发送缓冲区地址::将待发送数据拷贝到此缓冲进行发送


//static LINK_NODE *uRxLink1  = NULL;   //USART1接收链表
//static LINK_NODE *uRxLink2  = NULL;   //USART2接收链表
//static LINK_NODE *uRxLink3  = NULL;   //USART3接收链表
//static LINK_NODE *uRxLink4  = NULL;   //UART4接收链表
//static LINK_NODE *uRxLink5  = NULL;   //UART5接收链表

static LINK_NODE *uTxLink1  = NULL;   //USART1发送链表
static LINK_NODE *uTxLink2  = NULL;   //USART2发送链表
static LINK_NODE *uTxLink3  = NULL;   //USART3发送链表
static LINK_NODE *uTxLink4  = NULL;   //UART4发送链表
//static LINK_NODE *uTxLink5  = NULL;   //UART5发送链表


static struct
{
  unsigned short nUSART1;
  unsigned short nUSART2;
  unsigned short nUSART3;
  unsigned short nUART4;
//  unsigned short nUART5;	  //----无DMA
}SetDmaSize;      //配置时设置的DMA接收缓存大小
static struct
{
  unsigned short nUSART1;
  unsigned short nUSART2;
  unsigned short nUSART3;
  unsigned short nUART4;
//  unsigned short nUART5;	  //----无DMA
}RemaDmaSize;     //DMA开启后剩余DMA接收缓存大小，通过与设置的DMA缓存大小来判断数据是否在接收
static struct
{
  unsigned short nUSART1;
  unsigned short nUSART2;
  unsigned short nUSART3;
  unsigned short nUART4;
//  unsigned short nUART5;	  //----无DMA
}RetryCount;

//--------内部使用函数定义
//*****************RS485收发控制
void RS485_TX_EN(RS485Def *pRS485);	  //发使能
void RS485_RX_EN(RS485Def *pRS485);		//收使能，已经设置为接收状态返回1，否则返回0

/*******************************************************************************
*函数名			:	USART_DMA_ConfigurationNr
*功能描述		:	USART_DMA配置--查询方式，不开中断
*输入				: 
*返回值			:	无
*******************************************************************************/
void	USART_DMA_Initialize(
																USART_TypeDef* USARTx,	//串口号--USART1,USART2,USART3,UART4;//UART5不支持DMA
																u16 BufferSize					//设定接收缓冲区大小
)	//USART_DMA配置--查询方式，不开中断
{
	//1)**********定义变量	
	DMA_InitTypeDef DMA_Initstructure;
	
	DMA_Channel_TypeDef* DMAx_Channeltx=0;			//DMA发送通道请求信号---当DMA串口发送数据完成时，会发起DMA中断
	DMA_Channel_TypeDef* DMAx_Channelrx=0;			//DMA接收通道请求信号---DMA串口接收由串口发起中断，因此此处接收通道中断不使用

	u32 DMAx_FLAG_GLtx=0;												//DMA串口发送中断全局变量			
	u32 DMAx_FLAG_GLrx=0;												//DMA串口接收中断全局变量
	
	u8*	RXDBuffer	=	0;
  
 
	
	//2)******************************DMA
	//4)**********根据串口索引相关DMA通道及其它参数
	switch(*(u32*)&USARTx)
	{
		case 	USART1_BASE:
           if(BufferSize	==	0)	//如果未设定缓存大小，使用默认值
						SetDmaSize.nUSART1=uRxSize;
					else
						SetDmaSize.nUSART1=BufferSize;
          RXDBuffer	=	uRx1Addr;
					DMAx_Channeltx=DMA1_Channel4;
					DMAx_Channelrx=DMA1_Channel5;
					DMAx_FLAG_GLtx=DMA1_FLAG_GL4;
					DMAx_FLAG_GLrx=DMA1_FLAG_GL5;
					RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);	
					break;
		case 	USART2_BASE:
           if(BufferSize	==	0)	//如果未设定缓存大小，使用默认值
						SetDmaSize.nUSART2=uRxSize;
					else
						SetDmaSize.nUSART2=BufferSize;
          RXDBuffer	=	uRx2Addr;
					DMAx_Channeltx=DMA1_Channel7;
					DMAx_Channelrx=DMA1_Channel6;
					DMAx_FLAG_GLtx=DMA1_FLAG_GL7;
					DMAx_FLAG_GLrx=DMA1_FLAG_GL6;
					RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
					break;
		case 	USART3_BASE:
           if(BufferSize	==	0)	//如果未设定缓存大小，使用默认值
						SetDmaSize.nUSART3=uRxSize;
					else
						SetDmaSize.nUSART3=BufferSize;
          RXDBuffer	=	uRx3Addr;
					DMAx_Channeltx=DMA1_Channel2;
					DMAx_Channelrx=DMA1_Channel3;
					DMAx_FLAG_GLtx=DMA1_FLAG_GL2;
					DMAx_FLAG_GLrx=DMA1_FLAG_GL3;
					RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
					break;
		case 	UART4_BASE:
           if(BufferSize	==	0)	//如果未设定缓存大小，使用默认值
						SetDmaSize.nUART4=uRxSize;
					else
						SetDmaSize.nUART4=BufferSize;
          RXDBuffer	=	uRx4Addr;
					DMAx_Channeltx=DMA2_Channel5;
					DMAx_Channelrx=DMA2_Channel3;
					DMAx_FLAG_GLtx=DMA2_FLAG_GL5;
					DMAx_FLAG_GLrx=DMA2_FLAG_GL3;
					RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA2,ENABLE);
					break;
		case 	UART5_BASE:
					//UART5不支持DMA
					return;
		default :break;
	}

	//5)**********DMA发送初始化，外设作为DMA的目的端
	DMA_Initstructure.DMA_PeripheralBaseAddr  = (u32)(&USARTx->DR);					//DMA外设源地址
	DMA_Initstructure.DMA_MemoryBaseAddr      = (u32)RXDBuffer;							//DMA数据内存地址
	DMA_Initstructure.DMA_DIR                 = DMA_DIR_PeripheralDST;			  //DMA_DIR_PeripheralDST（外设作为DMA的目的端），DMA_DIR_PeripheralSRC（外设作为数据传输的来源）
	DMA_Initstructure.DMA_BufferSize          = BufferSize; 								  //指定DMA通道的DMA缓存的大小
	DMA_Initstructure.DMA_PeripheralInc       = DMA_PeripheralInc_Disable;	  //DMA_PeripheralInc_Enable（外设地址寄存器递增），DMA_PeripheralInc_Disable（外设地址寄存器不变），
	DMA_Initstructure.DMA_MemoryInc           = DMA_MemoryInc_Enable;				  //DMA_MemoryInc_Enable（内存地址寄存器递增），DMA_MemoryInc_Disable（内存地址寄存器不变）
	DMA_Initstructure.DMA_PeripheralDataSize  = DMA_PeripheralDataSize_Byte;	//外设数据宽度--DMA_PeripheralDataSize_Byte（数据宽度为8位），DMA_PeripheralDataSize_HalfWord（数据宽度为16位），DMA_PeripheralDataSize_Word（数据宽度为32位）
	DMA_Initstructure.DMA_MemoryDataSize      = DMA_MemoryDataSize_Byte;		  //内存数据宽度--DMA_MemoryDataSize_Byte（数据宽度为8位），DMA_MemoryDataSize_HalfWord（数据宽度为16位），DMA_MemoryDataSize_Word（数据宽度为32位）
	DMA_Initstructure.DMA_Mode                = DMA_Mode_Normal;						  //DMA工作模式--DMA_Mode_Normal（只传送一次）, DMA_Mode_Circular（不停地传送）
	DMA_Initstructure.DMA_Priority            = DMA_Priority_High; 					  //DMA通道的转输优先级--DMA_Priority_VeryHigh（非常高）DMA_Priority_High（高)，DMA_Priority_Medium（中），DMA_Priority_Low（低）
	DMA_Initstructure.DMA_M2M                 = DMA_M2M_Disable;						  //DMA通道的内存到内存传输--DMA_M2M_Enable(设置为内存到内存传输)，DMA_M2M_Disable（非内存到内存传输）
	DMA_Init(DMAx_Channeltx,&DMA_Initstructure);														  //初始化DMA

	//6)**********DMA接收初始化，外设作为DMA的源端
	DMA_Initstructure.DMA_PeripheralBaseAddr  = (u32)(&USARTx->DR);					//DMA外设源地址
	DMA_Initstructure.DMA_MemoryBaseAddr      = (u32)RXDBuffer;						  //DMA数据内存地址
	DMA_Initstructure.DMA_DIR                 = DMA_DIR_PeripheralSRC;			  //DMA_DIR_PeripheralDST（外设作为DMA的目的端），DMA_DIR_PeripheralSRC（外设作为数据传输的来源）
	DMA_Initstructure.DMA_BufferSize          = BufferSize; 								  //指定DMA通道的DMA缓存的大小
	DMA_Initstructure.DMA_PeripheralInc       = DMA_PeripheralInc_Disable;	  //DMA_PeripheralInc_Enable（外设地址寄存器递增），DMA_PeripheralInc_Disable（外设地址寄存器不变），
	DMA_Initstructure.DMA_MemoryInc           = DMA_MemoryInc_Enable;				  //DMA_MemoryInc_Enable（内存地址寄存器递增），DMA_MemoryInc_Disable（内存地址寄存器不变）
	DMA_Initstructure.DMA_PeripheralDataSize  = DMA_PeripheralDataSize_Byte; 	//外设数据宽度--DMA_PeripheralDataSize_Byte（数据宽度为8位），DMA_PeripheralDataSize_HalfWord（数据宽度为16位），DMA_PeripheralDataSize_Word（数据宽度为32位）
	DMA_Initstructure.DMA_MemoryDataSize      = DMA_MemoryDataSize_Byte;		  //内存数据宽度--DMA_MemoryDataSize_Byte（数据宽度为8位），DMA_MemoryDataSize_HalfWord（数据宽度为16位），DMA_MemoryDataSize_Word（数据宽度为32位）
	DMA_Initstructure.DMA_Mode                = DMA_Mode_Normal;						  //DMA工作模式--DMA_Mode_Normal（只传送一次）, DMA_Mode_Circular（不停地传送）
	DMA_Initstructure.DMA_Priority            = DMA_Priority_High; 					  //DMA通道的转输优先级--DMA_Priority_VeryHigh（非常高）DMA_Priority_High（高)，DMA_Priority_Medium（中），DMA_Priority_Low（低）
	DMA_Initstructure.DMA_M2M                 = DMA_M2M_Disable;						  //DMA通道的内存到内存传输--DMA_M2M_Enable(设置为内存到内存传输)，DMA_M2M_Disable（非内存到内存传输）
	DMA_Init(DMAx_Channelrx,&DMA_Initstructure);														  //初始化DMA	
	
	//8)**********配置相关中断
	//8.1)**********串口接收中断配置
	//--将串口接收中断关闭，然后开启串口空闲中断，利用DMA自动接收串口数据
	//--若DMA接收未开启，则使用串口接收中断
	//--若DMA接收开启，串口接收中断应该关闭，在DMA配置中会将串口接收中断关闭

	/* 启动DMA1通道5*/
	DMA_Cmd(DMAx_Channeltx,DISABLE);				//关闭DMA发送----需要发送时再打开
	//10.2)**********使能串口
	DMA_Cmd(DMAx_Channelrx,ENABLE);					//打开DMA接收----自动接收串口数据	
	//9.1)**********关闭DMA发送	
	
	//8.2)**********使能串口DMA方式接收
	USART_DMACmd(USARTx,USART_DMAReq_Rx,ENABLE);
	//8.3)**********使能串口DMA方式发送
	USART_DMACmd(USARTx,USART_DMAReq_Tx,ENABLE);
	//9)**********清除相关中断标志位	
	//	DMA_Cmd(DMAx_Channeltx,ENABLE);
	//9.2)**********使能相关DMA通道传输完成中断
	DMA_ITConfig(DMAx_Channeltx,DMA_IT_TC, DISABLE);
	//9.3)**********清除串口DMA方式发送中断全局标志
	DMA_ClearFlag(DMAx_FLAG_GLtx);                                 					// 清除DMA所有标志
	//9.3)**********清除串口DMA方式接收中断全局标志
	DMA_ClearFlag(DMAx_FLAG_GLrx);                                 					// 清除DMA所有标志	
}
/*******************************************************************************
*函数名			:	USART_DMA_ConfigurationNr
*功能描述		:	USART_DMA配置--查询方式，不开中断
*输入				: 
*返回值			:	无
*******************************************************************************/
void	USART_GPIO_Initialize(USART_TypeDef* USARTx)	//串口GPIO配置
{
	//1)**********定义变量	
	GPIO_InitTypeDef GPIO_InitStructure;					//GPIO结构体
	u16 TXD_Pin=0;																//串口发送脚
	u16 RXD_Pin=0;																//串口接收脚
	GPIO_TypeDef* GPIO_TX=0;
	GPIO_TypeDef* GPIO_RX=0;
	switch(*(u32*)&USARTx)
	{
		case 	USART1_BASE:
					
					GPIO_TX=GPIOA;
					GPIO_RX=GPIOA;
					TXD_Pin=GPIO_Pin_9;											//USART1-TX>PA9
					RXD_Pin=GPIO_Pin_10;										//USART1-RX>PA10
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO,ENABLE);
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);	//USART1时钟开启			
					break;
		case 	USART2_BASE:

					GPIO_TX=GPIOA;
					GPIO_RX=GPIOA;
					TXD_Pin=GPIO_Pin_2;		//USART2-TX>PA2
					RXD_Pin=GPIO_Pin_3;		//USART2-RX>PA3
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
					RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);	//USART2时钟开启		
					break;
		case 	USART3_BASE:

					GPIO_TX=GPIOB;
					GPIO_RX=GPIOB;
					TXD_Pin=GPIO_Pin_10;	//USART3-TX>PB10
					RXD_Pin=GPIO_Pin_11;	//USART3-RX>PB11
					
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);				//关闭AFIO时钟,为关闭JTAG功能
					GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);  //关闭JTAG功能
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
					RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);	//USART3时钟开启		
					break;
		case 	UART4_BASE:

					GPIO_TX=GPIOC;
					GPIO_RX=GPIOC;
					TXD_Pin=GPIO_Pin_10;	//USART1-TX>PC10
					RXD_Pin=GPIO_Pin_11;	//USART1-RX>PC11
					
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_AFIO,ENABLE);
					RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);	//UART4时钟开启	
					break;
		case 	UART5_BASE:   //UART5不支持DMA
          GPIO_TX=GPIOC;
					GPIO_RX=GPIOD;
					TXD_Pin=GPIO_Pin_10;	//USART1-TX>PC12
					RXD_Pin=GPIO_Pin_2; 	//USART1-RX>PD2
          RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD|RCC_APB2Periph_AFIO,ENABLE);
					RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE);	//UART4时钟开启	
					break;
		default :break;
	}
	//3)**********初始化串口
	//3.1)**********初始化TXD引脚
	GPIO_InitStructure.GPIO_Pin = TXD_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIO_TX,&GPIO_InitStructure);

	//3.2)**********初始化RXD引脚
	GPIO_InitStructure.GPIO_Pin = RXD_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;							//上拉输入
	GPIO_Init(GPIO_RX,&GPIO_InitStructure);
}
/*******************************************************************************
*函数名			:	USART_DMA_ConfigurationNr
*功能描述		:	USART_DMA配置--查询方式，不开中断
*输入				: 
*返回值			:	无
*******************************************************************************/
void	USART_IT_Initialize(USART_TypeDef* USARTx)	//串口GPIO配置
{
	//1)**********定义变量
  NVIC_InitTypeDef 	NVIC_InitStructure; 					//NVIC结构体
  u8 USARTx_IRQChannel=0;
  
	GPIO_InitTypeDef GPIO_InitStructure;					//GPIO结构体
	u16 TXD_Pin=0;																//串口发送脚
	u16 RXD_Pin=0;																//串口接收脚
	GPIO_TypeDef* GPIO_TX=0;
	GPIO_TypeDef* GPIO_RX=0;
	switch(*(u32*)&USARTx)
	{
		case 	USART1_BASE:
					USARTx_IRQChannel=USART1_IRQChannel;		//中断			
					break;
		case 	USART2_BASE:
          USARTx_IRQChannel=USART2_IRQChannel;		//中断	
					break;
		case 	USART3_BASE:
          USARTx_IRQChannel=USART3_IRQChannel;		//中断					break;
		case 	UART4_BASE:
          USARTx_IRQChannel=UART4_IRQChannel;		//中断
					break;
		case 	UART5_BASE:   //UART5不支持DMA
          USARTx_IRQChannel=UART5_IRQChannel;		//中断	
					break;
		default :break;
	}
	//4)**********串口全局中断初始化
	NVIC_InitStructure.NVIC_IRQChannel = USARTx_IRQChannel;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;     //默认1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;              //默认1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}
/*******************************************************************************
*函数名			:	USART_DMA_ConfigurationNr
*功能描述		:	USART_DMA配置--查询方式，不开中断
*输入				: 
*返回值			:	无
*******************************************************************************/
void	USART_DMA_ConfigurationNR(
																USART_TypeDef* USARTx,	//串口号--USART1,USART2,USART3,UART4;//UART5不支持DMA
																u32 USART_BaudRate,			//波特率
																u16 BufferSize					//设定接收缓冲区大小
)	//USART_DMA配置--查询方式，不开中断
{
	//1)**********定义变量	

	USART_InitTypeDef USART_InitStructure;				//USART结构体	
  //2)******************************GPIO配置
  USART_GPIO_Initialize(USARTx);	//串口GPIO配置
	
	//3.3)**********初始化串口参数
	USART_DeInit(USARTx);
	USART_InitStructure.USART_BaudRate    = USART_BaudRate; 					  //波特率
	USART_InitStructure.USART_WordLength  = USART_WordLength_8b;		    //数据位
	USART_InitStructure.USART_StopBits    = USART_StopBits_1;				    //停止位
	USART_InitStructure.USART_Parity      = USART_Parity_No ; 					//奇偶校验
	USART_InitStructure.USART_Mode        = USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//流控
	USART_Init(USARTx, &USART_InitStructure);											//初始化串口
	
  USART_ITConfig(USARTx,USART_IT_IDLE, DISABLE);					//使用空闲中断，DMA自动接收，检测到总线空闲表示发送端已经发送完成，数据保存在DMA缓冲器中
	USART_ClearITPendingBit(USARTx,USART_IT_IDLE); 					//清除空闲串口标志位
//	
	USART_Cmd(USARTx, ENABLE);
  //2)******************************DMA
	USART_DMA_Initialize	(USARTx,BufferSize);	//USART_DMA配置--查询方式，不开中断
}
/*******************************************************************************
*函数名			:	USART_DMA_ConfigurationNr
*功能描述		:	USART_DMA配置--查询方式，不开中断
*输入				: 
*返回值			:	无
*******************************************************************************/
void	USART_DMA_ConfigurationIDLEIT(
																USART_TypeDef* USARTx,	//串口号--USART1,USART2,USART3,UART4;//UART5不支持DMA
																u32 USART_BaudRate,			//波特率
																u16 BufferSize					//设定接收缓冲区大小
)	//USART_DMA配置--查询方式，不开中断
{
	//1)**********定义变量	
	USART_InitTypeDef USART_InitStructure;				//USART结构体	
	GPIO_InitTypeDef GPIO_InitStructure;					//GPIO结构体
	
	u16 TXD_Pin=0;																//串口发送脚
	u16 RXD_Pin=0;																//串口接收脚

	GPIO_TypeDef* GPIO_TX=0;
	GPIO_TypeDef* GPIO_RX=0;
	switch(*(u32*)&USARTx)
	{
		case 	USART1_BASE:
					if(BufferSize	==	0)	//如果未设定缓存大小，使用默认值
						SetDmaSize.nUSART1=uRxSize;
					else
						SetDmaSize.nUSART1=BufferSize;					

					GPIO_TX=GPIOA;
					GPIO_RX=GPIOA;
					TXD_Pin=GPIO_Pin_9;											//USART1-TX>PA9
					RXD_Pin=GPIO_Pin_10;										//USART1-RX>PA10
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO,ENABLE);
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);	//USART1时钟开启			
					break;
		case 	USART2_BASE:
					if(BufferSize	==	0)	//如果未设定缓存大小，使用默认值
						SetDmaSize.nUSART2=uRxSize;
					else
						SetDmaSize.nUSART2=BufferSize;

					GPIO_TX=GPIOA;
					GPIO_RX=GPIOA;
					TXD_Pin=GPIO_Pin_2;		//USART2-TX>PA2
					RXD_Pin=GPIO_Pin_3;		//USART2-RX>PA3
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
					RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);	//USART2时钟开启		
					break;
		case 	USART3_BASE:
					if(BufferSize	==	0)	//如果未设定缓存大小，使用默认值
						SetDmaSize.nUSART3=uRxSize;
					else
						SetDmaSize.nUSART3=BufferSize;

					GPIO_TX=GPIOB;
					GPIO_RX=GPIOB;
					TXD_Pin=GPIO_Pin_10;	//USART3-TX>PB10
					RXD_Pin=GPIO_Pin_11;	//USART3-RX>PB11
					
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);				//关闭AFIO时钟,为关闭JTAG功能
					GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);  //关闭JTAG功能
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
					RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);	//USART3时钟开启		
					break;
		case 	UART4_BASE:
					if(BufferSize	==	0)	//如果未设定缓存大小，使用默认值
						SetDmaSize.nUART4=uRxSize;
					else
						SetDmaSize.nUART4=BufferSize;

					GPIO_TX=GPIOC;
					GPIO_RX=GPIOC;
					TXD_Pin=GPIO_Pin_10;	//USART1-TX>PC10
					RXD_Pin=GPIO_Pin_11;	//USART1-RX>PC11
					
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_AFIO,ENABLE);
					RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);	//UART4时钟开启	
					break;
		case 	UART5_BASE:
					//UART5不支持DMA
					return;
		default :break;
	}
	//3)**********初始化串口
	//3.1)**********初始化TXD引脚
	GPIO_InitStructure.GPIO_Pin = TXD_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIO_TX,&GPIO_InitStructure);

	//3.2)**********初始化RXD引脚
	GPIO_InitStructure.GPIO_Pin = RXD_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;							//上拉输入
	GPIO_Init(GPIO_RX,&GPIO_InitStructure);
	
	//3.3)**********初始化串口参数
	USART_DeInit(USARTx);
	USART_InitStructure.USART_BaudRate    = USART_BaudRate; 					      //波特率
	USART_InitStructure.USART_WordLength  = USART_WordLength_8b;		        //数据位
	USART_InitStructure.USART_StopBits    = USART_StopBits_1;				        //停止位
	USART_InitStructure.USART_Parity      = USART_Parity_No ; 					    //奇偶校验
	USART_InitStructure.USART_Mode        = USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//流控
	USART_Init(USARTx, &USART_InitStructure);											//初始化串口	

	USART_ITConfig(USARTx,USART_IT_IDLE, ENABLE);				//使用空闲中断，DMA自动接收，检测到总线空闲表示发送端已经发送完成，数据保存在DMA缓冲器中
	USART_ITConfig(USARTx,USART_IT_TC, ENABLE);					//发送完成中断
	USART_ClearITPendingBit(USARTx,USART_IT_IDLE); 				//清除空闲串口标志位
	USART_ClearITPendingBit(USARTx,USART_IT_TC); 					//清除发送完成中断标志位
	
	USART_Cmd(USARTx, ENABLE);
  //2)******************************DMA
  USART_DMA_Initialize	(USARTx,BufferSize);	//USART_DMA配置--查询方式，不开中断

}
/*******************************************************************************
*函数名			:	USART_DMA_ConfigurationNr
*功能描述		:	USART_DMA配置--查询方式，不开中断
*输入				: 
*返回值			:	无
*******************************************************************************/
void	USART_DMA_ConfigurationEV(
																USART_TypeDef* USARTx,	//串口号--USART1,USART2,USART3,UART4;//UART5不支持DMA
																u32 USART_BaudRate,			//波特率
																u16 BufferSize					//设定接收缓冲区大小
)	//USART_DMA配置--查询方式，不开中断,偶校验
{
	//1)**********定义变量	
	
	USART_InitTypeDef USART_InitStructure;				//USART结构体
  //2)******************************GPIO配置	
	USART_GPIO_Initialize(USARTx);	//串口GPIO配置
	
	//3.3)**********初始化串口参数
	USART_DeInit(USARTx);
	USART_InitStructure.USART_BaudRate 		= USART_BaudRate; 			//波特率
	USART_InitStructure.USART_WordLength 	= USART_WordLength_9b;	//数据位
	USART_InitStructure.USART_StopBits 		= USART_StopBits_1;			//停止位
	USART_InitStructure.USART_Parity 			= USART_Parity_Even ; 	//偶校验
	USART_InitStructure.USART_Mode				= USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//流控
	USART_Init(USARTx, &USART_InitStructure);											//初始化串口
	

	USART_ITConfig(USARTx,USART_IT_IDLE, DISABLE);					//使用空闲中断，DMA自动接收，检测到总线空闲表示发送端已经发送完成，数据保存在DMA缓冲器中
	USART_ClearITPendingBit(USARTx,USART_IT_IDLE); 					//清除空闲串口标志位
	
	USART_Cmd(USARTx, ENABLE);
  
  //2)******************************DMA
  USART_DMA_Initialize	(USARTx,BufferSize);	//USART_DMA配置--查询方式，不开中断
}
/*******************************************************************************
*函数名			:	USART_DMA_ConfigurationNr
*功能描述		:	USART_DMA配置--查询方式，不开中断
*输入				: 
*返回值			:	无
*******************************************************************************/
void	USART_DMA_ConfigurationOD(
																USART_TypeDef* USARTx,	//串口号--USART1,USART2,USART3,UART4;//UART5不支持DMA
																u32 USART_BaudRate,			//波特率
																u16 BufferSize					//设定接收缓冲区大小
)	//USART_DMA配置--查询方式，不开中断--奇校验
{
	//1)**********定义变量	
	USART_InitTypeDef USART_InitStructure;				//USART结构体
  //2)******************************GPIO配置	
	USART_GPIO_Initialize(USARTx);	//串口GPIO配置
		
	//3.3)**********初始化串口参数
	USART_DeInit(USARTx);
	USART_InitStructure.USART_BaudRate = USART_BaudRate; 					//波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_9b;		//数据位
	USART_InitStructure.USART_StopBits = USART_StopBits_1;				//停止位
	USART_InitStructure.USART_Parity = USART_Parity_Odd ; 				//奇偶校验-奇校验
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//流控
	USART_Init(USARTx, &USART_InitStructure);											//初始化串口
	
	USART_ITConfig(USARTx,USART_IT_IDLE, DISABLE);					//使用空闲中断，DMA自动接收，检测到总线空闲表示发送端已经发送完成，数据保存在DMA缓冲器中
	USART_ClearITPendingBit(USARTx,USART_IT_IDLE); 					//清除空闲串口标志位
	
	USART_Cmd(USARTx, ENABLE);
  //2)******************************DMA
  USART_DMA_Initialize	(USARTx,BufferSize);	//USART_DMA配置--查询方式，不开中断
}

/*******************************************************************************
*函数名			:	USART_DMA_ConfigurationNr
*功能描述		:	USART_DMA配置--中断方式
*输入				: 
*返回值			:	无
*******************************************************************************/
void	USART_DMA_ConfigurationIT(
																USART_TypeDef* USARTx,			//串口号--USART1,USART2,USART3,UART4;//UART5不支持DMA
																u32 USART_BaudRate,					//波特率
																u32 BufferSize							//设定接收缓冲区大小
)	//USART_DMA配置--中断方式
{
  //2)******************************GPIO配置
  USART_GPIO_Initialize(USARTx);                //串口GPIO配置
  //2)******************************中断配置
  USART_IT_Initialize(USARTx);	                //串口中断配置	
	
	USART_ITConfig(USARTx,USART_IT_IDLE, ENABLE);					//使用空闲中断，DMA自动接收，检测到总线空闲表示发送端已经发送完成，数据保存在DMA缓冲器中
	USART_ClearITPendingBit(USARTx,USART_IT_IDLE); 				//清除空闲串口标志位
	
	USART_Cmd(USARTx, ENABLE);
  
  //2)******************************DMA
  USART_DMA_Initialize	(USARTx,BufferSize);	//USART_DMA配置--查询方式，不开中断
}

/*******************************************************************************
*函数名			:	USART_DMA_ConfigurationNr
*功能描述		:	USART_DMA配置--查询方式，不开中断
*输入				: 
*返回值			:	无
*******************************************************************************/
void	USART_DMA_ConfigurationNRRemap(
																USART_TypeDef* USARTx,	//串口号--USART1,USART2,USART3,UART4;//UART5不支持DMA
																u32 USART_BaudRate,			//波特率
																u32 *RXDBuffer,					//接收缓冲区地址::发送缓冲区地址在发送数据时设定，串口配置时借用接收缓冲区地址
																u32 BufferSize					//设定接收缓冲区大小
)	//USART_DMA配置--查询方式，不开中断
{
	//1)**********定义变量	
	USART_InitTypeDef USART_InitStructure;				//USART结构体	
	GPIO_InitTypeDef GPIO_InitStructure;					//GPIO结构体
	
	u16 TXD_Pin=0;																//串口发送脚
	u16 RXD_Pin=0;																//串口接收脚
	GPIO_TypeDef* GPIO_TX=0;
	GPIO_TypeDef* GPIO_RX=0;
//	u8 USARTx_IRQChannel=0;
	//2)******************************配置相关GPIO/串口时钟打开
	//2.1)**********USART1
	if(USARTx==USART1)
	{
		
		SetDmaSize.nUSART1=BufferSize;
		
		TXD_Pin=GPIO_Pin_6;									  //USART1-TX>PA9
		RXD_Pin=GPIO_Pin_7;										//USART1-RX>PA10
		
		GPIO_TX=GPIOB;
		GPIO_RX=GPIOB;
		
//		USARTx_IRQChannel=USART1_IRQChannel;		//中断
		
		GPIO_PinRemapConfig(GPIO_Remap_USART1,ENABLE);				//I/O口重映射开启
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO,ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);	//USART1时钟开启

	}
	//2.2)**********USART2
	else if(USARTx==USART2)
	{
		SetDmaSize.nUSART2=BufferSize;
		
		TXD_Pin=GPIO_Pin_2;		//USART2-TX>PA2
		RXD_Pin=GPIO_Pin_3;		//USART2-RX>PA3
		
		GPIO_TX=GPIOA;
		GPIO_RX=GPIOA;
		
//		USARTx_IRQChannel=USART2_IRQChannel;		//中断
		
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);	//USART1时钟开启

	}
	//2.3)**********USART3
	else if(USARTx==USART3)
	{
		SetDmaSize.nUSART3=BufferSize;
		
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);				//关闭AFIO时钟,为关闭JTAG功能
		GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);  //关闭JTAG功能
//		GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);  		//关闭SWD功能
		
		
		TXD_Pin=GPIO_Pin_10;	//USART3-TX>PB10
		RXD_Pin=GPIO_Pin_11;	//USART3-RX>PB11
		
		GPIO_TX=GPIOB;
		GPIO_RX=GPIOB;
		
//		USARTx_IRQChannel=USART3_IRQChannel;		//中断
		
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);	//USART1时钟开启
		

	}
	//2.4)**********USART4
	else if(USARTx==UART4)
	{
		SetDmaSize.nUART4=BufferSize;
		
		TXD_Pin=GPIO_Pin_10;	//USART1-TX>PC10
		RXD_Pin=GPIO_Pin_11;	//USART1-RX>PC11
		
		GPIO_TX=GPIOC;
		GPIO_RX=GPIOC;
		
//		USARTx_IRQChannel=UART4_IRQChannel;		//中断
		
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_AFIO,ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);	//USART1时钟开启
	}
	//2.5)**********USART5
	else if(USARTx==UART5)
	{
//		gUART5_BufferSizebac=BufferSize;		//-----串口5无DMA
		
		TXD_Pin=GPIO_Pin_12;	//USART1-TX>PC12
		RXD_Pin=GPIO_Pin_2;		//USART1-RX>PD2
		
		GPIO_TX=GPIOC;
		GPIO_RX=GPIOD;
		
//		USARTx_IRQChannel=UART5_IRQChannel;		//中断
		
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE);	//USART1时钟开启
	}
	//3)**********初始化串口
	//3.1)**********初始化TXD引脚
	GPIO_InitStructure.GPIO_Pin = TXD_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIO_TX,&GPIO_InitStructure);

	//3.2)**********初始化RXD引脚
	GPIO_InitStructure.GPIO_Pin = RXD_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;							//上拉输入
	GPIO_Init(GPIO_RX,&GPIO_InitStructure);
	
	//3.3)**********初始化串口参数
	USART_DeInit(USARTx);
	USART_InitStructure.USART_BaudRate = USART_BaudRate; 					//波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;		//数据位
	USART_InitStructure.USART_StopBits = USART_StopBits_1;				//停止位
	USART_InitStructure.USART_Parity = USART_Parity_No ; 					//奇偶校验
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//流控
	USART_Init(USARTx, &USART_InitStructure);											//初始化串口
	
	USART_ITConfig(USARTx,USART_IT_IDLE, DISABLE);					//使用空闲中断，DMA自动接收，检测到总线空闲表示发送端已经发送完成，数据保存在DMA缓冲器中
	USART_ClearITPendingBit(USARTx,USART_IT_IDLE); 					//清除空闲串口标志位
	
	USART_Cmd(USARTx, ENABLE);
  
  //2)******************************DMA
  USART_DMA_Initialize	(USARTx,BufferSize);	//USART_DMA配置--查询方式，不开中断
}
/*******************************************************************************
* 函数名			:	USART_ReadBuffer
* 功能描述		:	串口空闲模式读串口接收缓冲区，如果有数据，将数据拷贝到RevBuffer,并返回接收到的数据个数，然后重新将接收缓冲区地址指向RxdBuffer， 
* 输入			: void
* 返回值			: void
*******************************************************************************/
u16	USART_ReadBufferIDLE(
											USART_TypeDef* USARTx,	//串口号--USART1,USART2,USART3,UART4;//UART5不支持DMA
											u8 *RevBuffer						//数据保存缓冲区地址，如果串口的接收到数据，将数据拷贝到RevBuffer
)	//串口空闲模式读串口接收缓冲区，如果有数据，将数据拷贝到RevBuffer,并返回接收到的数据个数
{
	u16 length=0;
	switch(*(u32*)&USARTx)
	{
		case 	USART1_BASE:
					if(USART_GetITStatus(USART1,USART_IT_IDLE)||USART_GetFlagStatus(USART1,USART_FLAG_IDLE))
					{
						USART_ClearITPendingBit(USART1,USART_IT_IDLE); 							//清除空闲串口标志位
						USART_ClearFlag(USART1,USART_FLAG_IDLE); 										//清除空闲串口标志位

						DMA1_Channel5->CCR &= (u32)0xFFFFFFFE;											//DMA_Cmd(DMA1_Channel5,DISABLE);//DMA发送关闭，只能在DMA关闭情况下才可以写入CNDTR					
						
						//------计算接收长度及读取数据
						USART1->DR; 																								//读出数据以完成清除标志			
						length = DMA1_Channel5->CNDTR;															//DMA_GetCurrDataCounter(DMA1_Channel5);	//得到真正接收数据个数(DMA_GetCurrDataCounter返回当前DMA通道x剩余的待传输数据数目)
						length=SetDmaSize.nUSART1-length;												    //设定缓冲区大小减剩余缓冲区大小得到实际接收到的数据个数
						memcpy(RevBuffer,uRx1Addr,length);													//复制指定大小的数据
						
						//------重新指向接收缓冲区地址并使能DMA接收			
						DMA1_Channel5->CMAR=(u32)uRx1Addr;							//重新设置DMA接收地址
						DMA1_Channel5->CNDTR=SetDmaSize.nUSART1;			  //重新设置接收数据个数			
						DMA_Cmd(DMA1_Channel5,ENABLE);  								//开启接收DMA
						
						return length;			//返回接收到的数据个数
					}			
					break;
			case 	USART2_BASE:
					if(USART_GetITStatus(USART2,USART_IT_IDLE)||USART_GetFlagStatus(USART2,USART_FLAG_IDLE))
					{
						USART_ClearITPendingBit(USART2,USART_IT_IDLE); 							//清除空闲串口标志位
						USART_ClearFlag(USART2,USART_FLAG_IDLE); 										//清除空闲串口标志位

						DMA1_Channel6->CCR &= (u32)0xFFFFFFFE;											//DMA_Cmd(DMA1_Channel6,DISABLE);//DMA发送关闭，只能在DMA关闭情况下才可以写入CNDTR					
						
						//------计算接收长度及读取数据
						USART2->DR; 																								//读出数据以完成清除标志			
						length = DMA1_Channel6->CNDTR;															//DMA_GetCurrDataCounter(DMA1_Channel6);	//得到真正接收数据个数(DMA_GetCurrDataCounter返回当前DMA通道x剩余的待传输数据数目)
						length=SetDmaSize.nUSART2-length;												    //设定缓冲区大小减剩余缓冲区大小得到实际接收到的数据个数
						memcpy(RevBuffer,uRx2Addr,length);													//复制指定大小的数据
						
						//------重新指向接收缓冲区地址并使能DMA接收			
						DMA1_Channel6->CMAR=(u32)uRx2Addr;							//重新设置DMA接收地址
						DMA1_Channel6->CNDTR=SetDmaSize.nUSART2;			  //重新设置接收数据个数
						DMA1_Channel6->CCR |=(u32)0x00000001;						//DMA_Cmd(DMA1_Channel6,ENABLE);//DMA接收开启3						
						return length;			//返回接收到的数据个数
					}			
					break;
			case 	USART3_BASE:
					if(USART_GetITStatus(USART3,USART_IT_IDLE)||USART_GetFlagStatus(USART3,USART_FLAG_IDLE))
					{
						USART_ClearITPendingBit(USART3,USART_IT_IDLE); 							//清除空闲串口标志位
						USART_ClearFlag(USART3,USART_FLAG_IDLE); 										//清除空闲串口标志位

						DMA1_Channel3->CCR &= (u32)0xFFFFFFFE;											//DMA_Cmd(DMA1_Channel3,DISABLE);//DMA发送关闭，只能在DMA关闭情况下才可以写入CNDTR					
						
						//------计算接收长度及读取数据
						USART3->DR; 																								//读出数据以完成清除标志			
						length = DMA1_Channel3->CNDTR;															//DMA_GetCurrDataCounter(DMA1_Channel3);	//得到真正接收数据个数(DMA_GetCurrDataCounter返回当前DMA通道x剩余的待传输数据数目)
						length=SetDmaSize.nUSART3-length;   												//设定缓冲区大小减剩余缓冲区大小得到实际接收到的数据个数
						memcpy(RevBuffer,uRx3Addr,length);													//复制指定大小的数据
						
						//------重新指向接收缓冲区地址并使能DMA接收			
						DMA1_Channel3->CMAR=(u32)uRx3Addr;							//重新设置DMA接收地址
						DMA1_Channel3->CNDTR=SetDmaSize.nUSART3;			  //重新设置接收数据个数
						DMA1_Channel3->CCR |=(u32)0x00000001;						//DMA_Cmd(DMA1_Channel3,ENABLE);//DMA接收开启3						
						return length;			//返回接收到的数据个数
					}			
					break;
			case 	UART4_BASE:
					if(USART_GetITStatus(UART4,USART_IT_IDLE)||USART_GetFlagStatus(UART4,USART_FLAG_IDLE))
					{
						USART_ClearITPendingBit(UART4,USART_IT_IDLE); 							//清除空闲串口标志位
						USART_ClearFlag(UART4,USART_FLAG_IDLE); 										//清除空闲串口标志位

						DMA2_Channel3->CCR &= (u32)0xFFFFFFFE;											//DMA_Cmd(DMA2_Channel3,DISABLE);//DMA发送关闭，只能在DMA关闭情况下才可以写入CNDTR					
						
						//------计算接收长度及读取数据
						USART2->DR; 																								//读出数据以完成清除标志			
						length = DMA2_Channel3->CNDTR;															//DMA_GetCurrDataCounter(DMA2_Channel3);	//得到真正接收数据个数(DMA_GetCurrDataCounter返回当前DMA通道x剩余的待传输数据数目)
						length=SetDmaSize.nUART4-length;				    								//设定缓冲区大小减剩余缓冲区大小得到实际接收到的数据个数
						memcpy(RevBuffer,uRx4Addr,length);													//复制指定大小的数据
						
						//------重新指向接收缓冲区地址并使能DMA接收			
						DMA2_Channel3->CMAR=(u32)uRx4Addr;							//重新设置DMA接收地址
						DMA2_Channel3->CNDTR=SetDmaSize.nUART4;		    	//重新设置接收数据个数
						DMA2_Channel3->CCR |=(u32)0x00000001;						//DMA_Cmd(DMA2_Channel3,ENABLE);//DMA接收开启3						
						return length;			//返回接收到的数据个数
					}			
					break;
			case UART5_BASE:
					//UART5不支持DMA
					return 0;
		default:break;
	}
	return 0;
}

/*******************************************************************************
*函数名		: function
*功能描述	:	串口接收服务函数
*输入			: 
*输出			:	无
*返回值		:	无
*例程			:	USART_DMASend(USART2,"中文ENG=%d\n",num);
*特别说明	:	在DMA发送完成后需要释放动态空间，free(USART_BUFFER);
					:	USART_BUFFER定义在STM32_USART.H
*******************************************************************************/
u16 USART_DMAPrintf(USART_TypeDef* USARTx,const char *format,...)		//后边的省略号就是可变参数
{
	
//		va_list ap; 										//VA_LIST 是在C语言中解决变参问题的一组宏，所在头文件：#include <stdarg.h>,用于获取不确定个数的参数
//    static char string[ 256 ];			//定义数组，
//    va_start( ap, format );
//    vsprintf( string , format, ap );    
//    va_end( ap );
	
	
//8)**********将等发送缓冲区大小（数据个数）及缓冲区地址发给DMA开启发送
//8)**********DMA发送完成后注意应该释放缓冲区：free(USART_BUFFER);
//	if(DMAPrintf_Buffer!=NULL)
//	{
//		free(DMAPrintf_Buffer);						//释放动态空间
//	}
//	u8	*USART_BUFFER;
	//1)**********获取数据宽度
//	u32 num=strlen((const char*)format);		//获取数据宽度
	//2)**********定义缓冲区大小变量
	unsigned int BufferSize=0;
	unsigned char DMAPrintf_Buffer[256]={0};
	//3)**********args为定义的一个指向可变参数的变量，va_list以及下边要用到的va_start,va_end都是是在定义，可变参数函数中必须要用到宏， 在stdarg.h头文件中定义
	va_list args;  
//	free(DMAPrintf_Buffer);						//释放动态空间
//	DMAPrintf_Buffer=NULL;
	//4)**********申请动态空间
//	DMAPrintf_Buffer = (char*)malloc(sizeof(char) * num);	
	//5)**********初始化args的函数，使其指向可变参数的第一个参数，format是可变参数的前一个参数
	va_start(args, format);
	//6)**********正常情况下返回生成字串的长度(除去\0),错误情况返回负值
	BufferSize = vsprintf((char*)DMAPrintf_Buffer, format, args);
	//7)**********结束可变参数的获取
	va_end(args); 
	//8)**********将等发送缓冲区大小（数据个数）及缓冲区地址发给DMA开启发送
	//8)**********DMA发送完成后注意应该释放缓冲区：free(USART_BUFFER);

  BufferSize=USART_DMASend(USARTx,(u8*)DMAPrintf_Buffer,BufferSize);	//串口DMA发送程序

	return BufferSize;			//返回发送数据大小
}
/*******************************************************************************
*函数名		: function
*功能描述	:	串口接收服务函数
*输入			: 
*输出			:	无
*返回值		:	无
*例程			:	USART_DMASend(USART2,"中文ENG=%d\n",num);
*特别说明	:	在DMA发送完成后需要释放动态空间，free(USART_BUFFER);
					:	USART_BUFFER定义在STM32_USART.H
*******************************************************************************/
u16 USART_DMAPrintfList(USART_TypeDef* USARTx,const char *format,...)		//后边的省略号就是可变参数
{
	
//		va_list ap; 										//VA_LIST 是在C语言中解决变参问题的一组宏，所在头文件：#include <stdarg.h>,用于获取不确定个数的参数
//    static char string[ 256 ];			//定义数组，
//    va_start( ap, format );
//    vsprintf( string , format, ap );    
//    va_end( ap );
	

	//1)**********获取数据宽度
	//2)**********定义缓冲区大小变量
	unsigned int BufferSize=0;
	unsigned char DMAPrintf_Buffer[256]={0};
	//3)**********args为定义的一个指向可变参数的变量，va_list以及下边要用到的va_start,va_end都是是在定义，可变参数函数中必须要用到宏， 在stdarg.h头文件中定义
	va_list args;  
//	free(DMAPrintf_Buffer);						//释放动态空间
//	DMAPrintf_Buffer=NULL;
	//4)**********申请动态空间
//	DMAPrintf_Buffer = (char*)malloc(sizeof(char) * num);	
	//5)**********初始化args的函数，使其指向可变参数的第一个参数，format是可变参数的前一个参数
	va_start(args, format);
	//6)**********正常情况下返回生成字串的长度(除去\0),错误情况返回负值
	BufferSize = vsprintf((char*)DMAPrintf_Buffer, format, args);
	//7)**********结束可变参数的获取
	va_end(args); 
	//8)**********将等发送缓冲区大小（数据个数）及缓冲区地址发给DMA开启发送
	//8)**********DMA发送完成后注意应该释放缓冲区：free(USART_BUFFER);

  BufferSize=USART_DMASendList(USARTx,(u8*)DMAPrintf_Buffer,BufferSize);	//串口DMA发送程序

	return BufferSize;			//返回发送数据大小
}
/*******************************************************************************
*函数名			:	USART_DMASend
*功能描述		:	串口DMA发送程序，如果数据已经传入到DMA，返回Buffer大小，否则返回0
*输入				: 
*返回值			:	如果数据已经传入到DMA，返回Buffer大小，否则返回0（发送器忙）
*******************************************************************************/
u16 USART_DMASend(
									USART_TypeDef* USARTx,									//串口号--USART1,USART2,USART3,UART4;//UART5不支持DMA
									u8 *tx_buffer,													//待发送数据缓冲区地址
									u16 BufferSize													//设定发送数据大小
)		//串口DMA发送程序
{
	switch(*(u32*)&USARTx)
	{
		case USART1_BASE:
					if(
							(DMA1_Channel4->CNDTR==0)								  //通道空闲--已发完数据
						||((DMA1_Channel4->CCR&0x00000001)==0)				//通道未开启
						)
					{
            if(SET  ==  USART_GetFlagStatus(USART1,USART_FLAG_TC))    //发送完成
            {
							memcpy(uTx1Addr,tx_buffer,BufferSize);
              USART_ClearFlag(USART1, USART_FLAG_TC);
              DMA1_Channel4->CCR    &= (u32)0xFFFFFFFE;				//DMA_Cmd(DMA1_Channel4,DISABLE);//DMA发送关闭，只能在DMA关闭情况下才可以写入CNDTR					
              DMA1->IFCR            =   DMA1_FLAG_GL4;				//DMA_ClearFlag(DMA1_FLAG_TC4);	//清除标志						
              DMA1_Channel4->CNDTR 	=   BufferSize;					  //设定待发送缓冲区大小
              DMA1_Channel4->CMAR 	=   (u32)uTx1Addr;			  //发送缓冲区
              DMA1_Channel4->CCR    |=  (u32)0x00000001;			//DMA_Cmd(DMA1_Channel4,ENABLE);//DMA发送开启3
              return BufferSize;
            }
					}
			break;
			case USART2_BASE:
					if(
							(DMA1_Channel7->CNDTR==0)										//通道空闲--已发完数据
						||((DMA1_Channel7->CCR&0x00000001)==0)				//通道未开启
						)
					{
            if(SET  ==  USART_GetFlagStatus(USART2,USART_FLAG_TC))    //发送完成
            {
							memcpy(uTx2Addr,tx_buffer,BufferSize);
              USART_ClearFlag(USART2, USART_FLAG_TC);
              DMA1_Channel7->CCR &= (u32)0xFFFFFFFE;				//DMA_Cmd(DMA1_Channel7,DISABLE);//DMA发送关闭，只能在DMA关闭情况下才可以写入CNDTR					
              DMA1->IFCR = DMA1_FLAG_GL7;										//DMA_ClearFlag(DMA1_FLAG_TC7);	//清除标志						
              DMA1_Channel7->CNDTR 	=BufferSize;						    //设定待发送缓冲区大小
              DMA1_Channel7->CMAR 	=(u32)uTx2Addr;				  //发送缓冲区
              DMA1_Channel7->CCR |=(u32)0x00000001;					//DMA_Cmd(DMA1_Channel7,ENABLE);//DMA发送开启3
              return BufferSize;
            }
          }
			break;
			case USART3_BASE:
					if(
							(DMA1_Channel2->CNDTR==0)										//通道空闲--已发完数据
						||((DMA1_Channel2->CCR&0x00000001)==0)				//通道未开启
						)
					{
            if(SET  ==  USART_GetFlagStatus(USART3,USART_FLAG_TC))    //发送完成
            {
							memcpy(uTx3Addr,tx_buffer,BufferSize);
              USART_ClearFlag(USART3, USART_FLAG_TC);
              DMA1_Channel2->CCR &= (u32)0xFFFFFFFE;				//DMA_Cmd(DMA1_Channel2,DISABLE);//DMA发送关闭，只能在DMA关闭情况下才可以写入CNDTR					
              DMA1->IFCR = DMA1_FLAG_GL2;										//DMA_ClearFlag(DMA1_FLAG_TC2);	//清除标志						
              DMA1_Channel2->CNDTR 	=BufferSize;						//设定待发送缓冲区大小
              DMA1_Channel2->CMAR 	=(u32)uTx3Addr;				//发送缓冲区
              DMA1_Channel2->CCR |=(u32)0x00000001;					//DMA_Cmd(DMA1_Channel2,ENABLE);//DMA发送开启3
              return BufferSize;
            }
					}
			break;
			case UART4_BASE:
					if(
							(DMA2_Channel5->CNDTR==0)										//通道空闲--已发完数据
						||((DMA2_Channel5->CCR&0x00000001)==0)				//通道未开启
						)
					{
            if(SET  ==  USART_GetFlagStatus(UART4,USART_FLAG_TC))    //发送完成
            {
							memcpy(uTx4Addr,tx_buffer,BufferSize);
              USART_ClearFlag(UART4, USART_FLAG_TC);
              DMA2_Channel5->CCR &= (u32)0xFFFFFFFE;				//DMA_Cmd(DMA1_Channel2,DISABLE);//DMA发送关闭，只能在DMA关闭情况下才可以写入CNDTR					
              DMA2->IFCR = DMA2_FLAG_GL5;										//DMA_ClearFlag(DMA2_FLAG_TC5);	//清除标志						
              DMA2_Channel5->CNDTR 	=BufferSize;						//设定待发送缓冲区大小
              DMA2_Channel5->CMAR 	=(u32)uTx4Addr;				//发送缓冲区
              DMA2_Channel5->CCR |=(u32)0x00000001;					//DMA_Cmd(DMA2_Channel5,ENABLE);//DMA发送开启3
              return BufferSize;
            }
					}
			break;
			case UART5_BASE:
					//UART5不支持DMA
					return 0;
		default:break;
	}	
	return 0;
}
/*******************************************************************************
*函数名			:	USART_DMASend
*功能描述		:	串口DMA链表发送程序，如果数据已经传入到DMA，返回Buffer大小，否则数据存入链表
*输入				: 
*返回值			:	如果数据已经传入到DMA，返回Buffer大小，否则返回0（发送器忙）
*******************************************************************************/
u16 USART_DMASendList(
									USART_TypeDef* USARTx,									//串口号--USART1,USART2,USART3,UART4;//UART5不支持DMA
									u8 *tx_buffer,													//待发送数据缓冲区地址
									u16 BufferSize													//设定发送数据大小
)		//串口DMA发送程序
{
//	if(BufferSize>uTxSize)	//防止内存溢出
//		BufferSize	=	uTxSize;
	switch(*(u32*)&USARTx)
	{
		case USART1_BASE:
					//检查USART有无配置
					if((u16)(USARTx->CR1 &0x2000)!= 0x2000)					//串口未配置
					{
						USART_DMA_ConfigurationNR	(USART1,uBaudRate,uRxSize);	//USART_DMA配置--查询方式，不开中断
					}
					if(
							(DMA1_Channel4->CNDTR==0)										//通道空闲--已发完数据
						||((DMA1_Channel4->CCR&0x00000001)==0)				//通道未开启
						)
					{            
            if(NULL ==  uTxLink1)
            {
//              if(NULL !=  uTx1Addr)
//                free(uTx1Addr);
//              uTx1Addr  = (unsigned char*)malloc((unsigned int)BufferSize);
//              if(NULL ==  uTx1Addr)   //内存申请失败
//              {
//                return 0;
//              }
              memcpy(uTx1Addr,tx_buffer,BufferSize);
              DMA1_Channel4->CCR &= (u32)0xFFFFFFFE;				//DMA_Cmd(DMA1_Channel4,DISABLE);//DMA发送关闭，只能在DMA关闭情况下才可以写入CNDTR					
              DMA1->IFCR = DMA1_FLAG_GL4;										//DMA_ClearFlag(DMA1_FLAG_TC4);	//清除标志						
              DMA1_Channel4->CNDTR 	=BufferSize;						    //设定待发送缓冲区大小
              DMA1_Channel4->CMAR 	=(u32)uTx1Addr;				  //发送缓冲区
              DMA1_Channel4->CCR |=(u32)0x00000001;					//DMA_Cmd(DMA1_Channel4,ENABLE);//DMA发送开启3
              return BufferSize;
            }
            //===========有待发送链表，需要将待发数据加入待发队列等待发送
            else
            {
              unsigned short Result = 0;
              Result  = FIFO_IN(&uTxLink1,(char*)tx_buffer,BufferSize);
              //==========动态空间申请失败，需要发送一部分数据释放缓存
              if(0  ==  Result)
              {
                USART_TxServer(USART1);
                USART_DMASendList(USART1,tx_buffer,BufferSize);
              }
            }
					}
          //===========串口正在发送中：需要将待发数据加入待发队列等待发送
					else
					{
            unsigned short Result = 0;
            Result  = FIFO_IN(&uTxLink1,(char*)tx_buffer,BufferSize);
            if(0  ==  Result)
            {
              USART_TxServer(USART1);
              USART_DMASendList(USART1,tx_buffer,BufferSize);
            }
					}
			break;
			case USART2_BASE:
					//检查USART有无配置
					if((u16)(USARTx->CR1 &0x2000)!= 0x2000)					//串口未打开
					{
						USART_DMA_ConfigurationNR	(USART2,uBaudRate,uRxSize);	//USART_DMA配置--查询方式，不开中断
					}
					if(
							(DMA1_Channel7->CNDTR==0)										//通道空闲--已发完数据
						||((DMA1_Channel7->CCR&0x00000001)==0)				//通道未开启
						)
					{            
            if(NULL ==  uTxLink2)
            {
//              if(NULL !=  uTx2Addr)
//                free(uTx2Addr);
//              uTx2Addr  = (unsigned char*)malloc((unsigned int)BufferSize);
//              if(NULL ==  uTx2Addr)   //内存申请失败
//              {
//                return 0;
//              }
              memcpy(uTx2Addr,tx_buffer,BufferSize);
              DMA1_Channel7->CCR &= (u32)0xFFFFFFFE;				//DMA_Cmd(DMA1_Channel7,DISABLE);//DMA发送关闭，只能在DMA关闭情况下才可以写入CNDTR					
              DMA1->IFCR = DMA1_FLAG_GL7;										//DMA_ClearFlag(DMA1_FLAG_TC7);	//清除标志						
              DMA1_Channel7->CNDTR 	=BufferSize;						    //设定待发送缓冲区大小
              DMA1_Channel7->CMAR 	=(u32)uTx2Addr;				  //发送缓冲区
              DMA1_Channel7->CCR |=(u32)0x00000001;					//DMA_Cmd(DMA1_Channel7,ENABLE);//DMA发送开启3
              return BufferSize;
            }
            //===========有待发送链表，需要将待发数据加入待发队列等待发送
            else
            {
              unsigned short Result = 0;
              Result  = FIFO_IN(&uTxLink2,(char*)tx_buffer,BufferSize);
              //==========动态空间申请失败，需要发送一部分数据释放缓存
              if(0  ==  Result)
              {
                USART_TxServer(USART2);
                USART_DMASendList(USART2,tx_buffer,BufferSize);
              }
            }              
					}
          //===========串口正在发送中：需要将待发数据加入待发队列等待发送
          else
          {
            unsigned short Result = 0;
            Result  = FIFO_IN(&uTxLink2,(char*)tx_buffer,BufferSize);
            if(0  ==  Result)
            {
              USART_TxServer(USART2);
              USART_DMASendList(USART2,tx_buffer,BufferSize);
            }
          }
			break;
			case USART3_BASE:
					//检查USART有无配置
					if((u16)(USARTx->CR1 &0x2000)!= 0x2000)					//串口未打开
					{
						USART_DMA_ConfigurationNR	(USART3,uBaudRate,uRxSize);	//USART_DMA配置--查询方式，不开中断
					}
					if(
							(DMA1_Channel2->CNDTR==0)										//通道空闲--已发完数据
						||((DMA1_Channel2->CCR&0x00000001)==0)				//通道未开启
						)
					{
            if(NULL ==  uTxLink3)
            {
//              if(NULL !=  uTx3Addr)
//                free(uTx3Addr);
//              uTx3Addr  = (unsigned char*)malloc((unsigned int)BufferSize);
//              if(NULL ==  uTx3Addr)   //内存申请失败
//              {
//                return 0;
//              }
              memcpy(uTx3Addr,tx_buffer,BufferSize);
              DMA1_Channel2->CCR &= (u32)0xFFFFFFFE;				//DMA_Cmd(DMA1_Channel2,DISABLE);//DMA发送关闭，只能在DMA关闭情况下才可以写入CNDTR					
              DMA1->IFCR = DMA1_FLAG_GL2;										//DMA_ClearFlag(DMA1_FLAG_TC2);	//清除标志						
              DMA1_Channel2->CNDTR 	=BufferSize;						//设定待发送缓冲区大小
              DMA1_Channel2->CMAR 	=(u32)uTx3Addr;				//发送缓冲区
              DMA1_Channel2->CCR |=(u32)0x00000001;					//DMA_Cmd(DMA1_Channel2,ENABLE);//DMA发送开启3
              return BufferSize;
            }
            //===========有待发送链表，需要将待发数据加入待发队列等待发送
            else
            {
              unsigned short Result = 0;
              Result  = FIFO_IN(&uTxLink3,(char*)tx_buffer,BufferSize);
              //==========动态空间申请失败，需要发送一部分数据释放缓存
              if(0  ==  Result)
              {
                USART_TxServer(USART3);
                USART_DMASendList(USART3,tx_buffer,BufferSize);
              }
            }
					}
          //===========串口正在发送中：需要将待发数据加入待发队列等待发送
					else
					{
            unsigned short Result = 0;
            Result  = FIFO_IN(&uTxLink3,(char*)tx_buffer,BufferSize);
            if(0  ==  Result)
            {
              USART_TxServer(USART3);
              USART_DMASendList(USART3,tx_buffer,BufferSize);
            }
					}
			break;
			case UART4_BASE:
					//检查USART有无配置
					if((u16)(USARTx->CR1 &0x2000)!= 0x2000)					//串口未打开
					{
						USART_DMA_ConfigurationNR	(UART4,uBaudRate,uRxSize);	//USART_DMA配置--查询方式，不开中断
					}
					if(
							(DMA2_Channel5->CNDTR==0)										//通道空闲--已发完数据
						||((DMA2_Channel5->CCR&0x00000001)==0)				//通道未开启
						)
					{
            if(NULL ==  uTxLink4)
            {
//              if(NULL !=  uTx4Addr)
//                free(uTx4Addr);
//              uTx4Addr  = (unsigned char*)malloc((unsigned int)BufferSize);
//              if(NULL ==  uTx4Addr)   //内存申请失败
//              {
//                return 0;
//              }
              memcpy(uTx4Addr,tx_buffer,BufferSize);
              DMA2_Channel5->CCR &= (u32)0xFFFFFFFE;				//DMA_Cmd(DMA1_Channel2,DISABLE);//DMA发送关闭，只能在DMA关闭情况下才可以写入CNDTR					
              DMA2->IFCR = DMA2_FLAG_GL5;										//DMA_ClearFlag(DMA2_FLAG_TC5);	//清除标志						
              DMA2_Channel5->CNDTR 	=BufferSize;						//设定待发送缓冲区大小
              DMA2_Channel5->CMAR 	=(u32)uTx4Addr;				//发送缓冲区
              DMA2_Channel5->CCR |=(u32)0x00000001;					//DMA_Cmd(DMA2_Channel5,ENABLE);//DMA发送开启3
              return BufferSize;
            }
            //===========有待发送链表，需要将待发数据加入待发队列等待发送
            else
            {
              unsigned short Result = 0;
              Result  = FIFO_IN(&uTxLink4,(char*)tx_buffer,BufferSize);
              //==========动态空间申请失败，需要发送一部分数据释放缓存
              if(0  ==  Result)
              {
                USART_TxServer(UART4);
                USART_DMASendList(UART4,tx_buffer,BufferSize);
              }
            }
					}
          //===========串口正在发送中：需要将待发数据加入待发队列等待发送
					else
					{
            unsigned short Result = 0;
            Result  = FIFO_IN(&uTxLink4,(char*)tx_buffer,BufferSize);
            if(0  ==  Result)
            {
              USART_TxServer(UART4);
              USART_DMASendList(UART4,tx_buffer,BufferSize);
            }
					}
			break;
			case UART5_BASE:
					//UART5不支持DMA
					return 0;
		default:break;
	}	
	return 0;
}
/*******************************************************************************
*函数名			:	USART_DMASend
*功能描述		:	串口状态检查--检查DMA缓存大小判断使用状态
*输入				: 
*返回值			:	
*******************************************************************************/
USARTStatusDef	USART_Status(USART_TypeDef* USARTx)		//串口状态检查
{
  unsigned short	BufferSize	=	0;			//剩余缓存大小
  
	USARTStatusDef	Status;
	FlagStatus bitstatus = RESET;
  
  Status.USART_IDLESTD  = 0;
	
	switch(*(u32*)&USARTx)
	{
		case USART1_BASE:
				//接收状态检查
				BufferSize	=	DMA1_Channel5->CNDTR;		      //获取DMA接收缓存剩余空间
				if(BufferSize<SetDmaSize.nUSART1)	          //可用缓存小于预设大小，表示已使用
				{
					if(RemaDmaSize.nUSART1	== BufferSize)    //查询可用缓存大小是否继续在变化从而判断是否还在接收中
					{
						RetryCount.nUSART1++;
						if(RetryCount.nUSART1>=5)               //连续5次查询未变化表示接收完成
						{
							RetryCount.nUSART1	  =	0;
              Status.USART_IDLESTD  = 0;            //空闲
						}
					}
          //还在接收中
					else
					{
						RemaDmaSize.nUSART1		=	BufferSize;   	//更新
            Status.USART_IDLESTD  = 1;             	//非空闲
            Status.USART_ReceSTD  = 1;           		//正在接收中
					}					
				}
				//发送状态检查
				if((DMA1_Channel4->CNDTR!=0)&&((DMA1_Channel4->CCR&0x00000001)!=0))   //还在发送中
				{
          Status.USART_IDLESTD  = 1;        //非空闲
          Status.USART_SendSTD  = 1;        //正在发送中
				}
				else
				{
					bitstatus	=	USART_GetFlagStatus(USART1,USART_FLAG_TC);		//检测发送数据寄存器是否为空	RESET-非空，SET-空，
					if(bitstatus	!=	SET)
          {
						Status.USART_IDLESTD  = 1;        //非空闲
            Status.USART_SendSTD  = 1;        //正在发送中            
          }
          else
          {
            Status.USART_IDLESTD  = 0;        //空闲
          }
				}
				break;
		case USART2_BASE:
				//接收状态检查
				BufferSize	=	DMA1_Channel6->CNDTR;		//获取DMA接收缓存剩余空间
				if(BufferSize<SetDmaSize.nUSART2)	    //缓存在减小，表示在使用
				{
					if(RemaDmaSize.nUSART2	== BufferSize)
					{
						RetryCount.nUSART2++;
						if(RetryCount.nUSART2>=2)
						{
							RetryCount.nUSART2	=	0;
							Status.USART_IDLESTD  = 0;        //空闲
						}
					}
					else
					{
						RemaDmaSize.nUSART2	=	BufferSize;
						Status.USART_IDLESTD  = 1;        //非空闲
            Status.USART_ReceSTD  = 1;        //正在接收中
						return Status;
					}
				}
				//发送状态检查
				if((DMA1_Channel7->CNDTR!=0)&&((DMA1_Channel7->CCR&0x00000001)!=0))
				{
					Status.USART_IDLESTD  = 1;        //非空闲
          Status.USART_SendSTD  = 1;        //正在发送中
				}
				else
				{
					bitstatus	=	USART_GetFlagStatus(USART2,USART_FLAG_TC);		//检测发送数据寄存器是否为空	RESET-非空，SET-空，
					if(bitstatus	!=	SET)
					{
						Status.USART_IDLESTD  = 1;        //非空闲
            Status.USART_SendSTD  = 1;        //正在发送中            
          }
          else
          {
						Status.USART_SendSTD	=	0;
            Status.USART_IDLESTD  =	0;        //空闲
          }
				}
				break;
		case USART3_BASE:
				//接收状态检查
				BufferSize	=	DMA1_Channel3->CNDTR;		//获取DMA接收缓存剩余空间
				if(BufferSize<SetDmaSize.nUSART3)	    //缓存在减小，表示在使用
				{
					if(RemaDmaSize.nUSART3	== BufferSize)
					{
						RetryCount.nUSART3++;
						if(RetryCount.nUSART3>=5)
						{
							RetryCount.nUSART3	=	0;
							Status.USART_IDLESTD  = 0;        //空闲
						}
					}
					else
					{
						RemaDmaSize.nUSART3	=	BufferSize;
						Status.USART_IDLESTD  = 1;        //非空闲
            Status.USART_ReceSTD  = 1;        //正在接收中
						return Status;
					}
				}
				//发送状态检查
				if((DMA1_Channel2->CNDTR!=0)&&((DMA1_Channel2->CCR&0x00000001)!=0))
				{
					Status.USART_IDLESTD  = 1;        //非空闲
          Status.USART_SendSTD  = 1;        //正在发送中
				}
				else
				{
					bitstatus	=	USART_GetFlagStatus(USART3,USART_FLAG_TC);		//检测发送数据寄存器是否为空	RESET-非空，SET-空，
					if(bitstatus	!=	SET)
					{
						Status.USART_IDLESTD  = 1;        //非空闲
            Status.USART_SendSTD  = 1;        //正在发送中            
          }
          else
          {
            Status.USART_IDLESTD  = 0;        //空闲
          }
				}
				break;
		case UART4_BASE:
				//接收状态检查
				BufferSize	=	DMA2_Channel3->CNDTR;		//获取DMA接收缓存剩余空间
				if(BufferSize<SetDmaSize.nUART4)	    //缓存在减小，表示在使用
				{
					if(RemaDmaSize.nUART4	== BufferSize)
					{
						RetryCount.nUART4++;
						if(RetryCount.nUART4>=5)
						{
							RetryCount.nUART4	=	0;
							Status.USART_IDLESTD  = 0;        //空闲
						}
					}
					else
					{
						RemaDmaSize.nUART4	=	BufferSize;
						Status.USART_IDLESTD  = 1;        //非空闲
            Status.USART_ReceSTD  = 1;        //正在接收中
					}
				}
				//发送状态检查
				if((DMA2_Channel5->CNDTR!=0)&&((DMA2_Channel5->CCR&0x00000001)!=0))
				{
					Status.USART_IDLESTD  = 1;        //非空闲
          Status.USART_SendSTD  = 1;        //正在发送中
				}
				else
				{
					bitstatus	=	USART_GetFlagStatus(UART4,USART_FLAG_TC);		//检测发送数据寄存器是否为空	RESET-非空，SET-空，
					if(bitstatus	!=	SET)
					{
						Status.USART_IDLESTD  = 1;        //非空闲
            Status.USART_SendSTD  = 1;        //正在发送中            
          }
          else
          {
            Status.USART_IDLESTD  = 0;        //空闲
          }
				}
				break;
		default:break;
	}
	return Status;
}
//----------------------RS485---------------------------------------------------------------------------
/*******************************************************************************
*函数名			:	RS485_TX_EN
*功能描述		:	使能RS485发送---拉高控制脚
*输入				: 
*返回值			:	无
*******************************************************************************/
void RS485_TX_EN(RS485Def *pRS485)
{
	pRS485->RS485_CTL_PORT->BSRR		= pRS485->RS485_CTL_Pin;
//	GPIO_SetBits(RS485_Info->RS485_CTL_PORT,RS485_Info->RS485_CTL_Pin);
}
/*******************************************************************************
*函数名			:	RS485_RX_EN
*功能描述		:	使能RS485接收---拉低控制脚,使能前需要检测发送状态，如果在发送中，则不使能，
*输入				: 
*返回值			:	已经设置为接收状态返回1，否则返回0
*******************************************************************************/
void RS485_RX_EN(RS485Def *pRS485)
{
	pRS485->RS485_CTL_PORT->BRR 		= pRS485->RS485_CTL_Pin;	
}

/*******************************************************************************
*函数名			:	USART_DMA_ConfigurationNr
*功能描述		:	USART_DMA配置--查询方式，不开中断,配置完默认为接收状态
*输入				: 
*返回值			:	无
*******************************************************************************/
void	RS485_DMA_ConfigurationNR(
																RS485Def *pRS485,	//包含RS485选用的串口号和收发控制脚信息
																u32 USART_BaudRate,					//波特率
																u16 BufferSize							//设定接收缓冲区大小
)	//USART_DMA配置--查询方式，不开中断,配置完默认为接收状态
{
  GPIO_Configuration_OPP50	(pRS485->RS485_CTL_PORT,pRS485->RS485_CTL_Pin);			//将GPIO相应管脚配置为APP(复用推挽)输出模式，最大速度50MHz----V20170605
	pRS485->RS485_CTL_PORT->BRR 		= pRS485->RS485_CTL_Pin;				//RS485接收开启
	USART_DMA_ConfigurationNR	(pRS485->USARTx,USART_BaudRate,BufferSize);		//USART_DMA配置--查询方式，不开中断
	GPIO_Configuration_OPP50	(pRS485->RS485_CTL_PORT,pRS485->RS485_CTL_Pin);			//将GPIO相应管脚配置为APP(复用推挽)输出模式，最大速度50MHz----V20170605
	pRS485->RS485_CTL_PORT->BRR 		= pRS485->RS485_CTL_Pin;				//RS485接收开启
}
/*******************************************************************************
*函数名			:	USART_DMA_ConfigurationNr
*功能描述		:	USART_DMA配置--查询方式，不开中断,配置完默认为接收状态
*输入				: 
*返回值			:	无
*******************************************************************************/
void	RS485_DMA_ConfigurationNRRemap(
																RS485Def *pRS485,	//包含RS485选用的串口号和收发控制脚信息
																u32 USART_BaudRate,					//波特率
																u32 *RXDBuffer,							//接收缓冲区地址::发送缓冲区地址在发送数据时设定，串口配置时借用接收缓冲区地址
																u32 BufferSize							//设定接收缓冲区大小
)	//USART_DMA配置--查询方式，不开中断,配置完默认为接收状态
{
	USART_DMA_ConfigurationNRRemap	(pRS485->USARTx,USART_BaudRate,RXDBuffer,BufferSize);		//USART_DMA配置--查询方式，不开中断
	GPIO_Configuration_OPP50				(pRS485->RS485_CTL_PORT,pRS485->RS485_CTL_Pin);			//将GPIO相应管脚配置为APP(复用推挽)输出模式，最大速度50MHz----V20170605
	pRS485->RS485_CTL_PORT->BRR 		= pRS485->RS485_CTL_Pin;				//RS485接收开启
}
/*******************************************************************************
*函数名			:	RS485_ReadBufferIDLE
*功能描述		:	串口空闲模式读串口接收缓冲区，如果有数据，将数据拷贝到RevBuffer,并返回接收到的数据个数，然后重新将接收缓冲区地址指向RxdBuffer
*输入				: 
*返回值			:	无
*******************************************************************************/
u16	RS485_ReadBufferIDLE(
												RS485Def *pRS485,	//包含RS485选用的串口号和收发控制脚信息
												u8 *RevBuffer								//数据保存缓冲区地址，如果串口的接收到数据，将数据拷贝到RevBuffer
)	//串口空闲模式读串口接收缓冲区，如果有数据，将数据拷贝到RevBuffer,并返回接收到的数据个数，然后重新将接收缓冲区地址指向RxdBuffer，
{
	u16 length=0;
	USARTStatusDef	Status;
	Status	=	USART_Status(pRS485->USARTx);		//串口状态检查	
	if(0  ==  Status.USART_IDLESTD)		//bit[0] 0-串口空闲；1-串口非空闲，状态根据以下位定义
	{
		RS485_RX_EN(pRS485);
		length=USART_ReadBufferIDLE(pRS485->USARTx,RevBuffer);	//串口空闲模式读串口接收缓冲区，如果有数据，将数据拷贝到RevBuffer,并返回接收到的数据个数，然后重新将接收缓冲区地址指向RxdBuffer
	}
	return length;
}

/*******************************************************************************
*函数名			:	function
*功能描述		:	函数功能说明
*输入				: 
*返回值			:	无
*******************************************************************************/
u16	RS485_DMAPrintf(RS485Def *pRS485,const char *format,...)						//自定义printf串口DMA发送程序,后边的省略号就是可变参数
{
		
//		va_list ap; 										//VA_LIST 是在C语言中解决变参问题的一组宏，所在头文件：#include <stdarg.h>,用于获取不确定个数的参数
//    static char string[ 256 ];			//定义数组，
//    va_start( ap, format );
//    vsprintf( string , format, ap );    
//    va_end( ap );
	
//8)**********将等发送缓冲区大小（数据个数）及缓冲区地址发给DMA开启发送
//8)**********DMA发送完成后注意应该释放缓冲区：free(USART_BUFFER);
//	if(DMAPrintf_Buffer!=NULL)
//	{
//		free(DMAPrintf_Buffer);						//释放动态空间
//	}
//	u8	*USART_BUFFER;
	//1)**********获取数据宽度
	u32 num=strlen((const char*)format);		//获取数据宽度
	//2)**********定义缓冲区大小变量
	unsigned int BufferSize;
	unsigned char DMAPrintf_Buffer[256]={0};
	//3)**********args为定义的一个指向可变参数的变量，va_list以及下边要用到的va_start,va_end都是是在定义，可变参数函数中必须要用到宏， 在stdarg.h头文件中定义
	va_list args;  
	free(DMAPrintf_Buffer);						//释放动态空间
//	DMAPrintf_Buffer=NULL;
	//4)**********申请动态空间
//	DMAPrintf_Buffer = (char*)malloc(sizeof(char) * num);	
	//5)**********初始化args的函数，使其指向可变参数的第一个参数，format是可变参数的前一个参数
	va_start(args, format);
	//6)**********正常情况下返回生成字串的长度(除去\0),错误情况返回负值
	BufferSize = vsprintf((char*)DMAPrintf_Buffer, format, args);
	//7)**********结束可变参数的获取
	va_end(args); 
	//8)**********将等发送缓冲区大小（数据个数）及缓冲区地址发给DMA开启发送
	//8)**********DMA发送完成后注意应该释放缓冲区：free(USART_BUFFER);
	BufferSize=RS485_DMASend(pRS485,(u8*)DMAPrintf_Buffer,BufferSize);	//RS485-DMA发送程序
	return BufferSize;			//返回发送数据大小

}
/*******************************************************************************
*函数名			:	USART_DMASend
*功能描述		:	串口DMA发送程序，如果数据已经传入到DMA，返回Buffer大小，否则返回0
*输入				: 
*返回值			:	如果数据已经传入到DMA，返回Buffer大小，否则返回0（发送器忙）
*******************************************************************************/
u16 RS485_DMASend(
									RS485Def *pRS485,		//包含RS485选用的串口号和收发控制脚信息
									u8 *tx_buffer,								//待发送数据缓冲区地址
									u16 BufferSize								//设定发送数据大小
)		//RS485-DMA发送程序
{
	//----发送前检查相关串口发送状态，如果下在发送其它数据，则等待（返回0），否则清除相关标志位后开启发送
	
//	u32	DMA_status=0;			//DMA状态
  unsigned short sendedlen  =0;
	USARTStatusDef	Status;
	USART_TypeDef* USARTx=pRS485->USARTx;
	
	Status	=	USART_Status(USARTx);		//串口状态检查
	if(1  ==  Status.USART_IDLESTD)   //bit[0] 0-串口空闲；1-串口非空闲，状态根据以下位定义
	{
		return sendedlen;
	}
//	SysTick_DeleymS(1);				//SysTick延时nmS
	RS485_TX_EN(pRS485);
//	USART_DMASend	(USARTx,(u8*)tx_buffer,BufferSize);		//串口DMA发送程序
	sendedlen = USART_DMASend(USARTx,(u8*)tx_buffer,BufferSize);		//串口DMA发送程序
	return sendedlen;
}




/*******************************************************************************
*函数名			:	USART_ConfigurationIT
*功能描述		:	USART_配置---常规中断方式
*输入				: 
*返回值			:	无
*修改时间		:	2018/01/06
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
void	USART_ConfigurationIT(
																USART_TypeDef* USARTx,			//串口号--USART1,USART2,USART3,UART4;//UART5不支持DMA
																u32 USART_BaudRate,					//波特率
																u8 PreemptionPriority,			//中断优先级
																u8 SubPriority							//抢占优先级
)	//USART_DMA配置--查询方式，不开中断--奇校验
{
	//1)**********定义变量	

	NVIC_InitTypeDef NVIC_InitStructure;
	USART_InitTypeDef USART_InitStructure;				//USART结构体	
	GPIO_InitTypeDef GPIO_InitStructure;					//GPIO结构体

	
	u16 TXD_Pin=0;																//串口发送脚
	u16 RXD_Pin=0;																//串口接收脚
	GPIO_TypeDef* GPIO_TX=0;
	GPIO_TypeDef* GPIO_RX=0;
	
	u8 USARTx_IRQChannel=0;
	//2)******************************配置相关GPIO/串口时钟打开
	//2.1)**********USART1
	if(USARTx==USART1)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);				//关闭AFIO时钟,为关闭JTAG功能
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);	//USART1时钟开启
		
		TXD_Pin=GPIO_Pin_9;											//USART1-TX>PA9
		RXD_Pin=GPIO_Pin_10;										//USART1-RX>PA10
		
		GPIO_TX=GPIOA;
		GPIO_RX=GPIOA;
		
		USARTx_IRQChannel=USART1_IRQChannel;		//中断
		

	}
	//2.2)**********USART2
	else if(USARTx==USART2)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);				//关闭AFIO时钟,为关闭JTAG功能
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);	//USART1时钟开启
		
		TXD_Pin=GPIO_Pin_2;		//USART2-TX>PA2
		RXD_Pin=GPIO_Pin_3;		//USART2-RX>PA3
		
		GPIO_TX=GPIOA;
		GPIO_RX=GPIOA;
		
		USARTx_IRQChannel=USART2_IRQChannel;		//中断
	}
	//2.3)**********USART3
	else if(USARTx==USART3)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);				//关闭AFIO时钟,为关闭JTAG功能
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);	//USART1时钟开启
		GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);  //关闭JTAG功能
		
		TXD_Pin=GPIO_Pin_10;	//USART3-TX>PB10
		RXD_Pin=GPIO_Pin_11;	//USART3-RX>PB11
		
		GPIO_TX=GPIOB;
		GPIO_RX=GPIOB;
		
		USARTx_IRQChannel=USART3_IRQChannel;		//中断
	}
	//2.4)**********USART4
	else if(USARTx==UART4)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);	//USART1时钟开启
		
		TXD_Pin=GPIO_Pin_10;	//USART1-TX>PC10
		RXD_Pin=GPIO_Pin_11;	//USART1-RX>PC11
		
		GPIO_TX=GPIOC;
		GPIO_RX=GPIOC;
		
		USARTx_IRQChannel=UART4_IRQChannel;		//中断
		
	}
	//2.5)**********USART5
	else if(USARTx==UART5)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE);	//USART1时钟开启
		
		TXD_Pin=GPIO_Pin_12;	//USART1-TX>PC12
		RXD_Pin=GPIO_Pin_2;		//USART1-RX>PD2
		
		GPIO_TX=GPIOC;
		GPIO_RX=GPIOD;
		
		USARTx_IRQChannel=UART5_IRQChannel;		//中断		
	}
	
//	/* Configure the NVIC Preemption Priority Bits */  
//  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	/* Enable the USART2 Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = USARTx_IRQChannel;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority	=	PreemptionPriority;			//中断优先级
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = SubPriority;										//抢占优先级
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
	
	//3)**********初始化串口
	//3.1)**********初始化TXD引脚
	GPIO_InitStructure.GPIO_Pin = TXD_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIO_TX,&GPIO_InitStructure);

	//3.2)**********初始化RXD引脚
	GPIO_InitStructure.GPIO_Pin = RXD_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;							//上拉输入
	GPIO_Init(GPIO_RX,&GPIO_InitStructure);
	
	//3.3)**********初始化串口参数
	USART_DeInit(USARTx);
	USART_InitStructure.USART_BaudRate = USART_BaudRate; 					//波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;		//数据位
	USART_InitStructure.USART_StopBits = USART_StopBits_1;				//停止位
	USART_InitStructure.USART_Parity = USART_Parity_No ; 					//奇偶校验
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//流控
	USART_Init(USARTx, &USART_InitStructure);											//初始化串口
	
	
	
	
	

	/* Enable USART1 Receive and Transmit interrupts */
  USART_ITConfig(USARTx, USART_IT_RXNE, ENABLE);
//  USART_ITConfig(USARTx, USART_IT_TXE, ENABLE);
//	USART_ITConfig(USARTx, USART_IT_TC, ENABLE);
	
//	USART_ClearITPendingBit(USARTx, USART_IT_RXNE);
//	USART_ClearITPendingBit(USARTx, USART_IT_TC);
	
	USART_Cmd(USARTx, ENABLE);

}
/*******************************************************************************
*函数名			:	USART_ConfigurationIT
*功能描述		:	USART_配置---常规中断方式
*输入				: 
*返回值			:	无
*修改时间		:	2018/01/06
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
void	USART_Send(USART_TypeDef* USARTx,u8* TxdBuffer,u16 Lengh)
{
	u8 Temp	=	0;
	u16	Len	=	0;
	while(Len<Lengh)
	{
		while(USART_GetFlagStatus(USARTx, USART_FLAG_TXE)!=SET)
		{			
		}
		Temp=*TxdBuffer;
		USART_SendData(USARTx, Temp);
		TxdBuffer++;
		Len++;
	}
}
/*******************************************************************************
*函数名			:	USART_ConfigurationIT
*功能描述		:	USART_配置---常规中断方式
*输入				: 
*返回值			:	无
*修改时间		:	2018/01/06
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
void	USART_TxServer(USART_TypeDef* USARTx)
{
	switch(*(u32*)&USARTx)
	{
    case  USART1_BASE:
          if((u16)(USARTx->CR1 &0x2000)!= 0x2000)					//串口未配置
          {
            return;
          }
          if(
							(DMA1_Channel4->CNDTR==0)										//通道空闲--已发完数据
						||((DMA1_Channel4->CCR&0x00000001)==0)				//通道未开启
						)
					{
            if(NULL !=  uTxLink1)
            {
              unsigned short 	DataLen;			//存储的数据长度
              free(uTx1Addr);
              DataLen  = FIFO_OUT(&uTxLink1,(char*)uTx1Addr);
              if(0  ==  DataLen)
              {
                return;
              }
              DMA1_Channel4->CCR &= (u32)0xFFFFFFFE;				//DMA_Cmd(DMA1_Channel7,DISABLE);//DMA发送关闭，只能在DMA关闭情况下才可以写入CNDTR					
              DMA1->IFCR = DMA1_FLAG_GL4;										//DMA_ClearFlag(DMA1_FLAG_TC7);	//清除标志						
              DMA1_Channel4->CNDTR 	=DataLen;	                    //设定待发送缓冲区大小
              DMA1_Channel4->CMAR 	=(u32)uTx1Addr;			  //发送缓冲区
              DMA1_Channel4->CCR |=(u32)0x00000001;					//DMA_Cmd(DMA1_Channel7,ENABLE);//DMA发送开启3
            }
					}          
          break;
    case  USART2_BASE:
          if((u16)(USARTx->CR1 &0x2000)!= 0x2000)					//串口未配置
          {
            return;
          }
          if(
							(DMA1_Channel7->CNDTR==0)										//通道空闲--已发完数据
						||((DMA1_Channel7->CCR&0x00000001)==0)				//通道未开启
						)
					{
            if(NULL !=  uTxLink2)
            {
              unsigned short 	DataLen;			//存储的数据长度
              free(uTx2Addr);
              DataLen  = FIFO_OUT(&uTxLink2,(char*)uTx2Addr);
              if(0  ==  DataLen)
              {
                return;
              }
              DMA1_Channel7->CCR &= (u32)0xFFFFFFFE;				//DMA_Cmd(DMA1_Channel7,DISABLE);//DMA发送关闭，只能在DMA关闭情况下才可以写入CNDTR					
              DMA1->IFCR = DMA1_FLAG_GL7;										//DMA_ClearFlag(DMA1_FLAG_TC7);	//清除标志						
              DMA1_Channel7->CNDTR 	=DataLen;	                    //设定待发送缓冲区大小
              DMA1_Channel7->CMAR 	=(u32)uTx2Addr;			  //发送缓冲区
              DMA1_Channel7->CCR |=(u32)0x00000001;					//DMA_Cmd(DMA1_Channel7,ENABLE);//DMA发送开启3
            }
					}          
          break;
    case  USART3_BASE:
          if((u16)(USARTx->CR1 &0x2000)!= 0x2000)					//串口未配置
          {
            return;
          }
          if(
              (DMA1_Channel2->CNDTR==0)										//通道空闲--已发完数据
            ||((DMA1_Channel2->CCR&0x00000001)==0)				//通道未开启
            )
          {
            if(NULL !=  uTxLink3)
            {
              unsigned short 	DataLen;			//存储的数据长度
              free(uTx3Addr);
              DataLen  = FIFO_OUT(&uTxLink3,(char*)uTx3Addr);
              if(0  ==  DataLen)
              {
                return;
              }
              DMA1_Channel2->CCR &= (u32)0xFFFFFFFE;				//DMA_Cmd(DMA1_Channel7,DISABLE);//DMA发送关闭，只能在DMA关闭情况下才可以写入CNDTR					
              DMA1->IFCR = DMA1_FLAG_GL2;										//DMA_ClearFlag(DMA1_FLAG_TC7);	//清除标志						
              DMA1_Channel2->CNDTR 	=DataLen;	                    //设定待发送缓冲区大小
              DMA1_Channel2->CMAR 	=(u32)uTx3Addr;			  //发送缓冲区
              DMA1_Channel2->CCR |=(u32)0x00000001;					//DMA_Cmd(DMA1_Channel7,ENABLE);//DMA发送开启3
            }
          }          
          break;
     case  UART4_BASE:
           if((u16)(USARTx->CR1 &0x2000)!= 0x2000)					//串口未配置
            {
              return;
            }
          if(
              (DMA2_Channel5->CNDTR==0)										//通道空闲--已发完数据
            ||((DMA2_Channel5->CCR&0x00000001)==0)				//通道未开启
            )
          {
            if(NULL !=  uTxLink4)
            {
              unsigned short 	DataLen;			//存储的数据长度
              free(uTx4Addr);
              DataLen  = FIFO_OUT(&uTxLink4,(char*)uTx4Addr);
              if(0  ==  DataLen)
              {
                return;
              }
              DMA2_Channel5->CCR &= (u32)0xFFFFFFFE;				//DMA_Cmd(DMA1_Channel7,DISABLE);//DMA发送关闭，只能在DMA关闭情况下才可以写入CNDTR					
              DMA2->IFCR = DMA2_FLAG_GL5;										//DMA_ClearFlag(DMA1_FLAG_TC7);	//清除标志						
              DMA2_Channel5->CNDTR 	=DataLen;	                    //设定待发送缓冲区大小
              DMA2_Channel5->CMAR 	=(u32)uTx4Addr;			  //发送缓冲区
              DMA2_Channel5->CCR |=(u32)0x00000001;					//DMA_Cmd(DMA1_Channel7,ENABLE);//DMA发送开启3
            }
          }
      case  UART5_BASE:
           if((u16)(USARTx->CR1 &0x2000)!= 0x2000)					//串口未配置
            {
              return;
            }
          break;
    default:break;
  }
}
/*******************************************************************************
*函数名		:USART_RX_Server
*功能描述	:串口接收服务函数
*输入			: 
*输出			:无
*返回值		:无
*例程			：
*******************************************************************************/

void USART_RxServer(USART_TypeDef* USARTx)		//串口接收服务程序	
{

}
/*******************************************************************************
*函数名		:USART_RX_Server
*功能描述	:串口接收服务函数
*输入			: 
*输出			:无
*返回值		:无
*例程			：
*******************************************************************************/

void USART_Process(void)		//串口服务程序	
{
  USART_TxServer(USART1);
  USART_TxServer(USART2);
  USART_TxServer(USART3);
  USART_TxServer(UART4);
  USART_TxServer(UART5);
}


/*******************************************************************************
* 函数名		:	
* 功能描述	:	printf重定义 
* 输入		:	
* 输出		:
* 返回 		:
*******************************************************************************/
int fputc(int ch, FILE *f)				//printf重定义
{

	USART_SendData(USART1, (unsigned char) ch);// USART1 可以换成 USART2 等

	while(!(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == SET));

	return (ch);

}

  
/*******************************************************************************
* 函数名		:	
* 功能描述	:	 
* 输入		:	
* 输出		:
* 返回 		:
*******************************************************************************/
//int fgetc(FILE *f)
//{
// 
//	while(!(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == SET))
//	{
//	}
//	return (USART_ReceiveData(USART1));
//}
/*******************************************************************************
*函数名			:	function
*功能描述		:	function
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	
*******************************************************************************/
unsigned char UART5ReceiveData(unsigned char* RecByte)			//串口5读数据,返回0-无中断，返回1有中断无数据（发送中断），返回2-有中断有接收到数据
{
	//==============================Port5
	if(USART_GetITStatus(UART5, USART_IT_RXNE))
  {
		*RecByte	=	USART_ReceiveData(UART5);
	
		USART_ClearITPendingBit(UART5, USART_IT_RXNE);
		return 2;
	}
	else if(USART_GetITStatus(UART5, USART_IT_TC))
  {   
    USART_ClearITPendingBit(UART5, USART_IT_TC);
		return 1;
  }
	return 0;
}


































