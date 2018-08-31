#ifdef MmcSDTest

#include "MmcSDTest.H"

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
//#include "MMC_SD.h"
#include "FatFsAPI.h"			/* 自定义API接口*/

//#include "STM32_SDCard.H"
//#include "GT32L32M0180.H"



//#define SDCardTest
//#define GT32L32M0180Test	
//


LCDDef	sLCD;
SPIDef	sSCport;

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

u8 bsr  = 0x08;

u16 time=0;
u32 ADCDATA = 0;
//void GT32L32_PinSet(void);
FATFS FatFsObj[1]; /* 逻辑驱动器的工作区(文件系统对象) */	
FIL fsrc, fdst; /* 文件对象 */
BYTE buffer[4096]; /* 文件拷贝缓冲区 */
FRESULT result; /* FatFs 函数公共结果代码 */
UINT br, bw; /* 文件读/写字节计数 */
u16 xh=0,yv=0;
//=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>
//->函数名		:	
//->功能描述	:	 
//->输入		:	
//->输出		:
//->返回 		:
//<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=
void MmcSDTest_Configuration(void)
{	
	SYS_Configuration();					//系统配置---打开系统时钟 STM32_SYS.H	
	GPIO_DeInitAll();							//将所有的GPIO关闭----V20170605	
  LCD_Configuration();
  SD_Configuration();
  USART_DMA_ConfigurationNR	(USART1,115200,128);	//USART_DMA配置--查询方式，不开中断
//  TM1618_PinSet();

//  res = f_open(&fsrc, "1:srcfile.dat", FA_OPEN_EXISTING | FA_READ);
  ADC_TempSensorConfiguration(&ADCDATA);								//STM32内部温度传感器配置
  LCD_ShowBattery(780,2,2,LCD565_GREEN);   //显示12x12电池
  LCD_ShowAntenna(760,2,3,LCD565_GREEN);   //显示12x12天线
  
  LCD_Printf (300,0,32,LCD565_GREEN,"图片显示测试");					//自定义printf串口DMA发送程序,后边的省略号就是可变参数
  
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
void MmcSDTest_Server(void)
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
unsigned short Clllb(unsigned char r,unsigned char g,unsigned char b)
{
  unsigned short temp = 0;
  r>>=3;      //取高5位
  temp+=r;
  temp<<=5;
  g>>=3;      //取高5位
  temp+=g;
  temp<<=6;
  b>>=3;      //取高5位
  temp+=b;
  return temp;
}
unsigned short Clll(unsigned char r,unsigned char g)
{
  unsigned short temp = 0;
  temp=r;
  temp<<=8;
  temp+=g;
  return temp;
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
  DIR dir;
  char FilSearchCount[10][13]={0,0};
  
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
    }
  }
  else
  {
    LCD_Printf (0,32,16,LCD565_GREEN,"驱动器注册失败");					//自定义printf串口DMA发送程序,后边的省略号就是可变参数
  }
  //========================查找指定文件
  LCD_Printf (0,96,16,LCD565_GREEN,"查找指定文件:bmp");					//自定义printf串口DMA发送程序,后边的省略号就是可变参数
  result  = FilSearch(&FatFsObj[0],&dir,"0:/","bmp",FilSearchCount);  //在指定路径下查找指定扩展名的文件，并记录在(*p)[13]数组中，注意最大记录条数
  if(0 != result)
  {
    unsigned short    i=0;
    unsigned short    j = 0;
    unsigned short    flg=0;

    unsigned short  xs,xe,ys,ye;
    xh=0;
    yv=0;
    LCD_Printf (0,112,16,LCD565_GREEN,"查找到bmp文件");					//自定义printf串口DMA发送程序,后边的省略号就是可变参数
    for(i=0;i<10;i++)
    {
      if(0  !=  FilSearchCount[i][0])
      {
        unsigned char k = 0;
        for(k=0;k<13;++k)
        {
          if(0  ==  FilSearchCount[i][k])
            break;
        }
        LCD_Show(0,128+i*16,16,LCD565_GREEN,k,FilSearchCount[i]);
      }
    }
    while(1)
    {
      //===============================图片1
      yv  = 0;
      flg = 0;
      result  = f_open(&fsrc,"0:/Game.bmp",FA_READ);
      if(result)
        return;
      for(i=0;i<480;i++)
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
      SysTick_DeleyS(3);					//SysTick延时nS
      //===============================图片2
      yv  = 0;
      flg = 0;
      i   = 0;
      result  = f_open(&fsrc,"0:/Ga1.bmp",FA_READ);
      if(result)
        return;
      for(i=0;i<480;i++)
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
      SysTick_DeleyS(3);					//SysTick延时nS
      //===============================图片3
      yv  = 0;
      flg = 0;
      i   = 0;
      result  = f_open(&fsrc,"0:/Ga2.bmp",FA_READ);
      if(result)
        return;
      for(i=0;i<480;i++)
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
      SysTick_DeleyS(3);					//SysTick延时nS
      //===============================图片4
      yv  = 0;
      flg = 0;
      i   = 0;
      result  = f_open(&fsrc,"0:/Ga3.bmp",FA_READ);
      if(result)
        return;
      for(i=0;i<480;i++)
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
      SysTick_DeleyS(3);					//SysTick延时nS
      //===============================图片5
      yv  = 0;
      flg = 0;
      i   = 0;
      result  = f_open(&fsrc,"0:/Ga4.bmp",FA_READ);
      if(result)
        return;
      for(i=0;i<480;i++)
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
      SysTick_DeleyS(3);					//SysTick延时nS
      //===============================图片5
      yv  = 0;
      flg = 0;
      i   = 0;
      result  = f_open(&fsrc,"0:/Ga5.bmp",FA_READ);
      if(result)
        return;
      for(i=0;i<480;i++)
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
      SysTick_DeleyS(3);					//SysTick延时nS
      //===============================图片5
      yv  = 0;
      flg = 0;
      i   = 0;
      result  = f_open(&fsrc,"0:/Ga6.bmp",FA_READ);
      if(result)
        return;
      for(i=0;i<480;i++)
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
      SysTick_DeleyS(3);					//SysTick延时nS
      //===============================图片5
      yv  = 0;
      flg = 0;
      i   = 0;
      result  = f_open(&fsrc,"0:/Ga7.bmp",FA_READ);
      if(result)
        return;
      for(i=0;i<480;i++)
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
      SysTick_DeleyS(3);					//SysTick延时nS
      //===============================图片5
      yv  = 0;
      flg = 0;
      i   = 0;
      result  = f_open(&fsrc,"0:/Ga8.bmp",FA_READ);
      if(result)
        return;
      for(i=0;i<480;i++)
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
      SysTick_DeleyS(3);					//SysTick延时nS
     
    }
    
  }
  else
  {    
    LCD_Printf (0,112,16,LCD565_GREEN,"未找到bmp文件");					//自定义printf串口DMA发送程序,后边的省略号就是可变参数    
  }
//  f_getfree();  

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
	SPI->Port.SPI_BaudRatePrescaler_x=SPI_BaudRatePrescaler_128;
	
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
