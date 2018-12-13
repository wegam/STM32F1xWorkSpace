#ifdef FSMCTest

#include "FSMCTest.H"

#include "string.h"				//串和内存操作函数头文件
//#include "stm32f10x_dma.h"

#include "LCD.H"
#include "NAND.H"


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
#include "STM32_RTC.H"
//#include	"image.h"
//#include "STM32_DMA.H"

//#include 	"Image.H"
//#include "MMC_SD.h"
#include "FatFsAPI.h"			/* 自定义API接口*/

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
BYTE buffer[4096];    //文件拷贝缓冲区
char FilSearchInf[FileNum][13]={0,0};    //存储查找到的文件名数组
unsigned char LenName = 0;

UINT br, bw;          //文件读/写字节计数
u16 xh=0,yv=0;
char Key = 0;
unsigned  short color = 0;
unsigned	short	Rait	=	0;
unsigned	long	ImageAr	=	0;
unsigned	short	sysledtime=0;
unsigned	char	sysledflag=0;
unsigned	short	Ratio	=	0;

 u16 year; 
 u8 month;
 u8 day;
 u8 hour;
 u8 minute;
 u8 second;
u16 millisecond=0;

void GetTime(void);
void ClockServer(void);
void SYSLED(void);
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
  RTC_Configuration();
//  SD_Configuration();
  GetTime();

  LCD_SetBackground(LCD565_LBBLUE);
  LCD_ShowBattery(780,2,2,LCD565_GRED);   //显示12x12电池
  LCD_ShowAntenna(760,2,3,LCD565_GRED);   //显示12x12天线
  
//  USART_DMA_ConfigurationNR	(USART1,115200,128);	//USART_DMA配置--查询方式，不开中断
  
  LCD_Printf(10,10,32,LCD565_BRED,"FSMC液晶屏驱动测试：%0.4d年%0.2d月%0.2d日%0.2d时%0.2d分%0.2d秒",
    year,month,day,hour,minute,second);  //后边的省略号就是可变参数
	PWM_OUT(TIM2,PWM_OUTChannel1,2,300);						//PWM设定-20161127版本
//	PWM_OUT(TIM4,PWM_OUTChannel1,2000,0);						//PWM设定-20161127版本
//	PWM_OUT(TIM4,PWM_OUTChannel2,500,500);						//PWM设定-20161127版本
//	PWM_OUT(TIM4,PWM_OUTChannel3,2000,0);						//PWM设定-20161127版本
	
  
//	GPIO_Configuration_OPP50	(GPIOA,GPIO_Pin_0);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605
	
//  IWDG_Configuration(1000);													//独立看门狗配置---参数单位ms
  SysTick_Configuration(1000);    //系统嘀嗒时钟配置72MHz,单位为uS
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
//  unsigned short RxNum  = 0;
//  ClockServer();
  RTC_Server();
