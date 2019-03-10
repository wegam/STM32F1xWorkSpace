#line 1 "..\\..\\Examples\\WOW\\AMP_CABV11.C"
#line 1 "..\\..\\Examples\\WOW\\AMP_CABV11.H"



#line 1 "..\\..\\Driver\\Protocol\\AMP_PHY.H"





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




#line 5 "..\\..\\Examples\\WOW\\AMP_CABV11.H"































#line 43 "..\\..\\Examples\\WOW\\AMP_CABV11.H"












extern unsigned char MainFlag; 

void AMP_CABV11_Configuration(void);
void AMP_CABV11_Server(void);
void AMP_CABV11_Loop(void);
void CardReaderInitLoop(void);

void AMPCAB_Receive(void);
void AMPCAB_SwitchIDServer(void);
void AMPCAB_SYSLED(void);
void AMPCAB_BackLight(void);
void LockServer(void);


void AMPCABSwitchID_Configuration(void);
void AMPCAB_GenyConfiguration(void);
void AMPCABCOMM_Configuration(void);


unsigned short AMPCAB_SendBuff(enCCPortDef Port,unsigned char* pBuffer,unsigned short length);


unsigned short PCnet_Send(unsigned char* pBuffer,unsigned short length);      
unsigned short Cabinet_Send(unsigned char* pBuffer,unsigned short length);    
unsigned short Laynet_Send(unsigned char* pBuffer,unsigned short length);     
unsigned short CardPort_Send(unsigned char* pBuffer,unsigned short length);   




void Msg_Process(enCCPortDef Port,unsigned char* pBuffer,unsigned short length);        


void Msg_ProcessCB(enCCPortDef Port,unsigned char* pBuffer,unsigned short length);      
void Msg_ProcessPcPort(enCCPortDef Port,unsigned char* pBuffer,unsigned short length);
void Msg_ProcessCbPort(enCCPortDef Port,unsigned char* pBuffer,unsigned short length);
void Msg_ProcessCaPort(enCCPortDef Port,unsigned char* pBuffer,unsigned short length);
void Msg_ProcessLyPort(enCCPortDef Port,unsigned char* pBuffer,unsigned short length);
void CardDataSendUp(enCCPortDef Port,unsigned char* pBuffer,unsigned short length);




void RequestServer(void);   
void LockStatusUpdata(eucmddef Cmd,eLockStsdef std);
void CommTimeOutUpdata(enCCPortDef Port,stampaddrdef address);

#line 2 "..\\..\\Examples\\WOW\\AMP_CABV11.C"


#line 1 "..\\..\\Examples\\WOW\\AMP01V11.H"




#line 6 "..\\..\\Examples\\WOW\\AMP01V11.H"









extern stAMPProdef   AMPPro;

void AMP01V11_Configuration(void);
void AMP01V11_Server(void);

void AMP01V11_Loop(void);


unsigned short HW_SendBuff(enCCPortDef Port,unsigned char* pBuffer,unsigned short length);

void Tim_Server(void);


#line 5 "..\\..\\Examples\\WOW\\AMP_CABV11.C"

#line 7 "..\\..\\Examples\\WOW\\AMP_CABV11.C"

#line 1 "..\\..\\Driver\\Components\\INC\\IOT5302W.H"




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






#line 9 "..\\..\\Examples\\WOW\\AMP_CABV11.C"

#line 1 "..\\..\\Driver\\WOW\\INC\\STM32F10x_BitBand.H"




 




 












 

 



 
#line 31 "..\\..\\Driver\\WOW\\INC\\STM32F10x_BitBand.H"
 


 





#line 47 "..\\..\\Driver\\WOW\\INC\\STM32F10x_BitBand.H"
  
#line 55 "..\\..\\Driver\\WOW\\INC\\STM32F10x_BitBand.H"

 
 
 
 
 
#line 68 "..\\..\\Driver\\WOW\\INC\\STM32F10x_BitBand.H"

#line 76 "..\\..\\Driver\\WOW\\INC\\STM32F10x_BitBand.H"
 
#line 84 "..\\..\\Driver\\WOW\\INC\\STM32F10x_BitBand.H"

 
 
 
 
#line 103 "..\\..\\Driver\\WOW\\INC\\STM32F10x_BitBand.H"

 
 
 
 
#line 124 "..\\..\\Driver\\WOW\\INC\\STM32F10x_BitBand.H"

#line 141 "..\\..\\Driver\\WOW\\INC\\STM32F10x_BitBand.H"

 
#line 159 "..\\..\\Driver\\WOW\\INC\\STM32F10x_BitBand.H"

#line 176 "..\\..\\Driver\\WOW\\INC\\STM32F10x_BitBand.H"
 
#line 193 "..\\..\\Driver\\WOW\\INC\\STM32F10x_BitBand.H"

#line 210 "..\\..\\Driver\\WOW\\INC\\STM32F10x_BitBand.H"

 
#line 228 "..\\..\\Driver\\WOW\\INC\\STM32F10x_BitBand.H"

#line 245 "..\\..\\Driver\\WOW\\INC\\STM32F10x_BitBand.H"

 
#line 263 "..\\..\\Driver\\WOW\\INC\\STM32F10x_BitBand.H"

#line 280 "..\\..\\Driver\\WOW\\INC\\STM32F10x_BitBand.H"
 
  
#line 298 "..\\..\\Driver\\WOW\\INC\\STM32F10x_BitBand.H"

#line 315 "..\\..\\Driver\\WOW\\INC\\STM32F10x_BitBand.H"

					 


 


#line 11 "..\\..\\Examples\\WOW\\AMP_CABV11.C"
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










#line 12 "..\\..\\Examples\\WOW\\AMP_CABV11.C"
#line 1 "..\\..\\Driver\\WOW\\INC\\STM32_SYS.H"













 





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



 
#line 21 "..\\..\\Driver\\WOW\\INC\\STM32_SYS.H"
#line 1 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_flash.h"














 

 



 
#line 23 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_flash.h"

 

 
typedef enum
{ 
  FLASH_BUSY = 1,
  FLASH_ERROR_PG,
  FLASH_ERROR_WRP,
  FLASH_COMPLETE,
  FLASH_TIMEOUT
}FLASH_Status;


 








 







 







 

 
#line 97 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_flash.h"

 
#line 132 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_flash.h"






 





 





 





 





 





 






								 
 
 
 
void FLASH_SetLatency(u32 FLASH_Latency);										
void FLASH_HalfCycleAccessCmd(u32 FLASH_HalfCycleAccess);		
void FLASH_PrefetchBufferCmd(u32 FLASH_PrefetchBuffer);			


