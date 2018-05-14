#ifndef __PD002V30_H
#define __PD002V30_H






typedef	struct _PD002V30
{
	struct
	{
		unsigned short RunningTime;		//计时器
		unsigned char	 StartAddr;			//数据存储起始地址
		unsigned long	 PieceWeight;		//单重
		struct
		{
			unsigned long	 PieceWeightCh1;		//单重
			unsigned long	 PieceWeightCh2;		//单重
		}Weight;
	}AT24C02;
}PD002V30Def;

void PD002V30_Configuration(void);

void PD002V30_Server(void);
void PD002V30_USART_Cofiguration(void);
void PD002V30_USART_Server(void);

void AT24C02_Configuration(void);
void SwitchID_Configuration(void);

unsigned char PD002V30_GetSwitchID(void);				//获取拔码开关地址
unsigned char PD002V30_GetBufferArray(void);		//获取各抽屉的AD值

void CS5530_Configuration(void);		//CS5530初始化
void CS5530_Server(void);				//读取AD值
	
void Seg_Configuration(void);		//数码管接口配置
void Seg_Server(void);					//数码更新接口

#endif

