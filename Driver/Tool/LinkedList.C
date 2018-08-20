/************************************ TOOLS ************************************
* 文件名 	: LinkedList链表
* 作者   	: wegam@sina.com
* 版本   	: V
* 日期   	: 2017/09/11
* 说明   	: 
********************************************************************************
其它说明:
*
*
*
*
*
*
*
*
*******************************************************************************/
#include 	"LinkedList.H"

#include	"stdio.h"				//用于printf
#include	"string.h"			//用于printf
#include	"stdarg.h"			//用于获取不确定个数的参数
#include	"stdlib.h"			//malloc动态申请内存空间

//LINK_NODE** pNODE;
//===============================================================================
//函数:	CreateNode
//描述:	创建节点
//输入:	DataLenth-待存储的数据长度
//返回:	NULL--空地址,表示申请失败;否则返回创建的节点地址
//===============================================================================
static LINK_NODE *CreateNode(char* DataAddr,unsigned long DataLength)
{
	LINK_NODE *NewNode; 		//NewNode保存创建的新结点的地址
  char *Addr;
	if(DataLength==0	||	DataAddr==NULL)				//数据长度为0,不执行
	{
		return	NULL;
	}
	//==================为此结点申请动态空间
	NewNode = (LINK_NODE *) malloc (sizeof(LINK_NODE)); 	//开辟一个新结点(申请动态存储空间)

	if (NULL == NewNode)	//申请失败
	{
		return NULL;				//返回空地址
	}
	else									//申请成功:下一步申请数据空间
	{
		//==================为此结点申请数据存储空间----使用动态存储空间方式
		Addr	= (char *) malloc (DataLength);			//申请数据存储动态存储空间
		if(NULL	== Addr)	//数据空间申请失败:释放结点,返回NULL
		{
			free(NewNode);								//释放建立的新结点
			return NULL;									//返回空地址
		}
    NewNode->DataAddr = Addr;
		NewNode->NextNode = NULL;
		NewNode->DataLen  = DataLength;											//此结点存储的数据大小
		memcpy(NewNode->DataAddr,DataAddr,DataLength);		//复制数据		
	}
	return	NewNode;					//返回尾结点的地址:准备结尾结点添加数据
}
//===============================================================================
//函数:	InsertNode
//描述:	在头结点前面插入新结点
//输入:	HeadNODEx-头结点,NewNODEx-待插入的结点
//返回:	插入的结点地址
//===============================================================================
static LINK_NODE *InsertNode(LINK_NODE* HeadNODEx,LINK_NODE* NewNODEx)
{
	if(HeadNODEx==NULL)						//头结点为空结点----新链表
	{
		NewNODEx->PrevNode	=	NULL;	//第一个结点的上结点为空结点
		NewNODEx->NextNode	=	NULL;	//新建立的链表的下一结点为空结点
		return	NewNODEx;
	}
	//==================非空结点
	else													//头结点非空结点
	{		
		if(HeadNODEx->PrevNode	==NULL)			//头结点的上结点为空
		{
			NewNODEx->PrevNode	=	NULL;				//新结点的上结点为空
			NewNODEx->NextNode	=	HeadNODEx;	//新结点的下结点到头结点
			HeadNODEx->PrevNode	=	NewNODEx;		//头结点的上结点连接到新结点
		}
		else																											//头结点的上结点非空
		{
			NewNODEx->PrevNode	=	HeadNODEx->PrevNode->NextNode;		//新结点	的上结点连接到头结点的上结点
			NewNODEx->NextNode	=	HeadNODEx;												//新结点的下结点连接到头结点
			HeadNODEx->PrevNode->NextNode=NewNODEx;									//头结点的上结点的下结点连接到新结点
			HeadNODEx->PrevNode=NewNODEx;														//头结点的上结点连接到新结点
		}
		return	NewNODEx;
	}
}
//===============================================================================
//函数:	InsertNode
//描述:	从尾结点后增加新结点，并重新更新尾结点，返回新的尾结点地址
//输入:	EndNODEx-尾结点,NewNODEx-待添加的结点
//返回:	新的头结点地址
//===============================================================================
static LINK_NODE *AddNode(LINK_NODE* EndNODEx,LINK_NODE* NewNODEx)
{
	if(EndNODEx==NULL)						//头结点为空结点----新链表
	{
		NewNODEx->PrevNode	=	NULL;	//第一个结点的上结点为空结点
		NewNODEx->NextNode	=	NULL;	//新建立的链表的下一结点为空结点
		EndNODEx	=	NewNODEx;				//
		return	NewNODEx;
	}
	//==================非空结点
	else													//头结点非空结点
	{
    LINK_NODE* TempNODEx  = EndNODEx;   //备份新结点
    TempNODEx->NextNode   = NewNODEx;   //尾结点的下结点连接到新结点
    NewNODEx ->PrevNode   = EndNODEx;   //新结点的上结点指向尾结点
    
    NewNODEx->NextNode    = NULL;       //新结点的尾结点为空
    EndNODEx =  NewNODEx;               //更新尾结点
		return	EndNODEx;
	}
}
//===============================================================================
//函数:	DeleteNode
//描述:	删除本结点
//输入:	HeadNODEx-删除的结点
//返回:	
//===============================================================================
static LINK_NODE *DeleteNode(LINK_NODE* DelNODEx)
{
	LINK_NODE* pNODE;
	
	pNODE = DelNODEx;
	//==================判断结点是否为空
	if(pNODE	==	NULL)
	{
		return NULL;
	}
//	//==================动态数据方式:需要释放数据空间
//	free(pNODE->DataAddr);										//释放数据空间
	//==================结点头尾判断
	if(DelNODEx->PrevNode==NULL)			//----------------上一个结点为空
	{
		if(DelNODEx->NextNode==NULL)										//上一个结点为空,下一个结点为空
		{
      free(DelNODEx->DataAddr);									  //释放结点内数据缓存
			free(DelNODEx);															//释放已删除结点
			DelNODEx	=	NULL;													//删除地址
		}
		else																				//上一个结点为空,下一个结点非空
		{
			DelNODEx	=	DelNODEx->NextNode;				    //待删除结点地址更新为下一结点地址
			DelNODEx->PrevNode		=	NULL;	            //下一结点的头结点更改为空结点
      free(pNODE->DataAddr);									  //释放结点内数据缓存
			free(pNODE);															//释放已删除结点
		}
	}
	else													//----------------上一个结点非空
	{
		if(DelNODEx->NextNode==NULL)										//上一个结点非空,下一个结点为空
		{
			DelNODEx->PrevNode->NextNode	=	NULL;		//上结点的尾结点设置为空
			DelNODEx	=	DelNODEx->PrevNode;			//此结点地址更新为上一结点地址
      free(pNODE->DataAddr);									  //释放结点内数据缓存
			free(pNODE);															//释放已删除结点
		}
		else											//----------------上一个结点非空,下一个结点非空
		{
      DelNODEx->PrevNode->NextNode=DelNODEx->NextNode;	//上结点尾结点连接到此结点的下结点
			DelNODEx->NextNode->PrevNode=DelNODEx->PrevNode;	//些结点的下结点的头结点连接到些结点的上结点
      DelNODEx  = DelNODEx->PrevNode;			              //此结点地址更新为上一结点地址
      free(pNODE->DataAddr);									  //释放结点内数据缓存
			free(pNODE);															//释放已删除结点
		}
	}
	return DelNODEx;						//返回新结点地址
}
//===============================================================================
//函数:	DeleteNode
//描述:	删除本结点
//输入:	HeadNODEx-头结点,NewNODEx-待插入的结点
//返回:	头结点
//===============================================================================
static LINK_NODE *GetEndNode(LINK_NODE* DelNODEx)
{
	LINK_NODE* pNODE;
	pNODE	=	DelNODEx;
	if(pNODE	==	NULL)
	{
		return NULL;
	}
	if(pNODE->NextNode	==NULL)
	{
		return pNODE;
	}
	else
	{
		GetEndNode(pNODE->NextNode);
	}
	return pNODE;
}
//===============================================================================
//函数: FindData
//描述: 从头结点开始查找相关数据结点
//输入: HeadNODE-头结点,DataAddr-待查找的数据,DataLength-数据长度
//返回: 找到数据，返回结点地址，否则返回NULL
//===============================================================================
LINK_NODE *FindData(LINK_NODE	*HeadNODE,char* DataAddr,unsigned long DataLength)
{
	unsigned short i	=0;
	LINK_NODE* TempNODEx	=	NULL;
	
	if(HeadNODE	==	NULL)   //空结点
	{
		return NULL;
	}
	TempNODEx	=	HeadNODE;
	for(i=0;i<0xFF;i++)
	{
		if(TempNODEx  ==	NULL)
		{
			return NULL;
		}
		else if(memcmp(TempNODEx->DataAddr,DataAddr,DataLength)	==	0)				//查找到数据//比较内存数据相等
		{
			return	TempNODEx;
		}
		else
		{
			TempNODEx	=	TempNODEx->NextNode;
		}
	}
	return NULL;
}
//===============================================================================
//函数:	GetListLength
//描述:	获取链表长度
//输入:	HeadNODEx-链表头结点:第一个结点
//返回:	链表的长度
//===============================================================================
unsigned long GetListLength(LINK_NODE* HeadNODEx)
{
	if(HeadNODEx==NULL)			//结点为空
	{
		return 0;					//
	}
	return	1+GetListLength(HeadNODEx->NextNode);
}
//===============================================================================
//函数:	FIFO_IN--入列:FIFO存储数据---First in, First out
//描述:	存储数据，将数据存入到尾结点，并更新尾结点地址
//输入:	EndNode-尾结点
//输入:	DataAddr-待存储的数据地址
//输入:	DataLenth-待存储的数据长度
//返回:	入列结果0--失败,SaveLength--已经保存的数据大小
//===============================================================================
LINK_NODE*  FIFO_IN(LINK_NODE	**EndNode,char* SaveAddr,unsigned long SaveLength)
{
	//==================临时变量
	LINK_NODE *NewNode = NULL; 											//新建临时结点
  LINK_NODE *TempNode = *EndNode; 							  //临时结点
	//==================创建结点:返回结点地址
	NewNode	=	CreateNode(SaveAddr,SaveLength);			//得到新申请的结点地址
	//==================判断申请结点结果			
	if(NewNode==NULL)		//申请失败
	{
		return *EndNode;	  //退出,返回0
	}
  //==================空链表
  if(NULL ==  TempNode)
  {
    NewNode->NextNode = NULL;
    NewNode->PrevNode = NULL;
    *EndNode = NewNode;
    return  NewNode;
  }
  else
  {
    LINK_NODE*  TempNode  = *EndNode;
    unsigned char i=0;
    for(i=0;i<0xFF;i++)
    {
      if(NULL ==  TempNode->NextNode)
      {
        break;
      }
      TempNode  = TempNode->NextNode;
    }
    TempNode->NextNode  = NewNode;
    NewNode->PrevNode   = TempNode;
    NewNode->NextNode   = NULL;
    *EndNode = NewNode;
  }
	//==================判断此链表是否为空链表(头结点是否为空)
	
	return	*EndNode;
}

