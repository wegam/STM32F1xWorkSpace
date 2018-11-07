/**************************************************************************************************
* 液晶屏驱动IC
* 文件<$(filename)>
* 模块描述 :	定义、功能、说明
* 历史修改记录
*     <主要修改者>  <时间>   <版本 >   <说明>
*     xlyan        $(Date)   1.0.0    创建文件
**************************************************************************************************/
#include "LCD.H"

#include "stm32f10x_fsmc.h"

#include "STM32_GPIO.H"
#include "STM32_PWM.H"
#include "STM32_SYSTICK.H"
#include "font.h"
#include "string.h"				//串和内存操作函数头文件
#include "stdlib.h"				//串和内存操作函数头文件
#include "stdarg.h"				//串和内存操作函数头文件
#include "stdio.h"				//串和内存操作函数头文件

#include "R61509V.h"
#include "ILI9326.h"
#include "SSD1963.H"

LCDDef 			*LCDSYS	=	NULL;	//内部驱动使用，不可删除
unsigned short PenColor		=	0;		//画笔颜色
unsigned short BackColor	=	0;		//背景颜色
unsigned short VAsize	=	0;		//输入大小
/*******************************************************************************
*函数名			:	LCD_Initialize
*功能描述		:	LCD初始化：
*输入				: 
*返回值			:	无
*******************************************************************************/
void LCD_Initialize(LCDDef *pInfo)
{
	static unsigned short	DeviceCode	=	0;
	
  LCDPortDef  *Port;
	LCDSYS	  =	pInfo;		//指针指向
  
  Port	=	&(pInfo->Port);	
	
	//==========================GPIO配置
	GPIO_Configuration_OPP50	(Port->sBL_PORT,				Port->sBL_Pin);					//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度2MHz----V20170605
	GPIO_Configuration_OPP50	(Port->sRD_PORT,				Port->sRD_Pin);					//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度2MHz----V20170605
	GPIO_Configuration_OPP50	(Port->sREST_PORT,			Port->sREST_Pin);				//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度2MHz----V20170605
	GPIO_Configuration_OPP50	(Port->sDC_PORT,				Port->sDC_Pin);					//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度2MHz----V20170605
	GPIO_Configuration_OPP50	(Port->sWR_PORT,				Port->sWR_Pin);					//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度2MHz----V20170605
	GPIO_Configuration_OPP50	(Port->sCS_PORT,				Port->sCS_Pin);					//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度2MHz----V20170605
	GPIO_Configuration_OPP50	(Port->sTE_PORT,				Port->sTE_Pin);					//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度2MHz----V20170605
	GPIO_Configuration_OPP50	(Port->sDATABUS_PORT,		Port->sDATABUS_Pin);		//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度2MHz----V20170605
	//===========================函数地址
  LCDSYS->Display.WriteIndex    = LCD_WriteIndex;
  LCDSYS->Display.WriteData     = LCD_WriteData;
  LCDSYS->Display.WriteCommand  = LCD_WriteCommand;
	//==========================驱动芯片检测
	LCD_Reset();
	DeviceCode	=	LCD_ReadData(LCD_R000_IR);
	
	if(R61509ID	==	DeviceCode)
	{
		R61509V_Initialize(pInfo);
	}
	else if(ILI9326ID	==	DeviceCode)
	{
		ILI9326_Initialize(pInfo);
	}
	else
	{
    SSD1963_Initialize(pInfo);
	}
  //==========================检查背景色与画笔色是否相同
	if(pInfo->Data.PColor	==	pInfo->Data.BColor)
	{
		pInfo->Data.PColor	=	pInfo->Data.BColor^0xFF;
	}
  
	//==========================LCD初始化及上电配置
	LCDSYS->Display.PowerOn();						//LCD上电/初始化配置
	//==========================以背景色清除屏幕
	LCD_Clean(pInfo->Data.BColor);				//按背景色清除屏幕函数
	//==========================开背光
	LCD_BL_ON;
	//==========================字库配置
	GT32L32_Initialize(&pInfo->GT32L32.SPI);				//普通SPI通讯方式配置
}
/*******************************************************************************
*函数名			:	LCD_Initialize
*功能描述		:	LCD初始化：
*输入				: 
*返回值			:	无
*******************************************************************************/
void LCDFsmc_Initialize(LCDDef *pInfo)
{
  
  
	static unsigned short	DeviceCode	=	0;
  GPIO_InitTypeDef                GPIO_InitStructure;
	FSMC_NORSRAMInitTypeDef         FSMC_NORSRAMInitStructure;
  FSMC_NORSRAMTimingInitTypeDef   FSMC_NORSRAMTimingInitStructure;
  
  LCDPortDef  *Port;
	LCDSYS	  =	pInfo;		//指针指向
  
  Port	=	&(pInfo->Port);	
	
	//==========================开时钟
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |RCC_APB2Periph_GPIOB |RCC_APB2Periph_GPIOC |RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE | RCC_APB2Periph_GPIOF | RCC_APB2Periph_GPIOG | RCC_APB2Periph_AFIO, ENABLE);
  //==========================GPIO配置
  if(NULL!= Port->sBL_PORT)
    GPIO_Configuration_OPP50	(Port->sBL_PORT,				Port->sBL_Pin);					//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度2MHz----V20170605
  if(NULL!= Port->sREST_PORT)
    GPIO_Configuration_OPP50	(Port->sREST_PORT,			Port->sREST_Pin);				//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度2MHz----V20170605
  if(NULL!= Port->sCS_PORT)
    GPIO_Configuration_OPP50	(Port->sCS_PORT,				Port->sCS_Pin);					//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度2MHz----V20170605
  //-----------------打开FSMC的数据端口D[15:0]
  GPIO_Configuration_APP50(GPIOD,GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_14 | GPIO_Pin_15);
  GPIO_Configuration_APP50(GPIOE,GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 |  GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
  //-----------------打开FSMC功能端口，PD.4=RD(nOE)；PD.5=WR(nWE)
  GPIO_Configuration_APP50(GPIOD,GPIO_Pin_4 | GPIO_Pin_5);
  //-----------------打开NE4设置
  GPIO_Configuration_APP50(GPIOG,GPIO_Pin_12);
  //-----------------打开RS设置
  GPIO_Configuration_APP50(GPIOE,GPIO_Pin_3);
  
  //==========================初始化GPIO状态
  //--------------NE4=1
  GPIO_SetBits(GPIOG, GPIO_Pin_12);
  //--------------LCD_RESET=0
  GPIO_ResetBits(GPIOE, GPIO_Pin_1);
  //--------------LCD_RD=1(nOE)
  GPIO_SetBits(GPIOD, GPIO_Pin_4);
  //--------------LCD_WR=1(nWE)
  GPIO_SetBits(GPIOD, GPIO_Pin_5);
  //--------------NE4=0
  GPIO_ResetBits(GPIOG, GPIO_Pin_12);
  SysTick_DeleymS(100); 
  
  //===========================FSMC初始化
  
  /*-- FSMC Configuration ------------------------------------------------------*/
  /*----------------------- SRAM Bank 4 ----------------------------------------*/
  /* FSMC_Bank1_NORSRAM4 configuration */
  FSMC_NORSRAMTimingInitStructure.FSMC_AddressSetupTime = 1;
  FSMC_NORSRAMTimingInitStructure.FSMC_AddressHoldTime = 0;
  FSMC_NORSRAMTimingInitStructure.FSMC_DataSetupTime = 2;
  FSMC_NORSRAMTimingInitStructure.FSMC_BusTurnAroundDuration = 0;
  FSMC_NORSRAMTimingInitStructure.FSMC_CLKDivision = 0;
  FSMC_NORSRAMTimingInitStructure.FSMC_DataLatency = 0;
  FSMC_NORSRAMTimingInitStructure.FSMC_AccessMode = FSMC_AccessMode_B;

  /* Color LCD configuration ------------------------------------
     LCD configured as follow:
        - Data/Address MUX = Disable
        - Memory Type = SRAM
        - Data Width = 16bit
        - Write Operation = Enable
        - Extended Mode = Enable
        - Asynchronous Wait = Disable */
  FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM4;
  FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable;
  FSMC_NORSRAMInitStructure.FSMC_MemoryType = FSMC_MemoryType_SRAM;
  FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;
  FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode = FSMC_BurstAccessMode_Disable;
  FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
  FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable;
  FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;
  FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable;
  FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable;
  FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Disable;
  FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable;
  FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &FSMC_NORSRAMTimingInitStructure;
  FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &FSMC_NORSRAMTimingInitStructure;

  FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure);

  /* - BANK 3 (of NOR/SRAM Bank 0~3) is enabled */
  FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM4, ENABLE);  
  
