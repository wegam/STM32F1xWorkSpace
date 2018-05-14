/**************************************************************************************************
* 液晶屏驱动IC
* 文件<$(filename)>
* 模块描述 :	定义、功能、说明
* 历史修改记录
*     <主要修改者>  <时间>   <版本 >   <说明>
*     xlyan        $(Date)   1.0.0    创建文件
**************************************************************************************************/
#include "R61509V.h"

#include "STM32_GPIO.H"
#include "STM32_PWM.H"
#include "STM32_SYSTICK.H"
#include "font.h"

#include "LCD.H"

#define	Screen_Rotate	90

LCDDef	*pR61509V	=	0;


/*******************************************************************************
* 函数名			:	function
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
*******************************************************************************/
void R61509V_Initialize(void)
{
	pR61509V		=	LCDSYS;
	
//	pInfo->Display.PortInitialize		=	R61509V_PortInitialize;
//	pInfo->Display.WriteIndexStart	=	R61509V_WriteIndexStart;
//	pInfo->Display.WriteIndexEnd		=	R61509V_WriteIndexEnd;
//	pInfo->Display.WriteDataStart		=	R61509V_WriteDataStart;
//	pInfo->Display.WriteDataEnd			=	R61509V_WriteDataEnd;
//	pInfo->Display.WriteData				=	R61509V_WriteData;
//	
//	pInfo->Display.WriteCommand			=	R61509V_WriteCommand;
	
	
	LCDSYS->Data.MaxH	=	240;								//最大水平宽度
	LCDSYS->Data.MaxV	=	400;								//最大垂直高度
//	pInfo->Flag.Rotate	=	Draw_Rotate_90D;	//使用旋转角度
	LCDSYS->Data.BColor	=	LCD565_RED;				//背景色
	LCDSYS->Data.PColor	=	LCD565_YELLOW;		//画笔色
	
	LCDSYS->Display.WriteAddress		=	R61509V_SetWindowAddress;
	LCDSYS->Display.PowerOn					=	R61509V_PowerOn;
	LCDSYS->Display.DispOff					=	R61509V_PowerOff;
	
}
///*******************************************************************************
//* 函数名			:	function
//* 功能描述		:	函数功能说明 
//* 输入			: void
//* 返回值			: void
//*******************************************************************************/
//void R61509V_Delay(u32 xms)
//{
//	while(xms--);
//}
///*******************************************************************************
//* 函数名			:	function
//* 功能描述		:	函数功能说明 
//* 输入			: void
//* 返回值			: void
//*******************************************************************************/
//void R61509V_PortInitialize(LCDPortDef *pPort)
//{
//	LCDPortDef		*Port;	
//	
//	Port	=	pPort;
//	
//	GPIO_Configuration_OPP50	(Port->sBL_PORT,				Port->sBL_Pin);					//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度2MHz----V20170605
//	GPIO_Configuration_OPP50	(Port->sRD_PORT,				Port->sRD_Pin);					//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度2MHz----V20170605
//	GPIO_Configuration_OPP50	(Port->sREST_PORT,			Port->sREST_Pin);				//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度2MHz----V20170605
//	GPIO_Configuration_OPP50	(Port->sRS_PORT,				Port->sRS_Pin);					//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度2MHz----V20170605
//	GPIO_Configuration_OPP50	(Port->sWR_PORT,				Port->sWR_Pin);					//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度2MHz----V20170605
//	GPIO_Configuration_OPP50	(Port->sCS_PORT,				Port->sCS_Pin);					//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度2MHz----V20170605
//	GPIO_Configuration_OPP50	(Port->sTE_PORT,				Port->sTE_Pin);					//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度2MHz----V20170605
//	GPIO_Configuration_OPP50	(Port->sDATABUS_PORT,		Port->sDATABUS_Pin);		//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度2MHz----V20170605	
//	
//	
//	LCD_RD_HIGH;	//读信号;0:读数据
//}

