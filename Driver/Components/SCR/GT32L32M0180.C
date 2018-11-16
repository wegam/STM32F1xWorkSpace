/******************************** User_library *********************************
* 文件名 	: STM32_GT32L32M0180.C
* 作者   	: wegam@sina.com
* 版本   	: V
* 日期   	: 2017/01/15
* 说明   	: 
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/


#include "GT32L32M0180.H"

//#include "STM32_SPI.H"

#define STM32_GT32L32M0180_Code_Edit

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/


/* Private functions ---------------------------------------------------------*/

SPIDef		*pSPI = NULL;       //内部驱动使用，不可删除

u8 BAR_PIC_ADDR[64]={0XFF};
u8 GBCode[64]={0XFF};


//---------私有函数


u32 GT32L32_GetAddress(u8 font, u8 c1, u8 c2, u8 c3, u8 c4);//获取地址
u32 GT32L32_GetBufferLen(u8 font, u8 c1, u8 c2, u8 c3, u8 c4);//获取长度
u16 GT32L32_ReadBuffer(u32 Address,u32 lengh,u8 *ReadBuffer);		//从字库中读数据并返回数据长度

u32 GT32L32_GetGB18030(u8 c1, u8 c2, u8 c3, u8 c4);		//12x12点阵GB18030汉字&字符地址计算


u32 GT32L32_GetBarCode_13(u8 * BAR_NUM);															//EAN13条形码调用程序
u32 GT32L32_GetBarCode_128(u8	*BAR_NUM,u8	flag);											//GB/T 18347-2001(CODE128)条形码调用程序



