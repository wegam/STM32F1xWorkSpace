#ifndef __CardReader_H
#define __CardReader_H 



#include "stdint.h"

//============================================================================================������Э��Start
//-----------------------------------------------------------------------------------ö����
typedef enum	_eFWS9UsHead			//֡ͷ��ʶ��
{
	eFWS9UsOutHead		=	0xE1,		//֡ͷ,��λ���·�ʱ�̶�Ϊ0XE1����λ��Ӧ��ʱ�̶�Ϊ0XD2
	eFWS9UsInHead			=	0xD2,		//֡ͷ,��λ���·�ʱ�̶�Ϊ0XE1����λ��Ӧ��ʱ�̶�Ϊ0XD2
}eFWS9UsHeadDef;
typedef enum	_eFWS9UsEnd				//֡β��ʶ��
{
	eFWS9UsOutEnd				=	0x1E,		//֡β����λ���·�ʱ�̶�Ϊ0X1E����λ��Ӧ��ʱ�̶�Ϊ0X2D��
	eFWS9UsInEnd				=	0x2D,		//֡β����λ���·�ʱ�̶�Ϊ0X1E����λ��Ӧ��ʱ�̶�Ϊ0X2D��
}eFWS9UsEndDef;
typedef enum	_eFWS9Cmd					//��������
{
	eFWS9CmdReadBlock		=	0x24,		//0x24 �����������ÿ�������Ŀ�Ϊ0.1.2.������Ч��[1�ֽ�������+1�ֽڿ��+1�ֽ���Կģʽ��0x60\0x61��+ 6�ֽ�����(����-FF FF FF FF FF FF)]
	eFWS9CmdWriteBlock	=	0x25,		//0x25 д���������ÿ�������Ŀ�Ϊ0.1.2.������Ч��[1�ֽ�������+1�ֽڿ��+1�ֽ���Կģʽ��0x60\0x61��+ 6�ֽ����� + 16�ֽ�����]
	eFWS9CmdSetBlock		=	0x44,		//0x44 ���ö�ͷ������������š�KEYA/KEYB����������	[1�ֽ�������+1�ֽڿ��+1�ֽ���Կģʽ��0x60\0x61��+ 6�ֽ�����(����-FF FF FF FF FF FF)]
}eFWS9CmdDef;
typedef enum	_eFWS9ErrCode			//��������
{
	eFWS9NoErr					=	0x00,			//�ɹ����޴���
	eFWS9NoCard					=	0x01,			//�ڲ����������޿�
}eFWS9ErrCodeDef;

typedef enum	_eFWS9KeyType			//��Կģʽ KEYA��0x60��/KEYB(0x61)
{
	eKEYA				=	0x60,			//
	eKEYB				=	0x61,			//
}eFWS9KeyDef;

//-----------------------------------------------------------------------------------�ṹ��
//------------------------------------------CRC16
typedef	struct	_eFWS9CRC16
{
	unsigned char CRC_H;			//CRC��8λ
	unsigned char CRC_L;			//CRC��8λ
}eFWS9CRC16Def;
//------------------------------------------���������ؿ����ݽṹ��
typedef	struct	_sFWS9RecData	//���������յ������ݸ�ʽ
{
	eFWS9UsHeadDef	Head;				//֡ͷ��ʶ��:��λ���·�ʱ�̶�Ϊ0XE1����λ��Ӧ��ʱ�̶�Ϊ0XD2
	eFWS9CmdDef			Cmd;				//��������
	eFWS9ErrCodeDef Err;				//��������
	unsigned char 	data[16];		//����ڶ���ʱ���޴���ᷢ��16�ֽڿ�����
	unsigned short 	CRC16;			//CRC16
	eFWS9UsEndDef 	End;				//֡β����λ���·�ʱ�̶�Ϊ0X1E����λ��Ӧ��ʱ�̶�Ϊ0X2D��
}sFWS9RecDataDef;

typedef	struct	_sFWS9CmdData		//���Ͷ������������ݸ�ʽ
{
	eFWS9UsHeadDef	Head;					//֡ͷ��ʶ��:��λ���·�ʱ�̶�Ϊ0XE1����λ��Ӧ��ʱ�̶�Ϊ0XD2
	eFWS9CmdDef			Cmd;					//��������
	unsigned char 	Sector;				//������
	unsigned char 	Block;				//��ţ�ÿ�������Ŀ�Ϊ0.1.2.������Ч��
	eFWS9KeyDef			KeyType;			//��Կģʽ KEYA��0x60��/KEYB(0x61) Ĭ��KEYA
	unsigned char 	PassWord[6];	//6�ֽ����룬Ĭ��0xFF,0xFF,0xFF,0xFF,0xFF,0xFF
	unsigned short 	CRC16;				//CRC16
	eFWS9UsEndDef 	End;					//֡β����λ���·�ʱ�̶�Ϊ0X1E����λ��Ӧ��ʱ�̶�Ϊ0X2D��
}sFWS9CmdDataDef;


typedef	struct	_sFWS9WriteData		//д�������ʽ
{
	eFWS9UsHeadDef	Head;					//֡ͷ��ʶ��:��λ���·�ʱ�̶�Ϊ0XE1����λ��Ӧ��ʱ�̶�Ϊ0XD2
	eFWS9CmdDef			Cmd;					//��������
	unsigned char 	Sector;				//������
	unsigned char 	Block;				//��ţ�ÿ�������Ŀ�Ϊ0.1.2.������Ч��
	eFWS9KeyDef			KeyType;			//��Կģʽ KEYA��0x60��/KEYB(0x61) Ĭ��KEYA
	unsigned char 	PassWord[6];	//6�ֽ����룬Ĭ��0xFF,0xFF,0xFF,0xFF,0xFF,0xFF
	unsigned char 	data[16];			//д��ʱΪ��д���16�ֽ�����
	unsigned short 	CRC16;				//CRC16
	eFWS9UsEndDef 	End;					//֡β����λ���·�ʱ�̶�Ϊ0X1E����λ��Ӧ��ʱ�̶�Ϊ0X2D��
}sFWS9WriteDataDef;

typedef	struct	_sFWS9SetArea		//���ö�ͷ������������š�KEYA��0x60��/KEYB(0x61)����������0x44
{
	eFWS9UsHeadDef	Head;					//֡ͷ��ʶ��:��λ���·�ʱ�̶�Ϊ0XE1����λ��Ӧ��ʱ�̶�Ϊ0XD2
	eFWS9CmdDef			Cmd;					//��������
	unsigned char 	Sector;				//������
	unsigned char 	Block;				//��ţ�ÿ�������Ŀ�Ϊ0.1.2.������Ч��
	eFWS9KeyDef			KeyType;			//��Կģʽ KEYA��0x60��/KEYB(0x61) Ĭ��KEYA
	unsigned char 	PassWord[6];	//6�ֽ����룬Ĭ��0xFF,0xFF,0xFF,0xFF,0xFF,0xFF
	unsigned short 	CRC16;				//CRC16
	eFWS9UsEndDef 	End;					//֡β����λ���·�ʱ�̶�Ϊ0X1E����λ��Ӧ��ʱ�̶�Ϊ0X2D��
}sFWS9SetAreaDef;

//-----------------------------------------------------------------------------------ͷ�ļ�
extern sFWS9RecDataDef		sFWS9RecData;			//���������յ������ݸ�ʽ
extern sFWS9CmdDataDef		sFWS9ReadData;		//���������ʽ
extern sFWS9CmdDataDef		sFWS9SetArea;			//���ö�������
extern sFWS9WriteDataDef	sFWS9WriteData;		//д�������ʽ

    
#endif