///**************************************************************************************************
//* [Function] R61509V_DispOff:  关闭R61509V显示( 黑屏?)
//* [No param]
//**************************************************************************************************/
//void R61509V_WriteIndexStart( void )
//{
//	LCD_CS_LOW; 	//片选信号 0:片选;1:失能;
//	LCD_RS_LOW; 	//命令/数据：0：命令;1-数据
//	LCD_RD_HIGH;	//读信号;0:读数据
//}
///**************************************************************************************************
//* [Function] R61509V_DispOff:  关闭R61509V显示( 黑屏?)
//* [No param]
//**************************************************************************************************/
//void R61509V_WriteIndexEnd( void )
//{
//	LCD_CS_HIGH;	//片选信号 0:片选;1:失能;
//}
///**************************************************************************************************
//* [Function] R61509V_DispOff:  关闭R61509V显示( 黑屏?)
//* [No param]
//**************************************************************************************************/
//void R61509V_WriteDataStart( void )
//{
//	LCD_CS_LOW; 	//片选信号 0:片选;1:失能;
//	LCD_RS_HIGH; 	//命令/数据：0：命令;1-数据
//	LCD_RD_HIGH;	//读信号;0:读数据
//}
///**************************************************************************************************
//* [Function] R61509V_DispOff:  关闭R61509V显示( 黑屏?)
//* [No param]
//**************************************************************************************************/
//void R61509V_WriteDataEnd( void )
//{
//	LCD_RS_LOW; 	//数据
//	LCD_CS_HIGH;
//}
//#if 1
///*******************************************************************************
//* 函数名			:	R61509V_WriteData
//* 功能描述		:	写16位数据
//* 输入			: void
//* 返回值			: void
//* 修改时间		: 无
//* 修改内容		: 无
//* 其它			: wegam@sina.com
//*******************************************************************************/
//void R61509V_WriteData(u16 Data)
//{
//	LCD_WR_LOW;
//	LCD_DATABUS_PORT->ODR = Data;		
//	LCD_WR_HIGH;
//}
//#else
///*******************************************************************************
//* 函数名			:	R61509V_WriteData
//* 功能描述		:	写8位数据
//* 输入			: void
//* 返回值			: void
//* 修改时间		: 无
//* 修改内容		: 无
//* 其它			: wegam@sina.com
//*******************************************************************************/
//void R61509V_WriteData(u16 Data)
//{
//	LCD_WR_LOW;
//	LCD_DATABUS_PORT->ODR = Data>>8;		
//	LCD_WR_HIGH;
//	
//	LCD_WR_LOW;
//	LCD_DATABUS_PORT->ODR = Data;		
//	LCD_WR_HIGH;
//}
//#endif
//#if 1
///*******************************************************************************
//* 函数名			:	R61509V_WriteIndex16
//* 功能描述		:	写16位索引
//* 输入			: void
//* 返回值			: void
//* 修改时间		: 无
//* 修改内容		: 无
//* 其它			: wegam@sina.com
//*******************************************************************************/
//void R61509V_WriteIndex16(unsigned short index)	//写16位命令索引编号
//{
//	R61509V_WriteIndexStart();	
//	R61509V_WriteData(index);
//	R61509V_WriteIndexEnd();
//}
///*******************************************************************************
//* 函数名			:	R61509V_WriteData16
//* 功能描述		:	写16位数据
//* 输入			: void
//* 返回值			: void
//* 修改时间		: 无
//* 修改内容		: 无
//* 其它			: wegam@sina.com
//*******************************************************************************/
//void R61509V_WriteData16(unsigned short Data)			//写16位数据
//{
//	R61509V_WriteDataStart();
//	R61509V_WriteData(Data);
//	R61509V_WriteDataEnd();
//}



//#else
///*******************************************************************************
//* 函数名			:	R61509V_WriteData16
//* 功能描述		:	写8位数据
//* 输入			: void
//* 返回值			: void
//* 修改时间		: 无
//* 修改内容		: 无
//* 其它			: wegam@sina.com
//*******************************************************************************/
//void R61509V_WriteData16(unsigned short dashuju)			//写16位数据
//{
//	//****写入高位
//	LCD_CS_LOW; 	//片选信号 0:片选;1:失能;
//	LCD_RD_HIGH;
//	LCD_RS_HIGH; 	//命令/数据：0：命令;1-数据
//	LCD_WR_LOW;		//写信号 在WR的上升沿，使数据写入到R61509V里面
//	DATA=dashuju>>8;
//	LCD_WR_HIGH;
////****写入低位
//	LCD_WR_LOW;
//	DATA=dashuju;
//	LCD_WR_HIGH;
//	LCD_CS_HIGH;
//}
///*******************************************************************************
//* 函数名			:	R61509V_WriteIndex16
//* 功能描述		:	写8位索引
//* 输入			: void
//* 返回值			: void
//* 修改时间		: 无
//* 修改内容		: 无
//* 其它			: wegam@sina.com
//*******************************************************************************/
//void R61509V_WriteIndex16(unsigned short index)		//写16位命令索引编号
//{
//	//****写入高位
//	LCD_CS_LOW; //片选打开
//	LCD_RS_LOW; //命令/数据：0：命令;1-数据
//	LCD_WR_LOW;
//	DATA=index>>8;
//	LCD_WR_HIGH;
//	//****写入低位
//	LCD_WR_LOW;
//	DATA=index;
//	LCD_WR_HIGH;
//	LCD_CS_HIGH;
//}
//#endif
///**************************************************************************************************
//* [Function] R61509V_ReadData:  从R61509V读取数据
//* [No param][return]u16: 返回数据
//**************************************************************************************************/
//u16 R61509V_ReadData( void )
//{
//	u16 Dat;

//	LCD_CS_LOW;
//	LCD_WR_HIGH;
//	LCD_RS_HIGH;
//	Dat = LCD_DATABUS_PORT->IDR;
//	LCD_RD_LOW;
//	LCD_RD_HIGH;
//	LCD_CS_HIGH;

//	return(Dat);
//}

///*******************************************************************************
//*函数名			:	R61509V_WriteCommand
//*功能描述		:	写完整控制命令
//*输入				: 
//*返回值			:	无
//*******************************************************************************/
//void R61509V_WriteCommand(												//写完整控制命令
//											unsigned short Index,			//寄存器索引
//											unsigned short Command		//命令
//											)	//写完整控制命令
//{
//	//==================写地址
//	LCD_WriteIndexStart();		
//	LCD_WriteData(Index);
//	LCD_WriteIndexEnd();
//	
//	//==================写数据
//	LCD_WriteDataStart();
//	LCD_WriteData(Command);
//	LCD_WriteDataEnd();
//}

