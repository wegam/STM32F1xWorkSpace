#line 1 "..\\..\\Driver\\WOW\\SCR\\STM32_PWM.C"













 



#line 1 "..\\..\\Driver\\WOW\\INC\\STM32_PWM.H"













 







#line 1 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_tim.h"














 

 



 
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

 
 
 



 
#line 23 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_tim.h"

 

 
typedef struct
{
  u16 TIM_Prescaler;
  u16 TIM_CounterMode;
  u16 TIM_Period;
  u16 TIM_ClockDivision;
  u8 TIM_RepetitionCounter;
} TIM_TimeBaseInitTypeDef;

 
typedef struct
{
  u16 TIM_OCMode;
  u16 TIM_OutputState;
  u16 TIM_OutputNState;
  u16 TIM_Pulse;
  u16 TIM_OCPolarity;
  u16 TIM_OCNPolarity;
  u16 TIM_OCIdleState;
  u16 TIM_OCNIdleState;
} TIM_OCInitTypeDef;

 
typedef struct
{
  u16 TIM_Channel;
  u16 TIM_ICPolarity;
  u16 TIM_ICSelection;
  u16 TIM_ICPrescaler;
  u16 TIM_ICFilter;
} TIM_ICInitTypeDef;

 
typedef struct
{
  u16 TIM_OSSRState;
  u16 TIM_OSSIState;
  u16 TIM_LOCKLevel; 
  u16 TIM_DeadTime;
  u16 TIM_Break;
  u16 TIM_BreakPolarity;
  u16 TIM_AutomaticOutput;
} TIM_BDTRInitTypeDef;

                              

#line 81 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_tim.h"




#line 91 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_tim.h"

 
#line 99 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_tim.h"

#line 106 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_tim.h"

#line 115 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_tim.h"
 






 
















 








 












 






 






 






 






 






 






 






 






 





 










 






 






 






 






 






 








 










 
#line 298 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_tim.h"



#line 308 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_tim.h"

#line 317 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_tim.h"

 
#line 338 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_tim.h"

#line 358 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_tim.h"

 
#line 378 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_tim.h"

#line 397 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_tim.h"

 
#line 406 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_tim.h"



#line 416 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_tim.h"

 










 
#line 437 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_tim.h"

#line 446 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_tim.h"






 








 






 






 






  








 
#line 500 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_tim.h"



#line 510 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_tim.h"

 






 






 





                                     
 






  
#line 548 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_tim.h"

#line 557 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_tim.h"

#line 593 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_tim.h"

 










 






 
#line 625 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_tim.h"

#line 638 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_tim.h"

#line 646 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_tim.h"

#line 665 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_tim.h"
                                                                                            
 


 


 
 

void TIM_DeInit(TIM_TypeDef* TIMx);
void TIM_TimeBaseInit(TIM_TypeDef* TIMx, TIM_TimeBaseInitTypeDef* TIM_TimeBaseInitStruct);
void TIM_OC1Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct);
void TIM_OC2Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct);
void TIM_OC3Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct);
void TIM_OC4Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct);
void TIM_ICInit(TIM_TypeDef* TIMx, TIM_ICInitTypeDef* TIM_ICInitStruct);
void TIM_PWMIConfig(TIM_TypeDef* TIMx, TIM_ICInitTypeDef* TIM_ICInitStruct);
void TIM_BDTRConfig(TIM_TypeDef* TIMx, TIM_BDTRInitTypeDef *TIM_BDTRInitStruct);
void TIM_TimeBaseStructInit(TIM_TimeBaseInitTypeDef* TIM_TimeBaseInitStruct);
void TIM_OCStructInit(TIM_OCInitTypeDef* TIM_OCInitStruct);
void TIM_ICStructInit(TIM_ICInitTypeDef* TIM_ICInitStruct);
void TIM_BDTRStructInit(TIM_BDTRInitTypeDef* TIM_BDTRInitStruct);
void TIM_Cmd(TIM_TypeDef* TIMx, FunctionalState NewState);
void TIM_CtrlPWMOutputs(TIM_TypeDef* TIMx, FunctionalState NewState);
void TIM_ITConfig(TIM_TypeDef* TIMx, u16 TIM_IT, FunctionalState NewState);
void TIM_GenerateEvent(TIM_TypeDef* TIMx, u16 TIM_EventSource);
void TIM_DMAConfig(TIM_TypeDef* TIMx, u16 TIM_DMABase, u16 TIM_DMABurstLength);
void TIM_DMACmd(TIM_TypeDef* TIMx, u16 TIM_DMASource, FunctionalState NewState);
void TIM_InternalClockConfig(TIM_TypeDef* TIMx);
void TIM_ITRxExternalClockConfig(TIM_TypeDef* TIMx, u16 TIM_InputTriggerSource);
void TIM_TIxExternalClockConfig(TIM_TypeDef* TIMx, u16 TIM_TIxExternalCLKSource,
                                u16 TIM_ICPolarity, u16 ICFilter);                                
void TIM_ETRClockMode1Config(TIM_TypeDef* TIMx, u16 TIM_ExtTRGPrescaler, u16 TIM_ExtTRGPolarity,
                             u16 ExtTRGFilter);
void TIM_ETRClockMode2Config(TIM_TypeDef* TIMx, u16 TIM_ExtTRGPrescaler, 
                             u16 TIM_ExtTRGPolarity, u16 ExtTRGFilter);
void TIM_ETRConfig(TIM_TypeDef* TIMx, u16 TIM_ExtTRGPrescaler, u16 TIM_ExtTRGPolarity,
                   u16 ExtTRGFilter);
void TIM_PrescalerConfig(TIM_TypeDef* TIMx, u16 Prescaler, u16 TIM_PSCReloadMode);
void TIM_CounterModeConfig(TIM_TypeDef* TIMx, u16 TIM_CounterMode);
void TIM_SelectInputTrigger(TIM_TypeDef* TIMx, u16 TIM_InputTriggerSource);
void TIM_EncoderInterfaceConfig(TIM_TypeDef* TIMx, u16 TIM_EncoderMode,
                                u16 TIM_IC1Polarity, u16 TIM_IC2Polarity);
