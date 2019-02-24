#include "STM32_WOW.H"

#include "STM32_USART.H"
#include "STM32_WDG.H"




/*******************************************************************************
* 函数名	:	WOW_Configuration
* 功能描述	:	配置函数	 
* 输入		:	
* 输出		:
* 返回 		:
*******************************************************************************/
void WOW_Configuration(void)
{
//	GPIO_DeInit(GPIOA);
//	GPIO_DeInit(GPIOB);
//	GPIO_DeInit(GPIOC);
//	GPIO_DeInit(GPIOD);
//	GPIO_DeInit(GPIOE);
//	GPIO_DeInit(GPIOF);
//	GPIO_DeInit(GPIOG);
	
//	IWDG_Configuration(5000);	//独立看门狗配置 1000ms
	
//	SysTick_Configuration(1000);	//系统嘀嗒时钟配置72MHz,单位为uS
	

	
//***********************************TEST***********************************//
#ifdef DEMO	
	DEMO_Configuration();
#endif
	
//***********************************CS5530_DEMO***********************************//
#ifdef CS5530_DEMO	
	CS5530Demo_Configuration();
#endif
//***********************************TEST***********************************//
#ifdef TEST	
	TEST_Configuration();
#endif	
//***********************************数字调音板配置程序***********************************//
#ifdef R2A15908SP	
	R2A15908SP_Configuration();
#endif
//***********************************串口测试配置程序***********************************//
#ifdef USART_TEST	
	Usart_test_Configuration();
#endif
//***********************************7寸LCD配置程序***********************************//
#ifdef STM32_LCD	
	STM32_LCD_Configuration();
#endif
//***********************************ADC_TEST***********************************//
#ifdef ADC_TEST	
	ADC_TEST_Configuration();
#endif
//***********************************DAC_TEST***********************************//
#ifdef DAC_TEST	
	DAC_TEST_Configuration();
#endif
	
//***********************************ADC_TEST***********************************//
#ifdef ADC_Temperature	
	ADC_Temperature_Configuration();
#endif
//***********************************ADC_TEST***********************************//
#ifdef CAN_TEST	
	CAN_TEST_Configuration();
#endif
//***********************************ADC_TEST***********************************//
#ifdef SPI_TEST	
	SPI_TEST_Configuration();
#endif
//***********************************SPI_FLASH***********************************//
#ifdef OFFLINE_ISP
	OFFLINE_ISP_Configuration();
#endif

////***********************************ADC_TEST***********************************//
//#ifdef MS0800_WOW	
//	MS0800_WOW_Configuration();
//#endif

//***********************************ADC_TEST***********************************//
#ifdef CD4511BM_TEST	
	CD4511BM_TEST_Configuration();
#endif

//***********************************ADC_TEST***********************************//
#ifdef MS0800_PL001V20	
	MS0800_PL001V20_Configuration();
#endif

//***********************************ADC_TEST***********************************//
#ifdef MS0800_PC004V10	
	MS0800_PC004V10_Configuration();
#endif

//***********************************ADC_TEST***********************************//
#ifdef MS0800_PM001V20	
	MS0800_PM001V20_Configuration();
#endif

//***********************************ADC_TEST***********************************//
#ifdef MX25L4006E	
	MX25L4006E_Configuration();
#endif

//***********************************ADC_TEST***********************************//
#ifdef TM1618	
	TM1618_Configuration();
#endif
//***********************************TM1638_TEST***********************************//
#ifdef TM1638_TEST	
	TM1638_Configuration();
#endif

//***********************************VirtualCom***********************************//
#ifdef VirtualCom	
	VirtualCom_Configuration();
#endif

//***********************************USBtoSPI***********************************//
#ifdef USBtoSPI	
	USBtoSPI_Configuration();
#endif

//***********************************SPItoUSART***********************************//
#ifdef SPItoUSART	
	SPItoUSART_Configuration();
#endif

//***********************************SysTick_TEST***********************************//
#ifdef SysTick_TEST	
	SysTick_TEST_Configuration();
#endif

//***********************************SteepMotorTest***********************************//
#ifdef SteepMotorTest	
	SteepMotorTest_Configuration();
#endif
//***********************************PWM_TEST***********************************//
#ifdef PWM_TEST
	PWM_TEST_Configuration();
#endif

//***********************************PwrTest***********************************//
#ifdef PwrTest
	PwrTest_Configuration();
#endif
//***********************************TIM_TEST***********************************//
#ifdef TIM_TEST
	TIM_TEST_Configuration();
#endif
//********************************OLED096_TEST*********************************//
#ifdef OLED096_TEST
	OLED096_TEST_Configuration();
#endif

//*********************************LK3U_40MR*********************************//
#ifdef LK3U_40MR
	LK3U_40MR_Configuration();
#endif

//*********************************FX2N_14MR*********************************//
#ifdef FX2N_14MR
	FX2N_14MR_Configuration();
#endif

//*********************************A3987_TEST*********************************//
#ifdef A3987_TEST
	A3987_TEST_Configuration();
#endif

//*********************************Buzzer_TEST*********************************//
#ifdef Buzzer_TEST
	Buzzer_TEST_Configuration();
#endif

//*********************************PWM_LED*********************************//
#ifdef PWM_LED
	PWM_LED_Configuration();
#endif

//*********************************STM32F103C8T6核心板*********************************//
#ifdef STM32F103C8T6
	STM32F103C8T6_Configuration();
#endif

//*********************************STM32F4DISCOVERY评估板*********************************//
#ifdef STM32F4DISCOVERY
	STM32F4DISCOVERY_Configuration();
#endif

//*********************************Audio_Speaker*********************************//
#ifdef Audio_Speaker
	Audio_Speaker_Configuration();
#endif

//*********************************Audio_Speaker_WOW*********************************//
#ifdef Audio_Speaker_WOW
	Audio_Speaker_Configuration();
#endif
//*********************************Custom_HID*********************************//
#ifdef Custom_HID
	Custom_HID_Configuration();
#endif

//*********************************Device_Firmware_Upgrade*********************************//
#ifdef Device_Firmware_Upgrade
	Device_Firmware_Upgrade_Configuration();
#endif

//*********************************JoyStickMouse*********************************//
#ifdef JoyStickMouse
	JoyStickMouse_Configuration();
#endif

//*********************************Mass_Storage*********************************//
#ifdef Mass_Storage
	Mass_Storage_Configuration();
#endif

//*********************************Virtual_COM_Port*********************************//
#ifdef Virtual_COM_Port
	Virtual_COM_Port_Configuration();
#endif

//*********************************Virtual_COM_Port_IAD*********************************//
#ifdef Virtual_COM_Port_IAD
	Virtual_COM_Port_IAD_Configuration();
#endif

//*********************************ICCARD*********************************//
#ifdef ICCARD
	ICCARD_Configuration();
#endif

//*********************************IAP*********************************//
#ifdef IAP
	IAP_Configuration();
#endif

//*********************************SWDTEST*********************************//
#ifdef SWDTEST
	SWDTEST_Configuration();
#endif


//*********************************FatFsTest*********************************//
#ifdef FatFsTest
	FatFsTest_Configuration();
#endif

//*********************************MmcSDTest*********************************//
#ifdef MmcSDTest
	MmcSDTest_Configuration();
#endif
//*********************************FSMCTest*********************************//
#ifdef FSMCTest
	FSMCTest_Configuration();
#endif

//*********************************AMPTest*********************************//
#ifdef AMPTest
	AMPTest_Configuration();
#endif
//*********************************USBDEMO*********************************//
#ifdef USBDEMO
	USBDEMO_Configuration();
#endif

//*********************************AMP01*********************************//
#ifdef AMP01
	AMP01_Configuration();
#endif


//*********************************AMPLED02V13*********************************//
#ifdef AMPLED02V13
	AMPLED02_Configuration();
#endif

//*********************************TLE5012B*********************************//
#ifdef TLE5012B
	TLE5012B_Configuration();
#endif

//*********************************TLE5012BV2*********************************//
#ifdef TLE5012BV2
	TLE5012BV2_Configuration();
#endif
//*********************************Vl53l0x_TEST*********************************//
#ifdef Vl53l0x_TEST
	Vl53l0xTest_Configuration();
#endif

//*********************************EepromTest*********************************//
#ifdef EepromTest
	EepromTest_Configuration();
#endif

//*********************************IOTReaderTest*********************************//
#ifdef IOTReaderTest
	IOTReaderTest_Configuration();
#endif

}













