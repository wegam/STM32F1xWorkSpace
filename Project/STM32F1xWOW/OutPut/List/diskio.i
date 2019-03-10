#line 1 "..\\..\\Driver\\FatFs\\source\\diskio.c"
 
 
 
 
 
 
 
 

#line 1 "..\\..\\Driver\\FatFs\\source\\diskio.h"


 








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



#line 13 "..\\..\\Driver\\FatFs\\source\\diskio.h"


 
typedef BYTE	DSTATUS;

 
typedef enum {
	RES_OK = 0,		 
	RES_ERROR,		 
	RES_WRPRT,		 
	RES_NOTRDY,		 
	RES_PARERR		 
} DRESULT;


 
 

DSTATUS disk_initialize (BYTE pdrv);
DSTATUS disk_status (BYTE pdrv);
DRESULT disk_read (BYTE pdrv, BYTE* buff, DWORD sector, UINT count);
DRESULT disk_write (BYTE pdrv, const BYTE* buff, DWORD sector, UINT count);
DRESULT disk_ioctl (BYTE pdrv, BYTE cmd, void* buff);


 






 

 






 





 
#line 69 "..\\..\\Driver\\FatFs\\source\\diskio.h"

 








#line 11 "..\\..\\Driver\\FatFs\\source\\diskio.c"
#line 1 "..\\..\\Driver\\FatFs\\source\\FatFsAPI.h"


















 



#line 24 "..\\..\\Driver\\FatFs\\source\\FatFsAPI.h"
#line 1 "..\\..\\Driver\\FatFs\\source\\ff.h"


















 









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

 


 






 





 











#line 25 "..\\..\\Driver\\FatFs\\source\\FatFsAPI.h"
#line 1 "..\\..\\Driver\\Components\\INC\\MMC_SD.h"



#line 1 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_type.h"














 

 



 
 
typedef signed long  s32;
typedef signed short s16;
typedef signed char  s8;

typedef signed long  const sc32;   
typedef signed short const sc16;   
typedef signed char  const sc8;    

typedef volatile signed long  vs32;
typedef volatile signed short vs16;
typedef volatile signed char  vs8;

typedef volatile signed long  const vsc32;   
typedef volatile signed short const vsc16;   
typedef volatile signed char  const vsc8;    

typedef unsigned long  u32;
typedef unsigned short u16;
typedef unsigned char  u8;

typedef unsigned long  const uc32;   
typedef unsigned short const uc16;   
typedef unsigned char  const uc8;    

typedef volatile unsigned long  vu32;
typedef volatile unsigned short vu16;
typedef volatile unsigned char  vu8;

typedef volatile unsigned long  const vuc32;   
typedef volatile unsigned short const vuc16;   
typedef volatile unsigned char  const vuc8;    

typedef enum {FALSE = 0, TRUE = !FALSE} bool;

typedef enum {RESET = 0, SET = !RESET} FlagStatus, ITStatus;

typedef enum {DISABLE = 0, ENABLE = !DISABLE} FunctionalState;


typedef enum {ERROR = 0, SUCCESS = !ERROR} ErrorStatus;

#line 73 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_type.h"

 
 
 



 
#line 5 "..\\..\\Driver\\Components\\INC\\MMC_SD.h"
#line 1 "..\\..\\Driver\\WOW\\INC\\STM32F10x_BitBand.h"




 




 












 

 



 
#line 1 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_map.h"














 

 







 
#line 1 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_conf.h"













 

 



 
#line 22 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_conf.h"

 
 


 
 

 
 





 


 


 


 


 


 
#line 66 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_conf.h"

 


 



 


 


 
#line 90 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_conf.h"

 




 


 


 


 


 


 


 





 


 
#line 133 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_conf.h"

 
#line 141 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_conf.h"

 



 


 
#line 167 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_conf.h"



 
#line 27 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_map.h"
#line 28 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_map.h"
#line 1 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\cortexm3_macro.h"













 

 



 
#line 22 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\cortexm3_macro.h"

 
 
 
 
