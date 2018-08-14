#include "CS5530.H"

#include "STM32_GPIO.H"
#include "STM32_SYSTICK.H"

#include 	"TOOL.H"

#include "stdint.h"
#include "stdlib.h"



//#define CS5530_CS_LOW()			((pInfo->pGPIOxCS)->BRR = pInfo->pinCS)
//#define CS5530_CS_HIGH()		((pInfo->pGPIOxCS)->BSRR = pInfo->pinCS)
//#define CS5530_SDI_LOW()		((g_CS5530PinInfo->pGPIOxSDI)->BRR = g_CS5530PinInfo->pinSDI)
//#define CS5530_SDI_HIGH()		((g_CS5530PinInfo->pGPIOxSDI)->BSRR = g_CS5530PinInfo->pinSDI)
//#define CS5530_SDO_STATE()	((g_CS5530PinInfo->pGPIOxSDO)->IDR & g_CS5530PinInfo->pinSDO)
//#define CS5530_SCLK_LOW()		((g_CS5530PinInfo->pGPIOxSCLK)->BRR = g_CS5530PinInfo->pinSCLK)
//#define CS5530_SCLK_HIGH()	((g_CS5530PinInfo->pGPIOxSCLK)->BSRR = g_CS5530PinInfo->pinSCLK)
unsigned long CS5530_Status=0x00;







/*******************************************************************************
* ������			:	function
* ��������		:	��������˵�� 
* ����			: void
* ����ֵ			: void
*******************************************************************************/
void CS5530_Delay(u32 time)
{
	while(time--);
//	SysTick_DeleyuS(2);				//SysTick��ʱnmS
}

/*******************************************************************************
* ������			:	function
* ��������		:	���ذ�
* ����			: void
* ����ֵ			: void
*******************************************************************************/
u8 CS5530_SDO_STATE(CS5530Def *pInfo)
{
	return(GPIO_ReadInputDataBit(pInfo->Port.SDO_PORT, pInfo->Port.SDO_Pin));
}
/*******************************************************************************
* ������			:	function
* ��������		:	��������˵�� 
* ����			: void
* ����ֵ			: void
*******************************************************************************/
void CS5530_Initialize(CS5530Def *pInfo)
{
	unsigned long *p=(unsigned long*)&(pInfo->Flag);		//��ȡ���ݽṹ���ַ,�Ա㽫��ȡ�����ݱ���
	
	GPIO_Configuration_OPP50	(pInfo->Port.CS_PORT,		pInfo->Port.CS_Pin);			//��GPIO��Ӧ�ܽ�����ΪPP(����)���ģʽ������ٶ�2MHz----V20170605
	GPIO_Configuration_OPP50	(pInfo->Port.SDI_PORT,	pInfo->Port.SDI_Pin);			//��GPIO��Ӧ�ܽ�����ΪPP(����)���ģʽ������ٶ�2MHz----V20170605
	GPIO_Configuration_OPP50	(pInfo->Port.SCLK_PORT,	pInfo->Port.SCLK_Pin);		//��GPIO��Ӧ�ܽ�����ΪPP(����)���ģʽ������ٶ�2MHz----V20170605
	GPIO_Configuration_IPU		(pInfo->Port.SDO_PORT,	pInfo->Port.SDO_Pin);			//��GPIO��Ӧ�ܽ�����Ϊ��������ģʽ----V20170605
	
	CS5530_PowerUp(pInfo);		//CS5530�ϵ缰��ʼ��
	
	//���ݳ�ʼ��
	*p	=	0;		//pInfo->Flag��ʼ��
//	pInfo->Data.Origin	=	0;	//ԭ��
//	pInfo->Data.WeighPie=	0;	//����	
}
/*******************************************************************************
* ������			:	function
* ��������		:	���ذ�
* ����			: void
* ����ֵ			: void
*******************************************************************************/
void CS5530_WriteOneByte(CS5530Def *pInfo, u8 dat)
{
	u8 i;
	u16 delayTime	=	1000;
	pInfo->Port.SCLK_PORT->BRR    = pInfo->Port.SCLK_Pin;   //SCLK==0
	SysTick_DeleyuS(100);				//SysTick��ʱnuS
	for(i=0; i<8; i++)
	{
		if((dat&0x80) != 0)
      pInfo->Port.SDI_PORT->BSRR  = pInfo->Port.SDI_Pin;    //SDI==1
		else
      pInfo->Port.SDI_PORT->BRR   = pInfo->Port.SDI_Pin;    //SDI==0
		
		SysTick_DeleyuS(200);				//SysTick��ʱnuS
    pInfo->Port.SCLK_PORT->BSRR   = pInfo->Port.SCLK_Pin;   //SCLK==1
		SysTick_DeleyuS(200);				//SysTick��ʱnuS
    pInfo->Port.SCLK_PORT->BRR    = pInfo->Port.SCLK_Pin;   //SCLK==0
		dat <<= 1;
	}
}

