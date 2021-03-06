#include "STM32_WOW.H"


//#include "STM32F10x_BitBand.H"
//#include "stm32f10x_map.h"
//#include "STM32_WDG.H"
//#include "STM32_SYSTICK.H"
//#include "STM32_SYS.H"



//#ifndef	Usart_Test
//#define	Usart_Test
//	#include "USART_TEST.H"
//#endif
//#define R2A15908SP
//#define Usart_Test



/*******************************************************************************
* ������	:	WOW_Configuration
* ��������	:	���ú���	 
* ����		:	
* ���		:
* ���� 		:
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
	
//	IWDG_Configuration(5000);	//�������Ź����� 1000ms
	
//	SysTick_Configuration(1000);	//ϵͳ���ʱ������72MHz,��λΪuS
	
	
//***********************************TEST***********************************//
#ifdef DEMO	
	DEMO_Configuration();
#endif
//***********************************TEST***********************************//
#ifdef TEST	
	TEST_Configuration();
#endif	
//***********************************���ֵ��������ó���***********************************//
#ifdef R2A15908SP	
	R2A15908SP_Configuration();
#endif
//***********************************���ڲ������ó���***********************************//
#ifdef USART_TEST	
	Usart_test_Configuration();
#endif
//***********************************7��LCD���ó���***********************************//
#ifdef SSD1963	
	SSD1963_Configuration();
#endif
//***********************************7��LCD���ó���***********************************//
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

//*********************************PM001V20*********************************//
#ifdef PM001V20
	PM001V20_Configuration();
#endif

//*********************************PC001V10*********************************//
#ifdef PC001V10
	PC001V10_Configuration();
#endif

//*********************************PC001V21*********************************//
#ifdef PC001V21
	PC001V21_Configuration();
#endif
//*********************************PC001V25*********************************//
#ifdef PC001V25
	PC001V25_Configuration();
#endif
//*********************************PD002V30*********************************//
#ifdef PD002V30
	PD002V30_Configuration();
#endif

//*********************************PC004V21*********************************//
#ifdef PC004V21
	PC004V21_Configuration();
#endif

//*********************************PC006V20*********************************//
#ifdef PC006V20
	PC006V20_Configuration();
#endif

//*********************************PC016V20*********************************//
#ifdef PC016V20
	PC016V20_Configuration();
#endif

//*********************************PC006V21*********************************//
#ifdef PC006V21
	PC006V21_Configuration();
#endif

//***************************************************PC012V13�������ư�
#ifdef PC012V13
	PC012V13_Configuration();
#endif

//*********************************PC018V10*********************************//
#ifdef PC018V10
	PC018V10_Configuration();
#endif

//*********************************PD003V11*********************************//
#ifdef PD003V11
	PD003V11_Configuration();
#endif
//*********************************PD003VG*********************************//
#ifdef PD003VG
	PD003VG_Configuration();
#endif

//*********************************PD004V10*********************************//
#ifdef PD004V10
	PD004V10_Configuration();
#endif

//*********************************PD006V20*********************************//
#ifdef PD006V20
	PD006V20_Configuration();
#endif

//*********************************PD008V11*********************************//
#ifdef PD008V11
	PD008V11_Configuration();
#endif

//*********************************PD010V20*********************************//
#ifdef PD010V20
	PD010V20_Configuration();
#endif

//*********************************PD011V10*********************************//
#ifdef PD011V10
	PD011V10_Configuration();
#endif

//*********************************PD014V14*********************************//
#ifdef PD014V14
	PD014V14_Configuration();
#endif

//*********************************PD014V15*********************************//
#ifdef PD014V15
	PD014V14_Configuration();
#endif

//*********************************PL001V20*********************************//
#ifdef PL001V20
	PL001V20_Configuration();
#endif

//*********************************PL006V10*********************************//
#ifdef PL006V10
	PL006V10_Configuration();
#endif

//*********************************PL010V13*********************************//
#ifdef PL010V13
	PL010V13_Configuration();
#endif

//*********************************PL010V15*********************************//
#ifdef PL010V15
	PL010V15_Configuration();
#endif

//*********************************PL013V10*********************************//
#ifdef PL013V10
	PL013V10_Configuration();
#endif

//*********************************PL013V11*********************************//
#ifdef PL013V11
	PL013V11_Configuration();
#endif

//*********************************PL013V20*********************************//
#ifdef PL013V20
	PL013V20_Configuration();
#endif




//*********************************PM004V10*********************************//
#ifdef PM004V10
	PM004V10_Configuration();
#endif

//*********************************USBTEST_RS485TOUSART*********************************//
#ifdef USBTEST_RS485TOUSART
	USBTEST_RS485TOUSART_Configuration();
#endif

//*********************************PC001V22*********************************//
#ifdef PC001V22
	PC001V22_Configuration();
#endif

