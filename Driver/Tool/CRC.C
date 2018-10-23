/************************************ TOOLS ************************************
* 文件名 	: LinkedList链表
* 作者   	: wegam@sina.com
* 版本   	: V
* 日期   	: 2017/09/11
* 说明   	: 
********************************************************************************
其它说明:
*
*
*
*
*
*
*
*
*******************************************************************************/
#include 	"CRC.H"

//#include	"stdio.h"				//用于printf
//#include	"string.h"			//用于printf
//#include	"stdarg.h"			//用于获取不确定个数的参数
//#include	"stdlib.h"			//malloc动态申请内存空间


//CRC16常见的标准有以下几种，被用在各个规范中，其算法原理基本一致，就是在数据的输入和输出有所差异，下边把这些标准的差异列出，并给出C语言的算法实现。
//CRC16_CCITT：				多项式x16+x12+x5+1（0x1021），初始值0x0000，低位在前，高位在后，结果与0x0000异或
//CRC16_CCITT_FALSE：	多项式x16+x12+x5+1（0x1021），初始值0xFFFF，低位在后，高位在前，结果与0x0000异或
//CRC16_XMODEM：			多项式x16+x12+x5+1（0x1021），初始值0x0000，低位在后，高位在前，结果与0x0000异或
//CRC16_X25：					多项式x16+x12+x5+1（0x1021），初始值0x0000，低位在前，高位在后，结果与0xFFFF异或

//CRC16_MODBUS：			多项式x16+x15+x5+1（0x8005），初始值0xFFFF，低位在前，高位在后，结果与0x0000异或
//CRC16_IBM：					多项式x16+x15+x5+1（0x8005），初始值0x0000，低位在前，高位在后，结果与0x0000异或
//CRC16_MAXIM：				多项式x16+x15+x5+1（0x8005），初始值0x0000，低位在前，高位在后，结果与0xFFFF异或
//CRC16_USB：					多项式x16+x15+x5+1（0x8005），初始值0xFFFF，低位在前，高位在后，结果与0xFFFF异或

//CRC16的算法原理：
//1.根据CRC16的标准选择初值CRCIn的值。
//2.将数据的第一个字节与CRCIn高8位异或。
//3.判断最高位，若该位为 0 左移一位，若为 1 左移一位再与多项式Hex码异或。
//4.重复3直至8位全部移位计算结束。
//5.重复将所有输入数据操作完成以上步骤，所得16位数即16位CRC校验码。 

