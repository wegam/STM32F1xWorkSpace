#ifdef FatFsTest

#include "FatFsTest.H"

//#include "string.h"				//串和内存操作函数头文件
//#include "stm32f10x_dma.h"

#include "SSD1963.H"


#include "STM32F10x_BitBand.H"
#include "STM32_GPIO.H"
#include "STM32_SYS.H"
#include "STM32_SYSTICK.H"
#include "STM32_ADC.H"
#include "STM32_WDG.H"
//#include "STM32_PWM.H"
//#include "STM32_PWM.H"
//#include "STM32_GPIO.H"
#include "STM32_USART.H"
//#include "STM32_DMA.H"


#include "TM1618.H"

//#include "STM32_SDCard.H"
//#include "GT32L32M0180.H"



//#define SDCardTest
//#define GT32L32M0180Test	
//


LCDDef	sLCD;

//GT32L32_Info_TypeDef 	GT32L32_Init;
//GT32L32Def			GT32L32;
//SSD1963_Pindef 	SSD1963_Pinfo;
TM1618_Pindef		TM1618_1,TM1618_2;

u16 millisecond=0;
u8 hour=23,min=00,second=30;

//u8 GTBuffer[512]={0};		//点阵数据存储空间

u32	dspdata=0;
u16 us=0;
u16	mm=0;
u8	ss=0;
u8	hh=0;

u16 time=0;
u32 ADCDATA = 0;
//void GT32L32_PinSet(void);
FATFS fs[2]; /* 逻辑驱动器的工作区(文件系统对象) */	
FIL fsrc, fdst; /* 文件对象 */
BYTE buffer[4096]; /* 文件拷贝缓冲区 */
FRESULT res; /* FatFs 函数公共结果代码 */
UINT br, bw; /* 文件读/写字节计数 */
//=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>
//->函数名		:	
//->功能描述	:	 
//->输入		:	
//->输出		:
//->返回 		:
//<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=
void FatFsTest_Configuration(void)
{	
	SYS_Configuration();					//系统配置---打开系统时钟 STM32_SYS.H	
	GPIO_DeInitAll();							//将所有的GPIO关闭----V20170605	
	
  LCD_Configuration();
//  TM1618_PinSet();
  USART_DMA_ConfigurationNR	(USART1,115200,128);	//USART_DMA配置--查询方式，不开中断
  
  LCD_Printf (0,0,16,0,"为逻辑驱动器注册工作区......");					//自定义printf串口DMA发送程序,后边的省略号就是可变参数
  /* 为逻辑驱动器注册工作区 */
  res = f_mount(&fs[0],"",1);               //在FatFs模块上注册/注销一个工作区(文件系统对象)
  LCD_Printf (0,16,16,0,"%2d",res);					//自定义printf串口DMA发送程序,后边的省略号就是可变参数
  res = f_mount(&fs[1],"",1);               //在FatFs模块上注册/注销一个工作区(文件系统对象)
  LCD_Printf (0,32,16,0,"输出结果%0.2X",res);					//自定义printf串口DMA发送程序,后边的省略号就是可变参数
  res = f_open(&fsrc, "1:srcfile.dat", FA_OPEN_EXISTING | FA_READ);
  LCD_Printf (0,48,16,0,"%0.5X",res);					//自定义printf串口DMA发送程序,后边的省略号就是可变参数
  
  
  
  
  
  
  
  
  
  
	


  USART_DMA_ConfigurationNR	(USART1,115200,128);	//USART_DMA配置--查询方式，不开中断
//  
  ADC_TempSensorConfiguration(&ADCDATA);								//STM32内部温度传感器配置
//  LCD_ShowBattery(780,2,2,0);   //显示12x12电池
//  LCD_ShowAntenna(760,2,3,0);   //显示12x12天线
  
	SysTick_Configuration(1000);											//系统嘀嗒时钟配置72MHz,单位为uS
	
//	IWDG_Configuration(1000);													//独立看门狗配置---参数单位ms
	
	PWM_OUT(TIM2,PWM_OUTChannel1,1,10);						//PWM设定-20161127版本
	
}
//=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>
//->函数名		:	
//->功能描述	:	 
//->输入		:	
//->输出		:
//->返回 		:
//<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=
void FatFsTest_Server(void)
{
//  for(mm=0;mm<800;mm++)
//  {
//    for(us=0;us<480;us++)
//    {
//      if(dspdata++>=0xFFFF)
//        dspdata=0;
//      LCD_DrawDot(mm,us,dspdata);
//    }
//  }
////	LCD_Server();			//显示服务相关
//  if(time++>500)
//  {
//    float te  = 0.1;
//    time  = 0;
//    te  = Get_ADC_Temperature(ADCDATA);
//    LCD_Printf (0,350,32,0,"%-0.2f",te);					//自定义printf串口DMA发送程序,后边的省略号就是可变参数
//  }

//	TM1618_DIS();
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
  millisecond++;
	if(millisecond>999)
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
				LCD_Printf(300,230,32,0,"%02d:",hour);		//后边的省略号就是可变参数
				
			}
			LCD_Printf(348,230,32,0,"%02d:",min);		//后边的省略号就是可变参数
		}
		LCD_Printf(396,230,32,0,"%02d",second);		//后边的省略号就是可变参数
  }
    
