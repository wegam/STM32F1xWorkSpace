#ifndef __PC016V20_H
#define __PC016V20_H


#include "stm32f10x_exti.h"

#include "CardReader.H"			//读卡器

//#include "STM32_TOOLS.H"		//异或校验工具
#include "SWITCHID.H"
#include "STM32_CRC.H"
#include "STM32_USART.H"
#include "STM32_SPI.H"
#include "STM32_PWM.H"
#include "STM32_GPIO.H"
#include "STM32_SYS.H"
#include "STM32_WDG.H"
#include "STM32_SYSTICK.H"
#include "STM32F10x_BitBand.H"


#include	"stdio.h"			//用于printf
#include	"string.h"		//用于printf
#include	"stdarg.h"		//用于获取不确定个数的参数
#include	"stdlib.h"		//malloc动态申请内存空间

#define	MinPortNum		1			//最小/起始端口号 1~4
#define	MaxPortNum		4			//最大端口号 1~4
#define	MaxSysTime		1000	//TimeSYS最大计时时间，单位ms，到达最大计时时间后，所有计时器清零

//==============端口---读卡器
#define	ICCardReadPort1					USART3		//J1
#define	ICCardReadPort2					USART1		//J2
#define	ICCardReadPort3					UART4			//J3
#define	ICCardReadPort4					UART5			//J4---不支持DMA传输
#define	ICCardReadBaudRate			19200
#define	CardDataSize						50				//接收到IC读卡器完整数据大小（协议+数据共22byte）备用10byte
#define	ICDataStartByte					2					//16字节数据中有效卡号起始位 0~15
#define	ICDataNum								3					//16字节数据中有效卡号字节数

#define	CardStartByte						0					//16字节数据中有效卡号起始位 0~15
#define	CardLength							4					//16字节数据中有效卡号字节数

//==============复用端口

//==============端口---总线485
#define	Bus485Port				USART2
#define	Bus485CtlPort			GPIOA
#define	Bus485CtlPin			GPIO_Pin_1
#define	Bus485BaudRate		19200											//波特率
#define	BusDataSize				64												//一条消息携带的最大数据个数
#define	Bus485BufferSize	80												//一条消息的最大缓存大小（协议数据+数据）
#define	CommProtocolLenth		11											//标准协议部分数据长度//sizeof(sCommHeadDef)+sizeof(sCommStartDef)+sizeof(sCommAddrDef)+sizeof(eCommErrorCodeDef)
#define	CommBasicLenth			4												//数据长度nLength中地址和状态码的长度
#define	FixedAddrLenth			4												//固定数据长度nLength中地址和状态码的长度
#define	FixedDataLenth			3												//固定数据长度-----卡号数据

//==============端口---数码管485
#define	Seg485PortRmap		USART1		//端口重定义
#define	Seg485CtlPort			GPIOB
#define	Seg485CtlPin			GPIO_Pin_5
#define	Seg485BaudRate		19200
#define	Seg485BufferSize	22
//==============端口---锁
#define	LockPort(n)		LockPort##n
#define	LockPin(n)		LockPin##n
#define	LockOn(n)			GPIO_SetBits(LockPort(n),	LockPin(n))			//开锁
#define	LockOff(n)		GPIO_ResetBits(LockPort(n),	LockPin(n))		//释放锁

#define	LockPort1			GPIOC
#define	LockPin1			GPIO_Pin_3
#define	LockPort2			GPIOB
#define	LockPin2			GPIO_Pin_9
#define	LockPort3			GPIOB
#define	LockPin3			GPIO_Pin_3
#define	LockPort4			GPIOB
#define	LockPin4			GPIO_Pin_4


#define	DefaultOnTime	20000				//默认锁吸合时间20S
#define	MaxOnTime			120000			//锁吸合最大时间120S	2分钟
#define	MinOnTime			20000				//锁吸合最小时间10S	
#define	LockOffTime		5000				//药箱取走后锁释放时间5S
#define	SegOnTime			60000				//插入药箱后数码管常亮时间60S

#define	PowerT				6000				//上电时间	

#define	Pt(n)	GPIO_SetBits(LockPort(n),	LockPin(n))