void __WFI(void);
void __WFE(void);
void __SEV(void);
void __ISB(void);
void __DSB(void);
void __DMB(void);
void __SVC(void);
u32 __MRS_CONTROL(void);
void __MSR_CONTROL(u32 Control);
u32 __MRS_PSP(void);
void __MSR_PSP(u32 TopOfProcessStack);	
u32 __MRS_MSP(void);
void __MSR_MSP(u32 TopOfMainStack);			
void __RESETPRIMASK(void);
void __SETPRIMASK(void);
u32 __READ_PRIMASK(void);
void __RESETFAULTMASK(void);
void __SETFAULTMASK(void);
u32 __READ_FAULTMASK(void);
void __BASEPRICONFIG(u32 NewPriority);
u32 __GetBASEPRI(void);
u16 __REV_HalfWord(u16 Data);
u32 __REV_Word(u32 Data);



 
#line 29 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_map.h"

 
 
 
 

 
typedef struct
{
  vu32 SR;					
  vu32 CR1;					
  vu32 CR2;					
  vu32 SMPR1;				
  vu32 SMPR2;				
  vu32 JOFR1;				
  vu32 JOFR2;				
  vu32 JOFR3;				
  vu32 JOFR4;				
  vu32 HTR;					
  vu32 LTR;					
  vu32 SQR1;				
  vu32 SQR2;				
  vu32 SQR3;				
  vu32 JSQR;				
  vu32 JDR1;				
  vu32 JDR2;				
  vu32 JDR3;				
  vu32 JDR4;				
  vu32 DR;					
} ADC_TypeDef;

 
typedef struct
{
  u32  RESERVED0;	
  vu16 DR1;
  u16  RESERVED1;
  vu16 DR2;
  u16  RESERVED2;
  vu16 DR3;
  u16  RESERVED3;
  vu16 DR4;
  u16  RESERVED4;
  vu16 DR5;
  u16  RESERVED5;
  vu16 DR6;
  u16  RESERVED6;
  vu16 DR7;
  u16  RESERVED7;
  vu16 DR8;
  u16  RESERVED8;
  vu16 DR9;
  u16  RESERVED9;
  vu16 DR10;
  u16  RESERVED10; 
  vu16 RTCCR;				
  u16  RESERVED11;
  vu16 CR;					
  u16  RESERVED12;
  vu16 CSR;					
  u16  RESERVED13[5];
  vu16 DR11;
  u16  RESERVED14;
  vu16 DR12;
  u16  RESERVED15;
  vu16 DR13;
  u16  RESERVED16;
  vu16 DR14;
  u16  RESERVED17;
  vu16 DR15;
  u16  RESERVED18;
  vu16 DR16;
  u16  RESERVED19;
  vu16 DR17;
  u16  RESERVED20;
  vu16 DR18;
  u16  RESERVED21;
  vu16 DR19;
  u16  RESERVED22;
  vu16 DR20;
  u16  RESERVED23;
  vu16 DR21;
  u16  RESERVED24;
  vu16 DR22;
  u16  RESERVED25;
  vu16 DR23;
  u16  RESERVED26;
  vu16 DR24;
  u16  RESERVED27;
  vu16 DR25;
  u16  RESERVED28;
  vu16 DR26;
  u16  RESERVED29;
  vu16 DR27;
  u16  RESERVED30;
  vu16 DR28;
  u16  RESERVED31;
  vu16 DR29;
  u16  RESERVED32;
  vu16 DR30;
  u16  RESERVED33; 
  vu16 DR31;
  u16  RESERVED34;
  vu16 DR32;
  u16  RESERVED35;
  vu16 DR33;
  u16  RESERVED36;
  vu16 DR34;
  u16  RESERVED37;
  vu16 DR35;
  u16  RESERVED38;
  vu16 DR36;
  u16  RESERVED39;
  vu16 DR37;
  u16  RESERVED40;
  vu16 DR38;
  u16  RESERVED41;
  vu16 DR39;
  u16  RESERVED42;
  vu16 DR40;
  u16  RESERVED43;
  vu16 DR41;
  u16  RESERVED44;
  vu16 DR42;
  u16  RESERVED45;    
} BKP_TypeDef;

 
typedef struct
{
  vu32 TIR;				
  vu32 TDTR;			
  vu32 TDLR;			
  vu32 TDHR;			
} CAN_TxMailBox_TypeDef;

typedef struct
{
  vu32 RIR;				
  vu32 RDTR;			
  vu32 RDLR;			
  vu32 RDHR;			
} CAN_FIFOMailBox_TypeDef;

typedef struct
{
  vu32 FR1;			
  vu32 FR2;			
} CAN_FilterRegister_TypeDef;

