#ifndef __PC006V21_H
#define __PC006V21_H

#include	"stm32f10x_type.h"




#define	TestModel		//测试模式：测试模式下，1~4,4~1旋转
//SW6 ON表示与旋转相关的板，传感器信号采集板/旋转电机控制板
//SW5 ON表示旋转电机控制板，OFF表示传感器板


//===============旋转电机控制板与旋转相关传感器信号采集板专用通讯滤波器组
//CAN滤波器组使用 0x0A
//传感器板CAN-ID为0x80
//旋转电机控制板CAN-ID为0xC0
#define	MotorUD_Group		0x0B		//升降电机控制滤波器组
#define	MotorUD_ID			0xE0
#define	MotorRL_Group		0x0A		//旋转电机控制滤波器组
#define	MotorRL_ID			0xC0
#define	SensorRL_Group	MotorRL_Group		//旋转电机传感器滤波器组
#define	SensorRL_ID			0x80



//===============旋转电机控制板对外接口---接收电机控制命令
//CAN滤波器组0x09
//CAN-ID为0xCC			运行到指定窗口命令0xFA 0x55 nWindows
#define	Cmd_Group		0x09
#define	Cmd_ID			0xCC

//===============其它数据通讯端口
//CAN滤波器组 0x08
//CAN-ID为拔码地址
#define	DATA_Group	0x08
#define	DATA_ID			0xFA

#define	CAN1_BaudRate	500000		//CAN波特率	500K


//=================PA7电机控制板CCW做脉冲输出
#define	MOTOR_Plus_PORT		GPIOA
#define	MOTOR_Plus_Pin		GPIO_Pin_7
//=================PA6电机控制板CW做方向输出
#define	MOTOR_DIR_PORT		GPIOA
#define	MOTOR_DIR_Pin			GPIO_Pin_6

#define	MOTOR_PlusHigh		MOTOR_Plus_PORT->BSRR 	= MOTOR_Plus_Pin		//Plus	=	1;	//高电平
#define	MOTOR_PlusLow			MOTOR_Plus_PORT->BRR 		= MOTOR_Plus_Pin		//Plus	=	0;	//低电平

#define	MOTOR_RunUp				MOTOR_DIR_PORT->BSRR 		= MOTOR_DIR_Pin			//EN	=	1;	//顺时针
#define	MOTOR_RunDown			MOTOR_DIR_PORT->BRR			= MOTOR_DIR_Pin			//EN	=	0;	//逆时钟

#define	MOTOR_RunRight		MOTOR_DIR_PORT->BSRR 		= MOTOR_DIR_Pin			//EN	=	1;	//顺时针
#define	MOTOR_RunLeft			MOTOR_DIR_PORT->BRR			= MOTOR_DIR_Pin			//EN	=	0;	//逆时钟

//=================PA6传感器板CCW做脉冲输出
#define	TXLED_PORT	GPIOA
#define	TXLED_Pin		GPIO_Pin_7
//=================PA7传感器板CW做方向输出
#define	RXLED_PORT	GPIOA
#define	RXLED_Pin		GPIO_Pin_6

#define	MOTOR_PWM_FrequencyUD		200			//脉冲频率--单位Hz
#define	PWM_UpdataCountUD				2				//频率变化占计数个数，加减速时PWM_Updata个脉冲后更新一次输出频率
#define	PWM_RunUpCountUD				10			//加速/减速需要的步数
#define	SteepPerWindowUD				500		//一个窗口用到的驱动脉冲数---升降
#define	MaxWindowUD							1				//最大窗口数
#define	MOTOR_TIMxUD						TIM1		//旋转电机所使用的定时器

#define	MOTOR_PWM_FrequencyRL		400			//脉冲频率--单位Hz
#define	PWM_UpdataCountRL				2				//频率变化占计数个数，加减速时PWM_Updata个脉冲后更新一次输出频率
#define	PWM_RunUpCountRL				1000		//加速/减速需要的步数
#define	SteepPerWindowRL				3*2030				//一个窗口用到的驱动脉冲数---旋转
#define	MaxWindowRL		3					//最大窗口数
#define	MOTOR_TIMxRL						TIM1		//旋转电机所使用的定时器

#define	MOTOR_TIMx							TIM1		//旋转电机所使用的定时器

//=================传感器
#define	Sensor1_Port	GPIOB		//前传感器
#define	Sensor1_Pin		GPIO_Pin_4

#define	Sensor2_Port	GPIOB		//后传感器
#define	Sensor2_Pin		GPIO_Pin_5

#define	Sensor3_Port	GPIOB		//药品传感器
#define	Sensor3_Pin		GPIO_Pin_6

#define	Sensor4_Port	GPIOB		//备用传感器
#define	Sensor4_Pin		GPIO_Pin_7

