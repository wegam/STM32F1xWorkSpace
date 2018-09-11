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
#define	RS485endCode		(unsigned char)0x7F				//RS485尾标识符

#define	ReSendCount			1						//重发次数

#define	BusDataSize		128						//一条消息携带的最大数据个数
#define	SelfBuffSize				10					//本地址需要处理的消息缓存大小(不需要转发给下一层的消息)

//#define	BascDataLen		64					//单元地址+层地址+槽地址+状态码
//#define	BascDataLen		4						//单元地址+层地址+槽地址+状态码
//#define	HeadDataLen		8						//单元地址+层地址+槽地址+状态码
#define	RS485StartFrameLen 	9             		//RS485通讯起始帧长度
#define	RS485AckFrameLen		6			  //应答帧长度
#define	RS485MinFrameLen		10			//最短帧长度要求---应答消息长度10


#define	RS232StartFrameLen 	RS232MinFrameLen   	//RS485通讯起始帧长度
#define	RS232AckFrameLen		RS232MinFrameLen		//应答帧长度
#define	RS232MinFrameLen		7				 						//最短帧长度要求---应答消息长度10


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
//typedef enum		//状态码
//{
//	eNoErr		=	0x00,		//无错误
//	eNoData		=	0x23,		//无药箱数据
//	eBoxTout	=	0x24,		//取药箱超时
//	eBoxOff		=	0x25,		//药箱取走
//	eBoxBack	=	0x26,		//药箱取走后收回
//	eReadErr	=	0x27,		//读卡器通讯异常
//	eBoxTake	=	0x25,		//药箱被强制取走,原28
//	eBoxBusy	=	0x28,		//当前板忙或者等待状态
//	eBoxAck		=	0x29,		//此为应答消息
//}StatusDef;

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
	CMD_LINK					=	0x0E,	//透传传---如升级时使用
	
	CMD_TEST					=	0xFF	//透传传---如升级时使用
	
}CmdDef;  //命令码
//typedef struct
//{
//  CmdDef CMD        :5;     //命令体：
//  unsigned char Ack :1;     //应答位：Ack == 0时，此条消息依据CMD处理；Ack == 1时，代表此消息为应答消息，CMD内容无效，根据DIR判断是上层应答还是下层往上应答
//  unsigned char CD  :1;     //保留
//  unsigned char DIR :1;     //方向：DIR  = 0代表此消息为上层下发消息，DIR  = 1代表此消息为下层上传消息
//}CMDType;
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
	RES_ACKMSG,		  /* 5: 应答消息 */
	RES_UNKNOW,			/* 6: 未识别 */
	RES_NODATA,			/* 7: 无数据 */
	RES_FARMERR,	  // 8: 帧格式错误
	RES_FARME232,		// 9: 232格式数据
	RES_FARME485,		// 9: 232格式数据
	RES_LINK				// 9: 透传 例如升级使用，直接转发
}HCResult;

//-----------------------------------------------------------------------------------结构体
typedef	struct	_Addr						//通讯地址结构体（下行时：Addr1,Addr2,Addr3都得有数据，上行时，柜地址为0x00）,如果下发消息到中间层，则此层后面的地址必须设定为0x00
{
	unsigned char 	CabinetAddr;	//柜地址(单元柜号)
	unsigned char 	LayerAddr;		//层地址
	unsigned char	  SlotAddr;			//槽地址(终端地址)	
}AddrDef;
typedef	struct	_RS232Frame
{
	unsigned char	Head1;		  	//b1	0xFA
	unsigned char	Head2;		  	//b2	0xF5
	unsigned char	Serial;		  	//b3	流水号 0x01~0x7D 每次使用后加1(为了不与起始符和结束符冲突，流水号最大值为0x7D)
	CmdDef			  Cmd;		    	//b4	命令号：0x12-获取指定IC卡号，0x13取药,上报命令也在此位
	unsigned char	Bcc8;		    	//b5	异或校验	//计算范围为从地址开始(计算长度DataLength)	
  unsigned char	UserCode;			//b6	用户码：不处理，原样返回
	unsigned char	DataLength;		//b7	数据长度从地址开始计算长度--(3字节地址+1字节状态码+n字节数据）
	unsigned char	CabinetAddr;	//b8	柜地址(单元柜号)
	unsigned char	LayerAddr;		//b9	层地址
	unsigned char	SlotAddr;			//b10	槽地址(终端地址)
	ErrCodeDef	  ErrCode;  		//b8	状态码/错误码
	unsigned char	*data;  			//b9	数据(如果Start中DataLength	不为0，则data前三字节代表地址，倒数第二字节为BCC校验码，最后一字节为EndCode(0x7F)
}RS232FrameDef;			//RS232帧格式

