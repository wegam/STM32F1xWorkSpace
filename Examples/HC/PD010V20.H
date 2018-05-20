#ifndef __PD010V20_H
#define __PD010V20_H

#include	"stdio.h"			//����printf
#include	"string.h"		//����printf
#include	"stdarg.h"		//���ڻ�ȡ��ȷ�������Ĳ���
#include	"stdlib.h"		//malloc��̬�����ڴ�ռ�




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
#include "SWITCHID.H"		//���뿪��


#include "STM32_SPI.H"
#include "MX25L4006E.H"




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
	
	unsigned char		Num;							//�ӵİ��뿪��λ��,���16λ:����ʱ��Ҫ�������ӵİ��뿪��λ��
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
	
	unsigned char		Num;						//�ӵ�PMOS����
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
	unsigned char 	RxdBuffer[USARTBufferSize];				//DMA���ջ���
	unsigned char 	RevBuffer[USARTBufferSize];				//���ݴ�������
	unsigned char 	TxdBuffer[USARTBufferSize];				//DMA���ͻ���	
	
	unsigned long		BaudRate;
	unsigned long		Time;
	RS485_TypeDef		RS485Cof;	
}RS485Def;

typedef struct	_RS232
{
	//____________Buffer
	unsigned char 	RxdBuffer[USARTBufferSize];				//DMA���ջ���
	unsigned char 	RevBuffer[USARTBufferSize];				//���ݴ�������
	unsigned char 	TxdBuffer[USARTBufferSize];				//DMA���ͻ���	
	
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

typedef struct	_Board
{
	unsigned short	SwitchID;
	unsigned short	Data;
	unsigned long		SysTime;
}BoardDef;

typedef	struct _PD010
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
	MX25L4006EDef	MX25Lx;
	BoardDef			Board;
}PD010Def;


void PD010V20_Configuration(void);
void PD010V20_Server(void);


void Sensor_Configuration(void);
void Switch_Configuration(void);
void Pmos_Configuration(void);
void Motor_Configuration(void);
void RS485_Configuration(void);
void RS232_Configuration(void);
void CAN_Configuration(void);
void FLASH_Configuration(void);

void Sensor_Server(void);
void Switch_Server(void);
void Pmos_Server(void);
void Motor_Server(void);
void RS485_Server(void);
void RS232_Server(void);
void CAN_Server(void);
void FLASH_Server(void);
#endif
