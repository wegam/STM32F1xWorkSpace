#line 1 "..\\..\\Driver\\FatFs\\source\\ffunicode.c"
 
 
 




 














 


#line 1 "..\\..\\Driver\\FatFs\\source\\ff.h"


















 









#line 1 "..\\..\\Driver\\FatFs\\source\\integer.h"
 
 
 




#line 14 "..\\..\\Driver\\FatFs\\source\\integer.h"

 
typedef int				INT;
typedef unsigned int	UINT;

 
typedef unsigned char	BYTE;

 
typedef short			SHORT;
typedef unsigned short	WORD;
typedef unsigned short	WCHAR;

 
typedef long			LONG;
typedef unsigned long	DWORD;

 
typedef unsigned long long QWORD;



#line 30 "..\\..\\Driver\\FatFs\\source\\ff.h"
#line 1 "..\\..\\Driver\\FatFs\\source\\ffconf.h"


 





 





 









 







 




 



 



 



 




 




 



 




 



























 



















 











 







 












 








 




 


 













 








 









 





 











 





 





 

  



 













 











 




















 

 



 
#line 31 "..\\..\\Driver\\FatFs\\source\\ff.h"







 

#line 47 "..\\..\\Driver\\FatFs\\source\\ff.h"









 




#line 76 "..\\..\\Driver\\FatFs\\source\\ff.h"
typedef char TCHAR;








 




typedef DWORD FSIZE_t;




 
typedef struct 
{
	BYTE	fs_type;		    
	BYTE	pdrv;			        
	BYTE	n_fats;			    
	BYTE	wflag;			      
	BYTE	fsi_flag;		   
	WORD	id;				                          
	WORD	n_rootdir;    
	WORD	csize;			         
#line 119 "..\\..\\Driver\\FatFs\\source\\ff.h"
	DWORD	last_clst;       
	DWORD	free_clst;      
#line 130 "..\\..\\Driver\\FatFs\\source\\ff.h"
	DWORD	n_fatent;		   
	DWORD	fsize;			     
	DWORD	volbase;		           
	DWORD	fatbase;		              
	DWORD	dirbase;		     
	DWORD	database;		                       
	DWORD	winsect;		  
	BYTE	win[512];	  
} FATFS;    



 
typedef struct
{
	FATFS*	fs;				       
	WORD	  id;				        
	BYTE	  attr;			               
	BYTE	  stat;			      
	DWORD	  sclust;			   
	FSIZE_t	objsize;         
#line 161 "..\\..\\Driver\\FatFs\\source\\ff.h"
} FFOBJID;    



 
typedef struct
{
	FFOBJID	obj;			    
	BYTE	  flag;			            
	BYTE	  err;			      
	FSIZE_t fptr;			        
	DWORD	  clust;			  
	DWORD	  sect;			         

	DWORD	  dir_sect;		   
	BYTE*	  dir_ptr;		    





	BYTE	  buf[512];	    

}FIL;    



     
typedef struct
{
	FFOBJID	obj;			                
	DWORD	  dptr;		          
	DWORD	  clust;	                    
	DWORD	  sect;		       
	BYTE*	  dir;		             
	BYTE	  fn[12];	                
#line 203 "..\\..\\Driver\\FatFs\\source\\ff.h"
}DIR;    




 
typedef struct
{
	FSIZE_t	fsize;	          
	WORD	fdate;			    
	WORD	ftime;			    
	BYTE	fattrib;		   




	TCHAR	fname[12 + 1];	                      

} FILINFO;    




 
typedef enum
{
	FR_OK = 0,				                                    
	FR_DISK_ERR,			      
	FR_INT_ERR,				                             
	FR_NOT_READY,			               
	FR_NO_FILE,				                      
	FR_NO_PATH,				                      
	FR_INVALID_NAME,		            
	FR_DENIED,				       
	FR_EXIST,				         
	FR_INVALID_OBJECT,		     
	FR_WRITE_PROTECTED,		   
	FR_INVALID_DRIVE,		       
	FR_NOT_ENABLED,			               
	FR_NO_FILESYSTEM,		              
	FR_MKFS_ABORTED,		   
	FR_TIMEOUT,				     
	FR_LOCKED,				     
	FR_NOT_ENOUGH_CORE,		 
	FR_TOO_MANY_OPEN_FILES,	     
	FR_INVALID_PARAMETER	 
} FRESULT;    



 
 

FRESULT f_open (FIL* fp, const TCHAR* path, BYTE mode);				            
FRESULT f_close (FIL* fp);											                      
FRESULT f_read (FIL* fp, void* buff, UINT btr, UINT* br);			          
FRESULT f_write (FIL* fp, const void* buff, UINT btw, UINT* bw);	       
FRESULT f_lseek (FIL* fp, FSIZE_t ofs);								               
FRESULT f_truncate (FIL* fp);										                                        
FRESULT f_sync (FIL* fp);											                      
FRESULT f_opendir (DIR* dp, const TCHAR* path);						                               
FRESULT f_closedir (DIR* dp);										                   
FRESULT f_readdir (DIR* dp, FILINFO* fno);							                            
FRESULT f_findfirst (DIR* dp, FILINFO* fno, const TCHAR* path, const TCHAR* pattern);	 
FRESULT f_findnext (DIR* dp, FILINFO* fno);							           
FRESULT f_mkdir (const TCHAR* path);								                   
FRESULT f_unlink (const TCHAR* path);								                 
FRESULT f_rename (const TCHAR* path_old, const TCHAR* path_new);	    
FRESULT f_stat (const TCHAR* path, FILINFO* fno);					          
FRESULT f_chmod (const TCHAR* path, BYTE attr, BYTE mask);			       
FRESULT f_utime (const TCHAR* path, const FILINFO* fno);			         
FRESULT f_chdir (const TCHAR* path);								                         
FRESULT f_chdrive (const TCHAR* path);								             
FRESULT f_getcwd (TCHAR* buff, UINT len);							             
FRESULT f_getfree (const TCHAR* path, DWORD* nclst, FATFS** fatfs);	   
FRESULT f_getlabel (const TCHAR* path, TCHAR* label, DWORD* vsn);	   
FRESULT f_setlabel (const TCHAR* label);							               
FRESULT f_forward (FIL* fp, UINT(*func)(const BYTE*,UINT), UINT btf, UINT* bf);	   
FRESULT f_expand (FIL* fp, FSIZE_t szf, BYTE opt);					   
FRESULT f_mount (FATFS* fs, const TCHAR* path, BYTE opt);			      
FRESULT f_mkfs (const TCHAR* path, BYTE opt, DWORD au, void* work, UINT len);	      
FRESULT f_fdisk (BYTE pdrv, const DWORD* szt, void* work);			                 
FRESULT f_setcp (WORD cp);								       
int f_putc (TCHAR c, FIL* fp);							          
int f_puts (const TCHAR* str, FIL* cp);				           
int f_printf (FIL* fp, const TCHAR* str, ...);   
TCHAR* f_gets (TCHAR* buff, int len, FIL* fp);       

#line 299 "..\\..\\Driver\\FatFs\\source\\ff.h"








 
 

 




 
#line 325 "..\\..\\Driver\\FatFs\\source\\ff.h"

 
#line 333 "..\\..\\Driver\\FatFs\\source\\ff.h"




 
 


 
#line 349 "..\\..\\Driver\\FatFs\\source\\ff.h"

 


 






 





 











#line 27 "..\\..\\Driver\\FatFs\\source\\ffunicode.c"

