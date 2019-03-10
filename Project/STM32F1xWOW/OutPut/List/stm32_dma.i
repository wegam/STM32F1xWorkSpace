#line 1 "..\\..\\Driver\\WOW\\SCR\\STM32_DMA.C"













 


#line 1 "..\\..\\Driver\\WOW\\INC\\STM32_DMA.H"













 






#line 1 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_dma.h"














 



 
 



 
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

 
 
 



 
#line 26 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_dma.h"

 
 
typedef struct
{
  u32 DMA_PeripheralBaseAddr;			
  u32 DMA_MemoryBaseAddr;					
  u32 DMA_DIR;										
  u32 DMA_BufferSize;							
  u32 DMA_PeripheralInc;					
  u32 DMA_MemoryInc;							
  u32 DMA_PeripheralDataSize;			
  u32 DMA_MemoryDataSize;					
  u32 DMA_Mode;										
  u32 DMA_Priority;								
  u32 DMA_M2M;										
}DMA_InitTypeDef;

 
#line 57 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_dma.h"

 






 






 






 








 








 





 










 





 






 
#line 156 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_dma.h"
 
#line 177 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_dma.h"

#line 203 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_dma.h"

 
 
#line 234 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_dma.h"
 
#line 255 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_dma.h"

#line 281 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_dma.h"

 


 
 
void DMA_DeInit(DMA_Channel_TypeDef* DMAy_Channelx);
void DMA_Init(DMA_Channel_TypeDef* DMAy_Channelx, DMA_InitTypeDef* DMA_InitStruct);
void DMA_StructInit(DMA_InitTypeDef* DMA_InitStruct);
void DMA_Cmd(DMA_Channel_TypeDef* DMAy_Channelx, FunctionalState NewState);
void DMA_ITConfig(DMA_Channel_TypeDef* DMAy_Channelx, u32 DMA_IT, FunctionalState NewState);	
u16 DMA_GetCurrDataCounter(DMA_Channel_TypeDef* DMAy_Channelx);																
FlagStatus DMA_GetFlagStatus(u32 DMA_FLAG);
void DMA_ClearFlag(u32 DMA_FLAG);
ITStatus DMA_GetITStatus(u32 DMA_IT);
void DMA_ClearITPendingBit(u32 DMA_IT);



 
#line 22 "..\\..\\Driver\\WOW\\INC\\STM32_DMA.H"
#line 1 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_nvic.h"














 

 



 
#line 23 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_nvic.h"

 
 
typedef struct
{
  u8 NVIC_IRQChannel;
  u8 NVIC_IRQChannelPreemptionPriority;
  u8 NVIC_IRQChannelSubPriority;
  FunctionalState NVIC_IRQChannelCmd;
} NVIC_InitTypeDef;

 
 
#line 96 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_nvic.h"


#line 158 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_nvic.h"


 
#line 170 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_nvic.h"





#line 182 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_nvic.h"












#line 201 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_nvic.h"











 






 








 
#line 239 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_nvic.h"












 
 
void NVIC_DeInit(void);
void NVIC_SCBDeInit(void);
void NVIC_PriorityGroupConfig(u32 NVIC_PriorityGroup);
void NVIC_Init(NVIC_InitTypeDef* NVIC_InitStruct);
void NVIC_StructInit(NVIC_InitTypeDef* NVIC_InitStruct);
void NVIC_SETPRIMASK(void);
void NVIC_RESETPRIMASK(void);
void NVIC_SETFAULTMASK(void);
void NVIC_RESETFAULTMASK(void);
void NVIC_BASEPRICONFIG(u32 NewPriority);
u32 NVIC_GetBASEPRI(void);
u16 NVIC_GetCurrentPendingIRQChannel(void);
ITStatus NVIC_GetIRQChannelPendingBitStatus(u8 NVIC_IRQChannel);
void NVIC_SetIRQChannelPendingBit(u8 NVIC_IRQChannel);
void NVIC_ClearIRQChannelPendingBit(u8 NVIC_IRQChannel);
u16 NVIC_GetCurrentActiveHandler(void);
ITStatus NVIC_GetIRQChannelActiveBitStatus(u8 NVIC_IRQChannel);
u32 NVIC_GetCPUID(void);
void NVIC_SetVectorTable(u32 NVIC_VectTab, u32 Offset);
void NVIC_GenerateSystemReset(void);
void NVIC_GenerateCoreReset(void);
void NVIC_SystemLPConfig(u8 LowPowerMode, FunctionalState NewState);
void NVIC_SystemHandlerConfig(u32 SystemHandler, FunctionalState NewState);
void NVIC_SystemHandlerPriorityConfig(u32 SystemHandler, u8 SystemHandlerPreemptionPriority,
                                      u8 SystemHandlerSubPriority);
