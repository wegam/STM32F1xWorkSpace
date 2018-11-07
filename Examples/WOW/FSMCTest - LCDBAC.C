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

u16 millisecond=0;
u8 hour=23,min=00,second=30;

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


//=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>
//->函数名		:	
//->功能描述	:	 
//->输入		:	
//->输出		:
//->返回 		:
//<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=
void FSMCTest_Configuration(void)
{	
	SYS_Configuration();					//系统配置---打开系统时钟 STM32_SYS.H	
  Power_Configuration();
  LCD_Configuration();
//  FSMC_Initialize();
//  SSD1963_Init(); 
	
//  SSD1963_Init();  
//  tee:
//  SSD1963_Init();
  LCDCLER(0x5FFF);
//  goto tee;
//  SD_Configuration();
//  USART_DMA_ConfigurationNR	(USART1,115200,128);	//USART_DMA配置--查询方式，不开中断
//  TM1618_PinSet();

//  res = f_open(&fsrc, "1:srcfile.dat", FA_OPEN_EXISTING | FA_READ);
//  ADC_TempSensorConfiguration(&ADCDATA);								//STM32内部温度传感器配置
//  LCD_ShowBattery(780,2,2,LCD565_GREEN);   //显示12x12电池
//  LCD_ShowAntenna(760,2,3,LCD565_GREEN);   //显示12x12天线
  
//  LCD_Printf (300,0,32,LCD565_GREEN,"图片显示测试");					//自定义printf串口DMA发送程序,后边的省略号就是可变参数
  
//	SysTick_Configuration(1000);											//系统嘀嗒时钟配置72MHz,单位为uS
	
//	IWDG_Configuration(1000);													//独立看门狗配置---参数单位ms
	PWM_OUT(TIM2,PWM_OUTChannel1,2000,900);						//PWM设定-20161127版本
	while(1)
	{
		LCDCLER(LCD565_BLACK);SysTick_DeleymS(500);
		LCDCLER(LCD565_WHITE);SysTick_DeleymS(500);	
		LCDCLER(LCD565_BLUE);SysTick_DeleymS(500);
//		LCDCLER(LCD565_BRED);SysTick_DeleymS(500);
//		LCDCLER(LCD565_GRED);SysTick_DeleymS(500);
	}
	
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
//  for(i=0;i<0xFFFF;i++)
//  {
//    LCDCLER((u16)(i));
//    i+=89;
//  }
	LCDCLER(LCD565_BLACK);SysTick_DeleymS(1000);
	LCDCLER(LCD565_WHITE);SysTick_DeleymS(1000);	
	LCDCLER(LCD565_BLUE);SysTick_DeleymS(1000);
	LCDCLER(LCD565_BRED);SysTick_DeleymS(1000);
	LCDCLER(LCD565_GRED);SysTick_DeleymS(1000);
	LCDCLER(LCD565_RED);SysTick_DeleymS(1000);
//	NVIC_GenerateCoreReset();
//	LCDCLER(LCD565_GRAY);SysTick_DeleymS(1000);
//	LCDCLER(LCD565_LIGHTGREEN);SysTick_DeleymS(1000);
//	LCDCLER(LCD565_MAGENTA);SysTick_DeleymS(1000);
  
//  Power_Server();
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
//	SPIDef	*SPI	=	&sLCD.GT32L32.SPI;
//	sLCD.Port.sBL_PORT				=	GPIOA;
//	sLCD.Port.sBL_Pin					=	GPIO_Pin_0;
//	
//	sLCD.Port.sRD_PORT				=	GPIOD;
//	sLCD.Port.sRD_Pin					=	GPIO_Pin_4;	
//	
//	sLCD.Port.sREST_PORT			=	GPIOA;
//	sLCD.Port.sREST_Pin				=	GPIO_Pin_0;
//	
//	sLCD.Port.sDC_PORT				=	GPIOE;
//	sLCD.Port.sDC_Pin					=	GPIO_Pin_3;
//	
//	sLCD.Port.sWR_PORT				=	GPIOD;
//	sLCD.Port.sWR_Pin					=	GPIO_Pin_5;	
//	
//	sLCD.Port.sTE_PORT				=	GPIOC;
//	sLCD.Port.sTE_Pin					=	GPIO_Pin_5;
//	
//	sLCD.Port.sCS_PORT				=	GPIOG;
//	sLCD.Port.sCS_Pin					=	GPIO_Pin_12;
//	
//	sLCD.Port.sDATABUS_PORT		=	GPIOE;
//	sLCD.Port.sDATABUS_Pin		=	GPIO_Pin_All;	
//	
//	sLCD.Flag.Rotate	=	Draw_Rotate_180D;		//使用旋转角度
//  sLCD.Data.BColor  = LCD565_BLACK;
//  sLCD.Data.PColor  = LCD565_WHITE;
//	
//	SPI->Port.SPIx		=	SPI1;
//	SPI->Port.CS_PORT	=	GPIOB;
//	SPI->Port.CS_Pin	=	GPIO_Pin_14;
//	SPI->Port.SPI_BaudRatePrescaler_x=SPI_BaudRatePrescaler_128;
//	
//	LCD_Initialize(&sLCD);

  //=======================LCD端口
	LCDPortDef	*LcdPort	=	&sLCD.Port;
  
//  GPIO_InitTypeDef GPIO_InitStructure;
//  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |RCC_APB2Periph_GPIOB |RCC_APB2Periph_GPIOC |RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE | RCC_APB2Periph_GPIOF | RCC_APB2Periph_GPIOG | RCC_APB2Periph_AFIO, ENABLE);
//  //背光控制
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;

//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;

//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

//  GPIO_Init(GPIOA, &GPIO_InitStructure);
//  
//  //LCD复位

//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;

//  GPIO_Init(GPIOE, &GPIO_InitStructure);
//  //打开FSMC的数据端口D[15:0]

//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_14 | GPIO_Pin_15;

//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;

//  GPIO_Init(GPIOD, &GPIO_InitStructure);
//  

//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 |  GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;

//  GPIO_Init(GPIOE, &GPIO_InitStructure);

//  //打开FSMC功能端口，PD.4=RD(nOE)；PD.5=WR(nWE)

//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;

//  GPIO_Init(GPIOD, &GPIO_InitStructure);

//  //打开NE4设置

//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;

//  GPIO_Init(GPIOG, &GPIO_InitStructure);

//  //打开RS设置

//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 ;

//  GPIO_Init(GPIOE, &GPIO_InitStructure);

//  //NE4=1

//  GPIO_SetBits(GPIOG, GPIO_Pin_12);

//  //LCD_RESET=0

//  GPIO_ResetBits(GPIOE, GPIO_Pin_1);

//  //LCD_RD=1(nOE)

//  GPIO_SetBits(GPIOD, GPIO_Pin_4);

//  //LCD_WR=1(nWE)

//  GPIO_SetBits(GPIOD, GPIO_Pin_5);

//  //背光LIGHT=1

////  GPIO_SetBits(GPIOA, GPIO_Pin_0);
//  
//  //NE4=0
//  GPIO_ResetBits(GPIOG, GPIO_Pin_12);
//  SysTick_DeleymS(100);
  



  LcdPort->sBL_PORT   = GPIOA;
  LcdPort->sBL_Pin    = GPIO_Pin_0;
  
  LcdPort->sCS_PORT   = GPIOG;
  LcdPort->sCS_Pin    = GPIO_Pin_12;
  
  LcdPort->sREST_PORT = NULL;
  LcdPort->sREST_Pin  = 0;
  
  sLCD.Data.FsmcRegAddr   = (unsigned long)0x6C000000;
  sLCD.Data.FsmcDataAddr  = (unsigned long)0x6C100000;
  
  LCDFsmc_Initialize(&sLCD);
}

