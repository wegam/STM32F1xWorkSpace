/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : PC001V21.c
* Author             : WOW
* Version            : V2.0.1
* Date               : 06/26/2017
* Description        : PC001V21层控制板.
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/


//==========================================配置说明
//旋转驱动器分频 5000
//升降驱动器分频	5000




#ifdef PC006V21			//分检机控制板

#include "PC006V21.H"




PWM_TimDef		PWM_Tim;					//PWM控制脉冲结构体


u8 SwitchData	=	0;	//存储拔码开关最新地址，如果地址变化，再重新配置运行参数
u8 MotorUD		=	0;	//升降电机控制板标志，0-非升降电机控制，1-升降电机控制
u8 MotorRL		=	0;	//旋转电机控制板标志，0-非旋转电机控制板，1-旋转电机控制板
u8 SensorRL		=	0;	//传感器板标志，0-非旋转传感器板，1-旋转传感器板
u32	MotorTime	=	0;	//旋转电机测试运行时间

//u8	CANID	=	0;
u16 SYSTime=0;
//u16 data=0;
//u8 Flag=0;
u8 Sensor[4]	=	{0};	//4个传感器感应值存储区
u8 SensorON		=	0	;		//旋转电机控制板发来开启传感器采集命令BUFFER[0]=0XAF BUFFER[1]=0关，=1开，0--不采集信号，1-采集信号0.5ms主动上报
u32 SensorTime	=	0;
//=================================旋转电机相关变量
u8 PowerFag	=	0;
u8 PlusFlg						=	0;		//步进电机脉冲标志，一个上升沿计一个脉冲	
u8 RunToWindow				=	0;		//旋转到相应窗口 0-无，1-1号，2-2号，3-3号，4-4号
u8 StatusOfWindow			=	0;		//当时停止位置：0-未初始化，1-原点，2-2号窗口，3-3号窗口，4-4号窗口
u8 CMDOfWindow				=	0;		//运行到指定窗口命令
u16	RunFrequency			=	0;		//当前运行频率
u32 SteepCount				=	0;		//运行步数计数
u32 SteepNeedToRun		=	0;		//需要运行的总步数
#ifdef	TestModel
u8	CCWFlag		=	0;
u8	StartTest		=	0;
u32	TestTime	=	0;
#endif

CanRxMsg RxMessage;				//CAN接收 
//CanTxMsg TxMessage;			//CAN发送

sSYSDef	sUser;


/*******************************************************************************
*函数名		:	function
*功能描述	:	函数功能说明
*输入			: 
*输出			:	无
*返回值		:	无
*例程			:
*******************************************************************************/
void PC006V21_Configuration(void)
{
	
	SYS_Configuration();						//系统配置 STM32_SYS.H	
	PWM_OUT(TIM2,PWM_OUTChannel1,10,900);			//SYS-LED 5HZ 10%		SYSLED_FRQ
	SysTick_DeleyS(2);						//SysTick延时nS
	SysTick_Configuration(1000);		//系统嘀嗒时钟配置72MHz,单位为uS----定时扫描PC006V21_Server
	
	SWITCHID_Configuration(&sUser);				//拔码开关初始化及读数

	if(MotorUD)
	{		
		MotorUDBoard_Configuration();					//旋转电机控制板配置
		PWM_OUT(TIM2,PWM_OUTChannel1,SYSLED_FRQ,500);			//SYS-LED 1HZ 50%		SYSLED_FRQ
	}
	else if(SensorRL)
	{
		SensorRLBoard_Configuration();				//旋转控制传感器板配置
		PWM_OUT(TIM2,PWM_OUTChannel1,SYSLED_FRQ,500);			//SYS-LED 1HZ 50%		SYSLED_FRQ
	}
	else if(MotorRL)
	{		
		MotorRLBoard_Configuration(&sUser);					//旋转电机控制板配置
		PWM_OUT(TIM2,PWM_OUTChannel1,SYSLED_FRQ,500);			//SYS-LED 1HZ 50%		SYSLED_FRQ
	}
	else
	{
		SysTick_Configuration(1000);					//系统嘀嗒时钟配置72MHz,单位为uS----定时扫描PC006V21_Server
		PWM_OUT(TIM2,PWM_OUTChannel1,5,900);			//SYS-LED 5HZ 10%		SYSLED_FRQ
	}	
	IWDG_Configuration(1000);	//独立看门狗配置	Tout-超时复位时间，单位ms	
}

/*******************************************************************************
*函数名		:	function
*功能描述	:	函数功能说明
*输入			: 
*输出			:	无
*返回值		:	无
*例程			:
*******************************************************************************/
void PC006V21_Server(void)
{
//	CAN_test();				//CAN收发数据管理
	
	if(MotorUD)
	{
		MotorUDBoard_Server();		//升降电机控制程序
	}
	else if(SensorRL)
	{
		SensorRLBoard_Server();		//传感器板服务程序
	}	
	else if(MotorRL)
	{
		MotorRLBoard_Server();		//旋转电机控制程序
	}
	Switch_Server(&sUser);			//检查拔码地址有无变更，如果变更，重新配置运行参数
}
//==============================================================================



