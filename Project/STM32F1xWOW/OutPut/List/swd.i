#line 1 "..\\..\\Driver\\Protocol\\swd.c"
#line 1 "..\\..\\Driver\\Protocol\\swd.h"



#line 1 "..\\..\\Driver\\Protocol\\swd_pin.h"




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



 
#line 6 "..\\..\\Driver\\Protocol\\swd_pin.h"
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










#line 7 "..\\..\\Driver\\Protocol\\swd_pin.h"
































































#line 77 "..\\..\\Driver\\Protocol\\swd_pin.h"






 
void SW_PinInit(void);
unsigned long SW_READ_BIT(void);			
void SW_CLOCK_CYCLE(void);						
void SW_WRITE_BIT(unsigned long bit);	

void PIN_DELAY(void);
void DELAY_US(unsigned long us);




#line 5 "..\\..\\Driver\\Protocol\\swd.h"
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






 
#line 6 "..\\..\\Driver\\Protocol\\swd.h"
#line 1 "..\\..\\Driver\\Protocol\\debug_cm.h"



















 












#line 41 "..\\..\\Driver\\Protocol\\debug_cm.h"
	










#line 74 "..\\..\\Driver\\Protocol\\debug_cm.h"







#line 90 "..\\..\\Driver\\Protocol\\debug_cm.h"


#line 107 "..\\..\\Driver\\Protocol\\debug_cm.h"















#line 134 "..\\..\\Driver\\Protocol\\debug_cm.h"


#line 149 "..\\..\\Driver\\Protocol\\debug_cm.h"



















#line 174 "..\\..\\Driver\\Protocol\\debug_cm.h"





#line 7 "..\\..\\Driver\\Protocol\\swd.h"









 





#line 28 "..\\..\\Driver\\Protocol\\swd.h"










 


#line 47 "..\\..\\Driver\\Protocol\\swd.h"









typedef enum	_AddrInc
{
	AddrIncOff		=	0x00,		
	AddrIncSingle	=	0x01,		
	AddrIncPacked	=	0x02		
}AddrIncDef;

typedef enum	_CswSize	
{
	SizeByte		=	0x00,		
	Halfword		=	0x01,		
	SizeWord		=	0x02,		
	Doubleword	=	0x03,		
	Size128Bit	=	0x04,		
	Size256Bit	=	0x05		
}CswSizeDef;
typedef enum	_TrnMode	
{
	TrnNormal		=	0x00,		
	Trnverify		=	0x01,		
	Trncompare	=	0x02,		
	TrnReserved	=	0x03		
}TrnModeDef;

typedef struct _MEMAPCSW		
{
	unsigned long	Size					:3;			
	unsigned long	Reserved0			:1;			
	unsigned long	AddrInc				:2;			
	unsigned long DeviceEn 			:1;			
	unsigned long TrInProg 			:1;			
	unsigned long Mode 					:4;			
	unsigned long Type 					:4;			
	unsigned long Bits					:7;			
	unsigned long SPIDEN				:1;			
	unsigned long Prot					:7;			
	unsigned long DbgSwEnable		:1;			
}MEMAPCSWDef;

typedef struct _MEMAPDRW		
{
	unsigned long	Size					:3;			
	unsigned long	Reserved0			:1;			
	unsigned long	AddrInc				:2;			
	unsigned long DeviceEn 			:1;			
	unsigned long TrInProg 			:1;			
	unsigned long Mode 					:4;			
	unsigned long Type 					:4;			
	unsigned long Bits					:7;			
	unsigned long SPIDEN				:1;			
	unsigned long Prot					:7;			
	unsigned long DbgSwEnable		:1;			
}MEMAPDRWDef;






























