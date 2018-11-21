/**************************************************************************************************
* Copyright (C), 1997-2016,  HAICHUANG IOT Tech. Co., Ltd.
* 文件<Bsp_LcdILI9326.h>
* 模块描述 :	定义、功能、说明
* 历史修改记录
*     <主要修改者>  <时间>   <版本 >   <说明>
*     xlyan        2016/9/26   1.0.0    创建文件
**************************************************************************************************/
#ifndef __ILI9326_H_
#define __ILI9326_H_

#include "stm32f10x_type.h"
#include "stm32f10x_gpio.h"

//#include "LCD.H"

#define	ILI9326_H 240		//水平方向点数，从左到右+
#define ILI9326_V 400		//垂直方向点数，从上到下+

#define	ILI9326ID	(unsigned short)0x9326		//芯片型号标识
	

//****************************寄存器**************************
#define ILI9326_R000_IR			( (u16) 0x0000) 	//Index (IR)/*[10:0]REG ID */
#define ILI9326_R000_DCR		( (u16) 0x0000) 	//Device code read (R000h)/*[15:0]	B509H Read */			//Device code read
#define ILI9326_R001_DOC		( (u16) 0x0001) 	//Driver Output Control (R001h)/*[8]SS,[10]SM */
#define ILI9326_R002_DWC		( (u16) 0x0002) 	//LCD Drive Wave Control (R002h)/*[8]BC */
#define ILI9326_R003_EM			( (u16) 0x0003) 	//Entry Mode (R003h)/*[3]AM,[5:4]ID,[7]ORG,[12]BGR,[14]DFM,[15]TRI */
#define ILI9326_R007_DC1		( (u16) 0x0007) 	//Display Control 1 (R007h)/*[8]BASEE,[12]PTDE */
#define ILI9326_R008_DC2		( (u16) 0x0008) 	//Display Control 2 (R008h)/*[15:8]FP,[7:0]BP */
#define ILI9326_R009_DC3		( (u16) 0x0009) 	//Display Control 3 (R009h)/*[10]PTS,[11]PTV */
#define ILI9326_R00B_ECC		( (u16) 0x000B)		//Eight Color Control (R00Bh) /*[0]COL */
#define ILI9326_R00C_EDIC1	( (u16) 0x000C) 	//External Display Interface Control 1 (R00Ch)/*[0]RIM,[5:4]DM,[8]RM,[14:12]ENC */
#define ILI9326_R00F_EDIC2	( (u16) 0x000F) 	//External Display Interface Control 2 (R00Fh)//*[0]DPL,[1]EPL,[3]HSPL,[4]VSPL */
#define ILI9326_R010_PIC1		( (u16) 0x0010) 	//Panel Interface Control 1 (R010h)	/*[5:0]RTNI,[]DIV */
#define ILI9326_R011_PIC2		( (u16) 0x0011) 	//Panel Interface Control 2 (R011h)	/*[2:0]STDI,[10:8]NOWI */
#define ILI9326_R012_PIC3		( (u16) 0x0012) 	//Panel Interface Control 3 (R012h)	/*[2:0]SEQWI,[10:8]VEQWI */
#define ILI9326_R013_PIC4		( (u16) 0x0013) 	//Panel Interface Control 4 (R013h)	/*[2:0]MCPI */
#define ILI9326_R014_PIC5		( (u16) 0x0014) 	//Panel Interface Control 5 (R014h)	/*[2:0]PCDIVL,[10:8]PCDIVH */
#define ILI9326_R020_PIC6		( (u16) 0x0020) 	//Panel Interface Control 6 (R020h)	/*[] */
#define ILI9326_R021_PIC7		( (u16) 0x0021) 	//Panel Interface Control 7 (R021h)	/*[2:0]STDE,[10:8]NOWE */
#define ILI9326_R022_PIC8		( (u16) 0x0022) 	//Panel Interface Control 8 (R022h)	/*[2:0]SEQWE,[10:8]VEQWE */
#define ILI9326_R023_PIC9		( (u16) 0x0023) 	//Panel Interface Control 9 (R023h)	/*[7:0]MCPE */
#define ILI9326_R090_FMC		( (u16) 0x0090) 	//Frame Marker Control (R090h)	/*[8:0]FMP,[14:12]FMI,[15]FMKM */
#define ILI9326_R100_PC1		( (u16) 0x0100) 	//Power Control 1 (R100h)	/*[2]DSTB,[5:4]AP,[10:8]BT */
#define ILI9326_R101_PC2		( (u16) 0x0101)		//Power Control 2 (R101h) /*[2:0]VC,[6:4]DCO,[10:8]DC1 */
#define ILI9326_R102_PC3		( (u16) 0x0102) 	//Power Control3 (R102h)	/*[4]PON,[5]PSON,[8]VCMR,[15:11]VRH */
#define ILI9326_R103_PC4		( (u16) 0x0103) 	//Power Control 4 (R103h)	/*[12:8]VDV */
#define ILI9326_R200_HA			( (u16) 0x0200)		//RAM Address Set (Horizontal Address) (R200h)	 /*[7:0] */
#define ILI9326_R201_VA			( (u16) 0x0201) 	//RAM Address Set (Vertical Address) (R201h)	/*[8:0] */
#define ILI9326_R202_GDRW		( (u16) 0x0202)		//GRAM Data Write (R202h)/GRAM Data Read (R202h)
#define ILI9326_R280_NVM		( (u16) 0x0280) 	//NVM Data Read / NVM Data Write (R280h)	/*[7:0]UID,[14:8]VCM */