/*******************************************************************************
*函数名			:	R61509V_SetWindowAddress
*功能描述		:	设置窗口地址
*输入				: 
*返回值			:	无
*******************************************************************************/
void R61509V_SetWindowAddress(			//设置窗口地址
															unsigned short x1,		//水平起始点
															unsigned short y1,		//水平终止点
															unsigned short x2,		//垂直起始点
															unsigned short y2			//垂直终止点
															)
{	
	unsigned short MaxH,MaxV;
	unsigned short Model	=	0x5030;

	eRotate	Rotate	=	pR61509V->Flag.Rotate;

	
	MaxH	=	pR61509V->Data.MaxH;
	MaxV	=	pR61509V->Data.MaxV;
	
if	(Rotate	==Draw_Rotate_0D)
{
	pR61509V->Data.HSX	=	x1;
	pR61509V->Data.HEX	=	x2;
	pR61509V->Data.VSY	=	y1;
	pR61509V->Data.VEY	=	y2;
	
	pR61509V->Data.HXA	=	pR61509V->Data.HSX;
	pR61509V->Data.VYA	=	pR61509V->Data.VSY;
	
	Model	=	0x5030;
}
else if (Rotate	==Draw_Rotate_90D)
{
	pR61509V->Data.HSX	=	y1;
	pR61509V->Data.HEX	=	y2;	
	pR61509V->Data.VSY	=	MaxV	-	x2	-	1;
	pR61509V->Data.VEY	=	MaxV	-	x1	-	1;
	
	pR61509V->Data.HXA	=	pR61509V->Data.HSX;
	pR61509V->Data.VYA	=	pR61509V->Data.VEY;
	Model	=	0X5018;								//GRAM(Graphics RAM--图形内存) Data Write (R202h)准备写入
}
else if (Rotate	==Draw_Rotate_180D)	
{
	pR61509V->Data.HSX	=	MaxH	-	x2	-	1;
	pR61509V->Data.HEX	=	MaxH	-	x1	-	1;
	pR61509V->Data.VSY	=	MaxV	-	y2	-	1;
	pR61509V->Data.VEY	=	MaxV	-	y1	-	1;
	
	pR61509V->Data.HXA	=	pR61509V->Data.HEX;
	pR61509V->Data.VYA	=	pR61509V->Data.VEY;
	
	Model	=	0X5000;
}
else //(Rotate	==Draw_Rotate_270D)
{
	pR61509V->Data.HSX	=	MaxH	-	y2	-	1;
	pR61509V->Data.HEX	=	MaxH	-	y1	-	1;
	pR61509V->Data.VSY	=	x1;
	pR61509V->Data.VEY	=	x2;
	
	pR61509V->Data.HXA	=	pR61509V->Data.HEX;
	pR61509V->Data.VYA	=	pR61509V->Data.VSY;

	Model	=	0X5028;
}
	LCD_WriteCommand(R61509V_R210_HSA,pR61509V->Data.HSX);		//Window Horizontal RAM Address Start(R210h)		//水平
	LCD_WriteCommand(R61509V_R211_HEA,pR61509V->Data.HEX);		//Window Horizontal RAM Address End(R211h)			//水平
	LCD_WriteCommand(R61509V_R212_VSA,pR61509V->Data.VSY);		//Window Vertical RAM Address Start (R212h)			//垂直
	LCD_WriteCommand(R61509V_R213_VEA,pR61509V->Data.VEY);		//Window Vertical RAM Address End (R213h)				//垂直
	
	LCD_WriteCommand(R61509V_R200_HA,pR61509V->Data.HXA);			//RAM Address Set (Horizontal Address) (R200h)
	LCD_WriteCommand(R61509V_R201_VA,pR61509V->Data.VYA);			//RAM Address Set (Vertical Address) (R201h)

	LCD_WriteCommand(R61509V_R003_EM,Model);						//RAM Address Set (Vertical Address) (R201h)
//	R61509V_WriteIndex16(R61509V_R202_GDRW);								//GRAM(Graphics RAM--图形内存) Data Write (R202h)准备写入
	LCD_WriteIndexStart();	
	LCD_WriteData(R61509V_R202_GDRW);
	LCD_WriteIndexEnd();
}


