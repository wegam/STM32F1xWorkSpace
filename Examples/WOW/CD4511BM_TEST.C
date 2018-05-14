#ifdef	CD4511BM_TEST


//1）数码管测试指令
//2）小数点整齐显示指令
//3）特殊功能，根据指令确认有无称重与CAN,485通讯
#include "CD4511.H"
#include "CD4511BM_TEST.H"
#include "STM32_GPIO.H"
#include "STM32_PWM.H"
#include "STM32_SYS.H"
#include "STM32_SYSTICK.H"
#include "STM32F10x_BitBand.H"


#define	CD4511BM_DEBUG_TEST			//调试时数码管计数显示，正常使用时应该注释掉

CD4511_Pindef CD4511_Pin1;		//第一位数码管
CD4511_Pindef CD4511_Pin2;		//第二位数码管
CD4511_Pindef CD4511_Pin3;		//第三位数码管

u16 Time=0;
u16 data=0;

void CD4511BM_PinSet(void);
void SEG_DISPALY(u8 wei,u16 num);
/*******************************************************************************
*函数名		:	function
*功能描述	:	函数功能说明
*输入			: 
*输出			:	无
*返回值		:	无
*例程			:
*******************************************************************************/
void CD4511BM_TEST_Configuration(void)
{
	SYS_Configuration();											//系统配置 STM32_SYS.H	
	PWM_OUT(TIM2,PWM_OUTChannel1,1,500);
	SysTick_Configuration(1000);							//系统嘀嗒时钟配置72MHz,单位为uS
	
	CD4511BM_PinSet();		//CD4511驱动管脚及数码管位选管脚配置
}

