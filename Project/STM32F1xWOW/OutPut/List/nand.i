#line 1 "..\\..\\Driver\\Components\\SCR\\NAND.C"







 
#line 1 "..\\..\\Driver\\Components\\INC\\NAND.H"







 






void NAND_Initialize(void);


 
#line 10 "..\\..\\Driver\\Components\\SCR\\NAND.C"

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



 
#line 12 "..\\..\\Driver\\Components\\SCR\\NAND.C"





#line 1 "..\\..\\Library\\C\\string.h"
 
 
 
 




 








 












#line 38 "..\\..\\Library\\C\\string.h"


  



    typedef unsigned int size_t;    
#line 54 "..\\..\\Library\\C\\string.h"




extern __declspec(__nothrow) void *memcpy(void * __restrict  ,
                    const void * __restrict  , size_t  ) __attribute__((__nonnull__(1,2)));
   




 
extern __declspec(__nothrow) void *memmove(void *  ,
                    const void *  , size_t  ) __attribute__((__nonnull__(1,2)));
   







 
extern __declspec(__nothrow) char *strcpy(char * __restrict  , const char * __restrict  ) __attribute__((__nonnull__(1,2)));
   




 
extern __declspec(__nothrow) char *strncpy(char * __restrict  , const char * __restrict  , size_t  ) __attribute__((__nonnull__(1,2)));
   





 

extern __declspec(__nothrow) char *strcat(char * __restrict  , const char * __restrict  ) __attribute__((__nonnull__(1,2)));
   




 
extern __declspec(__nothrow) char *strncat(char * __restrict  , const char * __restrict  , size_t  ) __attribute__((__nonnull__(1,2)));
   






 






 

extern __declspec(__nothrow) int memcmp(const void *  , const void *  , size_t  ) __attribute__((__nonnull__(1,2)));
   





 
extern __declspec(__nothrow) int strcmp(const char *  , const char *  ) __attribute__((__nonnull__(1,2)));
   




 
extern __declspec(__nothrow) int strncmp(const char *  , const char *  , size_t  ) __attribute__((__nonnull__(1,2)));
   






 
extern __declspec(__nothrow) int strcasecmp(const char *  , const char *  ) __attribute__((__nonnull__(1,2)));
   





 
extern __declspec(__nothrow) int strncasecmp(const char *  , const char *  , size_t  ) __attribute__((__nonnull__(1,2)));
   






 
extern __declspec(__nothrow) int strcoll(const char *  , const char *  ) __attribute__((__nonnull__(1,2)));
   







 

extern __declspec(__nothrow) size_t strxfrm(char * __restrict  , const char * __restrict  , size_t  ) __attribute__((__nonnull__(2)));
   













 


#line 193 "..\\..\\Library\\C\\string.h"
extern __declspec(__nothrow) void *memchr(const void *  , int  , size_t  ) __attribute__((__nonnull__(1)));

   





 

#line 209 "..\\..\\Library\\C\\string.h"
extern __declspec(__nothrow) char *strchr(const char *  , int  ) __attribute__((__nonnull__(1)));

   




 

extern __declspec(__nothrow) size_t strcspn(const char *  , const char *  ) __attribute__((__nonnull__(1,2)));
   




 

#line 232 "..\\..\\Library\\C\\string.h"
extern __declspec(__nothrow) char *strpbrk(const char *  , const char *  ) __attribute__((__nonnull__(1,2)));

   




 

#line 247 "..\\..\\Library\\C\\string.h"
extern __declspec(__nothrow) char *strrchr(const char *  , int  ) __attribute__((__nonnull__(1)));

   





 

extern __declspec(__nothrow) size_t strspn(const char *  , const char *  ) __attribute__((__nonnull__(1,2)));
   



 

#line 270 "..\\..\\Library\\C\\string.h"
extern __declspec(__nothrow) char *strstr(const char *  , const char *  ) __attribute__((__nonnull__(1,2)));

   





 

extern __declspec(__nothrow) char *strtok(char * __restrict  , const char * __restrict  ) __attribute__((__nonnull__(2)));
extern __declspec(__nothrow) char *_strtok_r(char *  , const char *  , char **  ) __attribute__((__nonnull__(2,3)));

extern __declspec(__nothrow) char *strtok_r(char *  , const char *  , char **  ) __attribute__((__nonnull__(2,3)));

   

































 

extern __declspec(__nothrow) void *memset(void *  , int  , size_t  ) __attribute__((__nonnull__(1)));
   



 
extern __declspec(__nothrow) char *strerror(int  );
   





 
extern __declspec(__nothrow) size_t strlen(const char *  ) __attribute__((__nonnull__(1)));
   



 

extern __declspec(__nothrow) size_t strlcpy(char *  , const char *  , size_t  ) __attribute__((__nonnull__(1,2)));
   
















 

extern __declspec(__nothrow) size_t strlcat(char *  , const char *  , size_t  ) __attribute__((__nonnull__(1,2)));
   






















 

