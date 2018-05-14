#ifndef __LED_H__
#define __LED_H__

#include "STM32F10x_BitBand.h"

#define LED_INV                                     0			//1--高电平点亮LED；0--低电平点亮LED

typedef enum 
{
    LED_GREEN = 0,
    TXD_LED = 1,
    RXD_LED = 2,
    LED_DBG2 = 3,
} tLed;


//#if defined( STM32F4XX ) || defined( STM32F2XX )

//#define LED_NB                           5

//// RED
//#define LED1_PIN                         GPIO_Pin_5
//#define LED1_GPIO_PORT                   GPIOC
//#define LED1_GPIO_CLK                    RCC_AHB1Periph_GPIOC
//// GREEN
//#define LED2_PIN                         GPIO_Pin_4
//#define LED2_GPIO_PORT                   GPIOC
//#define LED2_GPIO_CLK                    RCC_AHB1Periph_GPIOC  
//// DBG1
//#define LED3_PIN                         GPIO_Pin_8
//#define LED3_GPIO_PORT                   GPIOI
//#define LED3_GPIO_CLK                    RCC_AHB1Periph_GPIOI  
//// DBG2
//#define LED4_PIN                         GPIO_Pin_9
//#define LED4_GPIO_PORT                   GPIOI
//#define LED4_GPIO_CLK                    RCC_AHB1Periph_GPIOI
//// DBG3
//#define LED5_PIN                         GPIO_Pin_10
//#define LED5_GPIO_PORT                   GPIOI
//#define LED5_GPIO_CLK                    RCC_AHB1Periph_GPIOI

//#elif defined( STM32F429_439xx )

//#define LED_NB                           5

//// RED
//#define LED1_PIN                         GPIO_Pin_5
//#define LED1_GPIO_PORT                   GPIOC
//#define LED1_GPIO_CLK                    RCC_AHB1Periph_GPIOC
//// GREEN
//#define LED2_PIN                         GPIO_Pin_4
//#define LED2_GPIO_PORT                   GPIOC
//#define LED2_GPIO_CLK                    RCC_AHB1Periph_GPIOC  
//// DBG1
//#define LED3_PIN                         GPIO_Pin_6
//#define LED3_GPIO_PORT                   GPIOB
//#define LED3_GPIO_CLK                    RCC_AHB1Periph_GPIOB  
//// DBG2
//#define LED4_PIN                         GPIO_Pin_5
//#define LED4_GPIO_PORT                   GPIOB
//#define LED4_GPIO_CLK                    RCC_AHB1Periph_GPIOB
//// DBG3
//#define LED5_PIN                         GPIO_Pin_4
//#define LED5_GPIO_PORT                   GPIOB
//#define LED5_GPIO_CLK                    RCC_AHB1Periph_GPIOB

//#else

#define LED_NB                           4			//LED数量

// RED
#define LED1_PIN                         GPIO_Pin_12
#define LED1_GPIO_PORT                   GPIOB
#define LED1_GPIO_CLK                    RCC_APB2Periph_GPIOB
// GREEN
#define LED2_PIN                         GPIO_Pin_13			//TX-LED发送完成LED
#define LED2_GPIO_PORT                   GPIOB
#define LED2_GPIO_CLK                    RCC_APB2Periph_GPIOB  
// DBG1
#define LED3_PIN                         GPIO_Pin_14			//RX-LED接收完成LED
#define LED3_GPIO_PORT                   GPIOB
#define LED3_GPIO_CLK                    RCC_APB2Periph_GPIOB  
// DBG2
#define LED4_PIN                         GPIO_Pin_15
#define LED4_GPIO_PORT                   GPIOB
#define LED4_GPIO_CLK                    RCC_APB2Periph_GPIOB

//#endif

#if LED_INV
#define LED_ON                           Bit_RESET
#define LED_OFF                          Bit_SET
#else
#define LED_ON                           Bit_SET
#define LED_OFF                          Bit_RESET
#endif


void LedInit( tLed led );				//LED初始化

void LedOn( tLed led );					//点亮LED

void LedOff( tLed led );				//关闭LED

void LedToggle( tLed led );			//LED翻转显示

#endif // __LED_H__
