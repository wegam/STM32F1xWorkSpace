#include "AMP_CABV11.H"


#include "AMP01.H"

#include	"AMP_PHY.H"

#include "IOT5302W.H"     //������

#include "STM32F10x_BitBand.H"
#include "STM32_GPIO.H"
#include "STM32_SYS.H"
#include "STM32_SYSTICK.H"
#include "STM32_WDG.H"
#include "STM32_PWM.H"
#include "STM32_USART.H"

#include "SWITCHID.H"

#include 	"CRC.H"

#include "string.h"				//�����ڴ��������ͷ�ļ�


RS485Def stCbRS485Ly;   //uart4,PA15   //���ӿ�
RS485Def stCbRS485Cb;   //usart1,PA8    //����ӿ�
RS485Def stCardRS485Ly; //usart3,PB2    //�������ӿ�
SwitchDef stCbSwitch;

unsigned char CardData[64]={0}; //���������ջ���
unsigned char CardNum=0;  //��������������
unsigned short InitCardReaderTimeOut=0; //���������ó�ʱʱ�� 10��
unsigned char InitCardReaderFlag=0; //���������ñ�ʶ��0-δ���ã�1-������
unsigned long InitCardUSART_BaudRate=0; //���ö�����ʱʹ�õĲ�����
unsigned char CabAddr   =0;
unsigned char MainFlag  =0; //0--����1--����

/*******************************************************************************
*������			:	function
*��������		:	function
*����				: 
*����ֵ			:	��
*�޸�ʱ��		:	��
*�޸�˵��		:	��
*ע��				:	wegam@sina.com
*******************************************************************************/
void AMP_CABV11_Configuration(void)
{	
	SYS_Configuration();					//ϵͳ����---��ϵͳʱ�� STM32_SYS.H	
  
  AMPCABSwitchID_Configuration();
  
  AMPCAB_GenyConfiguration();   //����ӿ����ã����⣬������Դ����
    
  AMPCABCOMM_Configuration();   //ͨѶ����
  
  SysTick_DeleymS(1000);				//SysTick��ʱnmS--���ϵ��ȶ�

}
/*******************************************************************************
*������			:	function
*��������		:	function
*����				: 
*����ֵ			:	��
*�޸�ʱ��		:	��
*�޸�˵��		:	��
*ע��				:	wegam@sina.com
*******************************************************************************/
void AMP_CABV11_Server(void)
{
  //========================������������
  LockServer();
  RequestServer();    //���������
  StatusServer();     //״̬����
  AMPCAB_SwitchIDServer();
  AMPCAB_SYSLED();
  AMPCAB_BackLight();
  API_IOT5302WServer();   //�������������
}
/*******************************************************************************
*������			:	MainBoard_Server
*��������		:	������з������
              1-��ѯ�����豸
              2-��ѯ�������������ϴ�
*����				: 
*����ֵ			:	��
*�޸�ʱ��		:	��
*�޸�˵��		:	��
*ע��				:	wegam@sina.com
*******************************************************************************/
void AMP_CABV11_Loop(void)
{ 
  //========================������������
  AMPCAB_Receive();
  Send_Server();
  
}
/*******************************************************************************
*������			:	CardReaderInitLoop
*��������		:	function
*����				: 
*����ֵ			:	��
*�޸�ʱ��		:	��
*�޸�˵��		:	��
*ע��				:	wegam@sina.com
*******************************************************************************/
void CardReaderInitLoop(void)
{
  unsigned char data[64]={0};
  unsigned char RxNum  = 0;
  //---------------------���ӿ� USART2
  RxNum = RS485_ReadBufferIDLE(&stCardRS485Ly,data);
  if(RxNum)
  {
    unsigned char i=0;
    if(RxNum>64)
      RxNum=64;
    
    memcpy(&CardData[CardNum],data,RxNum);
    CardNum+=RxNum;
    if(CardNum>=64)
    {
      CardNum=0;
    }
    for(i=0;i<64;i++)
    {
      if(CardData[i]==0xAA)
      {
        if((CardData[i+2]==0x02)  /*����*/
          &&(CardData[i+3]==0x00) /*״̬*/
        &&(CardData[i+4]==0x01)   /*�����ʴ���19200*/
        &&(CardData[i+6]==0xBB))  /*������*/
        {
          InitCardReaderFlag=1;
          InitCardUSART_BaudRate=19200;
          RS485_DMA_ConfigurationNR(&stCardRS485Ly,InitCardUSART_BaudRate,gDatasize);	//USART_DMA����--��ѯ��ʽ�������ж�,������Ĭ��Ϊ����״̬
        }
      }
    }
  } 
}
/*******************************************************************************
*������			:	function
*��������		:	function
*����				: 
*����ֵ			:	��
*�޸�ʱ��		:	��
*�޸�˵��		:	��
*ע��				:	wegam@sina.com
*******************************************************************************/
void AMPCAB_Receive(void)
{
  unsigned short RxNum  = 0;
  unsigned char rxd[256]={0};
  //==========================================================���ղ�ѯ
  //---------------------PC�ӿ� USART1
  RxNum = USART_ReadBufferIDLE(CommPcPort,rxd);
  if(RxNum)
  {
    Msg_ProcessCB(PcPort,rxd,RxNum);                //����Ϣ����
  }
  //---------------------����ӿ� UART4
  RxNum = RS485_ReadBufferIDLE(&stCbRS485Cb,rxd);
  if(RxNum)
  {
    Msg_ProcessCB(CabPort,rxd,RxNum);
  }  
  //---------------------���ӿ� USART2
  RxNum = RS485_ReadBufferIDLE(&stCbRS485Ly,rxd);
  if(RxNum)
  {
    Msg_ProcessCB(LayPort,rxd,RxNum);              //����Ϣ����
  }
  //---------------------�������ӿ� USART3
  RxNum = API_IOT5302WGetUID(rxd);
  if(RxNum)
  {
    Msg_ProcessCB(CardPort,rxd,RxNum);
  }
}
/*******************************************************************************
*������			:	function
*��������		:	function
*����				: 
*����ֵ			:	��
*�޸�ʱ��		:	��
*�޸�˵��		:	��
*ע��				:	wegam@sina.com
*******************************************************************************/
void AMPCAB_SwitchIDServer(void)
{
  unsigned char cabaddrbac=CabAddr;
  if(0==AMPPro.Time.swicthidtime)
  {
    CabAddr  = SWITCHID_ReadLeft(&stCbSwitch)&0x3F;
  
    if(SWITCHID_ReadLeft(&stCbSwitch)&0x80)
    {
      MainFlag=1; //0--����1--����
    }
    else
    {
      MainFlag=0; //0--����1--����
    }
    if(cabaddrbac!=CabAddr)
    {
      AMPCABCOMM_Configuration();   //ͨѶ����
    }
  }
}
/*******************************************************************************
* ������			:	function
* ��������		:	��������˵�� 
* ����			: void
* ����ֵ			: void
* �޸�ʱ��		: ��
* �޸�����		: ��
* ����			: wegam@sina.com
*******************************************************************************/
void AMPCAB_SYSLED(void)
{
  if(0==AMPPro.Time.SYSLEDTime)
  {    
    GPIO_Toggle	(SYSLEDPort,SYSLEDPin);		//��GPIO��Ӧ�ܽ������ת----V20170605
    if(CabAddr)   //�Ѳ��룬Ƶ��1Hz
    {
      AMPPro.Time.SYSLEDTime=500;
    }
    else          //δ���룬Ƶ��5Hz
    {
      AMPPro.Time.SYSLEDTime=100;
    }
  }
}