#define ILI9326_R281_VHV		( (u16) 0x0281) /*[0:5]VCM */
#define ILI9326_R290_OVPC		( (u16) 0x0290) /*[0:5]OTP,[11]VCM_PGM_EN [15]UID_PGM_en */
#define ILI9326_R291_OVPE		( (u16) 0x0291) /*[1]VCM_EN,[8-13]VCM [14-15]PGM_CNT */
#define ILI9326_R295_OPIK		( (u16) 0x0295) 

#define ILI9326_R210_HSA		( (u16) 0x0210) 	//Window Horizontal RAM Address Start (R210h)		/*[7:0] */
#define ILI9326_R211_HEA		( (u16) 0x0211) 	//Window Horizontal RAM Address End(R211h)	/*[7:0] */
#define ILI9326_R212_VSA		( (u16) 0x0212)		//Window Vertical RAM Address Start (R212h) /*[8:0] */
#define ILI9326_R213_VEA		( (u16) 0x0213) 	//Window Vertical RAM Address End (R213h)	/*[8:0] */

#define ILI9326_R300_YC1		( (u16) 0x0300)		//γ Control 1(R300)	
#define ILI9326_R301_YC2		( (u16) 0x0301)		//γ Control 2(R301)	
#define ILI9326_R302_YC3		( (u16) 0x0302)		//γ Control 3(R302)	
#define ILI9326_R303_YC4		( (u16) 0x0303)		//γ Control 4(R303)	
#define ILI9326_R304_YC5		( (u16) 0x0304)		//γ Control 5(R304)	
#define ILI9326_R305_YC6		( (u16) 0x0305)		//γ Control 6(R305)	
#define ILI9326_R306_YC7		( (u16) 0x0306)		//γ Control 7(R306)	
#define ILI9326_R307_YC8		( (u16) 0x0307)		//γ Control 8(R307)	
#define ILI9326_R308_YC9		( (u16) 0x0308)		//γ Control 9(R308)	
#define ILI9326_R309_YC10		( (u16) 0x0309)		//γ Control 10(R309)	
#define ILI9326_R400_BINL		( (u16) 0x0400)		//Base Image Number of Line (R400h) /*[15]GS,[14:9]NL,[6:1]SCN */
#define ILI9326_R401_BIDC		( (u16) 0x0401) 	//Base Image Display Control (R401h)	/*[2]NDL,[1]VLE,[0]REV */
#define ILI9326_R404_BIVSC	( (u16) 0x0404) 	//Base Image Vertical Scroll Control (R404h)	/*[8:0]VL */
#define ILI9326_R500_PTDP		( (u16) 0x0500) 	//Display Position (R500h)	/*[8:0] */
#define ILI9326_R501_PTSA		( (u16) 0x0501) 	//RAM Address 1 (Start Line Address) (R501h)	/*[8:0] */
#define ILI9326_R502_PTEA		( (u16) 0x0502) 	//RAM Address 1 (End Line Address) (R502h)	/*[8:0] */
#define ILI9326_R503_PIDP		( (u16) 0x0503) /*[0:7]PTD,[8] PTS*/
#define ILI9326_R504_PIRS		( (u16) 0x0504) /*[0:8] PTS*/
#define ILI9326_R505_PIRE		( (u16) 0x0505) /*[0:8]PTE*/
#define ILI9326_R600_TR			( (u16) 0x0600) 	//Test Register (Software Reset) (R600h)	/*[0]TRSR */
#define ILI9326_R6F0_NVMC1	( (u16) 0x06F0)  	//NVM Access Control 1 (R6F0h),	/*[5:4]EOP,[6]CALB,[7]TE */
#define ILI9326_R6F1_NVMC2	( (u16) 0x06F1)  	//NVM Access Control 2 (R6F1h),	/*[15:0]NVDAT */
#define ILI9326_R6F2_NVMC3	( (u16) 0x06F2)  	//NVM Access Control 3 (R6F2h)/*[3]NVVRF */
#define ILI9326_R702_SIT1    ( (u16) 0x0702) /*Set internal timing */
#define ILI9326_R705_SIT2    ( (u16) 0x0705) /*Set internal timing */
#define ILI9326_R70B_SIT3    ( (u16) 0x070B) /*Set internal timing */


