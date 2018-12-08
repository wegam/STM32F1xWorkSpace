/**************************************************************************************************
* Һ��������IC
* �ļ�<$(filename)>
* ģ������ :	���塢���ܡ�˵��
* ��ʷ�޸ļ�¼
*     <��Ҫ�޸���>  <ʱ��>   <�汾 >   <˵��>
*     xlyan        $(Date)   1.0.0    �����ļ�
**************************************************************************************************/
#include "LCD.H"

#include "stm32f10x_fsmc.h"

#include "STM32_GPIO.H"
#include "STM32_PWM.H"
#include "STM32_SYSTICK.H"
#include "font.h"
#include "string.h"				//�����ڴ��������ͷ�ļ�
#include "stdlib.h"				//�����ڴ��������ͷ�ļ�
#include "stdarg.h"				//�����ڴ��������ͷ�ļ�
#include "stdio.h"				//�����ڴ��������ͷ�ļ�

#include "R61509V.h"
#include "ILI9326.h"
#include "SSD1963.H"

#define		Bus16Bit
LCDDef 			*LCDSYS	=	NULL;	//�ڲ�����ʹ�ã�����ɾ��
stLCDScroll	*ScrollBuff	=	NULL;
unsigned short PenColor		=	0;		//������ɫ
unsigned short BackColor	=	0;		//������ɫ
unsigned short VAsize	=	0;		//�����С
/*******************************************************************************
*������			:	LCD_Initialize
*��������		:	LCD��ʼ����
*����				: 
*����ֵ			:	��
*******************************************************************************/
unsigned short LCD_Initialize(LCDDef *pInfo)
{
	static unsigned short	DeviceCode	=	0;
	
  LCDPortDef  *Port;
	LCDSYS	  =	pInfo;		//ָ��ָ��
  
  Port	=	&(pInfo->Port);	
	
	//==========================GPIO����
	GPIO_Configuration_OPP50	(Port->sBL_PORT,				Port->sBL_Pin);					//��GPIO��Ӧ�ܽ�����ΪPP(����)���ģʽ������ٶ�2MHz----V20170605
	GPIO_Configuration_OPP50	(Port->sRD_PORT,				Port->sRD_Pin);					//��GPIO��Ӧ�ܽ�����ΪPP(����)���ģʽ������ٶ�2MHz----V20170605
	GPIO_Configuration_OPP50	(Port->sREST_PORT,			Port->sREST_Pin);				//��GPIO��Ӧ�ܽ�����ΪPP(����)���ģʽ������ٶ�2MHz----V20170605
	GPIO_Configuration_OPP50	(Port->sDC_PORT,				Port->sDC_Pin);					//��GPIO��Ӧ�ܽ�����ΪPP(����)���ģʽ������ٶ�2MHz----V20170605
	GPIO_Configuration_OPP50	(Port->sWR_PORT,				Port->sWR_Pin);					//��GPIO��Ӧ�ܽ�����ΪPP(����)���ģʽ������ٶ�2MHz----V20170605
	GPIO_Configuration_OPP50	(Port->sCS_PORT,				Port->sCS_Pin);					//��GPIO��Ӧ�ܽ�����ΪPP(����)���ģʽ������ٶ�2MHz----V20170605
	GPIO_Configuration_OPP50	(Port->sTE_PORT,				Port->sTE_Pin);					//��GPIO��Ӧ�ܽ�����ΪPP(����)���ģʽ������ٶ�2MHz----V20170605
	GPIO_Configuration_OPP50	(Port->sDATABUS_PORT,		Port->sDATABUS_Pin);		//��GPIO��Ӧ�ܽ�����ΪPP(����)���ģʽ������ٶ�2MHz----V20170605
	//===========================������ַ
  LCDSYS->Display.WriteIndex    = LCD_WriteIndex;
  LCDSYS->Display.WriteData     = LCD_WriteData;
  LCDSYS->Display.WriteCommand  = LCD_WriteCommand;
	//==========================����оƬ���
	LCD_Reset();
//	DeviceCode	=	LCD_ReadData(0x0000);
	
	DeviceCode	=	ILI9326_Initialize(pInfo);
	if(ILI9326ID	==	DeviceCode)
	{
		goto	Lcd_InitContinue;
	}
		
	DeviceCode	=	R61509V_Initialize(pInfo);
	if(R61509ID	==	DeviceCode)
	{
		goto	Lcd_InitContinue;
	}
	
	SSD1963_Initialize(pInfo);

	Lcd_InitContinue:
  //==========================��鱳��ɫ�뻭��ɫ�Ƿ���ͬ
	if(pInfo->Data.PColor	==	pInfo->Data.BColor)
	{
		pInfo->Data.PColor	=	pInfo->Data.BColor^0xFF;
	}
  
	//==========================LCD��ʼ�����ϵ�����
	LCDSYS->Display.PowerOn();						//LCD�ϵ�/��ʼ������
	//==========================�Ա���ɫ�����Ļ
	LCD_Clean(pInfo->Data.BColor);				//������ɫ�����Ļ����
	//==========================������
	LCD_BL_ON;
	//==========================�ֿ�����
	GT32L32_Initialize(&pInfo->GT32L32.SPI);				//��ͨSPIͨѶ��ʽ����
	
	return	0;
}
/*******************************************************************************
*������			:	LCDFsmc_Initialize
*��������		:	FSMC�ӿ�LCD��ʼ����
*����				: 
*����ֵ			:	��
*******************************************************************************/
void LCDFsmc_Initialize(LCDDef *pInfo)
{  
	static unsigned short	DeviceCode	=	0;
  GPIO_InitTypeDef                GPIO_InitStructure;
	FSMC_NORSRAMInitTypeDef         FSMC_NORSRAMInitStructure;
  FSMC_NORSRAMTimingInitTypeDef   FSMC_NORSRAMTimingInitStructure;
  
  LCDPortDef  *Port;
	LCDSYS	  =	pInfo;		//ָ��ָ��
  
  Port	=	&(pInfo->Port);	
	
	//==========================��ʱ��
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |RCC_APB2Periph_GPIOB |RCC_APB2Periph_GPIOC |RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE | RCC_APB2Periph_GPIOF | RCC_APB2Periph_GPIOG | RCC_APB2Periph_AFIO, ENABLE);
  //==========================GPIO����
  if(NULL!= Port->sBL_PORT)
    GPIO_Configuration_OPP50	(Port->sBL_PORT,				Port->sBL_Pin);					//��GPIO��Ӧ�ܽ�����ΪPP(����)���ģʽ������ٶ�2MHz----V20170605
  if(NULL!= Port->sREST_PORT)
    GPIO_Configuration_OPP50	(Port->sREST_PORT,			Port->sREST_Pin);				//��GPIO��Ӧ�ܽ�����ΪPP(����)���ģʽ������ٶ�2MHz----V20170605
  if(NULL!= Port->sCS_PORT)
    GPIO_Configuration_OPP50	(Port->sCS_PORT,				Port->sCS_Pin);					//��GPIO��Ӧ�ܽ�����ΪPP(����)���ģʽ������ٶ�2MHz----V20170605
  //-----------------��FSMC�����ݶ˿�D[15:0]
  GPIO_Configuration_APP50(GPIOD,GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_14 | GPIO_Pin_15);
  GPIO_Configuration_APP50(GPIOE,GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 |  GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
  //-----------------��FSMC���ܶ˿ڣ�PD.4=RD(nOE)��PD.5=WR(nWE)
  GPIO_Configuration_APP50(GPIOD,GPIO_Pin_4 | GPIO_Pin_5);
  //-----------------��NE4����
  GPIO_Configuration_APP50(GPIOG,GPIO_Pin_12);
  //-----------------��RS����
  GPIO_Configuration_APP50(GPIOE,GPIO_Pin_3);
  
  //==========================��ʼ��GPIO״̬
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
  LCD_DelaymS(100); 
  
  //===========================FSMC��ʼ��
  
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
  
//	GPIO_Configuration_OPP50	(Port->sRD_PORT,				Port->sRD_Pin);					//��GPIO��Ӧ�ܽ�����ΪPP(����)���ģʽ������ٶ�2MHz----V20170605
//	GPIO_Configuration_OPP50	(Port->sREST_PORT,			Port->sREST_Pin);				//��GPIO��Ӧ�ܽ�����ΪPP(����)���ģʽ������ٶ�2MHz----V20170605
//	GPIO_Configuration_OPP50	(Port->sDC_PORT,				Port->sDC_Pin);					//��GPIO��Ӧ�ܽ�����ΪPP(����)���ģʽ������ٶ�2MHz----V20170605
//	GPIO_Configuration_OPP50	(Port->sWR_PORT,				Port->sWR_Pin);					//��GPIO��Ӧ�ܽ�����ΪPP(����)���ģʽ������ٶ�2MHz----V20170605	
//	GPIO_Configuration_OPP50	(Port->sTE_PORT,				Port->sTE_Pin);					//��GPIO��Ӧ�ܽ�����ΪPP(����)���ģʽ������ٶ�2MHz----V20170605
//	GPIO_Configuration_OPP50	(Port->sDATABUS_PORT,		Port->sDATABUS_Pin);		//��GPIO��Ӧ�ܽ�����ΪPP(����)���ģʽ������ٶ�2MHz----V20170605
	
  //===========================������ַ
  LCDSYS->Display.WriteIndex    = LCDFsmc_WriteIndex;
  LCDSYS->Display.WriteData     = LCDFsmc_WriteData;
  LCDSYS->Display.WriteCommand  = LCD_WriteCommand;
  //==========================��������
  SSD1963_Initialize(pInfo);

  //==========================��鱳��ɫ�뻭��ɫ�Ƿ���ͬ
	if(pInfo->Data.PColor	==	pInfo->Data.BColor)
	{
		pInfo->Data.PColor	=	pInfo->Data.BColor^0xFF;
	}
	//==========================LCD��ʼ�����ϵ�����
	LCDSYS->Display.PowerOn();						//LCD�ϵ�/��ʼ������
	//==========================�Ա���ɫ�����Ļ
//	LCD_Clean(pInfo->Data.BColor);				//������ɫ�����Ļ����
  LCD_Clean(LCD565_WHITE);				//������ɫ�����Ļ����
	//==========================������LIGHT=1
  GPIO_SetBits(Port->sBL_PORT, Port->sBL_Pin);
	//==========================�ֿ�����
	GT32L32_Initialize(&pInfo->GT32L32.SPI);				//��ͨSPIͨѶ��ʽ����
}
/*******************************************************************************
* ������			:	function
* ��������		:	��������˵�� 
* ����			: void
* ����ֵ			: void
* �޸�ʱ��		: ��
* �޸�����		: ��
* ����			: wegam@sina.com
*******************************************************************************/
void LCD_DisplayServer(void)
{
	if(NULL	!=	ScrollBuff)
	{
		LCD_Clean(LCDSYS->Data.BColor);
		LCD_ShowScroll(ScrollBuff);
	}
}
/*******************************************************************************
* ������			:	LCD_Reset
* ��������		:	��������˵�� 
* ����			: void
* ����ֵ			: void
* �޸�ʱ��		: ��
* �޸�����		: ��
* ����			: wegam@sina.com
*******************************************************************************/
void LCD_Reset(void)
{
	LCD_RST_HIGH;
	LCD_DelaymS(5);				//SysTick��ʱnmS
	LCD_RST_LOW;
	LCD_DelaymS(5);				//SysTick��ʱnmS
	LCD_RST_HIGH;
	LCD_DelaymS(10);				//SysTick��ʱnmS
}

