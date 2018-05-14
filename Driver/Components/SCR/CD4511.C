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



#include "CD4511.H"
#include "STM32_GPIO.H"
#include	"stdlib.h"		//malloc动态申请内存空间
//#include "STM32F10x_BitBand.H"

//CD4511BcdDef* CD4511Bcd;		//BCD码结构体
/*******************************************************************************
*函数名			:	function
*功能描述		:	函数功能说明
*输入				: 
*返回值			:	无
*******************************************************************************/
void CD4511_Delay(u32 time)
{
	while(time--);
}
/*******************************************************************************
*函数名			:	function
*功能描述		:	函数功能说明
*输入				: 
*返回值			:	无
*******************************************************************************/
void CD4511_Initialize(CD4511Def *pInfo)
{
//	unsigned char		i	=	0;
//	unsigned long		*Port			=	NULL;
//	unsigned long 	*Pin			=	NULL;					//GPIO_Pin_x
	
	GPIO_Configuration_OPP50	(pInfo->Port.A0_PORT,		pInfo->Port.A0_Pin);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度2MHz----V20170605
	GPIO_Configuration_OPP50	(pInfo->Port.A1_PORT,		pInfo->Port.A1_Pin);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度2MHz----V20170605
	GPIO_Configuration_OPP50	(pInfo->Port.A2_PORT,		pInfo->Port.A2_Pin);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度2MHz----V20170605
	GPIO_Configuration_OPP50	(pInfo->Port.A3_PORT,		pInfo->Port.A3_Pin);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度2MHz----V20170605
	
	GPIO_Configuration_OPP50	(pInfo->Port.Seg1_PORT,		pInfo->Port.Seg1_Pin);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度2MHz----V20170605
	GPIO_Configuration_OPP50	(pInfo->Port.Seg2_PORT,		pInfo->Port.Seg2_Pin);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度2MHz----V20170605
	GPIO_Configuration_OPP50	(pInfo->Port.Seg3_PORT,		pInfo->Port.Seg3_Pin);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度2MHz----V20170605
	
//	for(i	=	0;	i<pInfo->Data.Num;	i++)
//	{
//		GPIO_Configuration_OPP50	((GPIO_TypeDef*)*Port,(unsigned short)*Pin);		//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度2MHz----V20170605
//		GPIO_ResetBits((GPIO_TypeDef*)(*Port), (unsigned short)*Pin);
//		Port	+=	2;
//		Pin		+=	2;
//	}
}
/*******************************************************************************
*函数名			:	CD4511_Process
*功能描述		:	根据Time做三位数码管扫描
*输入				: 
*返回值			:	无
*******************************************************************************/
void CD4511_Process(CD4511Def *pInfo)
{
	unsigned char		i;
	unsigned short	Data;					//显示的数据
	unsigned short	Time;					//计时器
	CD4511BcdDef*		CD4511Bcd;		//BCD码结构体
	
	Data	=	pInfo->Data.Data;
	Time	=	pInfo->Data.Time;
	
	i	=	Time%3;				//三位数码管
	
	if(pInfo->Data.Time++>=10000)
	{
		pInfo->Data.Time	=	0;
	}
	//=============先关闭数码管显示
	GPIO_ResetBits(pInfo->Port.Seg1_PORT, pInfo->Port.Seg1_Pin);			//SEG1
	GPIO_ResetBits(pInfo->Port.Seg2_PORT, pInfo->Port.Seg2_Pin);			//SEG2
	GPIO_ResetBits(pInfo->Port.Seg3_PORT, pInfo->Port.Seg3_Pin);			//SEG3
	
	//=============取出显示数值
	switch(i)
	{
		case 0:Data	=	Data%10;break;//显示个位
		case 1:Data	=	(Data%100)/10;break;//显示十位
		case 2:Data	=	(Data/100);break;//显示百位
		default :break;
	}
	
	CD4511Bcd	=	(CD4511BcdDef*)&Data;				//转换为BCD码
	
	if(CD4511Bcd->A)
	{
		GPIO_SetBits(pInfo->Port.A0_PORT, pInfo->Port.A0_Pin);
	}
	else
	{
		GPIO_ResetBits(pInfo->Port.A0_PORT, pInfo->Port.A0_Pin);			//A/A0
	}
	if(CD4511Bcd->B)
	{
		GPIO_SetBits(pInfo->Port.A1_PORT, pInfo->Port.A1_Pin);
	}
	else
	{
		GPIO_ResetBits(pInfo->Port.A1_PORT, pInfo->Port.A1_Pin);			//B/A1
	}
	if(CD4511Bcd->C)
	{
		GPIO_SetBits(pInfo->Port.A2_PORT, pInfo->Port.A2_Pin);
	}
	else
	{
		GPIO_ResetBits(pInfo->Port.A2_PORT, pInfo->Port.A2_Pin);			//C/A2
	}
	if(CD4511Bcd->D)
	{
		GPIO_SetBits(pInfo->Port.A3_PORT, pInfo->Port.A3_Pin);
	}
	else
	{
		GPIO_ResetBits(pInfo->Port.A3_PORT, pInfo->Port.A3_Pin);			//D/A3
	}
	//=============打开相应数码管位
	switch(i)
	{
		case 0:GPIO_SetBits(pInfo->Port.Seg1_PORT, pInfo->Port.Seg1_Pin);			//SEG1
					break;
		case 1:GPIO_SetBits(pInfo->Port.Seg2_PORT, pInfo->Port.Seg2_Pin);			//SEG1
					break;
		case 2:GPIO_SetBits(pInfo->Port.Seg3_PORT, pInfo->Port.Seg3_Pin);			//SEG1
					break;
		default: break;		
	}
}
/*******************************************************************************
*函数名			:	CD4511_Clear
*功能描述		:	function
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
void CD4511_Clear(CD4511Def *pInfo)		//清除输出：bitA~bitG输出低电平
{
	GPIO_ResetBits(pInfo->Port.A0_PORT, pInfo->Port.A0_Pin);			//A/A0
	GPIO_SetBits	(pInfo->Port.A1_PORT, pInfo->Port.A1_Pin);			//B/A1
	GPIO_ResetBits(pInfo->Port.A2_PORT, pInfo->Port.A2_Pin);			//C/A2
	GPIO_SetBits	(pInfo->Port.A3_PORT, pInfo->Port.A3_Pin);			//D/A3
	
//	GPIO_ResetBits(pInfo->Port.Seg1_PORT, pInfo->Port.Seg1_Pin);			//C/A2
//	GPIO_ResetBits(pInfo->Port.Seg2_PORT, pInfo->Port.Seg2_Pin);			//C/A2
//	GPIO_ResetBits(pInfo->Port.Seg3_PORT, pInfo->Port.Seg3_Pin);			//C/A2
	
//	unsigned char		i	=	0;
//	unsigned long		*Port			=	NULL;
//	unsigned short 	*Pin			=	NULL;					//GPIO_Pin_x
//	
//	Port	=	(unsigned long*)&(pInfo->Port.A0_PORT);
//	Pin		=	(unsigned short*)&(pInfo->Port.A0_Pin);
//	GPIO_ResetBits(pInfo->Port.A0_PORT, pInfo->Port.A0_Pin);			//A/A0
//	GPIO_SetBits	(pInfo->Port.A1_PORT, pInfo->Port.A1_Pin);			//B/A1
//	GPIO_ResetBits(pInfo->Port.A2_PORT, pInfo->Port.A2_Pin);			//C/A2
//	GPIO_SetBits	(pInfo->Port.A3_PORT, pInfo->Port.A3_Pin);			//D/A3
	
//	for(i	=	0;	i<pInfo->Data.Num;	i++)
//	{
//		GPIO_ResetBits((GPIO_TypeDef*)(*Port), (unsigned short)*Pin);
//		Port	+=	2;
//		Pin		+=	2;
//	}
}
/*******************************************************************************
*函数名			:	CD4511_Clear
*功能描述		:	function
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
void CD4511_WriteData(CD4511Def *pInfo,unsigned short num)		//BCD转换为Segment输出 只输出0~9
{
	pInfo->Data.Data	=	num;
//	CD4511BcdDef*	CD4511Bcd;		//BCD码结构体
//	
//	num	=	num%10;			//限定在1位数
//	
//	CD4511Bcd	=	(CD4511BcdDef*)&num;				//转换为BCD码
//	
//	if(CD4511Bcd->A)
//	{
//		GPIO_SetBits(pInfo->Port.A0_PORT, pInfo->Port.A0_Pin);
//	}
//	else
//	{
//		GPIO_ResetBits(pInfo->Port.A0_PORT, pInfo->Port.A0_Pin);			//A/A0
//	}
//	if(CD4511Bcd->B)
//	{
//		GPIO_SetBits(pInfo->Port.A1_PORT, pInfo->Port.A1_Pin);
//	}
//	else
//	{
//		GPIO_ResetBits(pInfo->Port.A1_PORT, pInfo->Port.A1_Pin);			//B/A1
//	}
//	if(CD4511Bcd->C)
//	{
//		GPIO_SetBits(pInfo->Port.A2_PORT, pInfo->Port.A2_Pin);
//	}
//	else
//	{
//		GPIO_ResetBits(pInfo->Port.A2_PORT, pInfo->Port.A2_Pin);			//C/A2
//	}
//	if(CD4511Bcd->D)
//	{
//		GPIO_SetBits(pInfo->Port.A3_PORT, pInfo->Port.A3_Pin);
//	}
//	else
//	{
//		GPIO_ResetBits(pInfo->Port.A3_PORT, pInfo->Port.A3_Pin);			//D/A3
//	}
}
/*******************************************************************************
*函数名			:	CD4511_Clear
*功能描述		:	function
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
void CD4511_WriteDataNum(CD4511Def *pInfo,unsigned short num)		//BCD转换为Segment输出 只输出0~9
{
	CD4511BcdDef*	CD4511Bcd;		//BCD码结构体
	
	num	=	num%10;			//限定在1位数
	
	CD4511Bcd	=	(CD4511BcdDef*)&num;				//转换为BCD码
	
	if(CD4511Bcd->A)
	{
		GPIO_SetBits(pInfo->Port.A0_PORT, pInfo->Port.A0_Pin);
	}
	else
	{
		GPIO_ResetBits(pInfo->Port.A0_PORT, pInfo->Port.A0_Pin);			//A/A0
	}
	if(CD4511Bcd->B)
	{
		GPIO_SetBits(pInfo->Port.A1_PORT, pInfo->Port.A1_Pin);
	}
	else
	{
		GPIO_ResetBits(pInfo->Port.A1_PORT, pInfo->Port.A1_Pin);			//B/A1
	}
	if(CD4511Bcd->C)
	{
		GPIO_SetBits(pInfo->Port.A2_PORT, pInfo->Port.A2_Pin);
	}
	else
	{
		GPIO_ResetBits(pInfo->Port.A2_PORT, pInfo->Port.A2_Pin);			//C/A2
	}
	if(CD4511Bcd->D)
	{
		GPIO_SetBits(pInfo->Port.A3_PORT, pInfo->Port.A3_Pin);
	}
	else
	{
		GPIO_ResetBits(pInfo->Port.A3_PORT, pInfo->Port.A3_Pin);			//D/A3
	}
}
/*******************************************************************************
* 函数名			:	CD4511_DisplayOFF
* 功能描述		:	关闭显示---关NPN三极管
* 输入			: void
* 返回值			: void
*******************************************************************************/
void CD4511_DisplayOFF(CD4511Def *pInfo)			//关闭显示---关NPN三极管
{
	GPIO_ResetBits(pInfo->Port.Seg1_PORT,pInfo->Port.Seg1_Pin);
	GPIO_ResetBits(pInfo->Port.Seg2_PORT,pInfo->Port.Seg2_Pin);
	GPIO_ResetBits(pInfo->Port.Seg3_PORT,pInfo->Port.Seg3_Pin);
	CD4511_Delay(1000);
}
/*******************************************************************************
* 函数名			:	CD4511_DisplayOFF
* 功能描述		:	关闭显示---关NPN三极管
* 输入			: void
* 返回值			: void
*******************************************************************************/
void CD4511_DisplayON(CD4511Def *pInfo)			//开显示---关NPN三极管
{
	GPIO_SetBits(pInfo->Port.Seg1_PORT,pInfo->Port.Seg1_Pin);
	GPIO_SetBits(pInfo->Port.Seg2_PORT,pInfo->Port.Seg2_Pin);
	GPIO_SetBits(pInfo->Port.Seg3_PORT,pInfo->Port.Seg3_Pin);
	CD4511_Delay(1000);
}
