/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : spi_flash.h
* Author             : MCD Application Team
* Version            : V2.0.1
* Date               : 06/13/2008
* Description        : Header for spi_flash.c file.
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SPI_FLASH_H
#define __SPI_FLASH_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_lib.h"
#include "STM32_SPI.H"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Uncomment the line corresponding to the STMicroelectronics evaluation board
   used to run the example */
//#if !defined (USE_STM3210B_EVAL) &&  !defined (USE_STM3210E_EVAL)
// //#define USE_STM3210B_EVAL
// #define USE_STM3210E_EVAL
//#endif

//#ifdef USE_STM3210B_EVAL
// #define GPIO_CS                  GPIOA
// #define RCC_APB2Periph_GPIO_CS   RCC_APB2Periph_GPIOA
// #define GPIO_Pin_CS              GPIO_Pin_4 
//#else /* USE_STM3210E_EVAL */
// #define GPIO_CS                  GPIOB
// #define RCC_APB2Periph_GPIO_CS   RCC_APB2Periph_GPIOB
// #define GPIO_Pin_CS              GPIO_Pin_2 
//#endif

/* Exported macro ------------------------------------------------------------*/
/* Select SPI FLASH: Chip Select pin low  */
//#define SPI_FLASH_CS_LOW()       GPIO_ResetBits(GPIO_CS, GPIO_Pin_CS)
/* Deselect SPI FLASH: Chip Select pin high */
//#define SPI_FLASH_CS_HIGH()      GPIO_SetBits(GPIO_CS, GPIO_Pin_CS)

typedef struct	_SPIFlashStatus
{
	unsigned char WIP:1;		//write in progress bit写状态位：1-正在写操作;0-不在写操作
	unsigned char WEL:1;		//write enable latch写状态锁:1-允许写，0-写保护（禁止写）
	unsigned char BP0:1;		//the level of protected block BP0~BP2写保护块区域，
	unsigned char BP1:1;
	unsigned char BP2:1;
	unsigned char Reserve:2;
	unsigned char SRWD:1;		//Status Register Write Protect：状态寄存器写保护标志位：1-写保护（禁止写）
}SPIFlashStatusDef;
typedef struct	_SPIFlashCmd
{
	unsigned char WREN;		//write Enable：写使能
	unsigned char WRDI;		//write disable：写失能
	unsigned char WRSR;		//write status register：写状态寄存器
	unsigned char RDID;		//read identification：读设备信息，3byte；第一字节为制造商代码，第二第三字节为芯片代码
	unsigned char RDSR;		//read status register：读状态寄存器
	unsigned char READ;		//read data：读数据
	unsigned char FREAD;	//fast read data：快速读取数据
	unsigned char RDSFDP;	//Read SFDP:读(SFDP)Serial Flash芯片规范
	unsigned char RES;		//Read Electronic Signature:读器件读取电子标签
	unsigned char REMS;		//Read Electronic Manufacturer & Device ID:读制造商信息和ID
	unsigned char DREAD;	//Double Output Mode command：双输出模式命令
	unsigned char SE;			//Sector Erase：扇区擦除
	unsigned char BE;			//Block Erase：块擦除也可以用0XD8
	unsigned char CE;			//Chip Erase：芯片擦除; 整片擦除; 也可以用0XC7
	unsigned char PP;			//Page Program：写页面
	unsigned char DP;			//Deep Power Down：深度省电状态
	unsigned char RDP;		//Release from Deep Power-down：退出深度掉电
}SPIFlashCmdDef;
//----数据结构体------------------------------------------------------------
typedef struct	
{
	unsigned long	ChipSize;					//Flash总容量byte单位
	unsigned long	PageSize;					//页大小byte单位
	unsigned long	SectorSize;				//扇区大小byte单位
	unsigned long	BulkSize;					//块大小byte单位
} SPIFlashMemoryDef;
typedef struct	_SPIFlash
{
	SPIDef							SPI;				//SPI驱动
	SPIFlashCmdDef			Cmd;
	SPIFlashStatusDef 	Flag;
	SPIFlashMemoryDef		Memory;
}SPIFlashDef;

/* Exported functions ------------------------------------------------------- */
/*----- High layer function -----*/
void SPI_FLASH_Initialize(SPIFlashDef *Flash);


/*----- 数据层 -----*/
void SPI_FLASH_SectorErase(u32 SectorAddr);	//扇区擦除
void SPI_FLASH_BulkErase(u32 BulkAddr);			//块擦除
void SPI_FLASH_ChipErase(void);							//整片擦除

void SPI_FLASH_PageWrite(u8* pBuffer, u32 WriteAddr, u16 NumByteToWrite);
void SPI_FLASH_BufferWrite(u8* pBuffer, u32 StartAddr, u16 NumByteToWrite);
void SPI_FLASH_BufferRead(u8* pBuffer, u32 ReadAddr, u16 NumByteToRead);
void SPI_FLASH_StartReadSequence(u32 ReadAddr);

/*----- 信息层 -----*/
void SPI_FLASH_SetDeepPowerdown(void);	//进入深度省电模式
void SPI_FLASH_ResDeepPowerdown(void);	//退出深度省电模式
u32 SPI_FLASH_ReadRDSFDP(void);					//读(SFDP)Serial Flash芯片规范
u32 SPI_FLASH_ReadID(void);							//读设备信息，3byte；第一字节为制造商代码，第二第三字节为芯片代码
u32 SPI_FLASH_ReadREMS(void);						//读制造商信息和ID
u32 SPI_FLASH_ReadStatusRegister(void);	//读状态寄存器



/*----- Low layer function -----*/
u8 SPI_FLASH_ReadByte(void);
u8 SPI_FLASH_SendByte(u8 byte);
//u16 SPI_FLASH_SendHalfWord(u16 HalfWord);
void SPI_FLASH_WriteEnable(void);				//写开启
void SPI_FLASH_WriteDisble(void);				//写禁止
void SPI_FLASH_WaitForWriteEnd(void);		//等待写入完成

#endif /* __SPI_FLASH_H */

/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/
