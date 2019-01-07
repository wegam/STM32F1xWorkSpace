#ifndef __AMP01_H
#define __AMP01_H


//#include "stm32f10x_gpio.h"
//#include "stm32f10x_rcc.h"
//#include "stm32f10x_nvic.h"
//#include "stm32f10x_spi.h"

//#include "STM32_GPIO.H"


//#include	"stdio.h"			//用于printf
//#include	"string.h"			//用于printf
//#include	"stdarg.h"			//用于获取不确定个数的参数
//#include	"stdlib.h"			//malloc动态申请内存空间
//------------------锁接口J10
#define SYSLEDPort    GPIOA         //锁控制接口，高电平开锁
#define SYSLEDPin     GPIO_Pin_0
//------------------锁接口J10
#define LockDrPort    GPIOB         //锁控制接口，高电平开锁
#define LockDrPin     GPIO_Pin_7
#define LockSiPort    GPIOC         //锁信号，检测到低电平表示锁已开
#define LockSiPin     GPIO_Pin_15
#define UnLock        LockDrPort->BSRR  = LockDrPin    //开锁
#define ResLock       LockDrPort->BRR   = LockDrPin    //释放锁驱动
#define GetLockSts    LockSiPort->IDR & LockSiPin      //获取锁的状态，如果为0，表示锁已开
//------------------背光接口J11的VCC和EN脚
#define BackLightPort GPIOB         //高电平关闭，低电平点亮
#define BackLightPin  GPIO_Pin_6
#define BackLightOn   BackLightPort->BRR   = BackLightPin
#define BackLightOff  BackLightPort->BSRR  = BackLightPin
//------------------层板电源控制J5、J6、J9共用一个控制电源
#define LayPowerPort  GPIOB         //高电启动电源，低电平关闭电源
#define LayPowerPin   GPIO_Pin_8
#define LayPowerOn    LayPowerPort->BSRR = LayPowerPin   //启动电源
#define LayPowerOff   LayPowerPort->BRR  = LayPowerPin   //关闭电源

#define gDatasize    128      	//串口最大数据包容量
#define arrysize  25       	//每个发送端口待发送缓存排序个数
#define ReSendWaitTime  50 	//重发间隔时间单位ms
#define SendNopTime     5  	//发送等待时间单位ms
#define maxresendcount  5   //最大发送次数
#define unlocktime   2000 //开锁时间
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
  unsigned short MainIDLE  :1;   //主柜空闲标志：0-空闲，1-非空闲状态
  unsigned short CabBD     :1;   //柜控制板标志：0-非柜控制板，1-柜控制板
  unsigned short LayBD     :1;   //层控制制板标志：0-非层控制板，1-层控制板
  unsigned short SetBD     :1;   //位控制板标志：0-非位控制板，1-位控制板
  unsigned short LayPownOn :1;   //层板通电标志：0-未通电，1-已通电
  unsigned short WaitAck   :1;   //等待应答--发送完后需要等待应答，如果接收到应答，则清除一个发送缓存：0-未标志，1-在等待应答  
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

typedef struct _stSys
{
  stTimesdef        Time;         //相关时间变量
  stSWdef           SwData;       //主机标志
  stReqdef          Req;         //请求类标志
  stStadef          Sta;          //状态码
  stFlgdef          Flag;         //相关标志位
  stAckQdef         AckQ;         //标志应答标志，0-不需要，1-需要应答相应接口
  stBufferdef       buffer;       //串口数据缓存
  stSendCountdef    ReSend;
}stSysdef;



extern void AMP01_Configuration(void);
extern void AMP01_Server(void);

void AMP01_Loop(void);
void MainCabinet_IDLEServer(void);  //主柜空闲服务程序



void Send_Server(void);




void Msg_Process(enCCPortDef Port,unsigned char* pBuffer,unsigned short length);        //消息处理
void Msg_ProcessCB(enCCPortDef Port,unsigned char* pBuffer,unsigned short length);      //柜消息处理
void Msg_ProcessLY(enCCPortDef Port,unsigned char* pBuffer,unsigned short length);//层消息处理

void Msg_ProcessPcPort(enCCPortDef Port,unsigned char* pBuffer,unsigned short length);
void Msg_ProcessCbPort(enCCPortDef Port,unsigned char* pBuffer,unsigned short length);
void Msg_ProcessCaPort(enCCPortDef Port,unsigned char* pBuffer,unsigned short length);
void Msg_ProcessLyPort(enCCPortDef Port,unsigned char* pBuffer,unsigned short length);

void CMD_Process(unsigned char* pBuffer,unsigned short length);
void ackFrame(enCCPortDef Port,unsigned char dir);
//=================================软件接口ST=============================================================
unsigned short Check_SendBuff(enCCPortDef Port);                                //检查相应端口待发送缓存
unsigned short Releas_OneBuffer(enCCPortDef Port);        //释放一个发送缓存
unsigned short AddSendData(enCCPortDef Port,unsigned char* pBuffer,unsigned short length);
unsigned short PCnet_Send(unsigned char* pBuffer,unsigned short length);      //往PC发送消息
unsigned short Cabinet_Send(unsigned char* pBuffer,unsigned short length);    //往副柜发送消息
unsigned short Laynet_Send(unsigned char* pBuffer,unsigned short length);     //往层板发送消息
unsigned short CardPort_Send(unsigned char* pBuffer,unsigned short length);   //往读卡器接口发数据

//=================================硬件接口ST==============================================================
void Receive_Server(void);
unsigned short HW_SendBuff(enCCPortDef Port,unsigned char* pBuffer,unsigned short length);    //通过相应端口发送数据
void SwitchID_Server(void);
void LockServer(void);
void RequestServer(void);
void StatusServer(void);

//=================================配置函数ST==============================================================
void COMM_Configuration(void);
void SwitchID_Configuration(void);
void GenyConfiguration(void);   //常规接口配置，背光，锁，电源控制

//=================================时间函数ST==============================================================
void Tim_Server(void);
void AMPdelaymS(unsigned  short time);

#endif
