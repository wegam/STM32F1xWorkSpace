#line 1 "..\\..\\Driver\\Components\\SCR\\SWITCHID.C"







 

#line 1 "..\\..\\Driver\\Components\\INC\\SWITCHID.H"




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



 
#line 6 "..\\..\\Driver\\Components\\INC\\SWITCHID.H"





typedef struct _SwitchData
{
	unsigned short SW1:1;
	unsigned short SW2:1;
	unsigned short SW3:1;
	unsigned short SW4:1;
	unsigned short SW5:1;
	unsigned short SW6:1;
	unsigned short SW7:1;
	unsigned short SW8:1;
	unsigned short SW9:1;
	unsigned short SW10:1;
	unsigned short SW11:1;
	unsigned short SW12:1;
	unsigned short SW13:1;
	unsigned short SW14:1;
	unsigned short SW15:1;
	unsigned short SW16:1;
	
}SwitchDataType;			


typedef struct _SwitchConf
{
	
	
	GPIO_TypeDef* 	SW1_PORT;					
	unsigned short 	SW1_Pin;					
	
	
	GPIO_TypeDef* 	SW2_PORT;					
	unsigned short 	SW2_Pin;					
	
	
	GPIO_TypeDef* 	SW3_PORT;					
	unsigned short 	SW3_Pin;					
	
	
	GPIO_TypeDef* 	SW4_PORT;					
	unsigned short 	SW4_Pin;					
	
	
	GPIO_TypeDef* 	SW5_PORT;					
	unsigned short 	SW5_Pin;					
	
	
	GPIO_TypeDef* 	SW6_PORT;					
	unsigned short 	SW6_Pin;					
	
	
	GPIO_TypeDef* 	SW7_PORT;					
	unsigned short 	SW7_Pin;					
	
	
	GPIO_TypeDef* 	SW8_PORT;					
	unsigned short 	SW8_Pin;					
	
	
	GPIO_TypeDef* 	SW9_PORT;					
	unsigned short 	SW9_Pin;					
	
	
	GPIO_TypeDef* 	SW10_PORT;					
	unsigned short 	SW10_Pin;					
	
	
	GPIO_TypeDef* 	SW11_PORT;					
	unsigned short 	SW11_Pin;					
	
	
	GPIO_TypeDef* 	SW12_PORT;					
	unsigned short 	SW12_Pin;					
	
	
	GPIO_TypeDef* 	SW13_PORT;					
	unsigned short 	SW13_Pin;					
	
	
	GPIO_TypeDef* 	SW14_PORT;					
	unsigned short 	SW14_Pin;					
	
	
	GPIO_TypeDef* 	SW15_PORT;					
	unsigned short 	SW15_Pin;					
	
	
	GPIO_TypeDef* 	SW16_PORT;					
	unsigned short 	SW16_Pin;					
		
	unsigned char		NumOfSW;					
	unsigned short	nSWITCHID;				
	SwitchDataType	SWData;						
}SwitchDef;




void SwitchIdInitialize(SwitchDef *pSwitch);					
unsigned short SWITCHID_ReadRight(SwitchDef *pSwitch);	  
unsigned short SWITCHID_ReadLeft(SwitchDef *pSwitch);			





#line 11 "..\\..\\Driver\\Components\\SCR\\SWITCHID.C"

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