/*******************************************************************************
* 函数名	:	WOW_Server
* 功能描述	:	服务函数 
* 输入		:	
* 输出		:
* 返回 		:
*******************************************************************************/
void WOW_Server(void)
{
//	IWDG_Feed();								//独立看门狗喂狗
  MainServer();          //

//***********************************数字调音板服务程序***********************************//
#ifdef DEMO
	DEMO_Server();
#endif

//***********************************CS5530_DEMO***********************************//
#ifdef CS5530_DEMO
	CS5530Demo_Server();
#endif
//***********************************数字调音板服务程序***********************************//
#ifdef TEST
	TEST_Server();
#endif
//***********************************数字调音板服务程序***********************************//
#ifdef R2A15908SP	
	R2A15908SP_Server();
#endif
//***********************************串口测试服务程序***********************************//
#ifdef USART_TEST	
	Usart_test_Server();
#endif
//***********************************7寸LCD配置程序***********************************//
#ifdef STM32_LCD	
	STM32_LCD_Server();
#endif
//***********************************ADC_TEST***********************************//
#ifdef ADC_TEST	
	ADC_TEST_Server();
#endif
//***********************************DAC_TEST***********************************//
#ifdef DAC_TEST	
	DAC_TEST_Server();
#endif

//***********************************ADC_TEST***********************************//
#ifdef ADC_Temperature	
	ADC_Temperature_Server();
#endif
//***********************************ADC_TEST***********************************//
#ifdef CAN_TEST	
	CAN_TEST_Server();
#endif

//***********************************ADC_TEST***********************************//
#ifdef SPI_TEST	
	SPI_TEST_Server();
#endif
//***********************************OFFLINE_ISP***********************************//
#ifdef OFFLINE_ISP
	OFFLINE_ISP_Server();
#endif
//***********************************ADC_TEST***********************************//
//#ifdef MS0800_WOW	
//	MS0800_WOW_Server();
//#endif

//***********************************ADC_TEST***********************************//
#ifdef CD4511BM_TEST	
	CD4511BM_TEST_Server();
#endif

//***********************************ADC_TEST***********************************//
#ifdef MS0800_PL001V20	
	MS0800_PL001V20_Server();
#endif

//***********************************ADC_TEST***********************************//
#ifdef MS0800_PC004V10	
	MS0800_PC004V10_Server();
#endif

//***********************************ADC_TEST***********************************//
#ifdef MS0800_PM001V20	
	MS0800_PM001V20_Server();
#endif

//***********************************ADC_TEST***********************************//
#ifdef MX25L4006E	
	MX25L4006E_Server();
#endif

//***********************************ADC_TEST***********************************//
#ifdef TM1618	
	TM1618_Server();
#endif

//***********************************TM1638_TEST***********************************//
#ifdef TM1638_TEST	
	TM1638_Server();
#endif

//***********************************VirtualCom***********************************//
#ifdef VirtualCom	
	VirtualCom_Server();
#endif

//***********************************USBtoSPI***********************************//
#ifdef USBtoSPI	
	USBtoSPI_Server();
#endif

//***********************************SPItoUSART***********************************//
#ifdef SPItoUSART	
	SPItoUSART_Server();
#endif
//***********************************SysTick_TEST***********************************//
#ifdef SysTick_TEST	
	SysTick_TEST_Server();
#endif

//***********************************SteepMotorTest***********************************//
#ifdef SteepMotorTest	
	SteepMotorTest_Server();
#endif
//***********************************PWM_TEST***********************************//
#ifdef PWM_TEST	
	PWM_TEST_Server();
#endif

//***********************************PwrTest***********************************//
#ifdef PwrTest	
	PwrTest_Server();
#endif
//***********************************TIM_TEST***********************************//
#ifdef TIM_TEST	
	TIM_TEST_Server();
#endif

//********************************OLED096_TEST*********************************//
#ifdef OLED096_TEST
	OLED096_TEST_Server();
#endif
//*********************************LK3U_40MR*********************************//
#ifdef LK3U_40MR
	LK3U_40MR_Server();
#endif
//*********************************FX2N_14MR*********************************//
#ifdef FX2N_14MR
	FX2N_14MR_Server();
#endif

//*********************************A3987_TEST*********************************//
#ifdef A3987_TEST
	A3987_TEST_Server();
#endif

//*********************************Buzzer_TEST*********************************//
#ifdef Buzzer_TEST
	Buzzer_TEST_Server();
#endif

//*********************************PWM_LED*********************************//
#ifdef PWM_LED
	PWM_LED_Server();
#endif

//*********************************STM32F103C8T6核心板*********************************//
#ifdef STM32F103C8T6
	STM32F103C8T6_Server();
#endif

//*********************************STM32F4DISCOVERY评估板*********************************//
#ifdef STM32F4DISCOVERY
	STM32F4DISCOVERY_Server();
#endif

//*********************************Audio_Speaker*********************************//
#ifdef Audio_Speaker
	Audio_Speaker_Server();
#endif

//*********************************Audio_Speaker_WOW*********************************//
#ifdef Audio_Speaker
	Audio_Speaker_Server();
#endif
//*********************************Custom_HID*********************************//
#ifdef Custom_HID
	Custom_HID_Server();
#endif

//*********************************Device_Firmware_Upgrade*********************************//
#ifdef Device_Firmware_Upgrade
	Device_Firmware_Upgrade_Server();
#endif

//*********************************JoyStickMouse*********************************//
#ifdef JoyStickMouse
	JoyStickMouse_Server();
#endif

//*********************************Mass_Storage*********************************//
#ifdef Mass_Storage
	Mass_Storage_Server();
#endif

//*********************************Virtual_COM_Port*********************************//
#ifdef Virtual_COM_Port
	Virtual_COM_Port_Server();
#endif

//*********************************Virtual_COM_Port_IAD*********************************//
#ifdef Virtual_COM_Port_IAD
	Virtual_COM_Port_IAD_Server();
#endif

//*********************************ICCARD*********************************//
#ifdef ICCARD
	ICCARD_Server();
#endif

//*********************************IAP*********************************//
#ifdef IAP
	IAP_Server();
#endif

//*********************************SWDTEST*********************************//
#ifdef SWDTEST
	SWDTEST_Server();
#endif

//*********************************FatFsTest*********************************//
#ifdef FatFsTest
	FatFsTest_Server();
#endif
//*********************************MmcSDTest*********************************//
#ifdef MmcSDTest
	MmcSDTest_Server();
#endif
//*********************************FSMCTest*********************************//
#ifdef FSMCTest
	FSMCTest_Server();
#endif
//*********************************AMPTest*********************************//
#ifdef AMPTest
	AMPTest_Server();
#endif

//*********************************USBDEMO*********************************//
#ifdef USBDEMO
	USBDEMO_Server();
#endif

//*********************************AMP01*********************************//
#ifdef AMP01
	AMP01_Server();
#endif

//*********************************AMPLED02V13*********************************//
#ifdef AMPLED02V13
	AMPLED02_Server();
#endif
//*********************************TLE5012B*********************************//
#ifdef TLE5012B
	TLE5012B_Server();
#endif

//*********************************TLE5012BV2*********************************//
#ifdef TLE5012BV2
	TLE5012BV2_Server();
#endif
//*********************************Vl53l0x_TEST*********************************//
#ifdef Vl53l0x_TEST
	Vl53l0xTest_Server();
#endif

//*********************************EepromTest*********************************//
#ifdef EepromTest
	EepromTest_Server();
#endif


//*********************************IOTReaderTest*********************************//
#ifdef IOTReaderTest
	IOTReaderTest_Server();
#endif
//IWDG_Feed();								//独立看门狗喂狗

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
void MainServer(void)
{
  IWDG_Feed();			  //独立看门狗喂狗
  USART_Process();     //串口服务程序
}




