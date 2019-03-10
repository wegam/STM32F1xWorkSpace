#line 1 "..\\..\\Driver\\WOW\\SCR\\STM32_EXTI.C"













 


#line 1 "..\\..\\Driver\\WOW\\INC\\STM32_EXTI.H"













 






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



 
#line 22 "..\\..\\Driver\\WOW\\INC\\STM32_EXTI.H"

typedef struct _Trigger_Line
{
	unsigned short Trigger_Line0:1;
	unsigned short Trigger_Line1:1;
	unsigned short Trigger_Line2:1;
	unsigned short Trigger_Line3:1;
	unsigned short Trigger_Line4:1;
	unsigned short Trigger_Line5:1;
	unsigned short Trigger_Line6:1;
	unsigned short Trigger_Line7:1;
	unsigned short Trigger_Line8:1;
	unsigned short Trigger_Line9:1;
	unsigned short Trigger_Line10:1;
	unsigned short Trigger_Line11:1;
	unsigned short Trigger_Line12:1;
	unsigned short Trigger_Line13:1;
	unsigned short Trigger_Line14:1;
	unsigned short Trigger_Line15:1;
}Trigger_LineType;

extern Trigger_LineType Trigger_Line;


void EXTI_Configuration_ITR		(GPIO_TypeDef* GPIOx, u16 GPIO_Pin);		
void EXTI_Configuration_ITF		(GPIO_TypeDef* GPIOx, u16 GPIO_Pin);		
void EXTI_Configuration_ITRF	(GPIO_TypeDef* GPIOx, u16 GPIO_Pin);		




void EXTI_Server(void);



#line 18 "..\\..\\Driver\\WOW\\SCR\\STM32_EXTI.C"

#line 1 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_exti.h"














 

 



 
#line 23 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_exti.h"

 
 
typedef enum
{
  EXTI_Mode_Interrupt = 0x00,
  EXTI_Mode_Event = 0x04
}EXTIMode_TypeDef;


                            
 
typedef enum
{
  EXTI_Trigger_Rising = 0x08,
  EXTI_Trigger_Falling = 0x0C,  
  EXTI_Trigger_Rising_Falling = 0x10
}EXTITrigger_TypeDef;





 
typedef struct
{
  u32 EXTI_Line;
  EXTIMode_TypeDef EXTI_Mode;
  EXTITrigger_TypeDef EXTI_Trigger;
  FunctionalState EXTI_LineCmd;
}EXTI_InitTypeDef;

 
 
#line 80 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_exti.h"



#line 93 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_exti.h"
                                 
 
 
void EXTI_DeInit(void);
void EXTI_Init(EXTI_InitTypeDef* EXTI_InitStruct);
void EXTI_StructInit(EXTI_InitTypeDef* EXTI_InitStruct);
void EXTI_GenerateSWInterrupt(u32 EXTI_Line);
FlagStatus EXTI_GetFlagStatus(u32 EXTI_Line);
void EXTI_ClearFlag(u32 EXTI_Line);
ITStatus EXTI_GetITStatus(u32 EXTI_Line);
void EXTI_ClearITPendingBit(u32 EXTI_Line);



 
#line 20 "..\\..\\Driver\\WOW\\SCR\\STM32_EXTI.C"
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



 
#line 21 "..\\..\\Driver\\WOW\\SCR\\STM32_EXTI.C"
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



 
#line 22 "..\\..\\Driver\\WOW\\SCR\\STM32_EXTI.C"

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










#line 24 "..\\..\\Driver\\WOW\\SCR\\STM32_EXTI.C"


