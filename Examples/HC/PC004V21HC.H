#ifndef __PC004V21HC_H
#define __PC004V21HC_H

#include "stm32f10x_type.h"
#include "HC_PHY.H"

//#define	RS485MaxDataSize	64			//RS485总线最大数据长度
//#define	Rs232MaxDataSize	64			//RS232最大数据长度

//=============================RS485A总线端口(与上层/单元板通讯接口)
#define	RS485BusDataSize		64			//RS485总线最大数据长度
#define	RS485BusBaudRate		19200
#define	RS485BusSerialPort	USART2
#define	RS485BusCtlPort			GPIOA
#define	RS485BusCtlPin			GPIO_Pin_1

//=============================RS485B总线端口(与下层/层板通讯接口)
#define	RS485layDataSize		64			//RS485总线最大数据长度
#define	RS485layBaudRate		19200
#define	RS485laySerialPort	UART4
#define	RS485layCtlPort			GPIOC
#define	RS485layCtlPin			GPIO_Pin_12

//=============================RS232A端口
#define	RS232ADataSize			64			//RS485总线最大数据长度
#define	RS232ABaudRate			19200
#define	RS232ASerialPort		USART1

//=============================RS232A端口
#define	RS232BDataSize			64			//RS485总线最大数据长度
#define	RS232BBaudRate			19200
#define	RS232BSerialPort		USART3

//=============================CAN.
#define	CANBaudRate					100000		//100K

//=============================拨码开关端口
#define	GPIOxSW1		GPIOC
#define	PinxSW1			GPIO_Pin_0

#define	GPIOxSW2		GPIOC
#define	PinxSW2			GPIO_Pin_1

#define	GPIOxSW3		GPIOC
#define	PinxSW3			GPIO_Pin_2

#define	GPIOxSW4		GPIOC
#define	PinxSW4			GPIO_Pin_3

#define	GPIOxSW5		GPIOC
#define	PinxSW5			GPIO_Pin_4

#define	GPIOxSW6		GPIOC
#define	PinxSW6			GPIO_Pin_5

#define	GPIOxSW7		GPIOC
#define	PinxSW7			GPIO_Pin_6

#define	GPIOxSW8		GPIOC
#define	PinxSW8			GPIO_Pin_7

//=============================锁及锁信号检测
#define	Lock1DrPort		GPIOB					//锁控制端口
#define	Lock1DrPin		GPIO_Pin_13		//锁控制管脚
#define	Lock1SiPort		GPIOB					//锁控制端口
#define	Lock1SiPin		GPIO_Pin_14		//锁控制管脚

#define	Lock2DrPort		GPIOB					//锁控制端口
#define	Lock2DrPin		GPIO_Pin_0		//锁控制管脚
#define	Lock2SiPort		GPIOB					//锁控制端口
#define	Lock2SiPin		GPIO_Pin_1		//锁控制管脚

#define	Lock3DrPort		GPIOA					//锁控制端口
#define	Lock3DrPin		GPIO_Pin_6		//锁控制管脚
#define	Lock3SiPort		GPIOA					//锁控制端口
#define	Lock3SiPin		GPIO_Pin_7		//锁控制管脚

#define	Lock4DrPort		GPIOA					//锁控制端口
#define	Lock4DrPin		GPIO_Pin_4		//锁控制管脚
#define	Lock4SiPort		GPIOA					//锁控制端口
#define	Lock4SiPin		GPIO_Pin_5		//锁控制管脚


















void PC004V21HC_Configuration(void);
void PC004V21HC_Server(void);




void Communiction_Configuration(void);			//通讯接口配置：包含RS485,RS232,CAN
void Switch_Configuration(void);						//拨码开关配置
void Lock_Configuration(void);							//锁端口配置



/*##############################################################################
################################################################################
# 项目名		:	MS0800_PC004V10	
# 功能描述	:	智能药架单元板
-------------------------------------------------------------------------------	
********************************功能说明***************************************
-------------------------------------------------------------------------------
● 与网关板通讯，传达指令到数码管显示板，
● 显示地址：柜机号
● 拔码方式：
● CAN通讯说明：
	波特率：	100K
	公有地址：0X000
	
● 485通讯说明：485与网关板通讯
	波特率：	9600
	串口号：	USART2
	控制脚：	PA1
	头码：		0XFA,0XFB
	私有地址：拔码开关地址
-------------------------------------------------------------------------------
********************************软件流程***************************************
-------------------------------------------------------------------------------
1）配置项目
2）上电后主动获取单元地址
3）	
4）	
5）	
-------------------------------------------------------------------------------
*****************************指令/协议说明*************************************
-------------------------------------------------------------------------------

--------------------------------CAN协议----------------------------------------
1.1）	CAN协议：				与数码管板通讯
			CAN—ID：					0X3FF(StdId=0X3FF;)
			长度：						3	(DLC=1;)
			层时间同步：			0XAA;(Data[0]=0XAA;)
			获取/显示ID指令：	0X01;(Data[0]=0X01;)
			自检指令：				0X02;(Data[0]=0X02;)
			熄屏指令：				0X03;(Data[0]=0X02;)
-------------------------------------------------------------------------------		
1.2）	数码管板上报地址：设定完数码管板ID后往单元板上他地址
			CAN—ID：			SW_ID（拔码开关地址）
			长度：				1	(DLC=1;)
			层时间同步：	0XAA;(Data[0]=0XAA;)
		
1.3）	数码管板接收数据：接收上级单元板数据，显示或者关闭
			CAN—ID：			SW_ID（拔码开关地址）
			长度：					3	(DLC=3;)
			数据显示标识：	0X08;(Data[0]=0X08;)
			显示数据内容：	最大显示999
										高位8位：Data[1]
										低位8位：Data[2]
									
1.4）	数码管板应答：数据完板接收到正确的数据后的回执
			CAN—ID：			SW_ID（拔码开关地址）
			长度：					1	(DLC=1;)
			层时间同步：		0XA0;(Data[0]=0XA0;)
--------------------------------485协议----------------------------------------
2.1）	485协议：			与网关板通讯
			数据长度：	13Byte
			RS232通讯说明：			FA F5 01 01 BCC8 00 06 01 01 01 00 01 25------->FA F5 01 01 27 00 06 01 01 01 00 01 25
//			格式：			HEAD(2)，命令，柜号，单元号，数值高位，数值低位，异或校验
			说明：
			HEAD:				0XFA,0XFB
			命令：			0X00--关闭显示，0X01--显示数值，0x02--获取连接设备地址（柜号和单元号）,0x03--显示单元ID，
			柜号：			单元柜号，1~0XFF
			单元号：		数码管ID号，10~77
			数值高位：	与低位连接
			数值低位：	与高位连接，连接后取值范围：0~999，数码管只有三位
			异或校验：	Byte0~Byte6校验
			接收数据单元无误，回执位为0X80|命令类型
			接收数据单元地址错误：回执位0XE0|命令类型
-------------------------------------------------------------------------------


********************************************************************************

################################################################################
###############################################################################*/

#endif