/*******************************************************************************
* ������			:	function
* ��������		:	��������˵��
* ����			: void
* ����ֵ			: void
*******************************************************************************/
void CS5530_WriteCommand(CS5530Def *pInfo,u8 command)
{
	CS5530_WriteOneByte(pInfo,command);
}
/*******************************************************************************
* ������			:	function
* ��������		:	��������˵�� 
* ����			: void
* ����ֵ			: void
*******************************************************************************/
void CS5530_WriteRegister(CS5530Def *pInfo, u8 command,u32 setData)
{
//	unsigned long temp=0xFFFFFFFF;
	CS5530_WriteOneByte(pInfo, command);
	CS5530_WriteOneByte(pInfo, (uint8_t)(setData>>24));
	CS5530_WriteOneByte(pInfo, (uint8_t)(setData>>16));
	CS5530_WriteOneByte(pInfo, (uint8_t)(setData>>8));
	CS5530_WriteOneByte(pInfo, (uint8_t)(setData>>0));
}

/*******************************************************************************
* ������			:	function
* ��������		:	���ذ�
* ����			: void
* ����ֵ			: void
*******************************************************************************/
unsigned char CS5530_ReadOneByte(CS5530Def *pInfo)
{
	uint8_t i;
	uint8_t reValue=0;
  pInfo->Port.SDI_PORT->BRR    = pInfo->Port.SDI_Pin;       //SDI==0
	SysTick_DeleyuS(100);				//SysTick��ʱnuS
	for(i=0; i<8; i++)
	{	
		SysTick_DeleyuS(100);				//SysTick��ʱnuS
    pInfo->Port.SCLK_PORT->BSRR   = pInfo->Port.SCLK_Pin;   //SCLK==1
		reValue <<= 1;
		SysTick_DeleyuS(100);				//SysTick��ʱnuS
		if(CS5530_SDO_STATE(pInfo))
			reValue++;
		SysTick_DeleyuS(100);				//SysTick��ʱnuS
    pInfo->Port.SCLK_PORT->BRR    = pInfo->Port.SCLK_Pin;   //SCLK==0		
	}
	SysTick_DeleyuS(100);				//SysTick��ʱnuS

	return reValue;
}
/*******************************************************************************
* ������			:	function
* ��������		:	��������˵�� 
* ����			: void
* ����ֵ			: void
*******************************************************************************/
u32 CS5530_GetADData(CS5530Def *pInfo)
{
	u32 reValue=0;	

//		CS5530_WriteOneByte(pInfo, CS5530_CONTINUOUS_ON);		///*��������ת��ģʽ*/
		pInfo->Port.SDI_PORT->BRR    = pInfo->Port.SDI_Pin;       //SDI==0
		CS5530_ReadOneByte(pInfo);
		reValue = ((u32)CS5530_ReadOneByte(pInfo)<<24)
						+((uint32_t)CS5530_ReadOneByte(pInfo)<<16)
						+((uint32_t)CS5530_ReadOneByte(pInfo)<<8)
						+(uint32_t)CS5530_ReadOneByte(pInfo);
	return reValue;
}
/*******************************************************************************
* ������			:	function
* ��������		:	��������˵�� 
* ����			: void
* ����ֵ			: void
*******************************************************************************/
u32 CS5530_ReadRegister(CS5530Def *pInfo, u8 command)
{
	volatile unsigned long temp=0x00;
	
	CS5530_WriteOneByte(pInfo, command);
	temp = (CS5530_ReadOneByte(pInfo)<<24)
				+(CS5530_ReadOneByte(pInfo)<<16)
				+(CS5530_ReadOneByte(pInfo)<<8)
				+CS5530_ReadOneByte(pInfo);
	
	return temp;
}
/*******************************************************************************
* ������			:	function
* ��������		:	��������˵�� 
* ����			: void
* ����ֵ			: void
*******************************************************************************/
void CS5530_ClearBuf(CS5530Def *pInfo)
{
//	uint8_t i;

//	__disable_irq();
//	pInfo->continuousOFCount = 0;
//	for(i=0; i<pInfo->dataBufSize; i++)
//		pInfo->pDataBuf[i] = 0xFFFFFFFF;
//	pInfo->dataPtr = 0;
//	__enable_irq();
}