ITStatus NVIC_GetSystemHandlerPendingBitStatus(u32 SystemHandler);
void NVIC_SetSystemHandlerPendingBit(u32 SystemHandler);
void NVIC_ClearSystemHandlerPendingBit(u32 SystemHandler);
ITStatus NVIC_GetSystemHandlerActiveBitStatus(u32 SystemHandler);
u32 NVIC_GetFaultHandlerSources(u32 SystemHandler);
u32 NVIC_GetFaultAddress(u32 SystemHandler);



 
#line 23 "..\\..\\Driver\\WOW\\INC\\STM32_DMA.H"
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



 
#line 24 "..\\..\\Driver\\WOW\\INC\\STM32_DMA.H"



 
typedef enum
{
	
  ADC1_RQ = 0x01,
  TIM2_CH3,  
  TIM4_CH1,
	
	USART3_TX	=	0X04,
	TIM1_CH1,
	TIM2_UP,
	TIM3_CH3,
	SPI1_RX,
	
	USART3_RX = 0X09,
	TIM1_CH2,
	TIM3_CH4,
	TIM3_UP,
	SPI1_TX,
	
	USART1_TX	=	0X0E,
	TIM1_CH4,
	TIM1_TRIG,
	TIM1_COM,
	TIM4_CH2,
	SPI2_RX,
	I2S2_RX,
	I2C2_TX,
	
	USART1_RX =	0X16,
	TIM1_UP,
	SPI2_TX,
	I2S2_TX,
	I2C2_RX,
	TIM2_CH1,
	TIM4_CH3,
	
	USART2_RX	=0X1D,
	TIM1_CH3,
	TIM3_CH1,
	TIM3_TRIG,
	I2C1_TX,
	
	USART2_TX	=	0X22,
	TIM2_CH2,
	TIM2_CH4,
	TIM4_UP,
	I2C1_RX,
	
	TIM5_CH4	=	0X27,
	TIM5_TRIG,
	TIM8_CH3,
	TIM8_UP,
	SPI3_RX,
	I2S3_RX,
	
	TIM8_CH4	=	0X2D,
	TIM8_TRIG,
	TIM8_COM,
	TIM5_CH3,
	TIM5_UP,
	SPI3_TX,
	I2S3_TX,
	
	TIM8_CH1	=	0X34,
	UART4_RX,
	TIM6_UP,
	DAC_CH1,
	
	TIM5_CH2	=	0X38,
	SDIO_RQ,
	TIM7_UP,
	DAC_CH2,
	
	ADC3_RQ	=	0X3C,
	TIM8_CH2,
	TIM5_CH1,
	UART4_TX
	
}Peripheral_Request_TypeDef;

#line 163 "..\\..\\Driver\\WOW\\INC\\STM32_DMA.H"





void DMA_Configuration(Peripheral_Request_TypeDef Request,u32 *MemoryAddr,u32 BufferSize);	
void DMA_Server(void);		







#line 18 "..\\..\\Driver\\WOW\\SCR\\STM32_DMA.C"
#line 1 ".\\main\\STM32_WOW.H"



 
















































































