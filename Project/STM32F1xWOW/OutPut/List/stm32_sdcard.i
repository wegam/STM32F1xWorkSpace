#line 1 "..\\..\\Driver\\WOW\\SCR\\STM32_SDCard.C"













 

#line 1 "..\\..\\Driver\\WOW\\INC\\STM32_SDCard.H"













 



#line 1 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_gpio.h"














 

 



 
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



 
#line 19 "..\\..\\Driver\\WOW\\INC\\STM32_SDCard.H"
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



 
#line 20 "..\\..\\Driver\\WOW\\INC\\STM32_SDCard.H"
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



 
#line 21 "..\\..\\Driver\\WOW\\INC\\STM32_SDCard.H"
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



 
#line 22 "..\\..\\Driver\\WOW\\INC\\STM32_SDCard.H"
#line 1 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_dma.h"














 



 
 



 
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



 
#line 23 "..\\..\\Driver\\WOW\\INC\\STM32_SDCard.H"


#line 1 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_sdio.h"














 

 



 
#line 23 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_sdio.h"

 
typedef struct
{
  u8 SDIO_ClockDiv;
  u32 SDIO_ClockEdge;
  u32 SDIO_ClockBypass;
  u32 SDIO_ClockPowerSave;
  u32 SDIO_BusWide;
  u32 SDIO_HardwareFlowControl;
} SDIO_InitTypeDef;

typedef struct
{
  u32 SDIO_Argument;
  u32 SDIO_CmdIndex;
  u32 SDIO_Response;
  u32 SDIO_Wait;
  u32 SDIO_CPSM;
} SDIO_CmdInitTypeDef;

typedef struct
{
  u32 SDIO_DataTimeOut;
  u32 SDIO_DataLength;
  u32 SDIO_DataBlockSize;
  u32 SDIO_TransferDir;
  u32 SDIO_TransferMode;
  u32 SDIO_DPSM;
} SDIO_DataInitTypeDef;

 
 





                                   






  






 






                                
  





                                  
 





 
#line 121 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_sdio.h"



 


 








 







 





 








 


 
#line 178 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_sdio.h"

#line 194 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_sdio.h"

 






 






 





 
#line 240 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_sdio.h"

#line 265 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_sdio.h"



#line 292 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_sdio.h"


                                                        
 






 
 
void SDIO_DeInit(void);
void SDIO_Init(SDIO_InitTypeDef* SDIO_InitStruct);
void SDIO_StructInit(SDIO_InitTypeDef* SDIO_InitStruct);
void SDIO_ClockCmd(FunctionalState NewState);
void SDIO_SetPowerState(u32 SDIO_PowerState);
u32 SDIO_GetPowerState(void);
void SDIO_ITConfig(u32 SDIO_IT, FunctionalState NewState);
void SDIO_DMACmd(FunctionalState NewState);
void SDIO_SendCommand(SDIO_CmdInitTypeDef *SDIO_CmdInitStruct);
void SDIO_CmdStructInit(SDIO_CmdInitTypeDef* SDIO_CmdInitStruct);
u8 SDIO_GetCommandResponse(void);
u32 SDIO_GetResponse(u32 SDIO_RESP);
void SDIO_DataConfig(SDIO_DataInitTypeDef* SDIO_DataInitStruct);
void SDIO_DataStructInit(SDIO_DataInitTypeDef* SDIO_DataInitStruct);
u32 SDIO_GetDataCounter(void);
u32 SDIO_ReadData(void);
void SDIO_WriteData(u32 Data);
u32 SDIO_GetFIFOCount(void);
void SDIO_StartSDIOReadWait(FunctionalState NewState);
void SDIO_StopSDIOReadWait(FunctionalState NewState);
void SDIO_SetSDIOReadWaitMode(u32 SDIO_ReadWaitMode);
void SDIO_SetSDIOOperation(FunctionalState NewState);
void SDIO_SendSDIOSuspendCmd(FunctionalState NewState);
void SDIO_CommandCompletionCmd(FunctionalState NewState);
void SDIO_CEATAITCmd(FunctionalState NewState);
void SDIO_SendCEATACmd(FunctionalState NewState);
FlagStatus SDIO_GetFlagStatus(u32 SDIO_FLAG);
void SDIO_ClearFlag(u32 SDIO_FLAG);
ITStatus SDIO_GetITStatus(u32 SDIO_IT);
void SDIO_ClearITPendingBit(u32 SDIO_IT);



 
#line 26 "..\\..\\Driver\\WOW\\INC\\STM32_SDCard.H"

#line 1 "..\\..\\Driver\\WOW\\INC\\STM32F10x_BitBand.H"




 




 












 

 



 
#line 31 "..\\..\\Driver\\WOW\\INC\\STM32F10x_BitBand.H"
 


 





#line 47 "..\\..\\Driver\\WOW\\INC\\STM32F10x_BitBand.H"
  
#line 55 "..\\..\\Driver\\WOW\\INC\\STM32F10x_BitBand.H"

 
 
 
 
 
#line 68 "..\\..\\Driver\\WOW\\INC\\STM32F10x_BitBand.H"

#line 76 "..\\..\\Driver\\WOW\\INC\\STM32F10x_BitBand.H"
 
#line 84 "..\\..\\Driver\\WOW\\INC\\STM32F10x_BitBand.H"

 
 
 
 
#line 103 "..\\..\\Driver\\WOW\\INC\\STM32F10x_BitBand.H"

 
 
 
 
#line 124 "..\\..\\Driver\\WOW\\INC\\STM32F10x_BitBand.H"

#line 141 "..\\..\\Driver\\WOW\\INC\\STM32F10x_BitBand.H"

 
#line 159 "..\\..\\Driver\\WOW\\INC\\STM32F10x_BitBand.H"

#line 176 "..\\..\\Driver\\WOW\\INC\\STM32F10x_BitBand.H"
 
