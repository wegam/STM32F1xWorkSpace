#line 1 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\SCR\\stm32f10x_fsmc.c"













 

 
#line 1 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_fsmc.h"














 

 



 
#line 1 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_map.h"














 

 







 
#line 1 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_conf.h"













 

 



 
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

 
 
 



 
#line 23 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_fsmc.h"

 
 
typedef struct
{
  u32 FSMC_AddressSetupTime;
  u32 FSMC_AddressHoldTime;
  u32 FSMC_DataSetupTime;
  u32 FSMC_BusTurnAroundDuration;
  u32 FSMC_CLKDivision;
  u32 FSMC_DataLatency;
  u32 FSMC_AccessMode;
}FSMC_NORSRAMTimingInitTypeDef;

 
typedef struct
{
  u32 FSMC_Bank;
  u32 FSMC_DataAddressMux;
  u32 FSMC_MemoryType;
  u32 FSMC_MemoryDataWidth;
  u32 FSMC_BurstAccessMode;
  u32 FSMC_WaitSignalPolarity;
  u32 FSMC_WrapMode;
  u32 FSMC_WaitSignalActive;
  u32 FSMC_WriteOperation;
  u32 FSMC_WaitSignal;
  u32 FSMC_ExtendedMode;
  u32 FSMC_AsyncWait;
  u32 FSMC_WriteBurst;
   
  FSMC_NORSRAMTimingInitTypeDef* FSMC_ReadWriteTimingStruct;
   
  FSMC_NORSRAMTimingInitTypeDef* FSMC_WriteTimingStruct;
}FSMC_NORSRAMInitTypeDef;

 
typedef struct
{
  u32 FSMC_SetupTime;
  u32 FSMC_WaitSetupTime;
  u32 FSMC_HoldSetupTime;
  u32 FSMC_HiZSetupTime;
}FSMC_NAND_PCCARDTimingInitTypeDef;

 
typedef struct
{
  u32 FSMC_Bank;
  u32 FSMC_Waitfeature;
  u32 FSMC_MemoryDataWidth;
  u32 FSMC_ECC;
  u32 FSMC_ECCPageSize;
  u32 FSMC_AddressLowMapping;
  u32 FSMC_TCLRSetupTime;
  u32 FSMC_TARSetupTime;
   
  FSMC_NAND_PCCARDTimingInitTypeDef*  FSMC_CommonSpaceTimingStruct;
   
  FSMC_NAND_PCCARDTimingInitTypeDef*  FSMC_AttributeSpaceTimingStruct;
}FSMC_NANDInitTypeDef;

 
typedef struct
{
  u32 FSMC_Waitfeature;
  u32 FSMC_AddressLowMapping;
  u32 FSMC_TCLRSetupTime;
  u32 FSMC_TARSetupTime;
   
  FSMC_NAND_PCCARDTimingInitTypeDef*  FSMC_CommonSpaceTimingStruct;
   
  FSMC_NAND_PCCARDTimingInitTypeDef*  FSMC_AttributeSpaceTimingStruct;
   
  FSMC_NAND_PCCARDTimingInitTypeDef*  FSMC_IOSpaceTimingStruct;
}FSMC_PCCARDInitTypeDef;

 
 
#line 109 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_fsmc.h"













                                    





 
 






 









                                     
 





                                      
                               
 






                                   





                                        
  





                                 
                                  





                                    
 





                              
 






 





                               
 





                                  
                                   






 


 


 


 


 


 


 









                                  
 
 





                                    
 





                                    
 





                                            
 
#line 276 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_fsmc.h"

#line 283 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_fsmc.h"
                                                              
 





 


 


 


 


 


 


 










 











 
 
void FSMC_NORSRAMDeInit(u32 FSMC_Bank);
void FSMC_NANDDeInit(u32 FSMC_Bank);
void FSMC_PCCARDDeInit(void);
void FSMC_NORSRAMInit(FSMC_NORSRAMInitTypeDef* FSMC_NORSRAMInitStruct);
void FSMC_NANDInit(FSMC_NANDInitTypeDef* FSMC_NANDInitStruct);
void FSMC_PCCARDInit(FSMC_PCCARDInitTypeDef* FSMC_PCCARDInitStruct);
void FSMC_NORSRAMStructInit(FSMC_NORSRAMInitTypeDef* FSMC_NORSRAMInitStruct);
void FSMC_NANDStructInit(FSMC_NANDInitTypeDef* FSMC_NANDInitStruct);
void FSMC_PCCARDStructInit(FSMC_PCCARDInitTypeDef* FSMC_PCCARDInitStruct);
void FSMC_NORSRAMCmd(u32 FSMC_Bank, FunctionalState NewState);
void FSMC_NANDCmd(u32 FSMC_Bank, FunctionalState NewState);
void FSMC_PCCARDCmd(FunctionalState NewState);
void FSMC_NANDECCCmd(u32 FSMC_Bank, FunctionalState NewState);
u32 FSMC_GetECC(u32 FSMC_Bank);
void FSMC_ITConfig(u32 FSMC_Bank, u32 FSMC_IT, FunctionalState NewState);
FlagStatus FSMC_GetFlagStatus(u32 FSMC_Bank, u32 FSMC_FLAG);
void FSMC_ClearFlag(u32 FSMC_Bank, u32 FSMC_FLAG);
ITStatus FSMC_GetITStatus(u32 FSMC_Bank, u32 FSMC_IT);
void FSMC_ClearITPendingBit(u32 FSMC_Bank, u32 FSMC_IT);



 
#line 18 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\SCR\\stm32f10x_fsmc.c"
#line 1 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_rcc.h"














 

 



 
#line 23 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_rcc.h"

 
typedef struct
{
  u32 SYSCLK_Frequency;
  u32 HCLK_Frequency;
  u32 PCLK1_Frequency;
  u32 PCLK2_Frequency;
  u32 ADCCLK_Frequency;
}RCC_ClocksTypeDef;

 
 







 








 
#line 68 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_rcc.h"

