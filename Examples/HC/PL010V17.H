#ifndef __PL010V15_H
#define __PL010V15_H



//typedef struct _PL010V15
//{

//}PL010V15Def;


void PL010V17_Configuration(void);
void PL010V17_Server(void);

void DS18B20_Server(void);
void CS5530_Server(void);		//称重服务，AD值处理，获取稳定值
void TempSensor_Server(void);	//内部温度传感器
void LCD_Server(void);	//显示服务相关
void RS485_Server(void);		//通讯管理---负责信息的接收与发送
void SwitchID_Server(void);	//拔码开关处理--动态更新拨码地址

void SwitchID_Configuration(void);
void GT32L32_Configuration(void);
void LCD_Configuration(void);
void CS5530_Configuration(void);
void RS485_Configuration(void);
void USART_Configuration(void);

void LCD_PowerUp(void);
void LCD_Display(void);

void PL010Delay(unsigned long time);


#endif