void TIM_ForcedOC1Config(TIM_TypeDef* TIMx, u16 TIM_ForcedAction);
void TIM_ForcedOC2Config(TIM_TypeDef* TIMx, u16 TIM_ForcedAction);
void TIM_ForcedOC3Config(TIM_TypeDef* TIMx, u16 TIM_ForcedAction);
void TIM_ForcedOC4Config(TIM_TypeDef* TIMx, u16 TIM_ForcedAction);
void TIM_ARRPreloadConfig(TIM_TypeDef* TIMx, FunctionalState NewState);
void TIM_SelectCOM(TIM_TypeDef* TIMx, FunctionalState NewState);
void TIM_SelectCCDMA(TIM_TypeDef* TIMx, FunctionalState NewState);
void TIM_CCPreloadControl(TIM_TypeDef* TIMx, FunctionalState NewState);
void TIM_OC1PreloadConfig(TIM_TypeDef* TIMx, u16 TIM_OCPreload);
void TIM_OC2PreloadConfig(TIM_TypeDef* TIMx, u16 TIM_OCPreload);
void TIM_OC3PreloadConfig(TIM_TypeDef* TIMx, u16 TIM_OCPreload);
void TIM_OC4PreloadConfig(TIM_TypeDef* TIMx, u16 TIM_OCPreload);
void TIM_OC1FastConfig(TIM_TypeDef* TIMx, u16 TIM_OCFast);
void TIM_OC2FastConfig(TIM_TypeDef* TIMx, u16 TIM_OCFast);
void TIM_OC3FastConfig(TIM_TypeDef* TIMx, u16 TIM_OCFast);
void TIM_OC4FastConfig(TIM_TypeDef* TIMx, u16 TIM_OCFast);
void TIM_ClearOC1Ref(TIM_TypeDef* TIMx, u16 TIM_OCClear);
void TIM_ClearOC2Ref(TIM_TypeDef* TIMx, u16 TIM_OCClear);
void TIM_ClearOC3Ref(TIM_TypeDef* TIMx, u16 TIM_OCClear);
void TIM_ClearOC4Ref(TIM_TypeDef* TIMx, u16 TIM_OCClear);
void TIM_OC1PolarityConfig(TIM_TypeDef* TIMx, u16 TIM_OCPolarity);
void TIM_OC1NPolarityConfig(TIM_TypeDef* TIMx, u16 TIM_OCNPolarity);
void TIM_OC2PolarityConfig(TIM_TypeDef* TIMx, u16 TIM_OCPolarity);
void TIM_OC2NPolarityConfig(TIM_TypeDef* TIMx, u16 TIM_OCNPolarity);
void TIM_OC3PolarityConfig(TIM_TypeDef* TIMx, u16 TIM_OCPolarity);
void TIM_OC3NPolarityConfig(TIM_TypeDef* TIMx, u16 TIM_OCNPolarity);
void TIM_OC4PolarityConfig(TIM_TypeDef* TIMx, u16 TIM_OCPolarity);
void TIM_CCxCmd(TIM_TypeDef* TIMx, u16 TIM_Channel, u16 TIM_CCx);
void TIM_CCxNCmd(TIM_TypeDef* TIMx, u16 TIM_Channel, u16 TIM_CCxN);
void TIM_SelectOCxM(TIM_TypeDef* TIMx, u16 TIM_Channel, u16 TIM_OCMode);
void TIM_UpdateDisableConfig(TIM_TypeDef* TIMx, FunctionalState NewState);
void TIM_UpdateRequestConfig(TIM_TypeDef* TIMx, u16 TIM_UpdateSource);
void TIM_SelectHallSensor(TIM_TypeDef* TIMx, FunctionalState NewState);
void TIM_SelectOnePulseMode(TIM_TypeDef* TIMx, u16 TIM_OPMode);
void TIM_SelectOutputTrigger(TIM_TypeDef* TIMx, u16 TIM_TRGOSource);
void TIM_SelectSlaveMode(TIM_TypeDef* TIMx, u16 TIM_SlaveMode);
void TIM_SelectMasterSlaveMode(TIM_TypeDef* TIMx, u16 TIM_MasterSlaveMode);
void TIM_SetCounter(TIM_TypeDef* TIMx, u16 Counter);
void TIM_SetAutoreload(TIM_TypeDef* TIMx, u16 Autoreload);
void TIM_SetCompare1(TIM_TypeDef* TIMx, u16 Compare1);
void TIM_SetCompare2(TIM_TypeDef* TIMx, u16 Compare2);
void TIM_SetCompare3(TIM_TypeDef* TIMx, u16 Compare3);
void TIM_SetCompare4(TIM_TypeDef* TIMx, u16 Compare4);
void TIM_SetIC1Prescaler(TIM_TypeDef* TIMx, u16 TIM_ICPSC);
void TIM_SetIC2Prescaler(TIM_TypeDef* TIMx, u16 TIM_ICPSC);
void TIM_SetIC3Prescaler(TIM_TypeDef* TIMx, u16 TIM_ICPSC);
void TIM_SetIC4Prescaler(TIM_TypeDef* TIMx, u16 TIM_ICPSC);
void TIM_SetClockDivision(TIM_TypeDef* TIMx, u16 TIM_CKD);
u16 TIM_GetCapture1(TIM_TypeDef* TIMx);
u16 TIM_GetCapture2(TIM_TypeDef* TIMx);
u16 TIM_GetCapture3(TIM_TypeDef* TIMx);
u16 TIM_GetCapture4(TIM_TypeDef* TIMx);
u16 TIM_GetCounter(TIM_TypeDef* TIMx);
u16 TIM_GetPrescaler(TIM_TypeDef* TIMx);
FlagStatus TIM_GetFlagStatus(TIM_TypeDef* TIMx, u16 TIM_FLAG);
void TIM_ClearFlag(TIM_TypeDef* TIMx, u16 TIM_FLAG);
ITStatus TIM_GetITStatus(TIM_TypeDef* TIMx, u16 TIM_IT);
void TIM_ClearITPendingBit(TIM_TypeDef* TIMx, u16 TIM_IT);
                                                                                                             


 








#line 23 "..\\..\\Driver\\WOW\\INC\\STM32_PWM.H"
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



 
#line 24 "..\\..\\Driver\\WOW\\INC\\STM32_PWM.H"
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



 
#line 25 "..\\..\\Driver\\WOW\\INC\\STM32_PWM.H"
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



 
#line 26 "..\\..\\Driver\\WOW\\INC\\STM32_PWM.H"




typedef enum
{
  PWM_OUTChannel1	=	0,
	PWM_OUTChannel2,
	PWM_OUTChannel3,
	PWM_OUTChannel4,
} PWM_OUTChannelTypeDef;
typedef struct
{
	TIM_TypeDef*	TIMx;
	GPIO_TypeDef*	GPIOx;			
	u16 GPIO_Pin_n;						
	
	double PWM_Frequency;			
	u16 	PWM_Updata;					
	u32 	PWM_RunUp;					
	u32 	PWM_Count;					
}PWM_BasicDataDef;
typedef struct
{
	u16 	PWM_Cycle ;						
	u32 	PWM_Pulse;						
}PWM_RunDataDef;
typedef struct
{

	struct
	{
		TIM_TypeDef*	TIMx;
		GPIO_TypeDef*	GPIOx;			
		u16 GPIO_Pin_n;						
		
		double PWM_Frequency;			
		u16 	PWM_Updata;					
		u32 	PWM_RunUp;					
		u32 	PWM_Count;					
	}PWM_BasicData;		

	struct
	{
		u16 	PWM_Cycle ;					
		u32 	PWM_Pulse;					
	}PWM_RunData;			
}PWM_TimDef;
extern u32 Tim1_Count;
extern u32 Tim2_Count;
extern u32 Tim3_Count;
extern u32 Tim4_Count;


void PWM_OUT(TIM_TypeDef* TIMx,PWM_OUTChannelTypeDef PWM_OUTChanneln,double PWM_Frequency ,u16 PWM_Ratio);	
void PWM_OUTRemap(TIM_TypeDef* TIMx,PWM_OUTChannelTypeDef PWM_OUTChanneln,double PWM_Frequency ,u16 PWM_Ratio);	

void PWM_OUT2(TIM_TypeDef* TIMx,PWM_OUTChannelTypeDef PWM_OUTChanneln,double PWM_Frequency ,u16 PWM_Ratio);	
void SetPWM_Ratio(u16 PWM_Ratio);		





void PWM_OUT_TIMConf(PWM_TimDef* PWM_Tim);									
void PWM_OUT_SetFre(PWM_TimDef* PWM_Tim,double PWM_Frequency);	
void PWM_OUT_SetCount(PWM_TimDef* PWM_Tim,u32 PWM_Count);			
u8 PWM_OUT_TIMServer(PWM_TimDef* PWM_Tim);									



#line 19 "..\\..\\Driver\\WOW\\SCR\\STM32_PWM.C"
#line 1 "..\\..\\Driver\\WOW\\INC\\STM32_GPIO.H"













 





#line 21 "..\\..\\Driver\\WOW\\INC\\STM32_GPIO.H"




















	


void GPIO_DeInitAll(void);																							
void GPIO_Configuration(GPIO_TypeDef* GPIOx,	u16 GPIO_Pin_n,GPIOMode_TypeDef GPIO_Mode,GPIOSpeed_TypeDef GPIO_Speed);			


