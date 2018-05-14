
#ifndef __CD4511_H
#define __CD4511_H
//#include <stdint.h>
#include "stm32f10x_gpio.h"


//BCD码结构体
typedef	struct	_CD4511_BCD
{
	unsigned char	A:1;
	unsigned char	B:1;
	unsigned char	C:1;
	unsigned char	D:1;
	unsigned char	N:4;		//不使用
}CD4511BcdDef;


typedef struct	_CD4511Port
{
	//A/A0
	GPIO_TypeDef* 	A0_PORT;				//GPIOX
	unsigned short 	A0_Pin;					//GPIO_Pin_x
	
	//B/A1
	GPIO_TypeDef* 	A1_PORT;				//GPIOX
	unsigned short 	A1_Pin;					//GPIO_Pin_x
	
	//C/A2
	GPIO_TypeDef* 	A2_PORT;				//GPIOX
	unsigned short 	A2_Pin;					//GPIO_Pin_x
	
	//D/A3
	GPIO_TypeDef* 	A3_PORT;				//GPIOX
	unsigned short 	A3_Pin;					//GPIO_Pin_x
	
	//ENABLE-PIN
	GPIO_TypeDef* 	Seg1_PORT;			//GPIOX
	unsigned short 	Seg1_Pin;				//GPIO_Pin_x
	
	//ENABLE-PIN
	GPIO_TypeDef* 	Seg2_PORT;			//GPIOX
	unsigned short 	Seg2_Pin;				//GPIO_Pin_x
	
	//ENABLE-PIN
	GPIO_TypeDef* 	Seg3_PORT;			//GPIOX
	unsigned short 	Seg3_Pin;				//GPIO_Pin_x
}CD4511PortDef;
typedef struct	_CD4511Data
{
	unsigned short	Num;						//数码管个数
	unsigned short	Data;						//显示的数据
	unsigned long		Time;						//时间	
}CD4511DataDef;

typedef struct	_CD4511
{
	CD4511PortDef	Port;
	CD4511DataDef	Data;	
}CD4511Def;

//extern CD4511BcdDef*	CD4511Bcd;		//BCD码结构体

void CD4511_Initialize(CD4511Def *pInfo);
void CD4511_Process(CD4511Def *pInfo);

void CD4511_Clear(CD4511Def *pInfo);		//清除输出：bitA~bitG输出低电平
	
void CD4511_WriteData(CD4511Def *pInfo,unsigned short num);	//BCD转换为Segment输出 只输出0~9
void CD4511_WriteDataNum(CD4511Def *pInfo,unsigned short num);		//BCD转换为Segment输出 只输出0~9

void CD4511_DisplayOFF(CD4511Def *pInfo);			//关闭显示---关NPN三极管
void CD4511_DisplayON(CD4511Def *pInfo);			//开显示---关NPN三极管












#endif


