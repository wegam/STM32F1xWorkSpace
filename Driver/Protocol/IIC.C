#include	"IIC.H"



#include	"stdio.h"


#include "STM32_SYSTICK.H"

#define IICTime	1

I2CHWdef* softiic	=	NULL;
/*******************************************************************************
* 函数名			:	function
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
void IIC_Initialize(I2CHWdef* pInfo)
{
	softiic	=	pInfo;
	softiic->Start=IIC_Start;
	softiic->Stop=IIC_Stop;
	softiic->Ack=IIC_Ack;
	softiic->NAck=IIC_NAck;
	softiic->WaitAck=IIC_WaitAck;
	
	softiic->WriteOneByte=IIC_WriteOneByte;
	softiic->WriteBuffer=IIC_WriteBuffer;
	softiic->ReadOneByte=IIC_ReadOneByte;
	softiic->ReadBuffer=IIC_ReadBuffer;
}
/*******************************************************************************
*	函数名			:IIC_Start
*	功能描述		:IIC启动,在SCL线是高电平时SDA线从高电平向低电平切换这个情况表示起始条件
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
void IIC_Start(void)
{
	softiic->SDAWriteEn();	

	softiic->SDAHigh();
	IIC_Delayus(IICTime);
	
	softiic->SCLHigh();
	IIC_Delayus(IICTime);	
	
	softiic->SDALow();	
	IIC_Delayus(IICTime);
}
/*******************************************************************************
*	函数名			:	IIC_Stop
*	功能描述		:	IIC停止,当SCL是高电平时SDA线由低电平向高电平切换表示停止条件
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
void IIC_Stop(void)
{
	softiic->SDAWriteEn();
	
	softiic->SDALow();	
	IIC_Delayus(IICTime);
	
	softiic->SCLHigh();
	IIC_Delayus(IICTime);
	
	softiic->SDAHigh();
	IIC_Delayus(IICTime);
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
void IIC_Ack(void)
{
	softiic->SDAWriteEn();
	
	softiic->SCLLow();
	IIC_Delayus(IICTime);
	softiic->SDALow();
	IIC_Delayus(IICTime);
	softiic->SCLHigh();
	IIC_Delayus(IICTime);
	softiic->SCLLow();
	IIC_Delayus(IICTime);
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
void IIC_NAck(void)
{
	softiic->SDAWriteEn();
	
	softiic->SCLLow();
	IIC_Delayus(IICTime);
	softiic->SDAHigh();
	IIC_Delayus(IICTime);
	softiic->SCLHigh();
	IIC_Delayus(IICTime);
	softiic->SCLLow();
	IIC_Delayus(IICTime);
}
/*******************************************************************************
* 函数名			:	IIC_WaitAck
* 功能描述		:	等待应答 
* 输入			: void
* 返回值			: 0-ACK，1-NACK
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
unsigned char IIC_WaitAck(void)
{
	unsigned	char ack=0;
	
	softiic->SDAReadEn();
	
	softiic->SCLLow();
	IIC_Delayus(IICTime);
	
	softiic->SCLHigh();
	IIC_Delayus(IICTime);
	
	ack	=	softiic->SDAStd();
	
	softiic->SCLLow();
	IIC_Delayus(IICTime);
	
	return	ack;
}
/*******************************************************************************
* 函数名			:	IIC_WriteOneByte
* 功能描述		:	先传输高位
							在SCL呈现高电平期间，SDA上的电平必须保持稳定，低电平为数据0，高电平为数据1。
							只有在SCL为低电平期间，才允许SDA上的电平改变状态。逻辑0的电平为低电压，
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
unsigned char IIC_WriteOneByte(unsigned	char data)
{
	unsigned char i	=	0;
	softiic->SDAWriteEn();
	
	softiic->SCLLow();
	IIC_Delayus(IICTime);
	
	//-----------------拉低时钟开始数据传输
	for(i=0;i<8;i++)
	{		
		if(data&0x80)
		{
			softiic->SDAHigh();
		}
		else
		{
			softiic->SDALow();
		}
		IIC_Delayus(IICTime);
		//----------------产生一个时钟信号
		softiic->SCLHigh();
		IIC_Delayus(IICTime);	
		softiic->SCLLow();
		IIC_Delayus(IICTime);
		data<<=1;
	}	
	return	0;
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
unsigned short IIC_WriteBuffer(unsigned char* pbuffer,unsigned	short length)
{
	unsigned char i	=	0;
	unsigned char data	=	0;
	unsigned short len	=	0;

	softiic->SDAWriteEn();
	//-----------------拉低时钟开始数据传输
	softiic->SCLLow();
	IIC_Delayus(IICTime);
	
	for(len=0;len<length;len++)
	{		
		data	=	pbuffer[len];
		for(i=0;i<8;i++)
		{
			if(data&0x80)
			{
				softiic->SDAHigh();
			}
			else
			{
				softiic->SDALow();
			}
			IIC_Delayus(IICTime);
			//----------------产生一个时钟信号
			softiic->SCLHigh();
			IIC_Delayus(IICTime);
			softiic->SCLLow();
			IIC_Delayus(IICTime);
			data<<=1;
		}
	}	
	return	0;
}
/*******************************************************************************
* 函数名			:	IIC_ReadOneByte
* 功能描述		:	SCL上升沿从机输出数据
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
unsigned char IIC_ReadOneByte(void)
{
	unsigned char i	=	0;
	unsigned char receive	=	0;
	
	
	softiic->SDAReadEn();
	softiic->SCLLow();
	IIC_Delayus(IICTime);
	
	for(i=0;i<8;i++)
	{
		if(softiic->SDAStd())	//高电平
			receive|=0x01;
		else
			receive&=0xFE;
		receive<<=1;
		
		//----------------产生一个时钟信号
		softiic->SCLHigh();
		IIC_Delayus(IICTime);
		softiic->SCLLow();
		IIC_Delayus(IICTime);
	}
	return	receive;
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
unsigned short IIC_ReadBuffer(unsigned	char* pbuffer,unsigned short readlength)
{
	unsigned char i	=	0;
	unsigned char receive	=	0;
	unsigned short len	=	0;
	
	softiic->SDAReadEn();
	softiic->SCLLow();
	IIC_Delayus(IICTime);
	
	for(len=0;len<readlength;len++)
	{
		for(i=0;i<8;i++)
		{
			if(softiic->SDAStd)	//高电平
				receive|=0x01;
			else
				receive&=0xFE;			
			receive<<=1;
			//----------------产生一个时钟信号
			softiic->SCLHigh();
			IIC_Delayus(IICTime);
			softiic->SCLLow();
			IIC_Delayus(IICTime);
		}
		pbuffer[len]=receive;
	}
	return	len;
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
void IIC_Delayus(unsigned	short Time)
{
	SysTick_DeleyuS(Time);				//SysTick延时nmS
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
void IIC_Delayms(unsigned	short Time)
{
	SysTick_DeleymS(Time);				//SysTick延时nmS
}

