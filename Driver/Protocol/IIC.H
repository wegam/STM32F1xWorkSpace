#ifndef __IIC_H
#define __IIC_H



typedef struct
{
	//--------------------Ó²¼þ²ã
	void (*SDAHigh)(void);
	void (*SDALow)(void);
	void (*SCLHigh)(void);
	void (*SCLLow)(void);
	void (*SDAWriteEn)(void);
	void (*SDAReadEn)(void);	
	unsigned char (*SDAStd)(void);
	
	//--------------------Èí¼þ²ã
	void (*Start)(void);
	void (*Stop)(void);	
	void (*Ack)(void);
	void (*NAck)(void);
	unsigned char (*WaitAck)(void);
	
	unsigned char (*WriteOneByte)(unsigned	char data);
	unsigned short (*WriteBuffer)(unsigned char* pbuffer,unsigned	short length);
	
	unsigned char (*ReadOneByte)(void);
	unsigned short (*ReadBuffer)(unsigned	char* pbuffer,unsigned short readlength);
	
}I2CHWdef;


void IIC_Initialize(I2CHWdef* pInfo);


void IIC_Start(void);
void IIC_Stop(void);

void IIC_Ack(void);
void IIC_NAck(void);
unsigned char IIC_WaitAck(void);
	
unsigned char IIC_WriteOneByte(unsigned	char data);
unsigned short IIC_WriteBuffer(unsigned char* pbuffer,unsigned	short length);
unsigned char IIC_ReadOneByte(void);
unsigned short IIC_ReadBuffer(unsigned	char* pbuffer,unsigned short readlength);



void IIC_Delayus(unsigned	short Time);
void IIC_Delayms(unsigned	short Time);
#endif



