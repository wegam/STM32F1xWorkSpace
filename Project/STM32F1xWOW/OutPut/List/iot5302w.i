#line 1 "..\\..\\Driver\\Components\\SCR\\IOT5302W.C"


 
#line 1 "..\\..\\Driver\\Components\\INC\\IOT5302W.H"




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

 
 
 



 
#line 6 "..\\..\\Driver\\Components\\INC\\IOT5302W.H"
#line 1 "..\\..\\Driver\\WOW\\INC\\STM32_USART.H"













 










#line 26 "..\\..\\Driver\\WOW\\INC\\STM32_USART.H"
#line 1 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_usart.h"














 

 



 
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

 
 
 



 
#line 23 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_usart.h"

 
 
typedef struct
{
  u32 USART_BaudRate;			
  u16 USART_WordLength;		
  u16 USART_StopBits;			
  u16 USART_Parity;				
  u16 USART_Mode;					
  u16 USART_HardwareFlowControl; 	
} USART_InitTypeDef;

 
typedef struct
{
  u16 USART_Clock;
  u16 USART_CPOL;
  u16 USART_CPHA;
  u16 USART_LastBit;
} USART_ClockInitTypeDef;

 















 


                                    



 









 








 





 















 






 




                               
 




 






 
#line 146 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_usart.h"






















 





 






 







 






 

																															
																															
																															
																															

																															
																															
																															
																															

																															
																															
																															
																															

																															
																															
																															
																															

																															
																															
																															
																															

																															
																															
																															
																															

																															
																															
																															
																															
																															

																															
																															
																															
																															

																															
																															
																															

																															






                              










 
 
void USART_DeInit(USART_TypeDef* USARTx);
void USART_Init(USART_TypeDef* USARTx, USART_InitTypeDef* USART_InitStruct);
void USART_StructInit(USART_InitTypeDef* USART_InitStruct);
void USART_ClockInit(USART_TypeDef* USARTx, USART_ClockInitTypeDef* USART_ClockInitStruct);
void USART_ClockStructInit(USART_ClockInitTypeDef* USART_ClockInitStruct);
void USART_Cmd(USART_TypeDef* USARTx, FunctionalState NewState);
void USART_ITConfig(USART_TypeDef* USARTx, u16 USART_IT, FunctionalState NewState);
void USART_DMACmd(USART_TypeDef* USARTx, u16 USART_DMAReq, FunctionalState NewState);
void USART_SetAddress(USART_TypeDef* USARTx, u8 USART_Address);
void USART_WakeUpConfig(USART_TypeDef* USARTx, u16 USART_WakeUp);
void USART_ReceiverWakeUpCmd(USART_TypeDef* USARTx, FunctionalState NewState);
void USART_LINBreakDetectLengthConfig(USART_TypeDef* USARTx, u16 USART_LINBreakDetectLength);
void USART_LINCmd(USART_TypeDef* USARTx, FunctionalState NewState);
void USART_SendData(USART_TypeDef* USARTx, u16 Data);
u16 USART_ReceiveData(USART_TypeDef* USARTx);
void USART_SendBreak(USART_TypeDef* USARTx);
void USART_SetGuardTime(USART_TypeDef* USARTx, u8 USART_GuardTime);
void USART_SetPrescaler(USART_TypeDef* USARTx, u8 USART_Prescaler);
void USART_SmartCardCmd(USART_TypeDef* USARTx, FunctionalState NewState);
void USART_SmartCardNACKCmd(USART_TypeDef* USARTx, FunctionalState NewState);
void USART_HalfDuplexCmd(USART_TypeDef* USARTx, FunctionalState NewState);
void USART_IrDAConfig(USART_TypeDef* USARTx, u16 USART_IrDAMode);
void USART_IrDACmd(USART_TypeDef* USARTx, FunctionalState NewState);
FlagStatus USART_GetFlagStatus(USART_TypeDef* USARTx, u16 USART_FLAG);
void USART_ClearFlag(USART_TypeDef* USARTx, u16 USART_FLAG);
ITStatus USART_GetITStatus(USART_TypeDef* USARTx, u16 USART_IT);
void USART_ClearITPendingBit(USART_TypeDef* USARTx, u16 USART_IT);



 
#line 27 "..\\..\\Driver\\WOW\\INC\\STM32_USART.H"









