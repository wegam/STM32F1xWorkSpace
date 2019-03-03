/**************************************************************************************************
* Copyright (C), 1997-2016,  HAICHUANG IOT Tech. Co., Ltd.
* 文件<Bsp_LcdLCD.h>
* 模块描述 :	定义、功能、说明
* 历史修改记录
*     <主要修改者>  <时间>   <版本 >   <说明>
*     xlyan        2016/9/26   1.0.0    创建文件
**************************************************************************************************/
#ifndef __LCD_H_
#define __LCD_H

#include "stm32f10x_type.h"
#include "stm32f10x_gpio.h"
#include "GT32L32M0180.H"

#include "STM32_PWM.H"



//#define	LCD_H 240		//水平方向点数，从左到右+
//#define LCD_V 400		//垂直方向点数，从上到下+


//****************************控制定义End**************************


typedef enum
{
	Draw_Rotate_0D = 0,
	Draw_Rotate_90D,
	Draw_Rotate_180D,
	Draw_Rotate_270D,
} eRotate;


typedef struct	_LCDPort
{
	//____________背光控制定义	//1:开背光;0:关背光
	GPIO_TypeDef* 	sBL_PORT;			//GPIOX
	unsigned short 	sBL_Pin;				//GPIO_Pin_x
	
	//____________读信号;0:读数据
	GPIO_TypeDef* 	sRD_PORT;							//GPIOX
	unsigned short 	sRD_Pin;							//GPIO_Pin_x
	
	//____________复位信号 1:运行;0:复位
	GPIO_TypeDef* 	sREST_PORT;						//GPIOX
	unsigned short 	sREST_Pin;						//GPIO_Pin_x
	
	//____________命令/数据：0：命令;1-数据	RS
	GPIO_TypeDef* 	sDC_PORT;							//GPIOX
	unsigned short 	sDC_Pin;							//GPIO_Pin_x
	
	//____________写信号 在WR的上升沿，使数据写入到LCD里面
	GPIO_TypeDef* 	sWR_PORT;							//GPIOX
	unsigned short 	sWR_Pin;							//GPIO_Pin_x
	
	//____________片选信号 0:片选;1:失能;
	GPIO_TypeDef* 	sCS_PORT;							//GPIOX
	unsigned short 	sCS_Pin;							//GPIO_Pin_x
	
	//____________TE
	GPIO_TypeDef* 	sTE_PORT;							//GPIOX
	unsigned short 	sTE_Pin;							//GPIO_Pin_x
	
	//____________数据接口
	GPIO_TypeDef* 	sDATABUS_PORT;				//GPIOX
	unsigned short 	sDATABUS_Pin;					//GPIO_Pin_x

}LCDPortDef;
typedef struct	_LCDData
{
	unsigned short	MaxH;						//水平最大点数----初始化需要配置参数
	unsigned short 	MaxV;						//垂直最大点数----初始化需要配置参数
	unsigned short	HSX;						//水平起始点
	unsigned short 	HEX;						//水平终止点
	unsigned short	VSY;						//垂直起始点
	unsigned short 	VEY;						//垂直终止点
	unsigned short	HXA;						//RAM Address Set (Horizontal Address) (R200h)
	unsigned short 	VYA;						//RAM Address Set (Vertical Address) (R201h)
	unsigned short 	PColor;					//画笔颜色
	unsigned short 	BColor;					//背景颜色
  unsigned long   FsmcDataAddr;  //FSMC写数据地址
  unsigned long   FsmcRegAddr;   //FSMC写寄存器地址
}LCDDataDef;
typedef struct	_LCDFlag		//0为无标识
{
	eRotate	Rotate;						//扫描方式/旋转角度
}LCDFlagDef;
typedef struct _DisplayDriver
{
	//------------------待删除
	void ( *WriteAddress )( unsigned short HSX,unsigned short HSY,unsigned short HEX,unsigned short HEY);
	void ( *WriteIndex)(unsigned short Index);
  void ( *WriteData)(unsigned short Data);
  void ( *WriteCommand)(unsigned short Index,unsigned short Command);
	
	void ( *LcdBackLightOn )(void);
  void ( *LcdBackLightOff )(void);
	
	//---------------------------
	void ( *PowerOn )(void);
	void ( *PowerOff )(void);
	void ( *DispOff )(void);	 
	
	void ( *DrawDot)(unsigned short HSX,unsigned short HSY,unsigned short color);		//画点
	void ( *DrawLine)(u16 x1,u16 y1,u16 x2,u16 y2,u16 color);						//AB 两个坐标画一条直线
	void ( *DrawCircle)(u16 x1,u16 y1, u16 R, u8 Filled, u16 color );		//画一个圆形框
	void ( *DrawRectangle)(u16 x1,u16 y1,u16 x2,u16 y2,u16 color);				//画一个矩形框
	
	void ( *Fill )(u16 xsta,u16 ysta,u16 xend,u16 yend,u16 color);				//在指定区域内填充指定颜色;区域大小:(xend-xsta)*(yend-ysta)
	void ( *Clean)(u16 Color);								//清除屏幕函数;
	void ( *SetBackground)(u16 BackColor );
	
	//--------------------------------------------字符显示
	void ( *ShowChar)(u16 x,u16 y,u8 font,u16 color,u8 num,u8 *Buffer);	  //高通字库测试程序
	void ( *ShowWord)(u16 x,u16 y,u8 font,u16 color,u8 num,u8 *Buffer);	  //高通字库测试程序

}DisplayDriverDef;
typedef struct	_LCD
{
	LCDPortDef				Port;
	LCDDataDef				Data;
	LCDFlagDef				Flag;
	DisplayDriverDef	Display;
	GT32L32Def				GT32L32;
}LCDDef;