#line 77 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_rcc.h"

 








 
#line 97 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_rcc.h"







 










 
#line 122 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_rcc.h"







 






 








 







 








 
#line 170 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_rcc.h"



 
#line 190 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_rcc.h"


#line 207 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_rcc.h"

 
#line 230 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_rcc.h"


#line 253 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_rcc.h"

 










 
#line 277 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_rcc.h"

#line 284 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_rcc.h"



 
 
void RCC_DeInit(void);										
void RCC_HSEConfig(u32 RCC_HSE);					
ErrorStatus RCC_WaitForHSEStartUp(void);	
void RCC_AdjustHSICalibrationValue(u8 HSICalibrationValue);		
void RCC_HSICmd(FunctionalState NewState);
void RCC_PLLConfig(u32 RCC_PLLSource, u32 RCC_PLLMul);	
void RCC_PLLCmd(FunctionalState NewState);							
void RCC_SYSCLKConfig(u32 RCC_SYSCLKSource);						
u8 RCC_GetSYSCLKSource(void);														
void RCC_HCLKConfig(u32 RCC_SYSCLK);										
void RCC_PCLK1Config(u32 RCC_HCLK);											
void RCC_PCLK2Config(u32 RCC_HCLK);											
void RCC_ITConfig(u8 RCC_IT, FunctionalState NewState);	
void RCC_USBCLKConfig(u32 RCC_USBCLKSource);						
void RCC_ADCCLKConfig(u32 RCC_PCLK2);										
void RCC_LSEConfig(u8 RCC_LSE);													
void RCC_LSICmd(FunctionalState NewState);							
void RCC_RTCCLKConfig(u32 RCC_RTCCLKSource);						
void RCC_RTCCLKCmd(FunctionalState NewState);						
void RCC_GetClocksFreq(RCC_ClocksTypeDef* RCC_Clocks);	
void RCC_AHBPeriphClockCmd(u32 RCC_AHBPeriph, FunctionalState NewState);		
void RCC_APB2PeriphClockCmd(u32 RCC_APB2Periph, FunctionalState NewState);	
void RCC_APB1PeriphClockCmd(u32 RCC_APB1Periph, FunctionalState NewState);	
void RCC_APB2PeriphResetCmd(u32 RCC_APB2Periph, FunctionalState NewState);	
void RCC_APB1PeriphResetCmd(u32 RCC_APB1Periph, FunctionalState NewState);	
void RCC_BackupResetCmd(FunctionalState NewState);					
void RCC_ClockSecuritySystemCmd(FunctionalState NewState);	
void RCC_MCOConfig(u8 RCC_MCO);									
FlagStatus RCC_GetFlagStatus(u8 RCC_FLAG);			
void RCC_ClearFlag(void);												
ITStatus RCC_GetITStatus(u8 RCC_IT);						
void RCC_ClearITPendingBit(u8 RCC_IT);					



 
#line 19 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\SCR\\stm32f10x_fsmc.c"

 
 
 
 




 






 
 
 
 













 
void FSMC_NORSRAMDeInit(u32 FSMC_Bank)
{
   
  ((void)0);
  
   
  if(FSMC_Bank == ((u32)0x00000000))
  {
    ((FSMC_Bank1_TypeDef *) (((u32)0xA0000000) + 0x0000))->BTCR[FSMC_Bank] = 0x000030DB;    
  }
   
  else
  {   
    ((FSMC_Bank1_TypeDef *) (((u32)0xA0000000) + 0x0000))->BTCR[FSMC_Bank] = 0x000030D2; 
  }

  ((FSMC_Bank1_TypeDef *) (((u32)0xA0000000) + 0x0000))->BTCR[FSMC_Bank + 1] = 0x0FFFFFFF;
  ((FSMC_Bank1E_TypeDef *) (((u32)0xA0000000) + 0x0104))->BWTR[FSMC_Bank] = 0x0FFFFFFF;  
}











 
void FSMC_NANDDeInit(u32 FSMC_Bank)
{
   
  ((void)0);
  
  if(FSMC_Bank == ((u32)0x00000010))
  {
     
    ((FSMC_Bank2_TypeDef *) (((u32)0xA0000000) + 0x0060))->PCR2 = 0x00000018;
    ((FSMC_Bank2_TypeDef *) (((u32)0xA0000000) + 0x0060))->SR2 = 0x00000040;
    ((FSMC_Bank2_TypeDef *) (((u32)0xA0000000) + 0x0060))->PMEM2 = 0xFCFCFCFC;
    ((FSMC_Bank2_TypeDef *) (((u32)0xA0000000) + 0x0060))->PATT2 = 0xFCFCFCFC;  
  }
     
  else
  {
     
    ((FSMC_Bank3_TypeDef *) (((u32)0xA0000000) + 0x0080))->PCR3 = 0x00000018;
    ((FSMC_Bank3_TypeDef *) (((u32)0xA0000000) + 0x0080))->SR3 = 0x00000040;
    ((FSMC_Bank3_TypeDef *) (((u32)0xA0000000) + 0x0080))->PMEM3 = 0xFCFCFCFC;
    ((FSMC_Bank3_TypeDef *) (((u32)0xA0000000) + 0x0080))->PATT3 = 0xFCFCFCFC; 
  }  
}








 
void FSMC_PCCARDDeInit(void)
{
   
  ((FSMC_Bank4_TypeDef *) (((u32)0xA0000000) + 0x00A0))->PCR4 = 0x00000018; 
  ((FSMC_Bank4_TypeDef *) (((u32)0xA0000000) + 0x00A0))->SR4 = 0x00000000;	
  ((FSMC_Bank4_TypeDef *) (((u32)0xA0000000) + 0x00A0))->PMEM4 = 0xFCFCFCFC;
  ((FSMC_Bank4_TypeDef *) (((u32)0xA0000000) + 0x00A0))->PATT4 = 0xFCFCFCFC;
  ((FSMC_Bank4_TypeDef *) (((u32)0xA0000000) + 0x00A0))->PIO4 = 0xFCFCFCFC;
}










 
void FSMC_NORSRAMInit(FSMC_NORSRAMInitTypeDef* FSMC_NORSRAMInitStruct)
{ 
   
  ((void)0);
  ((void)0);
  ((void)0);
  ((void)0);
  ((void)0);
  ((void)0);
  ((void)0);
  ((void)0);
  ((void)0);
  ((void)0);
  ((void)0);
  ((void)0);
  ((void)0);  
  ((void)0);
  ((void)0);
  ((void)0);
  ((void)0);
  ((void)0);
  ((void)0);
  ((void)0); 
  
    
  ((FSMC_Bank1_TypeDef *) (((u32)0xA0000000) + 0x0000))->BTCR[FSMC_NORSRAMInitStruct->FSMC_Bank] = 
            (u32)FSMC_NORSRAMInitStruct->FSMC_DataAddressMux |
            FSMC_NORSRAMInitStruct->FSMC_MemoryType |
            FSMC_NORSRAMInitStruct->FSMC_MemoryDataWidth |
            FSMC_NORSRAMInitStruct->FSMC_BurstAccessMode |
            FSMC_NORSRAMInitStruct->FSMC_WaitSignalPolarity |
            FSMC_NORSRAMInitStruct->FSMC_WrapMode |
            FSMC_NORSRAMInitStruct->FSMC_WaitSignalActive |
            FSMC_NORSRAMInitStruct->FSMC_WriteOperation |
            FSMC_NORSRAMInitStruct->FSMC_WaitSignal |
            FSMC_NORSRAMInitStruct->FSMC_ExtendedMode |
            FSMC_NORSRAMInitStruct->FSMC_AsyncWait |
            FSMC_NORSRAMInitStruct->FSMC_WriteBurst;

  if(FSMC_NORSRAMInitStruct->FSMC_MemoryType == ((u32)0x00000008))
  {
    ((FSMC_Bank1_TypeDef *) (((u32)0xA0000000) + 0x0000))->BTCR[FSMC_NORSRAMInitStruct->FSMC_Bank] |= (u32)((u32)0x00000040);
  }

   
  ((FSMC_Bank1_TypeDef *) (((u32)0xA0000000) + 0x0000))->BTCR[FSMC_NORSRAMInitStruct->FSMC_Bank+1] = 
            (u32)FSMC_NORSRAMInitStruct->FSMC_ReadWriteTimingStruct->FSMC_AddressSetupTime |
            (FSMC_NORSRAMInitStruct->FSMC_ReadWriteTimingStruct->FSMC_AddressHoldTime << 4) |
            (FSMC_NORSRAMInitStruct->FSMC_ReadWriteTimingStruct->FSMC_DataSetupTime << 8) |
            (FSMC_NORSRAMInitStruct->FSMC_ReadWriteTimingStruct->FSMC_BusTurnAroundDuration << 16) |
            (FSMC_NORSRAMInitStruct->FSMC_ReadWriteTimingStruct->FSMC_CLKDivision << 20) |
            (FSMC_NORSRAMInitStruct->FSMC_ReadWriteTimingStruct->FSMC_DataLatency << 24) |
             FSMC_NORSRAMInitStruct->FSMC_ReadWriteTimingStruct->FSMC_AccessMode;
            

    
   
  if(FSMC_NORSRAMInitStruct->FSMC_ExtendedMode == ((u32)0x00004000))
  {
    ((void)0);
    ((void)0);
    ((void)0);
    ((void)0);
    ((void)0);
    ((void)0);
    ((void)0);

    ((FSMC_Bank1E_TypeDef *) (((u32)0xA0000000) + 0x0104))->BWTR[FSMC_NORSRAMInitStruct->FSMC_Bank] = 
              (u32)FSMC_NORSRAMInitStruct->FSMC_WriteTimingStruct->FSMC_AddressSetupTime |
              (FSMC_NORSRAMInitStruct->FSMC_WriteTimingStruct->FSMC_AddressHoldTime << 4 )|
              (FSMC_NORSRAMInitStruct->FSMC_WriteTimingStruct->FSMC_DataSetupTime << 8) |
              (FSMC_NORSRAMInitStruct->FSMC_WriteTimingStruct->FSMC_BusTurnAroundDuration << 16) |
              (FSMC_NORSRAMInitStruct->FSMC_WriteTimingStruct->FSMC_CLKDivision << 20) |
              (FSMC_NORSRAMInitStruct->FSMC_WriteTimingStruct->FSMC_DataLatency << 24) |
               FSMC_NORSRAMInitStruct->FSMC_WriteTimingStruct->FSMC_AccessMode;
  }
  else
  {
    ((FSMC_Bank1E_TypeDef *) (((u32)0xA0000000) + 0x0104))->BWTR[FSMC_NORSRAMInitStruct->FSMC_Bank] = 0x0FFFFFFF;
  }
}










 
void FSMC_NANDInit(FSMC_NANDInitTypeDef* FSMC_NANDInitStruct)
{
  u32 tmppcr = 0x00000000, tmppmem = 0x00000000, tmppatt = 0x00000000; 
    
   
  ((void)0);
  ((void)0);
  ((void)0);
  ((void)0);
  ((void)0);
  ((void)0);
  ((void)0);
  ((void)0);

  ((void)0);
  ((void)0);
  ((void)0);
  ((void)0);

  ((void)0);
  ((void)0);
  ((void)0);
  ((void)0);
  
   
  tmppcr = (u32)FSMC_NANDInitStruct->FSMC_Waitfeature |
            ((u32)0x00000008) |
            FSMC_NANDInitStruct->FSMC_MemoryDataWidth |
            FSMC_NANDInitStruct->FSMC_ECC |
            FSMC_NANDInitStruct->FSMC_ECCPageSize |
            FSMC_NANDInitStruct->FSMC_AddressLowMapping |
            (FSMC_NANDInitStruct->FSMC_TCLRSetupTime << 9 )|
            (FSMC_NANDInitStruct->FSMC_TARSetupTime << 13);
            
   
  tmppmem = (u32)FSMC_NANDInitStruct->FSMC_CommonSpaceTimingStruct->FSMC_SetupTime |
            (FSMC_NANDInitStruct->FSMC_CommonSpaceTimingStruct->FSMC_WaitSetupTime << 8) |
            (FSMC_NANDInitStruct->FSMC_CommonSpaceTimingStruct->FSMC_HoldSetupTime << 16)|
            (FSMC_NANDInitStruct->FSMC_CommonSpaceTimingStruct->FSMC_HiZSetupTime << 24); 
            
   
  tmppatt = (u32)FSMC_NANDInitStruct->FSMC_AttributeSpaceTimingStruct->FSMC_SetupTime |
            (FSMC_NANDInitStruct->FSMC_AttributeSpaceTimingStruct->FSMC_WaitSetupTime << 8) |
            (FSMC_NANDInitStruct->FSMC_AttributeSpaceTimingStruct->FSMC_HoldSetupTime << 16)|
            (FSMC_NANDInitStruct->FSMC_AttributeSpaceTimingStruct->FSMC_HiZSetupTime << 24);
  
  if(FSMC_NANDInitStruct->FSMC_Bank == ((u32)0x00000010))
  {
     
    ((FSMC_Bank2_TypeDef *) (((u32)0xA0000000) + 0x0060))->PCR2 = tmppcr;
    ((FSMC_Bank2_TypeDef *) (((u32)0xA0000000) + 0x0060))->PMEM2 = tmppmem;
    ((FSMC_Bank2_TypeDef *) (((u32)0xA0000000) + 0x0060))->PATT2 = tmppatt;
  }
  else
  {
     
    ((FSMC_Bank3_TypeDef *) (((u32)0xA0000000) + 0x0080))->PCR3 = tmppcr;
    ((FSMC_Bank3_TypeDef *) (((u32)0xA0000000) + 0x0080))->PMEM3 = tmppmem;
    ((FSMC_Bank3_TypeDef *) (((u32)0xA0000000) + 0x0080))->PATT3 = tmppatt;
  }
}










 
void FSMC_PCCARDInit(FSMC_PCCARDInitTypeDef* FSMC_PCCARDInitStruct)
{
   
  ((void)0);
  ((void)0);
  ((void)0);
  ((void)0);

 
  ((void)0);
  ((void)0);
  ((void)0);
  ((void)0);
  
  ((void)0);
  ((void)0);
  ((void)0);
  ((void)0);

  ((void)0);
  ((void)0);
  ((void)0);
  ((void)0);
  
   
  ((FSMC_Bank4_TypeDef *) (((u32)0xA0000000) + 0x00A0))->PCR4 = (u32)FSMC_PCCARDInitStruct->FSMC_Waitfeature |
                     FSMC_PCCARDInitStruct->FSMC_AddressLowMapping |
                     (FSMC_PCCARDInitStruct->FSMC_TCLRSetupTime << 9) |
                     (FSMC_PCCARDInitStruct->FSMC_TARSetupTime << 13);
            
   
  ((FSMC_Bank4_TypeDef *) (((u32)0xA0000000) + 0x00A0))->PMEM4 = (u32)FSMC_PCCARDInitStruct->FSMC_CommonSpaceTimingStruct->FSMC_SetupTime |
                      (FSMC_PCCARDInitStruct->FSMC_CommonSpaceTimingStruct->FSMC_WaitSetupTime << 8) |
                      (FSMC_PCCARDInitStruct->FSMC_CommonSpaceTimingStruct->FSMC_HoldSetupTime << 16)|
                      (FSMC_PCCARDInitStruct->FSMC_CommonSpaceTimingStruct->FSMC_HiZSetupTime << 24); 
            
   
  ((FSMC_Bank4_TypeDef *) (((u32)0xA0000000) + 0x00A0))->PATT4 = (u32)FSMC_PCCARDInitStruct->FSMC_AttributeSpaceTimingStruct->FSMC_SetupTime |
                      (FSMC_PCCARDInitStruct->FSMC_AttributeSpaceTimingStruct->FSMC_WaitSetupTime << 8) |
                      (FSMC_PCCARDInitStruct->FSMC_AttributeSpaceTimingStruct->FSMC_HoldSetupTime << 16)|
                      (FSMC_PCCARDInitStruct->FSMC_AttributeSpaceTimingStruct->FSMC_HiZSetupTime << 24);	
            
   
  ((FSMC_Bank4_TypeDef *) (((u32)0xA0000000) + 0x00A0))->PIO4 = (u32)FSMC_PCCARDInitStruct->FSMC_IOSpaceTimingStruct->FSMC_SetupTime |
                     (FSMC_PCCARDInitStruct->FSMC_IOSpaceTimingStruct->FSMC_WaitSetupTime << 8) |
                     (FSMC_PCCARDInitStruct->FSMC_IOSpaceTimingStruct->FSMC_HoldSetupTime << 16)|
                     (FSMC_PCCARDInitStruct->FSMC_IOSpaceTimingStruct->FSMC_HiZSetupTime << 24);             
}








 
void FSMC_NORSRAMStructInit(FSMC_NORSRAMInitTypeDef* FSMC_NORSRAMInitStruct)
{  
   
  FSMC_NORSRAMInitStruct->FSMC_Bank = ((u32)0x00000000);
  FSMC_NORSRAMInitStruct->FSMC_DataAddressMux = ((u32)0x00000002);
  FSMC_NORSRAMInitStruct->FSMC_MemoryType = ((u32)0x00000000);
  FSMC_NORSRAMInitStruct->FSMC_MemoryDataWidth = ((u32)0x00000000);
  FSMC_NORSRAMInitStruct->FSMC_BurstAccessMode = ((u32)0x00000000);
  FSMC_NORSRAMInitStruct->FSMC_WaitSignalPolarity = ((u32)0x00000000);
  FSMC_NORSRAMInitStruct->FSMC_WrapMode = ((u32)0x00000000);
  FSMC_NORSRAMInitStruct->FSMC_WaitSignalActive = ((u32)0x00000000);
  FSMC_NORSRAMInitStruct->FSMC_WriteOperation = ((u32)0x00001000);
  FSMC_NORSRAMInitStruct->FSMC_WaitSignal = ((u32)0x00002000);
  FSMC_NORSRAMInitStruct->FSMC_ExtendedMode = ((u32)0x00000000);
  FSMC_NORSRAMInitStruct->FSMC_AsyncWait = ((u32)0x00000000);
  FSMC_NORSRAMInitStruct->FSMC_WriteBurst = ((u32)0x00000000);
  FSMC_NORSRAMInitStruct->FSMC_ReadWriteTimingStruct->FSMC_AddressSetupTime = 0xF;
  FSMC_NORSRAMInitStruct->FSMC_ReadWriteTimingStruct->FSMC_AddressHoldTime = 0xF;
  FSMC_NORSRAMInitStruct->FSMC_ReadWriteTimingStruct->FSMC_DataSetupTime = 0xFF;
  FSMC_NORSRAMInitStruct->FSMC_ReadWriteTimingStruct->FSMC_BusTurnAroundDuration = 0xF;
  FSMC_NORSRAMInitStruct->FSMC_ReadWriteTimingStruct->FSMC_CLKDivision = 0xF;
  FSMC_NORSRAMInitStruct->FSMC_ReadWriteTimingStruct->FSMC_DataLatency = 0xF;
  FSMC_NORSRAMInitStruct->FSMC_ReadWriteTimingStruct->FSMC_AccessMode = ((u32)0x00000000); 
  FSMC_NORSRAMInitStruct->FSMC_WriteTimingStruct->FSMC_AddressSetupTime = 0xF;
  FSMC_NORSRAMInitStruct->FSMC_WriteTimingStruct->FSMC_AddressHoldTime = 0xF;
  FSMC_NORSRAMInitStruct->FSMC_WriteTimingStruct->FSMC_DataSetupTime = 0xFF;
  FSMC_NORSRAMInitStruct->FSMC_WriteTimingStruct->FSMC_BusTurnAroundDuration = 0xF;
  FSMC_NORSRAMInitStruct->FSMC_WriteTimingStruct->FSMC_CLKDivision = 0xF;
  FSMC_NORSRAMInitStruct->FSMC_WriteTimingStruct->FSMC_DataLatency = 0xF;
  FSMC_NORSRAMInitStruct->FSMC_WriteTimingStruct->FSMC_AccessMode = ((u32)0x00000000);
}








 
void FSMC_NANDStructInit(FSMC_NANDInitTypeDef* FSMC_NANDInitStruct)
{ 
   
  FSMC_NANDInitStruct->FSMC_Bank = ((u32)0x00000010);
  FSMC_NANDInitStruct->FSMC_Waitfeature = ((u32)0x00000000);
  FSMC_NANDInitStruct->FSMC_MemoryDataWidth = ((u32)0x00000000);
  FSMC_NANDInitStruct->FSMC_ECC = ((u32)0x00000000);
  FSMC_NANDInitStruct->FSMC_ECCPageSize = ((u32)0x00000000);
  FSMC_NANDInitStruct->FSMC_AddressLowMapping = ((u32)0x00000000);
  FSMC_NANDInitStruct->FSMC_TCLRSetupTime = 0x0;
  FSMC_NANDInitStruct->FSMC_TARSetupTime = 0x0;
  FSMC_NANDInitStruct->FSMC_CommonSpaceTimingStruct->FSMC_SetupTime = 0xFC;
  FSMC_NANDInitStruct->FSMC_CommonSpaceTimingStruct->FSMC_WaitSetupTime = 0xFC;
  FSMC_NANDInitStruct->FSMC_CommonSpaceTimingStruct->FSMC_HoldSetupTime = 0xFC;
  FSMC_NANDInitStruct->FSMC_CommonSpaceTimingStruct->FSMC_HiZSetupTime = 0xFC;
  FSMC_NANDInitStruct->FSMC_AttributeSpaceTimingStruct->FSMC_SetupTime = 0xFC;
  FSMC_NANDInitStruct->FSMC_AttributeSpaceTimingStruct->FSMC_WaitSetupTime = 0xFC;
  FSMC_NANDInitStruct->FSMC_AttributeSpaceTimingStruct->FSMC_HoldSetupTime = 0xFC;
  FSMC_NANDInitStruct->FSMC_AttributeSpaceTimingStruct->FSMC_HiZSetupTime = 0xFC;	  
}








 
void FSMC_PCCARDStructInit(FSMC_PCCARDInitTypeDef* FSMC_PCCARDInitStruct)
{
   
  FSMC_PCCARDInitStruct->FSMC_Waitfeature = ((u32)0x00000000);
  FSMC_PCCARDInitStruct->FSMC_AddressLowMapping = ((u32)0x00000000);
  FSMC_PCCARDInitStruct->FSMC_TCLRSetupTime = 0x0;
  FSMC_PCCARDInitStruct->FSMC_TARSetupTime = 0x0;
  FSMC_PCCARDInitStruct->FSMC_CommonSpaceTimingStruct->FSMC_SetupTime = 0xFC;
  FSMC_PCCARDInitStruct->FSMC_CommonSpaceTimingStruct->FSMC_WaitSetupTime = 0xFC;
  FSMC_PCCARDInitStruct->FSMC_CommonSpaceTimingStruct->FSMC_HoldSetupTime = 0xFC;
  FSMC_PCCARDInitStruct->FSMC_CommonSpaceTimingStruct->FSMC_HiZSetupTime = 0xFC;
  FSMC_PCCARDInitStruct->FSMC_AttributeSpaceTimingStruct->FSMC_SetupTime = 0xFC;
  FSMC_PCCARDInitStruct->FSMC_AttributeSpaceTimingStruct->FSMC_WaitSetupTime = 0xFC;
  FSMC_PCCARDInitStruct->FSMC_AttributeSpaceTimingStruct->FSMC_HoldSetupTime = 0xFC;
  FSMC_PCCARDInitStruct->FSMC_AttributeSpaceTimingStruct->FSMC_HiZSetupTime = 0xFC;	
  FSMC_PCCARDInitStruct->FSMC_IOSpaceTimingStruct->FSMC_SetupTime = 0xFC;
  FSMC_PCCARDInitStruct->FSMC_IOSpaceTimingStruct->FSMC_WaitSetupTime = 0xFC;
  FSMC_PCCARDInitStruct->FSMC_IOSpaceTimingStruct->FSMC_HoldSetupTime = 0xFC;
  FSMC_PCCARDInitStruct->FSMC_IOSpaceTimingStruct->FSMC_HiZSetupTime = 0xFC;
}














 
void FSMC_NORSRAMCmd(u32 FSMC_Bank, FunctionalState NewState)
{
  ((void)0);
  ((void)0);
  
  if (NewState != DISABLE)
  {
     
    ((FSMC_Bank1_TypeDef *) (((u32)0xA0000000) + 0x0000))->BTCR[FSMC_Bank] |= ((u32)0x00000001);
  }
  else
  {
     
    ((FSMC_Bank1_TypeDef *) (((u32)0xA0000000) + 0x0000))->BTCR[FSMC_Bank] &= ((u32)0x000FFFFE);
  }
}












 
void FSMC_NANDCmd(u32 FSMC_Bank, FunctionalState NewState)
{
  ((void)0);
  ((void)0);
  
  if (NewState != DISABLE)
  {
     
    if(FSMC_Bank == ((u32)0x00000010))
    {
      ((FSMC_Bank2_TypeDef *) (((u32)0xA0000000) + 0x0060))->PCR2 |= ((u32)0x00000004);
    }
    else
    {
      ((FSMC_Bank3_TypeDef *) (((u32)0xA0000000) + 0x0080))->PCR3 |= ((u32)0x00000004);
    }
  }
  else
  {
     
    if(FSMC_Bank == ((u32)0x00000010))
    {
      ((FSMC_Bank2_TypeDef *) (((u32)0xA0000000) + 0x0060))->PCR2 &= ((u32)0x000FFFFB);
    }
    else
    {
      ((FSMC_Bank3_TypeDef *) (((u32)0xA0000000) + 0x0080))->PCR3 &= ((u32)0x000FFFFB);
    }
  }
}








 
void FSMC_PCCARDCmd(FunctionalState NewState)
{
  ((void)0);
  
  if (NewState != DISABLE)
  {
     
    ((FSMC_Bank4_TypeDef *) (((u32)0xA0000000) + 0x00A0))->PCR4 |= ((u32)0x00000004);
  }
  else
  {
     
    ((FSMC_Bank4_TypeDef *) (((u32)0xA0000000) + 0x00A0))->PCR4 &= ((u32)0x000FFFFB);
  }
}












 
void FSMC_NANDECCCmd(u32 FSMC_Bank, FunctionalState NewState)
{
  ((void)0);
  ((void)0);
  
  if (NewState != DISABLE)
  {
     
    if(FSMC_Bank == ((u32)0x00000010))
    {
      ((FSMC_Bank2_TypeDef *) (((u32)0xA0000000) + 0x0060))->PCR2 |= ((u32)0x00000040);
    }
    else
    {
      ((FSMC_Bank3_TypeDef *) (((u32)0xA0000000) + 0x0080))->PCR3 |= ((u32)0x00000040);
    }
  }
  else
  {
     
    if(FSMC_Bank == ((u32)0x00000010))
    {
      ((FSMC_Bank2_TypeDef *) (((u32)0xA0000000) + 0x0060))->PCR2 &= ((u32)0x000FFFBF);
    }
    else
    {
      ((FSMC_Bank3_TypeDef *) (((u32)0xA0000000) + 0x0080))->PCR3 &= ((u32)0x000FFFBF);
    }
  }
}










 
u32 FSMC_GetECC(u32 FSMC_Bank)
{
  u32 eccval = 0x00000000;
  
  if(FSMC_Bank == ((u32)0x00000010))
  {
     
    eccval = ((FSMC_Bank2_TypeDef *) (((u32)0xA0000000) + 0x0060))->ECCR2;
  }
  else
  {
     
    eccval = ((FSMC_Bank3_TypeDef *) (((u32)0xA0000000) + 0x0080))->ECCR3;
  }
   
  return(eccval);
}



















 
void FSMC_ITConfig(u32 FSMC_Bank, u32 FSMC_IT, FunctionalState NewState)
{
  ((void)0);
  ((void)0);	
  ((void)0);
  
  if (NewState != DISABLE)
  {
     
    if(FSMC_Bank == ((u32)0x00000010))
    {
      ((FSMC_Bank2_TypeDef *) (((u32)0xA0000000) + 0x0060))->SR2 |= FSMC_IT;
    }
     
    else if (FSMC_Bank == ((u32)0x00000100))
    {
      ((FSMC_Bank3_TypeDef *) (((u32)0xA0000000) + 0x0080))->SR3 |= FSMC_IT;
    }
     
    else
    {
      ((FSMC_Bank4_TypeDef *) (((u32)0xA0000000) + 0x00A0))->SR4 |= FSMC_IT;    
    }
  }
  else
  {
     
    if(FSMC_Bank == ((u32)0x00000010))
    {
      
      ((FSMC_Bank2_TypeDef *) (((u32)0xA0000000) + 0x0060))->SR2 &= (u32)~FSMC_IT;
    }
     
    else if (FSMC_Bank == ((u32)0x00000100))
    {
      ((FSMC_Bank3_TypeDef *) (((u32)0xA0000000) + 0x0080))->SR3 &= (u32)~FSMC_IT;
    }
     
    else
    {
      ((FSMC_Bank4_TypeDef *) (((u32)0xA0000000) + 0x00A0))->SR4 &= (u32)~FSMC_IT;    
    }
  }
}
                  
















                    
FlagStatus FSMC_GetFlagStatus(u32 FSMC_Bank, u32 FSMC_FLAG)
{
  FlagStatus bitstatus = RESET;
  u32 tmpsr = 0x00000000;
  
   
  ((void)0);
  ((void)0);
  
  if(FSMC_Bank == ((u32)0x00000010))
  {
    tmpsr = ((FSMC_Bank2_TypeDef *) (((u32)0xA0000000) + 0x0060))->SR2;
  }  
  else if(FSMC_Bank == ((u32)0x00000100))
  {
    tmpsr = ((FSMC_Bank3_TypeDef *) (((u32)0xA0000000) + 0x0080))->SR3;
  }
   
  else
  {
    tmpsr = ((FSMC_Bank4_TypeDef *) (((u32)0xA0000000) + 0x00A0))->SR4;
  } 
  
   
  if ((tmpsr & FSMC_FLAG) != (u16)RESET )
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
   
  return bitstatus;
}
















                    
void FSMC_ClearFlag(u32 FSMC_Bank, u32 FSMC_FLAG)
{
  
  ((void)0);
  ((void)0) ;
    
  if(FSMC_Bank == ((u32)0x00000010))
  {
    ((FSMC_Bank2_TypeDef *) (((u32)0xA0000000) + 0x0060))->SR2 &= ~FSMC_FLAG; 
  }  
  else if(FSMC_Bank == ((u32)0x00000100))
  {
    ((FSMC_Bank3_TypeDef *) (((u32)0xA0000000) + 0x0080))->SR3 &= ~FSMC_FLAG;
  }
   
  else
  {
    ((FSMC_Bank4_TypeDef *) (((u32)0xA0000000) + 0x00A0))->SR4 &= ~FSMC_FLAG;
  }
}
















  
ITStatus FSMC_GetITStatus(u32 FSMC_Bank, u32 FSMC_IT)
{
  ITStatus bitstatus = RESET;
  u32 tmpsr = 0x0, itstatus = 0x0, itenable = 0x0; 
  
   
  ((void)0);
  ((void)0);
  
  if(FSMC_Bank == ((u32)0x00000010))
  {
    tmpsr = ((FSMC_Bank2_TypeDef *) (((u32)0xA0000000) + 0x0060))->SR2;
  }  
  else if(FSMC_Bank == ((u32)0x00000100))
  {
    tmpsr = ((FSMC_Bank3_TypeDef *) (((u32)0xA0000000) + 0x0080))->SR3;
  }
   
  else
  {
    tmpsr = ((FSMC_Bank4_TypeDef *) (((u32)0xA0000000) + 0x00A0))->SR4;
  } 
  
  itstatus = tmpsr & FSMC_IT;
  
  itenable = tmpsr & (FSMC_IT >> 3);

  if ((itstatus != (u32)RESET)  && (itenable != (u32)RESET))
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  return bitstatus; 
}
















 
void FSMC_ClearITPendingBit(u32 FSMC_Bank, u32 FSMC_IT)
{
   
  ((void)0);
  ((void)0);
    
  if(FSMC_Bank == ((u32)0x00000010))
  {
    ((FSMC_Bank2_TypeDef *) (((u32)0xA0000000) + 0x0060))->SR2 &= ~(FSMC_IT >> 3); 
  }  
  else if(FSMC_Bank == ((u32)0x00000100))
  {
    ((FSMC_Bank3_TypeDef *) (((u32)0xA0000000) + 0x0080))->SR3 &= ~(FSMC_IT >> 3);
  }
   
  else
  {
    ((FSMC_Bank4_TypeDef *) (((u32)0xA0000000) + 0x00A0))->SR4 &= ~(FSMC_IT >> 3);
  }
}

 
