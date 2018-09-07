#ifndef __HC_PHY_H
#define __HC_PHY_H



#define	MaxNetPerLayer	8					//每个结点所连接的最大支点数为64
#define	TargetLayer			LALayer		//本板所在层级：0-网关层，1-单元板层CabinetAddr，2-层控制板层LayerAddr，3,-驱动层SlotAddr
#define	MBLayer					0					//网关板所在层级：0-网关层，1-单元板层CabinetAddr，2-层控制板层LayerAddr，3,-驱动层SlotAddr
#define	CALayer					1					//单元板在层级：0-网关层，1-单元板层CabinetAddr，2-层控制板层LayerAddr，3,-驱动层SlotAddr
#define	LALayer					2					//层板在层级：0-网关层，1-单元板层CabinetAddr，2-层控制板层LayerAddr，3,-驱动层SlotAddr
#define	SALayer					3					//驱动所在层级：0-网关层，1-单元板层CabinetAddr，2-层控制板层LayerAddr，3,-驱动层SlotAddr

#define	SubTargetAdd		HCSYS.Layer+1	//下一级目标地址

#define	RS232Head1			0xFA				//RS232头标识符第一字节
#define	RS232Head2			0xF5				//RS232头标识符第二字节
#define	RS485Head1			0x7E				//RS485头标识符
#define	RS485end1				0x7F				//RS485尾标识符

#define	ReSendCount			5						//重发次数

#define	BusDataSize		128						//一条消息携带的最大数据个数
//#define	BascDataLen		64					//单元地址+层地址+槽地址+状态码
//#define	BascDataLen		4						//单元地址+层地址+槽地址+状态码
//#define	HeadDataLen		8						//单元地址+层地址+槽地址+状态码
#define	AckDataLen		MinDataLen		//应答消息长度
#define	MinDataLen		10				 		//最短消息长度

#define	CMDRead(n)		(n&0x80)			//最高位为1
#define	CMDWrite(n)		(!(n&0x80))		//最高位为0

typedef enum
{
	Err_FAULT_NON						=	0x00,	//无错误
	Err_FAULT_BUSY					=	0x01,	//忙状态
	Err_FAULT_ILLAGALPARA		=	0x02,	//参数非法
	Err_FAULT_INACTIVE			=	0x03,	//称重通道未激活
	Err_FAULT_DIRECTION			=	0x04,	//传感器方向错
	Err_FAULT_DIFFOVF				=	0x05,	//称重差值过大
	Err_FAULT_SENSOR				=	0x06,	//传感器故障
	Err_FAULT_ILLIGALWEIGHT	=	0x07,	//称重数值非法
	Err_FAULT_WEIGHTOVF			=	0x08,	//称重数据溢出
	Err_Fault_Nocail				=	0x09,	//称重未标定
	Err_CC_Error						=	0x0A,	//校验错误
	Err_TimeOut							=	0x0B	//连接超时
}ErrDef;			//错误码
typedef enum		//状态码
{
	eNoErr		=	0x00,		//无错误
	eNoData		=	0x23,		//无药箱数据
	eBoxTout	=	0x24,		//取药箱超时
	eBoxOff		=	0x25,		//药箱取走
	eBoxBack	=	0x26,		//药箱取走后收回
	eReadErr	=	0x27,		//读卡器通讯异常
	eBoxTake	=	0x25,		//药箱被强制取走,原28
	eBoxBusy	=	0x28,		//当前板忙或者等待状态
	eBoxAck		=	0x29,		//此为应答消息
}StatusDef;
typedef enum
{
	CMD_WRITE_QTY				=	0x01,	//写入数量
	CMD_UNLOCK					=	0x02,	//解锁
	CMD_ADD_MTRL				=	0x04,	//加料
	CMD_RDC_MTRL				=	0x06,	//取料
	CMD_CHECK_QTY				=	0x07,	//盘点
	CMD_WRITE_HINT			=	0x08,	//写入提示
	CMD_WRITE_NOTE			=	0x09,	//写入注释
	CMD_CNTRL_LED				=	0x0A,	//提示灯控制 ，该指令由单元板执行
	CMD_CNTRL_GATE			=	0x0B,	//冰箱门控制 ，该指令由网关执行，不往下层传递
	CMD_CHECK_VERSION		=	0x0C,	//查询软件版本
	//============================预设
	CMD_SET_DATA				=	0x71,	//设置数据/参数
	CMD_GET_DATA				=	0x72,	//获取数据/参数
	CMD_GET_CTL					=	0x73,	//控制命令
	CMD_GET_ADDR				=	0x74,	//控制命令
	CMD_LINK						=	0x0E	//透传传---如升级时使用
}CmdDef;			//命令码
typedef enum
{
	SubCmd_WRITE_QTY				=	0x01,	//写入数量
	SubCmd_UNLOCK						=	0x02,	//解锁
	SubCmd_ADD_MTRL					=	0x04,	//加料
	SubCmd_RDC_MTRL					=	0x06,	//取料
	SubCmd_CHECK_QTY				=	0x07,	//盘点
	SubCmd_WRITE_HINT				=	0x08,	//写入提示
	SubCmd_WRITE_NOTE				=	0x09,	//写入注释
	SubCmd_CNTRL_LED				=	0x0A,	//提示灯控制 ，该指令由单元板执行
	SubCmd_CNTRL_GATE				=	0x0B,	//冰箱门控制 ，该指令由网关执行，不往下层传递
	SubCmd_CHECK_VERSION		=	0x0C,	//查询软件版本
	//============================预设
	SubCmd_Adrress					=	0x71	//查询/设置地址
}SubCmdDef;			//命令码子码
typedef enum
{
	RES_OK = 0,			/* 0: Successful */
	RES_READ,				/* 1: 读数据 */
	RES_WRITE,			/* 2: 写数据 */
	RES_NOTRDY,			/* 3: Not Ready */
	RES_PARERR,			/* 4: Invalid Parameter */
	RES_ACKMSG,				/* 5: 应答消息 */
	RES_UNKNOW,			/* 6: 未识别 */
	RES_NODATA,			/* 7: 无数据 */
  RES_FARMERR,	  // 8: 帧格式错误
	RES_FARME232,		// 9: 232格式数据
	RES_FARME485,		// 9: 232格式数据
	RES_LINK				// 9: 透传 例如升级使用，直接转发
}HCResult;
typedef enum
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


