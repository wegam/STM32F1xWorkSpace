#ifdef ADC_Temperature
#include "ADC_Temperature.H"


#include "STM32_SYS.H"
#include "STM32_SYSTICK.H"
#include "STM32_USART.H"
#include "STM32_TIM.H"
#include "STM32_DMA.H"
#include "STM32_PWM.H"
#include "STM32_GPIO.H"
#include "STM32_ADC.H"
#include "STM32_DAC.H"
#include "STM32_RCC.H"


#define ADC_TEST_BUFFERSIZE 128

u16	SYSTIME	=	0;
u16 ADCBuffer=0;
float Temperature=0.0;

RCC_ClocksTypeDef RCC_ClocksStatus0;
/*******************************************************************************
* 函数名		:	
* 功能描述	:	 
* 输入		:	
* 输出		:
* 返回 		:
*******************************************************************************/
void ADC_Temperature_Configuration(void)
{
	SYS_Configuration();											//系统配置
	GPIO_DeInitAll();													//将所有的GPIO关闭----V20170605
	SysTick_Configuration(1000);						//系统嘀嗒时钟配置72MHz,单位为uS

	USART_DMA_ConfigurationNR	(USART2,115200,ADC_TEST_BUFFERSIZE);	//USART_DMA配置--查询方式，不开中断
	
	PWM_OUT(TIM2,PWM_OUTChannel1,1,500);			//PWM设定-20161127版本	占空比1/1000

	ADC_TempSensorConfiguration((u32*)&ADCBuffer);																									//STM32内部温度传感器配置
}
/*******************************************************************************
* 函数名		:	
* 功能描述	:	 
* 输入		:	
* 输出		:
* 返回 		:
*******************************************************************************/
void ADC_Temperature_Server(void)
{
	
	SYSTIME++;
	if(SYSTIME>=1000)
	{
		SYSTIME	=	0;
	Get_Clocks(&RCC_ClocksStatus0);
//	if(!USART_TX_DMAFlagClear(USART1))
//	{
		Temperature=Get_ADC_Temperature(ADCBuffer);														//获取内部温度传感器温度
		USART_DMAPrintf(USART2,"当前STM32内部温度为：%6.2f℃,外部高速时钟频率为：%dHz, %d, %d,  %d, %d, %d\n",Temperature,HSE_Value,RCC_ClocksStatus0.SYSCLK_Frequency,RCC_ClocksStatus0.HCLK_Frequency,RCC_ClocksStatus0.PCLK1_Frequency,RCC_ClocksStatus0.PCLK2_Frequency,RCC_ClocksStatus0.ADCCLK_Frequency);
//	}
	}
}

#endif
