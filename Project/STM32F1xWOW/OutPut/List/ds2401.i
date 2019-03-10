#line 1 "..\\..\\Driver\\Components\\SCR\\DS2401.c"
#line 1 "..\\..\\Driver\\Components\\INC\\DS2401.h"
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






 
#line 4 "..\\..\\Driver\\Components\\INC\\DS2401.h"


typedef enum
{
	Cmd_ReadROM		=	0x33,			
	Cmd_MatchROM	=	0x55,			
	Cmd_SkipROM		=	0xCC,			
	Cmd_SearchROM	=	0xF0			
}DallasCmd;


uint8_t CRC8_Calculate(uint8_t *pBuf, uint8_t len);
uint8_t Dallas_Rest(void);								

uint8_t Dallas_ReadBit(void);					
uint8_t Dallas_ReadByte(void);				

void Dallas_WriteBit(unsigned char bit);		
void Dallas_WriteByte(uint8_t dat);		
uint8_t Dallas_Init(void);						
uint8_t Dallas_GetID(uint8_t *pBuf);	

    


#line 2 "..\\..\\Driver\\Components\\SCR\\DS2401.c"


#line 1 "..\\..\\Driver\\WOW\\INC\\STM32_GPIO.H"













 





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










#line 5 "..\\..\\Driver\\Components\\SCR\\DS2401.c"
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
	



#line 6 "..\\..\\Driver\\Components\\SCR\\DS2401.c"















const uint8_t g_CRC8Tab[256]=
{
0x00, 0x5e, 0xbc, 0xe2, 0x61, 0x3f, 0xdd, 0x83, 0xc2, 0x9c, 0x7e, 0x20, 0xa3, 0xfd, 0x1f, 0x41,
0x9d, 0xc3, 0x21, 0x7f, 0xfc, 0xa2, 0x40, 0x1e, 0x5f, 0x01, 0xe3, 0xbd, 0x3e, 0x60, 0x82, 0xdc,
0x23, 0x7d, 0x9f, 0xc1, 0x42, 0x1c, 0xfe, 0xa0, 0xe1, 0xbf, 0x5d, 0x03, 0x80, 0xde, 0x3c, 0x62,
0xbe, 0xe0, 0x02, 0x5c, 0xdf, 0x81, 0x63, 0x3d, 0x7c, 0x22, 0xc0, 0x9e, 0x1d, 0x43, 0xa1, 0xff,
0x46, 0x18, 0xfa, 0xa4, 0x27, 0x79, 0x9b, 0xc5, 0x84, 0xda, 0x38, 0x66, 0xe5, 0xbb, 0x59, 0x07,
0xdb, 0x85, 0x67, 0x39, 0xba, 0xe4, 0x06, 0x58, 0x19, 0x47, 0xa5, 0xfb, 0x78, 0x26, 0xc4, 0x9a,
0x65, 0x3b, 0xd9, 0x87, 0x04, 0x5a, 0xb8, 0xe6, 0xa7, 0xf9, 0x1b, 0x45, 0xc6, 0x98, 0x7a, 0x24,
0xf8, 0xa6, 0x44, 0x1a, 0x99, 0xc7, 0x25, 0x7b, 0x3a, 0x64, 0x86, 0xd8, 0x5b, 0x05, 0xe7, 0xb9,
0x8c, 0xd2, 0x30, 0x6e, 0xed, 0xb3, 0x51, 0x0f, 0x4e, 0x10, 0xf2, 0xac, 0x2f, 0x71, 0x93, 0xcd,
0x11, 0x4f, 0xad, 0xf3, 0x70, 0x2e, 0xcc, 0x92, 0xd3, 0x8d, 0x6f, 0x31, 0xb2, 0xec, 0x0e, 0x50,
0xaf, 0xf1, 0x13, 0x4d, 0xce, 0x90, 0x72, 0x2c, 0x6d, 0x33, 0xd1, 0x8f, 0x0c, 0x52, 0xb0, 0xee,
0x32, 0x6c, 0x8e, 0xd0, 0x53, 0x0d, 0xef, 0xb1, 0xf0, 0xae, 0x4c, 0x12, 0x91, 0xcf, 0x2d, 0x73,
0xca, 0x94, 0x76, 0x28, 0xab, 0xf5, 0x17, 0x49, 0x08, 0x56, 0xb4, 0xea, 0x69, 0x37, 0xd5, 0x8b,
0x57, 0x09, 0xeb, 0xb5, 0x36, 0x68, 0x8a, 0xd4, 0x95, 0xcb, 0x29, 0x77, 0xf4, 0xaa, 0x48, 0x16,
0xe9, 0xb7, 0x55, 0x0b, 0x88, 0xd6, 0x34, 0x6a, 0x2b, 0x75, 0x97, 0xc9, 0x4a, 0x14, 0xf6, 0xa8,
0x74, 0x2a, 0xc8, 0x96, 0x15, 0x4b, 0xa9, 0xf7, 0xb6, 0xe8, 0x0a, 0x54, 0xd7, 0x89, 0x6b, 0x35
};













