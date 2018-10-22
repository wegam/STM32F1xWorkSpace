#ifndef __TOOL_H
#define __TOOL_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_type.h"


typedef struct
{
 u16 year; 
 u8 month;
 u8 day;
 u8 hour;
 u8 minute;
 u8 second;
}BuildTimeDef;


BuildTimeDef GetBuildTime(void* pDate, void*	pTime);
unsigned short GetBuildYear(const char* DataStr);
unsigned char GetBuildMonth(const char* DataStr);
unsigned char GetBuildDay(const char* DataStr);
unsigned char GetBuildHour(const char* TimeStr);
unsigned char GetBuildMinute(const char* TimeStr);
unsigned char GetBuildSecond(const char* TimeStr);

unsigned char BCC8(const unsigned char *buffer,unsigned short num);		//异或校验
unsigned char CRC8(const unsigned char *buffer);						//循环冗余校验
unsigned char LRC8(const unsigned char *buffer);						//纵向冗余校验

unsigned char 	GetMaxChar	(unsigned char *pBuffer,unsigned short Length);		//获取unsigned char型最大值
unsigned short 	GetMaxShort	(unsigned short *pBuffer,unsigned short Length);	//获取unsigned short型最大值
unsigned long 	GetMaxLong	(unsigned long *pBuffer,unsigned short Length);		//获取unsigned long型最大值

unsigned char 	GetMinChar	(unsigned char *pBuffer,unsigned short Length);		//获取unsigned char型最小值
unsigned short 	GetMinShort(unsigned short *pBuffer,unsigned short Length);		//获取unsigned short型最小值
unsigned long 	GetMinLong	(unsigned long *pBuffer,unsigned short Length);		//获取unsigned long型最小值

unsigned long 	GetAveLong(unsigned long *pBuffer,unsigned short Length);			//获取unsigned long型平均值
unsigned long 	GetVarLong(unsigned long *pBuffer,unsigned short Length);			//获取unsigned long方差

#endif


