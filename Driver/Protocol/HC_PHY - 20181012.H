#ifndef __HC_PHY_H
#define __HC_PHY_H



#define	MaxNetPerLayer	8					//每个结点所连接的最大支点数为64
//#define	TargetLayer			LALayer		//本板所在层级：0-网关层，1-单元板层CabinetAddr，2-层控制板层LayerAddr，3,-驱动层SlotAddr
#define	MBLayer					0					//网关板所在层级：0-网关层，1-单元板层CabinetAddr，2-层控制板层LayerAddr，3,-驱动层SlotAddr
#define	CALayer					1					//单元板在层级：0-网关层，1-单元板层CabinetAddr，2-层控制板层LayerAddr，3,-驱动层SlotAddr
#define	LALayer					2					//层板在层级：0-网关层，1-单元板层CabinetAddr，2-层控制板层LayerAddr，3,-驱动层SlotAddr
#define	SALayer					3					//驱动所在层级：0-网关层，1-单元板层CabinetAddr，2-层控制板层LayerAddr，3,-驱动层SlotAddr

#define	SubTargetAdd		HCSYS.Layer+1	//下一级目标地址

#define	RS232Head1			(unsigned char)0xFA				//RS232头标识符第一字节
#define	RS232Head2			(unsigned char)0xF5				//RS232头标识符第二字节
#define	RS485HeadCode		(unsigned char)0x7E				//RS485头标识符
#define	RS485EndCode		(unsigned char)0x7F				//RS485尾标识符

#define	ReSendCount			2						//重发次数

#define	BusDataSize		  64				  //一条消息携带的最大数据个数
#define	SelfBuffSize				10		  //本地址需要处理的消息缓存大小(不需要转发给下一层的消息)

//#define	BascDataLen		64					//单元地址+层地址+槽地址+状态码
//#define	BascDataLen		4						//单元地址+层地址+槽地址+状态码
//#define	HeadDataLen		8						//单元地址+层地址+槽地址+状态码
#define	RS485StartFrameLen 	8             		//RS485通讯起始帧长度
#define	RS485AckFrameLen		6			  //应答帧长度
#define	RS485MinFrameLen		6				//最短帧长度要求---应答消息长度10


#define	RS232StartFrameLen 	RS232MinFrameLen   	//RS485通讯起始帧长度
#define	RS232AckFrameLen		6			//应答帧长度
#define	RS232MinFrameLen		6			//最短帧长度要求---应答消息长度10


//#define	CMDRead(n)		(n&0x80)			//最高位为1
//#define	CMDWrite(n)		(!(n&0x80))		//最高位为0

typedef enum
{
	Err_None						    =	0x00,	//无错误
	Err_FAULT_BUSY					=	0x01,	//忙状态
	Err_FAULT_ILLAGALPARA		=	0x02,	//参数非法
	Err_FAULT_INACTIVE			=	0x03,	//称重通道未激活
	Err_FAULT_DIRECTION			=	0x04,	//传感器方向错
	Err_FAULT_DIFFOVF				=	0x05,	//称重差值过大
	Err_FAULT_SENSOR				=	0x06,	//传感器故障
	Err_FAULT_ILLIGALWEIGHT	=	0x07,	//称重数值非法
	Err_FAULT_WEIGHTOVF		  =	0x08,	//称重数据溢出
	Err_Fault_Nocail				=	0x09,	//称重未标定
	Err_CC_Error						=	0x0A,	//校验错误
	Err_TimeOut							=	0x0B,	//连接超时
	Err_ACKMSG							=	0x0C	//此为应答消息
}ErrCodeDef;	  //状态码/错误码
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
	CMD_ACK							=	0x0D,
	//============================预设
	CMD_SET_DATA				=	0x0E,	//设置数据/参数
	CMD_GET_DATA				=	0x0F,	//获取数据/参数
	CMD_GET_CTL					=	0x73,	//控制命令
	CMD_GET_ADDR				=	0x74,	//控制命令
	CMD_LINK					  =	0x0E,	//透传传---如升级时使用
	
	CMD_TEST					  =	0xFF	//透传传---如升级时使用
	
}CmdDef;  //命令码

