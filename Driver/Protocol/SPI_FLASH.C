/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : spi_flash.c
* Author             : MCD Application Team
* Version            : V2.0.1
* Date               : 06/13/2008
* Description        : This file provides a set of functions needed to manage the
*                      communication between SPI peripheral and SPI M25P64 FLASH.
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "SPI_FLASH.H"

//#include	"stdio.h"			//用于printf
#include	"string.h"			//用于printf
//#include	"stdarg.h"			//用于获取不确定个数的参数
//#include	"stdlib.h"			//malloc动态申请内存空间

/* Private typedef -----------------------------------------------------------*/
//#define SPI_FLASH_PageSize    0x1006

/* Private define ------------------------------------------------------------*/
//#define WRITE      0x02  /* Write to Memory instruction */
//#define WRSR       0x01  /* Write Status Register instruction */
//#define WREN       0x06  /* Write enable instruction */

//#define READ       0x03  /* Read from Memory instruction */
//#define RDSR       0x05  /* Read Status Register instruction  */
//#define RDID       0x9F  /* Read identification */
//#define SE         0xD8  /* Sector Erase instruction */
//#define BE         0xC7  /* Bulk Erase instruction */

#define WIP_Flag   0x01  /* Write In Progress (WIP) flag */

#define Dummy_Byte 0xA5

SPIFlashDef *FlashSYS	=	0;		//内部驱动使用，不可删除
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
* Function Name  : SPI_FLASH_Init
* Description    : Initializes the peripherals used by the SPI FLASH driver.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SPI_FLASH_Initialize(SPIFlashDef *Flash)
{
	SPIDef	*SPIx	=	0;
  SPIx	=	&Flash->SPI;
	FlashSYS	=	Flash;
	SPI_Initialize(SPIx);		//SPI接口配置
}

/*******************************************************************************
* Function Name  : SPI_FLASH_SectorErase
* Description    : Erases the specified FLASH sector.扇区擦除
* Input          : SectorAddr: address of the sector to erase.
* Output         : None
* Return         : None
*******************************************************************************/
void SPI_FLASH_SectorErase(u32 SectorAddr)
{
  /* Send write enable instruction */
  SPI_FLASH_WriteEnable();

  /* Sector Erase */
  /* Select the FLASH: Chip Select low */
  SPI_CS_LOW(&FlashSYS->SPI);
  /* Send Sector Erase instruction */
  SPI_ReadWriteByteSPI(&FlashSYS->SPI,FlashSYS->Cmd.SE);
  /* Send SectorAddr high nibble address byte */
  SPI_ReadWriteByteSPI(&FlashSYS->SPI,(SectorAddr & 0xFF0000) >> 16);
  /* Send SectorAddr medium nibble address byte */
  SPI_ReadWriteByteSPI(&FlashSYS->SPI,(SectorAddr & 0xFF00) >> 8);
  /* Send SectorAddr low nibble address byte */
  SPI_ReadWriteByteSPI(&FlashSYS->SPI,SectorAddr & 0xFF);
  /* Deselect the FLASH: Chip Select high */
  SPI_CS_HIGH(&FlashSYS->SPI);

  /* Wait the end of Flash writing */
  SPI_FLASH_WaitForWriteEnd();
}
/*******************************************************************************
* Function Name  : SPI_FLASH_BulkErase
* Description    : Erases the entire FLASH.块擦除
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SPI_FLASH_BulkErase(u32 BulkAddr)
{
  /* Send write enable instruction */
  SPI_FLASH_WriteEnable();

  /* Bulk Erase */
  /* Select the FLASH: Chip Select low */
  SPI_CS_LOW(&FlashSYS->SPI);
  /* Send Bulk Erase instruction  */
  SPI_ReadWriteByteSPI(&FlashSYS->SPI,FlashSYS->Cmd.BE);
	/* Send SectorAddr high nibble address byte */
  SPI_ReadWriteByteSPI(&FlashSYS->SPI,(BulkAddr & 0xFF0000) >> 16);
  /* Send SectorAddr medium nibble address byte */
  SPI_ReadWriteByteSPI(&FlashSYS->SPI,(BulkAddr & 0xFF00) >> 8);
  /* Send SectorAddr low nibble address byte */
  SPI_ReadWriteByteSPI(&FlashSYS->SPI,BulkAddr & 0xFF);
  /* Deselect the FLASH: Chip Select high */
  SPI_CS_HIGH(&FlashSYS->SPI);

  /* Wait the end of Flash writing */
  SPI_FLASH_WaitForWriteEnd();
}
/*******************************************************************************
* Function Name  : SPI_FLASH_SectorErase
* Description    : Erases the specified FLASH sector.扇区擦除
* Input          : SectorAddr: address of the sector to erase.
* Output         : None
* Return         : None
*******************************************************************************/
void SPI_FLASH_ChipErase(void)
{
  /* Send write enable instruction */
  SPI_FLASH_WriteEnable();

  /* Sector Erase */
  /* Select the FLASH: Chip Select low */
  SPI_CS_LOW(&FlashSYS->SPI);
  /* Send Sector Erase instruction */
  SPI_ReadWriteByteSPI(&FlashSYS->SPI,FlashSYS->Cmd.CE);
  /* Deselect the FLASH: Chip Select high */
  SPI_CS_HIGH(&FlashSYS->SPI);

  /* Wait the end of Flash writing */
  SPI_FLASH_WaitForWriteEnd();
}


