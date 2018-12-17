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

#ifdef PL010V17AMP				//智能药架称重LCD板---单称重

#include "PL010V17AMP.H"

#include	"AMP_PHY.H"

#include "LCD.h"


#include "GT32L32M0180.H"
#include "STM32F10x_BitBand.H"
#include "STM32_GPIO.H"
#include "STM32_SYS.H"
#include "STM32_SYSTICK.H"
#include "STM32_WDG.H"
#include "STM32_PWM.H"
#include "STM32_USART.H"





#include "SWITCHID.H"

#include "string.h"				//串和内存操作函数头文件
#include "stdlib.h"				//串和内存操作函数头文件
#include "stm32f10x_dma.h"




#define	Master	1		//0--从机，1-主机
u16	DelayTime=0x1000;
u16	LCDTime=0;
u16	DSPTime=0;

u8 hour=23,min=15,second=40;
u16 millisecond=0;

//GT32L32Def 	GT32L32;
//char	Char_Buffer[256];		//记录format内码


RS485Def  RS485;

#define	Rs485Size	256
u8 RxdBuffe[Rs485Size]={0};
u8 RevBuffe[Rs485Size]={0};
u8 TxdBuffe[Rs485Size]={0};
u8 RxFlg=0;
u16 RxNum=0;
u32	Rs485_Time	=	0;
u8	SlaveID	=	0;
u32 Rev_ADC	=	0;
u8	Rev_ID	=	0;



SwitchDef	SWITCHID;
u8 SwitchID=0;	//拔码开关地址


LCDDef	sLCD;

double	WenDubac	=	0.0;

//R61509VDef R61509V;
u8	DspFlg	=	0;

u16 BKlight	=	0;

u16 line	=	0;
u8 lineT	=	0;




u32	WeigthARR[100]	=	{0};
u8	DspFlg1	=	0;
u32	We1	=	0;
u8	NuW	=	0;
u32	BsW	=	0;	//空重
u32 SsW	=	0;	//单重
u8	St	=	0;	//步骤
u8	SN	=	0;	//数量
u8	SNb	=	0;	//备存数量
u32 TempData	=	0;		//温度
u32 TempDataB	=	0;		//温度

u16 weighVar[20]={0};
u8	VarN	=	0;