typedef struct _DLCR		
{
	unsigned long	Reserved0			:6;			
	unsigned long	Reserved1			:1;			
	unsigned long	Reserved2			:1;			
	unsigned long	TURNROUND			:2;			
	unsigned long	Reserved3			:22;		
}DLCRDef;
typedef struct _DLPIDR		
{
	unsigned long	PROTVSN				:4;			
	unsigned long	Reserved			:24;		
	unsigned long	TINSTANCE			:4;			
}DLPIDRDef;
typedef struct _EVENTSTAT		
{
	unsigned long	EA						:1;			
	unsigned long	Reserved			:31;		
}EVENTSTATDef;
typedef struct _RDBUFF		
{
	unsigned long	EA						:1;			
	unsigned long	Reserved			:31;		
}RDBUFFDef;









typedef struct _TARGETSEL		
{
	unsigned long	SBO						:1;			
	unsigned long	TDESIGNER			:11;		
	unsigned long	TPARTNO				:16;		
	unsigned long TREVISION 		:4;			
}TARGETSELDef;

typedef struct _TARGETID		
{
	unsigned long	RAO						:1;			
	unsigned long	TDESIGNER			:11;		
	unsigned long	TPARTNO				:16;		
	unsigned long TREVISION 		:4;			
}TARGETIDDef;



typedef enum
{
	SWJAckOK		=	0x01,		
	SWJAckWait	=	0x02,		
	SWJAckFault	=	0x04		
}SWJAckDef;
typedef struct _SWJRequest
{
	unsigned char Start 	:1;			
	unsigned char APnDP 	:1;			
	unsigned char RnW 		:1;			
	unsigned char Addr0   :1;			
  unsigned char Addr1   :1;			
	unsigned char Parity 	:1;			
	unsigned char Stop 		:1;			
	unsigned char Park	 	:1;			
}SWJRequestDef;







 

typedef struct
{
    unsigned long r[16];
    unsigned long xpsr;
} DEBUG_STATE;
typedef enum
{
    RESET_HOLD,              
    RESET_PROGRAM,           
    RESET_RUN,               
    RESET_RUN_WITH_DEBUG,    
    disDEBUG,                
    enDEBUG                  
} TARGET_RESET_STATE;

typedef struct
{
	unsigned long breakpoint;
	unsigned long static_base;
	unsigned long stack_pointer;
}FLASH_SYSCALL;















static unsigned char SWJ_ReadDP(unsigned char adr, unsigned long *val);
unsigned char SWJ_WriteDP(unsigned char adr, unsigned long val);
unsigned char SWJ_ReadAP(unsigned long adr, unsigned long *val);
unsigned char SWJ_WriteAP(unsigned long adr, unsigned long val);
unsigned char SWJ_InitDebug(void);
unsigned char SWJ_ReadMem(unsigned long addr, unsigned char *buf, unsigned long len);
unsigned char SWJ_WriteMem(unsigned long addr, unsigned char *buf, unsigned long len);
unsigned char SWJ_SetTargetState(TARGET_RESET_STATE state);
unsigned char swd_flash_syscall_exec(const FLASH_SYSCALL *sysCallParam, unsigned long entry,unsigned long arg1,unsigned long arg2, unsigned long arg3, unsigned long arg4);


unsigned char SWD_TransRequest(unsigned char request);			
unsigned char SWD_TransferOnce(unsigned long request, unsigned long *data);		
unsigned char SWD_Transfer(unsigned long request, unsigned long *data);				
static void SWJ_SendData(uint16_t data);			
void Line_Rest(void);			
static unsigned char SWJ_JTAG2SWD(void);		
static unsigned char SWJ_ReadDP(unsigned char adr, unsigned long *val);		
unsigned char SWJ_WriteDP(unsigned char adr, unsigned long val);		
unsigned char SWJ_ReadAP(unsigned long adr, unsigned long *val);		
unsigned char SWJ_WriteAP(unsigned long adr, unsigned long val);		

static unsigned char SWJ_WriteData(unsigned long addr, unsigned long data);	

