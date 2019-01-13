#ifndef __AMP_LAY_H
#define __AMP_LAY_H


#include	"AMP_PHY.H"

//#include "stm32f10x_gpio.h"
//#include "stm32f10x_rcc.h"
//#include "stm32f10x_nvic.h"
//#include "stm32f10x_spi.h"

//#include "STM32_GPIO.H"


//#include	"stdio.h"			//用于printf
//#include	"string.h"			//用于printf
//#include	"stdarg.h"			//用于获取不确定个数的参数
//#include	"stdlib.h"			//malloc动态申请内存空间


//------------------层板电源控制J5、J6、J9共用一个控制电源


//#define ccsize    64          //串口最大数据包容量
//#define arrysize  50          //每个发送端口待发送缓存排序个数
//#define ReSendWaitTime  50   //重发间隔时间单位ms
//#define SendNopTime     5        //发送等待时间单位ms
//#define maxresendcount  5   //最大发送次数
extern stAMPProdef   AMPPro;

void AMPLAY_Configuration(void);
void AMPLAY_Server(void);
void AMPLAY_Loop(void);
void AMPLAY_Receive(void);
void AMPLAY_SwitchIDServer(void);
void AMPLAY_SYSLED(void);


void AMPLAYSwitchID_Configuration(void);
void AMPLAY_GenyConfiguration(void);
void AMPLAYCOMM_Configuration(void);

void Msg_ProcessLY(enCCPortDef Port,unsigned char* pBuffer,unsigned short length);      //层消息处理

unsigned short AMPLAY_SendBuff(enCCPortDef Port,unsigned char* pBuffer,unsigned short length);
unsigned short AMPLAY_Send(unsigned char* pBuffer,unsigned short length);

#endif
