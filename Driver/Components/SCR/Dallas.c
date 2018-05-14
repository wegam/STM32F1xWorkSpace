#include "Dallas.h"	


#include "STM32_GPIO.H"
#include "STM32_SYSTICK.H"



#define	Port_Dallas		GPIOC
#define	Pin_Dallas		GPIO_Pin_2

#define	Dallas_SetOut		GPIO_Configuration_OPP50(Port_Dallas,	Pin_Dallas)			//��GPIO��Ӧ�ܽ�����ΪPP(����)���ģʽ������ٶ�50MHz----V20170605
#define	Dallas_SetIn		GPIO_Configuration_IPU(Port_Dallas,		Pin_Dallas)			//��GPIO��Ӧ�ܽ�����Ϊ��������ģʽ----V20170605

#define	Dallas_H			Port_Dallas->BSRR	= Pin_Dallas			//CPLD_WR	=	1;
#define	Dallas_L			Port_Dallas->BRR	= Pin_Dallas			//CPLD_WR	=	0;

#define	Dallas_Read		Port_Dallas->IDR	& Pin_Dallas			//CPLD_WR	=	0;


const uint8_t g_CRC8Tab[256]=
{
0x00, 0x5e, 0xbc, 0xe2, 0x61, 0x3f, 0xdd, 0x83, 0xc2, 0x9c, 0x7e, 0x20, 0xa3, 0xfd, 0x1f, 0x41,
0x9d, 0xc3, 0x21, 0x7f, 0xfc, 0xa2, 0x40, 0x1e, 0x5f, 0x01, 0xe3, 0xbd, 0x3e, 0x60, 0x82, 0xdc,
0x23, 0x7d, 0x9f, 0xc1, 0x42, 0x1c, 0xfe, 0xa0, 0xe1, 0xbf, 0x5d, 0x03, 0x80, 0xde, 0x3c, 0x62,
0xbe, 0xe0, 0x02, 0x5c, 0xdf, 0x81, 0x63, 0x3d, 0x7c, 0x22, 0xc0, 0x9e, 0x1d, 0x43, 0xa1, 0xff,
0x46, 0x18, 0xfa, 0xa4, 0x27, 0x79, 0x9b, 0xc5, 0x84, 0xda, 0x38, 0x66, 0xe5, 0xbb, 0x59, 0x07,
0xdb, 0x85, 0x67, 0x39, 0xba, 0xe4, 0x06, 0x58, 0x19, 0x47, 0xa5, 0xfb, 0x78, 0x26, 0xc4, 0x9a,
0x65, 0x3b, 0xd9, 0x87, 0x04, 0x5a, 0xb8, 0xe6, 0xa7, 0xf9, 0x1b, 0x45, 0xc6, 0x98, 0x7a, 0x24,
0xf8, 0xa6, 0x44, 0x1a, 0x99, 0xc7, 0x25, 0x7b, 0x3a, 0x64, 0x86, 0xd8, 0x5b, 0x05, 0xe7, 0xb9,
0x8c, 0xd2, 0x30, 0x6e, 0xed, 0xb3, 0x51, 0x0f, 0x4e, 0x10, 0xf2, 0xac, 0x2f, 0x71, 0x93, 0xcd,
0x11, 0x4f, 0xad, 0xf3, 0x70, 0x2e, 0xcc, 0x92, 0xd3, 0x8d, 0x6f, 0x31, 0xb2, 0xec, 0x0e, 0x50,
0xaf, 0xf1, 0x13, 0x4d, 0xce, 0x90, 0x72, 0x2c, 0x6d, 0x33, 0xd1, 0x8f, 0x0c, 0x52, 0xb0, 0xee,
0x32, 0x6c, 0x8e, 0xd0, 0x53, 0x0d, 0xef, 0xb1, 0xf0, 0xae, 0x4c, 0x12, 0x91, 0xcf, 0x2d, 0x73,
0xca, 0x94, 0x76, 0x28, 0xab, 0xf5, 0x17, 0x49, 0x08, 0x56, 0xb4, 0xea, 0x69, 0x37, 0xd5, 0x8b,
0x57, 0x09, 0xeb, 0xb5, 0x36, 0x68, 0x8a, 0xd4, 0x95, 0xcb, 0x29, 0x77, 0xf4, 0xaa, 0x48, 0x16,
0xe9, 0xb7, 0x55, 0x0b, 0x88, 0xd6, 0x34, 0x6a, 0x2b, 0x75, 0x97, 0xc9, 0x4a, 0x14, 0xf6, 0xa8,
0x74, 0x2a, 0xc8, 0x96, 0x15, 0x4b, 0xa9, 0xf7, 0xb6, 0xe8, 0x0a, 0x54, 0xd7, 0x89, 0x6b, 0x35
};