extern __declspec(__nothrow) void _membitcpybl(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitcpybb(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitcpyhl(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitcpyhb(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitcpywl(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitcpywb(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitmovebl(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitmovebb(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitmovehl(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitmovehb(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitmovewl(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) void _membitmovewb(void *  , const void *  , int  , int  , size_t  ) __attribute__((__nonnull__(1,2)));
    














































 







#line 502 "..\\..\\Library\\C\\string.h"



 

#line 18 "..\\..\\Driver\\Components\\SCR\\NAND.C"
#line 1 "..\\..\\Library\\C\\stdlib.h"
 
 
 




 
 



 






   














  


 








#line 54 "..\\..\\Library\\C\\stdlib.h"


  



    typedef unsigned int size_t;    
#line 70 "..\\..\\Library\\C\\stdlib.h"






    



    typedef unsigned short wchar_t;  
#line 91 "..\\..\\Library\\C\\stdlib.h"

typedef struct div_t { int quot, rem; } div_t;
    
typedef struct ldiv_t { long int quot, rem; } ldiv_t;
    

typedef struct lldiv_t { long long quot, rem; } lldiv_t;
    


#line 112 "..\\..\\Library\\C\\stdlib.h"
   



 

   




 
#line 131 "..\\..\\Library\\C\\stdlib.h"
   


 
extern __declspec(__nothrow) int __aeabi_MB_CUR_MAX(void);

   




 

   




 




extern __declspec(__nothrow) double atof(const char *  ) __attribute__((__nonnull__(1)));
   



 
extern __declspec(__nothrow) int atoi(const char *  ) __attribute__((__nonnull__(1)));
   



 
extern __declspec(__nothrow) long int atol(const char *  ) __attribute__((__nonnull__(1)));
   



 

extern __declspec(__nothrow) long long atoll(const char *  ) __attribute__((__nonnull__(1)));
   



 


extern __declspec(__nothrow) double strtod(const char * __restrict  , char ** __restrict  ) __attribute__((__nonnull__(1)));
   

















 

extern __declspec(__nothrow) float strtof(const char * __restrict  , char ** __restrict  ) __attribute__((__nonnull__(1)));
extern __declspec(__nothrow) long double strtold(const char * __restrict  , char ** __restrict  ) __attribute__((__nonnull__(1)));
   

 

extern __declspec(__nothrow) long int strtol(const char * __restrict  ,
                        char ** __restrict  , int  ) __attribute__((__nonnull__(1)));
   



























 
extern __declspec(__nothrow) unsigned long int strtoul(const char * __restrict  ,
                                       char ** __restrict  , int  ) __attribute__((__nonnull__(1)));
   


























 

 
extern __declspec(__nothrow) long long strtoll(const char * __restrict  ,
                                  char ** __restrict  , int  )
                          __attribute__((__nonnull__(1)));
   




 
extern __declspec(__nothrow) unsigned long long strtoull(const char * __restrict  ,
                                            char ** __restrict  , int  )
                                   __attribute__((__nonnull__(1)));
   



 

extern __declspec(__nothrow) int rand(void);
   







 
extern __declspec(__nothrow) void srand(unsigned int  );
   






 

struct _rand_state { int __x[57]; };
extern __declspec(__nothrow) int _rand_r(struct _rand_state *);
extern __declspec(__nothrow) void _srand_r(struct _rand_state *, unsigned int);
struct _ANSI_rand_state { int __x[1]; };
extern __declspec(__nothrow) int _ANSI_rand_r(struct _ANSI_rand_state *);
extern __declspec(__nothrow) void _ANSI_srand_r(struct _ANSI_rand_state *, unsigned int);
   


 

extern __declspec(__nothrow) void *calloc(size_t  , size_t  );
   



 
extern __declspec(__nothrow) void free(void *  );
   





 
extern __declspec(__nothrow) void *malloc(size_t  );
   



 
extern __declspec(__nothrow) void *realloc(void *  , size_t  );
   













 

extern __declspec(__nothrow) int posix_memalign(void **  , size_t  , size_t  );
   









 

typedef int (*__heapprt)(void *, char const *, ...);
extern __declspec(__nothrow) void __heapstats(int (*  )(void *  ,
                                           char const *  , ...),
                        void *  ) __attribute__((__nonnull__(1)));
   










 
extern __declspec(__nothrow) int __heapvalid(int (*  )(void *  ,
                                           char const *  , ...),
                       void *  , int  ) __attribute__((__nonnull__(1)));
   














 
extern __declspec(__nothrow) __declspec(__noreturn) void abort(void);
   







 

extern __declspec(__nothrow) int atexit(void (*  )(void)) __attribute__((__nonnull__(1)));
   




 
#line 436 "..\\..\\Library\\C\\stdlib.h"


extern __declspec(__nothrow) __declspec(__noreturn) void exit(int  );
   












 

extern __declspec(__nothrow) __declspec(__noreturn) void _Exit(int  );
   







      

extern __declspec(__nothrow) char *getenv(const char *  ) __attribute__((__nonnull__(1)));
   









 

extern __declspec(__nothrow) int  system(const char *  );
   









 

extern  void *bsearch(const void *  , const void *  ,
              size_t  , size_t  ,
              int (*  )(const void *, const void *)) __attribute__((__nonnull__(1,2,5)));
   












 
#line 524 "..\\..\\Library\\C\\stdlib.h"


extern  void qsort(void *  , size_t  , size_t  ,
           int (*  )(const void *, const void *)) __attribute__((__nonnull__(1,4)));
   









 

#line 553 "..\\..\\Library\\C\\stdlib.h"

extern __declspec(__nothrow) __attribute__((const)) int abs(int  );
   



 

extern __declspec(__nothrow) __attribute__((const)) div_t div(int  , int  );
   









 
extern __declspec(__nothrow) __attribute__((const)) long int labs(long int  );
   



 




extern __declspec(__nothrow) __attribute__((const)) ldiv_t ldiv(long int  , long int  );
   











 







extern __declspec(__nothrow) __attribute__((const)) long long llabs(long long  );
   



 




extern __declspec(__nothrow) __attribute__((const)) lldiv_t lldiv(long long  , long long  );
   











 
#line 634 "..\\..\\Library\\C\\stdlib.h"




 
typedef struct __sdiv32by16 { int quot, rem; } __sdiv32by16;
typedef struct __udiv32by16 { unsigned int quot, rem; } __udiv32by16;
    
typedef struct __sdiv64by32 { int rem, quot; } __sdiv64by32;

__value_in_regs extern __declspec(__nothrow) __attribute__((const)) __sdiv32by16 __rt_sdiv32by16(
     int  ,
     short int  );
   

 
__value_in_regs extern __declspec(__nothrow) __attribute__((const)) __udiv32by16 __rt_udiv32by16(
     unsigned int  ,
     unsigned short  );
   

 
__value_in_regs extern __declspec(__nothrow) __attribute__((const)) __sdiv64by32 __rt_sdiv64by32(
     int  , unsigned int  ,
     int  );
   

 




 
extern __declspec(__nothrow) unsigned int __fp_status(unsigned int  , unsigned int  );
   







 























 
extern __declspec(__nothrow) int mblen(const char *  , size_t  );
   












 
extern __declspec(__nothrow) int mbtowc(wchar_t * __restrict  ,
                   const char * __restrict  , size_t  );
   















 
extern __declspec(__nothrow) int wctomb(char *  , wchar_t  );
   













 





 
extern __declspec(__nothrow) size_t mbstowcs(wchar_t * __restrict  ,
                      const char * __restrict  , size_t  ) __attribute__((__nonnull__(2)));
   














 
extern __declspec(__nothrow) size_t wcstombs(char * __restrict  ,
                      const wchar_t * __restrict  , size_t  ) __attribute__((__nonnull__(2)));
   














 

extern __declspec(__nothrow) void __use_realtime_heap(void);
extern __declspec(__nothrow) void __use_realtime_division(void);
extern __declspec(__nothrow) void __use_two_region_memory(void);
extern __declspec(__nothrow) void __use_no_heap(void);
extern __declspec(__nothrow) void __use_no_heap_region(void);

extern __declspec(__nothrow) char const *__C_library_version_string(void);
extern __declspec(__nothrow) int __C_library_version_number(void);











#line 892 "..\\..\\Library\\C\\stdlib.h"





 
#line 19 "..\\..\\Driver\\Components\\SCR\\NAND.C"
#line 1 "..\\..\\Library\\C\\stdarg.h"
 
 
 





 










#line 27 "..\\..\\Library\\C\\stdarg.h"








 

 
 
#line 57 "..\\..\\Library\\C\\stdarg.h"
    typedef struct __va_list { void *__ap; } va_list;

   






 


   










 


   















 




   

 


   




 



   





 







#line 138 "..\\..\\Library\\C\\stdarg.h"



#line 147 "..\\..\\Library\\C\\stdarg.h"

 

#line 20 "..\\..\\Driver\\Components\\SCR\\NAND.C"
#line 1 "..\\..\\Library\\C\\stdio.h"
 
 
 





 






 







 




  
 








#line 47 "..\\..\\Library\\C\\stdio.h"


  



    typedef unsigned int size_t;    









 
 

 



    typedef struct __va_list __va_list;






   




 




typedef struct __fpos_t_struct {
    unsigned __int64 __pos;
    



 
    struct {
        unsigned int __state1, __state2;
    } __mbstate;
} fpos_t;
   


 


   

 

typedef struct __FILE FILE;
   






 

#line 136 "..\\..\\Library\\C\\stdio.h"


extern FILE __stdin, __stdout, __stderr;
extern FILE *__aeabi_stdin, *__aeabi_stdout, *__aeabi_stderr;

#line 166 "..\\..\\Library\\C\\stdio.h"
    

    

    





     



   


 


   


 

   



 

   


 




   


 





    


 






extern __declspec(__nothrow) int remove(const char *  ) __attribute__((__nonnull__(1)));
   





 
extern __declspec(__nothrow) int rename(const char *  , const char *  ) __attribute__((__nonnull__(1,2)));
   








 
extern __declspec(__nothrow) FILE *tmpfile(void);
   




 
extern __declspec(__nothrow) char *tmpnam(char *  );
   











 

extern __declspec(__nothrow) int fclose(FILE *  ) __attribute__((__nonnull__(1)));
   







 
extern __declspec(__nothrow) int fflush(FILE *  );
   







 
extern __declspec(__nothrow) FILE *fopen(const char * __restrict  ,
                           const char * __restrict  ) __attribute__((__nonnull__(1,2)));
   








































 
extern __declspec(__nothrow) FILE *freopen(const char * __restrict  ,
                    const char * __restrict  ,
                    FILE * __restrict  ) __attribute__((__nonnull__(2,3)));
   








 
extern __declspec(__nothrow) void setbuf(FILE * __restrict  ,
                    char * __restrict  ) __attribute__((__nonnull__(1)));
   




 
extern __declspec(__nothrow) int setvbuf(FILE * __restrict  ,
                   char * __restrict  ,
                   int  , size_t  ) __attribute__((__nonnull__(1)));
   















 
#pragma __printf_args
extern __declspec(__nothrow) int fprintf(FILE * __restrict  ,
                    const char * __restrict  , ...) __attribute__((__nonnull__(1,2)));
   


















 
#pragma __printf_args
extern __declspec(__nothrow) int _fprintf(FILE * __restrict  ,
                     const char * __restrict  , ...) __attribute__((__nonnull__(1,2)));
   



 
#pragma __printf_args
extern __declspec(__nothrow) int printf(const char * __restrict  , ...) __attribute__((__nonnull__(1)));
   




 
#pragma __printf_args
extern __declspec(__nothrow) int _printf(const char * __restrict  , ...) __attribute__((__nonnull__(1)));
   



 
#pragma __printf_args
extern __declspec(__nothrow) int sprintf(char * __restrict  , const char * __restrict  , ...) __attribute__((__nonnull__(1,2)));
   






 
#pragma __printf_args
extern __declspec(__nothrow) int _sprintf(char * __restrict  , const char * __restrict  , ...) __attribute__((__nonnull__(1,2)));
   



 

#pragma __printf_args
extern __declspec(__nothrow) int __ARM_snprintf(char * __restrict  , size_t  ,
                     const char * __restrict  , ...) __attribute__((__nonnull__(3)));


#pragma __printf_args
extern __declspec(__nothrow) int snprintf(char * __restrict  , size_t  ,
                     const char * __restrict  , ...) __attribute__((__nonnull__(3)));
   















 

#pragma __printf_args
extern __declspec(__nothrow) int _snprintf(char * __restrict  , size_t  ,
                      const char * __restrict  , ...) __attribute__((__nonnull__(3)));
   



 
#pragma __scanf_args
extern __declspec(__nothrow) int fscanf(FILE * __restrict  ,
                    const char * __restrict  , ...) __attribute__((__nonnull__(1,2)));
   






























 
#pragma __scanf_args
extern __declspec(__nothrow) int _fscanf(FILE * __restrict  ,
                     const char * __restrict  , ...) __attribute__((__nonnull__(1,2)));
   



 
#pragma __scanf_args
extern __declspec(__nothrow) int scanf(const char * __restrict  , ...) __attribute__((__nonnull__(1)));
   






 
#pragma __scanf_args
extern __declspec(__nothrow) int _scanf(const char * __restrict  , ...) __attribute__((__nonnull__(1)));
   



 
#pragma __scanf_args
extern __declspec(__nothrow) int sscanf(const char * __restrict  ,
                    const char * __restrict  , ...) __attribute__((__nonnull__(1,2)));
   








 
#pragma __scanf_args
extern __declspec(__nothrow) int _sscanf(const char * __restrict  ,
                     const char * __restrict  , ...) __attribute__((__nonnull__(1,2)));
   



 

 
extern __declspec(__nothrow) int vfscanf(FILE * __restrict  , const char * __restrict  , __va_list) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) int vscanf(const char * __restrict  , __va_list) __attribute__((__nonnull__(1)));
extern __declspec(__nothrow) int vsscanf(const char * __restrict  , const char * __restrict  , __va_list) __attribute__((__nonnull__(1,2)));

extern __declspec(__nothrow) int _vfscanf(FILE * __restrict  , const char * __restrict  , __va_list) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) int _vscanf(const char * __restrict  , __va_list) __attribute__((__nonnull__(1)));
extern __declspec(__nothrow) int _vsscanf(const char * __restrict  , const char * __restrict  , __va_list) __attribute__((__nonnull__(1,2)));
extern __declspec(__nothrow) int __ARM_vsscanf(const char * __restrict  , const char * __restrict  , __va_list) __attribute__((__nonnull__(1,2)));

extern __declspec(__nothrow) int vprintf(const char * __restrict  , __va_list  ) __attribute__((__nonnull__(1)));
   





 
extern __declspec(__nothrow) int _vprintf(const char * __restrict  , __va_list  ) __attribute__((__nonnull__(1)));
   



 
extern __declspec(__nothrow) int vfprintf(FILE * __restrict  ,
                    const char * __restrict  , __va_list  ) __attribute__((__nonnull__(1,2)));
   






 
extern __declspec(__nothrow) int vsprintf(char * __restrict  ,
                     const char * __restrict  , __va_list  ) __attribute__((__nonnull__(1,2)));
   






 
extern __declspec(__nothrow) int __ARM_vsnprintf(char * __restrict  , size_t  ,
                     const char * __restrict  , __va_list  ) __attribute__((__nonnull__(3)));

extern __declspec(__nothrow) int vsnprintf(char * __restrict  , size_t  ,
                     const char * __restrict  , __va_list  ) __attribute__((__nonnull__(3)));
   







 

extern __declspec(__nothrow) int _vsprintf(char * __restrict  ,
                      const char * __restrict  , __va_list  ) __attribute__((__nonnull__(1,2)));
   



 
extern __declspec(__nothrow) int _vfprintf(FILE * __restrict  ,
                     const char * __restrict  , __va_list  ) __attribute__((__nonnull__(1,2)));
   



 
extern __declspec(__nothrow) int _vsnprintf(char * __restrict  , size_t  ,
                      const char * __restrict  , __va_list  ) __attribute__((__nonnull__(3)));
   



 

#pragma __printf_args
extern __declspec(__nothrow) int asprintf(char **  , const char * __restrict  , ...) __attribute__((__nonnull__(2)));
extern __declspec(__nothrow) int vasprintf(char **  , const char * __restrict  , __va_list  ) __attribute__((__nonnull__(2)));

#pragma __printf_args
extern __declspec(__nothrow) int __ARM_asprintf(char **  , const char * __restrict  , ...) __attribute__((__nonnull__(2)));
extern __declspec(__nothrow) int __ARM_vasprintf(char **  , const char * __restrict  , __va_list  ) __attribute__((__nonnull__(2)));
   








 

extern __declspec(__nothrow) int fgetc(FILE *  ) __attribute__((__nonnull__(1)));
   







 
extern __declspec(__nothrow) char *fgets(char * __restrict  , int  ,
                    FILE * __restrict  ) __attribute__((__nonnull__(1,3)));
   










 
extern __declspec(__nothrow) int fputc(int  , FILE *  ) __attribute__((__nonnull__(2)));
   







 
extern __declspec(__nothrow) int fputs(const char * __restrict  , FILE * __restrict  ) __attribute__((__nonnull__(1,2)));
   




 
extern __declspec(__nothrow) int getc(FILE *  ) __attribute__((__nonnull__(1)));
   







 




    extern __declspec(__nothrow) int (getchar)(void);

   





 
extern __declspec(__nothrow) char *gets(char *  ) __attribute__((__nonnull__(1)));
   









 
extern __declspec(__nothrow) int putc(int  , FILE *  ) __attribute__((__nonnull__(2)));
   





 




    extern __declspec(__nothrow) int (putchar)(int  );

   



 
extern __declspec(__nothrow) int puts(const char *  ) __attribute__((__nonnull__(1)));
   





 
extern __declspec(__nothrow) int ungetc(int  , FILE *  ) __attribute__((__nonnull__(2)));
   






















 

extern __declspec(__nothrow) size_t fread(void * __restrict  ,
                    size_t  , size_t  , FILE * __restrict  ) __attribute__((__nonnull__(1,4)));
   











 

extern __declspec(__nothrow) size_t __fread_bytes_avail(void * __restrict  ,
                    size_t  , FILE * __restrict  ) __attribute__((__nonnull__(1,3)));
   











 

extern __declspec(__nothrow) size_t fwrite(const void * __restrict  ,
                    size_t  , size_t  , FILE * __restrict  ) __attribute__((__nonnull__(1,4)));
   







 

extern __declspec(__nothrow) int fgetpos(FILE * __restrict  , fpos_t * __restrict  ) __attribute__((__nonnull__(1,2)));
   








 
extern __declspec(__nothrow) int fseek(FILE *  , long int  , int  ) __attribute__((__nonnull__(1)));
   














 
extern __declspec(__nothrow) int fsetpos(FILE * __restrict  , const fpos_t * __restrict  ) __attribute__((__nonnull__(1,2)));
   










 
extern __declspec(__nothrow) long int ftell(FILE *  ) __attribute__((__nonnull__(1)));
   











 
extern __declspec(__nothrow) void rewind(FILE *  ) __attribute__((__nonnull__(1)));
   





 

extern __declspec(__nothrow) void clearerr(FILE *  ) __attribute__((__nonnull__(1)));
   




 

extern __declspec(__nothrow) int feof(FILE *  ) __attribute__((__nonnull__(1)));
   


 
extern __declspec(__nothrow) int ferror(FILE *  ) __attribute__((__nonnull__(1)));
   


 
extern __declspec(__nothrow) void perror(const char *  );
   









 

extern __declspec(__nothrow) int _fisatty(FILE *   ) __attribute__((__nonnull__(1)));
    
 

extern __declspec(__nothrow) void __use_no_semihosting_swi(void);
extern __declspec(__nothrow) void __use_no_semihosting(void);
    





 











#line 1021 "..\\..\\Library\\C\\stdio.h"



 

#line 21 "..\\..\\Driver\\Components\\SCR\\NAND.C"
#line 1 "..\\..\\Library\\C\\stdint.h"
 
 





 









     
#line 27 "..\\..\\Library\\C\\stdint.h"
     











#line 46 "..\\..\\Library\\C\\stdint.h"





 

     

     
typedef   signed          char int8_t;
typedef   signed short     int int16_t;
typedef   signed           int int32_t;
typedef   signed       __int64 int64_t;

     
typedef unsigned          char uint8_t;
typedef unsigned short     int uint16_t;
typedef unsigned           int uint32_t;
typedef unsigned       __int64 uint64_t;

     

     
     
typedef   signed          char int_least8_t;
typedef   signed short     int int_least16_t;
typedef   signed           int int_least32_t;
typedef   signed       __int64 int_least64_t;

     
typedef unsigned          char uint_least8_t;
typedef unsigned short     int uint_least16_t;
typedef unsigned           int uint_least32_t;
typedef unsigned       __int64 uint_least64_t;

     

     
typedef   signed           int int_fast8_t;
typedef   signed           int int_fast16_t;
typedef   signed           int int_fast32_t;
typedef   signed       __int64 int_fast64_t;

     
typedef unsigned           int uint_fast8_t;
typedef unsigned           int uint_fast16_t;
typedef unsigned           int uint_fast32_t;
typedef unsigned       __int64 uint_fast64_t;

     




typedef   signed           int intptr_t;
typedef unsigned           int uintptr_t;


     
typedef   signed     long long intmax_t;
typedef unsigned     long long uintmax_t;




     

     





     





     





     

     





     





     





     

     





     





     





     

     






     






     






     

     


     


     


     

     
#line 216 "..\\..\\Library\\C\\stdint.h"

     



     






     
    
 



#line 241 "..\\..\\Library\\C\\stdint.h"

     







     










     











#line 305 "..\\..\\Library\\C\\stdint.h"






 
#line 22 "..\\..\\Driver\\Components\\SCR\\NAND.C"

















 

 

#line 44 "..\\..\\Driver\\Components\\SCR\\NAND.C"
#line 1 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_flash.h"














 

 



 
#line 23 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_flash.h"

 

 
typedef enum
{ 
  FLASH_BUSY = 1,
  FLASH_ERROR_PG,
  FLASH_ERROR_WRP,
  FLASH_COMPLETE,
  FLASH_TIMEOUT
}FLASH_Status;


 








 







 







 

 
#line 97 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_flash.h"

 
#line 132 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_flash.h"






 





 





 





 





 





 






								 
 
 
 
void FLASH_SetLatency(u32 FLASH_Latency);										
void FLASH_HalfCycleAccessCmd(u32 FLASH_HalfCycleAccess);		
void FLASH_PrefetchBufferCmd(u32 FLASH_PrefetchBuffer);			


void FLASH_Unlock(void);		
void FLASH_Lock(void);			
FLASH_Status FLASH_ErasePage(u32 Page_Address);		
FLASH_Status FLASH_EraseAllPages(void);						
FLASH_Status FLASH_EraseOptionBytes(void);				
FLASH_Status FLASH_ProgramWord(u32 Address, u32 Data);					
FLASH_Status FLASH_ProgramHalfWord(u32 Address, u16 Data);			
FLASH_Status FLASH_ProgramOptionByteData(u32 Address, u8 Data);	
FLASH_Status FLASH_EnableWriteProtection(u32 FLASH_Pages);			
FLASH_Status FLASH_ReadOutProtection(FunctionalState NewState);	
FLASH_Status FLASH_UserOptionByteConfig(u16 OB_IWDG, u16 OB_STOP, u16 OB_STDBY);	
u32 FLASH_GetUserOptionByte(void);									
u32 FLASH_GetWriteProtectionOptionByte(void);				
FlagStatus FLASH_GetReadOutProtectionStatus(void);	
FlagStatus FLASH_GetPrefetchBufferStatus(void);			
void FLASH_ITConfig(u16 FLASH_IT, FunctionalState NewState);	
FlagStatus FLASH_GetFlagStatus(u16 FLASH_FLAG);			
void FLASH_ClearFlag(u16 FLASH_FLAG);								
FLASH_Status FLASH_GetStatus(void);									
FLASH_Status FLASH_WaitForLastOperation(u32 Timeout);	




 
#line 45 "..\\..\\Driver\\Components\\SCR\\NAND.C"
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



 
#line 46 "..\\..\\Driver\\Components\\SCR\\NAND.C"
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



 
#line 47 "..\\..\\Driver\\Components\\SCR\\NAND.C"
#line 57 "..\\..\\Driver\\Components\\SCR\\NAND.C"
uint8_t tabel[2111];
void mysysinit(void);
void my_USART_init(void);
void my_send_byte(unsigned char send_date); 
GPIO_InitTypeDef GPIO_InitStructure;
void READ_NAND_ID(void);
void delay_1us(uint32_t);
void my_NAND_INIT(void ); 
void wait_NAND_readay(void);
void write_nand_addrrs(uint8_t a);
void write_nand_commond(uint8_t comm);
void write_nand_date(uint8_t da);
uint8_t read_nand_date(void);
void write_NAND_PAGE(void);
void read_NAND_PAGE(void); 
void erase_NAND_BLOK(void);






 
void NAND_Initialize(void)
{

  RCC_APB2PeriphClockCmd(((u32)0x00000020), ENABLE);
  RCC_APB2PeriphClockCmd(((u32)0x00000100), ENABLE);
  RCC_APB2PeriphClockCmd(((u32)0x00000008), ENABLE);
  RCC_APB2PeriphClockCmd(((u32)0x00000040), ENABLE);
  RCC_APB2PeriphClockCmd(((u32)0x00000001), ENABLE);
  RCC_APB2PeriphClockCmd(((u32)0x00004000),ENABLE);
   




   
  GPIO_InitStructure.GPIO_Pin = ((u16)0x0040);
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), &GPIO_InitStructure);
   
  GPIO_InitStructure.GPIO_Pin = ((u16)0x0020) | ((u16)0x0040)| ((u16)0x0080)| ((u16)0x4000)| ((u16)0x8000);
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), &GPIO_InitStructure);

       

  wait_NAND_readay();

  my_send_byte(0);
  my_send_byte(1);
  my_send_byte(2);
  my_send_byte(3);
  
  READ_NAND_ID(); 
  erase_NAND_BLOK();
  write_NAND_PAGE();

  read_NAND_PAGE();
  while(1);


}
 
void erase_NAND_BLOK()
{ uint8_t e,m;



 
  GPIO_InitStructure.GPIO_Pin = ((u16)0x0001) | ((u16)0x0002)| ((u16)0x0004)| ((u16)0x0008)| ((u16)0x0010)|((u16)0x0020) | ((u16)0x0040)| ((u16)0x0080);
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1800)), &GPIO_InitStructure);
  
  GPIO_SetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x0020));
  GPIO_SetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x0010));
  GPIO_ResetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x1000));  
  GPIO_ResetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x0800));

  GPIO_ResetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x2000)), ((u16)0x0400));
  GPIO_SetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x0800));
  GPIO_ResetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x1000));
  GPIO_ResetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x0020));
  GPIO_Write(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1800)), 0x60); 
  GPIO_SetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x0020));
  GPIO_ResetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x0800));
  GPIO_SetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x1000));
  GPIO_ResetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x0020));
  GPIO_Write(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1800)), 0x00); 
  GPIO_SetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x0020));
  GPIO_ResetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x0020));
  GPIO_Write(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1800)), 0x00); 
  GPIO_SetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x0020));
  GPIO_ResetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x1000));
  GPIO_SetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x0800));
  GPIO_ResetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x0020));
  GPIO_Write(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1800)), 0xd0); 
  GPIO_SetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x0020));
  GPIO_ResetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x0800));
  for(m=5;m;m--);
  wait_NAND_readay();
  delay_1us(3000); 
  GPIO_SetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x0800));
  GPIO_ResetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x0020));
  GPIO_Write(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1800)), 0x70); 
  GPIO_SetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x0020));
  GPIO_ResetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x0800));
  ((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1800))->CRL=0x88888888; 
  GPIO_ResetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x0010));
  e=(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1800))->IDR);
  GPIO_SetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x0010));
  my_send_byte(e);  

}
 