u16	GT32L32_U2G_13(u16 Unicode);																			//UNICODE转GBK码表映射算法,仅1&3字符区
u32 GT32L32_UNICODE_To_GBK(u16 unicode,u8 *GetBuffer);								//UNICODE转GBK码表映射算法（不含符号区,转换全部双字节区） 
u32 GT32L32_BIG5_To_GBK(u16 BIG5_Code,u8 *GetBuffer);									//BIG5转GBK转换算法
/*******************************************************************************
*函数名			:	function
*功能描述		:	function
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
void GT32L32_Initialize(SPIDef *SpiPort)
{
  pSPI  = SpiPort;
  SPI_Initialize(pSPI);				//普通SPI通讯方式配置
	SPI_CS_LOW(pSPI);
	SPI_CS_HIGH(pSPI);
}

/*************************************************************************************************** 
32x32点阵GB18030汉字&字符
函数：u32 GB18030_32_GetData (u8 c1, u8 c2, u8 c3, u8 c4)  
功能：计算汉字点阵在芯片中的地址 
参数：c1,c2,c3,c4：4字节汉字内码通过参数c1,c2,c3,c4传入，双字节内码通过参数c1,c2传 入，c3=0,c4=0 
返回：汉字点阵的字节地址(byte address)。如果用户是按 word mode 读取点阵数据，
则其地 址(word address)为字节地址除以2，即：word address = byte address / 2 . 
例如：BaseAdd: 说明汉字点阵数据在字库芯片中的起始地址，即BaseAdd＝0x47AE10; “啊”字的内码为0xb0a1,
则byte address = gt(0xb0,0xa1,0x00,0x00) *128+BaseAdd word address = byte address / 2 
“.”字的内码为0x8139ee39,则byte address = gt(0x81, 0x39,0xee,0x39) *128+ BaseAdd word address = byte address / 2 
****************************************************************************************************/
u32 GT32L32_GetGB18030(u8 c1, u8 c2, u8 c3, u8 c4) 
{ 
	u32 Address=0;						//Address：对应字符点阵在芯片中的字节地址。
	u32  BaseAdd=0x47AE10;		//32x32点阵字库起始地址：BaseAdd＝0x47AE10，
	if(c2==0x7f) 
	{
		return (BaseAdd);
	}
	//====================Section 1
	if((c1>=0xA1 && c1 <= 0xAB) && c2>=0xA1) 			//Section 1
	{
		Address= (c1 - 0xA1) * 94 + (c2 - 0xA1);
	}
	//====================Section 5	
	else if((c1>=0xa8 && c1 <= 0xa9) && c2<0xa1) 	//Section 5
	{ 
		if(c2>0x7f)
			c2--; 
		Address=(c1-0xa8)*96 + (c2-0x40)+846; 
	}
	//====================Section 2
	if((c1>=0xb0 && c1 <= 0xf7) && c2>=0xa1) 			//Section 2
	{
		Address= (c1 - 0xB0) * 94 + (c2 - 0xA1)	+	1038-192;
	}
	//====================Section 3
	else if((c1<0xa1 && c1>=0x81) && c2>=0x40 ) 	//Section 3
	{ 
		if(c2>0x7f) 
			c2--;
		Address=(c1-0x81)*190 + (c2-0x40) + 1038 +	6768-192;
	}
	//====================Section 4
	else if(c1>=0xaa && c2<0xa1) 								//Section 4
	{ 
		if(c2>0x7f) 
			c2--; 
		Address=(c1-0xaa)*96 + (c2-0x40) + 1038 +	12848-192; 
	}
	else if(c1==0x81 && c2>=0x39) 							//四字节区1 
	{ 
		Address =1038 + 21008+(c3-0xEE)*10+c4-0x39; 
	} 
	else if(c1==0x82)														//四字节区2 
	{ 
		Address =1038 + 21008+161+(c2-0x30)*1260+(c3-0x81)*10+c4-0x30; 
	} 
	return	Address;  
}
/*******************************************************************************
*函数名			:	function
*功能描述		:	函数功能说明
*输入				: 4字节汉字内码通过参数c1,c2,c3,c4传入，双字节内码通过参数c1,c2 传入，c3=0,c4=0 
*返回值			:	汉字点阵的字节地址(Address)。
*******************************************************************************/
u32 GT32L32_GetAddress(u8 font, u8 c1, u8 c2, u8 c3, u8 c4)
{
	u32 Address=0;	//汉字点阵的字节地址(Address)
	u32 BaseAddr=0;
	//判断单字节与双字节字符（汉字通常为双字节）
	if(c1>0x80)				//双字节，ASCII码表为（0x00~0x7F)
	{
		//字体大小判断
		if(font==12)				//(u32)0x113D0E,			//12x12点阵GB18030汉字/
		{
			Address=GT32L32_GetGB18030(c1,	c2,	0,	0)*24+0x113D0E+192*24;
		}
		else if(font==16)		//(u32)0x194FDE,			//16x16点阵GB18030汉字
		{
			Address=GT32L32_GetGB18030(c1,	c2,	c3,	c4)*32+0x194FDE+192*32;
		}
		else if(font==24)		//(u32)0x2743DE,			//24x24点阵GB18030汉字
		{
			Address=GT32L32_GetGB18030(c1,	c2,	c3,	c4)*72+0x2743DE+192*72;
		}
		else if(font==32)		//(u32)0x47AE10,			//32x32点阵GB18030汉字
		{
			Address=GT32L32_GetGB18030(c1,	c2,	c3,	c4)*128+0x47AE10;
		}
	}
	else							//单字节，ASCII码表为（0x00~0x7F)
	{
		if  ((c1 >0x20)&&(c1<=0x7e))		//ASCIICode ASCII码表为（0x00~0x7F)	（0x00~0x20为控制符)
		{	
			switch(font)
			{
				case 0x100000:	Address=(c1-0x20)*8+0x100000;		//(u32)0x100000,			//5x7点阵ASCII标准字符
							break ;
				case 0x100300:	Address=(c1-0x20)*8+0x100300;		//(u32)0x100300,			//7x8点阵ASCII标准字符
							break ;
				case 0x100600:	Address=(c1-0x20)*8+0x100600;		//(u32)0x100600,			//7x8点阵ASCII粗体字符
							break ;
				case 12:	      Address=(c1-0x20)*12+0x100900;  //(u32)0x100900,			//6x12点阵ASCII字符
								break ;
				case 0x100D80:	Address=(c1-0x20)*16+0x100D80;  //(u32)0x100D80,			//8x16点阵ASCII标准字符
							break ;  
				case 16:				Address=(c1-0x20)*16+0x101580;  //(u32)0x101580,			//8x16点阵ASCII粗体字符
							break ;
				case 24:				Address=(c1-0x20)*48+0x101B80;  //(u32)0x101B80,			//12x24点阵ASCII标准字符
							break ;  
				case 32: 				Address=(c1-0x20)*64+0x102D80;  //(u32)0x102D80,			//16x32点阵ASCII标准字符
							break ;
				case 52: 	      Address=(c1-0x20)*64+0x104580;  //(u32)0x104580,			//16x32点阵ASCII粗体字符
							break ;
				case 62: 	      Address=(c1-0x20)*26+0x105D80;  //(u32)0x105D80,			//12点阵不等宽ASCII方头（Arial）字符
							break ;
				case 0x106740: 	Address=(c1-0x20)*34+0x106740;  //(u32)0x106740,			//16点阵不等宽ASCII方头（Arial）字符
							break ; 
				case 0x107400: 	Address=(c1-0x20)*74+0x107400;  //(u32)0x107400,			//24点阵不等宽ASCII方头（Arial）字符
							break ;
				case 0x108FC0: 	Address=(c1-0x20)*130+0x108FC0; //(u32)0x108FC0,			//32点阵不等宽ASCII方头（Arial）字符
							break ;
				case 121: 	    Address=(c1-0x20)*26+0x10C080;  //(u32)0x10C080,			//12点阵不等宽ASCII白正（Times New Roman）字符
							break ;
				case 56: 	      Address=(c1-0x20)*34+0x10CA50;  //(u32)0x10CA50,			//16点阵不等宽ASCII白正（Times New Roman）字符
							break ;
				case 54: 	      Address=(c1-0x20)*74+0x10D740;  //(u32)0x10D740,			//24点阵不等宽ASCII白正（Times New Roman）字符
							break ;
				case 36: 	      Address=(c1-0x20)*130+0x10F340; //(u32)0x10F340,			//32点阵不等宽ASCII白正（Times New Roman）字符
							break ;  
				default: 
							break ;
			}
		}	
	}	
	return(Address);
}
/*************************************************************************************************** 
16x16点阵GB18030汉字&字符
函数：u8 GB18030_16_GetData(u8 c1, u8 c2, u8 c3, u8 c4) 
功能：计算汉字点阵在芯片中的地址,读取点阵数据到指定数组。 
参数：c1,c2,c3,c4：
4字节汉字内码通过参数c1,c2,c3,c4传入，双字节内码通过参数c1,c2 传入，c3=0,c4=0 
返回：汉字点阵的字节地址(byte address)。
如果用户是按 word mode 读取点阵数据，则其地址(word address)为字节地址除以2，
即：word address = byte address / 2 . 例如：
BaseAdd: 说明汉字点阵数据在字库芯片中的起始地址，即BaseAdd＝0x114FDE;
 “啊”字的内码为0xb0a1,则byte address = GB18030_16_GetData(0xb0,0xa1,0x00,0x00) *32+BaseAdd; 
word address = byte address / 2 
“.”字的内码为0x8139ee39,则byte address = GB18030_16_GetData(0x81,0x39,0xee,0x39) *32+ BaseAdd
word address = byte address / 2 
****************************************************************************************************/
u32 GT32L32_GetBufferLen(u8 font, u8 c1, u8 c2, u8 c3, u8 c4) 
{	
	u32 lengh=0;
	//判断单字节与双字节字符（汉字通常为双字节）
	if(c1>0x80)				//双字节，ASCII码表为（0x00~0x7F)
	{	
		//字体大小判断
		if(font==12)
		{
			lengh=24;		//12/8/1(列）x12（行）
		}
		else if(font==16)
		{
			lengh=32;		//16/8/1(列）x16（行）
		}
		else if(font==24)
		{
			lengh=72;		//24/8/1(列）x24（行）
		}
		else if(font==32)
		{
			lengh=128;	//32/8/1(列）x32（行）
		}
	}
	else
	{
		//字体大小判断
		if(font==12)
		{
			lengh=16;		//12/8/2(列）x12（行）
		}
		else if(font==16)
		{
			lengh=16;		//16/8/2(列）x16（行）
		}
		else if(font==24)
		{
			lengh=48;		//24/8/2(列）x24（行）
		}
		else if(font==32)
		{
			lengh=64;	//32/8/2(列）x32（行）
		}
	}
	return lengh;	 
}



