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

#ifdef PL009V33HC				//智能药架称重LCD板---单称重

#include "PL009V33HC.H"

#include "HC_PHY.H"

#include "R61509V.h"
#include "CS5530.H"

#include "GT32L32M0180.H"
#include "STM32F10x_BitBand.H"
#include "STM32_GPIO.H"
#include "STM32_SYS.H"
#include "STM32_SYSTICK.H"
#include "STM32_WDG.H"
#include "STM32_PWM.H"
#include "STM32_USART.H"
#include "STM32_ADC.H"

#include "DS18B20.H"


#include "SWITCHID.H"

#include "string.h"				//串和内存操作函数头文件
#include "stdlib.h"				//串和内存操作函数头文件
#include "stm32f10x_dma.h"




#define	Master	1		//0--从机，1-主机
u16	DelayTime=0x1000;
u16	LCDTime=0;
u16	DSPTime=0;

u8 hour=23,min=15,second=40;
u16 millisecond=0;

//GT32L32Def 	GT32L32;
//char	Char_Buffer[256];		//记录format内码


RS485Def  RS485;
OneWrieDef DS18B20;
#define	Rs485Size	32
u8 RxdBuffe[Rs485Size]={0};
u8 RevBuffe[Rs485Size]={0};
u8 TxdBuffe[Rs485Size]={0};
u8 RxFlg=0;
u16 length=0;
u32	Rs485_Time	=	0;
u8	SlaveID	=	0;
u32 Rev_ADC	=	0;
u8	Rev_ID	=	0;



SwitchDef	SWITCHID;
u8 SwitchID=0;	//拔码开关地址


LCDDef	sLCD;

double	WenDubac	=	0.0;

//R61509VDef R61509V;
u8	DspFlg	=	0;

u16 BKlight	=	0;

u8 lineCH1	=	120;
u8 lineCH2	=	120;
u8 lineT	=	0;


CS5530Def CS5530CH1;
CS5530Def CS5530CH2;
u32	CS5530_Time	=	0;
u32	CS5530_ADC_CMP			=	0;
u32 CS5530_ADC_Value1		= 0xFFFFFFFF;
u32 CS5530_ADC_Value2		= 0xFFFFFFFF;
u32 CS5530_ADC_Valuebac	= 0xFFFFFFFF;

u32	WeigthARR[100]	=	{0};
u8	DspFlg1	=	0;
u32	We1	=	0;
u8	NuW	=	0;
u32	BsW	=	0;	//空重
u32 SsW	=	0;	//单重
u8	St	=	0;	//步骤
u8	SN	=	0;	//数量
u8	SNb	=	0;	//备存数量
u32 TempData	=	0;		//温度
u32 TempDataB	=	0;		//温度

u16 weighVar[20]={0};
u8	VarN	=	0;

u32 Rand	=	0;
//============LCD驱动调试变量
u16 HX	=	0;
u16	HY	=	0;
unsigned short	Color	=	0;
u8 ADCc	=	0;
u32 READ_GAIN	=	0;

u8 WriteFlag	=	0;
u16	row	=	1;
unsigned short time	=	0;

