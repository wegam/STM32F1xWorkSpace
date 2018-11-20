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

static LCDDef	*pR61509V	=	NULL;		//�ڲ�����ʹ�ã�����ɾ��

#define	R61509V_CS_HIGH		(pR61509V->Port.sCS_PORT->BSRR	= pR61509V->Port.sCS_Pin)
#define	R61509V_CS_LOW		(pR61509V->Port.sCS_PORT->BRR	=	pR61509V->Port.sCS_Pin)

#define	R61509V_DC_HIGH		(pR61509V->Port.sDC_PORT->BSRR	= pR61509V->Port.sDC_Pin)
#define	R61509V_DC_LOW		(pR61509V->Port.sDC_PORT->BRR	= pR61509V->Port.sDC_Pin)

#define	R61509V_WR_HIGH		(pR61509V->Port.sWR_PORT->BSRR	= pR61509V->Port.sWR_Pin)
#define	R61509V_WR_LOW		(pR61509V->Port.sWR_PORT->BRR	= pR61509V->Port.sWR_Pin)

#define	R61509V_RD_HIGH		(pR61509V->Port.sRD_PORT->BSRR	= pR61509V->Port.sRD_Pin)
#define	R61509V_RD_LOW		(pR61509V->Port.sRD_PORT->BRR	= pR61509V->Port.sRD_Pin)

#define	R61509V_RST_HIGH	(pR61509V->Port.sRST_PORT->BSRR	= pR61509V->Port.sRST_Pin)
#define	R61509V_RST_LOW		(pR61509V->Port.sRST_PORT->BRR	= pR61509V->Port.sRST_Pin)

