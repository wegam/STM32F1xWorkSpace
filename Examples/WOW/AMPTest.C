#ifdef AMPTest

#include "AMPTest.H"

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
#include 	"CRC.H"

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


#define ussize  256     //串口缓存大小
unsigned char u1txbuffer[ussize];
unsigned char u1rxbuffer[ussize];
unsigned char u3txbuffer[ussize];
unsigned char u3rxbuffer[ussize];
unsigned char u2txbuffer[ussize];
unsigned char u2rxbuffer[ussize];
unsigned short u1dsp=32;
unsigned short u3dsp=32;
unsigned short u1dspcolr=LCD565_RED;
unsigned short u3dspcolr=LCD565_RED;

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

unsigned char txflg = 0;
//unsigned char OpenLed[]={0x7E,0x09,0x03,0x01,0x01,0x01,0x01,0x01,0xB0,0x2C,0x6D,0x84,0xF3,0x7F};  //Address1中控制输出端口1以LED驱动的方式打开
//unsigned char ClosLed[]={0x7E,0x09,0x03,0x01,0x01,0x01,0x01,0x00,0x4D,0x13,0x30,0xC4,0xF6,0x7F};  //Address1中控制输出端口1以LED驱动的方式关闭

unsigned char OpenLed[]={0x7E,0x09,0x03,0x01,0x01,0x01,0x01,0x01,0x57,0x29,0x51,0x84,0xF3,0x7F};  //Address1中控制输出端口1以LED驱动的方式打开
unsigned char ClosLed[]={0x7E,0x09,0x03,0x01,0x01,0x01,0x01,0x00,0x00,0x00,0x00,0xC4,0xF6,0x7F};  //Address1中控制输出端口1以LED驱动的方式关闭

 u16 year; 
 u8 month;
 u8 day;
 u8 hour;
 u8 minute;
 u8 second;
u16 millisecond=0;

unsigned short crc16mbs = 0;

RS485Def RS485A;
RS485Def RS485B;

