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
	
	//SysTick_DeleymS(500);				//SysTick延时nmS
	
  HW_Configuration(); 

	DataInitialize();	
  
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
  

	IWDG_Feed();								//独立看门狗喂狗
//	Tim_Server();
  if(FlashTime==0)
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
			DisplayManaModel7();
		#endif
//		ST7789V_Clean(0xFFDE);
		//DisplayManaStaticTest1();
  }
	if(FlashTime++>2000)
		FlashTime=0;
  
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
void DisplayManaStaticTest1(void)
{

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
void DisplayManaModel6(void)
{
//	unsigned char i	=	0;
//	unsigned char len=0;
//	unsigned char num=0;
//	unsigned char size=0;
//	unsigned char offset=0;
//	unsigned char	buffer[256];
//	unsigned char* str;
//	
//	unsigned char TempLay	=	sAmpLcd.Sys.AddrLay%100;
//	unsigned char TempSeg	=	sAmpLcd.Sys.AddrSeg%100;
//	
//	unsigned short xs=0;
//	unsigned short ys=0;
//	unsigned short xe=0;
//	unsigned short ye=0;
//	unsigned short yebac=0;
//	
//	ListDef	DisplayData;		//
//	

//	if(0>=sAmpLcd.Windows.ReceivedManaCount)	//没收到数据显示位置号
//	{		
//		ST7789V_PrintfBK(68,ST7789V_H/2-DisplayNumFtSize/2,DisplayNumFtSize,DisplayNumBkColor,DisplayNumFtColor,"层%0.2d    位%0.2d",TempLay,TempSeg);  //LCD显示测试Printf
//		return;
//	}
//	if(0==sAmpLcd.Display.DisplaySerial)
//	{
//		sAmpLcd.Display.DisplaySerial=1;
//	}
//	if(sAmpLcd.Display.DisplaySerial>sAmpLcd.Display.ReceivedManaCount)
//	{
//		sAmpLcd.Display.DisplaySerial=1;
//	}
//	
//	//=====================================清空区域:名称
//	xs	=	0;
//	xe	=	ST7789V_V;
//	ys	=	DisplayTopStartY;
//	ye	=	DisplayBotStartY;
//	
//	//ST7789V_Fill(xs,ys,xe,ye,DisplayClrColor);				//在指定区域内填充指定颜色;区域大小:(xend-xsta)*(yend-ysta)	
//	
//	//===============================顶部填充
//	ye=DisplayTopStartY;	
//	ST7789V_Fill(0,0,ST7789V_V,ye,LCD565_BLACK);				//在指定区域内填充指定颜色;区域大小:(xend-xsta)*(yend-ysta)
//	//===============================中间分隔线填充
//	ys	=	(DisplayBotStartY-DisplayTopStartY-DisplayTitleSize-DisplaySeparWidth)/2+DisplayTopStartY+DisplayTitleSize;
//	ST7789V_Fill(0,ys-DisplaySeparWidth,ST7789V_V,ys+DisplaySeparWidth,DisplaySeparBkColor);				//在指定区域内填充指定颜色;区域大小:(xend-xsta)*(yend-ysta)
//	
//	//===============================底部填充
//	ys	=	DisplayBotStartY;
//	ye	=	DisplayBotEndY;
//	ST7789V_Fill(0,ys,ST7789V_V,ST7789V_H,LCD565_BLACK);				//在指定区域内填充指定颜色;区域大小:(xend-xsta)*(yend-ysta)
//	//===============================标题填充
//	ys	=	DisplayTopStartY;
//	ye	=	DisplayTopStartY+DisplayTitleSize;
//	ST7789V_Fill(0,ys,ST7789V_V,ye,DisplayTitleBkColor);				//在指定区域内填充指定颜色;区域大小:(xend-xsta)*(yend-ysta)
//	//===============================标题分隔线填充
//	ys	=	DisplayTopStartY+DisplayTitleSize;
//	ye	=	ys+DisplaySeparWidth;
//	ST7789V_Fill(0,ys,ST7789V_V,ye,DisplaySeparBkColor);				//在指定区域内填充指定颜色;区域大小:(xend-xsta)*(yend-ysta)
//	
//	//===============================显示地址
//	ST7789V_PrintfBK(1,DisplayTopStartY,16,DisplayTitleBkColor,DisplayTitleFtColor,"层号:%0.2d 位号:%0.2d",TempLay,TempSeg);  //LCD显示测试Printf
//	//===============================显示起始
//	ys=DisplayTopStartY+DisplayTitleSize+DisplaySeparWidth+1;
//	
//	DisplayStart:
//	//-------------------------------第一行
//	for(i=0;i<sAmpLcd.Display.ReceivedManaCount;i++)
//	{
//		if(sAmpLcd.Display.DisplaySerial==sAmpLcd.Display.DisplayArry[i].ListNum)
//		{
//			unsigned char Sum			=	sAmpLcd.Display.ReceivedManaCount;
//			unsigned char Serial	=	sAmpLcd.Display.DisplaySerial;
//			
//			DisplayData=sAmpLcd.Display.DisplayArry[i];
//			
//			DisplayName(DisplayData);				//显示名称
//			
//			DisplayNumber(DisplayData);			//显示数量和单位
//			
//			DisplayByName(DisplayData);			//显示别名
//			
//			DisplayVender(DisplayData);			//显示厂家名称
//			DisplaySpec(DisplayData);				//显示规格
//			DisplayCode(DisplayData);				//显示编码
////			DisplayNumber(DisplayData);			//显示数量和单位
//			sAmpLcd.Display.DisplaySerial+=1;	
//			break;
//		}		
//	}
//	if(sAmpLcd.Display.WinInfo.StartX<ST7789V_H/2)
//	{
//		goto DisplayStart;
//	}
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
void DisplayManaModel7(void)
{
	unsigned char i	=	0;
	unsigned char DaulFlag	=	0;
	unsigned char len=0;
	unsigned char num=0;
	unsigned char size=0;
	unsigned char offset=0;
	unsigned char MaxNameList=0;
	unsigned char	buffer[256];
	unsigned char* str;
	
	unsigned char TempLay	=	sAmpLcd.Sys.AddrLay%100;
	unsigned char TempSeg	=	sAmpLcd.Sys.AddrSeg%100;
	
	unsigned short xs=0;
	unsigned short ys=0;
	unsigned short xe=0;
	unsigned short ye=0;
	unsigned short yebac=0;
	unsigned short StartPixelY	=	0;
	
	ListDef*		List;
	
	MaxNameList	=	sAmpLcd.Windows.ManaData.MaxNameList;
	List	=	sAmpLcd.Windows.ManaData.List;
	i=sAmpLcd.Windows.ManaData.Serial;
	
	DisplayGui();				//显示界面
	
	for(;i<=MaxNameList;i++)
	{	
		if(0!=List[i].ListNum)
		{			
			DisplayString(List[i]);
			StartPixelY	=	sAmpLcd.Windows.ManaData.StartPixelY;
			if(StartPixelY>sAmpLcd.Windows.WinInfo.PxyValid.YV/2+sAmpLcd.Windows.WinInfo.PxyTopFill.YV+sAmpLcd.Windows.WinInfo.FtTitle.Size)
			{
				return;
			}
			DaulFlag	=	1;
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
void DisplayGui(void)
{
	unsigned char i	=	0;
	unsigned char len=0;
	unsigned char num=0;
	unsigned char size=0;
	unsigned char offset=0;
	unsigned char	buffer[256];
	unsigned char* str;

	unsigned short xs=0;
	unsigned short ys=0;
	unsigned short xe=0;
	unsigned short ye=0;
	unsigned short ysum=0;
	unsigned short yebac=0;
	unsigned short ValidX;		//水平有效使用点
	unsigned short ValidY;		//垂直有效使用点
	
	unsigned short BackColor;	//背景色
	unsigned short PenColor;	//画笔色
	unsigned short FontSize;	//字体大小
	
	WinInfoDef	WinInfo;			//显示字体信息
	//=================================初始化数据
	WinInfo	=	sAmpLcd.Windows.WinInfo;							//显示参数信息
	//-----------------------------------------------------顶端边框
	xs	=	0;
	xe	=	sAmpLcd.Windows.WinInfo.PxyPixel.XH-1;
	ys	=	0;
	ye	=	sAmpLcd.Windows.WinInfo.PxyTopFill.YV-1;
	BackColor	=	sAmpLcd.Windows.WinInfo.FtTitle.BackColor;
	ST7789V_Fill(xs,ys,xe,ye,0x0000);	//纯黑填充
	//-----------------------------------------------------底部边框
	xs	=	0;
	xe	=	sAmpLcd.Windows.WinInfo.PxyPixel.XH-1;
	ys	=	sAmpLcd.Windows.WinInfo.PxyPixel.YV-sAmpLcd.Windows.WinInfo.PxyBotFill.YV-1;
	ye	=	sAmpLcd.Windows.WinInfo.PxyPixel.YV-1;
	BackColor	=	sAmpLcd.Windows.WinInfo.FtTitle.BackColor;
	ST7789V_Fill(xs,ys,xe,ye,0x0000);	//纯黑填充
	//-----------------------------------------------------左边边框
	xs	=	0;
	xe	=	sAmpLcd.Windows.WinInfo.PxyLeftFill.XH-1;
	ys	=	0;
	ye	=	sAmpLcd.Windows.WinInfo.PxyPixel.YV-1;
	BackColor	=	sAmpLcd.Windows.WinInfo.FtTitle.BackColor;
	ST7789V_Fill(xs,ys,xe,ye,0x0000);	//纯黑填充
	//-----------------------------------------------------清空显示区
	xs	=	sAmpLcd.Windows.WinInfo.PxyLeftFill.XH;
	xe	=	sAmpLcd.Windows.WinInfo.PxyPixel.XH;
	ys	=	sAmpLcd.Windows.WinInfo.PxyTopFill.YV;
	ye	=	sAmpLcd.Windows.WinInfo.PxyPixel.YV-sAmpLcd.Windows.WinInfo.PxyBotFill.YV-2;
	BackColor	=	sAmpLcd.Windows.WinInfo.FtDefault.BackColor;
	ST7789V_Fill(xs,ys,xe,ye,BackColor);	//默认背景色填充
	//------------------------------------------Y起始点
	sAmpLcd.Windows.ManaData.StartPixelY	=WinInfo.PxyTopFill.YV+WinInfo.FtTitle.Size+WinInfo.FtSepar.Size;
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
void DisplayString(ListDef Node)
{
//	unsigned char i	=	0;
//	unsigned char len=0;
	unsigned char num=0;
//	unsigned char size=0;
	unsigned char offset=0;
	unsigned char	str[256];
	unsigned char	i=0;
	unsigned char	strtype		=	0;		//字符串类型
	unsigned char	strLen		=	0;		//字符串长度

	unsigned char	Line			=	0;		//可显示行数
	
	unsigned char		StartPixelY	=	0;
	
	unsigned char* Name;

	unsigned short xs=0;	//字体显示坐标信息
	unsigned short ys=0;
	unsigned short xe=0;
	unsigned short ye=0;
	
	unsigned short Fxs=0;	//填充背景色坐标信息
	unsigned short Fys=0;
	unsigned short Fxe=0;
	unsigned short Fye=0;
	
	unsigned short ysum=0;
	unsigned short yebac=0;
	unsigned short ValidX;		//水平有效使用点
	unsigned short ValidY;		//垂直有效使用点
	
	unsigned short BackColor;	//背景色
	unsigned short PenColor;	//画笔色
	unsigned short FontSize;	//字体大小
	
	unsigned short	ValidXH;			//X--水平有效点数
	unsigned short	ValidYV;			//Y--垂直有效点数
	
	unsigned short	StartYV;
	
	
	ParaDef*		Para;
	ListDef*		List;
	WinInfoDef	WinInfo;			//显示字体信息
	//=================================初始化数据
	List		=	sAmpLcd.Windows.ManaData.List;
	WinInfo	=	sAmpLcd.Windows.WinInfo;							//显示参数信息
	ValidXH	=	sAmpLcd.Windows.WinInfo.PxyValid.XH;
	ValidYV	=	sAmpLcd.Windows.WinInfo.PxyValid.YV;
	
	StartPixelY	=	sAmpLcd.Windows.ManaData.StartPixelY;
	
	xs	=	sAmpLcd.Windows.WinInfo.PxyLeftFill.XH;
	ys	=	StartPixelY;

	
	strtype	=	0x01;		//从名称开始
	
	//=================================显示数据准备
	DisplayStart:
	Fxs	=	sAmpLcd.Windows.WinInfo.PxyLeftFill.XH;
	//Fxe	=	Fxs+Node.ParaName.XH;
	Fys	=	StartPixelY;
	//Fye	=	Fys+Node.ParaName.YV;
	
	xs	=	sAmpLcd.Windows.WinInfo.PxyLeftFill.XH;
	ys	=	StartPixelY;
	
	switch(strtype)
	{
		case	0x01:	//商品名类型
			BackColor	=	WinInfo.FtName.BackColor;
			PenColor	=	WinInfo.FtName.PenColor;
			FontSize	=	WinInfo.FtName.Size;
		
			strLen		=	Node.ParaName.len;
			offset		=	Node.ParaName.Offset;
			memcpy(str,&Node.String[offset],strLen);			
		
			Fxe	=	Fxs+Node.ParaName.XH;
			Fye	=	Fys+Node.ParaName.YV;
		
			if(Node.ParaName.YV	==	FontSize)	//单行剧中显示
			{
				unsigned short tempx=0;
				tempx	=	strLen*(FontSize/2);				//实际显示占用的点数
				tempx	=	Node.ParaName.XH	-	tempx;	//剩余空闲点数
				tempx	=	tempx/2;										//平均剩余空间
				
				xs	=	tempx+sAmpLcd.Windows.WinInfo.PxyLeftFill.XH;
				xe	=	xs+strLen*(FontSize/2);		//
			}
			else
			{
				xs	=	sAmpLcd.Windows.WinInfo.PxyLeftFill.XH;
				xe	=	ys+Node.ParaName.XH;
			}
			
			ye	=	ys+Node.ParaName.YV;
			
			//-------------------------------------准备下一项内容显示参数
			StartPixelY+=Node.ParaName.YV;
			strtype	=	0x02;
		break;
		case	0x02:	//显示别名
			Name	=	"别名:";
			num		=	strlen("别名:");
		
			BackColor	=	WinInfo.FtByName.BackColor;
			PenColor	=	WinInfo.FtByName.PenColor;
			FontSize	=	WinInfo.FtByName.Size;
		
			strLen		=	Node.ParaByName.len;
			offset		=	Node.ParaByName.Offset;

			memcpy(str,Name,num);
			memcpy(&str[num],&Node.String[offset],strLen);
			strLen	=	strLen+num;
		
			
		
			Fxe	=	Fxs+Node.ParaByName.XH;
			Fye	=	Fys+Node.ParaByName.YV;

			xe	=	xs+Node.ParaByName.XH;		//
			ye	=	ys+Node.ParaByName.YV;
			//-------------------------------------准备下一项内容显示参数
			StartPixelY+=Node.ParaByName.YV;
			strtype	=	0x03;
		break;
		case	0x03:	//显示厂家
			Name	=	"厂家:";
			num		=	strlen("厂家:");
			
			BackColor	=	WinInfo.FtVender.BackColor;
			PenColor	=	WinInfo.FtVender.PenColor;
			FontSize	=	WinInfo.FtVender.Size;
		
			strLen		=	Node.ParaVender.len;
			offset		=	Node.ParaVender.Offset;

			memcpy(str,Name,num);
			memcpy(&str[num],&Node.String[offset],strLen);
			strLen	=	strLen+num;
		
			
		
			Fxe	=	Fxs+Node.ParaVender.XH;
			Fye	=	Fys+Node.ParaVender.YV;

			xe	=	xs+Node.ParaVender.XH;		//
			ye	=	ys+Node.ParaVender.YV;
			//-------------------------------------准备下一项内容显示参数
			StartPixelY+=Node.ParaSpec.YV;
			strtype	=	0x04;
		break;
		case	0x04:	//显示编码
			Name	=	"编码:";
			num		=	strlen("编码:");
		
			strLen		=	Node.ParaCode.len;
			offset		=	Node.ParaCode.Offset;

			memcpy(str,Name,num);
			memcpy(&str[num],&Node.String[offset],strLen);
			strLen	=	strLen+num;
		
			BackColor	=	WinInfo.FtCode.BackColor;
			PenColor	=	WinInfo.FtCode.PenColor;
			FontSize	=	WinInfo.FtCode.Size;
		
			Fxe	=	Fxs+Node.ParaCode.XH;
			Fye	=	Fys+Node.ParaCode.YV;

			xe	=	xs+Node.ParaCode.XH;		//
			ye	=	ys+Node.ParaCode.YV;
			//-------------------------------------准备下一项内容显示参数
			StartPixelY+=Node.ParaCode.YV;
			strtype	=	0x05;
		break;
		case	0x05:	//显示规格
			Name	=	"规格:";
			num		=	strlen("规格:");
		
			strLen		=	Node.ParaSpec.len;
			offset		=	Node.ParaSpec.Offset;

			memcpy(str,Name,num);
			memcpy(&str[num],&Node.String[offset],strLen);
			strLen	=	strLen+num;
		
			BackColor	=	WinInfo.FtSpec.BackColor;
			PenColor	=	WinInfo.FtSpec.PenColor;
			FontSize	=	WinInfo.FtSpec.Size;
		
			Fxe	=	Fxs+Node.ParaSpec.XH;
			Fye	=	Fys+Node.ParaSpec.YV;

			xe	=	xs+Node.ParaSpec.XH;		//
			ye	=	ys+Node.ParaSpec.YV;
			//-------------------------------------准备下一项内容显示参数
			StartPixelY+=Node.ParaSpec.YV;
			strtype	=	0x07;
		break;
		case	0x06:	//显示数量和单位
//			Name	=	"数量:";
//			num		=	strlen("数量:");
//		
//			strLen		=	Node.ParaSpec.len;
//			offset		=	Node.ParaSpec.Offset;

//			memcpy(str,Name,num);
//			memcpy(&str[num],&Node.String[offset],strLen);
//			strLen	=	strLen+num;
//		
//			BackColor	=	WinInfo.FtSpec.BackColor;
//			PenColor	=	WinInfo.FtSpec.PenColor;
//			FontSize	=	WinInfo.FtSpec.Size;
//		
//			Fxe	=	Fxs+Node.ParaSpec.XH;
//			Fye	=	Fys+Node.ParaSpec.YV;

//			xe	=	xs+Node.ParaSpec.XH;		//
//			ye	=	ys+Node.ParaSpec.YV;
//			//-------------------------------------准备下一项内容显示参数
//			StartPixelY+=Node.ParaSpec.YV;
//			strtype	=	0x07;
		break;
		default:return;	//未找到类型数据
	}
	//=================================补充数据
	
	//=================================显示数据
	DisplayData:
	ST7789V_Fill(Fxs,Fys,Fxe,Fye,BackColor);	//背景色填充/擦除/清除	
	ST7789V_ShowStringBKAre(xs,ys,xe,ye,FontSize,BackColor,PenColor,strLen,str);	//带背景色限定区域显示
	StartPixelY+=1;
	sAmpLcd.Windows.ManaData.StartPixelY	=	StartPixelY;
	
	goto DisplayStart;
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
void DisplayName(const ListDef Node)
{
//	unsigned char i	=	0;
//	unsigned char len=0;
//	unsigned char num=0;
//	unsigned char size=0;
//	unsigned char offset=0;
//	unsigned char	buffer[256];
	unsigned char* str;

	unsigned short xs=0;
	unsigned short ys=0;
	unsigned short xe=0;
	unsigned short ye=0;
//	unsigned short ysum=0;
//	unsigned short yebac=0;
//	unsigned short ValidX;		//水平有效使用点
//	unsigned short ValidY;		//垂直有效使用点
//	
	unsigned short BackColor;	//背景色
	unsigned short PenColor;	//画笔色
	unsigned short FontSize;	//字体大小
//	
//	
//	//unsigned short DisplayNewStartY;
//	
//	
//	WinFontDef	WinFont	=	sAmpLcd.Display.WinFont;			//显示配置
//	WinInfoDef	WinInfo	=	sAmpLcd.Display.WinInfo;
//	WinGuiDef		WinGui	=	sAmpLcd.Display.WinGui;
//	
//	BackColor	=	WinFont.FtName.BackColor;
//	PenColor	=	WinFont.FtName.PenColor;
//	FontSize	=	WinFont.FtName.Size;
//	
//	//-----------------------------------------------------检查有无数据
//	len=DisplayData.ParaName.len;	
//	if(0==len)
//	{
//		return;
//	}
//	//-----------------------------------------------------获取显示数据
//	len			=	DisplayData.ParaName.len;
//	offset	=	DisplayData.ParaName.Offset;	
//	memcpy(buffer,&DisplayData.String[offset],len);	
//	//-----------------------------------------------------清空显示区域
//	xs	=	WinInfo.PxyLeftFill.XH;	
//	xe	=	WinInfo.PxyRigthFill.XH;
//	
//	ys	=	WinGui.StartXY.YV;	
//	ye	=	ys+FontSize*WinInfo.PxyName.YV;
//	
//	ST7789V_Fill(xs,ys,xe,ye,BackColor);
//	
//	StartDisplay:
//	//-----------------------------------------------------获取显示区域(如果是单行则居中显示)
//	if((len*FontSize/2)<WinInfo.PxyValid.XH)
//	{
//		xs	=	WinInfo.PxyLeftFill.XH+((WinInfo.PxyValid.XH-(len*FontSize/2))/2);
//	}
//	else
//	{
//		xs	=	WinInfo.PxyLeftFill.XH;
//	}		
//	xe	=	WinInfo.PxyRigthFill.XH;
//	
//	ys	=	WinGui.StartXY.YV;	
//	ye	=	ys+FontSize*WinInfo.PxyName.YV;
//	//-----------------------------------------------------显示数据
//	ST7789V_ShowStringBKAre(xs,ys,xe,ye,FontSize,BackColor,PenColor,len,buffer);	//带背景色限定区域显示
//	
//	WinGui.StartXY.YV=ye;
//	
//	sAmpLcd.Display.WinInfo	=	WinInfo;
//	sAmpLcd.Display.WinGui.StartXY.YV	=	WinGui.StartXY.YV;
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
void DisplayByName(const ListDef Node)
{
//	unsigned char i	=	0;
//	unsigned char len=0;
//	unsigned char num=0;
//	unsigned char size=0;
//	unsigned char offset=0;
//	unsigned char	buffer[256];
//	unsigned char str[]	=	"别名:";
//	unsigned char	strl;

//	unsigned short xs=0;
//	unsigned short ys=0;
//	unsigned short xe=0;
//	unsigned short ye=0;
//	unsigned short ysum=0;
//	unsigned short yebac=0;
//	unsigned short ValidX;		//水平有效使用点
//	unsigned short ValidY;		//垂直有效使用点
//	
//	unsigned short BackColor;	//背景色
//	unsigned short PenColor;	//画笔色
//	unsigned short FontSize;	//字体大小
//	
//	
//	WinFontDef	WinFont	=	sAmpLcd.Display.WinFont;			//显示配置
//	WinInfoDef	WinInfo	=	sAmpLcd.Display.WinInfo;
//	WinGuiDef		WinGui	=	sAmpLcd.Display.WinGui;
//	
//	BackColor	=	WinFont.FtByName.BackColor;
//	PenColor	=	WinFont.FtByName.PenColor;
//	FontSize	=	WinFont.FtByName.Size;
//	
//	//-----------------------------------------------------检查有无数据
//	len=DisplayData.ParaByName.len;	
//	if(0==len)
//	{
//		return;
//	}
//	//-----------------------------------------------------获取显示数据
//	len			=	DisplayData.ParaByName.len;
//	offset	=	DisplayData.ParaByName.Offset;	
//	memcpy(buffer,&DisplayData.String[offset],len);	
//	
//	//-----------------------------------------------------获取显示区域
//	strl	=	strlen(str);	
//	memcpy(buffer,str,strl);
//	offset	=	DisplayData.ParaByName.Offset;
//	
//	len	=	DisplayData.ParaByName.len;
//	memcpy(&buffer[strl],&DisplayData.String[offset],len);
//	
//	len+=strl;
//	
//	//-----------------------------------------------------清空显示区域
//	xs	=	WinInfo.PxyLeftFill.XH;	
//	//xe	=	WinConf.WinEndX;
//	xe	=	xs+FontSize*WinInfo.PxyByName.XH/2;
//	
//	ys	=	WinGui.StartXY.YV;	
//	ye	=	ys+FontSize*WinInfo.PxyByName.YV;
//	
//	ST7789V_Fill(xs,ys,xe,ye,BackColor);
//	
//	StartDisplay:
//	//-----------------------------------------------------显示数据
//	ST7789V_ShowStringBKAre(xs,ys,xe,ye,FontSize,BackColor,PenColor,len,buffer);	//带背景色限定区域显示
//	
//	WinGui.StartXY.YV=ye;
//	
//	sAmpLcd.Display.WinInfo	=	WinInfo;
//	sAmpLcd.Display.WinGui.StartXY.YV	=	WinGui.StartXY.YV;
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
void DisplayVender(const ListDef Node)
{
//	unsigned char i	=	0;
//	unsigned char len=0;
//	unsigned char num=0;
//	unsigned char size=0;
//	unsigned char offset=0;
//	unsigned char	buffer[256];
//	unsigned char str[]	=	"厂家:";
//	unsigned char	strl;

//	unsigned short xs=0;
//	unsigned short ys=0;
//	unsigned short xe=0;
//	unsigned short ye=0;
//	unsigned short ysum=0;
//	unsigned short yebac=0;
//	unsigned short ValidX;		//水平有效使用点
//	unsigned short ValidY;		//垂直有效使用点
//	
//	unsigned short BackColor;	//背景色
//	unsigned short PenColor;	//画笔色
//	unsigned short FontSize;	//字体大小
//	

//	
//	
//	WinFontDef	WinFont	=	sAmpLcd.Display.WinFont;			//显示配置
//	WinInfoDef	WinInfo	=	sAmpLcd.Display.WinInfo;
//	WinGuiDef		WinGui	=	sAmpLcd.Display.WinGui;
//	
//	BackColor	=	WinFont.FtVender.BackColor;
//	PenColor	=	WinFont.FtVender.PenColor;
//	FontSize	=	WinFont.FtVender.Size;
//	//-----------------------------------------------------检查有无数据
//	len=DisplayData.ParaVender.len;	
//	if(0==len)
//	{
//		return;
//	}	
//	
//	//-----------------------------------------------------获取显示区域
//	strl	=	strlen(str);	
//	memcpy(buffer,str,strl);
//	offset	=	DisplayData.ParaVender.Offset;
//	
//	len	=	DisplayData.ParaVender.len;
//	memcpy(&buffer[strl],&DisplayData.String[offset],len);
//	
//	len+=strl;
//	
//	goto StartDisplayVender;
//	
//	//==========================================判断起始点在中线上还是下
//	//==========================================开始显示商品名称
//	StartDisplayVender:
//	
//	xs	=	WinInfo.PxyLeftFill.XH;
//	xe	=	xs+FontSize*WinInfo.PxyVender.XH/2;
//	
//	ys	=	WinGui.StartXY.YV;
//	
//	if(0!=len%WinInfo.PxyVender.XH)
//	{
//		ye	=	ys+FontSize*(len/WinInfo.PxyVender.XH+1);
//	}
//	else
//	{
//		ye	=	ys+FontSize*WinInfo.PxyVender.YV;
//	}	
//	//-----------------------------------------------------背景填充
//	ST7789V_Fill(xs,ys,xe,ye,BackColor);
//	//-----------------------------------------------------显示数据
//	ST7789V_ShowStringBKAre(xs,ys,xe,ye,FontSize,BackColor,PenColor,len,buffer);	//带背景色限定区域显示
//	
//	WinGui.StartXY.YV=ye;
//	
//	sAmpLcd.Display.WinInfo	=	WinInfo;
//	sAmpLcd.Display.WinGui.StartXY.YV	=	WinGui.StartXY.YV;
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
void DisplaySpec(const ListDef Node)
{
//	unsigned char i	=	0;
//	unsigned char len=0;
//	unsigned char num=0;
//	unsigned char size=0;
//	unsigned char offset=0;
//	unsigned char	buffer[256];
//	unsigned char str[]	=	"规格:";
//	unsigned char	strl;

//	unsigned short xs=0;
//	unsigned short ys=0;
//	unsigned short xe=0;
//	unsigned short ye=0;
//	unsigned short ysum=0;
//	unsigned short yebac=0;
//	unsigned short ValidX;		//水平有效使用点
//	unsigned short ValidY;		//垂直有效使用点
//	
//	unsigned short BackColor;	//背景色
//	unsigned short PenColor;	//画笔色
//	unsigned short FontSize;	//字体大小
//	

//	
//	
//	WinFontDef	WinFont	=	sAmpLcd.Display.WinFont;			//显示配置
//	WinInfoDef	WinInfo	=	sAmpLcd.Display.WinInfo;
//	WinGuiDef		WinGui	=	sAmpLcd.Display.WinGui;
//	
//	BackColor	=	WinFont.FtSpec.BackColor;
//	PenColor	=	WinFont.FtSpec.PenColor;
//	FontSize	=	WinFont.FtSpec.Size;
//	//-----------------------------------------------------检查有无数据
//	len=DisplayData.ParaSpec.len;	
//	if(0==len)
//	{
//		return;
//	}
//	
//	//-----------------------------------------------------获取显示区域	
//	//len			=	WinInfo.LineCoSpec*WinInfo.RowCoSpec;
//	len=DisplayData.ParaSpec.len;

//	strl	=	strlen(str);	
//	memcpy(buffer,str,strl);
//	offset	=	DisplayData.ParaSpec.Offset;
//	
//	memcpy(&buffer[strl],&DisplayData.String[offset],len);
//	
//	len+=strl;
//	
//	goto StartDisplaySpec;
//	
//	//==========================================判断起始点在中线上还是下
//	//==========================================开始显示商品名称
//	StartDisplaySpec:
//	
//	xs	=	WinInfo.PxyLeftFill.XH;
//	xe	=	xs+FontSize*WinInfo.PxySpec.XH/2;
//	
//	ys	=	WinGui.StartXY.YV;
//	
//	if(0!=len%WinInfo.PxySpec.XH)
//	{
//		ye	=	ys+FontSize*(len/WinInfo.PxySpec.XH+1);
//	}
//	else
//	{
//		ye	=	ys+FontSize*WinInfo.PxySpec.YV;
//	}	
//	//-----------------------------------------------------背景填充
//	ST7789V_Fill(xs,ys,xe,ye,BackColor);
//	//-----------------------------------------------------显示数据
//	ST7789V_ShowStringBKAre(xs,ys,xe,ye,FontSize,BackColor,PenColor,len,buffer);	//带背景色限定区域显示
//	
//	WinGui.StartXY.YV=ye;
//	
//	sAmpLcd.Display.WinInfo	=	WinInfo;
//	sAmpLcd.Display.WinGui.StartXY.YV	=	WinGui.StartXY.YV;
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
void DisplayCode(const ListDef Node)
{
//	unsigned char i	=	0;
//	unsigned char len=0;
//	unsigned char num=0;
//	unsigned char size=0;
//	unsigned char offset=0;
//	unsigned char	buffer[256];
//	unsigned char str[]	=	"编码:";
//	unsigned char	strl;

//	unsigned short xs=0;
//	unsigned short ys=0;
//	unsigned short xe=0;
//	unsigned short ye=0;
//	unsigned short ysum=0;
//	unsigned short yebac=0;
//	unsigned short ValidX;		//水平有效使用点
//	unsigned short ValidY;		//垂直有效使用点
//	
//	unsigned short BackColor;	//背景色
//	unsigned short PenColor;	//画笔色
//	unsigned short FontSize;	//字体大小
//	

//	
//	
//	WinFontDef	WinFont	=	sAmpLcd.Display.WinFont;			//显示配置
//	WinInfoDef	WinInfo	=	sAmpLcd.Display.WinInfo;
//	WinGuiDef		WinGui	=	sAmpLcd.Display.WinGui;
//	
//	BackColor	=	WinFont.FtCode.BackColor;
//	PenColor	=	WinFont.FtCode.PenColor;
//	FontSize	=	WinFont.FtCode.Size;
//	
//	//-----------------------------------------------------检查有无数据
//	len=DisplayData.ParaCode.len;	
//	if(0==len)
//	{
//		return;
//	}
//	//-----------------------------------------------------获取显示区域	
//	len			=	WinInfo.PxyCode.XH*WinInfo.PxyCode.YV;
//	if(DisplayData.ParaSpec.len<len)
//	{
//		len=DisplayData.ParaCode.len;
//	}
//	strl	=	strlen(str);	
//	memcpy(buffer,str,strl);
//	offset	=	DisplayData.ParaCode.Offset;
//	
//	memcpy(&buffer[strl],&DisplayData.String[offset],len);
//	
//	len+=strl;
//	
//	goto StartDisplay;
//	
//	//==========================================判断起始点在中线上还是下
//	//==========================================开始显示商品名称
//	StartDisplay:
//	
//	xs	=	WinInfo.PxyLeftFill.XH;
//	xe	=	xs+FontSize*WinInfo.PxyCode.XH/2;
//	
//	ys	=	WinGui.StartXY.YV;
//	
//	if(0!=len%WinInfo.PxyCode.XH)
//	{
//		ye	=	ys+FontSize*(len/WinInfo.PxyCode.XH+1);
//	}
//	else
//	{
//		ye	=	ys+FontSize*WinInfo.PxyCode.YV;
//	}	
//	//-----------------------------------------------------背景填充
//	ST7789V_Fill(xs,ys,xe,ye,BackColor);
//	//-----------------------------------------------------显示数据
//	ST7789V_ShowStringBKAre(xs,ys,xe,ye,FontSize,BackColor,PenColor,len,buffer);	//带背景色限定区域显示
//	
//	WinGui.StartXY.YV=ye;
//	
//	sAmpLcd.Display.WinInfo	=	WinInfo;
//	sAmpLcd.Display.WinGui.StartXY.YV	=	WinGui.StartXY.YV;
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
void DisplayNumber(const ListDef Node)
{
//	unsigned char i	=	0;
//	unsigned char len=0;
//	unsigned char num=0;
//	unsigned char size=0;
//	unsigned char offset=0;
//	unsigned char	buffer[256];
//	unsigned char* str;
//	unsigned char	strl;

//	unsigned short xs=0;
//	unsigned short ys=0;
//	unsigned short xe=0;
//	unsigned short ye=0;
//	unsigned short ysum=0;
//	unsigned short yebac=0;
//	unsigned short ValidX;		//水平有效使用点
//	unsigned short ValidY;		//垂直有效使用点
//	
//	unsigned short BackColor;	//背景色
//	unsigned short PenColor;	//画笔色
//	unsigned short FontSize;	//字体大小
//	

//	
//	
//	WinFontDef	WinFont	=	sAmpLcd.Display.WinFont;			//显示配置
//	WinInfoDef	WinInfo	=	sAmpLcd.Display.WinInfo;
//	WinGuiDef		WinGui	=	sAmpLcd.Display.WinGui;
//	
//	BackColor	=	WinFont.FtNum.BackColor;
//	PenColor	=	WinFont.FtNum.PenColor;
//	FontSize	=	WinFont.FtNum.Size;
//	//DisplayNewStartY	=	sAmpLcd.Display.DisplayNextStartY;	
//	//-----------------------------------------------------检查有无数据
////	len=DisplayData.LenNum;	
////	if(0==len)
////	{
////		return;
////	}
//	
//	//-----------------------------------------------------获取显示区域
//	str	=	buffer;	
//	len=DisplayData.ParaNum.len;
//	offset	=	DisplayData.ParaNum.Offset;	
//	memcpy(str,&DisplayData.String[offset],len);
//	
//	str	=	&buffer[len];	
//	len	=	DisplayData.ParaUnit.len;
//	offset	=	DisplayData.ParaUnit.Offset;
//	memcpy(str,&DisplayData.String[offset],len);

//	goto StartDisplay;
//	
//	//==========================================判断起始点在中线上还是下
//	//==========================================开始显示商品名称
//	StartDisplay:
////	ysum	=	WinInfo.RowCoSpec*WinConf.WinSpecFtSize+WinInfo.RowCoCode*WinConf.WinCodeFtSize+WinInfo.RowCoVender*WinConf.WinVenderFtSize;
//	len	=	DisplayData.ParaNum.len+DisplayData.ParaUnit.len;
//	xs	=	WinInfo.PxyLeftFill.XH+(WinInfo.PxyValid.XH-len*FontSize/2);
//	xe	=	xs+FontSize*len/2;
//	
//	//ys	=	WinInfo.StartY-FontSize;
//	ys	=	WinGui.StartXY.YV+4;
//	ye	=	ys+FontSize;
//	//-----------------------------------------------------背景填充
//	ST7789V_Fill(xs,ys,xe,ye,BackColor);
//	//-----------------------------------------------------显示数据
//	ST7789V_ShowStringBKAre(xs,ys,xe,ye,FontSize,BackColor,PenColor,len,buffer);	//带背景色限定区域显示
//	
//	//WinInfo.StartY=ye;
//	
//	sAmpLcd.Display.WinInfo	=	WinInfo;
//	sAmpLcd.Display.WinGui.StartXY.YV	=	WinGui.StartXY.YV;
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
void DisplayTitle(const ListDef Node)
{
	unsigned char i	=	0;
	unsigned char len=0;
	unsigned char num=0;
	unsigned char size=0;
	unsigned char offset=0;
	unsigned char	buffer[256];
	unsigned char* str;

	unsigned short xs=0;
	unsigned short ys=0;
	unsigned short xe=0;
	unsigned short ye=0;
	unsigned short ysum=0;
	unsigned short yebac=0;
	unsigned short ValidX;		//水平有效使用点
	unsigned short ValidY;		//垂直有效使用点
	
	unsigned short BackColor;	//背景色
	unsigned short PenColor;	//画笔色
	unsigned short FontSize;	//字体大小
	
//	//unsigned short DisplayNewStartY;
//	
//	
//	WinFontDef	WinFont	=	sAmpLcd.Display.WinFont;			//显示配置
//	WinInfoDef	WinInfo	=	sAmpLcd.Display.WinInfo;
//	WinGuiDef		WinGui	=	sAmpLcd.Display.WinGui;
//	
//	BackColor	=	WinFont.FtName.BackColor;
//	PenColor	=	WinFont.FtName.PenColor;
//	FontSize	=	WinFont.FtName.Size;
//	
//	//-----------------------------------------------------检查有无数据
//	len=DisplayData.ParaName.len;	
//	if(0==len)
//	{
//		return;
//	}
//	//-----------------------------------------------------获取显示数据
//	len			=	DisplayData.ParaName.len;
//	offset	=	DisplayData.ParaName.Offset;	
//	memcpy(buffer,&DisplayData.String[offset],len);	
//	//-----------------------------------------------------清空显示区域
//	xs	=	WinInfo.PxyLeftFill.XH;	
//	xe	=	WinInfo.PxyRigthFill.XH;
//	
//	ys	=	WinGui.StartXY.YV;	
//	ye	=	ys+FontSize*WinInfo.PxyName.YV;
//	
//	ST7789V_Fill(xs,ys,xe,ye,BackColor);
//	
//	StartDisplay:
//	//-----------------------------------------------------获取显示区域(如果是单行则居中显示)
//	if((len*FontSize/2)<WinInfo.PxyValid.XH)
//	{
//		xs	=	WinInfo.PxyLeftFill.XH+((WinInfo.PxyValid.XH-(len*FontSize/2))/2);
//	}
//	else
//	{
//		xs	=	WinInfo.PxyLeftFill.XH;
//	}		
//	xe	=	WinInfo.PxyRigthFill.XH;
//	
//	ys	=	WinGui.StartXY.YV;	
//	ye	=	ys+FontSize*WinInfo.PxyName.YV;
//	//-----------------------------------------------------显示数据
//	ST7789V_ShowStringBKAre(xs,ys,xe,ye,FontSize,BackColor,PenColor,len,buffer);	//带背景色限定区域显示
//	
//	WinGui.StartXY.YV=ye;
//	
//	sAmpLcd.Display.WinInfo	=	WinInfo;
//	sAmpLcd.Display.WinGui.StartXY.YV	=	WinGui.StartXY.YV;
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
//	if(sAmpLcd.Display.LcdPort.ST7789VBColor	!=	BKColor)
//	{
//		STM32_FLASH_Write(BackColorStartAddr,(unsigned short*)&BKColor,1);						//从指定地址写入指定长度的数据
//		BKColor	=	GetBackColor();
//		sAmpLcd.Display.LcdPort.ST7789VBColor=BKColor;
//	}	
//	ST7789V_Clean(BKColor);	//清除屏幕函数
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
	
	sAmpLcd.Windows.LcdPort	=	sST7789V;
	
	ST7789V_Initialize(&sAmpLcd.Windows.LcdPort);
	
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
	
	sAmpLcd.Windows.SpiPort	=	sGT32L32;	
  
  GT32L32_Initialize(&sAmpLcd.Windows.SpiPort);				//普通SPI通讯方式配置
	
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
/*******************************************************************************
*函数名			:	function
*功能描述		:	function
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
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
		else if(AmpCmdLcdConf ==  ampframe->msg.cmd.cmd)
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
void GetManaData(const unsigned char* Databuffer,unsigned short datalen)
{
	unsigned char		i=0;
	unsigned char 	strtype		=0;		//字符串类型
	unsigned char 	strLen		=0;		//字符串长度
//	unsigned char 	strCount	=0;		//已处理的字符串个数计数
	unsigned char 	FinishedDataLen	=	0;	//已处理数据个数
	unsigned char		Offset			=	0;	//下一个类型字符串的偏移地址
	unsigned char*	ParaOffsetAddr;		//字符串地址偏移指针
	unsigned char*	ParalenAddr;			//字符串长度指针
	
	unsigned char		MaxList		=	0;
//	unsigned char		ListCount	=	0;
	
	unsigned char* 	pSource;		//源字符串地址---源自串口接收到的数据
	unsigned char* 	pTarget;		//目标符串地址---存储
	
	ManaDef*	ManaData;
	ListDef*	List;		//
//	ListDef*	pNode;
	ListDef		Node;
	
	//=================================初始化数据
	List			=	sAmpLcd.Windows.ManaData.List;
	MaxList		=	sAmpLcd.Windows.ManaData.MaxNameList;	//可接收的最大条目限制
	memset(&Node,0x00,sizeof(ListDef));
	//=================================查找空缓存
	for(i=0;i<MaxList;i++)
	{
		if(0==List[i].ListNum)		//缓存为空，可以拷贝数据
		{
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
	ManaData	=	(ManaDef*)Databuffer;
	pSource		=	ManaData->String;			//数据源地址
	pTarget		=	Node.String;				//数据目标地址
	//---------------------------------01名称参数
	strtype		=	ManaData->type;
	strLen		=	ManaData->len;
	if(strLen+2>AMPLcdMaxStringLen)	//字符个数超限(字符串+type和len)
		return;
	
	GetDataStart:
	switch(strtype)	//字符串类型判断
	{
		case	0x01:	//商品名类型
			if(0!=Node.ParaName.len)	//数据异常
			{
				return;
			}
			ParaOffsetAddr	=	&Node.ParaName.Offset;
			ParalenAddr			=	&Node.ParaName.len;
		break;
		case	0x02:	//规格参数
			if(0!=Node.ParaSpec.len)	//数据异常
			{
				return;
			}
			ParaOffsetAddr	=	&Node.ParaSpec.Offset;
			ParalenAddr			=	&Node.ParaSpec.len;		
		break;
		case	0x03:	//数量参数
			if(0!=Node.ParaNum.len)	//数据异常
			{
				return;
			}
			ParaOffsetAddr	=	&Node.ParaNum.Offset;
			ParalenAddr			=	&Node.ParaNum.len;		
		break;
		
		case	0x04:	//别名
			if(0!=Node.ParaByName.len)	//数据异常
			{
				return;
			}
			ParaOffsetAddr	=	&Node.ParaByName.Offset;
			ParalenAddr			=	&Node.ParaByName.len;			
		break;
		case	0x05:	//厂商名称
			if(0!=Node.ParaVender.len)	//数据异常
			{
				return;
			}
			ParaOffsetAddr	=	&Node.ParaVender.Offset;
			ParalenAddr			=	&Node.ParaVender.len;
		break;
		case	0x06:	//商品编码
			if(0!=Node.ParaCode.len)	//数据异常
			{
				return;
			}
			ParaOffsetAddr	=	&Node.ParaCode.Offset;
			ParalenAddr			=	&Node.ParaCode.len;
		break;
		case	0x07:	//数量单位
			if(0!=Node.ParaUnit.len)	//数据异常
			{
				return;
			}
			ParaOffsetAddr	=	&Node.ParaUnit.Offset;
			ParalenAddr			=	&Node.ParaUnit.len;
		break;
		default:return;	//未找到类型数据
	}
	*ParalenAddr		=	strLen;		//字符串长度
	*ParaOffsetAddr	=	Offset;		//当前字符串偏移地址

	//-------------------------------复制数据
	memcpy(pTarget,pSource,strLen);		//复制字符串
	
	//-------------------------------统计已处理字节数
	Offset		=	Offset+strLen;				//下一个类型字符串的偏移地址
	FinishedDataLen+=strLen+2;							//已处理数据个数(字符串+type和len)
	//-------------------------------指向下一类型
	if(FinishedDataLen>=datalen)	//已处理完
	{
		//-------------------------------正确获取到数据
		if(0!=Node.ParaName.len||0!=Node.ParaByName.len)	//商品名称或者别名是必需数据
		{
			SetManaData(&Node);														//设置显示参数---数据获取成功后设置相关的显示参数
//			sAmpLcd.Windows.ManaData.ReceivedManaCount+=1;
//			pNode->ListNum	=	i+1;
		}
		return;
	}
	//-------------------------------指向下一类型	
	ManaData	=	(ManaDef*)&pSource[strLen];
	pSource		=	ManaData->String;		//新源字符串地址
	pTarget		=	&pTarget[strLen];		//新目标字符串地址
	strtype		=	ManaData->type;
	strLen		=	ManaData->len;
	//-------------------------------剩下字符重新做类型检查
	if(FinishedDataLen+strLen>AMPLcdMaxStringLen)	//字符个数超限
		return;
	goto GetDataStart;
	
}
/*******************************************************************************
*函数名			:	function
*功能描述		:	设置显示参数---数据获取成功后设置相关的显示参数
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
void SetManaData(ListDef* pNode)
{
	unsigned char		i=0;
	unsigned char 	strtype		=	0;		//字符串类型
	unsigned char 	strLen		=	0;		//字符串长度
	unsigned char		FontSize	=	0;		//字体大小16,24,32
	unsigned char		Line			=	0;		//可显示行数
//	unsigned char 	strCount	=0;		//已处理的字符串个数计数
	unsigned char 	FinishedDataLen	=	0;	//已处理数据个数
//	unsigned char		Offset			=	0;	//下一个类型字符串的偏移地址
//	unsigned char*	ParaOffsetAddr;		//字符串地址偏移指针
//	unsigned char*	ParalenAddr;			//字符串长度指针
	
	unsigned char		MaxList		=	0;
//	unsigned char		ListCount	=	0;
	
	unsigned char* 	pSource;		//源字符串地址---源自串口接收到的数据
	unsigned char* 	pTarget;		//目标符串地址---存储
	
	unsigned short	XH;						//X--水平占用点数
	unsigned short	YV;						//Y--垂直占用点数
	unsigned short	OffsetXH;			//X--数量和单位点用的水平点数
	
	unsigned short*	pTargetXH;		//X--数据水平有效点数地址
	unsigned short*	pTargetYV;		//Y--数据垂直有效点数地址
	
	unsigned short	ValidXH;			//X--水平有效点数
	unsigned short	ValidYV;			//Y--垂直有效点数
	
	ParaDef*		Para;
	ListDef*		List;
	ListDef			Node;
	WinInfoDef	WinInfo;			//显示字体信息
	//---------------------------------输入数据地址有效性
	if(NULL==pNode)
	{
		return;
	}
	//---------------------------------检查数据有效性
	if((0==pNode->ParaName.len)&&(0==pNode->ParaByName.len))	//商品名称或者别名是必需数据
	{
		return;
	}
	//=================================初始化数据
	List		=	sAmpLcd.Windows.ManaData.List;
	MaxList	=	sAmpLcd.Windows.ManaData.MaxNameList;	//可接收的最大条目限制
	WinInfo	=	sAmpLcd.Windows.WinInfo;							//字体信息
	ValidXH	=	sAmpLcd.Windows.WinInfo.PxyValid.XH;
	ValidYV	=	sAmpLcd.Windows.WinInfo.PxyValid.YV;
	
	Node	=	*pNode;
	//=================================先计算数量和单位占用X点数(除名称外，右缩进需要根据数量和单位占用的X点数来调整)
	//---------------------------------获取数量和单位数据
	FontSize	=	WinInfo.FtNum.Size;
	strLen		=	Node.ParaNum.len+Node.ParaUnit.len;		//数量和单位的字节点
	//---------------------------------计算数量占用水平点数
	Node.ParaNum.XH	=	Node.ParaNum.len*(FontSize/2);	//字符宽度为高度的一半
	Node.ParaNum.YV	=	Node.ParaNum.len*(FontSize);		//字符宽度为高度的一半
	//---------------------------------计算单位占用水平点数
	Node.ParaUnit.XH	=	Node.ParaUnit.len*(FontSize/2);	//字符宽度为高度的一半
	Node.ParaUnit.YV	=	Node.ParaUnit.len*(FontSize);		//字符宽度为高度的一半
	//----------------------------------数量和单位共占用的水平点数
	OffsetXH	=	Node.ParaNum.XH+Node.ParaUnit.XH;	
	
	//=================================分类拆装数据
	//---------------------------------初始化指针地址和数据
	Para	=	(ParaDef*)&Node.ParaName;

	//---------------------------------01名称参数
	strtype		=	0x01;		//从第一个参数开始


	SetDataStart:
	switch(strtype)
	{
		case	0x01:	//商品名类型
			Line	=	4;		//名称最大可显示4行
			strLen		=	Node.ParaName.len;			
			FontSize	=	WinInfo.FtName.Size;		
			Node.ParaName.XH	=	sAmpLcd.Windows.WinInfo.PxyValid.XH;
			
			pTargetXH	=	&Node.ParaName.XH;
			pTargetYV	=	&Node.ParaName.YV;
		break;
		case	0x02:	//规格参数
			Line	=	2;		//名称最大可显示2行
			strLen		=	Node.ParaSpec.len;			
			FontSize	=	WinInfo.FtSpec.Size;		
			Node.ParaSpec.XH	=	sAmpLcd.Windows.WinInfo.PxyValid.XH-OffsetXH;
		
			pTargetXH	=	&Node.ParaSpec.XH;
			pTargetYV	=	&Node.ParaSpec.YV;
		break;
		case	0x03:	//数量参数
			strtype+=1;
			goto SetDataStart;	
		break;
		
		case	0x04:	//别名
			Line	=	2;		//名称最大可显示2行
			strLen		=	Node.ParaByName.len;			
			FontSize	=	WinInfo.FtByName.Size;		
			Node.ParaByName.XH	=	sAmpLcd.Windows.WinInfo.PxyValid.XH-OffsetXH;
		
			pTargetXH	=	&Node.ParaByName.XH;
			pTargetYV	=	&Node.ParaByName.YV;			
		break;
		case	0x05:	//厂商名称
			Line	=	2;		//名称最大可显示2行
			strLen		=	Node.ParaVender.len;			
			FontSize	=	WinInfo.FtVender.Size;		
			Node.ParaVender.XH	=	sAmpLcd.Windows.WinInfo.PxyValid.XH-OffsetXH;
		
			pTargetXH	=	&Node.ParaVender.XH;
			pTargetYV	=	&Node.ParaVender.YV;
		break;
		case	0x06:	//商品编码
			Line	=	2;		//名称最大可显示2行
			strLen		=	Node.ParaCode.len;			
			FontSize	=	WinInfo.FtCode.Size;		
			Node.ParaCode.XH	=	sAmpLcd.Windows.WinInfo.PxyValid.XH-OffsetXH;
		
			pTargetXH	=	&Node.ParaCode.XH;
			pTargetYV	=	&Node.ParaCode.YV;
		break;
		case	0x07:	//数量单位
			strtype+=1;
			goto SetDataStart;
		break;
		default:goto AddNode;	//未找到类型数据
	}
	if(0==FontSize)
		return;
	//---------------------------------计算一行可以显示多少个对应的数据
	i=*pTargetXH/(FontSize/2);	//字符宽度为高度的一半
	//---------------------------------计算需要多少行才能显示完
	if(0==i)
		return;
	if(0==strLen%i)	//整数行
	{
		i	=	strLen/i;
	}
	else
	{
		i	=	strLen/i+1;
	}
	//---------------------------------检查行数有无超限,超出部分不计入显示(不显示)
	if(i>Line)
	{
		i=Line;
	}
	//---------------------------------计算Y轴需要多少点数
	*pTargetYV	=	i*FontSize;
	//---------------------------------继续检查其它项
	strtype+=1;
	if(strtype<8)
	{
		goto SetDataStart;
	}
	//---------------------------------添加数据：添加数据前比较缓存有无相同的数据，有则不添加
	AddNode:
	for(i=0;i<MaxList;i++)
	{
		if(0==memcmp((unsigned char*)&List[i].ParaName,&Node.ParaName,sizeof(ListDef)-2))	//检查数据内容(减2是因为List[i].ListNum，16字节对齐)
		{
			if(0!=List[i].ListNum)	//序号存在
				return;
		}
	}
//---------------------------------无相同数据，往空缓存内添加数据	
	for(i=0;i<MaxList;i++)
	{
		if(0==List[i].ListNum)		//缓存为空，可以拷贝数据
		{
			//List	=	List[i];
			memcpy((unsigned char*)&List[i],&Node,sizeof(ListDef));
			sAmpLcd.Windows.ManaData.ReceivedManaCount+=1;
			List[i].ListNum	=	i+1;
			break;
		}
	}	
}
/*******************************************************************************
*函数名			:	DataInitialize
*功能描述		:	数据初始化
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
void DataInitialize(void)
{
	unsigned	char*	addr;
	//==========================================显示参数初始化
	WinInfoDef* WinInfo	=	(WinInfoDef*)&sAmpLcd.Windows.WinInfo;
	//==========================================WinFont
	WinInfo->FtDefault.BackColor	=	DisplayBackColor;
	WinInfo->FtDefault.PenColor		=	DisplayFontColor;
	WinInfo->FtDefault.Size				=	DisplayFontSize;
	
	WinInfo->FtName.BackColor			=	DisplayNameBkColor;
	WinInfo->FtName.PenColor			=	DisplayNameFtColor;
	WinInfo->FtName.Size					=	DisplayNameFtSize;
	
	WinInfo->FtByName.BackColor		=	DisplayByNameBkColor;
	WinInfo->FtByName.PenColor		=	DisplayByNameFtColor;
	WinInfo->FtByName.Size				=	DisplayByNameFtSize;
	
	WinInfo->FtSpec.BackColor			=	DisplaySpecBkColor;
	WinInfo->FtSpec.PenColor			=	DisplaySpecFtColor;
	WinInfo->FtSpec.Size					=	DisplaySpecFtSize;
	
	WinInfo->FtNum.BackColor			=	DisplayNumBkColor;
	WinInfo->FtNum.PenColor				=	DisplayNumFtColor;
	WinInfo->FtNum.Size						=	DisplayNumFtSize;
	
	WinInfo->FtSeril.BackColor		=	DisplaySerialBkColor;
	WinInfo->FtSeril.PenColor			=	DisplaySerialFtColor;
	WinInfo->FtSeril.Size					=	DisplaySerialFtSize;
	
	WinInfo->FtCode.BackColor			=	DisplayCodeBkColor;
	WinInfo->FtCode.PenColor			=	DisplayCodeFtColor;
	WinInfo->FtCode.Size					=	DisplayCodeFtSize;
	
	WinInfo->FtVender.BackColor		=	DisplayVenderBkColor;
	WinInfo->FtVender.PenColor		=	DisplayVenderFtColor;
	WinInfo->FtVender.Size				=	DisplayVenderFtSize;
	
	WinInfo->FtTitle.BackColor		=	DisplayTitleBkColor;
	WinInfo->FtTitle.PenColor			=	DisplayTitleFtColor;
	WinInfo->FtTitle.Size					=	DisplayTitleSize;
	
	WinInfo->FtSepar.BackColor		=	DisplaySeparBkColor;
	WinInfo->FtSepar.Size					=	DisplaySeparWidth;
	
	//==========================================WinInfo
	//------------------------------------------整屏像素点
	WinInfo->PxyPixel.XH					=	ST7789V_V;		//水平点个数
	WinInfo->PxyPixel.YV					=	ST7789V_H;		//垂直点个数
	
	//------------------------------------------顶端垂直起始/填充点
	WinInfo->PxyTopFill.XH				=	0;
	WinInfo->PxyTopFill.YV				=	DisplayTopFillWidth;	
	//------------------------------------------底部垂直起始/填充点
	WinInfo->PxyBotFill.XH				=	0;
	WinInfo->PxyBotFill.YV				=	DisplayBotFillWidth;
	//------------------------------------------左边起始/填充点
	WinInfo->PxyLeftFill.XH				=	DisplayLeftFillWidth;
	WinInfo->PxyLeftFill.YV				=	0;
	//------------------------------------------剩余有效使用点数
	WinInfo->PxyValid.XH					=	WinInfo->PxyPixel.XH-WinInfo->PxyLeftFill.XH-1;
	WinInfo->PxyValid.YV					=	WinInfo->PxyPixel.YV-(WinInfo->PxyBotFill.YV+WinInfo->PxyTopFill.YV)-1;
	
	//------------------------------------------最大可以接收商品个数
	addr=(unsigned char*)&sAmpLcd.Windows.ManaData.MaxNameList;		//const类型
	*addr	=	DspMaxNameTypeCount;
	//------------------------------------------Y起始点
	sAmpLcd.Windows.ManaData.StartPixelY	=	WinInfo->PxyTopFill.YV+WinInfo->FtTitle.Size+WinInfo->FtSepar.Size;
}
#endif
