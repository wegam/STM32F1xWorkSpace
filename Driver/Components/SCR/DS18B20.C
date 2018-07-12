#include "DS18B20.H"	
#include "STM32_SYSTICK.H"

/*******************************************************************************
* 函数名			:	function
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
*******************************************************************************/
void DS18B20_Configuration(OneWrieDef *OneWrie)
{
	OneWrie_Configuration(OneWrie);		//配置
}
/*******************************************************************************
* 函数名			:	function
* 功能描述		:	复位Dallas--拉低总线(低速480uS,高速48uS),然后释放总线，等待从机拉高总线
* 输入			: void
* 返回值			: 返回0:复位不成功/无IC
							返回1:复位成功
*******************************************************************************/
unsigned short DS18B20_Read(OneWrieDef *OneWrie)		//复位Dallas,返回结果
{
	unsigned short	tempr=0;
	unsigned short	tempr1=0;

	OneWrie_Start(OneWrie);
	OneWrie_WriteByte(OneWrie,0xCC); //跳过 ROM 操作
	OneWrie_WriteByte(OneWrie,0x44); //写0X44启动温度转换
	
	SysTick_DeleymS(500);				//SysTick延时nmS
	
	OneWrie_Start(OneWrie);
	OneWrie_WriteByte(OneWrie,0xCC); //跳过 ROM 操作
	OneWrie_WriteByte(OneWrie,0xBE); //写0X44读RAM数据
	tempr		=	OneWrie_ReadByte(OneWrie);
	tempr1	=	OneWrie_ReadByte(OneWrie);
	tempr		=	tempr|(tempr1<<8);
	SysTick_DeleymS(500);				//SysTick延时nmS
//	OneWrie_ReadByte(OneWrie);
//	OneWrie_ReadByte(OneWrie);
//	OneWrie_ReadByte(OneWrie);
//	OneWrie_ReadByte(OneWrie);
//	OneWrie_ReadByte(OneWrie);
//	OneWrie_ReadByte(OneWrie);
//	OneWrie_ReadByte(OneWrie);
//	OneWrie_ReadByte(OneWrie);
//	OneWrie_ReadByte(OneWrie);
//	OneWrie_ReadByte(OneWrie);
//	OneWrie_ReadByte(OneWrie);
//	OneWrie_ReadByte(OneWrie);
//	OneWrie_ReadByte(OneWrie);
//	OneWrie_ReadByte(OneWrie);
////	OneWrie_SetIn(OneWrie);
//	SysTick_DeleymS(2000);				//SysTick延时nmS
////	OneWrie_ReadByte(OneWrie);

//	OneWrie_Start(OneWrie);
//	OneWrie_WriteByte(OneWrie,0x33); //跳过 ROM 编码
//	OneWrie_ReadByte(OneWrie);
//	OneWrie_ReadByte(OneWrie);
//	OneWrie_ReadByte(OneWrie);
//	OneWrie_ReadByte(OneWrie);
//	OneWrie_ReadByte(OneWrie);
//	OneWrie_ReadByte(OneWrie);
//	OneWrie_ReadByte(OneWrie);
//	OneWrie_ReadByte(OneWrie);
//	OneWrie_ReadByte(OneWrie);
//	OneWrie_ReadByte(OneWrie);
//	OneWrie_ReadByte(OneWrie);
//	
//	SysTick_DeleymS(2000);				//SysTick延时nmS
	return tempr;
}
