/******************************** User_library *********************************
* 文件名 	: STM32_SDCard.H
* 作者   	: wegam@sina.com
* 版本   	: V
* 日期   	: 2016/01/01
* 说明   	: 
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/


#ifndef __STM32_FLASH_H
#define __STM32_FLASH_H

#include "stm32f10x_type.h"
//#include "stm32f10x_gpio.h"
//#include "stm32f10x_dac.h"
//#include "stm32f10x_rcc.h"
//#include "stm32f10x_dma.h"
//#include "stm32f10x_tim.h"
//主存储块容量： 
//小容量产品主存储块最大为4K×64位，每个存储块划分为32个1K字节的页。 
//中容量产品主存储块最大为16K×64位，每个存储块划分为128个1K字节的页。 
//大容量产品主存储块最大为64K×64位，每个存储块划分为256个2K字节的页。 
//互联型产品主存储块最大为32K×64位，每个存储块划分为128个2K字节的页。
//用户根据自己的需要设置
#define STM32_FLASH_SIZE 128 	 		//所选STM32的FLASH容量大小(单位为K)---存储块大小128K
#define STM32_FLASH_WREN 1        //使能FLASH写入(0，不是能;1，使能)

#if STM32_FLASH_SIZE<256					//小容量
#define STM_SECTOR_SIZE 1024			//字节单位-----扇区大小/页大小
#else 
#define STM_SECTOR_SIZE	2048			//字节单位-----扇区大小/页大小
#endif



//FLASH起始地址
#define STM32_FLASH_BASE	0x08000000 	//STM32 FLASH的起始地址





u16 STM32_FLASH_ReadHalfWord(u32 Addr);		//读取指定地址的半字(16位数据)
void STM32_FLASH_Write_NoCheck(u32 StartAddr,u16 *pBuffer,u16 NumToWrite); 	//不检查的写入半字数据
void STM32_FLASH_Write(u32 StartAddr,u16 *pBuffer,u16 NumToWrite);		//从指定地址写入指定长度的数据
void STM32_FLASH_Read(u32 StartAddr,u16 *pBuffer,u16 NumToRead);			//从指定地址开始读出指定长度的数据
void STM32_FLASH_Erase(u32 WriteAddr,u16 NumToWrite);			//擦除FLASH

#endif