typedef struct
{
	
	USART_TypeDef* 	USARTx;			
	
	GPIO_TypeDef* 	RS485_CTL_PORT;				
	unsigned short 	RS485_CTL_Pin;				
}RS485Def;
typedef struct
{
	unsigned char USART_IDLESTD	:1;		
	unsigned char USART_ReceSTD	:1;		
	unsigned char USART_SendSTD	:1;		
	unsigned char USART_RTSTD	  :1;		
}USARTStatusDef;






void	USART_DMA_Initialize	(USART_TypeDef* USARTx,u16 BufferSize);	
void	USART_GPIO_Initialize(USART_TypeDef* USARTx);                 	
void	USART_IT_Initialize(USART_TypeDef* USARTx);	                    

void	USART_DMA_ConfigurationNR	(USART_TypeDef* USARTx,u32 USART_BaudRate,u16 BufferSize);	
void	USART_DMA_ConfigurationIDLEIT	(USART_TypeDef* USARTx,u32 USART_BaudRate,u16 BufferSize);	
void 	USART_DMA_ConfigurationEV	(USART_TypeDef* USARTx,u32 USART_BaudRate,u16 BufferSize);	
void 	USART_DMA_ConfigurationOD	(USART_TypeDef* USARTx,u32 USART_BaudRate,u16 BufferSize);	

void 	USART_DMA_ConfigurationIT	(USART_TypeDef* USARTx,u32 USART_BaudRate,u32 BufferSize);	

void	USART_DMA_ConfigurationNRRemap	(USART_TypeDef* USARTx,u32 USART_BaudRate,u32 *RxdBuffer,u32 BufferSize);	


u16	USART_ReadBufferIDLE	(USART_TypeDef* USARTx,u8 *RevBuffer);	


u16	USART_DMAPrintf		  (USART_TypeDef* USARTx,const char *format,...);					
u16	USART_DMAPrintfList (USART_TypeDef* USARTx,const char *format,...);					
u16	USART_DMASend			  (USART_TypeDef* USARTx,u8 *tx_buffer,u16 BufferSize);		
u16	USART_DMASendList   (USART_TypeDef* USARTx,u8 *tx_buffer,u16 BufferSize);		
USARTStatusDef	USART_Status(USART_TypeDef* USARTx);		









void	RS485_DMA_ConfigurationNR			(RS485Def *pRS485,u32 USART_BaudRate,u16 BufferSize);	
void	RS485_DMA_ConfigurationNRRemap(RS485Def *pRS485,u32 USART_BaudRate,u32 *RxdBuffer,u32 BufferSize);	

u16		RS485_ReadBufferIDLE			(RS485Def *pRS485,u8 *RevBuffer);	


u16 	RS485_DMAPrintf						(RS485Def *pRS485,const char *format,...);					
u16 	RS485_DMASend							(RS485Def *pRS485,u8 *tx_buffer,u16 BufferSize);	


void 	USART_ConfigurationIT(USART_TypeDef* USARTx,u32 USART_BaudRate,u8 PreemptionPriority,u8 SubPriority);	
void	USART_Send(USART_TypeDef* USARTx,u8* RevBuffer,u16 Lengh);
unsigned char UART5ReceiveData(unsigned char* RecByte);			


void  USART_TxServer(USART_TypeDef* USARTx);
void  USART_RxServer(USART_TypeDef* USARTx);		
void	USART_Process(void);		



#line 7 "..\\..\\Driver\\Components\\INC\\IOT5302W.H"













 



  






typedef enum  _Cmd 
{
  
  REQA          = 0x03,   
  Anticoll      = 0x04,   
  Select        = 0x05,   
  
  IotRead          = 0x20, 
  IotWrite         = 0x21, 
  InitVal       = 0x22, 
  Decrement     = 0x23, 
  Increment     = 0x24, 
  GET_SNR       = 0x25, 
  ISO14443CC    = 0x28, 
  
  SetAddress    = 0x80, 
  SetBaudrate   = 0x81, 
  SetSerlNum    = 0x82, 
  GetSerlNum    = 0x83, 
  WriteUserInfo = 0x84, 
  ReadUserInfo  = 0x85, 
  GetVersionNum = 0x86, 
  ControlLed    = 0x88, 
  ControlBuzzer = 0x89, 
}Cmddef;