//	GPIO_Configuration_OPP50	(Port->sRD_PORT,				Port->sRD_Pin);					//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度2MHz----V20170605
//	GPIO_Configuration_OPP50	(Port->sREST_PORT,			Port->sREST_Pin);				//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度2MHz----V20170605
//	GPIO_Configuration_OPP50	(Port->sDC_PORT,				Port->sDC_Pin);					//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度2MHz----V20170605
//	GPIO_Configuration_OPP50	(Port->sWR_PORT,				Port->sWR_Pin);					//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度2MHz----V20170605	
//	GPIO_Configuration_OPP50	(Port->sTE_PORT,				Port->sTE_Pin);					//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度2MHz----V20170605
//	GPIO_Configuration_OPP50	(Port->sDATABUS_PORT,		Port->sDATABUS_Pin);		//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度2MHz----V20170605
	
  //===========================函数地址
  LCDSYS->Display.WriteIndex    = LCDFsmc_WriteIndex;
  LCDSYS->Display.WriteData     = LCDFsmc_WriteData;
  LCDSYS->Display.WriteCommand  = LCDFsmc_WriteCommand;
  //==========================驱动配置
  SSD1963_Initialize(pInfo);

  //==========================检查背景色与画笔色是否相同
	if(pInfo->Data.PColor	==	pInfo->Data.BColor)
	{
		pInfo->Data.PColor	=	pInfo->Data.BColor^0xFF;
	}
	//==========================LCD初始化及上电配置
	LCDSYS->Display.PowerOn();						//LCD上电/初始化配置
	//==========================以背景色清除屏幕
