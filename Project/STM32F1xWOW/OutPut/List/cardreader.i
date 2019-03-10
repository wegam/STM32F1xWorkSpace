#line 1 "..\\..\\Driver\\Components\\SCR\\CardReader.c"
#line 1 "..\\..\\Driver\\Components\\INC\\CardReader.h"





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






 
#line 7 "..\\..\\Driver\\Components\\INC\\CardReader.h"



typedef enum	_eFWS9UsHead			
{
	eFWS9UsOutHead		=	0xE1,		
	eFWS9UsInHead			=	0xD2,		
}eFWS9UsHeadDef;
typedef enum	_eFWS9UsEnd				
{
	eFWS9UsOutEnd				=	0x1E,		
	eFWS9UsInEnd				=	0x2D,		
}eFWS9UsEndDef;
typedef enum	_eFWS9Cmd					
{
	eFWS9CmdReadBlock		=	0x24,		
	eFWS9CmdWriteBlock	=	0x25,		
	eFWS9CmdSetBlock		=	0x44,		
}eFWS9CmdDef;
typedef enum	_eFWS9ErrCode			
{
	eFWS9NoErr					=	0x00,			
	eFWS9NoCard					=	0x01,			
}eFWS9ErrCodeDef;

typedef enum	_eFWS9KeyType			
{
	eKEYA				=	0x60,			
	eKEYB				=	0x61,			
}eFWS9KeyDef;



typedef	struct	_eFWS9CRC16
{
	unsigned char CRC_H;			
	unsigned char CRC_L;			
}eFWS9CRC16Def;

typedef	struct	_sFWS9RecData	
{
	eFWS9UsHeadDef	Head;				
	eFWS9CmdDef			Cmd;				
	eFWS9ErrCodeDef Err;				
	unsigned char 	data[16];		
	unsigned short 	CRC16;			
	eFWS9UsEndDef 	End;				
}sFWS9RecDataDef;

typedef	struct	_sFWS9CmdData		
{
	eFWS9UsHeadDef	Head;					
	eFWS9CmdDef			Cmd;					
	unsigned char 	Sector;				
	unsigned char 	Block;				
	eFWS9KeyDef			KeyType;			
	unsigned char 	PassWord[6];	
	unsigned short 	CRC16;				
	eFWS9UsEndDef 	End;					
}sFWS9CmdDataDef;


typedef	struct	_sFWS9WriteData		
{
	eFWS9UsHeadDef	Head;					
	eFWS9CmdDef			Cmd;					
	unsigned char 	Sector;				
	unsigned char 	Block;				
	eFWS9KeyDef			KeyType;			
	unsigned char 	PassWord[6];	
	unsigned char 	data[16];			
	unsigned short 	CRC16;				
	eFWS9UsEndDef 	End;					
}sFWS9WriteDataDef;

typedef	struct	_sFWS9SetArea		
{
	eFWS9UsHeadDef	Head;					
	eFWS9CmdDef			Cmd;					
	unsigned char 	Sector;				
	unsigned char 	Block;				
	eFWS9KeyDef			KeyType;			
	unsigned char 	PassWord[6];	
	unsigned short 	CRC16;				
	eFWS9UsEndDef 	End;					
}sFWS9SetAreaDef;


extern sFWS9RecDataDef		sFWS9RecData;			
extern sFWS9CmdDataDef		sFWS9ReadData;		
extern sFWS9CmdDataDef		sFWS9SetArea;			
extern sFWS9WriteDataDef	sFWS9WriteData;		

    


#line 2 "..\\..\\Driver\\Components\\SCR\\CardReader.c"


sFWS9RecDataDef		sFWS9RecData;			


sFWS9CmdDataDef	sFWS9ReadData	=			
{
	eFWS9UsOutHead,									
	eFWS9CmdReadBlock,							
	0x01,														
	0x01,														
	eKEYA,													
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,	
	0xFFFF,													
	eFWS9UsOutEnd										
};
sFWS9CmdDataDef	sFWS9SetArea	=			
{
	eFWS9UsOutHead,									
	eFWS9CmdSetBlock,								
	0x01,														
	0x01,														
	eKEYA,													
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,	
	0xFFFF,													
	eFWS9UsOutEnd										
};








 
void FWS9_Initialize(void)						
{
}