typedef enum  _status 
{
  CMDOK       = 0x00,          
  CMDFAILED   = 0x01,   
  SETOK       = 0x80,     
  SETFAILED   = 0x81, 
  CMMTimeOut  = 0x82, 
  NoCard      = 0x83, 
  DataErr     = 0x84, 
  PraErr      = 0x85, 
  UnknowErr   = 0x87, 
  UnknowCmd   = 0x8F, 
}stsdef;

typedef struct _IOTReader
{
  unsigned char STX;  
  unsigned char ID;   
  unsigned char Len;  
  unsigned char Cts;  
  unsigned char Data[128];  
  unsigned char BCC;  
  unsigned char ETX;  
}IRDdef;

typedef struct _IOT5302WConf
{
  RS485Def  IOT5302WPort;         
  unsigned long USART_BaudRate;   
}IOT5302WConfWdef;

typedef struct _IOT5302WData
{
  unsigned char   UID[4];         
  unsigned char   UIDbac[4];      
  unsigned char   Data[128]; 
  unsigned char   DataCount;      
  unsigned char   Initialized;    
  unsigned short  Time;           
  unsigned short  TimeOut;        
  unsigned short  TimeCmp;        
  unsigned long   USART_BaudRate; 
  unsigned char   BaudRateSetStep; 
}IOT5302WDataWdef;

typedef struct _IOT5302W
{
  IOT5302WConfWdef  Conf;   
  IOT5302WDataWdef  Data;  
}IOT5302Wdef;




unsigned short IOT5302WGetSNR(unsigned char* Buffer);    
unsigned short IOT5302WSetBaudrate(unsigned char* Buffer,unsigned char Num);  
unsigned short IotMifareGetCmdFrame(Cmddef Cmd,unsigned char Sec,unsigned char* Buffer,unsigned char* KeyBuffer);




void API_IOT5302WConfiguration(IOT5302Wdef* pIOT5302W);
void API_IOT5302WServer(void);

unsigned short API_IOT5302WGetUID(unsigned char* Buffer);






#line 5 "..\\..\\Driver\\Components\\SCR\\IOT5302W.C"
#line 1 "..\\..\\Driver\\Tool\\TOOL.H"



 
#line 6 "..\\..\\Driver\\Tool\\TOOL.H"


typedef struct
{
 u16 year; 
 u8 month;
 u8 day;
 u8 hour;
 u8 minute;
 u8 second;
}BuildTimeDef;


BuildTimeDef* GetBuildTime(void* pDate, void*	pTime);
unsigned short GetBuildYear(const char* DataStr);
unsigned char GetBuildMonth(const char* DataStr);
unsigned char GetBuildDay(const char* DataStr);
unsigned char GetBuildHour(const char* TimeStr);
unsigned char GetBuildMinute(const char* TimeStr);
unsigned char GetBuildSecond(const char* TimeStr);

unsigned char BCC8(const unsigned char *buffer,unsigned short num);		
unsigned char CRC8(const unsigned char *buffer);						
unsigned char LRC8(const unsigned char *buffer);						

unsigned char 	GetMaxChar	(unsigned char *pBuffer,unsigned short Length);		
unsigned short 	GetMaxShort	(unsigned short *pBuffer,unsigned short Length);	
unsigned long 	GetMaxLong	(unsigned long *pBuffer,unsigned short Length);		

unsigned char 	GetMinChar	(unsigned char *pBuffer,unsigned short Length);		
unsigned short 	GetMinShort(unsigned short *pBuffer,unsigned short Length);		
unsigned long 	GetMinLong	(unsigned long *pBuffer,unsigned short Length);		

unsigned long 	GetAveLong(unsigned long *pBuffer,unsigned short Length);			
unsigned long 	GetVarLong(unsigned long *pBuffer,unsigned short Length);			




