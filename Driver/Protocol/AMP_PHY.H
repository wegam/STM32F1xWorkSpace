#ifndef __AMP_PHY_H
#define __AMP_PHY_H



#include "stm32f10x_type.h"



#define maxmsgsize 133  //5+128
#define headcode  (unsigned char)0x7E
#define endcode   (unsigned char)0x7F
  
#define gDatasize       128      	//串口最大数据包容量
#define arrysize        20       	//每个发送端口待发送缓存排序个数
#define MaxSlave        30        //最大从机数量(柜、层、位)
#define ReSendWaitTime  50 	      //重发间隔时间单位ms
#define SendNopTime     3  	      //发送等待时间单位ms---应答等待时间
#define maxresendcount  5         //最大发送次数
#define unlockOuttime   2000      //开锁倒计时超时时间
#define checkswitchidtime 2000    //检查拨码开关时间间隔
#define GetOnlinetime   5000      //获取在线设备时间间隔

typedef enum eucmd
{
  NoneCmd   = 0,  //不支持的命令/空命令
  AMPACK  = 1,    //应答类型，只带一个数据，不带地址，数据表示状态
  LED     = 2,    //LED控制，带三个数据，带地址，0-表示关，1-表示开
  CTL     = 3,    //开锁命令，只带一个数据，带地址，0-表示读锁状态，1表示开锁
  ICR     = 4,    //读卡器，带地址，第一个数据为0表示读卡，为1表示写卡，后面跟随卡数据
  PWD     = 5,    //层板供电控制
  STA     = 6,    //状态：主要为上报状态
  GetOnline = 7,    //检查在线设备，接收到后应答表示在线
  Up      = 0x80, //上传标志
  Down    = 0x7F  //下发与标志
}eucmddef;

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




