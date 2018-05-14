//=========================================================
//----------------------低功耗测试


#ifdef PwrTest
#include "PwrTest.H"


#include "stm32f10x_pwr.h"
#include "stm32f10x_exti.h"
#include "stm32f10x_nvic.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_rtc.h"
#include "stm32f10x_bkp.h"

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




//extern vu32 TimingDelay;
ErrorStatus HSEStartUpStatus;

u32 SYSTIME	=	0;

u8	LedFlag	=	0;


/* Private function prototypes -----------------------------------------------*/
void SYSCLKConfig_STOP001(void);
void RCC_Configuration001(void);
void GPIO_Configuration001(void);
void EXTI_Configuration001(void);
void RTC_Configuration001(void);
void NVIC_Configuration001(void);
void SysTick_Configuration001(void);
//void Delay001(vu32 nTime);

/*******************************************************************************
* 函数名		:	
* 功能描述	:	 
* 输入		:	
* 输出		:
* 返回 		:
*******************************************************************************/
void PwrTest_Configuration(void)
{
	SYS_Configuration();						//系统配置 STM32_SYS.H	
	SysTick_DeleyS(2);						//SysTick延时nS
//	SysTick_Configuration(1000);		//系统嘀嗒时钟配置72MHz,单位为uS----定时扫描PC006V21_Server
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);
	
//	PWM_OUT(TIM1,PWM_OUTChannel3,1,500);	//PWM设定-20161127版本	占空比1/1000
	
	GPIO_Configuration_OPP50	(GPIOA,	GPIO_Pin_8);			//SYSLED//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605
	GPIO_Configuration_OPP50	(GPIOB,	GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);			//SYSLED//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605
	
	EXTI_Configuration_ITF		(GPIOA,	GPIO_Pin_0);		//外部下降沿中断配置,抢占1，响应1--20171213
//	GPIO_Configuration_OPP50	(GPIOA,	GPIO_Pin_8);			//SYSLED//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605

//  /* Clock configuration */
//  RCC_Configuration001();
	
//	SYS_Configuration();						//系统配置 STM32_SYS.H	

  /* Enable PWR and BKP clock */
//  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);

//  /* GPIO configuration */
//  GPIO_Configuration001();

//	GPIO_Configuration_OPP50	(GPIOA,	GPIO_Pin_8);			//SYSLED//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605
//	GPIO_Configuration_OPP50	(GPIOB,	GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);			//SYSLED//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605

//  /* Configure EXTI Line to generate an interrupt on falling edge */
//  EXTI_Configuration001();
//	EXTI_Configuration_ITF		(GPIOA,	GPIO_Pin_0);		//外部下降沿中断配置,抢占1，响应1--20171213

//  /* Configure RTC clock source and prescaler */
//  RTC_Configuration();

  /* NVIC configuration */
//  NVIC_Configuration001();

  /* Configure the SysTick to generate an interrupt each 1 millisecond */
//  SysTick_Configuration001();
//	SysTick_Configuration(1000);		//系统嘀嗒时钟配置72MHz,单位为uS----定时扫描PC006V21_Server

//  /* Turn on led connected to GPIO_LED Pin6 */
  GPIO_SetBits(GPIO_LED, GPIO_Pin_14); 
  
  while (1)
  {
    /* Insert 1.5 second delay */
//    SysTick_DeleymS(500);
		while(SYSTIME++<10)
		{
			
			SysTick_DeleymS(500);
			GPIO_Toggle	(GPIOA,	GPIO_Pin_8);		//将GPIO相应管脚输出翻转----V20170605
		}
		SYSTIME	=0;
//    /* Wait till RTC Second event occurs */
//    RTC_ClearFlag(RTC_FLAG_SEC);
//    while(RTC_GetFlagStatus(RTC_FLAG_SEC) == RESET);

//    /* Alarm in 3 second */
//    RTC_SetAlarm(RTC_GetCounter()+ 3);
//    /* Wait until last write operation on RTC registers has finished */
//    RTC_WaitForLastTask();

//    /* Turn off led connected to GPIO_LED Pin6 */
    GPIO_ResetBits(GPIO_LED, GPIO_Pin_12|GPIO_Pin_13); 

    /* Request to enter STOP mode with regulator in low power mode*/
    PWR_EnterSTOPMode(PWR_Regulator_LowPower, PWR_STOPEntry_WFI);
    
    /* At this stage the system has resumed from STOP mode -------------------*/
    /* Turn on led connected to GPIO_LED Pin6 */
    GPIO_SetBits(GPIO_LED, GPIO_Pin_12|GPIO_Pin_13); 

    /* Configures system clock after wake-up from STOP: enable HSE, PLL and select 
       PLL as system clock source (HSE and PLL are disabled in STOP mode) */
    SYSCLKConfig_STOP001();
  }
	
}