Trigger_LineType Trigger_Line;









 
void EXTI_ClockConf(GPIO_TypeDef* GPIOx,						
										u16 GPIO_Pin_x									
										)		
{
	 
  ((void)0);
  ((void)0);
	switch (*(u32*)&GPIOx)
	{
		
		case ((((u32)0x40000000) + 0x10000) + 0x0800):

			if(((GPIO_Pin_x&((u16)0x2000))==((u16)0x2000))||((GPIO_Pin_x&((u16)0x4000))==((u16)0x4000))||((GPIO_Pin_x&((u16)0x8000))==((u16)0x8000))||(GPIO_Pin_x==((u16)0xFFFF)))
			{
				RCC_APB2PeriphClockCmd(((u32)0x00000004)|((u32)0x00000001), ENABLE);
				
				GPIO_PinRemapConfig(((u32)0x00300200),ENABLE);		
			}
			else
				RCC_APB2PeriphClockCmd(((u32)0x00000004), ENABLE);
			break;
		
		case ((((u32)0x40000000) + 0x10000) + 0x0C00):
			if(((GPIO_Pin_x&((u16)0x0008))==((u16)0x0008))||((GPIO_Pin_x&((u16)0x0010))==((u16)0x0010))||(GPIO_Pin_x==((u16)0xFFFF)))
			{
				RCC_APB2PeriphClockCmd(((u32)0x00000008)|((u32)0x00000001), ENABLE);
				GPIO_PinRemapConfig(((u32)0x00300200),ENABLE);				
			}
			else
				RCC_APB2PeriphClockCmd(((u32)0x00000008), ENABLE);
			break;
		
		case ((((u32)0x40000000) + 0x10000) + 0x1000):
			RCC_APB2PeriphClockCmd(((u32)0x00000010), ENABLE);
			if(((GPIO_Pin_x&((u16)0x4000))==((u16)0x4000))||((GPIO_Pin_x&((u16)0x8000))==((u16)0x8000)))
				RCC_APB2PeriphClockCmd(((u32)0x00000010) |((u32)0x00000001), ENABLE);
			break;
		
		case ((((u32)0x40000000) + 0x10000) + 0x1400):
			RCC_APB2PeriphClockCmd(((u32)0x00000020), ENABLE);
			break;
		
		case ((((u32)0x40000000) + 0x10000) + 0x1800):
			RCC_APB2PeriphClockCmd(((u32)0x00000040), ENABLE);
			break;
		
		case ((((u32)0x40000000) + 0x10000) + 0x1C00):
			RCC_APB2PeriphClockCmd(((u32)0x00000080), ENABLE);
			break;
		
		case ((((u32)0x40000000) + 0x10000) + 0x2000):
			RCC_APB2PeriphClockCmd(((u32)0x00000100), ENABLE);
			break;		
		default: break;		
	}
}








 
void EXTI_GPIOConf(GPIO_TypeDef* GPIOx,						
										u16 GPIO_Pin_x,								
										GPIOMode_TypeDef GPIO_Mode		
										)		
{
	
	GPIO_InitTypeDef	GPIO_InitStructure;
	 
  ((void)0);
  ((void)0);
	
	GPIO_InitStructure.GPIO_Pin  		= GPIO_Pin_x;
  GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_2MHz;					
  GPIO_InitStructure.GPIO_Mode 		= GPIO_Mode;								
	
	GPIO_Init(GPIOx,&GPIO_InitStructure);												
}








 
void EXTI_LineConf(GPIO_TypeDef* GPIOx,						
										u16 GPIO_Pin_x								
										)		
{
	u8 GPIO_PortSource=0;
	u8 GPIO_PinSource=0;
	
	 
  ((void)0);
  ((void)0);
	
	
	switch (*(u32*)&GPIOx)
	{
		
		case ((((u32)0x40000000) + 0x10000) + 0x0800):
			GPIO_PortSource	=	((u8)0x00);
			break;
		
		case ((((u32)0x40000000) + 0x10000) + 0x0C00):
			GPIO_PortSource	=	((u8)0x01);
			break;
		
		case ((((u32)0x40000000) + 0x10000) + 0x1000):
			GPIO_PortSource	=	((u8)0x02);
			break;
		
		case ((((u32)0x40000000) + 0x10000) + 0x1400):
			GPIO_PortSource	=	((u8)0x03);
			break;
		
		case ((((u32)0x40000000) + 0x10000) + 0x1800):
			GPIO_PortSource	=	((u8)0x04);
			break;
		
		case ((((u32)0x40000000) + 0x10000) + 0x1C00):
			GPIO_PortSource	=	((u8)0x05);
			break;
		
		case ((((u32)0x40000000) + 0x10000) + 0x2000):
			GPIO_PortSource	=	((u8)0x06);
			break;
		default:	
			break;
	}
	
	switch ((u16)GPIO_Pin_x)
	{
		case ((u16)0x0001):
			GPIO_PinSource	=	((u8)0x00);
			break;
		case ((u16)0x0002):
			GPIO_PinSource	=	((u8)0x01);
			break;
		case ((u16)0x0004):
			GPIO_PinSource	=	((u8)0x02);
			break;
		case ((u16)0x0008):
			GPIO_PinSource	=	((u8)0x03);
			break;
		case ((u16)0x0010):
			GPIO_PinSource	=	((u8)0x04);
			break;
		case ((u16)0x0020):
			GPIO_PinSource	=	((u8)0x05);
			break;
		case ((u16)0x0040):
			GPIO_PinSource	=	((u8)0x06);
			break;
		case ((u16)0x0080):
			GPIO_PinSource	=	((u8)0x07);
			break;
		case ((u16)0x0100):
			GPIO_PinSource	=	((u8)0x08);
			break;
		case ((u16)0x0200):
			GPIO_PinSource	=	((u8)0x09);
			break;
		case ((u16)0x0400):
			GPIO_PinSource	=	((u8)0x0A);
			break;
		case ((u16)0x0800):
			GPIO_PinSource	=	((u8)0x0B);
			break;
		case ((u16)0x1000):
			GPIO_PinSource	=	((u8)0x0C);
			break;
		case ((u16)0x2000):
			GPIO_PinSource	=	((u8)0x0D);
			break;
		case ((u16)0x4000):
			GPIO_PinSource	=	((u8)0x0E);
			break;
		case ((u16)0x8000):
			GPIO_PinSource	=	((u8)0x0F);
			break;
		
		default:	
			break;
	}
	
	GPIO_EXTILineConfig(GPIO_PortSource,GPIO_PinSource);
}








 
void EXTI_TTMConf(u16 GPIO_Pin_x,										
									EXTITrigger_TypeDef EXTI_Trigger	
									)		
{
	u32 EXTI_Line;
	EXTI_InitTypeDef EXTI_Initstructure;
	((void)0);
	
	switch ((u16)GPIO_Pin_x)
	{
		case ((u16)0x0001):
			EXTI_Line	=	((u32)0x00001);
			break;
		case ((u16)0x0002):
			EXTI_Line	=	((u32)0x00002);
			break;
		case ((u16)0x0004):
			EXTI_Line	=	((u32)0x00004);
			break;
		case ((u16)0x0008):
			EXTI_Line	=	((u32)0x00008);
			break;
		case ((u16)0x0010):
			EXTI_Line	=	((u32)0x00010);
			break;
		case ((u16)0x0020):
			EXTI_Line	=	((u32)0x00020);
			break;
		case ((u16)0x0040):
			EXTI_Line	=	((u32)0x00040);
			break;
		case ((u16)0x0080):
			EXTI_Line	=	((u32)0x00080);
			break;
		case ((u16)0x0100):
			EXTI_Line	=	((u32)0x00100);
			break;
		case ((u16)0x0200):
			EXTI_Line	=	((u32)0x00200);
			break;
		case ((u16)0x0400):
			EXTI_Line	=	((u32)0x00400);
			break;
		case ((u16)0x0800):
			EXTI_Line	=	((u32)0x00800);
			break;
		case ((u16)0x1000):
			EXTI_Line	=	((u32)0x01000);
			break;
		case ((u16)0x2000):
			EXTI_Line	=	((u32)0x02000);
			break;
		case ((u16)0x4000):
			EXTI_Line	=	((u32)0x04000);
			break;
		case ((u16)0x8000):
			EXTI_Line	=	((u32)0x08000);
			break;
		
		default:	
			break;
	}
	EXTI_Initstructure.EXTI_Line=EXTI_Line;												
	EXTI_Initstructure.EXTI_Mode=EXTI_Mode_Interrupt;							
	EXTI_Initstructure.EXTI_Trigger=EXTI_Trigger;									
	EXTI_Initstructure.EXTI_LineCmd=ENABLE;												
	EXTI_Init(&EXTI_Initstructure);
	
	EXTI_GenerateSWInterrupt(EXTI_Line);													
	EXTI_ClearITPendingBit(EXTI_Line);
}








 
void EXTI_NVICConf(GPIO_TypeDef* GPIOx,						
									u16 GPIO_Pin_x								
									)		
{
	u8 EXTI_IRQChannel;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
  ((void)0);
	((void)0);
	
	
	switch ((u16)GPIO_Pin_x)
	{
		case ((u16)0x0001):
			EXTI_IRQChannel	=	((u8)0x06);
			break;
		case ((u16)0x0002):
			EXTI_IRQChannel	=	((u8)0x07);
			break;
		case ((u16)0x0004):
			EXTI_IRQChannel	=	((u8)0x08);
			break;
		case ((u16)0x0008):
			EXTI_IRQChannel	=	((u8)0x09);
			break;
		case ((u16)0x0010):
			EXTI_IRQChannel	=	((u8)0x0A);
			break;
		
		case ((u16)0x0020):
			EXTI_IRQChannel	=	((u8)0x17);
			break;
		case ((u16)0x0040):
			EXTI_IRQChannel	=	((u8)0x17);
			break;
		case ((u16)0x0080):
			EXTI_IRQChannel	=	((u8)0x17);
			break;
		case ((u16)0x0100):
			EXTI_IRQChannel	=	((u8)0x17);
			break;
		case ((u16)0x0200):
			EXTI_IRQChannel	=	((u8)0x17);
			break;
		
		case ((u16)0x0400):
			EXTI_IRQChannel	=	((u8)0x28);
			break;
		case ((u16)0x0800):
			EXTI_IRQChannel	=	((u8)0x28);
			break;
		case ((u16)0x1000):
			EXTI_IRQChannel	=	((u8)0x28);
			break;
		case ((u16)0x2000):
			EXTI_IRQChannel	=	((u8)0x28);
			break;
		case ((u16)0x4000):
			EXTI_IRQChannel	=	((u8)0x28);
			break;
		case ((u16)0x8000):
			EXTI_IRQChannel	=	((u8)0x28);
			break;
		
		default:	
			break;
	}
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI_IRQChannel;					
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;			
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;						
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								
	NVIC_Init(&NVIC_InitStructure);

}








 
void EXTI_Configuration_ITR(GPIO_TypeDef* GPIOx,						
														u16 GPIO_Pin_x									
														)		
{
	 
  ((void)0);
	((void)0);
	
	EXTI_ClockConf(GPIOx,GPIO_Pin_x);								
	EXTI_GPIOConf(GPIOx,GPIO_Pin_x,GPIO_Mode_IPD);	
	EXTI_LineConf(GPIOx,GPIO_Pin_x);								
	EXTI_TTMConf(GPIO_Pin_x,EXTI_Trigger_Rising);		
	EXTI_NVICConf(GPIOx,GPIO_Pin_x);								
}








 
void EXTI_Configuration_ITF(GPIO_TypeDef* GPIOx,						
														u16 GPIO_Pin_x									
														)		
{
	 
  ((void)0);
	((void)0);
	
	EXTI_ClockConf(GPIOx,GPIO_Pin_x);								
	EXTI_GPIOConf(GPIOx,GPIO_Pin_x,GPIO_Mode_IPU);	
	EXTI_LineConf(GPIOx,GPIO_Pin_x);								
	EXTI_TTMConf(GPIO_Pin_x,EXTI_Trigger_Falling);	
	EXTI_NVICConf(GPIOx,GPIO_Pin_x);								
}








 
void EXTI_Configuration_ITRF(GPIO_TypeDef* GPIOx,						
														u16 GPIO_Pin_x									
														)		
{
	 
  ((void)0);
	((void)0);
	
	EXTI_ClockConf(GPIOx,GPIO_Pin_x);												
	EXTI_GPIOConf(GPIOx,GPIO_Pin_x,GPIO_Mode_IN_FLOATING);	
	EXTI_LineConf(GPIOx,GPIO_Pin_x);												
	EXTI_TTMConf(GPIO_Pin_x,EXTI_Trigger_Rising_Falling);		
	EXTI_NVICConf(GPIOx,GPIO_Pin_x);												
}







 
void EXTI_Event_Configuration(void)
{
	if(EXTI_GetITStatus(((u32)0x00001)))
	{
		Trigger_Line.Trigger_Line0	=	1;

	}
	else if(EXTI_GetITStatus(((u32)0x00002)))
	{
		Trigger_Line.Trigger_Line1	=	1;

	}
	else if(EXTI_GetITStatus(((u32)0x00004)))
	{
		Trigger_Line.Trigger_Line2	=	1;

	}
	else if(EXTI_GetITStatus(((u32)0x00008)))
	{
		Trigger_Line.Trigger_Line3	=	1;

	}
	else if(EXTI_GetITStatus(((u32)0x00010)))
	{
		Trigger_Line.Trigger_Line4	=	1;

	}
	else if(EXTI_GetITStatus(((u32)0x00020)))
	{
		Trigger_Line.Trigger_Line5	=	1;

	}
	else if(EXTI_GetITStatus(((u32)0x00040)))
	{
		Trigger_Line.Trigger_Line6	=	1;

	}
	else if(EXTI_GetITStatus(((u32)0x00080)))
	{
		Trigger_Line.Trigger_Line7	=	1;

	}
	else if(EXTI_GetITStatus(((u32)0x00100)))
	{
		Trigger_Line.Trigger_Line8	=	1;

	}
	else if(EXTI_GetITStatus(((u32)0x00200)))
	{
		Trigger_Line.Trigger_Line9	=	1;

	}
	else if(EXTI_GetITStatus(((u32)0x00400)))
	{
		Trigger_Line.Trigger_Line10	=	1;

	}
	else if(EXTI_GetITStatus(((u32)0x00800)))
	{
		Trigger_Line.Trigger_Line11	=	1;

	}
	else if(EXTI_GetITStatus(((u32)0x01000)))
	{
		Trigger_Line.Trigger_Line12	=	1;

	}
	else if(EXTI_GetITStatus(((u32)0x02000)))
	{
		Trigger_Line.Trigger_Line13	=	1;

	}
	else if(EXTI_GetITStatus(((u32)0x04000)))
	{
		Trigger_Line.Trigger_Line14	=	1;

	}
	else if(EXTI_GetITStatus(((u32)0x08000)))
	{
		Trigger_Line.Trigger_Line15	=	1;

	}
}







 
void EXTI_Server(void)
{
	unsigned short temp	=	0;
	EXTI_Event_Configuration();
	WOW_Server();				


	Trigger_Line	=	*(Trigger_LineType*)&temp;			
	EXTI_ClearITPendingBit(((u32)0x00001));
	EXTI_ClearITPendingBit(((u32)0x00002));
	EXTI_ClearITPendingBit(((u32)0x00004));
	EXTI_ClearITPendingBit(((u32)0x00008));
	EXTI_ClearITPendingBit(((u32)0x00010));
	EXTI_ClearITPendingBit(((u32)0x00020));
	EXTI_ClearITPendingBit(((u32)0x00040));
	EXTI_ClearITPendingBit(((u32)0x00080));
	EXTI_ClearITPendingBit(((u32)0x00100));
	EXTI_ClearITPendingBit(((u32)0x00200));
	EXTI_ClearITPendingBit(((u32)0x00400));
	EXTI_ClearITPendingBit(((u32)0x00800));
	EXTI_ClearITPendingBit(((u32)0x01000));
	EXTI_ClearITPendingBit(((u32)0x02000));
	EXTI_ClearITPendingBit(((u32)0x04000));
	EXTI_ClearITPendingBit(((u32)0x08000));
}


