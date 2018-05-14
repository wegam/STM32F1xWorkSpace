#ifdef TM1638_TEST

#include "TM1638_TEST.H"

#include "TM1638.H"

#include "STM32_PWM.H"
#include "STM32_GPIO.H"
#include "STM32_SYS.H"
#include "STM32_WDG.H"
#include "STM32_SYSTICK.H"
#include "STM32F10x_BitBand.H"

u16 us=0;
u16	mm=0;
u8	ss=0;
u8	hh=0;

u32	SYSTIME	=	0;

/*******************************************************************************
* 函数名		:	
* 功能描述	:	 
* 输入		:	
* 输出		:
* 返回 		:
*******************************************************************************/
void TM1638_Configuration(void)
{	
	SYS_Configuration();					//系统配置---打开系统时钟 STM32_SYS.H
	
	GPIO_DeInitAll();							//将所有的GPIO关闭----V20170605
	
	SysTick_Configuration(1000);	//系统嘀嗒时钟配置72MHz,单位为uS
	
	IWDG_Configuration(1000);			//独立看门狗配置---参数单位ms	
	
	PWM_OUT(TIM2,PWM_OUTChannel1,5000,20);						//PWM设定-20161127版本
	
	init_TM1638();

	Write_COM(0x40);					//地址自增命令

}
/*******************************************************************************
* 函数名		:	
* 功能描述	:	 
* 输入		:	
* 输出		:
* 返回 		:
*******************************************************************************/
void TM1638_Server(void)
{
	
	IWDG_Feed();								//独立看门狗喂狗
	SYSTIME++;
	if(SYSTIME>=99999999)
		SYSTIME	=	0;
	Write_DataNum(0,SYSTIME);
//	if(SYSTIME	==	0)
//	{
//		mm++;
//		if(mm>15)
//			mm=0;
//		Write_COM(0x44);			//固定地址
//		STB=0;
//		TM1638_Write(0xCE);		//写地址
//		Write_DATA(i++<<1,code[mm]);
//		STB=1;
//	}
//	if(SYSTIME	==	99999)
//	{
//		Write_COM(0x8c);       //亮度 (0x88-0x8f)8级亮度可调
//		Write_COM(0x40);       //采用地址自动加1
//		STB=0;		           //
//		TM1638_Write(0xC0);    //设置起始地址
//		i	=	0;
//		Write_DATA(0,code[SYSTIME/10000000]);
//		Write_DATA(2,code[SYSTIME%10000000/100000]);
//		Write_DATA(4,code[SYSTIME%1000000/100000]);
//		Write_DATA(6,code[SYSTIME%100000/10000]);
//		Write_DATA(8,code[SYSTIME%10000/1000]);
//		Write_DATA(10,code[SYSTIME%1000/100]);
//		Write_DATA(12,code[SYSTIME%100/10]);
//		Write_DATA(14,code[SYSTIME%10]);
//		STB=1;
//	}

//	if(SYSTIME%1000	==	0)
//	{
//		mm++;
//		if(mm>15)
//			mm=0;
//		Write_DataAI(1,code[mm]);
//	}
//	if(SYSTIME%10	==	0)
//	{
//		mm++;
//		if(mm>15)
//			mm=0;
//		Write_DataFX(0,code[mm]);
//		Write_DataFX(1,code[mm]);
//		Write_DataFX(2,code[mm]);
//		Write_DataFX(3,code[mm]);
//		Write_DataFX(4,code[mm]);
//		Write_DataFX(5,code[mm]);
//		Write_DataFX(6,code[mm]);
//		Write_DataFX(7,code[mm]);
//	}
	
//	if(SYSTIME%100	==	0)
//	{
//		mm++;
//		if(mm>15)
//			mm=0;
//		Write_DataNum(0,code[mm]);
//	}
		
	
//	i	=	0;
//	Write_DATA(i++<<1,code[SYSTIME/10000000]);
//	Write_DATA(i++<<1,code[SYSTIME%10000000/100000]);
//	Write_DATA(i++<<1,code[SYSTIME%1000000/100000]);
//	Write_DATA(i++<<1,code[SYSTIME%100000/10000]);
//	Write_DATA(i++<<1,code[SYSTIME%10000/1000]);
//	Write_DATA(i++<<1,code[SYSTIME%1000/100]);
//	Write_DATA(i++<<1,code[SYSTIME%100/10]);
//	Write_DATA(i++<<1,code[SYSTIME%10]);

//	Write_DATA(i<1,code[SYSTIME/10000]);
//	for(i	=	0;i<5;i++)
//	{
//		Write_DATA(i<1,code[i]);
//	}
//		i=Read_key();                  		//读按键值
//		if(i<8)
//		{
//			num[i]++;
//			while(Read_key()==i);		       //等待按键释放
//			if(num[i]>15)
//			num[i]=0;
//			Write_DATA(i*2,code[num[i]]);
//			Write_allLED(1<<i);
//		}
	
	
	
//	init_TM1638();
//	TM1638_DIS();
}
#endif


