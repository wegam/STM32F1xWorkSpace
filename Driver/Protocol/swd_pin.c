#include "swd_pin.H"
//#include "stdbool.h"
//#include "stdint.h"

/*
#define PAout(n)   BITBAND_REG(PTA->PDOR, n)
#define PAin(n)    BITBAND_REG(PTA->PDIR, n)
*/



void SW_PinInit(void)
{
    /* release trst pin */
    SWDIO_SET_OUTPUT() ;//SWDIO设置为输出

    SWCLK_SET_OUTPUT();	//SWCLK设置为输出
    RESET_SET_OUTPUT();	//RESET设置为输出
    RESET_CLR();/////

    SWDIO_SET();//(swdio)PB3输出1
    SWCLK_CLR();//(swclk)PB2输出0
    RESET_SET();//(Trst)PB10输出1
}




void DELAY_US(unsigned long us)
{
    volatile unsigned long i, j;

    for(i = 0; i < us; i++)
    {
        for(j = 0; j < 30U; j++)
        {
            __nop();
        }
    }

}

void PIN_DELAY(void)
{
      unsigned short count;
      count = 2;
      while (--count);
}
/*******************************************************************************
*函数名			:	SW_READ_BIT
*功能描述		:	读一位数据
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
unsigned long SW_READ_BIT(void)
{
    unsigned long bit;    
    bit = SWDIO_IN();
		SWCLK_SET();				//SWCLK	=	HIGH	
		SWCLK_CLR();		//SWCLK	=	LOW
    return bit;
}
/*******************************************************************************
*函数名			:	SW_CLOCK_CYCLE
*功能描述		:	输出时钟信号
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
void SW_CLOCK_CYCLE(void)
{
//    SWCLK_CLR();		//SWCLK	=	LOW
//    ///PIN_DELAY();	//此处以后增加频率关系
//    SWCLK_SET();		//SWCLK	=	HIGH
//    ///PIN_DELAY();
	//20180605
//	PIN_DELAY();
	SWCLK_SET();		//SWCLK	=	HIGH
//	PIN_DELAY();
	SWCLK_CLR();		//SWCLK	=	LOW
	
}
/*******************************************************************************
*函数名			:	SW_WRITE_BIT
*功能描述		:	位写--写一位数据
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
void SW_WRITE_BIT(unsigned long bit)
{
    SWDIO_OUT(bit);		//设置SWDIO电平
    SW_CLOCK_CYCLE();	//输出时钟
}