//	SYSLED();
//  RxNum = USART_ReadBufferIDLE(USART1,buffer);
//  if(RxNum)
//  {
//    USART_DMASend(USART1,buffer,RxNum);
//  }
//  if(time++<1000)
//    return;
//  time  = 0;
//  if(time++<9)
//  USART_DMAPrintfList(USART1,"RTC时钟%0.2d:%0.4d年%0.2d月%0.2d日%0.2d时%0.2d分%0.2d秒\r\n",
//    time,calendar.w_year,calendar.w_month,calendar.w_date,calendar.hour,calendar.min,calendar.sec);
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
void SYSLED(void)
{
	if(sysledtime++>5)
	{
		sysledtime	=	0;
		if(0==sysledflag)
		{
			if(Ratio++>999)
			{
				sysledflag	=	1;
			}
		}
		else
		{
			if(Ratio--==500)
			{
				sysledflag	=	0;
			}
		}
		PWM_OUT(TIM2,PWM_OUTChannel1,1000,Ratio);						//PWM设定-20161127版本
//		SetPWM_Ratio(Ratio);		//设置占空比---LED
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
void RTC_Server(void)
{
  static unsigned char  sec=0;  
  if(sec!=calendar.sec)
  {
    if(0==calendar.w_year||0==calendar.w_month||0==calendar.w_date)
    {
      RTC_Get();
      if(0==calendar.w_year||0==calendar.w_month||0==calendar.w_date)
      {
        GetTime();
        RTC_Set(year,month,day,hour,minute,second+9);   //编译下载时间会慢7秒
      }
    }
    sec=calendar.sec;
    LCD_Printf(0,180,32,LCD565_BLACK,"RTC时钟:%0.4d年%0.2d月%0.2d日%0.2d时%0.2d分%0.2d秒",
    calendar.w_year,calendar.w_month,calendar.w_date,calendar.hour,calendar.min,calendar.sec);
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
/*******************************************************************************
*函数名			:	function
*功能描述		:	function
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
void SD_Configuration(void)
{
  u16 da=0;
  u16 color;
  
  
  
  LCD_Printf (0,0,16,LCD565_GREEN,"STM32F1xWorkSpace--(MmcSDTest)SD卡读取");					//自定义printf串口DMA发送程序,后边的省略号就是可变参数
  LCD_Printf (0,16,16,LCD565_GREEN,"为驱动器注册工作区......");					//自定义printf串口DMA发送程序,后边的省略号就是可变参数
  //========================为逻辑驱动器注册工作区
  result = f_mount(&FatFsObj[0],"0:",1);    //在FatFs模块上注册/注销一个工作区(文件系统对象)
  if(0  ==  result)
  {
    u32 sd_size;
    u32 free;
    LCD_Printf (0,32,16,LCD565_GREEN,"驱动器注册成功");					//自定义printf串口DMA发送程序,后边的省略号就是可变参数
    //========================得到容量信息，包括总容量和剩余容量
    result = SD_disk_getcapacity("0",&sd_size,&free);
    if(0  ==  result)
    {
      LCD_Printf (0,48,16,LCD565_GREEN,"SD卡容量%dKByte,%dMB,%0.5fGB",sd_size,sd_size>>10,(double)(sd_size>>10)/1024);					//自定义printf串口DMA发送程序,后边的省略号就是可变参数
      //========================获取剩余容量    
      LCD_Printf (0,64,16,LCD565_GREEN,"SD卡剩余容量%dKByte,%dMB,%0.5fGB",free,free>>10,(double)(free>>10)/1024);					//自定义printf串口DMA发送程序,后边的省略号就是可变参数
      free  = sd_size-free;
      LCD_Printf (0,80,16,LCD565_GREEN,"已用容量%dKByte,%dMB,%0.5fGB",free,free>>10,(double)(free>>10)/1024);					//自定义printf串口DMA发送程序,后边的省略号就是可变参数
    }
    else
    {
      LCD_Printf (0,48,16,LCD565_GREEN,"容量信息查询失败");					//自定义printf串口DMA发送程序,后边的省略号就是可变参数
      return;
    }
  }
  else
  {
    LCD_Printf (0,32,16,LCD565_GREEN,"驱动器注册失败");					//自定义printf串口DMA发送程序,后边的省略号就是可变参数
    return;
  }
  //========================查找指定文件
  LCD_Printf (0,96,16,LCD565_GREEN,"查找指定文件:bmp");					//自定义printf串口DMA发送程序,后边的省略号就是可变参数
  result  = FilSearch(&FatFsObj[0],&dir,"0:/","bmp",FilSearchInf);  //在指定路径下查找指定扩展名的文件，并记录在(*p)[13]数组中，注意最大记录条数
  if(0 != result)
  {
    unsigned short    i=0;
    unsigned short    j = 0;
    unsigned short    flg=0;
    LCD_Printf (0,112,16,LCD565_GREEN,"查找到bmp文件");					//自定义printf串口DMA发送程序,后边的省略号就是可变参数
    for(i=0;i<FileNum;i++)
    {
      if(0  !=  FilSearchInf[i][0])
      {
        unsigned char k = 0;
        for(k=0;k<13;++k)
        {
          if(0  ==  FilSearchInf[i][k])
            break;
        }
        //===============打印查找的bmp文件名
        LCD_Show(0,128+i*16,16,LCD565_GREEN,k,FilSearchInf[i]);
      }
    }
    while(1)
    {
//      i=0;
//      j=0;
      //===============================图片1
      for(i=0;i<FileNum;i++)
      {
        if(FilSearchInf[i][0] !=0)
        {
          yv  = 0;
          flg = 0;
          result  = f_open(&fsrc,&FilSearchInf[i][0],FA_READ);
//          if(result)
//            break;
          for(j=0;j<480;j++)
          {
            if(flg==0)
            {
              result  = f_read(&fsrc,buffer,54,&br);
            }
            else
            {
              result  = f_read(&fsrc,buffer,2400,&br);
            }
            if(FR_OK  !=  result)
            {
    //          return;
            }
            da  = 0;
            if(flg==0)
            {
              flg = 1;
              da  = 0;
              result  = f_read(&fsrc,buffer,2400,&br);
            }

            LCD_ShowBMP(0,yv,800,yv,br,buffer);    //显示十六进制数据
            yv+=1;
            if(yv>=480)
              yv  = 0;
          }
//          SysTick_DeleyS(3);					//SysTick延时nS
        }
      }           
    }    
  }
  else
  {    
    LCD_Printf (0,112,16,LCD565_GREEN,"未找到bmp文件");					//自定义printf串口DMA发送程序,后边的省略号就是可变参数    
  }
//  f_getfree();  

}
#endif