//===============================================================================
//函数:	FIFO_OUT--出列:FIFO输出数据---First in, First out
//描述:	读出数据--从HeadNode读取,读取完,HeadNode指向下一个地址后释放已读取完的结点
//输入:	DataAddr--数据地址
//返回:	DataLenth---存储的数据大小
//===============================================================================
LINK_NODE* FIFO_OUT(LINK_NODE	**HeadNode,char* ReadAddr)
{
  LINK_NODE *TempNode = *HeadNode; 							  //临时结点
	//==================空结点
	if(TempNode==NULL)							//链表头结点为空---空链表
	{
		return NULL;												  //退出
	}
	//==================非空结点
	else		
	{
		//==================复制数据
		memcpy(ReadAddr,TempNode->DataAddr,TempNode->DataLen);	          //复制结点内数据到链表缓存
    //==================数据已读出，删除些结点，更新头结点地址
//    HeadNode  = DeleteNode(HeadNode);																  //删除结点
    if(NULL !=  TempNode->NextNode)                           //链表还有结点
    {
      *HeadNode  = TempNode  ->NextNode;
      free(TempNode->DataAddr);                               //释放结点内数据缓存
      free(TempNode);                                         //释放已删除结点
    }
    else
    {
      free(TempNode->DataAddr);                               //释放结点内数据缓存
      free(TempNode);                                         //释放已删除结点
      *HeadNode  = NULL;
    }
		return *HeadNode;					//返回数据宽度
	}
}
//===============================================================================
//函数:	FIFO_DEL
//描述:	FIFO删除相应数据的结点
//输入:	HeadNODEx-头结点,NewNODEx-待插入的结点
//返回:	头结点
//===============================================================================
LINK_NODE* FIFO_DEL(LINK_NODE	*DelNode)
{
	if(NULL ==  DelNode)
	{
		return 0;
	}
  if(NULL ==  DelNode->PrevNode)    //头结点为空
  {
    if(NULL ==  DelNode->NextNode)  //尾结点为空
    {
      free(DelNode->DataAddr);      //释放结点内数据缓存
      free(DelNode);                //释放已删除结点
      DelNode = NULL;
    }
    else
    {
      LINK_NODE* pNODE	=	DelNode;
      DelNode = DelNode->NextNode;
      free(pNODE->DataAddr);        //释放结点内数据缓存
      free(pNODE);                  //释放已删除结点
    }
  }
  
  else                              //头结点非空
  {
    if(NULL ==  DelNode->NextNode)  //尾结点为空
    {
      LINK_NODE* pNODE	=	DelNode;
      DelNode = DelNode->NextNode;
      DelNode->PrevNode = NULL;
      free(pNODE->DataAddr);        //释放结点内数据缓存
      free(pNODE);                  //释放已删除结点
    }
    else
    {
      LINK_NODE* pNODE	=	DelNode;
      DelNode->PrevNode->NextNode = DelNode->NextNode;
      DelNode->NextNode->PrevNode = DelNode->PrevNode;
      DelNode = DelNode->PrevNode;
      free(pNODE->DataAddr);        //释放结点内数据缓存
      free(pNODE);                  //释放已删除结点
    }
  }
	return DelNode;	
}
//===============================================================================
//函数:	LIFO_IN--入栈:单向链表:LIFO存储数据---Last in, First out
//描述:	与FIFO_IN不同之处为在链表头添加数据，并且更新头结点地址为新结点
//输入:	DataAddr-待存储的数据地址
//输入:	DataLenth-待存储的数据长度
//返回:	入列结果0--失败,SaveLength--已经保存的数据大小
//===============================================================================
unsigned long LIFO_IN(LINK_NODE	*HeadNode,char* SaveAddr,unsigned long SaveLength)
{
	LINK_NODE *NewNode = NULL; 											//临时数据
//	HeadNode->DataLen	=	SaveLength;							    //保存待存储的数据大小
	NewNode	=	CreateNode(SaveAddr,SaveLength);		  //得到新申请的结点地址
						
	if(NewNode==NULL)		//申请失败
	{
		return 0;					//
	}
  //在头结点前插入新结点
  if(NULL ==  HeadNode)                     //头结点为空结点
  {
    NewNode->NextNode = NULL;
    NewNode->PrevNode = NULL;
    HeadNode  = NewNode;
  }
  else
  {
    LINK_NODE*  TempNode  = HeadNode;
    unsigned char i=0;
    for(i=0;i<0xFF;i++)
    {
      if(NULL ==  TempNode->PrevNode)
      {
        break;
      }
      TempNode  = TempNode->PrevNode;
    }
    NewNode->NextNode = TempNode;
    NewNode->PrevNode = NULL;
    HeadNode  = NewNode;                    //更新头结点
    
  }
	return	SaveLength;
}

