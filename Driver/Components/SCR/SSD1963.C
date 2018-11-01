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
	
	pSSD1963		=	pInfo;		//指针指向	
	
	pSSD1963->Data.MaxH	=	SSD1963_H;					//最大水平宽度
	pSSD1963->Data.MaxV	=	SSD1963_V;					//最大垂直高度	
  
  pSSD1963->Data.BColor = LCD565_BLACK;
  pSSD1963->Data.PColor = LCD565_WHITE;
	
	pSSD1963->Display.WriteAddress    =	SSD1963_SetWindowAddress;
	pSSD1963->Display.PowerOn         =	SSD1963_PowerOn;
	pSSD1963->Display.DispOff         =	SSD1963_PowerOn;		//临时引用函数地址
}
/*******************************************************************************
*函数名		:	SSD1963_BackLightOn
*功能描述	:	开背光
*输入			: 
*输出			:	无
*返回值		:	无
*例程			:
*******************************************************************************/
void SSD1963_BackLightOn(void)
{
	 pSSD1963->Port.sBL_PORT->BSRR  = pSSD1963->Port.sBL_Pin;
}
/*******************************************************************************
*函数名		:	SSD1963_BackLightOff
*功能描述	:	关背光
*输入			: 
*输出			:	无
*返回值		:	无
*例程			:
*******************************************************************************/
void SSD1963_BackLightOff(void)
{
  pSSD1963->Port.sBL_PORT->BRR  = pSSD1963->Port.sBL_Pin;
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
	LCD_WriteIndex(0x002A);			//设置列地址
	LCD_WriteData(LCDSYS->Data.HSX>>8);		//起始地址高8位
	LCD_WriteData(LCDSYS->Data.HSX);			//起始地址低8位
	LCD_WriteData(LCDSYS->Data.HEX>>8);		//结束地址高8位
	LCD_WriteData(LCDSYS->Data.HEX);			//行结束地址低8位
	
	LCD_WriteIndex(0x002b);			//设置页地址	
	LCD_WriteData(LCDSYS->Data.VSY>>8);
	LCD_WriteData(LCDSYS->Data.VSY);
	LCD_WriteData(LCDSYS->Data.VEY>>8);
	LCD_WriteData(LCDSYS->Data.VEY);
	
	LCD_WriteIndex(0x0036);			//设置页地址
	LCD_WriteData(Model);

	LCD_WriteIndex(0x002c);			//写内存起始地址 
					 						 
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
	LCD_RST_LOW;
	LCD_RST_HIGH;
	while(temp--);			//等待晶振启动
	//2）——————————复位
	LCD_CS_HIGH;			//先取消片选
	LCD_RD_HIGH;
	LCD_WR_LOW;				//总线功能为写数据
	LCD_CS_LOW;  		//使能
  LCD_DelaymS(10);
	//3）——————————设置系统时钟  晶振频率 10MHz  250MHz < VCO < 800MHz
	LCD_WriteIndex(0x00E2);						//PLL multiplier, set PLL clock to 120M Start the PLL. Before the start, the system was operated with the crystal oscillator or clock input
	LCD_WriteData(0x0023);	    				//设置倍频 N=0x36 for 6.5M, 0x23 for 10M crystal
	LCD_WriteData(0x0001);							//设置分频
	LCD_WriteData(0x0004);							//完成设置
	//4）——————————使能PLL
	LCD_WriteIndex(0x00E0);  					//PLL enable
	LCD_WriteData(0x0001);
	
	LCD_WriteIndex(0x00E0);
	LCD_WriteData(0x0003);
  LCD_DelaymS(10);
	//5）——————————软件复位
	LCD_WriteIndex(0x0001);  					//software reset
	//6）——————————设置扫描频率
	LCD_WriteIndex(0x00E6);						//PLL setting for PCLK, depends on resolution
	LCD_WriteData(0x0003);
	LCD_WriteData(0x00FF);
	LCD_WriteData(0x00FF);
	//7）——————————设置LCD面板模式 Set the LCD panel mode (RGB TFT or TTL)
	LCD_WriteIndex(0x00B0);						//LCD SPECIFICATION
	LCD_WriteData(0x0000);
	LCD_WriteData(0x0000);
	LCD_WriteData((LCD_HDP>>8)&0X00FF);  		//设置水平像素点个数高8位		Set HDP 
	LCD_WriteData(LCD_HDP&0X00FF);					//设置水平像素点个数低8位
	LCD_WriteData((LCD_VDP>>8)&0X00FF);  		//设置垂直像素点个数高8位		Set VDP
	LCD_WriteData(LCD_VDP&0X00FF);					//设置垂直像素点个数低8位
	LCD_WriteData(0x0000);									//设置奇偶行RGB顺序，默认0，Even line RGB sequence&Odd line RGB sequence
	//8）——————————设置水平期 Set Horizontal Period
	LCD_WriteIndex(0x00B4);							//HSYNC
	LCD_WriteData((LCD_HT>>8)&0X00FF);  	//High byte of horizontal total period
	LCD_WriteData(LCD_HT&0X00FF);					//Low byte of the horizontal total period (display + non-display) in pixel clock (POR = 10101111)
																			//Horizontal total period = (HT + 1) pixels
	LCD_WriteData((LCD_HPS>>8)&0X00FF);  	//High byte of the non-display period between the start of the horizontal sync (LLINE) signal and the first
																			//display data. (POR = 000)
	LCD_WriteData(LCD_HPS&0X00FF);
	LCD_WriteData(LCD_HPW);			   //Set HPW
	LCD_WriteData((LCD_LPS>>8)&0X00FF);  //Set HPS
	LCD_WriteData(LCD_LPS&0X00FF);
	LCD_WriteData(0x0000);
	//9）——————————设置垂直期	Set Vertical Period
	LCD_WriteIndex(0x00B6);							//VSYNC
	LCD_WriteData((LCD_VT>>8)&0X00FF);   //Set VT
	LCD_WriteData(LCD_VT&0X00FF);
	LCD_WriteData((LCD_VPS>>8)&0X00FF);  //Set VPS
	LCD_WriteData(LCD_VPS&0X00FF);
	LCD_WriteData(LCD_VPW);			   //Set VPW
	LCD_WriteData((LCD_FPS>>8)&0X00FF);  //Set FPS
	LCD_WriteData(LCD_FPS&0X00FF);	
	//10）——————————配置GPIO
	LCD_WriteIndex(0x00B8);
	LCD_WriteData(0x0007);    //GPIO3=input, GPIO[2:0]=output //输出模式
	LCD_WriteData(0x0001);   	//0 GPIO0 is used to control the panel power with Enter Sleep Mode 0x10 or Exit Sleep Mode 0x11.
													//1 GPIO0 is used as normal GPIO
	//11）——————————设置GPIO（设置扫描方向） Set GPIO value for GPIO configured as output
	LCD_WriteIndex(0x00BA);
	LCD_WriteData((LCD_LR&0XFF)|(LCD_UD&0XFF));    //GPIO[3:0] out 1
	//12）——————————设置地址模式	Set Address Mode
	LCD_WriteIndex(0x0036); //rotation
	LCD_WriteData(0x0000);
	//13）——————————设置数据接口 Set Pixel Data Interface/Pixel Data Interface Format
	LCD_WriteIndex(0x00F0); //pixel data interface
	LCD_WriteData(0x0003);
	
	//14）——————————设置垂直期
	LCD_WriteIndex(0x0029); //display on
	//15）——————————设置垂直期
	LCD_WriteIndex(0x00d0); 
	LCD_WriteData(0x000D);
	
//	temp=time;
//	while(temp--);			//等待晶振启动
//	LCD_Clean(LCDSYS->Data.BColor);	//以背景色清屏
	
////	SSD1963_BackLightOn();    //开背光
//  
//  for(time=0xFFFF;time>0;time--)
//  {
//  }
}

