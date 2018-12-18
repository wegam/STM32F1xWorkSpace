///******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
//* File Name          : PC001V21.c
//* Author             : WOW
//* Version            : V2.0.1
//* Date               : 06/26/2017
//* Description        : PC001V21层控制板.
//********************************************************************************
//* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
//* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
//* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
//* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
//* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
//* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
//*******************************************************************************/

#ifdef AMPLED02V13				//拆零柜LCD板

#include "AMPLED02V13.H"

#include "LCD.H"


#include "STM32_GPIO.H"
#include "STM32_SYS.H"
#include "STM32_SYSTICK.H"
#include "STM32_WDG.H"
#include "STM32_PWM.H"
#include "STM32_USART.H"
#include	"AMP_PHY.H"


#include "SWITCHID.H"

#include 	"CRC.H"

//#include "string.h"				//串和内存操作函数头文件


LCDDef	sLCD;
RS485Def RS485;
SwitchDef stSwitch;

unsigned char SwitchID  = 0xFF;
unsigned char AddrLy	=	0,AddrSc	=	0;

unsigned char RxdBuffe[128]={0};
unsigned char msgBuffe[128]={0};
unsigned char ackBuffe[7]={0};

unsigned short time	=	0;
vu16	Color	=	0;

char tep[1]={'A'};

unsigned char Version[]="PL012V3.0 RF智能耗材管理柜";
unsigned char DataStr[]=__DATE__;
unsigned char	TimeStr[]=__TIME__;
//SWITCHID_CONF	SWITCHID;
//u8 SwitchID=0;	//拔码开关地址

