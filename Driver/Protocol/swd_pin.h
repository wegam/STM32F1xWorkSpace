#ifndef __swd_pin_H__
#define __swd_pin_H__


#include "stm32f10x_gpio.h"
#include "STM32_GPIO.H"
//#include "stdint.h"

#define SWCLK_PORT  		GPIOA
#define SWCLK_PIN     	GPIO_Pin_9

#define SWDIO_PORT     	GPIOA
#define SWDIO_PIN      	GPIO_Pin_10

#define RESET_PORT     	GPIOB
#define RESET_PIN      	GPIO_Pin_2

#define Mode50Hz				0x03<<0
#define ModeOutPP				0x00<<2
#define ModeInIP				0x02<<2

#define	PinPos(Pin)			Pin
//#define	SetCRL(PORT,m,s)			PORT ->CRL&=0xFFFFFFFF^((m|s)<<4);PORT ->CRL|=((m|s)<<4)
//#define	SetCRH(PORT,m,s)			PORT ->CRH&=0xFFFFFFFF^((m|s)<<8);PORT ->CRH|=((m|s)<<8)

//#define SWDIO_SET_OUTPUT()     SWDIO_GPIO ->CRL |=  (1 << SWDIO_PIN)  //DDIR(1)
//#define SWDIO_SET_INPUT()      SWDIO_GPIO ->PDDR &= ~(1 << SWDIO_PIN);\
//                               SWDIO_GPIO ->PIDR  &= ~(1 << SWDIO_PIN)
//#define SWCLK_SET_OUTPUT()     SWDIO_GPIO ->PDDR |=  (1 << SWCLK_PIN)  //DDIR(1)
//#define RESET_SET_OUTPUT()     SWDIO_GPIO ->PDDR |=  (1 << RESET_PIN)  //DDIR(1)
//#define SWCLK_SET()            SWCLK_GPIO ->PDOR |=  (1 << SWCLK_PIN)  //TCK(1)
//#define SWCLK_CLR()            SWCLK_GPIO ->PDOR &= ~(1 << SWCLK_PIN)  //TCK(0)
//#define RESET_SET()            RESET_GPIO ->PDOR |=  (1 << RESET_PIN)  //TRST(1)
//#define RESET_CLR()            RESET_GPIO ->PDOR &= ~(1 << RESET_PIN)  //TRST(0) 
//#define SWDIO_SET()            SWDIO_GPIO ->PDOR |=  (1 << SWDIO_PIN)   //SWDIO_OUT(1)
//#define SWDIO_CLR()            SWDIO_GPIO ->PDOR &= ~(1 << SWDIO_PIN)  //SWDIO_OUT(0)


//#define SWDIO_SET_OUTPUT()  	(SWDIO_PIN<0x00FF)?(1):(SetCRH(SWDIO_PORT,Mode50Hz,ModeOutPP))
//#define SWDIO_SET_OUTPUT()  	(SWDIO_PIN<0x00FF)?(1):(SetCRH(SWDIO_PORT,Mode50Hz,ModeOutPP))


//#define SWDIO_SET_OUTPUT()  	((SWDIO_PIN<0x00FF)?(SetCRL(SWDIO_PORT,Mode50Hz,ModeOutPP)):(SetCRH(SWDIO_PORT,Mode50Hz,ModeOutPP)))
//#define SWDIO_SET_INPUT()			SWDIO_PORT->BSRR = SWDIO_PIN;(SWDIO_PIN<0x00FF)?(SetCRL(SWDIO_PORT,Mode50Hz,ModeInIP)):(SetCRH(SWDIO_PORT,Mode50Hz,ModeInIP))
//#define SWCLK_SET_OUTPUT()  	(SWCLK_PIN<0x00FF)?(SetCRL(SWCLK_PORT,Mode50Hz,ModeOutPP)):(SetCRH(SWCLK_PORT,Mode50Hz,ModeOutPP))
//#define RESET_SET_OUTPUT()    (RESET_PIN<0x00FF)?(SetCRL(RESET_PORT,Mode50Hz,ModeOutPP)):(SetCRH(RESET_PORT,Mode50Hz,ModeOutPP))

