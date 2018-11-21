/**************************************************************************************************
* Һ��������IC
* �ļ�<$(filename)>
* ģ������ :	���塢���ܡ�˵��
* ��ʷ�޸ļ�¼
*     <��Ҫ�޸���>  <ʱ��>   <�汾 >   <˵��>
*     xlyan        $(Date)   1.0.0    �����ļ�
**************************************************************************************************/
#include "R61509V.h"
#include "LCD.H"

#include "STM32_GPIO.H"

#include	"stdio.h"			//����printf
#include	"string.h"		//����printf
#include	"stdarg.h"		//���ڻ�ȡ��ȷ�������Ĳ���
#include	"stdlib.h"		//malloc��̬�����ڴ�ռ�

static LCDDef	*pR61509V	=	NULL;		//�ڲ�����ʹ�ã�����ɾ��

#define	R61509V_CS_HIGH		(pR61509V->Port.sCS_PORT->BSRR	= pR61509V->Port.sCS_Pin)
#define	R61509V_CS_LOW		(pR61509V->Port.sCS_PORT->BRR	=	pR61509V->Port.sCS_Pin)

#define	R61509V_DC_HIGH		(pR61509V->Port.sDC_PORT->BSRR	= pR61509V->Port.sDC_Pin)
#define	R61509V_DC_LOW		(pR61509V->Port.sDC_PORT->BRR	= pR61509V->Port.sDC_Pin)

#define	R61509V_WR_HIGH		(pR61509V->Port.sWR_PORT->BSRR	= pR61509V->Port.sWR_Pin)
#define	R61509V_WR_LOW		(pR61509V->Port.sWR_PORT->BRR	= pR61509V->Port.sWR_Pin)

#define	R61509V_RD_HIGH		(pR61509V->Port.sRD_PORT->BSRR	= pR61509V->Port.sRD_Pin)
#define	R61509V_RD_LOW		(pR61509V->Port.sRD_PORT->BRR	= pR61509V->Port.sRD_Pin)

#define	R61509V_RST_HIGH	(pR61509V->Port.sREST_PORT->BSRR	= pR61509V->Port.sREST_Pin)
#define	R61509V_RST_LOW		(pR61509V->Port.sREST_PORT->BRR	= pR61509V->Port.sREST_Pin)

#define	R61509V_TE_HIGH		(pR61509V->Port.sTE_PORT->BSRR	= pR61509V->Port.sTE_Pin)
#define	R61509V_TE_LOW		(pR61509V->Port.sTE_PORT->BRR	= pR61509V->Port.sTE_Pin)

#define	R61509V_BL_HIGH		(pR61509V->Port.sBL_PORT->BSRR	= pR61509V->Port.sBL_Pin)
#define	R61509V_BL_LOW		(pR61509V->Port.sBL_PORT->BRR	= pR61509V->Port.sBL_Pin)

#define R61509V_DATABUS_PORT	(pR61509V->Port.sDATABUS_PORT)
#define R61509V_DATABUS_Pin		(pR61509V->Port.sDATABUS_Pin)

#define	R61509VSet(n)	R61509V_##n##_HIGH
#define	R61509VCrl(n)	R61509V_##n##_LOW