void GPIO_Configuration_INA(GPIO_TypeDef* GPIOx,	u16 GPIO_Pin_n);			
void GPIO_Configuration_INF(GPIO_TypeDef* GPIOx,	u16 GPIO_Pin_n);			

void GPIO_Configuration_IPD(GPIO_TypeDef* GPIOx,	u16 GPIO_Pin_n);			
void GPIO_Configuration_IPU(GPIO_TypeDef* GPIOx,	u16 GPIO_Pin_n);			
void GPIO_RegConfiguration_IPU(GPIO_TypeDef* GPIOx,	u16 GPIO_Pin_n);			



void GPIO_Configuration_OOD2	(GPIO_TypeDef* GPIOx,	u16 GPIO_Pin_n);			
void GPIO_Configuration_OOD10	(GPIO_TypeDef* GPIOx,	u16 GPIO_Pin_n);			
void GPIO_Configuration_OOD50	(GPIO_TypeDef* GPIOx,	u16 GPIO_Pin_n);			

void GPIO_Configuration_OPP2	(GPIO_TypeDef* GPIOx,	u16 GPIO_Pin_n);			
void GPIO_Configuration_OPP10	(GPIO_TypeDef* GPIOx,	u16 GPIO_Pin_n);			
void GPIO_Configuration_OPP50	(GPIO_TypeDef* GPIOx,	u16 GPIO_Pin_n);			
void GPIO_RegConfiguration_OPP50	(GPIO_TypeDef* GPIOx,	u16 GPIO_Pin_n);	

void GPIO_Configuration_AOD2	(GPIO_TypeDef* GPIOx,	u16 GPIO_Pin_n);			
void GPIO_Configuration_AOD10	(GPIO_TypeDef* GPIOx,	u16 GPIO_Pin_n);			
void GPIO_Configuration_AOD50	(GPIO_TypeDef* GPIOx,	u16 GPIO_Pin_n);			

void GPIO_Configuration_APP2	(GPIO_TypeDef* GPIOx,	u16 GPIO_Pin_n);			
void GPIO_Configuration_APP10	(GPIO_TypeDef* GPIOx,	u16 GPIO_Pin_n);			
void GPIO_Configuration_APP50	(GPIO_TypeDef* GPIOx,	u16 GPIO_Pin_n);			



void GPIO_Toggle	(GPIO_TypeDef* GPIOx,	u16 GPIO_Pin_n);		










#line 20 "..\\..\\Driver\\WOW\\SCR\\STM32_PWM.C"






























 

u32 Tim1_Count	=	0;
u32 Tim2_Count	=	0;
u32 Tim3_Count	=	0;
u32 Tim4_Count	=	0;

