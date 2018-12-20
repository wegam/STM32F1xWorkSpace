#ifndef __AMP_PHY_H
#define __AMP_PHY_H



#include "stm32f10x_type.h"



#define maxmsgsize 133  //5+128
#define headcode  (unsigned char)0x7E
#define endcode   (unsigned char)0x7F
typedef enum eucmd
{
  unknow  = 0,    //不支持的命令
  ACK     = 1,    //应答类型，只带一个数据，不带地址，数据表示状态
  LED     = 2,    //LED控制，带三个数据，带地址，0-表示关，1-表示开
  CTL     = 3,    //开锁命令，只带一个数据，带地址，0-表示读锁状态，1表示开锁
  ICR     = 4,    //读卡器，带地址，第一个数据为0表示读卡，为1表示写卡，后面跟随卡数据
  PWD     = 5,     //关闭层板供电
  Up      = 0x80, //上传标志
  Down    = 0x7F  //下发与标志
}eucmddef;
typedef enum eusubcmd
{
  ok  = 0,
}eusubcmddef;
typedef struct _stcmd
{
  unsigned char cmd :6;   //CMD1~CMD63---低6位  
  unsigned char rw  :1;   //0-write,1-read--高7位
  unsigned char dir :1;   //0-down,1-up---高8位
  
}stcmddef;
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
  unsigned char length;   //不包含此位
  stcmddef 			cmd;
	stampaddrdef	addr;
	unsigned char data[128];
}stmsgdef;
typedef struct _stampphy
{
  unsigned char head;
  stmsgdef      msg;
  stampcrc16def crc16;
  unsigned char end;
}stampphydef;


unsigned short getframe(unsigned char* pbuffer,unsigned short* length);
unsigned char* getheadaddr(unsigned char* pbuffer,unsigned short* length);
unsigned char crccheck(unsigned char* pframe,unsigned short* length);
unsigned short SetCrc(unsigned char* pframe,unsigned short* length);

unsigned short PaketMsg(unsigned	char* pbuffer,eucmddef cmd,unsigned	short* length);

unsigned char ackcheck(unsigned char* pframe);    //检查是否为应答消息,应答消息返回1
unsigned char addr1check(unsigned char* pframe,unsigned char addr1);
unsigned char addr2check(unsigned char* pframe,unsigned char addr2);
unsigned char addr3check(unsigned char* pframe,unsigned char addr3);

  

#endif



