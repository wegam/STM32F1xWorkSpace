#ifdef ICCARD
#include "ICCARD.H"
#include "STM32F10x_BitBand.H"
#include "STM32_GPIO.H"
#include "STM32_SYS.H"
#include "STM32_SYSTICK.H"
#include "STM32_WDG.H"
#include "STM32_USART.H"

#include	"stdio.h"			//用于printf
#include	"string.h"		//用于printf
#include	"stdarg.h"		//用于获取不确定个数的参数
#include	"stdlib.h"		//malloc动态申请内存空间


#define BufferSize	30

u8	Sector	=	1;						//扇区 0~1
u8	Block	=	1;						//块 0~2

#define	ICCARD_Number	=	0;			//数据0~99999999
u16 systimecount	=	0;
u16 ICCARD_SendLenth	=	0;			//全局变量，串口发送数据长度
u8 runFlag	=	0;
u8 RxdBuffer[BufferSize]={0};
u8 RevBuffer[BufferSize]={0};
u8 TxdBuffer[BufferSize]={0xE1,0x24,0x01,0x01,0x60,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x1C,0x0D,0x1E};
u8 CmdBuffer[30]	=	{0};

//=================读取块数据
u8 ICCARD_PassWord[6] =
  {
    0xFF,   /* PassWord0 */					//6字节密码
    0xFF,   /* PassWord1 */
    0xFF,   /* PassWord2 */
    0xFF,		/* PassWord3 */
    0xFF,   /* PassWord4 */
    0xFF		/* PassWord5 */
	};
//=================读取块数据
u8 ICCARD_Data[16] =
  {
    0x01,   /* Data0 	*/			//16字节数据
    0x02,   /* Data1 	*/
		0x03,   /* Data2 	*/
		0x04,   /* Data3 	*/
		0x05,   /* Data4 	*/
		0x06,   /* Data5 	*/
		0x07,   /* Data6 	*/
		0x08,   /* Data7 	*/
		0x09,   /* Data8 	*/
		0x10,   /* Data9 	*/
		0x11,   /* Data10 	*/
		0x12,   /* Data11 	*/
		0x13,   /* Data12 	*/
		0x14,   /* Data13 	*/
		0x15,   /* Data14 	*/
		0x16   	/* Data15 	*/		
	};

//=================读块数据
u8 ICCARD_CMD_GetDataBlock1[] =
  {
    0xE1,   /* F-Head 	*/			//为帧头，上位机下发时固定为0XE1，下位机应答时固定为0XD2；
    0x24,  	/* CmdType 	*/			//命令类型
    0x01,		/* Sector 	*/			//1字节扇区号
    0x01,   /* Block 		*/			//1字节块号
    0x60,   /* KeyType	*/			//1字节密钥模式 KEYA（0x60）/KEYB(0x61)
    0xFF,   /* PassWord0 */					//6字节密码
    0xFF,   /* PassWord1 */
    0xFF,   /* PassWord2 */
    0xFF,		/* PassWord3 */
    0xFF,   /* PassWord4 */
    0xFF,		/* PassWord5 */
    0x1C,   /* Crc16-HIGN */
    0x0D,		/* Crc16-LOW */
    0x1E   	/* F-End*/						//为帧尾，上位机下发时固定为0X1E，下位机应答时固定为0X2D；
	};
//=================写块数据
u8 ICCARD_CMD_SetDataBlock1[] =
  {
    ICCARD_MO_SetDataBlock(Sector,Block,ICCARD_Number),
	};
//=================写块数据
u8 ICCARD_CMD_SetDataBlock[] =
  {
		0xE1,   /* F-Head 	:为帧头，上位机下发时固定为0XE1，下位机应答时固定为0XD2*/
		0x25,  	/* CmdType 	:命令类型*/
		0x01,		/* Sector 	:1字节扇区号*/
		0x01,   /* Block 	:1字节块号	*/
		0x60,   /* KeyType	:1字节密钥模式 KEYA（0x60）/KEYB(0x61)*/
		0xFF,   /* PassWord0 :6字节密码*/
		0xFF,   /* PassWord1 */
		0xFF,   /* PassWord2 */
		0xFF,		/* PassWord3 */
		0xFF,   /* PassWord4 */
		0xFF,		/* PassWord5 */
		0xFF,   /* Data0 	:16字节数据*/
		0xFF,   /* Data1 	*/
		0xFF,   /* Data2 	*/
		0xFF,   /* Data3 	*/
		0xFF,   /* Data4 	*/
		0xFF,   /* Data5 	*/
		0xFF,   /* Data6 	*/
		0xFF,   /* Data7 	*/
		0xFF,   /* Data8 	*/
		0xFF,   /* Data9 	*/
		0xFF,   /* Data10 	*/
		0xFF,   /* Data11 	*/
		0xFF,   /* Data12 	*/
		0xFF,   /* Data13 	*/
		0xFF,   /* Data14 	*/
		0xFF,   /* Data15 	*/
		0x1C,   /* Crc16-HIGN */
		0x0D,		/* Crc16-LOW */
		0x1E   	/* F-End	:为帧尾，上位机下发时固定为0X1E，下位机应答时固定为0X2D*/
	};
