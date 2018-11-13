#ifdef FSMCTest

#include "FSMCTest.H"

//#include "string.h"				//串和内存操作函数头文件
//#include "stm32f10x_dma.h"

#include "LCD.H"


#include "STM32F10x_BitBand.H"
#include "STM32_GPIO.H"
#include "STM32_SYS.H"
#include "STM32_SYSTICK.H"
#include "STM32_ADC.H"
#include "STM32_WDG.H"
#include "STM32_FSMC.H"
#include "STM32_PWM.H"
//#include "STM32_PWM.H"
//#include "STM32_GPIO.H"
#include "STM32_USART.H"
//#include	"image.h"
//#include "STM32_DMA.H"

//#include 	"Image.H"
//#include 	"LinkedList.H"

//#include "TM1618.H"
//#include "MMC_SD.h"
//#include "FatFsAPI.h"			/* 自定义API接口*/

//#include "STM32_SDCard.H"
//#include "GT32L32M0180.H"
#include 	"TOOL.H"


//#define SDCardTest
//#define GT32L32M0180Test
//把TFT看做类似SRAM的存储器，只能接在 BANK1上。对应基地址是0x60000000.
//而BANK1又有划分为四个片选,分别对应基地址:
//NE1 0x600000000
//NE2 0x640000000
//NE3 0x680000000
//NE4 0x6C0000000

//数据区地址
#define Bank1_LCD_Data ((u32)0x6C100000)
//寄存器区地址
#define Bank1_LCD_Reg ((u32)0x6C000000)

LCDDef	sLCD;




//u8 GTBuffer[512]={0};		//点阵数据存储空间

u32	dspdata=0;
u16 us=0;
u16	mm=0;
u8	ss=0;
u8	hh=0;

u8 bsr  = 0x08;

u16 time=0;
u32 ADCDATA = 0;
//void GT32L32_PinSet(void);
#define FileNum 16
FRESULT result;       //FatFs 函数公共结果代码
FATFS   FatFsObj[1];  //逻辑驱动器的工作区(文件系统对象)
DIR     dir;          //目录对象结构体
FILINFO fno;          //文件信息结构体
FIL fsrc, fdst;       //文件对象
//BYTE buffer[4096];    //文件拷贝缓冲区
char FilSearchInf[FileNum][13]={0,0};    //存储查找到的文件名数组
unsigned char LenName = 0;

UINT br, bw;          //文件读/写字节计数
u16 xh=0,yv=0;
char Key = 0;
unsigned  short color = 0;
unsigned	short	Rait	=	0;
unsigned	long	ImageAr	=	0;

 u16 year; 
 u8 month;
 u8 day;
 u8 hour;
 u8 minute;
 u8 second;
u16 millisecond=0;

