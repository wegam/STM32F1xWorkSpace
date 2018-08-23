/**************************************************************************************************
* 液晶屏驱动IC
* 文件<$(filename)>
* 模块描述 :	定义、功能、说明
* 历史修改记录
*     <主要修改者>  <时间>   <版本 >   <说明>
*     xlyan        $(Date)   1.0.0    创建文件
**************************************************************************************************/
#include "R61509V.h"


LCDDef	*pR61509V	=	NULL;		//内部驱动使用，不可删除

/*******************************************************************************
* 函数名			:	function
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
*******************************************************************************/
void R61509V_Initialize(LCDDef *pInfo)
{
	pR61509V		=	pInfo;		//指针指向
	
	
	pR61509V->Data.MaxH	=	R61509V_H;					//最大水平宽度
	pR61509V->Data.MaxV	=	R61509V_V;					//最大垂直高度	
//	pR61509V->Data.BColor	=	LCD565_GBLUE;			//背景色
//	pR61509V->Data.PColor	=	LCD565_RED;				//画笔色
	
	
	pR61509V->Display.WriteAddress		=	R61509V_SetWindowAddress;
	pR61509V->Display.PowerOn					=	R61509V_PowerOn;
	pR61509V->Display.DispOff					=	R61509V_PowerOff;
	
	LCD_Initialize(pR61509V);
//	pR61509V	=	NULL;	
}
/*******************************************************************************
*函数名			:	R61509V_SetWindowAddress
*功能描述		:	设置窗口地址
*输入				: 
*返回值			:	无
*******************************************************************************/
static void R61509V_SetWindowAddress(			//设置窗口地址
															unsigned short x1,		//水平起始点
															unsigned short y1,		//水平终止点
															unsigned short x2,		//垂直起始点
															unsigned short y2			//垂直终止点
															)
{	
	unsigned short MaxH,MaxV;
	unsigned short Model	=	0x5030;

	eRotate	Rotate	=	pR61509V->Flag.Rotate;
	
	MaxH	=	pR61509V->Data.MaxH;
	MaxV	=	pR61509V->Data.MaxV;
	
	switch(Rotate)
	{
		case 	Draw_Rotate_0D:
					pR61509V->Data.HSX	=	x1;
					pR61509V->Data.HEX	=	x2;
					pR61509V->Data.VSY	=	y1;
					pR61509V->Data.VEY	=	y2;	
					pR61509V->Data.HXA	=	pR61509V->Data.HSX;
					pR61509V->Data.VYA	=	pR61509V->Data.VSY;	
					Model	=	0x5030;
			break;
		case 	Draw_Rotate_90D:
					pR61509V->Data.HSX	=	y1;
					pR61509V->Data.HEX	=	y2;	
					pR61509V->Data.VSY	=	MaxV	-	x2	-	1;
					pR61509V->Data.VEY	=	MaxV	-	x1	-	1;	
					pR61509V->Data.HXA	=	pR61509V->Data.HSX;
					pR61509V->Data.VYA	=	pR61509V->Data.VEY;
					Model	=	0X5018;								//GRAM(Graphics RAM--图形内存) Data Write (R202h)准备写入
			break;
		case 	Draw_Rotate_180D:
					pR61509V->Data.HSX	=	MaxH	-	x2	-	1;
					pR61509V->Data.HEX	=	MaxH	-	x1	-	1;
					pR61509V->Data.VSY	=	MaxV	-	y2	-	1;
					pR61509V->Data.VEY	=	MaxV	-	y1	-	1;	
					pR61509V->Data.HXA	=	pR61509V->Data.HEX;
					pR61509V->Data.VYA	=	pR61509V->Data.VEY;	
					Model	=	0X5000;
			break;
		default:
					pR61509V->Data.HSX	=	MaxH	-	y2	-	1;
					pR61509V->Data.HEX	=	MaxH	-	y1	-	1;
					pR61509V->Data.VSY	=	x1;
					pR61509V->Data.VEY	=	x2;	
					pR61509V->Data.HXA	=	pR61509V->Data.HEX;
					pR61509V->Data.VYA	=	pR61509V->Data.VSY;
					Model	=	0X5028;
			break;
	}
	LCD_WriteCommand(R61509V_R210_HSA,pR61509V->Data.HSX);		//Window Horizontal RAM Address Start(R210h)		//水平
	LCD_WriteCommand(R61509V_R211_HEA,pR61509V->Data.HEX);		//Window Horizontal RAM Address End(R211h)			//水平
	LCD_WriteCommand(R61509V_R212_VSA,pR61509V->Data.VSY);		//Window Vertical RAM Address Start (R212h)			//垂直
	LCD_WriteCommand(R61509V_R213_VEA,pR61509V->Data.VEY);		//Window Vertical RAM Address End (R213h)				//垂直
	
	LCD_WriteCommand(R61509V_R200_HA,pR61509V->Data.HXA);			//RAM Address Set (Horizontal Address) (R200h)
	LCD_WriteCommand(R61509V_R201_VA,pR61509V->Data.VYA);			//RAM Address Set (Vertical Address) (R201h)

	LCD_WriteCommand(R61509V_R003_EM,Model);						//RAM Address Set (Vertical Address) (R201h)
//	R61509V_WriteIndex16(R61509V_R202_GDRW);								//GRAM(Graphics RAM--图形内存) Data Write (R202h)准备写入
	LCD_WriteIndexStart();	
	LCD_WriteData(R61509V_R202_GDRW);
	LCD_WriteIndexEnd();
}


