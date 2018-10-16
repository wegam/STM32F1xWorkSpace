/**************************************************************************************************
* Copyright (C), 1997-$(Year),  HAICHUANG IOT Tech. Co., Ltd.
* 文件<$(filename)>
* 模块描述 :	定义、功能、说明
* 历史修改记录
*     <主要修改者>  <时间>   <版本 >   <说明>
*     xlyan        $(Date)   1.0.0    创建文件
**************************************************************************************************/
#include "ILI9326.h"


LCDDef *sILI9326=0;					//内部驱动使用，不可删除

//#ifdef LCD_61509_EN

t_LcdCfg g_ILI9326Cfg;

u16 ILI9326_Rotate=SCREEN_ROTATE_270D;			//屏方向



u16 ILI9326_BACK_COLOR	=	ILI9326_WHITE;		//背景色
u16 ILI9326_POINT_COLOR	=	ILI9326_BLACK;   	//画笔色

///*******************************************************************************
//* 函数名			:	function
//* 功能描述		:	函数功能说明 
//* 输入			: void
//* 返回值			: void
//*******************************************************************************/
//void ILI9326_Delay(u32 xms)
//{
//	while(xms--);
//}
/*******************************************************************************
* 函数名			:	function
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
*******************************************************************************/
void ILI9326_Initialize(LCDDef *pInfo)
{
	sILI9326		=	pInfo;		//指针指向
	
	
	sILI9326->Data.MaxH	=	ILI9326_H;					//最大水平宽度
	sILI9326->Data.MaxV	=	ILI9326_V;					//最大垂直高度	
//	pR61509V->Data.BColor	=	LCD565_GBLUE;			//背景色
//	pR61509V->Data.PColor	=	LCD565_RED;				//画笔色
	
	
	sILI9326->Display.WriteAddress		=	ILI9326_SetWindowAddress;
	sILI9326->Display.PowerOn					=	ILI9326_PowerOn;
	sILI9326->Display.DispOff					=	ILI9326_PowerOff;
	
	LCD_Initialize(sILI9326);

}
/*******************************************************************************
*函数名		:	SSD1963_BackLightOn
*功能描述	:	开背光
*输入			: 
*输出			:	无
*返回值		:	无
*例程			:
*******************************************************************************/
//void ILI9326_BackLightOn(void)
//{
//	LCD_BL_ON;
////	if(0	!=	sILI9326)
////	 sILI9326->Port.sBL_PORT->BSRR  = sILI9326->Port.sBL_Pin;
//}
/*******************************************************************************
*函数名		:	SSD1963_BackLightOff
*功能描述	:	关背光
*输入			: 
*输出			:	无
*返回值		:	无
*例程			:
*******************************************************************************/
//void ILI9326_BackLightOff(void)
//{
//	if(0	!=	sILI9326)
//		sILI9326->Port.sBL_PORT->BRR  = sILI9326->Port.sBL_Pin;
//}
/**************************************************************************************************
* [Function] LCD_PowerOff:  关闭LCD 电源
* [No param]
**************************************************************************************************/
void ILI9326_PowerOff( void )
{
	LCD_BL_OFF;		//关背光
	LCD_WriteCommand( ILI9326_R009_DC3, 0 );
	
}


