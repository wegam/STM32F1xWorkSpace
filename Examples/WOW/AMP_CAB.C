#ifdef AMP_CAB

#include "AMP_CAB.H"

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
unsigned  long*  MCUMEMaddr = (unsigned  long*)(0x1FFFF7E0);
unsigned  short  MCUMEMsize  = 0;
unsigned  short seril=0;
unsigned  char  ackupfarme[]=
{
  0x7E,
  0x02,
  0x81,
  0x00,
  0xB0,
  0x50,
  0x7F
};
unsigned  char  ackdownfarme[]=
{
  0x7E,
  0x02,
  0x01,
  0x00,
  0xD1,
  0x90,
  0x7F
};
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
  MCUMEMsize  = *MCUMEMaddr;
  if(0x0100 ==  MCUMEMsize) //256K Flash 柜控制板STM32F103RC
  {
    AMP.Flag.CabBD  = 1;
    AMP.Flag.LayBD  = 0;
    AMP.Flag.SetBD  = 0;
  }
  else if(0x0080 ==  MCUMEMsize) //128K Flash 层控制板STM32F103CB
  {
    AMP.Flag.CabBD  = 0;
    AMP.Flag.LayBD  = 1;
    AMP.Flag.SetBD  = 1;
  }
	SYS_Configuration();					//系统配置---打开系统时钟 STM32_SYS.H	 
	