typedef struct
{
  vu32 MCR;			
  vu32 MSR;			
  vu32 TSR;			
  vu32 RF0R;		
  vu32 RF1R;		
  vu32 IER;			
  vu32 ESR;			
  vu32 BTR;			
  u32  RESERVED0[88];													
  CAN_TxMailBox_TypeDef sTxMailBox[3];				
  CAN_FIFOMailBox_TypeDef sFIFOMailBox[2];		
  u32  RESERVED1[12];		
  vu32 FMR;							
  vu32 FM1R;						
  u32  RESERVED2;				
  vu32 FS1R;						
  u32  RESERVED3;				
  vu32 FFA1R;						
  u32  RESERVED4;				
  vu32 FA1R;						
  u32  RESERVED5[8];		
  CAN_FilterRegister_TypeDef sFilterRegister[14];				
} CAN_TypeDef;

 
typedef struct
{
  vu32 DR;				
  vu8  IDR;				
  u8   RESERVED0;	
  u16  RESERVED1;	
  vu32 CR;				
} CRC_TypeDef;


 
typedef struct
{
  vu32 CR;				
  vu32 SWTRIGR;		
  vu32 DHR12R1;		
  vu32 DHR12L1;		
  vu32 DHR8R1;		
  vu32 DHR12R2;		
  vu32 DHR12L2;		
  vu32 DHR8R2;		
  vu32 DHR12RD;		
  vu32 DHR12LD;		
  vu32 DHR8RD;		
  vu32 DOR1;			
  vu32 DOR2;			
} DAC_TypeDef;

 
typedef struct
{
  vu32 IDCODE;
  vu32 CR;	
}DBGMCU_TypeDef;

 
typedef struct
{
  vu32 CCR;					
  vu32 CNDTR;				
  vu32 CPAR;				
  vu32 CMAR;				
} DMA_Channel_TypeDef;

typedef struct
{
  vu32 ISR;					
  vu32 IFCR;				
} DMA_TypeDef;

 
typedef struct
{
  vu32 IMR;			
  vu32 EMR;			
  vu32 RTSR;		
  vu32 FTSR;		
  vu32 SWIER;		
  vu32 PR;			
} EXTI_TypeDef;

 
typedef struct
{
  vu32 ACR;				
  vu32 KEYR;			
  vu32 OPTKEYR;		
  vu32 SR;				
  vu32 CR;				
  vu32 AR;				
  vu32 RESERVED;	
  vu32 OBR;				
  vu32 WRPR;			
} FLASH_TypeDef;

typedef struct
{
  vu16 RDP;
  vu16 USER;
  vu16 Data0;
  vu16 Data1;
  vu16 WRP0;
  vu16 WRP1;
  vu16 WRP2;
  vu16 WRP3;
} OB_TypeDef;

 
typedef struct
{
  vu32 BTCR[8];   
} FSMC_Bank1_TypeDef; 

typedef struct
{
  vu32 BWTR[7];
} FSMC_Bank1E_TypeDef;

typedef struct
{
  vu32 PCR2;
  vu32 SR2;
  vu32 PMEM2;
  vu32 PATT2;
  u32  RESERVED0;   
  vu32 ECCR2; 
} FSMC_Bank2_TypeDef;  

typedef struct
{
  vu32 PCR3;
  vu32 SR3;
  vu32 PMEM3;
  vu32 PATT3;
  u32  RESERVED0;   
  vu32 ECCR3; 
} FSMC_Bank3_TypeDef; 

typedef struct
{
  vu32 PCR4;
  vu32 SR4;
  vu32 PMEM4;
  vu32 PATT4;
  vu32 PIO4; 
} FSMC_Bank4_TypeDef; 

 		
typedef struct
{
  vu32 CRL;		
  vu32 CRH;		
  vu32 IDR;		
  vu32 ODR;		
  vu32 BSRR;	
  vu32 BRR;		
  vu32 LCKR;	
} GPIO_TypeDef;

typedef struct
{
  vu32 EVCR;			
  vu32 MAPR;			
  vu32 EXTICR[4];	
} AFIO_TypeDef;

 
typedef struct
{
  vu16 CR1;
  u16  RESERVED0;
  vu16 CR2;
  u16  RESERVED1;
  vu16 OAR1;
  u16  RESERVED2;
  vu16 OAR2;
  u16  RESERVED3;
  vu16 DR;
  u16  RESERVED4;
  vu16 SR1;
  u16  RESERVED5;
  vu16 SR2;
  u16  RESERVED6;
  vu16 CCR;
  u16  RESERVED7;
  vu16 TRISE;
  u16  RESERVED8;
} I2C_TypeDef;

 		
typedef struct
{
  vu32 KR;		
  vu32 PR;		
  vu32 RLR;		
  vu32 SR;		
} IWDG_TypeDef;

 
typedef struct
{
  vu32 ISER[2];
  u32  RESERVED0[30];
  vu32 ICER[2];
  u32  RSERVED1[30];
  vu32 ISPR[2];
  u32  RESERVED2[30];
  vu32 ICPR[2];
  u32  RESERVED3[30];
  vu32 IABR[2];
  u32  RESERVED4[62];
  vu32 IPR[15];
} NVIC_TypeDef;