//u8 ICCARD_CMD_GetDataBlock1[] =
//{
//	0xE1,   /* F-Head 	*/			//为帧头，上位机下发时固定为0XE1，下位机应答时固定为0XD2；
//	0x24,  	/* CmdType 	*/			//命令类型
//	0x01,		/* Sector 	*/			//1字节扇区号
//	0x01,   /* Block 		*/			//1字节块号
//	0x60,   /* KeyType	*/			//1字节密钥模式 KEYA（0x60）/KEYB(0x61)
//	0xFF,   /* PassWord0 */			//6字节密码
//	0xFF,   /* PassWord1 */
//	0xFF,   /* PassWord2 */
//	0xFF,		/* PassWord3 */
//	0xFF,   /* PassWord4 */
//	0xFF,		/* PassWord5 */
//	0x1C,   /* Crc16-HIGN */
//	0x0D,		/* Crc16-LOW */
//	0x1E   	/* F-End*/						//为帧尾，上位机下发时固定为0X1E，下位机应答时固定为0X2D；
//};
//============================================================================================通讯协议Start
//***************485总线通讯（病区柜）
//-----------------------------------------------------------------------------------枚举类
typedef enum	_ePro485Us			//485协议头尾标识符
{
	ePro485Head			=	0x7E,			//头标识
	ePro485End			=	0x7F,			//结束标识
}ePro485UsDef;
//typedef enum	_ePro485Cmd			//命令类(包含下行命令和上行命令
//{
//	eGetID	=	0x92,							//上位机主动获取ID请求应答命令
//	eSendID	=	0x93,							//下位机主动上传ID号命令
//	eLock		=	0x93,							//锁控制命令上报
//	eGetBox	=	0x93,							//取药命令上报
//}ePro485CmdDef;
//typedef enum	_ePro485Ack			//命令类(包含下行命令和上行命令
//{
//	eGetID	=	0x92,							//上位机主动获取ID请求应答命令
//	eSendID	=	0x93,							//下位机主动上传ID号命令
//	eLock		=	0x93,							//锁控制命令上报
//	eGetBox	=	0x93,							//取药命令上报
//}ePro485AckDef;
typedef enum	_ePro485Com			//命令类(包含下行命令和上行命令
{
		//===============上位机下发命令
		CGetID	=	0x12,							//上位机主动获取ID请求应答命令
		CGetBox	=	0x13,							//取药命令上报
		
		//===============下位机上报命令
		AGetID	=	0x92,							//上位机主动获取ID请求应答命令
		ASendID	=	0x93,							//下位机主动上传ID号命令
		ALock		=	0x93,							//锁控制命令上报
		AGetBox	=	0x93,							//取药命令上报

}ePro485ComDef;
typedef enum	_ePro485Sts			//状态码
{
	eNoErr		=	0x00,		//无错误
	eNoData		=	0x23,		//无药箱数据
	eBoxTout	=	0x24,		//取药箱超时
	eBoxOff		=	0x25,		//药箱取走
	eBoxBack	=	0x26,		//药箱取走后收回
	eReadErr	=	0x27,		//读卡器通讯异常
	eBoxTake	=	0x25,		//药箱被强制取走,原28
}ePro485StsDef;
//-----------------------------------------------------------------------------------结构体
typedef	struct	_sPro485Addr			//通讯地址结构体（下行时：Addr1,Addr2,Addr3都得有数据，上行时，柜地址为0x00）
{
	u8 	Addr1;		//柜地址(单元柜号)  下行时为柜地址，上行时，柜地址为0x00）
	u8 	Addr2;		//层地址
	u8	Addr3;		//槽地址（端口号）	
}sPro485AddrDef;
typedef	struct	_sMs485Farme			//485通讯消息帧结构体MessageFarme  
{
	ePro485UsDef		Head;				//b0识别符	0x7E
	u8							dAdd;				//b1目标地址（暂时理解为单元柜地址）下发为接收地址，上传为0x00
	u8							sAdd;				//b2源地址 下发为0x00，上传为本地址
	u8							nSerial;		//b3流水号 0x01~0xFF 每次使用后加1
	ePro485ComDef		Cmd;				//b4命令号：0x12-获取指定IC卡号，0x13取药,上报命令也在此位
	u8							Ucode;			//b5用户码：不处理，原样返回
	u8							Length;			//b6地址+异常码固定长度为4，卡数据长度为3	
	sPro485AddrDef	Addr;				//通讯地址结构体	
	ePro485StsDef		StsCode;		//状态码/错误码
	
	u8							data[BusDataSize];		//BusDataSize为最大数据接收缓冲，实际数据大小按照Length-4(4为地址和状态码长度)
	
	u8							Bcc8;				//异或校验	//计算范围为起始段到数据段(dAdd~data[n])到错误码
	ePro485UsDef		End;				//结束符 0x7F
}sMs485FrmDef;
//============================================================================================通讯协议End