/**********************************************************************
EAN13条形码调用程序
函数：DWORD* BAR_CODE(int* BAR_NUM)
功能：将数组条形码转为对应条形码图形地址。
参数：int* BAR_NUM 条形码数字数组指针，BAR_NUM[13]数组包含13个数字。
返回：定义DWORD BAR_PIC_ADDR[13];用于存放对应地址，返回此数组指针。
***********************************************************************/
u32 GT32L32_GetBarCode_13(u8 * BAR_NUM)
{
	u32 i,BaseAddr=0x478FD2;
	BAR_PIC_ADDR[0]=BAR_NUM[0]*54+540*0+ BaseAddr;
	BAR_PIC_ADDR[1]=BAR_NUM[1]*54+540*1+ BaseAddr;
	switch(BAR_NUM[0])
	{
		case 0:
			for(i=2;i<=6;i++)
			{
				BAR_PIC_ADDR[i]=BAR_NUM[i]*54+540*1+ BaseAddr;
			}
		break;
		case 1:
			BAR_PIC_ADDR[2]=BAR_NUM[2]*54+540*1+ BaseAddr;
			BAR_PIC_ADDR[3]=BAR_NUM[3]*54+540*2+ BaseAddr;
			BAR_PIC_ADDR[4]=BAR_NUM[4]*54+540*1+ BaseAddr;
			BAR_PIC_ADDR[5]=BAR_NUM[5]*54+540*2+ BaseAddr;
			BAR_PIC_ADDR[6]=BAR_NUM[6]*54+540*2+ BaseAddr;
		break;
		case 2:
			BAR_PIC_ADDR[2]=BAR_NUM[2]*54+540*1+ BaseAddr;
			BAR_PIC_ADDR[3]=BAR_NUM[3]*54+540*2+ BaseAddr;
			BAR_PIC_ADDR[4]=BAR_NUM[4]*54+540*2+ BaseAddr;
			BAR_PIC_ADDR[5]=BAR_NUM[5]*54+540*1+ BaseAddr;
			BAR_PIC_ADDR[6]=BAR_NUM[6]*54+540*2+ BaseAddr;
		break;
		case 3:
			BAR_PIC_ADDR[2]=BAR_NUM[2]*54+540*1+ BaseAddr;
			BAR_PIC_ADDR[3]=BAR_NUM[3]*54+540*2+ BaseAddr;
			BAR_PIC_ADDR[4]=BAR_NUM[4]*54+540*2+ BaseAddr;
			BAR_PIC_ADDR[5]=BAR_NUM[5]*54+540*2+ BaseAddr;
			BAR_PIC_ADDR[6]=BAR_NUM[6]*54+540*1+ BaseAddr;
		break;
		case 4:
			BAR_PIC_ADDR[2]=BAR_NUM[2]*54+540*2+ BaseAddr;
			BAR_PIC_ADDR[3]=BAR_NUM[3]*54+540*1+ BaseAddr;
			BAR_PIC_ADDR[4]=BAR_NUM[4]*54+540*1+ BaseAddr;
			BAR_PIC_ADDR[5]=BAR_NUM[5]*54+540*2+ BaseAddr;
			BAR_PIC_ADDR[6]=BAR_NUM[6]*54+540*2+ BaseAddr;
		break;
		case 5:
			BAR_PIC_ADDR[2]=BAR_NUM[2]*54+540*2+ BaseAddr;
			BAR_PIC_ADDR[3]=BAR_NUM[3]*54+540*2+ BaseAddr;
			BAR_PIC_ADDR[4]=BAR_NUM[4]*54+540*1+ BaseAddr;
			BAR_PIC_ADDR[5]=BAR_NUM[5]*54+540*1+ BaseAddr;
			BAR_PIC_ADDR[6]=BAR_NUM[6]*54+540*2+ BaseAddr;
		break;
		case 6:
			BAR_PIC_ADDR[2]=BAR_NUM[2]*54+540*2+ BaseAddr;
			BAR_PIC_ADDR[3]=BAR_NUM[3]*54+540*2+ BaseAddr;
			BAR_PIC_ADDR[4]=BAR_NUM[4]*54+540*2+ BaseAddr;
			BAR_PIC_ADDR[5]=BAR_NUM[5]*54+540*1+ BaseAddr;
			BAR_PIC_ADDR[6]=BAR_NUM[6]*54+540*1+ BaseAddr;
		break;
		case 7:
			BAR_PIC_ADDR[2]=BAR_NUM[2]*54+540*2+ BaseAddr;
			BAR_PIC_ADDR[3]=BAR_NUM[3]*54+540*1+ BaseAddr;
			BAR_PIC_ADDR[4]=BAR_NUM[4]*54+540*2+ BaseAddr;
			BAR_PIC_ADDR[5]=BAR_NUM[5]*54+540*1+ BaseAddr;
			BAR_PIC_ADDR[6]=BAR_NUM[6]*54+540*2+ BaseAddr;
		break;
		case 8:
			BAR_PIC_ADDR[2]=BAR_NUM[2]*54+540*2+ BaseAddr;
			BAR_PIC_ADDR[3]=BAR_NUM[3]*54+540*1+ BaseAddr;
			BAR_PIC_ADDR[4]=BAR_NUM[4]*54+540*2+ BaseAddr;
			BAR_PIC_ADDR[5]=BAR_NUM[5]*54+540*2+ BaseAddr;
			BAR_PIC_ADDR[6]=BAR_NUM[6]*54+540*1+ BaseAddr;
		break;
		case 9:
			BAR_PIC_ADDR[2]=BAR_NUM[2]*54+540*2+ BaseAddr;
			BAR_PIC_ADDR[3]=BAR_NUM[3]*54+540*2+ BaseAddr;
			BAR_PIC_ADDR[4]=BAR_NUM[4]*54+540*1+ BaseAddr;
			BAR_PIC_ADDR[5]=BAR_NUM[5]*54+540*2+ BaseAddr;
			BAR_PIC_ADDR[6]=BAR_NUM[6]*54+540*1+ BaseAddr;
		break;
	}
	BAR_PIC_ADDR[7]=BAR_NUM[7]*54+540*3+ BaseAddr;
	for(i=8;i<=11;i++)
	{
		BAR_PIC_ADDR[i]=BAR_NUM[i]*54+540*4+ BaseAddr;
	}
	BAR_PIC_ADDR[12]=BAR_NUM[12]*54+540*5+ BaseAddr;
	
	memcpy(BAR_NUM,BAR_PIC_ADDR,140);	
	return BAR_PIC_ADDR[0];
}

