#ifndef __I2C_H
#define __I2C_H

#include "stdint.h"

#include "stm32f10x_gpio.h"


//#include "STM32_GPIO.H"

typedef	enum	_I2CACK				//带反馈锁控制标志及吸合时间
{
	I2C_NACK	=0,
	I2C_ACK		=1
}I2CACKDef;

//EEPROM类型24C01、24C02这两个型号是8个字节一个页，而24C04、24C08、24C16是16个字节一页
typedef	enum	_EEtype				//带反馈锁控制标志及吸合时间
{
	AT24C01	=0,		//1K位 	(128 x 8)	/128字节	/页大小：8字节		/页个数：16
	AT24C02,			//2K位 	(256 x 8)	/256字节	/页大小：8字节		/页个数：32
	AT24C04,			//4K位 	(512 x 8)	/512字节	/页大小：16字节	/页个数：32
	AT24C08,			//8K位 	(1024 x 8)/1024字节	/页大小：16字节	/页个数：64
	AT24C16				//16K位 (2048 x 8)/2048字节	/页大小：16字节	/页个数：128
}EEtypeDef;

typedef	struct	_I2CHW				//带反馈锁控制标志及吸合时间
{
	//-------------------------SDA驱动
	GPIO_TypeDef*	SDA_Port;
	u16	SDA_Pin;
	//-------------------------SCL驱动
	GPIO_TypeDef*	SCL_Port;
	u16	SCL_Pin;
}sI2CHWDef;
typedef	struct	_I2CDATA				//带反馈锁控制标志及吸合时间
{
	EEtypeDef	EEtype;			//EEPROM类型24C01、24C02这两个型号是8个字节一个页，而24C04、24C08、24C16是16个字节一页
	unsigned char  PageSize;		//页大小：一页包含的字节数
	unsigned short WPageStart;	//开始写入的页地址
	unsigned short WPageAddr;		//当前写入的页地址
	unsigned short WDataTotal;	//需要写入的数据总数
	unsigned short WDataSize;		//剩余待写入的数据个数
	unsigned char  DeviceAddr;	//设备地址：bit0=0:write;bit0=1:read
	unsigned char* WDataAddr;		//待写入的数据起始地址
}sI2CDATADef;
typedef	struct	_I2C				//带反馈锁控制标志及吸合时间
{
	//-------------------------硬件驱动
	sI2CHWDef HW;
	//-------------------------参数
	sI2CDATADef	DATA;
	
}sI2CDef;



void I2C_Configuration(sI2CDef *sI2C);		//启用锁--配置
void I2C_Server(sI2CDef *sI2C);

void I2C_Start(sI2CDef *sI2C);





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

void I2C_SendByte(sI2CDef *sI2C,unsigned char ucByte);
void I2C_WriteOneByte(sI2CDef *sI2C,unsigned short address,unsigned char ucByte);	//向I2C总线设备发送8bits的数据 ,首先传输的是数据的最高位（MSB）
void I2C_WritePage(sI2CDef *sI2C,unsigned short PageAddress,const unsigned char* pBuffer);		//页写：
void I2C_WriteNbyte(sI2CDef *sI2C,unsigned short address,const unsigned char* pBuffer,unsigned short length);
void I2C_WriteBuffer(sI2CDef *sI2C,unsigned short address,const unsigned char* pBuffer,unsigned short length);	//向I2C总线设备发送8bits的数据 ,首先传输的是数据的最高位（MSB）

unsigned char I2C_ReadByte(sI2CDef *sI2C);
unsigned char I2C_ReadOneByte(sI2CDef *sI2C,unsigned short address);							//从I2C总线读取8个bits的数据  ,首先读出的是数据的最高位（MSB）
unsigned short I2C_ReadPage(sI2CDef *sI2C,unsigned short PageAddress,unsigned char* pBuffer);
unsigned short I2C_ReadBuffer(sI2CDef *sI2C,unsigned short address,unsigned char* pBuffer,unsigned short length);




void I2C_Delayus(unsigned	short Time);
void I2C_Delayms(unsigned	short Time);
#endif

