/*
 * THE FOLLOWING FIRMWARE IS PROVIDED: (1) "AS IS" WITH NO WARRANTY; AND 
 * (2)TO ENABLE ACCESS TO CODING INFORMATION TO GUIDE AND FACILITATE CUSTOMER.
 * CONSEQUENTLY, SEMTECH SHALL NOT BE HELD LIABLE FOR ANY DIRECT, INDIRECT OR
 * CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE CONTENT
 * OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING INFORMATION
 * CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
 * 
 * Copyright (C) SEMTECH S.A.
 */
/*! 
 * \file       sx12xxEiger.c
 * \brief        
 *
 * \version    1.0
 * \date       Nov 21 2012
 * \author     Miguel Luis
 */
#include <stdint.h> 
#include "spi.h"
#include "i2c.h"
#include "ioe.h"
#include "led.h"
#include "uart.h"
#include "sx12xxEiger.h"

//#if( defined( STM32F4XX ) || defined( STM32F2XX ) || defined( STM32F429_439xx ) )

//#include "usbd_cdc_core.h"
//#include "usbd_usr.h"
//#include "usbd_desc.h"

//#else

#include "usb_regs.h"
#include "usb_core.h"
#include "usb_init.h"
#include "usb_pwr.h"
#include "usb_bsp.h"
#include "usb_sil.h"

//#endif

// System tick (1ms)
volatile uint32_t TickCounter = 0;

//#if( defined( STM32F4XX ) || defined( STM32F2XX ) || defined( STM32F429_439xx ) )

//#ifdef USB_OTG_HS_INTERNAL_DMA_ENABLED
//  #if defined ( __ICCARM__ ) /*!< IAR Compiler */
//    #pragma data_alignment=4   
//  #endif
//#endif /* USB_OTG_HS_INTERNAL_DMA_ENABLED */
//   
//__ALIGN_BEGIN USB_OTG_CORE_HANDLE    USB_OTG_dev __ALIGN_END ;

//#else

//#endif
/*******************************************************************************
*函数名			:	function
*功能描述		:	函数功能说明
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
void BoardInit( void )			//板载外设初始化--SPI初始化，LED初始化，USB初始化，其它端口初始化
{
    uint8_t i;

    /* Setup SysTick Timer for 1 us interrupts ( not too often to save power ) */
    if( SysTick_Config( SystemCoreClock / 1000 ) )
    { 
        /* Capture error */ 
        while (1);
    }

    // Initialize SPI
    SpiInit( );			//SPI初始化

    // Initialize I2C
    I2cInit( );			//I2C初始化
    
    // Initialize IO expander
    IoeInit( );			//IO扩展芯片SX1509初始化
    
    // Initialize LED		//LED初始化
    for( i = 0; i < LED_NB; i++ )
    {
        LedInit( ( tLed )i );
    }
//		PB12	=	0;
//		PB13	=	0;
//		PB14	=	0;
//		PB15	=	0;
		
    IoePinOn( LED_1_PIN );
    IoePinOn( LED_2_PIN );
    IoePinOn( LED_3_PIN );

		USB_Configuration( );		//USB配置
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
void Delay ( uint32_t delay )		//SYSTick延时--mS
{
    // Wait delay ms
    uint32_t startTick = TickCounter;
    while( ( TickCounter - startTick ) < delay );   
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
void LongDelay ( uint8_t delay )	//SYSTick延时--S
{
    uint32_t longDelay;
    uint32_t startTick;

    longDelay = delay * 1000;

    // Wait delay s
    startTick = TickCounter;
    while( ( TickCounter - startTick ) < longDelay );   
}