#line 1 "..\\..\\Examples\\WOW\\AMPLCDV11.H"




#line 1 "..\\..\\Driver\\Protocol\\AMP_PHY.H"





#line 7 "..\\..\\Driver\\Protocol\\AMP_PHY.H"






  
#line 24 "..\\..\\Driver\\Protocol\\AMP_PHY.H"

typedef enum _eucmd
{
  AmpCmdNone      = 0,    
  AmpCmdAck       = 1,    
  AmpCmdLed       = 2,    
  AmpCmdLock      = 3,    
  AmpCmdCard      = 4,    
  AmpCmdPwr       = 5,    
  AmpCmdSta       = 6,    
  AmpCmdGetOnline = 7,    
  AmpCmdBKligth   = 8,    
}eucmddef;
typedef enum _eSts
{
  AmpStsNone      = 0,    
  AmpStsLock      = 1,    
  AmpStsComm      = 2,    
}eStsdef;
typedef enum _eLockSts
{
  AmpLockOpen       = 0,    
  AmpLockOn         = 1,    
  AmpLockOpenFailed = 2,    
}eLockStsdef;
typedef enum _eCommSts
{
  AmpCommOK       = 0,    
  AmpCommTimeOut  = 1,    
}eCommStsdef;
typedef struct _stcmd
{
  unsigned char cmd :6;   
  unsigned char rw  :1;   
  unsigned char dir :1;   
}stcmddef;
typedef struct _stampaddr
{
  unsigned char address1;
  unsigned char address2;
  unsigned char address3;
}stampaddrdef;

typedef struct _stampcrc16
{
  unsigned char crcl;
  unsigned char crch;
}stampcrc16def;
typedef struct _stmsg
{
  unsigned char length;   
  stcmddef 			cmd;
	stampaddrdef	addr;
	unsigned char data[128];
}stmsgdef;
typedef struct _stampphy
{
  unsigned char head;
  stmsgdef      msg;
  stampcrc16def crc16;
  unsigned char end;
}stampphydef;




typedef enum  _CCPort
{
  NonPort     = 0,
  PcPort      = 1,  
  CabPort     = 2,  
  LayPort     = 3,  
  CardPort    = 4   
}enCCPortDef;
typedef struct _stSW        
{
  unsigned char ID        :6;   
  unsigned char ICreadFlg :1;   
  unsigned char MainFlg   :1;   
}stSWdef;
typedef struct _stFlg        
{
  unsigned short LayPownOn :1;   

}stFlgdef;
typedef struct _stStatus        
{
  unsigned short lockstd    :1;  
  unsigned short unlockerr  :1;  
  unsigned short Online     :1;  
}stStadef;
typedef struct _stAckQ        
{
  unsigned char PcAck     :1;   
  unsigned char PcDir     :1;   
  unsigned char CabAck    :1;   
  unsigned char CabDir    :1;   
  unsigned char LayAck    :1;   
  unsigned char LayDir    :1;   
  unsigned char CardAck   :1;   
  unsigned char CardDir   :1;   
}stAckQdef;
typedef struct _stSendCount   
{
  unsigned char PcCount;      
  unsigned char CabCount;     
  unsigned char LayCount;     
  unsigned char CardCount;    
}stSendCountdef;
typedef struct _stTx       
{
  unsigned char arry;           
  unsigned char size;           
  unsigned char data[128];   
}stTxdef;
typedef struct _stBuffer       
{  
  struct
  {
    unsigned char Pc:1;
    unsigned char Cab:1;
    unsigned char Lay:1;
    unsigned char Card:1;
  }WaitAck;
  unsigned char rxdbuffer[128]; 
  stTxdef   PcTx[20];     
  stTxdef   CabTx[20];    
  stTxdef   LayTx[20];    
  stTxdef   CardTx[20];   
}stBufferdef;
typedef struct _stTims       
{
  unsigned short runningtime;     
  unsigned short swicthidtime;    
  unsigned short SYSLEDTime;      
  unsigned short LockTime;        
  unsigned short PcSendTime;      
  unsigned short CabSendTime;     
  unsigned short LaySendTime;     
  unsigned short CardSendTime;    
}stTimesdef;
typedef struct _stRequest            
{
  unsigned short  unlockqust  :1;
  unsigned short  unlockrun   :1;
  unsigned short  reslock     :1;
  unsigned short  reslockqust :1;
  unsigned short  BLon        :1;
  unsigned short  BLoff       :1;
  unsigned short  PLon        :1;
  unsigned short  PLoff       :1;
}stReqdef;
typedef struct _stAMPPrl
{
  stTimesdef        Time;         

  stReqdef          Req;         
  stStadef          Sta;          
  stFlgdef          Flag;         
  stAckQdef         AckQ;         
  stBufferdef       buffer;       
  stSendCountdef    ReSend;
}stAMPProdef;


