/**************************************************************************************************
* Һ��������IC
* �ļ�<$(filename)>
* ģ������ :	���塢���ܡ�˵��
* ��ʷ�޸ļ�¼
*     <��Ҫ�޸���>  <ʱ��>   <�汾 >   <˵��>
*     xlyan        $(Date)   1.0.0    �����ļ�
**************************************************************************************************/
#include "LCD.H"


#include "STM32_GPIO.H"
#include "STM32_PWM.H"
#include "STM32_SYSTICK.H"
#include "font.h"
#include "string.h"				//�����ڴ��������ͷ�ļ�
#include "stdlib.h"				//�����ڴ��������ͷ�ļ�
#include "stdarg.h"				//�����ڴ��������ͷ�ļ�
#include "stdio.h"				//�����ڴ��������ͷ�ļ�

LCDDef 			*LCDSYS	=	NULL;	//�ڲ�����ʹ�ã�����ɾ��
unsigned short PenColor		=	0;		//������ɫ
unsigned short BackColor	=	0;		//������ɫ
unsigned short VAsize	=	0;		//�����С
/*******************************************************************************
*������			:	LCD_Initialize
*��������		:	LCD��ʼ����
*����				: 
*����ֵ			:	��
*******************************************************************************/
void LCD_Initialize(LCDDef *pInfo)
{
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
  //==========================��鱳��ɫ�뻭��ɫ�Ƿ���ͬ
	if(pInfo->Data.PColor	==	pInfo->Data.BColor)
	{
		pInfo->Data.PColor	=	pInfo->Data.BColor^0xFF;
	}
	//==========================LCD��ʼ�����ϵ�����
	LCDSYS->Display.PowerOn();						//LCD�ϵ�/��ʼ������
	//==========================�Ա���ɫ�����Ļ
	LCD_Clean(pInfo->Data.BColor);				//������ɫ�����Ļ����
	//==========================�ֿ�����
	GT32L32_Initialize(&pInfo->GT32L32.SPI);				//��ͨSPIͨѶ��ʽ����	
}

