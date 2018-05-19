/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : PC001V21.c
* Author             : WOW
* Version            : V2.0.1
* Date               : 06/26/2017
* Description        : PC001V21层控制板.
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

#ifdef PD010V20			//二路电机控制板

#include "PD010V20.H"


u32 RunTime	=	0;

unsigned short	TextSize	=	0;

PD010Def	PD010V20S;


//===============================================================================
//函数:	PD008V11_Configuration
//描述:	缓存架主配置程序
//返回:
//===============================================================================
void PD010V20_Configuration(void)
{
	SYS_Configuration();							//系统配置系统运行时钟72M	

	GPIO_DeInitAll();									//将所有的GPIO关闭----V20170605
	
//	Sensor_Configuration();	
//	Switch_Configuration();	
//	Pmos_Configuration();	
//	Motor_Configuration();	
//	RS485_Configuration();	
//	RS232_Configuration();	
//	CAN_Configuration();
	FLASH_Configuration();
	SysTick_Configuration(1000);			//系统嘀嗒时钟配置72MHz,单位为uS----软件运行以定时扫描模式,定时时间为SysTickTime	
//	IWDG_Configuration(1000);					//独立看门狗配置	Tout-超时复位时间，单位ms	
	PWM_OUT(TIM2,PWM_OUTChannel1,1,900);			//系统运行LED灯 频率1HZ,占空比500/1000
}

