//#ifdef MX25L4006E

#include "MX25L4006E.H"

//#include	"stdio.h"			//用于printf
#include	"string.h"			//用于printf
//#include	"stdarg.h"			//用于获取不确定个数的参数
//#include	"stdlib.h"			//malloc动态申请内存空间


SPIFlashCmdDef MX25L4006ECmd	=
{
	MX25L4006E_WREN,			//write Enable：写使能
	MX25L4006E_WRDI,				//write disable：写失能
	MX25L4006E_WRSR,				//write status register：写状态寄存器
	MX25L4006E_RDID,				//read identification：读设备信息，3byte；第一字节为制造商代码，第二第三字节为芯片代码
	MX25L4006E_RDSR,				//read status register：读状态寄存器
	MX25L4006E_READ,				//read data：读数据
	MX25L4006E_FREAD,				//fast read data：快速读取数据
	MX25L4006E_RDSFDP,				//Read SFDP:读(SFDP)Serial Flash芯片规范
	MX25L4006E_RES,				//Read Electronic Signature:读器件读取电子标签
	MX25L4006E_REMS,				//Read Electronic Manufacturer & Device ID:读书制造商信息和ID
	MX25L4006E_DREAD,				//Double Output Mode command：双输出模式命令
	MX25L4006E_SE,				//Sector Erase：扇区擦除
	MX25L4006E_BE,				//Block Erase：块擦除也可以用0XD8
	MX25L4006E_CE,				//Chip Erase：芯片擦除; 整片擦除; 也可以用0XC7
	MX25L4006E_PP,				//Page Program：写页面
	MX25L4006E_DP,				//Deep Power Down：深度省电状态
	MX25L4006E_RDP					//Release from Deep Power-down：退出深度掉电
};
SPIFlashMemoryDef MemorySize	=	
{
	MX25L4006E_ChipSize,
	MX25L4006E_PageSize,
	MX25L4006E_SectorSize,
	MX25L4006E_BulkSize
};

#define	SPI_BUFFERSIZE	10

char SPI_TX_Buffer[SPI_BUFFERSIZE]={0X90,0X0F,0X0A,0X00};
char SPI_RX_Buffer[SPI_BUFFERSIZE]={0};

SPI_InitTypeDef  SPI_InitStructure;


vu32 FLASH_ID = 0;

u32 Temp = 0,Temp0=0,Temp1=0,Temp2=0;		//测试
MX25L4006EDef MX25L4006E;
/*******************************************************************************
* 函数名		:
* 功能描述	:
* 输入		:
* 输出		:
* 返回 		:
*******************************************************************************/
void MX25L4006E_Initialize(MX25L4006EDef *MX25Lx)
{
//	SPIFlashCmdDef *Cmd	=	&MX25Lx->SPIFlash.Cmd;
	
	memcpy((unsigned char*)&(MX25Lx->SPIFlash.Cmd),(unsigned char*)&MX25L4006ECmd,sizeof(SPIFlashCmdDef));		//拷贝支持的命令
	memcpy((unsigned char*)&(MX25Lx->SPIFlash.Memory),(unsigned char*)&MemorySize,sizeof(SPIFlashMemoryDef));		//拷贝存储容量信息
	
	SPI_FLASH_Initialize(&MX25Lx->SPIFlash);
//	SPI_StructConf(&SPI_InitStructure);										//配置参数
	
//	SPI_BASIC_Configuration(SPI1,&SPI_InitStructure);			//SPI常规配置
	
//	SPI_DMA_Configuration(SPI1,&SPI_InitStructure,(u32*)SPI_TX_Buffer,(u32*)SPI_RX_Buffer,SPI_BUFFERSIZE);				//SPI_DMA配置
	
//	PWM_OUT(TIM2,PWM_OUTChannel2,1,500);	//PWM设定-20161127版本
	
//	SPIT_Configuration(SPI1);							//SPI常规使用方式配置
//	SPI_Cmd(SPI1, ENABLE);
//	SPI_I2S_ReceiveData(SPI1);


}
/*******************************************************************************
* 函数名		:	
* 功能描述	:	 
* 输入		:	
* 输出		:
* 返回 		:
*******************************************************************************/
void MX25L4006E_Server(void)
{
//	if(Temp==0)
//		MX25L4006E_ReadID();
//	SPI_DMA_BufferRead((u32*)SPI_RX_Buffer);
//	GPIO_ResetBits(GPIOA,GPIO_Pin_4);
//	SPI_DMASend(SPI1,(u32*)SPI_TX_Buffer,(u32*)SPI_RX_Buffer,SPI_BUFFERSIZE);	//SPI_DMA发送函数----后边的省略号就是可变参数
//	GPIO_SetBits(GPIOA,GPIO_Pin_4);	
//	SPI_Cmd(SPI1, ENABLE);
//	SPI_DMA_ReceiveSendByte(SPI1,8);		//DMA收发数据
//	SPI_Cmd(SPI1, DISABLE);
}


//#endif


