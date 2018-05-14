#ifndef __PwrTest_H
#define __PwrTest_H

//#include "STM32_USART.H"
//#include "STM32_TIM.H"
//#include "STM32_DMA.H"
//#include "STM32_PWM.H"
//#include "STM32_GPIO.H"
//#include "STM32_ADC.H"
//#include "STM32_DAC.H"
//#include "STM32_SPI.H"


  #define GPIO_LED                          GPIOB    
  #define RCC_APB2Periph_GPIO_LED           RCC_APB2Periph_GPIOB
  #define GPIO_KEY_BUTTON                   GPIOA    
  #define RCC_APB2Periph_GPIO_KEY_BUTTON    RCC_APB2Periph_GPIOA
  #define GPIO_PIN_KEY_BUTTON               GPIO_Pin_0
  #define EXTI_LINE_KEY_BUTTON              EXTI_Line0
  #define GPIO_PORT_SOURCE_KEY_BUTTON       GPIO_PortSourceGPIOA
  #define GPIO_PIN_SOURCE_KEY_BUTTON        GPIO_PinSource0
	
//typedef enum {DISABLE1 = 2, ENABLE1 = 3} FunctionalState1;
//#define IS_FUNCTIONAL_STATE1(STATE) (((STATE) == DISABLE1) || ((STATE) == ENABLE1))

//typedef enum {DISABLE2 = 4, ENABLE2 = 5} FunctionalState2;
//#define IS_FUNCTIONAL_STATE2(STATE) (((STATE) == DISABLE2) || ((STATE) == ENABLE2))

void PwrTest_Configuration(void);
void PwrTest_Server(void);


void STOPMODEG_Config(void);
void RTC_Configuration(void);
void SYSCLKConfig_STOP(void);
void TEST_STOPMODE(void);



#endif

