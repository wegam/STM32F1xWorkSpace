#ifndef __FIFO_H
#define __FIFO_H


typedef struct _LINK_NODE
{	
	unsigned long 	DataLen;			//存储的数据长度
	unsigned long	  Serial;				//存储的序号  
	char 						*DataAddr;	//数据动态存储空间
  struct _LINK_NODE* PrevNode;	//上一个节点:仅双向链表时使用
	struct _LINK_NODE* NextNode;	//下一个节点	:
}LINK_NODE;


//typedef struct _LINK_LIST
//{
//	unsigned long	*HeadNodeAddr;	//头结点地址
//	unsigned long	*LastNodeAddr;	//尾结点地址
//	
//	unsigned long 	Length;			//待保存的数据长度
//	char* 					DataAddr;		//待保存数据地址
//}LINK_LIST;

//typedef struct _LINK_LIST
//{
//	unsigned long 	ListLength;			//存储的链表长度
//	unsigned long 	DataLength;		  //待保存的数据长度
//	char 						DataAddr[5];		//待保存数据地址
//	
//	LINK_NODE	*HeadNode;		//头结点--
//	LINK_NODE	*LastNode;		//尾结点--保存原链表最后一个结点的地址	
//}LINK_LIST;


static LINK_NODE *CreateNode(char* DataAddr,unsigned long DataLength);										//创建结点
static LINK_NODE *InsertNode(LINK_NODE* HeadNODEx,LINK_NODE* NewNODEx);									//插入结点
static LINK_NODE *AddNode(LINK_NODE* EndNODEx,LINK_NODE* NewNODEx);											//从尾结点后增加新结点，并重新更新尾结点，返回新的尾结点地址
static LINK_NODE *DeleteNode(LINK_NODE* DelNODEx);																			//删除结点
static LINK_NODE *GetEndNode(LINK_NODE* DelNODEx);																				//查找表尾
LINK_NODE *FindData(LINK_NODE	*HeadNODE,char* DataAddr,unsigned long DataLength);	//查找相关数据结点

unsigned long GetListLength(LINK_NODE* HeadNODEx);																		//获取链表长度

LINK_NODE* FIFO_IN  (LINK_NODE	**EndNode,char* SaveAddr,unsigned long SaveLength);	//FIFO存储数据---First in, First out
LINK_NODE* FIFO_OUT	(LINK_NODE	**DATAx,char* ReadAddr);														//FIFO输出数据---First in, First out
LINK_NODE* FIFO_DEL	(LINK_NODE	*DelNode);	//FIFO删除相应数据的结点

unsigned long LIFO_IN		(LINK_NODE	*LISTx,char* SaveAddr,unsigned long SaveLength);	//LIFO存储数据---Last in, First out
LINK_NODE* LIFO_OUT	(LINK_NODE	*LISTx,char* ReadAddr);														//LIFO输出数据---Last in, First out

unsigned long LinkListTest(LINK_NODE	*LISTx,char* DataAddr,unsigned long SaveLength,unsigned char CMD);		//链表测试


#endif