//	LCD_Clean(pInfo->Data.BColor);				//按背景色清除屏幕函数
  LCD_Clean(LCD565_WHITE);				//按背景色清除屏幕函数
	//==========================开背光LIGHT=1
  GPIO_SetBits(Port->sBL_PORT, Port->sBL_Pin);
	//==========================字库配置
	GT32L32_Initialize(&pInfo->GT32L32.SPI);				//普通SPI通讯方式配置
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
void LCD_Reset(void)
{
	LCD_RST_HIGH;
	LCD_DelaymS(10);				//SysTick延时nmS
	LCD_RST_LOW;
	LCD_DelaymS(10);				//SysTick延时nmS
	LCD_RST_HIGH;
	LCD_DelaymS(10);				//SysTick延时nmS
}
/**************************************************************************************************
* [Function] R61509V_DispOff:  关闭R61509V显示( 黑屏?)
* [No param]
**************************************************************************************************/
void LCD_WriteIndexStart( void )
{
	LCD_CS_LOW; 	//片选信号 0:片选;1:失能;
	LCD_DC_LOW; 	//命令/数据：0：命令;1-数据
	LCD_RD_HIGH;	//读信号;0:读数据
}
/**************************************************************************************************
* [Function] R61509V_DispOff:  关闭R61509V显示( 黑屏?)
* [No param]
**************************************************************************************************/
void LCD_WriteIndexEnd( void )
{
	LCD_CS_HIGH;	//片选信号 0:片选;1:失能;
}
/**************************************************************************************************
* [Function] R61509V_DispOff:  关闭R61509V显示( 黑屏?)
* [No param]
**************************************************************************************************/
void LCD_WriteIndex( unsigned short Index )
{
	LCD_CS_LOW; 	//片选信号 0:片选;1:失能;
	LCD_DC_LOW; 	//命令/数据：0：命令;1-数据
	LCD_WriteData(Index);
	LCD_DC_HIGH; 	//命令/数据：0：命令;1-数据
}
/**************************************************************************************************
* [Function] R61509V_DispOff:  关闭R61509V显示( 黑屏?)
* [No param]
**************************************************************************************************/
void LCD_WriteDataStart( void )
{
	LCD_CS_LOW; 	//片选信号 0:片选;1:失能;
	LCD_DC_HIGH; 	//命令/数据：0：命令;1-数据
	LCD_RD_HIGH;	//读信号;0:读数据
}
/**************************************************************************************************
* [Function] R61509V_DispOff:  关闭R61509V显示( 黑屏?)
* [No param]
**************************************************************************************************/
void LCD_WriteDataEnd( void )
{
	LCD_DC_LOW; 	//数据
	LCD_CS_HIGH;
}

