/**************************************************************************************************
* Copyright (C), 1997-$(Year),  HAICHUANG IOT Tech. Co., Ltd.
* 文件<$(filename)>
* 模块描述 :	定义、功能、说明
* 历史修改记录
*     <主要修改者>  <时间>   <版本 >   <说明>
*     xlyan        $(Date)   1.0.0    创建文件
**************************************************************************************************/
#include "ILI9326.h"
#include "LCD.H"

#include "STM32_GPIO.H"

#include	"stdio.h"			//用于printf
#include	"string.h"		//用于printf
#include	"stdarg.h"		//用于获取不确定个数的参数
#include	"stdlib.h"		//malloc动态申请内存空间

static LCDDef	*ILI9326	=	NULL;		//内部驱动使用，不可删除

#define	ILI9326_CS_HIGH		(ILI9326->Port.sCS_PORT->BSRR	= ILI9326->Port.sCS_Pin)
#define	ILI9326_CS_LOW		(ILI9326->Port.sCS_PORT->BRR	=	ILI9326->Port.sCS_Pin)

#define	ILI9326_DC_HIGH		(ILI9326->Port.sDC_PORT->BSRR	= ILI9326->Port.sDC_Pin)
#define	ILI9326_DC_LOW		(ILI9326->Port.sDC_PORT->BRR	= ILI9326->Port.sDC_Pin)

#define	ILI9326_WR_HIGH		(ILI9326->Port.sWR_PORT->BSRR	= ILI9326->Port.sWR_Pin)
#define	ILI9326_WR_LOW		(ILI9326->Port.sWR_PORT->BRR	= ILI9326->Port.sWR_Pin)

#define	ILI9326_RD_HIGH		(ILI9326->Port.sRD_PORT->BSRR	= ILI9326->Port.sRD_Pin)
#define	ILI9326_RD_LOW		(ILI9326->Port.sRD_PORT->BRR	= ILI9326->Port.sRD_Pin)

#define	ILI9326_RST_HIGH	(ILI9326->Port.sREST_PORT->BSRR	= ILI9326->Port.sREST_Pin)
#define	ILI9326_RST_LOW		(ILI9326->Port.sREST_PORT->BRR	= ILI9326->Port.sREST_Pin)

#define	ILI9326_TE_HIGH		(ILI9326->Port.sTE_PORT->BSRR	= ILI9326->Port.sTE_Pin)
#define	ILI9326_TE_LOW		(ILI9326->Port.sTE_PORT->BRR	= ILI9326->Port.sTE_Pin)

#define	ILI9326_BL_HIGH		(ILI9326->Port.sBL_PORT->BSRR	= ILI9326->Port.sBL_Pin)
#define	ILI9326_BL_LOW		(ILI9326->Port.sBL_PORT->BRR	= ILI9326->Port.sBL_Pin)

#define ILI9326_DATABUS_PORT	(ILI9326->Port.sDATABUS_PORT)
#define ILI9326_DATABUS_Pin		(ILI9326->Port.sDATABUS_Pin)

