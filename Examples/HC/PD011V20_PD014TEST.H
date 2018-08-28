#ifndef __PD011V20_H
#define __PD011V20_H



void PD011V20_Configuration(void);
void PD011V20_Server(void);



void PD011V20_UsartConfiguration(void);
void PD011V20_GpioConfiguration(void);


void PD011V20_UsartServer(void);		//串口
void PD011V20_SensorServer(void);		//传感器接口
void PD011V20_OutServer(void);		//输出接口

#endif