/*******************************************************************************
* ������			:	function
* ��������		:	��������˵�� 
* ����			: void
* ����ֵ			: void
*******************************************************************************/
unsigned short R61509V_Initialize(void*	pInfo)
{
	static unsigned short	DeviceCode	=	0;
	LCDPortDef*	Port	=	NULL;
	if(NULL==	pInfo)
		return 0;
	
	pR61509V		=	(LCDDef*)pInfo;		//ָ��ָ��
	Port	=	&pR61509V->Port;
	
	//==========================GPIO����
	GPIO_Configuration_OPP50	(Port->sBL_PORT,				Port->sBL_Pin);					//��GPIO��Ӧ�ܽ�����ΪPP(����)���ģʽ������ٶ�2MHz----V20170605
	GPIO_Configuration_OPP50	(Port->sRD_PORT,				Port->sRD_Pin);					//��GPIO��Ӧ�ܽ�����ΪPP(����)���ģʽ������ٶ�2MHz----V20170605
	GPIO_Configuration_OPP50	(Port->sREST_PORT,			Port->sREST_Pin);				//��GPIO��Ӧ�ܽ�����ΪPP(����)���ģʽ������ٶ�2MHz----V20170605
	GPIO_Configuration_OPP50	(Port->sDC_PORT,				Port->sDC_Pin);					//��GPIO��Ӧ�ܽ�����ΪPP(����)���ģʽ������ٶ�2MHz----V20170605
	GPIO_Configuration_OPP50	(Port->sWR_PORT,				Port->sWR_Pin);					//��GPIO��Ӧ�ܽ�����ΪPP(����)���ģʽ������ٶ�2MHz----V20170605
	GPIO_Configuration_OPP50	(Port->sCS_PORT,				Port->sCS_Pin);					//��GPIO��Ӧ�ܽ�����ΪPP(����)���ģʽ������ٶ�2MHz----V20170605
	GPIO_Configuration_OPP50	(Port->sTE_PORT,				Port->sTE_Pin);					//��GPIO��Ӧ�ܽ�����ΪPP(����)���ģʽ������ٶ�2MHz----V20170605
	GPIO_Configuration_OPP50	(Port->sDATABUS_PORT,		Port->sDATABUS_Pin);		//��GPIO��Ӧ�ܽ�����ΪPP(����)���ģʽ������ٶ�2MHz----V20170605
	
	DeviceCode	=	R61509V_ReadRegister(R61509V_R000_IR);
	if(0xB509	!=	DeviceCode)
	{
		return 0;	//ʶ��ʧ��
	}
	//==========================��鱳��ɫ�뻭��ɫ�Ƿ���ͬ
	if(pR61509V->Data.PColor	==	pR61509V->Data.BColor)
	{
		pR61509V->Data.PColor	=	pR61509V->Data.BColor^0xFFFF;
	}
	
	pR61509V->Data.MaxH	=	R61509V_H;					//���ˮƽ���
	pR61509V->Data.MaxV	=	R61509V_V;					//���ֱ�߶�	
	
	//==========================�ӿں���
	pR61509V->Display.WriteAddress		=	R61509V_SetWindowAddress;
	pR61509V->Display.PowerOn					=	R61509V_PowerOn;
	pR61509V->Display.DispOff					=	R61509V_PowerOff;
	
	pR61509V->Display.DrawDot					=	R61509V_DrawDot;
	pR61509V->Display.DrawLine				=	R61509V_DrawLine;
	pR61509V->Display.DrawCircle			=	R61509V_DrawCircle;
	pR61509V->Display.DrawRectangle		=	R61509V_DrawRectangle;
	
	pR61509V->Display.Fill						=	R61509V_Fill;
	pR61509V->Display.Clean						=	R61509V_Clean;
	pR61509V->Display.SetBackground		=	R61509V_SetBackground;
	
	pR61509V->Display.ShowChar				=	R61509V_ShowChar;
	pR61509V->Display.ShowWord				=	R61509V_ShowWord;
	
	R61509V_PowerOn();
	R61509V_Clean(pR61509V->Data.BColor);
	
	R61509VSet(BL);
	return DeviceCode;		//���óɹ�
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
void R61509V_Reset(void)
{
	R61509VSet(RST);
	LCD_DelaymS(5);				//SysTick��ʱnmS
	R61509VCrl(RST);;
	LCD_DelaymS(5);				//SysTick��ʱnmS
	R61509VSet(RST);
	LCD_DelaymS(10);				//SysTick��ʱnmS
}
/*******************************************************************************
* ������			:	R61509V_WriteIndex
* ��������		:	дָ���Ĵ��� 
* ����			: void
* ����ֵ			: void
* �޸�ʱ��		: ��
* �޸�����		: ��
* ����			: wegam@sina.com
*******************************************************************************/
unsigned short R61509V_ReadData(void)
{
	unsigned short Data	=	0;
#if	1	//Bus16Bit
	R61509VCrl(RD);	//LCD_RD_LOW;
	Data	=	R61509V_DATABUS_PORT->IDR;
	R61509VSet(RD);	//LCD_RD_HIGH;
#else	
	R61509VCrl(RD);	//LCD_RD_LOW;
	Data	=	R61509V_DATABUS_PORT->IDR;
	R61509VSet(RD);	//LCD_RD_HIGH;
	
	Data	<<=8;
	
	R61509VCrl(RD);	//LCD_RD_LOW;
	Data	|=	R61509V_DATABUS_PORT->IDR;
	R61509VSet(RD);	//LCD_RD_HIGH;
#endif	
	return Data;
}
/*******************************************************************************
* ������			:	R61509V_ReadRegister
* ��������		:	��ָ���Ĵ��� 
* ����			: void
* ����ֵ			: void
* �޸�ʱ��		: ��
* �޸�����		: ��
* ����			: wegam@sina.com
*******************************************************************************/
unsigned short R61509V_ReadRegister(unsigned	short	Addr)
{
	unsigned short Data	=	0;
	R61509VCrl(CS);	//LCD_CS_LOW;
	//---------------------Write Index
	R61509V_WriteAddr(Addr);
	//---------------------Read Data
	GPIO_Configuration_IPU	(R61509V_DATABUS_PORT,R61509V_DATABUS_Pin);			//��GPIO��Ӧ�ܽ�����Ϊ��������ģʽ----V20170605
	Data	=	R61509V_ReadData();
	R61509VSet(CS);	//LCD_CS_HIGH;
	GPIO_Configuration_OPP50	(R61509V_DATABUS_PORT,R61509V_DATABUS_Pin);		//��GPIO��Ӧ�ܽ�����ΪPP(����)���ģʽ������ٶ�2MHz----V20170605	
	return Data;
}
/*******************************************************************************
* ������			:	R61509V_WriteIndex
* ��������		:	дָ���Ĵ��� 
* ����			: void
* ����ֵ			: void
* �޸�ʱ��		: ��
* �޸�����		: ��
* ����			: wegam@sina.com
*******************************************************************************/
void R61509V_WriteData(unsigned	short	Data)
{
#if	1	//Bus16Bit
	R61509VCrl(WR);	//LCD_WR_LOW;
	R61509V_DATABUS_PORT->ODR = Data;
	R61509VSet(WR);	//LCD_WR_HIGH;
#else
	R61509VCrl(WR);	//LCD_WR_LOW;
	R61509V_DATABUS_PORT->ODR = Data>>8;
	R61509VSet(WR);	//LCD_WR_HIGH;
	
	R61509VCrl(WR);	//LCD_WR_LOW;
	R61509V_DATABUS_PORT->ODR = Data&0xFF;
	R61509VSet(WR);	//LCD_WR_HIGH;
#endif
}
/*******************************************************************************
* ������			:	ILI9326_WriteAddr
* ��������		:	дָ���Ĵ��� 
* ����			: void
* ����ֵ			: void
* �޸�ʱ��		: ��
* �޸�����		: ��
* ����			: wegam@sina.com
*******************************************************************************/
void R61509V_WriteAddr(unsigned	short	Addr)
{
	R61509VCrl(DC);	//LCD_DC_LOW;		//RS
	R61509V_WriteData(Addr);
	R61509VSet(DC);	//LCD_DC_HIGH;	//RS
}
/*******************************************************************************
* ������			:	R61509V_WriteIndex
* ��������		:	дָ���Ĵ��� 
* ����			: void
* ����ֵ			: void
* �޸�ʱ��		: ��
* �޸�����		: ��
* ����			: wegam@sina.com
*******************************************************************************/
void R61509V_WriteIndex(unsigned	short	Index)
{
	R61509VCrl(CS);	//LCD_CS_LOW;	
	R61509V_WriteAddr(Index);
	R61509VSet(CS);	//LCD_CS_HIGH;
}
/*******************************************************************************
* ������			:	R61509V_WriteRegister
* ��������		:	дָ���Ĵ��� 
* ����			: void
* ����ֵ			: void
* �޸�ʱ��		: ��
* �޸�����		: ��
* ����			: wegam@sina.com
*******************************************************************************/
void R61509V_WriteRegister(unsigned	short	Addr,unsigned short Data)
{
	R61509VCrl(CS);	//LCD_CS_LOW;	
	//---------------------Write Index
	R61509V_WriteAddr(Addr);
	//---------------------Write Data
	R61509V_WriteData(Data);	
	R61509VSet(CS);	//LCD_CS_HIGH;	
}
/*******************************************************************************
* ������			:	R61509V_WriteCommand
* ��������		:	��ָ���Ĵ��� 
* ����			: void
* ����ֵ			: void
* �޸�ʱ��		: ��
* �޸�����		: ��
* ����			: wegam@sina.com
*******************************************************************************/
void R61509V_WriteCommand(unsigned	short	Index,unsigned short Cmd)
{
	R61509V_WriteRegister(Index,Cmd);
}
/*******************************************************************************
* ������			:	R61509V_WriteGRAM
* ��������		:	дָ���Ĵ��� 
* ����			: void
* ����ֵ			: void
* �޸�ʱ��		: ��
* �޸�����		: ��
* ����			: wegam@sina.com
*******************************************************************************/
void R61509V_WriteGRAM(unsigned	short* RAM,unsigned long length)
{
	unsigned	long	i	=	0;
	R61509VCrl(CS);	//LCD_CS_LOW;
	R61509V_WriteAddr(R61509V_R202_GDRW);
	for(i=0;i<length;i++)
	{
		R61509V_WriteData(RAM[i]);
	}
	R61509VSet(CS);	//LCD_CS_HIGH;
}
/*******************************************************************************
* ������			:	R61509V_WriteGRAM
* ��������		:	дָ���Ĵ��� 
* ����			: void
* ����ֵ			: void
* �޸�ʱ��		: ��
* �޸�����		: ��
* ����			: wegam@sina.com
*******************************************************************************/
void R61509V_ReadGRAM(unsigned	short* RAM,unsigned long length)
{
	unsigned	long	i	=	0;
	R61509VCrl(CS);	//LCD_CS_LOW;
	R61509V_WriteIndex(R61509V_R202_GDRW);
	GPIO_Configuration_IPU	(R61509V_DATABUS_PORT,R61509V_DATABUS_Pin);			//��GPIO��Ӧ�ܽ�����Ϊ��������ģʽ----V20170605
	for(i=0;i<length;i++)
	{
		RAM[i]=R61509V_ReadData();
	}
	R61509VSet(CS);	//LCD_CS_HIGH;
	GPIO_Configuration_OPP50	(R61509V_DATABUS_PORT,R61509V_DATABUS_Pin);		//��GPIO��Ӧ�ܽ�����ΪPP(����)���ģʽ������ٶ�2MHz----V20170605	
}
/**************************************************************************************************
* [Function] LCD_PowerOff:  �ر�LCD ��Դ
* [No param]
**************************************************************************************************/
void R61509V_PowerOff( void )
{
	LCD_BL_OFF;		//�ر���
	R61509V_WriteCommand( R61509V_R009_DC3, 0 );	
}
/*******************************************************************************
*������			:	R61509V_Initialize
*��������		:	IC��ʼ������������оƬR61509V��power supply on sequence ��������
*����				: 
*����ֵ			:	��
*******************************************************************************/
void R61509V_PowerOn(void)			//��������оƬR61509V��power supply on sequence ��������
{
	u32 dtime=2000;
	
	void(*Command)(unsigned short Index,unsigned short Command);//LcdDisplay.WriteCommand
	
	void(*DelaymS)(unsigned long xms) = LCD_DelaymS;
	
	Command	=	R61509V_WriteCommand;

	
	R61509V_Reset();
	DelaymS( 10 );
	
	Command(R61509V_R000_IR		,	0x0000);	//�Ĵ�д0x00
	Command(R61509V_R000_IR		,	0x0000);	//�Ĵ�д0x00
	Command(R61509V_R000_IR		,	0x0000);	//�Ĵ�д0x00
	Command(R61509V_R000_IR		,	0x0000);	//�Ĵ�д0x00
	
	DelaymS( 10 );
	
	Command(R61509V_R001_DOC	,	0x0300);	//--------��ʾ�������When SS = ��1�� and BGR = ��1��, RGB dots are assigned one to one from S720 to S1.
	Command(R61509V_R002_DWC	,	0x0100);	//--------	
	Command(R61509V_R003_EM		,	0X5030);	//--------RGB��Ϊ5-6-5ģʽ------------0X5030
	Command(R61509V_R007_DC1	,	0x0100);	//--------������ʾ����base image�Ĺ��뿪
	Command(R61509V_R008_DC2	,	0X0808);	//--------
	Command(R61509V_R009_DC3	,	0x0001);	//--------	
	
	Command(R61509V_R00B_ECC		,	0x0001);	//--------
	Command(R61509V_R00C_EDIC1	,	0x0000);	//--------
	Command(R61509V_R00F_EDIC2	,	0x0000);	//--------
	
	DelaymS( 10 );
	
	Command(R61509V_R010_PIC1	,	0x0019);	//--------���Ƶ��--0x19
	Command(R61509V_R011_PIC2	,	0x0101);	//--------		Panel Interface Control 2 (R011h)
	Command(R61509V_R012_PIC3	,	0x0000);	//--------
	Command(R61509V_R013_PIC4	,	0x0001);	//--------
	Command(R61509V_R014_PIC5	,	0x0055);	//--------
	Command(R61509V_R020_PIC6	,	0x0010);	//--------
	Command(R61509V_R021_PIC7	,	0x0101);	//--------
	Command(R61509V_R022_PIC8	,	0x0000);	//--------
	Command(R61509V_R023_PIC9	,	0x0001);	//--------	
	
	DelaymS( 10 );
	
	Command(R61509V_R090_FMC		,	0x8000);	//--------���������ƣ�FMARK interface
	
	Command(R61509V_R100_PC1		,	0x0330);	//--------���õ�Դ���ƣ�ƽ����ʾ�������
	Command(R61509V_R101_PC2		,	0x0227);	//--------Power Control 2
	Command(R61509V_R102_PC3		,	0xC1B0);	//--------PSON,PON ����Ϊ1����Դ��Ӧ��
	Command(R61509V_R103_PC4		,	0x0D00);	//--------	
	
	DelaymS( 20 );
	
	Command(R61509V_R200_HA			,	0x0000);	//--------RAM address ����
	Command(R61509V_R201_VA			,	0x0000);	//--------
	
	Command(R61509V_R280_NVM		,	0xB000);	//--------VCM
	
	Command(R61509V_R300_YC1		,	0x0C00);	//--------
	Command(R61509V_R301_YC2		,	0x5A0B);	//--------
	Command(R61509V_R302_YC3		,	0x0906);	//--------
	Command(R61509V_R303_YC4		,	0x1017);	//--------
	Command(R61509V_R304_YC5		,	0x2300);	//--------
	Command(R61509V_R305_YC6		,	0x1700);	//--------
	Command(R61509V_R306_YC7		,	0x6309);	//--------
	Command(R61509V_R307_YC8		,	0x0C09);	//--------
	Command(R61509V_R308_YC9		,	0x100C);	//--------
	Command(R61509V_R309_YC10		,	0x2232);	//--------
	
	DelaymS( 10 );
	
	Command(R61509V_R400_BINL		,	0X6400);	//base image ���� 400��
	Command(R61509V_R401_BIDC		,	0x0004);	//--------����base image ����ģʽ����������(��ɫ�������ã�
	Command(R61509V_R404_BIVSC	,	0x0000);	//--------��0�߿�ʼ����
	
	Command(R61509V_R502_PTEA		,	0x005f);
	DelaymS( 10 );
}
/*******************************************************************************
*������			:	R61509V_SetWindowAddress
*��������		:	���ô��ڵ�ַ
*����				: 
*����ֵ			:	��
*******************************************************************************/
void R61509V_SetWindowAddress(			//���ô��ڵ�ַ
															unsigned short x1,		//ˮƽ��ʼ��
															unsigned short y1,		//ˮƽ��ֹ��
															unsigned short x2,		//��ֱ��ʼ��
															unsigned short y2			//��ֱ��ֹ��
															)
{	
	unsigned short MaxH,MaxV;
	unsigned short Model	=	0x5030;
	eRotate	Rotate	=	pR61509V->Flag.Rotate;
	
	void(*Command)(unsigned short Index,unsigned short Command);//LcdDisplay.WriteCommand	
	Command	=	R61509V_WriteCommand;
	
	MaxH	=	pR61509V->Data.MaxH;
	MaxV	=	pR61509V->Data.MaxV;
	
	switch(Rotate)
	{
		case 	Draw_Rotate_0D:
					pR61509V->Data.HSX	=	x1;
					pR61509V->Data.HEX	=	x2;
					pR61509V->Data.VSY	=	y1;
					pR61509V->Data.VEY	=	y2;	
					pR61509V->Data.HXA	=	pR61509V->Data.HSX;
					pR61509V->Data.VYA	=	pR61509V->Data.VSY;	
					Model	=	0x5030;
			break;
		case 	Draw_Rotate_90D:
					pR61509V->Data.HSX	=	y1;
					pR61509V->Data.HEX	=	y2;	
					pR61509V->Data.VSY	=	MaxV	-	x2	-	1;
					pR61509V->Data.VEY	=	MaxV	-	x1	-	1;	
					pR61509V->Data.HXA	=	pR61509V->Data.HSX;
					pR61509V->Data.VYA	=	pR61509V->Data.VEY;
					Model	=	0X5018;								//GRAM(Graphics RAM--ͼ���ڴ�) Data Write (R202h)׼��д��
			break;
		case 	Draw_Rotate_180D:
					pR61509V->Data.HSX	=	MaxH	-	x2	-	1;
					pR61509V->Data.HEX	=	MaxH	-	x1	-	1;
					pR61509V->Data.VSY	=	MaxV	-	y2	-	1;
					pR61509V->Data.VEY	=	MaxV	-	y1	-	1;	
					pR61509V->Data.HXA	=	pR61509V->Data.HEX;
					pR61509V->Data.VYA	=	pR61509V->Data.VEY;	
					Model	=	0X5000;
			break;
		default:
					pR61509V->Data.HSX	=	MaxH	-	y2	-	1;
					pR61509V->Data.HEX	=	MaxH	-	y1	-	1;
					pR61509V->Data.VSY	=	x1;
					pR61509V->Data.VEY	=	x2;	
					pR61509V->Data.HXA	=	pR61509V->Data.HEX;
					pR61509V->Data.VYA	=	pR61509V->Data.VSY;
					Model	=	0X5028;
			break;
	}
	//======================================��������
	R61509V_WriteRegister(R61509V_R210_HSA,pR61509V->Data.HSX);		//Window Horizontal RAM Address Start(R210h)		//ˮƽ
	R61509V_WriteRegister(R61509V_R211_HEA,pR61509V->Data.HEX);		//Window Horizontal RAM Address End(R211h)			//ˮƽ
	R61509V_WriteRegister(R61509V_R212_VSA,pR61509V->Data.VSY);		//Window Vertical RAM Address Start (R212h)			//��ֱ
	R61509V_WriteRegister(R61509V_R213_VEA,pR61509V->Data.VEY);		//Window Vertical RAM Address End (R213h)				//��ֱ
	//======================================������ʼ��
	R61509V_WriteRegister(R61509V_R200_HA,pR61509V->Data.HXA);			//RAM Address Set (Horizontal Address) (R200h)
	R61509V_WriteRegister(R61509V_R201_VA,pR61509V->Data.VYA);			//RAM Address Set (Vertical Address) (R201h)
	//======================================����д��ģʽ
	R61509V_WriteRegister(R61509V_R003_EM,Model);						//RAM Address Set (Vertical Address) (R201h)
	//======================================����д��
	R61509V_WriteIndex(R61509V_R202_GDRW);		//GRAM(Graphics RAM--ͼ���ڴ�) Data Write (R202h)׼��д��
}
//
//--------------------------------------------------------------GUI
//
/*******************************************************************************
*������			:	LCD_DrawPoint
*��������		:	����
*����				: 
*����ֵ			:	��
*******************************************************************************/
void R61509V_DrawDot(
									unsigned short HSX,			//��X����*/
									unsigned short HSY,			//��Y����*/
									unsigned short Color		//����ɫ*/	
								)
{
	R61509V_SetWindowAddress(HSX,HSY,HSX,HSY);	//���ù��λ��
	R61509V_WriteGRAM(&Color,1);
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
void R61509V_DrawLine(
									unsigned short HSX, unsigned short HSY, 	//x1,y1:�������
									unsigned short HEX, unsigned short HEY,		//x2,y2:�յ�����
									unsigned short Color					//��ɫ
)
{
	u16 t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance; 
	int incx,incy,uRow,uCol; 

	delta_x=HEX-HSX; //������������ 
	delta_y=HEY-HSY; 
	uRow=HSX; 
	uCol=HSY;
	
	if(delta_x>0)
		incx=1; //���õ������� 
	else if(delta_x==0)
		incx=0;//��ֱ�� 
	else
	{
		incx=-1;
		delta_x=-delta_x;
	}
		
	if(delta_y>0)
		incy=1; 
	else if(delta_y==0)
		incy=0;//ˮƽ�� 
	else
		{incy=-1;delta_y=-delta_y;}
		
	if( delta_x>delta_y)
		distance=delta_x; 								//ѡȡ�������������� 
	else
		distance=delta_y;
	
	for(t=0;t<distance+1;t++ )					//������� 
	{  
		R61509V_DrawDot(uRow,uCol,Color);			//���� 
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
* [Function] LCD_DrawCircle:  �������ܡ�ע������ȵ�����
* [param01]t_Point point: description
* [param02]u16 R: description
* [param03]uint8_t Filled: description
* [param04]u16 color: description
**************************************************************************************************/
void R61509V_DrawCircle(
												u16 x,u16 y,		//Բ������ԭ��
												u16 r,					//�뾶
												u8 Filled,			//�Ƿ����
												u16 color				//��ɫ
												)
{
	int a,b;
	int di;
	a=0;b=r;	  
	di=3-(r<<1);             //�ж��¸���λ�õı�־
	while(a<=b)
	{
		if(Filled)	//���ͻ���
		{
			R61509V_DrawLine(x,y,x-b,y-a,color);             //3           
			R61509V_DrawLine(x,y,x+b,y-a,color);             //0           
			R61509V_DrawLine(x,y,x-a,y+b,color);             //1       
			R61509V_DrawLine(x,y,x-b,y-a,color);             //7           
			R61509V_DrawLine(x,y,x-a,y-b,color);             //2             
			R61509V_DrawLine(x,y,x+b,y+a,color);             //4               
			R61509V_DrawLine(x,y,x+a,y-b,color);             //5
			R61509V_DrawLine(x,y,x+a,y+b,color);             //6 
			R61509V_DrawLine(x,y,x-b,y+a,color);             
			a++;
			//ʹ��Bresenham�㷨��Բ     
			if(di<0)
				di +=4*a+6;	  
			else
			{
				di+=10+4*(a-b);   
				b--;
			}
			R61509V_DrawLine(x,y,x+a,y+b,color);				//AB �������껭һ��ֱ��
		}
		else
		{
			R61509V_DrawDot(x-b,y-a,color);             //3           
			R61509V_DrawDot(x+b,y-a,color);             //0           
			R61509V_DrawDot(x-a,y+b,color);             //1       
			R61509V_DrawDot(x-b,y-a,color);             //7           
			R61509V_DrawDot(x-a,y-b,color);             //2             
			R61509V_DrawDot(x+b,y+a,color);             //4               
			R61509V_DrawDot(x+a,y-b,color);             //5
			R61509V_DrawDot(x+a,y+b,color);             //6 
			R61509V_DrawDot(x-b,y+a,color);             
			a++;
			//ʹ��Bresenham�㷨��Բ     
			if(di<0)
				di +=4*a+6;	  
			else
			{
				di+=10+4*(a-b);   
				b--;
			}
				R61509V_DrawDot(x+a,y+b,color);
		}
	}
}
/**************************************************************************************************
* [Function] LCD_DrawRectangle:  ��һ�¾��ο�
* [param01]t_Point top_p: ��������ֵ
* [param02]t_Point botton_p : �ذ�����ֵ
**************************************************************************************************/
void R61509V_DrawRectangle(u16 x1,u16 y1,u16 x2,u16 y2,u16 color)
{
	R61509V_DrawLine( x1, y1,	x1,	y2, color );
	R61509V_DrawLine( x1, y1,	x2,	y1, color );
	R61509V_DrawLine( x2, y1,	x2,	y2, color );
	R61509V_DrawLine( x1, y2,	x2,	y2, color );
}
/*******************************************************************************
*������			:	ILI9326_Fill
*��������		:	��ָ�����������ָ����ɫ;�����С:(xend-xsta)*(yend-ysta)
*����				: 
*����ֵ			:	��
*******************************************************************************/
void R61509V_Fill(
							unsigned short x1, unsigned short y1, 	//x1,y1:�������
							unsigned short x2, unsigned short y2,		//x2,y2:�յ�����
							u16 Color
)
{          
	unsigned int x;
	unsigned int y;	
	R61509V_SetWindowAddress(x1,y1,x2,y2);
	R61509V_WriteIndex( R61509V_R202_GDRW );
	R61509VCrl(CS);	//LCD_CS_LOW;
	for(x=0;x<=x2-x1;x++)
	{
		for(y=0;y<=y2-y1;y++)
		{
			R61509V_WriteData(Color);							//д����
		}
	}	
	R61509VSet(CS);	//LCD_CS_HIGH;
}
/*******************************************************************************
* ������			:	ILI9326_Clean
* ��������		:	��������˵�� 
* ����			: void
* ����ֵ			: void
* �޸�ʱ��		: ��
* �޸�����		: ��
* ����			: wegam@sina.com
*******************************************************************************/
void R61509V_Clean(u16 Color)	//�����Ļ����
{
	unsigned short x,y;
	unsigned short HSX,HEX,HSY,HEY,MaxH,MaxV;
	unsigned long	length	=	0;
	eRotate	Rotate	=	pR61509V->Flag.Rotate;
	
	MaxH	=	pR61509V->Data.MaxH;
	MaxV	=	pR61509V->Data.MaxV;	
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
	R61509V_Fill(HSX,HSY,HEX,HEY,Color);
}
/**************************************************************************************************
* [Function] ILI9326_SetBackground:  ���ñ�����ɫ
* [param01]u16 BackColor: ������ɫֵ
**************************************************************************************************/
void R61509V_SetBackground(  u16 BackColor )
{
	pR61509V->Data.BColor	=	BackColor;
	R61509V_Clean(BackColor);	//�����Ļ����
}

//
//--------------------------------------------�ַ���ʾ
//

/*******************************************************************************
* ������			:	function
* ��������		:	��������˵�� 
* ����			: void
* ����ֵ			: void
*******************************************************************************/
void R61509V_ShowChar(
										u16 x,			//x				:���x����
										u16 y,			//y				:���y����
										u8 font,		//font		:�����С
										u16 color,	//������ɫ
										u8 num,			//num			:�ֽ���
										u8 *Buffer	//Buffer	:��ʾ�����ݻ���
										
)		//��ͨ�ֿ���Գ���
{
	u8 temp;
	u8 i=0,j=0;
	unsigned short x1=0,x2=0,y1=0,y2=0;
	unsigned short LCD_PEN_COLOR	=	0;   	//����ɫ
	x1	=	x;
	y1	=	y;
	x2	=	x+font/2-1;		//
	y2	=	y+font-1;
	
	R61509V_SetWindowAddress(x1,y1,x2,y2);//������ʾ����	
	R61509V_WriteIndex( R61509V_R202_GDRW );
	R61509VCrl(CS);	//LCD_CS_LOW;
	for(i=0;i<num;i++)
	{ 
		temp=Buffer[i];		 					//����1608����--��ά������ʽ--�ֿ�ʹ��ʱȡ��
		for(j=0;j<8;j++)
		{
			if((temp&0x80)==0X80)
			{
				LCD_PEN_COLOR=color;
			}
			else
				LCD_PEN_COLOR=pR61509V->Data.BColor;
			R61509V_WriteData(LCD_PEN_COLOR);
			temp=temp<<1;
		}
    //=======================δ��8λ�Ĳ��䶨��
    if((24==font)||(12==font))
    {
      temp=Buffer[i+1];		 					
      for(j=0;j<4;j++)
      {
        if((temp&0x80)==0X80)
        {
          LCD_PEN_COLOR=color;
        }
        else
          LCD_PEN_COLOR=pR61509V->Data.BColor;
        R61509V_WriteData(LCD_PEN_COLOR);
        temp=temp<<1;
      }
      i++;
    }		
	}
	R61509VSet(CS);	//LCD_CS_HIGH;
}
/*******************************************************************************
* ������			:	function
* ��������		:	��������˵�� 
* ����			: void
* ����ֵ			: void
*******************************************************************************/
void R61509V_ShowWord(
										u16 x,			//x				:���x����
										u16 y,			//y				:���y����
										u8 font,		//font		:�����С
										u16 color,	//������ɫ
										u8 num,			//num			:�ֽ���
										u8 *Buffer	//Buffer	:��ʾ�����ݻ���
										
)		//��ͨ�ֿ���Գ���
{
	u8 temp;
	u8 i=0,j=0;
	unsigned short x1=0,x2=0,y1=0,y2=0;
	unsigned short LCD_PEN_COLOR	=	0;   	//����ɫ
	x1	=	x;
	y1	=	y;
  x2	=	x+font-1;
  y2	=	y+font-1;
	R61509V_SetWindowAddress(x1,y1,x2,y2);//������ʾ����
	R61509V_WriteIndex( R61509V_R202_GDRW );
	R61509VCrl(CS);	//LCD_CS_LOW;
	for(i=0;i<num;i++)
	{ 
		temp=Buffer[i];		 				
		for(j=0;j<8;j++)
		{
			if((temp&0x80)==0X80)
			{
				LCD_PEN_COLOR=color;
			}
			else
				LCD_PEN_COLOR=pR61509V->Data.BColor;
			R61509V_WriteData(LCD_PEN_COLOR);
			temp=temp<<1;
		}
    //=======================δ��8λ�Ĳ��䶨��
    if((12==font))
    {
      temp=Buffer[i+1];		 					
      for(j=0;j<4;j++)
      {
        if((temp&0x80)==0X80)
        {
          LCD_PEN_COLOR=color;
        }
        else
          LCD_PEN_COLOR=pR61509V->Data.BColor;
        R61509V_WriteData(LCD_PEN_COLOR);
        temp=temp<<1;
      }
      i++;
    }			
	}
	R61509VSet(CS);	//LCD_CS_HIGH;
}

//#endif//R61509V_61509_EN
/************************************** The End Of FILE **************************************/


