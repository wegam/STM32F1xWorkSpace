#ifndef __PC004V31HC_H
#define __PC004V31HC_H

#include "stm32f10x_type.h"
#include "HC_PHY.H"

//#define	RS485MaxDataSize	64			//RS485总线最大数据长度
//#define	Rs232MaxDataSize	64			//RS232最大数据长度

//=============================RS485A总线端口(与上层/单元板通讯接口)

	#define	RS485BusDataSize		64			//RS485总线最大数据长度
	#define	RS485BusBaudRate		19200
	#define	RS485BusSerialPort	USART2
	#define	RS485BusCtlPort			GPIOA
	#define	RS485BusCtlPin			GPIO_Pin_1
	//=============================RS485B总线端口(与下层/层板通讯接口)
	#define	RS485layDataSize		64			//RS485总线最大数据长度
	#define	RS485layBaudRate		19200
	#define	RS485laySerialPort	UART4
	#define	RS485layCtlPort			GPIOC
	#define	RS485layCtlPin			GPIO_Pin_12
	//=============================RS232A端口
	#define	RS232ADataSize			64			//RS485总线最大数据长度
	#define	RS232ABaudRate			19200
	#define	RS232ASerialPort		USART1

	//=============================RS232A端口
	#define	RS232BDataSize			64			//RS485总线最大数据长度
	#define	RS232BBaudRate			19200
	#define	RS232BSerialPort		USART3

	//=============================CAN.
	#define	CANBaudRate					100000		//100K
	
	//=============================拨码开关端口
	#define NumOfSwitch			8			//拨码位数
	#define	GPIOxSW1		GPIOC
	#define	PinxSW1			GPIO_Pin_0

	#define	GPIOxSW2		GPIOC
	#define	PinxSW2			GPIO_Pin_1

	#define	GPIOxSW3		GPIOC
	#define	PinxSW3			GPIO_Pin_2

	#define	GPIOxSW4		GPIOC
	#define	PinxSW4			GPIO_Pin_3

	#define	GPIOxSW5		GPIOC
	#define	PinxSW5			GPIO_Pin_4

	#define	GPIOxSW6		GPIOC
	#define	PinxSW6			GPIO_Pin_5

	#define	GPIOxSW7		GPIOC
	#define	PinxSW7			GPIO_Pin_6

	#define	GPIOxSW8		GPIOC
	#define	PinxSW8			GPIO_Pin_7
	
	//=============================锁及锁信号检测
	#define	Lock1DrPort		GPIOB					//锁控制端口
	#define	Lock1DrPin		GPIO_Pin_13		//锁控制管脚
	#define	Lock1SiPort		GPIOB					//锁控制端口
	#define	Lock1SiPin		GPIO_Pin_14		//锁控制管脚

	#define	Lock2DrPort		GPIOB					//锁控制端口
	#define	Lock2DrPin		GPIO_Pin_0		//锁控制管脚
	#define	Lock2SiPort		GPIOB					//锁控制端口
	#define	Lock2SiPin		GPIO_Pin_1		//锁控制管脚

	#define	Lock3DrPort		GPIOA					//锁控制端口
	#define	Lock3DrPin		GPIO_Pin_6		//锁控制管脚
	#define	Lock3SiPort		GPIOA					//锁控制端口
	#define	Lock3SiPin		GPIO_Pin_7		//锁控制管脚

	#define	Lock4DrPort		GPIOA					//锁控制端口
	#define	Lock4DrPin		GPIO_Pin_4		//锁控制管脚
	#define	Lock4SiPort		GPIOA					//锁控制端口
	#define	Lock4SiPin		GPIO_Pin_5		//锁控制管脚



void PC004V31HC_Configuration(void);
void PC004V31HC_Server(void);

void AMPTEST(void);


void Communiction_Configuration(void);			//通讯接口配置：包含RS485,RS232,CAN
void Switch_Configuration(void);						//拨码开关配置
void Lock_Configuration(void);							//锁端口配置



#endif