void FLASH_Unlock(void);		
void FLASH_Lock(void);			
FLASH_Status FLASH_ErasePage(u32 Page_Address);		
FLASH_Status FLASH_EraseAllPages(void);						
FLASH_Status FLASH_EraseOptionBytes(void);				
FLASH_Status FLASH_ProgramWord(u32 Address, u32 Data);					
FLASH_Status FLASH_ProgramHalfWord(u32 Address, u16 Data);			
FLASH_Status FLASH_ProgramOptionByteData(u32 Address, u8 Data);	
FLASH_Status FLASH_EnableWriteProtection(u32 FLASH_Pages);			
FLASH_Status FLASH_ReadOutProtection(FunctionalState NewState);	
FLASH_Status FLASH_UserOptionByteConfig(u16 OB_IWDG, u16 OB_STOP, u16 OB_STDBY);	
u32 FLASH_GetUserOptionByte(void);									
u32 FLASH_GetWriteProtectionOptionByte(void);				
FlagStatus FLASH_GetReadOutProtectionStatus(void);	
FlagStatus FLASH_GetPrefetchBufferStatus(void);			
void FLASH_ITConfig(u16 FLASH_IT, FunctionalState NewState);	
FlagStatus FLASH_GetFlagStatus(u16 FLASH_FLAG);			
void FLASH_ClearFlag(u16 FLASH_FLAG);								
FLASH_Status FLASH_GetStatus(void);									
FLASH_Status FLASH_WaitForLastOperation(u32 Timeout);	




 
#line 22 "..\\..\\Driver\\WOW\\INC\\STM32_SYS.H"
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



 
#line 23 "..\\..\\Driver\\WOW\\INC\\STM32_SYS.H"


void SYS_Configuration(void);			

void RCC_Configuration_HSE(void);			
void RCC_Configuration_HSI(void);			


void SYSCLKConfig_STOP(void);





#line 13 "..\\..\\Examples\\WOW\\AMP_CABV11.C"
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
	



#line 14 "..\\..\\Examples\\WOW\\AMP_CABV11.C"
#line 1 "..\\..\\Driver\\WOW\\INC\\STM32_WDG.H"













 





#line 1 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_iwdg.h"














 

 



 
#line 23 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_iwdg.h"

 
 
 






 
#line 41 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_iwdg.h"

#line 49 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_iwdg.h"

 







 
 
void IWDG_WriteAccessCmd(u16 IWDG_WriteAccess);
void IWDG_SetPrescaler(u8 IWDG_Prescaler);
void IWDG_SetReload(u16 Reload);
void IWDG_ReloadCounter(void);
void IWDG_Enable(void);
FlagStatus IWDG_GetFlagStatus(u16 IWDG_FLAG);



 
#line 21 "..\\..\\Driver\\WOW\\INC\\STM32_WDG.H"

void IWDG_Configuration(u32 Tout);	
void IWDG_Feed(void);								

void WWDG_Configuration(void);			
void WWDG_Feed(void);								









#line 15 "..\\..\\Examples\\WOW\\AMP_CABV11.C"
#line 1 "..\\..\\Driver\\WOW\\INC\\STM32_PWM.H"













 







#line 1 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_tim.h"














 

 



 
#line 23 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_tim.h"

 

 
typedef struct
{
  u16 TIM_Prescaler;
  u16 TIM_CounterMode;
  u16 TIM_Period;
  u16 TIM_ClockDivision;
  u8 TIM_RepetitionCounter;
} TIM_TimeBaseInitTypeDef;

 
typedef struct
{
  u16 TIM_OCMode;
  u16 TIM_OutputState;
  u16 TIM_OutputNState;
  u16 TIM_Pulse;
  u16 TIM_OCPolarity;
  u16 TIM_OCNPolarity;
  u16 TIM_OCIdleState;
  u16 TIM_OCNIdleState;
} TIM_OCInitTypeDef;

 
typedef struct
{
  u16 TIM_Channel;
  u16 TIM_ICPolarity;
  u16 TIM_ICSelection;
  u16 TIM_ICPrescaler;
  u16 TIM_ICFilter;
} TIM_ICInitTypeDef;

 
typedef struct
{
  u16 TIM_OSSRState;
  u16 TIM_OSSIState;
  u16 TIM_LOCKLevel; 
  u16 TIM_DeadTime;
  u16 TIM_Break;
  u16 TIM_BreakPolarity;
  u16 TIM_AutomaticOutput;
} TIM_BDTRInitTypeDef;

                              

#line 81 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_tim.h"




#line 91 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_tim.h"

 
#line 99 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_tim.h"

#line 106 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_tim.h"

#line 115 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_tim.h"
 






 
















 








 












 






 






 






 






 






 






 






 






 





 










 






 






 






 






 






 








 










 
#line 298 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_tim.h"



#line 308 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_tim.h"

#line 317 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_tim.h"

 
#line 338 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_tim.h"

#line 358 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_tim.h"

 
#line 378 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_tim.h"

#line 397 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_tim.h"

 
#line 406 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_tim.h"



#line 416 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_tim.h"

 










 
#line 437 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_tim.h"

#line 446 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_tim.h"






 








 






 






 






  








 
#line 500 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_tim.h"



#line 510 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_tim.h"

 






 






 





                                     
 






  
#line 548 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_tim.h"

#line 557 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_tim.h"

#line 593 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_tim.h"

 










 






 
#line 625 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_tim.h"

#line 638 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_tim.h"

#line 646 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_tim.h"

#line 665 "..\\..\\Library\\STM32F10x_StdPeriph_Driver\\INC\\stm32f10x_tim.h"
                                                                                            
 


 


 
 