extern CommDef CommFun;
/*******************************************************************************
* 函数名		:	
* 功能描述	:	 
* 输入		:	
* 输出		:
* 返回 		:
*******************************************************************************/
void PL009V33HC_Configuration(void)
{
	SYS_Configuration();					//系统配置---打开系统时钟 STM32_SYS.H
	
	GPIO_DeInitAll();							//将所有的GPIO关闭----V20170605	
	
	SwitchID_Configuration();
	
	CS5530_Configuration();
	
	RS485_Configuration();
	
//	DS18B20_Server();
	
	USART_Configuration();
	
	SysTick_DeleymS(100);				//SysTick延时nmS
	
	LCD_Configuration();
	
	LCD_Printf(0		,0,16	,LCD565_RED,"ID:%-0.3d",SWITCHID.nSWITCHID);		//待发药槽位，后边的省略号就是可变参数
//	ADC_TempSensorConfiguration(&TempData);
	
	SysTick_Configuration(1000);	//系统嘀嗒时钟配置72MHz,单位为uS
	
	HCBoradSet(3,SWITCHID.nSWITCHID);
	
//	IWDG_Configuration(2000);			//独立看门狗配置---参数单位ms	

//	PWM_OUT(TIM2,PWM_OUTChannel1,2,500);	//PWM设定-20161127版本--运行指示灯
//	CommFun.GetDownlinkBusData  = RS485_ReadBufferIDLE;
}
/*******************************************************************************
* 函数名		:	
* 功能描述	:	 
* 输入		:	
* 输出		:
* 返回 		:
*******************************************************************************/
void PL009V33HC_Server(void)
{	
	unsigned short	tmepr=50;
	IWDG_Feed();				//独立看门狗喂狗
	RS485_Server();		//通讯管理---负责信息的接收与发送
//	LCD_Server();				//显示服务相关
	CS5530_Server();		//称重服务，AD值处理，获取稳定值
	SwitchID_Server();	//拔码开关处理--动态更新拨码地址
	tmepr	=	APIRS485ProcessData(TxdBuffe);
	if(tmepr)
	{
		HX++;
    LCD_ShowHex(0,200,16,LCD565_RED,tmepr,8,TxdBuffe);                //显示十六进制数据
		LCD_Printf(0,220,16	,LCD565_RED,"接收计数:%0.8d",HX);		//待发药槽位，后边的省略号就是可变参数
	}
}
/*******************************************************************************
* 函数名		:	
* 功能描述	:	 
* 输入		:	
* 输出		:
* 返回 		:
*******************************************************************************/
void DS18B20_Server(void)
{	
	DS18B20.Data_Port	=	GPIOC;
	DS18B20.Data_Pin	=	GPIO_Pin_11;
	DS18B20_Configuration(&DS18B20);
	DS18B20_Read(&DS18B20);						//复位Dallas,返回结果
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
void TempSensor_Server(void)
{
	if(TempDataB!=TempData)
	{
		float	TempR	=	0.0;
		if(lineT>=240)
			lineT	=	0;		
		TempDataB	=	TempData;
		TempR	=	Get_ADC_Temperature(TempDataB);												//获取内部温度传感器温度
		LCD_Printf(100		,lineT,16	,LCD565_RED,"温度:%0.8f",TempR);		//待发药槽位，后边的省略号就是可变参数
		lineT+=16;	
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
void CS5530_Server(void)		//称重服务，AD值处理，获取稳定值
{
#if 1
	unsigned char pBuffer[5]	=	{0};
	CS5530_Process(&CS5530CH1);
	CS5530_Process(&CS5530CH2);
	
//	CS5530_ADC_Value	=	0;
	if((CS5530CH1.Data.WeighLive	!=0xFFFFFFFF)&&(CS5530CH1.Data.WeighFilt	!=CS5530_ADC_Value1))
	{
		if(lineCH1>=230)
			lineCH1	=	120;
		CS5530_ADC_Value1	=	CS5530CH1.Data.WeighFilt>>0;
		pBuffer[0]=1;
		memcpy(&pBuffer[1],&CS5530_ADC_Value1,4);
		APIRS485SendData(pBuffer,5);
//		USART_DMAPrintf	(UART4,"CH1:%0.8X\r\n",CS5530_ADC_Value>>5);					//自定义printf串口DMA发送程序,后边的省略号就是可变参数--1.7版本为UART4
//		LCD_Printf(0		,lineCH1,16	,LCD565_RED,"AD1:%0.8d",CS5530_ADC_Value>>5);				//待发药槽位，后边的省略号就是可变参数
		
		lineCH1+=16;
		
//		CS5530CH1.Data.WeighLive	=0xFFFFFFFF;
//		SysTick_DeleymS(50);				//SysTick延时nmS
	}
//	CS5530_ADC_Value	=	0;
	
	if((CS5530CH2.Data.WeighLive	!=0xFFFFFFFF)&&(CS5530CH2.Data.WeighFilt	!=CS5530_ADC_Value2))
	{
		
		if(lineCH2>=230)
			lineCH2	=	120;
		CS5530_ADC_Value2	=	CS5530CH2.Data.WeighFilt>>0;
		
		pBuffer[0]=2;
		memcpy(&pBuffer[1],&CS5530_ADC_Value2,4);
		APIRS485SendData(pBuffer,5);
//		USART_DMAPrintf	(UART4,"CH2:%0.8X\r\n",CS5530_ADC_Value>>5);					//自定义printf串口DMA发送程序,后边的省略号就是可变参数--1.7版本为UART4
//		LCD_Printf(200		,lineCH2,16	,LCD565_GBLUE,"AD2:%0.8d",CS5530_ADC_Value>>5);				//待发药槽位，后边的省略号就是可变参数		
		lineCH2+=16;	

//		CS5530CH2.Data.WeighLive	=0xFFFFFFFF;
		
//		SysTick_DeleymS(50);				//SysTick延时nmS
	}
	
	return;
#endif
#if 0
	CS5530_Time++;
	if(CS5530_Time>=50)		//1秒钟
	{
		CS5530_Time=0;
		CS5530_ADC_Value	=	CS5530_ReadData(&CS5530);									//读取AD值，如果返回0xFFFFFFFF,则未读取到24位AD值
		
		if(CS5530_ADC_Value	!= 0xFFFFFFFF)
		{
			CS5530_ADC_Value	=	CS5530_ADC_Value>>2;
			LCD_Printf(0		,128,32	,LCD565_RED,"AD:%0.8d",CS5530_ADC_Value);				//待发药槽位，后边的省略号就是可变参数
			USART_DMAPrintf	(USART1,"CH1:%0.8X\r\n",CS5530_ADC_Value);					//自定义printf串口DMA发送程序,后边的省略号就是可变参数--1.7版本为UART4
//			READ_GAIN=CS5530_ReadRegister(&CS5530,CS5530_READ_GAIN);				//增益寄存器
		}
	}
	return;
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
void LCD_Server(void)			//显示服务相关
{
#if 1
	millisecond++;
	if(millisecond>=999)
	{
//		SSD1963_DrawRectangle(100,100,110,110);
		millisecond=0;
		second++;
		if(second>59)
		{
			second=0;
			min++;			
			if(min>59)
			{
				min=0;
				hour++;
				if(hour>23)
				{
					hour=0;
				}
				LCD_Printf(100,130,32,LCD565_RED,"%02d:",hour);		//后边的省略号就是可变参数
				
			}
			LCD_Printf(148,130,32,LCD565_RED,"%02d:",min);		//后边的省略号就是可变参数
		}
		LCD_Printf(196,130,32,LCD565_RED,"%02d",second);		//后边的省略号就是可变参数
	}
#endif
}
/*******************************************************************************
* 函数名			:	RS485_Server
* 功能描述		:	数据收发--获取AD值命令:FA F5 ID 01 ,上报数据格式：FB F6 ID B1 B2 B3 高位在前
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
void RS485_Server(void)			//通讯管理---负责信息的接收与发送
{
	HCResult	res;
#if Master			//主机
	unsigned char sLeng;
	length=RS485_ReadBufferIDLE(&RS485,RevBuffe);	//串口空闲模式读串口接收缓冲区，如果有数据，将数据拷贝到RevBuffer,并返回接收到的数据个数，然后重新将接收缓冲区地址指向RxdBuffer
	if(		length	)
	{
		u16 temp	=	0;
		u16 PenColor	=LCD565_RED;
		
		time	=	0;
		res		=	APIRS485UplinkSetData(RevBuffe,length);
		sLeng	=	APIRS485UplinkGetAck(TxdBuffe);				//获取需要上传的数据
		if(length)
		{
			RS485_DMASend(&RS485,TxdBuffe,sLeng);	//RS485-DMA发送程序
		}
		if(0	!=	WriteFlag)
		{
			WriteFlag	=	0;
			PenColor	=LCD565_WHITE;
		}
		else
		{
			WriteFlag	=	1;
			PenColor	=LCD565_GREEN;
		}
		if(row>=240-100)
		{
			LCD_Fill(0,16,400,240-100,LCD565_BLACK);				//在指定区域内填充指定颜色;区域大小:(xend-xsta)*(yend-ysta)
			row	=	16;
		}
		if(16>row)
		{
			row=16;
		}
		
		LCD_ShowHex(0,row,16,PenColor,length,8,RevBuffe);                //显示十六进制数据
		temp	=	8*3*length;
		if(0<temp%400)
		{
			row	+=	(temp/400+1)*16;
		}
		else
		{
			row	+=	(temp/400)*16;
		}
		
	}
	else if(time++>200)
	{
		time	=	0;
    NuW++;
//		sendDataLoop:
		length	=	APIRS485UplinkGetData(TxdBuffe);
		if(length)
		{
			time	=	0;
			
			RS485_DMASend(&RS485,TxdBuffe,length);	//RS485-DMA发送程序
//			goto sendDataLoop;
		}
		else
		{
			return;
		}
		
		
	}
//	if(Rs485_Time	++>5)
//	{
//		Rs485_Time	=	0;
//		TxdBuffe[0]	=	0xFA;
//		TxdBuffe[1]	=	0xF5;
//		TxdBuffe[2]	=	SlaveID;
//		TxdBuffe[3]	=	0x01;
//		RS485_DMASend	(&RS485,TxdBuffe,4);	//RS485-DMA发送程序
//		if(SlaveID++>=250)
//			SlaveID	=	1;
//	}
#else
	RxNum=RS485_ReadBufferIDLE(&RS485,(u32*)RevBuffe,(u32*)RxdBuffe);	//串口空闲模式读串口接收缓冲区，如果有数据，将数据拷贝到RevBuffer,并返回接收到的数据个数，然后重新将接收缓冲区地址指向RxdBuffer
	if(		RxNum												\
			&&(RevBuffe[0]	==	0xFA)			\
			&&(RevBuffe[1]	==	0xF5)			\
			&&(RevBuffe[2]	==	SwitchID)	\
			&&(RevBuffe[3]	==	0x01)			\
		)
	{
		RxFlg	=	1;
		Rs485_Time	=	0;
	}
	if(RxFlg	==	1)
	{
		if(Rs485_Time++>=2)	//延时10mS
		{
			//CS5530_ADC_Value
			RxFlg	=	0;
			Rs485_Time	=	0;
			
			TxdBuffe[0]	=	0xFB;
			TxdBuffe[1]	=	0xF6;
			TxdBuffe[2]	=	SwitchID;
			TxdBuffe[3]	=	(CS5530_ADC_Value>>16)&0xFF;
			TxdBuffe[4]	=	(CS5530_ADC_Value>>8)&0xFF;
			TxdBuffe[5]	=	(CS5530_ADC_Value>>0)&0xFF;
			RS485_DMASend	(&RS485,(u32*)TxdBuffe,6);	//RS485-DMA发送程序
		}
	}
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
void SwitchID_Server(void)	//拔码开关处理--动态更新拨码地址
{
	u8 ID_Temp	=	0;
	ID_Temp	=	SWITCHID_Read(&SWITCHID);		//
	if(SwitchID	!=	ID_Temp)
	{
		SwitchID	=	ID_Temp;
		LCD_Printf(0		,0,16	,LCD565_RED,"ID:%-0.3d",SwitchID);				//待发药槽位，后边的省略号就是可变参数
		HCBoradSet(2,SWITCHID.nSWITCHID);
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
void SwitchID_Configuration(void)
{
	SWITCHID.NumOfSW	=	8;
	
	SWITCHID.SW1_PORT	=	GPIOC;
	SWITCHID.SW1_Pin	=	GPIO_Pin_6;
	
	SWITCHID.SW2_PORT	=	GPIOC;
	SWITCHID.SW2_Pin	=	GPIO_Pin_7;
	
	SWITCHID.SW3_PORT	=	GPIOC;
	SWITCHID.SW3_Pin	=	GPIO_Pin_8;
	
	SWITCHID.SW4_PORT	=	GPIOC;
	SWITCHID.SW4_Pin	=	GPIO_Pin_9;
	
	SWITCHID.SW5_PORT	=	GPIOC;
	SWITCHID.SW5_Pin	=	GPIO_Pin_12;
	
	SWITCHID.SW6_PORT	=	GPIOC;
	SWITCHID.SW6_Pin	=	GPIO_Pin_13;
	
	SWITCHID.SW7_PORT	=	GPIOC;
	SWITCHID.SW7_Pin	=	GPIO_Pin_14;
	
	SWITCHID.SW8_PORT	=	GPIOC;
	SWITCHID.SW8_Pin	=	GPIO_Pin_15;
	
	SwitchIdInitialize(&SWITCHID);							//
	
	SwitchID	=	SWITCHID_Read(&SWITCHID);		//
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
void LCD_Configuration(void)
{
	LCDPortDef		*Port;
	SPIDef				*SPIx;
	
	Port	=	&(sLCD.Port);
	SPIx		=	&(sLCD.GT32L32.SPI);
	
	Port->sCS_PORT		=	GPIOA;
	Port->sCS_Pin			=	GPIO_Pin_12;
	
	Port->sDC_PORT		=	GPIOA;
	Port->sDC_Pin			=	GPIO_Pin_8;
	
	Port->sWR_PORT		=	GPIOA;
	Port->sWR_Pin			=	GPIO_Pin_15;
	
	Port->sRD_PORT		=	GPIOC;
	Port->sRD_Pin			=	GPIO_Pin_5;
	
	Port->sREST_PORT	=	GPIOD;
	Port->sREST_Pin		=	GPIO_Pin_2;
	
	Port->sBL_PORT		=	GPIOA;
	Port->sBL_Pin			=	GPIO_Pin_3;
	
	Port->sTE_PORT		=	GPIOC;
	Port->sTE_Pin			=	GPIO_Pin_4;
	
	Port->sDATABUS_PORT	=	GPIOB;
	Port->sDATABUS_Pin	=	GPIO_Pin_All;
	
	sLCD.Flag.Rotate	=	Draw_Rotate_270D;	//使用旋转角度	
	
	SPIx->Port.SPIx=SPI1;
	
	SPIx->Port.CS_PORT=GPIOA;
	SPIx->Port.CS_Pin=GPIO_Pin_4;
	
	SPIx->Port.CLK_PORT	=	GPIOA;
	SPIx->Port.CLK_Pin=GPIO_Pin_5;
	
	SPIx->Port.MISO_PORT	=	GPIOA;
	SPIx->Port.MISO_Pin=GPIO_Pin_6;
	
	SPIx->Port.MOSI_PORT	=	GPIOA;
	SPIx->Port.MOSI_Pin=GPIO_Pin_7;
	
	SPIx->Port.SPI_BaudRatePrescaler_x=SPI_BaudRatePrescaler_2;
	
	R61509V_Initialize(&sLCD);
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
void CS5530_Configuration(void)
{
	CS5530CH1.Port.CS_PORT=GPIOC;
	CS5530CH1.Port.CS_Pin=GPIO_Pin_3;
	
	CS5530CH1.Port.SDI_PORT=GPIOC;
	CS5530CH1.Port.SDI_Pin=GPIO_Pin_2;
	
	CS5530CH1.Port.SDO_PORT=GPIOC;
	CS5530CH1.Port.SDO_Pin=GPIO_Pin_1;
	
	CS5530CH1.Port.SCLK_PORT=GPIOC;
	CS5530CH1.Port.SCLK_Pin=GPIO_Pin_0;
	
	CS5530_Initialize(&CS5530CH1);
	
	CS5530CH2.Port.CS_PORT=GPIOA;
	CS5530CH2.Port.CS_Pin=GPIO_Pin_1;
	
	CS5530CH2.Port.SDI_PORT=GPIOC;
	CS5530CH2.Port.SDI_Pin=GPIO_Pin_2;
	
	CS5530CH2.Port.SDO_PORT=GPIOC;
	CS5530CH2.Port.SDO_Pin=GPIO_Pin_1;
	
	CS5530CH2.Port.SCLK_PORT=GPIOC;
	CS5530CH2.Port.SCLK_Pin=GPIO_Pin_0;
	
	CS5530_Initialize(&CS5530CH2);
	
//	CS5530_PowerDown(&CS5530CH2);		//CS5530断电
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
	RS485.USARTx=USART1;
	RS485.RS485_CTL_PORT=GPIOA;
	RS485.RS485_CTL_Pin=GPIO_Pin_11;
	
	RS485_DMA_ConfigurationNR	(&RS485,19200,Rs485Size);	//USART_DMA配置--查询方式，不开中断,配置完默认为接收状态
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
void USART_Configuration(void)
{
//	//1.6版本为USART1
//	USART_DMA_ConfigurationNR	(USART1,115200,Rs485Size);	//USART_DMA配置--查询方式，不开中断
	//1.7版本为UART4
	USART_DMA_ConfigurationNR	(UART4,115200,Rs485Size);	//USART_DMA配置--查询方式，不开中断
}
/*******************************************************************************
* 函数名		:	
* 功能描述	:	 
* 输入		:	
* 输出		:
* 返回 		:
*******************************************************************************/
void PL010V13_DISPLAY(void)
{
//	R61509V_DrawPixelEx( 100, 100,LCD_FORE_COLOR);
//	R61509V_DrawHLine( 10, 100, 200, LCD_FORE_COLOR);
}
void PL010Delay(u32 time)
{	
	while(time--);
}


#endif
