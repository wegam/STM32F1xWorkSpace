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
	
	//____________命令/数据：0：命令;1-数据
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
}LCDDataDef;
typedef struct	_LCDFlag		//0为无标识
{
	eRotate	Rotate;						//扫描方式/旋转角度
}LCDFlagDef;
typedef struct _DisplayDriver
{
	void ( *WriteAddress )( unsigned short HSX,unsigned short HSY,unsigned short HEX,unsigned short HEY);
	
	void ( *PowerOn )(void);
	void ( *PowerOff )(void);
	void ( *DispOff )(void);
  void ( *BackLightOn )(void);
  void ( *BackLightOff )(void);

}DisplayDriverDef;
typedef struct	_LCD
{
	LCDPortDef				Port;
	LCDDataDef				Data;
	LCDFlagDef				Flag;
	DisplayDriverDef	Display;
	GT32L32Def				GT32L32;
}LCDDef;


extern LCDDef *LCDSYS;			//内部驱动使用，不可删除

#define	pLcdPort	(&(LCDSYS->Port))

#define LCD_CS_HIGH					(pLcdPort->sCS_PORT->BSRR		= pLcdPort->sCS_Pin)
#define LCD_CS_LOW					(pLcdPort->sCS_PORT->BRR 		= pLcdPort->sCS_Pin)
#define LCD_DC_HIGH					(pLcdPort->sDC_PORT->BSRR 	= pLcdPort->sDC_Pin)
#define LCD_DC_LOW					(pLcdPort->sDC_PORT->BRR 		= pLcdPort->sDC_Pin)
#define LCD_WR_HIGH					(pLcdPort->sWR_PORT->BSRR 	= pLcdPort->sWR_Pin)
#define LCD_WR_LOW					(pLcdPort->sWR_PORT->BRR 		= pLcdPort->sWR_Pin)
#define LCD_RD_HIGH					(pLcdPort->sRD_PORT->BSRR 	= pLcdPort->sRD_Pin)
#define LCD_RD_LOW					(pLcdPort->sRD_PORT->BRR 		= pLcdPort->sRD_Pin)
#define LCD_RST_HIGH				(pLcdPort->sREST_PORT->BSRR	= pLcdPort->sREST_Pin)
#define LCD_RST_LOW					(pLcdPort->sREST_PORT->BRR 	= pLcdPort->sREST_Pin)
#define LCD_TE_HIGH					(pLcdPort->sTE_PORT->BSRR 	= pLcdPort->sTE_Pin)
#define LCD_TE_LOW					(pLcdPort->sTE_PORT->BRR 		= pLcdPort->sTE_Pin)
#define LCD_DATABUS_PORT		(pLcdPort->sDATABUS_PORT)

#if 0
	#define LCD_BL_ON		PWM_OUT((TIM_TypeDef*) TIM2_BASE,PWM_OUTChannel4,2000,500)	//(R61509V_BL_PORT->BSRR = R61509V_BL_PIN)
	#define LCD_BL_OFF	PWM_OUT((TIM_TypeDef*) TIM2_BASE,PWM_OUTChannel4,5,0)		//(R61509V_BL_PORT->BRR = R61509V_BL_PIN)
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









/*功能位 */
#define LCD_DC1_IMAGE_ENABLE_BIT	0x1000
#define LCD_DC1_PARTIAL_ENABLE_BIT	0x0100