//**********************************************************************************************************
//**********************************************************************************************************
//**********************************************************************************************************

//============================================================================================读卡器协议Start
typedef	struct	_ICCRC16
{
	u8 CRC_H;
	u8 CRC_L;
}ICCRC16Def;

typedef	struct	_ICBuffer			//读卡器数据格式
{
	u8 Head;
	u8 CmdType;			//命令类型 0x24为读卡
	u8 ErrCode;			//状态码 读卡时0x00无错误，0x01无卡
	u8 data[16];
	ICCRC16Def CRC16;
	u8 End;
}ICBufferDef;

typedef	struct	_ICReadCmd		//读卡命令格式
{
	u8	Head;						//0xE1,   /* F-Head 	*/			//为帧头，上位机下发时固定为0XE1，下位机应答时固定为0XD2；
	u8	CmdType;				//0x24,  	/* CmdType 	*/			//命令类型
	u8	Sector;					//0x01,		/* Sector 	*/			//1字节扇区号
	u8	Block;					//0x01,   /* Block 		*/			//1字节块号
	u8	KeyType;				//0x60,   /* KeyType	*/			//1字节密钥模式 KEYA（0x60）/KEYB(0x61)
	u8	PassWord[6];		//6字节密码0xFF
	ICCRC16Def	CRC16;
	u8 End;
}ReadCmdDef;
//============================================================================================读卡器协议End



//=======================================================数码管通讯结构体：插入药箱常亮30S；取药箱请求：一定时间内闪烁；无药箱：小数点一直闪烁；读卡通讯故障：小数点常亮
typedef struct _SegCmd
{
	unsigned char DispEnNum	:1;		//bit0显示数值	：	0-不显示，		1-显示
	unsigned char DispEnDp	:1;		//bit1显示点		：	0-不显示，		1-显示
	unsigned char DispMdNum	:1;		//bit2数值模式	：	0-静态显示，	1-0.5S闪烁
	unsigned char DispMdDp	:1;		//bit3点模式		：	0-静态显示，	1-0.5S闪烁
	unsigned char DispTime	:1;		//bit4显示时间	：	0-长亮，			1-在显示时间内根据显示模式显示
} SegCmdDef;
typedef struct _sSegFarme 	//数码管通讯数据格式
{
	unsigned char desAddr;				//目的地址---数码管拔码地址
	unsigned char srcAddr;				/*源地址*/
	unsigned char runningNumber;	/*流水号*/
	SegCmdDef			cmd;						/*命令*/
	unsigned char len;						/*长度*/
	unsigned char data[8];				/*数据,高位在前,data[0~3]为显示内容,data[4~7]为闪烁时间*/ 
} sSegFarmeDef;			//数码管数据结构体
//=======================================================读卡器构体
typedef	struct	_CardReader		//读卡器端口及缓存
{
	struct
	{
		unsigned char ReadFlg		:1;	//bit0：0-无操作,			
		unsigned char ReadData	:1;	//bit1：0-无操作,			1-已发送读卡命令
		unsigned char ReadID		:1;	//bit2：0-无操作,			1-读到ID(需要增加相关数据及标志)		
		unsigned char ReadErr		:1;	//bit3：0-读卡器正常，	1-读卡器通讯异常
		unsigned char NoCard		:1;	//bit5：0-无操作,			1-无卡（无药箱）
		unsigned char Active		:1;	//bit6：0-无操作,			1-发送主动上传
		unsigned char Passive		:1;	//bit7：0-无操作,			1-发送被动上传
	}ReaderSts;										//读卡器状态
	unsigned short 	TimeSpan;			//读卡时间间隔--单位ms
	unsigned short 	TimeCount;		//计时器
	unsigned char 	Retry;							//读卡器重试
	unsigned short 	DataLen;						//读到的数据大小
	unsigned long		CardNumber;					//十进制卡号
	unsigned char 	CardNum[CardLength];	//卡号
	unsigned char 	Rev[CardDataSize];		//读卡器数据接收---备份（卡数据+协议大小为22）
	unsigned char 	Rxd[CardDataSize];		//读卡器数据接收---接收缓冲区（DMA）（卡数据+协议大小为22）
	ICBufferDef			CardBuffer;						//卡数据
	USART_TypeDef*	UartPort;
}CardReaderDef;
//=======================================================锁结构体
typedef	struct	_LockFlag		//锁控制标志及吸合时间
{
	struct
	{
		unsigned char LockFlg		:1;	//bit0：0-无操作,1-有操作请求(控制锁的状态）
		unsigned char LockOn		:1;	//bit1：0-释放锁，1-开锁
		unsigned char LockSts		:1;	//bit2：0-已释放，1-已开锁
		unsigned char LockTout	:1;	//bit3：0-未超时，1-已超时(取药超时)
	}sLockSts;		//药箱状态
	unsigned long	LockTimeCountdown;		//开锁倒计时 计时到0时释放锁，如果LockTimeOut不为0，则开锁
//	unsigned long	Status			:1;		//0-锁未开，1-已开
//	unsigned long	LockOnTime	;	//锁吸合时间，最大值0x3FFF FFFF
	GPIO_TypeDef*	GPIOx;
	u16	GPIO_Pin_n;
}LockFlagDef;
//=======================================================时间结构体
typedef	struct	_Time			//相关时间表
{
	unsigned long	TimeSYS;	//系统计时器
//	unsigned long	TimeSEG;	//数码管更新数据计时器----可用于检测数码管通讯状态 20ms外发一个数码管状态
//	unsigned long	TimeBOX;	//药箱检测计时器	每个端口分配100mS时间检测----可用于检测读卡器通讯状态
	unsigned long	TimeBUS;	//外部总线时间
	unsigned long	TimeCard;	//读卡器时间
}TimeDef;

