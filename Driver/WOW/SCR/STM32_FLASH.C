/******************************** User_library *********************************
* 文件名 	: STM32_SDCard.H
* 作者   	: wegam@sina.com
* 版本   	: V
* 日期   	: 2016/01/01
* 说明   	: 
********************************************************************************
编程和擦除闪存闪存编程一次可以写入16位(半字)。 
闪存擦除操作可以按页面擦除或完全擦除(全擦除)。
全擦除不影响信息块。 为了确保不发生过度编程， 闪存编程和擦除控制器块是由一个固定的时钟控制的。 
写操作(编程或擦除)结束时可以触发中断。
仅当闪存控制器接口时钟开启时，此中断可以用来从WFI模式退出。
*******************************************************************************/


#include "STM32_FLASH.H"

#include "stm32f10x_flash.h"


#include	"string.h"		//用于printf/串和内存操作函数

//#include "STM32F10x_BitBand.H"

#define STM32_FLASH_SIZE 128 	 		//所选STM32的FLASH容量大小(单位为K)---存储块大小128K
#define STM32_FLASH_WREN 1        //使能FLASH写入(0，不是能;1，使能)

#define STM_SECTOR_SIZE 1024			//字节单位-----扇区大小/页大小

//#if	(STM32_FLASH_SIZE<256)					//小容量
//	#define STM_SECTOR_SIZE 1024			//字节单位-----扇区大小/页大小
//#else 
//	#define STM_SECTOR_SIZE	2048			//字节单位-----扇区大小/页大小
//#endif



//FLASH起始地址
#define STM32_FLASH_BASE	0x08000000 				//STM32 FLASH的起始地址
#define STM32_FLASH_UsedAddr	0x08010000		//备份数据存储起始基地址

u16 STM32_FLASH_BUF[STM_SECTOR_SIZE/2];//最多是2K字节