/*******************************************************************************
*������			:	function
*��������		:	function
*����				: 
*����ֵ			:	��
*�޸�ʱ��		:	��
*�޸�˵��		:	��
*ע��				:	wegam@sina.com
*******************************************************************************/
void AMPCAB_BackLight(void)
{
  static unsigned short BLtime=0;
  if(0==CabAddr)   //δ����
  {    
    if(BLtime++>200)
    {
      BLtime=0;
      GPIO_Toggle	(BackLightPort,BackLightPin);		//��GPIO��Ӧ�ܽ������ת----V20170605
    }
    return;
  }
  if(AMPPro.Req.BLon)      //���⿪�ؿ���
  {
    BackLightOn;
    AMPPro.Req.BLon=0;
  }
  else if(AMPPro.Req.BLoff)
  {
    BackLightOff;
    AMPPro.Req.BLoff=0;
  }
}
/*******************************************************************************
*������			:	function
*��������		:	function
*����				: 
*����ֵ			:	��
*�޸�ʱ��		:	��
*�޸�˵��		:	��
*ע��				:	wegam@sina.com
*******************************************************************************/
void LockServer(void)
{
    //-----------------------------------δ�����Զ�����
    if(0  ==  CabAddr)    //δ����--�Զ�����
    {
      if(GetLockSts)  //�����Ϊ�ر�״̬������
      {
        UnLock;
      }
      else
      {
        ResLock;
      }
      return;
    }
    //-----------------------------------����ִ�п�������
    if(1==AMPPro.Req.unlockrun)   //����ִ�п�������
    {
      if(AMPPro.Time.LockTime>unlockOuttime-10)//10ms��ʼ�����״̬
      {
        return;
      }
      if(GetLockSts)    //��δ��
      {
        AMPPro.Sta.lockstd  = 1;    //��״̬ΪON--��ס
        if(AMPPro.Time.LockTime==0) //��������ʱ��
        {
          AMPPro.Req.unlockrun  = 0;  //������־�ر�
          AMPPro.Sta.unlockerr  = 1;  //�����쳣
          AMPPro.Time.LockTime  = 0;  //����ʱ�����
          ResLock;
        }
      }
      //----------------------------���Ѵ򿪣���Ҫ��ʱ�ر�������
      else
      {
        if(0==AMPPro.Req.reslockqust) //��ʱ�ͷ�������
        {
          AMPPro.Req.reslockqust  = 1;  //�ͷ�����������
          AMPPro.Time.LockTime    = reslockdelaytime;  //��ʱNms
        }
        else
        {
          if(0==AMPPro.Time.LockTime)//��ʱ��ʱʱ�䵽
          {
            AMPPro.Sta.lockstd    = 0;  //��״̬Ϊ��
            AMPPro.Req.unlockrun  = 0;
            AMPPro.Req.reslockqust= 0;  //�ͷ������������־���
            AMPPro.Sta.unlockerr  = 0;
            AMPPro.Time.LockTime  = 0;
            ResLock;
          }
        }                
      }      
    }
    //-----------------------------------�п�������ʱ���ݴ���
    if(1==AMPPro.Req.unlockqust)  //��������
    {
      AMPPro.Req.unlockrun  = 1;
      AMPPro.Req.unlockqust = 0;
      AMPPro.Req.reslock    = 0;
      AMPPro.Req.reslockqust=0;   //�ͷ������������־���
      AMPPro.Sta.unlockerr  = 0;
      
      
      AMPPro.Req.BLon=1;   //������Ҫ������
      AMPPro.Req.PLon=1;   //���������Ҫ����
      
      AMPPro.Time.LockTime   = unlockOuttime;    //������ʱ����ʱʱ��
      UnLock;
    }
    
    //-----------------------------��������
    if(GetLockSts)    //��δ��
    {
      //����Ƿ�Ϊ��������
      if(0==AMPPro.Sta.lockstd)//ԭ״̬Ϊ���Ѵ�
      {
        AMPPro.Req.BLoff = 1;  //����ر���
        AMPPro.Req.PLoff = 1;  //����رղ���Դ
        AMPPro.Flag.LayPownOn=0; 
      }
      AMPPro.Sta.lockstd  = 1;
    }
    else
    {
      if(1==AMPPro.Sta.lockstd) //ԭ״̬��Ϊ�ر�---�ֶ�����
      {
        AMPPro.Req.BLon = 1;  //����򿪱���
        AMPPro.Req.PLon = 1;  //����򿪲���Դ
        AMPPro.Flag.LayPownOn=1;
      }
      AMPPro.Sta.lockstd  = 0;
    }
}
/*******************************************************************************
* ������			:	function
* ��������		:	��������˵�� 
* ����			: void
* ����ֵ			: void
* �޸�ʱ��		: ��
* �޸�����		: ��
* ����			: wegam@sina.com
*******************************************************************************/
void AMPCABSwitchID_Configuration(void)
{
  stCbSwitch.NumOfSW	=	8;
  
  stCbSwitch.SW1_PORT	=	GPIOB;
  stCbSwitch.SW1_Pin	=	GPIO_Pin_9;
  
  stCbSwitch.SW2_PORT	=	GPIOB;
  stCbSwitch.SW2_Pin	=	GPIO_Pin_8;
  
  stCbSwitch.SW3_PORT	=	GPIOB;
  stCbSwitch.SW3_Pin	=	GPIO_Pin_7;
  
  stCbSwitch.SW4_PORT	=	GPIOB;
  stCbSwitch.SW4_Pin	=	GPIO_Pin_6;
  
  stCbSwitch.SW5_PORT	=	GPIOB;
  stCbSwitch.SW5_Pin	=	GPIO_Pin_5;
  
  stCbSwitch.SW6_PORT	=	GPIOB;
  stCbSwitch.SW6_Pin	=	GPIO_Pin_4;
  
  stCbSwitch.SW7_PORT	=	GPIOB;
  stCbSwitch.SW7_Pin	=	GPIO_Pin_3;
  
  stCbSwitch.SW8_PORT	=	GPIOD;
  stCbSwitch.SW8_Pin	=	GPIO_Pin_2;

	SwitchIdInitialize(&stCbSwitch);						//

  CabAddr  = SWITCHID_ReadLeft(&stCbSwitch)&0x3F;  
  
  if(SWITCHID_ReadLeft(&stCbSwitch)&0x80)
  {
    MainFlag=1; //0--����1--����
  }
  else
  {
    MainFlag=0; //0--����1--����
  }
}
/*******************************************************************************
*������			:	function
*��������		:	function
*����				: 
*����ֵ			:	��
*�޸�ʱ��		:	��
*�޸�˵��		:	��
*ע��				:	wegam@sina.com
*******************************************************************************/
void AMPCAB_GenyConfiguration(void)
{
  //---------------------���ӿ�����
  GPIO_Configuration_OPP50(LockDrPort,LockDrPin);
  GPIO_Configuration_IPU(LockSiPort,LockSiPin);
  ResLock;    //�ͷ�������
  //---------------------����ӿ�����
  GPIO_Configuration_OPP50(BackLightPort,BackLightPin);
  BackLightOn;
  //---------------------��幩��ӿ�����
  GPIO_Configuration_OPP50(LayPowerPort,LayPowerPin);
  LayPowerOn;   //�����磬���ö�����
}

