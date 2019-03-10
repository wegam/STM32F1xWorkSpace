#line 1 "..\\..\\Driver\\Components\\SCR\\LCD.c"







 
#line 1 "..\\..\\Driver\\Components\\INC\\LCD.H"







 



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

 
 
 



 
#line 13 "..\\..\\Driver\\Components\\INC\\LCD.H"
#line 1 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_gpio.h"














 

 



 
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



 
#line 14 "..\\..\\Driver\\Components\\INC\\LCD.H"
#line 1 "..\\..\\Driver\\Components\\INC\\GT32L32M0180.H"













 




#line 20 "..\\..\\Driver\\Components\\INC\\GT32L32M0180.H"
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



 
#line 21 "..\\..\\Driver\\Components\\INC\\GT32L32M0180.H"
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



 
#line 22 "..\\..\\Driver\\Components\\INC\\GT32L32M0180.H"
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



 
#line 23 "..\\..\\Driver\\Components\\INC\\GT32L32M0180.H"
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



 
#line 24 "..\\..\\Driver\\Components\\INC\\GT32L32M0180.H"




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



 

#line 29 "..\\..\\Driver\\Components\\INC\\GT32L32M0180.H"
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



 

#line 30 "..\\..\\Driver\\Components\\INC\\GT32L32M0180.H"
#line 1 "..\\..\\Library\\C\\stdarg.h"
 
 
 





 










#line 27 "..\\..\\Library\\C\\stdarg.h"








 

 
 
#line 57 "..\\..\\Library\\C\\stdarg.h"
    typedef struct __va_list { void *__ap; } va_list;

   






 


   










 


   















 




   

 


   




 



   





 







#line 138 "..\\..\\Library\\C\\stdarg.h"



#line 147 "..\\..\\Library\\C\\stdarg.h"

 

#line 31 "..\\..\\Driver\\Components\\INC\\GT32L32M0180.H"
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





 
#line 32 "..\\..\\Driver\\Components\\INC\\GT32L32M0180.H"


#line 1 "..\\..\\Driver\\WOW\\INC\\STM32_SPI.H"













 





#line 21 "..\\..\\Driver\\WOW\\INC\\STM32_SPI.H"
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









































































































#line 35 "..\\..\\Driver\\Components\\INC\\GT32L32M0180.H"

 














typedef enum
{
	ASCII_BaseAddr_None					=	(u32)0x000000,			
	
	ASCII_BaseAddr_zf5x7				=	(u32)0x100000,			
	ASCII_BaseAddr_zfs7x8				=	(u32)0x100300,			
	ASCII_BaseAddr_zfm7x8				=	(u32)0x100600,			
	ASCII_BaseAddr_zf6x12				=	(u32)0x100900,			
	ASCII_BaseAddr_zfs8x16			=	(u32)0x100D80,			
	ASCII_BaseAddr_zfm8x16			=	(u32)0x101580,			
	ASCII_BaseAddr_zf12x24			=	(u32)0x101B80,			
	ASCII_BaseAddr_zfs16x32			=	(u32)0x102D80,			
	ASCII_BaseAddr_zfm16x32			=	(u32)0x104580,			
	
	ASCII_BaseAddr_ar12					=	(u32)0x105D80,			
	ASCII_BaseAddr_ar16					=	(u32)0x106740,			
	ASCII_BaseAddr_ar24					=	(u32)0x107400,			
	ASCII_BaseAddr_ar32					=	(u32)0x108FC0,			
	
	ASCII_BaseAddr_TNR12				=	(u32)0x10C080,			
	ASCII_BaseAddr_TNR16				=	(u32)0x10CA50,			
	ASCII_BaseAddr_TNR24				=	(u32)0x10D740,			
	ASCII_BaseAddr_TNR32				=	(u32)0x10F340,			
	
	Digital_BaseAddr_sz14x28		=	(u32)0x112400,			
	Digital_BaseAddr_sz20x40		=	(u32)0x112748,			
	Digital_BaseAddr_sz28				=	(u32)0x112CE8,			
	Digital_BaseAddr_sz40				=	(u32)0x113396,			
	
	GB18030_BaseAddr_zf12x12		=	(u32)0x113D0E,			
	GB18030_BaseAddr_zf16x16		=	(u32)0x194FDE,			
	GB18030_BaseAddr_zf24x24		=	(u32)0x2743DE,			
	GB18030_BaseAddr_zf32x32		=	(u32)0x47AE10,			
	
	GB18030_BaseAddr_hz12x12		=	(u32)0x113D0E,			
	GB18030_BaseAddr_hz16x16		=	(u32)0x194FDE,			
	GB18030_BaseAddr_hz24x24		=	(u32)0x2743DE,			
	GB18030_BaseAddr_hz32x32		=	(u32)0x47AE10,			
	
	Unicode_To_GBK_BaseAddr			=	(u32)0x46A90E,			
	BIG5_To_GBK_BaseAddr				=	(u32)0x7F1E10,			
	
	BarCode_BaseAddr_12x27			=	(u32)0x478FD2,			
	BarCode_BaseAddr_16x20			=	(u32)0x479C7A,			
	
	AntennaCode_BaseAddr_12X12	=	(u32)0x47AD32,			
	BatteryCode_BaseAddr_12X12	=	(u32)0x47ADAA,			
	
	Reserved_BaseAddr_LSB				=	(u32)0x7F8760,			
	Reserved_BaseAddr_MSB				=	(u32)0x7FFFFF,			
}	GT32L32BaseAddrTypeDef;		

typedef enum
{
	GT32L32_Error_None					=	(u8)0x00,			
	GT32L32_Error_Addr					=	(u8)0x01,			
	GT32L32_Error_ASCIICode			=	(u8)0x02,			
	GT32L32_Error_HzEmp					=	(u8)0x03,			
	
}	GT32L32FlagDef;		

typedef struct       
{

	unsigned long	Address;						


} GT32L32DataDef;

typedef struct      _GT32L32 
{
	SPIDef								SPI;
	GT32L32DataDef				Data;	
	GT32L32FlagDef				Flag;			
}GT32L32Def;			
 





 

void GT32L32_Initialize(SPIDef *SpiPort);  
u8 GT32L32_ReadStatus(GT32L32Def *pInfo);			
void GT32L32_ChipErase(GT32L32Def *pInfo);		



u32 GT32L32_GetAntennaCode(u8	NUM,u8 *GetBuffer);						
u32 GT32L32_GetBatteryCode(u8	NUM,u8 *GetBuffer);						
u16	GT32L32_GetCode(u8 font,u16 word,u8 *ReadBuffer);		








 
 
 


#line 15 "..\\..\\Driver\\Components\\INC\\LCD.H"

#line 1 "..\\..\\Driver\\WOW\\INC\\STM32_PWM.H"













 







#line 1 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_tim.h"














 

 



 
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
#line 24 "..\\..\\Driver\\WOW\\INC\\STM32_PWM.H"
#line 25 "..\\..\\Driver\\WOW\\INC\\STM32_PWM.H"
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



#line 17 "..\\..\\Driver\\Components\\INC\\LCD.H"










typedef enum
{
	Draw_Rotate_0D = 0,
	Draw_Rotate_90D,
	Draw_Rotate_180D,
	Draw_Rotate_270D,
} eRotate;


