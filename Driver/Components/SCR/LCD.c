/**************************************************************************************************
* 液晶屏驱动IC
* 文件<$(filename)>
* 模块描述 :	定义、功能、说明
* 历史修改记录
*     <主要修改者>  <时间>   <版本 >   <说明>
*     xlyan        $(Date)   1.0.0    创建文件
**************************************************************************************************/
#include "LCD.H"


#include "STM32_GPIO.H"
#include "STM32_PWM.H"
#include "STM32_SYSTICK.H"
#include "font.h"
#include "string.h"				//串和内存操作函数头文件
#include "stdlib.h"				//串和内存操作函数头文件
#include "stdarg.h"				//串和内存操作函数头文件
#include "stdio.h"				//串和内存操作函数头文件

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
  //==========================检查背景色与画笔色是否相同
	if(pInfo->Data.PColor	==	pInfo->Data.BColor)
	{
		pInfo->Data.PColor	=	pInfo->Data.BColor^0xFF;
	}
	//==========================LCD初始化及上电配置
	LCDSYS->Display.PowerOn();						//LCD上电/初始化配置
	//==========================以背景色清除屏幕
	LCD_Clean(pInfo->Data.BColor);				//按背景色清除屏幕函数
	//==========================字库配置
	GT32L32_Initialize(&pInfo->GT32L32.SPI);				//普通SPI通讯方式配置	
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
u16 LCD_ReadData( void )
{
	u16 Dat;

	LCD_CS_LOW;
	LCD_WR_HIGH;
	LCD_DC_HIGH;
	Dat = LCD_DATABUS_PORT->IDR;
	LCD_RD_LOW;
	LCD_RD_HIGH;
	LCD_CS_HIGH;

	return(Dat);
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
void LCD_WriteCommand(												//写完整控制命令
											unsigned short Index,			//寄存器索引
											unsigned short Command		//命令
											)	//写完整控制命令
{
	//==================写地址
	LCD_WriteIndexStart();		
	LCD_WriteData(Index);
	LCD_WriteIndexEnd();
	
	//==================写数据
	LCD_WriteDataStart();
	LCD_WriteData(Command);
	LCD_WriteDataEnd();
}

/*******************************************************************************
*函数名			:	R61509V_SetWindowAddress
*功能描述		:	设置窗口地址
*输入				: 
*返回值			:	无
*******************************************************************************/
void LCD_SetWindowAddress(			//设置窗口地址
															unsigned short x1,		//水平起始点
															unsigned short y1,		//水平终止点
															unsigned short x2,		//垂直起始点
															unsigned short y2			//垂直终止点
															)
{	
	unsigned short MaxH,MaxV;
	unsigned short Model	=	0x5030;

	eRotate	Rotate	=	LCDSYS->Flag.Rotate;	
	MaxH	=	LCDSYS->Data.MaxH;
	MaxV	=	LCDSYS->Data.MaxV;

	switch(Rotate)
	{
		case 	Draw_Rotate_0D:
					LCDSYS->Data.HSX	=	x1;
					LCDSYS->Data.HEX	=	x2;
					LCDSYS->Data.VSY	=	y1;
					LCDSYS->Data.VEY	=	y2;
					LCDSYS->Data.HXA	=	LCDSYS->Data.HSX;
					LCDSYS->Data.VYA	=	LCDSYS->Data.VSY;
					Model	=	0x5030;
				break;
		case 	Draw_Rotate_90D:
					LCDSYS->Data.HSX	=	y1;
					LCDSYS->Data.HEX	=	y2;	
					LCDSYS->Data.VSY	=	MaxV	-	x2	-	1;
					LCDSYS->Data.VEY	=	MaxV	-	x1	-	1;	
					LCDSYS->Data.HXA	=	LCDSYS->Data.HSX;
					LCDSYS->Data.VYA	=	LCDSYS->Data.VEY;
					Model	=	0X5018;								//GRAM(Graphics RAM--图形内存) Data Write (R202h)准备写入
				break;
		case 	Draw_Rotate_180D:
					LCDSYS->Data.HSX	=	MaxH	-	x2	-	1;
					LCDSYS->Data.HEX	=	MaxH	-	x1	-	1;
					LCDSYS->Data.VSY	=	MaxV	-	y2	-	1;
					LCDSYS->Data.VEY	=	MaxV	-	y1	-	1;	
					LCDSYS->Data.HXA	=	LCDSYS->Data.HEX;
					LCDSYS->Data.VYA	=	LCDSYS->Data.VEY;	
					Model	=	0X5000;
				break;
		default:
					LCDSYS->Data.HSX	=	MaxH	-	y2	-	1;
					LCDSYS->Data.HEX	=	MaxH	-	y1	-	1;
					LCDSYS->Data.VSY	=	x1;
					LCDSYS->Data.VEY	=	x2;	
					LCDSYS->Data.HXA	=	LCDSYS->Data.HEX;
					LCDSYS->Data.VYA	=	LCDSYS->Data.VSY;
					Model	=	0X5028;
				break;
	}
	LCD_WriteCommand(LCD_R210_HSA,LCDSYS->Data.HSX);		//Window Horizontal RAM Address Start(R210h)		//水平
	LCD_WriteCommand(LCD_R211_HEA,LCDSYS->Data.HEX);		//Window Horizontal RAM Address End(R211h)			//水平
	LCD_WriteCommand(LCD_R212_VSA,LCDSYS->Data.VSY);		//Window Vertical RAM Address Start (R212h)			//垂直
	LCD_WriteCommand(LCD_R213_VEA,LCDSYS->Data.VEY);		//Window Vertical RAM Address End (R213h)				//垂直	
	LCD_WriteCommand(LCD_R200_HA,LCDSYS->Data.HXA);			//RAM Address Set (Horizontal Address) (R200h)
	LCD_WriteCommand(LCD_R201_VA,LCDSYS->Data.VYA);			//RAM Address Set (Vertical Address) (R201h)
	LCD_WriteCommand(LCD_R003_EM,Model);						//RAM Address Set (Vertical Address) (R201h)
	//R61509V_WriteIndex16(R61509V_R202_GDRW);								//GRAM(Graphics RAM--图形内存) Data Write (R202h)准备写入
	LCD_WriteIndexStart();		
	LCD_WriteData(LCD_R202_GDRW);
	LCD_WriteIndexEnd();
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
	LCD_WriteDataStart();									//写数据使能
	for(x=0;x<MaxH;x++)
	{
		for(y=0;y<MaxV;y++)
		{
			LCD_WriteData(Color);							//写数据
		}
	}	
	LCD_WriteDataEnd();										//写数据完成
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
	LCD_WriteDataStart();
	LCD_WriteData(Color); 	//笔画颜色
	LCD_WriteDataEnd();
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
					HSX	=	x1;
					HEX	=	x2;
					HSY	=	y1;
					HEY	=	y2;
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

	LCDSYS->Display.WriteAddress(HSX,HSY,HEX,HEY);
	LCD_WriteDataStart();
	for(i=0;i<=HEX-HSX;i++)
	{
		for(j=0;j<=HEY-HSY;j++)
		{
			LCD_WriteData(color);
		}
	}
	LCD_WriteDataEnd();	
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
										...)
{	
  unsigned char GetBufferLength	=	0;
  unsigned char CodeBuffer[32]={0};
	unsigned short InputDataSize=	0;		//输入可变参数大小
//	unsigned short PenColor		=	0;		//画笔颜色
//	unsigned short BackColor	=	0;		//背景颜色
//	VAsize=strlen((const char*)Num);		//获取数据宽度	
	//================va_list  声明一个指针变量，跟踪当前参数的指针
//	va_list args;
//	//================va_start 初始化这个指针的位置，最开始指向第一个参数的结尾的位置
//	VAsize=strlen((const char*)Num);		//获取数据宽度
//	va_start(args, Num);
//	//================va_arg 则移动指针，指向一个新参数的位置，并返回当前值
//	PenColor 	= va_arg(args,unsigned short);	//画笔颜色
//	BackColor = va_arg(args,unsigned short);	//背景颜色
//	va_end(args);
  if(Num>4)
  {
    Num=4;
  }
  GetBufferLength = GT32L32_GetAntennaCode(Num,CodeBuffer);
	LCD_ShowChar(x,y,12,GetBufferLength,CodeBuffer,PenColor);
	LCD_ShowChar(x,y,12,GetBufferLength,CodeBuffer,BackColor);
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
										u16 color)
{
  unsigned char GetBufferLength	=	0;
  unsigned char CodeBuffer[32]={0};
  if(Num>3)
  {
    Num=3;
  }
  GetBufferLength = GT32L32_GetBatteryCode(Num,CodeBuffer);
	LCD_ShowChar(x,y,12,GetBufferLength,CodeBuffer,color);
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
										u8 num,			//num			:字节数
										u8 *Buffer,	//Buffer	:显示的内容缓存
										u16 color
)		//高通字库测试程序
{
	u8 temp;
	u8 i=0,j=0;
	unsigned short x1=0,x2=0,y1=0,y2=0;
	u16 colortemp=LCDSYS->Data.PColor;
//	CoordinateTransform(&x1,&y1,&x2,&y2);
	x1	=	x;
	y1	=	y;
	
	if(font==12)
	{
		if(x>LCDSYS->Data.MaxV-12||y>LCDSYS->Data.MaxH-12)
			return;
		
		x2	=	x+12-1;
		y2	=	y+12-1;
	}
	if(font==16)
	{
		if(x>LCDSYS->Data.MaxV-16||y>LCDSYS->Data.MaxH-16)
			return;
			x2	=	x+8-1;
			y2	=	y+16-1;
	}
	if(font==24)
	{
		if(x>LCDSYS->Data.MaxV-24||y>LCDSYS->Data.MaxH-24)
			return;
			x2	=	x+12-1;
			y2	=	y+24-1;
	}
	else if(font==32)
	{
		if(x>LCDSYS->Data.MaxV-32||y>LCDSYS->Data.MaxH-32)
			return;
			x2	=	x+16-1;
			y2	=	y+32-1;
	}
	else
	{
//		return ;
	}
	LCDSYS->Display.WriteAddress(x1,y1,x2,y2);//设置显示区域
	i=0;
	for(i=0;i<num;i++)
	{ 
		u16 LCD_PEN_COLOR	=	LCDSYS->Data.PColor;   	//画笔色	
		temp=Buffer[i];		 					//调用1608字体--二维数组形式--字库使用时取消
		for(j=0;j<8;j++)
		{
			if((temp&0x80)==0X80)
			{
				LCD_PEN_COLOR=LCDSYS->Data.PColor;
			}
			else
				LCD_PEN_COLOR=LCDSYS->Data.BColor;
			LCD_WriteDataStart();
			LCD_WriteData(LCD_PEN_COLOR);
			LCD_WriteDataEnd();
			temp=temp<<1;
		}
    //=======================未满8位的补充定入
    if(24==font)
    {
      temp=Buffer[i+1];		 					
      for(j=0;j<4;j++)
      {
        if((temp&0x80)==0X80)
        {
          LCD_PEN_COLOR=LCDSYS->Data.PColor;
        }
        else
          LCD_PEN_COLOR=LCDSYS->Data.BColor;
        LCD_WriteDataStart();
        LCD_WriteData(LCD_PEN_COLOR);
        LCD_WriteDataEnd();
        temp=temp<<1;
      }
      i++;
    }
    else if(12==font)
    {
      temp=Buffer[i+1];		 					
      for(j=0;j<4;j++)
      {
        if((temp&0x80)==0X80)
        {
          LCD_PEN_COLOR=LCDSYS->Data.PColor;
        }
        else
          LCD_PEN_COLOR=LCDSYS->Data.BColor;
        LCD_WriteDataStart();
        LCD_WriteData(LCD_PEN_COLOR);
        LCD_WriteDataEnd();
        temp=temp<<1;
      }
      i++;
    }
		LCDSYS->Data.PColor=colortemp;	
	}	
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
										u8 num,			//num			:字节数
										u8 *Buffer,	//Buffer	:显示的内容缓存
										u16 color
)		//高通字库测试程序
{
	u8 temp;
	u8 i=0,j=0;
	unsigned short x1=0,x2=0,y1=0,y2=0;
	u16 colortemp=LCDSYS->Data.PColor;
	x1	=	x;
	y1	=	y;
	
	if(font==12)
	{
		if(x>LCDSYS->Data.MaxV-12||y>LCDSYS->Data.MaxH-12)
			return;
		
		x2	=	x+12-1;
		y2	=	y+12-1;
	}
	if(font==16)
	{
		if(x>LCDSYS->Data.MaxV-16||y>LCDSYS->Data.MaxH-16)
			return;
			x2	=	x+16-1;
			y2	=	y+16-1;

	}
	if(font==24)
	{
		if(x>LCDSYS->Data.MaxV-24||y>LCDSYS->Data.MaxH-24)
			return;

			x2	=	x+24-1;
			y2	=	y+24-1;
	}
	else if(font==32)
	{
		if(x>LCDSYS->Data.MaxV-32||y>LCDSYS->Data.MaxH-32)
			return;
			x2	=	x+32-1;
			y2	=	y+32-1;
	}
	else
	{
//		return ;
	}
	LCDSYS->Display.WriteAddress(x1,y1,x2,y2);//设置显示区域
	i=0;
	for(i=0;i<num;i++)
	{ 
		u16 LCD_PEN_COLOR	=	LCDSYS->Data.PColor;   	//画笔色	
		temp=Buffer[i];		 				
		for(j=0;j<8;j++)
		{
			if((temp&0x80)==0X80)
			{
				LCD_PEN_COLOR=LCDSYS->Data.PColor;
			}
			else
				LCD_PEN_COLOR=LCDSYS->Data.BColor;
			LCD_WriteDataStart();
			LCD_WriteData(LCD_PEN_COLOR);
			LCD_WriteDataEnd();
			temp=temp<<1;
		}
		LCDSYS->Data.PColor=colortemp;	
	}	
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
		//=====================双字节--汉字
		if(dst>0x80)
		{
			u16 word=dst<<8;
      
			dst=Buffer[i+1];
			word=word|dst;			
			//显示超限判断
			if(font==12)
			{
				if(x>MaxH-12)
				{
					x=0;
					y+=12;
				}
				if(y>MaxV-12)
				{
					y=x=0;
				}
			}
			else if(font==16)
			{
				if(x>MaxH-16)
				{
					x=0;
					y+=16;
				}
				if(y>MaxV-16)
				{
					y=x=0;
				}
			}
			else if(font==24)
			{
				if(x>MaxH-24)
				{
					x=0;
					y+=24;
				}
				if(y>MaxV-24)
				{
					y=x=0;
				}
			}
			else if(font==32)
			{
				if(x>MaxH-32)
				{
					x=0;
					y+=32;
				}
				if(y>MaxV-32)
				{
					y=x=0;
				}
			}
			else
			{

			}
			GetBufferLength	=	GT32L32_ReadCode(font,word,CodeBuffer);		//从字库中读数据并返回数据长度
			//写入屏幕
			LCD_ShowWord(x,y,font,GetBufferLength,CodeBuffer,0);
			//显示地址增加	
			if(font==12)
			{
				x+=12;
			}
			else if(font==16)
			{
				x+=16;
			}
			else if(font==24)
			{
				x+=24;
			}
			else if(font==32)
			{
				x+=32;
			}
			i++;		//双字节，减两次
			
		}
		//=====================单字节--ASCII字符集
		else
		{			
			//显示超限判断
			if(font==12)
			{
				if(x>MaxH-12)
				{
					x=0;
					y+=12;
				}
				if(y>MaxV-12)
				{
					y=x=0;
				}
			}
			if(font==16)
			{
				if(x>MaxH-8)
				{
					x=0;
					y+=16;
				}
				if(y>MaxV-16)
				{
					y=x=0;
				}
			}
			if(font==24)
			{
				if(x>MaxH-24)
				{
					x=0;
					y+=24;
				}
				if(y>MaxV-24)
				{
					y=x=0;
				}
			}
			if(font==32)
			{
				if(x>MaxH-32)
				{
					x=0;
					y+=32;
				}
				if(y>MaxV-32)
				{
					y=x=0;
				}
			}
			GetBufferLength	=	GT32L32_ReadCode(font,(u16)dst,CodeBuffer);		//从字库中读数据并返回数据长度
//			//写入屏幕
			LCD_ShowChar(x,y,font,GetBufferLength,CodeBuffer,0);
			//显示地址增加
			if(font==12)
			{
				x+=6;
			}
			else if(font==16)
			{
				x+=8;
			}
			else if(font==24)
			{
				x+=12;
			}
			else if(font==32)
			{
				x+=16;
			}			
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
	
	unsigned short	MaxV,MaxH;	//边界值
	unsigned short	i=0;				//显示
	char	DataBuffer[256]={0};			//记录format内码
  unsigned char CodeBuffer[130]={0};
	//1)**********获取数据宽度
	u16 InputDataSize=strlen((const char*)format);		//获取数据宽度	
	
	//3)**********args为定义的一个指向可变参数的变量，va_list以及下边要用到的va_start,va_end都是是在定义，可变参数函数中必须要用到宏， 在stdarg.h头文件中定义
	va_list args; 
	//5)**********初始化args的函数，使其指向可变参数的第一个参数，format是可变参数的前一个参数
	va_start(args, format);
	//6)**********正常情况下返回生成字串的长度(除去\0),错误情况返回负值
	vsnprintf(DataBuffer, InputDataSize+1,format, args);

	//7)**********结束可变参数的获取
	va_end(args);                                      		

	LCD_Show(x,y,font,InputDataSize,(unsigned char*)DataBuffer);
	return InputDataSize;
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
* 函数名			:	function
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
*******************************************************************************/
void LCD_Delay(u32 xms)
{
	while(xms--);
}

//#endif//LCD_61509_EN
/************************************** The End Of FILE **************************************/