typedef struct	_stLCDScroll
{
	unsigned short	startx;				//起始显示x坐标
	unsigned short	starty;				//起始显示y坐标
	unsigned short	color;				//显示颜色
	unsigned short	length;				//显示内容长度.
	unsigned short	runxstart;		//从第几个字符开始显示
	unsigned char		font;					//显示字号
	unsigned char		buffer[100];	//显示内容
	unsigned long*	nextlist;			//下一个显示内容地址
}stLCDScroll;

extern LCDDef *LCDSYS;			//内部驱动使用，不可删除

#define	pLcdPort	(&(LCDSYS->Port))

#define LCD_CS_HIGH					(pLcdPort->sCS_PORT->BSRR		= pLcdPort->sCS_Pin)
#define LCD_CS_LOW					(pLcdPort->sCS_PORT->BRR 		= pLcdPort->sCS_Pin)
#define LCD_DC_HIGH					(pLcdPort->sDC_PORT->BSRR 		= pLcdPort->sDC_Pin)		//RS
#define LCD_DC_LOW					(pLcdPort->sDC_PORT->BRR 		= pLcdPort->sDC_Pin)		//RS
#define LCD_WR_HIGH					(pLcdPort->sWR_PORT->BSRR 		= pLcdPort->sWR_Pin)
#define LCD_WR_LOW					(pLcdPort->sWR_PORT->BRR 		= pLcdPort->sWR_Pin)
#define LCD_RD_HIGH					(pLcdPort->sRD_PORT->BSRR 		= pLcdPort->sRD_Pin)
#define LCD_RD_LOW					(pLcdPort->sRD_PORT->BRR 		= pLcdPort->sRD_Pin)
#define LCD_RST_HIGH				(pLcdPort->sREST_PORT->BSRR	= pLcdPort->sREST_Pin)
#define LCD_RST_LOW					(pLcdPort->sREST_PORT->BRR 	= pLcdPort->sREST_Pin)
#define LCD_TE_HIGH					(pLcdPort->sTE_PORT->BSRR 		= pLcdPort->sTE_Pin)
#define LCD_TE_LOW					(pLcdPort->sTE_PORT->BRR 		= pLcdPort->sTE_Pin)
#define LCD_DATABUS_PORT		(pLcdPort->sDATABUS_PORT)
#define LCD_DATABUS_Pin			(pLcdPort->sDATABUS_Pin)

#define LCD_RS_HIGH					LCD_DC_HIGH
#define LCD_RS_LOW					LCD_DC_LOW

#if 1
	#define LCD_BL_ON		PWM_OUT((TIM_TypeDef*) TIM2_BASE,PWM_OUTChannel4,1000,100)	//(R61509V_BL_PORT->BSRR = R61509V_BL_PIN)
	#define LCD_BL_OFF	PWM_OUT((TIM_TypeDef*) TIM2_BASE,PWM_OUTChannel4,5,0)		//(R61509V_BL_PORT->BRR = R61509V_BL_PIN)
//	#define LCD_BL_ON		PWM_OUT((TIM_TypeDef*) TIM3_BASE,PWM_OUTChannel3,2000,10)	//(R61509V_BL_PORT->BSRR = R61509V_BL_PIN)
//	#define LCD_BL_OFF	PWM_OUT((TIM_TypeDef*) TIM3_BASE,PWM_OUTChannel3,5,0)		//(R61509V_BL_PORT->BRR = R61509V_BL_PIN)
#else
	#define LCD_BL_ON		(pLcdPort->sBL_PORT->BSRR = pLcdPort->sBL_Pin)
	#define LCD_BL_OFF	(pLcdPort->sBL_PORT->BRR 	= pLcdPort->sBL_Pin)

#endif


#define LCD_PHY_WIDTH	( (u16) 240)
#define LCD_PHY_HEIGHT	( (u16) 400)
#define LCD_TOTAL_PIX	96000   /*240 * 400 */

#define LCD_DISP_ANGLE	GUI_DISP_ANGLE
#define LCD_START_LINE	0       /*the partial image 1 is displayed from the first line of the base image. */
#define LCD_LINE_NUM	LCD_PHY_HEIGHT

//#define LCD_FORE_COLOR	0x31a6
//#define LCD_BACK_COLOR	0xef5d
//#define LCD_FORE_COLOR	0xef5d 		//前景色
//#define LCD_BACK_COLOR	0x0000		//背景色

