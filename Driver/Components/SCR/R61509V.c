/**************************************************************************************************
* Һ��������IC
* �ļ�<$(filename)>
* ģ������ :	���塢���ܡ�˵��
* ��ʷ�޸ļ�¼
*     <��Ҫ�޸���>  <ʱ��>   <�汾 >   <˵��>
*     xlyan        $(Date)   1.0.0    �����ļ�
**************************************************************************************************/
#include "R61509V.h"


LCDDef	*pR61509V	=	NULL;		//�ڲ�����ʹ�ã�����ɾ��

/*******************************************************************************
* ������			:	function
* ��������		:	��������˵�� 
* ����			: void
* ����ֵ			: void
*******************************************************************************/
void R61509V_Initialize(LCDDef *pInfo)
{
	pR61509V		=	pInfo;		//ָ��ָ��
	
	
	pR61509V->Data.MaxH	=	R61509V_H;					//���ˮƽ���
	pR61509V->Data.MaxV	=	R61509V_V;					//���ֱ�߶�	
//	pR61509V->Data.BColor	=	LCD565_GBLUE;			//����ɫ
//	pR61509V->Data.PColor	=	LCD565_RED;				//����ɫ
	
	
	pR61509V->Display.WriteAddress		=	R61509V_SetWindowAddress;
	pR61509V->Display.PowerOn					=	R61509V_PowerOn;
	pR61509V->Display.DispOff					=	R61509V_PowerOff;
	
	LCD_Initialize(pR61509V);
//	pR61509V	=	NULL;	
}
/*******************************************************************************
*������			:	R61509V_SetWindowAddress
*��������		:	���ô��ڵ�ַ
*����				: 
*����ֵ			:	��
*******************************************************************************/
static void R61509V_SetWindowAddress(			//���ô��ڵ�ַ
															unsigned short x1,		//ˮƽ��ʼ��
															unsigned short y1,		//ˮƽ��ֹ��
															unsigned short x2,		//��ֱ��ʼ��
															unsigned short y2			//��ֱ��ֹ��
															)
{	
	unsigned short MaxH,MaxV;
	unsigned short Model	=	0x5030;

	eRotate	Rotate	=	pR61509V->Flag.Rotate;
	
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
	LCD_WriteCommand(R61509V_R210_HSA,pR61509V->Data.HSX);		//Window Horizontal RAM Address Start(R210h)		//ˮƽ
	LCD_WriteCommand(R61509V_R211_HEA,pR61509V->Data.HEX);		//Window Horizontal RAM Address End(R211h)			//ˮƽ
	LCD_WriteCommand(R61509V_R212_VSA,pR61509V->Data.VSY);		//Window Vertical RAM Address Start (R212h)			//��ֱ
	LCD_WriteCommand(R61509V_R213_VEA,pR61509V->Data.VEY);		//Window Vertical RAM Address End (R213h)				//��ֱ
	
	LCD_WriteCommand(R61509V_R200_HA,pR61509V->Data.HXA);			//RAM Address Set (Horizontal Address) (R200h)
	LCD_WriteCommand(R61509V_R201_VA,pR61509V->Data.VYA);			//RAM Address Set (Vertical Address) (R201h)

	LCD_WriteCommand(R61509V_R003_EM,Model);						//RAM Address Set (Vertical Address) (R201h)
//	R61509V_WriteIndex16(R61509V_R202_GDRW);								//GRAM(Graphics RAM--ͼ���ڴ�) Data Write (R202h)׼��д��
	LCD_WriteIndexStart();	
	LCD_WriteData(R61509V_R202_GDRW);
	LCD_WriteIndexEnd();
}


