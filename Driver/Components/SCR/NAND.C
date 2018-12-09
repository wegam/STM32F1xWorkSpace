/**************************************************************************************************
* 液晶屏驱动IC
* 文件<$(filename)>
* 模块描述 :	定义、功能、说明
* 历史修改记录
*     <主要修改者>  <时间>   <版本 >   <说明>
*     xlyan        $(Date)   1.0.0    创建文件
**************************************************************************************************/
#include "NAND.H"

#include "stm32f10x_fsmc.h"

//#include "STM32_GPIO.H"
//#include "STM32_PWM.H"
//#include "STM32_SYSTICK.H"
//#include "font.h"
#include "string.h"				//串和内存操作函数头文件
#include "stdlib.h"				//串和内存操作函数头文件
#include "stdarg.h"				//串和内存操作函数头文件
#include "stdio.h"				//串和内存操作函数头文件
#include "stdint.h"				//串和内存操作函数头文件



/**
  ******************************************************************************
本程序为GPIO驱动NAND 闪存的程序，初步完成了读写一个页的功能，无坏块处理和算法，
耗时近9小时！值得注意的是：
***************************************************
***********在写数据以前一定要先擦除，因为FLASH技术不能把0变1，只能1变0，切忌切忌**************
***********在写数据以前一定要先擦除，因为FLASH技术不能把0变1，只能1变0，切忌切忌****************************************
   在写数据以前一定要先擦除，因为FLASH技术不能把0变1，只能1变0，切忌切忌
   在写数据以前一定要先擦除，因为FLASH技术不能把0变1，只能1变0，切忌切忌


   2011年8月28日
   天津第四项目部宿舍内
   王均伟
*/

/*Includes ------------------------------------------------------------------*/

#include "stm32f10x_type.h"
#include "stm32f10x_flash.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#define SET_CLE GPIO_SetBits(GPIOD, GPIO_Pin_11)
#define CLR_CLE GPIO_ResetBits(GPIOD, GPIO_Pin_11)
#define SET_ALE GPIO_SetBits(GPIOD, GPIO_Pin_12)
#define CLR_ALE GPIO_ResetBits(GPIOD, GPIO_Pin_12)
#define SET_CE GPIO_SetBits(GPIOG, GPIO_Pin_10)
#define CLR_CE GPIO_ResetBits(GPIOG, GPIO_Pin_10)
#define SET_WE GPIO_SetBits(GPIOD, GPIO_Pin_5)
#define CLR_WE GPIO_ResetBits(GPIOD, GPIO_Pin_5)
#define SET_RE GPIO_SetBits(GPIOD, GPIO_Pin_4)
#define CLR_RE GPIO_ResetBits(GPIOD, GPIO_Pin_4)
uint8_t tabel[2111];
void mysysinit(void);//系统时钟初始
void my_USART_init(void);//初始化
void my_send_byte(unsigned char send_date); //发送一个字节
GPIO_InitTypeDef GPIO_InitStructure;//GPIO的属性结构体变量定义
void READ_NAND_ID(void);//读闪存的ID
void delay_1us(uint32_t);//延时1微秒程序
void my_NAND_INIT(void ); //nand flash 初始化
void wait_NAND_readay(void);//等待闪存准倍完毕
void write_nand_addrrs(uint8_t a);
void write_nand_commond(uint8_t comm);
void write_nand_date(uint8_t da);
uint8_t read_nand_date(void);
void write_NAND_PAGE(void);//写闪存的一页
void read_NAND_PAGE(void); //读闪存的一页
void erase_NAND_BLOK(void);//擦出闪存的一个块

/*******************************************************************************
*函数名			:	LCD_Initialize
*功能描述		:	LCD初始化：
*输入				: 
*返回值			:	无
*******************************************************************************/
void NAND_Initialize(void)
{
//  mysysinit();//RCC初始化，系统时钟设置72MHZ
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);//使能APB2的GPIO_D时钟
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG, ENABLE);//使能APB2的GPIO_D时钟
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);//使能APB2的GPIO_B时钟
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);//使能APB2的GPIO_E时钟
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);//使能APB2的GPIO_E时钟
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);//使能APB1的USART2时钟
  /* led*/
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9| GPIO_Pin_10| GPIO_Pin_11;
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//  GPIO_Init(GPIOD, &GPIO_InitStructure);
  /* 设置PB.5用于控制NAND的为上拉输入 RB */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(GPIOD, &GPIO_InitStructure);
  /* 设置PD口用于控制NAND的为输出 */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6| GPIO_Pin_7| GPIO_Pin_14| GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOD, &GPIO_InitStructure);
