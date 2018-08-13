#ifndef __TM1616_H
#define __TM1616_H
#include "stm32f10x_gpio.h"



typedef enum
{
	TM1616_Cathode	=	0,			//共阴数码管
	TM1616_Anode							//共阳数码管
}SegPolarity_TypeDef;				//数码管极性


typedef struct	_TM1616_Pin
{
	//DIO
	GPIO_TypeDef* 	DIO_PORT;				//GPIOX
	unsigned short 	DIO_Pin;				//GPIO_Pin_x
	
	//CLK
	GPIO_TypeDef* 	CLK_PORT;				//GPIOX
	unsigned short 	CLK_Pin;				//GPIO_Pin_x
	
	//STB
	GPIO_TypeDef* 	STB_PORT;				//GPIOX
	unsigned short 	STB_Pin;				//GPIO_Pin_x


}TM1616Def;


void TM1616_Initialize(TM1616Def *Pinfo);
void TM1616_Display(TM1616Def *Pinfo,u16 Data);


#endif

