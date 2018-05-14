#ifndef __TOOL_H
#define __TOOL_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_type.h"



u8 BCC8(u8 *Pointer,u16 num);			//异或校验
u8 CRC8(u8 *Pointer);			//循环冗余校验
u8 LRC8(u8 *Pointer);		//纵向冗余校验

unsigned char 	GetMaxChar	(unsigned char *pBuffer,unsigned short Length);		//获取unsigned char型最大值
unsigned short 	GetMaxShort	(unsigned short *pBuffer,unsigned short Length);	//获取unsigned short型最大值
unsigned long 	GetMaxLong	(unsigned long *pBuffer,unsigned short Length);		//获取unsigned long型最大值

unsigned char 	GetMinChar	(unsigned char *pBuffer,unsigned short Length);		//获取unsigned char型最小值
unsigned short 	GetMinShort(unsigned short *pBuffer,unsigned short Length);		//获取unsigned short型最小值
unsigned long 	GetMinLong	(unsigned long *pBuffer,unsigned short Length);		//获取unsigned long型最小值

unsigned long 	GetAveLong(unsigned long *pBuffer,unsigned short Length);			//获取unsigned long型平均值
unsigned long 	GetVarLong(unsigned long *pBuffer,unsigned short Length);			//获取unsigned long方差

#endif


