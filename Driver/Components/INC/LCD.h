/**************************************************************************************************
* Copyright (C), 1997-2016,  HAICHUANG IOT Tech. Co., Ltd.
* �ļ�<Bsp_LcdLCD.h>
* ģ������ :	���塢���ܡ�˵��
* ��ʷ�޸ļ�¼
*     <��Ҫ�޸���>  <ʱ��>   <�汾 >   <˵��>
*     xlyan        2016/9/26   1.0.0    �����ļ�
**************************************************************************************************/
#ifndef __LCD_H_
#define __LCD_H

#include "stm32f10x_type.h"
#include "stm32f10x_gpio.h"
#include "GT32L32M0180.H"

#include "STM32_PWM.H"



//#define	LCD_H 240		//ˮƽ���������������+
//#define LCD_V 400		//��ֱ������������ϵ���+


//****************************���ƶ���End**************************


typedef enum
{
	Draw_Rotate_0D = 0,
	Draw_Rotate_90D,
	Draw_Rotate_180D,
	Draw_Rotate_270D,
} eRotate;


typedef struct	_LCDPort
{
	//____________������ƶ���	//1:������;0:�ر���
	GPIO_TypeDef* 	sBL_PORT;			//GPIOX
	unsigned short 	sBL_Pin;				//GPIO_Pin_x
	
	//____________���ź�;0:������
	GPIO_TypeDef* 	sRD_PORT;							//GPIOX
	unsigned short 	sRD_Pin;							//GPIO_Pin_x
	
	//____________��λ�ź� 1:����;0:��λ
	GPIO_TypeDef* 	sREST_PORT;						//GPIOX
	unsigned short 	sREST_Pin;						//GPIO_Pin_x
	
	//____________����/���ݣ�0������;1-����	RS
	GPIO_TypeDef* 	sDC_PORT;							//GPIOX
	unsigned short 	sDC_Pin;							//GPIO_Pin_x
	
	//____________д�ź� ��WR�������أ�ʹ����д�뵽LCD����
	GPIO_TypeDef* 	sWR_PORT;							//GPIOX
	unsigned short 	sWR_Pin;							//GPIO_Pin_x
	
	//____________Ƭѡ�ź� 0:Ƭѡ;1:ʧ��;
	GPIO_TypeDef* 	sCS_PORT;							//GPIOX
	unsigned short 	sCS_Pin;							//GPIO_Pin_x
	
	//____________TE
	GPIO_TypeDef* 	sTE_PORT;							//GPIOX
	unsigned short 	sTE_Pin;							//GPIO_Pin_x
	
	//____________���ݽӿ�
	GPIO_TypeDef* 	sDATABUS_PORT;				//GPIOX
	unsigned short 	sDATABUS_Pin;					//GPIO_Pin_x

}LCDPortDef;
typedef struct	_LCDData
{
	unsigned short	MaxH;						//ˮƽ������----��ʼ����Ҫ���ò���
	unsigned short 	MaxV;						//��ֱ������----��ʼ����Ҫ���ò���
	unsigned short	HSX;						//ˮƽ��ʼ��
	unsigned short 	HEX;						//ˮƽ��ֹ��
	unsigned short	VSY;						//��ֱ��ʼ��
	unsigned short 	VEY;						//��ֱ��ֹ��
	unsigned short	HXA;						//RAM Address Set (Horizontal Address) (R200h)
	unsigned short 	VYA;						//RAM Address Set (Vertical Address) (R201h)
	unsigned short 	PColor;					//������ɫ
	unsigned short 	BColor;					//������ɫ
  unsigned long   FsmcDataAddr;  //FSMCд���ݵ�ַ
  unsigned long   FsmcRegAddr;   //FSMCд�Ĵ�����ַ
}LCDDataDef;
typedef struct	_LCDFlag		//0Ϊ�ޱ�ʶ
{
	eRotate	Rotate;						//ɨ�跽ʽ/��ת�Ƕ�
}LCDFlagDef;
typedef struct _DisplayDriver
{
	//------------------��ɾ��
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
	
	void ( *DrawDot)(unsigned short HSX,unsigned short HSY,unsigned short color);		//����
	void ( *DrawLine)(u16 x1,u16 y1,u16 x2,u16 y2,u16 color);						//AB �������껭һ��ֱ��
	void ( *DrawCircle)(u16 x1,u16 y1, u16 R, u8 Filled, u16 color );		//��һ��Բ�ο�
	void ( *DrawRectangle)(u16 x1,u16 y1,u16 x2,u16 y2,u16 color);				//��һ�����ο�
	
	void ( *Fill )(u16 xsta,u16 ysta,u16 xend,u16 yend,u16 color);				//��ָ�����������ָ����ɫ;�����С:(xend-xsta)*(yend-ysta)
	void ( *Clean)(u16 Color);								//�����Ļ����;
	void ( *SetBackground)(u16 BackColor );
	
	//--------------------------------------------�ַ���ʾ
	void ( *ShowChar)(u16 x,u16 y,u8 font,u16 color,u8 num,u8 *Buffer);	  //��ͨ�ֿ���Գ���
	void ( *ShowWord)(u16 x,u16 y,u8 font,u16 color,u8 num,u8 *Buffer);	  //��ͨ�ֿ���Գ���

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
	unsigned short	startx;				//��ʼ��ʾx����
	unsigned short	starty;				//��ʼ��ʾy����
	unsigned short	color;				//��ʾ��ɫ
	unsigned short	length;				//��ʾ���ݳ���.
	unsigned short	runxstart;		//�ӵڼ����ַ���ʼ��ʾ
	unsigned char		font;					//��ʾ�ֺ�
	unsigned char		buffer[100];	//��ʾ����
	unsigned long*	nextlist;			//��һ����ʾ���ݵ�ַ
}stLCDScroll;

