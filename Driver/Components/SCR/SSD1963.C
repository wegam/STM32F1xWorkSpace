//#ifdef	SSD1963

/********************************************************************************
***SSD1963 LCD屏驱动器
********************************************************************************/
#include "SSD1963.H"
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


LCDDef	*pSSD1963	=	0;		//内部驱动使用，不可删除

#define	SSD1963_CS_HIGH		(pSSD1963->Port.sCS_PORT->BSRR	= pSSD1963->Port.sCS_Pin)
#define	SSD1963_CS_LOW		(pSSD1963->Port.sCS_PORT->BRR	=	pSSD1963->Port.sCS_Pin)

#define	SSD1963_DC_HIGH		(pSSD1963->Port.sDC_PORT->BSRR	= pSSD1963->Port.sDC_Pin)		//RS
#define	SSD1963_DC_LOW		(pSSD1963->Port.sDC_PORT->BRR	= pSSD1963->Port.sDC_Pin)		//RS

#define	SSD1963_WR_HIGH		(pSSD1963->Port.sWR_PORT->BSRR	= pSSD1963->Port.sWR_Pin)
#define	SSD1963_WR_LOW		(pSSD1963->Port.sWR_PORT->BRR	= pSSD1963->Port.sWR_Pin)

#define	SSD1963_RD_HIGH		(pSSD1963->Port.sRD_PORT->BSRR	= pSSD1963->Port.sRD_Pin)
#define	SSD1963_RD_LOW		(pSSD1963->Port.sRD_PORT->BRR	= pSSD1963->Port.sRD_Pin)

#define	SSD1963_RST_HIGH	(pSSD1963->Port.sREST_PORT->BSRR	= pSSD1963->Port.sREST_Pin)
#define	SSD1963_RST_LOW		(pSSD1963->Port.sREST_PORT->BRR	= pSSD1963->Port.sREST_Pin)

#define	SSD1963_TE_HIGH		(pSSD1963->Port.sTE_PORT->BSRR	= pSSD1963->Port.sTE_Pin)
#define	SSD1963_TE_LOW		(pSSD1963->Port.sTE_PORT->BRR	= pSSD1963->Port.sTE_Pin)

#define	SSD1963_BL_HIGH		(pSSD1963->Port.sBL_PORT->BSRR	= pSSD1963->Port.sBL_Pin)
#define	SSD1963_BL_LOW		(pSSD1963->Port.sBL_PORT->BRR	= pSSD1963->Port.sBL_Pin)

#define SSD1963_DATABUS_PORT	(pSSD1963->Port.sDATABUS_PORT)
#define SSD1963_DATABUS_Pin		(pSSD1963->Port.sDATABUS_Pin)

