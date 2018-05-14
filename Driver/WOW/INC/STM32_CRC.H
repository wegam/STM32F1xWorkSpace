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


#ifndef __STM32_CRC_H
#define __STM32_CRC_H

#include "stm32f10x_type.h"

void InvertUint8	(unsigned char *dBuf,unsigned char *srcBuf);
void InvertUint16	(unsigned short *dBuf,unsigned short *srcBuf);
unsigned short CRC16_CCITT				(unsigned char *puchMsg, unsigned int usDataLen);
unsigned short CRC16_CCITT_FALSE	(unsigned char *puchMsg, unsigned int usDataLen);
unsigned short CRC16_XMODEM				(unsigned char *puchMsg, unsigned int usDataLen);
unsigned short CRC16_X25					(unsigned char *puchMsg, unsigned int usDataLen);
unsigned short CRC16_MODBUS				(unsigned char *puchMsg, unsigned int usDataLen);
unsigned short CRC16_IBM					(unsigned char *puchMsg, unsigned int usDataLen);
unsigned short CRC16_MAXIM				(unsigned char *puchMsg, unsigned int usDataLen);
unsigned short CRC16_USB					(unsigned char *puchMsg, unsigned int usDataLen);


void CRC_SetEnable(void);
u32 Get_CalcCrc32(u32 Data);
u32 Get_CalcCrc32(u32 Data);
u32 Get_CalcBlockCrc32(u32 pBuffer[],u32 BufferLength);

#endif


