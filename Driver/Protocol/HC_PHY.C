#include "HC_PHY.H"
#include "STM32_USART.H"
#include "TOOL.H"		//数据校验工具



#include	"stdio.h"			//用于printf
#include	"string.h"		//用于printf
#include	"stdarg.h"		//用于获取不确定个数的参数
#include	"stdlib.h"		//malloc动态申请内存空间



//#include "STM32_GPIO.H"
//#include "STM32_SYS.H"
//#include "STM32_SYSTICK.H"
//#include "STM32_WDG.H"
//#include "STM32_USART.H"
//#include "STM32_PWM.H"

//#include "string.h"				//串和内存操作函数头文件
//#include "stm32f10x_dma.h"

//#define BufferSize	512
//unsigned char RS485BufferRU[1024]={0};		//上级数据接收缓存
//unsigned char RS485BufferTU[1024]={0};		//向上级发送数据缓存
//unsigned char RS485BufferRD[1024]={0};		//下级数据接收缓存
////unsigned char RS485BufferTD[1024]={0};
//unsigned char RS232BufferU[1024]={0};
//unsigned char RS232BufferD[1024]={0};

unsigned char	SerialU	=	0;							  //往上层上传流水号 0x01~0x7D 每次使用后加1(为了不与起始符和结束符冲突，流水号最大值为0x7D)
unsigned char	SerialD	=	0;							  //往下层下发流水号 0x01~0x7D 每次使用后加1(为了不与起始符和结束符冲突，流水号最大值为0x7D)

TransDef  TransU;     //向上传送缓冲区
TransDef  TransD;     //向下传送缓冲区

StepDef UWORKSTEP;											  //往上级接口传送数据步骤
StepDef DWORKSTEP[MaxNetPerLayer]={0};	  //下级接口工作步骤
DataNodeDef	DataNode[MaxNetPerLayer+1];	//目标地址数据数组--按目标地址排序(缓存数组从0开始，目标地址从1开始）

RS485AckNodeDef		RS485ACKU;									//响应上级的应答
RS485AckNodeDef		RS485ACKD;									//响应下级的应答
static HCSYSDef	HCSYS;
unsigned short Lenth	=	0;
unsigned short Lenth2	=	0;

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
	HCResult	res	  	=	RES_OK;
  HCSYS.Layer				= Layer;
  HCSYS.SwitchAddr	= id;
	return res;
}