#define LCD_ALARM_COLOR  0xF800
#define LCD_TRANSPARENT_COLOR 0xFFFF


//画笔颜色
#define LCD565_WHITE     	0xFFFF
#define LCD565_BLACK     	0x0000	  
#define LCD565_BLUE      	0x001F  
#define LCD565_BRED      	0XF81F
#define LCD565_GRED 			0XFFE0
#define LCD565_GBLUE			0X07FF
#define LCD565_RED       	0xF800
#define LCD565_MAGENTA   	0xF81F
#define LCD565_GREEN     	0x07E0	//0X07E0
#define LCD565_CYAN      	0x7FFF
#define LCD565_YELLOW    	0xFFE0
#define LCD565_BROWN 			0XBC40 	//棕色
#define LCD565_BRRED 			0XFC07 	//棕红色
#define LCD565_GRAY  			0X8430 	//灰色
#define LCD565_DARKBLUE  	0X01CF	//深蓝色
#define LCD565_LIGHTBLUE 	0X7D7C	//浅蓝色  
#define LCD565_GRAYBLUE  	0X5458 	//灰蓝色
#define LCD565_LIGHTGREEN	0X841F 	//浅绿色
#define LCD565_LGRAY 			0XC618 	//浅灰色(PANNEL),窗体背景色
#define LCD565_LGRAYBLUE 	0XA651 	//浅灰蓝色(中间层颜色)
#define LCD565_LBBLUE    	0X2B12 	//浅棕蓝色(选择条目的反色)
#define LCD565_UNKNOW    	0X2B20 	//测试颜色


//======================================外部接口
unsigned short LCD_Initialize(LCDDef *pInfo);
void LCDFsmc_Initialize(LCDDef *pInfo);
void LCD_DisplayServer(void);

void LCD_ShowAntenna(u16 x,u16 y,u8 Num,u16 PenColor);   //显示12x12天线
void LCD_ShowBattery(u16 x,u16 y,u8 Num,u16 PenColor); 	//显示12x12电池
void LCD_Show(u16 x,u16 y,u8 font,u16 PenColor,u8 num,u8 *Buffer);	
void LCD_ShowScroll(stLCDScroll	*ScrollBuff);	
void LCD_ShowHex(u16 x,u16 y,u8 font,u16 color,u8 num,u8 bitnum,u8 *Buffer);    //显示十六进制数据
unsigned int LCD_Printf(u16 x,u16 y,u8 font,u16 color,const char *format,...);  //LCD打印内容
unsigned int LCD_PrintfScroll(u16 x,u16 y,u8 font,u16 color,const char *format,...);  //LCD滚动打印内容
void LCD_ShowBMP(u16 xsta,u16 ysta,u16 xend,u16 yend,u16 Length,u8 *RGBBuffer);    //显示十六进制数据
unsigned  short RGB888toRGB565(u8 *RGB888);

//======================================内部底层函数
void LCD_Reset(void);

void LCD_WriteIndex( unsigned short Index );		//GPIO方式写地址
void LCD_WriteData(u16 Data);										//GPIO方式写数据					
void LCDFsmc_WriteIndex(unsigned short Index);	//FSMC方式写地址
void LCDFsmc_WriteData(unsigned short Data);		//FSMC方式写数据
void LCD_WriteCommand(unsigned short index,unsigned short Command);		//写完整控制命令
u16 LCD_ReadData( unsigned short Index );				//读数据

void LCD_WriteRegister(unsigned	short	Index,unsigned short Data);
unsigned short LCD_ReadRegister(unsigned	short	Index);

void LCD_Clean(u16 COLOR);	//清除屏幕函数
void LCD_DrawDot(unsigned short HSX,unsigned short HSY,unsigned short color);		//画点
void LCD_DrawLine(u16 x1,u16 y1,u16 x2,u16 y2,u16 color);						//AB 两个坐标画一条直线
void LCD_DrawCircle(u16 x1,u16 y1, u16 R, u8 Filled, u16 color );		//画一个圆形框
void LCD_DrawRectangle(u16 x1,u16 y1,u16 x2,u16 y2,u16 color);				//画一个矩形框

void LCD_Fill(u16 xsta,u16 ysta,u16 xend,u16 yend,u16 color);				//在指定区域内填充指定颜色;区域大小:(xend-xsta)*(yend-ysta)
void LCD_SetBackground(u16 BackColor );
void LCD_ShowChar(u16 x,u16 y,u8 font,u16 color,u8 num,u8 *Buffer);	  //高通字库测试程序
void LCD_ShowWord(u16 x,u16 y,u8 font,u16 color,u8 num,u8 *Buffer);	  //高通字库测试程序
unsigned short LCD_GetDispCodeBuffer(u8 font,u16 word,u8 *ReadBuffer);	//获取显示的内容

//======================================延时函数
void LCD_DelayuS(u32 xuS);
void LCD_DelaymS(u32 xmS);
void LCD_DelayS(u32 xS);
#endif//_BSP_LCDLCD_H_2016_
/************************************** The End Of FILE **************************************/
