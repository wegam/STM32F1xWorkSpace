#line 1 "..\\..\\Driver\\Tool\\LinkedList.C"
















 
#line 1 "..\\..\\Driver\\Tool\\LinkedList.H"




typedef struct _LINK_NODE
{	
	unsigned short 	DataLen;			
	unsigned short  Serial;				
	char 						*DataAddr;	
  struct _LINK_NODE* PrevNode;	
	struct _LINK_NODE* NextNode;	
}LINK_NODE;






















static LINK_NODE *CreateNode(char* DataAddr,unsigned long DataLength);										
static LINK_NODE *InsertNode(LINK_NODE* HeadNODEx,LINK_NODE* NewNODEx);									
static LINK_NODE *AddNode(LINK_NODE* EndNODEx,LINK_NODE* NewNODEx);											
static LINK_NODE *DeleteNode(LINK_NODE* DelNODEx);																			
static LINK_NODE *GetEndNode(LINK_NODE* DelNODEx);																				
LINK_NODE *FindData(LINK_NODE	*HeadNODE,char* DataAddr,unsigned long DataLength);	

unsigned long GetListLength(LINK_NODE* HeadNODEx);																		

unsigned short FIFO_IN  (LINK_NODE	**EndNode,char* SaveAddr,unsigned short SaveLength);	
unsigned short FIFO_OUT	(LINK_NODE	**DATAx,char* ReadAddr);										    
LINK_NODE* FIFO_DEL	(LINK_NODE	*DelNode);	

unsigned long LIFO_IN		(LINK_NODE	*LISTx,char* SaveAddr,unsigned long SaveLength);	
LINK_NODE* LIFO_OUT	(LINK_NODE	*LISTx,char* ReadAddr);														

unsigned long LinkListTest(LINK_NODE	*LISTx,char* DataAddr,unsigned long SaveLength,unsigned char CMD);		





#line 19 "..\\..\\Driver\\Tool\\LinkedList.C"

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



 

#line 21 "..\\..\\Driver\\Tool\\LinkedList.C"
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



 

#line 22 "..\\..\\Driver\\Tool\\LinkedList.C"
#line 1 "..\\..\\Library\\C\\stdarg.h"
 
 
 





 










#line 27 "..\\..\\Library\\C\\stdarg.h"








 

 
 
#line 57 "..\\..\\Library\\C\\stdarg.h"
    typedef struct __va_list { void *__ap; } va_list;

   






 


   










 


   















 




   

 


   




 



   





 







#line 138 "..\\..\\Library\\C\\stdarg.h"



#line 147 "..\\..\\Library\\C\\stdarg.h"

 

#line 23 "..\\..\\Driver\\Tool\\LinkedList.C"
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





 
#line 24 "..\\..\\Driver\\Tool\\LinkedList.C"








static LINK_NODE *CreateNode(char* DataAddr,unsigned long DataLength)
{
	LINK_NODE *NewNode; 		
  char *Addr;
	if(DataLength==0	||	DataAddr==0)				
	{
		return	0;
	}
	
	NewNode = (LINK_NODE *) malloc (sizeof(LINK_NODE)); 	

	if (0 == NewNode)	
	{
		return 0;				
	}
	else									
	{
		
		Addr	= (char *) malloc (DataLength);			
		if(0	== Addr)	
		{
			free(NewNode);								
			return 0;									
		}
    NewNode->DataAddr = Addr;
		NewNode->NextNode = 0;
		NewNode->DataLen  = DataLength;											
		memcpy(NewNode->DataAddr,DataAddr,DataLength);		
	}
	return	NewNode;					
}






static LINK_NODE *InsertNode(LINK_NODE* HeadNODEx,LINK_NODE* NewNODEx)
{
	if(HeadNODEx==0)						
	{
		NewNODEx->PrevNode	=	0;	
		NewNODEx->NextNode	=	0;	
		return	NewNODEx;
	}
	
	else													
	{		
		if(HeadNODEx->PrevNode	==0)			
		{
			NewNODEx->PrevNode	=	0;				
			NewNODEx->NextNode	=	HeadNODEx;	
			HeadNODEx->PrevNode	=	NewNODEx;		
		}
		else																											
		{
			NewNODEx->PrevNode	=	HeadNODEx->PrevNode->NextNode;		
			NewNODEx->NextNode	=	HeadNODEx;												
			HeadNODEx->PrevNode->NextNode=NewNODEx;									
			HeadNODEx->PrevNode=NewNODEx;														
		}
		return	NewNODEx;
	}
}






