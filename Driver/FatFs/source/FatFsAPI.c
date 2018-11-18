/*----------------------------------------------------------------------------/
/  FatFs - Generic FAT Filesystem Module  R0.13b                              /
/-----------------------------------------------------------------------------/
/ �ļ�����	  :	FatFsAPI
/ ��������		:	FatFs�ӿڹ���
/ �޸�ʱ��		:	��
/ �޸�˵��		:	��
/ ע��		  :	wegam@sina.com
/
/----------------------------------------------------------------------------*/
#include "FatFsAPI.h"			/* �Զ���API�ӿ�*/




SPIDef	sSDFatFsPort;

/*******************************************************************************
*������			:	SD_disk_initialize
*��������		:	SD����Ӳ�����ü���ʼ��
*����				: ��
*����ֵ			:	0������
*�޸�ʱ��		:	��
*�޸�˵��		:	��
*ע��				:	wegam@sina.com
*******************************************************************************/
int SD_disk_initialize(void)
{ 
  unsigned char result  = 0;
  //========================Ӳ���ӿ�����
  sSDFatFsPort.Port.SPIx = SPI2;
  sSDFatFsPort.Port.CS_PORT  = GPIOG;
  sSDFatFsPort.Port.CS_Pin   = GPIO_Pin_6;
  sSDFatFsPort.Port.SPI_BaudRatePrescaler_x=SPI_BaudRatePrescaler_256;
  //========================��ʼ��SD��
  result  = SD_Initialize(&sSDFatFsPort);

  return result;
}
/*******************************************************************************
*������			:	function
*��������		:	function
*����				: 
*����ֵ			:	��
*�޸�ʱ��		:	��
*�޸�˵��		:	��
*ע��				:	wegam@sina.com
*******************************************************************************/
int SD_disk_status(void)
{
  unsigned char result  = 0;
  return result;
}
/*******************************************************************************
*������			:	function
*��������		:	function
*����				: 
*����ֵ			:	��
*�޸�ʱ��		:	��
*�޸�˵��		:	��
*ע��				:	wegam@sina.com
*******************************************************************************/
int SD_disk_read(BYTE *buff,DWORD sector,UINT count)
{
  unsigned char result  = 0;
  result  = SD_ReadDisk(buff,sector,count);
  return result;
}