#if 0		//画圆
	unsigned short i	=	0;
	for(i=1;i<100;i++)
	{
		LCD_DrawCircle(400,	200, i, 0, LCD565_WHITE );			//画一个圆形框	
	}
	for(i=100;i>0;i--)
	{
		LCD_DrawCircle(200,	120, i, 0, LCD565_BLACK );			//画一个圆形框	
	}
	LCD_DrawCircle(200,	100, 50, 0, LCD565_YELLOW );			//画一个圆形框	
	LCD_DrawCircle(200,	300,	50, 0, LCD565_YELLOW );			//画一个圆形框	
	LCD_DrawCircle(600,	100, 50, 0, LCD565_YELLOW );			//画一个圆形框	
	LCD_DrawCircle(600,	300, 50, 0, LCD565_YELLOW );			//画一个圆形框	
	LCD_DrawCircle(400,	200, 100, 0, LCD565_YELLOW );			//画一个圆形框	
	
	SysTick_DeleymS(500);					//SysTick延时nmS
	LCD_Clean(LCD565_BLACK);		//清除屏幕函数--
#endif
#if 0		//画圆
//	LCD_Fill(10,10,50,50,LCD565_YELLOW);	//在指定区域内填充指定颜色;区域大小:(xend-xsta)*(yend-ysta)
	
//	LCD_DrawRectangle(10,130,60,180,LCD565_YELLOW);			//画一个矩形框
	
//	R61509V_ShowChar(10,120,32,5,"sdsdf");
	
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
	unsigned short	Rand;
	Rand	=	rand();
	x	=	sLCD.Data.HSX;
	y	=	sLCD.Data.MaxV-Rand%450;
//	LCD_DrawDot(x,y,LCD565_YELLOW);
	LCD_DrawLine(x-1,sLCD.Data.VSY,x,y,LCD565_YELLOW);
	
	LCD_DrawDot(x,y,LCD565_YELLOW);
	if(sLCD.Data.HSX>=sLCD.Data.MaxH)
	{
		sLCD.Data.HSX	=	1;
		LCD_Clean(LCD565_RED);			//清除屏幕函数--
//		SysTick_DeleymS(500);				//SysTick延时nmS
	}
	sLCD.Data.VSY	=	y;
	sLCD.Data.HSX++;
//	SysTick_DeleymS(100);					//SysTick延时nmS
#endif
#if 0		//刷屏测试
	u32 LCDTime=10;
//	unsigned short Color;
//	unsigned short y	=	0;
//	for(Color	=	0;Color<=0xFFFF;)
//	{
//		LCD_DrawLine(y,0,y,480,Color);						//AB 两个坐标画一条直线
//		SysTick_DeleymS(LCDTime);				//SysTick延时nmS
//		Color+=100;	
//		y++;
//		if(y>=800)
//			y=0;
//	}
	
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
#endif
#if 0	//画直线
	unsigned short HX	=	0;
	unsigned short HY	=	10;