#define	R61509V_TE_HIGH		(pR61509V->Port.sTE_PORT->BSRR	= pR61509V->Port.sTE_Pin)
#define	R61509V_TE_LOW		(pR61509V->Port.sTE_PORT->BRR	= pR61509V->Port.sTE_Pin)

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
void R61509V_Initialize(void*	pInfo)
{
	static unsigned short	DeviceCode	=	0;
	LCDPortDef*	Port	=	NULL;
	if(NULL==	pInfo)
		return;
	
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
		return;
	}
	pR61509V->Data.MaxH	=	R61509V_H;					//���ˮƽ���
	pR61509V->Data.MaxV	=	R61509V_V;					//���ֱ�߶�	
	
	pR61509V->Display.WriteAddress		=	R61509V_SetWindowAddress;
	pR61509V->Display.PowerOn					=	R61509V_PowerOn;
	pR61509V->Display.DispOff					=	R61509V_PowerOff;
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
	R61509VCrl(DC);	//LCD_DC_LOW;		//RS
	R61509V_WriteData(Index);
	R61509VSet(DC);	//LCD_DC_HIGH;	//RS
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
void R61509V_WriteCommand(unsigned	short	Index,unsigned short Cmd)
{
	//---------------------Write Index
	R61509V_WriteIndex(Index);
	//---------------------Write Data
	R61509V_WriteData(Cmd);
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
void R61509V_WriteRegister(unsigned	short	Index,unsigned short Data)
{
	R61509VCrl(CS);	//LCD_CS_LOW;	
	//---------------------Write Index
	R61509V_WriteIndex(Index);
	//---------------------Write Data
	R61509V_WriteData(Data);	
	R61509VSet(CS);	//LCD_CS_HIGH;	
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
unsigned short R61509V_ReadRegister(unsigned	short	Index)
{
	unsigned short Data	=	0;
	R61509VCrl(CS);	//LCD_CS_LOW;
	//---------------------Write Index
	R61509V_WriteIndex(Index);
	//---------------------Read Data
	GPIO_Configuration_IPU	(R61509V_DATABUS_PORT,R61509V_DATABUS_Pin);			//��GPIO��Ӧ�ܽ�����Ϊ��������ģʽ----V20170605
	Data	=	R61509V_ReadData();
	R61509VSet(CS);	//LCD_CS_HIGH;
	GPIO_Configuration_OPP50	(R61509V_DATABUS_PORT,R61509V_DATABUS_Pin);		//��GPIO��Ӧ�ܽ�����ΪPP(����)���ģʽ������ٶ�2MHz----V20170605	
	return Data;
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
	R61509V_WriteIndex(R61509V_R202_GDRW);
	for(i=0;i<length;i++)
	{
		R61509V_WriteData(RAM[i]);
	}
	R61509VSet(CS);	//LCD_CS_HIGH;
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
//	R61509V_WriteIndex(R61509V_R202_GDRW);		//GRAM(Graphics RAM--ͼ���ڴ�) Data Write (R202h)׼��д��
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
	Command	=	R61509V_WriteCommand;
	R61509VCrl(CS);	//LCD_CS_LOW;
	
	LCD_Reset();
	dtime=10;
	
	Command(R61509V_R000_IR		,	0x0000);	//�Ĵ�д0x00
	Command(R61509V_R000_IR		,	0x0000);	//�Ĵ�д0x00
	Command(R61509V_R000_IR		,	0x0000);	//�Ĵ�д0x00
	Command(R61509V_R000_IR		,	0x0000);	//�Ĵ�д0x00
	
	Command(R61509V_R001_DOC	,	0x0300);	//--------��ʾ�������When SS = ��1�� and BGR = ��1��, RGB dots are assigned one to one from S720 to S1.
	Command(R61509V_R002_DWC	,	0x0100);	//--------	
	Command(R61509V_R003_EM		,	0X5030);	//--------RGB��Ϊ5-6-5ģʽ------------0X5030
	Command(R61509V_R007_DC1	,	0x0100);	//--------������ʾ����base image�Ĺ��뿪
	Command(R61509V_R008_DC2	,	0X0808);	//--------
	Command(R61509V_R009_DC3	,	0x0001);	//--------	
	
	Command(R61509V_R00B_ECC		,	0x0001);	//--------
	Command(R61509V_R00C_EDIC1	,	0x0000);	//--------
	Command(R61509V_R00F_EDIC2	,	0x0000);	//--------
	
	Command(R61509V_R010_PIC1	,	0x0019);	//--------���Ƶ��--0x19
	Command(R61509V_R011_PIC2	,	0x0101);	//--------		Panel Interface Control 2 (R011h)
	Command(R61509V_R012_PIC3	,	0x0000);	//--------
	Command(R61509V_R013_PIC4	,	0x0001);	//--------
	Command(R61509V_R014_PIC5	,	0x0055);	//--------
	Command(R61509V_R020_PIC6	,	0x0010);	//--------
	Command(R61509V_R021_PIC7	,	0x0101);	//--------
	Command(R61509V_R022_PIC8	,	0x0000);	//--------
	Command(R61509V_R023_PIC9	,	0x0001);	//--------	
	
	Command(R61509V_R090_FMC		,	0x8000);	//--------���������ƣ�FMARK interface
	
	Command(R61509V_R100_PC1		,	0x0330);	//--------���õ�Դ���ƣ�ƽ����ʾ�������
	Command(R61509V_R101_PC2		,	0x0227);	//--------Power Control 2
	Command(R61509V_R102_PC3		,	0xC1B0);	//--------PSON,PON ����Ϊ1����Դ��Ӧ��
	Command(R61509V_R103_PC4		,	0x0D00);	//--------	
	
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
	
	Command(R61509V_R400_BINL		,	0X6400);	//base image ���� 400��
	Command(R61509V_R401_BIDC		,	0x0004);	//--------����base image ����ģʽ����������(��ɫ�������ã�
	Command(R61509V_R404_BIVSC	,	0x0000);	//--------��0�߿�ʼ����
	
	Command(R61509V_R502_PTEA		,	0x005f);
	LCD_BL_ON;		//������
	R61509VSet(CS);	//LCD_CS_HIGH;
}

/**************************************************************************************************
* [Function] R61509V_PowerOff:  �ر�R61509V ��Դ
* [No param]
**************************************************************************************************/
void R61509V_PowerOff( void )
{
	LCD_WriteCommand( R61509V_R009_DC3, 0 );
	LCD_BL_OFF;
}
/**************************************************************************************************
* [Function] R61509V_DispOff:  �ر�R61509V��ʾ( ����?)
* [No param]
**************************************************************************************************/
void R61509V_DispOff( void )
{
	LCD_WriteCommand( R61509V_R007_DC1, 0x0000 );
}





//#endif//R61509V_61509_EN
/************************************** The End Of FILE **************************************/


