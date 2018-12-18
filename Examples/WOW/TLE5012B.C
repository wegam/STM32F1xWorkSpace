#ifdef TLE5012B

#include "TLE5012B.H"

#include "string.h"				//串和内存操作函数头文件
//#include "stm32f10x_dma.h"



#include "STM32F10x_BitBand.H"
#include "STM32_GPIO.H"
#include "STM32_SYS.H"
#include "STM32_SYSTICK.H"
#include "STM32_WDG.H"
#include "STM32_PWM.H"
#include "STM32_USART.H"
#include "STM32_SPI.H"
#include "STM32_MCO.H"

#include "TM1616.H"

#include 	"CRC.H"


RS485Def stRS485BS;   //usart2,pB11 PB10
TM1616Def	Seg1,Seg2;
SPIDef	TLE5012;


#define ussize  128     //串口缓存大小
unsigned char u1txbuffer[ussize];
unsigned char u1rxbuffer[ussize];
unsigned char u2txbuffer[ussize];
unsigned char u2rxbuffer[ussize];


char	cwflg	=	0;
char	runflg	=	0;
unsigned	short organgle	=	0;
signed	short cmpgangle	=	0;
unsigned	short angle1	=	0;
unsigned	short angle2	=	0;
unsigned	short anglecount	=	0;
unsigned	short	Speed	=	0;


unsigned	short time	=	0;
unsigned	short dstime	=	0;
unsigned  short seril	=	0;
//=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>
//->函数名		:	
//->功能描述	:	 
//->输入		:	
//->输出		:
//->返回 		:
//<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=
void TLE5012B_Configuration(void)
{	
  RCC_ClocksTypeDef RCC_ClocksStatus;							//时钟状态---时钟值
	SYS_Configuration();					//系统配置---打开系统时钟 STM32_SYS.H	

  COMM_Configuration();  
  
	Seg_Configuration();
	
	MCO_Initialize();
	
	//hw_configuration();
	SPI5012B_Init();
	
	GPIO_Configuration_OPP50(GPIOB,GPIO_Pin_6);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605
	GPIO_Configuration_OPP50(GPIOB,GPIO_Pin_7);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605
	
	PWM_OUT(TIM2,PWM_OUTChannel1,2,300);						//PWM设定-20161127版本
	
//  IWDG_Configuration(1000);													//独立看门狗配置---参数单位ms
	SysTick_DeleymS(1000);				//SysTick延时nmS
	for(time=0;time<20;time++)
	organgle	=	ReadAngle();
	SysTick_DeleymS(200);				//SysTick延时nmS
  SysTick_Configuration(1000);    //系统嘀嗒时钟配置72MHz,单位为uS
	while(1)
	{
		MOTORT();
	}
}