static LINK_NODE *AddNode(LINK_NODE* EndNODEx,LINK_NODE* NewNODEx)
{
	if(EndNODEx==0)						
	{
		NewNODEx->PrevNode	=	0;	
		NewNODEx->NextNode	=	0;	
		EndNODEx	=	NewNODEx;				
		return	NewNODEx;
	}
	
	else													
	{
    LINK_NODE* TempNODEx  = EndNODEx;   
    TempNODEx->NextNode   = NewNODEx;   
    NewNODEx ->PrevNode   = EndNODEx;   
    
    NewNODEx->NextNode    = 0;       
    EndNODEx =  NewNODEx;               
		return	EndNODEx;
	}
}






static LINK_NODE *DeleteNode(LINK_NODE* DelNODEx)
{
	LINK_NODE* pNODE;
	
	pNODE = DelNODEx;
	
	if(pNODE	==	0)
	{
		return 0;
	}


	
	if(DelNODEx->PrevNode==0)			
	{
		if(DelNODEx->NextNode==0)										
		{
      free(DelNODEx->DataAddr);									  
			free(DelNODEx);															
			DelNODEx	=	0;													
		}
		else																				
		{
			DelNODEx	=	DelNODEx->NextNode;				    
			DelNODEx->PrevNode		=	0;	            
      free(pNODE->DataAddr);									  
			free(pNODE);															
		}
	}
	else													
	{
		if(DelNODEx->NextNode==0)										
		{
			DelNODEx->PrevNode->NextNode	=	0;		
			DelNODEx	=	DelNODEx->PrevNode;			
      free(pNODE->DataAddr);									  
			free(pNODE);															
		}
		else											
		{
      DelNODEx->PrevNode->NextNode=DelNODEx->NextNode;	
			DelNODEx->NextNode->PrevNode=DelNODEx->PrevNode;	
      DelNODEx  = DelNODEx->PrevNode;			              
      free(pNODE->DataAddr);									  
			free(pNODE);															
		}
	}
	return DelNODEx;						
}






static LINK_NODE *GetEndNode(LINK_NODE* DelNODEx)
{
	LINK_NODE* pNODE;
	pNODE	=	DelNODEx;
	if(pNODE	==	0)
	{
		return 0;
	}
	if(pNODE->NextNode	==0)
	{
		return pNODE;
	}
	else
	{
		GetEndNode(pNODE->NextNode);
	}
	return pNODE;
}






LINK_NODE *FindData(LINK_NODE	*HeadNODE,char* DataAddr,unsigned long DataLength)
{
	unsigned short i	=0;
	LINK_NODE* TempNODEx	=	0;
	
	if(HeadNODE	==	0)   
	{
		return 0;
	}
	TempNODEx	=	HeadNODE;
	for(i=0;i<0xFF;i++)
	{
		if(TempNODEx  ==	0)
		{
			return 0;
		}
		else if(memcmp(TempNODEx->DataAddr,DataAddr,DataLength)	==	0)				
		{
			return	TempNODEx;
		}
		else
		{
			TempNODEx	=	TempNODEx->NextNode;
		}
	}
	return 0;
}






unsigned long GetListLength(LINK_NODE* HeadNODEx)
{
	if(HeadNODEx==0)			
	{
		return 0;					
	}
	return	1+GetListLength(HeadNODEx->NextNode);
}








unsigned short  FIFO_IN(LINK_NODE	**EndNode,char* SaveAddr,unsigned short SaveLength)
{
	
	LINK_NODE *NewNode = 0; 											
  LINK_NODE *TempNode = *EndNode; 							  
	
	NewNode	=	CreateNode(SaveAddr,SaveLength);			
	
	if(NewNode==0)		
	{
		return 0;	        
	}
  
  if(0 ==  TempNode)
  {
    NewNode->NextNode = 0;
    NewNode->PrevNode = 0;
    *EndNode = NewNode;
    return  SaveLength;
  }
  else
  {
    
    LINK_NODE*  TempNode  = *EndNode;
    unsigned char i=0;
    for(i=0;i<0xFF;i++)
    {
      if(0 ==  TempNode->NextNode)
      {
        break;
      }
      TempNode  = TempNode->NextNode;
    }
    TempNode->NextNode  = NewNode;
    NewNode->PrevNode   = TempNode;
    NewNode->NextNode   = 0;
    *EndNode = NewNode;
  }
	
	
	return	SaveLength;
}