#line 13 "..\\..\\Driver\\Components\\SCR\\SWITCHID.C"






 
void SwitchIdInitialize(SwitchDef *pSwitch)
{
	unsigned char NumOfSW=pSwitch->NumOfSW;			
	
	if(NumOfSW)	
	{
		GPIO_Configuration_IPU	(pSwitch->SW1_PORT,	pSwitch->SW1_Pin);			
		NumOfSW-=1;
	}
	if(NumOfSW)	
	{
		GPIO_Configuration_IPU	(pSwitch->SW2_PORT,	pSwitch->SW2_Pin);			
		NumOfSW-=1;
	}
	if(NumOfSW)	
	{
		GPIO_Configuration_IPU	(pSwitch->SW3_PORT,	pSwitch->SW3_Pin);			
		NumOfSW-=1;
	}
	if(NumOfSW)	
	{
		GPIO_Configuration_IPU	(pSwitch->SW4_PORT,	pSwitch->SW4_Pin);			
		NumOfSW-=1;
	}
	if(NumOfSW)	
	{
		GPIO_Configuration_IPU	(pSwitch->SW5_PORT,	pSwitch->SW5_Pin);			
		NumOfSW-=1;
	}
	if(NumOfSW)	
	{
		GPIO_Configuration_IPU	(pSwitch->SW6_PORT,	pSwitch->SW6_Pin);			
		NumOfSW-=1;
	}
	if(NumOfSW)	
	{
		GPIO_Configuration_IPU	(pSwitch->SW7_PORT,	pSwitch->SW7_Pin);			
		NumOfSW-=1;
	}
	if(NumOfSW)	
	{
		GPIO_Configuration_IPU	(pSwitch->SW8_PORT,	pSwitch->SW8_Pin);			
		NumOfSW-=1;
	}
	if(NumOfSW)	
	{
		GPIO_Configuration_IPU	(pSwitch->SW9_PORT,	pSwitch->SW9_Pin);			
		NumOfSW-=1;
	}
	if(NumOfSW)	
	{
		GPIO_Configuration_IPU	(pSwitch->SW10_PORT,	pSwitch->SW10_Pin);			
		NumOfSW-=1;
	}
	if(NumOfSW)	
	{
		GPIO_Configuration_IPU	(pSwitch->SW11_PORT,	pSwitch->SW11_Pin);			
		NumOfSW-=1;
	}
	if(NumOfSW)	
	{
		GPIO_Configuration_IPU	(pSwitch->SW12_PORT,	pSwitch->SW12_Pin);			
		NumOfSW-=1;
	}
	if(NumOfSW)	
	{
		GPIO_Configuration_IPU	(pSwitch->SW13_PORT,	pSwitch->SW13_Pin);			
		NumOfSW-=1;
	}
	if(NumOfSW)	
	{
		GPIO_Configuration_IPU	(pSwitch->SW14_PORT,	pSwitch->SW14_Pin);			
		NumOfSW-=1;
	}
	if(NumOfSW)	
	{
		GPIO_Configuration_IPU	(pSwitch->SW15_PORT,	pSwitch->SW15_Pin);			
		NumOfSW-=1;
	}
	if(NumOfSW)	
	{
		GPIO_Configuration_IPU	(pSwitch->SW16_PORT,	pSwitch->SW16_Pin);			
		NumOfSW-=1;
	}
	SWITCHID_ReadRight(pSwitch);
}








 
unsigned short SWITCHID_ReadRight(SwitchDef *pSwitch)
{
	unsigned short	reValue=0;	
	
	unsigned long *P=(unsigned long*)&(pSwitch->SWData);		
	unsigned char NumOfSW=pSwitch->NumOfSW;		

	unsigned short	Temp	=	0xFFFF<<NumOfSW;
	
	
	if(NumOfSW)	
	{
		NumOfSW-=1;
		if(pSwitch->SW1_PORT-> IDR	&pSwitch->SW1_Pin)
			reValue|=0x0001<<0;
	}
	if(NumOfSW)	
	{
		NumOfSW-=1;
		if(pSwitch->SW2_PORT-> IDR	&pSwitch->SW2_Pin)
			reValue|=0x0001<<1;
	}
	if(NumOfSW)	
	{
		NumOfSW-=1;
		if(pSwitch->SW3_PORT-> IDR	&pSwitch->SW3_Pin)
			reValue|=0x0001<<2;
	}
	if(NumOfSW)	
	{
		NumOfSW-=1;
		if(pSwitch->SW4_PORT-> IDR	&pSwitch->SW4_Pin)
			reValue|=0x0001<<3;
	}
	if(NumOfSW)	
	{
		NumOfSW-=1;
		if(pSwitch->SW5_PORT-> IDR	&pSwitch->SW5_Pin)
			reValue|=0x0001<<4;
	}
	if(NumOfSW)	
	{
		NumOfSW-=1;
		if(pSwitch->SW6_PORT-> IDR	&pSwitch->SW6_Pin)
			reValue|=0x0001<<5;
	}
	if(NumOfSW)	
	{
		NumOfSW-=1;
		if(pSwitch->SW7_PORT-> IDR	&pSwitch->SW7_Pin)
			reValue|=0x0001<<6;
	}
	if(NumOfSW)	
	{
		NumOfSW-=1;
		if(pSwitch->SW8_PORT-> IDR	&pSwitch->SW8_Pin)
			reValue|=0x0001<<7;
	}
	if(NumOfSW)	
	{
		NumOfSW-=1;
		if(pSwitch->SW9_PORT-> IDR	&pSwitch->SW9_Pin)
			reValue|=0x0001<<8;
	}
	if(NumOfSW)	
	{
		NumOfSW-=1;
		if(pSwitch->SW10_PORT-> IDR	&pSwitch->SW10_Pin)
			reValue|=0x0001<<9;
	}
	if(NumOfSW)	
	{
		NumOfSW-=1;
		if(pSwitch->SW11_PORT-> IDR	&pSwitch->SW11_Pin)
			reValue|=0x0001<<10;
	}
	if(NumOfSW)	
	{
		NumOfSW-=1;
		if(pSwitch->SW12_PORT-> IDR	&pSwitch->SW12_Pin)
			reValue|=0x0001<<11;
	}
	if(NumOfSW)	
	{
		NumOfSW-=1;
		if(pSwitch->SW13_PORT-> IDR	&pSwitch->SW13_Pin)
			reValue|=0x0001<<12;
	}
	if(NumOfSW)	
	{
		NumOfSW-=1;
		if(pSwitch->SW14_PORT-> IDR	&pSwitch->SW14_Pin)
			reValue|=0x0001<<13;
	}
	if(NumOfSW)	
	{
		NumOfSW-=1;
		if(pSwitch->SW15_PORT-> IDR	&pSwitch->SW15_Pin)
			reValue|=0x0001<<14;
	}
	if(NumOfSW)	
	{
		NumOfSW-=1;
		if(pSwitch->SW16_PORT-> IDR	&pSwitch->SW16_Pin)
			reValue|=0x0001<<15;
	}
	reValue	|=	Temp;
	reValue=~reValue;		
	*P=reValue;
	pSwitch->nSWITCHID=reValue;
	
	return	reValue;	
}








 
unsigned short SWITCHID_ReadLeft(SwitchDef *pSwitch)
{
  	unsigned short	reValue=0;	
	
	unsigned long *P=(unsigned long*)&(pSwitch->SWData);		
	unsigned char NumOfSW=pSwitch->NumOfSW;		

	unsigned short	Temp	=	0xFFFF<<NumOfSW;
	
	
	if(NumOfSW)	
	{
		NumOfSW-=1;
		if(pSwitch->SW1_PORT-> IDR	&pSwitch->SW1_Pin)
			reValue|=0x0001<<NumOfSW;
	}
	if(NumOfSW)	
	{
		NumOfSW-=1;
		if(pSwitch->SW2_PORT-> IDR	&pSwitch->SW2_Pin)
			reValue|=0x0001<<NumOfSW;
	}
	if(NumOfSW)	
	{
		NumOfSW-=1;
		if(pSwitch->SW3_PORT-> IDR	&pSwitch->SW3_Pin)
			reValue|=0x0001<<NumOfSW;
	}
	if(NumOfSW)	
	{
		NumOfSW-=1;
		if(pSwitch->SW4_PORT-> IDR	&pSwitch->SW4_Pin)
			reValue|=0x0001<<NumOfSW;
	}
	if(NumOfSW)	
	{
		NumOfSW-=1;
		if(pSwitch->SW5_PORT-> IDR	&pSwitch->SW5_Pin)
			reValue|=0x0001<<NumOfSW;
	}
	if(NumOfSW)	
	{
		NumOfSW-=1;
		if(pSwitch->SW6_PORT-> IDR	&pSwitch->SW6_Pin)
			reValue|=0x0001<<NumOfSW;
	}
	if(NumOfSW)	
	{
		NumOfSW-=1;
		if(pSwitch->SW7_PORT-> IDR	&pSwitch->SW7_Pin)
			reValue|=0x0001<<NumOfSW;
	}
	if(NumOfSW)	
	{
		NumOfSW-=1;
		if(pSwitch->SW8_PORT-> IDR	&pSwitch->SW8_Pin)
			reValue|=0x0001<<NumOfSW;
	}
	if(NumOfSW)	
	{
		NumOfSW-=1;
		if(pSwitch->SW9_PORT-> IDR	&pSwitch->SW9_Pin)
			reValue|=0x0001<<NumOfSW;
	}
	if(NumOfSW)	
	{
		NumOfSW-=1;
		if(pSwitch->SW10_PORT-> IDR	&pSwitch->SW10_Pin)
			reValue|=0x0001<<NumOfSW;
	}
	if(NumOfSW)	
	{
		NumOfSW-=1;
		if(pSwitch->SW11_PORT-> IDR	&pSwitch->SW11_Pin)
			reValue|=0x0001<<NumOfSW;
	}
	if(NumOfSW)	
	{
		NumOfSW-=1;
		if(pSwitch->SW12_PORT-> IDR	&pSwitch->SW12_Pin)
			reValue|=0x0001<<NumOfSW;
	}
	if(NumOfSW)	
	{
		NumOfSW-=1;
		if(pSwitch->SW13_PORT-> IDR	&pSwitch->SW13_Pin)
			reValue|=0x0001<<NumOfSW;
	}
	if(NumOfSW)	
	{
		NumOfSW-=1;
		if(pSwitch->SW14_PORT-> IDR	&pSwitch->SW14_Pin)
			reValue|=0x0001<<NumOfSW;
	}
	if(NumOfSW)	
	{
		NumOfSW-=1;
		if(pSwitch->SW15_PORT-> IDR	&pSwitch->SW15_Pin)
			reValue|=0x0001<<NumOfSW;
	}
	if(NumOfSW)	
	{
		NumOfSW-=1;
		if(pSwitch->SW16_PORT-> IDR	&pSwitch->SW16_Pin)
			reValue|=0x0001<<NumOfSW;
	}
	reValue	|=	Temp;
	reValue=~reValue;		
	*P=reValue;
	pSwitch->nSWITCHID=reValue;
	
	return	reValue;	
}

