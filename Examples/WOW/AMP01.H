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

#define ccsize  64        //串口最大数据包容量
typedef struct _stSW        //拨码数据：
{
  unsigned char ID        :6;   //拨码地 sw3~sw8为板ID号,sw3~sw8未拨时，为测试模式，背光灯闪烁
  unsigned char ICreadFlg :1;   //sw2 未拨时，读卡器的波特率为19200，拨上时波特率为9600
  unsigned char MainFlg   :1;   //sw1 未拨时，此柜为副柜，拨上时为主柜
}stSWdef;

typedef struct _stBuffer       //拨码数据：
{
  unsigned char u1rx[ccsize];   //串口1接收缓存--PC接口
  unsigned char u1tx[ccsize];   //串口1发送缓存--PC接口
  unsigned char u2rx[ccsize];   //串口1接收缓存--层板接口
  unsigned char u2tx[ccsize];   //串口1发送缓存--层板接口
  unsigned char u3rx[ccsize];   //串口1接收缓存--读卡器
  unsigned char u3tx[ccsize];   //串口1发送缓存--读卡器
  unsigned char u4rx[ccsize];   //串口1接收缓存--副柜
  unsigned char u4tx[ccsize];   //串口1发送缓存--副柜
}stBufferdef;

typedef struct _stSys
{
  unsigned short runtime;     //运行计数器
  stSWdef       SwData;       //主机标志
  stBufferdef   buffer;       //串口数据缓存
}stSysdef;



extern void AMP01_Configuration(void);
extern void AMP01_Server(void);

void USART_Server(void);
void SwitchID_Server(void);

void PCmsg_Process(unsigned char* pBuffer,unsigned short length);              //消息处理
void ICcardData_Process(unsigned char* pBuffer,unsigned short length);         //读卡器数据处理

unsigned short PCnet_Send(unsigned char* pBuffer,unsigned short length);     //往副柜发送消息
unsigned short Cabinet_Send(unsigned char* pBuffer,unsigned short length);     //往副柜发送消息
unsigned short Laynet_Send(unsigned char* pBuffer,unsigned short length);      //往层板发送消息


void GenyConfiguration(void);   //常规接口配置，背光，锁，电源控制

void LockServer(void);

void COMM_Configuration(void);
void SwitchID_Configuration(void);

#endif