//  my_USART_init();  
       

  wait_NAND_readay();//忙则等待；

  my_send_byte(0);
  my_send_byte(1);
  my_send_byte(2);
  my_send_byte(3);
  
  READ_NAND_ID(); //读闪存ID
  erase_NAND_BLOK();//擦除闪存的一个块
  write_NAND_PAGE();//写一个页

  read_NAND_PAGE();//读一个页
  while(1);


}
/*擦除一个块*/
void erase_NAND_BLOK()
{ uint8_t e,m;



/*设置PE口得低八位为输出*/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1| GPIO_Pin_2| GPIO_Pin_3| GPIO_Pin_4|GPIO_Pin_5 | GPIO_Pin_6| GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOE, &GPIO_InitStructure);
  
  SET_WE;
  SET_RE;
  CLR_ALE;  //初始化
  CLR_CLE;

  CLR_CE;
  SET_CLE;
  CLR_ALE;
  CLR_WE;
  GPIO_Write(GPIOE, 0x60); //命令
  SET_WE;
  CLR_CLE;
  SET_ALE;
  CLR_WE;
  GPIO_Write(GPIOE, 0x00); //快地址0
  SET_WE;
  CLR_WE;
  GPIO_Write(GPIOE, 0x00); //块地址1
  SET_WE;
  CLR_ALE;
  SET_CLE;
  CLR_WE;
  GPIO_Write(GPIOE, 0xd0); //开始擦除
  SET_WE;
  CLR_CLE;
  for(m=5;m;m--);//延时满足时序
  wait_NAND_readay();
  delay_1us(3000); //等待擦完
  SET_CLE;
  CLR_WE;
  GPIO_Write(GPIOE, 0x70); // 读状态码状态读 //这个状态要为E0才表示操作完成可以进行下一步操作
  SET_WE;
  CLR_CLE;
  GPIOE->CRL=0x88888888; //数据口转换成输入
  CLR_RE;
  e=(GPIOE->IDR);//读出数据
  SET_RE;
  my_send_byte(e);  //穿行发送

}
/*读闪存一页*/
void read_NAND_PAGE()
{
  uint32_t n;
  uint8_t sd;

  /*设置PE口得低八位为输出*/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1| GPIO_Pin_2| GPIO_Pin_3| GPIO_Pin_4|GPIO_Pin_5 | GPIO_Pin_6| GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOE, &GPIO_InitStructure);
  SET_WE;
  SET_RE;
  CLR_ALE;
  CLR_CLE;

  CLR_CE;//片选开启
  SET_CLE;
  CLR_ALE;
  SET_RE;
  CLR_WE;
  GPIO_Write(GPIOE, 0x00); //  读命令
  SET_WE;
  CLR_CLE;
  SET_ALE;
  SET_RE;
  CLR_WE;
  GPIO_Write(GPIOE, 0x00); //页地址
  SET_WE;
  CLR_WE;
  GPIO_Write(GPIOE, 0x00);//页地址
  SET_WE;
  CLR_WE;
  GPIO_Write(GPIOE, 0x00); //快地址
  SET_WE;
  CLR_WE;
  GPIO_Write(GPIOE, 0x00);//快地址
  SET_WE;

  CLR_ALE;
  SET_CLE;
  SET_RE;
  CLR_WE;
  GPIO_Write(GPIOE, 0x30); //开始读出命令
  SET_WE;
  CLR_CLE;
  GPIOE->CRL=0x88888888; //接口转换
  for(n=30;n;n--);//满足时序
    delay_1us(20); //等待
  wait_NAND_readay();
  for(n=2112;n;n--)
  {
    CLR_RE;
    sd=(GPIOE->IDR);//读出数据
    SET_RE;
    my_send_byte(sd);//发送到计算机
  }

  SET_CE;
  SET_WE;
  SET_RE;
  CLR_ALE;
  CLR_CLE;
}