/*******************************************************************************
*函数名			:	function
*功能描述		:	函数功能说明
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	
*******************************************************************************/
void SWITCHID_Configuration(sSYSDef* sUser)			//拔码开关初始化及读数
{
	//SW6 ON表示与旋转相关的板
	//SW5 ON表示旋转电机控制板，OFF表示传感器板
	//	u8 MotorBD	=	0;		//旋转电机控制板标志，0-非电机控制板，1-电机控制板
	//	u8 SensorBD	=	0;		//传感器板标志，0-非传感器板，1-传感器板
	SWITCHID_DATAType		SWData;					//结构体位形式:读取的拔码开关值---不需要配置
	
	SWData	=	sUser->sPlu.SWITCHID.SWData;
	
	sUser->sPlu.SWITCHID.NumOfSW	=	6;		//拔码位数
	//SW1--PA4
	sUser->sPlu.SWITCHID.SW1_PORT	=	GPIOA;
	sUser->sPlu.SWITCHID.SW1_Pin	=	GPIO_Pin_4;
	//SW2--PA5
	sUser->sPlu.SWITCHID.SW2_PORT	=	GPIOA;
	sUser->sPlu.SWITCHID.SW2_Pin	=	GPIO_Pin_5;
	//SW3--PB12
	sUser->sPlu.SWITCHID.SW3_PORT	=	GPIOB;
	sUser->sPlu.SWITCHID.SW3_Pin	=	GPIO_Pin_12;
	//SW4--PB13
	sUser->sPlu.SWITCHID.SW4_PORT	=	GPIOB;
	sUser->sPlu.SWITCHID.SW4_Pin	=	GPIO_Pin_13;
	//SW5--PB14
	sUser->sPlu.SWITCHID.SW5_PORT	=	GPIOB;
	sUser->sPlu.SWITCHID.SW5_Pin	=	GPIO_Pin_14;
	//SW6--PB15
	sUser->sPlu.SWITCHID.SW6_PORT	=	GPIOB;
	sUser->sPlu.SWITCHID.SW6_Pin	=	GPIO_Pin_15;
	
	SWITCHID_Conf(&(sUser->sPlu.SWITCHID));		//
	SWITCHID_Read(&(sUser->sPlu.SWITCHID));		//
	
	sUser->sPlu.SwitchData	=	((sUser->sPlu.SWITCHID).nSWITCHID)&0x3F;
	SwitchData	=	((sUser->sPlu.SWITCHID).nSWITCHID)&0x3F;
	
	//==========================升降电机控制板
	if(SWData.SW6==1&&SWData.SW5==1&&SWData.SW4==0)
	{
		MotorUD		=	1;	//升降电机控制板标志，0-非升降电机控制，1-升降电机控制
	}
	//==========================旋转电机控制板
	if(SWData.SW6==1&&SWData.SW5==0&&SWData.SW4==1)
	{
		MotorRL		=	1;		//旋转电机控制板标志，0-非电机控制板，1-电机控制板
	}
	//==========================旋转电机传感器板
	if(SWData.SW6==1&&SWData.SW5==0&&SWData.SW4==0)
	{
		SensorRL	=	1;		//传感器板标志，0-非传感器板，1-传感器板	
	}
}
/*******************************************************************************
*函数名			:	MotorBoard_Configuration
*功能描述		:	旋转电机控制板配置
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	
*******************************************************************************/
void MotorUDBoard_Configuration(void)		//旋转电机控制板配置
{
	//============================GPIO配置
	//电机控制板：	PA6-脉冲输出，PA7-方向控制输出
	//传感器板：		PA6，PA7做传感器指示灯（采集信号时闪烁）
	//1）============================步进电机参数配置
	
	TIM_ConfigurationFreq(MOTOR_TIMxUD,MOTOR_PWM_FrequencyUD);		//定时器频率配置方式，最小频率0.01Hz,最大100KHz //由于翻转需要双倍频率
	
	//2）============================传感器接口配置:配置为上拉输入模式(低有效）
	//-----Sensor1-PB4	前传感器
	//-----Sensor2-PB5	后传感器
	//-----Sensor3-PB6	药品传感器
	//-----Sensor4-PB7	备用传感器
	GPIO_Configuration_IPU(Sensor1_Port,	Sensor1_Pin);			//将GPIO相应管脚配置为上拉输入模式----V20170605
	GPIO_Configuration_IPU(Sensor2_Port,	Sensor2_Pin);			//将GPIO相应管脚配置为上拉输入模式----V20170605
	GPIO_Configuration_IPU(Sensor3_Port,	Sensor3_Pin);			//将GPIO相应管脚配置为上拉输入模式----V20170605
	GPIO_Configuration_IPU(Sensor4_Port,	Sensor4_Pin);			//将GPIO相应管脚配置为上拉输入模式----V20170605

	//======脉冲输出：PA7电机控制板CCW做脉冲输出
	GPIO_Configuration_OPP50	(MOTOR_Plus_PORT,		MOTOR_Plus_Pin);			//CCW	//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度2MHz----V20170605
	
	//======方向控制输出：PA6电机控制板CW做方向输出
	GPIO_Configuration_OPP50	(MOTOR_DIR_PORT,		MOTOR_DIR_Pin);			//CW	//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度2MHz----V20170605
	
	//3）============================CAN配置：500K
	CAN_Configuration_NR(CAN1_BaudRate);			//CAN1配置---标志位查询方式，不开中断--速率500K
	//4）============================CAN配置滤波器配置(使用两组滤波器分别与传感器板通讯和接收外部控制指令通讯）
	//-----传感器信号读取滤波器（与旋转传感器板通讯）：MotorBD_Group，MotorBD_ID
	CAN_FilterInitConfiguration_StdData(MotorUD_Group,MotorUD_ID,	(MotorUD_ID)^0XFFFF);			//CAN滤波器配置---标准数据帧模式---BIT7不过滤
	//-----旋转命令滤波器：Cmd_Group，Cmd_ID
	CAN_FilterInitConfiguration_StdData(Cmd_Group,		Cmd_ID,			0xFFFF);			//CAN滤波器配置---标准数据帧模式---电机控制板接收外部控制命令接口

	//4）============================系统嘀嗒时钟配置：做定时程序扫描
	SysTick_Configuration(100);		//系统嘀嗒时钟配置72MHz,单位为uS----定时扫描PC006V21_Server
}
/*******************************************************************************
*函数名			:	MotorBoard_Configuration
*功能描述		:	旋转电机控制板配置
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	
*******************************************************************************/
void MotorRLBoard_Configuration(sSYSDef* sUser)		//旋转电机控制板配置
{
	//============================GPIO配置
	//电机控制板：	PA6-脉冲输出，PA7-方向控制输出
	//传感器板：		PA6，PA7做传感器指示灯（采集信号时闪烁）
	//1）============================步进电机参数配置
	sUser->sMotor.SetTIMx	=	MOTOR_TIMxRL;
	
	sUser->sMotor.SetPulsPort	=	MOTOR_Plus_PORT;		//脉冲输出：PA7电机控制板CCW做脉冲输出
	sUser->sMotor.SetPulsPin	=	MOTOR_Plus_Pin;
	sUser->sMotor.SetDIRPort	=	MOTOR_DIR_PORT;			//方向控制输出：PA6电机控制板CW做方向输出
	sUser->sMotor.SetDIRPin		=	MOTOR_DIR_Pin;
		
	sUser->sMotor.SetFrequency	=	MOTOR_PWM_FrequencyRL;
	
	sUser->sMotor.SetPlusUp				=	PWM_UpdataCountRL;		//加速频率间隔
	sUser->sMotor.SetPlusUpNum		=	PWM_RunUpCountRL;			//加速总步数
	sUser->sMotor.SetPlusDown			=	PWM_UpdataCountRL;		//减速频率间隔
	sUser->sMotor.SetPlusDownNum	=	PWM_RunUpCountRL;			//减速总步数
	sUser->sMotor.SetPulsTotal		=	0;										//需要输出脉冲个数
	
	StepMotorConfiguration(&(sUser->sMotor));		//
	
	//3）============================CAN配置：500K
	CAN_Configuration_NR(CAN1_BaudRate);			//CAN1配置---标志位查询方式，不开中断--速率500K
	//4）============================CAN配置滤波器配置(使用两组滤波器分别与传感器板通讯和接收外部控制指令通讯）
	//-----传感器信号读取滤波器（与旋转传感器板通讯）：MotorBD_Group，MotorBD_ID
	CAN_FilterInitConfiguration_StdData(MotorRL_Group,MotorRL_ID,	(MotorRL_ID^SensorRL_ID)^0XFFFF);			//CAN滤波器配置---标准数据帧模式---BIT7不过滤
	//-----旋转命令滤波器：Cmd_Group，Cmd_ID
	CAN_FilterInitConfiguration_StdData(Cmd_Group,		Cmd_ID,			0xFFFF);			//CAN滤波器配置---标准数据帧模式---电机控制板接收外部控制命令接口

	//4）============================系统嘀嗒时钟配置：做定时程序扫描
	SysTick_Configuration(1000);		//系统嘀嗒时钟配置72MHz,单位为uS----定时扫描PC006V21_Server
}
/*******************************************************************************
*函数名			:	SensorBoard_Configuration
*功能描述		:	旋转控制传感器板配置
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	
*******************************************************************************/
void SensorRLBoard_Configuration(void)		//旋转控制传感器板配置
{
	//============================PA6-CCW,PA7-CW配置
	//电机控制板：	PA6-脉冲输出，PA7-方向控制输出
	//传感器板：		PA6，PA7做传感器指示灯（采集信号时闪烁）
	
	//1）============================信号采样闪烁LED配置
	GPIO_Configuration_OPP2	(TXLED_PORT,TXLED_Pin);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度2MHz----V20170605
	GPIO_Configuration_OPP2	(RXLED_PORT,RXLED_Pin);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度2MHz----V20170605
	
	//2）============================传感器接口配置:配置为上拉输入模式(低有效）
	//-----Sensor1-PB4	前传感器
	//-----Sensor2-PB5	后传感器
	//-----Sensor3-PB6	药品传感器
	//-----Sensor4-PB7	备用传感器
	GPIO_Configuration_IPU(Sensor1_Port,	Sensor1_Pin);			//将GPIO相应管脚配置为上拉输入模式----V20170605
	GPIO_Configuration_IPU(Sensor2_Port,	Sensor2_Pin);			//将GPIO相应管脚配置为上拉输入模式----V20170605
	GPIO_Configuration_IPU(Sensor3_Port,	Sensor3_Pin);			//将GPIO相应管脚配置为上拉输入模式----V20170605
	GPIO_Configuration_IPU(Sensor4_Port,	Sensor4_Pin);			//将GPIO相应管脚配置为上拉输入模式----V20170605		

	//3）============================CAN配置：500K
	//--------接收电机控制板命令：开启读传感器信号或者关闭
	CAN_Configuration_NR(CAN1_BaudRate);			//CAN1配置---标志位查询方式，不开中断--速率500K
	//4）============================CAN配置滤波器配置
	//-----传感器信号读取滤波器（与旋转电机控制板通讯）：SensorBD_Group，SensorBD_ID
	CAN_FilterInitConfiguration_StdData(SensorRL_Group,SensorRL_ID,(MotorRL_ID^SensorRL_ID)^0XFFFF);			//CAN滤波器配置---标准数据帧模式---BIT7不过滤
	//5）============================系统嘀嗒时钟配置：做定时程序扫描
	SysTick_Configuration(500);			//系统嘀嗒时钟配置72MHz,单位为uS----定时扫描PC006V21_Server(0.1ms扫描传感器)
}
//==============================================================================


