/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : main.c
* Author             : MCD Application Team
* Version            : V2.2.0
* Date               : 06/13/2008
* Description        : Audio Speaker Demo main file
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/
#ifdef	Audio_Speaker
#include "Audio_Speaker.h"
/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_lib.h"
#include "usb_lib.h"
#include "usb_desc.h"
#include "hw_config.h"
#include "usb_prop.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Extern variables ----------------------------------------------------------*/
extern u32 MUTE_DATA;
extern u16 In_Data_Offset;
extern u16 Out_Data_Offset;
extern u8 Stream_Buff[24];
extern u8 IT_Clock_Sent;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
*函数名			:	Audio_Speaker_Configuration
*功能描述		:	函数功能说明
*输入				: 
*返回值			:	无
*******************************************************************************/
void Audio_Speaker_Configuration(void)
{
#ifdef DEBUG
  debug();
#endif
	
  Set_System();
  Set_USBClock();
  USB_Config();
  USB_Init();
  Speaker_Config();
  while (1)
  {}
}
/*******************************************************************************
*函数名			:	Audio_Speaker_Configuration
*功能描述		:	函数功能说明
*输入				: 
*返回值			:	无
*******************************************************************************/
void Audio_Speaker_Server(void)
{

}


#endif
/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/