//=======================================================数码管结构体
typedef struct _sSeg 
{
	struct
	{
		unsigned char SegFlg			:1;	//bit0：0-无操作,		1-有操作请求(需要更新数码管状态）
		unsigned char Sync				:1;	//bit1：0-无操作,		1-更新
	}sSegSts;			//数码管标志
	unsigned short	DisplayTime;		//显示时间
	unsigned long		SyncTime;				//更新显示时间
	sSegFarmeDef 		SegFarme;					//数码管通讯协议
} sSegDef;			//数码管数据结构体

//=======================================================总线请求结构体
typedef	struct	_sBus		//端口状态--：有卡/无卡
{
	struct
	{
		unsigned short BusFlg		:1;	//bit0：0-无操作,	1-有待处理事件(上报数据或者状态）
		unsigned short GetID		:1;	//bit1：0-无请求，	1-有请求	，获取ID请求需要上报ID
		unsigned short GetBox		:1;	//bit2：0-无请求，	1-有请求	，取药(数码管数值同时闪烁)
		unsigned short GotBox		:1;	//bit3：0-无操作，	1-药箱已被取走
		unsigned short TakeBox	:1;	//bit4：0-无操作，	1-药箱被强制取
		unsigned short BoxBack	:1;	//bit5：0-无操作，	1-药箱收回,收回后需要上报药箱号（有GotBox标志时设置此位）
		unsigned short TimeOut	:1;	//bit6：0-无操作，	1-取药超时
	}BusqSts;		//药箱状态
	unsigned long		GetBoxTimeCountdown;			//取药计时，如果不为0，则未超时，否则超时
	unsigned char 	CardData[CardLength];	//卡号数据CardData[0]为百位，CardData[1]为十位，CardData[2]为个位
	unsigned char		Ucode;								//用户码
	sMs485FrmDef		sBusFarme;		//485总线结构体
}sBusDef;
typedef	struct	_sBusData		//端口状态--：有卡/无卡
{
	sMs485FrmDef	sFarmeTxd;		//总线485数据结构体---发送
	sMs485FrmDef	sFarmeRxd;		//总线485数据结构体---接收
	sMs485FrmDef	sFarmeRev;		//总线485数据结构体---缓存
}sBusDataDef;