///*******************************************************************************
//*函数名		:	LCD_DrawPoint
//*功能描述	:	画点
//*输入			: POINT_COLOR:此点的颜色
//*输出			:	无
//*返回值		:	无
//*例程			:
//*******************************************************************************/
//void SSD1963_DrawPoint(u16 x,u16 y)
//{
//	SSD1963_SetWindowAddress(x,y,x,y);//设置光标位置 
//	LCD_WriteData(LCDSYS->Data.PColor); 	    
//}
///*******************************************************************************
//*函数名		:	LCD_DrawPoint_big
//*功能描述	:	画一个大点
//*输入			: POINT_COLOR:此点的颜色
//*输出			:	无
//*返回值		:	无
//*例程			:
//*******************************************************************************/
//void SSD1963_DrawPoint_big(u16 x,u16 y)
//{
//	SSD1963_Fill(x-1,y-1,x+1,y+1,LCDSYS->Data.PColor);
//}
/*******************************************************************************
*函数名		:	LCD_Fill
*功能描述	:	在指定区域内填充指定颜色
*输入			: 区域大小:(xend-xsta)*(yend-ysta)
*输出			:	无
*返回值		:	无
*例程			:
*******************************************************************************/
//void SSD1963_Fill(
//							u16 xsta,u16 ysta,
//							u16 xend,u16 yend,u16 color
//)
//{          
//	u16 i,j; 
//	SSD1963_SetWindowAddress(xsta,ysta,xend,yend);      //设置光标位置 
//	for(i=ysta;i<=yend;i++)
//	{													   	 	
//		for(j=xsta;j<=xend;j++)
//			LCD_WriteData(color);//设置光标位置 	    
//	} 					  	    
//}
///*******************************************************************************
//*函数名		:	LCD_DrawLine
//*功能描述	:	画线
//*输入			: x1,y1:起点坐标
//						x2,y2:终点坐标
//*输出			:	无
//*返回值		:	无
//*例程			:
//*******************************************************************************/
//void SSD1963_DrawLine(
//									u16 x1, u16 y1, 	//x1,y1:起点坐标
//									u16 x2, u16 y2		//x2,y2:终点坐标
//)
//{
//	u16 t; 
//	int xerr=0,yerr=0,delta_x,delta_y,distance; 
//	int incx,incy,uRow,uCol; 