#line 193 "..\\..\\Driver\\WOW\\INC\\STM32F10x_BitBand.H"

#line 210 "..\\..\\Driver\\WOW\\INC\\STM32F10x_BitBand.H"

 
#line 228 "..\\..\\Driver\\WOW\\INC\\STM32F10x_BitBand.H"

#line 245 "..\\..\\Driver\\WOW\\INC\\STM32F10x_BitBand.H"

 
#line 263 "..\\..\\Driver\\WOW\\INC\\STM32F10x_BitBand.H"

#line 280 "..\\..\\Driver\\WOW\\INC\\STM32F10x_BitBand.H"
 
  
#line 298 "..\\..\\Driver\\WOW\\INC\\STM32F10x_BitBand.H"

#line 315 "..\\..\\Driver\\WOW\\INC\\STM32F10x_BitBand.H"

					 


 


#line 28 "..\\..\\Driver\\WOW\\INC\\STM32_SDCard.H"

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



 

#line 30 "..\\..\\Driver\\WOW\\INC\\STM32_SDCard.H"
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



 

#line 31 "..\\..\\Driver\\WOW\\INC\\STM32_SDCard.H"
#line 1 "..\\..\\Library\\C\\stdarg.h"
 
 
 





 










#line 27 "..\\..\\Library\\C\\stdarg.h"








 

 
 
#line 57 "..\\..\\Library\\C\\stdarg.h"
    typedef struct __va_list { void *__ap; } va_list;

   






 


   










 


   















 




   

 


   




 



   





 







#line 138 "..\\..\\Library\\C\\stdarg.h"



#line 147 "..\\..\\Library\\C\\stdarg.h"

 

#line 32 "..\\..\\Driver\\WOW\\INC\\STM32_SDCard.H"
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





 
#line 33 "..\\..\\Driver\\WOW\\INC\\STM32_SDCard.H"


 






























#line 73 "..\\..\\Driver\\WOW\\INC\\STM32_SDCard.H"















#line 104 "..\\..\\Driver\\WOW\\INC\\STM32_SDCard.H"






#line 119 "..\\..\\Driver\\WOW\\INC\\STM32_SDCard.H"
	





 
#line 146 "..\\..\\Driver\\WOW\\INC\\STM32_SDCard.H"

 












#line 171 "..\\..\\Driver\\WOW\\INC\\STM32_SDCard.H"




 





 






 
#line 224 "..\\..\\Driver\\WOW\\INC\\STM32_SDCard.H"




#line 235 "..\\..\\Driver\\WOW\\INC\\STM32_SDCard.H"



 
#line 247 "..\\..\\Driver\\WOW\\INC\\STM32_SDCard.H"


 
#line 261 "..\\..\\Driver\\WOW\\INC\\STM32_SDCard.H"

 




 
#line 276 "..\\..\\Driver\\WOW\\INC\\STM32_SDCard.H"





 
 
typedef enum {SDCard_ERROR = 0,SDCard_SUCCESS  = !SDCard_ERROR} SDCard_ErrorStatus;

typedef enum
{
   
  SD_CMD_CRC_FAIL                    = (1),  
  SD_DATA_CRC_FAIL                   = (2),  
  SD_CMD_RSP_TIMEOUT                 = (3),  
  SD_DATA_TIMEOUT                    = (4),  
  SD_TX_UNDERRUN                     = (5),  
  SD_RX_OVERRUN                      = (6),  
  SD_START_BIT_ERR                   = (7),  
  SD_CMD_OUT_OF_RANGE                = (8),  
  SD_ADDR_MISALIGNED                 = (9),  
  SD_BLOCK_LEN_ERR                   = (10),  
  SD_ERASE_SEQ_ERR                   = (11),  
  SD_BAD_ERASE_PARAM                 = (12),  
  SD_WRITE_PROT_VIOLATION            = (13),  
  SD_LOCK_UNLOCK_FAILED              = (14),  
  SD_COM_CRC_FAILED                  = (15),  
  SD_ILLEGAL_CMD                     = (16),  
  SD_CARD_ECC_FAILED                 = (17),  
  SD_CC_ERROR                        = (18),  
  SD_GENERAL_UNKNOWN_ERROR           = (19),  
  SD_STREAM_READ_UNDERRUN            = (20),  
  SD_STREAM_WRITE_OVERRUN            = (21),  
  SD_CID_CSD_OVERWRITE               = (22),  
  SD_WP_ERASE_SKIP                   = (23),  
  SD_CARD_ECC_DISABLED               = (24),  
  SD_ERASE_RESET                     = (25),  
  SD_AKE_SEQ_ERROR                   = (26),  
  SD_INVALID_VOLTRANGE               = (27),
  SD_ADDR_OUT_OF_RANGE               = (28),
  SD_SWITCH_ERROR                    = (29),
  SD_SDIO_DISABLED                   = (30),
  SD_SDIO_FUNCTION_BUSY              = (31),
  SD_SDIO_FUNCTION_FAILED            = (32),
  SD_SDIO_UNKNOWN_FUNCTION           = (33),

   
  SD_INTERNAL_ERROR, 
  SD_NOT_CONFIGURED,
  SD_REQUEST_PENDING, 
  SD_REQUEST_NOT_APPLICABLE, 
  SD_INVALID_PARAMETER,  
  SD_UNSUPPORTED_FEATURE,  
  SD_UNSUPPORTED_HW,  
  SD_ERROR,  
  SD_OK  
} SD_Error_TypeDef;

typedef enum
{
  SD_NO_TRANSFER  = 0,
  SD_TRANSFER_IN_PROGRESS
} SDTransferState_TypeDef;

typedef enum 	 
{
	SD_TYPE_ERR     =	0X00,	
	SD_TYPE_MMC     =	0X01,	
	SD_TYPE_V1      =	0X02,	
	SD_TYPE_V2      =	0X03,	
	SD_TYPE_V2MC   	=	0X04,	
	SD_TYPE_V2HC    =	0X06	
}SDCard_TYPE_TypeDef;

