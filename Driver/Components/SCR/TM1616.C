#include "TM1616.H"
#include "STM32_GPIO.H"
//#include "STM32F10x_BitBand.H"

unsigned char TM1616_Daddr[]={0XC0,0XC2,0XC4,0XC6,0XC8,0XCA,0XCC,0XCE};			//显示地址
unsigned char TM1616_SegCode[]={0x3F,0X06,0X5B,0X4F,0x66,0X6D,0X7D,0x07,0x7f,0x6f,0x00,0xff};
unsigned char TM1616_CovSeg[8]={0};			//共阳显示时转换后显示代码
//unsigned char d[8]={0};


static void TM1616_WriteByte(TM1616Def *Pinfo,unsigned char byted);
static void TM1616_WriteCommand(TM1616Def *Pinfo,unsigned char command);

/*******************************************************************************
*函数名			:	function
*功能描述		:	函数功能说明
*输入				: 
*返回值			:	无
*******************************************************************************/
void TM1616_Initialize(TM1616Def *Pinfo)
{
	GPIO_Configuration_OPP50	(Pinfo->DIO_PORT,		Pinfo->DIO_Pin);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度2MHz----V20170605
	GPIO_Configuration_OPP50	(Pinfo->CLK_PORT,		Pinfo->CLK_Pin);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度2MHz----V20170605
	GPIO_Configuration_OPP50	(Pinfo->STB_PORT,		Pinfo->STB_Pin);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度2MHz----V20170605
}
/*******************************************************************************
*函数名			:	TM1616_Display
*功能描述		:	4位数显示
*输入				: 
*返回值			:	无
*******************************************************************************/
void TM1616_Display(TM1616Def *Pinfo,u16 Data)
{
	TM1616_WriteCommand(Pinfo,0x00);		//显示模式
	TM1616_WriteCommand(Pinfo,0x40);		//地址自增命令	

	Pinfo->STB_PORT->BRR = Pinfo->STB_Pin;		//stb=0;
	
	TM1616_WriteByte(Pinfo,0xC0);    //设置起始地址
	
	TM1616_WriteByte(Pinfo,TM1616_SegCode[(Data/1000)%10]);
	TM1616_WriteByte(Pinfo,0x00);
	TM1616_WriteByte(Pinfo,TM1616_SegCode[(Data/100)%10]);
	TM1616_WriteByte(Pinfo,0x00);
	TM1616_WriteByte(Pinfo,TM1616_SegCode[(Data/10)%10]);
	TM1616_WriteByte(Pinfo,0x00);
	TM1616_WriteByte(Pinfo,TM1616_SegCode[Data%10]);
	TM1616_WriteByte(Pinfo,0x00);

	Pinfo->STB_PORT->BSRR = Pinfo->STB_Pin;		//stb=1;
	
	TM1616_WriteCommand(Pinfo,0x8D);		//亮度命令	
}
/*******************************************************************************
*函数名			:	function
*功能描述		:	函数功能说明
*输入				: 
*返回值			:	无
*******************************************************************************/
static void TM1616_WriteByte(TM1616Def *Pinfo,unsigned char byted)
{
	unsigned char i=0;
	for(i=0;i<8;i++)
	{
		GPIO_ResetBits(Pinfo->CLK_PORT, Pinfo->CLK_Pin);
		if((byted&0x01)==0x01)						 //确认最低位数，从低位开始写入
		{
			Pinfo->DIO_PORT->BSRR = Pinfo->DIO_Pin;		//dio=1;
		}
		else
		{
			Pinfo->DIO_PORT->BRR = Pinfo->DIO_Pin;		//dio=0;
		}
		GPIO_SetBits(Pinfo->CLK_PORT, Pinfo->CLK_Pin);
		byted=byted>>1;							 //右移一位		
	}
}
/*******************************************************************************
*函数名			:	function
*功能描述		:	函数功能说明
*输入				: 
*返回值			:	无
*******************************************************************************/
static void TM1616_WriteCommand(TM1616Def *Pinfo,unsigned char command)
{
	Pinfo->STB_PORT->BRR = Pinfo->STB_Pin;		//stb=0;
	TM1616_WriteByte(Pinfo,command);
	Pinfo->STB_PORT->BSRR = Pinfo->STB_Pin;		//stb=1;
}