/*******************************************************************************
* 函数名		:	
* 功能描述	:	 
* 输入		:	
* 输出		:
* 返回 		:
*******************************************************************************/
void AMPLED02_Configuration(void)
{
	SYS_Configuration();					//系统配置---打开系统时钟 STM32_SYS.H
	
	GPIO_DeInitAll();							//将所有的GPIO关闭----V20170605
	
	LCD_Configuration();

	RS485_Configuration();

	SwitchID_Configuration();

	//LCD_Printf(0,140,16,LCD565_RED,"显示驱动:%4X",LCD_ReadData(LCD_R000_IR));		//编译日期
	LCD_Printf(0,160,16,LCD565_RED,"项目编号:%s",Version);		//编译日期
	LCD_Printf(0,180,16,LCD565_RED,"编译日期:%s",__DATE__);		//编译日期
	LCD_Printf(0,200,16,LCD565_RED,"编译时间:%s",__TIME__); 	//编译时间 
	
	SysTick_Configuration(100000);	//系统嘀嗒时钟配置72MHz,单位为uS

//	IWDG_Configuration(1000);			//独立看门狗配置---参数单位ms	
	PWM_OUT(TIM2,PWM_OUTChannel1,1,900);	//PWM设定-20161127版本--指示灯
	
	PWM_OUT(TIM2,PWM_OUTChannel3,500,200);		//PWM设定-20161127版本--背光
}
/*******************************************************************************
* 函数名		:	
* 功能描述	:	 
* 输入		:	
* 输出		:
* 返回 		:
*******************************************************************************/
void AMPLED02_Server(void)
{	
	u16 Num=0;
	IWDG_Feed();								//独立看门狗喂狗
  SwitchID_Server();
	if(time++>100)
	{
		time	=	0;
	}
	RS485_Server();	

//  LCD_ShowAntenna(360,0,0,LCD565_RED);   //显示12x12天线
//  LCD_ShowBattery(380,0,3,LCD565_RED);   //显示12x12电池
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
	SPIDef				*SPIx;
	
	//==================字库配置
	SPIx		=	&(sLCD.GT32L32.SPI);
	
	SPIx->Port.SPIx=SPI1;
	
	SPIx->Port.CS_PORT		=	GPIOA;
	SPIx->Port.CS_Pin			=	GPIO_Pin_4;
	
	SPIx->Port.CLK_PORT		=	GPIOA;
	SPIx->Port.CLK_Pin		=	GPIO_Pin_5;
	
	SPIx->Port.MISO_PORT	=	GPIOA;
	SPIx->Port.MISO_Pin		=	GPIO_Pin_6;
	
	SPIx->Port.MOSI_PORT	=	GPIOA;
	SPIx->Port.MOSI_Pin		=	GPIO_Pin_7;
	
	SPIx->Port.SPI_BaudRatePrescaler_x=SPI_BaudRatePrescaler_2;
	
	//==================LCD配置
	sLCD.Port.sBL_PORT	=	GPIOA;
	sLCD.Port.sBL_Pin		=	GPIO_Pin_3;
	
	sLCD.Port.sCS_PORT	=	GPIOA;
	sLCD.Port.sCS_Pin		=	GPIO_Pin_12;
	
	sLCD.Port.sDC_PORT	=	GPIOA;
	sLCD.Port.sDC_Pin		=	GPIO_Pin_8;
	
	sLCD.Port.sRD_PORT	=	GPIOC;
	sLCD.Port.sRD_Pin		=	GPIO_Pin_5;
	
	sLCD.Port.sREST_PORT	=	GPIOD;
	sLCD.Port.sREST_Pin		=	GPIO_Pin_2;
	
	sLCD.Port.sTE_PORT		=	GPIOC;
	sLCD.Port.sTE_Pin			=	GPIO_Pin_4;
	
	sLCD.Port.sWR_PORT		=	GPIOA;
	sLCD.Port.sWR_Pin			=	GPIO_Pin_15;
	
	sLCD.Port.sDATABUS_PORT	=	GPIOB;
	sLCD.Port.sDATABUS_Pin	=	GPIO_Pin_All;	
	
	sLCD.Flag.Rotate			=	Draw_Rotate_90D;
	
	sLCD.Data.BColor			=	LCD565_YELLOW;
	sLCD.Data.PColor			=	LCD565_RED;
	
	//==================初始化
	LCD_Initialize(&sLCD);
	
//	R61509V_Initialize(&sLCD);
	
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
void RS485_Server(void)
{
	unsigned short RxNum	=	0;

	RxNum=RS485_ReadBufferIDLE(&RS485,RxdBuffe);	//串口空闲模式读串口接收缓冲区，如果有数据，将数据拷贝到RevBuffer,并返回接收到的数据个数，然后重新将接收缓冲区地址指向RxdBuffer
	if(RxNum)
	{
    memcpy(msgBuffe,RxdBuffe,RxNum);
    msg_Process(msgBuffe,RxNum);		
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
void msg_Process(unsigned char* pBuffer,unsigned short length)
{
  
  unsigned  char framlength  = 0;
  unsigned  char result  = 0;
  unsigned  short R,G,B;  
  stampphydef* ampframe=NULL;
  stcmddef*    cmd  = NULL;
  framlength	=	getframe(pBuffer,&length);
  if(0== framlength)
    return;
  result  = addr2check(pBuffer,AddrLy);   //层地址检查
  if(0==result)
    return;
  result  = addr3check(pBuffer,AddrSc);   //位地址检查
  if(0==result)
    return;

  LCD_ShowHex(0,16,16,LCD565_RED,length,8,pBuffer);                //显示十六进制数据  
  
  ampframe  = (stampphydef*)pBuffer;
  cmd = &ampframe->msg.cmd;
  
  if(0  !=  cmd->dir)
    return;
  if(0  ==  cmd->rw)  //写
  {
    if(cmd->cmd == 3) //控制命令
    {
      if(ampframe->msg.subcmd ==  1)
      {
        if(0  ==  pBuffer[7])
          LEDOFF();
        else
          LEDON();
      }
    }
    ackFrame();   
  }
  return;  
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
void LEDON(void)
{
  LCD_Fill(0,64,399,160,LCD565_RED);
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
void LEDOFF(void)
{
  LCD_Fill(0,64,399,160,LCD565_GBLUE);
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
void ackFrame(void)
{
  unsigned  short crc = 0;
  ackBuffe[0]=0x7E;   //head
  ackBuffe[1]=0x02;   //len
  ackBuffe[2]=0x81;   //cmd
  ackBuffe[3]=0x00;   //subcmd
  crc = CRC16_MODBUS(&ackBuffe[1],3);				//多项式x16+x15+x5+1（0x8005），初始值0xFFFF，低位在前，高位在后，结果与0x0000异或
  memcpy(&ackBuffe[4],&crc,2);
  ackBuffe[6]=0x7F;   //end
  RS485_DMASend(&RS485,ackBuffe,7);	//RS485-DMA发送程序
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
	stSwitch.NumOfSW	=	6;
	
	stSwitch.SW1_PORT	=	GPIOC;
	stSwitch.SW1_Pin	=	GPIO_Pin_6;
	
	stSwitch.SW2_PORT	=	GPIOC;
	stSwitch.SW2_Pin	=	GPIO_Pin_7;
	
	stSwitch.SW3_PORT	=	GPIOC;
	stSwitch.SW3_Pin	=	GPIO_Pin_8;
	
	stSwitch.SW4_PORT	=	GPIOC;
	stSwitch.SW4_Pin	=	GPIO_Pin_9;
	
	stSwitch.SW5_PORT	=	GPIOC;
	stSwitch.SW5_Pin	=	GPIO_Pin_12;
	
	stSwitch.SW6_PORT	=	GPIOC;
	stSwitch.SW6_Pin	=	GPIO_Pin_13;
	
	SwitchIdInitialize(&stSwitch);							//
	
	//SwitchID	=	SWITCHID_Read(&stSwitch);		//
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
void SwitchID_Server(void)
{
	u8 temp=0;	//拔码开关临时地址
	temp	=	SWITCHID_Read(&stSwitch);		//读取地址
	if(SwitchID	!=	temp)
	{
    SwitchID  = temp;
		AddrLy  = SwitchID>>3;
    AddrSc  = SwitchID&0x07;
    LCD_Printf(0	,0	,16	,LCD565_RED,"层号:%0.2d,位号:%0.2d",AddrLy,AddrSc);				//待发药槽位，后边的省略号就是可变参数

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
	RS485.USARTx=USART1;
	RS485.RS485_CTL_PORT=GPIOA;
	RS485.RS485_CTL_Pin=GPIO_Pin_11;
	
	RS485_DMA_ConfigurationNR	(&RS485,19200,64);	//USART_DMA配置--查询方式，不开中断,配置完默认为接收状态
}

#endif