typedef struct	_RS232Fram
{
	unsigned short 	FarmLen;
	unsigned char		Data[];
}RS232FramDef;		//RS232消息帧格式(PC机通讯)
typedef struct	_RS485Fram
{
	unsigned short 	FarmLen;
	unsigned char		Data[];
}RS485FramDef;		//RS485消息帧格式()

typedef struct	_Step
{
	unsigned char	IDLE:1;			//b0	空闲标志,					0-空闲，1-根据以下位的忙状态
	unsigned char	SendU:1;		//b1	往上级发送标志,		0-空闲，1-表示正在发送中
	unsigned char	WaitU:1;		//b2	等待上级响应标志,	0-空闲，1-表示等待下层板响应
	unsigned char	SendD:1;		//b3	往下级发送标志,		0-空闲，1-表示正在发送中
	unsigned char	WaitD:1;		//b4	等待下级响应标志,	0-空闲，1-表示等待下层板响应
	
}StepDef;

//-----------------------------------------------------------------------------------结构体
typedef	struct	_Addr						//通讯地址结构体（下行时：Addr1,Addr2,Addr3都得有数据，上行时，柜地址为0x00）
{
	unsigned char 	CabinetAddr;	//柜地址(单元柜号)  下行时为柜地址，上行时，柜地址为0x00）
	unsigned char 	LayerAddr;		//层地址
	unsigned char		SlotAddr;			//槽地址(终端地址)	
}AddrDef;
typedef	struct	_RS232Head
{
	unsigned char	Head1;		  //b1	0xFA
	unsigned char	Head2;		  //b2	0xF5
	unsigned char	Serial;		  //b3			流水号 0x01~0x7D 每次使用后加1(为了不与起始符和结束符冲突，流水号最大值为0x7D)
	CmdDef			  Cmd;		    //b4			命令号：0x12-获取指定IC卡号，0x13取药,上报命令也在此位
	unsigned char	Bcc8;		    //b5			异或校验	//计算范围为从地址开始(计算长度DataLength)	
  unsigned char	UserCode;		//b6			用户码：不处理，原样返回
	unsigned char	DataLength;	//b7			数据长度从地址开始计算长度--包含地址、数据和状态码
}RS232HeadDef;			//RS232帧格式
typedef	struct	_RS232Frame
{
	RS232HeadDef	Head;				//b1-b7		RS232标准头文件
	AddrDef			  Addr;				//b8-b10	通讯地址结构体（三级地址）
	StatusDef		  StsCode;	  //b11			状态码/错误码	
	unsigned char	*data;	    //b12-n		数据长度为(DataLength-4)的数据起始地址	
}RS232FrameDef;			//RS232帧格式

