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


//=========================文件系统对象结构体
/* Filesystem object structure (FATFS) */
typedef struct 
{
	BYTE	fs_type;		/* Filesystem type (0:N/A) */   //FAT子类型，一般在mount时用，置0表示未挂载
	BYTE	pdrv;			  /* Physical drive number */     //物理驱动器号，一般为0
	BYTE	n_fats;			/* Number of FATs (1 or 2) */   //文件分配表的数目(1,2) ，FAT文件系统依次为：引导扇区、两个文件分配表、根目录区和数据区
	BYTE	wflag;			/* win[] flag (b0:dirty) */     //标记文件是否被改动过，为1时要回写
	BYTE	fsi_flag;		/* FSINFO flags (b7:disabled, b0:dirty) */  //标记文件系统信息是否被改动过，为1时要回写
	WORD	id;				  /* Volume mount ID */                       //文件系统挂载ID
	WORD	n_rootdir;  /* Number of root directory entries (FAT12/16) */ //根目录区入口(目录项)的个数(用于FAT12/16)
	WORD	csize;			/* Cluster size [sectors] */        //每个簇的扇区数目(1,2,4...128)
#if FF_MAX_SS != FF_MIN_SS
	WORD	ssize;			/* Sector size (512, 1024, 2048 or 4096) */ //每扇区的字节数(用于扇区大于512Byte的flash)
#endif
#if FF_USE_LFN
	WCHAR*	lfnbuf;	  /* LFN working buffer */    //LFN工作缓冲区
#endif
#if FF_FS_EXFAT
	BYTE*	dirbuf;			/* Directory entry block scratchpad buffer for exFAT */ //用于exFAT的目录入口块暂存缓冲区
#endif
#if FF_FS_REENTRANT
	FF_SYNC_t	sobj;		/* Identifier of sync object */ //同步对象标识符
#endif
#if !FF_FS_READONLY //如果没定义为只读
	DWORD	last_clst;  /* Last allocated cluster */    //最后一个被分配的簇
	DWORD	free_clst;  /* Number of free clusters */   //空闲簇数量
#endif
#if FF_FS_RPATH
	DWORD	cdir;			  /* Current directory start cluster (0:root) */  //允许相对路径时用，存储当前目录起始簇(0:root)
#if FF_FS_EXFAT     //如果支持exFAT文件系统
	DWORD	cdc_scl;		/* Containing directory start cluster (invalid when cdir is 0) */   //包含目录起始群集（当CDIR为0时无效）
	DWORD	cdc_size;		/* b31-b8:Size of containing directory, b7-b0: Chain status */      //B31-B8:包含目录的大小，B7 B0:链状态 
	DWORD	cdc_ofs;		/* Offset in the containing directory (invalid when cdir is 0) */   //包含目录中的偏移量（当CDIR为0时无效） 
#endif
#endif
	DWORD	n_fatent;		/* Number of FAT entries (number of clusters + 2) */  //FAT目录数(簇的数目 + 2)
	DWORD	fsize;			/* Size of an FAT [sectors] */    //每个FAT所占扇区
	DWORD	volbase;		/* Volume base sector */          //扇区基地址
	DWORD	fatbase;		/* FAT base sector */             //FAT起始扇区
	DWORD	dirbase;		/* Root directory base sector/cluster */    //根目录起始扇区/簇(FAT32:Cluster#)
	DWORD	database;		/* Data base sector */                      //数据目录起始扇区 
	DWORD	winsect;		/* Current sector appearing in the win[] */ //当前缓冲区中存储的扇区号
	BYTE	win[FF_MAX_SS];	/* Disk access window for Directory, FAT (and file data at tiny cfg) */ //单个扇区缓存，当前为512Byte， FAT (and Data on tiny cfg)
} FATFS;    //文件系统对象结构体


