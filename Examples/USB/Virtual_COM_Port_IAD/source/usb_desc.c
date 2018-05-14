/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : usb_desc.c
* Author             : MCD Application Team
* Version            : V2.2.0
* Date               : 06/13/2008
* Description        : Descriptors for Virtual Com Port Demo
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/


/******************************** ˵��20160912**********************************
********************************************************************************
* ���ܣ������豸���������������ʹ���
* 
* 
* 
* 
* 
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "usb_lib.h"
#include "usb_desc.h"


/*=================================================================================*/
/*=================================================================================*/
/* USB��׼�豸������*/
const u8 Virtual_Com_Port_DeviceDescriptor[] =								//�豸������--����
  {
    0x12,   /* bLength */																			//��������������--0x12/18���ֽ�
    USB_DEVICE_DESCRIPTOR_TYPE,     /* bDescriptorType */			//���--0X01�豸������
    0x00,
    0x02,   /* bcdUSB = 2.00 */																//���豸����������ݵ�USB�豸˵���汾�ţ�BCD �룩
		#if (USB_MULTI_IF)
			0xEF,   /* bDeviceClass:  */															//�豸���룺0XEF �����豸
			0x02,   /* bDeviceSubClass */															//��������
			0x01,   /* bDeviceProtocol */															//Э����
			0x40,   /* bMaxPacketSize0 */															//�˵�0��������С����8,16,32,64 Ϊ�Ϸ�ֵ��
			0x02,
			0xFF,   /* idVendor = 0x0483 */														//���̱�־����USB-IF��֯��ֵ��
			0x01,
			0x00,   /* idProduct = 0x5740 */													//��Ʒ��־���ɳ��̸�ֵ��
		#else
			0x02,   /* bDeviceClass: CDC */														//�豸���룺0X02 CDC������
			0x02,   /* bDeviceSubClass */															//��������
			0x01,   /* bDeviceProtocol */															//Э����
			0x40,   /* bMaxPacketSize0 */															//�˵�0��������С����8,16,32,64 Ϊ�Ϸ�ֵ��
			0x83,
			0x04,   /* idVendor = 0x0483 */														//���̱�־����USB-IF��֯��ֵ��
			0x40,
			0x57,   /* idProduct = 0x5740 */													//��Ʒ��־���ɳ��̸�ֵ��
		#endif
    0x00,
    0x01,   /* bcdDevice = 2.00 */														//�豸�İ汾��	
    1,              /* Index of string descriptor describing manufacturer */										//����������Ϣ���ַ���������������ֵ��
    2,              /* Index of string descriptor describing product */													//������Ʒ��Ϣ���ִ�������������ֵ��
    3,              /* Index of string descriptor describing the device's serial number */			//�����豸���к���Ϣ���ִ�������������ֵ��
    0x01    /* bNumConfigurations */													//���ܵ�������������Ŀ
  };
const u8 Virtual_Com_Port_QualifierDescriptor[] =								//�豸������--����
  {
    0x0A,   /* bLength */																			//��������������--0x12/18���ֽ�
    0X06,     /* bDescriptorType */			//���--0X00�豸������
    0x00,
    0x02,   /* bcdUSB = 2.00 */																//���豸����������ݵ�USB�豸˵���汾�ţ�BCD �룩
    0x00,   /* bDeviceClass: CDC */														//�豸���룺0X02 CDC������
    0x00,   /* bDeviceSubClass */															//��������
    0x00,   /* bDeviceProtocol */															//Э����
    0x40,   /* bMaxPacketSize0 */															//�˵�0��������С����8,16,32,64 Ϊ�Ϸ�ֵ��
    0x01,
    0x00,   /* idVendor = 0x0483 */														//���̱�־����USB-IF��֯��ֵ��													
  };
	
const u8 Virtual_Com_Port_ConfigDescriptor[] =
{
///* Configuration 1 */
//  USB_CONFIGURATION_DESC_SIZE,       	/* bLength */
//  USB_CONFIGURATION_DESCRIPTOR_TYPE, 	/* bDescriptorType */
//  WBVAL((USB_CONFIGURATION_DESC_SIZE	+	(USB_NUM_INTERFACES/2) * IAD_CDC_IF_DESC_SET_SIZE)),/* wTotalLength */
//  USB_NUM_INTERFACES,                	/* bNumInterfaces */
////	0x02,                	/* bNumInterfaces */
//  0x01,                              	/* bConfigurationValue: 0x01 is used to select this configuration */
//  0x00,                              	/* iConfiguration: no string to describe this configuration */
//  USB_CONFIG_BUS_POWERED,							/* bmAttributes USB_CONFIG_REMOTE_WAKEUP*/
//  USB_CONFIG_POWER_MA(100),          	/* bMaxPower, device power consumption is 100 mA */
	
	Multiple_CONF_DESCRIPTOR(WBVAL((USB_CONFIGURATION_DESC_SIZE	+	(USB_NUM_INTERFACES/2) * IAD_CDC_IF_DESC_SET_SIZE)),USB_NUM_INTERFACES),
	
  IAD_CDC_IF_DESC_SET(	USB_CDC_CIF_NUM0,		USB_CDC_DIF_NUM0,		USB_ENDPOINT_IN(1),		USB_ENDPOINT_OUT(2),		USB_ENDPOINT_IN(2)	),		//CDC�ӿ�1
  IAD_CDC_IF_DESC_SET(	USB_CDC_CIF_NUM1, 	USB_CDC_DIF_NUM1, 	USB_ENDPOINT_IN(3), 	USB_ENDPOINT_OUT(4), 		USB_ENDPOINT_IN(4)	),		//CDC�ӿ�2
//  IAD_CDC_IF_DESC_SET(	USB_CDC_CIF_NUM2, 	USB_CDC_DIF_NUM2,		USB_ENDPOINT_IN(5),		USB_ENDPOINT_OUT(6), 		USB_ENDPOINT_IN(6)	),		//CDC�ӿ�3
//	IAD_CDC_IF_DESC_SET(	USB_CDC_CIF_NUM3, 	USB_CDC_DIF_NUM3,		USB_ENDPOINT_IN(7),		USB_ENDPOINT_OUT(8), 		USB_ENDPOINT_IN(8)	),		//CDC�ӿ�4
//	
//	IAD_CDC_IF_DESC_SET(	USB_CDC_CIF_NUM4, 	USB_CDC_DIF_NUM4,		USB_ENDPOINT_IN(1),		USB_ENDPOINT_OUT(3), 		USB_ENDPOINT_IN(1)	),		//CDC�ӿ�5
//	IAD_CDC_IF_DESC_SET(	USB_CDC_CIF_NUM5, 	USB_CDC_DIF_NUM5,		USB_ENDPOINT_IN(11),	USB_ENDPOINT_OUT(12), 	USB_ENDPOINT_IN(12)	),		//CDC�ӿ�6
//	IAD_CDC_IF_DESC_SET(	USB_CDC_CIF_NUM6, 	USB_CDC_DIF_NUM6,		USB_ENDPOINT_IN(11),	USB_ENDPOINT_OUT(12), 	USB_ENDPOINT_IN(12)	),		//CDC�ӿ�7
//	IAD_CDC_IF_DESC_SET(	USB_CDC_CIF_NUM7, 	USB_CDC_DIF_NUM7,		USB_ENDPOINT_IN(13),	USB_ENDPOINT_OUT(14), 	USB_ENDPOINT_IN(14)	),		//CDC�ӿ�8
//	IAD_CDC_IF_DESC_SET(	USB_CDC_CIF_NUM8, 	USB_CDC_DIF_NUM8,		USB_ENDPOINT_IN(15),	USB_ENDPOINT_OUT(16), 	USB_ENDPOINT_IN(16)	),		//CDC�ӿ�9
//	
//	IAD_CDC_IF_DESC_SET(	USB_CDC_CIF_NUM9, 	USB_CDC_DIF_NUM9,		USB_ENDPOINT_IN(15),	USB_ENDPOINT_OUT(16), 	USB_ENDPOINT_IN(16)	),		//CDC�ӿ�10
//	IAD_CDC_IF_DESC_SET(	USB_CDC_CIF_NUM10, 	USB_CDC_DIF_NUM10,	USB_ENDPOINT_IN(15),	USB_ENDPOINT_OUT(16), 	USB_ENDPOINT_IN(16)	),		//CDC�ӿ�11
//	IAD_CDC_IF_DESC_SET(	USB_CDC_CIF_NUM11, 	USB_CDC_DIF_NUM11,	USB_ENDPOINT_IN(15),	USB_ENDPOINT_OUT(16), 	USB_ENDPOINT_IN(16)	),		//CDC�ӿ�12
//	IAD_CDC_IF_DESC_SET(	USB_CDC_CIF_NUM12, 	USB_CDC_DIF_NUM12,	USB_ENDPOINT_IN(15),	USB_ENDPOINT_OUT(16), 	USB_ENDPOINT_IN(16)	),		//CDC�ӿ�13
//	
//	IAD_CDC_IF_DESC_SET(	USB_CDC_CIF_NUM13, 	USB_CDC_DIF_NUM13,	USB_ENDPOINT_IN(15),	USB_ENDPOINT_OUT(16), 	USB_ENDPOINT_IN(16)	),		//CDC�ӿ�14
//	IAD_CDC_IF_DESC_SET(	USB_CDC_CIF_NUM14, 	USB_CDC_DIF_NUM14,	USB_ENDPOINT_IN(15),	USB_ENDPOINT_OUT(16), 	USB_ENDPOINT_IN(16)	),		//CDC�ӿ�15
//	IAD_CDC_IF_DESC_SET(	USB_CDC_CIF_NUM15, 	USB_CDC_DIF_NUM15,	USB_ENDPOINT_IN(15),	USB_ENDPOINT_OUT(16), 	USB_ENDPOINT_IN(16)	),		//CDC�ӿ�16
//	IAD_CDC_IF_DESC_SET(	USB_CDC_CIF_NUM16, 	USB_CDC_DIF_NUM16,	USB_ENDPOINT_IN(15),	USB_ENDPOINT_OUT(16), 	USB_ENDPOINT_IN(16)	)			//CDC�ӿ�17
};
	
