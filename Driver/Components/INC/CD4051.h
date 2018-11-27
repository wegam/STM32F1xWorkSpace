
#ifndef __CD4051_H
#define __CD4051_H
//#include <stdint.h>
#include "stm32f10x_gpio.h"
typedef struct	_CD4511Port
{
	//A
	GPIO_TypeDef* 	A_PORT;				//GPIOX
	unsigned short 	A_Pin;					//GPIO_Pin_x
	
	//B
	GPIO_TypeDef* 	B_PORT;				//GPIOX
	unsigned short 	B_Pin;					//GPIO_Pin_x
	
	//C
	GPIO_TypeDef* 	C_PORT;				//GPIOX
	unsigned short 	C_Pin;					//GPIO_Pin_x
	
	//ENABLE-PIN
	GPIO_TypeDef* 	EN_PORT;				//GPIOX
	unsigned short 	EN_Pin;					//GPIO_Pin_x
}stCD4051PortDef;

typedef struct	_CD4511
{
	stCD4051PortDef	Port;
}stCD4051Def;

//extern CD4511BcdDef*	CD4511Bcd;		//BCD码结构体

void CD4051_Initialize(stCD4051Def *pInfo);
void CD4051_Clear(stCD4051Def *pInfo);		//清除输出：bitA~bitG输出低电平
	
void CD4051_WriteChannel(stCD4051Def *pInfo,unsigned char nChannel);













#endif


