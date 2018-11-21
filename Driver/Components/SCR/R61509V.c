/**************************************************************************************************
* 液晶屏驱动IC
* 文件<$(filename)>
* 模块描述 :	定义、功能、说明
* 历史修改记录
*     <主要修改者>  <时间>   <版本 >   <说明>
*     xlyan        $(Date)   1.0.0    创建文件
**************************************************************************************************/
#include "R61509V.h"
#include "LCD.H"

#include "STM32_GPIO.H"

#include	"stdio.h"			//用于printf
#include	"string.h"		//用于printf
#include	"stdarg.h"		//用于获取不确定个数的参数
#include	"stdlib.h"		//malloc动态申请内存空间

static LCDDef	*pR61509V	=	NULL;		//内部驱动使用，不可删除

#define	R61509V_CS_HIGH		(pR61509V->Port.sCS_PORT->BSRR	= pR61509V->Port.sCS_Pin)
#define	R61509V_CS_LOW		(pR61509V->Port.sCS_PORT->BRR	=	pR61509V->Port.sCS_Pin)

#define	R61509V_DC_HIGH		(pR61509V->Port.sDC_PORT->BSRR	= pR61509V->Port.sDC_Pin)
#define	R61509V_DC_LOW		(pR61509V->Port.sDC_PORT->BRR	= pR61509V->Port.sDC_Pin)

#define	R61509V_WR_HIGH		(pR61509V->Port.sWR_PORT->BSRR	= pR61509V->Port.sWR_Pin)
#define	R61509V_WR_LOW		(pR61509V->Port.sWR_PORT->BRR	= pR61509V->Port.sWR_Pin)

#define	R61509V_RD_HIGH		(pR61509V->Port.sRD_PORT->BSRR	= pR61509V->Port.sRD_Pin)
#define	R61509V_RD_LOW		(pR61509V->Port.sRD_PORT->BRR	= pR61509V->Port.sRD_Pin)

#define	R61509V_RST_HIGH	(pR61509V->Port.sREST_PORT->BSRR	= pR61509V->Port.sREST_Pin)
#define	R61509V_RST_LOW		(pR61509V->Port.sREST_PORT->BRR	= pR61509V->Port.sREST_Pin)

#define	R61509V_TE_HIGH		(pR61509V->Port.sTE_PORT->BSRR	= pR61509V->Port.sTE_Pin)
#define	R61509V_TE_LOW		(pR61509V->Port.sTE_PORT->BRR	= pR61509V->Port.sTE_Pin)

#define	R61509V_BL_HIGH		(pR61509V->Port.sBL_PORT->BSRR	= pR61509V->Port.sBL_Pin)
#define	R61509V_BL_LOW		(pR61509V->Port.sBL_PORT->BRR	= pR61509V->Port.sBL_Pin)

#define R61509V_DATABUS_PORT	(pR61509V->Port.sDATABUS_PORT)
#define R61509V_DATABUS_Pin		(pR61509V->Port.sDATABUS_Pin)

#define	R61509VSet(n)	R61509V_##n##_HIGH
#define	R61509VCrl(n)	R61509V_##n##_LOW

