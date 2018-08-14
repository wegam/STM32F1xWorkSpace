#include "CS5530.H"

#include "STM32_GPIO.H"
#include "STM32_SYSTICK.H"

#include 	"TOOL.H"

#include "stdint.h"
#include "stdlib.h"



//#define CS5530_CS_LOW()			((pInfo->pGPIOxCS)->BRR = pInfo->pinCS)
//#define CS5530_CS_HIGH()		((pInfo->pGPIOxCS)->BSRR = pInfo->pinCS)
//#define CS5530_SDI_LOW()		((g_CS5530PinInfo->pGPIOxSDI)->BRR = g_CS5530PinInfo->pinSDI)
//#define CS5530_SDI_HIGH()		((g_CS5530PinInfo->pGPIOxSDI)->BSRR = g_CS5530PinInfo->pinSDI)
//#define CS5530_SDO_STATE()	((g_CS5530PinInfo->pGPIOxSDO)->IDR & g_CS5530PinInfo->pinSDO)
//#define CS5530_SCLK_LOW()		((g_CS5530PinInfo->pGPIOxSCLK)->BRR = g_CS5530PinInfo->pinSCLK)
//#define CS5530_SCLK_HIGH()	((g_CS5530PinInfo->pGPIOxSCLK)->BSRR = g_CS5530PinInfo->pinSCLK)
unsigned long CS5530_Status=0x00;







/*******************************************************************************
* 函数名			:	function
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
*******************************************************************************/
void CS5530_Delay(u32 time)
{
	while(time--);
//	SysTick_DeleyuS(2);				//SysTick延时nmS
}

/*******************************************************************************
* 函数名			:	function
* 功能描述		:	称重板
* 输入			: void
* 返回值			: void
*******************************************************************************/
u8 CS5530_SDO_STATE(CS5530Def *pInfo)
{
	return(GPIO_ReadInputDataBit(pInfo->Port.SDO_PORT, pInfo->Port.SDO_Pin));
}
/*******************************************************************************
* 函数名			:	function
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
*******************************************************************************/
void CS5530_Initialize(CS5530Def *pInfo)
{
	unsigned long *p=(unsigned long*)&(pInfo->Flag);		//获取数据结构体地址,以便将读取的数据保存
	
	GPIO_Configuration_OPP50	(pInfo->Port.CS_PORT,		pInfo->Port.CS_Pin);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度2MHz----V20170605
	GPIO_Configuration_OPP50	(pInfo->Port.SDI_PORT,	pInfo->Port.SDI_Pin);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度2MHz----V20170605
	GPIO_Configuration_OPP50	(pInfo->Port.SCLK_PORT,	pInfo->Port.SCLK_Pin);		//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度2MHz----V20170605
	GPIO_Configuration_IPU		(pInfo->Port.SDO_PORT,	pInfo->Port.SDO_Pin);			//将GPIO相应管脚配置为上拉输入模式----V20170605
	
	CS5530_PowerUp(pInfo);		//CS5530上电及初始化
	
	//数据初始化
	*p	=	0;		//pInfo->Flag初始化
//	pInfo->Data.Origin	=	0;	//原点
//	pInfo->Data.WeighPie=	0;	//单重	
}
/*******************************************************************************
* 函数名			:	function
* 功能描述		:	称重板
* 输入			: void
* 返回值			: void
*******************************************************************************/
void CS5530_WriteOneByte(CS5530Def *pInfo, u8 dat)
{
	u8 i;
	u16 delayTime	=	1000;
	pInfo->Port.SCLK_PORT->BRR    = pInfo->Port.SCLK_Pin;   //SCLK==0
	SysTick_DeleyuS(100);				//SysTick延时nuS
	for(i=0; i<8; i++)
	{
		if((dat&0x80) != 0)
      pInfo->Port.SDI_PORT->BSRR  = pInfo->Port.SDI_Pin;    //SDI==1
		else
      pInfo->Port.SDI_PORT->BRR   = pInfo->Port.SDI_Pin;    //SDI==0
		
		SysTick_DeleyuS(200);				//SysTick延时nuS
    pInfo->Port.SCLK_PORT->BSRR   = pInfo->Port.SCLK_Pin;   //SCLK==1
		SysTick_DeleyuS(200);				//SysTick延时nuS
    pInfo->Port.SCLK_PORT->BRR    = pInfo->Port.SCLK_Pin;   //SCLK==0
		dat <<= 1;
	}
}

