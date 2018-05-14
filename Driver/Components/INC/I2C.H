#ifndef __I2C_H
#define __I2C_H

#include "stdint.h"

#include "stm32f10x_gpio.h"


//#include "STM32_GPIO.H"




typedef	struct	_I2C				//带反馈锁控制标志及吸合时间
{
	//-------------------------锁驱动
	GPIO_TypeDef*	SDA_Port;
	u16	SDA_Pin;
	//-------------------------锁反馈
	GPIO_TypeDef*	SCL_Port;
	u16	SCL_Pin;
}sI2CDef;



void I2C_Configuration(sI2CDef *sI2C);		//启用锁--配置
void I2C_Server(sI2CDef *sI2C);

void I2C_Start(sI2CDef *sI2C);




void I2C_Delay(void);
void I2C_SCLHigh(sI2CDef *sI2C);
void I2C_SCLLow(sI2CDef *sI2C);
void I2C_SDAHigh(sI2CDef *sI2C);
void I2C_SDALow(sI2CDef *sI2C);
void I2C_SDASetOut(sI2CDef *sI2C);
void I2C_SDASetIn(sI2CDef *sI2C);

unsigned char I2C_WaitAck(sI2CDef *sI2C);		//CPU产生一个时钟，并且读取器件的ACK应答信号
void I2C_Ack(sI2CDef *sI2C);								//CPU产生一个ACK信号 
void I2C_NAck(sI2CDef *sI2C);								//CPU产生一个NACK信号(NACK即无应答信号) 
unsigned char I2C_ReadBit(sI2CDef *sI2C);


void I2C_Start(sI2CDef *sI2C);
void I2C_Stop(sI2CDef *sI2C);

void I2C_SendByte(sI2CDef *sI2C,unsigned char ucByte);	//向I2C总线设备发送8bits的数据 ,首先传输的是数据的最高位（MSB） 
unsigned char I2C_ReadByte(sI2CDef *sI2C);							//从I2C总线读取8个bits的数据  ,首先读出的是数据的最高位（MSB）


#endif

