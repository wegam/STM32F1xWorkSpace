#ifndef __DS18B20_H
#define __DS18B20_H 

#include "OneWrie.H"

void DS18B20_Configuration(OneWrieDef *OneWrie);
unsigned short DS18B20_Read(OneWrieDef *OneWrie);		//复位Dallas,返回结果

    
#endif

