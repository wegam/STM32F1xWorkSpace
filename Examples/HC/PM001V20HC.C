



#ifdef PM001V20HC				//网关板

#include "PM001V20HC.H"

#define master 0

#include "STM32_GPIO.H"
#include "STM32_SYS.H"
#include "STM32_SYSTICK.H"
#include "STM32_WDG.H"
#include "STM32_USART.H"
#include "STM32_PWM.H"
#include "STM32_CAN.H"

#include "string.h"				//串和内存操作函数头文件
#include "stm32f10x_dma.h"
#include "STM32F10x_BitBand.H"

#define BufferSize	128
RS485_TypeDef	RS485A,RS485B;
CanRxMsg RxMessage;

u16 sysledcnt=0;			//系统运行指示灯扫描计数  0.5秒

u8 txBuffer[BufferSize]={0};
u8 rxBuffer[BufferSize]={0};
u16 CanTime	=	0;
u8 CanNum	=	0;

u8	txflg=0;	//发送标志
u8	rxflg=0;	//接收标志
u8	bpflg=0;	//蜂鸣器使能标志

/*******************************************************************************
* 函数名		:	
* 功能描述	:	 
* 输入		:	
* 输出		:
* 返回 		:
*******************************************************************************/
void PM001V20HC_Configuration(void)
{
	SYS_Configuration();					//系统配置---打开系统时钟 STM32_SYS.H
	
	SysTick_Configuration(1000);	//系统嘀嗒时钟配置72MHz,单位为uS
	
//	IWDG_Configuration(1000);			//独立看门狗配置---参数单位ms
	
	GPIO_DeInitAll();							//将所有的GPIO关闭----V20170605
	
	Driver_Configuration();
	
	USART_Configuration();
	
	CAN_Configuration_NR(100000);				//CAN1配置---标志位查询方式，不开中断
	
	CAN_FilterInitConfiguration_StdData(1,1,0);	//CAN滤波器配置---标准数据帧模式
	
	PWM_OUT(TIM2,PWM_OUTChannel1,1,500);	//PWM设定-20161127版本	

}
/*******************************************************************************
* 函数名		:	
* 功能描述	:	 
* 输入		:	
* 输出		:
* 返回 		:
*******************************************************************************/
void PM001V20HC_Server(void)
{	
	IWDG_Feed();								//独立看门狗喂狗
	PM001V20_SysLed();					//系统运行指示灯
	
	USART_Server();
	Driver_Server();
	CAN_Server();
}
/*******************************************************************************
* 函数名		:	
* 功能描述	:	 
* 输入		:	
* 输出		:
* 返回 		:
*******************************************************************************/
void CAN_Server(void)
{	
	u8 num	=	0;
#if master
	num	=	CAN_RX_DATA(&RxMessage);								//检查CAN接收有无数据
	if(num)
	{
		char *p	=	"can数据";
		memcpy(rxBuffer,p,8);
//		rxBuffer[0]+=1;
		CAN_StdTX_DATA(1,8,rxBuffer);			//CAN使用标准帧发送数据
	}
#else
	num	=	CAN_RX_DATA(&RxMessage);								//检查CAN接收有无数据
	if(num)
	{
		num	=	RxMessage.DLC;
		if(num)
		{
			memcpy(rxBuffer,RxMessage.Data,num);
			USART_DMASendList(USART1,rxBuffer,num);		//自定义printf串口DMA发送程序
		}
	}
#endif
}
/*******************************************************************************
* 函数名			:	function
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
*******************************************************************************/
void PM001V20_SysLed(void)
{
	if(sysledcnt++>=1000)			//系统运行指示灯扫描计数  0.5秒
	{
		sysledcnt=0;
		GPIO_Toggle	(GPIOC,GPIO_Pin_0);		//SysLed//将GPIO相应管脚输出翻转----V20170605
		if(bpflg)
		GPIO_Toggle	(GPIOC,GPIO_Pin_1);		//BUZZER//将GPIO相应管脚输出翻转----V20170605
	}
}
/*******************************************************************************
* 函数名			:	function
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
*******************************************************************************/
void USART_Configuration(void)
{
	//=============================DB9-USART1配置
	USART_DMA_ConfigurationNR(USART1,115200,BufferSize);	//USART_DMA配置
	//=============================RS485A(BUS1)-USART2配置
	RS485A.USARTx	=	USART2;
	RS485A.RS485_CTL_PORT	=	GPIOA;
	RS485A.RS485_CTL_Pin	=	GPIO_Pin_1;
	RS485_DMA_ConfigurationNR(&RS485A,19200,BufferSize);	//USART_DMA配置--查询方式，不开中断,配置完默认为接收状态
	//=============================RS485B(BUS2)-USART3配置
	RS485B.USARTx	=	USART3;
	RS485B.RS485_CTL_PORT	=	GPIOB;
	RS485B.RS485_CTL_Pin	=	GPIO_Pin_1;
	RS485_DMA_ConfigurationNR(&RS485B,19200,BufferSize);	//USART_DMA配置--查询方式，不开中断,配置完默认为接收状态	
}
/*******************************************************************************
* 函数名			:	function
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
*******************************************************************************/
void Driver_Configuration(void)
{
	//=============================系统运行指示灯配置
	GPIO_Configuration_OOD2	(GPIOC,GPIO_Pin_0);			//SysLed//将GPIO相应管脚配置为OD(开漏)输出模式，最大速度2MHz----V20170605
	//=============================蜂鸣器配置
	GPIO_Configuration_OPP2	(GPIOC,GPIO_Pin_1);			//BUZZER//将GPIO相应管脚配置为OD(开漏)输出模式，最大速度2MHz----V20170605
	//=============================Dout1配置
	GPIO_Configuration_OPP50	(GPIOC,GPIO_Pin_6);			
	//=============================Dout2配置
	GPIO_Configuration_OPP50	(GPIOC,GPIO_Pin_7);	
	//=============================Dout3配置
	GPIO_Configuration_OPP50	(GPIOC,GPIO_Pin_8);	
	//=============================Dout4配置
	GPIO_Configuration_OPP50	(GPIOC,GPIO_Pin_9);	
	//=============================Sin1配置
	GPIO_Configuration_IPU(GPIOB,GPIO_Pin_12);
	//=============================Sin2配置
	GPIO_Configuration_IPU(GPIOB,GPIO_Pin_13);
	//=============================Sin3配置
	GPIO_Configuration_IPU(GPIOB,GPIO_Pin_14);
	//=============================Sin4配置
	GPIO_Configuration_IPU(GPIOB,GPIO_Pin_15);
}
/*******************************************************************************
* 函数名			:	function
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
*******************************************************************************/
void Driver_Server(void)
{
	if(sysledcnt++>=1000)			//系统运行指示灯扫描计数  0.5秒
	{
		sysledcnt=0;
		GPIO_Toggle	(GPIOC,GPIO_Pin_0);		//SysLed//将GPIO相应管脚输出翻转----V20170605
		if(bpflg)
		GPIO_Toggle	(GPIOC,GPIO_Pin_1);		//BUZZER//将GPIO相应管脚输出翻转----V20170605
		
		GPIO_Toggle	(GPIOC,GPIO_Pin_6);
		GPIO_Toggle	(GPIOC,GPIO_Pin_7);
		GPIO_Toggle	(GPIOC,GPIO_Pin_8);
		GPIO_Toggle	(GPIOC,GPIO_Pin_9);
	}
	if(sysledcnt%100!=0)
	{
		return;
	}
	if(0==PB12in)
	{
		USART_DMAPrintfList(USART1,"传感器输入1\r\n");
	}
	if(0==PB13in)
	{
		USART_DMAPrintfList(USART1,"传感器输入2\r\n");
	}
	if(0==PB14in)
	{
		USART_DMAPrintfList(USART1,"传感器输入3\r\n");
	}
	if(1==PB15in)
	{
		USART_DMAPrintfList(USART1,"传感器输入4\r\n");
	}
	
}
/*******************************************************************************
* 函数名			:	function
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
*******************************************************************************/
void USART_Server(void)
{
	u32 num=0;
	//=============================DB9-USART1服务
	num	=	USART_ReadBufferIDLE(USART1,rxBuffer);
	if(num)
	{
		if(num==1)
		{
			if(rxBuffer[0]==0xFA)
			{
				bpflg=1;	//蜂鸣器使能标志
			}
			else if(rxBuffer[0]==0xFB)
			{
				bpflg=0;	//蜂鸣器使能标志
				GPIO_WriteBit(GPIOC,GPIO_Pin_1,Bit_RESET);			//将相应GPIO管脚输出为高
			}
			return;
		}
		if(0x01	==	rxBuffer[0])
		{
			RS485_DMASend(&RS485A,rxBuffer,num);
		}
		else if(0x02	==	rxBuffer[0])
		{
			RS485_DMASend(&RS485B,rxBuffer,num);
		}
		else if(0x03	==	rxBuffer[0])
		{
			CAN_StdTX_DATA(1,8,rxBuffer);			//CAN使用标准帧发送数据
		}
		else
		{
			memset(rxBuffer,0x03,num);
			USART_DMASendList(USART1,rxBuffer,num);		//自定义printf串口DMA发送程序
		}
	}
	//=============================RS485A(BUS1)-USART2服务
	num	=	RS485_ReadBufferIDLE(&RS485A,rxBuffer);
	if(num)
	{	
		USART_DMASendList(USART1,rxBuffer,num);		//自定义printf串口DMA发送程序
	}
	//=============================RS485B(BUS2)-USART3服务
	num	=	RS485_ReadBufferIDLE(&RS485B,rxBuffer);
	if(num)
	{	
		USART_DMASendList(USART1,rxBuffer,num);		//自定义printf串口DMA发送程序
	}	
	
}
#endif