//===============================================================================
//函数:	LIFO_OUT--出栈:单向链表:LIFO输出数据---Last in, First out
//描述:	出栈,找到尾结点，将数据拷贝到ReadAddr，释放尾结点，并重新更新尾结点地址
//输入:	DataAddr--数据地址
//返回:	DataLenth---存储的数据大小
//===============================================================================
LINK_NODE* LIFO_OUT(LINK_NODE	*EndNode,char* ReadAddr)
{
	//==================空结点
	if(EndNode==NULL)							//链表头结点为空---空链表
	{
		return 0;														//退出
	}
	//==================非空结点
	else		
	{
    LINK_NODE*  TempNode  = EndNode;
    do
    {
      TempNode  = TempNode->NextNode;
    }
    while(NULL ==  TempNode->NextNode);
    TempNode->PrevNode->NextNode  = NULL;
    EndNode = TempNode->PrevNode;
    memcpy(ReadAddr,TempNode->DataAddr,TempNode->DataLen);                //复制数据
    free(TempNode->DataAddr);                               //释放结点内数据缓存
    free(TempNode);                                         //释放已删除结点
    
		return EndNode;																			    //返回新的尾结点地址
	}
}
//===============================================================================
//函数:	ListTest
//描述:	
//输入:	
//返回:	
//===============================================================================
unsigned long LinkListTest(LINK_NODE	*LISTx,char* DataAddr,unsigned long SaveLength,unsigned char CMD)
{
	unsigned long	RevLength	=	0;
//	//===========================FIFO测试
//	//--------------------入列			----命令0x01;
//	if(CMD	==	0x01)
//	{
//		RevLength	=	FIFO_IN(LISTx,DataAddr,SaveLength);		//FIFO存储数据---First in, First out
//	}
//	//--------------------出列			----命令0x02
//	else if(CMD	==	0x02)
//	{
//		RevLength	=	FIFO_OUT(LISTx,DataAddr);							//FIFO输出数据---First in, First out
//	}	
//	//--------------------删除结点		----命令0x03
//	else if(CMD	==	0x03)
//	{
//		RevLength	=	FIFO_DEL(LISTx,DataAddr,SaveLength);	//FIFO删除相应数据的结点
//	}
//	//--------------------查找数据		----命令0x04
//	else if(CMD	==	0x04)
//	{
//	}
//	//--------------------清空链表		----命令0x05
//	else if(CMD	==	0x05)
//	{
//	}
//	
//	
//	//===========================LIFO测试
//	//--------------------入列			----命令0x11
//	else if(CMD	==	0x11)
//	{
//	}
//	//--------------------出列			----命令0x12
//	else if(CMD	==	0x11)
//	{
//	}
//	//--------------------删除结点		----命令0x13
//	else if(CMD	==	0x11)
//	{
//	}
//	//--------------------查找数据		----命令0x14
//	else if(CMD	==	0x11)
//	{
//	}
//	//--------------------清空链表		----命令0x15
//	else if(CMD	==	0x11)
//	{
//	}
//	return RevLength;
}



