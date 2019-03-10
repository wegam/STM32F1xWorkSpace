#line 1 "..\\..\\Driver\\Protocol\\AMP_PHY.C"
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




#line 2 "..\\..\\Driver\\Protocol\\AMP_PHY.C"


#line 1 "..\\..\\Examples\\WOW\\AMP_CABV11.H"



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

#line 5 "..\\..\\Driver\\Protocol\\AMP_PHY.C"

#line 1 "..\\..\\Driver\\Tool\\CRC.H"














unsigned short CRC16_CCITT(unsigned char *puchMsg, unsigned int usDataLen);				
unsigned short CRC16_CCITT_FALSE(unsigned char *puchMsg, unsigned int usDataLen);	
unsigned short CRC16_XMODEM(unsigned char *puchMsg, unsigned int usDataLen);				
unsigned short CRC16_X25(unsigned char *puchMsg, unsigned int usDataLen);					
unsigned short CRC16_MODBUS(unsigned char *puchMsg, unsigned int usDataLen);				
unsigned short CRC16_IBM(unsigned char *puchMsg, unsigned int usDataLen);					
unsigned short CRC16_MAXIM(unsigned char *puchMsg, unsigned int usDataLen);				
unsigned short CRC16_USB(unsigned char *puchMsg, unsigned int usDataLen);					





#line 7 "..\\..\\Driver\\Protocol\\AMP_PHY.C"

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



 

#line 9 "..\\..\\Driver\\Protocol\\AMP_PHY.C"
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



 

#line 10 "..\\..\\Driver\\Protocol\\AMP_PHY.C"
#line 1 "..\\..\\Library\\C\\stdarg.h"
 
 
 





 










#line 27 "..\\..\\Library\\C\\stdarg.h"








 

 
 
#line 57 "..\\..\\Library\\C\\stdarg.h"
    typedef struct __va_list { void *__ap; } va_list;

   






 


   










 


   















 




   

 


   




 



   





 







#line 138 "..\\..\\Library\\C\\stdarg.h"



#line 147 "..\\..\\Library\\C\\stdarg.h"

 

#line 11 "..\\..\\Driver\\Protocol\\AMP_PHY.C"
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





 
#line 12 "..\\..\\Driver\\Protocol\\AMP_PHY.C"

#line 1 "D:\\Program Files (x86)\\MDK\\CORE\\ARM\\ARMCC\\Bin\\..\\include\\stdbool.h"
 






 





#line 25 "D:\\Program Files (x86)\\MDK\\CORE\\ARM\\ARMCC\\Bin\\..\\include\\stdbool.h"



#line 14 "..\\..\\Driver\\Protocol\\AMP_PHY.C"

stampphydef* phy  = 0;
unsigned	char AmpBaket[133]={0};
stAMPProdef   AMPPro;


