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
#ifndef __FatFsAPI_H
#define __FatFsAPI_H

#include "integer.h"
#include "ff.h"			/* Declarations of FatFs API */
#include "MMC_SD.h"



int SD_disk_initialize(void);
int SD_disk_status(void);
int SD_disk_read(BYTE *buff,DWORD sector,UINT count);
int SD_disk_write(const BYTE *buff,DWORD sector,UINT count);


unsigned char SD_disk_getcapacity(unsigned char *drv,unsigned long *total,unsigned long *free);   //获取磁盘的总容量和剩余容量
bool FilSearch(FATFS *fs,DIR *dir,TCHAR *path,u8 *name,char (*p)[13]);  //在指定路径下查找指定扩展名的文件，并记录在(*p)[13]数组中，注意最大记录条数


#endif
