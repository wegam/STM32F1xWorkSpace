#include "CardReader.h"	


sFWS9RecDataDef		sFWS9RecData;			//���������յ������ݸ�ʽ
//sFWS9ReadDataDef	sFWS9ReadData;		//���������ʽ
//sFWS9WriteDataDef	sFWS9WriteData;		//д�������ʽ
sFWS9CmdDataDef	sFWS9ReadData	=			//���������ʽ
{
	eFWS9UsOutHead,									//֡ͷ��ʶ��:��λ���·�ʱ�̶�Ϊ0XE1����λ��Ӧ��ʱ�̶�Ϊ0XD2
	eFWS9CmdReadBlock,							//��������
	0x01,														//������
	0x01,														//��ţ�ÿ�������Ŀ�Ϊ0.1.2.������Ч��
	eKEYA,													//��Կģʽ KEYA��0x60��/KEYB(0x61) Ĭ��KEYA
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,	//6�ֽ����룬Ĭ��0xFF,0xFF,0xFF,0xFF,0xFF,0xFF
	0xFFFF,													//CRC16
	eFWS9UsOutEnd										//֡β����λ���·�ʱ�̶�Ϊ0X1E����λ��Ӧ��ʱ�̶�Ϊ0X2D��
};
sFWS9CmdDataDef	sFWS9SetArea	=			//���ö�������
{
	eFWS9UsOutHead,									//֡ͷ��ʶ��:��λ���·�ʱ�̶�Ϊ0XE1����λ��Ӧ��ʱ�̶�Ϊ0XD2
	eFWS9CmdSetBlock,								//��������
	0x01,														//������
	0x01,														//��ţ�ÿ�������Ŀ�Ϊ0.1.2.������Ч��
	eKEYA,													//��Կģʽ KEYA��0x60��/KEYB(0x61) Ĭ��KEYA
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,	//6�ֽ����룬Ĭ��0xFF,0xFF,0xFF,0xFF,0xFF,0xFF
	0xFFFF,													//CRC16
	eFWS9UsOutEnd										//֡β����λ���·�ʱ�̶�Ϊ0X1E����λ��Ӧ��ʱ�̶�Ϊ0X2D��
};
/*******************************************************************************
*������			:	function
*��������		:	function
*����				: 
*����ֵ			:	��
*�޸�ʱ��		:	��
*�޸�˵��		:	��
*ע��				:	wegam@sina.com
*******************************************************************************/
void FWS9_Initialize(void)						//������ʼ��
{
}