uint8_t CRC8_Calculate(uint8_t *pBuf, uint8_t len)
{
	uint8_t crc8=0;	
	
	
	while(len)
	{
		crc8 = g_CRC8Tab[*pBuf^crc8];
		pBuf++;
		len--;
	}

	return(crc8);	
}  





 
void DS2401_Configuration(void)
{
	GPIO_Configuration_OPP50	(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0C00)),	((u16)0x4000));			
}






 
uint8_t Dallas_Rest(void)		
{
	uint16_t retry=0;
	
	GPIO_Configuration_OPP50(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0C00)), ((u16)0x4000));					
	((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0C00))->BRR = ((u16)0x4000);								
	SysTick_DeleyuS(750);		


	
	
	
	
	
	
	GPIO_Configuration_IPU(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0C00)), ((u16)0x4000));				
	SysTick_DeleyuS(15);		
	while(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0C00))->IDR & ((u16)0x4000)	&& (retry < 500))			
	{
		retry++;

	}
	if(retry >= 500)	
		return 1;
	else
		retry=0;
	
	SysTick_DeleyuS(480);		
	return 0;
}












 
uint8_t Dallas_ReadBit(void)
{
	uint8_t data;
	
	GPIO_Configuration_OPP50(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0C00)), ((u16)0x4000));				
	((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0C00))->BRR = ((u16)0x4000); 						
	SysTick_DeleyuS(5);		

	GPIO_Configuration_IPU(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0C00)), ((u16)0x4000));					
	SysTick_DeleyuS(12);	
	if(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0C00))->IDR & ((u16)0x4000))				
		data = 1;
	else
		data = 0;	 
	SysTick_DeleyuS(50);
	
	return data;
}








 
uint8_t Dallas_ReadByte(void)
{        
	uint8_t i,j,dat;
	
	dat = 0;
	for (i=1; i<=8; i++)
	{
		j = Dallas_ReadBit();		
		dat = (j<<7)|(dat>>1);	
	}	
	return dat;
}













 
void Dallas_WriteBit(unsigned char bit)		
{
		
		if (bit&0x01)		
		{
			((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0C00))->BRR = ((u16)0x4000);					
			SysTick_DeleyuS(2);		
			((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0C00))->BSRR = ((u16)0x4000);					
			SysTick_DeleyuS(60);	
		}
		
		else						
		{
			((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0C00))->BRR = ((u16)0x4000);					
			SysTick_DeleyuS(60);	
			((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0C00))->BSRR = ((u16)0x4000);					
			SysTick_DeleyuS(2);
		}
}








 
void Dallas_WriteByte(uint8_t dat)
{             
	uint8_t j;
	uint8_t testb;
	
	GPIO_Configuration_OPP50(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0C00)), ((u16)0x4000));							
	
	for (j=1; j<=8; j++)
	{
		testb = dat&0x01;
		dat = dat>>1;
		Dallas_WriteBit(testb);		
	}
}









 
uint8_t Dallas_Init(void)
{
	uint8_t Result	=	0;
	GPIO_Configuration_OPP50	(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0C00)),	((u16)0x4000));			



	return Result;
}








 
uint8_t Dallas_GetID(uint8_t *pBuf)
{
	uint8_t i;
	uint8_t buf[8];

	Dallas_Rest();						

	Dallas_WriteByte(0x33);		
	for(i=0; i<8; i++)
		buf[i] = Dallas_ReadByte();
	
	if(buf[0] != 0x01)
		return 1;
	if(CRC8_Calculate(buf, 7) != buf[7])
		return 1;

	for(i=0; i<8; i++)
		pBuf[i] = buf[i];
	
	return 0;
}


























































































































































































































