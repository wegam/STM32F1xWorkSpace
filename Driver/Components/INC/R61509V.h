/**************************************************************************************************
* Copyright (C), 1997-2016,  HAICHUANG IOT Tech. Co., Ltd.
* 文件<Bsp_R61509VR61509V.h>
* 模块描述 :	定义、功能、说明
* 历史修改记录
*     <主要修改者>  <时间>   <版本 >   <说明>
*     xlyan        2016/9/26   1.0.0    创建文件
**************************************************************************************************/
#ifndef __R61509V_H_
#define __R61509V_H


#include "stm32f10x_type.h"
#include "stm32f10x_gpio.h"

//#include "LCD.H"

#define	R61509V_H 240		//水平方向点数，从左到右+
#define R61509V_V 400		//垂直方向点数，从上到下+

#define	R61509ID	(unsigned short)0xB509			//芯片型号标识
//****************************控制定义End**************************



/*功能位 */
#define R61509V_DC1_IMAGE_ENABLE_BIT		0x1000
#define R61509V_DC1_PARTIAL_ENABLE_BIT	0x0100

#define R61509V_R000_IR			( (u16) 0x0000) 	//Device code read Index (IR)/*[10:0]REG ID */
#define R61509V_R000_DCR		( (u16) 0x0000) 	//Device code read (R000h)/*[15:0]	B509H Read */			//Device code read
#define R61509V_R001_DOC		( (u16) 0x0001) 	//Driver Output Control (R001h)/*[8]SS,[10]SM */
#define R61509V_R002_DWC		( (u16) 0x0002) 	//R61509V Drive Wave Control (R002h)/*[8]BC */
#define R61509V_R003_EM			( (u16) 0x0003) 	//Entry Mode (R003h)/*[3]AM,[5:4]ID,[7]ORG,[12]BGR,[14]DFM,[15]TRI */
#define R61509V_R007_DC1		( (u16) 0x0007) 	//Display Control 1 (R007h)/*[8]BASEE,[12]PTDE */
#define R61509V_R008_DC2		( (u16) 0x0008) 	//Display Control 2 (R008h)/*[15:8]FP,[7:0]BP */
#define R61509V_R009_DC3		( (u16) 0x0009) 	//Display Control 3 (R009h)/*[10]PTS,[11]PTV */
#define R61509V_R00B_ECC		( (u16) 0x000B)		//Eight Color Control (R00Bh) /*[0]COL */
#define R61509V_R00C_EDIC1	( (u16) 0x000C) 	//External Display Interface Control 1 (R00Ch)/*[0]RIM,[5:4]DM,[8]RM,[14:12]ENC */
#define R61509V_R00F_EDIC2	( (u16) 0x000F) 	//External Display Interface Control 2 (R00Fh)//*[0]DPL,[1]EPL,[3]HSPL,[4]VSPL */
#define R61509V_R010_PIC1		( (u16) 0x0010) 	//Panel Interface Control 1 (R010h)	/*[5:0]RTNI,[]DIV */
#define R61509V_R011_PIC2		( (u16) 0x0011) 	//Panel Interface Control 2 (R011h)	/*[2:0]STDI,[10:8]NOWI */
#define R61509V_R012_PIC3		( (u16) 0x0012) 	//Panel Interface Control 3 (R012h)	/*[2:0]SEQWI,[10:8]VEQWI */
#define R61509V_R013_PIC4		( (u16) 0x0013) 	//Panel Interface Control 4 (R013h)	/*[2:0]MCPI */
#define R61509V_R014_PIC5		( (u16) 0x0014) 	//Panel Interface Control 5 (R014h)	/*[2:0]PCDIVL,[10:8]PCDIVH */
#define R61509V_R020_PIC6		( (u16) 0x0020) 	//Panel Interface Control 6 (R020h)	/*[] */
#define R61509V_R021_PIC7		( (u16) 0x0021) 	//Panel Interface Control 7 (R021h)	/*[2:0]STDE,[10:8]NOWE */
#define R61509V_R022_PIC8		( (u16) 0x0022) 	//Panel Interface Control 8 (R022h)	/*[2:0]SEQWE,[10:8]VEQWE */
#define R61509V_R023_PIC9		( (u16) 0x0023) 	//Panel Interface Control 9 (R023h)	/*[7:0]MCPE */
#define R61509V_R090_FMC		( (u16) 0x0090) 	//Frame Marker Control (R090h)	/*[8:0]FMP,[14:12]FMI,[15]FMKM */
#define R61509V_R100_PC1		( (u16) 0x0100) 	//Power Control 1 (R100h)	/*[2]DSTB,[5:4]AP,[10:8]BT */
#define R61509V_R101_PC2		( (u16) 0x0101)		//Power Control 2 (R101h) /*[2:0]VC,[6:4]DCO,[10:8]DC1 */
#define R61509V_R102_PC3		( (u16) 0x0102) 	//Power Control3 (R102h)	/*[4]PON,[5]PSON,[8]VCMR,[15:11]VRH */
#define R61509V_R103_PC4		( (u16) 0x0103) 	//Power Control 4 (R103h)	/*[12:8]VDV */
#define R61509V_R200_HA			( (u16) 0x0200)		//RAM Address Set (Horizontal Address) (R200h)	 /*[7:0] */
#define R61509V_R201_VA			( (u16) 0x0201) 	//RAM Address Set (Vertical Address) (R201h)	/*[8:0] */
#define R61509V_R202_GDRW		( (u16) 0x0202)		//GRAM Data Write (R202h)/GRAM Data Read (R202h)
#define R61509V_R280_NVM		( (u16) 0x0280) 	//NVM Data Read / NVM Data Write (R280h)	/*[7:0]UID,[14:8]VCM */
#define R61509V_R210_HSA		( (u16) 0x0210) 	//Window Horizontal RAM Address Start (R210h)		/*[7:0] */
#define R61509V_R211_HEA		( (u16) 0x0211) 	//Window Horizontal RAM Address End(R211h)	/*[7:0] */
#define R61509V_R212_VSA		( (u16) 0x0212)		//Window Vertical RAM Address Start (R212h) /*[8:0] */
#define R61509V_R213_VEA		( (u16) 0x0213) 	//Window Vertical RAM Address End (R213h)	/*[8:0] */
#define R61509V_R300_YC1		( (u16) 0x0300)		//γ Control 1(R300)	
#define R61509V_R301_YC2		( (u16) 0x0301)		//γ Control 2(R301)	
#define R61509V_R302_YC3		( (u16) 0x0302)		//γ Control 3(R302)	
#define R61509V_R303_YC4		( (u16) 0x0303)		//γ Control 4(R303)	
#define R61509V_R304_YC5		( (u16) 0x0304)		//γ Control 5(R304)	
#define R61509V_R305_YC6		( (u16) 0x0305)		//γ Control 6(R305)	
#define R61509V_R306_YC7		( (u16) 0x0306)		//γ Control 7(R306)	
#define R61509V_R307_YC8		( (u16) 0x0307)		//γ Control 8(R307)	
#define R61509V_R308_YC9		( (u16) 0x0308)		//γ Control 9(R308)	
#define R61509V_R309_YC10		( (u16) 0x0309)		//γ Control 10(R309)	
#define R61509V_R400_BINL		( (u16) 0x0400)		//Base Image Number of Line (R400h) /*[15]GS,[14:9]NL,[6:1]SCN */
#define R61509V_R401_BIDC		( (u16) 0x0401) 	//Base Image Display Control (R401h)	/*[2]NDL,[1]VLE,[0]REV */
#define R61509V_R404_BIVSC	( (u16) 0x0404) 	//Base Image Vertical Scroll Control (R404h)	/*[8:0]VL */
#define R61509V_R500_PTDP		( (u16) 0x0500) 	//Display Position (R500h)	/*[8:0] */
#define R61509V_R501_PTSA		( (u16) 0x0501) 	//RAM Address 1 (Start Line Address) (R501h)	/*[8:0] */
#define R61509V_R502_PTEA		( (u16) 0x0502) 	//RAM Address 1 (End Line Address) (R502h)	/*[8:0] */
#define R61509V_R600_TR			( (u16) 0x0600) 	//Test Register (Software Reset) (R600h)	/*[0]TRSR */
#define R61509V_R6F0_NVMC1	( (u16) 0x06F0)  	//NVM Access Control 1 (R6F0h),	/*[5:4]EOP,[6]CALB,[7]TE */
#define R61509V_R6F1_NVMC2	( (u16) 0x06F1)  	//NVM Access Control 2 (R6F1h),	/*[15:0]NVDAT */
#define R61509V_R6F2_NVMC3	( (u16) 0x06F2)  	//NVM Access Control 3 (R6F2h)/*[3]NVVRF */