void TIM_DeInit(TIM_TypeDef* TIMx);
void TIM_TimeBaseInit(TIM_TypeDef* TIMx, TIM_TimeBaseInitTypeDef* TIM_TimeBaseInitStruct);
void TIM_OC1Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct);
void TIM_OC2Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct);
void TIM_OC3Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct);
void TIM_OC4Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct);
void TIM_ICInit(TIM_TypeDef* TIMx, TIM_ICInitTypeDef* TIM_ICInitStruct);
void TIM_PWMIConfig(TIM_TypeDef* TIMx, TIM_ICInitTypeDef* TIM_ICInitStruct);
void TIM_BDTRConfig(TIM_TypeDef* TIMx, TIM_BDTRInitTypeDef *TIM_BDTRInitStruct);
void TIM_TimeBaseStructInit(TIM_TimeBaseInitTypeDef* TIM_TimeBaseInitStruct);
void TIM_OCStructInit(TIM_OCInitTypeDef* TIM_OCInitStruct);
void TIM_ICStructInit(TIM_ICInitTypeDef* TIM_ICInitStruct);
void TIM_BDTRStructInit(TIM_BDTRInitTypeDef* TIM_BDTRInitStruct);
void TIM_Cmd(TIM_TypeDef* TIMx, FunctionalState NewState);
void TIM_CtrlPWMOutputs(TIM_TypeDef* TIMx, FunctionalState NewState);
void TIM_ITConfig(TIM_TypeDef* TIMx, u16 TIM_IT, FunctionalState NewState);
void TIM_GenerateEvent(TIM_TypeDef* TIMx, u16 TIM_EventSource);
void TIM_DMAConfig(TIM_TypeDef* TIMx, u16 TIM_DMABase, u16 TIM_DMABurstLength);
void TIM_DMACmd(TIM_TypeDef* TIMx, u16 TIM_DMASource, FunctionalState NewState);
void TIM_InternalClockConfig(TIM_TypeDef* TIMx);
void TIM_ITRxExternalClockConfig(TIM_TypeDef* TIMx, u16 TIM_InputTriggerSource);
void TIM_TIxExternalClockConfig(TIM_TypeDef* TIMx, u16 TIM_TIxExternalCLKSource,
                                u16 TIM_ICPolarity, u16 ICFilter);                                
void TIM_ETRClockMode1Config(TIM_TypeDef* TIMx, u16 TIM_ExtTRGPrescaler, u16 TIM_ExtTRGPolarity,
                             u16 ExtTRGFilter);
void TIM_ETRClockMode2Config(TIM_TypeDef* TIMx, u16 TIM_ExtTRGPrescaler, 
                             u16 TIM_ExtTRGPolarity, u16 ExtTRGFilter);
void TIM_ETRConfig(TIM_TypeDef* TIMx, u16 TIM_ExtTRGPrescaler, u16 TIM_ExtTRGPolarity,
                   u16 ExtTRGFilter);
void TIM_PrescalerConfig(TIM_TypeDef* TIMx, u16 Prescaler, u16 TIM_PSCReloadMode);
void TIM_CounterModeConfig(TIM_TypeDef* TIMx, u16 TIM_CounterMode);
void TIM_SelectInputTrigger(TIM_TypeDef* TIMx, u16 TIM_InputTriggerSource);
void TIM_EncoderInterfaceConfig(TIM_TypeDef* TIMx, u16 TIM_EncoderMode,
                                u16 TIM_IC1Polarity, u16 TIM_IC2Polarity);
void TIM_ForcedOC1Config(TIM_TypeDef* TIMx, u16 TIM_ForcedAction);
void TIM_ForcedOC2Config(TIM_TypeDef* TIMx, u16 TIM_ForcedAction);
void TIM_ForcedOC3Config(TIM_TypeDef* TIMx, u16 TIM_ForcedAction);
void TIM_ForcedOC4Config(TIM_TypeDef* TIMx, u16 TIM_ForcedAction);
void TIM_ARRPreloadConfig(TIM_TypeDef* TIMx, FunctionalState NewState);
void TIM_SelectCOM(TIM_TypeDef* TIMx, FunctionalState NewState);
void TIM_SelectCCDMA(TIM_TypeDef* TIMx, FunctionalState NewState);
void TIM_CCPreloadControl(TIM_TypeDef* TIMx, FunctionalState NewState);
void TIM_OC1PreloadConfig(TIM_TypeDef* TIMx, u16 TIM_OCPreload);
void TIM_OC2PreloadConfig(TIM_TypeDef* TIMx, u16 TIM_OCPreload);
void TIM_OC3PreloadConfig(TIM_TypeDef* TIMx, u16 TIM_OCPreload);
void TIM_OC4PreloadConfig(TIM_TypeDef* TIMx, u16 TIM_OCPreload);
void TIM_OC1FastConfig(TIM_TypeDef* TIMx, u16 TIM_OCFast);
void TIM_OC2FastConfig(TIM_TypeDef* TIMx, u16 TIM_OCFast);
void TIM_OC3FastConfig(TIM_TypeDef* TIMx, u16 TIM_OCFast);
void TIM_OC4FastConfig(TIM_TypeDef* TIMx, u16 TIM_OCFast);
void TIM_ClearOC1Ref(TIM_TypeDef* TIMx, u16 TIM_OCClear);
void TIM_ClearOC2Ref(TIM_TypeDef* TIMx, u16 TIM_OCClear);
void TIM_ClearOC3Ref(TIM_TypeDef* TIMx, u16 TIM_OCClear);
void TIM_ClearOC4Ref(TIM_TypeDef* TIMx, u16 TIM_OCClear);
void TIM_OC1PolarityConfig(TIM_TypeDef* TIMx, u16 TIM_OCPolarity);
void TIM_OC1NPolarityConfig(TIM_TypeDef* TIMx, u16 TIM_OCNPolarity);
void TIM_OC2PolarityConfig(TIM_TypeDef* TIMx, u16 TIM_OCPolarity);
void TIM_OC2NPolarityConfig(TIM_TypeDef* TIMx, u16 TIM_OCNPolarity);
void TIM_OC3PolarityConfig(TIM_TypeDef* TIMx, u16 TIM_OCPolarity);
void TIM_OC3NPolarityConfig(TIM_TypeDef* TIMx, u16 TIM_OCNPolarity);
void TIM_OC4PolarityConfig(TIM_TypeDef* TIMx, u16 TIM_OCPolarity);
void TIM_CCxCmd(TIM_TypeDef* TIMx, u16 TIM_Channel, u16 TIM_CCx);
void TIM_CCxNCmd(TIM_TypeDef* TIMx, u16 TIM_Channel, u16 TIM_CCxN);
void TIM_SelectOCxM(TIM_TypeDef* TIMx, u16 TIM_Channel, u16 TIM_OCMode);
void TIM_UpdateDisableConfig(TIM_TypeDef* TIMx, FunctionalState NewState);
void TIM_UpdateRequestConfig(TIM_TypeDef* TIMx, u16 TIM_UpdateSource);
void TIM_SelectHallSensor(TIM_TypeDef* TIMx, FunctionalState NewState);
void TIM_SelectOnePulseMode(TIM_TypeDef* TIMx, u16 TIM_OPMode);
void TIM_SelectOutputTrigger(TIM_TypeDef* TIMx, u16 TIM_TRGOSource);
void TIM_SelectSlaveMode(TIM_TypeDef* TIMx, u16 TIM_SlaveMode);
void TIM_SelectMasterSlaveMode(TIM_TypeDef* TIMx, u16 TIM_MasterSlaveMode);
void TIM_SetCounter(TIM_TypeDef* TIMx, u16 Counter);
void TIM_SetAutoreload(TIM_TypeDef* TIMx, u16 Autoreload);
void TIM_SetCompare1(TIM_TypeDef* TIMx, u16 Compare1);
void TIM_SetCompare2(TIM_TypeDef* TIMx, u16 Compare2);
void TIM_SetCompare3(TIM_TypeDef* TIMx, u16 Compare3);
void TIM_SetCompare4(TIM_TypeDef* TIMx, u16 Compare4);
void TIM_SetIC1Prescaler(TIM_TypeDef* TIMx, u16 TIM_ICPSC);
void TIM_SetIC2Prescaler(TIM_TypeDef* TIMx, u16 TIM_ICPSC);
void TIM_SetIC3Prescaler(TIM_TypeDef* TIMx, u16 TIM_ICPSC);
void TIM_SetIC4Prescaler(TIM_TypeDef* TIMx, u16 TIM_ICPSC);
void TIM_SetClockDivision(TIM_TypeDef* TIMx, u16 TIM_CKD);
u16 TIM_GetCapture1(TIM_TypeDef* TIMx);
u16 TIM_GetCapture2(TIM_TypeDef* TIMx);
u16 TIM_GetCapture3(TIM_TypeDef* TIMx);
u16 TIM_GetCapture4(TIM_TypeDef* TIMx);
u16 TIM_GetCounter(TIM_TypeDef* TIMx);
u16 TIM_GetPrescaler(TIM_TypeDef* TIMx);
FlagStatus TIM_GetFlagStatus(TIM_TypeDef* TIMx, u16 TIM_FLAG);
void TIM_ClearFlag(TIM_TypeDef* TIMx, u16 TIM_FLAG);
ITStatus TIM_GetITStatus(TIM_TypeDef* TIMx, u16 TIM_IT);
void TIM_ClearITPendingBit(TIM_TypeDef* TIMx, u16 TIM_IT);
                                                                                                             


 








