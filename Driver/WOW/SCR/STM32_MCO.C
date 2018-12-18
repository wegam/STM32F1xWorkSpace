/******************************** User_library *********************************
* 文件名 	: STM32_MCO.H
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


#include "STM32_MCO.H"
#include "stm32f10x_gpio.h"
//#include "STM32F10x_BitBand.H"


//RCC_ClocksTypeDef
/*******************************************************************************
*函数名		:	function
*功能描述	:	获取时间
*输入			: 
*输出			:	无
*返回值		:	无
*例程			:
*******************************************************************************/
void MCO_Initialize(void)
{
	GPIO_InitTypeDef	GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	//--------------------------设置PA.8为复用Push-Pull模式。
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 
	GPIO_Init(GPIOA, &GPIO_InitStructure); 
	//--------------------------选择输出时钟源。
	//------时钟的选择由时钟配置寄存器(RCC_CFGR)中的MCO[2:0]位控制。
	//参数RCC_MCO为要输出的内部时钟：
	//RCC_MCO_NoClock --- 无时钟输出 
	//RCC_MCO_SYSCLK --- 输出系统时钟（SysCLK） 
	//RCC_MCO_HSI --- 输出内部高速8MHz的RC振荡器的时钟（HSI） 
	//RCC_MCO_HSE --- 输出高速外部时钟信号（HSE） 
	//RCC_MCO_PLLCLK_Div2 --- 输出PLL倍频后的二分频时钟（PLLCLK/2） 	
	RCC_MCOConfig(RCC_MCO_HSE); 
}


