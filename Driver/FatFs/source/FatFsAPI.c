/*----------------------------------------------------------------------------/
/  FatFs - Generic FAT Filesystem Module  R0.13b                              /
/-----------------------------------------------------------------------------/
/ 文件数名	  :	FatFsAPI
/ 功能描述		:	FatFs接口管理
/ 修改时间		:	无
/ 修改说明		:	无
/ 注释		  :	wegam@sina.com
/
/----------------------------------------------------------------------------*/
#include "FatFsAPI.h"			/* 自定义API接口*/




SPIDef	sSDFatFsPort;

/*******************************************************************************
*函数名			:	SD_disk_initialize
*功能描述		:	SD卡的硬件配置及初始化
*输入				: 无
*返回值			:	0：正常
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
int SD_disk_initialize(void)
{ 
  unsigned char result  = 0;
  //========================硬件接口配置
  sSDFatFsPort.Port.SPIx = SPI1;
  sSDFatFsPort.Port.CS_PORT  = GPIOC;
  sSDFatFsPort.Port.CS_Pin   = GPIO_Pin_6;
  sSDFatFsPort.Port.SPI_BaudRatePrescaler_x=SPI_BaudRatePrescaler_256;
  //========================初始化SD卡
  result  = SD_Initialize(&sSDFatFsPort);

  return result;
}
/*******************************************************************************
*函数名			:	function
*功能描述		:	function
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
int SD_disk_status(void)
{
  unsigned char result  = 0;
  return result;
}
/*******************************************************************************
*函数名			:	function
*功能描述		:	function
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
int SD_disk_read(BYTE *buff,DWORD sector,UINT count)
{
  unsigned char result  = 0;
  result  = SD_ReadDisk(buff,sector,count);
  return result;
}

/*******************************************************************************
*函数名			:	function
*功能描述		:	function
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
int SD_disk_write(const BYTE *buff,DWORD sector,UINT count)
{
  unsigned char result  = 0;
  
  return result;
}
/*******************************************************************************
*函数名			:	获取磁盘的总容量和剩余容量
*功能描述		:	exf_getfree
*输入				: drv:磁盘编号("0:"/"1:")
              total:总容量地址	 （单位KB）
              free:剩余容量地址	 （单位KB）
*返回值			:	返回值:0,正常.其他,错误代码
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
unsigned char SD_disk_getcapacity(unsigned char *drv,unsigned long *total,unsigned long *free)
{
	FATFS *fs1;
	u8 res;
  u32 fre_clust=0, fre_sect=0, tot_sect=0;
  //========================得到磁盘信息及空闲簇数量
  res =(u32)f_getfree((const TCHAR*)drv, (DWORD*)&fre_clust, &fs1);
  if(res==0)
	{											   
	    tot_sect=(fs1->n_fatent-2)*fs1->csize;	//得到总扇区数
	    fre_sect=fre_clust*fs1->csize;			    //得到空闲扇区数	   
#if FF_MAX_SS!=512				  				          //扇区大小不是512字节,则转换为512字节
		tot_sect*=fs1->ssize/512;
		fre_sect*=fs1->ssize/512;
#endif	  
		*total=tot_sect>>1;	//总容量单位为KB
		*free=fre_sect>>1;	//剩余容量单位为KB 
 	}
	return res;
}











