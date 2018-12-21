#include	"AMP_PHY.H"

#include	"CRC.H"		//

#include	"stdio.h"			//用于printf
#include	"string.h"		//用于printf
#include	"stdarg.h"		//用于获取不确定个数的参数
#include	"stdlib.h"		//malloc动态申请内存空间

#include	"stdbool.h"
unsigned  short crc16;
stampphydef* phy  = NULL;
unsigned	char AmpBaket[maxmsgsize]={0};
/*******************************************************************************
*函数名			:	function
*功能描述		:	function
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
*函数名			:	function
*功能描述		:	function
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
  unsigned short	framelength	=	0;
  
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
  return  NULL;
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
*函数名			:	function
*功能描述		:	function
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
unsigned short SetCrc(unsigned char* pframe,unsigned short* length)
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
  stcmddef*  Cmd = NULL;
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
  stcmddef*  Cmd = NULL;
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
  
  if(AMPACK  ==  Cmd)
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







