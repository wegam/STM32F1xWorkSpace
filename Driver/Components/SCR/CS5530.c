#include "CS5530.H"

#include "STM32_GPIO.H"
#include "STM32_SYSTICK.H"

#include 	"TOOL.H"

#include "stdint.h"
#include "stdlib.h"

CS5530PortDef*  CS5530Info  = NULL;

#define CS5530_CS_LOW			((CS5530Info->CS_PORT)->BRR = CS5530Info->CS_Pin)
#define CS5530_CS_HIGH		((CS5530Info->CS_PORT)->BSRR = CS5530Info->CS_Pin)
#define CS5530_SDI_LOW		((CS5530Info->SDI_PORT)->BRR = CS5530Info->SDI_Pin)
#define CS5530_SDI_HIGH		((CS5530Info->SDI_PORT)->BSRR = CS5530Info->SDI_Pin)
#define CS5530_SDO_Read	  ((CS5530Info->SDO_PORT)->IDR & CS5530Info->SDO_Pin)
#define CS5530_SCLK_LOW		((CS5530Info->SCLK_PORT)->BRR = CS5530Info->SCLK_Pin)
#define CS5530_SCLK_HIGH	((CS5530Info->SCLK_PORT)->BSRR = CS5530Info->SCLK_Pin)


#define	CS5530SetH(n)	    CS5530_##n##_HIGH
#define	CS5530SetL(n)	    CS5530_##n##_LOW
//#define	CS5530SetH(dev)	    ((CS5530Info->CS_PORT)->BSRR = CS5530Info->CS_Pin)
//#define	CS5530SetL(dev)	    ((CS5530Info->CS_PORT)->BRR = CS5530Info->CS_Pin)
#define	CS5530GetBit	    CS5530_SDO_Read

unsigned long CS5530_Status=0x00;







