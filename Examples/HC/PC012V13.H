#ifndef __PC012V13_H
#define __PC012V13_H









//=================================================================================================================主程序
void PC012V13_Configuration(void);
void PC012V13_Server(void);


//=================================================================================================================配置程序
void Lock_Configuration(void);				//锁初始化
void Switch_Configuration(void);			//拔码开关初始化及读数
void RS485_Configuration(void);				//RS485配置


#endif



