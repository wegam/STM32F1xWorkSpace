/******************************** User_library *********************************
* 文件名 	: STM32_SDCard.H
* 作者   	: wegam@sina.com
* 版本   	: V
* 日期   	: 2016/01/01
* 说明   	: 
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/


#include "STM32_CRC.H"
//#include "STM32F10x_BitBand.H"


#include "stm32f10x_crc.h"
#include "stm32f10x_rcc.h"

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
*函数名			:	function
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
*函数名			:	function
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
*功能描述		:	函数功能说明
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
*函数名			:	function
*功能描述		:	函数功能说明
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
*函数名			:	function
*功能描述		:	函数功能说明
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
*函数名			:	function
*功能描述		:	函数功能说明
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
*函数名			:	function
*功能描述		:	函数功能说明
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
*函数名			:	function
*功能描述		:	函数功能说明
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
*函数名			:	function
*功能描述		:	函数功能说明
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
*函数名			:	function
*功能描述		:	函数功能说明
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
/*******************************************************************************
*函数名			:	function
*功能描述		:	函数功能说明
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
void CRC_SetEnable(void)
{
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_CRC, ENABLE);		//打开CRC硬件时钟
	CRC_ResetDR();					//复位CRC模块
}
/*******************************************************************************
*函数名			:	function
*功能描述		:	函数功能说明
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
u32 Get_CalcCrc32(u32 Data)
{
	CRC_ResetDR();
	return CRC_CalcCRC(Data);
}
/*******************************************************************************
*函数名			:	function
*功能描述		:	函数功能说明
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
u32 Get_CalcBlockCrc32(u32 pBuffer[],u32 BufferLength)
{
	CRC_ResetDR();
	return CRC_CalcBlockCRC(pBuffer, BufferLength);
}

 /*******************************************************************************
* Function Name  : CRC32_ForWords
* Description    :输入的是32bit buffer的指针及长度
* Input          : 
* Output         : 
* Return         : 
* 说明           :
*******************************************************************************/
//u32 CRC32_ForWords(u32 *pData,u32 uLen)
//{
//	u32 i = 0,uData = 0;
//	if((RCC->AHB1ENR & RCC_CRC_BIT) == 0)
//	{
//		RCC->AHB1ENR |= RCC_CRC_BIT;
//	}

//	/* Reset CRC generator */
//	CRC->CR = CRC_CR_RESET;
//	for (i = 0;i < uLen;i++)
//	{
//#ifdef USED_BIG_ENDIAN		
//		uData = __REV(*(pData + i));
//#else
//		uData = *(pData + i);
//#endif		
//		CRC->DR = revbit(uData);
//	}
//	return revbit(CRC->DR)^0xFFFFFFFF;
//}
//#define	CRC32_POLYNOMIAL						((uint32_t)0xEDB88320)
//#define	RCC_CRC_BIT			           			((uint32_t)0x00001000)

//#define	USED_BIG_ENDIAN

/*==================================================================
* Function	: CRC32_ForBytes
* Description	: CRC32输入为8bits buffer的指针及长度
* Input Para	: 
* Output Para	: 
* Return Value: 
==================================================================*/
//u32 CRC32_ForBytes(u8 *pData,u32 uLen)
//{
//	u32 uIndex= 0,uData = 0,i;
//	uIndex = uLen >> 2;
//	
//	if((RCC->AHB1ENR & RCC_CRC_BIT) == 0)
//	{
//		RCC->AHB1ENR |= RCC_CRC_BIT;
//	}

//	/* Reset CRC generator */
//	CRC->CR = CRC_CR_RESET;
//	  
//	while(uIndex--)
//	{
//#ifdef USED_BIG_ENDIAN	
//		uData = __REV((u32*)pData);
//#else
//		memcpy((u8*)&uData,pData,4);
//#endif		
//		pData += 4;
//		uData = revbit(uData);
//		CRC->DR = uData;
//	}
//	uData = revbit(CRC->DR);
//	uIndex = uLen & 0x03;
//	while(uIndex--)
//	{
//	    uData ^= (u32)*pData++;
//	    for(i = 0;i < 8;i++)
//	      if (uData & 0x1)
//	        uData = (uData >> 1) ^ CRC32_POLYNOMIAL;
//	      else
//	        uData >>= 1;
//	}
//	return uData^0xFFFFFFFF;
//}

