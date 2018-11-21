#ifndef __SSD1963_H
#define __SSD1963_H


#include "stm32f10x_type.h"
//#include "stm32f10x_gpio.h"
//#include "stm32f10x_rcc.h"
//#include "stm32f10x_type.h"
//#include "STM32_GPIO.H"
//#include "font.h"

//#include	"stdio.h"			//用于printf
//#include	"string.h"			//用于printf
//#include	"stdarg.h"			//用于获取不确定个数的参数
//#include	"stdlib.h"			//malloc动态申请内存空间

//#include "LCD.H"



#define SSD1963
#define SSD1963_BITBAND


 //定义LCD的尺寸	
#define SSD1963_H 800
#define SSD1963_V 480



#define	Bus_16        //16位数据模式,如果使用8位模式，请注释此语句，如果使用16位模式，请打开此句,修改8位模式之前，请确认你手里的模块是否是8位总线接口
#define ShowCharAscii	//二维数组查询
#define Mode8080	//如果CONF引脚连接于VDDIO，单片机接口将被配置在8080模式。
//#define Mode6800	//如果CONF引脚连接于GND，单片机接口将被配置为6800模式接口


//IO连接
//#define	LCD_DataPortH P2     //高8位数据口,8位模式下只使用高8位 
//#define	LCD_DataPortL P0     //低8位数据口	,8位模式下低8位可以不接线,请确认P0口已经上拉10K电阻,不宜太小，最小4.7K,推荐10K.



#define LCD_HDP 799			//水平像素点个数
#define LCD_HT	928			//显示时长 928
#define LCD_HPS	46			//消影时长		46
#define LCD_LPS	15			//15
#define LCD_HPW	48			//48

#define LCD_VDP	479			//垂直像素点个数
#define LCD_VT	525
#define LCD_VPS	16
#define LCD_FPS	8
#define LCD_VPW	16

#define	LCD_LR	0X05		//左向右扫描
#define	LCD_RL	0X04		//左向右扫描
#define	LCD_UD	0X04		//上往下扫描
#define	LCD_DU	0X06		//下往上扫描


enum SSD1963REG
{
	SSD1963_R01_REST	=	0x01,		//soft_reset:Software Reset
	SSD1963_R0A_GPM		=	0X0A,		//get_power_mode:Get the current power mode
	SSD1963_R0B_GAM		=	0x0B,		//get_address_mode:Get the frame memory to the display panel read order
	SSD1963_R0C_GPF		=	0x0C,		//get_pixel_format:Get the current pixel format
	SSD1963_R0D_GDM		=	0x0D,		//get_display_mode:The display module returns the Display Signal Mode.
	SSD1963_R0E_GSM		=	0x0E,		//get_signal_mode:Get the current display mode from the peripheral
	SSD1963_R10_ISP		=	0x10,		//enter_sleep_mode:
	SSD1963_R11_OSP		=	0X11,		//exit_sleep_mode
	SSD1963_R12_EPM		=	0X12,		//enter_partial_mode:Part of the display area is used for image display.
	SSD1963_R13_ENM		=	0X13,		//enter_normal_mode:The whole display area is used for image display.
	SSD1963_R20_OIM		=	0X20,		//exit_invert_mode:Displayed image colors are not inverted.
	SSD1963_R21_IIM		=	0X21,		//enter_invert_mode:Displayed image colors are inverted.
	SSD1963_R26_SGC		=	0X26,		//set_gamma_curve:Selects the gamma curve used by the display device.
	SSD1963_R28_SOF		=	0X28,		//set_display_off:Blanks the display device
	SSD1963_R29_SON		=	0X29,		//set_display_on:Show the image on the display device
	SSD1963_R2A_SCA		=	0X2A,		//set_column_address:Set the column extent
	SSD1963_R2B_SPA		=	0X2B,		//set_page_address:Set the page extent
	SSD1963_R2C_WMS		=	0X2C,		//write_memory_start:
	SSD1963_R2E_RMS		=	0X2E,		//read_memory_start
	SSD1963_R30_SEA		=	0X30,		//set_partial_area:Defines the partial display area on the display device
	SSD1963_R33_SSA		=	0X33,		//set_scroll_area:Defines the vertical scrolling and fixed area on display area
	SSD1963_R34_STF		=	0X34,		//set_tear_off:Synchronization information is not sent from the display module to the host processor
	SSD1963_R35_STO		=	0X35,		//set_tear_on:Synchronization information is sent from the display module to the host processor at the start of VFP
	SSD1963_R36_SAM		=	0X36,		//set_address_mode:Set the read order from frame buffer to the display panel
	SSD1963_R37_SSS		=	0X37,		//set_scroll_start:Defines the vertical scrolling starting point
	SSD1963_R38_OIM		=	0X38,		//exit_idle_mode:Full color depth is used for the display panel
	SSD1963_R39_IIM		=	0X39,		//enter_idle_mode:Reduce color depth is used on the display panel.
	SSD1963_R3A_SPF		=	0X3A,		//set_pixel_format:Defines how many bits per pixel are used in the interface
	SSD1963_R3C_WMC		=	0X3C,		//write_memory_continue:Transfer image information from the host processor interface to the peripheral from the last written location
	SSD1963_R3E_RMC		=	0X3E,		//read_memory_continue:Read image data from the peripheral continuing after the last read_memory_continue or read_memory_start
	SSD1963_R44_STS		=	0X44,		//set_tear_scanline:Synchronization information is sent from the display module to the host processor when the display device refresh reaches the provided scanline
	SSD1963_R45_GS		=	0X45,		//get_scanline:Get the current scan line
	SSD1963_RA1_RD		=	0XA1,		//read_ddb:Read the DDB from the provided location
	SSD1963_RB0_SLM		=	0XB0,		//set_lcd_mode:Set the LCD panel mode (RGB TFT or TTL)
	SSD1963_RB1_GLM		=	0XB1,		//get_lcd_mode:Get the current LCD panel mode, pad strength and resolution
	SSD1963_RB4_SHP_	=	0XB4,		//set_hori_period:Set front porch
	SSD1963_RB5_GHP		=	0XB5,		//get_hori_period:Get current front porch settings
	SSD1963_RB6_SVP		=	0XB6,		//set_vert_period:Set the vertical blanking interval between last scan line and next LFRAME pulse
	SSD1963_RB7_GVP		=	0XB7,		//get_vert_period:Get the vertical blanking interval between last scan line and next LFRAME pulse
	SSD1963_RB8_SGC		=	0XB8,		//set_gpio_conf:Set the GPIO configuration. If the GPIO is not used for LCD,set the direction. Otherwise, they are toggled with LCD signals.
	SSD1963_RB9_GGC		=	0XB9,		//get_gpio_conf:Get the current GPIO configuration
	SSD1963_RBA_SGV		=	0XBA,		//set_gpio_value:Set GPIO value for GPIO configured as output
	SSD1963_RBC_SPP		=	0XBC,		//set_post_proc:Set the image post processor
	SSD1963_RBD_GPP		=	0XBD,		//get_post_proc:Get the image post processor
	SSD1963_RBE_SPC		=	0XBE,		//set_pwm_conf:Set the image post processor
	SSD1963_RBF_GPC		=	0XBF,		//get_pwm_conf:Get the image post processor
	
