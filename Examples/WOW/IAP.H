#ifndef __IAP_H
#define __IAP_H

//#include "STM32_USART.H"
//#include "STM32_TIM.H"
//#include "STM32_DMA.H"
//#include "STM32_PWM.H"
//#include "STM32_GPIO.H"
//#include "STM32_ADC.H"
//#include "STM32_DAC.H"
//#include "STM32_SPI.H"

#include "stm32f10x_type.h"
#include "stm32f10x_gpio.h"




#define	UpdataKey1	0xFFAA
#define	UpdataKey2	0xFFBB
#define	UpdataKey3	0xFFCC
#define	UpdataKey4	0xFFDD
#define	UpdataKey5	0xFFEE
#define	UpdataKey6	0xFFFF










void IAP_Configuration(void);
void IAP_Server(void);







#endif