/*******************************************************************************
*函数名			:	STM32_FLASH_ReadHalfWord
*功能描述		:	读取指定地址的半字(16位数据)
*输入				: Addr	地址(此地址必须为2的倍数!!)
*返回值			:	对应数据
*修改时间		:	20171215
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
u16 STM32_FLASH_ReadHalfWord(u32 Addr)		//读取指定地址的半字(16位数据)
{
	return *(vu16*)Addr; 
}

/*******************************************************************************
*函数名			:	STM32_FLASH_Write_NoCheck
*功能描述		:	不检查的写入数据--闪存编程一次可以写入16位(半字)。
*输入				: StartAddr:	起始地址
							pBuffer:		数据指针
							NumToWrite:	写入的半字(16位)个数数 
*返回值			:	无
*修改时间		:	20171215
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
void STM32_FLASH_Write_NoCheck(u32 StartAddr,u16 *pBuffer,u16 NumToWrite) 	//不检查的写入半字数据  
{ 			 		 
	u16 i;
	for(i=0;i<NumToWrite;i++)
	{
		FLASH_ProgramHalfWord(StartAddr,pBuffer[i]);		//在指定地址编写半字
		StartAddr	+=	2;	//地址增加2.
	}  
}
/*******************************************************************************
*函数名			:	STM32_FLASH_Write
*功能描述		:	从指定地址写入指定长度的数据
*输入				: StartAddr:	起始地址
							pBuffer:		数据指针
							NumToWrite:	半字(16位)数(就是要写入的16位数据的个数.) 
*返回值			:	无
*修改时间		:	20171215
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
void STM32_FLASH_Write(u32 StartAddr,u16 *pBuffer,u16 NumToWrite)		//从指定地址写入指定长度的数据
{
	u32 PageAddress;						//页地址
	u16 PageAddressOffset;			//页内偏移地址(16位字计算)
	u16 RemainderSpace;					//页内剩余存储空间(16位字计算)
	u16 NumWaitToWrite;					//等待写入的长度(16位字计算)	
	u16 TotalHaveWritten	=	0;	//已写入的长度(16位字计算)
 	u16 i;    

	if((StartAddr<STM32_FLASH_BASE)||(StartAddr>=(STM32_FLASH_BASE+1024*STM32_FLASH_SIZE)))		//地址不在合法范围内
		return;					//非法地址	
	
	FLASH_Unlock();		//解锁
	//FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);
	if(StartAddr>STM32_FLASH_BASE)
	{
		PageAddress				=	StartAddr-(StartAddr-STM32_FLASH_BASE)%STM_SECTOR_SIZE;		//计算起始页地址----擦除是按页擦除
	}
	//PageAddress				=	(StartAddr-STM32_FLASH_BASE)/STM_SECTOR_SIZE	+	STM32_FLASH_BASE;		//计算起始页地址----擦除是按页擦除
	//PageAddress				=	0x08008000;		//计算起始页地址----擦除是按页擦除
	PageAddressOffset	=	((StartAddr-STM32_FLASH_BASE)%STM_SECTOR_SIZE)/2;									//在扇区内的偏移(2个字节为基本单位.)----计算在扇区内的起始地址
	RemainderSpace		=	STM_SECTOR_SIZE/2	-	PageAddressOffset;															//页内剩余存储空间(16位字计算)

	//---------------------考虑跨页写情况
	while(TotalHaveWritten<NumToWrite)
	{
		if(RemainderSpace	>=	NumToWrite)		//不需要跨页
		{
			NumWaitToWrite	=	NumToWrite;			//全部数据写入
		}
		else
		{
			NumWaitToWrite	=	STM_SECTOR_SIZE/2	-	PageAddressOffset;
		}
		
		//检查页是否需要擦除
		STM32_FLASH_Read(PageAddress,STM32_FLASH_BUF,STM_SECTOR_SIZE/2);	//读出整个扇区的内容
		for(i=0;i<NumWaitToWrite;i++)		//校验数据----检查需要写入的存储空间是否为空
		{
			if(STM32_FLASH_BUF[PageAddressOffset+i]	!=	0XFFFF)			//检查偏移后的地址是否为空
				break;				//需要擦除
		}
		//需要擦除----注意保存原始不应该擦除的数据
		if(i<NumWaitToWrite)
		{
			//擦除整个页---闪存擦除操作可以按页面擦除或完全擦除(全擦除)
			//FLASH_ErasePage(PageAddress);			//擦除这个扇区
			FLASH_ErasePage(PageAddress);				//擦除这个扇区
			//将待写入数据及原扇区保留数据放入写入缓冲区
			memcpy(&STM32_FLASH_BUF[PageAddressOffset],pBuffer,NumWaitToWrite*2);		//数据拷贝是按字节拷贝									//复制数据
			STM32_FLASH_Write_NoCheck(PageAddress,STM32_FLASH_BUF,PageAddressOffset+NumWaitToWrite);		//将原保留数据和新增加数据写入扇区
		}
		else		//不需要擦除
		{
			STM32_FLASH_Write_NoCheck(PageAddress+PageAddressOffset,pBuffer,NumWaitToWrite);					//写已经擦除了的,直接写入扇区剩余区间.
		}
		
		TotalHaveWritten	+=	NumWaitToWrite;			//已写入计数
		
		//如果需要跨页时需要用到
		PageAddressOffset	=		0;									//新页起始地址0，不需要偏移
		PageAddress				+=	STM_SECTOR_SIZE;		//增加一个页地址
		RemainderSpace		+=	STM_SECTOR_SIZE/2;	//新页起始地址0，剩余页空间为页大小
	}
	FLASH_Lock();		//上锁
}

void STM32_FLASH_WriteBac(u32 StartAddr,u16 *pBuffer,u16 NumToWrite)		//从指定地址写入指定长度的数据
{
	u32 secpos;	   //扇区地址
	u16 secoff;	   //扇区内偏移地址(16位字计算)
	u16 secremain; //扇区内剩余地址(16位字计算)   
 	u16 i;    
	u32 offaddr;   //去掉0X08000000后的地址
	if(StartAddr<STM32_FLASH_BASE||(StartAddr>=(STM32_FLASH_BASE+1024*STM32_FLASH_SIZE)))		//地址不在合法范围内
		return;			//非法地址	
	
	FLASH_Unlock();		//解锁
	
	offaddr	=	StartAddr	-	STM32_FLASH_BASE;		//实际偏移地址.
	secpos	=	offaddr		/	STM_SECTOR_SIZE;		//扇区地址  0~127 for STM32F103RBT6---计算起始扇区地址
	//---------------------考虑跨页写情况
	secoff	=	(offaddr%STM_SECTOR_SIZE)/2;		//在扇区内的偏移(2个字节为基本单位.)----计算在扇区内的起始地址
	//1，不跨页情况	
	secremain	=	STM_SECTOR_SIZE/2	-	secoff;		//扇区剩余空间大小
	//2，跨页情况
	if(NumToWrite	+	secoff	>	STM_SECTOR_SIZE/2)		//跨页
	{
		//......
	}	
	
	if(NumToWrite<=secremain)			//不跨页
		secremain	=	NumToWrite;			//不大于该扇区范围
	while(1)
	{	
		STM32_FLASH_Read(secpos*STM_SECTOR_SIZE+STM32_FLASH_BASE,STM32_FLASH_BUF,STM_SECTOR_SIZE/2);	//读出整个扇区的内容
		for(i=0;i<secremain;i++)		//校验数据----检查需要写入的存储空间是否为空
		{
			if(STM32_FLASH_BUF[secoff+i]	!=	0XFFFF)			//检查偏移后的地址是否为空
				break;				//需要擦除  	  
		}
		if(i<secremain)		//需要擦除----注意保存原始不应该擦除的数据
		{
			FLASH_ErasePage(secpos*STM_SECTOR_SIZE+STM32_FLASH_BASE);			//擦除这个扇区
//			for(i=0;i<secremain;i++)			//复制---将待写入数据拷贝并且保留偏移前的原始数据
//			{
//				STM32_FLASH_BUF[i+secoff]=pBuffer[i];		//未跨页+偏移前数据	  
//			}
			memcpy(&STM32_FLASH_BUF[secoff],pBuffer,secremain);			//复制数据
//			STM32_FLASH_Write_NoCheck(secpos*STM_SECTOR_SIZE+STM32_FLASH_BASE,STM32_FLASH_BUF,STM_SECTOR_SIZE/2);	//写入整个扇区
			STM32_FLASH_Write_NoCheck(secpos*STM_SECTOR_SIZE+STM32_FLASH_BASE,STM32_FLASH_BUF,STM_SECTOR_SIZE/2);	//写入整个扇区 
		}									//不需要擦除，直接写入数据
		else
			STM32_FLASH_Write_NoCheck(StartAddr,pBuffer,secremain);				//写已经擦除了的,直接写入扇区剩余区间.
		
		if(NumToWrite	==	secremain)
			break;		//写入结束了
		else				//写入未结束
		{
			secpos			++;				//扇区地址增1
			secoff			=	0;			//偏移位置为0 	 
			pBuffer			+=	secremain;  	//指针偏移
			StartAddr		+=	secremain;		//写地址偏移	   
			NumToWrite	-=	secremain;		//字节(16位)数递减
			if(NumToWrite	>	(STM_SECTOR_SIZE/2))
				secremain	=	STM_SECTOR_SIZE/2;		//下一个扇区还是写不完
			else
				secremain	=	NumToWrite;						//下一个扇区可以写完了
		}	 
	};	
	FLASH_Lock();		//上锁
}
/*******************************************************************************
*函数名			:	STM32_FLASH_Read
*功能描述		:	从指定地址开始读出指定长度的数据
*输入				: StartAddr:	起始地址
							pBuffer:		数据指针
							NumToWrite:	半字(16位)数(就是要读出的16位数据的个数.) 
*返回值			:	无
*修改时间		:	20171215
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
void STM32_FLASH_Read(u32 StartAddr,u16 *pBuffer,u16 NumToRead)		//从指定地址开始读出指定长度的数据   	
{
	u16 i;
	for(i=0;i<NumToRead;i++)
	{
		pBuffer[i]	=		STM32_FLASH_ReadHalfWord(StartAddr);//读取2个字节.
		StartAddr		+=	2;//偏移2个字节.	
	}
}


/*******************************************************************************
*函数名			:	STM32_FLASH_Erase
*功能描述		:	擦除FLASH
*输入				: StartAddr:	起始地址
							WriteData:	要写入的数据
*返回值			:	无
*修改时间		:	20171215
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
void STM32_FLASH_Erase(u32 WriteAddr,u16 NumToWrite)	//擦除FLASH
{
  u32 secpos;	   //扇区地址
	u16 secoff;	   //扇区内偏移地址(16位字计算)
	u16 secremain; //扇区内剩余地址(16位字计算)	   
 	u16 i;    
	u32 offaddr;   //去掉0X08000000后的地址
	if(WriteAddr<STM32_FLASH_BASE||(WriteAddr>=(STM32_FLASH_BASE+1024*STM32_FLASH_SIZE)))
		return;//非法地址
	
	FLASH_Unlock();						//解锁
	
	offaddr		=	WriteAddr-STM32_FLASH_BASE;		//实际偏移地址.
	secpos		=	offaddr/STM_SECTOR_SIZE;			//扇区地址  0~127 for STM32F103RBT6
	secoff		=	(offaddr%STM_SECTOR_SIZE)/2;		//在扇区内的偏移(2个字节为基本单位.)
	secremain	=	STM_SECTOR_SIZE/2-secoff;		//扇区剩余空间大小
	
	if(NumToWrite	<=	secremain)
		secremain	=	NumToWrite;//不大于该扇区范围
	
	while(1) 
	{	
		STM32_FLASH_Read(secpos*STM_SECTOR_SIZE+STM32_FLASH_BASE,STM32_FLASH_BUF,STM_SECTOR_SIZE/2);//读出整个扇区的内容
		for(i=0;i<secremain;i++)	//校验数据
		{
			if(STM32_FLASH_BUF[secoff+i]!=0XFFFF)
				break;//需要擦除  	  
		}
		if(i<secremain)//需要擦除
		{
			FLASH_ErasePage(secpos*STM_SECTOR_SIZE+STM32_FLASH_BASE);//擦除这个扇区
		}
		if(NumToWrite	==	secremain)
			break;	//写入结束了
		else			//写入未结束
		{
			secpos++;				//扇区地址增1
			secoff=0;				//偏移位置为0 	 
			WriteAddr		+=	secremain;		//写地址偏移	   
		  NumToWrite	-=	secremain;	//字节(16位)数递减
			if(NumToWrite>(STM_SECTOR_SIZE/2))
				secremain	=	STM_SECTOR_SIZE/2;	//下一个扇区还是写不完
			else
				secremain	=	NumToWrite;					//下一个扇区可以写完了
		}	 
	};	
	FLASH_Lock();//上锁
}
//============================================================================================
/*******************************************************************************
*函数名			:	Test_Write
*功能描述		:	写数据测试
*输入				: StartAddr:	起始地址
							WriteData:	要写入的数据
*返回值			:	无
*修改时间		:	20171215
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
//void Test_Write(u32 StartAddr,u16 WriteData)   	
//{
//	STM32_FLASH_Write(StartAddr,&WriteData,1);//写入一个字 
//}












