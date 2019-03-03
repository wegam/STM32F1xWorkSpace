#ifdef AMPLCDV11

#include "AMPLCDV11.H"




#include "AMP_LAY.H"
#include "AMP_CABV11.H"

#include "STM32_GPIO.H"
#include "STM32_SYSTICK.H"
#include "STM32_WDG.H"
#include "STM32_PWM.H"

#include "LCD.H"
#include "ST7789V.H"

LCDDef	sLCD;

unsigned  long*  MCUMEMaddr = (unsigned  long*)(0x1FFFF7E0);
unsigned  short  MCUMEMsize  = 0;

unsigned  char gCbFlag=0;   //0--柜板，1--层板
unsigned short colr=0;
/*******************************************************************************
*函数名			:	function
*功能描述		:	function
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
void AMPLCDV11_Configuration(void)
{	
  GPIO_Configuration_OPP50(SYSLEDPort,SYSLEDPin);
  
  PWM_OUT(TIM2,PWM_OUTChannel2,500,10);	//PWM设定-20161127版本	占空比1/1000

  LCD_Configuration();
  
  IWDG_Configuration(1000);													//独立看门狗配置---参数单位ms
  
  SysTick_Configuration(1000);    //系统嘀嗒时钟配置72MHz,单位为uS
  
  while(1)
  {
    //AMPLCDV11_Loop();
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
void AMPLCDV11_Server(void)
{  
  colr+=9;
	IWDG_Feed();								//独立看门狗喂狗
	Tim_Server();
  ST7789V_Test(LCD565_RED);
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
void AMPLCDV11_Loop(void)
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

/*******************************************************************************
* 函数名			:	function
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
void LCD_Configuration(void)
{
	SPIDef	*SPI	=	&sLCD.GT32L32.SPI;
	sLCD.Port.sBL_PORT				=	GPIOC;
	sLCD.Port.sBL_Pin					=	GPIO_Pin_0;
	
	sLCD.Port.sRD_PORT				=	GPIOD;
	sLCD.Port.sRD_Pin					=	GPIO_Pin_2;	
	
//	sLCD.Port.sREST_PORT			=	GPIOC;
//	sLCD.Port.sREST_Pin				=	GPIO_Pin_2;
	
	sLCD.Port.sDC_PORT				=	GPIOC;
	sLCD.Port.sDC_Pin					=	GPIO_Pin_11;
	
	sLCD.Port.sWR_PORT				=	GPIOC;
	sLCD.Port.sWR_Pin					=	GPIO_Pin_12;	
	
//	sLCD.Port.sTE_PORT				=	GPIOC;
//	sLCD.Port.sTE_Pin					=	GPIO_Pin_5;
	
	sLCD.Port.sCS_PORT				=	GPIOC;
	sLCD.Port.sCS_Pin					=	GPIO_Pin_10;
	
	sLCD.Port.sDATABUS_PORT		=	GPIOB;
	sLCD.Port.sDATABUS_Pin		=	GPIO_Pin_All;	
	
	sLCD.Flag.Rotate	=	Draw_Rotate_180D;		//使用旋转角度
	
	SPI->Port.SPIx		=	SPI1;
	SPI->Port.CS_PORT	=	GPIOA;
	SPI->Port.CS_Pin	=	GPIO_Pin_4;
	SPI->Port.SPI_BaudRatePrescaler_x=SPI_BaudRatePrescaler_2;
	
	ST7789V_Initialize(&sLCD);
}
#endif