typedef enum 	 
{
	In_Idle_State  						=	0X00,	
	Erase_Reset     					=	0X01,	
	Illegal_Command      			=	0X02,	
	Communication_CRC_Error 	=	0X03,	
	Erase_Sequence_Error			=	0X04,	
	Address_Error    					=	0X06,	
	Parameter_Error						=	0X06,	
}SDCard_R1_TypeDef;
typedef enum 	 
{
	SDCard_Ready  						=	0X00,	
	SDCard_DMA_EN  						=	0X01,	
	SDCard_DMA_DIS  					=	0X02,	
	SDCard_Busy     					=	0X03,	
}SDCard_Status_TypeDef;






typedef enum 	 
{
	Reserved,
} SDCard_OCR_TypeDef;

typedef enum 	 
{
	SDCard_DeInit						=	0X00,	
	SDCard_StepReady				=	0X01,	
	SDCard_StepIDLE					=	0X02,	
	SDCard_StepRESET0				=	0X03,	
	SDCard_StepRESET1				=	0X04,	
	SDCard_StepGetOCR				=	0X05,	
	SDCard_StepGetCSD				=	0X06,	
	SDCard_StepGetCID				=	0X07,	
} SDCard_Step_TypeDef;
typedef struct
{
  unsigned short TransferredBytes;
  SD_Error_TypeDef TransferError;
  unsigned char  padding;
} SDLastTransferInfo_TypeDef;

typedef struct       
{
  volatile unsigned char  ManufacturerID;        					
  volatile unsigned short OEM_AppliID;           			


  volatile unsigned char  ProdRev;               				
  volatile unsigned int ProdSN;                		
  volatile unsigned char  Reserved1;             								
  volatile unsigned short ManufactDate;          			
  volatile unsigned char  CID_CRC;               									
  volatile unsigned char  Reserved2;             								
	volatile unsigned char  ProdName[5];						
} SDCard_CID_TypeDef;

typedef struct        	
{
  volatile unsigned char  CSDStruct;             						

  volatile unsigned char  Reserved1;             																
  volatile unsigned char  TAAC;                  									
  volatile unsigned char  NSAC;                  		
  volatile unsigned char  MaxBusClkFrec;         								
  volatile unsigned short CardComdClasses;       										
  volatile unsigned char  RdBlockLen;            							
  volatile unsigned char  PartBlockRead;         					
  volatile unsigned char  WrBlockMisalign;       								
  volatile unsigned char  RdBlockMisalign;       									
  volatile unsigned char  DSRImpl;               													
  volatile unsigned char  Reserved2;             																
  volatile unsigned int DeviceSize;            															
  volatile unsigned char  MaxRdCurrentVDDMin;    							
  volatile unsigned char  MaxRdCurrentVDDMax;    							
  volatile unsigned char  MaxWrCurrentVDDMin;    						
  volatile unsigned char  MaxWrCurrentVDDMax;    						
  volatile unsigned char  DeviceSizeMul;         									
  volatile unsigned char  EraseGrSize;           												
  volatile unsigned char  EraseGrMul;            							
  volatile unsigned char  WrProtectGrSize;       								
  volatile unsigned char  WrProtectGrEnable;     							
  volatile unsigned char  ManDeflECC;            								
  volatile unsigned char  WrSpeedFact;           											
  volatile unsigned char  MaxWrBlockLen;         						
  volatile unsigned char  WriteBlockPaPartial;   				
  volatile unsigned char  Reserved3;             																
  volatile unsigned char  ContentProtectAppli;   					
  volatile unsigned char  FileFormatGrouop;      												
  volatile unsigned char  CopyFlag;              													
  volatile unsigned char  PermWrProtect;         							
  volatile unsigned char  TempWrProtect;         							
  volatile unsigned char  FileFormat;            															
  volatile unsigned char  ECC;                   																
  volatile unsigned char  CSD_CRC;               																	
  volatile unsigned char  Reserved4;             																	
} SDCard_CSD_TypeDefbac;

typedef struct        	
{
  volatile unsigned char  CSD_STRUCTURE;      
  volatile unsigned char  Reserved1;          
  volatile unsigned char  TAAC;               
  volatile unsigned char  NSAC;               
  volatile unsigned char  TRAN_SPEED;        	
  volatile unsigned short CCC;     						
  volatile unsigned char  READ_BL_LEN;        
  volatile unsigned char  READ_BL_PARTIAL;    
  volatile unsigned char  WRITE_BLK_MISALIGN; 
  volatile unsigned char  READ_BLK_MISALIGN;  
  volatile unsigned char  DSR_IMP;            
  volatile unsigned char  Reserved2;          
  volatile unsigned int C_SIZE;          		
	volatile unsigned char  Reserved3;          
  volatile unsigned char  ERASE_BLK_EN;   		
  volatile unsigned char  SECTOR_SIZE;   			
  volatile unsigned char  WP_GRP_SIZE;   			
  volatile unsigned char  WP_GRP_ENABLE;   		
	volatile unsigned char  Reserved4;					
  volatile unsigned char  R2W_FACTOR;        	
  volatile unsigned char  WRITE_BL_LEN;     	
  volatile unsigned char  WRITE_BL_PARTIAL; 	
	volatile unsigned char  Reserved5;					
  volatile unsigned char  FILE_FORMAT_GRP;   	
  volatile unsigned char  COPY;    						
  volatile unsigned char  PERM_WRITE_PROTECT;	
  volatile unsigned char  TMP_WRITE_PROTECT; 	
  volatile unsigned char  FILE_FORMAT;        
	volatile unsigned char  Reserved6;					
  volatile unsigned char  CSD_CRC;          	
  volatile unsigned char  Reserved7;        	
} SDCard_CSD_TypeDef;

