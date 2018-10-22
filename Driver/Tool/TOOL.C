/************************************ TOOLS ************************************
* 文件名 	: LinkedList链表
* 作者   	: wegam@sina.com
* 版本   	: V
* 日期   	: 2017/09/11
* 说明   	: 
********************************************************************************
其它说明:
*
*
*
*
*
*
*
*
*******************************************************************************/
#include 	"TOOL.H"

#include	"stdio.h"				//用于printf
#include	"string.h"			//用于printf
#include	"stdarg.h"			//用于获取不确定个数的参数
#include	"stdlib.h"			//malloc动态申请内存空间


#define NULL 0

#define LEN sizeof(struct student)

struct student
{
	long num; 						/*学号 */
	float score; 					/*分数，其他信息可以继续在下面增加字段 */
	struct student *next; /*指向下一结点的指针 */
};
int n; /*结点总数 */


/////////////////////////////////CRC//////////////////////////////////////////
/*******************************************************************************
* 函数名			:	function
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: wegam@sina.com
*******************************************************************************/
BuildTimeDef GetBuildTime(void* pDate, void*	pTime)
{
	static BuildTimeDef	BuildTime;
	//=============================================转换日期
	BuildTime.year		=	GetBuildYear((char*)pDate);
	BuildTime.month		=	GetBuildMonth((char*)pDate);
	BuildTime.day			=	GetBuildDay((char*)pDate);
	//=============================================转换时间
	BuildTime.hour		=	GetBuildHour((char*)pTime);
	BuildTime.minute	=	GetBuildMinute((char*)pTime);
	BuildTime.second	=	GetBuildSecond((char*)pTime);
	return BuildTime;
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
unsigned short GetBuildYear(const char* DataStr)
{
	unsigned	short Year	=	0;
//	unsigned	char DataStr[]=__DATE__;
	if(NULL	==DataStr)
		return 0;
	Year	=	(unsigned short)((DataStr[7]-'0')*1000+(DataStr[8]-'0')*100+(DataStr[9]-'0')*10+(DataStr[10]-'0'));
	return	Year;
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
unsigned char GetBuildMonth(const char* DataStr)
{
	unsigned	char Month	=	0;
	if(NULL	==DataStr)
		return 0;
	Month	=	(DataStr[2] == 'c' ? 0\
					:DataStr[2] == 'b' ? 1\
					:DataStr[2] == 'r' ? (__DATE__ [0] == 'M' ? 2 : 3) \
					:DataStr[2] == 'y' ? 4 \
					:DataStr[2] == 'n' ? 5 \
					:DataStr[2] == 'l' ? 6 \
					:DataStr[2] == 'g' ? 7 \
					:DataStr[2] == 'p' ? 8 \
					:DataStr[2] == 't' ? 9 \
					:DataStr[2] == 'v' ? 10 : 11)+1;
//	Month	=	(unsigned char)((DataStr[7]-'0')*1000+(DataStr[8]-'0')*100+(DataStr[9]-'0')*10+(DataStr[10]-'0'));
	return	Month;
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
unsigned char GetBuildDay(const char* DataStr)
{
	unsigned	char Day	=	0;
	if(NULL	==DataStr)
		return 0;

	Day	=	(unsigned char)((DataStr[4] == ' ' ? 0 : DataStr[4] - '0') * 10+ (DataStr[5] - '0'));

	return	Day;
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
unsigned char GetBuildHour(const char* TimeStr)
{
	unsigned	char Hour	=	0;

	if(NULL	==TimeStr)
		return 0;

	Hour	=	(unsigned char)((TimeStr[0]-'0')*10+(TimeStr[1]-'0'));
	return	Hour;
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
unsigned char GetBuildMinute(const char* TimeStr)
{
	unsigned	char Minute	=	0;
	if(NULL	==TimeStr)
		return 0;

	Minute	=	(unsigned char)((TimeStr[3]-'0')*10+(TimeStr[4]-'0'));
	return	Minute;
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
unsigned char GetBuildSecond(const char* TimeStr)
{
	unsigned	char Second	=	0;
	if(NULL	==TimeStr)
		return 0;
	Second	=	(unsigned char)((TimeStr[6]-'0')*10+(TimeStr[7]-'0'));
	return	Second;
}
  
/*******************************************************************************
* 函数名		:	8位异或校验
* 功能描述	: 
* 输入			: buffer计算的数据缓存起始地址
              numb数据长度（个数）
* 输出			: 计算结果
* 返回			: 无
*******************************************************************************/
unsigned char BCC8(const unsigned char *buffer,unsigned short num)			//异或校验
{
	u16 i=0;
	u16 temp=0;
	if(NULL	==	buffer)
	{
		return 0;
	}
	if(1	>=	num)
	{
		return 0;
	}
	for(i=0;i<num;i++)
	{
		temp=temp^buffer[i];
	}
	return temp;
}
/*******************************************************************************
* 函数名		:	异或校验
* 功能描述	: 
* 输入			: 
* 输出			: 计算结果
* 返回			: 无
*******************************************************************************/
unsigned char CRC8(const unsigned char *buffer)			//循环冗余校验
{
	return 0;
}
/*******************************************************************************
* 函数名		:	纵向冗余校验
* 功能描述	: 
* 输入			: 无
* 输出			: 无
* 返回			: 无
*******************************************************************************/
unsigned char LRC8(const unsigned char *buffer)		//纵向冗余校验
{
	return 0;
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
unsigned char GetMaxChar(unsigned char *pBuffer,unsigned short Length)
{
	unsigned short i	=	0;
	unsigned char TempData=0;
	
	TempData	=	pBuffer[0];
	for(i=1;i<Length;i++)
	{
		if(TempData<pBuffer[i])
		{
			TempData	=	pBuffer[i];
		}
	}
	return TempData;
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
unsigned short GetMaxShort(unsigned short *pBuffer,unsigned short Length)
{
	unsigned short i	=	0;
	unsigned short TempData=0;
	
	TempData	=	pBuffer[0];
	for(i=1;i<Length;i++)
	{
		if(TempData<pBuffer[i])
		{
			TempData	=	pBuffer[i];
		}
	}
	return TempData;
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
unsigned long GetMaxLong(unsigned long *pBuffer,unsigned short Length)
{
	unsigned short i	=	0;
	unsigned long TempData=0;
	
	TempData	=	pBuffer[0];
	for(i=1;i<Length;i++)
	{
		if(TempData<pBuffer[i])
		{
			TempData	=	pBuffer[i];
		}
	}
	return TempData;
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
unsigned char GetMinChar(unsigned char *pBuffer,unsigned short Length)
{
	unsigned short i	=	0;
	unsigned char TempData=0;
	
	TempData	=	pBuffer[0];
	for(i=1;i<Length;i++)
	{
		if(TempData>pBuffer[i])
		{
			TempData	=	pBuffer[i];
		}
	}
	return TempData;
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
unsigned short GetMinShort(unsigned short *pBuffer,unsigned short Length)
{
	unsigned short i	=	0;
	unsigned short TempData=0;
	
	TempData	=	pBuffer[0];
	for(i=1;i<Length;i++)
	{
		if(TempData>pBuffer[i])
		{
			TempData	=	pBuffer[i];
		}
	}
	return TempData;
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
unsigned long GetMinLong(unsigned long *pBuffer,unsigned short Length)
{
	unsigned short i	=	0;
	unsigned long TempData=0;
	
	TempData	=	pBuffer[0];
	for(i=1;i<Length;i++)
	{
		if(TempData>pBuffer[i])
		{
			TempData	=	pBuffer[i];
		}
	}
	return TempData;
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
unsigned long GetAveLong(unsigned long *pBuffer,unsigned short Length)	//获取unsigned long型平均值
{
	unsigned short i	=	0;
	unsigned long TempData=0;
	
	TempData	=	pBuffer[0];
	for(i=1;i<Length;i++)
	{
		TempData	=	(TempData	+	pBuffer[i])/2;
	}
	return TempData;
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
unsigned long GetVarLong(unsigned long *pBuffer,unsigned short Length)	//获取unsigned long方差
{
	unsigned short i	=	0;
	unsigned long TempData=0;
	long VarData=0;
	
	//获取平均值
	TempData	=	GetAveLong(pBuffer,Length);	//获取unsigned long型平均值
		
	for(i=0;i<Length;i++)
	{
		if(pBuffer[i]>=TempData)
		{
			VarData+=(pBuffer[i]-TempData)*(pBuffer[i]-TempData);
		}
		else
		{
			VarData-=(TempData-pBuffer[i])*(TempData-pBuffer[i]);
		}
	}
	if(VarData<0)
	{
		VarData	=	0	-	VarData;
	}
	return VarData;
}