/*******************************************************************************
*函数名			:	R61509V_Initialize
*功能描述		:	IC初始化：按照主控芯片R61509V的power supply on sequence 进行配置
*输入				: 
*返回值			:	无
*******************************************************************************/
static void R61509V_PowerOn(void)			//按照主控芯片R61509V的power supply on sequence 进行配置
{
	u32 dtime=2000;
	
	void(*Command)(unsigned short Index,unsigned short Command);//LcdDisplay.WriteCommand	
	Command	=	LCD_WriteCommand;
	
	LCD_CS_LOW;
	LCD_WR_HIGH;
	LCD_RD_HIGH;
	LCD_RST_HIGH;
	LCD_Delay(dtime);
	LCD_RST_LOW;
	LCD_Delay(dtime);
	LCD_RST_HIGH;	
	LCD_Delay(dtime);		//复位后1ms内部晶振启动
	LCD_Delay(dtime);		//复位后1ms内部晶振启动
	LCD_Delay(dtime);		//复位后1ms内部晶振启动
	dtime=500;
	
	Command(R61509V_R000_IR		,	0x0000);		LCD_Delay(dtime); //四次写0x00
	Command(R61509V_R000_IR		,	0x0000);		LCD_Delay(dtime); //四次写0x00
	Command(R61509V_R000_IR		,	0x0000);		LCD_Delay(dtime); //四次写0x00
	Command(R61509V_R000_IR		,	0x0000);		LCD_Delay(dtime); //四次写0x00
	
	Command(R61509V_R001_DOC	,	0x0300);		LCD_Delay(dtime); //--------显示方向控制When SS = “1” and BGR = “1”, RGB dots are assigned one to one from S720 to S1.
	Command(R61509V_R002_DWC	,	0x0100);		LCD_Delay(dtime); //--------	
	Command(R61509V_R003_EM		,	0X5030);		LCD_Delay(dtime); //--------RGB设为5-6-5模式------------0X5030
	Command(R61509V_R007_DC1	,	0x0100);		LCD_Delay(dtime); //--------测试显示控制base image的关与开
	Command(R61509V_R008_DC2	,	0X0808);		LCD_Delay(dtime); //--------
	Command(R61509V_R009_DC3	,	0x0001);		LCD_Delay(dtime); //--------	
	
	Command(R61509V_R00B_ECC		,	0x0001);		LCD_Delay(dtime); //--------
	Command(R61509V_R00C_EDIC1	,	0x0000);		LCD_Delay(dtime); //--------
	Command(R61509V_R00F_EDIC2	,	0x0000);		LCD_Delay(dtime); //--------
	
	Command(R61509V_R010_PIC1	,	0x0019);		LCD_Delay(dtime); //--------面板频率--0x19
	Command(R61509V_R011_PIC2	,	0x0101);		LCD_Delay(dtime); //--------		Panel Interface Control 2 (R011h)
	Command(R61509V_R012_PIC3	,	0x0000);		LCD_Delay(dtime); //--------
	Command(R61509V_R013_PIC4	,	0x0001);		LCD_Delay(dtime); //--------
	Command(R61509V_R014_PIC5	,	0x0055);		LCD_Delay(dtime); //--------
	Command(R61509V_R020_PIC6	,	0x0010);		LCD_Delay(dtime); //--------
	Command(R61509V_R021_PIC7	,	0x0101);		LCD_Delay(dtime); //--------
	Command(R61509V_R022_PIC8	,	0x0000);		LCD_Delay(dtime); //--------
	Command(R61509V_R023_PIC9	,	0x0001);		LCD_Delay(dtime); //--------	
	
	Command(R61509V_R090_FMC		,	0x8000);		LCD_Delay(dtime); //--------窗特征控制，FMARK interface
	
	Command(R61509V_R100_PC1		,	0x0330);		LCD_Delay(dtime); //--------设置电源控制，平衡显示与电消耗
	Command(R61509V_R101_PC2		,	0x0227);		LCD_Delay(dtime); //--------Power Control 2
	Command(R61509V_R102_PC3		,	0xC1B0);		LCD_Delay(dtime); //--------PSON,PON 都设为1，电源供应打开
	Command(R61509V_R103_PC4		,	0x0D00);		LCD_Delay(dtime); //--------	
	
	Command(R61509V_R200_HA			,	0x0000);		LCD_Delay(dtime);	//--------RAM address 设置
	Command(R61509V_R201_VA			,	0x0000);		LCD_Delay(dtime);	//--------
	
	Command(R61509V_R280_NVM		,	0xB000);		LCD_Delay(dtime);	//--------VCM
	
	Command(R61509V_R300_YC1		,	0x0C00);		LCD_Delay(dtime); //--------
	Command(R61509V_R301_YC2		,	0x5A0B);		LCD_Delay(dtime); //--------
	Command(R61509V_R302_YC3		,	0x0906);		LCD_Delay(dtime); //--------
	Command(R61509V_R303_YC4		,	0x1017);		LCD_Delay(dtime); //--------
	Command(R61509V_R304_YC5		,	0x2300);		LCD_Delay(dtime); //--------
	Command(R61509V_R305_YC6		,	0x1700);		LCD_Delay(dtime); //--------
	Command(R61509V_R306_YC7		,	0x6309);		LCD_Delay(dtime); //--------
	Command(R61509V_R307_YC8		,	0x0C09);		LCD_Delay(dtime); //--------
	Command(R61509V_R308_YC9		,	0x100C);		LCD_Delay(dtime); //--------
	Command(R61509V_R309_YC10		,	0x2232);		LCD_Delay(dtime); //--------
	
	Command(R61509V_R400_BINL		,	0X6400);		LCD_Delay(dtime); //base image 设置 400线
	Command(R61509V_R401_BIDC		,	0x0004);		LCD_Delay(dtime); //--------设置base image 滚动模式，开启滚动(颜色反相设置）
	Command(R61509V_R404_BIVSC	,	0x0000);		LCD_Delay(dtime);	//--------从0线开始滚屏
	
	Command(R61509V_R502_PTEA		,	0x005f);		LCD_Delay(dtime);
	LCD_BL_ON;		//开背光
}

/**************************************************************************************************
* [Function] R61509V_PowerOff:  关闭R61509V 电源
* [No param]
**************************************************************************************************/
static void R61509V_PowerOff( void )
{
	LCD_WriteCommand( R61509V_R009_DC3, 0 );
	LCD_BL_OFF;
}
/**************************************************************************************************
* [Function] R61509V_DispOff:  关闭R61509V显示( 黑屏?)
* [No param]
**************************************************************************************************/
static void R61509V_DispOff( void )
{
	LCD_WriteCommand( R61509V_R007_DC1, 0x0000 );
}





//#endif//R61509V_61509_EN
/************************************** The End Of FILE **************************************/


