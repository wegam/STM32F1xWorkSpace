#ifndef __AMPLCDV11_H
#define __AMPLCDV11_H


#include	"AMP_PHY.H"

#include "GT32L32M0180.H"
#include "ST7789V.H"
#include "STM32_USART.H"
#include "SWITCHID.H"

#define	BackColorStartAddr	0x0801F800		//原点值在MCU内部FLASH的存储地址126K地址，按128Kflash应用

#define	SelectModel	4

#if 1==SelectModel		//DisplayManaStaticTest1();
	#define DisplayClrColor			0xFFFF		//显示区域清屏颜色
	#define DisplayBackColor		0xFFFF		//默认字体底色
	#define DisplayFontColor		0x0000		//默认字体颜色
	
	
	#define DisplayNameBkColor	0xFFFF		//名称底色
	#define DisplayNameFtColor	0x054A		//名称颜色
	#define	DisplayNameFtSize		24				//名称字体大小
	
	#define DisplaySpecBkColor	0xFFFF		//规格底色
	#define DisplaySpecFtColor	0x5ACA		//规格颜色
	#define	DisplaySpecFtSize		16				//规格字体大小
	
	#define DisplayNumBkColor		0x5902		//数量底色
	#define DisplayNumFtColor		0x07DF		//数量颜色
	#define	DisplayNumFtSize		48				//数量字体大小
	
	#define DisplaySerialBkColor		0xFFFF		//数量底色
	#define DisplaySerialFtColor		0xFB00		//数量颜色
	#define	DisplaySerialFtSize		16				//数量字体大小
	
	#define DisplayTitleBkColor		0x865D		//标题底色
	#define DisplayTitleFtColor		0x0000		//标题颜色
	#define DisplayTitleSize	16		//标题字体大小
	
	#define DisplaySeparBkColor		0x8450		//分隔线颜色
	#define DisplaySeparWidth	2							//分隔线宽度
	
	#define DisplayCodeBkColor		0xFFFF		//物料编码底色
	#define DisplayCodeFtColor		0x5ACA		//物料编码颜色
	#define	DisplayCodeFtSize			16				//物料编码字体大小
	
	#define DisplayVenderBkColor		0xFFFF		//厂家名称底色
	#define DisplayVenderFtColor		0x5ACA		//厂家名称颜色
	#define	DisplayVenderFtSize			16				//厂家名称字体大小
	
	#define DisplayTopStartY	16
	#define DisplayTopEndY		8	
	#define DisplayBotStartY	ST7789V_H-8
	#define DisplayBotEndY		ST7789V_H
	
	
	
	#define DisplayStartX	2
	#define DisplayEndX		2	
#elif 2==SelectModel		//DisplayManaStaticTest2();
	#define DisplayClrColor			0xFFFF		//显示区域清屏颜色
	#define DisplayBackColor		0xFFFF		//默认字体底色
	#define DisplayFontColor		0x0000		//默认字体颜色
	
	
	#define DisplayNameBkColor	0xFFFF		//名称底色
	#define DisplayNameFtColor	0x054A		//名称颜色
	#define	DisplayNameFtSize		24				//名称字体大小
	
	#define DisplaySpecBkColor	0xFFFF		//规格底色
	#define DisplaySpecFtColor	0x5ACA		//规格颜色
	#define	DisplaySpecFtSize		16				//规格字体大小
	
	#define DisplayNumBkColor		0x5902		//数量底色
	#define DisplayNumFtColor		0x07DF		//数量颜色
	#define	DisplayNumFtSize		32				//数量字体大小
	
	#define DisplaySerialBkColor	0xFFFF		//数量底色
	#define DisplaySerialFtColor	0xFB00		//数量颜色
	#define	DisplaySerialFtSize		16				//数量字体大小
	
	#define DisplayCodeBkColor		0xFFFF		//物料编码底色
	#define DisplayCodeFtColor		0x5ACA		//物料编码颜色
	#define	DisplayCodeFtSize			16				//物料编码字体大小
	
	#define DisplayVenderBkColor		0xFFFF		//厂家名称底色
	#define DisplayVenderFtColor		0x5ACA		//厂家名称颜色
	#define	DisplayVenderFtSize			16				//厂家名称字体大小
	
	#define DisplayTitleBkColor		0x865D		//标题底色
	#define DisplayTitleFtColor		0x0000		//标题颜色
	#define DisplayTitleSize			24				//标题字体大小
	
	#define DisplaySeparBkColor		0x8450		//分隔线颜色
	#define DisplaySeparWidth	2							//分隔线宽度
	
	#define DisplayTopStartY	16
	#define DisplayTopEndY		8	
	#define DisplayBotStartY	ST7789V_H-16
	#define DisplayBotEndY		ST7789V_H
	
	
	
	#define DisplayStartX	2
	#define DisplayEndX		2