/*******************************************************************************
*函数名			:	function
*功能描述		:	函数功能说明
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	
*******************************************************************************/
void MotorUDBoard_Server(void)		//电机控制板服务程序
{
	//	u8 SensorON		=	0	;		//旋转电机控制板发来开启传感器采集命令BUFFER[0]=0XAF BUFFER[1]=0关，=1开，0--不采集信号，1-采集信号0.5ms主动上报
	//先后顺序要求：电机运行时需要接收传感器板的数据，所以需要先查询CAN数据
//	u8 status	=	0;			//CAN读取返回0表示无效
	
	//1）============================独立看门狗喂狗
	IWDG_Feed();				//独立看门狗喂狗

	//2）============================查询CAN发送数据
	CAN_Server();					//CAN收发数据管理
	
	//3）============================查询电机控制程序：电机控制采用定时器中断
	MotorUD_Server();				//查询步进电机状态---电机的运行、停止、当前状态查询	
	
	//5）============================清除数据
	RxMessage.StdId	=	0x00;
	memset(RxMessage.Data,0X00,8);
	
	//6）============================计时器1ms
	SYSTime++;
	if(SYSTime>=4000)
	{		
		SYSTime=0;
	}
	
	//4）============================测试模式
	Test_modle();					//测试模式
}
/*******************************************************************************
*函数名			:	function
*功能描述		:	函数功能说明
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	
*******************************************************************************/
void MotorRLBoard_Server(void)		//电机控制板服务程序
{
	//	u8 SensorON		=	0	;		//旋转电机控制板发来开启传感器采集命令BUFFER[0]=0XAF BUFFER[1]=0关，=1开，0--不采集信号，1-采集信号0.5ms主动上报
	//先后顺序要求：电机运行时需要接收传感器板的数据，所以需要先查询CAN数据
//	u8 status	=	0;			//CAN读取返回0表示无效
	//1）============================电机
	
	//1）============================独立看门狗喂狗
	IWDG_Feed();				//独立看门狗喂狗

	//2）============================查询CAN发送数据
	CAN_Server();					//CAN收发数据管理
	
	//3）============================查询电机控制程序：电机控制采用定时器中断
	MotorRL_Server();				//查询步进电机状态---电机的运行、停止、当前状态查询
	
	//5）============================清除数据
	RxMessage.StdId	=	0x00;
	memset(RxMessage.Data,0X00,8);
	
	//6）============================计时器1ms
	SYSTime++;
	if(SYSTime>=4000)
	{		
		SYSTime=0;
	}
	
	
//	if(StatusOfWindow	==0)	//未初始化，不执行测试模式
//	{
//		return;
//	}
	//4）============================测试模式	
	Test_modle();					//测试模式
}
/*******************************************************************************
*函数名			:	function
*功能描述		:	函数功能说明
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	
*******************************************************************************/
void SensorRLBoard_Server(void)		//传感器板服务程序
{
	//	u8 SensorON		=	0	;		//旋转电机控制板发来开启传感器采集命令BUFFER[0]=0XAF BUFFER[1]=0关，=1开，0--不采集信号，1-采集信号0.5ms主动上报
	u8 status	=	0;			//CAN读取返回0表示无效
	//1）============================独立看门狗喂狗
	IWDG_Feed();				//独立看门狗喂狗
	//2）============================查询CAN接收数据
	CAN_Server();			//CAN收发数据管理
	//******************************************************************************
	//								以下部分根据旋转控制板的命令选择是否执行
	//******************************************************************************
	if(SensorON	==0)			//传感器板未收到工作命令
	{
		SYSTime	=	0;
		TXLED_PORT->BRR=TXLED_Pin;		//PA6传感器板CCW做脉冲输出---LED_OFF
		RXLED_PORT->BRR=RXLED_Pin;		//PA7传感器板CW做方向输出---LED_OFF
		return;
	}
	//3）============================计时器0.1ms
	SYSTime++;
	if(SYSTime>=10000)
	{		
		SYSTime=0;
	}
	//4）============================读取各传感器
	if((Sensor1_Status==0)	&&	(Sensor[0]<0xFF))
	{
		Sensor[0]++;
	}
	else
	{
		Sensor[0]	=	0;
	}
	if((Sensor2_Status==0)	&&	(Sensor[1]<0xFF))
	{
		Sensor[1]++;
	}
	else
	{
		Sensor[1]	=	0;
	}
	if((Sensor3_Status==0)	&&	(Sensor[2]<0xFF))
	{
		Sensor[2]++;
	}
	else
	{
		Sensor[2]	=	0;
	}
	if((Sensor4_Status==0)	&&	(Sensor[3]<0xFF))
	{
		Sensor[3]++;
	}
	else
	{
		Sensor[3]	=	0;
	}
	//5）============================上报传感器数据：0.5ms上服一次数据
//	if(SYSTime%5==0)									//旋转电机控制板发来开启传感器采集命令BUFFER[0]=0XAF BUFFER[1]=0关，=1开，0--不采集信号，1-采集信号0.5ms主动上报
//	{
//		CAN_StdTX_DATA(SensorRL_ID,4,Sensor);			//CAN使用标准帧发送数据---发送传感器数据 0.5ms发送间隔
//	}
	//6）============================传感器板在工作时LED闪烁
	if(SYSTime%100==0)
	{
		TXLED_PORT->BSRR=TXLED_Pin;		//PA6传感器板CCW做脉冲输出---LED_ON
		RXLED_PORT->BSRR=RXLED_Pin;		//PA7传感器板CW做方向输出---LED_ON
	}
	else	if(SYSTime%100==20)
	{
		TXLED_PORT->BRR=TXLED_Pin;		//PA6传感器板CCW做脉冲输出---LED_OFF
		RXLED_PORT->BRR=RXLED_Pin;		//PA7传感器板CW做方向输出---LED_OFF
	}
}