//=======================================================端口/槽位所有信息结构体
typedef	struct	_Port
{
	sSegDef					Seg;				//数码管数据结构体
	LockFlagDef			Lock;				//锁信息
	sBusDef					sBus;				//总线请求结构体
	CardReaderDef		sReader;		//读卡器结构体

	unsigned char		PortNum;							//槽地址（端口号）
} PortDef;
//=======================================================运行步骤
//typedef	struct	_Step
//{
////	unsigned char 	ReadCard		:1;			//bit0:	0-无操作,1-需要读卡
////	unsigned char 	WriteSeg		:1;			//bit1:	0-无操作,1-需要更新数码管(串请占用串口更新数码管）
//} StepDef;
//=======================================================公共数据结构体
typedef struct _sPlu 
{
//	StepDef				Step;					//执行分步（主要防止读卡器与数码管复用串口数据错乱）
	TimeDef				Time;					//各功能计时器
	sBusDataDef		BusData;			//总线485数据结构体---待处理
	u8 						PowerUpFlag;	//上电标志，0未上电完，1上电完
} sPluDef;			//数码管数据结构体
//=======================================================板内端口/板内数据
typedef	struct	_sBorad		//端口状态--：有卡/无卡
{
	PortDef	Port1;
	PortDef	Port2;
	PortDef	Port3;
	PortDef	Port4;
	
	sPluDef	sPlu;		//公共数据结构体

	u8	Nserial;		//流水号 1~0xFF
}sBoradDef;


//=======================================================全局变量
extern sBoradDef	sBorad;					//端口/槽位所有信息结构体




//=================================================================================================================主程序
void PC016V20_Configuration(void);
void PC016V20_Server(void);


//=================================================================================================================消息处理
void MessageServer(sBoradDef*	sBorad);		//外部总线消息处理

void MessageAnalysis(sBoradDef*	sBorad);	//解析消息

void MessageAck(sBoradDef*	sBorad);			//外部总线应答

void MessageGetID(sBoradDef*	sBorad);		//获取ID指令处理（0x12指令）：总线标志,数码管亮5秒

void MessageGetBox(sBoradDef*	sBorad);		//取药箱消息处理（0x13指令，0x13指令上报(0x93))：总线标志，数码管标志

void MessageLock(sBoradDef*	sBorad);			//锁相关消息处理（0x13指令，0x13指令上报(0x93))：锁标志

void MessageSend(sBoradDef*	sBorad);			//发送消息/消息上报


//=================================================================================================================板内处理程序
void BoardServer(sBoradDef*	sBorad);			//板内：锁控制，药箱，数码管

void BoardLockServer(sBoradDef*	sBorad);	//锁开关处理

void BoardBoxServer(sBoradDef*	sBorad);	//药箱处理程序

void BoardSegServer(sBoradDef*	sBorad);	//数码管

void BoardSegClear(sBoradDef*	sBorad);				//清除数码管显示


//=================================================================================================================读卡器
void CardReaderServer(sBoradDef*	sBorad);				//读卡器

void CardReaderSetPassive(sBoradDef*	sBorad);		//设置读卡器为被动读卡

void CardReaderSetActive(sBoradDef*	sBorad);			//设置读卡器为主动读卡

void CardReaderReadCmd(sBoradDef*	sBorad);				//读卡指令

void CardDataAnalysis(sBoradDef*	sBorad);			//卡数据格式分析

void CardReaderRead(sBoradDef*	sBorad);					//检查读卡器有无收到数据

void CardReaderSendData(USART_TypeDef* USARTx,u8 *tx_buffer,u16 BufferSize);	//向读卡器发送数据

u16 CardReaderReadData(USART_TypeDef* USARTx,u8 *RevBuffer,u8 *RxdBuffer);		//检查读卡器有无收到数据

u16 Uart5ReceiveData(sBoradDef*	sBorad);			//串口5读数据

void CardReadTimeCount(sBoradDef*	sBorad);										//取卡后倒计时，如果倒计时未完成再收回卡数据，读卡不稳定时的误动作



//=================================================================================================================锁程序
//void Lock_Server(sBoradDef*	sBorad);
//=================================================================================================================硬件驱动程序
void HALUsartRemapEnable(void);				//使能串口复用
void HALUsartRemapDisable(void);			//关闭串口复用
void HALSendSeg(u32* Buffer,u16 Length);					//向数码管发送数据

//=================================================================================================================配置程序
void Lock_Configuration(void);				//锁初始化
void Switch_Configuration(void);			//拔码开关初始化及读数
void RS485_Configuration(void);				//RS485配置
void CardReader_Configuration(void);	//读卡器配置
void Data_Initialize(void);						//参数初始化
void ResetData(void);									//重置相关变量


void CardReaderError(void);			//重置相关变量
#endif