/***********************************************************************************************
GB/T 18347-2001(CODE128)条形码调用程序
函数：u32 BAR_CODE128(u8 *BAR_NUM)
功能：将数组条形码转为对应条形码图形地址
参数：u8 *BAR_NUM 条形码数字数组指针,BAR_NUM[4]数组包含4个条形码ASCII符(数组取值为0~94)。
返回：定义u32 BAR_PIC_ADDR[7] ；用于存放对应地址，返回数组指针。
设基地址：BaseAddr=0x3F2ED3;
起始符有3种模式
当flag=1时为Code-128-A;
当flag=2时为Code-128-B;
当flag=3时为Code-128-C;
***********************************************************************************************/
u32 GT32L32_GetBarCode_128(u8	*BAR_NUM,u8	flag)
{
  u32 BaseAddr=0x479C7A;
  u8 i;
  for(i=0;i<7;i++) 
	{
     switch(flag)
		{  
		case 1 :
			 if(i==0)
			 {
				 BAR_PIC_ADDR[i]=103*40+BaseAddr;
			 }
			 else if(i==1||i==2||i==3||i==4)           
			 {
				 BAR_PIC_ADDR[i]=BAR_NUM[i-1]*40+BaseAddr;
			 }
			 else if(i==5)
			 {
				 BAR_PIC_ADDR[i]=95*40+BaseAddr;
			 }
			 else if(i==6)
			 {
				 BAR_PIC_ADDR[i]=106*40+BaseAddr;
			 }
			 break;
     
		case 2 :
			if(i==0)
			{
				BAR_PIC_ADDR[i]=104*40+BaseAddr;
			}
			else if(i==1||i==2||i==3||i==4)           
			{
				BAR_PIC_ADDR[i]=BAR_NUM[i-1]*40+BaseAddr;
			}
			else if(i==5)
			{
				BAR_PIC_ADDR[i]=95*40+BaseAddr;
			}
			else if(i==6)
			{
				BAR_PIC_ADDR[i]=106*40+BaseAddr;
			}
			break;
   	       
		case 3 :
			if(i==0)
			{
				BAR_PIC_ADDR[i]=105*40+BaseAddr;
			}
			else if(i==1||i==2||i==3||i==4)           
			{
				BAR_PIC_ADDR[i]=BAR_NUM[i-1]*40+BaseAddr;
			}
			else if(i==5)
			{
				BAR_PIC_ADDR[i]=95*40+BaseAddr;
			}
			else if(i==6)
			{
				BAR_PIC_ADDR[i]=106*40+BaseAddr;
			}
			break;
   
     default:
     break;
		}
	}
	return BAR_PIC_ADDR[0];
}