//#define SWCLK_SET()            SWCLK_GPIO ->PDOR |=  (1 << SWCLK_PIN)  //TCK(1)
//#define SWCLK_CLR()            SWCLK_GPIO ->PDOR &= ~(1 << SWCLK_PIN)  //TCK(0)
//#define RESET_SET()            RESET_GPIO ->PDOR |=  (1 << RESET_PIN)  //TRST(1)
//#define RESET_CLR()            RESET_GPIO ->PDOR &= ~(1 << RESET_PIN)  //TRST(0) 
//#define SWDIO_SET()            SWDIO_GPIO ->PDOR |=  (1 << SWDIO_PIN)   //SWDIO_OUT(1)
//#define SWDIO_CLR()            SWDIO_GPIO ->PDOR &= ~(1 << SWDIO_PIN)  //SWDIO_OUT(0)

//#define SWDIO_IN()    (((SWDIO_GPIO ->PDIR) >> SWDIO_PIN) & 0x01U)//BITBAND_REG(PTB->PDIR, n)
//#define SWDIO_OUT(n)    {if ( n ) SWDIO_SET(); else SWDIO_CLR();}


#define SWDIO_SET_OUTPUT()  	GPIO_Configuration_OPP50	(SWDIO_PORT,SWDIO_PIN);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605
#define SWDIO_SET_INPUT()  		GPIO_Configuration_IPU(SWDIO_PORT,SWDIO_PIN);					//将GPIO相应管脚配置为上拉输入模式----V20170605
//#define SWDIO_SET_OUTPUT()  	SWDIO_PORT->CRH	&=0xFFFFF0FF;SWDIO_PORT->CRH	|=0x00000300;		//SWDIO设置为输出
//#define SWDIO_SET_INPUT()  		SWDIO_PORT->CRH	&=0xFFFFF0FF;SWDIO_PORT->CRH	|=0x00000200;		//SWDIO设置为输入
#define SWCLK_SET_OUTPUT()  	GPIO_Configuration_OPP50	(SWCLK_PORT,SWCLK_PIN);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605
#define RESET_SET_OUTPUT()    RESET_PORT->CRL	&=0xFFFFF0FF;RESET_PORT->CRL	|=0x00000300;		//RESET设置为输出

//#define SWDIO_SET_OUTPUT()  	SWDIO_PORT->CRL	&=0xFFFFFF0F;SWDIO_PORT->CRL	|=0x00000030;		//SWDIO设置为输出
//#define SWDIO_SET_INPUT()  		SWDIO_PORT->CRL	&=0xFFFFFF0F;SWDIO_PORT->CRL	|=0x00000020;		//SWDIO设置为输入
//#define SWCLK_SET_OUTPUT()  	SWCLK_PORT->CRL	&=0xFFFFFFF0;SWCLK_PORT->CRL	|=0x00000003;		//SWCLK设置为输出
//#define RESET_SET_OUTPUT()    RESET_PORT->CRL	&=0xFFFFF0FF;RESET_PORT->CRL	|=0x00000300;		//RESET设置为输出

#define SWCLK_SET()         	SWCLK_PORT ->BSRR	=	SWCLK_PIN  //SWCLK	=	HIGH
#define SWCLK_CLR()         	SWCLK_PORT ->BRR 	=	SWCLK_PIN  //SWCLK	=	LOW
#define RESET_SET()         	RESET_PORT ->BSRR	=	RESET_PIN  //REST	=	HIGH
#define RESET_CLR()          	RESET_PORT ->BRR 	=	RESET_PIN  //REST	=	LOW
#define SWDIO_SET()          	SWDIO_PORT ->BSRR	=	SWDIO_PIN   //SWDIO_OUT(1)
#define SWDIO_CLR()          	SWDIO_PORT ->BRR 	= SWDIO_PIN  //SWDIO_OUT(0)

#define SWDIO_IN()    	GPIO_ReadInputDataBit(SWDIO_PORT,SWDIO_PIN)//BITBAND_REG(PTB->PDIR, n)
//#define SWDIO_IN()    	SWDIO_PORT->IDR & SWDIO_PIN//BITBAND_REG(PTB->PDIR, n)
#define SWDIO_OUT(n)    {if ( n ) SWDIO_SET(); else SWDIO_CLR();}


/* pin interface */
void SW_PinInit(void);
unsigned long SW_READ_BIT(void);			//读一位数据
void SW_CLOCK_CYCLE(void);						//输出时钟信号
void SW_WRITE_BIT(unsigned long bit);	//位写--写一位数据

void PIN_DELAY(void);
void DELAY_US(unsigned long us);

#endif