typedef struct			
{
  SDCard_CSD_TypeDef		SDCard_CSD;
  SDCard_CID_TypeDef		SDCard_CID;
	SDCard_TYPE_TypeDef		SDCard_TYPE;
	SD_Error_TypeDef			SD_Error;

  unsigned int CardCapacity; 		 	
  unsigned int CardBlockSize; 	 
  unsigned short RCA;
  unsigned char Status;
} SDCard_CardInfo_TypeDef;









 

extern SDCard_Status_TypeDef	SDCard_Status;
extern SDCard_Step_TypeDef	SDCard_Step;
extern unsigned char SD_TX_Addr[512];
extern unsigned char SD_RX_Addr[512];
 


SDCard_ErrorStatus			SDCard_Configuration(SDCard_CardInfo_TypeDef *SDCard_CardInfo);																								
SDCard_ErrorStatus			SDCard_Server(void);																											
void										SDCard_GPIO_Configuration(void);																					
void 										SDCard_SPI_Configuration(char Speed);																			
void 										SDCard_DMA_Configuration(u32 *SD_TX_Addr,u32 *SD_RX_Addr,u32 BufferSize);	

SDCard_ErrorStatus			SDCard_Initialize(SDCard_CardInfo_TypeDef *SDCard_CardInfo);							
void										SDCard_EnterReady(void);																									

SDCard_ErrorStatus			SDCard_EnterIDLE(SDCard_CardInfo_TypeDef *SDCard_CardInfo);								
SDCard_ErrorStatus			SDCard_GetCID(SDCard_CardInfo_TypeDef *SDCard_CardInfo);									
SDCard_ErrorStatus			SDCard_GetCSD(SDCard_CardInfo_TypeDef *SDCard_CardInfo);									
SDCard_ErrorStatus			SDCard_GetOCR(SDCard_CardInfo_TypeDef *SDCard_CardInfo);									
SDCard_ErrorStatus			SDCard_Identification(SDCard_CardInfo_TypeDef *SDCard_CardInfo);					

void										SDCard_Select(void);																											
void										SDCard_DisSelect(void);																										
void										SDCard_DMASend(unsigned int BufferSize);																	
unsigned char 					SDCard_SendCmd(unsigned char cmd, unsigned int arg,unsigned char crc);		
SDCard_ErrorStatus			SDCard_GetResponse(unsigned char Response);																
SDCard_ErrorStatus			SDCard_RecvData(unsigned char *Rxbuf,unsigned int len);										
unsigned char						SDCard_ReadWriteByte(u8 TxData);																					
SDCard_ErrorStatus			SDCard_ReadSingleBlock(u32 addr,unsigned char *Rxbuf, u16 BlockSize);			



	























 
 
 


#line 17 "..\\..\\Driver\\WOW\\SCR\\STM32_SDCard.C"

 
 












 














 	
unsigned char SD_TX_Addr[512]={0xFF};
unsigned char SD_RX_Addr[512]={0xFF};
unsigned char	SDCard_Type=0;					
SDCard_Status_TypeDef	SDCard_Status=SDCard_Ready;
SDCard_Step_TypeDef	SDCard_Step=SDCard_DeInit;










SDCard_ErrorStatus	SDCard_Configuration(SDCard_CardInfo_TypeDef *SDCard_CardInfo)
{
	
	SDCard_ErrorStatus Errorstatus = SDCard_SUCCESS;				
	
	SDCard_GPIO_Configuration();							
	SDCard_SPI_Configuration(0);	

	SDCard_DMA_Configuration((u32*)SD_TX_Addr,(u32*)SD_RX_Addr,512);

	Errorstatus=SDCard_Initialize(SDCard_CardInfo);														
	if(Errorstatus==SDCard_SUCCESS)
	{
		if(SDCard_CardInfo->SDCard_TYPE!=SD_TYPE_ERR)
		{
			SDCard_SPI_Configuration(1);	
			return SDCard_SUCCESS;
		}
		else
		{
			return SDCard_ERROR;
		}
	}
	return	Errorstatus;
}










SDCard_ErrorStatus	SDCard_Server(void)
{
	
	SDCard_ErrorStatus Errorstatus = SDCard_SUCCESS;				

	if(DMA_GetFlagStatus(((u32)0x00000010))== SET)
	{			
		
		DMA_ClearFlag(((u32)0x00000010)); 
		
		while (SPI_I2S_GetFlagStatus(((SPI_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x3000)), ((u16)0x0080)) == SET);
		DMA_Cmd(((DMA_Channel_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x0030)),DISABLE);											
		DMA_Cmd(((DMA_Channel_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x001C)),DISABLE);											
		SDCard_Status=SDCard_Ready;
		
		SDCard_DisSelect();
		return	SDCard_SUCCESS;
	}
	else
	{
		return	SDCard_ERROR;
	}


	return	Errorstatus;
}










void SDCard_GPIO_Configuration(void)
{
	
	GPIO_InitTypeDef		GPIO_InitStructure;
	
		
	RCC_APB2PeriphClockCmd(((u32)0x00000001),	ENABLE);		
	RCC_APB2PeriphClockCmd(((u32)0x00000010),		ENABLE);		
	RCC_APB2PeriphClockCmd(((u32)0x00000004),		ENABLE);		
	RCC_APB2PeriphClockCmd(((u32)0x00000004),	ENABLE);		
	RCC_APB2PeriphClockCmd(((u32)0x00000004),	ENABLE);		
	
	
	GPIO_InitStructure.GPIO_Pin			=	((u16)0x0040);
	GPIO_InitStructure.GPIO_Mode		=	GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed		= GPIO_Speed_50MHz;
	GPIO_Init(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1000)), &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin			=	((u16)0x0020);
	GPIO_InitStructure.GPIO_Mode		=	GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed		= GPIO_Speed_50MHz;
	GPIO_Init(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0800)), &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin			=	((u16)0x0040);
	GPIO_InitStructure.GPIO_Mode		=	GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed		= GPIO_Speed_50MHz;
	GPIO_Init(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0800)), &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin			=	((u16)0x0080);
	GPIO_InitStructure.GPIO_Mode		=	GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed		= GPIO_Speed_50MHz;
	GPIO_Init(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0800)), &GPIO_InitStructure);
	






















	
}