unsigned short FIFO_OUT(LINK_NODE	**HeadNode,char* ReadAddr)
{
  LINK_NODE *TempNode = *HeadNode; 							  
  unsigned short DataLen = 0;			
	
	if(TempNode==0)							
	{
		return 0;												  
	}
	
	else		
	{
    
    unsigned char i = 0;
    for(i=0;i<0xFF;i++)
    {
      if(0 ==  TempNode->PrevNode) 
      {
        break;
      }
      TempNode  = TempNode->PrevNode;
    }
		
    DataLen = TempNode->DataLen;
    if(DataLen)
    {
      if(0 !=  ReadAddr)
      {
        free(ReadAddr);        
      }
      ReadAddr  = (char*)malloc((unsigned int)DataLen);
      if(0 ==  ReadAddr)   
      {
        return 0;
      }
      memcpy(ReadAddr,TempNode->DataAddr,TempNode->DataLen);	          
    }
    
    if(0 !=  TempNode->NextNode)                           
    {
      TempNode ->NextNode->PrevNode = 0;
      *HeadNode  = TempNode  ->NextNode;
      free(TempNode->DataAddr);                               
      free(TempNode);                                         
    }
    else
    {
      free(TempNode->DataAddr);                               
      free(TempNode);                                         
      *HeadNode  = 0;
    }
		return DataLen;					
	}
}






LINK_NODE* FIFO_DEL(LINK_NODE	*DelNode)
{
	if(0 ==  DelNode)
	{
		return 0;
	}
  if(0 ==  DelNode->PrevNode)    
  {
    if(0 ==  DelNode->NextNode)  
    {
      free(DelNode->DataAddr);      
      free(DelNode);                
      DelNode = 0;
    }
    else
    {
      LINK_NODE* pNODE	=	DelNode;
      DelNode = DelNode->NextNode;
      free(pNODE->DataAddr);        
      free(pNODE);                  
    }
  }
  
  else                              
  {
    if(0 ==  DelNode->NextNode)  
    {
      LINK_NODE* pNODE	=	DelNode;
      DelNode = DelNode->NextNode;
      DelNode->PrevNode = 0;
      free(pNODE->DataAddr);        
      free(pNODE);                  
    }
    else
    {
      LINK_NODE* pNODE	=	DelNode;
      DelNode->PrevNode->NextNode = DelNode->NextNode;
      DelNode->NextNode->PrevNode = DelNode->PrevNode;
      DelNode = DelNode->PrevNode;
      free(pNODE->DataAddr);        
      free(pNODE);                  
    }
  }
	return DelNode;	
}







unsigned long LIFO_IN(LINK_NODE	*HeadNode,char* SaveAddr,unsigned long SaveLength)
{
	LINK_NODE *NewNode = 0; 											

	NewNode	=	CreateNode(SaveAddr,SaveLength);		  
						
	if(NewNode==0)		
	{
		return 0;					
	}
  
  if(0 ==  HeadNode)                     
  {
    NewNode->NextNode = 0;
    NewNode->PrevNode = 0;
    HeadNode  = NewNode;
  }
  else
  {
    LINK_NODE*  TempNode  = HeadNode;
    unsigned char i=0;
    for(i=0;i<0xFF;i++)
    {
      if(0 ==  TempNode->PrevNode)
      {
        break;
      }
      TempNode  = TempNode->PrevNode;
    }
    NewNode->NextNode = TempNode;
    NewNode->PrevNode = 0;
    HeadNode  = NewNode;                    
    
  }
	return	SaveLength;
}







LINK_NODE* LIFO_OUT(LINK_NODE	*EndNode,char* ReadAddr)
{
	
	if(EndNode==0)							
	{
		return 0;														
	}
	
	else		
	{
    LINK_NODE*  TempNode  = EndNode;
    do
    {
      TempNode  = TempNode->NextNode;
    }
    while(0 ==  TempNode->NextNode);
    TempNode->PrevNode->NextNode  = 0;
    EndNode = TempNode->PrevNode;
    memcpy(ReadAddr,TempNode->DataAddr,TempNode->DataLen);                
    free(TempNode->DataAddr);                               
    free(TempNode);                                         
    
		return EndNode;																			    
	}
}






unsigned long LinkListTest(LINK_NODE	*LISTx,char* DataAddr,unsigned long SaveLength,unsigned char CMD)
{
	unsigned long	RevLength	=	0;
















































}



