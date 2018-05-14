#ifndef __TM1638_H
#define __TM1638_H
#include "stm32f10x_gpio.h"



typedef enum
{
	TM1638_Cathode	=	0,			//共阴数码管
	TM1638_Anode							//共阳数码管
}SegPolarity_TypeDef;				//数码管极性


typedef struct	_TM1638_Pin
{
	//DIO
	GPIO_TypeDef* 	TM1638_DIO_PORT;				//GPIOX
	unsigned short 	TM1638_DIO_Pin;				//GPIO_Pin_x
	
	//CLK
	GPIO_TypeDef* 	TM1638_CLK_PORT;				//GPIOX
	unsigned short 	TM1638_CLK_Pin;				//GPIO_Pin_x
	
	//STB
	GPIO_TypeDef* 	TM1638_STB_PORT;				//GPIOX
	unsigned short 	TM1638_STB_Pin;				//GPIO_Pin_x


}TM1638_Pindef;


void TM1638_PinConf(TM1638_Pindef *Pinfo);
void TM1638_WriteData(TM1638_Pindef *Pinfo,u16 Data);
void TM1638_WriteDataN(TM1638_Pindef *Pinfo,u16 Data);		//反向信号写入


#endif

