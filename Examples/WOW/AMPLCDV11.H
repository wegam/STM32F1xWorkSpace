#ifndef __AMPLCDV11_H
#define __AMPLCDV11_H


#include	"AMP_PHY.H"

#include "GT32L32M0180.H"
#include "ST7789V.H"
#include "STM32_USART.H"
#include "SWITCHID.H"

////------------------锁接口J10
//#define SYSLEDPort    GPIOA         //锁控制接口，高电平开锁
//#define SYSLEDPin     GPIO_Pin_0

#define	DspMaxNameTypeCount	30	//最大接收名字类型数量
#define	FresPageTime	2000			//页面刷新时间--ms


typedef struct _sAmpLcd
{
	sST7789VDef	LcdPort;			//LCD
	SPIDef 			SpiPort;			//字库
	RS485Def 		RS485Port;   	//RS485通讯
	SwitchDef 	sSwitch;			//拔码开关
	struct
	{
		unsigned char Lay:4;	//层地址
		unsigned char Seg:4;	//位地址
	}Addr;
	unsigned char ReceivedManaCount;	//接收到的物品数量
	unsigned char DisplaySerial;			//当前显示序号
	DspDataDef DspData[DspMaxNameTypeCount];	//显示内容
}sAmpLcdDef;


extern stAMPProdef   AMPPro;

void AMPLCDV11_Configuration(void);
void AMPLCDV11_Server(void);

void AMPLCDV11_Loop(void);


void AMPLCDV11_Receive(void);
void AMPLCDV11_Process(unsigned char* ReceDatabuffer,unsigned short datalen);
void DisplayMana(void);
void SetBackColor(unsigned short BKColor);
unsigned short GetBackColor(void);

unsigned short HW_SendBuff(enCCPortDef Port,unsigned char* pBuffer,unsigned short length);
//=================================时间函数ST==============================================================
void Tim_Server(void);


void HW_Configuration(void);
#endif