/*******************************************************************************
*������			:	function
*��������		:	function
*����				: 
*����ֵ			:	��
*�޸�ʱ��		:	��
*�޸�˵��		:	��
*ע��				:	wegam@sina.com
*******************************************************************************/
void AMPCABCOMM_Configuration(void)
{
  IOT5302Wdef IOT5302W;
  //-----------------------------PC�ӿ�USART1
  USART_DMA_ConfigurationNR	(CommPcPort,19200,gDatasize);	//USART_DMA����--��ѯ��ʽ�������ж�
  
  //-----------------------------�������ӿ�USART3
  IOT5302W.Conf.IOT5302WPort.USARTx  = CommCardPort;
  IOT5302W.Conf.IOT5302WPort.RS485_CTL_PORT  = CommCardCTLPort;
  IOT5302W.Conf.IOT5302WPort.RS485_CTL_Pin   = CommCardCTLPin;
  IOT5302W.Conf.USART_BaudRate  = CommCardBaudRate;
  API_IOT5302WConfiguration(&IOT5302W);
  //-----------------------------���ӿ�USART2
  stCbRS485Ly.USARTx  = CommLayPort;
  stCbRS485Ly.RS485_CTL_PORT  = CommLayCTLPort;
  stCbRS485Ly.RS485_CTL_Pin   = CommLayCTLPin;
  RS485_DMA_ConfigurationNR			(&stCbRS485Ly,19200,gDatasize);	//USART_DMA����--��ѯ��ʽ�������ж�,������Ĭ��Ϊ����״̬
  //-----------------------------����ӿ�UART4
  stCbRS485Cb.USARTx  = CommCbPort;
  stCbRS485Cb.RS485_CTL_PORT  = CommCbCTLPort;
  stCbRS485Cb.RS485_CTL_Pin   = CommCbCTLPin;
  RS485_DMA_ConfigurationNR			(&stCbRS485Cb,19200,gDatasize);	//USART_DMA����--��ѯ��ʽ�������ж�,������Ĭ��Ϊ����״̬
}
/*******************************************************************************
*������			:	function
*��������		:	function
*����				: 
*����ֵ			:	��
*�޸�ʱ��		:	��
*�޸�˵��		:	��
*ע��				:	wegam@sina.com
*******************************************************************************/
unsigned short AMPCAB_SendBuff(enCCPortDef Port,unsigned char* pBuffer,unsigned short length)
{ 
  unsigned  short   sendedlen = 0;
  switch(Port)
  {
    case  NonPort   : return 0;   //������ִ��
    case  PcPort    : sendedlen = USART_DMASend(CommPcPort,pBuffer,length);
      break;
    case  CabPort   : sendedlen = RS485_DMASend(&stCbRS485Cb,pBuffer,length);	//RS485-DMA���ͳ���
      break;
    case  LayPort   : sendedlen = RS485_DMASend(&stCbRS485Ly,pBuffer,length);	//RS485-DMA���ͳ���
      break;
    case  CardPort  : sendedlen = RS485_DMASend(&stCardRS485Ly,pBuffer,length);	//RS485-DMA���ͳ���
      break;
    default :return 0;      //������ִ��
  }
  return  sendedlen;
}
/*******************************************************************************
*������			:	function
*��������		:	��PC������Ϣ
*����				: 
*����ֵ			:	��
*�޸�ʱ��		:	��
*�޸�˵��		:	��
*ע��				:	wegam@sina.com
*******************************************************************************/
unsigned short PCnet_Send(unsigned char* pBuffer,unsigned short length)
{
  return(AddSendBuffer(PcPort,pBuffer,length));
}
/*******************************************************************************
*������			:	function
*��������		:	����������Ϣ
*����				: 
*����ֵ			:	��
*�޸�ʱ��		:	��
*�޸�˵��		:	��
*ע��				:	wegam@sina.com
*******************************************************************************/
unsigned short Cabinet_Send(unsigned char* pBuffer,unsigned short length)
{
  return(AddSendBuffer(CabPort,pBuffer,length));
}
/*******************************************************************************
*������			:	function
*��������		:	����巢����Ϣ
*����				: 
*����ֵ			:	��
*�޸�ʱ��		:	��
*�޸�˵��		:	��
*ע��				:	wegam@sina.com
*******************************************************************************/
unsigned short Laynet_Send(unsigned char* pBuffer,unsigned short length)
{
  return(AddSendBuffer(LayPort,pBuffer,length));
}
/*******************************************************************************
*������			:	function
*��������		:	���������ӿڷ�����Ϣ
*����				: 
*����ֵ			:	��
*�޸�ʱ��		:	��
*�޸�˵��		:	��
*ע��				:	wegam@sina.com
*******************************************************************************/
unsigned short CardPort_Send(unsigned char* pBuffer,unsigned short length)
{
  return(AddSendBuffer(CardPort,pBuffer,length));
}

