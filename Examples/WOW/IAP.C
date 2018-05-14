/******************************** User_library *********************************
* 文件名 	: SPI_FLASH.C
* 作者   	: wegam@sina.com
* 版本   	: V
* 日期   	: 2017/04/16
* 说明   	: 
********************************************************************************
SPI_FLASH使用功能测试
1）需要宏定义 SPI_FLASH
2）使用USB_TEST 板测试
3）需要宏定义SPI引脚

*******************************************************************************/
#ifdef IAP							//如果定义了A3987_TEST 此功能生效

#include "cortexm3_macro.h"			//__MSR_MSP使用

#include "STM32F10x_BitBand.H"
#include "stm32f10x_nvic.h"


#include	"stdio.h"				//用于printf
#include	"string.h"			//用于printf
#include	"stdarg.h"			//用于获取不确定个数的参数
#include	"stdlib.h"			//malloc动态申请内存空间
	
#include	"stddef.h"
#include	"stdint.h"



#include "IAP.H"
#include "STM32_PWM.H"
#include "STM32_SYS.H"
#include "STM32_USART.H"
#include "STM32_SYSTICK.H"
#include "STM32_FLASH.H"
#include "STM32_CRC.H"







#define FLASH_IAP_ADDR		0x08000000  //用户程序的执行地址
#define FLASH_APP1_ADDR		0x08006000  //用户程序的执行地址
#define FLASH_USER_ADDR		0x08006000  //用户程序的执行地址
#define FLASH_APP2_ADDR   0x08013000  //存储接收到的用户程序的地址
#define FLASH_DATA_ADDR   0x0801E004  //存储用户数据的地址





#define BufferSize	STM_SECTOR_SIZE/2
u16 RevBuffer[BufferSize]={0};
u16 RxdBuffer[BufferSize]={0};
u16 TxdBuffer[BufferSize]={0};




u32	crc_data	=	0;
u32 SYS_TIME	=	0;
u32 JumpAddress;

/* 类型声明 -----------------------------------------------------------------*/
typedef  void (*pFunction)(void);

pFunction	UserApplication;

void MAIN_Configuration(void);	//
void SET_MSP(u32 addr) ;			//设置栈顶地址---调用汇编
void Jump_To_Application(void);	//跳转到应用程序
void Jump_To_IAP(void);
/*******************************************************************************
* 函数名		:	
* 功能描述	:	 
* 输入		:	
* 输出		:
* 返回 		:
*******************************************************************************/
void IAP_Configuration(void)
{
	//判断用户是否已经下载程序，因为正常情况下此地址是栈地址。
	//若没有这一句的话，即使没有下载程序也会进入而导致跑飞。
	if (((*(vu32*)FLASH_USER_ADDR) & 0x2FFE0000 ) != 0x20000000)
	{
		MAIN_Configuration();
		USART_DMAPrintf(USART1,"配置完成\n");					//自定义printf串口DMA发送程序,后边的省略号就是可变参数
	}
	else
	{
		USART_DMAPrintf(USART1,"跳转到应用程序\n");					//自定义printf串口DMA发送程序,后边的省略号就是可变参数
		Jump_To_Application();	//跳转到应用程序
	}
}