#define	ILI9326Set(n)	ILI9326_##n##_HIGH
#define	ILI9326Crl(n)	ILI9326_##n##_LOW
/*******************************************************************************
* 函数名			:	function
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
*******************************************************************************/
unsigned short ILI9326_Initialize(void*	pInfo)
{
	//
	static unsigned short	DeviceCode	=	0;
	LCDPortDef*	Port	=	NULL;
	if(NULL==	pInfo)
		return 0;
	ILI9326		=	(LCDDef*)pInfo;		//指针指向
	Port	=	&ILI9326->Port;
	
	//==========================GPIO配置
	GPIO_Configuration_OPP50	(Port->sBL_PORT,				Port->sBL_Pin);					//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度2MHz----V20170605
	GPIO_Configuration_OPP50	(Port->sRD_PORT,				Port->sRD_Pin);					//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度2MHz----V20170605
	GPIO_Configuration_OPP50	(Port->sREST_PORT,			Port->sREST_Pin);				//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度2MHz----V20170605
	GPIO_Configuration_OPP50	(Port->sDC_PORT,				Port->sDC_Pin);					//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度2MHz----V20170605
	GPIO_Configuration_OPP50	(Port->sWR_PORT,				Port->sWR_Pin);					//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度2MHz----V20170605
	GPIO_Configuration_OPP50	(Port->sCS_PORT,				Port->sCS_Pin);					//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度2MHz----V20170605
	GPIO_Configuration_OPP50	(Port->sTE_PORT,				Port->sTE_Pin);					//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度2MHz----V20170605
	GPIO_Configuration_OPP50	(Port->sDATABUS_PORT,		Port->sDATABUS_Pin);		//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度2MHz----V20170605
	
	DeviceCode	=	ILI9326_ReadRegister(ILI9326_R000_IR);
	if(ILI9326ID	!=	DeviceCode)
	{
		return 0;		//识别失败
	}
	
	//==========================检查背景色与画笔色是否相同
	if(ILI9326->Data.PColor	==	ILI9326->Data.BColor)
	{
		ILI9326->Data.PColor	=	ILI9326->Data.BColor^0xFFFF;
	}
	
	ILI9326->Data.MaxH	=	ILI9326_H;					//最大水平宽度
	ILI9326->Data.MaxV	=	ILI9326_V;					//最大垂直高度
	
	//==========================接口函数
//	ILI9326->Display.WriteAddress		=	ILI9326_SetWindowAddress;
	ILI9326->Display.PowerOn				=	ILI9326_PowerOn;
	ILI9326->Display.DispOff				=	ILI9326_PowerOff;
	
	ILI9326->Display.DrawDot				=	ILI9326_DrawDot;
	ILI9326->Display.DrawLine				=	ILI9326_DrawLine;
	ILI9326->Display.DrawCircle			=	ILI9326_DrawCircle;
	ILI9326->Display.DrawRectangle	=	ILI9326_DrawRectangle;
	
	ILI9326->Display.Fill						=	ILI9326_Fill;
	ILI9326->Display.Clean					=	ILI9326_Clean;
	ILI9326->Display.SetBackground	=	ILI9326_SetBackground;
	
	ILI9326->Display.ShowChar				=	ILI9326_ShowChar;
	ILI9326->Display.ShowWord				=	ILI9326_ShowWord;
	
	ILI9326_PowerOn();
	ILI9326_Clean(ILI9326->Data.BColor);
	
	ILI9326Set(BL);
	return DeviceCode;		//配置成功
}
/*******************************************************************************
* 函数名			:	LCD_Reset
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
void ILI9326_Reset(void)
{
	ILI9326Set(RST);
	LCD_DelaymS(5);				//SysTick延时nmS
	ILI9326Crl(RST);;
	LCD_DelaymS(5);				//SysTick延时nmS
	ILI9326Set(RST);
	LCD_DelaymS(10);				//SysTick延时nmS
}
/*******************************************************************************
* 函数名			:	ILI9326_ReadData
* 功能描述		:	写指定寄存器 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
unsigned short ILI9326_ReadData(void)
{
	unsigned short Data	=	0;
#if	1	//Bus16Bit
	ILI9326Crl(RD);	//LCD_RD_LOW;
	Data	=	ILI9326_DATABUS_PORT->IDR;
	ILI9326Set(RD);	//LCD_RD_HIGH;
#else	
	ILI9326Crl(RD);	//LCD_RD_LOW;
	Data	=	ILI9326_DATABUS_PORT->IDR;
	ILI9326et(RD);	//LCD_RD_HIGH;
	
	Data	<<=8;
	
	ILI9326Crl(RD);	//LCD_RD_LOW;
	Data	|=	ILI9326_DATABUS_PORT->IDR;
	ILI9326Set(RD);	//LCD_RD_HIGH;
#endif	
	return Data;
}
/*******************************************************************************
* 函数名			:	ILI9326_ReadRegister
* 功能描述		:	读指定寄存器 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
unsigned short ILI9326_ReadRegister(unsigned	short	Index)
{
	unsigned short Data	=	0;
	ILI9326Crl(CS);	//LCD_CS_LOW;
	//---------------------Write Index
	ILI9326_WriteAddr(Index);
	//---------------------Read Data
	GPIO_Configuration_IPU	(ILI9326_DATABUS_PORT,ILI9326_DATABUS_Pin);			//将GPIO相应管脚配置为上拉输入模式----V20170605
	Data	=	ILI9326_ReadData();
	ILI9326Set(CS);	//LCD_CS_HIGH;
	GPIO_Configuration_OPP50	(ILI9326_DATABUS_PORT,ILI9326_DATABUS_Pin);		//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度2MHz----V20170605	
	return Data;
}
/*******************************************************************************
* 函数名			:	ILI9326_WriteData
* 功能描述		:	写指定寄存器 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
void ILI9326_WriteData(unsigned	short	Data)
{
#if	1	//Bus16Bit
	ILI9326Crl(WR);	//LCD_WR_LOW;
	ILI9326_DATABUS_PORT->ODR = Data;
	ILI9326Set(WR);	//LCD_WR_HIGH;
#else
	ILI9326Crl(WR);	//LCD_WR_LOW;
	ILI9326_DATABUS_PORT->ODR = Data>>8;
	ILI9326Set(WR);	//LCD_WR_HIGH;
	
	ILI9326Crl(WR);	//LCD_WR_LOW;
	ILI9326_DATABUS_PORT->ODR = Data&0xFF;
	ILI9326Set(WR);	//LCD_WR_HIGH;
#endif
}
/*******************************************************************************
* 函数名			:	ILI9326_WriteAddr
* 功能描述		:	写指定寄存器 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
void ILI9326_WriteAddr(unsigned	short	Addr)
{
	ILI9326Crl(DC);	//LCD_DC_LOW;		//RS
	ILI9326_WriteData(Addr);
	ILI9326Set(DC);	//LCD_DC_HIGH;	//RS
}
/*******************************************************************************
* 函数名			:	ILI9326_WriteIndex
* 功能描述		:	写指定寄存器 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
void ILI9326_WriteIndex(unsigned	short	Index)
{
	ILI9326Crl(CS);	//LCD_CS_LOW;	
	ILI9326_WriteAddr(Index);
	ILI9326Set(CS);	//LCD_CS_HIGH;
}
/*******************************************************************************
* 函数名			:	ILI9326_WriteRegister
* 功能描述		:	写指定寄存器 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
void ILI9326_WriteRegister(unsigned	short	Addr,unsigned short Data)
{
	ILI9326Crl(CS);	//LCD_CS_LOW;	
	//---------------------Write Index
	ILI9326_WriteAddr(Addr);
	//---------------------Write Data
	ILI9326_WriteData(Data);	
	ILI9326Set(CS);	//LCD_CS_HIGH;	
}
/*******************************************************************************
* 函数名			:	ILI9326_WriteCommand
* 功能描述		:	读指定寄存器 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
void ILI9326_WriteCommand(unsigned	short	Index,unsigned short Cmd)
{
	ILI9326_WriteRegister(Index,Cmd);
}
/*******************************************************************************
* 函数名			:	R61509V_WriteGRAM
* 功能描述		:	写指定寄存器 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
void ILI9326_WriteGRAM(unsigned	short* RAM,unsigned long length)
{
	unsigned	long	i	=	0;
	ILI9326Crl(CS);	//LCD_CS_LOW;
	ILI9326_WriteAddr(ILI9326_R202_GDRW);
	for(i=0;i<length;i++)
	{
		ILI9326_WriteData(RAM[i]);
	}
	ILI9326Set(CS);	//LCD_CS_HIGH;
}
/*******************************************************************************
* 函数名			:	R61509V_WriteGRAM
* 功能描述		:	写指定寄存器 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
void ILI9326_ReadGRAM(unsigned	short* RAM,unsigned long length)
{
	unsigned	long	i	=	0;
	ILI9326Crl(CS);	//LCD_CS_LOW;
	ILI9326_WriteAddr(ILI9326_R202_GDRW);
	GPIO_Configuration_IPU	(ILI9326_DATABUS_PORT,ILI9326_DATABUS_Pin);			//将GPIO相应管脚配置为上拉输入模式----V20170605
	for(i=0;i<length;i++)
	{
		RAM[i]=ILI9326_ReadData();
	}
	ILI9326Set(CS);	//LCD_CS_HIGH;
	GPIO_Configuration_OPP50	(ILI9326_DATABUS_PORT,ILI9326_DATABUS_Pin);		//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度2MHz----V20170605
}




/**************************************************************************************************
* [Function] LCD_DispOff:  关闭LCD显示( 黑屏?)
* [No param]
**************************************************************************************************/
void ILI9326_DispOff( void )
{
	ILI9326_WriteCommand( ILI9326_R007_DC1, 0x0000 );
}
/**************************************************************************************************
* [Function] LCD_PowerOn: LCD 上电并初始化相关寄存器
* [No param]
**************************************************************************************************/
void ILI9326_PowerOn( void )
{
	u32 dtime=5000;
	
//	void(*ILI9326_WriteCMD)(unsigned short Index,unsigned short Command)	=	ILI9326->Display.WriteCommand;//LcdDisplay.WriteCommand
	void(*ILI9326_WriteCMD)(unsigned short Index,unsigned short Command);
	
  void(*DelaymS)(unsigned long xms) = LCD_DelaymS;
	
	ILI9326_WriteCMD	=	ILI9326_WriteCommand;
//  LCDSYS->Display.DelaymS
//	ILI9326_WriteCMD	=	sILI9326->Display.WriteCommand;
	
	ILI9326_Reset();
/************** Start Initial Sequence ********** // */
	ILI9326_WriteCMD( ILI9326_R702_SIT1, 	0x3008 );/* Set internal timing, don’t change this value */
	ILI9326_WriteCMD( ILI9326_R705_SIT2, 	0x0036 );/* Set internal timing, don’t change this value */
	ILI9326_WriteCMD( ILI9326_R70B_SIT3, 	0x1213 );/* Set internal timing, don’t change this value */

	ILI9326_WriteCMD( ILI9326_R001_DOC, 	0x0100 );/* set SS and SM bit */
	ILI9326_WriteCMD( ILI9326_R002_DWC, 	0x0100 );/* set 1 line inversion */
	ILI9326_WriteCMD( ILI9326_R003_EM, 		0x1030 );/* set GRAM write direction and BGR=1. */
	ILI9326_WriteCMD( ILI9326_R008_DC2, 	0x0202 );/* set the back porch and front porch */
	ILI9326_WriteCMD( ILI9326_R009_DC3, 	0x0000 );/* set non-display area refresh cycle ISC[3:0] */
	ILI9326_WriteCMD( ILI9326_R00C_EDIC1,	0x0000 );/* RGB interface setting */
	ILI9326_WriteCMD( ILI9326_R00F_EDIC2,	0x0000 );/* RGB interface polarity */

	/**************Power On sequence **************** // */
	ILI9326_WriteCMD( ILI9326_R100_PC1, 	0x0000 );/* SAP, BT[3:0], AP, DSTB, SLP, STB */
	ILI9326_WriteCMD( ILI9326_R102_PC3, 	0x0000 );/* VREG1OUT voltage */
	ILI9326_WriteCMD( ILI9326_R103_PC4, 	0x0000 );/* VDV[4:0] for VCOM amplitude */
	
	DelaymS( 100 );
	
	ILI9326_WriteCMD( ILI9326_R100_PC1, 	0x1190 ); /* SAP, BT[3:0], AP, DSTB, SLP, STB */
	ILI9326_WriteCMD( ILI9326_R101_PC2, 	0x0227 ); /* DC1[2:0], DC0[2:0], VC[2:0] */
	
	DelaymS( 100 );
	
	ILI9326_WriteCMD( ILI9326_R102_PC3, 	0x01BD ); /* VREG1OUT voltage */
	
	DelaymS( 100 );
	
	ILI9326_WriteCMD( ILI9326_R103_PC4,		0x2D00 );/* VDV[4:0] for VCOM amplitude */
	ILI9326_WriteCMD( ILI9326_R281_VHV, 	0x000E );/* VCM[5:0] for VCOMH */
	
	
	ILI9326_WriteCMD( ILI9326_R200_HA, 		0x0000 );/* GRAM horizontal Address */
	ILI9326_WriteCMD( ILI9326_R201_VA, 		0x0000 );/* GRAM Vertical Address */

	/* ----------- Adjust the Gamma    Curve ----------// */
	ILI9326_WriteCMD( ILI9326_R300_YC1,		0x0000 );
	ILI9326_WriteCMD( ILI9326_R301_YC2, 	0x0707 );
	ILI9326_WriteCMD( ILI9326_R302_YC3, 	0x0606 );
	ILI9326_WriteCMD( ILI9326_R303_YC4, 	0x0000 );
	ILI9326_WriteCMD( ILI9326_R304_YC5, 	0x0D00 );
	ILI9326_WriteCMD( ILI9326_R305_YC6, 	0x0706 );
	ILI9326_WriteCMD( ILI9326_R306_YC7, 	0x0005 );
	ILI9326_WriteCMD( ILI9326_R307_YC8, 	0x0007 );

	ILI9326_WriteCMD( ILI9326_R308_YC9, 	0x0000 );
	ILI9326_WriteCMD( ILI9326_R309_YC10, 	0x000A );

	/*------------------ Set GRAM area ---------------// */
	ILI9326_WriteCMD( ILI9326_R210_HSA, 	0x0000 );/* Horizontal GRAM Start Address */
	ILI9326_WriteCMD( ILI9326_R211_HEA, 	0x00EF );/* Horizontal GRAM End Address */
	ILI9326_WriteCMD( ILI9326_R212_VSA, 	0x0000 );/* Vertical GRAM Start Address */
	ILI9326_WriteCMD( ILI9326_R400_BINL, 	0x3100 );/*    / * Gate Scan Line 400 lines * / */
	ILI9326_WriteCMD( ILI9326_R401_BIDC, 	0x0001 );/* NDL,VLE, REV */
	ILI9326_WriteCMD( ILI9326_R404_BIVSC, 0x0000 );/* set scrolling line */

/*-------------- Partial Display Control ---------// */
	ILI9326_WriteCMD( ILI9326_R500_PTDP, 0x0000 );/*Partial Image 1 Display Position */
	ILI9326_WriteCMD( ILI9326_R501_PTSA, 0x0000 );/*Partial Image 1 RAM Start/End Address */
	ILI9326_WriteCMD( ILI9326_R502_PTEA, 0x0000 );/*Partial Image 1 RAM Start/End Address */
	ILI9326_WriteCMD( ILI9326_R503_PIDP, 0x0000 );/*Partial Image 2 Display Position */
	ILI9326_WriteCMD( ILI9326_R504_PIRS, 0x0000 );/*Partial Image 2 RAM Start/End Address */
	ILI9326_WriteCMD( ILI9326_R505_PIRE, 0x0000 );/*Partial Image 2 RAM Start/End Address */

/*-------------- Panel Control -------------------// */
	ILI9326_WriteCMD( ILI9326_R010_PIC1, 0x0010 );/*DIVI[1:0];RTNI[4:0] */
	ILI9326_WriteCMD( ILI9326_R011_PIC2, 0x0600 );/*NOWI[2:0];SDTI[2:0] */
	ILI9326_WriteCMD( ILI9326_R013_PIC4, 0x0002 );/*DIVE[1:0];RTNE[5:0] */

	ILI9326_WriteCMD( ILI9326_R007_DC1, 0x0173 );/* 262K color and display ON */
}
/**************************************************************************************************
* [Function] LCD_PowerOff:  关闭LCD 电源
* [No param]
**************************************************************************************************/
void ILI9326_PowerOff( void )
{
	LCD_BL_OFF;		//关背光
	ILI9326_WriteCommand( ILI9326_R009_DC3, 0 );	
}
/**************************************************************************************************
* [Function] LCD_SetDrawWindow:  LCD 屏显示扫描方式
* [param01]t_ILI9326_Rotate ScrnRotat: 相对于逐行从左到右 翻转角度值
* [param02]t_PixCfg PixCfg: 显示像素配置
* [param03]t_Point top_p: 顶点坐标
* [param04]u16 bottom_p: 底部坐标
**************************************************************************************************/
void ILI9326_SetWindowAddress( 
															unsigned short x1,		//水平起始点
															unsigned short y1,		//水平终止点
															unsigned short x2,		//垂直起始点
															unsigned short y2			//垂直终止点
															)
{
  void(*ILI9326_WriteCMD)(unsigned short Index,unsigned short Command)	=	ILI9326->Display.WriteCommand;//LcdDisplay.WriteCommand
	unsigned short MaxH,MaxV;
	unsigned short Model	=	0x5030;

	eRotate	Rotate	=	ILI9326->Flag.Rotate;
	
	MaxH	=	ILI9326->Data.MaxH;
	MaxV	=	ILI9326->Data.MaxV;
	
	switch(Rotate)
	{
		case 	Draw_Rotate_0D:
					ILI9326->Data.HSX	=	x1;
					ILI9326->Data.HEX	=	x2;
					ILI9326->Data.VSY	=	y1;
					ILI9326->Data.VEY	=	y2;	
					ILI9326->Data.HXA	=	ILI9326->Data.HSX;
					ILI9326->Data.VYA	=	ILI9326->Data.VSY;	
					Model	=	0x5030;
			break;
		case 	Draw_Rotate_90D:
					ILI9326->Data.HSX	=	y1;
					ILI9326->Data.HEX	=	y2;	
					ILI9326->Data.VSY	=	MaxV	-	x2	-	1;
					ILI9326->Data.VEY	=	MaxV	-	x1	-	1;	
					ILI9326->Data.HXA	=	ILI9326->Data.HSX;
					ILI9326->Data.VYA	=	ILI9326->Data.VEY;
					Model	=	0X5098;								//GRAM(Graphics RAM--图形内存) Data Write (R202h)准备写入
//					Model	=	0X5091;								//GRAM(Graphics RAM--图形内存) Data Write (R202h)准备写入
			break;
		case 	Draw_Rotate_180D:
					ILI9326->Data.HSX	=	MaxH	-	x2	-	1;
					ILI9326->Data.HEX	=	MaxH	-	x1	-	1;
					ILI9326->Data.VSY	=	MaxV	-	y2	-	1;
					ILI9326->Data.VEY	=	MaxV	-	y1	-	1;	
					ILI9326->Data.HXA	=	ILI9326->Data.HEX;
					ILI9326->Data.VYA	=	ILI9326->Data.VEY;	
					Model	=	0X5000;
			break;
		default:
					ILI9326->Data.HSX	=	MaxH	-	y2	-	1;
					ILI9326->Data.HEX	=	MaxH	-	y1	-	1;
					ILI9326->Data.VSY	=	x1;
					ILI9326->Data.VEY	=	x2;	
					ILI9326->Data.HXA	=	ILI9326->Data.HEX;
					ILI9326->Data.VYA	=	ILI9326->Data.VSY;
					Model	=	0X5028;
			break;
	}
	//======================================区域设置
	ILI9326_WriteCMD(ILI9326_R210_HSA,ILI9326->Data.HSX);		//Window Horizontal RAM Address Start(R210h)		//水平
	ILI9326_WriteCMD(ILI9326_R211_HEA,ILI9326->Data.HEX);		//Window Horizontal RAM Address End(R211h)			//水平
	ILI9326_WriteCMD(ILI9326_R212_VSA,ILI9326->Data.VSY);		//Window Vertical RAM Address Start (R212h)			//垂直
	ILI9326_WriteCMD(ILI9326_R213_VEA,ILI9326->Data.VEY);		//Window Vertical RAM Address End (R213h)				//垂直
	//======================================设置起始点
	ILI9326_WriteCMD( ILI9326_R200_HA, ILI9326->Data.HSX );
	ILI9326_WriteCMD( ILI9326_R201_VA, ILI9326->Data.VSY );
	//======================================设置写入模式
	ILI9326_WriteCMD( ILI9326_R003_EM, Model);
	//======================================启动写入
	ILI9326_WriteIndex( ILI9326_R202_GDRW );
}



