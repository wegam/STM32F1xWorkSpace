


#include "STM32_SYSTICK.H"


#include	"HC_PHY.H"
#include	"TOOL.H"		//数据校验工具
#include	"CRC.H"		//

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
//DataNodeDef SendNode[SelfBuffSize];       //本地址需要上传的(不需要转发给下一层的消息)


RS485FrameDef RunFrame;

HCSYSDef	HCSYS;


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
* 函数名			:	function
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
void PHY_Initialize(void)
{

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
void PHY_Server(void)
{

}
/*******************************************************************************
* 函数名			:	APIUplinkReceiveDataProcess
* 功能描述		:	上级接口下发数据处理 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
HCResult APIUplinkReceiveDataProcess(const unsigned char *buffer,const unsigned short length)
{
	HCResult	Result	=	RES_OK;
	
	Result	=	bspRS232UplinkReceiveDataProcess(buffer,length);
	if(RES_OK	==	Result)
	{
		return	Result;
	}
	
	
	Result	=	bspRS485UplinkReceiveDataProcess(buffer,length);
	if(RES_OK	==	Result)
	{
		return	Result;
	}	
	return Result;			//错误帧
}
/*******************************************************************************
* 函数名			:	APIUplinkSetData
* 功能描述		:	上级接口下发数据处理 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
unsigned short APIUplinkGetData(unsigned char *buffer)
{
	unsigned	short length	=	0;
	//=====================================接收缓存异常情况：空地址
	if(NULL	==	buffer)
	{
		return 0;
	}
	//=====================================检查RS485ACKU缓存
	length	=	bspUplinkGetAck(buffer);
	if(0	!=	length)
	{
//		Com_DelaymS(5);
		return length;
	}
	length	=	bspRS485UplinkGetData(buffer);
	if(0!=length)
	{
		Com_DelaymS(5);
		return length;
	}
	
	return length;			//错误帧
}



/*******************************************************************************
* 函数名			:	APIDownlinkReceiveDataProcess
* 功能描述		:	下端接口
* 输入			: buffer  输入的数据缓存地址
              length  输入的数据长度
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
HCResult APIDownlinkReceiveDataProcess(const unsigned char *buffer,const unsigned short length)
{
	HCResult	Result	=	RES_OK;
	
	Result	=	bspRS232UplinkReceiveDataProcess(buffer,length);
	if(RES_OK	==	Result)
	{
		return	Result;
	}
	Result	=	bspRS485DownLinkReceiveDataProcess(buffer,length);
	if(RES_OK	==	Result)
	{
		return	Result;
	}	
	return Result;			//错误帧
}
/*******************************************************************************
* 函数名			:	APIGetdownlinkData
* 功能描述		:	获取需要往下层发送的数据--如果有数据，则根据最新流水号计算BCC
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
unsigned short APIDownlinkGetData(unsigned char *buffer)
{
	unsigned	short length	=	0;
	//=====================================接收缓存异常情况：空地址
	if(NULL	==	buffer)
	{
		return 0;
	}
	//=====================================检查RS485ACKD缓存
	length	=	bspDownLinkGetAck(buffer);
	if(0	!=	length)
	{
//		Com_DelaymS(5);
		return length;
	}	
	length=	bspRS485DownlinkGetData(buffer);
	if(0	!=	length)
	{
//		Com_DelaymS(5);
		return length;
	}
	
	return	length;
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
* 函数名			:	bspRS485UplinkReceiveDataProcess
* 功能描述		:	上端口接收数据处理 
* 输入			: buffer
							length
							接收限制：目的地址不为0，源地址必须为0
							
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
HCResult bspRS485UplinkReceiveDataProcess(const unsigned char *buffer,const unsigned short length)
{
	HCResult	Result	=	RES_OK;
	
	RS485FrameDef*			RS485Frame			=	NULL;
	RS485FrameStartDef*	RS485FrameStart	=	NULL;
	FrameDataStartDef*	FrameDataStart	=	NULL;
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
	pBuffer	=	bspRS485GetFrmeAddr(pBuffer,&ValidLength);						//获取RS485帧头地址
	if(NULL	==	pBuffer)	//错误帧
	{
		return RES_Err;			
	}
	//==============================================地址校验：上端下发--目的地址不为0，源地址必须为0
	RS485FrameStart	=	(RS485FrameStartDef*)pBuffer;
	if((HCSYS.SwitchAddr!=RS485FrameStart->TargetAddr)		//目的地址为接收地址
		||(0!=RS485FrameStart->SourceAddr))								//源地址必须为0
	{
		pBuffer	=	&pBuffer[1];
		ValidLength	=	ValidLength-1;
		goto Start;		//重新检查剩余数据
	}
	Result	=	bspRS485AckFrameCheck(pBuffer,ValidLength);						//检查是否为应答
	if(RES_OK	==	Result)	//校验错误
	{
		bspRS485UplinkReleaseTxBuffer();
		pBuffer	=	&pBuffer[1];
		ValidLength	=	ValidLength-1;
		goto Start;		//重新检查剩余数据
	}
	//---------------------------------------------校验
	Result	=	bspRS485Verify(pBuffer,ValidLength);								//校验
	if(RES_OK	!=	Result)	//校验错误
	{
		pBuffer	=	&pBuffer[1];
		ValidLength	=	ValidLength-1;
		goto Start;		//重新检查剩余数据		
	}	
	//---------------------------------------------如果此消息是针对本地消息，则保存数据否则转发
	Result	=	bspRS485DataSave(pBuffer,ValidLength);
	if(RES_OK	==	Result)
	{
		bspSetAck(pBuffer,ValidLength);					//设置应答数据
	}	
	else if(RES_NotReady	==	Result)					//未准备好或者缓存满
	{
		bspSetAck(pBuffer,ValidLength);					//设置应答数据
		
		pBuffer	=	&pBuffer[1];
		ValidLength	=	ValidLength-1;
		goto Start;		//重新检查剩余数据
	}
	else
	{
		return Result;			//错误帧
	}
	return RES_OK;			//错误帧
}
/*******************************************************************************
* 函数名			:	bspRS485UplinkReceiveDataProcess
* 功能描述		:	函数功能说明 
* 输入			: buffer
							length
							下接口接收限制：目的地址必须为0，源地址必须不为0
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
HCResult bspRS485DownLinkReceiveDataProcess(const unsigned char *buffer,const unsigned short length)
{
	HCResult	Result	=	RES_OK;
	
	RS485FrameDef*			RS485Frame			=	NULL;
	RS485FrameStartDef*	RS485FrameStart	=	NULL;
	FrameDataStartDef*	FrameDataStart	=	NULL;
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
	pBuffer	=	bspRS485GetFrmeAddr(pBuffer,&ValidLength);						//获取RS485帧头地址
	if(NULL	==	pBuffer)	//错误帧
	{
		return RES_Err;			
	}
	//==============================================地址校验：下端接收--目的地址必须为0，源地址必须不为0
	RS485FrameStart	=	(RS485FrameStartDef*)pBuffer;
	if((0!=RS485FrameStart->TargetAddr)		//上端接口：下发数据，目标地址为接收地址
		||(0==RS485FrameStart->SourceAddr))									//下端接口:上传数据，目标地址为0
	{
		pBuffer	=	&pBuffer[1];
		ValidLength	=	ValidLength-1;
		goto Start;		//重新检查剩余数据
	}
	Result	=	bspRS485AckFrameCheck(pBuffer,ValidLength);						//检查是否为应答
	if(RES_OK	==	Result)	//校验错误
	{
		bspRS485DownLinkReleaseTxBuffer();
		pBuffer	=	&pBuffer[1];
		ValidLength	=	ValidLength-1;
		goto Start;		//重新检查剩余数据
	}
	//---------------------------------------------校验
	Result	=	bspRS485Verify(pBuffer,ValidLength);								//校验
	if(RES_OK	!=	Result)	//校验错误
	{
		pBuffer	=	&pBuffer[1];
		ValidLength	=	ValidLength-1;
		goto Start;		//重新检查剩余数据		
	}	
	//---------------------------------------------如果此消息是针对本地消息，则保存数据否则转发
	Result	=	bspRS485DataSave(pBuffer,ValidLength);
	if(RES_OK	==	Result)
	{
		bspSetAck(pBuffer,ValidLength);					//设置应答数据
	}	
	else if(RES_NotReady	==	Result)					//未准备好或者缓存满
	{
		bspSetAck(pBuffer,ValidLength);					//设置应答数据
		
		pBuffer	=	&pBuffer[1];
		ValidLength	=	ValidLength-1;
		goto Start;		//重新检查剩余数据
	}
	else
	{
		return Result;			//错误帧
	}
	return RES_OK;			//错误帧
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
unsigned char* bspRS485GetFrmeAddr(const unsigned char*	buffer,unsigned short* length)
{	
	RS485FrameStartDef*	RS485FrameStart	=	NULL;
	
	unsigned char*	pBuffer		=	NULL;	
	unsigned char*	HeadAddr	=	NULL;
	unsigned char*	EndAddr	=	NULL;
	
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
	Start:			
	//=====================
	HeadAddr	=	(unsigned char*)memchr(pBuffer,RS485HeadCode,ValidLength);
	EndAddr		=	(unsigned char*)memchr(pBuffer,RS485EndCode,ValidLength);
	if(NULL==HeadAddr||NULL==EndAddr)
	{
		return	NULL;		//未找到0x7E
	}	
	ValidLength	=	ValidLength-((unsigned long)HeadAddr-(unsigned long)pBuffer);
	pBuffer			=	HeadAddr;
	//=============================================协议
	//---------------------------------------------帧长度
	if(sizeof(RS485AckDef)>ValidLength)
	{
		return	NULL;		//剩余长度不够最短帧要求
	}
	*length	=	ValidLength;
	return pBuffer;

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
HCResult bspRS485AckFrameCheck(const unsigned char*	buffer,unsigned short length)
{
	RS485AckDef*	RS485AckFrame	=	NULL;	
	
	if(NULL	==	buffer)
	{
		return RES_Err;
	}
	//===============================BCC8校验方式
	RS485AckFrame	=	(RS485AckDef*)buffer;	
	if(RS485EndCode	==	RS485AckFrame->EndCode)
	{
		unsigned	char	Bcc8	=	0;
		Bcc8	=	bspGetBcc8(&buffer[1],sizeof(RS485AckDef)-3);
		if(Bcc8	==	RS485AckFrame->Bcc8)
			return	RES_OK;
	}
	//===============================CRC16校验方式:比BCC8多一字节
	else if(RS485EndCode	==	buffer[sizeof(RS485AckDef)])
	{
		unsigned	short	Crc16S	=	0;	//数据中CRC16
		unsigned	short	Crc16	=	0;
		
		Crc16		=	bspGetCrc16(&buffer[1],sizeof(RS485AckDef)-3);
		Crc16S	=	buffer[sizeof(RS485AckDef)-2];		//CRC16-H
		Crc16S	<<=8;
		Crc16S	|=	buffer[sizeof(RS485AckDef)-1];	//CRC16-L
		if(Crc16	==	Crc16S)
			return	RES_OK;
		else
			return RES_Err;			//非应答
	}
	return RES_Err;					//非应答
}
/*******************************************************************************
* 函数名			:	bspRS485DataSave
* 功能描述		:	保存上端接收或者下端接收的数据
* 输入			: void
* 返回值			: RES_OK	执行正常
							RES_Err	数据错误
							RES_Invalid	无效或者不支持--非本地消息
							RES_NotReady	缓存满
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
HCResult bspRS485DataSave(const unsigned char*	buffer,unsigned short length)
{
	HCResult	Result	=	RES_OK;
		
	Result	=	bspRS485UplinkDataSave(buffer,length);
	if((RES_OK==Result)
		||(RES_OK==RES_NotReady))
	{
		return	Result;
	}
	Result	=	bspRS485DownlinkDataSave(buffer,length);
	return	Result;	
}
/*******************************************************************************
* 函数名			:	bspRS485UplinkDataSave
* 功能描述		:	保存上端接收的数据
* 输入			: void
* 返回值			: RES_OK	执行正常
							RES_Err	数据错误
							RES_Invalid	无效或者不支持--非本地消息
							RES_NotReady	缓存满
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
HCResult bspRS485UplinkDataSave(const unsigned char*	buffer,unsigned short length)
{
	HCResult	Result	=	RES_OK;
	
	RS485FrameDef*			RS485Frame			=	NULL;
	RS485FrameStartDef*	RS485FrameStart	=	NULL;
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
	RS485Frame			=	(RS485FrameDef*)buffer;
	
	DataLength	=	RS485Frame->HStart.DataLength;
	//---------------------------------------------数据长度为0
	if(0	==	DataLength)
	{
		return RES_Err;		//数据长度错误
	}	
	//---------------------------------------------目标地址
	switch(HCSYS.Layer)
	{
		case	MBLayer:TargetAddr	=	RS485Frame->DStart.Addr.CabinetAddr;	break;
		case	CALayer:TargetAddr	=	RS485Frame->DStart.Addr.LayerAddr;		break;
		case	LALayer:TargetAddr	=	RS485Frame->DStart.Addr.SlotAddr;		break;
		case	SALayer:TargetAddr	=	0;		break;
	}
	//---------------------------------------------本级数据
	if(0	==	TargetAddr)	//本级数据:保存到ProcessNode缓存
	{		
		NodeLength	=	DataLength+sizeof(RS485FrameStartDef);
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
			return RES_NotReady;			//缓存满
	}
	if(0==DataNodeD[TargetAddr].NodeLength)
	{
		NodeLength	=	DataLength+sizeof(RS485FrameStartDef);
		DataNodeD[TargetAddr].NodeLength	=	NodeLength;
		memcpy(DataNodeD[TargetAddr].data,pBuffer,NodeLength);
		return RES_OK;
	}
	else
	{
		return RES_NotReady;			//缓存满
	}
	return RES_OK;
}
/*******************************************************************************
* 函数名			:	bspRS485DownlinkDataSave
* 功能描述		:	保存下端接收的数据
* 输入			: void
* 返回值			: RES_OK	执行正常
							RES_Err	数据错误
							RES_Invalid	无效或者不支持--非本地消息
							RES_NotReady	缓存满
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
HCResult bspRS485DownlinkDataSave(const unsigned char*	buffer,unsigned short length)
{
	HCResult	Result	=	RES_OK;
	
	RS485FrameDef*			RS485Frame			=	NULL;
	RS485FrameStartDef*	RS485FrameStart	=	NULL;
//	RS232DataStartDef*	RS232DataStart	=	NULL;
	
	unsigned char*	pBuffer	=	NULL;
	
	unsigned char		Bcc8				=	0;
	unsigned char		DataLength	=	0;
	unsigned char 	TargetAddr	=	0;		//目标地址
	unsigned char 	SourceAddr	=	0;		//源地址
	unsigned char 	i						=	0;
	unsigned short 	NodeLength	=	0;
	
	//=============================================输入规范
	if((NULL	==	buffer)||(0		==	length))
	{
		return	RES_Err;		//输入为空地址或者空长度
	}
	//=============================================获取相关数据
	pBuffer	=	(unsigned char*)buffer;
	RS485Frame			=	(RS485FrameDef*)buffer;
	
	DataLength	=	RS485Frame->HStart.DataLength;
	SourceAddr	=	RS485Frame->HStart.SourceAddr;
	//---------------------------------------------数据长度为0
	if(0	==	DataLength)
	{
		return RES_Err;		//数据长度错误
	}	
	
	//---------------------------------------------加入缓存
	if(0==DataNodeU[SourceAddr].NodeLength)			//检查缓存是否为空
	{
		//---------------------------------------------加入本地址
		switch(HCSYS.Layer)
		{
			
			case	MBLayer:break;
			case	CALayer:RS485Frame->DStart.Addr.CabinetAddr	=	HCSYS.SwitchAddr;	break;
			case	LALayer:RS485Frame->DStart.Addr.LayerAddr		=	HCSYS.SwitchAddr;		break;
			case	SALayer:RS485Frame->DStart.Addr.SlotAddr			=	HCSYS.SwitchAddr;		break;
		}	
		NodeLength	=	DataLength+sizeof(RS485FrameStartDef);
		DataNodeU[SourceAddr].NodeLength	=	NodeLength;
		memcpy(DataNodeU[SourceAddr].data,pBuffer,NodeLength);
		return RES_OK;
	}
	else
	{
		return RES_NotReady;			//缓存满
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
HCResult bspRS485Verify(const unsigned char*	buffer,unsigned short length)
{
	HCResult	Result	=	RES_OK;
	//=============================================输入规范
	if((NULL	==	buffer)||(0		==	length))
	{
		return	RES_Err;		//输入为空地址或者空长度
	}
	//=============================================BCC8
	Result	=		bspRS485VerifyBcc8(buffer,length);
	if(RES_OK	==	Result)
	{
		return	RES_OK;
	}
	//=============================================CRC16
	Result	=		bspRS485VerifyCrc16(buffer,length);
	return	Result;
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
HCResult bspRS485VerifyBcc8(const unsigned char*	buffer,unsigned short length)
{
	RS485FrameDef*			RS485Frame			=	NULL;

	unsigned char		Bcc8				=	0;
	unsigned char		Bcc8S				=	0;		//数据中的BCC8码
	unsigned char		EndCode			=	0;
	unsigned short	DataLength	=	0;	
	
	//=============================================输入规范
	if((NULL	==	buffer)||(0		==	length))
	{
		return	RES_Err;		//输入为空地址或者空长度
	}	
	//=============================================获取相关数据
	RS485Frame	=	(RS485FrameDef*)buffer;
	DataLength	=	RS485Frame->HStart.DataLength;
	
	EndCode	=	buffer[sizeof(RS485FrameStartDef)+DataLength];
	Bcc8S		=	buffer[sizeof(RS485FrameStartDef)+DataLength-1];
	Bcc8		=	bspGetBcc8(&buffer[1],sizeof(RS485FrameStartDef)+DataLength-1);		//去掉头标识符占位
	
	if((Bcc8S==Bcc8)&&(RS485EndCode==EndCode))
	{
		return RES_OK;
	}
	else
	{
		return RES_Err;	//校验错误
	}
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
HCResult bspRS485VerifyCrc16(const unsigned char*	buffer,unsigned short length)
{
	RS485FrameDef*			RS485Frame			=	NULL;
	RS485FrameStartDef*	RS485FrameStart	=	NULL;
//	RS232DataStartDef*	RS232DataStart	=	NULL;
	
	unsigned 	char*	pBuffer	=	NULL;	
	
	unsigned	char	EndCode			=	0;
	unsigned	short	Crc16				=	0;	
	unsigned	short	Crc16S			=	0;	//数据中CRC16	
	unsigned	short	DataLength	=	0;
	unsigned	short	FrameLength	=	0;
	
	//=============================================输入规范
	if((NULL	==	buffer)||(0		==	length))
	{
		return	RES_Err;		//输入为空地址或者空长度
	}	
	//=============================================获取相关数据
	RS485Frame	=	(RS485FrameDef*)buffer;
	DataLength	=	RS485Frame->HStart.DataLength;
	
	FrameLength	=	sizeof(RS485FrameStartDef)+DataLength+3;	//包含两字节CRC16和一字节结束符
	
	EndCode	=	buffer[FrameLength-1];
	Crc16S	=	buffer[FrameLength-3];		//CRC16-H
	Crc16S	<<=8;
	Crc16S	&=0xFF00;
	Crc16S	|=buffer[FrameLength-2];		//CRC16-L
	Crc16		=	bspGetCrc16(&buffer[1],FrameLength-4);			//去掉CRC16校验和头标识符占位
	
	if((Crc16S==Crc16)&&(RS485EndCode==EndCode))
	{
		return RES_OK;
	}
	else
	{
		return RES_Err;	//校验错误
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
unsigned short bspRS485UplinkGetData(unsigned char *buffer)
{
	unsigned char FrameLength	= 0;		//消息帧总长度，从HeadCode到EndCode的字节数
	unsigned char	i	=	0;
	//=====================================接收缓存异常情况：空地址
	if(NULL	==	buffer)
	{
		return 0;
	}
	//=====================================检查TransU缓存
	FrameLength	=	TransU.Length;
	if(0	!=	FrameLength)
	{
		if(TransU.Retry.Time++>ReSendTime)
		{
			TransU.Retry.Time	=	0;
			memcpy(buffer,TransU.data,FrameLength);
			if(++TransU.Retry.Retry>=ReSendCount)		//达到重发次数:释放缓存，放弃重发
			{
				TransU.Length	=	0;
				TransU.Retry.Retry	=	0;
				TransU.Length				=	0;
			}
			return FrameLength;
		}
		else
		{
			return	0;
		}
	}
//  //=====================================检查SendNode缓存
//  for(i=0;i<SelfBuffSize;i++)
//  {		
//    FrameLength	=	SendNode[i].NodeLength;
//		if(0	!=	FrameLength)		//有数据
//		{
//			memcpy(TransU.data,SendNode[i].data,FrameLength);
//			memcpy(buffer,SendNode[i].data,FrameLength);
//			TransU.Length	=	FrameLength;
//			TransU.Retry.Retry	=	0;
//			TransU.Retry.Time		=	0;			
//			SendNode[i].NodeLength	=	0;
//			return FrameLength;
//		}
//  }
	//=====================================检查DataNodeU缓存
	for(i	=	0;i<=MaxNetPerLayer;i++)
	{
		FrameLength	=	DataNodeU[i].NodeLength;
//		if(0	!=	FrameLength)		//有数据
//		{
//			memcpy(TransU.data,DataNodeU[i].data,FrameLength);
//			memcpy(buffer,DataNodeU[i].data,FrameLength);
//			TransU.Length	=	FrameLength;
//			TransU.Retry.Retry	=	0;
//			TransU.Retry.Time		=	0;			
//			DataNodeU[i].NodeLength	=	0;
//			return FrameLength;
//		}
		if(0	!=	FrameLength)		//有数据
		{
			RS485FrameDef*	RS485Frame	=	NULL;
			unsigned char* DataAddr			=	NULL;
			
			unsigned char		Bcc8	=	0;
			unsigned short	Len	=	0;
			DataAddr		=	DataNodeU[i].data;
			
			//-------------------------------------------更新流水号
			RS485Frame	=	(RS485FrameDef*)DataNodeU[i].data;
			RS485Frame->HStart.Serial	=	SerialU++;							//更新流水号
			//-------------------------------------------获取校验码和新消息帧长度(CRC16比BCC8数据长度多一字节)
			FrameLength	=	bspRS485SetCheckCode(DataAddr,FrameLength);		//计算校验码并返回新数据长度
			//-------------------------------------------将数据放置到发送缓冲区
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
* 功能描述		:	获取需要往下层发送的数据--如果有数据，则根据最新流水号计算BCC
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
unsigned short bspRS485DownlinkGetData(unsigned char *buffer)
{
	RS485FrameDef*	RS485Frame			=	NULL;
	
	unsigned char	FrameLength	= 0;		//消息帧总长度，从HeadCode到EndCode的字节数
	unsigned char	i	=	0;	
	
	//=====================================接收缓存异常情况：空地址
	if(NULL	==	buffer)
	{
		return 0;
	}	
	//=====================================检查TransD缓存
	FrameLength	=	TransD.Length;
	if(0	!=	FrameLength)
	{
		if(TransD.Retry.Time	++>ReSendTime)
		{
			TransD.Retry.Time	=	0;
			memcpy(buffer,TransD.data,FrameLength);
			TransD.Retry.Retry+=1;
			if((TransD.Retry.Retry)>=ReSendCount)		//达到重发次数:释放缓存，放弃重发
			{				
				TransD.Length				=	0;
				TransD.Retry.Retry	=	0;
				TransD.Length				=	0;
				bspSetErrorCode(TransD.data,Err_TimeOut);
			}
			return FrameLength;
		}
		else
		{
			return	0;
		}
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
			
			//-------------------------------------------更新流水号
			RS485Frame	=	(RS485FrameDef*)DataNodeD[i].data;
			RS485Frame->HStart.Serial	=	SerialD++;							//更新流水号
			//-------------------------------------------获取校验码和新消息帧长度(CRC16比BCC8数据长度多一字节)
			FrameLength	=	bspRS485SetCheckCode(DataAddr,FrameLength);		//计算校验码并返回新数据长度
			//-------------------------------------------将数据放置到发送缓冲区
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
HCResult bspRS232UplinkReceiveDataProcess(const unsigned char *buffer,const unsigned short length)
{
	HCResult	Result	=	RES_OK;
	
	RS232FrameDef*			RS232Frame			=	NULL;
	RS232FrameStartDef*	RS232FrameStart	=	NULL;
//	RS232DataStartDef*	RS232DataStart	=	NULL;
	
	unsigned char*	pBuffer		=	NULL;	
	unsigned char*	Head1Addr	=	NULL;
	unsigned char*	Head2Addr	=	NULL;	
	
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
	pBuffer	=	bspRS232GetFrmeAddr(pBuffer,&ValidLength);		//获取RS232帧头地址
	if(NULL	==	pBuffer)	//错误帧
	{
		return RES_Err;			
	}
	//---------------------------------------------BCC校验
	Result	=	bspRS232Verify(pBuffer,ValidLength);					//校验
	if(RES_OK	!=	Result)	//校验错误
	{
		pBuffer	=	&pBuffer[1];
		ValidLength	=	ValidLength-1;
		goto Start;		//重新检查剩余数据		
	}	
	Result	=	bspRS232AckFrameCheck(pBuffer,ValidLength);		//检查是否为应答
	if(RES_OK	==	Result)
	{
		bspRS232ReleaseTxBuffer();
		
		pBuffer	=	&pBuffer[1];
		ValidLength	=	ValidLength-1;
		goto Start;		//重新检查剩余数据
	}
	//---------------------------------------------如果此消息是针对本地消息，则保存数据否则转发
	Result	=	bspRS232DataSave(pBuffer,ValidLength);
	if(RES_OK	==	Result)
	{
		bspSetAck(pBuffer,ValidLength);					//设置应答数据
	}	
	else if(RES_NotReady	==	Result)					//未准备好或者缓存满
	{
		bspSetAck(pBuffer,ValidLength);					//设置应答数据
		
		pBuffer	=	&pBuffer[1];
		ValidLength	=	ValidLength-1;
		goto Start;		//重新检查剩余数据
	}
	else if(RES_Invalid	==	Result)						//非本层数据---转发
	{		
		Result	=	bspRS232ToRS485(pBuffer,length);		//RS232协议转换为RS485协议
		if(RES_OK	==	Result)
		{			
			bspSetAck(pBuffer,ValidLength);					//设置应答数据
			
			pBuffer	=	&pBuffer[1];
			ValidLength	=	ValidLength-1;
			goto Start;		//重新检查剩余数据			
		}
		else if(RES_NotReady	==	Result)
		{
			bspSetAck(pBuffer,ValidLength);					//设置应答数据
		}
		
	}
	else
	{
		return Result;			//错误帧
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
	
	unsigned char*	pBuffer		=	NULL;	
	unsigned char*	Head1Addr	=	NULL;
	unsigned char*	Head2Addr	=	NULL;
	
	
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
HCResult bspRS232Verify(const unsigned char*	buffer,unsigned short length)
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
* 函数名			:	bspRS232DataSave
* 功能描述		:	如果此消息是针对本地消息，则保存数据
* 输入			: void
* 返回值			: RES_OK	执行正常
							RES_Err	数据错误
							RES_Invalid	无效或者不支持--非本地消息
							RES_NotReady	缓存满
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
HCResult bspRS232DataSave(const unsigned char*	buffer,unsigned short length)
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
			return RES_NotReady;			//缓存满
	}
	//---------------------------------------------需要转发的数据
	else
	{
		return	RES_Invalid;				//无效或者不支持：非本地消息
	}
	return RES_OK;
}
/*******************************************************************************
* 函数名			:	bspRS232ToRS485
* 功能描述		:	RS232协议转换为RS485协议
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
	
	RS485Frame->HStart.HeadCode		=	RS485HeadCode;														//头标识符
	RS485Frame->HStart.TargetAddr	=	TargetAddr;																//目的地址
	RS485Frame->HStart.SourceAddr	=	0x00;																			//源地址---下发时源地址必须为0
	
	RS485Frame->HStart.Cmd				=	RS232Frame->HStart.Cmd;										//命令号
	RS485Frame->HStart.UserCode		=	RS232Frame->HStart.UserCode;							//用户码
	
	//------------------------------------------地址域
	RS485Frame->DStart.Addr.CabinetAddr	=	RS232Frame->DStart.Addr.CabinetAddr;
	RS485Frame->DStart.Addr.LayerAddr		=	RS232Frame->DStart.Addr.LayerAddr;
	RS485Frame->DStart.Addr.SlotAddr		=	RS232Frame->DStart.Addr.SlotAddr;
	
	RS485Frame->DStart.ErrCode					=	RS232Frame->DStart.ErrCode;					//错误码/状态码
	RS485Frame->HStart.DataLength				=	RS232Frame->HStart.DataLength;			//数据长度
	
	pRS232Data	=	(unsigned char*)&RS232Frame->DStart.ErrCode;								//RS232错误码地址---下一地址为数据起始地址
	pRS232Data	=	&pRS232Data[1];																							//RS232数据起始地址
	
	pRS485Data	=	(unsigned char*)&RS485Frame->DStart.ErrCode;								//RS485错误码地址---下一地址为数据起始地址
	pRS485Data	=	&pRS485Data[1];																							//RS485数据起始地址
	
	RS485Frame->Data	=	pRS485Data;
	
	DataLength	=	RS485Frame->HStart.DataLength	-sizeof(AddrDef)-sizeof(ErrCodeDef);		//RS485数据长度转换：不包括地址和错误码
	
	memcpy(pRS485Data,pRS232Data,DataLength);		//拷贝数据
	
	//------------------------------------------校验码在此不计算：在发送时根据最新流水号重新计算校验码
//	Bcc8	=	bspGetBcc8(&RS485Frame->DStart.Addr.CabinetAddr,RS485Frame->DStart.DataLength);		//从地址开始校验//	
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
/*******************************************************************************
* 函数名			:	bspRS232ReleaseTxData
* 功能描述		:	释放上传缓存：上传成功或者超时后调用 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
HCResult bspRS485UplinkReleaseTxBuffer(void)
{
	TransU.Length	=	0;
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
HCResult bspRS485DownLinkReleaseTxBuffer(void)
{
	TransD.Length	=	0;
	return RES_OK;
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
* 函数名			:	function
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
unsigned short bspGetCrc16(const unsigned char *HeadAddr,const unsigned short length)
{
	unsigned char		*pBuffer		=	0;			//数据处理buffer

	unsigned	short Crc16	=	0;
	
	pBuffer	=	(unsigned char*)HeadAddr;
	if(NULL==pBuffer||0==length)
		return	0;
	//=================================================================================导入数据:输入为const类型
	Crc16	=	CRC16_MODBUS(pBuffer,length);				//多项式x16+x15+x5+1（0x8005），初始值0xFFFF，低位在前，高位在后，结果与0x0000异或
	return Crc16;
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
unsigned short bspRS485SetCheckCode(const unsigned char *FrameAddr,const unsigned short Framelength)
{
	RS485FrameDef*	RS485Frame			=	NULL;
	
	unsigned	char*	pBuffer		=	NULL;			//数据处理buffer
	
	
	unsigned	short	NewFrameLength	= 0;		//消息帧总长度，从HeadCode到EndCode的字节数	
	unsigned	short	Len	=	0;
	
	RS485Frame	=	(RS485FrameDef*)FrameAddr;
	NewFrameLength	=	Framelength;
	if(NULL==RS485Frame||0==NewFrameLength)
		return	0;
	//=================================================================================导入数据:输入为const类型

	pBuffer		=	(unsigned	char*)RS485Frame;	
	Len		=	NewFrameLength-3;	//3为头尾标识和校验位长度
	
#if(CheckCodeUseCRC16)		//使用CRC16校验
	{
	//-----------------------------------------使用CRC16校验
	unsigned	short Crc16	=	0;
	Crc16	=	bspGetCrc16(&pBuffer[1],Len);				//多项式x16+x15+x5+1（0x8005），初始值0xFFFF，低位在前，高位在后，结果与0x0000异或
	pBuffer[NewFrameLength-2]	=	Crc16>>8&0xFF;		//高8位在前
	pBuffer[NewFrameLength-1]	=	Crc16&0xFF;
	pBuffer[NewFrameLength]		=	RS485EndCode;
//	RS485Frame->HStart.DataLength	=	RS485Frame->HStart.DataLength+1;	//CRC16时数据段会多一字节
	NewFrameLength+=1;						//用CRC16时帧长度需要增加一字节
	}
#else			//使用BCC8校验
	{
	//-----------------------------------------使用BCC8校验
	DataAddr[FrameLength-2]	=	bspGetBcc8(&DataAddr[1],Len);
	}
#endif
	return NewFrameLength;
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
HCResult bspRS485GetCheckCode(const unsigned char *FrameAddr,const unsigned short Framelength)
{
	RS485FrameDef*	RS485Frame			=	NULL;
	
	unsigned	char*	pBuffer		=	NULL;			//数据处理buffer
	
	
	unsigned	short	NewFrameLength	= 0;		//消息帧总长度，从HeadCode到EndCode的字节数	
	unsigned	short	Len	=	0;
	
	RS485Frame	=	(RS485FrameDef*)FrameAddr;
	NewFrameLength	=	Framelength;
	if(NULL==RS485Frame||0==NewFrameLength)
		return	RES_Err;
	//=================================================================================导入数据:输入为const类型

	pBuffer		=	(unsigned	char*)RS485Frame;	
	Len		=	NewFrameLength-3;	//3为头尾标识和校验位长度
	
#if(CheckCodeUseCRC16)		//使用CRC16校验
{	
	//-----------------------------------------使用CRC16校验
	unsigned	short Crc16				=	0;		//计算出的CRC16
	unsigned	short SoureCrc16	=	0;		//数据帧中的CRC16
	SoureCrc16	=	(((unsigned short)pBuffer[NewFrameLength-2])<<8)&0xFF00;
	SoureCrc16	|=pBuffer[NewFrameLength-1];
	
	Crc16	=	bspGetCrc16(&pBuffer[1],Len);				//多项式x16+x15+x5+1（0x8005），初始值0xFFFF，低位在前，高位在后，结果与0x0000异或
	
	if(SoureCrc16	==	Crc16)
		return	RES_OK;		//校验正确
	else
		return	RES_Err;	//校验错误
}
#else			//使用BCC8校验
{
	//-----------------------------------------使用BCC8校验
	unsigned	char	BCC8	=	0;				//计算出的BCC8
	unsigned	char	SoureBCC8	=	0;		//原BCC8
	SoureBCC8	=	DataAddr[FrameLength-1];
	BCC8	=	bspGetBcc8(&DataAddr[1],Len);
	if(SoureBCC8	==	BCC8)
		return	RES_OK;		//校验正确
	else
		return	RES_Err;	//校验错误
}
#endif
	return RES_OK;
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
	static RS232FrameDef*			RS232Frame			=	NULL;
	static RS485FrameDef*			RS485Frame			=	NULL;
	
	//=============================================输入规范
	if((NULL	==	buffer)||(0		==	length))
	{
		return	RES_Err;		//输入为空地址或者空长度
	}
	//=============================================RS232
	RS232Frame	=	(RS232FrameDef*)buffer;
	RS485Frame	=	(RS485FrameDef*)buffer;
	if((RS232Head1==RS232Frame->HStart.Head1)&&(RS232Head2==RS232Frame->HStart.Head2))
	{
		RS232Frame	=	(RS232FrameDef*)ACKU.data;		
		memcpy(ACKU.data,buffer,sizeof(RS232FrameStartDef));
		
		RS232Frame->HStart.Bcc8				=	0;
		RS232Frame->HStart.DataLength	=	0;
		ACKU.FarmeLength	=	sizeof(RS232FrameStartDef);
	}
	//=============================================RS485
	else if(
					(RS485HeadCode	==	RS485Frame->HStart.HeadCode)
				&&(0							!=	RS485Frame->HStart.DataLength)
				)
	{
		RS485AckDef*	RS485AckFrame	=	NULL;
		//---------------------------------------------下级往上传数据(目标地址为0，源地址为下级地址)：应答为向下应答
		//---------------------向下应答
		if(
				(0==RS485Frame->HStart.TargetAddr)
			&&(0!=RS485Frame->HStart.SourceAddr)
		)
		{
			
#if(CheckCodeUseCRC16)
			unsigned	char*	pBuffer	=	NULL;
			unsigned	short	Crc16	=	0;
			RS485AckFrame	=	(RS485AckDef*)ACKD.data;
			RS485AckFrame->HeadCode		=	RS485HeadCode;
			RS485AckFrame->TargetAddr	=	RS485AckFrame->SourceAddr;
			RS485AckFrame->SourceAddr	=	0x00;
			RS485AckFrame->ErrCode		=	Err_None;
			RS485AckFrame->Bcc8				=	bspGetCrc16((const unsigned char*)RS485AckFrame,3);
			RS485AckFrame->EndCode		=	RS485EndCode;
			
			pBuffer	=	(unsigned	char*)RS485AckFrame;
			Crc16	=	bspGetCrc16((const unsigned char*)&RS485AckFrame->TargetAddr,3);
			pBuffer[4]	=Crc16>>8&0xFF;
			pBuffer[5]	=Crc16&0xFF;
			pBuffer[6]	=RS485EndCode;
			memcpy(ACKD.data,pBuffer,sizeof(RS485AckDef)+1);
			
			ACKD.FarmeLength	=	sizeof(RS485AckDef)+1;
#else
			RS485AckFrame	=	(RS485AckDef*)ACKD.data;
			RS485AckFrame->HeadCode		=	RS485HeadCode;
			RS485AckFrame->TargetAddr	=	RS485AckFrame->SourceAddr;
			RS485AckFrame->SourceAddr	=	0x00;
			RS485AckFrame->ErrCode		=	Err_None;
			RS485AckFrame->Bcc8				=	bspGetBcc8((const unsigned char*)&RS485AckFrame->TargetAddr,3);
			RS485AckFrame->EndCode		=	RS485EndCode;
			
			memcpy(ACKD.data,RS485AckFrame,sizeof(RS485AckDef));
			
			ACKD.FarmeLength	=	sizeof(RS485AckDef);
#endif
		}
		//---------------------向上应答
		else if(
			(0!=RS485Frame->HStart.TargetAddr)
		&&(0==RS485Frame->HStart.SourceAddr)
		)
		{
			
#if(CheckCodeUseCRC16)
			unsigned	char*	pBuffer	=	NULL;
			unsigned	short	Crc16	=	0;
			RS485AckFrame	=	(RS485AckDef*)ACKU.data;
			RS485AckFrame->HeadCode		=	RS485HeadCode;
			RS485AckFrame->TargetAddr	=	0x00;
			RS485AckFrame->SourceAddr	=	HCSYS.SwitchAddr;
			RS485AckFrame->ErrCode		=	Err_None;
//			RS485AckFrame->Bcc8				=	bspGetCrc16((const unsigned char*)RS485AckFrame,3);
//			RS485AckFrame->EndCode		=	RS485EndCode;
			
			pBuffer	=	(unsigned	char*)RS485AckFrame;
			Crc16	=	bspGetCrc16((const unsigned char*)&RS485AckFrame->TargetAddr,3);
			pBuffer[4]	=Crc16>>8&0xFF;
			pBuffer[5]	=Crc16&0xFF;
			pBuffer[6]	=RS485EndCode;
			memcpy(ACKU.data,pBuffer,sizeof(RS485AckDef)+1);
			
			ACKU.FarmeLength	=	sizeof(RS485AckDef)+1;
#else
			RS485AckFrame	=	(RS485AckDef*)ACKU.data;
			RS485AckFrame->HeadCode		=	RS485HeadCode;
			RS485AckFrame->TargetAddr	=	0x00;
			RS485AckFrame->SourceAddr	=	HCSYS.SwitchAddr;
			RS485AckFrame->ErrCode		=	Err_None;
			RS485AckFrame->Bcc8				=	bspGetBcc8((const unsigned char*)&RS485AckFrame->TargetAddr,3);
			RS485AckFrame->EndCode		=	RS485EndCode;
			
			memcpy(ACKU.data,RS485AckFrame,sizeof(RS485AckDef));
			
			ACKU.FarmeLength	=	sizeof(RS485AckDef);
#endif
		}
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
HCResult bspSetErrorCode(const unsigned char*	buffer,ErrCodeDef Err)
{
	RS485FrameDef*	RS485Frame			=	NULL;	
	unsigned char	FrameLength	= 0;		//消息帧总长度，从HeadCode到EndCode的字节数
	unsigned char	i	=	0;
	unsigned	char	TargetAddr	=	0;
	//=====================================接收缓存异常情况：空地址
	if(NULL	==	buffer)
	{
		return RES_Err;
	}
	RS485Frame	=	(RS485FrameDef*)buffer;
	switch(HCSYS.Layer)
	{
		
		case	MBLayer:
					RS485Frame->DStart.Addr.LayerAddr		=	0;
					RS485Frame->DStart.Addr.SlotAddr		=	0;
		break;
		case	CALayer:
					RS485Frame->DStart.Addr.SlotAddr		=	0;
		break;
		case	LALayer:
		break;
	}
	TargetAddr	=	RS485Frame->HStart.TargetAddr;
	RS485Frame->HStart.TargetAddr	=	0;
	RS485Frame->HStart.SourceAddr	=	HCSYS.SwitchAddr;
	RS485Frame->HStart.DataLength	=sizeof(FrameDataStartDef);
	RS485Frame->DStart.ErrCode		=	Err;
	memcpy(DataNodeU[TargetAddr].data,RS485Frame,sizeof(RS485FrameStartDef)+sizeof(FrameDataStartDef));
	DataNodeU[TargetAddr].NodeLength	=	sizeof(RS485FrameStartDef)+sizeof(FrameDataStartDef)+2;		//加一字节校验位和一字节结束符
}
/*******************************************************************************
* 函数名			:	APIGetdownlinkData
* 功能描述		:	获取需要往下层发送的数据--如果有数据，则根据最新流水号计算BCC
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
unsigned short bspUplinkGetAck(unsigned char *buffer)
{
	unsigned	short length	=	0;
	//=====================================检查RS485ACKD缓存
	length	=	ACKU.FarmeLength;
	if(0	!=	length)
	{
		memcpy(buffer,&ACKU.data,length);
		ACKU.FarmeLength	=	0;
		return length;
	}	
	return	length;
}
/*******************************************************************************
* 函数名			:	APIGetdownlinkData
* 功能描述		:	获取需要往下层发送的数据--如果有数据，则根据最新流水号计算BCC
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
unsigned short bspDownLinkGetAck(unsigned char *buffer)
{
	unsigned	short length	=	0;
	//=====================================检查RS485ACKD缓存
	length	=	ACKD.FarmeLength;
	if(0	!=	length)
	{
		memcpy(buffer,&ACKD.data,length);
		ACKD.FarmeLength	=	0;
		return length;
	}	
	return	length;
}
/*******************************************************************************
* 函数名			:	Com_DelaymS
* 功能描述		:	延时x毫秒
* 输入			: void
* 返回值			: void
*******************************************************************************/
void Com_DelaymS(u32 xms)
{
	SysTick_DeleymS(xms);				//SysTick延时nmS;
}