/* USB��������������(���á��ӿڡ��˵㡢�ࡢ����)(Configuration, Interface, Endpoint, Class, Vendor */
const u8 Virtual_Com_Port_ConfigDescriptor1[] =			//����������
  {
		//*******************����Ϊ����������*********************/
    /*Configuation Descriptor*/		
    0x09,   /* bLength: Configuation Descriptor size */																		//��������������--0x09/9���ֽ�
    USB_CONFIGURATION_DESCRIPTOR_TYPE,      /* bDescriptorType: Configuration */					//���--0X02�豸������
    0X4B,       /* wTotalLength:no of returned bytes */				//��������Ϣ���ܳ����������ã��ӿڣ��˵���豸�༰���̶������������
    0x00,
//		WBVAL((USB_CONFIGURATION_DESC_SIZE	+	6 * IAD_CDC_IF_DESC_SET_SIZE)),/* wTotalLength */
    0x04,   /* bNumInterfaces: 2 interface */																							//��������֧�ֵĽӿڸ���----���ò����п��ܻ����ö�ٲ�����
    0x01,   /* bConfigurationValue: Configuration value */																//��SetConfiguration��������������������ѡ�������á�
    0x00,   /* iConfiguration: Index of string descriptor describing the configuration */	//���������õ��ִ�����������
    0xC0,   /* bmAttributes: self powered */																							//�������ԣ�D7�� ��������Ϊһ����D6�� �Ը���Դ��D5�� Զ�̻��ѣ�D4..0����������Ϊһ��
    0x32,   /* MaxPower 0 mA */																														//�ڴ������µ����ߵ�Դ�ķ�������2mA Ϊһ����λ��
    /*Interface Descriptor*/																							/*�ӿ�������*/
		
		
		//*******************����ΪIAD������*********************/
//		#if (USB_MULTI_IF)
//			CDC_ACM_DESC_IAD(1,1),
//		#endif
		
		/* Interface Association Descriptor */
		0x08,               				/* bLength: Interface Descriptor size */
		USB_INTERFACE_ASSOCIATION_DESCRIPTOR_TYPE,   		/* bDescriptorType: IAD */
		0x00,               				/* bFirstInterface */	//��ʼ�ӿ�
		0x02,               				/* bInterfaceCount */	//�ӿ���
		0x02,               				/* bFunctionClass */
		0x02,               				/* bFunctionSubClass */
		0x01,               				/* bFunctionProtocol */
		0x02,              					/* iFunction */

			
		
				
		//��߱������ӿڣ�CDC��ӿں�������ӿ�
		//��CDC�豸�У�������һ��CDC�ӿڣ��Թ�������ӿڴ��䣬CDC�ӿ�ʹ�ñ�׼�ӿ�����������һ���ж�����˵㣬��������״̬
		
		/**************  CDC��ӿ�������****************/
    
		0x09,   //bLength�ֶΡ��ӿ��������ĳ���Ϊ9�ֽڡ�		
		0x04,  //bDescriptorType�ֶΡ��ӿ��������ı��Ϊ0x04��/* bDescriptorType: Interface */
    /* Interface descriptor type */		//�ӿ���������
    
		0x00,   //bInterfaceNumber�ֶΡ��ýӿڵı�ţ���һ���ӿڣ����Ϊ0��
		0x00,   //bAlternateSetting�ֶΡ��ýӿڵı��ñ�ţ�Ϊ0��
		0x01,   //bNumEndpoints�ֶΡ���0�˵����Ŀ��CDC�ӿ�ֻʹ��һ���ж�����˵㡣�˽ӿ��õĶ˵������������0��˵���˽ӿ�ֻ��ȱʡ���ƹܵ���
		0x02,   //bInterfaceClass�ֶΡ��ýӿ���ʹ�õ��ࡣCDC��������Ϊ0x02���ӿ���������ֵ��0ֵΪ�����ı�׼������ ��������ֵ��ΪFFH����˽ӿ����ɳ���˵���� ����������ֵ��USB˵��������,0x02 CDC������
		0x02,   //bInterfaceSubClass�ֶΡ��ýӿ���ʹ�õ����ࡣҪʵ��USBת����,�ͱ���ʹ��Abstract Control Model���������ģ�ͣ����ࡣ���ı��Ϊ0x02��������:��Щֵ�Ķ�����bInterfaceClass������� ���bInterfaceClass���ֵΪ��������ֵ����Ϊ�㡣 bInterfaceClass��ΪFFH������ֵ��USB ��������					
		0x01,   //bInterfaceProtocol�ֶΡ�ʹ��Common AT Commands��ͨ��AT���Э�顣��Э��ı��Ϊ0x01��Э���룺bInterfaceClass ��bInterfaceSubClass ���ֵ����.���һ���ӿ�֧���豸����ص���������ֵָ�����豸��˵�����������Э��.
		0x00,   //iConfiguration�ֶΡ��ýӿڵ��ַ�������ֵ������û�У�Ϊ0��/* iInterface: */	

		
		
		/***************����Ϊ����������****************/
		//CDC���У����߱�HID�������ͱ��������������ǹ�����������������ӿ��������������������ӿڹ��ܡ�
    /*Header Functional Descriptor*/								/*ͷ��������*/
		/****************ͷ����������***************/
    0x05,   //bFunctionLength�ֶΡ�������������Ϊ5�ֽ�
    0x24,   //bDescriptorType�ֶΡ�����������Ϊ������ӿڣ�CS_INTERFACE��,���Ϊ0x24
    0x00,   //bDescriptorSubtype�ֶΡ�����������ΪHeader Functional Descriptor,���Ϊ0x00��
    0x10,   //bcdCDC�ֶΡ�CDC�汾�ţ�Ϊ0x0110�����ֽ����ȣ�
    0x01,
		
		
    /*Call Managment Functional Descriptor*/
		/*************���ù�����������*************/
    0x05,   //bFunctionLength�ֶΡ�������������Ϊ5�ֽ�
    0x24,   //bDescriptorType�ֶΡ�����������Ϊ������ӿڣ�CS_INTERFACE��,���Ϊ0x24
    0x01,   //bDescriptorSubtype�ֶΡ�����������ΪCall Management,functional descriptor�����Ϊ0x01��
    0x00,   //bmCapabilities�ֶΡ��豸�Լ�������call management
    0x01,   //bDataInterface�ֶΡ�û��������ӿ�����call management
		
		
		
    /*ACM Functional Descriptor*/
		/**************ACM ����������****************/
    0x04,   //bFunctionLength�ֶΡ�������������Ϊ4�ֽ�
    0x24,   //bDescriptorType�ֶΡ�����������Ϊ������ӿڣ�CS_INTERFACE��,���Ϊ0x24��
    0x02,   //bDescriptorSubtype�ֶΡ�����������ΪAbstract Control,Management functional descriptor�����Ϊ0x02��
    0x02,   //bmCapabilities�ֶΡ�֧��Set_Line_Coding��Set_Control_Line_State��Get_Line_Coding�����Serial_State֪ͨ
		
		
    /*Union Functional Descriptor*/
		/***************���Ϲ���������**************/
    0x05,   //bFunctionLength�ֶΡ�������������Ϊ5�ֽڡ�
    0x24,   //bDescriptorType�ֶΡ�����������Ϊ������ӿڣ�CS_INTERFACE��,���Ϊ0x24��
    0x06,   //bDescriptorSubtype�ֶΡ�����������ΪUnion functional descriptor�����Ϊ0x06��
    0x00,   //MasterInterface�ֶΡ�����Ϊǰ����Ϊ0��CDC�ӿڡ�
    0x01,   //SlaveInterface�ֶΣ�����Ϊ���������Ϊ1��������ӿڡ�
		
	


		/***************����Ϊ�˵�������****************/
    /*Endpoint 2 Descriptor*/
		/********************����˵�2������******************/
    0x07,   /* bLength: Endpoint Descriptor size */
    USB_ENDPOINT_DESCRIPTOR_TYPE,   /* bDescriptorType: Endpoint */				//�˵��������� 0x04
    0x82,   /* bEndpointAddress: (IN2) */																	//�˵㣺���������������Ķ˵�ĵ�ַ������
																																					//		Bit 3..0 : �˵�ţ�Bit 6..4 : ����,Ϊ�㣬Bit 7: ����,������ƶ˵����ԡ�0������˵㣨�������豸����1������˵㣨�豸��������
   
		0x03,   /* bmAttributes: Interrupt */																	//�������ͣ�Bit 1..0 :�������ͣ�00=���ƴ��ͣ�01=ͬ�����ͣ�10=�����ͣ�11=�жϴ���
    VIRTUAL_COM_PORT_INT_SIZE,      /* wMaxPacketSize: */									//�˵��ܹ����ջ��͵�������ݰ��Ĵ�С������ʵ�����䣬��ֵ����Ϊÿ֡�����ݾ�����Ԥ��ʱ�䡣��ʵ������ʱ���ܵ����ܲ���ȫ��ҪԤ���Ĵ���ʵ�ʴ�������豸ͨ��һ�ַ�USB����Ļ��ƻ㱨�������������жϴ��䣬��������Ϳ��ƴ��䣬�˵���ܷ��ͱ�֮�̵����ݰ�
    0x00,
    0xFF,   /* bInterval: */																							//�������ݴ���˵��ʱ���϶�������ֵ���������͵Ķ˵㼰���ƴ��͵Ķ˵������塣����ͬ�����͵Ķ˵�������Ϊ1����ʾ����Ϊ1ms�������жϴ��͵Ķ˵����ֵ�ķ�ΧΪ1ms��255ms��
    
	
	
		/*Data class interface descriptor*/
		/********************������ӿ�������********************/
    0x09,   /* bLength: Endpoint Descriptor size */												//
    USB_INTERFACE_DESCRIPTOR_TYPE,  /* bDescriptorType: */								//USB�ӿ������� 0X04
    0x01,   /* bInterfaceNumber: Number of Interface */										//�ӿںţ���ǰ����֧�ֵĽӿ��������������㿪ʼ����
    0x00,   /* bAlternateSetting: Alternate setting */										//��ѡ���õ�����ֵ��
    0x02,   /* bNumEndpoints: Two endpoints used */												//�˽ӿ��õĶ˵����������������˵���˽ӿ�ֻ��ȱʡ���ƹܵ���
    0x0A,   /* bInterfaceClass: CDC */																		//�ӿ���������ֵ�� 0ֵΪ�����ı�׼������ ��������ֵ��ΪFFH����˽ӿ����ɳ���˵���� ����������ֵ��USB ˵��������0x0A CDC������
    0x00,   /* bInterfaceSubClass: */																			//������
    0x00,   /* bInterfaceProtocol: */																			//Э���룺bInterfaceClass ��bInterfaceSubClass ���ֵ����.���һ���ӿ�֧���豸����ص���������ֵָ�����豸��˵�����������Э��.
    0x00,   /* iInterface: */																							//�����˽ӿڵ��ִ������������ֵ��   
	 
		
		/*Endpoint 3 Descriptor*/																/*�˵�3����*/
		/********************����˵�3������******************/
    0x07,   /* bLength: Endpoint Descriptor size */
    USB_ENDPOINT_DESCRIPTOR_TYPE,   /* bDescriptorType: Endpoint */				//�˵��������� 0x04
    0x03,   /* bEndpointAddress: (OUT3) */																//�˵㣺���������������Ķ˵�ĵ�ַ������
																																					//		Bit 3..0 : �˵�ţ�Bit 6..4 : ����,Ϊ�㣬Bit 7: ����,������ƶ˵����ԡ�0������˵㣨�������豸����1������˵㣨�豸��������
    0x02,   /* bmAttributes: Bulk */																			//�������ͣ�Bit 1..0 :�������ͣ�00=���ƴ��ͣ�01=ͬ�����ͣ�10=�����ͣ�11=�жϴ���
    VIRTUAL_COM_PORT_DATA_SIZE,             /* wMaxPacketSize: */					//�˵��ܹ����ջ��͵�������ݰ��Ĵ�С������ʵ�����䣬��ֵ����Ϊÿ֡�����ݾ�����Ԥ��ʱ�䡣��ʵ������ʱ���ܵ����ܲ���ȫ��ҪԤ���Ĵ���ʵ�ʴ�������豸ͨ��һ�ַ�USB����Ļ��ƻ㱨�������������жϴ��䣬��������Ϳ��ƴ��䣬�˵���ܷ��ͱ�֮�̵����ݰ�
    0x00,
    0x00,   /* bInterval: ignore for Bulk transfer */											//�������ݴ���˵��ʱ���϶�������ֵ���������͵Ķ˵㼰���ƴ��͵Ķ˵������塣����ͬ�����͵Ķ˵�������Ϊ1����ʾ����Ϊ1ms�������жϴ��͵Ķ˵����ֵ�ķ�ΧΪ1ms��255ms��
    
		
		/*Endpoint 1 Descriptor*/
		/********************����˵�1������********************/
    0x07,   /* bLength: Endpoint Descriptor size */
    USB_ENDPOINT_DESCRIPTOR_TYPE,   /* bDescriptorType: Endpoint */				//�˵��������� 0x04
    0x81,   /* bEndpointAddress: (IN1) */																	//�˵㣺���������������Ķ˵�ĵ�ַ������
																																					//		Bit 3..0 : �˵�ţ�Bit 6..4 : ����,Ϊ�㣬Bit 7: ����,������ƶ˵����ԡ�0������˵㣨�������豸����1������˵㣨�豸��������
    0x02,   /* bmAttributes: Bulk */																			//�������ͣ�Bit 1..0 :�������ͣ�00=���ƴ��ͣ�01=ͬ�����ͣ�10=�����ͣ�11=�жϴ���
    VIRTUAL_COM_PORT_DATA_SIZE,             /* wMaxPacketSize: */					//�˵��ܹ����ջ��͵�������ݰ��Ĵ�С������ʵ�����䣬��ֵ����Ϊÿ֡�����ݾ�����Ԥ��ʱ�䡣��ʵ������ʱ���ܵ����ܲ���ȫ��ҪԤ���Ĵ���ʵ�ʴ�������豸ͨ��һ�ַ�USB����Ļ��ƻ㱨�������������жϴ��䣬��������Ϳ��ƴ��䣬�˵���ܷ��ͱ�֮�̵����ݰ�
    0x00,
    0x00,    /* bInterval */																								//�������ݴ���˵��ʱ���϶�������ֵ���������͵Ķ˵㼰���ƴ��͵Ķ˵������塣����ͬ�����͵Ķ˵�������Ϊ1����ʾ����Ϊ1ms�������жϴ��͵Ķ˵����ֵ�ķ�ΧΪ1ms��255ms��																					//�������ݴ���˵��ʱ���϶�������ֵ���������͵Ķ˵㼰���ƴ��͵Ķ˵������塣����ͬ�����͵Ķ˵�������Ϊ1����ʾ����Ϊ1ms�������жϴ��͵Ķ˵����ֵ�ķ�ΧΪ1ms��255ms��
	
//==========================�豸2
		/* Interface Association Descriptor */
		0x08,               				/* bLength: Interface Descriptor size */
		USB_INTERFACE_ASSOCIATION_DESCRIPTOR_TYPE,   		/* bDescriptorType: IAD */
		0x00,               				/* bFirstInterface */	//��ʼ�ӿ�
		0x02,               				/* bInterfaceCount */	//�ӿ���
		0x02,               				/* bFunctionClass */
		0x02,               				/* bFunctionSubClass */
		0x01,               				/* bFunctionProtocol */
		0x02,              					/* iFunction */
		
		
				//��߱������ӿڣ�CDC��ӿں�������ӿ�
		//��CDC�豸�У�������һ��CDC�ӿڣ��Թ�������ӿڴ��䣬CDC�ӿ�ʹ�ñ�׼�ӿ�����������һ���ж�����˵㣬��������״̬
		
		/**************  CDC��ӿ�������****************/
    
		0x09,   //bLength�ֶΡ��ӿ��������ĳ���Ϊ9�ֽڡ�		
		0x04,  //bDescriptorType�ֶΡ��ӿ��������ı��Ϊ0x04��/* bDescriptorType: Interface */
    /* Interface descriptor type */		//�ӿ���������
    
		0x02,   //bInterfaceNumber�ֶΡ��ýӿڵı�ţ���һ���ӿڣ����Ϊ0��
		0x00,   //bAlternateSetting�ֶΡ��ýӿڵı��ñ�ţ�Ϊ0��
		0x01,   //bNumEndpoints�ֶΡ���0�˵����Ŀ��CDC�ӿ�ֻʹ��һ���ж�����˵㡣�˽ӿ��õĶ˵������������0��˵���˽ӿ�ֻ��ȱʡ���ƹܵ���
		0x02,   //bInterfaceClass�ֶΡ��ýӿ���ʹ�õ��ࡣCDC��������Ϊ0x02���ӿ���������ֵ��0ֵΪ�����ı�׼������ ��������ֵ��ΪFFH����˽ӿ����ɳ���˵���� ����������ֵ��USB˵��������,0x02 CDC������
		0x02,   //bInterfaceSubClass�ֶΡ��ýӿ���ʹ�õ����ࡣҪʵ��USBת����,�ͱ���ʹ��Abstract Control Model���������ģ�ͣ����ࡣ���ı��Ϊ0x02��������:��Щֵ�Ķ�����bInterfaceClass������� ���bInterfaceClass���ֵΪ��������ֵ����Ϊ�㡣 bInterfaceClass��ΪFFH������ֵ��USB ��������					
		0x01,   //bInterfaceProtocol�ֶΡ�ʹ��Common AT Commands��ͨ��AT���Э�顣��Э��ı��Ϊ0x01��Э���룺bInterfaceClass ��bInterfaceSubClass ���ֵ����.���һ���ӿ�֧���豸����ص���������ֵָ�����豸��˵�����������Э��.
		0x00,   //iConfiguration�ֶΡ��ýӿڵ��ַ�������ֵ������û�У�Ϊ0��/* iInterface: */	

		
		
		/***************����Ϊ����������****************/
		//CDC���У����߱�HID�������ͱ��������������ǹ�����������������ӿ��������������������ӿڹ��ܡ�
    /*Header Functional Descriptor*/								/*ͷ��������*/
		/****************ͷ����������***************/
    0x05,   //bFunctionLength�ֶΡ�������������Ϊ5�ֽ�
    0x24,   //bDescriptorType�ֶΡ�����������Ϊ������ӿڣ�CS_INTERFACE��,���Ϊ0x24
    0x00,   //bDescriptorSubtype�ֶΡ�����������ΪHeader Functional Descriptor,���Ϊ0x00��
    0x10,   //bcdCDC�ֶΡ�CDC�汾�ţ�Ϊ0x0110�����ֽ����ȣ�
    0x01,
		
		
    /*Call Managment Functional Descriptor*/
		/*************���ù�����������*************/
    0x05,   //bFunctionLength�ֶΡ�������������Ϊ5�ֽ�
    0x24,   //bDescriptorType�ֶΡ�����������Ϊ������ӿڣ�CS_INTERFACE��,���Ϊ0x24
    0x01,   //bDescriptorSubtype�ֶΡ�����������ΪCall Management,functional descriptor�����Ϊ0x01��
    0x00,   //bmCapabilities�ֶΡ��豸�Լ�������call management
    0x01,   //bDataInterface�ֶΡ�û��������ӿ�����call management
		
		
		
    /*ACM Functional Descriptor*/
		/**************ACM ����������****************/
    0x04,   //bFunctionLength�ֶΡ�������������Ϊ4�ֽ�
    0x24,   //bDescriptorType�ֶΡ�����������Ϊ������ӿڣ�CS_INTERFACE��,���Ϊ0x24��
    0x02,   //bDescriptorSubtype�ֶΡ�����������ΪAbstract Control,Management functional descriptor�����Ϊ0x02��
    0x02,   //bmCapabilities�ֶΡ�֧��Set_Line_Coding��Set_Control_Line_State��Get_Line_Coding�����Serial_State֪ͨ
		
		
    /*Union Functional Descriptor*/
		/***************���Ϲ���������**************/
    0x05,   //bFunctionLength�ֶΡ�������������Ϊ5�ֽڡ�
    0x24,   //bDescriptorType�ֶΡ�����������Ϊ������ӿڣ�CS_INTERFACE��,���Ϊ0x24��
    0x06,   //bDescriptorSubtype�ֶΡ�����������ΪUnion functional descriptor�����Ϊ0x06��
    0x00,   //MasterInterface�ֶΡ�����Ϊǰ����Ϊ0��CDC�ӿڡ�
    0x01,   //SlaveInterface�ֶΣ�����Ϊ���������Ϊ1��������ӿڡ�
		
	


		/***************����Ϊ�˵�������****************/
    /*Endpoint 2 Descriptor*/
		/********************����˵�2������******************/
    0x07,   /* bLength: Endpoint Descriptor size */
    USB_ENDPOINT_DESCRIPTOR_TYPE,   /* bDescriptorType: Endpoint */				//�˵��������� 0x04
    0x82,   /* bEndpointAddress: (IN2) */																	//�˵㣺���������������Ķ˵�ĵ�ַ������
																																					//		Bit 3..0 : �˵�ţ�Bit 6..4 : ����,Ϊ�㣬Bit 7: ����,������ƶ˵����ԡ�0������˵㣨�������豸����1������˵㣨�豸��������
   
		0x03,   /* bmAttributes: Interrupt */																	//�������ͣ�Bit 1..0 :�������ͣ�00=���ƴ��ͣ�01=ͬ�����ͣ�10=�����ͣ�11=�жϴ���
    VIRTUAL_COM_PORT_INT_SIZE,      /* wMaxPacketSize: */									//�˵��ܹ����ջ��͵�������ݰ��Ĵ�С������ʵ�����䣬��ֵ����Ϊÿ֡�����ݾ�����Ԥ��ʱ�䡣��ʵ������ʱ���ܵ����ܲ���ȫ��ҪԤ���Ĵ���ʵ�ʴ�������豸ͨ��һ�ַ�USB����Ļ��ƻ㱨�������������жϴ��䣬��������Ϳ��ƴ��䣬�˵���ܷ��ͱ�֮�̵����ݰ�
    0x00,
    0xFF,   /* bInterval: */																							//�������ݴ���˵��ʱ���϶�������ֵ���������͵Ķ˵㼰���ƴ��͵Ķ˵������塣����ͬ�����͵Ķ˵�������Ϊ1����ʾ����Ϊ1ms�������жϴ��͵Ķ˵����ֵ�ķ�ΧΪ1ms��255ms��
    
	
	
		/*Data class interface descriptor*/
		/********************������ӿ�������********************/
    0x09,   /* bLength: Endpoint Descriptor size */												//
    USB_INTERFACE_DESCRIPTOR_TYPE,  /* bDescriptorType: */								//USB�ӿ������� 0X04
    0x03,   /* bInterfaceNumber: Number of Interface */										//�ӿںţ���ǰ����֧�ֵĽӿ��������������㿪ʼ����
    0x00,   /* bAlternateSetting: Alternate setting */										//��ѡ���õ�����ֵ��
    0x02,   /* bNumEndpoints: Two endpoints used */												//�˽ӿ��õĶ˵����������������˵���˽ӿ�ֻ��ȱʡ���ƹܵ���
    0x0A,   /* bInterfaceClass: CDC */																		//�ӿ���������ֵ�� 0ֵΪ�����ı�׼������ ��������ֵ��ΪFFH����˽ӿ����ɳ���˵���� ����������ֵ��USB ˵��������0x0A CDC������
    0x00,   /* bInterfaceSubClass: */																			//������
    0x00,   /* bInterfaceProtocol: */																			//Э���룺bInterfaceClass ��bInterfaceSubClass ���ֵ����.���һ���ӿ�֧���豸����ص���������ֵָ�����豸��˵�����������Э��.
    0x00,   /* iInterface: */																							//�����˽ӿڵ��ִ������������ֵ��   
	 
		
		/*Endpoint 3 Descriptor*/																/*�˵�3����*/
		/********************����˵�3������******************/
    0x07,   /* bLength: Endpoint Descriptor size */
    USB_ENDPOINT_DESCRIPTOR_TYPE,   /* bDescriptorType: Endpoint */				//�˵��������� 0x04
    0x03,   /* bEndpointAddress: (OUT3) */																//�˵㣺���������������Ķ˵�ĵ�ַ������
																																					//		Bit 3..0 : �˵�ţ�Bit 6..4 : ����,Ϊ�㣬Bit 7: ����,������ƶ˵����ԡ�0������˵㣨�������豸����1������˵㣨�豸��������
    0x02,   /* bmAttributes: Bulk */																			//�������ͣ�Bit 1..0 :�������ͣ�00=���ƴ��ͣ�01=ͬ�����ͣ�10=�����ͣ�11=�жϴ���
    VIRTUAL_COM_PORT_DATA_SIZE,             /* wMaxPacketSize: */					//�˵��ܹ����ջ��͵�������ݰ��Ĵ�С������ʵ�����䣬��ֵ����Ϊÿ֡�����ݾ�����Ԥ��ʱ�䡣��ʵ������ʱ���ܵ����ܲ���ȫ��ҪԤ���Ĵ���ʵ�ʴ�������豸ͨ��һ�ַ�USB����Ļ��ƻ㱨�������������жϴ��䣬��������Ϳ��ƴ��䣬�˵���ܷ��ͱ�֮�̵����ݰ�
    0x00,
    0x00,   /* bInterval: ignore for Bulk transfer */											//�������ݴ���˵��ʱ���϶�������ֵ���������͵Ķ˵㼰���ƴ��͵Ķ˵������塣����ͬ�����͵Ķ˵�������Ϊ1����ʾ����Ϊ1ms�������жϴ��͵Ķ˵����ֵ�ķ�ΧΪ1ms��255ms��
    
		
		/*Endpoint 1 Descriptor*/
		/********************����˵�1������********************/
    0x07,   /* bLength: Endpoint Descriptor size */
    USB_ENDPOINT_DESCRIPTOR_TYPE,   /* bDescriptorType: Endpoint */				//�˵��������� 0x04
    0x81,   /* bEndpointAddress: (IN1) */																	//�˵㣺���������������Ķ˵�ĵ�ַ������
																																					//		Bit 3..0 : �˵�ţ�Bit 6..4 : ����,Ϊ�㣬Bit 7: ����,������ƶ˵����ԡ�0������˵㣨�������豸����1������˵㣨�豸��������
    0x02,   /* bmAttributes: Bulk */																			//�������ͣ�Bit 1..0 :�������ͣ�00=���ƴ��ͣ�01=ͬ�����ͣ�10=�����ͣ�11=�жϴ���
    VIRTUAL_COM_PORT_DATA_SIZE,             /* wMaxPacketSize: */					//�˵��ܹ����ջ��͵�������ݰ��Ĵ�С������ʵ�����䣬��ֵ����Ϊÿ֡�����ݾ�����Ԥ��ʱ�䡣��ʵ������ʱ���ܵ����ܲ���ȫ��ҪԤ���Ĵ���ʵ�ʴ�������豸ͨ��һ�ַ�USB����Ļ��ƻ㱨�������������жϴ��䣬��������Ϳ��ƴ��䣬�˵���ܷ��ͱ�֮�̵����ݰ�
    0x00,
    0x00,    /* bInterval */																								//�������ݴ���˵��ʱ���϶�������ֵ���������͵Ķ˵㼰���ƴ��͵Ķ˵������塣����ͬ�����͵Ķ˵�������Ϊ1����ʾ����Ϊ1ms�������жϴ��͵Ķ˵����ֵ�ķ�ΧΪ1ms��255ms��																					//�������ݴ���˵��ʱ���϶�������ֵ���������͵Ķ˵㼰���ƴ��͵Ķ˵������塣����ͬ�����͵Ķ˵�������Ϊ1����ʾ����Ϊ1ms�������жϴ��͵Ķ˵����ֵ�ķ�ΧΪ1ms��255ms��
	

		
		
};
/* USB��������������(���á��ӿڡ��˵㡢�ࡢ����)(Configuration, Interface, Endpoint, Class, Vendor */
const u8 Virtual_Com_Port_ConfigDescriptor2[] =			//����������
  {
		//*******************����Ϊ����������*********************/
    /*Configuation Descriptor*/		
    0x09,   /* bLength: Configuation Descriptor size */																		//��������������--0x09/9���ֽ�
    USB_CONFIGURATION_DESCRIPTOR_TYPE,      /* bDescriptorType: Configuration */					//���--0X02�豸������
    0X4B,       /* wTotalLength:no of returned bytes */				//��������Ϣ���ܳ����������ã��ӿڣ��˵���豸�༰���̶������������
    0x00,
//		WBVAL((USB_CONFIGURATION_DESC_SIZE	+	6 * IAD_CDC_IF_DESC_SET_SIZE)),/* wTotalLength */
    0x01,   /* bNumInterfaces: 2 interface */																							//��������֧�ֵĽӿڸ���----���ò����п��ܻ����ö�ٲ�����
    0x01,   /* bConfigurationValue: Configuration value */																//��SetConfiguration��������������������ѡ�������á�
    0x00,   /* iConfiguration: Index of string descriptor describing the configuration */	//���������õ��ִ�����������
    0xC0,   /* bmAttributes: self powered */																							//�������ԣ�D7�� ��������Ϊһ����D6�� �Ը���Դ��D5�� Զ�̻��ѣ�D4..0����������Ϊһ��
    0x32,   /* MaxPower 0 mA */																														//�ڴ������µ����ߵ�Դ�ķ�������2mA Ϊһ����λ��
    /*Interface Descriptor*/																							/*�ӿ�������*/
		
		
		//*******************����ΪIAD������*********************/
//		#if (USB_MULTI_IF)
//			CDC_ACM_DESC_IAD(1,1),
//		#endif
		
		/* Interface Association Descriptor */
		0x08,               				/* bLength: Interface Descriptor size */
		USB_INTERFACE_ASSOCIATION_DESCRIPTOR_TYPE,   		/* bDescriptorType: IAD */
		0x00,               				/* bFirstInterface */	//��ʼ�ӿ�
		0x01,               				/* bInterfaceCount */	//�ӿ���
		0x02,               				/* bFunctionClass */
		0x02,               				/* bFunctionSubClass */
		0x01,               				/* bFunctionProtocol */
		0x04,              					/* iFunction */

			
		
				
		//��߱������ӿڣ�CDC��ӿں�������ӿ�
		//��CDC�豸�У�������һ��CDC�ӿڣ��Թ�������ӿڴ��䣬CDC�ӿ�ʹ�ñ�׼�ӿ�����������һ���ж�����˵㣬��������״̬
		
		/**************  CDC��ӿ�������****************/
    
		0x09,   //bLength�ֶΡ��ӿ��������ĳ���Ϊ9�ֽڡ�		
		0x04,  //bDescriptorType�ֶΡ��ӿ��������ı��Ϊ0x04��/* bDescriptorType: Interface */
    /* Interface descriptor type */		//�ӿ���������
    
		0x00,   //bInterfaceNumber�ֶΡ��ýӿڵı�ţ���һ���ӿڣ����Ϊ0��
		0x00,   //bAlternateSetting�ֶΡ��ýӿڵı��ñ�ţ�Ϊ0��
		0x01,   //bNumEndpoints�ֶΡ���0�˵����Ŀ��CDC�ӿ�ֻʹ��һ���ж�����˵㡣�˽ӿ��õĶ˵������������0��˵���˽ӿ�ֻ��ȱʡ���ƹܵ���
		0x02,   //bInterfaceClass�ֶΡ��ýӿ���ʹ�õ��ࡣCDC��������Ϊ0x02���ӿ���������ֵ��0ֵΪ�����ı�׼������ ��������ֵ��ΪFFH����˽ӿ����ɳ���˵���� ����������ֵ��USB˵��������,0x02 CDC������
		0x02,   //bInterfaceSubClass�ֶΡ��ýӿ���ʹ�õ����ࡣҪʵ��USBת����,�ͱ���ʹ��Abstract Control Model���������ģ�ͣ����ࡣ���ı��Ϊ0x02��������:��Щֵ�Ķ�����bInterfaceClass������� ���bInterfaceClass���ֵΪ��������ֵ����Ϊ�㡣 bInterfaceClass��ΪFFH������ֵ��USB ��������					
		0x01,   //bInterfaceProtocol�ֶΡ�ʹ��Common AT Commands��ͨ��AT���Э�顣��Э��ı��Ϊ0x01��Э���룺bInterfaceClass ��bInterfaceSubClass ���ֵ����.���һ���ӿ�֧���豸����ص���������ֵָ�����豸��˵�����������Э��.
		0x00,   //iConfiguration�ֶΡ��ýӿڵ��ַ�������ֵ������û�У�Ϊ0��/* iInterface: */	

		
		
		/***************����Ϊ����������****************/
		//CDC���У����߱�HID�������ͱ��������������ǹ�����������������ӿ��������������������ӿڹ��ܡ�
    /*Header Functional Descriptor*/								/*ͷ��������*/
		/****************ͷ����������***************/
    0x05,   //bFunctionLength�ֶΡ�������������Ϊ5�ֽ�
    0x24,   //bDescriptorType�ֶΡ�����������Ϊ������ӿڣ�CS_INTERFACE��,���Ϊ0x24
    0x00,   //bDescriptorSubtype�ֶΡ�����������ΪHeader Functional Descriptor,���Ϊ0x00��
    0x10,   //bcdCDC�ֶΡ�CDC�汾�ţ�Ϊ0x0110�����ֽ����ȣ�
    0x01,
		
		
    /*Call Managment Functional Descriptor*/
		/*************���ù�����������*************/
    0x05,   //bFunctionLength�ֶΡ�������������Ϊ5�ֽ�
    0x24,   //bDescriptorType�ֶΡ�����������Ϊ������ӿڣ�CS_INTERFACE��,���Ϊ0x24
    0x01,   //bDescriptorSubtype�ֶΡ�����������ΪCall Management,functional descriptor�����Ϊ0x01��
    0x00,   //bmCapabilities�ֶΡ��豸�Լ�������call management
    0x01,   //bDataInterface�ֶΡ�û��������ӿ�����call management
		
		
		
    /*ACM Functional Descriptor*/
		/**************ACM ����������****************/
    0x04,   //bFunctionLength�ֶΡ�������������Ϊ4�ֽ�
    0x24,   //bDescriptorType�ֶΡ�����������Ϊ������ӿڣ�CS_INTERFACE��,���Ϊ0x24��
    0x02,   //bDescriptorSubtype�ֶΡ�����������ΪAbstract Control,Management functional descriptor�����Ϊ0x02��
    0x02,   //bmCapabilities�ֶΡ�֧��Set_Line_Coding��Set_Control_Line_State��Get_Line_Coding�����Serial_State֪ͨ
		
		
    /*Union Functional Descriptor*/
		/***************���Ϲ���������**************/
    0x05,   //bFunctionLength�ֶΡ�������������Ϊ5�ֽڡ�
    0x24,   //bDescriptorType�ֶΡ�����������Ϊ������ӿڣ�CS_INTERFACE��,���Ϊ0x24��
    0x06,   //bDescriptorSubtype�ֶΡ�����������ΪUnion functional descriptor�����Ϊ0x06��
    0x00,   //MasterInterface�ֶΡ�����Ϊǰ����Ϊ0��CDC�ӿڡ�
    0x01,   //SlaveInterface�ֶΣ�����Ϊ���������Ϊ1��������ӿڡ�
		
	


		/***************����Ϊ�˵�������****************/
    /*Endpoint 2 Descriptor*/
		/********************����˵�2������******************/
    0x07,   /* bLength: Endpoint Descriptor size */
    USB_ENDPOINT_DESCRIPTOR_TYPE,   /* bDescriptorType: Endpoint */				//�˵��������� 0x04
    0x82,   /* bEndpointAddress: (IN2) */																	//�˵㣺���������������Ķ˵�ĵ�ַ������
																																					//		Bit 3..0 : �˵�ţ�Bit 6..4 : ����,Ϊ�㣬Bit 7: ����,������ƶ˵����ԡ�0������˵㣨�������豸����1������˵㣨�豸��������
   
		0x03,   /* bmAttributes: Interrupt */																	//�������ͣ�Bit 1..0 :�������ͣ�00=���ƴ��ͣ�01=ͬ�����ͣ�10=�����ͣ�11=�жϴ���
    VIRTUAL_COM_PORT_INT_SIZE,      /* wMaxPacketSize: */									//�˵��ܹ����ջ��͵�������ݰ��Ĵ�С������ʵ�����䣬��ֵ����Ϊÿ֡�����ݾ�����Ԥ��ʱ�䡣��ʵ������ʱ���ܵ����ܲ���ȫ��ҪԤ���Ĵ���ʵ�ʴ�������豸ͨ��һ�ַ�USB����Ļ��ƻ㱨�������������жϴ��䣬��������Ϳ��ƴ��䣬�˵���ܷ��ͱ�֮�̵����ݰ�
    0x00,
    0xFF,   /* bInterval: */																							//�������ݴ���˵��ʱ���϶�������ֵ���������͵Ķ˵㼰���ƴ��͵Ķ˵������塣����ͬ�����͵Ķ˵�������Ϊ1����ʾ����Ϊ1ms�������жϴ��͵Ķ˵����ֵ�ķ�ΧΪ1ms��255ms��
    
	
	
		/*Data class interface descriptor*/
		/********************������ӿ�������********************/
    0x09,   /* bLength: Endpoint Descriptor size */												//
    USB_INTERFACE_DESCRIPTOR_TYPE,  /* bDescriptorType: */								//USB�ӿ������� 0X04
    0x01,   /* bInterfaceNumber: Number of Interface */										//�ӿںţ���ǰ����֧�ֵĽӿ��������������㿪ʼ����
    0x00,   /* bAlternateSetting: Alternate setting */										//��ѡ���õ�����ֵ��
    0x02,   /* bNumEndpoints: Two endpoints used */												//�˽ӿ��õĶ˵����������������˵���˽ӿ�ֻ��ȱʡ���ƹܵ���
    0x0A,   /* bInterfaceClass: CDC */																		//�ӿ���������ֵ�� 0ֵΪ�����ı�׼������ ��������ֵ��ΪFFH����˽ӿ����ɳ���˵���� ����������ֵ��USB ˵��������0x0A CDC������
    0x00,   /* bInterfaceSubClass: */																			//������
    0x00,   /* bInterfaceProtocol: */																			//Э���룺bInterfaceClass ��bInterfaceSubClass ���ֵ����.���һ���ӿ�֧���豸����ص���������ֵָ�����豸��˵�����������Э��.
    0x00,   /* iInterface: */																							//�����˽ӿڵ��ִ������������ֵ��   
	 
		
		/*Endpoint 3 Descriptor*/																/*�˵�3����*/
		/********************����˵�3������******************/
    0x07,   /* bLength: Endpoint Descriptor size */
    USB_ENDPOINT_DESCRIPTOR_TYPE,   /* bDescriptorType: Endpoint */				//�˵��������� 0x04
    0x03,   /* bEndpointAddress: (OUT3) */																//�˵㣺���������������Ķ˵�ĵ�ַ������
																																					//		Bit 3..0 : �˵�ţ�Bit 6..4 : ����,Ϊ�㣬Bit 7: ����,������ƶ˵����ԡ�0������˵㣨�������豸����1������˵㣨�豸��������
    0x02,   /* bmAttributes: Bulk */																			//�������ͣ�Bit 1..0 :�������ͣ�00=���ƴ��ͣ�01=ͬ�����ͣ�10=�����ͣ�11=�жϴ���
    VIRTUAL_COM_PORT_DATA_SIZE,             /* wMaxPacketSize: */					//�˵��ܹ����ջ��͵�������ݰ��Ĵ�С������ʵ�����䣬��ֵ����Ϊÿ֡�����ݾ�����Ԥ��ʱ�䡣��ʵ������ʱ���ܵ����ܲ���ȫ��ҪԤ���Ĵ���ʵ�ʴ�������豸ͨ��һ�ַ�USB����Ļ��ƻ㱨�������������жϴ��䣬��������Ϳ��ƴ��䣬�˵���ܷ��ͱ�֮�̵����ݰ�
    0x00,
    0x01,   /* bInterval: ignore for Bulk transfer */											//�������ݴ���˵��ʱ���϶�������ֵ���������͵Ķ˵㼰���ƴ��͵Ķ˵������塣����ͬ�����͵Ķ˵�������Ϊ1����ʾ����Ϊ1ms�������жϴ��͵Ķ˵����ֵ�ķ�ΧΪ1ms��255ms��
    
		
		/*Endpoint 1 Descriptor*/
		/********************����˵�1������********************/
    0x07,   /* bLength: Endpoint Descriptor size */
    USB_ENDPOINT_DESCRIPTOR_TYPE,   /* bDescriptorType: Endpoint */				//�˵��������� 0x04
    0x81,   /* bEndpointAddress: (IN1) */																	//�˵㣺���������������Ķ˵�ĵ�ַ������
																																					//		Bit 3..0 : �˵�ţ�Bit 6..4 : ����,Ϊ�㣬Bit 7: ����,������ƶ˵����ԡ�0������˵㣨�������豸����1������˵㣨�豸��������
    0x02,   /* bmAttributes: Bulk */																			//�������ͣ�Bit 1..0 :�������ͣ�00=���ƴ��ͣ�01=ͬ�����ͣ�10=�����ͣ�11=�жϴ���
    VIRTUAL_COM_PORT_DATA_SIZE,             /* wMaxPacketSize: */					//�˵��ܹ����ջ��͵�������ݰ��Ĵ�С������ʵ�����䣬��ֵ����Ϊÿ֡�����ݾ�����Ԥ��ʱ�䡣��ʵ������ʱ���ܵ����ܲ���ȫ��ҪԤ���Ĵ���ʵ�ʴ�������豸ͨ��һ�ַ�USB����Ļ��ƻ㱨�������������жϴ��䣬��������Ϳ��ƴ��䣬�˵���ܷ��ͱ�֮�̵����ݰ�
    0x00,
    0x01,    /* bInterval */																								//�������ݴ���˵��ʱ���϶�������ֵ���������͵Ķ˵㼰���ƴ��͵Ķ˵������塣����ͬ�����͵Ķ˵�������Ϊ1����ʾ����Ϊ1ms�������жϴ��͵Ķ˵����ֵ�ķ�ΧΪ1ms��255ms��																					//�������ݴ���˵��ʱ���϶�������ֵ���������͵Ķ˵㼰���ƴ��͵Ķ˵������塣����ͬ�����͵Ķ˵�������Ϊ1����ʾ����Ϊ1ms�������жϴ��͵Ķ˵����ֵ�ķ�ΧΪ1ms��255ms��
		
		
};
/* USB��������������(���á��ӿڡ��˵㡢�ࡢ����)(Configuration, Interface, Endpoint, Class, Vendor */
const u8 Virtual_Com_Port_ConfigDescriptor3[] =			//����������
  {
    /*Configuation Descriptor*/
		
    0x09,   /* bLength: Configuation Descriptor size */																		//��������������--0x09/9���ֽ�
    USB_CONFIGURATION_DESCRIPTOR_TYPE,      /* bDescriptorType: Configuration */					//���--0X02�豸������
    0x43,		//VIRTUAL_COM_PORT_SIZ_CONFIG_DESC,       /* wTotalLength:no of returned bytes */				//��������Ϣ���ܳ����������ã��ӿڣ��˵���豸�༰���̶������������
    0x00,
    0x02,   /* bNumInterfaces: 2 interface */																							//��������֧�ֵĽӿڸ���
    0x01,   /* bConfigurationValue: Configuration value */																//��SetConfiguration��������������������ѡ�������á�
    0x00,   /* iConfiguration: Index of string descriptor describing the configuration */	//���������õ��ִ�����������
    0xC0,   /* bmAttributes: self powered */																							//�������ԣ�D7�� ��������Ϊһ����D6�� �Ը���Դ��D5�� Զ�̻��ѣ�D4..0����������Ϊһ��
    0x32,   /* MaxPower 0 mA */																														//�ڴ������µ����ߵ�Դ�ķ�������2mA Ϊһ����λ��
    /*Interface Descriptor*/																							/*�ӿ�������*/





		
		//��߱������ӿڣ�CDC��ӿں�������ӿ�
		//��CDC�豸�У�������һ��CDC�ӿڣ��Թ�������ӿڴ��䣬CDC�ӿ�ʹ�ñ�׼�ӿ�����������һ���ж�����˵㣬��������״̬
		
		/**************  CDC��ӿ�������****************/
    
		0x09,   //bLength�ֶΡ��ӿ��������ĳ���Ϊ9�ֽڡ�		
		0x04,  //bDescriptorType�ֶΡ��ӿ��������ı��Ϊ0x04��/* bDescriptorType: Interface */
    /* Interface descriptor type */		//�ӿ���������
    
		0x00,   //bInterfaceNumber�ֶΡ��ýӿڵı�ţ���һ���ӿڣ����Ϊ0��
		0x00,   //bAlternateSetting�ֶΡ��ýӿڵı��ñ�ţ�Ϊ0��
		0x01,   //bNumEndpoints�ֶΡ���0�˵����Ŀ��CDC�ӿ�ֻʹ��һ���ж�����˵㡣�˽ӿ��õĶ˵������������0��˵���˽ӿ�ֻ��ȱʡ���ƹܵ���
		0x02,   //bInterfaceClass�ֶΡ��ýӿ���ʹ�õ��ࡣCDC��������Ϊ0x02���ӿ���������ֵ��0ֵΪ�����ı�׼������ ��������ֵ��ΪFFH����˽ӿ����ɳ���˵���� ����������ֵ��USB˵��������,0x02 CDC������
		0x02,   //bInterfaceSubClass�ֶΡ��ýӿ���ʹ�õ����ࡣҪʵ��USBת����,�ͱ���ʹ��Abstract Control Model���������ģ�ͣ����ࡣ���ı��Ϊ0x02��������:��Щֵ�Ķ�����bInterfaceClass������� ���bInterfaceClass���ֵΪ��������ֵ����Ϊ�㡣 bInterfaceClass��ΪFFH������ֵ��USB ��������					
		0x01,   //bInterfaceProtocol�ֶΡ�ʹ��Common AT Commands��ͨ��AT���Э�顣��Э��ı��Ϊ0x01��Э���룺bInterfaceClass ��bInterfaceSubClass ���ֵ����.���һ���ӿ�֧���豸����ص���������ֵָ�����豸��˵�����������Э��.
		0x00,   //iConfiguration�ֶΡ��ýӿڵ��ַ�������ֵ������û�У�Ϊ0��/* iInterface: */	

		
		
		/***************����Ϊ����������****************/
		//CDC���У����߱�HID�������ͱ��������������ǹ�����������������ӿ��������������������ӿڹ��ܡ�
    /*Header Functional Descriptor*/								/*ͷ��������*/
		/****************ͷ����������***************/
    0x05,   //bFunctionLength�ֶΡ�������������Ϊ5�ֽ�
    0x24,   //bDescriptorType�ֶΡ�����������Ϊ������ӿڣ�CS_INTERFACE��,���Ϊ0x24
    0x00,   //bDescriptorSubtype�ֶΡ�����������ΪHeader Functional Descriptor,���Ϊ0x00��
    0x10,   //bcdCDC�ֶΡ�CDC�汾�ţ�Ϊ0x0110�����ֽ����ȣ�
    0x01,
		
		
    /*Call Managment Functional Descriptor*/
		/*************���ù�����������*************/
    0x05,   //bFunctionLength�ֶΡ�������������Ϊ5�ֽ�
    0x24,   //bDescriptorType�ֶΡ�����������Ϊ������ӿڣ�CS_INTERFACE��,���Ϊ0x24
    0x01,   //bDescriptorSubtype�ֶΡ�����������ΪCall Management,functional descriptor�����Ϊ0x01��
    0x00,   //bmCapabilities�ֶΡ��豸�Լ�������call management
    0x01,   //bDataInterface�ֶΡ�û��������ӿ�����call management
		
		
		
    /*ACM Functional Descriptor*/
		/**************ACM ����������****************/
    0x04,   //bFunctionLength�ֶΡ�������������Ϊ4�ֽ�
    0x24,   //bDescriptorType�ֶΡ�����������Ϊ������ӿڣ�CS_INTERFACE��,���Ϊ0x24��
    0x02,   //bDescriptorSubtype�ֶΡ�����������ΪAbstract Control,Management functional descriptor�����Ϊ0x02��
    0x02,   //bmCapabilities�ֶΡ�֧��Set_Line_Coding��Set_Control_Line_State��Get_Line_Coding�����Serial_State֪ͨ
		
		
    /*Union Functional Descriptor*/
		/***************���Ϲ���������**************/
    0x05,   //bFunctionLength�ֶΡ�������������Ϊ5�ֽڡ�
    0x24,   //bDescriptorType�ֶΡ�����������Ϊ������ӿڣ�CS_INTERFACE��,���Ϊ0x24��
    0x06,   //bDescriptorSubtype�ֶΡ�����������ΪUnion functional descriptor�����Ϊ0x06��
    0x00,   //MasterInterface�ֶΡ�����Ϊǰ����Ϊ0��CDC�ӿڡ�
    0x01,   //SlaveInterface�ֶΣ�����Ϊ���������Ϊ1��������ӿڡ�
		
	


		/***************����Ϊ�˵�������****************/
    /*Endpoint 2 Descriptor*/
		/********************����˵�2������******************/
    0x07,   /* bLength: Endpoint Descriptor size */
    USB_ENDPOINT_DESCRIPTOR_TYPE,   /* bDescriptorType: Endpoint */				//�˵��������� 0x04
    0x82,   /* bEndpointAddress: (IN2) */																	//�˵㣺���������������Ķ˵�ĵ�ַ������
																																					//		Bit 3..0 : �˵�ţ�Bit 6..4 : ����,Ϊ�㣬Bit 7: ����,������ƶ˵����ԡ�0������˵㣨�������豸����1������˵㣨�豸��������
   
		0x03,   /* bmAttributes: Interrupt */																	//�������ͣ�Bit 1..0 :�������ͣ�00=���ƴ��ͣ�01=ͬ�����ͣ�10=�����ͣ�11=�жϴ���
    VIRTUAL_COM_PORT_INT_SIZE,      /* wMaxPacketSize: */									//�˵��ܹ����ջ��͵�������ݰ��Ĵ�С������ʵ�����䣬��ֵ����Ϊÿ֡�����ݾ�����Ԥ��ʱ�䡣��ʵ������ʱ���ܵ����ܲ���ȫ��ҪԤ���Ĵ���ʵ�ʴ�������豸ͨ��һ�ַ�USB����Ļ��ƻ㱨�������������жϴ��䣬��������Ϳ��ƴ��䣬�˵���ܷ��ͱ�֮�̵����ݰ�
    0x00,
    0xFF,   /* bInterval: */																							//�������ݴ���˵��ʱ���϶�������ֵ���������͵Ķ˵㼰���ƴ��͵Ķ˵������塣����ͬ�����͵Ķ˵�������Ϊ1����ʾ����Ϊ1ms�������жϴ��͵Ķ˵����ֵ�ķ�ΧΪ1ms��255ms��
    
	
	
		/*Data class interface descriptor*/
		/********************������ӿ�������********************/
    0x09,   /* bLength: Endpoint Descriptor size */												//
    USB_INTERFACE_DESCRIPTOR_TYPE,  /* bDescriptorType: */								//USB�ӿ������� 0X04
    0x01,   /* bInterfaceNumber: Number of Interface */										//�ӿںţ���ǰ����֧�ֵĽӿ��������������㿪ʼ����
    0x00,   /* bAlternateSetting: Alternate setting */										//��ѡ���õ�����ֵ��
    0x02,   /* bNumEndpoints: Two endpoints used */												//�˽ӿ��õĶ˵����������������˵���˽ӿ�ֻ��ȱʡ���ƹܵ���
    0x0A,   /* bInterfaceClass: CDC */																		//�ӿ���������ֵ�� 0ֵΪ�����ı�׼������ ��������ֵ��ΪFFH����˽ӿ����ɳ���˵���� ����������ֵ��USB ˵��������0x0A CDC������
    0x00,   /* bInterfaceSubClass: */																			//������
    0x00,   /* bInterfaceProtocol: */																			//Э���룺bInterfaceClass ��bInterfaceSubClass ���ֵ����.���һ���ӿ�֧���豸����ص���������ֵָ�����豸��˵�����������Э��.
    0x00,   /* iInterface: */																							//�����˽ӿڵ��ִ������������ֵ��   
	 
		
		/*Endpoint 3 Descriptor*/																/*�˵�3����*/
		/********************����˵�3������******************/
    0x07,   /* bLength: Endpoint Descriptor size */
    USB_ENDPOINT_DESCRIPTOR_TYPE,   /* bDescriptorType: Endpoint */				//�˵��������� 0x04
    0x03,   /* bEndpointAddress: (OUT3) */																//�˵㣺���������������Ķ˵�ĵ�ַ������
																																					//		Bit 3..0 : �˵�ţ�Bit 6..4 : ����,Ϊ�㣬Bit 7: ����,������ƶ˵����ԡ�0������˵㣨�������豸����1������˵㣨�豸��������
    0x02,   /* bmAttributes: Bulk */																			//�������ͣ�Bit 1..0 :�������ͣ�00=���ƴ��ͣ�01=ͬ�����ͣ�10=�����ͣ�11=�жϴ���
    VIRTUAL_COM_PORT_DATA_SIZE,             /* wMaxPacketSize: */					//�˵��ܹ����ջ��͵�������ݰ��Ĵ�С������ʵ�����䣬��ֵ����Ϊÿ֡�����ݾ�����Ԥ��ʱ�䡣��ʵ������ʱ���ܵ����ܲ���ȫ��ҪԤ���Ĵ���ʵ�ʴ�������豸ͨ��һ�ַ�USB����Ļ��ƻ㱨�������������жϴ��䣬��������Ϳ��ƴ��䣬�˵���ܷ��ͱ�֮�̵����ݰ�
    0x00,
    0x00,   /* bInterval: ignore for Bulk transfer */											//�������ݴ���˵��ʱ���϶�������ֵ���������͵Ķ˵㼰���ƴ��͵Ķ˵������塣����ͬ�����͵Ķ˵�������Ϊ1����ʾ����Ϊ1ms�������жϴ��͵Ķ˵����ֵ�ķ�ΧΪ1ms��255ms��
    
		
		/*Endpoint 1 Descriptor*/
		/********************����˵�1������********************/
    0x07,   /* bLength: Endpoint Descriptor size */
    USB_ENDPOINT_DESCRIPTOR_TYPE,   /* bDescriptorType: Endpoint */				//�˵��������� 0x04
    0x81,   /* bEndpointAddress: (IN1) */																	//�˵㣺���������������Ķ˵�ĵ�ַ������
																																					//		Bit 3..0 : �˵�ţ�Bit 6..4 : ����,Ϊ�㣬Bit 7: ����,������ƶ˵����ԡ�0������˵㣨�������豸����1������˵㣨�豸��������
    0x02,   /* bmAttributes: Bulk */																			//�������ͣ�Bit 1..0 :�������ͣ�00=���ƴ��ͣ�01=ͬ�����ͣ�10=�����ͣ�11=�жϴ���
    VIRTUAL_COM_PORT_DATA_SIZE,             /* wMaxPacketSize: */					//�˵��ܹ����ջ��͵�������ݰ��Ĵ�С������ʵ�����䣬��ֵ����Ϊÿ֡�����ݾ�����Ԥ��ʱ�䡣��ʵ������ʱ���ܵ����ܲ���ȫ��ҪԤ���Ĵ���ʵ�ʴ�������豸ͨ��һ�ַ�USB����Ļ��ƻ㱨�������������жϴ��䣬��������Ϳ��ƴ��䣬�˵���ܷ��ͱ�֮�̵����ݰ�
    0x00,
    0x00,    /* bInterval */																								//�������ݴ���˵��ʱ���϶�������ֵ���������͵Ķ˵㼰���ƴ��͵Ķ˵������塣����ͬ�����͵Ķ˵�������Ϊ1����ʾ����Ϊ1ms�������жϴ��͵Ķ˵����ֵ�ķ�ΧΪ1ms��255ms��
};