void read_NAND_PAGE()
{
  uint32_t n;
  uint8_t sd;

   
  GPIO_InitStructure.GPIO_Pin = ((u16)0x0001) | ((u16)0x0002)| ((u16)0x0004)| ((u16)0x0008)| ((u16)0x0010)|((u16)0x0020) | ((u16)0x0040)| ((u16)0x0080);
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1800)), &GPIO_InitStructure);
  GPIO_SetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x0020));
  GPIO_SetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x0010));
  GPIO_ResetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x1000));
  GPIO_ResetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x0800));

  GPIO_ResetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x2000)), ((u16)0x0400));
  GPIO_SetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x0800));
  GPIO_ResetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x1000));
  GPIO_SetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x0010));
  GPIO_ResetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x0020));
  GPIO_Write(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1800)), 0x00); 
  GPIO_SetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x0020));
  GPIO_ResetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x0800));
  GPIO_SetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x1000));
  GPIO_SetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x0010));
  GPIO_ResetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x0020));
  GPIO_Write(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1800)), 0x00); 
  GPIO_SetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x0020));
  GPIO_ResetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x0020));
  GPIO_Write(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1800)), 0x00);
  GPIO_SetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x0020));
  GPIO_ResetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x0020));
  GPIO_Write(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1800)), 0x00); 
  GPIO_SetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x0020));
  GPIO_ResetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x0020));
  GPIO_Write(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1800)), 0x00);
  GPIO_SetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x0020));

  GPIO_ResetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x1000));
  GPIO_SetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x0800));
  GPIO_SetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x0010));
  GPIO_ResetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x0020));
  GPIO_Write(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1800)), 0x30); 
  GPIO_SetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x0020));
  GPIO_ResetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x0800));
  ((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1800))->CRL=0x88888888; 
  for(n=30;n;n--);
    delay_1us(20); 
  wait_NAND_readay();
  for(n=2112;n;n--)
  {
    GPIO_ResetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x0010));
    sd=(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1800))->IDR);
    GPIO_SetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x0010));
    my_send_byte(sd);
  }

  GPIO_SetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x2000)), ((u16)0x0400));
  GPIO_SetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x0020));
  GPIO_SetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x0010));
  GPIO_ResetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x1000));
  GPIO_ResetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x0800));
}


 
void write_NAND_PAGE()
{
  uint8_t send_date=0;
  uint32_t numb;
    
  GPIO_InitStructure.GPIO_Pin = ((u16)0x0001) | ((u16)0x0002)| ((u16)0x0004)| ((u16)0x0008)| ((u16)0x0010)|((u16)0x0020) | ((u16)0x0040)| ((u16)0x0080);
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1800)), &GPIO_InitStructure);
  GPIO_SetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x0020));
  GPIO_SetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x0010));
  GPIO_ResetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x1000));
  GPIO_ResetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x0800));

  GPIO_ResetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x2000)), ((u16)0x0400));
  GPIO_SetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x0800));
  GPIO_ResetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x1000));
  GPIO_SetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x0020));
  GPIO_SetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x0010));

  GPIO_ResetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x0020));
  GPIO_Write(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1800)), 0x80); 
  GPIO_SetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x0020));
  GPIO_ResetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x0800));


  GPIO_SetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x1000));
  GPIO_ResetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x0020));
  GPIO_Write(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1800)), 0x00); 
  GPIO_SetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x0020));
  GPIO_ResetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x0020));
  GPIO_Write(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1800)), 0x00); 
  GPIO_SetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x0020));
  GPIO_ResetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x0020));
  GPIO_Write(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1800)), 0x00); 
  GPIO_SetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x0020));
  GPIO_ResetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x0020));
  GPIO_Write(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1800)), 0x00); 
  GPIO_SetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x0020));
  GPIO_ResetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x1000));

  for(numb=5;numb;numb--);
  for(numb=2112;numb;numb--)
  {
     GPIO_ResetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x0020));
     GPIO_Write(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1800)), 0x89);  
     GPIO_SetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x0020));

  }
  GPIO_SetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x0800));
  GPIO_ResetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x0020));
  GPIO_Write(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1800)), 0x10);
  GPIO_SetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x0020));
  for(numb=3;numb;numb--);
  wait_NAND_readay();
  delay_1us(500);
  GPIO_ResetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x0020));
  GPIO_Write(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1800)), 0x70);
  GPIO_SetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x0020));
  ((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1800))->CRL=0x88888888;
  GPIO_SetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x0020));
  GPIO_SetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x0010));
  GPIO_ResetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x0010));
  send_date=(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1800))->IDR);
  GPIO_SetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x2000)), ((u16)0x0400));
  my_send_byte(send_date);
  GPIO_SetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x0020));
  GPIO_SetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x0010));
  GPIO_ResetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x1000));
  GPIO_ResetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x0800));

}

 
void wait_NAND_readay()
{
  uint8_t wait=0;
  
  do
  {
    wait=GPIO_ReadOutputDataBit(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x0040));
  }
  while(0x00==wait);
}
 
