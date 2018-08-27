#ifndef __PL012V20_H
#define __PL012V20_H



void PL012V20_Configuration(void);
void PL012V20_Server(void);


void SwitchID_Configuration(void);

void R61509V_Configuration(void);
void ILI9326_Configuration(void);


void RS485_Configuration(void);


void LCD_PowerUp(void);
void LCD_Display(void);



void SwitchID_Server(void);
void RS485_Server(void);


void PL010Delay(unsigned long time);
void LCD_WS(void);		//位闪烁
void LCD_WXS(void);		//位显示
void LCD_DDSP(void);		//显示总共请求数量和已发数量
#endif