/*写闪存的一页，数据=2112字节=2kb*/
void write_NAND_PAGE()
{
  uint8_t send_date=0;
  uint32_t numb;
   /*设置PE口得低八位为输出*/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1| GPIO_Pin_2| GPIO_Pin_3| GPIO_Pin_4|GPIO_Pin_5 | GPIO_Pin_6| GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOE, &GPIO_InitStructure);
  SET_WE;
  SET_RE;
  CLR_ALE;
  CLR_CLE;

  CLR_CE;//片选开启
  SET_CLE;//命令
  CLR_ALE;
  SET_WE;
  SET_RE;

  CLR_WE;
  GPIO_Write(GPIOE, 0x80); //写一页命令
  SET_WE;
  CLR_CLE;//释放命令总线


  SET_ALE;//地址写入允许
  CLR_WE;
  GPIO_Write(GPIOE, 0x00); //页地址0
  SET_WE;
  CLR_WE;
  GPIO_Write(GPIOE, 0x00); //页地址
  SET_WE;
  CLR_WE;
  GPIO_Write(GPIOE, 0x00); //快递至
  SET_WE;
  CLR_WE;
  GPIO_Write(GPIOE, 0x00); //快递至
  SET_WE;
  CLR_ALE;//释放地址总线

  for(numb=5;numb;numb--);//延时
  for(numb=2112;numb;numb--)
  {
     CLR_WE;
     GPIO_Write(GPIOE, 0x89);  //写入数据89
     SET_WE;

  }
  SET_CLE;//开启命令总线
  CLR_WE;
  GPIO_Write(GPIOE, 0x10);//页编程
  SET_WE;
  for(numb=3;numb;numb--);//略微延时
  wait_NAND_readay();
  delay_1us(500);
  CLR_WE;
  GPIO_Write(GPIOE, 0x70);//状态读 //这个状态要为E0才表示操作完成可以进行下一步操作
  SET_WE;
  GPIOE->CRL=0x88888888;
  SET_WE;
  SET_RE;
  CLR_RE;
  send_date=(GPIOE->IDR);//读出数据
  SET_CE;
  my_send_byte(send_date);
  SET_WE;
  SET_RE;
  CLR_ALE;
  CLR_CLE;

}

/*等待芯片不忙*/
void wait_NAND_readay()
{
  uint8_t wait=0;//忙闲信号
  //等待芯片不忙
  do
  {
    wait=GPIO_ReadOutputDataBit(GPIOD, GPIO_Pin_6);//读取忙闲引脚
  }
  while(0x00==wait);
}
/*读取NAND闪存的ID序列号串口发送*/
void READ_NAND_ID()
{

  uint8_t a=0,b=0,c=0,d=0;

  
   /* 设置PD口用于控制NAND的为输出 */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6| GPIO_Pin_7| GPIO_Pin_14| GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOD, &GPIO_InitStructure);
