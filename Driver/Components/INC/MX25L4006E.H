#ifndef __MX25L4006E_H
#define __MX25L4006E_H

#include "stm32f10x_type.h"
//#include "STM32_SPI.H"
#include "STM32_PWM.H"

#include "SPI_FLASH.H"


/******************************MX25L4006E命令定义*******************************/
typedef enum _MX25L4006ECmd
{
	MX25L4006E_WREN			=	(unsigned char)0x06,			//write Enable：写使能
	MX25L4006E_WRDI			=	(unsigned char)0x04,				//write disable：写失能
	MX25L4006E_WRSR			=	(unsigned char)0x01,				//write status register：写状态寄存器
	MX25L4006E_RDID			=	(unsigned char)0x9F,				//read identification：读设备信息，3byte；第一字节为制造商代码，第二第三字节为芯片代码
	MX25L4006E_RDSR			=	(unsigned char)0x05,				//read status register：读状态寄存器
	MX25L4006E_READ			=	(unsigned char)0x03,				//read data：读数据
	MX25L4006E_FREAD		=	(unsigned char)0x0B,				//fast read data：快速读取数据
	MX25L4006E_RDSFDP		=	(unsigned char)0x5A,				//Read SFDP:读(SFDP)Serial Flash芯片规范
	MX25L4006E_RES			=	(unsigned char)0xAB,				//Read Electronic Signature:读器件读取电子标签
	MX25L4006E_REMS			=	(unsigned char)0x90,				//Read Electronic Manufacturer & Device ID:读书制造商信息和ID
	MX25L4006E_DREAD		=	(unsigned char)0x3B,				//Double Output Mode command：双输出模式命令
	MX25L4006E_SE				=	(unsigned char)0x20,				//Sector Erase：扇区擦除
	MX25L4006E_BE				=	(unsigned char)0x52,				//Block Erase：块擦除也可以用0XD8
	MX25L4006E_CE				=	(unsigned char)0x60,				//Chip Erase：芯片擦除; 整片擦除; 也可以用0XC7
	MX25L4006E_PP				=	(unsigned char)0x02,				//Page Program：写页面
	MX25L4006E_DP				=	(unsigned char)0xB9,				//Deep Power Down：深度省电状态
	MX25L4006E_RDP			=	(unsigned char)0xAB					//Release from Deep Power-down：退出深度掉电
}MX25L4006ECmdDef;
typedef enum _MX25L4006EMemory
{
	MX25L4006E_ChipSize			=	(unsigned long)524288,	//Flash总容量byte单位--512KByte
	MX25L4006E_PageSize			=	(unsigned long)256,			//页大小byte单位
	MX25L4006E_SectorSize		=	(unsigned long)4096,		//扇区大小byte单位-4KByte/16Page
	MX25L4006E_BulkSize			=	(unsigned long)65536		//块大小byte单位-64KByte/16Sector
}MX25L4006EMemoryDef;	

//----数据结构体------------------------------------------------------------
typedef struct      /*Card Identification Data*/
{
	unsigned long			Address;						//字符起始地址
	unsigned char			Buffer[200];				//点阵数据
	unsigned char			BufferSize;					//点阵数据长度
}MX25L4006EDataDef;
typedef struct	_MX25L4006E
{
	SPIFlashDef				SPIFlash;			//SPIFlash驱动
	MX25L4006EDataDef Data;
}MX25L4006EDef;



void MX25L4006E_Initialize(MX25L4006EDef *MX25Lx);
void MX25L4006E_Server(void);


#endif

