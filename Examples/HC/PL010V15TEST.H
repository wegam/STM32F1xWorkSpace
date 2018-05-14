#ifndef __PL010V15_H
#define __PL010V15_H



typedef enum
{
	Cmd0	=	0x01,
	Cmd1,
	Cmd2
}TcmdDef;



void PL010V15TEST_Configuration(void);
void PL010V15TEST_Server(void);


void CS5530_Server(void);		//称重服务，AD值处理，获取稳定值
void R61509V_Server(void);	//显示服务相关
void RS485_Server(void);		//通讯管理---负责信息的接收与发送
void SwitchID_Server(void);	//拔码开关处理--动态更新拨码地址

void SwitchID_Configuration(void);
void GT32L32_Configuration(void);
void R61509V_Configuration(void);
void CS5530_Configuration(void);
void RS485_Configuration(void);


void LCD_PowerUp(void);
void LCD_Display(void);

unsigned int PL010V13_PrintfString(unsigned short x,unsigned short y,unsigned char font,const char *format,...);				//后边的省略号就是可变参数
void PL010Delay(unsigned long time);


#endif

