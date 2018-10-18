#ifndef __PL012V20_H
#define __PL012V20_H

typedef struct _sPd014
{
	unsigned char Head;				//起始符0x7E
	unsigned char ADDdestin;	//目的地址
	unsigned char ADDsource;	//源地址
	unsigned char Serial;			//流水号 0x01~0x7C
	unsigned char Cmd;				//命令号
	unsigned char DataLen;		//数据长度
	unsigned char BCC8;				//异或检验：从目的地址开始异或到校验码前一个字节
	unsigned char End;				//结束符0x7F
}Pd014Def;
typedef struct _Pd014AckFarm
{
	unsigned char Head;				//起始符0x7E
	unsigned char ADDdestin;	//目的地址0x00
	unsigned char ADDsource;	//源地址:发药层地址
	unsigned char Serial;			//流水号 0x01~0x7C
	unsigned char Cmd;				//命令号：0xFF
	unsigned char DataLen;		//数据长度:0x03
	unsigned char Data1;			//数据长度:0x55
	unsigned char Data2;			//数据长度:0x01
	unsigned char Data3;			//数据长度:保留 0x00
	unsigned char BCC8;				//异或检验：从目的地址开始异或到校验码前一个字节
	unsigned char End;				//结束符0x7F
}Pd014AckFarmDef;

void PL012V20_Configuration(void);
void PL012V20_Server(void);


void SwitchID_Configuration(void);

void LCD_Configuration(void);
//void R61509V_Configuration(void);
//void ILI9326_Configuration(void);


void RS485_Configuration(void);


void LCD_PowerUp(void);
void LCD_Display(void);



void SwitchID_Server(void);
void RS485_Server(void);


void PL010Delay(unsigned long time);
void LCD_WS(void);		//位闪烁
void LCD_WXS(void);		//位显示
void LCD_DDSP(void);		//显示总共请求数量和已发数量


//=======================测试PD014
void PD014Test_Server(void);
void PD014Test_Display(unsigned char* buffer,unsigned char num);
void PD014Test_GetAdd(void);
#endif

