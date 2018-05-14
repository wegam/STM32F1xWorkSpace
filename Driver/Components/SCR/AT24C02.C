#include "AT24C02.H"	


	
#include "STM32_GPIO.H"
#include "STM32_SYSTICK.H"


#define	Write_24C02Addr	(unsigned char)0xA0
#define	Read_24C02Addr	(unsigned char)0xA1


//AT24C02 2048位，256字节，8字节/页,共32页
/*******************************************************************************
* 函数名			:	function
* 功能描述		:	在at24c02中的指定地址写入数据
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
void AT24C02_Write(sI2CDef *sI2C,unsigned char Addr,unsigned char Data)
{
	I2C_Start(sI2C);
	
	I2C_SendByte(sI2C,Write_24C02Addr);	//向I2C总线设备发送8bits的数据 ,首先传输的是数据的最高位（MSB）
	
	I2C_WaitAck(sI2C);
	
	I2C_SendByte(sI2C,Addr);	//向I2C总线设备发送8bits的数据 ,首先传输的是数据的最高位（MSB）
	
	I2C_WaitAck(sI2C);
	
	I2C_SendByte(sI2C,Data);	//向I2C总线设备发送8bits的数据 ,首先传输的是数据的最高位（MSB）
	
	I2C_WaitAck(sI2C);
	
	I2C_Stop(sI2C);
}
/*******************************************************************************
* 函数名			:	function
* 功能描述		:	在at24c02的指定地址中读出写入的数据
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
unsigned char AT24C02_Read(sI2CDef *sI2C,unsigned char Addr)
{
	unsigned char Data	=	0;
	
	I2C_Start(sI2C);
	
	I2C_SendByte(sI2C,Write_24C02Addr);	//向I2C总线设备发送8bits的数据 ,首先传输的是数据的最高位（MSB）
	
	I2C_WaitAck(sI2C);
	
	I2C_SendByte(sI2C,Addr);						//发送待读取地址
	
	I2C_WaitAck(sI2C);
	
	I2C_Start(sI2C);
	
	I2C_SendByte(sI2C,Read_24C02Addr);	//发送待读取地址
	
	I2C_WaitAck(sI2C);
	
	
	
	I2C_SDASetIn(sI2C);
	
	Data	=	I2C_ReadByte(sI2C);					//从I2C总线读取8个bits的数据  ,首先读出的是数据的最高位（MSB）
	
	I2C_NAck(sI2C);								//CPU产生一个NACK信号(NACK即无应答信号)
	
	I2C_Stop(sI2C);
	
	return Data;
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
void AT24C02_WritePage(sI2CDef *sI2C,unsigned char StartAddr,unsigned char *Buffer)
{
	unsigned char i	=	0;
	
	I2C_Start(sI2C);
	
	I2C_SendByte(sI2C,Write_24C02Addr);	//向I2C总线设备发送8bits的数据 ,首先传输的是数据的最高位（MSB）
	
	I2C_WaitAck(sI2C);
	
	I2C_SendByte(sI2C,StartAddr);	//向I2C总线设备发送8bits的数据 ,首先传输的是数据的最高位（MSB）
	
	I2C_WaitAck(sI2C);
	
	for(i=0;i<8;i++)
	{
		I2C_SendByte(sI2C,Buffer[i]);	//向I2C总线设备发送8bits的数据 ,首先传输的是数据的最高位（MSB）
	
		I2C_WaitAck(sI2C);
	}
	
	I2C_Stop(sI2C);
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
unsigned char AT24C02_ReadBuffer(sI2CDef *sI2C,unsigned char Addr,unsigned char *Buffer,unsigned char Length)
{
	unsigned char i	=	0;
	
	unsigned char Data	=	0;
	
	I2C_Start(sI2C);
	
	I2C_SendByte(sI2C,Write_24C02Addr);	//向I2C总线设备发送8bits的数据 ,首先传输的是数据的最高位（MSB）
	
	I2C_WaitAck(sI2C);
	
	I2C_SendByte(sI2C,Addr);						//发送待读取地址
	
	I2C_WaitAck(sI2C);
	
	I2C_Start(sI2C);
	
	I2C_SendByte(sI2C,Read_24C02Addr);	//发送待读取地址
	
	I2C_WaitAck(sI2C);	
	
	
	
	for(i=0;i<8;i++)
	{
		I2C_SDASetIn(sI2C);
		
		Buffer[i]	=	I2C_ReadByte(sI2C);					//从I2C总线读取8个bits的数据  ,首先读出的是数据的最高位（MSB）
	
		I2C_SDASetOut(sI2C);
		
		I2C_Ack(sI2C);											//CPU产生一个ACK信号
	}
	I2C_SDASetOut(sI2C);
	
	I2C_NAck(sI2C);											//CPU产生一个NACK信号(NACK即无应答信号)
	
	I2C_Stop(sI2C);

}