/**************************************************************************************************
* [Function] LCD_DispOff:  关闭LCD显示( 黑屏?)
* [No param]
**************************************************************************************************/
void ILI9326_DispOff( void )
{
	LCD_WriteCommand( ILI9326_R007_DC1, 0x0000 );
}
/**************************************************************************************************
* [Function] LCD_PowerOn: LCD 上电并初始化相关寄存器
* [No param]
**************************************************************************************************/
void ILI9326_PowerOn( void )
{
	u32 dtime=5000;
	
	void(*ILI9326_WriteCMD)(unsigned short Index,unsigned short Command);//LcdDisplay.WriteCommand	
	ILI9326_WriteCMD	=	LCD_WriteCommand;
	
	LCD_BL_OFF;		//关背光
	LCD_Delay( dtime );
	LCD_Delay( dtime );
	LCD_Delay( dtime );
	LCD_Delay( dtime );
//	LCD_CS_LOW;
	LCD_RST_HIGH;
	LCD_Delay( dtime );
	LCD_RST_LOW;
	LCD_Delay( dtime );
	LCD_RST_HIGH;
	LCD_Delay( dtime );
	LCD_Delay( dtime );
	LCD_Delay( dtime );
	LCD_Delay( dtime );

/************** Start Initial Sequence ********** // */
	ILI9326_WriteCMD( ILI9326_R702_SIT1, 	0x3008 );LCD_Delay( dtime ); /* Set internal timing, don’t change this value */
	ILI9326_WriteCMD( ILI9326_R705_SIT2, 	0x0036 );LCD_Delay( dtime ); /* Set internal timing, don’t change this value */
	ILI9326_WriteCMD( ILI9326_R70B_SIT3, 	0x1213 );LCD_Delay( dtime ); /* Set internal timing, don’t change this value */

	ILI9326_WriteCMD( ILI9326_R001_DOC, 	0x0100 );LCD_Delay( dtime ); /* set SS and SM bit */
	ILI9326_WriteCMD( ILI9326_R002_DWC, 	0x0100 );LCD_Delay( dtime ); /* set 1 line inversion */
	ILI9326_WriteCMD( ILI9326_R003_EM, 		0x1030 );LCD_Delay( dtime ); /* set GRAM write direction and BGR=1. */
	ILI9326_WriteCMD( ILI9326_R008_DC2, 	0x0202 );LCD_Delay( dtime );	 /* set the back porch and front porch */
	ILI9326_WriteCMD( ILI9326_R009_DC3, 	0x0000 );LCD_Delay( dtime ); /* set non-display area refresh cycle ISC[3:0] */
	ILI9326_WriteCMD( ILI9326_R00C_EDIC1,	0x0000 );LCD_Delay( dtime ); /* RGB interface setting */
	ILI9326_WriteCMD( ILI9326_R00F_EDIC2,	0x0000 );LCD_Delay( dtime ); /* RGB interface polarity */

	/**************Power On sequence **************** // */
	ILI9326_WriteCMD( ILI9326_R100_PC1, 	0x0000 );LCD_Delay( dtime ); /* SAP, BT[3:0], AP, DSTB, SLP, STB */
	ILI9326_WriteCMD( ILI9326_R102_PC3, 	0x0000 );LCD_Delay( dtime ); /* VREG1OUT voltage */
	ILI9326_WriteCMD( ILI9326_R103_PC4, 	0x0000 );LCD_Delay( dtime ); /* VDV[4:0] for VCOM amplitude */
	LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );                /* Dis-charge capacitor power voltage */
	LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );
	LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );
	LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );
	LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );
	LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );
	LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );
	LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );
	
	ILI9326_WriteCMD( ILI9326_R100_PC1, 	0x1190 ); /* SAP, BT[3:0], AP, DSTB, SLP, STB */
	ILI9326_WriteCMD( ILI9326_R101_PC2, 	0x0227 ); /* DC1[2:0], DC0[2:0], VC[2:0] */
	
	LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );                /* Dis-charge capacitor power voltage */
	LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );
	LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );
	LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );
	LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );
	LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );
	LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );
	LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );
	
	ILI9326_WriteCMD( ILI9326_R102_PC3, 	0x01BD ); /* VREG1OUT voltage */
	
	LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );                /* Dis-charge capacitor power voltage */
	LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );
	LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );
	LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );
	LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );
	LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );
	LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );
	LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );
	
	ILI9326_WriteCMD( ILI9326_R103_PC4,		0x2D00 );LCD_Delay( dtime ); /* VDV[4:0] for VCOM amplitude */
	ILI9326_WriteCMD( ILI9326_R281_VHV, 	0x000E );LCD_Delay( dtime ); /* VCM[5:0] for VCOMH */
	
	LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );                /* Dis-charge capacitor power voltage */
	LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );
	LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );
	LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );
	LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );
	LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );
	LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );
	LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );LCD_Delay( dtime );
	
	ILI9326_WriteCMD( ILI9326_R200_HA, 		0x0000 );LCD_Delay( dtime ); /* GRAM horizontal Address */
	ILI9326_WriteCMD( ILI9326_R201_VA, 		0x0000 );LCD_Delay( dtime ); /* GRAM Vertical Address */

	/* ----------- Adjust the Gamma    Curve ----------// */
	ILI9326_WriteCMD( ILI9326_R300_YC1,		0x0000 );LCD_Delay( dtime );
	ILI9326_WriteCMD( ILI9326_R301_YC2, 	0x0707 );LCD_Delay( dtime );
	ILI9326_WriteCMD( ILI9326_R302_YC3, 	0x0606 );LCD_Delay( dtime );
	ILI9326_WriteCMD( ILI9326_R303_YC4, 	0x0000 );LCD_Delay( dtime );
	ILI9326_WriteCMD( ILI9326_R304_YC5, 	0x0D00 );LCD_Delay( dtime );
	ILI9326_WriteCMD( ILI9326_R305_YC6, 	0x0706 );LCD_Delay( dtime );
	ILI9326_WriteCMD( ILI9326_R306_YC7, 	0x0005 );LCD_Delay( dtime );
	ILI9326_WriteCMD( ILI9326_R307_YC8, 	0x0007 );LCD_Delay( dtime );

	ILI9326_WriteCMD( ILI9326_R308_YC9, 	0x0000 );LCD_Delay( dtime );
	ILI9326_WriteCMD( ILI9326_R309_YC10, 	0x000A );LCD_Delay( dtime );

	/*------------------ Set GRAM area ---------------// */
	ILI9326_WriteCMD( ILI9326_R210_HSA, 	0x0000 );LCD_Delay( dtime ); /* Horizontal GRAM Start Address */
	ILI9326_WriteCMD( ILI9326_R211_HEA, 	0x00EF );LCD_Delay( dtime ); /* Horizontal GRAM End Address */
	ILI9326_WriteCMD( ILI9326_R212_VSA, 	0x0000 );LCD_Delay( dtime ); /* Vertical GRAM Start Address */
	ILI9326_WriteCMD( ILI9326_R400_BINL, 	0x3100 );LCD_Delay( dtime ); /*    / * Gate Scan Line 400 lines * / */
	ILI9326_WriteCMD( ILI9326_R401_BIDC, 	0x0001 );LCD_Delay( dtime ); /* NDL,VLE, REV */
	ILI9326_WriteCMD( ILI9326_R404_BIVSC, 0x0000 );LCD_Delay( dtime ); /* set scrolling line */


