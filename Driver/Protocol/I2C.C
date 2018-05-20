#include "I2C.H"	


#include "STM32_GPIO.H"
#include "STM32_SYSTICK.H"


//void I2CDelay(unsigned short Time);
//void I2C_SCLHigh(sI2CDef *sI2C);
//void I2C_SCLLow(sI2CDef *sI2C);
//void I2C_SDAHigh(sI2CDef *sI2C);
//void I2C_SDALow(sI2CDef *sI2C);
//void I2C_SDASetOut(sI2CDef *sI2C);
//void I2C_SDASetIn(sI2CDef *sI2C);

/*******************************************************************************
* 函数名			:	function
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
void I2C_Configuration(sI2CDef *sI2C)		//启用锁--配置
{
	//=====================================SDA脚
	GPIO_Configuration_OPP50	(sI2C->SDA_Port,sI2C->SDA_Pin);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605
	//=====================================SCL脚
	GPIO_Configuration_OPP50	(sI2C->SCL_Port,sI2C->SCL_Pin);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605
	//=====================================SDA,SCL拉低
	GPIO_SetBits(sI2C->SCL_Port,sI2C->SCL_Pin);
	GPIO_SetBits(sI2C->SDA_Port,sI2C->SDA_Pin);	
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
void I2C_Server(sI2CDef *sI2C)
{
	
}

/*******************************************************************************
* 函数名			:	function
* 功能描述		:	
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
void I2C_Delay(void)
{
	unsigned short Time	=	1;
	while(Time--);
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
void I2C_SCLHigh(sI2CDef *sI2C)
{
	GPIO_SetBits(sI2C->SCL_Port,sI2C->SCL_Pin);
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
void I2C_SCLLow(sI2CDef *sI2C)
{
	GPIO_ResetBits(sI2C->SCL_Port,sI2C->SCL_Pin);
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
void I2C_SDAHigh(sI2CDef *sI2C)
{
	GPIO_SetBits(sI2C->SDA_Port,sI2C->SDA_Pin);
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
void I2C_SDALow(sI2CDef *sI2C)
{
	GPIO_ResetBits(sI2C->SDA_Port,sI2C->SDA_Pin);
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
void I2C_SDASetOut(sI2CDef *sI2C)
{
	GPIO_Configuration_OPP50	(sI2C->SDA_Port,sI2C->SDA_Pin);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605
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
void I2C_SDASetIn(sI2CDef *sI2C)
{
	GPIO_Configuration_IPU	(sI2C->SDA_Port,sI2C->SDA_Pin);			//将GPIO相应管脚配置为上拉输入模式----V20170605
}
/*******************************************************************************
* 函数名			:	function
* 功能描述		:	CPU产生一个时钟，并且读取器件的ACK应答信号 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
unsigned char I2C_WaitAck(sI2CDef *sI2C)
{
	I2CACKDef ack;
	unsigned short i	=	0;
	
	I2C_SDAHigh(sI2C);
	I2C_SDASetIn(sI2C);	//设置为上拉输入模式
	

	I2C_SCLHigh(sI2C);
	I2C_Delay();
	while((GPIO_ReadInputDataBit(sI2C->SDA_Port,sI2C->SDA_Pin))&&i++<=20020)
	if(i>=20000)		//应答超时
	{
		I2C_Stop(sI2C);
		ack	= I2C_NACK;
	}
	else
	{
		ack	= I2C_ACK;
	}
	I2C_SCLLow(sI2C);
	
	I2C_SDASetOut(sI2C);
	
	return ack;
}
/*******************************************************************************
* 函数名			:	function
* 功能描述		:	CPU产生一个ACK信号 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
void I2C_Ack(sI2CDef *sI2C)
{
	I2C_SDASetOut(sI2C);
	
	I2C_SDALow(sI2C);
	I2C_Delay();
	
	I2C_SCLHigh(sI2C);
	I2C_Delay();
	
	I2C_SCLLow(sI2C);
	I2C_Delay();
	I2C_SDAHigh(sI2C);
	I2C_Delay();
}
/*******************************************************************************
* 函数名			:	function
* 功能描述		:	CPU产生一个NACK信号(NACK即无应答信号) 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
void I2C_NAck(sI2CDef *sI2C)
{
	I2C_SDASetOut(sI2C);
	
	I2C_SDAHigh(sI2C);
	I2C_Delay();
	
	I2C_SCLHigh(sI2C);
	I2C_Delay();
	
	I2C_SCLLow(sI2C);
	I2C_Delay();
	
	I2C_SDALow(sI2C);
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
unsigned char I2C_ReadBit(sI2CDef *sI2C)
{
	if(GPIO_ReadInputDataBit(sI2C->SDA_Port,sI2C->SDA_Pin))
		return 1;
	else
		return 0;
}
/*******************************************************************************
* 函数名			:	function
* 功能描述		:	开始信号：SCL为高电平时，SDA由高电平向低电平跳变，开始传送数据。
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
void I2C_Start(sI2CDef *sI2C)
{
	//=====================================SDA,SCL设置为高
	I2C_SDAHigh(sI2C);
	I2C_SCLHigh(sI2C);
	I2C_Delay();
	//=====================================SDA向低电平跳变
	I2C_SDALow(sI2C);
	I2C_Delay();
	I2C_SCLLow(sI2C);
	I2C_Delay();
}
/*******************************************************************************
* 函数名			:	function
* 功能描述		:	结束信号：SCL为高电平时，SDA由低电平向高电平跳变，结束传送数据。
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
void I2C_Stop(sI2CDef *sI2C)
{
	//=====================================SDA设置为低,SCL设置为高
	I2C_SDALow(sI2C);
	I2C_SCLHigh(sI2C);
	I2C_Delay();
	//=====================================SDA由低电平向高电平跳变
	I2C_SDAHigh(sI2C);
	I2C_Delay();
//	I2C_SCLLow(sI2C);
//	I2C_Delay();
}
/*******************************************************************************
* 函数名			:	function
* 功能描述		:	向I2C总线设备发送8bits的数据 ,首先传输的是数据的最高位（MSB） 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
void I2C_SendByte(sI2CDef *sI2C,unsigned char ucByte)
{
	unsigned char i	=	0;
	for(i=0;i<8;i++)
	{
//		I2C_SCLLow(sI2C);
		if(ucByte & 0x80)
		{
			I2C_SDAHigh(sI2C);
		}
		else
		{
			I2C_SDALow(sI2C);
		}
		I2C_Delay();
		I2C_SCLHigh(sI2C);
		I2C_Delay();
		I2C_SCLLow(sI2C);
		
//		if(i	==	7)	// 8位数据发送完毕后，主机释放SDA，以检测从机应答
//		{
//			I2C_SDASetIn(sI2C);	//设置为上拉输入模式
//			return;			//退出不往下执行
//		}
		ucByte<<=1;		//左移1个bit
		I2C_Delay();
	}
}
/*******************************************************************************
* 函数名			:	function
* 功能描述		:	从I2C总线读取8个bits的数据  ,首先读出的是数据的最高位（MSB） 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
unsigned char I2C_ReadByte(sI2CDef *sI2C)
{
	unsigned char ucByte;
	unsigned char i	=	0;
	
	I2C_Delay();
	for(i=0;i<8;i++)
	{
		ucByte<<=1;
		I2C_SCLHigh(sI2C);
		I2C_Delay();
		if(I2C_ReadBit(sI2C))
		{
			ucByte+=1;
		}
		I2C_SCLLow(sI2C);
		I2C_Delay();
	}
	return ucByte;
}