/*******************************************************************************
*函数名			:	R61509V_Initialize
*功能描述		:	IC初始化：按照主控芯片R61509V的power supply on sequence 进行配置
*输入				: 
*返回值			:	无
*******************************************************************************/
void R61509V_PowerOn(void)			//按照主控芯片R61509V的power supply on sequence 进行配置
{
	u32 dtime=2000;
	
	void(*Command)(unsigned short Index,unsigned short Command);//LcdDisplay.WriteCommand	
	Command	=	LCD_WriteCommand;
	
	LCD_CS_LOW;
	LCD_WR_HIGH;
	LCD_RD_HIGH;
	LCD_RST_HIGH;
	LCD_Delay(dtime);
	LCD_RST_LOW;
	LCD_Delay(dtime);
	LCD_RST_HIGH;	
	LCD_Delay(dtime);		//复位后1ms内部晶振启动
	dtime=500;
	
	Command(R61509V_R000_IR		,	0x0000);		LCD_Delay(dtime); //四次写0x00
	Command(R61509V_R000_IR		,	0x0000);		LCD_Delay(dtime); //四次写0x00
	Command(R61509V_R000_IR		,	0x0000);		LCD_Delay(dtime); //四次写0x00
	Command(R61509V_R000_IR		,	0x0000);		LCD_Delay(dtime); //四次写0x00
	
	Command(R61509V_R001_DOC	,	0x0300);		LCD_Delay(dtime); //--------显示方向控制When SS = “1” and BGR = “1”, RGB dots are assigned one to one from S720 to S1.
	Command(R61509V_R002_DWC	,	0x0100);		LCD_Delay(dtime); //--------	
	Command(R61509V_R003_EM		,	0X5030);		LCD_Delay(dtime); //--------RGB设为5-6-5模式------------0X5030
	Command(R61509V_R007_DC1	,	0x0100);		LCD_Delay(dtime); //--------测试显示控制base image的关与开
	Command(R61509V_R008_DC2	,	0X0808);		LCD_Delay(dtime); //--------
	Command(R61509V_R009_DC3	,	0x0001);		LCD_Delay(dtime); //--------	
	
	Command(R61509V_R00B_ECC		,	0x0001);		LCD_Delay(dtime); //--------
	Command(R61509V_R00C_EDIC1	,	0x0000);		LCD_Delay(dtime); //--------
	Command(R61509V_R00F_EDIC2	,	0x0000);		LCD_Delay(dtime); //--------
	
	Command(R61509V_R010_PIC1	,	0x0019);		LCD_Delay(dtime); //--------面板频率--0x19
	Command(R61509V_R011_PIC2	,	0x0101);		LCD_Delay(dtime); //--------		Panel Interface Control 2 (R011h)
	Command(R61509V_R012_PIC3	,	0x0000);		LCD_Delay(dtime); //--------
	Command(R61509V_R013_PIC4	,	0x0001);		LCD_Delay(dtime); //--------
	Command(R61509V_R014_PIC5	,	0x0055);		LCD_Delay(dtime); //--------
	Command(R61509V_R020_PIC6	,	0x0010);		LCD_Delay(dtime); //--------
	Command(R61509V_R021_PIC7	,	0x0101);		LCD_Delay(dtime); //--------
	Command(R61509V_R022_PIC8	,	0x0000);		LCD_Delay(dtime); //--------
	Command(R61509V_R023_PIC9	,	0x0001);		LCD_Delay(dtime); //--------	
	
	Command(R61509V_R090_FMC		,	0x8000);		LCD_Delay(dtime); //--------窗特征控制，FMARK interface
	
	Command(R61509V_R100_PC1		,	0x0330);		LCD_Delay(dtime); //--------设置电源控制，平衡显示与电消耗
	Command(R61509V_R101_PC2		,	0x0227);		LCD_Delay(dtime); //--------Power Control 2
	Command(R61509V_R102_PC3		,	0xC1B0);		LCD_Delay(dtime); //--------PSON,PON 都设为1，电源供应打开
	Command(R61509V_R103_PC4		,	0x0D00);		LCD_Delay(dtime); //--------	
	
	Command(R61509V_R200_HA			,	0x0000);		LCD_Delay(dtime);	//--------RAM address 设置
	Command(R61509V_R201_VA			,	0x0000);		LCD_Delay(dtime);	//--------
	
	Command(R61509V_R280_NVM		,	0xB000);		LCD_Delay(dtime);	//--------VCM
	
	Command(R61509V_R300_YC1		,	0x0C00);		LCD_Delay(dtime); //--------
	Command(R61509V_R301_YC2		,	0x5A0B);		LCD_Delay(dtime); //--------
	Command(R61509V_R302_YC3		,	0x0906);		LCD_Delay(dtime); //--------
	Command(R61509V_R303_YC4		,	0x1017);		LCD_Delay(dtime); //--------
	Command(R61509V_R304_YC5		,	0x2300);		LCD_Delay(dtime); //--------
	Command(R61509V_R305_YC6		,	0x1700);		LCD_Delay(dtime); //--------
	Command(R61509V_R306_YC7		,	0x6309);		LCD_Delay(dtime); //--------
	Command(R61509V_R307_YC8		,	0x0C09);		LCD_Delay(dtime); //--------
	Command(R61509V_R308_YC9		,	0x100C);		LCD_Delay(dtime); //--------
	Command(R61509V_R309_YC10		,	0x2232);		LCD_Delay(dtime); //--------
	
	Command(R61509V_R400_BINL		,	0X6400);		LCD_Delay(dtime); //base image 设置 400线
	Command(R61509V_R401_BIDC		,	0x0004);		LCD_Delay(dtime); //--------设置base image 滚动模式，开启滚动(颜色反相设置）
	Command(R61509V_R404_BIVSC	,	0x0000);		LCD_Delay(dtime);	//--------从0线开始滚屏
	
	Command(R61509V_R502_PTEA		,	0x005f);		LCD_Delay(dtime);
	LCD_BL_ON;		//开背光
}