/*******************************************************************************
*函数名		:	function
*功能描述	:	函数功能说明
*输入			: 
*输出			:	无
*返回值		:	无
*例程			:
*******************************************************************************/
void CD4511BM_TEST_Server(void)
{
	++Time;	
	if(Time>=3)
	{
		Time=0;	
		++data;		
	}
	if(data>999)
	{
		GPIO_Toggle	(GPIOA,	GPIO_Pin_0);		//将GPIO相应管脚输出翻转----V20170605
		data=0;
	}
	SEG_DISPALY(Time%3,data);
//	SEG_DISPALY(1,1);
}
/*******************************************************************************
* 函数名			:	function
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
*******************************************************************************/
void CD4511BM_PinSet(void)
{
	//********************RS485_CTL配置
//	GPIO_Configuration_OPP50(GPIOA,GPIO_Pin_1);				//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605
//	
//	//********************拔码开关配置
//	GPIO_Configuration_IPU(GPIOC,GPIO_Pin_0);						//将GPIO相应管脚配置为上拉输入模式----V20170605
//	GPIO_Configuration_IPU(GPIOC,GPIO_Pin_1);						//将GPIO相应管脚配置为上拉输入模式----V20170605
//	GPIO_Configuration_IPU(GPIOC,GPIO_Pin_2);						//将GPIO相应管脚配置为上拉输入模式----V20170605
//	GPIO_Configuration_IPU(GPIOC,GPIO_Pin_3);						//将GPIO相应管脚配置为上拉输入模式----V20170605
//	GPIO_Configuration_IPU(GPIOC,GPIO_Pin_4);						//将GPIO相应管脚配置为上拉输入模式----V20170605
//	GPIO_Configuration_IPU(GPIOC,GPIO_Pin_5);						//将GPIO相应管脚配置为上拉输入模式----V20170605
//	GPIO_Configuration_IPU(GPIOC,GPIO_Pin_6);						//将GPIO相应管脚配置为上拉输入模式----V20170605
//	GPIO_Configuration_IPU(GPIOC,GPIO_Pin_7);						//将GPIO相应管脚配置为上拉输入模式----V20170605
	
	//********************数码管
	//位
	GPIO_Configuration_OPP50	(GPIOB,		GPIO_Pin_5);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度2MHz----V20170605
	GPIO_Configuration_OPP50	(GPIOB,		GPIO_Pin_14);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度2MHz----V20170605
	GPIO_Configuration_OPP50	(GPIOB,		GPIO_Pin_15);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度2MHz----V20170605
	
	//SEG第一位数码管
	CD4511_Pin1.CD4511_A0_PORT=GPIOB;
	CD4511_Pin1.CD4511_A0_Pin=GPIO_Pin_0;
	
	CD4511_Pin1.CD4511_A1_PORT=GPIOB;
	CD4511_Pin1.CD4511_A1_Pin=GPIO_Pin_1;
	
	CD4511_Pin1.CD4511_A2_PORT=GPIOB;
	CD4511_Pin1.CD4511_A2_Pin=GPIO_Pin_2;
	
	CD4511_Pin1.CD4511_A3_PORT=GPIOB;
	CD4511_Pin1.CD4511_A3_Pin=GPIO_Pin_3;
	
	CD4511_Pin1.CD4511_EN_PORT=GPIOB;
	CD4511_Pin1.CD4511_EN_Pin=GPIO_Pin_15;
	
	CD4511_PinConf(&CD4511_Pin1);
	
	//SEG2第二位数码管
	CD4511_Pin2.CD4511_A0_PORT=GPIOB;
	CD4511_Pin2.CD4511_A0_Pin=GPIO_Pin_0;
	
	CD4511_Pin2.CD4511_A1_PORT=GPIOB;
	CD4511_Pin2.CD4511_A1_Pin=GPIO_Pin_1;
	
	CD4511_Pin2.CD4511_A2_PORT=GPIOB;
	CD4511_Pin2.CD4511_A2_Pin=GPIO_Pin_2;
	
	CD4511_Pin2.CD4511_A3_PORT=GPIOB;
	CD4511_Pin2.CD4511_A3_Pin=GPIO_Pin_3;
	
	CD4511_Pin2.CD4511_EN_PORT=GPIOB;
	CD4511_Pin2.CD4511_EN_Pin=GPIO_Pin_14;
	
	CD4511_PinConf(&CD4511_Pin2);
	
	//SEG3第三位数码管
	CD4511_Pin3.CD4511_A0_PORT=GPIOB;
	CD4511_Pin3.CD4511_A0_Pin=GPIO_Pin_0;
	
	CD4511_Pin3.CD4511_A1_PORT=GPIOB;
	CD4511_Pin3.CD4511_A1_Pin=GPIO_Pin_1;
	
	CD4511_Pin3.CD4511_A2_PORT=GPIOB;
	CD4511_Pin3.CD4511_A2_Pin=GPIO_Pin_2;
	
	CD4511_Pin3.CD4511_A3_PORT=GPIOB;
	CD4511_Pin3.CD4511_A3_Pin=GPIO_Pin_3;
	
	CD4511_Pin3.CD4511_EN_PORT=GPIOB;
	CD4511_Pin3.CD4511_EN_Pin=GPIO_Pin_5;
	
	CD4511_PinConf(&CD4511_Pin3);
}
/*******************************************************************************
*函数名		:	function
*功能描述	:	函数功能说明
*输入			: 
*输出			:	无
*返回值		:	无
*例程			:
*******************************************************************************/
void SEG_DISPALY(u8 wei,u16 num)
{
	CD4511_DisplayOFF(&CD4511_Pin1);			//关闭显示---关NPN三极管
	CD4511_DisplayOFF(&CD4511_Pin2);			//关闭显示---关NPN三极管
	CD4511_DisplayOFF(&CD4511_Pin3);			//关闭显示---关NPN三极管
	if(wei==2)
	{
//		if(num>100)
//		{
			CD4511_WriteData(&CD4511_Pin3,num/100);
//		}
	}
	else if(wei==1)
	{
//		if(num>=10||num>=100)
//		{
//			if(num>=100)
//			{
				num=num%100;
//			}
			CD4511_WriteData(&CD4511_Pin2,num/10);
//		}
	}
	else
	{
		CD4511_WriteData(&CD4511_Pin1,num%10);
	}
	
//	if(time%100>0)
//	{
//		PB5=1;
//		CD4511_WriteData(&CD4511_Pin,time%100);
//	}
//	else
//	{
//		PB5=0;
//	}	
//	if((time>100)||((time/10)%10>0))
//	{
//		PB14=1;
//		CD4511_WriteData(&CD4511_Pin,(time/10)%10);
//	}
//	else
//	{
//		PB14=0;
//	}
//	if(time%10>0)
//	{
//		PB15=1;
//		CD4511_WriteData(&CD4511_Pin,time%10);
//	}
//	else
//	{
//		PB15=0;
//	}
}
/*******************************************************************************
* 函数名			:	function
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
*******************************************************************************/
void CD4511BM_KEY_FUNC(void)
{
//	GPIO_InitTypeDef GPIO_InitStructure;						//GPIO结构体
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
//	
//	//1)**********S3管脚配置及初始化
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;				//GPIO引脚号			
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;				//GPIO模式
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;			//GPIO输出速度，输入时无效
//	GPIO_Init(GPIOB,&GPIO_InitStructure);	

}








#endif

