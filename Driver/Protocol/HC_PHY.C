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
HCResult SetDataProcess(const unsigned char *buffer,const unsigned short length,const unsigned char UDflag)
{
	HCResult	res	=	RES_OK;
//  RS485FrameDef *Frame  = (RS485FrameDef*)buffer;
  if(NULL ==  buffer)
  {
    return RES_ERROR;
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
	//===================================RS232数据协议（网关板）
	if(	(RS232Head1	==	buffer[0])		//0xFA
		&&(RS232Head2	==	buffer[1]))		//0xF5
	{
	}
	//===================================RS485数据协议
	else if(RS485Head1	==	buffer[0])		//0x7E RS485通讯协议头标识符
	{
    //-----------------------------------设置应答数据
    res	=	AddACKRS485(buffer,length,UDflag);
		res	=	AddDataRS485(buffer,length,UDflag);
	}
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
    return RES_ERROR;
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
    RS485ACKU.Bcc8	      =	BCC8(&RS485ACKU.TargetAdd,6);		//校验码
    RS485ACKU.EndCode		  =	RS485end1;
  }
  //===================================下层上传数据需要应答（下层上传数据识别：目标地址为0）
  else if(  (1  ==  UDflag)               //下层上传数据标志
         &&(0x00	==	Frame->TargetAdd))	                  //目标地址为0
  {
    RS485ACKD.HeadCode	  =	RS485Head1;                     //头标识符
    RS485ACKD.TargetAdd	  =	0x00;                           //目标地址
    RS485ACKD.SourceAdd 	=	HCSYS.SwitchAddr;               //源地址
    RS485ACKD.Serial		  =	Frame->Serial;                  //流水号
    RS485ACKD.Cmd				  =	Frame->Cmd;                     //命令号
    RS485ACKD.UserCode	  =	Frame->UserCode;                //用户码
    RS485ACKD.Length		  =	0;                              //数据长度
    RS485ACKD.Bcc8	      =	BCC8(&RS485ACKU.TargetAdd,6);		//校验码
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
HCResult AddDataRS485(const unsigned char *buffer,const unsigned short length,const unsigned char UDflag)
{
	HCResult	res	=	RES_OK;
  RS485FrameDef *Frame  = (RS485FrameDef*)buffer;
  unsigned char *Address  = (unsigned char*)&(Frame->Addr.CabinetAddr);
  if(NULL ==  buffer)		//空地址
  {
    return RES_ERROR;
  }
  if(length<=AckDataLen) //应答消息
  {
    
  }
	//===================================上层下发数据：目标地址与本地址相符，UDflag==0
  if((0==UDflag)&&(Frame->TargetAdd==HCSYS.SwitchAddr))		//上层下发数据              
  {    
    //-----------------------------------单元板级:转发目标地址为层地址，按层地址将数据包存入相应缓冲数组
    if(	SALayer	>	HCSYS.Layer)	        //非最低层板，如果缓存为空，将数据存入缓存数组待转发，如果非空，报忙或者等待状态
    {
      //-----------------------------------将要转发给下级的目标地址
      Frame->TargetAdd	=	Address[HCSYS.Layer]-1;		  //目标地址  
      if(0x00	==	RS485Node[Frame->TargetAdd].Length)				//数组缓存中下级目标地址为0表示缓存空
      {	
        RS485Node[Frame->TargetAdd].data[0]   = RS485Head1;                   //头标识
        RS485Node[Frame->TargetAdd].data[1]   = Address[HCSYS.Layer];         //目标地址
        RS485Node[Frame->TargetAdd].data[2]   = 0x00;                         //源地址
        RS485Node[Frame->TargetAdd].data[3]   = Frame->Serial;                //流水号
        RS485Node[Frame->TargetAdd].data[4]   = Frame->Cmd;                   //命令号
        RS485Node[Frame->TargetAdd].data[5]   = Frame->UserCode;              //用户码
        RS485Node[Frame->TargetAdd].data[6]   = Frame->Length;                //地址+状态码+数据长度
        RS485Node[Frame->TargetAdd].data[7]   = Frame->Addr.CabinetAddr;      //柜地址(单元柜号)  下行时为柜地址，上行时，柜地址为0x00）
        RS485Node[Frame->TargetAdd].data[8]   = Frame->Addr.LayerAddr;        //层地址
        RS485Node[Frame->TargetAdd].data[9]   = Frame->Addr.SlotAddr;         //槽地址(终端地址)
        RS485Node[Frame->TargetAdd].data[10]  = Frame->StsCode;               //状态码
        //---------------------------------拷贝数据
        memcpy(&RS485Node[Frame->TargetAdd].data[11],Frame->data,Frame->Length-4);  //复制数据
        RS485Node[Frame->TargetAdd].data[Frame->Length-4+7] = BCC8(&RS485Node[Frame->TargetAdd].data[1],(Frame->Length+6));   //校验码
        RS485Node[Frame->TargetAdd].data[Frame->Length-4+8] = RS485end1;      //结束符

        RS485Node[Frame->TargetAdd].Length  =	Frame->Length-4+9;
      }
      else				//数组缓存有数据未处理完---报忙或者等待状态
      {					
//					Frame->SourceAdd	=	Frame->TargetAdd;	//b2源地址 下发为0x00，上传为本地址
//					Frame->TargetAdd	=	0x00;		//b1目标地址（暂时理解为单元柜地址）下发为接收地址，上传为0x00
//					Frame->Cmd				=	(CmdDef)((unsigned char)Frame->Cmd|0x80);
//					Frame->StsCode		=	eBoxBusy;
//					Frame->Length			=	BascDataLen;				//基础数据长度（地址+状态）
//					Frame->data[(Frame->Length)-BascDataLen]		=	BCC8(&(Frame->TargetAdd),HeadDataLen+Frame->Length-3);		//校验码
//					Frame->data[(Frame->Length)-BascDataLen+1]	=	RS485end1;					//结束符
//					memcpy(&TransU.data,Frame,HeadDataLen+Frame->Length);						//数据复制到发送缓冲区
//          TransU.Length = HeadDataLen+Frame->Length;
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
  //===================================下层上传数据：目标地址为0，UDflag==1
  else if((1==UDflag)&&(Frame->TargetAdd==0))             //下层上传数据
  {
    if(0x00	==	RS485Node[Frame->TargetAdd].Length)				//数组缓存中下级目标地址为0表示缓存空
    {	
      RS485Node[Frame->TargetAdd].data[0]   = RS485Head1;                   //头标识
      RS485Node[Frame->TargetAdd].data[1]   = 0x00;                         //目标地址--
      RS485Node[Frame->TargetAdd].data[2]   = HCSYS.SwitchAddr;             //源地址
      RS485Node[Frame->TargetAdd].data[3]   = Frame->Serial;                //流水号
      RS485Node[Frame->TargetAdd].data[4]   = Frame->Cmd;                   //命令号
      RS485Node[Frame->TargetAdd].data[5]   = Frame->UserCode;              //用户码
      RS485Node[Frame->TargetAdd].data[6]   = Frame->Length;                //地址+状态码+数据长度
      RS485Node[Frame->TargetAdd].data[7]   = Frame->Addr.CabinetAddr;      //柜地址(单元柜号)  下行时为柜地址，上行时，柜地址为0x00）
      RS485Node[Frame->TargetAdd].data[8]   = Frame->Addr.LayerAddr;        //层地址
      RS485Node[Frame->TargetAdd].data[9]   = Frame->Addr.SlotAddr;         //槽地址(终端地址)
      RS485Node[Frame->TargetAdd].data[10]  = Frame->StsCode;               //状态码
      RS485Node[Frame->TargetAdd].data[HCSYS.Layer+6] = HCSYS.SwitchAddr;   //加入本层地址码
      //---------------------------------拷贝数据
      memcpy(&RS485Node[Frame->TargetAdd].data[11],Frame->data,Frame->Length-4);  //复制数据
      RS485Node[Frame->TargetAdd].data[Frame->Length-4+7] = BCC8(&RS485Node[Frame->TargetAdd].data[1],(Frame->Length+6));   //校验码
      RS485Node[Frame->TargetAdd].data[Frame->Length-4+8] = RS485end1;      //结束符

      RS485Node[Frame->TargetAdd].Length  =	Frame->Length-4+9;
    }
    else
    {
    }
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
            memcpy(TransU.data,RS485Node[i].data,RS485Node[i].Length);
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