/**************************************************************************************************
* [Function] R61509V_PowerOff:  关闭R61509V 电源
* [No param]
**************************************************************************************************/
void R61509V_PowerOff( void )
{
	LCD_WriteCommand( R61509V_R009_DC3, 0 );
	LCD_BL_OFF;
}
/**************************************************************************************************
* [Function] R61509V_DispOff:  关闭R61509V显示( 黑屏?)
* [No param]
**************************************************************************************************/
void R61509V_DispOff( void )
{
	LCD_WriteCommand( R61509V_R007_DC1, 0x0000 );
}

///*******************************************************************************
//*函数名			:	R61509V_Clean
//*功能描述		:	清屏程序：清除屏幕函数---用背景色填充屏幕
//*输入				: 
//*返回值			:	无
//*******************************************************************************/
//void R61509V_Clean(u16 COLOR)	//清除屏幕函数
//{
//	//	R61509V_H 240		//水平方向点数，从左到右+
//	//	R61509V_V 400		//垂直方向点数，从上到下+
//	unsigned short x,y;
//	unsigned short HSX,HEX,HSY,HEY,MaxH,MaxV;
//	eRotate	Rotate	=	pR61509V->Flag.Rotate;
//	
//	MaxH	=	pR61509V->Data.MaxH;
//	MaxV	=	pR61509V->Data.MaxV;
//	
//	if	(Rotate	==Draw_Rotate_0D)
//	{
//		HSX	=	0;
//		HEX	=	MaxH-1;
//		HSY	=	0;
//		HEY	=	MaxV-1;
//	}
//	else if (Rotate	==Draw_Rotate_90D)
//	{
//		HSX	=	0;
//		HEX	=	MaxV-1;
//		HSY	=	0;
//		HEY	=	MaxH-1;
//	}
//	else if (Rotate	==Draw_Rotate_180D)
//	{
//		HSX	=	0;
//		HEX	=	MaxH-1;
//		HSY	=	0;
//		HEY	=	MaxV-1;
//	}
//	else //if (Rotate	==Draw_Rotate_270D)
//	{
//		HSX	=	0;
//		HEX	=	MaxV-1;
//		HSY	=	0;
//		HEY	=	MaxH-1;
//	}	
//	pR61509V->Display.WriteAddress(HSX,HSY,HEX,HEY);
//	pR61509V->Display.WriteDataStart();
//	for(x=0;x<MaxH;x++)
//	{
//		for(y=0;y<MaxV;y++)
//		{
//			pR61509V->Display.WriteData(COLOR);
//		}
//	}	
//	pR61509V->Display.WriteDataEnd();
//}

///*******************************************************************************
//*函数名			:	R61509V_DrawPoint
//*功能描述		:	画点
//*输入				: 
//*返回值			:	无
//*******************************************************************************/
//void R61509V_DrawDot(u16 x,u16 y,u16 color)
//{
//	pR61509V->Display.WriteAddress(x,y,x,y);	//设置光标位置 
//	pR61509V->Display.WriteDataStart();
//	pR61509V->Display.WriteData(color); 	//笔画颜色
//	pR61509V->Display.WriteDataEnd();
//}

///*******************************************************************************
//*函数名		:	R61509V_DrawLine
//*功能描述	:	画线
//*输入			: x1,y1:起点坐标
//						x2,y2:终点坐标
//*输出			:	无
//*返回值		:	无
//*例程			:
//*******************************************************************************/
//void R61509V_DrawLine(
//									u16 x1, u16 y1, 	//x1,y1:起点坐标
//									u16 x2, u16 y2,		//x2,y2:终点坐标
//									u16 color					//颜色
//)
//{
//	u16 t; 
//	int xerr=0,yerr=0,delta_x,delta_y,distance; 
//	int incx,incy,uRow,uCol; 

//	delta_x=x2-x1; //计算坐标增量 
//	delta_y=y2-y1; 
//	uRow=x1; 
//	uCol=y1;
//	
//	if(delta_x>0)
//		incx=1; //设置单步方向 
//	else if(delta_x==0)
//		incx=0;//垂直线 
//	else
//		{
//			incx=-1;
//			delta_x=-delta_x;
//		}
//		
//	if(delta_y>0)
//		incy=1; 
//	else if(delta_y==0)
//		incy=0;//水平线 
//	else
//		{incy=-1;delta_y=-delta_y;}
//		
//	if( delta_x>delta_y)
//		distance=delta_x; 								//选取基本增量坐标轴 
//	else
//		distance=delta_y;
//	
//	for(t=0;t<distance+1;t++ )					//画线输出 
//	{  
//		R61509V_DrawDot(uRow,uCol,color);	//画点 
//		xerr+=delta_x ; 
//		yerr+=delta_y ; 
//		if(xerr>distance) 
//		{ 
//			xerr-=distance; 
//			uRow+=incx; 
//		} 
//		if(yerr>distance) 
//		{ 
//			yerr-=distance;
//			uCol+=incy; 
//		} 
//	}

