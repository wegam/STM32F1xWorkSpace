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
  sSDFatFsPort.Port.SPIx = SPI1;
  sSDFatFsPort.Port.CS_PORT  = GPIOC;
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
  
  return result;
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
	FATFS *fs1;
	u8 res;
  u32 fre_clust=0, fre_sect=0, tot_sect=0;
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
  res = f_opendir(dir,path);
  if(res != FR_OK)
    return FALSE;
  do
  {
    res = f_readdir(dir,&fno);
    if(res != FR_OK)
      return FALSE;
    if(fno.fname[0] == 0)
      return TRUE; 
    i = 13;
    while(--i)
    {
      if((fno.fname[i] == 0x2E) && (fno.fname[i+1] == name[0] && fno.fname[i+2] == name[1] && fno.fname[i+3] == name[2]))
        break;
    }
    if(i) //������һ��������չ���������ļ�
    {
      for(k =0;k < 13;k++) 
        *(*(p+j)+k) = fno.fname[k];
      j++; 
    }
    else
      return FALSE;
  }while(!res && fno.fname[0] != 0);
  return FALSE;
}