static unsigned char SWJ_WriteMem8(unsigned long addr, unsigned char val);	
unsigned char SWJ_WriteMem32(unsigned long addr, unsigned long val);				
static unsigned char SWJ_WriteBlock(unsigned long addr, unsigned char *buf, unsigned long len);		
static unsigned char SWJ_ReadData(unsigned long addr, unsigned long *val);	
static unsigned char SWJ_ReadMem32(unsigned long addr, unsigned long *val);	
static unsigned char SWJ_ReadMem8(unsigned long addr, unsigned char *val);	
static unsigned char SWJ_ReadBlock(unsigned long addr, unsigned char *buf, unsigned long len);		
unsigned char swd_write_memory(unsigned long address, unsigned char *data, unsigned long size);		
unsigned char swd_read_memory(unsigned long address, unsigned char *data, unsigned long size);		
unsigned char SWJ_ReadMem(unsigned long addr, unsigned char *buf, unsigned long len);							
unsigned char SWJ_WriteMem(unsigned long addr, unsigned char *buf, unsigned long len);						
static unsigned char SWJ_WaitUntilHalted(void);			
unsigned char SWJ_SetTargetState(TARGET_RESET_STATE state);			
static unsigned char SWJ_WriteCoreReg(unsigned long n, unsigned long val);		
static unsigned char SWJ_ReadCoreReg(unsigned long n, unsigned long *val);		
unsigned char swd_write_debug_state(DEBUG_STATE *state);		
unsigned char swd_flash_syscall_exec(const FLASH_SYSCALL *sysCallParam, unsigned long entry, unsigned long arg1, unsigned long arg2, unsigned long arg3, unsigned long arg4);	
unsigned char SWJ_InitDebug(void);		
void softdelay(unsigned long us);			

#line 2 "..\\..\\Driver\\Protocol\\swd.c"

#line 4 "..\\..\\Driver\\Protocol\\swd.c"



#line 8 "..\\..\\Driver\\Protocol\\swd.c"