////	u16	Num	=	0,i=0;
//////	CoordinateTransform(&x1,&y1,&x2,&y2);
////	if(x1>x2)
////	{
////		Num	+=	x1-x2;
////	}
////	else
////	{
////		Num	+=	x2-x1;
////	}
////	if(y1>y2)
////	{
////		Num	+=	y1-y2;
////	}
////	else
////	{
////		Num	+=	y2-y1;
////	}
////	
////	R61509V_SetWindowAddress(x1,y1,x2,y2);//设置窗地址
////	for(i=0;i<Num;i++)
////	{
////		R61509V_WriteData16(color); 	//笔画颜色
////	}
//}
///**************************************************************************************************
//* [Function] R61509V_DrawCircle:  函数功能、注意事项等的描述
//* [param01]t_Point point: description
//* [param02]u16 R: description
//* [param03]uint8_t Filled: description
//* [param04]u16 color: description
//**************************************************************************************************/
//void R61509V_DrawCircle(
//												u16 x,u16 y,		//圆心坐标原点
//												u16 r,					//半径
//												u8 Filled,			//是否填充
//												u16 color				//颜色
//												)
//{
//	int a,b;
//	int di;
//	
////	void ( *DSPDrawDot )(unsigned short HSX,unsigned short HSY,unsigned short Color);
////	void ( *DSPDrawLine )( unsigned short HSX,unsigned short HSY,unsigned short HEX,unsigned short HEY,unsigned short Color);
////	DSPDrawDot	=	LcdDisplay.DSPDrawDot;
////	DSPDrawLine	=	LcdDisplay.DSPDrawLine;
//	
//	a=0;b=r;	  
//	di=3-(r<<1);             //判断下个点位置的标志
//	while(a<=b)
//	{
//		if(Filled)	//填充就画线
//		{
//			R61509V_DrawLine(x,y,x-b,y-a,color);             //3           
//			R61509V_DrawLine(x,y,x+b,y-a,color);             //0           
//			R61509V_DrawLine(x,y,x-a,y+b,color);             //1       
//			R61509V_DrawLine(x,y,x-b,y-a,color);             //7           
//			R61509V_DrawLine(x,y,x-a,y-b,color);             //2             
//			R61509V_DrawLine(x,y,x+b,y+a,color);             //4               
//			R61509V_DrawLine(x,y,x+a,y-b,color);             //5
//			R61509V_DrawLine(x,y,x+a,y+b,color);             //6 
//			R61509V_DrawLine(x,y,x-b,y+a,color);             
//			a++;
//			//使用Bresenham算法画圆     
//			if(di<0)
//				di +=4*a+6;	  
//			else
//			{
//				di+=10+4*(a-b);   
//				b--;
//			}
//			R61509V_DrawLine(x,y,x+a,y+b,color);				//AB 两个坐标画一条直线
//		}
//		else
//		{
//			R61509V_DrawDot(x-b,y-a,color);             //3           
//			R61509V_DrawDot(x+b,y-a,color);             //0           
//			R61509V_DrawDot(x-a,y+b,color);             //1       
//			R61509V_DrawDot(x-b,y-a,color);             //7           
//			R61509V_DrawDot(x-a,y-b,color);             //2             
//			R61509V_DrawDot(x+b,y+a,color);             //4               
//			R61509V_DrawDot(x+a,y-b,color);             //5
//			R61509V_DrawDot(x+a,y+b,color);             //6 
//			R61509V_DrawDot(x-b,y+a,color);             
//			a++;
//			//使用Bresenham算法画圆     
//			if(di<0)
//				di +=4*a+6;	  
//			else
//			{
//				di+=10+4*(a-b);   
//				b--;
//			}
//				R61509V_DrawDot(x+a,y+b,color);
//		}
//	}
//}
///**************************************************************************************************
//* [Function] R61509V_DrawRectangle:  画一下矩形框
//* [param01]t_Point top_p: 顶点坐标值
//* [param02]t_Point botton_p : 地板坐标值
//**************************************************************************************************/
//void R61509V_DrawRectangle(u16 x1,u16 y1,u16 x2,u16 y2,u16 color)
//{
//	R61509V_DrawLine( x1, y1,	x1,	y2, color );
//	R61509V_DrawLine( x1, y1,	x2,	y1, color );
//	R61509V_DrawLine( x2, y1,	x2,	y2, color );
//	R61509V_DrawLine( x1, y2,	x2,	y2, color );
//}
///*******************************************************************************
//*函数名			:	R61509V_DrawPoint_big
//*功能描述		:	在指定区域内填充指定颜色;区域大小:(xend-xsta)*(yend-ysta)
//*输入				: 
//*返回值			:	无
//*******************************************************************************/
//void R61509V_Fill(
//							u16 xsta,u16 ysta,
//							u16 xend,u16 yend,
//							u16 color
//)
//{          
//	unsigned int i;
//	unsigned int j;	
////	u16 x1=0,y1=0,x2=0,y2=0;

