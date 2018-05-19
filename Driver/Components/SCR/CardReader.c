#include "CardReader.h"	


sFWS9RecDataDef		sFWS9RecData;			//读卡器接收到的数据格式
//sFWS9ReadDataDef	sFWS9ReadData;		//读卡命令格式
//sFWS9WriteDataDef	sFWS9WriteData;		//写卡命令格式
sFWS9CmdDataDef	sFWS9ReadData	=			//读卡命令格式
{
	eFWS9UsOutHead,									//帧头标识符:上位机下发时固定为0XE1，下位机应答时固定为0XD2
	eFWS9CmdReadBlock,							//命令类型
	0x01,														//扇区号
	0x01,														//块号（每个扇区的块为0.1.2.其他无效）
	eKEYA,													//密钥模式 KEYA（0x60）/KEYB(0x61) 默认KEYA
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,	//6字节密码，默认0xFF,0xFF,0xFF,0xFF,0xFF,0xFF
	0xFFFF,													//CRC16
	eFWS9UsOutEnd										//帧尾，上位机下发时固定为0X1E，下位机应答时固定为0X2D；
};
sFWS9CmdDataDef	sFWS9SetArea	=			//设置读卡区域
{
	eFWS9UsOutHead,									//帧头标识符:上位机下发时固定为0XE1，下位机应答时固定为0XD2
	eFWS9CmdSetBlock,								//命令类型
	0x01,														//扇区号
	0x01,														//块号（每个扇区的块为0.1.2.其他无效）
	eKEYA,													//密钥模式 KEYA（0x60）/KEYB(0x61) 默认KEYA
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,	//6字节密码，默认0xFF,0xFF,0xFF,0xFF,0xFF,0xFF
	0xFFFF,													//CRC16
	eFWS9UsOutEnd										//帧尾，上位机下发时固定为0X1E，下位机应答时固定为0X2D；
};
/*******************************************************************************
*函数名			:	function
*功能描述		:	function
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
void FWS9_Initialize(void)						//参数初始化
{
}