#line 20 "..\\..\\Driver\\Protocol\\swd.c"

 





 




 





 











 
unsigned char SWD_TransRequest(unsigned char request)
{
	unsigned char ack 		= 0;
	unsigned char bit 		= 0;
	unsigned char parity	=	0;
	unsigned char num 		= 0;
  unsigned char temp 		= 0;
  SWJRequestDef *Request=(SWJRequestDef*)&request;
  
  request=request<<1;
	
  temp  = request&0x0F;
	for(num=0;num<4;num++)
	{
    parity  += temp&0x01;
    temp>>=1;
  }
  Request->Start  = 0x01;
  Request->Parity = parity&0x01;  
  Request->Stop   = 0x00;
  Request->Park   = 0x01;
  
	GPIO_Configuration_OPP50 (((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0800)),((u16)0x0400));;		
	((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0800)) ->BSRR = ((u16)0x0400);
  ((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0800)) ->BRR = ((u16)0x0400);
  ((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0800)) ->BSRR = ((u16)0x0400);
	 
	SW_WRITE_BIT(Request->Start);      		
	SW_WRITE_BIT(Request->APnDP);      		
	SW_WRITE_BIT(Request->RnW);        			
	SW_WRITE_BIT(Request->Addr0);      				
	SW_WRITE_BIT(Request->Addr1);      				
	SW_WRITE_BIT(Request->Parity);     		
	SW_WRITE_BIT(Request->Stop);       			
	SW_WRITE_BIT(Request->Park);       			
  
	GPIO_Configuration_IPU(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0800)),((u16)0x0400));;			

	 
	
	
	
	
	SW_CLOCK_CYCLE();
	 	
	for(num = 0; num < 3; num++)
	{
			bit = SW_READ_BIT();		
			ack  |= bit << num;
	}
	return ack;
}









 
unsigned char SWD_TransferOnce(unsigned long request, unsigned long *data)
{
    unsigned long ack = 0;
    unsigned long bit;
    unsigned long val;
    unsigned long parity;
    unsigned long n;

		ack = SWD_TransRequest(request);
  
    switch(ack)
    {
        case (1<<0):			
						
            if(request & (1<<1))   
            {
                val = 0;
                parity = 0;

                for(n = 32; n; n--)
                {
                    bit = SW_READ_BIT();   
                    parity += bit;
                    val >>= 1;
                    val  |= bit << 31;
                }

                bit = SW_READ_BIT();     

                if((parity ^ bit) & 1)
                {
                    ack = (1<<3);		
                }

                if(data) 
									*data = val;

                 
                for(n = 1; n; n--)
                {
                    SW_CLOCK_CYCLE();
                }

                GPIO_Configuration_OPP50 (((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0800)),((u16)0x0400));;		
            }
						
            else     
            {
                 
                for(n = 1; n; n--)
                {
                    SW_CLOCK_CYCLE();
                }

                GPIO_Configuration_OPP50 (((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0800)),((u16)0x0400));;	
                 
                val = *data;
                parity = 0;

                for(n = 32; n; n--)
                {
                    SW_WRITE_BIT(val);  
                    parity += val;
                    val >>= 1;
                }

                SW_WRITE_BIT(parity); 
            }

             
            GPIO_Configuration_OPP50 (((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0800)),((u16)0x0400));;		
            
            for(n = 0; n < 8; n++)
            {
                SW_WRITE_BIT(0);
            }
						((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0800)) ->BSRR = ((u16)0x0400);
            return (ack);

        case (1<<1):
        case (1<<2):

             
            if(0 && ((request & (1<<1)) != 0))
            {
                for(n = 32 + 1; n; n--)
                {
                    SW_CLOCK_CYCLE();   
                }
            }

             
            for(n = 1; n; n--)
            {
                SW_CLOCK_CYCLE();
            }

            GPIO_Configuration_OPP50 (((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0800)),((u16)0x0400));;		

            if(0 && ((request & (1<<1)) == 0))
            {
                ((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0800)) ->BRR = ((u16)0x0200);

                for(n = 32 + 1; n; n--)
                {
                    SW_CLOCK_CYCLE();   
                }
            }

            ((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0800)) ->BSRR = ((u16)0x0400);
            for(n = 0; n < 8; n++)
            {
                SW_WRITE_BIT(0);
            }
            return (ack);

        default:
            break;
    }

     
    for(n = 1 + 32 + 1; n; n--)
    {
        SW_CLOCK_CYCLE();       
    }

    GPIO_Configuration_OPP50 (((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0800)),((u16)0x0400));;		
    
    for(n = 0; n < 8; n++)
    {
        SW_WRITE_BIT(0);
    }
		((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0800)) ->BSRR = ((u16)0x0400);
    return (ack);
}








 
unsigned char SWD_Transfer(unsigned long request, unsigned long *data)
{
    unsigned char i, ack;

    for(i = 0; i < 5; i++)
    {
        ack = SWD_TransferOnce(request, data);		

        
        if(ack != (1<<1))
        {
            return ack;
        }
    }
    return ack;
}











 








 
static void SWJ_SendData(uint16_t data)
{
    unsigned char i;

    for(i = 0; i < 16; i++)
    {
        SW_WRITE_BIT(((data & 0x1) == 1) ? (1) : (0));
        data >>= 1;
    }
}








 
void Line_Rest(void)
{
	unsigned long i;
  GPIO_Configuration_OPP50 (((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0800)),((u16)0x0400));;
	((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0800)) ->BSRR = ((u16)0x0400);
  ((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0800)) ->BRR = ((u16)0x0400);
  ((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0800)) ->BSRR = ((u16)0x0400);
	for(i = 0; i < 51; i++)
	{
		SW_CLOCK_CYCLE();
	}
	
}
















 
static unsigned char SWJ_JTAG2SWD(void)
{
    unsigned long i;
	GPIO_Configuration_OPP50 (((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0800)),((u16)0x0400));;
	((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0800)) ->BSRR = ((u16)0x0400);
	
	Line_Rest();	
	
	SWJ_SendData(0xE79E);
	
	Line_Rest();	
	
	SWJ_SendData(0x6DB7);
	Line_Rest();	
	((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0800)) ->BRR = ((u16)0x0400);
	for(i = 0; i < 16; i++)
	{
			SW_CLOCK_CYCLE();
	}
	((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0800)) ->BSRR = ((u16)0x0400);
	return 0;
}








 
static unsigned char SWJ_ReadDP(unsigned char adr, unsigned long *val)
{
	unsigned long tmp_in;
	unsigned char ack;
	unsigned char err;

	tmp_in = (0) | (1<<1) | (adr & 0x0c);
	ack = SWD_Transfer(tmp_in, val);

	(ack == (1<<0)) ? (err = 0) : (err = 1);
	return err;
}








 
unsigned char SWJ_WriteDP(unsigned char adr, unsigned long val)
{
    unsigned long req;
    unsigned char ack;
    unsigned char err;

    req = (0) | (0<<1) | (adr & 0x0c);		
    ack = SWD_Transfer(req, &val);

    (ack == (1<<0)) ? (err = 0) : (err = 1);
    return err;
}








 
unsigned char SWJ_ReadAP(unsigned long adr, unsigned long *val)
{
    unsigned char tmp_in, ack, err;

    unsigned long apsel = adr & 0xFF000000;
    unsigned long bank_sel = adr & 0x000000F0;

    if(SWJ_WriteDP(0x08, apsel | bank_sel))
    {
        return 1;
    }

    tmp_in = (1) | (1<<1) | (adr & 0x0c);

     
    ack = SWD_Transfer(tmp_in, val);
    ack = SWD_Transfer(tmp_in, val);

    (ack == (1<<0)) ? (err = 0) : (err = 1);
    return err;
}








 
unsigned char SWJ_WriteAP(unsigned long adr, unsigned long val)
{
    unsigned char req, ack, err;

    unsigned long apsel = adr & 0xFF000000;
    unsigned long bank_sel = adr & 0x000000F0;

     
    if(SWJ_WriteDP(0x08, apsel | bank_sel))
    {

    }

     
    req = (1) | (0<<1) | (adr & 0x0c);
    ack = SWD_Transfer(req, &val);

     
    req = (0) | (1<<1) | (0x0C & 0x0c);
    ack = SWD_Transfer(req, 0);
    (ack == (1<<0)) ? (err = 0) : (err = 1);

    return err;
}















 
static unsigned char SWJ_WriteData(unsigned long addr, unsigned long data)
{
    unsigned char req, ack, err;

    SWJ_WriteAP(0x04, addr);

     
    req = (1) | (0<<1) | 0x0C;
    ack = SWD_Transfer(req, &data);

     
    req = (0) | (1<<1) | (0x0C & 0x0c);
    ack = SWD_Transfer(req, 0);

    (ack == (1<<0)) ? (err = 0) : (err = 1);
    return err;
}








 


