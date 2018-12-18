#ifndef __TLE5012B_H
#define __TLE5012B_H


//#include "stm32f10x_gpio.h"
//#include "stm32f10x_rcc.h"
//#include "stm32f10x_nvic.h"
//#include "stm32f10x_spi.h"

//#include "STM32_GPIO.H"


//#include	"stdio.h"			//用于printf
//#include	"string.h"			//用于printf
//#include	"stdarg.h"			//用于获取不确定个数的参数
//#include	"stdlib.h"			//malloc动态申请内存空间




#define SPI_TX_OFF {GPIOA->CRL&=0x0FFFFFFF;GPIOA->CRL|=0x40000000;}//把PA7（MOSI）配置成开漏--输入模式
#define SPI_TX_ON  {GPIOA->CRL&=0x0FFFFFFF;GPIOA->CRL|=0xB0000000;}//把PA7（MOSI）配置成推挽--输出模式（50MHz）

#define GPIO_CS_Pin_Name  GPIO_Pin_4
#define GPIO_CS_Pin_Type  GPIOA

//以下内容一般不需变动
#define SPI_CS_ENABLE  GPIO_ResetBits(GPIO_CS_Pin_Type, GPIO_CS_Pin_Name)       //片选脚电平拉低
#define SPI_CS_DISABLE GPIO_SetBits(GPIO_CS_Pin_Type, GPIO_CS_Pin_Name)         //片选脚电平拉高
//#define INDEX_ENABLE   GPIO_SetBits(GPIOA, GPIO_Pin_4)/* for incremental signal index */

//#define CLK_H GPIO_SetBits(GPIOA, GPIO_Pin_5)                 //时钟脚PA5电平拉高
//#define CLK_L GPIO_ResetBits(GPIOA, GPIO_Pin_5)               //时钟脚PA5电平拉低

//#define DATA_H	GPIO_SetBits(GPIOA, GPIO_Pin_6)                         //PA6（MISO）电平拉高
//#define DATA_L	GPIO_ResetBits(GPIOA, GPIO_Pin_6)                       //PA6（MISO）电平拉低
//#define READ_DATA	GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6)

/* SPI command for TLE5012 */
#define READ_STATUS					0x8001			//8000
#define READ_ANGLE_VALUE		0x8021			//8020
#define READ_SPEED_VALUE		0x8031			//8030

#define WRITE_MOD1_VALUE		0x5060							//0_1010_0_000110_0001
#define MOD1_VALUE	0x0001

#define WRITE_MOD2_VALUE		0x5080							//0_1010_0_001000_0001
#define MOD2_VALUE	0x0801

#define WRITE_MOD3_VALUE		0x5091							//0_1010_0_001001_0001
#define MOD3_VALUE	0x0000

#define WRITE_MOD4_VALUE		0x50E0							//0_1010_0_001110_0001
#define MOD4_VALUE	0x0098				//9bit 512

#define WRITE_IFAB_VALUE		0x50B1
#define IFAB_VALUE 0x000D
/* Functionality mode */
#define REFERESH_ANGLE		0





extern void TLE5012B_Configuration(void);
extern void TLE5012B_Server(void);
void MOTORT(void);
void USART_Server(void);

void hw_configuration(void);
void Seg_Configuration(void);
void COMM_Configuration(void);



unsigned short ReadAngle(void);
unsigned short ReadSpeed(void);
unsigned short ReadValue(unsigned short u16RegValue);
unsigned short SPIx_ReadWriteByte(unsigned short byte);
void SPI5012B_Init(void);
void displaycount(unsigned long count);


void MCW(void);
void MCCW(void);
void MSTP(void);
	
#endif
