#ifndef __AMPLED02V13_H
#define __AMPLED02V13_H



void AMPLED02_Configuration(void);
void AMPLED02_Server(void);

void msg_Process(unsigned char* pFram,unsigned short length);

void LEDON(void);
void LEDOFF(void);
void ackFrame(void);


void LCD_Configuration(void);
	

void RS485_Configuration(void);


void RS485_Server(void);


void SwitchID_Configuration(void);
void SwitchID_Server(void);

////unsigned int PL010V13_PrintfString(unsigned short x,unsigned short y,unsigned char font,const char *format,...);				//后边的省略号就是可变参数
//void PL010Delay(unsigned long time);
//void LCD_WS(void);		//位闪烁
//void LCD_WXS(void);		//位显示
//void LCD_DDSP(void);		//显示总共请求数量和已发数量



#endif

