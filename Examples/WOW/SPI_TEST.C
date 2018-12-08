#ifdef SPI_TEST
#include "SPI_TEST.H"
#include "SPI_FLASH.H"

#include "STM32_SYS.H"
#include "STM32_GPIO.H"
#include "STM32_PWM.H"
#include "STM32_SPI.H"
#include "STM32_SYSTICK.H"
#include "STM32F10x_BitBand.H"


#include	"stdio.h"			//用于printf
#include	"string.h"		//用于printf
#include	"stdarg.h"		//用于获取不确定个数的参数
#include	"stdlib.h"		//malloc动态申请内存空间



SPIDef stSpi;
#define testlen 128
unsigned  char testrxbuffer[testlen]={0x05};
unsigned  char testtxbuffer[testlen]={0x05};

void Power_Configuration(void);
void SPI_Configuration(void);
void SPI_Test(void);
/*******************************************************************************
* 函数名		:	
* 功能描述	:	 
* 输入		:	
* 输出		:
* 返回 		:
*******************************************************************************/
void SPI_TEST_Configuration(void)
{
  SYS_Configuration();					//系统配置---打开系统时钟 STM32_SYS.H	
  Power_Configuration();
  SPI_Configuration();
  GPIO_Configuration_OPP50	(GPIOB,	GPIO_Pin_12);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605
  GPIO_Configuration_OPP50	(GPIOA,	GPIO_Pin_0);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605
//  PWM_OUT(TIM2,PWM_OUTChannel1,2000,500);						//PWM设定-20161127版本
  memset(testtxbuffer,0xAA,testlen);
  SysTick_Configuration(10);
}

