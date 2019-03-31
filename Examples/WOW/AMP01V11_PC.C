#include "AMP01V11_PC.H"


#include "AMP01V11A2.H"

#include	"AMP_PHY.H"

#include "IOT5302W.H"     //读卡器

#include "STM32F10x_BitBand.H"
#include "STM32_GPIO.H"
#include "STM32_SYS.H"
#include "STM32_SYSTICK.H"
#include "STM32_WDG.H"
#include "STM32_PWM.H"
#include "STM32_USART.H"

#include "SWITCHID.H"

#include 	"CRC.H"

#include "string.h"				//串和内存操作函数头文件


static RS485Def stCbRS485Ly;   //uart4,PA15   //层板接口
static RS485Def stCbRS485Cb;   //usart1,PA8    //副柜接口
static RS485Def stCardRS485Ly; //usart3,PB2    //读卡器接口
static SwitchDef stCbSwitch;

static unsigned char CardData[64]={0}; //读卡器接收缓存
static unsigned char CardNum=0;  //读卡器读数计数
static unsigned short InitCardReaderTimeOut=0; //读卡器配置超时时间 10秒
static unsigned char InitCardReaderFlag=0; //读卡器配置标识：0-未配置，1-已配置
static unsigned long InitCardUSART_BaudRate=0; //配置读卡器时使用的波特率
static unsigned char CabAddr   =0;
static unsigned char MainFlag  =0; //0--副柜，1--主柜

static unsigned short RxNum  = 0;
static unsigned char rxd[300]={0};