/* USB String Descriptors */
const u8 Virtual_Com_Port_StringLangID[VIRTUAL_COM_PORT_SIZ_STRING_LANGID] =		//�ַ�������
  {
    VIRTUAL_COM_PORT_SIZ_STRING_LANGID,						//����������ֽ���
    USB_STRING_DESCRIPTOR_TYPE,										//�ִ����������ͣ��˴�ӦΪ0x03��
    0x09,																					//���Ա�ʶ��LANGID�� ��0
    0x04 /* LangID = 0x0409: U.S. English */			//���Ա�ʶ��LANGID�� ��X
  };

	
const u8 Virtual_Com_Port_StringVendor[VIRTUAL_COM_PORT_SIZ_STRING_VENDOR] =		//
  {
    VIRTUAL_COM_PORT_SIZ_STRING_VENDOR,     /* Size of Vendor string */
    USB_STRING_DESCRIPTOR_TYPE,             /* bDescriptorType	*/
    /* Manufacturer: "STMicroelectronics" */
    'S', 0, 'T', 0, 'M', 0, 'i', 0, 'c', 0, 'r', 0, 'o', 0, 'e', 0,
    'l', 0, 'e', 0, 'c', 0, 't', 0, 'r', 0, 'o', 0, 'n', 0, 'i', 0,
    'c', 0, 's', 0
  };

const u8 Virtual_Com_Port_StringProduct[VIRTUAL_COM_PORT_SIZ_STRING_PRODUCT] =
  {
    VIRTUAL_COM_PORT_SIZ_STRING_PRODUCT,          /* bLength */
    USB_STRING_DESCRIPTOR_TYPE,        /* bDescriptorType */
    /* Product name: "STM32 Virtual COM Port" */
    'S', 0, 'T', 0, 'M', 0, '3', 0, '2', 0, ' ', 0, 'V', 0, 'i', 0,
    'r', 0, 't', 0, 'u', 0, 'a', 0, 'l', 0, ' ', 0, 'C', 0, 'O', 0,
    'M', 0, ' ', 0, 'P', 0, 'o', 0, 'r', 0, 't', 0, ' ', 0, ' ', 0
  };

u8 Virtual_Com_Port_StringSerial[VIRTUAL_COM_PORT_SIZ_STRING_SERIAL] =
  {
    VIRTUAL_COM_PORT_SIZ_STRING_SERIAL,           /* bLength */
    USB_STRING_DESCRIPTOR_TYPE,                   /* bDescriptorType */
    'S', 0, 'T', 0, 'M', 0, '3', 0, '2', 0, '1', 0, '0', 0
  }
  ;/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/