/*******************************************************************************
* 函数名		:	
* 功能描述	:	 
* 输入		:	
* 输出		:
* 返回 		:
*******************************************************************************/
void SPI_TEST_Server(void)
{
  GPIO_Toggle	(GPIOA,	GPIO_Pin_0);		//将GPIO相应管脚输出翻转----V20170605
//  GPIO_Toggle	(GPIOB,	GPIO_Pin_12);		//将GPIO相应管脚输出翻转----V20170605
	SPI_Test();
}
/*******************************************************************************
*函数名			:	function
*功能描述		:	function
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
void SPI_Configuration(void)
{
  GPIO_InitTypeDef	GPIO_InitStructure;
SPI_InitTypeDef  SPI_InitStructure;
DMA_InitTypeDef	DMA_Initstructure;
  
  stSpi.Port.SPIx = SPI2;
  
  stSpi.Port.CS_PORT  = GPIOB;
  stSpi.Port.CS_Pin   = GPIO_Pin_12;
  SPI_InitializeDMA(&stSpi);
  
  return;
  
  
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2 ,ENABLE);				//开启SPI时钟
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO|RCC_APB2Periph_GPIOB, ENABLE);
  
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;				//设置方向				（2线全双工、2线只接收、一线发送、一线接收）
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;															//模式         	（从或主设备）
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;													//宽度         	（8或16位）
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;																//时钟极性     	（低或高）
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;															//时钟相位     	（第一个或第二个跳变沿）	
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;												//最先发送的位 	（最低位，还是最高位在先）
	SPI_InitStructure.SPI_CRCPolynomial = 7;																	//设置crc多项式	（数字）如7
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;																	//片选方式     	（硬件或软件方式）
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;				//波特率预分频 	（从2---256分频）
  
//  SPI_InitStructure.SPI_NSS = SPI_NSS_Hard;																//片选方式     	（硬件或软件方式）  
  
	SPI_Init(SPI2,&SPI_InitStructure);
  
//  SPI_SSOutputCmd(SPI2, ENABLE);			//如果在主机模式下的片选方式为硬件（SPI_NSS_Hard）方式，此处必须打开，否则NSS无信号
  
	SPI_Cmd(SPI2, ENABLE);				//使能SPI
  
//  SPI_SSOutputCmd(SPI2, ENABLE);			//如果在主机模式下的片选方式为硬件（SPI_NSS_Hard）方式，此处必须打开，否则NSS无信号
  
//5)**********DMA发送初始化，外设作为DMA的目的端
  DMA_Initstructure.DMA_PeripheralBaseAddr =  (u32)(&SPI2->DR);	//DMA外设源地址
  DMA_Initstructure.DMA_MemoryBaseAddr     = (u32)testtxbuffer;						//DMA数据内存地址
  DMA_Initstructure.DMA_DIR = DMA_DIR_PeripheralDST;												//DMA_DIR_PeripheralDST（外设作为DMA的目的端），DMA_DIR_PeripheralSRC（外设作为数据传输的来源）
  DMA_Initstructure.DMA_BufferSize = testlen; 													  //指定DMA通道的DMA缓存的大小
  DMA_Initstructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;					//DMA_PeripheralInc_Enable（外设地址寄存器递增），DMA_PeripheralInc_Disable（外设地址寄存器不变），
  DMA_Initstructure.DMA_MemoryInc =DMA_MemoryInc_Enable;										//DMA_MemoryInc_Enable（内存地址寄存器递增），DMA_MemoryInc_Disable（内存地址寄存器不变）
  DMA_Initstructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;		//外设数据宽度--DMA_PeripheralDataSize_Byte（数据宽度为8位），DMA_PeripheralDataSize_HalfWord（数据宽度为16位），DMA_PeripheralDataSize_Word（数据宽度为32位）
  DMA_Initstructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;						//内存数据宽度--DMA_MemoryDataSize_Byte（数据宽度为8位），DMA_MemoryDataSize_HalfWord（数据宽度为16位），DMA_MemoryDataSize_Word（数据宽度为32位）
  DMA_Initstructure.DMA_Mode = DMA_Mode_Normal;															//DMA工作模式--DMA_Mode_Normal（只传送一次）, DMA_Mode_Circular（不停地传送）
  DMA_Initstructure.DMA_Priority = DMA_Priority_High; 											//DMA通道的转输优先级--DMA_Priority_VeryHigh（非常高）DMA_Priority_High（高)，DMA_Priority_Medium（中），DMA_Priority_Low（低）
  DMA_Initstructure.DMA_M2M = DMA_M2M_Disable;															//DMA通道的内存到内存传输--DMA_M2M_Enable(设置为内存到内存传输)，DMA_M2M_Disable（非内存到内存传输）
  DMA_Init(DMA1_Channel5,&DMA_Initstructure);															//初始化DMA

  //6)**********DMA接收初始化，外设作为DMA的源端
  DMA_Initstructure.DMA_PeripheralBaseAddr =  (u32)(&SPI2->DR);	//DMA外设源地址
  DMA_Initstructure.DMA_MemoryBaseAddr     = 	(u32)testrxbuffer;						//DMA数据内存地址
  DMA_Initstructure.DMA_DIR = DMA_DIR_PeripheralSRC;												//DMA_DIR_PeripheralDST（外设作为DMA的目的端），DMA_DIR_PeripheralSRC（外设作为数据传输的来源）
  DMA_Initstructure.DMA_BufferSize = testlen; 													  //指定DMA通道的DMA缓存的大小
  DMA_Initstructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;					//DMA_PeripheralInc_Enable（外设地址寄存器递增），DMA_PeripheralInc_Disable（外设地址寄存器不变），
  DMA_Initstructure.DMA_MemoryInc =DMA_MemoryInc_Enable;										//DMA_MemoryInc_Enable（内存地址寄存器递增），DMA_MemoryInc_Disable（内存地址寄存器不变）
  DMA_Initstructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;		//外设数据宽度--DMA_PeripheralDataSize_Byte（数据宽度为8位），DMA_PeripheralDataSize_HalfWord（数据宽度为16位），DMA_PeripheralDataSize_Word（数据宽度为32位）
  DMA_Initstructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;						//内存数据宽度--DMA_MemoryDataSize_Byte（数据宽度为8位），DMA_MemoryDataSize_HalfWord（数据宽度为16位），DMA_MemoryDataSize_Word（数据宽度为32位）
  DMA_Initstructure.DMA_Mode = DMA_Mode_Normal;															//DMA工作模式--DMA_Mode_Normal（只传送一次）, DMA_Mode_Circular（不停地传送）
  DMA_Initstructure.DMA_Priority = DMA_Priority_High; 											//DMA通道的转输优先级--DMA_Priority_VeryHigh（非常高）DMA_Priority_High（高)，DMA_Priority_Medium（中），DMA_Priority_Low（低）
  DMA_Initstructure.DMA_M2M = DMA_M2M_Disable;															//DMA通道的内存到内存传输--DMA_M2M_Enable(设置为内存到内存传输)，DMA_M2M_Disable（非内存到内存传输）
  DMA_Init(DMA1_Channel4,&DMA_Initstructure);															//初始化DMA
  
  
  SPI_I2S_DMACmd(SPI2, SPI_I2S_DMAReq_Tx, ENABLE);								//开启DMA发送
  SPI_I2S_DMACmd(SPI2, SPI_I2S_DMAReq_Rx, ENABLE);								//开启DMA接收
  
  DMA_Cmd(DMA1_Channel4,ENABLE);	
  DMA_Cmd(DMA1_Channel5,ENABLE);
    
}
/*******************************************************************************
*函数名			:	function
*功能描述		:	function
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
void SPI_Test(void)
{
//  rets:
//  PB12  = 0;
//  SPI_DMASend(stSpi.Port.SPIx,testtxbuffer,testlen);
////  
//  while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);		//检查指令SPI接收完成标志设置与否
////  goto rets;
//  PB12  = 1;
  unsigned  short num = 0;
  PB12  = 0;
  num = SPI_DMAReadWrite(SPI2,testtxbuffer,testrxbuffer,testlen);
  if((0==num)||(0xFFFF==num))
  {
    PB12  = 0;
  }
  else
  {
    PB12  = 1;
  }

  
  
  
//  SPI_Cmd(SPI2, ENABLE);				//使能SPI
//  SPI_I2S_SendData(SPI2, 0x55);				//发送数据
//  SPI_Cmd(SPI2, DISABLE);				//使能SPI
}
/*******************************************************************************
*函数名			:	function
*功能描述		:	function
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
void Power_Configuration(void)
{
  unsigned  short  temp  = 0;
  GPIO_Configuration_IPU(GPIOB,	GPIO_Pin_4);			//将GPIO相应管脚配置为上拉输入模式----V20170605
  GPIO_Configuration_OPP50(GPIOF,GPIO_Pin_10);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605
  restart:
  PF10 = 1;
	SysTick_DeleymS(1000);					//SysTick延时nS
//  while(0  ==  PB4in)
//  {
//    SysTick_DeleymS(1);					//SysTick延时nS
//    temp++;
//    if(temp>3000)
//    {
//      Key = 0;
//      
//      break;
//    }
//    
//  }
//  if(temp<3000)
//  {
//    PF10  = 1;
//    temp  = 0;
//    goto restart;
//  }
}




#endif
