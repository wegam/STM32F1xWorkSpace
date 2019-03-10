#line 1 "..\\..\\Driver\\Components\\SCR\\GT32L32M0180.C"













 


#line 1 "..\\..\\Driver\\Components\\INC\\GT32L32M0180.H"













 




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








 
 
 


#line 18 "..\\..\\Driver\\Components\\SCR\\GT32L32M0180.C"





 
 

 


 

SPIDef		*pSPI = 0;       

u8 BAR_PIC_ADDR[64]={0XFF};
u8 GBCode[64]={0XFF};





u32 GT32L32_GetAddress(u8 font, u8 c1, u8 c2, u8 c3, u8 c4);
u32 GT32L32_GetBufferLen(u8 font, u8 c1, u8 c2, u8 c3, u8 c4);
u16 GT32L32_ReadBuffer(u32 Address,u32 lengh,u8 *ReadBuffer);		

u32 GT32L32_GetGB18030(u8 c1, u8 c2, u8 c3, u8 c4);		


u32 GT32L32_GetBarCode_13(u8 * BAR_NUM);															
u32 GT32L32_GetBarCode_128(u8	*BAR_NUM,u8	flag);											



u16	GT32L32_U2G_13(u16 Unicode);																			
u32 GT32L32_UNICODE_To_GBK(u16 unicode,u8 *GetBuffer);								
u32 GT32L32_BIG5_To_GBK(u16 BIG5_Code,u8 *GetBuffer);									








 
void GT32L32_Initialize(SPIDef *SpiPort)
{
  pSPI  = SpiPort;
  SPI_Initialize(pSPI);				
	SPI_CS_LOW(pSPI);
	SPI_CS_HIGH(pSPI);
}











 
u32 GT32L32_GetGB18030(u8 c1, u8 c2, u8 c3, u8 c4) 
{ 
	u32 Address=0;						
	u32  BaseAdd=0x47AE10;		
	if(c2==0x7f) 
	{
		return (BaseAdd);
	}
	
	if((c1>=0xA1 && c1 <= 0xAB) && c2>=0xA1) 			
	{
		Address= (c1 - 0xA1) * 94 + (c2 - 0xA1);
	}
	
	else if((c1>=0xa8 && c1 <= 0xa9) && c2<0xa1) 	
	{ 
		if(c2>0x7f)
			c2--; 
		Address=(c1-0xa8)*96 + (c2-0x40)+846; 
	}
	
	if((c1>=0xb0 && c1 <= 0xf7) && c2>=0xa1) 			
	{
		Address= (c1 - 0xB0) * 94 + (c2 - 0xA1)	+	1038-192;
	}
	
	else if((c1<0xa1 && c1>=0x81) && c2>=0x40 ) 	
	{ 
		if(c2>0x7f) 
			c2--;
		Address=(c1-0x81)*190 + (c2-0x40) + 1038 +	6768-192;
	}
	
	else if(c1>=0xaa && c2<0xa1) 								
	{ 
		if(c2>0x7f) 
			c2--; 
		Address=(c1-0xaa)*96 + (c2-0x40) + 1038 +	12848-192; 
	}
	else if(c1==0x81 && c2>=0x39) 							
	{ 
		Address =1038 + 21008+(c3-0xEE)*10+c4-0x39; 
	} 
	else if(c1==0x82)														
	{ 
		Address =1038 + 21008+161+(c2-0x30)*1260+(c3-0x81)*10+c4-0x30; 
	} 
	return	Address;  
}





 
u32 GT32L32_GetAddress(u8 font, u8 c1, u8 c2, u8 c3, u8 c4)
{
	u32 Address=0;	
	u32 BaseAddr=0;
	
	if(c1>0x80)				
	{
		
		if(font==12)				
		{
			Address=GT32L32_GetGB18030(c1,	c2,	0,	0)*24+0x113D0E+192*24;
		}
		else if(font==16)		
		{
			Address=GT32L32_GetGB18030(c1,	c2,	c3,	c4)*32+0x194FDE+192*32;
		}
		else if(font==24)		
		{
			Address=GT32L32_GetGB18030(c1,	c2,	c3,	c4)*72+0x2743DE+192*72;
		}
		else if(font==32)		
		{
			Address=GT32L32_GetGB18030(c1,	c2,	c3,	c4)*128+0x47AE10;
		}
	}
	else							
	{
		if  ((c1 >0x20)&&(c1<=0x7e))		
		{	
			switch(font)
			{
				case 0x100000:	Address=(c1-0x20)*8+0x100000;		
							break ;
				case 0x100300:	Address=(c1-0x20)*8+0x100300;		
							break ;
				case 0x100600:	Address=(c1-0x20)*8+0x100600;		
							break ;
				case 12:	      Address=(c1-0x20)*12+0x100900;  
								break ;
				case 0x100D80:	Address=(c1-0x20)*16+0x100D80;  
							break ;  
				case 16:				Address=(c1-0x20)*16+0x101580;  
							break ;
				case 24:				Address=(c1-0x20)*48+0x101B80;  
							break ;  
				case 32: 				Address=(c1-0x20)*64+0x102D80;  
							break ;
				case 52: 	      Address=(c1-0x20)*64+0x104580;  
							break ;
				case 62: 	      Address=(c1-0x20)*26+0x105D80;  
							break ;
				case 0x106740: 	Address=(c1-0x20)*34+0x106740;  
							break ; 
				case 0x107400: 	Address=(c1-0x20)*74+0x107400;  
							break ;
				case 0x108FC0: 	Address=(c1-0x20)*130+0x108FC0; 
							break ;
				case 121: 	    Address=(c1-0x20)*26+0x10C080;  
							break ;
				case 56: 	      Address=(c1-0x20)*34+0x10CA50;  
							break ;
				case 54: 	      Address=(c1-0x20)*74+0x10D740;  
							break ;
				case 36: 	      Address=(c1-0x20)*130+0x10F340; 
							break ;  
				default: 
							break ;
			}
		}	
	}	
	return(Address);
}














 
u32 GT32L32_GetBufferLen(u8 font, u8 c1, u8 c2, u8 c3, u8 c4) 
{	
	u32 lengh=0;
	
	if(c1>0x80)				
	{	
		
		if(font==12)
		{
			lengh=24;		
		}
		else if(font==16)
		{
			lengh=32;		
		}
		else if(font==24)
		{
			lengh=72;		
		}
		else if(font==32)
		{
			lengh=128;	
		}
	}
	else
	{
		
		if(font==12)
		{
			lengh=16;		
		}
		else if(font==16)
		{
			lengh=16;		
		}
		else if(font==24)
		{
			lengh=48;		
		}
		else if(font==32)
		{
			lengh=64;	
		}
	}
	return lengh;	 
}









 
u32 GT32L32_GetBarCode_13(u8 * BAR_NUM)
{
	u32 i,BaseAddr=0x478FD2;
	BAR_PIC_ADDR[0]=BAR_NUM[0]*54+540*0+ BaseAddr;
	BAR_PIC_ADDR[1]=BAR_NUM[1]*54+540*1+ BaseAddr;
	switch(BAR_NUM[0])
	{
		case 0:
			for(i=2;i<=6;i++)
			{
				BAR_PIC_ADDR[i]=BAR_NUM[i]*54+540*1+ BaseAddr;
			}
		break;
		case 1:
			BAR_PIC_ADDR[2]=BAR_NUM[2]*54+540*1+ BaseAddr;
			BAR_PIC_ADDR[3]=BAR_NUM[3]*54+540*2+ BaseAddr;
			BAR_PIC_ADDR[4]=BAR_NUM[4]*54+540*1+ BaseAddr;
			BAR_PIC_ADDR[5]=BAR_NUM[5]*54+540*2+ BaseAddr;
			BAR_PIC_ADDR[6]=BAR_NUM[6]*54+540*2+ BaseAddr;
		break;
		case 2:
			BAR_PIC_ADDR[2]=BAR_NUM[2]*54+540*1+ BaseAddr;
			BAR_PIC_ADDR[3]=BAR_NUM[3]*54+540*2+ BaseAddr;
			BAR_PIC_ADDR[4]=BAR_NUM[4]*54+540*2+ BaseAddr;
			BAR_PIC_ADDR[5]=BAR_NUM[5]*54+540*1+ BaseAddr;
			BAR_PIC_ADDR[6]=BAR_NUM[6]*54+540*2+ BaseAddr;
		break;
		case 3:
			BAR_PIC_ADDR[2]=BAR_NUM[2]*54+540*1+ BaseAddr;
			BAR_PIC_ADDR[3]=BAR_NUM[3]*54+540*2+ BaseAddr;
			BAR_PIC_ADDR[4]=BAR_NUM[4]*54+540*2+ BaseAddr;
			BAR_PIC_ADDR[5]=BAR_NUM[5]*54+540*2+ BaseAddr;
			BAR_PIC_ADDR[6]=BAR_NUM[6]*54+540*1+ BaseAddr;
		break;
		case 4:
			BAR_PIC_ADDR[2]=BAR_NUM[2]*54+540*2+ BaseAddr;
			BAR_PIC_ADDR[3]=BAR_NUM[3]*54+540*1+ BaseAddr;
			BAR_PIC_ADDR[4]=BAR_NUM[4]*54+540*1+ BaseAddr;
			BAR_PIC_ADDR[5]=BAR_NUM[5]*54+540*2+ BaseAddr;
			BAR_PIC_ADDR[6]=BAR_NUM[6]*54+540*2+ BaseAddr;
		break;
		case 5:
			BAR_PIC_ADDR[2]=BAR_NUM[2]*54+540*2+ BaseAddr;
			BAR_PIC_ADDR[3]=BAR_NUM[3]*54+540*2+ BaseAddr;
			BAR_PIC_ADDR[4]=BAR_NUM[4]*54+540*1+ BaseAddr;
			BAR_PIC_ADDR[5]=BAR_NUM[5]*54+540*1+ BaseAddr;
			BAR_PIC_ADDR[6]=BAR_NUM[6]*54+540*2+ BaseAddr;
		break;
		case 6:
			BAR_PIC_ADDR[2]=BAR_NUM[2]*54+540*2+ BaseAddr;
			BAR_PIC_ADDR[3]=BAR_NUM[3]*54+540*2+ BaseAddr;
			BAR_PIC_ADDR[4]=BAR_NUM[4]*54+540*2+ BaseAddr;
			BAR_PIC_ADDR[5]=BAR_NUM[5]*54+540*1+ BaseAddr;
			BAR_PIC_ADDR[6]=BAR_NUM[6]*54+540*1+ BaseAddr;
		break;
		case 7:
			BAR_PIC_ADDR[2]=BAR_NUM[2]*54+540*2+ BaseAddr;
			BAR_PIC_ADDR[3]=BAR_NUM[3]*54+540*1+ BaseAddr;
			BAR_PIC_ADDR[4]=BAR_NUM[4]*54+540*2+ BaseAddr;
			BAR_PIC_ADDR[5]=BAR_NUM[5]*54+540*1+ BaseAddr;
			BAR_PIC_ADDR[6]=BAR_NUM[6]*54+540*2+ BaseAddr;
		break;
		case 8:
			BAR_PIC_ADDR[2]=BAR_NUM[2]*54+540*2+ BaseAddr;
			BAR_PIC_ADDR[3]=BAR_NUM[3]*54+540*1+ BaseAddr;
			BAR_PIC_ADDR[4]=BAR_NUM[4]*54+540*2+ BaseAddr;
			BAR_PIC_ADDR[5]=BAR_NUM[5]*54+540*2+ BaseAddr;
			BAR_PIC_ADDR[6]=BAR_NUM[6]*54+540*1+ BaseAddr;
		break;
		case 9:
			BAR_PIC_ADDR[2]=BAR_NUM[2]*54+540*2+ BaseAddr;
			BAR_PIC_ADDR[3]=BAR_NUM[3]*54+540*2+ BaseAddr;
			BAR_PIC_ADDR[4]=BAR_NUM[4]*54+540*1+ BaseAddr;
			BAR_PIC_ADDR[5]=BAR_NUM[5]*54+540*2+ BaseAddr;
			BAR_PIC_ADDR[6]=BAR_NUM[6]*54+540*1+ BaseAddr;
		break;
	}
	BAR_PIC_ADDR[7]=BAR_NUM[7]*54+540*3+ BaseAddr;
	for(i=8;i<=11;i++)
	{
		BAR_PIC_ADDR[i]=BAR_NUM[i]*54+540*4+ BaseAddr;
	}
	BAR_PIC_ADDR[12]=BAR_NUM[12]*54+540*5+ BaseAddr;
	
	memcpy(BAR_NUM,BAR_PIC_ADDR,140);	
	return BAR_PIC_ADDR[0];
}












 
u32 GT32L32_GetBarCode_128(u8	*BAR_NUM,u8	flag)
{
  u32 BaseAddr=0x479C7A;
  u8 i;
  for(i=0;i<7;i++) 
	{
     switch(flag)
		{  
		case 1 :
			 if(i==0)
			 {
				 BAR_PIC_ADDR[i]=103*40+BaseAddr;
			 }
			 else if(i==1||i==2||i==3||i==4)           
			 {
				 BAR_PIC_ADDR[i]=BAR_NUM[i-1]*40+BaseAddr;
			 }
			 else if(i==5)
			 {
				 BAR_PIC_ADDR[i]=95*40+BaseAddr;
			 }
			 else if(i==6)
			 {
				 BAR_PIC_ADDR[i]=106*40+BaseAddr;
			 }
			 break;
     
		case 2 :
			if(i==0)
			{
				BAR_PIC_ADDR[i]=104*40+BaseAddr;
			}
			else if(i==1||i==2||i==3||i==4)           
			{
				BAR_PIC_ADDR[i]=BAR_NUM[i-1]*40+BaseAddr;
			}
			else if(i==5)
			{
				BAR_PIC_ADDR[i]=95*40+BaseAddr;
			}
			else if(i==6)
			{
				BAR_PIC_ADDR[i]=106*40+BaseAddr;
			}
			break;
   	       
		case 3 :
			if(i==0)
			{
				BAR_PIC_ADDR[i]=105*40+BaseAddr;
			}
			else if(i==1||i==2||i==3||i==4)           
			{
				BAR_PIC_ADDR[i]=BAR_NUM[i-1]*40+BaseAddr;
			}
			else if(i==5)
			{
				BAR_PIC_ADDR[i]=95*40+BaseAddr;
			}
			else if(i==6)
			{
				BAR_PIC_ADDR[i]=106*40+BaseAddr;
			}
			break;
   
     default:
     break;
		}
	}
	return BAR_PIC_ADDR[0];
}










  

