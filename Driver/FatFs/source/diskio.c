/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for FatFs     (C)ChaN, 2016        */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various exsisting      */
/* storage control modules to the FatFs module with a defined API.       */
/*-----------------------------------------------------------------------*/

#include "diskio.h"		  /* FatFs lower layer API */
#include "FatFsAPI.h"	  /* 自定义API接口*/

/* Definitions of physical drive number for each drive */
#define DEV_RAM		0	/* Example: Map Ramdisk to physical drive 0 */
#define DEV_MMC		1	/* Example: Map MMC/SD card to physical drive 1 */
#define DEV_USB		2	/* Example: Map USB MSD to physical drive 2 */


/*-----------------------------------------------------------------------*/
/* Get Drive Status                                                      */
/*-----------------------------------------------------------------------*/
//====================添加__weak占位函数START20180825
//-------------------disk_status
//__weak int RAM_disk_status(void)
//{
//  return 0;
//}
__weak int MMC_disk_status(void)
{
  return 0;
}
__weak int USB_disk_status(void)
{
  return 0;
}
//-------------------disk_initialize
//__weak int RAM_disk_initialize(void)
//{
//  return 0;
//}
__weak int MMC_disk_initialize(void)
{
  return 0;
}
__weak int USB_disk_initialize(void)
{
  return 0;
}
//-------------------disk_read
//__weak int RAM_disk_read(BYTE *buff,DWORD sector,UINT count)
//{
//  return 0;
//}
__weak int MMC_disk_read(BYTE *buff,DWORD sector,UINT count)
{
  return 0;
}
__weak int USB_disk_read(BYTE *buff,DWORD sector,UINT count)
{
  return 0;
}
//-------------------disk_write
//__weak int RAM_disk_write(const BYTE *buff,DWORD sector,UINT count)
//{
//  return 0;
//}
__weak int MMC_disk_write(const BYTE *buff,DWORD sector,UINT count)
{
  return 0;
}
__weak int USB_disk_write(const BYTE *buff,DWORD sector,UINT count)
{
  return 0;
}
//====================添加__weak占位函数END
DSTATUS disk_status (
	BYTE pdrv		/* Physical drive nmuber to identify the drive */
)
{
	DSTATUS stat;
	int result;

	switch (pdrv) {
	case DEV_RAM :
//		result = RAM_disk_status();
    
		// translate the reslut code here
    result = SD_disk_status();
		return stat;

	case DEV_MMC :
		result = MMC_disk_status();

		// translate the reslut code here

		return stat;

	case DEV_USB :
		result = USB_disk_status();

		// translate the reslut code here

		return stat;
	}
	return STA_NOINIT;
}



/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                                                    */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize (
	BYTE pdrv				/* Physical drive nmuber to identify the drive */
)
{
	DSTATUS stat;
	int result;

	switch (pdrv)
  {
	case DEV_RAM :
//		result = RAM_disk_initialize();
    

    // translate the reslut code here
    result = SD_disk_initialize();

		return stat;

	case DEV_MMC :
		result = MMC_disk_initialize();

		// translate the reslut code here

		return stat;

	case DEV_USB :
		result = USB_disk_initialize();

		// translate the reslut code here

		return stat;
	}
	return STA_NOINIT;
}



/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/
/*******************************************************************************
*函数名			:	Read Sector(s) 
*功能描述		:	读扇区               
*输入				: BYTE pdrv--要读取的物理驱动器号（磁盘号）
              buff--读取的数据缓存
              sector--待读取的起始扇区号
              count --待读取的扇区个数
*返回值			:	
*修改时间		:	无
*修改说明		:	无
*应用举例		: 
              
*注释				:	wegam@sina.com
*******************************************************************************/
DRESULT disk_read (
	BYTE pdrv,		/* Physical drive nmuber to identify the drive */
	BYTE *buff,		/* Data buffer to store read data */
	DWORD sector,	/* Start sector in LBA */
	UINT count		/* Number of sectors to read */
)
{
	DRESULT res;
	int result;

	switch (pdrv) {
	case DEV_RAM :
    // translate the reslut code here
//		result = RAM_disk_read(buff, sector, count);

		// translate the reslut code here
    result = SD_disk_read(buff, sector, count);

		return res;

	case DEV_MMC :
		// translate the arguments here

		result = MMC_disk_read(buff, sector, count);

		// translate the reslut code here

		return res;

	case DEV_USB :
		// translate the arguments here

		result = USB_disk_read(buff, sector, count);

		// translate the reslut code here

		return res;
	}

	return RES_PARERR;
}



/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/
/*******************************************************************************
*函数名			:	Write Sector(s)
*功能描述		:	写入扇区               
*输入				: BYTE pdrv--要写入的物理驱动器号（磁盘号）
              buff--数据缓存
              sector--待写入的起始扇区号
              count --待写入的扇区个数
*返回值			:	
*修改时间		:	无
*修改说明		:	无
*应用举例		: 
              
*注释				:	wegam@sina.com
*******************************************************************************/
DRESULT disk_write (
                    BYTE pdrv,			  /* Physical drive nmuber to identify the drive */
                    const BYTE *buff,	/* Data to be written */
                    DWORD sector,		  /* Start sector in LBA */
                    UINT count			  /* Number of sectors to write */
)
{
	DRESULT res;
	int result;

	switch (pdrv) {
	case DEV_RAM :
		// translate the arguments here

//		result = RAM_disk_write(buff, sector, count);

		// translate the reslut code here
    result = SD_disk_write(buff, sector, count);
		return res;

	case DEV_MMC :
		// translate the arguments here

		result = MMC_disk_write(buff, sector, count);

		// translate the reslut code here

		return res;

	case DEV_USB :
		// translate the arguments here

		result = USB_disk_write(buff, sector, count);

		// translate the reslut code here

		return res;
	}

	return RES_PARERR;
}



/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

DRESULT disk_ioctl (
	BYTE pdrv,  /* Physical drive nmuber (0..) */
	BYTE cmd,		/* Control code */
	void *buff  /* Buffer to send/receive control data */
)
{
	DRESULT res;
	int result;

	switch (pdrv) {
	case DEV_RAM :

		// Process of the command for the RAM drive

		return res;

	case DEV_MMC :

		// Process of the command for the MMC/SD card

		return res;

	case DEV_USB :

		// Process of the command the USB drive

		return res;
	}

	return RES_PARERR;
}