/**********************************************************
UNICODE转GBK码表映射算法,仅1&3字符区 
函数：WORD U2G(WORD Unicode) 
功能：将UNICODE码转换为GB码,
注：仅应用于1区&3区。 
参数：WORD Unicode,表示输入的UNICODE码。 
返回：对应的GB码在字库中存放的地址。
（注:读取对应地址2字节数据即为unicode对应的GB码）。
***********************************************************/ 

u16 GT32L32_U2G_13(u16 Unicode) 
{
	u16 GB_Code; 
	u32 i; 
	u16 UG[]={	0x3000,0x3001,0x3002,0x00b7,0x02c9,0x02c7,0x00a8,
							0x3003,0x3005,0x2014, 0xff5e,0x2016,0x2026,0x2018,0x2019,0x201c,
							0x201d,0x3014,0x3015,0x3008, 0x3009,0x300a,0x300b,0x300c,0x300d,
							0x300e,0x300f,0x3016,0x3017,0x3010, 0x3011,0x00b1,0x00d7,0x00f7,
							0x2236,0x2227,0x2228,0x2211,0x220f,0x222a, 0x2229,0x2208,0x2237,
							0x221a,0x22a5,0x2225,0x2220,0x2312,0x2299,0x222b, 0x222e,0x2261,
							0x224c,0x2248,0x223d,0x221d,0x2260,0x226e,0x226f,0x2264, 0x2265,
							0x221e,0x2235,0x2234,0x2642,0x2640,0x00b0,0x2032,0x2033,0x2103,
							0xff04,0x00a4,0xffe0,0xffe1,0x2030,0x00a7,0x2116,0x2606,0x2605,
							0x25cb, 0x25cf,0x25ce,0x25c7,0x25c6,0x25a1,0x25a0,0x25b3,0x25b2,
							0x203b,0x2192, 0x2190,0x2191,0x2193,0x3013
						}; 

	if(Unicode<=0xffe5&&Unicode>=0xff01)//section 3 
	{ 
		if(Unicode==0xff04) 
			GB_Code=0xa1e7;
		if(Unicode==0xff5e) 
			GB_Code=0xa1ab; 
		if(Unicode==0xffe0) 
			GB_Code=0xa1e9; 
		if(Unicode==0xffe1) 
			GB_Code=0xa1ea; 
		if(Unicode==0xffe3) 
			GB_Code=0xa3fe; 
		if(Unicode==0xffe5) 
			GB_Code=0xa3a4; 
		else
			GB_Code=Unicode-0xff01+0xa3a1; 
	} 
	if(Unicode<=0x3013) 
	{ 
		for(i=0;i<94;i++) 
		{ 
			if(Unicode==UG[i]) 
			GB_Code=0xa1a1+i; 
		} 
	}
	GBCode[0]=GB_Code>>8;
	GBCode[1]=GB_Code&0xff;
	return GB_Code;
}

