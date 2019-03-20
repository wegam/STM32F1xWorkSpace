//#ifdef	ST7789V

/********************************************************************************
***ST7789V LCD屏驱动器
********************************************************************************/
#include "ST7789V.H"
//#include "LCD.H"
#include "STM32_GPIO.H"
#include "STM32_SYSTICK.H"
#include "STM32_PWM.H"

#include "GT32L32M0180.H"

#include	"stdio.h"			//用于printf
#include	"string.h"		//用于printf
#include	"stdarg.h"		//用于获取不确定个数的参数
#include	"stdlib.h"		//malloc动态申请内存空间




sST7789VDef	*pST7789V	=	0;		//内部驱动使用，不可删除

#define	ST7789V_CS_HIGH		(pST7789V->HWPort.sCS_PORT->BSRR	= pST7789V->HWPort.sCS_Pin)
#define	ST7789V_CS_LOW		(pST7789V->HWPort.sCS_PORT->BRR		=	pST7789V->HWPort.sCS_Pin)

#define	ST7789V_DC_HIGH		(pST7789V->HWPort.sDC_PORT->BSRR	= pST7789V->HWPort.sDC_Pin)		//RS
#define	ST7789V_DC_LOW		(pST7789V->HWPort.sDC_PORT->BRR		= pST7789V->HWPort.sDC_Pin)		//RS

#define	ST7789V_WR_HIGH		(pST7789V->HWPort.sWR_PORT->BSRR	= pST7789V->HWPort.sWR_Pin)
#define	ST7789V_WR_LOW		(pST7789V->HWPort.sWR_PORT->BRR		= pST7789V->HWPort.sWR_Pin)   //WriteEnable

#define	ST7789V_RD_HIGH		(pST7789V->HWPort.sRD_PORT->BSRR	= pST7789V->HWPort.sRD_Pin)
#define	ST7789V_RD_LOW		(pST7789V->HWPort.sRD_PORT->BRR		= pST7789V->HWPort.sRD_Pin)   //ReadEnable

#define	ST7789V_RST_HIGH	(pST7789V->HWPort.sREST_PORT->BSRR	= pST7789V->HWPort.sREST_Pin)
#define	ST7789V_RST_LOW		(pST7789V->HWPort.sREST_PORT->BRR		= pST7789V->HWPort.sREST_Pin)

//#define	ST7789V_TE_HIGH		(pST7789V->Port.sTE_PORT->BSRR	= pST7789V->Port.sTE_Pin)
//#define	ST7789V_TE_LOW		(pST7789V->Port.sTE_PORT->BRR	= pST7789V->Port.sTE_Pin)

//#define	ST7789V_BL_HIGH		(pST7789V->sBL_PORT->BSRR	= pST7789V->sBL_Pin)
//#define	ST7789V_BL_LOW		(pST7789V->sBL_PORT->BRR	= pST7789V->sBL_Pin)

#define ST7789V_DATABUS_PORT	(pST7789V->HWPort.sDATABUS_PORT)
#define ST7789V_DATABUS_Pin		(pST7789V->HWPort.sDATABUS_Pin)

#define	ST7789VSet(n)	ST7789V_##n##_HIGH
#define	ST7789VCrl(n)	ST7789V_##n##_LOW

#define ST7789V_BL_ON		PWM_OUT((TIM_TypeDef*) TIM2_BASE,PWM_OUTChannel2,1000,10)	//(R61509V_BL_PORT->BSRR = R61509V_BL_PIN)
#define ST7789V_BL_OFF	PWM_OUT((TIM_TypeDef*) TIM2_BASE,PWM_OUTChannel2,1,1000)		//(R61509V_BL_PORT->BRR = R61509V_BL_PIN)