/*-------------- Partial Display Control ---------// */
	ILI9326_WriteCMD( ILI9326_R500_PTDP, 0x0000 );LCD_Delay( dtime ); /*Partial Image 1 Display Position */
	ILI9326_WriteCMD( ILI9326_R501_PTSA, 0x0000 );LCD_Delay( dtime ); /*Partial Image 1 RAM Start/End Address */
	ILI9326_WriteCMD( ILI9326_R502_PTEA, 0x0000 );LCD_Delay( dtime ); /*Partial Image 1 RAM Start/End Address */
	ILI9326_WriteCMD( ILI9326_R503_PIDP, 0x0000 );LCD_Delay( dtime ); /*Partial Image 2 Display Position */
	ILI9326_WriteCMD( ILI9326_R504_PIRS, 0x0000 );LCD_Delay( dtime ); /*Partial Image 2 RAM Start/End Address */
	ILI9326_WriteCMD( ILI9326_R505_PIRE, 0x0000 );LCD_Delay( dtime ); /*Partial Image 2 RAM Start/End Address */



/*-------------- Panel Control -------------------// */
	ILI9326_WriteCMD( ILI9326_R010_PIC1, 0x0010 );LCD_Delay( dtime ); /*DIVI[1:0];RTNI[4:0] */
	ILI9326_WriteCMD( ILI9326_R011_PIC2, 0x0600 );LCD_Delay( dtime ); /*NOWI[2:0];SDTI[2:0] */
	ILI9326_WriteCMD( ILI9326_R013_PIC4, 0x0002 );LCD_Delay( dtime ); /*DIVE[1:0];RTNE[5:0] */

	ILI9326_WriteCMD( ILI9326_R007_DC1, 0x0173 );LCD_Delay( dtime ); /* 262K color and display ON */
	
	LCD_BL_ON;			//打开背光
}
/**************************************************************************************************
* [Function] LCD_SetDrawWindow:  LCD 屏显示扫描方式
* [param01]t_ILI9326_Rotate ScrnRotat: 相对于逐行从左到右 翻转角度值
* [param02]t_PixCfg PixCfg: 显示像素配置
* [param03]t_Point top_p: 顶点坐标
* [param04]u16 bottom_p: 底部坐标
**************************************************************************************************/
void ILI9326_SetWindowAddress( 
															unsigned short x1,		//水平起始点
															unsigned short y1,		//水平终止点
															unsigned short x2,		//垂直起始点
															unsigned short y2			//垂直终止点
															)
{
	unsigned short MaxH,MaxV;
	unsigned short Model	=	0x5030;

	eRotate	Rotate	=	sILI9326->Flag.Rotate;
	
	MaxH	=	sILI9326->Data.MaxH;
	MaxV	=	sILI9326->Data.MaxV;
	
	switch(Rotate)
	{
		case 	Draw_Rotate_0D:
					sILI9326->Data.HSX	=	x1;
					sILI9326->Data.HEX	=	x2;
					sILI9326->Data.VSY	=	y1;
					sILI9326->Data.VEY	=	y2;	
					sILI9326->Data.HXA	=	sILI9326->Data.HSX;
					sILI9326->Data.VYA	=	sILI9326->Data.VSY;	
					Model	=	0x5030;
			break;
		case 	Draw_Rotate_90D:
//					sILI9326->Data.HSX	=	y1;
//					sILI9326->Data.HEX	=	y2;	
//					sILI9326->Data.VSY	=	MaxV	-	x2	-	1;
//					sILI9326->Data.VEY	=	MaxV	-	x1	-	1;	
//					sILI9326->Data.HXA	=	sILI9326->Data.HSX;
//					sILI9326->Data.VYA	=	sILI9326->Data.VEY;
						sILI9326->Data.HSX	=	y1;
						sILI9326->Data.HEX	=	y2;	
						sILI9326->Data.VSY	=	MaxV	-	x2	-	1;
						sILI9326->Data.VEY	=	MaxV	-	x1	-	1;	
						sILI9326->Data.HXA	=	sILI9326->Data.HSX;
						sILI9326->Data.VYA	=	sILI9326->Data.VEY;
					Model	=	0X0098;								//GRAM(Graphics RAM--图形内存) Data Write (R202h)准备写入
			break;
		case 	Draw_Rotate_180D:
					sILI9326->Data.HSX	=	MaxH	-	x2	-	1;
					sILI9326->Data.HEX	=	MaxH	-	x1	-	1;
					sILI9326->Data.VSY	=	MaxV	-	y2	-	1;
					sILI9326->Data.VEY	=	MaxV	-	y1	-	1;	
					sILI9326->Data.HXA	=	sILI9326->Data.HEX;
					sILI9326->Data.VYA	=	sILI9326->Data.VEY;	
					Model	=	0X5000;
			break;
		default:
					sILI9326->Data.HSX	=	MaxH	-	y2	-	1;
					sILI9326->Data.HEX	=	MaxH	-	y1	-	1;
					sILI9326->Data.VSY	=	x1;
					sILI9326->Data.VEY	=	x2;	
					sILI9326->Data.HXA	=	sILI9326->Data.HEX;
					sILI9326->Data.VYA	=	sILI9326->Data.VSY;
					Model	=	0X5028;
			break;
	}
	//======================================区域设置
	LCD_WriteCommand(ILI9326_R210_HSA,sILI9326->Data.HSX);		//Window Horizontal RAM Address Start(R210h)		//水平
	LCD_WriteCommand(ILI9326_R211_HEA,sILI9326->Data.HEX);		//Window Horizontal RAM Address End(R211h)			//水平
	LCD_WriteCommand(ILI9326_R212_VSA,sILI9326->Data.VSY);		//Window Vertical RAM Address Start (R212h)			//垂直
	LCD_WriteCommand(ILI9326_R213_VEA,sILI9326->Data.VEY);		//Window Vertical RAM Address End (R213h)				//垂直
	//======================================设置起始点
	LCD_WriteCommand( ILI9326_R200_HA, sILI9326->Data.HSX );
	LCD_WriteCommand( ILI9326_R201_VA, sILI9326->Data.VSY );
	//======================================设置写入模式
	LCD_WriteCommand( ILI9326_R003_EM, Model);
	//======================================启动写入
	LCD_WriteIndexStart();
	LCD_WriteData( ILI9326_R202_GDRW );
	LCD_WriteIndexEnd();
}
//#endif//LCD_61509_EN
/************************************** The End Of FILE **************************************/