////	switch(Sreen_Rotate)
////	{
////		case 	SCREEN_ROTATE_0D:		
////					{
////						xend=xend-1;
////						yend=yend-1;
////					}
////			break;
////		case 	SCREEN_ROTATE_90D:	
////					{
////						x1=xsta;x2=xend;y1=ysta;y2=yend;	
////						xsta=R61509V_H-y2;	xend=R61509V_H-y1-1;
////						ysta=x1;	yend=x2-1;
////					}
////			break;
////		case 	SCREEN_ROTATE_180D:	
////					{
////						x1=xsta;x2=xend;y1=ysta;y2=yend;
////						xsta=R61509V_H-x2;	xend=R61509V_H-x1-1;
////						ysta=R61509V_W-y2;	yend=R61509V_W-y1-1;
////					}
////			break;
////		case	SCREEN_ROTATE_270D:	
////					{
////						x1=xsta;x2=xend;y1=ysta;y2=yend;
////						xsta=y1;	xend=y2-1;
////						ysta=R61509V_W-x2;	yend=R61509V_W-x1-1;
////					}
////			break;
////		default: break;			
////	}
//	
////	switch(Sreen_Rotate)
////	{
////		case SCREEN_ROTATE_0D:{}
////			break;
////		case SCREEN_ROTATE_90D:{x1=R61509V_H-y;y=x;x=x1;}
////			break;
////		case SCREEN_ROTATE_180D:{x1=R61509V_H-x;y=R61509V_W-y;x=x1;}
////			break;
////		case	SCREEN_ROTATE_270D:{x1=y;y=R61509V_W-x;x=x1;}
////			break;
////		default: break;			
////	}

//	pR61509V->Display.WriteAddress(xsta,ysta,xend,yend);
//	pR61509V->Display.WriteDataStart();
//	for(i=0;i<xend-xsta;i++)
//	{
//		for(j=0;j<yend-ysta;j++)
//		{
//			pR61509V->Display.WriteData(color);
//		}
//	}
//	pR61509V->Display.WriteDataEnd();	
//}
///*******************************************************************************
//* 函数名			:	function
//* 功能描述		:	函数功能说明 
//* 输入			: void
//* 返回值			: void
//*******************************************************************************/
//void R61509V_ShowChar(
//										u16 x,			//x				:起点x坐标
//										u16 y,			//y				:起点y坐标
//										u8 font,		//font		:字体大小
//										u8 num,			//num			:字节数
//										u8 *Buffer	//Buffer	:显示的内容缓存
//)		//高通字库测试程序
//{
//	u8 temp;
//	u8 i=0,j=0;
//	unsigned short x1=0,x2=0,y1=0,y2=0;
//	u16 colortemp=R61509V_POINT_COLOR;
////	CoordinateTransform(&x1,&y1,&x2,&y2);
//	x1	=	x;
//	y1	=	y;
//	
//	if(font==12)
//	{
//		if(x>R61509V_V-12||y>R61509V_H-12)
//			return;
//		
//		x2	=	x+12-1;
//		y2	=	y+12;
////		R61509V_SetWindowAddress(x,y,x+12-1,y+12);      //设置光标位置 
//	}
//	if(font==16)
//	{
//		if(x>R61509V_V-16||y>R61509V_H-16)
//			return;
//		x2	=	x+16-1;
//		y2	=	y+16;
////		R61509V_SetWindowAddress(x,y,x+16-1,y+16);      //设置光标位置 
//	}
//	if(font==24)
//	{
//		if(x>R61509V_V-24||y>R61509V_H-24)
//			return;
//		x2	=	x+24-1;
//		y2	=	y+24;
////		R61509V_SetWindowAddress(x,y,x+24-1,y+24);      //设置光标位置 
//	}
//	else if(font==32)
//	{
//		if(x>R61509V_V-32||y>R61509V_H-32)
//			return;
//		if(num==128)
//		{
//			x2	=	x+32-1;
//			y2	=	y+32-1;
////			R61509V_SetWindowAddress(x,y,x+32-1,y+32);      //设置光标位置
//		}
//		else
//		{
//			x2	=	x+16-1;
//			y2	=	y+32;
////			R61509V_SetWindowAddress(x,y,x+16-1,y+32);      //设置光标位置 
//		}
//	}
//	else
//	{
////		return ;
//	}
////	CoordinateTransform(&x1,&y1,&x2,&y2);
//	R61509V_SetWindowAddress(x1,y1,x2,y2);      //设置光标位置
//	
//	i=0;
//	for(i=0;i<num;i++)
//	{ 
//		u16 R61509V_PEN_COLOR	=	R61509V_BLUE;   	//画笔色	
//		temp=Buffer[i];		 					//调用1608字体--二维数组形式--字库使用时取消 	
//		for(j=0;j<8;j++)
//		{
//			if((temp&0x80)==0X80)
//			{
//				R61509V_PEN_COLOR=R61509V_POINT_COLOR;
//			}
//			else
//				R61509V_PEN_COLOR=R61509V_BACK_COLOR;
//			
//			R61509V_WriteData16(R61509V_PEN_COLOR);
//			temp=temp<<1;
//		}
//		R61509V_POINT_COLOR=colortemp;	
//	}	
//}

