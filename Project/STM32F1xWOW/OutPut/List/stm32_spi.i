#line 1 "..\\..\\Driver\\WOW\\SCR\\STM32_SPI.C"


















 
#line 1 "..\\..\\Driver\\WOW\\INC\\STM32_SPI.H"













 





#line 1 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_spi.h"














 

 



 
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



 
#line 21 "..\\..\\Driver\\WOW\\INC\\STM32_SPI.H"
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









































































































#line 21 "..\\..\\Driver\\WOW\\SCR\\STM32_SPI.C"

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










#line 23 "..\\..\\Driver\\WOW\\SCR\\STM32_SPI.C"









#line 33 "..\\..\\Driver\\WOW\\SCR\\STM32_SPI.C"
#line 34 "..\\..\\Driver\\WOW\\SCR\\STM32_SPI.C"
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



 
#line 35 "..\\..\\Driver\\WOW\\SCR\\STM32_SPI.C"
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



 
#line 36 "..\\..\\Driver\\WOW\\SCR\\STM32_SPI.C"
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



 
#line 37 "..\\..\\Driver\\WOW\\SCR\\STM32_SPI.C"

unsigned  char spiTxBuff[256]={0};










 
void SPI_Delay(unsigned long Time)
{
	while(Time--);
}








 
void SPI_Initialize(SPIDef* pInfo)
{

	SPI_InitializeSPI(pInfo);	

	GPIO_Configuration_OPP50	(pInfo->Port.CS_PORT,pInfo->Port.CS_Pin);					
}








 
void SPI_InitializeNR(SPIDef* pInfo)					
{
	SPIPortDef		*Port;	

	Port			=	&(pInfo->Port);
	
	GPIO_Configuration_OPP50	(Port->CS_PORT,				Port->CS_Pin);					
	GPIO_Configuration_OPP50	(Port->CLK_PORT,			Port->CLK_Pin);					
	GPIO_Configuration_OPP50	(Port->MOSI_PORT,			Port->MOSI_Pin);					
	GPIO_Configuration_IPU		(Port->MISO_PORT,			Port->MISO_Pin);				
}





 
void SPI_InitializeSPI(SPIDef *pInfo)
{
	
	SPI_InitTypeDef  SPI_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	SPI_TypeDef *SPIx	=	pInfo->Port.SPIx;
	unsigned char SPIx_CsFlg=1;		

	
	switch(*(u32*)&SPIx)
	{
		case	((((u32)0x40000000) + 0x10000) + 0x3000):
										RCC_APB2PeriphClockCmd(((u32)0x00001000) ,ENABLE);			
										RCC_APB2PeriphClockCmd(((u32)0x00000001)|((u32)0x00000004), ENABLE);
										GPIO_InitStructure.GPIO_Pin = ((u16)0x0010) | ((u16)0x0020) | ((u16)0x0040) | ((u16)0x0080);
										GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
										GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
										GPIO_Init(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0800)), &GPIO_InitStructure);
					break;
		case	(((u32)0x40000000) + 0x3800):
										RCC_APB1PeriphClockCmd(((u32)0x00004000) ,ENABLE);				
										RCC_APB2PeriphClockCmd(((u32)0x00000001)|((u32)0x00000008), ENABLE);
										GPIO_InitStructure.GPIO_Pin = ((u16)0x1000) | ((u16)0x2000) | ((u16)0x4000) | ((u16)0x8000);
										GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
										GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  
										GPIO_Init(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0C00)), &GPIO_InitStructure);
					break;
		case	(((u32)0x40000000) + 0x3C00):
										RCC_APB1PeriphClockCmd(((u32)0x00008000) ,ENABLE);
										RCC_APB2PeriphClockCmd(((u32)0x00000001)|((u32)0x00000004)|((u32)0x00000008), ENABLE);
										GPIO_InitStructure.GPIO_Pin 	= ((u16)0x0008) | ((u16)0x0010) | ((u16)0x0020);
										GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
										GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_AF_PP;  		
										GPIO_Init(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0C00)), &GPIO_InitStructure);
										
										GPIO_InitStructure.GPIO_Pin 	= ((u16)0x8000);
										GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
										GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_AF_PP;  		
										GPIO_Init(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0800)), &GPIO_InitStructure);
					break;
		default		: break;
	}
	
	
	if(
			(((u16)0x0000)  !=	pInfo->Port.SPI_BaudRatePrescaler_x)
		&(((u16)0x0008)		!=	pInfo->Port.SPI_BaudRatePrescaler_x)
		&(((u16)0x0010)		!=	pInfo->Port.SPI_BaudRatePrescaler_x)
		&(((u16)0x0018)  !=	pInfo->Port.SPI_BaudRatePrescaler_x)
		&(((u16)0x0020)  !=	pInfo->Port.SPI_BaudRatePrescaler_x)
		&(((u16)0x0028)  !=	pInfo->Port.SPI_BaudRatePrescaler_x)
		&(((u16)0x0030)	!=	pInfo->Port.SPI_BaudRatePrescaler_x)
		&(((u16)0x0038)	!=	pInfo->Port.SPI_BaudRatePrescaler_x)
		)
	{
		
		pInfo->Port.SPI_BaudRatePrescaler_x	=	((u16)0x0000);
	}
	SPI_InitStructure.SPI_Direction = ((u16)0x0000);				
	SPI_InitStructure.SPI_Mode = ((u16)0x0104);															
	SPI_InitStructure.SPI_DataSize = ((u16)0x0000);													
	SPI_InitStructure.SPI_CPOL = ((u16)0x0002);																
	SPI_InitStructure.SPI_CPHA = ((u16)0x0001);															
	SPI_InitStructure.SPI_FirstBit = ((u16)0x0000);												
	SPI_InitStructure.SPI_CRCPolynomial = 7;																	
	SPI_InitStructure.SPI_NSS = ((u16)0x0200);																	
	SPI_InitStructure.SPI_BaudRatePrescaler = pInfo->Port.SPI_BaudRatePrescaler_x;				
	SPI_Init(pInfo->Port.SPIx,&SPI_InitStructure);
	


	if((pInfo->Port.SPIx->CR1&0X0200)!=((u16)0x0200))						
	{
		SPI_SSOutputCmd(pInfo->Port.SPIx, ENABLE);			
	}
  SPI_Cmd(pInfo->Port.SPIx, ENABLE);				
}







 
void SPI_InitializeDMA(SPIDef *pInfo)		
{










 
	
	SPI_InitTypeDef  SPI_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	DMA_InitTypeDef	DMA_Initstructure;
	DMA_Channel_TypeDef* DMAx_Channeltx=0;				
	DMA_Channel_TypeDef* DMAx_Channelrx=0;				
	SPI_TypeDef *	SPIx	=	pInfo->Port.SPIx;
	
	SPI_InitializeSPI(pInfo);					

	
	switch(*(u32*)&SPIx)
	{
		case	((((u32)0x40000000) + 0x10000) + 0x3000):
										DMAx_Channeltx=((DMA_Channel_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x0030));
										DMAx_Channelrx=((DMA_Channel_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x001C));
										RCC_AHBPeriphClockCmd(((u32)0x00000001),ENABLE);
					break;
		case	(((u32)0x40000000) + 0x3800):
										DMAx_Channeltx=((DMA_Channel_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x0058));
										DMAx_Channelrx=((DMA_Channel_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x0044));
										RCC_AHBPeriphClockCmd(((u32)0x00000001),ENABLE);
					break;
		case	(((u32)0x40000000) + 0x3C00):
										DMAx_Channeltx=((DMA_Channel_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x0408));
										DMAx_Channelrx=((DMA_Channel_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x041C));
										RCC_AHBPeriphClockCmd(((u32)0x00000002),ENABLE);
					break;
		default	:	break;
	}
	

		
		DMA_Initstructure.DMA_PeripheralBaseAddr =  (u32)(&SPIx->DR);	
		DMA_Initstructure.DMA_MemoryBaseAddr     = (u32)spiTxBuff;						
		DMA_Initstructure.DMA_DIR = ((u32)0x00000010);												
		DMA_Initstructure.DMA_BufferSize = 256; 													  
		DMA_Initstructure.DMA_PeripheralInc = ((u32)0x00000000);					
		DMA_Initstructure.DMA_MemoryInc =((u32)0x00000080);										
		DMA_Initstructure.DMA_PeripheralDataSize = ((u32)0x00000000);		
		DMA_Initstructure.DMA_MemoryDataSize = ((u32)0x00000000);						
		DMA_Initstructure.DMA_Mode = ((u32)0x00000000);															
		DMA_Initstructure.DMA_Priority = ((u32)0x00002000); 											
		DMA_Initstructure.DMA_M2M = ((u32)0x00000000);															
		DMA_Init(DMAx_Channeltx,&DMA_Initstructure);															

		
		DMA_Initstructure.DMA_PeripheralBaseAddr =  (u32)(&SPIx->DR);	
		DMA_Initstructure.DMA_MemoryBaseAddr     = 	(u32)spiTxBuff;						
		DMA_Initstructure.DMA_DIR = ((u32)0x00000000);												
		DMA_Initstructure.DMA_BufferSize = 256; 													  
		DMA_Initstructure.DMA_PeripheralInc = ((u32)0x00000000);					
		DMA_Initstructure.DMA_MemoryInc =((u32)0x00000080);										
		DMA_Initstructure.DMA_PeripheralDataSize = ((u32)0x00000000);		
		DMA_Initstructure.DMA_MemoryDataSize = ((u32)0x00000000);						
		DMA_Initstructure.DMA_Mode = ((u32)0x00000000);															
		DMA_Initstructure.DMA_Priority = ((u32)0x00002000); 											
		DMA_Initstructure.DMA_M2M = ((u32)0x00000000);															
		DMA_Init(DMAx_Channelrx,&DMA_Initstructure);															
		
		
			
		SPI_I2S_DMACmd(SPIx, ((u16)0x0002), ENABLE);								
		SPI_I2S_DMACmd(SPIx, ((u16)0x0001), ENABLE);								
		

		
		
		DMA_Cmd(DMAx_Channelrx,ENABLE);	
		DMA_Cmd(DMAx_Channeltx,ENABLE);


  
	











}



