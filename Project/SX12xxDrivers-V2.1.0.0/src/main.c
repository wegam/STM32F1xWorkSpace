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
 * \file       main.c
 * \brief      Ping-Pong example application on how to use Semtech's Radio
 *             drivers.
 *
 * \version    2.0
 * \date       Nov 21 2012
 * \author     Miguel Luis
 */
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include "platform.h"
#include "led.h"

#if USE_UART
#include "uart.h"
#endif

#include "radio.h"


#define BUFFER_SIZE                                 256 // Define the payload size here



uint16_t BufferSize = BUFFER_SIZE;			// RF buffer size
uint8_t Buffer[BUFFER_SIZE];					// RF buffer

uint8_t Bn	=	0;
uint8_t RBuffer[BUFFER_SIZE];					// RF buffer
uint8_t TBuffer[BUFFER_SIZE];					// RF buffer

static uint8_t EnableMaster = true; 				// Master/Slave selection

tRadioDriver *Radio = NULL;

const uint8_t PingMsg[] = "PING";
const uint8_t PongMsg[] = "PONG";

void OnMaster( void );		//
void OnSlave( void );

/*
 * Main application entry point.
 */
int main( void )
{
    BoardInit( );				//板载外设初始化--SPI初始化，LED初始化，USB初始化，其它端口初始化
    
    Radio = RadioDriverInit( );		//获取驱动程序指针
    
    Radio->Init( );				//SX1276Init();	//初始化SX1276--GPIO初始化，寄存器初始化，工作模式初始化，芯片参数配置。配置完成后进入待机状态

    Radio->StartRx( );		//启动接收---更新状态为准备接收
    
    while( 1 )
    {
        if( EnableMaster == true )
        {
            OnMaster( );	//主机处理程序
        }
        else
        {
            OnSlave( );		//从机处理程序
        }    
#if( PLATFORM == SX12xxEiger ) && ( USE_UART == 1 )			//串口数据收发
				
				//==============================检查FifoTx是否有数据需要发往USART(USB）
        UartProcess( );		//串口数据处理----检查FifoTx内是否有数据，如有数据，转存到USART_Rx_Buffer并且计数
				
				//==============================检查FifoRx//USB接收FIFO，存储USB（串口）发送过来的数据，准备发往RF
        {
            uint8_t data = 0;
//            if( UartGetChar( &data ) == UART_OK )		//从接收FifoRx中读取数据放到data缓冲区发往RF
//            {
//                UartPutChar( data );		//检查FifoTx数据是否为满并且将RF接收到新数据加入到FifoTx队列
////							Radio->SetTxPacket( &data, 1 );
////							Radio->StartRx( );
//            }
						if( UartGetChar( &data ) == UART_OK )		//从接收FifoRx中读取数据放到data缓冲区发往RF
            {
//                UartPutChar( data );		//检查FifoTx数据是否为满并且将RF接收到新数据加入到FifoTx队列
							TBuffer[Bn++]=data;
//							Radio->SetTxPacket( &data, 1 );
//							Radio->StartRx( );
            }
						else if(Bn != 0)
						{
							Radio->SetTxPacket( TBuffer, Bn );		//设置要传输的缓冲区的副本并开始传输。
							Bn = 0;
						}

        }
#endif 

    }
#ifdef __GNUC__
    return 0;
#endif
}


/*
 * Manages the master operation
 */
void OnMaster( void )
{
    uint8_t i;
	
    switch( Radio->Process( ) )		//指向SX1276LoRaProcess( void )	//SX1276在LoRa工作模式下的接收和发送状态处理程序
    {
    case RF_RX_TIMEOUT:
        // Send the next PING frame
        Buffer[0] = 'P';
        Buffer[1] = 'I';
        Buffer[2] = 'N';
        Buffer[3] = 'G';
        for( i = 4; i < BufferSize; i++ )
        {
            Buffer[i] = i - 4;
        }
        Radio->SetTxPacket( Buffer, BufferSize );
        break;
    case RF_RX_DONE:
        Radio->GetRxPacket( Buffer, ( uint16_t* )&BufferSize );
				
        if( BufferSize > 0 )
        {
					for(i=0;i<BufferSize;i++)
					UartPutChar( Buffer[i] );		//检查FifoTx数据是否为满并且将RF接收到新数据加入到FifoTx队列
					LedToggle( RXD_LED );
					
//            if( strncmp( ( const char* )Buffer, ( const char* )PongMsg, 4 ) == 0 )
//            {
//                // Indicates on a LED that the received frame is a PONG
//                LedToggle( LED_GREEN );

//                // Send the next PING frame            
//                Buffer[0] = 'P';
//                Buffer[1] = 'I';
//                Buffer[2] = 'N';
//                Buffer[3] = 'G';
//                // We fill the buffer with numbers for the payload 
//                for( i = 4; i < BufferSize; i++ )
//                {
//                    Buffer[i] = i - 4;
//                }
//                Radio->SetTxPacket( Buffer, BufferSize );
//            }
//            else if( strncmp( ( const char* )Buffer, ( const char* )PingMsg, 4 ) == 0 )
//            { // A master already exists then become a slave
                EnableMaster = false;
//                LedOff( LED_RED );
//            }
        }            
        break;
    case RF_TX_DONE:
        // Indicates on a LED that we have sent a PING
        LedToggle( TXD_LED );
        Radio->StartRx( );
        break;
    default:
        break;
    }
}