//=================设置扇区密码
u8 ICCARD_CMD_SetPassWord[] =
  {
		0xE1,   /* F-Head 	:为帧头，上位机下发时固定为0XE1，下位机应答时固定为0XD2*/
		0x26,  	/* CmdType 	:命令类型*/
		0x01,		/* Sector 	:1字节扇区号*/
		0x60,   /* KeyType	:1字节密钥模式 KEYA（0x60）/KEYB(0x61)*/
		0xFF,   /* OldPassWord0 :6字节旧密码*/
		0xFF,   /* OldPassWord1 */
		0xFF,   /* OldPassWord2 */
		0xFF,		/* OldPassWord3 */
		0xFF,   /* OldPassWord4 */
		0xFF,		/* OldPassWord5 */
		0xFF,   /* OldPassWord0 :6字节新密码*/
		0xFF,   /* OldPassWord1 */
		0xFF,   /* OldPassWord2 */
		0xFF,		/* OldPassWord3 */
		0xFF,   /* OldPassWord4 */
		0xFF,		/* OldPassWord5 */
		0x26,   /* Crc16-HIGN */
		0x63,		/* Crc16-LOW */
		0x1E   	/* F-End	:为帧尾，上位机下发时固定为0X1E，下位机应答时固定为0X2D*/
	};
//=================设置读头ID	
u8 ICCARD_CMD_SetReaderID[] =
  {
    0xE1,   /* F-Head 	*/			//为帧头，上位机下发时固定为0XE1，下位机应答时固定为0XD2；
    0x42,  	/* CmdType 	*/			//命令类型
		0x03,		/* ID-HIGN  	*/	//1字节扇区号
		0xE8,		/* ID-HIGN  	*/	//1字节扇区号
    0x5A,		/* Crc16-HIGN  	*/	//1字节扇区号
    0xB8,   /* Crc16-LOW 		*/	//1字节块号
    0x1E   	/* F-End*/					//为帧尾，上位机下发时固定为0X1E，下位机应答时固定为0X2D；
	};	
//=================读取读头ID	
u8 ICCARD_CMD_GetReaderID[] =
  {
    0xE1,   /* F-Head 			*/	//为帧头，上位机下发时固定为0XE1，下位机应答时固定为0XD2；
    0x43,  	/* CmdType 			*/	//命令类型
    0x78,		/* Crc16-HIGN  	*/	//1字节扇区号
    0xA7,   /* Crc16-LOW 		*/	//1字节块号
    0x1E   	/* F-End				*/	//为帧尾，上位机下发时固定为0X1E，下位机应答时固定为0X2D；
	};
//=================设置读卡器读卡区域	
const u8 ICCARD_CMD_SetReaderArea[] =
  {
    0xE1,   /* F-Head 	*/			//为帧头，上位机下发时固定为0XE1，下位机应答时固定为0XD2；
    0x44,  	/* CmdType 	*/			//命令类型
		0x01,  	/* Sector 	*/			//扇区：0,1,其中0为只读，为卡信息
		0x01,  	/* Block 	*/				//块号：0,1,2
		0x60,   /* KeyType	*/			//1字节密钥模式 KEYA（0x60）/KEYB(0x61)
		0xFF,   /* PassWord0 */					//6字节密码
    0xFF,   /* PassWord1 */
    0xFF,   /* PassWord2 */
    0xFF,		/* PassWord3 */
    0xFF,   /* PassWord4 */
    0xFF,		/* PassWord5 */
    0x9F,		/* Crc16-HIGN  	*/	//1字节扇区号
    0x6F,   /* Crc16-LOW 		*/	//1字节块号
    0x1E   	/* F-End*/					//为帧尾，上位机下发时固定为0X1E，下位机应答时固定为0X2D；
	};		