#line 23 "..\\..\\Driver\\WOW\\INC\\STM32_PWM.H"
#line 24 "..\\..\\Driver\\WOW\\INC\\STM32_PWM.H"
#line 25 "..\\..\\Driver\\WOW\\INC\\STM32_PWM.H"
#line 26 "..\\..\\Driver\\WOW\\INC\\STM32_PWM.H"




typedef enum
{
  PWM_OUTChannel1	=	0,
	PWM_OUTChannel2,
	PWM_OUTChannel3,
	PWM_OUTChannel4,
} PWM_OUTChannelTypeDef;
typedef struct
{
	TIM_TypeDef*	TIMx;
	GPIO_TypeDef*	GPIOx;			
	u16 GPIO_Pin_n;						
	
	double PWM_Frequency;			
	u16 	PWM_Updata;					
	u32 	PWM_RunUp;					
	u32 	PWM_Count;					
}PWM_BasicDataDef;
typedef struct
{
	u16 	PWM_Cycle ;						
	u32 	PWM_Pulse;						
}PWM_RunDataDef;
typedef struct
{

	struct
	{
		TIM_TypeDef*	TIMx;
		GPIO_TypeDef*	GPIOx;			
		u16 GPIO_Pin_n;						
		
		double PWM_Frequency;			
		u16 	PWM_Updata;					
		u32 	PWM_RunUp;					
		u32 	PWM_Count;					
	}PWM_BasicData;		

	struct
	{
		u16 	PWM_Cycle ;					
		u32 	PWM_Pulse;					
	}PWM_RunData;			
}PWM_TimDef;
extern u32 Tim1_Count;
extern u32 Tim2_Count;
extern u32 Tim3_Count;
extern u32 Tim4_Count;


void PWM_OUT(TIM_TypeDef* TIMx,PWM_OUTChannelTypeDef PWM_OUTChanneln,double PWM_Frequency ,u16 PWM_Ratio);	
void PWM_OUTRemap(TIM_TypeDef* TIMx,PWM_OUTChannelTypeDef PWM_OUTChanneln,double PWM_Frequency ,u16 PWM_Ratio);	

void PWM_OUT2(TIM_TypeDef* TIMx,PWM_OUTChannelTypeDef PWM_OUTChanneln,double PWM_Frequency ,u16 PWM_Ratio);	
void SetPWM_Ratio(u16 PWM_Ratio);		





void PWM_OUT_TIMConf(PWM_TimDef* PWM_Tim);									
void PWM_OUT_SetFre(PWM_TimDef* PWM_Tim,double PWM_Frequency);	
void PWM_OUT_SetCount(PWM_TimDef* PWM_Tim,u32 PWM_Count);			
u8 PWM_OUT_TIMServer(PWM_TimDef* PWM_Tim);									



#line 16 "..\\..\\Examples\\WOW\\AMP_CABV11.C"
#line 17 "..\\..\\Examples\\WOW\\AMP_CABV11.C"

#line 1 "..\\..\\Driver\\Components\\INC\\SWITCHID.H"




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





#line 19 "..\\..\\Examples\\WOW\\AMP_CABV11.C"

#line 1 "..\\..\\Driver\\Tool\\CRC.H"














unsigned short CRC16_CCITT(unsigned char *puchMsg, unsigned int usDataLen);				
unsigned short CRC16_CCITT_FALSE(unsigned char *puchMsg, unsigned int usDataLen);	
unsigned short CRC16_XMODEM(unsigned char *puchMsg, unsigned int usDataLen);				
unsigned short CRC16_X25(unsigned char *puchMsg, unsigned int usDataLen);					
unsigned short CRC16_MODBUS(unsigned char *puchMsg, unsigned int usDataLen);				
unsigned short CRC16_IBM(unsigned char *puchMsg, unsigned int usDataLen);					
unsigned short CRC16_MAXIM(unsigned char *puchMsg, unsigned int usDataLen);				
unsigned short CRC16_USB(unsigned char *puchMsg, unsigned int usDataLen);					





#line 21 "..\\..\\Examples\\WOW\\AMP_CABV11.C"

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



 

#line 23 "..\\..\\Examples\\WOW\\AMP_CABV11.C"


RS485Def stCbRS485Ly;   
RS485Def stCbRS485Cb;   
RS485Def stCardRS485Ly; 
SwitchDef stCbSwitch;