typedef struct
{
  vuc32 CPUID;
  vu32 ICSR;
  vu32 VTOR;
  vu32 AIRCR;
  vu32 SCR;
  vu32 CCR;
  vu32 SHPR[3];
  vu32 SHCSR;
  vu32 CFSR;
  vu32 HFSR;
  vu32 DFSR;
  vu32 MMFAR;
  vu32 BFAR;
  vu32 AFSR;
} SCB_TypeDef;

 		
typedef struct
{
  vu32 CR;			
  vu32 CSR;			
} PWR_TypeDef;

 	
typedef struct
{
  vu32 CR;				
  vu32 CFGR;			
  vu32 CIR;				
  vu32 APB2RSTR;	
  vu32 APB1RSTR;	
  vu32 AHBENR;		
  vu32 APB2ENR;		
  vu32 APB1ENR;		
  vu32 BDCR;			
  vu32 CSR;				
} RCC_TypeDef;

 		
typedef struct
{
  vu16 CRH;					
  u16  RESERVED0;		
  vu16 CRL;					
  u16  RESERVED1;		
  vu16 PRLH;				
  u16  RESERVED2;		
  vu16 PRLL;				
  u16  RESERVED3;		
  vu16 DIVH;				
  u16  RESERVED4;		
  vu16 DIVL;				
  u16  RESERVED5;		
  vu16 CNTH;				
  u16  RESERVED6;		
  vu16 CNTL;				
  u16  RESERVED7;		
  vu16 ALRH;				
  u16  RESERVED8;		
  vu16 ALRL;				
  u16  RESERVED9;
} RTC_TypeDef;

 		
typedef struct
{
  vu32 POWER;						
  vu32 CLKCR;						
  vu32 ARG;							
  vu32 CMD;							
  vuc32 RESPCMD;				
  vuc32 RESP1;					
  vuc32 RESP2;					
  vuc32 RESP3;					
  vuc32 RESP4;					
  vu32 DTIMER;					
  vu32 DLEN;						
  vu32 DCTRL;						
  vuc32 DCOUNT;					
  vuc32 STA;						
  vu32 ICR;							
  vu32 MASK;						
  u32  RESERVED0[2];		
  vuc32 FIFOCNT;				
  u32  RESERVED1[13];		
  vu32 FIFO;						
} SDIO_TypeDef;

 		
typedef struct
{
  vu16 CR1;					
  u16  RESERVED0;
  vu16 CR2;					
  u16  RESERVED1;
  vu16 SR;					
  u16  RESERVED2;
  vu16 DR;					
  u16  RESERVED3;
  vu16 CRCPR;				
  u16  RESERVED4;
  vu16 RXCRCR;			
  u16  RESERVED5;
  vu16 TXCRCR;			
  u16  RESERVED6;
  vu16 I2SCFGR;			
  u16  RESERVED7;
  vu16 I2SPR;				
  u16  RESERVED8;  
} SPI_TypeDef;

 
typedef struct
{
  vu32 CTRL;			
  vu32 LOAD;			
  vu32 VAL;				
  vuc32 CALIB;		
} SysTick_TypeDef;

 
typedef struct
{
  vu16 CR1;					
  u16  RESERVED0;
  vu16 CR2;					
  u16  RESERVED1;
  vu16 SMCR;				
  u16  RESERVED2;
  vu16 DIER;				
  u16  RESERVED3;
  vu16 SR;					
  u16  RESERVED4;
  vu16 EGR;					
  u16  RESERVED5;
  vu16 CCMR1;				
  u16  RESERVED6;
  vu16 CCMR2;				
  u16  RESERVED7;
  vu16 CCER;				
  u16  RESERVED8;
  vu16 CNT;					
  u16  RESERVED9;
  vu16 PSC;					
  u16  RESERVED10;
  vu16 ARR;					
  u16  RESERVED11;
  vu16 RCR;					
  u16  RESERVED12;
  vu16 CCR1;				
  u16  RESERVED13;
  vu16 CCR2;				
  u16  RESERVED14;
  vu16 CCR3;				
  u16  RESERVED15;
  vu16 CCR4;				
  u16  RESERVED16;
  vu16 BDTR;				
  u16  RESERVED17;
  vu16 DCR;					
  u16  RESERVED18;
  vu16 DMAR;				
  u16  RESERVED19;
} TIM_TypeDef;

 	
typedef struct
{
  vu16 SR;					
  u16  RESERVED0;
  vu16 DR;					
  u16  RESERVED1;
  vu16 BRR;					
  u16  RESERVED2;
  vu16 CR1;					
  u16  RESERVED3;
  vu16 CR2;					
  u16  RESERVED4;
  vu16 CR3;					
  u16  RESERVED5;
  vu16 GTPR;				
  u16  RESERVED6;
} USART_TypeDef;

 		
typedef struct
{
  vu32 CR;		
  vu32 CFR;		
  vu32 SR;		
} WWDG_TypeDef;

 
 
 
 



 



 


 