//typedef enum
//{
//	SubCmd_WRITE_QTY				=	0x01,	//写入数量
//	SubCmd_UNLOCK						=	0x02,	//解锁
//	SubCmd_ADD_MTRL					=	0x04,	//加料
//	SubCmd_RDC_MTRL					=	0x06,	//取料
//	SubCmd_CHECK_QTY				=	0x07,	//盘点
//	SubCmd_WRITE_HINT				=	0x08,	//写入提示
//	SubCmd_WRITE_NOTE				=	0x09,	//写入注释
//	SubCmd_CNTRL_LED				=	0x0A,	//提示灯控制 ，该指令由单元板执行
//	SubCmd_CNTRL_GATE				=	0x0B,	//冰箱门控制 ，该指令由网关执行，不往下层传递
//	SubCmd_CHECK_VERSION		=	0x0C,	//查询软件版本
//	//============================预设
//	SubCmd_Adrress					=	0x71	//查询/设置地址
//}SubCmdDef;			//命令码子码
typedef enum
{
	RES_OK = 0,			/* 0: Successful */
	RES_Err,				//错误
	RES_READ,				/* 1: 读数据 */
	RES_WRITE,			/* 2: 写数据 */
	RES_NOTRDY,			/* 3: Not Ready */
	RES_PARERR,			/* 4: Invalid Parameter */
	RES_ACKMSG,		  /* 5: 应答消息 */
	RES_UNKNOW,			/* 6: 未识别 */
	RES_NODATA,			/* 7: 无数据 */
	RES_FARMERR,	  // 8: 帧格式错误
	RES_FARME232,		// 9: 232格式数据
	RES_FARME485,		// 9: 232格式数据
	RES_LINK,				// 9: 透传 例如升级使用，直接转发
  RES_DataOF		  // 9: 数据长度超限，溢出
}HCResult;

//-----------------------------------------------------------------------------------结构体
typedef	struct	_Addr						//通讯地址结构体（下行时：Addr1,Addr2,Addr3都得有数据，上行时，柜地址为0x00）,如果下发消息到中间层，则此层后面的地址必须设定为0x00
{
	unsigned char 	CabinetAddr;	//柜地址(单元柜号)
	unsigned char 	LayerAddr;		//层地址
	unsigned char	  SlotAddr;			//槽地址(终端地址)
}AddrDef;
//-------------------------------------------------
typedef	struct	_DataType					//用户数据标识
{
//	unsigned char	  Serial;				//流水号	
	CmdDef 					Cmd;					//命令号
	unsigned char 	UserCode;			//用户码
	unsigned char		*Data;				//数据
}DataTypeDef;
//-------------------------------------------------
typedef struct
{
	unsigned char Serial;
	CmdDef				Cmd;
	unsigned char Bcc8;
	unsigned char UserCode;
	unsigned char DataLength;	
}RS232FrameStartDef;
//-------------------------------------------------
typedef struct
{
	unsigned char TargetAddr;		//目标地址：上层下发，目标地址为本地址，源地址无效，下层上发，目标地址必须为0，源地址为发送地址,如果地址为0xFF表示为广播地址
	unsigned char SourceAddr;		//源地址：上层下发，目标地址为本地址，源地址无效，下层上发，目标地址必须为0，源地址为发送地址	
	unsigned char Serial;				//流水号 0x01~0x7D 每次使用后加1(为了不与起始符和结束符冲突，流水号最大值为0x7D)
	CmdDef				Cmd;					//命令号
	unsigned char UserCode;			//用户码：不处理，原样返回
	unsigned char DataLength;		//数据长度从地址开始计算长度--(3字节地址+1字节状态码+n字节数据）
}RS485FrameStartDef;
//-------------------------------------------------
typedef struct _DataHead
{
	AddrDef				Addr;					//地址	
	ErrCodeDef	  ErrCode;  		//状态码/错误码	
}DataStartDef;
//-------------------------------------------------
typedef	struct	_RS232Frame			//RS232通讯格式
{
	//---------------------------起始段：包含两字节头标识(0xFA 0xF5)
	unsigned char	Head1;		  	//b1	0xFA
	unsigned char	Head2;		  	//b2	0xF5
	unsigned char	Serial;		  	//b3	流水号 0x01~0x7D 每次使用后加1(为了不与起始符和结束符冲突，流水号最大值为0x7D)
	CmdDef			  Cmd;		    	//b4	命令号：0x12-获取指定IC卡号，0x13取药,上报命令也在此位
	unsigned char	Bcc8;		    	//b5	异或校验	//计算范围为从地址开始(计算长度DataLength)	
  unsigned char	UserCode;			//b6	用户码：不处理，原样返回
	unsigned char	DataLength;		//b7	数据长度从地址开始计算长度--(3字节地址+1字节状态码+n字节数据）
	//---------------------------数据段：
	unsigned char	CabinetAddr;	//b8	柜地址(单元柜号)
	unsigned char	LayerAddr;		//b9	层地址
	unsigned char	SlotAddr;			//b10	槽地址(终端地址)
	ErrCodeDef	  ErrCode;  		//b8	状态码/错误码
	unsigned char	*data;  			//b9	数据(如果Start中DataLength	不为0，则data前三字节代表地址，倒数第二字节为BCC校验码，最后一字节为EndCode(0x7F)
}RS232FrameDef;			//RS232帧格式
//-------------------------------------------------
typedef	struct	_RS485Frame  //485通讯消息帧结构体MessageFarme  
{
	//---------------------------起始段
	unsigned char				HeadCode;		  //b1	识别符	0x7E
	RS485FrameStartDef	HStart;				//起始段
	DataStartDef				DStart;				//数据起始段
	unsigned char				Data[BusDataSize]; 	//b13	数据，倒数第二字节为BCC校验码，最后一字节为EndCode(0x7F)
	//---------------------------数据段:前三字节为用户标识，校验码及结束符不计入数据长度
//	unsigned char	*data;  			//b13	数据，倒数第二字节为BCC校验码，最后一字节为EndCode(0x7F)
}RS485FrameDef;			//RS485协议帧起始段(格式固定） 长度8字节
//-------------------------------------------------
typedef	struct	_RS485AckFrame  //485通讯消息帧结构体MessageFarme  
{
	unsigned char	HeadCode;		  //b1	识别符	0x7E	
	unsigned char	TargetAddr;		//b2	目标地址：上层下发，目标地址为本地址，源地址无效，下层上发，目标地址必须为0，源地址为发送地址,如果地址为0xFF表示为广播地址
	unsigned char	SourceAddr;		//b3	源地址：上层下发，目标地址为本地址，源地址无效，下层上发，目标地址必须为0，源地址为发送地址
	ErrCodeDef	  ErrCode;  		//b4	状态码/错误码
  unsigned char	Bcc8;					//b5	从TargetAddr开始到ErrCode
  unsigned char	EndCode;		  //b6	识别符	0x7F  
}RS485AckDef;   							//RS485协议帧起始段(格式固定） 长度8字节
//-------------------------------------------------
typedef	struct	_Ack	  //485通讯消息帧结构体MessageFarme  
{
	unsigned char	FarmeLength; 	//Frame的总长度(data[BusDataSize]有效数据长度
	RS485AckDef		Ack;
}AckDef;
//-------------------------------------------------
typedef	struct	_Trans		//485通讯消息帧结构体MessageFarme  
{
  unsigned short Length;    //待传输数据长度，数据不为0表示有数据,需要传送
  struct
  {
    unsigned char Time;     //计时器-单位ms
    unsigned char Retry;    //重试次数
  }Retry;
	unsigned char   data[BusDataSize+15];
}TransDef;
//-------------------------------------------------
typedef	struct	_DataNode	  //485通讯消息帧结构体MessageFarme  
{
	unsigned short	NodeLength;		//待传输数据长度，数据不为0表示有数据,需要传送
	unsigned char		data[BusDataSize];		//第一字节为命令码，第二字节为用户码，之后为数据
}DataNodeDef;
//-------------------------------------------------
typedef	struct	_HCSYS
{
	unsigned char	SwitchAddr;					//本板地址
	unsigned char	Layer;							//本板所在层级：0-网关层，1-单元板层CabinetAddr，2-层控制板层LayerAddr，3,-驱动层SlotAddr
	unsigned int	SerialNum;					//序列号
	const	char		*Borad_Name;				//PCB板名
	unsigned char	SubOnlineAddr[MaxNetPerLayer];	//下一级在线设备地址
}HCSYSDef;
//-------------------------------------------------
typedef struct
{
  unsigned short (*GetUplinkBusData)(unsigned char *buffer);
  unsigned short (*GetDownlinkBusData)(unsigned char *buffer);
  HCResult(*SendUplinkData)(unsigned char *buffer,unsigned short length);
  HCResult(*SendDownlinkData)(unsigned char *buffer,unsigned short length);
}CommDef;