//	delta_x=x2-x1; //计算坐标增量 
//	delta_y=y2-y1;
//	
//	uRow=x1; 
//	uCol=y1; 
//	
//	if(delta_x>0)
//		incx=1; //设置单步方向 
//	else if(delta_x==0)
//		incx=0;//垂直线 
//	else
//	{
//		incx=-1;
//		delta_x=-delta_x;
//	}
//	
//	if(delta_y>0)
//		incy=1; 
//	else if(delta_y==0)
//		incy=0;//水平线 
//	else
//	{
//			incy=-1;
//			delta_y=-delta_y;
//	} 
//		
//	if( delta_x>delta_y)
//		distance=delta_x; //选取基本增量坐标轴 
//	else
//		distance=delta_y; 
//	
//	for(t=0;t<=distance+1;t++ )//画线输出 
//	{  
//		SSD1963_DrawPoint(uRow,uCol);//画点 
//		xerr+=delta_x ; 
//		yerr+=delta_y ; 
//		if(xerr>distance) 
//		{ 
//			xerr-=distance; 
//			uRow+=incx; 
//		} 
//		if(yerr>distance) 
//		{ 
//			yerr-=distance; 
//			uCol+=incy; 
//		} 
//	}  
//}
///*******************************************************************************
//*函数名		:	LCD_DrawRectangle
//*功能描述	:	画矩形
//*输入			: 
//*输出			:	无
//*返回值		:	无
//*例程			:
//*******************************************************************************/
//void SSD1963_DrawRectangle(
//												u16 x1, 		//x1
//												u16 y1, 		//y1
//												u16 x2, 		//x2
//												u16 y2			//y2
//)
//{
//	SSD1963_DrawLine(x1,y1,x2,y1);		
//	SSD1963_DrawLine(x1,y1,x1,y2);
//	SSD1963_DrawLine(x1,y2,x2,y2);
//	SSD1963_DrawLine(x2,y1,x2,y2);
//}
///*******************************************************************************
//*函数名		:	Draw_Circle
//*功能描述	:	在指定位置画一个指定大小的圆
//*输入			: (x,y):中心点
//						r    :半径
//*输出			:	无
//*返回值		:	无
//*例程			:
//*******************************************************************************/
//void SSD1963_DrawCircle(
//												u16 x0,		//(x,y):中心点
//												u16 y0,		//(x,y):中心点
//												u8 r			//r    :半径
//)
//{
//	int a,b;
//	int di;
//	a=0;b=r;	  
//	di=3-(r<<1);             //判断下个点位置的标志
//	while(a<=b)
//	{
//		SSD1963_DrawPoint(x0-b,y0-a);             //3           
//		SSD1963_DrawPoint(x0+b,y0-a);             //0           
//		SSD1963_DrawPoint(x0-a,y0+b);             //1       
//		SSD1963_DrawPoint(x0-b,y0-a);             //7           
//		SSD1963_DrawPoint(x0-a,y0-b);             //2             
//		SSD1963_DrawPoint(x0+b,y0+a);             //4               
//		SSD1963_DrawPoint(x0+a,y0-b);             //5
//		SSD1963_DrawPoint(x0+a,y0+b);             //6 
//		SSD1963_DrawPoint(x0-b,y0+a);             
//		a++;
//		//使用Bresenham算法画圆     
//		if(di<0)di +=4*a+6;	  
//		else
//		{
//			di+=10+4*(a-b);   
//			b--;
//		} 
//		SSD1963_DrawPoint(x0+a,y0+b);
//	}
//}

