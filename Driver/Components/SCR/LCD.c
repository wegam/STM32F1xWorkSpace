/**************************************************************************************************
* 液晶屏驱动IC
* 文件<$(filename)>
* 模块描述 :	定义、功能、说明
* 历史修改记录
*     <主要修改者>  <时间>   <版本 >   <说明>
*     xlyan        $(Date)   1.0.0    创建文件
**************************************************************************************************/
#include "LCD.H"


//#define	SSD1963_USED

#ifdef SSD1963_USED
	#include "SSD1963.H"
#else
	#include "R61509V.h"
#endif

//#include "GT32L32M0180.H"



#include "STM32_GPIO.H"
#include "STM32_PWM.H"
#include "STM32_SYSTICK.H"
#include "font.h"
#include "string.h"				//串和内存操作函数头文件
#include "stdlib.h"				//串和内存操作函数头文件
#include "stdarg.h"				//串和内存操作函数头文件
#include "stdio.h"				//串和内存操作函数头文件

LCDDef 			*LCDSYS	=	0;
/*******************************************************************************
*函数名			:	LCD_Initialize
*功能描述		:	LCD初始化：
*输入				: 
*返回值			:	无
*******************************************************************************/
void LCD_Initialize(LCDDef *pInfo)
{
	LCDSYS	=	pInfo;
	
#ifdef SSD1963_USED
	SSD1963_Initialize();
#else
	R61509V_Initialize();
#endif
	
	
	LCD_PortInitialize(&pInfo->Port);			//LCD端口配置
	LCDSYS->Display.PowerOn();						//LCD上电/初始化配置
	
	
	GT32L32_ConfigurationNR(&pInfo->GT32L32);				//普通SPI通讯方式配置	
	GPIO_Configuration_OPP50	(pInfo->GT32L32.Port.sGT32L32_CS_PORT,pInfo->GT32L32.Port.sGT32L32_CS_PIN);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605

}
/*******************************************************************************
* 函数名			:	function
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
*******************************************************************************/
void LCD_PortInitialize(LCDPortDef *pPort)
{
	LCDPortDef		*Port;	
	
	Port	=	pPort;
	
	GPIO_Configuration_OPP50	(Port->sBL_PORT,				Port->sBL_Pin);					//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度2MHz----V20170605
	GPIO_Configuration_OPP50	(Port->sRD_PORT,				Port->sRD_Pin);					//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度2MHz----V20170605
	GPIO_Configuration_OPP50	(Port->sREST_PORT,			Port->sREST_Pin);				//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度2MHz----V20170605
	GPIO_Configuration_OPP50	(Port->sDC_PORT,				Port->sDC_Pin);					//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度2MHz----V20170605
	GPIO_Configuration_OPP50	(Port->sWR_PORT,				Port->sWR_Pin);					//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度2MHz----V20170605
	GPIO_Configuration_OPP50	(Port->sCS_PORT,				Port->sCS_Pin);					//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度2MHz----V20170605
	GPIO_Configuration_OPP50	(Port->sTE_PORT,				Port->sTE_Pin);					//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度2MHz----V20170605
	GPIO_Configuration_OPP50	(Port->sDATABUS_PORT,		Port->sDATABUS_Pin);		//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度2MHz----V20170605	
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
	
if	(Rotate	==Draw_Rotate_0D)
{
	LCDSYS->Data.HSX	=	x1;
	LCDSYS->Data.HEX	=	x2;
	LCDSYS->Data.VSY	=	y1;
	LCDSYS->Data.VEY	=	y2;
	
	LCDSYS->Data.HXA	=	LCDSYS->Data.HSX;
	LCDSYS->Data.VYA	=	LCDSYS->Data.VSY;
	
	Model	=	0x5030;
}
else if (Rotate	==Draw_Rotate_90D)
{
	LCDSYS->Data.HSX	=	y1;
	LCDSYS->Data.HEX	=	y2;	
	LCDSYS->Data.VSY	=	MaxV	-	x2	-	1;
	LCDSYS->Data.VEY	=	MaxV	-	x1	-	1;
	
	LCDSYS->Data.HXA	=	LCDSYS->Data.HSX;
	LCDSYS->Data.VYA	=	LCDSYS->Data.VEY;
	Model	=	0X5018;								//GRAM(Graphics RAM--图形内存) Data Write (R202h)准备写入
}
else if (Rotate	==Draw_Rotate_180D)	
{
	LCDSYS->Data.HSX	=	MaxH	-	x2	-	1;
	LCDSYS->Data.HEX	=	MaxH	-	x1	-	1;
	LCDSYS->Data.VSY	=	MaxV	-	y2	-	1;
	LCDSYS->Data.VEY	=	MaxV	-	y1	-	1;
	
	LCDSYS->Data.HXA	=	LCDSYS->Data.HEX;
	LCDSYS->Data.VYA	=	LCDSYS->Data.VEY;
	
	Model	=	0X5000;
}
else //(Rotate	==Draw_Rotate_270D)
{
	LCDSYS->Data.HSX	=	MaxH	-	y2	-	1;
	LCDSYS->Data.HEX	=	MaxH	-	y1	-	1;
	LCDSYS->Data.VSY	=	x1;
	LCDSYS->Data.VEY	=	x2;
	
	LCDSYS->Data.HXA	=	LCDSYS->Data.HEX;
	LCDSYS->Data.VYA	=	LCDSYS->Data.VSY;

	Model	=	0X5028;
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
	//	LCD_H 240		//水平方向点数，从左到右+
	//	LCD_V 400		//垂直方向点数，从上到下+
	unsigned short x,y;
	unsigned short HSX,HEX,HSY,HEY,MaxH,MaxV;
	eRotate	Rotate	=	LCDSYS->Flag.Rotate;
	
	MaxH	=	LCDSYS->Data.MaxH;
	MaxV	=	LCDSYS->Data.MaxV;
	
	if	(Rotate	==Draw_Rotate_0D)
	{
		HSX	=	0;
		HEX	=	MaxH-1;
		HSY	=	0;
		HEY	=	MaxV-1;
	}
	else if (Rotate	==Draw_Rotate_90D)
	{
		HSX	=	0;
		HEX	=	MaxV-1;
		HSY	=	0;
		HEY	=	MaxH-1;
	}
	else if (Rotate	==Draw_Rotate_180D)
	{
		HSX	=	0;
		HEX	=	MaxH-1;
		HSY	=	0;
		HEY	=	MaxV-1;
	}
	else //if (Rotate	==Draw_Rotate_270D)
	{
		HSX	=	0;
		HEX	=	MaxV-1;
		HSY	=	0;
		HEY	=	MaxH-1;
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

//	u16	Num	=	0,i=0;
////	CoordinateTransform(&x1,&y1,&x2,&y2);
//	if(HSX>HEX)
//	{
//		Num	+=	HSX-HEX;
//	}
//	else
//	{
//		Num	+=	HEX-HSX;
//	}
//	if(HSY>HEY)
//	{
//		Num	+=	HSY-HEY;
//	}
//	else
//	{
//		Num	+=	HEY-HSY;
//	}
//	
//	LCDSYS->Display.WriteAddress(HSX,HSY,HEX,HEY);//设置窗地址
//	LCD_WriteDataStart();
//	for(i=0;i<Num;i++)
//	{
//		LCD_WriteData(Color); 	//笔画颜色
//	}
//	LCD_WriteDataEnd();
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
							unsigned short HSX, unsigned short HSY, 	//x1,y1:起点坐标
							unsigned short HEX, unsigned short HEY,		//x2,y2:终点坐标
							u16 color
)
{          
	unsigned int i;
	unsigned int j;	
//	u16 x1=0,y1=0,x2=0,y2=0;

//	switch(Sreen_Rotate)
//	{
//		case 	SCREEN_ROTATE_0D:		
//					{
//						xend=xend-1;
//						yend=yend-1;
//					}
//			break;
//		case 	SCREEN_ROTATE_90D:	
//					{
//						x1=xsta;x2=xend;y1=ysta;y2=yend;	
//						xsta=LCD_H-y2;	xend=LCD_H-y1-1;
//						ysta=x1;	yend=x2-1;
//					}
//			break;
//		case 	SCREEN_ROTATE_180D:	
//					{
//						x1=xsta;x2=xend;y1=ysta;y2=yend;
//						xsta=LCD_H-x2;	xend=LCD_H-x1-1;
//						ysta=LCD_W-y2;	yend=LCD_W-y1-1;
//					}
//			break;
//		case	SCREEN_ROTATE_270D:	
//					{
//						x1=xsta;x2=xend;y1=ysta;y2=yend;
//						xsta=y1;	xend=y2-1;
//						ysta=LCD_W-x2;	yend=LCD_W-x1-1;
//					}
//			break;
//		default: break;			
//	}
	
//	switch(Sreen_Rotate)
//	{
//		case SCREEN_ROTATE_0D:{}
//			break;
//		case SCREEN_ROTATE_90D:{x1=LCD_H-y;y=x;x=x1;}
//			break;
//		case SCREEN_ROTATE_180D:{x1=LCD_H-x;y=LCD_W-y;x=x1;}
//			break;
//		case	SCREEN_ROTATE_270D:{x1=y;y=LCD_W-x;x=x1;}
//			break;
//		default: break;			
//	}

	LCDSYS->Display.WriteAddress(HSX,HSY,HEX,HEY);
	LCD_WriteDataStart();
	for(i=0;i<HEX-HSX;i++)
	{
		for(j=0;j<HEY-HSY;j++)
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
										u8 *Buffer	//Buffer	:显示的内容缓存
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
//		LCD_SetWindowAddress(x,y,x+12-1,y+12);      //设置光标位置 
	}
	if(font==16)
	{
		if(x>LCDSYS->Data.MaxV-16||y>LCDSYS->Data.MaxH-16)
			return;
		x2	=	x+16-1;
		y2	=	y+16-1;
//		LCD_SetWindowAddress(x,y,x+16-1,y+16);      //设置光标位置 
	}
	if(font==24)
	{
		if(x>LCDSYS->Data.MaxV-24||y>LCDSYS->Data.MaxH-24)
			return;
		x2	=	x+24-1;
		y2	=	y+24-1;
//		LCD_SetWindowAddress(x,y,x+24-1,y+24);      //设置光标位置 
	}
	else if(font==32)
	{
		if(x>LCDSYS->Data.MaxV-32||y>LCDSYS->Data.MaxH-32)
			return;
		if(num==128)
		{
			x2	=	x+32-1;
			y2	=	y+32-1;
//			LCD_SetWindowAddress(x,y,x+32-1,y+32);      //设置光标位置
		}
		else
		{
			x2	=	x+16-1;
			y2	=	y+32-1;
//			LCD_SetWindowAddress(x,y,x+16-1,y+32);      //设置光标位置 
		}
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
//		temp	=	0xFF;
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
*函数名		:	LCD_ShowChar
*功能描述	:	在指定位置显示一个字符
*输入			: x,y		:起点坐标
						num		:要显示的字符:" "--->"~"
						mode	:叠加方式(1)还是非叠加方式(0)
						num		:要显示的字符:" "--->"~"
*输出			:	无
*返回值		:	无
*例程			:
*******************************************************************************/
void LCD_ShowCharT(u16 x,u16 y,u8 num,u8 mode)
{
////	LCD_BACK_COLOR	//背景色
////	LCD_POINT_COLOR	//画笔色
//	u8 temp;
//	u8 pos,t;
//	u16 x0=x;
//	u16 colortemp=LCD_POINT_COLOR; 
//	if(x>LCD_V-16||y>LCD_H-16)
//		return;	    
//	//设置窗口		   
//	num=num-' ';//得到偏移后的值
////	num=41;//得到偏移后的值
//	
//	
////	LCD_SetWindowAddress(x,y,x+8-1,y+16-1);      //设置光标位置 
//	if(!mode) //非叠加方式
//	{
//		for(pos=0;pos<16;pos++)
//		{ 
//			temp=code_asc2_1608[(u16)num*16+pos];		 		//调用1608字体
////			temp=code_num_1608[(u16)num*16+pos];		 //调用1608字体
//			for(t=0;t<8;t++)
//			{                 
//				if((temp&0x01)==0x01)
//					LCD_POINT_COLOR=colortemp;
//				else
//					LCD_POINT_COLOR=LCD_BACK_COLOR;

//				LCD_DrawDot(x,y,LCD_POINT_COLOR);//画一个点 
//				
//				temp=temp>>1; 
//				x++;
//			}
//			x=x0;
//			y++;
//		}	
//	}
//	else//叠加方式
//	{
//		for(pos=0;pos<16;pos++)
//		{
//			temp=code_asc2_1608[(u16)num*16+pos];		 //调用1608字体
//			for(t=0;t<8;t++)
//			{                 
//				if(temp&0x01)
//					LCD_DrawDot(x+t,y+pos,LCD_POINT_COLOR);//画一个点     
//				temp>>=1; 
//			}
//		}
//	}
//	LCD_POINT_COLOR=colortemp;	    	   	 	  
}
/*******************************************************************************
*函数名			:	R61509V_Clean
*功能描述		:	显示汉字程序
*输入				: 
*返回值			:	无
*******************************************************************************/
void LCD_ShowChinese(unsigned char zimo[720],unsigned int backcolor)  //写入字符
{
	unsigned char j,flag=0;
	unsigned char *point;
	unsigned int i,x1=0x00,x2=0x17,y1=0x00,y2=0x17;
	unsigned int colors[10]=
	{
		0xf800,0x07e0,0x001f,0xffe0,0x0000,0x07ff,0xf81f,0xb81f,0x7f7,0xfec0
	};
	point=&zimo[0];
	LCD_WriteDataStart();
	for(i=1;i<=720;i++,point++)
	{  
		for(j=0;j<=7;j++)
		{
			if((*point<<j)&0x80)
			{
				LCD_WriteData(colors[flag]);
			}
			else
			{
				LCD_WriteData(backcolor);
			}
		}   
		if(i%72==0)
		{
			x1=x1+24;x2=x2+24;y1=y1+24;y2=y2+24;
			flag=flag+1;
			LCDSYS->Display.WriteAddress(x1,y1,x2,y2);
		}   
	}
	LCD_WriteDataEnd();
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
unsigned int LCD_Printf(u16 x,u16 y,u8 font,const char *format,...)				//后边的省略号就是可变参数
{ 
		
//		va_list ap; 										//VA_LIST 是在C语言中解决变参问题的一组宏，所在头文件：#include <stdarg.h>,用于获取不确定个数的参数
//		static char string[ 256 ];			//定义数组，
//  	va_start( ap, format );
//		vsprintf( string , format, ap );    
//		va_end( ap );
	

	u16 i=0;		//显示
	char	Char_Buffer[256];		//记录format内码
	//1)**********获取数据宽度
	u16 num=strlen((const char*)format);		//获取数据宽度
	//2)**********定义缓冲区大小变量
	unsigned int BufferSize;
	//3)**********args为定义的一个指向可变参数的变量，va_list以及下边要用到的va_start,va_end都是是在定义，可变参数函数中必须要用到宏， 在stdarg.h头文件中定义
	va_list args; 
	//5)**********初始化args的函数，使其指向可变参数的第一个参数，format是可变参数的前一个参数
	va_start(args, format);
	//6)**********正常情况下返回生成字串的长度(除去\0),错误情况返回负值
	BufferSize = vsnprintf(Char_Buffer, 128,format, args);
	num=BufferSize;
	//7)**********结束可变参数的获取
	va_end(args);                                      		
	
	for(i=0;i<num;i++)
	{ 
		unsigned char dst=Char_Buffer[i];
//		u8 GTBuffer[512]={0};		//点阵数据存储空间
//		u32 lengh=0;						//汉字点阵的数据长度		
		if(dst>0x80)		//双字节--汉字
		{
			u16 word=dst<<8;			
//			Char_Buffer++;
			dst=Char_Buffer[i+1];
			word=word|dst;			
			//显示超限判断
			if(font==16&&x>LCDSYS->Data.MaxV-16)
			{
				x=0;
				y+=16;
			}
			if(font==32&&x>LCDSYS->Data.MaxV-32)
			{
				x=0;
				y+=32;
			}
			if(font==16&&y>LCDSYS->Data.MaxV-16)
			{
				y=x=0;
			}
			if(font==32&&y>LCDSYS->Data.MaxV-32)
			{
				y=x=0;
			}
			GT32L32_ReadBuffer(&LCDSYS->GT32L32,font,word);		//从字库中读数据函数
			//写入屏幕
			LCD_ShowChar(x,y,font,LCDSYS->GT32L32.Data.BufferSize,LCDSYS->GT32L32.Data.Buffer);
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
//			Char_Buffer++;
			i++;		//双字节，减两次
		}
		else		//单字节
		{			
			if(x>LCDSYS->Data.MaxH-16)
			{
				x=0;
				y+=32;
			}
			if(font==16&&y>LCDSYS->Data.MaxH-16)
			{
				y=x=0;
			}
			if((font==32)&&(y>LCDSYS->Data.MaxH-32))
			{
				y=x=0;
			}
			GT32L32_ReadBuffer(&LCDSYS->GT32L32,font,(u16)dst);		//从字库中读数据函数
//			//写入屏幕
			LCD_ShowChar(x,y,font,LCDSYS->GT32L32.Data.BufferSize,LCDSYS->GT32L32.Data.Buffer);			
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
//			Char_Buffer++;
//			i++;		//双字节，减两次
		}
	}
	//9)**********DMA发送完成后注意应该释放缓冲区：free(USART_BUFFER);
//	free(Char_Buffer);		//发送完成后注意应该释放缓冲区：free(Char_Buffer); 
	return BufferSize;
//	return 0;
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


