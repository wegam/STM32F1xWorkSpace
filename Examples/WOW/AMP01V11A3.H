#ifndef __AMP01V11A2_H
#define __AMP01V11A2_H


#include	"AMP_PHY.H"


//------------------锁接口J10
#define SYSLEDPort    GPIOA         //锁控制接口，高电平开锁
#define SYSLEDPin     GPIO_Pin_0
//------------------通讯接口--PC
#define CommPcPort        USART2
//------------------通讯接口--柜口
#define CommCbPort       USART1
#define CommCbCTLPort    GPIOA         //锁控制接口，高电平开锁
#define CommCbCTLPin     GPIO_Pin_8
//------------------通讯接口--层板接口
#define CommLayPort       UART4
#define CommLayCTLPort    GPIOA         //锁控制接口，高电平开锁
#define CommLayCTLPin     GPIO_Pin_12
//------------------通讯接口--读卡器接口
#define CommCardPort      USART3
#define CommCardCTLPort   GPIOC         //锁控制接口，高电平开锁
#define CommCardCTLPin    GPIO_Pin_8
#define CommCardBaudRate  19200         //读卡器通讯波特率

//------------------锁接口J10
#define LockDrPort    GPIOC         //锁控制接口，高电平开锁
#define LockDrPin     GPIO_Pin_12
#define LockSiPort    GPIOB         //锁信号，检测到低电平表示锁已开
#define LockSiPin     GPIO_Pin_1
#define UnLock        LockDrPort->BSRR  = LockDrPin    //开锁
#define ResLock       LockDrPort->BRR   = LockDrPin    //释放锁驱动
#define GetLockSts    LockSiPort->IDR & LockSiPin      //获取锁的状态，如果为0，表示锁已开
//------------------背光接口J11的VCC和EN脚
#define BackLightPort GPIOB         //高电平关闭，低电平点亮
#define BackLightPin  GPIO_Pin_0
#define BackLightOn   BackLightPort->BSRR   = BackLightPin
#define BackLightOff  BackLightPort->BRR    = BackLightPin
//------------------层板电源控制J5、J6、J9共用一个控制电源
#define LayPowerPort  GPIOB         //高电启动电源，低电平关闭电源
#define LayPowerPin   GPIO_Pin_2
#define LayPowerOn    LayPowerPort->BSRR = LayPowerPin   //启动电源
#define LayPowerOff   LayPowerPort->BRR  = LayPowerPin   //关闭电源



extern stAMPProdef   AMPPro;

void AMP01V11A3_Configuration(void);
void AMP01V11A3_Server(void);

//void AMP01V11_Loop(void);


unsigned short HW_SendBuff(enCCPortDef Port,unsigned char* pBuffer,unsigned short length);
//=================================时间函数ST==============================================================
void Tim_Server(void);


#endif