unsigned char API_AmpCheckFrame(unsigned char* pbuffer,unsigned short* length);
  
unsigned short getframe(unsigned char* pbuffer,unsigned short* length);
unsigned char* getheadaddr(unsigned char* pbuffer,unsigned short* length);
unsigned char AmpCrc16Check(unsigned char* pframe,unsigned short* length);
unsigned short SetFrame(unsigned char* pframe,unsigned short* length);    


unsigned short PaketUpMsg(unsigned	char* pbuffer,eucmddef cmd,unsigned	short* length);     
unsigned short PaketDownMsg(unsigned	char* pbuffer,eucmddef cmd,unsigned	short* length);   

unsigned char ackcheck(unsigned char* pframe);    
unsigned char addr1check(unsigned char* pframe,unsigned char addr1);
unsigned char addr2check(unsigned char* pframe,unsigned char addr2);
unsigned char addr3check(unsigned char* pframe,unsigned char addr3);

unsigned short SendTimeOut(enCCPortDef Port); 
unsigned short Releas_OneBuffer(enCCPortDef Port);


void ackFrame(enCCPortDef Port,unsigned char dir);
void Send_Server(void);
unsigned short Check_SendBuff(enCCPortDef Port); 
void Send_ConnectErr(enCCPortDef Port,unsigned char* pBuffer,unsigned short length);    

unsigned short AddSendBuffer(enCCPortDef Port,unsigned char* pBuffer,unsigned short length);




#line 6 "..\\..\\Examples\\WOW\\AMPLCDV11.H"









extern stAMPProdef   AMPPro;

void AMPLCDV11_Configuration(void);
void AMPLCDV11_Server(void);

void AMPLCDV11_Loop(void);

void AMPLCDV11_ComConfiguration(void);

void AMPLCDV11_Receive(void);

unsigned short HW_SendBuff(enCCPortDef Port,unsigned char* pBuffer,unsigned short length);

void Tim_Server(void);


void LCD_Configuration(void);
#line 87 ".\\main\\STM32_WOW.H"






















































 
 
 




 












 
























































































































































































































void WOW_Configuration(void);		
void WOW_Server(void);					
void MainServer(void);          










