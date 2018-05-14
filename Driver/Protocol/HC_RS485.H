#ifndef __HC_RS485_H
#define __HC_RS485_H




#define	HC485BuffSize	16


//==============================起始标识符&结束标识符
typedef enum	_HC485Head
{
	eHead		=	0x7E,
	eEnd		=	0x7F
}eRS485HeadDef;

//==============================命令码
typedef enum	_HC485Cmd
{
	eR,
}eRS485CmdDef;
//==============================状态码/错误码
typedef enum	_HC485ErrCode
{
	eGetStatus	=	1,
	eGetData		=	2,
	eSetStatus	=	3,
	eSetData		=	4,
}eRS485ErrDef;
//==============================通讯协议结构体
typedef	struct	_sHC485Farme			//485通讯消息帧结构体MessageFarme  
{
	eRS485HeadDef		eHead;			//b0识别符	0x7E
	unsigned char		dAdd;				//b1目标地址（暂时理解为单元柜地址）下发为接收地址，上传为0x00
	unsigned char		sAdd;				//b2源地址 下发为0x00，上传为本地址
	unsigned char		nSerial;		//b3流水号 0x01~0xFF 每次使用后加1
	eRS485CmdDef		Cmd;				//b4命令号：0x12-获取指定IC卡号，0x13取药,上报命令也在此位
	unsigned char		Ucode;			//b5用户码：不处理，原样返回
	unsigned char		Length;			//b6地址+异常码固定长度为4，卡数据长度为3
	unsigned char		Addr1;			//单元柜地址
	unsigned char		Addr2;			//层地址
	unsigned char		Addr3;			//端口地址/槽地址

	eRS485ErrDef		ErrCode;		//状态码/错误码
	
	unsigned char		data[HC485BuffSize];		//BusDataSize为最大数据接收缓冲，实际数据大小按照Length-4(4为地址和状态码长度)
	
	unsigned char		Bcc8;				//异或校验	//计算范围为起始段到数据段(dAdd~data[n])到错误码
	eRS485HeadDef		eEnd;				//结束符 0x7F
}sHC485FrmDef;













#endif



