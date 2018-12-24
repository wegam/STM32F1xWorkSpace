/**
  ******************************************************************************
  * @file    vl53l0x.c
  * @author  MCD Application Team
  * @version V2.0.0
  * @date    26-June-2015
  * @brief   This file provides a set of functions needed to manage the L3GD20,
  *          ST MEMS motion sensor, 3-axis digital output gyroscope.  
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2015 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "vl53l0x.h"


#include "STM32_GPIO.H"


stvl53l0xDef* vl53l0x;

void vl53l0x_WriteEn(void);
void vl53l0x_ReadEn(void);

void vl53l0x_SDAHigh(void);
void vl53l0x_SDALow(void);
void vl53l0x_SCLHigh(void);
void vl53l0x_SCLLow(void);
unsigned	char vl53l0x_ReadBit(void);
/*******************************************************************************
* 函数名			:	function
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
void vl53l0x_Initialize(stvl53l0xDef* pInfo)
{
	vl53l0x	=	pInfo;
	GPIO_Configuration_OPP50(pInfo->Port.SDA_Port,pInfo->Port.SDA_Pin);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度2MHz----V20170605
	GPIO_Configuration_OPP50(pInfo->Port.SCL_Port,pInfo->Port.SCL_Pin);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度2MHz----V20170605
	
	vl53l0x->i2c.SDAWriteEn	=	vl53l0x_WriteEn;
	vl53l0x->i2c.SDAReadEn		=	vl53l0x_ReadEn;	
	vl53l0x->i2c.SDAHigh			=	vl53l0x_SDAHigh;
	vl53l0x->i2c.SDALow			=	vl53l0x_SDALow;
	vl53l0x->i2c.SCLHigh			=	vl53l0x_SCLHigh;
	vl53l0x->i2c.SCLLow			=	vl53l0x_SCLLow;
	vl53l0x->i2c.SDAStd			=	vl53l0x_ReadBit;
	
	IIC_Initialize(&vl53l0x->i2c);
}
/*******************************************************************************
* 函数名			:	function
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
void vl53l0x_WriteEn(void)
{
	GPIO_Configuration_OPP50(vl53l0x->Port.SDA_Port,vl53l0x->Port.SDA_Pin);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度2MHz----V20170605
}
/*******************************************************************************
* 函数名			:	function
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
void vl53l0x_ReadEn(void)
{
	GPIO_Configuration_IPU(vl53l0x->Port.SDA_Port,vl53l0x->Port.SDA_Pin);			//将GPIO相应管脚配置为上拉输入模式----V20170605
}
/*******************************************************************************
* 函数名			:	function
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
void vl53l0x_SDAHigh(void)
{
	vl53l0x->Port.SDA_Port->BSRR = vl53l0x->Port.SDA_Pin;
}
/*******************************************************************************
* 函数名			:	function
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
void vl53l0x_SDALow(void)
{
	vl53l0x->Port.SDA_Port->BRR = vl53l0x->Port.SDA_Pin;
}
/*******************************************************************************
* 函数名			:	function
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
void vl53l0x_SCLHigh(void)
{
	vl53l0x->Port.SCL_Port->BSRR = vl53l0x->Port.SCL_Pin;
}
/*******************************************************************************
* 函数名			:	function
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
void vl53l0x_SCLLow(void)
{
	vl53l0x->Port.SCL_Port->BRR = vl53l0x->Port.SCL_Pin;
}
/*******************************************************************************
* 函数名			:	function
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
unsigned char vl53l0x_ReadBit(void)
{
	return(vl53l0x->Port.SDA_Port->IDR &vl53l0x->Port.SDA_Pin);
}
/*******************************************************************************
* 函数名			:	function
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
unsigned char vl53l0x_ReadData(void)
{
	unsigned char data=0;
	vl53l0x->i2c.Start();
	vl53l0x->i2c.WriteOneByte(0x52);
	if(0	==	vl53l0x->i2c.WaitAck())	//有应答
	{
		data	=	vl53l0x->i2c.ReadOneByte();
		vl53l0x->i2c.WaitAck();		
	}
	
	vl53l0x->i2c.Start();
	vl53l0x->i2c.WriteOneByte(0x53);
	vl53l0x->i2c.WaitAck();
	
	data	=	vl53l0x->i2c.ReadOneByte();
	vl53l0x->i2c.NAck();
	
	data	=	vl53l0x->i2c.ReadOneByte();
	vl53l0x->i2c.NAck();
	
	data	=	vl53l0x->i2c.ReadOneByte();
	vl53l0x->i2c.NAck();
	
	data	=	vl53l0x->i2c.ReadOneByte();
	vl53l0x->i2c.NAck();
	
	data	=	vl53l0x->i2c.ReadOneByte();
	vl53l0x->i2c.NAck();

	vl53l0x->i2c.Stop();
	
	return	data;
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/     