#line 634 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_map.h"

#line 651 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_map.h"



#line 670 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_map.h"

 

 


 






 


 






 
 
 

 



























































































































































































































#line 924 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_map.h"














 
#line 1180 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_map.h"

 
 
 



 
#line 31 "..\\..\\Driver\\WOW\\INC\\STM32F10x_BitBand.h"
 


 





#line 47 "..\\..\\Driver\\WOW\\INC\\STM32F10x_BitBand.h"
  
#line 55 "..\\..\\Driver\\WOW\\INC\\STM32F10x_BitBand.h"

 
 
 
 
 
#line 68 "..\\..\\Driver\\WOW\\INC\\STM32F10x_BitBand.h"

#line 76 "..\\..\\Driver\\WOW\\INC\\STM32F10x_BitBand.h"
 
#line 84 "..\\..\\Driver\\WOW\\INC\\STM32F10x_BitBand.h"

 
 
 
 
#line 103 "..\\..\\Driver\\WOW\\INC\\STM32F10x_BitBand.h"

 
 
 
 
#line 124 "..\\..\\Driver\\WOW\\INC\\STM32F10x_BitBand.h"

#line 141 "..\\..\\Driver\\WOW\\INC\\STM32F10x_BitBand.h"

 
#line 159 "..\\..\\Driver\\WOW\\INC\\STM32F10x_BitBand.h"

#line 176 "..\\..\\Driver\\WOW\\INC\\STM32F10x_BitBand.h"
 
#line 193 "..\\..\\Driver\\WOW\\INC\\STM32F10x_BitBand.h"

#line 210 "..\\..\\Driver\\WOW\\INC\\STM32F10x_BitBand.h"

 
#line 228 "..\\..\\Driver\\WOW\\INC\\STM32F10x_BitBand.h"

#line 245 "..\\..\\Driver\\WOW\\INC\\STM32F10x_BitBand.h"

 
#line 263 "..\\..\\Driver\\WOW\\INC\\STM32F10x_BitBand.h"

#line 280 "..\\..\\Driver\\WOW\\INC\\STM32F10x_BitBand.h"
 
  
#line 298 "..\\..\\Driver\\WOW\\INC\\STM32F10x_BitBand.h"

#line 315 "..\\..\\Driver\\WOW\\INC\\STM32F10x_BitBand.h"

					 


 


#line 6 "..\\..\\Driver\\Components\\INC\\MMC_SD.h"

#line 1 "..\\..\\Driver\\WOW\\INC\\STM32_SPI.H"













 





#line 1 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_spi.h"














 

 



 
#line 23 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_spi.h"

 
 
typedef struct
{
  u16 SPI_Direction;					
  u16 SPI_Mode;								
  u16 SPI_DataSize;						
  u16 SPI_CPOL;								
  u16 SPI_CPHA;					 			
  u16 SPI_NSS;								
  u16 SPI_BaudRatePrescaler;	
  u16 SPI_FirstBit;						
  u16 SPI_CRCPolynomial;			
}SPI_InitTypeDef;

 
typedef struct
{
  u16 I2S_Mode;
  u16 I2S_Standard;
  u16 I2S_DataFormat;
  u16 I2S_MCLKOutput;
  u16 I2S_AudioFreq;
  u16 I2S_CPOL;
}I2S_InitTypeDef;

 








 










 






 






 






 






 






 
#line 114 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_spi.h"

#line 123 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_spi.h"

 






 










 












 










  






 
#line 180 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_spi.h"

