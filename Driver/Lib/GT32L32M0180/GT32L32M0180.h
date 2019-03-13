/******************************************************************************
//┌────────────────────────────────────────┐
//│         高通科技版权所有  						 │
//│      GENITOP RESEARCH CO.,LTD.         │
//│        created on 2015.7.27            │
//└────────────────────────────────────────┘
******************************************************************************/


extern unsigned char r_dat_bat(unsigned long address,unsigned long byte_long,unsigned char *p_arr);
 
#define ASCII_5X7              1      //ASCII编码5X7点阵
#define ASCII_7X8              2      //ASCII编码7X8点阵
#define ASCII_7X8_F            3      //ASCII编码7X8点阵Fat风格字符（具体字形看规格书）
#define ASCII_6X12             4      //ASCII编码6X12点阵
#define ASCII_8X16             5      //ASCII编码8X16点阵
#define ASCII_8X16_F           6      //ASCII编码8X16点阵Fat风格字符（具体字形看规格书）
#define ASCII_12X24            7      //ASCII编码12X24点阵
//#define ASCII_12X24_P          8      //ASCII编码12X24点阵打印体
#define ASCII_16X32            9      //ASCII编码16X32点阵
#define ASCII_16X32_F         10      //ASCII编码16X32点阵Fat风格字符（具体字形看规格书）
#define ASCII_12_A            11      //ASCII编码12x12点阵不等宽Arial风格字符（具体字形看规格书）		
#define ASCII_12_T            12		  //ASCII编码12X12点阵不等宽Time news Roman风格字符（具体字形看规格书）
#define ASCII_16_A            13      //ASCII编码16X16点阵不等宽Arial风格字符（具体字形看规格书）		
#define ASCII_16_T            14		  //ASCII编码16X16点阵不等宽Time news Roman风格字符（具体字形看规格书）
#define ASCII_24_A            15      //ASCII编码24X24点阵不等宽Arial风格字符（具体字形看规格书）		
#define ASCII_24_T            16		  //ASCII编码24X24点阵不等宽Time news Roman风格字符（具体字形看规格书）
#define ASCII_32_A            17      //ASCII编码32X32点阵不等宽Arial风格字符（具体字形看规格书）		
#define ASCII_32_T            18		  //ASCII编码32X32点阵不等宽Time news Roman风格字符（具体字形看规格书）

#defien NUB_14X28							 0
#defien NUB_20X40							 1
#defien NUB_28X28							 2
#defien NUB_40X40							 3

