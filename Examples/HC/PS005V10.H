#ifndef __PL009V33_H
#define __PL009V33_H



//typedef struct _PL010V15
//{

//}PL010V15Def;


void PS005V10_Configuration(void);
void PS005V10_Server(void);


void RS485_Server(void);		//通讯管理---负责信息的接收与发送
void SensorServer(void);

void HC595_Configuration(void);
void HC595_Write(unsigned	char* Buffer,unsigned	char len);

void CD4051_Configuration(void);
void CD4051_SetSensor(unsigned	char x,unsigned char y);

void RS485_Configuration(void);
void USART_Configuration(void);


#endif

