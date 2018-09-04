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
unsigned char RS485BufferRU[1024]={0};		//上级数据接收缓存
unsigned char RS485BufferTU[1024]={0};		//向上级发送数据缓存
unsigned char RS485BufferRD[1024]={0};		//下级数据接收缓存
//unsigned char RS485BufferTD[1024]={0};
unsigned char RS232BufferU[1024]={0};
unsigned char RS232BufferD[1024]={0};

unsigned char	SerialU	=	0;							  //往上层上传流水号 0x01~0x7D 每次使用后加1(为了不与起始符和结束符冲突，流水号最大值为0x7D)
unsigned char	SerialD	=	0;							  //往下层下发流水号 0x01~0x7D 每次使用后加1(为了不与起始符和结束符冲突，流水号最大值为0x7D)

StepDef UWORKSTEP;											  //往上级接口传送数据步骤
StepDef DWORKSTEP[MaxNetPerLayer]={0};	  //下级接口工作步骤
RS485NodeDef	RS485Node[MaxNetPerLayer];	//目标地址数据数组--按目标地址排序(缓存数组从0开始，目标地址从1开始）

RS485NodeDef	RS485ACKU;									//响应上级的应答
RS485NodeDef	RS485ACKD;									//响应下级的应答
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
	if(0	==	flag)	//0-获取响应上级的应答
	{
		Length	=	RS485ACKU.NodeLength;
		if(0	!=	Length)
		{			
			memcpy(buffer,&RS485ACKU.Frame,Length);
			RS485ACKU.NodeLength	=	0;
		}
	}
	else						//1-获取响应下级的应答
	{
		Length	=	RS485ACKD.NodeLength;
		if(0	!=	Length)
		{			
			memcpy(buffer,&RS485ACKD.Frame,Length);
			RS485ACKD.NodeLength	=	0;
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
//		unsigned char GetAddr	=	0x00;
		unsigned char	i	=	0;
		RS485NodeDef	*FrameNode	=	RS485Node;
		RS485FrameDef *Frame  		= &FrameNode->Frame;
//		unsigned char *Address  	= (unsigned char*)&(Frame->Addr.CabinetAddr);	//指向地址域
		//===================================清空所有数据
		memset(RS485Node,0x00,sizeof(RS485Node));		//清空网络缓存
		//===================================组装数据
		for(i	=	0;i<MaxNetPerLayer;i++)
		{
			//-----------------------------------获取地址
			Frame		=	&(RS485Node[i].Frame);			//结点内RS485格式数据起始地址
//			Address	= (unsigned char*)&(Frame->Addr.CabinetAddr);	//指向地址域
			//-----------------------------------组装数据
			Frame->RS485Head	=	RS485Head1;			//485起始符
			Frame->TargetAdd	=	i+1;						//目标地址
			Frame->SourceAdd	=	0x00;						//源地址
			Frame->Serial			=	0x01;						//流水号
			Frame->Cmd				=	CMD_GET_ADDR;		//获取地址命令
			Frame->UserCode		=	0x00;						//用户码
			Frame->Length			=	BascDataLen;		//数据长度
	//		Address[HCSYS.Layer-1]	=	HCSYS.SwitchAddr;	//当前层地址
	//		Address[HCSYS.Layer]		=	i+1;			//目标地址
	//		Frame->Addr.CabinetAddr	=	0x00;			//单元地址
	//		Frame->Addr.LayerAddr		=	0x00;			//层地址
	//		Frame->Addr.SlotAddr		=	0x00;			//驱动层地址
			Frame->StsCode		=	eNoErr;					//状态码
			Frame->data[0]		=	BCC8(&(Frame->TargetAdd),sizeof(RS485FrameDef)-3-BusDataSize+Frame->Length);	//计算校验码
			Frame->data[1]		=	RS485end1;			//结束符
			//-----------------------------------标记当前数据包总长度
			RS485Node[i].NodeLength	=	HeadDataLen+BascDataLen;				//此结点存储的有效数据长度
		}
	}
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
HCResult SetDataProcess(const unsigned char *buffer,unsigned short length)
{
	HCResult	res	=	RES_OK;
//  RS485FrameDef *Frame  = (RS485FrameDef*)buffer;
  if(NULL ==  buffer)
  {
    return RES_ERROR;
  }
	//===================================RS232数据协议（网关板）
	if(	(RS232Head1	==	buffer[0])		//0xFA
		&&(RS232Head2	==	buffer[1]))		//0xF5
	{
	}
	//===================================RS485数据协议
	else if(RS485Head1	==	buffer[0])		//0x7E	//检查目标地址与本地址是否匹配
	{
		res	=	SetDataRS485(buffer,length);
	}
	//===================================其它跳过协议和地址的命令（透传）
	
//  if(ePro485Head  ==  Frame->Head)    //RS485通讯头标识
//  {
//    //===================================检查数据为上级下发还是下级上传
//    if(0x80 ==  (((char)Frame->Cmd)&0x80))    //bit7为1表示下级上传
//    {
//    }
//    else    //上层下发
//    {
//      unsigned char *Address  = (unsigned char*)&(Frame->Addr.CabinetAddr);
////      if(Address[HCSYS.AddrBase]  ==  HCSYS.Addr)   //判断地址是否符合本板地址
//      if(Frame->TargetAdd  ==  HCSYS.Addr)            //判断地址是否符合本板地址
//      {
//         //------------------------------检查缓存是否有待处理数据
//        if()
//        {
//        }
//      }
//    }
//  }
	//=====================================转发上层数据

	//=====================================转发下级数据
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
HCResult SetDataRS485(const unsigned char *buffer,unsigned short length)
{
	HCResult	res	=	RES_OK;
  RS485FrameDef *Frame  = (RS485FrameDef*)buffer;
  if(NULL ==  buffer)		//空地址
  {
    return RES_ERROR;
  }
	AddDataRS485(buffer,length);
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
HCResult AddACKRS485(const unsigned char *buffer,unsigned short length)
{
	HCResult	res	=	RES_OK;
  RS485FrameDef *Frame  = (RS485FrameDef*)buffer;
  if(NULL ==  buffer)		//空地址
  {
    return RES_ERROR;
  }
	//===================================此数据为下级上传数据（目标地址为0）
		if(0x00	==	Frame->TargetAdd)
		{
		}
		//===================================此数据为上级下发数据（目标地址不为0）根据子地址将数据存入相应数组
		else if(HCSYS.SwitchAddr	==	Frame->TargetAdd)		//目标地址与本拨码地址一致
		{
			unsigned char *Address  = (unsigned char*)&(Frame->Addr.CabinetAddr);
			unsigned char TargetAddr	=	0;			//目标地址---目标缓存（目标地址-1）
			unsigned short Length 		= 0;			//缓存内数据长度不为0表示有数据
			//-----------------------------------将要转发给下级的目标地址
			Frame->TargetAdd	=	Address[HCSYS.Layer];											//目标地址
			Length	=	RS485Node[Frame->TargetAdd-1].NodeLength;	//节点内存储的下级目标地址
			
			RS485ACKU.Frame.RS485Head	=	ePro485Head;
			RS485ACKU.Frame.TargetAdd	=	0x00;
			RS485ACKU.Frame.SourceAdd	=	HCSYS.SwitchAddr;
			RS485ACKU.Frame.Serial		=	Frame->Serial;
			RS485ACKU.Frame.Cmd				=	Frame->Cmd;
			RS485ACKU.Frame.UserCode	=	Frame->UserCode;
			RS485ACKU.Frame.Length		=	0;
			RS485ACKU.Frame.Addr.CabinetAddr	=	BCC8(&RS485ACKU.Frame.TargetAdd,6);		//校验码
			RS485ACKU.Frame.Addr.LayerAddr		=	ePro485End;
			RS485ACKU.NodeLength	=	9;
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
HCResult AddDataRS485(const unsigned char *buffer,unsigned short length)
{
	HCResult	res	=	RES_OK;
  RS485FrameDef *Frame  = (RS485FrameDef*)buffer;
  if(NULL ==  buffer)		//空地址
  {
    return RES_ERROR;
  }
	//===================================此数据为下级上传数据（目标地址为0）
		if(0x00	==	Frame->TargetAdd)
		{
		}
		//===================================此数据为上级下发数据（目标地址不为0）根据子地址将数据存入相应数组
		else if(HCSYS.SwitchAddr	==	Frame->TargetAdd)		//目标地址与本拨码地址一致
		{
			unsigned char *Address  = (unsigned char*)&(Frame->Addr.CabinetAddr);
			//-----------------------------------单元板级:转发目标地址为层地址，按层地址将数据包存入相应缓冲数组
			if(	SALayer	>	HCSYS.Layer)	//非最低层板，如果缓存为空，将数据存入缓存数组待转发，如果非空，报忙或者等待状态
			{
				unsigned char TargetAddr	=	0;			//目标地址---目标缓存（目标地址-1）
				unsigned short Length 		= 0;			//缓存内数据长度不为0表示有数据
				//-----------------------------------将要转发给下级的目标地址
				Frame->TargetAdd	=	Address[HCSYS.Layer];											//目标地址
				Length	=	RS485Node[Frame->TargetAdd-1].NodeLength;	//节点内存储的下级目标地址
				
				RS485ACKU.Frame.RS485Head	=	ePro485Head;
				RS485ACKU.Frame.TargetAdd	=	0x00;
				RS485ACKU.Frame.SourceAdd	=	HCSYS.SwitchAddr;
				RS485ACKU.Frame.Serial		=	Frame->Serial;
				RS485ACKU.Frame.Cmd				=	Frame->Cmd;
				RS485ACKU.Frame.UserCode	=	Frame->UserCode;
				RS485ACKU.Frame.Length		=	0;
				RS485ACKU.Frame.Addr.CabinetAddr	=	BCC8(&RS485ACKU.Frame.TargetAdd,6);		//校验码
				RS485ACKU.Frame.Addr.LayerAddr		=	ePro485End;
				RS485ACKU.NodeLength	=	9;
				
				if(0x00	==	Length)				//数组缓存中下级目标地址为0表示缓存空
				{					
					Frame->SourceAdd														=	0x00;										//下发时源地址为0x00
					Frame->data[(Frame->Length)-BascDataLen]		=	BCC8(&(Frame->TargetAdd),HeadDataLen+Frame->Length-3);		//校验码
					Frame->data[(Frame->Length)-BascDataLen+1]	=	RS485end1;				//结束符
					RS485Node[Frame->TargetAdd-1].NodeLength		=	HeadDataLen+Frame->Length;
					memcpy(&RS485Node[Frame->TargetAdd-1].Frame,Frame,length);	//存入下级目标数组缓存--待发送(缓存数组从0开始，目标地址从1开始）					
				}
				else				//数组缓存有数据未处理完---报忙或者等待状态
				{					
					Frame->SourceAdd	=	Frame->TargetAdd;	//b2源地址 下发为0x00，上传为本地址
					Frame->TargetAdd	=	0x00;		//b1目标地址（暂时理解为单元柜地址）下发为接收地址，上传为0x00
					Frame->Cmd				=	(CmdDef)((unsigned char)Frame->Cmd|0x80);
					Frame->StsCode		=	eBoxBusy;
					Frame->Length			=	BascDataLen;				//基础数据长度（地址+状态）
					Frame->data[(Frame->Length)-BascDataLen]		=	BCC8(&(Frame->TargetAdd),HeadDataLen+Frame->Length-3);		//校验码
					Frame->data[(Frame->Length)-BascDataLen+1]	=	RS485end1;					//结束符
					memcpy(RS485BufferTU,Frame,HeadDataLen+Frame->Length);						//数据复制到发送缓冲区
				}
			}
			//-----------------------------------驱动层
			else		//最底层板，保存数据，待处理
			{
				Frame->TargetAdd	=	Address[HCSYS.Layer];					//目标地址
				Frame->SourceAdd	=	0x00;													//下发时源地址为0x00
				Frame->data[(Frame->Length)-4]		=	BCC8(&(Frame->TargetAdd),sizeof(RS485FrameDef)-3-BusDataSize+Frame->Length);		//校验码
				Frame->data[(Frame->Length)-4+1]	=	RS485end1;			//结束符
				memcpy(&RS485Node[Frame->TargetAdd-1],Frame,length);		//存入数据--待发送(缓存数组从0开始，目标地址从1开始）
			}
		}
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
unsigned short GetDataProcess(unsigned char *buffer)
{
	unsigned short Length = 0;
	unsigned char	i	=	0;
	for(i	=	0;i<MaxNetPerLayer;i++)
	{
		if(RS485Node[i].NodeLength)
		{
			Length	=	RS485Node[i].NodeLength;
			memcpy(buffer,(unsigned char*)&RS485Node[i].Frame,Length);
			RS485Node[i].NodeLength	=	0;
			return Length;
		}
	}
	//=====================================转发上层数据
	//=====================================转发下级数据
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














