#ifdef EepromTest
#include "EepromTest.H"
#include "STM32_FLASH.H"

#include "STM32_PWM.H"
#include "STM32_GPIO.H"
#include "STM32_SYS.H"
#include "STM32_WDG.H"
#include "STM32_SYSTICK.H"
#include "STM32_USART.H"
#include "STM32F10x_BitBand.H"


#include "AT24C02.H"
#include "I2C.H"	

#include	"stdio.h"			//用于printf
#include	"string.h"		//用于printf
#include	"stdarg.h"		//用于获取不确定个数的参数
#include	"stdlib.h"		//malloc动态申请内存空间


//#include "delay.h"
//#include "sys.h"
//#include "STM32_096OLED.h"
//#include "bmp.h"


sI2CDef At24c02;

unsigned	char *teststr="I2C_WriteBuffer(&At24c02,0,WriteBuffer,5);";
unsigned	char WriteBuffer[300]={0xF5,0xFF};
unsigned	char ReadBuffer[300]={0x00};

	
unsigned	short time=	0;
unsigned	short strsize=0;
unsigned	long	WriteCount=0;

unsigned	long	STARTADDR=0x08008000;

void EEPROMReadERROR(void);
/*******************************************************************************
* 函数名		:	
* 功能描述	:	 
* 输入		:	
* 输出		:
* 返回 		:
*******************************************************************************/
void EepromTest_Configuration(void)
{

	SYS_Configuration();				//系统配置
	At24c02.HW.SDA_Port		=	GPIOB;
	At24c02.HW.SDA_Pin		=	GPIO_Pin_7;
	At24c02.HW.SCL_Port		=	GPIOB;
	At24c02.HW.SCL_Pin		=	GPIO_Pin_6;
	I2C_Configuration(&At24c02);	//启用锁--配置
	
	SysTick_Configuration(1000);	//系统嘀嗒时钟配置72MHz,单位为uS
	PWM_OUT(TIM2,PWM_OUTChannel1,1,990);						//PWM设定-20161127版本
	
	strsize=strlen(teststr);
	memcpy(WriteBuffer,teststr,strsize);
	
	//I2C_WriteBuffer(&At24c02,0,WriteBuffer,8);
	STM32_FLASH_Read(STARTADDR,(unsigned short*)&WriteCount,2);							//从指定地址开始读出指定长度的数据
//	if(WriteCount==0xFFFFFFFF)
//	{
//		WriteCount=0;
//		STM32_FLASH_Write(STARTADDR,(unsigned short*)&WriteCount,2);						//从指定地址写入指定长度的数据
//	}
}
/*******************************************************************************
* 函数名		:	
* 功能描述	:	 
* 输入		:	
* 输出		:
* 返回 		:
*******************************************************************************/
void EepromTest_Server(void)
{
	unsigned char datasize=3;
	time++;
	if(time==1)
	{	
		//I2C_WriteBuffer(&At24c02,0,WriteBuffer,2);
		I2C_WritePage(&At24c02,0,WriteBuffer);
		//memset(ReadBuffer,0x00,256);
	}
	else if(time==20)
	{
		//I2C_ReadBuffer(&At24c02,0,ReadBuffer,1);
		I2C_ReadPage(&At24c02,0,ReadBuffer);
		if(0!=memcmp(WriteBuffer,ReadBuffer,1))
		{
			PWM_OUT(TIM2,PWM_OUTChannel1,8,500);						//PWM设定-20161127版本
			//STM32_FLASH_Write(STARTADDR,(unsigned short*)&WriteCount,2);						//从指定地址写入指定长度的数据
			EEPROMReadERROR();
		}
		else
		{
			WriteCount++;
			if(WriteCount%5000==0)
			{
				//STM32_FLASH_Write(STARTADDR,(unsigned short*)&WriteCount,2);						//从指定地址写入指定长度的数据
			}
		}
		//memset(ReadBuffer,0x00,2048);
	}
	else if(time>=100)
	{
		//STM32_FLASH_Write(STARTADDR,(unsigned short*)&WriteCount,2);						//从指定地址写入指定长度的数据
		//STM32_FLASH_Read(STARTADDR,(unsigned short*)&WriteCount,2);							//从指定地址开始读出指定长度的数据
		time=	0;
	}
	
}

void EEPROMReadERROR(void)
{
	while(1);
}




#endif