static unsigned char SWJ_WriteMem8(unsigned long addr, unsigned char val)
{
    unsigned long tmp;
    unsigned char err;

    SWJ_WriteAP(0x00, (0x01000000 | 0x20000000 | 0x02000000 | 0x00000040 | 0x00000010) | 0x00000000);

    tmp = val << ((addr & 0x03) << 3);
    err = SWJ_WriteData(addr, tmp);
    return err;
}








 


unsigned char SWJ_WriteMem32(unsigned long addr, unsigned long val)
{
    unsigned char err;

    SWJ_WriteAP(0x00, (0x01000000 | 0x20000000 | 0x02000000 | 0x00000040 | 0x00000010) | 0x00000002);
    err = SWJ_WriteData(addr, val);
    return err;
}









 




static unsigned char SWJ_WriteBlock(unsigned long addr, unsigned char *buf, unsigned long len)
{
    unsigned char err, req;
    unsigned long size_in_words;
    unsigned long i, ack;

    if(len == 0)  return 0;

    err = 0;
    size_in_words = len / 4;


    err += SWJ_WriteAP(0x00, (0x01000000 | 0x20000000 | 0x02000000 | 0x00000040 | 0x00000010) | 0x00000002);

    if(err)
    {
        
    }

    err += SWJ_WriteAP(0x04, addr);

    if(err) return err;

     
    req = (1) | (0<<1) | (3 << 2);

    for(i = 0; i < size_in_words; i++)
    {
        if(SWD_Transfer(req, (unsigned long *)buf) != (1<<0))
        {
            return 1;
        }

        buf += 4;
    }

     
    req = (0) | (1<<1) | (0x0C & 0x0c);
    ack = SWD_Transfer(req, 0);

    (ack == (1<<0)) ? (err = 0) : (err = 1);
    return 0;
}








 



