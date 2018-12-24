#ifndef __AMP01_H
#define __AMP01_H


//#include "stm32f10x_gpio.h"
//#include "stm32f10x_rcc.h"
//#include "stm32f10x_nvic.h"
//#include "stm32f10x_spi.h"

//#include "STM32_GPIO.H"


//#include	"stdio.h"			//����printf
//#include	"string.h"			//����printf
//#include	"stdarg.h"			//���ڻ�ȡ��ȷ�������Ĳ���
//#include	"stdlib.h"			//malloc��̬�����ڴ�ռ�
//------------------���ӿ�J10
#define LockDrPort    GPIOB         //�����ƽӿڣ��ߵ�ƽ����
#define LockDrPin     GPIO_Pin_7
#define LockSiPort    GPIOC         //���źţ���⵽�͵�ƽ��ʾ���ѿ�
#define LockSiPin     GPIO_Pin_15
#define UnLock        LockDrPort->BSRR  = LockDrPin    //����
#define ResLock       LockDrPort->BRR   = LockDrPin    //�ͷ�������
#define GetLockSts    LockSiPort->IDR & LockSiPin      //��ȡ����״̬�����Ϊ0����ʾ���ѿ�
//------------------����ӿ�J11��VCC��EN��
#define BackLightPort GPIOB         //�ߵ�ƽ�رգ��͵�ƽ����
#define BackLightPin  GPIO_Pin_6
#define BackLightOn   BackLightPort->BRR   = BackLightPin
#define BackLightOff  BackLightPort->BSRR  = BackLightPin
//------------------����Դ����J5��J6��J9����һ�����Ƶ�Դ
#define LayPowerPort  GPIOB         //�ߵ�������Դ���͵�ƽ�رյ�Դ
#define LayPowerPin   GPIO_Pin_8
#define LayPowerOn    LayPowerPort->BSRR = LayPowerPin   //������Դ
#define LayPowerOff   LayPowerPort->BRR  = LayPowerPin   //�رյ�Դ

#define ccsize    64          //����������ݰ�����
#define arrysize  50          //ÿ�����Ͷ˿ڴ����ͻ����������
#define ReSendWaitTime  50   //�ط����ʱ�䵥λms
#define SendNopTime     5        //���͵ȴ�ʱ�䵥λms
#define maxresendcount  5   //����ʹ���

typedef enum  _CCPort
{
  NonPort     = 0,
  PcPort      = 1,  //PCͨѶ�ӿ�
  CabPort     = 2,  //��ͨѶ�ӿ�
  LayPort     = 3,  //��ͨѶ�ӿ�
  CardPort    = 4   //������ͨѶ�ӿ�
}enCCPortDef;