u32 Rand	=	0;
//============LCD驱动调试变量
u16 HX	=	0;
u16	HY	=	0;
unsigned short	Color	=	0;
u8 ADCc	=	0;
u32 READ_GAIN	=	0;
/*******************************************************************************
* 函数名		:	
* 功能描述	:	 
* 输入		:	
* 输出		:
* 返回 		:
*******************************************************************************/
void PL010V17AMP_Configuration(void)
{
	SYS_Configuration();					//系统配置---打开系统时钟 STM32_SYS.H
	
	GPIO_DeInitAll();							//将所有的GPIO关闭----V20170605	
	
	SwitchID_Configuration();
	
	RS485_Configuration();
	
	
//	USART_Configuration();
	
	SysTick_DeleymS(500);				//SysTick延时nmS
	
	LCD_Configuration();
	

	
	
	
	SysTick_Configuration(1000);	//系统嘀嗒时钟配置72MHz,单位为uS
	
//	IWDG_Configuration(500);			//独立看门狗配置---参数单位ms	

//	PWM_OUT(TIM2,PWM_OUTChannel1,1,900);	//PWM设定-20161127版本--运行指示灯

	
	
}
/*******************************************************************************
* 函数名		:	
* 功能描述	:	 
* 输入		:	
* 输出		:
* 返回 		:
*******************************************************************************/
void PL010V17AMP_Server(void)
{	
	IWDG_Feed();				//独立看门狗喂狗
	RS485_Server();		  //通讯管理---负责信息的接收与发送
  if(millisecond++==1000)
  {
    millisecond=1001;
    LCD_Clean(LCD565_LBBLUE);	//清除屏幕函数
  }
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
	RxNum=RS485_ReadBufferIDLE(&RS485,RxdBuffe);	//串口空闲模式读串口接收缓冲区，如果有数据，将数据拷贝到RevBuffer,并返回接收到的数据个数，然后重新将接收缓冲区地址指向RxdBuffer
	if(RxNum)
	{
    
    unsigned char* head = NULL;
    memcpy(RevBuffe,RxdBuffe,RxNum);
    head = getheadaddr(RevBuffe,RxNum);
    if(head)
    {
      LCD_ShowHex(0	,128,16	,LCD565_RED,RxNum,8,head);				//待发药槽位，后边的省略号就是可变参数	
    }
    else
    {
      LCD_Printf(0,0,16	,LCD565_RED,"未识别指令");				//待发药槽位，后边的省略号就是可变参数
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
void SwitchID_Server(void)	//拔码开关处理--动态更新拨码地址
{
	u8 ID_Temp	=	0;
	ID_Temp	=	SWITCHID_Read(&SWITCHID);		//
	if(SwitchID	!=	ID_Temp)
	{
		SwitchID	=	ID_Temp;
		LCD_Printf(0		,0,32	,LCD565_RED,"地址：%0.2d",SwitchID);				//待发药槽位，后边的省略号就是可变参数
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
	SWITCHID.NumOfSW	=	6;
	
	SWITCHID.SW1_PORT	=	GPIOC;
	SWITCHID.SW1_Pin	=	GPIO_Pin_6;
	
	SWITCHID.SW2_PORT	=	GPIOC;
	SWITCHID.SW2_Pin	=	GPIO_Pin_7;
	
	SWITCHID.SW3_PORT	=	GPIOC;
	SWITCHID.SW3_Pin	=	GPIO_Pin_8;
	
	SWITCHID.SW4_PORT	=	GPIOC;
	SWITCHID.SW4_Pin	=	GPIO_Pin_9;
	
	SWITCHID.SW5_PORT	=	GPIOC;
	SWITCHID.SW5_Pin	=	GPIO_Pin_12;
	
	SWITCHID.SW6_PORT	=	GPIOC;
	SWITCHID.SW6_Pin	=	GPIO_Pin_13;
	
	SwitchIdInitialize(&SWITCHID);							//
	
	SwitchID	=	SWITCHID_Read(&SWITCHID);		//
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
void LCD_Configuration(void)
{
	LCDPortDef		*Port;
	SPIDef				*SPIx;
	
	Port	=	&(sLCD.Port);
	SPIx		=	&(sLCD.GT32L32.SPI);
	
	Port->sCS_PORT		=	GPIOA;
	Port->sCS_Pin			=	GPIO_Pin_12;
	
	Port->sDC_PORT		=	GPIOA;
	Port->sDC_Pin			=	GPIO_Pin_8;
	
	Port->sWR_PORT		=	GPIOA;
	Port->sWR_Pin			=	GPIO_Pin_15;
	
	Port->sRD_PORT		=	GPIOC;
	Port->sRD_Pin			=	GPIO_Pin_5;
	
	Port->sREST_PORT	=	GPIOD;
	Port->sREST_Pin		=	GPIO_Pin_2;
	
	Port->sBL_PORT		=	GPIOA;
	Port->sBL_Pin			=	GPIO_Pin_3;
	
	Port->sTE_PORT		=	GPIOC;
	Port->sTE_Pin			=	GPIO_Pin_4;
	
	Port->sDATABUS_PORT	=	GPIOB;
	Port->sDATABUS_Pin	=	GPIO_Pin_All;
	
	sLCD.Data.BColor	=	LCD565_LBBLUE;
	sLCD.Data.PColor	=	LCD565_RED;
	sLCD.Flag.Rotate	=	Draw_Rotate_90D;
	
	SPIx->Port.SPIx=SPI1;
	
	SPIx->Port.CS_PORT=GPIOA;
	SPIx->Port.CS_Pin=GPIO_Pin_4;
	
	SPIx->Port.CLK_PORT	=	GPIOA;
	SPIx->Port.CLK_Pin=GPIO_Pin_5;
	
	SPIx->Port.MISO_PORT	=	GPIOA;
	SPIx->Port.MISO_Pin=GPIO_Pin_6;
	
	SPIx->Port.MOSI_PORT	=	GPIOA;
	SPIx->Port.MOSI_Pin=GPIO_Pin_7;
	
	SPIx->Port.SPI_BaudRatePrescaler_x=SPI_BaudRatePrescaler_2;
	
	sLCD.GT32L32.SPI.Port.SPIx	=	SPI1;
	sLCD.GT32L32.SPI.Port.CS_PORT	=	GPIOA;
	sLCD.GT32L32.SPI.Port.CS_Pin		=	GPIO_Pin_4;
	sLCD.GT32L32.SPI.Port.SPI_BaudRatePrescaler_x=SPI_BaudRatePrescaler_2;
	
	LCD_Initialize(&sLCD);
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
	RS485.USARTx=USART1;
	RS485.RS485_CTL_PORT=GPIOA;
	RS485.RS485_CTL_Pin=GPIO_Pin_11;
	
	RS485_DMA_ConfigurationNR	(&RS485,115200,Rs485Size);	//USART_DMA配置--查询方式，不开中断,配置完默认为接收状态
}
/*******************************************************************************
* 函数名		:	
* 功能描述	:	 
* 输入		:	
* 输出		:
* 返回 		:
*******************************************************************************/
void PL010V13_DISPLAY(void)
{
//	R61509V_DrawPixelEx( 100, 100,LCD_FORE_COLOR);
//	R61509V_DrawHLine( 10, 100, 200, LCD_FORE_COLOR);
}
void PL010Delay(u32 time)
{	
	while(time--);
}


#endif
