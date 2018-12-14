/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : usb_pwr.c
* Author             : MCD Application Team
* Version            : V2.2.0
* Date               : 06/13/2008
* Description        : Connection/disconnection & power management
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/


/******************************** ˵��20160912**********************************
********************************************************************************
* ���ܣ�����USB���ӡ��Ͽ�����
* 
* 
* 
* 
* 
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "usb_Initialize.h"

#include "stm32f10x_type.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_nvic.h"
#include "stm32f10x_gpio.h"
//#include "stm32f10x_lib.h"
//#include "usb_lib.h"
//#include "usb_conf.h"
//#include "usb_pwr.h"
//#include "hw_config.h"



//#include "usb_regs.h"			//���ڼĴ�������
#include "usb_init.h"			//���ڶ˵��������������жϴ���

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/*******************************************************************************
*������			:	function
*��������		:	function
*����				: 
*����ֵ			:	��
*�޸�ʱ��		:	��
*�޸�˵��		:	��
*ע��				:	wegam@sina.com
*******************************************************************************/
void USB_Initialize(void)
{
	//1----------����USBʱ��
  USB_ClockInitialize();     //USBʱ�ӳ�ʼ��
  
	//2----------����USB�ж�
  USB_NvicInitialize();      //USB�жϳ�ʼ��
	
	//3----------����USB�ж�
	USB_GpioInitialize();
	
	//3----------���⴮�ڳ�ʼ��
	VirtualCom_Initialize();
	
	//USB_Init();
}
/*******************************************************************************
*������			:	function
*��������		:	function
*����				: 
*����ֵ			:	��
*�޸�ʱ��		:	��
*�޸�˵��		:	��
*ע��				:	wegam@sina.com
*******************************************************************************/
void USB_ClockInitialize(void)
{
  /* USBCLK = PLLCLK / 1.5 */
  RCC_USBCLKConfig(RCC_USBCLKSource_PLLCLK_1Div5);
  /* Enable USB clock */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USB, ENABLE);
  /* Enable GPIOA*/
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
}

/*******************************************************************************
*������			:	function
*��������		:	function
*����				: 
*����ֵ			:	��
*�޸�ʱ��		:	��
*�޸�˵��		:	��
*ע��				:	wegam@sina.com
*******************************************************************************/
void USB_GpioInitialize(void)
{  
//  GPIO_InitTypeDef GPIO_InitStructure;
  
//  /* Configure USART1 Rx (PA.10) as input floating */
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
//  GPIO_Init(GPIOA, &GPIO_InitStructure);

//  /* Configure USART1 Tx (PA.09) as alternate function push-pull */
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
//  GPIO_Init(GPIOA, &GPIO_InitStructure);
  

}
/*******************************************************************************
* Function Name  : USB_Interrupts_Config
* Description    : Configures the USB interrupts
* Input          : None.
* Return         : None.
*******************************************************************************/
void USB_NvicInitialize(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;

#ifdef  VECT_TAB_RAM
  /* Set the Vector Table base location at 0x20000000 */
  NVIC_SetVectorTable(NVIC_VectTab_RAM, 0x0);
#else  /* VECT_TAB_FLASH */
  /* Set the Vector Table base location at 0x08000000 */
  NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);
#endif

  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

  NVIC_InitStructure.NVIC_IRQChannel = USB_LP_CAN_RX0_IRQChannel;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}
/*******************************************************************************
*������			:	function
*��������		:	function
*����				: 
*����ֵ			:	��
*�޸�ʱ��		:	��
*�޸�˵��		:	��
*ע��				:	wegam@sina.com
*******************************************************************************/
void VirtualCom_Initialize(void)
{  
  pInformation = &Device_Info;			//������豸���ϲ���,�����ȫ����������̬��	//pInformation ��һ��ָ��Device_Info ��ָ��
  pInformation->ControlState = 2;
  pProperty = &VirtualCom_DeviceProperty;			//pProperty ��һ��ָ�룬ָ��DEVICE_PROP ������豸���Բ��֣���usb_prop.c->Line 60
																		//�豸���Բ��ְ���һЩ��������������Ҳ��������������һ���ǽ������Ļ�������ַ��һ��
																		//�����İ��ĳ��ȡ��������ֽڱ�ʾ�ġ�
																		
  pUser_Standard_Requests = &User_Standard_Requests;		//��׼����
  /* Initialize devices one by one */
  pProperty->Init();			//��ʼ��--��ʼ����ɺ󣬺�����¼��������жϴ���������,usb_istr.c->USB_Istr->CTR_LP()		
													//usb_prop.c->Device_Property->Virtual_Com_Port_init;	Virtual_Com_Port_init
													//���������һ��ͨ�õ����ԣ���ָ���൱��ʵ�����׵�USB ���ͷ��ȥ�������������￴
													//��ȥ����һ��pProperty->Init();ʵ�������е���DEVICE_PROP �е�
													//Virtual_Com_Port_init�������������
}
/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/
