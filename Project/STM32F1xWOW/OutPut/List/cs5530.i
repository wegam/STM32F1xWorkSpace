#line 1 "..\\..\\Driver\\Components\\SCR\\CS5530.c"
#line 1 "..\\..\\Driver\\Components\\INC\\CS5530.H"




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



 
#line 6 "..\\..\\Driver\\Components\\INC\\CS5530.H"


#line 14 "..\\..\\Driver\\Components\\INC\\CS5530.H"





 



  
#line 31 "..\\..\\Driver\\Components\\INC\\CS5530.H"


#line 39 "..\\..\\Driver\\Components\\INC\\CS5530.H"
																											
#line 70 "..\\..\\Driver\\Components\\INC\\CS5530.H"
	



 





typedef struct	_CS5530Port
{
	
	
	
	
	GPIO_TypeDef* 	CS_PORT;				
	unsigned short 	CS_Pin;				
	
	
	
	GPIO_TypeDef* 	SDI_PORT;			
	unsigned short 	SDI_Pin;				
	
	
	
	GPIO_TypeDef* 	SDO_PORT;			
	unsigned short 	SDO_Pin;				
	
	
	
	
	GPIO_TypeDef* 	SCLK_PORT;			
	unsigned short 	SCLK_Pin;			

}CS5530PortDef;
typedef struct	_CS5530Data
{
	unsigned short	Retry;						
	unsigned short 	Quantity;					
	unsigned short	Num;							
	unsigned long		Origin;						
	unsigned long 	WeighLive;				
	unsigned long 	WeighFilt;				
	unsigned long 	WeighPie;					
	unsigned long		Buffer[20];	
	unsigned long		Time;							
}CS5530DataDef;
typedef struct	_CS5530Flag		
{
	unsigned short IDLE:1;			
	unsigned short StLv:1;			
	unsigned short GetOri:1;		
	unsigned short GetCali:1;		
	unsigned short GetQua:1;		
}CS5530FlagDef;
typedef struct	_CS5530
{
	CS5530PortDef Port;
	CS5530DataDef	Data;
	CS5530FlagDef	Flag;
}CS5530Def;


void CS5530_Initialize(CS5530Def *pInfo);
u32	CS5530_ReadData(CS5530Def *pInfo);		
void CS5530_Process(CS5530Def *pInfo);


void CS5530_Delay(u32 time);


void CS5530_WriteOneByte(u8 dat);
unsigned char CS5530_ReadOneByte(void);

void CS5530_WriteRegister(u8 command,u32 setData);
void CS5530_WriteCommand(u8 command);


u32 CS5530_GetADData(CS5530Def *pInfo);
u32 CS5530_ReadRegister(u8 command);



void CS5530_PowerUp(CS5530Def *pInfo);		
void CS5530_PowerDown(CS5530Def *pInfo);



unsigned long CS5530_GetWeightUseMedinaFilter(CS5530Def *pInfo);
unsigned long CS5530_GetWeigh(CS5530Def *pInfo);		
unsigned long CS5530_GetCalib(CS5530Def *pInfo);		
unsigned long CS5530_GetOrigin(CS5530Def *pInfo);		
unsigned long CS5530_GetQuant(CS5530Def *pInfo);		

void CS5530_Clear(CS5530Def *pInfo);		



#line 2 "..\\..\\Driver\\Components\\SCR\\CS5530.c"

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










#line 4 "..\\..\\Driver\\Components\\SCR\\CS5530.c"
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
	



#line 5 "..\\..\\Driver\\Components\\SCR\\CS5530.c"

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




#line 7 "..\\..\\Driver\\Components\\SCR\\CS5530.c"

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






 
#line 9 "..\\..\\Driver\\Components\\SCR\\CS5530.c"
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





 
#line 10 "..\\..\\Driver\\Components\\SCR\\CS5530.c"

CS5530PortDef*  CS5530Info  = 0;

#line 20 "..\\..\\Driver\\Components\\SCR\\CS5530.c"








