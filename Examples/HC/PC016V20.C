#ifdef PC016V20

#include "PC016V20.H"
#include "HC_PHY.H"

//#define PC016V20Test

//==============读卡命令
u8 CardReaderCmd_ReadData[14]	=
{
	0xE1,		/* F-Head 	*/			//为帧头，上位机下发时固定为0XE1，下位机应答时固定为0XD2；
	0x24, 	/* CmdType 	*/			//命令类型
	0x01,		/* Sector 	*/			//1字节扇区号
	0x01, 	/* Block 		*/			//1字节块号
	0x60, 	/* KeyType	*/			//1字节密钥模式 KEYA（0x60）/KEYB(0x61)
	0xFF,		//6字节密码
	0xFF,
	0xFF,
	0xFF,
	0xFF,
	0xFF,
	0x1C,		/* Crc16-HIGN */
	0x0D,		/* Crc16-LOW */
	0x1E 		/* F-End*/						//为帧尾，上位机下发时固定为0X1E，下位机应答时固定为0X2D；
};

//=================设置读卡器读卡区域命令	
u8 CardReaderCmd_SetArea[14] =
{
	0xE1,   /* F-Head 	*/			//为帧头，上位机下发时固定为0XE1，下位机应答时固定为0XD2；
	0x44,  	/* CmdType 	*/			//命令类型
	0x01,  	/* Sector 	*/			//扇区：0,1,其中0为只读，为卡信息
	0x01,  	/* Block 	*/				//块号：0,1,2	//产品使用1
	0x00,   /* KeyType	*/			//1字节密钥模式 KEYA（0x60）/KEYB(0x61) 00为关闭主动上传功能
	0xFF,   /* PassWord0 */			//6字节密码
	0xFF,   /* PassWord1 */
	0xFF,   /* PassWord2 */
	0xFF,		/* PassWord3 */
	0xFF,   /* PassWord4 */
	0xFF,		/* PassWord5 */
	0x9F,		/* Crc16-HIGN  	*/	//1字节扇区号
	0x6F,   /* Crc16-LOW 		*/	//1字节块号
	0x1E   	/* F-End*/					//为帧尾，上位机下发时固定为0X1E，下位机应答时固定为0X2D；
};
//=================写卡数据	
u8 CardReaderCmd_WriteData[30] =
{
	0xE1,   /* F-Head 	*/			//为帧头，上位机下发时固定为0XE1，下位机应答时固定为0XD2；
	0x25,  	/* CmdType 	*/			//命令类型
	0x01,  	/* Sector 	*/			//扇区：0,1,其中0为只读，为卡信息
	0x01,  	/* Block 	*/				//块号：0,1,2	//产品使用1
	0x60,   /* KeyType	*/			//1字节密钥模式 KEYA（0x60）/KEYB(0x61)
	0xFF,   /* PassWord0 */			//6字节密码
	0xFF,   /* PassWord1 */
	0xFF,   /* PassWord2 */
	0xFF,		/* PassWord3 */
	0xFF,   /* PassWord4 */
	0xFF,		/* PassWord5 */
	0x00,
	0x00,
	0x04,
	0x52,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x9F,		/* Crc16-HIGN  	*/	//1字节扇区号
	0x6F,   /* Crc16-LOW 		*/	//1字节块号
	0x1E   	/* F-End*/					//为帧尾，上位机下发时固定为0X1E，下位机应答时固定为0X2D；
};



sBoradDef			sBorad;					//端口/槽位所有信息结构体


//==============结体体
RS485_TypeDef	RS485_Bus;		//总线通讯485
RS485_TypeDef	RS485_Seg7;		//数码管显示485
SWITCHID_CONF	SWITCHID;			//拔码开关


u8 RS485BusTxd[Bus485BufferSize];


u8 Seg485Rxd[Seg485BufferSize]	=	{0};


//==============其它变量

u8 SwitchData	=	0;				//存储拔码开关最新地址，如果地址变化，再重新配置运行参数


//=================================================================================================================主程序


/*******************************************************************************
* 函数名		:	
* 功能描述	:	 
* 输入		:	
* 输出		:
* 返回 		:
*******************************************************************************/
void PC016V20_Configuration(void)
{
	u8 Num	=	0;
	//========================系统时钟初始化
	SYS_Configuration();							//系统配置---打开系统时钟 STM32_SYS.H	
	
	//========================延时1秒，等待上电稳定
	SysTick_DeleymS(50);					//SysTick延时nmS
	
	//========================硬件初始化
	Data_Initialize();								//标准参数初始化
	
	Lock_Configuration();							//锁初始化
	Switch_Configuration();						//拔码开关初始化及读数
	RS485_Configuration();						//RS485配置
	CardReader_Configuration();				//读卡器配置
	

	//========================运行指示灯初始化：频率1秒，占空比500/1000
	PWM_OUT(TIM2,PWM_OUTChannel1,1,500);

	//========================清除数码管显示
	
	BoardSegClear(&sBorad);				//清除数码管显示
	
	SysTick_DeleymS(100);					//SysTick延时nmS
	
	//========================设置读卡扇区、块号、KEYA/KEYB、读卡密码0x44
	//---命令：0x44
	//---扇区1
	//---块号1
	//---密码：0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
	CardReaderCmd_SetArea[4]	=	0x00;
	USART_DMASend	(ICCardReadPort1,(u32*)CardReaderCmd_SetArea,14);	//设置读头读卡扇区、块号、KEYA/KEYB、读卡密码0x44
	USART_DMASend	(ICCardReadPort2,(u32*)CardReaderCmd_SetArea,14);	//设置读头读卡扇区、块号、KEYA/KEYB、读卡密码0x44
	USART_DMASend	(ICCardReadPort3,(u32*)CardReaderCmd_SetArea,14);	//设置读头读卡扇区、块号、KEYA/KEYB、读卡密码0x44
	USART_Send		(ICCardReadPort4,(u8*)CardReaderCmd_SetArea,14);	//设置读头读卡扇区、块号、KEYA/KEYB、读卡密码0x44
	SysTick_DeleymS(100);					//SysTick延时nmS
	//========================上电读卡
	
	USART_DMASend	(ICCardReadPort1,(u32*)CardReaderCmd_ReadData,14);	//串口DMA发送程序

	USART_DMASend	(ICCardReadPort2,(u32*)CardReaderCmd_ReadData,14);	//串口DMA发送程序

	USART_DMASend	(ICCardReadPort3,(u32*)CardReaderCmd_ReadData,14);	//串口DMA发送程序

	USART_Send		(ICCardReadPort4,(u8*)CardReaderCmd_ReadData,14);			//串口5发送程序
	
	SysTick_DeleymS(100);					//SysTick延时nmS
	//写卡
	USART_DMASend	(ICCardReadPort1,(u32*)CardReaderCmd_WriteData,sizeof(CardReaderCmd_WriteData));	//串口DMA发送程序
		

	//========================SysTick初始化：用作周期扫描PC016V20_Server
	SysTick_Configuration(1000);	//系统嘀嗒时钟配置72MHz,单位为uS
	
	sBorad.sPlu.PowerUpFlag		=	0;		//上电标志，0未上电完，1上电完
	sBorad.sPlu.Time.TimeSYS	=	0;
	
	//========================独立看门狗初始化：1秒	
	IWDG_Configuration(1000);					//独立看门狗配置---参数单位ms
}
/*******************************************************************************
* 函数名		:	PC016V20_Server
* 功能描述	:	1ms扫描周期 
* 输入		:	
* 输出		:
* 返回 		:
*******************************************************************************/
void PC016V20_Server(void)
{
	u8	Num	=	0;
	
	Num	=	Uart5ReceiveData(&sBorad);			//串口5读数据
	
	if(Num)
	{
		return;
	}
	
	IWDG_Feed();						//独立看门狗喂狗

	//==================================消息处理
	MessageServer(&sBorad);				//外部总线消息处理		MessageProcess(&sFarmeTxd,&sBorad);				//外部总线消息处理
	//==================================板内处理程序
	BoardServer(&sBorad);					//板内：锁控制，药箱，数码管
	//==================================读卡器
	CardReaderServer(&sBorad);		//读卡器

	//========================计数器
	sBorad.sPlu.Time.TimeSYS++;
	
	if(sBorad.sPlu.Time.TimeSYS>=5000)
	{
		sBorad.sPlu.Time.TimeSYS		=	0;		//系统计时器
		sBorad.sPlu.Time.TimeBUS		=	0;		//外部总线时间
		sBorad.sPlu.PowerUpFlag		=	1;		//上电标志，0未上电完，1上电完
	}
	if(sBorad.sPlu.Time.TimeCard++	>=1000)
	{
		sBorad.sPlu.Time.TimeCard	=	0;
	}

}

//======




//=================================================================================================================协议程序