/***************************************************************************
UNICODE转GBK码表映射算法（不含符号区,转换全部双字节区）
GB_Address转换之后的GB码的存放地址， 
函数：u32 U2G(u16 Unicode) 
功能：将UNICODE码转换为GB码, 
参数：u16 Unicode,表示输入的UNICODE码。 
返回：对应的GB码在字库中存放的地址。 
（注:读取对应地址2字节数据即为unicode对应的GB码）。
转码表起始地址： BaseAdd＝0x3EA90E;
***************************************************************************/
u32 GT32L32_UNICODE_To_GBK(u16 unicode,u8 *GetBuffer)
{
	u32 BaseAdd=0x46A90E;
	u32 Address,U_Start_Addr;
	if(unicode<=0x0451&&unicode>=0x00a0) 
	{
		U_Start_Addr	=	0;
		Address= U_Start_Addr +(unicode-0x00a0)*2; 
	} 
	else if(unicode<=0x2642&&unicode>=0x2010) 
	{ 
		U_Start_Addr =1892; 
		Address= U_Start_Addr +(unicode-0x2010)*2; 
	} 
	else if(unicode<=0x33d5&&unicode>=0x3000) 
	{ 
		U_Start_Addr =5066; 
		Address= U_Start_Addr +(unicode-0x3000)*2; 
	} 
	else if(unicode<=0x9fa5&&unicode>=0x4e00) 
	{ 
		U_Start_Addr =7030; 
		Address= U_Start_Addr +(unicode-0x4e00)*2; 
	} 
	else if(unicode<=0xfe6b&&unicode>=0xfe30) 
	{ 
		U_Start_Addr =48834; 
		Address= U_Start_Addr +(unicode-0xfe30)*2; 
	} 
	else if(unicode<=0xff5e&&unicode>=0xff01) 
	{ 
		U_Start_Addr =48954; 
		Address= U_Start_Addr +(unicode-0xff01)*2; 
	} 
	else if(unicode<=0xffe5&&unicode>=0xffe0) 
	{ 
		U_Start_Addr =49142; 
		Address= U_Start_Addr +(unicode-0xffe0)*2; 
	} 
	else if (unicode<=0xFA29&&unicode>=0xF92C) 
	{ 
		U_Start_Addr =49312; 
		Address= U_Start_Addr +(unicode-0xF92C)*2; 
	} 
	else if(unicode<=0xE864&&unicode>=0xE816) 
	{ 
		U_Start_Addr =49820; 
		Address= U_Start_Addr +(unicode-0xE816)*2; 
	}
	else if(unicode<=0x2ECA&&unicode>=0x2E81) 
	{ 
		U_Start_Addr =49978; 
		Address= U_Start_Addr +(unicode-0x2E81)*2; 
	} 
	else if(unicode<=0x49B7&&unicode>=0x4947) 
	{ 
		U_Start_Addr =50126; 
		Address= U_Start_Addr +(unicode-0x4947)*2; 
	} 
	else if(unicode<=0x4DAE&&unicode>=0x4C77) 
	{ 
		U_Start_Addr =50352; 
		Address= U_Start_Addr +(unicode-0x4C77)*2; 
	} 
	else if(unicode<=0x3CE0&&unicode>=0x3447) 
	{ 
		U_Start_Addr =50976; 
		Address= U_Start_Addr +(unicode-0x3447)*2; 
	} 
	else if(unicode<=0x478D&&unicode>=0x4056) 
	{ 
		U_Start_Addr =55380; 
		Address= U_Start_Addr +(unicode-0x4056)*2; 
	} 
	Address+=BaseAdd;
	return Address; 
}
/***********************************************************
BIG5转GBK转换算法
函数：u32 GT32L32_BIG5_To_GBK(u16 BIG5_Code) 
功能：计算BIG5码对应GB码存放的起始地址 
参数：BIG5_Code 输入BIG5编码双字节 
返回：对应GB码存放地址，对应GB码高位在前，低位在后。
************************************************************/
u32 GT32L32_BIG5_To_GBK(u16 BIG5_Code,u8 *GetBuffer) 
{
	u32 Address,part_addr,BaseAddr=0x7F1E10;//转码表基地址; 
	u8 TMP,BIG5_MSB,BIG5_LSB; 
	BIG5_MSB= BIG5_Code >>8; 
	BIG5_LSB= BIG5_Code &0x00ff; 

	if(BIG5_MSB>=0xa1&&BIG5_MSB<=0xa3)
	{ 
		part_addr=0; 
		TMP=0xa1; 
	} 
	else if(BIG5_MSB>=0xa4&&BIG5_MSB<=0xc6) 
	{ 
		part_addr=816; 
		TMP=0xa4; 
	} 
	else if(BIG5_MSB>=0xc9&&BIG5_MSB<=0xf9) 
	{ 
		part_addr=11618; TMP=0xc9; 
	}
	if(BIG5_LSB<=0x7e&&BIG5_LSB>=0x40) 
	{ 
		Address=part_addr+((BIG5_MSB-TMP)*157+BIG5_LSB-0x40)*2+BaseAddr; 
	}
	else if(BIG5_LSB<=0xfe&&BIG5_LSB>=0xa1) 
	{ 
		Address=part_addr+((BIG5_MSB-TMP)*157+BIG5_LSB-0xa1+63)*2+BaseAddr; 
	}
	return Address; 
}