#elif 3==SelectModel		//DisplayManaModel1();
	#define DisplayClrColor			0xFFFF		//显示区域清屏颜色
	#define DisplayBackColor		0xFFFF		//默认字体底色
	#define DisplayFontColor		0x0000		//默认字体颜色
	
	
	#define DisplayNameBkColor	0xFFFF		//名称底色
	#define DisplayNameFtColor	0x054A		//名称颜色
	#define	DisplayNameFtSize		24				//名称字体大小
	
	#define DisplaySpecBkColor	0xFFFF		//规格底色
	#define DisplaySpecFtColor	0x5ACA		//规格颜色
	#define	DisplaySpecFtSize		16				//规格字体大小
	
	#define DisplayNumBkColor		0x5902		//数量底色
	#define DisplayNumFtColor		0x07DF		//数量颜色
	#define	DisplayNumFtSize		48				//数量字体大小
	
	#define DisplaySerialBkColor		0xFFFF		//数量底色
	#define DisplaySerialFtColor		0xFB00		//数量颜色
	#define	DisplaySerialFtSize		16				//数量字体大小
	
	#define DisplayCodeBkColor		0xFFFF		//物料编码底色
	#define DisplayCodeFtColor		0x5ACA		//物料编码颜色
	#define	DisplayCodeFtSize			16				//物料编码字体大小
	
	#define DisplayVenderBkColor		0xFFFF		//厂家名称底色
	#define DisplayVenderFtColor		0x5ACA		//厂家名称颜色
	#define	DisplayVenderFtSize			16				//厂家名称字体大小
	
	#define DisplayTitleBkColor		0x865D		//标题底色
	#define DisplayTitleFtColor		0x0000		//标题颜色
	#define DisplayTitleSize	16		//标题字体大小
	
	#define DisplaySeparBkColor		0x8450		//分隔线颜色
	#define DisplaySeparWidth	2							//分隔线宽度
	
	#define DisplayTopStartY	16
	#define DisplayTopEndY		8	
	#define DisplayBotStartY	ST7789V_H-8
	#define DisplayBotEndY		ST7789V_H	
	
	#define DisplayStartX	2
	#define DisplayEndX		2	
	
#elif 4==SelectModel		//DisplayManaModel2();
	#define DisplayClrColor			0xFFFF		//显示区域清屏颜色
	#define DisplayBackColor		0xFFFF		//默认字体底色
	#define DisplayFontColor		0x0000		//默认字体颜色
	
	
	#define DisplayNameBkColor	0xFFFF		//名称底色
	#define DisplayNameFtColor	0x054A		//名称颜色
	#define	DisplayNameFtSize		24				//名称字体大小
	
	#define DisplaySpecBkColor	0xFFFF		//规格底色
	#define DisplaySpecFtColor	0x5ACA		//规格颜色
	#define	DisplaySpecFtSize		16				//规格字体大小
	
	#define DisplayNumBkColor		0x5902		//数量底色
	#define DisplayNumFtColor		0x07DF		//数量颜色
	#define	DisplayNumFtSize		32				//数量字体大小
	
	#define DisplaySerialBkColor		0xFFFF		//数量底色
	#define DisplaySerialFtColor		0xFB00		//数量颜色
	#define	DisplaySerialFtSize		16				//数量字体大小
	
	#define DisplayCodeBkColor		0xFFFF		//物料编码底色
	#define DisplayCodeFtColor		0x5ACA		//物料编码颜色
	#define	DisplayCodeFtSize			16				//物料编码字体大小
	
	#define DisplayVenderBkColor		0xFFFF		//厂家名称底色
	#define DisplayVenderFtColor		0x5ACA		//厂家名称颜色
	#define	DisplayVenderFtSize			16				//厂家名称字体大小
	
	#define DisplayTitleBkColor		0x865D		//标题底色
	#define DisplayTitleFtColor		0x0000		//标题颜色
	#define DisplayTitleSize	16		//标题字体大小
	
	#define DisplaySeparBkColor		0x8450		//分隔线颜色
	#define DisplaySeparWidth	2							//分隔线宽度
	
	#define DisplayTopStartY	24
	#define DisplayTopEndY		8	
	#define DisplayBotStartY	ST7789V_H-16
	#define DisplayBotEndY		ST7789V_H	
	
	#define DisplayStartX	2
	#define DisplayEndX		2	