/*******************************************************************************
* Function Name  : SPI_FLASH_PageWrite
* Description    : Writes more than one byte to the FLASH with a single WRITE
*                  cycle(Page WRITE sequence). The number of byte can't exceed
*                  the FLASH page size.
* Input          : - pBuffer : pointer to the buffer  containing the data to be
*                    written to the FLASH.
*                  - WriteAddr : FLASH's internal address to write to.
*                  - NumByteToWrite : number of bytes to write to the FLASH,
*                    must be equal or less than "SPI_FLASH_PageSize" value.
* Output         : None
* Return         : None
*******************************************************************************/
void SPI_FLASH_PageWrite(u8* pBuffer, u32 WriteAddr, u16 NumByteToWrite)
{
	if(NumByteToWrite>FlashSYS->Memory.PageSize)		//写入数据大于一页
	{
		NumByteToWrite	=	FlashSYS->Memory.PageSize;
	}
  /* Enable the write access to the FLASH */
  SPI_FLASH_WriteEnable();

  /* Select the FLASH: Chip Select low */
  SPI_CS_LOW(&FlashSYS->SPI);
  /* Send "Write to Memory " instruction */
  SPI_ReadWriteByteSPI(&FlashSYS->SPI,FlashSYS->Cmd.PP);
  /* Send WriteAddr high nibble address byte to write to */
  SPI_ReadWriteByteSPI(&FlashSYS->SPI,(WriteAddr & 0xFF0000) >> 16);
  /* Send WriteAddr medium nibble address byte to write to */
  SPI_ReadWriteByteSPI(&FlashSYS->SPI,(WriteAddr & 0xFF00) >> 8);
  /* Send WriteAddr low nibble address byte to write to */
  SPI_ReadWriteByteSPI(&FlashSYS->SPI,WriteAddr & 0xFF);

  /* while there is data to be written on the FLASH */
  while (NumByteToWrite--)
  {
    /* Send the current byte */
    SPI_ReadWriteByteSPI(&FlashSYS->SPI,*pBuffer);
    /* Point on the next byte to be written */
    pBuffer++;
  }

  /* Deselect the FLASH: Chip Select high */
  SPI_CS_HIGH(&FlashSYS->SPI);

  /* Wait the end of Flash writing */
  SPI_FLASH_WaitForWriteEnd();
}