	SSD1963_RC0_SLG0	=	0XC0,		//set_lcd_gen0:Set the rise, fall, period and toggling properties of LCD signal generator 0
	SSD1963_RC1_GLG0	=	0XC1,		//get_lcd_gen0:Get the current settings of LCD signal generator 0
	SSD1963_RC2_SLG1	=	0XC2,		//set_lcd_gen1:Set the rise, fall, period and toggling properties of LCD signal generator 1
	SSD1963_RC3_SLG1	=	0XC3,		//get_lcd_gen1:Get the current settings of LCD signal generator 1
	SSD1963_RC4_SLG2	=	0XC4,		//set_lcd_gen2:Set the rise, fall, period and toggling properties of LCD signal generator 2
	SSD1963_RC5_SLG2	=	0XC5,		//get_lcd_gen2:Get the current settings of LCD signal generator 2
	SSD1963_RC6_SLG3	=	0XC6,		//set_lcd_gen3:Set the rise, fall, period and toggling properties of LCD signal generator 3
	SSD1963_RC7_SLG3	=	0XC7,		//get_lcd_gen3:Get the current settings of LCD signal generator 3
	
	SSD1963_RC8_SPR0	=	0XC8,		//set_gpio0_rop:Set the GPIO0 with respect to the LCD signal generators using ROP3 operation. No effect if the GPIO0 is configured as general GPIO.
	SSD1963_RC9_GPR0	=	0XC9,		//get_gpio0_rop:Get the GPIO0 properties with respect to the LCD signal generators.
	SSD1963_RCA_SPR1	=	0XCA,		//set_gpio1_rop:Set the GPIO1 with respect to the LCD signal generators using ROP3 operation. No effect if the GPIO1 is configured as general GPIO.
	SSD1963_RCB_GPR1	=	0XCB,		//get_gpio1_rop:Get the GPIO1 properties with respect to the LCD signal generators.
	SSD1963_RCC_SPR2	=	0XCC,		//set_gpio2_rop:Set the GPIO2 with respect to the LCD signal generators using ROP3 operation. No effect if the GPIO2 is configured as general GPIO.
	SSD1963_RCD_GPR2	=	0XCD,		//get_gpio2_rop:Get the GPIO2 properties with respect to the LCD signal generators.
	SSD1963_RCE_SPR3	=	0XCE,		//set_gpio3_rop:Set the GPIO3 with respect to the LCD signal generators using ROP3 operation. No effect if the GPIO3 is configured as general GPIO.
	SSD1963_RCF_GPR3	=	0XCF,		//get_gpio3_rop:Get the GPIO3 properties with respect to the LCD signal generators.
	