///*******************************************************************************
//* ������			:	function
//* ��������		:	��������˵�� 
//* ����			: void
//* ����ֵ			: void
//*******************************************************************************/
//void Delay_us(unsigned short time)
//{
//	time	=	72*time;
//	while(time--);
//}
//�����㷽��
uint8_t CRC8_Calculate(uint8_t *pBuf, uint8_t len)
{
	uint8_t crc8=0;	//CRC8�ֽڳ�ʼ��
	
	//����CRC8λУ��
	while(len)
	{
		crc8 = g_CRC8Tab[*pBuf^crc8];
		pBuf++;
		len--;
	}

	return(crc8);	//����CRC8У������
}  
/*******************************************************************************
* ������			:	function
* ��������		:	��������˵�� 
* ����			: void
* ����ֵ			: void
*******************************************************************************/
void DS2401_Configuration(void)
{
	GPIO_Configuration_OPP50	(Port_Dallas,	Pin_Dallas);			//��GPIO��Ӧ�ܽ�����ΪPP(����)���ģʽ������ٶ�50MHz----V20170605
}
/*******************************************************************************
* ������			:	function
* ��������		:	��λDallas--��������(����480uS,����48uS),Ȼ���ͷ����ߣ��ȴ��ӻ���������
* ����			: void
* ����ֵ			: void
*******************************************************************************/
void Dallas_Rest(void)		//��λDallas
{                 
	Dallas_SetOut;	//SET PG11 OUTPUT
	Dallas_L;			//����DQ
	SysTick_DeleyuS(750);		//����750us
	Dallas_H;			//DQ=1 
	SysTick_DeleyuS(15);			//15US
}

