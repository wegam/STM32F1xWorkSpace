#include "TM1638.H"
#include "STM32_GPIO.H"
//#include "STM32F10x_BitBand.H"

#define	TM1638_DelayTime	10

unsigned char TM1638_Daddr[]={0XC0,0XC2,0XC4,0XC6,0XC8,0XCA,0XCC,0XCE};			//显示地址
unsigned char TM1638_SegCode[]={0x3F,0X06,0X5B,0X4F,0x66,0X6D,0X7D,0x07,0x7f,0x6f,0x00,0xff};
unsigned char TM1638_CovSeg[8]={0};			//共阳显示时转换后显示代码
//unsigned char d[8]={0};


void TM1638_Delay(u16 time);
void TM1638_WriteByte(TM1638_Pindef *Pinfo,unsigned char byted);
void TM1638_WriteCommand(TM1638_Pindef *Pinfo,unsigned char command);
void TM1638_WriteCommandN(TM1638_Pindef *Pinfo,unsigned char command);
void TM1638_DataCov(u16 number);			//共阳显示数据转换

/*******************************************************************************
*函数名			:	function
*功能描述		:	函数功能说明
*输入				: 
*返回值			:	无
*******************************************************************************/
void TM1638_Delay(u16 time)
{
	while(time--);
}
/*******************************************************************************
*函数名			:	function
*功能描述		:	函数功能说明
*输入				: 
*返回值			:	无
*******************************************************************************/
void TM1638_PinConf(TM1638_Pindef *Pinfo)
{
	GPIO_Configuration_OPP50	(Pinfo->TM1638_DIO_PORT,		Pinfo->TM1638_DIO_Pin);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度2MHz----V20170605
	GPIO_Configuration_OPP50	(Pinfo->TM1638_CLK_PORT,		Pinfo->TM1638_CLK_Pin);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度2MHz----V20170605
	GPIO_Configuration_OPP50	(Pinfo->TM1638_STB_PORT,		Pinfo->TM1638_STB_Pin);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度2MHz----V20170605
}
/*******************************************************************************
*函数名			:	function
*功能描述		:	函数功能说明
*输入				: 
*返回值			:	无
*******************************************************************************/
void TM1638_WriteByte(TM1638_Pindef *Pinfo,unsigned char byted)
{
	unsigned char i=0;
	for(i=0;i<8;i++)
	{
		GPIO_ResetBits(Pinfo->TM1638_CLK_PORT, Pinfo->TM1638_CLK_Pin);
		TM1638_Delay(TM1638_DelayTime);
		if((byted&0x01)==0x01)						 //确认最低位数，从低位开始写入
		{
			GPIO_SetBits(Pinfo->TM1638_DIO_PORT, Pinfo->TM1638_DIO_Pin);
		}
		else
		{
			GPIO_ResetBits(Pinfo->TM1638_DIO_PORT, Pinfo->TM1638_DIO_Pin);
		}
		TM1638_Delay(TM1638_DelayTime);
		GPIO_SetBits(Pinfo->TM1638_CLK_PORT, Pinfo->TM1638_CLK_Pin);
		TM1638_Delay(TM1638_DelayTime);
		byted=byted>>1;							 //右移一位		
	}
}
/*******************************************************************************
*函数名			:	function
*功能描述		:	函数功能说明
*输入				: 
*返回值			:	无
*******************************************************************************/
void TM1638_WriteCommand(TM1638_Pindef *Pinfo,unsigned char command)
{
//	stb=1;
	GPIO_ResetBits(Pinfo->TM1638_STB_PORT, Pinfo->TM1638_STB_Pin);			//stb=0;
	TM1638_Delay(TM1638_DelayTime);
	TM1638_WriteByte(Pinfo,0x44);	//固定地址模式
	TM1638_Delay(TM1638_DelayTime);
	GPIO_SetBits(Pinfo->TM1638_STB_PORT, Pinfo->TM1638_STB_Pin);		//stb=1;
	TM1638_Delay(TM1638_DelayTime);
	
	GPIO_ResetBits(Pinfo->TM1638_STB_PORT, Pinfo->TM1638_STB_Pin);			//stb=0;
	TM1638_Delay(TM1638_DelayTime);
	TM1638_WriteByte(Pinfo,command);				//脉冲宽度设置 0x80（关）<0x88<0x89<0x8a<0x8b<0x8c<0x8d<0x8e<0x8f
	TM1638_Delay(TM1638_DelayTime);
	GPIO_SetBits(Pinfo->TM1638_STB_PORT, Pinfo->TM1638_STB_Pin);		//stb=1;
	TM1638_Delay(TM1638_DelayTime);
}
/*******************************************************************************
*函数名			:	function
*功能描述		:	函数功能说明
*输入				: 
*返回值			:	无
*******************************************************************************/
void TM1638_WriteCommandN(TM1638_Pindef *Pinfo,unsigned char command)
{
//	stb=1;
	GPIO_SetBits(Pinfo->TM1638_STB_PORT, Pinfo->TM1638_STB_Pin);			//stb=0;
	TM1638_Delay(TM1638_DelayTime);
	TM1638_WriteByte(Pinfo,0x44);																			//固定地址模式
	TM1638_Delay(TM1638_DelayTime);
	GPIO_ResetBits(Pinfo->TM1638_STB_PORT, Pinfo->TM1638_STB_Pin);		//stb=1;
	TM1638_Delay(TM1638_DelayTime);
	
	GPIO_SetBits(Pinfo->TM1638_STB_PORT, Pinfo->TM1638_STB_Pin);			//stb=0;
	TM1638_Delay(TM1638_DelayTime);
	TM1638_WriteByte(Pinfo,command);				//脉冲宽度设置(亮度) 0x80（关）<0x88<0x89<0x8a<0x8b<0x8c<0x8d<0x8e<0x8f
	TM1638_Delay(TM1638_DelayTime);
	GPIO_ResetBits(Pinfo->TM1638_STB_PORT, Pinfo->TM1638_STB_Pin);		//stb=1;
	TM1638_Delay(TM1638_DelayTime);
}
/*******************************************************************************
*函数名			:	function
*功能描述		:	函数功能说明
*输入				: 
*返回值			:	无
*******************************************************************************/
void TM1638_WriteData(TM1638_Pindef *Pinfo,u16 Data)
{
	unsigned char i=0;
	TM1638_WriteCommand(Pinfo,0X88);			//亮度
	TM1638_Delay(TM1638_DelayTime);
	for(i=0;i<8;i++)
	{
		GPIO_ResetBits(Pinfo->TM1638_STB_PORT, Pinfo->TM1638_STB_Pin);	//stb=0;
		TM1638_Delay(TM1638_DelayTime);
		TM1638_WriteByte(Pinfo,Data);				//写入地址
		TM1638_WriteByte(Pinfo,Data);				//写入数据
		TM1638_Delay(TM1638_DelayTime);
		GPIO_SetBits(Pinfo->TM1638_STB_PORT, Pinfo->TM1638_STB_Pin);		//stb=1;
	}
}
/*******************************************************************************
*函数名			:	function
*功能描述		:	函数功能说明
*输入				: 
*返回值			:	无
*******************************************************************************/
void TM1638_WriteDataN(TM1638_Pindef *Pinfo,u16 Data)
{
	unsigned char i=0;
	TM1638_DataCov(Data);
	TM1638_WriteCommandN(Pinfo,0X8A);			//亮度
	TM1638_Delay(TM1638_DelayTime);
	for(i=0;i<8;i++)
	{
		GPIO_SetBits(Pinfo->TM1638_STB_PORT, Pinfo->TM1638_STB_Pin);			//stb=0;
		TM1638_WriteByte(Pinfo,TM1638_Daddr[i]);				//写入地址
		TM1638_Delay(TM1638_DelayTime);
		TM1638_WriteByte(Pinfo,TM1638_CovSeg[i]);				//写入数据
		TM1638_Delay(TM1638_DelayTime);
		GPIO_ResetBits(Pinfo->TM1638_STB_PORT, Pinfo->TM1638_STB_Pin);		//stb=1;
	}
}
/*******************************************************************************
*函数名			:	function
*功能描述		:	共阳显示数据转换
*输入				: 
*返回值			:	无
*******************************************************************************/
void TM1638_DataCov(u16 number)
{
	unsigned char s[4];
	unsigned char	i,j;
	s[0]=TM1638_SegCode[number/1000];
	s[1]=TM1638_SegCode[number%1000/100];
	s[2]=TM1638_SegCode[number%100/10];
	s[3]=TM1638_SegCode[number%10];
	
//	if(number<10)
//	{
//		s[0]=TM1638_SegCode[10];
//		s[1]=TM1638_SegCode[10];
//		s[2]=TM1638_SegCode[10];
//	}
//	else if(100>number&&number>9)
//	{
//		s[0]=TM1638_SegCode[10];
//		s[1]=TM1638_SegCode[10];
//	}
//	else if(1000>number&&number>99)
//		s[0]=TM1638_SegCode[10];
	
	
	
	for(i=0;i<8;i++)
	{
		for(j=0;j<4;j++)
		{
			TM1638_CovSeg[i]<<=1;
			if(s[j]&0x01)
			TM1638_CovSeg[i]|=0x01;
			s[j]>>=1;
			
		}
	}

}



