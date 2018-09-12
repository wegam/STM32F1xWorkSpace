

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
		if(SourceBcc8==pBuffer[4])			//应答消息
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
						memcpy(ProcessNode[i].data,RS485Frame,RS485Frame->DataLength+RS485StartFrameLen+2);	//将源数据全部拷贝
						ProcessNode[i].Length	=	RS485Frame->DataLength+RS485StartFrameLen+2;
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
			
			Addr	=	&RS485Frame->CabinetAddr;
//			SourceAddr	=	Addr[HCSYS.Layer];
			SourceAddr	=	RS485Frame->SourceAddr;
			//---------------------------------------中间级
			if(HCSYS.Layer>0)		//非最终端设备--最顶层
			{
//				SourceAddr	=	Addr[HCSYS.Layer];

				if(DataNodeU[SourceAddr].Length)
				{
					ACKD.Ack.ErrCode		=	Err_FAULT_BUSY;
				}
				else
				{
					memcpy(DataNodeU[SourceAddr].data,RS485Frame,RS485Frame->DataLength+RS485StartFrameLen);
					DataNodeU[SourceAddr].Length	=	RS485Frame->DataLength+RS485StartFrameLen+2;
					RS485Frame	=	(RS485FrameDef*)DataNodeU[SourceAddr].data;
					pTemp	=	(unsigned char*)DataNodeU[SourceAddr].data;
					//------------------------修改目的地址和源地址
					RS485Frame->TargetAddr	=	0x00;
					RS485Frame->SourceAddr	=	HCSYS.SwitchAddr;
					Addr[HCSYS.Layer]				=	HCSYS.SwitchAddr;
					//------------------------校验
					pTemp[RS485Frame->DataLength+RS485StartFrameLen]	=	BCC8(&pTemp[1],RS485Frame->DataLength+RS485StartFrameLen-1);	//头标识符和尾标识符不参与校验
					pTemp[RS485Frame->DataLength+RS485StartFrameLen+1]	=	RS485EndCode;
					ACKD.Ack.ErrCode		=	Err_None;
				}						
			}
			//---------------------------------------终端级--最顶层：转485
			else
			{	

			}			
			ACKD.Ack.HeadCode		=	RS485HeadCode;
			ACKD.Ack.TargetAddr	=	0;
			ACKD.Ack.SourceAddr	=	HCSYS.SwitchAddr;
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
      pBuffer     = (unsigned char*)RS485Frame->data;
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
      pBuffer[RS485Frame->DataLength+RS485StartFrameLen]	=	BCC8(pBuffer,RS485Frame->DataLength+RS485StartFrameLen-1);	//头标识符和尾标识符不参与校验
      
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
  RS485FrameDef *RS485Frame  	= NULL;
  unsigned char	*pBuffer		  =	0;
  
  unsigned char i = 0;
  unsigned short	DataLength	=	0;
  
  if(NULL ==  buffer) //空地址
	{
		return 0;
	}
  for(i=0;i<SelfBuffSize;i++)
  {
    if(0  !=  ProcessNode[i].Length)
    {
      RS485Frame  = (RS485FrameDef*)ProcessNode[i].data;
      
      DataLength  = RS485Frame->DataLength;
      
      pBuffer = RS485Frame->data;
      
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








































///*******************************************************************************
//* 函数名			:	function
//* 功能描述		:	函数功能说明 
//* 输入			: void
//* 返回值			: void
//* 修改时间		: 无
//* 修改内容		: 无
//* 其它			: wegam@sina.com
//*******************************************************************************/
//unsigned char FarmeCheck(const void *buffer,const unsigned short length)
//{
//	RS485FrameDef *RS485Frame  	= NULL;
//	RS232FrameDef *RS232Frame 	= NULL;
//	RS485Frame	=	RS485Step1FarmeDataCheck(buffer,length);
//	RS232Frame	=	RS232Step1FindData(buffer,length);
//	if(NULL	!=	RS485Frame)	//非RS485
//	{
//		return 1;
//	}
//	else if(NULL	!=	RS232Frame)
//	{
//		return 2;
//	}
//	return 0;
//}
/*******************************************************************************
* 函数名			:	function
* 功能描述		:	函数功能说明 
* 输入			: buffer  输入的数据缓存地址
              length  输入的数据长度
              UDflag  1-上层输入的数据
                      2-下层输入的数据
* 返回值			: 0 不需要继续处理
              1 RS485数据
              2 RS232数据
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
unsigned char FarmeCheck(const void *buffer,const unsigned short length)
{
	RS485FrameDef *RS485Frame  	= NULL;
	RS232FrameDef *RS232Frame 	= NULL;
	
	unsigned long	*RS485HeadCodeAddr	= NULL;
	unsigned long	*RS485EndCodeAddr		= NULL;
	unsigned char	*pBuffer						=	0;
	
//  unsigned short bass				=	0;
	unsigned char SourceBcc8  = 0;
  if(NULL ==  buffer) //空地址
	{
		return 0;
	}
  //=========================================RS485格式判断
  RS485HeadCodeAddr =	(unsigned long*)memchr(buffer,RS485HeadCode,length);	//查找RS485HeadCode头标识符
	RS485EndCodeAddr	=	(unsigned long*)memchr(RS485HeadCodeAddr,RS485EndCode,length);	//查找RS485HeadCode头标识符
  if(NULL != RS485Frame)    //查找到0x7E
  {
		//=======================================长度判断
		if(RS232AckFrameLen==RS485EndCodeAddr	-	RS485HeadCodeAddr)
		{
			pBuffer=(unsigned char*)RS485HeadCodeAddr;
			SourceBcc8	=	BCC8(&pBuffer[1],3);
			if(SourceBcc8	==	pBuffer[4])		//应答消息
			{
			}
		}
		if(RS485Frame->TargetAddr ==  HCSYS.SwitchAddr)
		{
		}
  }
  //=========================================RS232格式判断
  
	RS485Frame	=	RS485Step1FarmeDataCheck(buffer,length);
	RS232Frame	=	RS232Step1FindData(buffer,length);
	if(NULL	!=	RS485Frame)	//非RS485
	{
		return 1;
	}
	else if(NULL	!=	RS232Frame)
	{
		return 2;
	}
	return 0;
}
/*******************************************************************************
*函数名			:	FindRS485Data
*功能描述		:	查找RS485数据在buffer中的起始地址并校验数据
*输入			: 
*返回值			:	NULL  未找到
					Addr  找到的起始地址
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
RS485FrameDef* RS485Step1FarmeDataCheck(const void *buffer,const unsigned short length)
{
	RS485FrameDef *RS485Frame  		    = NULL;
//	unsigned long *TargetDataAddr	= NULL;
//	unsigned long	*SourceDataAddr	= NULL;
//	unsigned char	*Bcc8DataAddr	  = NULL;   //校验位地址
//	unsigned char	*EndCodeAddr	  = NULL;   //结束符地址
	unsigned char *p							=	NULL;
 
	unsigned char TargetAddr	= 0;		//目标地址：上层下发，目标地址为本地址，源地址无效，下层上发，目标地址必须为0，源地址为发送地址,如果地址为0xFF表示为广播地址
	unsigned char SourceAddr	= 0;		//源地址：上层下发，目标地址为本地址，源地址无效，下层上发，目标地址必须为0，源地址为发送地址
	unsigned char	DataLength	= 0;		//消息内数据长度：包含地址位
  unsigned char FrameLength	= 0;		//消息帧总长度，从HeadCode到EndCode的字节数	
	unsigned char ValidLength	= 0;    //buffer中有效数据长度(从RS485头标识符开始后的数据为有效数据)
  unsigned char SourceBcc8  = 0;
	unsigned char SourceEndCode  = 0;
	unsigned char Bcc8      	= 0;    //异或校验
	unsigned char bass				=	0;
	
//	unsigned char NetLayer	  = 0;    //本板所在层级：0-网关层，1-单元板层CabinetAddr，2-层控制板层LayerAddr，3,-驱动层SlotAddr，数据来源为HCSYS.Layer
//	ErrCodeDef    ErrCode 	  = Err_None; //状态码/错误码

	if(NULL ==  buffer) //空地址
	{
		return NULL;
	}
	//=====================================最短帧长度要求
	RS485Frame =	(RS485FrameDef*)memchr(buffer,RS485HeadCode,length);		          //查找RS485Head1头标识符
	if(NULL ==  RS485Frame)
	{
		return NULL;      //未长度头标识符，退出
	}
  //=====================================

	bass   = (unsigned char)((unsigned long)RS485Frame-(unsigned long)buffer);  //获取起始帧头与缓存地址的偏差值
	ValidLength   = length-bass;     //去除前面无效数据	
  
	//-------------------------------------有效数据长度判断
	if(RS485MinFrameLen>ValidLength) 
	{
		return NULL;      //数据长度错误，退出
	}
	//-------------------------------------数据长度与buffer长度判断：最短帧长度+数据长度为有效长度+1字节校验位和1字节结束符
  FrameLength	  = DataLength+RS485StartFrameLen+1;	//1为结束符字节	
	if(FrameLength>ValidLength)
	{
		return NULL;      //数据个数+基本数据个数大于有效数据个数，退出
	}
	TargetAddr	=	RS485Frame->TargetAddr;
	SourceAddr	=	RS485Frame->SourceAddr;
	//=====================================地址校验
	if((0x00==TargetAddr)&&(0x00==SourceAddr))
	{
		return NULL;	//无地址数据，退出
	}
	//-------------------------------------上层下发时地址校验:上层下发时目标地址为本地址，源地址无效，广播地址为0xFF;下层上传时目标地址必须为0
	if((0x00!=TargetAddr)&&(!((0xFF==TargetAddr)||(HCSYS.SwitchAddr==TargetAddr))))
	{
		return NULL;	//非本板数据，退出
	}
	if(RS485Frame->DataLength>0)
	{
//		RS485Frame->data	=	(unsigned char*)(&(RS485Frame->DataLength)+(unsigned char)1);
//		RS485Frame->data	=	&DataNodeD[CabinetAddr].data[12]
//		RS485Frame->data	=	&(((unsigned char*)RS485Frame)[12]);
	}
	//=====================================数据校验BCC8：异或校验--计算长度为数据长度+地址前面部分长度包含DataLength字节
	SourceBcc8	=	*p;
	p	=	(unsigned char*)&RS485Frame->TargetAddr;
	Bcc8  = BCC8(p,RS485StartFrameLen+RS485Frame->DataLength-2);		//去年前两个字节（头标识和BCC8）
	if( Bcc8  !=  SourceBcc8)
	{
		return NULL;
	}
	//=====================================查找结束符(0x7F)
	SourceEndCode	=	(unsigned char)(((unsigned char*)RS485Frame)[RS485StartFrameLen+RS485Frame->DataLength]);
	if(RS485EndCode !=  SourceEndCode)
	{
		return NULL;
	}
		return  RS485Frame;
}
 /*******************************************************************************
*函数名			:	RS485AckProcess
*功能描述		:	function
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
HCResult RS485Step2AckProcess(const void *buffer,const unsigned short length)
{
  HCResult	res	=	RES_OK;

	RS485FrameDef *RS485Frame  	  = NULL;
//  AddrDef       *NetLayerAddr	  = NULL;   //地址域指针:Frame->Start.DataLength下一地址
  RS485AckDef	*ACK            = NULL;
//	unsigned long *TargetDataAddr	= NULL;
//	unsigned long	*SourceDataAddr	= NULL;  
//	unsigned long	*Bcc8DataAddr	  = NULL;   //校验位地址
//	unsigned long	*EndCodeAddr	  = NULL;   //结束符地址
  

	unsigned char TargetAddr	= 0;		//目标地址：上层下发，目标地址为本地址，源地址无效，下层上发，目标地址必须为0，源地址为发送地址,如果地址为0xFF表示为广播地址
	unsigned char SourceAddr	= 0;		//源地址：上层下发，目标地址为本地址，源地址无效，下层上发，目标地址必须为0，源地址为发送地址
  unsigned char SubAddr     = 0;    //获取下一级地址在地址域里的偏移
//	unsigned char	DataLength	= 0;		//消息内数据长度：包含地址位
//	unsigned char FrameLength	= 0;		//消息帧总长度，从HeadCode到EndCode的字节数
//	unsigned char ValidLength	= 0;    //buffer中有效数据长度(从RS485头标识符开始后的数据为有效数据)	
	unsigned char NetLayer	  = 0;    //本板所在层级：0-网关层，1-单元板层CabinetAddr，2-层控制板层LayerAddr，3,-驱动层SlotAddr，数据来源为HCSYS.Layer
//  unsigned char Bcc8      	= 0;    //异或校验
  
//	ErrCodeDef    ErrCode 	  = Err_None; //状态码/错误码
  
  RS485Frame = RS485Step1FarmeDataCheck(buffer,length); //查找RS485数据在buffer中的起始地址并校验数据
	if(NULL ==  RS485Frame)  //消息帧不符合
	{
		return RES_PARERR;
	}
  NetLayer    = HCSYS.Layer;
//  TargetAddr  = Frame->Start.TargetAddr;
//  SourceAddr  = Frame->Start.SourceAddr;
//  DataLength  = Frame->Start.DataLength;
//  FrameLength = DataLength+RS485StartFrameLen+2;	//2为校验位和结束符
  //=====================================广播消息：不应答
  if(0xFF ==  RS485Frame->TargetAddr)   //0xFF广播不应答
  {
    return  RES_OK;
  }
  //=====================================检查状态位确认此消息是否为应答消息
//  if((CMD_ACK==Frame->Start.Cmd)&&(RS485AckFrameLen==FrameLength))
	if((RS485AckFrameLen== RS485Frame->DataLength+RS485StartFrameLen+1))
  {
		if(0	==	NetLayer)			//网关板
		{
			if(0	==	TargetAddr)	//下级应答
			{
				if(Err_None==RS485Frame->ErrCode) //无错误
					TransD.Length = 0;
			}
			else
			{
				if(Err_None==RS485Frame->ErrCode) //无错误
					TransU.Length = 0;
			}
		}
    //-------------------------------------上层对下应答:清除上传缓存
    else if(TargetAddr  ==  HCSYS.SwitchAddr)
    {
      if(Err_None==RS485Frame->ErrCode) //无错误
        TransU.Length = 0;
    }
    //-------------------------------------下层对上应答:清除下发缓存
    else
    {
      if(Err_None==RS485Frame->ErrCode) //无错误
        TransD.Length = 0;       
    }
    return RES_ACKMSG;
  }
  //=====================================非应答消息--创建应答消息：表示为数据或者命令传输消息，需要应答
	switch(HCSYS.Layer)
	{
		case 0:SubAddr	=	RS485Frame->CabinetAddr;
			break;
		case 1:SubAddr	=	RS485Frame->LayerAddr;
			break;
		case 2:SubAddr	=	RS485Frame->SlotAddr;
			break;
		case 3:
			break;
		default:break;
	}
 
  //-------------------------------------上层对下发送消息:检查相应下发缓冲区(DataNodeD)是否为空，非空应答忙
  if(HCSYS.SwitchAddr	==	RS485Frame->TargetAddr)   
  {
		unsigned char i	=	0;
		ACK =  (RS485AckDef*)&ACKU.Ack;
		if(0	==	SubAddr)		//本层
		{
			ACK->ErrCode    = Err_FAULT_BUSY;
			res  = RES_NOTRDY;
			for(i=0;i<SelfBuffSize;i++)
			{
				if(0	==	ProcessNode[i].Length)
				{
					ACK->ErrCode    = Err_None;
					res  = RES_OK;
					break;
				}
			}
		}
		else
		{
			if(DataNodeD[SubAddr].Length)     //当前下发缓存位有数据
			{       
				ACK->ErrCode     = Err_FAULT_BUSY;           //忙状态
				res  = RES_NOTRDY;
			}
			else
			{
				ACK->ErrCode    = Err_None;
				res  = RES_OK;
			}
		}		
		ACK->TargetAddr   = 0x00;
		ACK->SourceAddr   = HCSYS.SwitchAddr;
  }
  //-------------------------------------下层对上发送消息:检查相应下发缓冲区(DataNodeU)是否为空，非空应答忙
  else if(TargetAddr ==  0x00)        //上传消息
  {
    ACK =  (RS485AckDef*)&ACKD.Ack;
     if(DataNodeU[SourceAddr].Length)       //当前上传缓存位有数据
     {
       ACK->ErrCode    = Err_FAULT_BUSY;
       res  = RES_NOTRDY;
     }
     else
     {       
       ACK->ErrCode    = Err_None;        
       res  = RES_OK;
     }    
    ACK->TargetAddr = RS485Frame->SourceAddr;
    ACK->SourceAddr = 0x00;           
  }
  ACK->HeadCode    	= RS485HeadCode;
//  ACK->Serial      	= RS485Frame->Serial+1;
//  ACK->Cmd        	= CMD_ACK;
//  ACK->UserCode  		= RS485Frame->UserCode;
//  ACK->DataLength 	= 0;
//  ACK->Bcc8       	= BCC8((unsigned char*)&ACK->TargetAddr,7);
//	ACK->CabinetAddr	=	RS485EndCode;
//  ACKU.FarmeLength  = RS485AckFrameLen;  
  return res;
}
/*******************************************************************************
* 函数名			:	RS485SaveData
* 功能描述		:	保存数据，根据源地址或者目的地址区分数据应该保存在上传缓冲区还是下发缓冲区
              如果下一级地址为0，表示此条消息针对本板使用，保存在本地缓存(SelfNode)待处理
              如果是上层下发到下层的消息，将目的地址修改为下层地址，源地址为0
              如果是下层上传到上层的消息，将源地址修改为本地地址，并将本地地址添加到地址域的相应位置
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
HCResult RS485Step3SaveData(const void *buffer,const unsigned short length)
{
	HCResult	res	=	RES_OK;

	RS485FrameDef *RceFrame  		  = NULL;
  AddrDef       *NetLayerAddr	  = NULL;   //地址域指针:Frame->Start.DataLength下一地址
  DataNodeDef	  *DataNode       = NULL;
//	unsigned long *TargetDataAddr	= NULL;
//	unsigned long	*SourceDataAddr	= NULL;
//	unsigned char	*Bcc8DataAddr	  = NULL;   //校验位地址:数据地址后为校验位地址
//	unsigned char *p							=	NULL;

//	unsigned long	*EndCodeAddr	  = NULL;   //结束符地址
  

	unsigned char TargetAddr	= 0;		//目标地址：上层下发，目标地址为本地址，源地址无效，下层上发，目标地址必须为0，源地址为发送地址,如果地址为0xFF表示为广播地址
//	unsigned char SourceAddr	= 0;		//源地址：上层下发，目标地址为本地址，源地址无效，下层上发，目标地址必须为0，源地址为发送地址
	unsigned char	DataLength	= 0;		//消息内数据长度：包含地址位
	unsigned char FrameLength	= 0;		//消息帧总长度，从HeadCode到EndCode的字节数
//	unsigned char ValidLength	= 0;    //buffer中有效数据长度(从RS485头标识符开始后的数据为有效数据)
//	unsigned char Bcc8      	= 0;    //异或校验
	unsigned char NetLayer	  = 0;    //本板所在层级：0-网关层，1-单元板层CabinetAddr，2-层控制板层LayerAddr，3,-驱动层SlotAddr，数据来源为HCSYS.Layer
//	ErrCodeDef    ErrCode 	  = Err_None; //状态码/错误码

  //=====================================
	RceFrame = RS485Step1FarmeDataCheck(buffer,length); //查找RS485数据在buffer中的起始地址并校验数据
	if(NULL ==  RceFrame)  //消息帧不符合
	{
		return RES_PARERR;
	}
  //=====================================相关数据准备
  TargetAddr  = RceFrame->TargetAddr;
//  ErrCode     = RceFrame->ErrCode;
  DataLength  = RceFrame->DataLength;
  FrameLength = RS485StartFrameLen+DataLength+2;
	
  NetLayer    = HCSYS.Layer;  
  NetLayerAddr  = (AddrDef*)((&RceFrame->DataLength)+1); //获取地址域起始坐标，Frame->Start.DataLength下一地址
  
  //=====================================上层下发消息：根据目标地址是否为本地址或者为广播地址，如果目标地址为0，则为下层往上发
  //-------------------------------------上层下发消息：地址为本地址或者为广播地址0xFF
  if((TargetAddr == HCSYS.SwitchAddr)||(TargetAddr == 0xFF))     //上层下发消息
  {
    //---------------------将数据放入相应数组缓冲区
    unsigned char SubAddr   = ((unsigned char*)NetLayerAddr)[NetLayer];  //获取下一级地址在地址域里的偏移
    RS485FrameDef *NewFrame = NULL;
		//---------------------如果是结点最后层或者此消息为本层消息，则将消息保存在待处理缓冲区
		if((3==NetLayer)||(0==SubAddr))
		{
			unsigned char i = 0;
      for(i=0;i<SelfBuffSize;i++)
      {
        DataNode  =  &ProcessNode[i];
        if(0  ==  DataNode->Length) //缓存空
        {
          NewFrame  = (RS485FrameDef*)DataNode->data;
          memcpy(NewFrame,RceFrame,FrameLength);    //复制数据
          DataNode->Length  = FrameLength;
          return RES_OK;      //找到空位，保存完数据后退出保存函数
        }
      }
		}
    //---------------------此消息需要转发到下一层
    else if(0x00 != SubAddr)         //下一地址不为0表示此消息不属于本层，需要转发
    {
      if(0xFF ==  TargetAddr)   //广播消息:数组0存储广播消息
      {
        DataNode  =  &DataNodeD[0];
      }
      else
      {
        DataNode  =  &DataNodeD[SubAddr];
      }
      NewFrame  = (RS485FrameDef*)DataNode->data;
      memcpy(NewFrame,RceFrame,FrameLength);    //复制数据
      
      NewFrame->TargetAddr	= SubAddr;
      NewFrame->SourceAddr	= 0x00;       //下发时，源地址必须为0 
//      NewFrame->Serial    	= ++SerialD;
//			NewFrame->Bcc8				=	0xF8;
			
//      p	=	(unsigned char*)&NewFrame->TargetAddr;
//			NewFrame->Bcc8				= BCC8(p,RS485StartFrameLen+RceFrame->DataLength-2);
      DataNode->Length  = RS485StartFrameLen+RceFrame->DataLength+1;		//1字节结束符
      
      return RES_OK;      //找到空位，保存完数据后退出保存函数
    }
    //---------------------此消息为本层消息
  }
  //=====================================上传消息
  else
  {
  }
	return res;
}
/*******************************************************************************
* 函数名			:	RS485ToRS485
* 功能描述		:	RS485转RS485 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
HCResult RS485ToRS485(const void *buffer,const unsigned short length)
{
	HCResult	res	=	RES_OK;

	RS485FrameDef *Frame  		    = NULL;
//	unsigned long *TargetDataAddr	= NULL;
//	unsigned long	*SourceDataAddr	= NULL;
//	unsigned long	*Bcc8DataAddr	  = NULL;   //校验位地址
//	unsigned long	*EndCodeAddr	  = NULL;   //结束符地址

//	unsigned char TargetAddr	= 0;		//目标地址：上层下发，目标地址为本地址，源地址无效，下层上发，目标地址必须为0，源地址为发送地址,如果地址为0xFF表示为广播地址
//	unsigned char SourceAddr	= 0;		//源地址：上层下发，目标地址为本地址，源地址无效，下层上发，目标地址必须为0，源地址为发送地址
//	unsigned char	DataLength	= 0;		//消息内数据长度：包含地址位
//	unsigned char FrameLength	= 0;		//消息帧总长度，从HeadCode到EndCode的字节数
//	unsigned char ValidLength	= 0;    //buffer中有效数据长度(从RS485头标识符开始后的数据为有效数据)
//	unsigned char Bcc8      	= 0;    //异或校验
//	unsigned char NetLayer	  = 0;    //本板所在层级：0-网关层，1-单元板层CabinetAddr，2-层控制板层LayerAddr，3,-驱动层SlotAddr，数据来源为HCSYS.Layer
//	ErrCodeDef    ErrCode 	  = Err_None; //状态码/错误码

  //=====================================
	Frame = RS485Step1FarmeDataCheck(buffer,length); //查找RS485数据在buffer中的起始地址并校验数据
	if(NULL ==  Frame)  //消息帧不符合
	{
		return RES_PARERR;
	}
  
  //=====================================
  res = RS485Step2AckProcess(Frame,length);
  if(RES_OK != res)
  {
    return res;
  }
  
	//=====================================保存数据
  res = RS485Step3SaveData(Frame,length);
  if(RES_OK != res)
  {
    return res;
  }
	//-------------------------------------上层下发消息
	return res;
}
/*******************************************************************************
*函数名			:	FindRS485Data
*功能描述		:	查找RS485数据在buffer中的起始地址并校验数据
*输入			: 
*返回值			:	NULL  未找到
					Addr  找到的起始地址
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
RS232FrameDef* RS232Step1FindData(const void *buffer,const unsigned short length)
{
	RS232FrameDef *RceFrame  		    = NULL;
	RS232FrameDef *Frame2  		    = NULL;
//	unsigned long *TargetDataAddr	= NULL;
//	unsigned long	*SourceDataAddr	= NULL;
	unsigned long	*Bcc8DataAddr	  = NULL;   //校验位地址
//	unsigned long	*EndCodeAddr	  = NULL;   //结束符地址

//	unsigned char TargetAddr	= 0;		//目标地址：上层下发，目标地址为本地址，源地址无效，下层上发，目标地址必须为0，源地址为发送地址,如果地址为0xFF表示为广播地址
//	unsigned char SourceAddr	= 0;		//源地址：上层下发，目标地址为本地址，源地址无效，下层上发，目标地址必须为0，源地址为发送地址
	unsigned char	DataLength	= 0;		//消息内数据长度：包含地址位
	unsigned char FrameLength	= 0;		//消息帧总长度，从HeadCode到EndCode的字节数
	unsigned char ValidLength	= 0;    //buffer中有效数据长度(从RS485头标识符开始后的数据为有效数据)
	unsigned char Bcc8      	= 0;    //异或校验
//	unsigned char NetLayer	  = 0;    //本板所在层级：0-网关层，1-单元板层CabinetAddr，2-层控制板层LayerAddr，3,-驱动层SlotAddr，数据来源为HCSYS.Layer
//	ErrCodeDef    ErrCode 	  = Err_None; //状态码/错误码

	if(NULL ==  buffer) //空地址
	{
		return NULL;
	}
	//=====================================最短帧长度要求
	RceFrame 	=	(RS232FrameDef*)memchr(buffer,RS232Head1,length);		          //查找RS485Head1头标识符
	Frame2 		=	(RS232FrameDef*)memchr(buffer,RS232Head2,length);		          //查找RS485Head1头标识符
	if(1 !=  ((unsigned long)Frame2-	(unsigned long)RceFrame))
	{
		return NULL;      //未长度头标识符，退出
	}
	ValidLength = (unsigned char)((unsigned long)RceFrame-(unsigned long)buffer);  //获取起始帧头与缓存地址的偏差值
	ValidLength = length-ValidLength;     //去除前面无效数据	
	//-------------------------------------有效数据长度判断
	if(RS232MinFrameLen>ValidLength) 
	{
		return NULL;      //数据长度错误，退出
	}
	//-------------------------------------数据长度与buffer长度判断：最短帧长度+数据长度为有效长度
	DataLength  = RceFrame->DataLength;
	FrameLength	= DataLength+RS232StartFrameLen;	//2为校验位和结束符
	if(FrameLength>ValidLength)
	{
		return NULL;      //数据个数+基本数据个数大于有效数据个数，退出
	}
	//=====================================数据校验BCC8：异或校验--计算长度为数据长度+地址前面部分长度包含DataLength字节
	if((0==DataLength)&&(0==RceFrame->Bcc8))
	{
		return  RceFrame;
	}
//	Bcc8DataAddr  = (unsigned long*)((unsigned long)RceFrame+RS232MinFrameLen);     //BCC8开始校验起始地址段
	Bcc8DataAddr  = (unsigned long*)&RceFrame->DataLength;     //BCC8开始校验起始地址段
	Bcc8DataAddr	=	(unsigned long*)((unsigned long)Bcc8DataAddr+1);
	Bcc8  = BCC8((unsigned char*)Bcc8DataAddr,DataLength);
	if( Bcc8  !=  RceFrame->Bcc8)
	{
		return NULL;
	}
		return  RceFrame;
}
/*******************************************************************************
*函数名			:	RS485AckProcess
*功能描述		:	function
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
HCResult RS232Step2AckProcess(const void *buffer,const unsigned short length)
{
  HCResult	res	=	RES_OK;

	RS232FrameDef *RS232Frame  		= NULL;
	RS232FrameDef	*RS232ACK     	= NULL;
//	AddrDef				*Addr						=	NULL;	//地址段起始地址
	
//	unsigned char*	p	=	NULL;

	unsigned char TargetAddr	= 0;		//目标地址：上层下发，目标地址为本地址，源地址无效，下层上发，目标地址必须为0，源地址为发送地址,如果地址为0xFF表示为广播地址
  
  RS232Frame = RS232Step1FindData(buffer,length); //查找RS485数据在buffer中的起始地址并校验数据
	if(NULL ==  RS232Frame)  //消息帧不符合
	{
		return RES_PARERR;
	}
	//=====================================检查状态位确认此消息是否为应答消息
  if((RS232AckFrameLen==length)&&(0==RS232Frame->DataLength))
  {
		TransU.Length = 0;
    return RES_ACKMSG;
  }
//	p	=	(unsigned char*)((unsigned long)RS232Frame+(unsigned long)11);
//	RS232Frame->data	=p;
//	RS232Frame->data	=(unsigned char*)((unsigned long)RS232Frame+(unsigned long)11);	
  //=====================================非应答消息--创建应答消息：表示为数据或者命令传输消息，需要应答
	TargetAddr	=	RS232Frame->CabinetAddr;			//单元板地址
  //-------------------------------------广播消息：存储在DataNodeD[0]
  if(0xFF ==  TargetAddr)   //0xFF广播不应答
  {
		return RES_OK;
  }
	//-------------------------------------检查相应缓存是否为空:空则应答，非空则不应答
	if(0==DataNodeD[TargetAddr].Length)		//非空
	{
		RS232ACK	=	(RS232FrameDef*)&(ACKU.Ack);
		memcpy(RS232ACK,RS232Frame,RS232AckFrameLen);
		RS232ACK->Bcc8					=	0;
		RS232ACK->DataLength		=	0;
		ACKU.FarmeLength	=	RS232AckFrameLen;
		res	=	RES_OK;
	}
	else
	{
		res  = RES_NOTRDY;
	}
  return res;
}
/*******************************************************************************
* 函数名			:	RS485SaveData
* 功能描述		:	保存数据，根据源地址或者目的地址区分数据应该保存在上传缓冲区还是下发缓冲区
              如果下一级地址为0，表示此条消息针对本板使用，保存在本地缓存(SelfNode)待处理
              如果是上层下发到下层的消息，将目的地址修改为下层地址，源地址为0
              如果是下层上传到上层的消息，将源地址修改为本地地址，并将本地地址添加到地址域的相应位置
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
HCResult RS232Step3SaveData(const void *buffer,const unsigned short length)
{
//	HCResult	res	=	RES_OK;
	
	RS232FrameDef	*RS232Frame  		= NULL;
	RS485FrameDef	*RS485Frame  		= NULL;

//	AddrDef				*SourceAddr			=	NULL;	//地址段起始地址
//	AddrDef				*TargetAddr			=	NULL;	//地址段起始地址	
//  DataNodeDef	  *DataNode       = NULL;
	
//	unsigned long	*SourceDataAddr	=	NULL;	//数据段起始地址
//	unsigned long	*TargetDataAddr	=	NULL;	//数据段起始地址
//	unsigned long	*Bcc8DataAddr	  = NULL;   //校验位地址:数据地址后为校验位地址
//	unsigned long	*EndCodeAddr	  = NULL;   //结束符地址
  

	unsigned char CabinetAddr	= 0;		//目标地址：上层下发，目标地址为本地址，源地址无效，下层上发，目标地址必须为0，源地址为发送地址,如果地址为0xFF表示为广播地址
//	unsigned char SourceAddr	= 0;		//源地址：上层下发，目标地址为本地址，源地址无效，下层上发，目标地址必须为0，源地址为发送地址
//	unsigned char	DataLengthS	= 0;		//源消息内数据长度：不包含地址位
//	unsigned char RS485FrameLength	= 0;		//消息帧总长度，从HeadCode到EndCode的字节数
//	unsigned char ValidLength	= 0;    //buffer中有效数据长度(从RS485头标识符开始后的数据为有效数据)
//	unsigned char Bcc8      	= 0;    //异或校验
//	unsigned char NetLayer	  = 0;    //本板所在层级：0-网关层，1-单元板层CabinetAddr，2-层控制板层LayerAddr，3,-驱动层SlotAddr，数据来源为HCSYS.Layer
//	ErrCodeDef    ErrCode 	  = Err_None; //状态码/错误码

  //=====================================
	RS232Frame = RS232Step1FindData(buffer,length); //查找RS485数据在buffer中的起始地址并校验数据
	if(NULL ==  RS232Frame)  //消息帧不符合
	{
		return RES_PARERR;
	}
  //=====================================相关数据准备	
	CabinetAddr	=	RS232Frame->CabinetAddr;	
	
	if(0xFF	==	CabinetAddr)	//广播消息
	{
		CabinetAddr	=	0;
	}	
	RS485Frame	=	(RS485FrameDef*)(DataNodeD[CabinetAddr].data);	
	RS485Frame->HeadCode	=	RS485HeadCode;
	RS485Frame->TargetAddr	=	CabinetAddr;
	RS485Frame->SourceAddr	=	0x00;
	RS485Frame->ErrCode			=	RS232Frame->ErrCode;
	RS485Frame->DataLength	=	RS232Frame->DataLength-1;		//去掉ErrCode
	RS485Frame->CabinetAddr	=	RS232Frame->CabinetAddr;
	RS485Frame->LayerAddr		=	RS232Frame->LayerAddr;
	RS485Frame->SlotAddr		=	RS232Frame->SlotAddr;
	
//	RS485Frame->data				=	&DataNodeD[CabinetAddr].data[12];
//	RS232Frame->data				=	(unsigned char*)((unsigned long)RS232Frame+11);
	memcpy(&DataNodeD[CabinetAddr].data[12],&(((unsigned char*)RS232Frame)[11]),RS485Frame->DataLength-3);
	
//	RS485Frame->Bcc8				=	BCC8(&RS485Frame->TargetAddr,RS485Frame->DataLength+7);
	
	DataNodeD[CabinetAddr].data[RS485Frame->DataLength+9]	=	RS485EndCode;			//结束符
	
	DataNodeD[CabinetAddr].Length	=	RS485Frame->DataLength+7+3;			//帧长度
	return RES_OK;
}
/*******************************************************************************
* 函数名			:	RS485ToRS485
* 功能描述		:	RS485转RS485 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
HCResult RS232ToRS485(const void *buffer,const unsigned short length)
{
	HCResult	res	=	RES_OK;

	RS232FrameDef *Frame  		    = NULL;
//	unsigned long *TargetDataAddr	= NULL;
//	unsigned long	*SourceDataAddr	= NULL;
//	unsigned long	*Bcc8DataAddr	  = NULL;   //校验位地址
//	unsigned long	*EndCodeAddr	  = NULL;   //结束符地址

//	unsigned char TargetAddr	= 0;		//目标地址：上层下发，目标地址为本地址，源地址无效，下层上发，目标地址必须为0，源地址为发送地址,如果地址为0xFF表示为广播地址
//	unsigned char SourceAddr	= 0;		//源地址：上层下发，目标地址为本地址，源地址无效，下层上发，目标地址必须为0，源地址为发送地址
//	unsigned char	DataLength	= 0;		//消息内数据长度：包含地址位
//	unsigned char FrameLength	= 0;		//消息帧总长度，从HeadCode到EndCode的字节数
//	unsigned char ValidLength	= 0;    //buffer中有效数据长度(从RS485头标识符开始后的数据为有效数据)
//	unsigned char Bcc8      	= 0;    //异或校验
//	unsigned char NetLayer	  = 0;    //本板所在层级：0-网关层，1-单元板层CabinetAddr，2-层控制板层LayerAddr，3,-驱动层SlotAddr，数据来源为HCSYS.Layer
//	ErrCodeDef    ErrCode 	  = Err_None; //状态码/错误码

  //=====================================
	Frame = RS232Step1FindData(buffer,length); //查找RS485数据在buffer中的起始地址并校验数据
	if(NULL ==  Frame)  //消息帧不符合
	{
		return RES_PARERR;
	}
  
  //=====================================
  res = RS232Step2AckProcess(buffer,length);
  if(RES_OK != res)
  {
    return res;
  }
  
	//=====================================保存数据
  res = RS232Step3SaveData(buffer,length);
  if(RES_OK != res)
  {
    return res;
  }
	//-------------------------------------上层下发消息
	return res;
}


/*******************************************************************************
*函数名			:	function
*功能描述		:	function
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
HCResult GetSubOnlineAddr(void)
{

	return RES_OK;
}











