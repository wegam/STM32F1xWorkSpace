





#include "HC_PHY.H"
#include "STM32_USART.H"

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

unsigned char	SerialU	=	0;							//往上层上传流水号 0x01~0x7D 每次使用后加1(为了不与起始符和结束符冲突，流水号最大值为0x7D)
unsigned char	SerialD	=	0;							//往下层下发流水号 0x01~0x7D 每次使用后加1(为了不与起始符和结束符冲突，流水号最大值为0x7D)

StepDef UWORKSTEP;											//往上级接口传送数据步骤
StepDef DWORKSTEP[MaxNetPerLayer]={0};	//下级接口工作步骤
RS485FrameDef	RS485Node[MaxNetPerLayer];

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
HCResult UMFrameProcess(void)
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
HCResult DMFrameProcess(void)
{
	HCResult	res	=	RES_OK;

	//=====================================转发上层数据

	//=====================================转发下级数据
	return res;
}