/*******************************************************************************
* ������			:	function
* ��������		:	�ȴ�Dallas�Ļ�Ӧ
* ����			: void
* ����ֵ			: ����1:δ��⵽Dallas1�Ĵ���
							����0:����
*******************************************************************************/
uint8_t Dallas_Check(void)
{
	uint8_t retry=0;
	
	Dallas_SetIn;		//SET PG11 INPUT	 
	while(Dallas_Read	&& (retry < 200))
	{
		retry++;
		SysTick_DeleyuS(1);
	} 
	if(retry >= 200)
		return 1;
	else
		retry=0;
	while((!Dallas_Read) && (retry < 240))
	{
		retry++;
		SysTick_DeleyuS(1);
	}
	if(retry >= 240)
		return 1;
	
	return 0;
}
/*******************************************************************************
* ������			:	Dallas_ReadBit
* ��������		:	��Dallas��ȡһ��λ	- ��0&��1
							��ʱ��������Ҫ��������1us��Ȼ���ͷ����ߣ����豸����15-45us�������ߣ��������в�����
							����֮��������Ҫ1us��ʱ������
							��1-Wire���߶�ȡ1bitͬ��������Ҫ60��s��ͬʱҲҪ��֤���������Ķ��������1��s����
* ����			: void
* ����ֵ			: 1/0
* �޸�ʱ��		: ��
* �޸�����		: ��
* ����			: wegam@sina.com
*******************************************************************************/
uint8_t Dallas_ReadBit(void)
{
	uint8_t data;
	
	Dallas_SetOut;				//��Ϊ���ģʽ
	Dallas_L; 						//��������
	SysTick_DeleyuS(2);		//����1usʱ��
	Dallas_H; 						//�ͷ�����
	Dallas_SetIn;					//����Ϊ����ģʽ
	SysTick_DeleyuS(12);	//�ȴ��ӻ���Ӧ
	if(Dallas_Read)				//��ȡ����״̬
		data = 1;
	else
		data = 0;	 
	SysTick_DeleyuS(50);
	
	return data;
}
/*******************************************************************************
* ������			:	function
* ��������		:	��Dallas��ȡһ���ֽ�---�ӵ�λ��ʼ��ȡ
* ����			: void
* ����ֵ			: ����������
* �޸�ʱ��		: ��
* �޸�����		: ��
* ����			: wegam@sina.com
*******************************************************************************/
uint8_t Dallas_ReadByte(void)
{        
	uint8_t i,j,dat;
	
	dat = 0;
	for (i=1; i<=8; i++)
	{
		j = Dallas_ReadBit();		//��ȡһλ����
		dat = (j<<7)|(dat>>1);	//�ӵ�λ��ʼ��������
	}	
	return dat;
}
/*******************************************************************************
* ������			:	Dallas_WriteBit
* ��������		:	1-wire һλ��1bit��д����-д0&д1��д��������ʱ����Ҫ60-120us��д�����Ҫ����1us�ȴ�ʱ�䡣
							д����ʱ���豸�������������ͺ�15-60us���в�����дʱ����Ҫ���������ͺ�15us������������д1����д0���ߵ�ƽд1���͵�ƽд0����

							��1-Wire����д1bit������Ҫ60��s��ͬʱ��Ҫ��֤����������д������1��s ���ϵļ����
							����дλwbitΪ0��������������60��sȻ���ͷţ�д0������ɡ�
							����дλwbitΪ1���������������߲���1��15��s���ͷţ�Ȼ��ȴ�60��s��д1������ɡ�
* ����			: void
* ����ֵ			: void
* �޸�ʱ��		: ��
* �޸�����		: ��
* ����			: wegam@sina.com
*******************************************************************************/
void Dallas_WriteBit(unsigned char bit)		//1-wire һλ��1bit��д����-д0&д1
{
		// =============Write 1
		if (bit&0x01)		
		{
			Dallas_L;					//��������
			SysTick_DeleyuS(2);		//����ά����1us,��ʾдʱ��(����д0ʱ���д1ʱ��)��ʼ 
			Dallas_H;					//��������
			SysTick_DeleyuS(60);	//�ȴ��ӻ��������
		}
		// =============Write 0
		else						
		{
			Dallas_L;					//��������
			SysTick_DeleyuS(60);	//����60us���ȴ��ӻ�����
			Dallas_H;					//�ͷ�����
			SysTick_DeleyuS(2);
		}

}
/*******************************************************************************
* ������			:	function
* ��������		:	дһ���ֽڵ�Dallas---�ӵ�λ��ʼд��
* ����			: dat��Ҫд����ֽ�,
* ����ֵ			: void
* �޸�ʱ��		: ��
* �޸�����		: ��
* ����			: wegam@sina.com
*******************************************************************************/
void Dallas_WriteByte(uint8_t dat)
{             
	uint8_t j;
	uint8_t testb;
	
	Dallas_SetOut;	//SET PG11 OUTPUT;
	for (j=1; j<=8; j++)
	{
		testb = dat&0x01;
		dat = dat>>1;
		Dallas_WriteBit(testb);		//1-wire һλ��1bit��д����-д0&д1
	}
}
/*******************************************************************************
* ������			:	function
* ��������		:	��ʼ��Dallas��IO�� DQ ͬʱ���DS�Ĵ���
* ����			: void
* ����ֵ			: ����1:������
							����0:����
* �޸�ʱ��		: ��
* �޸�����		: ��
* ����			: wegam@sina.com
*******************************************************************************/
uint8_t Dallas_Init(void)
{
	GPIO_Configuration_OPP50	(Port_Dallas,	Pin_Dallas);			//��GPIO��Ӧ�ܽ�����ΪPP(����)���ģʽ������ٶ�50MHz----V20170605

	Dallas_Rest();

	return Dallas_Check();
}
/*******************************************************************************
* ������			:	function
* ��������		:	��Dallas����Rom����IDֵ
* ����			: void
* ����ֵ			: ��ʼ8λ�ǵ��߲�Ʒϵ�д��룬����48λ��Ψһ���кţ����8λ��ǰ56λ��CRCֵ
* �޸�ʱ��		: ��
* �޸�����		: ��
* ����			: wegam@sina.com
*******************************************************************************/
uint8_t Dallas_GetID(uint8_t *pBuf)
{
	uint8_t i;
	uint8_t buf[8];

	Dallas_Rest();	
	if(Dallas_Check())
		return 1;
	Dallas_WriteByte(0x33);	//read romid
	for(i=0; i<8; i++)
		buf[i] = Dallas_ReadByte();
	
	if(buf[0] != 0x01)
		return 1;
	if(CRC8_Calculate(buf, 7) != buf[7])
		return 1;

	for(i=0; i<8; i++)
		pBuf[i] = buf[i];
	
	return 0;
}









































