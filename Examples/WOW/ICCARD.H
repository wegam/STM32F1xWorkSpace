#ifndef __ICCARD_H
#define __ICCARD_H


//#include "stm32f10x_gpio.h"
//#include "stm32f10x_rcc.h"
//#include "STM32_GPIO.H"
#include "STM32_PWM.H"
//#include "STM32_GPIO.H"
//#include "STM32_USART.H"
//#include "STM32_DMA.H"

//================IC卡命令
typedef enum	_ICCARD_Cmd
{
	GetOnlineDevice		=	0x20,		//搜索在线机器
	UpDataUID					=	0x23,		//刷卡上传UID，命令字 0x23
	GetBlockData			=	0x24,		//读扇区块（数据）
	SetBlockData			=	0x25,		//写扇区块
	SetPassWord				=	0x26,		//修改扇区密码
	SetRelayOn				=	0x40,		//继电器打开
	SetRelayOff				=	0x41,		//关闭继电器
	RemoteCtl					=	0x3E,		//远程操作
	SetReaderID				=	0x42,		//设置读头编号
	GetReaderID				=	0x43,		//获取读头编号
	SetReaderKey			=	0x44		//设置读头密码	
}ICCARD_CmdType;

//=================写块数据
#define ICCARD_MO_SetDataBlock(Sector,	/*扇区*/	\
																Block,	/*块*/			\
																ICCARD_Number	/*卡号*/	\
																)												\
0xE1,   /* F-Head 	:为帧头，上位机下发时固定为0XE1，下位机应答时固定为0XD2*/	\
0x25,  	/* CmdType 	:命令类型*/	\
0x01,		/* Sector 	:1字节扇区号*/	\
0x01,   /* Block 	:1字节块号	*/	\
0x60,   /* KeyType	:1字节密钥模式 KEYA（0x60）/KEYB(0x61)*/	\
0xFF,   /* PassWord0 :6字节密码*/	\
0xFF,   /* PassWord1 */	\
0xFF,   /* PassWord2 */	\
0xFF,		/* PassWord3 */	\
0xFF,   /* PassWord4 */	\
0xFF,		/* PassWord5 */	\
0xFF,   /* Data0 	:16字节数据*/	\
0xFF,   /* Data1 	*/	\
0xFF,   /* Data2 	*/	\
0xFF,   /* Data3 	*/	\
0xFF,   /* Data4 	*/	\
0xFF,   /* Data5 	*/	\
0xFF,   /* Data6 	*/	\
0xFF,   /* Data7 	*/	\
0xFF,   /* Data8 	*/	\
0xFF,   /* Data9 	*/	\
0xFF,   /* Data10 	*/	\
0xFF,   /* Data11 	*/	\
0xFF,   /* Data12 	*/	\
0xFF,   /* Data13 	*/	\
0xFF,   /* Data14 	*/	\
0xFF,   	/* Data15 	*/	\
0x1C,   /* Crc16-HIGN */	\
0x0D,		/* Crc16-LOW */	\
0x1E   	/* F-End	:为帧尾，上位机下发时固定为0X1E，下位机应答时固定为0X2D*/


	
	

void ICCARD_Configuration(void);
void ICCARD_Server(void);

unsigned char* ICCARD_WriteData(u32	Number);

#endif
