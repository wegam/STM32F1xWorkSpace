

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
//	HCResult	res	=	RES_OK;
	
	RS485FrameDef *RS485Frame  				= NULL;
	unsigned long	*RS485EndCodeAddr		= NULL;
	unsigned char	*pBuffer						=	0;
	
	unsigned char		SourceBcc8  = 0;
  unsigned short	FarmeLen		=	0;
	unsigned short	DataLength	=	0;
	unsigned short 	ValidLength	= 0;    //buffer中有效数据长度(从RS485头标识符开始后的数据为有效数据)
	
  if(NULL ==  buffer) //空地址
	{
		return RES_PARERR;
	}
  //=========================================查找RS485HeadCode头标识符
	pBuffer			=	(unsigned char*)buffer;
	ValidLength	=	length;
	//-----------------------------------------查找头标识
	CheckFarm:
	RS485Frame 				=	(RS485FrameDef*)memchr(pBuffer,RS485HeadCode,ValidLength);							//查找RS485HeadCode头标识符	
	if(NULL==RS485Frame)
	{
		return RES_PARERR;
	}
	ValidLength				=	ValidLength-((unsigned long)RS485Frame-(unsigned long)pBuffer);		//剩余数据长度
	RS485EndCodeAddr	=	(unsigned long*)memchr(RS485Frame,RS485EndCode,length);		//查找RS485EndCode尾标识符----从头标识符后开始查找
	if(NULL==RS485EndCodeAddr)
	{
		return RES_PARERR;
	}
	//-----------------------------------------地址判断:上层下发，识别目标地址是否为本地址或者广播地址0xFF
	pBuffer	=	(unsigned char*)RS485Frame;
	if((HCSYS.SwitchAddr!=RS485Frame->TargetAddr)&&(0xFF!=RS485Frame->TargetAddr))
	{		
		pBuffer	=	&pBuffer[1];
		goto CheckFarm;
	}
	//-----------------------------------------帧长度判断
	FarmeLen		=	(unsigned long)RS485EndCodeAddr-(unsigned long)RS485Frame+1;	
	if(RS485MinFrameLen>FarmeLen)
	{
		goto CheckFarm;
	}
	//-----------------------------------------应答帧判断
	if(RS485AckFrameLen==FarmeLen)		//应答帧
	{
		//---------------------------------------校验判断
		SourceBcc8	=	BCC8(&pBuffer[1],3);
		if(SourceBcc8!=pBuffer[4])			//应答消息
		{
			pBuffer	=	&pBuffer[1];
			goto CheckFarm;								//校验不对
		}
		//---------------------------------------应答帧:释放上传缓存
		else
		{
			TransU.Length	=	0;			//清除发送缓存
			pBuffer	=	&pBuffer[1];
			goto CheckFarm;
		}
	}
	//-----------------------------------------消息帧判断
	else
	{
		if(ValidLength<RS485Frame->DataLength+RS485StartFrameLen+2)
		{
			pBuffer	=	&pBuffer[1];
			goto CheckFarm;
		}
		DataLength	=	RS485Frame->DataLength;
		//---------------------------------------校验判断
		SourceBcc8	=	BCC8(&pBuffer[1],RS485StartFrameLen+DataLength-1);
		if(SourceBcc8	!=	pBuffer[RS485StartFrameLen+DataLength])
		{
			pBuffer	=	&pBuffer[1];
			goto CheckFarm;
		}
		//---------------------------------------数据正确：根据地址保存到DataNodeD或者SelfNode
		else
		{	
			//本地数据缓存大小SelfBuffSize
			unsigned char NextAddr	=	0;			//下一层地址			
			unsigned char	*Addr			=	NULL;
			unsigned char	*pTemp		=	NULL;
			
			Addr	=	&RS485Frame->CabinetAddr;
			//---------------------------------------中间级
			if(HCSYS.Layer<3)		//非最终端设备
			{
				NextAddr	=	Addr[HCSYS.Layer];
				if(0xFF	==	NextAddr)
				{
					NextAddr	=	0;
					if(DataNodeD[0].Length)
					{
						ACKU.Ack.ErrCode		=	Err_FAULT_BUSY;
					}
					else
					{
						memcpy(DataNodeD[0].data,RS485Frame,RS485Frame->DataLength+RS485StartFrameLen);						
						DataNodeD[0].Length	=	RS485Frame->DataLength+RS485StartFrameLen+2;						
						RS485Frame	=	(RS485FrameDef*)DataNodeD[0].data;
						pTemp	=	(unsigned char*)DataNodeD[0].data;
						//------------------------修改目的地址和源地址
						RS485Frame->TargetAddr	=	0xFF;
						RS485Frame->SourceAddr	=	0x00;
						//------------------------校验
						pTemp[RS485Frame->DataLength+RS485StartFrameLen]	=	BCC8(&pTemp[1],RS485Frame->DataLength+RS485StartFrameLen-1);	//头标识符和尾标识符不参与校验
						pTemp[RS485Frame->DataLength+RS485StartFrameLen+1]	=	RS485EndCode;
						ACKU.Ack.ErrCode		=	Err_None;
					}
				}
				else
				{
					if(DataNodeD[NextAddr].Length)
					{
						ACKU.Ack.ErrCode		=	Err_FAULT_BUSY;
					}
					else
					{
						memcpy(DataNodeD[NextAddr].data,RS485Frame,RS485Frame->DataLength+RS485StartFrameLen);
						DataNodeD[NextAddr].Length	=	RS485Frame->DataLength+RS485StartFrameLen+2;
						RS485Frame	=	(RS485FrameDef*)DataNodeD[NextAddr].data;
						pTemp	=	(unsigned char*)DataNodeD[NextAddr].data;
						//------------------------修改目的地址和源地址
						RS485Frame->TargetAddr	=	NextAddr;
						RS485Frame->SourceAddr	=	0x00;
						//------------------------校验
						pTemp[RS485Frame->DataLength+RS485StartFrameLen]	=	BCC8(&pTemp[1],RS485Frame->DataLength+RS485StartFrameLen-1);	//头标识符和尾标识符不参与校验
						pTemp[RS485Frame->DataLength+RS485StartFrameLen+1]	=	RS485EndCode;
						ACKU.Ack.ErrCode		=	Err_None;
					}						
				}				
			}
			//---------------------------------------终端级
			else
			{	
				unsigned char i	=	0;
				for(i=0;i<SelfBuffSize;i++)
				{
					if(0	==	ProcessNode[i].Length)
					{
						unsigned char *pTemp	=	NULL;
						pTemp	=	(unsigned char*)RS485Frame;
						pTemp	=	&pTemp[RS485StartFrameLen];
//						memcpy(ProcessNode[i].data,RS485Frame,RS485Frame->DataLength+RS485StartFrameLen+2);	//将源数据全部拷贝
						memcpy(ProcessNode[i].data,pTemp,RS485Frame->DataLength);	//将源数据全部拷贝
						ProcessNode[i].Length	=	RS485Frame->DataLength;
						break;
					}
				}
				if(i<SelfBuffSize)		//应答
				{
					ACKU.Ack.ErrCode		=	Err_None;
				}
				else
				{
					ACKU.Ack.ErrCode		=	Err_FAULT_BUSY;
				}
			}			
			ACKU.Ack.HeadCode		=	RS485HeadCode;
			ACKU.Ack.TargetAddr	=	0;
			ACKU.Ack.SourceAddr	=	HCSYS.SwitchAddr;
			//ACKU.Ack.ErrCode		=	Err_None;
			ACKU.Ack.Bcc8				=	BCC8(&ACKU.Ack.TargetAddr,3);
			ACKU.Ack.EndCode		=	RS485EndCode;
			ACKU.FarmeLength		=	RS485AckFrameLen;
			
			pBuffer	=	&pBuffer[1];
			goto CheckFarm;
		}
	}
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
	//	HCResult	res	=	RES_OK;
	
	RS485FrameDef *RS485Frame  	= NULL;
	unsigned long	*RS485EndCodeAddr		= NULL;
	unsigned char	*pBuffer						=	0;
	
	unsigned char		SourceBcc8  = 0;
  unsigned short	FarmeLen		=	0;
	unsigned short	DataLength	=	0;
	unsigned short 	ValidLength	= 0;    //buffer中有效数据长度(从RS485头标识符开始后的数据为有效数据)
	
  if(NULL ==  buffer) //空地址
	{
		return RES_PARERR;
	}
  //=========================================查找RS485HeadCode头标识符
	pBuffer			=	(unsigned char*)buffer;
	ValidLength	=	length;
	//-----------------------------------------查找头标识
	CheckFarm:
	RS485Frame 				=	(RS485FrameDef*)memchr(pBuffer,RS485HeadCode,length);							//查找RS485HeadCode头标识符	
	if(NULL==RS485Frame)
	{
		return RES_PARERR;
	}
	ValidLength				=	ValidLength-((unsigned long)RS485Frame-(unsigned long)pBuffer);		//剩余数据长度
	RS485EndCodeAddr	=	(unsigned long*)memchr(RS485Frame,RS485EndCode,length);		//查找RS485EndCode尾标识符----从头标识符后开始查找
	if(NULL==RS485EndCodeAddr)
	{
		return RES_PARERR;
	}
	//-----------------------------------------地址判断:下层上传，目标地址为0，原地址为上传的地址
	pBuffer	=	(unsigned char*)RS485Frame;
	if((0x00!=RS485Frame->TargetAddr)||(0x00==RS485Frame->SourceAddr))
	{		
		pBuffer	=	&pBuffer[1];
		goto CheckFarm;
	}
	//-----------------------------------------帧长度判断
	FarmeLen		=	(unsigned long)RS485EndCodeAddr-(unsigned long)RS485Frame+1;	
	if(RS485MinFrameLen>FarmeLen)
	{
		goto CheckFarm;
	}
	//-----------------------------------------应答帧判断
	if(RS485AckFrameLen==FarmeLen)		//应答帧
	{
		//---------------------------------------校验判断
		SourceBcc8	=	BCC8(&pBuffer[1],3);
		if(SourceBcc8!=pBuffer[4])			//应答消息
		{
			pBuffer	=	&pBuffer[1];
			goto CheckFarm;								//校验不对
		}
		//---------------------------------------应答帧:释放下发缓存
		else
		{
			TransD.Length	=	0;			//清除发送缓存
			pBuffer	=	&pBuffer[1];
			goto CheckFarm;
		}
	}
	//-----------------------------------------消息帧判断
	else
	{
		if(ValidLength<RS485Frame->DataLength+RS485StartFrameLen+2)
		{
			pBuffer	=	&pBuffer[1];
			goto CheckFarm;
		}
		DataLength	=	RS485Frame->DataLength;
		//---------------------------------------校验判断
		SourceBcc8	=	BCC8(&pBuffer[1],RS485StartFrameLen+DataLength-1);
		if(SourceBcc8	!=	pBuffer[RS485StartFrameLen+DataLength])
		{
			pBuffer	=	&pBuffer[1];
			goto CheckFarm;
		}
		//---------------------------------------数据正确：根据地址保存到DataNodeD或者SelfNode
		else
		{	
			//本地数据缓存大小SelfBuffSize
			unsigned char SourceAddr	=	0;			//下一层地址			
			unsigned char	*Addr			=	NULL;
			unsigned char	*pTemp		=	NULL;
			unsigned char Layer			=	HCSYS.Layer;
			
			
//			SourceAddr	=	Addr[HCSYS.Layer];
			SourceAddr	=	RS485Frame->SourceAddr;
			//---------------------------------------中间级
			if(HCSYS.Layer>0)		//非最终端设备--最顶层
			{
				Layer	=	Layer-1;
//				SourceAddr	=	Addr[HCSYS.Layer];

				if(DataNodeU[SourceAddr].Length)
				{
					ACKD.Ack.TargetAddr	=	RS485Frame->SourceAddr;
					ACKD.Ack.ErrCode		=	Err_FAULT_BUSY;
				}
				else
				{
					ACKD.Ack.TargetAddr	=	RS485Frame->SourceAddr;					
					
					memcpy(DataNodeU[SourceAddr].data,RS485Frame,RS485Frame->DataLength+RS485StartFrameLen);
					
					DataNodeU[SourceAddr].Length	=	RS485Frame->DataLength+RS485StartFrameLen+2;
					
					RS485Frame	=	(RS485FrameDef*)DataNodeU[SourceAddr].data;
					Addr	=	&RS485Frame->CabinetAddr;
					
					pTemp	=	(unsigned char*)DataNodeU[SourceAddr].data;
					//------------------------修改目的地址和源地址
					RS485Frame->TargetAddr	=	0x00;
					RS485Frame->SourceAddr	=	HCSYS.SwitchAddr;
					Addr[Layer]				=	HCSYS.SwitchAddr;
					//------------------------校验
					pTemp[RS485Frame->DataLength+RS485StartFrameLen]	=	BCC8(&pTemp[1],RS485Frame->DataLength+RS485StartFrameLen-1);	//头标识符和尾标识符不参与校验
					pTemp[RS485Frame->DataLength+RS485StartFrameLen+1]	=	RS485EndCode;
					ACKD.Ack.ErrCode		=	Err_None;
				}						
			}
			//---------------------------------------终端级--最顶层：转485
			else
			{	
				if(DataNodeU[SourceAddr].Length)
				{
					ACKD.Ack.TargetAddr	=	RS485Frame->SourceAddr;
					ACKD.Ack.ErrCode		=	Err_FAULT_BUSY;
				}
				else
				{
					ACKD.Ack.TargetAddr	=	RS485Frame->SourceAddr;
					memcpy(DataNodeU[SourceAddr].data,RS485Frame,RS485Frame->DataLength+RS485StartFrameLen);
					
					DataNodeU[SourceAddr].Length	=	RS485Frame->DataLength+RS485StartFrameLen+2;
					RS485Frame	=	(RS485FrameDef*)DataNodeU[SourceAddr].data;
					pTemp	=	(unsigned char*)DataNodeU[SourceAddr].data;
					//------------------------修改目的地址和源地址
					RS485Frame->TargetAddr	=	0x00;
					RS485Frame->SourceAddr	=	HCSYS.SwitchAddr;
//					Addr[HCSYS.Layer]				=	HCSYS.SwitchAddr;
					//------------------------校验
					pTemp[RS485Frame->DataLength+RS485StartFrameLen]	=	BCC8(&pTemp[1],RS485Frame->DataLength+RS485StartFrameLen-1);	//头标识符和尾标识符不参与校验
					pTemp[RS485Frame->DataLength+RS485StartFrameLen+1]	=	RS485EndCode;
					
					ACKD.Ack.ErrCode		=	Err_None;
				}
			}			
			ACKD.Ack.HeadCode		=	RS485HeadCode;			
			ACKD.Ack.SourceAddr	=	0x00;
			//ACKU.Ack.ErrCode		=	Err_None;
			ACKD.Ack.Bcc8				=	BCC8(&ACKD.Ack.TargetAddr,3);
			ACKD.Ack.EndCode		=	RS485EndCode;
			ACKD.FarmeLength		=	RS485AckFrameLen;
			
			pBuffer	=	&pBuffer[1];
			goto CheckFarm;
		}
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
  HCResult	res	=	RES_OK;
	
	RS485FrameDef *RS485Frame  	= NULL;
//	unsigned long	*RS485EndCodeAddr		= NULL;
	unsigned char	*pBuffer						=	0;
	
  unsigned char   i = 0;
//	unsigned char		SourceBcc8  = 0;
//  unsigned short	FarmeLen		=	0;
//	unsigned short	DataLength	=	0;
//	unsigned short 	ValidLength	= 0;    //buffer中有效数据长度(从RS485头标识符开始后的数据为有效数据)
	
  if(NULL ==  buffer) //空地址
	{
		return RES_PARERR;
	}
  //=========================================检查数据长度超限
  if(length+RS485StartFrameLen+2>BusDataSize)
  {
    return RES_DataOF;
  }
  //=========================================查找空缓存
  for(i=0;i<SelfBuffSize;i++)
  {
    if(0  ==  SendNode[i].Length) //空缓存
    {
      RS485Frame  = (RS485FrameDef*)SendNode[i].data;
//      pBuffer     = (unsigned char*)RS485Frame->data;
			pBuffer     = (unsigned char*)SendNode[i].data;
			pBuffer			=	&pBuffer[RS485StartFrameLen];
      memcpy(pBuffer,buffer,length);
      
      RS485Frame->DataLength  = length;
      RS485Frame->HeadCode    = RS485HeadCode;
      RS485Frame->TargetAddr  = 0x00;
      RS485Frame->SourceAddr  = HCSYS.SwitchAddr;
      RS485Frame->ErrCode     = Err_None;
      
      pBuffer = (unsigned char*)&RS485Frame->CabinetAddr;
      memset(pBuffer,0x00,3);
      if(0<HCSYS.Layer)
      {
        pBuffer[HCSYS.Layer-1]  = HCSYS.SwitchAddr;
      }
      //---------------------------------计算校验
      pBuffer = (unsigned char*)&RS485Frame->TargetAddr;
      pBuffer[RS485Frame->DataLength+RS485StartFrameLen-1]	=	BCC8(pBuffer,RS485Frame->DataLength+RS485StartFrameLen-1);	//头标识符和尾标识符不参与校验
      pBuffer[RS485Frame->DataLength+RS485StartFrameLen]	=	RS485EndCode;	
      SendNode[i].Length  = RS485Frame->DataLength+RS485StartFrameLen+2;
      
      break;
    }
  }
  if(i>=SelfBuffSize)
  {
    return RES_NOTRDY;
  }
  return res;
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
//  RS485FrameDef *RS485Frame  	= NULL;
  unsigned char	*pBuffer		  =	0;
  
  unsigned char i = 0;
  unsigned short	DataLength	=	0;
  
  if(NULL ==  buffer) //空地址
	{
		return 0;
	}
  for(i=0;i<SelfBuffSize;i++)
  {
		DataLength  = ProcessNode[i].Length;
		
    if(0  !=  DataLength)
    {
      pBuffer = ProcessNode[i].data;
      
      memcpy(buffer,pBuffer,DataLength);
      
      ProcessNode[i].Length = 0;
      
      return DataLength;
    }
  }
  return 0;
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
    FrameLength	=	SendNode[i].Length;
		if(0	!=	FrameLength)		//有数据
		{
			memcpy(TransU.data,SendNode[i].data,FrameLength);
			memcpy(buffer,SendNode[i].data,FrameLength);
			TransU.Length	=	FrameLength;
			TransU.Retry.Retry	=	0;
			TransU.Retry.Time		=	0;			
			SendNode[i].Length	=	0;
			return FrameLength;
		}
  }
	//=====================================检查DataNodeU缓存
	for(i	=	0;i<=MaxNetPerLayer;i++)
	{
		FrameLength	=	DataNodeU[i].Length;
		if(0	!=	FrameLength)		//有数据
		{
			memcpy(TransU.data,DataNodeU[i].data,FrameLength);
			memcpy(buffer,DataNodeU[i].data,FrameLength);
			TransU.Length	=	FrameLength;
			TransU.Retry.Retry	=	0;
			TransU.Retry.Time		=	0;			
			DataNodeU[i].Length	=	0;
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
	unsigned char FrameLength	= 0;		//消息帧总长度，从HeadCode到EndCode的字节数
	unsigned char	i	=	0;
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
	//=====================================检查TransU缓存
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
	//=====================================检查DataNodeU缓存
	for(i	=	0;i<=MaxNetPerLayer;i++)
	{
		FrameLength	=	DataNodeD[i].Length;
		if(0	!=	FrameLength)		//有数据
		{
			memcpy(TransD.data,DataNodeD[i].data,FrameLength);
			memcpy(buffer,DataNodeD[i].data,FrameLength);
			TransD.Length	=	FrameLength;
			TransD.Retry.Retry	=	0;
			TransD.Retry.Time		=	0;			
			DataNodeD[i].Length	=	0;
			return FrameLength;
		}
	}
	return FrameLength;
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
HCResult APIRS232UplinkSetData(const unsigned char *buffer,const unsigned short length)
{
	AddrDef		AddrTemp;
	CmdDef		CmdTemp;
	
	RS232FrameDef *RS232Frame 	= NULL;
	RS485FrameDef *RS485Frame 	= NULL;
	unsigned char	*pBuffer			=	0;
	unsigned char	*Head1Addr		=	0;
	unsigned char	*Head2Addr		=	0;
	
	unsigned char		UserCode  	=	0;
	unsigned char		SourceBcc8  =	0;
	unsigned char		TargetAddr	=	0;
  unsigned short	FarmeLen		=	0;
	unsigned short	DataLength	=	0;
	unsigned short 	ValidLength	= 0;    //buffer中有效数据长度(从RS485头标识符开始后的数据为有效数据)
	
  if(NULL ==  buffer) //空地址
	{
		return RES_PARERR;
	}
  //=========================================查找RS485HeadCode头标识符
	pBuffer			=	(unsigned char*)buffer;
	ValidLength	=	length;
	//-----------------------------------------查找头标识(0xFA 0xF5)
	CheckFarm:
	Head1Addr		=	(unsigned char*)memchr(pBuffer,RS232Head1,ValidLength);							//查找RS485HeadCode头标识符
	Head2Addr 	=	(unsigned char*)memchr(pBuffer,RS232Head2,ValidLength);							//查找RS485HeadCode头标识符
	
	if((NULL==Head1Addr)||(NULL==Head2Addr))		//标识未找到或者不完整
	{
		return RES_PARERR;
	}
	if(Head2Addr	!=Head1Addr+1)		//0xFA,0xF5不相邻（0xFA在前,0xF5在后)
	{
		pBuffer	=	&pBuffer[1];				//地址加1，返回继续检查
		goto CheckFarm;
	}
	RS232Frame	=	(RS232FrameDef*)Head1Addr;		//头地址
	ValidLength	=	ValidLength-((unsigned long)RS232Frame-(unsigned long)pBuffer);		//剩余数据长度
	SourceBcc8	=	RS232Frame->Bcc8;
	DataLength	=	RS232Frame->DataLength;
	UserCode		=	RS232Frame->UserCode;
	CmdTemp			=	RS232Frame->Cmd;	
	//=========================================应答帧判断(数据长度为0，校验码为0):如果为应答消息，则把发送缓存标志清除
	if(0	==	DataLength)			//应答类型
	{
		//---------------------------------------校验判断
		if(0!=SourceBcc8)
		{
			pBuffer	=	&pBuffer[1];	//地址加1，返回继续检查
			goto CheckFarm;					//校验不对
		}
		//---------------------------------------应答帧:释放上传缓存
		else
		{
			TransU.Length	=	0;			//清除发送缓存
			pBuffer	=	&pBuffer[1];	//地址加1，返回继续检查剩余数据
			goto CheckFarm;
		}
	}
	//=========================================数据帧
	if(0	!=	DataLength)			//网关板下一级为单元板
	{		
		unsigned char *pTemp		=0;
		unsigned char Bcc8Temp	=0;
		unsigned char i					=0;		
		
		pTemp	=	&RS232Frame->DataLength;
		pTemp	=	&pTemp[1];
		memcpy(&AddrTemp,pTemp,3);
		TargetAddr	=	AddrTemp.CabinetAddr;

		Bcc8Temp	=	BCC8(pTemp,DataLength);
		if(SourceBcc8	!=	Bcc8Temp)
		{
			pBuffer	=	&pBuffer[1];		//地址加1，返回继续检查
			goto CheckFarm;
		}
		//=========================================拷贝相关数据
		//-----------------------------------------本地消息：单元板地址为0
		if((0==AddrTemp.CabinetAddr)&&(DataLength<BusDataSize))
		{
			for(i=0;i<SelfBuffSize;i++)
			{
				if(0	==	ProcessNode[i].Length)
				{
					ProcessNode[i].data[0]	=	CmdTemp;
					ProcessNode[i].data[1]	=	UserCode;
					memcpy(&ProcessNode[i].data[2],pTemp,DataLength);
					ProcessNode[i].Length	=	DataLength+2;
				}
			}
			if(i<SelfBuffSize)
			{
				ACKU.Ack.ErrCode		=	Err_None;
			}
			else
			{
				ACKU.Ack.ErrCode		=	Err_FAULT_BUSY;
			}
		}
		//-----------------------------------------转换为RS485协议包
		else
		{
			unsigned char	*pT	=	NULL;
			for(i=0;i<MaxNetPerLayer;i++)
			{
				if(0	==	DataNodeD[i].Length)
				{
					RS485Frame	=	(RS485FrameDef*)&DataNodeD[i].data[0];
					
					RS485Frame->HeadCode		=	RS485HeadCode;
					RS485Frame->TargetAddr	=	RS232Frame->CabinetAddr;
					RS485Frame->SourceAddr	=	0x00;
					RS485Frame->ErrCode			=	RS232Frame->ErrCode;
					RS485Frame->CabinetAddr	=	RS232Frame->CabinetAddr;
					RS485Frame->LayerAddr		=	RS232Frame->LayerAddr;
					RS485Frame->SlotAddr		=	RS232Frame->SlotAddr;
					RS485Frame->DataLength	=	RS232Frame->DataLength-4+3;
					//---------------获取数据地址
					pTemp	=	(unsigned char*)&RS232Frame->ErrCode;
					pTemp++;
					
					pT	=	&DataNodeD[i].data[RS485StartFrameLen];
					pT[0]	=	RS232Frame->Cmd;
					pT[1]	=	RS232Frame->UserCode;
					pT[2]	=	RS232Frame->Serial;
					
					memcpy(&pT[3],pTemp,RS485Frame->DataLength-3);
					
					pTemp	=	(unsigned char*)&RS485Frame->data[RS485Frame->DataLength+3];
					
					pT[RS485Frame->DataLength]		=	BCC8(&RS485Frame->TargetAddr,RS485StartFrameLen+RS485Frame->DataLength-1);
					pT[RS485Frame->DataLength+1]	=	RS485EndCode;
					DataNodeD[i].Length	=	RS485StartFrameLen+RS485Frame->DataLength+3;
					break;
				}
			}
			if(i<MaxNetPerLayer)
			{
				ACKU.Ack.ErrCode		=	Err_None;
			}
			else
			{
				ACKU.Ack.ErrCode		=	Err_FAULT_BUSY;
			}
		}
	}
	return RES_OK;
}











































