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

#ifdef PL010V15TEST				//智能药架称重LCD板

#include "PL010V15TEST.H"

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


#include "SWITCHID.H"

#include "string.h"				//串和内存操作函数头文件
#include "stm32f10x_dma.h"



#define	Master	1		//0--从机，1-主机
u16	DelayTime=0x1000;
u16	LCDTime=0;
u16	DSPTime=0;




GT32L32Def 	GT32L32_Info;
char	Char_Buffer[256];		//记录format内码


RS485Def  RS485;
#define	Rs485Size	256
u8 RxdBuffe[Rs485Size]={0};
u8 RevBuffe[Rs485Size]={0};
u8 TxdBuffe[Rs485Size]={0};
u8 RxFlg=0;
u16 RxNum=0;
u32	Rs485_Time	=	0;
u8	SlaveID	=	0;
u32 Rev_ADC	=	0;
u8	Rev_ID	=	0;



SwitchDef	SWITCHID;
u8 SwitchID=0;	//拔码开关地址


R61509V_Pindef R61509V_Pinfo;
u8	DspFlg	=	0;

u16 BKlight	=	0;



CS5530Def CS5530;
u32	CS5530_Time	=	0;
u32	CS5530_ADC_CMP			=	0;
u32 CS5530_ADC_Value		=0xFFFFFFFF;
u32 CS5530_ADC_Valuebac	=0xFFFFFFFF;

u32	WeigthARR[100]	=	{0};
u8	DspFlg1	=	0;
u32	We1	=	0;
u8	NuW	=	0;
u32	BsW	=	0;	//空重
u32 SsW	=	0;	//单重
u8	St	=	0;	//步骤
u8	SN	=	0;	//数量
u8	SNb	=	0;	//备存数量

u16 weighVar[20]={0};
u8	VarN	=	0;

