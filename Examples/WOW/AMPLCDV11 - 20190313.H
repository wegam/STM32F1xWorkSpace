#ifndef __AMPLCDV11_H
#define __AMPLCDV11_H


#include	"AMP_PHY.H"

#include "GT32L32M0180.H"
#include "ST7789V.H"
#include "STM32_USART.H"
#include "SWITCHID.H"

#define	BackColorStartAddr	0x0801F800		//原点值在MCU内部FLASH的存储地址126K地址，按128Kflash应用

#define	SelectModel	4

#if 1==SelectModel		//DisplayManaStaticTest1();		//双显示效果演示
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
#elif 2==SelectModel		//DisplayManaStaticTest2();	//单显示效果演示
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
	#define DisplayTitleSize			16				//标题字体大小
	
	#define DisplaySeparBkColor		0x8450		//分隔线颜色
	#define DisplaySeparWidth	2							//分隔线宽度
	
	#define DisplayTopStartY	48
	#define DisplayTopEndY		8	
	#define DisplayBotStartY	ST7789V_H-48
	#define DisplayBotEndY		ST7789V_H
	
	
	
	#define DisplayStartX	2
	#define DisplayEndX		2
#elif 3==SelectModel							//DisplayManaModel1();	//双显示--数量大号字体
	#define DisplayClrColor					0xFFFF		//显示区域清屏颜色
	#define DisplayBackColor				0xFFFF		//默认字体底色
	#define DisplayFontColor				0x0000		//默认字体颜色
	
	
	#define DisplayNameBkColor			0xFFFF		//名称底色
	#define DisplayNameFtColor			0x054A		//名称颜色
	#define	DisplayNameFtSize				24				//名称字体大小
	
	#define DisplaySpecBkColor			0xFFFF		//规格底色
	#define DisplaySpecFtColor			0x5ACA		//规格颜色
	#define	DisplaySpecFtSize				16				//规格字体大小
	
	#define DisplayNumBkColor				0x5902		//数量底色
	#define DisplayNumFtColor				0x07DF		//数量颜色
	#define	DisplayNumFtSize				48				//数量字体大小
	
	#define DisplaySerialBkColor		0xFFFF		//数量底色
	#define DisplaySerialFtColor		0xFB00		//数量颜色
	#define	DisplaySerialFtSize			16				//数量字体大小
	
	#define DisplayCodeBkColor			0xFFFF		//物料编码底色
	#define DisplayCodeFtColor			0x5ACA		//物料编码颜色
	#define	DisplayCodeFtSize				16				//物料编码字体大小
	
	#define DisplayVenderBkColor		0xFFFF		//厂家名称底色
	#define DisplayVenderFtColor		0x5ACA		//厂家名称颜色
	#define	DisplayVenderFtSize			16				//厂家名称字体大小
	
	#define DisplayTitleBkColor			0x865D		//标题底色
	#define DisplayTitleFtColor			0x0000		//标题颜色
	#define DisplayTitleSize				16				//标题字体大小
	
	#define DisplaySeparBkColor			0x8450		//分隔线颜色
	#define DisplaySeparWidth				2					//分隔线宽度
	
	#define DisplayTopStartY				16
	#define DisplayTopEndY					8	
	#define DisplayBotStartY				ST7789V_H-8
	#define DisplayBotEndY					ST7789V_H	
	
	#define DisplayStartX	2
	#define DisplayEndX		2	
	
#elif 4==SelectModel		//DisplayManaModel2();	//双显示--数量32号字体
	#define DisplayClrColor					0xFFFF		//显示区域清屏颜色
	#define DisplayBackColor				0xFFFF		//默认字体底色
	#define DisplayFontColor				0x0000		//默认字体颜色
	
	
	#define DisplayNameBkColor			0xFFFF		//名称底色
	#define DisplayNameFtColor			0x054A		//名称颜色
	#define	DisplayNameFtSize				24				//名称字体大小
	
	#define DisplaySpecBkColor			0xFFFF		//规格底色
	#define DisplaySpecFtColor			0x5ACA		//规格颜色
	#define	DisplaySpecFtSize				16				//规格字体大小
	
	#define DisplayNumBkColor				0x5902		//数量底色
	#define DisplayNumFtColor				0x07DF		//数量颜色
	#define	DisplayNumFtSize				32				//数量字体大小
	
	#define DisplaySerialBkColor		0xFFFF		//数量底色
	#define DisplaySerialFtColor		0xFB00		//数量颜色
	#define	DisplaySerialFtSize			16				//数量字体大小
	
	#define DisplayCodeBkColor			0xFFFF		//物料编码底色
	#define DisplayCodeFtColor			0x5ACA		//物料编码颜色
	#define	DisplayCodeFtSize				16				//物料编码字体大小
	
	#define DisplayVenderBkColor		0xFFFF		//厂家名称底色
	#define DisplayVenderFtColor		0x5ACA		//厂家名称颜色
	#define	DisplayVenderFtSize			16				//厂家名称字体大小
	
	#define DisplayTitleBkColor			0x865D		//标题底色
	#define DisplayTitleFtColor			0x0000		//标题颜色
	#define DisplayTitleSize				16				//标题字体大小
	
	#define DisplaySeparBkColor			0x8450		//分隔线颜色
	#define DisplaySeparWidth				2					//分隔线宽度
	
	#define DisplayTopStartY	24
	#define DisplayTopEndY		8	
	#define DisplayBotStartY	ST7789V_H-16
	#define DisplayBotEndY		ST7789V_H	
	
	#define DisplayStartX	2
	#define DisplayEndX		2	