//===============================================================================
//函数:	PD008V11_Server
//描述:	缓存架主服务程序
//返回:
//===============================================================================
void PD010V20_Server(void)
{
	IWDG_Feed();						//独立看门狗喂狗

	if(RunTime++>2000)
	{
		RunTime=0;
		FLASH_Server();
	}
//	Sensor_Server();
//	Switch_Server();
//	Pmos_Server();
//	Motor_Server();
//	RS485_Server();
//	RS232_Server();
//	CAN_Server();
//	SPI_Server();
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
void FLASH_Configuration(void)
{
	unsigned char temp	=	0x03;
	SPIDef		*SPIx	=	&(PD010V20S.MX25Lx.SPIFlash.SPI);

	SPIx->Port.SPIx=SPI1;
	SPIx->Port.SPI_BaudRatePrescaler_x=SPI_BaudRatePrescaler_64;

	SPIx->Port.CS_PORT	=	GPIOA;
	SPIx->Port.CS_Pin		=	GPIO_Pin_4;
	
	SPIx->Port.CLK_PORT	=	GPIOA;
	SPIx->Port.CLK_Pin	=	GPIO_Pin_5;
	
	SPIx->Port.MISO_PORT	=	GPIOA;
	SPIx->Port.MISO_Pin		=	GPIO_Pin_6;
	
	SPIx->Port.MOSI_PORT	=	GPIOA;
	SPIx->Port.MOSI_Pin		=	GPIO_Pin_7;
	
	memcpy((unsigned char*)&PD010V20S.MX25Lx.SPIFlash.Flag,&temp,1);
	MX25L4006E_Initialize(&PD010V20S.MX25Lx);
//	SPI_InitializeNR(&PD010V20S.SPI);
//	SPI_Initialize(SPIx);
//	GPIO_Configuration_OPP50	(Port->CS_PORT,				Port->CS_PIN);					//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605
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
void FLASH_Server(void)
{
	u8 Buffer[256]	=	{0};
//	GPIO_ResetBits(GPIOA,GPIO_Pin_4);
//	SPI_ReadWriteByteNR(SPI1,0XAA);
//	SPI_ReadWriteByteNR(SPI1,0X55);
//	GPIO_SetBits(GPIOA,GPIO_Pin_4);
//	SPI_CS_LOW();
//	SPI_Cmd(SPI1, ENABLE);
//	SPI_ReadWriteByteSPI(SPI1,0XAA);
//	SPI_ReadWriteByteSPI(SPI1,0X55);
//	SPI_Cmd(SPI1, DISABLE);
//	SPI_CS_HIGH;
//	SPI_FLASH_WriteEnable();
//	SPI_FLASH_WaitForWriteEnd();
//	SPI_FLASH_ReadID();
//	SPI_FLASH_ReadREMS();
	SPI_FLASH_SetDeepPowerdown();		//进入深度省电模式
	SPI_FLASH_ResDeepPowerdown();		//退出深度省电模式
	SPI_FLASH_ReadREMS();						//读制造商信息和ID
	SPI_FLASH_ReadRDSFDP();					//读(SFDP)Serial Flash芯片规范
	SPI_FLASH_ReadStatusRegister();	//读状态寄存器
//	SPI_FLASH_ChipErase();					//整片擦除
	SPI_FLASH_BufferRead(Buffer, 0x00, 256);
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
void Sensor_Configuration(void)
{
	unsigned char 	Num	=	0;
	unsigned char 	i		=	0;
	
	unsigned short	SwitchID	=	0;
	
	unsigned long		*Port;
	unsigned long 	*Pin;					//GPIO_Pin_x	
	
	SwitchID	=	PD010V20S.Board.SwitchID;
	
	Port	=	(unsigned long*)&(PD010V20S.Sensor.Sen1_PORT);
	Pin	=	(unsigned long*)&(PD010V20S.Sensor.Sen1_Pin);					//GPIO_Pin_x
	
	PD010V20S.Sensor.Num	=	8;
	Num	=	PD010V20S.Sensor.Num;	
	
	PD010V20S.Sensor.Sen1_PORT	=	GPIOC;
	PD010V20S.Sensor.Sen1_Pin		=	GPIO_Pin_0;
	
	PD010V20S.Sensor.Sen2_PORT	=	GPIOC;
	PD010V20S.Sensor.Sen2_Pin		=	GPIO_Pin_1;
	
	PD010V20S.Sensor.Sen3_PORT	=	GPIOC;
	PD010V20S.Sensor.Sen3_Pin		=	GPIO_Pin_2;
	
	PD010V20S.Sensor.Sen4_PORT	=	GPIOC;
	PD010V20S.Sensor.Sen4_Pin		=	GPIO_Pin_3;
	
	PD010V20S.Sensor.Sen5_PORT	=	GPIOC;
	PD010V20S.Sensor.Sen5_Pin		=	GPIO_Pin_4;
	
	PD010V20S.Sensor.Sen6_PORT	=	GPIOB;
	PD010V20S.Sensor.Sen6_Pin		=	GPIO_Pin_0;
	
	PD010V20S.Sensor.Sen7_PORT	=	GPIOB;
	PD010V20S.Sensor.Sen7_Pin		=	GPIO_Pin_1;
	
	PD010V20S.Sensor.Sen8_PORT	=	GPIOC;
	PD010V20S.Sensor.Sen8_Pin		=	GPIO_Pin_5;

	PD010V20S.Sensor.Time	=	0;
	
	for(i	=	0;i<Num;i++)
	{
		if(SwitchID	==	0x00)
		{
			GPIO_Configuration_OPP50	((GPIO_TypeDef*)(*Port), (unsigned short)*Pin);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605
			GPIO_SetBits((GPIO_TypeDef*)(*Port), (unsigned short)*Pin);
		}
		else
		{
			GPIO_Configuration_IPU	((GPIO_TypeDef*)(*Port), (unsigned short)*Pin);			//将GPIO相应管脚配置为上拉输入模式----V20170605
		}
		Port	+=	2;
		Pin		+=	2;
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
void Switch_Configuration(void)
{
	unsigned char Num	=	6;
	unsigned char i	=	0;
	
	unsigned long		*Port;
	unsigned long 	*Pin;					//GPIO_Pin_x
	
	Port	=	(unsigned long*)&(PD010V20S.Switch.SW1_PORT);
	Pin	=	(unsigned long*)&(PD010V20S.Switch.SW1_Pin);					//GPIO_Pin_x
	
	PD010V20S.Switch.NumOfSW	=	6;
	
	PD010V20S.Switch.SW1_PORT	=	GPIOB;
	PD010V20S.Switch.SW1_Pin	=	GPIO_Pin_15;
	
	PD010V20S.Switch.SW2_PORT	=	GPIOC;
	PD010V20S.Switch.SW2_Pin	=	GPIO_Pin_6;
	
	PD010V20S.Switch.SW3_PORT	=	GPIOC;
	PD010V20S.Switch.SW3_Pin	=	GPIO_Pin_7;
	
	PD010V20S.Switch.SW4_PORT	=	GPIOC;
	PD010V20S.Switch.SW4_Pin	=	GPIO_Pin_8;
	
	PD010V20S.Switch.SW5_PORT	=	GPIOC;
	PD010V20S.Switch.SW5_Pin	=	GPIO_Pin_9;
	
	PD010V20S.Switch.SW6_PORT	=	GPIOA;
	PD010V20S.Switch.SW6_Pin	=	GPIO_Pin_8;
	
	SwitchIdInitialize(&(PD010V20S.Switch));
	SWITCHID_Read(&(PD010V20S.Switch));
	
	for(i	=	0;i<Num;i++)
	{
		GPIO_Configuration_IPU	((GPIO_TypeDef*)(*Port), (unsigned short)*Pin);			//将GPIO相应管脚配置为上拉输入模式----V20170605
		Port	+=	sizeof(&(PD010V20S.Switch.SW1_PORT))/4+sizeof(&(PD010V20S.Switch.SW1_Pin))/4;
		Pin	+=	sizeof(&(PD010V20S.Switch.SW1_PORT))/4+sizeof(&(PD010V20S.Switch.SW1_Pin))/4;
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
void Pmos_Configuration(void)
{
	unsigned char 	Num		=	4;
	unsigned char 	i			=	0;
	
	unsigned long		*Port;
	unsigned long 	*Pin;					//GPIO_Pin_x
	
	Port	=	(unsigned long*)&(PD010V20S.Pmos.P1_PORT);
	Pin		=	(unsigned long*)&(PD010V20S.Pmos.P1_Pin);					//GPIO_Pin_x
	
	PD010V20S.Pmos.P1_PORT	=	GPIOB;
	PD010V20S.Pmos.P1_Pin		=	GPIO_Pin_3;
	
	PD010V20S.Pmos.P2_PORT	=	GPIOB;
	PD010V20S.Pmos.P2_Pin		=	GPIO_Pin_4;
	
	PD010V20S.Pmos.P3_PORT	=	GPIOB;
	PD010V20S.Pmos.P3_Pin		=	GPIO_Pin_5;
	
	PD010V20S.Pmos.P4_PORT	=	GPIOB;
	PD010V20S.Pmos.P4_Pin		=	GPIO_Pin_6;
	
	PD010V20S.Pmos.Num	=	0;
	PD010V20S.Pmos.Time	=	0;
	
	for(i	=	0;i<Num;i++)
	{		
		GPIO_Configuration_OPP50((GPIO_TypeDef*)(*Port), (unsigned short)*Pin);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605
		GPIO_ResetBits((GPIO_TypeDef*)(*Port), (unsigned short)*Pin);
		Port	+=	2;
		Pin		+=	2;
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
void Motor_Configuration(void)
{
		unsigned char Num	=	3;
	unsigned char i	=	0;
	
	unsigned long		*Port;
	unsigned long 	*Pin;					//GPIO_Pin_x
	
	Port	=	(unsigned long*)&(PD010V20S.Motor1.DIR_PORT);
	Pin	=	(unsigned long*)&(PD010V20S.Motor1.DIR_Pin);					//GPIO_Pin_x
	
	PD010V20S.Motor1.DIR_PORT	=	GPIOA;
	PD010V20S.Motor1.DIR_Pin	=	GPIO_Pin_15;
	
	PD010V20S.Motor1.PUL_PORT	=	GPIOB;
	PD010V20S.Motor1.PUL_Pin	=	GPIO_Pin_14;
	
	PD010V20S.Motor1.EN_PORT	=	GPIOC;
	PD010V20S.Motor1.EN_Pin		=	GPIO_Pin_12;
	
	PD010V20S.Motor1.Time	=	0;
	
	for(i	=	0;i<Num;i++)
	{
		GPIO_Configuration_OPP50	((GPIO_TypeDef*)(*Port), (unsigned short)*Pin);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605
		Port	+=	2;
		Pin		+=	2;
	}
	
	Port	=	(unsigned long*)&(PD010V20S.Motor2.DIR_PORT);
	Pin	=	(unsigned long*)&(PD010V20S.Motor2.DIR_Pin);					//GPIO_Pin_x
	
	PD010V20S.Motor2.DIR_PORT	=	GPIOB;
	PD010V20S.Motor2.DIR_Pin	=	GPIO_Pin_12;
	
	PD010V20S.Motor2.PUL_PORT	=	GPIOA;
	PD010V20S.Motor2.PUL_Pin	=	GPIO_Pin_1;
	
	PD010V20S.Motor2.EN_PORT	=	GPIOB;
	PD010V20S.Motor2.EN_Pin		=	GPIO_Pin_13;
	
	PD010V20S.Motor2.Time	=	0;
	
	for(i	=	0;i<Num;i++)
	{
		GPIO_Configuration_OPP50	((GPIO_TypeDef*)(*Port), (unsigned short)*Pin);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605
		Port	+=	2;
		Pin		+=	2;
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
void RS485_Configuration(void)
{
	unsigned long BaudRate	=	0;
	unsigned char *RxdB	=	NULL;
	RS485_TypeDef *RS485_Info	=	NULL;
	
	//-------------------------RS485通道1配置
	PD010V20S.RS485A.BaudRate									=	19200;	
	PD010V20S.RS485A.RS485Cof.USARTx					=	USART1;
	PD010V20S.RS485A.RS485Cof.RS485_CTL_PORT	=	GPIOB;
	PD010V20S.RS485A.RS485Cof.RS485_CTL_Pin		=	GPIO_Pin_7;
	
	BaudRate		=	PD010V20S.RS485A.BaudRate;
	RxdB				=	PD010V20S.RS485A.RxdBuffer;
	RS485_Info	=	&(PD010V20S.RS485A.RS485Cof);
	RS485_DMA_ConfigurationNR	(RS485_Info,BaudRate,(u32*)RxdB,USARTBufferSize);	//USART_DMA配置--查询方式，不开中断,配置完默认为接收状态
	
	//-------------------------RS485通道2配置
	PD010V20S.RS485B.BaudRate									=	19200;	
	PD010V20S.RS485B.RS485Cof.USARTx					=	UART4;
	PD010V20S.RS485B.RS485Cof.RS485_CTL_PORT	=	GPIOB;
	PD010V20S.RS485B.RS485Cof.RS485_CTL_Pin		=	GPIO_Pin_9;
	
	BaudRate		=	PD010V20S.RS485B.BaudRate;
	RxdB				=	PD010V20S.RS485B.RxdBuffer;
	RS485_Info	=	&(PD010V20S.RS485B.RS485Cof);
	RS485_DMA_ConfigurationNR	(RS485_Info,BaudRate,(u32*)RxdB,USARTBufferSize);	//USART_DMA配置--查询方式，不开中断,配置完默认为接收状态
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
void RS232_Configuration(void)
{
	unsigned long BaudRate	=	0;
	unsigned char *RxdB	=	NULL;
	USART_TypeDef* USARTx	=	NULL;
	
	//-------------------------RS232通道1配置
	PD010V20S.RS232A.BaudRate	=	19200;
	PD010V20S.RS232A.USARTx		=	USART2;
	
	BaudRate	=	PD010V20S.RS232A.BaudRate;
	RxdB			=	PD010V20S.RS232A.RxdBuffer;
	USARTx		=	PD010V20S.RS232A.USARTx;
	USART_DMA_ConfigurationNR	(USARTx,BaudRate,(u32*)RxdB,USARTBufferSize);	//USART_DMA配置--查询方式，不开中断
	
	//-------------------------RS232通道2配置
	PD010V20S.RS232B.BaudRate	=	19200;
	PD010V20S.RS232B.USARTx		=	USART3;
	
	BaudRate	=	PD010V20S.RS232B.BaudRate;
	RxdB			=	PD010V20S.RS232B.RxdBuffer;
	USARTx		=	PD010V20S.RS232B.USARTx;
	USART_DMA_ConfigurationNR	(USARTx,BaudRate,(u32*)RxdB,USARTBufferSize);	//USART_DMA配置--查询方式，不开中断
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
void CAN_Configuration(void)
{
	unsigned short	CANID			=	0;
	unsigned long		BaudRate	=	0;
	
	PD010V20S.CANBUS.BaudRate	=	50000;
	
	BaudRate	=	PD010V20S.CANBUS.BaudRate;
	CANID			=	(PD010V20S.Switch.nSWITCHID)&0xFFFF;
	
	CAN_Configuration_NR(BaudRate);		//CAN1配置---标志位查询方式，不开中断
	//---------------滤波器组01：通用广播帧
	CAN_FilterInitConfiguration_StdData(0x01,0x00,0xFFFF);		//CAN滤波器配置---标准数据帧模式
	//---------------滤波器组02：专用滤波器组
	CAN_FilterInitConfiguration_StdData(0x02,CANID,0xFFFF);		//CAN滤波器配置---标准数据帧模式
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
void Sensor_Server(void)
{
	unsigned short	SwitchID	=	0;
	
	SwitchID	=	PD010V20S.Board.SwitchID;
	
	if(SwitchID	==	0x00)		//未拨码--测试模式
	{
		unsigned long		Time			=	0;
		unsigned long		*Port			=	NULL;
		unsigned long 	*Pin			=	NULL;					//GPIO_Pin_x
		
		Time			=	(unsigned short)((PD010V20S.Sensor.Num)*100);
		
		Port	=	(unsigned long*)&(PD010V20S.Sensor.Sen1_PORT);
		Pin		=	(unsigned long*)&(PD010V20S.Sensor.Sen1_Pin);					//GPIO_Pin_x
		
		if((PD010V20S.Sensor.Time)%Time	==	0)
		{
			PD010V20S.Sensor.Time	=	0;
		}
		if((PD010V20S.Sensor.Time)%100	==	0)
		{
			unsigned char	Num	=	0;
			Num	=	PD010V20S.Sensor.Time	/	100;
			
			Port	=	Port	+	(unsigned long)(Num*2);
			Pin		=	Pin		+	(unsigned long)(Num*2);
			GPIO_Toggle	((GPIO_TypeDef*)(*Port), ((unsigned short)*Pin));		//将GPIO相应管脚输出翻转----V20170605
		}
		PD010V20S.Sensor.Time++;
		return;			//退出
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
void Switch_Server(void)
{
	unsigned short	SwitchID	=	0;
	SwitchID	=	SWITCHID_Read(&(PD010V20S.Switch));
	if(PD010V20S.Board.SwitchID	!=	SwitchID)
	{
		PD010V20S.Board.SwitchID	=	SwitchID;
		PD010V20_Configuration();								//拨码变化，重新配置整板
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
void Pmos_Server(void)
{	
	unsigned short	SwitchID	=	0;
	unsigned long		*Port			=	NULL;
	unsigned long 	*Pin			=	NULL;					//GPIO_Pin_x
	
	SwitchID	=	PD010V20S.Board.SwitchID;
	
	if(SwitchID	==	0x00)		//未拨码--测试模式
	{
		Port	=	(unsigned long*)&(PD010V20S.Pmos.P1_PORT);
		Pin		=	(unsigned long*)&(PD010V20S.Pmos.P1_Pin);					//GPIO_Pin_x
		if((++PD010V20S.Pmos.Time)%200	==	0)
		{
			PD010V20S.Pmos.Time	=	0;
			Port	=	Port	+	(unsigned long)(PD010V20S.Pmos.Num*2);
			Pin		=	Pin		+	(unsigned long)(PD010V20S.Pmos.Num*2);
			GPIO_Toggle	((GPIO_TypeDef*)(*Port), ((unsigned short)*Pin));		//将GPIO相应管脚输出翻转----V20170605
			
			if(PD010V20S.Pmos.Num++>=3)
			{
				PD010V20S.Pmos.Num	=	0;
			}
		}
		return;			//退出
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
void Motor_Server(void)
{
	unsigned char	i	=	0;
	unsigned long		*Port;
	unsigned long 	*Pin;					//GPIO_Pin_x
	
	Port	=	(unsigned long*)&(PD010V20S.Motor1.DIR_PORT);
	Pin		=	(unsigned long*)&(PD010V20S.Motor1.DIR_Pin);					//GPIO_Pin_x
	if(++PD010V20S.Motor1.Time%500	==	0)
	{	
		PD010V20S.Motor1.Time	=	0;
		for(i	=	0;i<3;i++)
		{
			GPIO_Toggle	((GPIO_TypeDef*)(*Port), ((unsigned short)*Pin));		//将GPIO相应管脚输出翻转----V20170605
			Port	=	Port	+	2;
			Pin		=	Pin		+	2;
		}
	}
	Port	=	(unsigned long*)&(PD010V20S.Motor2.DIR_PORT);
	Pin		=	(unsigned long*)&(PD010V20S.Motor2.DIR_Pin);					//GPIO_Pin_x
	if(++PD010V20S.Motor2.Time%500	==	0)
	{	
		PD010V20S.Motor2.Time	=	0;
		for(i	=	0;i<3;i++)
		{
			GPIO_Toggle	((GPIO_TypeDef*)(*Port), ((unsigned short)*Pin));		//将GPIO相应管脚输出翻转----V20170605
			Port	=	Port	+	2;
			Pin		=	Pin		+	2;
		}
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
void RS485_Server(void)
{
	unsigned char 	RxNum			=	0;
	unsigned char 	*RxdB			=	NULL;
	unsigned char 	*RevB			=	NULL;
	unsigned char 	*TxdB			=	NULL;
	unsigned short	SwitchID	=	0;
	unsigned long		Time			=	0;
	RS485_TypeDef 	*RS485_Info	=	NULL;
	
	SwitchID	=	PD010V20S.Board.SwitchID;
	
	//-------------------------RS485通道1
	RxdB				=	PD010V20S.RS485A.RxdBuffer;
	RevB				=	PD010V20S.RS485A.RevBuffer;
	TxdB				=	PD010V20S.RS485A.TxdBuffer;
	RS485_Info	=	&(PD010V20S.RS485A.RS485Cof);	
	RxNum	=	RS485_ReadBufferIDLE(RS485_Info,(u32*)RevB,(u32*)RxdB);	//串口空闲模式读串口接收缓冲区，如果有数据，将数据拷贝到RevBuffer,并返回接收到的数据个数，然后重新将接收缓冲区地址指向RxdBuffer
	if(RxNum)
	{
		SysTick_DeleyuS(500);				//SysTick延时nuS
		memcpy(TxdB,RevB,RxNum);
		RS485_DMASend(RS485_Info,(u32*)TxdB,RxNum);	//RS485-DMA发送程序
	}
#if 0
//	PD010V20S.Board.Data++;
	Time	=	PD010V20S.RS485A.Time;
	if(Time%100	==0)
	{
		PD010V20S.RS485A.Time	=	0;
		RxNum	=	2;
		PD010V20S.Board.Data++;
		if(PD010V20S.Board.Data>=1000)
		{
			PD010V20S.Board.Data	=	0;
		}
		memcpy(TxdB,(unsigned char*)&PD010V20S.Board.Data,RxNum);
		RS485_DMASend(RS485_Info,(u32*)TxdB,RxNum);	//RS485-DMA发送程序
	}
	PD010V20S.RS485A.Time++;
#endif
	
#if 0
	if(SwitchID	==	0)
	{
		unsigned long		Time			=	0;
		Time	=	PD010V20S.RS485A.Time;
		if(Time%500	==	0)
		{
			PD010V20S.RS485A.Time	=0;
			RS485_DMASend(RS485_Info,(u32*)TxdB,16);	//RS485-DMA发送程序
		}
		PD010V20S.RS485A.Time	++;
	}
#endif
	
	//-------------------------RS485通道2
	RxdB				=	PD010V20S.RS485B.RxdBuffer;
	RevB				=	PD010V20S.RS485B.RevBuffer;
	TxdB				=	PD010V20S.RS485B.TxdBuffer;
	RS485_Info	=	&(PD010V20S.RS485B.RS485Cof);	
	RxNum	=	RS485_ReadBufferIDLE(RS485_Info,(u32*)RevB,(u32*)RxdB);	//串口空闲模式读串口接收缓冲区，如果有数据，将数据拷贝到RevBuffer,并返回接收到的数据个数，然后重新将接收缓冲区地址指向RxdBuffer
	if(RxNum)
	{
		SysTick_DeleyuS(500);				//SysTick延时nuS
		memcpy(TxdB,RevB,RxNum);
		RS485_DMASend(RS485_Info,(u32*)TxdB,RxNum);	//RS485-DMA发送程序
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
void RS232_Server(void)
{
	unsigned char RxNum	=	0;
	unsigned char *RxdB	=	NULL;
	unsigned char *RevB	=	NULL;
	unsigned char *TxdB	=	NULL;
	unsigned long	Time			=	0;
	USART_TypeDef* USARTx	=	NULL;
	//-------------------------RS232通道1
	RxdB				=	PD010V20S.RS232A.RxdBuffer;
	RevB				=	PD010V20S.RS232A.RevBuffer;
	TxdB				=	PD010V20S.RS232A.TxdBuffer;
	USARTx			=	PD010V20S.RS232A.USARTx;
	RxNum	=	USART_ReadBufferIDLE	(USARTx,(u32*)RevB,(u32*)RxdB);	//串口空闲模式读串口接收缓冲区，如果有数据，将数据拷贝到RevBuffer,并返回接收到的数据个数，然后重新将接收缓冲区地址指向RxdBuffer
	if(RxNum)
	{
		memcpy(TxdB,RevB,RxNum);
//		USART_DMASend(USARTx,(u32*)TxdB,RxNum);	//串口DMA发送程序
	}
#if 1
	Time	=	PD010V20S.RS232A.Time;
	if(Time%100	==	0)
	{
		unsigned char TxData[8]	=	{0x05};	
		RxNum	=	2;
		PD010V20S.RS232A.Time	=	0;
		PD010V20S.Board.Data++;
		if(PD010V20S.Board.Data>=1000)
		{
			PD010V20S.Board.Data	=	0;
		}
		memcpy(TxdB,(unsigned char*)&PD010V20S.Board.Data,RxNum);
		USART_DMASend(USARTx,(u32*)TxdB,RxNum);	//串口DMA发送程序		
	}
	PD010V20S.RS232A.Time++;
#endif
	//-------------------------RS232通道2
	RxdB				=	PD010V20S.RS232B.RxdBuffer;
	RevB				=	PD010V20S.RS232B.RevBuffer;
	TxdB				=	PD010V20S.RS232B.TxdBuffer;
	USARTx			=	PD010V20S.RS232B.USARTx;
	RxNum	=	USART_ReadBufferIDLE	(USARTx,(u32*)RevB,(u32*)RxdB);	//串口空闲模式读串口接收缓冲区，如果有数据，将数据拷贝到RevBuffer,并返回接收到的数据个数，然后重新将接收缓冲区地址指向RxdBuffer
	if(RxNum)
	{
		memcpy(TxdB,RevB,RxNum);
		USART_DMASend(USARTx,(u32*)TxdB,RxNum);	//串口DMA发送程序
	}
	#if 0
	Time	=	PD010V20S.RS232B.Time;
	if(Time%100	==	0)
	{
		unsigned char TxData[8]	=	{0x05};	
		RxNum	=	2;
		PD010V20S.RS232B.Time	=	0;
		PD010V20S.Board.Data++;
		if(PD010V20S.Board.Data>=1000)
		{
			PD010V20S.Board.Data	=	0;
		}
		memcpy(TxdB,(unsigned char*)&PD010V20S.Board.Data,RxNum);
		USART_DMASend(USARTx,(u32*)TxdB,RxNum);	//串口DMA发送程序		
	}
	PD010V20S.RS232B.Time++;
#endif


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
void CAN_Server(void)
{
	unsigned char 	RxFlg			=	0;
	unsigned short	CANID			=	0;
	unsigned short	SwitchID	=	0;
	unsigned long		Time			=	0;		
	CanRxMsg *RxMessage	=	NULL;	
	
	SwitchID	=	PD010V20S.Board.SwitchID;
	RxMessage	=	&(PD010V20S.CANBUS.RxMessage);
	
	RxFlg	=	CAN_RX_DATA(RxMessage);									//检查CAN接收有无数据
	if(RxFlg)
	{
		if(SwitchID	==	0)
		{
			unsigned char TxData[8]	=	{0};		
			CANID			=	(PD010V20S.Switch.nSWITCHID)&0xFFFF;
			CAN_StdTX_DATA(CANID,8,TxData);			//CAN使用标准帧发送数据
		}
	}
#if 0
	if(SwitchID	==	0)
	{
		unsigned char TxData[8]	=	{0x05};		
		Time	=	PD010V20S.CANBUS.Time;	
		if(Time%500	==	0)
		{
			PD010V20S.Board.Data++;
			if(PD010V20S.Board.Data>=1000)
			{
				PD010V20S.Board.Data	=	0;
			}
			TxData[0]	=	PD010V20S.Board.Data>>8;
			TxData[1]	=	PD010V20S.Board.Data&0xFF;
			PD010V20S.CANBUS.Time	=0;
			CANID			=	(PD010V20S.Switch.nSWITCHID)&0xFFFF;
			CAN_StdTX_DATA(CANID,8,TxData);			//CAN使用标准帧发送数据
		}
		PD010V20S.CANBUS.Time	++;		
	}
#endif
#if 0
		Time	=	PD010V20S.CANBUS.Time;	
		if(Time%50	==	0)
		{
			unsigned char TxData[8]	=	{0x05};	
			PD010V20S.Board.Data++;
			if(PD010V20S.Board.Data>=1000)
			{
				PD010V20S.Board.Data	=	0;
			}
			TxData[0]	=	PD010V20S.Board.Data>>8;
			TxData[1]	=	PD010V20S.Board.Data&0xFF;
			PD010V20S.CANBUS.Time	=0;
			CANID			=	(PD010V20S.Switch.nSWITCHID)&0xFFFF;
			CAN_StdTX_DATA(CANID,8,TxData);			//CAN使用标准帧发送数据
		}
		PD010V20S.CANBUS.Time	++;		
#endif
}
#endif