/*******************************************************************************
*函数名			:	function
*功能描述		:	function
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
void AMP_CABV11_Configuration(void)
{	
	SYS_Configuration();					//系统配置---打开系统时钟 STM32_SYS.H	
  
  AMPCABSwitchID_Configuration();
  
  AMPCAB_GenyConfiguration();   //常规接口配置，背光，锁，电源控制
    
  AMPCABCOMM_Configuration();   //通讯配置
  
  SysTick_DeleymS(1000);				//SysTick延时nmS--等上电稳定

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
void AMP_CABV11_Server(void)
{
  //========================读卡器已配置
  LockServer();       //锁

  RequestServer();    //请求命令处理
  AMPCAB_SwitchIDServer();
  AMPCAB_SYSLED();
  AMPCAB_BackLight();     //背光灯
  API_IOT5302WServer();   //读卡器服务程序
	
	AMPCAB_Receive();
  Send_Server();
}
/*******************************************************************************
*函数名			:	MainBoard_Server
*功能描述		:	主柜空闲服务程序
              1-查询在线设备
              2-查询副柜有无数据上传
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
//void AMP_CABV11_Loop(void)
//{ 
//  //========================读卡器已配置
//  AMPCAB_Receive();
//  Send_Server();
//  
//}
/*******************************************************************************
*函数名			:	CardReaderInitLoop
*功能描述		:	function
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
void CardReaderInitLoop(void)
{
  unsigned char data[64]={0};
  unsigned char RxNum  = 0;
  //---------------------层板接口 USART2
  RxNum = RS485_ReadBufferIDLE(&stCardRS485Ly,data);
  if(RxNum)
  {
    unsigned char i=0;
    if(RxNum>64)
      RxNum=64;
    
    memcpy(&CardData[CardNum],data,RxNum);
    CardNum+=RxNum;
    if(CardNum>=64)
    {
      CardNum=0;
    }
    for(i=0;i<64;i++)
    {
      if(CardData[i]==0xAA)
      {
        if((CardData[i+2]==0x02)  /*长度*/
          &&(CardData[i+3]==0x00) /*状态*/
        &&(CardData[i+4]==0x01)   /*波特率代码19200*/
        &&(CardData[i+6]==0xBB))  /*结束符*/
        {
          InitCardReaderFlag=1;
          InitCardUSART_BaudRate=19200;
          RS485_DMA_ConfigurationNR(&stCardRS485Ly,InitCardUSART_BaudRate,gDatasize);	//USART_DMA配置--查询方式，不开中断,配置完默认为接收状态
        }
      }
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
void AMPCAB_Receive(void)
{
//  unsigned short RxNum  = 0;
//  unsigned char rxd[300]={0};
  //==========================================================接收查询
  //---------------------PC接口 USART1
  RxNum = USART_ReadBufferIDLE(CommPcPort,rxd);
  if(RxNum)
  {
		if(RxNum>maxmsgsize)
			RxNum=maxmsgsize;
    Msg_ProcessCB(PcPort,rxd,RxNum);                //柜消息处理
  }
  //---------------------副柜接口 UART4
  RxNum = RS485_ReadBufferIDLE(&stCbRS485Cb,rxd);
  if(RxNum)
  {
		if(RxNum>maxmsgsize)
			RxNum=maxmsgsize;
    Msg_ProcessCB(CabPort,rxd,RxNum);
  }  
  //---------------------层板接口 USART2
  RxNum = RS485_ReadBufferIDLE(&stCbRS485Ly,rxd);
  if(RxNum)
  {
		if(RxNum>maxmsgsize)
			RxNum=maxmsgsize;
    Msg_ProcessCB(LayPort,rxd,RxNum);              //柜消息处理
  }
  //---------------------读卡器接口 USART3
  RxNum = API_IOT5302WGetUID(rxd);
  if(RxNum)
  {
		if(RxNum>maxmsgsize)
			RxNum=maxmsgsize;
    Msg_ProcessCB(CardPort,rxd,RxNum);
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
void AMPCAB_SwitchIDServer(void)
{
  unsigned char cabaddrbac=CabAddr;
  if(0==AMPPro.Time.swicthidtime)
  {
    CabAddr  = SWITCHID_ReadLeft(&stCbSwitch)&0x3F;
  
    if(SWITCHID_ReadLeft(&stCbSwitch)&0x80)
    {
      MainFlag=1; //0--副柜，1--主柜
    }
    else
    {
      MainFlag=0; //0--副柜，1--主柜
    }
    if(cabaddrbac!=CabAddr)
    {
      AMPCABCOMM_Configuration();   //通讯配置
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
void AMPCAB_SYSLED(void)
{
  if(0==AMPPro.Time.SYSLEDTime)
  {    
    GPIO_Toggle	(SYSLEDPort,SYSLEDPin);		//将GPIO相应管脚输出翻转----V20170605
    if(CabAddr)   //已拨码，频率1Hz
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
*函数名			:	function
*功能描述		:	function
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
void AMPCAB_BackLight(void)
{
  static unsigned short BLtime=0;
  if(0==CabAddr)   //未拨码
  {    
    if(BLtime++>200)
    {
      BLtime=0;
      GPIO_Toggle	(BackLightPort,BackLightPin);		//将GPIO相应管脚输出翻转----V20170605
    }
    return;
  }
  if(AMPPro.Req.BLon)      //背光开关控制
  {
    BackLightOn;
    AMPPro.Req.BLon=0;
  }
  else if(AMPPro.Req.BLoff)
  {
    BackLightOff;
    AMPPro.Req.BLoff=0;
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
void LockServer(void)
{
    //-----------------------------------未拨码自动开锁
    if(0  ==  CabAddr)    //未拨码--自动开锁
    {
      if(GetLockSts)  //如果锁为关闭状态，则开锁
      {
        UnLock;
      }
      else
      {
        ResLock;
      }
      return;
    }
    //-----------------------------------正在执行开锁动作
    if(1==AMPPro.Req.unlockrun)   //正在执行开锁动作
    {
      if(AMPPro.Time.LockTime>unlockOuttime-10)//10ms后开始检查锁状态
      {
        return;
      }
      if(GetLockSts)    //锁未开
      {
        AMPPro.Sta.lockstd  = 1;    //锁状态为ON--锁住
        if(AMPPro.Time.LockTime==0) //超过开锁时间
        {
          AMPPro.Req.unlockrun  = 0;  //开锁标志关闭
          AMPPro.Time.LockTime  = 0;  //开锁时间清除
          LockStatusUpdata(AmpCmdLock,AmpLockOpenFailed);  //开锁失败
          ResLock;
        }
      }
      //----------------------------锁已打开，需要延时关闭锁驱动
      else
      {
        if(0==AMPPro.Req.reslockqust) //延时释放锁驱动
        {
          AMPPro.Req.reslockqust  = 1;  //释放锁驱动请求
          AMPPro.Time.LockTime    = reslockdelaytime;  //延时Nms
        }
        else
        {
          if(0==AMPPro.Time.LockTime)//延时计时时间到
          { 
            AMPPro.Sta.lockstd    = 0;  //锁开状态
            AMPPro.Req.unlockrun  = 0;
            AMPPro.Req.reslockqust= 0;  //释放锁驱动请求标志清除
            AMPPro.Sta.unlockerr  = 0;
            AMPPro.Time.LockTime  = 0;
            ResLock;
            
            LockStatusUpdata(AmpCmdLock,AmpLockOpen);  //锁已打开
          }
        }                
      }      
    }
    //-----------------------------------有开锁请求时数据处理
    if(1==AMPPro.Req.unlockqust)  //开锁请求
    {
      AMPPro.Req.unlockrun  = 1;
      AMPPro.Req.unlockqust = 0;
      AMPPro.Req.reslock    = 0;
      AMPPro.Req.reslockqust=0;   //释放锁驱动请求标志清除
      AMPPro.Sta.unlockerr  = 0;
      
      
      AMPPro.Req.BLon=1;   //开锁需要开背光
      AMPPro.Req.PLon=1;   //开锁层板需要供电
      
      AMPPro.Time.LockTime   = unlockOuttime;    //开锁超时倒计时时间
      UnLock;
    }
    
    //-----------------------------关锁动作
    if(GetLockSts)    //锁未开
    {
      //检查是否为关锁动作
      if(0==AMPPro.Sta.lockstd)//原状态为锁已打开
      {
        AMPPro.Req.BLoff = 1;  //请求关背光
        AMPPro.Req.PLoff = 1;  //请求关闭层板电源
        AMPPro.Flag.LayPownOn=0; 
        
        LockStatusUpdata(AmpCmdLock,AmpLockOn);  //锁已关闭
      }      
      AMPPro.Sta.lockstd  = 1;
      
    }
    else
    {
      if(1==AMPPro.Sta.lockstd) //原状态锁为关闭---手动开锁
      {
        AMPPro.Req.BLon = 1;  //请求打开背光
        AMPPro.Req.PLon = 1;  //请求打开层板电源
        AMPPro.Flag.LayPownOn=1;
        
        LockStatusUpdata(AmpCmdLock,AmpLockOpen);  //锁已打开
      }
      AMPPro.Sta.lockstd  = 0;
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
void AMPCABSwitchID_Configuration(void)
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
void AMPCAB_GenyConfiguration(void)
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
void AMPCABCOMM_Configuration(void)
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
/*******************************************************************************
*函数名			:	function
*功能描述		:	function
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
unsigned short AMPCAB_SendBuff(enCCPortDef Port,unsigned char* pBuffer,unsigned short length)
{ 
  unsigned  short   sendedlen = 0;
  switch(Port)
  {
    case  NonPort   : return 0;   //不继续执行
    case  PcPort    : sendedlen = api_usart_dma_send(CommPcPort,pBuffer,length);
      break;
    case  CabPort   : sendedlen = RS485_DMASend(&stCbRS485Cb,pBuffer,length);	//RS485-DMA发送程序
      break;
    case  LayPort   : sendedlen = RS485_DMASend(&stCbRS485Ly,pBuffer,length);	//RS485-DMA发送程序
      break;
    case  CardPort  : sendedlen = RS485_DMASend(&stCardRS485Ly,pBuffer,length);	//RS485-DMA发送程序
      break;
    default :return 0;      //不继续执行
  }
  return  sendedlen;
}
/*******************************************************************************
*函数名			:	function
*功能描述		:	往PC发送消息
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
unsigned short PCnet_Send(unsigned char* pBuffer,unsigned short length)
{
  return(AddSendBuffer(PcPort,pBuffer,length));
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
  return(AddSendBuffer(CabPort,pBuffer,length));
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
  return(AddSendBuffer(LayPort,pBuffer,length));
}
/*******************************************************************************
*函数名			:	function
*功能描述		:	往读卡器接口发送消息
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
unsigned short CardPort_Send(unsigned char* pBuffer,unsigned short length)
{
  return(AddSendBuffer(CardPort,pBuffer,length));
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
void Msg_ProcessCB(enCCPortDef Port,unsigned char* pBuffer,unsigned short length)
{  
  switch(Port)
  {
    case PcPort:Msg_ProcessPcPort(Port,pBuffer,length);     //PC端口
      break;
    case CabPort:Msg_ProcessCbPort(Port,pBuffer,length);    //柜端口
      break;
    case LayPort:Msg_ProcessLyPort(Port,pBuffer,length);    //层端口
      break;
    case CardPort:Msg_ProcessCaPort(Port,pBuffer,length);   //读卡器端口
      break;
    default:
      break;
  }
}
/*******************************************************************************
* 函数名			:	Msg_ProcessPcPort
* 功能描述		:	柜消息处理：处理上位机下发消息，处理主柜下发消息，处理层板消息 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
void Msg_ProcessPcPort(enCCPortDef Port,unsigned char* pBuffer,unsigned short length)
{  
  unsigned  char result       = 0; 
  unsigned  char address      = 0;  
  unsigned  short framlength  = 0; 
  unsigned  char  Cmd         = 0;  
  unsigned  char* paddrbac    = pBuffer;         //备份数据缓存起始地址
  
  stampphydef* ampframe=NULL;
  //-------------------------检查端口是否为层接口及缓存地址是否为空
  if(PcPort!=Port||NULL==pBuffer)
  {
    return;
  } 
  //-------------------------协议检查
  framlength	=	getframe(pBuffer,&length);    //判断帧消息内容是否符合协议
  if(0== framlength)
  {
    memset(paddrbac,0x00,gDatasize);          //清除数据
    return;
  }
  result  = ackcheck(pBuffer);                //检查是否为应答消息,应答消息返回1  
  if(1==result)
  {
    if(AMPPro.buffer.WaitAck.Pc)      //如果为等待应答状态，则释放一个缓存
    {
      AMPPro.buffer.WaitAck.Pc=0;
      Releas_OneBuffer(Port);        //释放一个发送缓存
    }
    return;
  }  
  //-------------------------根据地址转发数据：广播数据发送到副柜和本柜层板
  ampframe  = (stampphydef*)pBuffer;
  Cmd = ampframe->msg.cmd.cmd;  
  
  //-------------------------上传数据:柜接口
  //主柜：接收到的数据上传到PC并向下应答
  //副柜：接收到下发数据判断地址,如果地址为本地址，向上应答(广播地址不应答)，如果是上传数据，不处理
  //1）-----------------上传数据:PC接口只接收下发数据

  //2）-----------------下发数据：地址为本地址或者广播地址(0xFF)需要进行处理，如果地址为本地址，向上应答(广播地址不应答)
  if(MainFlag)  //0--副柜，1--主柜
  {
  }
  address=ampframe->msg.addr.address1;
  if(0==address)      //柜地址为空
  {
    return;
  }
  //----------------------------PC接口都要应答
  ackFrame(Port,1);             //向上应答---取消PC应答
  
  if((CabAddr!=address))  //不属于主柜消息
  {
    
    Cabinet_Send((unsigned char*)ampframe,framlength);//往副柜发送
    if(0xFF==address) //广播地址
    {      
      AMPPro.buffer.WaitAck.Cab=0;   //不需要副柜应答      
    }
    else
    {
      //ackFrame(Port,1);             //向上应答
      AMPPro.buffer.WaitAck.Cab=1;  //需要副柜应答
      return;       //其它柜数据，退出
    }
  }
  //===================================接收到的数据为本柜可接收数据(本柜地址或者广播地址(0xFF))
  //1)-----------------检查层地址，判断是否需要将数据发往层，发往层时，需要开锁，开背光灯
  
  //2)-----------------层地址为0，不需要往下发，只在柜控制板处理：灯控制/锁控制/供电
  if((AmpCmdLed == Cmd)||(AmpCmdLcdData == Cmd)||(AmpCmdLcdConf == Cmd))       //LED/LCD控制
  {
    if((0x00==ampframe->msg.addr.address2)||(0x00==ampframe->msg.addr.address3))//广播地址
    {
      return;   //层或者柜地址不正确
    }
    else if((0xFF==ampframe->msg.addr.address2)||(0xFF==ampframe->msg.addr.address3))//广播地址
    {
      AMPPro.buffer.WaitAck.Lay=0;   //不需要应答
    }
    else
    {
      AMPPro.buffer.WaitAck.Lay=1;   //需要应答
    }
    AMPPro.Req.PLon  =1;    //层板供电
    AMPPro.Req.PLoff =0;    
    Laynet_Send((unsigned char*)ampframe,framlength);     //往层板发送消息
  }
	else if(AmpCmdLcdPwr ==  Cmd)   //LCD电源供电控制指令
  {
		AMPPro.Req.PLon  =0;
    AMPPro.Req.PLoff =0;
		if(0==ampframe->msg.data[0])
      AMPPro.Req.PLoff=1;
	}
  else if(AmpCmdPwr ==  Cmd)   //层板供电控制命令
  {
    AMPPro.Req.PLon  =0;
    AMPPro.Req.PLoff =0;
    
    if(ampframe->msg.data[0])
      AMPPro.Req.PLon=1;
    else
      AMPPro.Req.PLoff=1;
  }
  else if(AmpCmdLock ==  Cmd)   //锁控制命令
  {
    AMPPro.Req.reslock  =0;
    AMPPro.Req.unlockqust =0;
    
    if(ampframe->msg.data[0])
      AMPPro.Req.unlockqust=1;
    else
      AMPPro.Req.reslock=1;
  }
  else if(AmpCmdBKligth ==  Cmd)   //背光控制指令
  {
    AMPPro.Req.BLon     =0;
    AMPPro.Req.BLoff    =0;
    
    if(ampframe->msg.data[0])
      AMPPro.Req.BLon=1;
    else
      AMPPro.Req.BLoff=1;    
  }
  else if(AmpCmdSta ==  Cmd)   //查询状态
  {
    if(0==AMPPro.Sta.lockstd) //开状态
    {
      LockStatusUpdata(AmpCmdSta,AmpLockOpen);  //锁---开状态
    }
    else
    {
      LockStatusUpdata(AmpCmdSta,AmpLockOn);  //锁---关状态
    }
  }
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
void Msg_ProcessCbPort(enCCPortDef Port,unsigned char* pBuffer,unsigned short length)
{  
  unsigned  char result       = 0; 
  unsigned  char address      = 0;  
  unsigned  short framlength  = 0; 
  unsigned  char  Cmd         = 0;  
  unsigned  char* paddrbac    = pBuffer;         //备份数据缓存起始地址
  
  stampphydef* ampframe=NULL;
  //-------------------------检查端口是否为层接口及缓存地址是否为空
  if(CabPort!=Port||NULL==pBuffer)
  {
    return;
  } 
  //-------------------------协议检查
  framlength	=	getframe(pBuffer,&length);    //判断帧消息内容是否符合协议
  if(0== framlength)
  {
    //memset(paddrbac,0x00,gDatasize);             //清除数据
    return;
  }
  result  = ackcheck(pBuffer);                //检查是否为应答消息,应答消息返回1  
  if(1==result)
  {
    if(AMPPro.buffer.WaitAck.Cab)           //如果为等待应答状态，则释放一个缓存
    {
      AMPPro.buffer.WaitAck.Cab=0;
      Releas_OneBuffer(Port);               //释放一个发送缓存
    }
    return;
  }  
  //-------------------------根据地址转发数据：广播数据发送到副柜和本柜层板
  ampframe  = (stampphydef*)pBuffer;
  Cmd = ampframe->msg.cmd.cmd;  
  
  //-------------------------上传数据:柜接口
  //主柜：接收到的数据上传到PC并向下应答
  //副柜：接收到下发数据判断地址,如果地址为本地址，向上应答(广播地址不应答)，如果是上传数据，不处理
  //1）-----------------上传数据:PC接口只接收下发数据
  if(ampframe->msg.cmd.dir)   //0-down,1-up---高8位
  {
    if(MainFlag)    //0--副柜，1--主柜
    {
      ackFrame(Port,0); //向下应答---主柜应答副柜
      AMPPro.buffer.WaitAck.Pc=1;   //需要PC应答
      PCnet_Send((unsigned char*)ampframe,framlength);      //往PC发送消息
    }
    return;   //任务完成
  }
  //2）-----------------下发数据：地址为本地址或者广播地址(0xFF)需要进行处理，如果地址为本地址，向上应答(广播地址不应答)
  address=ampframe->msg.addr.address1;
  if(0==address)      //柜地址为空
  {
    return;
  }
  if((CabAddr!=address)&&(0xFF!=address))  //不属于此柜消息
  {
    return;
  }
  if(CabAddr==address)
    ackFrame(Port,1);             //向上应答
  //===================================接收到的数据为本柜可接收数据(本柜地址或者广播地址(0xFF))
  if((AmpCmdLed == Cmd)||(AmpCmdLcdData == Cmd)||(AmpCmdLcdConf == Cmd))       //LED/LCD控制
  {
    if((0x00==ampframe->msg.addr.address2)||(0x00==ampframe->msg.addr.address3))//广播地址
    {
      return;   //退出---层或者柜地址不正确
    }
    else if((0xFF==ampframe->msg.addr.address2)||(0xFF==ampframe->msg.addr.address3))//广播地址
    {
      AMPPro.buffer.WaitAck.Lay=0;   //不需要应答
    }
    else
    {
      AMPPro.buffer.WaitAck.Lay=1;   //需要应答
    }
    AMPPro.Req.PLon  =1;    //层板供电
    AMPPro.Req.PLoff =0;
    Laynet_Send((unsigned char*)ampframe,framlength);     //往层板发送消息
  }
	else if(AmpCmdLcdPwr ==  Cmd)   //LCD电源供电控制指令
  {
		AMPPro.Req.PLon  =0;
    AMPPro.Req.PLoff =0;
		if(0==ampframe->msg.data[0])
      AMPPro.Req.PLoff=1;
	}
  else if(AmpCmdPwr ==  Cmd)   //层板供电控制命令
  {
    AMPPro.Req.PLon  =0;
    AMPPro.Req.PLoff =0;
    
    if(ampframe->msg.data[0])
      AMPPro.Req.PLon=1;
    else
      AMPPro.Req.PLoff=1;
  }
  else if(AmpCmdLock ==  Cmd)   //锁控制命令
  {
    AMPPro.Req.reslock  =0;
    AMPPro.Req.unlockqust =0;
    
    if(ampframe->msg.data[0])
      AMPPro.Req.unlockqust=1;
    else
      AMPPro.Req.reslock=1;
  }
  else if(AmpCmdBKligth ==  Cmd)   //背光控制指令
  {
    AMPPro.Req.BLon     =0;
    AMPPro.Req.BLoff    =0;
    
    if(ampframe->msg.data[0])
      AMPPro.Req.BLon=1;
    else
      AMPPro.Req.BLoff=1;    
  }
  else if(AmpCmdSta ==  Cmd)   //查询状态
  {
    if(0==AMPPro.Sta.lockstd) //开状态
    {
      LockStatusUpdata(AmpCmdSta,AmpLockOpen);  //锁---开状态
    }
    else
    {
      LockStatusUpdata(AmpCmdSta,AmpLockOn);    //锁---关状态
    }
  }
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
void Msg_ProcessCaPort(enCCPortDef Port,unsigned char* pBuffer,unsigned short length)
{  
  CardDataSendUp(Port,pBuffer,length);
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
void Msg_ProcessLyPort(enCCPortDef Port,unsigned char* pBuffer,unsigned short length)
{  
  unsigned  char result       = 0; 
  //unsigned  char address      = 0;  
  unsigned  short framlength  = 0; 
  //unsigned  char  Cmd         = 0;  
  unsigned  char* paddrbac    = pBuffer;         //备份数据缓存起始地址
  
  stampphydef* ampframe=NULL;
  
  framlength=length;
  
  //-------------------------协议检查
  framlength	=	getframe(paddrbac,&framlength);    //判断帧消息内容是否符合协议
  if(0== framlength)    //不符合协议，做透传---读卡器
  {
//    CardDataSendUp(Port,pBuffer,length);
    return;
  }
  
  pBuffer=paddrbac;  
  result  = ackcheck(pBuffer);                //检查是否为应答消息,应答消息返回1  
  if(1==result)
  {
    if(AMPPro.buffer.WaitAck.Lay)      //如果为等待应答状态，则释放一个缓存
    {
      AMPPro.buffer.WaitAck.Lay=0;
      Releas_OneBuffer(Port);        //释放一个发送缓存
    }
    return;
  }  
  //-------------------------根据地址转发数据：广播数据发送到副柜和本柜层板
  ampframe  = (stampphydef*)pBuffer;
  //Cmd = ampframe->msg.cmd.cmd;
  
  //-------------------------处理说明：柜板--LyPort口根据方向判断为层板还是柜板，柜板下发，层板上传
  //-------------------------上传数据:柜接口
  //柜板：接收的数据方向为上传，应答或者数据，不符合协议的内容则透传
  //层板：接收到的数据为下发数据，应答或者命令，不符合协议的内容不处理
  //1）-----------------上传数据:柜接收的数据为上传数据，如果不是应答，则需要加上柜地址，再打包通过柜/PC接口上传
  if(1==ampframe->msg.cmd.dir)
  {
    unsigned  char  databuffer[64]={0};
    
    ackFrame(Port,0); //向下应答    
       
    //-------------------------读卡器端口接收到数据
    memcpy(databuffer,pBuffer,length);
    framlength  = length;
    framlength  = PackUpMsg(databuffer,AmpCmdCard,&framlength);
    //-------------------------设置地址:柜控制板地址段为address1
    ampframe  = (stampphydef*)databuffer;
    ampframe->msg.addr.address1 = CabAddr;
    //-------------------------设置CRC和结束符
    SetFrame(databuffer,&framlength);   //补充消息的CRC和结束符，返回帧长度
    //-------------------------检查本柜是否为主柜
    if(1==MainFlag)   //主柜--通过PC接口上传
    {
      AMPPro.buffer.WaitAck.Pc=1;   //需要应答
      PCnet_Send(databuffer,framlength);
    }
    else  //副柜--通过副柜接口上传
    {
      AMPPro.buffer.WaitAck.Cab=1;   //需要应答
      Cabinet_Send(databuffer,framlength);     //往副柜发送消息
    }    
    return;
  }
  //2）-----------------下发数据：只有层板会接收下发数据
  else
  {
    return;
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
void CardDataSendUp(enCCPortDef Port,unsigned char* pBuffer,unsigned short length)
{
  //unsigned  char result       = 0; 
  //unsigned  char address      = 0;  
  unsigned  short framlength  = 0;  
  //unsigned  char* paddrbac    = pBuffer;         //备份数据缓存起始地址
  
  stampphydef* ampframe=NULL;
  //stcmddef    Cmd;
  
  unsigned  char  databuffer[64]={0};   
  //-------------------------读卡器端口接收到数据
  memcpy(databuffer,pBuffer,length);
  framlength  = length;
  framlength  = PackUpMsg(databuffer,AmpCmdCard,&framlength);
  
  //-------------------------设置地址:柜控制板地址段为address1
  ampframe  = (stampphydef*)databuffer;
  ampframe->msg.addr.address1 = CabAddr;    //柜地址
  ampframe->msg.addr.address2 = 0;
  ampframe->msg.addr.address3 = 0;
  //-------------------------设置CRC和结束符
  SetFrame(databuffer,&framlength);//补充消息的CRC和结束符，返回帧长度
  
  if(MainFlag)  //0--副柜，1--主柜
  {
    AMPPro.buffer.WaitAck.Pc=1;   //需要应答
    PCnet_Send(databuffer,framlength);    //往副柜发送消息
  }
  else
  {
    AMPPro.buffer.WaitAck.Cab=1;   //需要应答
    Cabinet_Send(databuffer,framlength);    //往副柜发送消息
  }
  return;
}
/*******************************************************************************
*函数名			:	RequestServer
*功能描述		:	请求命令处理
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
void RequestServer(void)
{    
  //-------------------层板供电
    if(AMPPro.Req.PLon)    //层板供电控制
    {      
      LayPowerOn;
      AMPPro.Req.PLon=0;
      AMPPro.Flag.LayPownOn=1;
    }
    else if(AMPPro.Req.PLoff)
    {
      LayPowerOff;
      AMPPro.Req.PLoff=0;
      AMPPro.Flag.LayPownOn=0;
    }
//    //-------------------背光
//    if(AMPPro.Req.BLon)
//    {
//      BackLightOn;
//      AMPPro.Req.BLon=0;
//      AMPPro.Flag.LayPownOn=0;
//    }
//    else if(AMPPro.Req.BLoff)
//    {
//      BackLightOff;
//      AMPPro.Req.BLoff=0;
//      AMPPro.Flag.LayPownOn=0;
//    }
}
/*******************************************************************************
*函数名			:	LockStatusUpdata
*功能描述		:	上报锁状态
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
void LockStatusUpdata(eucmddef Cmd,eLockStsdef std)
{
  unsigned char databuffer[32]={0};
  unsigned short framlength = 0;  //生成的消息长度
  unsigned short datalength = 2;  //需要上报的数据字节数
  stampphydef* ampframe=NULL;
  //-------------------------锁状态上报：第一字节为锁标识，第二字节为状态
  databuffer[0] = AmpStsLock;
  databuffer[1] = std;
  //-------------------------按状态上报类型打包消息
  framlength  = PackUpMsg(databuffer,Cmd,&datalength); 
  //-------------------------打包完成的数据转换为消息帧
  ampframe  = (stampphydef*)databuffer;
  //-------------------------添加地址
  ampframe->msg.addr.address1 = CabAddr;  //当前柜地址
  ampframe->msg.addr.address2 = 0;
  ampframe->msg.addr.address3 = 0;
  //-------------------------设置CRC和结束符
  framlength  = SetFrame(databuffer,&framlength);//补充消息的CRC和结束符，返回帧长度
  //-------------------------选择上报路径
  if(MainFlag)  //0--副柜，1--主柜
  {
    AMPPro.buffer.WaitAck.Pc=1;   //需要应答
    PCnet_Send(databuffer,framlength);    //往副柜发送消息
  }
  else
  {
    AMPPro.buffer.WaitAck.Cab=1;   //需要应答
    Cabinet_Send(databuffer,framlength);    //往副柜发送消息
  }
}
/*******************************************************************************
*函数名			:	LockStatusUpdata
*功能描述		:	上报锁状态
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
void CommTimeOutUpdata(enCCPortDef Port,stampaddrdef address)
{
  unsigned char databuffer[32]={0};
  unsigned short framlength = 0;  //生成的消息长度
  unsigned short datalength = 2;  //需要上报的数据字节数
  stampphydef* ampframe=NULL;
  //-------------------------锁状态上报：第一字节为锁标识，第二字节为状态
  databuffer[0] = AmpStsComm;       //连接状态标识
  databuffer[1] = AmpCommTimeOut;   //连接超时
  //-------------------------按状态上报类型打包消息
  framlength  = PackUpMsg(databuffer,AmpCmdSta,&datalength); 
  //-------------------------打包完成的数据转换为消息帧
  ampframe  = (stampphydef*)databuffer;
  //-------------------------添加地址
  ampframe->msg.addr.address1 = address.address1;  //当前柜地址
  ampframe->msg.addr.address2 = address.address2;
  ampframe->msg.addr.address3 = address.address3;
  
  switch(Port)
  {
    case  NonPort   : return ;   //不继续执行
    case  PcPort    : return;    //PC接口发送缓存
      break;
    case  CabPort   ://柜接口发送缓存
                      ampframe->msg.addr.address2 = 0;
                      ampframe->msg.addr.address3 = 0;
      break;
    case  LayPort   ://层接口发送缓存
      break;
    case  CardPort  ://读卡器接口发送缓存
                      ampframe->msg.addr.address2 = 0;
                      ampframe->msg.addr.address3 = 0;
      break;
    default :return;      //不继续执行 
  }
  //-------------------------设置CRC和结束符
  framlength  = SetFrame(databuffer,&framlength);//补充消息的CRC和结束符，返回帧长度
  //-------------------------选择上报路径
  if(MainFlag)  //0--副柜，1--主柜
  {
    AMPPro.buffer.WaitAck.Pc=1;   //需要应答
    PCnet_Send(databuffer,framlength);    //往副柜发送消息
  }
  else
  {
    AMPPro.buffer.WaitAck.Cab=1;   //需要应答
    Cabinet_Send(databuffer,framlength);    //往副柜发送消息
  }
}


