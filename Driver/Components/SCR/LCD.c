/**************************************************************************************************
* Һ��������IC
* �ļ�<$(filename)>
* ģ������ :	���塢���ܡ�˵��
* ��ʷ�޸ļ�¼
*     <��Ҫ�޸���>  <ʱ��>   <�汾 >   <˵��>
*     xlyan        $(Date)   1.0.0    �����ļ�
**************************************************************************************************/
#include "LCD.H"


//#define	SSD1963_USED

#ifdef SSD1963_USED
	#include "SSD1963.H"
#else
	#include "R61509V.h"
#endif

//#include "GT32L32M0180.H"



#include "STM32_GPIO.H"
#include "STM32_PWM.H"
#include "STM32_SYSTICK.H"
#include "font.h"
#include "string.h"				//�����ڴ��������ͷ�ļ�
#include "stdlib.h"				//�����ڴ��������ͷ�ļ�
#include "stdarg.h"				//�����ڴ��������ͷ�ļ�
#include "stdio.h"				//�����ڴ��������ͷ�ļ�

LCDDef 			*LCDSYS	=	0;
/*******************************************************************************
*������			:	LCD_Initialize
*��������		:	LCD��ʼ����
*����				: 
*����ֵ			:	��
*******************************************************************************/
void LCD_Initialize(LCDDef *pInfo)
{
	LCDSYS	=	pInfo;
	
#ifdef SSD1963_USED
	SSD1963_Initialize();
#else
	R61509V_Initialize();
#endif
	
	
	LCD_PortInitialize(&pInfo->Port);			//LCD�˿�����
	LCDSYS->Display.PowerOn();						//LCD�ϵ�/��ʼ������
	
	
	GT32L32_ConfigurationNR(&pInfo->GT32L32);				//��ͨSPIͨѶ��ʽ����	
	GPIO_Configuration_OPP50	(pInfo->GT32L32.Port.sGT32L32_CS_PORT,pInfo->GT32L32.Port.sGT32L32_CS_PIN);			//��GPIO��Ӧ�ܽ�����ΪPP(����)���ģʽ������ٶ�50MHz----V20170605

}
/*******************************************************************************
* ������			:	function
* ��������		:	��������˵�� 
* ����			: void
* ����ֵ			: void
*******************************************************************************/
void LCD_PortInitialize(LCDPortDef *pPort)
{
	LCDPortDef		*Port;	
	
	Port	=	pPort;
	
	GPIO_Configuration_OPP50	(Port->sBL_PORT,				Port->sBL_Pin);					//��GPIO��Ӧ�ܽ�����ΪPP(����)���ģʽ������ٶ�2MHz----V20170605
	GPIO_Configuration_OPP50	(Port->sRD_PORT,				Port->sRD_Pin);					//��GPIO��Ӧ�ܽ�����ΪPP(����)���ģʽ������ٶ�2MHz----V20170605
	GPIO_Configuration_OPP50	(Port->sREST_PORT,			Port->sREST_Pin);				//��GPIO��Ӧ�ܽ�����ΪPP(����)���ģʽ������ٶ�2MHz----V20170605
	GPIO_Configuration_OPP50	(Port->sDC_PORT,				Port->sDC_Pin);					//��GPIO��Ӧ�ܽ�����ΪPP(����)���ģʽ������ٶ�2MHz----V20170605
	GPIO_Configuration_OPP50	(Port->sWR_PORT,				Port->sWR_Pin);					//��GPIO��Ӧ�ܽ�����ΪPP(����)���ģʽ������ٶ�2MHz----V20170605
	GPIO_Configuration_OPP50	(Port->sCS_PORT,				Port->sCS_Pin);					//��GPIO��Ӧ�ܽ�����ΪPP(����)���ģʽ������ٶ�2MHz----V20170605
	GPIO_Configuration_OPP50	(Port->sTE_PORT,				Port->sTE_Pin);					//��GPIO��Ӧ�ܽ�����ΪPP(����)���ģʽ������ٶ�2MHz----V20170605
	GPIO_Configuration_OPP50	(Port->sDATABUS_PORT,		Port->sDATABUS_Pin);		//��GPIO��Ӧ�ܽ�����ΪPP(����)���ģʽ������ٶ�2MHz----V20170605	
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
	
if	(Rotate	==Draw_Rotate_0D)
{
	LCDSYS->Data.HSX	=	x1;
	LCDSYS->Data.HEX	=	x2;
	LCDSYS->Data.VSY	=	y1;
	LCDSYS->Data.VEY	=	y2;
	
	LCDSYS->Data.HXA	=	LCDSYS->Data.HSX;
	LCDSYS->Data.VYA	=	LCDSYS->Data.VSY;
	
	Model	=	0x5030;
}
else if (Rotate	==Draw_Rotate_90D)
{
	LCDSYS->Data.HSX	=	y1;
	LCDSYS->Data.HEX	=	y2;	
	LCDSYS->Data.VSY	=	MaxV	-	x2	-	1;
	LCDSYS->Data.VEY	=	MaxV	-	x1	-	1;
	
	LCDSYS->Data.HXA	=	LCDSYS->Data.HSX;
	LCDSYS->Data.VYA	=	LCDSYS->Data.VEY;
	Model	=	0X5018;								//GRAM(Graphics RAM--ͼ���ڴ�) Data Write (R202h)׼��д��
}
else if (Rotate	==Draw_Rotate_180D)	
{
	LCDSYS->Data.HSX	=	MaxH	-	x2	-	1;
	LCDSYS->Data.HEX	=	MaxH	-	x1	-	1;
	LCDSYS->Data.VSY	=	MaxV	-	y2	-	1;
	LCDSYS->Data.VEY	=	MaxV	-	y1	-	1;
	
	LCDSYS->Data.HXA	=	LCDSYS->Data.HEX;
	LCDSYS->Data.VYA	=	LCDSYS->Data.VEY;
	
	Model	=	0X5000;
}
else //(Rotate	==Draw_Rotate_270D)
{
	LCDSYS->Data.HSX	=	MaxH	-	y2	-	1;
	LCDSYS->Data.HEX	=	MaxH	-	y1	-	1;
	LCDSYS->Data.VSY	=	x1;
	LCDSYS->Data.VEY	=	x2;
	
	LCDSYS->Data.HXA	=	LCDSYS->Data.HEX;
	LCDSYS->Data.VYA	=	LCDSYS->Data.VSY;

	Model	=	0X5028;
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
	//	LCD_H 240		//ˮƽ���������������+
	//	LCD_V 400		//��ֱ������������ϵ���+
	unsigned short x,y;
	unsigned short HSX,HEX,HSY,HEY,MaxH,MaxV;
	eRotate	Rotate	=	LCDSYS->Flag.Rotate;
	
	MaxH	=	LCDSYS->Data.MaxH;
	MaxV	=	LCDSYS->Data.MaxV;
	
	if	(Rotate	==Draw_Rotate_0D)
	{
		HSX	=	0;
		HEX	=	MaxH-1;
		HSY	=	0;
		HEY	=	MaxV-1;
	}
	else if (Rotate	==Draw_Rotate_90D)
	{
		HSX	=	0;
		HEX	=	MaxV-1;
		HSY	=	0;
		HEY	=	MaxH-1;
	}
	else if (Rotate	==Draw_Rotate_180D)
	{
		HSX	=	0;
		HEX	=	MaxH-1;
		HSY	=	0;
		HEY	=	MaxV-1;
	}
	else //if (Rotate	==Draw_Rotate_270D)
	{
		HSX	=	0;
		HEX	=	MaxV-1;
		HSY	=	0;
		HEY	=	MaxH-1;
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

//	u16	Num	=	0,i=0;
////	CoordinateTransform(&x1,&y1,&x2,&y2);
//	if(HSX>HEX)
//	{
//		Num	+=	HSX-HEX;
//	}
//	else
//	{
//		Num	+=	HEX-HSX;
//	}
//	if(HSY>HEY)
//	{
//		Num	+=	HSY-HEY;
//	}
//	else
//	{
//		Num	+=	HEY-HSY;
//	}
//	
//	LCDSYS->Display.WriteAddress(HSX,HSY,HEX,HEY);//���ô���ַ
//	LCD_WriteDataStart();
//	for(i=0;i<Num;i++)
//	{
//		LCD_WriteData(Color); 	//�ʻ���ɫ
//	}
//	LCD_WriteDataEnd();
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
							unsigned short HSX, unsigned short HSY, 	//x1,y1:�������
							unsigned short HEX, unsigned short HEY,		//x2,y2:�յ�����
							u16 color
)
{          
	unsigned int i;
	unsigned int j;	
//	u16 x1=0,y1=0,x2=0,y2=0;

//	switch(Sreen_Rotate)
//	{
//		case 	SCREEN_ROTATE_0D:		
//					{
//						xend=xend-1;
//						yend=yend-1;
//					}
//			break;
//		case 	SCREEN_ROTATE_90D:	
//					{
//						x1=xsta;x2=xend;y1=ysta;y2=yend;	
//						xsta=LCD_H-y2;	xend=LCD_H-y1-1;
//						ysta=x1;	yend=x2-1;
//					}
//			break;
//		case 	SCREEN_ROTATE_180D:	
//					{
//						x1=xsta;x2=xend;y1=ysta;y2=yend;
//						xsta=LCD_H-x2;	xend=LCD_H-x1-1;
//						ysta=LCD_W-y2;	yend=LCD_W-y1-1;
//					}
//			break;
//		case	SCREEN_ROTATE_270D:	
//					{
//						x1=xsta;x2=xend;y1=ysta;y2=yend;
//						xsta=y1;	xend=y2-1;
//						ysta=LCD_W-x2;	yend=LCD_W-x1-1;
//					}
//			break;
//		default: break;			
//	}
	
//	switch(Sreen_Rotate)
//	{
//		case SCREEN_ROTATE_0D:{}
//			break;
//		case SCREEN_ROTATE_90D:{x1=LCD_H-y;y=x;x=x1;}
//			break;
//		case SCREEN_ROTATE_180D:{x1=LCD_H-x;y=LCD_W-y;x=x1;}
//			break;
//		case	SCREEN_ROTATE_270D:{x1=y;y=LCD_W-x;x=x1;}
//			break;
//		default: break;			
//	}

	LCDSYS->Display.WriteAddress(HSX,HSY,HEX,HEY);
	LCD_WriteDataStart();
	for(i=0;i<HEX-HSX;i++)
	{
		for(j=0;j<HEY-HSY;j++)
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
										u8 *Buffer	//Buffer	:��ʾ�����ݻ���
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
//		LCD_SetWindowAddress(x,y,x+12-1,y+12);      //���ù��λ�� 
	}
	if(font==16)
	{
		if(x>LCDSYS->Data.MaxV-16||y>LCDSYS->Data.MaxH-16)
			return;
		x2	=	x+16-1;
		y2	=	y+16-1;
//		LCD_SetWindowAddress(x,y,x+16-1,y+16);      //���ù��λ�� 
	}
	if(font==24)
	{
		if(x>LCDSYS->Data.MaxV-24||y>LCDSYS->Data.MaxH-24)
			return;
		x2	=	x+24-1;
		y2	=	y+24-1;
//		LCD_SetWindowAddress(x,y,x+24-1,y+24);      //���ù��λ�� 
	}
	else if(font==32)
	{
		if(x>LCDSYS->Data.MaxV-32||y>LCDSYS->Data.MaxH-32)
			return;
		if(num==128)
		{
			x2	=	x+32-1;
			y2	=	y+32-1;
//			LCD_SetWindowAddress(x,y,x+32-1,y+32);      //���ù��λ��
		}
		else
		{
			x2	=	x+16-1;
			y2	=	y+32-1;
//			LCD_SetWindowAddress(x,y,x+16-1,y+32);      //���ù��λ�� 
		}
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
//		temp	=	0xFF;
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
*������		:	LCD_ShowChar
*��������	:	��ָ��λ����ʾһ���ַ�
*����			: x,y		:�������
						num		:Ҫ��ʾ���ַ�:" "--->"~"
						mode	:���ӷ�ʽ(1)���Ƿǵ��ӷ�ʽ(0)
						num		:Ҫ��ʾ���ַ�:" "--->"~"
*���			:	��
*����ֵ		:	��
*����			:
*******************************************************************************/
void LCD_ShowCharT(u16 x,u16 y,u8 num,u8 mode)
{
////	LCD_BACK_COLOR	//����ɫ
////	LCD_POINT_COLOR	//����ɫ
//	u8 temp;
//	u8 pos,t;
//	u16 x0=x;
//	u16 colortemp=LCD_POINT_COLOR; 
//	if(x>LCD_V-16||y>LCD_H-16)
//		return;	    
//	//���ô���		   
//	num=num-' ';//�õ�ƫ�ƺ��ֵ
////	num=41;//�õ�ƫ�ƺ��ֵ
//	
//	
////	LCD_SetWindowAddress(x,y,x+8-1,y+16-1);      //���ù��λ�� 
//	if(!mode) //�ǵ��ӷ�ʽ
//	{
//		for(pos=0;pos<16;pos++)
//		{ 
//			temp=code_asc2_1608[(u16)num*16+pos];		 		//����1608����
////			temp=code_num_1608[(u16)num*16+pos];		 //����1608����
//			for(t=0;t<8;t++)
//			{                 
//				if((temp&0x01)==0x01)
//					LCD_POINT_COLOR=colortemp;
//				else
//					LCD_POINT_COLOR=LCD_BACK_COLOR;

//				LCD_DrawDot(x,y,LCD_POINT_COLOR);//��һ���� 
//				
//				temp=temp>>1; 
//				x++;
//			}
//			x=x0;
//			y++;
//		}	
//	}
//	else//���ӷ�ʽ
//	{
//		for(pos=0;pos<16;pos++)
//		{
//			temp=code_asc2_1608[(u16)num*16+pos];		 //����1608����
//			for(t=0;t<8;t++)
//			{                 
//				if(temp&0x01)
//					LCD_DrawDot(x+t,y+pos,LCD_POINT_COLOR);//��һ����     
//				temp>>=1; 
//			}
//		}
//	}
//	LCD_POINT_COLOR=colortemp;	    	   	 	  
}
/*******************************************************************************
*������			:	R61509V_Clean
*��������		:	��ʾ���ֳ���
*����				: 
*����ֵ			:	��
*******************************************************************************/
void LCD_ShowChinese(unsigned char zimo[720],unsigned int backcolor)  //д���ַ�
{
	unsigned char j,flag=0;
	unsigned char *point;
	unsigned int i,x1=0x00,x2=0x17,y1=0x00,y2=0x17;
	unsigned int colors[10]=
	{
		0xf800,0x07e0,0x001f,0xffe0,0x0000,0x07ff,0xf81f,0xb81f,0x7f7,0xfec0
	};
	point=&zimo[0];
	LCD_WriteDataStart();
	for(i=1;i<=720;i++,point++)
	{  
		for(j=0;j<=7;j++)
		{
			if((*point<<j)&0x80)
			{
				LCD_WriteData(colors[flag]);
			}
			else
			{
				LCD_WriteData(backcolor);
			}
		}   
		if(i%72==0)
		{
			x1=x1+24;x2=x2+24;y1=y1+24;y2=y2+24;
			flag=flag+1;
			LCDSYS->Display.WriteAddress(x1,y1,x2,y2);
		}   
	}
	LCD_WriteDataEnd();
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
unsigned int LCD_Printf(u16 x,u16 y,u8 font,const char *format,...)				//��ߵ�ʡ�Ժž��ǿɱ����
{ 
		
//		va_list ap; 										//VA_LIST ����C�����н����������һ��꣬����ͷ�ļ���#include <stdarg.h>,���ڻ�ȡ��ȷ�������Ĳ���
//		static char string[ 256 ];			//�������飬
//  	va_start( ap, format );
//		vsprintf( string , format, ap );    
//		va_end( ap );
	

	u16 i=0;		//��ʾ
	char	Char_Buffer[256];		//��¼format����
	//1)**********��ȡ���ݿ��
	u16 num=strlen((const char*)format);		//��ȡ���ݿ��
	//2)**********���建������С����
	unsigned int BufferSize;
	//3)**********argsΪ�����һ��ָ��ɱ�����ı�����va_list�Լ��±�Ҫ�õ���va_start,va_end�������ڶ��壬�ɱ���������б���Ҫ�õ��꣬ ��stdarg.hͷ�ļ��ж���
	va_list args; 
	//5)**********��ʼ��args�ĺ�����ʹ��ָ��ɱ�����ĵ�һ��������format�ǿɱ������ǰһ������
	va_start(args, format);
	//6)**********��������·��������ִ��ĳ���(��ȥ\0),����������ظ�ֵ
	BufferSize = vsnprintf(Char_Buffer, 128,format, args);
	num=BufferSize;
	//7)**********�����ɱ�����Ļ�ȡ
	va_end(args);                                      		
	
	for(i=0;i<num;i++)
	{ 
		unsigned char dst=Char_Buffer[i];
//		u8 GTBuffer[512]={0};		//�������ݴ洢�ռ�
//		u32 lengh=0;						//���ֵ�������ݳ���		
		if(dst>0x80)		//˫�ֽ�--����
		{
			u16 word=dst<<8;			
//			Char_Buffer++;
			dst=Char_Buffer[i+1];
			word=word|dst;			
			//��ʾ�����ж�
			if(font==16&&x>LCDSYS->Data.MaxV-16)
			{
				x=0;
				y+=16;
			}
			if(font==32&&x>LCDSYS->Data.MaxV-32)
			{
				x=0;
				y+=32;
			}
			if(font==16&&y>LCDSYS->Data.MaxV-16)
			{
				y=x=0;
			}
			if(font==32&&y>LCDSYS->Data.MaxV-32)
			{
				y=x=0;
			}
			GT32L32_ReadBuffer(&LCDSYS->GT32L32,font,word);		//���ֿ��ж����ݺ���
			//д����Ļ
			LCD_ShowChar(x,y,font,LCDSYS->GT32L32.Data.BufferSize,LCDSYS->GT32L32.Data.Buffer);
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
//			Char_Buffer++;
			i++;		//˫�ֽڣ�������
		}
		else		//���ֽ�
		{			
			if(x>LCDSYS->Data.MaxH-16)
			{
				x=0;
				y+=32;
			}
			if(font==16&&y>LCDSYS->Data.MaxH-16)
			{
				y=x=0;
			}
			if((font==32)&&(y>LCDSYS->Data.MaxH-32))
			{
				y=x=0;
			}
			GT32L32_ReadBuffer(&LCDSYS->GT32L32,font,(u16)dst);		//���ֿ��ж����ݺ���
//			//д����Ļ
			LCD_ShowChar(x,y,font,LCDSYS->GT32L32.Data.BufferSize,LCDSYS->GT32L32.Data.Buffer);			
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
//			Char_Buffer++;
//			i++;		//˫�ֽڣ�������
		}
	}
	//9)**********DMA������ɺ�ע��Ӧ���ͷŻ�������free(USART_BUFFER);
//	free(Char_Buffer);		//������ɺ�ע��Ӧ���ͷŻ�������free(Char_Buffer); 
	return BufferSize;
//	return 0;
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


