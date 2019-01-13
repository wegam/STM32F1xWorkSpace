#ifndef __AMP01_H
#define __AMP01_H


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
