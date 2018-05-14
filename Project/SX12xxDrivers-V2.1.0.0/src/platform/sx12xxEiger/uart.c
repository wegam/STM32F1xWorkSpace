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

tFifo FifoRx;		//USB����FIFO���洢USB���͹��������ݣ�׼������RF
tFifo FifoTx;		//USART����FIFO���洢RF���͹���������׼�����͵�USART���ջ�����USART_Rx_Buffer��USART_Rx_Buffer���͵�USB����˵㻺��

uint16_t FifoRxBuffer[FIFO_RX_SIZE];
uint16_t FifoTxBuffer[FIFO_TX_SIZE];
/*******************************************************************************
*������			:	function
*��������		:	��������˵��
*����				: 
*����ֵ			:	��
*�޸�ʱ��		:	��
*�޸�˵��		:	��
*ע��				:	wegam@sina.com
*******************************************************************************/
uint8_t UartInit( void )		//�����շ�FIFO��ʼ��
{
	FifoInit( &FifoRx, FifoRxBuffer, FIFO_RX_SIZE );		//��ʼ�����ν��ջ�������//��ʼ��FIFO��������ʼ��ַ������������
	FifoInit( &FifoTx, FifoTxBuffer, FIFO_TX_SIZE );		//��ʼ�����η��ͻ�������//��ʼ��FIFO��������ʼ��ַ������������

	return UART_OK;
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
void UartProcess( void )		//�������ݴ���----���FifoTx���Ƿ������ݣ��������ݣ�ת�浽USART_Rx_Buffer���Ҽ���
{
	if( IsFifoEmpty( &FifoTx ) == false )		//������������Ƿ�Ϊ��,true-��,false-�ǿ�
	{
		if( linecoding.datatype == 7 )
		{
				USART_Rx_Buffer[USART_Rx_ptr_in] = FifoPop( &FifoTx ) & 0x7F;		//��ջ
		}
		else if (linecoding.datatype == 8)
		{
				USART_Rx_Buffer[USART_Rx_ptr_in] = FifoPop( &FifoTx );					//��ջ
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
*������			:	function
*��������		:	��������˵��
*����				: 
*����ֵ			:	��
*�޸�ʱ��		:	��
*�޸�˵��		:	��
*ע��				:	wegam@sina.com
*******************************************************************************/
uint8_t UartPutChar( uint8_t data )		//���FifoTx�����Ƿ�Ϊ�����ҽ�RF���յ������ݼ��뵽FifoTx����
{
	if( IsFifoFull( &FifoTx ) == true )		//��鷢��FIFO�Ƿ�Ϊ��
	{
		UartProcess();		//�������ݴ���----���FifoTx���Ƿ������ݣ��������ݣ�ת�浽USART_Rx_Buffer���Ҽ���
		//return BUSY;
	}
	FifoPush( &FifoTx, data );				//��ջ���������ݼ��뵽FifoTx����
	return UART_OK;
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
uint8_t UartGetChar( uint8_t *data )	//�ӽ���FifoRx�ж�ȡ���ݷŵ�data����������RF
{
	if( IsFifoEmpty( &FifoRx ) == true )
	{
		return UART_EMPTY;
	}
	*data = FifoPop( &FifoRx );
	return UART_OK;
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
uint8_t UartPutBuffer( uint8_t *buffer, uint8_t size )		//���������ݷ��͵�USART���ͻ�����FifoTx
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
