#ifdef SysTick_TEST
#include "SysTick_TEST.H"


#include "SteepMotor.H"
#include "STM32_TIM.H"
#include "SWITCHID.H"
#include "STM32_WDG.H"
#include "STM32_EXTI.H"
#include "STM32_GPIO.H"
#include "STM32_PWM.H"
#include "STM32_SYS.H"
#include "STM32_SYSTICK.H"
#include "STM32_CAN.H"
#include "STM32F10x_BitBand.H"
u32 SYSTIME	=	0;
/*******************************************************************************
* ������		:	
* ��������	:	 
* ����		:	
* ���		:
* ���� 		:
*******************************************************************************/
void SysTick_TEST_Configuration(void)
{
	SYS_Configuration();						//ϵͳ���� STM32_SYS.H	
	SysTick_DeleyS(2);						//SysTick��ʱnS
	SysTick_Configuration(1000);		//ϵͳ���ʱ������72MHz,��λΪuS----��ʱɨ��PC006V21_Server
	GPIO_Configuration_OPP50	(GPIOA,	GPIO_Pin_0);			//��GPIO��Ӧ�ܽ�����ΪPP(����)���ģʽ������ٶ�50MHz----V20170605
//	while(1)
//	{
////		SysTick_DeleyS(15);				//SysTick��ʱnuS
//		SysTick_DeleymS(100);								//
//		GPIO_Toggle	(GPIOA,	GPIO_Pin_0);		//��GPIO��Ӧ�ܽ������ת----V20170605
//	}
}

/*******************************************************************************
* ������		:	
* ��������	:	 
* ����		:	
* ���		:
* ���� 		:
*******************************************************************************/
void SysTick_TEST_Server(void)
{
	SYSTIME++;
	if(SYSTIME>=10000)
		SYSTIME	=0;
	if(SYSTIME%10==0)
	{
		SysTick_DeleyS(1);						//SysTick��ʱnS
		GPIO_Toggle	(GPIOA,	GPIO_Pin_0);		//��GPIO��Ӧ�ܽ������ת----V20170605
	}
}





#endif