#line 6 "..\\..\\Driver\\Components\\SCR\\IOT5302W.C"


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



 

#line 9 "..\\..\\Driver\\Components\\SCR\\IOT5302W.C"
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



 

#line 10 "..\\..\\Driver\\Components\\SCR\\IOT5302W.C"
#line 1 "..\\..\\Library\\C\\stdarg.h"
 
 
 





 










#line 27 "..\\..\\Library\\C\\stdarg.h"








 

 
 
#line 57 "..\\..\\Library\\C\\stdarg.h"
    typedef struct __va_list { void *__ap; } va_list;

   






 


   










 


   















 




   

 


   




 



   





 







#line 138 "..\\..\\Library\\C\\stdarg.h"



#line 147 "..\\..\\Library\\C\\stdarg.h"

 

#line 11 "..\\..\\Driver\\Components\\SCR\\IOT5302W.C"
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





 
#line 12 "..\\..\\Driver\\Components\\SCR\\IOT5302W.C"

IOT5302Wdef IOT5302W;

unsigned char CmdBuffer[16]={0};

void IOT5302W_Initialize(void);     
void IOT5302W_DataProcess(void);    
void IOT5302W_DataCheck(void);

unsigned short IOT5302W_HWSendData(unsigned char* TxdBuffer,unsigned short length);
unsigned short IOT5302W_HWReadData(unsigned char* Buffer);









 
void API_IOT5302WConfiguration(IOT5302Wdef* pIOT5302W)
{
  IOT5302W  = *pIOT5302W;
  IOT5302W.Data.Initialized = 0;
  IOT5302W.Data.Time        = 0;
  IOT5302W.Data.TimeOut     = 0;
  IOT5302W.Data.USART_BaudRate  = 0;
  IOT5302W.Data.BaudRateSetStep = 0;
}








 
void API_IOT5302WServer(void)
{ 
  
  if((0==IOT5302W.Conf.USART_BaudRate)||((0==IOT5302W.Conf.IOT5302WPort.USARTx)||(0==IOT5302W.Conf.IOT5302WPort.RS485_CTL_PORT)))  
  {
    return;
  }
  
  
  IOT5302W_DataProcess();
  
  if(0==IOT5302W.Data.Initialized)  
  {
    IOT5302W_Initialize();    
    return;
  }
  IOT5302W.Data.Time++;
  
  if(IOT5302W.Data.Time%300==0)   
  {
    unsigned char TxdLen  = 0;
    IOT5302W.Data.Time=0; 
    IOT5302WGetSNR(CmdBuffer);
    TxdLen  = IOT5302WGetSNR(CmdBuffer);                    
    TxdLen  = IOT5302W_HWSendData(CmdBuffer,TxdLen);	      
  }
}









 
unsigned short API_IOT5302WGetUID(unsigned char* Buffer)
{
  unsigned char i=0;
  unsigned char n=0;
  for(i=0;i<4;i++)
  {
    if(IOT5302W.Data.UID[i])
      n++;
  }
  if(0!=n)  
  {
    if(memcmp(IOT5302W.Data.UID,IOT5302W.Data.UIDbac,4)) 
    {
      memcpy(Buffer,IOT5302W.Data.UID,4);
      memcpy(IOT5302W.Data.UIDbac,IOT5302W.Data.UID,4);
      memset(IOT5302W.Data.UID,0x00,4);
      IOT5302W.Data.TimeCmp = 0;
      return 4; 
    }
    else if(IOT5302W.Data.TimeCmp++>2000)
    {
      memcpy(Buffer,IOT5302W.Data.UID,4);
      IOT5302W.Data.TimeCmp = 0;
      return 4; 
    }
  }
  else
  {
    memset(IOT5302W.Data.UIDbac,0x00,4);
  }
  return 0;
}








 
unsigned short IOT5302W_HWSendData(unsigned char* TxdBuffer,unsigned short length)
{
  unsigned short TxdLen = 0;
  TxdLen = RS485_DMASend(&IOT5302W.Conf.IOT5302WPort,TxdBuffer,length);	
  return TxdLen;
}








 
unsigned short IOT5302W_HWReadData(unsigned char* Buffer)
{
  unsigned short RxdLen = 0;
  RxdLen = RS485_ReadBufferIDLE(&IOT5302W.Conf.IOT5302WPort,Buffer);
  return RxdLen;
}








 
void IOT5302W_HWPortInitialize(unsigned long USART_BaudRate)
{  
  RS485_DMA_ConfigurationNR(&IOT5302W.Conf.IOT5302WPort,USART_BaudRate,128);	
}








 
void IOT5302W_Initialize(void)
{  
  IOT5302W_DataProcess(); 
  if(0!=IOT5302W.Data.Initialized)  
  {
    return;
  }
  
  if(IOT5302W.Data.Time>=1500)
  {
    IOT5302W.Data.Time  = 0;
  }
  
  if(IOT5302W.Data.Time%300==0)
  {    
    if(0==IOT5302W.Data.BaudRateSetStep)
    {
      IOT5302W.Data.USART_BaudRate=9600;
    }
    else if(1==IOT5302W.Data.BaudRateSetStep)
    {
      IOT5302W.Data.USART_BaudRate=19200;
    }
    else if(2==IOT5302W.Data.BaudRateSetStep)
    {
      IOT5302W.Data.USART_BaudRate=38400;
    }
    else if(3==IOT5302W.Data.BaudRateSetStep)
    {
      IOT5302W.Data.USART_BaudRate=57600;
    }
    else if(4==IOT5302W.Data.BaudRateSetStep)
    {
      IOT5302W.Data.USART_BaudRate=115200;
    }
    else
    {
      IOT5302W.Data.USART_BaudRate=IOT5302W.Conf.USART_BaudRate;
      IOT5302W.Data.BaudRateSetStep = 0;
    }
    IOT5302W_HWPortInitialize(IOT5302W.Data.USART_BaudRate);	
    IOT5302W.Data.Time  = 0;
  }
  
  if((50==IOT5302W.Data.Time))
  {
    
    unsigned char TxdLen  = 0;
    unsigned char BaudRateCode  = 0;
    switch(IOT5302W.Conf.USART_BaudRate)    
    {
      case 9600:BaudRateCode=0;
      break;
      case 19200:BaudRateCode=1;
      break;
      case 38400:BaudRateCode=2;
      break;
      case 57600:BaudRateCode=3;
      break;
      case 115200:BaudRateCode=4;
      break;
      default:BaudRateCode=0; 
      break;
    }
    TxdLen  = IOT5302WSetBaudrate(CmdBuffer,BaudRateCode);  
    TxdLen  = IOT5302W_HWSendData(CmdBuffer,TxdLen);	      
    IOT5302W.Data.BaudRateSetStep += 1;
  }
  IOT5302W.Data.Time++;
}








 
void IOT5302W_DataProcess(void)
{
  unsigned char IOT5302WRx[64];
  unsigned short RxdLen = 0;  
  RxdLen  = IOT5302W_HWReadData(IOT5302WRx);
  if(RxdLen)
  {
    if(IOT5302W.Data.DataCount+RxdLen>128)
    {
      IOT5302W.Data.DataCount=0;
      memset(IOT5302W.Data.UID,0x00,4);   
      IOT5302W.Data.TimeOut = 0;    
    }
    memcpy(&IOT5302W.Data.Data[IOT5302W.Data.DataCount],IOT5302WRx,RxdLen); 
    IOT5302W.Data.DataCount+=RxdLen;    
  }
  else if(IOT5302W.Data.TimeOut++>=1500) 
  {
    IOT5302W.Data.Initialized = 0;  
  }
  IOT5302W_DataCheck();
}








 
void IOT5302W_DataCheck(void)
{
  if(0==IOT5302W.Data.DataCount)  
  {
    return;
  }
  else
  {
    unsigned char i=0;
    unsigned char n=0;
    unsigned char bcc=0;
    for(i=0;i<IOT5302W.Data.DataCount;i++)
    {
      if((unsigned char)0xAA==IOT5302W.Data.Data[i]) 
      {
        n=IOT5302W.Data.Data[i+2];
        if(i+2+n+1+1>128)  
        {
          IOT5302W.Data.DataCount=0;
        }
        if((unsigned char)0xBB==IOT5302W.Data.Data[i+2+n+1+1]) 
        {
          bcc=BCC8(&IOT5302W.Data.Data[i+1],n+2);   
          if(bcc==IOT5302W.Data.Data[i+2+n+1])
          {
            IOT5302W.Data.Initialized = 1;  
            if(0x06==IOT5302W.Data.Data[i+2]) 
            {
              memcpy(IOT5302W.Data.UID,&IOT5302W.Data.Data[i+5],4); 
              memset(IOT5302W.Data.Data,0x00,128);   
              IOT5302W.Data.DataCount=0;
              IOT5302W.Data.TimeOut = 0;    
              return;
            }
          }
        }
      }
    }
    if(i>=128-2)
    {
      memset(IOT5302W.Data.Data,0x00,128);   
      IOT5302W.Data.DataCount=0;
    }
  }
  if(IOT5302W.Data.TimeOut++>1500)
  {
    memset(IOT5302W.Data.UID,0x00,4);   
    IOT5302W.Data.TimeOut = 0;    
  }
}








 
unsigned short IOT5302WGetSNR(unsigned char* Buffer)
{
  unsigned short FrameLen=8;
  
  Buffer[0]   = (unsigned char)0xAA; 
  Buffer[1]   = 0x00;         
  Buffer[2]   = 0x03;         
  Buffer[3]   = GET_SNR;      
  Buffer[4]   = 0x26;         
                              
  Buffer[5]   = 00;           
                              
  Buffer[6]  = BCC8(&Buffer[1],5);		
  Buffer[7]  = (unsigned char)0xBB;		
  
  return  FrameLen;
}








 
unsigned short IOT5302WSetBaudrate(unsigned char* Buffer,unsigned char BaudRateCode)
{
  unsigned short FrameLen=7;
  
  Buffer[0]   = (unsigned char)0xAA; 
  Buffer[1]   = 0x00;         
  Buffer[2]   = 0x02;         
  Buffer[3]   = SetBaudrate;  
  Buffer[4]   = BaudRateCode; 
                              
                              
                              
                              
                              
  Buffer[5]  = BCC8(&Buffer[1],4);		
  Buffer[6]  = (unsigned char)0xBB;		
  
  return  FrameLen;
}








 
unsigned short IotReaderGetCmdFrame(Cmddef Cmd,unsigned char* Buffer)
{
  unsigned short FrameLen=0;
  IRDdef* IotReader=(IRDdef*)Buffer;
  IotReader->STX  = (unsigned char)0xAA;   
  IotReader->ID   = 0x00;
  IotReader->Len  = 0X00;     
  IotReader->Cts  = Cmd;
  switch((unsigned char)Cmd)
  {
    case  WriteUserInfo:
          FrameLen  = 0;
    case  ReadUserInfo:
          FrameLen  = 0;
    default:
      FrameLen  = 0;
  }
  return  FrameLen;
}









 
unsigned short IotMifareGetCmdFrame(Cmddef Cmd,unsigned char Sec,unsigned char* Buffer,unsigned char* KeyBuffer)
{
  unsigned short FrameLen=0;




  switch((unsigned char)Cmd)
  {
    case  IotRead:
          Buffer[0]   = (unsigned char)0xAA; 
          Buffer[1]   = 0x00;         
          Buffer[2]   = 0x0A;         
          Buffer[3]   = Cmd;          
          Buffer[4]   = 0x01;         
          Buffer[5]   = Sec;          
          Buffer[6]   = 0x01;         
          Buffer[7]   = KeyBuffer[0]; 
          Buffer[8]   = KeyBuffer[1]; 
          Buffer[9]   = KeyBuffer[2]; 
          Buffer[10]  = KeyBuffer[3]; 
          Buffer[11]  = KeyBuffer[4]; 
          Buffer[12]  = KeyBuffer[5]; 
          Buffer[13]  = BCC8(&Buffer[1],12);		
          Buffer[14]  = (unsigned char)0xBB;		
          FrameLen    = 15;
    break;
    case  IotWrite:
          FrameLen  = 0;
    break;
    default:
      FrameLen  = 0;
  }
  return  FrameLen;
}