void SDCard_SPI_Configuration(char Speed)
{
	
	SPI_InitTypeDef			SPI_InitStructure;
	RCC_APB2PeriphClockCmd(((u32)0x00001000),		ENABLE);		
	
	if(Speed==1)		
	{
		SPI_InitStructure.SPI_Direction					=	((u16)0x0000);	
		SPI_InitStructure.SPI_Mode							=	((u16)0x0104);									
		SPI_InitStructure.SPI_DataSize					=	((u16)0x0000);									
		SPI_InitStructure.SPI_CPOL							=	((u16)0x0002);										
		SPI_InitStructure.SPI_CPHA							=	((u16)0x0001);										
		SPI_InitStructure.SPI_NSS								=	((u16)0x0200);											
	
		SPI_InitStructure.SPI_BaudRatePrescaler	=	((u16)0x0030);					
		SPI_InitStructure.SPI_FirstBit					=	((u16)0x0000);									
		SPI_InitStructure.SPI_CRCPolynomial			=	0X07;															
		SPI_Init(((SPI_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x3000)),&SPI_InitStructure);													
	}
	else											
	{
		SPI_InitStructure.SPI_Direction					=	((u16)0x0000);	
		SPI_InitStructure.SPI_Mode							=	((u16)0x0104);									
		SPI_InitStructure.SPI_DataSize					=	((u16)0x0000);									
		SPI_InitStructure.SPI_CPOL							=	((u16)0x0002);										
		SPI_InitStructure.SPI_CPHA							=	((u16)0x0001);										
		SPI_InitStructure.SPI_NSS								=	((u16)0x0200);											
	
		SPI_InitStructure.SPI_BaudRatePrescaler	=	((u16)0x0038);				
		SPI_InitStructure.SPI_FirstBit					=	((u16)0x0000);									
		SPI_InitStructure.SPI_CRCPolynomial			=	0X07;															
		SPI_Init(((SPI_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x3000)),&SPI_InitStructure);													
	}
	*((volatile unsigned long *)((((((((u32)0x40000000) + 0x10000) + 0x1000)+12) & 0xF0000000)+0x2000000+(((((((u32)0x40000000) + 0x10000) + 0x1000)+12) &0xFFFFF)<<5)+(6<<2))))=1;			
	SPI_Cmd(((SPI_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x3000)), ENABLE);				
}












void	SDCard_DMA_Configuration(u32 *SD_TX_Addr,u32 *SD_RX_Addr,u32 BufferSize)
{
	
	DMA_InitTypeDef			DMA_Initstructure;
	NVIC_InitTypeDef		NVIC_Initstructure;
	
	
	DMA_Initstructure.DMA_PeripheralBaseAddr	=	(u32)(&((SPI_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x3000))->DR);								
	DMA_Initstructure.DMA_MemoryBaseAddr			=	(u32)SD_TX_Addr;								
	DMA_Initstructure.DMA_DIR									= ((u32)0x00000010);					
	DMA_Initstructure.DMA_BufferSize					= BufferSize; 										
	DMA_Initstructure.DMA_PeripheralInc				= ((u32)0x00000000);			
	DMA_Initstructure.DMA_MemoryInc						=	((u32)0x00000080);						
	DMA_Initstructure.DMA_PeripheralDataSize	= ((u32)0x00000000);		
	DMA_Initstructure.DMA_MemoryDataSize			= ((u32)0x00000000);				
	DMA_Initstructure.DMA_Mode								= ((u32)0x00000000);								
	DMA_Initstructure.DMA_Priority						= ((u32)0x00002000); 							
	DMA_Initstructure.DMA_M2M									= ((u32)0x00000000);								
	DMA_Init(((DMA_Channel_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x0030)),&DMA_Initstructure);																	

	
	DMA_Initstructure.DMA_PeripheralBaseAddr	=	(u32)(&((SPI_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x3000))->DR);								
	DMA_Initstructure.DMA_MemoryBaseAddr     	=	(u32)SD_RX_Addr;								
	DMA_Initstructure.DMA_DIR									=	((u32)0x00000000);					
	DMA_Initstructure.DMA_BufferSize					= BufferSize; 										
	DMA_Initstructure.DMA_PeripheralInc				= ((u32)0x00000000);			
	DMA_Initstructure.DMA_MemoryInc						=	((u32)0x00000080);						
	DMA_Initstructure.DMA_PeripheralDataSize	= ((u32)0x00000000);		
	DMA_Initstructure.DMA_MemoryDataSize			= ((u32)0x00000000);				
	DMA_Initstructure.DMA_Mode								= ((u32)0x00000000);								
	DMA_Initstructure.DMA_Priority						= ((u32)0x00002000); 							
	DMA_Initstructure.DMA_M2M									= ((u32)0x00000000);								
	DMA_Init(((DMA_Channel_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x001C)),&DMA_Initstructure);																	
	
	
	NVIC_Initstructure.NVIC_IRQChannel = ((u8)0x0C);       				
	NVIC_Initstructure.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_Initstructure.NVIC_IRQChannelSubPriority = 1; 													
	NVIC_Initstructure.NVIC_IRQChannelCmd = ENABLE;        											
	NVIC_Init(&NVIC_Initstructure);

	
	
	
	
	DMA_ITConfig(((DMA_Channel_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x001C)),((u32)0x00000002),ENABLE);						
	
	SPI_I2S_DMACmd(((SPI_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x3000)), ((u16)0x0002), ENABLE);				
	SPI_I2S_DMACmd(((SPI_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x3000)), ((u16)0x0001), ENABLE);				

	
	DMA_Cmd(((DMA_Channel_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x001C)),DISABLE);	
	DMA_Cmd(((DMA_Channel_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x0030)),DISABLE);
}