//
//--------------------------------------------------------------GUI

/*******************************************************************************
*函数名			:	LCD_DrawPoint
*功能描述		:	画点
*输入				: 
*返回值			:	无
*******************************************************************************/
void ILI9326_DrawDot(
									unsigned short HSX,			//点X坐标*/
									unsigned short HSY,			//点Y坐标*/
									unsigned short Color		//点颜色*/	
								)
{
	ILI9326_SetWindowAddress(HSX,HSY,HSX,HSY);	//设置光标位置
	ILI9326_WriteGRAM(&Color,1);
}
/*******************************************************************************
*函数名		:	LCD_DrawLine
*功能描述	:	画线
*输入			: x1,y1:起点坐标
						x2,y2:终点坐标
*输出			:	无
*返回值		:	无
*例程			:
*******************************************************************************/
void ILI9326_DrawLine(
									unsigned short HSX, unsigned short HSY, 	//x1,y1:起点坐标
									unsigned short HEX, unsigned short HEY,		//x2,y2:终点坐标
									unsigned short Color					//颜色
)
{
	u16 t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance; 
	int incx,incy,uRow,uCol; 

	delta_x=HEX-HSX; //计算坐标增量 
	delta_y=HEY-HSY; 
	uRow=HSX; 
	uCol=HSY;
	
	if(delta_x>0)
		incx=1; //设置单步方向 
	else if(delta_x==0)
		incx=0;//垂直线 
	else
	{
		incx=-1;
		delta_x=-delta_x;
	}
		
	if(delta_y>0)
		incy=1; 
	else if(delta_y==0)
		incy=0;//水平线 
	else
		{incy=-1;delta_y=-delta_y;}
		
	if( delta_x>delta_y)
		distance=delta_x; 								//选取基本增量坐标轴 
	else
		distance=delta_y;
	
	for(t=0;t<distance+1;t++ )					//画线输出 
	{  
		ILI9326_DrawDot(uRow,uCol,Color);			//画点 
		xerr+=delta_x ; 
		yerr+=delta_y ; 
		if(xerr>distance) 
		{ 
			xerr-=distance; 
			uRow+=incx; 
		} 
		if(yerr>distance) 
		{ 
			yerr-=distance;
			uCol+=incy; 
		} 
	}
}
/**************************************************************************************************
* [Function] LCD_DrawCircle:  函数功能、注意事项等的描述
* [param01]t_Point point: description
* [param02]u16 R: description
* [param03]uint8_t Filled: description
* [param04]u16 color: description
**************************************************************************************************/
void ILI9326_DrawCircle(
												u16 x,u16 y,		//圆心坐标原点
												u16 r,					//半径
												u8 Filled,			//是否填充
												u16 color				//颜色
												)
{
	int a,b;
	int di;
	a=0;b=r;	  
	di=3-(r<<1);             //判断下个点位置的标志
	while(a<=b)
	{
		if(Filled)	//填充就画线
		{
			ILI9326_DrawLine(x,y,x-b,y-a,color);             //3           
			ILI9326_DrawLine(x,y,x+b,y-a,color);             //0           
			ILI9326_DrawLine(x,y,x-a,y+b,color);             //1       
			ILI9326_DrawLine(x,y,x-b,y-a,color);             //7           
			ILI9326_DrawLine(x,y,x-a,y-b,color);             //2             
			ILI9326_DrawLine(x,y,x+b,y+a,color);             //4               
			ILI9326_DrawLine(x,y,x+a,y-b,color);             //5
			ILI9326_DrawLine(x,y,x+a,y+b,color);             //6 
			ILI9326_DrawLine(x,y,x-b,y+a,color);             
			a++;
			//使用Bresenham算法画圆     
			if(di<0)
				di +=4*a+6;	  
			else
			{
				di+=10+4*(a-b);   
				b--;
			}
			ILI9326_DrawLine(x,y,x+a,y+b,color);				//AB 两个坐标画一条直线
		}
		else
		{
			ILI9326_DrawDot(x-b,y-a,color);             //3           
			ILI9326_DrawDot(x+b,y-a,color);             //0           
			ILI9326_DrawDot(x-a,y+b,color);             //1       
			ILI9326_DrawDot(x-b,y-a,color);             //7           
			ILI9326_DrawDot(x-a,y-b,color);             //2             
			ILI9326_DrawDot(x+b,y+a,color);             //4               
			ILI9326_DrawDot(x+a,y-b,color);             //5
			ILI9326_DrawDot(x+a,y+b,color);             //6 
			ILI9326_DrawDot(x-b,y+a,color);             
			a++;
			//使用Bresenham算法画圆     
			if(di<0)
				di +=4*a+6;	  
			else
			{
				di+=10+4*(a-b);   
				b--;
			}
				ILI9326_DrawDot(x+a,y+b,color);
		}
	}
}
/**************************************************************************************************
* [Function] LCD_DrawRectangle:  画一下矩形框
* [param01]t_Point top_p: 顶点坐标值
* [param02]t_Point botton_p : 地板坐标值
**************************************************************************************************/
void ILI9326_DrawRectangle(u16 x1,u16 y1,u16 x2,u16 y2,u16 color)
{
	ILI9326_DrawLine( x1, y1,	x1,	y2, color );
	ILI9326_DrawLine( x1, y1,	x2,	y1, color );
	ILI9326_DrawLine( x2, y1,	x2,	y2, color );
	ILI9326_DrawLine( x1, y2,	x2,	y2, color );
}
/*******************************************************************************
*函数名			:	ILI9326_Fill
*功能描述		:	在指定区域内填充指定颜色;区域大小:(xend-xsta)*(yend-ysta)
*输入				: 
*返回值			:	无
*******************************************************************************/
void ILI9326_Fill(
							unsigned short x1, unsigned short y1, 	//x1,y1:起点坐标
							unsigned short x2, unsigned short y2,		//x2,y2:终点坐标
							u16 Color
)
{          
	unsigned int x;
	unsigned int y;	
	ILI9326_SetWindowAddress(x1,y1,x2,y2);
	ILI9326_WriteIndex( ILI9326_R202_GDRW );
	ILI9326Crl(CS);	//LCD_CS_LOW;
	for(x=0;x<=x2-x1;x++)
	{
		for(y=0;y<=y2-y1;y++)
		{
			ILI9326_WriteData(Color);							//写数据
		}
	}	
	ILI9326Set(CS);	//LCD_CS_HIGH;
}
/*******************************************************************************
* 函数名			:	ILI9326_Clean
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
void ILI9326_Clean(u16 Color)	//清除屏幕函数
{
	unsigned short x,y;
	unsigned short HSX,HEX,HSY,HEY,MaxH,MaxV;
	unsigned long	length	=	0;
	eRotate	Rotate	=	ILI9326->Flag.Rotate;
	
	MaxH	=	ILI9326->Data.MaxH;
	MaxV	=	ILI9326->Data.MaxV;	
	switch(Rotate)
	{
		case 	Draw_Rotate_0D:
					HSX	=	0;
					HEX	=	MaxH-1;
					HSY	=	0;
					HEY	=	MaxV-1;
			break;
		case	Draw_Rotate_90D:
					HSX	=	0;
					HEX	=	MaxV-1;
					HSY	=	0;
					HEY	=	MaxH-1;
			break;
		case	Draw_Rotate_180D:
					HSX	=	0;
					HEX	=	MaxH-1;
					HSY	=	0;
					HEY	=	MaxV-1;
			break;
		default:
					HSX	=	0;
					HEX	=	MaxV-1;
					HSY	=	0;
					HEY	=	MaxH-1;
			break;			
	}	
	ILI9326_Fill(HSX,HSY,HEX,HEY,Color);
}
/**************************************************************************************************
* [Function] ILI9326_SetBackground:  设置背景颜色
* [param01]u16 BackColor: 背景颜色值
**************************************************************************************************/
void ILI9326_SetBackground(  u16 BackColor )
{
	ILI9326->Data.BColor	=	BackColor;
	ILI9326_Clean(BackColor);	//清除屏幕函数
}

