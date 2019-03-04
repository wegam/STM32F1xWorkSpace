#ifndef __AMPLCDV11_H
#define __AMPLCDV11_H


#include	"AMP_PHY.H"


////------------------锁接口J10
//#define SYSLEDPort    GPIOA         //锁控制接口，高电平开锁
//#define SYSLEDPin     GPIO_Pin_0




extern stAMPProdef   AMPPro;

void AMPLCDV11_Configuration(void);
void AMPLCDV11_Server(void);

void AMPLCDV11_Loop(void);

void AMPLCDV11_ComConfiguration(void);

void AMPLCDV11_Receive(void);

unsigned short HW_SendBuff(enCCPortDef Port,unsigned char* pBuffer,unsigned short length);
//=================================时间函数ST==============================================================
void Tim_Server(void);


void LCD_Configuration(void);
#endif
