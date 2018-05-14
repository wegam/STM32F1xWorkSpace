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
*������			:	function
*��������		:	��������˵��
*����				: 
*����ֵ			:	��
*�޸�ʱ��		:	��
*�޸�˵��		:	��
*ע��				:	wegam@sina.com
*******************************************************************************/
void LedInit( tLed led )		//LED��ʼ��
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
*������			:	function
*��������		:	��������˵��
*����				: 
*����ֵ			:	��
*�޸�ʱ��		:	��
*�޸�˵��		:	��
*ע��				:	wegam@sina.com
*******************************************************************************/
void LedOn( tLed led )		//����LED
{
    GPIO_WriteBit( LedPort[led], LedPin[led], LED_ON );
}
/*******************************************************************************
*������			:	function
*��������		:	��������˵��
*����				: 
*����ֵ			:	��
*�޸�ʱ��		:	��
*�޸�˵��		:	��
*ע��				:	wegam@sina.com
*******************************************************************************/
void LedOff( tLed led )		//�ر�LED
{
    GPIO_WriteBit( LedPort[led], LedPin[led], LED_OFF ); 
}
/*******************************************************************************
*������			:	function
*��������		:	��������˵��
*����				: 
*����ֵ			:	��
*�޸�ʱ��		:	��
*�޸�˵��		:	��
*ע��				:	wegam@sina.com
*******************************************************************************/
void LedToggle( tLed led )	//LED��ת��ʾ
{
    LedPort[led]->ODR ^= LedPin[led]; 
}
