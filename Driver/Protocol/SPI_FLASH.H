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
	unsigned char WIP:1;		//write in progress bitд״̬λ��1-����д����;0-����д����
	unsigned char WEL:1;		//write enable latchд״̬��:1-����д��0-д��������ֹд��
	unsigned char BP0:1;		//the level of protected block BP0~BP2д����������
	unsigned char BP1:1;
	unsigned char BP2:1;
	unsigned char Reserve:2;
	unsigned char SRWD:1;		//Status Register Write Protect��״̬�Ĵ���д������־λ��1-д��������ֹд��
}SPIFlashStatusDef;
typedef struct	_SPIFlashCmd
{
	unsigned char WREN;		//write Enable��дʹ��
	unsigned char WRDI;		//write disable��дʧ��
	unsigned char WRSR;		//write status register��д״̬�Ĵ���
	unsigned char RDID;		//read identification�����豸��Ϣ��3byte����һ�ֽ�Ϊ�����̴��룬�ڶ������ֽ�ΪоƬ����
	unsigned char RDSR;		//read status register����״̬�Ĵ���
	unsigned char READ;		//read data��������
	unsigned char FREAD;	//fast read data�����ٶ�ȡ����
	unsigned char RDSFDP;	//Read SFDP:��(SFDP)Serial FlashоƬ�淶
	unsigned char RES;		//Read Electronic Signature:��������ȡ���ӱ�ǩ
	unsigned char REMS;		//Read Electronic Manufacturer & Device ID:����������Ϣ��ID
	unsigned char DREAD;	//Double Output Mode command��˫���ģʽ����
	unsigned char SE;			//Sector Erase����������
	unsigned char BE;			//Block Erase�������Ҳ������0XD8
	unsigned char CE;			//Chip Erase��оƬ����; ��Ƭ����; Ҳ������0XC7
	unsigned char PP;			//Page Program��дҳ��
	unsigned char DP;			//Deep Power Down�����ʡ��״̬
	unsigned char RDP;		//Release from Deep Power-down���˳���ȵ���
}SPIFlashCmdDef;
//----���ݽṹ��------------------------------------------------------------
typedef struct	
{
	unsigned long	ChipSize;					//Flash������byte��λ
	unsigned long	PageSize;					//ҳ��Сbyte��λ
	unsigned long	SectorSize;				//������Сbyte��λ
	unsigned long	BulkSize;					//���Сbyte��λ
} SPIFlashMemoryDef;
typedef struct	_SPIFlash
{
	SPIDef							SPI;				//SPI����
	SPIFlashCmdDef			Cmd;
	SPIFlashStatusDef 	Flag;
	SPIFlashMemoryDef		Memory;
}SPIFlashDef;

/* Exported functions ------------------------------------------------------- */
/*----- High layer function -----*/
void SPI_FLASH_Initialize(SPIFlashDef *Flash);


/*----- ���ݲ� -----*/
void SPI_FLASH_SectorErase(u32 SectorAddr);	//��������
void SPI_FLASH_BulkErase(u32 BulkAddr);			//�����
void SPI_FLASH_ChipErase(void);							//��Ƭ����

void SPI_FLASH_PageWrite(u8* pBuffer, u32 WriteAddr, u16 NumByteToWrite);
void SPI_FLASH_BufferWrite(u8* pBuffer, u32 StartAddr, u16 NumByteToWrite);
void SPI_FLASH_BufferRead(u8* pBuffer, u32 ReadAddr, u16 NumByteToRead);
void SPI_FLASH_StartReadSequence(u32 ReadAddr);

/*----- ��Ϣ�� -----*/
void SPI_FLASH_SetDeepPowerdown(void);	//�������ʡ��ģʽ
void SPI_FLASH_ResDeepPowerdown(void);	//�˳����ʡ��ģʽ
u32 SPI_FLASH_ReadRDSFDP(void);					//��(SFDP)Serial FlashоƬ�淶
u32 SPI_FLASH_ReadID(void);							//���豸��Ϣ��3byte����һ�ֽ�Ϊ�����̴��룬�ڶ������ֽ�ΪоƬ����
u32 SPI_FLASH_ReadREMS(void);						//����������Ϣ��ID
u32 SPI_FLASH_ReadStatusRegister(void);	//��״̬�Ĵ���



/*----- Low layer function -----*/
u8 SPI_FLASH_ReadByte(void);
u8 SPI_FLASH_SendByte(u8 byte);
//u16 SPI_FLASH_SendHalfWord(u16 HalfWord);
void SPI_FLASH_WriteEnable(void);				//д����
void SPI_FLASH_WriteDisble(void);				//д��ֹ
void SPI_FLASH_WaitForWriteEnd(void);		//�ȴ�д�����

#endif /* __SPI_FLASH_H */

/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/