//==============================================================================




/*******************************************************************************
*函数名			:	function
*功能描述		:	function
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:		
*******************************************************************************/
//void Motor_Configuration(void)
//{
//	SteepMotor1.SetTIMx			=	MOTOR_TIMx;
//	
//	SteepMotor1.SetPulsPort	=	MOTOR_Plus_PORT;
//	SteepMotor1.SetPulsPin	=	MOTOR_Plus_Pin;
//	
//	SteepMotor1.SetDIRPort	=	MOTOR_DIR_PORT;
//	SteepMotor1.SetDIRPin		=	MOTOR_DIR_Pin;
//	
//	SteepMotor1.SetFrequency	=	1000;
//	
//	StepMotorConfiguration(&SteepMotor1);		//
//}









/*******************************************************************************
*函数名			:	function
*功能描述		:	函数功能说明
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	
*******************************************************************************/
void Test_modle(void)		//测试模式
{
#ifdef	TestModel
	
	
	
	if(StatusOfWindow	==	0)		//未初始化，不执行测试模式
	{
		CCWFlag	=	0;	//运行方向标志
		return;
	}
	

	if(RunToWindow!=0)
	{
//		TestTime	=	0;
		return;
	}
	else
	{
		TestTime++;
		if(TestTime>=2000)
		{
			TestTime	=	0;
		}
	
		if(MotorRL)
		{
			CMDOfWindow	=	(TestTime%MaxWindowRL)+1;
		}
		else if(MotorUD)
		{
			CMDOfWindow	=	(TestTime%MaxWindowUD)+1;
		}

	}
	
	
	
	
//	if(StatusOfWindow	==	0)
//	{
//		CCWFlag	=	0;	//运行方向标志
//		return;
//	}
//	
//	if(RunToWindow!=0)
//	{
//		TestTime	=	0;
//	}
//	else
//	{
//		TestTime++;
//	}
////	if(RunToWindow!=0)
////	{
////		return;
////	}
//	if(TestTime	>=	500)
//	{
//		TestTime	=	0;
//		if(CCWFlag	==	0)		//正转
//		{
//			CMDOfWindow	=	StatusOfWindow+1;
//			if(CMDOfWindow	>=	MaxWindow)
//			{
//				CCWFlag	=	1;
//			}
//		}
//		else		//反转
//		{
//			CMDOfWindow	=	StatusOfWindow-1;
//			if(CMDOfWindow	<=	1)
//			{
//				CCWFlag	=	0;
//			}
//		}
//	}
#endif
}
//==============================================================================