u16 GT32L32_U2G_13(u16 Unicode) 
{
	u16 GB_Code; 
	u32 i; 
	u16 UG[]={	0x3000,0x3001,0x3002,0x00b7,0x02c9,0x02c7,0x00a8,
							0x3003,0x3005,0x2014, 0xff5e,0x2016,0x2026,0x2018,0x2019,0x201c,
							0x201d,0x3014,0x3015,0x3008, 0x3009,0x300a,0x300b,0x300c,0x300d,
							0x300e,0x300f,0x3016,0x3017,0x3010, 0x3011,0x00b1,0x00d7,0x00f7,
							0x2236,0x2227,0x2228,0x2211,0x220f,0x222a, 0x2229,0x2208,0x2237,
							0x221a,0x22a5,0x2225,0x2220,0x2312,0x2299,0x222b, 0x222e,0x2261,
							0x224c,0x2248,0x223d,0x221d,0x2260,0x226e,0x226f,0x2264, 0x2265,
							0x221e,0x2235,0x2234,0x2642,0x2640,0x00b0,0x2032,0x2033,0x2103,
							0xff04,0x00a4,0xffe0,0xffe1,0x2030,0x00a7,0x2116,0x2606,0x2605,
							0x25cb, 0x25cf,0x25ce,0x25c7,0x25c6,0x25a1,0x25a0,0x25b3,0x25b2,
							0x203b,0x2192, 0x2190,0x2191,0x2193,0x3013
						}; 

	if(Unicode<=0xffe5&&Unicode>=0xff01)
	{ 
		if(Unicode==0xff04) 
			GB_Code=0xa1e7;
		if(Unicode==0xff5e) 
			GB_Code=0xa1ab; 
		if(Unicode==0xffe0) 
			GB_Code=0xa1e9; 
		if(Unicode==0xffe1) 
			GB_Code=0xa1ea; 
		if(Unicode==0xffe3) 
			GB_Code=0xa3fe; 
		if(Unicode==0xffe5) 
			GB_Code=0xa3a4; 
		else
			GB_Code=Unicode-0xff01+0xa3a1; 
	} 
	if(Unicode<=0x3013) 
	{ 
		for(i=0;i<94;i++) 
		{ 
			if(Unicode==UG[i]) 
			GB_Code=0xa1a1+i; 
		} 
	}
	GBCode[0]=GB_Code>>8;
	GBCode[1]=GB_Code&0xff;
	return GB_Code;
}










 
u32 GT32L32_UNICODE_To_GBK(u16 unicode,u8 *GetBuffer)
{
	u32 BaseAdd=0x46A90E;
	u32 Address,U_Start_Addr;
	if(unicode<=0x0451&&unicode>=0x00a0) 
	{
		U_Start_Addr	=	0;
		Address= U_Start_Addr +(unicode-0x00a0)*2; 
	} 
	else if(unicode<=0x2642&&unicode>=0x2010) 
	{ 
		U_Start_Addr =1892; 
		Address= U_Start_Addr +(unicode-0x2010)*2; 
	} 
	else if(unicode<=0x33d5&&unicode>=0x3000) 
	{ 
		U_Start_Addr =5066; 
		Address= U_Start_Addr +(unicode-0x3000)*2; 
	} 
	else if(unicode<=0x9fa5&&unicode>=0x4e00) 
	{ 
		U_Start_Addr =7030; 
		Address= U_Start_Addr +(unicode-0x4e00)*2; 
	} 
	else if(unicode<=0xfe6b&&unicode>=0xfe30) 
	{ 
		U_Start_Addr =48834; 
		Address= U_Start_Addr +(unicode-0xfe30)*2; 
	} 
	else if(unicode<=0xff5e&&unicode>=0xff01) 
	{ 
		U_Start_Addr =48954; 
		Address= U_Start_Addr +(unicode-0xff01)*2; 
	} 
	else if(unicode<=0xffe5&&unicode>=0xffe0) 
	{ 
		U_Start_Addr =49142; 
		Address= U_Start_Addr +(unicode-0xffe0)*2; 
	} 
	else if (unicode<=0xFA29&&unicode>=0xF92C) 
	{ 
		U_Start_Addr =49312; 
		Address= U_Start_Addr +(unicode-0xF92C)*2; 
	} 
	else if(unicode<=0xE864&&unicode>=0xE816) 
	{ 
		U_Start_Addr =49820; 
		Address= U_Start_Addr +(unicode-0xE816)*2; 
	}
	else if(unicode<=0x2ECA&&unicode>=0x2E81) 
	{ 
		U_Start_Addr =49978; 
		Address= U_Start_Addr +(unicode-0x2E81)*2; 
	} 
	else if(unicode<=0x49B7&&unicode>=0x4947) 
	{ 
		U_Start_Addr =50126; 
		Address= U_Start_Addr +(unicode-0x4947)*2; 
	} 
	else if(unicode<=0x4DAE&&unicode>=0x4C77) 
	{ 
		U_Start_Addr =50352; 
		Address= U_Start_Addr +(unicode-0x4C77)*2; 
	} 
	else if(unicode<=0x3CE0&&unicode>=0x3447) 
	{ 
		U_Start_Addr =50976; 
		Address= U_Start_Addr +(unicode-0x3447)*2; 
	} 
	else if(unicode<=0x478D&&unicode>=0x4056) 
	{ 
		U_Start_Addr =55380; 
		Address= U_Start_Addr +(unicode-0x4056)*2; 
	} 
	Address+=BaseAdd;
	return Address; 
}






 
u32 GT32L32_BIG5_To_GBK(u16 BIG5_Code,u8 *GetBuffer) 
{
	u32 Address,part_addr,BaseAddr=0x7F1E10;
	u8 TMP,BIG5_MSB,BIG5_LSB; 
	BIG5_MSB= BIG5_Code >>8; 
	BIG5_LSB= BIG5_Code &0x00ff; 

	if(BIG5_MSB>=0xa1&&BIG5_MSB<=0xa3)
	{ 
		part_addr=0; 
		TMP=0xa1; 
	} 
	else if(BIG5_MSB>=0xa4&&BIG5_MSB<=0xc6) 
	{ 
		part_addr=816; 
		TMP=0xa4; 
	} 
	else if(BIG5_MSB>=0xc9&&BIG5_MSB<=0xf9) 
	{ 
		part_addr=11618; TMP=0xc9; 
	}
	if(BIG5_LSB<=0x7e&&BIG5_LSB>=0x40) 
	{ 
		Address=part_addr+((BIG5_MSB-TMP)*157+BIG5_LSB-0x40)*2+BaseAddr; 
	}
	else if(BIG5_LSB<=0xfe&&BIG5_LSB>=0xa1) 
	{ 
		Address=part_addr+((BIG5_MSB-TMP)*157+BIG5_LSB-0xa1+63)*2+BaseAddr; 
	}
	return Address; 
}









 
u8 GT32L32_ReadStatus(GT32L32Def *pInfo)
{
	
	u8	ChipStatus=0;
	u8	Address=0x05;	
	
	GPIO_ResetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1000)),((u16)0x0040));
	SPI_Cmd(pInfo->SPI.Port.SPIx, ENABLE);
	
	SPI_ReadWriteByteSPI(&pInfo->SPI,Address);						
	
	
	ChipStatus=SPI_ReadWriteByteSPI(&pInfo->SPI,0XFF);

	
	GPIO_SetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1000)),((u16)0x0040));
	SPI_Cmd(pInfo->SPI.Port.SPIx, DISABLE);

	return ChipStatus;
}








 
void GT32L32_ChipErase(GT32L32Def *pInfo)
{
	
	u32 i=0;
	u8	len=255;
	u8	Address=0x60;	
	
	GPIO_ResetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1000)),((u16)0x0040));
	SPI_Cmd(pInfo->SPI.Port.SPIx, ENABLE);

	SPI_ReadWriteByteSPI(&pInfo->SPI,Address);						

	for(i=0;i<len;i++)
	{
	 SPI_ReadWriteByteSPI(&pInfo->SPI,0XFF);
	}
	
	GPIO_SetBits(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1000)),((u16)0x0040));
	SPI_Cmd(pInfo->SPI.Port.SPIx,DISABLE);
}








 
u16 GT32L32_ReadBuffer(
												u32 Address,					  
												u32 lengh,						  
                        u8 *ReadBuffer				  
											)
{
	
	u32 i=0;
	

	SPI_CS_LOW(pSPI);
	Address=Address|0x03000000;		
	

	SPI_ReadWriteByteSPI(pSPI,Address>>24);				
	SPI_ReadWriteByteSPI(pSPI,Address>>16);				
	SPI_ReadWriteByteSPI(pSPI,Address>>8);				
	SPI_ReadWriteByteSPI(pSPI,Address);						
	



	for(i=0;i<lengh;i++)
	{
		ReadBuffer[i]=SPI_ReadWriteByteSPI(pSPI,0XFF);	
	}
	
	SPI_CS_HIGH(pSPI);



	return lengh;	
}









 
u32 GT32L32_GetAntennaCode(u8	NUM,u8 *GetBuffer)
{
  u32 lengh=24;
	u32 Address,BaseAdd=0x47AD32;  
	Address=NUM*24+BaseAdd;

  GT32L32_ReadBuffer(Address,lengh,GetBuffer);		
  
	return lengh;
}









 
u32 GT32L32_GetBatteryCode(u8	NUM,u8 *GetBuffer)
{
  u32 lengh=24;
	u32 Address, BaseAdd=0x47ADAA;
	Address=BaseAdd+NUM*24;
  
  GT32L32_ReadBuffer(Address,lengh,GetBuffer);		
  
	return lengh;
}








 
u16 GT32L32_GetCode(
												u8 font,								
												u16 word,								
                        u8 *ReadBuffer				  
											)
{
	
	u32 i=0;
	u32 Address=0;
	u32 lengh=0;
	
	if(word>>8>=0x80)
	{
		Address	=	GT32L32_GetAddress(font, (u8)(word>>8), (u8)word, 0, 0);		
		lengh= GT32L32_GetBufferLen(font, (u8)(word>>8), (u8)word, 0, 0);			
	}
	else
	{
		Address	=	GT32L32_GetAddress(font, (u8)word, 0, 0, 0);			
		lengh= GT32L32_GetBufferLen(font, (u8)word, 0, 0, 0);			
	}	
  GT32L32_ReadBuffer(Address,lengh,ReadBuffer);		
	return lengh;
}

 
 
 


