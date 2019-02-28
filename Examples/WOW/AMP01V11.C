#ifdef AMP01V11


#include "AMP01V11.H"
#include "AMP_LAY.H"
#include "AMP_CABV11.H"

#include "STM32_GPIO.H"
#include "STM32_SYSTICK.H"
#include "STM32_WDG.H"


unsigned  long*  MCUMEMaddr = (unsigned  long*)(0x1FFFF7E0);
unsigned  short  MCUMEMsize  = 0;

unsigned  char gCbFlag=0;   //0--柜板，1--层板

/*******************************************************************************
*函数名			:	function
*功能描述		:	function
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
void AMP01V11_Configuration(void)
{	
  MCUMEMsize  = *MCUMEMaddr;
  if(MCUMEMsize>=0x0100) //256K Flash 柜控制板STM32F103RC
  {
    gCbFlag=0;  //0--柜板，1--层板

    AMP_CABV11_Configuration();
  }
  else if(0x0080 ==  MCUMEMsize) //128K Flash 层控制板STM32F103CB
  {
    gCbFlag=1;  //0--柜板，1--层板

    AMPLAY_Configuration();
  }

  GPIO_Configuration_OPP50(SYSLEDPort,SYSLEDPin);

  IWDG_Configuration(1000);													//独立看门狗配置---参数单位ms
  
  SysTick_Configuration(1000);    //系统嘀嗒时钟配置72MHz,单位为uS
  
  while(1)
  {
    AMP01V11_Loop();
  }
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
void AMP01V11_Server(void)
{  
	IWDG_Feed();								//独立看门狗喂狗
	Tim_Server();
  if(gCbFlag) //0--柜板，1--层板
  {
    AMPLAY_Server();
  }
  else
  {
    AMP_CABV11_Server();
  }
}
/*******************************************************************************
*函数名			:	MainBoard_Server
*功能描述		:	主柜空闲服务程序
              1-查询在线设备
              2-查询副柜有无数据上传
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
void AMP01V11_Loop(void)
{  
  if(gCbFlag) //0--柜板，1--层板
  {
    AMPLAY_Loop();
  }
  else
  {
    AMP_CABV11_Loop();
  }
}









//=================================软件接口End=============================================================



/*******************************************************************************
*函数名			:	function
*功能描述		:	function
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
unsigned short HW_SendBuff(enCCPortDef Port,unsigned char* pBuffer,unsigned short length)
{ 
  unsigned  short   sendedlen = 0;
  if(gCbFlag) //0--柜板，1--层板
  {
    sendedlen = AMPLAY_SendBuff(Port,pBuffer,length);
  }
  else
  {
    sendedlen = AMPCAB_SendBuff(Port,pBuffer,length);
  }
  return  sendedlen;
}




//=================================硬件接口End=============================================================


//=================================配置函数End=============================================================


//=================================时间函数ST==============================================================

/*******************************************************************************
*函数名			:	function
*功能描述		:	function
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
void Tim_Server(void)
{
  //----------------PC发送
  if(AMPPro.Time.PcSendTime>0)
  {
    AMPPro.Time.PcSendTime--;
  }
  //----------------柜发送
  if(AMPPro.Time.CabSendTime>0)
  {
    AMPPro.Time.CabSendTime--;
  }
  //----------------层发送
  if(AMPPro.Time.LaySendTime>0)
  {
    AMPPro.Time.LaySendTime--;
  }
  //----------------读卡器发送
  if(AMPPro.Time.CardSendTime>0)
  {
    AMPPro.Time.CardSendTime--;
  }
  //----------------锁
  if(AMPPro.Time.LockTime>0)
  {
    AMPPro.Time.LockTime--;
  }
  //----------------拨码
  if(AMPPro.Time.swicthidtime>0)
  {
    AMPPro.Time.swicthidtime--;
  }
  //----------------运行指示灯
  if(AMPPro.Time.SYSLEDTime>0)
  {
    AMPPro.Time.SYSLEDTime--;
  }
}
#endif