void PWM_ClockCmd(TIM_TypeDef* TIMx,u16 Prescaler,u16 Period,u8 PWM_RATIO);		
void PWM_GPIO_Configuration(void);			
void PWM_SET(TIM_TypeDef* TIMx,u8 PWM_RATIO);	






 
void PWM_OUT			
(
	TIM_TypeDef* TIMx,											
	PWM_OUTChannelTypeDef PWM_OUTChanneln,	
	double PWM_Frequency,										
	u16 PWM_Ratio														
)
{
	
	
	
	
	
	
	
	
	
	
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef	TIM_TimeBaseStructure;	
	TIM_OCInitTypeDef TIMOCInitStructure;
	RCC_ClocksTypeDef RCC_ClocksStatus;							
	
	GPIO_TypeDef* GPIOx				=	0;			
	u16 GPIO_Pin_n						=	0xFF;		
	u32 RCC_APB2Periph_GPIOx	=	0x00;		
	u32	TIMx_Frequency=0;								
	u16 TIMx_Prescaler				=	0	;			
  u16 TIMx_Period						=	0	;			


	double	Tim_num1					=	0	;			

	
	switch (*(u32*)&TIMx)
	{
		case ((((u32)0x40000000) + 0x10000) + 0x2C00):
			RCC_APB2PeriphClockCmd(((u32)0x00000800), ENABLE);
			switch(PWM_OUTChanneln)
			{
				case PWM_OUTChannel1:	GPIOx	=	((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0800));	GPIO_Pin_n	=	((u16)0x0100);		RCC_APB2Periph_GPIOx	=	((u32)0x00000004);	
															break;
				case PWM_OUTChannel2:	GPIOx	=	((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0800));	GPIO_Pin_n	=	((u16)0x0200);		RCC_APB2Periph_GPIOx	=	((u32)0x00000004);
															break;
				case PWM_OUTChannel3:	GPIOx	=	((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0800));	GPIO_Pin_n	=	((u16)0x0400);	RCC_APB2Periph_GPIOx	=	((u32)0x00000004);
															break;
				case PWM_OUTChannel4:	GPIOx	=	((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0800));	GPIO_Pin_n	=	((u16)0x0800);	RCC_APB2Periph_GPIOx	=	((u32)0x00000004);
															break;
			}
			break;
		
		case (((u32)0x40000000) + 0x0000):
			RCC_APB1PeriphClockCmd(((u32)0x00000001), ENABLE);
			switch(PWM_OUTChanneln)
			{
				case PWM_OUTChannel1:	GPIOx	=	((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0800));	GPIO_Pin_n	=	((u16)0x0001);		RCC_APB2Periph_GPIOx	=	((u32)0x00000004);
															break;
				case PWM_OUTChannel2:	GPIOx	=	((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0800));	GPIO_Pin_n	=	((u16)0x0002);		RCC_APB2Periph_GPIOx	=	((u32)0x00000004);
															break;
				case PWM_OUTChannel3:	GPIOx	=	((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0800));	GPIO_Pin_n	=	((u16)0x0004);		RCC_APB2Periph_GPIOx	=	((u32)0x00000004);
															break;
				case PWM_OUTChannel4:	GPIOx	=	((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0800));	GPIO_Pin_n	=	((u16)0x0008);		RCC_APB2Periph_GPIOx	=	((u32)0x00000004);
															break;
			}
			break;
		
		case (((u32)0x40000000) + 0x0400):
			RCC_APB1PeriphClockCmd(((u32)0x00000002), ENABLE);
			switch(PWM_OUTChanneln)
			{
				case PWM_OUTChannel1:	GPIOx	=	((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0800));	GPIO_Pin_n	=	((u16)0x0040);		RCC_APB2Periph_GPIOx	=	((u32)0x00000004);
															break;
				case PWM_OUTChannel2:	GPIOx	=	((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0800));	GPIO_Pin_n	=	((u16)0x0080);		RCC_APB2Periph_GPIOx	=	((u32)0x00000004);
															break;
				case PWM_OUTChannel3:	GPIOx	=	((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0C00));	GPIO_Pin_n	=	((u16)0x0001);		RCC_APB2Periph_GPIOx	=	((u32)0x00000008);
															break;
				case PWM_OUTChannel4:	GPIOx	=	((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0C00));	GPIO_Pin_n	=	((u16)0x0002);		RCC_APB2Periph_GPIOx	=	((u32)0x00000008);
															break;
			}
			break;
		
		case (((u32)0x40000000) + 0x0800):
			RCC_APB1PeriphClockCmd(((u32)0x00000004), ENABLE);
			switch(PWM_OUTChanneln)
			{
				case PWM_OUTChannel1:	GPIOx	=	((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0C00));	GPIO_Pin_n	=	((u16)0x0040);		RCC_APB2Periph_GPIOx	=	((u32)0x00000008);
															break;
				case PWM_OUTChannel2:	GPIOx	=	((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0C00));	GPIO_Pin_n	=	((u16)0x0080);		RCC_APB2Periph_GPIOx	=	((u32)0x00000008);
															break;
				case PWM_OUTChannel3:	GPIOx	=	((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0C00));	GPIO_Pin_n	=	((u16)0x0100);		RCC_APB2Periph_GPIOx	=	((u32)0x00000008);
															break;
				case PWM_OUTChannel4:	GPIOx	=	((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0C00));	GPIO_Pin_n	=	((u16)0x0200);		RCC_APB2Periph_GPIOx	=	((u32)0x00000008);
															break;
			}
			break;
		
		case (((u32)0x40000000) + 0x0C00):
			RCC_APB1PeriphClockCmd(((u32)0x00000008), ENABLE);
			break;
		
		case (((u32)0x40000000) + 0x1000):
			RCC_APB1PeriphClockCmd(((u32)0x00000010), ENABLE);
			break;
		
		case (((u32)0x40000000) + 0x1400):
			RCC_APB1PeriphClockCmd(((u32)0x00000020), ENABLE);
			break;
		
		case ((((u32)0x40000000) + 0x10000) + 0x3400):
			RCC_APB2PeriphClockCmd(((u32)0x00002000), ENABLE);
			break;
		
		default:
			break;		
	}
	
	
	
	RCC_APB2PeriphClockCmd(((u32)0x00000001), ENABLE);	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOx, ENABLE);	
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_n;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP ;
	GPIO_Init(GPIOx,&GPIO_InitStructure);	
	
	
	
	RCC_GetClocksFreq(&RCC_ClocksStatus);	
	TIMx_Frequency = RCC_ClocksStatus.SYSCLK_Frequency;
	if (((*(u32*)&TIMx)&(((u32)0x40000000) + 0x10000)) == (((u32)0x40000000) + 0x10000))
  {
    TIMx_Frequency = RCC_ClocksStatus.PCLK2_Frequency;	
  }
  else
  {
    TIMx_Frequency = RCC_ClocksStatus.PCLK1_Frequency;	
  }
	
	
	
	
	
	if(1/PWM_Frequency>10)	
	{
		Tim_num1=(double)(TIMx_Frequency)/(PWM_Frequency*100);							
		TIMx_Prescaler=60000;
		TIMx_Period=(u16)(((double)Tim_num1/(double)TIMx_Prescaler)*200);
	}
	else if(1/PWM_Frequency>1.0)
	{
		Tim_num1=(double)(TIMx_Frequency)/(PWM_Frequency*10);							
		TIMx_Prescaler=60000;
		TIMx_Period=(u16)(((double)Tim_num1/(double)TIMx_Prescaler)*20);
	}
	else if(PWM_Frequency>=1.0)
	{
		Tim_num1=(double)(TIMx_Frequency)/(PWM_Frequency);							
		Tim_num1=(double)(Tim_num1*2.0);
		if(Tim_num1>=10000000)
		{
			TIMx_Prescaler=2000;
			TIMx_Period=Tim_num1/TIMx_Prescaler;
		}
		else if(Tim_num1>=1000000)
		{
			TIMx_Prescaler=200;
			TIMx_Period=Tim_num1/TIMx_Prescaler;
		}
		else if(Tim_num1>=100000)
		{
			TIMx_Prescaler=20;
			TIMx_Period=Tim_num1/TIMx_Prescaler;
		}
		else if(Tim_num1>=65530)
		{
			TIMx_Prescaler=2;
			TIMx_Period=Tim_num1/TIMx_Prescaler;
		}
		else
		{
			TIMx_Prescaler=1;
			TIMx_Period=Tim_num1/TIMx_Prescaler;
		}
	}	
	
	TIM_TimeBaseStructure.TIM_Prescaler = TIMx_Prescaler-1; 				
	TIM_TimeBaseStructure.TIM_Period 		= TIMx_Period-1;        		
	TIM_TimeBaseStructure.TIM_ClockDivision = ((u16)0x0000);  				
	TIM_TimeBaseStructure.TIM_CounterMode = ((u16)0x0000);  		
	TIM_TimeBaseInit(TIMx, &TIM_TimeBaseStructure);		
	
	if((TIMx_Period*(u32)PWM_Ratio)>1000)
		PWM_Ratio=(u16)((u32)(TIMx_Period*PWM_Ratio)/1000);
	else if(PWM_Ratio!=0)
		PWM_Ratio=1;
		
	TIMOCInitStructure.TIM_OCMode = ((u16)0x0060); 								
	TIMOCInitStructure.TIM_Pulse =(u16)PWM_Ratio;										
	TIMOCInitStructure.TIM_OCPolarity = ((u16)0x0000);				
	TIMOCInitStructure.TIM_OutputState = ((u16)0x0001);		
	
	switch(PWM_OUTChanneln)
	{
		case PWM_OUTChannel1:	TIM_OC1Init(TIMx, &TIMOCInitStructure);												
		break;
		case PWM_OUTChannel2:	TIM_OC2Init(TIMx, &TIMOCInitStructure);												
		break;
		case PWM_OUTChannel3:	TIM_OC3Init(TIMx, &TIMOCInitStructure);												
		break;
		case PWM_OUTChannel4:	TIM_OC4Init(TIMx, &TIMOCInitStructure);												
		break;
		default:
		break;
	}	
	TIM_CtrlPWMOutputs(TIMx,ENABLE);																
	
	switch(PWM_OUTChanneln)			
	{
		case PWM_OUTChannel1:	TIM_OC1PreloadConfig(TIMx, ((u16)0x0008));
				break;
		case PWM_OUTChannel2:	TIM_OC2PreloadConfig(TIMx, ((u16)0x0008));
				break;
		case PWM_OUTChannel3:	TIM_OC3PreloadConfig(TIMx, ((u16)0x0008));
				break;
		case PWM_OUTChannel4:	TIM_OC4PreloadConfig(TIMx, ((u16)0x0008));
				break;
	}	
	
	TIM_ARRPreloadConfig(TIMx, ENABLE);			
	
	TIM_Cmd(TIMx, ENABLE); 									
}






 
void PWM_OUTRemap			
(
	TIM_TypeDef* TIMx,											
	PWM_OUTChannelTypeDef PWM_OUTChanneln,	
	double PWM_Frequency,										
	u16 PWM_Ratio														
)
{
	
	
	
	
	
	
	
	
	
	
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef	TIM_TimeBaseStructure;	
	TIM_OCInitTypeDef TIMOCInitStructure;
	RCC_ClocksTypeDef RCC_ClocksStatus;							
	
	GPIO_TypeDef* GPIOx				=	0;			
	u16 GPIO_Pin_n						=	0xFF;		
	u32 RCC_APB2Periph_GPIOx	=	0x00;		
	u32	TIMx_Frequency=0;								
	u16 TIMx_Prescaler				=	0	;			
  u16 TIMx_Period						=	0	;			


	double	Tim_num1					=	0	;			

	
	switch (*(u32*)&TIMx)
	{
		case ((((u32)0x40000000) + 0x10000) + 0x2C00):
			RCC_APB2PeriphClockCmd(((u32)0x00000800), ENABLE);
			switch(PWM_OUTChanneln)
			{
				case PWM_OUTChannel1:	GPIOx	=	((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0800));	GPIO_Pin_n	=	((u16)0x0100);		RCC_APB2Periph_GPIOx	=	((u32)0x00000004);	
															break;
				case PWM_OUTChannel2:	GPIOx	=	((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0800));	GPIO_Pin_n	=	((u16)0x0200);		RCC_APB2Periph_GPIOx	=	((u32)0x00000004);
															break;
				case PWM_OUTChannel3:	GPIOx	=	((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0800));	GPIO_Pin_n	=	((u16)0x0400);	RCC_APB2Periph_GPIOx	=	((u32)0x00000004);
															break;
				case PWM_OUTChannel4:	GPIOx	=	((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0800));	GPIO_Pin_n	=	((u16)0x0800);	RCC_APB2Periph_GPIOx	=	((u32)0x00000004);
															break;
			}
			break;
		
		case (((u32)0x40000000) + 0x0000):
			RCC_APB1PeriphClockCmd(((u32)0x00000001), ENABLE);
			switch(PWM_OUTChanneln)
			{
				case PWM_OUTChannel1:	GPIOx	=	((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0800));	GPIO_Pin_n	=	((u16)0x0001);		RCC_APB2Periph_GPIOx	=	((u32)0x00000004);
															break;
				case PWM_OUTChannel2:	GPIOx	=	((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0C00));	GPIO_Pin_n	=	((u16)0x0008);		RCC_APB2Periph_GPIOx	=	((u32)0x00000008);
															break;
				case PWM_OUTChannel3:	GPIOx	=	((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0800));	GPIO_Pin_n	=	((u16)0x0004);		RCC_APB2Periph_GPIOx	=	((u32)0x00000004);
															break;
				case PWM_OUTChannel4:	GPIOx	=	((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0800));	GPIO_Pin_n	=	((u16)0x0008);		RCC_APB2Periph_GPIOx	=	((u32)0x00000004);
															break;
			}
			break;
		
		case (((u32)0x40000000) + 0x0400):
			RCC_APB1PeriphClockCmd(((u32)0x00000002), ENABLE);
			switch(PWM_OUTChanneln)
			{
				case PWM_OUTChannel1:	GPIOx	=	((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0800));	GPIO_Pin_n	=	((u16)0x0040);		RCC_APB2Periph_GPIOx	=	((u32)0x00000004);
															break;
				case PWM_OUTChannel2:	GPIOx	=	((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0800));	GPIO_Pin_n	=	((u16)0x0080);		RCC_APB2Periph_GPIOx	=	((u32)0x00000004);
															break;
				case PWM_OUTChannel3:	GPIOx	=	((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0C00));	GPIO_Pin_n	=	((u16)0x0001);		RCC_APB2Periph_GPIOx	=	((u32)0x00000008);
															break;
				case PWM_OUTChannel4:	GPIOx	=	((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0C00));	GPIO_Pin_n	=	((u16)0x0002);		RCC_APB2Periph_GPIOx	=	((u32)0x00000008);
															break;
			}
			break;
		
		case (((u32)0x40000000) + 0x0800):
			RCC_APB1PeriphClockCmd(((u32)0x00000004), ENABLE);
			switch(PWM_OUTChanneln)
			{
				case PWM_OUTChannel1:	GPIOx	=	((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0C00));	GPIO_Pin_n	=	((u16)0x0040);		RCC_APB2Periph_GPIOx	=	((u32)0x00000008);
															break;
				case PWM_OUTChannel2:	GPIOx	=	((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0C00));	GPIO_Pin_n	=	((u16)0x0080);		RCC_APB2Periph_GPIOx	=	((u32)0x00000008);
															break;
				case PWM_OUTChannel3:	GPIOx	=	((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0C00));	GPIO_Pin_n	=	((u16)0x0100);		RCC_APB2Periph_GPIOx	=	((u32)0x00000008);
															break;
				case PWM_OUTChannel4:	GPIOx	=	((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0C00));	GPIO_Pin_n	=	((u16)0x0200);		RCC_APB2Periph_GPIOx	=	((u32)0x00000008);
															break;
			}
			break;
		
		case (((u32)0x40000000) + 0x0C00):
			RCC_APB1PeriphClockCmd(((u32)0x00000008), ENABLE);
			break;
		
		case (((u32)0x40000000) + 0x1000):
			RCC_APB1PeriphClockCmd(((u32)0x00000010), ENABLE);
			break;
		
		case (((u32)0x40000000) + 0x1400):
			RCC_APB1PeriphClockCmd(((u32)0x00000020), ENABLE);
			break;
		
		case ((((u32)0x40000000) + 0x10000) + 0x3400):
			RCC_APB2PeriphClockCmd(((u32)0x00002000), ENABLE);
			break;
		
		default:
			break;		
	}
	
	
	
	RCC_APB2PeriphClockCmd(((u32)0x00000001), ENABLE);	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOx, ENABLE);	
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_n;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP ;
	GPIO_Init(GPIOx,&GPIO_InitStructure);	
	
	
	
	RCC_GetClocksFreq(&RCC_ClocksStatus);	
	TIMx_Frequency = RCC_ClocksStatus.SYSCLK_Frequency;
	if (((*(u32*)&TIMx)&(((u32)0x40000000) + 0x10000)) == (((u32)0x40000000) + 0x10000))
  {
    TIMx_Frequency = RCC_ClocksStatus.PCLK2_Frequency;	
  }
  else
  {
    TIMx_Frequency = RCC_ClocksStatus.PCLK1_Frequency;	
  }
	
	
	
	
	
	if(1/PWM_Frequency>10)
	{
		Tim_num1=(double)(TIMx_Frequency)/(PWM_Frequency*100);							
		TIMx_Prescaler=60000;
		TIMx_Period=(u16)(((double)Tim_num1/(double)TIMx_Prescaler)*200);
	}
	else if(1/PWM_Frequency>1.0)
	{
		Tim_num1=(double)(TIMx_Frequency)/(PWM_Frequency*10);							
		TIMx_Prescaler=60000;
		TIMx_Period=(u16)(((double)Tim_num1/(double)TIMx_Prescaler)*20);
	}
	else if(PWM_Frequency>=1.0)
	{
		Tim_num1=(double)(TIMx_Frequency)/(PWM_Frequency);							
		Tim_num1=(double)(Tim_num1*2.0);
		if(Tim_num1>=10000000)
		{
			TIMx_Prescaler=2000;
			TIMx_Period=Tim_num1/TIMx_Prescaler;
		}
		else if(Tim_num1>=1000000)
		{
			TIMx_Prescaler=200;
			TIMx_Period=Tim_num1/TIMx_Prescaler;
		}
		else if(Tim_num1>=100000)
		{
			TIMx_Prescaler=20;
			TIMx_Period=Tim_num1/TIMx_Prescaler;
		}
		else if(Tim_num1>=65530)
		{
			TIMx_Prescaler=2;
			TIMx_Period=Tim_num1/TIMx_Prescaler;
		}
		else
		{
			TIMx_Prescaler=1;
			TIMx_Period=Tim_num1/TIMx_Prescaler;
		}
	}	
	
	TIM_TimeBaseStructure.TIM_Prescaler = TIMx_Prescaler-1; 				
	TIM_TimeBaseStructure.TIM_Period 		= TIMx_Period-1;        		
	TIM_TimeBaseStructure.TIM_ClockDivision = ((u16)0x0000);  				
	TIM_TimeBaseStructure.TIM_CounterMode = ((u16)0x0000);  		
	TIM_TimeBaseInit(TIMx, &TIM_TimeBaseStructure);		
	
	if((TIMx_Period*(u32)PWM_Ratio)>1000)
		PWM_Ratio=(u16)((u32)(TIMx_Period*PWM_Ratio)/1000);
	else if(PWM_Ratio!=0)
		PWM_Ratio=1;
		
	TIMOCInitStructure.TIM_OCMode = ((u16)0x0060); 								
	TIMOCInitStructure.TIM_Pulse =(u16)PWM_Ratio;										
	TIMOCInitStructure.TIM_OCPolarity = ((u16)0x0000);				
	TIMOCInitStructure.TIM_OutputState = ((u16)0x0001);		
	
	switch(PWM_OUTChanneln)
	{
		case PWM_OUTChannel1:	TIM_OC1Init(TIMx, &TIMOCInitStructure);												
		break;
		case PWM_OUTChannel2:	TIM_OC2Init(TIMx, &TIMOCInitStructure);												
		break;
		case PWM_OUTChannel3:	TIM_OC3Init(TIMx, &TIMOCInitStructure);												
		break;
		case PWM_OUTChannel4:	TIM_OC4Init(TIMx, &TIMOCInitStructure);												
		break;
		default:
		break;
	}	
	TIM_CtrlPWMOutputs(TIMx,ENABLE);																
	
	switch(PWM_OUTChanneln)			
	{
		case PWM_OUTChannel1:	TIM_OC1PreloadConfig(TIMx, ((u16)0x0008));
				break;
		case PWM_OUTChannel2:	TIM_OC2PreloadConfig(TIMx, ((u16)0x0008));
				break;
		case PWM_OUTChannel3:	TIM_OC3PreloadConfig(TIMx, ((u16)0x0008));
				break;
		case PWM_OUTChannel4:	TIM_OC4PreloadConfig(TIMx, ((u16)0x0008));
				break;
	}	
	
	TIM_ARRPreloadConfig(TIMx, ENABLE);			
	
	TIM_Cmd(TIMx, ENABLE); 									
}






 
void PWM_OUT2			
(
	TIM_TypeDef* TIMx,											
	PWM_OUTChannelTypeDef PWM_OUTChanneln,	
	double PWM_Frequency,										
	u16 PWM_Ratio														
)
{
	
	
	
	
	
	
	
	
	
	
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef	TIM_TimeBaseStructure;	
	TIM_OCInitTypeDef TIMOCInitStructure;
	RCC_ClocksTypeDef RCC_ClocksStatus;							
	
	GPIO_TypeDef* GPIOx				=	0;			
	u16 GPIO_Pin_n						=	0xFF;		
	u32 RCC_APB2Periph_GPIOx	=	0x00;		
	u32	TIMx_Frequency=0;								
	u16 TIMx_Prescaler				=	0	;			
  u16 TIMx_Period						=	0	;			


	double	Tim_num1					=	0	;			

	
	switch (*(u32*)&TIMx)
	{
		case ((((u32)0x40000000) + 0x10000) + 0x2C00):
			RCC_APB2PeriphClockCmd(((u32)0x00000800), ENABLE);
			switch(PWM_OUTChanneln)
			{
				case PWM_OUTChannel1:	GPIOx	=	((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0800));	GPIO_Pin_n	=	((u16)0x0100);		RCC_APB2Periph_GPIOx	=	((u32)0x00000004);	
															break;
				case PWM_OUTChannel2:	GPIOx	=	((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0800));	GPIO_Pin_n	=	((u16)0x0200);		RCC_APB2Periph_GPIOx	=	((u32)0x00000004);
															break;
				case PWM_OUTChannel3:	GPIOx	=	((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0800));	GPIO_Pin_n	=	((u16)0x0400);	RCC_APB2Periph_GPIOx	=	((u32)0x00000004);
															break;
				case PWM_OUTChannel4:	GPIOx	=	((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0800));	GPIO_Pin_n	=	((u16)0x0800);	RCC_APB2Periph_GPIOx	=	((u32)0x00000004);
															break;
			}
			break;
		
		case (((u32)0x40000000) + 0x0000):
			RCC_APB1PeriphClockCmd(((u32)0x00000001), ENABLE);
			switch(PWM_OUTChanneln)
			{
				case PWM_OUTChannel1:	GPIOx	=	((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0800));	GPIO_Pin_n	=	((u16)0x0001);		RCC_APB2Periph_GPIOx	=	((u32)0x00000004);
															break;
				case PWM_OUTChannel2:	GPIOx	=	((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0800));	GPIO_Pin_n	=	((u16)0x0002);		RCC_APB2Periph_GPIOx	=	((u32)0x00000004);
															break;
				case PWM_OUTChannel3:	GPIOx	=	((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0800));	GPIO_Pin_n	=	((u16)0x0004);		RCC_APB2Periph_GPIOx	=	((u32)0x00000004);
															break;
				case PWM_OUTChannel4:	GPIOx	=	((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0800));	GPIO_Pin_n	=	((u16)0x0008);		RCC_APB2Periph_GPIOx	=	((u32)0x00000004);
															break;
			}
			break;
		
		case (((u32)0x40000000) + 0x0400):
			RCC_APB1PeriphClockCmd(((u32)0x00000002), ENABLE);
			switch(PWM_OUTChanneln)
			{
				case PWM_OUTChannel1:	GPIOx	=	((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0800));	GPIO_Pin_n	=	((u16)0x0040);		RCC_APB2Periph_GPIOx	=	((u32)0x00000004);
															break;
				case PWM_OUTChannel2:	GPIOx	=	((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0800));	GPIO_Pin_n	=	((u16)0x0080);		RCC_APB2Periph_GPIOx	=	((u32)0x00000004);
															break;
				case PWM_OUTChannel3:	GPIOx	=	((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0C00));	GPIO_Pin_n	=	((u16)0x0001);		RCC_APB2Periph_GPIOx	=	((u32)0x00000008);
															break;
				case PWM_OUTChannel4:	GPIOx	=	((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0C00));	GPIO_Pin_n	=	((u16)0x0002);		RCC_APB2Periph_GPIOx	=	((u32)0x00000008);
															break;
			}
			break;
		
		case (((u32)0x40000000) + 0x0800):
			RCC_APB1PeriphClockCmd(((u32)0x00000004), ENABLE);
			switch(PWM_OUTChanneln)
			{
				case PWM_OUTChannel1:	GPIOx	=	((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0C00));	GPIO_Pin_n	=	((u16)0x0040);		RCC_APB2Periph_GPIOx	=	((u32)0x00000008);
															break;
				case PWM_OUTChannel2:	GPIOx	=	((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0C00));	GPIO_Pin_n	=	((u16)0x0080);		RCC_APB2Periph_GPIOx	=	((u32)0x00000008);
															break;
				case PWM_OUTChannel3:	GPIOx	=	((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0C00));	GPIO_Pin_n	=	((u16)0x0100);		RCC_APB2Periph_GPIOx	=	((u32)0x00000008);
															break;
				case PWM_OUTChannel4:	GPIOx	=	((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0C00));	GPIO_Pin_n	=	((u16)0x0200);		RCC_APB2Periph_GPIOx	=	((u32)0x00000008);
															break;
			}
			break;
		
		case (((u32)0x40000000) + 0x0C00):
			RCC_APB1PeriphClockCmd(((u32)0x00000008), ENABLE);
			break;
		
		case (((u32)0x40000000) + 0x1000):
			RCC_APB1PeriphClockCmd(((u32)0x00000010), ENABLE);
			break;
		
		case (((u32)0x40000000) + 0x1400):
			RCC_APB1PeriphClockCmd(((u32)0x00000020), ENABLE);
			break;
		
		case ((((u32)0x40000000) + 0x10000) + 0x3400):
			RCC_APB2PeriphClockCmd(((u32)0x00002000), ENABLE);
			break;
		
		default:
			break;		
	}
	
	
	
	RCC_APB2PeriphClockCmd(((u32)0x00000001), ENABLE);	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOx, ENABLE);	
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_n;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP ;
	GPIO_Init(GPIOx,&GPIO_InitStructure);	
	
	
	
	RCC_GetClocksFreq(&RCC_ClocksStatus);	
	TIMx_Frequency = RCC_ClocksStatus.SYSCLK_Frequency;;
	if (((*(u32*)&TIMx)&(((u32)0x40000000) + 0x10000)) == (((u32)0x40000000) + 0x10000))
  {
    TIMx_Frequency = RCC_ClocksStatus.PCLK2_Frequency;	
  }
  else
  {
    TIMx_Frequency = RCC_ClocksStatus.PCLK1_Frequency;	
  }
	
	
	
	
	
	if(1/PWM_Frequency>10)
	{
		Tim_num1=(double)(TIMx_Frequency)/(PWM_Frequency*100);							
		TIMx_Prescaler=60000;
		TIMx_Period=(u16)(((double)Tim_num1/(double)TIMx_Prescaler)*200);
	}
	else if(1/PWM_Frequency>1.0)
	{
		Tim_num1=(double)(TIMx_Frequency)/(PWM_Frequency*10);							
		TIMx_Prescaler=60000;
		TIMx_Period=(u16)(((double)Tim_num1/(double)TIMx_Prescaler)*20);
	}
	else if(PWM_Frequency>=1.0)
	{
		Tim_num1=(double)(TIMx_Frequency)/(PWM_Frequency);							
		Tim_num1=(double)(Tim_num1*2.0);
		if(Tim_num1>=10000000)
		{
			TIMx_Prescaler=2000;
			TIMx_Period=Tim_num1/TIMx_Prescaler;
		}
		else if(Tim_num1>=1000000)
		{
			TIMx_Prescaler=200;
			TIMx_Period=Tim_num1/TIMx_Prescaler;
		}
		else if(Tim_num1>=100000)
		{
			TIMx_Prescaler=20;
			TIMx_Period=Tim_num1/TIMx_Prescaler;
		}
		else if(Tim_num1>=65530)
		{
			TIMx_Prescaler=2;
			TIMx_Period=Tim_num1/TIMx_Prescaler;
		}
		else
		{
			TIMx_Prescaler=1;
			TIMx_Period=Tim_num1/TIMx_Prescaler;
		}
	}	
	
	TIM_TimeBaseStructure.TIM_Prescaler = TIMx_Prescaler-1; 				
	TIM_TimeBaseStructure.TIM_Period 		= TIMx_Period-1;        		
	TIM_TimeBaseStructure.TIM_ClockDivision = ((u16)0x0000);  				
	TIM_TimeBaseStructure.TIM_CounterMode = ((u16)0x0000);  		
	TIM_TimeBaseInit(TIMx, &TIM_TimeBaseStructure);		
	
	if((TIMx_Period*(u32)PWM_Ratio)>1200)
		PWM_Ratio=(u16)((u32)(TIMx_Period*PWM_Ratio)/1200);
	else if(PWM_Ratio!=0)
		PWM_Ratio=1;
		
	TIMOCInitStructure.TIM_OCMode = ((u16)0x0060); 								
	TIMOCInitStructure.TIM_Pulse =(u16)PWM_Ratio;										
	TIMOCInitStructure.TIM_OCPolarity = ((u16)0x0000);				
	TIMOCInitStructure.TIM_OutputState = ((u16)0x0001);		
	
	switch(PWM_OUTChanneln)
	{
		case PWM_OUTChannel1:	TIM_OC1Init(TIMx, &TIMOCInitStructure);												
		break;
		case PWM_OUTChannel2:	TIM_OC2Init(TIMx, &TIMOCInitStructure);												
		break;
		case PWM_OUTChannel3:	TIM_OC3Init(TIMx, &TIMOCInitStructure);												
		break;
		case PWM_OUTChannel4:	TIM_OC4Init(TIMx, &TIMOCInitStructure);												
		break;
		default:
		break;
	}	
	TIM_CtrlPWMOutputs(TIMx,ENABLE);																
	
	switch(PWM_OUTChanneln)			
	{
		case PWM_OUTChannel1:	TIM_OC1PreloadConfig(TIMx, ((u16)0x0008));
				break;
		case PWM_OUTChannel2:	TIM_OC2PreloadConfig(TIMx, ((u16)0x0008));
				break;
		case PWM_OUTChannel3:	TIM_OC3PreloadConfig(TIMx, ((u16)0x0008));
				break;
		case PWM_OUTChannel4:	TIM_OC4PreloadConfig(TIMx, ((u16)0x0008));
				break;
	}	
	
	TIM_ARRPreloadConfig(TIMx, ENABLE);			
	
	TIM_Cmd(TIMx, ENABLE); 									
}






 
void SetPWM_Ratio(u16 PWM_Ratio)
{







	
	((TIM_TypeDef *) (((u32)0x40000000) + 0x0000))->CCR1 = PWM_Ratio;
}







 
void PWM_OUT_TIMConf(PWM_TimDef* PWM_Tim)			
{
	
	TIM_TimeBaseInitTypeDef	TIM_TimeBaseStructure;	
	RCC_ClocksTypeDef RCC_ClocksStatus;							
	NVIC_InitTypeDef	NVIC_InitStructure;						
	
	
	
	

	TIM_TypeDef * TIMx		=	PWM_Tim->PWM_BasicData.TIMx;

	double PWM_Frequency	=	2*(PWM_Tim->PWM_BasicData.PWM_Frequency);
	
	u8 TIM_IRQChannel=0;


	u32	TIMx_Frequency				=	0;			
	u16 TIMx_Prescaler				=	0	;			
  u16 TIMx_Period						=	0	;			
	
	
	
	
	
	GPIO_Configuration_OPP50(PWM_Tim->PWM_BasicData.GPIOx,PWM_Tim->PWM_BasicData.GPIO_Pin_n);

	
	
	switch ((u32)TIMx)
	{
		case ((((u32)0x40000000) + 0x10000) + 0x2C00):
			RCC_APB2PeriphClockCmd(((u32)0x00000800), ENABLE);
			TIM_IRQChannel=((u8)0x19);	
			TIM_TimeBaseStructure.TIM_RepetitionCounter	=	0;
			break;
		
		case (((u32)0x40000000) + 0x0000):
			RCC_APB1PeriphClockCmd(((u32)0x00000001), ENABLE);
			TIM_IRQChannel=((u8)0x1C);
			break;
		
		case (((u32)0x40000000) + 0x0400):
			RCC_APB1PeriphClockCmd(((u32)0x00000002), ENABLE);
			TIM_IRQChannel=((u8)0x1D);
			break;
		
		case (((u32)0x40000000) + 0x0800):
			RCC_APB1PeriphClockCmd(((u32)0x00000004), ENABLE);
			TIM_IRQChannel=((u8)0x1E);
			break;
		
		case (((u32)0x40000000) + 0x0C00):
			RCC_APB1PeriphClockCmd(((u32)0x00000008), ENABLE);
			TIM_IRQChannel=((u8)0x32);
			break;
		
		case (((u32)0x40000000) + 0x1000):
			RCC_APB1PeriphClockCmd(((u32)0x00000010), ENABLE);
			TIM_IRQChannel=((u8)0x36);
			break;
		
		case (((u32)0x40000000) + 0x1400):
			RCC_APB1PeriphClockCmd(((u32)0x00000020), ENABLE);
			TIM_IRQChannel=((u8)0x37);
			break;
		
		case ((((u32)0x40000000) + 0x10000) + 0x3400):
			RCC_APB2PeriphClockCmd(((u32)0x00002000), ENABLE);
			TIM_IRQChannel=((u8)0x2C);
			TIM_TimeBaseStructure.TIM_RepetitionCounter	=	0;
			break;
		
		default:
			break;		
	}
	
	








	PWM_Tim->PWM_BasicData.PWM_Count	=	0;
	PWM_Tim->PWM_RunData.PWM_Cycle	=	0;


	

	
	
	
	
	RCC_GetClocksFreq(&RCC_ClocksStatus);	
	TIMx_Frequency = RCC_ClocksStatus.SYSCLK_Frequency;
	if ((((u32)TIMx)&(((u32)0x40000000) + 0x10000)) == (((u32)0x40000000) + 0x10000))
  {
    TIMx_Frequency = RCC_ClocksStatus.PCLK2_Frequency;	
  }
  else
  {
    TIMx_Frequency = RCC_ClocksStatus.PCLK1_Frequency;	
  }

	
	
	
	
	
	if(PWM_Frequency>100000)		
	{
		TIMx_Prescaler=0;
		TIMx_Period=(u16)(TIMx_Frequency/PWM_Frequency-1);
	}
	else if(PWM_Frequency>1000)	
	{
		TIMx_Prescaler=10-1;
		TIMx_Period=(u16)((TIMx_Frequency/PWM_Frequency)/10-1);
	}
	else if(PWM_Frequency>100)		
	{
		TIMx_Prescaler=100-1;
		TIMx_Period=(u16)((TIMx_Frequency/PWM_Frequency)/100-1);
	}
	else if(PWM_Frequency>10)		
	{
		TIMx_Prescaler=1000-1;
		TIMx_Period=(u16)((TIMx_Frequency/PWM_Frequency)/1000-1);
	}
	else if(PWM_Frequency<=10)		
	{
		TIMx_Prescaler=2000-1;
		TIMx_Period=(u16)((TIMx_Frequency/PWM_Frequency)/2000-1);
	}	
	
	TIM_TimeBaseStructure.TIM_Prescaler = TIMx_Prescaler; 				
	TIM_TimeBaseStructure.TIM_Period 		= TIMx_Period;        		
	TIM_TimeBaseStructure.TIM_ClockDivision = ((u16)0x0000);  				
	TIM_TimeBaseStructure.TIM_CounterMode = ((u16)0x0000);  		
	TIM_TimeBaseInit(TIMx, &TIM_TimeBaseStructure);		
		
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM_IRQChannel;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	 
	TIM_ClearFlag(TIMx, ((u16)0x0001));

	 
	TIM_ITConfig(TIMx, ((u16)0x0001), ENABLE); 
	
	TIM_Cmd(TIMx, DISABLE); 									
}






 
void PWM_OUT_SetFre(PWM_TimDef* PWM_Tim,double PWM_Frequency)			
{

	
	RCC_ClocksTypeDef RCC_ClocksStatus;							
	
	

	TIM_TypeDef * TIMx		=	PWM_Tim->PWM_BasicData.TIMx;
	
	u32	TIMx_Frequency	=	0	;			
	u16 TIMx_Prescaler	=	0	;			
  u16 TIMx_Period			=	0	;			
	
	PWM_Frequency				=	2*(PWM_Frequency);	
	
	
	
	RCC_GetClocksFreq(&RCC_ClocksStatus);	
	TIMx_Frequency = RCC_ClocksStatus.SYSCLK_Frequency;;
	if ((((u32)TIMx)&(((u32)0x40000000) + 0x10000)) == (((u32)0x40000000) + 0x10000))
  {
    TIMx_Frequency = RCC_ClocksStatus.PCLK2_Frequency;	
  }
  else
  {
    TIMx_Frequency = RCC_ClocksStatus.PCLK1_Frequency;	
  }
	
	if(PWM_Frequency>100000)		
	{
		TIMx_Prescaler=0;
		TIMx_Period=(u16)(TIMx_Frequency/PWM_Frequency-1);
	}
	else if(PWM_Frequency>1000)	
	{
		TIMx_Prescaler=10-1;
		TIMx_Period=(u16)((TIMx_Frequency/PWM_Frequency)/10-1);
	}
	else if(PWM_Frequency>100)		
	{
		TIMx_Prescaler=100-1;
		TIMx_Period=(u16)((TIMx_Frequency/PWM_Frequency)/100-1);
	}
	else if(PWM_Frequency>10)		
	{
		TIMx_Prescaler=1000-1;
		TIMx_Period=(u16)((TIMx_Frequency/PWM_Frequency)/1000-1);
	}
	else if(PWM_Frequency<=10)		
	{
		TIMx_Prescaler=2000-1;
		TIMx_Period=(u16)((TIMx_Frequency/PWM_Frequency)/2000-1);
	}
	
	
	 
  TIMx->ARR = TIMx_Period;        		

   
  TIMx->PSC = TIMx_Prescaler; 				
	

}





 
void PWM_OUT_SetCount(PWM_TimDef* PWM_Tim,u32 PWM_Count)			
{
	if(PWM_Count	!=	0)
	{
		PWM_Tim->PWM_BasicData.PWM_Count	=	2*PWM_Count;
		PWM_Tim->PWM_RunData.PWM_Pulse	=	0;
		PWM_Tim->PWM_RunData.PWM_Cycle	=	0;	
		
		
		PWM_Tim->PWM_BasicData.GPIOx->BRR = PWM_Tim->PWM_BasicData.GPIO_Pin_n;			
		((TIM_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x2C00))->CNT	=	1;
		TIM_Cmd(PWM_Tim->PWM_BasicData.TIMx, ENABLE); 															
	}
	else
	{
		PWM_Tim->PWM_BasicData.PWM_Count	=	0;
		PWM_Tim->PWM_RunData.PWM_Pulse	=	0;
		PWM_Tim->PWM_RunData.PWM_Cycle	=	0;
		
		PWM_Tim->PWM_BasicData.GPIOx->BRR = PWM_Tim->PWM_BasicData.GPIO_Pin_n;			
		TIM_Cmd(PWM_Tim->PWM_BasicData.TIMx, DISABLE); 															
	}
}





 
u8 PWM_OUT_TIMServer(PWM_TimDef* PWM_Tim)			
{
	volatile u8	temp	=	0;
	if((PWM_Tim->PWM_BasicData.TIMx->SR & ((u16)0x0001))	== ((u16)0x0001))
	{
		if(PWM_Tim->PWM_RunData.PWM_Pulse<PWM_Tim->PWM_BasicData.PWM_Count)
		{
			if(PWM_Tim->PWM_RunData.PWM_Pulse	<	PWM_Tim->PWM_BasicData.PWM_RunUp)		
			{
				if(PWM_Tim->PWM_RunData.PWM_Cycle++	>=	PWM_Tim->PWM_BasicData.PWM_Updata)
				{
					PWM_Tim->PWM_RunData.PWM_Cycle	=	0;
					PWM_Tim->PWM_BasicData.PWM_Frequency+=20;						
					PWM_OUT_SetFre(PWM_Tim,PWM_Tim->PWM_BasicData.PWM_Frequency);														
				}
			}
			else if(PWM_Tim->PWM_RunData.PWM_Pulse+(PWM_Tim->PWM_BasicData.PWM_RunUp)>PWM_Tim->PWM_BasicData.PWM_Count)
			{
				if(PWM_Tim->PWM_RunData.PWM_Cycle++>=PWM_Tim->PWM_BasicData.PWM_Updata	&&	PWM_Tim->PWM_BasicData.PWM_Frequency>200)
				{
					PWM_Tim->PWM_RunData.PWM_Cycle	=	0;
					PWM_Tim->PWM_BasicData.PWM_Frequency-=20;						
					PWM_OUT_SetFre(PWM_Tim,PWM_Tim->PWM_BasicData.PWM_Frequency);														
				}
			}
		
			PWM_Tim->PWM_RunData.PWM_Pulse++;
			
			GPIO_Toggle	(PWM_Tim->PWM_BasicData.GPIOx,	PWM_Tim->PWM_BasicData.GPIO_Pin_n);		
			

			return 1;
			
		}
		else
		{
			PWM_Tim->PWM_RunData.PWM_Pulse	=	0;
			PWM_Tim->PWM_BasicData.GPIOx->BRR = PWM_Tim->PWM_BasicData.GPIO_Pin_n;			
			TIM_ClearFlag(PWM_Tim->PWM_BasicData.TIMx, ((u16)0x0001));									
			TIM_Cmd(PWM_Tim->PWM_BasicData.TIMx, DISABLE); 															
			return 2;				
			
		}
		TIM_ClearFlag(PWM_Tim->PWM_BasicData.TIMx, ((u16)0x0001));									
		return 1;
	}
	return 0;
}


































































































































































































