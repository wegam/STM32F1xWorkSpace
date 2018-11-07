/******************************** User_library *********************************
* 文件名 	: STM32_SDCard.H
* 作者   	: wegam@sina.com
* 版本   	: V
* 日期   	: 2016/01/01
* 说明   	: 
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/


#include "STM32_SYS.H"
#include "STM32_GPIO.H"

#define	HSE_USE

#ifndef	HSE_USE
	#define	HSI_USE
#endif


/*******************************************************************************
* 函数名		:	SYS_Configuration	
* 功能描述	:	 
* 输入		:	
* 输出		:
* 返回 		:
*******************************************************************************/
void SYS_Configuration(void)
{
#ifdef	HSE_USE
	RCC_Configuration_HSE();
#else
	RCC_Configuration_HSI();
#endif
}

/*******************************************************************************
* 函数名		:	RCC_Configuration
* 功能描述	:	系统时钟配置--使用外部8MHz晶振倍频到72MHz
* 输入		:	
* 输出		:
* 返回 		:
*******************************************************************************/
void RCC_Configuration_HSE(void)
{
	unsigned	short	retry	=	0;
	unsigned	long	time	=	0;
	ErrorStatus HSEStartUpStatus;
	/* RCC system reset(for debug purpose) */
	RCC_DeInit();																	//复位系统时钟
	
	/* Enable HSE */
	RCC_HSEConfig(RCC_HSE_ON);										//打开外部高速时钟
	
	while(time++<0xFFFF);
	
	Restart:
	
	/* Wait till HSE is ready */
	HSEStartUpStatus = RCC_WaitForHSEStartUp();		//等待外部高速时钟启动
	
	if(HSEStartUpStatus == SUCCESS)
	{
		/* Enable Prefetch Buffer */
		FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);	//使能或者失能预取指缓存
		
		/* Flash 2 wait state */
		FLASH_SetLatency(FLASH_Latency_2);					//设置代码延时值
		
		/* HCLK = SYSCLK */
		RCC_HCLKConfig(RCC_SYSCLK_Div1); 						//设置AHB时钟（HCLK）
		
		/* PCLK2 = HCLK */
		RCC_PCLK2Config(RCC_HCLK_Div1); 						//设置高速AHB时钟（PCLK2）
		
		/* PCLK1 = HCLK/2 */
		RCC_PCLK1Config(RCC_HCLK_Div2);							//设置低速AHB时钟（PCLK1）
		
		/* PLLCLK = 8MHz * 9 = 72 MHz */
		RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);	//设置PLL时钟源及倍频系数
		
		/* Enable PLL */ 
		RCC_PLLCmd(ENABLE);			//使能或者失能PLL
		
		/* Wait till PLL is ready */
		while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
		{
		}
		
		/* Select PLL as system clock source */
		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);	//设置系统时钟源（SYSCLK）
		
		/* Wait till PLL is used as system clock source */
		while(RCC_GetSYSCLKSource() != 0x08)				//返回用作系统时钟的时钟源
		{
		}
	}
	else if(retry++<2000)
	{
		goto Restart;
	}
//	GPIO_DeInitAll();				//将所有的GPIO关闭----V20170605
}
/*******************************************************************************
* 函数名		:	RCC_Configuration
* 功能描述	:	系统时钟配置---使用内部8MHz晶振倍频到64MHz
* 输入		:	
* 输出		:
* 返回 		:
*******************************************************************************/
void RCC_Configuration_HSI(void)
{
//	unsigned char temp=0;
//	unsigned char PLL;
//	//	RCC->CR|=0x00040000;  //????????HSEON
////	RCC->CR|=0x00010000;  //????????HSEON
////	while(!(RCC->CR>>17));//????????
//	RCC->CFGR=0X00000400; //APB1=DIV2;APB2=DIV1;AHB=DIV1;
//	PLL-=2;//??2???
//	RCC->CFGR|=PLL<<18;   //??PLL? 2~16
////	RCC->CFGR|=1<<16;	  //PLLSRC ON 
//	FLASH->ACR|=0x32;	  //FLASH 2?????

//	RCC->CR|=0x01000000;  //PLLON
//	while(!(RCC->CR>>25));//??PLL??
//	RCC->CFGR|=0x00000002;//PLL??????	 
//	while(temp!=0x02)     //??PLL??????????
//	{   
//		temp=RCC->CFGR>>2;
//		temp&=0x03;
//	}
		
		
	RCC_DeInit();	/*将外设RCC寄存器重设为缺省值?*/ 
	RCC_HSICmd(ENABLE); 
	while(RCC_GetFlagStatus(RCC_FLAG_HSIRDY)==RESET);//等待HSI就绪 
	RCC_HCLKConfig(RCC_SYSCLK_Div1);			/*设置AHB时钟（HCLK）?RCC_SYSCLK_Div1——AHB时钟=系统时*/	
	RCC_PCLK2Config(RCC_HCLK_Div1);				/*设置高速AHB时钟（PCLK2)RCC_HCLK_Div1——APB2时钟=HCLK*/	
	RCC_PCLK1Config(RCC_HCLK_Div2);				/*设置低速AHB时钟（PCLK1）RCC_HCLK_Div2——APB1时钟=HCLK/2*/	
	FLASH_SetLatency(FLASH_Latency_2);			/*设置FLASH存储器延时时钟周期数FLASH_Latency_2  2延时周期*/	
	FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);	/*选择FLASH预取指缓存的模,预取指缓存使能*/ 
	RCC_PLLConfig(RCC_PLLSource_HSI_Div2,RCC_PLLMul_16);	/*设置PLL时钟源及倍频系数，频率为8/2*16=64Mhz*/	
	RCC_PLLCmd(ENABLE);										/*使能PLL*/ 
	while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY)==RESET)	/*检查指定的RCC标志位(PLL准备好标志)设置与否*/	
	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);			/*设置系统时钟（SYSCLK）*/	 
	while(RCC_GetSYSCLKSource()!=0x08);					/*0x08：PLL作为系统时钟*/ 	

	GPIO_DeInitAll();				//将所有的GPIO关闭----V20170605
}

/*******************************************************************************
* Function Name  : SYSCLKConfig_STOP
* Description    : Configures system clock after wake-up from STOP: enable HSE, PLL
*                  and select PLL as system clock source.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SYSCLKConfig_STOP(void)
{
	ErrorStatus HSEStartUpStatus;
	
  /* Enable HSE */
  RCC_HSEConfig(RCC_HSE_ON);

  /* Wait till HSE is ready */
  HSEStartUpStatus = RCC_WaitForHSEStartUp();

  if(HSEStartUpStatus == SUCCESS)
  {
    /* Enable PLL */ 
    RCC_PLLCmd(ENABLE);

    /* Wait till PLL is ready */
    while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
    {
    }

    /* Select PLL as system clock source */
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

    /* Wait till PLL is used as system clock source */
    while(RCC_GetSYSCLKSource() != 0x08)
    {
    }
  }
}