SDCard_ErrorStatus	SDCard_Initialize(SDCard_CardInfo_TypeDef *SDCard_CardInfo)
{







































































	
		
	SDCard_ErrorStatus Errorstatus = SDCard_SUCCESS;				




	SDCard_Select();									
	
	SDCard_EnterReady();
	
	if(SDCard_Step==SDCard_DeInit)
	{
	}
	
		Errorstatus=SDCard_EnterIDLE(SDCard_CardInfo);	
	
	if(Errorstatus!=SDCard_SUCCESS)										
		return SDCard_ERROR;					
	
	
	
	
	
	
	
	
	
	Errorstatus=SDCard_Identification(SDCard_CardInfo);
	if(Errorstatus!=SDCard_SUCCESS)											
	{
		SDCard_DisSelect();									
		return SDCard_ERROR;															
	}
	SDCard_GetCSD(SDCard_CardInfo);											
	SDCard_GetCID(SDCard_CardInfo);											
	
	
#line 486 "..\\..\\Driver\\WOW\\SCR\\STM32_SDCard.C"
	SDCard_DisSelect();									
	return	SDCard_SUCCESS;
}










void	SDCard_DisSelect(void)
{
	*((volatile unsigned long *)((((((((u32)0x40000000) + 0x10000) + 0x1000)+12) & 0xF0000000)+0x2000000+(((((((u32)0x40000000) + 0x10000) + 0x1000)+12) &0xFFFFF)<<5)+(6<<2))))=1;								

	SDCard_ReadWriteByte(0xff);		
}










void	SDCard_Select(void)
{
	*((volatile unsigned long *)((((((((u32)0x40000000) + 0x10000) + 0x1000)+12) & 0xF0000000)+0x2000000+(((((((u32)0x40000000) + 0x10000) + 0x1000)+12) &0xFFFFF)<<5)+(6<<2))))=0;												
}







void SDCard_DMASend(unsigned int BufferSize)
{
	((DMA_Channel_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x0030))->CNDTR =BufferSize;										
	((DMA_Channel_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x0030))->CMAR =(u32)SD_TX_Addr;					
	
	((DMA_Channel_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x001C))->CNDTR =BufferSize;										
	((DMA_Channel_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x001C))->CMAR =(u32)SD_RX_Addr;					
	
	DMA_Cmd(((DMA_Channel_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x0030)),ENABLE);											
	DMA_Cmd(((DMA_Channel_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x001C)),ENABLE);											
}






































SDCard_ErrorStatus SDCard_GetResponse(unsigned char Response)
{
	
	SDCard_ErrorStatus Errorstatus = SDCard_SUCCESS;				
	
	unsigned int Count=0xFFFF;		


	




	while ((SDCard_ReadWriteByte(0XFF)!=Response)&&Count--);	

	if (Count==0)
	{
		Errorstatus = SDCard_ERROR;		
	}		
	else
	{
		Errorstatus = SDCard_SUCCESS;	
	}


	
	return(Errorstatus);
}












SDCard_ErrorStatus SDCard_RecvData(unsigned char	*Rxbuf,unsigned int len)
{
	
	SDCard_ErrorStatus Errorstatus = SDCard_SUCCESS;		
	
	
	SDCard_Select();																		
	
	
	if(SDCard_GetResponse(0xFE)==SDCard_ERROR)
	{
		
		SDCard_DisSelect();	
		return SDCard_ERROR;
	}

	while(len--)
	{
		*Rxbuf=SDCard_ReadWriteByte(0xFF);
		Rxbuf++;
	}
	
	SDCard_ReadWriteByte(0xFF);
	SDCard_ReadWriteByte(0xFF);
	
	
	SDCard_DisSelect();
	
	return SDCard_SUCCESS;		

	
	return Errorstatus;
}










void	SDCard_EnterReady(void)
{
	
	u8 retry=0;													
	

	
	
	for(retry=0;retry<=20;retry++)
	{
		SDCard_ReadWriteByte(0XFF);
	}
	

}










SDCard_ErrorStatus	SDCard_EnterIDLE(SDCard_CardInfo_TypeDef *SDCard_CardInfo)
{
	

	unsigned char retry=20;							
	unsigned char r1=0xFF;							


	
	
	

	SDCard_SendCmd(0,0x00,0x95);
#line 711 "..\\..\\Driver\\WOW\\SCR\\STM32_SDCard.C"
	
	return	SDCard_SUCCESS;	
}