/*******************************************************************************
* Function Name  : SPI_FLASH_BufferWrite
* Description    : Writes block of data to the FLASH. In this function, the
*                  number of WRITE cycles are reduced, using Page WRITE sequence.
* Input          : - pBuffer : pointer to the buffer  containing the data to be
*                    written to the FLASH.
*                  - StartAddr : FLASH's internal address to write to.待写入的数据在Falsh内部的起始地址
*                  - NumByteToWrite : number of bytes to write to the FLASH.
* Output         : None
* Return         : None
*******************************************************************************/
void SPI_FLASH_BufferWrite(u8* pBuffer, u32 StartAddr, u16 NumByteToWrite)
{
  u8 NumOfPage = 0, NumOfSingle = 0, Addr = 0, count = 0, temp = 0;
	unsigned long	SPI_FLASH_PageSize	=	0;	//页大小byte单位
	unsigned long	WriteAddr	=	StartAddr;		//页大小byte单位
	
	SPI_FLASH_PageSize	=	FlashSYS->Memory.PageSize;
	
  Addr 				= WriteAddr % SPI_FLASH_PageSize;					//判断数据起始地址是否与页起始地址对齐，如果与页起始地址对齐，可以整页写
  count 			= SPI_FLASH_PageSize - Addr;							//计数写入地址与页地址的偏移，如果起始地址与页对齐，此时为0,否则为偏移值
  NumOfPage 	=	NumByteToWrite / SPI_FLASH_PageSize;		//计数页数---需要使用多少页空间
  NumOfSingle = NumByteToWrite % SPI_FLASH_PageSize;		//剩余数量--不到整页部分数据大小

  if (Addr == 0) 				/* StartAddr is SPI_FLASH_PageSize aligned  */	//写入的数据起始地址与页地址对齐
  {
    if (NumOfPage == 0) /* NumByteToWrite < SPI_FLASH_PageSize */				//总数据量不超过一页
    {
      SPI_FLASH_PageWrite(pBuffer, WriteAddr, NumByteToWrite);
    }
    else /* NumByteToWrite > SPI_FLASH_PageSize */
    {
      while (NumOfPage--)		//整页写入
      {
        SPI_FLASH_PageWrite(pBuffer, WriteAddr, SPI_FLASH_PageSize);
        WriteAddr +=  SPI_FLASH_PageSize;
        pBuffer += SPI_FLASH_PageSize;
      }

      SPI_FLASH_PageWrite(pBuffer, WriteAddr, NumOfSingle);	//写入剩余非整页数据
    }
  }
  else /* StartAddr is not SPI_FLASH_PageSize aligned  */		//起始地址未对齐
  {
    if (NumOfPage == 0) /* NumByteToWrite < SPI_FLASH_PageSize */
    {
      if (NumOfSingle > count) /* (NumByteToWrite + WriteAddr) > SPI_FLASH_PageSize */
      {
        temp = NumOfSingle - count;

        SPI_FLASH_PageWrite(pBuffer, WriteAddr, count);
        WriteAddr +=  count;
        pBuffer += count;

        SPI_FLASH_PageWrite(pBuffer, WriteAddr, temp);
      }
      else
      {
        SPI_FLASH_PageWrite(pBuffer, WriteAddr, NumByteToWrite);
      }
    }
    else /* NumByteToWrite > SPI_FLASH_PageSize */
    {
      NumByteToWrite -= count;
      NumOfPage =  NumByteToWrite / SPI_FLASH_PageSize;
      NumOfSingle = NumByteToWrite % SPI_FLASH_PageSize;

      SPI_FLASH_PageWrite(pBuffer, WriteAddr, count);
      WriteAddr +=  count;
      pBuffer += count;

      while (NumOfPage--)
      {
        SPI_FLASH_PageWrite(pBuffer, WriteAddr, SPI_FLASH_PageSize);
        WriteAddr +=  SPI_FLASH_PageSize;
        pBuffer += SPI_FLASH_PageSize;
      }

      if (NumOfSingle != 0)
      {
        SPI_FLASH_PageWrite(pBuffer, WriteAddr, NumOfSingle);
      }
    }
  }
}

