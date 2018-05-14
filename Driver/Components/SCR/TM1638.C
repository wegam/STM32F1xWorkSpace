#include "TM1638.H"
#include "STM32_GPIO.H"
//#include "STM32F10x_BitBand.H"

#include "STM32F10x_BitBand.H"
#include "STM32_GPIO.H"
//#include	<REGX51.H>

//#define	DATA_COMMAND	0X40		//数据命令设置:数据读写模式，地址自增模式
//#define	DISP_COMMAND	0x80		//显示命令：显示亮度设置
//#define	ADDR_COMMAND	0XC0		//地址命令设置:数据写入起始地址

////TM1638模块引脚定义
//#define	DIO	PC12
//#define	CLK	PC11
//#define	STB	PD2

//#define	DIO_Port	GPIOC
//#define	DIO_Pin		GPIO_Pin_12

//#define	CLK_Port	GPIOC
//#define	CLK_Pin		GPIO_Pin_11

//#define	STB_Port	GPIOD
//#define	STB_Pin		GPIO_Pin_2


//TM1638模块引脚定义
#define	DIO	PA7
#define	CLK	PA5
#define	STB	PA4

#define	DIO_Port	GPIOA
#define	DIO_Pin		GPIO_Pin_7

#define	CLK_Port	GPIOA
#define	CLK_Pin		GPIO_Pin_5

#define	STB_Port	GPIOA
#define	STB_Pin		GPIO_Pin_4



//共阴数码管显示代码
unsigned char code[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71};


/*******************************************************************************
* 函数名			:	TM1638_Write
* 功能描述		:	写一字节数据 
* 输入			: void
* 返回值			: void
*******************************************************************************/
void TM1638_Write(unsigned char	DATA)			//写数据函数
{
	unsigned char i;
	for(i=0;i<8;i++)
	{
		CLK=0;
		if(DATA&0X01)
			DIO=1;
		else
			DIO=0;
		DATA>>=1;
		CLK=1;
	}
}
/*******************************************************************************
* 函数名			:	function
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
*******************************************************************************/
unsigned char TM1638_Read(void)					//读数据函数
{
	unsigned char i;
	unsigned char temp=0;
	DIO=1;	//设置为输入
	for(i=0;i<8;i++)
	{
		temp>>=1;
		CLK=0;
		if(DIO)
			temp|=0x80;
		CLK=1;
	}
	return temp;
}
/*******************************************************************************
* 函数名			:	Write_COM
* 功能描述		:	发送命令字 
* 输入			: void
* 返回值			: void
*******************************************************************************/
void Write_COM(unsigned char cmd)		//发送命令字
{
	STB=0;
	TM1638_Write(cmd);
	STB=1;
}
/*******************************************************************************
* 函数名			:	Read_key
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
*******************************************************************************/
unsigned char Read_key(void)
{
	unsigned char c[4],i,key_value=0;
	STB=0;
	TM1638_Write(0x42);		           //读键扫数据 命令
	for(i=0;i<4;i++)		
		c[i]=TM1638_Read();
	STB=1;					           //4个字节数据合成一个字节
	for(i=0;i<4;i++)
		key_value|=c[i]<<i;
	for(i=0;i<8;i++)
		if((0x01<<i)==key_value)
			break;
	return i;
}
/*******************************************************************************
* 函数名			:	function
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
*******************************************************************************/
void Write_DATA(unsigned char add,unsigned char DATA)		//指定地址写入数据
{
	Write_COM(0x40);					//固定地址
	STB=0;
	TM1638_Write(0xC0|add);		//写地址
	TM1638_Write(DATA);				//写数据
	STB=1;
}
/*******************************************************************************
* 函数名			:	Write_DataFX
* 功能描述		:	固定地址方式
* 输入			: void
* 返回值			: void
*******************************************************************************/
void Write_DataFX(unsigned char add,unsigned char DATA)		//固定地址方式
{
	Write_COM(0x44);					//固定地址命令
	STB=0;
	TM1638_Write(0xC0|(add<<1));		//写地址
	TM1638_Write(DATA);				//写数据
	STB=1;
}
/*******************************************************************************
* 函数名			:	Write_DataAI
* 功能描述		:	地址自增
* 输入			: void
* 返回值			: void
*******************************************************************************/
void Write_DataAI(unsigned char add,unsigned char DATA)		//地址自增
{
	unsigned char i;
	Write_COM(0x40);					//地址自增命令
	STB=0;
	TM1638_Write(0xC0);    		//设置起始地址
	for(i=0;i<8;i++)	   			//传送16个字节的数据
	{
		TM1638_Write(DATA);			//写数据
		TM1638_Write(0x01);			//写数据
	}
	STB=1;
}
/*******************************************************************************
* 函数名			:	Write_DataNum
* 功能描述		:	地址自增方式写数据
* 输入			: Startadd--起始地址，Num--数据
* 返回值			: void
*******************************************************************************/
void Write_DataNum(unsigned char Startadd,unsigned long Num)		//地址自增方式写入8位数据
{
//	Write_COM(0x40);					//地址自增命令
	STB=0;
	TM1638_Write(0xC0|Startadd);    		//设置起始地址
	
	TM1638_Write(code[Num/10000000]);
	TM1638_Write(code[Num/10000000]);			//写数据
	TM1638_Write(code[Num%10000000/1000000]);
	TM1638_Write(code[Num%10000000/1000000]);			//写数据
	TM1638_Write(code[Num%1000000/100000]);
	TM1638_Write(code[Num%1000000/100000]);			//写数据
	TM1638_Write(code[Num%100000/10000]);
	TM1638_Write(code[Num%100000/10000]);			//写数据
	TM1638_Write(code[Num%10000/1000]);
	TM1638_Write(code[Num%10000/1000]);			//写数据
	TM1638_Write(code[Num%1000/100]);
	TM1638_Write(code[Num%1000/100]);			//写数据
	TM1638_Write(code[Num%100/10]);
	TM1638_Write(code[Num%100/10]);			//写数据
	TM1638_Write(code[Num%10]);
	TM1638_Write(code[Num%10]);			//写数据
	STB=1;
}
/*
void Write_oneLED(unsigned char num,unsigned char flag)	//单独控制一个LED函数，num为需要控制的led序号，flag为0时熄灭，不为0时点亮
{
	if(flag)
		Write_DATA(2*num+1,1);
	else
		Write_DATA(2*num+1,0);
}  	*/
/*******************************************************************************
* 函数名			:	function
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
*******************************************************************************/
void Write_allLED(unsigned char LED_flag)					//控制全部LED函数，LED_flag表示各个LED状态
{
	unsigned char i;
	for(i=0;i<8;i++)
		{
			if(LED_flag&(1<<i))
				//Write_DATA(2*i+1,3);
				Write_DATA(2*i+1,1);
			else
				Write_DATA(2*i+1,0);
		}
}
/*******************************************************************************
* 函数名			:	function
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
*******************************************************************************/
//TM1638初始化函数
void init_TM1638(void)
{
	unsigned char i;
	GPIO_Configuration_OPP50	(DIO_Port,	DIO_Pin);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605
	GPIO_Configuration_OPP50	(CLK_Port,	CLK_Pin);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605
	GPIO_Configuration_OPP50	(STB_Port,	STB_Pin);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605
	
	Write_COM(0x8F);       //亮度 (0x88-0x8f)8级亮度可调
	Write_COM(0x40);       //采用地址自动加1
	STB=0;		           //
	TM1638_Write(0xC0);    //设置起始地址

	for(i=0;i<16;i++)	   //传送16个字节的数据
		TM1638_Write(0xFF);
	STB=1;
}