#line 187 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_spi.h"

 






 





 






 





 






 






















 
#line 253 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_spi.h"

#line 260 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_spi.h"

 


 
 
void SPI_I2S_DeInit(SPI_TypeDef* SPIx);
void SPI_Init(SPI_TypeDef* SPIx, SPI_InitTypeDef* SPI_InitStruct);											
void I2S_Init(SPI_TypeDef* SPIx, I2S_InitTypeDef* I2S_InitStruct);
void SPI_StructInit(SPI_InitTypeDef* SPI_InitStruct);																		
void I2S_StructInit(I2S_InitTypeDef* I2S_InitStruct);
void SPI_Cmd(SPI_TypeDef* SPIx, FunctionalState NewState);															
void I2S_Cmd(SPI_TypeDef* SPIx, FunctionalState NewState);
void SPI_I2S_ITConfig(SPI_TypeDef* SPIx, u8 SPI_I2S_IT, FunctionalState NewState);			
void SPI_I2S_DMACmd(SPI_TypeDef* SPIx, u16 SPI_I2S_DMAReq, FunctionalState NewState);		
void SPI_I2S_SendData(SPI_TypeDef* SPIx, u16 Data);																			
u16 SPI_I2S_ReceiveData(SPI_TypeDef* SPIx);																							
void SPI_NSSInternalSoftwareConfig(SPI_TypeDef* SPIx, u16 SPI_NSSInternalSoft);					
void SPI_SSOutputCmd(SPI_TypeDef* SPIx, FunctionalState NewState);											
void SPI_DataSizeConfig(SPI_TypeDef* SPIx, u16 SPI_DataSize);														
void SPI_TransmitCRC(SPI_TypeDef* SPIx);																								
void SPI_CalculateCRC(SPI_TypeDef* SPIx, FunctionalState NewState);											
u16 SPI_GetCRC(SPI_TypeDef* SPIx, u8 SPI_CRC);																					
u16 SPI_GetCRCPolynomial(SPI_TypeDef* SPIx);																						
void SPI_BiDirectionalLineConfig(SPI_TypeDef* SPIx, u16 SPI_Direction);									
FlagStatus SPI_I2S_GetFlagStatus(SPI_TypeDef* SPIx, u16 SPI_I2S_FLAG);									
void SPI_I2S_ClearFlag(SPI_TypeDef* SPIx, u16 SPI_I2S_FLAG);														
ITStatus SPI_I2S_GetITStatus(SPI_TypeDef* SPIx, u8 SPI_I2S_IT);													
void SPI_I2S_ClearITPendingBit(SPI_TypeDef* SPIx, u8 SPI_I2S_IT);												



 
#line 21 "..\\..\\Driver\\WOW\\INC\\STM32_SPI.H"
#line 1 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_gpio.h"














 

 



 
#line 23 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_gpio.h"

 
#line 32 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_gpio.h"
                                     
 
typedef enum
{ 
  GPIO_Speed_10MHz = 1,
  GPIO_Speed_2MHz, 
  GPIO_Speed_50MHz
}GPIOSpeed_TypeDef;



                                         
 
typedef enum
{ 
	GPIO_Mode_AIN 		= 0x0,
  GPIO_Mode_IN_FLOATING = 0x04,
  GPIO_Mode_IPD 		= 0x28,
  GPIO_Mode_IPU 		= 0x48,
  GPIO_Mode_Out_OD 	= 0x14,
  GPIO_Mode_Out_PP 	= 0x10,
  GPIO_Mode_AF_OD 	= 0x1C,
  GPIO_Mode_AF_PP 	= 0x18
}GPIOMode_TypeDef;





                              
 
typedef struct
{
  u16 GPIO_Pin;
  GPIOSpeed_TypeDef GPIO_Speed;
  GPIOMode_TypeDef GPIO_Mode;
}GPIO_InitTypeDef;

 
typedef enum
{ Bit_RESET = 0,
  Bit_SET
}BitAction;


 
 
#line 96 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_gpio.h"



#line 115 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_gpio.h"
                            
 
#line 142 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_gpio.h"


#line 157 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_gpio.h"
                              
 
#line 166 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_gpio.h"






                                         
#line 180 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_gpio.h"
                                       
 
#line 198 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_gpio.h"

#line 215 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_gpio.h"
                          
 
 
