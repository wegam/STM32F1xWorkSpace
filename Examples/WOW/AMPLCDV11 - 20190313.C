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




sAmpLcdDef	sAmpLcd;




unsigned  long*  MCUMEMaddr = (unsigned  long*)(0x1FFFF7E0);
unsigned  short  MCUMEMsize  = 0;

unsigned  char 	gCbFlag		=0;   //0--柜板，1--层板
unsigned	short FlashTime	=0;
unsigned	short Num=0;
//unsigned char testbuffer[]="GPIO_Configuration_OPP50(GPIOA,GPIO_Pin_0);";




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
	
	SysTick_DeleymS(500);				//SysTick延时nmS
	
  HW_Configuration();  
  
  IWDG_Configuration(2000);													//独立看门狗配置---参数单位ms
	
	//SetBackColor(LCD565_DARKBLUE);
  ST7789V_Clean(0xFFFF);
	//AMPLCDV11GUI();
  SysTick_Configuration(1000);    //系统嘀嗒时钟配置72MHz,单位为uS  
  while(1)
  {
		AMPLCDV11_Receive();
		AMPLCDV11_Send();
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
	static unsigned short color=0;
  FlashTime+=1;
	IWDG_Feed();								//独立看门狗喂狗
	Tim_Server();
  if(FlashTime==2000)
  {
		FlashTime=0;
		#if 1==SelectModel
			DisplayManaStaticTest1();
		#elif 2==SelectModel
			DisplayManaStaticTest2();
		#elif 3==SelectModel
			DisplayManaModel1();
		#elif 4==SelectModel
			DisplayManaModel2();
		#elif 5==SelectModel
			DisplayManaModel3();
		#elif 6==SelectModel
			DisplayManaModel2();
		#endif
//		ST7789V_Clean(0xFFDE);
		//DisplayManaStaticTest1();
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
void AMPLCDV11_Send(void)
{ 
  unsigned  short   sendedlen = sAmpLcd.Comm.TxLen;
	if(sendedlen)
	{
		sendedlen	=	RS485_DMASend(&sAmpLcd.Comm.RS485Port,sAmpLcd.Comm.Txd,sendedlen);	//RS485-DMA发送程序
		if(sAmpLcd.Comm.TxLen	==	sendedlen)
		{
			sAmpLcd.Comm.TxLen	=	0;
		}
	}
}
void AMPLCDV11_Ack(void)
{
	memcpy(sAmpLcd.Comm.Txd,ackupfarme,AmpMinFrameSize);
	sAmpLcd.Comm.TxLen	=	AmpMinFrameSize;
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
  //==========================================================接收查询
  //---------------------层板接口 USART2
  RxNum = RS485_ReadBufferIDLE(&sAmpLcd.Comm.RS485Port,sAmpLcd.Comm.Rxd);
  if(RxNum)
  {	
    AMPLCDV11_Process(sAmpLcd.Comm.Rxd,RxNum);              //柜消息处理
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
	
	
	unsigned char	i=0;
	unsigned char DataLen	=0;		//数据段长度
	ManaDef*	ManaData;
  
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
	if(sAmpLcd.Sys.AddrLay	!=	ampframe->msg.addr.address2)
	{
		goto ReCheckData;		//重新检测剩余的数据
	}
	//-------------------------位地址检查
	if(sAmpLcd.Sys.AddrSeg	!=	ampframe->msg.addr.address3)
	{
		goto ReCheckData;		//重新检测剩余的数据
	}
 
  //-------------------------下发数据
  if(0  ==  ampframe->msg.cmd.dir)	//最高位为0表示上往下发
  {
    //---------------------------显示数据命令
    if(AmpCmdLcdData ==  ampframe->msg.cmd.cmd) 
    {	
			unsigned char* buffer=NULL;
			DataLen	=	ampframe->msg.length-4;		//数据段长度			
			buffer=(unsigned char*)ampframe->msg.data;
			
			PackManaData:
			GetManaData(buffer,DataLen);
			AMPLCDV11_Ack();						
    }
		//---------------------------修改背景色命令--只带2字节数据,低8位颜色在前
		else if(AmpCmdLcdBKCL ==  ampframe->msg.cmd.cmd)
		{
			unsigned short BackColor	=	0;			
			memcpy(&BackColor,ampframe->msg.data,2);	//2字节背景色数据，低位在前
			SetBackColor(BackColor);
			AMPLCDV11_Ack();			
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
void GetManaData(unsigned char* Databuffer,unsigned short datalen)
{
	unsigned char		i=0;
	unsigned char 	strtype		=0;		//字符串类型
	unsigned char 	strLen		=0;		//字符串长度
	unsigned char 	strCount	=0;		//已处理的字符串个数计数
	unsigned char* 	strSource;		//源字符串地址---源自串口接收到的数据
	unsigned char* 	strTarget;		//目标符串地址---存储
	
	ManaDef*	ManaData;
	DisplayDataDef*	pDisplayData;		//
	
	ManaData	=	(ManaDef*)Databuffer;
	//=================================查找空缓存
	for(i=0;i<DspMaxNameTypeCount;i++)
	{
		if(0==sAmpLcd.Display.DisplayArry[i].Serial)		//缓存为空，可以拷贝数据
		{
			pDisplayData	=	&sAmpLcd.Display.DisplayArry[i];
			sAmpLcd.Display.ReceivedManaCount+=1;
			break;
		}
	}	
	//=================================未查找到空缓存，缓存满
	if(i>=DspMaxNameTypeCount)
	{
		return;
	}
	//=================================分类拆装数据
	//---------------------------------初始化指针地址和数据
	strSource	=	ManaData->String;
	strTarget	=	pDisplayData->String;	
	
	//---------------------------------01名称参数
	strtype		=	ManaData->type;
	strLen		=	ManaData->len;
	if(0x01	==	strtype)	//名称参数
	{
		strCount+=strLen;		//已处理字符串
		
		pDisplayData->NameLen	=	strLen;
		memcpy(strTarget,strSource,strLen);		
		
		ManaData	=	(ManaDef*)&strSource[strLen];
		strSource	=	ManaData->String;
		strTarget	=	&strTarget[strLen];
		
		strtype		=	ManaData->type;
		strLen		=	ManaData->len;		
	}
	//---------------------------------02规格参数
	if(0x02	==	strtype)
	{
		strCount+=strLen;		//已处理字符串
		
		pDisplayData->SpecLen	=	strLen;
		memcpy(strTarget,strSource,strLen);
		
		ManaData	=	(ManaDef*)&strSource[strLen];
		strSource	=	ManaData->String;
		strTarget	=	&strTarget[strLen];
		
		strtype		=	ManaData->type;
		strLen		=	ManaData->len;
	}
	//---------------------------------03耗材数量		
	if(0x03	==	ManaData->type)	//数量参数
	{
		unsigned char Num	=	0;
		strCount+=strLen;		//已处理字符串
	
		if((0<strLen)&&(strLen<2))
		{
			Num	=	strSource[0]-0x30;		//数量
		}
		else if(2==strLen)
		{
			Num	=	(strSource[0]-0x30)*10;		//数量--Ascii码，十位在前
			Num	+= (strSource[1]-0x30);			//数量--Ascii码，十位在后
		}
		else
		{
			Num=99;
		}
		pDisplayData->Num	=	Num;
		
		ManaData	=	(ManaDef*)&strSource[strLen];
		strSource	=	ManaData->String;

		strtype		=	ManaData->type;
		strLen		=	ManaData->len;
	}
	//---------------------------------04别名
	if(0x04	==	strtype)
	{
		strCount+=strLen;		//已处理字符串
		
		pDisplayData->byNameLen	=	strLen;
		memcpy(strTarget,strSource,strLen);
		
		ManaData	=	(ManaDef*)&strSource[strLen];
		strSource	=	ManaData->String;
		strTarget	=	&strTarget[strLen];
		
		strtype		=	ManaData->type;
		strLen		=	ManaData->len;
	}
	//---------------------------------05厂家名称
	if(0x05	==	strtype)
	{
		strCount+=strLen;		//已处理字符串
		
		pDisplayData->VenderLen	=	strLen;
		memcpy(strTarget,strSource,strLen);
		
		ManaData	=	(ManaDef*)&strSource[strLen];
		strSource	=	ManaData->String;
		strTarget	=	&strTarget[strLen];
		
		strtype		=	ManaData->type;
		strLen		=	ManaData->len;
	}
	//---------------------------------06耗材编码
	if(0x06	==	strtype)
	{
		strCount+=strLen;		//已处理字符串
		
		pDisplayData->CodeLen	=	strLen;
		memcpy(strTarget,strSource,strLen);
		
		ManaData	=	(ManaDef*)&strSource[strLen];
		strSource	=	ManaData->String;
		strTarget	=	&strTarget[strLen];
		
		strtype		=	ManaData->type;
		strLen		=	ManaData->len;
	}
	//---------------------------------07数量单位
	if(0x07	==	strtype)
	{
		strCount+=strLen;		//已处理字符串
		
		pDisplayData->UnitLen	=	strLen;
		memcpy(strTarget,strSource,strLen);
		
		ManaData	=	(ManaDef*)&strSource[strLen];
		strSource	=	ManaData->String;
		strTarget	=	&strTarget[strLen];
		
		strtype		=	ManaData->type;
		strLen		=	ManaData->len;
	}
	pDisplayData->Serial	=	sAmpLcd.Display.ReceivedManaCount;
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
void DisplayManaStaticTest1(void)
{
	unsigned char i=0;
	unsigned short x=0,y=0;
	unsigned short xysbac=0;
	unsigned char font=0;
	static unsigned char testnum=0;
	if(testnum++>=99)
		testnum=0;

	x	=	0;
	y	=	8;
	xysbac=y;
	//y=ystarttop;	//ystarttop==8
	//-----------------------------------画上边边线
	ST7789V_Fill(0,0,320,y+2,0x0000);				//在指定区域内填充指定颜色;区域大小:(xend-xsta)*(yend-ysta)
	
	y+=2;
	ST7789V_Fill(0,y-1,320,y+16,0x865D);				//在指定区域内填充指定颜色;区域大小:(xend-xsta)*(yend-ysta)
	ST7789V_PrintfBK(x,y,16,0x865D,0x0000,"层号:%0.2d  位号:%0.2d         %d/99::%d/99页",sAmpLcd.Sys.AddrLay%100,sAmpLcd.Sys.AddrSeg%100,testnum%100,(testnum+1)%100);  //LCD显示测试Printf
	ST7789V_Fill(x,y+16,320,y+18,0x8450);				//在指定区域内填充指定颜色;区域大小:(xend-xsta)*(yend-ysta)
	
	y+=16+3;
	ST7789V_Fill(ST7789V_V-32*2,y+32+16+4,ST7789V_V,y+32+16+4+32,0xFFFF);				//在指定区域内填充指定颜色;区域大小:(xend-xsta)*(yend-ysta)
	ST7789V_PrintfBK(ST7789V_V-32*2,y+32+16+4,32,0xFFFF,0xFB00,"%0.2d",testnum%100);  //LCD显示测试Printf
	ST7789V_PrintfBK(ST7789V_V-32*1,y+31*2,16,0xFFFF,0xFB00,"盒");  //LCD显示测试Printf
//	y+=32;
	font=24;
	ST7789V_PrintfBK(x,y,font,0xFFFF,0x054A,"测试物品名称1测试物品名称1");  //LCD显示测试Printf
	y+=font;
	ST7789V_PrintfBK(x,y,font,0xFFFF,0x054A,"一次性套管穿刺器一次性套管");  //LCD显示测试Printf
	y+=font+2;
	font=16;
	ST7789V_Printf(x,y,font,0x5ACA,"Ⅲ型Ф10-MBQ2019FF1299-ACTD-MT");  //LCD显示测试Printf
	ST7789V_Printf(x,y+16,font,0x5ACA,"#Яβπポほ㈣019FF1299-ACTD-M");  //LCD显示测试Printf
	y+=font+2;
	
	//-----------------------------------画中线

	y	=	(ST7789V_H)/2-4+xysbac;
	ST7789V_Fill(0,y,320,y+8,0x8450);				//在指定区域内填充指定颜色;区域大小:(xend-xsta)*(yend-ysta)
	y+=10;
	
	ST7789V_Fill(ST7789V_V-32*2,y+32+16+4,ST7789V_V,y+32+16+4+32,0xFFFF);				//在指定区域内填充指定颜色;区域大小:(xend-xsta)*(yend-ysta)
	ST7789V_PrintfBK(ST7789V_V-32*2,y+32+16+4,32,0xFFFF,0xFB00,"%0.2d",testnum+1%100);  //LCD显示测试Printf
	ST7789V_PrintfBK(ST7789V_V-32*1,y+31*2,16,0xFFFF,0xFB00,"瓶");  //LCD显示测试Printf
//	y+=32;
	font=24;
	ST7789V_PrintfBK(x,y,font,0xFFFF,0x054A,"测试物品名称2测试物品名称2");  //LCD显示测试Printf
	y+=font;
	ST7789V_PrintfBK(x,y,font,0xFFFF,0x054A,"（套管穿刺针）        ");  //LCD显示测试Printf
	y+=font+2;
	font=16;
	ST7789V_Printf(x,y,font,0x5ACA,"Ⅲ型Ф10-MBQ2019FF1299-ACTD-MT");  //LCD显示测试Printf
	y+=16;
	ST7789V_Printf(x,y,font,0x5ACA,"#Яβπポほ㈣019FF1299-ACTD-M");  //LCD显示测试Printf
	y+=16;
	y+=16;
	ST7789V_Fill(0,y,320,ST7789V_H,LCD565_BLACK);				//在指定区域内填充指定颜色;区域大小:(xend-xsta)*(yend-ysta)

	testnum+=1;
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
void DisplayManaStaticTest2(void)
{
	unsigned char i	=	0;
	unsigned char len=0;
	unsigned char num=0;
	unsigned char* str;
	
	unsigned char TempLay	=	sAmpLcd.Sys.AddrLay%100;
	unsigned char TempSeg	=	sAmpLcd.Sys.AddrSeg%100;

	
	unsigned short xs=0;
	unsigned short ys=0;
	unsigned short xe=0;
	unsigned short ye=0;
	unsigned short yebac=0;
	
	static unsigned char testnum=0;
	if(testnum++>=99)
		testnum=0;

	//===============================顶部填充
	ye=DisplayTopStartY;	
	ST7789V_Fill(0,0,ST7789V_V,ye,LCD565_BLACK);				//在指定区域内填充指定颜色;区域大小:(xend-xsta)*(yend-ysta)
	//===============================中间分隔线填充
//	ys	=	(DisplayBotStartY-DisplayTopStartY-DisplayTitleSize-DisplaySeparWidth)/2+DisplayTopStartY+DisplayTitleSize;
//	ST7789V_Fill(0,ys-DisplaySeparWidth,ST7789V_V,ys+DisplaySeparWidth,DisplaySeparBkColor);				//在指定区域内填充指定颜色;区域大小:(xend-xsta)*(yend-ysta)
	
	//===============================底部填充
	ys	=	DisplayBotStartY;
	ye	=	DisplayBotEndY;
	ST7789V_Fill(0,ys,ST7789V_V,ST7789V_H,LCD565_BLACK);				//在指定区域内填充指定颜色;区域大小:(xend-xsta)*(yend-ysta)
	//===============================标题填充
	ys	=	DisplayTopStartY;
	ye	=	DisplayTopStartY+DisplayTitleSize;
	ST7789V_Fill(0,ys,ST7789V_V,ye,DisplayTitleBkColor);				//在指定区域内填充指定颜色;区域大小:(xend-xsta)*(yend-ysta)
	//===============================标题分隔线填充
	ys	=	ye;
	ye	=	ys+DisplaySeparWidth;
	ST7789V_Fill(0,ys,ST7789V_V,ye,DisplaySeparBkColor);				//在指定区域内填充指定颜色;区域大小:(xend-xsta)*(yend-ysta)
	
	//===============================显示地址
	ys	=	DisplayTopStartY;
	ST7789V_PrintfBK(DisplayStartX,ys,DisplayTitleSize,DisplayTitleBkColor,DisplayTitleFtColor,"层号:%0.2d 位号:%0.2d                 01/03页",TempLay,TempSeg);  //LCD显示测试Printf
	
	//===============================显示别名/学名
	ys	=	ys+DisplayTitleSize+DisplaySeparWidth+1;
	ST7789V_PrintfBK(DisplayStartX,ys,DisplayNameFtSize,DisplayNameBkColor,DisplayNameFtColor,"无纺布食品车间防尘条形帽/医用一次性帽子");  //LCD显示测试Printf
	ys	=	ys+DisplayNameFtSize;
	ST7789V_PrintfBK(DisplayStartX,ys,DisplayNameFtSize,DisplayNameBkColor,DisplayNameFtColor,"无纺布食品车间防尘条形帽/医用一次性帽子");  //LCD显示测试Printf
	//===============================物料编码
	ys	=	ys+DisplayNameFtSize*2;
	ST7789V_PrintfBK(DisplayStartX,ys,DisplayCodeFtSize,DisplayCodeBkColor,DisplayCodeFtColor,"编码:POY20190315-M1");  //LCD显示测试Printf
	//===============================厂家
	ys	=	ys+DisplayCodeFtSize;
	ST7789V_PrintfBK(DisplayStartX,ys,DisplayVenderFtSize,DisplayVenderBkColor,DisplayVenderFtColor,"厂家:特斯拉中国 - Tesla");  //LCD显示测试Printf
	//===============================规格
	ys	=	ys+DisplayVenderFtSize;
	ST7789V_PrintfBK(DisplayStartX,ys,DisplaySpecFtSize,DisplaySpecBkColor,DisplaySpecFtColor,"规格:Red 1000x40000000cm");  //LCD显示测试Printf
	//===============================数量
	xs	=	ST7789V_V-DisplayNumFtSize*2;
	ys	=	ys+DisplaySpecFtSize-DisplayNumFtSize;
	ST7789V_PrintfBK(xs,ys,DisplayNumFtSize,DisplayNumBkColor,DisplayNumFtColor,"13包");  //LCD显示测试Printf
	
	//-----------------------------------画上边边线
//	ST7789V_Fill(0,0,320,y+2,0x0000);				//在指定区域内填充指定颜色;区域大小:(xend-xsta)*(yend-ysta)
//	
//	y+=2;
//	ST7789V_Fill(0,y-1,320,y+16,0x865D);				//在指定区域内填充指定颜色;区域大小:(xend-xsta)*(yend-ysta)
//	ST7789V_PrintfBK(x,y,16,0x865D,0x0000,"层号:%0.2d  位号:%0.2d         %d/99::%d/99页",sAmpLcd.Addr.Lay%100,sAmpLcd.Addr.Seg%100,testnum%100,(testnum+1)%100);  //LCD显示测试Printf
//	ST7789V_Fill(x,y+16,320,y+18,0x8450);				//在指定区域内填充指定颜色;区域大小:(xend-xsta)*(yend-ysta)
//	
//	y+=16+3;
//	ST7789V_Fill(ST7789V_V-32*2,y+32+16+4,ST7789V_V,y+32+16+4+32,0xFFFF);				//在指定区域内填充指定颜色;区域大小:(xend-xsta)*(yend-ysta)
//	ST7789V_PrintfBK(ST7789V_V-32*2,y+32+16+4,32,0xFFFF,0xFB00,"%0.2d",testnum%100);  //LCD显示测试Printf
//	ST7789V_PrintfBK(ST7789V_V-32*1,y+31*2,16,0xFFFF,0xFB00,"盒");  //LCD显示测试Printf
////	y+=32;
//	font=24;
//	ST7789V_PrintfBK(x,y,font,0xFFFF,0x054A,"测试物品名称1测试物品名称1",sAmpLcd.Addr.Lay,sAmpLcd.Addr.Seg);  //LCD显示测试Printf
//	y+=font;
//	ST7789V_PrintfBK(x,y,font,0xFFFF,0x054A,"一次性套管穿刺器一次性套管",sAmpLcd.Addr.Lay,sAmpLcd.Addr.Seg);  //LCD显示测试Printf
//	y+=font+2;
//	font=16;
//	ST7789V_Printf(x,y,font,0x5ACA,"Ⅲ型Ф10-MBQ2019FF1299-ACTD-MT",sAmpLcd.Addr.Lay,sAmpLcd.Addr.Seg);  //LCD显示测试Printf
//	ST7789V_Printf(x,y+16,font,0x5ACA,"#Яβπポほ㈣019FF1299-ACTD-M",sAmpLcd.Addr.Lay,sAmpLcd.Addr.Seg);  //LCD显示测试Printf
//	y+=font+2;
//	
//	//-----------------------------------画中线

//	y	=	(ST7789V_H)/2-4+xysbac;
//	ST7789V_Fill(0,y,320,y+8,0x8450);				//在指定区域内填充指定颜色;区域大小:(xend-xsta)*(yend-ysta)
//	y+=10;
//	
//	ST7789V_Fill(ST7789V_V-32*2,y+32+16+4,ST7789V_V,y+32+16+4+32,0xFFFF);				//在指定区域内填充指定颜色;区域大小:(xend-xsta)*(yend-ysta)
//	ST7789V_PrintfBK(ST7789V_V-32*2,y+32+16+4,32,0xFFFF,0xFB00,"%0.2d",testnum+1%100);  //LCD显示测试Printf
//	ST7789V_PrintfBK(ST7789V_V-32*1,y+31*2,16,0xFFFF,0xFB00,"瓶");  //LCD显示测试Printf
////	y+=32;
//	font=24;
//	ST7789V_PrintfBK(x,y,font,0xFFFF,0x054A,"测试物品名称2测试物品名称2",sAmpLcd.Addr.Lay,sAmpLcd.Addr.Seg);  //LCD显示测试Printf
//	y+=font;
//	ST7789V_PrintfBK(x,y,font,0xFFFF,0x054A,"（套管穿刺针）        ",sAmpLcd.Addr.Lay,sAmpLcd.Addr.Seg);  //LCD显示测试Printf
//	y+=font+2;
//	font=16;
//	ST7789V_Printf(x,y,font,0x5ACA,"Ⅲ型Ф10-MBQ2019FF1299-ACTD-MT",sAmpLcd.Addr.Lay,sAmpLcd.Addr.Seg);  //LCD显示测试Printf
//	y+=16;
//	ST7789V_Printf(x,y,font,0x5ACA,"#Яβπポほ㈣019FF1299-ACTD-M",sAmpLcd.Addr.Lay,sAmpLcd.Addr.Seg);  //LCD显示测试Printf
//	y+=16;
//	y+=16;
//	ST7789V_Fill(0,y,320,ST7789V_H,LCD565_BLACK);				//在指定区域内填充指定颜色;区域大小:(xend-xsta)*(yend-ysta)

//	testnum+=1;
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
void DisplayManaModel1(void)
{
	unsigned char i	=	0;
	unsigned char len=0;
	unsigned char num=0;
	unsigned char* str;
	//unsigned char  FontSize	=	0;
	
	unsigned short xs=0;
	unsigned short ys=0;
	unsigned short xe=0;
	unsigned short ye=0;
	unsigned short yebac=0;
	
	DisplayDataDef	DisplayData;		//

	if(0>=sAmpLcd.Display.ReceivedManaCount)	//没收到数据显示位置号
	{
		unsigned char TempLay	=	sAmpLcd.Sys.AddrLay%100;
		unsigned char TempSeg	=	sAmpLcd.Sys.AddrSeg%100;
		ST7789V_PrintfBK(68,ST7789V_H/2-DisplayNumFtSize/2,DisplayNumFtSize,DisplayNumBkColor,DisplayNumFtColor,"层%0.2d    位%0.2d",TempLay,TempSeg);  //LCD显示测试Printf
		return;
	}
	if(0==sAmpLcd.Display.DisplaySerial)
	{
		sAmpLcd.Display.DisplaySerial=1;
	}
	if(sAmpLcd.Display.DisplaySerial>sAmpLcd.Display.ReceivedManaCount)
	{
		sAmpLcd.Display.DisplaySerial=1;
	}
	
	//=====================================清空区域:名称
	xs	=	0;
	xe	=	ST7789V_V;
	ys	=	DisplayTopStartY;
	ye	=	DisplayBotStartY;
	
	ST7789V_Fill(xs,ys,xe,ye,DisplayNameBkColor);				//在指定区域内填充指定颜色;区域大小:(xend-xsta)*(yend-ysta)	
	
	//===============================顶部填充
	ye=DisplayTopStartY;	
	ST7789V_Fill(0,0,ST7789V_V,ye,LCD565_BLACK);				//在指定区域内填充指定颜色;区域大小:(xend-xsta)*(yend-ysta)
	//===============================中间填充
	//ys=DisplayTopStartY+DisplayNameFtSize*2+DisplaySpecFtSize*3;
	ys	=	(DisplayBotStartY-DisplayTopStartY)/2+DisplayTopStartY;
	ST7789V_Fill(0,ys-2,ST7789V_V,ys+2,LCD565_BLACK);				//在指定区域内填充指定颜色;区域大小:(xend-xsta)*(yend-ysta)
	
	//===============================底部填充
	ys	=	DisplayBotStartY;
	ye	=	DisplayBotEndY;
	ST7789V_Fill(0,ys,ST7789V_V,ST7789V_H,LCD565_BLACK);				//在指定区域内填充指定颜色;区域大小:(xend-xsta)*(yend-ysta)
	
	ys=DisplayTopStartY+1;
	
	DisplayStart:
	//-------------------------------第一行
	for(i=0;i<sAmpLcd.Display.ReceivedManaCount;i++)
	{
		if(sAmpLcd.Display.DisplaySerial==sAmpLcd.Display.DisplayArry[i].Serial)
		{
			DisplayData	=	sAmpLcd.Display.DisplayArry[i];
			yebac	=	ys;			
			
			//=====================================数量
			num	=	DisplayData.Num;
			ST7789V_ShowChar4836(248,ys,DisplayNumBkColor,DisplayNumFtColor,code_ascii_4836[num/10]);	 	//高通字库测试程序
			ST7789V_ShowChar4836(284,ys,DisplayNumBkColor,DisplayNumFtColor,code_ascii_4836[num%10]);	  //高通字库测试程序
			
			//=====================================显示名称：10个字(20字节)一行						
			
			//-----------------------------------------第一行
			xs	=	0;
			str	=	DisplayData.String;
			len	=	DisplayData.NameLen;		//字节数
			num	=	(ST7789V_V-36*2)/(DisplayNameFtSize/2);			//一行能够显示的数量
			if(len>num)
			{
				ST7789V_ShowStringBK(xs,ys,DisplayNameFtSize,DisplayNameBkColor,DisplayNameFtColor,num,str);				
				len-=num;
				str=&str[num];
				ys+=DisplayNameFtSize;
			}			
			//-----------------------------------------第二行
			if(len>0)
			{
				if(len>num)
				{
					num=num;
				}
				else
				{
					num=len;
				}
				ST7789V_ShowStringBK(xs,ys,DisplayNameFtSize,DisplayNameBkColor,DisplayNameFtColor,num,str);
				ys+=DisplayNameFtSize;
			}
			//=====================================显示序号
			
			ys=yebac+DisplayNameFtSize*2+DisplaySpecFtSize*1;
			
			xs	=	ST7789V_V-DisplaySerialFtSize*3;
			ST7789V_PrintfBK(xs,ys,DisplaySerialFtSize,DisplayNameBkColor,DisplayNameFtColor,"%0.2d/%0.2d",sAmpLcd.Display.DisplaySerial,sAmpLcd.Display.ReceivedManaCount);
			
			//=====================================显示规格
			
			//-----------------------------------------第一行
			xs	=	0;
			xe	=	ST7789V_V-DisplaySerialFtSize*3;
			ys=yebac+DisplayNameFtSize*2+1;
			
			len	=	DisplayData.NameLen;			//字节数
			str	=	&DisplayData.String[len];
			len	=	DisplayData.SpecLen;
			
			num	=	(ST7789V_V-DisplaySerialFtSize*3)/(DisplaySpecFtSize/2);			//一行能够显示的数量
			if(len>num)
			{
				ST7789V_ShowStringBK(0,ys,DisplaySpecFtSize,DisplaySpecBkColor,DisplaySpecFtColor,num,str);
				ys+=DisplaySpecFtSize;
				len-=num;
				str=&str[num];
			}
			//-----------------------------------------第二行
			if(len>0)
			{
				if(len>num)
				{
					num=num;
				}
				else
				{
					num=len;
				}
				ST7789V_ShowStringBK(0,ys,DisplaySpecFtSize,DisplaySpecBkColor,DisplaySpecFtColor,num,str);
			}				
			sAmpLcd.Display.DisplaySerial+=1;			
			break;
		}		
	}
	
	if(ys<ST7789V_H/2)
	{
		ys	=	(DisplayBotStartY-DisplayTopStartY)/2+DisplayTopStartY+3;
		goto DisplayStart;
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
void DisplayManaModel2(void)
{
	unsigned char i	=	0;
	unsigned char len=0;
	unsigned char num=0;
	unsigned char* str;
	
	unsigned char TempLay	=	sAmpLcd.Sys.AddrLay%100;
	unsigned char TempSeg	=	sAmpLcd.Sys.AddrSeg%100;

	
	unsigned short xs=0;
	unsigned short ys=0;
	unsigned short xe=0;
	unsigned short ye=0;
	unsigned short yebac=0;
	
	DisplayDataDef	DisplayData;		//
	

	if(0>=sAmpLcd.Display.ReceivedManaCount)	//没收到数据显示位置号
	{		
		ST7789V_PrintfBK(68,ST7789V_H/2-DisplayNumFtSize/2,DisplayNumFtSize,DisplayNumBkColor,DisplayNumFtColor,"层%0.2d    位%0.2d",TempLay,TempSeg);  //LCD显示测试Printf
		return;
	}
	if(0==sAmpLcd.Display.DisplaySerial)
	{
		sAmpLcd.Display.DisplaySerial=1;
	}
	if(sAmpLcd.Display.DisplaySerial>sAmpLcd.Display.ReceivedManaCount)
	{
		sAmpLcd.Display.DisplaySerial=1;
	}
	
	//=====================================清空区域:名称
	xs	=	0;
	xe	=	ST7789V_V;
	ys	=	DisplayTopStartY;
	ye	=	DisplayBotStartY;
	
	ST7789V_Fill(xs,ys,xe,ye,DisplayNameBkColor);				//在指定区域内填充指定颜色;区域大小:(xend-xsta)*(yend-ysta)	
	
	//===============================顶部填充
	ye=DisplayTopStartY;	
	ST7789V_Fill(0,0,ST7789V_V,ye,LCD565_BLACK);				//在指定区域内填充指定颜色;区域大小:(xend-xsta)*(yend-ysta)
	//===============================中间分隔线填充
	ys	=	(DisplayBotStartY-DisplayTopStartY-DisplayTitleSize-DisplaySeparWidth)/2+DisplayTopStartY+DisplayTitleSize;
	ST7789V_Fill(0,ys-DisplaySeparWidth,ST7789V_V,ys+DisplaySeparWidth,DisplaySeparBkColor);				//在指定区域内填充指定颜色;区域大小:(xend-xsta)*(yend-ysta)
	
	//===============================底部填充
	ys	=	DisplayBotStartY;
	ye	=	DisplayBotEndY;
	ST7789V_Fill(0,ys,ST7789V_V,ST7789V_H,LCD565_BLACK);				//在指定区域内填充指定颜色;区域大小:(xend-xsta)*(yend-ysta)
	//===============================标题填充
	ys	=	DisplayTopStartY;
	ye	=	DisplayTopStartY+DisplayTitleSize;
	ST7789V_Fill(0,ys,ST7789V_V,ye,DisplayTitleBkColor);				//在指定区域内填充指定颜色;区域大小:(xend-xsta)*(yend-ysta)
	//===============================标题分隔线填充
	ys	=	DisplayTopStartY+DisplayTitleSize;
	ye	=	ys+DisplaySeparWidth;
	ST7789V_Fill(0,ys,ST7789V_V,ye,DisplaySeparBkColor);				//在指定区域内填充指定颜色;区域大小:(xend-xsta)*(yend-ysta)
	
	//===============================显示地址
	ST7789V_PrintfBK(1,DisplayTopStartY,16,DisplayTitleBkColor,DisplayTitleFtColor,"层号:%0.2d 位号:%0.2d",TempLay,TempSeg);  //LCD显示测试Printf
	//===============================显示起始
	ys=DisplayTopStartY+DisplayTitleSize+DisplaySeparWidth+1;
	
	DisplayStart:
	//-------------------------------第一行
	for(i=0;i<sAmpLcd.Display.ReceivedManaCount;i++)
	{
		if(sAmpLcd.Display.DisplaySerial==sAmpLcd.Display.DisplayArry[i].Serial)
		{
			unsigned char Sum			=	sAmpLcd.Display.ReceivedManaCount;
			unsigned char Serial	=	sAmpLcd.Display.DisplaySerial;
			
			DisplayData=sAmpLcd.Display.DisplayArry[i];
			
			yebac	=	ys;			
			
			//=====================================显示序号
			if(ys<DisplayTopStartY*4)
			{
				ST7789V_PrintfBK(ST7789V_V-DisplayTitleSize*4,DisplayTopStartY,DisplayTitleSize,DisplayTitleBkColor,DisplayTitleFtColor,"%0.2d/%0.2d页",Serial,Sum);  //LCD显示测试Printf
			}
			else
			{
				ST7789V_PrintfBK(ST7789V_V-DisplayTitleSize*8,DisplayTopStartY,DisplayTitleSize,DisplayTitleBkColor,DisplayTitleFtColor,"%0.2d/%0.2d页 %0.2d/%0.2d页",Serial-1,Sum,Serial,Sum);  //LCD显示测试Printf
			}
			//=====================================显示数量
			num	=	DisplayData.Num;
			xs	=	ST7789V_V-DisplayNumFtSize*2;
			ys	=	yebac+DisplayNameFtSize*2;
			
			ST7789V_PrintfBK(xs,ys,DisplayNumFtSize,DisplayNumBkColor,DisplayNumFtColor,"%0.2d",num);
			xs+=DisplayNumFtSize;
			ST7789V_PrintfBK(xs,ys,32,DisplayNumBkColor,DisplayNumFtColor,"瓶");
			//=====================================显示名称：10个字(20字节)一行			
			xs	=	0;
			ys	=	yebac;
			str	=	DisplayData.String;
			len	=	DisplayData.NameLen;		//字节数
			num	=	(ST7789V_V)/(DisplayNameFtSize/2);			//一行能够显示的数量
			if(len>2*num)
			{
				num=2*num;
			}
			else
			{
				num=len;
			}
			ST7789V_ShowStringBK(xs,ys,DisplayNameFtSize,DisplayNameBkColor,DisplayNameFtColor,num,str);
			ys+=DisplayNameFtSize*2;
			//=====================================显示规格			
			//-----------------------------------------第一行
			xs	=	0;
			xe	=	ST7789V_V-DisplaySerialFtSize*3;
			ys=yebac+DisplayNameFtSize*2+1;
			
			len	=	DisplayData.NameLen;			//字节数
			str	=	&DisplayData.String[len];
			len	=	DisplayData.SpecLen;
			
			num	=	(ST7789V_V-DisplayNumFtSize/2*5)/(DisplaySpecFtSize/2);			//一行能够显示的数量
			if(len>num)
			{
				ST7789V_ShowStringBK(0,ys,DisplaySpecFtSize,DisplaySpecBkColor,DisplaySpecFtColor,num,str);
				ys+=DisplaySpecFtSize;
				len-=num;
				str=&str[num];
			}
			//-----------------------------------------第二行
			if(len>0)
			{
				if(len>num)
				{
					num=num;
				}
				else
				{
					num=len;
				}
				ST7789V_ShowStringBK(0,ys,DisplaySpecFtSize,DisplaySpecBkColor,DisplaySpecFtColor,num,str);
			}				
			sAmpLcd.Display.DisplaySerial+=1;			
			break;
		}		
	}
	
	if(ys<ST7789V_H/2)
	{
		ys	=	(DisplayBotStartY-DisplayTopStartY-DisplayTitleSize-DisplaySeparWidth)/2+DisplayTopStartY+DisplayTitleSize+DisplaySeparWidth*2-1;
		//ys	=	(DisplayBotStartY-DisplayTopStartY-DisplaySeparWidth)/2+DisplayTopStartY+3;
		goto DisplayStart;
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
void DisplayManaModel3(void)
{
	unsigned char i	=	0;
	unsigned char len=0;
	unsigned char num=0;
	unsigned char* str;
	
	unsigned char TempLay	=	sAmpLcd.Sys.AddrLay%100;
	unsigned char TempSeg	=	sAmpLcd.Sys.AddrSeg%100;

	
	unsigned short xs=0;
	unsigned short ys=0;
	unsigned short xe=0;
	unsigned short ye=0;
	unsigned short yebac=0;
	

	if(0>=sAmpLcd.Display.ReceivedManaCount)	//没收到数据显示位置号
	{		
		ST7789V_PrintfBK(68,ST7789V_H/2-DisplayNumFtSize/2,DisplayNumFtSize,DisplayNumBkColor,DisplayNumFtColor,"层%0.2d    位%0.2d",TempLay,TempSeg);  //LCD显示测试Printf
		return;
	}
	if(0==sAmpLcd.Display.DisplaySerial)
	{
		sAmpLcd.Display.DisplaySerial=1;
	}
	if(sAmpLcd.Display.DisplaySerial>sAmpLcd.Display.ReceivedManaCount)
	{
		sAmpLcd.Display.DisplaySerial=1;
	}
	
	//=====================================清空区域:名称
	xs	=	0;
	xe	=	ST7789V_V;
	ys	=	DisplayTopStartY;
	ye	=	DisplayBotStartY;
	
	ST7789V_Fill(xs,ys,xe,ye,DisplayNameBkColor);				//在指定区域内填充指定颜色;区域大小:(xend-xsta)*(yend-ysta)	
	
	//===============================顶部填充
	ye=DisplayTopStartY;	
	ST7789V_Fill(0,0,ST7789V_V,ye,LCD565_BLACK);				//在指定区域内填充指定颜色;区域大小:(xend-xsta)*(yend-ysta)
//	//===============================中间分隔线填充
//	ys	=	(DisplayBotStartY-DisplayTopStartY-DisplayTitleSize-DisplaySeparWidth)/2+DisplayTopStartY+DisplayTitleSize;
//	ST7789V_Fill(0,ys-DisplaySeparWidth,ST7789V_V,ys+DisplaySeparWidth,DisplaySeparBkColor);				//在指定区域内填充指定颜色;区域大小:(xend-xsta)*(yend-ysta)
	
	//===============================底部填充
	ys	=	DisplayBotStartY;
	ye	=	DisplayBotEndY;
	ST7789V_Fill(0,ys,ST7789V_V,ST7789V_H,LCD565_BLACK);				//在指定区域内填充指定颜色;区域大小:(xend-xsta)*(yend-ysta)
	//===============================标题填充
	ys	=	DisplayTopStartY;
	ye	=	DisplayTopStartY+DisplayTitleSize;
	ST7789V_Fill(0,ys,ST7789V_V,ye,DisplayTitleBkColor);				//在指定区域内填充指定颜色;区域大小:(xend-xsta)*(yend-ysta)
	//===============================标题分隔线填充
	ys	=	DisplayTopStartY+DisplayTitleSize;
	ye	=	ys+DisplaySeparWidth;
	ST7789V_Fill(0,ys,ST7789V_V,ye,DisplaySeparBkColor);				//在指定区域内填充指定颜色;区域大小:(xend-xsta)*(yend-ysta)
	
	//===============================显示地址
	ST7789V_PrintfBK(1,DisplayTopStartY,DisplayTitleSize,DisplayTitleBkColor,DisplayTitleFtColor,"%0.2d::%0.2d",TempLay,TempSeg);  //LCD显示测试Printf
	//===============================显示起始
	ys=DisplayTopStartY+DisplayTitleSize+DisplaySeparWidth+1;
	
	DisplayStart:
	//-------------------------------第一行
	for(i=0;i<sAmpLcd.Display.ReceivedManaCount;i++)
	{
		if(sAmpLcd.Display.DisplaySerial==sAmpLcd.Display.DisplayArry[i].Serial)
		{
			unsigned char Sum			=	sAmpLcd.Display.ReceivedManaCount;
			unsigned char Serial	=	sAmpLcd.Display.DisplaySerial;
			yebac	=	ys;			
			
			//=====================================显示序号
			if(ys<DisplayTopStartY*4)
			{
				ST7789V_PrintfBK(ST7789V_V-DisplayTitleSize*4,DisplayTopStartY,DisplayTitleSize,DisplayTitleBkColor,DisplayTitleFtColor,"%0.2d/%0.2d页",Serial,Sum);  //LCD显示测试Printf
			}
			
			//=====================================显示名称：10个字(20字节)一行			
			//-----------------------------------------第一行
			xs	=	0;
			ys	=	yebac;
			str	=	sAmpLcd.Display.DisplayArry[i].String;
			len	=	sAmpLcd.Display.DisplayArry[i].NameLen;		//字节数
			num	=	(ST7789V_V)/(DisplayNameFtSize/2);			//一行能够显示的数量
			ST7789V_ShowStringBKAre(xs,ys,ST7789V_V,ys+DisplayNameFtSize*2,DisplayNameFtSize,DisplayNameBkColor,DisplayNameFtColor,len,str);	//带背景色限定区域显示
			ys+=DisplayNameFtSize*2;
			
			//=====================================显示规格			
			//-----------------------------------------第一行
			xs	=	0;
			xe	=	ST7789V_V-DisplayNumFtSize*2;
			ys=		yebac+DisplayNameFtSize*2+1;
			ye	=	ys+DisplaySpecFtSize*2;
			
			len	=	sAmpLcd.Display.DisplayArry[i].NameLen;			//字节数
			str	=	&sAmpLcd.Display.DisplayArry[i].String[len];
			len	=	sAmpLcd.Display.DisplayArry[i].SpecLen;
			
			ST7789V_ShowStringBKAre(xs,ys,xe,ye,DisplaySpecFtSize,DisplaySpecBkColor,DisplaySpecFtColor,len,str);	//带背景色限定区域显示
			
			//=====================================显示数量
			num	=	sAmpLcd.Display.DisplayArry[i].Num;
			xs	=	ST7789V_V-DisplayNumFtSize*2;
			xe	=	ST7789V_V;
			ys	=	yebac+DisplayNameFtSize*2;
			ye	=	ys+DisplayNumFtSize;
			
			ST7789V_PrintfBK(xs,ys,DisplayNumFtSize,DisplayNumBkColor,DisplayNumFtColor,"%0.2d",num);
			xs+=DisplayNumFtSize;
			//=====================================显示单位			
			ST7789V_PrintfBK(xs,ys,32,DisplayNumBkColor,DisplayNumFtColor,"瓶");
			//ST7789V_ShowStringBKAre(u16 xs,u16 ys,u16 xe,u16 ye,u8 font,u16 BKColor,u16 PenColor,u8 num,u8 *Buffer);	//带背景色限定区域显示
			//ST7789V_ShowStringBKAre(xs,ys,xe,ye,DisplaySpecFtSize,DisplayNumBkColor,DisplayNumFtColor,len,str);	//带背景色限定区域显示
				
			sAmpLcd.Display.DisplaySerial+=1;			
			break;
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
void DisplayManaModel3bac(void)
{
	unsigned char i	=	0;
	unsigned char len=0;
	unsigned char num=0;
	unsigned char* str;
	
	unsigned char TempLay	=	sAmpLcd.Sys.AddrLay%100;
	unsigned char TempSeg	=	sAmpLcd.Sys.AddrSeg%100;

	
	unsigned short xs=0;
	unsigned short ys=0;
	unsigned short xe=0;
	unsigned short ye=0;
	unsigned short yebac=0;
	

	if(0>=sAmpLcd.Display.ReceivedManaCount)	//没收到数据显示位置号
	{		
		ST7789V_PrintfBK(68,ST7789V_H/2-DisplayNumFtSize/2,DisplayNumFtSize,DisplayNumBkColor,DisplayNumFtColor,"层%0.2d    位%0.2d",TempLay,TempSeg);  //LCD显示测试Printf
		return;
	}
	if(0==sAmpLcd.Display.DisplaySerial)
	{
		sAmpLcd.Display.DisplaySerial=1;
	}
	if(sAmpLcd.Display.DisplaySerial>sAmpLcd.Display.ReceivedManaCount)
	{
		sAmpLcd.Display.DisplaySerial=1;
	}
	
	//=====================================清空区域:名称
	xs	=	0;
	xe	=	ST7789V_V;
	ys	=	DisplayTopStartY;
	ye	=	DisplayBotStartY;
	
	ST7789V_Fill(xs,ys,xe,ye,DisplayNameBkColor);				//在指定区域内填充指定颜色;区域大小:(xend-xsta)*(yend-ysta)	
	
	//===============================顶部填充
	ye=DisplayTopStartY;	
	ST7789V_Fill(0,0,ST7789V_V,ye,LCD565_BLACK);				//在指定区域内填充指定颜色;区域大小:(xend-xsta)*(yend-ysta)
//	//===============================中间分隔线填充
//	ys	=	(DisplayBotStartY-DisplayTopStartY-DisplayTitleSize-DisplaySeparWidth)/2+DisplayTopStartY+DisplayTitleSize;
//	ST7789V_Fill(0,ys-DisplaySeparWidth,ST7789V_V,ys+DisplaySeparWidth,DisplaySeparBkColor);				//在指定区域内填充指定颜色;区域大小:(xend-xsta)*(yend-ysta)
	
	//===============================底部填充
	ys	=	DisplayBotStartY;
	ye	=	DisplayBotEndY;
	ST7789V_Fill(0,ys,ST7789V_V,ST7789V_H,LCD565_BLACK);				//在指定区域内填充指定颜色;区域大小:(xend-xsta)*(yend-ysta)
	//===============================标题填充
	ys	=	DisplayTopStartY;
	ye	=	DisplayTopStartY+DisplayTitleSize;
	ST7789V_Fill(0,ys,ST7789V_V,ye,DisplayTitleBkColor);				//在指定区域内填充指定颜色;区域大小:(xend-xsta)*(yend-ysta)
	//===============================标题分隔线填充
	ys	=	DisplayTopStartY+DisplayTitleSize;
	ye	=	ys+DisplaySeparWidth;
	ST7789V_Fill(0,ys,ST7789V_V,ye,DisplaySeparBkColor);				//在指定区域内填充指定颜色;区域大小:(xend-xsta)*(yend-ysta)
	
	//===============================显示地址
	ST7789V_PrintfBK(1,DisplayTopStartY,DisplayTitleSize,DisplayTitleBkColor,DisplayTitleFtColor,"%0.2d::%0.2d",TempLay,TempSeg);  //LCD显示测试Printf
	//===============================显示起始
	ys=DisplayTopStartY+DisplayTitleSize+DisplaySeparWidth+1;
	
	DisplayStart:
	//-------------------------------第一行
	for(i=0;i<sAmpLcd.Display.ReceivedManaCount;i++)
	{
		if(sAmpLcd.Display.DisplaySerial==sAmpLcd.Display.DisplayArry[i].Serial)
		{
			unsigned char Sum			=	sAmpLcd.Display.ReceivedManaCount;
			unsigned char Serial	=	sAmpLcd.Display.DisplaySerial;
			yebac	=	ys;			
			
			//=====================================显示序号
			if(ys<DisplayTopStartY*4)
			{
				ST7789V_PrintfBK(ST7789V_V-DisplayTitleSize*4,DisplayTopStartY,DisplayTitleSize,DisplayTitleBkColor,DisplayTitleFtColor,"%0.2d/%0.2d页",Serial,Sum);  //LCD显示测试Printf
			}
			//=====================================显示数量
			num	=	sAmpLcd.Display.DisplayArry[i].Num;
			xs	=	ST7789V_V-DisplayNumFtSize*2;
			ys	=	yebac+DisplayNameFtSize*2;
			
			ST7789V_PrintfBK(xs,ys,DisplayNumFtSize,DisplayNumBkColor,DisplayNumFtColor,"%0.2d",num);
			xs+=DisplayNumFtSize;
			ST7789V_PrintfBK(xs,ys,32,DisplayNumBkColor,DisplayNumFtColor,"瓶");
			//=====================================显示名称：10个字(20字节)一行			
			//-----------------------------------------第一行
			xs	=	0;
			ys	=	yebac;
			str	=	sAmpLcd.Display.DisplayArry[i].String;
			len	=	sAmpLcd.Display.DisplayArry[i].NameLen;		//字节数
			num	=	(ST7789V_V)/(DisplayNameFtSize/2);			//一行能够显示的数量
			if(len>num)
			{
				ST7789V_ShowStringBK(xs,ys,DisplayNameFtSize,DisplayNameBkColor,DisplayNameFtColor,num,str);				
				len-=num;
				str=&str[num];
				ys+=DisplayNameFtSize;
			}			
			//-----------------------------------------第二行
			if(len>0)
			{
				if(len>num)
				{
					num=num;
				}
				else
				{
					num=len;
				}
				ST7789V_ShowStringBK(xs,ys,DisplayNameFtSize,DisplayNameBkColor,DisplayNameFtColor,num,str);
				ys+=DisplayNameFtSize;
			}			
			
			//=====================================显示规格			
			//-----------------------------------------第一行
			xs	=	0;
			xe	=	ST7789V_V-DisplaySerialFtSize*3;
			ys=yebac+DisplayNameFtSize*2+1;
			
			len	=	sAmpLcd.Display.DisplayArry[i].NameLen;			//字节数
			str	=	&sAmpLcd.Display.DisplayArry[i].String[len];
			len	=	sAmpLcd.Display.DisplayArry[i].SpecLen;
			
			num	=	(ST7789V_V-DisplayNumFtSize/2*5)/(DisplaySpecFtSize/2);			//一行能够显示的数量
			if(len>num)
			{
				ST7789V_ShowStringBK(0,ys,DisplaySpecFtSize,DisplaySpecBkColor,DisplaySpecFtColor,num,str);
				ys+=DisplaySpecFtSize;
				len-=num;
				str=&str[num];
			}
			//-----------------------------------------第二行
			if(len>0)
			{
				if(len>num)
				{
					num=num;
				}
				else
				{
					num=len;
				}
				ST7789V_ShowStringBK(0,ys,DisplaySpecFtSize,DisplaySpecBkColor,DisplaySpecFtColor,num,str);
			}				
			sAmpLcd.Display.DisplaySerial+=1;			
			break;
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
	if(sAmpLcd.Display.LcdPort.ST7789VBColor	!=	BKColor)
	{
		STM32_FLASH_Write(BackColorStartAddr,(unsigned short*)&BKColor,1);						//从指定地址写入指定长度的数据
		BKColor	=	GetBackColor();
		sAmpLcd.Display.LcdPort.ST7789VBColor=BKColor;
	}	
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
	
	sAmpLcd.Display.LcdPort	=	sST7789V;
	
	ST7789V_Initialize(&sAmpLcd.Display.LcdPort);
	
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
	
	sAmpLcd.Display.SpiPort	=	sGT32L32;	
  
  GT32L32_Initialize(&sAmpLcd.Display.SpiPort);				//普通SPI通讯方式配置
	
	//-------------------------------------------层板接口USART1 PA11-RE,PA12-TE
  sRS485Port.USARTx  				= USART1;
  sRS485Port.RS485_CTL_PORT  = GPIOA;
  sRS485Port.RS485_CTL_Pin   = GPIO_Pin_8;
	
	sAmpLcd.Comm.RS485Port	=	sRS485Port;
	
  RS485_DMA_ConfigurationNR			(&sAmpLcd.Comm.RS485Port,19200,gDatasize);	//USART_DMA配置--查询方式，不开中断,配置完默认为接收状态
  GPIO_Configuration_OPP50	(sRS485Port.RS485_CTL_PORT,sRS485Port.RS485_CTL_Pin);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605
  GPIO_ResetBits(sRS485Port.RS485_CTL_PORT,sRS485Port.RS485_CTL_Pin);
	
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
  sAmpLcd.Sys.AddrLay=(temp>>4)&0X0F;  	//层地址
  sAmpLcd.Sys.AddrSeg=temp&0x0F;      	//位地址
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
void AMPLCDV11GUI(void)
{
	unsigned short xs=0;
	unsigned short ys=0;
	unsigned short xe=ST7789V_V-1;
	unsigned short ye=DisplayTopStartY-1;
	
	ST7789V_Clean(DisplayClrColor);
	ST7789V_Fill(xs,ys,xe,ye,LCD565_RED);				//在指定区域内填充指定颜色;区域大小:(xend-xsta)*(yend-ysta)
	
	xs	=	0;
	ys	=	ST7789V_H-DisplayTopStartY+2;
	xe	=	ST7789V_V-1;
	ye	=	ST7789V_H-1;
	
	ST7789V_Fill(xs,ys,xe,ye,LCD565_RED);				//在指定区域内填充指定颜色;区域大小:(xend-xsta)*(yend-ysta)
	
	xs	=	0;
	ys	=	ST7789V_H/2-2;
	xe	=	ST7789V_V-1;
	ye	=	ST7789V_H/2+2;
	
	ST7789V_Fill(xs,ys,xe,ye,LCD565_RED);				//在指定区域内填充指定颜色;区域大小:(xend-xsta)*(yend-ysta)
	
}
#endif
