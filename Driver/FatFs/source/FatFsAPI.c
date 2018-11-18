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
  sSDFatFsPort.Port.SPIx = SPI2;
  sSDFatFsPort.Port.CS_PORT  = GPIOG;
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
  result  = SD_WriteDisk((u8*)buff,sector,count);   //往SD卡写数据
  return result;
}
/*******************************************************************************
*函数名			:	ByteCmp
*功能描述		:	字节比较
*输入				: a,b
*返回值			:	返回值:FALSE,不相同.TRUE,相同
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
bool ByteCmp(char a,char b)
{
  if(a==b)
    return TRUE;
  if((a>='a')&&(a<='z'))
  {
    if(a-32==b)
      return TRUE;
  }
  if((b>='a')&&(b<='z'))
  {
    if(b-32==a)
      return TRUE;
  }
  return FALSE;
}
/*******************************************************************************
*函数名			:	SD_disk_getcapacity
*功能描述		:	获取磁盘的总容量和剩余容量
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
	FATFS *fs1;         //文件系统对象结构体
	u8 res;
  u32 fre_clust=0;    /* 存储空闲簇数目变量的指针 */
  u32 fre_sect=0;
  u32 tot_sect=0;
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
/*******************************************************************************
*函数名			:	mf_open
*功能描述		:	打开路径下的文件
*输入				: path:路径+文件名
              mode:打开模式
*返回值			:	返回值:执行结果
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
//unsigned char mf_open(u8*path,u8 mode)
//{
//	u8 res;	 
//	res=f_open(file,(const TCHAR*)path,mode);//打开文件夹
//	return res;
//} 
/*******************************************************************************
*函数名			:	FilSearch
*功能描述		:	在指定路径下查找指定扩展名的文件，并记录在(*p)[13]数组中，注意最大记录条数
*输入				: fs
              dir
              path 要检索的文件路径
              name 要检索的文件扩展名
              (*p)[13] 检索结果存放地址
*返回值			:	输出参数：TRUE 成功 FALSE 出错
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
bool FilSearch(FATFS *fs,DIR *dir,TCHAR *path,u8 *name,char (*p)[13])
{ 
  //===========未验证
  FILINFO fno;
  FRESULT res;
  u8 i,j,k;
  j = k = 0;
  res = f_opendir(dir,path);    //创建目录对象及获取相关参数
  if(res != FR_OK)
    return FALSE;
  do
  {
    res = f_readdir(dir,&fno);  //按顺序读取目录条目及将文件信息
    if(res != FR_OK)
      return FALSE;
//    if(fno.fname[0] == 0)
//      return TRUE; 
    i = 13;   //单个文件信息存储长度
    while(--i)
    {
      if((fno.fname[i] == 0x2E) && (ByteCmp(fno.fname[i+1],name[0]) && ByteCmp(fno.fname[i+2],name[1]) && ByteCmp(fno.fname[i+3],name[2])))
        break;    
    }
    if(i) //检索到一个符合扩展名条件的文件
    {
      for(k =0;k < 13;k++) 
        *(*(p+j)+k) = fno.fname[k];
      j++; 
//      return TRUE;
    }
//    else
//      return FALSE;
  }while(!res && fno.fname[0] != 0);
  return TRUE;
}
///**************************函数*************************/
//u8 fileNum;
//u8 fileName[32][32];
//FILINFO finfo;
//#define _MAX_LFN 30
//#define _MAX_LFN 32
//void scanfile(const TCHAR *path)
//{
//  DIR dirs;
//  char curdirpath[_MAX_LFN],nextdirpath[_MAX_LFN];
//  if (f_opendir(&dirs, path) == FR_OK) 
//  {
//    while (f_readdir(&dirs, &finfo) == FR_OK) 
//    {
//      if(!finfo.fname[0]) 
//        break;
//      if(finfo.fname[0]=='.' || (finfo.fname[0]=='.' && finfo.fname[1]=='.'))
//        continue;

//      if(fileNum<32)
//        strncpy(fileName[fileNum++] ,*finfo.lfname ? finfo.lfname : finfo.fname,32);
//      f_getcwd(curdirpath,_MAX_LFN);
//      if((finfo.fattrib&AM_DIR) == AM_DIR)
//      { 
//        f_getcwd(curdirpath,_MAX_LFN);
//        strcpy(nextdirpath, curdirpath);
//        strcat(nextdirpath,"/");
//        strncat(nextdirpath, *finfo.lfname ? finfo.lfname : finfo.fname, 32); 

//        f_chdir(nextdirpath);
//        scanfile(nextdirpath);

//        f_chdir(curdirpath);
//      }
//    }
//  }
//}
/*******************************************************************************
*函数名			:	FATFS_ScanFiles
*功能描述		:	读取指定文件下所有文件的名字和后缀
*输入				: fs
              dir
              path 要检索的文件路径
              name 要检索的文件扩展名
              (*p)[13] 检索结果存放地址
*返回值			:	输出参数：TRUE 成功 FALSE 出错
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
//unsigned char FATFS_ScanFiles(DIR *dir, FILINFO *file)
//{
//  FRESULT res;
//  FILINFO fileInfo;
//  DIR dirs;
//  char *fn, i = 0;
// #if FF_USE_LFN
//  static char lfn[FF_MAX_LFN + 1]; /* Buffer to store the LFN */
//  fileInfo.lfname = lfn;
//  fileInfo.lfsize = sizeof(lfn);
//#endif
//  /* 打开文件夹 */
//  res = f_opendir(&dirs, (const TCHAR*)dir);
//  if (res == FR_OK) //成功打开文件夹
//  {
//    while (f_readdir(&dirs, &fileInfo) == FR_OK) //按照顺序读文件夹
//    {
//      if(!fileInfo.fname[0]) //如果文件名为 0,结束
//      {
//        break;
//      }
//    /* 判断文件属性 */
//      if((fileInfo.fattrib == AM_ARC)|(fileInfo.fattrib == AM_DIR))
//      {
//#if FF_USE_LFN //为长字符串名准备
//        fn = *fileInfo.lfname ? fileInfo.lfname : fileInfo.fname;
//#else
//        fn = fileInfo.fname;
//#endif
//        //============读取名字 */
//        i = 0;
//        while((*fn != '.') && (*fn != '\0')) //有一个成立就跳出循环
//        {
//          file->name[i] = *fn;
//          i++;
//          fn++; 
//        }
//        file->fname[i] = '\0';
//        //============读取后缀 */
//        i = 0;
//        while(*fn != '\0')
//        {
//          file->type[i] = *fn;
//          i++;
//          fn++;
//        }
//        file->type[i] = '\0';
//        file++;
//      }//end of 文件属性判断呢
//    } //end of while (f_readdir(&dirs, &fileInfo) == FR_OK)//按照顺序读文件夹
//  }
//  return res;
//}