//=========================对象ID和分配信息结构体
/* Object ID and allocation information (FFOBJID) */
typedef struct
{
	FATFS*	fs;				  /* Pointer to the hosting volume of this object */    //指向主文件系统对象的指针
	WORD	  id;				  /* Hosting volume mount ID */     //主机卷安装ID
	BYTE	  attr;			  /* Object attribute */            //对象属性
	BYTE	  stat;			  /* Object chain status (b1-0: =0:not contiguous, =2:contiguous, =3:flagmented in this session, b2:sub-directory stretched) */   //对象链状态（B1-0:＝0：不连续，＝2：邻接，＝3：标记I）
	DWORD	  sclust;			/* Object data start cluster (0:no cluster or root directory) */  //对象数据起始簇（0：没有集群或根目录）
	FSIZE_t	objsize;    /* Object size (valid when sclust != 0) */    //对象大小（当sclust != 0时有效）
#if FF_FS_EXFAT       //如果支持exFAT文件系统
	DWORD	  n_cont;			/* Size of first fragment - 1 (valid when stat == 3) */   //第一个片段的大小- 1（当STAT＝3时有效）
	DWORD	  n_frag;			/* Size of last fragment needs to be written to FAT (valid when not zero) */    //最后一个需要写到FAT的片段大小（有效时不为零
	DWORD	  c_scl;			/* Containing directory start cluster (valid when sclust != 0) */               //包含目录启动群集（ScRestUp时有效）= 0） 
	DWORD	  c_size;			/* b31-b8:Size of containing directory, b7-b0: Chain status (valid when c_scl != 0) */  //B31-B8:包含目录的大小，B7 B0:链状态（CSCL时有效） 
	DWORD	  c_ofs;			/* Offset in the containing directory (valid when file object and sclust != 0) */       //在包含目录中的偏移量（当文件对象和SCLUST时有效）= 0）
#endif
#if FF_FS_LOCK
	UINT	  lockid;			/* File lock ID origin from 1 (index of file semaphore table Files[]) */    //文件锁ID源于1（文件信号量表文件索引） 
#endif
} FFOBJID;    //对象ID和分配信息结构体


//=========================文件对象结构体
/* File object structure (FIL) */
typedef struct
{
	FFOBJID	obj;			  /* Object identifier (must be the 1st member to detect invalid object pointer) */ //所在的文件系统指针
	BYTE	  flag;			  /* File status flags */         //文件状态标识
	BYTE	  err;			  /* Abort flag (error code) */   //异常标志（错误代码）
	FSIZE_t fptr;			  /* File read/write pointer (Zeroed on file open) */     //文件读/写指针（文件打开为零）
	DWORD	  clust;			/* Current cluster of fpter (invalid when fptr is 0) */ //fpter的当前簇（fpter为0时无效） 
	DWORD	  sect;			  /* Sector number appearing in buf[] (0:invalid) */      //出现在BUF[]中的扇区号（0：无效）
#if !FF_FS_READONLY   //如果没有定义为只读
	DWORD	  dir_sect;		/* Sector number containing the directory entry (not used at exFAT) */  //包含目录条目的扇区编号（不用于exFAT）
	BYTE*	  dir_ptr;		/* Pointer to the directory entry in the win[] (not used at exFAT) */   //目录入口指针（不用于ExFAT） 
#endif
#if FF_USE_FASTSEEK   //如果已定义了快速查找功能
	DWORD*	cltbl;	    /* Pointer to the cluster link map table (nulled on open, set by application) */  //指向簇链接映射表的指针（已打开，由应用程序设置） 
#endif
#if !FF_FS_TINY       //如果没定义微缓冲区
	BYTE	  buf[FF_MAX_SS];	/* File private data read/write window */   //文件专用数据读/写缓冲区
#endif
}FIL;    //文件对象结构体


//=========================目录对象结构体
/* Directory object structure (DIR) */    //目录对象结构体
typedef struct
{
	FFOBJID	obj;			/* Object identifier */               //所在的文件系统指针
	DWORD	  dptr;		  /* Current read/write offset */       //当前读/写偏移量
	DWORD	  clust;	  /* Current cluster */                 //当前簇
	DWORD	  sect;		  /* Current sector (0:Read operation has terminated) */    //当前扇区（0：读取操作已终止）
	BYTE*	  dir;		  /* Pointer to the directory item in the win[] */          //在Win中指向目录项的指针
	BYTE	  fn[12];	  /* SFN (in/out) {body[8],ext[3],status[1]} */             //SFN：Short filename短文件名，文件指针 (in/out) {file[8],ext[3],status[1]}
#if FF_USE_LFN      //如果使用了长文件名
	DWORD	  blk_ofs;  /* Offset of current entry block being processed (0xFFFFFFFF:Invalid) */  //正在处理的当前输入块的偏移量（0xFFFFFFF:无效）
#endif
#if FF_USE_FIND
	const   TCHAR* pat;		/* Pointer to the name matching pattern */    //指向名称匹配模式的指针
#endif
}DIR;    //目录对象结构体