#define LCD_R000_IR			( (u16) 0x0000) 	//Device code read Index (IR)/*[10:0]REG ID */
#define LCD_R000_DCR		( (u16) 0x0000) 	//Device code read (R000h)/*[15:0]	B509H Read */			//Device code read
#define LCD_R001_DOC		( (u16) 0x0001) 	//Driver Output Control (R001h)/*[8]SS,[10]SM */
#define LCD_R002_DWC		( (u16) 0x0002) 	//LCD Drive Wave Control (R002h)/*[8]BC */
#define LCD_R003_EM			( (u16) 0x0003) 	//Entry Mode (R003h)/*[3]AM,[5:4]ID,[7]ORG,[12]BGR,[14]DFM,[15]TRI */
#define LCD_R007_DC1		( (u16) 0x0007) 	//Display Control 1 (R007h)/*[8]BASEE,[12]PTDE */
#define LCD_R008_DC2		( (u16) 0x0008) 	//Display Control 2 (R008h)/*[15:8]FP,[7:0]BP */
#define LCD_R009_DC3		( (u16) 0x0009) 	//Display Control 3 (R009h)/*[10]PTS,[11]PTV */
#define LCD_R00B_ECC		( (u16) 0x000B)		//Eight Color Control (R00Bh) /*[0]COL */
#define LCD_R00C_EDIC1	( (u16) 0x000C) 	//External Display Interface Control 1 (R00Ch)/*[0]RIM,[5:4]DM,[8]RM,[14:12]ENC */
#define LCD_R00F_EDIC2	( (u16) 0x000F) 	//External Display Interface Control 2 (R00Fh)//*[0]DPL,[1]EPL,[3]HSPL,[4]VSPL */
#define LCD_R010_PIC1		( (u16) 0x0010) 	//Panel Interface Control 1 (R010h)	/*[5:0]RTNI,[]DIV */
#define LCD_R011_PIC2		( (u16) 0x0011) 	//Panel Interface Control 2 (R011h)	/*[2:0]STDI,[10:8]NOWI */
#define LCD_R012_PIC3		( (u16) 0x0012) 	//Panel Interface Control 3 (R012h)	/*[2:0]SEQWI,[10:8]VEQWI */
#define LCD_R013_PIC4		( (u16) 0x0013) 	//Panel Interface Control 4 (R013h)	/*[2:0]MCPI */
#define LCD_R014_PIC5		( (u16) 0x0014) 	//Panel Interface Control 5 (R014h)	/*[2:0]PCDIVL,[10:8]PCDIVH */
#define LCD_R020_PIC6		( (u16) 0x0020) 	//Panel Interface Control 6 (R020h)	/*[] */
#define LCD_R021_PIC7		( (u16) 0x0021) 	//Panel Interface Control 7 (R021h)	/*[2:0]STDE,[10:8]NOWE */
#define LCD_R022_PIC8		( (u16) 0x0022) 	//Panel Interface Control 8 (R022h)	/*[2:0]SEQWE,[10:8]VEQWE */
#define LCD_R023_PIC9		( (u16) 0x0023) 	//Panel Interface Control 9 (R023h)	/*[7:0]MCPE */
#define LCD_R090_FMC		( (u16) 0x0090) 	//Frame Marker Control (R090h)	/*[8:0]FMP,[14:12]FMI,[15]FMKM */
#define LCD_R100_PC1		( (u16) 0x0100) 	//Power Control 1 (R100h)	/*[2]DSTB,[5:4]AP,[10:8]BT */
#define LCD_R101_PC2		( (u16) 0x0101)		//Power Control 2 (R101h) /*[2:0]VC,[6:4]DCO,[10:8]DC1 */
#define LCD_R102_PC3		( (u16) 0x0102) 	//Power Control3 (R102h)	/*[4]PON,[5]PSON,[8]VCMR,[15:11]VRH */
#define LCD_R103_PC4		( (u16) 0x0103) 	//Power Control 4 (R103h)	/*[12:8]VDV */
#define LCD_R200_HA			( (u16) 0x0200)		//RAM Address Set (Horizontal Address) (R200h)	 /*[7:0] */
#define LCD_R201_VA			( (u16) 0x0201) 	//RAM Address Set (Vertical Address) (R201h)	/*[8:0] */
#define LCD_R202_GDRW		( (u16) 0x0202)		//GRAM Data Write (R202h)/GRAM Data Read (R202h)
#define LCD_R280_NVM		( (u16) 0x0280) 	//NVM Data Read / NVM Data Write (R280h)	/*[7:0]UID,[14:8]VCM */
#define LCD_R210_HSA		( (u16) 0x0210) 	//Window Horizontal RAM Address Start (R210h)		/*[7:0] */
#define LCD_R211_HEA		( (u16) 0x0211) 	//Window Horizontal RAM Address End(R211h)	/*[7:0] */
#define LCD_R212_VSA		( (u16) 0x0212)		//Window Vertical RAM Address Start (R212h) /*[8:0] */
#define LCD_R213_VEA		( (u16) 0x0213) 	//Window Vertical RAM Address End (R213h)	/*[8:0] */
#define LCD_R300_YC1		( (u16) 0x0300)		//γ Control 1(R300)	
#define LCD_R301_YC2		( (u16) 0x0301)		//γ Control 2(R301)	
#define LCD_R302_YC3		( (u16) 0x0302)		//γ Control 3(R302)	
#define LCD_R303_YC4		( (u16) 0x0303)		//γ Control 4(R303)	
#define LCD_R304_YC5		( (u16) 0x0304)		//γ Control 5(R304)	
#define LCD_R305_YC6		( (u16) 0x0305)		//γ Control 6(R305)	
#define LCD_R306_YC7		( (u16) 0x0306)		//γ Control 7(R306)	
#define LCD_R307_YC8		( (u16) 0x0307)		//γ Control 8(R307)	
#define LCD_R308_YC9		( (u16) 0x0308)		//γ Control 9(R308)	
#define LCD_R309_YC10		( (u16) 0x0309)		//γ Control 10(R309)	
#define LCD_R400_BINL		( (u16) 0x0400)		//Base Image Number of Line (R400h) /*[15]GS,[14:9]NL,[6:1]SCN */
#define LCD_R401_BIDC		( (u16) 0x0401) 	//Base Image Display Control (R401h)	/*[2]NDL,[1]VLE,[0]REV */
#define LCD_R404_BIVSC	( (u16) 0x0404) 	//Base Image Vertical Scroll Control (R404h)	/*[8:0]VL */
#define LCD_R500_PTDP		( (u16) 0x0500) 	//Display Position (R500h)	/*[8:0] */
#define LCD_R501_PTSA		( (u16) 0x0501) 	//RAM Address 1 (Start Line Address) (R501h)	/*[8:0] */
#define LCD_R502_PTEA		( (u16) 0x0502) 	//RAM Address 1 (End Line Address) (R502h)	/*[8:0] */
#define LCD_R600_TR			( (u16) 0x0600) 	//Test Register (Software Reset) (R600h)	/*[0]TRSR */
#define LCD_R6F0_NVMC1	( (u16) 0x06F0)  	//NVM Access Control 1 (R6F0h),	/*[5:4]EOP,[6]CALB,[7]TE */
#define LCD_R6F1_NVMC2	( (u16) 0x06F1)  	//NVM Access Control 2 (R6F1h),	/*[15:0]NVDAT */
#define LCD_R6F2_NVMC3	( (u16) 0x06F2)  	//NVM Access Control 3 (R6F2h)/*[3]NVVRF */