///*******************************************************************************
//*函数名		:	LCD_ShowChar
//*功能描述	:	在指定位置显示一个字符
//*输入			: x,y		:起点坐标
//						num		:要显示的字符:" "--->"~"
//						mode	:叠加方式(1)还是非叠加方式(0)
//						num		:要显示的字符:" "--->"~"
//*输出			:	无
//*返回值		:	无
//*例程			:
//*******************************************************************************/
//void SSD1963_ShowChar(u16 x,u16 y,u8 num,u8 mode)
//{
//	u8 temp;
//	u8 pos,t;
//	u16 x0=x;
//	u16 colortemp=LCDSYS->Data.PColor;      
//	if(x>SSD1963_H-16||y>SSD1963_V-16)return;	    
//	//设置窗口		   
//	num=num-' ';//得到偏移后的值
////	num=41;//得到偏移后的值
//	SSD1963_SetWindowAddress(x,y,x+8-1,y+16-1);      //设置光标位置 
//	if(!mode) //非叠加方式
//	{
//		for(pos=0;pos<16;pos++)
//		{ 
//			temp=code_asc2_1608[(u16)num*16+pos];		 	//调用1608字体
////			temp=code_num_1608[(u16)num*16+pos];		 //调用1608字体
//			for(t=0;t<8;t++)
//			{                 
//				if(temp&0x01)
//					colortemp=LCDSYS->Data.PColor;
//				else
//					colortemp=LCDSYS->Data.BColor;
//				LCD_WriteData(colortemp);	
//				temp>>=1; 
//				x++;
//			}
//			x=x0;
//			y++;
//		}	
//	}else//叠加方式
//	{
//		for(pos=0;pos<16;pos++)
//		{
//			temp=code_asc2_1608[(u16)num*16+pos];		 //调用1608字体
//			for(t=0;t<8;t++)
//			{                 
//				if(temp&0x01)
//					SSD1963_DrawPoint(x+t,y+pos);				//画一个点     
//				temp>>=1; 
//			}
//		}
//	}
//}
//#endif
///*******************************************************************************
//*函数名		:	mypow
//*功能描述	:	m^n函数
//*输入			: 
//*输出			:	无
//*返回值		:	无
//*例程			:
//*******************************************************************************/
//u32 mypow(u8 m,u8 n)
//{
//	u32 result=1;	 
//	while(n--)
//		result*=m;    
//	return result;
//}
///*******************************************************************************
//*函数名		:	LCD_ShowNum
//*功能描述	:	显示数字
//*输入			: x,y		:起点坐标
//						len 	:数字的位数
//						color	:颜色
//						num		:数值(0~4294967295);
//*输出			:	无
//*返回值		:	无
//*例程			:
//*******************************************************************************/
//void SSD1963_ShowNum(u16 x,u16 y,u32 num,u8 len)
//{         	
//	u8 t,temp;
//	u8 enshow=0;
//	num=(u32)num;
//	for(t=0;t<len;t++)
//	{
//		temp=(num/mypow(10,len-t-1))%10;
//		if(enshow==0&&t<(len-1))
//		{
//			if(temp==0)
//			{
//				SSD1963_ShowChar(x+8*t,y,' ',0);
//				continue;
//			}else enshow=1; 
//		 	 
//		}
//	 	SSD1963_ShowChar(x+8*t,y,temp+48,0); 
//	}
//}
///*******************************************************************************
//*函数名		:	LCD_ShowEn
//*功能描述	:	显示数字
//*输入			: x,y		:起点坐标
//						len 	:数字的位数
//						color	:颜色
//						num		:数值(0~4294967295);
//*输出			:	无
//*返回值		:	无
//*例程			:
//*******************************************************************************/
//void SSD1963_ShowEn(u16 x,u16 y,u32 num)
//{         	
//	u8 t=0,len=0;
//	u32 num2=num;
//	u8 enshow=0;
//	while(num2)
//	{
//		num2=num2/10;
//		len++;		
//	}
//	for(t=len;t>0;t--)
//	{
//		num2=mypow(10,t-1);
//		if(num>9)
//		{
//			enshow=num/num2;
//			num=num%num2;
//		}
//		else
//			enshow=(char)num;
//	 	SSD1963_ShowChar(x+8*(len-t),y,enshow+48,0); 
//	}
//}
///*******************************************************************************
//*函数名		:	LCD_Show2Num
//*功能描述	:	显示2个数字
//*输入			: x,y:起点坐标
//						num:数值(0~99);
//*输出			:	无
//*返回值		:	无
//*例程			:
//*******************************************************************************/
//void SSD1963_Show2Num(u16 x,u16 y,u16 num,u8 len)
//{         	
//	u8 t,temp;						   
//	for(t=0;t<len;t++)
//	{
//		temp=(num/mypow(10,len-t-1))%10;
//	 	SSD1963_ShowChar(x+8*t,y,temp+'0',0); 
//	}
//}

