#ifndef __DS2401_H
#define __DS2401_H 
#include "stdint.h"


typedef enum
{
	Cmd_ReadROM		=	0x33,			//读ROM(33H)
	Cmd_MatchROM	=	0x55,			//匹配ROM(55H)
	Cmd_SkipROM		=	0xCC,			//跳过ROM(CCH)
	Cmd_SearchROM	=	0xF0			//查找ROM(F0H)
}DallasCmd;


uint8_t CRC8_Calculate(uint8_t *pBuf, uint8_t len);
uint8_t Dallas_Rest(void);								//复位Dallas,返回结果
//uint8_t Dallas_Check(void);						//等待Dallas的回应---包含到复位函数中
uint8_t Dallas_ReadBit(void);					//从Dallas读取一个位
uint8_t Dallas_ReadByte(void);				//从Dallas读取一个字节

void Dallas_WriteBit(unsigned char bit);		//1-wire 一位（1bit）写操作-写0&写1
void Dallas_WriteByte(uint8_t dat);		//写一个字节到Dallas
uint8_t Dallas_Init(void);						//初始化Dallas的IO口 DQ 同时检测DS的存在
uint8_t Dallas_GetID(uint8_t *pBuf);	//从Dallas器件Rom读出ID值

    
#endif