/*******************************************************************************
* 函数名			:	GT32L32_ReadStatus
* 功能描述		:	读取芯片状态 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
u8 GT32L32_ReadStatus(GT32L32Def *pInfo)
{
	//____________定义变量
	u8	ChipStatus=0;
	u8	Address=0x05;	//0X60 OR 0XC7
	//____________使能片选
	GPIO_ResetBits(GPIOC,GPIO_Pin_6);
	SPI_Cmd(pInfo->SPI.Port.SPIx, ENABLE);
	//____________发送地址数据	
	SPI_ReadWriteByteSPI(&pInfo->SPI,Address);						//发送地址
	//____________接收数据	
	
	ChipStatus=SPI_ReadWriteByteSPI(&pInfo->SPI,0XFF);// 从字库读出点阵数据到数组中。

	//____________取消片选	
	GPIO_SetBits(GPIOC,GPIO_Pin_6);
	SPI_Cmd(pInfo->SPI.Port.SPIx, DISABLE);

	return ChipStatus;
}
/*******************************************************************************
* 函数名			:	GT32L32_ChipErase
* 功能描述		:	 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
void GT32L32_ChipErase(GT32L32Def *pInfo)
{
	//____________定义变量
	u32 i=0;
	u8	len=255;
	u8	Address=0x60;	//0X60 OR 0XC7
	//____________使能片选
	GPIO_ResetBits(GPIOC,GPIO_Pin_6);
	SPI_Cmd(pInfo->SPI.Port.SPIx, ENABLE);

	SPI_ReadWriteByteSPI(&pInfo->SPI,Address);						//发送地址

	for(i=0;i<len;i++)
	{
	 SPI_ReadWriteByteSPI(&pInfo->SPI,0XFF);// 从字库读出点阵数据到数组中。
	}
	//____________取消片选	
	GPIO_SetBits(GPIOC,GPIO_Pin_6);
	SPI_Cmd(pInfo->SPI.Port.SPIx,DISABLE);
}
/*******************************************************************************
* 函数名			:	GT32L32_ReadBuffer
* 功能描述		:	从字库中指定地址开始读取指定个数的数据
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
u16 GT32L32_ReadBuffer(
												u32 Address,					  //起始地址
												u32 lengh,						  //需要读取的长度
                        u8 *ReadBuffer				  //接收数据的缓存
											)
{
	//____________定义变量
	u32 i=0;
	//____________使能片选
//	SPI_Cmd(pInfo->SPI.Port.SPIx, ENABLE);
	SPI_CS_LOW(pSPI);
	Address=Address|0x03000000;		//0x03指令字+地址。
//	Address=Address|0x0B000000;//0x0B指令字+地址。--快速

	SPI_ReadWriteByteSPI(pSPI,Address>>24);				//发送地址高8位
	SPI_ReadWriteByteSPI(pSPI,Address>>16);				//发送地址
	SPI_ReadWriteByteSPI(pSPI,Address>>8);				//发送地址
	SPI_ReadWriteByteSPI(pSPI,Address);						//发送地址
	
//	if((Address&0x0B000000)==0x0B000000)
//		SPI_ReadWriteByteSPI(pInfo->SPI.Port.SPIx,0XFF);						//从字库读出点阵数据到数组中。
//	while((Status=GT32L32_ReadStatus()&0x01)!=0x01);
	for(i=0;i<lengh;i++)
	{
		ReadBuffer[i]=SPI_ReadWriteByteSPI(pSPI,0XFF);	//从字库读出点阵数据到数组中。
	}
	//____________取消片选	
	SPI_CS_HIGH(pSPI);
//	SPI_Cmd(pInfo->SPI.Port.SPIx, DISABLE);
//	pInfo->Data.Address			=	Address;
//	pInfo->Data.BufferSize	=	lengh;
	return lengh;	
}
/*******************************************************************************
* 函数名			:	GT32L32_GetAntennaCode
* 功能描述		:	天线符号读取程序，获取12X12天线调用地址,取出点阵数据
* 输入			: NUM 0123带表天线信号强度
							GetBuffer 数据接收缓存
* 返回值			: 读取的数据长度
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
u32 GT32L32_GetAntennaCode(u8	NUM,u8 *GetBuffer)
{
  u32 lengh=24;
	u32 Address,BaseAdd=0x47AD32;  
	Address=NUM*24+BaseAdd;

  GT32L32_ReadBuffer(Address,lengh,GetBuffer);		//从字库中读数据并返回数据长度
  
	return lengh;
}
/*******************************************************************************
* 函数名			:	GT32L32_GetBatteryCode
* 功能描述		:	电池符号读取程序，获取12X12电池调用地址,取出点阵数据
* 输入			: NUM 0123带表电池电量
							GetBuffer 数据接收缓存
* 返回值			: 读取的数据长度
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
u32 GT32L32_GetBatteryCode(u8	NUM,u8 *GetBuffer)
{
  u32 lengh=24;
	u32 Address, BaseAdd=0x47ADAA;
	Address=BaseAdd+NUM*24;
  
  GT32L32_ReadBuffer(Address,lengh,GetBuffer);		//从字库中读数据并返回数据长度
  
	return lengh;
}
/*******************************************************************************
* 函数名			:	GT32L32_ReadCode
* 功能描述		:	从字库中读数据并返回数据长度 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
u16 GT32L32_ReadCode(
												u8 font,								//字体大小
												u16 word,								//字符内码值
                        u8 *ReadBuffer				  //接收数据的缓存
											)
{
	//____________定义变量
	u32 i=0;
	u32 Address=0;
	u32 lengh=0;
	//区分单双字节
	if(word>>8>=0x80)
	{
		Address	=	GT32L32_GetAddress(font, (u8)(word>>8), (u8)word, 0, 0);		//获取地址
		lengh= GT32L32_GetBufferLen(font, (u8)(word>>8), (u8)word, 0, 0);			//获取长度
	}
	else
	{
		Address	=	GT32L32_GetAddress(font, (u8)word, 0, 0, 0);			//获取地址
		lengh= GT32L32_GetBufferLen(font, (u8)word, 0, 0, 0);			//获取长度
	}	
  GT32L32_ReadBuffer(Address,lengh,ReadBuffer);		//读取数据
	return lengh;
}

/*******************	wegam@sina.com	*******************/
/*********************	2017/01/21	*********************/
/**********************	END OF FILE	*********************/


