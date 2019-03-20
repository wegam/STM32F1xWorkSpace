#ifdef AMP01V11A3

#include "AMP01V11A3.H"


#include "AMP_LAY.H"
//#include "AMP_CABV11.H"

#include	"AMP_PHY.H"

#include "STM32F10x_BitBand.H"
#include "STM32_GPIO.H"
#include "STM32_SYS.H"
#include "STM32_SYSTICK.H"
#include "STM32_WDG.H"
#include "STM32_PWM.H"
#include "STM32_USART.H"

#include "SWITCHID.H"
#include "IOT5302W.H"     //读卡器

#include 	"CRC.H"

#include "string.h"				//串和内存操作函数头文件
/* Private variables ---------------------------------------------------------*/
static RS485Def stCbRS485Ly;   //uart4,PA15   //层板接口
static RS485Def stCbRS485Cb;   //usart1,PA8    //副柜接口
static RS485Def stCardRS485Ly; //usart3,PB2    //读卡器接口
static SwitchDef stCbSwitch;

static unsigned char CabAddr   =0;
static unsigned char MainFlag  =0; //0--副柜，1--主柜

//tAMPProdef   AMPPro;
/* Private function prototypes -----------------------------------------------*/
static void Hardware_Configuration(void);
static void HW_SwitchID_Configuration(void);
static void GenyGPIO_Configuration(void);
static void Communication_Configuration(void);
/*******************************************************************************
*函数名			:	function
*功能描述		:	function
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
void AMP01V11A3_Configuration(void)
{	
	SYS_Configuration();					//系统配置---打开系统时钟 STM32_SYS.H	
	
	Hardware_Configuration();

  GPIO_Configuration_OPP50(SYSLEDPort,SYSLEDPin);

	//SysTick_DeleymS(500);				//SysTick延时nmS
	
  IWDG_Configuration(2000);			//独立看门狗配置---参数单位ms
  
  SysTick_Configuration(1000);	//系统嘀嗒时钟配置72MHz,单位为uS
  
  while(1)
  {

  }
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
void AMP01V11A3_Server(void)
{  
	IWDG_Feed();								//独立看门狗喂狗
	Tim_Server();

	AMP_CABV11_Server();
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
static void Hardware_Configuration(void)
{
	SysTick_DeleymS(200);				//SysTick延时nmS--等上电稳定
	
	//=======================================================拨码开关配置
	HW_SwitchID_Configuration();
	//=======================================================常规接口配置，背光，锁，电源控制
	GenyGPIO_Configuration(); 
	//=======================================================通讯配置
  Communication_Configuration();
	
  SysTick_DeleymS(200);				//SysTick延时nmS--等上电稳定  
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
static void HW_SwitchID_Configuration(void)
{
  stCbSwitch.NumOfSW	=	8;
  
  stCbSwitch.SW1_PORT	=	GPIOB;
  stCbSwitch.SW1_Pin	=	GPIO_Pin_9;
  
  stCbSwitch.SW2_PORT	=	GPIOB;
  stCbSwitch.SW2_Pin	=	GPIO_Pin_8;
  
  stCbSwitch.SW3_PORT	=	GPIOB;
  stCbSwitch.SW3_Pin	=	GPIO_Pin_7;
  
  stCbSwitch.SW4_PORT	=	GPIOB;
  stCbSwitch.SW4_Pin	=	GPIO_Pin_6;
  
  stCbSwitch.SW5_PORT	=	GPIOB;
  stCbSwitch.SW5_Pin	=	GPIO_Pin_5;
  
  stCbSwitch.SW6_PORT	=	GPIOB;
  stCbSwitch.SW6_Pin	=	GPIO_Pin_4;
  
  stCbSwitch.SW7_PORT	=	GPIOB;
  stCbSwitch.SW7_Pin	=	GPIO_Pin_3;
  
  stCbSwitch.SW8_PORT	=	GPIOD;
  stCbSwitch.SW8_Pin	=	GPIO_Pin_2;

	SwitchIdInitialize(&stCbSwitch);						//

  CabAddr  = SWITCHID_ReadLeft(&stCbSwitch)&0x3F;  
  
  if(SWITCHID_ReadLeft(&stCbSwitch)&0x80)
  {
    MainFlag=1; //0--副柜，1--主柜
  }
  else
  {
    MainFlag=0; //0--副柜，1--主柜
  }
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
static void GenyGPIO_Configuration(void)
{
	//---------------------锁接口配置
  GPIO_Configuration_OPP50(LockDrPort,LockDrPin);
  GPIO_Configuration_IPU(LockSiPort,LockSiPin);
  ResLock;    //释放锁驱动
  //---------------------背光接口配置
  GPIO_Configuration_OPP50(BackLightPort,BackLightPin);
  BackLightOn;
  //---------------------层板供电接口配置
  GPIO_Configuration_OPP50(LayPowerPort,LayPowerPin);
  LayPowerOn;   //开供电，配置读卡器
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
static void Communication_Configuration(void)
{
	IOT5302Wdef IOT5302W;
  //-----------------------------PC接口USART1
  USART_DMA_ConfigurationNR	(CommPcPort,19200,gDatasize);	//USART_DMA配置--查询方式，不开中断
  
  //-----------------------------读卡器接口USART3
  IOT5302W.Conf.IOT5302WPort.USARTx  = CommCardPort;
  IOT5302W.Conf.IOT5302WPort.RS485_CTL_PORT  = CommCardCTLPort;
  IOT5302W.Conf.IOT5302WPort.RS485_CTL_Pin   = CommCardCTLPin;
  IOT5302W.Conf.USART_BaudRate  = CommCardBaudRate;
	GPIO_Configuration_OOD50(GPIOC,GPIO_Pin_7);			//将GPIO相应管脚配置为OD(开漏)输出模式，最大速度50MHz----V20170605
	GPIO_ResetBits(GPIOC,GPIO_Pin_7);
  API_IOT5302WConfiguration(&IOT5302W);
  //-----------------------------层板接口USART2
  stCbRS485Ly.USARTx  = CommLayPort;
  stCbRS485Ly.RS485_CTL_PORT  = CommLayCTLPort;
  stCbRS485Ly.RS485_CTL_Pin   = CommLayCTLPin;
  RS485_DMA_ConfigurationNR			(&stCbRS485Ly,19200,gDatasize);	//USART_DMA配置--查询方式，不开中断,配置完默认为接收状态
	GPIO_Configuration_OOD50(GPIOA,GPIO_Pin_11);			//将GPIO相应管脚配置为OD(开漏)输出模式，最大速度50MHz----V20170605
	GPIO_ResetBits(GPIOA,GPIO_Pin_11);
  //-----------------------------副柜接口UART4
  stCbRS485Cb.USARTx  = CommCbPort;
  stCbRS485Cb.RS485_CTL_PORT  = CommCbCTLPort;
  stCbRS485Cb.RS485_CTL_Pin   = CommCbCTLPin;
  RS485_DMA_ConfigurationNR			(&stCbRS485Cb,19200,gDatasize);	//USART_DMA配置--查询方式，不开中断,配置完默认为接收状态
	GPIO_Configuration_OOD50(GPIOC,GPIO_Pin_9);			//将GPIO相应管脚配置为OD(开漏)输出模式，最大速度50MHz----V20170605
	GPIO_ResetBits(GPIOC,GPIO_Pin_9);
}





//=================================软件接口End=============================================================



/*******************************************************************************
*函数名			:	function
*功能描述		:	function
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
unsigned short HW_SendBuff(enCCPortDef Port,unsigned char* pBuffer,unsigned short length)
{ 
  unsigned  short   sendedlen = 0;

    sendedlen = AMPCAB_SendBuff(Port,pBuffer,length);

  return  sendedlen;
}




//=================================硬件接口End=============================================================


//=================================配置函数End=============================================================


//=================================时间函数ST==============================================================

/*******************************************************************************
*函数名			:	function
*功能描述		:	function
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
void Tim_Server(void)
{
  //----------------PC发送
  if(AMPPro.Time.PcSendTime>0)
  {
    AMPPro.Time.PcSendTime--;
  }
  //----------------柜发送
  if(AMPPro.Time.CabSendTime>0)
  {
    AMPPro.Time.CabSendTime--;
  }
  //----------------层发送
  if(AMPPro.Time.LaySendTime>0)
  {
    AMPPro.Time.LaySendTime--;
  }
  //----------------读卡器发送
  if(AMPPro.Time.CardSendTime>0)
  {
    AMPPro.Time.CardSendTime--;
  }
  //----------------锁
  if(AMPPro.Time.LockTime>0)
  {
    AMPPro.Time.LockTime--;
  }
  //----------------拨码
  if(AMPPro.Time.swicthidtime>0)
  {
    AMPPro.Time.swicthidtime--;
  }
  //----------------运行指示灯
  if(AMPPro.Time.SYSLEDTime>0)
  {
    AMPPro.Time.SYSLEDTime--;
  }
}
#endif
