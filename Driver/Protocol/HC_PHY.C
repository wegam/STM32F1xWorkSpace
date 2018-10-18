

#include "HC_PHY.H"
#include "TOOL.H"		//数据校验工具

#include	"stdio.h"			//用于printf
#include	"string.h"		//用于printf
#include	"stdarg.h"		//用于获取不确定个数的参数
#include	"stdlib.h"		//malloc动态申请内存空间


extern CommDef CommFun;

unsigned char	SerialU	=	0;							  //往上层上传流水号 0x01~0x7D 每次使用后加1(为了不与起始符和结束符冲突，流水号最大值为0x7D)
unsigned char	SerialD	=	0;							  //往下层下发流水号 0x01~0x7D 每次使用后加1(为了不与起始符和结束符冲突，流水号最大值为0x7D)

AckDef		ACKU;									//响应上级的应答
AckDef		ACKD;									//响应下级的应答

TransDef  TransU;     //向上传送缓冲区
TransDef  TransD;     //向下传送缓冲区

DataNodeDef	DataNodeU[MaxNetPerLayer+1];  //向上传输数据缓存队列
DataNodeDef	DataNodeD[MaxNetPerLayer+1];  //向下传输数据缓存队列，DataNodeD[0]存储广播消息
DataNodeDef ProcessNode[SelfBuffSize];    //本地址需要处理的消息缓存(不需要转发给下一层的消息)
DataNodeDef SendNode[SelfBuffSize];       //本地址需要上传的(不需要转发给下一层的消息)


RS485FrameDef RunFrame;

static HCSYSDef	HCSYS;


unsigned short 	gValidLength	= 0;	//buffer中有效数据长度(从RS485头标识符开始后的数据为有效数据)