typedef struct	_LCDPort
{
	
	GPIO_TypeDef* 	sBL_PORT;			
	unsigned short 	sBL_Pin;				
	
	
	GPIO_TypeDef* 	sRD_PORT;							
	unsigned short 	sRD_Pin;							
	
	
	GPIO_TypeDef* 	sREST_PORT;						
	unsigned short 	sREST_Pin;						
	
	
	GPIO_TypeDef* 	sDC_PORT;							
	unsigned short 	sDC_Pin;							
	
	
	GPIO_TypeDef* 	sWR_PORT;							
	unsigned short 	sWR_Pin;							
	
	
	GPIO_TypeDef* 	sCS_PORT;							
	unsigned short 	sCS_Pin;							
	
	
	GPIO_TypeDef* 	sTE_PORT;							
	unsigned short 	sTE_Pin;							
	
	
	GPIO_TypeDef* 	sDATABUS_PORT;				
	unsigned short 	sDATABUS_Pin;					

}LCDPortDef;
typedef struct	_LCDData
{
	unsigned short	MaxH;						
	unsigned short 	MaxV;						
	unsigned short	HSX;						
	unsigned short 	HEX;						
	unsigned short	VSY;						
	unsigned short 	VEY;						
	unsigned short	HXA;						
	unsigned short 	VYA;						
	unsigned short 	PColor;					
	unsigned short 	BColor;					
  unsigned long   FsmcDataAddr;  
  unsigned long   FsmcRegAddr;   
}LCDDataDef;
typedef struct	_LCDFlag		
{
	eRotate	Rotate;						
}LCDFlagDef;
typedef struct _DisplayDriver
{
	
	void ( *WriteAddress )( unsigned short HSX,unsigned short HSY,unsigned short HEX,unsigned short HEY);
	void ( *WriteIndex)(unsigned short Index);
  void ( *WriteData)(unsigned short Data);
  void ( *WriteCommand)(unsigned short Index,unsigned short Command);
	
	void ( *LcdBackLightOn )(void);
  void ( *LcdBackLightOff )(void);
	
	
	void ( *PowerOn )(void);
	void ( *PowerOff )(void);
	void ( *DispOff )(void);	 
	
	void ( *DrawDot)(unsigned short HSX,unsigned short HSY,unsigned short color);		
	void ( *DrawLine)(u16 x1,u16 y1,u16 x2,u16 y2,u16 color);						
	void ( *DrawCircle)(u16 x1,u16 y1, u16 R, u8 Filled, u16 color );		
	void ( *DrawRectangle)(u16 x1,u16 y1,u16 x2,u16 y2,u16 color);				
	
	void ( *Fill )(u16 xsta,u16 ysta,u16 xend,u16 yend,u16 color);				
	void ( *Clean)(u16 Color);								
	void ( *SetBackground)(u16 BackColor );
	
	
	void ( *ShowChar)(u16 x,u16 y,u8 font,u16 color,u8 num,u8 *Buffer);	  
	void ( *ShowWord)(u16 x,u16 y,u8 font,u16 color,u8 num,u8 *Buffer);	  

}DisplayDriverDef;
typedef struct	_LCD
{
	LCDPortDef				Port;
	LCDDataDef				Data;
	LCDFlagDef				Flag;
	DisplayDriverDef	Display;
	GT32L32Def				GT32L32;
}LCDDef;

typedef struct	_stLCDScroll
{
	unsigned short	startx;				
	unsigned short	starty;				
	unsigned short	color;				
	unsigned short	length;				
	unsigned short	runxstart;		
	unsigned char		font;					
	unsigned char		buffer[100];	
	unsigned long*	nextlist;			
}stLCDScroll;

extern LCDDef *LCDSYS;			



#line 159 "..\\..\\Driver\\Components\\INC\\LCD.H"


































#line 215 "..\\..\\Driver\\Components\\INC\\LCD.H"



unsigned short LCD_Initialize(LCDDef *pInfo);
void LCDFsmc_Initialize(LCDDef *pInfo);
void LCD_DisplayServer(void);

void LCD_ShowAntenna(u16 x,u16 y,u8 Num,u16 PenColor);   
void LCD_ShowBattery(u16 x,u16 y,u8 Num,u16 PenColor); 	
void LCD_Show(u16 x,u16 y,u8 font,u16 PenColor,u8 num,u8 *Buffer);	
void LCD_ShowScroll(stLCDScroll	*ScrollBuff);	
void LCD_ShowHex(u16 x,u16 y,u8 font,u16 color,u8 num,u8 bitnum,u8 *Buffer);    
unsigned int LCD_Printf(u16 x,u16 y,u8 font,u16 color,const char *format,...);  
unsigned int LCD_PrintfScroll(u16 x,u16 y,u8 font,u16 color,const char *format,...);  
void LCD_ShowBMP(u16 xsta,u16 ysta,u16 xend,u16 yend,u16 Length,u8 *RGBBuffer);    
unsigned  short RGB888toRGB565(u8 *RGB888);


void LCD_Reset(void);

void LCD_WriteIndex( unsigned short Index );		
void LCD_WriteData(u16 Data);										
void LCDFsmc_WriteIndex(unsigned short Index);	
void LCDFsmc_WriteData(unsigned short Data);		
void LCD_WriteCommand(unsigned short index,unsigned short Command);		
u16 LCD_ReadData( unsigned short Index );				

void LCD_WriteRegister(unsigned	short	Index,unsigned short Data);
unsigned short LCD_ReadRegister(unsigned	short	Index);

void LCD_Clean(u16 COLOR);	
void LCD_DrawDot(unsigned short HSX,unsigned short HSY,unsigned short color);		
void LCD_DrawLine(u16 x1,u16 y1,u16 x2,u16 y2,u16 color);						
void LCD_DrawCircle(u16 x1,u16 y1, u16 R, u8 Filled, u16 color );		
void LCD_DrawRectangle(u16 x1,u16 y1,u16 x2,u16 y2,u16 color);				

void LCD_Fill(u16 xsta,u16 ysta,u16 xend,u16 yend,u16 color);				
void LCD_SetBackground(u16 BackColor );
void LCD_ShowChar(u16 x,u16 y,u8 font,u16 color,u8 num,u8 *Buffer);	  
void LCD_ShowWord(u16 x,u16 y,u8 font,u16 color,u8 num,u8 *Buffer);	  
unsigned short LCD_GetDispCodeBuffer(u8 font,u16 word,u8 *ReadBuffer);	


void LCD_DelayuS(u32 xuS);
void LCD_DelaymS(u32 xmS);
void LCD_DelayS(u32 xS);

 
#line 10 "..\\..\\Driver\\Components\\SCR\\LCD.c"

#line 1 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_fsmc.h"














 

 



 
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



 
#line 12 "..\\..\\Driver\\Components\\SCR\\LCD.c"

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










#line 14 "..\\..\\Driver\\Components\\SCR\\LCD.c"
#line 15 "..\\..\\Driver\\Components\\SCR\\LCD.c"
#line 1 "..\\..\\Driver\\WOW\\INC\\STM32_SYSTICK.H"













 





#line 1 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_systick.h"














 

 



 
#line 23 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_systick.h"

 
 
 






 








 










 
 