static unsigned char SWJ_ReadData(unsigned long addr, unsigned long *val)
{
    unsigned char req, ack, err;

    SWJ_WriteAP(0x04, addr);

     
    req = (1) | (1<<1) | 0x0C;
    ack = SWD_Transfer(req, val);

     
    req = (0) | (1<<1) | (0x0C & 0x0c);
    ack = SWD_Transfer(req, val);

    (ack == (1<<0)) ? (err = 0) : (err = 1);
    return err;
}








 


static unsigned char SWJ_ReadMem32(unsigned long addr, unsigned long *val)
{
    unsigned char err;
    SWJ_WriteAP(0x00, (0x01000000 | 0x20000000 | 0x02000000 | 0x00000040 | 0x00000010) | 0x00000002);
    err = SWJ_ReadData(addr, val);
    return err;
}








 


static unsigned char SWJ_ReadMem8(unsigned long addr, unsigned char *val)
{
    unsigned long tmp;
    unsigned char err;

    SWJ_WriteAP(0x00, (0x01000000 | 0x20000000 | 0x02000000 | 0x00000040 | 0x00000010) | 0x00000000);

    err = SWJ_ReadData(addr, &tmp);

    *val = (unsigned char)(tmp >> ((addr & 0x03) << 3));

    return err;
}








 




static unsigned char SWJ_ReadBlock(unsigned long addr, unsigned char *buf, unsigned long len)
{
    unsigned char err, req;
    unsigned long size_in_words;
    unsigned long i, ack;

    if(len == 0)  return 0;

    err = 0;
    size_in_words = len / 4;


    err += SWJ_WriteAP(0x00, (0x01000000 | 0x20000000 | 0x02000000 | 0x00000040 | 0x00000010) | 0x00000002);
    err += SWJ_WriteAP(0x04, addr);

    if(err) return err;

    req = (1) | (1<<1) | (3 << 2);

     
    if(SWD_Transfer(req, (unsigned long *)buf) != 0x01)
    {
        return 1;
    }

    for(i = 0; i < size_in_words; i++)
    {
        if(SWD_Transfer(req, (unsigned long *)buf) != (1<<0))
        {
            return 1;
        }

        buf += 4;
    }

     
    req = (0) | (1<<1) | (0x0C & 0x0c);
    ack = SWD_Transfer(req, 0);

    (ack == (1<<0)) ? (err = 0) : (err = 1);
    return err;
}










 




unsigned char swd_write_memory(unsigned long address, unsigned char *data, unsigned long size)
{
    unsigned long n;

    
    while((size > 0) && (address & 0x3))
    {
        SWJ_WriteMem8(address, *data);
        address++;
        data++;
        size--;
    }

    
    while(size > 3)
    {
        
        n = (0x400) - (address & ((0x400) - 1));

        if(size < n)
        {
            n = size & 0xFFFFFFFC; 
        }

        if(SWJ_WriteBlock(address, data, n))
        {
            ;
            return 1;
        }

        address += n;
        data += n;
        size -= n;
    }

    
    while(size > 0)
    {
        SWJ_WriteMem8(address, *data);

        address++;
        data++;
        size--;
    }

    return 0;
}








 