unsigned char CardData[64]={0}; 
unsigned char CardNum=0;  
unsigned short InitCardReaderTimeOut=0; 
unsigned char InitCardReaderFlag=0; 
unsigned long InitCardUSART_BaudRate=0; 
unsigned char CabAddr   =0;
unsigned char MainFlag  =0; 









 
void AMP_CABV11_Configuration(void)
{	
	SYS_Configuration();					
  
  AMPCABSwitchID_Configuration();
  
  AMPCAB_GenyConfiguration();   
    
  AMPCABCOMM_Configuration();   
  
  SysTick_DeleymS(1000);				

}








 
void AMP_CABV11_Server(void)
{
  
  LockServer();       
  RequestServer();    
  AMPCAB_SwitchIDServer();
  AMPCAB_SYSLED();
  AMPCAB_BackLight();     
  API_IOT5302WServer();   
}










 
void AMP_CABV11_Loop(void)
{ 
  
  AMPCAB_Receive();
  Send_Server();
  
}








 
void CardReaderInitLoop(void)
{
  unsigned char data[64]={0};
  unsigned char RxNum  = 0;
  
  RxNum = RS485_ReadBufferIDLE(&stCardRS485Ly,data);
  if(RxNum)
  {
    unsigned char i=0;
    if(RxNum>64)
      RxNum=64;
    
    memcpy(&CardData[CardNum],data,RxNum);
    CardNum+=RxNum;
    if(CardNum>=64)
    {
      CardNum=0;
    }
    for(i=0;i<64;i++)
    {
      if(CardData[i]==0xAA)
      {
        if((CardData[i+2]==0x02)   
          &&(CardData[i+3]==0x00)  
        &&(CardData[i+4]==0x01)    
        &&(CardData[i+6]==0xBB))   
        {
          InitCardReaderFlag=1;
          InitCardUSART_BaudRate=19200;
          RS485_DMA_ConfigurationNR(&stCardRS485Ly,InitCardUSART_BaudRate,128);	
        }
      }
    }
  } 
}








 
void AMPCAB_Receive(void)
{
  unsigned short RxNum  = 0;
  unsigned char rxd[256]={0};
  
  
  RxNum = USART_ReadBufferIDLE(((USART_TypeDef *) (((u32)0x40000000) + 0x4400)),rxd);
  if(RxNum)
  {
    Msg_ProcessCB(PcPort,rxd,RxNum);                
  }
  
  RxNum = RS485_ReadBufferIDLE(&stCbRS485Cb,rxd);
  if(RxNum)
  {
    Msg_ProcessCB(CabPort,rxd,RxNum);
  }  
  
  RxNum = RS485_ReadBufferIDLE(&stCbRS485Ly,rxd);
  if(RxNum)
  {
    Msg_ProcessCB(LayPort,rxd,RxNum);              
  }
  
  RxNum = API_IOT5302WGetUID(rxd);
  if(RxNum)
  {
    Msg_ProcessCB(CardPort,rxd,RxNum);
  }
}








 
void AMPCAB_SwitchIDServer(void)
{
  unsigned char cabaddrbac=CabAddr;
  if(0==AMPPro.Time.swicthidtime)
  {
    CabAddr  = SWITCHID_ReadLeft(&stCbSwitch)&0x3F;
  
    if(SWITCHID_ReadLeft(&stCbSwitch)&0x80)
    {
      MainFlag=1; 
    }
    else
    {
      MainFlag=0; 
    }
    if(cabaddrbac!=CabAddr)
    {
      AMPCABCOMM_Configuration();   
    }
  }
}








 
void AMPCAB_SYSLED(void)
{
  if(0==AMPPro.Time.SYSLEDTime)
  {    
    GPIO_Toggle	(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0800)),((u16)0x0001));		
    if(CabAddr)   
    {
      AMPPro.Time.SYSLEDTime=500;
    }
    else          
    {
      AMPPro.Time.SYSLEDTime=100;
    }
  }
}









 
void AMPCAB_BackLight(void)
{
  static unsigned short BLtime=0;
  if(0==CabAddr)   
  {    
    if(BLtime++>200)
    {
      BLtime=0;
      GPIO_Toggle	(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1000)),((u16)0x0020));		
    }
    return;
  }
  if(AMPPro.Req.BLon)      
  {
    ((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1000))->BSRR = ((u16)0x0020);
    AMPPro.Req.BLon=0;
  }
  else if(AMPPro.Req.BLoff)
  {
    ((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1000))->BRR = ((u16)0x0020);
    AMPPro.Req.BLoff=0;
  }
}








 
void LockServer(void)
{
    
    if(0  ==  CabAddr)    
    {
      if(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1000))->IDR & ((u16)0x1000))  
      {
        ((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0C00))->BSRR = ((u16)0x0001);
      }
      else
      {
        ((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0C00))->BRR = ((u16)0x0001);
      }
      return;
    }
    
    if(1==AMPPro.Req.unlockrun)   
    {
      if(AMPPro.Time.LockTime>2000-10)
      {
        return;
      }
      if(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1000))->IDR & ((u16)0x1000))    
      {
        AMPPro.Sta.lockstd  = 1;    
        if(AMPPro.Time.LockTime==0) 
        {
          AMPPro.Req.unlockrun  = 0;  
          AMPPro.Time.LockTime  = 0;  
          LockStatusUpdata(AmpCmdLock,AmpLockOpenFailed);  
          ((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0C00))->BRR = ((u16)0x0001);
        }
      }
      
      else
      {
        if(0==AMPPro.Req.reslockqust) 
        {
          AMPPro.Req.reslockqust  = 1;  
          AMPPro.Time.LockTime    = 200;  
        }
        else
        {
          if(0==AMPPro.Time.LockTime)
          { 
            AMPPro.Sta.lockstd    = 0;  
            AMPPro.Req.unlockrun  = 0;
            AMPPro.Req.reslockqust= 0;  
            AMPPro.Sta.unlockerr  = 0;
            AMPPro.Time.LockTime  = 0;
            ((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0C00))->BRR = ((u16)0x0001);
            
            LockStatusUpdata(AmpCmdLock,AmpLockOpen);  
          }
        }                
      }      
    }
    
    if(1==AMPPro.Req.unlockqust)  
    {
      AMPPro.Req.unlockrun  = 1;
      AMPPro.Req.unlockqust = 0;
      AMPPro.Req.reslock    = 0;
      AMPPro.Req.reslockqust=0;   
      AMPPro.Sta.unlockerr  = 0;
      
      
      AMPPro.Req.BLon=1;   
      AMPPro.Req.PLon=1;   
      
      AMPPro.Time.LockTime   = 2000;    
      ((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0C00))->BSRR = ((u16)0x0001);
    }
    
    
    if(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1000))->IDR & ((u16)0x1000))    
    {
      
      if(0==AMPPro.Sta.lockstd)
      {
        AMPPro.Req.BLoff = 1;  
        AMPPro.Req.PLoff = 1;  
        AMPPro.Flag.LayPownOn=0; 
        
        LockStatusUpdata(AmpCmdLock,AmpLockOn);  
      }      
      AMPPro.Sta.lockstd  = 1;
      
    }
    else
    {
      if(1==AMPPro.Sta.lockstd) 
      {
        AMPPro.Req.BLon = 1;  
        AMPPro.Req.PLon = 1;  
        AMPPro.Flag.LayPownOn=1;
        
        LockStatusUpdata(AmpCmdLock,AmpLockOpen);  
      }
      AMPPro.Sta.lockstd  = 0;
    }
}








 
void AMPCABSwitchID_Configuration(void)
{
  stCbSwitch.NumOfSW	=	8;
  
  stCbSwitch.SW1_PORT	=	((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0C00));
  stCbSwitch.SW1_Pin	=	((u16)0x0200);
  
  stCbSwitch.SW2_PORT	=	((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0C00));
  stCbSwitch.SW2_Pin	=	((u16)0x0100);
  
  stCbSwitch.SW3_PORT	=	((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0C00));
  stCbSwitch.SW3_Pin	=	((u16)0x0080);
  
  stCbSwitch.SW4_PORT	=	((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0C00));
  stCbSwitch.SW4_Pin	=	((u16)0x0040);
  
  stCbSwitch.SW5_PORT	=	((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0C00));
  stCbSwitch.SW5_Pin	=	((u16)0x0020);
  
  stCbSwitch.SW6_PORT	=	((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0C00));
  stCbSwitch.SW6_Pin	=	((u16)0x0010);
  
  stCbSwitch.SW7_PORT	=	((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0C00));
  stCbSwitch.SW7_Pin	=	((u16)0x0008);
  
  stCbSwitch.SW8_PORT	=	((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1400));
  stCbSwitch.SW8_Pin	=	((u16)0x0004);

	SwitchIdInitialize(&stCbSwitch);						

  CabAddr  = SWITCHID_ReadLeft(&stCbSwitch)&0x3F;  
  
  if(SWITCHID_ReadLeft(&stCbSwitch)&0x80)
  {
    MainFlag=1; 
  }
  else
  {
    MainFlag=0; 
  }
}








 
void AMPCAB_GenyConfiguration(void)
{
  
  GPIO_Configuration_OPP50(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0C00)),((u16)0x0001));
  GPIO_Configuration_IPU(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1000)),((u16)0x1000));
  ((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0C00))->BRR = ((u16)0x0001);    
  
  GPIO_Configuration_OPP50(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1000)),((u16)0x0020));
  ((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x1000))->BSRR = ((u16)0x0020);
  
  GPIO_Configuration_OPP50(((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0C00)),((u16)0x0002));
  ((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0C00))->BSRR = ((u16)0x0002);   
}









 
void AMPCABCOMM_Configuration(void)
{
  IOT5302Wdef IOT5302W;
  
  USART_DMA_ConfigurationNR	(((USART_TypeDef *) (((u32)0x40000000) + 0x4400)),19200,128);	
  
  
  IOT5302W.Conf.IOT5302WPort.USARTx  = ((USART_TypeDef *) (((u32)0x40000000) + 0x4800));
  IOT5302W.Conf.IOT5302WPort.RS485_CTL_PORT  = ((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0C00));
  IOT5302W.Conf.IOT5302WPort.RS485_CTL_Pin   = ((u16)0x0004);
  IOT5302W.Conf.USART_BaudRate  = 19200;
  API_IOT5302WConfiguration(&IOT5302W);
  
  stCbRS485Ly.USARTx  = ((USART_TypeDef *) (((u32)0x40000000) + 0x4C00));
  stCbRS485Ly.RS485_CTL_PORT  = ((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0800));
  stCbRS485Ly.RS485_CTL_Pin   = ((u16)0x8000);
  RS485_DMA_ConfigurationNR			(&stCbRS485Ly,19200,128);	
  
  stCbRS485Cb.USARTx  = ((USART_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x3800));
  stCbRS485Cb.RS485_CTL_PORT  = ((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0800));
  stCbRS485Cb.RS485_CTL_Pin   = ((u16)0x0100);
  RS485_DMA_ConfigurationNR			(&stCbRS485Cb,19200,128);	
}








 
unsigned short AMPCAB_SendBuff(enCCPortDef Port,unsigned char* pBuffer,unsigned short length)
{ 
  unsigned  short   sendedlen = 0;
  switch(Port)
  {
    case  NonPort   : return 0;   
    case  PcPort    : sendedlen = USART_DMASend(((USART_TypeDef *) (((u32)0x40000000) + 0x4400)),pBuffer,length);
      break;
    case  CabPort   : sendedlen = RS485_DMASend(&stCbRS485Cb,pBuffer,length);	
      break;
    case  LayPort   : sendedlen = RS485_DMASend(&stCbRS485Ly,pBuffer,length);	
      break;
    case  CardPort  : sendedlen = RS485_DMASend(&stCardRS485Ly,pBuffer,length);	
      break;
    default :return 0;      
  }
  return  sendedlen;
}








 
unsigned short PCnet_Send(unsigned char* pBuffer,unsigned short length)
{
  return(AddSendBuffer(PcPort,pBuffer,length));
}








 
unsigned short Cabinet_Send(unsigned char* pBuffer,unsigned short length)
{
  return(AddSendBuffer(CabPort,pBuffer,length));
}








 
unsigned short Laynet_Send(unsigned char* pBuffer,unsigned short length)
{
  return(AddSendBuffer(LayPort,pBuffer,length));
}








 
unsigned short CardPort_Send(unsigned char* pBuffer,unsigned short length)
{
  return(AddSendBuffer(CardPort,pBuffer,length));
}









 
void Msg_ProcessCB(enCCPortDef Port,unsigned char* pBuffer,unsigned short length)
{  
  switch(Port)
  {
    case PcPort:Msg_ProcessPcPort(Port,pBuffer,length);     
      break;
    case CabPort:Msg_ProcessCbPort(Port,pBuffer,length);    
      break;
    case LayPort:Msg_ProcessLyPort(Port,pBuffer,length);    
      break;
    case CardPort:Msg_ProcessCaPort(Port,pBuffer,length);   
      break;
    default:
      break;
  }
}








 
void Msg_ProcessPcPort(enCCPortDef Port,unsigned char* pBuffer,unsigned short length)
{  
  unsigned  char result       = 0; 
  unsigned  char address      = 0;  
  unsigned  short framlength  = 0; 
  unsigned  char  Cmd         = 0;  
  unsigned  char* paddrbac    = pBuffer;         
  
  stampphydef* ampframe=0;
  
  if(PcPort!=Port||0==pBuffer)
  {
    return;
  } 
  
  framlength	=	getframe(pBuffer,&length);    
  if(0== framlength)
  {
    memset(paddrbac,0x00,128);          
    return;
  }
  result  = ackcheck(pBuffer);                
  if(1==result)
  {
    if(AMPPro.buffer.WaitAck.Pc)      
    {
      AMPPro.buffer.WaitAck.Pc=0;
      Releas_OneBuffer(Port);        
    }
    return;
  }  
  
  ampframe  = (stampphydef*)pBuffer;
  Cmd = ampframe->msg.cmd.cmd;  
  
  
  
  
  

  
  if(MainFlag)  
  {
  }
  address=ampframe->msg.addr.address1;
  if(0==address)      
  {
    return;
  }
  
  ackFrame(Port,1);             
  
  if((CabAddr!=address))  
  {
    
    Cabinet_Send((unsigned char*)ampframe,framlength);
    if(0xFF==address) 
    {      
      AMPPro.buffer.WaitAck.Cab=0;   
    }
    else
    {
      
      AMPPro.buffer.WaitAck.Cab=1;  
      return;       
    }
  }
  
  
  
  
  if(AmpCmdLed ==  Cmd)       
  {
    if((0x00==ampframe->msg.addr.address2)||(0x00==ampframe->msg.addr.address3))
    {
      return;   
    }
    else if((0xFF==ampframe->msg.addr.address2)||(0xFF==ampframe->msg.addr.address3))
    {
      AMPPro.buffer.WaitAck.Lay=0;   
    }
    else
    {
      AMPPro.buffer.WaitAck.Lay=1;   
    }
    AMPPro.Req.PLon  =1;    
    AMPPro.Req.PLoff =0;    
    Laynet_Send((unsigned char*)ampframe,framlength);     
  }
  else if(AmpCmdPwr ==  Cmd)   
  {
    AMPPro.Req.PLon  =0;
    AMPPro.Req.PLoff =0;
    
    if(ampframe->msg.data[0])
      AMPPro.Req.PLon=1;
    else
      AMPPro.Req.PLoff=1;
  }
  else if(AmpCmdLock ==  Cmd)   
  {
    AMPPro.Req.reslock  =0;
    AMPPro.Req.unlockqust =0;
    
    if(ampframe->msg.data[0])
      AMPPro.Req.unlockqust=1;
    else
      AMPPro.Req.reslock=1;
  }
  else if(AmpCmdBKligth ==  Cmd)   
  {
    AMPPro.Req.BLon     =0;
    AMPPro.Req.BLoff    =0;
    
    if(ampframe->msg.data[0])
      AMPPro.Req.BLon=1;
    else
      AMPPro.Req.BLoff=1;    
  }
  else if(AmpCmdSta ==  Cmd)   
  {
    if(0==AMPPro.Sta.lockstd) 
    {
      LockStatusUpdata(AmpCmdSta,AmpLockOpen);  
    }
    else
    {
      LockStatusUpdata(AmpCmdSta,AmpLockOn);  
    }
  }
}








 
void Msg_ProcessCbPort(enCCPortDef Port,unsigned char* pBuffer,unsigned short length)
{  
  unsigned  char result       = 0; 
  unsigned  char address      = 0;  
  unsigned  short framlength  = 0; 
  unsigned  char  Cmd         = 0;  
  unsigned  char* paddrbac    = pBuffer;         
  
  stampphydef* ampframe=0;
  
  if(CabPort!=Port||0==pBuffer)
  {
    return;
  } 
  
  framlength	=	getframe(pBuffer,&length);    
  if(0== framlength)
  {
    memset(paddrbac,0x00,128);             
    return;
  }
  result  = ackcheck(pBuffer);                
  if(1==result)
  {
    if(AMPPro.buffer.WaitAck.Cab)           
    {
      AMPPro.buffer.WaitAck.Cab=0;
      Releas_OneBuffer(Port);               
    }
    return;
  }  
  
  ampframe  = (stampphydef*)pBuffer;
  Cmd = ampframe->msg.cmd.cmd;  
  
  
  
  
  
  if(ampframe->msg.cmd.dir)   
  {
    if(MainFlag)    
    {
      ackFrame(Port,0); 
      AMPPro.buffer.WaitAck.Pc=1;   
      PCnet_Send((unsigned char*)ampframe,framlength);      
    }
    return;   
  }
  
  address=ampframe->msg.addr.address1;
  if(0==address)      
  {
    return;
  }
  if((CabAddr!=address)&&(0xFF!=address))  
  {
    return;
  }
  if(CabAddr==address)
    ackFrame(Port,1);             
  
  if(AmpCmdLed ==  Cmd)       
  {
    if((0x00==ampframe->msg.addr.address2)||(0x00==ampframe->msg.addr.address3))
    {
      return;   
    }
    else if((0xFF==ampframe->msg.addr.address2)||(0xFF==ampframe->msg.addr.address3))
    {
      AMPPro.buffer.WaitAck.Lay=0;   
    }
    else
    {
      AMPPro.buffer.WaitAck.Lay=1;   
    }
    AMPPro.Req.PLon  =1;    
    AMPPro.Req.PLoff =0;
    Laynet_Send((unsigned char*)ampframe,framlength);     
  }
  else if(AmpCmdPwr ==  Cmd)   
  {
    AMPPro.Req.PLon  =0;
    AMPPro.Req.PLoff =0;
    
    if(ampframe->msg.data[0])
      AMPPro.Req.PLon=1;
    else
      AMPPro.Req.PLoff=1;
  }
  else if(AmpCmdLock ==  Cmd)   
  {
    AMPPro.Req.reslock  =0;
    AMPPro.Req.unlockqust =0;
    
    if(ampframe->msg.data[0])
      AMPPro.Req.unlockqust=1;
    else
      AMPPro.Req.reslock=1;
  }
  else if(AmpCmdBKligth ==  Cmd)   
  {
    AMPPro.Req.BLon     =0;
    AMPPro.Req.BLoff    =0;
    
    if(ampframe->msg.data[0])
      AMPPro.Req.BLon=1;
    else
      AMPPro.Req.BLoff=1;    
  }
  else if(AmpCmdSta ==  Cmd)   
  {
    if(0==AMPPro.Sta.lockstd) 
    {
      LockStatusUpdata(AmpCmdSta,AmpLockOpen);  
    }
    else
    {
      LockStatusUpdata(AmpCmdSta,AmpLockOn);    
    }
  }
}








 
void Msg_ProcessCaPort(enCCPortDef Port,unsigned char* pBuffer,unsigned short length)
{  
  CardDataSendUp(Port,pBuffer,length);
}








 
void Msg_ProcessLyPort(enCCPortDef Port,unsigned char* pBuffer,unsigned short length)
{  
  unsigned  char result       = 0; 
  
  unsigned  short framlength  = 0; 
  
  unsigned  char* paddrbac    = pBuffer;         
  
  stampphydef* ampframe=0;
  
  framlength=length;
  
  
  framlength	=	getframe(paddrbac,&framlength);    
  if(0== framlength)    
  {

    return;
  }
  
  pBuffer=paddrbac;  
  result  = ackcheck(pBuffer);                
  if(1==result)
  {
    if(AMPPro.buffer.WaitAck.Lay)      
    {
      AMPPro.buffer.WaitAck.Lay=0;
      Releas_OneBuffer(Port);        
    }
    return;
  }  
  
  ampframe  = (stampphydef*)pBuffer;
  
  
  
  
  
  
  
  if(1==ampframe->msg.cmd.dir)
  {
    unsigned  char  databuffer[64]={0};
    
    ackFrame(Port,0); 
       
    
    memcpy(databuffer,pBuffer,length);
    framlength  = length;
    framlength  = PaketUpMsg(databuffer,AmpCmdCard,&framlength);
    
    ampframe  = (stampphydef*)databuffer;
    ampframe->msg.addr.address1 = CabAddr;
    
    SetFrame(databuffer,&framlength);   
    
    if(1==MainFlag)   
    {
      AMPPro.buffer.WaitAck.Pc=1;   
      PCnet_Send(databuffer,framlength);
    }
    else  
    {
      AMPPro.buffer.WaitAck.Cab=1;   
      Cabinet_Send(databuffer,framlength);     
    }    
    return;
  }
  
  else
  {
    return;
  }
}








 
void CardDataSendUp(enCCPortDef Port,unsigned char* pBuffer,unsigned short length)
{
  
  
  unsigned  short framlength  = 0;  
  
  
  stampphydef* ampframe=0;
  
  
  unsigned  char  databuffer[64]={0};   
  
  memcpy(databuffer,pBuffer,length);
  framlength  = length;
  framlength  = PaketUpMsg(databuffer,AmpCmdCard,&framlength);
  
  
  ampframe  = (stampphydef*)databuffer;
  ampframe->msg.addr.address1 = CabAddr;    
  ampframe->msg.addr.address2 = 0;
  ampframe->msg.addr.address3 = 0;
  
  SetFrame(databuffer,&framlength);
  
  if(MainFlag)  
  {
    AMPPro.buffer.WaitAck.Pc=1;   
    PCnet_Send(databuffer,framlength);    
  }
  else
  {
    AMPPro.buffer.WaitAck.Cab=1;   
    Cabinet_Send(databuffer,framlength);    
  }
  return;
}








 
void RequestServer(void)
{    
  
    if(AMPPro.Req.PLon)    
    {      
      ((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0C00))->BSRR = ((u16)0x0002);
      AMPPro.Req.PLon=0;
      AMPPro.Flag.LayPownOn=1;
    }
    else if(AMPPro.Req.PLoff)
    {
      ((GPIO_TypeDef *) ((((u32)0x40000000) + 0x10000) + 0x0C00))->BRR = ((u16)0x0002);
      AMPPro.Req.PLoff=0;
      AMPPro.Flag.LayPownOn=0;
    }













}








 
void LockStatusUpdata(eucmddef Cmd,eLockStsdef std)
{
  unsigned char databuffer[32]={0};
  unsigned short framlength = 0;  
  unsigned short datalength = 2;  
  stampphydef* ampframe=0;
  
  databuffer[0] = AmpStsLock;
  databuffer[1] = std;
  
  framlength  = PaketUpMsg(databuffer,Cmd,&datalength); 
  
  ampframe  = (stampphydef*)databuffer;
  
  ampframe->msg.addr.address1 = CabAddr;  
  ampframe->msg.addr.address2 = 0;
  ampframe->msg.addr.address3 = 0;
  
  framlength  = SetFrame(databuffer,&framlength);
  
  if(MainFlag)  
  {
    AMPPro.buffer.WaitAck.Pc=1;   
    PCnet_Send(databuffer,framlength);    
  }
  else
  {
    AMPPro.buffer.WaitAck.Cab=1;   
    Cabinet_Send(databuffer,framlength);    
  }
}








 
void CommTimeOutUpdata(enCCPortDef Port,stampaddrdef address)
{
  unsigned char databuffer[32]={0};
  unsigned short framlength = 0;  
  unsigned short datalength = 2;  
  stampphydef* ampframe=0;
  
  databuffer[0] = AmpStsComm;       
  databuffer[1] = AmpCommTimeOut;   
  
  framlength  = PaketUpMsg(databuffer,AmpCmdSta,&datalength); 
  
  ampframe  = (stampphydef*)databuffer;
  
  ampframe->msg.addr.address1 = address.address1;  
  ampframe->msg.addr.address2 = address.address2;
  ampframe->msg.addr.address3 = address.address3;
  
  switch(Port)
  {
    case  NonPort   : return ;   
    case  PcPort    : return;    
      break;
    case  CabPort   :
                      ampframe->msg.addr.address2 = 0;
                      ampframe->msg.addr.address3 = 0;
      break;
    case  LayPort   :
      break;
    case  CardPort  :
                      ampframe->msg.addr.address2 = 0;
                      ampframe->msg.addr.address3 = 0;
      break;
    default :return;      
  }
  
  framlength  = SetFrame(databuffer,&framlength);
  
  if(MainFlag)  
  {
    AMPPro.buffer.WaitAck.Pc=1;   
    PCnet_Send(databuffer,framlength);    
  }
  else
  {
    AMPPro.buffer.WaitAck.Cab=1;   
    Cabinet_Send(databuffer,framlength);    
  }
}