/*******************************************************************************
* ������			:	function
* ��������		:	��������˵�� 
* ����			: void
* ����ֵ			: void
*******************************************************************************/
void CS5530_Delayus(u32 time)
{
	SysTick_DeleyuS(time);				//SysTick��ʱnmS
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
	CS5530Info  = &pInfo->Port;
	
	GPIO_Configuration_OPP50	(pInfo->Port.CS_PORT,		pInfo->Port.CS_Pin);			//��GPIO��Ӧ�ܽ�����ΪPP(����)���ģʽ������ٶ�2MHz----V20170605
	GPIO_Configuration_OPP50	(pInfo->Port.SDI_PORT,	pInfo->Port.SDI_Pin);			//��GPIO��Ӧ�ܽ�����ΪPP(����)���ģʽ������ٶ�2MHz----V20170605
	GPIO_Configuration_OPP50	(pInfo->Port.SCLK_PORT,	pInfo->Port.SCLK_Pin);		//��GPIO��Ӧ�ܽ�����ΪPP(����)���ģʽ������ٶ�2MHz----V20170605
	GPIO_Configuration_IPU		(pInfo->Port.SDO_PORT,	pInfo->Port.SDO_Pin);			//��GPIO��Ӧ�ܽ�����Ϊ��������ģʽ----V20170605
	
	CS5530SetH(CS);         //CS==0
	CS5530_SCLK_LOW;
	CS5530_PowerUp(pInfo);		//CS5530�ϵ缰��ʼ��
}
/*******************************************************************************
* ������			:	function
* ��������		:	���ذ�
* ����			: void
* ����ֵ			: void
*******************************************************************************/
void CS5530_WriteOneByte(u8 dat)
{
	u8 i;
	u16 delayTime	=	1000;
  
//	pInfo->Port.SCLK_PORT->BRR    = pInfo->Port.SCLK_Pin;   //SCLK==0
  CS5530SetL(CS);         //CS==0
	CS5530_Delayus(20);				//SysTick��ʱnuS
	for(i=0; i<8; i++)
	{
		if((dat&0x80) != 0)
      CS5530SetH(SDI);    //SDI==1
		else
      CS5530SetL(SDI);    //SDI==0
		
		CS5530_Delayus(10);	  //SysTick��ʱnuS
    CS5530SetH(SCLK);     //SCLK==1
		CS5530_Delayus(10);    //SysTick��ʱnuS
    CS5530SetL(SCLK);     //SCLK==0
    CS5530_Delayus(5);    //SysTick��ʱnuS
		dat <<= 1;
	}
}
/*******************************************************************************
* ������			:	function
* ��������		:	���ذ�
* ����			: void
* ����ֵ			: void
*******************************************************************************/
unsigned char CS5530_ReadOneByte(void)
{
	uint8_t i;
	uint8_t reValue=0;
  CS5530SetL(SDI);        //SDI==0
	CS5530_Delayus(20);		  //SysTick��ʱnuS
	for(i=0; i<8; i++)
	{	
    CS5530SetH(SCLK);     //SCLK==1
    CS5530_Delayus(5);	  //SysTick��ʱnuS
		reValue <<= 1;
		if(CS5530GetBit)
			reValue++;
		CS5530_Delayus(5);	  //SysTick��ʱnuS
    CS5530SetL(SCLK);     //SCLK==0	
    CS5530_Delayus(5);	  //SysTick��ʱnuS
	}
	CS5530_Delayus(5);	  //SysTick��ʱnuS

	return reValue;
}
/*******************************************************************************
* ������			:	function
* ��������		:	��������˵��
* ����			: void
* ����ֵ			: void
*******************************************************************************/
void CS5530_WriteCommand(u8 command)
{
	CS5530_WriteOneByte(command);
}
/*******************************************************************************
* ������			:	function
* ��������		:	��������˵�� 
* ����			: void
* ����ֵ			: void
*******************************************************************************/
void CS5530_WriteRegister(u8 command,u32 setData)
{
//	unsigned long temp=0xFFFFFFFF;
	CS5530_WriteOneByte(command);
	CS5530_WriteOneByte((uint8_t)(setData>>24));
	CS5530_WriteOneByte((uint8_t)(setData>>16));
	CS5530_WriteOneByte((uint8_t)(setData>>8));
	CS5530_WriteOneByte((uint8_t)(setData>>0));
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
  CS5530Info  = &pInfo->Port;
  CS5530SetL(SDI);    //SDI==0
  CS5530_ReadOneByte();
  reValue = ((u32)CS5530_ReadOneByte()<<24)
          +((uint32_t)CS5530_ReadOneByte()<<16)
          +((uint32_t)CS5530_ReadOneByte()<<8)
          +(uint32_t)CS5530_ReadOneByte();
	return reValue;
}
/*******************************************************************************
* ������			:	function
* ��������		:	��������˵�� 
* ����			: void
* ����ֵ			: void
*******************************************************************************/
u32 CS5530_ReadRegister(u8 command)
{
	volatile unsigned long temp=0x00;

	CS5530_WriteOneByte(command);
	temp = (CS5530_ReadOneByte()<<24)
				+(CS5530_ReadOneByte()<<16)
				+(CS5530_ReadOneByte()<<8)
				+CS5530_ReadOneByte();
	
	return temp;
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
  CS5530Info  = &pInfo->Port;
	SysTick_DeleymS(20);				//SysTick��ʱnmS
	CS5530_SCLK_LOW;
  CS5530SetL(CS);         //CS==0
	SysTick_DeleymS(20);				//SysTick��ʱnmS
	//1)��ϵͳ����ADC���͸�λ����
	//1.1��************д��15��SYNC1����(0XFF)
	for(num=0;num<20;num++)
	{
		CS5530_WriteOneByte(CS5530_SYNC1);
	}
	//1.2��************д��1��SYNC0���0XFE��
	CS5530_WriteOneByte(CS5530_SYNC0);
	SysTick_DeleymS(1);				//SysTick��ʱnmS
	
	//2)��ʼ���Ĵ���
	//2.1)д���üĴ��� д��CS5530��λ���� RSΪ1
	CS5530_WriteRegister(CS5530_WRITE_CONFIG,CS5530_CONF_SYSTEM_RESET);
	SysTick_DeleymS(1);				//SysTick��ʱnmS
	//2.1)��RS����Ϊ1�󣬵�8����ʱ�����ڣ��ٰ�RSд��0
	CS5530_WriteOneByte(CS5530_NULL_BYTE);
	SysTick_DeleymS(1);				//SysTick��ʱnmS
	//2.1)��RSд��0����ע�������д���ڹ����У���Ҫ�����üĴ����������߼�λ���в���
	CS5530_WriteRegister(CS5530_WRITE_CONFIG,CS5530_CONF_NORMAL_MODE);
	SysTick_DeleymS(1);				//SysTick��ʱnmS
	
//	CS5530SetH(CS);         //CS==1
//	return;
	
	//2.2���RV�Ƿ�Ϊ1(��λ�� ����Ϊ1),�����Ϊ1�ټ�����ȡ���üĴ���		
	do
	{ 
		CS5530_Status = CS5530_ReadRegister(CS5530_READ_CONFIG);
		SysTick_DeleymS(10);				//SysTick��ʱnmS
	}
	while(((CS5530_Status & CS5530_CONF_RESET_STATUS) != 0)&&(retry++<=20));
	
	if(retry>=19)		//����ʧ��
	{
		CS5530SetH(CS);         //CS==1
		return;
	}
	//---------------------------��ʼ����ɺ�����Ĵ�����ֵ(�Ǳ�������)
	CS5530_Status = CS5530_ReadRegister(CS5530_READ_CONFIG);			//���üĴ���0x00000000
	CS5530_Status = CS5530_ReadRegister(CS5530_READ_OFFSET);			//ƫ�ƼĴ���0x00000000
	CS5530_Status = CS5530_ReadRegister(CS5530_READ_GAIN);				//����Ĵ���0x01000000
  
  //3)��������Ĵ���
  //3.1)������Ĵ���
  WriteCS5530Gain:
  SysTick_DeleymS(10);				//SysTick��ʱnmS
  CS5530_Status = CS5530_ReadRegister(CS5530_READ_GAIN);				//����Ĵ���
	//3.2)��������ֵ
//	CS5530_Status|=0x01000000;
//  CS5530_Status=0x3F000000;	
//	CS5530_Status=0x0FFFFFF;	
//	CS5530_Status=0x7FFFFFF;	
//	CS5530_Status=0x1FFFFFF;	
//	CS5530_Status=0x1000000;		//1200	
//	CS5530_Status=0x00800000;		//600	
//	CS5530_Status=0x00400000;		//300	
//	CS5530_Status=0x00200000;		//150	
//	CS5530_Status=0x01000000;		//1200	
	CS5530_Status=0x01000000;		//test    //����Խ�󣬷Ŵ���ԽС
	//3.3)д������ֵ
  CS5530_WriteRegister(CS5530_WRITE_GAIN,CS5530_Status);			//����Ĵ���	
  //3.4)���д��ֵ
  CS5530_Status = CS5530_ReadRegister(CS5530_READ_GAIN);				//����Ĵ���
  if(CS5530_Status != CS5530_ReadRegister(CS5530_READ_GAIN))
  {
    goto WriteCS5530Gain;
  }
  
  //4)����ƫ�ƼĴ���
  //4.1)��ƫ�ƼĴ���
  WriteCS5530Offset:
  SysTick_DeleymS(10);				//SysTick��ʱnmS
	CS5530_Status=CS5530_ReadRegister(CS5530_READ_OFFSET);			//ƫ�ƼĴ���
  //4.2)����ƫ��ֵ
  CS5530_Status|=0x000000;
  //4.3)д��ƫ��ֵ
  CS5530_WriteRegister(CS5530_WRITE_OFFSET,CS5530_Status);		//���üĴ���
  //4.4)���д��ֵ
  if(CS5530_Status  !=  CS5530_ReadRegister(CS5530_READ_OFFSET))
  {
    goto WriteCS5530Offset;
  }
  
  //5)�������üĴ���
  //5.1)�����üĴ���
  WriteCS5530Config:
  SysTick_DeleymS(10);				//SysTick��ʱnmS
  CS5530_Status=CS5530_ReadRegister(CS5530_READ_CONFIG);			//���üĴ���
  //5.2)����ת������
  CS5530_Status=CS5530_Status|0x82000;    //6.25sps	
//  CS5530_Status=CS5530_Status|0x2000;	    //7.5sps	
//  CS5530_Status=CS5530_Status|0x1800;		  //15sps	
//  CS5530_Status=CS5530_Status|0x0800;		  //60sps	
//  CS5530_Status=CS5530_Status|0x4000;		  //3840sps	
//  CS5530_Status=CS5530_Status|0x6000;		  //240sps
  //5.3)�������뼫��
	CS5530_Status	&=	~CS5530_CONF_UNIPOLAR_MODE;		            //˫����
  //CS5530_Status	=	CS5530_Status|CS5530_CONF_UNIPOLAR_MODE;		//������
  //5.4)��������ģʽ
//  CS5530_Status	&=	~CS5530_CONF_SHORT_INPUTS;                //��������
//  CS5530_Status=CS5530_Status|CS5530_CONF_SHORT_INPUTS;		    //����Ϊ�����·
  //5.3)д��
  CS5530_WriteRegister(CS5530_WRITE_CONFIG,CS5530_Status);		//���üĴ���
  //5.4)���д��ֵ
  if(CS5530_Status  !=  CS5530_ReadRegister(CS5530_READ_CONFIG))
  {
    goto WriteCS5530Config;
  }
	
  SysTick_DeleymS(50);				//SysTick��ʱnmS
  
	CS5530_WriteCommand(CS5530_SYSTEM_OFFSET_CAL);							//ִ��ƫ��У׼
	
	CS5530_WriteCommand(CS5530_SYSTEM_GAIN_CAL);								//ִ��ϵͳ����У׼


	SysTick_DeleymS(50);				//SysTick��ʱnmS
	CS5530_WriteCommand(CS5530_START_CONTINUOUS);									//ִ������ת��
	
//	CS5530_WriteCommand(CS5530_START_SINGLE);									//ִ�е���ת��
	
	CS5530_Delayus(500);
	CS5530SetH(CS);         //CS==1
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
  CS5530Info  = &pInfo->Port;
	CS5530SetL(CS);         //CS==0
	SysTick_DeleymS(200);				//SysTick��ʱnmS
	//1)��ϵͳ����ADC���͸�λ����
	//1.1��************д��15��SYNC1����(0XFF)
	for(num=0;num<15;num++)
	{
		CS5530_WriteOneByte(CS5530_SYNC1);
		SysTick_DeleymS(5);				//SysTick��ʱnmS
	}
	SysTick_DeleymS(50);				//SysTick��ʱnmS
	//1.2��************д��1��SYNC0���0XFE��
	CS5530_WriteOneByte(CS5530_SYNC0);
	SysTick_DeleymS(50);				//SysTick��ʱnmS
	
	//2)д���üĴ��� д��CS5530��λ���� RSΪ1
	CS5530_WriteRegister(CS5530_WRITE_CONFIG,CS5530_CONF_SYSTEM_RESET);
	SysTick_DeleymS(50);				//SysTick��ʱnmS
	CS5530_WriteOneByte(CS5530_NULL_BYTE);
	SysTick_DeleymS(50);				//SysTick��ʱnmS
	CS5530_WriteRegister(CS5530_WRITE_CONFIG,CS5530_CONF_NORMAL_MODE);
	SysTick_DeleymS(50);				//SysTick��ʱnmS
	
	//���RV�Ƿ�Ϊ1(��λ�� ����Ϊ1),�����Ϊ1�ټ�����ȡ���üĴ���		
	do
	{ 
		CS5530_Status = CS5530_ReadRegister( CS5530_READ_CONFIG);
		SysTick_DeleymS(50);				//SysTick��ʱnmS
	}
	while(((CS5530_Status & CS5530_CONF_RESET_STATUS) != 0)&&(retry++<=100));
	
	if(retry>=100)
	{
		return;
	}
	
	CS5530_WriteRegister(CS5530_WRITE_CONFIG,CS5530_CONF_POWER_SAVE_MODE);
	
	CS5530_Delayus(500);
	CS5530SetH(CS);         //CS==1
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
	CS5530Info  = &pInfo->Port;
	CS5530SetL(CS);         //CS==0
	SysTick_DeleyuS(100);				//SysTick��ʱnuS
	if(CS5530GetBit == 0)
	{			
		ADC_Value=CS5530_GetADData(pInfo)>>8;		//��ȡ24λԭ��ֵ---����4���ֽڣ���8λΪ��ֵ
	}
	CS5530SetH(CS);         //CS==1
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
	static unsigned long 	weighAve=0;		//ƽ��ֵ
	static unsigned long 	weighVar=0;		//����
	static unsigned short 	Length	=	0;
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
	
//	if(weighVar<WeighVarMax)		//����̫����ɢ�Բ������Ч
//	{
//		return weighAve;		
//	}
//	else
//	{
//		return 0xFFFFFFFF;
//	}
	return weighAve;
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
	static unsigned char ReadErrorNum=0;
	if(pInfo->Data.Time++>=5)	//5Hz 0.2S
	{
		unsigned long		ADC	=	0;
		unsigned short	Num			=	0;					//������		
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
			unsigned long	ADC_CMP	=	0;	//�˴��������ϴ����ݵıȽ�ֵ
			ReadErrorNum=0;		//���Ӵ����������
			
			//-------------------------------�жϴ���ֵ���ϴ���ֵ��ƫ��ֵ
			if(0==Num)	//���ݻ���Ϊ��,
			{
				Buffer[Num]	=	ADC;
				pInfo->Data.Num++;	//��������---Ŀǰ�Ѳ����������ݸ���
				return 0;						//�˳��˺���
			}
			//-------------------------------��Ҫ��ǰ�β����Ƚ�
			else
			{
				if(Buffer[Num-1]>ADC)	//�˴β���ֵ���ϴ�С
				{
					ADC_CMP	=	Buffer[Num-1]-ADC;
				}
				else
				{
					ADC_CMP	=	ADC-Buffer[Num-1];
				}
				//-----------------------------������ڲ��Ƿ񳬳�����Χ
				if(ADC_CMP>WeighCmpMax)			//�������ݲ�̫��ȡ����Ч
				{
					*WeighFilt	=	0xFFFFFFFF;	//������Ч
					pInfo->Data.Num	=	0;			//������в���ֵ�����¿�ʼ
					return 0;									//�˳��˺���
				}
				else
				{
					Buffer[Num]	=	ADC;
					pInfo->Data.Num++;				//��������---Ŀǰ�Ѳ����������ݸ���
				}
			}
			//-------------------------------�������ݴﵽ����ֵʱ�Ĵ���:����������������ƽ��ֵ
			if(pInfo->Data.Num>=WeighDataNum)		//��������
			{
				*WeighFilt	=	CS5530_GetWeightUseMedinaFilter(pInfo);
				pInfo->Data.Num	=	0;
				return *WeighFilt;
			}
		}
		//-------------------------------������ζ���ʧ�ܣ������
		else
		{
			if(ReadErrorNum++>50)
			{
				pInfo->Data.Num	=	0;
				*WeighFilt=0xFFFFFFFF;
				
				ReadErrorNum=0;		//���Ӵ����������
			}
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
			AD1	=	pInfo->Data.Origin;			//ԭ��ֵ
			AD2	=	pInfo->Data.WeighFilt;	//��ǰADֵ
			AD3	=	pInfo->Data.WeighPie;		//����ֵ
			if(AD2<=AD1)	//��ǰADֵ����ԭ��
			{
				pInfo->Data.Quantity		=	0;
			}
			else
			{
				pInfo->Data.Quantity=((pInfo->Data.WeighFilt-pInfo->Data.Origin)+pInfo->Data.WeighPie/2)/pInfo->Data.WeighPie;	//50%
			}
			pInfo->Flag.GetQua=0;	//�����־
		}		
	}
	return pInfo->Data.Quantity;
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
	CS5530_GetQuant(pInfo);		//��ȡ����
//	pInfo->Flag.GetQua		=	1;
}



/************************************************************************************/
