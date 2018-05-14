/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : PC001V21.c
* Author             : WOW
* Version            : V2.0.1
* Date               : 06/26/2017
* Description        : PC001V21层控制板.
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

#ifdef PL010V15				//智能药架称重LCD板

#include "PL010V15.H"

<<<<<<< HEAD
//#include "R61509V.h"
#include "LCD.H"
=======
#include "R61509V.h"
//#include "LCD.h"
>>>>>>> 24cd2ea4c8c2e2240d51603a2d65a86ccb26281c
#include "CS5530.H"

#include "GT32L32M0180.H"
#include "STM32F10x_BitBand.H"
#include "STM32_GPIO.H"
#include "STM32_SYS.H"
#include "STM32_SYSTICK.H"
#include "STM32_WDG.H"
#include "STM32_PWM.H"
#include "STM32_USART.H"


#include "SWITCHID.H"

#include "string.h"				//串和内存操作函数头文件
#include "stdlib.h"				//串和内存操作函数头文件
#include "stm32f10x_dma.h"



#define	Master	1		//0--从机，1-主机
u16	DelayTime=0x1000;
u16	LCDTime=0;
u16	DSPTime=0;

u8 hour=23,min=15,second=40;
u16 millisecond=0;

//GT32L32Def 	GT32L32;
//char	Char_Buffer[256];		//记录format内码


RS485_TypeDef  RS485;
#define	Rs485Size	256
u8 RxdBuffe[Rs485Size]={0};
u8 RevBuffe[Rs485Size]={0};
u8 TxdBuffe[Rs485Size]={0};
u8 RxFlg=0;
u16 RxNum=0;
u32	Rs485_Time	=	0;
u8	SlaveID	=	0;
u32 Rev_ADC	=	0;
u8	Rev_ID	=	0;



SWITCHID_CONF	SWITCHID;
u8 SwitchID=0;	//拔码开关地址


<<<<<<< HEAD
LCDDef	sLCD;


//R61509VDef R61509V;
=======
LcdDriverDef	Display;


R61509VDef R61509V;
>>>>>>> 24cd2ea4c8c2e2240d51603a2d65a86ccb26281c
u8	DspFlg	=	0;

u16 BKlight	=	0;



CS5530Def CS5530;
u32	CS5530_Time	=	0;
u32	CS5530_ADC_CMP			=	0;
u32 CS5530_ADC_Value		=0xFFFFFFFF;
u32 CS5530_ADC_Valuebac	=0xFFFFFFFF;

u32	WeigthARR[100]	=	{0};
u8	DspFlg1	=	0;
u32	We1	=	0;
u8	NuW	=	0;
u32	BsW	=	0;	//空重
u32 SsW	=	0;	//单重
u8	St	=	0;	//步骤
u8	SN	=	0;	//数量
u8	SNb	=	0;	//备存数量

u16 weighVar[20]={0};
u8	VarN	=	0;