void GPIO_DeInit(GPIO_TypeDef* GPIOx);
void GPIO_AFIODeInit(void);
void GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct);
void GPIO_StructInit(GPIO_InitTypeDef* GPIO_InitStruct);
u8 GPIO_ReadInputDataBit(GPIO_TypeDef* GPIOx, u16 GPIO_Pin);
u16 GPIO_ReadInputData(GPIO_TypeDef* GPIOx);
u8 GPIO_ReadOutputDataBit(GPIO_TypeDef* GPIOx, u16 GPIO_Pin);
u16 GPIO_ReadOutputData(GPIO_TypeDef* GPIOx);
void GPIO_SetBits(GPIO_TypeDef* GPIOx, u16 GPIO_Pin);
void GPIO_ResetBits(GPIO_TypeDef* GPIOx, u16 GPIO_Pin);
void GPIO_WriteBit(GPIO_TypeDef* GPIOx, u16 GPIO_Pin, BitAction BitVal);
void GPIO_Write(GPIO_TypeDef* GPIOx, u16 PortVal);
void GPIO_PinLockConfig(GPIO_TypeDef* GPIOx, u16 GPIO_Pin);
void GPIO_EventOutputConfig(u8 GPIO_PortSource, u8 GPIO_PinSource);
void GPIO_EventOutputCmd(FunctionalState NewState);
void GPIO_PinRemapConfig(u32 GPIO_Remap, FunctionalState NewState);
void GPIO_EXTILineConfig(u8 GPIO_PortSource, u8 GPIO_PinSource);



 
#line 22 "..\\..\\Driver\\WOW\\INC\\STM32_SPI.H"














typedef struct	_SPIPort
{
	
	SPI_TypeDef *			SPIx;				

	
	GPIO_TypeDef* 	CS_PORT;		
	unsigned short 	CS_Pin;			

	
	GPIO_TypeDef* 	CLK_PORT;		
	unsigned short 	CLK_Pin;		

	
	GPIO_TypeDef* 	MISO_PORT;	
	unsigned short 	MISO_Pin;		

	
	GPIO_TypeDef* 	MOSI_PORT;	
	unsigned short 	MOSI_Pin;		
	
	
	unsigned short 	SPI_BaudRatePrescaler_x;		
	
}SPIPortDef;










typedef struct	
{
	SPIPortDef		Port;
	
}SPIDef;

















void SPI_Initialize(SPIDef* pInfo);		
	
void SPI_InitializeNR(SPIDef* pInfo);							

void SPI_InitializeSPI(SPIDef *pInfo);		
void SPI_InitializeDMA(SPIDef *pInfo);			


unsigned short SPI_DMASend(SPI_TypeDef* SPIx,unsigned char *tx_buffer,unsigned short BufferSize);
unsigned short SPI_DMAReadWrite(SPI_TypeDef* SPIx,unsigned char *tx_buffer,unsigned char *rx_buffer,unsigned short BufferSize);


void SPI_CS_LOW(SPIDef *pInfo);
void SPI_CS_HIGH(SPIDef *pInfo);
void SPI_CLK_LOW(SPIDef *pInfo);
void SPI_CLK_HIGH(SPIDef *pInfo);
void SPI_MOSI_LOW(SPIDef *pInfo);
void SPI_MOSI_HIGH(SPIDef *pInfo);
unsigned char SPI_MISO_In(SPIDef *pInfo);

unsigned char	SPI_ReadWriteByteNR(SPIDef *pInfo,unsigned char Byte);
unsigned char	SPI_ReadWriteByteSPI(SPIDef *pInfo,unsigned char Byte);






void SPI_WriteBufferSPI(SPIDef *pInfo,u8 *Buffer,u16 BufferSize);
void SPI_ReadBufferSPI(SPIDef *pInfo,u8 *Buffer,u16 BufferSize);









































































































#line 8 "..\\..\\Driver\\Components\\INC\\MMC_SD.h"













 						    	 

#line 29 "..\\..\\Driver\\Components\\INC\\MMC_SD.h"

#line 46 "..\\..\\Driver\\Components\\INC\\MMC_SD.h"






#line 61 "..\\..\\Driver\\Components\\INC\\MMC_SD.h"
 							   						 	 




extern u8  SD_Type;			

u8 SD_SPI_ReadWriteByte(u8 data);
void SD_SPI_SpeedLow(void);
void SD_SPI_SpeedHigh(void);
u8 SD_WaitReady(void);							


u8 SD_Initialize(SPIDef *SpiPort);							