/*******************************************************************************
* 函数名		:	
* 功能描述	:	 
* 输入		:	
* 输出		:
* 返回 		:
*******************************************************************************/
void ICCARD_Configuration(void)
{
	SYS_Configuration();
	SysTick_Configuration(1000);	//系统嘀嗒时钟配置72MHz,单位为uS
	
//	GPIO_Configuration0();
//	TIM_Configuration(TIM1,7200,3000);	//定时时间设定
//	PWM_Configuration(TIM2,7200,10000,51);
//	PWM_OUT(TIM1,PWM_OUTChannel1,20000,50);		//PWM设定
//	PWM_OUT(TIM2,PWM_OUTChannel1,20000,500);	//PWM设定
//	PWM_OUT(TIM3,PWM_OUTChannel1,5000,30);		//PWM设定
//	PWM_OUT(TIM3,PWM_OUTChannel2,5000,30);		//PWM设定
//	PWM_OUT(TIM3,PWM_OUTChannel3,1000,500);		//PWM设定
//	PWM_OUT(TIM4,PWM_OUTChannel1,20000,40);		//PWM设定
	
	PWM_OUT(TIM2,PWM_OUTChannel1,2,500);		//PWM设定
	USART_DMA_ConfigurationNR	(USART2,19200,(u32*)RxdBuffer,BufferSize);	//USART_DMA配置--查询方式，不开中断
	GPIO_Configuration_OPP50(GPIOC,	GPIO_Pin_12);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605
	GPIO_Configuration_OPP50(GPIOD,	GPIO_Pin_2);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605
	GPIO_Configuration_OPP50(GPIOB,	GPIO_Pin_3);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605
	GPIO_Configuration_OPP50(GPIOB,	GPIO_Pin_4);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605
	GPIO_Configuration_OPP50(GPIOB,	GPIO_Pin_5);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605
	GPIO_Configuration_OPP50(GPIOB,	GPIO_Pin_6);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605
	GPIO_Configuration_OPP50(GPIOB,	GPIO_Pin_7);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605
	GPIO_Configuration_OPP50(GPIOB,	GPIO_Pin_8);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605
	GPIO_Configuration_OPP50(GPIOB,	GPIO_Pin_9);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605
}
/*******************************************************************************
* 函数名		:	
* 功能描述	:	 
* 输入		:	
* 输出		:
* 返回 		:
*******************************************************************************/
void ICCARD_Server(void)
{
	u16 Num	=	0;
	systimecount++;
	if(systimecount>=2000)
	{
		systimecount=0;
		runFlag	=	0;
		ICCARD_WriteData(12345678);
		memcpy(TxdBuffer,CmdBuffer,ICCARD_SendLenth);
		USART_DMASend	(USART2,(u32*)TxdBuffer,ICCARD_SendLenth);														//串口DMA发送程序
		GPIO_Toggle	(GPIOB,	GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9);		//将GPIO相应管脚输出翻转----V20170605
		GPIO_Toggle	(GPIOC,	GPIO_Pin_12);		//将GPIO相应管脚输出翻转----V20170605
		GPIO_Toggle	(GPIOD,	GPIO_Pin_2);		//将GPIO相应管脚输出翻转----V20170605
	}
	if(systimecount	==	1000)
	{
		memset(RevBuffer, 0x00, 22);
		memset(TxdBuffer, 0x00, 30);
	}
	Num	=	USART_ReadBufferIDLE(USART2,(u32*)RevBuffer,(u32*)RxdBuffer);	//串口空闲模式读串口接收缓冲区，如果有数据，将数据拷贝到RevBuffer,并返回接收到的数据个数，然后重新将接收缓冲区地址指向RxdBuffer
	if(Num)
	{
//	USART_DMASend	(USART2,(u32*)TxdBuffer,22);	//串口DMA发送程序
//	USART_DMASend	(USART2,(u32*)ICCARD_CMD_SetDataBlock,Num);	//串口DMA发送程序
//	USART_DMASend	(USART2,(u32*)ICCARD_CMD_SetReaderID,sizeof(ICCARD_CMD_SetReaderID));	//串口DMA发送程序
//	USART_DMASend	(USART2,(u32*)ICCARD_CMD_GetReaderID,sizeof(ICCARD_CMD_GetReaderID));	//串口DMA发送程序
		
//		GPIO_Toggle	(GPIOB,	GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9);		//将GPIO相应管脚输出翻转----V20170605
//		GPIO_Toggle	(GPIOC,	GPIO_Pin_12);		//将GPIO相应管脚输出翻转----V20170605
//		GPIO_Toggle	(GPIOD,	GPIO_Pin_2);		//将GPIO相应管脚输出翻转----V20170605
	}
//	if(systimecount	==	0)
//	GPIO_Toggle	(GPIOB,	GPIO_Pin_0);		//将GPIO相应管脚输出翻转----V20170605
}
/*******************************************************************************
* 函数名			:	function
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
*******************************************************************************/
void ICCardReader_initialze(void)
{

}
/*******************************************************************************
* 函数名			:	ICCARD_WriteData
* 功能描述		:	写数据，默认使用扇区1，块1,KEY60,密码FF FF FF FF FF FF
* 输入			: void
* 返回值			: void
*******************************************************************************/
u8* ICCARD_WriteData(u32	Number)
{
	u32 Temp	=	Number;
//	Temp	|=	((Number/10000000)&0x0000000F)<<28;
//	Temp	|=	((Number%10000000/1000000)&0x0000000F)<<24;
//	Temp	|=	((Number%1000000/100000)&0x0000000F)<<20;
//	Temp	|=	((Number%100000/10000)&0x0000000F)<<16;
//	Temp	|=	((Number%10000/1000)&0x0000000F)<<12;
//	Temp	|=	((Number%1000/100)&0x0000000F)<<8;
//	Temp	|=	((Number%100/10)&0x0000000F)<<4;
//	Temp	|=	((Number%10)&0x0000000F)<<0;
	
	ICCARD_SendLenth	=	sizeof(ICCARD_CMD_SetDataBlock);	
	memcpy(CmdBuffer,ICCARD_CMD_SetDataBlock,ICCARD_SendLenth);
	
	
	CmdBuffer[11]	=	(Temp>>24)&0xFF;
	CmdBuffer[12]	=	(Temp>>16)&0xFF;
	CmdBuffer[13]	=	(Temp>>8)&0xFF;
	CmdBuffer[14]	=	(Temp>>0)&0xFF;
	return CmdBuffer;
//	ICCARD_SendLenth	=	sizeof(ICCARD_CMD_SetDataBlock);
}
/*******************************************************************************
* 函数名			:	ICCARD_SetPassWord
* 功能描述		:	修改扇区密码命令，命令字 0x26
*							DataBlock：1字节扇区号+1字节密钥模式+1字节keyA（0x60）/keyB（0x61）标志+6字节旧密码+6字节新密码
*
*						例：
*							E1 26 01 61 00 FF FF FF FF FF FF FF FF FF FF FF FF 26 63 1E
*							E1 26 01 61 00 FF FF FF FF FF FF 11 11 11 11 11 11 6B 81 1E
* 输入			: void
* 返回值			: void
*******************************************************************************/
u8* ICCARD_SetPassWord(u8 Sector,u8* NewPassWord)
{
	ICCARD_SendLenth	=	sizeof(ICCARD_CMD_SetPassWord);	
	memcpy(CmdBuffer,ICCARD_CMD_SetPassWord,ICCARD_SendLenth);	
	
	CmdBuffer[2]	=	Sector;		//扇区
	memcpy(&CmdBuffer[11],NewPassWord,6);
	
	//----CRC16

	return CmdBuffer;
//	ICCARD_SendLenth	=	sizeof(ICCARD_CMD_SetDataBlock);
}
/*******************************************************************************
* 函数名			:	ICCARD_SetReadArea
* 功能描述		:	设置读头读卡扇区、块号、KEYA（0x60）/KEYB(0x61)、读卡密码0x44
*							DataBlock：扇区-01、块号-02、KEYA 、密码-FF FF FF FF FF FF
*							应答：按执行命令应答
*							举例：E1 44 01 01 60 FF FF FF FF FF FF 9F 6F 1E
* 输入			: void
* 返回值			: void
*******************************************************************************/
u8* ICCARD_SetReadArea(u8 Sector,u8 Block,u8* PassWord)
{
	ICCARD_SendLenth	=	sizeof(ICCARD_CMD_SetReaderArea);	
	memcpy(CmdBuffer,ICCARD_CMD_SetReaderArea,ICCARD_SendLenth);	
	
	CmdBuffer[2]	=	Sector;		//扇区
	CmdBuffer[3]	=	Block;		//扇区
	memcpy(&CmdBuffer[5],PassWord,6);
	
	//----CRC16

	return CmdBuffer;
//	ICCARD_SendLenth	=	sizeof(ICCARD_CMD_SetDataBlock);
}

#endif