void GetTime(void);
void ClockServer(void);
void SYSLED(void);
void USART_TEST(void);
void RS485Configuration(void);
//=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>
//->函数名		:	
//->功能描述	:	 
//->输入		:	
//->输出		:
//->返回 		:
//<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=
void AMPTest_Configuration(void)
{	
  RCC_ClocksTypeDef RCC_ClocksStatus;							//时钟状态---时钟值
	SYS_Configuration();					//系统配置---打开系统时钟 STM32_SYS.H	
  Power_Configuration();
  LCD_Configuration();
  RTC_Configuration();
//  SD_Configuration();
  GetTime();
  
  LCD_SetBackground(LCD565_WHITE);
  LCD_ShowBattery(780,2,2,LCD565_GRED);   //显示12x12电池
  LCD_ShowAntenna(760,2,3,LCD565_GRED);   //显示12x12天线

  
//  LCD_Printf(10,10,32,LCD565_BRED,"FSMC液晶屏驱动测试：%0.4d年%0.2d月%0.2d日%0.2d时%0.2d分%0.2d秒",
//    year,month,day,hour,minute,second);  //后边的省略号就是可变参数
  
  
  USART_DMA_ConfigurationNR	(USART1,19200,ussize);	//USART_DMA配置--查询方式，不开中断
  USART_DMA_ConfigurationNR	(USART3,19200,ussize);	//USART_DMA配置--查询方式，不开中断
  RS485Configuration();
	PWM_OUT(TIM2,PWM_OUTChannel1,100,900);						//PWM设定-20161127版本

	
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
void AMPTest_Server(void)
{
//  ClockServer();
  RTC_Server();
  USART_Server();
  //USART_TEST();
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
void RS485Configuration(void)
{
	RS485B.USARTx	=	USART2;
	RS485B.RS485_CTL_PORT	=	GPIOA;
	RS485B.RS485_CTL_Pin	=	GPIO_Pin_1;
	
	RS485_DMA_ConfigurationNR	(&RS485B,19200,ussize);	//USART_DMA配置--查询方式，不开中断,配置完默认为接收状态
}
//=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>
//->函数名		:	
//->功能描述	:	 
//->输入		:	
//->输出		:
//->返回 		:
//<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=
void USART_TEST(void)
{
  unsigned short RxNum  = 0;
  static  unsigned  short serial  = 0;
  static  unsigned  short testtime  = 0;
  
  if(testtime++>1000)
  {
    unsigned  short crc16 = 0;
    testtime  = 0;
    serial++;
    memcpy(u3txbuffer,&serial,2);
    if(0  !=  txflg)  //开LED
    {
      txflg = 0;
      crc16 = CRC16_MODBUS(&OpenLed[1],10);
      memcpy(&OpenLed[11],&crc16,2);
      api_usart_dma_send(USART3,OpenLed,sizeof(OpenLed));
    }
    else  //关LED
    {
      txflg = 1;
      crc16 = CRC16_MODBUS(&ClosLed[1],10);
      memcpy(&ClosLed[11],&crc16,2);
      api_usart_dma_send(USART3,ClosLed,sizeof(ClosLed));
    }
  }

  RxNum = USART_ReadBufferIDLE(USART1,u1rxbuffer);
  if(RxNum)
  {
    memcpy(u3txbuffer,u1rxbuffer,RxNum);
    api_usart_dma_send(USART3,u3txbuffer,RxNum);
    LCD_ShowHex(0,u1dsp,16,u1dspcolr,RxNum,8,u3txbuffer);
    u1dsp+=16;
    if(u1dsp>=479)
    {
      if(LCD565_RED !=  u1dspcolr)
      {
        u1dspcolr = LCD565_RED;
      }
      else
      {
        u1dspcolr = LCD565_BLUE;
      }
      u1dsp=32;
    }
  }
  RxNum = USART_ReadBufferIDLE(USART3,u3rxbuffer);
  if(RxNum)
  {
    memcpy(u1txbuffer,u3rxbuffer,RxNum);
    api_usart_dma_send(USART1,u1txbuffer,RxNum);
    LCD_ShowHex(400,u3dsp,16,u3dspcolr,RxNum,8,u1txbuffer);
    u3dsp+=16;
    if(u3dsp>=479)
    {
      if(LCD565_RED !=  u3dspcolr)
      {
        u3dspcolr = LCD565_RED;
      }
      else
      {
        u3dspcolr = LCD565_BLUE;
      }
      u3dsp=32;
    }
  }
}
//=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>
//->函数名		:	
//->功能描述	:	 
//->输入		:	
//->输出		:
//->返回 		:
//<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=
void USART_Server(void)
{
  unsigned short RxNum  = 0;


  RxNum = USART_ReadBufferIDLE(USART1,u1rxbuffer);
  if(RxNum)
  {
    memcpy(u3txbuffer,u1rxbuffer,RxNum);
    
    crc16mbs  = CRC16_MODBUS(&u3txbuffer[1],u3txbuffer[1]+1);
    
    memcpy(&u3txbuffer[u3txbuffer[1]+2],&crc16mbs,2);
    
    api_usart_dma_send(USART3,u3txbuffer,RxNum);
		RS485_DMASend(&RS485B,u3txbuffer,RxNum);	//RS485-DMA发送程序
    LCD_ShowHex(0,u1dsp,16,u1dspcolr,RxNum,8,u3txbuffer);
    u1dsp+=(RxNum/33+1)*16;
    if(LCD565_RED==u1dspcolr)
		{
			u1dspcolr = LCD565_BLUE;
		}
		else
		{
			u1dspcolr = LCD565_RED;
		}
    if(u1dsp>=479)
    {
      LCD_Fill(0,32,800,480,sLCD.Data.BColor);				//在指定区域内填充指定颜色;区域大小:(xend-xsta)*(yend-ysta)
      u1dsp=32;
      u3dsp=32;
    }
  }
  RxNum = USART_ReadBufferIDLE(USART3,u3rxbuffer);
  if(RxNum)
  {
    memcpy(u1txbuffer,u3rxbuffer,RxNum);
    api_usart_dma_send(USART1,u1txbuffer,RxNum);
    LCD_ShowHex(0,u3dsp,16,u3dspcolr,RxNum,8,u1txbuffer);
    u3dsp+=16;
    if(u3dsp>=479)
    {
      if(LCD565_RED !=  u3dspcolr)
      {
        u3dspcolr = LCD565_RED;
      }
      else
      {
        u3dspcolr = LCD565_BLUE;
      }
      LCD_Fill(0,32,800,480,sLCD.Data.BColor);				//在指定区域内填充指定颜色;区域大小:(xend-xsta)*(yend-ysta)
      u3dsp=32;
    }
  }
	RxNum = RS485_ReadBufferIDLE(&RS485B,u2rxbuffer);
	if(RxNum)
	{
		memcpy(u1txbuffer,u2rxbuffer,RxNum);
    api_usart_dma_send(USART1,u1txbuffer,RxNum);
    LCD_ShowHex(0,u1dsp,16,u1dspcolr,RxNum,8,u1txbuffer);
		u1dsp+=(RxNum/33+1)*16;
		if(LCD565_RED==u1dspcolr)
		{
			u1dspcolr = LCD565_BLUE;
		}
		else
		{
			u1dspcolr = LCD565_RED;
		}
    if(u1dsp>=479)
    {
      LCD_Fill(0,32,800,480,sLCD.Data.BColor);				//在指定区域内填充指定颜色;区域大小:(xend-xsta)*(yend-ysta)
      u1dsp=32;
      u3dsp=32;
    }
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
void SYSLED(void)
{
	if(sysledtime++>200)
	{
		sysledtime	=	0;
		if(0==sysledflag)
		{
			Ratio+=1;
			if(Ratio>35)
			{
				sysledflag	=	1;
			}
		}
		else
		{
			Ratio-=1;
			if(Ratio<=20)
			{
				sysledflag	=	0;
			}
		}
		PWM_OUT(TIM2,PWM_OUTChannel1,2000,Ratio*Ratio);						//PWM设定-20161127版本
//		SetPWM_Ratio(Ratio*Ratio);		//设置占空比---LED
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
//    if(0==calendar.sec)
//      LCD_Clean(sLCD.Data.BColor);	//清除屏幕函数
    sec=calendar.sec;
    LCD_Printf(0,0,32,LCD565_BLACK,"RTC时钟:%0.4d年%0.2d月%0.2d日%0.2d时%0.2d分%0.2d秒",
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