void SysTick_CLKSourceConfig(u32 SysTick_CLKSource);
void SysTick_SetReload(u32 Reload);
void SysTick_CounterCmd(u32 SysTick_Counter);
void SysTick_ITConfig(FunctionalState NewState);
u32 SysTick_GetCounter(void);
FlagStatus SysTick_GetFlagStatus(u8 SysTick_FLAG);



 
#line 21 "..\\..\\Driver\\WOW\\INC\\STM32_SYSTICK.H"


void SysTick_Configuration(unsigned long Time);	
void SysTick_Server(void);											



void SysTick_DeleyuS(unsigned int Time);				
void SysTick_DeleymS(unsigned int Time);				
void SysTick_DeleyS(unsigned int Time);					



void DeleyuS(unsigned int Time);								
	



#line 16 "..\\..\\Driver\\Components\\SCR\\LCD.c"
#line 1 "..\\..\\Driver\\Components\\INC\\font.h"









  
extern unsigned char code_asc2_1608[1520];




extern volatile unsigned char code_ascii_1608[127][16];
extern  unsigned char ascii_code0_9748[583];

extern volatile unsigned char code_nBitmapDot[598];                  





	 
	 



#line 17 "..\\..\\Driver\\Components\\SCR\\LCD.c"
#line 18 "..\\..\\Driver\\Components\\SCR\\LCD.c"
#line 19 "..\\..\\Driver\\Components\\SCR\\LCD.c"
#line 20 "..\\..\\Driver\\Components\\SCR\\LCD.c"
#line 21 "..\\..\\Driver\\Components\\SCR\\LCD.c"

#line 1 "..\\..\\Driver\\Components\\INC\\R61509V.h"







 




#line 14 "..\\..\\Driver\\Components\\INC\\R61509V.h"
#line 15 "..\\..\\Driver\\Components\\INC\\R61509V.h"











 



#line 83 "..\\..\\Driver\\Components\\INC\\R61509V.h"




unsigned short R61509V_Initialize(void*	pInfo);


void R61509V_Reset(void);
unsigned short R61509V_ReadData(void);
unsigned short R61509V_ReadRegister(unsigned	short	Addr);

void R61509V_WriteData(unsigned	short	Data);
void R61509V_WriteIndex(unsigned	short	Index);
void R61509V_WriteAddr(unsigned	short	Addr);
void R61509V_WriteRegister(unsigned	short	Addr,unsigned short Data);		
void R61509V_WriteCommand(unsigned	short	Index,unsigned short Cmd);


void R61509V_WriteGRAM(unsigned	short* RAM,unsigned long length);				
void R61509V_ReadGRAM(unsigned	short* RAM,unsigned long length);


void R61509V_PowerOn(void);					
void R61509V_PowerOff( void );		
void R61509V_DispOff( void );			
void R61509V_SetWindowAddress(unsigned short x1,unsigned short y1,unsigned short x2,unsigned short y2);


void R61509V_DrawDot(unsigned short HSX,unsigned short HSY,unsigned short color);		
void R61509V_DrawLine(u16 x1,u16 y1,u16 x2,u16 y2,u16 color);						
void R61509V_DrawCircle(u16 x1,u16 y1, u16 R, u8 Filled, u16 color );		
void R61509V_DrawRectangle(u16 x1,u16 y1,u16 x2,u16 y2,u16 color);

void R61509V_Fill(u16 xsta,u16 ysta,u16 xend,u16 yend,u16 color);				
void R61509V_Clean(u16 Color);	
void R61509V_SetBackground(u16 BackColor );


void R61509V_ShowChar(u16 x,u16 y,u8 font,u16 color,u8 num,u8 *Buffer);	  
void R61509V_ShowWord(u16 x,u16 y,u8 font,u16 color,u8 num,u8 *Buffer);	  


 
#line 23 "..\\..\\Driver\\Components\\SCR\\LCD.c"
#line 1 "..\\..\\Driver\\Components\\INC\\ILI9326.h"







 



#line 13 "..\\..\\Driver\\Components\\INC\\ILI9326.h"
#line 14 "..\\..\\Driver\\Components\\INC\\ILI9326.h"







	


#line 53 "..\\..\\Driver\\Components\\INC\\ILI9326.h"











#line 90 "..\\..\\Driver\\Components\\INC\\ILI9326.h"


unsigned short ILI9326_Initialize(void*	pInfo);



void ILI9326_Reset(void);
unsigned short ILI9326_ReadData(void);
unsigned short ILI9326_ReadRegister(unsigned	short	Index);

void ILI9326_WriteData(unsigned	short	Data);
void ILI9326_WriteAddr(unsigned	short	Addr);
void ILI9326_WriteIndex(unsigned	short	Index);
void ILI9326_WriteRegister(unsigned	short	Addr,unsigned short Data);
void ILI9326_WriteCommand(unsigned	short	Index,unsigned short Cmd);

void ILI9326_WriteGRAM(unsigned	short* RAM,unsigned long length);
void ILI9326_ReadGRAM(unsigned	short* RAM,unsigned long length);

void ILI9326_PowerOn( void );			
void ILI9326_PowerOff( void );		
void ILI9326_SetWindowAddress(unsigned short x1,unsigned short y1,unsigned short x2,unsigned short y2);


void ILI9326_DrawDot(unsigned short HSX,unsigned short HSY,unsigned short color);		
void ILI9326_DrawLine(u16 x1,u16 y1,u16 x2,u16 y2,u16 color);						
void ILI9326_DrawCircle(u16 x1,u16 y1, u16 R, u8 Filled, u16 color );		
void ILI9326_DrawRectangle(u16 x1,u16 y1,u16 x2,u16 y2,u16 color);				

void ILI9326_Fill(u16 xsta,u16 ysta,u16 xend,u16 yend,u16 color);				
void ILI9326_Clean(u16 Color);	
void ILI9326_SetBackground(u16 BackColor );


void ILI9326_ShowChar(u16 x,u16 y,u8 font,u16 color,u8 num,u8 *Buffer);	  
void ILI9326_ShowWord(u16 x,u16 y,u8 font,u16 color,u8 num,u8 *Buffer);	  



 
#line 24 "..\\..\\Driver\\Components\\SCR\\LCD.c"
#line 1 "..\\..\\Driver\\Components\\INC\\SSD1963.H"




#line 6 "..\\..\\Driver\\Components\\INC\\SSD1963.H"



















 



































