#ifdef AMP01

#include "AMP01.H"

#include "string.h"				//串和内存操作函数头文件
//#include "stm32f10x_dma.h"

//#include	"AMP_PHY.H"

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

unsigned  char addr2,addr3; //地址
stSysdef  AMP;

unsigned  short testcrc = 0;
unsigned char tetbff[] = { 0x7E,0x07,0x02,0x02,0x01,0x01,0x01,0x01,0x01,0x00,0xA1,0x7F };
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
  testcrc = CRC16_MODBUS(&tetbff[1],8);
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
	
  IWDG_Configuration(1000);													//独立看门狗配置---参数单位ms
  
  SysTick_Configuration(1000);    //系统嘀嗒时钟配置72MHz,单位为uS
  
  SwitchID_Configuration();
  
  GenyConfiguration();   //常规接口配置，背光，锁，电源控制
    
  COMM_Configuration();  
	
	if(AMP.Flag.CabBD)
	{
		if(AMP.SwData.ID)		//已拨码
			PWM_OUT(TIM2,PWM_OUTChannel1,1,900);						//PWM设定-20161127版本
		else
			PWM_OUT(TIM2,PWM_OUTChannel1,5,900);						//PWM设定-20161127版本
	}
	else
		GPIO_Configuration_OPP50(SYSLEDPort,SYSLEDPin);

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
	IWDG_Feed();								//独立看门狗喂狗
	
  SwitchID_Server();
  RequestServer();
  StatusServer();
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
    if(AMP.Flag.CabBD)  //柜控制板
    {
			if(0  ==  AMP.SwData.ID)		//未拨码
			{
				if(AMP.Time.SYSLEDTime>=500)
				{
					GPIO_Toggle	(BackLightPort,BackLightPin);		//将GPIO相应管脚输出翻转----V20170605
					AMP.Time.SYSLEDTime  = 0;
				}
				return;
			}
    }
    else if(AMP.Flag.LayBD)
    {
				if(AMP.Time.SYSLEDTime%500==0)
				{
					GPIO_Toggle	(SYSLEDPort,SYSLEDPin);		//将GPIO相应管脚输出翻转----V20170605
				}				
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
  if(AMP.Flag.CabBD)//柜控制板
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
  else if(AMP.Flag.LayBD) //层控制板
  {
    //----------------层发送
    if(0  ==  AMP.Time.LaySendTime)
    {
      Check_SendBuff(LayPort);
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
  
  //------------------------------检查发送缓存:先发送排序为1的缓存
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
      
      if(*ReSendCount>=maxresendcount) //超出重发次数：放弃发送
      {
        Releas_OneBuffer(Port);
        *ReSendCount  = 0;      //重发清零
      }
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
 if(AMP.Flag.CabBD) //柜控制板  
  Msg_ProcessCB(Port,pBuffer,length);       //柜消息处理
 else
  Msg_ProcessLY(Port,pBuffer,length);      //层消息处理
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
* 函数名			:	Cabinetmsg_Process
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
  
  //-------------------------协议检查
  framlength	=	getframe(pBuffer,&length);    //判断帧消息内容是否符合协议
  if(0== framlength)
  {
    memset(paddrbac,0x00,gDatasize);             //清除数据
    return;
  }
  result  = ackcheck(pBuffer);                //检查是否为应答消息,应答消息返回1  
  if(1==result)
  {
    if(AMP.Flag.WaitAck)      //如果为等待应答状态，则释放一个缓存
    {
      AMP.Flag.WaitAck=0;
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
  //1）-----------------上传数据:主柜接收到的数据上传到PC，并向下应答，副柜不处理
  if(1==ampframe->msg.cmd.dir)
  {
    if(1==AMP.SwData.MainFlg)
    {
      ackFrame(Port,0);   //向下应答
      PCnet_Send((unsigned char*)ampframe,framlength);     //往PC发送消息
      return;
    }    
    else
      return;
  }
  //2）-----------------下发数据：地址为本地址或者广播地址(0xFF)需要进行处理，如果地址为本地址，向上应答(广播地址不应答)
  address=ampframe->msg.addr.address1;
  if(0==address)  //柜地址为空
  {
    return;
  }
  if((AMP.SwData.ID!=address))  //不属于主柜消息
  {
    Cabinet_Send((unsigned char*)ampframe,framlength);//往副柜发送
    if(0xFF==address) //广播地址
    {
      AMP.Flag.WaitAck=0;   //不需要副柜应答      
    }
    else
    {
      AMP.Flag.WaitAck=1;   //需要副柜应答
      return;
    }
  }
  //===================================柜接口接收到的下发数据处理
  if(0xFF!=address)   //非广播地址，向上应答
  {
    ackFrame(Port,1); //向上应答
  }
  //1)-----------------检查层地址，判断是否需要将数据发往层，发往层时，需要开锁，开背光灯
  address=ampframe->msg.addr.address2;
  if(0!=address)
  {
    AMP.Req.unlockqust=1;//请求开锁
    AMP.Req.reslock=0;
    AMP.Req.BLon=1;
    AMP.Req.BLoff=0;
    AMP.Req.PLon=1; 
    AMP.Req.PLoff=0; 
    AMP.Flag.WaitAck=1;   //需要应答
    Laynet_Send((unsigned char*)ampframe,framlength);     //往层板发送消息
  }
  //2)-----------------命令处理：灯控制/锁控制/供电
  if(LED ==  Cmd)   //背光控制命令
  {
    AMP.Req.BLon=0;
    AMP.Req.BLoff=0;
    if(ampframe->msg.data[0])
      AMP.Req.BLon=1;
    else
      AMP.Req.BLoff=1;
  }
  else if(PWD ==  Cmd)   //层板供电控制命令
  {
    AMP.Req.PLon  =0;
    AMP.Req.PLoff =0;
    if(ampframe->msg.data[0])
      AMP.Req.PLon=1;
    else
      AMP.Req.PLoff=1;
  }
  else if(CTL ==  Cmd)   //锁控制命令
  {
    AMP.Req.reslock  =0;
    AMP.Req.unlockqust =0;
    if(ampframe->msg.data[0])
      AMP.Req.unlockqust=1;
    else
      AMP.Req.reslock=1;
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
  
  //-------------------------协议检查
  framlength	=	getframe(pBuffer,&length);    //判断帧消息内容是否符合协议
  if(0== framlength)
  {
    memset(paddrbac,0x00,gDatasize);             //清除数据
    return;
  }
  result  = ackcheck(pBuffer);                //检查是否为应答消息,应答消息返回1  
  if(1==result)
  {
    if(AMP.Flag.WaitAck)      //如果为等待应答状态，则释放一个缓存
    {
      AMP.Flag.WaitAck=0;
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
  //1）-----------------上传数据:主柜接收到的数据上传到PC，并向下应答，副柜不处理
  if(1==ampframe->msg.cmd.dir)
  {
    if(1==AMP.SwData.MainFlg)
    {
      ackFrame(Port,0);   //向下应答
      PCnet_Send((unsigned char*)ampframe,framlength);     //往PC发送消息
      return;
    }    
    else
      return;
  }
  //2）-----------------下发数据：地址为本地址或者广播地址(0xFF)需要进行处理，如果地址为本地址，向上应答(广播地址不应答)
  address=ampframe->msg.addr.address1;
  if((0xFF!=address)&&(AMP.SwData.ID!=address))
  {
    return;   //地址不对，不处理
  }
  //===================================柜接口接收到的下发数据处理
  if(0xFF!=address)   //非广播地址，向上应答
  {
    ackFrame(Port,1); //向上应答
  }
  //1)-----------------检查层地址，判断是否需要将数据发往层，发往层时，需要开锁，开背光灯
  address=ampframe->msg.addr.address2;
  if(0!=address)
  {    
    if((LED==Cmd)&&(ampframe->msg.data[0]|ampframe->msg.data[1]|ampframe->msg.data[2]))
    {
      AMP.Req.unlockqust=1;//请求开锁
      AMP.Req.reslock=0;
      AMP.Req.BLon=1;
      AMP.Req.BLoff=0;
      AMP.Req.PLon=1; 
      AMP.Req.PLoff=0; 
    }
    Laynet_Send((unsigned char*)ampframe,framlength);     //往层板发送消息
  }
  //2)-----------------命令处理：灯控制/锁控制/供电
  if(LED ==  Cmd)   //背光控制命令
  {
    AMP.Req.BLon=0;
    AMP.Req.BLoff=0;
    if(ampframe->msg.data[0])
      AMP.Req.BLon=1;
    else
      AMP.Req.BLoff=1;
  }
  else if(PWD ==  Cmd)   //层板供电控制命令
  {
    AMP.Req.PLon  =0;
    AMP.Req.PLoff =0;
    if(ampframe->msg.data[0])
      AMP.Req.PLon=1;
    else
      AMP.Req.PLoff=1;
  }
  else if(CTL ==  Cmd)   //锁控制命令
  {
    AMP.Req.reslock  =0;
    AMP.Req.unlockqust =0;
    if(ampframe->msg.data[0])
      AMP.Req.unlockqust=1;
    else
      AMP.Req.reslock=1;
  }
  //CMD_Process(pBuffer,framlength);
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
  unsigned  char result       = 0; 
  unsigned  char address      = 0;  
  unsigned  short framlength  = 0;  
  unsigned  char* paddrbac    = pBuffer;         //备份数据缓存起始地址
  
  stampphydef* ampframe=NULL;
  stcmddef    Cmd;
  //-------------------------读卡器端口:读卡器接口接收的数据只通过柜接口或者PC接口上传
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
    SetFrame(databuffer,&framlength); //补充消息的CRC和结束符，返回帧长度
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
    memset(paddrbac,0x00,gDatasize);             //清除数据
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
    else if(LayPort == Port)  //层控制接口无下发数据，只有上传数据
    {
      //CMD_Process((unsigned char*)ampframe,framlength);
      return;
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
      if(AMP.SwData.MainFlg)  //主柜接收到上柜端口数据需要应答
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
    CMD_Process(pBuffer,framlength);
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
  SetFrame((unsigned char*)ampframe,&framlength);   //补充消息的CRC和结束符，返回帧长度
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
  unsigned  char address      = 0;  
  unsigned  short framlength  = 0; 
  unsigned  char  Cmd         = 0;  
  unsigned  char* paddrbac    = pBuffer;         //备份数据缓存起始地址
  
  stampphydef* ampframe=NULL;
  
  //-------------------------协议检查
  framlength	=	getframe(pBuffer,&length);    //判断帧消息内容是否符合协议
  if(0== framlength)
  {
    memset(paddrbac,0x00,gDatasize);             //清除数据
    return;
  }
  result  = ackcheck(pBuffer);                //检查是否为应答消息,应答消息返回1  
  if(1==result)
  {
    if(AMP.Flag.WaitAck)      //如果为等待应答状态，则释放一个缓存
    {
      AMP.Flag.WaitAck=0;
      Releas_OneBuffer(Port);        //释放一个发送缓存
    }
    return;
  }  
  //-------------------------根据地址转发数据：广播数据发送到副柜和本柜层板
  ampframe  = (stampphydef*)pBuffer;
  Cmd = ampframe->msg.cmd.cmd;
  
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
    framlength  = PaketUpMsg(databuffer,ICR,&framlength);
    //-------------------------设置地址:柜控制板地址段为address1
    ampframe  = (stampphydef*)databuffer;
    ampframe->msg.addr.address1 = AMP.SwData.ID;
    //-------------------------设置CRC和结束符
    SetFrame(databuffer,&framlength);   //补充消息的CRC和结束符，返回帧长度
    //-------------------------检查本柜是否为主柜
    if(1==AMP.SwData.MainFlg)   //主柜--通过PC接口上传
    {
      PCnet_Send(databuffer,framlength);
    }
    else  //副柜--通过副柜接口上传
    {
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
//      UnLock;   //开锁
      AMP.Req.unlockqust = 1;
      AMP.Req.reslock    = 0;
    }
    else
    {
//      ResLock;  //释放锁
      AMP.Req.unlockqust = 0;
      AMP.Req.reslock    = 1;      
    }
    return;
  }
  //---------------------------层板供电控制
  if(PWD ==  (*cmd&Down)) //最高位为0表示上往下发
  {
    if(0==AMP.Flag.CabBD)  //柜控制板
      return;
    if(0  ==  ampframe->msg.data[0])    //0为开锁命令
    {       
      LayPowerOff;//关闭层板供电
    }
    else
    {
      LayPowerOn;//打开层板供电
    }
    return;
  }
  //---------------------------开背光灯命令
  if(LED ==  (*cmd&Down)) //最高位为0表示上往下发
  {
    if(AMP.Flag.CabBD)  //柜控制板
    {
      if(0==ampframe->msg.addr.address2)
       {
        if(0  !=  ampframe->msg.data[0])    //1为开LED
        {
          BackLightOn;   //开LED
        }
        else
        {
          BackLightOff;  //关LED
        }
      }
      return;
    }
    else if(AMP.Flag.LayBD) //层控制板
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
  if(AMP.Flag.CabBD)  //柜控制板
  {
    return(AddSendBuffer(LayPort,pBuffer,length));
  }
  else if(AMP.Flag.LayBD) //层控制板
  {
    return(AddSendBuffer(LayPort,pBuffer,length));
  }
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
  unsigned char rxd[256]={0};
  //==========================================================接收查询
  if(AMP.Flag.CabBD)  //柜控制板
  {
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
  else if(AMP.Flag.LayBD) //层控制板
  {
    //---------------------层板接口 USART2
    RxNum = RS485_ReadBufferIDLE(&stRS485Ly,rxd);
    if(RxNum)
    {
      Msg_Process(LayPort,rxd,RxNum);              //柜消息处理
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
			
			if(AMP.Flag.CabBD)	//柜
			{
				if(AMP.SwData.ID)		//已拨码
					PWM_OUT(TIM2,PWM_OUTChannel1,1,900);						//PWM设定-20161127版本
				else
					PWM_OUT(TIM2,PWM_OUTChannel1,5,900);						//PWM设定-20161127版本
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
void LockServer(void)
{
  if(AMP.Flag.CabBD)  //柜控制板
  {
    static unsigned  short locktime = 0;

    if(0  ==  AMP.SwData.ID)    //未拨码--自动开锁
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
    if(1==AMP.Req.unlockrun)   //正在执行开锁动作
    {
      if(AMP.Time.LockTime>unlocktime-10)//10ms后开始检查锁状态
      {
        return;
      }
      if(GetLockSts)    //锁未开
      {
        AMP.Sta.lockstd  = 1;
        if(AMP.Time.LockTime==0)//超过开锁时间
        {
          AMP.Req.unlockrun  = 0;
          AMP.Sta.unlockerr  = 1;
          AMP.Time.LockTime   = 0;
          ResLock;
        }
      }
      else
      {
        AMP.Sta.lockstd    = 0;
        AMP.Req.unlockrun  = 0;
        AMP.Sta.unlockerr  = 0;
        AMP.Time.LockTime   = 0;
        ResLock;        
      }      
    }
    if(1==AMP.Req.unlockqust)  //开锁请求
    {
      AMP.Req.unlockrun   = 1;
      AMP.Req.unlockqust  = 0;
      AMP.Req.reslock     = 0;
      AMP.Sta.unlockerr  = 0;
      
      AMP.Req.BLon=1;   //开锁需要开背光
      AMP.Req.PLon=1;   //开锁层板需要供电
      
      AMP.Time.LockTime   = unlocktime;
      UnLock;
    }
    
    //-----------------------------关锁动作
    if(GetLockSts)    //锁未开
    {
      //检查是否为关锁动作
      if(0==AMP.Sta.lockstd)//原状态为锁已打开
      {
        AMP.Req.BLoff = 1;  //请求关背光
        AMP.Req.PLoff = 1;  //请求关闭层板电源
        AMP.Flag.LayPownOn=0; 
      }
      AMP.Sta.lockstd  = 1;
    }
    else
    {
      if(1==AMP.Sta.lockstd) //原状态锁为关闭---手动开锁
      {
        AMP.Req.BLon = 1;  //请求打开背光
        AMP.Req.PLon = 1;  //请求打开层板电源
        AMP.Flag.LayPownOn=1;
      }
      AMP.Sta.lockstd  = 0;
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
void RequestServer(void)
{
  if(AMP.Flag.CabBD)      //柜控制板
  {
    if(AMP.Req.BLon)      //背光开关控制
    {
      BackLightOn;
      AMP.Req.BLon=0;
    }
    else if(AMP.Req.BLoff)
    {
      BackLightOff;
      AMP.Req.BLoff=0;
    }
    if(AMP.Req.PLon)    //层板供电控制
    {      
      LayPowerOn;
      AMP.Req.PLon=0;
      AMP.Flag.LayPownOn=1;
    }
    else if(AMP.Req.PLoff)
    {
      LayPowerOff;
      AMP.Req.PLoff=0;
      AMP.Flag.LayPownOn=0;
    }
    //if(AMP.Req.unlockqust)
    //{      
      //LockServer();
    //}
    LockServer();
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
void StatusServer(void)
{
  static unsigned long statustemp=0;
  unsigned short* ptemp=0;
  ptemp=(unsigned short*)&AMP.Sta;
  if(statustemp!=*ptemp)//状态有变化
  {
    unsigned short framlength=3;
    unsigned char databuffer[32]={0};
    
    stampphydef* ampframe=NULL;
    stcmddef*   Cmd=NULL;
    
    statustemp=*ptemp;
    

    memcpy(databuffer,ptemp,2);
    
    framlength  = PaketUpMsg(databuffer,STA,&framlength);    
    ampframe  = (stampphydef*)databuffer;
    
    ampframe->msg.addr.address1 = AMP.SwData.ID;
    ampframe->msg.addr.address2 = 0;
    ampframe->msg.addr.address3 = 0;
    //-------------------------设置CRC和结束符
    SetFrame(databuffer,&framlength);//补充消息的CRC和结束符，返回帧长度
    Cabinet_Send(databuffer,framlength);    //往副柜发送消息
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
  if(AMP.Flag.CabBD)  //柜控制板
  {
    //-----------------------------PC接口USART1
    USART_DMA_ConfigurationNR	(USART1,19200,gDatasize);	//USART_DMA配置--查询方式，不开中断
    
    //-----------------------------读卡器接口USART3
    if(0==AMP.SwData.ICreadFlg) //sw2未拨码，默认19200
      USART_DMA_ConfigurationNR	(USART3,19200,gDatasize);	//USART_DMA配置--查询方式，不开中断
    else
      USART_DMA_ConfigurationNR	(USART3,9600,gDatasize);	//USART_DMA配置--查询方式，不开中断

    //-----------------------------层板接口USART2
    stRS485Ly.USARTx  = USART2;
    stRS485Ly.RS485_CTL_PORT  = GPIOA;
    stRS485Ly.RS485_CTL_Pin   = GPIO_Pin_1;
    RS485_DMA_ConfigurationNR			(&stRS485Ly,19200,gDatasize);	//USART_DMA配置--查询方式，不开中断,配置完默认为接收状态
    //-----------------------------副柜接口UART4
    stRS485Cb.USARTx  = UART4;
    stRS485Cb.RS485_CTL_PORT  = GPIOC;
    stRS485Cb.RS485_CTL_Pin   = GPIO_Pin_12;
    RS485_DMA_ConfigurationNR			(&stRS485Cb,19200,gDatasize);	//USART_DMA配置--查询方式，不开中断,配置完默认为接收状态
  }
  else if(AMP.Flag.LayBD) //层控制板
  {
    //-----------------------------层板接口USART1 PA11-RE,PA12-TE
    stRS485Ly.USARTx  = USART1;
    stRS485Ly.RS485_CTL_PORT  = GPIOA;
    stRS485Ly.RS485_CTL_Pin   = GPIO_Pin_12;
    RS485_DMA_ConfigurationNR			(&stRS485Ly,19200,gDatasize);	//USART_DMA配置--查询方式，不开中断,配置完默认为接收状态
    GPIO_Configuration_OPP50	(GPIOA,GPIO_Pin_11);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605
    GPIO_ResetBits(GPIOA,GPIO_Pin_11);
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
  
  if(AMP.Flag.LayBD)//层控制板
  {
    addr2=(SWITCHID_ReadLeft(&stSwitch)>>4)&0X0F;  //层地址
    addr3=SWITCHID_ReadLeft(&stSwitch)&0x0F;  //位地址
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
  if(AMP.Flag.CabBD)  //层控制板
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
  else if(AMP.Flag.LayBD) //柜控制板
  {
    if(addr2&&addr3)
    {
      PWM_OUT(TIM2,PWM_OUTChannel2,1000,1000);						//PWM设定-20161127版本---红色
      PWM_OUT(TIM2,PWM_OUTChannel4,1000,1000);						//PWM设定-20161127版本---黄色
      PWM_OUT(TIM2,PWM_OUTChannel3,1000,1000);						//PWM设定-20161127版本---蓝色
    }
    else
    {
      PWM_OUT(TIM2,PWM_OUTChannel2,2,900);						//PWM设定-20161127版本---红色
      PWM_OUT(TIM2,PWM_OUTChannel4,2,600);						//PWM设定-20161127版本---黄色
      PWM_OUT(TIM2,PWM_OUTChannel3,2,200);						//PWM设定-20161127版本---蓝色
    }
  }
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
	AMP.Time.SYSLEDTime++;
  if(AMP.Flag.CabBD)  //柜控制板
  {
//    AMP.Time.LockTime++;
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
    //----------------锁
    if(AMP.Time.LockTime>0)
    {
      AMP.Time.LockTime--;
    }
  }
  else if(AMP.Flag.LayBD) //层控制板
  {
    //----------------层发送
    if(AMP.Time.LaySendTime>0)
    {
      AMP.Time.LaySendTime--;
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
void AMPdelaymS(unsigned  short time)
{
  SysTick_DeleymS(time);				//SysTick延时nmS
}
#endif
