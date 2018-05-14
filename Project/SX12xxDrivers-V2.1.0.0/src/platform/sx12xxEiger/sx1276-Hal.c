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
 * \file       sx1276-Hal.c
 * \brief      SX1276 Hardware Abstraction Layer
 *
 * \version    2.0.B2 
 * \date       Nov 21 2012
 * \author     Miguel Luis
 *
 * Last modified by Miguel Luis on Jun 19 2013
 */
#include <stdint.h>
#include <stdbool.h> 

#include "platform.h"

#if defined( USE_SX1276_RADIO )

#include "ioe.h"
#include "spi.h"
#include "../../radio/sx1276-Hal.h"

/*!
 * SX1276 RESET I/O definitions
 */
#if defined( STM32F4XX ) || defined( STM32F2XX ) 
#define RESET_IOPORT                                GPIOG
#define RESET_PIN                                   GPIO_Pin_12
#elif defined( STM32F429_439xx )
#define RESET_IOPORT                                GPIOG
#define RESET_PIN                                   GPIO_Pin_12
#else
#define RESET_IOPORT                                GPIOA
#define RESET_PIN                                   GPIO_Pin_1
#endif

/*!
 * SX1276 SPI NSS I/O definitions
 */
#if defined( STM32F4XX ) || defined( STM32F2XX )
#define NSS_IOPORT                                  GPIOA
#define NSS_PIN                                     GPIO_Pin_4
#elif defined( STM32F429_439xx )
#define NSS_IOPORT                                  GPIOA
#define NSS_PIN                                     GPIO_Pin_4
#else
#define NSS_IOPORT                                  GPIOA
#define NSS_PIN                                     GPIO_Pin_4
#endif

/*!
 * SX1276 DIO pins  I/O definitions
 */
#if defined( STM32F4XX ) || defined( STM32F2XX ) 
#define DIO0_IOPORT                                 GPIOG
#define DIO0_PIN                                    GPIO_Pin_13
#elif defined( STM32F429_439xx )
#define DIO0_IOPORT                                 GPIOG
#define DIO0_PIN                                    GPIO_Pin_13
#else
#define DIO0_IOPORT                                 GPIOB
#define DIO0_PIN                                    GPIO_Pin_6
#endif

#if defined( STM32F4XX ) || defined( STM32F2XX )
#define DIO1_IOPORT                                 GPIOB
#define DIO1_PIN                                    GPIO_Pin_8
#elif defined( STM32F429_439xx )
#define DIO1_IOPORT                                 GPIOB
#define DIO1_PIN                                    GPIO_Pin_7
#else
#define DIO1_IOPORT                                 GPIOB
#define DIO1_PIN                                    GPIO_Pin_5
#endif

#if defined( STM32F4XX ) || defined( STM32F2XX ) 
#define DIO2_IOPORT                                 GPIOA
#define DIO2_PIN                                    GPIO_Pin_2
#elif defined( STM32F429_439xx )
#define DIO2_IOPORT                                 GPIOA
#define DIO2_PIN                                    GPIO_Pin_2
#else
#define DIO2_IOPORT                                 GPIOB
#define DIO2_PIN                                    GPIO_Pin_4
#endif

#if defined( STM32F4XX ) || defined( STM32F2XX ) || defined( STM32F429_439xx )
#define DIO3_IOPORT                                 
#define DIO3_PIN                                    RF_DIO3_PIN
#else
#define DIO3_IOPORT                                 
#define DIO3_PIN                                    RF_DIO3_PIN
#endif

#if defined( STM32F4XX ) || defined( STM32F2XX ) || defined( STM32F429_439xx )
#define DIO4_IOPORT                                 
#define DIO4_PIN                                    RF_DIO4_PIN
#else
#define DIO4_IOPORT                                 
#define DIO4_PIN                                    RF_DIO4_PIN
#endif

#if defined( STM32F4XX ) || defined( STM32F2XX ) || defined( STM32F429_439xx )
#define DIO5_IOPORT                                 
#define DIO5_PIN                                    RF_DIO5_PIN
#else
#define DIO5_IOPORT                                 
#define DIO5_PIN                                    RF_DIO5_PIN
#endif