u32 Rand	=	0;
//============LCD驱动调试变量
u16 HX	=	0;
u16	HY	=	0;
unsigned short	Color	=	0;
/*******************************************************************************
* 函数名		:	
* 功能描述	:	 
* 输入		:	
* 输出		:
* 返回 		:
*******************************************************************************/
void PL010V15_Configuration(void)
{
	SYS_Configuration();					//系统配置---打开系统时钟 STM32_SYS.H
	
	GPIO_DeInitAll();							//将所有的GPIO关闭----V20170605	
	
	SwitchID_Configuration();
	
	CS5530_Configuration();
	
	RS485_Configuration();
	
	LCD_Configuration();
	
	SysTick_Configuration(990);	//系统嘀嗒时钟配置72MHz,单位为uS
	
//	IWDG_Configuration(2000);			//独立看门狗配置---参数单位ms	

//	PWM_OUT(TIM2,PWM_OUTChannel1,1,900);	//PWM设定-20161127版本--运行指示灯
	
//	PWM_OUT(TIM2,PWM_OUTChannel4,500,200);		//PWM设定-20161127版本--背光
<<<<<<< HEAD
	LCD_Clean(LCD565_RED);			//清除屏幕函数--
	LCD_Printf(100,100,32,"时钟");					//后边的省略号就是可变参数
	LCD_Printf(100,130,32,"%02d:",hour);		//后边的省略号就是可变参数
	LCD_Printf(148,130,32,"%02d:",min);			//后边的省略号就是可变参数
	LCD_Printf(196,130,32,"%02d",second);		//后边的省略号就是可变参数
=======
	
//	PL010V13_PrintfString(0		,0,32	,"地址：%0.2d",SwitchID);				//待发药槽位，后边的省略号就是可变参数
//	PL010V13_PrintfString(0		,32,16	,"地址：%0.2d",SwitchID);				//待发药槽位，后边的省略号就是可变参数
>>>>>>> 24cd2ea4c8c2e2240d51603a2d65a86ccb26281c
//	R61509V_DrawCircle(200,120, 100, 1, R61509V_YELLOW );		//画一个圆形框
	
//	Display.Init	=	PL010V15_Configuration;
}
/*******************************************************************************
* 函数名		:	
* 功能描述	:	 
* 输入		:	
* 输出		:
* 返回 		:
*******************************************************************************/
void PL010V15_Server(void)
{	
	IWDG_Feed();				//独立看门狗喂狗
//	RS485_Server();		//通讯管理---负责信息的接收与发送
	LCD_Server();				//显示服务相关
//	CS5530_Server();	//称重服务，AD值处理，获取稳定值
	SwitchID_Server();	//拔码开关处理--动态更新拨码地址
}
/*******************************************************************************
* 函数名			:	function
* 功能描述		:	函数功能说明
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
void CS5530_Server(void)		//称重服务，AD值处理，获取稳定值
{
	CS5530_Process(&CS5530);
	if(CS5530_ADC_Value	!=	CS5530.Data.Origin)
	{
		CS5530_ADC_Value	=	CS5530.Data.Origin;
		LCD_Printf(0		,128,32	,"AD:%0.8d",CS5530_ADC_Value);				//待发药槽位，后边的省略号就是可变参数
	}
//	if(CS5530_Time++>=50)		//1秒钟
//	{		
//		CS5530_Time=0;
//		CS5530_ADC_Valuebac=CS5530_ReadData(&CS5530);	//读取AD值，如果返回0xFFFFFFFF,则未读取到24位AD值
//		if(CS5530_ADC_Valuebac!=0xFFFFFFFF)
//		{
//			
////			CS5530_ADC_Valuebac>>=5;		//19位精度
//			
//			if(CS5530_ADC_Value==CS5530_ADC_Valuebac)
//			{
//				DspFlg	=	0;
//			}
//			if(CS5530_ADC_Value>=CS5530_ADC_Valuebac)
//			{
//				CS5530_ADC_CMP	=	CS5530_ADC_Value-CS5530_ADC_Valuebac;
//			}
//			else
//			{
//				CS5530_ADC_CMP	=	CS5530_ADC_Valuebac-CS5530_ADC_Value;				
//			}
//			DspFlg	=	1;
//			CS5530_ADC_Value	=	CS5530_ADC_Valuebac;
//			
//			if(CS5530_ADC_CMP>100)
//			{
//				NuW	=	0;
//				return;
//			}
//			WeigthARR[NuW]	=	CS5530_ADC_Value;
//			if(NuW++>=20-1)
//			{
//				long	temp	=	0;
//				//We1
//				
//				u8 i	=	0;
//				
//				temp	=	CS5530_GetWeightUseMedinaFilter(&CS5530);
//				
//				if(temp>200)
//				{
//					NuW	=	0;
//					return;
//				}
//				NuW	=	0;
//				We1	=	WeigthARR[i];
//				for(i=1;i<20;i++)
//				{
//					We1	=	(We1+WeigthARR[i])/2;
//				}
//				if(St	==	1)
//				{
//					St=0;
//					BsW	=	We1;
//				}
//				else if(St	==	2)
//				{
//					SsW	=	(We1	-	BsW)/10;
//					St	=	3;
//					SN	=	10;
//					SNb	=	10;
//				}
//				else if(St	==	3)
//				{
//					SN	=	(We1-BsW+500)/SsW;	//计数数量
//					if(SN!=SNb)
//					{
//						SNb	=	SN;
//						PL010V13_PrintfString(0		,128,32	,"数量%0.3d",SNb);				//待发药槽位，后边的省略号就是可变参数
//					}
//				}
//				DspFlg1	=	1;
//			}
//				
//		}
//		else
//		{
////			We1	=0;
////			NuW	=0;
//		}
//	}
}
/*******************************************************************************
* 函数名			:	function
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
void LCD_Server(void)			//显示服务相关
{
<<<<<<< HEAD
#if 1
	millisecond++;
	if(millisecond>=999)
	{
//		SSD1963_DrawRectangle(100,100,110,110);
		millisecond=0;
		second++;
		if(second>59)
		{
			second=0;
			min++;			
			if(min>59)
			{
				min=0;
				hour++;
				if(hour>23)
				{
					hour=0;
				}
				LCD_Printf(100,130,32,"%02d:",hour);		//后边的省略号就是可变参数
				
			}
			LCD_Printf(148,130,32,"%02d:",min);		//后边的省略号就是可变参数
		}
		LCD_Printf(196,130,32,"%02d",second);		//后边的省略号就是可变参数
	}
#endif
#if 0		//画圆
	unsigned short i	=	0;
	for(i=1;i<100;i++)
	{
		LCD_DrawCircle(200,	120, i, 0, LCD565_WHITE );			//画一个圆形框	
	}
	for(i=100;i>0;i--)
	{
		LCD_DrawCircle(200,	120, i, 0, LCD565_BLACK );			//画一个圆形框	
	}
	LCD_DrawCircle(50,	60, 50, 0, LCD565_YELLOW );			//画一个圆形框	
	LCD_DrawCircle(340,	60,	50, 0, LCD565_YELLOW );			//画一个圆形框	
	LCD_DrawCircle(50,	180, 50, 0, LCD565_YELLOW );			//画一个圆形框	
	LCD_DrawCircle(340,	180, 50, 0, LCD565_YELLOW );			//画一个圆形框	
	LCD_DrawCircle(200,	120, 100, 0, LCD565_YELLOW );			//画一个圆形框	
	
	SysTick_DeleymS(500);					//SysTick延时nmS
	LCD_Clean(LCD565_BLACK);		//清除屏幕函数--
#endif
#if 0		//画圆
//	LCD_Fill(10,10,50,50,LCD565_YELLOW);	//在指定区域内填充指定颜色;区域大小:(xend-xsta)*(yend-ysta)
	
//	LCD_DrawRectangle(10,130,60,180,LCD565_YELLOW);			//画一个矩形框
	
//	R61509V_ShowChar(10,120,32,5,"sdsdf");
=======
#if 0		//画点测试
	u16 x=0,y=0;
	for(y=0;y<R61509V.Data.MaxH;y++)
	{
		for(x=0;x<R61509V.Data.MaxV;x++)
		{
			R61509V_DrawDot(x,y,R61509V_YELLOW);
//			SysTick_DeleyuS(10);				//SysTick延时nmS
		}
	}
	SysTick_DeleymS(100);				//SysTick延时nmS
	R61509V_Clean(R61509V_RED);			//清除屏幕函数--
#endif	
#if 0			//测试波形绘制
	u16 x=0,y=0;
	
	Rand	=	rand();
	x	=	HX;
	y	=	R61509V_H-Rand%200;
	R61509V_DrawDot(x,y,R61509V_YELLOW);
//	R61509V_DrawLine(x,HY,x,y,R61509V_YELLOW);
	HY	=	y;
	if(HX++>=R61509V_V)
	{
		HX	=	0;
		R61509V_Clean(R61509V_RED);			//清除屏幕函数--
//		SysTick_DeleymS(500);				//SysTick延时nmS
	}
//	SysTick_DeleymS(100);					//SysTick延时nmS
#endif
#if 0		//刷屏测试
	u32 LCDTime=500;
>>>>>>> 24cd2ea4c8c2e2240d51603a2d65a86ccb26281c
	
	LCD_DrawCircle(50,	50, 50, 1, LCD565_YELLOW );			//画一个圆形框	
	LCD_DrawCircle(350,	50,	50, 1, LCD565_YELLOW );			//画一个圆形框	
	LCD_DrawCircle(50,	190, 50, 1, LCD565_YELLOW );			//画一个圆形框	
	LCD_DrawCircle(350,	190, 50, 1, LCD565_YELLOW );			//画一个圆形框	
	LCD_DrawCircle(200,	120, 100, 1, LCD565_YELLOW );			//画一个圆形框	
	
	SysTick_DeleymS(500);					//SysTick延时nmS
	LCD_Clean(LCD565_RED);		//清除屏幕函数--
#endif
#if 0		//画点测试
	u16 x=0,y=0;
	for(y=0;y<sLCD.Data.MaxH;y++)
	{
		for(x=0;x<sLCD.Data.MaxV;x++)
		{
			LCD_DrawDot(x,y,LCD565_YELLOW);
//			SysTick_DeleyuS(10);				//SysTick延时nmS
		}
	}
	SysTick_DeleymS(100);				//SysTick延时nmS
	LCD_Clean(LCD565_RED);			//清除屏幕函数--
#endif	
#if 0			//测试波形绘制
	u16 x=0,y=0;
	
	Rand	=	rand();
	x	=	HX;
	y	=	R61509V_H-Rand%200;
	LCD_DrawDot(x,y,LCD565_YELLOW);
//	R61509V_DrawLine(x,HY,x,y,R61509V_YELLOW);
	HY	=	y;
	if(HX++>=R61509V_V)
	{
		HX	=	0;
		LCD_Clean(LCD565_RED);			//清除屏幕函数--
//		SysTick_DeleymS(500);				//SysTick延时nmS
	}
//	SysTick_DeleymS(100);					//SysTick延时nmS
#endif
#if 0		//刷屏测试
	u32 LCDTime=500;
////	u8 i	=	0;
//	for(Color	=	0;Color<=0xFFFF;)
//	{
//		LCD_Clean(Color);			//清除屏幕函数--
//		SysTick_DeleymS(LCDTime);				//SysTick延时nmS
//		Color+=100;		
//	}
<<<<<<< HEAD
=======
	
>>>>>>> 24cd2ea4c8c2e2240d51603a2d65a86ccb26281c
	
	
	LCD_Clean(LCD565_WHITE);		//清除屏幕函数--
	SysTick_DeleymS(LCDTime);				//SysTick延时nmS

	LCD_Clean(LCD565_BLACK);		//清除屏幕函数--
	SysTick_DeleymS(LCDTime);				//SysTick延时nmS
	
	LCD_Clean(LCD565_BLUE);		//清除屏幕函数--
	SysTick_DeleymS(LCDTime);				//SysTick延时nmS
	
	LCD_Clean(LCD565_BRED);			//清除屏幕函数--
	SysTick_DeleymS(LCDTime);				//SysTick延时nmS
	
	LCD_Clean(LCD565_GRED);			//清除屏幕函数--
	SysTick_DeleymS(LCDTime);				//SysTick延时nmS
<<<<<<< HEAD
	
	LCD_Clean(LCD565_GBLUE);			//清除屏幕函数--
	SysTick_DeleymS(LCDTime);				//SysTick延时nmS
	
	LCD_Clean(LCD565_RED);			//清除屏幕函数--
	SysTick_DeleymS(LCDTime);				//SysTick延时nmS
	
	LCD_Clean(LCD565_MAGENTA);			//清除屏幕函数--
	SysTick_DeleymS(LCDTime);				//SysTick延时nmS
	
	LCD_Clean(LCD565_GREEN);			//清除屏幕函数--
	SysTick_DeleymS(LCDTime);				//SysTick延时nmS
	
	LCD_Clean(LCD565_CYAN);			//清除屏幕函数--
	SysTick_DeleymS(LCDTime);				//SysTick延时nmS
	
	LCD_Clean(LCD565_YELLOW);			//清除屏幕函数--
	SysTick_DeleymS(LCDTime);				//SysTick延时nmS
=======
//	
//	LCD_Clean(R61509V_GBLUE);			//清除屏幕函数--
//	SysTick_DeleymS(LCDTime);				//SysTick延时nmS
//	
//	LCD_Clean(R61509V_RED);			//清除屏幕函数--
//	SysTick_DeleymS(LCDTime);				//SysTick延时nmS
//	
//	LCD_Clean(R61509V_MAGENTA);			//清除屏幕函数--
//	SysTick_DeleymS(LCDTime);				//SysTick延时nmS
//	
//	LCD_Clean(R61509V_GREEN);			//清除屏幕函数--
//	SysTick_DeleymS(LCDTime);				//SysTick延时nmS
//	
//	LCD_Clean(R61509V_CYAN);			//清除屏幕函数--
//	SysTick_DeleymS(LCDTime);				//SysTick延时nmS
//	
//	LCD_Clean(R61509V_YELLOW);			//清除屏幕函数--
//	SysTick_DeleymS(LCDTime);				//SysTick延时nmS
>>>>>>> 24cd2ea4c8c2e2240d51603a2d65a86ccb26281c
#endif
#if 1	//画直线
	HX	=	0;HY	=	10;
//	for(HY	=	10;HY<=10;HY++)
//	{
//		for(HX	=	10;HX<=400;)
//		{
//			LCD_DrawDot(HX,HY,R61509V_YELLOW);
//			HX	+=	1;
//			SysTick_DeleymS(10);				//SysTick延时nmS
//		}
//	}
//	R61509V_SetWindowAddress(0,10,100,10);//设置窗地址
//	R61509V_SetWindowAddress(0,10,300,10);//设置窗地址
//	for(HX=0;HX<=400;HX++)
//	{
//		R61509V_WriteData16(R61509V_YELLOW); 	//笔画颜色	
//	}
	R61509V_DrawLine(0,100,500,100,R61509V_YELLOW);
	R61509V_DrawLine(100,0,100,230,R61509V_YELLOW);
<<<<<<< HEAD
	R61509V_DrawLine(350,0,350,230,R61509V_YELLOW);
=======
>>>>>>> 24cd2ea4c8c2e2240d51603a2d65a86ccb26281c
	SysTick_DeleymS(1000);				//SysTick延时nmS
	R61509V_Clean(R61509V_RED);			//清除屏幕函数--蓝白
//	//清除直线
//	HX	=	10;HY	=	10;
//	for(HX	=	10;HX<230;HX++)
//	{
//		for(HY	=	10;HY<=380;)
//		{
//			LCD_DrawDot(HX,HY,R61509V_RED);
//			HY	+=	5;
//			SysTick_DeleymS(100);				//SysTick延时nmS
//		}
//	}

//	LCD_Clean(R61509V_RED);			//清除屏幕函数--蓝白
#endif
#if 0	//LCD驱动调试.----画线
	LCD_Clean(LCD565_RED);			//清除屏幕函数--蓝白
	HX	=	10;HY	=	10;
	for(HY	=	10;HY<=230;)
	{
		LCD_DrawLine(10,HY,390,HY,LCD565_YELLOW);
		HY	+=	5;
	}
	SysTick_DeleymS(1000);				//SysTick延时nmS
	HX	=	10;HY	=	10;
	for(HX	=	10;HX<=390;)
	{
		LCD_DrawLine(HX,10,HX,230,LCD565_YELLOW);
		HX	+=	5;
//		SysTick_DeleymS(100);				//SysTick延时nmS
	}
	SysTick_DeleymS(1000);				//SysTick延时nmS
	//清除
	HX	=	10;HY	=	10;
	for(HY	=	10;HY<=230;)
	{
		LCD_DrawLine(10,HY,390,HY,LCD565_RED);
		HY	+=	5;
	}
	SysTick_DeleymS(1000);				//SysTick延时nmS
	HX	=	10;HY	=	10;
	for(HX	=	10;HX<=390;)
	{
		LCD_DrawLine(HX,10,HX,230,LCD565_RED);
		HX	+=	5;
	}
<<<<<<< HEAD
	SysTick_DeleymS(1000);				//SysTick延时nmS
	LCD_Clean(LCD565_RED);			//清除屏幕函数--蓝白
#endif
#if 0
	LCD_Clean(LCD565_RED);			//清除屏幕函数--蓝白
	
//	LCD_Printf(0		,0,32	,"萘");									//待发药槽位，后边的省略号就是可变参数
	
//	LCD_Printf(0		,0,16	,"显示测试……");									//待发药槽位，后边的省略号就是可变参数
//	LCD_Printf(0		,16,16	,"显示测试……");									//待发药槽位，后边的省略号就是可变参数
//	LCD_Printf(0		,32,32	,"显示测试……");									//待发药槽位，后边的省略号就是可变参数
//	LCD_Printf(0		,64,32	,"显示测试……");									//待发药槽位，后边的省略号就是可变参数
	LCD_Printf(0		,96,32	,"显示测试……");									//待发药槽位，后边的省略号就是可变参数
	LCD_Printf(0		,128,32	,"测试显示……");									//待发药槽位，后边的省略号就是可变参数
	LCD_Printf(0		,160,32	,"怲试显示……");									//待发药槽位，后边的省略号就是可变参数
=======
//	SysTick_DeleymS(500);				//SysTick延时nmS
//	LCD_Clean(R61509V_RED);			//清除屏幕函数--蓝白
#endif
#if 0

	PL010V13_PrintfString(0		,0,16	,"显示测试……");									//待发药槽位，后边的省略号就是可变参数
	PL010V13_PrintfString(0		,16,16	,"显示测试……");									//待发药槽位，后边的省略号就是可变参数
	PL010V13_PrintfString(0		,32,32	,"显示测试……");									//待发药槽位，后边的省略号就是可变参数
	PL010V13_PrintfString(0		,64,32	,"显示测试……");									//待发药槽位，后边的省略号就是可变参数
	PL010V13_PrintfString(0		,96,32	,"显示测试……");									//待发药槽位，后边的省略号就是可变参数
>>>>>>> 24cd2ea4c8c2e2240d51603a2d65a86ccb26281c

	SysTick_DeleymS(1000);				//SysTick延时nmS
	LCD_Clean(LCD565_RED);			//清除屏幕函数--蓝白	
#endif
	if(DspFlg)
	{
		DspFlg	=	0;
//		LCD_Printf(0		,32,32	,"%0.8d",CS5530_ADC_CMP);				//待发药槽位，后边的省略号就是可变参数
//		LCD_Printf(0		,64	,32	,"%0.8d",CS5530_ADC_Value);				//待发药槽位，后边的省略号就是可变参数
	}
	if(DspFlg1)
	{
		DspFlg1	=	0;
//		LCD_Printf(0		,96,32	,"%0.8d",We1);				//待发药槽位，后边的省略号就是可变参数
	}
}
/*******************************************************************************
* 函数名			:	RS485_Server
* 功能描述		:	数据收发--获取AD值命令:FA F5 ID 01 ,上报数据格式：FB F6 ID B1 B2 B3 高位在前
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
void RS485_Server(void)			//通讯管理---负责信息的接收与发送
{
#if Master			//主机
	RxNum=RS485_ReadBufferIDLE(&RS485,(u32*)RevBuffe,(u32*)RxdBuffe);	//串口空闲模式读串口接收缓冲区，如果有数据，将数据拷贝到RevBuffer,并返回接收到的数据个数，然后重新将接收缓冲区地址指向RxdBuffer
	if(		RxNum								\
			&&	(RevBuffe[0]	==	0xFB)			\
			&&	(RevBuffe[1]	==	0xF6)			\
		)
	{		
		Rs485_Time	=	0;
		Rev_ADC	=	0;
		Rev_ID	=	RevBuffe[2];
		
		Rev_ADC	+=	RevBuffe[3];
		Rev_ADC	<<=	8;
		Rev_ADC	+=	RevBuffe[4];
		Rev_ADC<<=8;
		Rev_ADC	+=	RevBuffe[5];
		
		LCD_Printf(0		,128	,16	,"接收到通道%0.2d称重值：%0.8d",Rev_ID,Rev_ADC);				//待发药槽位，后边的省略号就是可变参数
		
	}
	if(Rs485_Time	++>5)
	{
		Rs485_Time	=	0;
		TxdBuffe[0]	=	0xFA;
		TxdBuffe[1]	=	0xF5;
		TxdBuffe[2]	=	SlaveID;
		TxdBuffe[3]	=	0x01;
		RS485_DMASend	(&RS485,(u32*)TxdBuffe,4);	//RS485-DMA发送程序
		if(SlaveID++>=250)
			SlaveID	=	1;
	}
#else
	RxNum=RS485_ReadBufferIDLE(&RS485,(u32*)RevBuffe,(u32*)RxdBuffe);	//串口空闲模式读串口接收缓冲区，如果有数据，将数据拷贝到RevBuffer,并返回接收到的数据个数，然后重新将接收缓冲区地址指向RxdBuffer
	if(		RxNum												\
			&&(RevBuffe[0]	==	0xFA)			\
			&&(RevBuffe[1]	==	0xF5)			\
			&&(RevBuffe[2]	==	SwitchID)	\
			&&(RevBuffe[3]	==	0x01)			\
		)
	{
		RxFlg	=	1;
		Rs485_Time	=	0;
	}
	if(RxFlg	==	1)
	{
		if(Rs485_Time++>=2)	//延时10mS
		{
			//CS5530_ADC_Value
			RxFlg	=	0;
			Rs485_Time	=	0;
			
			TxdBuffe[0]	=	0xFB;
			TxdBuffe[1]	=	0xF6;
			TxdBuffe[2]	=	SwitchID;
			TxdBuffe[3]	=	(CS5530_ADC_Value>>16)&0xFF;
			TxdBuffe[4]	=	(CS5530_ADC_Value>>8)&0xFF;
			TxdBuffe[5]	=	(CS5530_ADC_Value>>0)&0xFF;
			RS485_DMASend	(&RS485,(u32*)TxdBuffe,6);	//RS485-DMA发送程序
		}
	}
#endif
}
/*******************************************************************************
* 函数名			:	function
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
void SwitchID_Server(void)	//拔码开关处理--动态更新拨码地址
{
	u8 ID_Temp	=	0;
	ID_Temp	=	SWITCHID_Read(&SWITCHID);		//
	if(SwitchID	!=	ID_Temp)
	{
		SwitchID	=	ID_Temp;
		LCD_Printf(0		,0,32	,"地址：%0.2d",SwitchID);				//待发药槽位，后边的省略号就是可变参数
	}
}
/*******************************************************************************
* 函数名			:	function
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
void SwitchID_Configuration(void)
{
	SWITCHID.NumOfSW	=	6;
	
	SWITCHID.SW1_PORT	=	GPIOC;
	SWITCHID.SW1_Pin	=	GPIO_Pin_6;
	
	SWITCHID.SW2_PORT	=	GPIOC;
	SWITCHID.SW2_Pin	=	GPIO_Pin_7;
	
	SWITCHID.SW3_PORT	=	GPIOC;
	SWITCHID.SW3_Pin	=	GPIO_Pin_8;
	
	SWITCHID.SW4_PORT	=	GPIOC;
	SWITCHID.SW4_Pin	=	GPIO_Pin_9;
	
	SWITCHID.SW5_PORT	=	GPIOC;
	SWITCHID.SW5_Pin	=	GPIO_Pin_12;
	
	SWITCHID.SW6_PORT	=	GPIOC;
	SWITCHID.SW6_Pin	=	GPIO_Pin_13;
	
	SwitchIdInitialize(&SWITCHID);							//
	
	SwitchID	=	SWITCHID_Read(&SWITCHID);		//
}


/*******************************************************************************
* 函数名			:	function
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
void LCD_Configuration(void)
{
<<<<<<< HEAD
	LCDPortDef		*Port;	
	
	Port	=	&(sLCD.Port);
=======
	R61509VPortDef		*Port;	
	
	Port	=	&(R61509V.Port);
>>>>>>> 24cd2ea4c8c2e2240d51603a2d65a86ccb26281c

	Port->sCS_PORT		=	GPIOA;
	Port->sCS_Pin			=	GPIO_Pin_12;
	
	Port->sDC_PORT		=	GPIOA;
	Port->sDC_Pin			=	GPIO_Pin_8;
	
	Port->sWR_PORT		=	GPIOA;
	Port->sWR_Pin			=	GPIO_Pin_15;
	
	Port->sRD_PORT		=	GPIOC;
	Port->sRD_Pin			=	GPIO_Pin_5;
	
	Port->sREST_PORT	=	GPIOD;
	Port->sREST_Pin		=	GPIO_Pin_2;
	
	Port->sBL_PORT		=	GPIOA;
	Port->sBL_Pin			=	GPIO_Pin_3;
	
	Port->sTE_PORT		=	GPIOC;
	Port->sTE_Pin			=	GPIO_Pin_4;
	
	Port->sDATABUS_PORT	=	GPIOB;
	Port->sDATABUS_Pin	=	GPIO_Pin_All;
	
	sLCD.Flag.Rotate	=	Draw_Rotate_90D;	//使用旋转角度
	
	
	sLCD.GT32L32.Port.sSPIx=SPI1;
	sLCD.GT32L32.Port.sGT32L32_CS_PORT=GPIOA;
	sLCD.GT32L32.Port.sGT32L32_CS_PIN=GPIO_Pin_4;
	sLCD.GT32L32.Port.SPI_BaudRatePrescaler_x=SPI_BaudRatePrescaler_2;
	
	
	
	LCD_Initialize(&sLCD);
	
}
/*******************************************************************************
* 函数名			:	function
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
void CS5530_Configuration(void)
{
	CS5530.Port.CS_PORT=GPIOC;
	CS5530.Port.CS_Pin=GPIO_Pin_3;
	
	CS5530.Port.SDI_PORT=GPIOC;
	CS5530.Port.SDI_Pin=GPIO_Pin_2;
	
	CS5530.Port.SDO_PORT=GPIOC;
	CS5530.Port.SDO_Pin=GPIO_Pin_1;
	
	CS5530.Port.SCLK_PORT=GPIOC;
	CS5530.Port.SCLK_Pin=GPIO_Pin_0;
	
	CS5530_Initialize(&CS5530);
}
/*******************************************************************************
* 函数名			:	function
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
void RS485_Configuration(void)
{
	RS485.USARTx=USART1;
	RS485.RS485_CTL_PORT=GPIOA;
	RS485.RS485_CTL_Pin=GPIO_Pin_11;
	
	RS485_DMA_ConfigurationNR	(&RS485,115200,(u32*)RxdBuffe,Rs485Size);	//USART_DMA配置--查询方式，不开中断,配置完默认为接收状态
}
<<<<<<< HEAD
=======
/*******************************************************************************
* 函数名		:	
* 功能描述	:	 
* 输入		:	
* 输出		:
* 返回 		:
*******************************************************************************/
void LCD_PowerUp(void)
{	
	#if 0
	PL010Delay(0xFFFF);
	PL010V13_PrintfString(1		,0	,16	,"待发药槽位：%2d",RevBuffe[0]);				//后边的省略号就是可变参数
	PL010V13_PrintfString(1		,0	,16	,"待发药槽位：%2d",RevBuffe[0]);				//后边的省略号就是可变参数
	PL010Delay(0xFFFF);
	PL010V13_PrintfString(1		,20	,16	,"待发药数量：%2d",RevBuffe[1]);				//后边的省略号就是可变参数
	PL010Delay(0xFFFF);
	PL010V13_PrintfString(1		,40	,16	,"已发药数量：%2d",RevBuffe[1]);				//后边的省略号就是可变参数
	PL010Delay(0xFFFF);
	
//	PL010V13_PrintfString(0		,60	,16	,"总共请求数量：%4d",SumFQ);				//总共发药请求数量
//	PL010V13_PrintfString(0		,80	,16	,"总共发药数量：%4d",SumFed);				//总共已发药数量
	PL010V13_PrintfString(1		,100	,16	,"错误状态：");				//错误状态
	PL010Delay(0xFFFF);
	
	PL010V13_PrintfString(1		,160	,16	,"提示：长按3秒读取发药头");				//错误状态
	PL010Delay(0xFFFF);
	

	//平行线
	R61509V_DrawLine(221,0,221,400,R61509V_WHITE);						//AB 两个坐标画一条直线
	R61509V_DrawLine(201,0,201,400,R61509V_WHITE);						//AB 两个坐标画一条直线
	R61509V_DrawLine(181,0,181,400,R61509V_WHITE);						//AB 两个坐标画一条直线
	R61509V_DrawLine(161,0,161,400,R61509V_WHITE);						//AB 两个坐标画一条直线
	//垂直线--中
	R61509V_DrawLine(161,200,221,200,R61509V_WHITE);					//AB 两个坐标画一条直线
	//垂直线--右
	R61509V_DrawLine(161,250-1,221,250-1,R61509V_WHITE);			//AB 两个坐标画一条直线
	R61509V_DrawLine(161,300-1,221,300-1,R61509V_WHITE);			//AB 两个坐标画一条直线
	R61509V_DrawLine(161,350-1,221,350-1,R61509V_WHITE);			//AB 两个坐标画一条直线
	R61509V_DrawLine(161,400-1,221,400-1,R61509V_WHITE);			//AB 两个坐标画一条直线
	
	//垂直线--左
	R61509V_DrawLine(161,1,221,1,					R61509V_WHITE);							//AB 两个坐标画一条直线
	R61509V_DrawLine(161,51,221,51,				R61509V_WHITE);						//AB 两个坐标画一条直线
	R61509V_DrawLine(161,101,221,101,			R61509V_WHITE);					//AB 两个坐标画一条直线
	R61509V_DrawLine(161,151,221,151,			R61509V_WHITE);					//AB 两个坐标画一条直线

	//填充
	R61509V_Fill(2,180,50,200-2,R61509V_RED);				//在指定区域内填充指定颜色;区域大小:(xend-xsta)*(yend-ysta)
	R61509V_Clean(R61509V_BLUE);			//清除屏幕函数------
	
	
	
//	R61509V_DrawLine(10,200,10,280,R61509V_WHITE);						//AB 两个坐标画一条直线
	
	#else
//	LCD_Clean(R61509V_WHITE);			//清除屏幕函数------
//	PL010Delay(0x8FFFFF);
	R61509V_Clean(R61509V_BLUE);			//清除屏幕函数------
//	PL010Delay(0x8FFFFF);
//	LCD_Clean(R61509V_GRAY);			//清除屏幕函数------
	PL010Delay(0x0FFFFF);
	R61509V_Clean(R61509V_YELLOW);			//清除屏幕函数------
//	PL010Delay(0x8FFFFF);
//	LCD_Clean(R61509V_WHITE);			//清除屏幕函数------
//	PL010Delay(0x8FFFFF);
//	LCD_Clean(R61509V_BLACK);			//清除屏幕函数------

//	PL010Delay(0xFFFF);
//	PL010V13_PrintfString(0	,0,16	,"TEST");				//错误状态
	#endif
//	LCD_Clean(R61509V_BLACK);			//清除屏幕函数------
	
}
/*******************************************************************************
* 函数名			:	function
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
void LCD_Display(void)
{
//	PL010V13_PrintfString(0		,120	,16	,"显示测试！！！！！！！！！");				//错误状态
	
#if 0		
	DSPTime++;
	if(DSPTime>500)
	{
		DSPTime=0;
		LCD_WXS();		//位显示
		LCD_DDSP();		//显示总共请求数量和已发数量
	}	
	LCD_WS();		//位闪烁
	
	if(LCDTime>=1000)
	{			
		LCDTime=0;		
	}	
	
	RxNum=RS485_ReadBufferIDLE(&RS485,(u32*)RevBuffe,(u32*)RxdBuffe);	//串口空闲模式读串口接收缓冲区，如果有数据，将数据拷贝到RevBuffer,并返回接收到的数据个数，然后重新将接收缓冲区地址指向RxdBuffer
	if(RxNum==4&&RevBuffe[0]==0x00&&RevBuffe[1]==0xFF)		//RS485接收到数据
	{
		NumFW=RevBuffe[2];
		PL010V13_PrintfString(96		,0	,16	,"%2d",RevBuffe[2]);				//待发药槽位，后边的省略号就是可变参数
		PL010V13_PrintfString(96		,20	,16	,"%2d",RevBuffe[3]);				//待发药数量，后边的省略号就是可变参数
//		PL010V13_PrintfString(192		,68	,16	,"%2d",RevBuffe[1]);				//已发药数量，后边的省略号就是可变参数
	}
	else if(RxNum==3&&RevBuffe[0]==0x02)		//RS485接收到数据
	{
		SumFQ[RevBuffe[1]-1]+=RevBuffe[2];
		NumFW=RevBuffe[1];
		PL010V13_PrintfString(96		,0	,16	,"%2d",RevBuffe[1]);				//待发药槽位，后边的省略号就是可变参数
		PL010V13_PrintfString(96		,20	,16	,"%2d",RevBuffe[2]);				//待发药数量，后边的省略号就是可变参数
		PL010V13_PrintfString(96		,40	,16	,"%2d",0);									//已发药数量，后边的省略号就是可变参数
		
//		PL010V13_PrintfString(0		,60	,16	,"总共请求数量：%4d",SumFQ);				//总共发药请求数量
		PL010V13_PrintfString(0		,120	,16	,"正在发药！！！！！！！！！！");				//错误状态
	}
	else if(RxNum==4&&RevBuffe[0]==0x82)		//RS485接收到数据
	{
		SumFed[RevBuffe[1]-1]+=RevBuffe[2];
		PL010V13_PrintfString(96		,0	,16	,"%2d",RevBuffe[1]);				//待发药槽位，后边的省略号就是可变参数
		PL010V13_PrintfString(96		,20	,16	,"%2d",0);									//待发药数量，后边的省略号就是可变参数
		PL010V13_PrintfString(96		,40	,16	,"%2d",RevBuffe[2]);				//已发药数量，后边的省略号就是可变参数		
		
//		PL010V13_PrintfString(112		,80	,16	,"%4d",SumFed);					//总共已发药数量
		
	}
	else if(RxNum==6&&RevBuffe[0]==0x81)	//槽位信息0x01--获取,0x81--上报
	{
		Onlinede=RevBuffe[4];
	}
	else if(RxNum==1&&RevBuffe[0]==0x01)	//槽位信息0x01--获取,0x81--上报
	{
		PL010V13_PrintfString(0		,120	,16		,"获取槽位信息！！！");				//错误状态
		NumFW=0;
		Onlinede=0;
		memset(SumFed,0x00,8);
		memset(SumFQ,0x00,8);

		PL010V13_PrintfString(96		,0	,16	,"%2d",0);				//待发药槽位，后边的省略号就是可变参数
		PL010V13_PrintfString(96		,20	,16	,"%2d",0);				//待发药数量，后边的省略号就是可变参数
	}
	
	for(DelayTime=0;DelayTime<1000;DelayTime++)
	{
		
	}
	if(RxNum&&(RevBuffe[0]==0x82))		//错误状态显示
	{
		switch(RevBuffe[3])
		{
			case 0x00:	PL010V13_PrintfString(0		,120	,16	,"！！！！！！！！！！！！！！");				//错误状态
				break;
			case 0x80:	PL010V13_PrintfString(0		,120	,16	,"药品被卡住！！！！！！！！！");				//错误状态
				break;
			case 0x81:	PL010V13_PrintfString(0		,120	,16	,"缺药！！！！！！！！！！！！");				//错误状态
				break;
			case 0x82:	PL010V13_PrintfString(0		,120	,16	,"等待命令结果超时！！！！！！");				//错误状态
				break;
			case 0xC0:	PL010V13_PrintfString(0		,120	,16	,"单元柜控制器通信异常！！！！");				//错误状态
				break;
			case 0xC1:	PL010V13_PrintfString(0		,120	,16	,"发药层控制器通信异常！！！！");				//错误状态
				break;
		}
>>>>>>> 24cd2ea4c8c2e2240d51603a2d65a86ccb26281c




/*******************************************************************************
* 函数名		:	
* 功能描述	:	 
* 输入		:	
* 输出		:
* 返回 		:
*******************************************************************************/
void PL010V13_DISPLAY(void)
{
//	R61509V_DrawPixelEx( 100, 100,LCD_FORE_COLOR);
//	R61509V_DrawHLine( 10, 100, 200, LCD_FORE_COLOR);
}
void PL010Delay(u32 time)
{	
	while(time--);
}


#endif
