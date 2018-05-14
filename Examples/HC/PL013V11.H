#ifndef __PL013V11_H
#define __PL013V11_H

#include "stm32f10x_type.h"


//==============端口---总线485
#define	Bus485Port				USART2
#define	Bus485CtlPort			GPIOA
#define	Bus485CtlPin			GPIO_Pin_1
#define	Bus485BaudRate		19200											//波特率
#define	Bus485DataSize		16												//一条消息携带的最大数据个数

#define	DPPort	GPIOB				//小数点控制端口
#define	DPPin		GPIO_Pin_4	//小数点控制微管脚

#define	PortA0	GPIOB
#define	PinA0		GPIO_Pin_0

#define	PortA1	GPIOB
#define	PinA1		GPIO_Pin_1

#define	PortA2	GPIOB
#define	PinA2		GPIO_Pin_2

#define	PortA3	GPIOB
#define	PinA3		GPIO_Pin_3

#define	PortEN1	GPIOB
#define	PinEN1	GPIO_Pin_15

#define	PortEN2	GPIOB
#define	PinEN2	GPIO_Pin_14

#define	PortEN3	GPIOB
#define	PinEN3	GPIO_Pin_5

//=======================命令结构体
typedef struct _Cmd
{
	unsigned char DispEnNum	:1;		//显示数值	：	0-不显示，		1-显示,数值显示优先于点显示，如果有数值显示，则点不显示
	unsigned char DispEnDp	:1;		//显示点		：	0-不显示，		1-显示
	unsigned char DispMdNum	:1;		//数值模式	：	0-静态显示，	1-0.5S闪烁
	unsigned char DispMdDp	:1;		//点模式		：	0-静态显示，	1-0.5S闪烁
	unsigned char DispTime	:1;		//bit4显示时间	：	0-长亮，			1-在显示时间内根据显示模式显示
} CmdDef;
//=======================接收结构体
typedef struct _sReceFarme
{
	unsigned char desAddr;				/*目的地址*/
	unsigned char srcAddr;				/*源地址*/
	unsigned char runningNumber;	/*流水号*/
	CmdDef				cmd;						/*命令*/
	unsigned char len;						/*长度*/
	unsigned char data[8];				/*数据,高位在前,data[0~3]为显示内容,data[4~7]为闪烁时间,0表示不闪烁*/ //显示时间为0xFFFF FFFF表示为常亮
} sReceFarmeDef;				//接收结构体	
//=======================应答结构体
typedef struct uart2_send 
{
	unsigned char desAddr;				/*目的地址*/
	unsigned char srcAddr;				/*源地址*/
	unsigned char runningNumber;	/*流水号*/
	unsigned char cmd;						/*命令*/
	unsigned char len;						/*长度*/
	unsigned char data[1];				/*数据*/
} UART2_SEND;


extern sReceFarmeDef	sReceFarmeRxd;				//接收结构体---接收缓冲区
extern sReceFarmeDef	sReceFarmeRev;				//接收结构体---备份缓冲区
extern sReceFarmeDef	sReceFarmeSrv;				//接收结构体---待处理缓冲区




void PL013V11_Configuration(void);
void PL013V11_Server(void);


void SWITCHID_Configuration(void);			//拔码开关初始化及读数
void RS485_Configuration(void);			//RS485配置


void CD4511_Configuration(void);			//数码管驱动
void CD4511_DISPALY(u8 wei,u16 num);
void CD4511_DisplayClear(void);		//清除显示
void CD4511_DisplayDp(void);			//个位显示小数点

void RS485_Server(void);			//RS485接收数据

void DataServer(void);				//处理接收到的有效数据

void CD4511_DisplayClear(void);		//清除显示包括小数点
void CD4511_DisplayDp(void);		//个位显示小数点
void CD4511_DisplayNum(u8 wei,u16 num);		//指定位显示指定数值
void CD4511_DisplayTest(void);			//显示测试：000~999刷新显示---带小数点
void DisplayServer(void);		//显示服务程序，根据显示命令刷新

void SwitchIdServer(void);		//检测拔码值有无变化，有则更新ID



#endif

