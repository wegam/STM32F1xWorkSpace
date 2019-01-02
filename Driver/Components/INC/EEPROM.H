#ifndef __AT24C02_H
#define __AT24C02_H

#include "stdint.h"

#include "stm32f10x_gpio.h"


#include "I2C.H"

void AT24C02_Write(sI2CDef *sI2C,unsigned char Addr,unsigned char Data);
unsigned char AT24C02_Read(sI2CDef *sI2C,unsigned char Addr);

void AT24C02_WritePage(sI2CDef *sI2C,unsigned char StartAddr,unsigned char *Buffer);


unsigned char AT24C02_ReadBuffer(sI2CDef *sI2C,unsigned char Addr,unsigned char *Buffer,unsigned char Length);

#endif

