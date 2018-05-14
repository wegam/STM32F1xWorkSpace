#ifndef __HC_RS232_H
#define __HC_RS232_H








typedef enum	_Head
{
	Head1		=	0xFA,
	Head2		=	0xF5,
}HeadDef;


typedef enum	_Cmd
{
	GetStatus	=	1,
	GetData		=	2,
	SetStatus	=	3,
	SetData		=	4,
}CmdDef;

//typedef	struct	_Communication
//{
//	HeadDef Head1;
//	HeadDef Head2;
//	CmdDef	Cmd;
//}CommunicationDef;


typedef	struct	_Borad_Info
{
	unsigned int	SerialNum;				//–Ú¡–∫≈
	const char		*Borad_Name;			//PCB∞Â√˚
}Borad_InfoDef;












#endif