/*******************************************************************************
*函数名			:	function
*功能描述		:	函数功能说明
*输入				: 
*返回值			:	0-无定时器中断，1-有定时器中断
*修改时间		:	无
*修改说明		:	无
*注释				:	
*******************************************************************************/
u8 MotorUD_Server(void)				//查询步进电机状态
{
	//SW6 ON表示与旋转相关的板
	//SW5 ON表示旋转电机控制板，OFF表示传感器板
	//CAN滤波器组使用 0x0A
	//传感器板CAN-ID为0x80
	//旋转电机控制板CAN-ID为0xC0
	//	u8 MotorBD	=	0;		//旋转电机控制板标志，0-非电机控制板，1-电机控制板
	//	u8 SensorBD	=	0;		//传感器板标志，0-非传感器板，1-传感器板	
	//	u8 RunToWindow	=	0;		//旋转到相应窗口 0-无，1-1号，2-2号，3-3号，4-4号
	//	u8 StatusOfWindow	=	0;	//当时停止位置：0-未初始化，1-原点，2-2号窗口，3-3号窗口，4-4号窗口
	
	//==============电机控制说明
	//运行过程分：启动加速，匀速运行，减速停止
	//窗口位置：
	//电机原点为中间传感器：上电时，先逆时针慢速运转到极限位再回到原点（如果在回极限位过程中找到原点，则停止在原点，初始化完成）
	
//	u8 status	=	0;
	
	
	if((MOTOR_TIMxUD->SR & TIM_IT_Update)==TIM_IT_Update	&&	RunToWindow!=0)			//表示定时中断---运行计数未完
	{
		if(PlusFlg	!=0)			//步进电机脉冲标志，一个上升沿计一个脉冲
		{
			PlusFlg	=	0;				//步进电机脉冲标志，一个上升沿计一个脉冲
			SteepCount	+=	1;							//运行步数计数
			if(Sensor1_Status==0)
			{
				StatusOfWindow	=	RunToWindow;	//新的电机停止窗口位
				RunToWindow			=	0;						//旋转到相应窗口 0-无，1-1号，2-2号，3-3号，4-4号
				
				MOTOR_PlusLow;		//MOTOR_Plus输出关闭（低电平）
				TIM_Cmd(MOTOR_TIMxUD, DISABLE); 	//关闭定时器
			}
			else	if(SteepCount>=SteepNeedToRun)	//运行步数到达
			{
				StatusOfWindow	=	RunToWindow;	//新的电机停止窗口位
				RunToWindow			=	0;						//旋转到相应窗口 0-无，1-1号，2-2号，3-3号，4-4号
				
				MOTOR_PlusLow;		//MOTOR_Plus输出关闭（低电平）
				TIM_Cmd(MOTOR_TIMxUD, DISABLE); 	//关闭定时器
			}
			else
			{
				if(StatusOfWindow	==	0)
				{
					MOTOR_PlusLow;		//MOTOR_Plus输出低电平
				}
				else
				{
					if(SteepCount<PWM_RunUpCountUD)
					{
						RunFrequency	+=	PWM_UpdataCountUD;		//当前运行频率
						TIM_SetFreq(MOTOR_TIMxUD,RunFrequency);		//设定频率
					}
					else if(SteepCount+PWM_RunUpCountUD>=SteepNeedToRun)
					{
						RunFrequency	-=	PWM_UpdataCountUD;		//当前运行频率
						TIM_SetFreq(MOTOR_TIMxUD,RunFrequency);		//设定频率
					}
					MOTOR_PlusLow;		//MOTOR_Plus输出低电平
				}
			}
		}
		else
		{
			PlusFlg	=	1;				//步进电机脉冲标志，一个上升沿计一个脉冲
			MOTOR_PlusHigh;		//MOTOR_Plus输出高电平
		}
		TIM_ClearITPendingBit(MOTOR_TIMxUD, TIM_IT_Update);			//清除中断标志
	}
	
	
	
	if(StatusOfWindow==0	&&	RunToWindow==0)				//电机上电初始化
	{
		MOTOR_RunDown;						//
		PlusFlg						=	0;		//步进电机脉冲标志，一个上升沿计一个脉冲	
		CMDOfWindow				=	1;		//运行到指定窗口命令
		RunToWindow				=	1;		//旋转到相应窗口 0-无，1-1号，2-2号，3-3号，4-4号
		
		SteepCount				=	0;		//运行步数计数
		SteepNeedToRun		=	MaxWindowUD*SteepPerWindowUD+PWM_RunUpCountUD;				//需要运行的总步数
		RunFrequency			=	MOTOR_PWM_FrequencyUD;
		TIM_SetFreq(MOTOR_TIMxUD,RunFrequency);		//设定频率MOTOR_PWM_Frequency
		TIM_Cmd(MOTOR_TIMxUD, ENABLE); 						//开启定时器
	}
	else if(StatusOfWindow!=0	&&	RunToWindow==0	&&	CMDOfWindow!=0)		//电机在待机待机状态下有新的窗口命令
	{
		if(CMDOfWindow	==	StatusOfWindow)
		{			
			RunToWindow				=	0;							//旋转到相应窗口 0-无，1-1号，2-2号，3-3号，4-4号
			CMDOfWindow				=	0;							//运行到指定窗口命令
			
			TIM_Cmd(MOTOR_TIMxUD, DISABLE); 			//关闭定时器
		}
		else if(CMDOfWindow	>	StatusOfWindow)
		{
			MOTOR_RunUp;											//顺时针
			PlusFlg						=	0;							//步进电机脉冲标志，一个上升沿计一个脉冲				
			RunToWindow				=	CMDOfWindow;		//旋转到相应窗口 0-无，1-1号，2-2号，3-3号，4-4号
			CMDOfWindow				=	0;		//运行到指定窗口命令			
			
			SteepCount				=	0;							//运行步数计数
			if(RunToWindow	==	1)
			{
				SteepNeedToRun		=	(RunToWindow-StatusOfWindow)*SteepPerWindowUD+PWM_RunUpCountUD;				//需要运行的总步数
			}
			else
			{
				SteepNeedToRun		=	(RunToWindow-StatusOfWindow)*SteepPerWindowUD;				//需要运行的总步数
			}
			
			RunFrequency			=	MOTOR_PWM_FrequencyUD;		//起始频率
			
			TIM_SetFreq(MOTOR_TIMxUD,RunFrequency);		//设定频率
			
			TIM_Cmd(MOTOR_TIMxUD, ENABLE); 				//开启定时器
		}
		else if(CMDOfWindow	<	StatusOfWindow)
		{
			MOTOR_RunDown;											//逆时针
			PlusFlg						=	0;							//步进电机脉冲标志，一个上升沿计一个脉冲				
			RunToWindow				=	CMDOfWindow;		//旋转到相应窗口 0-无，1-1号，2-2号，3-3号，4-4号
			CMDOfWindow				=	0;							//运行到指定窗口命令			
			
			SteepCount				=	0;							//运行步数计数
			SteepNeedToRun		=	(StatusOfWindow-RunToWindow)*SteepPerWindowUD;				//需要运行的总步数	
			
			RunFrequency			=	MOTOR_PWM_FrequencyUD;		//起始频率
			
			TIM_SetFreq(MOTOR_TIMxUD,RunFrequency);		//设定频率
			
			TIM_Cmd(MOTOR_TIMxUD, ENABLE); 				//开启定时器			
		}
	}
			
	MotorTime++;
	if(MotorTime>=1000)
	{
		
		MotorTime=0;
	}
	return 0;
}
/*******************************************************************************
*函数名			:	function
*功能描述		:	函数功能说明
*输入				: 
*返回值			:	0-无定时器中断，1-有定时器中断
*修改时间		:	无
*修改说明		:	无
*注释				:	
*******************************************************************************/
u8 MotorRL_Server(void)				//查询步进电机状态
{
	//SW6 ON表示与旋转相关的板
	//SW5 ON表示旋转电机控制板，OFF表示传感器板
	//CAN滤波器组使用 0x0A
	//传感器板CAN-ID为0x80
	//旋转电机控制板CAN-ID为0xC0
	//	u8 MotorBD	=	0;		//旋转电机控制板标志，0-非电机控制板，1-电机控制板
	//	u8 SensorBD	=	0;		//传感器板标志，0-非传感器板，1-传感器板	
	//	u8 RunToWindow	=	0;		//旋转到相应窗口 0-无，1-1号，2-2号，3-3号，4-4号
	//	u8 StatusOfWindow	=	0;	//当时停止位置：0-未初始化，1-原点，2-2号窗口，3-3号窗口，4-4号窗口
	
	//==============电机控制说明
	//运行过程分：启动加速，匀速运行，减速停止
	//窗口位置：
	//电机原点为中间传感器：上电时，先逆时针慢速运转到极限位再回到原点（如果在回极限位过程中找到原点，则停止在原点，初始化完成）
	
//	u8 status	=	0;
	
	if(StepMotorServer(&(sUser.sMotor)))
	{
		if((RxMessage.StdId==SensorRL_ID)&&(RxMessage.Data[1]!=0)&&(RunToWindow==1))
		{
			StatusOfWindow	=	RunToWindow;	//新的电机停止窗口位
			RunToWindow			=	0;						//旋转到相应窗口 0-无，1-1号，2-2号，3-3号，4-4号
			
			StepMotorStop(&(sUser.sMotor));
		}
		else if((sUser.sMotor).GetPulsTotal>=SteepNeedToRun)
		{
			StatusOfWindow	=	RunToWindow;	//新的电机停止窗口位
			RunToWindow			=	0;						//旋转到相应窗口 0-无，1-1号，2-2号，3-3号，4-4号
			
			StepMotorStop(&(sUser.sMotor));
		}
		return 1;
	}
	else
	{
		if(StatusOfWindow==0	&&	RunToWindow==0)				//电机上电初始化
		{
			MOTOR_RunLeft;						//逆时针
			PlusFlg						=	0;		//步进电机脉冲标志，一个上升沿计一个脉冲	
			CMDOfWindow				=	1;		//运行到指定窗口命令
			RunToWindow				=	1;		//旋转到相应窗口 0-无，1-1号，2-2号，3-3号，4-4号
			
			SteepCount				=	0;		//运行步数计数
			SteepNeedToRun		=	MaxWindowRL*SteepPerWindowRL+PWM_RunUpCountRL;				//需要运行的总步数
	//		RunFrequency			=	2*MOTOR_PWM_FrequencyRL;
	//		TIM_SetFreq(MOTOR_TIMxRL,RunFrequency);		//设定频率MOTOR_PWM_Frequency
//			TIM_Cmd(MOTOR_TIMxRL, ENABLE); 						//开启定时器
			
			StepMotorCW(&(sUser.sMotor),MOTOR_PWM_FrequencyRL,0,0,0,0,SteepNeedToRun);		//顺时针旋转
		}
		else if(StatusOfWindow!=0	&&	RunToWindow==0	&&	CMDOfWindow!=0)		//电机在待机待机状态下有新的窗口命令
		{
			if(CMDOfWindow	==	StatusOfWindow)
			{			
				RunToWindow				=	0;							//旋转到相应窗口 0-无，1-1号，2-2号，3-3号，4-4号
				CMDOfWindow				=	0;							//运行到指定窗口命令
				
				StepMotorStop(&(sUser.sMotor));
			}
			else if(CMDOfWindow	>	StatusOfWindow)
			{
				PlusFlg						=	0;							//步进电机脉冲标志，一个上升沿计一个脉冲				
				RunToWindow				=	CMDOfWindow;		//旋转到相应窗口 0-无，1-1号，2-2号，3-3号，4-4号
				CMDOfWindow				=	0;		//运行到指定窗口命令			
				
				SteepCount				=	0;							//运行步数计数
				if(RunToWindow	==	1)
				{
					SteepNeedToRun		=	(RunToWindow-StatusOfWindow)*SteepPerWindowRL+PWM_RunUpCountRL/5;				//需要运行的总步数
				}
				else
				{
					SteepNeedToRun		=	(RunToWindow-StatusOfWindow)*SteepPerWindowRL;				//需要运行的总步数
				}
				
				RunFrequency			=	MOTOR_PWM_FrequencyRL;		//起始频率
				
				StepMotorCCW(&(sUser.sMotor),MOTOR_PWM_FrequencyRL,PWM_UpdataCountRL,PWM_RunUpCountRL,PWM_UpdataCountRL,PWM_RunUpCountRL,SteepNeedToRun);		//顺时针旋转
			}
			else if(CMDOfWindow	<	StatusOfWindow)
			{

				PlusFlg						=	0;							//步进电机脉冲标志，一个上升沿计一个脉冲				
				RunToWindow				=	CMDOfWindow;		//旋转到相应窗口 0-无，1-1号，2-2号，3-3号，4-4号
				CMDOfWindow				=	0;							//运行到指定窗口命令			
				
				SteepCount				=	0;							//运行步数计数
				SteepNeedToRun		=	(StatusOfWindow-RunToWindow)*SteepPerWindowRL;				//需要运行的总步数	
				
				RunFrequency			=	MOTOR_PWM_FrequencyRL;		//起始频率
				
				StepMotorCW(&(sUser.sMotor),MOTOR_PWM_FrequencyRL,PWM_UpdataCountRL,PWM_RunUpCountRL,PWM_UpdataCountRL,PWM_RunUpCountRL,SteepNeedToRun);		//顺时针旋转		
			}
		}
				
		MotorTime++;
		if(MotorTime>=1000)
		{
			
			MotorTime=0;
		}
		return 0;
	}
}



