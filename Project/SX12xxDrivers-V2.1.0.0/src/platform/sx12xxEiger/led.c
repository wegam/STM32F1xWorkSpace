#include "sx12xxEiger.h"

#include "led.h"



GPIO_TypeDef* LedPort[LED_NB] = { 
																	LED1_GPIO_PORT,
																	LED2_GPIO_PORT,
																	LED3_GPIO_PORT,
																	LED4_GPIO_PORT,
                                };
const uint16_t LedPin[LED_NB] = {
																	LED1_PIN,
																	LED2_PIN,
																	LED3_PIN,
																	LED4_PIN,
                                };
const uint32_t LedClk[LED_NB] = {
																	LED1_GPIO_CLK,
																	LED2_GPIO_CLK,
																	LED3_GPIO_CLK,
																	LED4_GPIO_CLK,
                                };

/*******************************************************************************
*函数名			:	function
*功能描述		:	函数功能说明
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
void LedInit( tLed led )		//LED初始化
{
    GPIO_InitTypeDef  GPIO_InitStructure;
	
    RCC_APB2PeriphClockCmd( LedClk[led], ENABLE );
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Pin = LedPin[led];
    GPIO_Init( LedPort[led], &GPIO_InitStructure );
    GPIO_WriteBit( LedPort[led], LedPin[led], LED_OFF );
}
/*******************************************************************************
*函数名			:	function
*功能描述		:	函数功能说明
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
void LedOn( tLed led )		//点亮LED
{
    GPIO_WriteBit( LedPort[led], LedPin[led], LED_ON );
}
/*******************************************************************************
*函数名			:	function
*功能描述		:	函数功能说明
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
void LedOff( tLed led )		//关闭LED
{
    GPIO_WriteBit( LedPort[led], LedPin[led], LED_OFF ); 
}
/*******************************************************************************
*函数名			:	function
*功能描述		:	函数功能说明
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
void LedToggle( tLed led )	//LED翻转显示
{
    LedPort[led]->ODR ^= LedPin[led]; 
}