unsigned short R61509V_Initialize(void*	pInfo);

//--------------------------------------------驱动层
void R61509V_Reset(void);
unsigned short R61509V_ReadData(void);
unsigned short R61509V_ReadRegister(unsigned	short	Addr);

void R61509V_WriteData(unsigned	short	Data);
void R61509V_WriteIndex(unsigned	short	Index);
void R61509V_WriteAddr(unsigned	short	Addr);
void R61509V_WriteRegister(unsigned	short	Addr,unsigned short Data);		//写指定寄存器
void R61509V_WriteCommand(unsigned	short	Index,unsigned short Cmd);


void R61509V_WriteGRAM(unsigned	short* RAM,unsigned long length);				//写显示寄存器
void R61509V_ReadGRAM(unsigned	short* RAM,unsigned long length);
//--------------------------------------------接口层

void R61509V_PowerOn(void);					//按照主控芯片R61509V的power supply on sequence 进行配置
void R61509V_PowerOff( void );		//关闭R61509V 电源
void R61509V_DispOff( void );			//关闭R61509V显示( 黑屏?)
void R61509V_SetWindowAddress(unsigned short x1,unsigned short y1,unsigned short x2,unsigned short y2);//设置窗地址

//--------------------------------------------GUI
void R61509V_DrawDot(unsigned short HSX,unsigned short HSY,unsigned short color);		//画点
void R61509V_DrawLine(u16 x1,u16 y1,u16 x2,u16 y2,u16 color);						//AB 两个坐标画一条直线
void R61509V_DrawCircle(u16 x1,u16 y1, u16 R, u8 Filled, u16 color );		//画一个圆形框
void R61509V_DrawRectangle(u16 x1,u16 y1,u16 x2,u16 y2,u16 color);

void R61509V_Fill(u16 xsta,u16 ysta,u16 xend,u16 yend,u16 color);				//在指定区域内填充指定颜色;区域大小:(xend-xsta)*(yend-ysta)
void R61509V_Clean(u16 Color);	//清除屏幕函数;
void R61509V_SetBackground(u16 BackColor );

//--------------------------------------------字符显示
void R61509V_ShowChar(u16 x,u16 y,u8 font,u16 color,u8 num,u8 *Buffer);	  //高通字库测试程序
void R61509V_ShowWord(u16 x,u16 y,u8 font,u16 color,u8 num,u8 *Buffer);	  //高通字库测试程序

#endif	//_BSP_R61509VR61509V_H_2016_
/************************************** The End Of FILE **************************************/