void READ_NAND_ID()
{

  uint8_t a=0,b=0,c=0,d=0;

  
    
  GPIO_InitStructure.GPIO_Pin = ((u16)0x0020) | ((u16)0x0040)| ((u16)0x0080)| ((u16)0x4000)| ((u16)0x8000);
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), &GPIO_InitStructure);
 
  GPIO_InitStructure.GPIO_Pin = ((u16)0x0001) | ((u16)0x0002)| ((u16)0x0004)| ((u16)0x0008)| ((u16)0x0010)|((u16)0x0020) | ((u16)0x0040)| ((u16)0x0080);
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1800)), &GPIO_InitStructure);


  GPIO_ResetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x2000)), ((u16)0x0400));


  GPIO_SetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x0800));
  GPIO_ResetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x0020));
  GPIO_ResetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x1000));
  GPIO_SetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x0010));
  GPIO_Write(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1800)), 0x90); 
  GPIO_SetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x0020));

  GPIO_ResetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x0800));
  GPIO_SetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x1000));
  GPIO_ResetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x0020));
  GPIO_Write(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1800)), 0x00); 
  GPIO_SetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x0020));




   
  GPIO_InitStructure.GPIO_Pin = ((u16)0x0001) | ((u16)0x0002)| ((u16)0x0004)| ((u16)0x0008)| ((u16)0x0010)|((u16)0x0080) | ((u16)0x0040)| ((u16)0x0080);
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1800)), &GPIO_InitStructure);

  GPIO_ResetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x1000)); 
       
     
  GPIO_ResetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x0010));

  a=(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1800))->IDR);
  GPIO_SetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x0010));

  GPIO_ResetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x0010));
  b=(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1800))->IDR);
  GPIO_SetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x0010));

  GPIO_ResetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x0010));
  c=(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1800))->IDR);
  GPIO_SetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x0010));

  GPIO_ResetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x0010));
  d=(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1800))->IDR);
  GPIO_SetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x0010));


  GPIO_SetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x2000)), ((u16)0x0400));

  my_send_byte(a);
  my_send_byte(b);
  my_send_byte(c);
  my_send_byte(d);
}
 