#if defined( STM32F4XX ) || defined( STM32F2XX ) || defined( STM32F429_439xx )
#define RXTX_IOPORT                                 
#define RXTX_PIN                                    FEM_CTX_PIN
#else
#define RXTX_IOPORT                                 
#define RXTX_PIN                                    FEM_CTX_PIN
#endif

/*******************************************************************************
*函数名			:	SX1276InitIo
*功能描述		:	SX1276 GPIO配置
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
void SX1276InitIo( void )		//SX1276 GPIO配置	NSS，DIO0~DIO5配置
{
    GPIO_InitTypeDef GPIO_InitStructure;

#if defined( STM32F4XX ) || defined( STM32F2XX ) || defined( STM32F429_439xx )
    RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB |
                            RCC_AHB1Periph_GPIOG, ENABLE );
#else
    RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB |
                            RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO, ENABLE );
#endif

#if defined( STM32F4XX ) || defined( STM32F2XX ) || defined( STM32F429_439xx )
    GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
#else
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
#endif
    
    // Configure NSS as output
    GPIO_WriteBit( NSS_IOPORT, NSS_PIN, Bit_SET );
    GPIO_InitStructure.GPIO_Pin = NSS_PIN;
    GPIO_Init( NSS_IOPORT, &GPIO_InitStructure );

    // Configure radio DIO as inputs
#if defined( STM32F4XX ) || defined( STM32F2XX ) || defined( STM32F429_439xx )
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
#else
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
#endif

    // Configure DIO0
    GPIO_InitStructure.GPIO_Pin =  DIO0_PIN;
    GPIO_Init( DIO0_IOPORT, &GPIO_InitStructure );
    
    // Configure DIO1
    GPIO_InitStructure.GPIO_Pin =  DIO1_PIN;
    GPIO_Init( DIO1_IOPORT, &GPIO_InitStructure );
    
    // Configure DIO2
    GPIO_InitStructure.GPIO_Pin =  DIO2_PIN;
    GPIO_Init( DIO2_IOPORT, &GPIO_InitStructure );
    
    // REAMARK: DIO3/4/5 configured are connected to IO expander

    // Configure DIO3 as input
    
    // Configure DIO4 as input
    
    // Configure DIO5 as input
}
/*******************************************************************************
*函数名			:	SX1276SetReset
*功能描述		:	SX1276复位
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
void SX1276SetReset( uint8_t state )		//SX1276复位--配置NREST控制管脚及拉低无线芯片NREST脚，  引脚7(NREST) 的电平拉低100微秒
{
    GPIO_InitTypeDef GPIO_InitStructure;

    if( state == RADIO_RESET_ON )
    {
        // Set RESET pin to 0
        GPIO_WriteBit( RESET_IOPORT, RESET_PIN, Bit_RESET );		//拉低NREST脚电平

        // Configure RESET as output
#if defined( STM32F4XX ) || defined( STM32F2XX ) || defined( STM32F429_439xx )
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
        GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
#else

        GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
#endif        
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitStructure.GPIO_Pin = RESET_PIN;
        GPIO_Init( RESET_IOPORT, &GPIO_InitStructure );
    }
    else
    {
#if FPGA == 0    
        // Configure RESET as input
#if defined( STM32F4XX ) || defined( STM32F2XX ) || defined( STM32F429_439xx )
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
#else
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
#endif        
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitStructure.GPIO_Pin =  RESET_PIN;
        GPIO_Init( RESET_IOPORT, &GPIO_InitStructure );
#else
        GPIO_WriteBit( RESET_IOPORT, RESET_PIN, Bit_RESET );
#endif
    }
}
/*******************************************************************************
*函数名			:	SX1276Write
*功能描述		:	写一字节数据
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
void SX1276Write( uint8_t addr, uint8_t data )		//写寄存器参数，寄存器地址+数据
{
    SX1276WriteBuffer( addr, &data, 1 );
}
/*******************************************************************************
*函数名			:	SX1276Read
*功能描述		:	读一字节数据
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
void SX1276Read( uint8_t addr, uint8_t *data )		//读一字节数据
{
    SX1276ReadBuffer( addr, data, 1 );
}
/*******************************************************************************
*函数名			:	SX1276WriteBuffer
*功能描述		:	SX1276写数据，
*输入				: addr-寄存器地址，buffer-待写入数据缓冲；size-待写入长度
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
void SX1276WriteBuffer( uint8_t addr, uint8_t *buffer, uint8_t size )		//SX1276写数据：将n字节数据写入指定寄存器
{
    uint8_t i;

    //NSS = 0;
    GPIO_WriteBit( NSS_IOPORT, NSS_PIN, Bit_RESET );

    SpiInOut( addr | 0x80 );
    for( i = 0; i < size; i++ )
    {
        SpiInOut( buffer[i] );
    }

    //NSS = 1;
    GPIO_WriteBit( NSS_IOPORT, NSS_PIN, Bit_SET );
}
/*******************************************************************************
*函数名			:	SX1276ReadBuffer
*功能描述		:	SX1276读数据
*输入				: addr-寄存器地址；buffer-接收数据缓冲；size-读取长度
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
void SX1276ReadBuffer( uint8_t addr, uint8_t *buffer, uint8_t size )	//SX1276读数据
{
    uint8_t i;

    //NSS = 0;
    GPIO_WriteBit( NSS_IOPORT, NSS_PIN, Bit_RESET );

    SpiInOut( addr & 0x7F );

    for( i = 0; i < size; i++ )
    {
        buffer[i] = SpiInOut( 0 );
    }

    //NSS = 1;
    GPIO_WriteBit( NSS_IOPORT, NSS_PIN, Bit_SET );
}
/*******************************************************************************
*函数名			:	SX1276WriteFifo
*功能描述		:	SX1276写入FIFO
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
void SX1276WriteFifo( uint8_t *buffer, uint8_t size )		//SX1276写入FIFO
{
    SX1276WriteBuffer( 0, buffer, size );
}
/*******************************************************************************
*函数名			:	SX1276ReadFifo
*功能描述		:	读取FIFO
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
void SX1276ReadFifo( uint8_t *buffer, uint8_t size )		//读取FIFO
{
    SX1276ReadBuffer( 0, buffer, size );
}
/*******************************************************************************
*函数名			:	SX1276ReadDio0
*功能描述		:	读取Dio0状态
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
inline uint8_t SX1276ReadDio0( void )		//读取Dio0状态
{
    return GPIO_ReadInputDataBit( DIO0_IOPORT, DIO0_PIN );
}
/*******************************************************************************
*函数名			:	SX1276ReadDio1
*功能描述		:	函数功能说明
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
inline uint8_t SX1276ReadDio1( void )		//读取Dio1状态
{
    return GPIO_ReadInputDataBit( DIO1_IOPORT, DIO1_PIN );
}
/*******************************************************************************
*函数名			:	SX1276ReadDio2
*功能描述		:	函数功能说明
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
inline uint8_t SX1276ReadDio2( void )		//读取Dio2状态
{
    return GPIO_ReadInputDataBit( DIO2_IOPORT, DIO2_PIN );
}
/*******************************************************************************
*函数名			:	SX1276ReadDio3
*功能描述		:	函数功能说明
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
inline uint8_t SX1276ReadDio3( void )		//读取Dio3状态
{
    return IoePinGet( RF_DIO3_PIN );
}
/*******************************************************************************
*函数名			:	SX1276ReadDio4
*功能描述		:	函数功能说明
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
inline uint8_t SX1276ReadDio4( void )		//读取Dio4状态
{
    return IoePinGet( RF_DIO4_PIN );
}
/*******************************************************************************
*函数名			:	SX1276ReadDio5
*功能描述		:	函数功能说明
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
inline uint8_t SX1276ReadDio5( void )		//读取Dio5状态
{
    return IoePinGet( RF_DIO5_PIN );
}
/*******************************************************************************
*函数名			:	SX1276WriteRxTx
*功能描述		:	函数功能说明
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
inline void SX1276WriteRxTx( uint8_t txEnable )
{
    if( txEnable != 0 )
    {
        IoePinOn( FEM_CTX_PIN );
        IoePinOff( FEM_CPS_PIN );
    }
    else
    {
        IoePinOff( FEM_CTX_PIN );
        IoePinOn( FEM_CPS_PIN );
    }
}

#endif // USE_SX1276_RADIO
