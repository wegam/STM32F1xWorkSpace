#line 1 "..\\..\\Driver\\Components\\SCR\\MOTOR.C"







 

#line 1 "..\\..\\Driver\\Components\\INC\\MOTOR.H"




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



 
#line 6 "..\\..\\Driver\\Components\\INC\\MOTOR.H"















typedef enum	_STEP_MOTO_COMMAND
{

	MOTO_COMMAND_RUN,				
	MOTO_COMMAND_PAUSE,			
	MOTO_COMMAND_STOP				
}STEP_MOTO_COMMAND;				

typedef struct _STEP_TIME_CONF
{
	u32	StepTimeOut;			
	u32	StepFreq;					
	u32	StartFreq;				
	u32	BaseTime;					
}STEP_TIME_CONF;				

typedef struct _STEP_TIME_RUN
{
	u32	StepTimeCount;		
	u32	StepCycle;				
	u32	StartCycle;				
	u32	StartSteps;				
	u32	RunCycle;					
	u32	HalfCycle;				
	u32	ToggleTime;				
}STEP_TIME_RUN;					

typedef struct _STEP_MOTO_CONF
{
	
		
	GPIO_TypeDef* 	PUL_PORT;				
	unsigned short 	PUL_Pin;				
	
	
	GPIO_TypeDef* 	DIR_PORT;				
	unsigned short 	DIR_Pin;				
	
	
	GPIO_TypeDef* 	EN_PORT;				
	unsigned short 	EN_Pin;					
	
	
	GPIO_TypeDef* 	Brake_PORT;			
	unsigned short 	Brake_Pin;			
	
	STEP_TIME_CONF			TIME_CONF;	
	STEP_TIME_RUN				TIME_RUN;		
	
	STEP_MOTO_COMMAND		MOTO_COMMAND;				

}STEP_MOTO_CONF;



void StepMotoConf(STEP_MOTO_CONF *STEP_MOTOx);		
void StepMotoContrl(STEP_MOTO_CONF *STEP_MOTOx);	


void StepMotoRun(STEP_MOTO_CONF *STEP_MOTOx);			
void StepMotoStop(STEP_MOTO_CONF *STEP_MOTOx);		
void StepMotoSever(STEP_MOTO_CONF *STEP_MOTOx);		




#line 11 "..\\..\\Driver\\Components\\SCR\\MOTOR.C"

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










