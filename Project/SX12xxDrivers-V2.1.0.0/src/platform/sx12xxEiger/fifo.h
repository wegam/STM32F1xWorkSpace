#ifndef __FIFO_H__
#define __FIFO_H__

#include <stdbool.h>

//#if defined( STM32F4XX ) || defined( STM32F429_439xx )
//    #include "stm32f4xx.h"
//#elif defined( STM32F2XX )
//    #include "stm32f2xx.h"
//#else
//    #include "stm32f10x.h"
//#endif

#include "stm32f10x.h"

/*!
 * FIFO
 */
typedef struct sFifo			//��������
{
	uint16_t Begin;
	uint16_t End;
	uint16_t *Data;
	uint16_t Size;
}tFifo;

void FifoInit( tFifo *fifo, uint16_t *buffer, uint16_t size );		//��ʼ��FIFO��������ʼ��ַ������������

void FifoPush( tFifo *fifo, uint16_t data );		//��ջ

uint16_t FifoPop( tFifo *fifo );								//��ջ

void FifoFlush( tFifo *fifo );									//���FIFO

bool IsFifoEmpty( tFifo *fifo );								//������������Ƿ�Ϊ��,true-��,false-�ǿ�

bool IsFifoFull( tFifo *fifo );									//������������Ƿ�Ϊ����ture-����false-����

#endif // __FIFO_H__
