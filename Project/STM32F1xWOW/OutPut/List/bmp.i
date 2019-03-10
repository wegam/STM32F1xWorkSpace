#line 1 "..\\..\\Driver\\Tool\\BMP.C"
















 
#line 1 "..\\..\\Driver\\Tool\\Image.H"



 

typedef struct _BMPInf
{
  
  
  unsigned char B;     
  unsigned char M;     
  
  unsigned long bfSize; 
  
  unsigned long bfRev0;       
  unsigned long bfOffset; 
  
  unsigned long   biSize;         
  unsigned long   biWidth;        
  unsigned long   biHeight;       
  unsigned short  biPlanes;       
  unsigned short  biBitCount;     
  unsigned long   biCompression;  
                                  
                                  
                                  
                                  
                                  
                                  
                                  
                                  
  unsigned long   biSizeImage;    
  unsigned long   biXPelsPerMater;    
  unsigned long   biYPelsPerMater;    
  unsigned long   biClrUsed;          
  unsigned long   biClrImportant;     
}BMPInftDef;





#line 19 "..\\..\\Driver\\Tool\\BMP.C"







