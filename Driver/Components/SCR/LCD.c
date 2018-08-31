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

//
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
	u8 temp;
	u8 i=0,j=0;
	unsigned short x1=0,x2=0,y1=0,y2=0;
	unsigned short LCD_PEN_COLOR	=	LCDSYS->Data.PColor;   	//����ɫ
	x1	=	x;
	y1	=	y;
//  if(x>LCDSYS->Data.MaxV-font||y>LCDSYS->Data.MaxH-font)
//			return;
    x2	=	x+font/2-1;
    y2	=	y+font-1;
	LCDSYS->Display.WriteAddress(x1,y1,x2,y2);//������ʾ����
	i=0;
	LCD_WriteDataStart();
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
				LCD_PEN_COLOR=LCDSYS->Data.BColor;
			LCD_WriteData(LCD_PEN_COLOR);
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
          LCD_PEN_COLOR=LCDSYS->Data.BColor;
        LCD_WriteData(LCD_PEN_COLOR);
        temp=temp<<1;
      }
      i++;
    }		
	}
	LCD_WriteDataEnd();	
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
	u8 temp;
	u8 i=0,j=0;
	unsigned short x1=0,x2=0,y1=0,y2=0;
	unsigned short LCD_PEN_COLOR	=	LCDSYS->Data.PColor;   	//����ɫ
	x1	=	x;
	y1	=	y;
  
//  if(x>LCDSYS->Data.MaxH-font||y>LCDSYS->Data.MaxV-font)
//    return;
  x2	=	x+font-1;
  y2	=	y+font-1;
	LCDSYS->Display.WriteAddress(x1,y1,x2,y2);//������ʾ����
	LCD_WriteDataStart();
	for(i=0;i<num;i++)
	{ 
		u16 LCD_PEN_COLOR	=	LCDSYS->Data.PColor;   	//����ɫ	
		temp=Buffer[i];		 				
		for(j=0;j<8;j++)
		{
			if((temp&0x80)==0X80)
			{
				LCD_PEN_COLOR=color;
			}
			else
				LCD_PEN_COLOR=LCDSYS->Data.BColor;
			LCD_WriteData(LCD_PEN_COLOR);
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
          LCD_PEN_COLOR=LCDSYS->Data.BColor;
        LCD_WriteData(LCD_PEN_COLOR);
        temp=temp<<1;
      }
      i++;
    }			
	}
	LCD_WriteDataEnd();
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
			GetBufferLength	=	GT32L32_ReadCode(font,word,CodeBuffer);		//���ֿ��ж����ݲ��������ݳ���
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
        y+=12;
      }
      //B2=====================��ʾ����β����ԭ�㿪ʼ
      if(y>MaxV-font)
      {
        y=x=0;
      }
      //B3=====================��ȡ��������
			GetBufferLength	=	GT32L32_ReadCode(font,(u16)dst,CodeBuffer);		//���ֿ��ж����ݲ��������ݳ���
			//B4=====================д����Ļ
			LCD_ShowChar(x,y,font,PenColor,GetBufferLength,CodeBuffer);
			//B5=====================ˮƽ��ʾ��ַ����
      x+=font/2;						
		}
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
      if((0<=dst)&&(9>=dst))
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
      GetBufferLength	=	GT32L32_ReadCode(font,dst,CodeBuffer);		//���ֿ��ж����ݲ��������ݳ���
      //4=====================д����Ļ
      LCD_ShowChar(x,y,font,color,GetBufferLength,CodeBuffer);
      //5=====================��ʾ��ַ����
      x+=font/2;
    }
    //========================����ո�
    //3=====================��ȡ��������
//    GetBufferLength	=	GT32L32_ReadCode(font,' ',CodeBuffer);		//���ֿ��ж����ݲ��������ݳ���
    //4=====================д����Ļ
//    LCD_ShowChar(x,y,font,GetBufferLength,CodeBuffer,0);
    //5=====================��ʾ��ַ����
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
  if((12!=font)&&(16!=font)&&(24!=font)&&(32!=font))
  {
    font  = 24;
  }
	LCD_Show(x,y,font,color,InputDataSize,(unsigned char*)DataBuffer);
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
  LCDSYS->Flag.Rotate  = Draw_Rotate_0D;		//ʹ����ת�Ƕ�
  LCDSYS->Display.WriteAddress(x1,y1,x2,y2);//������ʾ����
  LCD_WriteDataStart();
	for(i=0;i<Length;)
	{
    RGB565  =   (RGBBuffer[j+2]>>3);
    RGB565  <<= 5;
    RGB565  |=  (RGBBuffer[j+1]>>3);
    RGB565  <<= 6;
    RGB565  |=  (RGBBuffer[j+0]>>3);
    LCD_WriteData(RGB565);
    j+=3;
    i+=3;
	}
  LCD_WriteDataEnd();
  LCDSYS->Flag.Rotate  =  Rotate;
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


