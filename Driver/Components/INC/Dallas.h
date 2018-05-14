#ifndef __Dallas_H
#define __Dallas_H 
#include "stdint.h"





uint8_t CRC8_Calculate(uint8_t *pBuf, uint8_t len);
void Dallas_Rst(void);
uint8_t Dallas_Check(void);						//�ȴ�Dallas�Ļ�Ӧ
uint8_t Dallas_ReadBit(void);					//��Dallas��ȡһ��λ
uint8_t Dallas_ReadByte(void);				//��Dallas��ȡһ���ֽ�

void Dallas_WriteBit(unsigned char bit);		//1-wire һλ��1bit��д����-д0&д1
void Dallas_WriteByte(uint8_t dat);		//дһ���ֽڵ�Dallas
uint8_t Dallas_Init(void);						//��ʼ��Dallas��IO�� DQ ͬʱ���DS�Ĵ���
uint8_t Dallas_GetID(uint8_t *pBuf);	//��Dallas����Rom����IDֵ

    
#endif