typedef enum  _CCPort
{
  NonPort     = 0,
  PcPort      = 1,  //PC通讯接口
  CabPort     = 2,  //柜通讯接口
  LayPort     = 3,  //层通讯接口
  CardPort    = 4   //读卡器通讯接口
}enCCPortDef;
typedef struct _stSW        //拨码数据：
{
  unsigned char ID        :6;   //拨码地 sw3~sw8为板ID号,sw3~sw8未拨时，为测试模式，背光灯闪烁
  unsigned char ICreadFlg :1;   //sw2 未拨时，读卡器的波特率为19200，拨上时波特率为9600
  unsigned char MainFlg   :1;   //sw1 未拨时，此柜为副柜，拨上时为主柜
}stSWdef;
typedef struct _stFlg        //拨码数据：
{
  unsigned short LayPownOn :1;   //层板通电标志：0-未通电，1-已通电
//  unsigned short WaitAck   :1;   //等待应答--发送完后需要等待应答，如果接收到应答，则清除一个发送缓存：0-未标志，1-在等待应答  
}stFlgdef;
typedef struct _stStatus        //拨码数据：
{
  unsigned short lockstd    :1;  //锁状态：0-开状态，1-锁状态
  unsigned short unlockerr  :1;  //开锁错误/失败:0-无，1-开锁失败
  unsigned short Online     :1;  //设备掉线:0-掉线，1-在线
}stStadef;
typedef struct _stAckQ        //需要应答标志
{
  unsigned char PcAck     :1;   //PC接口需要应答：0-空闲，1-需要应答
  unsigned char PcDir     :1;   //PC接口应答方向：0-向下应答，1-向上应答
  unsigned char CabAck    :1;   //柜接口需要应答：0-空闲，1-需要应答
  unsigned char CabDir    :1;   //柜接口应答方向：0-向下应答，1-向上应答
  unsigned char LayAck    :1;   //层接口需要应答：0-空闲，1-需要应答
  unsigned char LayDir    :1;   //层接口应答方向：0-向下应答，1-向上应答
  unsigned char CardAck   :1;   //读卡器接口需要应答：0-空闲，1-需要应答
  unsigned char CardDir   :1;   //读卡器接口应答方向：0-向下应答，1-向上应答
}stAckQdef;
typedef struct _stSendCount   //重发计数器
{
  unsigned char PcCount;      //PC上传重发计数
  unsigned char CabCount;     //柜接口重发计数
  unsigned char LayCount;     //层接口重发计数
  unsigned char CardCount;    //读卡器接口重发计数
}stSendCountdef;
typedef struct _stTx       //拨码数据：
{
  unsigned char arry;           //发送排序：0时为空，从第1个开始发送，发送完一个，排序减1，直到0，增加时，增加一个待发送缓存，新缓存排最后
  unsigned char size;           //当前缓存有效数据个数(待发送字节数)
  unsigned char data[gDatasize];   //缓存
}stTxdef;
typedef struct _stBuffer       //拨码数据：
{  
  struct
  {
    unsigned char Pc:1;
    unsigned char Cab:1;
    unsigned char Lay:1;
    unsigned char Card:1;
  }WaitAck;
  unsigned char rxdbuffer[gDatasize]; //所有端口接收缓存
  stTxdef   PcTx[arrysize];     //串口1发送缓存--PC接口
  stTxdef   CabTx[arrysize];    //串口4发送缓存--副柜
  stTxdef   LayTx[arrysize];    //串口2发送缓存--层板接口
  stTxdef   CardTx[arrysize];   //串口3发送缓存--读卡器
}stBufferdef;
typedef struct _stTims       //拨码数据：
{
  unsigned short runningtime;     //运行计数器
  unsigned short swicthidtime;    //运行计数器
  unsigned short SYSLEDTime;      //LED运行计数器
  unsigned short LockTime;        //LED运行计数器
  unsigned short PcSendTime;      //运行计数器
  unsigned short CabSendTime;     //运行计数器
  unsigned short LaySendTime;     //运行计数器
  unsigned short CardSendTime;    //运行计数器  
}stTimesdef;
typedef struct _stRequest            //锁
{
  unsigned short  unlockqust  :1;//开锁请求：0-无请求，1-有请求
  unsigned short  unlockrun   :1;//执行开锁：0-无，1-正在执行  
  unsigned short  reslock     :1;//释放锁驱动请求：0-无请求，1-有请求
  unsigned short  BLon        :1;//开背光请求：0-无请求，1-有请求
  unsigned short  BLoff       :1;//关背光请求：0-无请求，1-有请求
  unsigned short  PLon        :1;//层板供电开请求：0-无请求，1-有请求
  unsigned short  PLoff       :1;//层板供电关请求：0-无请求，1-有请求
}stReqdef;
typedef struct _stAMPPrl
{
  stTimesdef        Time;         //相关时间变量
//  stSWdef           SwData;       //主机标志
  stReqdef          Req;         //请求类标志
  stStadef          Sta;          //状态码
  stFlgdef          Flag;         //相关标志位
  stAckQdef         AckQ;         //标志应答标志，0-不需要，1-需要应答相应接口
  stBufferdef       buffer;       //串口数据缓存
  stSendCountdef    ReSend;
}stAMPProdef;
unsigned short getframe(unsigned char* pbuffer,unsigned short* length);
unsigned char* getheadaddr(unsigned char* pbuffer,unsigned short* length);
unsigned char crccheck(unsigned char* pframe,unsigned short* length);
unsigned short SetFrame(unsigned char* pframe,unsigned short* length);    //补充消息的CRC和结束符，返回帧长度


unsigned short PaketUpMsg(unsigned	char* pbuffer,eucmddef cmd,unsigned	short* length);     //打包上传消息
unsigned short PaketDownMsg(unsigned	char* pbuffer,eucmddef cmd,unsigned	short* length);   //打包上传消息

unsigned char ackcheck(unsigned char* pframe);    //检查是否为应答消息,应答消息返回1
unsigned char addr1check(unsigned char* pframe,unsigned char addr1);
unsigned char addr2check(unsigned char* pframe,unsigned char addr2);
unsigned char addr3check(unsigned char* pframe,unsigned char addr3);

 
unsigned short Releas_OneBuffer(enCCPortDef Port);
void ackFrame(enCCPortDef Port,unsigned char dir);
void Send_Server(void);
unsigned short Check_SendBuff(enCCPortDef Port); 
void Send_ConnectErr(enCCPortDef Port,unsigned char* pBuffer,unsigned short length);    //发送连接错误/超时

unsigned short AddSendBuffer(enCCPortDef Port,unsigned char* pBuffer,unsigned short length);
#endif



