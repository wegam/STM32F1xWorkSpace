#ifndef __OneWrie_H
#define __OneWrie_H

#include "stdint.h"

#include "stm32f10x_gpio.h"


//#include "STM32_GPIO.H"

typedef	struct	_OneWrie				//带反馈锁控制标志及吸合时间
{
	//-------------------------锁驱动
	GPIO_TypeDef*	Data_Port;
	u16	Data_Pin;
}OneWrieDef;



void OneWrie_Configuration(OneWrieDef *OneWrie);		//启用锁--配置
void OneWrie_Server(OneWrieDef *OneWrie);



unsigned char OneWrie_Start(OneWrieDef *OneWrie);
unsigned char OneWrie_WriteByte(OneWrieDef *OneWrie,unsigned char dat);
unsigned char OneWrie_ReadByte(OneWrieDef *OneWrie);




unsigned char OneWrie_SetOut(OneWrieDef *OneWrie);
unsigned char OneWrie_SetIn(OneWrieDef *OneWrie);
unsigned char OneWrie_SetHigh(OneWrieDef *OneWrie);
unsigned char OneWrie_SetLow(OneWrieDef *OneWrie);
unsigned char OneWrie_Read(OneWrieDef *OneWrie);
unsigned char OneWrie_ReadAck(OneWrieDef *OneWrie);
unsigned char OneWrie_ReadBit(OneWrieDef *OneWrie);
unsigned char OneWrie_WriteBit(OneWrieDef *OneWrie,unsigned char bit);

#endif