typedef struct _stSW        //�������ݣ�
{
  unsigned char ID        :6;   //����� sw3~sw8Ϊ��ID��,sw3~sw8δ��ʱ��Ϊ����ģʽ���������˸
  unsigned char ICreadFlg :1;   //sw2 δ��ʱ���������Ĳ�����Ϊ19200������ʱ������Ϊ9600
  unsigned char MainFlg   :1;   //sw1 δ��ʱ���˹�Ϊ���񣬲���ʱΪ����
}stSWdef;
typedef struct _stFlg        //�������ݣ�
{
  unsigned char MainIDLE  :1;   //������б�־��0-���У�1-�ǿ���״̬
  unsigned char CabBD     :1;   //����ư��־��0-�ǹ���ư壬1-����ư�
  unsigned char LayBD     :1;   //������ư��־��0-�ǲ���ư壬1-����ư�
  unsigned char SetBD     :1;   //λ���ư��־��0-��λ���ư壬1-λ���ư�
  unsigned char LockFlg   :1;   //����־��0-��״̬��1-��״̬
  unsigned char LayPownOn :1;   //���ͨ���־��0-δͨ�磬1-��ͨ��
}stFlgdef;
typedef struct _stAckQ        //��ҪӦ���־
{
  unsigned char PcAck     :1;   //PC�ӿ���ҪӦ��0-���У�1-��ҪӦ��
  unsigned char PcDir     :1;   //PC�ӿ�Ӧ����0-����Ӧ��1-����Ӧ��
  unsigned char CabAck    :1;   //��ӿ���ҪӦ��0-���У�1-��ҪӦ��
  unsigned char CabDir    :1;   //��ӿ�Ӧ����0-����Ӧ��1-����Ӧ��
  unsigned char LayAck    :1;   //��ӿ���ҪӦ��0-���У�1-��ҪӦ��
  unsigned char LayDir    :1;   //��ӿ�Ӧ����0-����Ӧ��1-����Ӧ��
  unsigned char CardAck   :1;   //�������ӿ���ҪӦ��0-���У�1-��ҪӦ��
  unsigned char CardDir   :1;   //�������ӿ�Ӧ����0-����Ӧ��1-����Ӧ��
}stAckQdef;
typedef struct _stSendCount   //�ط�������
{
  unsigned char PcCount;      //PC�ϴ��ط�����
  unsigned char CabCount;     //��ӿ��ط�����
  unsigned char LayCount;     //��ӿ��ط�����
  unsigned char CardCount;    //�������ӿ��ط�����
}stSendCountdef;
typedef struct _stTx       //�������ݣ�
{
  unsigned char arry;           //��������0ʱΪ�գ��ӵ�1����ʼ���ͣ�������һ���������1��ֱ��0������ʱ������һ�������ͻ��棬�»��������
  unsigned char size;           //��ǰ������Ч���ݸ���(�������ֽ���)
  unsigned char data[ccsize];   //����
}stTxdef;
typedef struct _stBuffer       //�������ݣ�
{  
//  stTxdef   Amprx[1];           //���ж˿ڽ��ջ���
  stTxdef   PcTx[arrysize];     //����1���ͻ���--PC�ӿ�
  stTxdef   CabTx[arrysize];    //����4���ͻ���--����
  stTxdef   LayTx[arrysize];    //����2���ͻ���--���ӿ�
  stTxdef   CardTx[arrysize];   //����3���ͻ���--������  
}stBufferdef;
typedef struct _stTims       //�������ݣ�
{
  unsigned short runningtime;   //���м�����
  unsigned short swicthidtime;   //���м�����
  unsigned short PcSendTime;    //���м�����
  unsigned short CabSendTime;   //���м�����
  unsigned short LaySendTime;   //���м�����
  unsigned short CardSendTime;  //���м�����
}stTimsdef;

typedef struct _stSys
{
  stTimsdef         Time;         //���ʱ�����
  stSWdef           SwData;       //������־
  stFlgdef          Flag;         //��ر�־λ
  stAckQdef         AckQ;         //��־Ӧ���־��0-����Ҫ��1-��ҪӦ����Ӧ�ӿ�
  stBufferdef       buffer;       //�������ݻ���
  stSendCountdef    ReSend;
}stSysdef;



extern void AMP01_Configuration(void);
extern void AMP01_Server(void);

void AMP01_Loop(void);
void MainCabinet_IDLEServer(void);  //������з������



void Send_Server(void);




void Msg_Process(enCCPortDef Port,unsigned char* pBuffer,unsigned short length);        //����Ϣ����
void CMD_Process(unsigned char* pBuffer,unsigned short length);
void ackFrame(enCCPortDef Port,unsigned char dir);
//=================================�����ӿ�ST=============================================================
unsigned short Check_SendBuff(enCCPortDef Port);                                //�����Ӧ�˿ڴ����ͻ���
unsigned short Releas_OneBuffer(enCCPortDef Port);        //�ͷ�һ�����ͻ���
unsigned short AddSendData(enCCPortDef Port,unsigned char* pBuffer,unsigned short length);
unsigned short PCnet_Send(unsigned char* pBuffer,unsigned short length);      //��PC������Ϣ
unsigned short Cabinet_Send(unsigned char* pBuffer,unsigned short length);    //����������Ϣ
unsigned short Laynet_Send(unsigned char* pBuffer,unsigned short length);     //����巢����Ϣ
unsigned short CardPort_Send(unsigned char* pBuffer,unsigned short length);   //���������ӿڷ�����

//=================================Ӳ���ӿ�ST==============================================================
void Receive_Server(void);
unsigned short HW_SendBuff(enCCPortDef Port,unsigned char* pBuffer,unsigned short length);    //ͨ����Ӧ�˿ڷ�������
void SwitchID_Server(void);
void LockServer(void);

//=================================���ú���ST==============================================================
void COMM_Configuration(void);
void SwitchID_Configuration(void);
void GenyConfiguration(void);   //����ӿ����ã����⣬������Դ����

//=================================ʱ�亯��ST==============================================================
void Tim_Server(void);
void AMPdelaymS(unsigned  short time);

#endif