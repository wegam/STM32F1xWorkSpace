//#ifdef	ST7789V

/********************************************************************************
***ST7789V LCD屏驱动器
********************************************************************************/
#include "ST7789V.H"
#include "LCD.H"
#include "STM32_GPIO.H"

#include	"stdio.h"			//用于printf
#include	"string.h"		//用于printf
#include	"stdarg.h"		//用于获取不确定个数的参数
#include	"stdlib.h"		//malloc动态申请内存空间

//#include <reg51.h>
//#include "intrins.h"
//#include "font\font.h"
//#include "sys\sys.h"
//#include "lcd\lcd.h"


LCDDef	*pST7789V	=	0;		//内部驱动使用，不可删除

#define	ST7789V_CS_HIGH		(pST7789V->Port.sCS_PORT->BSRR	= pST7789V->Port.sCS_Pin)
#define	ST7789V_CS_LOW		(pST7789V->Port.sCS_PORT->BRR	=	pST7789V->Port.sCS_Pin)

#define	ST7789V_DC_HIGH		(pST7789V->Port.sDC_PORT->BSRR	= pST7789V->Port.sDC_Pin)		//RS
#define	ST7789V_DC_LOW		(pST7789V->Port.sDC_PORT->BRR	= pST7789V->Port.sDC_Pin)		//RS

#define	ST7789V_WR_HIGH		(pST7789V->Port.sWR_PORT->BSRR	= pST7789V->Port.sWR_Pin)
#define	ST7789V_WR_LOW		(pST7789V->Port.sWR_PORT->BRR	= pST7789V->Port.sWR_Pin)

#define	ST7789V_RD_HIGH		(pST7789V->Port.sRD_PORT->BSRR	= pST7789V->Port.sRD_Pin)
#define	ST7789V_RD_LOW		(pST7789V->Port.sRD_PORT->BRR	= pST7789V->Port.sRD_Pin)

#define	ST7789V_RST_HIGH	(pST7789V->Port.sREST_PORT->BSRR	= pST7789V->Port.sREST_Pin)
#define	ST7789V_RST_LOW		(pST7789V->Port.sREST_PORT->BRR	= pST7789V->Port.sREST_Pin)

#define	ST7789V_TE_HIGH		(pST7789V->Port.sTE_PORT->BSRR	= pST7789V->Port.sTE_Pin)
#define	ST7789V_TE_LOW		(pST7789V->Port.sTE_PORT->BRR	= pST7789V->Port.sTE_Pin)

#define	ST7789V_BL_HIGH		(pST7789V->Port.sBL_PORT->BSRR	= pST7789V->Port.sBL_Pin)
#define	ST7789V_BL_LOW		(pST7789V->Port.sBL_PORT->BRR	= pST7789V->Port.sBL_Pin)

#define ST7789V_DATABUS_PORT	(pST7789V->Port.sDATABUS_PORT)
#define ST7789V_DATABUS_Pin		(pST7789V->Port.sDATABUS_Pin)

