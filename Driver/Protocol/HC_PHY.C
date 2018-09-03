





#include "HC_PHY.H"
#include "STM32_USART.H"
#include "TOOL.H"		//数据校验工具



#include	"stdio.h"			//用于printf
#include	"string.h"		//用于printf
#include	"stdarg.h"		//用于获取不确定个数的参数
#include	"stdlib.h"		//malloc动态申请内存空间

#define	MaxNetPerLayer	64			//每个结点所连接的最大支点数

//#include "STM32_GPIO.H"
//#include "STM32_SYS.H"
//#include "STM32_SYSTICK.H"
//#include "STM32_WDG.H"
//#include "STM32_USART.H"
//#include "STM32_PWM.H"

//#include "string.h"				//串和内存操作函数头文件
//#include "stm32f10x_dma.h"

//#define BufferSize	512
unsigned char RS485BufferU[1024]={0};
unsigned char RS485BufferD[1024]={0};
unsigned char RS232BufferU[1024]={0};
unsigned char RS232BufferD[1024]={0};

unsigned char	SerialU	=	0;							  //往上层上传流水号 0x01~0x7D 每次使用后加1(为了不与起始符和结束符冲突，流水号最大值为0x7D)
unsigned char	SerialD	=	0;							  //往下层下发流水号 0x01~0x7D 每次使用后加1(为了不与起始符和结束符冲突，流水号最大值为0x7D)

StepDef UWORKSTEP;											  //往上级接口传送数据步骤
StepDef DWORKSTEP[MaxNetPerLayer]={0};	  //下级接口工作步骤
RS485FrameDef	RS485Node[MaxNetPerLayer];
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
	HCResult	res	  =	RES_OK;
  HCSYS.AddrBase  = buffer[0];
  HCSYS.Addr      = buffer[1];
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
HCResult DataProcessSet(const unsigned char *buffer,unsigned short length)
{
	HCResult	res	=	RES_OK;
  RS485FrameDef *Frame  = (RS485FrameDef*)buffer;
  if(NULL ==  buffer)
  {
    return RES_ERROR;
  }
  if(ePro485Head  ==  Frame->Head)    //RS485通讯头标识
  {
    //===================================检查数据为上级下发还是下级上传
    if(0x80 ==  (((char)Frame->Cmd)&0x80))    //bit7为1表示下级上传
    {
    }
    else    //上层下发
    {
      unsigned char *Address  = (unsigned char*)&(Frame->Addr.CabinetAddr);
//      if(Address[HCSYS.AddrBase]  ==  HCSYS.Addr)   //判断地址是否符合本板地址
      if(Frame->TargetAdd  ==  HCSYS.Addr)            //判断地址是否符合本板地址
      {
         //------------------------------检查缓存是否有待处理数据
        if()
        {
        }
      }
    }
  }
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
unsigned short DataProcessGet(unsigned char *buffer)
{
	unsigned short Length = 0;

	//=====================================转发上层数据
  buffer[0] = 1;
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














