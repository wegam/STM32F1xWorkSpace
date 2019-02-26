#ifdef TLE5012BV2

#include "TLE5012BV2.H"

#include "string.h"				//串和内存操作函数头文件
//#include "stm32f10x_dma.h"



#include "STM32F10x_BitBand.H"
#include "STM32_GPIO.H"
#include "STM32_SYS.H"
#include "STM32_SYSTICK.H"
#include "STM32_WDG.H"
#include "STM32_PWM.H"
#include "STM32_SPI.H"
#include "STM32_FLASH.H"




#define	TLE5012StartAddr	0x08008000		//原点值在MCU内部FLASH的存储地址

#define	ErrAngle	10						//允许偏差角度范围(正负偏差)

#define	Divisor		360						//求余除数
#define	StopAngle	5							//运行时，提前停止角度，例如，一个周期需要旋转300度的计数，在300-StopAngle后，停止电机控制，剩余的角度偏差由原点校正函数处理
#define	AngleCountPerCycle 	360	//一个运行周期需要的角度计数(四拨片分拣机拨一次需要360度)
#define	AngleCountStopDr 			(AngleCountPerCycle-StopAngle)	//计数到达AngleCountStopDr后停止电机驱动，剩下角度偏差由原点控制程序处理

SPIDef	TLE5012;

//--------------------------标志变量
unsigned short	testflg	=	0;				//正反转标志,0-停止，1-正转，-1-反转
unsigned char	MotorRunFlg	=	0;		//电机运行标志,0-不支行，1-正转，2-反转

unsigned char SetFlag=0;	//设置标志：0--正常状态，1-设置状态

//--------------------------角度变量
unsigned	short Organgle	=	0;							//原点角度值
unsigned	short angle1		=	0,angle2	=	0;	//角度值，通过对比两个角度值确认旋转方向
unsigned	short	DeviationAngle	=	0;				//当前角度与原点偏移值
unsigned	short anglecount	=	0;						//角度计数器，每次启动电机前需要清零

//--------------------------时间变量
unsigned	short testtime	=	0;
unsigned	short readdelay	=	0;
unsigned	short timedelay	=	0;
unsigned	short SYSLEDtime=	0;



//--------------------------临时变量
unsigned	short i=0;
//=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>
//->函数名		:	
//->功能描述	:	 
//->输入		:	
//->输出		:
//->返回 		:
//<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=
void TLE5012BV2_Configuration(void)
{	
	SYS_Configuration();					//系统配置---打开系统时钟 STM32_SYS.H	
	
	//-----------------------SYSLED脚
	GPIO_Configuration_OPP50(SYSLED_Port,SYSLED_Pin);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605
	//-----------------------TLE CLK脚
	PWM_OUT(TIM2,PWM_OUTChannel4,80000,500);						//PWM设定-20161127版本

	//-----------------------SetKey脚:设定原点值按键
	GPIO_Configuration_IPU(SetKey_Port,SetKey_Pin);			//将GPIO相应管脚配置为上拉输入模式----V20170605
	
	//-----------------------TLE5012 SPI配置
	SPI5012B_Init();
	//-----------------------电机控制接口
	GPIO_Configuration_OPP50(GPIOA,GPIO_Pin_1);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605
	GPIO_Configuration_OPP50(GPIOA,GPIO_Pin_2);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605
	//GPIO_Configuration_OPP50(GPIOA,GPIO_Pin_9);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605
	//GPIO_Toggle	(GPIOA,GPIO_Pin_9);		//将GPIO相应管脚输出翻转----V20170605
	MSTP();
	//-----------------------模组控制接口(原模组控制电机接口)
	GPIO_Configuration_IPU(CWtargePort,CWtargePin);			//将GPIO相应管脚配置为上拉输入模式----V20170605
	GPIO_Configuration_IPU(CCWtargePort,CCWtargePin);		//将GPIO相应管脚配置为上拉输入模式----V20170605
	
  
	SysTick_DeleymS(1000);				//SysTick延时nmS
	
	//-----------------------------读取原点值
	STM32_FLASH_Read(TLE5012StartAddr,(unsigned short*)&Organgle,2);							//从指定地址开始读出指定长度的数据
	
	//-----------------------等待计读数稳定
	for(i=0;i<30;i++)
	angle1	=	ReadAngle();	//读后读取的角度值认为是原点值
	//-----------------------初始化相关数据
	SysTick_DeleymS(200);				//SysTick延时nmS
	IWDG_Configuration(1000);													//独立看门狗配置---参数单位ms
	//-----------------------
  SysTick_Configuration(1000);    //系统嘀嗒时钟配置72MHz,单位为uS
	
	//-----------------------
	while(1)
	{
		if(0==SetFlag)//正常运行状态
		{
			//---------------------电机控制程序
			MOTORT();	
			//---------------------原点定位程序
			SetOrig();
			if(anglecount>=AngleCountStopDr)		//预设一个触发旋转角度：到达角度后停，由原点定位程序来控制停止位
			{
				MotorRunFlg	=	0;
			}	
		}		
	}
}