/*******************************************************************************
* 函数名			:	function
* 功能描述		:	函数功能说明 
* 输入			: buffer  输入的数据缓存地址
              length  输入的数据长度
              UDflag  0-上层输入的数据
                      1-下层输入的数据
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
HCResult SetDataProcess(const unsigned char *buffer,const unsigned short length,const unsigned char UDflag)
{
	HCResult	res	=	RES_OK;
	if(NULL ==  buffer)		//空地址
  {
    return RES_NODATA;
  }
	//===================================上层下发数据：目标地址与本地址相符，UDflag==0
  switch(HCSYS.Layer)
  {
   case MBLayer:      //0-主板(网关板)
        res = MBLayerDataProcess(buffer,length,UDflag);     //单元板数据处理
     break;
   case CALayer:      //1-单元板
        res = CALayerDataProcess(buffer,length,UDflag);     //单元板数据处理
     break;
   case LALayer:      //2-层板
        res = LALayerDataProcess(buffer,length,UDflag);     //层板数据处理
     break;
   case SALayer:      //3-驱动板
        res = SALayerDataProcess(buffer,length,UDflag);     //驱动板数据处理
     break;
   default:break;
  }
	res	=	AckDataProcess(buffer,length,UDflag);

	//===================================其它跳过协议和地址的命令（透传）
	return res;
}
/*******************************************************************************
* 函数名			:	GetSubOnlineAddr
* 功能描述		:	获取下级在线设备地址(最大挂载设备数MaxNetPerLayer) 
* 输入			: buffer 接收数据的缓存
							flag		0-获取响应上级的应答
											1-获取响应下级的应答
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
unsigned short GetAck(unsigned char *buffer,unsigned char flag)
{
	unsigned short Length = 0;
	if(0	==	flag)	    //0-获取响应上级的应答
	{
		Length  = RS485ACKU.FarmeLength;
		if(0	!=	Length)
		{			
			memcpy(buffer,&RS485ACKU.data,Length);
			RS485ACKU.FarmeLength	=	0;      
		}
	}
	else						    //1-获取响应下级的应答
	{
		Length  = RS485ACKD.FarmeLength;
		if(0	!=	Length)
		{			
			memcpy(buffer,&RS485ACKD.data,Length);
			RS485ACKD.FarmeLength	=	0; 
		}
	}
	return Length;
}
/*******************************************************************************
* 函数名			:	GetSubOnlineAddr
* 功能描述		:	获取下级在线设备地址(最大挂载设备数MaxNetPerLayer) 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
HCResult GetSubOnlineAddr(void)
{
	HCResult	res	  			=	RES_OK;
	RS485FrameDef *Frame 	= NULL;	//接收到的消息帧结构体
	if(	SALayer	>	HCSYS.Layer)	//非最低层板，如果缓存为空，将数据存入缓存数组待转发，如果非空，报忙或者等待状态
	{
		unsigned char	i	=	0;
		//===================================组装数据
		for(i	=	1;i<=MaxNetPerLayer;i++)
		{
			Frame	=	(RS485FrameDef*)DataNode[i].data;			
			Frame->HeadCode					=	RS485Head1;
			Frame->TargetAdd				=	i;
			Frame->SourceAdd				=	0;
			Frame->Serial						=	0x01;
			Frame->Cmd							=	CMD_GET_ADDR;
			Frame->UserCode					=	0x00;
			Frame->StsCode					=	eNoErr;
			Frame->DataLength				=	0;							//数据长度
			Frame->Addr.CabinetAddr	=	0;
			Frame->Addr.LayerAddr		=	0;
			Frame->Addr.SlotAddr		=	0;
			DataNode[i].data[11]		=	BCC8(&DataNode[i].data[0],11);	//从源地址开始计算校验码
			DataNode[i].data[12]		= RS485end1;			//结束符
			DataNode[i].FarmeInfo.Length   = 13;       //数据长度
		}
	}
	return res;
}

/*******************************************************************************
* 函数名			:	AddACKRS485
* 功能描述		:	函数功能说明 
* 输入			: buffer  输入的数据缓存地址
              length  输入的数据长度
              UDflag  0-上层输入的数据
                      1-下层输入的数据
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
HCResult AckDataProcess(const unsigned char *buffer,const unsigned short length,const unsigned char UDflag)
{
	HCResult	res	=	RES_OK;
  RS485FrameDef *RecFrame 	= NULL;	//接收到的消息帧结构体
	RS485FrameDef *AckFrame 	= NULL;	//应答帧结构体
	unsigned char	TargetAdd		=	0;		//目标地址
	unsigned char	LayerAddr		=	0;		//层地址
	unsigned char	FrameLength	=	0;		//消息帧总长度，从HeadCode到EndCode的字节数
  if(NULL ==  buffer)		//空地址
  {
    return RES_NODATA;
  }
	//----------------------------------
	RecFrame		=	(RS485FrameDef*)memchr(buffer,RS485Head1,length);		//查找RS485Head1头标识符
	TargetAdd		=	RecFrame->TargetAdd;	          //目标地址
	LayerAddr		=	RecFrame->Addr.SlotAddr;		    //下一级目标地址：如果下级地址为0，表示此消息是本板使用消息，存入RS485Node[0]
	FrameLength	=	RecFrame->DataLength+13;
	
	//===================================上层发数据需要向上应答（上层下发地址识别：目标地址为本地址）应答协议：目标地址为0，源地址为本地址，下级及往后地址都为0
  if( (0  ==  UDflag)                         	//上层下发数据标志:向上层应答
    &&(HCSYS.SwitchAddr	==	TargetAdd))  				//目标地址与本拨码地址一致
  {
		if(eBoxAck	==	RecFrame->StsCode)					//此消息为应答消息
		{
			TransU.Length	=	0;
			return RES_OK;
		}
		
		AckFrame	=	(RS485FrameDef*)RS485ACKU.data;
		
		AckFrame	=	(RS485FrameDef*)RS485ACKU.data;		
		AckFrame->HeadCode		=	RS485Head1;           				//头标识符
		AckFrame->TargetAdd		=	0;														//目标地址:下发为需要接收的地址
		AckFrame->SourceAdd		=	HCSYS.SwitchAddr;     				//源地址:下发为0
		AckFrame->Serial			=	SerialU;											//流水号
		AckFrame->Cmd					=	RecFrame->Cmd;								//命令号
		AckFrame->UserCode		=	RecFrame->UserCode;						//用户码：不处理，原样返回
		AckFrame->StsCode			=	eBoxAck;											//状态码---应答消息
		AckFrame->DataLength	=	0;														//data数据长度（*data)	
		RS485ACKU.data[8]			=	BCC8(&(RS485ACKU.data[0]),8);	//校验码
		RS485ACKU.data[9]			=	RS485end1;										//b(DataLength+13)结束符 0x7F
		RS485ACKU.FarmeLength	=	AckDataLen;										//应答消息长度
		
		res = RES_OK;
  }
  //===================================下层上传数据需要应答（下层上传数据识别：目标地址为0）应答协议：目标地址为对答对象地址，源地址0，不带地址域和数据
  else if(  (1  ==  UDflag)               //下层上传数据标志：向下层应答
         &&(0x00	==	TargetAdd))	       	//目标地址为0
  {
		if(eBoxAck	==	RecFrame->StsCode)			//此消息为应答消息
		{
			TransD.Length	=	0;
			return RES_OK;
		}
		AckFrame	=	(RS485FrameDef*)RS485ACKD.data;		
		AckFrame->HeadCode		=	RS485Head1;                		//头标识符
		AckFrame->TargetAdd		=	0;														//目标地址:下发为需要接收的地址
		AckFrame->SourceAdd		=	HCSYS.SwitchAddr;         		//源地址:下发为0
		AckFrame->Serial			=	SerialU;											//流水号
		AckFrame->Cmd					=	RecFrame->Cmd;								//命令号
		AckFrame->UserCode		=	RecFrame->UserCode;						//用户码：不处理，原样返回
		AckFrame->StsCode			=	eBoxAck;											//状态码---应答消息
		AckFrame->DataLength	=	0;														//data数据长度（*data)	
		RS485ACKD.data[8]			=	BCC8(&(RS485ACKD.data[0]),8);	//校验码
		RS485ACKD.data[9]			=	RS485end1;										//b(DataLength+13)结束符 0x7F
		RS485ACKD.FarmeLength	=	AckDataLen;										//应答消息长度
		
		res = RES_OK;
  }
	return res;
}

/*******************************************************************************
* 函数名			:	SetDataRS485
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
HCResult MBLayerDataProcess(const unsigned char *buffer,const unsigned short length,const unsigned char UDflag)
{
	HCResult	res	=	RES_OK;
	RS232FrameDef	*RS232Frame	=	NULL;
	unsigned char TargetAddr		=	0;			//目标地址
	res	=	CheckDataFarm(buffer,length,UDflag);
	if(RES_FARME232	==	res)		//232格式数据
	{
		if(7	==	length)			//上位机应答数据长度
		{
			TransU.Length	=	0;
		}
		else			//转换为RS485格式数据
		{
			RS485FrameDef *RS485Frame	=	NULL;
			RS232Frame	=	(RS232FrameDef*)memchr(buffer,RS232Head1,length);		//查找RS485Head1头标识符
			TargetAddr	=	RS232Frame->Addr.CabinetAddr;												//获取单元板地址
			
			RS485Frame	=	(RS485FrameDef*)DataNode[TargetAddr].data;					//数据存储起始地址
			RS485Frame->HeadCode	=	RS485Head1;								//头标识
			RS485Frame->TargetAdd	=	TargetAddr;								//目标地址
			RS485Frame->SourceAdd	=	0x00;											//源地址
			RS485Frame->Serial		=	RS232Frame->Head.Serial;	//流水号
			RS485Frame->Cmd				=	RS232Frame->Head.Cmd;			//命令号
			RS485Frame->UserCode	=	RS232Frame->Head.UserCode;//用户码
			RS485Frame->DataLength=		RS232Frame->Head.DataLength-3;	//数据长度，去掉地址长度

		}
	}

  return res;
}
/*******************************************************************************
* 函数名			:	SetDataRS485
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
HCResult CALayerDataProcess(const unsigned char *buffer,const unsigned short length,const unsigned char UDflag)
{
	HCResult	res	=	RES_OK;

  return res;
}
/*******************************************************************************
* 函数名			:	SetDataRS485
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
HCResult LALayerDataProcess(const unsigned char *buffer,const unsigned short length,const unsigned char UDflag)
{
	HCResult	res	=	RES_OK;
  RS485FrameDef *Frame  		= NULL;
	unsigned char TargetAdd		=	0;		//目标地址
	unsigned char LayerAddr		=	0;		//层地址
	unsigned char FrameLength	=	0;	//消息帧总长度，从HeadCode到EndCode的字节数
	
  if(NULL ==  buffer)		//空地址
  {
    return RES_NODATA;
  }
	Frame	    =	(RS485FrameDef*)memchr(buffer,RS485Head1,length);		//查找RS485Head1头标识符
	TargetAdd	=	Frame->TargetAdd;	          //目标地址
	LayerAddr	=	Frame->Addr.SlotAddr;		    //下一级目标地址：如果下级地址为0，表示此消息是本板使用消息，存入RS485Node[0]
	FrameLength	=	Frame->DataLength+13;
  if((TargetAdd ==  HCSYS.SwitchAddr)     //本板消息
    &&(0  ==  UDflag))                    //此消息为上层下发消息
  {
    memcpy(&(DataNode[LayerAddr].data[0]),Frame,FrameLength);   //复制数据到本地缓存
    if((0<LayerAddr)&&(0xFF>LayerAddr))   //此消息需要传递到下一层
    {
      ((RS485FrameDef*)(DataNode[LayerAddr].data))->TargetAdd  	= LayerAddr;        //目标地址
      ((RS485FrameDef*)(DataNode[LayerAddr].data))->SourceAdd  	= 0x00; 						//源地址--下发为00
      DataNode[LayerAddr].data[Frame->DataLength+12]						= BCC8(DataNode[LayerAddr].data,Frame->DataLength+11);  //重新计数校验
      DataNode[LayerAddr].FarmeInfo.Length               						= FrameLength;    	//加上校验位，总共需要发送的数据长度
    }
    res	=	RES_OK;
  }
  else if(1  ==  UDflag)      //底层上传数据：需要添加本层地址后待上传
  {
    memcpy(&(DataNode[LayerAddr].data[0]),Frame,Frame->DataLength+13);      							//复制数据到本地缓存
    ((RS485FrameDef*)(DataNode[LayerAddr].data))->TargetAdd					= 0;    							//目标地址:上传为0
    ((RS485FrameDef*)(DataNode[LayerAddr].data))->SourceAdd					= HCSYS.SwitchAddr;  	//源地址
    ((RS485FrameDef*)(DataNode[LayerAddr].data))->Addr.LayerAddr		= HCSYS.SwitchAddr;  	//加入本地址--层板地址
    DataNode[LayerAddr].data[Frame->DataLength+12]									= BCC8(DataNode[LayerAddr].data,Frame->DataLength+11);  //重新计数校验
    DataNode[LayerAddr].FarmeInfo.Length               									= FrameLength;    		//加上校验位，总共需要发送的数据长度
    res	=	RES_OK;
  }
  else
  {
    res	= RES_UNKNOW;
  }
  return res;
}
/*******************************************************************************
* 函数名			:	SALayerDataProcess
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
HCResult SALayerDataProcess(const unsigned char *buffer,const unsigned short length,const unsigned char UDflag)
{
	HCResult	res	=	RES_OK;
  RS485FrameDef *Frame  = NULL;
  unsigned char *Address  = NULL;	//地址域起始地址
	unsigned char TargetAdd	=	0;		//目标地址
	unsigned char LayerAddr	=	0;		//层地址
  if(NULL ==  buffer)		//空地址
  {
    return RES_NODATA;
  }
	Frame	    =	(RS485FrameDef*)memchr(buffer,RS485Head1,length);		//查找RS485Head1头标识符
	TargetAdd	=	Frame->TargetAdd;	          //目标地址

  if((TargetAdd ==  HCSYS.SwitchAddr)     //本板消息
    &&(0  ==  UDflag))                    //此消息为上层下发消息
  {
    memcpy(&(DataNode[0].data[0]),Frame,Frame->DataLength+13);   //复制数据到本地缓存
    res	=	RES_OK;
  }
  else
  {
    res	= RES_UNKNOW;
  }
  return res;
}
/*******************************************************************************
* 函数名			:	DataCheck
* 功能描述		:	数据校验
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
HCResult CheckDataFarm(const unsigned char *buffer,const unsigned short length,const unsigned char UDflag)
{
  HCResult	res	=	RES_OK;
  RS485FrameDef   *RS485Frame	= NULL;
	RS232FrameDef		*RS232Frame	=	NULL;
  unsigned char   Bcc8      = 0;    //校验码
//  unsigned short  BassAddr  = 0;    //找到头标识符在输入数组中的偏移地址
	if(NULL ==  buffer)		//空地址
  {
    return RES_NODATA;
  }
	RS232Frame	=	(RS232FrameDef*)memchr(buffer,RS232Head1,length);		//查找RS485Head1头标识符
	if(NULL	!=	RS232Frame)			//未找到RS232Head1
	{
		if((RS232Head2==RS232Frame->Head.Head2)
			&&(length>=sizeof(RS232HeadDef)))
		{
			return RES_FARME232;     	//232格式数据
		}
	}
	
  RS485Frame	=	(RS485FrameDef*)memchr(buffer,RS485Head1,length);		//查找RS485Head1头标识符
  if(NULL == RS485Frame)         //未找到头标识符
  {
    return RES_FARMERR;     //帧格式错误
  }
  if(MinDataLen>length) 		//数据长度校验(消息长度==Frame->Length+1字节校验位)
  {
    return RES_FARMERR;     //帧格式错误
  }
	if(	(0	==	UDflag)				//上层下发，匹配目的地址
		&&(HCSYS.SwitchAddr	!=	RS485Frame->TargetAdd))	//地址不匹配
	{
		return RES_UNKNOW;
	}
  Bcc8  = BCC8((unsigned char*)RS485Frame,RS485Frame->DataLength+11);      //固定长度为7（从RS485Head到End校验）  
  if(Bcc8 ==  ((unsigned char*)RS485Frame)[RS485Frame->DataLength+11])   	//校验位在消息尾端，不计算在消息长度内
  {
		if(eBoxAck	==	RS485Frame->StsCode)
			return RES_ACK;
		else
			return RES_FARME485;     	//232格式数据
  }  
  return res;
}
/*******************************************************************************
* 函数名			:	DataCheck
* 功能描述		:	数据校验
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
HCResult RS485FarmCheck(const unsigned char *buffer,const unsigned short length,const unsigned char UDflag)
{
  HCResult	res	=	RES_OK;
  RS485FrameDef   *RS485Frame	= NULL;
	RS232FrameDef		*RS232Frame	=	NULL;
  unsigned char   Bcc8      = 0;    //校验码
  unsigned short  BassAddr  = 0;    //找到头标识符在输入数组中的偏移地址
	if(NULL ==  buffer)		//空地址
  {
    return RES_NODATA;
  }
	switch(HCSYS.Layer)
  {
   case MBLayer:      //0-主板(网关板)
								RS232Frame	=	(RS232FrameDef*)memchr(buffer,RS232Head1,length);		//查找RS485Head1头标识符
								if(NULL	==	RS232Frame)	//未找到
								{
									return RES_FARMERR;     //帧格式错误
								}
								if(RS232Frame->Head.Head2	==	0xF5)
								{
								}
     break;
   case CALayer:      //1-单元板
        res = CALayerDataProcess(buffer,length,UDflag);     //单元板数据处理
     break;
   case LALayer:      //2-层板
        res = LALayerDataProcess(buffer,length,UDflag);     //层板数据处理
     break;
   case SALayer:      //3-驱动板
        res = SALayerDataProcess(buffer,length,UDflag);     //驱动板数据处理
     break;
   default:break;
  }
	res	=	AckDataProcess(buffer,length,UDflag);
	
  
	
	
	
	
  RS485Frame	=	(RS485FrameDef*)memchr(buffer,RS485Head1,length);		//查找RS485Head1头标识符
  if(NULL == RS485Frame)         //未找到头标识符
  {
    return RES_FARMERR;     //帧格式错误
  }
  if(MinDataLen>length) 		//数据长度校验(消息长度==Frame->Length+1字节校验位)
  {
    return RES_FARMERR;     //帧格式错误
  }
	if(	(0	==	UDflag)				//上层下发，匹配目的地址
		&&(HCSYS.SwitchAddr	!=	RS485Frame->TargetAdd))	//地址不匹配
	{
		return RES_UNKNOW;
	}
  Bcc8  = BCC8((unsigned char*)RS485Frame,RS485Frame->DataLength+11);      //固定长度为7（从RS485Head到End校验）  
  if(Bcc8 ==  ((unsigned char*)RS485Frame)[RS485Frame->DataLength+11])   	//校验位在消息尾端，不计算在消息长度内
  {
		if(eBoxAck	==	RS485Frame->StsCode)
			return RES_ACK;
		else
			return RES_OK;          //数据校验正确
  }  
  return res;
}
/*******************************************************************************
* 函数名			:	function
* 功能描述		:	函数功能说明 
* 输入			: buffer  输入的数据缓存地址
              UDflag  0-获取向上传的数据
                      1-获取向下发数据缓存
* 返回值			: 缓存长度
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
unsigned short GetDataProcess(unsigned char *buffer,const unsigned char UDflag)
{	
	unsigned char i	=	0;
  unsigned short Length = 0;
  //=================================获取待上传数据
  if(0  ==  UDflag)
  {
    Length  = TransU.Length;
    if(Length)                  //发送缓冲有数据
    {
      memcpy(buffer,TransU.data,Length);
			if(TransU.Retry.Retry++>=ReSendCount)
			{
				TransU.Length	=	0;
			}
      return Length;
    }
    else                        							//发送缓冲区无数据，检查数据队列中有没待发送数据
    {
      for(i	=	1;i<=MaxNetPerLayer;i++) 				//遍历
      {
				Length  = DataNode[i].FarmeInfo.Length;
        if(Length&&(0x00 ==  DataNode[i].data[1]))
        {
					memcpy(TransU.data,DataNode[i].data,DataNode[i].FarmeInfo.Length);
					memcpy(buffer,DataNode[i].data,DataNode[i].FarmeInfo.Length);
					
					TransU.Length = DataNode[i].FarmeInfo.Length;
					TransU.Retry.Retry  = 0;
					TransU.Retry.Time   = 0;
					DataNode[i].FarmeInfo.Length = 0;    //清除缓存数据标志
					return Length;
        }
      }
      return 0;
    }
  }
  //=================================获取待下发数据
  else
  {
    Length  = TransD.Length;
    if(Length)                  //发送缓冲有数据
    {
      memcpy(buffer,TransD.data,Length);
			if(TransD.Retry.Retry++>ReSendCount)		//下发示响应
			{				
				TransD.Length	=	0;
			}
      return Length;
    }
    else                        //发送缓冲区无数据，检查数据队列中有没待发送数据
    {
      for(i	=	1;i<=MaxNetPerLayer;i++) //遍历
      {
				Length  = DataNode[i].FarmeInfo.Length;
        if(Length&&(0x00 !=  DataNode[i].data[1]))
        {
					memcpy(TransD.data,DataNode[i].data,Length);
					memcpy(buffer,DataNode[i].data,Length);
					
					TransD.Length = Length;
					TransD.Retry.Retry  = 0;
					TransD.Retry.Time   = 0;
					DataNode[i].FarmeInfo.Length = 0;    //清除缓存数据标志
					return Length;
        }
      }
      return 0;
    }
  }
	return Length;
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
HCResult UMFrameProcess(const unsigned char *buffer)
{
	HCResult	res	=	RES_OK;

	//=====================================转发上层数据

	//=====================================转发下级数据
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
HCResult DMFrameProcess(const unsigned char *buffer)
{
	HCResult	res	=	RES_OK;

	//=====================================转发上层数据

	//=====================================转发下级数据
	return res;
}














