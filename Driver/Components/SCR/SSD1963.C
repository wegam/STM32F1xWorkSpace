//#ifdef	SSD1963

/********************************************************************************
***SSD1963 LCD屏驱动器
********************************************************************************/
#include "SSD1963.H"

#include "STM32_GPIO.H"

#include "stm32f10x_rcc.h"
#include "stm32f10x_type.h"
#include "stm32f10x_gpio.h"

#include "font.h"

#include	"stdio.h"			//用于printf
#include	"string.h"			//用于printf
#include	"stdarg.h"			//用于获取不确定个数的参数
#include	"stdlib.h"			//malloc动态申请内存空间
#include "LCD.H"
//#include <reg51.h>
//#include "intrins.h"
//#include "font\font.h"
//#include "sys\sys.h"
//#include "lcd\lcd.h"

unsigned char hanzidata;

LCDDef	*pSSD1963	=	0;		//内部驱动使用，不可删除
/*******************************************************************************
*函数名			:	function
*功能描述		:	函数功能说明
*输入				: 
*返回值			:	无
*******************************************************************************/
void SSD1963_Initialize(void*	pInfo)
{
	
	pSSD1963		=	(LCDDef*)pInfo;		//指针指向	
	
	pSSD1963->Data.MaxH	=	SSD1963_H;					//最大水平宽度
	pSSD1963->Data.MaxV	=	SSD1963_V;					//最大垂直高度	
  
//  pSSD1963->Data.BColor = LCD565_BLACK;
//  pSSD1963->Data.PColor = LCD565_WHITE;
	
	pSSD1963->Display.WriteAddress    =	SSD1963_SetWindowAddress;
	pSSD1963->Display.PowerOn         =	SSD1963_PowerOn;
	pSSD1963->Display.DispOff         =	SSD1963_PowerOn;		//临时引用函数地址
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
}


