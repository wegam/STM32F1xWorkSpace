#ifndef __TM1638_H
#define __TM1638_H
#include "stm32f10x_gpio.h"



void TM1638_Write(unsigned char	DATA);			//写数据函数
unsigned char TM1638_Read(void);						//读数据函数
void Write_COM(unsigned char cmd);					//发送命令字
unsigned char Read_key(void);
void Write_DATA(unsigned char add,unsigned char DATA);					//指定地址写入一字节数据
void Write_DataFX(unsigned char add,unsigned char DATA);				//固定地址方式
void Write_DataAI(unsigned char add,unsigned char DATA);				//地址自增
void Write_allLED(unsigned char LED_flag);											//控制全部LED函数，LED_flag表示各个LED状态



void Write_DataNum(unsigned char Startadd,unsigned long Num);		//地址自增方式写入8位数据
void init_TM1638(void);


#endif