unsigned char SD_ReadDisk(u8*buf,u32 sector,u8 cnt);		
unsigned char SD_WriteDisk(u8*buf,u32 sector,u8 cnt);   
u32 SD_GetSectorCount(void);   					    
unsigned char SD_GetCID(u8 *cid_data);      
unsigned char SD_GetCSD(u8 *csd_data);      






void SD_DisSelect(void);
unsigned char SD_Select(void);
unsigned char SD_WaitReady(void);
unsigned char SD_GetResponse(u8 Response);          
unsigned char SD_RecvData(u8*buf,u16 len);          
unsigned char SD_SendBlock(u8*buf,u8 cmd);          
unsigned char SD_SendCmd(u8 cmd, u32 arg, u8 crc);  




unsigned char SPI1_ReadWriteByte(u8 TxData);
unsigned char SD_SPI_ReadWriteByte(u8 data);
void SD_SPI_SpeedLow(void);
void SD_SPI_SpeedHigh(void);
 





#line 26 "..\\..\\Driver\\FatFs\\source\\FatFsAPI.h"


bool ByteCmp(char,char);

int SD_disk_initialize(void);
int SD_disk_status(void);
int SD_disk_read(BYTE *buff,DWORD sector,UINT count);
int SD_disk_write(const BYTE *buff,DWORD sector,UINT count);


unsigned char SD_disk_getcapacity(unsigned char *drv,unsigned long *total,unsigned long *free);   
bool FilSearch(FATFS *fs,DIR *dir,TCHAR *path,u8 *name,char (*p)[13]);  


#line 12 "..\\..\\Driver\\FatFs\\source\\diskio.c"

 





 
 
 






__weak int MMC_disk_status(void)
{
  return 0;
}
__weak int USB_disk_status(void)
{
  return 0;
}





__weak int MMC_disk_initialize(void)
{
  return 0;
}
__weak int USB_disk_initialize(void)
{
  return 0;
}





__weak int MMC_disk_read(BYTE *buff,DWORD sector,UINT count)
{
  return 0;
}
__weak int USB_disk_read(BYTE *buff,DWORD sector,UINT count)
{
  return 0;
}





__weak int MMC_disk_write(const BYTE *buff,DWORD sector,UINT count)
{
  return 0;
}
__weak int USB_disk_write(const BYTE *buff,DWORD sector,UINT count)
{
  return 0;
}

DSTATUS disk_status (
	BYTE pdrv		 
)
{
	DSTATUS stat;
	int result;

	switch (pdrv) {
	case 0 :

    
		
    result = SD_disk_status();
		return stat;

	case 1 :
		result = MMC_disk_status();

		

		return stat;

	case 2 :
		result = USB_disk_status();

		

		return stat;
	}
	return 0x01;
}



 
 
 

DSTATUS disk_initialize (
	BYTE pdrv				 
)
{
	DSTATUS stat;
	int result;

	switch (pdrv)
  {
	case 0 :

    

    
    result = SD_disk_initialize();

		return stat;

	case 1 :
		result = MMC_disk_initialize();

		

		return stat;

	case 2 :
		result = USB_disk_initialize();

		

		return stat;
	}
	return 0x01;
}



 
 
 













 
DRESULT disk_read (
	BYTE pdrv,		 
	BYTE *buff,		 
	DWORD sector,	 
	UINT count		 
)
{
	DRESULT res;


	switch (pdrv) {
	case 0 :
    


		
    res = SD_disk_read(buff, sector, count);

		return res;

	case 1 :
		

		res = MMC_disk_read(buff, sector, count);

		

		return res;

	case 2 :
		

		res = USB_disk_read(buff, sector, count);

		

		return res;
	}

	return RES_PARERR;
}



 
 
 













 
DRESULT disk_write (
                    BYTE pdrv,			   
                    const BYTE *buff,	 
                    DWORD sector,		   
                    UINT count			   
)
{
	DRESULT res;
	int result;

	switch (pdrv) {
	case 0 :
		



		
    result = SD_disk_write(buff, sector, count);
		return res;

	case 1 :
		

		result = MMC_disk_write(buff, sector, count);

		

		return res;

	case 2 :
		

		result = USB_disk_write(buff, sector, count);

		

		return res;
	}

	return RES_PARERR;
}



 
 
 

DRESULT disk_ioctl (
	BYTE pdrv,   
	BYTE cmd,		 
	void *buff   
)
{
	DRESULT res;
	int result;

	switch (pdrv) {
	case 0 :

		

		return res;

	case 1 :

		

		return res;

	case 2 :

		

		return res;
	}

	return RES_PARERR;
}