void SPI_CS_LOW(SPIDef *pInfo)
{
	pInfo->Port.CS_PORT->BRR		= pInfo->Port.CS_Pin;
}
void SPI_CS_HIGH(SPIDef *pInfo)
{
	pInfo->Port.CS_PORT->BSRR		= pInfo->Port.CS_Pin;
}
void SPI_CLK_LOW(SPIDef *pInfo)
{
	pInfo->Port.CLK_PORT->BRR 	= pInfo->Port.CLK_Pin;
}
void SPI_CLK_HIGH(SPIDef *pInfo)
{
	pInfo->Port.CLK_PORT->BSRR 	= pInfo->Port.CLK_Pin;
}
void SPI_MOSI_LOW(SPIDef *pInfo)
{
	pInfo->Port.CLK_PORT->BRR 	= pInfo->Port.CLK_Pin;
}
void SPI_MOSI_HIGH(SPIDef *pInfo)
{
	pInfo->Port.CLK_PORT->BSRR 	= pInfo->Port.CLK_Pin;
}
unsigned char SPI_MISO_In(SPIDef *pInfo)
{
	return(pInfo->Port.MISO_PORT->IDR 	&	pInfo->Port.MISO_Pin);
}








 
unsigned short SPI_DMASend(SPI_TypeDef* SPIx,unsigned char *tx_buffer,unsigned short BufferSize)
{

  switch(*(u32*)&SPIx)
  {
    case ((((u32)0x40000000) + 0x10000) + 0x3000):
      if(   (((DMA_Channel_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x0030))->CNDTR==0)										
        ||( (((DMA_Channel_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x0030))->CCR&0x00000001)==0))				
        {
          ((DMA_Channel_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x0030))->CCR &= (u32)0xFFFFFFFE;				
          ((DMA_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x0000))->IFCR = ((u32)0x00000100);										
          ((DMA_Channel_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x0030))->CNDTR 	=BufferSize;					  
          ((DMA_Channel_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x0030))->CMAR 	=(u32)tx_buffer;			  
          ((DMA_Channel_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x0030))->CCR |=(u32)0x00000001;			  
          return BufferSize;
        }
		case (((u32)0x40000000) + 0x3800):
      if(   (((DMA_Channel_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x0058))->CNDTR==0)										
        ||( (((DMA_Channel_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x0058))->CCR&0x00000001)==0))				
        {
          ((DMA_Channel_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x0058))->CCR &= (u32)0xFFFFFFFE;				
          ((DMA_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x0000))->IFCR = ((u32)0x00010000);										
          ((DMA_Channel_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x0058))->CNDTR 	=BufferSize;					  
          ((DMA_Channel_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x0058))->CMAR 	=(u32)tx_buffer;			  
          ((DMA_Channel_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x0058))->CCR |=(u32)0x00000001;			  
          return BufferSize;
        }




      break;
    default:break;
  }  
}








 
unsigned short SPI_DMAReadWrite(SPI_TypeDef* SPIx,unsigned char *tx_buffer,unsigned char *rx_buffer,unsigned short BufferSize)
{
  switch(*(u32*)&SPIx)
  {
    case (((u32)0x40000000) + 0x3800):
      
    if(SPI_I2S_GetFlagStatus(((SPI_TypeDef *) (((u32)0x40000000) + 0x3800)), ((u16)0x0002)) != RESET)  
    {
      if(0!=((DMA_Channel_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x0044))->CNDTR)       
      {
        unsigned  short RxdNum;  
        ((DMA_Channel_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x0044))->CCR &= (u32)0xFFFFFFFE;				
        RxdNum  = ((DMA_Channel_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x0044))->CNDTR;
        ((DMA_Channel_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x0044))->CNDTR  = 0;                  
        return RxdNum;      
      }
      else if(0 ==  ((DMA_Channel_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x0058))->CNDTR)   
      {
        
        ((DMA_Channel_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x0044))->CNDTR 	=BufferSize;					  
        ((DMA_Channel_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x0044))->CMAR = (u32)rx_buffer;
        ((DMA_Channel_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x0044))->CCR |=(u32)0x00000001;			  
        
        ((DMA_Channel_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x0058))->CCR &= (u32)0xFFFFFFFE;				
        ((DMA_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x0000))->IFCR = ((u32)0x00010000);										
        ((DMA_Channel_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x0058))->CNDTR 	=BufferSize;					  
        ((DMA_Channel_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x0058))->CMAR 	=(u32)tx_buffer;			  
        ((DMA_Channel_TypeDef *) ((((u32)0x40000000) + 0x20000) + 0x0058))->CCR |=(u32)0x00000001;			  
        return 0;
      }
    }
      break;
    default:break;
  }
  return 0xFFFF;
}








 
unsigned char	SPI_ReadWriteByteNR(SPIDef *pInfo,unsigned char Byte)
{
	unsigned char i	=	0;	
	unsigned char Recv	=	0;	

	for(i=0;i<8;i++)
	{
		Recv<<=1;
		SPI_CLK_LOW(pInfo);
		if((Byte&0x80)	==	0x80)
		{
			SPI_MOSI_HIGH(pInfo);
		}
		else
		{
			SPI_MOSI_LOW(pInfo);
		}
		if(SPI_MISO_In(pInfo))
		{
			Recv	|=	0x01;
		}		
		SPI_CLK_HIGH(pInfo);
		Byte<<=1;		
	}
	return Recv;
}





 
u8	SPI_ReadWriteByteSPI(SPIDef *pInfo,unsigned char Data)
{

	u16 retry=0;													
	
	while(SPI_I2S_GetFlagStatus(pInfo->Port.SPIx, ((u16)0x0002)) == RESET) 		
	{
		retry++;
		if(retry>5000)
			return 0;
	}	
	
	SPI_I2S_SendData(pInfo->Port.SPIx, Data);				
	
	retry=0;	
	while(SPI_I2S_GetFlagStatus(pInfo->Port.SPIx, ((u16)0x0001)) == RESET)		
	{
		retry++;
		if(retry>5000)
			return 0;
	}
	while (SPI_I2S_GetFlagStatus(pInfo->Port.SPIx, ((u16)0x0080)) == SET);
	
	return SPI_I2S_ReceiveData(pInfo->Port.SPIx); 			
}








 
void SPI_WriteBufferSPI(
										SPIDef *pInfo,
										u8 *Buffer,
										u16 BufferSize										
										)
{
	unsigned short bufferNum=0;


	for(bufferNum=0;bufferNum<BufferSize;bufferNum++)
	{
		SPI_ReadWriteByteSPI(pInfo,Buffer[bufferNum]);
	}


}








 
void SPI_ReadBufferSPI(
										SPIDef *pInfo,
										u8 *Buffer,
										u16 BufferSize										
										)
{
	unsigned short bufferNum=0;


	for(bufferNum=0;bufferNum<BufferSize;bufferNum++)
	{
		Buffer[bufferNum]	=	SPI_ReadWriteByteSPI(pInfo,0xFF);
	}


}


























































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































