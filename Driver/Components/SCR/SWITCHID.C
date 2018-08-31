/*********************************************
*步进电机驱动
*结构体参数配置形式
*驱动模式---计时
*特殊功能:超时,加速
*最高优先级:停止--任何情况下,有停止命令,优先执行停止
*其它:刹车
**********************************************/

#include "SWITCHID.H"

#include "STM32_GPIO.H"


/****************************************************************
*函数名:
*描述:
*
******************************************************************/
void SwitchIdInitialize(SwitchDef *pSwitch)
{
	unsigned char NumOfSW=pSwitch->NumOfSW;			//拉入的拔码开关位数
	//根据接入的拔码开关位数从低位到高位进行上拉输入配置
	if(NumOfSW)	//SW1
	{
		GPIO_Configuration_IPU	(pSwitch->SW1_PORT,	pSwitch->SW1_Pin);			//将GPIO相应管脚配置为上拉输入模式----V20170605
		NumOfSW-=1;
	}
	if(NumOfSW)	//SW2
	{
		GPIO_Configuration_IPU	(pSwitch->SW2_PORT,	pSwitch->SW2_Pin);			//将GPIO相应管脚配置为上拉输入模式----V20170605
		NumOfSW-=1;
	}
	if(NumOfSW)	//SW3
	{
		GPIO_Configuration_IPU	(pSwitch->SW3_PORT,	pSwitch->SW3_Pin);			//将GPIO相应管脚配置为上拉输入模式----V20170605
		NumOfSW-=1;
	}
	if(NumOfSW)	//SW4
	{
		GPIO_Configuration_IPU	(pSwitch->SW4_PORT,	pSwitch->SW4_Pin);			//将GPIO相应管脚配置为上拉输入模式----V20170605
		NumOfSW-=1;
	}
	if(NumOfSW)	//SW5
	{
		GPIO_Configuration_IPU	(pSwitch->SW5_PORT,	pSwitch->SW5_Pin);			//将GPIO相应管脚配置为上拉输入模式----V20170605
		NumOfSW-=1;
	}
	if(NumOfSW)	//SW6
	{
		GPIO_Configuration_IPU	(pSwitch->SW6_PORT,	pSwitch->SW6_Pin);			//将GPIO相应管脚配置为上拉输入模式----V20170605
		NumOfSW-=1;
	}
	if(NumOfSW)	//SW7
	{
		GPIO_Configuration_IPU	(pSwitch->SW7_PORT,	pSwitch->SW7_Pin);			//将GPIO相应管脚配置为上拉输入模式----V20170605
		NumOfSW-=1;
	}
	if(NumOfSW)	//SW8
	{
		GPIO_Configuration_IPU	(pSwitch->SW8_PORT,	pSwitch->SW8_Pin);			//将GPIO相应管脚配置为上拉输入模式----V20170605
		NumOfSW-=1;
	}
	if(NumOfSW)	//SW9
	{
		GPIO_Configuration_IPU	(pSwitch->SW9_PORT,	pSwitch->SW9_Pin);			//将GPIO相应管脚配置为上拉输入模式----V20170605
		NumOfSW-=1;
	}
	if(NumOfSW)	//SW10
	{
		GPIO_Configuration_IPU	(pSwitch->SW10_PORT,	pSwitch->SW10_Pin);			//将GPIO相应管脚配置为上拉输入模式----V20170605
		NumOfSW-=1;
	}
	if(NumOfSW)	//SW11
	{
		GPIO_Configuration_IPU	(pSwitch->SW11_PORT,	pSwitch->SW11_Pin);			//将GPIO相应管脚配置为上拉输入模式----V20170605
		NumOfSW-=1;
	}
	if(NumOfSW)	//SW12
	{
		GPIO_Configuration_IPU	(pSwitch->SW12_PORT,	pSwitch->SW12_Pin);			//将GPIO相应管脚配置为上拉输入模式----V20170605
		NumOfSW-=1;
	}
	if(NumOfSW)	//SW13
	{
		GPIO_Configuration_IPU	(pSwitch->SW13_PORT,	pSwitch->SW13_Pin);			//将GPIO相应管脚配置为上拉输入模式----V20170605
		NumOfSW-=1;
	}
	if(NumOfSW)	//SW14
	{
		GPIO_Configuration_IPU	(pSwitch->SW14_PORT,	pSwitch->SW14_Pin);			//将GPIO相应管脚配置为上拉输入模式----V20170605
		NumOfSW-=1;
	}
	if(NumOfSW)	//SW15
	{
		GPIO_Configuration_IPU	(pSwitch->SW15_PORT,	pSwitch->SW15_Pin);			//将GPIO相应管脚配置为上拉输入模式----V20170605
		NumOfSW-=1;
	}
	if(NumOfSW)	//SW16
	{
		GPIO_Configuration_IPU	(pSwitch->SW16_PORT,	pSwitch->SW16_Pin);			//将GPIO相应管脚配置为上拉输入模式----V20170605
		NumOfSW-=1;
	}
	SWITCHID_Read(pSwitch);
}
/****************************************************************
*函数名:
*描述:
*
******************************************************************/
unsigned short SWITCHID_Read(SwitchDef *pSwitch)
{
	unsigned short	reValue=0;	
	
	unsigned long *P=(unsigned long*)&(pSwitch->SWData);		//获取数据结构体地址,以便将读取的数据保存	
	unsigned char NumOfSW=pSwitch->NumOfSW;		//接入的拔码开关位数

	unsigned short	Temp	=	0xFFFF<<NumOfSW;
	
	//根据接入的拔码开关位数从低位到高位进行读取
	if(NumOfSW)	//SW1
	{
		NumOfSW-=1;
		if(pSwitch->SW1_PORT-> IDR	&pSwitch->SW1_Pin)
			reValue|=0x0001<<0;
	}
	if(NumOfSW)	//SW2
	{
		NumOfSW-=1;
		if(pSwitch->SW2_PORT-> IDR	&pSwitch->SW2_Pin)
			reValue|=0x0001<<1;
	}
	if(NumOfSW)	//SW3
	{
		NumOfSW-=1;
		if(pSwitch->SW3_PORT-> IDR	&pSwitch->SW3_Pin)
			reValue|=0x0001<<2;
	}
	if(NumOfSW)	//SW4
	{
		NumOfSW-=1;
		if(pSwitch->SW4_PORT-> IDR	&pSwitch->SW4_Pin)
			reValue|=0x0001<<3;
	}
	if(NumOfSW)	//SW5
	{
		NumOfSW-=1;
		if(pSwitch->SW5_PORT-> IDR	&pSwitch->SW5_Pin)
			reValue|=0x0001<<4;
	}
	if(NumOfSW)	//SW6
	{
		NumOfSW-=1;
		if(pSwitch->SW6_PORT-> IDR	&pSwitch->SW6_Pin)
			reValue|=0x0001<<5;
	}
	if(NumOfSW)	//SW7
	{
		NumOfSW-=1;
		if(pSwitch->SW7_PORT-> IDR	&pSwitch->SW7_Pin)
			reValue|=0x0001<<6;
	}
	if(NumOfSW)	//SW8
	{
		NumOfSW-=1;
		if(pSwitch->SW8_PORT-> IDR	&pSwitch->SW8_Pin)
			reValue|=0x0001<<7;
	}
	if(NumOfSW)	//SW9
	{
		NumOfSW-=1;
		if(pSwitch->SW9_PORT-> IDR	&pSwitch->SW9_Pin)
			reValue|=0x0001<<8;
	}
	if(NumOfSW)	//SW10
	{
		NumOfSW-=1;
		if(pSwitch->SW10_PORT-> IDR	&pSwitch->SW10_Pin)
			reValue|=0x0001<<9;
	}
	if(NumOfSW)	//SW11
	{
		NumOfSW-=1;
		if(pSwitch->SW11_PORT-> IDR	&pSwitch->SW11_Pin)
			reValue|=0x0001<<10;
	}
	if(NumOfSW)	//SW12
	{
		NumOfSW-=1;
		if(pSwitch->SW12_PORT-> IDR	&pSwitch->SW12_Pin)
			reValue|=0x0001<<11;
	}
	if(NumOfSW)	//SW13
	{
		NumOfSW-=1;
		if(pSwitch->SW13_PORT-> IDR	&pSwitch->SW13_Pin)
			reValue|=0x0001<<12;
	}
	if(NumOfSW)	//SW14
	{
		NumOfSW-=1;
		if(pSwitch->SW14_PORT-> IDR	&pSwitch->SW14_Pin)
			reValue|=0x0001<<13;
	}
	if(NumOfSW)	//SW15
	{
		NumOfSW-=1;
		if(pSwitch->SW15_PORT-> IDR	&pSwitch->SW15_Pin)
			reValue|=0x0001<<14;
	}
	if(NumOfSW)	//SW16
	{
		NumOfSW-=1;
		if(pSwitch->SW16_PORT-> IDR	&pSwitch->SW16_Pin)
			reValue|=0x0001<<15;
	}
	reValue	|=	Temp;
	reValue=~reValue;		//拔码开关低有效,需要取反
	*P=reValue;
	pSwitch->nSWITCHID=reValue;
	
	return	reValue;	//将数据返回(如果需要直接获取读取值可以使用返回值)
}