/*******************************************************************************
*函数名			:	function
*功能描述		:	函数功能说明
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	
*******************************************************************************/
void CAN_Server(void)			//CAN收发数据管理
{
	//SW6 ON表示与旋转相关的板
	//SW5 ON表示旋转电机控制板，OFF表示传感器板
	//CAN滤波器组使用 0x0A
	//传感器板CAN-ID为0x80
	//旋转电机控制板CAN-ID为0xC0
	//	u8 MotorBD	=	0;		//旋转电机控制板标志，0-非电机控制板，1-电机控制板
	//	u8 SensorBD	=	0;		//传感器板标志，0-非传感器板，1-传感器板
	
	//	u8 RunToWindow	=	0;		//旋转到相应窗口 0-无，1-1号，2-2号，3-3号，4-4号
	//	u8 SensorON		=	0	;		//旋转电机控制板发来开启传感器采集命令BUFFER[0]=0XAF BUFFER[1]=0关，=1开，0--不采集信号，1-采集信号0.5ms主动上报
	u8 status	=	0;		//CAN读取返回0表示无效
	
	if(SensorRL)															//传感器板---旋转电机开始运行时开始采集信号
	{
		status	=	CAN_RX_DATA(&RxMessage);									//检查CAN接收有无数据
		if(status)		//未接收到数据
		{
			SYSTime	=	0;
			if(RxMessage.StdId	==	MotorRL_ID)							//旋转电机控制板发来数据
			{
				//传感器信号采集开关
				if(RxMessage.Data[0]==0xAF	&&	RxMessage.Data[1]==0x01)
				{				
					SensorON	=	1;		//旋转电机控制板发来开启传感器采集命令BUFFER[0]=0XAF BUFFER[1]=0关，=1开，0--不采集信号，1-采集信号0.5ms主动上报
				}
				else if(RxMessage.Data[0]==0xAF	&&	RxMessage.Data[1]==0x00)
				{				
					SensorON	=	0;		//旋转电机控制板发来开启传感器采集命令BUFFER[0]=0XAF BUFFER[1]=0关，=1开，0--不采集信号，1-采集信号0.5ms主动上报
				}
				memset(RxMessage.Data,0x00,2);
			}
		}
		else if(SensorON)
		{
//			if(SYSTime%5==0)									//旋转电机控制板发来开启传感器采集命令BUFFER[0]=0XAF BUFFER[1]=0关，=1开，0--不采集信号，1-采集信号0.5ms主动上报
//			{
				CAN_StdTX_DATA(SensorRL_ID,4,Sensor);			//CAN使用标准帧发送数据---发送传感器数据 0.5ms发送间隔
//			}
		}
		
	}
	else if(MotorRL)				//旋转电机控制板
	{
		//	u8 RunToWindow	=	0;		//旋转到相应窗口 0-无，1-1号，2-2号，3-3号，4-4号
		status	=	CAN_RX_DATA(&RxMessage);									//检查CAN接收有无数据
		if(status	!=	0)		//接收到数据
		{
			if(RxMessage.StdId	==	Cmd_ID)							//旋转电机控制板接收到控制命令
			{
				if(RxMessage.Data[0]==0xFA	&&	RxMessage.Data[1]==0x55)	//运行到指定窗口命令
				{
					CMDOfWindow	=	RxMessage.Data[2];
				}	
			}
		}
		
		if(RunToWindow!=0	&&	SensorON!=1)			//电机在运转---需要传感器板返回传感器信号
		{
			Sensor[0]	=	0xAF;
			Sensor[1]	=	0x01;
			SensorON	=	1;
			CAN_StdTX_DATA(MotorRL_ID,2,Sensor);				//CAN使用标准帧发送数据
			memset(Sensor,0x00,2);
		}
		else if(RunToWindow==0	&&	SensorON!=0)				//电机停止运转---传感器板停止采集信号
		{
			Sensor[0]	=	0xAF;
			Sensor[1]	=	0x00;
			SensorON	=	0;
			CAN_StdTX_DATA(MotorRL_ID,2,Sensor);				//CAN使用标准帧发送数据
			memset(Sensor,0x00,2);
		}
	}
}