/*
 * Manages the slave operation
 */
void OnSlave( void )
{
    uint8_t i;

    switch( Radio->Process( ) )
    {
    case RF_RX_DONE:
        Radio->GetRxPacket( Buffer, ( uint16_t* )&BufferSize );
				
        if( BufferSize > 0 )
        {
					for(i=0;i<BufferSize;i++)
					UartPutChar( Buffer[i] );		//检查FifoTx数据是否为满并且将RF接收到新数据加入到FifoTx队列
					LedToggle( RXD_LED );
					
//            if( strncmp( ( const char* )Buffer, ( const char* )PingMsg, 4 ) == 0 )
//            {
//                // Indicates on a LED that the received frame is a PING
//                LedToggle( LED_GREEN );

//               // Send the reply to the PONG string
//                Buffer[0] = 'P';
//                Buffer[1] = 'O';
//                Buffer[2] = 'N';
//                Buffer[3] = 'G';
//                // We fill the buffer with numbers for the payload 
//                for( i = 4; i < BufferSize; i++ )
//                {
//                    Buffer[i] = i - 4;
//                }

//                Radio->SetTxPacket( Buffer, BufferSize );
//            }
        }
        break;
    case RF_TX_DONE:
        // Indicates on a LED that we have sent a PONG
        LedToggle( TXD_LED );
        Radio->StartRx( );
        break;
    default:
        break;
    }
}


///*
// * Manages the slave operation
// */
//void OnSlave( void )
//{
//    uint8_t i;

//    switch( Radio->Process( ) )
//    {
//    case RF_RX_DONE:
//        Radio->GetRxPacket( Buffer, ( uint16_t* )&BufferSize );
//				
//        if( BufferSize > 0 )
//        {
//					
//            if( strncmp( ( const char* )Buffer, ( const char* )PingMsg, 4 ) == 0 )
//            {
//                // Indicates on a LED that the received frame is a PING
//                LedToggle( RXD_LED );

//               // Send the reply to the PONG string
//                Buffer[0] = 'P';
//                Buffer[1] = 'O';
//                Buffer[2] = 'N';
//                Buffer[3] = 'G';
//                // We fill the buffer with numbers for the payload 
//                for( i = 4; i < BufferSize; i++ )
//                {
//                    Buffer[i] = i - 4;
//                }

//                Radio->SetTxPacket( Buffer, BufferSize );
//            }
//        }
//        break;
//    case RF_TX_DONE:
//        // Indicates on a LED that we have sent a PONG
//        LedToggle( TXD_LED );
//        Radio->StartRx( );
//        break;
//    default:
//        break;
//    }
//}

///*
// * Manages the master operation
// */
//void OnMaster( void )
//{
//    uint8_t i;
//	
//    switch( Radio->Process( ) )
//    {
//    case RF_RX_TIMEOUT:
//        // Send the next PING frame
//        Buffer[0] = 'P';
//        Buffer[1] = 'I';
//        Buffer[2] = 'N';
//        Buffer[3] = 'G';
//        for( i = 4; i < BufferSize; i++ )
//        {
//            Buffer[i] = i - 4;
//        }
//        Radio->SetTxPacket( Buffer, BufferSize );
//        break;
//    case RF_RX_DONE:
//        Radio->GetRxPacket( Buffer, ( uint16_t* )&BufferSize );
//				
//        if( BufferSize > 0 )
//        {
//					for(i=0;i<BufferSize;i++)
//					UartPutChar( Buffer[i] );		//检查FifoTx数据是否为满并且将RF接收到新数据加入到FifoTx队列
//					
//            if( strncmp( ( const char* )Buffer, ( const char* )PongMsg, 4 ) == 0 )
//            {
//                // Indicates on a LED that the received frame is a PONG
//                LedToggle( RXD_LED );

//                // Send the next PING frame            
//                Buffer[0] = 'P';
//                Buffer[1] = 'I';
//                Buffer[2] = 'N';
//                Buffer[3] = 'G';
//                // We fill the buffer with numbers for the payload 
//                for( i = 4; i < BufferSize; i++ )
//                {
//                    Buffer[i] = i - 4;
//                }
//                Radio->SetTxPacket( Buffer, BufferSize );
//            }
//            else if( strncmp( ( const char* )Buffer, ( const char* )PingMsg, 4 ) == 0 )
//            { // A master already exists then become a slave
//                EnableMaster = false;
//                LedOff( LED_GREEN );
//            }
//        }            
//        break;
//    case RF_TX_DONE:
//        // Indicates on a LED that we have sent a PING
//        LedToggle( TXD_LED );
//        Radio->StartRx( );
//        break;
//    default:
//        break;
//    }
//}

