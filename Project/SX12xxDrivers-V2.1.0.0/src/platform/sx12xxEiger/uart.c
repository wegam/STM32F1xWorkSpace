/*
 * Copyright (C) SEMTECH SA. All rights reserved.
 * Developed at SEMTECH SA, Neuchatel, Switzerland
 * All rights reserved. Reproduction in whole or part is
 * prohibited without the written permission of the copyright owner.
 *                                 
 */
/*! 
 *	\file		uart.c
 *	\brief		Implements the functions that manage the microcontroller UART's
 *
 *	\version	1.0
 *	\date		Feb 26 2007
 *	\author		MiL
 *
 *	\version	1.1
 *	\date		Apr 30 2007
 *	\author		MAL
 *	\remarks	- Adaptated to compile for the PIC16F877 
 *
 *	\version	1.2
 *	\date		Jun 1 2007
 *	\author		MAL
 *	\remarks	- Rx fifo and Rx interrupt handler added.
 */
#include "sx12xxEiger.h"
#include "fifo.h"
#include "uart.h"

//#if defined( STM32F4XX ) || defined( STM32F2XX ) || defined( STM32F429_439xx )

//#include "usbd_cdc_core.h"
//#include "usb_conf.h"
//#include "usbd_desc.h"

//#else

#include "usb_core.h"
#include "usb_prop.h"
#include "usb_desc.h"
#include "usb_bsp.h"

//#endif

/*!
 * FIFO buffers size
 */
#define FIFO_RX_SIZE								128
#define FIFO_TX_SIZE								128

//#if defined( STM32F4XX ) || defined( STM32F2XX ) || defined( STM32F429_439xx )

//extern CDC_IF_Prop_TypeDef  APP_FOPS;

//#else

extern  uint8_t USART_Rx_Buffer[];
extern uint32_t USART_Rx_ptr_in;
extern LINE_CODING linecoding;

//#endif

tFifo FifoRx;		//USB接收FIFO，存储USB发送过来的数据，准备发往RF
tFifo FifoTx;		//USART发送FIFO，存储RF发送过来的数据准备发送到USART接收缓冲区USART_Rx_Buffer，USART_Rx_Buffer发送到USB输入端点缓存

uint16_t FifoRxBuffer[FIFO_RX_SIZE];
uint16_t FifoTxBuffer[FIFO_TX_SIZE];
/*******************************************************************************
*函数名			:	function
*功能描述		:	函数功能说明
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
uint8_t UartInit( void )		//串口收发FIFO初始化
{
	FifoInit( &FifoRx, FifoRxBuffer, FIFO_RX_SIZE );		//初始化环形接收缓冲链表//初始化FIFO，缓冲起始地址，环形链表长度
	FifoInit( &FifoTx, FifoTxBuffer, FIFO_TX_SIZE );		//初始化环形发送缓冲链表//初始化FIFO，缓冲起始地址，环形链表长度

	return UART_OK;
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
void UartProcess( void )		//串口数据处理----检查FifoTx内是否有数据，如有数据，转存到USART_Rx_Buffer并且计数
{
	if( IsFifoEmpty( &FifoTx ) == false )		//检查链表数据是否为空,true-空,false-非空
	{
		if( linecoding.datatype == 7 )
		{
				USART_Rx_Buffer[USART_Rx_ptr_in] = FifoPop( &FifoTx ) & 0x7F;		//出栈
		}
		else if (linecoding.datatype == 8)
		{
				USART_Rx_Buffer[USART_Rx_ptr_in] = FifoPop( &FifoTx );					//出栈
		}

		USART_Rx_ptr_in++;

		/* To avoid buffer overflow */
		if( USART_Rx_ptr_in == USART_RX_DATA_SIZE )
		{
				USART_Rx_ptr_in = 0;
		}	
	}
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
uint8_t UartPutChar( uint8_t data )		//检查FifoTx数据是否为满并且将RF接收到新数据加入到FifoTx队列
{
	if( IsFifoFull( &FifoTx ) == true )		//检查发数FIFO是否为满
	{
		UartProcess();		//串口数据处理----检查FifoTx内是否有数据，如有数据，转存到USART_Rx_Buffer并且计数
		//return BUSY;
	}
	FifoPush( &FifoTx, data );				//进栈，将新数据加入到FifoTx队列
	return UART_OK;
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
uint8_t UartGetChar( uint8_t *data )	//从接收FifoRx中读取数据放到data缓冲区发往RF
{
	if( IsFifoEmpty( &FifoRx ) == true )
	{
		return UART_EMPTY;
	}
	*data = FifoPop( &FifoRx );
	return UART_OK;
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
uint8_t UartPutBuffer( uint8_t *buffer, uint8_t size )		//将缓存数据发送到USART发送缓冲区FifoTx
{
	uint8_t i;

	for( i = 0; i < size; i++ )
	{
		if( IsFifoFull( &FifoTx ) == true )
		{
			return UART_BUSY;
		}
		FifoPush( &FifoTx, buffer[i] );
	}
	return UART_OK;	
}

uint8_t UartGetBuffer( uint8_t *buffer, uint8_t size, uint8_t *nbReadBytes )
{
	uint8_t i;

	for( i = 0; i < size; i++ )
	{
		if( IsFifoEmpty( &FifoRx ) == true )
		{
			*nbReadBytes = i;
			return UART_EMPTY;
		}
		buffer[i] = FifoPop( &FifoRx );
	}
	*nbReadBytes = i;
	return( UART_OK );
}

uint8_t UartFlush( void )
{
	FifoFlush( &FifoRx );
	FifoFlush( &FifoTx );
	return( UART_OK );
}

bool UartIsTxFifoEmpty( void )
{
	return IsFifoEmpty( &FifoTx );
}

bool UartIsRxFifoEmpty( void )
{
	return IsFifoEmpty( &FifoRx );
}