#define	ST7789VSet(n)	ST7789V_##n##_HIGH
#define	ST7789VCrl(n)	ST7789V_##n##_LOW
/*******************************************************************************
*函数名			:	function
*功能描述		:	函数功能说明
*输入				: 
*返回值			:	无
*******************************************************************************/
void ST7789V_Initialize(void*	pInfo)
{
	static unsigned short	DeviceCode	=	0;
	LCDPortDef*	Port	=	NULL;
	if(NULL==	pInfo)
		return;
	pST7789V		=	(LCDDef*)pInfo;		//指针指向	
	
	pST7789V		=	(LCDDef*)pInfo;		//指针指向
	Port	=	&pST7789V->Port;
	
	//==========================GPIO配置
//	GPIO_Configuration_OPP50	(Port->sBL_PORT,				Port->sBL_Pin);					//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度2MHz----V20170605
//	GPIO_Configuration_OPP50	(Port->sRD_PORT,				Port->sRD_Pin);					//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度2MHz----V20170605
//	GPIO_Configuration_OPP50	(Port->sREST_PORT,			Port->sREST_Pin);				//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度2MHz----V20170605
//	GPIO_Configuration_OPP50	(Port->sDC_PORT,				Port->sDC_Pin);					//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度2MHz----V20170605
//	GPIO_Configuration_OPP50	(Port->sWR_PORT,				Port->sWR_Pin);					//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度2MHz----V20170605
//	GPIO_Configuration_OPP50	(Port->sCS_PORT,				Port->sCS_Pin);					//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度2MHz----V20170605
//	GPIO_Configuration_OPP50	(Port->sTE_PORT,				Port->sTE_Pin);					//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度2MHz----V20170605
//	GPIO_Configuration_OPP50	(Port->sDATABUS_PORT,		Port->sDATABUS_Pin);		//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度2MHz----V20170605
	
//	DeviceCode	=	ST7789V_ReadRegister(0x00);
	
	//==========================检查背景色与画笔色是否相同
	if(pST7789V->Data.PColor	==	pST7789V->Data.BColor)
	{
		pST7789V->Data.PColor	=	pST7789V->Data.BColor^0xFFFF;
	}
	
	pST7789V->Data.MaxH	=	ST7789V_H;					//最大水平宽度
	pST7789V->Data.MaxV	=	ST7789V_V;					//最大垂直高度	
  
	//==========================接口函数
	pST7789V->Display.WriteAddress		=	ST7789V_SetWindowAddress;
	pST7789V->Display.PowerOn					=	ST7789V_PowerOn;
	pST7789V->Display.DispOff					=	ST7789V_PowerOff;
	
	pST7789V->Display.DrawDot					=	ST7789V_DrawDot;
	pST7789V->Display.DrawLine				=	ST7789V_DrawLine;
	pST7789V->Display.DrawCircle			=	ST7789V_DrawCircle;
	pST7789V->Display.DrawRectangle		=	ST7789V_DrawRectangle;
	
	pST7789V->Display.Fill						=	ST7789V_Fill;
	pST7789V->Display.Clean						=	ST7789V_Clean;
	pST7789V->Display.SetBackground		=	ST7789V_SetBackground;
	
	pST7789V->Display.ShowChar				=	ST7789V_ShowChar;
	pST7789V->Display.ShowWord				=	ST7789V_ShowWord;
	
  if(NULL ==  pST7789V->Display.WriteIndex)
    pST7789V->Display.WriteIndex  = ST7789V_WriteIndex;
  if(NULL ==  pST7789V->Display.WriteData)
    pST7789V->Display.WriteData  = ST7789V_WriteData;
  if(NULL ==  pST7789V->Display.WriteCommand)
    pST7789V->Display.WriteCommand  = ST7789V_WriteCommand;
  
	ST7789V_PowerOn();
	ST7789V_Clean(pST7789V->Data.BColor);
	
	ST7789VCrl(BL);
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
void ST7789V_Reset(void)
{
	ST7789VSet(RST);
	LCD_DelaymS(5);				//SysTick延时nmS
	ST7789VCrl(RST);;
	LCD_DelaymS(5);				//SysTick延时nmS
	ST7789VSet(RST);
	LCD_DelaymS(10);				//SysTick延时nmS
}
/*******************************************************************************
* 函数名			:	ST7789V_WriteIndex
* 功能描述		:	写指定寄存器 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
unsigned short ST7789V_ReadData(void)
{
	unsigned short Data	=	0;
#if	1	//Bus16Bit
	ST7789VCrl(RD);	//LCD_RD_LOW;
	Data	=	ST7789V_DATABUS_PORT->IDR;
	ST7789VSet(RD);	//LCD_RD_HIGH;
#else	
	ST7789VCrl(RD);	//LCD_RD_LOW;
	Data	=	ST7789V_DATABUS_PORT->IDR;
	ST7789VSet(RD);	//LCD_RD_HIGH;
	
	Data	<<=8;
	
	ST7789VCrl(RD);	//LCD_RD_LOW;
	Data	|=	ST7789V_DATABUS_PORT->IDR;
	ST7789VSet(RD);	//LCD_RD_HIGH;
#endif	
	return Data;
}
/*******************************************************************************
* 函数名			:	ST7789V_ReadRegister
* 功能描述		:	读指定寄存器 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
unsigned short ST7789V_ReadRegister(unsigned	short	Addr)
{
	unsigned short Data	=	0;
	ST7789VCrl(CS);	//LCD_CS_LOW;
	//---------------------Write Index
	ST7789V_WriteAddr(Addr);
	//---------------------Read Data
	GPIO_Configuration_IPU	(ST7789V_DATABUS_PORT,ST7789V_DATABUS_Pin);			//将GPIO相应管脚配置为上拉输入模式----V20170605
	Data	=	ST7789V_ReadData();
	ST7789VSet(CS);	//LCD_CS_HIGH;
	GPIO_Configuration_OPP50	(ST7789V_DATABUS_PORT,ST7789V_DATABUS_Pin);		//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度2MHz----V20170605	
	return Data;
}
/*******************************************************************************
* 函数名			:	ST7789V_WriteIndex
* 功能描述		:	写指定寄存器 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
void ST7789V_WriteData(unsigned	short	Data)
{
#if	1	//Bus16Bit
	ST7789VCrl(WR);	//LCD_WR_LOW;
	ST7789V_DATABUS_PORT->ODR = Data;
	ST7789VSet(WR);	//LCD_WR_HIGH;
#else
	ST7789VCrl(WR);	//LCD_WR_LOW;
	ST7789V_DATABUS_PORT->ODR = Data>>8;
	ST7789VSet(WR);	//LCD_WR_HIGH;
	
	ST7789VCrl(WR);	//LCD_WR_LOW;
	ST7789V_DATABUS_PORT->ODR = Data&0xFF;
	ST7789VSet(WR);	//LCD_WR_HIGH;
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
void ST7789V_WriteAddr(unsigned	short	Addr)
{
	ST7789VCrl(DC);	//LCD_DC_LOW;		//RS
	ST7789V_WriteData(Addr);
	ST7789VSet(DC);	//LCD_DC_HIGH;	//RS
}
/*******************************************************************************
* 函数名			:	ST7789V_WriteIndex
* 功能描述		:	写指定寄存器 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
void ST7789V_WriteIndex(unsigned	short	Index)
{
	ST7789VCrl(CS);	//LCD_CS_LOW;	
	ST7789V_WriteAddr(Index);
	ST7789VSet(CS);	//LCD_CS_HIGH;
}
/*******************************************************************************
* 函数名			:	ST7789V_WriteRegister
* 功能描述		:	写指定寄存器 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
void ST7789V_WriteRegister(unsigned	short	Addr,unsigned short Data)
{
	ST7789VCrl(CS);	//LCD_CS_LOW;	
	//---------------------Write Index
	ST7789V_WriteAddr(Addr);
	//---------------------Write Data
	ST7789V_WriteData(Data);	
	ST7789VSet(CS);	//LCD_CS_HIGH;	
}
/*******************************************************************************
* 函数名			:	ST7789V_WriteCommand
* 功能描述		:	读指定寄存器 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
void ST7789V_WriteCommand(unsigned	short	Index,unsigned short Cmd)
{
	ST7789V_WriteRegister(Index,Cmd);
}
/*******************************************************************************
* 函数名			:	ST7789V_WriteGRAM
* 功能描述		:	写指定寄存器 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
void ST7789V_WriteGRAM(unsigned	short* RAM,unsigned long length)
{
	unsigned	long	i	=	0;
	ST7789VCrl(CS);	//LCD_CS_LOW;
	pST7789V->Display.WriteIndex(0X3C);
	for(i=0;i<length;i++)
	{
		pST7789V->Display.WriteData(RAM[i]);
	}
	ST7789VSet(CS);	//LCD_CS_HIGH;
}
/*******************************************************************************
* 函数名			:	ST7789V_WriteGRAM
* 功能描述		:	写指定寄存器 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
void ST7789V_ReadGRAM(unsigned	short* RAM,unsigned long length)
{
	unsigned	long	i	=	0;
	ST7789VCrl(CS);	//LCD_CS_LOW;
	ST7789V_WriteIndex(0X3E);
	GPIO_Configuration_IPU	(ST7789V_DATABUS_PORT,ST7789V_DATABUS_Pin);			//将GPIO相应管脚配置为上拉输入模式----V20170605
	for(i=0;i<length;i++)
	{
		RAM[i]=ST7789V_ReadData();
	}
	ST7789VSet(CS);	//LCD_CS_HIGH;
	GPIO_Configuration_OPP50	(ST7789V_DATABUS_PORT,ST7789V_DATABUS_Pin);		//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度2MHz----V20170605	
}
/**************************************************************************************************
* [Function] LCD_PowerOff:  关闭LCD 电源
* [No param]
**************************************************************************************************/
void ST7789V_PowerOff( void )
{
	LCD_BL_OFF;		//关背光
	ST7789V_WriteCommand( 0x10, 0 );	
}
/*******************************************************************************
*函数名		:	Lcd_Init
*功能描述	:	STM32内部温度传感器配置
*输入			: 
*输出			:	无
*返回值		:	无
*例程			:
*******************************************************************************/
void ST7789V_PowerOn(void)
{

	u16 time=2000;
	u16	temp=time;
//调用一次这些函数，免得编译的时候提示警告
	//1）——————————复位
//	ST7789V_BACKLIGHT_OFF;	//关背光
//	LCD_REST();
//	LCD_RST_LOW;
//	LCD_RST_HIGH;
//	while(temp--);	  //等待晶振启动
//	//2）——————————复位
//	LCD_CS_HIGH;			//先取消片选
//	LCD_RD_HIGH;
//	LCD_WR_LOW;				//总线功能为写数据
//	LCD_CS_LOW;  		  //使能
//  LCD_DelaymS(10);
	ST7789VCrl(CS);	//LCD_CS_LOW;
 
  pST7789V->Display.WriteIndex(0x11); 
 LCD_DelaymS(120); 	   //Delay 120ms 
 //----------------------------------Display Setting-----------------------------------------------// 
 pST7789V->Display.WriteData(0x36); 
 pST7789V->Display.WriteData(0x00); 
 
 pST7789V->Display.WriteData(0x3a); 
 pST7789V->Display.WriteData(0x55); 
 //--------------------------------ST7789V Frame rate setting----------------------------------// 
 pST7789V->Display.WriteData(0xb2); 
 pST7789V->Display.WriteData(0x0c); 
 pST7789V->Display.WriteData(0x0c); 
 pST7789V->Display.WriteData(0x00); 
 pST7789V->Display.WriteData(0x33); 
 pST7789V->Display.WriteData(0x33); 
 pST7789V->Display.WriteData(0xb7); 
 pST7789V->Display.WriteData(0x35);		//VGH=13V, VGL=-10.4V 
 //----------------------------------------------------------------------------------------------------// 
 pST7789V->Display.WriteData(0xbb); 
 pST7789V->Display.WriteData(0x19); 
 pST7789V->Display.WriteData(0xc0); 
 pST7789V->Display.WriteData(0x2c); 
 pST7789V->Display.WriteData(0xc2); 
 pST7789V->Display.WriteData(0x01); 
 pST7789V->Display.WriteData(0xc3); 
 pST7789V->Display.WriteData(0x12); 
 pST7789V->Display.WriteData(0xc4); 
 pST7789V->Display.WriteData(0x20); 
 pST7789V->Display.WriteData(0xc6); 
 pST7789V->Display.WriteData(0x0f); 
 pST7789V->Display.WriteData(0xd0); 
 pST7789V->Display.WriteData(0xa4); 
 pST7789V->Display.WriteData(0xa1); 
 //----------------------------------------------------------------------------------------------------// 
 pST7789V->Display.WriteData(0xe0);	   //gamma setting 
 pST7789V->Display.WriteData(0xd0); 
 pST7789V->Display.WriteData(0x04); 
 pST7789V->Display.WriteData(0x0d); 
 pST7789V->Display.WriteData(0x11); 
 pST7789V->Display.WriteData(0x13); 
 pST7789V->Display.WriteData(0x2b); 
 pST7789V->Display.WriteData(0x3f); 
 pST7789V->Display.WriteData(0x54); 
 pST7789V->Display.WriteData(0x4c); 
 pST7789V->Display.WriteData(0x18); 
 pST7789V->Display.WriteData(0x0d); 
 pST7789V->Display.WriteData(0x0b); 
 pST7789V->Display.WriteData(0x1f); 
 pST7789V->Display.WriteData(0x23); 
 pST7789V->Display.WriteData(0xe1); 
 pST7789V->Display.WriteData(0xd0); 
 pST7789V->Display.WriteData(0x04); 
 pST7789V->Display.WriteData(0x0c); 
 pST7789V->Display.WriteData(0x11); 
 pST7789V->Display.WriteData(0x13); 
 pST7789V->Display.WriteData(0x2c); 
 pST7789V->Display.WriteData(0x3f); 
 pST7789V->Display.WriteData(0x44); 
 pST7789V->Display.WriteData(0x51); 
 pST7789V->Display.WriteData(0x2f); 
 pST7789V->Display.WriteData(0x1f); 
 pST7789V->Display.WriteData(0x1f); 
 pST7789V->Display.WriteData(0x20); 
 pST7789V->Display.WriteData(0x23); 
 
 pST7789V->Display.WriteData(0x29);	   //display on 
 pST7789V->Display.WriteIndex(0x2c); 
 
 ST7789VSet(CS);	//LCD_CS_HIGH;
 
}
/*******************************************************************************
*函数名		:	Address_set
*功能描述	:	STM32内部温度传感器配置
*输入			: 
*输出			:	无
*返回值		:	无
*例程			:
*******************************************************************************/
void ST7789V_SetWindowAddress(unsigned short x1,unsigned short y1,unsigned short x2,unsigned short y2)
{ 
	unsigned short MaxH,MaxV;
	unsigned short Model	=	0x5030;
	
	eRotate	Rotate	=	LCDSYS->Flag.Rotate;
	
	MaxH	=	LCDSYS->Data.MaxH;
	MaxV	=	LCDSYS->Data.MaxV;
	
if	(Rotate	==Draw_Rotate_0D)
{
	LCDSYS->Data.HSX	=	x1;
	LCDSYS->Data.HEX	=	x2;
	LCDSYS->Data.VSY	=	y1;
	LCDSYS->Data.VEY	=	y2;
	
	LCDSYS->Data.HXA	=	LCDSYS->Data.HSX;
	LCDSYS->Data.VYA	=	LCDSYS->Data.VSY;
	
	Model	=	0X00;
}
else if (Rotate	==Draw_Rotate_90D)
{
	LCDSYS->Data.HSX	=	y1;
	LCDSYS->Data.HEX	=	y2;	
	LCDSYS->Data.VSY	=	MaxV	-	x2	-	1;
	LCDSYS->Data.VEY	=	MaxV	-	x1	-	1;
	
	LCDSYS->Data.HXA	=	LCDSYS->Data.HSX;
	LCDSYS->Data.VYA	=	LCDSYS->Data.VEY;
	Model	=	0XA0;								//GRAM(Graphics RAM--图形内存) Data Write (R202h)准备写入
}
else if (Rotate	==Draw_Rotate_180D)	
{
	LCDSYS->Data.HSX	=	MaxH	-	x2	-	1;
	LCDSYS->Data.HEX	=	MaxH	-	x1	-	1;
	LCDSYS->Data.VSY	=	MaxV	-	y2	-	1;
	LCDSYS->Data.VEY	=	MaxV	-	y1	-	1;
	
	LCDSYS->Data.HXA	=	LCDSYS->Data.HEX;
	LCDSYS->Data.VYA	=	LCDSYS->Data.VEY;
	
	Model	=	0XC0;
}
else //(Rotate	==Draw_Rotate_270D)
{
	LCDSYS->Data.HSX	=	y1;
	LCDSYS->Data.HEX	=	y2;
	LCDSYS->Data.VSY	=	x1;
	LCDSYS->Data.VEY	=	x2;
	
	LCDSYS->Data.HXA	=	LCDSYS->Data.HEX;
	LCDSYS->Data.VYA	=	LCDSYS->Data.VSY;

	Model	=	0X22;
}
	//======================================区域设置
	pST7789V->Display.WriteIndex(0x002A);			//设置列地址
	pST7789V->Display.WriteData(LCDSYS->Data.HSX>>8);		//起始地址高8位
	pST7789V->Display.WriteData(LCDSYS->Data.HSX);			//起始地址低8位
	pST7789V->Display.WriteData(LCDSYS->Data.HEX>>8);		//结束地址高8位
	pST7789V->Display.WriteData(LCDSYS->Data.HEX);			//行结束地址低8位
	
	pST7789V->Display.WriteIndex(0x002b);			//设置页地址	
	pST7789V->Display.WriteData(LCDSYS->Data.VSY>>8);
	pST7789V->Display.WriteData(LCDSYS->Data.VSY);
	pST7789V->Display.WriteData(LCDSYS->Data.VEY>>8);
	pST7789V->Display.WriteData(LCDSYS->Data.VEY);
	
	pST7789V->Display.WriteIndex(0x0036);			//设置页地址
	pST7789V->Display.WriteData(Model);

	pST7789V->Display.WriteIndex(0x002c);			//写内存起始地址					 						 
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
void ST7789V_DrawDot(
									unsigned short HSX,			//点X坐标*/
									unsigned short HSY,			//点Y坐标*/
									unsigned short Color		//点颜色*/	
								)
{
	ST7789V_SetWindowAddress(HSX,HSY,HSX,HSY);	//设置光标位置
	ST7789V_WriteGRAM(&Color,1);
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
void ST7789V_DrawLine(
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
		ST7789V_DrawDot(uRow,uCol,Color);			//画点 
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
void ST7789V_DrawCircle(
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
			ST7789V_DrawLine(x,y,x-b,y-a,color);             //3           
			ST7789V_DrawLine(x,y,x+b,y-a,color);             //0           
			ST7789V_DrawLine(x,y,x-a,y+b,color);             //1       
			ST7789V_DrawLine(x,y,x-b,y-a,color);             //7           
			ST7789V_DrawLine(x,y,x-a,y-b,color);             //2             
			ST7789V_DrawLine(x,y,x+b,y+a,color);             //4               
			ST7789V_DrawLine(x,y,x+a,y-b,color);             //5
			ST7789V_DrawLine(x,y,x+a,y+b,color);             //6 
			ST7789V_DrawLine(x,y,x-b,y+a,color);             
			a++;
			//使用Bresenham算法画圆     
			if(di<0)
				di +=4*a+6;	  
			else
			{
				di+=10+4*(a-b);   
				b--;
			}
			ST7789V_DrawLine(x,y,x+a,y+b,color);				//AB 两个坐标画一条直线
		}
		else
		{
			ST7789V_DrawDot(x-b,y-a,color);             //3           
			ST7789V_DrawDot(x+b,y-a,color);             //0           
			ST7789V_DrawDot(x-a,y+b,color);             //1       
			ST7789V_DrawDot(x-b,y-a,color);             //7           
			ST7789V_DrawDot(x-a,y-b,color);             //2             
			ST7789V_DrawDot(x+b,y+a,color);             //4               
			ST7789V_DrawDot(x+a,y-b,color);             //5
			ST7789V_DrawDot(x+a,y+b,color);             //6 
			ST7789V_DrawDot(x-b,y+a,color);             
			a++;
			//使用Bresenham算法画圆     
			if(di<0)
				di +=4*a+6;	  
			else
			{
				di+=10+4*(a-b);   
				b--;
			}
				ST7789V_DrawDot(x+a,y+b,color);
		}
	}
}
/**************************************************************************************************
* [Function] LCD_DrawRectangle:  画一下矩形框
* [param01]t_Point top_p: 顶点坐标值
* [param02]t_Point botton_p : 地板坐标值
**************************************************************************************************/
void ST7789V_DrawRectangle(u16 x1,u16 y1,u16 x2,u16 y2,u16 color)
{
	ST7789V_DrawLine( x1, y1,	x1,	y2, color );
	ST7789V_DrawLine( x1, y1,	x2,	y1, color );
	ST7789V_DrawLine( x2, y1,	x2,	y2, color );
	ST7789V_DrawLine( x1, y2,	x2,	y2, color );
}
/*******************************************************************************
*函数名			:	ILI9326_Fill
*功能描述		:	在指定区域内填充指定颜色;区域大小:(xend-xsta)*(yend-ysta)
*输入				: 
*返回值			:	无
*******************************************************************************/
void ST7789V_Fill(
							unsigned short x1, unsigned short y1, 	//x1,y1:起点坐标
							unsigned short x2, unsigned short y2,		//x2,y2:终点坐标
							u16 Color
)
{          
	unsigned int x;
	unsigned int y;	
	ST7789V_SetWindowAddress(x1,y1,x2,y2);
	pST7789V->Display.WriteIndex( 0X2C );
	ST7789VCrl(CS);	//LCD_CS_LOW;
	for(x=0;x<=x2-x1;x++)
	{
		for(y=0;y<=y2-y1;y++)
		{
			pST7789V->Display.WriteData(Color);							//写数据
		}
	}	
	ST7789VSet(CS);	//LCD_CS_HIGH;
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
void ST7789V_Clean(u16 Color)	//清除屏幕函数
{
	unsigned short x,y;
	unsigned short HSX,HEX,HSY,HEY,MaxH,MaxV;
	unsigned long	length	=	0;
	eRotate	Rotate	=	pST7789V->Flag.Rotate;
	
	MaxH	=	pST7789V->Data.MaxH;
	MaxV	=	pST7789V->Data.MaxV;	
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
	ST7789V_Fill(HSX,HSY,HEX,HEY,Color);
}
/**************************************************************************************************
* [Function] ILI9326_SetBackground:  设置背景颜色
* [param01]u16 BackColor: 背景颜色值
**************************************************************************************************/
void ST7789V_SetBackground(  u16 BackColor )
{
	pST7789V->Data.BColor	=	BackColor;
	ST7789V_Clean(BackColor);	//清除屏幕函数
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
void ST7789V_ShowChar(
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
	
	ST7789V_SetWindowAddress(x1,y1,x2,y2);//设置显示区域	
	pST7789V->Display.WriteIndex( 0X2C );
	ST7789VCrl(CS);	//LCD_CS_LOW;
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
				LCD_PEN_COLOR=pST7789V->Data.BColor;
			pST7789V->Display.WriteData(LCD_PEN_COLOR);
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
          LCD_PEN_COLOR=pST7789V->Data.BColor;
        pST7789V->Display.WriteData(LCD_PEN_COLOR);
        temp=temp<<1;
      }
      i++;
    }		
	}
	ST7789VSet(CS);	//LCD_CS_HIGH;
}
/*******************************************************************************
* 函数名			:	function
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
*******************************************************************************/
void ST7789V_ShowWord(
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
	ST7789V_SetWindowAddress(x1,y1,x2,y2);//设置显示区域
	pST7789V->Display.WriteIndex( 0X2C );
	ST7789VCrl(CS);	//LCD_CS_LOW;
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
				LCD_PEN_COLOR=pST7789V->Data.BColor;
			pST7789V->Display.WriteData(LCD_PEN_COLOR);
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
          LCD_PEN_COLOR=pST7789V->Data.BColor;
        pST7789V->Display.WriteData(LCD_PEN_COLOR);
        temp=temp<<1;
      }
      i++;
    }			
	}
	ST7789VSet(CS);	//LCD_CS_HIGH;
}



