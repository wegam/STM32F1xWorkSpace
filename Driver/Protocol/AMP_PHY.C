#include	"AMP_PHY.H"

#include "AMP01.H"

#include	"CRC.H"		//

#include	"stdio.h"			//用于printf
#include	"string.h"		//用于printf
#include	"stdarg.h"		//用于获取不确定个数的参数
#include	"stdlib.h"		//malloc动态申请内存空间

#include	"stdbool.h"
unsigned  short crc16;
stampphydef* phy  = NULL;
unsigned	char AmpBaket[maxmsgsize]={0};
stAMPProdef   AMPPro;

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
*函数名			:	API_AmpCheckFrame
*功能描述		:	检查协议
*输入				: pbuffer-数据地址
              length-数据长度地址
*返回值			:	消息帧类型
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
unsigned  char API_AmpCheckFrame(unsigned char* pbuffer,unsigned short* length)
{
  unsigned  char  Cmd         = 0;
  unsigned  char* headaddr    = NULL;
  unsigned  char* endaddr     = NULL;
  unsigned short	HeadCodeValidLength	=	*length;    //头标识有效查找长度
  unsigned short	EndCodeValidLength	=	*length;    //尾标识有效查找长度
  unsigned short	FrameValidLength	  =	*length;    //当前帧最大有效长度
  
 
  if(NULL  ==  pbuffer)
  {
    goto ExitAmpCheckFrame;   //退出此函数--空地址
  }
  if(FrameValidLength<7)  //小于最小帧长度
  {
    goto ExitAmpCheckFrame;   //退出此函数--帧长度不够
  }  
  startcheckdata:
  //---------------------查找头标识地址
  headaddr	=	(unsigned char*)memchr(pbuffer,headcode,HeadCodeValidLength);   //找头标识
  if(NULL==headaddr)
  {
    goto ExitAmpCheckFrame;   //退出此函数--未找到头标识符
  }
  //---------------------查找尾标识地址
  EndCodeValidLength  = HeadCodeValidLength-((unsigned long)headaddr-(unsigned long)pbuffer);
  if(EndCodeValidLength<7)
  {
    goto ExitAmpCheckFrame;   //退出此函数--帧长度不够
  }
  endaddr		=	(unsigned char*)memchr(headaddr,endcode,EndCodeValidLength);   //找尾标识---从头标识后开始查找
  if((NULL==endaddr)
  {
    //return  0;
    //goto ExitAmpCheckFrame;   //退出此函数--未找到尾标识符
  }
  //======================================
//  else
//  {
    //======================================根据协议做CRC校验
    //--------------------------------------应答帧校验
//    if(crccheck(headaddr,&ValidLength))
//    {
//      *length = ValidLength;
//    }
//    else
//    {
//      pbuffer = &headaddr[1];
//      ValidLength = ValidLength-1;
//      goto startcheckdata;
//    }    
//  }
  ExitAmpCheckFrame:  //退出此函数
//  *length  = 0;       //长度清零
//  Cmd =  0;
  return  0;
}
/*******************************************************************************
*函数名			:	getframe
*功能描述		:	获取帧地址，返回帧长度
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
unsigned short getframe(unsigned char* pbuffer,unsigned short* length)
{  
  unsigned  char* headaddr  = NULL;
  unsigned  short farmelength = 0;
  headaddr  = getheadaddr(pbuffer,length);
  if(NULL==headaddr)
  {
    return  0;
  }
  pbuffer = headaddr;
  farmelength = *length;
  return  farmelength;
}
/*******************************************************************************
*函数名			:	getheadaddr
*功能描述		:	获取头标识地址
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
unsigned char* getheadaddr(unsigned char* pbuffer,unsigned short* length)
{
  unsigned  char* headaddr  = NULL;
  unsigned  char* endaddr   = NULL;
  
  unsigned short	ValidLength	=	*length;
//  unsigned short	framelength	=	0;
  
  if(NULL  ==  pbuffer)
  {
    return NULL;
  }
  startcheckdata:
  headaddr	=	(unsigned char*)memchr(pbuffer,headcode,ValidLength);
	endaddr		=	(unsigned char*)memchr(headaddr,endcode,ValidLength);
  ValidLength = ValidLength-((unsigned long)headaddr-(unsigned long)pbuffer);
  if(ValidLength<7)   //小于最小帧长度
  {
    *length = 0;
    return  NULL;
  }
  if((NULL==headaddr)||(NULL==endaddr))
  {
    *length = 0;
    return  NULL;
  }
  else
  {
    
    if(crccheck(headaddr,&ValidLength))
    {
      *length = ValidLength;
      return headaddr;
    }
    else
    {
      pbuffer = &headaddr[1];
      ValidLength = ValidLength-1;
      goto startcheckdata;
    }    
  }
//  return  NULL;
}

/*******************************************************************************
*函数名			:	crccheck
*功能描述		:	crc校验
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
unsigned char crccheck(unsigned char* pframe,unsigned short* length)
{  
  unsigned  short msglen  = 0;  
  unsigned  short	ValidLength	=	*length;  
  if(NULL  ==  pframe)
  {
    return 0;
  }
  phy  = (stampphydef*)pframe;
  //crc16 = pbuffer->
  msglen  = phy->msg.length;
  if(2==msglen) //应答
  {
    phy->crc16.crcl = pframe[4];
    phy->crc16.crch = pframe[5];
  }
  else
  {
    if(msglen>ValidLength)     //帧长度不够
      return  0;
    else if(msglen>2)     //排除应答帧长度判断
      if(msglen+5>ValidLength) //消息帧长度不够 
        return 0;
    phy->crc16.crcl = pframe[msglen+2];
    phy->crc16.crch = pframe[msglen+3];
  }
  crc16 = CRC16_MODBUS(&pframe[1],msglen+1);
  if(((crc16&0xFF)==phy->crc16.crcl)&&(((crc16>>8)&0xFF)==phy->crc16.crch))
  {
    *length = msglen+5;
    return 1;
  }
  return 0;
}
/*******************************************************************************
*函数名			:	SetFrame
*功能描述		:	补充消息的CRC和结束符，返回帧长度
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
unsigned short SetFrame(unsigned char* pframe,unsigned short* length)
{  
  unsigned short msglen = 0;    //消息段长度
  unsigned short datalen = 0;   //data长度
  unsigned short crclen = 0;    //要参与CRC计数的字节数
  unsigned short crc16 = 0;     //计算的CRC16
  
  stampphydef* ampframe;
  
  ampframe  = (stampphydef*)pframe;
  msglen  = ampframe->msg.length;
  datalen = msglen-4;   //一字节命令，三字节地址
  crclen  = msglen+1;   //msg.length需要参与CRC计算
  crc16 = CRC16_MODBUS(&ampframe->msg.length,crclen);
  memcpy(&ampframe->msg.data[datalen],&crc16,2);       //复制CRC数据
  ampframe->msg.data[datalen+2]  = endcode;      //增加结束符
  return *length;
}

/*******************************************************************************
* 函数名			:	PaketUpMsg
* 功能描述		:	打包上传消息
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
unsigned	short PaketUpMsg(unsigned	char* pbuffer,eucmddef cmd,unsigned	short* length)
{
  unsigned  short framlength  = 0;  //msg段数据长度：1字节命令+3字节地址
  unsigned  char* temp  = NULL;
//  stcmddef*  Cmd = NULL;
  stampphydef ampframe;
  
  framlength  = *length+4;  //msg段数据长度：1字节命令+3字节地址
  temp  = (unsigned  char*)&ampframe.msg.cmd;   //设置命令
  *temp = (unsigned  char)cmd;
  ampframe.msg.cmd.dir  = 1;      //设置此消息为上传类型消息
  
  ampframe.head = headcode;
  ampframe.msg.length = framlength;           //设置msg段长度
  memcpy(ampframe.msg.data,pbuffer,*length);  //复制数据
  
  framlength  = framlength+5;   //完整帧长度，head,length,crc16,end为5个字节
  
  memcpy(pbuffer,&ampframe,framlength);   //更新pbuffer内容
  *length = framlength;   //打包完成后的消息长度
  return framlength;
}
/*******************************************************************************
* 函数名			:	PaketUpMsg
* 功能描述		:	打包上传消息
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
unsigned	short PaketDownMsg(unsigned	char* pbuffer,eucmddef cmd,unsigned	short* length)
{
  unsigned  short framlength  = 0;  //msg段数据长度：1字节命令+3字节地址
  unsigned  char* temp  = NULL;
//  stcmddef*  Cmd = NULL;
  stampphydef ampframe;
  
  framlength  = *length+4;  //msg段数据长度：1字节命令+3字节地址
  temp  = (unsigned  char*)&ampframe.msg.cmd;   //设置命令
  *temp = (unsigned  char)cmd;
  ampframe.msg.cmd.dir  = 0;      //设置此消息为下发类型消息
  
  ampframe.head = headcode;
  ampframe.msg.length = framlength;           //设置msg段长度
  memcpy(ampframe.msg.data,pbuffer,*length);  //复制数据
  
  framlength  = framlength+5;   //完整帧长度，head,length,crc16,end为5个字节
  
  memcpy(pbuffer,&ampframe,framlength);   //更新pbuffer内容
  *length = framlength;   //打包完成后的消息长度
  return framlength;
}
/*******************************************************************************
*函数名			:	function
*功能描述		:	检查是否为应答消息,应答消息返回1
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
unsigned char ackcheck(unsigned char* pframe)
{ 
  unsigned  char Cmd  = 0;
  stampphydef *ampframe;
  
  if(NULL ==  pframe)
    return  0;
  
  ampframe = (stampphydef*)pframe;
  Cmd = (unsigned  char)ampframe->msg.cmd.cmd;
  Cmd&=0x3F;            //去掉高2位
  
  if(AmpCmdAck  ==  Cmd)
    return  1;        //应答消息
  return 0;
}
/*******************************************************************************
*函数名			:	function
*功能描述		:	检查address1地址
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
unsigned char addr1check(unsigned char* pframe,unsigned char addr1)
{ 
  unsigned addrck=0;
  if(NULL ==  pframe)
    return  0;
  phy = (stampphydef*)pframe;
  addrck  = phy->msg.addr.address1;
  if((addrck==addr1)||(addrck==0xFF))
    return  1;
  return 0;
}
/*******************************************************************************
*函数名			:	function
*功能描述		:	检查address2地址
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
unsigned char addr2check(unsigned char* pframe,unsigned char addr2)
{ 
  unsigned addrck=0;
  if(NULL ==  pframe)
    return  0;
  phy = (stampphydef*)pframe;
  addrck  = phy->msg.addr.address2;
  if((addrck==addr2)||(addrck==0xFF))
    return  1;
  return 0;
}
/*******************************************************************************
*函数名			:	function
*功能描述		:	检查address3地址
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
unsigned char addr3check(unsigned char* pframe,unsigned char addr3)
{ 
  unsigned addrck=0;
  if(NULL ==  pframe)
    return  0;
  phy = (stampphydef*)pframe;
  addrck  = phy->msg.addr.address3;
  if((addrck==addr3)||(addrck==0xFF))
    return  1;
  return 0;
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
unsigned short sendbuffer(unsigned char* pbuffer,unsigned short length)
{
  return  0;
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
    case  PcPort    : ReSendCount = &AMPPro.ReSend.PcCount;
                      Txd=AMPPro.buffer.PcTx;    //PC接口发送缓存
                      SendTime  = &AMPPro.Time.PcSendTime;
      break;
    case  CabPort   : ReSendCount = &AMPPro.ReSend.CabCount;
                      Txd=AMPPro.buffer.CabTx;   //柜接口发送缓存
                      SendTime  = &AMPPro.Time.CabSendTime;
      break;
    case  LayPort   : ReSendCount = &AMPPro.ReSend.LayCount;
                      Txd=AMPPro.buffer.LayTx;   //层接口发送缓存
                      SendTime  = &AMPPro.Time.LaySendTime;
      break;
    case  CardPort  : ReSendCount = &AMPPro.ReSend.CardCount;
                      Txd=AMPPro.buffer.CardTx;  //读卡器接口发送缓存
                      SendTime  = &AMPPro.Time.CardSendTime;
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
    case  PcPort    : AMPPro.AckQ.PcAck     = 1;
                      AMPPro.AckQ.PcDir     = dir;
                      AMPPro.Time.PcSendTime=SendNopTime;   //等待发送时间
      break;
    case  CabPort   : AMPPro.AckQ.CabAck    = 1;
                      AMPPro.AckQ.CabDir    = dir;
                      AMPPro.Time.CabSendTime=SendNopTime;   //等待发送时间
      break;
    case  LayPort   : AMPPro.AckQ.LayAck    = 1;
                      AMPPro.AckQ.LayDir    = dir;
                      AMPPro.Time.LaySendTime=SendNopTime;   //等待发送时间
      break;
    case  CardPort  : AMPPro.AckQ.CardAck   = 1;
                      AMPPro.AckQ.CardDir   = dir;
                      AMPPro.Time.CardSendTime=SendNopTime;   //等待发送时间
      break;
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
void Send_Server(void)
{
    //----------------PC发送
    if(0  ==  AMPPro.Time.PcSendTime)
    {
      Check_SendBuff(PcPort);
    }
    //----------------柜发送
    if(0  ==  AMPPro.Time.CabSendTime)
    {
      Check_SendBuff(CabPort);
    }
    //----------------层发送
    if(0  ==  AMPPro.Time.LaySendTime)
    {
      Check_SendBuff(LayPort);
    }
    //----------------读卡器发送
    if(0  ==  AMPPro.Time.CardSendTime)
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
  

  //------------------------------检查重发
  switch(Port)
  {
    case  NonPort   : return 0;   //不继续执行
    case  PcPort    : ReSendCount = &AMPPro.ReSend.PcCount;
                      Txd=AMPPro.buffer.PcTx;    //PC接口发送缓存
                      SendTime  = &AMPPro.Time.PcSendTime;
                      ackflag = AMPPro.AckQ.PcAck;
                      ackdir  = AMPPro.AckQ.PcDir;
      break;
    case  CabPort   : ReSendCount = &AMPPro.ReSend.CabCount;
                      Txd=AMPPro.buffer.CabTx;   //柜接口发送缓存
                      SendTime  = &AMPPro.Time.CabSendTime;
                      ackflag = AMPPro.AckQ.CabAck;
                      ackdir  = AMPPro.AckQ.CabDir;
      break;
    case  LayPort   : ReSendCount = &AMPPro.ReSend.LayCount;
                      Txd=AMPPro.buffer.LayTx;   //层接口发送缓存
                      SendTime  = &AMPPro.Time.LaySendTime;
                      ackflag = AMPPro.AckQ.LayAck;
                      ackdir  = AMPPro.AckQ.LayDir;
      break;
    case  CardPort  : ReSendCount = &AMPPro.ReSend.CardCount;
                      Txd=AMPPro.buffer.CardTx;  //读卡器接口发送缓存
                      SendTime  = &AMPPro.Time.CardSendTime;
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
        case  PcPort    : AMPPro.AckQ.PcAck = 0;
          break;
        case  CabPort   : AMPPro.AckQ.CabAck = 0;
          break;
        case  LayPort   : AMPPro.AckQ.LayAck = 0;
          break;
        case  CardPort  : AMPPro.AckQ.CardAck  = 0;
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
      break;
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
*函数名			:	function
*功能描述		:	function
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
void Send_ConnectErr(enCCPortDef Port,unsigned char* pBuffer,unsigned short length)
{

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
    case  PcPort    : Txd=AMPPro.buffer.PcTx;    //PC接口发送缓存
      break;
    case  CabPort   : Txd=AMPPro.buffer.CabTx;   //柜接口发送缓存
      break;
    case  LayPort   : Txd=AMPPro.buffer.LayTx;   //层接口发送缓存
      break;
    case  CardPort  : Txd=AMPPro.buffer.CardTx;  //读卡器接口发送缓存
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



