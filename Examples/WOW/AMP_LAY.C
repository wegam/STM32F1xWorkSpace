#include "AMP_LAY.H"

#include "string.h"				//串和内存操作函数头文件
//#include "stm32f10x_dma.h"

#include	"AMP_PHY.H"
#include "AMP01.H"

#include "STM32F10x_BitBand.H"
#include "STM32_GPIO.H"
#include "STM32_SYS.H"
#include "STM32_SYSTICK.H"
#include "STM32_WDG.H"
#include "STM32_PWM.H"
#include "STM32_USART.H"

#include "SWITCHID.H"

#include 	"CRC.H"

RS485Def stLayRS485;   //usart2,pa1    //层板接口

SwitchDef stLaySwitch;

unsigned char LayAddr=0,SegAddr=0;
/*******************************************************************************
*函数名			:	function
*功能描述		:	function
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
void AMPLAY_Configuration(void)
{	
	SYS_Configuration();					//系统配置---打开系统时钟 STM32_SYS.H	
  
  AMPLAYSwitchID_Configuration();
  
  AMPLAY_GenyConfiguration();   //常规接口配置，背光，锁，电源控制
    
  AMPLAYCOMM_Configuration();  
 
//	PWM_OUT(TIM2,PWM_OUTChannel1,1000,950);	  //PWM设定-20161127版本  
//  IWDG_Configuration(1000);								  //独立看门狗配置---参数单位ms
//  SysTick_Configuration(1000);              //系统嘀嗒时钟配置72MHz,单位为uS
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
void AMPLAY_Server(void)
{  
  AMPLAY_SwitchIDServer();
  AMPLAY_SYSLED();
}
/*******************************************************************************
*函数名			:	
*功能描述		:	
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
void AMPLAY_Loop(void)
{  
  AMPLAY_Receive();
  //----------------层发送
  if(0  ==  AMPPro.Time.LaySendTime)
  {
    Check_SendBuff(LayPort);
  }
}
//=================================硬件接口ST==============================================================
/*******************************************************************************
*函数名			:	function
*功能描述		:	function
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
void AMPLAY_Receive(void)
{
  unsigned short RxNum  = 0;
  unsigned char rxd[256]={0};
  //==========================================================接收查询
  //---------------------层板接口 USART2
  RxNum = RS485_ReadBufferIDLE(&stLayRS485,rxd);
  if(RxNum)
  {
    Msg_ProcessLY(LayPort,rxd,RxNum);              //柜消息处理
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
void AMPLAY_SwitchIDServer(void)
{
  unsigned char Lbac=LayAddr,Sbac=SegAddr;
  if(0==AMPPro.Time.swicthidtime)
  {
    LayAddr = SWITCHID_ReadLeft(&stLaySwitch);
    SegAddr = LayAddr;
    LayAddr =(LayAddr>>4)&0x0F;
    SegAddr = SegAddr&0x0F;
    
    if((Lbac!=LayAddr)||(Sbac!=SegAddr))
      AMPLAY_GenyConfiguration();
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
void AMPLAY_SYSLED(void)
{
  if(0==AMPPro.Time.SYSLEDTime)
  {    
    GPIO_Toggle	(SYSLEDPort,SYSLEDPin);		//将GPIO相应管脚输出翻转----V20170605
    if(LayAddr&SegAddr)   //已拨码，频率1Hz
    {
      AMPPro.Time.SYSLEDTime=500;
    }
    else          //未拨码，频率5Hz
    {
      AMPPro.Time.SYSLEDTime=100;
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
void AMPLAYSwitchID_Configuration(void)
{
  stLaySwitch.NumOfSW	=	8;
  
  stLaySwitch.SW1_PORT	=	GPIOA;
  stLaySwitch.SW1_Pin	=	GPIO_Pin_7;
  
  stLaySwitch.SW2_PORT	=	GPIOA;
  stLaySwitch.SW2_Pin	=	GPIO_Pin_6;
  
  stLaySwitch.SW3_PORT	=	GPIOA;
  stLaySwitch.SW3_Pin	=	GPIO_Pin_5;
  
  stLaySwitch.SW4_PORT	=	GPIOA;
  stLaySwitch.SW4_Pin	=	GPIO_Pin_4;
  
  stLaySwitch.SW5_PORT	=	GPIOB;
  stLaySwitch.SW5_Pin	=	GPIO_Pin_11;
  
  stLaySwitch.SW6_PORT	=	GPIOB;
  stLaySwitch.SW6_Pin	=	GPIO_Pin_10;
  
  stLaySwitch.SW7_PORT	=	GPIOB;
  stLaySwitch.SW7_Pin	=	GPIO_Pin_2;
  
  stLaySwitch.SW8_PORT	=	GPIOB;
  stLaySwitch.SW8_Pin	=	GPIO_Pin_1;

	SwitchIdInitialize(&stLaySwitch);						//


  LayAddr=(SWITCHID_ReadLeft(&stLaySwitch)>>4)&0X0F;  //层地址
  SegAddr=SWITCHID_ReadLeft(&stLaySwitch)&0x0F;        //位地址

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
void AMPLAY_GenyConfiguration(void)
{
  //--------------------------已拨码
  if(LayAddr&&SegAddr)  
  {
    PWM_OUT(TIM2,PWM_OUTChannel2,1000,1000);						//PWM设定-20161127版本---红色
    PWM_OUT(TIM2,PWM_OUTChannel4,1000,1000);						//PWM设定-20161127版本---黄色
    PWM_OUT(TIM2,PWM_OUTChannel3,1000,1000);						//PWM设定-20161127版本---蓝色
  }
  //--------------------------未拨码
  else
  {
    PWM_OUT(TIM2,PWM_OUTChannel2,2,900);						//PWM设定-20161127版本---红色
    PWM_OUT(TIM2,PWM_OUTChannel4,2,600);						//PWM设定-20161127版本---黄色
    PWM_OUT(TIM2,PWM_OUTChannel3,2,200);						//PWM设定-20161127版本---蓝色
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
void AMPLAYCOMM_Configuration(void)
{ 
  //-----------------------------层板接口USART1 PA11-RE,PA12-TE
  stLayRS485.USARTx  = USART1;
  stLayRS485.RS485_CTL_PORT  = GPIOA;
  stLayRS485.RS485_CTL_Pin   = GPIO_Pin_12;
  RS485_DMA_ConfigurationNR			(&stLayRS485,19200,gDatasize);	//USART_DMA配置--查询方式，不开中断,配置完默认为接收状态
  GPIO_Configuration_OPP50	(GPIOA,GPIO_Pin_11);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605
  GPIO_ResetBits(GPIOA,GPIO_Pin_11);
}
/*******************************************************************************
* 函数名			:	Cabinetmsg_Process
* 功能描述		:	柜消息处理：处理上位机下发消息，处理主柜下发消息，处理层板消息 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
void Msg_ProcessLY(enCCPortDef Port,unsigned char* pBuffer,unsigned short length)
{  
  unsigned  char result       = 0; 
  //unsigned  char address      = 0;  
  unsigned  short framlength  = 0; 
  unsigned  char  Cmd         = 0;  
  unsigned  char* paddrbac    = pBuffer;         //备份数据缓存起始地址
  
  stampphydef* ampframe=NULL;
  //-------------------------检查端口是否为层接口及缓存地址是否为空
  if(LayPort!=Port||NULL==pBuffer)
  {
    return;
  }
  //-------------------------协议检查
  framlength	=	getframe(pBuffer,&length);    //判断帧消息内容是否符合协议
  if(0== framlength)
  {
    memset(paddrbac,0x00,gDatasize);             //清除数据
    return;
  }
  //-------------------------检查是否为应答帧
  result  = ackcheck(pBuffer);                //检查是否为应答消息,应答消息返回1
  if(1==result)
  {
    if(AMPPro.buffer.WaitAck.Lay)
    {
      AMPPro.buffer.WaitAck.Lay=0;
      Releas_OneBuffer(LayPort);        //释放一个发送缓存
    }
    return;
  }
  //-------------------------地址检查

  if(0==addr2check(pBuffer,LayAddr))
    return;
  if(0==addr3check(pBuffer,SegAddr))
    return;

  
  //-------------------------根据地址转发数据：广播数据发送到副柜和本柜层板
  ampframe  = (stampphydef*)pBuffer;
  Cmd = ampframe->msg.cmd.cmd;
  
  //-------------------------下发数据
  if(0  ==  ampframe->msg.cmd.dir)
  {
    //CMD_Process((unsigned char*)ampframe,framlength);
    ackFrame(LayPort,1); //向上应答
    //---------------------------开背光灯命令
    if(LED ==  Cmd) //最高位为0表示上往下发
    {
      if(LayAddr&&SegAddr)
      {
        PWM_OUT(TIM2,PWM_OUTChannel2,2,1000);						//PWM设定-20161127版本---红色
        PWM_OUT(TIM2,PWM_OUTChannel4,2,1000);						//PWM设定-20161127版本---黄色
        PWM_OUT(TIM2,PWM_OUTChannel3,2,1000);						//PWM设定-20161127版本---蓝色
        
        if(ampframe->msg.data[0]) //红灯
          PWM_OUT(TIM2,PWM_OUTChannel2,2,500);						//PWM设定-20161127版本---红色
        if(ampframe->msg.data[1]) //黄色
          PWM_OUT(TIM2,PWM_OUTChannel4,2,500);						//PWM设定-20161127版本---黄色
        if(ampframe->msg.data[2]) //蓝色
          PWM_OUT(TIM2,PWM_OUTChannel3,2,500);						//PWM设定-20161127版本---蓝色
      }
    }
  }
  //-------------------------上传数据
  else
  {    
    return;   //层板端口只接收下发数据，如有上发数据，则为其它层上传，其它层板不处理
  }
}
/*******************************************************************************
* 函数名			:	AMPLAY_SendBuff
* 功能描述		:	消息发送
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
unsigned short AMPLAY_SendBuff(enCCPortDef Port,unsigned char* pBuffer,unsigned short length)
{
  unsigned  short   sendedlen = 0;
  sendedlen = RS485_DMASend(&stLayRS485,pBuffer,length);	//RS485-DMA发送程序
  return  sendedlen;
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
unsigned short AMPLAY_Send(unsigned char* pBuffer,unsigned short length)
{
  return(AddSendBuffer(LayPort,pBuffer,length));
}