/*******************************************************************************
* ������			:	Cabinetmsg_Process
* ��������		:	����Ϣ������������λ���·���Ϣ�����������·���Ϣ�����������Ϣ 
* ����			: void
* ����ֵ			: void
* �޸�ʱ��		: ��
* �޸�����		: ��
* ����			: wegam@sina.com
*******************************************************************************/
void Msg_ProcessCB(enCCPortDef Port,unsigned char* pBuffer,unsigned short length)
{  
  switch(Port)
  {
    case PcPort:Msg_ProcessPcPort(Port,pBuffer,length);     //PC�˿�
      break;
    case CabPort:Msg_ProcessCbPort(Port,pBuffer,length);    //��˿�
      break;
    case LayPort:Msg_ProcessLyPort(Port,pBuffer,length);    //��˿�
      break;
    case CardPort:Msg_ProcessCaPort(Port,pBuffer,length);   //�������˿�
      break;
    default:
      break;
  }
}
/*******************************************************************************
* ������			:	Msg_ProcessPcPort
* ��������		:	����Ϣ������������λ���·���Ϣ�����������·���Ϣ�����������Ϣ 
* ����			: void
* ����ֵ			: void
* �޸�ʱ��		: ��
* �޸�����		: ��
* ����			: wegam@sina.com
*******************************************************************************/
void Msg_ProcessPcPort(enCCPortDef Port,unsigned char* pBuffer,unsigned short length)
{  
  unsigned  char result       = 0; 
  unsigned  char address      = 0;  
  unsigned  short framlength  = 0; 
  unsigned  char  Cmd         = 0;  
  unsigned  char* paddrbac    = pBuffer;         //�������ݻ�����ʼ��ַ
  
  stampphydef* ampframe=NULL;
  //-------------------------���˿��Ƿ�Ϊ��ӿڼ������ַ�Ƿ�Ϊ��
  if(PcPort!=Port||NULL==pBuffer)
  {
    return;
  } 
  //-------------------------Э����
  framlength	=	getframe(pBuffer,&length);    //�ж�֡��Ϣ�����Ƿ����Э��
  if(0== framlength)
  {
    memset(paddrbac,0x00,gDatasize);             //�������
    return;
  }
  result  = ackcheck(pBuffer);                //����Ƿ�ΪӦ����Ϣ,Ӧ����Ϣ����1  
  if(1==result)
  {
    if(AMPPro.buffer.WaitAck.Pc)      //���Ϊ�ȴ�Ӧ��״̬�����ͷ�һ������
    {
      AMPPro.buffer.WaitAck.Pc=0;
      Releas_OneBuffer(Port);        //�ͷ�һ�����ͻ���
    }
    return;
  }  
  //-------------------------���ݵ�ַת�����ݣ��㲥���ݷ��͵�����ͱ�����
  ampframe  = (stampphydef*)pBuffer;
  Cmd = ampframe->msg.cmd.cmd;  
  
  //-------------------------�ϴ�����:��ӿ�
  //���񣺽��յ��������ϴ���PC������Ӧ��
  //���񣺽��յ��·������жϵ�ַ,�����ַΪ����ַ������Ӧ��(�㲥��ַ��Ӧ��)��������ϴ����ݣ�������
  //1��-----------------�ϴ�����:PC�ӿ�ֻ�����·�����

  //2��-----------------�·����ݣ���ַΪ����ַ���߹㲥��ַ(0xFF)��Ҫ���д����������ַΪ����ַ������Ӧ��(�㲥��ַ��Ӧ��)
  if(MainFlag)  //0--����1--����
  {
  }
  address=ampframe->msg.addr.address1;
  if(0==address)      //���ַΪ��
  {
    return;
  }
  //----------------------------PC�ӿڶ�ҪӦ��
  ackFrame(Port,1);             //����Ӧ��---ȡ��PCӦ��
  
  if((CabAddr!=address))  //������������Ϣ
  {
    
    Cabinet_Send((unsigned char*)ampframe,framlength);//��������
    if(0xFF==address) //�㲥��ַ
    {
      
      AMPPro.buffer.WaitAck.Cab=0;   //����Ҫ����Ӧ��      
    }
    else
    {
      //ackFrame(Port,1);             //����Ӧ��
      AMPPro.buffer.WaitAck.Cab=1;  //��Ҫ����Ӧ��
      return;       //���������ݣ��˳�
    }
  }
  //===================================���յ�������Ϊ����ɽ�������(�����ַ���߹㲥��ַ(0xFF))
  //1)-----------------�����ַ���ж��Ƿ���Ҫ�����ݷ����㣬������ʱ����Ҫ�������������
  address=ampframe->msg.addr.address2;
  if(0!=address)
  {
    if(ampframe->msg.data[0]||ampframe->msg.data[1]||ampframe->msg.data[2])   //����ָ���ƣ���Ҫ���������
    {
      AMPPro.Req.unlockqust=1;//������
      AMPPro.Req.reslock=0;
      AMPPro.Req.BLon=1;
      AMPPro.Req.BLoff=0;
      AMPPro.Req.PLon=1; 
      AMPPro.Req.PLoff=0; 
    }
    if(0xFF==address)//�㲥��ַ
    {
      AMPPro.buffer.WaitAck.Lay=0;   //����ҪӦ��
    }
    else
    {
      AMPPro.buffer.WaitAck.Lay=1;   //��ҪӦ��
    }    
    Laynet_Send((unsigned char*)ampframe,framlength);     //����巢����Ϣ
    return;     //������ɣ��˳�
  }
  //2)-----------------���ַΪ0������Ҫ���·���ֻ�ڹ���ư崦�����ƿ���/������/����
  if(AmpCmdLed ==  Cmd)   //�����������
  {
    AMPPro.Req.BLon=0;
    AMPPro.Req.BLoff=0;
    if(ampframe->msg.data[0])
      AMPPro.Req.BLon=1;
    else
      AMPPro.Req.BLoff=1;
  }
  else if(AmpCmdPwr ==  Cmd)   //��幩���������
  {
    AMPPro.Req.PLon  =0;
    AMPPro.Req.PLoff =0;
    if(ampframe->msg.data[0])
      AMPPro.Req.PLon=1;
    else
      AMPPro.Req.PLoff=1;
  }
  else if(AmpCmdLock ==  Cmd)   //����������
  {
    AMPPro.Req.reslock  =0;
    AMPPro.Req.unlockqust =0;
    if(ampframe->msg.data[0])
      AMPPro.Req.unlockqust=1;
    else
      AMPPro.Req.reslock=1;
  }
}
/*******************************************************************************
* ������			:	Cabinetmsg_Process
* ��������		:	����Ϣ������������λ���·���Ϣ�����������·���Ϣ�����������Ϣ 
* ����			: void
* ����ֵ			: void
* �޸�ʱ��		: ��
* �޸�����		: ��
* ����			: wegam@sina.com
*******************************************************************************/
void Msg_ProcessCbPort(enCCPortDef Port,unsigned char* pBuffer,unsigned short length)
{  
  unsigned  char result       = 0; 
  unsigned  char address      = 0;  
  unsigned  short framlength  = 0; 
  unsigned  char  Cmd         = 0;  
  unsigned  char* paddrbac    = pBuffer;         //�������ݻ�����ʼ��ַ
  
  stampphydef* ampframe=NULL;
  //-------------------------���˿��Ƿ�Ϊ��ӿڼ������ַ�Ƿ�Ϊ��
  if(CabPort!=Port||NULL==pBuffer)
  {
    return;
  } 
  //-------------------------Э����
  framlength	=	getframe(pBuffer,&length);    //�ж�֡��Ϣ�����Ƿ����Э��
  if(0== framlength)
  {
    memset(paddrbac,0x00,gDatasize);             //�������
    return;
  }
  result  = ackcheck(pBuffer);                //����Ƿ�ΪӦ����Ϣ,Ӧ����Ϣ����1  
  if(1==result)
  {
    if(AMPPro.buffer.WaitAck.Cab)           //���Ϊ�ȴ�Ӧ��״̬�����ͷ�һ������
    {
      AMPPro.buffer.WaitAck.Cab=0;
      Releas_OneBuffer(Port);               //�ͷ�һ�����ͻ���
    }
    return;
  }  
  //-------------------------���ݵ�ַת�����ݣ��㲥���ݷ��͵�����ͱ�����
  ampframe  = (stampphydef*)pBuffer;
  Cmd = ampframe->msg.cmd.cmd;  
  
  //-------------------------�ϴ�����:��ӿ�
  //���񣺽��յ��������ϴ���PC������Ӧ��
  //���񣺽��յ��·������жϵ�ַ,�����ַΪ����ַ������Ӧ��(�㲥��ַ��Ӧ��)��������ϴ����ݣ�������
  //1��-----------------�ϴ�����:PC�ӿ�ֻ�����·�����
  if(ampframe->msg.cmd.dir)   //0-down,1-up---��8λ
  {
    if(MainFlag)    //0--����1--����
    {
      ackFrame(Port,0); //����Ӧ��---����Ӧ�𸱹�
      AMPPro.buffer.WaitAck.Pc=1;   //��ҪPCӦ��
      PCnet_Send((unsigned char*)ampframe,framlength);      //��PC������Ϣ
    }
    return;   //�������
  }
  //2��-----------------�·����ݣ���ַΪ����ַ���߹㲥��ַ(0xFF)��Ҫ���д����������ַΪ����ַ������Ӧ��(�㲥��ַ��Ӧ��)
  address=ampframe->msg.addr.address1;
  if(0==address)      //���ַΪ��
  {
    return;
  }
  if((CabAddr!=address)&&(0xFF!=address))  //�����ڴ˹���Ϣ
  {
    return;
  }
  if(CabAddr==address)
    ackFrame(Port,1);             //����Ӧ��
  //===================================���յ�������Ϊ����ɽ�������(�����ַ���߹㲥��ַ(0xFF))
  //1)-----------------�����ַ���ж��Ƿ���Ҫ�����ݷ����㣬������ʱ����Ҫ�������������
  address=ampframe->msg.addr.address2;
  if(0!=address)
  {
    if(ampframe->msg.data[0]||ampframe->msg.data[1]||ampframe->msg.data[2])   //����ָ���ƣ���Ҫ���������
    {
      AMPPro.Req.unlockqust=1;//������
      AMPPro.Req.reslock=0;
      AMPPro.Req.BLon=1;
      AMPPro.Req.BLoff=0;
      AMPPro.Req.PLon=1; 
      AMPPro.Req.PLoff=0; 
    }    
    if(0xFF==address)//�㲥��ַ
    {
      AMPPro.buffer.WaitAck.Lay=0;   //����ҪӦ��
    }
    else
    {
      AMPPro.buffer.WaitAck.Lay=1;   //��ҪӦ��
    }
    Laynet_Send((unsigned char*)ampframe,framlength);     //����巢����Ϣ
    return;     //������ɣ��˳�
  }
  //2)-----------------���ַΪ0������Ҫ���·���ֻ�ڹ���ư崦�����ƿ���/������/����
  if(AmpCmdLed ==  Cmd)   //�����������
  {
    AMPPro.Req.BLon=0;
    AMPPro.Req.BLoff=0;
    if(ampframe->msg.data[0])
      AMPPro.Req.BLon=1;
    else
      AMPPro.Req.BLoff=1;
  }
  else if(AmpCmdPwr ==  Cmd)   //��幩���������
  {
    AMPPro.Req.PLon  =0;
    AMPPro.Req.PLoff =0;
    if(ampframe->msg.data[0])
      AMPPro.Req.PLon=1;
    else
      AMPPro.Req.PLoff=1;
  }
  else if(AmpCmdLock ==  Cmd)   //����������
  {
    AMPPro.Req.reslock  =0;
    AMPPro.Req.unlockqust =0;
    if(ampframe->msg.data[0])
      AMPPro.Req.unlockqust=1;
    else
      AMPPro.Req.reslock=1;
  }
  else if(AmpCmdGetOnline ==  Cmd)   //��ȡ�����豸��ǰ�������Ӧ�𣬴˴�������
  {
    return;
  }
}
/*******************************************************************************
* ������			:	Cabinetmsg_Process
* ��������		:	����Ϣ������������λ���·���Ϣ�����������·���Ϣ�����������Ϣ 
* ����			: void
* ����ֵ			: void
* �޸�ʱ��		: ��
* �޸�����		: ��
* ����			: wegam@sina.com
*******************************************************************************/
void Msg_ProcessCaPort(enCCPortDef Port,unsigned char* pBuffer,unsigned short length)
{  
  CardDataSendUp(Port,pBuffer,length);
}
/*******************************************************************************
* ������			:	Cabinetmsg_Process
* ��������		:	����Ϣ������������λ���·���Ϣ�����������·���Ϣ�����������Ϣ 
* ����			: void
* ����ֵ			: void
* �޸�ʱ��		: ��
* �޸�����		: ��
* ����			: wegam@sina.com
*******************************************************************************/
void Msg_ProcessLyPort(enCCPortDef Port,unsigned char* pBuffer,unsigned short length)
{  
  unsigned  char result       = 0; 
  //unsigned  char address      = 0;  
  unsigned  short framlength  = 0; 
  //unsigned  char  Cmd         = 0;  
  unsigned  char* paddrbac    = pBuffer;         //�������ݻ�����ʼ��ַ
  
  stampphydef* ampframe=NULL;
  
  framlength=length;
  
  //-------------------------Э����
  framlength	=	getframe(paddrbac,&framlength);    //�ж�֡��Ϣ�����Ƿ����Э��
  if(0== framlength)    //������Э�飬��͸��---������
  {
//    CardDataSendUp(Port,pBuffer,length);
    return;
  }
  
  pBuffer=paddrbac;  
  result  = ackcheck(pBuffer);                //����Ƿ�ΪӦ����Ϣ,Ӧ����Ϣ����1  
  if(1==result)
  {
    if(AMPPro.buffer.WaitAck.Lay)      //���Ϊ�ȴ�Ӧ��״̬�����ͷ�һ������
    {
      AMPPro.buffer.WaitAck.Lay=0;
      Releas_OneBuffer(Port);        //�ͷ�һ�����ͻ���
    }
    return;
  }  
  //-------------------------���ݵ�ַת�����ݣ��㲥���ݷ��͵�����ͱ�����
  ampframe  = (stampphydef*)pBuffer;
  //Cmd = ampframe->msg.cmd.cmd;
  
  //-------------------------����˵�������--LyPort�ڸ��ݷ����ж�Ϊ��廹�ǹ�壬����·�������ϴ�
  //-------------------------�ϴ�����:��ӿ�
  //��壺���յ����ݷ���Ϊ�ϴ���Ӧ��������ݣ�������Э���������͸��
  //��壺���յ�������Ϊ�·����ݣ�Ӧ��������������Э������ݲ�����
  //1��-----------------�ϴ�����:����յ�����Ϊ�ϴ����ݣ��������Ӧ������Ҫ���Ϲ��ַ���ٴ��ͨ����/PC�ӿ��ϴ�
  if(1==ampframe->msg.cmd.dir)
  {
    unsigned  char  databuffer[64]={0};
    
    ackFrame(Port,0); //����Ӧ��    
       
    //-------------------------�������˿ڽ��յ�����
    memcpy(databuffer,pBuffer,length);
    framlength  = length;
    framlength  = PaketUpMsg(databuffer,AmpCmdCard,&framlength);
    //-------------------------���õ�ַ:����ư��ַ��Ϊaddress1
    ampframe  = (stampphydef*)databuffer;
    ampframe->msg.addr.address1 = CabAddr;
    //-------------------------����CRC�ͽ�����
    SetFrame(databuffer,&framlength);   //������Ϣ��CRC�ͽ�����������֡����
    //-------------------------��鱾���Ƿ�Ϊ����
    if(1==MainFlag)   //����--ͨ��PC�ӿ��ϴ�
    {
      AMPPro.buffer.WaitAck.Pc=1;   //��ҪӦ��
      PCnet_Send(databuffer,framlength);
    }
    else  //����--ͨ������ӿ��ϴ�
    {
      AMPPro.buffer.WaitAck.Cab=1;   //��ҪӦ��
      Cabinet_Send(databuffer,framlength);     //����������Ϣ
    }    
    return;
  }
  //2��-----------------�·����ݣ�ֻ�в�������·�����
  else
  {
    return;
  }
}
/*******************************************************************************
*������			:	function
*��������		:	function
*����				: 
*����ֵ			:	��
*�޸�ʱ��		:	��
*�޸�˵��		:	��
*ע��				:	wegam@sina.com
*******************************************************************************/
void CardDataSendUp(enCCPortDef Port,unsigned char* pBuffer,unsigned short length)
{
  //unsigned  char result       = 0; 
  //unsigned  char address      = 0;  
  unsigned  short framlength  = 0;  
  //unsigned  char* paddrbac    = pBuffer;         //�������ݻ�����ʼ��ַ
  
  stampphydef* ampframe=NULL;
  //stcmddef    Cmd;
  
  unsigned  char  databuffer[64]={0};   
  //-------------------------�������˿ڽ��յ�����
  memcpy(databuffer,pBuffer,length);
  framlength  = length;
  framlength  = PaketUpMsg(databuffer,AmpCmdCard,&framlength);
  
  //-------------------------���õ�ַ:����ư��ַ��Ϊaddress1
  ampframe  = (stampphydef*)databuffer;
  ampframe->msg.addr.address1 = CabAddr;    //���ַ
  ampframe->msg.addr.address2 = 0;
  ampframe->msg.addr.address3 = 0;
  //-------------------------����CRC�ͽ�����
  SetFrame(databuffer,&framlength);//������Ϣ��CRC�ͽ�����������֡����
  
  if(MainFlag)  //0--����1--����
  {
    AMPPro.buffer.WaitAck.Pc=1;   //��ҪӦ��
    PCnet_Send(databuffer,framlength);    //����������Ϣ
  }
  else
  {
    AMPPro.buffer.WaitAck.Cab=1;   //��ҪӦ��
    Cabinet_Send(databuffer,framlength);    //����������Ϣ
  }
  return;
}
/*******************************************************************************
*������			:	RequestServer
*��������		:	���������
*����				: 
*����ֵ			:	��
*�޸�ʱ��		:	��
*�޸�˵��		:	��
*ע��				:	wegam@sina.com
*******************************************************************************/
void RequestServer(void)
{    
    if(AMPPro.Req.PLon)    //��幩�����
    {      
      LayPowerOn;
      AMPPro.Req.PLon=0;
      AMPPro.Flag.LayPownOn=1;
    }
    else if(AMPPro.Req.PLoff)
    {
      LayPowerOff;
      AMPPro.Req.PLoff=0;
      AMPPro.Flag.LayPownOn=0;
    }
    //if(AMP.Req.unlockqust)
    //{      
      //LockServer();
    //}
    //LockServer();
}
/*******************************************************************************
*������			:	function
*��������		:	function
*����				: 
*����ֵ			:	��
*�޸�ʱ��		:	��
*�޸�˵��		:	��
*ע��				:	wegam@sina.com
*******************************************************************************/
void StatusServer(void)
{
  static unsigned long statustemp=0;
  unsigned short* ptemp=0;
  ptemp=(unsigned short*)&AMPPro.Sta;
  if(statustemp!=*ptemp)//״̬�б仯
  {
    unsigned short framlength=3;
    unsigned char databuffer[32]={0};
    
    stampphydef* ampframe=NULL;
    //stcmddef*   Cmd=NULL;
    
    statustemp=*ptemp;
    

    memcpy(databuffer,ptemp,2);
    
    framlength  = PaketUpMsg(databuffer,AmpCmdSta,&framlength);    
    ampframe  = (stampphydef*)databuffer;
    
    ampframe->msg.addr.address1 = CabAddr;
    ampframe->msg.addr.address2 = 0;
    ampframe->msg.addr.address3 = 0;
    //-------------------------����CRC�ͽ�����
    SetFrame(databuffer,&framlength);//������Ϣ��CRC�ͽ�����������֡����
    if(MainFlag)  //0--����1--����
    {
      AMPPro.buffer.WaitAck.Pc=1;   //��ҪӦ��
      PCnet_Send(databuffer,framlength);    //����������Ϣ
    }
    else
    {
      AMPPro.buffer.WaitAck.Cab=1;   //��ҪӦ��
      Cabinet_Send(databuffer,framlength);    //����������Ϣ
    }
  }
}