/*******************************************************************************
* 函数名		:	
* 功能描述	:	 
* 输入		:	
* 输出		:
* 返回 		:
*******************************************************************************/
void PL010V15TEST_Configuration(void)
{
	SYS_Configuration();					//系统配置---打开系统时钟 STM32_SYS.H
	
	GPIO_DeInitAll();							//将所有的GPIO关闭----V20170605	
	
	SwitchID_Configuration();
	
	GT32L32_Configuration();
	
//	CS5530_Configuration();
	
	RS485_Configuration();
	
	R61509V_Configuration();
	
	SysTick_Configuration(1000);	//系统嘀嗒时钟配置72MHz,单位为uS
	
	IWDG_Configuration(2000);			//独立看门狗配置---参数单位ms	

//	PWM_OUT(TIM2,PWM_OUTChannel1,1,900);	//PWM设定-20161127版本--运行指示灯
	
	PWM_OUT(TIM2,PWM_OUTChannel4,500,200);		//PWM设定-20161127版本--背光
	
	PL010V13_PrintfString(0		,0,32	,"地址：%0.2d",SwitchID);				//待发药槽位，后边的省略号就是可变参数
	PL010V13_PrintfString(0		,0,32	,"地址：%0.2d",SwitchID);				//待发药槽位，后边的省略号就是可变参数
}
/*******************************************************************************
* 函数名		:	
* 功能描述	:	 
* 输入		:	
* 输出		:
* 返回 		:
*******************************************************************************/
void PL010V15TEST_Server(void)
{	
	IWDG_Feed();				//独立看门狗喂狗
	RS485_Server();			//通讯管理---负责信息的接收与发送
	R61509V_Server();		//显示服务相关
//	CS5530_Server();		//称重服务，AD值处理，获取稳定值
	SwitchID_Server();	//拔码开关处理--动态更新拨码地址
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
	CS5530_Process(&CS5530);
	if(CS5530_ADC_Value	!=	CS5530.Data.Origin)
	{
		CS5530_ADC_Value	=	CS5530.Data.Origin;
		PL010V13_PrintfString(0		,128,32	,"AD:%0.8d",CS5530_ADC_Value);				//待发药槽位，后边的省略号就是可变参数
	}
//	if(CS5530_Time++>=50)		//1秒钟
//	{		
//		CS5530_Time=0;
//		CS5530_ADC_Valuebac=CS5530_ReadData(&CS5530);	//读取AD值，如果返回0xFFFFFFFF,则未读取到24位AD值
//		if(CS5530_ADC_Valuebac!=0xFFFFFFFF)
//		{
//			
////			CS5530_ADC_Valuebac>>=5;		//19位精度
//			
//			if(CS5530_ADC_Value==CS5530_ADC_Valuebac)
//			{
//				DspFlg	=	0;
//			}
//			if(CS5530_ADC_Value>=CS5530_ADC_Valuebac)
//			{
//				CS5530_ADC_CMP	=	CS5530_ADC_Value-CS5530_ADC_Valuebac;
//			}
//			else
//			{
//				CS5530_ADC_CMP	=	CS5530_ADC_Valuebac-CS5530_ADC_Value;				
//			}
//			DspFlg	=	1;
//			CS5530_ADC_Value	=	CS5530_ADC_Valuebac;
//			
//			if(CS5530_ADC_CMP>100)
//			{
//				NuW	=	0;
//				return;
//			}
//			WeigthARR[NuW]	=	CS5530_ADC_Value;
//			if(NuW++>=20-1)
//			{
//				long	temp	=	0;
//				//We1
//				
//				u8 i	=	0;
//				
//				temp	=	CS5530_GetWeightUseMedinaFilter(&CS5530);
//				
//				if(temp>200)
//				{
//					NuW	=	0;
//					return;
//				}
//				NuW	=	0;
//				We1	=	WeigthARR[i];
//				for(i=1;i<20;i++)
//				{
//					We1	=	(We1+WeigthARR[i])/2;
//				}
//				if(St	==	1)
//				{
//					St=0;
//					BsW	=	We1;
//				}
//				else if(St	==	2)
//				{
//					SsW	=	(We1	-	BsW)/10;
//					St	=	3;
//					SN	=	10;
//					SNb	=	10;
//				}
//				else if(St	==	3)
//				{
//					SN	=	(We1-BsW+500)/SsW;	//计数数量
//					if(SN!=SNb)
//					{
//						SNb	=	SN;
//						PL010V13_PrintfString(0		,128,32	,"数量%0.3d",SNb);				//待发药槽位，后边的省略号就是可变参数
//					}
//				}
//				DspFlg1	=	1;
//			}
//				
//		}
//		else
//		{
////			We1	=0;
////			NuW	=0;
//		}
//	}
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
void R61509V_Server(void)			//显示服务相关
{
	if(DspFlg)
	{
		DspFlg	=	0;
//		PL010V13_PrintfString(0		,32,32	,"%0.8d",CS5530_ADC_CMP);				//待发药槽位，后边的省略号就是可变参数
//		PL010V13_PrintfString(0		,64	,32	,"%0.8d",CS5530_ADC_Value);				//待发药槽位，后边的省略号就是可变参数
	}
	if(DspFlg1)
	{
		DspFlg1	=	0;
		PL010V13_PrintfString(0		,96,32	,"%0.8d",We1);				//待发药槽位，后边的省略号就是可变参数
	}
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
	RxNum=RS485_ReadBufferIDLE(&RS485,(u32*)RevBuffe,(u32*)RxdBuffe);	//串口空闲模式读串口接收缓冲区，如果有数据，将数据拷贝到RevBuffer,并返回接收到的数据个数，然后重新将接收缓冲区地址指向RxdBuffer
	if(		RxNum													\
			&&	(RevBuffe[0]	==	0xFB)			\
			&&	(RevBuffe[1]	==	0xF6)			\
		)
	{
		unsigned char temp	=	0;
		temp	=	RevBuffe[2];
		switch(temp)
		{
			case 0x00:PL010V13_PrintfString(0		,0,32	,"主机发出命令");break;//清除屏幕函数--蓝色 R61509V_Clean(0XFC07)
			case 0x01:PL010V13_PrintfString(0		,0,32	,"主机发出命令"); break;
			case 0x02:PL010V13_PrintfString(0		,32,32	,"收到单元板应答"); break;
			case 0x03:PL010V13_PrintfString(0		,64,32	,"收到驱动板应答"); break;
//			case 0x04:PL010V13_PrintfString(0		,96,32	,"收到驱动板应答"); break;
			default :break;
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
void SwitchID_Server(void)	//拔码开关处理--动态更新拨码地址
{
	u8 ID_Temp	=	0;
	ID_Temp	=	SWITCHID_Read(&SWITCHID);		//
	if(SwitchID	!=	ID_Temp)
	{
		SwitchID	=	ID_Temp;
		PL010V13_PrintfString(0		,0,32	,"地址：%0.2d",SwitchID);				//待发药槽位，后边的省略号就是可变参数
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
	SWITCHID.NumOfSW	=	6;
	
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
void GT32L32_Configuration(void)
{
	GT32L32_Info.GT32L32_Port.sSPIx=SPI1;
	GT32L32_Info.GT32L32_Port.sGT32L32_CS_PORT=GPIOA;
	GT32L32_Info.GT32L32_Port.sGT32L32_CS_PIN=GPIO_Pin_4;
	GT32L32_Info.GT32L32_Port.SPI_BaudRatePrescaler_x=SPI_BaudRatePrescaler_32;
	
	GT32L32_ConfigurationNR(&GT32L32_Info);				//普通SPI通讯方式配置
	
	GPIO_Configuration_OPP50	(GPIOA,GPIO_Pin_4);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605
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
void R61509V_Configuration(void)
{
	unsigned long	LCDTime	=	0xFFFFFF;
	R61509V_Pinfo.R61509V_sCS_PORT		=	GPIOA;
	R61509V_Pinfo.R61509V_sCS_Pin			=	GPIO_Pin_12;
	
	R61509V_Pinfo.R61509V_sRS_PORT		=	GPIOA;
	R61509V_Pinfo.R61509V_sRS_Pin			=	GPIO_Pin_8;
	
	R61509V_Pinfo.R61509V_sWR_PORT		=	GPIOA;
	R61509V_Pinfo.R61509V_sWR_Pin			=	GPIO_Pin_15;
	
	R61509V_Pinfo.R61509V_sRD_PORT		=	GPIOC;
	R61509V_Pinfo.R61509V_sRD_Pin			=	GPIO_Pin_5;
	
	R61509V_Pinfo.R61509V_sREST_PORT	=	GPIOD;
	R61509V_Pinfo.R61509V_sREST_Pin		=	GPIO_Pin_2;
	
	R61509V_Pinfo.R61509V_sBL_PORT		=	GPIOA;
	R61509V_Pinfo.R61509V_sBL_Pin			=	GPIO_Pin_3;
	
	R61509V_Pinfo.R61509V_sTE_PORT		=	GPIOC;
	R61509V_Pinfo.R61509V_sTE_Pin			=	GPIO_Pin_4;
	
	R61509V_Pinfo.R61509V_sDATABUS_PORT	=	GPIOB;
	R61509V_Pinfo.R61509V_sDATABUS_Pin	=	GPIO_Pin_All;
	
	R61509V_PinConf(&R61509V_Pinfo);
	

	R61509V_Clean(0xF800);			//清除屏幕函数--蓝白
	R61509V_Delay(LCDTime);

//	R61509V_Clean(0X01CF);			//清除屏幕函数--黄色
//	R61509V_Delay(LCDTime);
	
//	R61509V_Clean(0X07FF);			//清除屏幕函数--红色
//	R61509V_Delay(LCDTime);
	
//	R61509V_Clean(0x07E0);			//清除屏幕函数--紫色
//	R61509V_Delay(LCDTime);
//	
	R61509V_Clean(0XFC07);			//清除屏幕函数--蓝色
	R61509V_Delay(LCDTime);
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
	CS5530.Port.CS_PORT=GPIOC;
	CS5530.Port.CS_Pin=GPIO_Pin_3;
	
	CS5530.Port.SDI_PORT=GPIOC;
	CS5530.Port.SDI_Pin=GPIO_Pin_2;
	
	CS5530.Port.SDO_PORT=GPIOC;
	CS5530.Port.SDO_Pin=GPIO_Pin_1;
	
	CS5530.Port.SCLK_PORT=GPIOC;
	CS5530.Port.SCLK_Pin=GPIO_Pin_0;
	
	CS5530_Initialize(&CS5530);
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
	
	RS485_DMA_ConfigurationNR	(&RS485,115200,(u32*)RxdBuffe,Rs485Size);	//USART_DMA配置--查询方式，不开中断,配置完默认为接收状态
}
/*******************************************************************************
* 函数名		:	
* 功能描述	:	 
* 输入		:	
* 输出		:
* 返回 		:
*******************************************************************************/
void LCD_PowerUp(void)
{	
	#if 0
	PL010Delay(0xFFFF);
	PL010V13_PrintfString(1		,0	,16	,"待发药槽位：%2d",RevBuffe[0]);				//后边的省略号就是可变参数
	PL010V13_PrintfString(1		,0	,16	,"待发药槽位：%2d",RevBuffe[0]);				//后边的省略号就是可变参数
	PL010Delay(0xFFFF);
	PL010V13_PrintfString(1		,20	,16	,"待发药数量：%2d",RevBuffe[1]);				//后边的省略号就是可变参数
	PL010Delay(0xFFFF);
	PL010V13_PrintfString(1		,40	,16	,"已发药数量：%2d",RevBuffe[1]);				//后边的省略号就是可变参数
	PL010Delay(0xFFFF);
	
//	PL010V13_PrintfString(0		,60	,16	,"总共请求数量：%4d",SumFQ);				//总共发药请求数量
//	PL010V13_PrintfString(0		,80	,16	,"总共发药数量：%4d",SumFed);				//总共已发药数量
	PL010V13_PrintfString(1		,100	,16	,"错误状态：");				//错误状态
	PL010Delay(0xFFFF);
	
	PL010V13_PrintfString(1		,160	,16	,"提示：长按3秒读取发药头");				//错误状态
	PL010Delay(0xFFFF);
	

	//平行线
	R61509V_DrawLine(221,0,221,400,R61509V_WHITE);						//AB 两个坐标画一条直线
	R61509V_DrawLine(201,0,201,400,R61509V_WHITE);						//AB 两个坐标画一条直线
	R61509V_DrawLine(181,0,181,400,R61509V_WHITE);						//AB 两个坐标画一条直线
	R61509V_DrawLine(161,0,161,400,R61509V_WHITE);						//AB 两个坐标画一条直线
	//垂直线--中
	R61509V_DrawLine(161,200,221,200,R61509V_WHITE);					//AB 两个坐标画一条直线
	//垂直线--右
	R61509V_DrawLine(161,250-1,221,250-1,R61509V_WHITE);			//AB 两个坐标画一条直线
	R61509V_DrawLine(161,300-1,221,300-1,R61509V_WHITE);			//AB 两个坐标画一条直线
	R61509V_DrawLine(161,350-1,221,350-1,R61509V_WHITE);			//AB 两个坐标画一条直线
	R61509V_DrawLine(161,400-1,221,400-1,R61509V_WHITE);			//AB 两个坐标画一条直线
	
	//垂直线--左
	R61509V_DrawLine(161,1,221,1,					R61509V_WHITE);							//AB 两个坐标画一条直线
	R61509V_DrawLine(161,51,221,51,				R61509V_WHITE);						//AB 两个坐标画一条直线
	R61509V_DrawLine(161,101,221,101,			R61509V_WHITE);					//AB 两个坐标画一条直线
	R61509V_DrawLine(161,151,221,151,			R61509V_WHITE);					//AB 两个坐标画一条直线

	//填充
	R61509V_Fill(2,180,50,200-2,R61509V_RED);				//在指定区域内填充指定颜色;区域大小:(xend-xsta)*(yend-ysta)
	R61509V_Clean(R61509V_BLUE);			//清除屏幕函数------
	
	
	
//	R61509V_DrawLine(10,200,10,280,R61509V_WHITE);						//AB 两个坐标画一条直线
	
	#else
//	R61509V_Clean(R61509V_WHITE);			//清除屏幕函数------
//	PL010Delay(0x8FFFFF);
	R61509V_Clean(R61509V_BLUE);			//清除屏幕函数------
//	PL010Delay(0x8FFFFF);
//	R61509V_Clean(R61509V_GRAY);			//清除屏幕函数------
	PL010Delay(0x0FFFFF);
	R61509V_Clean(R61509V_YELLOW);			//清除屏幕函数------
//	PL010Delay(0x8FFFFF);
//	R61509V_Clean(R61509V_WHITE);			//清除屏幕函数------
//	PL010Delay(0x8FFFFF);
//	R61509V_Clean(R61509V_BLACK);			//清除屏幕函数------

//	PL010Delay(0xFFFF);
//	PL010V13_PrintfString(0	,0,16	,"TEST");				//错误状态
	#endif
//	R61509V_Clean(R61509V_BLACK);			//清除屏幕函数------
	
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
void LCD_Display(void)
{
//	PL010V13_PrintfString(0		,120	,16	,"显示测试！！！！！！！！！");				//错误状态
	
#if 0		
	DSPTime++;
	if(DSPTime>500)
	{
		DSPTime=0;
		LCD_WXS();		//位显示
		LCD_DDSP();		//显示总共请求数量和已发数量
	}	
	LCD_WS();		//位闪烁
	
	if(LCDTime>=1000)
	{			
		LCDTime=0;		
	}	
	
	RxNum=RS485_ReadBufferIDLE(&RS485,(u32*)RevBuffe,(u32*)RxdBuffe);	//串口空闲模式读串口接收缓冲区，如果有数据，将数据拷贝到RevBuffer,并返回接收到的数据个数，然后重新将接收缓冲区地址指向RxdBuffer
	if(RxNum==4&&RevBuffe[0]==0x00&&RevBuffe[1]==0xFF)		//RS485接收到数据
	{
		NumFW=RevBuffe[2];
		PL010V13_PrintfString(96		,0	,16	,"%2d",RevBuffe[2]);				//待发药槽位，后边的省略号就是可变参数
		PL010V13_PrintfString(96		,20	,16	,"%2d",RevBuffe[3]);				//待发药数量，后边的省略号就是可变参数
//		PL010V13_PrintfString(192		,68	,16	,"%2d",RevBuffe[1]);				//已发药数量，后边的省略号就是可变参数
	}
	else if(RxNum==3&&RevBuffe[0]==0x02)		//RS485接收到数据
	{
		SumFQ[RevBuffe[1]-1]+=RevBuffe[2];
		NumFW=RevBuffe[1];
		PL010V13_PrintfString(96		,0	,16	,"%2d",RevBuffe[1]);				//待发药槽位，后边的省略号就是可变参数
		PL010V13_PrintfString(96		,20	,16	,"%2d",RevBuffe[2]);				//待发药数量，后边的省略号就是可变参数
		PL010V13_PrintfString(96		,40	,16	,"%2d",0);									//已发药数量，后边的省略号就是可变参数
		
//		PL010V13_PrintfString(0		,60	,16	,"总共请求数量：%4d",SumFQ);				//总共发药请求数量
		PL010V13_PrintfString(0		,120	,16	,"正在发药！！！！！！！！！！");				//错误状态
	}
	else if(RxNum==4&&RevBuffe[0]==0x82)		//RS485接收到数据
	{
		SumFed[RevBuffe[1]-1]+=RevBuffe[2];
		PL010V13_PrintfString(96		,0	,16	,"%2d",RevBuffe[1]);				//待发药槽位，后边的省略号就是可变参数
		PL010V13_PrintfString(96		,20	,16	,"%2d",0);									//待发药数量，后边的省略号就是可变参数
		PL010V13_PrintfString(96		,40	,16	,"%2d",RevBuffe[2]);				//已发药数量，后边的省略号就是可变参数		
		
//		PL010V13_PrintfString(112		,80	,16	,"%4d",SumFed);					//总共已发药数量
		
	}
	else if(RxNum==6&&RevBuffe[0]==0x81)	//槽位信息0x01--获取,0x81--上报
	{
		Onlinede=RevBuffe[4];
	}
	else if(RxNum==1&&RevBuffe[0]==0x01)	//槽位信息0x01--获取,0x81--上报
	{
		PL010V13_PrintfString(0		,120	,16		,"获取槽位信息！！！");				//错误状态
		NumFW=0;
		Onlinede=0;
		memset(SumFed,0x00,8);
		memset(SumFQ,0x00,8);

		PL010V13_PrintfString(96		,0	,16	,"%2d",0);				//待发药槽位，后边的省略号就是可变参数
		PL010V13_PrintfString(96		,20	,16	,"%2d",0);				//待发药数量，后边的省略号就是可变参数
	}
	
	for(DelayTime=0;DelayTime<1000;DelayTime++)
	{
		
	}
	if(RxNum&&(RevBuffe[0]==0x82))		//错误状态显示
	{
		switch(RevBuffe[3])
		{
			case 0x00:	PL010V13_PrintfString(0		,120	,16	,"！！！！！！！！！！！！！！");				//错误状态
				break;
			case 0x80:	PL010V13_PrintfString(0		,120	,16	,"药品被卡住！！！！！！！！！");				//错误状态
				break;
			case 0x81:	PL010V13_PrintfString(0		,120	,16	,"缺药！！！！！！！！！！！！");				//错误状态
				break;
			case 0x82:	PL010V13_PrintfString(0		,120	,16	,"等待命令结果超时！！！！！！");				//错误状态
				break;
			case 0xC0:	PL010V13_PrintfString(0		,120	,16	,"单元柜控制器通信异常！！！！");				//错误状态
				break;
			case 0xC1:	PL010V13_PrintfString(0		,120	,16	,"发药层控制器通信异常！！！！");				//错误状态
				break;
		}

	}
#endif
}
/*******************************************************************************
*函数名		:	LCD_ShowString
*功能描述	:	显示字符串高通字库
*输入			: x,y:起点坐标
						*p:字符串起始地址
						用16字体
*输出			:	无
*返回值		:	无
*例程			:
*******************************************************************************/
unsigned int PL010V13_PrintfString(u16 x,u16 y,u8 font,const char *format,...)				//后边的省略号就是可变参数
{ 
		
//		va_list ap; 										//VA_LIST 是在C语言中解决变参问题的一组宏，所在头文件：#include <stdarg.h>,用于获取不确定个数的参数
//		static char string[ 256 ];			//定义数组，
//  	va_start( ap, format );
//		vsprintf( string , format, ap );    
//		va_end( ap );
	

	u16 i=0;		//显示

	//1)**********获取数据宽度
	u16 num=strlen((const char*)format);		//获取数据宽度
	//2)**********定义缓冲区大小变量
	unsigned int BufferSize;
	//3)**********args为定义的一个指向可变参数的变量，va_list以及下边要用到的va_start,va_end都是是在定义，可变参数函数中必须要用到宏， 在stdarg.h头文件中定义
	va_list args; 
	//5)**********初始化args的函数，使其指向可变参数的第一个参数，format是可变参数的前一个参数
	va_start(args, format);
	//6)**********正常情况下返回生成字串的长度(除去\0),错误情况返回负值
	BufferSize = vsnprintf(Char_Buffer, 128,format, args);
	num=BufferSize;
	//7)**********结束可变参数的获取
	va_end(args);                                      		
	
	for(i=0;i<num;i++)
	{ 
		unsigned char dst=Char_Buffer[i];
//		u8 GTBuffer[512]={0};		//点阵数据存储空间
		u32 lengh=0;						//汉字点阵的数据长度		
		if(dst>0x80)		//双字节--汉字
		{
			u16 word=dst<<8;			
//			Char_Buffer++;
			dst=Char_Buffer[i+1];
			word=word|dst;			
			//显示超限判断
			if(font==16&&x>R61509V_W-16)
			{
				x=0;
				y+=16;
			}
			if(font==32&&x>R61509V_W-32)
			{
				x=0;
				y+=32;
			}
			if(font==16&&y>R61509V_H-16)
			{
				y=x=0;
			}
			if(font==32&&y>R61509V_H-32)
			{
				y=x=0;
			}
			lengh=GT32L32_ReadBuffer(&GT32L32_Info,font,word,GT32L32_Info.GT32L32_Data.GT32L32_Buffer);		//从字库中读数据函数
			//写入屏幕
			R61509V_ShowChar(x,y,font,lengh,GT32L32_Info.GT32L32_Data.GT32L32_Buffer);
			//显示地址增加	
			if(font==12)
			{
				x+=12;
			}
			else if(font==16)
			{
				x+=16;
			}
			else if(font==24)
			{
				x+=24;
			}
			else if(font==32)
			{
				x+=32;
			}
//			Char_Buffer++;
			i++;		//双字节，减两次
		}
		else		//单字节
		{			
			if(x>R61509V_W-16)
			{
				x=0;
				y+=32;
			}
			if(font==16&&y>R61509V_H-16)
			{
				y=x=0;
			}
			if((font==32)&&(y>R61509V_H-32))
			{
				y=x=0;
			}
			lengh=GT32L32_ReadBuffer(&GT32L32_Info,font,(u16)dst,GT32L32_Info.GT32L32_Data.GT32L32_Buffer);		//从字库中读数据函数
//			//写入屏幕
			R61509V_ShowChar(x,y,font,lengh,GT32L32_Info.GT32L32_Data.GT32L32_Buffer);			
			//显示地址增加
			if(font==12)
			{
				x+=6;
			}
			else if(font==16)
			{
				x+=8;
			}
			else if(font==24)
			{
				x+=12;
			}
			else if(font==32)
			{
				x+=16;
			}			
//			Char_Buffer++;
//			i++;		//双字节，减两次
		}
	}
	//9)**********DMA发送完成后注意应该释放缓冲区：free(USART_BUFFER);
//	free(Char_Buffer);		//发送完成后注意应该释放缓冲区：free(Char_Buffer); 
	return BufferSize;
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