/*******************************************************************************
*函数名			:	function
*功能描述		:	函数功能说明
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	
*******************************************************************************/
void Switch_Server(sSYSDef* sUser)			//检查拔码地址有无变更，如果变更，重新配置运行参数
{
	
	SWITCHID_Read(&(sUser->sPlu.SWITCHID));		//
	
	if(((sUser->sPlu.SWITCHID.nSWITCHID)&0x3F)	!=	SwitchData)
	{
		Reset_Data();		//复位所有的全局变量值
		SwitchData	=	(sUser->sPlu.SWITCHID.nSWITCHID)&0x3F;
		PC006V21_Configuration();
	}
	else if(((sUser->sPlu.SWITCHID.nSWITCHID)&0x3F)	==	0x00)		//拨码未拨，循环配置
	{
		PC006V21_Configuration();
	}
}
/*******************************************************************************
*函数名			:	function
*功能描述		:	function
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
void Data_Initialize(void)		//参数初始化
{

}

/*******************************************************************************
*函数名			:	function
*功能描述		:	函数功能说明
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	
*******************************************************************************/
void Reset_Data(void)		//复位所有的全局变量值
{
	SwitchData	=	0;	//存储拔码开关最新地址，如果地址变化，再重新配置运行参数
	SensorRL		=	0;	//传感器板标志，0-非旋转传感器板，1-旋转传感器板
	MotorRL		=	0;	//旋转电机控制板标志，0-非旋转电机控制板，1-旋转电机控制板
	MotorUD		=	0;	//升降电机控制板标志，0-非升降电机控制，1-升降电机控制
	MotorTime	=	0;	//旋转电机测试运行时间

	SYSTime=0;

	memset(Sensor,0x00,4);	//4个传感器感应值存储区
	SensorON		=	0	;				//旋转电机控制板发来开启传感器采集命令BUFFER[0]=0XAF BUFFER[1]=0关，=1开，0--不采集信号，1-采集信号0.5ms主动上报/电机控制板来储存是否开启传感器标志

	RunToWindow	=	0;				//旋转到相应窗口 0-无，1-1号，2-2号，3-3号，4-4号
	StatusOfWindow	=	0;		//当时停止位置：0-未初始化，1-原点，2-2号窗口，3-3号窗口，4-4号窗口
	CMDOfWindow	=	0;				//运行到指定窗口命令
}



#endif