/**************************************************************************************************
* [Function] R61509V_DispOff:  �ر�R61509V��ʾ( ����?)
* [No param]
**************************************************************************************************/
void LCD_WriteIndexStart( void )
{
	LCD_CS_LOW; 	//Ƭѡ�ź� 0:Ƭѡ;1:ʧ��;
	LCD_DC_LOW; 	//����/���ݣ�0������;1-����
	LCD_RD_HIGH;	//���ź�;0:������
}
/**************************************************************************************************
* [Function] R61509V_DispOff:  �ر�R61509V��ʾ( ����?)
* [No param]
**************************************************************************************************/
void LCD_WriteIndexEnd( void )
{
	LCD_CS_HIGH;	//Ƭѡ�ź� 0:Ƭѡ;1:ʧ��;
}
/**************************************************************************************************
* [Function] R61509V_DispOff:  �ر�R61509V��ʾ( ����?)
* [No param]
**************************************************************************************************/
void LCD_WriteIndex( unsigned short Index )
{
	LCD_CS_LOW; 	//Ƭѡ�ź� 0:Ƭѡ;1:ʧ��;
	LCD_DC_LOW; 	//����/���ݣ�0������;1-����
	LCD_WriteData(Index);
	LCD_DC_HIGH; 	//����/���ݣ�0������;1-����
}
/**************************************************************************************************
* [Function] R61509V_DispOff:  �ر�R61509V��ʾ( ����?)
* [No param]
**************************************************************************************************/
void LCD_WriteDataStart( void )
{
	LCD_CS_LOW; 	//Ƭѡ�ź� 0:Ƭѡ;1:ʧ��;
	LCD_DC_HIGH; 	//����/���ݣ�0������;1-����
	LCD_RD_HIGH;	//���ź�;0:������
}
/**************************************************************************************************
* [Function] R61509V_DispOff:  �ر�R61509V��ʾ( ����?)
* [No param]
**************************************************************************************************/
void LCD_WriteDataEnd( void )
{
	LCD_DC_LOW; 	//����
	LCD_CS_HIGH;
}
#if 1
/*******************************************************************************
* ������			:	R61509V_WriteData
* ��������		:	д16λ����
* ����			: void
* ����ֵ			: void
* �޸�ʱ��		: ��
* �޸�����		: ��
* ����			: wegam@sina.com
*******************************************************************************/
void LCD_WriteData(u16 Data)
{
	LCD_WR_LOW;
	LCD_DATABUS_PORT->ODR = Data;		
	LCD_WR_HIGH;
}
/**************************************************************************************************
* [Function] R61509V_ReadData:  ��R61509V��ȡ����
* [No param][return]u16: ��������
**************************************************************************************************/
u16 LCD_ReadData( void )
{
	u16 Dat;

	LCD_CS_LOW;
	LCD_WR_HIGH;
	LCD_DC_HIGH;
	Dat = LCD_DATABUS_PORT->IDR;
	LCD_RD_LOW;
	LCD_RD_HIGH;
	LCD_CS_HIGH;

	return(Dat);
}
#else
/*******************************************************************************
* ������			:	R61509V_WriteData
* ��������		:	д8λ����
* ����			: void
* ����ֵ			: void
* �޸�ʱ��		: ��
* �޸�����		: ��
* ����			: wegam@sina.com
*******************************************************************************/
void LCD_WriteData(u16 Data)
{
	LCD_WR_LOW;
	LCD_DATABUS_PORT->ODR = Data>>8;		
	LCD_WR_HIGH;
	
	LCD_WR_LOW;
	LCD_DATABUS_PORT->ODR = Data;		
	LCD_WR_HIGH;
}
#endif
/*******************************************************************************
*������			:	R61509V_WriteCommand
*��������		:	д������������
*����				: 
*����ֵ			:	��
*******************************************************************************/
void LCD_WriteCommand(												//д������������
											unsigned short Index,			//�Ĵ�������
											unsigned short Command		//����
											)	//д������������
{
	//==================д��ַ
	LCD_WriteIndexStart();		
	LCD_WriteData(Index);
	LCD_WriteIndexEnd();
	
	//==================д����
	LCD_WriteDataStart();
	LCD_WriteData(Command);
	LCD_WriteDataEnd();
}

