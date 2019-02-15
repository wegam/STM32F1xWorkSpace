
#ifndef __CS5530_H
#define __CS5530_H
//#include <stdint.h>
#include "stm32f10x_gpio.h"


#define WeighDataNum											20	//����ʱ��Ҫ��ȡ�����ݸ���
#define GetFiltDataDelayTime				WeighDataNum*150	//��ȡ�ȶ�ADֵ��Ҫ����ʱ��λms������ȡ��ʱ��*ȡ������+������ʱ��3000��
#define	WeighCmpMax									1000	//����ADֵ�����ֵ��С
#define	WeighVarMax									20000	//������󷽲�
#define CS5530_OF_MAX_NUM						10	/*�������������10�ζ����,��ʾ�����Ѿ������*/
#define CS5530_CONTINUOUS_IGNORE		10	/*��ʼ����ת��ʱ,Ҫ����ǰ10(�������Ƽ���5)����׼ȷ������*/


#define CS5530_WRITE_OFFSET				(unsigned char)0x01	/*дƫ�ƼĴ���*/
#define CS5530_WRITE_GAIN					(unsigned char)0x02	/*д����Ĵ���*/
#define CS5530_WRITE_CONFIG				(unsigned char)0x03	/*д���üĴ���*/
 
#define CS5530_READ_OFFSET				(unsigned char)0x09	/*��ƫ�ƼĴ���*/
#define CS5530_READ_GAIN					(unsigned char)0x0A	/*������Ĵ���*/
#define CS5530_READ_CONFIG				(unsigned char)0x0B	/*�����üĴ���*/
  
#define CS5530_START_SINGLE				(unsigned char)0x80	//ִ�е���ת��
#define CS5530_START_CONTINUOUS		(unsigned char)0xC0	//ִ������ת��
#define CS5530_SYSTEM_OFFSET_CAL	(unsigned char)0x85	/*ִ��ϵͳƫ��У׼*/
#define CS5530_SYSTEM_GAIN_CAL		(unsigned char)0x86	/*ִ��ϵͳ����У׼*/
#define CS5530_SYNC1							(unsigned char)0xFF	/*���пڳ�ʼ����������֮һ*/
#define CS5530_SYNC0							(unsigned char)0xFE	/*���пڳ�ʼ�����н�������*/
#define CS5530_NULL_BYTE					(unsigned char)0x00	/*��������˿ڱ�־λʹ��ת��������������ת��ģʽ*/

// Configuration Register
#define CS5530_CONF_STANDBY_MODE				(0x00UL<<31)	/*����ģʽ,���Ľ���4mW,����ģʽ�±�������
																											��ģ��ƫ�õ�·����,�������PDW����Ϊ0ʱ,
																											ת�����������ϴ�ʡ��ģʽ��������ģʽ*/
#define CS5530_CONF_SLEEP_MODE					(0x01UL<<31)	/*����ģʽ,����˯��ģʽ,���Ľ�Ϊ500��W,����
																											ģʽ�����ڹر�������,��Ҫ��������ģʽʱ,
																											����Ҫ��ʱ20mS����������*/
																											
#define CS5530_CONF_POWER_SAVE_MODE			(0x01UL<<30)	/*�ڵ�ģʽ*/
#define CS5530_CONF_POWER_ON_MODE				(0x00UL<<30)	/*����ģʽ*/
#define CS5530_CONF_NORMAL_MODE					(0x00UL<<29)	/*��������*/
#define CS5530_CONF_SYSTEM_RESET				(0x01UL<<29)	/*����һ����λ���� ��λ����Ҫ�����0*/
#define CS5530_CONF_RESET_STATUS				(0x01UL<<28)	/*��λ��Ч ϵͳ�Ѹ�λ ֻ��,0-����������1-��λ�ɹ�*/
#define CS5530_CONF_SHORT_INPUTS				(0x01UL<<27)	//����Ϊ�����·
#define CS5530_CONF_NOSHORT_INPUTS			(0x00UL<<27)	//��������,ͨ�����벻�̽�
#define CS5530_CONF_VREF_HIGH						(0x00UL<<25)	/*�ο���ѹ 2.5~((VA+)-(VA-))V*/
#define CS5530_CONF_VREF_LOW						(0x01UL<<25)	/*�ο���ѹ 1~2.5V*/
#define CS5530_CONF_CR_A1_0							(0x00UL<<24)	/*��A1�ܽŵ�ƽ��ΪVA-*/
#define CS5530_CONF_CR_A1_1							(0x01UL<<24)	/*��A1�ܽŵ�ƽ��ΪVA+*/
#define CS5530_CONF_CR_A0_0							(0x00UL<<23)	/*��A0�ܽŵ�ƽ��ΪVA-*/
#define CS5530_CONF_CR_A0_1							(0x01UL<<23)	/*��A0�ܽŵ�ƽ��ΪVA+*/
#define CS5530_CONF_LINE_FREQ_60				(0x00UL<<19)	/*�˲�����ѡ�� ȱʡ������,�ϵ��������¿��ṩ60Hz����*/
#define CS5530_CONF_LINE_FREQ_50				(0x01UL<<19)	/*��������ʼ���Ӧ�˲������Գ���ϵ��5/6,�ϵ��������¿��ṩ50Hz����*/
#define CS5530_CONF_DATARATE_120_100		(0x00UL<<11)	/*����������ʱ��Ϊ4.9152MHz,����ת��ģʽ�µ�������*/
#define CS5530_CONF_DATARATE_60_50			(0x01UL<<11)
#define CS5530_CONF_DATARATE_30_25			(0x02UL<<11)
#define CS5530_CONF_DATARATE_15_12P5		(0x03UL<<11)
#define CS5530_CONF_DATARATE_7P5_6P25		(0x04UL<<11)
#define CS5530_CONF_DATARATE_3840_3200	(0x08UL<<11)
#define CS5530_CONF_DATARATE_1920_1600	(0x09UL<<11)
#define CS5530_CONF_DATARATE_960_800		(0x0AUL<<11)
#define CS5530_CONF_DATARATE_480_400		(0x0BUL<<11)
#define CS5530_CONF_DATARATE_240_200		(0x0CUL<<11)
#define CS5530_CONF_DATARATE_MASK				(0x0FUL<<11)
#define CS5530_CONF_BIPOLAR_MODE				(0x00UL<<10)	//����ѡ��˫����ģʽ
#define CS5530_CONF_UNIPOLAR_MODE				(0x01UL<<10)	//����ѡ�񵥼���ģʽ
#define CS5530_CONF_TURN_OFF_300NA			(0x00UL<<9)		/*���������Դ*/
#define CS5530_CONF_TURN_ON_300NA				(0x01UL<<9)		/*�������Դ300ma*/
	
