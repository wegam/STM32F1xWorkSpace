#line 1 "..\\..\\Driver\\Protocol\\USART_ISP.C"

















 

#line 1 "..\\..\\Driver\\Protocol\\USART_ISP.H"



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

 
 
 



 
#line 5 "..\\..\\Driver\\Protocol\\USART_ISP.H"
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



 
#line 6 "..\\..\\Driver\\Protocol\\USART_ISP.H"























 

	
typedef	enum _ISP_COMMAND			
{
	ISP_COMMAND_Get		=0x00,		
	ISP_COMMAND_GetVS	=0x01,		
	ISP_COMMAND_GetID	=0x02,		
	ISP_COMMAND_RM		=0x11,		
	ISP_COMMAND_Go		=0x21,		
	ISP_COMMAND_WM		=0x31,		
	ISP_COMMAND_Erase	=0x43,		
	ISP_COMMAND_EE		=0x44,		
	ISP_COMMAND_WP		=0x63,		
	ISP_COMMAND_WU		=0x73,		
	ISP_COMMAND_RP		=0x82,		
	ISP_COMMAND_RU		=0x92			
	
	
	
	
}ISP_COMMAND_TypeDef;

typedef	enum _ISP_Answer	
{
	ISP_ANSWER_ACK		=0x79,		
	ISP_ANSWER_NACK		=0x1F			
}ISP_ANSWER_TypeDef;
typedef	enum _ISP_FUN	
{
	ISP_IDLE			=0xA0,	
	ISP_SLAVE,						
	ISP_MASTER,						
	ISP_WaitDeliver				
}ISP_FUN_TypeDef;






















typedef enum _ISP_SLAVE_STATUS			
{
	ISP_STATUS_IDLE=0x00,				
	ISP_STATUS_UnConnect,				
	ISP_STATUS_WaitConnect,			
	ISP_STATUS_Connectting,			
	ISP_STATUS_Connectted,			
	ISP_STATUS_WaitCommand,			
	ISP_STATUS_WaitEraseAddr,		
	ISP_STATUS_WaitErase,				
	ISP_STATUS_Eraseing,				
	ISP_STATUS_WaitErased,			
	ISP_STATUS_WaitWAddr,				
	ISP_STATUS_WaitWData,				
	ISP_STATUS_WaitWrite,				
	ISP_STATUS_WaitWrited,			
	ISP_STATUS_WaitReadAddr,		
	ISP_STATUS_WaitReadData,		
	ISP_STATUS_WaitLengh,				
	ISP_STATUS_WaitSData,				
	ISP_STATUS_WaitGoAddr,				
	ISP_STATUS_WaitReset				
}ISP_SLAVE_STATUS_TypeDef;
typedef enum _ISP_MASTER_STATUS		
{
	ISP_MSTATUS_IDLE=0x1E,			
	ISP_MSTATUS_ResetDevice,		
	ISP_MSTATUS_WriteConnect,		

	ISP_MSTATUS_Connectted,			
	ISP_MSTATUS_WriteUnprotect,	
	ISP_MSTATUS_WaitUnprotect,	
	ISP_MSTATUS_FlashUnprotected,	
	ISP_MSTATUS_GetFirmwareInf,	
	ISP_MSTATUS_WaitFirmwareInf,	
	ISP_MSTATUS_GetedFirmwareInf,	
	ISP_MSTATUS_WriteGet,				
	ISP_MSTATUS_WaitAck,				
	ISP_MSTATUS_WriteEraseCMD,	
	ISP_MSTATUS_WriteEraseConf,	
	ISP_MSTATUS_EraseDone,	
	ISP_MSTATUS_ReadFirmware,		
	ISP_MSTATUS_WaitFirmware,		
	ISP_MSTATUS_GettedFirmware,	
	ISP_MSTATUS_WriteWM,				
	ISP_MSTATUS_WriteAddr,			
	ISP_MSTATUS_WriteData,			
	ISP_MSTATUS_WriteRM,				
	ISP_MSTATUS_WriteRMLengh,		
	ISP_MSTATUS_Verify,					
	ISP_MSTATUS_WriteGo,				
	ISP_MSTATUS_WriteGoAddr,		
	ISP_MSTATUS_ResetDevice2,		
	ISP_MSTATUS_WaitDeliver			
}ISP_MASTER_STATUS_TypeDef;

typedef	struct _ISP_Version				
{
	unsigned char ISP_VS				;		
	unsigned char ISP_VS_Get		;		
	unsigned char ISP_VS_GetVS	;		
	unsigned char ISP_VS_GetID	;		
	unsigned char ISP_VS_RM			;		
	unsigned char ISP_VS_Go			;		
	unsigned char ISP_VS_WM			;		
	unsigned char ISP_VS_Erase	;		
	unsigned char ISP_VS_WP			;		
	unsigned char ISP_VS_WU			;		
	unsigned char ISP_VS_RP			;		
	unsigned char ISP_VS_RU			;		
}ISP_VERSION_TypeDef;

typedef	struct _ISP_DATA				
{
	unsigned int OffsetAddr				;		
	unsigned int StartAddr				;		
	unsigned int GoAddr						;		
	unsigned int FirmwareLen			;		
	
	unsigned int ReceivedLen			;		
	unsigned int USARTSendLen			;		
	
	unsigned int FLASHNumToSave		;		
	unsigned int FLASHNumToRead		;		
	
	unsigned int ReadAddr					;		
	unsigned int ReadLen					;		
	
	unsigned int WriteAddr				;		
	unsigned int WriteLen					;		
	

	unsigned int 	SumHaveReceived		;		
	unsigned int 	SumHaveWritten		;		
		
	unsigned char Command[2]				;		
	
	unsigned char ISP_RxBuffer[300]	;		
	unsigned char ISP_RvBuffer[300]	;		
	unsigned char ISP_TxBuffer[300]	;		
	unsigned char ISP_TvBuffer[300]	;		

}ISP_DATA_TypeDef;

typedef	struct _ISP_Conf					
{
	USART_TypeDef* 	USARTx															;		
	
	GPIO_TypeDef* 	RESET_CTL_PORT;				
	unsigned short 	RESET_CTL_Pin;				
	
	GPIO_TypeDef* 	BOOT0_CTL_PORT;				
	unsigned short 	BOOT0_CTL_Pin;				
	
	ISP_SLAVE_STATUS_TypeDef	ISP_SLAVE_STATUS					;		
	ISP_SLAVE_STATUS_TypeDef	SlaveLastStatus					;			
	
	ISP_MASTER_STATUS_TypeDef	ISP_MASTER_STATUS					;		
	ISP_MASTER_STATUS_TypeDef	MasterLastStatus					;		
	
	ISP_VERSION_TypeDef				SlaveVersion							;		
	ISP_DATA_TypeDef					ISP_DATA									;		
	ISP_DATA_TypeDef					ISP_MDATA									;		
	ISP_FUN_TypeDef						ISP_FUN										;		
	
	unsigned int 	OverRunTime														;		
	unsigned int 	TimeCount															;		
	unsigned char Connected															;		

}ISP_Conf_TypeDef;


void Usart_ISP_Cof(ISP_Conf_TypeDef *ISP_Conf);
void Usart_ISP_ConfigurationNR(ISP_Conf_TypeDef *ISP_Conf,u32 USART_BaudRate,u32 *RXDBuffer,u32 BufferSize);	
void Usart_ISP_Process(ISP_Conf_TypeDef *ISP_Conf);

void Usart_ISP_SlaveProcess(ISP_Conf_TypeDef *ISP_Conf);		
void Usart_ISP_MasterProcess(ISP_Conf_TypeDef *ISP_Conf);		
void Usart_ISP_CheckFun(ISP_Conf_TypeDef *ISP_Conf);				

void Usart_ISP_ACK(ISP_Conf_TypeDef *ISP_Conf);	
void Usart_ISP_NACK(ISP_Conf_TypeDef *ISP_Conf);		

void Usart_ISP_CommandRead(ISP_Conf_TypeDef *ISP_Conf);			
void Usart_ISP_GetAddr(ISP_Conf_TypeDef *ISP_Conf);					

void Usart_ISP_GetLengh(ISP_Conf_TypeDef *ISP_Conf);				

void Usart_ISP_ReadMemory(ISP_Conf_TypeDef *ISP_Conf);			
void Usart_ISP_WriteMemory(ISP_Conf_TypeDef *ISP_Conf);			
void Usart_ISP_SendBuffer(ISP_Conf_TypeDef *ISP_Conf);			
void Usart_ISP_Erase(ISP_Conf_TypeDef *ISP_Conf);						
u8 Usart_ISP_GetSlaveStatus(ISP_Conf_TypeDef *ISP_Conf);	
void Usart_ISP_SetSlaveStatus(ISP_Conf_TypeDef *ISP_Conf,ISP_SLAVE_STATUS_TypeDef Status);	



void Usart_MISP_StatusProcess(ISP_Conf_TypeDef *ISP_Conf);			
u8 Usart_MISP_GetStatus(ISP_Conf_TypeDef *ISP_Conf);	
void Usart_MISP_GetFirmwareInf(ISP_Conf_TypeDef *ISP_Conf);			
void Usart_MISP_GetDevice(ISP_Conf_TypeDef *ISP_Conf);					
void Usart_MISP_WriteUnprotect(ISP_Conf_TypeDef *ISP_Conf);			
void Usart_MISP_Connect(ISP_Conf_TypeDef *ISP_Conf);						
void Usart_MISP_ResetDevice(ISP_Conf_TypeDef *ISP_Conf);				
void Usart_MISP_SetDevice(ISP_Conf_TypeDef *ISP_Conf);					
void Usart_MISP_RunDevice(ISP_Conf_TypeDef *ISP_Conf);					
void Usart_MISP_CommandSend(ISP_Conf_TypeDef *ISP_Conf,unsigned char Command);	
bool Usart_MISP_ReadAck(ISP_Conf_TypeDef *ISP_Conf);						



void Usart_ISP_Send(ISP_Conf_TypeDef *ISP_Conf);						
void Usart_ISP_Reset(ISP_Conf_TypeDef *ISP_Conf);						








typedef	struct _BSP_Port					
{
	
	USART_TypeDef* 	USARTx															;		
	
	GPIO_TypeDef* 	RESET_CTL_PORT;				
	unsigned short 	RESET_CTL_Pin;				
	
	GPIO_TypeDef* 	BOOT0_CTL_PORT;				
	unsigned short 	BOOT0_CTL_Pin;				
}BSP_Port_TypeDef;


typedef	enum _BSP_COMMAND			
{
	BSP_COMMAND_Get		=0x00,		
	BSP_COMMAND_GetVR	=0x01,		
	BSP_COMMAND_GetID	=0x02,		
	BSP_COMMAND_RM		=0x11,		
	BSP_COMMAND_Go		=0x21,		
	BSP_COMMAND_WM		=0x31,		
	BSP_COMMAND_Erase	=0x43,		
	BSP_COMMAND_EE		=0x44,		
	BSP_COMMAND_WP		=0x63,		
	BSP_COMMAND_WU		=0x73,		
	BSP_COMMAND_RP		=0x82,		
	BSP_COMMAND_RU		=0x92			
	
	
	
	
}BSP_COMMAND_TypeDef;

typedef	struct _BSP_Version				
{
	unsigned char BSP_VS				;		
	unsigned char BSP_VS_Get		;		
	unsigned char BSP_VS_GetVS	;		
	unsigned char BSP_VS_GetID	;		
	unsigned char BSP_VS_RM			;		
	unsigned char BSP_VS_Go			;		
	unsigned char BSP_VS_WM			;		
	unsigned char BSP_VS_Erase	;		
	unsigned char BSP_VS_WP			;		
	unsigned char BSP_VS_WU			;		
	unsigned char BSP_VS_RP			;		
	unsigned char BSP_VS_RU			;		
}BSP_VERSION_TypeDef;

