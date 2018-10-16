

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
//	HCResult	res	=	RES_OK;
	
	RS485FrameDef *RS485Frame  				= NULL;
	AddrDef				*Addr								=	NULL;
	unsigned long	*RS485EndCodeAddr		= NULL;
	unsigned char	*pBuffer						=	0;
	
	unsigned char		TargetAddr	=	0;
	unsigned char		SourceBcc8  = 0;
  unsigned short	FarmeLen		=	0;
	
	unsigned short 	ValidLength	= 0;    //buffer中有效数据长度(从RS485头标识符开始后的数据为有效数据)
	
  if(NULL ==  buffer) //空地址
	{
		return RES_PARERR;
	}
  //=========================================数据有效性检查：
	pBuffer			=	(unsigned char*)buffer;
	ValidLength	=	length;
	//-----------------------------------------查找头标识和结束标识
	CheckFarm:
	RS485Frame 				=	(RS485FrameDef*)memchr(pBuffer,RS485HeadCode,ValidLength);		//查找RS485HeadCode头标识符
	RS485EndCodeAddr	=	(unsigned long*)memchr(RS485Frame,RS485EndCode,length);			//查找RS485EndCode尾标识符----从头标识符后开始查找	
	if(NULL==RS485Frame||NULL==RS485EndCodeAddr)
	{
		return RES_PARERR;
	}	
	ValidLength	=	ValidLength-((unsigned long)RS485Frame-(unsigned long)pBuffer);		//更新剩余数据长度
	pBuffer	=	(unsigned char*)RS485Frame;			//更新起始地址
	//-----------------------------------------地址判断:上层下发，识别目标地址是否为本地址或者广播地址0xFF
	TargetAddr	=	RS485Frame->HStart.TargetAddr;
	if((HCSYS.SwitchAddr!=TargetAddr)&&(0xFF!=TargetAddr))
	{		
		pBuffer	=	&pBuffer[1];
		goto CheckFarm;
	}
	//-----------------------------------------帧长度检查
	FarmeLen		=	(unsigned long)RS485EndCodeAddr-(unsigned long)RS485Frame+1;	
	if(sizeof(RS485AckDef)>FarmeLen)
	{
		pBuffer	=	&pBuffer[1];
		goto CheckFarm;
	}	
	//=========================================应答帧判断
	if(sizeof(RS485AckDef)==FarmeLen)		//应答帧
	{
		//---------------------------------------校验判断
		SourceBcc8	=	BCC8(&pBuffer[1],3);
		if(SourceBcc8!=pBuffer[4])					//应答消息
		{
			pBuffer	=	&pBuffer[1];
			goto CheckFarm;										//校验不对
		}
		//---------------------------------------应答帧:释放上传缓存
		else
		{
			TransU.Length	=	0;			//清除发送缓存
			pBuffer	=	&pBuffer[1];
			goto CheckFarm;
		}
	}
	
	
	//=========================================消息帧判断
	else
	{
		unsigned short	DataLength	=	0;
		DataLength	=	RS485Frame->HStart.DataLength;	
		if(ValidLength<DataLength+sizeof(RS485FrameStartDef)+3)	//3为起始符，结束符和BCC8，DataLength包含DataStartDef长度
		{
			pBuffer	=	&pBuffer[1];
			goto CheckFarm;
		}
		//---------------------------------------校验判断
		SourceBcc8	=	BCC8(&RS485Frame->HStart.TargetAddr,DataLength+sizeof(RS485FrameStartDef));
		if(SourceBcc8	!=	pBuffer[DataLength+sizeof(RS485FrameStartDef)+1])		//1为跨过起始标识符
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
			
			Addr	=	&RS485Frame->DStart.Addr.CabinetAddr;
			//---------------------------------------中间级
			if(HCSYS.Layer<3)		//非最终端设备
			{
				NextAddr	=	Addr[HCSYS.Layer];
				if(0xFF	==	NextAddr)
				{
					NextAddr	=	0;
					if(DataNodeD[0].NodeLength)
					{
						ACKU.Ack.ErrCode		=	Err_FAULT_BUSY;
					}
					else
					{
						memcpy(DataNodeD[0].data,RS485Frame,DataLength+sizeof(RS485FrameStartDef));						
						DataNodeD[0].NodeLength	=	DataLength+sizeof(RS485FrameStartDef)+3;	//3为起始符，结束符和BCC8，DataLength包含DataStartDef长度					
						RS485Frame	=	(RS485FrameDef*)DataNodeD[0].data;						
						//------------------------修改目的地址和源地址
						RS485Frame->HStart.TargetAddr	=	0xFF;
						RS485Frame->HStart.SourceAddr	=	0x00;
						
						pTemp	=	(unsigned char*)&RS485Frame->HStart.TargetAddr;
						//------------------------校验
						pTemp[DataLength+sizeof(RS485FrameStartDef)]	=	BCC8(pTemp,DataLength+sizeof(RS485FrameStartDef));	//头标识符和尾标识符不参与校验
						pTemp[DataLength+sizeof(RS485FrameStartDef)+1]	=	RS485EndCode;
						ACKU.Ack.ErrCode		=	Err_None;
					}
				}
				else
				{
					if(DataNodeD[NextAddr].NodeLength)
					{
						ACKU.Ack.ErrCode		=	Err_FAULT_BUSY;
					}
					else
					{
						memcpy(DataNodeD[NextAddr].data,RS485Frame,DataLength+sizeof(RS485FrameStartDef));
						DataNodeD[NextAddr].NodeLength	=	DataLength+sizeof(RS485FrameStartDef)+3;	//3为起始符，结束符和BCC8，DataLength包含DataStartDef长度	
						RS485Frame	=	(RS485FrameDef*)DataNodeD[NextAddr].data;						
						//------------------------修改目的地址和源地址
						RS485Frame->HStart.TargetAddr	=	NextAddr;
						RS485Frame->HStart.SourceAddr	=	0x00;
						
						pTemp	=	(unsigned char*)&RS485Frame->HStart.TargetAddr;
						//------------------------校验
						pTemp[DataLength+sizeof(RS485FrameStartDef)]	=	BCC8(pTemp,DataLength+sizeof(RS485FrameStartDef));	//头标识符和尾标识符不参与校验
						pTemp[DataLength+sizeof(RS485FrameStartDef)+1]	=	RS485EndCode;
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
					if(0	==	ProcessNode[i].NodeLength)
					{
						memcpy(ProcessNode[i].data,RS485Frame,DataLength+sizeof(RS485FrameStartDef));
						ProcessNode[i].NodeLength	=	DataLength+sizeof(RS485FrameStartDef)+3;	//3为起始符，结束符和BCC8，DataLength包含DataStartDef长度
						RS485Frame	=	(RS485FrameDef*)ProcessNode[i].data;
						
						pTemp	=	(unsigned char*)RS485Frame;
						pTemp	=	&pTemp[RS485StartFrameLen];
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
	
	unsigned char		TargetAddr	=	0;
	unsigned char		SourceAddr	=	0;
	unsigned char		SourceBcc8  =	0;
  unsigned short	FarmeLen		=	0;
//	unsigned short	DataLength	=	0;
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
	RS485Frame 				=	(RS485FrameDef*)memchr(pBuffer,RS485HeadCode,length);			//查找RS485HeadCode头标识符
	RS485EndCodeAddr	=	(unsigned long*)memchr(RS485Frame,RS485EndCode,length);		//查找RS485EndCode尾标识符----从头标识符后开始查找	
	if(NULL==RS485Frame||NULL==RS485EndCodeAddr)
	{
		return RES_PARERR;
	}
	ValidLength				=	ValidLength-((unsigned long)RS485Frame-(unsigned long)pBuffer);		//剩余数据长度
	pBuffer	=	(unsigned char*)RS485Frame;			//更新起始地址
	//-----------------------------------------地址判断:下层上传，目标地址为0，原地址为上传的地址
	pBuffer	=	(unsigned char*)RS485Frame;
	TargetAddr	=	RS485Frame->HStart.TargetAddr;
	SourceAddr	=	RS485Frame->HStart.SourceAddr;
	if((0x00!=TargetAddr)||(0x00==SourceAddr))
	{		
		pBuffer	=	&pBuffer[1];
		goto CheckFarm;
	}
	//-----------------------------------------帧长度判断
	FarmeLen		=	(unsigned long)RS485EndCodeAddr-(unsigned long)RS485Frame+1;	
	if(sizeof(RS485AckDef)>FarmeLen)
	{
		pBuffer	=	&pBuffer[1];
		goto CheckFarm;
	}
	//-----------------------------------------应答帧判断
	if(sizeof(RS485AckDef)==FarmeLen)		//应答帧
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
		unsigned short	DataLength	=	0;
		DataLength	=	RS485Frame->HStart.DataLength;	
		if(ValidLength<DataLength+sizeof(RS485FrameStartDef)+3)	//3为起始符，结束符和BCC8，DataLength包含DataStartDef长度
		{
			pBuffer	=	&pBuffer[1];
			goto CheckFarm;
		}
		//---------------------------------------校验判断
		SourceBcc8	=	BCC8(&RS485Frame->HStart.TargetAddr,DataLength+sizeof(RS485FrameStartDef));
		if(SourceBcc8	!=	pBuffer[DataLength+sizeof(RS485FrameStartDef)+1])		//1为跨过起始标识符
		{
			pBuffer	=	&pBuffer[1];
			goto CheckFarm;
		}
		//---------------------------------------数据正确：根据地址保存到DataNodeD或者SelfNode
		else
		{	
			//本地数据缓存大小SelfBuffSize
//			unsigned char SourceAddr	=	0;			//下一层地址			
			unsigned char	*Addr			=	NULL;
			unsigned char	*pTemp		=	NULL;
			unsigned char Layer			=	HCSYS.Layer;
			
			
//			SourceAddr	=	Addr[HCSYS.Layer];
//			SourceAddr	=	RS485Frame->SourceAddr;
			//---------------------------------------中间级
			if(HCSYS.Layer>0)		//非最终端设备--最顶层
			{
				Layer	=	Layer-1;
//				SourceAddr	=	Addr[HCSYS.Layer];

				if(DataNodeU[SourceAddr].NodeLength)
				{
					ACKD.Ack.TargetAddr	=	SourceAddr;
					ACKD.Ack.ErrCode		=	Err_FAULT_BUSY;
				}
				else
				{
					ACKD.Ack.TargetAddr	=	SourceAddr;					
					
					memcpy(DataNodeU[SourceAddr].data,RS485Frame,DataLength+sizeof(RS485FrameStartDef));
					
					DataNodeU[SourceAddr].NodeLength	=	DataLength+sizeof(RS485FrameStartDef)+2;
					
					RS485Frame	=	(RS485FrameDef*)DataNodeU[SourceAddr].data;
					Addr	=	&RS485Frame->DStart.Addr.CabinetAddr;
					
					pTemp	=	(unsigned char*)DataNodeU[SourceAddr].data;
					//------------------------修改目的地址和源地址
					RS485Frame->HStart.TargetAddr	=	0x00;
					RS485Frame->HStart.SourceAddr	=	HCSYS.SwitchAddr;
					Addr[Layer]				=	HCSYS.SwitchAddr;
					//------------------------校验
					pTemp[DataLength+sizeof(RS485FrameStartDef)]	=	BCC8(&pTemp[1],DataLength+sizeof(RS485FrameStartDef)-1);	//头标识符和尾标识符不参与校验
					pTemp[DataLength+sizeof(RS485FrameStartDef)+1]	=	RS485EndCode;
					ACKD.Ack.ErrCode		=	Err_None;
				}						
			}
			//---------------------------------------终端级--最顶层：转485
			else
			{	
				if(DataNodeU[SourceAddr].NodeLength)
				{
					ACKD.Ack.TargetAddr	=	RS485Frame->HStart.SourceAddr;
					ACKD.Ack.ErrCode		=	Err_FAULT_BUSY;
				}
				else
				{
					ACKD.Ack.TargetAddr	=	RS485Frame->HStart.SourceAddr;
					memcpy(DataNodeU[SourceAddr].data,RS485Frame,DataLength+sizeof(RS485FrameStartDef));
					
					DataNodeU[SourceAddr].NodeLength	=	DataLength+sizeof(RS485FrameStartDef)+2;
					RS485Frame	=	(RS485FrameDef*)DataNodeU[SourceAddr].data;
					pTemp	=	(unsigned char*)DataNodeU[SourceAddr].data;
					//------------------------修改目的地址和源地址
					RS485Frame->HStart.TargetAddr	=	0x00;
					RS485Frame->HStart.SourceAddr	=	HCSYS.SwitchAddr;
//					Addr[HCSYS.Layer]				=	HCSYS.SwitchAddr;
					//------------------------校验
					pTemp[DataLength+sizeof(RS485FrameStartDef)]	=	BCC8(&pTemp[1],DataLength+sizeof(RS485FrameStartDef)-1);	//头标识符和尾标识符不参与校验
					pTemp[DataLength+sizeof(RS485FrameStartDef)+1]	=	RS485EndCode;
					
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
	unsigned short	DataLength	=	0;
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
    if(0  ==  SendNode[i].NodeLength) //空缓存
    {
      RS485Frame  = (RS485FrameDef*)SendNode[i].data;
//      pBuffer     = (unsigned char*)RS485Frame->data;
			pBuffer     = (unsigned char*)SendNode[i].data;
			pBuffer			=	&pBuffer[RS485StartFrameLen];
      memcpy(pBuffer,buffer,length);
      
      RS485Frame->HStart.DataLength  = length;
      RS485Frame->HeadCode    = RS485HeadCode;
      RS485Frame->HStart.TargetAddr  = 0x00;
      RS485Frame->HStart.SourceAddr  = HCSYS.SwitchAddr;
      RS485Frame->DStart.ErrCode     = Err_None;
      
      pBuffer = (unsigned char*)&RS485Frame->DStart.Addr.CabinetAddr;
      memset(pBuffer,0x00,3);
      if(0<HCSYS.Layer)
      {
        pBuffer[HCSYS.Layer-1]  = HCSYS.SwitchAddr;
      }
      //---------------------------------计算校验
			DataLength	=	RS485Frame->HStart.DataLength;
      pBuffer = (unsigned char*)&RS485Frame->HStart.TargetAddr;
      pBuffer[DataLength+sizeof(RS485FrameStartDef)-1]	=	BCC8(pBuffer,DataLength+sizeof(RS485FrameStartDef)-1);	//头标识符和尾标识符不参与校验
      pBuffer[DataLength+sizeof(RS485FrameStartDef)]	=	RS485EndCode;	
      SendNode[i].NodeLength  = DataLength+sizeof(RS485FrameStartDef)+2;
      
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
		DataLength  = ProcessNode[i].NodeLength;
		
    if(0  !=  DataLength)
    {
      pBuffer = ProcessNode[i].data;
      
      memcpy(buffer,pBuffer,DataLength);
      
      ProcessNode[i].NodeLength = 0;
      
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
		FrameLength	=	DataNodeD[i].NodeLength;
		if(0	!=	FrameLength)		//有数据
		{
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
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
HCResult APIRS232UplinkSetData(const unsigned char *buffer,const unsigned short length)
{
	
//	CmdDef		CmdTemp;
	
	RS232FrameDef *RS232Frame 	= NULL;
	RS485FrameDef *RS485Frame 	= NULL;
	unsigned char	*pBuffer			=	0;
	unsigned char	*Head1Addr		=	0;		//头标识符地址
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
	if(ValidLength>0)
	{
		ValidLength	=	ValidLength	-	1;		//去除RS232Head1长度
	}
	SourceBcc8	=	RS232Frame->Bcc8;
	DataLength	=	RS232Frame->DataLength;
	UserCode		=	RS232Frame->UserCode;
	//=========================================应答帧判断(数据长度为0，校验码为0):如果为应答消息，则把发送缓存标志清除
	if(0	==	DataLength)				//应答类型
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
	else			//网关板下一级为单元板
	{	
		AddrDef		AddrTemp;						//地址
		unsigned char *pTemp		=0;
		unsigned char Bcc8Temp	=0;
		unsigned char i					=0;		
		//----------------------------------------获取地址数据
		pTemp	=	&RS232Frame->DataLength;
		pTemp	=	&pTemp[1];
		memcpy(&AddrTemp,pTemp,3);		//拷贝地址	
		//----------------------------------------数据校验
		Bcc8Temp	=	BCC8(pTemp,DataLength);
		if(SourceBcc8	!=	Bcc8Temp)
		{
			pBuffer	=	&pBuffer[1];			//地址加1，返回继续检查
			goto CheckFarm;
		}
		//========================================数据处理
		//----------------------------------------判断是本层数据还是需要转发的数据(柜地址为0表示此为网关板数据)
		TargetAddr	=	AddrTemp.CabinetAddr;
		//-----------------------------------------本地消息：单元板地址为0
		if(0==AddrTemp.CabinetAddr)		//单元柜地址为0
		{
			//--------------------------------------查找空缓存存储数据待处理(按485格式存储)
			for(i=0;i<SelfBuffSize;i++)
			{
				if(0	==	ProcessNode[i].NodeLength)
				{
					RS485Frame	=	(RS485FrameDef*)&ProcessNode[i].data[0];
					//------------------头两字节为命令号和用户码
					RS485Frame->HeadCode		=	RS485HeadCode;
					RS485Frame->HStart.TargetAddr	=	0x00;
					RS485Frame->HStart.SourceAddr	=	0x00;
					RS485Frame->DStart.ErrCode			=	RS232Frame->ErrCode;
					RS485Frame->DStart.Addr.CabinetAddr	=	RS232Frame->CabinetAddr;
					RS485Frame->DStart.Addr.LayerAddr		=	RS232Frame->LayerAddr;
					RS485Frame->DStart.Addr.SlotAddr		=	RS232Frame->SlotAddr;
					RS485Frame->HStart.DataLength	=	RS232Frame->DataLength-4+3;
					
//					DataType->Cmd				=	RS232Frame->Cmd;
//					DataType->UserCode	=	RS232Frame->UserCode;
					
					memcpy(&ProcessNode[i].data[2],pTemp,DataLength);
					ProcessNode[i].NodeLength	=	DataLength+2;
				}
			}
			//--------------------------------------创建应答
			if(i<SelfBuffSize)		//存储成功
			{
				ACKU.Ack.ErrCode		=	Err_None;
			}
			else									//无空缓存，设备忙状态
			{
				ACKU.Ack.ErrCode		=	Err_FAULT_BUSY;
			}
		}
		//(DataLength<BusDataSize))		//数据长度小于最大缓存空间
		//-----------------------------------------转换为RS485协议包
		else
		{
			unsigned char	*pT	=	NULL;
			for(i=0;i<MaxNetPerLayer;i++)
			{
				if(0	==	DataNodeD[i].NodeLength)
				{
					RS485Frame	=	(RS485FrameDef*)&DataNodeD[i].data[0];
					
					RS485Frame->HeadCode		=	RS485HeadCode;
					RS485Frame->HStart.TargetAddr				=	RS232Frame->CabinetAddr;
					RS485Frame->HStart.SourceAddr				=	0x00;
					RS485Frame->DStart.ErrCode					=	RS232Frame->ErrCode;
					RS485Frame->DStart.Addr.CabinetAddr	=	RS232Frame->CabinetAddr;
					RS485Frame->DStart.Addr.LayerAddr		=	RS232Frame->LayerAddr;
					RS485Frame->DStart.Addr.SlotAddr		=	RS232Frame->SlotAddr;
					RS485Frame->HStart.DataLength				=	RS232Frame->DataLength-4+3;
					//---------------获取数据地址
					pTemp	=	(unsigned char*)&RS232Frame->ErrCode;
					pTemp++;
					
					pT	=	&DataNodeD[i].data[RS485StartFrameLen];
					pT[0]	=	RS232Frame->Cmd;
					pT[1]	=	RS232Frame->UserCode;
					pT[2]	=	RS232Frame->Serial;
					
					DataLength	=	RS485Frame->HStart.DataLength;
					
					memcpy(&pT[3],pTemp,DataLength-3);
					
					pTemp	=	(unsigned char*)&RS485Frame->Data[DataLength+3];
					
					pT[DataLength]		=	BCC8(&RS485Frame->HStart.TargetAddr,DataLength+sizeof(RS485FrameStartDef)-1);
					pT[DataLength+1]	=	RS485EndCode;
					DataNodeD[i].NodeLength	=	DataLength+sizeof(RS485FrameStartDef)+3;
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
	Bcc8	=	RS485FrameGetBcc8(HeadAddr,RS485AckFrameLen);
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
unsigned char RS485FrameGetBcc8(const unsigned char *HeadAddr,const unsigned short length)
{
	unsigned char		*pBuffer		=	0;			//数据处理buffer
	
	unsigned char		Bcc8				=	0;
	unsigned short	ValidLength	= 0;			//buffer中有效数据长度(从RS485头标识符开始后的数据为有效数据)
	unsigned short	i	=	0;
	//=================================================================================导入数据:输入为const类型
	pBuffer			=	(unsigned char*)HeadAddr;
	ValidLength	=	(unsigned short)length-3;			//减去头尾和校验位长度
	
	pBuffer			=	&pBuffer[1];				//开始计算校验的起始字节
	
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











