//#ifdef USE_DALLAS
//const uint8_t g_CRC8Tab[256]=
//{
//0x00, 0x5e, 0xbc, 0xe2, 0x61, 0x3f, 0xdd, 0x83, 0xc2, 0x9c, 0x7e, 0x20, 0xa3, 0xfd, 0x1f, 0x41,
//0x9d, 0xc3, 0x21, 0x7f, 0xfc, 0xa2, 0x40, 0x1e, 0x5f, 0x01, 0xe3, 0xbd, 0x3e, 0x60, 0x82, 0xdc,
//0x23, 0x7d, 0x9f, 0xc1, 0x42, 0x1c, 0xfe, 0xa0, 0xe1, 0xbf, 0x5d, 0x03, 0x80, 0xde, 0x3c, 0x62,
//0xbe, 0xe0, 0x02, 0x5c, 0xdf, 0x81, 0x63, 0x3d, 0x7c, 0x22, 0xc0, 0x9e, 0x1d, 0x43, 0xa1, 0xff,
//0x46, 0x18, 0xfa, 0xa4, 0x27, 0x79, 0x9b, 0xc5, 0x84, 0xda, 0x38, 0x66, 0xe5, 0xbb, 0x59, 0x07,
//0xdb, 0x85, 0x67, 0x39, 0xba, 0xe4, 0x06, 0x58, 0x19, 0x47, 0xa5, 0xfb, 0x78, 0x26, 0xc4, 0x9a,
//0x65, 0x3b, 0xd9, 0x87, 0x04, 0x5a, 0xb8, 0xe6, 0xa7, 0xf9, 0x1b, 0x45, 0xc6, 0x98, 0x7a, 0x24,
//0xf8, 0xa6, 0x44, 0x1a, 0x99, 0xc7, 0x25, 0x7b, 0x3a, 0x64, 0x86, 0xd8, 0x5b, 0x05, 0xe7, 0xb9,
//0x8c, 0xd2, 0x30, 0x6e, 0xed, 0xb3, 0x51, 0x0f, 0x4e, 0x10, 0xf2, 0xac, 0x2f, 0x71, 0x93, 0xcd,
//0x11, 0x4f, 0xad, 0xf3, 0x70, 0x2e, 0xcc, 0x92, 0xd3, 0x8d, 0x6f, 0x31, 0xb2, 0xec, 0x0e, 0x50,
//0xaf, 0xf1, 0x13, 0x4d, 0xce, 0x90, 0x72, 0x2c, 0x6d, 0x33, 0xd1, 0x8f, 0x0c, 0x52, 0xb0, 0xee,
//0x32, 0x6c, 0x8e, 0xd0, 0x53, 0x0d, 0xef, 0xb1, 0xf0, 0xae, 0x4c, 0x12, 0x91, 0xcf, 0x2d, 0x73,
//0xca, 0x94, 0x76, 0x28, 0xab, 0xf5, 0x17, 0x49, 0x08, 0x56, 0xb4, 0xea, 0x69, 0x37, 0xd5, 0x8b,
//0x57, 0x09, 0xeb, 0xb5, 0x36, 0x68, 0x8a, 0xd4, 0x95, 0xcb, 0x29, 0x77, 0xf4, 0xaa, 0x48, 0x16,
//0xe9, 0xb7, 0x55, 0x0b, 0x88, 0xd6, 0x34, 0x6a, 0x2b, 0x75, 0x97, 0xc9, 0x4a, 0x14, 0xf6, 0xa8,
//0x74, 0x2a, 0xc8, 0x96, 0x15, 0x4b, 0xa9, 0xf7, 0xb6, 0xe8, 0x0a, 0x54, 0xd7, 0x89, 0x6b, 0x35
//};

////�����㷽��
//uint8_t CRC8_Calculate(uint8_t *pBuf, uint8_t len)
//{
//	uint8_t crc8=0;	//CRC8�ֽڳ�ʼ��
//	
//	//����CRC8λУ��
//	while(len){
//		crc8 = g_CRC8Tab[*pBuf^crc8];
//		pBuf++;
//		len--;
//	}

