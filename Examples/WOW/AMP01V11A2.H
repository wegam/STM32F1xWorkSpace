#ifndef __AMP01V11A2_H
#define __AMP01V11A2_H


#include	"AMP_PHY.H"


//------------------锁接口J10
#define SYSLEDPort    GPIOA         //锁控制接口，高电平开锁
#define SYSLEDPin     GPIO_Pin_0




extern stAMPProdef   AMPPro;

void AMP01V11A2_Configuration(void);
void AMP01V11A2_Server(void);

//void AMP01V11_Loop(void);


unsigned short HW_SendBuff(enCCPortDef Port,unsigned char* pBuffer,unsigned short length);
//=================================时间函数ST==============================================================
void Tim_Server(void);


#endif
