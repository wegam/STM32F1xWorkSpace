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
typedef struct sFifo			//环形链表
{
	uint16_t Begin;
	uint16_t End;
	uint16_t *Data;
	uint16_t Size;
}tFifo;

void FifoInit( tFifo *fifo, uint16_t *buffer, uint16_t size );		//初始化FIFO，缓冲起始地址，环形链表长度

void FifoPush( tFifo *fifo, uint16_t data );		//进栈

uint16_t FifoPop( tFifo *fifo );								//出栈

void FifoFlush( tFifo *fifo );									//清除FIFO

bool IsFifoEmpty( tFifo *fifo );								//检查链表数据是否为空,true-空,false-非空

bool IsFifoFull( tFifo *fifo );									//检查链表数据是否为满，ture-满，false-非满

#endif // __FIFO_H__