/*******************************************************************************
* ������			:	CS5530_PowerUp
* ��������		:	CS5530�ϵ缰��ʼ��
* ����			: void
* ����ֵ			: void
*******************************************************************************/
void CS5530_PowerUp(CS5530Def *pInfo)
{
	u8 num=0;
	u16 retry	=	0;	//����

  pInfo->Port.CS_PORT->BRR    = pInfo->Port.CS_Pin;       //CS==0
	SysTick_DeleymS(200);				//SysTick��ʱnmS
	//1)��ϵͳ����ADC���͸�λ����
	//1.1��************д��15��SYNC1����(0XFF)
	for(num=0;num<15;num++)
	{
		CS5530_WriteOneByte(pInfo, CS5530_SYNC1);
		SysTick_DeleymS(10);				//SysTick��ʱnmS
	}
	SysTick_DeleymS(50);				//SysTick��ʱnmS
	//1.2��************д��1��SYNC0���0XFE��
	CS5530_WriteOneByte(pInfo, CS5530_SYNC0);
	SysTick_DeleymS(50);				//SysTick��ʱnmS
	
	//2)д���üĴ��� д��CS5530��λ���� RSΪ1
	CS5530_WriteRegister(pInfo,CS5530_WRITE_CONFIG,CS5530_CONF_SYSTEM_RESET);
	SysTick_DeleymS(50);				//SysTick��ʱnmS
	CS5530_WriteOneByte(pInfo, CS5530_NULL_BYTE);
	SysTick_DeleymS(50);				//SysTick��ʱnmS
	CS5530_WriteRegister(pInfo,CS5530_WRITE_CONFIG,CS5530_CONF_NORMAL_MODE);
	SysTick_DeleymS(50);				//SysTick��ʱnmS
	
	//���RV�Ƿ�Ϊ1(��λ�� ����Ϊ1),�����Ϊ1�ټ�����ȡ���üĴ���		
	do
	{ 
		CS5530_Status = CS5530_ReadRegister(pInfo, CS5530_READ_CONFIG);
		SysTick_DeleymS(50);				//SysTick��ʱnmS
	}
	while(((CS5530_Status & CS5530_CONF_RESET_STATUS) != 0)&&(retry++<=100));
	
	if(retry>=100)
	{
		return;
	}
	
//	CS5530_Status=0x1FFFFFF;
	
	CS5530_Status=0x1000000;
	
//	CS5530_Status=0x3F000000;
//	
//	CS5530_Status=0x0FFFFFF;
//	
//	CS5530_Status=0x7FFFFFF;
//	
//	CS5530_Status=0x1FFFFFF;
	
//	CS5530_Status=0x1000000;		//1200
	
	CS5530_Status=0x0800000;		//600
	
	CS5530_Status=0x0400000;		//300
	
	CS5530_Status=0x0200000;		//150
	
	CS5530_Status=0x01000000;		//1200
	
	CS5530_WriteRegister(pInfo,CS5530_WRITE_GAIN,CS5530_Status);			//����Ĵ���	
		
//	CS5530_Status=0xFFFFFFFF;
	CS5530_Status=CS5530_ReadRegister(pInfo,CS5530_READ_CONFIG);			//���üĴ���
//	CS5530_Status=0xFFFFFFFF;
	CS5530_Status=CS5530_ReadRegister(pInfo,CS5530_READ_OFFSET);			//ƫ�ƼĴ���
//	CS5530_Status=0xFFFFFFFF;
	CS5530_Status=CS5530_ReadRegister(pInfo,CS5530_READ_GAIN);				//����Ĵ���
	
	CS5530_Status=0x00;
	
//	CS5530_Status=CS5530_Status|0x82000;																	//6.25sps
	
	CS5530_Status=CS5530_Status|0x2000;																	//7.5sps
	
//	CS5530_Status=CS5530_Status|0x1800;																	//15sps
	
//	CS5530_Status=CS5530_Status|0x0800;																	//60sps
	
//	CS5530_Status=CS5530_Status|0x4000;																	//3840sps
	
//	CS5530_Status=CS5530_Status|0x6000;																	//240sps

	CS5530_Status=CS5530_Status&(~CS5530_CONF_SHORT_INPUTS);						//��������,ͨ�����벻�̽�
	
//	CS5530_Status=CS5530_Status|CS5530_CONF_SHORT_INPUTS;								//����Ϊ�����·

	CS5530_WriteRegister(pInfo,CS5530_WRITE_CONFIG,CS5530_Status);		//���üĴ���
	
	CS5530_WriteCommand(pInfo,CS5530_SYSTEM_OFFSET_CAL);							//ִ��ƫ��У׼
	
	CS5530_WriteCommand(pInfo,CS5530_SYSTEM_GAIN_CAL);								//ִ��ϵͳ����У׼

	CS5530_Status=CS5530_ReadRegister(pInfo,CS5530_READ_GAIN);				//����Ĵ���
	
//	CS5530_WriteRegister(pInfo,CS5530_WRITE_GAIN,0x00FFFFFF);						//д����Ĵ���
	
//	CS5530_WriteRegister(Pinfo,CS5530_WRITE_GAIN,0x00100000);					//д����Ĵ���
	
	CS5530_WriteCommand(pInfo,CS5530_START_CONTINUOUS);									//ִ������ת��
	
//	CS5530_WriteCommand(pInfo,CS5530_START_SINGLE);									//ִ�е���ת��
	
	CS5530_Delay(500);
	pInfo->Port.CS_PORT->BSRR    = pInfo->Port.CS_Pin;       //CS==1
}
/*******************************************************************************
* ������			:	CS5530_PowerUp
* ��������		:	CS5530�ϵ缰��ʼ��
* ����			: void
* ����ֵ			: void
*******************************************************************************/
void CS5530_PowerDown(CS5530Def *pInfo)
{
	u8 num=0;
	u16 retry	=	0;	//����
	pInfo->Port.CS_PORT->BRR    = pInfo->Port.CS_Pin;       //CS==0
	SysTick_DeleymS(200);				//SysTick��ʱnmS
	//1)��ϵͳ����ADC���͸�λ����
	//1.1��************д��15��SYNC1����(0XFF)
	for(num=0;num<15;num++)
	{
		CS5530_WriteOneByte(pInfo, CS5530_SYNC1);
		SysTick_DeleymS(5);				//SysTick��ʱnmS
	}
	SysTick_DeleymS(50);				//SysTick��ʱnmS
	//1.2��************д��1��SYNC0���0XFE��
	CS5530_WriteOneByte(pInfo, CS5530_SYNC0);
	SysTick_DeleymS(50);				//SysTick��ʱnmS
	
	//2)д���üĴ��� д��CS5530��λ���� RSΪ1
	CS5530_WriteRegister(pInfo,CS5530_WRITE_CONFIG,CS5530_CONF_SYSTEM_RESET);
	SysTick_DeleymS(50);				//SysTick��ʱnmS
	CS5530_WriteOneByte(pInfo, CS5530_NULL_BYTE);
	SysTick_DeleymS(50);				//SysTick��ʱnmS
	CS5530_WriteRegister(pInfo,CS5530_WRITE_CONFIG,CS5530_CONF_NORMAL_MODE);
	SysTick_DeleymS(50);				//SysTick��ʱnmS
	
	//���RV�Ƿ�Ϊ1(��λ�� ����Ϊ1),�����Ϊ1�ټ�����ȡ���üĴ���		
	do
	{ 
		CS5530_Status = CS5530_ReadRegister(pInfo, CS5530_READ_CONFIG);
		SysTick_DeleymS(50);				//SysTick��ʱnmS
	}
	while(((CS5530_Status & CS5530_CONF_RESET_STATUS) != 0)&&(retry++<=100));
	
	if(retry>=100)
	{
		return;
	}
	
	CS5530_WriteRegister(pInfo,CS5530_WRITE_CONFIG,CS5530_CONF_POWER_SAVE_MODE);
	
	CS5530_Delay(500);
	pInfo->Port.CS_PORT->BSRR    = pInfo->Port.CS_Pin;       //CS==1
}
/*******************************************************************************
* ������			:	CS5530_PowerUp
* ��������		:	CS5530�ϵ缰��ʼ��
* ����			: void
* ����ֵ			: void
*******************************************************************************/
void CS5530_PowerUpBac(CS5530Def *pInfo)
{
	u8 num=0;
	u16 retry	=	0;	//����
	pInfo->Port.CS_PORT->BSRR    = pInfo->Port.CS_Pin;       //CS==1
	SysTick_DeleymS(200);				//SysTick��ʱnmS
	//1)��ϵͳ����ADC���͸�λ����
	//1.1��************д��15��SYNC1����(0XFF)
	for(num=0;num<15;num++)
	{
		CS5530_WriteOneByte(pInfo, CS5530_SYNC1);
		SysTick_DeleymS(5);				//SysTick��ʱnmS
	}
	SysTick_DeleymS(50);				//SysTick��ʱnmS
	//1.2��************д��1��SYNC0���0XFE��
	CS5530_WriteOneByte(pInfo, CS5530_SYNC0);
	SysTick_DeleymS(50);				//SysTick��ʱnmS
	
	//2)д���üĴ��� д��CS5530��λ���� RSΪ1
	CS5530_WriteRegister(pInfo,CS5530_WRITE_CONFIG,CS5530_CONF_SYSTEM_RESET);
	SysTick_DeleymS(50);				//SysTick��ʱnmS
	CS5530_WriteOneByte(pInfo, CS5530_NULL_BYTE);
	SysTick_DeleymS(50);				//SysTick��ʱnmS
	CS5530_WriteRegister(pInfo,CS5530_WRITE_CONFIG,CS5530_CONF_NORMAL_MODE);
	SysTick_DeleymS(50);				//SysTick��ʱnmS
	
	//���RV�Ƿ�Ϊ1(��λ�� ����Ϊ1),�����Ϊ1�ټ�����ȡ���üĴ���		
		do
		{ 
			CS5530_Status = CS5530_ReadRegister(pInfo, CS5530_READ_CONFIG);
			SysTick_DeleymS(50);				//SysTick��ʱnmS
		}
		while(((CS5530_Status & CS5530_CONF_RESET_STATUS) != 0)&&(retry++<=100));
		
		if(retry>=100)
		{
			return;
		}
	
//	CS5530_Delay(50);		
//	CS5530_WriteRegister(Pinfo,CS5530_WRITE_CONFIG,CS5530_CONF_NORMAL_MODE);
//	CS5530_Delay(50);
	
//	while(CS5530_ReadRegister(Pinfo,CS5530_READ_CONFIG)==0x00000000);
//	while(CS5530_ReadRegister(Pinfo,CS5530_READ_OFFSET)==0x00000000);
//	while(CS5530_ReadRegister(Pinfo,CS5530_READ_GAIN)==0x01000000);
		
//	CS5530_Status=0xFFFFFFFF;
	CS5530_Status=CS5530_ReadRegister(pInfo,CS5530_READ_CONFIG);			//���üĴ���
//	CS5530_Status=0xFFFFFFFF;
	CS5530_Status=CS5530_ReadRegister(pInfo,CS5530_READ_OFFSET);			//ƫ�ƼĴ���
//	CS5530_Status=0xFFFFFFFF;
	CS5530_Status=CS5530_ReadRegister(pInfo,CS5530_READ_GAIN);				//����Ĵ���
		
		
//	CS5530_Status=0xFFFFFFFF;
		
	CS5530_Status=CS5530_Status|CS5530_CONF_SHORT_INPUTS;								//����Ϊ�����·

	CS5530_Status=CS5530_ReadRegister(pInfo,CS5530_READ_CONFIG);				//����Ĵ���

//	CS5530_Status=CS5530_Status|0x82000;																	//6.25sps
	
	CS5530_Status=CS5530_Status|0x2000;																	//7.5sps
	
//	CS5530_Status=CS5530_Status|0x1800;																	//15sps
	
//	CS5530_Status=CS5530_Status|0x0800;																	//60sps
	
//	CS5530_Status=CS5530_Status|0x4000;																	//3840sps
	
//	CS5530_Status=CS5530_Status|0x6000;																	//240sps
	
	CS5530_WriteCommand(pInfo,CS5530_SYSTEM_OFFSET_CAL);								//ִ��ƫ��У׼
	
	CS5530_WriteCommand(pInfo,CS5530_SYSTEM_GAIN_CAL);									//ִ��ϵͳ����У׼	
	
//	CS5530_Status=CS5530_Status|CS5530_CONF_UNIPOLAR_MODE;							//����ѡ�񵥼���ģʽ

	CS5530_Status=CS5530_Status|CS5530_CONF_BIPOLAR_MODE;									//����ѡ��˫����ģʽ
	
	CS5530_WriteRegister(pInfo,CS5530_WRITE_CONFIG,CS5530_Status);			//���üĴ���
	
	CS5530_Status=CS5530_ReadRegister(pInfo,CS5530_READ_CONFIG);				//���üĴ���
	
//	CS5530_Status=CS5530_Status&(~CS5530_CONF_SHORT_INPUTS);						//��������,ͨ�����벻�̽�

	CS5530_Status=CS5530_Status|CS5530_CONF_SHORT_INPUTS;								//����Ϊ�����·
	
	CS5530_WriteRegister(pInfo,CS5530_WRITE_CONFIG,CS5530_Status);			//д���üĴ���
	
//	CS5530_WriteRegister(pInfo,CS5530_WRITE_GAIN,0x00FFFFFF);						//д����Ĵ���
	
	CS5530_WriteRegister(pInfo,CS5530_WRITE_GAIN,0x01000000);					//д����Ĵ���
	
	CS5530_WriteCommand(pInfo,CS5530_START_CONTINUOUS);									//ִ������ת��
	
	CS5530_Delay(500);
	pInfo->Port.CS_PORT->BRR    = pInfo->Port.CS_Pin;       //CS==0
}
/*******************************************************************************
*������			:	CS5530_ReadData
*��������		:	��ȡADֵ���������0xFFFFFFFF,��δ��ȡ��24λADֵ
*����				: 
*����ֵ			:	��
*******************************************************************************/
u32	CS5530_ReadData(CS5530Def *pInfo)
{
	u32 ADC_Value=0xFFFFFFFF;
	
	pInfo->Port.CS_PORT->BRR    = pInfo->Port.CS_Pin;       //CS==0
	SysTick_DeleyuS(100);				//SysTick��ʱnuS
	if(CS5530_SDO_STATE(pInfo) == 0)
	{			
		ADC_Value=CS5530_GetADData(pInfo)>>8;		//��ȡ24λԭ��ֵ---����4���ֽڣ���8λΪ��ֵ
	}
	pInfo->Port.CS_PORT->BSRR    = pInfo->Port.CS_Pin;       //CS==1
	return ADC_Value;
}
/**********************************************************
������:��ֵ�˲����
����:��ȡn�βɼ�������,ȥ����m��,ȥ����m��,Ȼ�������м��(n-2*m)������,
		�����ݲ�ֵ�Ƿ�����Ҫ��,�������Ҫ��,��ƽ��ֵ���
����:
	pInfo:��һ·����;
	pDataBuf:��ʱ���ݻ���,��Ҫ���ú����ṩһ����pInfo->pDataBuf��ָ������ݻ�����
				�ߴ�һ����С����ʱ���ݻ���,������������;
	dataMaxDiff:�������Ĳ�ֵ;
Length:��������鳤��
���:�м�(n-2*m)�����ݵ�ƽ��ֵ,�����Ϊ0xFFFFFFFF,������������Ч,�����Ϊ0xFF000000,�������������
*********************************************************/
unsigned long CS5530_GetWeightUseMedinaFilter(CS5530Def *pInfo)
{
//	unsigned long 	weighMax=0;
//	unsigned long 	weighMid=0;
//	unsigned long 	weighMin=0;
	unsigned long 	weighAve=0;		//ƽ��ֵ
	unsigned long 	weighVar=0;		//����
	unsigned short 	Length	=	0;
	unsigned long		*Buffer		=	NULL;			//���ݻ���	

	Buffer	=	&(pInfo->Data.Buffer[0]);
	Length	=	pInfo->Data.Num;
	
	//�������ֵ����Сֵ
//	weighMid	=	GetMinLong(Buffer,Length);		//��ȡunsigned long����Сֵ
//	weighMax	=	GetMaxLong(Buffer,Length);		//��ȡunsigned long�����ֵ	
	//��ƽ��ֵ
	weighAve	=	GetAveLong(Buffer,Length);		//��ȡunsigned long��ƽ��ֵ	
	//����(��׼��)����
	weighVar	=	GetVarLong(Buffer,Length);		//��ȡunsigned long����
	weighVar	=	weighVar/Length;
	
	if(weighVar<WeighVarMax)		//����̫����ɢ�Բ������Ч
	{
		return weighAve;		
	}
	else
	{
		return 0xFFFFFFFF;
	}
//	return weighVar;
}
/*******************************************************************************
* ������			:	function
* ��������		:	��ȡ�ȶ���ADֵ 
* ����			: void
* ����ֵ			: void
* �޸�ʱ��		: ��
* �޸�����		: ��
* ����			: wegam@sina.com
*******************************************************************************/
unsigned long CS5530_GetWeigh(CS5530Def *pInfo)
{
	if(pInfo->Data.Time++>=5)	//5Hz 0.2S
	{
		unsigned long		ADC	=	0;
		unsigned short	Num			=	0;			//������		
		unsigned short	*Quantity	=	NULL;			//����	
		unsigned long		*WeighFilt	=	NULL;		//�˲���ADֵ	
		unsigned long		*Origin		=	NULL;			//ԭ��ֵ
		unsigned long		*Buffer		=	NULL;			//���ݻ���
		
		Num	=	pInfo->Data.Num;
		WeighFilt	=	&(pInfo->Data.WeighFilt);
		Quantity	=	&(pInfo->Data.Quantity);		
		Origin	=	&(pInfo->Data.Origin);
		Buffer	=	&(pInfo->Data.Buffer[0]);
		
		pInfo->Data.Time	=	0;
		
		ADC	=	CS5530_ReadData(pInfo);	//��ȡADֵ���������0xFFFFFFFF,��δ��ȡ��24λADֵ
		
		pInfo->Data.WeighLive	=	ADC;
		
		if(ADC	!=	0xFFFFFFFF)
		{
			unsigned long	ADC_CMP	=	0;			
			Buffer[Num]	=	ADC;			
			if(Num>0)		//�ж�����ADֵ֮ǰ��ƫ��
			{
				if(Buffer[Num]>Buffer[Num-1])
				{
					ADC_CMP	=	Buffer[Num]-Buffer[Num-1];
				}
				else
				{
					ADC_CMP	=	Buffer[Num-1]-Buffer[Num];
				}
				if(ADC_CMP>WeighCmpMax)	//�������ݲ�̫��ȡ����Ч
				{
					*WeighFilt	=	0xFFFFFFFF;
					pInfo->Data.Num	=	0;
					return 0;						//�˳��˺���
				}				
			}
			pInfo->Data.Num++;
			if(Num>=DataNum-1)		//��������
			{
				*WeighFilt	=	CS5530_GetWeightUseMedinaFilter(pInfo);
				pInfo->Data.Num	=	0;
				return *WeighFilt;
			}
		}
		else
		{
//			*WeighFilt	=	0xFFFFFFFF;
			return 0xFFFFFFFF;
		}
	}	
	return 0xFFFFFFFF;
}
/*******************************************************************************
* ������			:	function
* ��������		:	�궨/��ȡ����
* ����			: void
* ����ֵ			: void
* �޸�ʱ��		: ��
* �޸�����		: ��
* ����			: wegam@sina.com
*******************************************************************************/
unsigned long CS5530_GetCalib(CS5530Def *pInfo)
{
	if(pInfo->Flag.GetCali)	//��ȡԭ����
	{
		if((pInfo->Data.WeighFilt!= 0xFFFFFFFF)&&(pInfo->Data.Origin!= 0))
		{
			unsigned short	Quq;
			unsigned long AD1,AD2;
			
			Quq	=	pInfo->Data.Quantity;		//����
			AD1	=	pInfo->Data.Origin;			//ԭ��ֵ
			AD2	=	pInfo->Data.WeighFilt;	//�˲���ADֵ	
			if((Quq>0)&&(AD2>AD1))
			{
				pInfo->Flag.GetCali		=	0;
				pInfo->Data.WeighPie	=	(AD2-AD1)/Quq;
				return pInfo->Data.WeighPie;
			}
		}
	}
	return 0xFFFFFFFF;
}
/*******************************************************************************
* ������			:	function
* ��������		:	��ȡԭ��ֵ 
* ����			: void
* ����ֵ			: void
* �޸�ʱ��		: ��
* �޸�����		: ��
* ����			: wegam@sina.com
*******************************************************************************/
unsigned long CS5530_GetOrigin(CS5530Def *pInfo)
{
	if(pInfo->Flag.GetOri)	//��ȡԭ����
	{
		if((pInfo->Data.WeighFilt!= 0xFFFFFFFF)&&(pInfo->Data.WeighFilt!= 0))
		{
			pInfo->Flag.GetOri	=	0;
			pInfo->Data.Origin	=	pInfo->Data.WeighFilt;
			return pInfo->Data.Origin;
		}
	}
	return 0xFFFFFFFF;
}
/*******************************************************************************
* ������			:	CS5530_GetQuant
* ��������		:	��ȡ���� 
* ����			: void
* ����ֵ			: void
* �޸�ʱ��		: ��
* �޸�����		: ��
* ����			: wegam@sina.com
*******************************************************************************/
unsigned long CS5530_GetQuant(CS5530Def *pInfo)
{
	if(pInfo->Flag.GetQua)	//��ȡԭ����
	{
		if((pInfo->Data.WeighFilt!= 0xFFFFFFFF)&&(pInfo->Data.Origin!= 0))
		{
			unsigned short	Quq;
			unsigned long AD1,AD2,AD3;
			
			Quq	=	pInfo->Data.Quantity;
			AD1	=	pInfo->Data.Origin;
			AD2	=	pInfo->Data.WeighFilt;
			AD3	=	pInfo->Data.WeighPie;
			if((Quq>0)&&(AD1>0)&&((AD2+AD3/5)>=AD1)&&(AD3>0))
			{
				pInfo->Flag.GetQua		=	0;
				pInfo->Data.Quantity	=	(AD2-AD1+(AD3)/5)/AD3;
				return pInfo->Data.Quantity;
			}
		}
	}
	return 0xFFFFFFFF;
}
/*******************************************************************************
* ������			:	CS5530_Clear
* ��������		:	�����������б�־������
* ����			: void
* ����ֵ			: void
* �޸�ʱ��		: ��
* �޸�����		: ��
* ����			: wegam@sina.com
*******************************************************************************/
void CS5530_Clear(CS5530Def *pInfo)
{
//	memset(&(pInfo->Data),0xFF,(sizeof(pInfo->Data))/sizeof(char));
//	memset(&(pInfo->Flag),0xFF,(sizeof(pInfo->Flag))/sizeof(char));
	
	memset(&(pInfo->Data),0x00,(sizeof(pInfo->Data))/sizeof(char));
	memset(&(pInfo->Flag),0x00,(sizeof(pInfo->Flag))/sizeof(char));
}
/*******************************************************************************
* ������			:	function
* ��������		:	��ȡԭ��ֵ 
* ����			: void
* ����ֵ			: void
* �޸�ʱ��		: ��
* �޸�����		: ��
* ����			: wegam@sina.com
*******************************************************************************/
void CS5530_Process(CS5530Def *pInfo)
{
	CS5530_GetWeigh(pInfo);	
	CS5530_GetOrigin(pInfo);
	CS5530_GetCalib(pInfo);
	CS5530_GetQuant(pInfo);
//	pInfo->Flag.GetQua		=	1;
}



/************************************************************************************/