SDCard_ErrorStatus	SDCard_Identification(SDCard_CardInfo_TypeDef *SDCard_CardInfo)
{	
	
	
	
	
	
	
	
	
	
	SDCard_ErrorStatus Errorstatus = SDCard_SUCCESS;				
	unsigned char retry=0;							
	unsigned char r1=0xFF;							
	


	
	
	retry=20;
	r1=0xFF;
	do
	{

		r1	=	SDCard_SendCmd(8,0x01AA,0x87);

	}while((r1!=0x01)&&retry--);
	
	if(r1==0x01)
	{

		SDCard_ReadWriteByte(0xFF);
		SDCard_ReadWriteByte(0xFF);
		SDCard_ReadWriteByte(0xFF);
		SDCard_ReadWriteByte(0xFF);

	}
	else
	{
		SDCard_CardInfo->SD_Error	=	SD_ILLEGAL_CMD;					
		return	SDCard_ERROR;																
	}
	
	
	if(r1==0x01)				
	{	
		
		retry=100;
		r1=0xFF;
		do
		{
			SDCard_SendCmd(55,0x00,0x01);
			r1	=	SDCard_SendCmd(41,0X40000000,0x01);
		}while((r1!=0x00)&&retry--);		
		if(r1==0x00)		
		{
			
			Errorstatus=SDCard_GetOCR(SDCard_CardInfo);

			if(Errorstatus==SDCard_SUCCESS)
			return SDCard_SUCCESS;																	
		}
		else		
		{
			SDCard_CardInfo->SDCard_TYPE	=	SD_TYPE_V2;			
			SDCard_DisSelect();									
			return	SDCard_ERROR;																
		}
	}	
	
	else
	{
		
		retry=100;
		r1=0xFF;
		do
		{
			SDCard_SendCmd(55,0x00,0x01);
			r1	=	SDCard_SendCmd(41,0X40000000,0x01);
		}while((r1!=0x00)&&retry--);
		if(r1==0x00)		
		{
			SDCard_GetOCR(SDCard_CardInfo);
		}
		
		else
		{
			retry=100;
			r1=0xFF;
			do
			{
				SDCard_SendCmd(1,0x00,0x00);
			}while((r1!=0x00)&&retry--);
			if(r1==0x00)		
			{
				SDCard_CardInfo->SDCard_TYPE	=	SD_TYPE_MMC;			
			}
			else						
			{
				SDCard_CardInfo->SDCard_TYPE	=	SD_TYPE_ERR;			

				return	SDCard_ERROR;															
			}
		}
	}
	
	return SDCard_SUCCESS;																	
}











unsigned char	SDCard_ReadWriteByte(u8 TxData)
{
	
	unsigned short retry=0;													
	
	while (SPI_I2S_GetFlagStatus(((SPI_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x3000)), ((u16)0x0080)) == SET);	






	
	SPI_I2S_SendData(((SPI_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x3000)), TxData);				
	

	retry=0;	
	while(SPI_I2S_GetFlagStatus(((SPI_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x3000)), ((u16)0x0001)) == RESET)		
	{
		retry++;
		if(retry>1000)
			return 0;
	}
	while (SPI_I2S_GetFlagStatus(((SPI_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x3000)), ((u16)0x0080)) == SET);
	
	return SPI_I2S_ReceiveData(((SPI_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x3000))); 			
}













unsigned char SDCard_SendCmd(unsigned char cmd, unsigned int arg,unsigned char crc)
{
	
	unsigned char r1;				
	unsigned char retry=0;	
	


#line 905 "..\\..\\Driver\\WOW\\SCR\\STM32_SDCard.C"
	
	SDCard_ReadWriteByte(cmd | 0x40);	
	SDCard_ReadWriteByte(arg >> 24);	
	SDCard_ReadWriteByte(arg >> 16);	
	SDCard_ReadWriteByte(arg >> 8);		
	SDCard_ReadWriteByte(arg);	  
	SDCard_ReadWriteByte(crc);				
	
	if(cmd==12)
		SDCard_ReadWriteByte(0xff);
	
	r1=0xFF;
	for(retry=0;retry<0x1F&&(r1&0x80);retry++)
	{
		r1=SDCard_ReadWriteByte(0xFF);
	}







	


	
	return r1;	
}












SDCard_ErrorStatus SDCard_GetCID(SDCard_CardInfo_TypeDef *SDCard_CardInfo)
{
	
	SDCard_ErrorStatus Errorstatus = SDCard_SUCCESS;				
	SDCard_CID_TypeDef	SDCard_CID;
	unsigned char R1;																		
	unsigned char R2;																		
	unsigned char	CID[20]={0xFF};
	unsigned char i;																		


	
	R1=SDCard_SendCmd(10,0,0x01);
	
	if(R1==0x00)
	{


		
		R2=SDCard_ReadWriteByte(0xFF);		
		
		for(i=0;i<19;i++)
		{
			CID[i]=SDCard_ReadWriteByte(0xFF);
		}


		
		SDCard_CID.ManufacturerID=CID[0];
		SDCard_CID.OEM_AppliID=(((CID[1]&0X00FF)<<8)|(CID[2]&0X00FF));


		SDCard_CID.ProdRev=CID[8];
		SDCard_CID.ProdSN=((CID[9]&0X000000FF<<24)|(CID[10]&0X000000FF<<16)|(CID[11]&0X000000FF<<8)|(CID[12]&0X000000FF));
		SDCard_CID.ManufactDate=((CID[13]&0X000F<<8)|(CID[14]&0X00FF));
		SDCard_CID.CID_CRC=(CID[15]&0xFE)>>1;
		
		SDCard_CID.ProdName[0]=CID[3];
		SDCard_CID.ProdName[1]=CID[4];
		SDCard_CID.ProdName[2]=CID[5];
		SDCard_CID.ProdName[3]=CID[6];
		SDCard_CID.ProdName[4]=CID[7];
		
		
		SDCard_CardInfo->SDCard_CID=SDCard_CID;
		
		return	SDCard_SUCCESS;
	}
	else
	{
		return	SDCard_ERROR;
	}	
	
	return(Errorstatus);
}










