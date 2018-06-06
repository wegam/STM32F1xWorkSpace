#ifndef __PD002V30_H
#define __PD002V30_H


#include "STM32_USART.H"
#include "AT24C02.H"
#include "PD002V30.H"
#include "CS5530.H"
#include "74HC595.H"
#include "SWITCHID.H"



enum
{
	head1	=	0xFA,
	head2	=	0xF5
};
typedef	enum _PD002V30Cmd
{
	APP_CMD_Null						=	0x00,	/*无命令*/
	APP_CMD_CTFAYAO					=	0x21,	/*称重抽屉发药*/
	APP_CMD_CTPANDIAN				=	0x22,	/*称重抽屉盘点*/
	APP_CMD_CTJIAYAO				=	0x23,	/*称重抽屉加药*/
	APP_CMD_CTCLEAR					=	0x25,	/*称重抽屉清零*/
	APP_CMD_CTBIAODINGS1		=	0x26,	/*称重抽屉标定步骤1:放入一定数量的药品*/
	APP_CMD_CTBIAODINGS2		=	0x27,	/*称重抽屉标定步骤2:输入数量--标定*/
	APP_CMD_CTHUISHOUFLICK	=	0x2A,	/*弹开回收抽屉*/
	APP_CMD_CTFORCEPOPUP		=	0x2B,	/*称重抽屉强制弹出*/
	APP_CMD_CTHUISHOUCOUNT	=	0x2C,	/*回收空药瓶计数*/
	APP_CMD_CTHUISHOUCLEAR	=	0x2D	/*回收空药瓶清空*/
}PD002V30CmdDef;
typedef enum _WorkStatebac 
{
	SYS_IDLE=0,									/*空闲状态*/
	SYS_ORIGIN_TRACK_REQ,				/*请求跟踪原点*/
	SYS_ORIGIN_TRACK_WAIT,			/*等待跟踪原点*/
	SYS_ORIGIN_TRACK_EXE,				/*执行跟踪原点*/
	SYS_ORIGIN_TRACK_OPEN_SUS,	/*抽屉打开,跟踪原点挂起*/
	SYS_ORIGIN_TRACK_OPEN_REQ,	/*请求开抽屉跟踪一次原点*/
	SYS_ORIGIN_TRACK_OPEN_EXE,	/*执行开抽屉跟踪一次原点*/
	SYS_GET_QUANTITY_REQ,				/*得到数量请求*/
	SYS_GET_QUANTITY_OTINQ,			/*得到数量是否超时查询*/
	SYS_GET_QUANTITY_EXE_OT,		/*得到数量+查询是否超时*/
	SYS_GET_QUANTITY_EXE,				/*得到数量*/
	SYS_DEMAR_REQ,							/*标定请求*/
	SYS_DEMAR_OTINQ,						/*标定执行是否超时查询*/
	SYS_DEMAR_EXE_OT,						/*标定执行+查询是否超时*/
	SYS_DEMAR_EXE,							/*标定执行*/
	SYS_SENSOR_ERROR_SUS				/*传感器被挂起在错误状态*/
} WorkStatebacDef;
typedef enum _WorkRequst
{
	RequstIdle=0,					/*无数据请求*/
	RequstBackupData,			/*请求备份操作前AD值*/
	RequstNewData,				/*请求备份操作后AD值*/
	RequstQuantity,				/*请求获取数量*/	
	RequstPiece,					/*请求获取单重AD值*/
} WorkRequstDef;
typedef enum _WorkState 
{
	StateIdle=0,								/*空闲状态*/
	StateSuspend,								/*不执行采样操作*/
	StateGetFiltDataReq,				/*请求获取滤波AD值*/
	StateGetFiltDataWait,				/*等待获取滤波AD值*/
	StateGetFiltDataExe,				/*执行获取滤波AD值*/	
	
	StateProcessDataExe,				/*执行计算*/
	
	StateReadI2CDataReq,				/*请求获取备份EEPROM数值*/
	StateSaveI2CDataReq,				/*请求保存备份EEPROM数值*/
	StateClearI2CDataReq,				/*请求清除备份EEPROM数值*/
	
//	StateGetNewDataReq,					/*请求获取操作后AD值*/
//	StateGetNewDataWait,				/*等待获取操作后AD值*/
//	StateGetNewDataExe,					/*执行获取操作后AD值*/
//	
//	StateGetNewNumReq,					/*请求获取数量*/
//	StateGetNewNumWait,					/*等待获取数量**/
//	StateGetNewNumExe,					/*执行获取数量**/	
//	
//	StateGetPieceDataReq,				/*请求获取单重AD值*/
	
} WorkStateDef;
typedef	struct
{
	unsigned short RunningTime;		//计时器
	unsigned char	 StartAddr;			//数据存储起始地址
	struct
	{
		unsigned short	Quantity;			//数量
		unsigned short	PieceWeight;	//单重
	}CH1;	//通道1
	struct
	{
		unsigned short	Quantity;			//数量
		unsigned short	PieceWeight;	//单重
	}CH2;	//通道2
	
	sI2CDef 			Port;
}AT24C02Def;
typedef	struct	_MS200Pro
{
	struct
	{
		unsigned char h1;
		unsigned char h2;
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
}MS200ProCCDef;
typedef	struct	_PD002V30RS485Pro
{
	struct
	{
		unsigned char Time;
		unsigned char Retry;
	}Data;
	MS200ProCCDef	Pro;
}RS485ProCCDef;

typedef	struct _PD002V30Data
{
	unsigned short	Time;					//计时器
	unsigned short	Retry;				//采样重试计数
	unsigned short	Quantity;			//数量
	unsigned short	WeightPiece;	//单重
	unsigned long		WeightBackUp;	//操作前备份AD值
	unsigned long		WeightNew;		//操作后新AD值
}PD002V30DataDef;
typedef	struct _PD002V30CH
{
	PD002V30DataDef	Data;					//数据
	WorkStateDef		WorkState;		//工作状态
	WorkRequstDef		WorkRequst;		//请求类型
	CS5530Def 			ADC;					//ADC：包包含接口，数据
	RS485ProCCDef		RS485Rx;			//485接收缓存
	RS485ProCCDef		RS485Bc;			//485接收备份缓存
	RS485ProCCDef		RS485Tx;			//485发送缓存
}PD002V30CHDef;
typedef	struct _PD002V30
{
	PD002V30CHDef	CH1SS3;			//通道1，SS3接口，里面
	PD002V30CHDef	CH2SS4;			//通道2，SS4接口，外面
	MS200ProCCDef	Ack;
	AT24C02Def		AT24C02;		//EEPROM
	RS485_TypeDef BUS485;			//485
	SWITCHID_CONF	SWITCHID;
}PD002V30Def;


















void PD002V30_Configuration(void);

void PD002V30_Server(void);

void PD002V30_USART_Cofiguration(void);
void PD002V30_USART_Server(void);
void PD002V30_RS485_Server(void);	//RS485服务程序
void PD002V30_RS485_Recv(void);		//RS485接收
void PD002V30_RS485_Send(void);		//RS485发送
void PD002V30_Pro_Packet(MS200ProCCDef	*Pro);	//协议打包


void PD002V30_CMD_Server(void);		//命令处理
void PD002V30_WORK_Server(void);	//状态处理
	
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