///*******************************************************************************
//*函数名		:	R61509V_ShowChar
//*功能描述	:	在指定位置显示一个字符
//*输入			: x,y		:起点坐标
//						num		:要显示的字符:" "--->"~"
//						mode	:叠加方式(1)还是非叠加方式(0)
//						num		:要显示的字符:" "--->"~"
//*输出			:	无
//*返回值		:	无
//*例程			:
//*******************************************************************************/
//void R61509V_ShowCharT(u16 x,u16 y,u8 num,u8 mode)
//{
////	R61509V_BACK_COLOR	//背景色
////	R61509V_POINT_COLOR	//画笔色
//	u8 temp;
//	u8 pos,t;
//	u16 x0=x;
//	u16 colortemp=R61509V_POINT_COLOR; 
//	if(x>R61509V_V-16||y>R61509V_H-16)
//		return;	    
//	//设置窗口		   
//	num=num-' ';//得到偏移后的值
////	num=41;//得到偏移后的值
//	
//	
////	R61509V_SetWindowAddress(x,y,x+8-1,y+16-1);      //设置光标位置 
//	if(!mode) //非叠加方式
//	{
//		for(pos=0;pos<16;pos++)
//		{ 
//			temp=code_asc2_1608[(u16)num*16+pos];		 		//调用1608字体
////			temp=code_num_1608[(u16)num*16+pos];		 //调用1608字体
//			for(t=0;t<8;t++)
//			{                 
//				if((temp&0x01)==0x01)
//					R61509V_POINT_COLOR=colortemp;
//				else
//					R61509V_POINT_COLOR=R61509V_BACK_COLOR;

//				R61509V_DrawDot(x,y,R61509V_POINT_COLOR);//画一个点 
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
//					R61509V_DrawDot(x+t,y+pos,R61509V_POINT_COLOR);//画一个点     
//				temp>>=1; 
//			}
//		}
//	}
//	R61509V_POINT_COLOR=colortemp;	    	   	 	  
//}










///**************************************************************************************************
//* [Function] R61509V_DrawPixelEx:  函数功能、注意事项等的描述
//* [param01]u16 x: description
//* [param02]u16 y: description
//* [param03]u16 color: description
//**************************************************************************************************/
//void R61509V_DrawPixelEx( u16 x, u16 y, u16 color )
//{
//	R61509V_DrawDot(x,y,color);		//画点
//}























/*************************************************************************************************************************************************/
/*************************************************************************************************************************************************/
/*************************************************************************************************************************************************/
/*************************************************************************************************************************************************/
/*************************************************************************************************************************************************/







 
///*******************************************************************************
//*函数名			:	R61509V_Clean
//*功能描述		:	显示汉字程序
//*输入				: 
//*返回值			:	无
//*******************************************************************************/
//void R61509V_CHINESE(unsigned char zimo[720],unsigned int backcolor)  //写入字符
//{
//	unsigned char j,flag=0;
//	unsigned char *point;
//	unsigned int i,x1=0x00,x2=0x17,y1=0x00,y2=0x17;
//	unsigned int colors[10]=
//	{
//		0xf800,0x07e0,0x001f,0xffe0,0x0000,0x07ff,0xf81f,0xb81f,0x7f7,0xfec0
//	};
//	point=&zimo[0];
//	for(i=1;i<=720;i++,point++)
//	{  
//		for(j=0;j<=7;j++)
//		{
//			if((*point<<j)&0x80)
//			{
//				R61509V_WriteData16(colors[flag]);
//				R61509V_Delay(1);
//			}
//			else
//			{
//				R61509V_WriteData16(backcolor);
//				R61509V_Delay(1);
//			}
//		}   
//		if(i%72==0)
//		{
//			x1=x1+24;x2=x2+24;y1=y1+24;y2=y2+24;
//			flag=flag+1;
//			R61509V_SetWindowAddress(x1,y1,x2,y2);
//		}   
//	}
//}

///*******************************************************************************
//*函数名			:	R61509V_DrawPoint_big
//*功能描述		:	画一个大点
//*输入				: 
//*返回值			:	无
//*******************************************************************************/
//void R61509V_DrawDot_big(u16 x,u16 y,u16 color)
//{
////	if((x<=5)&&(y<=5))
////	{
////		R61509V_Fill(0,0,x+10,y+10,color);
////	}
////	else if((x>5)&&(y<=5))
////	{
////		R61509V_Fill(x-5,0,x+5,y+10,color);
////	}
////	else if((x<=5)&&(y>5))
////	{
////		R61509V_Fill(0,y-5,x+10,y+5,color);
////	}
////	else if((x>5)&&(y>5))
////	{
////		R61509V_Fill(x-5,y-5,x+5,y+5,color);
////	}
//	
//	if((x==0)&&(y==0))
//	{
//		R61509V_Fill(0,0,x+2,y+2,color);
//	}
//	else if((x>0)&&(y>0))
//	{
//		R61509V_Fill(x-1,y-1,x+1,y+1,color);
//	}
//	
////	R61509V_Fill(x-1,y-1,x+1,y+1,color);
//}





//#endif//R61509V_61509_EN
/************************************** The End Of FILE **************************************/