//=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>
//->函数名		:	
//->功能描述	:	 
//->输入		:	
//->输出		:
//->返回 		:
//<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=
void TLE5012B_Server(void)
{
	if(time++>8000)
	{		
		time	=	0;
	}
	if(0	==	time)
	{
		
		angle1	=	ReadAngle();
		angle1	=	ReadAngle();
		angle2	=	angle1;
		
		cwflg	=	1;
//		anglecount	=	0;
	}
	else if(4000	==	time)
	{
		
		angle1	=	ReadAngle();
		angle1	=	ReadAngle();
		angle2	=	angle1;
		
		cwflg	=	1;
//		anglecount	=	0;
	}
	else if(8000<time)
	{
		cwflg	=	0;
	}
	if(dstime++>100)
	{
//		unsigned	short temp	=	0;
//		dstime=0;
//		TM1616_Display(&Seg1,angle1);
//		if(cmpgangle<0)
//			cmpgangle=0-cmpgangle;
//		TM1616_Display(&Seg2,anglecount);
		displaycount(anglecount);
	}
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
void MOTORT(void)
{	
	if(0==cwflg)
	{
//		MSTP();
//		return;
	}
	angle2	=	ReadAngle();
	if(angle2>angle1)
	{
		if(angle2-angle1>350)
		{
			anglecount+=360-angle2+angle1;
		}
		else if((angle2-angle1>1))
		{
			anglecount	+=	(angle2-angle1);
		}
	}
	else
	{
		if(angle1-angle2>350)
		{
			anglecount+=360-angle1+angle2;
		}
		else if((angle1-angle2>1))
		{
			anglecount	+=	(angle1-angle2);
		}
	}
	if(angle1	!=	angle2)
	angle1	=	angle2;

	MCW();
	
//	if(cwflg==1)		//正转
//	{		
//		if(anglecount>320)
//		{
//			cwflg		=	0;
//			runflg	=	0;
//			MSTP();
//			return;
//		}
//		else
//		{
//			MCW();
//		}
//	}
//	else if(cwflg==2)	//反转
//	{
//		if(anglecount>320)
//		{
//			cwflg		=	0;
//			runflg	=	0;
//			MSTP();
//			return;
//		}
//		else
//		{
//			MCCW();
//		}
//	}

//	else
//	{
////	cmpgangle	=	angle2-organgle;
////	if((angle2>-30)&&(cmpgangle<30))
////	{
////		MSTP();
////	}
////	else if(cmpgangle<-30)
////	{
////		MCW();
////	}
////	else
////	{
////		MCCW();
////	}
////	return;
////		if(organgle>angle2)
////			temp	=	organgle-angle2;
////		else
////			temp	=	angle2-organgle;
//		
//		if(angle2<40||angle2>320)
//		{
//			MSTP();
//		}
//		else if((angle2<=320)&&(angle2>180))
//		{
//			MCW();
//		}
//		else
//		{
//			MCCW();
//		}
//	}
}
//=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>
//->函数名		:	
//->功能描述	:	 
//->输入		:	
//->输出		:
//->返回 		:
//<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=
void USART_Server(void)
{
  unsigned short RxNum  = 0;
  unsigned char str[]="串口接收到数据\r\n";
  RxNum = USART_ReadBufferIDLE(USART1,u1rxbuffer);
  if(RxNum)
  {
    memcpy(u1txbuffer,str,sizeof(str));
    memcpy(u2txbuffer,u1rxbuffer,RxNum);

    
    USART_DMASend(USART1,u1txbuffer,sizeof(str)-1);		//串口DMA发送程序，如果数据已经传入到DMA，返回Buffer大小，否则返回0
    
    RS485_DMASend(&stRS485BS,u2txbuffer,RxNum);

  }
  RxNum = RS485_ReadBufferIDLE(&stRS485BS,u2rxbuffer);
  if(RxNum)
  {
    memcpy(u1txbuffer,u2rxbuffer,RxNum);
    USART_DMASend(USART1,u1txbuffer,RxNum);
  }
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
void hw_configuration(void)
{
	TLE5012.Port.SPIx	=	SPI1;
	TLE5012.Port.CS_PORT	=	GPIOA;
	TLE5012.Port.CS_Pin		=	GPIO_Pin_4;
	
	TLE5012.Port.SPI_BaudRatePrescaler_x	=	SPI_BaudRatePrescaler_8;
	
	SPI_Initialize(&TLE5012);
	MCO_Initialize();
}
//=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>=>
//->函数名		:	
//->功能描述	:	 
//->输入		:	
//->输出		:
//->返回 		:
//<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=<=
void COMM_Configuration(void)
{
  unsigned short RxNum  = 0;
  USART_DMA_ConfigurationNR	(USART1,115200,ussize);	//USART_DMA配置--查询方式，不开中断

  //-----------------------------总线接口485
  stRS485BS.USARTx  = USART2;
  stRS485BS.RS485_CTL_PORT  = GPIOB;
  stRS485BS.RS485_CTL_Pin   = GPIO_Pin_11;
  RS485_DMA_ConfigurationNR			(&stRS485BS,19200,ussize);	//USART_DMA配置--查询方式，不开中断,配置完默认为接收状态
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
void Seg_Configuration(void)
{
	Seg1.STB_PORT	=	GPIOB;
	Seg1.STB_Pin	=	GPIO_Pin_12;
	
	Seg1.DIO_PORT	=	GPIOB;
	Seg1.DIO_Pin	=	GPIO_Pin_15;
	
	Seg1.CLK_PORT	=	GPIOB;
	Seg1.CLK_Pin	=	GPIO_Pin_13;
	
	Seg2.STB_PORT	=	GPIOB;
	Seg2.STB_Pin	=	GPIO_Pin_2;
	
	Seg2.DIO_PORT	=	GPIOB;
	Seg2.DIO_Pin	=	GPIO_Pin_15;
	
	Seg2.CLK_PORT	=	GPIOB;
	Seg2.CLK_Pin	=	GPIO_Pin_13;
	
	TM1616_Initialize(&Seg1);
	TM1616_Initialize(&Seg2);
}


//得到 0~359 度
unsigned short ReadAngle(void)
{
	return ( ReadValue(READ_ANGLE_VALUE) * 360 / 0x10000 );
}

//得到角速度
unsigned short ReadSpeed(void)
{
	return ReadValue(READ_SPEED_VALUE);
}


unsigned short ReadValue(unsigned short u16RegValue)
{
	unsigned short u16Data;
	unsigned short i	=	5;
	SPI_CS_ENABLE;
	
	SPIx_ReadWriteByte(u16RegValue);
  SPI_TX_OFF;
//	while(i--);
	//发送 0xFFFF 是无用的，可能是为了有时钟
	u16Data = ( SPIx_ReadWriteByte(0xffff) & 0x7FFF ) << 1;//0x12/0xff*100k
	
	SPI_CS_DISABLE;
  SPI_TX_ON;
	
	return(u16Data);
}

unsigned short SPIx_ReadWriteByte(unsigned short byte)
{
	unsigned short retry = 0;
	while( (SPI1->SR&1<<1) == 0 )//发送缓冲区非空
	{
		if( ++retry > 200 )
			return 0;//延迟一段时间后返回
	}
	SPI1->DR = byte;     //发送数据
	
	retry = 0;
	while( (SPI1->SR&1<<0) == 0 ) //接收缓冲区为空
	{
		if( ++retry > 200 )
			return 0;//延迟一段时间后返回
	}
	return SPI1->DR;          //读一下缓冲区，清标志
}
void SPI5012B_Init(void)
{
	SPI_InitTypeDef  SPI_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_SPI1,ENABLE );
	
	//以下二句，在它处声明，请增加使用
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO,ENABLE);
	//GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable,ENABLE);//使JTDO、JTDI、JTCK 当成普通IO口进行操作
	//GPIOB0 当成普通IO口进行操作
	
	/*SPI: NSS,SCK,MISO and MOSI */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;//PA5--CLK--复用推挽
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//GPIO_StructInit(&GPIO_InitStructure);
	
	/* Configure PA6 as encoder input */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;//PA6--MISO--输入
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	/* PA7*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//PA7--MOSI--推挽输出
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_CS_Pin_Name;//PB0--CS--推挽输出
	GPIO_Init(GPIO_CS_Pin_Type, &GPIO_InitStructure);
	
	/**********SPI****************/
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;//SPI1--双线全双工！！
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_16b;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_CRCPolynomial = 7;
	
	SPI_Init(SPI1, &SPI_InitStructure);
	SPI_Cmd(SPI1, ENABLE);
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
void MCW(void)
{
	PB6	=	0;
	PB7	=	1;
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
void MCCW(void)
{
	PB6	=	1;
	PB7	=	0;
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
void MSTP(void)
{
	PB6	=	0;
	PB7	=	0;
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
void displaycount(unsigned long count)
{
	TM1616_Display(&Seg1,count/10000);
	TM1616_Display(&Seg2,count%10000);
}
#endif