/*******************************************************************************
* 函数名			:	function
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
HCResult HCBoradSet(const unsigned char Layer,const unsigned char id)
{
	HCResult res	  	=	  RES_OK;
	HCSYS.Layer			  = 	Layer;  //0-网关层，1-单元板层CabinetAddr，2-层控制板层LayerAddr，3,-驱动层SlotAddr
	HCSYS.SwitchAddr	= 	id;
	return res;
}

/*******************************************************************************
* 函数名			:	APIRS485SetUplinkData
* 功能描述		:	上端接口 
* 输入			: buffer  输入的数据缓存地址
              length  输入的数据长度
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
HCResult APIRS485UplinkSetData(const unsigned char *buffer,const unsigned short length)
{

}
/*******************************************************************************
* 函数名			:	APIRS485SetDownlinkData
* 功能描述		:	下端接口
* 输入			: buffer  输入的数据缓存地址
              length  输入的数据长度
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
HCResult APIRS485DownlinkSetData(const unsigned char *buffer,const unsigned short length)
{
	unsigned char i	=	0;
	for(i=0;i<MaxNetPerLayer;i++)
	{
		
	}
}
/*******************************************************************************
* 函数名			:	APIRS485SendData
* 功能描述		:	发送数据(打包，存入发送缓冲区)
* 输入			: buffer  输入的数据缓存地址
              length  输入的数据长度
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
HCResult APIRS485SendData(const unsigned char *buffer,const unsigned short length)
{
 
}
/*******************************************************************************
* 函数名			:	APIRS485ProcessData
* 功能描述		:	获取需要处理的数据
* 输入			: buffer  输入的数据缓存地址
              length  输入的数据长度
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
unsigned short APIRS485ProcessData(unsigned char *buffer)
{

}
/*******************************************************************************
* 函数名			:	GetUplinkData
* 功能描述		:	获取需要往上层发送的数据
							1-先检查应答缓存有无数据
							2-应答缓存RS485ACKU无数据则检查TransU缓存
							3-TransU无数据则扫描DataNodeU
							4-如果DataNodeU有待传消息，将数据复制到TransU和buffer
* 输入			: buffer  接收数据的缓存
* 返回值			: FrameLength 需要发送的总字节数
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
unsigned short APIRS485UplinkGetAck(unsigned char *buffer)
{
	unsigned char FrameLength	= 0;		//消息帧总长度，从HeadCode到EndCode的字节数
//	unsigned char	i	=	0;
	//=====================================接收缓存异常情况：空地址
	if(NULL	==	buffer)
	{
		return 0;
	}
	//=====================================检查RS485ACKU缓存
	FrameLength	=	ACKU.FarmeLength;
	if(0	!=	FrameLength)
	{
		memcpy(buffer,&ACKU.Ack,FrameLength);
		ACKU.FarmeLength	=	0;
		return FrameLength;
	}
	return FrameLength;
}
/*******************************************************************************
* 函数名			:	APIGetdownlinkData
* 功能描述		:	获取需要往下层发送的数据
							1-先检查应答缓存有无数据
							2-应答缓存RS485ACKD无数据则检查TransD缓存
							3-TransD无数据则扫描DataNoded
							4-如果DataNodeD有待传消息，将数据复制到TransD和buffer
* 输入			: buffer  接收数据的缓存
* 返回值			: FrameLength 需要发送的总字节数
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
unsigned short APIRS485DownlinkGetAck(unsigned char *buffer)
{
	unsigned char FrameLength	= 0;		//消息帧总长度，从HeadCode到EndCode的字节数
	//=====================================接收缓存异常情况：空地址
	if(NULL	==	buffer)
	{
		return 0;
	}
	//=====================================检查RS485ACKU缓存
	FrameLength	=	ACKD.FarmeLength;
	if(0	!=	FrameLength)
	{
		memcpy(buffer,&ACKD.Ack,FrameLength);
		ACKD.FarmeLength	=	0;
		return FrameLength;
	}	
	return FrameLength;
}
/*******************************************************************************
* 函数名			:	GetUplinkData
* 功能描述		:	获取需要往上层发送的数据
							1-先检查应答缓存有无数据
							2-应答缓存RS485ACKU无数据则检查TransU缓存
							3-TransU无数据则扫描DataNodeU
							4-如果DataNodeU有待传消息，将数据复制到TransU和buffer
* 输入			: buffer  接收数据的缓存
* 返回值			: FrameLength 需要发送的总字节数
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
unsigned short APIRS485UplinkGetData(unsigned char *buffer)
{
	unsigned char FrameLength	= 0;		//消息帧总长度，从HeadCode到EndCode的字节数
	unsigned char	i	=	0;
	//=====================================接收缓存异常情况：空地址
	if(NULL	==	buffer)
	{
		return 0;
	}
	//=====================================检查RS485ACKU缓存
	FrameLength	=	ACKU.FarmeLength;
	if(0	!=	FrameLength)
	{
		memcpy(buffer,&ACKU.Ack,FrameLength);
		ACKU.FarmeLength	=	0;
		return FrameLength;
	}
	//=====================================检查TransU缓存
	FrameLength	=	TransU.Length;
	if(0	!=	FrameLength)
	{
		memcpy(buffer,TransU.data,FrameLength);
		if(++TransU.Retry.Retry>=ReSendCount)		//达到重发次数:释放缓存，放弃重发
		{
			TransU.Length	=	0;
			TransU.Retry.Retry	=	0;
			TransU.Length				=	0;
		}
		return FrameLength;
	}
  //=====================================检查SendNode缓存
  for(i=0;i<SelfBuffSize;i++)
  {
    FrameLength	=	SendNode[i].NodeLength;
		if(0	!=	FrameLength)		//有数据
		{
			memcpy(TransU.data,SendNode[i].data,FrameLength);
			memcpy(buffer,SendNode[i].data,FrameLength);
			TransU.Length	=	FrameLength;
			TransU.Retry.Retry	=	0;
			TransU.Retry.Time		=	0;			
			SendNode[i].NodeLength	=	0;
			return FrameLength;
		}
  }
	//=====================================检查DataNodeU缓存
	for(i	=	0;i<=MaxNetPerLayer;i++)
	{
		FrameLength	=	DataNodeU[i].NodeLength;
		if(0	!=	FrameLength)		//有数据
		{
			memcpy(TransU.data,DataNodeU[i].data,FrameLength);
			memcpy(buffer,DataNodeU[i].data,FrameLength);
			TransU.Length	=	FrameLength;
			TransU.Retry.Retry	=	0;
			TransU.Retry.Time		=	0;			
			DataNodeU[i].NodeLength	=	0;
			return FrameLength;
		}
	}
	return FrameLength;
}
/*******************************************************************************
* 函数名			:	APIGetdownlinkData
* 功能描述		:	获取需要往下层发送的数据
							1-先检查应答缓存有无数据
							2-应答缓存RS485ACKD无数据则检查TransD缓存
							3-TransD无数据则扫描DataNoded
							4-如果DataNodeD有待传消息，将数据复制到TransD和buffer
* 输入			: buffer  接收数据的缓存
* 返回值			: FrameLength 需要发送的总字节数
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
unsigned short APIRS485DownlinkGetData(unsigned char *buffer)
{
	RS485FrameDef*	RS485Frame			=	NULL;
	
	unsigned char	FrameLength	= 0;		//消息帧总长度，从HeadCode到EndCode的字节数
	unsigned char	i	=	0;
	
	
	//=====================================接收缓存异常情况：空地址
	if(NULL	==	buffer)
	{
		return 0;
	}
	//=====================================检查RS485ACKD缓存
	FrameLength	=	ACKD.FarmeLength;
	if(0	!=	FrameLength)
	{
		memcpy(buffer,&ACKD.Ack,FrameLength);
		ACKD.FarmeLength	=	0;
		return FrameLength;
	}
	//=====================================检查TransD缓存
	FrameLength	=	TransD.Length;
	if(0	!=	FrameLength)
	{
		
		memcpy(buffer,TransD.data,FrameLength);
    TransD.Retry.Retry+=1;
		if((TransD.Retry.Retry)>=ReSendCount)		//达到重发次数:释放缓存，放弃重发
		{
			TransD.Length	=	0;
			TransD.Retry.Retry	=	0;
			TransD.Length				=	0;
		}
		return FrameLength;
	}
	//=====================================检查DataNodeD缓存
	for(i	=	0;i<=MaxNetPerLayer;i++)
	{
		FrameLength	=	DataNodeD[i].NodeLength;
		if(0	!=	FrameLength)		//有数据
		{
			unsigned char* DataAddr	=	NULL;
			
			unsigned char		Bcc8	=	0;
			unsigned short	Len	=	0;
			DataAddr		=	DataNodeD[i].data;
			
			RS485Frame	=	(RS485FrameDef*)DataNodeD[i].data;
			RS485Frame->HStart.Serial	=	SerialD++;
			
			Len		=	FrameLength-3;	//3为头尾标识和校验位长度
			DataAddr[FrameLength-2]	=	bspGetBcc8(&DataAddr[1],Len);
			
			memcpy(TransD.data,DataNodeD[i].data,FrameLength);
			memcpy(buffer,DataNodeD[i].data,FrameLength);
			TransD.Length	=	FrameLength;
			TransD.Retry.Retry	=	0;
			TransD.Retry.Time		=	0;			
			DataNodeD[i].NodeLength	=	0;
			return FrameLength;
		}
	}
	return FrameLength;
}

/*******************************************************************************
* 函数名			:	APIRS232UplinkSetData
* 功能描述		:	以下函数调用严格按照顺序执行 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
HCResult APIRS232UplinkSetData(const unsigned char *buffer,const unsigned short length)
{
	HCResult	Result	=	RES_OK;
	
	RS232FrameDef*			RS232Frame			=	NULL;
	RS232FrameStartDef*	RS232FrameStart	=	NULL;
//	RS232DataStartDef*	RS232DataStart	=	NULL;
	
	unsigned char*	pBuffer		=	NULL;	
	unsigned char*	Head1Addr	=	0;
	unsigned char*	Head2Addr	=	0;	
	
	unsigned short	ValidLength	=	0;
	unsigned char		DataLength	=	0;	
	
	pBuffer	=	(unsigned char*)buffer;	
	ValidLength	=	length;
	//=============================================输入规范
	if((NULL	==	buffer)||(0		==	length))
	{
		return	RES_Err;		//输入为空地址或者空长度
	}
	//=============================================帧格式检查
	Start:			//开始执行
	//---------------------------------------------查找头文件
	pBuffer	=	bspRS232GetFrmeAddr(pBuffer,&ValidLength);						//获取RS232帧头地址
	if(NULL	==	pBuffer)	//错误帧
	{
		return RES_Err;			
	}
	//---------------------------------------------BCC校验
	Result	=	bspRS232Bcc8Check(pBuffer,ValidLength);								//校验
	if(RES_OK	!=	Result)	//校验错误
	{
		pBuffer	=	&pBuffer[1];
		ValidLength	=	ValidLength-1;
		goto Start;		//重新检查剩余数据		
	}	
	Result	=	bspRS232AckFrameCheck(pBuffer,ValidLength);						//检查是否为应答
	if(RES_OK	==	Result)
	{
		bspRS232ReleaseTxBuffer();
		
		pBuffer	=	&pBuffer[1];
		ValidLength	=	ValidLength-1;
		goto Start;		//重新检查剩余数据
	}
	//---------------------------------------------数据类型检查
	Result	=	bspRS232DataCheck(pBuffer,ValidLength);
	if(RES_OK	!=	Result)
	{
		return RES_Err;			//校验错误
	}
	return RES_OK;			//错误帧
}
/*******************************************************************************
* 函数名			:	APIRS232UplinkSetData
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
unsigned char* bspRS232GetFrmeAddr(const unsigned char*	buffer,unsigned short* length)
{
	RS232FrameStartDef*	RS232FrameStart	=	NULL;
	
	unsigned char*	pBuffer	=	NULL;	
	unsigned char*	Head1Addr	=	0;
	unsigned char*	Head2Addr	=	0;
	
	
	unsigned short	ValidLength	=	0;
	unsigned char		DataLength	=	0;
	
	
	pBuffer	=	(unsigned char*)buffer;	
	
	//=============================================输入规范
	if((NULL	==	buffer)||(0		==	length))
	{
		return	NULL;		//输入为空地址或者空长度
	}
	
	//=============================================头标识校验
	ValidLength	=	*length;
	
	Start:			//=====================
	Head1Addr		=	(unsigned char*)memchr(pBuffer,RS232Head1,ValidLength);
	if(NULL	==	Head1Addr)
	{
		return	NULL;		//未找到0xFA
	}	
	ValidLength	=	ValidLength-((unsigned long)Head1Addr-(unsigned long)pBuffer);
	pBuffer			=	Head1Addr;
	Head2Addr		=	(unsigned char*)memchr(pBuffer,RS232Head2,ValidLength);	
	if(NULL	==	Head2Addr)
	{
		return	NULL;		//未找到0xF5
	}
	//---------------------------------------------检查0xFA,0xF5是否连续
	if(1!=((unsigned long)Head2Addr-(unsigned long)Head1Addr))
	{
		ValidLength	=	ValidLength-((unsigned long)Head2Addr-(unsigned long)pBuffer);
		pBuffer	=	Head2Addr;
		
		goto Start;					//不连续，从新地址开始重新检测
	}
	//=============================================协议
	//---------------------------------------------帧长度
	if(sizeof(RS232FrameStartDef)>ValidLength)
	{
		return	NULL;		//剩余长度不够最短帧要求
	}
	
	RS232FrameStart	=	(RS232FrameStartDef*)pBuffer;
	
	DataLength	=	RS232FrameStart->DataLength;
	if(sizeof(RS232FrameStartDef)+DataLength>ValidLength)
	{
		return	NULL;		//剩余长度与数据不符
	}
	
	*length	=	ValidLength;
	return pBuffer;
}
/*******************************************************************************
* 函数名			:	APIRS232UplinkSetData
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
HCResult bspRS232Bcc8Check(const unsigned char*	buffer,unsigned short length)
{
	RS232FrameDef*			RS232Frame			=	NULL;
	RS232FrameStartDef*	RS232FrameStart	=	NULL;
//	RS232DataStartDef*	RS232DataStart	=	NULL;
	
	unsigned char*	pBuffer	=	NULL;	
	
	unsigned char		Bcc8				=	0;
	unsigned char		DataLength	=	0;	
	
	//=============================================输入规范
	if((NULL	==	buffer)||(0		==	length))
	{
		return	RES_Err;		//输入为空地址或者空长度
	}
	
	//=============================================获取相关数据
	RS232Frame	=	(RS232FrameDef*)buffer;
	DataLength	=	RS232Frame->HStart.DataLength;
	Bcc8				=	RS232Frame->HStart.Bcc8;
	//---------------------------------------------数据长度为0
	if(0	==	DataLength)
	{
		if(0	==	Bcc8)
			return RES_OK;
		else
			return RES_Err;	//校验错误
	}	
	//---------------------------------------------计算Bcc8
	pBuffer	=	(unsigned char*)&(RS232Frame->DStart.Addr.CabinetAddr);
	Bcc8		=	bspGetBcc8(pBuffer,DataLength);
	if(Bcc8	!=	RS232Frame->HStart.Bcc8)
	{
		return RES_Err;	//校验错误
	}
	return RES_OK;
}
/*******************************************************************************
* 函数名			:	bspRS232AckFrameCheck
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
HCResult bspRS232AckFrameCheck(const unsigned char*	buffer,unsigned short length)
{
	RS232FrameDef*			RS232Frame			=	NULL;

	unsigned char		DataLength	=	0;
	
	//=============================================输入规范
	if((NULL	==	buffer)||(0		==	length))
	{
		return	RES_Err;		//输入为空地址或者空长度
	}	
	//=============================================获取相关数据
	RS232Frame	=	(RS232FrameDef*)buffer;
	DataLength	=	RS232Frame->HStart.DataLength;
	//---------------------------------------------数据长度为0
	if(0	!=	DataLength)
	{
		return RES_Err;		//数据长度不为0表示非应答帧
	}	
	return RES_OK;
}

/*******************************************************************************
* 函数名			:	bspRS232DataCheck
* 功能描述		:	检查数据是否为针对本层还是需要转发到下一层：
							本层数据：下一级地址为0,否则是需要转发到下一层的数据
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
HCResult bspRS232DataCheck(const unsigned char*	buffer,unsigned short length)
{
	HCResult	Result	=	RES_OK;
	
	RS232FrameDef*			RS232Frame			=	NULL;
	RS232FrameStartDef*	RS232FrameStart	=	NULL;
//	RS232DataStartDef*	RS232DataStart	=	NULL;
	
	unsigned char*	pBuffer	=	NULL;
	
	unsigned char		Bcc8				=	0;
	unsigned char		DataLength	=	0;
	unsigned char 	TargetAddr	=	0;		//目标地址
	unsigned char 	i						=	0;
	unsigned short 	NodeLength	=	0;
	
	//=============================================输入规范
	if((NULL	==	buffer)||(0		==	length))
	{
		return	RES_Err;		//输入为空地址或者空长度
	}
	//=============================================获取相关数据
	pBuffer	=	(unsigned char*)buffer;
	RS232Frame			=	(RS232FrameDef*)buffer;
	
	DataLength	=	RS232Frame->HStart.DataLength;
	//---------------------------------------------数据长度为0
	if(0	==	DataLength)
	{
		return RES_Err;		//数据长度错误
	}	
	//---------------------------------------------
//	RS232DataStart	=	(RS232DataStartDef*)&RS232Frame->DStart;
	TargetAddr	=	RS232Frame->DStart.Addr.CabinetAddr;
	//---------------------------------------------本级数据
	if(0	==	TargetAddr)	//本级数据:保存到ProcessNode缓存
	{		
		NodeLength	=	DataLength+sizeof(RS232FrameStartDef);
		for(i=0;i<SelfBuffSize;i++)
		{
			if(0	==	ProcessNode[i].NodeLength)
			{
				ProcessNode[i].NodeLength	=	NodeLength;
				memcpy(ProcessNode[i].data,pBuffer,NodeLength);
				break;
			}
		}
		if(i<SelfBuffSize)
			return RES_OK;
		else
			return RES_NotReady;		
	}
	//---------------------------------------------需要转发的数据
	else
	{
		Result	=	bspRS232ToRS485(pBuffer,length);
		bspSetAck(pBuffer,length);
		return	Result;
	}
	return RES_OK;
}
/*******************************************************************************
* 函数名			:	APIRS232UplinkSetData
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
HCResult bspRS232ToRS485(const unsigned char*	buffer,unsigned short length)
{
	RS232FrameDef*			RS232Frame			=	NULL;
	RS232FrameStartDef*	RS232FrameStart	=	NULL;
//	RS232DataStartDef*	RS232DataStart	=	NULL;
	
	RS485FrameDef*			RS485Frame			=	NULL;
	
	unsigned char*	pBuffer			=	NULL;	
	unsigned char*	pRS232Data	=	NULL;
	unsigned char*	pRS485Data	=	NULL;
	
	unsigned short	Bcc8				=	0;
	unsigned char		DataLength	=	0;
	unsigned char 	TargetAddr	=	0;		//目标地址
	unsigned char 	i						=	0;
	unsigned short 	NodeLength	=	0;	
	
	pBuffer	=	(unsigned char*)buffer;	
	
	//=============================================输入规范
	if((NULL	==	buffer)||(0		==	length))
	{
		return	RES_Err;		//输入为空地址或者空长度
	}
	RS232Frame	=	(RS232FrameDef*)pBuffer;
	TargetAddr	=	RS232Frame->DStart.Addr.CabinetAddr;
	if(0	!=	DataNodeD[TargetAddr].NodeLength)
	{
		return RES_NotReady;
	}
	
	RS485Frame	=	(RS485FrameDef*)DataNodeD[TargetAddr].data;
	
	RS485Frame->HStart.HeadCode		=	RS485HeadCode;
	RS485Frame->HStart.TargetAddr	=	TargetAddr;
	RS485Frame->HStart.SourceAddr	=	0x00;
	
	RS485Frame->HStart.Cmd				=	RS232Frame->HStart.Cmd;
	RS485Frame->HStart.UserCode		=	RS232Frame->HStart.UserCode;
	
	RS485Frame->DStart.Addr.CabinetAddr	=	RS232Frame->DStart.Addr.CabinetAddr;
	RS485Frame->DStart.Addr.LayerAddr		=	RS232Frame->DStart.Addr.LayerAddr;
	RS485Frame->DStart.Addr.SlotAddr		=	RS232Frame->DStart.Addr.SlotAddr;
	RS485Frame->DStart.ErrCode					=	RS232Frame->DStart.ErrCode;
	
	RS485Frame->HStart.DataLength				=	RS232Frame->HStart.DataLength;
	
	pRS232Data	=	(unsigned char*)&RS232Frame->DStart.ErrCode;
	pRS232Data	=	&pRS232Data[1];
	
	pRS485Data	=	(unsigned char*)&RS485Frame->DStart.ErrCode;
	pRS485Data	=	&pRS485Data[1];
	
	RS485Frame->Data	=	pRS485Data;
	
	DataLength	=	RS485Frame->HStart.DataLength	-sizeof(AddrDef)-sizeof(ErrCodeDef);		//数据长度：不包换地址和错误码
	
	memcpy(pRS485Data,pRS232Data,DataLength);
	
//	Bcc8	=	bspGetBcc8(&RS485Frame->DStart.Addr.CabinetAddr,RS485Frame->DStart.DataLength);		//从地址开始校验
//	
//	pRS485Data	=	&pRS485Data[DataLength];		//Bcc8地址
//	*pRS485Data	=	Bcc8;
	
	pRS485Data	=	&pRS485Data[DataLength+1];		//结束符地址
	*pRS485Data	=	RS485EndCode;
	
	DataNodeD[TargetAddr].NodeLength	=	sizeof(RS485FrameStartDef)+sizeof(FrameDataStartDef)+DataLength+2;		//2为Bcc8和结束符长度
	
	return RES_OK;
}

/*******************************************************************************
* 函数名			:	bspRS232ReleaseTxData
* 功能描述		:	释放上传缓存：上传成功或者超时后调用 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
HCResult bspRS232ReleaseTxBuffer(void)
{
	TransU.Length	=	0;
	return RES_OK;
}





























/*******************************************************************************
* 函数名			:	RS485SetAckFrame
* 功能描述		:	建立应答包 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
unsigned char* RS485FrameGetHead(const unsigned char *buffer,const unsigned short length)
{
	unsigned char* FrameHead	=	NULL;
	return FrameHead;
}
/*******************************************************************************
* 函数名			:	RS485FrameCheck
* 功能描述		:	协议检查
* 输入			: buffer地址和length长度
* 返回值			: RES_OK 	数据正确
							RES_Err	数据错误
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
HCResult RS485FrameCheck(const unsigned char *buffer,const unsigned short length)
{
	unsigned char	*HeadAddr			=	0;	//头标识符地址
	unsigned char	*pBuffer			=	0;	//数据处理buffer
	
	unsigned short 	ValidLength	= 0;	//buffer中有效数据长度(从RS485头标识符开始后的数据为有效数据)
	
	//=================================================================================导入数据:输入为const类型
	pBuffer			=	(unsigned char*)buffer;
	ValidLength	=	(unsigned short)length;
	//=================================================================================检查输入数据，防止内存错误
	if(
			(NULL	==pBuffer)				//指针地址为空
		||(0		==ValidLength)		//数据长度为0
		)
	{
		return RES_Err;
	}
	//=================================================================================查找头标识地址:返回空表示为未找到
	HeadAddr	=	(unsigned char*)memchr(pBuffer,RS485HeadCode,ValidLength);			//查找RS485HeadCode头标识符
	if(NULL==HeadAddr)
	{
		return RES_Err;
	}
	//=================================================================================更新有效数据长度并判断剩余数据长度是否符合最短帧长度
	ValidLength	=	ValidLength-(unsigned short)(pBuffer	-	HeadAddr);
	pBuffer			=	HeadAddr;
	if(RS485MinFrameLen>ValidLength)
	{
		return RES_Err;
	}
	//=================================================================================
}
/*******************************************************************************
* 函数名			:	function
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
HCResult RS485FrameAckCheck(const unsigned char *HeadAddr,const unsigned short length)
{
	RS485AckDef			*AckFrame		=	NULL;		//应答类型指针	
	unsigned char		*EndAddr		= NULL;		//结束符地址
	unsigned char		*pBuffer			=	0;		//数据处理buffer
	
	unsigned char		Bcc8				=	0;
	
	AckFrame	=	(RS485AckDef*)HeadAddr;
	//=================================================================================帧尾判断
	if(RS485EndCode	!=	AckFrame->EndCode)
	{
		return RES_Err;
	}
	
	//=================================================================================校验判断
	Bcc8	=	bspGetBcc8(HeadAddr,RS485AckFrameLen);
	if(Bcc8	!=	AckFrame->Bcc8)
	{
		return RES_Err;
	}	
	return RES_OK;
}

/*******************************************************************************
* 函数名			:	function
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
unsigned short RS485FrameGetLength(const unsigned char *HeadAddr,const unsigned short length)
{
	unsigned long	*EndAddr	= NULL;		//结束符地址
	return RES_Err;
}
/*******************************************************************************
* 函数名			:	RS485SetAckFrame
* 功能描述		:	建立应答包 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
unsigned char* RS485SetAckFrame(const unsigned char *buffer,const unsigned short length)
{
	unsigned char* FrameHead	=	NULL;
	return FrameHead;
}





































//------------------------------------------------------------------------------------------------------------------------------公共子函数





/*******************************************************************************
* 函数名			:	function
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
unsigned char bspGetBcc8(const unsigned char *HeadAddr,const unsigned short length)
{
	unsigned char		*pBuffer		=	0;			//数据处理buffer
	
	unsigned char		Bcc8				=	0;
	unsigned short	ValidLength	= 0;			//buffer中有效数据长度(从RS485头标识符开始后的数据为有效数据)
	unsigned short	i	=	0;
	//=================================================================================导入数据:输入为const类型
	pBuffer			=	(unsigned char*)HeadAddr;
	ValidLength	=	(unsigned short)length;			//减去头尾和校验位长度
	
	if(1	>=	ValidLength)
	{
		return 0;
	}
		
	//=================================================================================校验判断
	for(i=0;i<ValidLength;i++)
	{
		Bcc8=Bcc8^pBuffer[i];
	}	
	return Bcc8;
}
/*******************************************************************************
* 函数名			:	bspSetAck
* 功能描述		:	设置应答数据
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
HCResult bspSetAck(const unsigned char*	buffer,unsigned short length)
{
	RS232FrameDef*			RS232Frame			=	NULL;
	RS485FrameDef*			RS485Frame			=	NULL;
	
	unsigned char*	pBuffer			=	NULL;	
//	unsigned char*	pRS232Data	=	NULL;
//	unsigned char*	pRS485Data	=	NULL;
	
//	unsigned short	Bcc8				=	0;
//	unsigned char		DataLength	=	0;
//	unsigned char 	TargetAddr	=	0;		//目标地址
//	unsigned char 	i						=	0;
//	unsigned short 	NodeLength	=	0;	
	
	pBuffer	=	(unsigned char*)buffer;	
	
	//=============================================输入规范
	if((NULL	==	buffer)||(0		==	length))
	{
		return	RES_Err;		//输入为空地址或者空长度
	}
	//=============================================RS232
	RS232Frame	=	(RS232FrameDef*)pBuffer;
	RS485Frame	=	(RS485FrameDef*)pBuffer;
	if((RS232Head1==RS232Frame->HStart.Head1)&&(RS232Head2==RS232Frame->HStart.Head2))
	{
//		RS232FrameDef*	RS232Frame	=	NULL;
//		RS485FrameDef*	RS485Frame	=	NULL;

		RS232Frame	=	(RS232FrameDef*)TransU.data;
		
		memcpy(TransU.data,pBuffer,sizeof(RS232FrameStartDef));
		
		RS232Frame->HStart.Bcc8				=	0;
		RS232Frame->HStart.DataLength	=	0;
		TransU.Retry.Retry	=	0;
		TransU.Retry.Time		=	0;
		TransU.Length				=	sizeof(RS232FrameStartDef);
	}
	//=============================================RS485
	else if(
					(RS485HeadCode	==	RS485Frame->HStart.HeadCode)
				&&(0							!=	RS485Frame->HStart.DataLength)
				)
	{
		//---------------------------------------------下级往上传数据(目标地址为0，源地址为下级地址)：应答为向下应答
		if(
				(0==RS485Frame->HStart.TargetAddr)
			&&(0!=RS485Frame->HStart.SourceAddr)
		)
		{
		}
		else if(
			(0!=RS485Frame->HStart.TargetAddr)
		&&(0==RS485Frame->HStart.SourceAddr)
		)
		{
		}
	}

	return RES_OK;
}








































///*******************************************************************************
//* 函数名			:	APIRS232UplinkSetData
//* 功能描述		:	函数功能说明 
//* 输入			: void
//* 返回值			: void
//* 修改时间		: 无
//* 修改内容		: 无
//* 其它			: wegam@sina.com
//*******************************************************************************/
//HCResult APIRS232UplinkSetData(const unsigned char *buffer,const unsigned short length)
//{
//	
////	CmdDef		CmdTemp;
//	
//	RS232FrameDef *RS232Frame 	= NULL;
//	RS485FrameDef *RS485Frame 	= NULL;
//	unsigned char	*pBuffer			=	0;
//	unsigned char	*Head1Addr		=	0;
//	unsigned char	*Head2Addr		=	0;
//	
//	unsigned char		UserCode  	=	0;
//	unsigned char		SourceBcc8  =	0;
//	unsigned char		TargetAddr	=	0;
//  unsigned short	FarmeLen		=	0;
//	unsigned short	DataLength	=	0;
//	unsigned short 	ValidLength	= 0;    //buffer中有效数据长度(从RS485头标识符开始后的数据为有效数据)
//	
//  if(NULL ==  buffer) //空地址
//	{
//		return RES_PARERR;
//	}
//  //=========================================查找RS485HeadCode头标识符
//	pBuffer			=	(unsigned char*)buffer;
//	ValidLength	=	length;
//	//-----------------------------------------查找头标识(0xFA 0xF5)
//	CheckFarm:
//	Head1Addr		=	(unsigned char*)memchr(pBuffer,RS232Head1,ValidLength);							//查找RS485HeadCode头标识符
//	Head2Addr 	=	(unsigned char*)memchr(pBuffer,RS232Head2,ValidLength);							//查找RS485HeadCode头标识符
//	
//	if((NULL==Head1Addr)||(NULL==Head2Addr))		//标识未找到或者不完整
//	{
//		return RES_PARERR;
//	}
//	if(Head2Addr	!=Head1Addr+1)		//0xFA,0xF5不相邻（0xFA在前,0xF5在后)
//	{
//		pBuffer	=	&pBuffer[1];				//地址加1，返回继续检查
//		goto CheckFarm;
//	}
//	RS232Frame	=	(RS232FrameDef*)Head1Addr;		//头地址
//	ValidLength	=	ValidLength-((unsigned long)RS232Frame-(unsigned long)pBuffer);		//剩余数据长度
//	SourceBcc8	=	RS232Frame->Bcc8;
//	DataLength	=	RS232Frame->DataLength;
//	UserCode		=	RS232Frame->UserCode;
//	//=========================================应答帧判断(数据长度为0，校验码为0):如果为应答消息，则把发送缓存标志清除
//	if(0	==	DataLength)			//应答类型
//	{
//		//---------------------------------------校验判断
//		if(0!=SourceBcc8)
//		{
//			pBuffer	=	&pBuffer[1];	//地址加1，返回继续检查
//			goto CheckFarm;					//校验不对
//		}
//		//---------------------------------------应答帧:释放上传缓存
//		else
//		{
//			TransU.Length	=	0;			//清除发送缓存
//			pBuffer	=	&pBuffer[1];	//地址加1，返回继续检查剩余数据
//			goto CheckFarm;
//		}
//	}
//	//=========================================数据帧
//	else			//网关板下一级为单元板
//	{	
//		AddrDef		AddrTemp;						//地址
//		unsigned char *pTemp		=0;
//		unsigned char Bcc8Temp	=0;
//		unsigned char i					=0;		
//		//----------------------------------------获取地址数据
//		pTemp	=	&RS232Frame->DataLength;
//		pTemp	=	&pTemp[1];
//		memcpy(&AddrTemp,pTemp,3);		//拷贝地址	
//		//----------------------------------------数据校验
//		Bcc8Temp	=	BCC8(pTemp,DataLength);
//		if(SourceBcc8	!=	Bcc8Temp)
//		{
//			pBuffer	=	&pBuffer[1];			//地址加1，返回继续检查
//			goto CheckFarm;
//		}
//		//========================================数据处理
//		//----------------------------------------判断是本层数据还是需要转发的数据(柜地址为0表示此为网关板数据)
//		TargetAddr	=	AddrTemp.CabinetAddr;
//		//-----------------------------------------本地消息：单元板地址为0
//		if(0==AddrTemp.CabinetAddr)		//单元柜地址为0
//		{
//			//--------------------------------------查找空缓存存储数据待处理
//			for(i=0;i<SelfBuffSize;i++)
//			{
//				if(0	==	ProcessNode[i].NodeLength)
//				{
//					DataTypeDef	*DataType	=	(DataTypeDef*)ProcessNode;
//					//------------------头两字节为命令号和用户码
//					DataType->Cmd				=	RS232Frame->Cmd;
//					DataType->UserCode	=	RS232Frame->UserCode;
//					
//					memcpy(&ProcessNode[i].data[2],pTemp,DataLength);
//					ProcessNode[i].NodeLength	=	DataLength+2;
//				}
//			}
//			//--------------------------------------创建应答
//			if(i<SelfBuffSize)		//存储成功
//			{
//				ACKU.Ack.ErrCode		=	Err_None;
//			}
//			else									//无空缓存，设备忙状态
//			{
//				ACKU.Ack.ErrCode		=	Err_FAULT_BUSY;
//			}
//		}
//		//(DataLength<BusDataSize))		//数据长度小于最大缓存空间
//		//-----------------------------------------转换为RS485协议包
//		else
//		{
//			unsigned char	*pT	=	NULL;
//			for(i=0;i<MaxNetPerLayer;i++)
//			{
//				if(0	==	DataNodeD[i].NodeLength)
//				{
//					RS485Frame	=	(RS485FrameDef*)&DataNodeD[i].data[0];
//					
//					RS485Frame->HeadCode		=	RS485HeadCode;
//					RS485Frame->TargetAddr	=	RS232Frame->CabinetAddr;
//					RS485Frame->SourceAddr	=	0x00;
//					RS485Frame->ErrCode			=	RS232Frame->ErrCode;
//					RS485Frame->CabinetAddr	=	RS232Frame->CabinetAddr;
//					RS485Frame->LayerAddr		=	RS232Frame->LayerAddr;
//					RS485Frame->SlotAddr		=	RS232Frame->SlotAddr;
//					RS485Frame->DataLength	=	RS232Frame->DataLength-4+3;
//					//---------------获取数据地址
//					pTemp	=	(unsigned char*)&RS232Frame->ErrCode;
//					pTemp++;
//					
//					pT	=	&DataNodeD[i].data[RS485StartFrameLen];
//					pT[0]	=	RS232Frame->Cmd;
//					pT[1]	=	RS232Frame->UserCode;
//					pT[2]	=	RS232Frame->Serial;
//					
//					memcpy(&pT[3],pTemp,RS485Frame->DataLength-3);
//					
//					pTemp	=	(unsigned char*)&RS485Frame->data[RS485Frame->DataLength+3];
//					
//					pT[RS485Frame->DataLength]		=	BCC8(&RS485Frame->TargetAddr,RS485StartFrameLen+RS485Frame->DataLength-1);
//					pT[RS485Frame->DataLength+1]	=	RS485EndCode;
//					DataNodeD[i].NodeLength	=	RS485StartFrameLen+RS485Frame->DataLength+3;
//					break;
//				}
//			}
//			if(i<MaxNetPerLayer)
//			{
//				ACKU.Ack.ErrCode		=	Err_None;
//			}
//			else
//			{
//				ACKU.Ack.ErrCode		=	Err_FAULT_BUSY;
//			}
//		}
//	}
//	return RES_OK;
//}











