unsigned char swd_read_memory(unsigned long address, unsigned char *data, unsigned long size)
{
    unsigned long n;

    
    while((size > 0) && (address & 0x3))
    {
        SWJ_ReadMem8(address, data);
        address++;
        data++;
        size--;
    }

    
    while(size > 3)
    {
        
        n = (0x400) - (address & ((0x400) - 1));

        if(size < n)
        {
            n = size & 0xFFFFFFFC; 
        }

        if(SWJ_ReadBlock(address, data, n))
        {
            return 1;
        }

        address += n;
        data += n;
        size -= n;
    }

    
    while(size > 0)
    {
        SWJ_ReadMem8(address, data);
        address++;
        data++;
        size--;
    }

    return 0;
}








 


unsigned char SWJ_ReadMem(unsigned long addr, unsigned char *buf, unsigned long len)
{
    return swd_read_memory(addr, buf, len);
}








 


unsigned char SWJ_WriteMem(unsigned long addr, unsigned char *buf, unsigned long len)
{
    return swd_write_memory(addr, buf, len);
}









 


static unsigned char SWJ_WaitUntilHalted(void)
{
    
    unsigned long val, i, timeout = 1;

    for(i = 0; i < timeout; i++)
    {

        if(SWJ_ReadMem32(((0xE000EDF0) + 0x00), &val))
        {
            return 1;
        }

        if(val & 0x00020000)
        {
            return 0;
        }
    }

    return (1<<3);		
}








 


unsigned char SWJ_SetTargetState(TARGET_RESET_STATE state)
{
    switch(state)
    {
        case RESET_HOLD:
            ((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0C00)) ->BRR = ((u16)0x0004);		
            break;

        case RESET_RUN:	
            ((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0C00)) ->BRR = ((u16)0x0004);		
            DELAY_US(20 * 1000);
            ((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0C00)) ->BSRR = ((u16)0x0004);		
            DELAY_US(20 * 1000);
            break;

        case RESET_PROGRAM:
            ((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0C00)) ->BRR = ((u16)0x0004);		
            DELAY_US(20);
            
            

            SWJ_InitDebug();

            
            SWJ_WriteMem32(((0xE000EDF0) + 0x00), 0xA05F0000 | 0x00000001);

            
            SWJ_WriteMem32(((0xE000EDF0) + 0x0C), 0x00000001);

            
            ((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0C00)) ->BRR = ((u16)0x0004);		
            DELAY_US(20 * 1000);
            ((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0C00)) ->BSRR = ((u16)0x0004);		

            break;

        default:
            break;
    }

    return 0;
}








 


static unsigned char SWJ_WriteCoreReg(unsigned long n, unsigned long val)
{
    int i = 0, timeout = 1;

    SWJ_WriteMem32(0xE000EDF8, val);

    SWJ_WriteMem32(0xE000EDF4, n | (1 << 16));

    
    for(i = 0; i < timeout; i++)
    {
        SWJ_ReadMem32(0xE000EDF0, &val);

        if(val & 0x00010000)
        {
            return 0;
        }
    }

    return 1;
}








 


static unsigned char SWJ_ReadCoreReg(unsigned long n, unsigned long *val)
{
    int i = 0, timeout = 1, err;

    if(SWJ_WriteMem32(0xE000EDF4, n))
        return 1;

    
    for(i = 0; i < timeout; i++)
    {

        if(SWJ_ReadMem32(0xE000EDF0, val))
            return 1;

        if(*val & 0x00010000)
            break;
    }

    if(i == timeout)
        return 1;

    err = SWJ_ReadMem32(0xE000EDF8, val);

    return err;
}








 