//=========================文件信息结构体
/* File information structure (FILINFO) */
typedef struct
{
	FSIZE_t	fsize;	  /* File size */       //文件大小
	WORD	fdate;			/* Modified date */   //修改日期
	WORD	ftime;			/* Modified time */   //修改时间
	BYTE	fattrib;		/* File attribute */  //文件属性
#if FF_USE_LFN      //如果已定义使用长文件名
	TCHAR	altname[FF_SFN_BUF + 1];/* Altenative file name */  //补充文件名
	TCHAR	fname[FF_LFN_BUF + 1];	/* Primary file name */     //主文件名
#else
	TCHAR	fname[12 + 1];	/* File name */                     //文件名
#endif
} FILINFO;    //文件信息结构体



//=========================文件函数返回码
/* File function return code (FRESULT) */
typedef enum
{
	FR_OK = 0,				    /* (0) Succeeded */                               //函数成功，该文件对象有效。
	FR_DISK_ERR,			    /* (1) A hard error occurred in the low level disk I/O layer */ //由于底层磁盘I/O接口函数中的一个错误，而导致该函数失败
	FR_INT_ERR,				    /* (2) Assertion failed */                        //由于一个错误的FAT结构或一个内部错误，而导致该函数失败
	FR_NOT_READY,			    /* (3) The physical drive cannot work */          //由于驱动器中没有存储介质或任何其他原因，而导致磁盘驱动器无法工作
	FR_NO_FILE,				    /* (4) Could not find the file */                 //找不到该文件
	FR_NO_PATH,				    /* (5) Could not find the path */                 //找不到该路径
	FR_INVALID_NAME,		  /* (6) The path name format is invalid */         //文件名无效
	FR_DENIED,				    /* (7) Access denied due to prohibited access or directory full */  //由于下列原因，所需的访问被拒绝
	FR_EXIST,				      /* (8) Access denied due to prohibited access */  //该文件已存在
	FR_INVALID_OBJECT,		/* (9) The file/directory object is invalid */    //文件/目录对象无效
	FR_WRITE_PROTECTED,		/* (10) The physical drive is write protected */  //存储介质被写保护
	FR_INVALID_DRIVE,		  /* (11) The logical drive number is invalid */    //驱动器号无效
	FR_NOT_ENABLED,			  /* (12) The volume has no work area */            //逻辑驱动器没有工作区
	FR_NO_FILESYSTEM,		  /* (13) There is no valid FAT volume */           //磁盘上没有有效地FAT卷
	FR_MKFS_ABORTED,		  /* (14) The f_mkfs() aborted due to any problem */
	FR_TIMEOUT,				    /* (15) Could not get a grant to access the volume within defined period */
	FR_LOCKED,				    /* (16) The operation is rejected according to the file sharing policy */
	FR_NOT_ENOUGH_CORE,		/* (17) LFN working buffer could not be allocated */
	FR_TOO_MANY_OPEN_FILES,	/* (18) Number of open files > FF_FS_LOCK */    //打开的文件数目
	FR_INVALID_PARAMETER	/* (19) Given parameter is invalid */
} FRESULT;    //文件函数执行结果返回码

//==============================================================内部函数START（未写出头文件
//==============================================================内部函数END（未写出头文件
/*--------------------------------------------------------------*/
/* FatFs module application interface                           */