typedef	struct	_RS485Frame  //485通讯消息帧结构体MessageFarme  
{
	unsigned char	HeadCode;		  //b1	识别符	0x7E
	unsigned char	Bcc8;					//b2	从TargetAddr开始到帧尾
	unsigned char	TargetAddr;		//b3	目标地址：上层下发，目标地址为本地址，源地址无效，下层上发，目标地址必须为0，源地址为发送地址,如果地址为0xFF表示为广播地址
	unsigned char	SourceAddr;		//b4	源地址：上层下发，目标地址为本地址，源地址无效，下层上发，目标地址必须为0，源地址为发送地址
	unsigned char	Serial;		  	//b5	流水号 0x01~0x7D 每次使用后加1(为了不与起始符和结束符冲突，流水号最大值为0x7D)
	CmdDef			  Cmd;		      //b6	命令号：0x12-获取指定IC卡号，0x13取药,上报命令也在此位
	unsigned char	UserCode;	  	//b7	用户码：不处理，原样返回
	ErrCodeDef	  ErrCode;  		//b8	状态码/错误码		
	unsigned char	DataLength;		//b9	data数据长度（地址长度+data长度)	--包含地址，如果DataLength为0，则地址和数据域都没有，尾部需要添加Bcc8校验和EndCode
	unsigned char	CabinetAddr;	//b10	柜地址(单元柜号)
	unsigned char	LayerAddr;		//b11	层地址
	unsigned char	SlotAddr;			//b12	槽地址(终端地址)
	unsigned char	*data;  			//b13	数据(如果Start中DataLength	不为0，则data前三字节代表地址，倒数第二字节为BCC校验码，最后一字节为EndCode(0x7F)
}RS485FrameDef;   						//RS485协议帧起始段(格式固定） 长度8字节
typedef	struct	_RS485AckFrame  //485通讯消息帧结构体MessageFarme  
{
	unsigned char	HeadCode;		  //b1	识别符	0x7E	
	unsigned char	TargetAddr;		//b2	目标地址：上层下发，目标地址为本地址，源地址无效，下层上发，目标地址必须为0，源地址为发送地址,如果地址为0xFF表示为广播地址
	unsigned char	SourceAddr;		//b3	源地址：上层下发，目标地址为本地址，源地址无效，下层上发，目标地址必须为0，源地址为发送地址
	ErrCodeDef	  ErrCode;  		//b4	状态码/错误码
  unsigned char	Bcc8;					//b5	从TargetAddr开始到ErrCode
  unsigned char	EndCode;		  //b6	识别符	0x7F  
}RS485AckDef;   						//RS485协议帧起始段(格式固定） 长度8字节
typedef	struct	_Ack	  //485通讯消息帧结构体MessageFarme  
{
	unsigned char	FarmeLength; 	//Frame的总长度(data[BusDataSize]有效数据长度
	unsigned char Data[16];
}AckDef;

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

typedef	struct	_DataNode	  //485通讯消息帧结构体MessageFarme  
{
	unsigned short	Length;		//待传输数据长度，数据不为0表示有数据,需要传送
	unsigned char		data[BusDataSize];
}DataNodeDef;


typedef	struct	_HCSYS
{
	unsigned char	SwitchAddr;					//本板地址
	unsigned char	Layer;						//本板所在层级：0-网关层，1-单元板层CabinetAddr，2-层控制板层LayerAddr，3,-驱动层SlotAddr
	unsigned int	SerialNum;					//序列号
	const	char		*Borad_Name;				//PCB板名
	unsigned char	SubOnlineAddr[MaxNetPerLayer];	//下一级在线设备地址
}HCSYSDef;

typedef struct
{
  unsigned short (*GetUplinkBusData)(unsigned char *buffer);
  unsigned short (*GetDownlinkBusData)(unsigned char *buffer);
  HCResult(*SendUplinkData)(unsigned char *buffer,unsigned short length);
  HCResult(*SendDownlinkData)(unsigned char *buffer,unsigned short length);
}CommDef;

extern CommDef CommFun;

HCResult HCBoradSet(const unsigned char Layer,const unsigned char id);

HCResult APISetDataProcess(const unsigned char *buffer,const unsigned short length,unsigned char UDFlag);

unsigned short APIRS485GetUplinkAck(unsigned char *buffer);
unsigned short APIRS485GetDownlinkAck(unsigned char *buffer);


unsigned short APIRS485GetUplinkData(unsigned char *buffer);
unsigned short APIRS485GetDownlinkData(unsigned char *buffer);

unsigned short APIReadData(unsigned char *buffer);

HCResult APISendData(const unsigned char *buffer,const unsigned short length);






//unsigned char FarmeCheck(const void *buffer,const unsigned short length);
unsigned char FarmeCheck(const void *buffer,const unsigned short length,unsigned char UDFlag);
HCResult RS485ToRS485(const void *buffer,const unsigned short length);
RS485FrameDef* RS485Step1FarmeDataCheck(const void *buffer,const unsigned short length);		//查找RS485数据在buffer中的起始地址并校验数据
HCResult RS485Step2AckProcess(const void *buffer,const unsigned short length);
HCResult RS485Step3SaveData(const void *buffer,const unsigned short length);

HCResult RS232ToRS485(const void *buffer,const unsigned short length);
RS232FrameDef* RS232Step1FindData(const void *buffer,const unsigned short length);
HCResult RS232Step2AckProcess(const void *buffer,const unsigned short length);
HCResult RS232Step3SaveData(const void *buffer,const unsigned short length);








HCResult GetSubOnlineAddr(void);





















#endif