void write_nand_commond(uint8_t comm)
{
  GPIO_ResetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x2000)), ((u16)0x0400));
  GPIO_SetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x0010));
  GPIO_SetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x0800));
  GPIO_ResetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x1000));
  GPIO_ResetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x0020));
  GPIO_Write(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1800)), comm); 
  GPIO_SetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x0020));
  GPIO_ResetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x0800));
  GPIO_SetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x2000)), ((u16)0x0400));

}
 
void write_nand_addrrs(uint8_t a)
{
  GPIO_ResetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x2000)), ((u16)0x0400));
  GPIO_SetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x0010));
  GPIO_ResetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x0800));
  GPIO_SetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x1000));
  GPIO_ResetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x0020));;;
  GPIO_Write(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1800)), a); 
  GPIO_SetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x0020));
  GPIO_ResetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x1000));
  GPIO_SetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x2000)), ((u16)0x0400));


}

void write_nand_date(uint8_t da)
{ 
  GPIO_ResetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x2000)), ((u16)0x0400));
  GPIO_ResetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x1000));
  GPIO_ResetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x0800));
  GPIO_SetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x0010));
  GPIO_ResetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x0020));
  ((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1800))->ODR=da;
  GPIO_SetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x0020));
  GPIO_SetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x2000)), ((u16)0x0400));
}
 