/*设置PE口得低八位为输出*/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1| GPIO_Pin_2| GPIO_Pin_3| GPIO_Pin_4|GPIO_Pin_5 | GPIO_Pin_6| GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOE, &GPIO_InitStructure);


  CLR_CE;//开启片选


  SET_CLE;//命令锁存开启
  CLR_WE;//写使能
  CLR_ALE;//地址锁存关闭
  SET_RE;//读关闭
  GPIO_Write(GPIOE, 0x90); //读ID命令
  SET_WE;//关闭写

  CLR_CLE;
  SET_ALE;
  CLR_WE;
  GPIO_Write(GPIOE, 0x00); //地址00
  SET_WE;




  /*设置PE口得低八位为输入*/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1| GPIO_Pin_2| GPIO_Pin_3| GPIO_Pin_4|GPIO_Pin_7 | GPIO_Pin_6| GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(GPIOE, &GPIO_InitStructure);

  CLR_ALE; //注意啊，这里一定把他放在下面应为是有时间要求的；时序图TAR=15纳秒之后才是RE的操作；
       //读出的结果是AD F1 80 1D ，2011年8月26日，与天津第四项目部宿舍
     //AD F1,不用关心，80 1D代表本闪存为8位组织结构，页面大小为2KB，快大小为128KB，备用区为每512字节有16字节
  CLR_RE;

  a=(GPIOE->IDR);//读出数据
  SET_RE;

  CLR_RE;
  b=(GPIOE->IDR);
  SET_RE;

  CLR_RE;
  c=(GPIOE->IDR);
  SET_RE;

  CLR_RE;
  d=(GPIOE->IDR);//delay_1us(1);
  SET_RE;


  SET_CE;//关闭片选

  my_send_byte(a);
  my_send_byte(b);
  my_send_byte(c);
  my_send_byte(d);
}
/*写一个命令*/
void write_nand_commond(uint8_t comm)
{
  CLR_CE;
  SET_RE;
  SET_CLE;//命令锁存开启
  CLR_ALE;//地址锁存关闭
  CLR_WE;//写使能
  GPIO_Write(GPIOE, comm); //命令
  SET_WE;//关闭写
  CLR_CLE;
  SET_CE;

}
/*写一个地址*/
void write_nand_addrrs(uint8_t a)
{
  CLR_CE;
  SET_RE;
  CLR_CLE;
  SET_ALE;
  CLR_WE;;;
  GPIO_Write(GPIOE, a); //地址
  SET_WE;
  CLR_ALE;
  SET_CE;


}
//写一个数据
void write_nand_date(uint8_t da)
{ 
  CLR_CE;
  CLR_ALE;
  CLR_CLE;
  SET_RE;
  CLR_WE;
  GPIOE->ODR=da;//GPIO_Write(GPIOE, da); //数据
  SET_WE;
  SET_CE;
}
/*读一个数据*/
uint8_t read_nand_date()
{
  uint8_t a;
  CLR_CE;
  SET_WE;
  SET_RE;
  CLR_RE;;;; 
  a=(GPIOE->IDR);//读出数据
  SET_RE;
  SET_CE;
  return a;
}
/********************
  延时函数
  形参：uint8_t time
  功能：延时数值为time值

*********************/
void delay_1us(uint32_t time)
{   
  uint32_t b,c;
  for(c=time;c;c--) //定时=time*3*333.6=time*1000.8ns
  {     
    for(b=8;b;b--); //8*13.9*3= 333.6     
  }
}
/***********************************

发送一个字节函数通过串口

************************************/ 
void my_send_byte(unsigned char send_date )
{

  while( (USART1->SR&0x00000080)!=0x80);//发送寄存器为空
   USART1->DR=send_date; 


}
/**********************************
          初始化串口

**********************************/
void my_USART_init()
{

/*USART2的优先级设为5*/
NVIC->IPR[37]=5;
/*开启38号中断即USART2，关闭其他所有外部的中断*/
NVIC->ISER[1]=0x00000020;    
/*设置复用模式下的引脚模式为全双工：TX输出推挽复用，RX为输入上拉模式，速度50MHZ*/
            GPIOA->CRH=0x000008b0; 
  /* 1.开启USART，
* 
*/
USART1->CR1=0x2000;
/* 1.关闭局域网模式
* 2.1个停止位
* 3.CK引脚禁能
*/
USART1->CR2=0;
/* 1.关闭调制解调模式
* 2.关闭DMA模式
* 3.关闭智能卡、红外模式
*   4.关闭错误中断

*/
USART1->CR3=0;
/*     波特率设置

     2011年8月11日
        王均伟
         天津第四项目部宿舍

    BRR中的第四位（DIV_Fraction）作为小数，高12位(DIV_MANtissa)作为整数部分，
  
    1，根据公式：波特率=fck/16*usardiv,其中usardivBRR寄存器的值，所以变形得：USARDIV=fck/16*波特率
    2.算出来BRR寄存器的值后就要把这个值变成16进制数据写入BRR寄存器中，
      遵循以下规则：
      小数部分*16=DIV_Fraction或者取近似的值
      整数部分直接=DIV_MANtissa
    3.把这个16进制值写入BRR寄存器
    例如我要算波特率设成9600bps的BRR寄存器值，
    1.先求USARDIV=36000000/16*9600=234.375
    2.换成十六进制：DIV_Fraction=16*0.375=0x6
                    DIV_MANtissa=234=0xea
    3.组合并写入寄存器
                     USART2->BRR=0x0ea6;值得注意的是这里是16位半字操作，所以不要以为是32位。

*/
USART1->BRR=0x0ea6;

/* 1.开启USART
* 2.开启接收完毕中断
* 3.开启发送功能
*   4.开启接收功能
*/
USART1->CR1=0x202c;


}