/*******************************************************************************
*������			:	R61509V_Initialize
*��������		:	IC��ʼ������������оƬR61509V��power supply on sequence ��������
*����				: 
*����ֵ			:	��
*******************************************************************************/
static void R61509V_PowerOn(void)			//��������оƬR61509V��power supply on sequence ��������
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
	LCD_Delay(dtime);		//��λ��1ms�ڲ���������
	LCD_Delay(dtime);		//��λ��1ms�ڲ���������
	LCD_Delay(dtime);		//��λ��1ms�ڲ���������
	dtime=500;
	
	Command(R61509V_R000_IR		,	0x0000);		LCD_Delay(dtime); //�Ĵ�д0x00
	Command(R61509V_R000_IR		,	0x0000);		LCD_Delay(dtime); //�Ĵ�д0x00
	Command(R61509V_R000_IR		,	0x0000);		LCD_Delay(dtime); //�Ĵ�д0x00
	Command(R61509V_R000_IR		,	0x0000);		LCD_Delay(dtime); //�Ĵ�д0x00
	
	Command(R61509V_R001_DOC	,	0x0300);		LCD_Delay(dtime); //--------��ʾ�������When SS = ��1�� and BGR = ��1��, RGB dots are assigned one to one from S720 to S1.
	Command(R61509V_R002_DWC	,	0x0100);		LCD_Delay(dtime); //--------	
	Command(R61509V_R003_EM		,	0X5030);		LCD_Delay(dtime); //--------RGB��Ϊ5-6-5ģʽ------------0X5030
	Command(R61509V_R007_DC1	,	0x0100);		LCD_Delay(dtime); //--------������ʾ����base image�Ĺ��뿪
	Command(R61509V_R008_DC2	,	0X0808);		LCD_Delay(dtime); //--------
	Command(R61509V_R009_DC3	,	0x0001);		LCD_Delay(dtime); //--------	
	
	Command(R61509V_R00B_ECC		,	0x0001);		LCD_Delay(dtime); //--------
	Command(R61509V_R00C_EDIC1	,	0x0000);		LCD_Delay(dtime); //--------
	Command(R61509V_R00F_EDIC2	,	0x0000);		LCD_Delay(dtime); //--------
	
	Command(R61509V_R010_PIC1	,	0x0019);		LCD_Delay(dtime); //--------���Ƶ��--0x19
	Command(R61509V_R011_PIC2	,	0x0101);		LCD_Delay(dtime); //--------		Panel Interface Control 2 (R011h)
	Command(R61509V_R012_PIC3	,	0x0000);		LCD_Delay(dtime); //--------
	Command(R61509V_R013_PIC4	,	0x0001);		LCD_Delay(dtime); //--------
	Command(R61509V_R014_PIC5	,	0x0055);		LCD_Delay(dtime); //--------
	Command(R61509V_R020_PIC6	,	0x0010);		LCD_Delay(dtime); //--------
	Command(R61509V_R021_PIC7	,	0x0101);		LCD_Delay(dtime); //--------
	Command(R61509V_R022_PIC8	,	0x0000);		LCD_Delay(dtime); //--------
	Command(R61509V_R023_PIC9	,	0x0001);		LCD_Delay(dtime); //--------	
	
	Command(R61509V_R090_FMC		,	0x8000);		LCD_Delay(dtime); //--------���������ƣ�FMARK interface
	
	Command(R61509V_R100_PC1		,	0x0330);		LCD_Delay(dtime); //--------���õ�Դ���ƣ�ƽ����ʾ�������
	Command(R61509V_R101_PC2		,	0x0227);		LCD_Delay(dtime); //--------Power Control 2
	Command(R61509V_R102_PC3		,	0xC1B0);		LCD_Delay(dtime); //--------PSON,PON ����Ϊ1����Դ��Ӧ��
	Command(R61509V_R103_PC4		,	0x0D00);		LCD_Delay(dtime); //--------	
	
	Command(R61509V_R200_HA			,	0x0000);		LCD_Delay(dtime);	//--------RAM address ����
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
	
	Command(R61509V_R400_BINL		,	0X6400);		LCD_Delay(dtime); //base image ���� 400��
	Command(R61509V_R401_BIDC		,	0x0004);		LCD_Delay(dtime); //--------����base image ����ģʽ����������(��ɫ�������ã�
	Command(R61509V_R404_BIVSC	,	0x0000);		LCD_Delay(dtime);	//--------��0�߿�ʼ����
	
	Command(R61509V_R502_PTEA		,	0x005f);		LCD_Delay(dtime);
	LCD_BL_ON;		//������
}

/**************************************************************************************************
* [Function] R61509V_PowerOff:  �ر�R61509V ��Դ
* [No param]
**************************************************************************************************/
static void R61509V_PowerOff( void )
{
	LCD_WriteCommand( R61509V_R009_DC3, 0 );
	LCD_BL_OFF;
}
/**************************************************************************************************
* [Function] R61509V_DispOff:  �ر�R61509V��ʾ( ����?)
* [No param]
**************************************************************************************************/
static void R61509V_DispOff( void )
{
	LCD_WriteCommand( R61509V_R007_DC1, 0x0000 );
}





//#endif//R61509V_61509_EN
/************************************** The End Of FILE **************************************/