extern CommDef CommFun;

HCResult HCBoradSet(const unsigned char Layer,const unsigned char id);

HCResult APIRS485UplinkSetData(const unsigned char *buffer,const unsigned short length);
HCResult APIRS485DownlinkSetData(const unsigned char *buffer,const unsigned short length);
HCResult APIRS485DownlinkReceiveData(const unsigned char *buffer,const unsigned short length);

unsigned short APIRS485UplinkGetAck(unsigned char *buffer);
unsigned short APIRS485DownlinkGetAck(unsigned char *buffer);


unsigned short APIRS485UplinkGetData(unsigned char *buffer);
unsigned short APIRS485DownlinkGetData(unsigned char *buffer);

HCResult APIRS485SendData(const unsigned char *buffer,const unsigned short length);
unsigned short APIRS485ProcessData(unsigned char *buffer);




HCResult APIRS232UplinkSetData(const unsigned char *buffer,const unsigned short length);














////unsigned char FarmeCheck(const void *buffer,const unsigned short length);
//unsigned char FarmeCheck(const void *buffer,const unsigned short length);
//HCResult RS485ToRS485(const void *buffer,const unsigned short length);
//RS485FrameDef* RS485Step1FarmeDataCheck(const void *buffer,const unsigned short length);		//查找RS485数据在buffer中的起始地址并校验数据
//HCResult RS485Step2AckProcess(const void *buffer,const unsigned short length);
//HCResult RS485Step3SaveData(const void *buffer,const unsigned short length);

//HCResult RS232ToRS485(const void *buffer,const unsigned short length);
//RS232FrameDef* RS232Step1FindData(const void *buffer,const unsigned short length);
//HCResult RS232Step2AckProcess(const void *buffer,const unsigned short length);
//HCResult RS232Step3SaveData(const void *buffer,const unsigned short length);










HCResult GetSubOnlineAddr(void);





















#endif



