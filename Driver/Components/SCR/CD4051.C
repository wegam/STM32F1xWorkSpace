/******************************** User_library *********************************
* 文件名 	: CD4051单端8通道多路开关
* 作者   	: wegam@sina.com
* 版本   	: V
* 日期   	: 2016/01/01
* 说明   	: 
********************************************************************************
* CD4051是单端8通道多路开关，它有3个通道选择输入端C、B、A 和一个禁止输入
* 端INH。C、B、A 用来选译通道号，INH 用来控制CD4051是否有效。INH=“1”，
* 即INH=Vp时，所有通道均断开，禁止模拟量输入;当INH=“O”,即INH=Vss 时，
* 通道接通，允许模拟量输入。输入数字信号的范围是Vop~-Vss(3-15V).
* 输入模拟信号的范围是LYm(-15~15V)。所以，用户可以根据自己的输入信号范围
* 和数字控制信号的逻辑电平来选择VP、VSS、VeE 的电压值。
* 例如，如果Vob=5V,Vss=0V,Y=-5v,此时数字信号为0~5V,模拟信号的范围为-5V~+5V。
*******************************************************************************/



#include "CD4051.H"
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
void CD4051_Delay(u32 time)
{
	while(time--);
}
/*******************************************************************************
*函数名			:	function
*功能描述		:	函数功能说明
*输入				: 
*返回值			:	无
*******************************************************************************/
void CD4051_Initialize(stCD4051Def *pInfo)
{
	GPIO_Configuration_OPP50	(pInfo->Port.A_PORT,		pInfo->Port.A_Pin);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度2MHz----V20170605
	GPIO_Configuration_OPP50	(pInfo->Port.B_PORT,		pInfo->Port.B_Pin);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度2MHz----V20170605
	GPIO_Configuration_OPP50	(pInfo->Port.C_PORT,		pInfo->Port.C_Pin);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度2MHz----V20170605
	GPIO_Configuration_OPP50	(pInfo->Port.EN_PORT,		pInfo->Port.EN_Pin);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度2MHz----V20170605
	
	GPIO_SetBits	(pInfo->Port.EN_PORT, pInfo->Port.EN_Pin);			//B/A1
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
void CD4051_Clear(stCD4051Def *pInfo)		//清除输出：bitA~bitG输出低电平
{
	GPIO_ResetBits(pInfo->Port.A_PORT, pInfo->Port.A_Pin);			//A/A0
	GPIO_SetBits	(pInfo->Port.B_PORT, pInfo->Port.B_Pin);			//B/A1
	GPIO_ResetBits(pInfo->Port.C_PORT, pInfo->Port.C_Pin);			//C/A2
	GPIO_SetBits	(pInfo->Port.EN_PORT, pInfo->Port.EN_Pin);			//D/A3
}
/*******************************************************************************
*函数名			:	CD4051_WriteChannel
*功能描述		:	打开相应通道号，只能打开一个
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
void CD4051_WriteChannel(stCD4051Def *pInfo,unsigned char nChannel)
{
	GPIO_ResetBits(pInfo->Port.A_PORT, pInfo->Port.A_Pin);			//A/A0
	GPIO_ResetBits(pInfo->Port.B_PORT, pInfo->Port.B_Pin);			//A/A0
	GPIO_ResetBits(pInfo->Port.C_PORT, pInfo->Port.C_Pin);			//A/A0
	
	if(nChannel&0x01)
	{
		GPIO_SetBits(pInfo->Port.A_PORT, pInfo->Port.A_Pin);			//A/A0
	}
	if(nChannel&0x02)
	{
		GPIO_SetBits(pInfo->Port.B_PORT, pInfo->Port.B_Pin);			//A/A0
	}
	if(nChannel&0x04)
	{
		GPIO_SetBits(pInfo->Port.C_PORT, pInfo->Port.C_Pin);			//A/A0
	}
}
