#ifndef __IOTReaderTest_H
#define __IOTReaderTest_H

#include "STM32_USART.H"
#include "STM32_TIM.H"
#include "STM32_DMA.H"
#include "STM32_PWM.H"
#include "STM32_GPIO.H"
#include "STM32_ADC.H"
#include "STM32_DAC.H"


//#include "delay.h"
//#include "sys.h"
#include "STM32_096OLED.h"



void IOTReaderTest_Configuration(void);
void IOTReaderTest_Server(void);



void IOTReaderTestCOMM_Configuration(void);
void IOTReaderTestCOMM_Server(void);

#endif

