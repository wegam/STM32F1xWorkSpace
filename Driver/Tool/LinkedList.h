#ifndef __FIFO_H
#define __FIFO_H


typedef struct _LINK_NODE
{	
	unsigned short 	DataLen;			//�洢�����ݳ���
	unsigned short  Serial;				//�洢�����  
	char 						*DataAddr;	//���ݶ�̬�洢�ռ�
  struct _LINK_NODE* PrevNode;	//��һ���ڵ�:��˫������ʱʹ��
	struct _LINK_NODE* NextNode;	//��һ���ڵ�	:
}LINK_NODE;


//typedef struct _LINK_LIST
//{
//	unsigned long	*HeadNodeAddr;	//ͷ����ַ
//	unsigned long	*LastNodeAddr;	//β����ַ
//	
//	unsigned long 	Length;			//����������ݳ���
//	char* 					DataAddr;		//���������ݵ�ַ
//}LINK_LIST;

//typedef struct _LINK_LIST
//{
//	unsigned long 	ListLength;			//�洢��������
//	unsigned long 	DataLength;		  //����������ݳ���
//	char 						DataAddr[5];		//���������ݵ�ַ
//	
//	LINK_NODE	*HeadNode;		//ͷ���--
//	LINK_NODE	*LastNode;		//β���--����ԭ�������һ�����ĵ�ַ	
//}LINK_LIST;


static LINK_NODE *CreateNode(char* DataAddr,unsigned long DataLength);										//�������
static LINK_NODE *InsertNode(LINK_NODE* HeadNODEx,LINK_NODE* NewNODEx);									//������
static LINK_NODE *AddNode(LINK_NODE* EndNODEx,LINK_NODE* NewNODEx);											//��β���������½�㣬�����¸���β��㣬�����µ�β����ַ
static LINK_NODE *DeleteNode(LINK_NODE* DelNODEx);																			//ɾ�����
static LINK_NODE *GetEndNode(LINK_NODE* DelNODEx);																				//���ұ�β
LINK_NODE *FindData(LINK_NODE	*HeadNODE,char* DataAddr,unsigned long DataLength);	//����������ݽ��

unsigned long GetListLength(LINK_NODE* HeadNODEx);																		//��ȡ������

unsigned short FIFO_IN  (LINK_NODE	**EndNode,char* SaveAddr,unsigned short SaveLength);	//FIFO�洢����---First in, First out
unsigned short FIFO_OUT	(LINK_NODE	**DATAx,char* ReadAddr);										    //FIFO�������---First in, First out
LINK_NODE* FIFO_DEL	(LINK_NODE	*DelNode);	//FIFOɾ����Ӧ���ݵĽ��

unsigned long LIFO_IN		(LINK_NODE	*LISTx,char* SaveAddr,unsigned long SaveLength);	//LIFO�洢����---Last in, First out
LINK_NODE* LIFO_OUT	(LINK_NODE	*LISTx,char* ReadAddr);														//LIFO�������---Last in, First out

unsigned long LinkListTest(LINK_NODE	*LISTx,char* DataAddr,unsigned long SaveLength,unsigned char CMD);		//�������


#endif