//LCD写寄存器地址函数

void LCD_WriteAddr1(u16 index)
{
  *(vu16*)(Bank1_LCD_Reg) = index;
}
//LCD写数据函数

void LCD_WriteData1(u16 val)
{
  *(vu16*)(Bank1_LCD_Data) = val; 
}

//LCD写寄存器命令函数，先将命令地址写到Reg中，然后再将命令的数值写到Data中

//具体地址和配置参照ILI9325的Datasheet

void LCD_WR_CMD(u16 index, u16 val)
{

  *(vu16 *)(Bank1_LCD_Reg) = index;
  *(vu16 *)(Bank1_LCD_Data) = val;
}
/*******************************************************************************
*函数名		:	Lcd_Init
*功能描述	:	STM32内部温度传感器配置
*输入			: 
*输出			:	无
*返回值		:	无
*例程			:
*******************************************************************************/
void SSD1963_Init(void)
{

	u16 time=2000;
	u16	temp=time;
//调用一次这些函数，免得编译的时候提示警告
	//1）——————————复位
//	SSD1963_BACKLIGHT_OFF;	//关背光
//	LCD_REST();
//	LCD_RST_LOW;
//	LCD_RST_HIGH;
//	while(temp--);			//等待晶振启动
	//2）——————————复位
//	LCD_CS_HIGH;			//先取消片选
//	LCD_RD_HIGH;
//	LCD_WR_LOW;				//总线功能为写数据
//	LCD_CS_LOW;  		//使能
  SysTick_DeleymS(100);
	//3）——————————设置系统时钟  晶振频率 10MHz  250MHz < VCO < 800MHz
	LCD_WriteAddr1(0x00E2);						  //PLL multiplier, set PLL clock to 120M Start the PLL. Before the start, the system was operated with the crystal oscillator or clock input
	LCD_WriteData1(0x0023);	    				//设置倍频 N=0x36 for 6.5M, 0x23 for 10M crystal
	LCD_WriteData1(0x0001);							//设置分频
	LCD_WriteData1(0x0004);							//完成设置
	//4）——————————使能PLL
	LCD_WriteAddr1(0x00E0);  					//PLL enable
	LCD_WriteData1(0x0001);
	
	LCD_WriteAddr1(0x00E0);
	LCD_WriteData1(0x0003);
  SysTick_DeleymS(50);
	//5）——————————软件复位
	LCD_WriteAddr1(0x0001);  					//software reset
	//6）——————————设置扫描频率
	LCD_WriteAddr1(0x00E6);						//PLL setting for PCLK, depends on resolution
	LCD_WriteData1(0x0003);
	LCD_WriteData1(0x00FF);
	LCD_WriteData1(0x00FF);
	//7）——————————设置LCD面板模式 Set the LCD panel mode (RGB TFT or TTL)
	LCD_WriteAddr1(0x00B0);						//LCD SPECIFICATION
	LCD_WriteData1(0x0000);
	LCD_WriteData1(0x0000);
	LCD_WriteData1((799>>8)&0X00FF);  		//设置水平像素点个数高8位		Set HDP 
	LCD_WriteData1(799&0X00FF);					//设置水平像素点个数低8位
	LCD_WriteData1((479>>8)&0X00FF);  		//设置垂直像素点个数高8位		Set VDP
	LCD_WriteData1(479&0X00FF);					//设置垂直像素点个数低8位
	LCD_WriteData1(0x0000);									//设置奇偶行RGB顺序，默认0，Even line RGB sequence&Odd line RGB sequence
	//8）——————————设置水平期 Set Horizontal Period
	LCD_WriteAddr1(0x00B4);							//HSYNC
	LCD_WriteData1((928>>8)&0X00FF);  	//High byte of horizontal total period
	LCD_WriteData1(928&0X00FF);					//Low byte of the horizontal total period (display + non-display) in pixel clock (POR = 10101111)
																			//Horizontal total period = (HT + 1) pixels
	LCD_WriteData1((46>>8)&0X00FF);  	//High byte of the non-display period between the start of the horizontal sync (LLINE) signal and the first
																			//display data. (POR = 000)
	LCD_WriteData1(46&0X00FF);
	LCD_WriteData1(48);			   //Set HPW
	LCD_WriteData1((15>>8)&0X00FF);  //Set HPS
	LCD_WriteData1(15&0X00FF);
	LCD_WriteData1(0x0000);
	//9）——————————设置垂直期	Set Vertical Period
	LCD_WriteAddr1(0x00B6);							//VSYNC
	LCD_WriteData1((525>>8)&0X00FF);   //Set VT
	LCD_WriteData1(525&0X00FF);
	LCD_WriteData1((16>>8)&0X00FF);  //Set VPS
	LCD_WriteData1(16&0X00FF);
	LCD_WriteData1(16);			   //Set VPW
	LCD_WriteData1((8>>8)&0X00FF);  //Set FPS
	LCD_WriteData1(8&0X00FF);	
	//10）——————————配置GPIO
	LCD_WriteAddr1(0x00B8);
	LCD_WriteData1(0x0007);    //GPIO3=input, GPIO[2:0]=output //输出模式
	LCD_WriteData1(0x0001);   	//0 GPIO0 is used to control the panel power with Enter Sleep Mode 0x10 or Exit Sleep Mode 0x11.
													//1 GPIO0 is used as normal GPIO
	//11）——————————设置GPIO（设置扫描方向） Set GPIO value for GPIO configured as output
	LCD_WriteAddr1(0x00BA);
	LCD_WriteData1((0X05&0XFF)|(0X04&0XFF));    //GPIO[3:0] out 1
	//12）——————————设置地址模式	Set Address Mode
	LCD_WriteAddr1(0x0036); //rotation
	LCD_WriteData1(0x0000);
	//13）——————————设置数据接口 Set Pixel Data Interface/Pixel Data Interface Format
	LCD_WriteAddr1(0x00F0); //pixel data interface
	LCD_WriteData1(0x0003);
	
	//14）——————————设置垂直期
	LCD_WriteAddr1(0x0029); //display on
	//15）——————————设置垂直期
	LCD_WriteAddr1(0x00d0); 
	LCD_WriteData1(0x000D);
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
void LCDCLER(unsigned short color)
{
  unsigned  short i = 0,j=0;
  unsigned  short xs = 0,xe =800;
  unsigned  short ys = 0,ye =480;
  //======================================区域设置
	LCD_WriteAddr1(0x002A);			//设置列地址
	LCD_WriteData1(xs>>8);		//起始地址高8位
	LCD_WriteData1(xs);			//起始地址低8位
	LCD_WriteData1(xe>>8);		//结束地址高8位
	LCD_WriteData1(xe);			//行结束地址低8位
	
	LCD_WriteAddr1(0x002b);			//设置页地址	
	LCD_WriteData1(ys>>8);
	LCD_WriteData1(ys);
	LCD_WriteData1(ye>>8);
	LCD_WriteData1(ye);
	
	LCD_WriteAddr1(0x0036);			//设置页地址
	LCD_WriteData1(0XA0);       //显示模式

	LCD_WriteAddr1(0x002c);			//写内存起始地址 
  for(i=0;i<=(xe-xs);i++)
  {
    for(j=0;j<=(ye-ys);j++)
      LCD_WriteData1(color);
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
void ImageDisp(unsigned char* buffer,unsigned long len)
{
	unsigned  long i = 0;
  unsigned  short xs = 0,xe =800;
  unsigned  short ys = 0,ye =480;
	unsigned	short	P	=	0;
  //======================================区域设置
	LCD_WriteAddr1(0x002A);			//设置列地址
	LCD_WriteData1(xs>>8);		//起始地址高8位
	LCD_WriteData1(xs);			//起始地址低8位
	LCD_WriteData1(xe>>8);		//结束地址高8位
	LCD_WriteData1(xe);			//行结束地址低8位
	
	LCD_WriteAddr1(0x002b);			//设置页地址	
	LCD_WriteData1(ys>>8);
	LCD_WriteData1(ys);
	LCD_WriteData1(ye>>8);
	LCD_WriteData1(ye);
	
	LCD_WriteAddr1(0x0036);			//设置页地址
	LCD_WriteData1(0XA0);       //显示模式

	LCD_WriteAddr1(0x002c);			//写内存起始地址 
  for(i=0;i<=len;)
  {
		P=buffer[i];
		P=P<<8;
		P|=buffer[i+1];
      LCD_WriteData1(P);
			i+=2;
  }
}

#endif