/**************************************************************************************************
* [Function] R61509V_DispOff:  �ر�R61509V��ʾ( ����?)
* [No param]
**************************************************************************************************/
void LCD_WriteIndex( unsigned short Index )
{
//	LCD_CS_LOW; 	//Ƭѡ�ź� 0:Ƭѡ;1:ʧ��;
//	LCD_DC_LOW; 	//����/���ݣ�0������;1-����
//	LCD_WriteData(Index);
//	LCD_DC_HIGH; 	//����/���ݣ�0������;1-����
	
	LCD_CS_LOW;
	LCD_RD_HIGH;
	LCD_RS_LOW;
	LCD_DATABUS_PORT->ODR = Index;
	LCD_WR_LOW;
	LCD_WR_HIGH;
	LCD_CS_HIGH;
}
/*******************************************************************************
* ������			:	LCD_WriteData
* ��������		:	д16λ����
* ����			: void
* ����ֵ			: void
* �޸�ʱ��		: ��
* �޸�����		: ��
* ����			: wegam@sina.com
*******************************************************************************/
void LCD_WriteData(u16 Data)
{
#if 1	//16λ���ݽӿ�
//	LCD_WR_LOW;
//	LCD_DATABUS_PORT->ODR = Data;		
//	LCD_WR_HIGH;
	
	LCD_CS_LOW;
	LCD_RD_HIGH;
	LCD_RS_HIGH;
	LCD_DATABUS_PORT->ODR = Data;
	LCD_WR_LOW;
	LCD_WR_HIGH;
	LCD_CS_HIGH;
#else	//8λ���ݽӿ�
	LCD_CS_LOW;
	LCD_RD_HIGH;
	LCD_RS_HIGH;
	//----------��8λ
	LCD_WR_LOW;
	LCD_DATABUS_PORT->ODR = Data>>8;		
	LCD_WR_HIGH;
	//----------��8λ
	LCD_WR_LOW;
	LCD_DATABUS_PORT->ODR = Data;		
	LCD_WR_HIGH;
	
	LCD_CS_HIGH;
#endif
}
/*******************************************************************************
*������			:	function
*��������		:	function
*����				: 
*����ֵ			:	��
*�޸�ʱ��		:	��
*�޸�˵��		:	��
*ע��				:	wegam@sina.com
*******************************************************************************/
void LCDFsmc_WriteIndex(unsigned short Index)
{  
  *(volatile unsigned short*)(LCDSYS->Data.FsmcRegAddr)  = Index;
}
/*******************************************************************************
*������			:	function
*��������		:	function
*����				: 
*����ֵ			:	��
*�޸�ʱ��		:	��
*�޸�˵��		:	��
*ע��				:	wegam@sina.com
*******************************************************************************/
void LCDFsmc_WriteData(unsigned short Data)
{  
  *(volatile unsigned short*)(LCDSYS->Data.FsmcDataAddr)  = Data;
}
/*******************************************************************************
*������			:	R61509V_WriteCommand
*��������		:	д������������
*����				: 
*����ֵ			:	��
*******************************************************************************/
void LCD_WriteCommand(												  //д������������
											unsigned short Index,			//�Ĵ�������
											unsigned short Command		//����
											)	//д������������
{
	//==================д��ַ
  LCDSYS->Display.WriteIndex(Index);	
	//==================д����
  LCDSYS->Display.WriteData(Command);
}
/**************************************************************************************************
* [Function] R61509V_ReadData:  ��R61509V��ȡ����
* [No param][return]u16: ��������
**************************************************************************************************/
u16 LCD_ReadData( unsigned short Index )
{
	u16 Data;
	
	GPIO_Configuration_OPP50	(LCD_DATABUS_PORT,LCD_DATABUS_Pin);		//��GPIO��Ӧ�ܽ�����ΪPP(����)���ģʽ������ٶ�2MHz----V20170605
	
	//==================д��ַ
	LCD_RD_HIGH;
	LCD_CS_LOW;
	LCD_RS_LOW;

	LCD_DATABUS_PORT->ODR = Index;
	LCD_WR_LOW;
	LCD_WR_HIGH;
	LCD_RS_HIGH;

	GPIO_Configuration_IPU	(LCD_DATABUS_PORT,LCD_DATABUS_Pin);			//��GPIO��Ӧ�ܽ�����Ϊ��������ģʽ----V20170605
  
	LCD_RD_LOW;

	Data = LCD_DATABUS_PORT->IDR;
	LCD_RD_HIGH;
	LCD_CS_HIGH;
	
	GPIO_Configuration_OPP50	(LCD_DATABUS_PORT,LCD_DATABUS_Pin);		//��GPIO��Ӧ�ܽ�����ΪPP(����)���ģʽ������ٶ�2MHz----V20170605
	return Data;	
}
/*******************************************************************************
* ������			:	LCD_WriteRegister
* ��������		:	дָ���Ĵ��� 
* ����			: void
* ����ֵ			: void
* �޸�ʱ��		: ��
* �޸�����		: ��
* ����			: wegam@sina.com
*******************************************************************************/
void LCD_WriteRegister(unsigned	short	Index,unsigned short Data)
{
#ifdef	Bus16Bit
	//---------------------Write Index
	LCD_RD_HIGH;
	LCD_CS_LOW;
	
	LCD_DC_LOW;		//RS
	LCD_WR_LOW;
	LCD_DATABUS_PORT->ODR = Index;
	LCD_WR_HIGH;
	LCD_DC_HIGH;	//RS
	//---------------------Write Data
	LCD_WR_LOW;
	LCD_DATABUS_PORT->ODR = Data;
	LCD_WR_HIGH;
	LCD_CS_HIGH;	
#else
	//---------------------Write Index
	LCD_RD_HIGH;
	LCD_CS_LOW;
	
	LCD_DC_LOW;		//RS
	
	LCD_WR_LOW;
	LCD_DATABUS_PORT->ODR = Index>>8;
	LCD_WR_HIGH;
	
	LCD_WR_LOW;
	LCD_DATABUS_PORT->ODR = Index;
	LCD_WR_HIGH;
	
	LCD_DC_HIGH;	//RS
	//---------------------Write Data
	LCD_WR_LOW;
	LCD_DATABUS_PORT->ODR = Data>>8;
	LCD_WR_HIGH;
	
	LCD_WR_LOW;
	LCD_DATABUS_PORT->ODR = Data;
	LCD_WR_HIGH;
	
	LCD_CS_HIGH;		
#endif
}
/*******************************************************************************
* ������			:	LCD_ReadRegister
* ��������		:	��ָ���Ĵ��� 
* ����			: void
* ����ֵ			: void
* �޸�ʱ��		: ��
* �޸�����		: ��
* ����			: wegam@sina.com
*******************************************************************************/
unsigned short LCD_ReadRegister(unsigned	short	Index)
{
	unsigned short Data	=	0;
#ifdef	Bus16Bit
	//---------------------Write Index
	LCD_RD_HIGH;
	LCD_CS_LOW;
	
	LCD_DC_LOW;		//RS
	LCD_WR_LOW;
	LCD_DATABUS_PORT->ODR = Index;
	LCD_WR_HIGH;
	LCD_DC_HIGH;	//RS
	//---------------------Write Data
	GPIO_Configuration_IPU	(LCD_DATABUS_PORT,LCD_DATABUS_Pin);			//��GPIO��Ӧ�ܽ�����Ϊ��������ģʽ----V20170605
	LCD_RD_LOW;
	Data	=	LCD_DATABUS_PORT->IDR;
	LCD_RD_HIGH;
	LCD_CS_HIGH;
	GPIO_Configuration_OPP50	(LCD_DATABUS_PORT,LCD_DATABUS_Pin);		//��GPIO��Ӧ�ܽ�����ΪPP(����)���ģʽ������ٶ�2MHz----V20170605
#else
	//---------------------Write Index
	LCD_RD_HIGH;
	LCD_CS_LOW;
	
	LCD_DC_LOW;		//RS
	
	LCD_WR_LOW;
	LCD_DATABUS_PORT->ODR = Index>>8;
	LCD_WR_HIGH;
	
	LCD_WR_LOW;
	LCD_DATABUS_PORT->ODR = Index;
	LCD_WR_HIGH;
	
	LCD_DC_HIGH;	//RS
	//---------------------Write Data
	GPIO_Configuration_IPU	(LCD_DATABUS_PORT,LCD_DATABUS_Pin);			//��GPIO��Ӧ�ܽ�����Ϊ��������ģʽ----V20170605
	LCD_RD_LOW;
	Data	=	LCD_DATABUS_PORT->IDR;
	LCD_RD_HIGH;
	
	Data	<<=8;
	
	LCD_RD_LOW;
	Data	|=	LCD_DATABUS_PORT->IDR;
	LCD_RD_HIGH;	
	LCD_CS_HIGH;
	GPIO_Configuration_OPP50	(LCD_DATABUS_PORT,LCD_DATABUS_Pin);		//��GPIO��Ӧ�ܽ�����ΪPP(����)���ģʽ������ٶ�2MHz----V20170605
#endif
	return Data;
}