/*******************************************************************************
*函数名			:	InvertUint8
*功能描述		:	函数功能说明
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
void InvertUint8(unsigned char *dBuf,unsigned char *srcBuf)
{
	int	i	=	0;
	unsigned char tmp[4];
	tmp[0] = 0;
	for(i=0; i< 8; i++)
	{
		if(srcBuf[0]& (1 << i))
		tmp[0]|=1<<(7-i);
	}
	dBuf[0] = tmp[0];
}
/*******************************************************************************
*函数名			:	InvertUint16
*功能描述		:	函数功能说明
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
void InvertUint16(unsigned short *dBuf,unsigned short *srcBuf)
{
	int	i	=	0;
	unsigned short tmp[4];
	tmp[0] = 0;
	for(i=0; i< 16; i++)
	{
		if(srcBuf[0]& (1 << i))
			tmp[0]|=1<<(15 - i);
	}
	dBuf[0] = tmp[0];
} 
/*******************************************************************************
*函数名			:	function
*功能描述		:	多项式x16+x12+x5+1（0x1021），初始值0x0000，低位在前，高位在后，结果与0x0000异或
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
unsigned short CRC16_CCITT(unsigned char *puchMsg, unsigned int usDataLen)
{
  unsigned short 	wCRCin 	= 0x0000;
  unsigned short 	wCPoly 	= 0x1021;
  unsigned char 	wChar 	= 0;
  int	i	=	0;
	
  while (usDataLen--) 	
  {
			wChar = *(puchMsg++);
			InvertUint8(&wChar,&wChar);
			wCRCin ^= (wChar << 8);
			for(i = 0;i < 8;i++)
			{
				if(wCRCin & 0x8000)
					wCRCin = (wCRCin << 1) ^ wCPoly;
				else
					wCRCin = wCRCin << 1;
			}
  }
  InvertUint16(&wCRCin,&wCRCin);
  return (wCRCin) ;
}
/*******************************************************************************
*函数名			:	CRC16_CCITT_FALSE
*功能描述		:	多项式x16+x12+x5+1（0x1021），初始值0xFFFF，低位在后，高位在前，结果与0x0000异或
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
unsigned short CRC16_CCITT_FALSE(unsigned char *puchMsg, unsigned int usDataLen)
{
  unsigned short wCRCin = 0xFFFF;
  unsigned short wCPoly = 0x1021;
  unsigned char wChar = 0;
  int	i	=	0;
	
  while (usDataLen--) 	
  {
        wChar = *(puchMsg++);
        wCRCin ^= (wChar << 8);
        for(i = 0;i < 8;i++)
        {
          if(wCRCin & 0x8000)
            wCRCin = (wCRCin << 1) ^ wCPoly;
          else
            wCRCin = wCRCin << 1;
        }
  }
  return (wCRCin) ;
}
/*******************************************************************************
*函数名			:	CRC16_XMODEM
*功能描述		:	多项式x16+x12+x5+1（0x1021），初始值0x0000，低位在后，高位在前，结果与0x0000异或
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
unsigned short CRC16_XMODEM(unsigned char *puchMsg, unsigned int usDataLen)
{
  unsigned short 	wCRCin 	= 0x0000;
  unsigned short 	wCPoly 	= 0x1021;
  unsigned char 	wChar 	= 0;
  int	i	=	0;
	
  while (usDataLen--) 	
  {
        wChar = *(puchMsg++);
        wCRCin ^= (wChar << 8);
        for(i = 0;i < 8;i++)
        {
          if(wCRCin & 0x8000)
            wCRCin = (wCRCin << 1) ^ wCPoly;
          else
            wCRCin = wCRCin << 1;
        }
  }
  return (wCRCin) ;
}
/*******************************************************************************
*函数名			:	CRC16_X25
*功能描述		:	多项式x16+x12+x5+1（0x1021），初始值0x0000，低位在前，高位在后，结果与0xFFFF异或
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
unsigned short CRC16_X25(unsigned char *puchMsg, unsigned int usDataLen)
{
  unsigned short 	wCRCin 	= 0xFFFF;
  unsigned short 	wCPoly 	= 0x1021;
  unsigned char 	wChar 	= 0;
  int	i	=	0;
	
  while (usDataLen--) 	
  {
        wChar = *(puchMsg++);
        InvertUint8(&wChar,&wChar);
        wCRCin ^= (wChar << 8);
        for(i = 0;i < 8;i++)
        {
          if(wCRCin & 0x8000)
            wCRCin = (wCRCin << 1) ^ wCPoly;
          else
            wCRCin = wCRCin << 1;
        }
  }
  InvertUint16(&wCRCin,&wCRCin);
	return (wCRCin^0xFFFF) ;
//	wCRCin	=	wCRCin^0xFFFF;
//	*puchMsg++	=	wCRCin&0XFF;
//	*puchMsg++	=	wCRCin>>8&0XFF;
}
/*******************************************************************************
*函数名			:	CRC16_MODBUS
*功能描述		:	多项式x16+x15+x5+1（0x8005），初始值0xFFFF，低位在前，高位在后，结果与0x0000异或
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
unsigned short CRC16_MODBUS(unsigned char *puchMsg, unsigned int usDataLen)
{
  unsigned short wCRCin = 0xFFFF;
  unsigned short wCPoly = 0x8005;
  unsigned char wChar 	= 0;
  int	i	=	0;
	
  while (usDataLen--) 	
  {
        wChar = *(puchMsg++);
        InvertUint8(&wChar,&wChar);
        wCRCin ^= (wChar << 8);
        for(i = 0;i < 8;i++)
        {
          if(wCRCin & 0x8000)
            wCRCin = (wCRCin << 1) ^ wCPoly;
          else
            wCRCin = wCRCin << 1;
        }
  }
  InvertUint16(&wCRCin,&wCRCin);
  return (wCRCin) ;
}
/*******************************************************************************
*函数名			:	CRC16_IBM
*功能描述		:	多项式x16+x15+x5+1（0x8005），初始值0x0000，低位在前，高位在后，结果与0x0000异或
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
unsigned short CRC16_IBM(unsigned char *puchMsg, unsigned int usDataLen)
{
  unsigned short wCRCin = 0x0000;
  unsigned short wCPoly = 0x8005;
  unsigned char wChar 	= 0;
  int	i	=	0;
	
  while (usDataLen--) 	
  {
        wChar = *(puchMsg++);
        InvertUint8(&wChar,&wChar);
        wCRCin ^= (wChar << 8);
        for(i = 0;i < 8;i++)
        {
          if(wCRCin & 0x8000)
            wCRCin = (wCRCin << 1) ^ wCPoly;
          else
            wCRCin = wCRCin << 1;
        }
  }
  InvertUint16(&wCRCin,&wCRCin);
  return (wCRCin) ;
}
/*******************************************************************************
*函数名			:	CRC16_MAXIM
*功能描述		:	多项式x16+x15+x5+1（0x8005），初始值0x0000，低位在前，高位在后，结果与0xFFFF异或
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
unsigned short CRC16_MAXIM(unsigned char *puchMsg, unsigned int usDataLen)
{
  unsigned short wCRCin = 0x0000;
  unsigned short wCPoly = 0x8005;
  unsigned char wChar 	= 0;
  int	i	=	0;
	
  while (usDataLen--) 	
  {
        wChar = *(puchMsg++);
        InvertUint8(&wChar,&wChar);
        wCRCin ^= (wChar << 8);
        for(i = 0;i < 8;i++)
        {
          if(wCRCin & 0x8000)
            wCRCin = (wCRCin << 1) ^ wCPoly;
          else
            wCRCin = wCRCin << 1;
        }
  }
  InvertUint16(&wCRCin,&wCRCin);
  return (wCRCin^0xFFFF) ;
}
/*******************************************************************************
*函数名			:	CRC16_USB
*功能描述		:	多项式x16+x15+x5+1（0x8005），初始值0xFFFF，低位在前，高位在后，结果与0xFFFF异或
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
unsigned short CRC16_USB(unsigned char *puchMsg, unsigned int usDataLen)
{
  unsigned short wCRCin = 0xFFFF;
  unsigned short wCPoly = 0x8005;
  unsigned char wChar 	= 0;
  int i = 0;
	
  while (usDataLen--) 	
  {
        wChar = *(puchMsg++);
        InvertUint8(&wChar,&wChar);
        wCRCin ^= (wChar << 8);
        for(i = 0;i < 8;i++)
        {
          if(wCRCin & 0x8000)
            wCRCin = (wCRCin << 1) ^ wCPoly;
          else
            wCRCin = wCRCin << 1;
        }
  }
  InvertUint16(&wCRCin,&wCRCin);
  return (wCRCin^0xFFFF) ;
}