	SSD1963_RD0_SDC		=	0XD0,		//set_dbc_conf:Set the dynamic back light configuration
	SSD1963_RD1_GDC		=	0XD1,		//get_dbc_conf:Get the current dynamic back light configuration
	SSD1963_RD4_SDT		=	0XD4,		//set_dbc_th:Set the threshold for each level of power saving
	SSD1963_RD5_GDT		=	0XD5,		//get_dbc_th:Get the threshold for each level of power saving
	
	SSD1963_RE0_SPLL	=	0XE0,		//set_pll:Start the PLL. Before the start, the system was operated with the crystal oscillator or clock input
	SSD1963_RE2_SPLLM	=	0XE2,		//set_pll_mn:Set the PLL
	SSD1963_RE3_GPLLM	=	0XE3,		//get_pll_mn:Get the PLL settings
	SSD1963_RE4_GPLLS	=	0XE4,		//get_pll_status:Get the current PLL status
	SSD1963_RE5_SDS		=	0XE5,		//set_deep_sleep:Set deep sleep mode
	SSD1963_RE6_SLF		=	0XE6,		//set_lshift_freq:Set the LSHIFT (pixel clock) frequency
	SSD1963_RE7_GLF		=	0XE7,		//get_lshift_freq:Get current LSHIFT (pixel clock) frequency setting
	SSD1963_RF0_SPDI	=	0XF0,		//set_pixel_data_interface:Set the pixel data format of the parallel host processor interface
	SSD1963_RF1_GPDI	=	0XF1,		//get_pixel_data_interface:Get the current pixel data format settings
};


			



void SSD1963_Initialize(void*	pInfo);

void SSD1963_SetWindowAddress(unsigned short x1,unsigned short y1,unsigned short x2,unsigned short y2);
void SSD1963_PowerOn(void);


//--------------------------------------------驱动层
unsigned short SSD1963_ReadData(void);
unsigned short SSD1963_ReadRegister(unsigned	short	Addr);

void SSD1963_WriteData(unsigned	short	Data);
void SSD1963_WriteIndex(unsigned	short	Index);
void SSD1963_WriteAddr(unsigned	short	Addr);
void SSD1963_WriteRegister(unsigned	short	Addr,unsigned short Data);		//写指定寄存器
void SSD1963_WriteCommand(unsigned	short	Index,unsigned short Cmd);


void SSD1963_WriteGRAM(unsigned	short* RAM,unsigned long length);				//写显示寄存器
void SSD1963_ReadGRAM(unsigned	short* RAM,unsigned long length);
//--------------------------------------------接口层

void SSD1963_PowerOn(void);					//按照主控芯片SSD1963的power supply on sequence 进行配置
void SSD1963_PowerOff( void );		//关闭SSD1963 电源
void SSD1963_DispOff( void );			//关闭SSD1963显示( 黑屏?)
void SSD1963_SetWindowAddress(unsigned short x1,unsigned short y1,unsigned short x2,unsigned short y2);//设置窗地址

//--------------------------------------------GUI
void SSD1963_DrawDot(unsigned short HSX,unsigned short HSY,unsigned short color);		//画点
void SSD1963_DrawLine(u16 x1,u16 y1,u16 x2,u16 y2,u16 color);						//AB 两个坐标画一条直线
void SSD1963_DrawCircle(u16 x1,u16 y1, u16 R, u8 Filled, u16 color );		//画一个圆形框
void SSD1963_DrawRectangle(u16 x1,u16 y1,u16 x2,u16 y2,u16 color);

void SSD1963_Fill(u16 xsta,u16 ysta,u16 xend,u16 yend,u16 color);				//在指定区域内填充指定颜色;区域大小:(xend-xsta)*(yend-ysta)
void SSD1963_Clean(u16 Color);	//清除屏幕函数;
void SSD1963_SetBackground(u16 BackColor );

//--------------------------------------------字符显示
void SSD1963_ShowChar(u16 x,u16 y,u8 font,u16 color,u8 num,u8 *Buffer);	  //高通字库测试程序
void SSD1963_ShowWord(u16 x,u16 y,u8 font,u16 color,u8 num,u8 *Buffer);	  //高通字库测试程序


#endif