typedef	enum _BSP_Answer	
{
	BSP_ACK		=0x79,		
	BSP_NACK		=0x1F			
}BSP_ANSWER_TypeDef;
typedef	enum _BSP_FUN	
{
	BSP_IDLE			=0xA0,	
	BSP_SLAVE,						
	BSP_MASTER,						
	BSP_WaitDeliver				
}BSP_FUN_TypeDef;
typedef enum _WORK_STEEPS			
{
	WORK_STEEPS_IDLE=0x00,		
	WORK_STEEPS_RESET,				
	WORK_STEEPS_VS,						
	WORK_STEEPS_GET,					
	WORK_STEEPS_GETVS,				
	WORK_STEEPS_GETID,				
	WORK_STEEPS_RM,						
	WORK_STEEPS_WM,						
	WORK_STEEPS_ERASE,				
	WORK_STEEPS_EERASE,				
	WORK_STEEPS_WP,						
	WORK_STEEPS_WU,						
	WORK_STEEPS_RP,						
	WORK_STEEPS_RU,						
	WORK_STEEPS_GO						
}WORK_STEEPS_TypeDef;
typedef enum _BSPS_STATUS			
{
	BSP_STATUS_IDLE=0x3E,				
	BSP_STATUS_UnConnect,				
	BSP_STATUS_WaitConnect,			
	BSP_STATUS_Connectting,			
	BSP_STATUS_Connectted,			
	BSP_STATUS_WaitCommand,			
	BSP_STATUS_WaitEraseAddr,		
	BSP_STATUS_WaitErase,				
	BSP_STATUS_Eraseing,				
	BSP_STATUS_WaitErased,			
	BSP_STATUS_WaitWAddr,				
	BSP_STATUS_WaitWData,				
	BSP_STATUS_WaitWrite,				
	BSP_STATUS_WaitWrited,			
	BSP_STATUS_WaitReadAddr,		
	BSP_STATUS_WaitReadData,		
	BSP_STATUS_WaitLengh,				
	BSP_STATUS_WaitSData,				
	BSP_STATUS_WaitGoAddr,				
	BSP_STATUS_WaitReset				
}BSPS_STATUS_TypeDef;
typedef enum _BSP_MASTER_STATUS		
{
	BSP_MSTATUS_IDLE=0x5E,			
	BSP_MSTATUS_ResetDevice,		
	BSP_MSTATUS_WriteConnect,		
	BSP_MSTATUS_WriteGet,				
	BSP_MSTATUS_WriteGetVR,			
	BSP_MSTATUS_WriteGetID,			
	BSP_MSTATUS_WriteRM,				
	BSP_MSTATUS_WriteErase,			
	BSP_MSTATUS_WriteWM,				
	BSP_MSTATUS_WriteAddr,			
	BSP_MSTATUS_WriteData,			
	BSP_MSTATUS_WriteGo,				
	BSP_MSTATUS_WriteGoAddr,		
	BSP_MSTATUS_WriteUnprotect,	
	BSP_MSTATUS_WriteEraseConf,		
	BSP_MSTATUS_WriteRMLengh,			
	
	BSP_MSTATUS_WaitUnprotect,		
	BSP_MSTATUS_FlashUnprotected,	
	BSP_MSTATUS_GetFirmwareInf,		
	BSP_MSTATUS_WaitFirmwareInf,	
	BSP_MSTATUS_GetedFirmwareInf,	
	BSP_MSTATUS_WaitAck,					
	BSP_MSTATUS_EraseDone,				
	BSP_MSTATUS_ReadFirmware,			
	BSP_MSTATUS_WaitFirmware,			
	BSP_MSTATUS_GettedFirmware,		
	BSP_MSTATUS_Verify,						
	BSP_MSTATUS_StartDevice,			
	BSP_MSTATUS_ERROR,						
	BSP_MSTATUS_TIMEOUT,					
	BSP_MSTATUS_WaitDeliver,			
	BSP_MSTATUS_Connectted				
}BSPM_STATUS_TypeDef;



typedef	struct _BSPM_Info					
{
	BSPM_STATUS_TypeDef		BSP_MASTER_STATUS		;		
	BSPM_STATUS_TypeDef		MasterLastStatus		;		
	
	BSP_VERSION_TypeDef		SlaveVersion				;		
	
	WORK_STEEPS_TypeDef		WORK_STEEPS					;
	
	BSP_ANSWER_TypeDef		ACK;										
	BSP_ANSWER_TypeDef		ACK2;										
	
}BSPM_Info_TypeDef;

typedef	struct _BSPS_Info
{
	BSPS_STATUS_TypeDef		BSP_SLAVE_STATUS		;		
	BSPS_STATUS_TypeDef		SlaveLastStatus			;			
}BSPS_Info_TypeDef;

typedef	struct _BSPM_Public					
{
	unsigned int 	OverRunTime				;		
	unsigned int 	TimeCount					;		
	unsigned int	RetryTimes				;		
	unsigned char Connected					;		
	
	unsigned int 	OffsetAddr				;		
	unsigned int 	StartAddr					;		
	unsigned int 	StepLen						;		
	unsigned int 	GoAddr						;		
	unsigned int 	FirmwareLen				;		
	
	unsigned int 	FLASHNumToSave		;		
	unsigned int 	FLASHNumToRead		;		
	
	unsigned int 	ReadAddr					;		
	unsigned int 	ReadLen						;		
	
	unsigned int 	WriteAddr					;		
	unsigned int 	WriteLen					;		
	
	unsigned int 	ReceivedLen				;		
	unsigned int	USARTSendLen			;		

	unsigned int 	SumHaveReceived		;		
	unsigned int 	SumHaveWritten		;		
		
	unsigned char Command[2]				;		
	
	unsigned char BSP_RxBuffer[300]	;		
	unsigned char BSP_RvBuffer[300]	;		
	unsigned char BSP_TxBuffer[300]	;		
	unsigned char BSP_TvBuffer[300]	;		
	unsigned char BSP_FlashBuffer[300]	;		
	
}BSPM_Public_TypeDef;

typedef	struct _BSP_Conf					
{
	BSP_Port_TypeDef		BSP_Port			;			
	
	BSPM_Info_TypeDef		BSPM_Info			;			
	
	BSPS_Info_TypeDef		BSPS_Info			;			
	
	BSPM_Public_TypeDef	BSP_DATA			;			
	
	BSP_FUN_TypeDef			BSP_FUN				;			
	
	WORK_STEEPS_TypeDef	STEEPS				;			

}BSP_Conf_TypeDef;











void BSP_Configuration(BSP_Conf_TypeDef *BSP_Conf);									
void BSP_Process(BSP_Conf_TypeDef *BSP_Conf);								
void BSP_Reset(BSP_Conf_TypeDef *BSP_Conf);									
void BSP_SendBuffer(BSP_Conf_TypeDef *BSP_Conf);						




void USM_BSP_PROCESS(BSP_Conf_TypeDef *BSP_Conf);					
void USM_BSP_RESET(BSP_Conf_TypeDef *BSP_Conf);						
void USM_BSP_ResetToBSP(BSP_Conf_TypeDef *BSP_Conf);			
void USM_BSP_ResetToRUN(BSP_Conf_TypeDef *BSP_Conf);			
void USM_BSP_SetStatus(BSP_Conf_TypeDef *BSP_Conf,BSPM_STATUS_TypeDef BSPM_STATUS);		
BSPM_STATUS_TypeDef USM_BSP_GetStatus(BSP_Conf_TypeDef *BSP_Conf);		
void USM_BSP_Connect(BSP_Conf_TypeDef *BSP_Conf);					
void USM_BSP_Get(BSP_Conf_TypeDef *BSP_Conf);							
void USM_BSP_GetVR(BSP_Conf_TypeDef *BSP_Conf);						
void USM_BSP_GetId(BSP_Conf_TypeDef *BSP_Conf);						
void USM_BSP_ReadMemory(BSP_Conf_TypeDef *BSP_Conf);			
void USM_BSP_Go(BSP_Conf_TypeDef *BSP_Conf);							
void USM_BSP_WriteMemory(BSP_Conf_TypeDef *BSP_Conf);			
void USM_BSP_WriteAddr(BSP_Conf_TypeDef *BSP_Conf);				
void USM_BSP_WriteData(BSP_Conf_TypeDef *BSP_Conf);				
void USM_BSP_EraseMemory(BSP_Conf_TypeDef *BSP_Conf);			
void USM_BSP_EEraseMemory(BSP_Conf_TypeDef *BSP_Conf);		
void USM_BSP_WriteProtect(BSP_Conf_TypeDef *BSP_Conf);		
void USM_BSP_WriteUnProtect(BSP_Conf_TypeDef *BSP_Conf);	
void USM_BSP_ReadProtect(BSP_Conf_TypeDef *BSP_Conf);			
void USM_BSP_ReadUnProtect(BSP_Conf_TypeDef *BSP_Conf);		
void USM_BSP_GetAck(BSP_Conf_TypeDef *BSP_Conf);					
void USM_BSP_SendCommand(BSP_Conf_TypeDef *BSP_Conf,BSP_COMMAND_TypeDef Command);	



void USS_BSP_PROCESS(BSP_Conf_TypeDef *BSP_Conf);					
void USS_BSP_RESET(BSP_Conf_TypeDef *BSP_Conf);
void USS_BSP_Get(BSP_Conf_TypeDef *BSP_Conf);							
void USS_BSP_GetVR(BSP_Conf_TypeDef *BSP_Conf);						
void USS_BSP_GetId(BSP_Conf_TypeDef *BSP_Conf);						
void USS_BSP_ReadMemory(BSP_Conf_TypeDef *BSP_Conf);			
void USS_BSP_Go(BSP_Conf_TypeDef *BSP_Conf);							
void USS_BSP_WriteMemory(BSP_Conf_TypeDef *BSP_Conf);			
void USS_BSP_EraseMemory(BSP_Conf_TypeDef *BSP_Conf);			
void USS_BSP_EEraseMemory(BSP_Conf_TypeDef *BSP_Conf);		
void USS_BSP_WriteProtect(BSP_Conf_TypeDef *BSP_Conf);		
void USS_BSP_WriteUnProtect(BSP_Conf_TypeDef *BSP_Conf);	
void USS_BSP_ReadProtect(BSP_Conf_TypeDef *BSP_Conf);			
void USS_BSP_ReadUnProtect(BSP_Conf_TypeDef *BSP_Conf);		
void USS_BSP_ACK(BSP_Conf_TypeDef *BSP_Conf);							
void USS_BSP_NACK(BSP_Conf_TypeDef *BSP_Conf);						





















































#line 21 "..\\..\\Driver\\Protocol\\USART_ISP.C"

#line 1 "..\\..\\Driver\\WOW\\INC\\STM32_USART.H"













 










#line 26 "..\\..\\Driver\\WOW\\INC\\STM32_USART.H"
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



#line 23 "..\\..\\Driver\\Protocol\\USART_ISP.C"
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




#line 24 "..\\..\\Driver\\Protocol\\USART_ISP.C"
#line 1 "..\\..\\Driver\\WOW\\INC\\STM32_GPIO.H"













 





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










#line 25 "..\\..\\Driver\\Protocol\\USART_ISP.C"





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



 

#line 31 "..\\..\\Driver\\Protocol\\USART_ISP.C"



#line 35 "..\\..\\Driver\\Protocol\\USART_ISP.C"