//	for(HY	=	10;HY<=480;)
//	{
//		for(HX	=	10;HX<=800;)
//		{
//			LCD_DrawDot(HX,HY,LCD565_YELLOW);
//			HX	+=	1;
////			SysTick_DeleymS(10);				//SysTick延时nmS
//		}
//		HY	+=	2;
//	}
//	R61509V_SetWindowAddress(0,10,100,10);//设置窗地址
//	R61509V_SetWindowAddress(0,10,300,10);//设置窗地址
//	for(HX=0;HX<=400;HX++)
//	{
//		R61509V_WriteData16(R61509V_YELLOW); 	//笔画颜色	
//	}
	LCD_DrawLine(0,100,500,100,LCD565_YELLOW);
	LCD_DrawLine(100,0,100,230,LCD565_YELLOW);
	LCD_DrawLine(350,0,350,230,LCD565_YELLOW);
	SysTick_DeleymS(1000);				//SysTick延时nmS
	LCD_Clean(LCD565_RED);			//清除屏幕函数--蓝白
	//清除直线
	HX	=	10;HY	=	10;
	for(HX	=	10;HX<230;HX++)
	{
		for(HY	=	10;HY<=380;)
		{
			LCD_DrawDot(HX,HY,R61509V_RED);
			HY	+=	5;
			SysTick_DeleymS(100);				//SysTick延时nmS
		}
	}

//	LCD_Clean(R61509V_RED);			//清除屏幕函数--蓝白
#endif
#if 0	//LCD驱动调试.----画线
	unsigned short HX	=	0;
	unsigned short HY	=	10;
//	LCD_Clean(LCD565_RED);			//清除屏幕函数--蓝白
	HX	=	10;HY	=	10;
	for(HY	=	10;HY<=470;)
	{
		LCD_DrawLine(10,HY,790,HY,LCD565_YELLOW);
		HY	+=	5;
	}
	SysTick_DeleymS(1000);				//SysTick延时nmS
	HX	=	10;HY	=	10;
	for(HX	=	10;HX<=790;)
	{
		LCD_DrawLine(HX,10,HX,470,LCD565_YELLOW);
		HX	+=	5;
//		SysTick_DeleymS(100);				//SysTick延时nmS
	}
//	SysTick_DeleymS(1000);				//SysTick延时nmS
	//清除
	HX	=	10;HY	=	10;
	for(HY	=	10;HY<=470;)
	{
		LCD_DrawLine(10,HY,790,HY,LCD565_RED);
		HY	+=	5;
	}
	SysTick_DeleymS(1000);				//SysTick延时nmS
//	HX	=	10;HY	=	10;
//	for(HX	=	10;HX<=790;)
//	{
//		LCD_DrawLine(HX,10,HX,470,LCD565_RED);
//		HX	+=	5;
//	}
//	SysTick_DeleymS(1000);				//SysTick延时nmS
//	LCD_Clean(LCD565_RED);			//清除屏幕函数--蓝白
#endif
#if 0
//	LCD_Clean(LCD565_RED);			//清除屏幕函数--蓝白
	
//	LCD_Printf(0		,0,32	,"显");									//待发药槽位，后边的省略号就是可变参数
	
	LCD_Printf(300,230,32,"%02d:",hour);		//后边的省略号就是可变参数
	LCD_Printf(348,230,32,"%02d:",min);			//后边的省略号就是可变参数
	LCD_Printf(396,230,32,"%02d",second);		//后边的省略号就是可变参数
	
//	LCD_Printf(0		,0,16	,"待发药槽位，后边的省略号就是可变参数……");									//待发药槽位，后边的省略号就是可变参数
//	LCD_Printf(0		,16,16	,"显示测试……");									//待发药槽位，后边的省略号就是可变参数
//	LCD_Printf(0		,32,32	,"显示测试……");									//待发药槽位，后边的省略号就是可变参数
//	LCD_Printf(0		,64,32	,"显示测试……");									//待发药槽位，后边的省略号就是可变参数
//	LCD_Printf(0		,96,32	,"显示测试……");									//待发药槽位，后边的省略号就是可变参数
//	LCD_Printf(0		,128,32	,"测试显示……");									//待发药槽位，后边的省略号就是可变参数
//	LCD_Printf(0		,160,32	,"怲试显示……");									//待发药槽位，后边的省略号就是可变参数