void GetTime(void);
void ClockServer(void);
//=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>
//->函数名		:	
//->功能描述	:	 
//->输入		:	
//->输出		:
//->返回 		:
//<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=
void FSMCTest_Configuration(void)
{	
  RCC_ClocksTypeDef RCC_ClocksStatus;							//时钟状态---时钟值
	SYS_Configuration();					//系统配置---打开系统时钟 STM32_SYS.H	
  Power_Configuration();
  LCD_Configuration();
  GetTime();

//  res = f_open(&fsrc, "1:srcfile.dat", FA_OPEN_EXISTING | FA_READ);
//  ADC_TempSensorConfiguration(&ADCDATA);								//STM32内部温度传感器配置
//  LCD_ShowBattery(780,2,2,LCD565_GREEN);   //显示12x12电池
//  LCD_ShowAntenna(760,2,3,LCD565_GREEN);   //显示12x12天线
  
//  LCD_Printf (300,0,32,LCD565_GREEN,"图片显示测试");					//自定义printf串口DMA发送程序,后边的省略号就是可变参数
  
//	SysTick_Configuration(1000);											//系统嘀嗒时钟配置72MHz,单位为uS
	
//	IWDG_Configuration(1000);													//独立看门狗配置---参数单位ms
//  SysTick_DeleymS(500);
//  LCD_Clean(LCD565_BLUE);
  LCD_ShowBattery(780,2,2,LCD565_GRED);   //显示12x12电池
  LCD_ShowAntenna(760,2,3,LCD565_GRED);   //显示12x12天线
  LCD_Printf(10,10,32,LCD565_BRED,"后边的省略号就是可变参数");  //后边的省略号就是可变参数
	PWM_OUT(TIM2,PWM_OUTChannel1,2000,900);						//PWM设定-20161127版本
  
  SysTick_Configuration(1000);
//  SysTick_DeleymS(500);
//  LCD_Clean(LCD565_WHITE);
//	while(1)
//	{
//    RCC_GetClocksFreq(&RCC_ClocksStatus);	//获取时钟参数
//    LCD_Printf(10,10,32,LCD565_BRED,"后边的省略号就是可变参数%0.8d",SysTick->VAL);  //后边的省略号就是可变参数
//		LCD_Clean(LCD565_BLACK);SysTick_DeleymS(500);
//		LCD_Clean(LCD565_WHITE);SysTick_DeleymS(500);	
//		LCD_Clean(LCD565_BLUE);SysTick_DeleymS(500);
//		LCDCLER(LCD565_BRED);SysTick_DeleymS(500);
//		LCDCLER(LCD565_GRED);SysTick_DeleymS(500);
//	}
//  LCD_Printf(0,220,32,LCD565_RED,"%0.4d-",year);		//编译日期
//  LCD_Printf(5*16,220,32,LCD565_RED,"%0.2d-",month);		//编译日期
//  LCD_Printf(8*16,220,32,LCD565_RED,"%0.2d-",day);		//编译日期
//	LCD_Printf(11*16,220,32,LCD565_RED,"%0.2d:",hour);		//编译日期
//  LCD_Printf(14*16*3,220,32,LCD565_RED,"%0.2d:",minute);		//编译日期
//  LCD_Printf(17*16,220,32,LCD565_RED,"%0.2d:",second);		//编译日期
}