SDCard_ErrorStatus SDCard_GetCSD(SDCard_CardInfo_TypeDef *SDCard_CardInfo)
{
	
	SDCard_ErrorStatus	Errorstatus = SDCard_SUCCESS;		
	SDCard_CSD_TypeDef	SDCard_CSD;
	unsigned char R1;																		
	unsigned char R2;																		
	unsigned char	CSD[20]={0xFF};
	unsigned char i;																		
	
	R1=SDCard_SendCmd(9,0,0x01);
	
	if(R1==0x00)
	{


		
		R2=SDCard_ReadWriteByte(0xFF);		
		
		for(i=0;i<19;i++)
		{
			CSD[i]=SDCard_ReadWriteByte(0xFF);
		}		


		
		SDCard_CSD.CSD_STRUCTURE			=	(CSD[0]>>6)&0x03;			
		SDCard_CSD.TAAC								=	CSD[1];														
		SDCard_CSD.NSAC								=	CSD[2];													
		SDCard_CSD.TRAN_SPEED					=	CSD[3];														
		SDCard_CSD.CCC								=	((0X0FFF&CSD[4])<<4)|((CSD[5]>>4)&0X0F);		
		SDCard_CSD.READ_BL_LEN				=	CSD[5]&0x0F;				
		SDCard_CSD.READ_BL_PARTIAL		=	CSD[6]>>7;				
		SDCard_CSD.WRITE_BLK_MISALIGN	=	(CSD[6]&0x40>>6);	
		SDCard_CSD.READ_BLK_MISALIGN	=	(CSD[6]&0x20>>5);	
		SDCard_CSD.DSR_IMP						=	(CSD[6]&0x10>>4);		
		SDCard_CSD.C_SIZE							=	((CSD[7]&0x003F)<<16)|((CSD[8]&0x00FF)<<8)|((CSD[9]&0x00FF));
		SDCard_CSD.ERASE_BLK_EN				=	CSD[10]&40>>6;
		SDCard_CSD.SECTOR_SIZE				=	(CSD[10]&0x3F)<<1|(CSD[11]&0x80)>>7;
		SDCard_CSD.WP_GRP_SIZE				=	CSD[11]&0x7F;
		SDCard_CSD.WP_GRP_ENABLE			=	(CSD[12]&0x80)>>7;
		SDCard_CSD.R2W_FACTOR					=	(CSD[12]&0x1C)>>2;
		SDCard_CSD.WRITE_BL_LEN				=	(CSD[12]&0x03)<<2|(CSD[13]&0xC0)>>6;
		SDCard_CSD.WRITE_BL_PARTIAL		=	(CSD[13]&0x20)>>5;
		SDCard_CSD.FILE_FORMAT_GRP		=	(CSD[14]&0x80)>>7;
		SDCard_CSD.COPY								=	(CSD[14]&0x40)>>6;
		SDCard_CSD.PERM_WRITE_PROTECT	=	(CSD[14]&0x20)>>5;
		SDCard_CSD.TMP_WRITE_PROTECT	=	(CSD[14]&0x10)>>4;
		SDCard_CSD.FILE_FORMAT				=	(CSD[14]&0x0C)>>2;
		SDCard_CSD.CSD_CRC						=	(CSD[15]&0xFE)>>1;	

		
		SDCard_CardInfo->SDCard_CSD=SDCard_CSD;
		
		
		SDCard_CardInfo->CardCapacity=((SDCard_CSD.C_SIZE+1)*512)/1024;		
		
		return	SDCard_SUCCESS;
	}

	else
	{
		return	SDCard_ERROR;
	}
	
	return(Errorstatus);
}











SDCard_ErrorStatus	SDCard_GetOCR(SDCard_CardInfo_TypeDef *SDCard_CardInfo)
{
	unsigned char r3[4]={0xFF};
	
	SDCard_SendCmd(58,0x00,0x00);
	

	r3[0]	=	SDCard_ReadWriteByte(0xFF);
	r3[1]	=	SDCard_ReadWriteByte(0xFF);
	r3[2]	=	SDCard_ReadWriteByte(0xFF);
	r3[3]	=	SDCard_ReadWriteByte(0xFF);

	
	if((r3[0]&0x40)==0x40)	
		SDCard_CardInfo->SDCard_TYPE=SD_TYPE_V2HC;					
	else
		SDCard_CardInfo->SDCard_TYPE=SD_TYPE_V2MC;					
	return	SDCard_SUCCESS;						
}











SDCard_ErrorStatus SDCard_ReadSingleBlock(u32 addr,unsigned char *Rxbuf, u16 BlockSize)
{
	
	SDCard_ErrorStatus	Errorstatus = SDCard_SUCCESS;		

	unsigned char retry=0;
	unsigned char R1;																		
	unsigned char R2;																		
	



	if(SDCard_Status!=SDCard_DMA_EN)								
	{
		
			SDCard_Select();																		
		
		retry=100;
		do
		{
			R1=SDCard_SendCmd(17,addr,0x01);
		}while(R1!=0x00&&retry--);
		
		if(retry==0x00)			
		{
			
			return	SDCard_ERROR;	
		}
		
		else
		{
			
			
			
			if(SDCard_GetResponse(0xFE)==SDCard_ERROR)
			{
				
				SDCard_DisSelect();	
				return SDCard_ERROR;
			}
				memset(SD_TX_Addr,0XFF,BlockSize);						
				memset(SD_RX_Addr,0XFF,BlockSize);						
				
				Rxbuf=SD_RX_Addr;		
				
				((DMA_Channel_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x0030))->CNDTR =BlockSize+5;						
				((DMA_Channel_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x0030))->CMAR =(u32)SD_TX_Addr;		
				
				((DMA_Channel_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x001C))->CNDTR =BlockSize+5;						
				((DMA_Channel_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x001C))->CMAR =(u32)SD_RX_Addr;		
				
				DMA_Cmd(((DMA_Channel_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x0030)),ENABLE);					
				DMA_Cmd(((DMA_Channel_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x001C)),ENABLE);					
				
				
				SDCard_Status=SDCard_DMA_EN;
				
				return SDCard_SUCCESS;									
			}
	}
	else
	{		
		return	SDCard_ERROR;
	}
#line 1202 "..\\..\\Driver\\WOW\\SCR\\STM32_SDCard.C"
	
	return	SDCard_SUCCESS;						
}


















































































 


















































































































































 


















 



























































































 


















































































































































































































 



































































 





























 
























 








































































































































































 















































































































































































































 












































































































































































































































 


















































































































































































































































































 






















 
























 

































































































 






































 





























































































































 







































































































































 































 








































 





















































































































































 































 







































 









































































 





















































































































 

































































































































































 
















































































































 




















 

























 



































 



































 
 




























































































































































































































































































































































































 


 
 
 