#if 1
/*******************************************************************************
* 函数名			:	R61509V_WriteData
* 功能描述		:	写16位数据
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
void LCD_WriteData(u16 Data)
{
	LCD_WR_LOW;
	LCD_DATABUS_PORT->ODR = Data;		
	LCD_WR_HIGH;
}
/**************************************************************************************************
* [Function] R61509V_ReadData:  从R61509V读取数据
* [No param][return]u16: 返回数据
**************************************************************************************************/
u16 LCD_ReadData( unsigned short Index )
{
	u16 Data;
	
	GPIO_Configuration_OPP50	(LCD_DATABUS_PORT,LCD_DATABUS_Pin);		//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度2MHz----V20170605
	
	//==================写地址
	LCD_RD_HIGH;
	LCD_CS_LOW;
	LCD_RS_LOW;
	LCD_WR_LOW;
	LCD_DATABUS_PORT->ODR = Index;
	LCD_WR_HIGH;
	LCD_RS_HIGH;
	LCD_DelaymS(10);
	GPIO_Configuration_IPU	(LCD_DATABUS_PORT,LCD_DATABUS_Pin);			//将GPIO相应管脚配置为上拉输入模式----V20170605
  
	LCD_RD_LOW;
  LCD_DelaymS(10);
	Data = LCD_DATABUS_PORT->IDR;
	LCD_RD_HIGH;
	LCD_CS_HIGH;
	
	GPIO_Configuration_OPP50	(LCD_DATABUS_PORT,LCD_DATABUS_Pin);		//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度2MHz----V20170605
	return Data;	
}
#else
/*******************************************************************************
* 函数名			:	R61509V_WriteData
* 功能描述		:	写8位数据
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
void LCD_WriteData(u16 Data)
{
	LCD_WR_LOW;
	LCD_DATABUS_PORT->ODR = Data>>8;		
	LCD_WR_HIGH;
	
	LCD_WR_LOW;
	LCD_DATABUS_PORT->ODR = Data;		
	LCD_WR_HIGH;
}
#endif
/*******************************************************************************
*函数名			:	R61509V_WriteCommand
*功能描述		:	写完整控制命令
*输入				: 
*返回值			:	无
*******************************************************************************/
void LCD_WriteCommand(												  //写完整控制命令
											unsigned short Index,			//寄存器索引
											unsigned short Command		//命令
											)	//写完整控制命令
{
	//==================写地址
//	LCD_WriteIndexStart();	
//	LCD_WriteData(Index);
//	LCD_WriteIndexEnd();
  LCDSYS->Display.WriteIndex(Index);
	
	//==================写数据
//	LCD_WriteDataStart();
//	LCD_WriteData(Command);
//	LCD_WriteDataEnd();
  LCDSYS->Display.WriteData(Command);
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
void LCDFsmc_WriteIndex(unsigned short Index)
{  
  *(volatile unsigned short*)(LCDSYS->Data.FsmcRegAddr)  = Index;
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
void LCDFsmc_WriteData(unsigned short Data)
{  
  *(volatile unsigned short*)(LCDSYS->Data.FsmcDataAddr)  = Data;
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
void LCDFsmc_WriteCommand(										  //写完整控制命令
											unsigned short Index,			//寄存器索引
											unsigned short Command		//命令
											)	//写完整控制命令
{
  LCDFsmc_WriteIndex(Index);
  LCDFsmc_WriteData(Command);
}



/*******************************************************************************
*函数名			:	LCD_Clean
*功能描述		:	清屏程序：清除屏幕函数---用背景色填充屏幕
*输入				: 
*返回值			:	无
*******************************************************************************/
void LCD_Clean(u16 Color)	//清除屏幕函数
{
	unsigned short x,y;
	unsigned short HSX,HEX,HSY,HEY,MaxH,MaxV;
	eRotate	Rotate	=	LCDSYS->Flag.Rotate;
	
	MaxH	=	LCDSYS->Data.MaxH;
	MaxV	=	LCDSYS->Data.MaxV;
	
	switch(Rotate)
	{
		case 	Draw_Rotate_0D:
					HSX	=	0;
					HEX	=	MaxH-1;
					HSY	=	0;
					HEY	=	MaxV-1;
			break;
		case	Draw_Rotate_90D:
					HSX	=	0;
					HEX	=	MaxV-1;
					HSY	=	0;
					HEY	=	MaxH-1;
			break;
		case	Draw_Rotate_180D:
					HSX	=	0;
					HEX	=	MaxH-1;
					HSY	=	0;
					HEY	=	MaxV-1;
			break;
		default:
					HSX	=	0;
					HEX	=	MaxV-1;
					HSY	=	0;
					HEY	=	MaxH-1;
			break;			
	}
	LCDSYS->Display.WriteAddress(HSX,HSY,HEX,HEY);		//写入地址区域
//	LCD_WriteDataStart();									//写数据使能	
	for(x=0;x<MaxH;x++)
	{
		for(y=0;y<MaxV;y++)
		{
			LCDSYS->Display.WriteData(Color);							//写数据
		}
	}	
//	LCD_WriteDataEnd();										//写数据完成
}

/*******************************************************************************
*函数名			:	LCD_DrawPoint
*功能描述		:	画点
*输入				: 
*返回值			:	无
*******************************************************************************/
void LCD_DrawDot(
									unsigned short HSX,			//点X坐标*/
									unsigned short HSY,			//点Y坐标*/
									unsigned short Color		//点颜色*/	
								)
{
	LCDSYS->Display.WriteAddress(HSX,HSY,HSX,HSY);	//设置光标位置
  LCDSYS->Display.WriteData(Color);
//	LCD_WriteDataStart();
//	LCD_WriteData(Color); 	//笔画颜色
//	LCD_WriteDataEnd();
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
void LCD_DrawLine(
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
	
	for(t=0;t<distance+1;t++ )					//画线输出 
	{  
		LCD_DrawDot(uRow,uCol,Color);			//画点 
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
}
/**************************************************************************************************
* [Function] LCD_DrawCircle:  函数功能、注意事项等的描述
* [param01]t_Point point: description
* [param02]u16 R: description
* [param03]uint8_t Filled: description
* [param04]u16 color: description
**************************************************************************************************/
void LCD_DrawCircle(
												u16 x,u16 y,		//圆心坐标原点
												u16 r,					//半径
												u8 Filled,			//是否填充
												u16 color				//颜色
												)
{
	int a,b;
	int di;
	
//	void ( *DSPDrawDot )(unsigned short HSX,unsigned short HSY,unsigned short Color);
//	void ( *DSPDrawLine )( unsigned short HSX,unsigned short HSY,unsigned short HEX,unsigned short HEY,unsigned short Color);
//	DSPDrawDot	=	LcdDisplay.DSPDrawDot;
//	DSPDrawLine	=	LcdDisplay.DSPDrawLine;
	
	a=0;b=r;	  
	di=3-(r<<1);             //判断下个点位置的标志
	while(a<=b)
	{
		if(Filled)	//填充就画线
		{
			LCD_DrawLine(x,y,x-b,y-a,color);             //3           
			LCD_DrawLine(x,y,x+b,y-a,color);             //0           
			LCD_DrawLine(x,y,x-a,y+b,color);             //1       
			LCD_DrawLine(x,y,x-b,y-a,color);             //7           
			LCD_DrawLine(x,y,x-a,y-b,color);             //2             
			LCD_DrawLine(x,y,x+b,y+a,color);             //4               
			LCD_DrawLine(x,y,x+a,y-b,color);             //5
			LCD_DrawLine(x,y,x+a,y+b,color);             //6 
			LCD_DrawLine(x,y,x-b,y+a,color);             
			a++;
			//使用Bresenham算法画圆     
			if(di<0)
				di +=4*a+6;	  
			else
			{
				di+=10+4*(a-b);   
				b--;
			}
			LCD_DrawLine(x,y,x+a,y+b,color);				//AB 两个坐标画一条直线
		}
		else
		{
			LCD_DrawDot(x-b,y-a,color);             //3           
			LCD_DrawDot(x+b,y-a,color);             //0           
			LCD_DrawDot(x-a,y+b,color);             //1       
			LCD_DrawDot(x-b,y-a,color);             //7           
			LCD_DrawDot(x-a,y-b,color);             //2             
			LCD_DrawDot(x+b,y+a,color);             //4               
			LCD_DrawDot(x+a,y-b,color);             //5
			LCD_DrawDot(x+a,y+b,color);             //6 
			LCD_DrawDot(x-b,y+a,color);             
			a++;
			//使用Bresenham算法画圆     
			if(di<0)
				di +=4*a+6;	  
			else
			{
				di+=10+4*(a-b);   
				b--;
			}
				LCD_DrawDot(x+a,y+b,color);
		}
	}
}
/**************************************************************************************************
* [Function] LCD_DrawRectangle:  画一下矩形框
* [param01]t_Point top_p: 顶点坐标值
* [param02]t_Point botton_p : 地板坐标值
**************************************************************************************************/
void LCD_DrawRectangle(u16 x1,u16 y1,u16 x2,u16 y2,u16 color)
{
	LCD_DrawLine( x1, y1,	x1,	y2, color );
	LCD_DrawLine( x1, y1,	x2,	y1, color );
	LCD_DrawLine( x2, y1,	x2,	y2, color );
	LCD_DrawLine( x1, y2,	x2,	y2, color );
}
/*******************************************************************************
*函数名			:	LCD_DrawPoint_big
*功能描述		:	在指定区域内填充指定颜色;区域大小:(xend-xsta)*(yend-ysta)
*输入				: 
*返回值			:	无
*******************************************************************************/
void LCD_Fill(
							unsigned short x1, unsigned short y1, 	//x1,y1:起点坐标
							unsigned short x2, unsigned short y2,		//x2,y2:终点坐标
							u16 color
)
{          
	unsigned int i;
	unsigned int j;	
	LCDSYS->Display.WriteAddress(x1,y1,x2,y2);
//	LCD_WriteDataStart();
	for(i=0;i<=x2-x1;i++)
	{
		for(j=0;j<=y2-y1;j++)
		{
			LCDSYS->Display.WriteData(color);
		}
	}
//	LCD_WriteDataEnd();	
}
/**************************************************************************************************
* [Function] R61509V_Setbackground:  设置背景颜色
* [param01]u16 BackColor: 背景颜色值
**************************************************************************************************/
void LCD_SetBackground(  u16 BackColor )
{
	LCD_Clean(BackColor);	//清除屏幕函数
}
/*******************************************************************************
* 函数名			:	LCD_ShowAntenna
* 功能描述		:	显示12x12天线 
* 输入			: Num 01234带表天线信号强度。
* 返回值			: void
*******************************************************************************/
void LCD_ShowAntenna(
                    u16 x,			//x				:起点x坐标
										u16 y,			//y				:起点y坐标
                    u8 Num,
										u16 PenColor)
{	
  unsigned char GetBufferLength	=	0;
  unsigned char CodeBuffer[32]={0};
  if(Num>4)
  {
    Num=4;
  }
  GetBufferLength = GT32L32_GetAntennaCode(Num,CodeBuffer);
//	LCD_Show(x,y,12,GetBufferLength,CodeBuffer);
	LCD_ShowWord(x,y,12,PenColor,GetBufferLength,CodeBuffer);
}
/*******************************************************************************
* 函数名			:	LCD_ShowBattery
* 功能描述		:	显示12x12电池 
* 输入			: Num 01234带表电池电量。
* 返回值			: void
*******************************************************************************/
void LCD_ShowBattery(
                    u16 x,			//x				:起点x坐标
										u16 y,			//y				:起点y坐标
                    u8 Num,
										u16 PenColor)
{
  unsigned char GetBufferLength	=	0;
  unsigned char CodeBuffer[64]={0};
  if(Num>3)
  {
    Num=3;
  }
  GetBufferLength = GT32L32_GetBatteryCode(Num,CodeBuffer);
	LCD_ShowWord(x,y,12,PenColor,GetBufferLength,CodeBuffer);
}
/*******************************************************************************
* 函数名			:	function
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
*******************************************************************************/
void LCD_ShowChar(
										u16 x,			//x				:起点x坐标
										u16 y,			//y				:起点y坐标
										u8 font,		//font		:字体大小
										u16 color,	//字体颜色
										u8 num,			//num			:字节数
										u8 *Buffer	//Buffer	:显示的内容缓存
										
)		//高通字库测试程序
{
	u8 temp;
	u8 i=0,j=0;
	unsigned short x1=0,x2=0,y1=0,y2=0;
	unsigned short LCD_PEN_COLOR	=	LCDSYS->Data.PColor;   	//画笔色
	x1	=	x;
	y1	=	y;
//  if(x>LCDSYS->Data.MaxV-font||y>LCDSYS->Data.MaxH-font)
//			return;
    x2	=	x+font/2-1;
    y2	=	y+font-1;
	LCDSYS->Display.WriteAddress(x1,y1,x2,y2);//设置显示区域
	i=0;
//	LCD_WriteDataStart();
	for(i=0;i<num;i++)
	{ 
		temp=Buffer[i];		 					//调用1608字体--二维数组形式--字库使用时取消
		for(j=0;j<8;j++)
		{
			if((temp&0x80)==0X80)
			{
				LCD_PEN_COLOR=color;
			}
			else
				LCD_PEN_COLOR=LCDSYS->Data.BColor;
			LCDSYS->Display.WriteData(LCD_PEN_COLOR);
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
          LCD_PEN_COLOR=color;
        }
        else
          LCD_PEN_COLOR=LCDSYS->Data.BColor;
        LCDSYS->Display.WriteData(LCD_PEN_COLOR);
        temp=temp<<1;
      }
      i++;
    }		
	}
//	LCD_WriteDataEnd();	
}
/*******************************************************************************
* 函数名			:	function
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
*******************************************************************************/
void LCD_ShowWord(
										u16 x,			//x				:起点x坐标
										u16 y,			//y				:起点y坐标
										u8 font,		//font		:字体大小
										u16 color,	//字体颜色
										u8 num,			//num			:字节数
										u8 *Buffer	//Buffer	:显示的内容缓存
										
)		//高通字库测试程序
{
	u8 temp;
	u8 i=0,j=0;
	unsigned short x1=0,x2=0,y1=0,y2=0;
//	unsigned short LCD_PEN_COLOR	=	LCDSYS->Data.PColor;   	//画笔色
	x1	=	x;
	y1	=	y;
  
//  if(x>LCDSYS->Data.MaxH-font||y>LCDSYS->Data.MaxV-font)
//    return;
  x2	=	x+font-1;
  y2	=	y+font-1;
	LCDSYS->Display.WriteAddress(x1,y1,x2,y2);//设置显示区域
//	LCD_WriteDataStart();
	for(i=0;i<num;i++)
	{ 
		u16 LCD_PEN_COLOR	=	LCDSYS->Data.PColor;   	//画笔色	
		temp=Buffer[i];		 				
		for(j=0;j<8;j++)
		{
			if((temp&0x80)==0X80)
			{
				LCD_PEN_COLOR=color;
			}
			else
				LCD_PEN_COLOR=LCDSYS->Data.BColor;
			LCDSYS->Display.WriteData(LCD_PEN_COLOR);
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
          LCD_PEN_COLOR=color;
        }
        else
          LCD_PEN_COLOR=LCDSYS->Data.BColor;
        LCDSYS->Display.WriteData(LCD_PEN_COLOR);
        temp=temp<<1;
      }
      i++;
    }			
	}
//	LCD_WriteDataEnd();
}

/*******************************************************************************
* 函数名			:	function
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
*******************************************************************************/
void LCD_Show(
							u16 x,			//x				:起点x坐标
							u16 y,			//y				:起点y坐标
							u8 font,		//font		:字体大小
							u16 PenColor,//字体颜色
							u8 num,			//num			:字节数
							u8 *Buffer	//Buffer	:显示的内容缓存
)		//高通字库测试程序
{
	unsigned short	MaxV,MaxH;	//边界值
	unsigned char i=0;
	unsigned char CodeBuffer[130]={0};
	switch(LCDSYS->Flag.Rotate)
	{
		case Draw_Rotate_90D:
			MaxV	=	LCDSYS->Data.MaxH;
			MaxH	=	LCDSYS->Data.MaxV;
			break;
		case Draw_Rotate_180D:
			MaxV	=	LCDSYS->Data.MaxV;
			MaxH	=	LCDSYS->Data.MaxH;
			break;
		case Draw_Rotate_270D:
			MaxV	=	LCDSYS->Data.MaxH;
			MaxH	=	LCDSYS->Data.MaxV;
			break;
		default:
			MaxV	=	LCDSYS->Data.MaxV;
			MaxH	=	LCDSYS->Data.MaxH;
			break;
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
			GetBufferLength	=	GT32L32_ReadCode(font,word,CodeBuffer);		//从字库中读数据并返回数据长度
			//A4=====================写入屏幕
			LCD_ShowWord(x,y,font,PenColor,GetBufferLength,CodeBuffer);
			//A5=====================水平显示地址增加
      x+=font;
			i++;		//双字节，减两次
			
		}
		//B=====================单字节--ASCII字符集
		else
		{			
			//B1=====================显示超限换行
      if(x>MaxH-font/2)
      {
        x=0;
        y+=12;
      }
      //B2=====================显示到屏尾，从原点开始
      if(y>MaxV-font)
      {
        y=x=0;
      }
      //B3=====================读取点阵数据
			GetBufferLength	=	GT32L32_ReadCode(font,(u16)dst,CodeBuffer);		//从字库中读数据并返回数据长度
			//=======================水平制表符按空格显示(部分字库会当0xFF输出)
			if(	('	'	==	(char)dst)		//水平制表符
				||(' '	==	(char)dst))		//空格
			{
				memset(CodeBuffer,0x00,GetBufferLength);
			}
			//B4=====================写入屏幕
			LCD_ShowChar(x,y,font,PenColor,GetBufferLength,CodeBuffer);
			//B5=====================水平显示地址增加
      x+=font/2;						
		}
	}
}
/*******************************************************************************
* 函数名			:	LCD_ShowHex
* 功能描述		:	十六进制显示 
* 输入			: void
* 返回值			: void
*******************************************************************************/
void LCD_ShowHex(
							u16 x,			//x				:起点x坐标
							u16 y,			//y				:起点y坐标
							u8 font,		//font		:字体大小
							u16 color,	///字体颜色
							u8 num,			//num			:数据个数
              u8 bitnum,  //num			:位数
							u8 *Buffer	//Buffer	:显示的内容缓存
)		//高通字库测试程序
{
	unsigned short	MaxV,MaxH;	//边界值
	unsigned char i=0;
  unsigned char Cril  = 0;
	unsigned char CodeBuffer[130]={0};

  
	switch(LCDSYS->Flag.Rotate)
	{
		case Draw_Rotate_90D:
			MaxV	=	LCDSYS->Data.MaxH;
			MaxH	=	LCDSYS->Data.MaxV;
			break;
		case Draw_Rotate_180D:
			MaxV	=	LCDSYS->Data.MaxV;
			MaxH	=	LCDSYS->Data.MaxH;
			break;
		case Draw_Rotate_270D:
			MaxV	=	LCDSYS->Data.MaxH;
			MaxH	=	LCDSYS->Data.MaxV;
			break;
		default:
			MaxV	=	LCDSYS->Data.MaxV;
			MaxH	=	LCDSYS->Data.MaxH;
			break;
	}
	for(i=0;i<num;i++)
	{
    unsigned char GetBufferLength	=	0;
    for(Cril=bitnum/4;Cril>0;Cril--)
    {
      //=============================8位显示方式      
      unsigned char dst=(((u32)Buffer[i]>>(Cril-1)*4)&0x0F);
      //1=====================转换为ASSIC码
      if(dst<=9)
      {
        dst+=0x30;
      }
      else if((10<=dst)&&(15>=dst))
      {
        dst+=0x37;
      }
      //1=====================显示超限换行
      if(x>MaxH-font/2)
      {
        x=0;
        y+=font;
      }
      //2=====================显示到屏尾，从原点开始
      if(y>MaxV-font)
      {
        y=x=0;
      }
      //3=====================读取点阵数据
      GetBufferLength	=	GT32L32_ReadCode(font,dst,CodeBuffer);		//从字库中读数据并返回数据长度
      //4=====================写入屏幕
      LCD_ShowChar(x,y,font,color,GetBufferLength,CodeBuffer);
      //5=====================显示地址增加
      x+=font/2;
    }
    //5=====================显示地址增加(增加空格位)
    x+=font/2;
		if(x>MaxH-font)
		{
			y+=font;
			x=0;
		}
	}
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
unsigned int LCD_Printf(u16 x,u16 y,u8 font,u16 color,const char *format,...)				//后边的省略号就是可变参数
{ 
		
//		va_list ap; 										//VA_LIST 是在C语言中解决变参问题的一组宏，所在头文件：#include <stdarg.h>,用于获取不确定个数的参数
//		static char string[ 256 ];			//定义数组，
//  	va_start( ap, format );
//		vsprintf( string , format, ap );    
//		va_end( ap );
	
	char	DataBuffer[256]={0};			//记录format内码
	//1)**********获取数据宽度
  u16 InputDataSize=0;		//获取数据宽度	
	//3)**********args为定义的一个指向可变参数的变量，va_list以及下边要用到的va_start,va_end都是是在定义，可变参数函数中必须要用到宏， 在stdarg.h头文件中定义
	va_list args; 
	//5)**********初始化args的函数，使其指向可变参数的第一个参数，format是可变参数的前一个参数
	va_start(args, format);
	//6)**********正常情况下返回生成字串的长度(除去\0),错误情况返回负值
	InputDataSize = vsnprintf(DataBuffer, InputDataSize,format, args);

	//7)**********结束可变参数的获取
	va_end(args);                                      		
  if((12!=font)&&(16!=font)&&(24!=font)&&(32!=font))
  {
    font  = 24;
  }
	LCD_Show(x,y,font,color,InputDataSize,(unsigned char*)DataBuffer);
	return InputDataSize;
}
/*******************************************************************************
* 函数名			:	LCD_ShowHex
* 功能描述		:	十六进制显示 
* 输入			: void
* 返回值			: void
*******************************************************************************/
void LCD_ShowBMP(
							unsigned short x1, unsigned short y1, 	//x1,y1:起点坐标
							unsigned short x2, unsigned short y2,		//x2,y2:终点坐标
							u16 Length,   
              u8 *RGBBuffer     //RGB888数据地址，传入顺序为BGR，就是第一字节为B
)		//高通字库测试程序
{
	unsigned short i = 0;
  unsigned short j = 0;
  unsigned short  RGB565;
  eRotate Rotate = LCDSYS->Flag.Rotate;
  LCDSYS->Flag.Rotate  = Draw_Rotate_0D;		//使用旋转角度
  LCDSYS->Display.WriteAddress(x1,y1,x2,y2);//设置显示区域
//  LCD_WriteDataStart();
	for(i=0;i<Length;)
	{
//    RGB565  =   (RGBBuffer[j+2]>>3);
//    RGB565  <<= 5;
//    RGB565  |=  (RGBBuffer[j+1]>>3);		//取5位
//    RGB565  <<= 6;
//    RGB565  |=  (RGBBuffer[j+0]>>3);
//    LCD_WriteData(RGB565);
//    j+=3;
//    i+=3;
    RGB565  = RGB888toRGB565(&RGBBuffer[i]);
    LCDSYS->Display.WriteData(RGB565);
    i+=3;
	}
//  LCD_WriteDataEnd();
  LCDSYS->Flag.Rotate  =  Rotate;
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
unsigned  short RGB888toRGB565(u8 *RGB888)
{
  unsigned  short RGB565  = 0;
  //-----------------Red:取5位
  RGB565  = RGB888[2]>>3;
  RGB565<<=5;
  //-----------------Green：取5位
  RGB565  |= RGB888[1]>>3;
  RGB565<<=6;
  //-----------------Blue：取5位
  RGB565  |= RGB888[0]>>3;

  return  RGB565;
}

/**************************************************************************************************
* [Function] LCD_DrawPixelEx:  函数功能、注意事项等的描述
* [param01]u16 x: description
* [param02]u16 y: description
* [param03]u16 color: description
**************************************************************************************************/
void LCD_DrawPixelEx( u16 x, u16 y, u16 color )
{
	LCD_DrawDot(x,y,color);		//画点
}
/*******************************************************************************
* 函数名			:	LCD_DelayuS
* 功能描述		:	延时x微秒
* 输入			: void
* 返回值			: void
*******************************************************************************/
void LCD_DelayuS(u32 xuS)
{
	SysTick_DeleyuS(xuS);				//SysTick延时nmS;
}
/*******************************************************************************
* 函数名			:	LCD_DelaymS
* 功能描述		:	延时x毫秒
* 输入			: void
* 返回值			: void
*******************************************************************************/
void LCD_DelaymS(u32 xms)
{
	SysTick_DeleymS(xms);				//SysTick延时nmS;
}
/*******************************************************************************
* 函数名			:	LCD_DelayS
* 功能描述		:	延时x秒
* 输入			: void
* 返回值			: void
*******************************************************************************/
void LCD_DelayS(u32 xS)
{
	SysTick_DeleyS(xS);				//SysTick延时nmS;
}
//#endif//LCD_61509_EN
/************************************** The End Of FILE **************************************/