FRESULT f_open (FIL* fp, const TCHAR* path, BYTE mode);				    /* Open or create a file */       //创建一个将要访问的文件对象。
FRESULT f_close (FIL* fp);											                  /* Close an open file object */   //关闭一个已打开的文件
FRESULT f_read (FIL* fp, void* buff, UINT btr, UINT* br);			    /* Read data from the file */     //从文件读取数据
FRESULT f_write (FIL* fp, const void* buff, UINT btw, UINT* bw);	/* Write data to the file */      //写数据到文件
FRESULT f_lseek (FIL* fp, FSIZE_t ofs);								            /* Move file pointer of the file object */  //移动一个打开文件的文件读写指针
FRESULT f_truncate (FIL* fp);										                  /* Truncate the file */                     //截断文件
FRESULT f_sync (FIL* fp);											                    /* Flush cached data of the writing file */ //冲洗缓冲数据
FRESULT f_opendir (DIR* dp, const TCHAR* path);						        /* Open a directory */                      //打开一个目录,此函数打开一个已经存在目录并且为随后的调用创建一个目录对象
FRESULT f_closedir (DIR* dp);										                  /* Close an open directory */
FRESULT f_readdir (DIR* dp, FILINFO* fno);							          /* Read a directory item */                 //按顺序读取目录条目及将文件信息存储到fno
FRESULT f_findfirst (DIR* dp, FILINFO* fno, const TCHAR* path, const TCHAR* pattern);	/* Find first file */
FRESULT f_findnext (DIR* dp, FILINFO* fno);							          /* Find next file */
FRESULT f_mkdir (const TCHAR* path);								              /* Create a sub directory */    //创建一个目录
FRESULT f_unlink (const TCHAR* path);								              /* Delete an existing file or directory */  //移除一个对象
FRESULT f_rename (const TCHAR* path_old, const TCHAR* path_new);	/* Rename/Move a file or directory */   //重命名一个对象
FRESULT f_stat (const TCHAR* path, FILINFO* fno);					        /* Get file status */ //获取文件状态
FRESULT f_chmod (const TCHAR* path, BYTE attr, BYTE mask);			  /* Change attribute of a file/dir */    //修改一个文件或目录的属性。
FRESULT f_utime (const TCHAR* path, const FILINFO* fno);			    /* Change timestamp of a file/dir */    //修改一个文件或目录的时间戳。
FRESULT f_chdir (const TCHAR* path);								              /* Change current directory */          //改变一个驱动器的当前目录。
FRESULT f_chdrive (const TCHAR* path);								            /* Change current drive */
FRESULT f_getcwd (TCHAR* buff, UINT len);							            /* Get current directory */
FRESULT f_getfree (const TCHAR* path, DWORD* nclst, FATFS** fatfs);	/* Get number of free clusters on the drive */  //获取空闲簇的数目
FRESULT f_getlabel (const TCHAR* path, TCHAR* label, DWORD* vsn);	  /* Get volume label */
FRESULT f_setlabel (const TCHAR* label);							              /* Set volume label */
FRESULT f_forward (FIL* fp, UINT(*func)(const BYTE*,UINT), UINT btf, UINT* bf);	/* Forward data to the stream */  //读取文件数据并将其转发到数据流设备。
FRESULT f_expand (FIL* fp, FSIZE_t szf, BYTE opt);					  /* Allocate a contiguous block to the file */
FRESULT f_mount (FATFS* fs, const TCHAR* path, BYTE opt);			/* Mount/Unmount a logical drive */     //在FatFs模块上注册/注销一个工作区(文件系统对象)
FRESULT f_mkfs (const TCHAR* path, BYTE opt, DWORD au, void* work, UINT len);	  /* Create a FAT volume */   //在驱动器上创建一个文件系统
FRESULT f_fdisk (BYTE pdrv, const DWORD* szt, void* work);			                /* Divide a physical drive into some partitions */
FRESULT f_setcp (WORD cp);								      /* Set current code page */
int f_putc (TCHAR c, FIL* fp);							    /* Put a character to the file */     //向文件中写入一个字符
int f_puts (const TCHAR* str, FIL* cp);				  /* Put a string to the file */        //向文件中写入一个字符串
int f_printf (FIL* fp, const TCHAR* str, ...);  /* Put a formatted string to the file */
TCHAR* f_gets (TCHAR* buff, int len, FIL* fp);  /* Get a string from the file */    //从文件中读取一个字符串

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
#define	FA_READ				    0x01    //指定读访问对象。可以从文件读取数据。与FA_WRITE组合为读写访问。
#define	FA_WRITE			    0x02    //指定写访问对象。可以向文件写入数据。与FA_READ组合为读写访问。
#define	FA_OPEN_EXISTING	0x00    //打开文件。如果文件不存在，函数返回失败。（默认模式）
#define	FA_CREATE_NEW		  0x04    //创建一个新文件。如果文件存在，函数执行失败，并返回FR_EXIST值。
#define	FA_CREATE_ALWAYS	0x08    //创建一个新文件。如果文件存在，将被删节和复写。
#define	FA_OPEN_ALWAYS		0x10    //如果存在打开文件。如果文件不存在，创建一个新文件。在使用此模式打开文件后，使用f_lseek函数，追加数据到文件。
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
