#include "LOCK.H"	


#include "STM32_GPIO.H"
#include "STM32_SYSTICK.H"

/*******************************************************************************
* 函数名			:	function
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
void LockInitialize(sLockSeDef *LockSe)		//启用锁--配置
{
	//=====================================配置锁驱动
	GPIO_Configuration_OPP50	(LockSe->DrGPIOx,LockSe->DrGPIO_Pin_n);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605
	//=====================================配置锁反馈
	GPIO_Configuration_IPU(LockSe->SeGPIOx,LockSe->SeGPIO_Pin_n);					//将GPIO相应管脚配置为上拉输入模式----V20170605
	
	//=====================================初始化状态标志
	LockSe->sLockFlg.LockFlg	=	0;			//bit0：0-无操作,	1-有操作请求(控制锁的状态/需要上报状态）
	LockSe->sLockFlg.LockOn		=	0;			//bit1：0-无状态，	1-锁已锁上
	LockSe->sLockFlg.LockOff	=	0;			//bit2：0-无状态，	1-锁已打开
	LockSe->sLockFlg.LockSts	=	0;			//bit3：0-已释放，	1-已闭合
	LockSe->sLockFlg.LockTout	=	0;			//bit4：0-未超时，	1-已超时(锁打开超时或者锁状态反馈异常)
	
	//=====================================初始化吸合时间
	LockSe->LockTimeCountdown	=	50;			//开锁倒计时 计时到0时释放锁，如果LockTimeOut不为0，则开锁	
}
/*******************************************************************************
* 函数名			:	function
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
void LockServer(sLockSeDef *LockSe)
{
	//=====================================锁驱动控制
	if(LockSe->LockTimeCountdown	> 0)		//时间大于0，锁驱动
	{
		LockSe->LockTimeCountdown--;				//倒计数
		GPIO_SetBits((LockSe->DrGPIOx),(LockSe->DrGPIO_Pin_n));		//锁驱动打开--S8050
//		GPIO_ResetBits(LockSe->DrGPIOx,LockSe->DrGPIO_Pin_n);			//锁驱动打开--S8550
		
		if(GPIO_ReadInputDataBit(LockSe->SeGPIOx,LockSe->SeGPIO_Pin_n))		//检测锁反馈状态---低电平表示未打开
		{
			if(LockSe->LockTimeCountdown	<=	1)	//倒计数完成
			{
				LockSe->sLockFlg.LockFlg	=	1;			//bit0：0-无操作,	1-有操作请求(控制锁的状态/需要上报状态）
				LockSe->sLockFlg.LockOn		=	0;			//bit1：0-无状态，	1-锁已锁上
				LockSe->sLockFlg.LockOff	=	0;			//bit2：0-无状态，	1-锁已打开
				LockSe->sLockFlg.LockSts	=	1;			//bit3：0-已释放，	1-已闭合
				LockSe->sLockFlg.LockTout	=	1;			//bit4：0-未超时，	1-已超时(锁打开超时或者锁状态反馈异常)
				
				LockSe->LockTimeCountdown	=	0;			//清除倒计数
				
				GPIO_ResetBits(LockSe->DrGPIOx,LockSe->DrGPIO_Pin_n);			//锁驱动关闭--S8050
//				GPIO_SetBits((LockSe->DrGPIOx),(LockSe->DrGPIO_Pin_n));		//锁驱动关闭--S8550
			}
			LockSe->SeTimeCountUp			=	0;
		}
		else
		{
			
			if(LockSe->SeTimeCountUp++	>=5)
			{
				LockSe->SeTimeCountUp			=	0;
				LockSe->sLockFlg.LockFlg	=	1;			//bit0：0-无操作,	1-有操作请求(控制锁的状态/需要上报状态）
				LockSe->sLockFlg.LockOn		=	0;			//bit1：0-无状态，	1-锁已锁上
				LockSe->sLockFlg.LockOff	=	1;			//bit2：0-无状态，	1-锁已打开
				LockSe->sLockFlg.LockSts	=	0;			//bit3：0-已释放，	1-已闭合
				LockSe->sLockFlg.LockTout	=	0;			//bit4：0-未超时，	1-已超时(锁打开超时或者锁状态反馈异常)
				
				LockSe->LockTimeCountdown	=	0;			//清除倒计数
				
				GPIO_ResetBits(LockSe->DrGPIOx,LockSe->DrGPIO_Pin_n);			//锁驱动关闭--S8050
//				GPIO_SetBits((LockSe->DrGPIOx),(LockSe->DrGPIO_Pin_n));		//锁驱动关闭--S8550
			}
		}		
	}
	else
	{
		GPIO_ResetBits(LockSe->DrGPIOx,LockSe->DrGPIO_Pin_n);			//锁驱动关闭--S8050
//		GPIO_SetBits((LockSe->DrGPIOx),(LockSe->DrGPIO_Pin_n));		//锁驱动关闭--S8550
		if(LockSe->sLockFlg.LockFlg	==	1)			//有待处理事件未处理完
		{
			return;
		}
		//=====================================锁驱状态检测
		if(GPIO_ReadInputDataBit(LockSe->SeGPIOx,LockSe->SeGPIO_Pin_n))		//检测锁反馈状态---低电平表示未打开
		{
			if(LockSe->sLockFlg.LockSts	==	0)		//抽屉收回
			{
				LockSe->sLockFlg.LockFlg	=	1;			//bit0：0-无操作,	1-有操作请求(控制锁的状态/需要上报状态）
				LockSe->sLockFlg.LockOn		=	1;			//bit1：0-无状态，	1-锁已锁上
				LockSe->sLockFlg.LockOff	=	0;			//bit2：0-无状态，	1-锁已打开
				LockSe->sLockFlg.LockSts	=	1;			//bit3：0-已释放，	1-已闭合
				LockSe->sLockFlg.LockTout	=	0;			//bit4：0-未超时，	1-已超时(锁打开超时或者锁状态反馈异常)
			}
		}
		else
		{
			if(LockSe->sLockFlg.LockSts	==	1)		//抽屉强制打开
			{
				LockSe->sLockFlg.LockFlg	=	1;			//bit0：0-无操作,	1-有操作请求(控制锁的状态/需要上报状态）
				LockSe->sLockFlg.LockOn		=	0;			//bit1：0-无状态，	1-锁已锁上
				LockSe->sLockFlg.LockOff	=	1;			//bit2：0-无状态，	1-锁已打开
				LockSe->sLockFlg.LockSts	=	0;			//bit3：0-已释放，	1-已闭合
				LockSe->sLockFlg.LockTout	=	0;			//bit4：0-未超时，	1-已超时(锁打开超时或者锁状态反馈异常)
			}
		}
	}	
}

/*******************************************************************************
* 函数名			:	function
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
void LockSetOn(sLockSeDef *LockSe,unsigned long LockOnTime)		//打开锁
{
	if(LockOnTime	==	0)	//未设定锁吸合时间
	{
		LockSe->LockTimeCountdown	=	DefaultLockOnTime;		//默认锁吸合时间数量级
	}
	else
	{
		LockSe->LockTimeCountdown	=	LockOnTime;						//锁吸合时间
	}
}
/*******************************************************************************
* 函数名			:	function
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
void LockSetOff(sLockSeDef *LockSe)		//释放锁
{
	LockSe->LockTimeCountdown	=	0;			//开锁倒计时 计时到0时释放锁，如果LockTimeOut不为0，则开锁	
}

/*******************************************************************************
* 函数名			:	function
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
unsigned char LockGetStatus(sLockSeDef *LockSe)
{
	unsigned char	Status	=	0;
	unsigned long	*P	=	(unsigned long*)&(LockSe->sLockFlg);
	if(LockSe->sLockFlg.LockFlg	==	1)
	{
		Status	=	0xFF&*P;
		return Status;
	}
	return 0;
}