enum SSD1963REG
{
	SSD1963_R01_REST	=	0x01,		
	SSD1963_R0A_GPM		=	0X0A,		
	SSD1963_R0B_GAM		=	0x0B,		
	SSD1963_R0C_GPF		=	0x0C,		
	SSD1963_R0D_GDM		=	0x0D,		
	SSD1963_R0E_GSM		=	0x0E,		
	SSD1963_R10_ISP		=	0x10,		
	SSD1963_R11_OSP		=	0X11,		
	SSD1963_R12_EPM		=	0X12,		
	SSD1963_R13_ENM		=	0X13,		
	SSD1963_R20_OIM		=	0X20,		
	SSD1963_R21_IIM		=	0X21,		
	SSD1963_R26_SGC		=	0X26,		
	SSD1963_R28_SOF		=	0X28,		
	SSD1963_R29_SON		=	0X29,		
	SSD1963_R2A_SCA		=	0X2A,		
	SSD1963_R2B_SPA		=	0X2B,		
	SSD1963_R2C_WMS		=	0X2C,		
	SSD1963_R2E_RMS		=	0X2E,		
	SSD1963_R30_SEA		=	0X30,		
	SSD1963_R33_SSA		=	0X33,		
	SSD1963_R34_STF		=	0X34,		
	SSD1963_R35_STO		=	0X35,		
	SSD1963_R36_SAM		=	0X36,		
	SSD1963_R37_SSS		=	0X37,		
	SSD1963_R38_OIM		=	0X38,		
	SSD1963_R39_IIM		=	0X39,		
	SSD1963_R3A_SPF		=	0X3A,		
	SSD1963_R3C_WMC		=	0X3C,		
	SSD1963_R3E_RMC		=	0X3E,		
	SSD1963_R44_STS		=	0X44,		
	SSD1963_R45_GS		=	0X45,		
	SSD1963_RA1_RD		=	0XA1,		
	SSD1963_RB0_SLM		=	0XB0,		
	SSD1963_RB1_GLM		=	0XB1,		
	SSD1963_RB4_SHP_	=	0XB4,		
	SSD1963_RB5_GHP		=	0XB5,		
	SSD1963_RB6_SVP		=	0XB6,		
	SSD1963_RB7_GVP		=	0XB7,		
	SSD1963_RB8_SGC		=	0XB8,		
	SSD1963_RB9_GGC		=	0XB9,		
	SSD1963_RBA_SGV		=	0XBA,		
	SSD1963_RBC_SPP		=	0XBC,		
	SSD1963_RBD_GPP		=	0XBD,		
	SSD1963_RBE_SPC		=	0XBE,		
	SSD1963_RBF_GPC		=	0XBF,		
	
	SSD1963_RC0_SLG0	=	0XC0,		
	SSD1963_RC1_GLG0	=	0XC1,		
	SSD1963_RC2_SLG1	=	0XC2,		
	SSD1963_RC3_SLG1	=	0XC3,		
	SSD1963_RC4_SLG2	=	0XC4,		
	SSD1963_RC5_SLG2	=	0XC5,		
	SSD1963_RC6_SLG3	=	0XC6,		
	SSD1963_RC7_SLG3	=	0XC7,		
	
	SSD1963_RC8_SPR0	=	0XC8,		
	SSD1963_RC9_GPR0	=	0XC9,		
	SSD1963_RCA_SPR1	=	0XCA,		
	SSD1963_RCB_GPR1	=	0XCB,		
	SSD1963_RCC_SPR2	=	0XCC,		
	SSD1963_RCD_GPR2	=	0XCD,		
	SSD1963_RCE_SPR3	=	0XCE,		
	SSD1963_RCF_GPR3	=	0XCF,		
	
	SSD1963_RD0_SDC		=	0XD0,		
	SSD1963_RD1_GDC		=	0XD1,		
	SSD1963_RD4_SDT		=	0XD4,		
	SSD1963_RD5_GDT		=	0XD5,		
	
	SSD1963_RE0_SPLL	=	0XE0,		
	SSD1963_RE2_SPLLM	=	0XE2,		
	SSD1963_RE3_GPLLM	=	0XE3,		
	SSD1963_RE4_GPLLS	=	0XE4,		
	SSD1963_RE5_SDS		=	0XE5,		
	SSD1963_RE6_SLF		=	0XE6,		
	SSD1963_RE7_GLF		=	0XE7,		
	SSD1963_RF0_SPDI	=	0XF0,		
	SSD1963_RF1_GPDI	=	0XF1,		
};


			



void SSD1963_Initialize(void*	pInfo);

void SSD1963_SetWindowAddress(unsigned short x1,unsigned short y1,unsigned short x2,unsigned short y2);
void SSD1963_PowerOn(void);



unsigned short SSD1963_ReadData(void);
unsigned short SSD1963_ReadRegister(unsigned	short	Addr);

void SSD1963_WriteData(unsigned	short	Data);
void SSD1963_WriteIndex(unsigned	short	Index);
void SSD1963_WriteAddr(unsigned	short	Addr);
void SSD1963_WriteRegister(unsigned	short	Addr,unsigned short Data);		
void SSD1963_WriteCommand(unsigned	short	Index,unsigned short Cmd);


void SSD1963_WriteGRAM(unsigned	short* RAM,unsigned long length);				
void SSD1963_ReadGRAM(unsigned	short* RAM,unsigned long length);


void SSD1963_PowerOn(void);					
void SSD1963_PowerOff( void );		
void SSD1963_DispOff( void );			
void SSD1963_SetWindowAddress(unsigned short x1,unsigned short y1,unsigned short x2,unsigned short y2);


void SSD1963_DrawDot(unsigned short HSX,unsigned short HSY,unsigned short color);		
void SSD1963_DrawLine(u16 x1,u16 y1,u16 x2,u16 y2,u16 color);						
void SSD1963_DrawCircle(u16 x1,u16 y1, u16 R, u8 Filled, u16 color );		
void SSD1963_DrawRectangle(u16 x1,u16 y1,u16 x2,u16 y2,u16 color);

void SSD1963_Fill(u16 xsta,u16 ysta,u16 xend,u16 yend,u16 color);				
void SSD1963_Clean(u16 Color);	
void SSD1963_SetBackground(u16 BackColor );


void SSD1963_ShowChar(u16 x,u16 y,u8 font,u16 color,u8 num,u8 *Buffer);	  
void SSD1963_ShowWord(u16 x,u16 y,u8 font,u16 color,u8 num,u8 *Buffer);	  






#line 25 "..\\..\\Driver\\Components\\SCR\\LCD.c"