unsigned long CS5530_Status=0x00;












 
void CS5530_Delayus(u32 time)
{
	SysTick_DeleyuS(time);				
}






 
void CS5530_Initialize(CS5530Def *pInfo)
{
	unsigned long *p=(unsigned long*)&(pInfo->Flag);		
	CS5530Info  = &pInfo->Port;
	
	GPIO_Configuration_OPP50	(pInfo->Port.CS_PORT,		pInfo->Port.CS_Pin);			
	GPIO_Configuration_OPP50	(pInfo->Port.SDI_PORT,	pInfo->Port.SDI_Pin);			
	GPIO_Configuration_OPP50	(pInfo->Port.SCLK_PORT,	pInfo->Port.SCLK_Pin);		
	GPIO_Configuration_IPU		(pInfo->Port.SDO_PORT,	pInfo->Port.SDO_Pin);			
	
	((CS5530Info->CS_PORT)->BSRR = CS5530Info->CS_Pin);         
	((CS5530Info->SCLK_PORT)->BRR = CS5530Info->SCLK_Pin);
	CS5530_PowerUp(pInfo);		
}





 
void CS5530_WriteOneByte(u8 dat)
{
	u8 i;
	u16 delayTime	=	1000;
  

  ((CS5530Info->CS_PORT)->BRR = CS5530Info->CS_Pin);         
	CS5530_Delayus(20);				
	for(i=0; i<8; i++)
	{
		if((dat&0x80) != 0)
      ((CS5530Info->SDI_PORT)->BSRR = CS5530Info->SDI_Pin);    
		else
      ((CS5530Info->SDI_PORT)->BRR = CS5530Info->SDI_Pin);    
		
		CS5530_Delayus(10);	  
    ((CS5530Info->SCLK_PORT)->BSRR = CS5530Info->SCLK_Pin);     
		CS5530_Delayus(10);    
    ((CS5530Info->SCLK_PORT)->BRR = CS5530Info->SCLK_Pin);     
    CS5530_Delayus(5);    
		dat <<= 1;
	}
}





 
unsigned char CS5530_ReadOneByte(void)
{
	uint8_t i;
	uint8_t reValue=0;
  ((CS5530Info->SDI_PORT)->BRR = CS5530Info->SDI_Pin);        
	CS5530_Delayus(20);		  
	for(i=0; i<8; i++)
	{	
    ((CS5530Info->SCLK_PORT)->BSRR = CS5530Info->SCLK_Pin);     
    CS5530_Delayus(5);	  
		reValue <<= 1;
		if(((CS5530Info->SDO_PORT)->IDR & CS5530Info->SDO_Pin))
			reValue++;
		CS5530_Delayus(5);	  
    ((CS5530Info->SCLK_PORT)->BRR = CS5530Info->SCLK_Pin);     
    CS5530_Delayus(5);	  
	}
	CS5530_Delayus(5);	  

	return reValue;
}





 
void CS5530_WriteCommand(u8 command)
{
	CS5530_WriteOneByte(command);
}





 
void CS5530_WriteRegister(u8 command,u32 setData)
{

	CS5530_WriteOneByte(command);
	CS5530_WriteOneByte((uint8_t)(setData>>24));
	CS5530_WriteOneByte((uint8_t)(setData>>16));
	CS5530_WriteOneByte((uint8_t)(setData>>8));
	CS5530_WriteOneByte((uint8_t)(setData>>0));
}







 
u32 CS5530_GetADData(CS5530Def *pInfo)
{
	u32 reValue=0;	
  CS5530Info  = &pInfo->Port;
  ((CS5530Info->SDI_PORT)->BRR = CS5530Info->SDI_Pin);    
  CS5530_ReadOneByte();
  reValue = ((u32)CS5530_ReadOneByte()<<24)
          +((uint32_t)CS5530_ReadOneByte()<<16)
          +((uint32_t)CS5530_ReadOneByte()<<8)
          +(uint32_t)CS5530_ReadOneByte();
	return reValue;
}





 
u32 CS5530_ReadRegister(u8 command)
{
	volatile unsigned long temp=0x00;

	CS5530_WriteOneByte(command);
	temp = (CS5530_ReadOneByte()<<24)
				+(CS5530_ReadOneByte()<<16)
				+(CS5530_ReadOneByte()<<8)
				+CS5530_ReadOneByte();
	
	return temp;
}





 
void CS5530_PowerUp(CS5530Def *pInfo)
{
	u8 num=0;
	u16 retry	=	0;	
  CS5530Info  = &pInfo->Port;
	SysTick_DeleymS(20);				
	((CS5530Info->SCLK_PORT)->BRR = CS5530Info->SCLK_Pin);
  ((CS5530Info->CS_PORT)->BRR = CS5530Info->CS_Pin);         
	SysTick_DeleymS(20);				
	
	
	for(num=0;num<20;num++)
	{
		CS5530_WriteOneByte((unsigned char)0xFF);
	}
	
	CS5530_WriteOneByte((unsigned char)0xFE);
	SysTick_DeleymS(1);				
	
	
	
	CS5530_WriteRegister((unsigned char)0x03,(0x01UL<<29));
	SysTick_DeleymS(1);				
	
	CS5530_WriteOneByte((unsigned char)0x00);
	SysTick_DeleymS(1);				
	
	CS5530_WriteRegister((unsigned char)0x03,(0x00UL<<29));
	SysTick_DeleymS(1);				
	


	
	
	do
	{ 
		CS5530_Status = CS5530_ReadRegister((unsigned char)0x0B);
		SysTick_DeleymS(10);				
	}
	while(((CS5530_Status & (0x01UL<<28)) != 0)&&(retry++<=20));
	
	if(retry>=19)		
	{
		((CS5530Info->CS_PORT)->BSRR = CS5530Info->CS_Pin);         
		return;
	}
	
	CS5530_Status = CS5530_ReadRegister((unsigned char)0x0B);			
	CS5530_Status = CS5530_ReadRegister((unsigned char)0x09);			
	CS5530_Status = CS5530_ReadRegister((unsigned char)0x0A);				
  
  
  
  WriteCS5530Gain:
  SysTick_DeleymS(10);				
  CS5530_Status = CS5530_ReadRegister((unsigned char)0x0A);				
	










	CS5530_Status=0x01000000;		
	
  CS5530_WriteRegister((unsigned char)0x02,CS5530_Status);			
  
  CS5530_Status = CS5530_ReadRegister((unsigned char)0x0A);				
  if(CS5530_Status != CS5530_ReadRegister((unsigned char)0x0A))
  {
    goto WriteCS5530Gain;
  }
  
  
  
  WriteCS5530Offset:
  SysTick_DeleymS(10);				
	CS5530_Status=CS5530_ReadRegister((unsigned char)0x09);			
  
  CS5530_Status|=0x000000;
  
  CS5530_WriteRegister((unsigned char)0x01,CS5530_Status);		
  
  if(CS5530_Status  !=  CS5530_ReadRegister((unsigned char)0x09))
  {
    goto WriteCS5530Offset;
  }
  
  
  
  WriteCS5530Config:
  SysTick_DeleymS(10);				
  CS5530_Status=CS5530_ReadRegister((unsigned char)0x0B);			
  
  CS5530_Status=CS5530_Status|0x82000;    





  
	CS5530_Status	&=	~(0x01UL<<10);		            
  
  


  
  CS5530_WriteRegister((unsigned char)0x03,CS5530_Status);		
  
  if(CS5530_Status  !=  CS5530_ReadRegister((unsigned char)0x0B))
  {
    goto WriteCS5530Config;
  }
	
  SysTick_DeleymS(50);				
  
	CS5530_WriteCommand((unsigned char)0x85);							
	
	CS5530_WriteCommand((unsigned char)0x86);								


	SysTick_DeleymS(50);				
	CS5530_WriteCommand((unsigned char)0xC0);									
	

	
	CS5530_Delayus(500);
	((CS5530Info->CS_PORT)->BSRR = CS5530Info->CS_Pin);         
}





 
void CS5530_PowerDown(CS5530Def *pInfo)
{
	u8 num=0;
	u16 retry	=	0;	
  CS5530Info  = &pInfo->Port;
	((CS5530Info->CS_PORT)->BRR = CS5530Info->CS_Pin);         
	SysTick_DeleymS(200);				
	
	
	for(num=0;num<15;num++)
	{
		CS5530_WriteOneByte((unsigned char)0xFF);
		SysTick_DeleymS(5);				
	}
	SysTick_DeleymS(50);				
	
	CS5530_WriteOneByte((unsigned char)0xFE);
	SysTick_DeleymS(50);				
	
	
	CS5530_WriteRegister((unsigned char)0x03,(0x01UL<<29));
	SysTick_DeleymS(50);				
	CS5530_WriteOneByte((unsigned char)0x00);
	SysTick_DeleymS(50);				
	CS5530_WriteRegister((unsigned char)0x03,(0x00UL<<29));
	SysTick_DeleymS(50);				
	
	
	do
	{ 
		CS5530_Status = CS5530_ReadRegister( (unsigned char)0x0B);
		SysTick_DeleymS(50);				
	}
	while(((CS5530_Status & (0x01UL<<28)) != 0)&&(retry++<=100));
	
	if(retry>=100)
	{
		return;
	}
	
	CS5530_WriteRegister((unsigned char)0x03,(0x01UL<<30));
	
	CS5530_Delayus(500);
	((CS5530Info->CS_PORT)->BSRR = CS5530Info->CS_Pin);         
}






 
u32	CS5530_ReadData(CS5530Def *pInfo)
{
	u32 ADC_Value=0xFFFFFFFF;
	CS5530Info  = &pInfo->Port;
	((CS5530Info->CS_PORT)->BRR = CS5530Info->CS_Pin);         
	SysTick_DeleyuS(100);				
	if(((CS5530Info->SDO_PORT)->IDR & CS5530Info->SDO_Pin) == 0)
	{			
		ADC_Value=CS5530_GetADData(pInfo)>>8;		
	}
	((CS5530Info->CS_PORT)->BSRR = CS5530Info->CS_Pin);         
	return ADC_Value;
}











 
unsigned long CS5530_GetWeightUseMedinaFilter(CS5530Def *pInfo)
{
	static unsigned long 	weighAve=0;		
	static unsigned long 	weighVar=0;		
	static unsigned short 	Length	=	0;
	unsigned long		*Buffer		=	0;			

	Buffer	=	&(pInfo->Data.Buffer[0]);
	Length	=	pInfo->Data.Num;
	
	


	
	weighAve	=	GetAveLong(Buffer,Length);		
	
	weighVar	=	GetVarLong(Buffer,Length);		
	weighVar	=	weighVar/Length;
	








	return weighAve;
}








 
unsigned long CS5530_GetWeigh(CS5530Def *pInfo)
{
	static unsigned char ReadErrorNum=0;
	if(pInfo->Data.Time++>=5)	
	{
		unsigned long		ADC	=	0;
		unsigned short	Num			=	0;					
		unsigned short	*Quantity	=	0;			
		unsigned long		*WeighFilt	=	0;		
		unsigned long		*Origin		=	0;			
		unsigned long		*Buffer		=	0;			
		
		Num	=	pInfo->Data.Num;
		WeighFilt	=	&(pInfo->Data.WeighFilt);
		Quantity	=	&(pInfo->Data.Quantity);		
		Origin	=	&(pInfo->Data.Origin);
		Buffer	=	&(pInfo->Data.Buffer[0]);
		
		pInfo->Data.Time	=	0;
		
		ADC	=	CS5530_ReadData(pInfo);	
		
		pInfo->Data.WeighLive	=	ADC;
		
		if(ADC	!=	0xFFFFFFFF)
		{
			unsigned long	ADC_CMP	=	0;	
			ReadErrorNum=0;		
			
			
			if(0==Num)	
			{
				Buffer[Num]	=	ADC;
				pInfo->Data.Num++;	
				return 0;						
			}
			
			else
			{
				if(Buffer[Num-1]>ADC)	
				{
					ADC_CMP	=	Buffer[Num-1]-ADC;
				}
				else
				{
					ADC_CMP	=	ADC-Buffer[Num-1];
				}
				
				if(ADC_CMP>1000)			
				{
					*WeighFilt	=	0xFFFFFFFF;	
					pInfo->Data.Num	=	0;			
					return 0;									
				}
				else
				{
					Buffer[Num]	=	ADC;
					pInfo->Data.Num++;				
				}
			}
			
			if(pInfo->Data.Num>=20)		
			{
				*WeighFilt	=	CS5530_GetWeightUseMedinaFilter(pInfo);
				pInfo->Data.Num	=	0;
				return *WeighFilt;
			}
		}
		
		else
		{
			if(ReadErrorNum++>50)
			{
				pInfo->Data.Num	=	0;
				*WeighFilt=0xFFFFFFFF;
				
				ReadErrorNum=0;		
			}
		}
	}	
	return 0xFFFFFFFF;
}








 
unsigned long CS5530_GetCalib(CS5530Def *pInfo)
{
	if(pInfo->Flag.GetCali)	
	{
		if((pInfo->Data.WeighFilt!= 0xFFFFFFFF)&&(pInfo->Data.Origin!= 0))
		{
			unsigned short	Quq;
			unsigned long AD1,AD2;
			
			Quq	=	pInfo->Data.Quantity;		
			AD1	=	pInfo->Data.Origin;			
			AD2	=	pInfo->Data.WeighFilt;	
			if((Quq>0)&&(AD2>AD1))
			{
				pInfo->Flag.GetCali		=	0;
				pInfo->Data.WeighPie	=	(AD2-AD1)/Quq;
				return pInfo->Data.WeighPie;
			}
		}
	}
	return 0xFFFFFFFF;
}








 
unsigned long CS5530_GetOrigin(CS5530Def *pInfo)
{
	if(pInfo->Flag.GetOri)	
	{
		if((pInfo->Data.WeighFilt!= 0xFFFFFFFF)&&(pInfo->Data.WeighFilt!= 0))
		{
			pInfo->Flag.GetOri	=	0;
			pInfo->Data.Origin	=	pInfo->Data.WeighFilt;
			return pInfo->Data.Origin;
		}
	}
	return 0xFFFFFFFF;
}








 
unsigned long CS5530_GetQuant(CS5530Def *pInfo)
{
	if(pInfo->Flag.GetQua)	
	{
		if((pInfo->Data.WeighFilt!= 0xFFFFFFFF)&&(pInfo->Data.Origin!= 0))
		{
			unsigned short	Quq;
			unsigned long AD1,AD2,AD3;
			
			Quq	=	pInfo->Data.Quantity;
			AD1	=	pInfo->Data.Origin;			
			AD2	=	pInfo->Data.WeighFilt;	
			AD3	=	pInfo->Data.WeighPie;		
			if(AD2<=AD1)	
			{
				pInfo->Data.Quantity		=	0;
			}
			else
			{
				pInfo->Data.Quantity=((pInfo->Data.WeighFilt-pInfo->Data.Origin)+pInfo->Data.WeighPie/2)/pInfo->Data.WeighPie;	
			}
			pInfo->Flag.GetQua=0;	
		}		
	}
	return pInfo->Data.Quantity;
}








 
void CS5530_Clear(CS5530Def *pInfo)
{


	
	memset(&(pInfo->Data),0x00,(sizeof(pInfo->Data))/sizeof(char));
	memset(&(pInfo->Flag),0x00,(sizeof(pInfo->Flag))/sizeof(char));
}








 
void CS5530_Process(CS5530Def *pInfo)
{
	CS5530_GetWeigh(pInfo);	
	CS5530_GetOrigin(pInfo);
	CS5530_GetCalib(pInfo);
	CS5530_GetQuant(pInfo);		

}



 
