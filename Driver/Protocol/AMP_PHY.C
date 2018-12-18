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
unsigned char* getheadaddr(unsigned char* pbuffer,unsigned short length)
{
  unsigned  char* headaddr  = NULL;
  unsigned  char* endaddr   = NULL;
  
  unsigned short	ValidLength	=	length;
  
  if(NULL  ==  pbuffer)
  {
    return NULL;
  }
  startcheckdata:
  headaddr	=	(unsigned char*)memchr(pbuffer,headcode,ValidLength);
	endaddr		=	(unsigned char*)memchr(headaddr,endcode,ValidLength);
  ValidLength = ValidLength-((unsigned long)headaddr-(unsigned long)pbuffer);
  if((NULL==headaddr)||(NULL==endaddr))
  {
    return  NULL;
  }
  else
  {
    if(crccheck(headaddr,ValidLength))
    {
      return headaddr;
    }
    else
    {
      pbuffer = &headaddr[1];
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
unsigned char crccheck(unsigned char* pbuffer,unsigned short length)
{
  
  
  stampcrc16def*  crc16cmp0;
  
  
  unsigned  short msglen  = 0;  
  unsigned  short	ValidLength	=	length;  
  if(NULL  ==  pbuffer)
  {
    return 0;
  }
  phy  = (stampphydef*)pbuffer;
  //crc16 = pbuffer->
  msglen  = phy->msg[0];
  if((msglen>length)||(msglen+5>length))
    return 0;
  crc16cmp0   = (stampcrc16def*)&phy->msg[msglen];
  phy->crc16.crcl = phy->msg[msglen+1];
  phy->crc16.crch = phy->msg[msglen+2];
  crc16 = CRC16_MODBUS(phy->msg,msglen+1);
  if(((crc16&0xFF)==phy->crc16.crcl)&&(((crc16>>8)&0xFF)==phy->crc16.crch))
  {
    return 1;
  }
  return 0;
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
unsigned	short PaketMsg(unsigned	char* pbuffer,unsigned	short length)
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
unsigned short sendbuffer(unsigned char* pbuffer,unsigned short length)
{
  return  0;
}







