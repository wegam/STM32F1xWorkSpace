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
#include "STM32_SPI.H"

#include "SWITCHID.H"
#include "IOT5302W.H"     //读卡器

#include 	"CRC.H"

#include "string.h"				//串和内存操作函数头文件

//------------------锁接口J10
#define SYSLEDPort    GPIOA         //锁控制接口，高电平开锁
#define SYSLEDPin     GPIO_Pin_0
//------------------通讯接口--PC
#define CommPcPort        USART2
//------------------通讯接口--柜口
#define CommCbPort       USART1
#define CommCbCTLPort    GPIOA         //锁控制接口，高电平开锁
#define CommCbCTLPin     GPIO_Pin_8
//------------------通讯接口--层板接口
#define CommLayPort       UART4
#define CommLayCTLPort    GPIOA         //锁控制接口，高电平开锁
#define CommLayCTLPin     GPIO_Pin_12
//------------------通讯接口--读卡器接口
#define CommCardPort      USART3
#define CommCardCTLPort   GPIOC         //锁控制接口，高电平开锁
#define CommCardCTLPin    GPIO_Pin_8
#define CommCardBaudRate  19200         //读卡器通讯波特率

//------------------锁接口J10
#define LockDrPort    GPIOC         //锁控制接口，高电平开锁
#define LockDrPin     GPIO_Pin_12
#define LockSiPort    GPIOB         //锁信号，检测到低电平表示锁已开
#define LockSiPin     GPIO_Pin_1
#define UnLock        LockDrPort->BSRR  = LockDrPin    //开锁
#define ResLock       LockDrPort->BRR   = LockDrPin    //释放锁驱动
#define GetLockSts    LockSiPort->IDR & LockSiPin      //获取锁的状态，如果为0，表示锁已开
//------------------背光接口J11的VCC和EN脚
#define BackLightPort GPIOB         //高电平关闭，低电平点亮
#define BackLightPin  GPIO_Pin_0

//------------------层板电源控制J5、J6、J9共用一个控制电源
#define LayPowerPort  GPIOB         //高电启动电源，低电平关闭电源
#define LayPowerPin   GPIO_Pin_2
#define LayPowerOn    LayPowerPort->BSRR = LayPowerPin   //启动电源
#define LayPowerOff   LayPowerPort->BRR  = LayPowerPin   //关闭电源

/* Private variables ---------------------------------------------------------*/
static RS485Def stCbRS485Ly;   //uart4,PA15   //层板接口
static RS485Def stCbRS485Cb;   //usart1,PA8    //副柜接口
static RS485Def stCardRS485Ly; //usart3,PB2    //读卡器接口
static SwitchDef stCbSwitch;
static SPIDef stLed;

static unsigned char CabAddr   =0;
static unsigned char MainFlag  =0; //0--副柜，1--主柜
unsigned char rxx[512]={0};
unsigned char txx[]="Communication_Configuration";
unsigned short timee=0;
//tAMPProdef   AMPPro;
/* Private function prototypes -----------------------------------------------*/
static void Hardware_Configuration(void);
static void GenyGPIO_Configuration(void);
static void Communication_Configuration(void);
//-----------------------------背光相关程序
static void BackLight_Configuration(void);
static void BackLight_Server(void);
static void Set_BackLight_On(void);
static void Set_BackLight_Off(void);
static unsigned char Get_BackLight_State(void);
//-----------------------------锁相关程序
static void Lock_Configuration(void);
static void Lock_Server(void);
static void Set_Lock_Open(void);
static void Set_Lock_Release(void);
static void Request_Lock_Open(void);
static unsigned char Get_Lock_State(void);
//-----------------------------拨码开关相关程序
static void SwitchID_Configuration(void);
static void SwitchID_Server(void);
//-----------------------------通讯LED指示灯
static void Led_Configuration(void);
static void Led_Server(void);
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
  PWM_OUT(TIM2,PWM_OUTChannel1,2,500);	//PWM设定-20161127版本	占空比1/1000
	
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
  unsigned char rxnum;
	IWDG_Feed();								//独立看门狗喂狗
	Tim_Server();
  BackLight_Server();
  Lock_Server();
  SwitchID_Server();
  Led_Server();
  
//  rxnum = RS485_ReadBufferIDLE(&stCbRS485Cb,rxx);	//串口空闲模式读串口接收缓冲区，如果有数据，将数据拷贝到RevBuffer,并返回接收到的数据个数，然后重新将接收缓冲区地址指向RxdBuffer
//  if(rxnum)
//  {
////    memset(rxx,0,200);
//  }
////	AMP_CABV11_Server();
//  
//  if(timee++>=2000)
//  {
//    timee=0;
//    memset(rxx,0xFF,200);
//    RS485_DMASend(&stCbRS485Cb,txx,strlen(txx));	//RS485-DMA发送程序    
//  }
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
  BackLight_Configuration();
	Lock_Configuration();
  SwitchID_Configuration();
  Led_Configuration();