//char	ST7789VStringBuffer[256]={0};			//记录format内码
/*******************************************************************************
*函数名			:	function
*功能描述		:	函数功能说明
*输入				: 
*返回值			:	无
*******************************************************************************/
void ST7789V_Initialize(void*	pInfo)
{
	sST7789VPortDef*	Port	=	NULL;
	if(NULL==	pInfo)
		return;
	pST7789V		=	(sST7789VDef*)pInfo;		//指针指向	

	Port	=	(sST7789VPortDef*)&pST7789V->HWPort;
	
	//==========================GPIO配置
//	GPIO_Configuration_OPP50	(Port->sBL_PORT,				Port->sBL_Pin);					//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度2MHz----V20170605
	GPIO_Configuration_OPP50	(Port->sRD_PORT,				Port->sRD_Pin);					//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度2MHz----V20170605
	GPIO_Configuration_OPP50	(Port->sREST_PORT,			Port->sREST_Pin);				//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度2MHz----V20170605
	GPIO_Configuration_OPP50	(Port->sDC_PORT,				Port->sDC_Pin);					//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度2MHz----V20170605
	GPIO_Configuration_OPP50	(Port->sWR_PORT,				Port->sWR_Pin);					//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度2MHz----V20170605
	GPIO_Configuration_OPP50	(Port->sCS_PORT,				Port->sCS_Pin);					//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度2MHz----V20170605
//	GPIO_Configuration_OPP50	(Port->sTE_PORT,				Port->sTE_Pin);					//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度2MHz----V20170605
	GPIO_Configuration_OPP50	(Port->sDATABUS_PORT,		Port->sDATABUS_Pin);		//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度2MHz----V20170605

//  pST7789V->Display.PowerOn   = ST7789V_PowerOn;
//  pST7789V->Display.ShowChar  = ST7789V_ShowChar;
//  pST7789V->Display.ShowWord  = ST7789V_ShowWord;
	
	//------------------------------------------旋转角度
	//pST7789V->ST7789VRotate	=	ST7789V_Rotate_90D;
	//ST7789V_Clean(pST7789V->ST7789VBColor);	//清除屏幕函数;
	ST7789V_PowerOn();
}
/*******************************************************************************
*函数名		:	LCD_ShowString
*功能描述	:	显示字符串高通字库
*输入			: x,y:起点坐标
						*p:字符串起始地址
						用16字体
*输出			:	无
*返回值		:	无
*例程			:
*******************************************************************************/
unsigned int ST7789V_Printf(u16 x,u16 y,u8 font,u16 color,const char *format,...)				//后边的省略号就是可变参数
{ 
	#include	"stdarg.h"		//用于获取不确定个数的参数
	#include	"stdlib.h"		//malloc动态申请内存空间
//		va_list ap; 										//VA_LIST 是在C语言中解决变参问题的一组宏，所在头文件：#include <stdarg.h>,用于获取不确定个数的参数
//		static char string[ 256 ];			//定义数组，
//  	va_start( ap, format );
//		vsprintf( string , format, ap );    
//		va_end( ap );
	
	char	ST7789VStringBuffer[256]={0};			//记录format内码
	//1)**********获取数据宽度
  u16 InputDataSize=0;
	//3)**********vArgList为定义的一个指向可变参数的变量，va_list以及下边要用到的va_start,va_end都是是在定义，可变参数函数中必须要用到宏， 在stdarg.h头文件中定义
	va_list vArgList; 
	//5)**********初始化vArgList的函数，使其指向可变参数的第一个参数，format是可变参数的前一个参数
	va_start(vArgList, format);
	//6)**********正常情况下返回生成字串的长度(除去\0),错误情况返回负值
	InputDataSize =vsnprintf(ST7789VStringBuffer,InputDataSize,format,vArgList);
	//7)**********结束可变参数的获取
	va_end(vArgList);                                      		
  if((8!=font)&&(12!=font)&&(16!=font)&&(24!=font)&&(32!=font))
  {
    font  = 32;
  }
	ST7789V_ShowString(x,y,font,color,InputDataSize,(unsigned char*)ST7789VStringBuffer);
	return InputDataSize;
}
/*******************************************************************************
*函数名		:	LCD_ShowString
*功能描述	:	显示字符串高通字库
*输入			: x,y:起点坐标
						*p:字符串起始地址
						用16字体
*输出			:	无
*返回值		:	无
*例程			:
*******************************************************************************/
unsigned int ST7789V_PrintfBK(u16 x,u16 y,u8 font,u16 BKColor,u16 PenColor,const char *format,...)				//后边的省略号就是可变参数
{ 
	#include	"stdarg.h"		//用于获取不确定个数的参数
	#include	"stdlib.h"		//malloc动态申请内存空间
//		va_list ap; 										//VA_LIST 是在C语言中解决变参问题的一组宏，所在头文件：#include <stdarg.h>,用于获取不确定个数的参数
//		static char string[ 256 ];			//定义数组，
//  	va_start( ap, format );
//		vsprintf( string , format, ap );    
//		va_end( ap );
	
	char	ST7789VStringBuffer[256]={0};			//记录format内码
	//1)**********获取数据宽度
  u16 InputDataSize=0;
	//3)**********vArgList为定义的一个指向可变参数的变量，va_list以及下边要用到的va_start,va_end都是是在定义，可变参数函数中必须要用到宏， 在stdarg.h头文件中定义
	va_list vArgList; 
	//5)**********初始化vArgList的函数，使其指向可变参数的第一个参数，format是可变参数的前一个参数
	va_start(vArgList, format);
	//6)**********正常情况下返回生成字串的长度(除去\0),错误情况返回负值
	InputDataSize =vsnprintf(ST7789VStringBuffer,InputDataSize,format,vArgList);
	//7)**********结束可变参数的获取
	va_end(vArgList);                                      		
  if((8!=font)&&(12!=font)&&(16!=font)&&(24!=font)&&(32!=font))
  {
    font  = 32;
  }
	ST7789V_ShowStringBK(x,y,font,BKColor,PenColor,InputDataSize,(unsigned char*)ST7789VStringBuffer);
	return InputDataSize;
}
/*******************************************************************************
* 函数名			:	function
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
*******************************************************************************/
void ST7789V_ShowString(
							u16 x,			//x				:起点x坐标
							u16 y,			//y				:起点y坐标
							u8 font,		//font		:字体大小
							u16 PenColor,//字体颜色
							u8 num,			//num			:字节数
							u8 *Buffer	//Buffer	:显示的内容缓存
)		//高通字库测试程序
{
	unsigned short	MaxV=ST7789V_V,MaxH=ST7789V_H;	//边界值
	unsigned char i=0;
	unsigned char CodeBuffer[256]={0};
	switch(pST7789V->ST7789VRotate)
	{
		case ST7789V_Rotate_0D:
			MaxV=ST7789V_V;
			MaxH=ST7789V_H;
		break;
		case ST7789V_Rotate_90D:
			MaxV=ST7789V_H;
			MaxH=ST7789V_V;
		break;
		case ST7789V_Rotate_180D:
			MaxV=ST7789V_V;
			MaxH=ST7789V_H;
		break;
		case ST7789V_Rotate_270D:
			MaxV=ST7789V_H;
			MaxH=ST7789V_V;
		break;
		default:break;		
	}
	for(i=0;i<num;i++)
	{
		unsigned char GetBufferLength	=	0;
		unsigned char dst=Buffer[i];
		unsigned char UnicodeFlag=0;
		unsigned char UnicodeAddr=0;
		//==================================Unicode
		//UnicodeFlag	=	UnicodeCheck(&Buffer[i],num-i);
		
		
		dst=Buffer[i];
		//A=====================双字节--汉字
		if(dst>0x80)
		{
			u16 word=dst<<8;
      
			dst=Buffer[i+1];
			word=word|dst;			
			//A1=====================显示超限换行
      if(x>MaxH-font)
      {
        x=0;
        y+=font;
      }
      //A2=====================显示到屏尾，从原点开始
      if(y>MaxV-font)
      {
        y=x=0;
      }
      //A3=====================读取点阵数据
			GetBufferLength	=	GT32L32_GetCode(font,word,CodeBuffer);		//从字库中读数据并返回数据长度
			//GetBufferLength	=	GT32L32_GetAntennaCode(3,CodeBuffer);
			//A4=====================写入屏幕
			ST7789V_ShowWord(x,y,font,PenColor,GetBufferLength,CodeBuffer);
			//A5=====================水平显示地址增加
      x+=font;
			i++;		//双字节，减两次			
		}
		else if(('\r'==dst)||('\n'==dst))
		{
			if(('\n'==Buffer[i+1])||('\r'==Buffer[i+1]))
			{
				i++;	//去掉回车符长度
			}
			if(y>MaxV-font)
      {
        y=x=0;
      }
			else
			{
				x=0;
				y+=font;
			}
			goto LCD_ShowJump;
		}
		//B=====================单字节--ASCII字符集
		else
		{			
			//B1=====================显示超限换行
      if(x>MaxH-font/2)//半个宽度
      {
        x=0;
        y+=font;
      }
      //B2=====================显示到屏尾，从原点开始
      if(y>MaxV-font)
      {
        y=x=0;
      }
			if(0x00	!=	(char)dst)
			{
				//B3=====================读取点阵数据
				GetBufferLength	=	GT32L32_GetCode(font,(u16)dst,CodeBuffer);		//从字库中读数据并返回数据长度
				//GetBufferLength	=	GT32L32_GetBatteryCode(3,CodeBuffer);
				//=======================水平制表符按空格显示(部分字库会当0xFF输出)
				if(	('	'	==	(char)dst)		//水平制表符
					||(' '	==	(char)dst))		//空格
				{
					memset(CodeBuffer,0x00,GetBufferLength);
				}
				//B4=====================写入屏幕
				ST7789V_ShowChar(x,y,font,PenColor,GetBufferLength,CodeBuffer);
				//B5=====================水平显示地址增加
				x+=font/2;
			}
      						
		}
		if(UnicodeFlag)
		{
			i+=1;
		}
		LCD_ShowJump:
			__nop();
	}
}
/*******************************************************************************
* 函数名			:	function
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
*******************************************************************************/
void ST7789V_ShowStringBK(
							u16 x,			//x				:起点x坐标
							u16 y,			//y				:起点y坐标
							u8 font,		//font		:字体大小
							u16 BKColor,
							u16 PenColor,//字体颜色
							u8 num,			//num			:字节数
							u8 *Buffer	//Buffer	:显示的内容缓存
)		//高通字库测试程序
{
	unsigned short	MaxV=ST7789V_V,MaxH=ST7789V_H;	//边界值
	unsigned char i=0;
	unsigned char CodeBuffer[256]={0};
	switch(pST7789V->ST7789VRotate)
	{
		case ST7789V_Rotate_0D:
			MaxV=ST7789V_V;
			MaxH=ST7789V_H;
		break;
		case ST7789V_Rotate_90D:
			MaxV=ST7789V_H;
			MaxH=ST7789V_V;
		break;
		case ST7789V_Rotate_180D:
			MaxV=ST7789V_V;
			MaxH=ST7789V_H;
		break;
		case ST7789V_Rotate_270D:
			MaxV=ST7789V_H;
			MaxH=ST7789V_V;
		break;
		default:break;		
	}
	for(i=0;i<num;i++)
	{
		unsigned char GetBufferLength	=	0;
		unsigned char dst=Buffer[i];
		
		//A=====================双字节--汉字
		if(dst>0x80)
		{
			u16 word=dst<<8;
      
			dst=Buffer[i+1];
			word=word|dst;			
			//A1=====================显示超限换行
      if(x>MaxH-font)
      {
        x=0;
        y+=font;
      }
      //A2=====================显示到屏尾，从原点开始
      if(y>MaxV-font)
      {
        y=x=0;
      }
      //A3=====================读取点阵数据
			GetBufferLength	=	GT32L32_GetCode(font,word,CodeBuffer);		//从字库中读数据并返回数据长度
			//GetBufferLength	=	GT32L32_GetAntennaCode(3,CodeBuffer);
			//A4=====================写入屏幕
			ST7789V_ShowWordBK(x,y,font,BKColor,PenColor,GetBufferLength,CodeBuffer);
			//A5=====================水平显示地址增加
      x+=font;
			i++;		//双字节，减两次			
		}
		else if(('\r'==dst)||('\n'==dst))
		{
			if(('\n'==Buffer[i+1])||('\r'==Buffer[i+1]))
			{
				i++;	//去掉回车符长度
			}
			if(y>MaxV-font)
      {
        y=x=0;
      }
			else
			{
				x=0;
				y+=font;
			}
			goto LCD_ShowJump;
		}
		//B=====================单字节--ASCII字符集
		else
		{			
			//B1=====================显示超限换行
      if(x>MaxH-font/2)//半个宽度
      {
        x=0;
        y+=font;
      }
      //B2=====================显示到屏尾，从原点开始
      if(y>MaxV-font)
      {
        y=x=0;
      }
			if(0x00	!=	(char)dst)
			{
				//B3=====================读取点阵数据
				GetBufferLength	=	GT32L32_GetCode(font,(u16)dst,CodeBuffer);		//从字库中读数据并返回数据长度
				//GetBufferLength	=	GT32L32_GetBatteryCode(3,CodeBuffer);
				//=======================水平制表符按空格显示(部分字库会当0xFF输出)
				if(	('	'	==	(char)dst)		//水平制表符
					||(' '	==	(char)dst))		//空格
				{
					memset(CodeBuffer,0x00,GetBufferLength);
				}
				//B4=====================写入屏幕
				ST7789V_ShowCharBK(x,y,font,BKColor,PenColor,GetBufferLength,CodeBuffer);
				//B5=====================水平显示地址增加
				x+=font/2;
			}
      						
		}
		LCD_ShowJump:
			__nop();
	}
}
/*******************************************************************************
* 函数名			:	ST7789V_ShowStringBKAre
* 功能描述		:	带背景色限定区域显示 
* 输入			: void
* 返回值			: void
*******************************************************************************/
void ST7789V_ShowStringBKAre(
							u16 xs,			//x				:起点x坐标
							u16 ys,			//y				:起点y坐标
							u16 xe,			//x				:终点x坐标
							u16 ye,			//y				:终点y坐标
							u8 font,		//font		:字体大小
							u16 BKColor,
							u16 PenColor,//字体颜色
							u8 num,			//num			:字节数
							u8 *Buffer	//Buffer	:显示的内容缓存
)		//高通字库测试程序
{
	unsigned short	MaxX	=	xe-xs;	//水平宽度
	unsigned short	MaxY	=	ye-ys;	//垂直高度
	unsigned short	x	=	xs;	//水平起始点
	unsigned short	y	=	ys;	//垂直起始点
	unsigned char 	i=0;
	unsigned char 	CodeBuffer[256]={0};

	for(i=0;i<num;i++)
	{
		unsigned char GetBufferLength	=	0;
		unsigned char dst=Buffer[i];		
		//A=====================双字节--汉字
		if(dst>0x80)
		{
			u16 word=dst<<8;
      
			dst=Buffer[i+1];
			word=word|dst;			
			//A1=====================显示超限换行
      if(x+font>xe)
      {
        x=xs;
        y+=font;
      }
      //A2=====================显示到屏尾，从原点开始
      if(y>(ye-font))
      {
        return;
      }
      //A3=====================读取点阵数据
			GetBufferLength	=	GT32L32_GetCode(font,word,CodeBuffer);		//从字库中读数据并返回数据长度
			//GetBufferLength	=	GT32L32_GetAntennaCode(3,CodeBuffer);
			//A4=====================写入屏幕
			ST7789V_ShowWordBK(x,y,font,BKColor,PenColor,GetBufferLength,CodeBuffer);
			//A5=====================水平显示地址增加
      x+=font;
			i++;		//双字节，减两次			
		}
		else if(('\r'==dst)||('\n'==dst))
		{
			if(('\n'==Buffer[i+1])||('\r'==Buffer[i+1]))
			{
				i++;	//去掉回车符长度
			}
//			if(x>MaxX-font)
//      {
//				x=xs;
//        y+=font;
//      }
//			else
//			{
//				x=xs;
//				y+=font;
//			}
		}
		//B=====================单字节--ASCII字符集
		else
		{			
			//B1=====================显示超限换行
      if(x>xe-font/2)//半个宽度
      {
        x=xs;
        y+=font;
      }
      //B2=====================显示到屏尾，从原点开始
      if(y>ye-font)
      {
				return;
      }
			if(0x00	!=	(char)dst)
			{
				//B3=====================读取点阵数据
				GetBufferLength	=	GT32L32_GetCode(font,(u16)dst,CodeBuffer);		//从字库中读数据并返回数据长度
				//GetBufferLength	=	GT32L32_GetBatteryCode(3,CodeBuffer);
				//=======================水平制表符按空格显示(部分字库会当0xFF输出)
				if(	('	'	==	(char)dst)		//水平制表符
					||(' '	==	(char)dst))		//空格
				{
					memset(CodeBuffer,0x00,GetBufferLength);
				}
				//B4=====================写入屏幕
				ST7789V_ShowCharBK(x,y,font,BKColor,PenColor,GetBufferLength,CodeBuffer);
				//B5=====================水平显示地址增加
				x+=font/2;
			}
      						
		}
	}
}
/*******************************************************************************
*函数名			:	function
*功能描述		:	function
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
void ST7789V_Test(unsigned short Colr)
{
  unsigned short i=0,j=0;
  
  //ST7789V_PowerOn();
  
  ST7789V_Enable();
  
  //ST7789V_WriteCommand(0x2C); 
  
  ST7789V_SetWindowAddress(0,0,239,319);
    
  for(i=0;i<240;i++)
    for(j=0;j<320;j++)
	{
      ST7789V_WriteData(Colr);
			SysTick_DeleyuS(10);				//SysTick延时nmS
	}
  
  //ST7789V_WriteCommand(0x29);
  
//  for(i=0;i<60000;i++)
//    ST7789V_WriteData(0x00); 
//  
//  ST7789V_WriteCommand(0x29); 
  
  ST7789V_Disable();
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
//	ST7789VSet(RST);
//	LCD_DelaymS(5);				//SysTick延时nmS
//	ST7789VCrl(RST);;
//	LCD_DelaymS(5);				//SysTick延时nmS
//	ST7789VSet(RST);
//	LCD_DelaymS(10);				//SysTick延时nmS
}
/*******************************************************************************
* 函数名			:	
* 功能描述		:	 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
void ST7789V_Enable(void)
{
	ST7789V_DC_HIGH;  //WriteCommand:DC/RS-LOW
  ST7789V_RD_HIGH;  //ReadDisable
  ST7789V_WR_HIGH;  //WriteDisable
  
  ST7789V_CS_LOW;   //SelectLcm
}
/*******************************************************************************
* 函数名			:	
* 功能描述		:	 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
void ST7789V_Disable(void)
{
  ST7789V_CS_HIGH;  //Disable LCM
  
  ST7789V_DC_HIGH;  //WriteCommand:DC/RS-LOW
  ST7789V_RD_HIGH;  //ReadDisable
  ST7789V_WR_HIGH;  //WriteDisable
}
/*******************************************************************************
* 函数名			:	
* 功能描述		:	
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
void ST7789V_WriteCommand(unsigned short Command)
{
	ST7789V_DC_LOW;   //WriteCommand:DC/RS-LOW
  
  ST7789V_WR_LOW;   //WriteEnable
  ST7789V_DATABUS_PORT->ODR = Command;
  ST7789V_WR_HIGH;  //Read
  
  ST7789V_DC_HIGH;   //WriteCommand:DC/RS-LOW
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
  ST7789V_WR_LOW;   //WriteEnable
  ST7789V_DATABUS_PORT->ODR = Data;
  ST7789V_WR_HIGH;  //Read
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
  ST7789V_DC_HIGH;  //WriteData:DC/RS
  ST7789V_WR_HIGH;  //WriteDisable
  
  ST7789V_RD_LOW;   //ReadEnable
  Data  = ST7789V_DATABUS_PORT->IDR;
  ST7789V_RD_HIGH;  //ReadEnable
	return Data;
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
//	unsigned	long	i	=	0;
//	ST7789VCrl(CS);	//LCD_CS_LOW;
//	ST7789V_WriteIndex(0X3E);
//	GPIO_Configuration_IPU	(ST7789V_DATABUS_PORT,ST7789V_DATABUS_Pin);			//将GPIO相应管脚配置为上拉输入模式----V20170605
//	for(i=0;i<length;i++)
//	{
//		RAM[i]=ST7789V_ReadData();
//	}
//	ST7789VSet(CS);	//LCD_CS_HIGH;
//	GPIO_Configuration_OPP50	(ST7789V_DATABUS_PORT,ST7789V_DATABUS_Pin);		//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度2MHz----V20170605	
}
/**************************************************************************************************
* [Function] LCD_PowerOff:  关闭LCD 电源
* [No param]
**************************************************************************************************/
void ST7789V_PowerOff( void )
{
	ST7789V_BL_OFF;		//关背光

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

  ST7789V_Enable();	  //
	//----------------------------------Hardware Reset-----------------------------------------------//
	ST7789V_RST_LOW;  	
	ST7789V_DelaymS(1); 	   //最少10us
	ST7789V_RST_HIGH;
	//----------------------------------ExitSleep-----------------------------------------------//
	
	//----------------------------------Software Reset-----------------------------------------------//
  //ST7789V_WriteCommand(0x01);  	
  //ST7789V_DelaymS(520); 	   //Delay 120ms 
	//----------------------------------ExitSleep-----------------------------------------------//
  ST7789V_WriteCommand(0x11);           
  ST7789V_DelaymS(100); 	   //Delay 120ms 
  //----------------------------------Display Setting-----------------------------------------------// 
  ST7789V_WriteCommand(0x36); 
  ST7789V_WriteData(0x00);    //ST7789V_WriteData(0x00);   
	
	
  ST7789V_WriteCommand(0x3a); 
  ST7789V_WriteData(0x55); 
  //--------------------------------ST7789V Frame rate setting----------------------------------// 
  ST7789V_WriteCommand(0xb2); 
  ST7789V_WriteData(0x0c); 
  ST7789V_WriteData(0x0c); 
  ST7789V_WriteData(0x00); 
  ST7789V_WriteData(0x33); 
  ST7789V_WriteData(0x33); 
	
  ST7789V_WriteCommand(0xb7); 
  ST7789V_WriteData(0x35);		//VGH=13V, VGL=-10.4V 
  //----------------------------------------------------------------------------------------------------// 
  ST7789V_WriteCommand(0xbb); 
  ST7789V_WriteData(0x19); 
  ST7789V_WriteCommand(0xc0); 
  ST7789V_WriteData(0x2c); 
  ST7789V_WriteCommand(0xc2); 
  ST7789V_WriteData(0x01); 
  ST7789V_WriteCommand(0xc3); 
  ST7789V_WriteData(0x12); 
  ST7789V_WriteCommand(0xc4); 
  ST7789V_WriteData(0x20); 
  ST7789V_WriteCommand(0xc6); 
  ST7789V_WriteData(0x0f); 
  ST7789V_WriteCommand(0xd0); 
  ST7789V_WriteData(0xa4); 
  ST7789V_WriteData(0xa1); 
  //----------------------------------------------------------------------------------------------------// 
  ST7789V_WriteCommand(0xe0);	   //gamma setting 
  ST7789V_WriteData(0xd0); 
  ST7789V_WriteData(0x04); 
  ST7789V_WriteData(0x0d); 
  ST7789V_WriteData(0x11); 
  ST7789V_WriteData(0x13); 
  ST7789V_WriteData(0x2b); 
  ST7789V_WriteData(0x3f); 
  ST7789V_WriteData(0x54); 
  ST7789V_WriteData(0x4c); 
  ST7789V_WriteData(0x18); 
  ST7789V_WriteData(0x0d); 
  ST7789V_WriteData(0x0b); 
  ST7789V_WriteData(0x1f); 
  ST7789V_WriteData(0x23); 
  ST7789V_WriteCommand(0xe1); 
  ST7789V_WriteData(0xd0); 
  ST7789V_WriteData(0x04); 
  ST7789V_WriteData(0x0c); 
  ST7789V_WriteData(0x11); 
  ST7789V_WriteData(0x13); 
  ST7789V_WriteData(0x2c); 
  ST7789V_WriteData(0x3f); 
  ST7789V_WriteData(0x44); 
  ST7789V_WriteData(0x51); 
  ST7789V_WriteData(0x2f); 
  ST7789V_WriteData(0x1f); 
  ST7789V_WriteData(0x1f); 
  ST7789V_WriteData(0x20); 
  ST7789V_WriteData(0x23); 

  ST7789V_WriteCommand(0x29);	   //display on 
  ST7789V_WriteCommand(0x2c); 

//	ST7789V_EnterSleep();
  ST7789V_Disable();	//LCD_CS_HIGH;
	
	ST7789V_BL_ON;
 
}
/*******************************************************************************
*函数名			:	function
*功能描述		:	function
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
void ST7789V_EnterSleep(void)
{
  ST7789V_WriteCommand(0x28); // Standby out
  ST7789V_DelaymS(10);
  ST7789V_WriteCommand(0x10); // Display on
  ST7789V_BL_OFF;		//关背光
}


/*******************************************************************************
*函数名			:	function
*功能描述		:	function
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
void ST7789V_ExitSleep(void)
{
  ST7789V_WriteCommand(0x11); // Standby out
  ST7789V_DelaymS(180);
  ST7789V_WriteCommand(0x29); // Display on
  ST7789V_BL_ON;		//关背光
}

/*******************************************************************************
*函数名			:	function
*功能描述		:	function
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
void ST7789V_SetWindowAddress(unsigned short xs,unsigned short ys,unsigned short xe,unsigned short ye)
{
  //--------------------设置X
  ST7789V_WriteCommand(0x2A);
  ST7789V_WriteData(xs>>8);
  ST7789V_WriteData(xs&0xFF);
  ST7789V_WriteData(xe>>8);
  ST7789V_WriteData(xe&0xFF);
  
  //--------------------设置Y
  ST7789V_WriteCommand(0x2B);
  ST7789V_WriteData(ys>>8);
  ST7789V_WriteData(ys&0xFF);
  ST7789V_WriteData(ye>>8);
  ST7789V_WriteData(ye&0xFF);
  
	//----------------------------------Display Setting-----------------------------------------------// 
  ST7789V_WriteCommand(0x36); 
  ST7789V_WriteData(pST7789V->ST7789VRotate);    //ST7789V_WriteData(0x00);
	//----------------------------------write_memory_start
  ST7789V_WriteCommand(ST7789V_R2C_WMS);	  
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
  ST7789V_Enable();	//LCD_CS_LOW;
	ST7789V_SetWindowAddress(HSX,HSY,HSX,HSY);	//设置光标位置
	ST7789V_WriteData(Color);
  ST7789V_Disable();	//LCD_CS_HIGH;
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
  
	ST7789V_Enable();	//LCD_CS_LOW;
	for(t=0;t<distance+1;t++ )					//画线输出 
	{  
    ST7789V_SetWindowAddress(uRow,uCol,uRow,uCol);	//设置光标位置
    ST7789V_WriteData(Color);
    
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
  ST7789V_Disable();	//LCD_CS_HIGH;
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
							unsigned short xs, unsigned short ys, 	//x1,y1:起点坐标
							unsigned short xe, unsigned short ye,		//x2,y2:终点坐标
							u16 Color
)
{          
	unsigned int x;
	unsigned int y;	
  ST7789V_Enable();	//LCD_CS_LOW;
	ST7789V_SetWindowAddress(xs,ys,xe,ye);
	for(x=0;x<=xe-xs;x++)
	{
		for(y=0;y<=ye-ys;y++)
		{
			ST7789V_WriteData(Color);							//写数据
		}
	}
  ST7789V_Disable();	//LCD_CS_HIGH;
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
	unsigned short HSX=0,HEX=0,VSY=0,VEY=0,MaxH=0,MaxV=0;
//	unsigned long	length	=	0;
	switch(pST7789V->ST7789VRotate)
	{
		case ST7789V_Rotate_0D:
			HEX=ST7789V_H;
			VEY=ST7789V_V;
		break;
		case ST7789V_Rotate_90D:
			HEX=ST7789V_V;
			VEY=ST7789V_H;
		break;
		case ST7789V_Rotate_180D:
			HEX=ST7789V_H;
			VEY=ST7789V_V;
		break;
		case ST7789V_Rotate_270D:
			HEX=ST7789V_V;
			VEY=ST7789V_H;
		break;
		default:break;
		
	}
	pST7789V->ST7789VBColor	=	Color;
	ST7789V_Fill(0x00,0x00,HEX,VEY,Color);
}
/**************************************************************************************************
* [Function] ILI9326_SetBackground:  设置背景颜色
* [param01]u16 BackColor: 背景颜色值
**************************************************************************************************/
void ST7789V_SetBackground(  u16 BackColor )
{
	pST7789V->ST7789VBColor	=	BackColor;
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
										u16 PenColor,	//字体颜色
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
	
  ST7789V_Enable();	//LCD_CS_LOW;
  
	ST7789V_SetWindowAddress(x1,y1,x2,y2);//设置显示区域	

	for(i=0;i<num;i++)
	{ 
		temp=Buffer[i];		 					//调用1608字体--二维数组形式--字库使用时取消
		for(j=0;j<8;j++)
		{
			if((temp&0x80)==0X80)
			{
				LCD_PEN_COLOR=PenColor;
			}
			else
				LCD_PEN_COLOR=pST7789V->ST7789VBColor	;
			ST7789V_WriteData(LCD_PEN_COLOR);
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
          LCD_PEN_COLOR=PenColor;
        }
        else
          LCD_PEN_COLOR=pST7789V->ST7789VBColor	;
        ST7789V_WriteData(LCD_PEN_COLOR);
        temp=temp<<1;
      }
      i++;
    }		
	}
	ST7789V_Disable();	//LCD_CS_HIGH;
}
/*******************************************************************************
* 函数名			:	function
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
*******************************************************************************/
void ST7789V_ShowCharBK(
										u16 x,			//x				:起点x坐标
										u16 y,			//y				:起点y坐标
										u8 font,		//font		:字体大小
										u16 BKColor,	//背景颜色
										u16 PenColor,	//字体颜色
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
	
  ST7789V_Enable();	//LCD_CS_LOW;
  
	ST7789V_SetWindowAddress(x1,y1,x2,y2);//设置显示区域	

	for(i=0;i<num;i++)
	{ 
		temp=Buffer[i];		 					//调用1608字体--二维数组形式--字库使用时取消
		for(j=0;j<8;j++)
		{
			if((temp&0x80)==0X80)
			{
				LCD_PEN_COLOR=PenColor;
			}
			else
				LCD_PEN_COLOR=BKColor	;
			ST7789V_WriteData(LCD_PEN_COLOR);
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
          LCD_PEN_COLOR=PenColor;
        }
        else
          LCD_PEN_COLOR=BKColor	;
        ST7789V_WriteData(LCD_PEN_COLOR);
        temp=temp<<1;
      }
      i++;
    }		
	}
	ST7789V_Disable();	//LCD_CS_HIGH;
}
/*******************************************************************************
* 函数名			:	function
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
*******************************************************************************/
void ST7789V_ShowChar4836(
										u16 x,			//x				:起点x坐标
										u16 y,			//y				:起点y坐标
										u16 BKColor,	//背景颜色
										u16 PenColor,	//字体颜色
										const u8 *Buffer	//Buffer	:显示的内容缓存
										
)		//高通字库测试程序
{
	u8 temp;
	unsigned short i=0,j=0;
	unsigned short x1=0,x2=0,y1=0,y2=0;
	unsigned short LCD_PEN_COLOR	=	0;   	//画笔色
	x1	=	x;
	y1	=	y;
	x2	=	x+36-1;		//5字节,每行4个半字节
	y2	=	y+48-1;		//48行
	
  ST7789V_Enable();	//LCD_CS_LOW;
  
	ST7789V_SetWindowAddress(x1,y1,x2,y2);//设置显示区域	
	//5*48=240
	for(i=0;i<240;i++)
	{ 
		temp=Buffer[i];		 		//调用1608字体--二维数组形式--字库使用时取消
		if(i%10==4||i%10==9)	//每行第五个字节时只画半个字节
		{
			for(j=0;j<4;j++)
			{
				if((temp&0x80)==0X80)
				{
					LCD_PEN_COLOR=PenColor;
				}
				else
					LCD_PEN_COLOR=BKColor	;
				ST7789V_WriteData(LCD_PEN_COLOR);
				temp=temp<<1;
			}
		}
		else
		{
			for(j=0;j<8;j++)
			{
				if((temp&0x80)==0X80)
				{
					LCD_PEN_COLOR=PenColor;
				}
				else
					LCD_PEN_COLOR=BKColor	;
				ST7789V_WriteData(LCD_PEN_COLOR);
				temp=temp<<1;
			}
		}
	}
	ST7789V_Disable();	//LCD_CS_HIGH;
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
										u16 PenColor,	//字体颜色
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
  
  ST7789V_Enable();	//LCD_CS_LOW;
	ST7789V_SetWindowAddress(x1,y1,x2,y2);//设置显示区域

	for(i=0;i<num;i++)
	{ 
		temp=Buffer[i];		 				
		for(j=0;j<8;j++)
		{
			if((temp&0x80)==0X80)
			{
				LCD_PEN_COLOR=PenColor;
			}
			else
				LCD_PEN_COLOR=pST7789V->ST7789VBColor;
			ST7789V_WriteData(LCD_PEN_COLOR);
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
          LCD_PEN_COLOR=PenColor;
        }
        else
          LCD_PEN_COLOR=pST7789V->ST7789VBColor	;
        ST7789V_WriteData(LCD_PEN_COLOR);
        temp=temp<<1;
      }
      i++;
    }			
	}
	ST7789V_Disable();	//LCD_CS_HIGH;
}
/*******************************************************************************
* 函数名			:	function
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
*******************************************************************************/
void ST7789V_ShowWordBK(
										u16 x,			//x				:起点x坐标
										u16 y,			//y				:起点y坐标
										u8 font,		//font		:字体大小
										u16 BKColor,	//背景颜色
										u16 PenColor,	//字体颜色
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
  
  ST7789V_Enable();	//LCD_CS_LOW;
	ST7789V_SetWindowAddress(x1,y1,x2,y2);//设置显示区域

	for(i=0;i<num;i++)
	{ 
		temp=Buffer[i];		 				
		for(j=0;j<8;j++)
		{
			if((temp&0x80)==0X80)
			{
				LCD_PEN_COLOR=PenColor;
			}
			else
				LCD_PEN_COLOR=BKColor;
			ST7789V_WriteData(LCD_PEN_COLOR);
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
          LCD_PEN_COLOR=PenColor;
        }
        else
          LCD_PEN_COLOR=BKColor	;
        ST7789V_WriteData(LCD_PEN_COLOR);
        temp=temp<<1;
      }
      i++;
    }			
	}
	ST7789V_Disable();	//LCD_CS_HIGH;
}

/*******************************************************************************
* 函数名			:	LCD_DelayuS
* 功能描述		:	延时x微秒
* 输入			: void
* 返回值			: void
*******************************************************************************/
void ST7789V_DelayuS(u32 xuS)
{
	SysTick_DeleyuS(xuS);				//SysTick延时nmS;
}
/*******************************************************************************
* 函数名			:	LCD_DelaymS
* 功能描述		:	延时x毫秒
* 输入			: void
* 返回值			: void
*******************************************************************************/
void ST7789V_DelaymS(u32 xms)
{
	SysTick_DeleymS(xms);				//SysTick延时nmS;
}
/*******************************************************************************
* 函数名			:	LCD_DelayS
* 功能描述		:	延时x秒
* 输入			: void
* 返回值			: void
*******************************************************************************/
void ST7789V_DelayS(u32 xS)
{
	SysTick_DeleyS(xS);				//SysTick延时nmS;
}


