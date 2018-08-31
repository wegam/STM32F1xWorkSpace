#ifndef __PM001V20HC_H
#define __PM001V20HC_H



typedef enum _ErrCode
{
	GBL_FAULT_NON							=	0x00,	//无错误
	GBL_FAULT_BUSY						=	0x01,	//忙状态
	GBL_FAULT_ILLAGALPARA			=	0x02,	//参数非法
	GBL_FAULT_INACTIVE				=	0x03,	//称重通道未激活
	GBL_FAULT_DIRECTION				=	0x04,	//传感器方向错
	GBL_FAULT_DIFFOVF					=	0x05,	//称重差值过大
	GBL_FAULT_SENSOR					=	0x06,	//传感器故障
	GBL_FAULT_ILLIGALWEIGHT		=	0x07,	//称重数值非法
	GBL_FAULT_WEIGHTOVF				=	0x08,	//称重数据溢出
	GBL_FAULT_NOCALI					=	0x09	//称重未标定
}ErrDef;			//错误码
typedef enum _CmdCode
{
	CMD_WRITE_QTY							=	0x01,	//写入数量
	CMD_UNLOCK								=	0x02,	//解锁
	CMD_ADD_MTRL							=	0x04,	//加料
	CMD_RDC_MTRL							=	0x06,	//取料
	CMD_CHECK_QTY							=	0x07,	//盘点
	CMD_WRITE_HINT						=	0x08,	//写入提示
	CMD_WRITE_NOTE						=	0x09,	//写入注释
	CMD_CNTRL_LED							=	0x0A,	//提示灯控制 ，该指令由单元板执行
	CMD_CNTRL_GATE						=	0x0B,	//冰箱门控制 ，该指令由网关执行，不往下层传递
	CMD_CHECK_VERSION					=	0x0C	//查询软件版本
}CmdDef;			//命令码
typedef enum _FrameType
{
	FRAME_TYPE_DATA						=	0x01,		//帧类型--数据帧
	FRAME_TYPE_ACK						=	0x02,		//帧类型--应答帧
	FRAME_TYPE_INVALID				=	0x00		//帧类型--无效帧
}FrameTypeDef;	//帧类型
typedef enum _OrderState
{
	ORDER_STAT_IDLE						=	0,			//空闲状态
	ORDER_STAT_WORK						=	1				//工作状态--忙状态
}OrderStateDef;	//工作状态


typedef struct	_RS232RceFram
{
	unsigned short 	FarmLen;
	unsigned char		Data[];
}RS232RceFramDef;		//232接收帧格式(PC机通讯)
























void PM001V20HC_Configuration(void);
void PM001V20HC_Server(void);
void PM001V20_SysLed(void);			//系统运行指示灯
void USART_Configuration(void);
void Driver_Configuration(void);
void USART_Server(void);
void Driver_Server(void);
void CAN_Server(void);


#endif