//	//=======================================================拨码开关配置
//	SwitchID_Configuration();
//	//=======================================================常规接口配置，背光，锁，电源控制
//	GenyGPIO_Configuration(); 
//	//=======================================================通讯配置
//  Communication_Configuration();
//	
//  SysTick_DeleymS(200);				//SysTick延时nmS--等上电稳定  
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
  BackLight_Configuration();
  //---------------------层板供电接口配置
  GPIO_Configuration_OPP50(LayPowerPort,LayPowerPin);
  LayPowerOff;   //开供电，配置读卡器
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
//=================================背光相关程序=================================
/*******************************************************************************
*函数名			:	function
*功能描述		:	function
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
static void BackLight_Configuration(void)
{
  GPIO_Configuration_OPP50(BackLightPort,BackLightPin);
  Set_BackLight_Off();
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
static void BackLight_Server(void)
{
  
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
static void Set_BackLight_On(void)
{
  BackLightPort->BSRR = BackLightPin;
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
static void Set_BackLight_Off(void)
{
  BackLightPort->BRR = BackLightPin;
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
static unsigned char Get_BackLight_State(void)
{
  return(GPIO_ReadOutputDataBit(BackLightPort,BackLightPin));
}
//=================================锁相关程序=================================
/*******************************************************************************
*函数名			:	function
*功能描述		:	function
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
static void Lock_Configuration(void)
{
  GPIO_Configuration_OPP50(LockDrPort,LockDrPin);
  GPIO_Configuration_IPU(LockSiPort,LockSiPin);
  Set_Lock_Release();
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
static void Lock_Server(void)
{
  
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
static void Set_Lock_Open(void)
{
  LockDrPort->BSRR = LockDrPin;  
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
static void Set_Lock_Release(void)
{
  LockDrPort->BRR = LockDrPin;
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
static void Request_Lock_Open(void)
{

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
static unsigned char Get_Lock_State(void)
{
  return(GPIO_ReadOutputDataBit(LockDrPort,LockDrPin));
}
//=======================================拨码开关===============================
/*******************************************************************************
* 函数名			:	function
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
static void SwitchID_Configuration(void)
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
static void SwitchID_Server(void)
{
  static unsigned char id=0;
  static unsigned char power_on_flag=0; //上电时为0
  static unsigned short timout_to_check_id_change=0;  
  if(0==power_on_flag)  //刚上电
  {
    power_on_flag = 1;  //已上电完成
    id  = SWITCHID_ReadLeft(&stCbSwitch)&0x3F;
  }
  else
  {
    if(timout_to_check_id_change++>2000)  //2秒检查一次拨码变化
    {
      unsigned char new_id  = 0;
      timout_to_check_id_change = 0;
      new_id  = SWITCHID_ReadLeft(&stCbSwitch)&0x3F;
      if(id != new_id)  //重新初始化
      {
        power_on_flag = 0;
      }
    }
  }
}
//=======================================通讯LED指示灯=============================
/*******************************************************************************
*函数名			:	function
*功能描述		:	function
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
static void Led_Configuration(void)
{
  stLed.Port.SPIx 			= SPI1;
  stLed.Port.CS_PORT  	= GPIOA;
  stLed.Port.CS_Pin   	= GPIO_Pin_4;
  stLed.Port.CLK_PORT 	= GPIOA;
  stLed.Port.CLK_Pin  	= GPIO_Pin_5;
  stLed.Port.MISO_PORT  = GPIOA;
  stLed.Port.MISO_Pin   = GPIO_Pin_6;
  stLed.Port.MOSI_PORT  = GPIOA;
  stLed.Port.MOSI_Pin   = GPIO_Pin_7;
  stLed.Port.SPI_BaudRatePrescaler_x  = SPI_BaudRatePrescaler_64;
	SPI_Initialize(&stLed);		//SPI接口配置
  //SPI_InitializeSPI(&stLed);			//SPI-DMA通讯方式配置
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
static void Led_Server(void)
{
  static unsigned short freshen_led_time=0;
  static unsigned char led_stata=0;
  if(freshen_led_time++>500)
  {
		freshen_led_time	=	0;
    led_stata++;
		//____________使能片选
		SPI_CS_LOW(&stLed);
    SPI_ReadWriteByteSPI(&stLed,led_stata);
		//____________取消片选	
		SPI_CS_HIGH(&stLed);
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
