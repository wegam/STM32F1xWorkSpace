#ifdef PL013V20

#include "PL013V20.H"
#include "CD4511.H"



#include "SWITCHID.H"
#include "STM32F10x_BitBand.H"
#include "STM32_GPIO.H"
#include "STM32_SYS.H"
#include "STM32_SYSTICK.H"
#include "STM32_WDG.H"
#include "STM32_PWM.H"



#include "STM32_USART.H"
#include "STM32_TOOLS.H"		//数据校验工具


#include "string.h"				//串和内存操作函数头文件



//************485通讯数据
CD4511_Pindef	CD4511;

SWITCHID_CONF	SWITCHID;			//拔码开关



u8 SwitchID=0;				//拔码开关地址 //单元板ID----从右到左依次为增高，最右边为最低位，最高位为1表示测试模式，测试模式下从0到9循环显示

vu8		LongDsp		=	0;			//0--在显示时间内显示，1-常亮,不再显示倒计时
vu32	DSPTIME		=	0;		//显示总时间--单位mS
vu32	DSPCount	=	0;		//显示计时--单位mS
vu32	SYSTIME		=	0;		//循环计时变量
vu32	DSPNum		=	0;		//显示数据
u8		PowerOn		=	0;		//上电PowerOn为0，前2秒显示ID 0.5秒闪烁






/*******************************************************************************
* 函数名		:	
* 功能描述	:	 
* 输入		:	
* 输出		:
* 返回 		:
*******************************************************************************/
void PL013V20_Configuration(void)
{
	
	SYS_Configuration();					//系统配置---打开系统时钟 STM32_SYS.H
	
	GPIO_DeInitAll();							//将所有的GPIO关闭----V20170605
	

}
/*******************************************************************************
* 函数名		:	
* 功能描述	:	 
* 输入		:	
* 输出		:
* 返回 		:
*******************************************************************************/
void PL013V20_Server(void)
{
	//循环周期1mS
//	u8 status=0;	
	
	IWDG_Feed();											//独立看门狗喂狗	
	SYSTIME++;	
	if(SYSTIME>=5000)	//1秒
	{
		SYSTIME=0;
	}
	
}



#endif