typedef	struct	_RS485Frame			//485通讯消息帧结构体MessageFarme  
{
	unsigned char	HeadCode;		//b1			识别符	0x7E  
	unsigned char	TargetAdd;	//b2			目标地址（暂时理解为单元柜地址）下发为接收地址，上传为0x00
	unsigned char	SourceAdd;	//b3			源地址 下发为0x00，上传为本地址
	unsigned char	Serial;			//b4			流水号 0x01~0x7D 每次使用后加1(为了不与起始符和结束符冲突，流水号最大值为0x7D)
	CmdDef			  Cmd;				//b5			命令号：0x12-获取指定IC卡号，0x13取药,上报命令也在此位
	unsigned char	UserCode;		//b6			用户码：不处理，原样返回
	StatusDef		  StsCode;		//b7			状态码/错误码	
	unsigned char	DataLength;	//b8			data数据长度（*data)	--不包含地址		
	AddrDef			  Addr;				//b9-b11	通讯地址结构体（三级地址）	
	unsigned char	*data;	    //b(DataLength)-b(DataLength)数据	
	unsigned char	Bcc8;				//b(DataLength+12)异或校验	//计算范围为起始段到数据段(RS485Head-data[DataLength-1])
	unsigned char	EndCode;		//b(DataLength+13)结束符 0x7F
}RS485FrameDef;

typedef	struct	_RS485Ack			//485通讯消息帧结构体MessageFarme  
{
	unsigned char		HeadCode;	  //b0识别符	0x7E  为其它表示无应答数据
	unsigned char		TargetAdd;	//b1目标地址（暂时理解为单元柜地址）下发为接收地址，上传为0x00
	unsigned char		SourceAdd;	//b2源地址 下发为0x00，上传为本地址
	unsigned char		Serial;			//b3流水号 0x01~0x7D 每次使用后加1(为了不与起始符和结束符冲突，流水号最大值为0x7D)
	CmdDef					Cmd;				//b4命令号：0x12-获取指定IC卡号，0x13取药,上报命令也在此位
	unsigned char		UserCode;		//b6			用户码：不处理，原样返回
	StatusDef				StsCode;		//状态码/错误码
	unsigned char		DataLength;	//b11			data数据长度（*data)
	unsigned char		Bcc8;				//异或校验	//计算范围为起始段到数据段(TargetAdd-data[n])到错误码
	unsigned char		EndCode;	  //结束符 0x7F
}RS485AckDef;



typedef	struct	_Trans			//485通讯消息帧结构体MessageFarme  
{
  unsigned short Length;    //待传输数据长度，数据不为0表示有数据
  struct
  {
    unsigned char Time;     //计时器-单位ms
    unsigned char Retry;    //重试次数
  }Retry;
	unsigned char   data[BusDataSize+15];
}TransDef;



typedef	struct	_RS485AckNode	  //485通讯消息帧结构体MessageFarme  
{
  unsigned short  FarmeLength;     	//Frame的总长度(data[BusDataSize]有效数据长度
	unsigned char   data[BusDataSize];
}RS485AckNodeDef;
typedef	struct	_DataNode	  //485通讯消息帧结构体MessageFarme  
{
  struct 
	{
		unsigned short Length	:14;	//数据长度		data[BusDataSize]的长度
		unsigned short UD			:	1;	//方向标识;	0--需要上传到上层，1--需要下发到下层
		unsigned short Flag		:	1;	//数据标志;	0--无数据，1--缓存内有数据
	}FarmeInfo;     			//Frame的总长度和方向信息
	unsigned char   data[BusDataSize];
}DataNodeDef;


typedef	struct	_HCSYS
{
  unsigned char SwitchAddr;											//本板地址
  unsigned char Layer;													//本板所在层级：0-网关层，1-单元板层CabinetAddr，2-层控制板层LayerAddr，3,-驱动层SlotAddr
	unsigned int	SerialNum;											//序列号
	const char		*Borad_Name;										//PCB板名
	unsigned char	SubOnlineAddr[MaxNetPerLayer];	//下一级在线设备地址
}HCSYSDef;







HCResult HCBoradSet(const unsigned char Layer,const unsigned char id);
unsigned short GetAck(unsigned char *buffer,unsigned char flag);

HCResult GetSubOnlineAddr(void);
unsigned short GetDataProcess(unsigned char *buffer,const unsigned char UDflag);
HCResult SetDataProcess(const unsigned char *buffer,const unsigned short length,const unsigned char UDflag);
HCResult CheckDataFarm(const unsigned char *buffer,const unsigned short length,const unsigned char UDflag);

HCResult MBLayerDataProcess(const unsigned char *buffer,const unsigned short length,const unsigned char UDflag);
HCResult CALayerDataProcess(const unsigned char *buffer,const unsigned short length,const unsigned char UDflag);
HCResult LALayerDataProcess(const unsigned char *buffer,const unsigned short length,const unsigned char UDflag);
HCResult SALayerDataProcess(const unsigned char *buffer,const unsigned short length,const unsigned char UDflag);

HCResult AckDataProcess(const unsigned char *buffer,const unsigned short length,const unsigned char UDflag);


HCResult UMFrameProcess(const unsigned char *buffer);
HCResult DMFrameProcess(const unsigned char *buffer);


















#endif