//======================================外部接口
void LCD_Initialize(LCDDef *pInfo);
void LCD_ShowAntenna(u16 x,u16 y,u8 Num,...);   //显示12x12天线
void LCD_ShowBattery(u16 x,u16 y,u8 Num,u16 color);   //显示12x12电池
void LCD_Show(u16 x,u16 y,u8 font,u8 num,u8 *Buffer);	
void LCD_ShowHex(u16 x,u16 y,u8 font,u8 num,u8 bitnum,u8 *Buffer);                //显示十六进制数据
unsigned int LCD_Printf(u16 x,u16 y,u8 font,u16 color,const char *format,...);		//后边的省略号就是可变参数


//======================================内部函数
void LCD_WriteIndexStart( void );
void LCD_WriteIndexEnd( void );
void LCD_WriteIndex( unsigned short Index );
void LCD_WriteDataStart( void );
void LCD_WriteDataEnd( void );
void LCD_WriteData(u16 Data);
u16 LCD_ReadData( void );
void LCD_WriteCommand(unsigned short index,unsigned short Command);	//写完整控制命令

void LCD_Clean(u16 COLOR);	//清除屏幕函数
void LCD_DrawDot(unsigned short HSX,unsigned short HSY,unsigned short color);		//画点
void LCD_DrawLine(u16 x1,u16 y1,u16 x2,u16 y2,u16 color);						//AB 两个坐标画一条直线
void LCD_DrawCircle(u16 x1,u16 y1, u16 R, u8 Filled, u16 color );		//画一个圆形框
void LCD_DrawRectangle(u16 x1,u16 y1,u16 x2,u16 y2,u16 color);			//画一个矩形框

void LCD_Fill(u16 xsta,u16 ysta,u16 xend,u16 yend,u16 color);				//在指定区域内填充指定颜色;区域大小:(xend-xsta)*(yend-ysta)
void LCD_SetBackground(u16 BackColor );
void LCD_ShowChar(u16 x,u16 y,u8 font,u8 num,u8 *Buffer,u16 color);	  //高通字库测试程序
void LCD_ShowWord(u16 x,u16 y,u8 font,u8 num,u8 *Buffer,u16 color);	  //高通字库测试程序





void LCD_Delay(u32 xms);
#endif//_BSP_LCDLCD_H_2016_
/************************************** The End Of FILE **************************************/