#line 13 "..\\..\\Driver\\Components\\SCR\\MOTOR.C"





 
void StepMotoConf(STEP_MOTO_CONF *STEP_MOTOx)
{
	
	GPIO_Configuration_OPP50	(STEP_MOTOx->PUL_PORT,	STEP_MOTOx->PUL_Pin);			
	
	GPIO_Configuration_OPP50	(STEP_MOTOx->DIR_PORT,	STEP_MOTOx->DIR_Pin);			
	
	GPIO_Configuration_OPP50	(STEP_MOTOx->EN_PORT,		STEP_MOTOx->EN_Pin);			
	
	GPIO_Configuration_OPP50	(STEP_MOTOx->Brake_PORT,	STEP_MOTOx->Brake_Pin);			
	
	
	STEP_MOTOx->TIME_RUN.StepCycle=1000000/(STEP_MOTOx->TIME_CONF.BaseTime)/(STEP_MOTOx->TIME_CONF.StepFreq);				
	if(STEP_MOTOx->TIME_RUN.StepCycle<2)
	{
		STEP_MOTOx->TIME_RUN.StepCycle=2;
	}
	else if((STEP_MOTOx->TIME_RUN.StepCycle%2)!=0)
	{
		STEP_MOTOx->TIME_RUN.StepCycle-=1;
	}
	STEP_MOTOx->TIME_RUN.StartCycle=1000000/(STEP_MOTOx->TIME_CONF.BaseTime)/(STEP_MOTOx->TIME_CONF.StartFreq);			
	STEP_MOTOx->TIME_RUN.StartSteps=(STEP_MOTOx->TIME_RUN.StartCycle-STEP_MOTOx->TIME_RUN.StepCycle)/500+0.5;				
	STEP_MOTOx->TIME_RUN.RunCycle=STEP_MOTOx->TIME_RUN.StartCycle;		
	STEP_MOTOx->TIME_RUN.HalfCycle=STEP_MOTOx->TIME_RUN.RunCycle/2;		
	if(STEP_MOTOx->TIME_RUN.StartSteps<2)
	{
		STEP_MOTOx->TIME_RUN.StartSteps=2;
	}
	
	STEP_MOTOx->MOTO_COMMAND		=	MOTO_COMMAND_STOP;		
}




 
void StepMotoContrl(STEP_MOTO_CONF *STEP_MOTOx)
{

}




 
void StepMotoRun(STEP_MOTO_CONF *STEP_MOTOx)
{
	STEP_MOTOx->TIME_RUN.StepTimeCount++;
	if(STEP_MOTOx->TIME_RUN.StepTimeCount	<=	2)								
	{
		GPIO_SetBits(STEP_MOTOx->DIR_PORT,STEP_MOTOx->DIR_Pin);
	}
	if(STEP_MOTOx->TIME_RUN.StepTimeCount	<	STEP_MOTOx->TIME_CONF.StepTimeOut)				
	{
		
		
		
		if(STEP_MOTOx->TIME_RUN.RunCycle	>	STEP_MOTOx->TIME_RUN.StepCycle)
		{
			if((STEP_MOTOx->TIME_RUN.StepTimeCount*STEP_MOTOx->TIME_CONF.BaseTime)%1000==0)		
			{
				STEP_MOTOx->TIME_RUN.RunCycle		-=	2;
				STEP_MOTOx->TIME_RUN.HalfCycle	=		(STEP_MOTOx->TIME_RUN.RunCycle/2);		
			}
			
			if(STEP_MOTOx->TIME_RUN.RunCycle	<=	STEP_MOTOx->TIME_RUN.StepCycle)			
			{
				STEP_MOTOx->TIME_RUN.RunCycle		=		STEP_MOTOx->TIME_RUN.StepCycle;				
				STEP_MOTOx->TIME_RUN.HalfCycle	=		(STEP_MOTOx->TIME_RUN.RunCycle/2);		
			}
		}
		
		
		if(STEP_MOTOx->TIME_RUN.ToggleTime++	>=	STEP_MOTOx->TIME_RUN.RunCycle-1)	
		{
			STEP_MOTOx->TIME_RUN.HalfCycle	=	(STEP_MOTOx->TIME_RUN.RunCycle/2);			
			STEP_MOTOx->TIME_RUN.ToggleTime	=	0;			
		}
		
		if(STEP_MOTOx->TIME_RUN.ToggleTime	<	STEP_MOTOx->TIME_RUN.HalfCycle)			
		{
			GPIO_SetBits(STEP_MOTOx->PUL_PORT,STEP_MOTOx->PUL_Pin);
		}
		else					
		{
			GPIO_ResetBits(STEP_MOTOx->PUL_PORT,STEP_MOTOx->PUL_Pin);
		}

	}
	else		
	{
		StepMotoStop(STEP_MOTOx);																		
	}
}




 
void StepMotoStop(STEP_MOTO_CONF *STEP_MOTOx)
{
	STEP_MOTOx->TIME_RUN.StepTimeCount=0;														
	STEP_MOTOx->TIME_RUN.ToggleTime=0;															
	STEP_MOTOx->TIME_RUN.RunCycle=STEP_MOTOx->TIME_RUN.StartCycle;	
	
	GPIO_ResetBits(STEP_MOTOx->DIR_PORT,STEP_MOTOx->DIR_Pin);
	GPIO_ResetBits(STEP_MOTOx->PUL_PORT,STEP_MOTOx->PUL_Pin);				
	


}




 
void StepMotoPause(STEP_MOTO_CONF *STEP_MOTOx)
{
	STEP_MOTOx->TIME_RUN.StepTimeCount=0;														
	STEP_MOTOx->TIME_RUN.ToggleTime=0;															
	STEP_MOTOx->TIME_RUN.RunCycle=STEP_MOTOx->TIME_RUN.StartCycle;	
	
	GPIO_ResetBits(STEP_MOTOx->DIR_PORT,STEP_MOTOx->DIR_Pin);
	GPIO_ResetBits(STEP_MOTOx->PUL_PORT,STEP_MOTOx->PUL_Pin);				
	


}




 
void StepMotoSever(STEP_MOTO_CONF *STEP_MOTOx)
{
	if(STEP_MOTOx->MOTO_COMMAND==MOTO_COMMAND_RUN)
	{
		StepMotoRun(STEP_MOTOx);			
	}
	else if(STEP_MOTOx->MOTO_COMMAND==MOTO_COMMAND_STOP)
	{
		StepMotoStop(STEP_MOTOx);			
		
	}
}


































































































