//=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>
//->函数名		:	
//->功能描述	:	 
//->输入		:	
//->输出		:
//->返回 		:
//<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=
void FSMCTest_Server(void)
{
//  unsigned  short i = 0;
//  for(i=0;i<0x1FFFFFF;i++)
//  {
//    LCD_Printf(10,10,32,LCD565_RED,"后边的省略号就是可变参数%0.8d",i);  //后边的省略号就是可变参数
//    i+=89;
//  }
  ClockServer();
//	LCD_Clean(LCD565_WHITE);SysTick_DeleymS(200);	
//	LCD_Clean(LCD565_BLUE);SysTick_DeleymS(200);
//	LCD_Clean(LCD565_BRED);SysTick_DeleymS(200);
//	LCD_Clean(LCD565_GRED);SysTick_DeleymS(200);
//	LCD_Clean(LCD565_RED);
//  LCD_Clean(LCD565_BLACK);
//  SysTick->LOAD=800000000;
//  SysTick_Configuration(1000);
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
void GetTime(void)
{
	BuildTimeDef*	BuildTime	=	GetBuildTime(__DATE__,__TIME__);
	
  year  	= BuildTime->year;
  month 	= BuildTime->month;
  day   	= BuildTime->day;
  hour  	= BuildTime->hour;
  minute  = BuildTime->minute;
	
  second  = BuildTime->second;
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
void ClockServer(void)
{
  static char Flag = 0;
  if(Flag== 0)
  {
    Flag= 1;
    
    LCD_Printf(0,220,32,LCD565_RED,"%0.4d-",year);		//编译日期
    LCD_Printf(5*16,220,32,LCD565_RED,"%0.2d-",month);		//编译日期
    LCD_Printf(8*16,220,32,LCD565_RED,"%0.2d",day);		//编译日期
    
    LCD_Printf(13*16,220,32,LCD565_RED,"%0.2d:",hour);		//编译日期
    LCD_Printf(16*16,220,32,LCD565_RED,"%0.2d:",minute);		//编译日期
    LCD_Printf(19*16,220,32,LCD565_RED,"%0.2d",second);		//编译日期    
  }
  if(++millisecond>999)
  {
    millisecond = 0;
    if(++second>59)
    {    
      second  = 0;
      if(++minute>59)
      {  
        minute  = 0;
        if(++hour>=24)
        { 
          hour = 0;
          LCD_Printf(8*16,220,32,LCD565_RED,"%0.2d",++day);		//编译日期
        }
        LCD_Printf(13*16,220,32,LCD565_RED,"%0.2d:",hour);		//编译日期      
      }
      LCD_Printf(16*16,220,32,LCD565_RED,"%0.2d:",minute);		//编译日期    
    }
    LCD_Printf(19*16,220,32,LCD565_RED,"%0.2d",second);		//编译日期
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
void Power_Configuration(void)
{
  unsigned  short  temp  = 0;
  GPIO_Configuration_IPU(GPIOB,	GPIO_Pin_4);			//将GPIO相应管脚配置为上拉输入模式----V20170605
  GPIO_Configuration_OPP50(GPIOF,GPIO_Pin_10);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605
  restart:
  PF10 = 1;
	SysTick_DeleymS(1000);					//SysTick延时nS
//  while(0  ==  PB4in)
//  {
//    SysTick_DeleymS(1);					//SysTick延时nS
//    temp++;
//    if(temp>3000)
//    {
//      Key = 0;
//      
//      break;
//    }
//    
//  }
//  if(temp<3000)
//  {
//    PF10  = 1;
//    temp  = 0;
//    goto restart;
//  }
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
void Power_Server(void)
{
  unsigned  short  temp  = 0;

  if((0  ==  PB4in)&&(1==Key))
  {
    while(0  ==  PB4in)
    {
      SysTick_DeleymS(1);					//SysTick延时nS
      temp++;
      if(temp>3000)
      {
        Key = 0;
        PF10  = 0;
        PWM_OUT(TIM2,PWM_OUTChannel1,1000,110);						//PWM设定-20161127版本
        while(0  ==  PB4in);
        NVIC_GenerateCoreReset();
      }
    }
  }
  else if(1 ==PB4in)
  {
    Key = 1;
  }
  
  if(temp<3000)
  {
    PF10  = 1;
//    while(1);
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
void LCD_Server(void)			//显示服务相关
{

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
  //=======================LCD端口
	LCDPortDef	*LcdPort	=	&sLCD.Port;
  
  LcdPort->sBL_PORT   = GPIOA;
  LcdPort->sBL_Pin    = GPIO_Pin_0;
  
  LcdPort->sCS_PORT   = GPIOG;
  LcdPort->sCS_Pin    = GPIO_Pin_12;
  
  LcdPort->sREST_PORT = NULL;
  LcdPort->sREST_Pin  = 0;
  
  sLCD.Data.FsmcRegAddr   = (unsigned long)0x6C000000;
  sLCD.Data.FsmcDataAddr  = (unsigned long)0x6C100000;
  
  sLCD.Data.BColor	=	LCD565_WHITE;
	sLCD.Data.PColor	=	LCD565_BLACK;
	sLCD.Flag.Rotate	=	Draw_Rotate_0D;
	
	//=======================字库端口
	sLCD.GT32L32.SPI.Port.SPIx	    =	SPI2;
	sLCD.GT32L32.SPI.Port.CS_PORT	  =	GPIOB;
	sLCD.GT32L32.SPI.Port.CS_Pin		=	GPIO_Pin_12;
	sLCD.GT32L32.SPI.Port.SPI_BaudRatePrescaler_x=SPI_BaudRatePrescaler_2;
  
  LCDFsmc_Initialize(&sLCD);  
}
#endif