unsigned short ILI9326_Initialize(void*	pInfo);


//--------------------------------------------驱动层
void ILI9326_Reset(void);
unsigned short ILI9326_ReadData(void);
unsigned short ILI9326_ReadRegister(unsigned	short	Index);

void ILI9326_WriteData(unsigned	short	Data);
void ILI9326_WriteAddr(unsigned	short	Addr);
void ILI9326_WriteIndex(unsigned	short	Index);
void ILI9326_WriteRegister(unsigned	short	Addr,unsigned short Data);
void ILI9326_WriteCommand(unsigned	short	Index,unsigned short Cmd);

void ILI9326_WriteGRAM(unsigned	short* RAM,unsigned long length);
void ILI9326_ReadGRAM(unsigned	short* RAM,unsigned long length);
//--------------------------------------------接口层
void ILI9326_PowerOn( void );			//LCD 上电并初始化相关寄存器
void ILI9326_PowerOff( void );		//关闭LCD 电源
void ILI9326_SetWindowAddress(unsigned short x1,unsigned short y1,unsigned short x2,unsigned short y2);//设置窗地址

//--------------------------------------------GUI
void ILI9326_DrawDot(unsigned short HSX,unsigned short HSY,unsigned short color);		//画点
void ILI9326_DrawLine(u16 x1,u16 y1,u16 x2,u16 y2,u16 color);						//AB 两个坐标画一条直线
void ILI9326_DrawCircle(u16 x1,u16 y1, u16 R, u8 Filled, u16 color );		//画一个圆形框
void ILI9326_DrawRectangle(u16 x1,u16 y1,u16 x2,u16 y2,u16 color);				//画一个矩形框

void ILI9326_Fill(u16 xsta,u16 ysta,u16 xend,u16 yend,u16 color);				//在指定区域内填充指定颜色;区域大小:(xend-xsta)*(yend-ysta)
void ILI9326_Clean(u16 Color);	//清除屏幕函数;
void ILI9326_SetBackground(u16 BackColor );

//--------------------------------------------字符显示
void ILI9326_ShowChar(u16 x,u16 y,u8 font,u16 color,u8 num,u8 *Buffer);	  //高通字库测试程序
void ILI9326_ShowWord(u16 x,u16 y,u8 font,u16 color,u8 num,u8 *Buffer);	  //高通字库测试程序


#endif//_BSP_LCDILI9326_H_2016_
/************************************** The End Of FILE **************************************/
