#ifndef __PL001V20_H
#define __PL001V20_H



#include "Board.H"


typedef	struct _PL001V20
{
	SWITCHID_CONF Switch;
	RS485Def			RS485A;
	CD4511Def			CD4511;
	CANBUSDef			CANBUS;
	SysDef				Sys;
}PL001V20Def;



void PL001V20_Configuration(void);
void PL001V20_Server(void);


void Switch_Configuration(void);
void CD4511_Configuration(void);
void RS485_Configuration(void);
void CAN_Configuration(void);


void CD4511_Server(void);
void Switch_Server(void);
void RS485_Server(void);
void CAN_Server(void);
#endif