//======传感器状态：：读取状态为高表示无信号，低-有信号
#define	Sensor1_Status	(Sensor1_Port->IDR & Sensor1_Pin)	//不启用
#define	Sensor2_Status	(Sensor2_Port->IDR & Sensor2_Pin)	//原点
#define	Sensor3_Status	(Sensor3_Port->IDR & Sensor3_Pin)	//中间传感器
#define	Sensor4_Status	(Sensor4_Port->IDR & Sensor4_Pin)	//不启用



#define	SYSLED_FRQ	1				//正常运行时SYSLED闪烁频率

typedef struct _sMoto				//电机控制
{
	struct
	{
		unsigned char 	Set :1;		//Bit0:0-无操作，1-需要更新运行参数
		unsigned char 	CW 	:1;		//Bit1:0-无操作，1-正转（顺时针）
		unsigned char 	CCW	:1;		//Bit2:0-无操作，1-反转（逆时针）
	}MoFlg;
	struct
	{
		unsigned long		Frequency;				//脉冲频率
		unsigned short	Acceleration;			//加/减速脉冲个数
	}MoSetData;
	struct
	{
		unsigned long		PulsMax;					//从原点运行到终点的最大步数
		unsigned long		PulsTotal;				//需要运行的总步数
		unsigned long		PulsCountDown;		//运行步数计数---倒计数
		
		unsigned char		CurrentLocation;	//电机当前位置（0为未初始化，上电需要初始化，找到原点位置1）
	}MoRunData;
}sMotoDef;

typedef struct _sSensor			//传感器
{
	struct
	{
		unsigned char 	SendData :1;		//Bit0:0-无操作，	1-将传感器数据发送出去
	}SenFlg;
	struct
	{
		unsigned char 	Sens0 :1;		//Bit0:0-未触发，	1-有触发
		unsigned char 	Sens1 :1;		//Bit1:0-未触发，	1-有触发
		unsigned char 	Sens2 :1;		//Bit2:0-未触发，	1-有触发
		unsigned char 	Sens3 :1;		//Bit3:0-未触发，	1-有触发
		unsigned char 	Sens4 :1;		//Bit4:0-未触发，	1-有触发
		unsigned char 	Sens5 :1;		//Bit5:0-未触发，	1-有触发
		unsigned char 	Sens6 :1;		//Bit6:0-未触发，	1-有触发
		unsigned char 	Sens7 :1;		//Bit7:0-未触发，	1-有触发
		
	}SenPerSensor;
}sSensorDef;
typedef struct _sMessage		//传感器
{
	struct
	{
		unsigned char 	SendData :1;		//Bit0:0-无操作，	1-将传感器数据发送出去
	}MsgFlg;
	struct
	{
		unsigned char 	Sens0 :1;		//Bit0:0-未触发，	1-有触发
		unsigned char 	Sens1 :1;		//Bit1:0-未触发，	1-有触发
		unsigned char 	Sens2 :1;		//Bit2:0-未触发，	1-有触发
		unsigned char 	Sens3 :1;		//Bit3:0-未触发，	1-有触发
		unsigned char 	Sens4 :1;		//Bit4:0-未触发，	1-有触发
		unsigned char 	Sens5 :1;		//Bit5:0-未触发，	1-有触发
		unsigned char 	Sens6 :1;		//Bit6:0-未触发，	1-有触发
		unsigned char 	Sens7 :1;		//Bit7:0-未触发，	1-有触发
		
	}MsgData;
}sMsgDef;

typedef struct _sSYS
{
	sSensorDef 	Sensor;				//传感器
	sMotoDef 		Motor;				//电机
}sSYSDef;

extern sSYSDef sSYS;

void PC006V21_Configuration(void);
void PC006V21_Server(void);


//========================配置程序
void SWITCHID_Configuration(void);			//拔码开关初始化及读数
void MotorUDBoard_Configuration(void);					//升降电机控制板配置
void MotorRLBoard_Configuration(void);					//旋转电机控制板配置
void SensorRLBoard_Configuration(void);		//旋转控制传感器板配置
//========================服务程序

void MotorUDBoard_Server(void);		//升降电机控制板服务程序
void MotorRLBoard_Server(void);		//电机控制板服务程序
void SensorRLBoard_Server(void);		//传感器板服务程序


//========================驱动程序

void Motor_Configuration(void);
	
//void Motor_RunSet(int Num);			//使药架旋转---Num为正值时表时顺时针转(从上往下视角)Num个格数，负值时为逆时针转Num个格数，0为停止
	

//u8 SetToWindows(u8* nWindows);	//运行到指定窗口	

void Test_modle(void);					//测试模式：测试模式下，1~4,4~1旋转	---宏定义TestModel



u8 MotorUD_Server(void);				//步进电机返回状态
u8 MotorRL_Server(void);				//步进电机返回状态
void CAN_Server(void);				//CAN收发数据管理
//void CAN_test(void);				//CAN收发数据管理
void Switch_Server(void);			//检查拔码地址有无变更，如果变更，重新配置运行参数

void Reset_Data(void);					//复位所有的全局变量值

#endif