//
//--------------------------------------------字符显示
//

/*******************************************************************************
* 函数名			:	function
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
*******************************************************************************/
void ILI9326_ShowChar(
										u16 x,			//x				:起点x坐标
										u16 y,			//y				:起点y坐标
										u8 font,		//font		:字体大小
										u16 color,	//字体颜色
										u8 num,			//num			:字节数
										u8 *Buffer	//Buffer	:显示的内容缓存
										
)		//高通字库测试程序
{
	u8 temp;
	u8 i=0,j=0;
	unsigned short x1=0,x2=0,y1=0,y2=0;
	unsigned short LCD_PEN_COLOR	=	0;   	//画笔色
	x1	=	x;
	y1	=	y;
	x2	=	x+font/2-1;		//
	y2	=	y+font-1;
	
	ILI9326_SetWindowAddress(x1,y1,x2,y2);//设置显示区域	
	ILI9326_WriteIndex( ILI9326_R202_GDRW );
	ILI9326Crl(CS);	//LCD_CS_LOW;
	for(i=0;i<num;i++)
	{ 
		temp=Buffer[i];		 					//调用1608字体--二维数组形式--字库使用时取消
		for(j=0;j<8;j++)
		{
			if((temp&0x80)==0X80)
			{
				LCD_PEN_COLOR=color;
			}
			else
				LCD_PEN_COLOR=ILI9326->Data.BColor;
			ILI9326_WriteData(LCD_PEN_COLOR);
			temp=temp<<1;
		}
    //=======================未满8位的补充定入
    if((24==font)||(12==font))
    {
      temp=Buffer[i+1];		 					
      for(j=0;j<4;j++)
      {
        if((temp&0x80)==0X80)
        {
          LCD_PEN_COLOR=color;
        }
        else
          LCD_PEN_COLOR=ILI9326->Data.BColor;
        ILI9326_WriteData(LCD_PEN_COLOR);
        temp=temp<<1;
      }
      i++;
    }		
	}
	ILI9326Set(CS);	//LCD_CS_HIGH;
}
/*******************************************************************************
* 函数名			:	function
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
*******************************************************************************/
void ILI9326_ShowWord(
										u16 x,			//x				:起点x坐标
										u16 y,			//y				:起点y坐标
										u8 font,		//font		:字体大小
										u16 color,	//字体颜色
										u8 num,			//num			:字节数
										u8 *Buffer	//Buffer	:显示的内容缓存
										
)		//高通字库测试程序
{
	u8 temp;
	u8 i=0,j=0;
	unsigned short x1=0,x2=0,y1=0,y2=0;
	unsigned short LCD_PEN_COLOR	=	0;   	//画笔色
	x1	=	x;
	y1	=	y;
  x2	=	x+font-1;
  y2	=	y+font-1;
	ILI9326_SetWindowAddress(x1,y1,x2,y2);//设置显示区域
	ILI9326_WriteIndex( ILI9326_R202_GDRW );
	ILI9326Crl(CS);	//LCD_CS_LOW;
	for(i=0;i<num;i++)
	{ 
		temp=Buffer[i];		 				
		for(j=0;j<8;j++)
		{
			if((temp&0x80)==0X80)
			{
				LCD_PEN_COLOR=color;
			}
			else
				LCD_PEN_COLOR=ILI9326->Data.BColor;
			ILI9326_WriteData(LCD_PEN_COLOR);
			temp=temp<<1;
		}
    //=======================未满8位的补充定入
    if((12==font))
    {
      temp=Buffer[i+1];		 					
      for(j=0;j<4;j++)
      {
        if((temp&0x80)==0X80)
        {
          LCD_PEN_COLOR=color;
        }
        else
          LCD_PEN_COLOR=ILI9326->Data.BColor;
        ILI9326_WriteData(LCD_PEN_COLOR);
        temp=temp<<1;
      }
      i++;
    }			
	}
	ILI9326Set(CS);	//LCD_CS_HIGH;
}
//#endif//LCD_61509_EN
/************************************** The End Of FILE **************************************/