#line 37 "..\\..\\Driver\\Protocol\\USART_ISP.C"
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



 
#line 38 "..\\..\\Driver\\Protocol\\USART_ISP.C"
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



 
#line 39 "..\\..\\Driver\\Protocol\\USART_ISP.C"
















 
void Usart_ISP_Cof(ISP_Conf_TypeDef *ISP_Conf)
{
	USART_DMA_ConfigurationEV	(ISP_Conf->USARTx,115200,300);	
	GPIO_Configuration_OPP50	(ISP_Conf->RESET_CTL_PORT,ISP_Conf->RESET_CTL_Pin);			
	GPIO_Configuration_OPP50	(ISP_Conf->BOOT0_CTL_PORT,ISP_Conf->BOOT0_CTL_Pin);			
	Usart_ISP_Reset(ISP_Conf);																																								

}





 
void Usart_ISP_Process(ISP_Conf_TypeDef *ISP_Conf)
{
	if(ISP_Conf->ISP_FUN==ISP_SLAVE)				
	{
		Usart_ISP_SlaveProcess(ISP_Conf);			
	}
	else if(ISP_Conf->ISP_FUN==ISP_MASTER)	
	{
		Usart_ISP_MasterProcess(ISP_Conf);			
	}
	else if(ISP_Conf->ISP_FUN==ISP_WaitDeliver)			
	{
		Usart_ISP_CheckFun(ISP_Conf);					
	}
	else
	{
		Usart_ISP_CheckFun(ISP_Conf);					
	}	


}





 
void Usart_ISP_SlaveProcess(ISP_Conf_TypeDef *ISP_Conf)		
{
	ISP_Conf->ISP_DATA.ReceivedLen=USART_ReadBufferIDLE(ISP_Conf->USARTx,(u8*)ISP_Conf->ISP_DATA.ISP_RvBuffer);	
	if(ISP_Conf->ISP_DATA.ReceivedLen)
	{
		ISP_Conf->OverRunTime=0;									
		if(ISP_Conf->ISP_DATA.ReceivedLen==1)			
		{
			if(ISP_Conf->ISP_DATA.ISP_RvBuffer[0]==0x7F)	
			{
				if(ISP_Conf->Connected==ISP_STATUS_UnConnect)
				{
					Usart_ISP_Reset(ISP_Conf);														
					ISP_Conf->Connected=ISP_STATUS_WaitConnect;						
				}
				else if(ISP_Conf->Connected==ISP_STATUS_Connectting||ISP_Conf->Connected==ISP_STATUS_WaitConnect)
				{
				}
				else if(ISP_Conf->Connected==ISP_STATUS_Connectted)
				{					
					Usart_ISP_SetSlaveStatus(ISP_Conf,ISP_STATUS_WaitCommand);		
					Usart_ISP_ACK(ISP_Conf);
				}																							
			}
		}
		else if(ISP_Conf->ISP_DATA.ReceivedLen==2&&ISP_Conf->ISP_SLAVE_STATUS==ISP_STATUS_WaitCommand)				
		{
			Usart_ISP_CommandRead(ISP_Conf);			
		}
		else if((ISP_Conf->ISP_DATA.ReceivedLen==5&&(ISP_Conf->ISP_SLAVE_STATUS==ISP_STATUS_WaitReadAddr||ISP_Conf->ISP_SLAVE_STATUS==ISP_STATUS_WaitWAddr||ISP_Conf->ISP_SLAVE_STATUS==ISP_STATUS_WaitGoAddr))||ISP_Conf->ISP_SLAVE_STATUS==ISP_STATUS_WaitEraseAddr)				
		{
			Usart_ISP_GetAddr(ISP_Conf);						
		}
		else if(ISP_Conf->ISP_DATA.ReceivedLen==2&&ISP_Conf->ISP_SLAVE_STATUS==ISP_STATUS_WaitLengh)				
		{
			Usart_ISP_GetLengh(ISP_Conf);					
		}
		else if(ISP_Conf->ISP_SLAVE_STATUS==ISP_STATUS_WaitWData)	
		{
			Usart_ISP_WriteMemory(ISP_Conf);			
		}
				
	}
	else if(ISP_Conf->ISP_SLAVE_STATUS==ISP_STATUS_WaitReadData)	
	{
		Usart_ISP_ReadMemory(ISP_Conf);															
	}	
	else if(ISP_Conf->ISP_SLAVE_STATUS==ISP_STATUS_WaitSData)			
	{
		Usart_ISP_SendBuffer(ISP_Conf);															
	}
	else if(ISP_Conf->ISP_SLAVE_STATUS==ISP_STATUS_WaitErase||ISP_Conf->ISP_SLAVE_STATUS==ISP_STATUS_WaitErased)		
	{
		Usart_ISP_Erase(ISP_Conf);						
	}
	else if(ISP_Conf->ISP_SLAVE_STATUS==ISP_STATUS_WaitWrited)	
	{
		Usart_ISP_WriteMemory(ISP_Conf);			
	}
	else if(ISP_Conf->ISP_SLAVE_STATUS==ISP_STATUS_WaitReset)	
	{
		Usart_ISP_CheckFun(ISP_Conf);					
	}
	else	if((ISP_Conf->ISP_SLAVE_STATUS!=ISP_STATUS_IDLE)||(ISP_Conf->ISP_FUN==ISP_SLAVE))				
	{
		ISP_Conf->OverRunTime=ISP_Conf->OverRunTime+1;					
		if(ISP_Conf->OverRunTime>=5000000)				
		Usart_ISP_Reset(ISP_Conf);								
	}

}





 
void Usart_ISP_MasterProcess(ISP_Conf_TypeDef *ISP_Conf)		
{
	Usart_MISP_StatusProcess(ISP_Conf);			
	Usart_ISP_Send(ISP_Conf);						
}





 
void Usart_ISP_CheckFun(ISP_Conf_TypeDef *ISP_Conf)				
{
	u32 delaytime=0x00;










	
	

	
	
	if(ISP_Conf->ISP_SLAVE_STATUS==ISP_STATUS_WaitReset)	
	{
		GPIO_Configuration_IPD(ISP_Conf->BOOT0_CTL_PORT,ISP_Conf->BOOT0_CTL_Pin);				
		while((GPIO_ReadInputDataBit(ISP_Conf->BOOT0_CTL_PORT,ISP_Conf->BOOT0_CTL_Pin)==Bit_SET));
		Usart_ISP_Reset(ISP_Conf);						
	}
	else if(ISP_Conf->ISP_MASTER_STATUS==ISP_MSTATUS_WaitDeliver)	
	{
		GPIO_Configuration_IPD(ISP_Conf->RESET_CTL_PORT,ISP_Conf->RESET_CTL_Pin);			
		if(GPIO_ReadInputDataBit(ISP_Conf->RESET_CTL_PORT,ISP_Conf->RESET_CTL_Pin)==Bit_SET)
		{

			ISP_Conf->TimeCount=0;
		}
		else
		{
			if(ISP_Conf->TimeCount++>20000)
				Usart_ISP_Reset(ISP_Conf);						
		}
	}
	else
	{	
		GPIO_Configuration_IPD(ISP_Conf->BOOT0_CTL_PORT,ISP_Conf->BOOT0_CTL_Pin);				
		while(delaytime++<0xFFFF)
		{
			if((GPIO_ReadInputDataBit(ISP_Conf->BOOT0_CTL_PORT,ISP_Conf->BOOT0_CTL_Pin)==Bit_SET))
			{
				ISP_Conf->ISP_FUN=ISP_SLAVE;		
				return;
			}
		}
		
		{
			Usart_ISP_Reset(ISP_Conf);			
			ISP_Conf->ISP_FUN=ISP_MASTER;		
			ISP_Conf->ISP_MASTER_STATUS	=ISP_MSTATUS_IDLE;
			GPIO_Configuration_OPP50	(ISP_Conf->RESET_CTL_PORT,ISP_Conf->RESET_CTL_Pin);			
			GPIO_Configuration_OPP50	(ISP_Conf->BOOT0_CTL_PORT,ISP_Conf->BOOT0_CTL_Pin);			
		}
	}		
}





 
void Usart_ISP_ACK(ISP_Conf_TypeDef *ISP_Conf)	
{
	ISP_Conf->ISP_DATA.Command[0]=ISP_ANSWER_ACK;
	USART_DMASend(ISP_Conf->USARTx,(u8*)ISP_Conf->ISP_DATA.Command,1);	
}





 
void Usart_ISP_NACK(ISP_Conf_TypeDef *ISP_Conf)		
{
	ISP_Conf->ISP_DATA.Command[0]=ISP_ANSWER_NACK;
	USART_DMASend(ISP_Conf->USARTx,(u8*)ISP_Conf->ISP_DATA.Command,1);	
}






 
void Usart_ISP_CommandRead(ISP_Conf_TypeDef *ISP_Conf)			
{

	unsigned char C0=ISP_Conf->ISP_DATA.ISP_RvBuffer[0];
	unsigned char C1=ISP_Conf->ISP_DATA.ISP_RvBuffer[1];
	C1=C1^0XFF;
	if(C0!=C1)
	{
		return;
	}
	if(C0==ISP_COMMAND_Get)			
	{
		ISP_Conf->ISP_DATA.ISP_TvBuffer[0]=ISP_ANSWER_ACK;			
		ISP_Conf->ISP_DATA.ISP_TvBuffer[1]=0x0B;								
		ISP_Conf->ISP_DATA.ISP_TvBuffer[2]=0x22;								
		ISP_Conf->ISP_DATA.ISP_TvBuffer[3]=ISP_COMMAND_Get;		
		ISP_Conf->ISP_DATA.ISP_TvBuffer[4]=ISP_COMMAND_GetVS;	
		ISP_Conf->ISP_DATA.ISP_TvBuffer[5]=ISP_COMMAND_GetID;	
		ISP_Conf->ISP_DATA.ISP_TvBuffer[6]=ISP_COMMAND_RM;			
		ISP_Conf->ISP_DATA.ISP_TvBuffer[7]=ISP_COMMAND_Go;			
		ISP_Conf->ISP_DATA.ISP_TvBuffer[8]=ISP_COMMAND_WM;			
		ISP_Conf->ISP_DATA.ISP_TvBuffer[9]=ISP_COMMAND_Erase;	
		ISP_Conf->ISP_DATA.ISP_TvBuffer[10]=ISP_COMMAND_WP;		
		ISP_Conf->ISP_DATA.ISP_TvBuffer[11]=ISP_COMMAND_WU;		
		ISP_Conf->ISP_DATA.ISP_TvBuffer[12]=ISP_COMMAND_RP;		
		ISP_Conf->ISP_DATA.ISP_TvBuffer[13]=ISP_COMMAND_RU;		
		ISP_Conf->ISP_DATA.ISP_TvBuffer[14]=ISP_ANSWER_ACK;		
		
		Usart_ISP_SetSlaveStatus(ISP_Conf,ISP_STATUS_WaitCommand);		
		ISP_Conf->ISP_DATA.USARTSendLen=15;												
		
		memcpy(ISP_Conf->ISP_DATA.ISP_TxBuffer, ISP_Conf->ISP_DATA.ISP_TvBuffer, ISP_Conf->ISP_DATA.USARTSendLen);
		USART_DMASend(ISP_Conf->USARTx,(u8*)ISP_Conf->ISP_DATA.ISP_TxBuffer,ISP_Conf->ISP_DATA.USARTSendLen);	
			
	}
	else if(C0==ISP_COMMAND_GetVS)	
	{
		ISP_Conf->ISP_DATA.ISP_TvBuffer[0]=ISP_ANSWER_ACK;		
		ISP_Conf->ISP_DATA.ISP_TvBuffer[1]=0x22;							
		ISP_Conf->ISP_DATA.ISP_TvBuffer[2]=0x00;							
		ISP_Conf->ISP_DATA.ISP_TvBuffer[3]=0x00;							
		ISP_Conf->ISP_DATA.ISP_TvBuffer[4]=ISP_ANSWER_ACK;		
		
		Usart_ISP_SetSlaveStatus(ISP_Conf,ISP_STATUS_WaitCommand);		
		ISP_Conf->ISP_DATA.USARTSendLen=5;												
		
		memcpy(ISP_Conf->ISP_DATA.ISP_TxBuffer, ISP_Conf->ISP_DATA.ISP_TvBuffer, ISP_Conf->ISP_DATA.USARTSendLen);
		USART_DMASend(ISP_Conf->USARTx,(u8*)ISP_Conf->ISP_DATA.ISP_TxBuffer,ISP_Conf->ISP_DATA.USARTSendLen);	
	}
	else if(C0==ISP_COMMAND_GetID)	
	{
		ISP_Conf->ISP_DATA.ISP_TvBuffer[0]=ISP_ANSWER_ACK;		
		ISP_Conf->ISP_DATA.ISP_TvBuffer[1]=0x01;							
		ISP_Conf->ISP_DATA.ISP_TvBuffer[2]=0x04;							
		ISP_Conf->ISP_DATA.ISP_TvBuffer[3]=0x10;							
		ISP_Conf->ISP_DATA.ISP_TvBuffer[4]=ISP_ANSWER_ACK;		
		
		Usart_ISP_SetSlaveStatus(ISP_Conf,ISP_STATUS_WaitCommand);		
		ISP_Conf->ISP_DATA.USARTSendLen=5;												
		
		memcpy(ISP_Conf->ISP_DATA.ISP_TxBuffer, ISP_Conf->ISP_DATA.ISP_TvBuffer, ISP_Conf->ISP_DATA.USARTSendLen);
		USART_DMASend(ISP_Conf->USARTx,(u8*)ISP_Conf->ISP_DATA.ISP_TxBuffer,ISP_Conf->ISP_DATA.USARTSendLen);	
	}
	else if(C0==ISP_COMMAND_RM)			
	{
		Usart_ISP_SetSlaveStatus(ISP_Conf,ISP_STATUS_WaitReadAddr);			
		Usart_ISP_ACK(ISP_Conf);															
		return;
	}
	else if(C0==ISP_COMMAND_Go)			
	{
		Usart_ISP_SetSlaveStatus(ISP_Conf,ISP_STATUS_WaitGoAddr);			
		Usart_ISP_ACK(ISP_Conf);	
	}
	else if(C0==ISP_COMMAND_WM)			
	{
		Usart_ISP_SetSlaveStatus(ISP_Conf,ISP_STATUS_WaitWAddr);			
		Usart_ISP_ACK(ISP_Conf);	
	}
	else if(C0==ISP_COMMAND_Erase)	
	{
		Usart_ISP_SetSlaveStatus(ISP_Conf,ISP_STATUS_WaitEraseAddr);	
		Usart_ISP_ACK(ISP_Conf);	
	}
	else if(C0==ISP_COMMAND_EE)			
	{
		Usart_ISP_SetSlaveStatus(ISP_Conf,ISP_STATUS_WaitEraseAddr);	
		Usart_ISP_ACK(ISP_Conf);	
	}
	else if(C0==ISP_COMMAND_WP)			
	{
		


 
		return;			
	}
	else if(C0==ISP_COMMAND_WU)			
	{
		


 
		return;			
	}
	else if(C0==ISP_COMMAND_RP)			
	{
		


 
		return;			
	}
	else if(C0==ISP_COMMAND_RU)			
	{
		



 
		return;			
	}
	else
	{
	}	





}





 
void Usart_ISP_GetAddr(ISP_Conf_TypeDef *ISP_Conf)		
{	
	
	
	if(ISP_Conf->ISP_SLAVE_STATUS==ISP_STATUS_WaitEraseAddr)			
	{
		unsigned char C0=ISP_Conf->ISP_DATA.ISP_RvBuffer[0];
		unsigned char C1=ISP_Conf->ISP_DATA.ISP_RvBuffer[1];
		C1=C1^0XFF;
		if(C0!=C1)
		{
			return;
		}
		ISP_Conf->ISP_DATA.WriteAddr=C0;													
		Usart_ISP_SetSlaveStatus(ISP_Conf,ISP_STATUS_WaitErase);						
	}
	else
	{
		unsigned int addr=0x00;		
		unsigned char Bcc=BCC8(ISP_Conf->ISP_DATA.ISP_RvBuffer,4);		
		if(Bcc!=ISP_Conf->ISP_DATA.ISP_RvBuffer[4])
		{
			return;
		}
		else		
		{		
			addr=	(ISP_Conf->ISP_DATA.ISP_RvBuffer[0])<<24;
			addr+=(ISP_Conf->ISP_DATA.ISP_RvBuffer[1])<<16;
			addr+=(ISP_Conf->ISP_DATA.ISP_RvBuffer[2])<<8;
			addr+=(ISP_Conf->ISP_DATA.ISP_RvBuffer[3]);
		}
		
		if(ISP_Conf->ISP_SLAVE_STATUS==ISP_STATUS_WaitReadAddr)				
		{
			ISP_Conf->ISP_DATA.ReadAddr=addr;														
			Usart_ISP_SetSlaveStatus(ISP_Conf,ISP_STATUS_WaitLengh);						
			Usart_ISP_ACK(ISP_Conf);	
		}
		else if(ISP_Conf->ISP_SLAVE_STATUS==ISP_STATUS_WaitWAddr)			
		{
			if(ISP_Conf->ISP_DATA.OffsetAddr==0)
			{
				ISP_Conf->ISP_DATA.OffsetAddr=addr;
			}
		
			ISP_Conf->ISP_DATA.WriteAddr=addr;													
			Usart_ISP_SetSlaveStatus(ISP_Conf,ISP_STATUS_WaitWData);		

			Usart_ISP_ACK(ISP_Conf);	
		}
		else if(ISP_Conf->ISP_SLAVE_STATUS==ISP_STATUS_WaitGoAddr)			
		{
			u32 timedelay=0;
			ISP_Conf->ISP_DATA.GoAddr=addr;																
			ISP_Conf->Connected=ISP_STATUS_UnConnect;											

			Usart_ISP_ACK(ISP_Conf);	
			while(timedelay++<0xFF);

		}
	}
}





 
void Usart_ISP_GetLengh(ISP_Conf_TypeDef *ISP_Conf)				
{	
	
	unsigned char C0=ISP_Conf->ISP_DATA.ISP_RvBuffer[0];
	unsigned char C1=ISP_Conf->ISP_DATA.ISP_RvBuffer[1];
	C1=C1^0XFF;
	if(C0!=C1)		
	{
		return;
	}
	else
	{
		ISP_Conf->ISP_DATA.USARTSendLen=C0;										
		Usart_ISP_SetSlaveStatus(ISP_Conf,ISP_STATUS_WaitReadData);	
	}

}







 
void Usart_ISP_ReadMemory(ISP_Conf_TypeDef *ISP_Conf)		
{	
#line 513 "..\\..\\Driver\\Protocol\\USART_ISP.C"
	{
		
		
		
		
		
		
	}

}





 
void Usart_ISP_WriteMemory(ISP_Conf_TypeDef *ISP_Conf)	
{	
#line 552 "..\\..\\Driver\\Protocol\\USART_ISP.C"
	{
		if(ISP_Conf->ISP_SLAVE_STATUS==ISP_STATUS_WaitWData)		
		{
			unsigned char	Wlen=ISP_Conf->ISP_DATA.ISP_RvBuffer[0];						
			unsigned char Bcc=BCC8(ISP_Conf->ISP_DATA.ISP_RvBuffer,Wlen+2);		
			if(Bcc!=ISP_Conf->ISP_DATA.ISP_RvBuffer[Wlen+2])
			{
				return;
			}
			ISP_Conf->ISP_DATA.WriteLen=ISP_Conf->ISP_DATA.ISP_RvBuffer[0];		
			
			memcpy(ISP_Conf->ISP_DATA.ISP_RvBuffer, &ISP_Conf->ISP_DATA.ISP_RvBuffer[1], ISP_Conf->ISP_DATA.WriteLen+1);	
			Usart_ISP_SetSlaveStatus(ISP_Conf,ISP_STATUS_WaitWrite);				
		}
		else if(ISP_Conf->ISP_SLAVE_STATUS==ISP_STATUS_WaitWrited)	
		{
			
			Usart_ISP_ACK(ISP_Conf);	
			Usart_ISP_SetSlaveStatus(ISP_Conf,ISP_STATUS_WaitCommand);				
		}
	}










}





 
void Usart_ISP_SendBuffer(ISP_Conf_TypeDef *ISP_Conf)	
{	

	ISP_Conf->ISP_DATA.ISP_TxBuffer[0]=0x79;
	memcpy(&ISP_Conf->ISP_DATA.ISP_TxBuffer[1], ISP_Conf->ISP_DATA.ISP_TvBuffer, ISP_Conf->ISP_DATA.USARTSendLen+1);	
	USART_DMASend(ISP_Conf->USARTx,(u8*)ISP_Conf->ISP_DATA.ISP_TxBuffer,ISP_Conf->ISP_DATA.USARTSendLen+2);				
	Usart_ISP_SetSlaveStatus(ISP_Conf,ISP_STATUS_WaitCommand);				

	









}





 
void Usart_ISP_Erase(ISP_Conf_TypeDef *ISP_Conf)				
{
	
#line 635 "..\\..\\Driver\\Protocol\\USART_ISP.C"
	{
		if(ISP_Conf->ISP_SLAVE_STATUS==ISP_STATUS_WaitErase)	
		{
			if(ISP_Conf->ISP_DATA.WriteAddr==0xFF)	
			{
				Usart_ISP_SetSlaveStatus(ISP_Conf,ISP_STATUS_Eraseing);			
			}
		}
		else if(ISP_Conf->ISP_SLAVE_STATUS==ISP_STATUS_WaitErased)			
		{
			Usart_ISP_ACK(ISP_Conf);							
			Usart_ISP_SetSlaveStatus(ISP_Conf,ISP_STATUS_WaitCommand);	
		}
		
	}	

}





 
u8 Usart_ISP_GetSlaveStatus(ISP_Conf_TypeDef *ISP_Conf)	
{	
	return(ISP_Conf->ISP_SLAVE_STATUS);		
}





 
void Usart_ISP_SetSlaveStatus(ISP_Conf_TypeDef *ISP_Conf,ISP_SLAVE_STATUS_TypeDef Status)	
{	
	ISP_Conf->ISP_SLAVE_STATUS=Status;	
}




















 
void Usart_MISP_StatusProcess(ISP_Conf_TypeDef *ISP_Conf)			
{
	if(ISP_Conf->OverRunTime++>2000000)			
	{
		Usart_ISP_Reset(ISP_Conf);						
	}
	if(ISP_Conf->ISP_MASTER_STATUS==ISP_MSTATUS_IDLE)								
	{
		ISP_Conf->ISP_MASTER_STATUS=ISP_MSTATUS_ResetDevice;
		Usart_MISP_RunDevice(ISP_Conf);						
		ISP_Conf->OverRunTime=0;									
		Usart_MISP_GetFirmwareInf(ISP_Conf);			
	}
	else if(ISP_Conf->ISP_MASTER_STATUS==ISP_MSTATUS_ResetDevice)		
	{
		if(ISP_Conf->TimeCount++<10000)					
		{			
			Usart_MISP_ResetDevice(ISP_Conf);			
		}
		else
		{
			ISP_Conf->TimeCount=0;																			
			ISP_Conf->ISP_MASTER_STATUS=ISP_MSTATUS_WriteConnect;				
			Usart_MISP_SetDevice(ISP_Conf);															
		}
	}
	else if(ISP_Conf->ISP_MASTER_STATUS==ISP_MSTATUS_WriteConnect)	
	{
		ISP_Conf->MasterLastStatus=ISP_MSTATUS_WriteConnect;					
		ISP_Conf->ISP_MASTER_STATUS=ISP_MSTATUS_WaitAck;							
		Usart_MISP_Connect(ISP_Conf);																	
	}
	else if(ISP_Conf->ISP_MASTER_STATUS==ISP_MSTATUS_Connectted)		
	{
		ISP_Conf->MasterLastStatus=ISP_MSTATUS_WriteGet;							
		ISP_Conf->ISP_MASTER_STATUS=ISP_MSTATUS_WaitAck;							
		Usart_MISP_GetDevice(ISP_Conf);																
	}
	else if(ISP_Conf->ISP_MASTER_STATUS==ISP_MSTATUS_WriteUnprotect)		
	{
		ISP_Conf->MasterLastStatus=ISP_MSTATUS_WriteUnprotect;				
		ISP_Conf->ISP_MASTER_STATUS=ISP_MSTATUS_WaitAck;							
		Usart_MISP_WriteUnprotect(ISP_Conf);													
	}
	else if(ISP_Conf->ISP_MASTER_STATUS==ISP_MSTATUS_WaitUnprotect)		
	{
		ISP_Conf->MasterLastStatus=ISP_MSTATUS_WaitUnprotect;				
		ISP_Conf->ISP_MASTER_STATUS=ISP_MSTATUS_WaitAck;							
	}
	else if(ISP_Conf->ISP_MASTER_STATUS==ISP_MSTATUS_FlashUnprotected)		
	{
		ISP_Conf->MasterLastStatus	=ISP_MSTATUS_WriteEraseCMD;							
		ISP_Conf->ISP_MASTER_STATUS	=ISP_MSTATUS_WaitAck;										
		Usart_MISP_CommandSend(ISP_Conf,ISP_COMMAND_Erase);									
	}
	else if(ISP_Conf->ISP_MASTER_STATUS==ISP_MSTATUS_WriteEraseConf)						
	{
		ISP_Conf->MasterLastStatus	=ISP_MSTATUS_WriteEraseConf;								
		ISP_Conf->ISP_MASTER_STATUS	=ISP_MSTATUS_WaitAck;												
		Usart_MISP_CommandSend(ISP_Conf,0xFF);																	
	}	
	else if(ISP_Conf->ISP_MASTER_STATUS==ISP_MSTATUS_EraseDone)						
	{
		ISP_Conf->MasterLastStatus	=ISP_MSTATUS_GetFirmwareInf;								
		ISP_Conf->ISP_MASTER_STATUS	=ISP_MSTATUS_GetFirmwareInf;							
	}	
	else if(ISP_Conf->ISP_MASTER_STATUS==ISP_MSTATUS_GetedFirmwareInf)
	{
		ISP_Conf->MasterLastStatus	=ISP_MSTATUS_WriteWM;	
		ISP_Conf->ISP_MASTER_STATUS	=ISP_MSTATUS_WriteWM;
		ISP_Conf->ISP_MDATA.WriteAddr=ISP_Conf->ISP_MDATA.GoAddr;							

	}
	else if(ISP_Conf->ISP_MASTER_STATUS==ISP_MSTATUS_ReadFirmware)
	{
		ISP_Conf->MasterLastStatus	=ISP_MSTATUS_ReadFirmware;
		ISP_Conf->ISP_MASTER_STATUS	=ISP_MSTATUS_ReadFirmware;
	}
	else if(ISP_Conf->ISP_MASTER_STATUS==ISP_MSTATUS_WaitFirmware)
	{
		if(ISP_Conf->OverRunTime++>400000)				
		{
			Usart_ISP_Reset(ISP_Conf);							
		}
	}
	else if(ISP_Conf->ISP_MASTER_STATUS==ISP_MSTATUS_GettedFirmware)	
	{
		ISP_Conf->ISP_MASTER_STATUS=ISP_MSTATUS_WriteData;

		ISP_Conf->ISP_MDATA.WriteAddr+=0xFF;
	}
	else if(ISP_Conf->ISP_MASTER_STATUS==ISP_MSTATUS_WriteWM)
	{
		ISP_Conf->MasterLastStatus	=ISP_MSTATUS_WriteWM;
		ISP_Conf->ISP_MASTER_STATUS	=ISP_MSTATUS_WaitAck;
		Usart_MISP_CommandSend(ISP_Conf,ISP_COMMAND_WM);										
	}
	else if(ISP_Conf->ISP_MASTER_STATUS==ISP_MSTATUS_WriteAddr)						
	{
		ISP_Conf->MasterLastStatus	=ISP_MSTATUS_WriteAddr;
		ISP_Conf->ISP_MASTER_STATUS	=ISP_MSTATUS_WaitAck;
		ISP_Conf->ISP_DATA.ISP_TvBuffer[0]=ISP_Conf->ISP_MDATA.WriteAddr>>24;
		ISP_Conf->ISP_DATA.ISP_TvBuffer[1]=ISP_Conf->ISP_MDATA.WriteAddr>>16;
		ISP_Conf->ISP_DATA.ISP_TvBuffer[2]=ISP_Conf->ISP_MDATA.WriteAddr>>8;
		ISP_Conf->ISP_DATA.ISP_TvBuffer[3]=ISP_Conf->ISP_MDATA.WriteAddr>>0;
		ISP_Conf->ISP_DATA.ISP_TvBuffer[4]=BCC8(ISP_Conf->ISP_DATA.ISP_TvBuffer,4);		

		ISP_Conf->ISP_DATA.USARTSendLen=5;

	}
	else if(ISP_Conf->ISP_MASTER_STATUS==ISP_MSTATUS_WriteData)						
	{
		ISP_Conf->MasterLastStatus	=ISP_MSTATUS_WriteData;
		ISP_Conf->ISP_MASTER_STATUS	=ISP_MSTATUS_WaitAck;
		ISP_Conf->ISP_DATA.USARTSendLen=ISP_Conf->ISP_MDATA.WriteLen;


	}
	else if(ISP_Conf->ISP_MASTER_STATUS==ISP_MSTATUS_WriteGo)						
	{
		ISP_Conf->MasterLastStatus	=ISP_MSTATUS_WriteGo;
		ISP_Conf->ISP_MASTER_STATUS	=ISP_MSTATUS_WaitAck;
		Usart_MISP_CommandSend(ISP_Conf,ISP_COMMAND_Go);										
	}
	else if(ISP_Conf->ISP_MASTER_STATUS==ISP_MSTATUS_WriteGoAddr)						
	{
		ISP_Conf->MasterLastStatus	=ISP_MSTATUS_WriteGoAddr;
		ISP_Conf->ISP_MASTER_STATUS	=ISP_MSTATUS_WaitAck;
		
		ISP_Conf->ISP_DATA.ISP_TvBuffer[0]=ISP_Conf->ISP_MDATA.StartAddr>>24;
		ISP_Conf->ISP_DATA.ISP_TvBuffer[1]=ISP_Conf->ISP_MDATA.StartAddr>>16;
		ISP_Conf->ISP_DATA.ISP_TvBuffer[2]=ISP_Conf->ISP_MDATA.StartAddr>>8;
		ISP_Conf->ISP_DATA.ISP_TvBuffer[3]=ISP_Conf->ISP_MDATA.StartAddr>>0;
		ISP_Conf->ISP_DATA.ISP_TvBuffer[4]=BCC8(ISP_Conf->ISP_DATA.ISP_TvBuffer,4);		
		ISP_Conf->ISP_DATA.USARTSendLen=5;
		

	}
	else if(ISP_Conf->ISP_MASTER_STATUS==ISP_MSTATUS_ResetDevice2)						
	{
		u32 timedelay=0;
		Usart_MISP_ResetDevice(ISP_Conf);				
		while(timedelay++<0xFFF);
		Usart_MISP_RunDevice(ISP_Conf);					
		while(timedelay++<0xFFF);
		ISP_Conf->ISP_MASTER_STATUS=ISP_MSTATUS_WaitDeliver;		
		ISP_Conf->ISP_FUN=ISP_WaitDeliver;			


		
	}
	
	else if(ISP_Conf->ISP_MASTER_STATUS==ISP_MSTATUS_GetFirmwareInf||ISP_Conf->ISP_MASTER_STATUS==ISP_MSTATUS_WaitFirmwareInf)
	{
		if(ISP_Conf->OverRunTime++>400000)				
		{
			Usart_ISP_Reset(ISP_Conf);							
		}
	}
	else if(ISP_Conf->ISP_MASTER_STATUS==ISP_MSTATUS_WaitAck)				
	{
		bool Result=FALSE;				
		Result=Usart_MISP_ReadAck(ISP_Conf);					
		if(Result==TRUE)					
		{
			if(ISP_Conf->MasterLastStatus==ISP_MSTATUS_WriteConnect)			
			{
				ISP_Conf->ISP_MASTER_STATUS=ISP_MSTATUS_Connectted;					
			}
			else if(ISP_Conf->MasterLastStatus==ISP_MSTATUS_WriteGet)	
			{
				ISP_Conf->ISP_MASTER_STATUS=ISP_MSTATUS_WriteUnprotect;			
			}
			else if(ISP_Conf->MasterLastStatus==ISP_MSTATUS_WriteUnprotect)	
			{
				ISP_Conf->ISP_MASTER_STATUS=ISP_MSTATUS_WaitUnprotect;			
			}
			else if(ISP_Conf->MasterLastStatus==ISP_MSTATUS_WaitUnprotect)	
			{
				ISP_Conf->ISP_MASTER_STATUS=ISP_MSTATUS_FlashUnprotected;			
			}
			else if(ISP_Conf->MasterLastStatus==ISP_MSTATUS_WriteEraseCMD)	
			{
				ISP_Conf->ISP_MASTER_STATUS=ISP_MSTATUS_WriteEraseConf;				
			}
			else if(ISP_Conf->MasterLastStatus==ISP_MSTATUS_WriteEraseConf)	
			{
				ISP_Conf->ISP_MASTER_STATUS=ISP_MSTATUS_EraseDone;						
			}
			else if(ISP_Conf->MasterLastStatus==ISP_MSTATUS_WriteWM)	
			{
				ISP_Conf->ISP_MASTER_STATUS=ISP_MSTATUS_WriteAddr;						
			}
			else if(ISP_Conf->MasterLastStatus==ISP_MSTATUS_WriteAddr)	
			{
				ISP_Conf->ISP_MASTER_STATUS=ISP_MSTATUS_ReadFirmware;						
			}
			else if(ISP_Conf->MasterLastStatus==ISP_MSTATUS_WriteData)	
			{
				ISP_Conf->ISP_MDATA.SumHaveWritten+=ISP_Conf->ISP_MDATA.WriteLen-2;
				if(ISP_Conf->ISP_MDATA.SumHaveWritten<ISP_Conf->ISP_MDATA.FirmwareLen)
				{
					ISP_Conf->ISP_MASTER_STATUS=ISP_MSTATUS_WriteWM;						
					ISP_Conf->ISP_MDATA.WriteAddr+=1;					
				}
				else
				{
					ISP_Conf->ISP_MASTER_STATUS=ISP_MSTATUS_WriteGo;						
				}
			}
			else if(ISP_Conf->MasterLastStatus==ISP_MSTATUS_WriteGo)				
			{
				ISP_Conf->ISP_MASTER_STATUS	=ISP_MSTATUS_WriteGoAddr;
			}
			else if(ISP_Conf->MasterLastStatus==ISP_MSTATUS_WriteGoAddr)		
			{
				ISP_Conf->ISP_MASTER_STATUS	=ISP_MSTATUS_ResetDevice2;
			}
		}
		else											
		{
			if(ISP_Conf->MasterLastStatus==ISP_MSTATUS_WriteConnect)			
			{
				if(ISP_Conf->TimeCount++>1000)						
				{
					ISP_Conf->TimeCount=0;									
					ISP_Conf->ISP_MASTER_STATUS=ISP_MSTATUS_WriteConnect;		
				}
				if(ISP_Conf->OverRunTime++>100000)				
				{
					Usart_ISP_Reset(ISP_Conf);							
				}
			}




		}
	}
	
}
u8 Usart_MISP_GetStatus(ISP_Conf_TypeDef *ISP_Conf)	
{	
	return(ISP_Conf->ISP_MASTER_STATUS);		
}





 
void Usart_MISP_GetFirmwareInf(ISP_Conf_TypeDef *ISP_Conf)			
{
	
}





 
void Usart_MISP_GetDevice(ISP_Conf_TypeDef *ISP_Conf)			
{
	Usart_MISP_CommandSend(ISP_Conf,ISP_COMMAND_Get);				
}





 
void Usart_MISP_WriteUnprotect(ISP_Conf_TypeDef *ISP_Conf)			
{
	Usart_MISP_CommandSend(ISP_Conf,ISP_COMMAND_WU);	
}





 
void Usart_MISP_Connect(ISP_Conf_TypeDef *ISP_Conf)					
{
		ISP_Conf->ISP_DATA.USARTSendLen=1;										
		ISP_Conf->ISP_DATA.ISP_TvBuffer[0]=0x7F;							
}





 
void Usart_MISP_ResetDevice(ISP_Conf_TypeDef *ISP_Conf)			
{
	GPIO_SetBits(ISP_Conf->BOOT0_CTL_PORT,ISP_Conf->BOOT0_CTL_Pin);		
	GPIO_ResetBits(ISP_Conf->RESET_CTL_PORT,ISP_Conf->RESET_CTL_Pin);	
}





 
void Usart_MISP_SetDevice(ISP_Conf_TypeDef *ISP_Conf)			
{
	GPIO_SetBits(ISP_Conf->BOOT0_CTL_PORT,ISP_Conf->BOOT0_CTL_Pin);			
	GPIO_SetBits(ISP_Conf->RESET_CTL_PORT,ISP_Conf->RESET_CTL_Pin);			
}





 
void Usart_MISP_RunDevice(ISP_Conf_TypeDef *ISP_Conf)			
{
	GPIO_ResetBits(ISP_Conf->BOOT0_CTL_PORT,ISP_Conf->BOOT0_CTL_Pin);		
	GPIO_SetBits(ISP_Conf->RESET_CTL_PORT,ISP_Conf->RESET_CTL_Pin);			
}





 
void Usart_MISP_CommandSend(ISP_Conf_TypeDef *ISP_Conf,unsigned char Command)	
{
	ISP_Conf->ISP_DATA.Command[0]=Command;
	ISP_Conf->ISP_DATA.Command[1]=Command^0XFF;
	USART_DMASend(ISP_Conf->USARTx,(u8*)ISP_Conf->ISP_DATA.Command,2);	
}





 
bool Usart_MISP_ReadAck(ISP_Conf_TypeDef *ISP_Conf)			
{
	ISP_Conf->ISP_DATA.ReceivedLen=USART_ReadBufferIDLE(ISP_Conf->USARTx,(u8*)ISP_Conf->ISP_DATA.ISP_RvBuffer);	
	if(ISP_Conf->ISP_DATA.ReceivedLen)
	{
		if(ISP_Conf->ISP_DATA.ISP_RvBuffer[0]==0x79)
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}
	return FALSE;
}








 
void Usart_ISP_Send(ISP_Conf_TypeDef *ISP_Conf)						
{
	if(ISP_Conf->ISP_DATA.USARTSendLen)
	{
		memcpy(ISP_Conf->ISP_DATA.ISP_TxBuffer, ISP_Conf->ISP_DATA.ISP_TvBuffer,ISP_Conf->ISP_DATA.USARTSendLen);		
		memset(ISP_Conf->ISP_DATA.ISP_TvBuffer,0xFF, 300);	
		USART_DMASend(ISP_Conf->USARTx,(u8*)ISP_Conf->ISP_DATA.ISP_TxBuffer,ISP_Conf->ISP_DATA.USARTSendLen);			
		ISP_Conf->ISP_DATA.USARTSendLen=0;
	}
}






 
void Usart_ISP_Reset(ISP_Conf_TypeDef *ISP_Conf)	
{	
	
	ISP_Conf->ISP_DATA.OffsetAddr				=	0;			
	ISP_Conf->ISP_DATA.StartAddr				=	0;			
	ISP_Conf->ISP_DATA.GoAddr						=	0;			
	
	ISP_Conf->ISP_DATA.ReceivedLen			=	0;			
	ISP_Conf->ISP_DATA.USARTSendLen			=	0;			
	
	ISP_Conf->ISP_DATA.FLASHNumToSave		=	0;			
	ISP_Conf->ISP_DATA.FLASHNumToRead		=	0;			
	
	ISP_Conf->ISP_DATA.ReadAddr					=	0;			
	
	ISP_Conf->ISP_DATA.WriteAddr				=	0;			
	ISP_Conf->ISP_DATA.WriteLen					=	0;			

	ISP_Conf->ISP_DATA.SumHaveReceived	=	0;			
	ISP_Conf->ISP_DATA.SumHaveWritten		=	0;			

	
	
	ISP_Conf->ISP_FUN										=	ISP_IDLE;						
	ISP_Conf->ISP_SLAVE_STATUS					=	ISP_STATUS_IDLE;		
	ISP_Conf->SlaveLastStatus						=	ISP_STATUS_IDLE;		
	
	
	ISP_Conf->ISP_MDATA.OffsetAddr			=0;
	ISP_Conf->ISP_MDATA.StartAddr				=0;
	ISP_Conf->ISP_MDATA.GoAddr					=0;
	
	ISP_Conf->ISP_MDATA.ReceivedLen			=0;
	ISP_Conf->ISP_MDATA.USARTSendLen		=0;
	
	ISP_Conf->ISP_MDATA.FLASHNumToSave	=0;
	ISP_Conf->ISP_MDATA.FLASHNumToRead	=0;
	
	ISP_Conf->ISP_MDATA.ReadAddr				=0;
	
	ISP_Conf->ISP_MDATA.WriteAddr				=0;
	ISP_Conf->ISP_MDATA.WriteLen				=0;
	
	ISP_Conf->ISP_MDATA.SumHaveReceived	=0;
	ISP_Conf->ISP_MDATA.SumHaveWritten	=0;
	
	ISP_Conf->ISP_MASTER_STATUS					=	ISP_MSTATUS_IDLE;		
	ISP_Conf->MasterLastStatus					=	ISP_MSTATUS_IDLE;		
	
	
	
	ISP_Conf->OverRunTime								=	0;									
	ISP_Conf->TimeCount									=	0;									
	ISP_Conf->Connected=ISP_STATUS_UnConnect;							
	
	memset(ISP_Conf->ISP_DATA.ISP_RxBuffer,0xFF, 300);	
	memset(ISP_Conf->ISP_DATA.ISP_RvBuffer,0xFF, 300);	
	memset(ISP_Conf->ISP_DATA.ISP_TxBuffer,0xFF, 300);	
	memset(ISP_Conf->ISP_DATA.ISP_TvBuffer,0xFF, 300);	
}







 
void BSP_Configuration(BSP_Conf_TypeDef *BSP_Conf)		
{
	USART_DMA_ConfigurationEV	(BSP_Conf->BSP_Port.USARTx,115200,300);	
	GPIO_Configuration_OPP50	(BSP_Conf->BSP_Port.RESET_CTL_PORT,BSP_Conf->BSP_Port.RESET_CTL_Pin);			
	GPIO_Configuration_OPP50	(BSP_Conf->BSP_Port.BOOT0_CTL_PORT,BSP_Conf->BSP_Port.BOOT0_CTL_Pin);			
	BSP_Reset(BSP_Conf);																																								


}





 
void BSP_Process(BSP_Conf_TypeDef *BSP_Conf)			
{
	USM_BSP_PROCESS(BSP_Conf);					
	USS_BSP_PROCESS(BSP_Conf);					
	
}
void BSP_SendBuffer(BSP_Conf_TypeDef *BSP_Conf)						
{
	if(BSP_Conf->BSP_DATA.USARTSendLen!=0)
	{
		memcpy(BSP_Conf->BSP_DATA.BSP_TxBuffer,BSP_Conf->BSP_DATA.BSP_TvBuffer,BSP_Conf->BSP_DATA.USARTSendLen);					
		USART_DMASend(BSP_Conf->BSP_Port.USARTx,(u8*)BSP_Conf->BSP_DATA.BSP_TxBuffer,BSP_Conf->BSP_DATA.USARTSendLen);		
		memset(BSP_Conf->BSP_DATA.BSP_TvBuffer,0xFF, BSP_Conf->BSP_DATA.USARTSendLen);																		
		BSP_Conf->BSP_DATA.USARTSendLen=0;			
	}
}





 
void BSP_Reset(BSP_Conf_TypeDef *BSP_Conf)	
{	
	
	BSP_Conf->BSPM_Info.BSP_MASTER_STATUS	=	BSP_MSTATUS_IDLE;		
	BSP_Conf->BSPM_Info.MasterLastStatus	=	BSP_MSTATUS_IDLE;		
	BSP_Conf->BSPM_Info.ACK								=	BSP_NACK;						
	BSP_Conf->BSPM_Info.ACK2							=	BSP_NACK;						
	
	BSP_Conf->BSPS_Info.BSP_SLAVE_STATUS	=	BSP_STATUS_IDLE;		
	BSP_Conf->BSPS_Info.SlaveLastStatus		=	BSP_STATUS_IDLE;		
	
	BSP_Conf->BSP_DATA.OverRunTime=0;			
	BSP_Conf->BSP_DATA.TimeCount=0;				
	BSP_Conf->BSP_DATA.Connected=0;				
	BSP_Conf->BSP_DATA.OffsetAddr=0;			
	BSP_Conf->BSP_DATA.StartAddr=0;				
	BSP_Conf->BSP_DATA.StepLen	=256;			
	BSP_Conf->BSP_DATA.GoAddr=0;					
	BSP_Conf->BSP_DATA.FirmwareLen=0;			
	BSP_Conf->BSP_DATA.FLASHNumToSave=0;	
	BSP_Conf->BSP_DATA.FLASHNumToRead=0;	
	BSP_Conf->BSP_DATA.ReadAddr=0;				
	BSP_Conf->BSP_DATA.ReadLen=0;					
	BSP_Conf->BSP_DATA.WriteAddr=0;				
	BSP_Conf->BSP_DATA.WriteLen=0;				
	BSP_Conf->BSP_DATA.ReceivedLen=0;			
	BSP_Conf->BSP_DATA.USARTSendLen=0;		
	BSP_Conf->BSP_DATA.SumHaveReceived=0;	
	BSP_Conf->BSP_DATA.SumHaveWritten=0;	
	BSP_Conf->BSP_DATA.Command[0]=0;			
	BSP_Conf->BSP_DATA.Command[1]=0;
	

	memset(BSP_Conf->BSP_DATA.BSP_RxBuffer,0xFF, 300);	
	memset(BSP_Conf->BSP_DATA.BSP_RvBuffer,0xFF, 300);	
	memset(BSP_Conf->BSP_DATA.BSP_TxBuffer,0xFF, 300);	
	memset(BSP_Conf->BSP_DATA.BSP_TvBuffer,0xFF, 300);	
	
}













 
void USM_BSP_PROCESS(BSP_Conf_TypeDef *BSP_Conf)
{
	if(BSP_Conf->BSPM_Info.BSP_MASTER_STATUS==BSP_MSTATUS_IDLE)
	{
		BSP_Conf->BSPM_Info.BSP_MASTER_STATUS=BSP_MSTATUS_ResetDevice;
	}

	USM_BSP_GetAck(BSP_Conf);					
	
	USM_BSP_RESET(BSP_Conf);					
	USM_BSP_Connect(BSP_Conf);				

	USM_BSP_Get(BSP_Conf);						
	USM_BSP_GetVR(BSP_Conf);					
	USM_BSP_GetId(BSP_Conf);					
	USM_BSP_EraseMemory(BSP_Conf);		
	USM_BSP_EEraseMemory(BSP_Conf);		
	USM_BSP_WriteMemory(BSP_Conf);		
	USM_BSP_WriteAddr(BSP_Conf);			

	
	BSP_SendBuffer(BSP_Conf);					
}







 
void USM_BSP_RESET(BSP_Conf_TypeDef *BSP_Conf)		
{
	USM_BSP_ResetToBSP(BSP_Conf);			

	USM_BSP_ResetToRUN(BSP_Conf);			
}





 
void USM_BSP_ResetToBSP(BSP_Conf_TypeDef *BSP_Conf)			
{
	if(USM_BSP_GetStatus(BSP_Conf)==BSP_MSTATUS_ResetDevice)		
	{
		BSP_Conf->BSP_DATA.TimeCount++;
	}
	else
	{
		return;
	}
	if(BSP_Conf->BSP_DATA.TimeCount<=100)	
	{	
		GPIO_SetBits	(BSP_Conf->BSP_Port.BOOT0_CTL_PORT,BSP_Conf->BSP_Port.BOOT0_CTL_Pin);		
		GPIO_SetBits	(BSP_Conf->BSP_Port.RESET_CTL_PORT,BSP_Conf->BSP_Port.RESET_CTL_Pin);		
	}
	else if(BSP_Conf->BSP_DATA.TimeCount>100&&BSP_Conf->BSP_DATA.TimeCount<=10000)	
	{
		GPIO_SetBits	(BSP_Conf->BSP_Port.BOOT0_CTL_PORT,BSP_Conf->BSP_Port.BOOT0_CTL_Pin);		
		GPIO_ResetBits	(BSP_Conf->BSP_Port.RESET_CTL_PORT,BSP_Conf->BSP_Port.RESET_CTL_Pin);		
	}
	else
	{
		GPIO_SetBits	(BSP_Conf->BSP_Port.RESET_CTL_PORT,BSP_Conf->BSP_Port.RESET_CTL_Pin);		
		USM_BSP_SetStatus(BSP_Conf,BSP_MSTATUS_WriteConnect);		
		BSP_Conf->BSP_DATA.TimeCount=0;		
	}
}





 
void USM_BSP_ResetToRUN(BSP_Conf_TypeDef *BSP_Conf)			
{
	if(USM_BSP_GetStatus(BSP_Conf)==BSP_MSTATUS_StartDevice)
	{
		BSP_Conf->BSP_DATA.TimeCount++;
	}
	else
	{
		return;
	}
	if(BSP_Conf->BSP_DATA.TimeCount<=5000)	
	{
		GPIO_ResetBits(BSP_Conf->BSP_Port.BOOT0_CTL_PORT,BSP_Conf->BSP_Port.BOOT0_CTL_Pin);		
		GPIO_ResetBits(BSP_Conf->BSP_Port.RESET_CTL_PORT,BSP_Conf->BSP_Port.RESET_CTL_Pin);		
	}
	else if(BSP_Conf->BSP_DATA.TimeCount>5000&&BSP_Conf->BSP_DATA.TimeCount<10000)	
	{
		GPIO_SetBits	(BSP_Conf->BSP_Port.RESET_CTL_PORT,BSP_Conf->BSP_Port.RESET_CTL_Pin);		
	}
	else
	{
		USM_BSP_SetStatus(BSP_Conf,BSP_MSTATUS_WriteConnect);		
		BSP_Conf->BSP_DATA.TimeCount=0;		
	}
}





 
void USM_BSP_SetStatus(BSP_Conf_TypeDef *BSP_Conf,BSPM_STATUS_TypeDef BSPM_STATUS)		
{
	BSP_Conf->BSPM_Info.BSP_MASTER_STATUS	=	BSPM_STATUS;				
}





 
BSPM_STATUS_TypeDef USM_BSP_GetStatus(BSP_Conf_TypeDef *BSP_Conf)		
{
	return BSP_Conf->BSPM_Info.BSP_MASTER_STATUS;				
}





 
void USM_BSP_Connect(BSP_Conf_TypeDef *BSP_Conf)		
{
	if(USM_BSP_GetStatus(BSP_Conf)==BSP_MSTATUS_WriteConnect)
	{
		BSP_Conf->BSP_DATA.TimeCount++;
	}
	else
	{
		return;
	}
	
	if(BSP_Conf->BSP_DATA.TimeCount==100)				
	{
		BSP_Conf->BSP_DATA.BSP_TvBuffer[0]=0x7F;
		BSP_Conf->BSP_DATA.USARTSendLen=1;				
	}
	else if(BSP_Conf->BSP_DATA.TimeCount>1000)	
	{
		BSP_Conf->BSP_DATA.RetryTimes++;	
		if(BSP_Conf->BSP_DATA.RetryTimes>50)
		{
			USM_BSP_SetStatus(BSP_Conf,BSP_MSTATUS_ERROR);		
		}
		BSP_Conf->BSP_DATA.TimeCount=0;		
	}
	else
	{
		if(BSP_Conf->BSPM_Info.ACK==BSP_ACK)
		{
			USM_BSP_SetStatus(BSP_Conf,BSP_MSTATUS_WriteGet);		
			BSP_Conf->BSP_DATA.TimeCount=0;		
			BSP_Conf->BSP_DATA.RetryTimes=0;	
			BSP_Conf->BSPM_Info.ACK=BSP_NACK;	
		}		
	}
}





 
void USM_BSP_Get(BSP_Conf_TypeDef *BSP_Conf)		
{
	if(USM_BSP_GetStatus(BSP_Conf)==BSP_MSTATUS_WriteGet)
	{
		BSP_Conf->BSP_DATA.TimeCount++;
	}
	else
	{
		return;
	}
	if(BSP_Conf->BSP_DATA.TimeCount==100)				
	{
		USM_BSP_SendCommand(BSP_Conf,BSP_COMMAND_Get);	
	}
	else if(BSP_Conf->BSP_DATA.TimeCount>1000)	
	{
		BSP_Conf->BSP_DATA.RetryTimes++;	
		if(BSP_Conf->BSP_DATA.RetryTimes>50)
		{
			USM_BSP_SetStatus(BSP_Conf,BSP_MSTATUS_ERROR);		
		}
		BSP_Conf->BSP_DATA.TimeCount=0;		
	}
	else
	{
		if(BSP_Conf->BSPM_Info.ACK==BSP_ACK)
		{
			BSP_Conf->BSPM_Info.SlaveVersion.BSP_VS					=	BSP_Conf->BSP_DATA.BSP_RvBuffer[2];		
			BSP_Conf->BSPM_Info.SlaveVersion.BSP_VS_Get			=	BSP_Conf->BSP_DATA.BSP_RvBuffer[3];		
			BSP_Conf->BSPM_Info.SlaveVersion.BSP_VS_GetVS		=	BSP_Conf->BSP_DATA.BSP_RvBuffer[4];		
			BSP_Conf->BSPM_Info.SlaveVersion.BSP_VS_GetID		=	BSP_Conf->BSP_DATA.BSP_RvBuffer[5];		
			BSP_Conf->BSPM_Info.SlaveVersion.BSP_VS_RM			=	BSP_Conf->BSP_DATA.BSP_RvBuffer[6];		
			BSP_Conf->BSPM_Info.SlaveVersion.BSP_VS_Go			=	BSP_Conf->BSP_DATA.BSP_RvBuffer[7];		
			BSP_Conf->BSPM_Info.SlaveVersion.BSP_VS_WM			=	BSP_Conf->BSP_DATA.BSP_RvBuffer[8];		
			BSP_Conf->BSPM_Info.SlaveVersion.BSP_VS_Erase		=	BSP_Conf->BSP_DATA.BSP_RvBuffer[9];		
			BSP_Conf->BSPM_Info.SlaveVersion.BSP_VS_WP			=	BSP_Conf->BSP_DATA.BSP_RvBuffer[10];	
			BSP_Conf->BSPM_Info.SlaveVersion.BSP_VS_WU			=	BSP_Conf->BSP_DATA.BSP_RvBuffer[11];	
			BSP_Conf->BSPM_Info.SlaveVersion.BSP_VS_RP			=	BSP_Conf->BSP_DATA.BSP_RvBuffer[12];	
			BSP_Conf->BSPM_Info.SlaveVersion.BSP_VS_RU			=	BSP_Conf->BSP_DATA.BSP_RvBuffer[13];	
			
			USM_BSP_SetStatus(BSP_Conf,BSP_MSTATUS_WriteGetVR);		
			BSP_Conf->BSP_DATA.TimeCount=0;		
			BSP_Conf->BSP_DATA.RetryTimes=0;	
			BSP_Conf->BSPM_Info.ACK=BSP_NACK;	
		}		
	}
}





 
void USM_BSP_GetVR(BSP_Conf_TypeDef *BSP_Conf)		
{
	if(USM_BSP_GetStatus(BSP_Conf)==BSP_MSTATUS_WriteGetVR)
	{
		BSP_Conf->BSP_DATA.TimeCount++;
	}
	else
	{
		return;
	}
	if(BSP_Conf->BSP_DATA.TimeCount==100)				
	{
		USM_BSP_SendCommand(BSP_Conf,BSP_COMMAND_GetVR);	
	}
	else if(BSP_Conf->BSP_DATA.TimeCount>1000)	
	{
		BSP_Conf->BSP_DATA.RetryTimes++;	
		if(BSP_Conf->BSP_DATA.RetryTimes>50)
		{
			USM_BSP_SetStatus(BSP_Conf,BSP_MSTATUS_ERROR);		
		}	
		BSP_Conf->BSP_DATA.TimeCount=0;		
	}
	else
	{
		if(BSP_Conf->BSPM_Info.ACK==BSP_ACK)
		{
			
			USM_BSP_SetStatus(BSP_Conf,BSP_MSTATUS_WriteGetID);		
			BSP_Conf->BSP_DATA.TimeCount=0;		
			BSP_Conf->BSP_DATA.RetryTimes=0;	
			BSP_Conf->BSPM_Info.ACK=BSP_NACK;	
		}		
	}
}





 
void USM_BSP_GetId(BSP_Conf_TypeDef *BSP_Conf)			
{
	if(USM_BSP_GetStatus(BSP_Conf)==BSP_MSTATUS_WriteGetID)
	{
		BSP_Conf->BSP_DATA.TimeCount++;
	}
	else
	{
		return;
	}
	if(BSP_Conf->BSP_DATA.TimeCount==100)				
	{
		USM_BSP_SendCommand(BSP_Conf,BSP_COMMAND_GetID);	
	}
	else if(BSP_Conf->BSP_DATA.TimeCount>1000)	
	{
		BSP_Conf->BSP_DATA.RetryTimes++;	
		if(BSP_Conf->BSP_DATA.RetryTimes>50)
		{
			USM_BSP_SetStatus(BSP_Conf,BSP_MSTATUS_ERROR);		
		}	
		BSP_Conf->BSP_DATA.TimeCount=0;		
	}
	else
	{
		if(BSP_Conf->BSPM_Info.ACK==BSP_ACK)
		{
			
			USM_BSP_SetStatus(BSP_Conf,BSP_MSTATUS_WriteErase);		
			BSP_Conf->BSP_DATA.TimeCount=0;		
			BSP_Conf->BSP_DATA.RetryTimes=0;	
			BSP_Conf->BSPM_Info.ACK=BSP_NACK;	
		}		
	}
}





 
void USM_BSP_ReadMemory(BSP_Conf_TypeDef *BSP_Conf)		
{

}





 
void USM_BSP_Go(BSP_Conf_TypeDef *BSP_Conf)		
{

}







 
void USM_BSP_WriteMemory(BSP_Conf_TypeDef *BSP_Conf)		
{
	if(USM_BSP_GetStatus(BSP_Conf)==BSP_MSTATUS_WriteWM)	
	{
		BSP_Conf->BSP_DATA.TimeCount++;						
		if(BSP_Conf->BSP_DATA.TimeCount<=5000)		
		{
			if(BSP_Conf->BSP_DATA.StartAddr!=0)			
			{
				BSP_Conf->BSP_DATA.TimeCount=0;		
				BSP_Conf->BSP_DATA.WriteAddr=BSP_Conf->BSP_DATA.StartAddr;		
				BSP_Conf->BSP_DATA.SumHaveWritten=0;	
				USM_BSP_SetStatus(BSP_Conf,BSP_MSTATUS_WriteAddr);		
			}
			else
			{
				return;			
			}
		}
		else		
		{
			USM_BSP_SetStatus(BSP_Conf,BSP_MSTATUS_ERROR);		
			return;
		}
	}
	else
	{
		return;
	}
}








 
void USM_BSP_WriteAddr(BSP_Conf_TypeDef *BSP_Conf)		
{
	if(USM_BSP_GetStatus(BSP_Conf)==BSP_MSTATUS_WriteAddr&&BSP_Conf->BSP_DATA.USARTSendLen==0)	
	{
		BSP_Conf->BSP_DATA.TimeCount++;												
	}
	else		
	{
		return;
	}
	if(BSP_Conf->BSP_DATA.TimeCount==5)		
	{	
		BSP_Conf->BSP_DATA.BSP_TvBuffer[0]=BSP_Conf->BSP_DATA.WriteAddr>>24;
		BSP_Conf->BSP_DATA.BSP_TvBuffer[1]=BSP_Conf->BSP_DATA.WriteAddr>>16;
		BSP_Conf->BSP_DATA.BSP_TvBuffer[2]=BSP_Conf->BSP_DATA.WriteAddr>>8;
		BSP_Conf->BSP_DATA.BSP_TvBuffer[3]=BSP_Conf->BSP_DATA.WriteAddr>>0;
		BSP_Conf->BSP_DATA.BSP_TvBuffer[4]=BCC8(BSP_Conf->BSP_DATA.BSP_TvBuffer,4);		
		BSP_Conf->BSP_DATA.USARTSendLen=5;
	}
	else if(BSP_Conf->BSP_DATA.TimeCount>200)		
	{
		BSP_Conf->BSP_DATA.RetryTimes++;			
		if(BSP_Conf->BSP_DATA.RetryTimes>10)	
		{
			USM_BSP_SetStatus(BSP_Conf,BSP_MSTATUS_ERROR);		
		}	
		BSP_Conf->BSP_DATA.TimeCount=0;				
	}
	else if(BSP_Conf->BSP_DATA.TimeCount>5)		
	{
		if(BSP_Conf->BSPM_Info.ACK==BSP_ACK)		
		{	
			USM_BSP_SetStatus(BSP_Conf,BSP_MSTATUS_WriteData);		
			BSP_Conf->BSP_DATA.TimeCount=0;			
			BSP_Conf->BSP_DATA.RetryTimes=0;		
			BSP_Conf->BSPM_Info.ACK=BSP_NACK;		
			BSP_Conf->BSP_DATA.WriteAddr+=BSP_Conf->BSP_DATA.StepLen;		
			return;		
		}
		else		
		{
			return;
		}
	}
	else		
	{
		return;
	}
}





 
void USM_BSP_WriteData(BSP_Conf_TypeDef *BSP_Conf)		
{
	if(
		USM_BSP_GetStatus(BSP_Conf)==BSP_MSTATUS_WriteData&&	
		BSP_Conf->BSP_DATA.USARTSendLen==0&&		
		BSP_Conf->BSP_DATA.WriteLen							
	)	
	{
		BSP_Conf->BSP_DATA.TimeCount++;												
	}
	else if(BSP_Conf->BSP_DATA.TimeCount>5000)			
	{
		USM_BSP_SetStatus(BSP_Conf,BSP_MSTATUS_ERROR);		
	}
	else	
	{
		return;
	}
	if(BSP_Conf->BSP_DATA.TimeCount==1)
	{
		BSP_Conf->BSP_DATA.USARTSendLen=BSP_Conf->BSP_DATA.WriteLen;				
		BSP_Conf->BSP_DATA.SumHaveWritten+=BSP_Conf->BSP_DATA.USARTSendLen;	
		memcpy(BSP_Conf->BSP_DATA.BSP_TxBuffer, BSP_Conf->BSP_DATA.BSP_FlashBuffer,BSP_Conf->BSP_DATA.USARTSendLen);	
	}
	else	
	{
		if(BSP_Conf->BSPM_Info.ACK==BSP_ACK)	
		{
			if(BSP_Conf->BSP_DATA.SumHaveWritten<BSP_Conf->BSP_DATA.FirmwareLen)	
			{
				USM_BSP_SetStatus(BSP_Conf,BSP_MSTATUS_WriteAddr);		
				BSP_Conf->BSP_DATA.TimeCount=0;			
				BSP_Conf->BSPM_Info.ACK=BSP_NACK;		
				BSP_Conf->BSP_DATA.WriteLen=0;			
			}
			else	
			{
				USM_BSP_SetStatus(BSP_Conf,BSP_MSTATUS_WriteGo);		
				BSP_Conf->BSP_DATA.TimeCount=0;			
				BSP_Conf->BSPM_Info.ACK=BSP_NACK;		
				BSP_Conf->BSP_DATA.WriteLen=0;			
			}			
		}
		else
		{
			return;
		}
	}
}





 
void USM_BSP_EraseMemory(BSP_Conf_TypeDef *BSP_Conf)		
{
	if(USM_BSP_GetStatus(BSP_Conf)==BSP_MSTATUS_WriteErase)
	{
		BSP_Conf->BSP_DATA.TimeCount++;
	}
	else
	{
		return;
	}
	if(BSP_Conf->BSP_DATA.TimeCount==100)				
	{
		if(BSP_Conf->BSPM_Info.ACK2!=BSP_ACK)
		{
			USM_BSP_SendCommand(BSP_Conf,BSP_COMMAND_Erase);	
		}
		else
		{
			BSP_Conf->BSP_DATA.BSP_TvBuffer[0]=0xFF;
			BSP_Conf->BSP_DATA.BSP_TvBuffer[1]=0x00;
			BSP_Conf->BSP_DATA.USARTSendLen=2;				
		}
	}
	else if(BSP_Conf->BSP_DATA.TimeCount>1000)	
	{
		BSP_Conf->BSP_DATA.RetryTimes++;			
		if(BSP_Conf->BSP_DATA.RetryTimes>50)	
		{
			USM_BSP_SetStatus(BSP_Conf,BSP_MSTATUS_ERROR);		
		}	
		BSP_Conf->BSP_DATA.TimeCount=0;				
	}
	else	
	{
		if(BSP_Conf->BSPM_Info.ACK==BSP_ACK)		
		{	
			if(BSP_Conf->BSPM_Info.ACK2!=BSP_ACK)	
			{
				BSP_Conf->BSP_DATA.TimeCount=0;		
				BSP_Conf->BSP_DATA.RetryTimes=0;	
				BSP_Conf->BSPM_Info.ACK=BSP_NACK;	
				BSP_Conf->BSPM_Info.ACK2=BSP_ACK;	
			}
			else		
			{
				USM_BSP_SetStatus(BSP_Conf,BSP_MSTATUS_WriteWM);		
				BSP_Conf->BSP_DATA.TimeCount=0;			
				BSP_Conf->BSP_DATA.RetryTimes=0;		
				BSP_Conf->BSPM_Info.ACK=BSP_NACK;		
				BSP_Conf->BSPM_Info.ACK2=BSP_NACK;	
			}			
		}		
	}
}





 
void USM_BSP_EEraseMemory(BSP_Conf_TypeDef *BSP_Conf)		
{

}





 
void USM_BSP_WriteProtect(BSP_Conf_TypeDef *BSP_Conf)		
{

}





 
void USM_BSP_WriteUnProtect(BSP_Conf_TypeDef *BSP_Conf)		
{

}





 
void USM_BSP_ReadProtect(BSP_Conf_TypeDef *BSP_Conf)		
{

}





 
void USM_BSP_ReadUnProtect(BSP_Conf_TypeDef *BSP_Conf)		
{

}





 
void USM_BSP_GetAck(BSP_Conf_TypeDef *BSP_Conf)		
{
	unsigned char RxNum=0;
	RxNum=USART_ReadBufferIDLE(BSP_Conf->BSP_Port.USARTx,(u8*)BSP_Conf->BSP_DATA.BSP_RvBuffer);	
	if((RxNum!=0)&&(BSP_Conf->BSP_DATA.BSP_RvBuffer[0]==BSP_ACK))
	{
		BSP_Conf->BSP_DATA.BSP_RvBuffer[0]=0xFF;		
		BSP_Conf->BSPM_Info.ACK=BSP_ACK;		
	}
}





 
void USM_BSP_SendCommand(BSP_Conf_TypeDef *BSP_Conf,BSP_COMMAND_TypeDef Command)	
{
	BSP_Conf->BSP_DATA.Command[0]=Command;
	BSP_Conf->BSP_DATA.Command[1]=Command^0XFF;
	USART_DMASend(BSP_Conf->BSP_Port.USARTx,(u8*)BSP_Conf->BSP_DATA.Command,2);	
}





 
void USM_BSP_SendBuffer(BSP_Conf_TypeDef *BSP_Conf)						
{
	if(BSP_Conf->BSP_DATA.USARTSendLen)
	{
		memcpy(BSP_Conf->BSP_DATA.BSP_TxBuffer, BSP_Conf->BSP_DATA.BSP_TvBuffer,BSP_Conf->BSP_DATA.USARTSendLen);				
		memset(BSP_Conf->BSP_DATA.BSP_TvBuffer,0xFF, 300);				
		USART_DMASend(BSP_Conf->BSP_Port.USARTx,(u8*)BSP_Conf->BSP_DATA.BSP_TxBuffer,BSP_Conf->BSP_DATA.USARTSendLen);	
		BSP_Conf->BSP_DATA.USARTSendLen=0;
	}
}






















 
void USS_BSP_PROCESS(BSP_Conf_TypeDef *BSP_Conf)
{

}





 
void USS_BSP_RESET(BSP_Conf_TypeDef *BSP_Conf)
{

}





 
void USS_BSP_Get(BSP_Conf_TypeDef *BSP_Conf)		
{

}





 
void USS_BSP_GetVR(BSP_Conf_TypeDef *BSP_Conf)		
{

}





 
void USS_BSP_GetId(BSP_Conf_TypeDef *BSP_Conf)			
{

}





 
void USS_BSP_ReadMemory(BSP_Conf_TypeDef *BSP_Conf)		
{

}





 
void USS_BSP_Go(BSP_Conf_TypeDef *BSP_Conf)		
{

}





 
void USS_BSP_WriteMemory(BSP_Conf_TypeDef *BSP_Conf)		
{

}





 
void USS_BSP_EraseMemory(BSP_Conf_TypeDef *BSP_Conf)		
{

}





 
void USS_BSP_EEraseMemory(BSP_Conf_TypeDef *BSP_Conf)		
{

}





 
void USS_BSP_WriteProtect(BSP_Conf_TypeDef *BSP_Conf)		
{

}





 
void USS_BSP_WriteUnProtect(BSP_Conf_TypeDef *BSP_Conf)		
{

}





 
void USS_BSP_ReadProtect(BSP_Conf_TypeDef *BSP_Conf)		
{

}





 
void USS_BSP_ReadUnProtect(BSP_Conf_TypeDef *BSP_Conf)		
{

}





 
void USS_BSP_ACK(BSP_Conf_TypeDef *BSP_Conf)		
{

}





 
void USS_BSP_NACK(BSP_Conf_TypeDef *BSP_Conf)		
{

}
























