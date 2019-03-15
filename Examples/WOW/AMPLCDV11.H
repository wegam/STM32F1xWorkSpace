#ifndef __AMPLCDV11_H
#define __AMPLCDV11_H


#include	"AMP_PHY.H"

#include "GT32L32M0180.H"
#include "ST7789V.H"
#include "STM32_USART.H"
#include "SWITCHID.H"

#define	BackColorStartAddr	0x0801F800		//原点值在MCU内部FLASH的存储地址126K地址，按128Kflash应用

#define	SelectModel	6

#if 1==SelectModel		//DisplayManaStaticTest1();		//双显示效果演示
	#define DisplayClrColor			0xFFFF		//显示区域清屏颜色
	#define DisplayBackColor		0xFFFF		//默认字体底色
	#define DisplayFontColor		0x0000		//默认字体颜色
	
	
	#define DisplayNameBkColor	0xFFFF		//名称底色
	#define DisplayNameFtColor	0x054A		//名称颜色
	#define	DisplayNameFtSize		24				//名称字体大小
	
	#define DisplayByNameBkColor	0xB71C		//别名底色
	#define DisplayByNameFtColor	0x094A		//别名颜色
	#define	DisplayByNameFtSize		16				//别名字体大小
	
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
	#define DisplayEndX		ST7789V_V	
#elif 2==SelectModel		//DisplayManaStaticTest2();	//单显示效果演示
	#define DisplayClrColor			0xFFFF		//显示区域清屏颜色
	#define DisplayBackColor		0xFFFF		//默认字体底色
	#define DisplayFontColor		0x0000		//默认字体颜色
	
	
	#define DisplayNameBkColor	0xFFFF		//名称底色
	#define DisplayNameFtColor	0x054A		//名称颜色
	#define	DisplayNameFtSize		24				//名称字体大小
	
	#define DisplayByNameBkColor	0xB71C		//别名底色
	#define DisplayByNameFtColor	0x094A		//别名颜色
	#define	DisplayByNameFtSize		16				//别名字体大小
	
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
	#define DisplayEndX		ST7789V_V
#elif 3==SelectModel							//DisplayManaModel1();	//双显示--数量大号字体
	#define DisplayClrColor					0xFFFF		//显示区域清屏颜色
	#define DisplayBackColor				0xFFFF		//默认字体底色
	#define DisplayFontColor				0x0000		//默认字体颜色
	
	
	#define DisplayNameBkColor			0xFFFF		//名称底色
	#define DisplayNameFtColor			0x054A		//名称颜色
	#define	DisplayNameFtSize				24				//名称字体大小
	
	#define DisplayByNameBkColor		0xB71C		//别名底色
	#define DisplayByNameFtColor		0x094A		//别名颜色
	#define	DisplayByNameFtSize			16				//别名字体大小
	
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
	#define DisplayEndX		ST7789V_V	
	
#elif 4==SelectModel		//DisplayManaModel2();	//双显示--数量32号字体
	#define DisplayClrColor					0xFFFF		//显示区域清屏颜色
	#define DisplayBackColor				0xFFFF		//默认字体底色
	#define DisplayFontColor				0x0000		//默认字体颜色
	
	
	#define DisplayNameBkColor			0x1C9F		//名称底色
	#define DisplayNameFtColor			0x0000		//名称颜色
	#define	DisplayNameFtSize				24				//名称字体大小
	
	#define DisplayByNameBkColor		0xB71C		//别名底色
	#define DisplayByNameFtColor		0x094A		//别名颜色
	#define	DisplayByNameFtSize			16				//别名字体大小
	
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
	#define DisplayEndX		ST7789V_V	
#elif 5==SelectModel		//DisplayManaModel3();	//单显示--数量32号字体
	#define DisplayClrColor			0xFFFF		//显示区域清屏颜色
	#define DisplayBackColor		0xFFFF		//默认字体底色
	#define DisplayFontColor		0x0000		//默认字体颜色
	
	
	#define DisplayNameBkColor	0xFFFF		//名称底色
	#define DisplayNameFtColor	0x054A		//名称颜色
	#define	DisplayNameFtSize		24				//名称字体大小
	
	#define DisplayByNameBkColor		0xB71C		//别名底色
	#define DisplayByNameFtColor		0x094A		//别名颜色
	#define	DisplayByNameFtSize			16				//别名字体大小
	
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
	#define DisplayEndX		ST7789V_V