//  IWDG_Configuration(1000);													//独立看门狗配置---参数单位ms
  
  SysTick_Configuration(1000);    //系统嘀嗒时钟配置72MHz,单位为uS
  
  SwitchID_Configuration();
  
  GenyConfiguration();   //常规接口配置，背光，锁，电源控制
    
  COMM_Configuration();  
 
	PWM_OUT(TIM2,PWM_OUTChannel1,2,950);						//PWM设定-20161127版本

  while(1)
  {
    AMP01_Loop();
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
void AMP01_Server(void)
{  
  SwitchID_Server();
  if(0  ==  AMP.SwData.ID)
  {
    AMP.Time.runningtime++;
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
  LockServer();
  Tim_Server();
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
void AMP01_Loop(void)
{
  if(0  ==  AMP.SwData.ID)
  {
    if(AMP.Time.runningtime>=500)
    {
      GPIO_Toggle	(BackLightPort,BackLightPin);		//将GPIO相应管脚输出翻转----V20170605
      AMP.Time.runningtime  = 0;
    }
    return;
  }
  Receive_Server();
  Send_Server();
}

//=================================软件接口ST=============================================================
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
void MainCabinet_IDLEServer(void)
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
void Send_Server(void)
{
  //----------------PC发送
  if(0  ==  AMP.Time.PcSendTime)
  {
    Check_SendBuff(PcPort);
  }
  //----------------柜发送
  if(0  ==  AMP.Time.CabSendTime)
  {
    Check_SendBuff(CabPort);
  }
  //----------------层发送
  if(0  ==  AMP.Time.LaySendTime)
  {
    Check_SendBuff(LayPort);
  }
  //----------------读卡器发送
  if(0  ==  AMP.Time.CardSendTime)
  {
    Check_SendBuff(CardPort);
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
unsigned short Check_SendBuff(enCCPortDef Port)
{ 
  unsigned  char  i  = 0;
  unsigned  short  SendLen  = 0;
  unsigned  char  ackflag =0;
  unsigned  char  ackdir =0;
  unsigned  char* SendAddr = NULL;  
  unsigned  char*  ReSendCount;      //PC上传重发计数
  
  unsigned  short*  SendTime=NULL;
  
  stTxdef* Txd  = NULL;
  
  if(LayPort  ==  Port) //层板：需要检查供电有无打开
  {
    if(0  ==  AMP.Flag.LayPownOn) //供电未打开
    {
      return  0;
    }
  }
  
  //------------------------------检查重发
  switch(Port)
  {
    case  NonPort   : return 0;   //不继续执行
    case  PcPort    : ReSendCount = &AMP.ReSend.PcCount;
                      Txd=AMP.buffer.PcTx;    //PC接口发送缓存
                      SendTime  = &AMP.Time.PcSendTime;
                      ackflag = AMP.AckQ.PcAck;
                      ackdir  = AMP.AckQ.PcDir;
      break;
    case  CabPort   : ReSendCount = &AMP.ReSend.CabCount;
                      Txd=AMP.buffer.CabTx;   //柜接口发送缓存
                      SendTime  = &AMP.Time.CabSendTime;
                      ackflag = AMP.AckQ.CabAck;
                      ackdir  = AMP.AckQ.CabDir;
      break;
    case  LayPort   : ReSendCount = &AMP.ReSend.LayCount;
                      Txd=AMP.buffer.LayTx;   //层接口发送缓存
                      SendTime  = &AMP.Time.LaySendTime;
                      ackflag = AMP.AckQ.LayAck;
                      ackdir  = AMP.AckQ.LayDir;
      break;
    case  CardPort  : ReSendCount = &AMP.ReSend.CardCount;
                      Txd=AMP.buffer.CardTx;  //读卡器接口发送缓存
                      SendTime  = &AMP.Time.CardSendTime;
                      ackflag = 0;
      break;
    default :return 0;      //不继续执行 
  }
  if(ackflag) //有应答请求，先应答
  {
    if(ackdir)  //向上应答
      SendLen = HW_SendBuff(Port,ackupfarme,sizeof(ackupfarme));   //返回已发送字节
    else
      SendLen = HW_SendBuff(Port,ackdownfarme,sizeof(ackdownfarme));   //返回已发送字节
    if(SendLen)   //应答发送成功---清除标志请求
    {
      switch(Port)
      {
        case  NonPort   : return 0;   //不继续执行
        case  PcPort    : AMP.AckQ.PcAck = 0;
          break;
        case  CabPort   : AMP.AckQ.CabAck = 0;
          break;
        case  LayPort   : AMP.AckQ.LayAck = 0;
          break;
        case  CardPort  : AMP.AckQ.CardAck  = 0;
          break;
        default :return 0;      //不继续执行 
      }
    }
    *SendTime  = 10;
    return  0;
  }
  if(*SendTime>0)   //不到重发时间，退出
  {
    return  0;
  }
  if(*ReSendCount>=maxresendcount) //超出重发次数：放弃发送
  {
    Releas_OneBuffer(Port);
    *ReSendCount  = 0;      //重发清零
  }
  //------------------------------检查发送缓存
  for(i=0;i<arrysize;i++)
  {
    if(1  ==  Txd[i].arry)
    {
      SendAddr  = Txd[i].data;    //起始地址
      SendLen   = Txd[i].size;    //大小
    }
  }
  //-----------------------------有发数据 
  if(NULL!= SendAddr)
  {
    SendLen = HW_SendBuff(Port,SendAddr,SendLen);   //返回已发送字节
    if(SendLen)   //成功发送到缓存
    {
      *ReSendCount +=1;
      *SendTime = ReSendWaitTime;
    }
    else
    {
      *SendTime = ReSendWaitTime;
    }
    return  SendLen;
  }
  return  0;
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
void Msg_Process(enCCPortDef Port,unsigned char* pBuffer,unsigned short length)
{  
  unsigned  char result       = 0; 
  unsigned  char address      = 0;  
  unsigned  short framlength  = 0;  
  unsigned  char* paddrbac    = pBuffer;         //备份数据缓存起始地址
  
  stampphydef* ampframe=NULL;
  stcmddef    Cmd;
  //-------------------------读卡器端口
  if(CardPort  == Port)   //读卡器接口无协议，只打包数据透传
  {
    unsigned  char  databuffer[64]={0};   
    //-------------------------读卡器端口接收到数据
    memcpy(databuffer,pBuffer,length);
    framlength  = length;
    framlength  = PaketUpMsg(databuffer,ICR,&framlength);
    //-------------------------设置地址:柜控制板地址段为address1
    ampframe  = (stampphydef*)databuffer;
    ampframe->msg.addr.address1 = AMP.SwData.ID;
    ampframe->msg.addr.address2 = 0;
    ampframe->msg.addr.address3 = 0;
    //-------------------------设置CRC和结束符
    SetCrc(databuffer,&framlength);
    //-------------------------检查本柜是否为主柜
    if(1==AMP.SwData.MainFlg)   //主柜--通过PC接口上传
    {
      PCnet_Send(databuffer,framlength);
    }
    else  //副柜--通过副柜接口上传
    {
      //PCnet_Send(databuffer,framlength);
      Cabinet_Send(databuffer,framlength);     //往副柜发送消息
    }
    return;
  }
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
    Releas_OneBuffer(Port);        //释放一个发送缓存
    return;
  }
  
  
  //-------------------------根据地址转发数据：广播数据发送到副柜和本柜层板
  ampframe  = (stampphydef*)pBuffer;
  Cmd = ampframe->msg.cmd;
  
  //-------------------------下发数据
  if(0  ==  Cmd.dir)
  {    
    if(PcPort == Port)
    {
      ackFrame(Port,1); //向上应答
      if(AMP.SwData.ID  ==  ampframe->msg.addr.address1)    //柜地址
      {
        goto CabinetSelfDownDataProcess;
      }
      else if(0xFF  ==  ampframe->msg.addr.address1)      //广播地址--对所有柜
      {
        Cabinet_Send((unsigned char*)ampframe,framlength);           //往副柜发送消息
        goto CabinetSelfDownDataProcess;
      }
      else
      {
        Cabinet_Send((unsigned char*)ampframe,framlength);           //往副柜发送消息
        return;
      }
    }
    else if(CabPort == Port)    //柜接口接收到下发数据要做地址判断
    {
      if(AMP.SwData.ID  ==  ampframe->msg.addr.address1)
      {
        ackFrame(CabPort,1); //向上应答
        //goto CabinetSelfDownDataProcess;
      }
      else if(0xFF  ==  ampframe->msg.addr.address1)  //广播数据
      {
        //goto CabinetSelfDownDataProcess;
      }
      else    //其它柜数据：退出，不处理
      {
        return;
      }
      goto CabinetSelfDownDataProcess;
    }
    else if(LayPort == Port)
    {
      CMD_Process((unsigned char*)ampframe,framlength);
    }    
  }
  //-------------------------上传数据
  else
  {    
    if(PcPort == Port)    //PC口只下发消息
    {
      return;
    }
    else if(CabPort == Port)  //柜接口接收到数据，如果为主机，则应答，再上传到PC端口，如果是副柜，上传到PC端口，不应答
    {
      if(AMP.SwData.MainFlg)
      {
        ackFrame(Port,0);   //向下应答
      }
      PCnet_Send((unsigned char*)ampframe,framlength);     //往PC发送消息
      return;
    }
    else if(LayPort == Port)
    {
      ackFrame(Port,0);   //向下应答
      goto CabinetSelfUpDataProcess;
    }
  }
  
  return;
  
  //----------------------下发消息需要本柜处理时会执行此过程
  CabinetSelfDownDataProcess:     //本柜接收到的上级下发消息处理：根据第二级地址确定是否需要转发
  
  //---------------------检查此消息是否需要转发到层
  if(0x00 != ampframe->msg.addr.address2)   //层地址不为0表示需要转发
  {
    Laynet_Send((unsigned char*)ampframe,framlength);     //往层板发送消息
  }
  //---------------------不需要转发，消息内容针对柜控制板
  else
  {
    CMD_Process(pBuffer,framlength);
  }
  return;
  
  //----------------------上报类型的消息address1为0时会执行此过程
  CabinetSelfUpDataProcess:     //接收到层上报的消息：需要添加柜地址，如果本柜为主柜，则上传到PC，如果为副柜，则上传到主柜
  //----------------------补充数据
  ampframe->msg.addr.address1 = AMP.SwData.ID;    //添加ID
  ampframe->msg.cmd.dir       = 1;                //传输方向设定为上传模式
  SetCrc((unsigned char*)ampframe,&framlength);   //重新计算CRC
  //----------------------根据是否为主柜选择消息传输接口
  if(AMP.SwData.MainFlg)        //主柜：通过PC接口上传
  {
    PCnet_Send((unsigned char*)ampframe,framlength);     //往PC发送消息
  }
  else    //辅柜：上传到PC端口和副柜接口
  {
    PCnet_Send((unsigned char*)ampframe,framlength);     //往PC发送消息
    Cabinet_Send((unsigned char*)ampframe,framlength);  //通过柜接口向主柜发送消息
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
void CMD_Process(unsigned char* pBuffer,unsigned short length)
{
  unsigned  short datalen     = 0; 
  stampphydef* ampframe       = NULL;
  eucmddef*    cmd  = NULL;
  
  ampframe  = (stampphydef*)pBuffer;
  cmd = (eucmddef*)&ampframe->msg.cmd;
  //---------------------------上位机下发读卡器命令
  if(ICR ==  (*cmd&Down)) //最高位为0表示上往下发
  {
    datalen = ampframe->msg.length-4;   //减一命令位，三地址位长度
    CardPort_Send(ampframe->msg.data,datalen);   //往读卡器接口发数据
    return;
  }
  //---------------------------开锁命令
  if(CTL ==  (*cmd&Down)) //最高位为0表示上往下发
  {
    if(0  ==  ampframe->msg.data[0])    //0为开锁命令
    {
      UnLock;   //开锁
    }
    else
    {
      ResLock;  //释放锁
    }
    return;
  }
  //---------------------------开背光灯命令
  if(LED ==  (*cmd&Down)) //最高位为0表示上往下发
  {
    if(0  !=  ampframe->msg.data[0])    //1为开LED
    {
      BackLightOn;   //开LED
    }
    else
    {
      BackLightOff;  //关LED
    }
    return;
  }
}
/*******************************************************************************
*函数名			:	function
*功能描述		:	function
*输入				: 
*返回值			:	dir:0向下应答，1向上应答
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
void ackFrame(enCCPortDef Port,unsigned char dir)
{
  switch(Port)
  {
    case  NonPort   : return;   //不继续执行
    case  PcPort    : AMP.AckQ.PcAck  = 1;
                      AMP.AckQ.PcDir  = dir;
      break;
    case  CabPort   : AMP.AckQ.CabAck  = 1;
                      AMP.AckQ.CabDir  = dir;
      break;
    case  LayPort   : AMP.AckQ.LayAck  = 1;
                      AMP.AckQ.LayDir  = dir;
      break;
    //case  CardPort  : AMP.AckQ.CardAck  = 1;
    //                    AMP.AckQ.CardDir  = dir;
      //break;
    default :return;      //不继续执行 
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
unsigned short Releas_OneBuffer(enCCPortDef Port)
{
  unsigned  char  i  = 0;
  stTxdef* Txd  = NULL;
  unsigned  char*  ReSendCount;      //PC上传重发计数
  unsigned  short*  SendTime=NULL;
  
  switch(Port)
  {
    case  NonPort   : return 0;   //不继续执行
    case  PcPort    : ReSendCount = &AMP.ReSend.PcCount;
                      Txd=AMP.buffer.PcTx;    //PC接口发送缓存
                      SendTime  = &AMP.Time.PcSendTime;
      break;
    case  CabPort   : ReSendCount = &AMP.ReSend.CabCount;
                      Txd=AMP.buffer.CabTx;   //柜接口发送缓存
                      SendTime  = &AMP.Time.CabSendTime;
      break;
    case  LayPort   : ReSendCount = &AMP.ReSend.LayCount;
                      Txd=AMP.buffer.LayTx;   //层接口发送缓存
                      SendTime  = &AMP.Time.LaySendTime;
      break;
    case  CardPort  : ReSendCount = &AMP.ReSend.CardCount;
                      Txd=AMP.buffer.CardTx;  //读卡器接口发送缓存
                      SendTime  = &AMP.Time.CardSendTime;
      break;
    default :return 0;      //不继续执行 
  }
  for(i=0;i<arrysize;i++)
  {
    if(Txd[i].arry>0)
    {
      Txd[i].arry--;
      *SendTime  = SendNopTime;   //释放一个缓存后等待SendNopTime时间后再发下一帧
      *ReSendCount  = 0;
    }
  }
  return  0;
}

/*******************************************************************************
*函数名			:	function
*功能描述		:	AddSendData
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
unsigned short AddSendBuffer(enCCPortDef Port,unsigned char* pBuffer,unsigned short length)
{
  unsigned  char  i  = 0;
  unsigned  char  lastarry  = 0;
  
  stTxdef* Txd  = NULL;
  
  switch(Port)
  {
    case  NonPort   : return 0;   //不继续执行
    case  PcPort    : Txd=AMP.buffer.PcTx;    //PC接口发送缓存
      break;
    case  CabPort   : Txd=AMP.buffer.CabTx;   //柜接口发送缓存
      break;
    case  LayPort   : Txd=AMP.buffer.LayTx;   //层接口发送缓存
      break;
    case  CardPort  : Txd=AMP.buffer.CardTx;  //读卡器接口发送缓存
      break;
    default :return 0;      //不继续执行 
  }
  //-------------------------给当前待发送队列编号(最尾号)
  for(i=0;i<arrysize;i++)
  {
    if(Txd[i].arry>lastarry)
    {
      lastarry  = Txd[i].arry;
      //---------------------检查发送队列中是否有相同的指令，如果有，则退出
      if(0  ==  memcmp(Txd[i].data,pBuffer,length)) //比较相同
      {
        if(length ==  Txd[i].size)    //待发送长度一样
          return  length;
      }
    }
  }
  if(lastarry>=arrysize)  //缓存满
    return 0;     //不继续执行
  lastarry=lastarry+1;      //最后的队列编号
  //-------------------------将数据存储到空队列
  for(i=0;i<arrysize;i++)
  {
    if(0  ==  Txd[i].arry)  //0编号表示此为空缓存
    {
      memcpy(Txd[i].data,pBuffer,length);
      Txd[i].arry = lastarry;             //此缓存在发送队列中的排序
      Txd[i].size = length; 
      return  length;
    }
  }
  return  0;
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
  if(1  ==  AMP.Flag.LockFlg) //锁关状态：未开
  {
    UnLock;
    LayPowerOn;
    BackLightOn;
  }
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
//=================================软件接口End=============================================================


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
void Receive_Server(void)
{
  unsigned short RxNum  = 0;
  unsigned char rxd[ccsize]={0};
  //==========================================================接收查询
  //---------------------PC接口 USART1
  RxNum = USART_ReadBufferIDLE(USART1,rxd);
  if(RxNum)
  {
    Msg_Process(PcPort,rxd,RxNum);                //柜消息处理
  }
  //---------------------副柜接口 UART4
  RxNum = RS485_ReadBufferIDLE(&stRS485Cb,rxd);
  if(RxNum)
  {
    Msg_Process(CabPort,rxd,RxNum);
  }  
  //---------------------层板接口 USART2
  RxNum = RS485_ReadBufferIDLE(&stRS485Ly,rxd);
  if(RxNum)
  {
    Msg_Process(LayPort,rxd,RxNum);              //柜消息处理
  }
  //---------------------读卡器接口 USART3
  RxNum = USART_ReadBufferIDLE(USART3,rxd);
  if(RxNum)
  {
    Msg_Process(CardPort,rxd,RxNum);
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
  switch(Port)
  {
    case  NonPort   : return 0;   //不继续执行
    case  PcPort    : sendedlen = USART_DMASend(USART1,pBuffer,length);
      break;
    case  CabPort   : sendedlen = RS485_DMASend(&stRS485Cb,pBuffer,length);	//RS485-DMA发送程序
      break;
    case  LayPort   : sendedlen = RS485_DMASend(&stRS485Ly,pBuffer,length);	//RS485-DMA发送程序
      break;
    case  CardPort  : sendedlen = USART_DMASend(USART3,pBuffer,length);
      break;
    default :return 0;      //不继续执行
  }

  return  sendedlen;
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
  if(AMP.Time.swicthidtime++>2000) //2秒检查一次拨码
  {
    unsigned  char  tempid  = 0;
    unsigned  char* tempbc  = (unsigned  char*)&AMP.SwData;
    AMP.Time.swicthidtime  = 0;
    tempid  = SWITCHID_ReadLeft(&stSwitch);
    if(*tempbc  != tempid)
    {
      *tempbc  = tempid;
//      AMP01_Configuration();    //重新配置控制板
      SwitchID_Configuration();  
      GenyConfiguration();   //常规接口配置，背光，锁，电源控制    
      COMM_Configuration();
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
void LockServer(void)
{
  static unsigned  short locktime = 0;
  if(GetLockSts)    //锁未开
  {
    locktime  = 0;
    AMP.Flag.LockFlg    = 1;
    AMP.Flag.LayPownOn  = 0;
    BackLightOff;
    LayPowerOff;
  }
  else
  {
    LayPowerOn;
    BackLightOn;
    if(locktime++>50) //延迟50ms释放锁驱动
    {
      ResLock;
    }
    if(locktime++>500)  //延迟100ms打开层供电
    {
      AMP.Flag.LockFlg    = 0;
      AMP.Flag.LayPownOn  = 1;
      locktime  = 0;
      BackLightOn;      //打开背光      
    }
  }    
}
//=================================硬件接口End=============================================================


//=================================配置函数ST==============================================================

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
  if(AMP.Flag.CabBD)  //柜控制板
  {
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
  }
  else if(AMP.Flag.LayBD) //层控制板
  {
    stSwitch.NumOfSW	=	8;
    
    stSwitch.SW1_PORT	=	GPIOA;
    stSwitch.SW1_Pin	=	GPIO_Pin_7;
    
    stSwitch.SW2_PORT	=	GPIOA;
    stSwitch.SW2_Pin	=	GPIO_Pin_6;
    
    stSwitch.SW3_PORT	=	GPIOA;
    stSwitch.SW3_Pin	=	GPIO_Pin_5;
    
    stSwitch.SW4_PORT	=	GPIOA;
    stSwitch.SW4_Pin	=	GPIO_Pin_4;
    
    stSwitch.SW5_PORT	=	GPIOB;
    stSwitch.SW5_Pin	=	GPIO_Pin_11;
    
    stSwitch.SW6_PORT	=	GPIOB;
    stSwitch.SW6_Pin	=	GPIO_Pin_10;
    
    stSwitch.SW7_PORT	=	GPIOB;
    stSwitch.SW7_Pin	=	GPIO_Pin_2;
    
    stSwitch.SW8_PORT	=	GPIOB;
    stSwitch.SW8_Pin	=	GPIO_Pin_1;
  }
	SwitchIdInitialize(&stSwitch);						//

	
  tempsw  = (unsigned  char*)&AMP.SwData;
  *tempsw  = SWITCHID_ReadLeft(&stSwitch);
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
  if(AMP.Time.PcSendTime>0)
  {
    AMP.Time.PcSendTime--;
  }
  //----------------柜发送
  if(AMP.Time.CabSendTime>0)
  {
    AMP.Time.CabSendTime--;
  }
  //----------------层发送
  if(AMP.Time.LaySendTime>0)
  {
    AMP.Time.LaySendTime--;
  }
  //----------------读卡器发送
  if(AMP.Time.CardSendTime>0)
  {
    AMP.Time.CardSendTime--;
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
void AMPdelaymS(unsigned  short time)
{
  SysTick_DeleymS(time);				//SysTick延时nmS
}
#endif
