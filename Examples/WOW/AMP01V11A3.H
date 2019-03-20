#ifndef __AMP01V11A2_H
#define __AMP01V11A2_H


#include	"AMP_PHY.H"






extern stAMPProdef   AMPPro;

void AMP01V11A3_Configuration(void);
void AMP01V11A3_Server(void);

//void AMP01V11_Loop(void);


unsigned short HW_SendBuff(enCCPortDef Port,unsigned char* pBuffer,unsigned short length);
//=================================Ê±¼äº¯ÊýST==============================================================
void Tim_Server(void);


#endif
