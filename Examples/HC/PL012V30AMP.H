#ifndef __PL012V30AMP_H
#define __PL012V30AMP_H



void PL012V30AMP_Configuration(void);
void PL012V30AMP_Server(void);



void LCD_Configuration(void);
	
//void SwitchID_Configuration(void);
//void R61509V_Configuration(void);
void RS485_Configuration(void);


////void LCD_PowerUp(void);
////void LCD_Display(void);



//void SwitchID_Server(void);
void RS485_Server(void);

////unsigned int PL010V13_PrintfString(unsigned short x,unsigned short y,unsigned char font,const char *format,...);				//后边的省略号就是可变参数
//void PL010Delay(unsigned long time);
//void LCD_WS(void);		//位闪烁
//void LCD_WXS(void);		//位显示
//void LCD_DDSP(void);		//显示总共请求数量和已发数量



#endif