#elif 5==SelectModel		//DisplayManaModel3();	//单显示--数量32号字体
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
	
	#define DisplayTopStartY	48
	#define DisplayTopEndY		8	
	#define DisplayBotStartY	ST7789V_H-48
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
#define	AMPLcdMaxStringLen			256-9

//-----------------------------------LCD显示相关结构体
typedef struct _DisplayData			//显示数据结构体
{
	unsigned char 	Serial;					//显示序号
	
	unsigned char 	Num;						//显示数量
	unsigned char 	NameLen;				//物品名称字符串长度
	unsigned char 	byNameLen;			//别名字符串长度
	unsigned char 	SpecLen;				//物品规格字符串长度
	unsigned char 	VenderLen;			//厂家名称字符串长度
	unsigned char 	CodeLen;				//编码字符串长度
	unsigned char 	UnitLen;				//数量单位符串长度
	//----------------字符串数据
	unsigned char		String[AMPLcdMaxStringLen];		//名字和规格字符串缓存，名字在前
}DisplayDataDef;
typedef struct _Mana						//耗材数据结构体，名称，规格，数量使用相同的结构体
{
	unsigned char 	type;					//类型：01-耗材名称，02-耗材规格，03-耗材数量,04-别名，05-厂家名称，06-耗材编码，07-数量单位
	unsigned char 	len;					//参数长度，String数据长度--字节单位
	unsigned char		String[AMPLcdMaxStringLen];		//字体缓存，如果是数量类型则存数值，如果是改背景色时，此为空，如果是名称或者规格时，存放字符数据GBK
}ManaDef;


typedef struct _Display		//显示
{
	sST7789VDef			LcdPort;			//LCD
	SPIDef 					SpiPort;			//字库
	DisplayDataDef 	DisplayArry[DspMaxNameTypeCount];	//显示内容
	
	unsigned char 	ReceivedManaCount;	//接收到的物品信息数量
	unsigned char 	DisplaySerial;			//当前显示序号
}DisplayDef;
typedef struct _Comm			//通讯
{
	RS485Def 				RS485Port;   	//RS485通讯
	unsigned	char	Rxd[gDatasize];	//接收
	unsigned	char	Txd[gDatasize];	//发送
	unsigned	short TxLen;					//需要发送的数量
}CommDef;
typedef struct _Variable	//运行相关变量
{
	unsigned char 	AddrCab;		//柜地址
	unsigned char 	AddrLay;		//层地址
	unsigned char 	AddrSeg;		//位地址
	unsigned char 	DisplaySerial;			//当前显示序号
	unsigned short 	PowerOnTime;				//上电时间
	
}VarDataDef;

	
//#define testmodel

typedef struct _sAmpLcd
{
	DisplayDef	Display;
	CommDef			Comm;					//通讯
	SwitchDef 	sSwitch;			//拔码开关
	VarDataDef	Sys;					//其它变量数据
}sAmpLcdDef;


extern stAMPProdef   AMPPro;

void AMPLCDV11_Configuration(void);
void AMPLCDV11_Server(void);

void AMPLCDV11_Loop(void);


void AMPLCDV11_Receive(void);
void AMPLCDV11_Send(void);
void AMPLCDV11_Ack(void);
void AMPLCDV11_Process(unsigned char* ReceDatabuffer,unsigned short datalen);
void GetManaData(unsigned char* Databuffer,unsigned short datalen);

void DisplayManaStaticTest1(void);		//双显示效果演示
void DisplayManaStaticTest2(void);		//单显示效果演示
void DisplayManaModel1(void);					//双显示--数量48号字体
void DisplayManaModel2(void);					//双显示--数量32号字体
void DisplayManaModel3(void);					//单显示--数量32号字体

void SetBackColor(unsigned short BKColor);
unsigned short GetBackColor(void);

unsigned short HW_SendBuff(enCCPortDef Port,unsigned char* pBuffer,unsigned short length);
//=================================时间函数ST==============================================================



void HW_Configuration(void);

void AMPLCDV11GUI(void);
#endif
