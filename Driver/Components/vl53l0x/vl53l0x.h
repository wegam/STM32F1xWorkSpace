/**
  ******************************************************************************
  * @file    vl53l0x.h
  * @author  MCD Application Team
  * @version V2.0.0
  * @date    26-June-2015
  * @brief   This file contains all the functions prototypes for the l3gd20.c driver.
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
  

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __vl53l0x_H
#define __vl53l0x_H

#include "stm32f10x_gpio.h"

#include	"IIC.H"


//可以帮助你，从arduino网站获得
// 从API vl53l0x_device.h注册地址（按此处列出的那样排序）
// 枚举
enum regAddr
{
 SYSRANGE_START = 0x00 ,
	SYSTEM_THRESH_HIGH =  0x0C,
	SYSTEM_THRESH_LOW = 0x0E,
	SYSTEM_SEQUENCE_CONFIG = 0x01,
	SYSTEM_RANGE_CONFIG =  0x09,
	SYSTEM_INTERMEASUREMENT_PERIOD =0x04,
	SYSTEM_INTERRUPT_CONFIG_GPIO = 0x0A,
	GPIO_HV_MUX_ACTIVE_HIGH = 0x84,
	SYSTEM_INTERRUPT_CLEAR =  0x0B,
	RESULT_INTERRUPT_STATUS = 0x13,
	RESULT_RANGE_STATUS = 0x14,
	RESULT_CORE_AMBIENT_WINDOW_EVENTS_RTN =0xBC,
	RESULT_CORE_RANGING_TOTAL_EVENTS_RTN = 0xC0,
	RESULT_CORE_AMBIENT_WINDOW_EVENTS_REF = 0xD0,
	RESULT_CORE_RANGING_TOTAL_EVENTS_REF = 0xD4,
	RESULT_PEAK_SIGNAL_RATE_REF = 0xB6,
	ALGO_PART_TO_PART_RANGE_OFFSET_MM = 0x28,
	I2C_SLAVE_DEVICE_ADDRESS = 0x8A,
	MSRC_CONFIG_CONTROL = 0x60,
	PRE_RANGE_CONFIG_MIN_SNR = 0x27,
	PRE_RANGE_CONFIG_VALID_PHASE_LOW = 0x56,
	PRE_RANGE_CONFIG_VALID_PHASE_HIGH = 0x57,
	PRE_RANGE_MIN_COUNT_RATE_RTN_LIMIT = 0x64,
	FINAL_RANGE_CONFIG_MIN_SNR = 0x67,
	FINAL_RANGE_CONFIG_VALID_PHASE_LOW = 0x47,
	FINAL_RANGE_CONFIG_VALID_PHASE_HIGH = 0x48,
	FINAL_RANGE_CONFIG_MIN_COUNT_RATE_RTN_LIMIT = 0x44,
	PRE_RANGE_CONFIG_SIGMA_THRESH_HI = 0x61,
	PRE_RANGE_CONFIG_SIGMA_THRESH_LO = 0x62,
	PRE_RANGE_CONFIG_VCSEL_PERIOD = 0x50,
	PRE_RANGE_CONFIG_TIMEOUT_MACROP_HI = 0x51,
	PRE_RANGE_CONFIG_TIMEOUT_MACROP_LO = 0x52,
	SYSTEM_HISTOGRAM_BIN = 0x81,
	HISTOGRAM_CONFIG_INITIAL_PHASE_SELECT = 0x33,
	HISTOGRAM_CONFIG_READOUT_CTRL = 0x55,
	FINAL_RANGE_CONFIG_VCSEL_PERIOD = 0x70,
	FINAL_RANGE_CONFIG_TIMEOUT_MACROP_HI = 0x71,
	FINAL_RANGE_CONFIG_TIMEOUT_MACROP_LO = 0x72,
	CROSSTALK_COMPENSATION_PEAK_RATE_MCPS = 0x20,
	MSRC_CONFIG_TIMEOUT_MACROP = 0x46,
	SOFT_RESET_GO2_SOFT_RESET_N = 0xBF,
	IDENTIFICATION_MODEL_ID = 0xC0,
	IDENTIFICATION_REVISION_ID = 0xC2,
	OSC_CALIBRATE_VAL = 0xF8,
	GLOBAL_CONFIG_VCSEL_WIDTH = 0x32,
	GLOBAL_CONFIG_SPAD_ENABLES_REF_0 = 0xB0,
	GLOBAL_CONFIG_SPAD_ENABLES_REF_1 = 0xB1,
	GLOBAL_CONFIG_SPAD_ENABLES_REF_2 = 0xB2,
	GLOBAL_CONFIG_SPAD_ENABLES_REF_3 = 0xB3,
	GLOBAL_CONFIG_SPAD_ENABLES_REF_4 = 0xB4,
	GLOBAL_CONFIG_SPAD_ENABLES_REF_5 = 0xB5,
	GLOBAL_CONFIG_REF_EN_START_SELECT = 0xB6,
	DYNAMIC_SPAD_NUM_REQUESTED_REF_SPAD = 0x4E,
	DYNAMIC_SPAD_REF_EN_START_OFFSET = 0x4F,POWER_MANAGEMENT_GO1_POWER_FORCE = 
 0x80
 ,VHV_CONFIG_PAD_SCL_SDA__EXTSUP_HV = 
 0x89
 ,ALGO_PHASECAL_LIM = 
 0x30
 ,ALGO_PHASECAL_CONFIG_TIMEOUT = 
 0x30
 ,}; 



typedef struct _vl53l0x
{
	//-------------------GPIO
	struct
	{
		//SDA
		GPIO_TypeDef* 	SDA_Port;				//GPIOX
		unsigned short 	SDA_Pin;				//GPIO_Pin_x
		
		//SCK
		GPIO_TypeDef* 	SCL_Port;				//GPIOX
		unsigned short 	SCL_Pin;				//GPIO_Pin_x
	}Port;
	I2CHWdef i2c;
}stvl53l0xDef;


void vl53l0x_Initialize(stvl53l0xDef* pInfo);
unsigned char vl53l0x_ReadData(void);

#endif /* __L3GD20_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/ 