/*******************************************************************************
*函数名			:	function
*功能描述		:	function
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
void MessageServer(sBoradDef*	sBorad)				//外部总线消息处理
{
	u16 Num	=	0;
	//=====================================检查外部总线是否有命令
	Num	=	RS485_ReadBufferIDLE(&RS485_Bus,(u32*)&(sBorad->sPlu.BusData.sFarmeRev),(u32*)&(sBorad->sPlu.BusData.sFarmeRxd));	//串口空闲模式读串口接收缓冲区，如果有数据，将数据拷贝到RevBuffer,并返回接收到的数据个数，然后重新将接收缓冲区地址指向RxdBuffer
	if(Num)			//只要总线有消息传输就清零计时，以免数据回复时总线冲突
	{
		sBorad->sPlu.Time.TimeBUS	=	0;				//清零，以免数据回复时总线冲突
	}
	if((Num)&&((sBorad->sPlu.BusData.sFarmeRev.Head)==0x7E)&&((sBorad->sPlu.BusData.sFarmeRev.Addr.Addr3)<=MaxPortNum)&&(((sBorad->sPlu.BusData.sFarmeRev.Addr.Addr2) ==SwitchData)||((sBorad->sPlu.BusData.sFarmeRev.Addr.Addr2) ==SwitchData-1)))					//本层指令(本层分上层和下层，取药或者加药时，指令对上下层都有效，取药或者加药时结果上报，消息对上层也有效）
	{		
		sMs485FrmDef* sFarme=&(sBorad->sPlu.BusData.sFarmeRev);			//获取缓存指针		
		MessageAnalysis(sBorad);							//解析消息（重新按协议包装数据）
		if(sFarme->Addr.Addr2 ==SwitchData)					//本层消息
		{
			if(sFarme->Cmd==CGetID)							//获取ID指令处理（0x12指令）
			{
				MessageAck(sBorad);								//外部总线应答
				MessageGetID(sBorad);							//获取ID指令处理（0x12指令）
			}
			else if(sFarme->Cmd==CGetBox)
			{
				MessageAck(sBorad);								//外部总线应答
				MessageGetBox(sBorad);						//取药箱消息处理---设置相关标志（0x13指令，0x13指令上报(0x93))
			}
		}
		else if(sFarme->Addr.Addr2 ==SwitchData-1)	//非本层消息（取药箱，取药箱状态上报）----与锁控制相关
		{
			MessageLock(sBorad);								//锁相关消息处理（0x13指令，0x13指令上报(0x93))
		}
//		sBorad->sPlu.Time.TimeBUS	=	0;				//清零，以免数据回复时总线冲突
	}		
	//=====================================处理上报消息
	else
	{
		MessageSend(sBorad);			//发送消息/消息上报
	}
}
/*******************************************************************************
*函数名			:	function
*功能描述		:	function
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	
*******************************************************************************/
void MessageAnalysis(sBoradDef*	sBorad)				//解析消息
{
	sMs485FrmDef* sFarme=&(sBorad->sPlu.BusData.sFarmeRev);			//获取缓存指针
	
	if(sFarme->Length==FixedAddrLenth)							//数据长度为FixedAddrLenth表示无数据//固定数据长度nLength中地址和状态码的长度
	{
		sFarme->Bcc8	=	sFarme->data[0];
		sFarme->End		=	(ePro485UsDef)sFarme->data[1];
	}
	else																						//带数据长度
	{
		sFarme->Bcc8	=	sFarme->data[sFarme->Length-FixedAddrLenth];
		sFarme->End		=	(ePro485UsDef)sFarme->data[sFarme->Length-FixedAddrLenth+1];
	}
}
/*******************************************************************************
*函数名			:	function
*功能描述		:	function
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	
*******************************************************************************/
void MessageAck(sBoradDef*	sBorad)			//外部总线应答
{
	u8 Temp	=	0;
	u8 Temp1	=	0;
	sMs485FrmDef* sFarme=&(sBorad->sPlu.BusData.sFarmeRev);			//获取缓存指针	
//	sBorad->sPlu.Time.TimeBUS	=	0;				//清零，以免数据回复时总线冲突
	
	RS485BusTxd[0]	=	0x7E;
	RS485BusTxd[1]	=	sFarme->sAdd;
	RS485BusTxd[2]	=	sFarme->dAdd;
	RS485BusTxd[3]	=	sFarme->nSerial;
	RS485BusTxd[4]	=	sFarme->Cmd;
	RS485BusTxd[5]	=	sFarme->Ucode;
	RS485BusTxd[6]	=	0x00;								//错误码
//	RS485BusTxd[7]	=	BCC8((u8*)&RS485BusTxd[1],6);		//8位数异或校验码：地址段+异常码+数据段校验
	RS485BusTxd[8]	=	0x7F;
	for(Temp=1;Temp<6;Temp++)
	{
		Temp1=Temp1^RS485BusTxd[Temp];
	}
	RS485BusTxd[7]	=	Temp1;
	
	RS485_DMASend(&RS485_Bus,(u32*)RS485BusTxd,9);	//RS485-DMA发送程序
}
/*******************************************************************************
*函数名			:	function
*功能描述		:	function
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	
*******************************************************************************/
void MessageGetID(sBoradDef*	sBorad)				//解析消息
{
	u32	Time;						//点亮时间，单位mS
	u8 Num	=	0;
	PortDef*	Port	=	&(sBorad->Port1);
	sMs485FrmDef* sFarme=&(sBorad->sPlu.BusData.sFarmeRev);			//获取缓存指针
	//================保存标识
	for(Num=0;Num<MaxPortNum;Num++)
	{
		if(sFarme->Addr.Addr3	==	Num+1)			//端口地址
		{
			//=====================总线待处理标志
			Port->sBus.BusqSts.BusFlg		=	1;	//bit0：0-无操作,	1-有待处理事件(上报数据或者状态）
			Port->sBus.BusqSts.GetID		=	1;	//bit1：0-无请求，	1-有请求	，获取ID请求需要上报ID
			Port->sBus.BusqSts.GetBox		=	0;	//bit2：0-无请求，	1-有请求	，取药(数码管数值同时闪烁)
			Port->sBus.BusqSts.GotBox		=	0;	//bit3：0-无操作，	1-药箱已被取走
			Port->sBus.BusqSts.TakeBox	=	0;	//bit4：0-无操作，	1-药箱被强制取
			Port->sBus.BusqSts.BoxBack	=	0;	//bit5：0-无操作，	1-药箱收回,收回后需要上报药箱号（有GotBox标志时设置此位）
			Port->sBus.BusqSts.TimeOut	=	0;	//bit6：0-无操作，	1-取药超时
			
			Port->sBus.Ucode	=	sFarme->Ucode;	//b5用户码：不处理，原样返回
			
			//=====================读卡器：检查药箱有无取出---高频读卡
		
			//========数码管：每次获取ID指令就点亮数码管 30秒
			Port->Seg.sSegSts.SegFlg	=	1;	//bit0：0-无操作,	1-有操作请求(需要更新数码管状态）
			Port->Seg.SegFarme.cmd.DispEnNum	=	1;	//bit0显示数值	：	0-不显示，		1-显示
			Port->Seg.SegFarme.cmd.DispEnDp		=	0;	//bit1显示点		：	0-不显示，		1-显示
			Port->Seg.SegFarme.cmd.DispMdNum	=	0;	//bit2数值模式	：	0-静态显示，	1-0.5S闪烁
			Port->Seg.SegFarme.cmd.DispMdDp		=	0;	//bit3点模式		：	0-静态显示，	1-0.5S闪烁
			Port->Seg.SegFarme.cmd.DispTime		=	1;	//bit4显示时间	：	0-长亮，			1-在显示时间内根据显示模式显示			
			
			//数码管亮时间
			if((Port->sReader.ReaderSts.ReadErr	==1)||(Port->sReader.ReaderSts.NoCard	==1))
			{
				u32 time	=	LockOffTime;		//药箱取走后锁释放时间5S
				memcpy(&(Port->Seg.SegFarme.data[4]),&time,4);
				Port->Seg.SyncTime	=	time;
			}
			else
			{
				Time	=	15000;				//15000ms
				//数码管亮时间
				memcpy(&(Port->Seg.SegFarme.data[4]),&Time,4);
			}

			break;			//退出For
		}
		
		if(Num<MaxPortNum-1)
		{
			Port=(PortDef*)((u32)Port+sizeof(PortDef));			//指向下一端口
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
*注释				:	
*******************************************************************************/
void MessageGetBox(sBoradDef*	sBorad)			//取药箱消息处理---设置相关标志（0x13指令，0x13指令上报(0x93))
{
	u8 Num	=	0;
	PortDef*	Port	=	&(sBorad->Port1);
	sMs485FrmDef* sFarme=&(sBorad->sPlu.BusData.sFarmeRev);			//获取缓存指针
	//================保存标识
	for(Num=0;Num<MaxPortNum;Num++)
	{
		if(sFarme->Addr.Addr3	==	Num+1)			//端口地址
		{
			//=====================总线待处理标志
			Port->sBus.BusqSts.BusFlg		=	1;	//bit0：0-无操作,	1-有待处理事件(上报数据或者状态）
			Port->sBus.BusqSts.GetID		=	0;	//bit1：0-无请求，	1-有请求	，获取ID请求需要上报ID
			Port->sBus.BusqSts.GetBox		=	1;	//bit2：0-无请求，	1-有请求	，取药(数码管数值同时闪烁)
			Port->sBus.BusqSts.GotBox		=	0;	//bit3：0-无操作，	1-药箱已被取走
			Port->sBus.BusqSts.TakeBox	=	0;	//bit4：0-无操作，	1-药箱被强制取
			Port->sBus.BusqSts.BoxBack	=	0;	//bit5：0-无操作，	1-药箱收回,收回后需要上报药箱号（有GotBox标志时设置此位）
			Port->sBus.BusqSts.TimeOut	=	0;	//bit6：0-无操作，	1-取药超时
			
			Port->sBus.Ucode	=	sFarme->Ucode;	//b5用户码：不处理，原样返回
			//========数码管：每次获取ID指令就点亮数码管 30秒
			
			Port->Seg.sSegSts.SegFlg	=	1;	//bit0：0-无操作,	1-有操作请求(需要更新数码管状态）
			Port->Seg.SegFarme.cmd.DispEnNum	=	1;	//bit0显示数值	：	0-不显示，		1-显示
			Port->Seg.SegFarme.cmd.DispEnDp		=	0;	//bit1显示点		：	0-不显示，		1-显示
			Port->Seg.SegFarme.cmd.DispMdNum	=	1;	//bit2数值模式	：	0-静态显示，	1-0.5S闪烁
			Port->Seg.SegFarme.cmd.DispMdDp		=	0;	//bit3点模式		：	0-静态显示，	1-0.5S闪烁
			Port->Seg.SegFarme.cmd.DispTime		=	1;	//bit4显示时间	：	0-长亮，			1-在显示时间内根据显示模式显示
				
				//=======================取药倒计时时间
			if(Port->sReader.ReaderSts.ReadErr	!= 1)
			{
				if(sFarme->Length<5)		//未配置时间
				{
					Port->sBus.GetBoxTimeCountdown	=	DefaultOnTime;		//默认取药时间
				}
				else
				{
					if(sFarme->data[0]>(MaxOnTime/1000))			//锁吸合最大时间120S	2分钟
					{
						Port->sBus.GetBoxTimeCountdown	=	MaxOnTime;
					}
					else if(sFarme->data[0]<(MinOnTime/1000))	//锁吸合最小时间10S
					{
						Port->sBus.GetBoxTimeCountdown	=	MinOnTime;
					}
					else
					{
						Port->sBus.GetBoxTimeCountdown	=	sFarme->data[0]*1000;	//其它时间
					}
				}
			}
			else
			{
				Port->sBus.GetBoxTimeCountdown	=	15000;		//15秒吸合时间
			}
			
				//数码管亮时间
				if((Port->sReader.ReaderSts.ReadErr	==1)||(Port->sReader.ReaderSts.NoCard	==1))
				{
					u32 time	=	LockOffTime;		//药箱取走后锁释放时间5S
					memcpy(&(Port->Seg.SegFarme.data[4]),&time,4);
					Port->Seg.SyncTime	=	time;
				}
				else
				{
					memcpy(&(Port->Seg.SegFarme.data[4]),&(Port->sBus.GetBoxTimeCountdown),4);
				}

			break;			//退出For
		}
		if(Num<MaxPortNum-1)
		{
			Port=(PortDef*)((u32)Port+sizeof(PortDef));			//指向下一端口
		}		
	}
	memset((u8*)sFarme,0x00,BusDataSize);
}
/*******************************************************************************
*函数名			:	function
*功能描述		:	function
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	
*******************************************************************************/
void MessageLock(sBoradDef*	sBorad)				//解析消息
{
	u8 Num	=	0;
	PortDef*	Port	=	&(sBorad->Port1);
	sMs485FrmDef* sFarme=&(sBorad->sPlu.BusData.sFarmeRev);			//获取缓存指针
	//================保存标识
	for(Num=0;Num<MaxPortNum;Num++)
	{
		if(sFarme->Addr.Addr3	==	Num+1)			//端口地址
		{
			if(sFarme->Cmd	==	CGetBox)		//取药箱命令---需要开锁（设置开锁时间）
			{		
				//=======================取药倒计时时间
				if(sFarme->Length<5)		//未配置时间
				{
					Port->Lock.LockTimeCountdown	=	DefaultOnTime-500;		//默认取药时间---需要提前释放锁
				}
				else
				{
					if(sFarme->data[0]>(MaxOnTime/1000))			//锁吸合最大时间120S	2分钟
					{
						Port->Lock.LockTimeCountdown	=	MaxOnTime-500;
					}
					else if(sFarme->data[0]<(MinOnTime/1000))	//锁吸合最小时间10S
					{
						Port->Lock.LockTimeCountdown	=	MinOnTime-500;
					}
					else
					{
						Port->Lock.LockTimeCountdown	=	sFarme->data[0]*1000-500;	//其它时间
					}
				}
				Port->Lock.LockTimeCountdown		=	Port->Lock.LockTimeCountdown		-	1000;		//需要在取药箱超时前释放锁
			}
			else if(sFarme->Cmd==AGetBox)			//取药箱状态上报：如果开锁时间不为0，则等待5秒后释放锁
			{
				if((Port->Lock.LockTimeCountdown>0)&&((sFarme->StsCode==eNoData)||(sFarme->StsCode==eBoxOff)||(sFarme->StsCode==eReadErr)))
				{
					Port->Lock.LockTimeCountdown	=	LockOffTime;		//药箱取走后锁释放时间5S
				}
			}
			
			//break;			//退出For
			return;
		}

		if(Num<MaxPortNum-1)
		{
			Port=(PortDef*)((u32)Port+sizeof(PortDef));			//指向下一端口
		}		
	}
}
/*******************************************************************************
*函数名			:	function
*功能描述		:	插入药盒上报ID，获取ID上报ID，取药上报状态（已取，超时）
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	
*******************************************************************************/
void MessageSend(sBoradDef*	sBorad)			//发送消息/消息上报
{
	u8	Flag	=	0;				//0-无需上报，1-需要上报
	u8 	Num		=	0;
	u8 	Temp	=	0;
	u8 	Temp1	=	0;
	PortDef*	Port	=	&(sBorad->Port1);
	
	sBorad->sPlu.Time.TimeBUS	++;								//外部总线时间	
	if(((sBorad->sPlu.Time.TimeBUS)%50)	==	0)	//50ms发送一个帧
	{		
		sBorad->sPlu.Time.TimeBUS	=	0;
		for(Num=0;Num<MaxPortNum;Num++)
		{
			if(Port->sBus.BusqSts.BusFlg	==	1)	//bit0：0-无操作,	1-有待处理事件(上报数据或者状态）
			{
				//=====================================上报ID
				Flag	=	1;			//0-无需上报，1-需要上报
				Port->sBus.BusqSts.BusFlg	=	0;			//bit0：0-无操作,	1-有待处理事件(上报数据或者状态）
				if(Port->sBus.BusqSts.GetID	==1)		//bit1：0-无请求，	1-有请求	，获取ID请求需要上报ID
				{
					Port->sBus.sBusFarme.Ucode	=	Port->sBus.Ucode;			//数据帧到达底层后，回复的数据帧总是将其按原值返回。若数据帧是底层设备自主发出，则用户码设为0，因此规定工控主机不能将下行数据帧的用户码设为0。
					Port->sBus.sBusFarme.Cmd		=	AGetID;					//上位机主动获取ID请求应答命令
					
					//-------------------------------------读卡器坏
					if(Port->sReader.ReaderSts.ReadErr	==1)			//bit3：0-读卡器正常，	1-读卡器通讯异常
					{
//						Port->sReader.ReaderSts.ReadErr	=	0;				//需要重获取读卡器状态再新更新数码管
						Port->sBus.sBusFarme.StsCode	=	eReadErr;						//读卡器通讯异常
						Port->sBus.sBusFarme.Length	=	FixedAddrLenth;
					}
					//-------------------------------------无药箱
					else if(Port->sReader.ReaderSts.ReadID	==0)	//bit2：0-无操作,			1-读到ID(需要增加相关数据及标志)
					{
						Port->sBus.sBusFarme.StsCode	=	eNoData;						//无药箱数据
						Port->sBus.sBusFarme.Length	=	FixedAddrLenth;
					}
					//-------------------------------------无错误（上报ID号）
					else
					{
						Port->sBus.sBusFarme.StsCode	=	eNoErr;							//无错误
						Port->sBus.sBusFarme.Length	=	FixedAddrLenth+FixedDataLenth;
					}
					break;			//退出For，准备上传数据					
				}
				//=====================================取药箱
				else if(Port->sBus.BusqSts.GetBox	==1)	//bit2：0-无请求，	1-有请求	，取药(数码管数值同时闪烁)
				{
					Port->sBus.sBusFarme.Ucode		=	Port->sBus.Ucode;		//数据帧到达底层后，回复的数据帧总是将其按原值返回。若数据帧是底层设备自主发出，则用户码设为0，因此规定工控主机不能将下行数据帧的用户码设为0。
					Port->sBus.sBusFarme.Cmd			=	AGetBox;						//取药命令上报						
					Port->sBus.sBusFarme.Length		=	FixedAddrLenth;			//b6地址+异常码固定长度为4，卡数据长度为3	
					
					//-------------------------------------读卡器坏
					if(Port->sReader.ReaderSts.ReadErr==1)		//bit3：0-读卡器正常，	1-读卡器通讯异常
					{
//						Port->sReader.ReaderSts.ReadErr	=	0;						//需要重获取读卡器状态再新更新数码管
						Port->sBus.sBusFarme.StsCode	=	eReadErr;				//读卡器通讯异常
						break;			//退出For，准备上传数据
					}
					//-------------------------------------无药箱/无数据
					else if(Port->sReader.ReaderSts.ReadID==0)
					{
						Port->sBus.sBusFarme.StsCode	=	eNoData;						//无药箱数据
						break;			//退出For，准备上传数据
					}
					else
					{
						Flag	=	0;	//0-无需上报，1-需要上报
					}					
				}
				//=====================================药箱取走
				else if(Port->sBus.BusqSts.GotBox	==1)	//bit3：0-无操作，	1-药箱已被取走
				{
					Port->sBus.sBusFarme.Ucode			=	Port->sBus.Ucode;			//数据帧到达底层后，回复的数据帧总是将其按原值返回。若数据帧是底层设备自主发出，则用户码设为0，因此规定工控主机不能将下行数据帧的用户码设为0。
					Port->sBus.sBusFarme.Cmd				=	AGetBox;							//下位机主动上传ID号命令
					Port->sBus.sBusFarme.StsCode		=	eBoxOff;							//药箱取走
					Port->sBus.sBusFarme.Length			=	FixedAddrLenth;				//b6地址+异常码固定长度为4，卡数据长度为3
					break;
				}
				//=====================================取药箱超时
				else if(Port->sBus.BusqSts.TimeOut	==1)	//bit6：0-无操作，	1-取药超时(只上传状态，不上传卡号）
				{
					Port->sBus.sBusFarme.Ucode		=	Port->sBus.Ucode;	//数据帧到达底层后，回复的数据帧总是将其按原值返回。若数据帧是底层设备自主发出，则用户码设为0，因此规定工控主机不能将下行数据帧的用户码设为0。
					Port->sBus.sBusFarme.Cmd			=	ALock;				//下位机主动上传ID号命令
					Port->sBus.sBusFarme.StsCode	=	eBoxTout;			//药箱收回
					Port->sBus.sBusFarme.Length		=	FixedAddrLenth;		//不带卡号上传
					break;
				}
				//=====================================药箱收回（包括新药箱插入和取走药箱收回）
				else if(Port->sBus.BusqSts.BoxBack	==1)		//bit5：0-无操作，	1-药箱收回
				{
					Port->sBus.sBusFarme.Ucode			=	0x00;						//数据帧到达底层后，回复的数据帧总是将其按原值返回。若数据帧是底层设备自主发出，则用户码设为0，因此规定工控主机不能将下行数据帧的用户码设为0。
					Port->sBus.sBusFarme.Cmd				=	ASendID;				//下位机主动上传ID号命令
					Port->sBus.sBusFarme.StsCode		=	eBoxBack;				//药箱收回
					Port->sBus.sBusFarme.Length			=	FixedAddrLenth+FixedDataLenth;		//b6地址+异常码固定长度为4，卡数据长度为3
					break;
				}
				//=====================================药箱丢失（强制取走）
				else if(Port->sBus.BusqSts.TakeBox	==1)	//bit4：0-无操作，	1-药箱被强制取
				{
					Port->sBus.sBusFarme.Ucode			=	0x00;							//数据帧到达底层后，回复的数据帧总是将其按原值返回。若数据帧是底层设备自主发出，则用户码设为0，因此规定工控主机不能将下行数据帧的用户码设为0。
					Port->sBus.sBusFarme.Cmd				=	AGetBox;						//下位机主动上传ID号命令
					Port->sBus.sBusFarme.StsCode		=	eBoxOff;					//药箱被强制取走
					Port->sBus.sBusFarme.Length			=	FixedAddrLenth;		//b6地址+异常码固定长度为4，卡数据长度为3
					break;
				}
				else
				{
					Flag	=	0;
				}
			}
			//=====================================检查下一端口
			if(Num<MaxPortNum-1)
			{
				Port=(PortDef*)((u32)Port+sizeof(PortDef));			//指向下一端口
			}
		}		
	}
	else
	{
		return;
	}
	if(Flag	==0)		//0-无需上报，1-需要上报
	{
		return;	//退出，不往下执行
	}
//	else			//清除所有标志
//	{
//		Port->sBus.BusqSts.GetID		=	0;		//bit1：0-无请求，	1-有请求	，获取ID请求需要上报ID	
//		Port->sBus.BusqSts.GetBox		=	0;		//bit2：0-无请求，	1-有请求	，取药(数码管数值同时闪烁)
//		Port->sBus.BusqSts.GotBox		=	0;		//bit3：0-无操作，	1-药箱已被取走
//		Port->sBus.BusqSts.TakeBox	=	0;		//bit4：0-无操作，	1-药箱被强制取
//		Port->sBus.BusqSts.BoxBack	=	0;		//bit5：0-无操作，1-药箱收回,收回后需要上报药箱号（有GotBox标志时设置此位）
//		Port->sBus.BusqSts.TimeOut	=	0;		//bit6：0-无操作，	1-取药超时
//	}
	
	Port->sBus.sBusFarme.Head			=	ePro485Head;			//头标识
	Port->sBus.sBusFarme.dAdd			=	0x00;							//b1目标地址（暂时理解为单元柜地址）下发为接收地址，上传为0x00
	Port->sBus.sBusFarme.sAdd			=	SwitchData;				//b2源地址 下发为0x00，上传为本地址
	Port->sBus.sBusFarme.nSerial	=	0x00;							//流水号:不能用7F 7E帧头帧尾会冲突
	
	Port->sBus.sBusFarme.Addr.Addr1	=	0x00;						//柜地址(单元柜号)  下行时为柜地址，上行时，柜地址为0x00）
	Port->sBus.sBusFarme.Addr.Addr2	=	SwitchData;			//层地址
	Port->sBus.sBusFarme.Addr.Addr3	=	Port->PortNum;	//槽地址（端口号）
	//=======卡号
	memcpy((Port->sBus.sBusFarme.data),(Port->sBus.CardData),3);
	
	memcpy(RS485BusTxd,(u8*)&(Port->sBus.sBusFarme),14);
	//=======计算校验
	for(Temp=1;Temp<7+(Port->sBus.sBusFarme.Length);Temp++)
	{
		Temp1=Temp1^RS485BusTxd[Temp];
	}
	Port->sBus.sBusFarme.Bcc8	=	Temp1;

	Port->sBus.sBusFarme.End		=	ePro485End;			//结束标识

	if(Port->sBus.sBusFarme.Length>4)
	{
		RS485BusTxd[14]	=	Port->sBus.sBusFarme.Bcc8;
		RS485BusTxd[15]	=	Port->sBus.sBusFarme.End;
	}
	else
	{
		RS485BusTxd[11]	=	Port->sBus.sBusFarme.Bcc8;
		RS485BusTxd[12]	=	Port->sBus.sBusFarme.End;
	}
	RS485_DMASend(&RS485_Bus,(u32*)RS485BusTxd,6+RS485BusTxd[6]+3);	//RS485-DMA发送程序
}
//======

//=================================================================================================================药箱
/*******************************************************************************
* 函数名			:	function
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: 
*******************************************************************************/
void BoardServer(sBoradDef*	sBorad)							
{
	//=====================================
	BoardLockServer(sBorad);							//锁开关处理
	//=====================================
	BoardBoxServer(sBorad);								//药箱处理程序
	//=====================================
	BoardSegServer(sBorad);								//数码管
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
void BoardLockServer(sBoradDef*	sBorad)							//锁开关处理
{
	//===============================================================取药
	u8 Num	=	0;
	PortDef*	Port	=	&(sBorad->Port1);
	for(Num=0;Num<MaxPortNum;Num++)								//循环扫描各端口
	{
		if(Port->Lock.LockTimeCountdown>0)					//锁吸合时间，最大值0x3FFF FFFF
		{
			Port->Lock.LockTimeCountdown-=1;					//锁吸合时间，最大值0x3FFF FFFF---倒计时
			Port->Lock.GPIOx->BSRR = Port->Lock.GPIO_Pin_n;		//GPIO_SetBits(Port->Lock.GPIOx,	Port->Lock.GPIO_Pin_n);			//开锁
		}
		else
		{
			Port->Lock.GPIOx->BRR = Port->Lock.GPIO_Pin_n;		//GPIO_ResetBits(Port->Lock.GPIOx,	Port->Lock.GPIO_Pin_n);			//释放锁
		}		
		//-----------------------------------指向下一端口
		if(Num<MaxPortNum-1)
		{
			Port=(PortDef*)((u32)Port+sizeof(PortDef));				
		}
	}	
}
/*******************************************************************************
* 函数名			:	function
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: 
*******************************************************************************/
void BoardBoxServer(sBoradDef*	sBorad)				//药箱处理程序
{
	//===============================================================取药
	u8 Num	=	0;
	PortDef*	Port	=	&(sBorad->Port1);
	for(Num=0;Num<MaxPortNum;Num++)							//循环扫描各端口
	{
		if(Port->sBus.GetBoxTimeCountdown>0)
		{
			Port->sBus.GetBoxTimeCountdown-=1;
		}
		if((Port->sBus.GetBoxTimeCountdown ==0)&&(Port->sReader.ReaderSts.ReadErr ==0))
		{
			if(Port->sBus.BusqSts.GetBox	==	1)		//bit2：0-无请求，	1-有请求	，取药(数码管数值同时闪烁)
			{
				Port->sBus.BusqSts.BusFlg		=	1;		//bit0：0-无操作,	1-有待处理事件(上报数据或者状态）
				Port->sBus.BusqSts.GetID		=	0;		//bit1：0-无请求，	1-有请求	，获取ID请求需要上报ID
				Port->sBus.BusqSts.GetBox		=	0;		//bit2：0-无请求，	1-有请求	，取药(数码管数值同时闪烁)
				Port->sBus.BusqSts.GotBox		=	0;		//bit3：0-无操作，	1-药箱已被取走
				Port->sBus.BusqSts.TakeBox	=	0;		//bit4：0-无操作，	1-药箱被强制取
				Port->sBus.BusqSts.BoxBack	=	0;		//bit5：0-无操作，	1-药箱收回,收回后需要上报药箱号（有GotBox标志时设置此位）
				Port->sBus.BusqSts.TimeOut	=	1;		//bit6：0-无操作，	1-取药超时
			}
		}		
		//-----------------------------------指向下一端口
		if(Num<MaxPortNum-1)
		{
			Port=(PortDef*)((u32)Port+sizeof(PortDef));				
		}
	}
}

//=================================================================================================================数码管控制程序
/*******************************************************************************
* 函数名			:	function
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: 
*******************************************************************************/
void BoardSegServer(sBoradDef*	sBorad)				//数码管
{
	u8 Num	=	0;
	PortDef*	Port	=	&(sBorad->Port1);
	//=====================================检查有无更新数码管
	if(((sBorad->sPlu.Time.TimeCard)%1000<100)&&((sBorad->sPlu.Time.TimeCard)%1000>0))		//前100ms读数据CardReaderRead，后100ms发送读卡请求
	{
		if((sBorad->sPlu.Time.TimeCard)%1000==10)		//前100ms读数据CardReaderRead，后100ms发送读卡请求
		{	
			HALUsartRemapEnable();											//使能串口复用
		}
		else if(sBorad->sPlu.Time.TimeCard%20 ==0)		//数码管更新数据计时器----可用于检测数码管通讯状态 20ms外发一个数码管状态
		{
			for(Num=0;Num<MaxPortNum;Num++)					//循环扫描各端口
			{
				if(Port->Seg.sSegSts.SegFlg	==	1)		//bit0：0-无操作,		1-有操作请求(需要更新数码管状态）
				{
					HALSendSeg((u32*)&(Port->Seg.SegFarme),sizeof(sSegFarmeDef));		//向数码管发送数据
					Port->Seg.sSegSts.SegFlg	=	0;			//bit0：0-无操作,		1-有操作请求(需要更新数码管状态）
					return;															//退出，不继续执行
				}		
				//-----------------------------------指向下一端口
				if(Num<MaxPortNum-1)
				{
					Port=(PortDef*)((u32)Port+sizeof(PortDef));				
				}
			}
		}
		else if(sBorad->sPlu.Time.TimeCard	==90)
		{
			//=====================================禁用串口复用
			HALUsartRemapDisable();								//关闭串口复用
		}
	}
	
	Port	=	&(sBorad->Port1);
	for(Num=0;Num<MaxPortNum;Num++)					//循环扫描各端口
	{
		if(Port->Seg.SyncTime>0)
		{
			Port->Seg.SyncTime-=1;
			if(Port->Seg.SyncTime==0)
			{
				Port->Seg.sSegSts.Sync	=	1;		//bit1：0-无操作,		1-更新
			}
		}
		//-----------------------------------指向下一端口
		if(Num<MaxPortNum-1)
		{
			Port=(PortDef*)((u32)Port+sizeof(PortDef));				
		}
	}
}
/*******************************************************************************
* 函数名			:	function
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: 
*******************************************************************************/
void BoardSegClear(sBoradDef*	sBorad)				//清除数码管显示
{
	u8 Num	=	0;
	PortDef*	Port	=	&(sBorad->Port1);
	//=====================================检查有无更新数码管
	for(Num=0;Num<MaxPortNum;Num++)					//循环扫描各端口
	{
		SysTick_DeleymS(20);					//SysTick延时nmS
		Port->Seg.SegFarme.cmd.DispEnNum	=	0;	//bit0显示数值	：	0-不显示，		1-显示
		Port->Seg.SegFarme.cmd.DispEnDp		=	0;	//bit1显示点		：	0-不显示，		1-显示
		Port->Seg.SegFarme.cmd.DispMdNum	=	0;	//bit2数值模式	：	0-静态显示，	1-0.5S闪烁
		Port->Seg.SegFarme.cmd.DispMdDp		=	0;	//bit3点模式		：	0-静态显示，	1-0.5S闪烁
		Port->Seg.SegFarme.cmd.DispTime		=	0;	//bit4显示时间	：	0-长亮，			1-在显示时间内根据显示模式显示
		
		memset((Port->Seg.SegFarme.data),0x00,4);		//清除数据
		
		HALSendSeg((u32*)&(Port->Seg.SegFarme),sizeof(sSegFarmeDef));		//向数码管发送数据
		
		Port->Seg.sSegSts.SegFlg	=	0;			//bit0：0-无操作,		1-有操作请求(需要更新数码管状态）
		//-----------------------------------指向下一端口
		if(Num<MaxPortNum-1)
		{
			Port=(PortDef*)((u32)Port+sizeof(PortDef));				
		}
	}
	SysTick_DeleymS(20);					//SysTick延时nmS
	//=====================================禁用串口复用
	HALUsartRemapDisable();								//关闭串口复用
}
/*******************************************************************************
*函数名			:	function
*功能描述		:	function
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	
*******************************************************************************/
void CardReaderServer(sBoradDef*	sBorad)
{
	CardReaderRead(sBorad);					//检查读卡器有无收到数据
	CardReaderReadCmd(sBorad);			//读卡指令---发送主动读卡命令	
}

/*******************************************************************************
*函数名			:	function
*功能描述		:	function
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	
*******************************************************************************/
void CardReaderSetPassive(sBoradDef*	sBorad)		//设置读卡器为被动读卡
{
	u8 Num	=	0;
	PortDef*	Port	=	&(sBorad->Port1);			//TimeSpan
	CardReaderCmd_SetArea[4]	=	0x00;
	for(Num=0;Num<MaxPortNum;Num++)					//循环扫描各端口
	{
		if((Port->sReader.TimeCount%50)	==	0)
		{
			Port->sReader.TimeCount++;

			CardReaderSendData((Port->sReader.UartPort),CardReaderCmd_SetArea,14);		//设置读头读卡扇区、块号、KEYA/KEYB、读卡密码0x44
		}

		if(Num<MaxPortNum-1)
		{
			Port=(PortDef*)((u32)Port+sizeof(PortDef));				
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
*注释				:	
*******************************************************************************/
void CardReaderSetActive(sBoradDef*	sBorad)		//设置读卡器为主动读卡
{
	u8 Num	=	0;
	PortDef*	Port	=	&(sBorad->Port1);			//TimeSpan
	CardReaderCmd_SetArea[4]	=	0x60;
	for(Num=0;Num<MaxPortNum;Num++)					//循环扫描各端口
	{
		if((Port->sReader.TimeCount%50)	==	0)
		{
			Port->sReader.TimeCount++;

			CardReaderSendData((Port->sReader.UartPort),CardReaderCmd_SetArea,14);		//设置读头读卡扇区、块号、KEYA/KEYB、读卡密码0x44
		}

		if(Num<MaxPortNum-1)
		{
			Port=(PortDef*)((u32)Port+sizeof(PortDef));				
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
*注释				:	
*******************************************************************************/
void CardReaderReadCmd(sBoradDef*	sBorad)		//读卡指令---发送主动读卡命令
{
	u8 Num	=	0;
	PortDef*	Port	=	&(sBorad->Port1);			//TimeSpan	

	if(((sBorad->sPlu.Time.TimeCard)%1000<100)||((sBorad->sPlu.Time.TimeCard)%1000>=200))		//前50ms读数据CardReaderRead，后100ms发送读卡请求
	{
		return;
	}
	
	for(Num=0;Num<MaxPortNum;Num++)					//循环扫描各端口
	{
		if((Port->sReader.ReaderSts.ReadData)==0)
		{
			Port->sReader.ReaderSts.ReadData	=	1;		//bit1：0-无操作,			1-已发送读卡命令
			CardReaderSendData((Port->sReader.UartPort),CardReaderCmd_ReadData,14);
		}
		//-----------------------------------指向下一端口
		if(Num<MaxPortNum-1)
		{
			Port=(PortDef*)((u32)Port+sizeof(PortDef));				
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
void	CardDataAnalysis(sBoradDef*	sBorad)					//读取IC卡数据校验
{
	u8 Num	=	0;
	u16 Length	=	0;
	PortDef*	Port	=	&(sBorad->Port1);			//TimeSpan
	
	//========清除标识
	for(Num=0;Num<MaxPortNum;Num++)					//循环扫描各端口
	{
		Port->sReader.ReaderSts.ReadData	=	0;		//bit1：0-无操作,			1-已发送读卡命令
		//-----------------------------------指向下一端口
		if(Num<MaxPortNum-1)
		{
			Port=(PortDef*)((u32)Port+sizeof(PortDef));				
		}
	}
	
	Port	=	&(sBorad->Port1);			//TimeSpan
	for(Num=0;Num<MaxPortNum;Num++)					//循环扫描各端口
	{
		Length	=	CardReaderReadData(Port->sReader.UartPort,(u8*)&(Port->sReader.Rev[0]),(u8*)&(Port->sReader.Rxd[0]));			//检查读卡器有无收到数据
		if(Length>=6)
		{
			u8 i	=	0;
			for(i	=	0;i<6;i++)
			{
				if((Port->sReader.Rev[i]	==	0xD2)&&(Port->sReader.Rev[i+1]	==	0x24))		//查找IC卡数据头标识符
				{
					if(Port->sReader.Rev[i+2]	==	0x01)			//无卡数据
					{
						Port->sReader.DataLen	=	6;					//6字节表示返回无卡数据
						memset(Port->sReader.Rev,0x00,CardDataSize);
					}
					else
					{
						Port->sReader.DataLen	=	22;					//2字节表示返回卡数据
						memcpy((u8*)&(Port->sReader.CardBuffer),&(Port->sReader.Rev[i]),22);
						memset(Port->sReader.Rev,0x00,CardDataSize);
					}
				}
			}
		}
		else
		{
			Port->sReader.DataLen	=	0;					//6字节表示返回无卡数据
		}
		//-----------------------------------指向下一端口
		if(Num<MaxPortNum-1)
		{
			Port=(PortDef*)((u32)Port+sizeof(PortDef));				
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
*注释				:	
*******************************************************************************/
void CardReaderRead(sBoradDef*	sBorad)			//检查读卡器有无收到数据
{
	u8 Num	=	0;

	PortDef*	Port	=	&(sBorad->Port1);			//TimeSpan
	
	if((sBorad->sPlu.Time.TimeCard)%1000!=950)		//前950ms读数据CardReaderRead，后50ms发送读卡请求
	{
		return;
	}	
	CardDataAnalysis(sBorad);								//读取IC卡数据校验，
	
	Port	=	&(sBorad->Port1);			//TimeSpan
	
	for(Num=0;Num<MaxPortNum;Num++)					//循环扫描各端口
	{
		if(Port->sReader.DataLen	==	6)	//无卡
		{
			Port->sReader.DataLen	=	0;			//读到的数据大小	
			if(((Port->sReader.ReaderSts.NoCard	!=1)||(Port->sReader.ReaderSts.ReadID!=0))&&(Port->sReader.Retry++>1))	//bit5：0-无操作,			1-无卡（无药箱）
			{
				Port->sReader.Retry		=	0;			//读卡器重试		
				//=====================更新读卡器标志				
				Port->sReader.ReaderSts.ReadID	=	0;	//bit2：0-无操作,			1-读到ID(需要增加相关数据及标志)
				Port->sReader.ReaderSts.ReadErr	=	0;	//bit3：0-读卡器正常，	1-读卡器通讯异常
				Port->sReader.ReaderSts.NoCard	=	1;	//bit5：0-无操作,			1-无卡（无药箱）
				//---------------------清除卡号数据
				memset((Port->sReader.CardNum),0x00,CardLength);
				Port->sReader.CardNumber	=	0;
				
				//=====================数码管：点闪烁
				Port->Seg.sSegSts.SegFlg					=	1;	//bit0：0-无操作,	1-有操作请求(需要更新数码管状态）
				Port->Seg.SegFarme.cmd.DispEnNum	=	0;	//bit0显示数值	：	0-不显示，		1-显示
				Port->Seg.SegFarme.cmd.DispEnDp		=	1;	//bit1显示点		：	0-不显示，		1-显示
				Port->Seg.SegFarme.cmd.DispMdNum	=	0;	//bit2数值模式	：	0-静态显示，	1-0.5S闪烁
				Port->Seg.SegFarme.cmd.DispMdDp		=	1;	//bit3点模式		：	0-静态显示，	1-0.5S闪烁
				Port->Seg.SegFarme.cmd.DispTime		=	0;	//bit4显示时间	：	0-长亮，			1-在显示时间内根据显示模式显示				
				memset((Port->Seg.SegFarme.data),0x00,4);		//清除数据	

				//=====================更新总线标志及根据条件上报
				if(sBorad->sPlu.PowerUpFlag	!=0)		//上电标志，0未上电完，1上电完
				{
					if(Port->sBus.BusqSts.GetBox	==	1)			//取药请求
					{
						Port->sBus.BusqSts.GotBox		=	1;	//bit3：0-无操作，	1-药箱已被取走
						Port->sBus.BusqSts.TakeBox	=	0;	//bit4：0-无操作，	1-药箱被强制取
					}
					else
					{
						Port->sBus.BusqSts.GotBox		=	0;	//bit3：0-无操作，	1-药箱已被取走
						Port->sBus.BusqSts.TakeBox	=	1;	//bit4：0-无操作，	1-药箱被强制取
					}							
					Port->sBus.BusqSts.BusFlg		=	1;		//bit0：0-无操作,	1-有待处理事件(上报数据或者状态）
					Port->sBus.BusqSts.GetID		=	0;		//bit1：0-无请求，	1-有请求	，获取ID请求需要上报ID
					Port->sBus.BusqSts.GetBox		=	0;		//bit2：0-无请求，	1-有请求	，取药(数码管数值同时闪烁)
					Port->sBus.BusqSts.BoxBack	=	0;		//bit5：0-无操作，	1-药箱收回,收回后需要上报药箱号（有GotBox标志时设置此位）
					Port->sBus.BusqSts.TimeOut	=	0;		//bit6：0-无操作，	1-取药超时
				}
				Port->sBus.CardData[0]	=	0;
				Port->sBus.CardData[1]	=	0;
				Port->sBus.CardData[2]	=	0;
			}
			else if(Port->Seg.sSegSts.Sync	==	1)
			{
				//=====================数码管：点闪烁
				Port->Seg.sSegSts.Sync						=	0;	//bit1：0-无操作,		1-更新
				Port->Seg.sSegSts.SegFlg					=	1;	//bit0：0-无操作,	1-有操作请求(需要更新数码管状态）
				Port->Seg.SegFarme.cmd.DispEnNum	=	0;	//bit0显示数值	：	0-不显示，		1-显示
				Port->Seg.SegFarme.cmd.DispEnDp		=	1;	//bit1显示点		：	0-不显示，		1-显示
				Port->Seg.SegFarme.cmd.DispMdNum	=	0;	//bit2数值模式	：	0-静态显示，	1-0.5S闪烁
				Port->Seg.SegFarme.cmd.DispMdDp		=	1;	//bit3点模式		：	0-静态显示，	1-0.5S闪烁
				Port->Seg.SegFarme.cmd.DispTime		=	0;	//bit4显示时间	：	0-长亮，			1-在显示时间内根据显示模式显示				
				memset((Port->Seg.SegFarme.data),0x00,4);		//清除数据
				
			}
		}
		else if(Port->sReader.DataLen	==	22)		//读到卡数据
		{			
			Port->sReader.DataLen	=	0;			//读到的数据大小
			
			if(((Port->sReader.ReaderSts.NoCard	!=0)||(Port->sReader.ReaderSts.ReadID!=1))&&(Port->sReader.Retry++>1))	//bit5：0-无操作,			1-无卡（无药箱）
			{
				Port->sReader.Retry		=	0;			//读卡器重试
				if(!((Port->sReader.CardBuffer.data[2]==0)&&(Port->sReader.CardBuffer.data[3]==0)))
				{
					u32 Time	=	5000;			//数码管亮5秒
					//=====================更新读卡器标志
					Port->sReader.ReaderSts.ReadID	=	1;	//bit2：0-无操作,			1-读到ID(需要增加相关数据及标志)
					Port->sReader.ReaderSts.ReadErr	=	0;	//bit3：0-读卡器正常，	1-读卡器通讯异常
					Port->sReader.ReaderSts.NoCard	=	0;	//bit5：0-无操作,			1-无卡（无药箱）
					
					memcpy((Port->sReader.CardNum),(Port->sReader.CardBuffer.data),CardLength);
					Port->sReader.CardNum[0]	=	((Port->sReader.CardBuffer.data[2])>>4)&0x0F;
					Port->sReader.CardNum[1]	=	((Port->sReader.CardBuffer.data[2])>>0)&0x0F;
					Port->sReader.CardNum[2]	=	((Port->sReader.CardBuffer.data[3])>>4)&0x0F;
					Port->sReader.CardNum[3]	=	((Port->sReader.CardBuffer.data[3])>>0)&0x0F;
					
					Port->sReader.CardNumber	=	Port->sReader.CardNum[0]*1000
																		+	Port->sReader.CardNum[1]*100
																		+	Port->sReader.CardNum[2]*10
																		+	Port->sReader.CardNum[3];
					//=====================数码管：数码管显示卡号长亮5秒
					Port->Seg.sSegSts.SegFlg					=	1;	//bit0：0-无操作,	1-有操作请求(需要更新数码管状态）
					Port->Seg.SegFarme.cmd.DispEnNum	=	1;	//bit0显示数值	：	0-不显示，		1-显示
					Port->Seg.SegFarme.cmd.DispEnDp		=	0;	//bit1显示点		：	0-不显示，		1-显示
					Port->Seg.SegFarme.cmd.DispMdNum	=	0;	//bit2数值模式	：	0-静态显示，	1-0.5S闪烁
					Port->Seg.SegFarme.cmd.DispMdDp		=	0;	//bit3点模式		：	0-静态显示，	1-0.5S闪烁
					Port->Seg.SegFarme.cmd.DispTime		=	1;	//bit4显示时间	：	0-长亮，			1-在显示时间内根据显示模式显示
							
					//-------------------数码管数据
					Port->Seg.SegFarme.data[0]	=	(Port->sReader.CardNumber>>24)&0xFF;
					Port->Seg.SegFarme.data[1]	=	(Port->sReader.CardNumber>>18)&0xFF;
					Port->Seg.SegFarme.data[2]	=	(Port->sReader.CardNumber>>8)&0xFF;
					Port->Seg.SegFarme.data[3]	=	(Port->sReader.CardNumber>>0)&0xFF;
					//-------------------数码管显示时间
					memcpy(&(Port->Seg.SegFarme.data[4]),&Time,4);
					
					//=====================更新总线标志及根据条件上报					
					if(sBorad->sPlu.PowerUpFlag	==1)	//上电标志，0未上电完，1上电完
					{
						Port->sBus.BusqSts.BusFlg		=	1;	//bit0：0-无操作,	1-有待处理事件(上报数据或者状态）
						Port->sBus.BusqSts.GetID		=	0;	//bit1：0-无请求，	1-有请求	，获取ID请求需要上报ID
						Port->sBus.BusqSts.GetBox		=	0;	//bit2：0-无请求，	1-有请求	，取药(数码管数值同时闪烁)
						Port->sBus.BusqSts.GotBox		=	0;	//bit3：0-无操作，	1-药箱已被取走
						Port->sBus.BusqSts.TakeBox	=	0;	//bit4：0-无操作，	1-药箱被强制取
						Port->sBus.BusqSts.BoxBack	=	1;	//bit5：0-无操作，	1-药箱收回,收回后需要上报药箱号（有GotBox标志时设置此位）
						Port->sBus.BusqSts.TimeOut	=	0;	//bit6：0-无操作，	1-取药超时						
					}
					Port->sBus.CardData[0]	=	Port->sReader.CardNum[1];
					Port->sBus.CardData[1]	=	Port->sReader.CardNum[2];
					Port->sBus.CardData[2]	=	Port->sReader.CardNum[3];
				}
			}
		}
		else
		{
			Port->sReader.Retry		++;			//读卡器重试
			if(Port->sReader.Retry>=5)
			{
				Port->sReader.Retry	=	0;
				//=====================更新读卡器标志
				Port->sReader.ReaderSts.ReadID	=	0;	//bit2：0-无操作,			1-读到ID(需要增加相关数据及标志)
				Port->sReader.ReaderSts.ReadErr	=	1;	//bit3：0-读卡器正常，	1-读卡器通讯异常
				Port->sReader.ReaderSts.NoCard	=	0;	//bit5：0-无操作,			1-无卡（无药箱）
				
				//=====================数码管：数码管显示卡号长亮5秒
				Port->Seg.sSegSts.SegFlg					=	1;	//bit0：0-无操作,	1-有操作请求(需要更新数码管状态）
				Port->Seg.SegFarme.cmd.DispEnNum	=	0;	//bit0显示数值	：	0-不显示，		1-显示
				Port->Seg.SegFarme.cmd.DispEnDp		=	1;	//bit1显示点		：	0-不显示，		1-显示
				Port->Seg.SegFarme.cmd.DispMdNum	=	0;	//bit2数值模式	：	0-静态显示，	1-0.5S闪烁
				Port->Seg.SegFarme.cmd.DispMdDp		=	0;	//bit3点模式		：	0-静态显示，	1-0.5S闪烁
				Port->Seg.SegFarme.cmd.DispTime		=	0;	//bit4显示时间	：	0-长亮，			1-在显示时间内根据显示模式显示
			}
		}
		//-----------------------------------指向下一端口
		if(Num<MaxPortNum-1)
		{
			Port=(PortDef*)((u32)Port+sizeof(PortDef));				
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
*注释				:	
*******************************************************************************/
void CardReaderSendData(USART_TypeDef* USARTx,u8 *tx_buffer,u16 BufferSize)		//向读卡器发送数据
{
	if(USARTx	==	ICCardReadPort4)	//无DMA
	{
		USART_Send		(USARTx,(u8*)tx_buffer,14);	//设置读头读卡扇区、块号、KEYA/KEYB、读卡密码0x44
	}
	else
	{
		USART_DMASend	(USARTx,(u32*)tx_buffer,14);	//设置读头读卡扇区、块号、KEYA/KEYB、读卡密码0x44
	}
}

/*******************************************************************************
*函数名			:	function
*功能描述		:	function
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	
*******************************************************************************/
u16 CardReaderReadData(USART_TypeDef* USARTx,u8 *RevBuffer,u8 *RxdBuffer)			//检查读卡器有无收到数据
{
	u16 Num	=	0;	
	if(USARTx	==	ICCardReadPort4)	//无DMA
	{
		Num	=	sBorad.Port4.sReader.DataLen;
		if(Num)
		{
			memcpy(RevBuffer,RxdBuffer,Num);
		}
	}
	else
	{
		Num	=	USART_ReadBufferIDLE(USARTx,(u32*)RevBuffer,(u32*)RxdBuffer);	//串口空闲模式读串口接收缓冲区，如果有数据，将数据拷贝到RevBuffer,并返回接收到的数据个数，然后重新将接收缓冲区地址指向RxdBuffer
	}
	return Num;
}

/*******************************************************************************
*函数名			:	function
*功能描述		:	function
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	
*******************************************************************************/
u16 Uart5ReceiveData(sBoradDef*	sBorad)			//串口5读数据
{
	//==============================Port4
	CardReaderDef *CardReader	=	&(sBorad->Port4.sReader);
	if(USART_GetITStatus(CardReader->UartPort, USART_IT_RXNE))
  {
		CardReader->Rxd[CardReader->DataLen]	=	USART_ReceiveData(CardReader->UartPort);
		
		if(CardReader->DataLen<CardDataSize-1)
		{
			CardReader->DataLen+=1;
		}
		else
		{
			CardReader->DataLen=0;
		}		
		USART_ClearITPendingBit(CardReader->UartPort, USART_IT_RXNE);
		return 1;
	}
	else if(USART_GetITStatus(CardReader->UartPort, USART_IT_TC))
  {   
    USART_ClearITPendingBit(CardReader->UartPort, USART_IT_TC);
		return 1;
  }
	return 0;
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
void CardReadTimeCount(sBoradDef*	sBorad)			//取卡后倒计时，如果倒计时未完成再收回卡数据，读卡不稳定时的误动作
{	
	u8 Num	=	0;
	PortDef*	Port	=	&(sBorad->Port1);			//TimeSpan
	for(Num=0;Num<MaxPortNum;Num++)					//循环扫描各端口
	{
		if(Port->sReader.ReaderSts.ReadFlg	==	1)		//bit0：0-无操作,			1-有操作请求
		{
			if((Port->sReader.TimeCount)<0xFFF0)
			{
				Port->sReader.TimeCount++;
			}
			else
			{
				Port->sReader.TimeCount	=	0;
			}
		}
		else
		{
			Port->sReader.TimeCount	=	0;
		}
		if(Num<MaxPortNum-1)
		{
			Port=(PortDef*)((u32)Port+sizeof(PortDef));				
		}
	}

}



//=================================================================================================================硬件驱动程序

/*******************************************************************************
*函数名			:	function
*功能描述		:	function
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
void HALUsartRemapEnable(void)												//使能串口复用
{
	RS485_DMA_ConfigurationNRRemap(&RS485_Seg7,Seg485BaudRate,(u32*)Seg485Rxd,Seg485BufferSize);//USART_DMA配置(映射)--查询方式，不开中断,配置完默认为接收状态
	GPIO_PinRemapConfig(GPIO_Remap_USART1,ENABLE);			//I/O口重映射开启
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
void HALUsartRemapDisable(void)												//关闭串口复用
{
	GPIO_PinRemapConfig(GPIO_Remap_USART1,DISABLE);				//I/O口重映射开启
	GPIO_ResetBits(RS485_Seg7.RS485_CTL_PORT,	RS485_Seg7.RS485_CTL_Pin);			//释放总线
	USART_DMA_ConfigurationNR	((sBorad.Port2.sReader.UartPort),ICCardReadBaudRate,(u32*)(sBorad.Port2.sReader.Rxd),CardDataSize);	//USART_DMA配置--查询方式，不开中断
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
void HALSendSeg(u32* Buffer,u16 Length)		//向数码管发送数据
{
//	HALUsartRemapEnable();											//使能串口复用
	RS485_DMASend(&RS485_Seg7,Buffer,Length);	//RS485-DMA发送程序
}
//======

//=================================================================================================================配置程序
/*******************************************************************************
*函数名			:	function
*功能描述		:	function
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
void Lock_Configuration(void)			//锁初始化
{
	GPIO_Configuration_OPP50(LockPort1,	LockPin1);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605
	GPIO_Configuration_OPP50(LockPort2,	LockPin2);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605
	GPIO_Configuration_OPP50(LockPort3,	LockPin3);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605
	GPIO_Configuration_OPP50(LockPort4,	LockPin4);			//将GPIO相应管脚配置为PP(推挽)输出模式，最大速度50MHz----V20170605
	LockOff(1);
	LockOff(2);
	LockOff(3);
	LockOff(4);	
}
/*******************************************************************************
*函数名			:	function
*功能描述		:	函数功能说明
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	
*******************************************************************************/
void Switch_Configuration(void)			//拔码开关初始化及读数
{
	SWITCHID.NumOfSW	=	8;
	//SW1--PA4
	SWITCHID.SW1_PORT	=	GPIOA;
	SWITCHID.SW1_Pin	=	GPIO_Pin_4;
	//SW2--PA5
	SWITCHID.SW2_PORT	=	GPIOA;
	SWITCHID.SW2_Pin	=	GPIO_Pin_5;
	//SW3--PB12
	SWITCHID.SW3_PORT	=	GPIOA;
	SWITCHID.SW3_Pin	=	GPIO_Pin_6;
	//SW4--PB13
	SWITCHID.SW4_PORT	=	GPIOA;
	SWITCHID.SW4_Pin	=	GPIO_Pin_7;
	//SW5--PB14
	SWITCHID.SW5_PORT	=	GPIOC;
	SWITCHID.SW5_Pin	=	GPIO_Pin_4;
	//SW6--PB15
	SWITCHID.SW6_PORT	=	GPIOC;
	SWITCHID.SW6_Pin	=	GPIO_Pin_5;
	//SW7--PB0
	SWITCHID.SW7_PORT	=	GPIOB;
	SWITCHID.SW7_Pin	=	GPIO_Pin_0;
	//SW8--PB1
	SWITCHID.SW8_PORT	=	GPIOB;
	SWITCHID.SW8_Pin	=	GPIO_Pin_1;
	
	SwitchIdInitialize(&SWITCHID);				//
	SWITCHID_Read(&SWITCHID);				//读拔码地址
	
	SwitchData	=	(SWITCHID.nSWITCHID)&0xFF;
}
/*******************************************************************************
* 函数名			:	RS485_Configuration
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: 
*******************************************************************************/
void RS485_Configuration(void)			//RS485配置
{
	//============================总线通讯485
	RS485_Bus.USARTx	=	Bus485Port;	
	RS485_Bus.RS485_CTL_PORT	=	Bus485CtlPort;
	RS485_Bus.RS485_CTL_Pin		=	Bus485CtlPin;
	
	RS485_DMA_ConfigurationNR	(&RS485_Bus,Bus485BaudRate,(u32*)&(sBorad.sPlu.BusData.sFarmeRxd),Bus485BufferSize);	//USART_DMA配置--查询方式，不开中断,配置完默认为接收状态
	
	//============================数码管显示485
	RS485_Seg7.USARTx	=	Seg485PortRmap;	
	RS485_Seg7.RS485_CTL_PORT	=	Seg485CtlPort;
	RS485_Seg7.RS485_CTL_Pin		=	Seg485CtlPin;
	
	RS485_DMA_ConfigurationNRRemap(&RS485_Seg7,Seg485BaudRate,(u32*)Seg485Rxd,Seg485BufferSize);//USART_DMA配置(映射)--查询方式，不开中断,配置完默认为接收状态
}
/*******************************************************************************
* 函数名			:	RS485_Configuration
* 功能描述		:	函数功能说明 
* 输入			: void
* 返回值			: void
* 修改时间		: 无
* 修改内容		: 无
* 其它			: 
*******************************************************************************/
void CardReader_Configuration(void)			//选择相应端口读卡器配置
{
	USART_DMA_ConfigurationNR	((sBorad.Port1.sReader.UartPort),ICCardReadBaudRate,(u32*)(sBorad.Port1.sReader.Rxd),CardDataSize);	//USART_DMA配置--查询方式，不开中断
	USART_DMA_ConfigurationNR	((sBorad.Port2.sReader.UartPort),ICCardReadBaudRate,(u32*)(sBorad.Port2.sReader.Rxd),CardDataSize);	//USART_DMA配置--查询方式，不开中断
	USART_DMA_ConfigurationNR	((sBorad.Port3.sReader.UartPort),ICCardReadBaudRate,(u32*)(sBorad.Port3.sReader.Rxd),CardDataSize);	//USART_DMA配置--查询方式，不开中断
	USART_ConfigurationIT			((sBorad.Port4.sReader.UartPort),ICCardReadBaudRate,0,0);	//USART_配置---常规中断方式//UART5不支持DMA传输
	
//	USART_DMA_ConfigurationNRRemap	(ICCardReadPort2,ICCardReadBaudRate,(u32*)&ICCardReadRxd2,ICCardReadBufferSize);	//USART_DMA配置(映射)--查询方式，不开中断
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
void Data_Initialize(void)						//参数初始化
{
	u8 Num	=	0;
	PortDef*	Port	=	&(sBorad.Port1);
	//========================各端口锁绑定
	sBorad.Port1.Lock.GPIOx	=	LockPort1;
	sBorad.Port1.Lock.GPIO_Pin_n	=	LockPin1;
	
	sBorad.Port2.Lock.GPIOx	=	LockPort2;
	sBorad.Port2.Lock.GPIO_Pin_n	=	LockPin2;
	
	sBorad.Port3.Lock.GPIOx	=	LockPort3;
	sBorad.Port3.Lock.GPIO_Pin_n	=	LockPin3;
	
	sBorad.Port4.Lock.GPIOx	=	LockPort4;
	sBorad.Port4.Lock.GPIO_Pin_n	=	LockPin4;
	
	//========================端口编号
	Port	=	&(sBorad.Port1);
	for(Num=0;Num<MaxPortNum;Num++)
	{
		Port->PortNum	=	Num+1;			//分配端口号：1~4
		if(Num<MaxPortNum-1)
		{
			Port=(PortDef*)((u32)Port+sizeof(PortDef));		//指向下一端口
		}
	}
	
	//========================各端口数码管地址分配
	Port	=	&(sBorad.Port1);
	for(Num=0;Num<MaxPortNum;Num++)
	{
		Port->Seg.SegFarme.desAddr	=	Num+1;			//分配地址：1~4
		if(Num<MaxPortNum-1)
		{
			Port=(PortDef*)((u32)Port+sizeof(PortDef));		//指向下一端口
		}
	}
	//========================读卡器端口
	sBorad.Port1.sReader.UartPort	=	ICCardReadPort1;
	sBorad.Port2.sReader.UartPort	=	ICCardReadPort2;
	sBorad.Port3.sReader.UartPort	=	ICCardReadPort3;
	sBorad.Port4.sReader.UartPort	=	ICCardReadPort4;

}
/*******************************************************************************
*函数名			:	function
*功能描述		:	function
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	
*******************************************************************************/
void ResetData(void)			//重置相关变量
{

}

//================

#endif

