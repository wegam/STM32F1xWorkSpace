#ifndef __PD002V30_H
#define __PD002V30_H


#include "STM32_USART.H"
#include "AT24C02.H"
#include "PD002V30.H"
#include "CS5530.H"
#include "74HC595.H"


typedef	enum _PD002V30Cmd
{
	APP_CMD_Null						=	0x00,	/*无命令*/
	APP_CMD_CTFAYAO					=	0x21,	/*称重抽屉发药*/
	APP_CMD_CTPANDIAN				=	0x22,	/*称重抽屉盘点*/
	APP_CMD_CTJIAYAO				=	0x23,	/*称重抽屉加药*/
	APP_CMD_CTCLEAR					=	0x25,	/*称重抽屉清零*/
	APP_CMD_CTBIAODINGS1		=	0x26,	/*称重抽屉标定步骤1:放入一定数量的药品*/
	APP_CMD_CTBIAODINGS2		=	0x27,	/*称重抽屉标定步骤2:输入数量*/
	APP_CMD_CTHUISHOUFLICK	=	0x2A,	/*弹开回收抽屉*/
	APP_CMD_CTFORCEPOPUP		=	0x2B,	/*称重抽屉强制弹出*/
	APP_CMD_CTHUISHOUCOUNT	=	0x2C,	/*回收空药瓶计数*/
	APP_CMD_CTHUISHOUCLEAR	=	0x2D	/*回收空药瓶清空*/
}PD002V30CmdDef;

typedef	struct
{
	unsigned short RunningTime;		//计时器
	unsigned char	 StartAddr;			//数据存储起始地址
	struct
	{
		unsigned short	Quantity;			//数量
		unsigned short	PieceWeight;		//单重
	}CH1;	//通道1
	struct
	{
		unsigned short	Quantity;			//数量
		unsigned short	PieceWeight;		//单重
	}CH2;	//通道2
	
	sI2CDef 			Port;
}AT24C02Def;
typedef	struct	_PD002V30RS485Pro
{
	struct
	{
		unsigned char head1;
		unsigned char head2;
	}Head;
	unsigned char		SerialNumber;	//流水号
	unsigned char		Receipt;			//回执位
	unsigned char		Number;				//编号
	unsigned char		Address;			//位置	//取低4位
	PD002V30CmdDef	Cmd;					//命令
	unsigned char		Data;					//数据
	unsigned char		Reserve;			//保留位
	unsigned char		State;				//运行状态位
	unsigned char		ErrFlag;			//错误码
	unsigned char		Bcc8;					//异或校验(流水号到错误码）
}PD002V30RS485ProCCDef;
typedef	struct _PD002V30
{
	CS5530Def 	ADCSS3CH1;		//SS3接口，外面
	CS5530Def 	ADCSS4CH2;		//SS4接口，里面
	AT24C02Def	I2C;
	PD002V30RS485ProCCDef	RS485Data;
}PD002V30Def;






void PD002V30_Configuration(void);

void PD002V30_Server(void);

void PD002V30_USART_Cofiguration(void);
void PD002V30_USART_Server(void);
void PD002V30_RS485_Server(void);
void PD002V30_RS485_Ack(PD002V30RS485ProCCDef *RS485Data);
void PD002V30_CMD_Server(void);

void AT24C02_Configuration(void);
void AT24C02_SaveData(void);		//保存数据,一页一通道，前4字节存数量，后4字节存单重
void AT24C02_ReadData(void);		//读数据,一页一通道，前4字节存数量，后4字节存单重
	
void SwitchID_Configuration(void);

unsigned char PD002V30_GetSwitchID(void);				//获取拔码开关地址
unsigned char PD002V30_GetBufferArray(void);		//获取各抽屉的AD值

void CS5530_Configuration(void);		//CS5530初始化
void CS5530_Server(void);				//读取AD值
	
void Seg_Configuration(void);		//数码管接口配置
void Seg_Server(void);					//数码更新接口

#endif