/*******************************************************************************
*������			:	LCD_Clean
*��������		:	�������������Ļ����---�ñ���ɫ�����Ļ
*����				: 
*����ֵ			:	��
*******************************************************************************/
void LCD_Clean(u16 Color)	//�����Ļ����
{
	LCDSYS->Display.Clean(Color);
}

/*******************************************************************************
*������			:	LCD_DrawPoint
*��������		:	����
*����				: 
*����ֵ			:	��
*******************************************************************************/
void LCD_DrawDot(
									unsigned short HSX,			//��X����*/
									unsigned short HSY,			//��Y����*/
									unsigned short Color		//����ɫ*/	
								)
{
	LCDSYS->Display.DrawDot(HSX,HSY,Color);
}
/*******************************************************************************
*������		:	LCD_DrawLine
*��������	:	����
*����			: x1,y1:�������
						x2,y2:�յ�����
*���			:	��
*����ֵ		:	��
*����			:
*******************************************************************************/
void LCD_DrawLine(
									unsigned short HSX, unsigned short HSY, 	//x1,y1:�������
									unsigned short HEX, unsigned short HEY,		//x2,y2:�յ�����
									unsigned short Color					//��ɫ
)
{
	LCDSYS->Display.DrawLine(HSX,HSY,HEX,HEY,Color);
}
/**************************************************************************************************
* [Function] LCD_DrawCircle:  �������ܡ�ע������ȵ�����
* [param01]t_Point point: description
* [param02]u16 R: description
* [param03]uint8_t Filled: description
* [param04]u16 color: description
**************************************************************************************************/
void LCD_DrawCircle(
												u16 x,u16 y,		//Բ������ԭ��
												u16 r,					//�뾶
												u8 Filled,			//�Ƿ����
												u16 Color				//��ɫ
												)
{
	LCDSYS->Display.DrawCircle(x,y,r,Filled,Color);
}
/**************************************************************************************************
* [Function] LCD_DrawRectangle:  ��һ�¾��ο�
* [param01]t_Point top_p: ��������ֵ
* [param02]t_Point botton_p : �ذ�����ֵ
**************************************************************************************************/
void LCD_DrawRectangle(u16 x1,u16 y1,u16 x2,u16 y2,u16 Color)
{
	LCDSYS->Display.DrawRectangle(x1,y1,x2,y2,Color);
}
/*******************************************************************************
*������			:	LCD_DrawPoint_big
*��������		:	��ָ�����������ָ����ɫ;�����С:(xend-xsta)*(yend-ysta)
*����				: 
*����ֵ			:	��
*******************************************************************************/
void LCD_Fill(
							unsigned short x1, unsigned short y1, 	//x1,y1:�������
							unsigned short x2, unsigned short y2,		//x2,y2:�յ�����
							u16 Color
)
{ 
	LCDSYS->Display.Fill(x1,y1,x2,y2,Color);
}
/**************************************************************************************************
* [Function] R61509V_Setbackground:  ���ñ�����ɫ
* [param01]u16 BackColor: ������ɫֵ
**************************************************************************************************/
void LCD_SetBackground(  u16 BackColor )
{
  LCDSYS->Data.BColor = BackColor;
	LCD_Clean(BackColor);	//�����Ļ����
}
/*******************************************************************************
* ������			:	LCD_ShowAntenna
* ��������		:	��ʾ12x12���� 
* ����			: Num 01234���������ź�ǿ�ȡ�
* ����ֵ			: void
*******************************************************************************/
void LCD_ShowAntenna(
                    u16 x,			//x				:���x����
										u16 y,			//y				:���y����
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
* ������			:	LCD_ShowBattery
* ��������		:	��ʾ12x12��� 
* ����			: Num 01234�����ص�����
* ����ֵ			: void
*******************************************************************************/
void LCD_ShowBattery(
                    u16 x,			//x				:���x����
										u16 y,			//y				:���y����
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
* ������			:	function
* ��������		:	��������˵�� 
* ����			: void
* ����ֵ			: void
*******************************************************************************/
void LCD_ShowChar(
										u16 x,			//x				:���x����
										u16 y,			//y				:���y����
										u8 font,		//font		:�����С
										u16 color,	//������ɫ
										u8 num,			//num			:�ֽ���
										u8 *Buffer	//Buffer	:��ʾ�����ݻ���
										
)		//��ͨ�ֿ���Գ���
{
	LCDSYS->Display.ShowChar(x,y,font,color,num,Buffer);
}
/*******************************************************************************
* ������			:	function
* ��������		:	��������˵�� 
* ����			: void
* ����ֵ			: void
*******************************************************************************/
void LCD_ShowWord(
										u16 x,			//x				:���x����
										u16 y,			//y				:���y����
										u8 font,		//font		:�����С
										u16 color,	//������ɫ
										u8 num,			//num			:�ֽ���
										u8 *Buffer	//Buffer	:��ʾ�����ݻ���
										
)		//��ͨ�ֿ���Գ���
{
	LCDSYS->Display.ShowWord(x,y,font,color,num,Buffer);
}
/*******************************************************************************
* ������			:	function
* ��������		:	��������˵�� 
* ����			: void
* ����ֵ			: void
* �޸�ʱ��		: ��
* �޸�����		: ��
* ����			: wegam@sina.com
*******************************************************************************/
unsigned short LCD_GetDispCodeBuffer(
													u8 font,								//�����С
													u16 word,								//�ַ�����ֵ
													u8 *ReadBuffer				  //�������ݵĻ���
												)
{
	unsigned short lengh=0;
	lengh	=	GT32L32_GetCode(font,word,ReadBuffer);		//���ֿ��ж����ݲ��������ݳ���
	return lengh;
}
/*******************************************************************************
* ������			:	function
* ��������		:	��������˵�� 
* ����			: void
* ����ֵ			: void
*******************************************************************************/
void LCD_Show(
							u16 x,			//x				:���x����
							u16 y,			//y				:���y����
							u8 font,		//font		:�����С
							u16 PenColor,//������ɫ
							u8 num,			//num			:�ֽ���
							u8 *Buffer	//Buffer	:��ʾ�����ݻ���
)		//��ͨ�ֿ���Գ���
{
	unsigned short	MaxV,MaxH;	//�߽�ֵ
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
		
		//A=====================˫�ֽ�--����
		if(dst>0x80)
		{
			u16 word=dst<<8;
      
			dst=Buffer[i+1];
			word=word|dst;			
			//A1=====================��ʾ���޻���
      if(x>MaxH-font)
      {
        x=0;
        y+=font;
      }
      //A2=====================��ʾ����β����ԭ�㿪ʼ
      if(y>MaxV-font)
      {
        y=x=0;
      }
      //A3=====================��ȡ��������
			GetBufferLength	=	LCD_GetDispCodeBuffer(font,word,CodeBuffer);		//���ֿ��ж����ݲ��������ݳ���
			//A4=====================д����Ļ
			LCD_ShowWord(x,y,font,PenColor,GetBufferLength,CodeBuffer);
			//A5=====================ˮƽ��ʾ��ַ����
      x+=font;
			i++;		//˫�ֽڣ�������			
		}
		else if(('\r'==dst)||('\n'==dst))
		{
			if(('\n'==Buffer[i+1])||('\r'==Buffer[i+1]))
			{
				i++;	//ȥ���س�������
			}
			if(y>MaxV-font)
      {
        y=x=0;
      }
			else
			{
				x=0;
				y+=font;
			}
			goto LCD_ShowJump;
		}
		//B=====================���ֽ�--ASCII�ַ���
		else
		{			
			//B1=====================��ʾ���޻���
      if(x>MaxH-font/2)
      {
        x=0;
        y+=font;
      }
      //B2=====================��ʾ����β����ԭ�㿪ʼ
      if(y>MaxV-font)
      {
        y=x=0;
      }
      //B3=====================��ȡ��������
			GetBufferLength	=	LCD_GetDispCodeBuffer(font,(u16)dst,CodeBuffer);		//���ֿ��ж����ݲ��������ݳ���
			//=======================ˮƽ�Ʊ�����ո���ʾ(�����ֿ�ᵱ0xFF���)
			if(	('	'	==	(char)dst)		//ˮƽ�Ʊ��
				||(' '	==	(char)dst))		//�ո�
			{
				memset(CodeBuffer,0x00,GetBufferLength);
			}
			//B4=====================д����Ļ
			LCD_ShowChar(x,y,font,PenColor,GetBufferLength,CodeBuffer);
			//B5=====================ˮƽ��ʾ��ַ����
      x+=font/2;						
		}
		LCD_ShowJump:
			__nop();
	}
}
/*******************************************************************************
* ������			:	LCD_ShowScroll
* ��������		:	������ʾ 
* ����			: void
* ����ֵ			: void
*******************************************************************************/
void LCD_ShowScroll(stLCDScroll	*ScrollBuff)		//��ͨ�ֿ���Գ���
{
	unsigned short	MaxV,MaxH;	//�߽�ֵ
	unsigned char i=0;
	unsigned char CodeBuffer[130]={0};
	unsigned char	num		=	ScrollBuff->length;
	unsigned char	font	=	0;
	unsigned char* Buffer	=NULL;
	unsigned	short x,y;
	stLCDScroll*	TempBuff;
	if(NULL==	ScrollBuff)
	{
		return;
	}
	TempBuff	=	ScrollBuff;
	
//	LCD_Show(TempBuff->startx,TempBuff->starty,TempBuff->font,TempBuff->color,TempBuff->length,TempBuff->buffer);
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
	LCD_ShowCoutinue:
	Buffer	=	&TempBuff->buffer[TempBuff->starty];
	for(i=0;i<num;i++)
	{
		unsigned char GetBufferLength	=	0;
		unsigned char dst=Buffer[i];
		
		//A=====================˫�ֽ�--����
		if(dst>0x80)
		{
			
			u16 word=dst<<8;
      
			TempBuff->starty+=2;
			dst=Buffer[i+1];
			word=word|dst;			
			//A1=====================��ʾ���޻���
      if(x>MaxH-font)
      {
        x=0;
        y+=font;
      }
      //A2=====================��ʾ����β����ԭ�㿪ʼ
      if(y>MaxV-font)
      {
        y=x=0;
      }
      //A3=====================��ȡ��������
			GetBufferLength	=	LCD_GetDispCodeBuffer(font,word,CodeBuffer);		//���ֿ��ж����ݲ��������ݳ���
			//A4=====================д����Ļ
			LCD_ShowWord(x,y,font,PenColor,GetBufferLength,CodeBuffer);
			//A5=====================ˮƽ��ʾ��ַ����
      x+=font;
			i++;		//˫�ֽڣ�������			
		}
		//B=====================���ֽ�--ASCII�ַ���
		else
		{			
			//B1=====================��ʾ���޻���
      if(x>MaxH-font/2)
      {
        x=0;
        y+=font;
      }
      //B2=====================��ʾ����β����ԭ�㿪ʼ
      if(y>MaxV-font)
      {
        y=x=0;
      }
      //B3=====================��ȡ��������
			GetBufferLength	=	LCD_GetDispCodeBuffer(font,(u16)dst,CodeBuffer);		//���ֿ��ж����ݲ��������ݳ���
			//=======================ˮƽ�Ʊ�����ո���ʾ(�����ֿ�ᵱ0xFF���)
			if(	('	'	==	(char)dst)		//ˮƽ�Ʊ��
				||(' '	==	(char)dst))		//�ո�
			{
				memset(CodeBuffer,0x00,GetBufferLength);
			}
			//B4=====================д����Ļ
			LCD_ShowChar(x,y,font,PenColor,GetBufferLength,CodeBuffer);
			//B5=====================ˮƽ��ʾ��ַ����
      x+=font/2;						
		}
		LCD_ShowJump:
			__nop();
	}
}
/*******************************************************************************
* ������			:	LCD_ShowHex
* ��������		:	ʮ��������ʾ 
* ����			: void
* ����ֵ			: void
*******************************************************************************/
void LCD_ShowHex(
							u16 x,			//x				:���x����
							u16 y,			//y				:���y����
							u8 font,		//font		:�����С
							u16 color,	///������ɫ
							u8 num,			//num			:���ݸ���
              u8 bitnum,  //num			:λ��
							u8 *Buffer	//Buffer	:��ʾ�����ݻ���
)		//��ͨ�ֿ���Գ���
{
	unsigned short	MaxV,MaxH;	//�߽�ֵ
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
      //=============================8λ��ʾ��ʽ      
      unsigned char dst=(((u32)Buffer[i]>>(Cril-1)*4)&0x0F);
      //1=====================ת��ΪASSIC��
      if(dst<=9)
      {
        dst+=0x30;
      }
      else if((10<=dst)&&(15>=dst))
      {
        dst+=0x37;
      }
      //1=====================��ʾ���޻���
      if(x>MaxH-font/2)
      {
        x=0;
        y+=font;
      }
      //2=====================��ʾ����β����ԭ�㿪ʼ
      if(y>MaxV-font)
      {
        y=x=0;
      }
      //3=====================��ȡ��������
      GetBufferLength	=	LCD_GetDispCodeBuffer(font,dst,CodeBuffer);		//���ֿ��ж����ݲ��������ݳ���
      //4=====================д����Ļ
      LCD_ShowChar(x,y,font,color,GetBufferLength,CodeBuffer);
      //5=====================��ʾ��ַ����
      x+=font/2;
    }
    //5=====================��ʾ��ַ����(���ӿո�λ)
    x+=font/2;
		if(x>MaxH-font)
		{
			y+=font;
			x=0;
		}
	}
}
/*******************************************************************************
*������		:	LCD_ShowString
*��������	:	��ʾ�ַ�����ͨ�ֿ�
*����			: x,y:�������
						*p:�ַ�����ʼ��ַ
						��16����
*���			:	��
*����ֵ		:	��
*����			:
*******************************************************************************/
unsigned int LCD_Printf(u16 x,u16 y,u8 font,u16 color,const char *format,...)				//��ߵ�ʡ�Ժž��ǿɱ����
{ 
		
//		va_list ap; 										//VA_LIST ����C�����н����������һ��꣬����ͷ�ļ���#include <stdarg.h>,���ڻ�ȡ��ȷ�������Ĳ���
//		static char string[ 256 ];			//�������飬
//  	va_start( ap, format );
//		vsprintf( string , format, ap );    
//		va_end( ap );
	
	char	DataBuffer[256]={0};			//��¼format����
	//1)**********��ȡ���ݿ��
  u16 InputDataSize=0;		//��ȡ���ݿ��	
	//3)**********argsΪ�����һ��ָ��ɱ�����ı�����va_list�Լ��±�Ҫ�õ���va_start,va_end�������ڶ��壬�ɱ���������б���Ҫ�õ��꣬ ��stdarg.hͷ�ļ��ж���
	va_list args; 
	//5)**********��ʼ��args�ĺ�����ʹ��ָ��ɱ�����ĵ�һ��������format�ǿɱ������ǰһ������
	va_start(args, format);
	//6)**********��������·��������ִ��ĳ���(��ȥ\0),����������ظ�ֵ
	InputDataSize = vsnprintf(DataBuffer, InputDataSize,format, args);

	//7)**********�����ɱ�����Ļ�ȡ
	va_end(args);                                      		
  if((8!=font)&&(12!=font)&&(16!=font)&&(24!=font)&&(32!=font))
  {
    font  = 32;
  }
	LCD_Show(x,y,font,color,InputDataSize,(unsigned char*)DataBuffer);
	return InputDataSize;
}
/*******************************************************************************
*������		:	LCD_PrintfScroll
*��������	:	LCD������ʾ����
*����			: x,y:�������
						*p:�ַ�����ʼ��ַ
						��16����
*���			:	��
*����ֵ		:	��
*����			:
*******************************************************************************/
unsigned int LCD_PrintfScroll(u16 x,u16 y,u8 font,u16 color,const char *format,...)				//��ߵ�ʡ�Ժž��ǿɱ����
{ 
		
//		va_list ap; 										//VA_LIST ����C�����н����������һ��꣬����ͷ�ļ���#include <stdarg.h>,���ڻ�ȡ��ȷ�������Ĳ���
//		static char string[ 256 ];			//�������飬
//  	va_start( ap, format );
//		vsprintf( string , format, ap );    
//		va_end( ap );
	
	char	DataBuffer[256]={0};			//��¼format����
	//1)**********��ȡ���ݿ��
  u16 InputDataSize=0;		//��ȡ���ݿ��	
	//3)**********argsΪ�����һ��ָ��ɱ�����ı�����va_list�Լ��±�Ҫ�õ���va_start,va_end�������ڶ��壬�ɱ���������б���Ҫ�õ��꣬ ��stdarg.hͷ�ļ��ж���
	va_list args; 
	//5)**********��ʼ��args�ĺ�����ʹ��ָ��ɱ�����ĵ�һ��������format�ǿɱ������ǰһ������
	va_start(args, format);
	//6)**********��������·��������ִ��ĳ���(��ȥ\0),����������ظ�ֵ
	InputDataSize = vsnprintf(DataBuffer, InputDataSize,format, args);

	//7)**********�����ɱ�����Ļ�ȡ
	va_end(args);                                      		
  if((8!=font)&&(12!=font)&&(16!=font)&&(24!=font)&&(32!=font))
  {
    font  = 24;
  }
	if(NULL	==	ScrollBuff)
	{
		static stLCDScroll	NewBuff;		
		
		NewBuff.startx	=	x;
		NewBuff.starty	=	y;
		NewBuff.runxstart	=	0;
		NewBuff.color	=	color;
		NewBuff.font	=	font;
		NewBuff.length	=	InputDataSize;
		memcpy(NewBuff.buffer,DataBuffer,InputDataSize);
		
		ScrollBuff	=	&NewBuff;
		ScrollBuff->nextlist	=	NULL;
	}
	else
	{
		static stLCDScroll		NewBuff;
		stLCDScroll*	TempBuff;
		TempBuff	=	(stLCDScroll*)ScrollBuff->nextlist;
		while(NULL	!=	TempBuff->nextlist)
		{
			TempBuff	=	(stLCDScroll*)ScrollBuff->nextlist;
		}
		NewBuff.startx	=	x;
		NewBuff.starty	=	y;
		NewBuff.runxstart	=	0;
		NewBuff.color	=	color;
		NewBuff.font	=	font;
		NewBuff.length	=	InputDataSize;
		memcpy(NewBuff.buffer,DataBuffer,InputDataSize);
		
		NewBuff.nextlist	=	NULL;
		TempBuff->nextlist	=	(unsigned long*)&NewBuff;
	}
//	LCD_ShowScroll(x,y,font,color,InputDataSize,(unsigned char*)DataBuffer);
	return InputDataSize;
}
/*******************************************************************************
* ������			:	LCD_ShowHex
* ��������		:	ʮ��������ʾ 
* ����			: void
* ����ֵ			: void
*******************************************************************************/
void LCD_ShowBMP(
							unsigned short x1, unsigned short y1, 	//x1,y1:�������
							unsigned short x2, unsigned short y2,		//x2,y2:�յ�����
							u16 Length,   
              u8 *RGBBuffer     //RGB888���ݵ�ַ������˳��ΪBGR�����ǵ�һ�ֽ�ΪB
)		//��ͨ�ֿ���Գ���
{
	unsigned short i = 0;
  unsigned short j = 0;
  unsigned short  RGB565;
  eRotate Rotate = LCDSYS->Flag.Rotate;
  LCDSYS->Flag.Rotate  = Draw_Rotate_0D;			//ʹ����ת�Ƕ�
  LCDSYS->Display.WriteAddress(x1,y1,x2,y2);	//������ʾ����
//  LCD_WriteDataStart();
	for(i=0;i<Length;)
	{
    RGB565  = RGB888toRGB565(&RGBBuffer[i]);
    LCDSYS->Display.WriteData(RGB565);
    i+=3;
	}
//  LCD_WriteDataEnd();
  LCDSYS->Flag.Rotate  =  Rotate;
}
/*******************************************************************************
*������			:	function
*��������		:	function
*����				: 
*����ֵ			:	��
*�޸�ʱ��		:	��
*�޸�˵��		:	��
*ע��				:	wegam@sina.com
*******************************************************************************/
unsigned  short RGB888toRGB565(u8 *RGB888)
{
  unsigned  short RGB565  = 0;
  //-----------------Red:ȡ5λ
  RGB565  = RGB888[2]>>3;
  RGB565<<=5;
  //-----------------Green��ȡ5λ
  RGB565  |= RGB888[1]>>3;
  RGB565<<=6;
  //-----------------Blue��ȡ5λ
  RGB565  |= RGB888[0]>>3;
  return  RGB565;
}


/*******************************************************************************
* ������			:	LCD_DelayuS
* ��������		:	��ʱx΢��
* ����			: void
* ����ֵ			: void
*******************************************************************************/
void LCD_DelayuS(u32 xuS)
{
	SysTick_DeleyuS(xuS);				//SysTick��ʱnmS;
}
/*******************************************************************************
* ������			:	LCD_DelaymS
* ��������		:	��ʱx����
* ����			: void
* ����ֵ			: void
*******************************************************************************/
void LCD_DelaymS(u32 xms)
{
	SysTick_DeleymS(xms);				//SysTick��ʱnmS;
}
/*******************************************************************************
* ������			:	LCD_DelayS
* ��������		:	��ʱx��
* ����			: void
* ����ֵ			: void
*******************************************************************************/
void LCD_DelayS(u32 xS)
{
	SysTick_DeleyS(xS);				//SysTick��ʱnmS;
}
//#endif//LCD_61509_EN
/************************************** The End Of FILE **************************************/


