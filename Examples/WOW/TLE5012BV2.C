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




#define	TLE5012StartAddr	0x0800C800		//原点值在MCU内部FLASH的存储地址50K地址，按64Kflash应用

#define TOPSMT	1			//0--原安装方式，传感器芯片反而装，1--传感器芯片与MCU同面装

#define WeiNum  4     //两/四片拨片

#if WeiNum==2   //两拨片，拨一次405度
  #define	OrigErrAngle	20			  		//原点调整允许偏差角度范围(正负偏差)
  #define	StopAngle	3*OrigErrAngle		//运行时，提前停止角度，例如，一个周期需要旋转300度的计数，在300-StopAngle后，停止电机控制，剩余的角度偏差由原点校正函数处理
  #define	AngleCountPerCycle 	405			//一个运行周期需要的角度计数(四拨片分拣机拨一次需要360，二拨片的为405度)  
#else   //4拨片，每拨一次刚好360度
  #define	OrigErrAngle	10			  //原点调整允许偏差角度范围(正负偏差)
  #define	StopAngle	30							//运行时，提前停止角度，例如，一个周期需要旋转300度的计数，在300-StopAngle后，停止电机控制，剩余的角度偏差由原点校正函数处理
  #define	AngleCountPerCycle 	360	//一个运行周期需要的角度计数(四拨片分拣机拨一次需要360，二拨片的为405度)
#endif

//#define	Divisor		360						//求余除数
#define	AngleCountStopDr 			(AngleCountPerCycle-StopAngle)	//计数到达AngleCountStopDr后停止电机驱动，剩下角度偏差由原点控制程序处理

SPIDef	TLE5012;

//--------------------------标志变量
unsigned char	MotorRunFlg	=	0;		//电机运行标志,0-不运行，1-正转，2-反转

unsigned char SetFlag=0;	//设置标志：0--正常状态，1-设置状态
unsigned char ErrFlag=0;	//错误标志：0--正常状态，1-错误状态

//--------------------------角度变量
unsigned	long Organgle	=	0;							  //原点角度值
unsigned	short angleCmp		=	0;					  //角度值，通过对比两个角度值确认旋转方向
unsigned	short anglelive	=	0;							//实时角度值，通过对比两个角度值确认旋转方向
unsigned	short	DeviationAngle	=	0;				//当前角度与原点偏移值
unsigned	short anglecount	=	0;						//角度计数器，每次启动电机前需要清零

//--------------------------时间变量
unsigned	short testtime	=	0;
unsigned	short readdelay	=	0;    //读取数据简单时间间隔
//unsigned	short	Triggerdelay	=	0;	//触发信号延时
unsigned	short SYSLEDtime=	0;

#define ArrSize 800
unsigned short AngleArr[ArrSize]={0};
unsigned short SampleCount=0;
unsigned short delaytime=0;


//--------------------------临时变量
unsigned	short i=0;

void ReadError(void);
void RecordData(unsigned short data);
//=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>
//->函数名		:	
//->功能描述	:	 
//->输入		:	
//->输出		:
//->返回 		:
//<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=
void TLE5012BV2_Configuration(void)
{	
	//-----------------------系统配置---打开系统时钟 STM32_SYS.H
	SYS_Configuration();
	
	//-----------------------TLE5012 SPI配置
	SPI5012B_Init();	
	//-----------------------TLE5012 CLK脚
	PWM_OUT(TIM2,PWM_OUTChannel4,80000,500);						//PWM设定-20161127版本
	
	//-----------------------SYSLED脚
	GPIO_Configuration_OPP50(SYSLED_Port,SYSLED_Pin);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605	

	//-----------------------触发信号输入接口
	GPIO_Configuration_IPU(CWtargePort,CWtargePin);			//将GPIO相应管脚配置为上拉输入模式----V20170605
	GPIO_Configuration_IPU(CCWtargePort,CCWtargePin);		//将GPIO相应管脚配置为上拉输入模式----V20170605
	
	//-----------------------SetKey脚:设定原点值按键
	GPIO_Configuration_IPU(SetKey_Port,SetKey_Pin);			//将GPIO相应管脚配置为上拉输入模式----V20170605	
	
	//-----------------------电机控制接口
	GPIO_Configuration_OPP50(GPIOA,GPIO_Pin_1);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605
	GPIO_Configuration_OPP50(GPIOA,GPIO_Pin_2);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605

	MSTP();	
  
	SysTick_DeleymS(500);				//SysTick延时nmS
	
	//-----------------------------读取备份原点值
	STM32_FLASH_Read(TLE5012StartAddr,(unsigned short*)&Organgle,2);							//从指定地址开始读出指定长度的数据
	//-----------------------------转换为角度值(防止读出的数据大于360)
	Organgle=Organgle%360;	
	
	//-----------------------等待计读数稳定
	SysTick_DeleymS(500);				//SysTick延时nmS
	for(i=0;i<30;i++)
		anglelive	=	ReadAngle();	//读后读取的角度值认为是原点值
#if WeiNum==2   //两拨片，拨一次405度,启动位置当原点
  Organgle  = anglelive;
#endif
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
		}		
	}
}