extern LCDDef *LCDSYS;			//�ڲ�����ʹ�ã�����ɾ��

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
//#define LCD_FORE_COLOR	0xef5d 		//ǰ��ɫ
//#define LCD_BACK_COLOR	0x0000		//����ɫ

#define LCD_ALARM_COLOR  0xF800
#define LCD_TRANSPARENT_COLOR 0xFFFF


//������ɫ
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
#define LCD565_BROWN 			0XBC40 	//��ɫ
#define LCD565_BRRED 			0XFC07 	//�غ�ɫ
#define LCD565_GRAY  			0X8430 	//��ɫ
#define LCD565_DARKBLUE  	0X01CF	//����ɫ
#define LCD565_LIGHTBLUE 	0X7D7C	//ǳ��ɫ  
#define LCD565_GRAYBLUE  	0X5458 	//����ɫ
#define LCD565_LIGHTGREEN	0X841F 	//ǳ��ɫ
#define LCD565_LGRAY 			0XC618 	//ǳ��ɫ(PANNEL),���屳��ɫ
#define LCD565_LGRAYBLUE 	0XA651 	//ǳ����ɫ(�м����ɫ)
#define LCD565_LBBLUE    	0X2B12 	//ǳ����ɫ(ѡ����Ŀ�ķ�ɫ)
#define LCD565_UNKNOW    	0X2B20 	//������ɫ


//======================================�ⲿ�ӿ�
unsigned short LCD_Initialize(LCDDef *pInfo);
void LCDFsmc_Initialize(LCDDef *pInfo);
void LCD_DisplayServer(void);

void LCD_ShowAntenna(u16 x,u16 y,u8 Num,u16 PenColor);   //��ʾ12x12����
void LCD_ShowBattery(u16 x,u16 y,u8 Num,u16 PenColor); 	//��ʾ12x12���
void LCD_Show(u16 x,u16 y,u8 font,u16 PenColor,u8 num,u8 *Buffer);	
void LCD_ShowScroll(stLCDScroll	*ScrollBuff);	
void LCD_ShowHex(u16 x,u16 y,u8 font,u16 color,u8 num,u8 bitnum,u8 *Buffer);    //��ʾʮ����������
unsigned int LCD_Printf(u16 x,u16 y,u8 font,u16 color,const char *format,...);  //LCD��ӡ����
unsigned int LCD_PrintfScroll(u16 x,u16 y,u8 font,u16 color,const char *format,...);  //LCD������ӡ����
void LCD_ShowBMP(u16 xsta,u16 ysta,u16 xend,u16 yend,u16 Length,u8 *RGBBuffer);    //��ʾʮ����������
unsigned  short RGB888toRGB565(u8 *RGB888);

//======================================�ڲ��ײ㺯��
void LCD_Reset(void);

void LCD_WriteIndex( unsigned short Index );		//GPIO��ʽд��ַ
void LCD_WriteData(u16 Data);										//GPIO��ʽд����					
void LCDFsmc_WriteIndex(unsigned short Index);	//FSMC��ʽд��ַ
void LCDFsmc_WriteData(unsigned short Data);		//FSMC��ʽд����
void LCD_WriteCommand(unsigned short index,unsigned short Command);		//д������������
u16 LCD_ReadData( unsigned short Index );				//������

void LCD_WriteRegister(unsigned	short	Index,unsigned short Data);
unsigned short LCD_ReadRegister(unsigned	short	Index);

void LCD_Clean(u16 COLOR);	//�����Ļ����
void LCD_DrawDot(unsigned short HSX,unsigned short HSY,unsigned short color);		//����
void LCD_DrawLine(u16 x1,u16 y1,u16 x2,u16 y2,u16 color);						//AB �������껭һ��ֱ��
void LCD_DrawCircle(u16 x1,u16 y1, u16 R, u8 Filled, u16 color );		//��һ��Բ�ο�
void LCD_DrawRectangle(u16 x1,u16 y1,u16 x2,u16 y2,u16 color);				//��һ�����ο�

void LCD_Fill(u16 xsta,u16 ysta,u16 xend,u16 yend,u16 color);				//��ָ�����������ָ����ɫ;�����С:(xend-xsta)*(yend-ysta)
void LCD_SetBackground(u16 BackColor );
void LCD_ShowChar(u16 x,u16 y,u8 font,u16 color,u8 num,u8 *Buffer);	  //��ͨ�ֿ���Գ���
void LCD_ShowWord(u16 x,u16 y,u8 font,u16 color,u8 num,u8 *Buffer);	  //��ͨ�ֿ���Գ���
unsigned short LCD_GetDispCodeBuffer(u8 font,u16 word,u8 *ReadBuffer);	//��ȡ��ʾ������

//======================================��ʱ����
void LCD_DelayuS(u32 xuS);
void LCD_DelaymS(u32 xmS);
void LCD_DelayS(u32 xS);
#endif//_BSP_LCDLCD_H_2016_
/************************************** The End Of FILE **************************************/
