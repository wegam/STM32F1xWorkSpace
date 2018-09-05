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
RS485NodeDef	RS485Node[MaxNetPerLayer];	//目标地址数据数组--按目标地址排序(缓存数组从0开始，目标地址从1开始）

RS485AckDef	RS485ACKU;									//响应上级的应答
RS485AckDef	RS485ACKD;									//响应下级的应答
static HCSYSDef  HCSYS;
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
HCResult HCBoradSet(const unsigned char *buffer,unsigned short length)
{
	HCResult	res	  	=	RES_OK;
  HCSYS.Layer				= TargetLayer;
  HCSYS.SwitchAddr	= buffer[1];
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
HCResult DataProcess(const unsigned char *buffer,const unsigned short length,const unsigned char UDflag)
{
	HCResult	res	=	RES_OK;
  RS485FrameDef *Frame  = NULL;
  res = DataCheck(buffer,length,UDflag);    //数据校验
  if(RES_OK !=  res)  //校验不通过
  {
    return res;
  }
  if(length<=AckDataLen)      //应答消息，有应答，清除相关缓存，不再重发
  {
    if(0  ==  UDflag)         //上层应答，清除发送缓冲区
    {
      TransU.Length  = 0;
    }
    else
    {
      TransD.Length  = 0;
    }
    return RES_OK;
  }
  res	=	WriteDataProcess(buffer,length,UDflag);
//	//===================================RS232数据协议（网关板）
//	if(	(RS232Head1	==	buffer[0])		//0xFA
//		&&(RS232Head2	==	buffer[1]))		//0xF5
//	{
//	}
//	//===================================RS485数据协议
//	else if(RS485Head1	==	buffer[0])		//0x7E RS485通讯协议头标识符
//	{
//		Frame	=	(RS485FrameDef*)memchr(buffer,RS485Head1,length);		//查找RS485Head1头标识符
//		if(NULL	==	Frame)	//未找到
//		{
//			return	RES_UNKNOW;
//		}
//		switch(Frame->Cmd)
//		{
//			case CMD_LINK:	return RES_LINK;
//				break;
//			default:
//							res	=	WriteDataProcess(buffer,length,UDflag);
//							res	=	AddACKRS485(buffer,length,UDflag);			//将数据存入缓存
//			break;
//		}
//	}
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
		if(RS485Head1 ==	RS485ACKU.HeadCode)
		{			
			memcpy(buffer,&RS485ACKU,AckDataLen);
			RS485ACKU.HeadCode	=	0;
      Length  = AckDataLen;
		}
	}
	else						    //1-获取响应下级的应答
	{
		if(RS485Head1 ==	RS485ACKD.HeadCode)
		{			
			memcpy(buffer,&RS485ACKD,AckDataLen);
			RS485ACKD.HeadCode	=	0;
      Length  = AckDataLen;
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
	HCResult	res	  	=	RES_OK;
	if(	SALayer	>	HCSYS.Layer)	//非最低层板，如果缓存为空，将数据存入缓存数组待转发，如果非空，报忙或者等待状态
	{
		unsigned char	i	=	0;
		//===================================组装数据
		for(i	=	0;i<MaxNetPerLayer;i++)
		{
      RS485Node[i].Length   = 13;       //数据长度
      RS485Node[i].data[0]  = (unsigned char)RS485Head1;			//485起始符
      RS485Node[i].data[1]  = i+1;			      //目标地址
      RS485Node[i].data[2]  = 0x00;			      //源地址
      RS485Node[i].data[3]  = 0x01;			      //流水号
      RS485Node[i].data[4]  = CMD_GET_ADDR;	  //命令号
      RS485Node[i].data[5]  = 0x01;			      //用户码
      RS485Node[i].data[6]  = 4;			        //数据长度（地址+状态码）
      RS485Node[i].data[7]  = 0x00;			      //柜地址(单元柜号)  下行时为柜地址，上行时，柜地址为0x00）
      RS485Node[i].data[8]  = 0x00;			      //层地址
      RS485Node[i].data[9]  = 0x00;			      //槽地址(终端地址)
      RS485Node[i].data[10] = 0x00;           //状态码
      RS485Node[i].data[11] = BCC8(&RS485Node[i].data[1],9);			//从源地址开始计算校验码
      RS485Node[i].data[12] = RS485end1;			//结束符
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
HCResult AddACKRS485(const unsigned char *buffer,const unsigned short length,const unsigned char UDflag)
{
	HCResult	res	=	RES_OK;
  RS485FrameDef *Frame  = (RS485FrameDef*)buffer;
  if(NULL ==  buffer)		//空地址
  {
    return RES_NODATA;
  }
	//===================================上层发数据需要向上应答（上层下发地址识别：目标地址为本地址）
  if( (0  ==  UDflag)                           //上层下发数据标志
    &&(HCSYS.SwitchAddr	==	Frame->TargetAdd))  //目标地址与本拨码地址一致
  {
    RS485ACKU.HeadCode	  =	RS485Head1;                     //头标识符
    RS485ACKU.TargetAdd	  =	0x00;                           //目标地址
    RS485ACKU.SourceAdd 	=	HCSYS.SwitchAddr;               //源地址
    RS485ACKU.Serial		  =	Frame->Serial;                  //流水号
    RS485ACKU.Cmd				  =	Frame->Cmd;                     //命令号
    RS485ACKU.UserCode	  =	Frame->UserCode;                //用户码
    RS485ACKU.Length		  =	0;                              //数据长度
    RS485ACKU.Bcc8	      =	BCC8(&(RS485ACKU.TargetAdd),6);		//校验码
    RS485ACKU.EndCode		  =	RS485end1;
  }
  //===================================下层上传数据需要应答（下层上传数据识别：目标地址为0）
  else if(  (1  ==  UDflag)               //下层上传数据标志
         &&(0x00	==	Frame->TargetAdd))	                  //目标地址为0
  {
    RS485ACKD.HeadCode	  =	RS485Head1;                     //头标识符
    RS485ACKD.TargetAdd	  =	Frame->SourceAdd;             	//目标地址
    RS485ACKD.SourceAdd 	=	0x00;               						//源地址
    RS485ACKD.Serial		  =	Frame->Serial;                  //流水号
    RS485ACKD.Cmd				  =	Frame->Cmd;                     //命令号
    RS485ACKD.UserCode	  =	Frame->UserCode;                //用户码
    RS485ACKD.Length		  =	0;                              //数据长度
    RS485ACKD.Bcc8	      =	BCC8(&(RS485ACKD.TargetAdd),6);		//校验码
    RS485ACKD.EndCode		  =	RS485end1;
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
HCResult WriteDataProcess(const unsigned char *buffer,const unsigned short length,const unsigned char UDflag)
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
	LayerAddr	=	Frame->Addr.LayerAddr;		  //下一级目标地址：如果下级地址为0，表示此消息是本板使用消息，存入RS485Node[0]
  if((TargetAdd ==  HCSYS.SwitchAddr)     //本板消息
    &&(0  ==  UDflag))                    //此消息为上层下发消息
  {
    memcpy(&(RS485Node[LayerAddr].data[0]),Frame,Frame->Length);   //复制数据到本地缓存
    if((0<LayerAddr)&&(0xFF>LayerAddr))   //此消息需要传递到下一层
    {
      ((RS485FrameDef*)(RS485Node[LayerAddr].data))->TargetAdd  = LayerAddr;        //目标地址
      ((RS485FrameDef*)(RS485Node[LayerAddr].data))->SourceAdd  = HCSYS.SwitchAddr; //源地址
      RS485Node[LayerAddr].data[Frame->Length]  = BCC8(RS485Node[LayerAddr].data,Frame->Length);  //重新计数校验
      RS485Node[LayerAddr].Length               = Frame->Length+1;    //加上校验位，总共需要发送的数据长度
    }
    res	=	RES_OK;
  }
  else if(1  ==  UDflag)      //底层上传数据：需要添加本层地址后待上传
  {
    memcpy(&(RS485Node[LayerAddr].data[0]),Frame,Frame->Length);      //复制数据到本地缓存
    ((RS485FrameDef*)(RS485Node[LayerAddr].data))->TargetAdd  = 0;    //目标地址
    ((RS485FrameDef*)(RS485Node[LayerAddr].data))->SourceAdd  = HCSYS.SwitchAddr;         //源地址
    ((RS485FrameDef*)(RS485Node[LayerAddr].data))->Addr.CabinetAddr  = HCSYS.SwitchAddr;  //加入本地址--单元板地址
    RS485Node[LayerAddr].data[Frame->Length]  = BCC8(RS485Node[LayerAddr].data,Frame->Length);  //重新计数校验
    RS485Node[LayerAddr].Length               = Frame->Length+1;    //加上校验位，总共需要发送的数据长度
    res	=	RES_OK;
  }
  else
  {
    res	= RES_UNKNOW;
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
	LayerAddr	=	Frame->Addr.LayerAddr;		  //下一级目标地址：如果下级地址为0，表示此消息是本板使用消息，存入RS485Node[0]
  if((TargetAdd ==  HCSYS.SwitchAddr)     //本板消息
    &&(0  ==  UDflag))                    //此消息为上层下发消息
  {
    memcpy(&(RS485Node[LayerAddr].data[0]),Frame,Frame->Length);   //复制数据到本地缓存
    if((0<LayerAddr)&&(0xFF>LayerAddr))   //此消息需要传递到下一层
    {
      ((RS485FrameDef*)(RS485Node[LayerAddr].data))->TargetAdd  = LayerAddr;        //目标地址
      ((RS485FrameDef*)(RS485Node[LayerAddr].data))->SourceAdd  = HCSYS.SwitchAddr; //源地址
      RS485Node[LayerAddr].data[Frame->Length]  = BCC8(RS485Node[LayerAddr].data,Frame->Length);  //重新计数校验
      RS485Node[LayerAddr].Length               = Frame->Length+1;    //加上校验位，总共需要发送的数据长度
    }
    res	=	RES_OK;
  }
  else if(1  ==  UDflag)      //底层上传数据：需要添加本层地址后待上传
  {
    memcpy(&(RS485Node[LayerAddr].data[0]),Frame,Frame->Length);      //复制数据到本地缓存
    ((RS485FrameDef*)(RS485Node[LayerAddr].data))->TargetAdd  = 0;    //目标地址
    ((RS485FrameDef*)(RS485Node[LayerAddr].data))->SourceAdd  = HCSYS.SwitchAddr;         //源地址
    ((RS485FrameDef*)(RS485Node[LayerAddr].data))->Addr.CabinetAddr  = HCSYS.SwitchAddr;  //加入本地址--单元板地址
    RS485Node[LayerAddr].data[Frame->Length]  = BCC8(RS485Node[LayerAddr].data,Frame->Length);  //重新计数校验
    RS485Node[LayerAddr].Length               = Frame->Length+1;    //加上校验位，总共需要发送的数据长度
    res	=	RES_OK;
  }
  else
  {
    res	= RES_UNKNOW;
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
HCResult LALayerDataProcess(const unsigned char *buffer,const unsigned short length,const unsigned char UDflag)
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
	LayerAddr	=	Frame->Addr.SlotAddr;		    //下一级目标地址：如果下级地址为0，表示此消息是本板使用消息，存入RS485Node[0]
  if((TargetAdd ==  HCSYS.SwitchAddr)     //本板消息
    &&(0  ==  UDflag))                    //此消息为上层下发消息
  {
    memcpy(&(RS485Node[LayerAddr].data[0]),Frame,Frame->Length);   //复制数据到本地缓存
    if((0<LayerAddr)&&(0xFF>LayerAddr))   //此消息需要传递到下一层
    {
      ((RS485FrameDef*)(RS485Node[LayerAddr].data))->TargetAdd  = LayerAddr;        //目标地址
      ((RS485FrameDef*)(RS485Node[LayerAddr].data))->SourceAdd  = HCSYS.SwitchAddr; //源地址
      RS485Node[LayerAddr].data[Frame->Length]  = BCC8(RS485Node[LayerAddr].data,Frame->Length);  //重新计数校验
      RS485Node[LayerAddr].Length               = Frame->Length+1;    //加上校验位，总共需要发送的数据长度
    }
    res	=	RES_OK;
  }
  else if(1  ==  UDflag)      //底层上传数据：需要添加本层地址后待上传
  {
    memcpy(&(RS485Node[LayerAddr].data[0]),Frame,Frame->Length);      //复制数据到本地缓存
    ((RS485FrameDef*)(RS485Node[LayerAddr].data))->TargetAdd  = 0;    //目标地址
    ((RS485FrameDef*)(RS485Node[LayerAddr].data))->SourceAdd  = HCSYS.SwitchAddr;         //源地址
    ((RS485FrameDef*)(RS485Node[LayerAddr].data))->Addr.LayerAddr  = HCSYS.SwitchAddr;    //加入本地址--层板地址
    RS485Node[LayerAddr].data[Frame->Length]  = BCC8(RS485Node[LayerAddr].data,Frame->Length);  //重新计数校验
    RS485Node[LayerAddr].Length               = Frame->Length+1;    //加上校验位，总共需要发送的数据长度
    res	=	RES_OK;
  }
  else
  {
    res	= RES_UNKNOW;
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
	LayerAddr	=	Frame->Addr.SlotAddr;		    //下一级目标地址：如果下级地址为0，表示此消息是本板使用消息，存入RS485Node[0]
  if((TargetAdd ==  HCSYS.SwitchAddr)     //本板消息
    &&(0  ==  UDflag))                    //此消息为上层下发消息
  {
    memcpy(&(RS485Node[0].data[0]),Frame,Frame->Length);   //复制数据到本地缓存
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
HCResult DataCheck(const unsigned char *buffer,const unsigned short length,const unsigned char UDflag)
{
  HCResult	res	=	RES_OK;
  RS485FrameDef   *Frame    = NULL;
  unsigned char   Bcc8      = 0;    //校验码
  unsigned short  BassAddr  = 0;    //找到头标识符在输入数组中的偏移地址
  if(NULL ==  buffer)		//空地址
  {
    return RES_NODATA;
  }
  Frame	=	(RS485FrameDef*)memchr(buffer,RS485Head1,length);		//查找RS485Head1头标识符
  if(NULL == Frame)         //未找到头标识符
  {
    return RES_FARMERR;     //帧格式错误
  }
  if(Frame->Length>=length) //数据长度校验(消息长度==Frame->Length+1字节校验位)
  {
    return RES_FARMERR;     //帧格式错误
  }  
  Bcc8  = BCC8((unsigned char*)Frame,Frame->Length);      //固定长度为7（从RS485Head到End校验）  
  if(Bcc8 ==  ((unsigned char*)Frame)[Frame->Length+1])   //校验位在消息尾端，不计算在消息长度内
  {
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
    else                        //发送缓冲区无数据，检查数据队列中有没待发送数据
    {
      for(i	=	0;i<MaxNetPerLayer;i++) //遍历
      {
        if(RS485Node[i].Length)
        {
          if(0x00 ==  RS485Node[i].data[1])   //目标地址为0表示上传
          {
            memcpy(TransU.data,RS485Node[i].data,RS485Node[i].Length);
            memcpy(buffer,RS485Node[i].data,RS485Node[i].Length);
            
            TransU.Length = RS485Node[i].Length;
            TransU.Retry.Retry  = 0;
            TransU.Retry.Time   = 0;
            RS485Node[i].Length = 0;    //清除缓存数据标志
            return TransU.Length;
          }
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
				unsigned char TargetAdd	=	TransD.data[1];
				memcpy(&RS485Node[TargetAdd].data[0],&TransD.data[0],15);
//				RS485Node[TargetAdd].data[0]   	= RS485Head1;       	//头标识
				RS485Node[TargetAdd].data[1]   	= 0x00;             	//目标地址--
				RS485Node[TargetAdd].data[2]   	= HCSYS.SwitchAddr; 	//源地址
//				RS485Node[TargetAdd].data[3]   	= TransD.data[3]+1; 		//流水号
				RS485Node[TargetAdd].data[4]   	= TransD.data[4]|0x80; 		//命令号
//				RS485Node[TargetAdd].data[4]   	= 0x84; 		//命令号
//				RS485Node[TargetAdd].data[5]   	= TransD.data[5]; 		//用户码
//				RS485Node[TargetAdd].data[6]   	= TransD.data[6]; 		//地址+状态码+数据长度
				RS485Node[TargetAdd].data[6]   	= 6; 										//地址+状态码+数据长度
//				RS485Node[TargetAdd].data[7]   	= TransD.data[7]; 		//柜地址(单元柜号)  下行时为柜地址，上行时，柜地址为0x00）
//				RS485Node[TargetAdd].data[8]   	= TransD.data[8]; 		//层地址
//				RS485Node[TargetAdd].data[9]   	= TransD.data[9]; 		//槽地址(终端地址)
//				RS485Node[TargetAdd].data[10]  	= TransD.data[10]; 		//状态码
				RS485Node[TargetAdd].data[10]		=	Err_FAULT_ILLAGALPARA;					//错误码
//				RS485Node[TargetAdd].data[11]		=	0x00;
//				RS485Node[TargetAdd].data[12]		=	0x00;
//				RS485Node[TargetAdd].data[6]		=	6;
//				RS485Node[TargetAdd].data[5]   	= 0x0D; 		//用户码
				
				/*	连接超时：超时时，返回超时单元地址
				switch(HCSYS.Layer)
				{
					case CALayer:	//单元板
												RS485Node[TargetAdd].data[9]   	= 0x00; 		//槽地址(终端地址)
						break;
					case MBLayer:	//层板
												RS485Node[TargetAdd].data[8]   	= TransD.data[8]; 		//层地址
												RS485Node[TargetAdd].data[9]   	= 0x00; 		//槽地址(终端地址)
						break;			
					default:break;
				}
				*/
				RS485Node[TargetAdd].data[13]		=	BCC8(&(RS485Node[TargetAdd].data[1]),12);
				RS485Node[TargetAdd].data[14]		=	RS485end1;				
				RS485Node[TargetAdd].Length			=	15;
				TransD.Length	=	0;
			}
      return Length;
    }
    else                        //发送缓冲区无数据，检查数据队列中有没待发送数据
    {
      for(i	=	0;i<MaxNetPerLayer;i++) //遍历
      {
        if(RS485Node[i].Length)
        {
          if(0x00 !=  RS485Node[i].data[1])   //目标地址不为0表示为下发数据
          {
            memcpy(TransD.data,RS485Node[i].data,RS485Node[i].Length);
            memcpy(buffer,RS485Node[i].data,RS485Node[i].Length);
            
            TransD.Length = RS485Node[i].Length;
            TransD.Retry.Retry  = 0;
            TransD.Retry.Time   = 0;
            RS485Node[i].Length = 0;    //清除缓存数据标志
            return TransD.Length;
          }
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














