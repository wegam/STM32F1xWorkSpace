#ifndef __DS2401_H
#define __DS2401_H 
#include "stdint.h"


typedef enum
{
	Cmd_ReadROM		=	0x33,			//��ROM(33H)
	Cmd_MatchROM	=	0x55,			//ƥ��ROM(55H)
	Cmd_SkipROM		=	0xCC,			//����ROM(CCH)
	Cmd_SearchROM	=	0xF0			//����ROM(F0H)
}DallasCmd;


uint8_t CRC8_Calculate(uint8_t *pBuf, uint8_t len);
uint8_t Dallas_Rest(void);								//��λDallas,���ؽ��
//uint8_t Dallas_Check(void);						//�ȴ�Dallas�Ļ�Ӧ---��������λ������
uint8_t Dallas_ReadBit(void);					//��Dallas��ȡһ��λ
uint8_t Dallas_ReadByte(void);				//��Dallas��ȡһ���ֽ�

void Dallas_WriteBit(unsigned char bit);		//1-wire һλ��1bit��д����-д0&д1
void Dallas_WriteByte(uint8_t dat);		//дһ���ֽڵ�Dallas
uint8_t Dallas_Init(void);						//��ʼ��Dallas��IO�� DQ ͬʱ���DS�Ĵ���
uint8_t Dallas_GetID(uint8_t *pBuf);	//��Dallas����Rom����IDֵ

    
#endif