unsigned  char  ackupfarme[7]=
{
  0x7E,   
  0x02,   
  0x81,   
  0x00,   
  0xB0,   
  0x50,   
  0x7F    
};
unsigned  char  ackdownfarme[7]=
{
  0x7E,
  0x02,
  0x01,
  0x00,
  0xD1,
  0x90,
  0x7F
};









 
unsigned char API_AmpCheckFrame(unsigned char* pbuffer,unsigned short* length)
{
  unsigned  char  Cmd         = 0;
  unsigned  char* headaddr    = 0;
  unsigned  char* endaddr     = 0;
  unsigned short	HeadCodeValidLength	=	*length;    
  unsigned short	EndCodeValidLength	=	*length;    
  unsigned short	FrameValidLength	  =	*length;    
  unsigned short	DataValidLength	    =	*length;    
  
  stampphydef* ampframe;
  
  
  if(0  ==  pbuffer)
  {
    goto ExitAmpCheckFrame;   
  }
  if(FrameValidLength<7)  
  {
    goto ExitAmpCheckFrame;   
  }  
  FrameGetHeadCodeAddr:
  
  headaddr	=	(unsigned char*)memchr(pbuffer,(unsigned char)0x7E,HeadCodeValidLength);   
  if(0==headaddr)
  {
    goto ExitAmpCheckFrame;   
  }
  
  
  
  
  DataValidLength  = FrameValidLength-((unsigned long)headaddr-(unsigned long)pbuffer); 
  if(DataValidLength<7)
  {
    goto ExitAmpCheckFrame;   
  }
  
  EndCodeValidLength  = DataValidLength-1; 
  endaddr=&headaddr[1];        
  
  FrameGetEndCodeAddr:
  
  endaddr		=	(unsigned char*)memchr(endaddr,(unsigned char)0x7F,EndCodeValidLength);   
  if(0==endaddr)
  {
    goto ExitAmpCheckFrame;   
  }
  
  else
  {
    FrameValidLength  = (unsigned long)endaddr-(unsigned long)headaddr+1;
    
    if(7>FrameValidLength)      
    {
      if(7<EndCodeValidLength)  
      {
        endaddr=&endaddr[1];        
        EndCodeValidLength=EndCodeValidLength-FrameValidLength;      
        goto FrameGetEndCodeAddr;   
      }
      else
      {
        goto ExitAmpCheckFrame;   
      }
    }
    
    else if(7==FrameValidLength)  
    {
      if(AmpCrc16Check(headaddr,&FrameValidLength))  
      {
        pbuffer = headaddr;
        return DataValidLength;
      }
      else    
      {
        endaddr=&endaddr[1];        
        EndCodeValidLength=EndCodeValidLength-FrameValidLength;      
        goto FrameGetEndCodeAddr;   
      }
    }
    else
    {
    }
    


    if(AmpCmdAck  ==  ampframe->msg.cmd.cmd)  
    {
    }
    if(AmpCrc16Check(headaddr,&FrameValidLength))
    {
      *length = FrameValidLength;
    }
    else
    {
      pbuffer = &headaddr[1];
      FrameValidLength = FrameValidLength-1;
      goto FrameGetEndCodeAddr;
    }    
  }
  ExitAmpCheckFrame:  
  return  0;
}








 
unsigned short getframe(unsigned char* pbuffer,unsigned short* length)
{  
  unsigned  char* headaddr  = 0;
  unsigned  short farmelength = 0;
  headaddr  = getheadaddr(pbuffer,length);
  if(0==headaddr)
  {
    return  0;
  }
  pbuffer = headaddr;
  farmelength = *length;
  return  farmelength;
}








 
unsigned char* getheadaddr(unsigned char* pbuffer,unsigned short* length)
{
  unsigned  char* headaddr  = 0;
  unsigned  char* endaddr   = 0;
  
  unsigned short	ValidLength	=	*length;

  
  if(0  ==  pbuffer)
  {
    return 0;
  }
  startcheckdata:
  headaddr	=	(unsigned char*)memchr(pbuffer,(unsigned char)0x7E,ValidLength);
	endaddr		=	(unsigned char*)memchr(headaddr,(unsigned char)0x7F,ValidLength);
  ValidLength = ValidLength-((unsigned long)headaddr-(unsigned long)pbuffer);
  if(ValidLength<7)   
  {
    *length = 0;
    return  0;
  }
  if((0==headaddr)||(0==endaddr))
  {
    *length = 0;
    return  0;
  }
  else
  {    
    if(AmpCrc16Check(headaddr,&ValidLength))
    {
      *length = ValidLength;
      return headaddr;
    }
    else
    {
      pbuffer = &headaddr[1];
      ValidLength = ValidLength-1;
      goto startcheckdata;
    }    
  }

}









 
unsigned char AmpCrc16Check(unsigned char* pframe,unsigned short* length)
{  
  unsigned  short msglen  = 0;  
  unsigned  short	ValidLength	=	*length; 
  unsigned  short crc16; 
  
  if(0  ==  pframe)
  {
    return 0;
  }
  phy  = (stampphydef*)pframe;
  
  msglen  = phy->msg.length;
  if(2==msglen) 
  {
    phy->crc16.crcl = pframe[4];
    phy->crc16.crch = pframe[5];
  }
  else
  {
    if(msglen>ValidLength)     
      return  0;
    else if(msglen>2)     
      if(msglen+5>ValidLength) 
        return 0;
    phy->crc16.crcl = pframe[msglen+2];
    phy->crc16.crch = pframe[msglen+3];
  }
  crc16 = CRC16_MODBUS(&pframe[1],msglen+1);
  if(((crc16&0xFF)==phy->crc16.crcl)&&(((crc16>>8)&0xFF)==phy->crc16.crch))
  {
    *length = msglen+5;
    return 1;
  }
  return 0;
}








 
unsigned short SetFrame(unsigned char* pframe,unsigned short* length)
{  
  unsigned short msglen = 0;    
  unsigned short datalen = 0;   
  unsigned short crclen = 0;    
  unsigned short crc16 = 0;     
  
  stampphydef* ampframe;
  
  ampframe  = (stampphydef*)pframe;
  msglen  = ampframe->msg.length;
  datalen = msglen-4;   
  crclen  = msglen+1;   
  crc16 = CRC16_MODBUS(&ampframe->msg.length,crclen);
  memcpy(&ampframe->msg.data[datalen],&crc16,2);       
  ampframe->msg.data[datalen+2]  = (unsigned char)0x7F;      
  return *length;
}









 
unsigned	short PaketUpMsg(unsigned	char* pbuffer,eucmddef cmd,unsigned	short* length)
{
  unsigned  short framlength  = 0;  
  unsigned  char* temp  = 0;

  stampphydef ampframe;
  
  framlength  = *length+4;  
  temp  = (unsigned  char*)&ampframe.msg.cmd;   
  *temp = (unsigned  char)cmd;
  ampframe.msg.cmd.dir  = 1;      
  
  ampframe.head = (unsigned char)0x7E;
  ampframe.msg.length = framlength;           
  memcpy(ampframe.msg.data,pbuffer,*length);  
  
  framlength  = framlength+5;   
  
  memcpy(pbuffer,&ampframe,framlength);   
  *length = framlength;   
  return framlength;
}








 
unsigned	short PaketDownMsg(unsigned	char* pbuffer,eucmddef cmd,unsigned	short* length)
{
  unsigned  short framlength  = 0;  
  unsigned  char* temp  = 0;

  stampphydef ampframe;
  
  framlength  = *length+4;  
  temp  = (unsigned  char*)&ampframe.msg.cmd;   
  *temp = (unsigned  char)cmd;
  ampframe.msg.cmd.dir  = 0;      
  
  ampframe.head = (unsigned char)0x7E;
  ampframe.msg.length = framlength;           
  memcpy(ampframe.msg.data,pbuffer,*length);  
  
  framlength  = framlength+5;   
  
  memcpy(pbuffer,&ampframe,framlength);   
  *length = framlength;   
  return framlength;
}








 
unsigned char ackcheck(unsigned char* pframe)
{ 
  unsigned  char Cmd  = 0;
  stampphydef *ampframe;
  
  if(0 ==  pframe)
    return  0;
  
  ampframe = (stampphydef*)pframe;
  Cmd = (unsigned  char)ampframe->msg.cmd.cmd;
  Cmd&=0x3F;            
  
  if(AmpCmdAck  ==  Cmd)
    return  1;        
  return 0;
}








 
unsigned char addr1check(unsigned char* pframe,unsigned char addr1)
{ 
  unsigned addrck=0;
  if(0 ==  pframe)
    return  0;
  phy = (stampphydef*)pframe;
  addrck  = phy->msg.addr.address1;
  if((addrck==addr1)||(addrck==0xFF))
    return  1;
  return 0;
}








 
unsigned char addr2check(unsigned char* pframe,unsigned char addr2)
{ 
  unsigned addrck=0;
  if(0 ==  pframe)
    return  0;
  phy = (stampphydef*)pframe;
  addrck  = phy->msg.addr.address2;
  if((addrck==addr2)||(addrck==0xFF))
    return  1;
  return 0;
}








 
unsigned char addr3check(unsigned char* pframe,unsigned char addr3)
{ 
  unsigned addrck=0;
  if(0 ==  pframe)
    return  0;
  phy = (stampphydef*)pframe;
  addrck  = phy->msg.addr.address3;
  if((addrck==addr3)||(addrck==0xFF))
    return  1;
  return 0;
}









 
unsigned short sendbuffer(unsigned char* pbuffer,unsigned short length)
{
  return  0;
}








 
unsigned short SendTimeOut(enCCPortDef Port)
{
  unsigned  char  i  = 0;
  stTxdef* Txd  = 0;
  unsigned  char*  ReSendCount;      
  unsigned  short*  SendTime=0;
  stampphydef* ampframe=0;
  
  switch(Port)
  {
    case  NonPort   : return 0;   
    case  PcPort    : Txd=AMPPro.buffer.PcTx;    
      break;
    case  CabPort   : Txd=AMPPro.buffer.CabTx;   
      break;
    case  LayPort   : Txd=AMPPro.buffer.LayTx;   
      break;
    case  CardPort  : Txd=AMPPro.buffer.CardTx;  
      break;
    default :return 0;      
  }
  for(i=0;i<20;i++)
  {
    if(1==Txd[i].arry>0)  
    {
      ampframe  = (stampphydef*)Txd[i].data;
      CommTimeOutUpdata(Port,ampframe->msg.addr);   
      Releas_OneBuffer(Port);     
    }
  }
  return  0;
}








 
unsigned short Releas_OneBuffer(enCCPortDef Port)
{
  unsigned  char  i  = 0;
  stTxdef* Txd  = 0;
  unsigned  char*  ReSendCount;      
  unsigned  short*  SendTime=0;
  
  switch(Port)
  {
    case  NonPort   : return 0;   
    case  PcPort    : ReSendCount = &AMPPro.ReSend.PcCount;
                      Txd=AMPPro.buffer.PcTx;    
                      SendTime  = &AMPPro.Time.PcSendTime;
      break;
    case  CabPort   : ReSendCount = &AMPPro.ReSend.CabCount;
                      Txd=AMPPro.buffer.CabTx;   
                      SendTime  = &AMPPro.Time.CabSendTime;
      break;
    case  LayPort   : ReSendCount = &AMPPro.ReSend.LayCount;
                      Txd=AMPPro.buffer.LayTx;   
                      SendTime  = &AMPPro.Time.LaySendTime;
      break;
    case  CardPort  : ReSendCount = &AMPPro.ReSend.CardCount;
                      Txd=AMPPro.buffer.CardTx;  
                      SendTime  = &AMPPro.Time.CardSendTime;
      break;
    default :return 0;      
  }
  for(i=0;i<20;i++)
  {
    if(Txd[i].arry>0)
    {
      Txd[i].arry--;
      *SendTime  = 3;   
      *ReSendCount  = 0;
    }
  }
  return  0;
}








 
void ackFrame(enCCPortDef Port,unsigned char dir)
{
  switch(Port)
  {
    case  NonPort   : return;   
    case  PcPort    : AMPPro.AckQ.PcAck     = 1;
                      AMPPro.AckQ.PcDir     = dir;
                      AMPPro.Time.PcSendTime=3;   
      break;
    case  CabPort   : AMPPro.AckQ.CabAck    = 1;
                      AMPPro.AckQ.CabDir    = dir;
                      AMPPro.Time.CabSendTime=3;   
      break;
    case  LayPort   : AMPPro.AckQ.LayAck    = 1;
                      AMPPro.AckQ.LayDir    = dir;
                      AMPPro.Time.LaySendTime=3;   
      break;
    case  CardPort  : AMPPro.AckQ.CardAck   = 1;
                      AMPPro.AckQ.CardDir   = dir;
                      AMPPro.Time.CardSendTime=3;   
      break;
    default :return;      
  }
}








 
void Send_Server(void)
{
    
    if(0  ==  AMPPro.Time.PcSendTime)
    {
      Check_SendBuff(PcPort);
    }
    
    if(0  ==  AMPPro.Time.CabSendTime)
    {
      Check_SendBuff(CabPort);
    }
    
    if(0  ==  AMPPro.Time.LaySendTime)
    {
      Check_SendBuff(LayPort);
    }
    
    if(0  ==  AMPPro.Time.CardSendTime)
    {
      Check_SendBuff(CardPort);
    }
}








 
unsigned short Check_SendBuff(enCCPortDef Port)
{ 
  unsigned  char  i  = 0;
  unsigned  short  SendLen  = 0;
  unsigned  char  ackflag =0;
  unsigned  char  ackdir =0;
  unsigned  char* SendAddr = 0;  
  unsigned  char*  ReSendCount;      
  
  unsigned  short*  SendTime=0;
  
  stTxdef* Txd  = 0;
  

  
  switch(Port)
  {
    case  NonPort   : return 0;   
    case  PcPort    : ReSendCount = &AMPPro.ReSend.PcCount;
                      Txd=AMPPro.buffer.PcTx;    
                      SendTime  = &AMPPro.Time.PcSendTime;
                      ackflag = AMPPro.AckQ.PcAck;
                      ackdir  = AMPPro.AckQ.PcDir;
      break;
    case  CabPort   : ReSendCount = &AMPPro.ReSend.CabCount;
                      Txd=AMPPro.buffer.CabTx;   
                      SendTime  = &AMPPro.Time.CabSendTime;
                      ackflag = AMPPro.AckQ.CabAck;
                      ackdir  = AMPPro.AckQ.CabDir;
      break;
    case  LayPort   : ReSendCount = &AMPPro.ReSend.LayCount;
                      Txd=AMPPro.buffer.LayTx;   
                      SendTime  = &AMPPro.Time.LaySendTime;
                      ackflag = AMPPro.AckQ.LayAck;
                      ackdir  = AMPPro.AckQ.LayDir;
      break;
    case  CardPort  : ReSendCount = &AMPPro.ReSend.CardCount;
                      Txd=AMPPro.buffer.CardTx;  
                      SendTime  = &AMPPro.Time.CardSendTime;
                      ackflag = 0;
      break;
    default :return 0;      
  }
  if(ackflag) 
  {
    if(ackdir)  
      SendLen = HW_SendBuff(Port,ackupfarme,sizeof(ackupfarme));   
    else
      SendLen = HW_SendBuff(Port,ackdownfarme,sizeof(ackdownfarme));   
    if(SendLen)   
    {
      switch(Port)
      {
        case  NonPort   : return 0;   
        case  PcPort    : AMPPro.AckQ.PcAck = 0;
          break;
        case  CabPort   : AMPPro.AckQ.CabAck = 0;
          break;
        case  LayPort   : AMPPro.AckQ.LayAck = 0;
          break;
        case  CardPort  : AMPPro.AckQ.CardAck  = 0;
          break;
        default :return 0;      
      }
    }
    *SendTime  = 10;
    return  0;
  }
  if(*SendTime>0)   
  {
    return  0;
  }
  
  
  for(i=0;i<20;i++)
  {
    if(1  ==  Txd[i].arry)
    {
      SendAddr  = Txd[i].data;    
      SendLen   = Txd[i].size;    
      break;
    }
  }
  
  if(0!= SendAddr)
  {
    SendLen = HW_SendBuff(Port,SendAddr,SendLen);   
    if(SendLen)   
    {
      *ReSendCount +=1;
      *SendTime = 50;
      
      if(*ReSendCount>=5) 
      {
        
        SendTimeOut(Port);      
        
        *ReSendCount  = 0;      
      }
      if(PcPort ==  Port) 
      {
        Releas_OneBuffer(Port);
        *ReSendCount  = 0;      
      }
    }
    else
    {
      *SendTime = 50;
    }
    return  SendLen;
  }
  return  0;
}








 
void Send_ConnectErr(enCCPortDef Port,unsigned char* pBuffer,unsigned short length)
{

}









 
unsigned short AddSendBuffer(enCCPortDef Port,unsigned char* pBuffer,unsigned short length)
{
  unsigned  char  i  = 0;
  unsigned  char  lastarry  = 0;
  
  stTxdef* Txd  = 0;
  
  switch(Port)
  {
    case  NonPort   : return 0;   
    case  PcPort    : Txd=AMPPro.buffer.PcTx;    
      break;
    case  CabPort   : Txd=AMPPro.buffer.CabTx;   
      break;
    case  LayPort   : Txd=AMPPro.buffer.LayTx;   
      break;
    case  CardPort  : Txd=AMPPro.buffer.CardTx;  
      break;
    default :return 0;      
  }
  
  for(i=0;i<20;i++)
  {
    if(Txd[i].arry>lastarry)
    {
      lastarry  = Txd[i].arry;
      
      if(0  ==  memcmp(Txd[i].data,pBuffer,length)) 
      {
        if(length ==  Txd[i].size)    
          return  length;
      }
    }
  }
  if(lastarry>=20)  
    return 0;     
  lastarry=lastarry+1;      
  
  for(i=0;i<20;i++)
  {
    if(0  ==  Txd[i].arry)  
    {
      memcpy(Txd[i].data,pBuffer,length);
      Txd[i].arry = lastarry;             
      Txd[i].size = length; 
      return  length;
    }
  }
  return  0;
}