/*******************************************************************************
* 函数名		:	
* 功能描述	:	 
* 输入		:	
* 输出		:
* 返回 		:
*******************************************************************************/
void IAP_Server(void)		//CRC--TEST
{	
//	u16	Num	=	0;
//	Num	=	USART_ReadBufferIDLE(USART1,(u32*)RevBuffer,(u32*)RxdBuffer);	//串口空闲模式读串口接收缓冲区，如果有数据，将数据拷贝到RevBuffer,并返回接收到的数据个数，然后重新将接收缓冲区地址指向RxdBuffer
//	if(Num)
//	{
//		if(RevBuffer[0]	==	UpdataKey2)
//		{
//			STM32_FLASH_Erase(FLASH_USER_ADDR,512);			//擦除FLASH
//			NVIC_GenerateSystemReset();
//		}
//		else
//		{
//			memcpy(TxdBuffer,RevBuffer,Num);
//			USART_DMASend(USART1,(u32*)TxdBuffer,Num);	//串口DMA发送程序
//		}
//	}
//	
	SYS_TIME++;
	if(SYS_TIME>=5000)
	{
		Jump_To_IAP();
//		NVIC_GenerateSystemReset();
//		NVIC_DeInit();		//
//		__disable_irq();
	}
}
/*******************************************************************************
*函数名			:	function
*功能描述		:	函数功能说明
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
void MAIN_Configuration(void)
{
	SYS_Configuration();											//系统配置 STM32_SYS.H	
	
	PWM_OUT(TIM2,PWM_OUTChannel1,1,500);
		
	SysTick_Configuration(500);							//系统嘀嗒时钟配置72MHz,单位为uS
	
	USART_DMA_ConfigurationNR	(USART1,115200,(u32*)RxdBuffer,BufferSize);	//USART_DMA配置--查询方式，不开中断
	
	CRC_SetEnable();
}

/*******************************************************************************
* 函数名		:	
* 功能描述	:	 
* 输入		:	
* 输出		:
* 返回 		:
*******************************************************************************/
void IAP_CRCTEST(void)		//CRC--TEST
{	
	u16	Num	=	0;
	Num	=	USART_ReadBufferIDLE(USART1,(u32*)RevBuffer,(u32*)RxdBuffer);	//串口空闲模式读串口接收缓冲区，如果有数据，将数据拷贝到RevBuffer,并返回接收到的数据个数，然后重新将接收缓冲区地址指向RxdBuffer
	if(Num)
	{
		memcpy(TxdBuffer,RevBuffer,Num);
//		crc_data	=	Get_CalcBlockCrc32((u32*)TxdBuffer,Num/2);
		crc_data	=	CRC16_MODBUS((unsigned char *)TxdBuffer, Num);
		if(Num%2	==	0)
		{
			TxdBuffer[Num/2]	=	crc_data;
		}
		else
		{
			TxdBuffer[Num/2]		=	(TxdBuffer[Num/2]&0x00FF)|((crc_data<<8)&0xFF00);			//低8位放入最后半字的高8位
			TxdBuffer[Num/2+1]	=	(TxdBuffer[Num/2+1]&0xFF00)|((crc_data>>8)&0x00FF);		//高8位放入新增半字的低8位
		}
		USART_DMASend(USART1,(u32*)TxdBuffer,Num+2);	//串口DMA发送程序
	}
}
/*******************************************************************************
*函数名			:	function
*功能描述		:	设置栈顶地址---调用汇编
*输入				: addr:栈顶地址
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
void SET_MSP(u32 addr) 
{
	__MSR_MSP(addr);
}
/*******************************************************************************
*函数名			:	function
*功能描述		:	函数功能说明
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
void Jump_To_Application(void)
{
//	ApplicationAddr
	if (((*(vu32*)FLASH_USER_ADDR) & 0x2FFE0000 ) == 0x20000000)
	{           
		USART_DMAPrintf(USART1,"Execute user Program\r\n\n");
		//跳转至用户代码
		//	asm("CPSID I");
		__disable_irq();
		JumpAddress = *(vu32*) (FLASH_USER_ADDR + 4);
		UserApplication = (pFunction) JumpAddress;

		//初始化用户程序的堆栈指针
		SET_MSP(*(vu32*) FLASH_USER_ADDR);
		UserApplication();		//运行用户程序
	}
}
/*******************************************************************************
*函数名			:	function
*功能描述		:	函数功能说明
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
void Jump_To_IAP(void)
{
	vu32	RAMAddr	=	0;
	RAMAddr	=	*(vu32*)FLASH_IAP_ADDR;
	if ((RAMAddr	& 0x2FFE0000) == 0x20000000)
//	if (((*(vu32*)FLASH_IAP_ADDR) & 0x2FFE0000 ) == 0x20000000)
	{           
		//跳转至用户代码
		//	asm("CPSID I");
		__disable_irq();
		JumpAddress = *(vu32*) (FLASH_IAP_ADDR);
		UserApplication = (pFunction) JumpAddress;

		//初始化用户程序的堆栈指针
		SET_MSP(*(vu32*) FLASH_IAP_ADDR);
		UserApplication();		//运行用户程序
	}
}






















/*******************************************************************************
*函数名			:	function
*功能描述		:	设置栈顶地址---调用汇编
*输入				: addr:栈顶地址
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
//跳转到应用程序段
//appxaddr:用户代码起始地址.
//void iap_load_app(u32 appxaddr)
//{
//	if(((*(vu32*)appxaddr)&0x2FFE0000)==0x20000000) //检查栈顶地址是否合法.
//	{
//		jump2app = (iapfun)*(vu32*)(appxaddr+4);//用户代码区第二个字为程序开始地址(复位地址)，此处查看中断向量表可知
//		MSR_MSP(*(vu32*)appxaddr);//初始化APP堆栈指针(用户代码区的第一个字用于存放栈顶地址)
//		jump2app(); //跳转到APP，执行复位中断程序
//	}
//}
/*******************************************************************************
*函数名			:	function
*功能描述		:	设置栈顶地址---调用汇编
*输入				: addr:栈顶地址
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
//void Jump_Address(void)
//{
//	if (((*(volatile u32*)ApplicationAddress) & 0x2FFE0000 ) == 0x20000000)
//	{
//		test = (*(volatile u32*)ApplicationAddress);
//		JumpAddress = *(volatile u32*) (ApplicationAddress + 4);
//		Jump_To_Application = (pFunction) JumpAddress;
//		__set_MSP(*(volatile u32*) ApplicationAddress);
//		Jump_To_Application();
//	}
//}
































#endif