unsigned char swd_write_debug_state(DEBUG_STATE *state)
{
    unsigned long i, status;

    SWJ_WriteDP(0x08, 0);

    
    for(i = 0; i < 4; i++)
    {
        SWJ_WriteCoreReg(i, state->r[i]);
    }

    
    SWJ_WriteCoreReg(9, state->r[9]);

    
    for(i = 13; i < 16; i++)
    {
        SWJ_WriteCoreReg(i, state->r[i]);
    }

    
    SWJ_WriteCoreReg(16, state->xpsr);
    SWJ_WriteMem32(((0xE000EDF0) + 0x00), 0xA05F0000 | 0x00000001);

    
    SWJ_ReadDP(0x04, &status);

    if(status & (0x00000020 | 0x00000080))
    {
        ;
        return 1;
    }

    return 0;
}








 


unsigned char swd_flash_syscall_exec(const FLASH_SYSCALL *sysCallParam, unsigned long entry, unsigned long arg1, unsigned long arg2, unsigned long arg3, unsigned long arg4)
{
    DEBUG_STATE state;

    
    state.xpsr     = 0x01000000;          
    state.r[0]     = arg1;                   
    state.r[1]     = arg2;                   
    state.r[2]     = arg3;                   
    state.r[3]     = arg4;                   

    state.r[9]     = sysCallParam->static_base;    

    state.r[13]    = sysCallParam->stack_pointer;  
    state.r[14]    = sysCallParam->breakpoint;       
    state.r[15]    = entry;                           

    if(swd_write_debug_state(&state))
    {
        ;
        return 1;
    }

    if(SWJ_WaitUntilHalted())
    {
        ;
        return 1;
    }

    if(SWJ_ReadCoreReg(0, &state.r[0]))
    {
        ;
        return 1;
    }


    
    if(state.r[0] != 0)
    {
        ;
        return 1;
    }

    return 0;
}








 


unsigned char SWJ_InitDebug(void)
{
  unsigned long tmp = 0;
  unsigned long val;
  unsigned char ack;
     
    SWJ_JTAG2SWD();
	
    if(SWJ_ReadDP(0x00, &val))		
    {
        return 1;
    }
		
    ;

    SWJ_WriteDP(0x00, 0x00000002	|	0x00000004	|	0x00000008	|	0x00000010);

     
    

     
    SWJ_WriteDP(0x04, 0x40000000 | 0x10000000);   
    
    
    do
    { 
        ack = SWJ_ReadDP(0x04, &tmp);
        if(0!=ack)
        {
            return 0;
        }
    }
    while((tmp & (0x20000000 | 0x80000000)) != (0x20000000 | 0x80000000));

    SWJ_WriteDP(0x04, 0x40000000 | 0x10000000 | 0x00000000 | 0x00000F00);
		
		GPIO_Configuration_OPP50 (((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0800)),((u16)0x0400));;
		((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0800)) ->BSRR = ((u16)0x0400);
    return 0;
}

void softdelay(unsigned long us)
{
    volatile unsigned long i, j;

    for(i = 0; i < us; i++)
    {
        for(j = 0; j < 30U; j++)
        {
            __nop();
        }
    }
}
unsigned long sss[10];
void test(void)
{
	unsigned long i = 10, val;
	
    GPIO_Configuration_OPP50 (((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0800)),((u16)0x0400));;		
    GPIO_Configuration_OPP50 (((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0800)),((u16)0x0200));;		

    ((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0800)) ->BRR = ((u16)0x0200);
    ((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0800)) ->BSRR = ((u16)0x0400);

    
    SWJ_InitDebug();

    while(i--)
    {
        SWJ_ReadDP(0x00, &val);
        sss[i] = val;


        softdelay(100);
        
        
    }
    while(1);
}