void mysysinit()//系统初始化程序
{
ErrorStatus HSEStartUpStatus;//说明标志位
RCC_DeInit();//所有外设全部缺省设置

/* Enable HSE */
RCC_HSEConfig(RCC_HSE_ON);
/* Wait till HSE is ready and if Time out is reached exit */
HSEStartUpStatus = RCC_WaitForHSEStartUp();
if(HSEStartUpStatus == SUCCESS)//启动成功
{
/*这两条FLASH指令必须加上，不知为啥？不加上就运行几秒后出错，参照系统初始化*/
/* Enable The Prefetch Buffer */
FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);//FLASH缓存开启
/* Configure the Latency cycle: Set 2 Latency cycles */
  FLASH_SetLatency(FLASH_Latency_2);  //设置FLASH这些位表示SYSCLK(系统时钟)周期与闪存访问时间的比例,为010：两个等待状态，当 48MHz < SYSCLK ≤ 72MHz
/* Set PLL clock output to 72MHz using HSE (8MHz) as entry clock */
RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);//外部时钟为8M，PLL的输入时钟=8MHZ，倍频系数9，

/* Configure HCLK such as HCLK = SYSCLK */
RCC_HCLKConfig(RCC_SYSCLK_Div1);//设置了啦AHB分频器的分频系数=1，即HCLK=SYSCLK=72MHZ
/* Configure PCLK1 such as PCLK1 = HCLK/2 */
RCC_PCLK1Config(RCC_HCLK_Div2);//设置了APB1外设的时钟频率最大是36M这里是APB1的分频器设为2,PCLK1=HCLK/2=72/2=36MHZ正好是最大值
/* Configure PCLK2 such as PCLK2 = HCLK */
RCC_PCLK2Config(RCC_HCLK_Div1);//设置PLCK2=HCLK=72MHZ，的APB2分频器=1
/* Select the PLL as system clock source */
RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);//设置了SYSCLK的提供者为PLL，频率由上面算出=72MHZ
/* disable PLL Ready interrupt */
RCC_ITConfig(RCC_IT_PLLRDY, DISABLE);//PLL中断关闭
/* disable PLL Ready interrupt */
RCC_ITConfig(RCC_IT_HSERDY,DISABLE);//HSE中断关闭
/* disable PLL Ready interrupt */
RCC_ITConfig(RCC_IT_HSIRDY, DISABLE); //HSI中断关闭
/* disable PLL Ready interrupt */
RCC_ITConfig(RCC_IT_LSERDY, DISABLE); //LSE中断关闭
/* disable PLL Ready interrupt */
RCC_ITConfig(RCC_IT_LSIRDY, DISABLE); //LSI中断关闭

/* PLL clock divided by 1.5 used as USB clock source */
RCC_USBCLKConfig(RCC_USBCLKSource_PLLCLK_1Div5);//设置USB的时钟为=72、1.5=48mhz
/* Configure ADCCLK such as ADCCLK = PCLK2/2 */
RCC_ADCCLKConfig(RCC_PCLK2_Div2);//设置ADC时钟=PCLK2/2= 36MHZ
/* disable the LSE */
RCC_LSEConfig(RCC_LSE_OFF);//外部低速晶振关闭

/*DISable the RTC clock */
RCC_RTCCLKCmd(DISABLE);
/* DISable the Clock Security System */
RCC_ClockSecuritySystemCmd(DISABLE);
/* Enable the PLL */
RCC_PLLCmd(ENABLE);//使能PLL







/* PLL ans system clock config */
}
else
{
/* Add here some code to deal with this error */
}
}
/************************************** The End Of FILE **************************************/