//	return(crc8);	//����CRC8У������
//}  

////��λDallas
//void Dallas_Rst(void)
//{                 
//	DALLAS_IO_OUT();	//SET PG11 OUTPUT
//	DALLAS_OUT_LOW();	//����DQ
//	Delay_us(750);		//����750us
//	DALLAS_OUT_HIGH();	//DQ=1 
//	Delay_us(15);		//15US
//}

////�ȴ�Dallas�Ļ�Ӧ
////����1:δ��⵽Dallas1�Ĵ���
////����0:����
//uint8_t Dallas_Check(void)
//{
//	uint8_t retry=0;
//	
//	DALLAS_IO_IN();		//SET PG11 INPUT	 
//	while(DALLAS_IN_STATE() && (retry < 200)){
//		retry++;
//		Delay_us(1);
//	} 
//	if(retry >= 200)
//		return 1;
//	else
//		retry=0;
//	while((!DALLAS_IN_STATE()) && (retry < 240)){
//		retry++;
//		Delay_us(1);
//	}
//	if(retry >= 240)
//		return 1;
//	
//	return 0;
//}

////��Dallas��ȡһ��λ
////����ֵ��1/0
//uint8_t Dallas_ReadBit(void)
//{
//	uint8_t data;
//	
//	DALLAS_IO_OUT();	//SET PG11 OUTPUT
//	DALLAS_OUT_LOW(); 
//	Delay_us(2);
//	DALLAS_OUT_HIGH(); 
//	DALLAS_IO_IN();		//SET PG11 INPUT
//	Delay_us(12);
//	if(DALLAS_IN_STATE())
//		data = 1;
//	else
//		data = 0;	 
//	Delay_us(50);
//	
//	return data;
//}

////��Dallas��ȡһ���ֽ�
////����ֵ������������
//uint8_t Dallas_ReadByte(void)
//{        
//	uint8_t i,j,dat;
//	
//	dat = 0;
//	for (i=1; i<=8; i++){
//		j = Dallas_ReadBit();
//		dat = (j<<7)|(dat>>1);
//	}
//	
//	return dat;
//}

////дһ���ֽڵ�Dallas
////dat��Ҫд����ֽ�
//void Dallas_WriteByte(uint8_t dat)
//{             
//	uint8_t j;
//	uint8_t testb;
//	
//	DALLAS_IO_OUT();	//SET PG11 OUTPUT;
//	for (j=1; j<=8; j++){
//		testb = dat&0x01;
//		dat = dat>>1;
//		if (testb){
//			DALLAS_OUT_LOW();	// Write 1
//			Delay_us(2);
//			DALLAS_OUT_HIGH();
//			Delay_us(60);
//		}else{
//			DALLAS_OUT_LOW();	// Write 0
//			Delay_us(60);
//			DALLAS_OUT_HIGH();
//			Delay_us(2);
//		}
//	}
//}

////��ʼ��Dallas��IO�� DQ ͬʱ���DS�Ĵ���
////����1:������
////����0:����    	 
//uint8_t Dallas_Init(void)
//{
//	GPIO_InitTypeDef  GPIO_InitStructure;

//	GPIO_SetBits(DALLAS_GPIOx, DALLAS_PIN);
//	GPIO_InitStructure.GPIO_Pin = DALLAS_PIN;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		  
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(DALLAS_GPIOx, &GPIO_InitStructure);

//	Dallas_Rst();

//	return Dallas_Check();
//}

////��Dallas����Rom����IDֵ
////���ݣ���ʼ8λ�ǵ��߲�Ʒϵ�д��룬����48λ��Ψһ���кţ����8λ��ǰ56λ��CRCֵ
//uint8_t Dallas_GetID(uint8_t *pBuf)
//{
//	uint8_t i;
//	uint8_t buf[8];

//	Dallas_Rst();	
//	if(Dallas_Check())
//		return 1;
//	Dallas_WriteByte(0x33);	//read romid
//	for(i=0; i<8; i++)
//		buf[i] = Dallas_ReadByte();
//	
//	if(buf[0] != 0x01)
//		return 1;
//	if(CRC8_Calculate(buf, 7) != buf[7])
//		return 1;

//	for(i=0; i<8; i++)
//		pBuf[i] = buf[i];
//	
//	return 0;
//}
//#endif

