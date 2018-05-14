#ifndef __LOCK_H
#define __LOCK_H

#include "stdint.h"

#include "stm32f10x_gpio.h"


#include "STM32_GPIO.H"


#define	DefaultLockOnTime	50	//默认锁吸合时间数量级

typedef	struct	_LockSe				//带反馈锁控制标志及吸合时间
{
	struct
	{
		unsigned char LockFlg		:1;	//bit0：0-无操作,	1-有操作请求(控制锁的状态/需要上报状态）
		unsigned char LockOn		:1;	//bit1：0-无状态，	1-锁已锁上
		unsigned char LockOff		:1;	//bit2：0-无状态，	1-锁已打开
		unsigned char LockSts		:1;	//bit3：0-已释放，	1-已闭合
		unsigned char LockTout	:1;	//bit4：0-未超时，	1-已超时(锁打开超时或者锁状态反馈异常)
	}sLockFlg;		//药箱状态
	unsigned char	SeTimeCountUp;				//锁反馈信号，当有反馈时计数增加到一定值表示反馈有效，简单滤波效果
	unsigned long	LockTimeCountdown;		//开锁倒计时 计时到0时释放锁，如果LockTimeOut不为0，则开锁
	//-------------------------锁驱动
	GPIO_TypeDef*	DrGPIOx;
	u16	DrGPIO_Pin_n;
	//-------------------------锁反馈
	GPIO_TypeDef*	SeGPIOx;
	u16	SeGPIO_Pin_n;
}sLockSeDef;



void LockInitialize(sLockSeDef *LockSe);		//启用锁--配置
void LockServer(sLockSeDef *LockSe);
void LockSetOn(sLockSeDef *LockSe,unsigned long LockOnTime);		//打开锁
void LockSetOff(sLockSeDef *LockSe);		//释放锁
unsigned char LockGetStatus(sLockSeDef *LockSe);
    
#endif