#line 19 "..\\..\\Driver\\WOW\\SCR\\STM32_DMA.C"

















































































 













																	














 
void DMA_Configuration(Peripheral_Request_TypeDef	Request,u32 *MemoryAddr,u32 BufferSize)	
{
	DMA_InitTypeDef DMA_Initstructure;
	NVIC_InitTypeDef NVIC_Initstructure;

	DMA_Channel_TypeDef* DMAy_Channelx=0;											

	FunctionalState	DMA_IT_Interruupt=ENABLE;									
	u8	DMAy_Channelx_IRQChannel=((u8)0x0B);		
	u32	DMAy_FLAG_GLx=0;																			
	
	
	u32 DMA_PeripheralBaseAddr=0;															
  u32 DMA_MemoryBaseAddr=(u32)MemoryAddr;										
  u32 DMA_DIR=((u32)0x00000000);												
  u32 DMA_BufferSize=BufferSize;														
  u32 DMA_PeripheralInc=((u32)0x00000000);					
  u32 DMA_MemoryInc=((u32)0x00000000);									
  u32 DMA_PeripheralDataSize=((u32)0x00000000);		
  u32 DMA_MemoryDataSize=((u32)0x00000000);						
  u32 DMA_Mode=((u32)0x00000000);															
																														
  u32 DMA_Priority=((u32)0x00003000);										
  u32 DMA_M2M=((u32)0x00000000);															
	
	

	((void)0);

	
	if(Request==ADC1_RQ)					
	{
		DMAy_Channelx=((DMA_Channel_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x0008));
		DMA_PeripheralBaseAddr=(u32)&((ADC_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x2400))->DR;										
		DMA_DIR=((u32)0x00000000);														
		DMA_PeripheralInc=((u32)0x00000000);							
		DMA_MemoryInc=((u32)0x00000000);											
		DMA_PeripheralDataSize=((u32)0x00000100);		
		DMA_MemoryDataSize=((u32)0x00000400);						
		DMA_Mode=((u32)0x00000020);																
		DMA_Priority=((u32)0x00003000);												
		DMA_M2M=((u32)0x00000000);																	
		
		DMAy_FLAG_GLx=((u32)0x00000001);															
		
		DMA_IT_Interruupt=DISABLE;																
	}
	else if(Request==TIM2_CH3)
	{
		DMAy_Channelx=((DMA_Channel_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x0008));
		DMA_PeripheralBaseAddr=(u32)&((TIM_TypeDef *) (((u32)0x40000000) + 0x0000))->CCR3;										
		DMA_DIR=((u32)0x00000000);															
		DMA_PeripheralInc=((u32)0x00000000);								
		DMA_MemoryInc=((u32)0x00000000);												
		DMA_PeripheralDataSize=((u32)0x00000100);			
		DMA_MemoryDataSize=((u32)0x00000400);							
		DMA_Mode=((u32)0x00000000);																		
		DMA_Priority=((u32)0x00003000);													
		DMA_M2M=((u32)0x00000000);																		
		
		DMAy_FLAG_GLx=((u32)0x00000001);																
		
		DMA_IT_Interruupt=DISABLE;																	
	}
	else if(Request==TIM4_CH1)
	{
		DMAy_Channelx=((DMA_Channel_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x0008));
		DMA_PeripheralBaseAddr=(u32)&((TIM_TypeDef *) (((u32)0x40000000) + 0x0800))->CCR1;										
		DMA_DIR=((u32)0x00000000);															
		DMA_PeripheralInc=((u32)0x00000000);								
		DMA_MemoryInc=((u32)0x00000000);												
		DMA_PeripheralDataSize=((u32)0x00000000);					
		DMA_MemoryDataSize=((u32)0x00000000);									
		DMA_Mode=((u32)0x00000000);																		
		DMA_Priority=((u32)0x00003000);													
		DMA_M2M=((u32)0x00000000);																		
		
		DMAy_FLAG_GLx=((u32)0x00000001);																
		
		DMA_IT_Interruupt=DISABLE;																	
	}
	else if(Request==USART3_TX)		
	{
		DMAy_Channelx=((DMA_Channel_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x001C));
	}
	else if(Request==TIM1_CH1)
	{
		DMAy_Channelx=((DMA_Channel_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x001C));
	}
	else if(Request==TIM2_UP)
	{
		DMAy_Channelx=((DMA_Channel_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x001C));
	}
	else if(Request==TIM3_CH3)		
	{
		DMAy_Channelx=((DMA_Channel_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x001C));
	}
	else if(Request==SPI1_RX)
	{
		DMAy_Channelx=((DMA_Channel_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x001C));
	}
	else if(Request==USART3_RX)		
	{
		DMAy_Channelx=((DMA_Channel_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x0030));
	}
	else if(Request==TIM1_CH2)
	{
		DMAy_Channelx=((DMA_Channel_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x0030));
	}
	else if(Request==TIM3_CH4)
	{
		DMAy_Channelx=((DMA_Channel_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x0030));
	}
	else if(Request==TIM3_UP)
	{
		DMAy_Channelx=((DMA_Channel_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x0030));
	}
	else if(Request==SPI1_TX)
	{
		DMAy_Channelx=((DMA_Channel_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x0030));
	}
	else if(Request==USART1_TX)		
	{
		DMAy_Channelx=((DMA_Channel_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x0044));
		DMA_PeripheralBaseAddr=(u32)&((USART_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x3800))->DR;									
		DMA_DIR=((u32)0x00000010);														
		DMA_PeripheralInc=((u32)0x00000000);							
		DMA_MemoryInc=((u32)0x00000080);												
		DMA_PeripheralDataSize=((u32)0x00000100);		
		DMA_MemoryDataSize=((u32)0x00000400);						
		DMA_Mode=((u32)0x00000000);																	
		DMA_Priority=((u32)0x00003000);												
		DMA_M2M=((u32)0x00000000);																	
		
		DMAy_FLAG_GLx=((u32)0x00001000);															
		
		DMA_IT_Interruupt=ENABLE;																	
	}
	else if(Request==TIM1_CH4)
	{
		DMAy_Channelx=((DMA_Channel_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x0044));
	}
	else if(Request==TIM1_TRIG)
	{
		DMAy_Channelx=((DMA_Channel_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x0044));
	}
	else if(Request==TIM1_COM)
	{
		DMAy_Channelx=((DMA_Channel_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x0044));
	}
	else if(Request==TIM4_CH2)
	{
		DMAy_Channelx=((DMA_Channel_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x0044));
	}
	else if(Request==SPI2_RX)
	{
		DMAy_Channelx=((DMA_Channel_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x0044));
	}
	else if(Request==I2S2_RX)
	{
		DMAy_Channelx=((DMA_Channel_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x0044));
	}
	else if(Request==I2C2_TX)
	{
		DMAy_Channelx=((DMA_Channel_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x0044));
	}
	else if(Request==USART1_RX)		
	{
		DMAy_Channelx=((DMA_Channel_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x0058));
		DMA_PeripheralBaseAddr=(u32)&((USART_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x3800))->DR;									
		DMA_DIR=((u32)0x00000000);														
		DMA_PeripheralInc=((u32)0x00000000);							
		DMA_MemoryInc=((u32)0x00000080);												
		DMA_PeripheralDataSize=((u32)0x00000100);		
		DMA_MemoryDataSize=((u32)0x00000400);						
		DMA_Mode=((u32)0x00000000);																	
		DMA_Priority=((u32)0x00003000);												
		DMA_M2M=((u32)0x00000000);																	
		
		DMAy_FLAG_GLx=((u32)0x00010000);															
		
		DMA_IT_Interruupt=DISABLE;																
	}
	else if(Request==TIM1_UP)
	{
		DMAy_Channelx=((DMA_Channel_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x0058));
	}
	else if(Request==SPI2_TX)
	{
		DMAy_Channelx=((DMA_Channel_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x0058));
	}
	else if(Request==I2S2_TX)
	{
		DMAy_Channelx=((DMA_Channel_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x0058));
	}
	else if(Request==I2C2_RX)
	{
		DMAy_Channelx=((DMA_Channel_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x0058));
	}
	else if(Request==TIM2_CH1)
	{
		DMAy_Channelx=((DMA_Channel_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x0058));
	}
	else if(Request==TIM4_CH3)
	{
		DMAy_Channelx=((DMA_Channel_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x0058));
	}
	else if(Request==USART2_RX)		
	{
		DMAy_Channelx=((DMA_Channel_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x006C));
	}
	else if(Request==TIM1_CH3)
	{
		DMAy_Channelx=((DMA_Channel_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x006C));
	}
	else if(Request==TIM3_CH1)
	{
		DMAy_Channelx=((DMA_Channel_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x006C));
	}
	else if(Request==TIM3_TRIG)
	{
		DMAy_Channelx=((DMA_Channel_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x006C));
	}
	else if(Request==I2C1_TX)
	{
		DMAy_Channelx=((DMA_Channel_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x006C));
	}
	else if(Request==USART2_TX)		
	{
		DMAy_Channelx=((DMA_Channel_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x0080));
	}
	else if(Request==TIM2_CH2)
	{
		DMAy_Channelx=((DMA_Channel_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x0080));
	}
	else if(Request==TIM2_CH4)
	{
		DMAy_Channelx=((DMA_Channel_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x0080));
	}
	else if(Request==TIM4_UP)
	{
		DMAy_Channelx=((DMA_Channel_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x0080));
	}
	else if(Request==I2C1_RX)
	{
		DMAy_Channelx=((DMA_Channel_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x0080));
	}
	else if(Request==TIM5_CH4)		
	{
		DMAy_Channelx=((DMA_Channel_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x0408));
	}
	else if(Request==TIM5_TRIG)
	{
		DMAy_Channelx=((DMA_Channel_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x0408));
	}
	else if(Request==TIM8_CH3)
	{
		DMAy_Channelx=((DMA_Channel_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x0408));
	}
	else if(Request==TIM8_UP)
	{
		DMAy_Channelx=((DMA_Channel_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x0408));
	}
	else if(Request==SPI3_RX)
	{
		DMAy_Channelx=((DMA_Channel_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x0408));
	}
	else if(Request==I2S3_RX)
	{
		DMAy_Channelx=((DMA_Channel_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x0408));
	}
	else if(Request==TIM8_CH4)		
	{
		DMAy_Channelx=((DMA_Channel_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x041C));
	}
	else if(Request==TIM8_TRIG)
	{
		DMAy_Channelx=((DMA_Channel_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x041C));
	}
	else if(Request==TIM8_COM)
	{
		DMAy_Channelx=((DMA_Channel_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x041C));
	}
	else if(Request==TIM5_CH3)
	{
		DMAy_Channelx=((DMA_Channel_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x041C));
	}
	else if(Request==TIM5_UP)
	{
		DMAy_Channelx=((DMA_Channel_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x041C));
	}
	else if(Request==SPI3_TX)
	{
		DMAy_Channelx=((DMA_Channel_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x041C));
	}
	else if(Request==I2S3_TX)
	{
		DMAy_Channelx=((DMA_Channel_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x041C));
	}
	else if(Request==TIM8_CH1)		
	{
		DMAy_Channelx=((DMA_Channel_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x0430));
	}
	else if(Request==UART4_RX)
	{
		DMAy_Channelx=((DMA_Channel_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x0430));
	}
	else if(Request==TIM6_UP)
	{
		DMAy_Channelx=((DMA_Channel_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x0430));
	}
	else if(Request==DAC_CH1)
	{
		DMAy_Channelx=((DMA_Channel_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x0430));
	}
	else if(Request==TIM5_CH2)		
	{
		DMAy_Channelx=((DMA_Channel_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x0444));
	}
	else if(Request==SDIO_RQ)
	{
		DMAy_Channelx=((DMA_Channel_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x0444));
	}
	else if(Request==TIM7_UP)
	{
		DMAy_Channelx=((DMA_Channel_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x0444));
	}
	else if(Request==DAC_CH2)
	{
		DMAy_Channelx=((DMA_Channel_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x0444));
	}
	else if(Request==ADC3_RQ)		
	{
		DMAy_Channelx=((DMA_Channel_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x0458));
	}
	else if(Request==TIM8_CH2)
	{
		DMAy_Channelx=((DMA_Channel_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x0458));
	}
	else if(Request==TIM5_CH1)
	{
		DMAy_Channelx=((DMA_Channel_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x0458));
	}
	else if(Request==UART4_TX)
	{
		DMAy_Channelx=((DMA_Channel_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x0458));
	}

	
	
	if(DMAy_Channelx>=((DMA_Channel_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x0008))||DMAy_Channelx<=((DMA_Channel_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x0080)))
	{
		RCC_AHBPeriphClockCmd(((u32)0x00000001),ENABLE);
	}
	else if(DMAy_Channelx>=((DMA_Channel_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x0408))||DMAy_Channelx<=((DMA_Channel_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x0458)))
	{
		RCC_AHBPeriphClockCmd(((u32)0x00000002),ENABLE);
	}

	
	
	
	
		
	
	 
	NVIC_Initstructure.NVIC_IRQChannel = DMAy_Channelx_IRQChannel;       			
	NVIC_Initstructure.NVIC_IRQChannelSubPriority = 0;     										
	NVIC_Initstructure.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_Initstructure.NVIC_IRQChannelCmd = ENABLE;        										
	NVIC_Init(&NVIC_Initstructure);

	 
	DMA_Initstructure.DMA_PeripheralBaseAddr =  (u32)DMA_PeripheralBaseAddr;	
	DMA_Initstructure.DMA_MemoryBaseAddr     = (u32)DMA_MemoryBaseAddr;				
	DMA_Initstructure.DMA_DIR = (u32)DMA_DIR;																	
	DMA_Initstructure.DMA_BufferSize = (u32)DMA_BufferSize; 									

	DMA_Initstructure.DMA_PeripheralInc = (u32)DMA_PeripheralInc;							
	DMA_Initstructure.DMA_MemoryInc =(u32)DMA_MemoryInc;											
	DMA_Initstructure.DMA_PeripheralDataSize = (u32)DMA_PeripheralDataSize;		
	DMA_Initstructure.DMA_MemoryDataSize = (u32)DMA_MemoryDataSize;						
	DMA_Initstructure.DMA_Mode = (u32)DMA_Mode;																
	DMA_Initstructure.DMA_Priority = (u32)DMA_Priority; 											
	DMA_Initstructure.DMA_M2M = (u32)DMA_M2M;																	
	DMA_Init(DMAy_Channelx,&DMA_Initstructure);																

	 
	DMA_ClearFlag(DMAy_FLAG_GLx);                                 						
	 
	DMA_Cmd(DMAy_Channelx,DISABLE);
	 
	DMA_ITConfig(DMAy_Channelx,((u32)0x00000002), DMA_IT_Interruupt);									




















}








 
void DMA_Server(void)
{ 
	WOW_Server();				






		 
	if(DMA_GetFlagStatus(((u32)0x00000010))== SET)
	{
			 
		DMA_ClearFlag(((u32)0x00000010)); 
		  
		DMA_Cmd(((DMA_Channel_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x001C)),DISABLE); 
	}
	 
	else if(DMA_GetFlagStatus(((u32)0x00001000))== SET)
	{
		 
		DMA_ClearFlag(((u32)0x00001000)); 
		  
		DMA_Cmd(((DMA_Channel_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x0044)),DISABLE);
	}
	 
	else if(DMA_GetFlagStatus(((u32)0x01000000))== SET)
	{
			 
		DMA_ClearFlag(((u32)0x01000000)); 
		  
		DMA_Cmd(((DMA_Channel_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x0080)),DISABLE); 
	}

	 
	else if(DMA_GetFlagStatus(((u32)0x10010000))== SET)
	{
			 
		DMA_ClearFlag(((u32)0x10010000)); 
		  
		DMA_Cmd(((DMA_Channel_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x0458)),DISABLE); 
	}
	




















 
	
}