#define CS5530_CONTINUOUS_ON			(unsigned char)0x00	/*��������ת��ģʽ--���SDO��־*/
#define CS5530_CONTINUOUS_OFF			(unsigned char)0xFF	/*�˳�����ת��ģʽ*/

/*ת�����ݼĴ�����8λ״̬*/
#define CS5530_CDR_OF_MASK				0x00000004	/*�����־λ:
																	0-���洦;
																	1-���,���������źŴ����������̷�Χ,�������ź�С��
																	0(������)��С�ڸ������̷�Χ(˫����)ʱ����1;*/

typedef struct	_CS5530Port
{
	//CS-PIN:Ƭѡ
	//	��CS=0ʱ�����ڿ���ʶ��SCLK�źš�
	//	��CS=1ʱ��SDOΪ����̬��
	//	��SCLK=0ʱ��CS���Ųſ��Ըı�״̬��
	GPIO_TypeDef* 	CS_PORT;				//GPIOX
	unsigned short 	CS_Pin;				//GPIO_Pin_x
	
	//SDI-PIN:������������
	//���������������ţ����������ٶ���SCLK����
	GPIO_TypeDef* 	SDI_PORT;			//GPIOX
	unsigned short 	SDI_Pin;				//GPIO_Pin_x
	
	//SDO-PIN:�����������
	//��CS=1ʱ��SDOΪ����̬��
	GPIO_TypeDef* 	SDO_PORT;			//GPIOX
	unsigned short 	SDO_Pin;				//GPIO_Pin_x
	
	//SCLK-PIN:����ʱ������
	//�����ŵ�ʱ���źſ��Ծ���SDI/SDO��������/����ٶȵĴ�С�������ž���ʩ����
	//�������������������Ƚ������ź����롣��CS=0ʱ�������ſ���ʶ��ʱ���źš�
	GPIO_TypeDef* 	SCLK_PORT;			//GPIOX
	unsigned short 	SCLK_Pin;			//GPIO_Pin_x

}CS5530PortDef;
typedef struct	_CS5530Data
{
	unsigned short	Retry;						//���Լ���
	unsigned short 	Quantity;					//����
	unsigned short	Num;							//������	
	unsigned long		Origin;						//ԭ��ֵ
	unsigned long 	WeighLive;				//ʵʱADֵ
	unsigned long 	WeighFilt;				//�˲���ADֵ	
	unsigned long 	WeighPie;					//����
	unsigned long		Buffer[WeighDataNum];	//���ݻ���
	unsigned long		Time;							//��ʱ��
}CS5530DataDef;
typedef struct	_CS5530Flag		//0Ϊ�ޱ�ʶ
{
	unsigned short IDLE:1;			//����
	unsigned short StLv:1;			//���ȶ�
	unsigned short GetOri:1;		//��ȡԭ��
	unsigned short GetCali:1;		//��ȡ����
	unsigned short GetQua:1;		//��ȡ����
}CS5530FlagDef;
typedef struct	_CS5530
{
	CS5530PortDef Port;
	CS5530DataDef	Data;
	CS5530FlagDef	Flag;
}CS5530Def;


void CS5530_Initialize(CS5530Def *pInfo);
u32	CS5530_ReadData(CS5530Def *pInfo);		//��ȡADֵ���������0xFFFFFFFF,��δ��ȡ��24λADֵ
void CS5530_Process(CS5530Def *pInfo);


void CS5530_Delay(u32 time);


void CS5530_WriteOneByte(u8 dat);
unsigned char CS5530_ReadOneByte(void);

void CS5530_WriteRegister(u8 command,u32 setData);
void CS5530_WriteCommand(u8 command);


u32 CS5530_GetADData(CS5530Def *pInfo);
u32 CS5530_ReadRegister(u8 command);



void CS5530_PowerUp(CS5530Def *pInfo);		//CS5530�ϵ缰��ʼ��
void CS5530_PowerDown(CS5530Def *pInfo);



unsigned long CS5530_GetWeightUseMedinaFilter(CS5530Def *pInfo);
unsigned long CS5530_GetWeigh(CS5530Def *pInfo);		//��ȡ�ȶ���ADֵ
unsigned long CS5530_GetCalib(CS5530Def *pInfo);		//�궨/��ȡ����
unsigned long CS5530_GetOrigin(CS5530Def *pInfo);		//��ȡԭ��ֵ
unsigned long CS5530_GetQuant(CS5530Def *pInfo);		//��ȡ����

void CS5530_Clear(CS5530Def *pInfo);		//�����������б�־������

#endif

