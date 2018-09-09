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