///*******************************************************************************
//*函数名		:	RGB888ToRGB565
//*功能描述	:	RGB888转RGB565颜色(分别取高位)
//*输入			: x,y:起点坐标
//						*p:字符串起始地址
//						用16字体
//*输出			:	无
//*返回值		:	无
//*例程			:
//*******************************************************************************/
//void RGB888ToRGB565(
//										unsigned char Color_R,		//RED	
//										unsigned char Color_G,		//GREEN
//										unsigned char Color_B,		//BLUE
//										u16 *RGB565
//)				//RGB888转RGB565颜色(分别取高位)
//{  
//	u16 temp=0;
//	temp|=(u16)(Color_R&0XF8)<<8;
//	temp|=(u16)(Color_G&0XFC)<<3;
//	temp|=(u16)(Color_B>>3);
//	*RGB565=temp;
//}










///*******************************************************************************
//*函数名			:	function
//*功能描述		:	关背光
//*输入				: 
//*返回值			:	无
//*******************************************************************************/
//void SSD1963_BACKLIGHToff(SSD1963_Pindef *Pinfo)
//{
//	GPIO_ResetBits(Pinfo->SSD1963_sBACKLIGHT_PORT, Pinfo->SSD1963_sBACKLIGHT_Pin);
//}
///*******************************************************************************
//*函数名			:	function
//*功能描述		:	函数功能说明
//*输入				: 
//*返回值			:	无
//*******************************************************************************/
//void SSD1963_BACKLIGHTon(SSD1963_Pindef *Pinfo)
//{
//	GPIO_SetBits(Pinfo->SSD1963_sBACKLIGHT_PORT, Pinfo->SSD1963_sBACKLIGHT_Pin);
//}
///*******************************************************************************
//*函数名			:	function
//*功能描述		:	函数功能说明
//*输入				: 
//*返回值			:	无
//*******************************************************************************/
//void SSD1963_REST(SSD1963_Pindef *Pinfo)
//{
//	GPIO_ResetBits(Pinfo->SSD1963_sREST_PORT, Pinfo->SSD1963_sREST_Pin);
//}
///*******************************************************************************
//*函数名			:	function
//*功能描述		:	函数功能说明
//*输入				: 
//*返回值			:	无
//*******************************************************************************/
//void SSD1963_EST(SSD1963_Pindef *Pinfo)
//{
//	GPIO_SetBits(Pinfo->SSD1963_sREST_PORT, Pinfo->SSD1963_sREST_Pin);
//}
///*******************************************************************************
//*函数名			:	function
//*功能描述		:	函数功能说明
//*输入				: 
//*返回值			:	无
//*******************************************************************************/
//void SSD1963_cRDlow(SSD1963_Pindef *Pinfo)
//{
//	GPIO_ResetBits(Pinfo->SSD1963_sRD_PORT, Pinfo->SSD1963_sRD_Pin);
//}
///*******************************************************************************
//*函数名			:	function
//*功能描述		:	函数功能说明
//*输入				: 
//*返回值			:	无
//*******************************************************************************/
//void SSD1963_cRDhigh(SSD1963_Pindef *Pinfo)
//{
//	GPIO_SetBits(Pinfo->SSD1963_sRD_PORT, Pinfo->SSD1963_sRD_Pin);
//}
///*******************************************************************************
//*函数名			:	function
//*功能描述		:	函数功能说明
//*输入				: 
//*返回值			:	无
//*******************************************************************************/
//void SSD1963_cDClow(SSD1963_Pindef *Pinfo)
//{
//	GPIO_ResetBits(Pinfo->SSD1963_sDC_PORT, Pinfo->SSD1963_sDC_Pin);
//}
///*******************************************************************************
//*函数名			:	function
//*功能描述		:	函数功能说明
//*输入				: 
//*返回值			:	无
//*******************************************************************************/
//void SSD1963_cDChigh(SSD1963_Pindef *Pinfo)
//{
//	GPIO_SetBits(Pinfo->SSD1963_sDC_PORT, Pinfo->SSD1963_sDC_Pin);
//}
///*******************************************************************************
//*函数名			:	function
//*功能描述		:	函数功能说明
//*输入				: 
//*返回值			:	无
//*******************************************************************************/
//void SSD1963_cWRlow(SSD1963_Pindef *Pinfo)
//{
//	GPIO_ResetBits(Pinfo->SSD1963_sWR_PORT, Pinfo->SSD1963_sWR_Pin);
//}
///*******************************************************************************
//*函数名			:	function
//*功能描述		:	函数功能说明
//*输入				: 
//*返回值			:	无
//*******************************************************************************/
//void SSD1963_cWRhigh(SSD1963_Pindef *Pinfo)
//{
//	GPIO_SetBits(Pinfo->SSD1963_sWR_PORT, Pinfo->SSD1963_sWR_Pin);
//}
///*******************************************************************************
//*函数名			:	function
//*功能描述		:	函数功能说明
//*输入				: 
//*返回值			:	无
//*******************************************************************************/
//void SSD1963_cCSlow(SSD1963_Pindef *Pinfo)
//{
//	GPIO_ResetBits(Pinfo->SSD1963_sCS_PORT, Pinfo->SSD1963_sCS_Pin);
//}
///*******************************************************************************
//*函数名			:	function
//*功能描述		:	函数功能说明
//*输入				: 
//*返回值			:	无
//*******************************************************************************/
//void SSD1963_cCShigh(SSD1963_Pindef *Pinfo)
//{
//	GPIO_SetBits(Pinfo->SSD1963_sCS_PORT, Pinfo->SSD1963_sCS_Pin);
//}












//#endif