//=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>
//->函数名		:	
//->功能描述	:	 
//->输入		:	
//->输出		:
//->返回 		:
//<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=
void TLE5012BV2_Server(void)
{	
	unsigned char result=0;
	//---------------------看门狗
	IWDG_Feed();
	
	//---------------------设置键
	SetKeyServer();
	
	//=====================================原点设置模式：按键触发原点设置功能
	if(0!=SetFlag)		//设置状态
	{
		if(SYSLEDtime++>=50)		//设置时按键指示灯快速闪烁
		{
			SYSLEDtime=0;
			GPIO_Toggle	(SYSLED_Port,SYSLED_Pin);		//将GPIO相应管脚输出翻转----V20170605
		}
		MSTP();	//释放电机控制
		MotorRunFlg	=	0;			//正反转标志
		Organgle	=	ReadAngle();	//读后读取的角度值认为是原点值
		angle1=Organgle;
		angle2=Organgle;
		//-----------------------------保存原点值
		STM32_FLASH_Write(TLE5012StartAddr,(unsigned short*)&Organgle,2);						//从指定地址写入指定长度的数据
		return;		
	}
	//=====================================运行LED：正常运行时闪烁周期为1秒
	if(SYSLEDtime++>=500)
	{
		SYSLEDtime=0;
		GPIO_Toggle	(SYSLED_Port,SYSLED_Pin);		//将GPIO相应管脚输出翻转----V20170605
	}
	
	goto ActivateModel;	//外部触发模式
	
	//=====================================测试模式：定时正反转
	TestModel:				//测试模式
	if(testtime++>8000)
	{		
		testtime	=	0;
	}
	if(0	==	testtime)
	{		
		angle1	=	ReadAngle();
		angle1	=	ReadAngle();
		angle2	=	angle1;
		
		MotorRunFlg	=	1;		//正转
		anglecount	=	0;
	}
	else if(3000	==	testtime)
	{		
		angle1	=	ReadAngle();
		angle1	=	ReadAngle();
		angle2	=	angle1;
		
		MotorRunFlg	=	2;		//反转
		anglecount	=	0;
	}
	else if(6000<testtime)
	{
		MotorRunFlg	=	0;
		anglecount	=	0;
	}	
	return;
	
	//=====================================外部触发模式：根据触发信号控制正反转
	ActivateModel:			//外部触发模式
	if(timedelay>0)			//读到触发信号后需要等待一段时间才可以两次读触发信号:单位ms
	{
		timedelay--;
		return;
	}
	//---------------------读触发信号：正转触发
	result=GPIO_ReadInputDataBit(CWtargePort,CWtargePin);
	if(0==result)
	{
		angle1	=	ReadAngle();
		//angle1	=	ReadAngle();
		angle2	=	angle1;
		
		MotorRunFlg	=	1;		//正转
		anglecount	=	0;
		timedelay=50;
	}
	//---------------------读触发信号：反转触发
	result=GPIO_ReadInputDataBit(CCWtargePort,CCWtargePin);
	if(0==result)
	{
		angle1	=	ReadAngle();
		//angle1	=	ReadAngle();
		angle2	=	angle1;
		
		MotorRunFlg	=	2;		//反转
		anglecount	=	0;
		timedelay=50;
	}
	return;
}
/*******************************************************************************
* 函数名			:	function
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
unsigned char SetKeyServer(void)
{
	unsigned char result=GPIO_ReadInputDataBit(SetKey_Port,SetKey_Pin);
	static unsigned short keytime=0;
	static unsigned	char	keyon=0;	//按键被按下未松开标志
	if(0==result)	//按键被按下
	{
		if(0==keyon)
		{
			if(keytime++>20)	//按键防抖时间ms
			{
				keyon=1;
				if(0==SetFlag)	//原来为设置状态
				{
					SetFlag=1;		//进入设置状态
				}
				else
				{
					SetFlag=0;		//设置完成，进入正常状态
				}
			}			
		}
	}
	else
	{
		keyon=0;
		keytime=0;
	}
	return result;
}
/*******************************************************************************
* 函数名			:	MOTORT
* 功能描述		:	电机控制程序 
* 输入			: void
* 返回值			: void
* 修改时间		: 20190225
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
void MOTORT(void)
{	
	//---------------------电机没有运行
	if(0==MotorRunFlg)
	{
		return;
	}
	//---------------------
	if(readdelay++<2)
	{
		return;
	}
	readdelay	=	0;
	//---------------------读取当前位置角度值
	angle2	=	ReadAngle();
	
	//=====================================电机正转角度计数：角度增量方向运行：正转角度计数，angle2>angle1，注意角度到达360度后会归零
	if(2==MotorRunFlg)	//正转标志
	{	
		//--------------------角度顺序增加(未过360度临界值)
		if(angle2>angle1)
		{
			anglecount+=angle2-angle1;
		}
		//--------------------已过临界点
		else
		{
			unsigned	short AngleTemp=0;
			//------------------计算上次角度与临界点差值
			AngleTemp=360-angle1;
			//------------------角度计数：
			anglecount+=AngleTemp+angle2;
		}
	}	
	//=====================================电机反转角度计数：角度减量方向运行：反转角度计数，angle2<angle1，注意角度到达0度后会变成360
	else if(1==MotorRunFlg)	//反转标志
	{
		//--------------------角度顺序减小(未过0度临界值)
		if(angle1>angle2)
		{
			anglecount+=angle1-angle2;
		}
		//--------------------已过临界点
		else
		{
			unsigned	short AngleTemp=0;
			//------------------计算此次角度与临界点差值
			AngleTemp=360-angle2;
			//------------------角度计数：
			anglecount+=AngleTemp+angle1;
		}
	}
	//--------------------更新对比角度值
	angle1	=	angle2;
	//--------------------判断角度计数有无达到预期
	if(anglecount>=AngleCountStopDr)		//预设一个触发旋转角度：到达角度后停，由原点定位程序来控制停止位
	{
		MotorRunFlg	=	0;
	}
	//=====================================电机驱动控制
	if(1	==	MotorRunFlg)
		MCW();
	else if(2	==	MotorRunFlg)
		MCCW();
	else
		MSTP();	
	return;
}
/*******************************************************************************
* 函数名			:	MOTORT
* 功能描述		:	电机控制程序 
* 输入			: void
* 返回值			: void
* 修改时间		: 20190101
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
void MOTORTBAC(void)
{	
	//---------------------电机没有运行
	if(0==MotorRunFlg)
	{
		return;
	}
	//---------------------
	if(readdelay++<2)
	{
		return;
	}
	readdelay	=	0;
	//---------------------读取当前位置角度值
	angle2	=	ReadAngle();
	
	//=====================================电机正转角度计数：角度增量方向运行：正转角度计数，angle2>angle1，注意角度到达360度后会归零
	if(2==MotorRunFlg)
	{	
		//--------------------超过180度：
		if(angle2-angle1>120)
			anglecount+=360-angle2+angle1;
		
		//--------------------角度增加：增加角度计数
		else if(angle2>angle1)
			anglecount+=angle2-angle1;
		
		//--------------------回调时(无效，由原点校正函数处理)：角度计数需要减
		else if(anglecount>0)
		{
			if(angle1-angle2>120)
				anglecount-=360-angle1+angle2;
			else
				anglecount-=angle1-angle2;
		}
	}	
	//=====================================电机反转角度计数：角度减量方向运行：反转角度计数，angle2<angle1，注意角度到达0度后会变成360
	else if(1==MotorRunFlg)	//减量方向运行：反转角度计数
	{
		//--------------------超过180度：
		if(angle1-angle2>120)
			anglecount+=360-angle1+angle2;
		
		//--------------------角度增加：增加角度计数
		else if(angle1>angle2)
			anglecount+=angle1-angle2;
		
		//--------------------回调时(无效，由原点校正函数处理)：角度计数需要减
		else if(anglecount>0)
		{
			if(angle2-angle1>120)
				anglecount-=360-angle2+angle1;
			else
				anglecount-=angle2-angle1;
		}
	}
	//--------------------更新对比角度值
	angle1	=	angle2;
	//=====================================电机驱动控制
	if(1	==	MotorRunFlg)
		MCW();
	else if(2	==	MotorRunFlg)
		MCCW();
	else
		MSTP();	
	return;
}
/*******************************************************************************
* 函数名			:	SetOrig
* 功能描述		:	原点定位程序
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
void SetOrig(void)
{
	//DeviationAngle	//允许偏差角度范围(正负偏差)
	
	if(0!=MotorRunFlg)		//电机运行中，
		return;
	
	//--------------------读取当前角度
	angle1	=	ReadAngle();
	//--------------------
	DeviationAngle	=	((angle1+Organgle)>>1)%(Divisor);
	
	goto SetOrigtest2;	//选用模式2测试
	
	//=============================测试模式1
	SetOrigtest1:
	if((angle1>Organgle)&&(angle1-Organgle>ErrAngle))
	{
		MCCW();
	}
	else if((angle1<Organgle)&&(Organgle-angle1>ErrAngle))
	{
		MCW();
	}
	else
	{
		MSTP();
	}
	return;		//退出，不往下执行
	
	//=============================测试模式2
	SetOrigtest2:
	
	DeviationAngle=360-Organgle;		//原点偏差
	DeviationAngle=(angle1+DeviationAngle)%(Divisor);	//
	if(DeviationAngle<=ErrAngle||(360-DeviationAngle)<=ErrAngle)		//在允许误差范围内
	{
		MSTP();
	}
	else			//大于允许误差
	{
		if(DeviationAngle>180)
		{
			MCCW();
		}
		else if(DeviationAngle<180)
		{
			MCW();
		}
	}	
	return;		//退出，不往下执行	
}

/*******************************************************************************
* 函数名			:	ReadAngle
* 功能描述		:	得到 0~359 度
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
unsigned short ReadAngle(void)
{
	return ( ReadValue(READ_ANGLE_VALUE) * 360 / 0x10000 );
}
/*******************************************************************************
* 函数名			:	ReadSpeed
* 功能描述		:	得到角速度
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
unsigned short ReadSpeed(void)
{
	return ReadValue(READ_SPEED_VALUE);
}


unsigned short ReadValue(unsigned short u16RegValue)
{
	unsigned short u16Data;
//	unsigned short i	=	5;
	SPI_CS_ENABLE;
	
	SPIx_ReadWriteByte(u16RegValue);
  SPI_TX_OFF;
//	while(i--);
	//发送 0xFFFF 是无用的，可能是为了有时钟
	u16Data = ( SPIx_ReadWriteByte(0xffff) & 0x7FFF ) << 1;//0x12/0xff*100k
	
	SPI_CS_DISABLE;
  SPI_TX_ON;
	
	return(u16Data);
}

unsigned short SPIx_ReadWriteByte(unsigned short byte)
{
	unsigned short retry = 0;
	while( (SPI1->SR&1<<1) == 0 )//发送缓冲区非空
	{
		if( ++retry > 200 )
			return 0;//延迟一段时间后返回
	}
	SPI1->DR = byte;     //发送数据
	
	retry = 0;
	while( (SPI1->SR&1<<0) == 0 ) //接收缓冲区为空
	{
		if( ++retry > 200 )
			return 0;//延迟一段时间后返回
	}
	return SPI1->DR;          //读一下缓冲区，清标志
}
void SPI5012B_Init(void)
{
	SPI_InitTypeDef  SPI_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_SPI1,ENABLE );
	
	//以下二句，在它处声明，请增加使用
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO,ENABLE);
	//GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable,ENABLE);//使JTDO、JTDI、JTCK 当成普通IO口进行操作
	//GPIOB0 当成普通IO口进行操作
	
	/*SPI: NSS,SCK,MISO and MOSI */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;//PA5--CLK--复用推挽
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//GPIO_StructInit(&GPIO_InitStructure);
	
	/* Configure PA6 as encoder input */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;//PA6--MISO--输入
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	/* PA7*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//PA7--MOSI--推挽输出
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_CS_Pin_Name;//PB0--CS--推挽输出
	GPIO_Init(GPIO_CS_Pin_Type, &GPIO_InitStructure);
	
	/**********SPI****************/
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;//SPI1--双线全双工！！
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_16b;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_32;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_CRCPolynomial = 7;
	
	SPI_Init(SPI1, &SPI_InitStructure);
	SPI_Cmd(SPI1, ENABLE);
}
/*******************************************************************************
* 函数名			:	function
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
void MCW(void)
{
	testflg=1;	//正反转标志,0-停止，1-正转，-1-反转
	PA1	=	0;
	PA2	=	1;
}
/*******************************************************************************
* 函数名			:	function
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
void MCCW(void)
{
	testflg=-1;	//正反转标志,0-停止，1-正转，-1-反转
	PA1	=	1;
	PA2	=	0;
}
/*******************************************************************************
* 函数名			:	function
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
void MSTP(void)
{
	testflg=0;	//正反转标志,0-停止，1-正转，-1-反转
	PA1	=	0;
	PA2	=	0;
}

#endif
