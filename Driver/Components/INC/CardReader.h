#ifndef __CardReader_H
#define __CardReader_H 



#include "stdint.h"

//============================================================================================读卡器协议Start
//-----------------------------------------------------------------------------------枚举类
typedef enum	_eFWS9UsHead			//帧头标识符
{
	eFWS9UsOutHead		=	0xE1,		//帧头,上位机下发时固定为0XE1，下位机应答时固定为0XD2
	eFWS9UsInHead			=	0xD2,		//帧头,上位机下发时固定为0XE1，下位机应答时固定为0XD2
}eFWS9UsHeadDef;
typedef enum	_eFWS9UsEnd				//帧尾标识符
{
	eFWS9UsOutEnd				=	0x1E,		//帧尾，上位机下发时固定为0X1E，下位机应答时固定为0X2D；
	eFWS9UsInEnd				=	0x2D,		//帧尾，上位机下发时固定为0X1E，下位机应答时固定为0X2D；
}eFWS9UsEndDef;
typedef enum	_eFWS9Cmd					//命令类型
{
	eFWS9CmdReadBlock		=	0x24,		//0x24 读扇区块命令（每个扇区的块为0.1.2.其他无效）[1字节扇区号+1字节块号+1字节密钥模式（0x60\0x61）+ 6字节密码(密码-FF FF FF FF FF FF)]
	eFWS9CmdWriteBlock	=	0x25,		//0x25 写扇区块命令（每个扇区的块为0.1.2.其他无效）[1字节扇区号+1字节块号+1字节密钥模式（0x60\0x61）+ 6字节密码 + 16字节数据]
	eFWS9CmdSetBlock		=	0x44,		//0x44 设置读头读卡扇区、块号、KEYA/KEYB、读卡密码	[1字节扇区号+1字节块号+1字节密钥模式（0x60\0x61）+ 6字节密码(密码-FF FF FF FF FF FF)]
}eFWS9CmdDef;
typedef enum	_eFWS9ErrCode			//错误类型
{
	eFWS9NoErr					=	0x00,			//成功，无错误
	eFWS9NoCard					=	0x01,			//在操作区域内无卡
}eFWS9ErrCodeDef;

typedef enum	_eFWS9KeyType			//密钥模式 KEYA（0x60）/KEYB(0x61)
{
	eKEYA				=	0x60,			//
	eKEYB				=	0x61,			//
}eFWS9KeyDef;

//-----------------------------------------------------------------------------------结构体
//------------------------------------------CRC16
typedef	struct	_eFWS9CRC16
{
	unsigned char CRC_H;			//CRC高8位
	unsigned char CRC_L;			//CRC低8位
}eFWS9CRC16Def;
//------------------------------------------读卡器返回卡数据结构体
typedef	struct	_sFWS9RecData	//读卡器接收到的数据格式
{
	eFWS9UsHeadDef	Head;				//帧头标识符:上位机下发时固定为0XE1，下位机应答时固定为0XD2
	eFWS9CmdDef			Cmd;				//命令类型
	eFWS9ErrCodeDef Err;				//错误类型
	unsigned char 	data[16];		//如果在读卡时，无错误会发送16字节卡数据
	unsigned short 	CRC16;			//CRC16
	eFWS9UsEndDef 	End;				//帧尾，上位机下发时固定为0X1E，下位机应答时固定为0X2D；
}sFWS9RecDataDef;

typedef	struct	_sFWS9CmdData		//发送读卡器命令数据格式
{
	eFWS9UsHeadDef	Head;					//帧头标识符:上位机下发时固定为0XE1，下位机应答时固定为0XD2
	eFWS9CmdDef			Cmd;					//命令类型
	unsigned char 	Sector;				//扇区号
	unsigned char 	Block;				//块号（每个扇区的块为0.1.2.其他无效）
	eFWS9KeyDef			KeyType;			//密钥模式 KEYA（0x60）/KEYB(0x61) 默认KEYA
	unsigned char 	PassWord[6];	//6字节密码，默认0xFF,0xFF,0xFF,0xFF,0xFF,0xFF
	unsigned short 	CRC16;				//CRC16
	eFWS9UsEndDef 	End;					//帧尾，上位机下发时固定为0X1E，下位机应答时固定为0X2D；
}sFWS9CmdDataDef;


typedef	struct	_sFWS9WriteData		//写卡命令格式
{
	eFWS9UsHeadDef	Head;					//帧头标识符:上位机下发时固定为0XE1，下位机应答时固定为0XD2
	eFWS9CmdDef			Cmd;					//命令类型
	unsigned char 	Sector;				//扇区号
	unsigned char 	Block;				//块号（每个扇区的块为0.1.2.其他无效）
	eFWS9KeyDef			KeyType;			//密钥模式 KEYA（0x60）/KEYB(0x61) 默认KEYA
	unsigned char 	PassWord[6];	//6字节密码，默认0xFF,0xFF,0xFF,0xFF,0xFF,0xFF
	unsigned char 	data[16];			//写卡时为待写入的16字节数据
	unsigned short 	CRC16;				//CRC16
	eFWS9UsEndDef 	End;					//帧尾，上位机下发时固定为0X1E，下位机应答时固定为0X2D；
}sFWS9WriteDataDef;

typedef	struct	_sFWS9SetArea		//设置读头读卡扇区、块号、KEYA（0x60）/KEYB(0x61)、读卡密码0x44
{
	eFWS9UsHeadDef	Head;					//帧头标识符:上位机下发时固定为0XE1，下位机应答时固定为0XD2
	eFWS9CmdDef			Cmd;					//命令类型
	unsigned char 	Sector;				//扇区号
	unsigned char 	Block;				//块号（每个扇区的块为0.1.2.其他无效）
	eFWS9KeyDef			KeyType;			//密钥模式 KEYA（0x60）/KEYB(0x61) 默认KEYA
	unsigned char 	PassWord[6];	//6字节密码，默认0xFF,0xFF,0xFF,0xFF,0xFF,0xFF
	unsigned short 	CRC16;				//CRC16
	eFWS9UsEndDef 	End;					//帧尾，上位机下发时固定为0X1E，下位机应答时固定为0X2D；
}sFWS9SetAreaDef;

//-----------------------------------------------------------------------------------头文件
extern sFWS9RecDataDef		sFWS9RecData;			//读卡器接收到的数据格式
extern sFWS9CmdDataDef		sFWS9ReadData;		//读卡命令格式
extern sFWS9CmdDataDef		sFWS9SetArea;			//设置读卡区域
extern sFWS9WriteDataDef	sFWS9WriteData;		//写卡命令格式

    
#endif

