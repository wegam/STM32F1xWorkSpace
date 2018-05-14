#ifndef __PD010V20_H
#define __PD010V20_H

#include	"stdio.h"			//用于printf
#include	"string.h"		//用于printf
#include	"stdarg.h"		//用于获取不确定个数的参数
#include	"stdlib.h"		//malloc动态申请内存空间




#include "STM32_SYS.H"
#include "STM32_SYSTICK.H"
#include "STM32F10x_BitBand.H"

#include "STM32_GPIO.H"
#include "STM32_PWM.H"
#include "STM32_USART.H"
#include "STM32_CAN.H"
#include "STM32_WDG.H"

#include "MOTOR.H"
#include "74HC165.H"
#include "CD4511.H"
#include "SWITCHID.H"		//拔码开关



#define	USARTBufferSize	64

typedef struct	_Sensor
{
	//____________Sensor1
	GPIO_TypeDef* 	Sen1_PORT;				//GPIOX
	unsigned short 	Sen1_Pin;					//GPIO_Pin_x
	//____________Sensor2
	GPIO_TypeDef* 	Sen2_PORT;				//GPIOX
	unsigned short 	Sen2_Pin;					//GPIO_Pin_x
	//____________Sensor3
	GPIO_TypeDef* 	Sen3_PORT;				//GPIOX
	unsigned short 	Sen3_Pin;					//GPIO_Pin_x
	//____________Sensor4
	GPIO_TypeDef* 	Sen4_PORT;				//GPIOX
	unsigned short 	Sen4_Pin;					//GPIO_Pin_x
	//____________Sensor5
	GPIO_TypeDef* 	Sen5_PORT;				//GPIOX
	unsigned short 	Sen5_Pin;					//GPIO_Pin_x
	//____________Sensor6
	GPIO_TypeDef* 	Sen6_PORT;				//GPIOX
	unsigned short 	Sen6_Pin;					//GPIO_Pin_x
	//____________Sensor7
	GPIO_TypeDef* 	Sen7_PORT;				//GPIOX
	unsigned short 	Sen7_Pin;					//GPIO_Pin_x
	//____________Sensor8
	GPIO_TypeDef* 	Sen8_PORT;				//GPIOX
	unsigned short 	Sen8_Pin;					//GPIO_Pin_x
	
	unsigned char		Num;							//接的拔码开关位数,最大16位:配置时需要填入所接的拔码开关位数
	unsigned long		Time;
	
}SensorDef;

typedef struct	_Pmos
{
	//____________Sensor1
	GPIO_TypeDef* 	P1_PORT;				//GPIOX
	unsigned short 	P1_Pin;					//GPIO_Pin_x
	//____________Sensor2
	GPIO_TypeDef* 	P2_PORT;				//GPIOX
	unsigned short 	P2_Pin;					//GPIO_Pin_x
	//____________Sensor3
	GPIO_TypeDef* 	P3_PORT;				//GPIOX
	unsigned short 	P3_Pin;					//GPIO_Pin_x
	//____________Sensor4
	GPIO_TypeDef* 	P4_PORT;				//GPIOX
	unsigned short 	P4_Pin;					//GPIO_Pin_x
	
	unsigned char		Num;						//接的PMOS个数
	unsigned long		Time;
	
}PmosDef;

typedef struct	_Motor
{
	//____________Sensor2
	GPIO_TypeDef* 	DIR_PORT;				//GPIOX
	unsigned short 	DIR_Pin;					//GPIO_Pin_x
	//____________Sensor1
	GPIO_TypeDef* 	PUL_PORT;				//GPIOX
	unsigned short 	PUL_Pin;					//GPIO_Pin_x	
	//____________Sensor3
	GPIO_TypeDef* 	EN_PORT;				//GPIOX
	unsigned short 	EN_Pin;					//GPIO_Pin_x

	unsigned long		Time;
	
}MotorDef;

typedef struct	_RS485
{
	//____________Buffer
	unsigned char 	RxdBuffer[USARTBufferSize];				//DMA接收缓存
	unsigned char 	RevBuffer[USARTBufferSize];				//数据处理缓存
	unsigned char 	TxdBuffer[USARTBufferSize];				//DMA发送缓存	
	
	unsigned long		BaudRate;
	unsigned long		Time;
	RS485_TypeDef		RS485Cof;	
}RS485Def;

typedef struct	_RS232
{
	//____________Buffer
	unsigned char 	RxdBuffer[USARTBufferSize];				//DMA接收缓存
	unsigned char 	RevBuffer[USARTBufferSize];				//数据处理缓存
	unsigned char 	TxdBuffer[USARTBufferSize];				//DMA发送缓存	
	
	unsigned long		BaudRate;
	unsigned long		Time;
	
	USART_TypeDef* USARTx;
}RS232Def;

typedef struct	_CANBUS
{
	//____________Buffer
	CanRxMsg RxMessage;
	CanTxMsg TxMessage;
	
	unsigned long		BaudRate;
	unsigned long		Time;
}CANBUSDef;

typedef struct	_Sys
{
	unsigned short	SwitchID;
	unsigned long		SysTime;
}SysDef;

typedef	struct _Board
{
	SensorDef			Sensor;
	SWITCHID_CONF Switch;
	PmosDef				Pmos;
	MotorDef			Motor1;
	MotorDef			Motor2;
	RS485Def			RS485A;
	RS485Def			RS485B;
	RS232Def			RS232A;
	RS232Def			RS232B;
	CANBUSDef			CANBUS;
	SysDef				Sys;
}BoardDef;


#endif