/*******************************************************************************
* 函数名		:	
* 功能描述	:	 
* 输入		:	
* 输出		:
* 返回 		:
*******************************************************************************/
void PwrTest_Server(void)
{
	if(Trigger_Line.Trigger_Line0)
	{
//		if(LedFlag)
//		{
//			LedFlag=0;
//		}
//		else
//		{
//			LedFlag=1;
//		}
		DeleyuS(1000);
		GPIO_Toggle	(GPIOB,	GPIO_Pin_14);		//将GPIO相应管脚输出翻转----V20170605
		GPIO_Toggle	(GPIOB,	GPIO_Pin_15);		//将GPIO相应管脚输出翻转----V20170605
//		RCC_Configuration_HSE();			//配置系统时钟--使用外部高速晶振
//			SysTick->CTRL	= SysTick_CTRL_CLKSOURCE_Msk |SysTick_CTRL_TICKINT_Msk	|	SysTick_CTRL_ENABLE_Msk;	
//		SysTick_ITConfig(ENABLE);
//		GPIO_Toggle	(GPIOB,	GPIO_Pin_12|GPIO_Pin_15);		//将GPIO相应管脚输出翻转----V20170605
//		GPIO_Toggle	(GPIOB,	GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);		//将GPIO相应管脚输出翻转----V20170605
	}
	SYSTIME++;
	if(SYSTIME>=5000)
	{
		SYSTIME	=0;
////		SysTick->CTRL &= SysTick_Counter_Disable;			//SysTick_CounterCmd(SysTick_Counter_Disable);	//关闭计数
////		SysTick_ITConfig(DISABLE);					//关闭中断
//		SysTick->CTRL = 0;									//SysTick_ITConfig(DISABLE);					//关闭中断
//		
//		SysTick_DeleyS(1);
//		while(SysTick->CTRL	!= 0)
////		RCC_HSICmd(ENABLE);			//配置系统时钟--使用内部高速晶振
//		GPIO_Toggle	(GPIOB,	GPIO_Pin_12|GPIO_Pin_13);		//将GPIO相应管脚输出翻转----V20170605
//		PWR_EnterSTOPMode(PWR_Regulator_LowPower, PWR_STOPEntry_WFI);//进入停止模式
//		
////		SYS_Configuration();						//系统配置 STM32_SYS.H	
////		EXTI_Configuration_ITR		(GPIOA,	GPIO_Pin_0);		//外部上升沿中断配置,抢占1，响应1--20171213
//		GPIO_Toggle	(GPIOB,	GPIO_Pin_12|GPIO_Pin_13);		//将GPIO相应管脚输出翻转----V20170605
////		
//		SYSCLKConfig_STOP();
//		SysTick_Configuration(1000);		//系统嘀嗒时钟配置72MHz,单位为uS----定时扫描PC006V21_Server
	}

	if(SYSTIME%500==0)
	{
//		GPIO_Toggle	(GPIOA,	GPIO_Pin_8);		//将GPIO相应管脚输出翻转----V20170605
//		if(LedFlag)
//		GPIO_Toggle	(GPIOB,	GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);		//将GPIO相应管脚输出翻转----V20170605
	}
}



/*******************************************************************************
* Function Name  : RCC_Configuration
* Description    : Configures the different system clocks.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void RCC_Configuration001(void)
{
  /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration -----------------------------*/   
  /* RCC system reset(for debug purpose) */
  RCC_DeInit();

  /* Enable HSE */
  RCC_HSEConfig(RCC_HSE_ON);

  /* Wait till HSE is ready */
  HSEStartUpStatus = RCC_WaitForHSEStartUp();

  if(HSEStartUpStatus == SUCCESS)
  {
    /* Enable Prefetch Buffer */
    FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);

    /* Flash 2 wait state */
    FLASH_SetLatency(FLASH_Latency_2);
 
    /* HCLK = SYSCLK */
    RCC_HCLKConfig(RCC_SYSCLK_Div1); 
  
    /* PCLK2 = HCLK */
    RCC_PCLK2Config(RCC_HCLK_Div1); 

    /* PCLK1 = HCLK/2 */
    RCC_PCLK1Config(RCC_HCLK_Div2);

    /* PLLCLK = 8MHz * 9 = 72 MHz */
    RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);

    /* Enable PLL */ 
    RCC_PLLCmd(ENABLE);

    /* Wait till PLL is ready */
    while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
    {
    }

    /* Select PLL as system clock source */
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

    /* Wait till PLL is used as system clock source */
    while(RCC_GetSYSCLKSource() != 0x08)
    {
    }
  }
}

/*******************************************************************************
* Function Name  : SYSCLKConfig_STOP
* Description    : Configures system clock after wake-up from STOP: enable HSE, PLL
*                  and select PLL as system clock source.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SYSCLKConfig_STOP001(void)
{
  /* Enable HSE */
  RCC_HSEConfig(RCC_HSE_ON);

  /* Wait till HSE is ready */
  HSEStartUpStatus = RCC_WaitForHSEStartUp();

  if(HSEStartUpStatus == SUCCESS)
  {
    /* Enable PLL */ 
    RCC_PLLCmd(ENABLE);

    /* Wait till PLL is ready */
    while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
    {
    }

    /* Select PLL as system clock source */
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

    /* Wait till PLL is used as system clock source */
    while(RCC_GetSYSCLKSource() != 0x08)
    {
    }
  }
}

