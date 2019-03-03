/********************************************************************************
***IOT5302W读卡器--RS485
********************************************************************************/
#include  "IOT5302W.H"
#include  "TOOL.H"


#include	"stdio.h"			//用于printf
#include	"string.h"			//用于printf
#include	"stdarg.h"			//用于获取不确定个数的参数
#include	"stdlib.h"			//malloc动态申请内存空间

IOT5302Wdef IOT5302W;

unsigned char CmdBuffer[16]={0};

void IOT5302W_Initialize(void);     //读卡器初始化
void IOT5302W_DataProcess(void);    //数据处理，接收拼包，协议检查
void IOT5302W_DataCheck(void);

unsigned short IOT5302W_HWSendData(unsigned char* TxdBuffer,unsigned short length);
unsigned short IOT5302W_HWReadData(unsigned char* Buffer);
/*******************************************************************************
*函数名			:	IOT5302W_Configuration
*功能描述		:	IOT5302W配置
*输入				: pRS485使用的RS485结构体
              USART_BaudRate希望配置成的波特率
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
void API_IOT5302WConfiguration(IOT5302Wdef* pIOT5302W)
{
  IOT5302W  = *pIOT5302W;
  IOT5302W.Data.Initialized = 0;
  IOT5302W.Data.Time        = 0;
  IOT5302W.Data.TimeOut     = 0;
  IOT5302W.Data.USART_BaudRate  = 0;
  IOT5302W.Data.BaudRateSetStep = 0;
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
void API_IOT5302WServer(void)
{ 
  //==================================检查参数
  if((0==IOT5302W.Conf.USART_BaudRate)||((0==IOT5302W.Conf.IOT5302WPort.USARTx)||(0==IOT5302W.Conf.IOT5302WPort.RS485_CTL_PORT)))  //参数错误
  {
    return;
  }
  
  //==================================数据处理，接收拼包，协议检查
  IOT5302W_DataProcess();
  //==================================如果未初始化成功，不执行
  if(0==IOT5302W.Data.Initialized)  //未初始化成功
  {
    IOT5302W_Initialize();    //读卡器初始化
    return;
  }
  IOT5302W.Data.Time++;
  //==================================周期扫描数据
  if(IOT5302W.Data.Time%IOT5302WReadCycle==0)   //0.5秒扫描一次
  {
    unsigned char TxdLen  = 0;
    IOT5302W.Data.Time=0; //清零
    IOT5302WGetSNR(CmdBuffer);
    TxdLen  = IOT5302WGetSNR(CmdBuffer);                    //设置读卡器波特率
    TxdLen  = IOT5302W_HWSendData(CmdBuffer,TxdLen);	      //寻卡，获取卡的UID，每个M1卡都有一个唯一的序列号，我们称为“UID”，是32位的，也就是4个字节。
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
unsigned short API_IOT5302WGetUID(unsigned char* Buffer)
{
  unsigned char i=0;
  unsigned char n=0;
  for(i=0;i<4;i++)
  {
    if(IOT5302W.Data.UID[i])
      n++;
  }
  if(0!=n)  //有数据
  {
    if(memcmp(IOT5302W.Data.UID,IOT5302W.Data.UIDbac,4)) //对比两组数据不一样
    {
      memcpy(Buffer,IOT5302W.Data.UID,4);
      memcpy(IOT5302W.Data.UIDbac,IOT5302W.Data.UID,4);
      memset(IOT5302W.Data.UID,0x00,4);
      IOT5302W.Data.TimeCmp = 0;
      return 4; //4字节UID
    }
    else if(IOT5302W.Data.TimeCmp++>2000)
    {
      memcpy(Buffer,IOT5302W.Data.UID,4);
      IOT5302W.Data.TimeCmp = 0;
      return 4; //4字节UID
    }
  }
  else
  {
    memset(IOT5302W.Data.UIDbac,0x00,4);
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
unsigned short IOT5302W_HWSendData(unsigned char* TxdBuffer,unsigned short length)
{
  unsigned short TxdLen = 0;
  TxdLen = RS485_DMASend(&IOT5302W.Conf.IOT5302WPort,TxdBuffer,length);	//RS485-DMA发送程序
  return TxdLen;
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
unsigned short IOT5302W_HWReadData(unsigned char* Buffer)
{
  unsigned short RxdLen = 0;
  RxdLen = RS485_ReadBufferIDLE(&IOT5302W.Conf.IOT5302WPort,Buffer);
  return RxdLen;
}
/*******************************************************************************
*函数名			:	function
*功能描述		:	配置读卡器接口
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
void IOT5302W_HWPortInitialize(unsigned long USART_BaudRate)
{  
  RS485_DMA_ConfigurationNR(&IOT5302W.Conf.IOT5302WPort,USART_BaudRate,IOT5302WBufferSize);	//USART_DMA配置--查询方式，不开中断,配置完默认为接收状态
}
/*******************************************************************************
*函数名			:	IOT5302W_Initialize
*功能描述		:	根据读卡器的响应时间，时间间隔可以设置为200ms
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
void IOT5302W_Initialize(void)
{  
  IOT5302W_DataProcess(); ////数据处理，接收拼包，协议检查
  if(0!=IOT5302W.Data.Initialized)  //未初始化成功
  {
    return;
  }
  //---------------------1秒设置一次波特率,将波特率设置为19200
  if(IOT5302W.Data.Time>=IOT5302WInitializeTimeOut)
  {
    IOT5302W.Data.Time  = 0;
  }
  //---------------------选择相应的测试波特率
  if(IOT5302W.Data.Time%IOT5302WReadCycle==0)
  {    
    if(0==IOT5302W.Data.BaudRateSetStep)
    {
      IOT5302W.Data.USART_BaudRate=9600;
    }
    else if(1==IOT5302W.Data.BaudRateSetStep)
    {
      IOT5302W.Data.USART_BaudRate=19200;
    }
    else if(2==IOT5302W.Data.BaudRateSetStep)
    {
      IOT5302W.Data.USART_BaudRate=38400;
    }
    else if(3==IOT5302W.Data.BaudRateSetStep)
    {
      IOT5302W.Data.USART_BaudRate=57600;
    }
    else if(4==IOT5302W.Data.BaudRateSetStep)
    {
      IOT5302W.Data.USART_BaudRate=115200;
    }
    else
    {
      IOT5302W.Data.USART_BaudRate=IOT5302W.Conf.USART_BaudRate;
      IOT5302W.Data.BaudRateSetStep = 0;
    }
    IOT5302W_HWPortInitialize(IOT5302W.Data.USART_BaudRate);	//配置读卡器接口
    IOT5302W.Data.Time  = 0;
  }
  //---------------------0.5秒发送一次配置
  if((50==IOT5302W.Data.Time))
  {
    
    unsigned char TxdLen  = 0;
    unsigned char BaudRateCode  = 0;
    switch(IOT5302W.Conf.USART_BaudRate)    //根据实际应用需要的波特率设置获取设置读卡器波特率的代码
    {
      case 9600:BaudRateCode=0;
      break;
      case 19200:BaudRateCode=1;
      break;
      case 38400:BaudRateCode=2;
      break;
      case 57600:BaudRateCode=3;
      break;
      case 115200:BaudRateCode=4;
      break;
      default:BaudRateCode=0; //默认配置
      break;
    }
    TxdLen  = IOT5302WSetBaudrate(CmdBuffer,BaudRateCode);  //设置读卡器波特率
    TxdLen  = IOT5302W_HWSendData(CmdBuffer,TxdLen);	      //RS485-DMA发送程序
    IOT5302W.Data.BaudRateSetStep += 1;
  }
  IOT5302W.Data.Time++;
}
/*******************************************************************************
*函数名			:	IOT5302W_DataProcess
*功能描述		:	数据处理，接收拼包，协议检查
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
void IOT5302W_DataProcess(void)
{
  unsigned char IOT5302WRx[64];
  unsigned short RxdLen = 0;  
  RxdLen  = IOT5302W_HWReadData(IOT5302WRx);
  if(RxdLen)
  {
    if(IOT5302W.Data.DataCount+RxdLen>IOT5302WBufferSize)
    {
      IOT5302W.Data.DataCount=0;
      memset(IOT5302W.Data.UID,0x00,4);   //清除UID记录
      IOT5302W.Data.TimeOut = 0;    //超时计时清除
    }
    memcpy(&IOT5302W.Data.Data[IOT5302W.Data.DataCount],IOT5302WRx,RxdLen); //保存接收到的数据
    IOT5302W.Data.DataCount+=RxdLen;    
  }
  else if(IOT5302W.Data.TimeOut++>=IOT5302WReadTimeOut) //超时：无读卡器或者波特率不对
  {
    IOT5302W.Data.Initialized = 0;  //初始化标志，0-未初始化成功，1-初始化成功
  }
  IOT5302W_DataCheck();
}
/*******************************************************************************
*函数名			:	IOT5302W_DataCheck
*功能描述		:	检查数据协议
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
void IOT5302W_DataCheck(void)
{
  if(0==IOT5302W.Data.DataCount)  //没有数据
  {
    return;
  }
  else
  {
    unsigned char i=0;
    unsigned char n=0;
    unsigned char bcc=0;
    for(i=0;i<IOT5302W.Data.DataCount;i++)
    {
      if(IotReaderSTX==IOT5302W.Data.Data[i]) //查找到头标识
      {
        n=IOT5302W.Data.Data[i+2];
        if(i+2+n+1+1>IOT5302WBufferSize)  //超出缓存
        {
          IOT5302W.Data.DataCount=0;
        }
        if(IotReaderETX==IOT5302W.Data.Data[i+2+n+1+1]) //尾标识（2字节为ID和长度，n字节数据，1字节校验，1字节尾标识)
        {
          bcc=BCC8(&IOT5302W.Data.Data[i+1],n+2);   //计算BCC(从ID开始，包含CMD/STD位和n个数据
          if(bcc==IOT5302W.Data.Data[i+2+n+1])//BCC字节（2字节为ID和长度，n字节数据，最后字节为BCC)
          {
            IOT5302W.Data.Initialized = 1;  //初始化标志，0-未初始化成功，1-初始化成功
            if(0x06==IOT5302W.Data.Data[i+2]) //UID消息的数据长度
            {
              memcpy(IOT5302W.Data.UID,&IOT5302W.Data.Data[i+5],4); //读取到UID
              memset(IOT5302W.Data.Data,0x00,IOT5302WBufferSize);   //清除缓存
              IOT5302W.Data.DataCount=0;
              IOT5302W.Data.TimeOut = 0;    //超时计时清除
              return;
            }
          }
        }
      }
    }
    if(i>=IOT5302WBufferSize-2)//未找到UID
    {
      memset(IOT5302W.Data.Data,0x00,IOT5302WBufferSize);   //清除缓存
      IOT5302W.Data.DataCount=0;
    }
  }
  if(IOT5302W.Data.TimeOut++>IOT5302WReadTimeOut)
  {
    memset(IOT5302W.Data.UID,0x00,4);   //清除UID记录
    IOT5302W.Data.TimeOut = 0;    //超时计时清除
  }
}
/*******************************************************************************
*函数名			:	IOT5302WGetSNR
*功能描述		:	寻卡，获取卡的UID，每个M1卡都有一个唯一的序列号，我们称为“UID”，是32位的，也就是4个字节。
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
unsigned short IOT5302WGetSNR(unsigned char* Buffer)
{
  unsigned short FrameLen=8;
  
  Buffer[0]   = IotReaderSTX; //头标识
  Buffer[1]   = 0x00;         //设备地址
  Buffer[2]   = 0x03;         //长度：不包括STX,ETX,BCC,设备地址
  Buffer[3]   = GET_SNR;      //命令
  Buffer[4]   = 0x26;         //0x26：IDLE模式，只对一张卡操作
                              //0x52：ALL模式，可对多张卡操作
  Buffer[5]   = 00;           //0x00：读写器不需要执行halt
                              //0x01：读写器需要执行halt
  Buffer[6]  = BCC8(&Buffer[1],5);		//异或校验;
  Buffer[7]  = IotReaderETX;		//结束标志符
  
  return  FrameLen;
}
/*******************************************************************************
*函数名			:	IOT5302WSetBaudrate
*功能描述		:	设置读卡器波特率
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
unsigned short IOT5302WSetBaudrate(unsigned char* Buffer,unsigned char BaudRateCode)
{
  unsigned short FrameLen=7;
  
  Buffer[0]   = IotReaderSTX; //头标识
  Buffer[1]   = 0x00;         //设备地址
  Buffer[2]   = 0x02;         //长度：不包括STX,ETX,BCC,设备地址
  Buffer[3]   = SetBaudrate;  //命令
  Buffer[4]   = BaudRateCode; //0x00：9600
                              //0x01：19200
                              //0x02：38400
                              //0x03：57600
                              //0x04：115200
                              //其它：9600
  Buffer[5]  = BCC8(&Buffer[1],4);		//异或校验;
  Buffer[6]  = IotReaderETX;		//结束标志符
  
  return  FrameLen;
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
unsigned short IotReaderGetCmdFrame(Cmddef Cmd,unsigned char* Buffer)
{
  unsigned short FrameLen=0;
  IRDdef* IotReader=(IRDdef*)Buffer;
  IotReader->STX  = IotReaderSTX;   //头标识
  IotReader->ID   = 0x00;
  IotReader->Len  = 0X00;     //长度
  IotReader->Cts  = Cmd;
  switch((unsigned char)Cmd)
  {
    case  WriteUserInfo:
          FrameLen  = 0;
    case  ReadUserInfo:
          FrameLen  = 0;
    default:
      FrameLen  = 0;
  }
  return  FrameLen;
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
unsigned short IotMifareGetCmdFrame(Cmddef Cmd,unsigned char Sec,unsigned char* Buffer,unsigned char* KeyBuffer)
{
  unsigned short FrameLen=0;
//  if(Sec<1&&Sec>4)  //读取的块范围不对
//  {
//    return  0;
//  }
  switch((unsigned char)Cmd)
  {
    case  IotRead:
          Buffer[0]   = IotReaderSTX; //头标识
          Buffer[1]   = 0x00;         //设备地址
          Buffer[2]   = 0x0A;         //长度：不包括STX,ETX,BCC,设备地址
          Buffer[3]   = Cmd;          //命令
          Buffer[4]   = 0x01;         //Data[0]读取模式
          Buffer[5]   = Sec;          //Data[1]要读的块，即读多少块。取值范围01-04(一个扇区有4个块，可以一次读取多个块)
          Buffer[6]   = 0x01;         //Data[2]要读的块的起点地址。取值范围：十六进制00-3F即00块到63块。(一个扇区4个块，一个块16字节，一个扇区总共64字节)
          Buffer[7]   = KeyBuffer[0]; //Data[3]key[0]
          Buffer[8]   = KeyBuffer[1]; //Data[4]key[1]
          Buffer[9]   = KeyBuffer[2]; //Data[5]key[2]
          Buffer[10]  = KeyBuffer[3]; //Data[6]key[3]
          Buffer[11]  = KeyBuffer[4]; //Data[7]key[4]
          Buffer[12]  = KeyBuffer[5]; //Data[8]key[5]
          Buffer[13]  = BCC8(&Buffer[1],12);		//异或校验;         //Data[8]key[5]
          Buffer[14]  = IotReaderETX;		//异或校验;         //Data[8]key[5]
          FrameLen    = 15;
    break;
    case  IotWrite:
          FrameLen  = 0;
    break;
    default:
      FrameLen  = 0;
  }
  return  FrameLen;
}



