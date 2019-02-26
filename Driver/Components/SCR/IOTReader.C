//#ifdef	SSD1963

/********************************************************************************
***SSD1963 LCD屏驱动器
********************************************************************************/
#include "IOTReader.H"
#include 	"TOOL.H"
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
unsigned short IOT5302WSetBaudrate(unsigned char* Buffer,unsigned char Num)
{
  unsigned short FrameLen=7;
  
  Buffer[0]   = IotReaderSTX; //头标识
  Buffer[1]   = 0x00;         //设备地址
  Buffer[2]   = 0x02;         //长度：不包括STX,ETX,BCC,设备地址
  Buffer[3]   = SetBaudrate;  //命令
  Buffer[4]   = Num;         //0x00：9600
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
