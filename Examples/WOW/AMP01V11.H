#ifndef __AMP01V11_H
#define __AMP01V11_H


#include	"AMP_PHY.H"


//------------------���ӿ�J10
#define SYSLEDPort    GPIOA         //�����ƽӿڣ��ߵ�ƽ����
#define SYSLEDPin     GPIO_Pin_0




extern stAMPProdef   AMPPro;

void AMP01V11_Configuration(void);
void AMP01V11_Server(void);

void AMP01V11_Loop(void);


unsigned short HW_SendBuff(enCCPortDef Port,unsigned char* pBuffer,unsigned short length);
//=================================ʱ�亯��ST==============================================================
void Tim_Server(void);


#endif