/*******************************************************************************
* 函数名			:	function
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
*******************************************************************************/
unsigned short R61509V_Initialize(void*	pInfo)
{
	static unsigned short	DeviceCode	=	0;
	LCDPortDef*	Port	=	NULL;
	if(NULL==	pInfo)
		return 0;
	
	pR61509V		=	(LCDDef*)pInfo;		//指针指向
	Port	=	&pR61509V->Port;
	
	//==========================GPIO配置
	GPIO_Configuration_OPP50	(Port->sBL_PORT,				Port->sBL_Pin);					//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度2MHz----V20170605
	GPIO_Configuration_OPP50	(Port->sRD_PORT,				Port->sRD_Pin);					//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度2MHz----V20170605
	GPIO_Configuration_OPP50	(Port->sREST_PORT,			Port->sREST_Pin);				//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度2MHz----V20170605
	GPIO_Configuration_OPP50	(Port->sDC_PORT,				Port->sDC_Pin);					//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度2MHz----V20170605
	GPIO_Configuration_OPP50	(Port->sWR_PORT,				Port->sWR_Pin);					//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度2MHz----V20170605
	GPIO_Configuration_OPP50	(Port->sCS_PORT,				Port->sCS_Pin);					//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度2MHz----V20170605
	GPIO_Configuration_OPP50	(Port->sTE_PORT,				Port->sTE_Pin);					//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度2MHz----V20170605
	GPIO_Configuration_OPP50	(Port->sDATABUS_PORT,		Port->sDATABUS_Pin);		//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度2MHz----V20170605
	
	DeviceCode	=	R61509V_ReadRegister(R61509V_R000_IR);
	if(0xB509	!=	DeviceCode)
	{
		return 0;	//识别失败
	}
	//==========================检查背景色与画笔色是否相同
	if(pR61509V->Data.PColor	==	pR61509V->Data.BColor)
	{
		pR61509V->Data.PColor	=	pR61509V->Data.BColor^0xFFFF;
	}
	
	pR61509V->Data.MaxH	=	R61509V_H;					//最大水平宽度
	pR61509V->Data.MaxV	=	R61509V_V;					//最大垂直高度	
	
	//==========================接口函数
	pR61509V->Display.WriteAddress		=	R61509V_SetWindowAddress;
	pR61509V->Display.PowerOn					=	R61509V_PowerOn;
	pR61509V->Display.DispOff					=	R61509V_PowerOff;
	
	pR61509V->Display.DrawDot					=	R61509V_DrawDot;
	pR61509V->Display.DrawLine				=	R61509V_DrawLine;
	pR61509V->Display.DrawCircle			=	R61509V_DrawCircle;
	pR61509V->Display.DrawRectangle		=	R61509V_DrawRectangle;
	
	pR61509V->Display.Fill						=	R61509V_Fill;
	pR61509V->Display.Clean						=	R61509V_Clean;
	pR61509V->Display.SetBackground		=	R61509V_SetBackground;
	
	pR61509V->Display.ShowChar				=	R61509V_ShowChar;
	pR61509V->Display.ShowWord				=	R61509V_ShowWord;
	
	R61509V_PowerOn();
	R61509V_Clean(pR61509V->Data.BColor);
	
	R61509VSet(BL);
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
void R61509V_Reset(void)
{
	R61509VSet(RST);
	LCD_DelaymS(5);				//SysTick延时nmS
	R61509VCrl(RST);;
	LCD_DelaymS(5);				//SysTick延时nmS
	R61509VSet(RST);
	LCD_DelaymS(10);				//SysTick延时nmS
}
/*******************************************************************************
* 函数名			:	R61509V_WriteIndex
* 功能描述		:	写指定寄存器 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
unsigned short R61509V_ReadData(void)
{
	unsigned short Data	=	0;
#if	1	//Bus16Bit
	R61509VCrl(RD);	//LCD_RD_LOW;
	Data	=	R61509V_DATABUS_PORT->IDR;
	R61509VSet(RD);	//LCD_RD_HIGH;
#else	
	R61509VCrl(RD);	//LCD_RD_LOW;
	Data	=	R61509V_DATABUS_PORT->IDR;
	R61509VSet(RD);	//LCD_RD_HIGH;
	
	Data	<<=8;
	
	R61509VCrl(RD);	//LCD_RD_LOW;
	Data	|=	R61509V_DATABUS_PORT->IDR;
	R61509VSet(RD);	//LCD_RD_HIGH;
#endif	
	return Data;
}
/*******************************************************************************
* 函数名			:	R61509V_ReadRegister
* 功能描述		:	读指定寄存器 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
unsigned short R61509V_ReadRegister(unsigned	short	Addr)
{
	unsigned short Data	=	0;
	R61509VCrl(CS);	//LCD_CS_LOW;
	//---------------------Write Index
	R61509V_WriteAddr(Addr);
	//---------------------Read Data
	GPIO_Configuration_IPU	(R61509V_DATABUS_PORT,R61509V_DATABUS_Pin);			//将GPIO相应管脚配置为上拉输入模式----V20170605
	Data	=	R61509V_ReadData();
	R61509VSet(CS);	//LCD_CS_HIGH;
	GPIO_Configuration_OPP50	(R61509V_DATABUS_PORT,R61509V_DATABUS_Pin);		//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度2MHz----V20170605	
	return Data;
}
/*******************************************************************************
* 函数名			:	R61509V_WriteIndex
* 功能描述		:	写指定寄存器 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
void R61509V_WriteData(unsigned	short	Data)
{
#if	1	//Bus16Bit
	R61509VCrl(WR);	//LCD_WR_LOW;
	R61509V_DATABUS_PORT->ODR = Data;
	R61509VSet(WR);	//LCD_WR_HIGH;
#else
	R61509VCrl(WR);	//LCD_WR_LOW;
	R61509V_DATABUS_PORT->ODR = Data>>8;
	R61509VSet(WR);	//LCD_WR_HIGH;
	
	R61509VCrl(WR);	//LCD_WR_LOW;
	R61509V_DATABUS_PORT->ODR = Data&0xFF;
	R61509VSet(WR);	//LCD_WR_HIGH;
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
void R61509V_WriteAddr(unsigned	short	Addr)
{
	R61509VCrl(DC);	//LCD_DC_LOW;		//RS
	R61509V_WriteData(Addr);
	R61509VSet(DC);	//LCD_DC_HIGH;	//RS
}
/*******************************************************************************
* 函数名			:	R61509V_WriteIndex
* 功能描述		:	写指定寄存器 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
void R61509V_WriteIndex(unsigned	short	Index)
{
	R61509VCrl(CS);	//LCD_CS_LOW;	
	R61509V_WriteAddr(Index);
	R61509VSet(CS);	//LCD_CS_HIGH;
}
/*******************************************************************************
* 函数名			:	R61509V_WriteRegister
* 功能描述		:	写指定寄存器 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
void R61509V_WriteRegister(unsigned	short	Addr,unsigned short Data)
{
	R61509VCrl(CS);	//LCD_CS_LOW;	
	//---------------------Write Index
	R61509V_WriteAddr(Addr);
	//---------------------Write Data
	R61509V_WriteData(Data);	
	R61509VSet(CS);	//LCD_CS_HIGH;	
}
/*******************************************************************************
* 函数名			:	R61509V_WriteCommand
* 功能描述		:	读指定寄存器 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
void R61509V_WriteCommand(unsigned	short	Index,unsigned short Cmd)
{
	R61509V_WriteRegister(Index,Cmd);
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
void R61509V_WriteGRAM(unsigned	short* RAM,unsigned long length)
{
	unsigned	long	i	=	0;
	R61509VCrl(CS);	//LCD_CS_LOW;
	R61509V_WriteAddr(R61509V_R202_GDRW);
	for(i=0;i<length;i++)
	{
		R61509V_WriteData(RAM[i]);
	}
	R61509VSet(CS);	//LCD_CS_HIGH;
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
void R61509V_ReadGRAM(unsigned	short* RAM,unsigned long length)
{
	unsigned	long	i	=	0;
	R61509VCrl(CS);	//LCD_CS_LOW;
	R61509V_WriteIndex(R61509V_R202_GDRW);
	GPIO_Configuration_IPU	(R61509V_DATABUS_PORT,R61509V_DATABUS_Pin);			//将GPIO相应管脚配置为上拉输入模式----V20170605
	for(i=0;i<length;i++)
	{
		RAM[i]=R61509V_ReadData();
	}
	R61509VSet(CS);	//LCD_CS_HIGH;
	GPIO_Configuration_OPP50	(R61509V_DATABUS_PORT,R61509V_DATABUS_Pin);		//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度2MHz----V20170605	
}
/**************************************************************************************************
* [Function] LCD_PowerOff:  关闭LCD 电源
* [No param]
**************************************************************************************************/
void R61509V_PowerOff( void )
{
	LCD_BL_OFF;		//关背光
	R61509V_WriteCommand( R61509V_R009_DC3, 0 );	
}
/*******************************************************************************
*函数名			:	R61509V_Initialize
*功能描述		:	IC初始化：按照主控芯片R61509V的power supply on sequence 进行配置
*输入				: 
*返回值			:	无
*******************************************************************************/
void R61509V_PowerOn(void)			//按照主控芯片R61509V的power supply on sequence 进行配置
{
	u32 dtime=2000;
	
	void(*Command)(unsigned short Index,unsigned short Command);//LcdDisplay.WriteCommand
	
	void(*DelaymS)(unsigned long xms) = LCD_DelaymS;
	
	Command	=	R61509V_WriteCommand;

	
	R61509V_Reset();
	DelaymS( 10 );
	
	Command(R61509V_R000_IR		,	0x0000);	//四次写0x00
	Command(R61509V_R000_IR		,	0x0000);	//四次写0x00
	Command(R61509V_R000_IR		,	0x0000);	//四次写0x00
	Command(R61509V_R000_IR		,	0x0000);	//四次写0x00
	
	DelaymS( 10 );
	
	Command(R61509V_R001_DOC	,	0x0300);	//--------显示方向控制When SS = “1” and BGR = “1”, RGB dots are assigned one to one from S720 to S1.
	Command(R61509V_R002_DWC	,	0x0100);	//--------	
	Command(R61509V_R003_EM		,	0X5030);	//--------RGB设为5-6-5模式------------0X5030
	Command(R61509V_R007_DC1	,	0x0100);	//--------测试显示控制base image的关与开
	Command(R61509V_R008_DC2	,	0X0808);	//--------
	Command(R61509V_R009_DC3	,	0x0001);	//--------	
	
	Command(R61509V_R00B_ECC		,	0x0001);	//--------
	Command(R61509V_R00C_EDIC1	,	0x0000);	//--------
	Command(R61509V_R00F_EDIC2	,	0x0000);	//--------
	
	DelaymS( 10 );
	
	Command(R61509V_R010_PIC1	,	0x0019);	//--------面板频率--0x19
	Command(R61509V_R011_PIC2	,	0x0101);	//--------		Panel Interface Control 2 (R011h)
	Command(R61509V_R012_PIC3	,	0x0000);	//--------
	Command(R61509V_R013_PIC4	,	0x0001);	//--------
	Command(R61509V_R014_PIC5	,	0x0055);	//--------
	Command(R61509V_R020_PIC6	,	0x0010);	//--------
	Command(R61509V_R021_PIC7	,	0x0101);	//--------
	Command(R61509V_R022_PIC8	,	0x0000);	//--------
	Command(R61509V_R023_PIC9	,	0x0001);	//--------	
	
	DelaymS( 10 );
	
	Command(R61509V_R090_FMC		,	0x8000);	//--------窗特征控制，FMARK interface
	
	Command(R61509V_R100_PC1		,	0x0330);	//--------设置电源控制，平衡显示与电消耗
	Command(R61509V_R101_PC2		,	0x0227);	//--------Power Control 2
	Command(R61509V_R102_PC3		,	0xC1B0);	//--------PSON,PON 都设为1，电源供应打开
	Command(R61509V_R103_PC4		,	0x0D00);	//--------	
	
	DelaymS( 20 );
	
	Command(R61509V_R200_HA			,	0x0000);	//--------RAM address 设置
	Command(R61509V_R201_VA			,	0x0000);	//--------
	
	Command(R61509V_R280_NVM		,	0xB000);	//--------VCM
	
	Command(R61509V_R300_YC1		,	0x0C00);	//--------
	Command(R61509V_R301_YC2		,	0x5A0B);	//--------
	Command(R61509V_R302_YC3		,	0x0906);	//--------
	Command(R61509V_R303_YC4		,	0x1017);	//--------
	Command(R61509V_R304_YC5		,	0x2300);	//--------
	Command(R61509V_R305_YC6		,	0x1700);	//--------
	Command(R61509V_R306_YC7		,	0x6309);	//--------
	Command(R61509V_R307_YC8		,	0x0C09);	//--------
	Command(R61509V_R308_YC9		,	0x100C);	//--------
	Command(R61509V_R309_YC10		,	0x2232);	//--------
	
	DelaymS( 10 );
	
	Command(R61509V_R400_BINL		,	0X6400);	//base image 设置 400线
	Command(R61509V_R401_BIDC		,	0x0004);	//--------设置base image 滚动模式，开启滚动(颜色反相设置）
	Command(R61509V_R404_BIVSC	,	0x0000);	//--------从0线开始滚屏
	
	Command(R61509V_R502_PTEA		,	0x005f);
	DelaymS( 10 );
}
/*******************************************************************************
*函数名			:	R61509V_SetWindowAddress
*功能描述		:	设置窗口地址
*输入				: 
*返回值			:	无
*******************************************************************************/
void R61509V_SetWindowAddress(			//设置窗口地址
															unsigned short x1,		//水平起始点
															unsigned short y1,		//水平终止点
															unsigned short x2,		//垂直起始点
															unsigned short y2			//垂直终止点
															)
{	
	unsigned short MaxH,MaxV;
	unsigned short Model	=	0x5030;
	eRotate	Rotate	=	pR61509V->Flag.Rotate;
	
	void(*Command)(unsigned short Index,unsigned short Command);//LcdDisplay.WriteCommand	
	Command	=	R61509V_WriteCommand;
	
	MaxH	=	pR61509V->Data.MaxH;
	MaxV	=	pR61509V->Data.MaxV;
	
	switch(Rotate)
	{
		case 	Draw_Rotate_0D:
					pR61509V->Data.HSX	=	x1;
					pR61509V->Data.HEX	=	x2;
					pR61509V->Data.VSY	=	y1;
					pR61509V->Data.VEY	=	y2;	
					pR61509V->Data.HXA	=	pR61509V->Data.HSX;
					pR61509V->Data.VYA	=	pR61509V->Data.VSY;	
					Model	=	0x5030;
			break;
		case 	Draw_Rotate_90D:
					pR61509V->Data.HSX	=	y1;
					pR61509V->Data.HEX	=	y2;	
					pR61509V->Data.VSY	=	MaxV	-	x2	-	1;
					pR61509V->Data.VEY	=	MaxV	-	x1	-	1;	
					pR61509V->Data.HXA	=	pR61509V->Data.HSX;
					pR61509V->Data.VYA	=	pR61509V->Data.VEY;
					Model	=	0X5018;								//GRAM(Graphics RAM--图形内存) Data Write (R202h)准备写入
			break;
		case 	Draw_Rotate_180D:
					pR61509V->Data.HSX	=	MaxH	-	x2	-	1;
					pR61509V->Data.HEX	=	MaxH	-	x1	-	1;
					pR61509V->Data.VSY	=	MaxV	-	y2	-	1;
					pR61509V->Data.VEY	=	MaxV	-	y1	-	1;	
					pR61509V->Data.HXA	=	pR61509V->Data.HEX;
					pR61509V->Data.VYA	=	pR61509V->Data.VEY;	
					Model	=	0X5000;
			break;
		default:
					pR61509V->Data.HSX	=	MaxH	-	y2	-	1;
					pR61509V->Data.HEX	=	MaxH	-	y1	-	1;
					pR61509V->Data.VSY	=	x1;
					pR61509V->Data.VEY	=	x2;	
					pR61509V->Data.HXA	=	pR61509V->Data.HEX;
					pR61509V->Data.VYA	=	pR61509V->Data.VSY;
					Model	=	0X5028;
			break;
	}
	//======================================区域设置
	R61509V_WriteRegister(R61509V_R210_HSA,pR61509V->Data.HSX);		//Window Horizontal RAM Address Start(R210h)		//水平
	R61509V_WriteRegister(R61509V_R211_HEA,pR61509V->Data.HEX);		//Window Horizontal RAM Address End(R211h)			//水平
	R61509V_WriteRegister(R61509V_R212_VSA,pR61509V->Data.VSY);		//Window Vertical RAM Address Start (R212h)			//垂直
	R61509V_WriteRegister(R61509V_R213_VEA,pR61509V->Data.VEY);		//Window Vertical RAM Address End (R213h)				//垂直
	//======================================设置起始点
	R61509V_WriteRegister(R61509V_R200_HA,pR61509V->Data.HXA);			//RAM Address Set (Horizontal Address) (R200h)
	R61509V_WriteRegister(R61509V_R201_VA,pR61509V->Data.VYA);			//RAM Address Set (Vertical Address) (R201h)
	//======================================设置写入模式
	R61509V_WriteRegister(R61509V_R003_EM,Model);						//RAM Address Set (Vertical Address) (R201h)
	//======================================启动写入
	R61509V_WriteIndex(R61509V_R202_GDRW);		//GRAM(Graphics RAM--图形内存) Data Write (R202h)准备写入
}
//
//--------------------------------------------------------------GUI
//
/*******************************************************************************
*函数名			:	LCD_DrawPoint
*功能描述		:	画点
*输入				: 
*返回值			:	无
*******************************************************************************/
void R61509V_DrawDot(
									unsigned short HSX,			//点X坐标*/
									unsigned short HSY,			//点Y坐标*/
									unsigned short Color		//点颜色*/	
								)
{
	R61509V_SetWindowAddress(HSX,HSY,HSX,HSY);	//设置光标位置
	R61509V_WriteGRAM(&Color,1);
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
void R61509V_DrawLine(
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
		R61509V_DrawDot(uRow,uCol,Color);			//画点 
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
void R61509V_DrawCircle(
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
			R61509V_DrawLine(x,y,x-b,y-a,color);             //3           
			R61509V_DrawLine(x,y,x+b,y-a,color);             //0           
			R61509V_DrawLine(x,y,x-a,y+b,color);             //1       
			R61509V_DrawLine(x,y,x-b,y-a,color);             //7           
			R61509V_DrawLine(x,y,x-a,y-b,color);             //2             
			R61509V_DrawLine(x,y,x+b,y+a,color);             //4               
			R61509V_DrawLine(x,y,x+a,y-b,color);             //5
			R61509V_DrawLine(x,y,x+a,y+b,color);             //6 
			R61509V_DrawLine(x,y,x-b,y+a,color);             
			a++;
			//使用Bresenham算法画圆     
			if(di<0)
				di +=4*a+6;	  
			else
			{
				di+=10+4*(a-b);   
				b--;
			}
			R61509V_DrawLine(x,y,x+a,y+b,color);				//AB 两个坐标画一条直线
		}
		else
		{
			R61509V_DrawDot(x-b,y-a,color);             //3           
			R61509V_DrawDot(x+b,y-a,color);             //0           
			R61509V_DrawDot(x-a,y+b,color);             //1       
			R61509V_DrawDot(x-b,y-a,color);             //7           
			R61509V_DrawDot(x-a,y-b,color);             //2             
			R61509V_DrawDot(x+b,y+a,color);             //4               
			R61509V_DrawDot(x+a,y-b,color);             //5
			R61509V_DrawDot(x+a,y+b,color);             //6 
			R61509V_DrawDot(x-b,y+a,color);             
			a++;
			//使用Bresenham算法画圆     
			if(di<0)
				di +=4*a+6;	  
			else
			{
				di+=10+4*(a-b);   
				b--;
			}
				R61509V_DrawDot(x+a,y+b,color);
		}
	}
}
/**************************************************************************************************
* [Function] LCD_DrawRectangle:  画一下矩形框
* [param01]t_Point top_p: 顶点坐标值
* [param02]t_Point botton_p : 地板坐标值
**************************************************************************************************/
void R61509V_DrawRectangle(u16 x1,u16 y1,u16 x2,u16 y2,u16 color)
{
	R61509V_DrawLine( x1, y1,	x1,	y2, color );
	R61509V_DrawLine( x1, y1,	x2,	y1, color );
	R61509V_DrawLine( x2, y1,	x2,	y2, color );
	R61509V_DrawLine( x1, y2,	x2,	y2, color );
}
/*******************************************************************************
*函数名			:	ILI9326_Fill
*功能描述		:	在指定区域内填充指定颜色;区域大小:(xend-xsta)*(yend-ysta)
*输入				: 
*返回值			:	无
*******************************************************************************/
void R61509V_Fill(
							unsigned short x1, unsigned short y1, 	//x1,y1:起点坐标
							unsigned short x2, unsigned short y2,		//x2,y2:终点坐标
							u16 Color
)
{          
	unsigned int x;
	unsigned int y;	
	R61509V_SetWindowAddress(x1,y1,x2,y2);
	R61509V_WriteIndex( R61509V_R202_GDRW );
	R61509VCrl(CS);	//LCD_CS_LOW;
	for(x=0;x<=x2-x1;x++)
	{
		for(y=0;y<=y2-y1;y++)
		{
			R61509V_WriteData(Color);							//写数据
		}
	}	
	R61509VSet(CS);	//LCD_CS_HIGH;
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
void R61509V_Clean(u16 Color)	//清除屏幕函数
{
	unsigned short x,y;
	unsigned short HSX,HEX,HSY,HEY,MaxH,MaxV;
	unsigned long	length	=	0;
	eRotate	Rotate	=	pR61509V->Flag.Rotate;
	
	MaxH	=	pR61509V->Data.MaxH;
	MaxV	=	pR61509V->Data.MaxV;	
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
	R61509V_Fill(HSX,HSY,HEX,HEY,Color);
}
/**************************************************************************************************
* [Function] ILI9326_SetBackground:  设置背景颜色
* [param01]u16 BackColor: 背景颜色值
**************************************************************************************************/
void R61509V_SetBackground(  u16 BackColor )
{
	pR61509V->Data.BColor	=	BackColor;
	R61509V_Clean(BackColor);	//清除屏幕函数
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
void R61509V_ShowChar(
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
	
	R61509V_SetWindowAddress(x1,y1,x2,y2);//设置显示区域	
	R61509V_WriteIndex( R61509V_R202_GDRW );
	R61509VCrl(CS);	//LCD_CS_LOW;
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
				LCD_PEN_COLOR=pR61509V->Data.BColor;
			R61509V_WriteData(LCD_PEN_COLOR);
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
          LCD_PEN_COLOR=pR61509V->Data.BColor;
        R61509V_WriteData(LCD_PEN_COLOR);
        temp=temp<<1;
      }
      i++;
    }		
	}
	R61509VSet(CS);	//LCD_CS_HIGH;
}
/*******************************************************************************
* 函数名			:	function
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
*******************************************************************************/
void R61509V_ShowWord(
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
	R61509V_SetWindowAddress(x1,y1,x2,y2);//设置显示区域
	R61509V_WriteIndex( R61509V_R202_GDRW );
	R61509VCrl(CS);	//LCD_CS_LOW;
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
				LCD_PEN_COLOR=pR61509V->Data.BColor;
			R61509V_WriteData(LCD_PEN_COLOR);
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
          LCD_PEN_COLOR=pR61509V->Data.BColor;
        R61509V_WriteData(LCD_PEN_COLOR);
        temp=temp<<1;
      }
      i++;
    }			
	}
	R61509VSet(CS);	//LCD_CS_HIGH;
}

//#endif//R61509V_61509_EN
/************************************** The End Of FILE **************************************/