//	SysTick_DeleymS(1000);				//SysTick延时nmS
//	LCD_Clean(LCD565_RED);			//清除屏幕函数--蓝白	
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
void LCD_Configuration(void)
{
	SPIDef	*SPI	=	&sLCD.GT32L32.SPI;
	sLCD.Port.sBL_PORT				=	GPIOC;
	sLCD.Port.sBL_Pin					=	GPIO_Pin_0;
	
	sLCD.Port.sRD_PORT				=	GPIOC;
	sLCD.Port.sRD_Pin					=	GPIO_Pin_1;	
	
	sLCD.Port.sREST_PORT			=	GPIOC;
	sLCD.Port.sREST_Pin				=	GPIO_Pin_2;
	
	sLCD.Port.sDC_PORT				=	GPIOC;
	sLCD.Port.sDC_Pin					=	GPIO_Pin_3;
	
	sLCD.Port.sWR_PORT				=	GPIOC;
	sLCD.Port.sWR_Pin					=	GPIO_Pin_4;	
	
	sLCD.Port.sTE_PORT				=	GPIOC;
	sLCD.Port.sTE_Pin					=	GPIO_Pin_5;
	
	sLCD.Port.sCS_PORT				=	GPIOC;
	sLCD.Port.sCS_Pin					=	GPIO_Pin_5;
	
	sLCD.Port.sDATABUS_PORT		=	GPIOE;
	sLCD.Port.sDATABUS_Pin		=	GPIO_Pin_All;	
	
	sLCD.Flag.Rotate	=	Draw_Rotate_180D;		//使用旋转角度
  sLCD.Data.BColor  = LCD565_BLACK;
  sLCD.Data.PColor  = LCD565_WHITE;
	
	SPI->Port.SPIx		=	SPI1;
	SPI->Port.CS_PORT	=	GPIOB;
	SPI->Port.CS_Pin	=	GPIO_Pin_14;
	SPI->Port.SPI_BaudRatePrescaler_x=SPI_BaudRatePrescaler_2;
	
	SSD1963_Initialize(&sLCD);
}

/*******************************************************************************
*函数名			:	function
*功能描述		:	函数功能说明
*输入				: 
*返回值			:	无
*******************************************************************************/
void TM1618_PinSet(void)
{
	TM1618_1.TM1618_CLK_PORT	=GPIOC;
	TM1618_1.TM1618_CLK_Pin		=GPIO_Pin_8;
	
	TM1618_1.TM1618_DIO_PORT	=GPIOC;
	TM1618_1.TM1618_DIO_Pin		=GPIO_Pin_9;	
	
	TM1618_1.TM1618_STB_PORT	=GPIOC;
	TM1618_1.TM1618_STB_Pin		=GPIO_Pin_10;
	
	TM1618_2.TM1618_CLK_PORT	=GPIOC;
	TM1618_2.TM1618_CLK_Pin		=GPIO_Pin_8;
	
	TM1618_2.TM1618_DIO_PORT	=GPIOC;
	TM1618_2.TM1618_DIO_Pin		=GPIO_Pin_9;	
	
	TM1618_2.TM1618_STB_PORT	=GPIOC;
	TM1618_2.TM1618_STB_Pin		=GPIO_Pin_11;
	
	TM1618_PinConf(&TM1618_1);
	TM1618_PinConf(&TM1618_2);
	
	GPIO_Configuration_OPP50	(GPIOC,	GPIO_Pin_12);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605
	
	PC12=1;
}

/*******************************************************************************
*函数名			:	function
*功能描述		:	函数功能说明
*输入				: 
*返回值			:	无
*******************************************************************************/
void TM1618_DIS(void)
{
	if(us++>=1000)
	{
		us=0;
		mm++;
		if(mm>=60)
		{
			mm=0;
			ss++;
		}
		if(ss>=60)
		{
			ss=0;
			hh++;
		}
		if(hh>=24)
		{
			hh=0;
		}
		
		dspdata=(u32)mm+(u32)ss*100+(u32)hh*10000;
		TM1618_WriteDataN(&TM1618_1,dspdata/10000);
		TM1618_WriteDataN(&TM1618_2,dspdata%10000);	
	}
}


#endif