/*******************************************************************************
* 函数名			:	function
* 功能描述		:	函数功能说明
* 输入			: void
* 返回值			: void
*******************************************************************************/
void CS5530_WriteCommand(CS5530Def *pInfo,u8 command)
{
	CS5530_WriteOneByte(pInfo,command);
}
/*******************************************************************************
* 函数名			:	function
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
*******************************************************************************/
void CS5530_WriteRegister(CS5530Def *pInfo, u8 command,u32 setData)
{
//	unsigned long temp=0xFFFFFFFF;
	CS5530_WriteOneByte(pInfo, command);
	CS5530_WriteOneByte(pInfo, (uint8_t)(setData>>24));
	CS5530_WriteOneByte(pInfo, (uint8_t)(setData>>16));
	CS5530_WriteOneByte(pInfo, (uint8_t)(setData>>8));
	CS5530_WriteOneByte(pInfo, (uint8_t)(setData>>0));
}

/*******************************************************************************
* 函数名			:	function
* 功能描述		:	称重板
* 输入			: void
* 返回值			: void
*******************************************************************************/
unsigned char CS5530_ReadOneByte(CS5530Def *pInfo)
{
	uint8_t i;
	uint8_t reValue=0;
  pInfo->Port.SDI_PORT->BRR    = pInfo->Port.SDI_Pin;       //SDI==0
	SysTick_DeleyuS(100);				//SysTick延时nuS
	for(i=0; i<8; i++)
	{	
		SysTick_DeleyuS(100);				//SysTick延时nuS
    pInfo->Port.SCLK_PORT->BSRR   = pInfo->Port.SCLK_Pin;   //SCLK==1
		reValue <<= 1;
		SysTick_DeleyuS(100);				//SysTick延时nuS
		if(CS5530_SDO_STATE(pInfo))
			reValue++;
		SysTick_DeleyuS(100);				//SysTick延时nuS
    pInfo->Port.SCLK_PORT->BRR    = pInfo->Port.SCLK_Pin;   //SCLK==0		
	}
	SysTick_DeleyuS(100);				//SysTick延时nuS

	return reValue;
}
/*******************************************************************************
* 函数名			:	function
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
*******************************************************************************/
u32 CS5530_GetADData(CS5530Def *pInfo)
{
	u32 reValue=0;	

//		CS5530_WriteOneByte(pInfo, CS5530_CONTINUOUS_ON);		///*继续连续转换模式*/
		pInfo->Port.SDI_PORT->BRR    = pInfo->Port.SDI_Pin;       //SDI==0
		CS5530_ReadOneByte(pInfo);
		reValue = ((u32)CS5530_ReadOneByte(pInfo)<<24)
						+((uint32_t)CS5530_ReadOneByte(pInfo)<<16)
						+((uint32_t)CS5530_ReadOneByte(pInfo)<<8)
						+(uint32_t)CS5530_ReadOneByte(pInfo);
	return reValue;
}
/*******************************************************************************
* 函数名			:	function
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
*******************************************************************************/
u32 CS5530_ReadRegister(CS5530Def *pInfo, u8 command)
{
	volatile unsigned long temp=0x00;
	
	CS5530_WriteOneByte(pInfo, command);
	temp = (CS5530_ReadOneByte(pInfo)<<24)
				+(CS5530_ReadOneByte(pInfo)<<16)
				+(CS5530_ReadOneByte(pInfo)<<8)
				+CS5530_ReadOneByte(pInfo);
	
	return temp;
}
/*******************************************************************************
* 函数名			:	function
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
*******************************************************************************/
void CS5530_ClearBuf(CS5530Def *pInfo)
{
//	uint8_t i;

//	__disable_irq();
//	pInfo->continuousOFCount = 0;
//	for(i=0; i<pInfo->dataBufSize; i++)
//		pInfo->pDataBuf[i] = 0xFFFFFFFF;
//	pInfo->dataPtr = 0;
//	__enable_irq();
}