/*************************************************************
函数用法：
    unsigned char DZ_Data[数组长度客户自定义];
    ASCII_GetData(0x41,ASCII_5X7,DZ_Data);      //读取5X7点阵 ASCII 编码A的点阵数据，并将点阵数据存在DZ_Data数组中；数据长度为8 BYTE
	  ASCII_GetData(0x41,ASCII_7X8,DZ_Data);      //读取7X8点阵 ASCII 编码A的点阵数据，并将点阵数据存在DZ_Data数组中；数据长度为8 BYTE
		ASCII_GetData(0x41,ASCII_7X8_F,DZ_Data);		//读取7X8点阵 ASCII 编码A的点阵数据，并将点阵数据存在DZ_Data数组中；数据长度为8 BYTE
	  ASCII_GetData(0x41,ASCII_6X12,DZ_Data);     //读取6X12点阵 ASCII 编码A的点阵数据，并将点阵数据存在DZ_Data数组中；数据长度为12 BYTE
	  ASCII_GetData(0x41,ASCII_8X16,DZ_Data);   	//读取8X16点阵 ASCII 编码A的点阵数据，并将点阵数据存在DZ_Data数组中；数据长度为16 BYTE
	  ASCII_GetData(0x41,ASCII_8X16_F,DZ_Data);   //读取8X16点阵 ASCII 编码A的点阵数据，并将点阵数据存在DZ_Data数组中；数据长度为16 BYTE
	  ASCII_GetData(0x41,ASCII_12X24,DZ_Data);		//读取12X24点阵 ASCII 编码A的点阵数据，并将点阵数据存在DZ_Data数组中；数据长度为48 BYTE
		ASCII_GetData(0x41,ASCII_16X32,DZ_Data);		//读取16X32点阵 ASCII 编码A的点阵数据，并将点阵数据存在DZ_Data数组中；数据长度为64 BYTE
		ASCII_GetData(0x41,ASCII_16X32_F,DZ_Data);	//读取16X32点阵 ASCII 编码A的点阵数据，并将点阵数据存在DZ_Data数组中；数据长度为64 BYTE
		ASCII_GetData(0x41,ASCII_12_A,DZ_Data);     //读取12X12点阵 ASCII 编码A的点阵数据，并将点阵数据存在DZ_Data数组中；数据长度为26 BYTE
		ASCII_GetData(0x41,ASCII_12_T,DZ_Data);     //读取12X12点阵 ASCII 编码A的点阵数据，并将点阵数据存在DZ_Data数组中；数据长度为26 BYTE
	  ASCII_GetData(0x41,ASCII_16_A,DZ_Data);     //读取16X16点阵 ASCII 编码A的点阵数据，并将点阵数据存在DZ_Data数组中；数据长度为34 BYTE
		ASCII_GetData(0x41,ASCII_16_T,DZ_Data);     //读取16X16点阵 ASCII 编码A的点阵数据，并将点阵数据存在DZ_Data数组中；数据长度为34 BYTE
		ASCII_GetData(0x41,ASCII_24_A,DZ_Data);     //读取24X24点阵 ASCII 编码A的点阵数据，并将点阵数据存在DZ_Data数组中；数据长度为74 BYTE
		ASCII_GetData(0x41,ASCII_24_T,DZ_Data);     //读取24X24点阵 ASCII 编码A的点阵数据，并将点阵数据存在DZ_Data数组中；数据长度为74 BYTE
		ASCII_GetData(0x41,ASCII_32_A,DZ_Data);     //读取32X32点阵 ASCII 编码A的点阵数据，并将点阵数据存在DZ_Data数组中；数据长度为128 BYTE
		ASCII_GetData(0x41,ASCII_32_T,DZ_Data);     //读取32X32点阵 ASCII 编码A的点阵数据，并将点阵数据存在DZ_Data数组中；数据长度为128 BYTE
				
*************************************************************/ 
unsigned char  ASCII_GetData(unsigned char  ASCIICode,unsigned long  ascii_kind,unsigned char *DZ_Data);

/*************************************************************
函数用法：
    unsigned char DZ_Data[数组长度客户自定义];
    Dig_Ch_GetData(1,NUB_14X28,DZ_Data);	//读取14X28点阵数字符号字符点阵数据，并将点阵数据存在DZ_Data数组中；数据长度为56 BYTE
	  Dig_Ch_GetData(1,NUB_20X40,DZ_Data);	//读取20X40点阵数字符号字符点阵数据，并将点阵数据存在DZ_Data数组中；数据长度为120 BYTE
		Dig_Ch_GetData(1,NUB_28X28,DZ_Data);	//读取28X28点阵数字符号字符点阵数据，并将点阵数据存在DZ_Data数组中；数据长度为112 BYTE
	  Dig_Ch_GetData(1,NUB_40X40,DZ_Data);	//读取40X40点阵数字符号字符点阵数据，并将点阵数据存在DZ_Data数组中；数据长度为200 BYTE
*************************************************************/ 
unsigned char	 Dig_Ch_GetData(unsigned char  Sequence,unsigned long  NUB_kind,unsigned char *DZ_Data);
 
/*************************************************************
函数用法：
    unsigned char DZ_Data[数组长度客户自定义];
    gt_12_GetData(0xb0,0xa1,0x00,0x00,DZ_Data); //读取12X12点阵 汉字"啊"的点阵数据，并将点阵数据存在DZ_Data数组中；数据长度为24 BYTE
*************************************************************/
unsigned long  gt_12_GetData(unsigned char c1,unsigned char c2,unsigned char c3,unsigned char c4,unsigned char *DZ_Data);