/*******************************************************************************
*������			:	function
*��������		:	function
*����				: 
*����ֵ			:	��
*�޸�ʱ��		:	��
*�޸�˵��		:	��
*ע��				:	wegam@sina.com
*******************************************************************************/
int SD_disk_write(const BYTE *buff,DWORD sector,UINT count)
{
  unsigned char result  = 0;
  result  = SD_WriteDisk((u8*)buff,sector,count);   //��SD��д����
  return result;
}
/*******************************************************************************
*������			:	ByteCmp
*��������		:	�ֽڱȽ�
*����				: a,b
*����ֵ			:	����ֵ:FALSE,����ͬ.TRUE,��ͬ
*�޸�ʱ��		:	��
*�޸�˵��		:	��
*ע��				:	wegam@sina.com
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
*������			:	SD_disk_getcapacity
*��������		:	��ȡ���̵���������ʣ������
*����				: drv:���̱��("0:"/"1:")
              total:��������ַ	 ����λKB��
              free:ʣ��������ַ	 ����λKB��
*����ֵ			:	����ֵ:0,����.����,�������
*�޸�ʱ��		:	��
*�޸�˵��		:	��
*ע��				:	wegam@sina.com
*******************************************************************************/
unsigned char SD_disk_getcapacity(unsigned char *drv,unsigned long *total,unsigned long *free)
{
	FATFS *fs1;         //�ļ�ϵͳ����ṹ��
	u8 res;
  u32 fre_clust=0;    /* �洢���д���Ŀ������ָ�� */
  u32 fre_sect=0;
  u32 tot_sect=0;
  //========================�õ�������Ϣ�����д�����
  res =(u32)f_getfree((const TCHAR*)drv, (DWORD*)&fre_clust, &fs1);
  if(res==0)
	{											   
	    tot_sect=(fs1->n_fatent-2)*fs1->csize;	//�õ���������
	    fre_sect=fre_clust*fs1->csize;			    //�õ�����������	   
#if FF_MAX_SS!=512				  				          //������С����512�ֽ�,��ת��Ϊ512�ֽ�
		tot_sect*=fs1->ssize/512;
		fre_sect*=fs1->ssize/512;
#endif	  
		*total=tot_sect>>1;	//��������λΪKB
		*free=fre_sect>>1;	//ʣ��������λΪKB 
 	}
	return res;
}
/*******************************************************************************
*������			:	mf_open
*��������		:	��·���µ��ļ�
*����				: path:·��+�ļ���
              mode:��ģʽ
*����ֵ			:	����ֵ:ִ�н��
*�޸�ʱ��		:	��
*�޸�˵��		:	��
*ע��				:	wegam@sina.com
*******************************************************************************/
//unsigned char mf_open(u8*path,u8 mode)
//{
//	u8 res;	 
//	res=f_open(file,(const TCHAR*)path,mode);//���ļ���
//	return res;
//} 
/*******************************************************************************
*������			:	FilSearch
*��������		:	��ָ��·���²���ָ����չ�����ļ�������¼��(*p)[13]�����У�ע������¼����
*����				: fs
              dir
              path Ҫ�������ļ�·��
              name Ҫ�������ļ���չ��
              (*p)[13] ���������ŵ�ַ
*����ֵ			:	���������TRUE �ɹ� FALSE ����
*�޸�ʱ��		:	��
*�޸�˵��		:	��
*ע��				:	wegam@sina.com
*******************************************************************************/
bool FilSearch(FATFS *fs,DIR *dir,TCHAR *path,u8 *name,char (*p)[13])
{ 
  //===========δ��֤
  FILINFO fno;
  FRESULT res;
  u8 i,j,k;
  j = k = 0;
  res = f_opendir(dir,path);    //����Ŀ¼���󼰻�ȡ��ز���
  if(res != FR_OK)
    return FALSE;
  do
  {
    res = f_readdir(dir,&fno);  //��˳���ȡĿ¼��Ŀ�����ļ���Ϣ
    if(res != FR_OK)
      return FALSE;
//    if(fno.fname[0] == 0)
//      return TRUE; 
    i = 13;   //�����ļ���Ϣ�洢����
    while(--i)
    {
      if((fno.fname[i] == 0x2E) && (ByteCmp(fno.fname[i+1],name[0]) && ByteCmp(fno.fname[i+2],name[1]) && ByteCmp(fno.fname[i+3],name[2])))
        break;    
    }
    if(i) //������һ��������չ���������ļ�
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
///**************************����*************************/
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
*������			:	FATFS_ScanFiles
*��������		:	��ȡָ���ļ��������ļ������ֺͺ�׺
*����				: fs
              dir
              path Ҫ�������ļ�·��
              name Ҫ�������ļ���չ��
              (*p)[13] ���������ŵ�ַ
*����ֵ			:	���������TRUE �ɹ� FALSE ����
*�޸�ʱ��		:	��
*�޸�˵��		:	��
*ע��				:	wegam@sina.com
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
//  /* ���ļ��� */
//  res = f_opendir(&dirs, (const TCHAR*)dir);
//  if (res == FR_OK) //�ɹ����ļ���
//  {
//    while (f_readdir(&dirs, &fileInfo) == FR_OK) //����˳����ļ���
//    {
//      if(!fileInfo.fname[0]) //����ļ���Ϊ 0,����
//      {
//        break;
//      }
//    /* �ж��ļ����� */
//      if((fileInfo.fattrib == AM_ARC)|(fileInfo.fattrib == AM_DIR))
//      {
//#if FF_USE_LFN //Ϊ���ַ�����׼��
//        fn = *fileInfo.lfname ? fileInfo.lfname : fileInfo.fname;
//#else
//        fn = fileInfo.fname;
//#endif
//        //============��ȡ���� */
//        i = 0;
//        while((*fn != '.') && (*fn != '\0')) //��һ������������ѭ��
//        {
//          file->name[i] = *fn;
//          i++;
//          fn++; 
//        }
//        file->fname[i] = '\0';
//        //============��ȡ��׺ */
//        i = 0;
//        while(*fn != '\0')
//        {
//          file->type[i] = *fn;
//          i++;
//          fn++;
//        }
//        file->type[i] = '\0';
//        file++;
//      }//end of �ļ������ж���
//    } //end of while (f_readdir(&dirs, &fileInfo) == FR_OK)//����˳����ļ���
//  }
//  return res;
//}








