#ifndef __AMP_PHY_H
#define __AMP_PHY_H



#include "stm32f10x_type.h"



#define maxmsgsize 133  //5+128
#define headcode  (unsigned char)0x7E
#define endcode   (unsigned char)0x7F
typedef enum eucmd
{
  unknow  = 0,
  ack     = 1,
  data    = 2,
  ctl     = 3,
  sensor  = 4,
  conf    = 5
}eucmddef;
typedef enum eusubcmd
{
  ok  = 0,
}eusubcmddef;
typedef struct _stsubcmd
{
  unsigned char dir :1;   //0-down,1-up
  unsigned char rw  :1;   //0-write,1-read
  unsigned char cmd :6;   //CMD1~CMD63
}stsubcmddef;
typedef struct _stampaddr
{
  unsigned char address1;
  unsigned char address2;
  unsigned char address3;
}stampaddrdef;

typedef struct _stampcrc16
{
  unsigned char crcl;
  unsigned char crch;
}stampcrc16def;
typedef struct _stmsg
{
  unsigned char length;
  eucmddef 			cmd;
	eusubcmddef		subcmd;
	stampaddrdef	addr;
	unsigned char buffer[128];
}stmsgdef;
typedef struct _stampphy
{
  unsigned char head;
  unsigned char msg[maxmsgsize];
  stampcrc16def crc16;
  unsigned char end;
}stampphydef;



unsigned char* getheadaddr(unsigned char* pbuffer,unsigned short length);
unsigned char crccheck(unsigned char* pbuffer,unsigned short length);
unsigned short PaketMsg(unsigned	char* pbuffer,unsigned	short length);
  

#endif