/*******************************************************************************
* 函数名			:	CS5530_PowerUp
* 功能描述		:	CS5530上电及初始化
* 输入			: void
* 返回值			: void
*******************************************************************************/
void CS5530_PowerUp(CS5530Def *pInfo)
{
	u8 num=0;
	u16 retry	=	0;	//重试

  pInfo->Port.CS_PORT->BRR    = pInfo->Port.CS_Pin;       //CS==0
	SysTick_DeleymS(200);				//SysTick延时nmS
	//1)向系统所有ADC发送复位序列
	//1.1、************写入15个SYNC1命令(0XFF)
	for(num=0;num<15;num++)
	{
		CS5530_WriteOneByte(pInfo, CS5530_SYNC1);
		SysTick_DeleymS(10);				//SysTick延时nmS
	}
	SysTick_DeleymS(50);				//SysTick延时nmS
	//1.2、************写入1个SYNC0命令（0XFE）
	CS5530_WriteOneByte(pInfo, CS5530_SYNC0);
	SysTick_DeleymS(50);				//SysTick延时nmS
	
	//2)写配置寄存器 写入CS5530复位命令 RS为1
	CS5530_WriteRegister(pInfo,CS5530_WRITE_CONFIG,CS5530_CONF_SYSTEM_RESET);
	SysTick_DeleymS(50);				//SysTick延时nmS
	CS5530_WriteOneByte(pInfo, CS5530_NULL_BYTE);
	SysTick_DeleymS(50);				//SysTick延时nmS
	CS5530_WriteRegister(pInfo,CS5530_WRITE_CONFIG,CS5530_CONF_NORMAL_MODE);
	SysTick_DeleymS(50);				//SysTick延时nmS
	
	//检测RV是否为1(复位成 功后为1),如果不为1再继续读取配置寄存器		
	do
	{ 
		CS5530_Status = CS5530_ReadRegister(pInfo, CS5530_READ_CONFIG);
		SysTick_DeleymS(50);				//SysTick延时nmS
	}
	while(((CS5530_Status & CS5530_CONF_RESET_STATUS) != 0)&&(retry++<=100));
	
	if(retry>=100)
	{
		return;
	}
	
//	CS5530_Status=0x1FFFFFF;
	
	CS5530_Status=0x1000000;
	
//	CS5530_Status=0x3F000000;
//	
//	CS5530_Status=0x0FFFFFF;
//	
//	CS5530_Status=0x7FFFFFF;
//	
//	CS5530_Status=0x1FFFFFF;
	
//	CS5530_Status=0x1000000;		//1200
	
	CS5530_Status=0x0800000;		//600
	
	CS5530_Status=0x0400000;		//300
	
	CS5530_Status=0x0200000;		//150
	
	CS5530_Status=0x01000000;		//1200
	
	CS5530_WriteRegister(pInfo,CS5530_WRITE_GAIN,CS5530_Status);			//增益寄存器	
		
//	CS5530_Status=0xFFFFFFFF;
	CS5530_Status=CS5530_ReadRegister(pInfo,CS5530_READ_CONFIG);			//配置寄存器
//	CS5530_Status=0xFFFFFFFF;
	CS5530_Status=CS5530_ReadRegister(pInfo,CS5530_READ_OFFSET);			//偏移寄存器
//	CS5530_Status=0xFFFFFFFF;
	CS5530_Status=CS5530_ReadRegister(pInfo,CS5530_READ_GAIN);				//增益寄存器
	
	CS5530_Status=0x00;
	
//	CS5530_Status=CS5530_Status|0x82000;																	//6.25sps
	
	CS5530_Status=CS5530_Status|0x2000;																	//7.5sps
	
//	CS5530_Status=CS5530_Status|0x1800;																	//15sps
	
//	CS5530_Status=CS5530_Status|0x0800;																	//60sps
	
//	CS5530_Status=CS5530_Status|0x4000;																	//3840sps
	
//	CS5530_Status=CS5530_Status|0x6000;																	//240sps

	CS5530_Status=CS5530_Status&(~CS5530_CONF_SHORT_INPUTS);						//正常输入,通道输入不短接
	
//	CS5530_Status=CS5530_Status|CS5530_CONF_SHORT_INPUTS;								//设置为输入短路

	CS5530_WriteRegister(pInfo,CS5530_WRITE_CONFIG,CS5530_Status);		//配置寄存器
	
	CS5530_WriteCommand(pInfo,CS5530_SYSTEM_OFFSET_CAL);							//执行偏移校准
	
	CS5530_WriteCommand(pInfo,CS5530_SYSTEM_GAIN_CAL);								//执行系统增益校准

	CS5530_Status=CS5530_ReadRegister(pInfo,CS5530_READ_GAIN);				//增益寄存器
	
//	CS5530_WriteRegister(pInfo,CS5530_WRITE_GAIN,0x00FFFFFF);						//写增益寄存器
	
//	CS5530_WriteRegister(Pinfo,CS5530_WRITE_GAIN,0x00100000);					//写增益寄存器
	
	CS5530_WriteCommand(pInfo,CS5530_START_CONTINUOUS);									//执行连续转换
	
//	CS5530_WriteCommand(pInfo,CS5530_START_SINGLE);									//执行单次转换
	
	CS5530_Delay(500);
	pInfo->Port.CS_PORT->BSRR    = pInfo->Port.CS_Pin;       //CS==1
}
/*******************************************************************************
* 函数名			:	CS5530_PowerUp
* 功能描述		:	CS5530上电及初始化
* 输入			: void
* 返回值			: void
*******************************************************************************/
void CS5530_PowerDown(CS5530Def *pInfo)
{
	u8 num=0;
	u16 retry	=	0;	//重试
	pInfo->Port.CS_PORT->BRR    = pInfo->Port.CS_Pin;       //CS==0
	SysTick_DeleymS(200);				//SysTick延时nmS
	//1)向系统所有ADC发送复位序列
	//1.1、************写入15个SYNC1命令(0XFF)
	for(num=0;num<15;num++)
	{
		CS5530_WriteOneByte(pInfo, CS5530_SYNC1);
		SysTick_DeleymS(5);				//SysTick延时nmS
	}
	SysTick_DeleymS(50);				//SysTick延时nmS
	//1.2、************写入1个SYNC0命令（0XFE）
	CS5530_WriteOneByte(pInfo, CS5530_SYNC0);
	SysTick_DeleymS(50);				//SysTick延时nmS
	
	//2)写配置寄存器 写入CS5530复位命令 RS为1
	CS5530_WriteRegister(pInfo,CS5530_WRITE_CONFIG,CS5530_CONF_SYSTEM_RESET);
	SysTick_DeleymS(50);				//SysTick延时nmS
	CS5530_WriteOneByte(pInfo, CS5530_NULL_BYTE);
	SysTick_DeleymS(50);				//SysTick延时nmS
	CS5530_WriteRegister(pInfo,CS5530_WRITE_CONFIG,CS5530_CONF_NORMAL_MODE);
	SysTick_DeleymS(50);				//SysTick延时nmS
	
	//检测RV是否为1(复位成 功后为1),如果不为1再继续读取配置寄存器		
	do
	{ 
		CS5530_Status = CS5530_ReadRegister(pInfo, CS5530_READ_CONFIG);
		SysTick_DeleymS(50);				//SysTick延时nmS
	}
	while(((CS5530_Status & CS5530_CONF_RESET_STATUS) != 0)&&(retry++<=100));
	
	if(retry>=100)
	{
		return;
	}
	
	CS5530_WriteRegister(pInfo,CS5530_WRITE_CONFIG,CS5530_CONF_POWER_SAVE_MODE);
	
	CS5530_Delay(500);
	pInfo->Port.CS_PORT->BSRR    = pInfo->Port.CS_Pin;       //CS==1
}
/*******************************************************************************
* 函数名			:	CS5530_PowerUp
* 功能描述		:	CS5530上电及初始化
* 输入			: void
* 返回值			: void
*******************************************************************************/
void CS5530_PowerUpBac(CS5530Def *pInfo)
{
	u8 num=0;
	u16 retry	=	0;	//重试
	pInfo->Port.CS_PORT->BSRR    = pInfo->Port.CS_Pin;       //CS==1
	SysTick_DeleymS(200);				//SysTick延时nmS
	//1)向系统所有ADC发送复位序列
	//1.1、************写入15个SYNC1命令(0XFF)
	for(num=0;num<15;num++)
	{
		CS5530_WriteOneByte(pInfo, CS5530_SYNC1);
		SysTick_DeleymS(5);				//SysTick延时nmS
	}
	SysTick_DeleymS(50);				//SysTick延时nmS
	//1.2、************写入1个SYNC0命令（0XFE）
	CS5530_WriteOneByte(pInfo, CS5530_SYNC0);
	SysTick_DeleymS(50);				//SysTick延时nmS
	
	//2)写配置寄存器 写入CS5530复位命令 RS为1
	CS5530_WriteRegister(pInfo,CS5530_WRITE_CONFIG,CS5530_CONF_SYSTEM_RESET);
	SysTick_DeleymS(50);				//SysTick延时nmS
	CS5530_WriteOneByte(pInfo, CS5530_NULL_BYTE);
	SysTick_DeleymS(50);				//SysTick延时nmS
	CS5530_WriteRegister(pInfo,CS5530_WRITE_CONFIG,CS5530_CONF_NORMAL_MODE);
	SysTick_DeleymS(50);				//SysTick延时nmS
	
	//检测RV是否为1(复位成 功后为1),如果不为1再继续读取配置寄存器		
		do
		{ 
			CS5530_Status = CS5530_ReadRegister(pInfo, CS5530_READ_CONFIG);
			SysTick_DeleymS(50);				//SysTick延时nmS
		}
		while(((CS5530_Status & CS5530_CONF_RESET_STATUS) != 0)&&(retry++<=100));
		
		if(retry>=100)
		{
			return;
		}
	
//	CS5530_Delay(50);		
//	CS5530_WriteRegister(Pinfo,CS5530_WRITE_CONFIG,CS5530_CONF_NORMAL_MODE);
//	CS5530_Delay(50);
	
//	while(CS5530_ReadRegister(Pinfo,CS5530_READ_CONFIG)==0x00000000);
//	while(CS5530_ReadRegister(Pinfo,CS5530_READ_OFFSET)==0x00000000);
//	while(CS5530_ReadRegister(Pinfo,CS5530_READ_GAIN)==0x01000000);
		
//	CS5530_Status=0xFFFFFFFF;
	CS5530_Status=CS5530_ReadRegister(pInfo,CS5530_READ_CONFIG);			//配置寄存器
//	CS5530_Status=0xFFFFFFFF;
	CS5530_Status=CS5530_ReadRegister(pInfo,CS5530_READ_OFFSET);			//偏移寄存器
//	CS5530_Status=0xFFFFFFFF;
	CS5530_Status=CS5530_ReadRegister(pInfo,CS5530_READ_GAIN);				//增益寄存器
		
		
//	CS5530_Status=0xFFFFFFFF;
		
	CS5530_Status=CS5530_Status|CS5530_CONF_SHORT_INPUTS;								//设置为输入短路

	CS5530_Status=CS5530_ReadRegister(pInfo,CS5530_READ_CONFIG);				//增益寄存器

//	CS5530_Status=CS5530_Status|0x82000;																	//6.25sps
	
	CS5530_Status=CS5530_Status|0x2000;																	//7.5sps
	
//	CS5530_Status=CS5530_Status|0x1800;																	//15sps
	
//	CS5530_Status=CS5530_Status|0x0800;																	//60sps
	
//	CS5530_Status=CS5530_Status|0x4000;																	//3840sps
	
//	CS5530_Status=CS5530_Status|0x6000;																	//240sps
	
	CS5530_WriteCommand(pInfo,CS5530_SYSTEM_OFFSET_CAL);								//执行偏移校准
	
	CS5530_WriteCommand(pInfo,CS5530_SYSTEM_GAIN_CAL);									//执行系统增益校准	
	
//	CS5530_Status=CS5530_Status|CS5530_CONF_UNIPOLAR_MODE;							//极性选择单极性模式

	CS5530_Status=CS5530_Status|CS5530_CONF_BIPOLAR_MODE;									//极性选择双极性模式
	
	CS5530_WriteRegister(pInfo,CS5530_WRITE_CONFIG,CS5530_Status);			//配置寄存器
	
	CS5530_Status=CS5530_ReadRegister(pInfo,CS5530_READ_CONFIG);				//配置寄存器
	
//	CS5530_Status=CS5530_Status&(~CS5530_CONF_SHORT_INPUTS);						//正常输入,通道输入不短接

	CS5530_Status=CS5530_Status|CS5530_CONF_SHORT_INPUTS;								//设置为输入短路
	
	CS5530_WriteRegister(pInfo,CS5530_WRITE_CONFIG,CS5530_Status);			//写配置寄存器
	
//	CS5530_WriteRegister(pInfo,CS5530_WRITE_GAIN,0x00FFFFFF);						//写增益寄存器
	
	CS5530_WriteRegister(pInfo,CS5530_WRITE_GAIN,0x01000000);					//写增益寄存器
	
	CS5530_WriteCommand(pInfo,CS5530_START_CONTINUOUS);									//执行连续转换
	
	CS5530_Delay(500);
	pInfo->Port.CS_PORT->BRR    = pInfo->Port.CS_Pin;       //CS==0
}
/*******************************************************************************
*函数名			:	CS5530_ReadData
*功能描述		:	读取AD值，如果返回0xFFFFFFFF,则未读取到24位AD值
*输入				: 
*返回值			:	无
*******************************************************************************/
u32	CS5530_ReadData(CS5530Def *pInfo)
{
	u32 ADC_Value=0xFFFFFFFF;
	
	pInfo->Port.CS_PORT->BRR    = pInfo->Port.CS_Pin;       //CS==0
	SysTick_DeleyuS(100);				//SysTick延时nuS
	if(CS5530_SDO_STATE(pInfo) == 0)
	{			
		ADC_Value=CS5530_GetADData(pInfo)>>8;		//获取24位原码值---读出4个字节，低8位为空值
	}
	pInfo->Port.CS_PORT->BSRR    = pInfo->Port.CS_Pin;       //CS==1
	return ADC_Value;
}
/**********************************************************
函数名:中值滤波输出
描述:提取n次采集的数据,去掉高m个,去掉低m个,然后留下中间的(n-2*m)个数据,
		看数据差值是否满足要求,如果满足要求,求平均值输出
输入:
	pInfo:那一路数据;
	pDataBuf:临时数据缓存,需要调用函数提供一个与pInfo->pDataBuf所指向的数据缓存区
				尺寸一样大小的临时数据缓存,用来保存数据;
	dataMaxDiff:允许最大的差值;
Length:输入的数组长度
输出:中间(n-2*m)个数据的平均值,若输出为0xFFFFFFFF,表明该数据无效,若输出为0xFF000000,表明该数据溢出
*********************************************************/
unsigned long CS5530_GetWeightUseMedinaFilter(CS5530Def *pInfo)
{
//	unsigned long 	weighMax=0;
//	unsigned long 	weighMid=0;
//	unsigned long 	weighMin=0;
	unsigned long 	weighAve=0;		//平均值
	unsigned long 	weighVar=0;		//方差
	unsigned short 	Length	=	0;
	unsigned long		*Buffer		=	NULL;			//数据缓存	

	Buffer	=	&(pInfo->Data.Buffer[0]);
	Length	=	pInfo->Data.Num;
	
	//查找最大值和最小值
//	weighMid	=	GetMinLong(Buffer,Length);		//获取unsigned long型最小值
//	weighMax	=	GetMaxLong(Buffer,Length);		//获取unsigned long型最大值	
	//求平均值
	weighAve	=	GetAveLong(Buffer,Length);		//获取unsigned long型平均值	
	//方差(标准差)计算
	weighVar	=	GetVarLong(Buffer,Length);		//获取unsigned long方差
	weighVar	=	weighVar/Length;
	
	if(weighVar<WeighVarMax)		//方差太大，离散性差，数据无效
	{
		return weighAve;		
	}
	else
	{
		return 0xFFFFFFFF;
	}
//	return weighVar;
}
/*******************************************************************************
* 函数名			:	function
* 功能描述		:	获取稳定的AD值 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
unsigned long CS5530_GetWeigh(CS5530Def *pInfo)
{
	if(pInfo->Data.Time++>=5)	//5Hz 0.2S
	{
		unsigned long		ADC	=	0;
		unsigned short	Num			=	0;			//计数器		
		unsigned short	*Quantity	=	NULL;			//数量	
		unsigned long		*WeighFilt	=	NULL;		//滤波后AD值	
		unsigned long		*Origin		=	NULL;			//原点值
		unsigned long		*Buffer		=	NULL;			//数据缓存
		
		Num	=	pInfo->Data.Num;
		WeighFilt	=	&(pInfo->Data.WeighFilt);
		Quantity	=	&(pInfo->Data.Quantity);		
		Origin	=	&(pInfo->Data.Origin);
		Buffer	=	&(pInfo->Data.Buffer[0]);
		
		pInfo->Data.Time	=	0;
		
		ADC	=	CS5530_ReadData(pInfo);	//读取AD值，如果返回0xFFFFFFFF,则未读取到24位AD值
		
		pInfo->Data.WeighLive	=	ADC;
		
		if(ADC	!=	0xFFFFFFFF)
		{
			unsigned long	ADC_CMP	=	0;			
			Buffer[Num]	=	ADC;			
			if(Num>0)		//判断相邻AD值之前的偏差
			{
				if(Buffer[Num]>Buffer[Num-1])
				{
					ADC_CMP	=	Buffer[Num]-Buffer[Num-1];
				}
				else
				{
					ADC_CMP	=	Buffer[Num-1]-Buffer[Num];
				}
				if(ADC_CMP>WeighCmpMax)	//相邻数据差太大，取数无效
				{
					*WeighFilt	=	0xFFFFFFFF;
					pInfo->Data.Num	=	0;
					return 0;						//退出此函数
				}				
			}
			pInfo->Data.Num++;
			if(Num>=DataNum-1)		//缓存已满
			{
				*WeighFilt	=	CS5530_GetWeightUseMedinaFilter(pInfo);
				pInfo->Data.Num	=	0;
				return *WeighFilt;
			}
		}
		else
		{
//			*WeighFilt	=	0xFFFFFFFF;
			return 0xFFFFFFFF;
		}
	}	
	return 0xFFFFFFFF;
}
/*******************************************************************************
* 函数名			:	function
* 功能描述		:	标定/获取单重
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
unsigned long CS5530_GetCalib(CS5530Def *pInfo)
{
	if(pInfo->Flag.GetCali)	//获取原点标记
	{
		if((pInfo->Data.WeighFilt!= 0xFFFFFFFF)&&(pInfo->Data.Origin!= 0))
		{
			unsigned short	Quq;
			unsigned long AD1,AD2;
			
			Quq	=	pInfo->Data.Quantity;		//数量
			AD1	=	pInfo->Data.Origin;			//原点值
			AD2	=	pInfo->Data.WeighFilt;	//滤波后AD值	
			if((Quq>0)&&(AD2>AD1))
			{
				pInfo->Flag.GetCali		=	0;
				pInfo->Data.WeighPie	=	(AD2-AD1)/Quq;
				return pInfo->Data.WeighPie;
			}
		}
	}
	return 0xFFFFFFFF;
}
/*******************************************************************************
* 函数名			:	function
* 功能描述		:	获取原点值 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
unsigned long CS5530_GetOrigin(CS5530Def *pInfo)
{
	if(pInfo->Flag.GetOri)	//获取原点标记
	{
		if((pInfo->Data.WeighFilt!= 0xFFFFFFFF)&&(pInfo->Data.WeighFilt!= 0))
		{
			pInfo->Flag.GetOri	=	0;
			pInfo->Data.Origin	=	pInfo->Data.WeighFilt;
			return pInfo->Data.Origin;
		}
	}
	return 0xFFFFFFFF;
}
/*******************************************************************************
* 函数名			:	CS5530_GetQuant
* 功能描述		:	获取数量 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
unsigned long CS5530_GetQuant(CS5530Def *pInfo)
{
	if(pInfo->Flag.GetQua)	//获取原点标记
	{
		if((pInfo->Data.WeighFilt!= 0xFFFFFFFF)&&(pInfo->Data.Origin!= 0))
		{
			unsigned short	Quq;
			unsigned long AD1,AD2,AD3;
			
			Quq	=	pInfo->Data.Quantity;
			AD1	=	pInfo->Data.Origin;
			AD2	=	pInfo->Data.WeighFilt;
			AD3	=	pInfo->Data.WeighPie;
			if((Quq>0)&&(AD1>0)&&((AD2+AD3/5)>=AD1)&&(AD3>0))
			{
				pInfo->Flag.GetQua		=	0;
				pInfo->Data.Quantity	=	(AD2-AD1+(AD3)/5)/AD3;
				return pInfo->Data.Quantity;
			}
		}
	}
	return 0xFFFFFFFF;
}
/*******************************************************************************
* 函数名			:	CS5530_Clear
* 功能描述		:	清除：清除所有标志及存数
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
void CS5530_Clear(CS5530Def *pInfo)
{
//	memset(&(pInfo->Data),0xFF,(sizeof(pInfo->Data))/sizeof(char));
//	memset(&(pInfo->Flag),0xFF,(sizeof(pInfo->Flag))/sizeof(char));
	
	memset(&(pInfo->Data),0x00,(sizeof(pInfo->Data))/sizeof(char));
	memset(&(pInfo->Flag),0x00,(sizeof(pInfo->Flag))/sizeof(char));
}
/*******************************************************************************
* 函数名			:	function
* 功能描述		:	获取原点值 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
void CS5530_Process(CS5530Def *pInfo)
{
	CS5530_GetWeigh(pInfo);	
	CS5530_GetOrigin(pInfo);
	CS5530_GetCalib(pInfo);
	CS5530_GetQuant(pInfo);
//	pInfo->Flag.GetQua		=	1;
}



/************************************************************************************/