//*********************************PWM_LED*********************************//
#ifdef PWM_LED
	PWM_LED_Configuration();
#endif

//*********************************STM32F103C8T6���İ�*********************************//
#ifdef STM32F103C8T6
	STM32F103C8T6_Configuration();
#endif

//*********************************STM32F4DISCOVERY������*********************************//
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






}













/*******************************************************************************
* ������	:	WOW_Server
* ��������	:	������ 
* ����		:	
* ���		:
* ���� 		:
*******************************************************************************/
void WOW_Server(void)
{
//	IWDG_Feed();								//�������Ź�ι��

//***********************************���ֵ�����������***********************************//
#ifdef DEMO
	DEMO_Server();
#endif
	
//***********************************���ֵ�����������***********************************//
#ifdef TEST
	TEST_Server();
#endif
//***********************************���ֵ�����������***********************************//
#ifdef R2A15908SP	
	R2A15908SP_Server();
#endif
//***********************************���ڲ��Է������***********************************//
#ifdef USART_TEST	
	Usart_test_Server();
#endif
//***********************************7��LCD�������***********************************//
#ifdef SSD1963	
//	SSD1963_Server();
#endif
//***********************************7��LCD���ó���***********************************//
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

//*********************************PM001V20*********************************//
#ifdef PM001V20
	PM001V20_Server();
#endif

//*********************************PC001V10*********************************//
#ifdef PC001V10
	PC001V10_Server();
#endif

//*********************************PC001V21*********************************//
#ifdef PC001V21
	PC001V21_Server();
#endif
//*********************************PC001V25*********************************//
#ifdef PC001V25
	PC001V25_Server();
#endif

//*********************************PD002V30*********************************//
#ifdef PD002V30
	PD002V30_Server();
#endif

//*********************************PL001V20*********************************//
#ifdef PL001V20
	PL001V20_Server();
#endif

//*********************************PC006V20*********************************//
#ifdef PC006V20
	PC006V20_Server();
#endif

//*********************************PC006V21*********************************//
#ifdef PC006V21
	PC006V21_Server();
#endif

//*********************************PC012V13*********************************//
#ifdef PC012V13
	PC012V13_Server();
#endif

//*********************************PC016V20*********************************//
#ifdef PC016V20
	PC016V20_Server();
#endif

//*********************************PC018V10*********************************//
#ifdef PC018V10
	PC018V10_Server();
#endif

//*********************************PL006V10*********************************//
#ifdef PL006V10
	PL006V10_Server();
#endif

//*********************************PD011V10*********************************//
#ifdef PD008V11
	PD008V11_Server();
#endif
//*********************************PD010V20*********************************//
#ifdef PD010V20
	PD010V20_Server();
#endif

//*********************************PD011V10*********************************//
#ifdef PD011V10
	PD011V10_Server();
#endif

//*********************************PD006V20*********************************//
#ifdef PD006V20
	PD006V20_Server();
#endif

//*********************************PD004V10*********************************//
#ifdef PD004V10
	PD004V10_Server();
#endif

//*********************************PL010V13*********************************//
#ifdef PL010V13
	PL010V13_Server();
#endif

//*********************************PL010V15*********************************//
#ifdef PL010V15
	PL010V15_Server();
#endif

//*********************************PL013V10*********************************//
#ifdef PL013V10
	PL013V10_Server();
#endif

//*********************************PL013V11*********************************//
#ifdef PL013V11
	PL013V11_Server();
#endif

//*********************************PL013V20*********************************//
#ifdef PL013V20
	PL013V20_Server();
#endif

//*********************************PC004V21*********************************//
#ifdef PC004V21
	PC004V21_Server();
#endif

//*********************************PD003V11*********************************//
#ifdef PD003V11
	PD003V11_Server();
#endif
//*********************************PD003VG*********************************//
#ifdef PD003VG
	PD003VG_Server();
#endif

//*********************************PD014V14*********************************//
#ifdef PD014V14
	PD014V14_Server();
#endif

//*********************************PD014V15*********************************//
#ifdef PD014V15
	PD014V14_Server();
#endif

//*********************************PM004V10*********************************//
#ifdef PM004V10
	PM004V10_Server();
#endif

//*********************************USBTEST_RS485TOUSART*********************************//
#ifdef USBTEST_RS485TOUSART
	USBTEST_RS485TOUSART_Server();
#endif

//*********************************PC001V22*********************************//
#ifdef PC001V22
	PC001V22_Server();
#endif

//*********************************PWM_LED*********************************//
#ifdef PWM_LED
	PWM_LED_Server();
#endif

//*********************************STM32F103C8T6���İ�*********************************//
#ifdef STM32F103C8T6
	STM32F103C8T6_Server();
#endif

//*********************************STM32F4DISCOVERY������*********************************//
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




//IWDG_Feed();								//�������Ź�ι��

}




