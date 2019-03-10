#ifdef AMPLCDV11

#include "AMPLCDV11.H"



#include	"AMP_PHY.H"
//#include "AMP_LAY.H"
//#include "AMP_CABV11.H"

#include "STM32_SYS.H"
#include "STM32_GPIO.H"
#include "STM32_SYSTICK.H"
#include "STM32_WDG.H"
#include "STM32_PWM.H"
#include "STM32_FLASH.H"

#include "LCD.H"
#include "ST7789V.H"

#include "font.h"

#define	BackColorStartAddr	0x0801F800		//原点值在MCU内部FLASH的存储地址126K地址，按128Kflash应用

sAmpLcdDef	sAmpLcd;


unsigned char LcdRS485Rxd[150];

unsigned  long*  MCUMEMaddr = (unsigned  long*)(0x1FFFF7E0);
unsigned  short  MCUMEMsize  = 0;

unsigned  char gCbFlag=0;   //0--柜板，1--层板
unsigned short colr=0;
unsigned short Num=0;
unsigned char testbuffer[]="GPIO_Configuration_OPP50(GPIOA,GPIO_Pin_0);";


void AsciiDspTest(void);
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
	
	SYS_Configuration();				//系统配置
	
  GPIO_Configuration_OPP50(GPIOA,GPIO_Pin_0);
  
  PWM_OUT(TIM2,PWM_OUTChannel2,500,1);	//PWM设定-20161127版本	占空比1/1000

  HW_Configuration();  
  
  //IWDG_Configuration(20000);													//独立看门狗配置---参数单位ms
	
	//SetBackColor(LCD565_DARKBLUE);
  
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
  colr+=1;
	IWDG_Feed();								//独立看门狗喂狗
	Tim_Server();
	
	//return;
	
  if(colr==500)
  {
    //ST7789V_Clean(LCD565_GREEN);
		//ST7789V_Clean(sAmpLcd.LcdPort.ST7789VBColor);
  }
  else if(colr==1000)
  {    
		unsigned char data[6]={0xaa,0x98,0x89,0x88,0x92,0x92};
		colr=0;
		//ST7789V_Clean(LCD565_RED);
    //ST7789V_Test(LCD565_LBBLUE);
    //ST7789V_DrawLine(0,0,240,320,LCD565_LBBLUE);
    //ST7789V_DrawCircle(100,100,70,1,LCD565_LBBLUE);		//画一个圆形框
    //ST7789V_DrawCircle(20,20,20,1,LCD565_LBBLUE);			//画一个圆形框
    //ST7789V_Fill(0,0,240,320,LCD565_LBBLUE);
    //ST7789V_Clean(LCD565_LBBLUE);
		//ST7789V_DrawLine(120,0,120,320,LCD565_GREEN);						//AB 两个坐标画一条直线
		//ST7789V_DrawLine(0,9,320,9,LCD565_GREEN);						//AB 两个坐标画一条直线
		//ST7789V_DrawLine(9,0,9,240,LCD565_GREEN);						//AB 两个坐标画一条直线
		//ST7789V_Printf(10,210,24,LCD565_RED,"层号%0.2d:位号%0.2d",sAmpLcd.Addr.Lay,sAmpLcd.Addr.Seg);  //LCD显示测试Printf
    //ST7789V_Printf(10,10,24,LCD565_RED,"LCD显示测试Printf自动换行",LCD565_GREEN);  //LCD显示测试Printf
		//ST7789V_Printf(10,20,32,LCD565_RED,"层号%0.2d:位号%0.3d",sAmpLcd.Addr.Lay,sAmpLcd.Addr.Seg);  //LCD显示测试Printf
		//ST7789V_Printf(10,155,24,LCD565_RED,"层号%0.2d:位号%0.2d",sAmpLcd.Addr.Lay,sAmpLcd.Addr.Seg);  //LCD显示测试Printf
		//ST7789V_Printf(10,180,12,LCD565_RED,"层号%0.2d:位号%0.2d",sAmpLcd.Addr.Lay,sAmpLcd.Addr.Seg);  //LCD显示测试Printf
		//ST7789V_Printf(10,200,8,LCD565_RED,"层号%0.2d:位号%0.2d",sAmpLcd.Addr.Lay,sAmpLcd.Addr.Seg);  //LCD显示测试Printf
		//ST7789V_ShowString(10,50,24,LCD565_BLACK,6,data);
		AsciiDspTest();
    //ST7789V_ShowChar(10,10,16,LCD565_LBBLUE,20,LcdRS485Rxd);	  //高通字库测试程序
    DisplayMana();
  }
  AMPLCDV11_Receive();
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
void AsciiDspTest(void)
{
	static unsigned char i=0;
	if(i++>=9)
		i=0;
	ST7789V_DrawLine(0,10,320,10,LCD565_GREEN);						//AB 两个坐标画一条直线
	
	ST7789V_Printf(0,12,24,LCD565_RED,"物品名称:高通字库24",sAmpLcd.Addr.Lay,sAmpLcd.Addr.Seg);  //LCD显示测试Printf
	ST7789V_Printf(0,36,24,LCD565_RED,"物品名称:高通字库24",sAmpLcd.Addr.Lay,sAmpLcd.Addr.Seg);  //LCD显示测试Printf
	ST7789V_Printf(0,62,16,LCD565_BRRED,"物品规格:高通字库测试程序高通字库测试16",sAmpLcd.Addr.Lay,sAmpLcd.Addr.Seg);  //LCD显示测试Printf
	ST7789V_Printf(0,84,16,LCD565_BRRED,"物品规格:高通字库测试程序高通字库测试16",sAmpLcd.Addr.Lay,sAmpLcd.Addr.Seg);  //LCD显示测试Printf
	
	ST7789V_ShowChar4836(237,12,LCD565_RED,code_ascii_4836[i]);	  //高通字库测试程序
	ST7789V_ShowChar4836(273,12,LCD565_GREEN,code_ascii_4836[i]);	  //高通字库测试程序
	
	ST7789V_DrawLine(0,119,320,119,LCD565_GREEN);						//AB 两个坐标画一条直线
	ST7789V_DrawLine(0,120,320,120,LCD565_GREEN);						//AB 两个坐标画一条直线
	ST7789V_DrawLine(0,121,320,121,LCD565_GREEN);						//AB 两个坐标画一条直线
	
	
	ST7789V_Printf(0,125,24,LCD565_RED,"物品名称:高通字库24",sAmpLcd.Addr.Lay,sAmpLcd.Addr.Seg);  //LCD显示测试Printf
	ST7789V_Printf(0,149,24,LCD565_RED,"物品名称:高通字库24",sAmpLcd.Addr.Lay,sAmpLcd.Addr.Seg);  //LCD显示测试Printf
	ST7789V_Printf(0,175,16,LCD565_GREEN,"物品规格:高通字库测试程序高通字库测试16",sAmpLcd.Addr.Lay,sAmpLcd.Addr.Seg);  //LCD显示测试Printf
	ST7789V_Printf(0,197,16,LCD565_GREEN,"物品规格:高通字库测试程序高通字库测试16",sAmpLcd.Addr.Lay,sAmpLcd.Addr.Seg);  //LCD显示测试Printf
	
	ST7789V_ShowChar4836(237,125,LCD565_GREEN,code_ascii_4836[i]);	  //高通字库测试程序
	ST7789V_ShowChar4836(273,125,LCD565_GREEN,code_ascii_4836[i]);	  //高通字库测试程序

	
	
	ST7789V_DrawLine(0,230,320,230,LCD565_GREEN);						//AB 两个坐标画一条直线
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
//  unsigned  short   sendedlen = 0;
//  if(gCbFlag) //0--柜板，1--层板
//  {
//    sendedlen = AMPLAY_SendBuff(Port,pBuffer,length);
//  }
//  else
//  {
//    sendedlen = AMPCAB_SendBuff(Port,pBuffer,length);
//  }
//  return  sendedlen;
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
*函数名			:	function
*功能描述		:	function
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
void AMPLCDV11_Receive(void)
{
  unsigned short RxNum  = 0;
  //unsigned char rxd[256]={0};
  //==========================================================接收查询
  //---------------------层板接口 USART2
  RxNum = RS485_ReadBufferIDLE(&sAmpLcd.RS485Port,LcdRS485Rxd);
  if(RxNum)
  {
    AMPLCDV11_Process(LcdRS485Rxd,RxNum);              //柜消息处理
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
void AMPLCDV11_Process(unsigned char* ReceDatabuffer,unsigned short datalen)
{
  unsigned  short framlength  = datalen; 
  unsigned  char* StartAddr    = ReceDatabuffer;         //备份数据缓存起始地址
  
  stampphydef* ampframe=NULL;
  //-------------------------检查端口是否为层接口及缓存地址是否为空
  if(NULL==StartAddr||0==framlength)
  {
    return;
  }
	ReceiveDataCheckStart:	//开始检测接收到的数据
  //-------------------------协议检查
  ampframe	=	(stampphydef*)API_AmpCheckFrame(StartAddr,&framlength);    //判断帧消息内容是否符合协议
  if(NULL== ampframe)
  {
    return;		//退出，未检测到有效的帧
  }
  //-------------------------检查是否为应答帧
	if(AmpCmdAck==ampframe->msg.cmd.cmd)
	{
		goto ReCheckData;		//重新检测剩余的数据
	}
  //-------------------------层地址检查
	if(sAmpLcd.Addr.Lay	!=	ampframe->msg.addr.address2)
	{
		goto ReCheckData;		//重新检测剩余的数据
	}
	//-------------------------位地址检查
	if(sAmpLcd.Addr.Seg	!=	ampframe->msg.addr.address3)
	{
		goto ReCheckData;		//重新检测剩余的数据
	}
 
  //-------------------------下发数据
  if(0  ==  ampframe->msg.cmd.dir)	//最高位为0表示上往下发
  {
    //---------------------------显示数据命令
    if(AmpCmdLcdData ==  ampframe->msg.cmd.cmd) 
    {
			unsigned char	i=0;
			unsigned char DataLen	=	ampframe->msg.length-4;		//数据段长度
			ManaDef*	ManaData;
			DspDataDef*	DspData;		//
			
			ManaData=(ManaDef*)ampframe->msg.data;
			
			//------------------------------查找空显示缓存
			for(i=0;i<DspMaxNameTypeCount;i++)
			{
				if(0==sAmpLcd.DspData[i].Serial)		//缓存为空，可以拷贝数据
				{
					DspData	=	&sAmpLcd.DspData[i];
					sAmpLcd.ReceivedManaCount+=1;
					break;
				}
			}
			//------------------------------未查找到空缓存，缓存满
			if(i>=DspMaxNameTypeCount)
			{
				return;
			}
			
			//------------------------------分类拆装数据
			PackManaData:
			if(0x01	==	ManaData->type)	//名称参数
			{
				DspData->NameLen			=	ManaData->len-3;		//名称字符串长度，需要减去一字节大小数据和两字节颜色数据
				DspData->NameFontSize	=	ManaData->FontSize;	//显示字符大小
				DspData->NameColor		=	ManaData->Color;
				memcpy(DspData->String,ManaData->String,DspData->NameLen);	//拷贝名称数据
			}
			ManaData=(ManaDef*)&ampframe->msg.data[DspData->NameLen+2];		//包含类型和长度位
			if(0x02	==	ManaData->type)	//规格参数
			{
				DspData->SpecLen			=	ManaData->len-3;		//规格字符串长度，需要减去一字节大小数据和两字节颜色数据
				DspData->SpecFontSize	=	ManaData->FontSize;	//显示字符大小
				DspData->SpecColor		=	ManaData->Color;
				memcpy(&DspData->String[DspData->NameLen],ManaData->String,DspData->SpecLen);	//拷贝名称数据
			}
			ManaData=(ManaDef*)&ampframe->msg.data[DspData->SpecLen+2];		//包含类型和长度位
			if(0x03	==	ManaData->type)	//数量参数
			{
				DspData->Num			=	ManaData->String[0];		//数量
				DspData->NumColor	=	ManaData->Color;				//显示字符大小
			}
			sAmpLcd.ReceivedManaCount+=1;
			sAmpLcd.DspData[i].Serial=sAmpLcd.ReceivedManaCount;
			ackFrame(LayPort,1); //向上应答
						
    }
		//---------------------------修改背景色命令--只带2字节数据,低8位颜色在前
		else if(AmpCmdLcdBKCL ==  ampframe->msg.cmd.cmd)
		{
			unsigned short BackColor	=	0;			
			memcpy(&BackColor,ampframe->msg.data,2);	//2字节背景色数据，低位在前
			SetBackColor(BackColor);
			ackFrame(LayPort,1); //向上应答			
		}
		goto ReCheckData;		//重新检测剩余的数据
  }
	//------------------------------继续检查剩余数据，直到检查失败
	ReCheckData:
	StartAddr=(unsigned char*)&ampframe[1];
	framlength-=1;	//去掉一字节长度
	goto ReceiveDataCheckStart;
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
void DisplayMana(void)
{
	unsigned char i	=	0;
	unsigned char len=0;
	unsigned char num=0;
	unsigned char* str;
	if(sAmpLcd.DisplaySerial>=sAmpLcd.ReceivedManaCount)
	{
		sAmpLcd.DisplaySerial=1;
	}
	//-------------------------------第一行
	for(i=1;i<sAmpLcd.ReceivedManaCount;i++)
	{
		if(i==sAmpLcd.DspData[i].Serial)
		{
			//-----------------------------------------显示名称
			str	=	sAmpLcd.DspData[i].String;
			len	=	sAmpLcd.DspData[i].NameLen;			
			if(len>10)
			{
				ST7789V_ShowString(0,12,24,sAmpLcd.DspData[i].NameColor,10,str);
				ST7789V_ShowString(0,36,24,sAmpLcd.DspData[i].NameColor,len-10,&str[10]);
			}
			else
			{
				ST7789V_ShowString(0,12,24,sAmpLcd.DspData[i].NameColor,len,sAmpLcd.DspData[i].String);
			}
			//-----------------------------------------显示规格
			str	=	&sAmpLcd.DspData[i].String[len];
			len	=	sAmpLcd.DspData[i].SpecLen;
			if(len>10)
			{
				ST7789V_ShowString(0,62,16,sAmpLcd.DspData[i].SpecColor,10,str);  //LCD显示测试Printf
				ST7789V_ShowString(0,86,16,sAmpLcd.DspData[i].SpecColor,10,&str[10]);  //LCD显示测试Printf
			}
			//-----------------------------------------数量
			num	=	sAmpLcd.DspData[i].Num;
			ST7789V_ShowChar4836(237,12,LCD565_RED,code_ascii_4836[num/10]);	  	//高通字库测试程序
			ST7789V_ShowChar4836(273,12,LCD565_GREEN,code_ascii_4836[num%10]);	  //高通字库测试程序
			
			sAmpLcd.DisplaySerial+=1;
		}
		
	}
	//-------------------------------第二行
	for(;i<sAmpLcd.ReceivedManaCount;i++)
	{
		if(i==sAmpLcd.DspData[i].Serial)
		{
			
			sAmpLcd.DisplaySerial+=1;
		}
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
void SetBackColor(unsigned short BKColor)
{
	STM32_FLASH_Write(BackColorStartAddr,(unsigned short*)&BKColor,1);						//从指定地址写入指定长度的数据
	BKColor	=	GetBackColor();
	ST7789V_Clean(BKColor);	//清除屏幕函数
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
unsigned short GetBackColor(void)
{
	unsigned short BKColor;
	STM32_FLASH_Read(BackColorStartAddr,(unsigned short*)&BKColor,1);							//从指定地址开始读出指定长度的数据
	return	BKColor;
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
void HW_Configuration(void)
{
//	SPIDef	*SPI	=	&sAmpLcd.SpiPort;
	sST7789VDef	sST7789V;
	SPIDef			sGT32L32;
	RS485Def		sRS485Port;   //层板接口
	SwitchDef 	sSwitch;			//拔码开关
	
	unsigned short temp;
	
	//-------------------------------------------LCD参数初始化
	sST7789V.HWPort.sBL_PORT				=	GPIOA;
	sST7789V.HWPort.sBL_Pin					=	GPIO_Pin_1;
	
	sST7789V.HWPort.sRD_PORT				=	GPIOD;
	sST7789V.HWPort.sRD_Pin					=	GPIO_Pin_2;	
	
	sST7789V.HWPort.sREST_PORT			=	GPIOA;
	sST7789V.HWPort.sREST_Pin				=	GPIO_Pin_15;
	
	sST7789V.HWPort.sDC_PORT				=	GPIOC;
	sST7789V.HWPort.sDC_Pin					=	GPIO_Pin_11;
	
	sST7789V.HWPort.sWR_PORT				=	GPIOC;
	sST7789V.HWPort.sWR_Pin					=	GPIO_Pin_12;	
	
	sST7789V.HWPort.sCS_PORT				=	GPIOC;
	sST7789V.HWPort.sCS_Pin					=	GPIO_Pin_10;
	
	sST7789V.HWPort.sDATABUS_PORT		=	GPIOB;
	sST7789V.HWPort.sDATABUS_Pin		=	GPIO_Pin_All;	
	
	sST7789V.ST7789VRotate	=	ST7789V_Rotate_90D;		//使用旋转角度
	
	
	temp	=	 GetBackColor();			//背景色
	sST7789V.ST7789VBColor=	temp;
	
	sAmpLcd.LcdPort	=	sST7789V;
	
	ST7789V_Initialize(&sAmpLcd.LcdPort);
	
	//-------------------------------------------字库参数初始化
	sGT32L32.Port.SPIx			=	SPI1;
	sGT32L32.Port.CS_PORT		=	GPIOA;
	sGT32L32.Port.CS_Pin		=	GPIO_Pin_4;
	
	sGT32L32.Port.CLK_PORT	=	GPIOA;
	sGT32L32.Port.CLK_Pin		=	GPIO_Pin_5;
	
	sGT32L32.Port.MISO_PORT	=	GPIOA;
	sGT32L32.Port.MISO_Pin	=	GPIO_Pin_6;
	
	sGT32L32.Port.MOSI_PORT	=	GPIOA;
	sGT32L32.Port.MOSI_Pin	=	GPIO_Pin_7;	
	sGT32L32.Port.SPI_BaudRatePrescaler_x=SPI_BaudRatePrescaler_2;
	
	sAmpLcd.SpiPort	=	sGT32L32;	
  
  GT32L32_Initialize(&sAmpLcd.SpiPort);				//普通SPI通讯方式配置
	
	//-------------------------------------------层板接口USART1 PA11-RE,PA12-TE
  sRS485Port.USARTx  				= USART1;
  sRS485Port.RS485_CTL_PORT  = GPIOA;
  sRS485Port.RS485_CTL_Pin   = GPIO_Pin_8;
	
	sAmpLcd.RS485Port	=	sRS485Port;
	
  RS485_DMA_ConfigurationNR			(&sAmpLcd.RS485Port,19200,gDatasize);	//USART_DMA配置--查询方式，不开中断,配置完默认为接收状态
  GPIO_Configuration_OPP50	(sAmpLcd.RS485Port.RS485_CTL_PORT,sAmpLcd.RS485Port.RS485_CTL_Pin);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605
  GPIO_ResetBits(sAmpLcd.RS485Port.RS485_CTL_PORT,sAmpLcd.RS485Port.RS485_CTL_Pin);
	
	//-------------------------------------------拨码开关
	sSwitch.NumOfSW	=	8;
  
  sSwitch.SW1_PORT	=	GPIOC;
  sSwitch.SW1_Pin		=	GPIO_Pin_7;
  
  sSwitch.SW2_PORT	=	GPIOC;
  sSwitch.SW2_Pin		=	GPIO_Pin_6;
  
  sSwitch.SW3_PORT	=	GPIOC;
  sSwitch.SW3_Pin		=	GPIO_Pin_5;
  
  sSwitch.SW4_PORT	=	GPIOC;
  sSwitch.SW4_Pin		=	GPIO_Pin_4;
  
  sSwitch.SW5_PORT	=	GPIOC;
  sSwitch.SW5_Pin		=	GPIO_Pin_3;
  
  sSwitch.SW6_PORT	=	GPIOC;
  sSwitch.SW6_Pin		=	GPIO_Pin_2;
  
  sSwitch.SW7_PORT	=	GPIOC;
  sSwitch.SW7_Pin		=	GPIO_Pin_1;
  
  sSwitch.SW8_PORT	=	GPIOC;
  sSwitch.SW8_Pin		=	GPIO_Pin_0;

	sAmpLcd.sSwitch		=	sSwitch;
	
	SwitchIdInitialize(&sAmpLcd.sSwitch);	
	
	temp	=	SWITCHID_ReadLeft(&sAmpLcd.sSwitch);
  sAmpLcd.Addr.Lay=(temp>>4)&0X0F;  	//层地址
  sAmpLcd.Addr.Seg=temp&0x0F;      	//位地址
}

#endif