#else			//DisplayManaModel1();
	#define DisplayClrColor			0xFFFF		//显示区域清屏颜色
	#define DisplayBackColor		0xFFFF		//默认字体底色
	#define DisplayFontColor		0x0000		//默认字体颜色
	
	
	#define DisplayNameBkColor		0x07DF		//名称底色
	#define DisplayNameFtColor		0x054A		//名称颜色
	#define	DisplayNameFtSize			24				//名称字体大小
	
	#define DisplayByNameBkColor	0xFFFF		//别名底色
	#define DisplayByNameFtColor	0x0000		//别名颜色
	#define	DisplayByNameFtSize		16				//别名字体大小
	
	#define DisplaySpecBkColor		0xFFFF		//规格底色
	#define DisplaySpecFtColor		0x0000		//规格颜色
	#define	DisplaySpecFtSize			16				//规格字体大小
	
	#define DisplayNumBkColor			0x8145		//数量底色
	#define DisplayNumFtColor			0xFFFF		//数量颜色
	#define	DisplayNumFtSize			32				//数量字体大小
	
	#define DisplaySerialBkColor	0xFFFF		//序号底色
	#define DisplaySerialFtColor	0xFB00		//序号颜色
	#define	DisplaySerialFtSize		16				//序号字体大小
	
	#define DisplayCodeBkColor		0xFFFF		//物料编码底色
	#define DisplayCodeFtColor		0x0000		//物料编码颜色
	#define	DisplayCodeFtSize			16				//物料编码字体大小
	
	#define DisplayVenderBkColor	0xFFFF		//厂家名称底色
	#define DisplayVenderFtColor	0x0000		//厂家名称颜色
	#define	DisplayVenderFtSize		16				//厂家名称字体大小
	
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
	#define DisplayEndX		ST7789V_V
	
#endif

#define	DspMaxNameTypeCount	30	//最大接收名字类型数量
#define	FresPageTime	2000			//页面刷新时间--ms
#define	AMPLcdMaxStringLen			256-9