uint8_t read_nand_date()
{
  uint8_t a;
  GPIO_ResetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x2000)), ((u16)0x0400));
  GPIO_SetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x0020));
  GPIO_SetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x0010));
  GPIO_ResetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x0010));;;; 
  a=(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1800))->IDR);
  GPIO_SetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x0010));
  GPIO_SetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x2000)), ((u16)0x0400));
  return a;
}





 
void delay_1us(uint32_t time)
{   
  uint32_t b,c;
  for(c=time;c;c--) 
  {     
    for(b=8;b;b--); 
  }
}




  
void my_send_byte(unsigned char send_date )
{

  while( (((USART_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x3800))->SR&0x00000080)!=0x80);
   ((USART_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x3800))->DR=send_date; 


}



 
void my_USART_init()
{

 
((NVIC_TypeDef *) (((u32)0xE000E000) + 0x0100))->IPR[37]=5;
 
((NVIC_TypeDef *) (((u32)0xE000E000) + 0x0100))->ISER[1]=0x00000020;    
 
            ((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0800))->CRH=0x000008b0; 
  

 
((USART_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x3800))->CR1=0x2000;



 
((USART_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x3800))->CR2=0;





 
((USART_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x3800))->CR3=0;





















 
((USART_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x3800))->BRR=0x0ea6;





 
((USART_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x3800))->CR1=0x202c;


}