//=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>
//->函数名		:	TLE5012BV2_Server
//->功能描述	:	触发及设置，程序扫描周期1ms
//->输入		:	
//->输出		:
//->返回 		:
//<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=
void TLE5012BV2_Server(void)
{	
	unsigned char result=0;
	//---------------------看门狗
	IWDG_Feed();
	
  //---------------------
  if(ErrFlag)
    return;
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
		angleCmp=Organgle;
		anglelive=Organgle;
		
		return;		
	}
	//=====================================运行LED：正常运行时闪烁周期为1秒
	if(SYSLEDtime++>=500)
	{
		SYSLEDtime=0;
		GPIO_Toggle	(SYSLED_Port,SYSLED_Pin);		//将GPIO相应管脚输出翻转----V20170605
	}
	
	if(0!=MotorRunFlg)	//电机忙，不检查触发信号
	{    
		return;
	}
  if(delaytime>0)   //电机停止后等待时间才可以再次触发运行
  {
    delaytime--;
    testtime	=	0;
    return;
  }
	goto ActivateModel;	//外部触发模式
  //goto TestModel2;	//正转测试
  //goto TestModel3;	//反转测试
	
	//=====================================测试模式：定时正反转
  TestModel2:				//正转测试
	if(testtime++>200)
	{		
		testtime	=	0;

		angleCmp	=	ReadAngle();
		anglelive	=	angleCmp;
		
		MotorRunFlg	=	2;		//正转
		anglecount	=	0;
    
    Organgle=AngleCountPerCycle-360+Organgle;
    Organgle=Organgle%360;
	}
	return;
  
  TestModel3:				//反转测试
	if(testtime++>200)
	{		
		testtime	=	0;
    SampleCount=0;
    memset(AngleArr,0x00,ArrSize);
	}
	if(0	==	testtime)
	{		
		angleCmp	=	ReadAngle();
		anglelive	=	angleCmp;
		
		MotorRunFlg	=	1;		//反转
		anglecount	=	0;
    
    Organgle=360*2+Organgle-AngleCountPerCycle;    
    Organgle=Organgle%360;
	}
	return;
	
	//=====================================外部触发模式：根据触发信号控制正反转
	ActivateModel:			//外部触发模式
  if(delaytime>0)
  {
    delaytime--;
    return;
  }
	//---------------------读触发信号：正转触发--角度增加
	result=GPIO_ReadInputDataBit(CWtargePort,CWtargePin);
	if(0==result)
	{
		angleCmp	=	ReadAngle();
		anglelive	=	angleCmp;
		
		MotorRunFlg	=	2;		//正转
		anglecount	=	0;
    //------------------计算新的原点角度
    //----------正转计算2
    Organgle=AngleCountPerCycle-360+Organgle;
    //----------反转计算1
    //Organgle=360*2+Organgle-AngleCountPerCycle;
    Organgle=Organgle%360;
     
    //Organgle=(Organgle+AngleCountPerCycle)%360;
    //Organgle=720+Organgle-AngleCountPerCycle;
		return;
	}
	//---------------------读触发信号：反转触发--角度减小
	result=GPIO_ReadInputDataBit(CCWtargePort,CCWtargePin);
	if(0==result)
	{
		angleCmp	=	ReadAngle();
		anglelive	=	angleCmp;
		
		MotorRunFlg	=	1;		//反转
		anglecount	=	0;
    //------------------计算新的原点角度
    //----------正转计算2
    //Organgle=AngleCountPerCycle-360+Organgle;
    //----------反转计算1
    Organgle=360*2+Organgle-AngleCountPerCycle;    
    Organgle=Organgle%360;
		return;
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
				if(0==SetFlag)	//原来为正常状态
				{
					SetFlag=1;		//进入设置状态
				}
				else
				{
          unsigned short tempAngle=0;
          unsigned char i=0;
					//-----------------------------保存原点值
          while(i++<10&&Organgle!=tempAngle)
          {            
            STM32_FLASH_Write(TLE5012StartAddr,(unsigned short*)&Organgle,2);						//从指定地址写入指定长度的数据
            SysTick_DeleymS(2);				//SysTick延时nmS
          }
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
	//---------------------等电机运行一段时间后再开始读角度数据
	if(readdelay++<100)
	{
		return;
	}
	readdelay	=	0;
	//---------------------读取当前位置角度值
	anglelive	=	ReadAngle();
  
  if(anglelive==angleCmp)
    goto MotorRunning;
  
//  AngleArr[SampleCount++]=anglelive;
//	if(SampleCount>=360)
// {
//    SampleCount=0;
//  }
  
	//=====================================电机正转角度计数：角度增量方向运行：正转角度计数，angle2>angle1，注意角度到达360度后会归零
	if(2==MotorRunFlg)	//正转标志--角度增加
	{	
		unsigned	short AngleTemp=0;
		//--------------------角度顺序增加(未过360度临界值)+2的误差
		if(anglelive>angleCmp)
		{
			AngleTemp=anglelive-angleCmp;
      if(AngleTemp>30)  //每次角度计数应该在有限范围内
      {
        ReadError();
        return;
      }
      anglecount+=AngleTemp;
		}
		//--------------------已过临界点(过临界点时，按转速估计，上次读取的数据应该接近临界点)
		else if((angleCmp>anglelive)&&(angleCmp>270)&&(anglelive<90))
		{
			unsigned	short AngleTemp=0;
			//------------------计算上次角度与临界点差值
			AngleTemp=360-angleCmp;
			//------------------角度计数：
			AngleTemp=AngleTemp+anglelive;
      if(AngleTemp>30)  //每次角度计数应该在有限范围内
      {
        ReadError();
        return;
      }
        
      anglecount+=AngleTemp;
      
		}
		else
		{
			goto MotorRunning;
		}
	}	
	//=====================================电机反转角度计数：角度减量方向运行：反转角度计数，angle2<angle1，注意角度到达0度后会变成360
	else if(1==MotorRunFlg)	//反转标志-角度减小
	{
		unsigned	short AngleTemp=0;
		//--------------------角度顺序减小(未过0度临界值)+2的误差
		if(angleCmp>anglelive)
		{
			AngleTemp=angleCmp-anglelive;
      if(AngleTemp>30)  //每次角度计数应该在有限范围内
        return;
      anglecount+=AngleTemp;
		}
		//--------------------已过临界点(过临界点时，按转速估计，上次读取的数据应该接近临界点)
		else if((anglelive>angleCmp))
		{			
			//------------------计算此次角度与临界点差值+5的误差
			AngleTemp=360-anglelive;
			//------------------角度差计数：
			AngleTemp=AngleTemp+angleCmp;
      if(AngleTemp>30)  //每次角度计数应该在有限范围内
        return;
      anglecount+=AngleTemp;
		}
		else
		{
			goto MotorRunning;
		}
	}
	//--------------------更新对比角度值
	angleCmp	=	anglelive;
  //------------------记录数据
  //RecordData(anglecount);
	//--------------------判断角度计数有无达到预期
	if(anglecount>=AngleCountStopDr)		//预设一个触发旋转角度：到达角度后停，由原点定位程序来控制停止位
	{
		MotorRunFlg	=	0;		//0停止，1反转,2正转
    SampleCount=0;
		//anglecount=0;
	}
	//=====================================电机驱动控制
	MotorRunning:
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
  unsigned char RFWflag=0;
	if(0!=MotorRunFlg)		//电机运行中，
		return;
	//---------------------等电机运行一段时间后再开始读角度数据
	if(readdelay++<1000)
	{
		return;
	}
	readdelay	=	0;
	//--------------------读取当前角度
	anglelive	=	ReadAngle();
	
	goto SetOrigtest2;	//选用模式2测试
	
	//=============================测试模式1
	SetOrigtest1:
	if((anglelive>Organgle)&&(anglelive-Organgle>OrigErrAngle))
	{
		MCCW();
	}
	else if((anglelive<Organgle)&&(Organgle-anglelive>OrigErrAngle))
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
	
	DeviationAngle=360-Organgle;																//原点值离0角度点的偏差
  DeviationAngle=DeviationAngle+anglelive;    								//当前位置与原点之和  
  DeviationAngle=(DeviationAngle-(DeviationAngle/360)*360); 	//求出低于360度的数据,不能只求余数
  
  if(DeviationAngle>180)  //超过原点位置
  {
    RFWflag = 0;  //反转调
    DeviationAngle=360-DeviationAngle;    //求出偏离原点数据
  }
  else
  {
    RFWflag = 1;  //正转调 
  }

  RecordData(DeviationAngle);   //记录数据
  
	if(DeviationAngle<=OrigErrAngle)		//在允许误差范围内(正偏差和负偏差)
	{
		MSTP();
	}
	else			//大于允许误差
	{
		if(RFWflag)
		{
			MCW();
		}
		else
		{
			MCCW();
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

/*******************************************************************************
* 函数名			:	ReadValue
* 功能描述		:	读数据
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
unsigned short ReadValue(unsigned short u16RegValue)
{
	unsigned short u16Data;
//	unsigned short i	=	5;
	SPI_CS_ENABLE;
	
	SPIx_ReadWriteByte(u16RegValue);
  SPI_TX_OFF;
//	while(i--);
	//发送 0xFFFF 是无用的，可能是为了有时钟
	u16Data = ( SPIx_ReadWriteByte(0xFFFF) & 0x7FFF ) << 1;//0x12/0xff*100k
	
	SPI_CS_DISABLE;
  SPI_TX_ON;
	
	return(u16Data);
}
/*******************************************************************************
* 函数名			:	SPIx_ReadWriteByte
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
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
/*******************************************************************************
* 函数名			:	function
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
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
#if TOPSMT==1			//传感器芯片与MCU安装在同一面
	PA1	=	1;
	PA2	=	0;
#else 
	PA1	=	0;
	PA2	=	1;
#endif
  delaytime=50;  //ms
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
#if TOPSMT==1			//传感器芯片与MCU安装在同一面
	PA1	=	0;
	PA2	=	1;
#else 
	PA1	=	1;
	PA2	=	0;
#endif
  delaytime=50;  //ms
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
	PA1	=	0;
	PA2	=	0;
}
/*******************************************************************************
* 函数名			:	ReadError
* 功能描述		:	读数异常停止运行 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
void ReadError(void)
{
//  ErrFlag=1;
//  while(1)
//  {    
//    MSTP();
//    SetFlag = 1;
//  }
}
/*******************************************************************************
* 函数名			:	RecordData
* 功能描述		:	记录数据，调试观察数据使用 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
void RecordData(unsigned short data)
{
  
  AngleArr[SampleCount++]=data;
  if(SampleCount>=ArrSize)
    SampleCount=0;
  if(data>120)
  {
    ReadError();	//读数异常停止运行，观察记录的数据内容
  }
}
#endif