/*******************************************************************************
* Function Name  : SPI_FLASH_BufferRead
* Description    : Reads a block of data from the FLASH.
* Input          : - pBuffer : pointer to the buffer that receives the data read
*                    from the FLASH.
*                  - ReadAddr : FLASH's internal address to read from.
*                  - NumByteToRead : number of bytes to read from the FLASH.
* Output         : None
* Return         : None
*******************************************************************************/
void SPI_FLASH_BufferRead(u8* pBuffer, u32 ReadAddr, u16 NumByteToRead)
{
  /* Select the FLASH: Chip Select low */
  SPI_CS_LOW(&FlashSYS->SPI);

  /* Send "Read from Memory " instruction */
  SPI_ReadWriteByteSPI(&FlashSYS->SPI,FlashSYS->Cmd.READ);

  /* Send ReadAddr high nibble address byte to read from */
  SPI_ReadWriteByteSPI(&FlashSYS->SPI,(ReadAddr & 0xFF0000) >> 16);
  /* Send ReadAddr medium nibble address byte to read from */
  SPI_ReadWriteByteSPI(&FlashSYS->SPI,(ReadAddr& 0xFF00) >> 8);
  /* Send ReadAddr low nibble address byte to read from */
  SPI_ReadWriteByteSPI(&FlashSYS->SPI,ReadAddr & 0xFF);

  while (NumByteToRead--) /* while there is data to be read */
  {
    /* Read a byte from the FLASH */
    *pBuffer = SPI_ReadWriteByteSPI(&FlashSYS->SPI,Dummy_Byte);
    /* Point to the next location where the byte read will be saved */
    pBuffer++;
  }

  /* Deselect the FLASH: Chip Select high */
  SPI_CS_HIGH(&FlashSYS->SPI);
}
/*******************************************************************************
* Function Name  : SPI_FLASH_StartReadSequence
* Description    : Initiates a read data byte (READ) sequence from the Flash.
*                  This is done by driving the /CS line low to select the device,
*                  then the READ instruction is transmitted followed by 3 bytes
*                  address. This function exit and keep the /CS line low, so the
*                  Flash still being selected. With this technique the whole
*                  content of the Flash is read with a single READ instruction.
* Input          : - ReadAddr : FLASH's internal address to read from.
* Output         : None
* Return         : None
*******************************************************************************/
void SPI_FLASH_StartReadSequence(u32 ReadAddr)
{
  /* Select the FLASH: Chip Select low */
  SPI_CS_LOW(&FlashSYS->SPI);

  /* Send "Read from Memory " instruction */
  SPI_ReadWriteByteSPI(&FlashSYS->SPI,FlashSYS->Cmd.READ);

  /* Send the 24-bit address of the address to read from -----------------------*/
  /* Send ReadAddr high nibble address byte */
  SPI_ReadWriteByteSPI(&FlashSYS->SPI,(ReadAddr & 0xFF0000) >> 16);
  /* Send ReadAddr medium nibble address byte */
  SPI_ReadWriteByteSPI(&FlashSYS->SPI,(ReadAddr& 0xFF00) >> 8);
  /* Send ReadAddr low nibble address byte */
  SPI_ReadWriteByteSPI(&FlashSYS->SPI,ReadAddr & 0xFF);
}
/*******************************************************************************
* Function Name  : SPI_FLASH_SetDeepPowerdown
* Description    : Deep Power-down.芯片进入深度省电模式后禁止读写和擦除操作
* Input          : None
* Output         : None
* Return         : FLASH identification
*******************************************************************************/
void SPI_FLASH_SetDeepPowerdown(void)
{

  /* Select the FLASH: Chip Select low */
  SPI_CS_LOW(&FlashSYS->SPI);

  /* Send "DP " instruction */
  SPI_ReadWriteByteSPI(&FlashSYS->SPI,FlashSYS->Cmd.DP);

  /* Deselect the FLASH: Chip Select high */
  SPI_CS_HIGH(&FlashSYS->SPI);

}
/*******************************************************************************
* Function Name  : SPI_FLASH_ResDeepPowerdown
* Description    : Release from Deep Power-down.退出深度省电模式
* Input          : None
* Output         : None
* Return         : FLASH identification
*******************************************************************************/
void SPI_FLASH_ResDeepPowerdown(void)
{

  /* Select the FLASH: Chip Select low */
  SPI_CS_LOW(&FlashSYS->SPI);

  /* Send "RDP " instruction */
  SPI_ReadWriteByteSPI(&FlashSYS->SPI,FlashSYS->Cmd.RDP);

  /* Deselect the FLASH: Chip Select high */
  SPI_CS_HIGH(&FlashSYS->SPI);

}
/*******************************************************************************
* Function Name  : SPI_FLASH_ReadSFDP
* Description    : Reads The Serial Flash Discoverable Parameter (SFDP).Serial Flash芯片规范
* Input          : None
* Output         : None
* Return         : FLASH identification
*******************************************************************************/
u32 SPI_FLASH_ReadRDSFDP(void)
{
  u32 Temp = 0, Temp0 = 0, Temp1 = 0;

  /* Select the FLASH: Chip Select low */
  SPI_CS_LOW(&FlashSYS->SPI);

  /* Send "RDSFDP " instruction */
  SPI_ReadWriteByteSPI(&FlashSYS->SPI,FlashSYS->Cmd.RDSFDP);

	/* Send "ADD1 "  */
	SPI_ReadWriteByteSPI(&FlashSYS->SPI,0x00);
	
	/* Send "ADD2 "  */
	SPI_ReadWriteByteSPI(&FlashSYS->SPI,0x00);
	
	/* Send "ADD3 "  */
	SPI_ReadWriteByteSPI(&FlashSYS->SPI,0x00);
	
	/* Send one dummy bytes---Byte1 */
	SPI_ReadWriteByteSPI(&FlashSYS->SPI,Dummy_Byte);
	
  /* Read Data1 from the FLASH */
  Temp0 = SPI_ReadWriteByteSPI(&FlashSYS->SPI,Dummy_Byte);

  /* Read Data2 from the FLASH */
  Temp1 = SPI_ReadWriteByteSPI(&FlashSYS->SPI,Dummy_Byte);

  /* Deselect the FLASH: Chip Select high */
  SPI_CS_HIGH(&FlashSYS->SPI);

  Temp = (Temp0 << 8) | Temp1;

  return Temp;
}
/*******************************************************************************
* Function Name  : SPI_FLASH_ReadID
* Description    : Reads FLASH identification.
* Input          : None
* Output         : None
* Return         : FLASH identification
*******************************************************************************/
u32 SPI_FLASH_ReadID(void)
{
  u32 Temp = 0, Temp0 = 0, Temp1 = 0, Temp2 = 0;

  /* Select the FLASH: Chip Select low */
  SPI_CS_LOW(&FlashSYS->SPI);

  /* Send "RDID " instruction */
  SPI_ReadWriteByteSPI(&FlashSYS->SPI,FlashSYS->Cmd.RDID);

  /* Read a byte from the FLASH */
  Temp0 = SPI_ReadWriteByteSPI(&FlashSYS->SPI,Dummy_Byte);

  /* Read a byte from the FLASH */
  Temp1 = SPI_ReadWriteByteSPI(&FlashSYS->SPI,Dummy_Byte);

  /* Read a byte from the FLASH */
  Temp2 = SPI_ReadWriteByteSPI(&FlashSYS->SPI,Dummy_Byte);

  /* Deselect the FLASH: Chip Select high */
  SPI_CS_HIGH(&FlashSYS->SPI);

  Temp = (Temp0 << 16) | (Temp1 << 8) | Temp2;

  return Temp;
}
/*******************************************************************************
* Function Name  : SPI_FLASH_ReadREMS 读书制造商信息和ID
* Description    : Read Electronic Manufacturer ID & Device ID (REMS).
* Input          : None
* Output         : None
* Return         : FLASH identification
*******************************************************************************/
u32 SPI_FLASH_ReadREMS(void)
{
  u16 Temp = 0, Temp0 = 0, Temp1 = 0;

  /* Select the FLASH: Chip Select low */
  SPI_CS_LOW(&FlashSYS->SPI);

  /* Send "REMS " instruction */
  SPI_ReadWriteByteSPI(&FlashSYS->SPI,FlashSYS->Cmd.REMS);

  /* Send two dummy bytes---Byte1 */
	SPI_ReadWriteByteSPI(&FlashSYS->SPI,Dummy_Byte);

  /* Send two dummy bytes---Byte2 */
	SPI_ReadWriteByteSPI(&FlashSYS->SPI,Dummy_Byte);

	/* Send one bytes address (A7~A0). 发送0x00,manufacturer ID先出;发送0x01，device ID先出*/
	SPI_ReadWriteByteSPI(&FlashSYS->SPI,0X00);
	
	/* Read a byte from the FLASH */
  Temp0 = SPI_ReadWriteByteSPI(&FlashSYS->SPI,Dummy_Byte);

  /* Read a byte from the FLASH */
  Temp1 = SPI_ReadWriteByteSPI(&FlashSYS->SPI,Dummy_Byte);

  /* Deselect the FLASH: Chip Select high */
  SPI_CS_HIGH(&FlashSYS->SPI);

  Temp = (Temp0 << 8) | Temp1;

  return Temp;
}
/*******************************************************************************
* Function Name  : SPI_FLASH_ReadStatusRegister 
* Description    : Read Status Register (RDSR).读状态寄存器
* Input          : None
* Output         : None
* Return         : FLASH identification
*******************************************************************************/
u32 SPI_FLASH_ReadStatusRegister(void)
{
  u8 Temp = 0;

  /* Select the FLASH: Chip Select low */
  SPI_CS_LOW(&FlashSYS->SPI);

  /* Send "REMS " instruction */
  SPI_ReadWriteByteSPI(&FlashSYS->SPI,FlashSYS->Cmd.RDSR);

	/* Read a byte from the FLASH */
  Temp = SPI_ReadWriteByteSPI(&FlashSYS->SPI,Dummy_Byte);

  /* Deselect the FLASH: Chip Select high */
  SPI_CS_HIGH(&FlashSYS->SPI);

	memcpy((unsigned char*)&FlashSYS->Flag,&Temp,1);
	
  return Temp;
}
/*******************************************************************************
* Function Name  : SPI_FLASH_ReadStatusRegister 
* Description    : Read Status Register (RDSR).读状态寄存器
* Input          : None
* Output         : None
* Return         : FLASH identification
*******************************************************************************/
void SPI_FLASH_WriteStatusRegister(SPIFlashStatusDef Flag)
{
	u8 Status	=	0;
	
  FlashSYS->Flag 	=	Flag;
	memcpy((unsigned char*)&Status,(unsigned char*)&Flag,1);
	
  /* Select the FLASH: Chip Select low */
  SPI_CS_LOW(&FlashSYS->SPI);

  /* Send "WRSR " instruction */
  SPI_ReadWriteByteSPI(&FlashSYS->SPI,FlashSYS->Cmd.WRSR);

	/* Send "Status " to the FLASH */
	SPI_ReadWriteByteSPI(&FlashSYS->SPI,Status);

  /* Deselect the FLASH: Chip Select high */
  SPI_CS_HIGH(&FlashSYS->SPI);
}