#define	SSD1963Set(n)	SSD1963_##n##_HIGH
#define	SSD1963Crl(n)	SSD1963_##n##_LOW
/*******************************************************************************
*函数名			:	function
*功能描述		:	函数功能说明
*输入				: 
*返回值			:	无
*******************************************************************************/
void SSD1963_Initialize(void*	pInfo)
{
	static unsigned short	DeviceCode	=	0;
	LCDPortDef*	Port	=	NULL;
	if(NULL==	pInfo)
		return;
	pSSD1963		=	(LCDDef*)pInfo;		//指针指向	
	
	pSSD1963		=	(LCDDef*)pInfo;		//指针指向
	Port	=	&pSSD1963->Port;
	
	//==========================GPIO配置
//	GPIO_Configuration_OPP50	(Port->sBL_PORT,				Port->sBL_Pin);					//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度2MHz----V20170605
//	GPIO_Configuration_OPP50	(Port->sRD_PORT,				Port->sRD_Pin);					//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度2MHz----V20170605
//	GPIO_Configuration_OPP50	(Port->sREST_PORT,			Port->sREST_Pin);				//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度2MHz----V20170605
//	GPIO_Configuration_OPP50	(Port->sDC_PORT,				Port->sDC_Pin);					//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度2MHz----V20170605
//	GPIO_Configuration_OPP50	(Port->sWR_PORT,				Port->sWR_Pin);					//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度2MHz----V20170605
//	GPIO_Configuration_OPP50	(Port->sCS_PORT,				Port->sCS_Pin);					//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度2MHz----V20170605
//	GPIO_Configuration_OPP50	(Port->sTE_PORT,				Port->sTE_Pin);					//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度2MHz----V20170605
//	GPIO_Configuration_OPP50	(Port->sDATABUS_PORT,		Port->sDATABUS_Pin);		//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度2MHz----V20170605
	
//	DeviceCode	=	SSD1963_ReadRegister(0x00);
	
	//==========================检查背景色与画笔色是否相同
	if(pSSD1963->Data.PColor	==	pSSD1963->Data.BColor)
	{
		pSSD1963->Data.PColor	=	pSSD1963->Data.BColor^0xFFFF;
	}
	
	pSSD1963->Data.MaxH	=	SSD1963_H;					//最大水平宽度
	pSSD1963->Data.MaxV	=	SSD1963_V;					//最大垂直高度	
  
	//==========================接口函数
	pSSD1963->Display.WriteAddress		=	SSD1963_SetWindowAddress;
	pSSD1963->Display.PowerOn					=	SSD1963_PowerOn;
	pSSD1963->Display.DispOff					=	SSD1963_PowerOff;
	
	pSSD1963->Display.DrawDot					=	SSD1963_DrawDot;
	pSSD1963->Display.DrawLine				=	SSD1963_DrawLine;
	pSSD1963->Display.DrawCircle			=	SSD1963_DrawCircle;
	pSSD1963->Display.DrawRectangle		=	SSD1963_DrawRectangle;
	
	pSSD1963->Display.Fill						=	SSD1963_Fill;
	pSSD1963->Display.Clean						=	SSD1963_Clean;
	pSSD1963->Display.SetBackground		=	SSD1963_SetBackground;
	
	pSSD1963->Display.ShowChar				=	SSD1963_ShowChar;
	pSSD1963->Display.ShowWord				=	SSD1963_ShowWord;
	
  if(NULL ==  pSSD1963->Display.WriteIndex)
    pSSD1963->Display.WriteIndex  = SSD1963_WriteIndex;
  if(NULL ==  pSSD1963->Display.WriteData)
    pSSD1963->Display.WriteData  = SSD1963_WriteData;
  if(NULL ==  pSSD1963->Display.WriteCommand)
    pSSD1963->Display.WriteCommand  = SSD1963_WriteCommand;
  
	SSD1963_PowerOn();
	SSD1963_Clean(pSSD1963->Data.BColor);
	
	SSD1963Set(BL);
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
void SSD1963_Reset(void)
{
	SSD1963Set(RST);
	LCD_DelaymS(5);				//SysTick延时nmS
	SSD1963Crl(RST);;
	LCD_DelaymS(5);				//SysTick延时nmS
	SSD1963Set(RST);
	LCD_DelaymS(10);				//SysTick延时nmS
}
/*******************************************************************************
* 函数名			:	SSD1963_WriteIndex
* 功能描述		:	写指定寄存器 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
unsigned short SSD1963_ReadData(void)
{
	unsigned short Data	=	0;
#if	1	//Bus16Bit
	SSD1963Crl(RD);	//LCD_RD_LOW;
	Data	=	SSD1963_DATABUS_PORT->IDR;
	SSD1963Set(RD);	//LCD_RD_HIGH;
#else	
	SSD1963Crl(RD);	//LCD_RD_LOW;
	Data	=	SSD1963_DATABUS_PORT->IDR;
	SSD1963Set(RD);	//LCD_RD_HIGH;
	
	Data	<<=8;
	
	SSD1963Crl(RD);	//LCD_RD_LOW;
	Data	|=	SSD1963_DATABUS_PORT->IDR;
	SSD1963Set(RD);	//LCD_RD_HIGH;
#endif	
	return Data;
}
/*******************************************************************************
* 函数名			:	SSD1963_ReadRegister
* 功能描述		:	读指定寄存器 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
unsigned short SSD1963_ReadRegister(unsigned	short	Addr)
{
	unsigned short Data	=	0;
	SSD1963Crl(CS);	//LCD_CS_LOW;
	//---------------------Write Index
	SSD1963_WriteAddr(Addr);
	//---------------------Read Data
	GPIO_Configuration_IPU	(SSD1963_DATABUS_PORT,SSD1963_DATABUS_Pin);			//将GPIO相应管脚配置为上拉输入模式----V20170605
	Data	=	SSD1963_ReadData();
	SSD1963Set(CS);	//LCD_CS_HIGH;
	GPIO_Configuration_OPP50	(SSD1963_DATABUS_PORT,SSD1963_DATABUS_Pin);		//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度2MHz----V20170605	
	return Data;
}
/*******************************************************************************
* 函数名			:	SSD1963_WriteIndex
* 功能描述		:	写指定寄存器 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
void SSD1963_WriteData(unsigned	short	Data)
{
#if	1	//Bus16Bit
	SSD1963Crl(WR);	//LCD_WR_LOW;
	SSD1963_DATABUS_PORT->ODR = Data;
	SSD1963Set(WR);	//LCD_WR_HIGH;
#else
	SSD1963Crl(WR);	//LCD_WR_LOW;
	SSD1963_DATABUS_PORT->ODR = Data>>8;
	SSD1963Set(WR);	//LCD_WR_HIGH;
	
	SSD1963Crl(WR);	//LCD_WR_LOW;
	SSD1963_DATABUS_PORT->ODR = Data&0xFF;
	SSD1963Set(WR);	//LCD_WR_HIGH;
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
void SSD1963_WriteAddr(unsigned	short	Addr)
{
	SSD1963Crl(DC);	//LCD_DC_LOW;		//RS
	SSD1963_WriteData(Addr);
	SSD1963Set(DC);	//LCD_DC_HIGH;	//RS
}
/*******************************************************************************
* 函数名			:	SSD1963_WriteIndex
* 功能描述		:	写指定寄存器 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
void SSD1963_WriteIndex(unsigned	short	Index)
{
	SSD1963Crl(CS);	//LCD_CS_LOW;	
	SSD1963_WriteAddr(Index);
	SSD1963Set(CS);	//LCD_CS_HIGH;
}
/*******************************************************************************
* 函数名			:	SSD1963_WriteRegister
* 功能描述		:	写指定寄存器 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
void SSD1963_WriteRegister(unsigned	short	Addr,unsigned short Data)
{
	SSD1963Crl(CS);	//LCD_CS_LOW;	
	//---------------------Write Index
	SSD1963_WriteAddr(Addr);
	//---------------------Write Data
	SSD1963_WriteData(Data);	
	SSD1963Set(CS);	//LCD_CS_HIGH;	
}
/*******************************************************************************
* 函数名			:	SSD1963_WriteCommand
* 功能描述		:	读指定寄存器 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
void SSD1963_WriteCommand(unsigned	short	Index,unsigned short Cmd)
{
	SSD1963_WriteRegister(Index,Cmd);
}
/*******************************************************************************
* 函数名			:	SSD1963_WriteGRAM
* 功能描述		:	写指定寄存器 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
void SSD1963_WriteGRAM(unsigned	short* RAM,unsigned long length)
{
	unsigned	long	i	=	0;
	SSD1963Crl(CS);	//LCD_CS_LOW;
	pSSD1963->Display.WriteIndex(0X3C);
	for(i=0;i<length;i++)
	{
		pSSD1963->Display.WriteData(RAM[i]);
	}
	SSD1963Set(CS);	//LCD_CS_HIGH;
}
/*******************************************************************************
* 函数名			:	SSD1963_WriteGRAM
* 功能描述		:	写指定寄存器 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
void SSD1963_ReadGRAM(unsigned	short* RAM,unsigned long length)
{
	unsigned	long	i	=	0;
	SSD1963Crl(CS);	//LCD_CS_LOW;
	SSD1963_WriteIndex(0X3E);
	GPIO_Configuration_IPU	(SSD1963_DATABUS_PORT,SSD1963_DATABUS_Pin);			//将GPIO相应管脚配置为上拉输入模式----V20170605
	for(i=0;i<length;i++)
	{
		RAM[i]=SSD1963_ReadData();
	}
	SSD1963Set(CS);	//LCD_CS_HIGH;
	GPIO_Configuration_OPP50	(SSD1963_DATABUS_PORT,SSD1963_DATABUS_Pin);		//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度2MHz----V20170605	
}
/**************************************************************************************************
* [Function] LCD_PowerOff:  关闭LCD 电源
* [No param]
**************************************************************************************************/
void SSD1963_PowerOff( void )
{
	LCD_BL_OFF;		//关背光
	SSD1963_WriteCommand( 0x10, 0 );	
}
/*******************************************************************************
*函数名		:	Lcd_Init
*功能描述	:	STM32内部温度传感器配置
*输入			: 
*输出			:	无
*返回值		:	无
*例程			:
*******************************************************************************/
void SSD1963_PowerOn(void)
{

	u16 time=2000;
	u16	temp=time;
//调用一次这些函数，免得编译的时候提示警告
	//1）——————————复位
//	SSD1963_BACKLIGHT_OFF;	//关背光
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
	SSD1963Crl(CS);	//LCD_CS_LOW;
	//3）——————————设置系统时钟  晶振频率 10MHz  250MHz < VCO < 800MHz
	pSSD1963->Display.WriteIndex(0x00E2);						//PLL multiplier, set PLL clock to 120M Start the PLL. Before the start, the system was operated with the crystal oscillator or clock input
	pSSD1963->Display.WriteData(0x0023);	    				//设置倍频 N=0x36 for 6.5M, 0x23 for 10M crystal
	pSSD1963->Display.WriteData(0x0001);							//设置分频
	pSSD1963->Display.WriteData(0x0004);							//完成设置
	//4）——————————使能PLL
	pSSD1963->Display.WriteIndex(0x00E0);  					//PLL enable
	pSSD1963->Display.WriteData(0x0001);
	
	pSSD1963->Display.WriteIndex(0x00E0);
	pSSD1963->Display.WriteData(0x0003);
  LCD_DelaymS(10);
	//5）——————————软件复位
	pSSD1963->Display.WriteIndex(0x0001);  					//software reset
	//6）——————————设置扫描频率
	pSSD1963->Display.WriteIndex(0x00E6);						//PLL setting for PCLK, depends on resolution
	pSSD1963->Display.WriteData(0x0003);
	pSSD1963->Display.WriteData(0x00FF);
	pSSD1963->Display.WriteData(0x00FF);
	//7）——————————设置LCD面板模式 Set the LCD panel mode (RGB TFT or TTL)
	pSSD1963->Display.WriteIndex(0x00B0);						//LCD SPECIFICATION
	pSSD1963->Display.WriteData(0x0000);
	pSSD1963->Display.WriteData(0x0000);
	pSSD1963->Display.WriteData((LCD_HDP>>8)&0X00FF);  		//设置水平像素点个数高8位		Set HDP 
	pSSD1963->Display.WriteData(LCD_HDP&0X00FF);					//设置水平像素点个数低8位
	pSSD1963->Display.WriteData((LCD_VDP>>8)&0X00FF);  		//设置垂直像素点个数高8位		Set VDP
	pSSD1963->Display.WriteData(LCD_VDP&0X00FF);					//设置垂直像素点个数低8位
	pSSD1963->Display.WriteData(0x0000);									//设置奇偶行RGB顺序，默认0，Even line RGB sequence&Odd line RGB sequence
	//8）——————————设置水平期 Set Horizontal Period
	pSSD1963->Display.WriteIndex(0x00B4);							//HSYNC
	pSSD1963->Display.WriteData((LCD_HT>>8)&0X00FF);  	//High byte of horizontal total period
	pSSD1963->Display.WriteData(LCD_HT&0X00FF);					//Low byte of the horizontal total period (display + non-display) in pixel clock (POR = 10101111)
																			//Horizontal total period = (HT + 1) pixels
	pSSD1963->Display.WriteData((LCD_HPS>>8)&0X00FF);  	//High byte of the non-display period between the start of the horizontal sync (LLINE) signal and the first
																			//display data. (POR = 000)
	pSSD1963->Display.WriteData(LCD_HPS&0X00FF);
	pSSD1963->Display.WriteData(LCD_HPW);			   //Set HPW
	pSSD1963->Display.WriteData((LCD_LPS>>8)&0X00FF);  //Set HPS
	pSSD1963->Display.WriteData(LCD_LPS&0X00FF);
	pSSD1963->Display.WriteData(0x0000);
	//9）——————————设置垂直期	Set Vertical Period
	pSSD1963->Display.WriteIndex(0x00B6);							//VSYNC
	pSSD1963->Display.WriteData((LCD_VT>>8)&0X00FF);   //Set VT
	pSSD1963->Display.WriteData(LCD_VT&0X00FF);
	pSSD1963->Display.WriteData((LCD_VPS>>8)&0X00FF);  //Set VPS
	pSSD1963->Display.WriteData(LCD_VPS&0X00FF);
	pSSD1963->Display.WriteData(LCD_VPW);			   //Set VPW
	pSSD1963->Display.WriteData((LCD_FPS>>8)&0X00FF);  //Set FPS
	pSSD1963->Display.WriteData(LCD_FPS&0X00FF);	
	//10）——————————配置GPIO
	pSSD1963->Display.WriteIndex(0x00B8);
	pSSD1963->Display.WriteData(0x0007);    //GPIO3=input, GPIO[2:0]=output //输出模式
	pSSD1963->Display.WriteData(0x0001);   	//0 GPIO0 is used to control the panel power with Enter Sleep Mode 0x10 or Exit Sleep Mode 0x11.
													//1 GPIO0 is used as normal GPIO
	//11）——————————设置GPIO（设置扫描方向） Set GPIO value for GPIO configured as output
	pSSD1963->Display.WriteIndex(0x00BA);
	pSSD1963->Display.WriteData((LCD_LR&0XFF)|(LCD_UD&0XFF));    //GPIO[3:0] out 1
	//12）——————————设置地址模式	Set Address Mode
	pSSD1963->Display.WriteIndex(0x0036); //rotation
	pSSD1963->Display.WriteData(0x0000);
	//13）——————————设置数据接口 Set Pixel Data Interface/Pixel Data Interface Format
	pSSD1963->Display.WriteIndex(0x00F0); //pixel data interface
	pSSD1963->Display.WriteData(0x0003);
	
	//14）——————————设置垂直期
	pSSD1963->Display.WriteIndex(0x0029); //display on
	//15）——————————设置垂直期
	pSSD1963->Display.WriteIndex(0x00d0); 
	pSSD1963->Display.WriteData(0x000D);
	SSD1963Set(CS);	//LCD_CS_HIGH;
}
/*******************************************************************************
*函数名		:	Address_set
*功能描述	:	STM32内部温度传感器配置
*输入			: 
*输出			:	无
*返回值		:	无
*例程			:
*******************************************************************************/
void SSD1963_SetWindowAddress(unsigned short x1,unsigned short y1,unsigned short x2,unsigned short y2)
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
	pSSD1963->Display.WriteIndex(0x002A);			//设置列地址
	pSSD1963->Display.WriteData(LCDSYS->Data.HSX>>8);		//起始地址高8位
	pSSD1963->Display.WriteData(LCDSYS->Data.HSX);			//起始地址低8位
	pSSD1963->Display.WriteData(LCDSYS->Data.HEX>>8);		//结束地址高8位
	pSSD1963->Display.WriteData(LCDSYS->Data.HEX);			//行结束地址低8位
	
	pSSD1963->Display.WriteIndex(0x002b);			//设置页地址	
	pSSD1963->Display.WriteData(LCDSYS->Data.VSY>>8);
	pSSD1963->Display.WriteData(LCDSYS->Data.VSY);
	pSSD1963->Display.WriteData(LCDSYS->Data.VEY>>8);
	pSSD1963->Display.WriteData(LCDSYS->Data.VEY);
	
	pSSD1963->Display.WriteIndex(0x0036);			//设置页地址
	pSSD1963->Display.WriteData(Model);

	pSSD1963->Display.WriteIndex(0x002c);			//写内存起始地址					 						 
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
void SSD1963_DrawDot(
									unsigned short HSX,			//点X坐标*/
									unsigned short HSY,			//点Y坐标*/
									unsigned short Color		//点颜色*/	
								)
{
	SSD1963_SetWindowAddress(HSX,HSY,HSX,HSY);	//设置光标位置
	SSD1963_WriteGRAM(&Color,1);
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
void SSD1963_DrawLine(
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
		SSD1963_DrawDot(uRow,uCol,Color);			//画点 
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
void SSD1963_DrawCircle(
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
			SSD1963_DrawLine(x,y,x-b,y-a,color);             //3           
			SSD1963_DrawLine(x,y,x+b,y-a,color);             //0           
			SSD1963_DrawLine(x,y,x-a,y+b,color);             //1       
			SSD1963_DrawLine(x,y,x-b,y-a,color);             //7           
			SSD1963_DrawLine(x,y,x-a,y-b,color);             //2             
			SSD1963_DrawLine(x,y,x+b,y+a,color);             //4               
			SSD1963_DrawLine(x,y,x+a,y-b,color);             //5
			SSD1963_DrawLine(x,y,x+a,y+b,color);             //6 
			SSD1963_DrawLine(x,y,x-b,y+a,color);             
			a++;
			//使用Bresenham算法画圆     
			if(di<0)
				di +=4*a+6;	  
			else
			{
				di+=10+4*(a-b);   
				b--;
			}
			SSD1963_DrawLine(x,y,x+a,y+b,color);				//AB 两个坐标画一条直线
		}
		else
		{
			SSD1963_DrawDot(x-b,y-a,color);             //3           
			SSD1963_DrawDot(x+b,y-a,color);             //0           
			SSD1963_DrawDot(x-a,y+b,color);             //1       
			SSD1963_DrawDot(x-b,y-a,color);             //7           
			SSD1963_DrawDot(x-a,y-b,color);             //2             
			SSD1963_DrawDot(x+b,y+a,color);             //4               
			SSD1963_DrawDot(x+a,y-b,color);             //5
			SSD1963_DrawDot(x+a,y+b,color);             //6 
			SSD1963_DrawDot(x-b,y+a,color);             
			a++;
			//使用Bresenham算法画圆     
			if(di<0)
				di +=4*a+6;	  
			else
			{
				di+=10+4*(a-b);   
				b--;
			}
				SSD1963_DrawDot(x+a,y+b,color);
		}
	}
}
/**************************************************************************************************
* [Function] LCD_DrawRectangle:  画一下矩形框
* [param01]t_Point top_p: 顶点坐标值
* [param02]t_Point botton_p : 地板坐标值
**************************************************************************************************/
void SSD1963_DrawRectangle(u16 x1,u16 y1,u16 x2,u16 y2,u16 color)
{
	SSD1963_DrawLine( x1, y1,	x1,	y2, color );
	SSD1963_DrawLine( x1, y1,	x2,	y1, color );
	SSD1963_DrawLine( x2, y1,	x2,	y2, color );
	SSD1963_DrawLine( x1, y2,	x2,	y2, color );
}
/*******************************************************************************
*函数名			:	ILI9326_Fill
*功能描述		:	在指定区域内填充指定颜色;区域大小:(xend-xsta)*(yend-ysta)
*输入				: 
*返回值			:	无
*******************************************************************************/
void SSD1963_Fill(
							unsigned short x1, unsigned short y1, 	//x1,y1:起点坐标
							unsigned short x2, unsigned short y2,		//x2,y2:终点坐标
							u16 Color
)
{          
	unsigned int x;
	unsigned int y;	
	SSD1963_SetWindowAddress(x1,y1,x2,y2);
	pSSD1963->Display.WriteIndex( 0X2C );
	SSD1963Crl(CS);	//LCD_CS_LOW;
	for(x=0;x<=x2-x1;x++)
	{
		for(y=0;y<=y2-y1;y++)
		{
			pSSD1963->Display.WriteData(Color);							//写数据
		}
	}	
	SSD1963Set(CS);	//LCD_CS_HIGH;
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
void SSD1963_Clean(u16 Color)	//清除屏幕函数
{
	unsigned short x,y;
	unsigned short HSX,HEX,HSY,HEY,MaxH,MaxV;
	unsigned long	length	=	0;
	eRotate	Rotate	=	pSSD1963->Flag.Rotate;
	
	MaxH	=	pSSD1963->Data.MaxH;
	MaxV	=	pSSD1963->Data.MaxV;	
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
	SSD1963_Fill(HSX,HSY,HEX,HEY,Color);
}
/**************************************************************************************************
* [Function] ILI9326_SetBackground:  设置背景颜色
* [param01]u16 BackColor: 背景颜色值
**************************************************************************************************/
void SSD1963_SetBackground(  u16 BackColor )
{
	pSSD1963->Data.BColor	=	BackColor;
	SSD1963_Clean(BackColor);	//清除屏幕函数
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
void SSD1963_ShowChar(
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
	
	SSD1963_SetWindowAddress(x1,y1,x2,y2);//设置显示区域	
	pSSD1963->Display.WriteIndex( 0X2C );
	SSD1963Crl(CS);	//LCD_CS_LOW;
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
				LCD_PEN_COLOR=pSSD1963->Data.BColor;
			pSSD1963->Display.WriteData(LCD_PEN_COLOR);
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
          LCD_PEN_COLOR=pSSD1963->Data.BColor;
        pSSD1963->Display.WriteData(LCD_PEN_COLOR);
        temp=temp<<1;
      }
      i++;
    }		
	}
	SSD1963Set(CS);	//LCD_CS_HIGH;
}
/*******************************************************************************
* 函数名			:	function
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
*******************************************************************************/
void SSD1963_ShowWord(
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
	SSD1963_SetWindowAddress(x1,y1,x2,y2);//设置显示区域
	pSSD1963->Display.WriteIndex( 0X2C );
	SSD1963Crl(CS);	//LCD_CS_LOW;
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
				LCD_PEN_COLOR=pSSD1963->Data.BColor;
			pSSD1963->Display.WriteData(LCD_PEN_COLOR);
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
          LCD_PEN_COLOR=pSSD1963->Data.BColor;
        pSSD1963->Display.WriteData(LCD_PEN_COLOR);
        temp=temp<<1;
      }
      i++;
    }			
	}
	SSD1963Set(CS);	//LCD_CS_HIGH;
}



