#ifdef AMP01

#include "AMP01.H"

#include "string.h"				//串和内存操作函数头文件
//#include "stm32f10x_dma.h"

#include	"AMP_PHY.H"

#include "STM32F10x_BitBand.H"
#include "STM32_GPIO.H"
#include "STM32_SYS.H"
#include "STM32_SYSTICK.H"
#include "STM32_WDG.H"
#include "STM32_PWM.H"
#include "STM32_USART.H"

#include "SWITCHID.H"

#include 	"CRC.H"




RS485Def stRS485Ly;   //usart2,pa1    //层板接口
RS485Def stRS485Cb;   //uart4,pc12    //副柜接口
SwitchDef stSwitch;

stSysdef  AMP;



unsigned  short seril=0;
/*******************************************************************************
*函数名			:	function
*功能描述		:	function
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
void AMP01_Configuration(void)
{	
	SYS_Configuration();					//系统配置---打开系统时钟 STM32_SYS.H	
  
  SwitchID_Configuration();
  
  GenyConfiguration();   //常规接口配置，背光，锁，电源控制
    
  COMM_Configuration();  
//  
	PWM_OUT(TIM2,PWM_OUTChannel1,2,950);						//PWM设定-20161127版本
	
//  IWDG_Configuration(1000);													//独立看门狗配置---参数单位ms
  SysTick_Configuration(1000);    //系统嘀嗒时钟配置72MHz,单位为uS
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
void AMP01_Server(void)
{
  USART_Server();
  SwitchID_Server();
  LockServer();
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
  static unsigned short swtime  = 0;
  if(swtime++>2000) //2秒检查一次拨码
  {
    unsigned  char  tempid  = 0;
    unsigned  char* tempbc  = (unsigned  char*)&AMP.SwData;
    swtime  = 0;
    tempid  = SWITCHID_ReadLeft(&stSwitch);
    if(*tempbc  != tempid)
    {
      *tempbc  = tempid;
      AMP01_Configuration();    //重新配置控制板
    }
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
void USART_Server(void)
{
  unsigned short RxNum  = 0;
  unsigned char str[]="串口接收到数据\r\n";
  //---------------------PC接口 USART1
  RxNum = USART_ReadBufferIDLE(USART1,AMP.buffer.u1rx);
  if(RxNum)
  {
    PCmsg_Process(AMP.buffer.u1rx,RxNum);                //PC消息处理
  }
  //---------------------读卡器接口 USART3
  RxNum = USART_ReadBufferIDLE(USART3,AMP.buffer.u3rx);
  if(RxNum)
  {
    ICcardData_Process(AMP.buffer.u3rx,RxNum);
  }
  //---------------------层板接口 USART2
  RxNum = RS485_ReadBufferIDLE(&stRS485Ly,AMP.buffer.u2rx);
  if(RxNum)
  {
    memcpy(AMP.buffer.u1tx,AMP.buffer.u2rx,RxNum);
    USART_DMASend(USART1,AMP.buffer.u1tx,RxNum);
  }
  //---------------------副柜接口 UART4
  RxNum = RS485_ReadBufferIDLE(&stRS485Cb,AMP.buffer.u4rx);
  if(RxNum)
  {
    memcpy(AMP.buffer.u1tx,AMP.buffer.u4rx,RxNum);
    USART_DMASend(USART1,AMP.buffer.u1tx,RxNum);
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
void PCmsg_Process(unsigned char* pBuffer,unsigned short length)
{
  
  unsigned  char result  = 0;
  
  unsigned  short framlength  = 0;
  
  unsigned  char* paddrbac = pBuffer;         //备份数据缓存起始地址
  
  stampphydef* ampframe=NULL;
  stcmddef*    cmd;
  //-------------------------协议检查
  framlength	=	getframe(pBuffer,&length);    //判断帧消息内容是否符合协议
  if(0== framlength)
  {
    memset(paddrbac,0x00,ccsize);             //清除数据
    return;
  }
  result  = ackcheck(pBuffer);                //检查是否为应答消息,应答消息返回1
  if(1==result)
  {
    memset(paddrbac,0x00,ccsize);             //清除数据
    return;
  }
//  //-------------------------ID检查---PC接口不检查
//  result  = addr1check(pBuffer,AMP.SwData.ID);     //层地址检查---控制板地址段为address1
//  if(0==result)
//  {
//    return;
//  }
  //-------------------------根据地址转发数据：广播数据发送到副柜和本柜层板
  ampframe  = (stampphydef*)pBuffer;
  if(0xFF==ampframe->msg.addr.address1)   //广播数据
  {
    LayPowerOn;
    UnLock;      //开锁
    Cabinet_Send(pBuffer,length);    //往副柜发送消息
    Laynet_Send(pBuffer,length);     //往层板发送消息
  }
  else if(AMP.SwData.ID==ampframe->msg.addr.address1) //本柜数据
  {
    LayPowerOn;
    UnLock;      //开锁
    Laynet_Send(pBuffer,length);     //往层板发送消息
  }
  else    //其它柜数据
  {
    Cabinet_Send(pBuffer,length);    //往副柜发送消息
  }  
}
/*******************************************************************************
* 函数名			:	ICcardData_Process
* 功能描述		:	IC卡数据处理，如果是主柜，通过PC接口打包上传，如果是副柜，通过副柜接口打包上传 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
void ICcardData_Process(unsigned char* pBuffer,unsigned short length)
{
  
  unsigned  char result  = 0;
  
  unsigned  short framlength  = 0;
  
  unsigned  char  databuffer[64]={0};
  
  unsigned  char* paddrbac = pBuffer;         //备份数据缓存起始地址  
  
  stampphydef* ampframe=NULL;
  stcmddef*    cmd;
  //-------------------------打包数据
  memcpy(databuffer,pBuffer,length);
  framlength  = length;
  framlength  = PaketMsg(databuffer,ICR|Up,&framlength);
  //-------------------------设置地址:柜控制板地址段为address1
  ampframe  = (stampphydef*)databuffer;
  ampframe->msg.addr.address1 = AMP.SwData.ID;
  //-------------------------设置CRC和结束符
  SetCrc(databuffer,&framlength);
  //-------------------------检查本柜是否为主柜
  if(1==AMP.SwData.MainFlg)   //主柜--通过PC接口上传
  {
    PCnet_Send(databuffer,framlength);
  }
  else  //副柜--通过副柜接口上传
  {
    Cabinet_Send(databuffer,framlength);     //往副柜发送消息
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
void GenyConfiguration(void)
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
  LayPowerOn;
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
void LockServer(void)
{
  static unsigned  char locktime = 0;
  if(GetLockSts)    //锁未开
  {
    locktime  = 0;
    BackLightOff;
//    LayPowerOff;
  }
  else
  {
    if(locktime++>100)  //延迟10ms释放锁驱动
    {
      locktime  = 0;
      BackLightOn;      //打开背光
      ResLock;
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
void SwitchID_Configuration(void)
{
  unsigned  char* tempsw = NULL;
	stSwitch.NumOfSW	=	8;
	
	stSwitch.SW1_PORT	=	GPIOC;
	stSwitch.SW1_Pin	=	GPIO_Pin_0;
	
	stSwitch.SW2_PORT	=	GPIOC;
	stSwitch.SW2_Pin	=	GPIO_Pin_1;
	
	stSwitch.SW3_PORT	=	GPIOC;
	stSwitch.SW3_Pin	=	GPIO_Pin_2;
	
	stSwitch.SW4_PORT	=	GPIOC;
	stSwitch.SW4_Pin	=	GPIO_Pin_3;
	
	stSwitch.SW5_PORT	=	GPIOC;
	stSwitch.SW5_Pin	=	GPIO_Pin_4;
	
	stSwitch.SW6_PORT	=	GPIOC;
	stSwitch.SW6_Pin	=	GPIO_Pin_5;
  
  stSwitch.SW7_PORT	=	GPIOC;
	stSwitch.SW7_Pin	=	GPIO_Pin_6;
  
  stSwitch.SW8_PORT	=	GPIOC;
	stSwitch.SW8_Pin	=	GPIO_Pin_7;
	
	SwitchIdInitialize(&stSwitch);							//
	
  tempsw  = (unsigned  char*)&AMP.SwData;
  *tempsw  = SWITCHID_ReadLeft(&stSwitch);
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
void COMM_Configuration(void)
{
  //-----------------------------PC接口USART1
  USART_DMA_ConfigurationNR	(USART1,19200,ccsize);	//USART_DMA配置--查询方式，不开中断
  
  //-----------------------------读卡器接口USART3
  if(0==AMP.SwData.ICreadFlg) //sw2未拨码，默认19200
    USART_DMA_ConfigurationNR	(USART3,19200,ccsize);	//USART_DMA配置--查询方式，不开中断
  else
    USART_DMA_ConfigurationNR	(USART3,9600,ccsize);	//USART_DMA配置--查询方式，不开中断

  //-----------------------------层板接口USART2
  stRS485Ly.USARTx  = USART2;
  stRS485Ly.RS485_CTL_PORT  = GPIOA;
  stRS485Ly.RS485_CTL_Pin   = GPIO_Pin_1;
  RS485_DMA_ConfigurationNR			(&stRS485Ly,19200,ccsize);	//USART_DMA配置--查询方式，不开中断,配置完默认为接收状态
  //-----------------------------副柜接口UART4
  stRS485Cb.USARTx  = UART4;
  stRS485Cb.RS485_CTL_PORT  = GPIOC;
  stRS485Cb.RS485_CTL_Pin   = GPIO_Pin_12;
  RS485_DMA_ConfigurationNR			(&stRS485Cb,19200,ccsize);	//USART_DMA配置--查询方式，不开中断,配置完默认为接收状态
}
/*******************************************************************************
*函数名			:	function
*功能描述		:	往副柜发送消息
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
unsigned short PCnet_Send(unsigned char* pBuffer,unsigned short length)
{
  memcpy(AMP.buffer.u1tx,pBuffer,length);
  USART_DMASend(USART1,AMP.buffer.u1tx,length);
  return  0;
}
/*******************************************************************************
*函数名			:	function
*功能描述		:	往副柜发送消息
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
unsigned short Cabinet_Send(unsigned char* pBuffer,unsigned short length)
{
  memcpy(AMP.buffer.u4tx,pBuffer,length);

  RS485_DMASend(&stRS485Cb,AMP.buffer.u4tx,length);
  
  return  0;
}
/*******************************************************************************
*函数名			:	function
*功能描述		:	往层板发送消息
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
unsigned short Laynet_Send(unsigned char* pBuffer,unsigned short length)
{
  memcpy(AMP.buffer.u2tx,pBuffer,length);

  RS485_DMASend(&stRS485Ly,AMP.buffer.u2tx,length);
  
  return  0;
}

#endif