/*************************************************************
函数用法：
    unsigned char DZ_Data[数组长度客户自定义];
    gt_16_GetData(0xb0,0xa1,0x00,0x00,DZ_Data); //读取16X16点阵 汉字"啊"的点阵数据，并将点阵数据存在DZ_Data数组中；数据长度为24 BYTE
*************************************************************/ 
unsigned long  gt_16_GetData(unsigned char  c1, unsigned char  c2, unsigned char  c3, unsigned char  c4,unsigned char *DZ_Data);

/*************************************************************
函数用法：
    unsigned char DZ_Data[数组长度客户自定义];
    gt_24_GetData(0xb0,0xa1,0x00,0x00,DZ_Data); //读取24X24点阵 汉字"啊"的点阵数据，并将点阵数据存在DZ_Data数组中；数据长度为72 BYTE
*************************************************************/ 
unsigned long  gt_24_GetData(unsigned char  c1, unsigned char  c2, unsigned char  c3, unsigned char  c4,unsigned char *DZ_Data);

/*************************************************************
函数用法：
    unsigned char DZ_Data[数组长度客户自定义];
    gt_32_GetData(0xb0,0xa1,0x00,0x00,DZ_Data); //读取32X32点阵 汉字"啊"的点阵数据，并将点阵数据存在DZ_Data数组中；数据长度为128 BYTE
*************************************************************/ 
unsigned long  gt_32_GetData(unsigned char  c1,unsigned char  c2,unsigned char  c3,unsigned char  c4,unsigned char *DZ_Data);

/*************************************************************
函数用法：
    unsigned long BAR_NUM[13]={0,1,2,3,4,5,6,7,8,9,1,2,3};
    unsigned long BAR_ADDR[13];
		BAR_CODE13(BAR_NUM,BAR_ADDR); //获取条形码的地址，并将地址存于数组BAR_ADDR中
*************************************************************/
unsigned long  BAR_CODE13(unsigned char  * BAR_NUM,unsigned char *BAR_PIC_ADDR);
/*************************************************************
函数用法：
    unsigned long BAR_NUM[13]={0,1,2,3,4,5,6,7,8,9,1,2,3};
    unsigned long BAR_ADDR[7];
		BAR_CODE128(BAR_NUM,1,BAR_ADDR); //获取条形码的地址，并将地址存于数组BAR_ADDR中
起始符有3种模式
当flag=1时为Code-128-A;
当flag=2时为Code-128-B;
当flag=3时为Code-128-C;		
*************************************************************/
unsigned long  BAR_CODE128(unsigned char  *BAR_NUM,unsigned char  flag,unsigned char *BAR_PIC_ADDR);

/*************************************************************
函数用法：
    unsigned char DZ_Data[数组长度客户自定义];
    Antenna_CODE_12X12_GetData(0,DZ_Data); //读取12X12点阵天线字符的点阵数据，并将点阵数据存在DZ_Data数组中；数据长度为24 BYTE
*************************************************************/ 
unsigned long  Antenna_CODE_12X12_GetData(unsigned char  NUM,unsigned char *DZ_Data);

/*************************************************************
函数用法：
    unsigned char DZ_Data[数组长度客户自定义];
    Battery_CODE_12X12_GetData(0,DZ_Data); //读取12X12点阵电池字符的点阵数据，并将点阵数据存在DZ_Data数组中；数据长度为24 BYTE
*************************************************************/ 
unsigned long  Battery_CODE_12X12_GetData(unsigned char   NUM,unsigned char *DZ_Data);

/*************************************************************
函数用法：
    unsigned char GBCode;
    GBCode = U2G(0x554A); //将unicode编码数据转换GBK编码
*************************************************************/ 
unsigned long	U2G(unsigned int  unicode);

/*************************************************************
函数用法：
    unsigned char GBCode;
    GBCode = U2G_13(0x554A); //将unicode编码数据转换GBK编码（字符区）
*************************************************************/ 
unsigned int  U2G_13(unsigned int  Unicode);

/*************************************************************
函数用法：
    unsigned char GBCode;
    GBCode = BIG5_G(0xB0DA); //将Big5编码数据转换GBK编码 
*************************************************************/ 
unsigned long  BIG5_G(unsigned int  B5code);
 