//-----------------------------------LCD显示相关结构体
typedef struct _Mana						//耗材数据结构体，名称，规格，数量使用相同的结构体
{
	unsigned char 	type;					//类型：0x01-耗材名称，0x02-耗材规格，0x03-耗材数量,0x04-别名，0x05-厂家名称，0x06-耗材编码，0x07-数量单位
	unsigned char 	len;					//参数长度，String数据长度--字节单位
	unsigned char		String[AMPLcdMaxStringLen];		//字体缓存，如果是数量类型则存数值，如果是改背景色时，此为空，如果是名称或者规格时，存放字符数据GBK码
}ManaDef;
typedef struct _DisplayData			//显示数据结构体
{
	unsigned char 	Serial;					//显示序号	
	unsigned char 	Num;						//物品名称字符串长度
	
	
	unsigned char 	LenName;				//物品名称字符串长度
	unsigned char 	LenSpec;				//物品规格字符串长度
	unsigned char 	LenNum;					//数量长度/位数	
	unsigned char 	LenByName;			//别名字符串长度	
	unsigned char 	LenVender;			//厂家名称字符串长度
	unsigned char 	LenCode;				//编码字符串长度
	unsigned char 	LenUnit;				//数量单位字符串长度
	
	
	unsigned char 	OffsetName;			//物品名称字符串长度
	unsigned char 	OffsetSpec;			//物品规格字符串长度
	unsigned char 	OffsetNum;			//数量长度/位数	
	unsigned char 	OffsetByName;		//别名字符串长度	
	unsigned char 	OffsetVender;		//厂家名称字符串长度
	unsigned char 	OffsetCode;			//编码字符串长度
	unsigned char 	OffsetUnit;			//数量单位字符串长度
	//----------------字符串数据
	unsigned char		String[AMPLcdMaxStringLen];		//名字和规格字符串缓存，名字在前
}DisplayDataDef;
typedef struct _DisplayConf					//显示基本参数
{	
	unsigned short	WinNameBkColor;		//名称底色
	unsigned short	WinNameFtColor;		//名称颜色
	unsigned short	WinNameFtSize;		//名称字体大小
	
	unsigned short	WinByNameBkColor;		//名称底色
	unsigned short	WinByNameFtColor;		//名称颜色
	unsigned short	WinByNameFtSize;		//名称字体大小
	
	unsigned short 	WinSpecBkColor;		//规格底色
	unsigned short 	WinSpecFtColor;		//规格颜色
	unsigned short	WinSpecFtSize;		//规格字体大小
	
	unsigned short 	WinNumBkColor;		//数量底色
	unsigned short 	WinNumFtColor;		//数量颜色
	unsigned short	WinNumFtSize;			//数量字体大小
	
	unsigned short 	WinSerialBkColor;	//序号底色
	unsigned short 	WinSerialFtColor;	//序号颜色
	unsigned short	WinSerialFtSize;	//序号字体大小
	
	unsigned short 	WinCodeBkColor;		//物料编码底色
	unsigned short 	WinCodeFtColor;		//物料编码颜色
	unsigned short	WinCodeFtSize;		//物料编码字体大小
	
	unsigned short 	WinVenderBkColor;		//厂家名称底色
	unsigned short 	WinVenderFtColor;		//厂家名称颜色
	unsigned short	WinVenderFtSize;		//厂家名称字体大小
	
	unsigned short 	WinTitleBkColor;		//标题底色
	unsigned short 	WinTitleFtColor;		//标题颜色
	unsigned short 	WinTitleSize;				//标题字体大小
	
	unsigned short 	WinSeparBkColor;		//分隔线颜色
	unsigned short 	WinSeparWidth;			//分隔线宽度
	
	unsigned short	WinBackColor;			//默认字体底色
	unsigned short	WinFontColor;			//默认字体颜色
	
	unsigned short 	WinTopStartY;
	unsigned short 	WinTopEndY;
	unsigned short 	WinBotStartY;
	unsigned short 	WinBotEndY;
	
	unsigned short 	WinStartX;
	unsigned short 	WinEndX;
}DisplayConfDef;
typedef struct _DisplayInfo			//显示基本参数
{
	unsigned char 	Total;				//接收到的物品信息数量
	unsigned char 	Serial;				//当前显示序号
	
	unsigned char		LineCoName;		//名称占用列数x
	unsigned char		RowCoName;		//名称占用列数y
	
	unsigned char		LineCoByName;	//别名占用列数x
	unsigned char		RowCoByName;	//别名占用列数y
	
	unsigned char		LineCoSpec;		//规格占用列数x
	unsigned char		RowCoSpec;		//规格占用行数y
	
	unsigned char		LineCoNum;		//数量占用列数x
	unsigned char		RowCoNum;			//数量占用行数y
	
	unsigned char		LineCoCode;		//编码占用列数x
	unsigned char		RowCoCode;		//编码占用行数y
	
	unsigned char		LineCoVender;		//厂家占用列数x
	unsigned char		RowCoVender;		//厂家占用行数y
	
	unsigned short	ValidX;				//x轴有效显示区域
	unsigned short	ValidY;				//Y轴有效显示区域
	
	unsigned short	StartX;				//当前显示X起始点
	unsigned short	EndX;					//当前显示X终止点
	
	unsigned short	StartY;				//当前显示Y起始点
	unsigned short	EndY;					//当前显示Y终止点
}DisplayInfoDef;


typedef struct _Display		//显示
{
	sST7789VDef			LcdPort;			//LCD
	SPIDef 					SpiPort;			//字库
	DisplayDataDef 	DisplayArry[DspMaxNameTypeCount];	//显示内容
	
	DisplayConfDef	WinConf;			//显示配置
	DisplayInfoDef	WinInfo;			//显示参数
	
	unsigned char 	ReceivedManaCount;	//接收到的物品信息数量
	unsigned char 	DisplaySerial;			//当前显示序号
	unsigned short 	DisplayNextStartX;	//当前显示序号
	unsigned short 	DisplayNextStartY;	//当前显示序号
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
void DisplayManaModel6(void);


void DisplaySetInfo(const DisplayDataDef DisplayData);		//设置显示参数及清屏
void DisplayName(const DisplayDataDef DisplayData);				//显示别名和名称
void DisplayByName(const DisplayDataDef DisplayData);			//显示别名
void DisplayVender(const DisplayDataDef DisplayData);			//显示厂家名称
void DisplaySpec(const DisplayDataDef DisplayData);				//显示规格
void DisplayCode(const DisplayDataDef DisplayData);				//显示编码
void DisplayNumber(const DisplayDataDef DisplayData);			//显示数量和单位

void SetBackColor(unsigned short BKColor);
unsigned short GetBackColor(void);

unsigned short HW_SendBuff(enCCPortDef Port,unsigned char* pBuffer,unsigned short length);
//=================================时间函数ST==============================================================



void HW_Configuration(void);
void DataInitialize(void);		//数据初始化

void AMPLCDV11GUI(void);
#endif
