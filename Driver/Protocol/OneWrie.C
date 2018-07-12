#include "OneWrie.H"	


#include "STM32_GPIO.H"
#include "STM32_SYSTICK.H"

/*******************************************************************************
* 函数名			:	function
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
void OneWrie_Configuration(OneWrieDef *OneWrie)		//配置
{
	//=====================================Data脚
	GPIO_Configuration_OPP50	(OneWrie->Data_Port,OneWrie->Data_Pin);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605
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
void OneWrie_Server(OneWrieDef *OneWrie)
{
	
}
/*******************************************************************************
* 函数名			:	OneWrie_SetOut
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
unsigned char OneWrie_SetOut(OneWrieDef *OneWrie)
{
	GPIO_Configuration_OPP50	(OneWrie->Data_Port,OneWrie->Data_Pin);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605
	return 0;
}
/*******************************************************************************
* 函数名			:	OneWrie_SetOut
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
unsigned char OneWrie_SetIn(OneWrieDef *OneWrie)
{
	GPIO_Configuration_IPU(OneWrie->Data_Port,OneWrie->Data_Pin);		//输入模式
	return 0;
}
/*******************************************************************************
* 函数名			:	OneWrie_SetHigh
* 功能描述		:	拉高总线
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
unsigned char OneWrie_SetHigh(OneWrieDef *OneWrie)
{
	GPIO_SetBits(OneWrie->Data_Port,OneWrie->Data_Pin);							//拉高DQ
	return 0;
}
/*******************************************************************************
* 函数名			:	OneWrie_SetLow
* 功能描述		:	拉低总线
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
unsigned char OneWrie_SetLow(OneWrieDef *OneWrie)
{
	GPIO_ResetBits(OneWrie->Data_Port,OneWrie->Data_Pin);						//拉低DQ
	return 0;
}
/*******************************************************************************
* 函数名			:	OneWrie_Read
* 功能描述		:	读总线
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
unsigned char OneWrie_Read(OneWrieDef *OneWrie)
{
//	return ((OneWrie->Data_Port->IDR)	& (OneWrie->Data_Pin));
	return GPIO_ReadInputDataBit(OneWrie->Data_Port,OneWrie->Data_Pin);
}
/*******************************************************************************
* 函数名			:	OneWrie_ReadAck
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
unsigned char OneWrie_ReadAck(OneWrieDef *OneWrie)
{
	return ((OneWrie->Data_Port->IDR)	& (OneWrie->Data_Pin));
}
/*******************************************************************************
* 函数名			:	OneWrie_ReadBit
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
unsigned char OneWrie_ReadBit(OneWrieDef *OneWrie)
{
	unsigned char data;
	
	OneWrie_SetOut(OneWrie);			//设为输出模式
	OneWrie_SetLow(OneWrie); 			//拉低总线
	SysTick_DeleyuS(5);						//至少1us时间
	OneWrie_SetIn(OneWrie);;			//设置为输入模式
	SysTick_DeleyuS(12);					//等待从机响应
	if(OneWrie_Read(OneWrie))			//读取总线状态
		data = 1;
	else
		data = 0;	 
	SysTick_DeleyuS(50);	
	return data;
}
/*******************************************************************************
* 函数名			:	OneWrie_WriteBit
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
unsigned char OneWrie_WriteBit(OneWrieDef *OneWrie,unsigned char bit)
{
	//写间隙有两种，包括写0的时间隙和写1的时间隙。
	//当数据线拉低后，在15 ~ 60 us的时间窗口内对数据线进行采样。
	//如果数据线为低电平，就是写0，如果数据线为高电平，就是写1。
	//主机要产生一个写1时间隙，就必须把数据线拉低，在写时间隙开始后的15 us内允许数据线拉高。
	//主机要产生一个写0时间隙，就必须把数据线拉低并保持60 us。
	OneWrie_SetLow(OneWrie); 	//拉低总线
	SysTick_DeleyuS(2);			//15 ~ 60 us的时间窗口内对数据线进行采样
	// =============Write 1
	if (bit&0x01)		
	{
		OneWrie_SetHigh(OneWrie);		//拉高总线
		SysTick_DeleyuS(60);				//等待从机采样完成
	}
	// =============Write 0
	else						
	{
		SysTick_DeleyuS(60);				//保持60us，等待从机采样
		OneWrie_SetHigh(OneWrie);		//拉高总线
		SysTick_DeleyuS(2);
	}
	return 0;
}
/*******************************************************************************
* 函数名			:	OneWrie_Start
* 功能描述		:	初始化 
							初始化过程 = 复位脉冲 + 从机应答脉冲。
							主机通过拉低单总线480 ~ 960 us产生复位脉冲，然后释放总线，进入接收模式。
							主机释放总线时，会产生低电平跳变为高电平的上升沿，单总线器件检测到上升沿之后，延时15 ~ 60 us，单总线器件拉低总线60 ~ 240 us来产生应答脉冲。
							主机接收到从机的应答脉冲说明单总线器件就绪，初始化过程完成。
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
unsigned char OneWrie_Start(OneWrieDef *OneWrie)
{
	uint16_t retry=0;
	GPIO_Configuration_OPP50(OneWrie->Data_Port,OneWrie->Data_Pin);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605
	GPIO_ResetBits(OneWrie->Data_Port,OneWrie->Data_Pin);								//拉低DQ
	SysTick_DeleyuS(750);		//拉低750us（大于480uS)
	//----------------------检测响应：总时间需要大于480us
	//1释放总线
	//2等待15us~60uS
	//3从机拉低总线60uS~240uS
	//4从机释放/拉高总线
	GPIO_Configuration_IPU(OneWrie->Data_Port,OneWrie->Data_Pin);		//输入模式
	SysTick_DeleyuS(15);		//15US---检测响应需要在15uS后
	while(OneWrie_ReadAck(OneWrie)	&& (retry < 500))			//响应检测时间不超过240uS
	{
		retry++;
		SysTick_DeleyuS(1);
	}
	if(retry >= 500)	//超时
		return 1;
	else
		retry=0;
	//增加延时--为了满足总的检测时间480uS
	SysTick_DeleyuS(480);		//总的检测响应时间需要大于480uS
	return 0;
}
/*******************************************************************************
* 函数名			:	function
* 功能描述		:	写一个字节到Dallas---从低位开始写入
* 输入			: dat：要写入的字节,
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
unsigned char OneWrie_WriteByte(OneWrieDef *OneWrie,unsigned char dat)
{             
	unsigned char j;
	unsigned char bit;
	
	OneWrie_SetOut(OneWrie);							//SET PG11 OUTPUT;
	
	for (j=1; j<=8; j++)
	{
		bit = dat&0x01;
		dat = dat>>1;
		OneWrie_WriteBit(OneWrie,bit);		//1-wire 一位（1bit）写操作-写0&写1
	}
	return 0;
}
/*******************************************************************************
* 函数名			:	OneWrie_ReadByte
* 功能描述		:	从Dallas读一个字节---从低位开始读取
* 输入			:
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
unsigned char OneWrie_ReadByte(OneWrieDef *OneWrie)
{             
	unsigned char j;
	unsigned char bit;
	unsigned char dat	=	0;
	
	for (j=1; j<=8; j++)
	{
		dat>>=1;
		if(OneWrie_ReadBit(OneWrie))
		{
			dat|=0x80;
		}
	}
	return dat;
}