/*******************************************************************************
* Function Name  : GPIO_Configuration
* Description    : Configures the different GPIO ports.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void GPIO_Configuration001(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  /* Enable Key Button GPIO Port, GPIO_LED and AFIO clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIO_KEY_BUTTON | RCC_APB2Periph_GPIO_LED 
                         | RCC_APB2Periph_AFIO, ENABLE);

  /* Configure GPIO_LED Pin 6, Pin 7 and Pin 8 as Output push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14| GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIO_LED, &GPIO_InitStructure);

  /* Configure Key Button GPIO Pin as input floating */
  GPIO_InitStructure.GPIO_Pin = GPIO_PIN_KEY_BUTTON;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIO_KEY_BUTTON, &GPIO_InitStructure);
}

/*******************************************************************************
* Function Name  : EXTI_Configuration
* Description    : Configures EXTI Lines.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void EXTI_Configuration001(void)
{
  EXTI_InitTypeDef EXTI_InitStructure;

  /* Connect Key Button EXTI Line to Key Button GPIO Pin */
  GPIO_EXTILineConfig(GPIO_PORT_SOURCE_KEY_BUTTON, GPIO_PIN_SOURCE_KEY_BUTTON);

  /* Configure Key Button EXTI Line to generate an interrupt on falling edge */  
  EXTI_InitStructure.EXTI_Line = EXTI_LINE_KEY_BUTTON;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);

//  /* Configure EXTI Line17(RTC Alarm) to generate an interrupt on rising edge */
//  EXTI_ClearITPendingBit(EXTI_Line17);
//  EXTI_InitStructure.EXTI_Line = EXTI_Line17;
//  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
//  EXTI_Init(&EXTI_InitStructure);    
}

/*******************************************************************************
* Function Name  : RTC_Configuration
* Description    : Configures RTC clock source and prescaler.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void RTC_Configuration001(void)
{
  /* RTC clock source configuration ------------------------------------------*/
  /* Allow access to BKP Domain */
  PWR_BackupAccessCmd(ENABLE);

  /* Reset Backup Domain */
  BKP_DeInit();
  
  /* Enable the LSE OSC */
  RCC_LSEConfig(RCC_LSE_ON);
  /* Wait till LSE is ready */
  while(RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET)
  {
  }

  /* Select the RTC Clock Source */
  RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);

  /* Enable the RTC Clock */
  RCC_RTCCLKCmd(ENABLE);

  /* RTC configuration -------------------------------------------------------*/
  /* Wait for RTC APB registers synchronisation */
  RTC_WaitForSynchro();

  /* Set the RTC time base to 1s */
  RTC_SetPrescaler(32767);  
  /* Wait until last write operation on RTC registers has finished */
  RTC_WaitForLastTask();

  /* Enable the RTC Alarm interrupt */
  RTC_ITConfig(RTC_IT_ALR, ENABLE);
  /* Wait until last write operation on RTC registers has finished */
  RTC_WaitForLastTask();
}

/*******************************************************************************
* Function Name  : NVIC_Configuration
* Description    : Configures NVIC and Vector Table base location.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void NVIC_Configuration001(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;

  /* Set the Vector Table base location at 0x08000000 */ 
  NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);   

  /* 2 bits for Preemption Priority and 2 bits for Sub Priority */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

//  NVIC_InitStructure.NVIC_IRQChannel = RTCAlarm_IRQChannel;
//  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
//  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
//  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//  NVIC_Init(&NVIC_InitStructure);

  NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQChannel;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_Init(&NVIC_InitStructure);
}

/*******************************************************************************
* Function Name  : SysTick_Configuration
* Description    : Configures the SysTick to generate an interrupt each 1 millisecond.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SysTick_Configuration001(void)
{
  /* Select AHB clock(HCLK) as SysTick clock source */
  SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);

  /* Set SysTick Priority to 3 */
  NVIC_SystemHandlerPriorityConfig(SystemHandler_SysTick, 3, 0);
   
  /* SysTick interrupt each 1ms with HCLK equal to 72MHz */
  SysTick_SetReload(72000);

  /* Enable the SysTick Interrupt */
  SysTick_ITConfig(ENABLE);
}

///*******************************************************************************
//* Function Name  : Delay
//* Description    : Inserts a delay time.
//* Input          : nTime: specifies the delay time length, in milliseconds.
//* Output         : None
//* Return         : None
//*******************************************************************************/
//void Delay001(u32 nTime)
//{
//  /* Enable the SysTick Counter */
//  SysTick_CounterCmd(SysTick_Counter_Enable);
//  
//  TimingDelay = nTime;

//  while(TimingDelay != 0);

//  /* Disable the SysTick Counter */
//  SysTick_CounterCmd(SysTick_Counter_Disable);
//  /* Clear the SysTick Counter */
//  SysTick_CounterCmd(SysTick_Counter_Clear);
//}


#endif