/*******************************************************************************
*������			:	R61509V_SetWindowAddress
*��������		:	���ô��ڵ�ַ
*����				: 
*����ֵ			:	��
*******************************************************************************/
void LCD_SetWindowAddress(			//���ô��ڵ�ַ
															unsigned short x1,		//ˮƽ��ʼ��
															unsigned short y1,		//ˮƽ��ֹ��
															unsigned short x2,		//��ֱ��ʼ��
															unsigned short y2			//��ֱ��ֹ��
															)
{	
	unsigned short MaxH,MaxV;
	unsigned short Model	=	0x5030;

	eRotate	Rotate	=	LCDSYS->Flag.Rotate;	
	MaxH	=	LCDSYS->Data.MaxH;
	MaxV	=	LCDSYS->Data.MaxV;

	switch(Rotate)
	{
		case 	Draw_Rotate_0D:
					LCDSYS->Data.HSX	=	x1;
					LCDSYS->Data.HEX	=	x2;
					LCDSYS->Data.VSY	=	y1;
					LCDSYS->Data.VEY	=	y2;
					LCDSYS->Data.HXA	=	LCDSYS->Data.HSX;
					LCDSYS->Data.VYA	=	LCDSYS->Data.VSY;
					Model	=	0x5030;
				break;
		case 	Draw_Rotate_90D:
					LCDSYS->Data.HSX	=	y1;
					LCDSYS->Data.HEX	=	y2;	
					LCDSYS->Data.VSY	=	MaxV	-	x2	-	1;
					LCDSYS->Data.VEY	=	MaxV	-	x1	-	1;	
					LCDSYS->Data.HXA	=	LCDSYS->Data.HSX;
					LCDSYS->Data.VYA	=	LCDSYS->Data.VEY;
					Model	=	0X5018;								//GRAM(Graphics RAM--ͼ���ڴ�) Data Write (R202h)׼��д��
				break;
		case 	Draw_Rotate_180D:
					LCDSYS->Data.HSX	=	MaxH	-	x2	-	1;
					LCDSYS->Data.HEX	=	MaxH	-	x1	-	1;
					LCDSYS->Data.VSY	=	MaxV	-	y2	-	1;
					LCDSYS->Data.VEY	=	MaxV	-	y1	-	1;	
					LCDSYS->Data.HXA	=	LCDSYS->Data.HEX;
					LCDSYS->Data.VYA	=	LCDSYS->Data.VEY;	
					Model	=	0X5000;
				break;
		default:
					LCDSYS->Data.HSX	=	MaxH	-	y2	-	1;
					LCDSYS->Data.HEX	=	MaxH	-	y1	-	1;
					LCDSYS->Data.VSY	=	x1;
					LCDSYS->Data.VEY	=	x2;	
					LCDSYS->Data.HXA	=	LCDSYS->Data.HEX;
					LCDSYS->Data.VYA	=	LCDSYS->Data.VSY;
					Model	=	0X5028;
				break;
	}
	LCD_WriteCommand(LCD_R210_HSA,LCDSYS->Data.HSX);		//Window Horizontal RAM Address Start(R210h)		//ˮƽ
	LCD_WriteCommand(LCD_R211_HEA,LCDSYS->Data.HEX);		//Window Horizontal RAM Address End(R211h)			//ˮƽ
	LCD_WriteCommand(LCD_R212_VSA,LCDSYS->Data.VSY);		//Window Vertical RAM Address Start (R212h)			//��ֱ
	LCD_WriteCommand(LCD_R213_VEA,LCDSYS->Data.VEY);		//Window Vertical RAM Address End (R213h)				//��ֱ	
	LCD_WriteCommand(LCD_R200_HA,LCDSYS->Data.HXA);			//RAM Address Set (Horizontal Address) (R200h)
	LCD_WriteCommand(LCD_R201_VA,LCDSYS->Data.VYA);			//RAM Address Set (Vertical Address) (R201h)
	LCD_WriteCommand(LCD_R003_EM,Model);						//RAM Address Set (Vertical Address) (R201h)
	//R61509V_WriteIndex16(R61509V_R202_GDRW);								//GRAM(Graphics RAM--ͼ���ڴ�) Data Write (R202h)׼��д��
	LCD_WriteIndexStart();		
	LCD_WriteData(LCD_R202_GDRW);
	LCD_WriteIndexEnd();
}
/*******************************************************************************
*������			:	LCD_Clean
*��������		:	�������������Ļ����---�ñ���ɫ�����Ļ
*����				: 
*����ֵ			:	��
*******************************************************************************/
void LCD_Clean(u16 Color)	//�����Ļ����
{
	unsigned short x,y;
	unsigned short HSX,HEX,HSY,HEY,MaxH,MaxV;
	eRotate	Rotate	=	LCDSYS->Flag.Rotate;
	
	MaxH	=	LCDSYS->Data.MaxH;
	MaxV	=	LCDSYS->Data.MaxV;
	
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
	LCDSYS->Display.WriteAddress(HSX,HSY,HEX,HEY);		//д���ַ����
	LCD_WriteDataStart();									//д����ʹ��
	for(x=0;x<MaxH;x++)
	{
		for(y=0;y<MaxV;y++)
		{
			LCD_WriteData(Color);							//д����
		}
	}	
	LCD_WriteDataEnd();										//д�������
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
	LCDSYS->Display.WriteAddress(HSX,HSY,HSX,HSY);	//���ù��λ�� 
	LCD_WriteDataStart();
	LCD_WriteData(Color); 	//�ʻ���ɫ
	LCD_WriteDataEnd();
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
		LCD_DrawDot(uRow,uCol,Color);			//���� 
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
void LCD_DrawCircle(
												u16 x,u16 y,		//Բ������ԭ��
												u16 r,					//�뾶
												u8 Filled,			//�Ƿ����
												u16 color				//��ɫ
												)
{
	int a,b;
	int di;
	
//	void ( *DSPDrawDot )(unsigned short HSX,unsigned short HSY,unsigned short Color);
//	void ( *DSPDrawLine )( unsigned short HSX,unsigned short HSY,unsigned short HEX,unsigned short HEY,unsigned short Color);
//	DSPDrawDot	=	LcdDisplay.DSPDrawDot;
//	DSPDrawLine	=	LcdDisplay.DSPDrawLine;
	
	a=0;b=r;	  
	di=3-(r<<1);             //�ж��¸���λ�õı�־
	while(a<=b)
	{
		if(Filled)	//���ͻ���
		{
			LCD_DrawLine(x,y,x-b,y-a,color);             //3           
			LCD_DrawLine(x,y,x+b,y-a,color);             //0           
			LCD_DrawLine(x,y,x-a,y+b,color);             //1       
			LCD_DrawLine(x,y,x-b,y-a,color);             //7           
			LCD_DrawLine(x,y,x-a,y-b,color);             //2             
			LCD_DrawLine(x,y,x+b,y+a,color);             //4               
			LCD_DrawLine(x,y,x+a,y-b,color);             //5
			LCD_DrawLine(x,y,x+a,y+b,color);             //6 
			LCD_DrawLine(x,y,x-b,y+a,color);             
			a++;
			//ʹ��Bresenham�㷨��Բ     
			if(di<0)
				di +=4*a+6;	  
			else
			{
				di+=10+4*(a-b);   
				b--;
			}
			LCD_DrawLine(x,y,x+a,y+b,color);				//AB �������껭һ��ֱ��
		}
		else
		{
			LCD_DrawDot(x-b,y-a,color);             //3           
			LCD_DrawDot(x+b,y-a,color);             //0           
			LCD_DrawDot(x-a,y+b,color);             //1       
			LCD_DrawDot(x-b,y-a,color);             //7           
			LCD_DrawDot(x-a,y-b,color);             //2             
			LCD_DrawDot(x+b,y+a,color);             //4               
			LCD_DrawDot(x+a,y-b,color);             //5
			LCD_DrawDot(x+a,y+b,color);             //6 
			LCD_DrawDot(x-b,y+a,color);             
			a++;
			//ʹ��Bresenham�㷨��Բ     
			if(di<0)
				di +=4*a+6;	  
			else
			{
				di+=10+4*(a-b);   
				b--;
			}
				LCD_DrawDot(x+a,y+b,color);
		}
	}
}
/**************************************************************************************************
* [Function] LCD_DrawRectangle:  ��һ�¾��ο�
* [param01]t_Point top_p: ��������ֵ
* [param02]t_Point botton_p : �ذ�����ֵ
**************************************************************************************************/
void LCD_DrawRectangle(u16 x1,u16 y1,u16 x2,u16 y2,u16 color)
{
	LCD_DrawLine( x1, y1,	x1,	y2, color );
	LCD_DrawLine( x1, y1,	x2,	y1, color );
	LCD_DrawLine( x2, y1,	x2,	y2, color );
	LCD_DrawLine( x1, y2,	x2,	y2, color );
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
							u16 color
)
{          
	unsigned int i;
	unsigned int j;	
	unsigned short HSX,HEX,HSY,HEY,MaxH,MaxV;
	eRotate	Rotate	=	LCDSYS->Flag.Rotate;
	
	MaxH	=	LCDSYS->Data.MaxH;
	MaxV	=	LCDSYS->Data.MaxV;
	
	switch(Rotate)
	{
		case 	Draw_Rotate_0D:
					HSX	=	0;
					HEX	=	MaxH-1;
					HSY	=	0;
					HEY	=	MaxV-1;
			break;
		case	Draw_Rotate_90D:
					HSX	=	x1;
					HEX	=	x2;
					HSY	=	y1;
					HEY	=	y2;
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

	LCDSYS->Display.WriteAddress(HSX,HSY,HEX,HEY);
	LCD_WriteDataStart();
	for(i=0;i<=HEX-HSX;i++)
	{
		for(j=0;j<=HEY-HSY;j++)
		{
			LCD_WriteData(color);
		}
	}
	LCD_WriteDataEnd();	
}
/**************************************************************************************************
* [Function] R61509V_Setbackground:  ���ñ�����ɫ
* [param01]u16 BackColor: ������ɫֵ
**************************************************************************************************/
void LCD_SetBackground(  u16 BackColor )
{
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
										...)
{	
  unsigned char GetBufferLength	=	0;
  unsigned char CodeBuffer[32]={0};
	unsigned short InputDataSize=	0;		//����ɱ������С
//	unsigned short PenColor		=	0;		//������ɫ
//	unsigned short BackColor	=	0;		//������ɫ
//	VAsize=strlen((const char*)Num);		//��ȡ���ݿ��	
	//================va_list  ����һ��ָ����������ٵ�ǰ������ָ��
//	va_list args;
//	//================va_start ��ʼ�����ָ���λ�ã��ʼָ���һ�������Ľ�β��λ��
//	VAsize=strlen((const char*)Num);		//��ȡ���ݿ��
//	va_start(args, Num);
//	//================va_arg ���ƶ�ָ�룬ָ��һ���²�����λ�ã������ص�ǰֵ
//	PenColor 	= va_arg(args,unsigned short);	//������ɫ
//	BackColor = va_arg(args,unsigned short);	//������ɫ
//	va_end(args);
  if(Num>4)
  {
    Num=4;
  }
  GetBufferLength = GT32L32_GetAntennaCode(Num,CodeBuffer);
	LCD_ShowChar(x,y,12,GetBufferLength,CodeBuffer,PenColor);
	LCD_ShowChar(x,y,12,GetBufferLength,CodeBuffer,BackColor);
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
										u16 color)
{
  unsigned char GetBufferLength	=	0;
  unsigned char CodeBuffer[32]={0};
  if(Num>3)
  {
    Num=3;
  }
  GetBufferLength = GT32L32_GetBatteryCode(Num,CodeBuffer);
	LCD_ShowChar(x,y,12,GetBufferLength,CodeBuffer,color);
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
										u8 num,			//num			:�ֽ���
										u8 *Buffer,	//Buffer	:��ʾ�����ݻ���
										u16 color
)		//��ͨ�ֿ���Գ���
{
	u8 temp;
	u8 i=0,j=0;
	unsigned short x1=0,x2=0,y1=0,y2=0;
	u16 colortemp=LCDSYS->Data.PColor;
//	CoordinateTransform(&x1,&y1,&x2,&y2);
	x1	=	x;
	y1	=	y;
	
	if(font==12)
	{
		if(x>LCDSYS->Data.MaxV-12||y>LCDSYS->Data.MaxH-12)
			return;
		
		x2	=	x+12-1;
		y2	=	y+12-1;
	}
	if(font==16)
	{
		if(x>LCDSYS->Data.MaxV-16||y>LCDSYS->Data.MaxH-16)
			return;
			x2	=	x+8-1;
			y2	=	y+16-1;
	}
	if(font==24)
	{
		if(x>LCDSYS->Data.MaxV-24||y>LCDSYS->Data.MaxH-24)
			return;
			x2	=	x+12-1;
			y2	=	y+24-1;
	}
	else if(font==32)
	{
		if(x>LCDSYS->Data.MaxV-32||y>LCDSYS->Data.MaxH-32)
			return;
			x2	=	x+16-1;
			y2	=	y+32-1;
	}
	else
	{
//		return ;
	}
	LCDSYS->Display.WriteAddress(x1,y1,x2,y2);//������ʾ����
	i=0;
	for(i=0;i<num;i++)
	{ 
		u16 LCD_PEN_COLOR	=	LCDSYS->Data.PColor;   	//����ɫ	
		temp=Buffer[i];		 					//����1608����--��ά������ʽ--�ֿ�ʹ��ʱȡ��
		for(j=0;j<8;j++)
		{
			if((temp&0x80)==0X80)
			{
				LCD_PEN_COLOR=LCDSYS->Data.PColor;
			}
			else
				LCD_PEN_COLOR=LCDSYS->Data.BColor;
			LCD_WriteDataStart();
			LCD_WriteData(LCD_PEN_COLOR);
			LCD_WriteDataEnd();
			temp=temp<<1;
		}
    //=======================δ��8λ�Ĳ��䶨��
    if(24==font)
    {
      temp=Buffer[i+1];		 					
      for(j=0;j<4;j++)
      {
        if((temp&0x80)==0X80)
        {
          LCD_PEN_COLOR=LCDSYS->Data.PColor;
        }
        else
          LCD_PEN_COLOR=LCDSYS->Data.BColor;
        LCD_WriteDataStart();
        LCD_WriteData(LCD_PEN_COLOR);
        LCD_WriteDataEnd();
        temp=temp<<1;
      }
      i++;
    }
    else if(12==font)
    {
      temp=Buffer[i+1];		 					
      for(j=0;j<4;j++)
      {
        if((temp&0x80)==0X80)
        {
          LCD_PEN_COLOR=LCDSYS->Data.PColor;
        }
        else
          LCD_PEN_COLOR=LCDSYS->Data.BColor;
        LCD_WriteDataStart();
        LCD_WriteData(LCD_PEN_COLOR);
        LCD_WriteDataEnd();
        temp=temp<<1;
      }
      i++;
    }
		LCDSYS->Data.PColor=colortemp;	
	}	
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
										u8 num,			//num			:�ֽ���
										u8 *Buffer,	//Buffer	:��ʾ�����ݻ���
										u16 color
)		//��ͨ�ֿ���Գ���
{
	u8 temp;
	u8 i=0,j=0;
	unsigned short x1=0,x2=0,y1=0,y2=0;
	u16 colortemp=LCDSYS->Data.PColor;
	x1	=	x;
	y1	=	y;
	
	if(font==12)
	{
		if(x>LCDSYS->Data.MaxV-12||y>LCDSYS->Data.MaxH-12)
			return;
		
		x2	=	x+12-1;
		y2	=	y+12-1;
	}
	if(font==16)
	{
		if(x>LCDSYS->Data.MaxV-16||y>LCDSYS->Data.MaxH-16)
			return;
			x2	=	x+16-1;
			y2	=	y+16-1;

	}
	if(font==24)
	{
		if(x>LCDSYS->Data.MaxV-24||y>LCDSYS->Data.MaxH-24)
			return;

			x2	=	x+24-1;
			y2	=	y+24-1;
	}
	else if(font==32)
	{
		if(x>LCDSYS->Data.MaxV-32||y>LCDSYS->Data.MaxH-32)
			return;
			x2	=	x+32-1;
			y2	=	y+32-1;
	}
	else
	{
//		return ;
	}
	LCDSYS->Display.WriteAddress(x1,y1,x2,y2);//������ʾ����
	i=0;
	for(i=0;i<num;i++)
	{ 
		u16 LCD_PEN_COLOR	=	LCDSYS->Data.PColor;   	//����ɫ	
		temp=Buffer[i];		 				
		for(j=0;j<8;j++)
		{
			if((temp&0x80)==0X80)
			{
				LCD_PEN_COLOR=LCDSYS->Data.PColor;
			}
			else
				LCD_PEN_COLOR=LCDSYS->Data.BColor;
			LCD_WriteDataStart();
			LCD_WriteData(LCD_PEN_COLOR);
			LCD_WriteDataEnd();
			temp=temp<<1;
		}
		LCDSYS->Data.PColor=colortemp;	
	}	
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
		//=====================˫�ֽ�--����
		if(dst>0x80)
		{
			u16 word=dst<<8;
      
			dst=Buffer[i+1];
			word=word|dst;			
			//��ʾ�����ж�
			if(font==12)
			{
				if(x>MaxH-12)
				{
					x=0;
					y+=12;
				}
				if(y>MaxV-12)
				{
					y=x=0;
				}
			}
			else if(font==16)
			{
				if(x>MaxH-16)
				{
					x=0;
					y+=16;
				}
				if(y>MaxV-16)
				{
					y=x=0;
				}
			}
			else if(font==24)
			{
				if(x>MaxH-24)
				{
					x=0;
					y+=24;
				}
				if(y>MaxV-24)
				{
					y=x=0;
				}
			}
			else if(font==32)
			{
				if(x>MaxH-32)
				{
					x=0;
					y+=32;
				}
				if(y>MaxV-32)
				{
					y=x=0;
				}
			}
			else
			{

			}
			GetBufferLength	=	GT32L32_ReadCode(font,word,CodeBuffer);		//���ֿ��ж����ݲ��������ݳ���
			//д����Ļ
			LCD_ShowWord(x,y,font,GetBufferLength,CodeBuffer,0);
			//��ʾ��ַ����	
			if(font==12)
			{
				x+=12;
			}
			else if(font==16)
			{
				x+=16;
			}
			else if(font==24)
			{
				x+=24;
			}
			else if(font==32)
			{
				x+=32;
			}
			i++;		//˫�ֽڣ�������
			
		}
		//=====================���ֽ�--ASCII�ַ���
		else
		{			
			//��ʾ�����ж�
			if(font==12)
			{
				if(x>MaxH-12)
				{
					x=0;
					y+=12;
				}
				if(y>MaxV-12)
				{
					y=x=0;
				}
			}
			if(font==16)
			{
				if(x>MaxH-8)
				{
					x=0;
					y+=16;
				}
				if(y>MaxV-16)
				{
					y=x=0;
				}
			}
			if(font==24)
			{
				if(x>MaxH-24)
				{
					x=0;
					y+=24;
				}
				if(y>MaxV-24)
				{
					y=x=0;
				}
			}
			if(font==32)
			{
				if(x>MaxH-32)
				{
					x=0;
					y+=32;
				}
				if(y>MaxV-32)
				{
					y=x=0;
				}
			}
			GetBufferLength	=	GT32L32_ReadCode(font,(u16)dst,CodeBuffer);		//���ֿ��ж����ݲ��������ݳ���
//			//д����Ļ
			LCD_ShowChar(x,y,font,GetBufferLength,CodeBuffer,0);
			//��ʾ��ַ����
			if(font==12)
			{
				x+=6;
			}
			else if(font==16)
			{
				x+=8;
			}
			else if(font==24)
			{
				x+=12;
			}
			else if(font==32)
			{
				x+=16;
			}			
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
	
	unsigned short	MaxV,MaxH;	//�߽�ֵ
	unsigned short	i=0;				//��ʾ
	char	DataBuffer[256]={0};			//��¼format����
  unsigned char CodeBuffer[130]={0};
	//1)**********��ȡ���ݿ��
	u16 InputDataSize=strlen((const char*)format);		//��ȡ���ݿ��	
	
	//3)**********argsΪ�����һ��ָ��ɱ�����ı�����va_list�Լ��±�Ҫ�õ���va_start,va_end�������ڶ��壬�ɱ���������б���Ҫ�õ��꣬ ��stdarg.hͷ�ļ��ж���
	va_list args; 
	//5)**********��ʼ��args�ĺ�����ʹ��ָ��ɱ�����ĵ�һ��������format�ǿɱ������ǰһ������
	va_start(args, format);
	//6)**********��������·��������ִ��ĳ���(��ȥ\0),����������ظ�ֵ
	vsnprintf(DataBuffer, InputDataSize+1,format, args);

	//7)**********�����ɱ�����Ļ�ȡ
	va_end(args);                                      		

	LCD_Show(x,y,font,InputDataSize,(unsigned char*)DataBuffer);
	return InputDataSize;
}
/**************************************************************************************************
* [Function] LCD_DrawPixelEx:  �������ܡ�ע������ȵ�����
* [param01]u16 x: description
* [param02]u16 y: description
* [param03]u16 color: description
**************************************************************************************************/
void LCD_DrawPixelEx( u16 x, u16 y, u16 color )
{
	LCD_DrawDot(x,y,color);		//����
}
/*******************************************************************************
* ������			:	function
* ��������		:	��������˵�� 
* ����			: void
* ����ֵ			: void
*******************************************************************************/
void LCD_Delay(u32 xms)
{
	while(xms--);
}

//#endif//LCD_61509_EN
/************************************** The End Of FILE **************************************/