/*******************************************************************************
* Function Name  : SPI_FLASH_WriteEnable
* Description    : Enables the write access to the FLASH.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SPI_FLASH_WriteEnable(void)
{
	SPI_CS_LOW(&FlashSYS->SPI);
	SPI_ReadWriteByteSPI(&FlashSYS->SPI,FlashSYS->Cmd.WREN);
	SPI_CS_HIGH(&FlashSYS->SPI);
}
/*******************************************************************************
* Function Name  : SPI_FLASH_WriteDisble
* Description    : Disables the write access to the FLASH.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SPI_FLASH_WriteDisble(void)
{
	SPI_CS_LOW(&FlashSYS->SPI);
	SPI_ReadWriteByteSPI(&FlashSYS->SPI,FlashSYS->Cmd.WRDI);
	SPI_CS_HIGH(&FlashSYS->SPI);
}
/*******************************************************************************
* Function Name  : SPI_FLASH_WaitForWriteEnd
* Description    : Polls the status of the Write In Progress (WIP) flag in the
*                  FLASH's status  register  and  loop  until write  opertaion
*                  has completed.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SPI_FLASH_WaitForWriteEnd(void)
{
  u8 FLASH_Status = 0;
	unsigned long Time	=	720000;

  /* Select the FLASH: Chip Select low */
  SPI_CS_LOW(&FlashSYS->SPI);

  /* Send "Read Status Register" instruction */
  SPI_ReadWriteByteSPI(&FlashSYS->SPI,FlashSYS->Cmd.RDSR);

  /* Loop as long as the memory is busy with a write cycle */
  do
  {
    /* Send a dummy byte to generate the clock needed by the FLASH
    and put the value of the status register in FLASH_Status variable */
    FLASH_Status = SPI_ReadWriteByteSPI(&FlashSYS->SPI,Dummy_Byte);
  }
  while (((FLASH_Status & WIP_Flag) == SET)&&(Time--)); /* Write in progress */
  /* Deselect the FLASH: Chip Select high */
  SPI_CS_HIGH(&FlashSYS->SPI);
}

/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/