#elif 5==SelectModel		//DisplayManaModel3();
	#define DisplayClrColor			0xFFFF		//显示区域清屏颜色
	#define DisplayBackColor		0xFFFF		//默认字体底色
	#define DisplayFontColor		0x0000		//默认字体颜色
	
	
	#define DisplayNameBkColor	0xFFFF		//名称底色
	#define DisplayNameFtColor	0x054A		//名称颜色
	#define	DisplayNameFtSize		24				//名称字体大小
	
	#define DisplaySpecBkColor	0xFFFF		//规格底色
	#define DisplaySpecFtColor	0x5ACA		//规格颜色
	#define	DisplaySpecFtSize		16				//规格字体大小
	
	#define DisplayNumBkColor		0x5902		//数量底色
	#define DisplayNumFtColor		0x07DF		//数量颜色
	#define	DisplayNumFtSize		32				//数量字体大小
	
	#define DisplaySerialBkColor		0xFFFF		//数量底色
	#define DisplaySerialFtColor		0xFB00		//数量颜色
	#define	DisplaySerialFtSize		16				//数量字体大小
	
	#define DisplayCodeBkColor		0xFFFF		//物料编码底色
	#define DisplayCodeFtColor		0x5ACA		//物料编码颜色
	#define	DisplayCodeFtSize			16				//物料编码字体大小
	
	#define DisplayVenderBkColor		0xFFFF		//厂家名称底色
	#define DisplayVenderFtColor		0x5ACA		//厂家名称颜色
	#define	DisplayVenderFtSize			16				//厂家名称字体大小
	
	#define DisplayTitleBkColor		0x865D		//标题底色
	#define DisplayTitleFtColor		0x0000		//标题颜色
	#define DisplayTitleSize	24						//标题字体大小
	
	#define DisplaySeparBkColor		0x8450		//分隔线颜色
	#define DisplaySeparWidth	2							//分隔线宽度
	
	#define DisplayTopStartY	16
	#define DisplayTopEndY		8	
	#define DisplayBotStartY	ST7789V_H-16
	#define DisplayBotEndY		ST7789V_H
	
	
	
	#define DisplayStartX	2
	#define DisplayEndX		2
#else			//DisplayManaModel1();
	#define DisplayClrColor			0xFFFF		//显示区域清屏颜色
	#define DisplayBackColor		0xFFFF		//默认字体底色
	#define DisplayFontColor		0x0000		//默认字体颜色
	
	
	#define DisplayNameBkColor	0xFFFF		//名称底色
	#define DisplayNameFtColor	0x054A		//名称颜色
	#define	DisplayNameFtSize		24				//名称字体大小
	
	#define DisplaySpecBkColor	0xFFFF		//规格底色
	#define DisplaySpecFtColor	0x5ACA		//规格颜色
	#define	DisplaySpecFtSize		16				//规格字体大小
	
	#define DisplayNumBkColor		0x5902		//数量底色
	#define DisplayNumFtColor		0x07DF		//数量颜色
	#define	DisplayNumFtSize		48				//数量字体大小
	
	#define DisplaySerialBkColor		0xFFFF		//数量底色
	#define DisplaySerialFtColor		0xFB00		//数量颜色
	#define	DisplaySerialFtSize		16				//数量字体大小
	
	#define DisplayCodeBkColor		0xFFFF		//物料编码底色
	#define DisplayCodeFtColor		0x5ACA		//物料编码颜色
	#define	DisplayCodeFtSize			16				//物料编码字体大小
	
	#define DisplayVenderBkColor		0xFFFF		//厂家名称底色
	#define DisplayVenderFtColor		0x5ACA		//厂家名称颜色
	#define	DisplayVenderFtSize			16				//厂家名称字体大小
	
	#define DisplayTitleBkColor		0x865D		//标题底色
	#define DisplayTitleFtColor		0x0000		//标题颜色
	#define DisplayTitleSize	16		//标题字体大小
	
	#define DisplaySeparBkColor		0x8450		//分隔线颜色
	#define DisplaySeparWidth	2							//分隔线宽度
	
	#define DisplayTopStartY	16
	#define DisplayTopEndY		8	
	#define DisplayBotStartY	ST7789V_H-8
	#define DisplayBotEndY		ST7789V_H
	
	
	
	#define DisplayStartX	2
	#define DisplayEndX		2
	
#endif





#define	DspMaxNameTypeCount	30	//最大接收名字类型数量
#define	FresPageTime	2000			//页面刷新时间--ms



	
//#define testmodel

typedef struct _sAmpLcd
{
	sST7789VDef	LcdPort;			//LCD
	SPIDef 			SpiPort;			//字库
	RS485Def 		RS485Port;   	//RS485通讯
	SwitchDef 	sSwitch;			//拔码开关
	struct
	{
		unsigned char Cab:4;	//柜地址
		unsigned char Lay:4;	//层地址
		unsigned char Seg:4;	//位地址
	}Addr;
	unsigned char ReceivedManaCount;	//接收到的物品数量
	unsigned char DisplaySerial;			//当前显示序号
	unsigned short PowerOnTime;				//上电时间
	DspDataDef DspData[DspMaxNameTypeCount];	//显示内容
}sAmpLcdDef;


extern stAMPProdef   AMPPro;

void AMPLCDV11_Configuration(void);
void AMPLCDV11_Server(void);
void DisplayAddr(void);

void AMPLCDV11_Loop(void);


void AMPLCDV11_Receive(void);
void AMPLCDV11_Process(unsigned char* ReceDatabuffer,unsigned short datalen);
void GetManaData(unsigned char* Databuffer,unsigned short datalen);

void DisplayManaStaticTest1(void);
void DisplayManaStaticTest2(void);
void DisplayManaModel1(void);
void DisplayManaModel2(void);
void DisplayManaModel3(void);
void DisplayStyle(void);
void SetBackColor(unsigned short BKColor);
unsigned short GetBackColor(void);

unsigned short HW_SendBuff(enCCPortDef Port,unsigned char* pBuffer,unsigned short length);
//=================================时间函数ST==============================================================
void Tim_Server(void);


void HW_Configuration(void);

void AMPLCDV11GUI(void);
#endif