LCDDef 			*LCDSYS	=	0;	
stLCDScroll	*ScrollBuff	=	0;
unsigned short PenColor		=	0;		
unsigned short BackColor	=	0;		
unsigned short VAsize	=	0;		





 
unsigned short LCD_Initialize(LCDDef *pInfo)
{
	static unsigned short	DeviceCode	=	0;
	
  LCDPortDef  *Port;
	LCDSYS	  =	pInfo;		
  
  Port	=	&(pInfo->Port);	
	
	
	GPIO_Configuration_OPP50	(Port->sBL_PORT,				Port->sBL_Pin);					
	GPIO_Configuration_OPP50	(Port->sRD_PORT,				Port->sRD_Pin);					
	GPIO_Configuration_OPP50	(Port->sREST_PORT,			Port->sREST_Pin);				
	GPIO_Configuration_OPP50	(Port->sDC_PORT,				Port->sDC_Pin);					
	GPIO_Configuration_OPP50	(Port->sWR_PORT,				Port->sWR_Pin);					
	GPIO_Configuration_OPP50	(Port->sCS_PORT,				Port->sCS_Pin);					
	GPIO_Configuration_OPP50	(Port->sTE_PORT,				Port->sTE_Pin);					
	GPIO_Configuration_OPP50	(Port->sDATABUS_PORT,		Port->sDATABUS_Pin);		
	
  LCDSYS->Display.WriteIndex    = LCD_WriteIndex;
  LCDSYS->Display.WriteData     = LCD_WriteData;
  LCDSYS->Display.WriteCommand  = LCD_WriteCommand;
	
	LCD_Reset();

	
	DeviceCode	=	ILI9326_Initialize(pInfo);
	if((unsigned short)0x9326	==	DeviceCode)
	{
		goto	Lcd_InitContinue;
	}
		
	DeviceCode	=	R61509V_Initialize(pInfo);
	if((unsigned short)0xB509	==	DeviceCode)
	{
		goto	Lcd_InitContinue;
	}
	
	SSD1963_Initialize(pInfo);

	Lcd_InitContinue:
  
	if(pInfo->Data.PColor	==	pInfo->Data.BColor)
	{
		pInfo->Data.PColor	=	pInfo->Data.BColor^0xFF;
	}
  
	
	LCDSYS->Display.PowerOn();						
	
	LCD_Clean(pInfo->Data.BColor);				
	
	PWM_OUT((TIM_TypeDef*) (((u32)0x40000000) + 0x0000),PWM_OUTChannel4,1000,100);
	
	GT32L32_Initialize(&pInfo->GT32L32.SPI);				
	
	return	0;
}





 
void LCDFsmc_Initialize(LCDDef *pInfo)
{  
	static unsigned short	DeviceCode	=	0;
  GPIO_InitTypeDef                GPIO_InitStructure;
	FSMC_NORSRAMInitTypeDef         FSMC_NORSRAMInitStructure;
  FSMC_NORSRAMTimingInitTypeDef   FSMC_NORSRAMTimingInitStructure;
  
  LCDPortDef  *Port;
	LCDSYS	  =	pInfo;		
  
  Port	=	&(pInfo->Port);	
	
	
  RCC_AHBPeriphClockCmd(((u32)0x00000100), ENABLE);
  RCC_APB2PeriphClockCmd(((u32)0x00000004) |((u32)0x00000008) |((u32)0x00000010) |((u32)0x00000020) | ((u32)0x00000040) | ((u32)0x00000080) | ((u32)0x00000100) | ((u32)0x00000001), ENABLE);
  
  if(0!= Port->sBL_PORT)
    GPIO_Configuration_OPP50	(Port->sBL_PORT,				Port->sBL_Pin);					
  if(0!= Port->sREST_PORT)
    GPIO_Configuration_OPP50	(Port->sREST_PORT,			Port->sREST_Pin);				
  if(0!= Port->sCS_PORT)
    GPIO_Configuration_OPP50	(Port->sCS_PORT,				Port->sCS_Pin);					
  
  GPIO_Configuration_APP50(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)),((u16)0x0001) | ((u16)0x0002) | ((u16)0x0100) | ((u16)0x0200) | ((u16)0x0400) | ((u16)0x4000) | ((u16)0x8000));
  GPIO_Configuration_APP50(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1800)),((u16)0x0080) | ((u16)0x0100) | ((u16)0x0200) | ((u16)0x0400) |  ((u16)0x0800) | ((u16)0x1000) | ((u16)0x2000) | ((u16)0x4000) | ((u16)0x8000));
  
  GPIO_Configuration_APP50(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)),((u16)0x0010) | ((u16)0x0020));
  
  GPIO_Configuration_APP50(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x2000)),((u16)0x1000));
  
  GPIO_Configuration_APP50(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1800)),((u16)0x0008));
  
  
  
  GPIO_SetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x2000)), ((u16)0x1000));
  
  GPIO_ResetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1800)), ((u16)0x0002));
  
  GPIO_SetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x0010));
  
  GPIO_SetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400)), ((u16)0x0020));
  
  GPIO_ResetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x2000)), ((u16)0x1000));
  LCD_DelaymS(100); 
  
  
  
   
   
   
  FSMC_NORSRAMTimingInitStructure.FSMC_AddressSetupTime = 1;
  FSMC_NORSRAMTimingInitStructure.FSMC_AddressHoldTime = 0;
  FSMC_NORSRAMTimingInitStructure.FSMC_DataSetupTime = 2;
  FSMC_NORSRAMTimingInitStructure.FSMC_BusTurnAroundDuration = 0;
  FSMC_NORSRAMTimingInitStructure.FSMC_CLKDivision = 0;
  FSMC_NORSRAMTimingInitStructure.FSMC_DataLatency = 0;
  FSMC_NORSRAMTimingInitStructure.FSMC_AccessMode = ((u32)0x10000000);

  






 
  FSMC_NORSRAMInitStructure.FSMC_Bank = ((u32)0x00000006);
  FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = ((u32)0x00000000);
  FSMC_NORSRAMInitStructure.FSMC_MemoryType = ((u32)0x00000000);
  FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = ((u32)0x00000010);
  FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode = ((u32)0x00000000);
  FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = ((u32)0x00000000);
  FSMC_NORSRAMInitStructure.FSMC_WrapMode = ((u32)0x00000000);
  FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = ((u32)0x00000000);
  FSMC_NORSRAMInitStructure.FSMC_WriteOperation = ((u32)0x00001000);
  FSMC_NORSRAMInitStructure.FSMC_WaitSignal = ((u32)0x00000000);
  FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = ((u32)0x00000000);
  FSMC_NORSRAMInitStructure.FSMC_WriteBurst = ((u32)0x00000000);
  FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &FSMC_NORSRAMTimingInitStructure;
  FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &FSMC_NORSRAMTimingInitStructure;

  FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure);

   
  FSMC_NORSRAMCmd(((u32)0x00000006), ENABLE);  
  






	
  
  LCDSYS->Display.WriteIndex    = LCDFsmc_WriteIndex;
  LCDSYS->Display.WriteData     = LCDFsmc_WriteData;
  LCDSYS->Display.WriteCommand  = LCD_WriteCommand;
  
  SSD1963_Initialize(pInfo);

  
	if(pInfo->Data.PColor	==	pInfo->Data.BColor)
	{
		pInfo->Data.PColor	=	pInfo->Data.BColor^0xFF;
	}
	
	LCDSYS->Display.PowerOn();						
	

  LCD_Clean(0xFFFF);				
	
  GPIO_SetBits(Port->sBL_PORT, Port->sBL_Pin);
	
	GT32L32_Initialize(&pInfo->GT32L32.SPI);				
}








 
void LCD_DisplayServer(void)
{
	if(0	!=	ScrollBuff)
	{
		LCD_Clean(LCDSYS->Data.BColor);
		LCD_ShowScroll(ScrollBuff);
	}
}








 
void LCD_Reset(void)
{
	((&(LCDSYS->Port))->sREST_PORT->BSRR = (&(LCDSYS->Port))->sREST_Pin);
	LCD_DelaymS(5);				
	((&(LCDSYS->Port))->sREST_PORT->BRR = (&(LCDSYS->Port))->sREST_Pin);
	LCD_DelaymS(5);				
	((&(LCDSYS->Port))->sREST_PORT->BSRR = (&(LCDSYS->Port))->sREST_Pin);
	LCD_DelaymS(10);				
}




 
void LCD_WriteIndex( unsigned short Index )
{




	
	((&(LCDSYS->Port))->sCS_PORT->BRR = (&(LCDSYS->Port))->sCS_Pin);
	((&(LCDSYS->Port))->sRD_PORT->BSRR = (&(LCDSYS->Port))->sRD_Pin);
	((&(LCDSYS->Port))->sDC_PORT->BRR = (&(LCDSYS->Port))->sDC_Pin);
	((&(LCDSYS->Port))->sDATABUS_PORT)->ODR = Index;
	((&(LCDSYS->Port))->sWR_PORT->BRR = (&(LCDSYS->Port))->sWR_Pin);
	((&(LCDSYS->Port))->sWR_PORT->BSRR = (&(LCDSYS->Port))->sWR_Pin);
	((&(LCDSYS->Port))->sCS_PORT->BSRR = (&(LCDSYS->Port))->sCS_Pin);
}








 
void LCD_WriteData(u16 Data)
{




	
	((&(LCDSYS->Port))->sCS_PORT->BRR = (&(LCDSYS->Port))->sCS_Pin);
	((&(LCDSYS->Port))->sRD_PORT->BSRR = (&(LCDSYS->Port))->sRD_Pin);
	((&(LCDSYS->Port))->sDC_PORT->BSRR = (&(LCDSYS->Port))->sDC_Pin);
	((&(LCDSYS->Port))->sDATABUS_PORT)->ODR = Data;
	((&(LCDSYS->Port))->sWR_PORT->BRR = (&(LCDSYS->Port))->sWR_Pin);
	((&(LCDSYS->Port))->sWR_PORT->BSRR = (&(LCDSYS->Port))->sWR_Pin);
	((&(LCDSYS->Port))->sCS_PORT->BSRR = (&(LCDSYS->Port))->sCS_Pin);
#line 310 "..\\..\\Driver\\Components\\SCR\\LCD.c"
}








 
void LCDFsmc_WriteIndex(unsigned short Index)
{  
  *(volatile unsigned short*)(LCDSYS->Data.FsmcRegAddr)  = Index;
}








 
void LCDFsmc_WriteData(unsigned short Data)
{  
  *(volatile unsigned short*)(LCDSYS->Data.FsmcDataAddr)  = Data;
}





 
void LCD_WriteCommand(												  
											unsigned short Index,			
											unsigned short Command		
											)	
{
	
  LCDSYS->Display.WriteIndex(Index);	
	
  LCDSYS->Display.WriteData(Command);
}



 
u16 LCD_ReadData( unsigned short Index )
{
	u16 Data;
	
	GPIO_Configuration_OPP50	(((&(LCDSYS->Port))->sDATABUS_PORT),((&(LCDSYS->Port))->sDATABUS_Pin));		
	
	
	((&(LCDSYS->Port))->sRD_PORT->BSRR = (&(LCDSYS->Port))->sRD_Pin);
	((&(LCDSYS->Port))->sCS_PORT->BRR = (&(LCDSYS->Port))->sCS_Pin);
	((&(LCDSYS->Port))->sDC_PORT->BRR = (&(LCDSYS->Port))->sDC_Pin);

	((&(LCDSYS->Port))->sDATABUS_PORT)->ODR = Index;
	((&(LCDSYS->Port))->sWR_PORT->BRR = (&(LCDSYS->Port))->sWR_Pin);
	((&(LCDSYS->Port))->sWR_PORT->BSRR = (&(LCDSYS->Port))->sWR_Pin);
	((&(LCDSYS->Port))->sDC_PORT->BSRR = (&(LCDSYS->Port))->sDC_Pin);

	GPIO_Configuration_IPU	(((&(LCDSYS->Port))->sDATABUS_PORT),((&(LCDSYS->Port))->sDATABUS_Pin));			
  
	((&(LCDSYS->Port))->sRD_PORT->BRR = (&(LCDSYS->Port))->sRD_Pin);

	Data = ((&(LCDSYS->Port))->sDATABUS_PORT)->IDR;
	((&(LCDSYS->Port))->sRD_PORT->BSRR = (&(LCDSYS->Port))->sRD_Pin);
	((&(LCDSYS->Port))->sCS_PORT->BSRR = (&(LCDSYS->Port))->sCS_Pin);
	
	GPIO_Configuration_OPP50	(((&(LCDSYS->Port))->sDATABUS_PORT),((&(LCDSYS->Port))->sDATABUS_Pin));		
	return Data;	
}








 
void LCD_WriteRegister(unsigned	short	Index,unsigned short Data)
{

	
	((&(LCDSYS->Port))->sRD_PORT->BSRR = (&(LCDSYS->Port))->sRD_Pin);
	((&(LCDSYS->Port))->sCS_PORT->BRR = (&(LCDSYS->Port))->sCS_Pin);
	
	((&(LCDSYS->Port))->sDC_PORT->BRR = (&(LCDSYS->Port))->sDC_Pin);		
	((&(LCDSYS->Port))->sWR_PORT->BRR = (&(LCDSYS->Port))->sWR_Pin);
	((&(LCDSYS->Port))->sDATABUS_PORT)->ODR = Index;
	((&(LCDSYS->Port))->sWR_PORT->BSRR = (&(LCDSYS->Port))->sWR_Pin);
	((&(LCDSYS->Port))->sDC_PORT->BSRR = (&(LCDSYS->Port))->sDC_Pin);	
	
	((&(LCDSYS->Port))->sWR_PORT->BRR = (&(LCDSYS->Port))->sWR_Pin);
	((&(LCDSYS->Port))->sDATABUS_PORT)->ODR = Data;
	((&(LCDSYS->Port))->sWR_PORT->BSRR = (&(LCDSYS->Port))->sWR_Pin);
	((&(LCDSYS->Port))->sCS_PORT->BSRR = (&(LCDSYS->Port))->sCS_Pin);	
#line 437 "..\\..\\Driver\\Components\\SCR\\LCD.c"
}








 
unsigned short LCD_ReadRegister(unsigned	short	Index)
{
	unsigned short Data	=	0;

	
	((&(LCDSYS->Port))->sRD_PORT->BSRR = (&(LCDSYS->Port))->sRD_Pin);
	((&(LCDSYS->Port))->sCS_PORT->BRR = (&(LCDSYS->Port))->sCS_Pin);
	
	((&(LCDSYS->Port))->sDC_PORT->BRR = (&(LCDSYS->Port))->sDC_Pin);		
	((&(LCDSYS->Port))->sWR_PORT->BRR = (&(LCDSYS->Port))->sWR_Pin);
	((&(LCDSYS->Port))->sDATABUS_PORT)->ODR = Index;
	((&(LCDSYS->Port))->sWR_PORT->BSRR = (&(LCDSYS->Port))->sWR_Pin);
	((&(LCDSYS->Port))->sDC_PORT->BSRR = (&(LCDSYS->Port))->sDC_Pin);	
	
	GPIO_Configuration_IPU	(((&(LCDSYS->Port))->sDATABUS_PORT),((&(LCDSYS->Port))->sDATABUS_Pin));			
	((&(LCDSYS->Port))->sRD_PORT->BRR = (&(LCDSYS->Port))->sRD_Pin);
	Data	=	((&(LCDSYS->Port))->sDATABUS_PORT)->IDR;
	((&(LCDSYS->Port))->sRD_PORT->BSRR = (&(LCDSYS->Port))->sRD_Pin);
	((&(LCDSYS->Port))->sCS_PORT->BSRR = (&(LCDSYS->Port))->sCS_Pin);
	GPIO_Configuration_OPP50	(((&(LCDSYS->Port))->sDATABUS_PORT),((&(LCDSYS->Port))->sDATABUS_Pin));		
#line 497 "..\\..\\Driver\\Components\\SCR\\LCD.c"
	return Data;
}






 
void LCD_Clean(u16 Color)	
{
	LCDSYS->Display.Clean(Color);
}






 
void LCD_DrawDot(
									unsigned short HSX,			
									unsigned short HSY,			
									unsigned short Color		
								)
{
	LCDSYS->Display.DrawDot(HSX,HSY,Color);
}








 
void LCD_DrawLine(
									unsigned short HSX, unsigned short HSY, 	
									unsigned short HEX, unsigned short HEY,		
									unsigned short Color					
)
{
	LCDSYS->Display.DrawLine(HSX,HSY,HEX,HEY,Color);
}






 
void LCD_DrawCircle(
												u16 x,u16 y,		
												u16 r,					
												u8 Filled,			
												u16 Color				
												)
{
	LCDSYS->Display.DrawCircle(x,y,r,Filled,Color);
}




 
void LCD_DrawRectangle(u16 x1,u16 y1,u16 x2,u16 y2,u16 Color)
{
	LCDSYS->Display.DrawRectangle(x1,y1,x2,y2,Color);
}





 
void LCD_Fill(
							unsigned short x1, unsigned short y1, 	
							unsigned short x2, unsigned short y2,		
							u16 Color
)
{ 
	LCDSYS->Display.Fill(x1,y1,x2,y2,Color);
}



 
void LCD_SetBackground(  u16 BackColor )
{
  LCDSYS->Data.BColor = BackColor;
	LCD_Clean(BackColor);	
}





 
void LCD_ShowAntenna(
                    u16 x,			
										u16 y,			
                    u8 Num,
										u16 PenColor)
{	
  unsigned char GetBufferLength	=	0;
  unsigned char CodeBuffer[32]={0};
  if(Num>4)
  {
    Num=4;
  }
  GetBufferLength = GT32L32_GetAntennaCode(Num,CodeBuffer);

	LCD_ShowWord(x,y,12,PenColor,GetBufferLength,CodeBuffer);
}





 
void LCD_ShowBattery(
                    u16 x,			
										u16 y,			
                    u8 Num,
										u16 PenColor)
{
  unsigned char GetBufferLength	=	0;
  unsigned char CodeBuffer[64]={0};
  if(Num>3)
  {
    Num=3;
  }
  GetBufferLength = GT32L32_GetBatteryCode(Num,CodeBuffer);
	LCD_ShowWord(x,y,12,PenColor,GetBufferLength,CodeBuffer);
}





 
void LCD_ShowChar(
										u16 x,			
										u16 y,			
										u8 font,		
										u16 color,	
										u8 num,			
										u8 *Buffer	
										
)		
{
	LCDSYS->Display.ShowChar(x,y,font,color,num,Buffer);
}





 
void LCD_ShowWord(
										u16 x,			
										u16 y,			
										u8 font,		
										u16 color,	
										u8 num,			
										u8 *Buffer	
										
)		
{
	LCDSYS->Display.ShowWord(x,y,font,color,num,Buffer);
}








 
unsigned short LCD_GetDispCodeBuffer(
													u8 font,								
													u16 word,								
													u8 *ReadBuffer				  
												)
{
	unsigned short lengh=0;
	lengh	=	GT32L32_GetCode(font,word,ReadBuffer);		
	return lengh;
}





 
void LCD_Show(
							u16 x,			
							u16 y,			
							u8 font,		
							u16 PenColor,
							u8 num,			
							u8 *Buffer	
)		
{
	unsigned short	MaxV,MaxH;	
	unsigned char i=0;
	unsigned char CodeBuffer[130]={0};
	switch(LCDSYS->Flag.Rotate)
	{
		case Draw_Rotate_90D:
			MaxV	=	LCDSYS->Data.MaxH;
			MaxH	=	LCDSYS->Data.MaxV;
			break;
		case Draw_Rotate_180D:
			MaxV	=	LCDSYS->Data.MaxV;
			MaxH	=	LCDSYS->Data.MaxH;
			break;
		case Draw_Rotate_270D:
			MaxV	=	LCDSYS->Data.MaxH;
			MaxH	=	LCDSYS->Data.MaxV;
			break;
		default:
			MaxV	=	LCDSYS->Data.MaxV;
			MaxH	=	LCDSYS->Data.MaxH;
			break;
	}
	for(i=0;i<num;i++)
	{
		unsigned char GetBufferLength	=	0;
		unsigned char dst=Buffer[i];
		
		
		if(dst>0x80)
		{
			u16 word=dst<<8;
      
			dst=Buffer[i+1];
			word=word|dst;			
			
      if(x>MaxH-font)
      {
        x=0;
        y+=font;
      }
      
      if(y>MaxV-font)
      {
        y=x=0;
      }
      
			GetBufferLength	=	LCD_GetDispCodeBuffer(font,word,CodeBuffer);		
			
			LCD_ShowWord(x,y,font,PenColor,GetBufferLength,CodeBuffer);
			
      x+=font;
			i++;		
		}
		else if(('\r'==dst)||('\n'==dst))
		{
			if(('\n'==Buffer[i+1])||('\r'==Buffer[i+1]))
			{
				i++;	
			}
			if(y>MaxV-font)
      {
        y=x=0;
      }
			else
			{
				x=0;
				y+=font;
			}
			goto LCD_ShowJump;
		}
		
		else
		{			
			
      if(x>MaxH-font/2)
      {
        x=0;
        y+=font;
      }
      
      if(y>MaxV-font)
      {
        y=x=0;
      }
      
			GetBufferLength	=	LCD_GetDispCodeBuffer(font,(u16)dst,CodeBuffer);		
			
			if(	('	'	==	(char)dst)		
				||(' '	==	(char)dst))		
			{
				memset(CodeBuffer,0x00,GetBufferLength);
			}
			
			LCD_ShowChar(x,y,font,PenColor,GetBufferLength,CodeBuffer);
			
      x+=font/2;						
		}
		LCD_ShowJump:
			__nop();
	}
}





 
void LCD_ShowScroll(stLCDScroll	*ScrollBuff)		
{
	unsigned short	MaxV,MaxH;	
	unsigned char i=0;
	unsigned char CodeBuffer[130]={0};
	unsigned char	num		=	ScrollBuff->length;
	unsigned char	font	=	0;
	unsigned char* Buffer	=0;
	unsigned	short x,y;
	stLCDScroll*	TempBuff;
	if(0==	ScrollBuff)
	{
		return;
	}
	TempBuff	=	ScrollBuff;
	

	switch(LCDSYS->Flag.Rotate)
	{
		case Draw_Rotate_90D:
			MaxV	=	LCDSYS->Data.MaxH;
			MaxH	=	LCDSYS->Data.MaxV;
			break;
		case Draw_Rotate_180D:
			MaxV	=	LCDSYS->Data.MaxV;
			MaxH	=	LCDSYS->Data.MaxH;
			break;
		case Draw_Rotate_270D:
			MaxV	=	LCDSYS->Data.MaxH;
			MaxH	=	LCDSYS->Data.MaxV;
			break;
		default:
			MaxV	=	LCDSYS->Data.MaxV;
			MaxH	=	LCDSYS->Data.MaxH;
			break;
	}
	LCD_ShowCoutinue:
	Buffer	=	&TempBuff->buffer[TempBuff->starty];
	for(i=0;i<num;i++)
	{
		unsigned char GetBufferLength	=	0;
		unsigned char dst=Buffer[i];
		
		
		if(dst>0x80)
		{
			
			u16 word=dst<<8;
      
			TempBuff->starty+=2;
			dst=Buffer[i+1];
			word=word|dst;			
			
      if(x>MaxH-font)
      {
        x=0;
        y+=font;
      }
      
      if(y>MaxV-font)
      {
        y=x=0;
      }
      
			GetBufferLength	=	LCD_GetDispCodeBuffer(font,word,CodeBuffer);		
			
			LCD_ShowWord(x,y,font,PenColor,GetBufferLength,CodeBuffer);
			
      x+=font;
			i++;		
		}
		
		else
		{			
			
      if(x>MaxH-font/2)
      {
        x=0;
        y+=font;
      }
      
      if(y>MaxV-font)
      {
        y=x=0;
      }
      
			GetBufferLength	=	LCD_GetDispCodeBuffer(font,(u16)dst,CodeBuffer);		
			
			if(	('	'	==	(char)dst)		
				||(' '	==	(char)dst))		
			{
				memset(CodeBuffer,0x00,GetBufferLength);
			}
			
			LCD_ShowChar(x,y,font,PenColor,GetBufferLength,CodeBuffer);
			
      x+=font/2;						
		}
		LCD_ShowJump:
			__nop();
	}
}





 
void LCD_ShowHex(
							u16 x,			
							u16 y,			
							u8 font,		
							u16 color,	
							u8 num,			
              u8 bitnum,  
							u8 *Buffer	
)		
{
	unsigned short	MaxV,MaxH;	
	unsigned char i=0;
  unsigned char Cril  = 0;
	unsigned char CodeBuffer[130]={0};

  
	switch(LCDSYS->Flag.Rotate)
	{
		case Draw_Rotate_90D:
			MaxV	=	LCDSYS->Data.MaxH;
			MaxH	=	LCDSYS->Data.MaxV;
			break;
		case Draw_Rotate_180D:
			MaxV	=	LCDSYS->Data.MaxV;
			MaxH	=	LCDSYS->Data.MaxH;
			break;
		case Draw_Rotate_270D:
			MaxV	=	LCDSYS->Data.MaxH;
			MaxH	=	LCDSYS->Data.MaxV;
			break;
		default:
			MaxV	=	LCDSYS->Data.MaxV;
			MaxH	=	LCDSYS->Data.MaxH;
			break;
	}
	for(i=0;i<num;i++)
	{
    unsigned char GetBufferLength	=	0;
    for(Cril=bitnum/4;Cril>0;Cril--)
    {
      
      unsigned char dst=(((u32)Buffer[i]>>(Cril-1)*4)&0x0F);
      
      if(dst<=9)
      {
        dst+=0x30;
      }
      else if((10<=dst)&&(15>=dst))
      {
        dst+=0x37;
      }
      
      if(x>MaxH-font/2)
      {
        x=0;
        y+=font;
      }
      
      if(y>MaxV-font)
      {
        y=x=0;
      }
      
      GetBufferLength	=	LCD_GetDispCodeBuffer(font,dst,CodeBuffer);		
      
      LCD_ShowChar(x,y,font,color,GetBufferLength,CodeBuffer);
      
      x+=font/2;
    }
    
    x+=font/2;
		if(x>MaxH-font)
		{
			y+=font;
			x=0;
		}
	}
}









 
unsigned int LCD_Printf(u16 x,u16 y,u8 font,u16 color,const char *format,...)				
{ 
		





	
	char	DataBuffer[256]={0};			
	
  u16 InputDataSize=0;		
	
	va_list args; 
	
	__va_start(args, format);
	
	InputDataSize = vsnprintf(DataBuffer, InputDataSize,format, args);

	
	__va_end(args);                                      		
  if((8!=font)&&(12!=font)&&(16!=font)&&(24!=font)&&(32!=font))
  {
    font  = 32;
  }
	LCD_Show(x,y,font,color,InputDataSize,(unsigned char*)DataBuffer);
	return InputDataSize;
}









 
unsigned int LCD_PrintfScroll(u16 x,u16 y,u8 font,u16 color,const char *format,...)				
{ 
		





	
	char	DataBuffer[256]={0};			
	
  u16 InputDataSize=0;		
	
	va_list args; 
	
	__va_start(args, format);
	
	InputDataSize = vsnprintf(DataBuffer, InputDataSize,format, args);

	
	__va_end(args);                                      		
  if((8!=font)&&(12!=font)&&(16!=font)&&(24!=font)&&(32!=font))
  {
    font  = 24;
  }
	if(0	==	ScrollBuff)
	{
		static stLCDScroll	NewBuff;		
		
		NewBuff.startx	=	x;
		NewBuff.starty	=	y;
		NewBuff.runxstart	=	0;
		NewBuff.color	=	color;
		NewBuff.font	=	font;
		NewBuff.length	=	InputDataSize;
		memcpy(NewBuff.buffer,DataBuffer,InputDataSize);
		
		ScrollBuff	=	&NewBuff;
		ScrollBuff->nextlist	=	0;
	}
	else
	{
		static stLCDScroll		NewBuff;
		stLCDScroll*	TempBuff;
		TempBuff	=	(stLCDScroll*)ScrollBuff->nextlist;
		while(0	!=	TempBuff->nextlist)
		{
			TempBuff	=	(stLCDScroll*)ScrollBuff->nextlist;
		}
		NewBuff.startx	=	x;
		NewBuff.starty	=	y;
		NewBuff.runxstart	=	0;
		NewBuff.color	=	color;
		NewBuff.font	=	font;
		NewBuff.length	=	InputDataSize;
		memcpy(NewBuff.buffer,DataBuffer,InputDataSize);
		
		NewBuff.nextlist	=	0;
		TempBuff->nextlist	=	(unsigned long*)&NewBuff;
	}

	return InputDataSize;
}





 
void LCD_ShowBMP(
							unsigned short x1, unsigned short y1, 	
							unsigned short x2, unsigned short y2,		
							u16 Length,   
              u8 *RGBBuffer     
)		
{
	unsigned short i = 0;
  unsigned short j = 0;
  unsigned short  RGB565;
  eRotate Rotate = LCDSYS->Flag.Rotate;
  LCDSYS->Flag.Rotate  = Draw_Rotate_0D;			
  LCDSYS->Display.WriteAddress(x1,y1,x2,y2);	

	for(i=0;i<Length;)
	{
    RGB565  = RGB888toRGB565(&RGBBuffer[i]);
    LCDSYS->Display.WriteData(RGB565);
    i+=3;
	}

  LCDSYS->Flag.Rotate  =  Rotate;
}








 
unsigned  short RGB888toRGB565(u8 *RGB888)
{
  unsigned  short RGB565  = 0;
  
  RGB565  = RGB888[2]>>3;
  RGB565<<=5;
  
  RGB565  |= RGB888[1]>>3;
  RGB565<<=6;
  
  RGB565  |= RGB888[0]>>3;
  return  RGB565;
}







 
void LCD_DelayuS(u32 xuS)
{
	SysTick_DeleyuS(xuS);				
}





 
void LCD_DelaymS(u32 xms)
{
	SysTick_DeleymS(xms);				
}





 
void LCD_DelayS(u32 xS)
{
	SysTick_DeleyS(xS);				
}

 


