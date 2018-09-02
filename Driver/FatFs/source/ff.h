/*----------------------------------------------------------------------------/
/  FatFs - Generic FAT Filesystem module  R0.13b                              /
/-----------------------------------------------------------------------------/
/
/ Copyright (C) 2018, ChaN, all right reserved.
/
/ FatFs module is an open source software. Redistribution and use of FatFs in
/ source and binary forms, with or without modification, are permitted provided
/ that the following condition is met:

/ 1. Redistributions of source code must retain the above copyright notice,
/    this condition and the following disclaimer.
/
/ This software is provided by the copyright holder and contributors "AS IS"
/ and any warranties related to this software are DISCLAIMED.
/ The copyright owner or contributors be NOT LIABLE for any damages caused
/ by use of this software.
/
/----------------------------------------------------------------------------*/


#ifndef FF_DEFINED
#define FF_DEFINED	63463	/* Revision ID */

#ifdef __cplusplus
extern "C" {
#endif

#include "integer.h"	/* Basic integer types */
#include "ffconf.h"		/* FatFs configuration options */

#if FF_DEFINED != FFCONF_DEF
#error Wrong configuration file (ffconf.h).
#endif



/* Definitions of volume management */

#if FF_MULTI_PARTITION		/* Multiple partition configuration */
typedef struct {
	BYTE pd;	/* Physical drive number */
	BYTE pt;	/* Partition: 0:Auto detect, 1-4:Forced partition) */
} PARTITION;
extern PARTITION VolToPart[];	/* Volume - Partition resolution table */
#endif

#if FF_STR_VOLUME_ID
#ifndef FF_VOLUME_STRS
extern const char* VolumeStr[FF_VOLUMES];	/* User defied volume ID */
#endif
#endif



/* Type of path name strings on FatFs API */

#ifndef _INC_TCHAR
#define _INC_TCHAR

#if FF_USE_LFN && FF_LFN_UNICODE == 1 	/* Unicode in UTF-16 encoding */
typedef WCHAR TCHAR;
#define _T(x) L ## x
#define _TEXT(x) L ## x
#elif FF_USE_LFN && FF_LFN_UNICODE == 2	/* Unicode in UTF-8 encoding */
typedef char TCHAR;
#define _T(x) u8 ## x
#define _TEXT(x) u8 ## x
#elif FF_USE_LFN && FF_LFN_UNICODE == 3	/* Unicode in UTF-32 encoding */
typedef DWORD TCHAR;
#define _T(x) U ## x
#define _TEXT(x) U ## x
#elif FF_USE_LFN && (FF_LFN_UNICODE < 0 || FF_LFN_UNICODE > 3)
#error Wrong FF_LFN_UNICODE setting
#else									/* ANSI/OEM code in SBCS/DBCS */
typedef char TCHAR;
#define _T(x) x
#define _TEXT(x) x
#endif

#endif



/* Type of file size variables */

#if FF_FS_EXFAT
typedef QWORD FSIZE_t;
#else
typedef DWORD FSIZE_t;
#endif


//=========================�ļ�ϵͳ����ṹ��
/* Filesystem object structure (FATFS) */
typedef struct 
{
	BYTE	fs_type;		/* Filesystem type (0:N/A) */   //FAT�����ͣ�һ����mountʱ�ã���0��ʾδ����
	BYTE	pdrv;			  /* Physical drive number */     //�����������ţ�һ��Ϊ0
	BYTE	n_fats;			/* Number of FATs (1 or 2) */   //�ļ���������Ŀ(1,2) ��FAT�ļ�ϵͳ����Ϊ�����������������ļ��������Ŀ¼����������
	BYTE	wflag;			/* win[] flag (b0:dirty) */     //����ļ��Ƿ񱻸Ķ�����Ϊ1ʱҪ��д
	BYTE	fsi_flag;		/* FSINFO flags (b7:disabled, b0:dirty) */  //����ļ�ϵͳ��Ϣ�Ƿ񱻸Ķ�����Ϊ1ʱҪ��д
	WORD	id;				  /* Volume mount ID */                       //�ļ�ϵͳ����ID
	WORD	n_rootdir;  /* Number of root directory entries (FAT12/16) */ //��Ŀ¼�����(Ŀ¼��)�ĸ���(����FAT12/16)
	WORD	csize;			/* Cluster size [sectors] */        //ÿ���ص�������Ŀ(1,2,4...128)
#if FF_MAX_SS != FF_MIN_SS
	WORD	ssize;			/* Sector size (512, 1024, 2048 or 4096) */ //ÿ�������ֽ���(������������512Byte��flash)
#endif
#if FF_USE_LFN
	WCHAR*	lfnbuf;	  /* LFN working buffer */    //LFN����������
#endif
#if FF_FS_EXFAT
	BYTE*	dirbuf;			/* Directory entry block scratchpad buffer for exFAT */ //����exFAT��Ŀ¼��ڿ��ݴ滺����
#endif
#if FF_FS_REENTRANT
	FF_SYNC_t	sobj;		/* Identifier of sync object */ //ͬ�������ʶ��
#endif
#if !FF_FS_READONLY //���û����Ϊֻ��
	DWORD	last_clst;  /* Last allocated cluster */    //���һ��������Ĵ�
	DWORD	free_clst;  /* Number of free clusters */   //���д�����
#endif
#if FF_FS_RPATH
	DWORD	cdir;			  /* Current directory start cluster (0:root) */  //�������·��ʱ�ã��洢��ǰĿ¼��ʼ��(0:root)
#if FF_FS_EXFAT     //���֧��exFAT�ļ�ϵͳ
	DWORD	cdc_scl;		/* Containing directory start cluster (invalid when cdir is 0) */   //����Ŀ¼��ʼȺ������CDIRΪ0ʱ��Ч��
	DWORD	cdc_size;		/* b31-b8:Size of containing directory, b7-b0: Chain status */      //B31-B8:����Ŀ¼�Ĵ�С��B7 B0:��״̬ 
	DWORD	cdc_ofs;		/* Offset in the containing directory (invalid when cdir is 0) */   //����Ŀ¼�е�ƫ��������CDIRΪ0ʱ��Ч�� 
#endif
#endif
	DWORD	n_fatent;		/* Number of FAT entries (number of clusters + 2) */  //FATĿ¼��(�ص���Ŀ + 2)
	DWORD	fsize;			/* Size of an FAT [sectors] */    //ÿ��FAT��ռ����
	DWORD	volbase;		/* Volume base sector */          //��������ַ
	DWORD	fatbase;		/* FAT base sector */             //FAT��ʼ����
	DWORD	dirbase;		/* Root directory base sector/cluster */    //��Ŀ¼��ʼ����/��(FAT32:Cluster#)
	DWORD	database;		/* Data base sector */                      //����Ŀ¼��ʼ���� 
	DWORD	winsect;		/* Current sector appearing in the win[] */ //��ǰ�������д洢��������
	BYTE	win[FF_MAX_SS];	/* Disk access window for Directory, FAT (and file data at tiny cfg) */ //�����������棬��ǰΪ512Byte�� FAT (and Data on tiny cfg)
} FATFS;    //�ļ�ϵͳ����ṹ��


//=========================����ID�ͷ�����Ϣ�ṹ��
/* Object ID and allocation information (FFOBJID) */
typedef struct
{
	FATFS*	fs;				  /* Pointer to the hosting volume of this object */    //ָ�����ļ�ϵͳ�����ָ��
	WORD	  id;				  /* Hosting volume mount ID */     //������װID
	BYTE	  attr;			  /* Object attribute */            //��������
	BYTE	  stat;			  /* Object chain status (b1-0: =0:not contiguous, =2:contiguous, =3:flagmented in this session, b2:sub-directory stretched) */   //������״̬��B1-0:��0������������2���ڽӣ���3�����I��
	DWORD	  sclust;			/* Object data start cluster (0:no cluster or root directory) */  //����������ʼ�أ�0��û�м�Ⱥ���Ŀ¼��
	FSIZE_t	objsize;    /* Object size (valid when sclust != 0) */    //�����С����sclust != 0ʱ��Ч��
#if FF_FS_EXFAT       //���֧��exFAT�ļ�ϵͳ
	DWORD	  n_cont;			/* Size of first fragment - 1 (valid when stat == 3) */   //��һ��Ƭ�εĴ�С- 1����STAT��3ʱ��Ч��
	DWORD	  n_frag;			/* Size of last fragment needs to be written to FAT (valid when not zero) */    //���һ����Ҫд��FAT��Ƭ�δ�С����Чʱ��Ϊ��
	DWORD	  c_scl;			/* Containing directory start cluster (valid when sclust != 0) */               //����Ŀ¼����Ⱥ����ScRestUpʱ��Ч��= 0�� 
	DWORD	  c_size;			/* b31-b8:Size of containing directory, b7-b0: Chain status (valid when c_scl != 0) */  //B31-B8:����Ŀ¼�Ĵ�С��B7 B0:��״̬��CSCLʱ��Ч�� 
	DWORD	  c_ofs;			/* Offset in the containing directory (valid when file object and sclust != 0) */       //�ڰ���Ŀ¼�е�ƫ���������ļ������SCLUSTʱ��Ч��= 0��
#endif
#if FF_FS_LOCK
	UINT	  lockid;			/* File lock ID origin from 1 (index of file semaphore table Files[]) */    //�ļ���IDԴ��1���ļ��ź������ļ������� 
#endif
} FFOBJID;    //����ID�ͷ�����Ϣ�ṹ��


//=========================�ļ�����ṹ��
/* File object structure (FIL) */
typedef struct
{
	FFOBJID	obj;			  /* Object identifier (must be the 1st member to detect invalid object pointer) */ //���ڵ��ļ�ϵͳָ��
	BYTE	  flag;			  /* File status flags */         //�ļ�״̬��ʶ
	BYTE	  err;			  /* Abort flag (error code) */   //�쳣��־��������룩
	FSIZE_t fptr;			  /* File read/write pointer (Zeroed on file open) */     //�ļ���/дָ�루�ļ���Ϊ�㣩
	DWORD	  clust;			/* Current cluster of fpter (invalid when fptr is 0) */ //fpter�ĵ�ǰ�أ�fpterΪ0ʱ��Ч�� 
	DWORD	  sect;			  /* Sector number appearing in buf[] (0:invalid) */      //������BUF[]�е������ţ�0����Ч��
#if !FF_FS_READONLY   //���û�ж���Ϊֻ��
	DWORD	  dir_sect;		/* Sector number containing the directory entry (not used at exFAT) */  //����Ŀ¼��Ŀ��������ţ�������exFAT��
	BYTE*	  dir_ptr;		/* Pointer to the directory entry in the win[] (not used at exFAT) */   //Ŀ¼���ָ�루������ExFAT�� 
#endif
#if FF_USE_FASTSEEK   //����Ѷ����˿��ٲ��ҹ���
	DWORD*	cltbl;	    /* Pointer to the cluster link map table (nulled on open, set by application) */  //ָ�������ӳ����ָ�루�Ѵ򿪣���Ӧ�ó������ã� 
#endif
#if !FF_FS_TINY       //���û����΢������
	BYTE	  buf[FF_MAX_SS];	/* File private data read/write window */   //�ļ�ר�����ݶ�/д������
#endif
}FIL;    //�ļ�����ṹ��


//=========================Ŀ¼����ṹ��
/* Directory object structure (DIR) */    //Ŀ¼����ṹ��
typedef struct
{
	FFOBJID	obj;			/* Object identifier */               //���ڵ��ļ�ϵͳָ��
	DWORD	  dptr;		  /* Current read/write offset */       //��ǰ��/дƫ����
	DWORD	  clust;	  /* Current cluster */                 //��ǰ��
	DWORD	  sect;		  /* Current sector (0:Read operation has terminated) */    //��ǰ������0����ȡ��������ֹ��
	BYTE*	  dir;		  /* Pointer to the directory item in the win[] */          //��Win��ָ��Ŀ¼���ָ��
	BYTE	  fn[12];	  /* SFN (in/out) {body[8],ext[3],status[1]} */             //SFN��Short filename���ļ������ļ�ָ�� (in/out) {file[8],ext[3],status[1]}
#if FF_USE_LFN      //���ʹ���˳��ļ���
	DWORD	  blk_ofs;  /* Offset of current entry block being processed (0xFFFFFFFF:Invalid) */  //���ڴ���ĵ�ǰ������ƫ������0xFFFFFFF:��Ч��
#endif
#if FF_USE_FIND
	const   TCHAR* pat;		/* Pointer to the name matching pattern */    //ָ������ƥ��ģʽ��ָ��
#endif
}DIR;    //Ŀ¼����ṹ��



//=========================�ļ���Ϣ�ṹ��
/* File information structure (FILINFO) */
typedef struct
{
	FSIZE_t	fsize;	  /* File size */       //�ļ���С
	WORD	fdate;			/* Modified date */   //�޸�����
	WORD	ftime;			/* Modified time */   //�޸�ʱ��
	BYTE	fattrib;		/* File attribute */  //�ļ�����
#if FF_USE_LFN      //����Ѷ���ʹ�ó��ļ���
	TCHAR	altname[FF_SFN_BUF + 1];/* Altenative file name */  //�����ļ���
	TCHAR	fname[FF_LFN_BUF + 1];	/* Primary file name */     //���ļ���
#else
	TCHAR	fname[12 + 1];	/* File name */                     //�ļ���
#endif
} FILINFO;    //�ļ���Ϣ�ṹ��



//=========================�ļ�����������
/* File function return code (FRESULT) */
typedef enum
{
	FR_OK = 0,				    /* (0) Succeeded */                               //�����ɹ������ļ�������Ч��
	FR_DISK_ERR,			    /* (1) A hard error occurred in the low level disk I/O layer */ //���ڵײ����I/O�ӿں����е�һ�����󣬶����¸ú���ʧ��
	FR_INT_ERR,				    /* (2) Assertion failed */                        //����һ�������FAT�ṹ��һ���ڲ����󣬶����¸ú���ʧ��
	FR_NOT_READY,			    /* (3) The physical drive cannot work */          //������������û�д洢���ʻ��κ�����ԭ�򣬶����´����������޷�����
	FR_NO_FILE,				    /* (4) Could not find the file */                 //�Ҳ������ļ�
	FR_NO_PATH,				    /* (5) Could not find the path */                 //�Ҳ�����·��
	FR_INVALID_NAME,		  /* (6) The path name format is invalid */         //�ļ�����Ч
	FR_DENIED,				    /* (7) Access denied due to prohibited access or directory full */  //��������ԭ������ķ��ʱ��ܾ�
	FR_EXIST,				      /* (8) Access denied due to prohibited access */  //���ļ��Ѵ���
	FR_INVALID_OBJECT,		/* (9) The file/directory object is invalid */    //�ļ�/Ŀ¼������Ч
	FR_WRITE_PROTECTED,		/* (10) The physical drive is write protected */  //�洢���ʱ�д����
	FR_INVALID_DRIVE,		  /* (11) The logical drive number is invalid */    //����������Ч
	FR_NOT_ENABLED,			  /* (12) The volume has no work area */            //�߼�������û�й�����
	FR_NO_FILESYSTEM,		  /* (13) There is no valid FAT volume */           //������û����Ч��FAT��
	FR_MKFS_ABORTED,		  /* (14) The f_mkfs() aborted due to any problem */
	FR_TIMEOUT,				    /* (15) Could not get a grant to access the volume within defined period */
	FR_LOCKED,				    /* (16) The operation is rejected according to the file sharing policy */
	FR_NOT_ENOUGH_CORE,		/* (17) LFN working buffer could not be allocated */
	FR_TOO_MANY_OPEN_FILES,	/* (18) Number of open files > FF_FS_LOCK */    //�򿪵��ļ���Ŀ
	FR_INVALID_PARAMETER	/* (19) Given parameter is invalid */
} FRESULT;    //�ļ�����ִ�н��������

//==============================================================�ڲ�����START��δд��ͷ�ļ�
//==============================================================�ڲ�����END��δд��ͷ�ļ�
/*--------------------------------------------------------------*/
/* FatFs module application interface                           */

FRESULT f_open (FIL* fp, const TCHAR* path, BYTE mode);				    /* Open or create a file */       //����һ����Ҫ���ʵ��ļ�����
FRESULT f_close (FIL* fp);											                  /* Close an open file object */   //�ر�һ���Ѵ򿪵��ļ�
FRESULT f_read (FIL* fp, void* buff, UINT btr, UINT* br);			    /* Read data from the file */     //���ļ���ȡ����
FRESULT f_write (FIL* fp, const void* buff, UINT btw, UINT* bw);	/* Write data to the file */      //д���ݵ��ļ�
FRESULT f_lseek (FIL* fp, FSIZE_t ofs);								            /* Move file pointer of the file object */  //�ƶ�һ�����ļ����ļ���дָ��
FRESULT f_truncate (FIL* fp);										                  /* Truncate the file */                     //�ض��ļ�
FRESULT f_sync (FIL* fp);											                    /* Flush cached data of the writing file */ //��ϴ��������
FRESULT f_opendir (DIR* dp, const TCHAR* path);						        /* Open a directory */                      //��һ��Ŀ¼,�˺�����һ���Ѿ�����Ŀ¼����Ϊ���ĵ��ô���һ��Ŀ¼����
FRESULT f_closedir (DIR* dp);										                  /* Close an open directory */
FRESULT f_readdir (DIR* dp, FILINFO* fno);							          /* Read a directory item */                 //��˳���ȡĿ¼��Ŀ�����ļ���Ϣ�洢��fno
FRESULT f_findfirst (DIR* dp, FILINFO* fno, const TCHAR* path, const TCHAR* pattern);	/* Find first file */
FRESULT f_findnext (DIR* dp, FILINFO* fno);							          /* Find next file */
FRESULT f_mkdir (const TCHAR* path);								              /* Create a sub directory */    //����һ��Ŀ¼
FRESULT f_unlink (const TCHAR* path);								              /* Delete an existing file or directory */  //�Ƴ�һ������
FRESULT f_rename (const TCHAR* path_old, const TCHAR* path_new);	/* Rename/Move a file or directory */   //������һ������
FRESULT f_stat (const TCHAR* path, FILINFO* fno);					        /* Get file status */ //��ȡ�ļ�״̬
FRESULT f_chmod (const TCHAR* path, BYTE attr, BYTE mask);			  /* Change attribute of a file/dir */    //�޸�һ���ļ���Ŀ¼�����ԡ�
FRESULT f_utime (const TCHAR* path, const FILINFO* fno);			    /* Change timestamp of a file/dir */    //�޸�һ���ļ���Ŀ¼��ʱ�����
FRESULT f_chdir (const TCHAR* path);								              /* Change current directory */          //�ı�һ���������ĵ�ǰĿ¼��
FRESULT f_chdrive (const TCHAR* path);								            /* Change current drive */
FRESULT f_getcwd (TCHAR* buff, UINT len);							            /* Get current directory */
FRESULT f_getfree (const TCHAR* path, DWORD* nclst, FATFS** fatfs);	/* Get number of free clusters on the drive */  //��ȡ���дص���Ŀ
FRESULT f_getlabel (const TCHAR* path, TCHAR* label, DWORD* vsn);	  /* Get volume label */
FRESULT f_setlabel (const TCHAR* label);							              /* Set volume label */
FRESULT f_forward (FIL* fp, UINT(*func)(const BYTE*,UINT), UINT btf, UINT* bf);	/* Forward data to the stream */  //��ȡ�ļ����ݲ�����ת�����������豸��
FRESULT f_expand (FIL* fp, FSIZE_t szf, BYTE opt);					  /* Allocate a contiguous block to the file */
FRESULT f_mount (FATFS* fs, const TCHAR* path, BYTE opt);			/* Mount/Unmount a logical drive */     //��FatFsģ����ע��/ע��һ��������(�ļ�ϵͳ����)
FRESULT f_mkfs (const TCHAR* path, BYTE opt, DWORD au, void* work, UINT len);	  /* Create a FAT volume */   //���������ϴ���һ���ļ�ϵͳ
FRESULT f_fdisk (BYTE pdrv, const DWORD* szt, void* work);			                /* Divide a physical drive into some partitions */
FRESULT f_setcp (WORD cp);								      /* Set current code page */
int f_putc (TCHAR c, FIL* fp);							    /* Put a character to the file */     //���ļ���д��һ���ַ�
int f_puts (const TCHAR* str, FIL* cp);				  /* Put a string to the file */        //���ļ���д��һ���ַ���
int f_printf (FIL* fp, const TCHAR* str, ...);  /* Put a formatted string to the file */
TCHAR* f_gets (TCHAR* buff, int len, FIL* fp);  /* Get a string from the file */    //���ļ��ж�ȡһ���ַ���

#define f_eof(fp) ((int)((fp)->fptr == (fp)->obj.objsize))
#define f_error(fp) ((fp)->err)
#define f_tell(fp) ((fp)->fptr)
#define f_size(fp) ((fp)->obj.objsize)
#define f_rewind(fp) f_lseek((fp), 0)
#define f_rewinddir(dp) f_readdir((dp), 0)
#define f_rmdir(path) f_unlink(path)
#define f_unmount(path) f_mount(0, path, 0)

#ifndef EOF
#define EOF (-1)
#endif




/*--------------------------------------------------------------*/
/* Additional user defined functions                            */

/* RTC function */
#if !FF_FS_READONLY && !FF_FS_NORTC
DWORD get_fattime (void);
#endif

/* LFN support functions */
#if FF_USE_LFN >= 1						/* Code conversion (defined in unicode.c) */
WCHAR ff_oem2uni (WCHAR oem, WORD cp);	/* OEM code to Unicode conversion */
WCHAR ff_uni2oem (DWORD uni, WORD cp);	/* Unicode to OEM code conversion */
DWORD ff_wtoupper (DWORD uni);			/* Unicode upper-case conversion */
#endif
#if FF_USE_LFN == 3						/* Dynamic memory allocation */
void* ff_memalloc (UINT msize);			/* Allocate memory block */
void ff_memfree (void* mblock);			/* Free memory block */
#endif

/* Sync functions */
#if FF_FS_REENTRANT
int ff_cre_syncobj (BYTE vol, FF_SYNC_t* sobj);	/* Create a sync object */
int ff_req_grant (FF_SYNC_t sobj);		/* Lock sync object */
void ff_rel_grant (FF_SYNC_t sobj);		/* Unlock sync object */
int ff_del_syncobj (FF_SYNC_t sobj);	/* Delete a sync object */
#endif




/*--------------------------------------------------------------*/
/* Flags and offset address                                     */


/* File access mode and open method flags (3rd argument of f_open) */
#define	FA_READ				    0x01    //ָ�������ʶ��󡣿��Դ��ļ���ȡ���ݡ���FA_WRITE���Ϊ��д���ʡ�
#define	FA_WRITE			    0x02    //ָ��д���ʶ��󡣿������ļ�д�����ݡ���FA_READ���Ϊ��д���ʡ�
#define	FA_OPEN_EXISTING	0x00    //���ļ�������ļ������ڣ���������ʧ�ܡ���Ĭ��ģʽ��
#define	FA_CREATE_NEW		  0x04    //����һ�����ļ�������ļ����ڣ�����ִ��ʧ�ܣ�������FR_EXISTֵ��
#define	FA_CREATE_ALWAYS	0x08    //����һ�����ļ�������ļ����ڣ�����ɾ�ں͸�д��
#define	FA_OPEN_ALWAYS		0x10    //������ڴ��ļ�������ļ������ڣ�����һ�����ļ�����ʹ�ô�ģʽ���ļ���ʹ��f_lseek������׷�����ݵ��ļ���
#define	FA_OPEN_APPEND		0x30    //

/* Fast seek controls (2nd argument of f_lseek) */
#define CREATE_LINKMAP	((FSIZE_t)0 - 1)

/* Format options (2nd argument of f_mkfs) */
#define FM_FAT		0x01
#define FM_FAT32	0x02
#define FM_EXFAT	0x04
#define FM_ANY		0x07
#define FM_SFD		0x08

/* Filesystem type (FATFS.fs_type) */
#define FS_FAT12	1
#define FS_FAT16	2
#define FS_FAT32	3
#define FS_EXFAT	4

/* File attribute bits for directory entry (FILINFO.fattrib) */
#define	AM_RDO	0x01	/* Read only */
#define	AM_HID	0x02	/* Hidden */
#define	AM_SYS	0x04	/* System */
#define AM_DIR	0x10	/* Directory */
#define AM_ARC	0x20	/* Archive */


#ifdef __cplusplus
}
#endif

#endif /* FF_DEFINED */