void mysysinit()
{
ErrorStatus HSEStartUpStatus;
RCC_DeInit();

 
RCC_HSEConfig(((u32)0x00010000));
 
HSEStartUpStatus = RCC_WaitForHSEStartUp();
if(HSEStartUpStatus == SUCCESS)
{
 
 
FLASH_PrefetchBufferCmd(((u32)0x00000010));
 
  FLASH_SetLatency(((u32)0x00000002));  
 
RCC_PLLConfig(((u32)0x00010000), ((u32)0x001C0000));

 
RCC_HCLKConfig(((u32)0x00000000));
 
RCC_PCLK1Config(((u32)0x00000400));
 
RCC_PCLK2Config(((u32)0x00000000));
 
RCC_SYSCLKConfig(((u32)0x00000002));
 
RCC_ITConfig(((u8)0x10), DISABLE);
 
RCC_ITConfig(((u8)0x08),DISABLE);
 
RCC_ITConfig(((u8)0x04), DISABLE); 
 
RCC_ITConfig(((u8)0x02), DISABLE); 
 
RCC_ITConfig(((u8)0x01), DISABLE); 

 
RCC_USBCLKConfig(((u8)0x00));
 
RCC_ADCCLKConfig(((u32)0x00000000));
 
RCC_LSEConfig(((u8)0x00));

 
RCC_RTCCLKCmd(DISABLE);
 
RCC_ClockSecuritySystemCmd(DISABLE);
 
RCC_PLLCmd(ENABLE);







 
}
else
{
 
}
}
 


