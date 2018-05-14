#ifndef	_TM16382_H
#define	_TM16382_H

#include "STM32F10x_BitBand.H"
#include "STM32_GPIO.H"
//#include	<REGX51.H>

//#define	DATA_COMMAND	0X40		//������������:���ݶ�дģʽ����ַ����ģʽ
//#define	DISP_COMMAND	0x80		//��ʾ�����ʾ��������
//#define	ADDR_COMMAND	0XC0		//��ַ��������:����д����ʼ��ַ

//TM1638ģ�����Ŷ���
#define	DIO	PC12
#define	CLK	PC11
#define	STB	PD2

#define	DIO_Port	GPIOC
#define	DIO_Pin		GPIO_Pin_12

#define	CLK_Port	GPIOC
#define	CLK_Pin		GPIO_Pin_11

#define	STB_Port	GPIOD
#define	STB_Pin		GPIO_Pin_2

//�����������ʾ����
unsigned char code[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71};

/*******************************************************************************
* ������			:	function
* ��������		:	��������˵�� 
* ����			: void
* ����ֵ			: void
*******************************************************************************/
void TM1638_Write(unsigned char	DATA)			//д���ݺ���
{
	unsigned char i;
	for(i=0;i<8;i++)
	{
		CLK=0;
		if(DATA&0X01)
			DIO=1;
		else
			DIO=0;
		DATA>>=1;
		CLK=1;
	}
}
/*******************************************************************************
* ������			:	function
* ��������		:	��������˵�� 
* ����			: void
* ����ֵ			: void
*******************************************************************************/
unsigned char TM1638_Read(void)					//�����ݺ���
{
	unsigned char i;
	unsigned char temp=0;
	DIO=1;	//����Ϊ����
	for(i=0;i<8;i++)
	{
		temp>>=1;
		CLK=0;
		if(DIO)
			temp|=0x80;
		CLK=1;
	}
	return temp;
}
/*******************************************************************************
* ������			:	Write_COM
* ��������		:	���������� 
* ����			: void
* ����ֵ			: void
*******************************************************************************/
void Write_COM(unsigned char cmd)		//����������
{
	STB=0;
	TM1638_Write(cmd);
	STB=1;
}
/*******************************************************************************
* ������			:	Read_key
* ��������		:	��������˵�� 
* ����			: void
* ����ֵ			: void
*******************************************************************************/
unsigned char Read_key(void)
{
	unsigned char c[4],i,key_value=0;
	STB=0;
	TM1638_Write(0x42);		           //����ɨ���� ����
	for(i=0;i<4;i++)		
		c[i]=TM1638_Read();
	STB=1;					           //4���ֽ����ݺϳ�һ���ֽ�
	for(i=0;i<4;i++)
		key_value|=c[i]<<i;
	for(i=0;i<8;i++)
		if((0x01<<i)==key_value)
			break;
	return i;
}
/*******************************************************************************
* ������			:	function
* ��������		:	��������˵�� 
* ����			: void
* ����ֵ			: void
*******************************************************************************/
void Write_DATA(unsigned char add,unsigned char DATA)		//ָ����ַд������
{
	Write_COM(0x40);					//�̶���ַ
	STB=0;
	TM1638_Write(0xC0|add);		//д��ַ
	TM1638_Write(DATA);				//д����
	STB=1;
}
/*******************************************************************************
* ������			:	Write_DataFX
* ��������		:	�̶���ַ��ʽ
* ����			: void
* ����ֵ			: void
*******************************************************************************/
void Write_DataFX(unsigned char add,unsigned char DATA)		//�̶���ַ��ʽ
{
	Write_COM(0x44);					//�̶���ַ����
	STB=0;
	TM1638_Write(0xC0|(add<<1));		//д��ַ
	TM1638_Write(DATA);				//д����
	STB=1;
}
/*******************************************************************************
* ������			:	Write_DataAI
* ��������		:	��ַ����
* ����			: void
* ����ֵ			: void
*******************************************************************************/
void Write_DataAI(unsigned char add,unsigned char DATA)		//��ַ����
{
	unsigned char i;
	Write_COM(0x40);					//��ַ��������
	STB=0;
	TM1638_Write(0xC0);    		//������ʼ��ַ
	for(i=0;i<8;i++)	   			//����16���ֽڵ�����
	{
		TM1638_Write(DATA);			//д����
		TM1638_Write(0x01);			//д����
	}
	STB=1;
}
/*******************************************************************************
* ������			:	Write_DataNum
* ��������		:	��ַ������ʽд����
* ����			: Startadd--��ʼ��ַ��Num--����
* ����ֵ			: void
*******************************************************************************/
void Write_DataNum(unsigned char Startadd,unsigned long Num)		//��ַ����
{
//	Write_COM(0x40);					//��ַ��������
	STB=0;
	TM1638_Write(0xC0|Startadd);    		//������ʼ��ַ
	
	TM1638_Write(code[Num/10000000]);
	TM1638_Write(code[Num/10000000]);			//д����
	TM1638_Write(code[Num%10000000/1000000]);
	TM1638_Write(code[Num%10000000/1000000]);			//д����
	TM1638_Write(code[Num%1000000/100000]);
	TM1638_Write(code[Num%1000000/100000]);			//д����
	TM1638_Write(code[Num%100000/10000]);
	TM1638_Write(code[Num%100000/10000]);			//д����
	TM1638_Write(code[Num%10000/1000]);
	TM1638_Write(code[Num%10000/1000]);			//д����
	TM1638_Write(code[Num%1000/100]);
	TM1638_Write(code[Num%1000/100]);			//д����
	TM1638_Write(code[Num%100/10]);
	TM1638_Write(code[Num%100/10]);			//д����
	TM1638_Write(code[Num%10]);
	TM1638_Write(code[Num%10]);			//д����
	STB=1;
}
/*
void Write_oneLED(unsigned char num,unsigned char flag)	//��������һ��LED������numΪ��Ҫ���Ƶ�led��ţ�flagΪ0ʱϨ�𣬲�Ϊ0ʱ����
{
	if(flag)
		Write_DATA(2*num+1,1);
	else
		Write_DATA(2*num+1,0);
}  	*/
/*******************************************************************************
* ������			:	function
* ��������		:	��������˵�� 
* ����			: void
* ����ֵ			: void
*******************************************************************************/
void Write_allLED(unsigned char LED_flag)					//����ȫ��LED������LED_flag��ʾ����LED״̬
{
	unsigned char i;
	for(i=0;i<8;i++)
		{
			if(LED_flag&(1<<i))
				//Write_DATA(2*i+1,3);
				Write_DATA(2*i+1,1);
			else
				Write_DATA(2*i+1,0);
		}
}
/*******************************************************************************
* ������			:	function
* ��������		:	��������˵�� 
* ����			: void
* ����ֵ			: void
*******************************************************************************/
//TM1638��ʼ������
void init_TM1638(void)
{
	unsigned char i;
	GPIO_Configuration_OPP50	(DIO_Port,	DIO_Pin);			//��GPIO��Ӧ�ܽ�����ΪPP(����)���ģʽ������ٶ�50MHz----V20170605
	GPIO_Configuration_OPP50	(CLK_Port,	CLK_Pin);			//��GPIO��Ӧ�ܽ�����ΪPP(����)���ģʽ������ٶ�50MHz----V20170605
	GPIO_Configuration_OPP50	(STB_Port,	STB_Pin);			//��GPIO��Ӧ�ܽ�����ΪPP(����)���ģʽ������ٶ�50MHz----V20170605
	
	Write_COM(0x8F);       //���� (0x88-0x8f)8�����ȿɵ�
	Write_COM(0x40);       //���õ�ַ�Զ���1
	STB=0;		           //
	TM1638_Write(0xC0);    //������ʼ��ַ

	for(i=0;i<16;i++)	   //����16���ֽڵ�����
		TM1638_Write(0xFF);
	STB=1;
}
#endif
