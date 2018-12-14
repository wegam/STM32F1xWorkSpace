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


/******************************** 说明20160912**********************************
********************************************************************************
* 功能：用于USB连接、断开操作
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



//#include "usb_regs.h"			//用于寄存器操作
#include "usb_init.h"			//用于端点数据输入输入中断处理

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/*******************************************************************************
*函数名			:	function
*功能描述		:	function
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
void USB_Initialize(void)
{
	//1----------开启USB时钟
  USB_ClockInitialize();     //USB时钟初始化
  
	//2----------开启USB中断
  USB_NvicInitialize();      //USB中断初始化
	
	//3----------开启USB中断
	USB_GpioInitialize();
	
	//3----------虚拟串口初始化
	VirtualCom_Initialize();
	
	//USB_Init();
}
/*******************************************************************************
*函数名			:	function
*功能描述		:	function
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
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
*函数名			:	function
*功能描述		:	function
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
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
*函数名			:	function
*功能描述		:	function
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
void VirtualCom_Initialize(void)
{  
  pInformation = &Device_Info;			//这个是设备资料部分,里面的全部变量，静态的	//pInformation 是一个指向Device_Info 的指针
  pInformation->ControlState = 2;
  pProperty = &VirtualCom_DeviceProperty;			//pProperty 是一个指针，指向DEVICE_PROP 这个是设备属性部分，在usb_prop.c->Line 60
																		//设备属性部分包含一些方法，即函数。也包括两个参数，一个是接收区的缓冲区地址，一个
																		//是最大的包的长度。都是用字节表示的。
																		
  pUser_Standard_Requests = &User_Standard_Requests;		//标准请求
  /* Initialize devices one by one */
  pProperty->Init();			//初始化--初始化完成后，后面的事件处理由中断处理函数进行,usb_istr.c->USB_Istr->CTR_LP()		
													//usb_prop.c->Device_Property->Virtual_Com_Port_init;	Virtual_Com_Port_init
													//这个属性是一个通用的属性，它指以相当于实例化套到USB 这个头上去。故我们在这里看
													//上去运行一个pProperty->Init();实际上运行的是DEVICE_PROP 中的
													//Virtual_Com_Port_init（）这个函数。
}
/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/
