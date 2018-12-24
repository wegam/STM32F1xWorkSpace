#ifdef AMP_LAY

#include "AMP_LAY.H"

#include "string.h"				//�����ڴ��������ͷ�ļ�
//#include "stm32f10x_dma.h"

#include	"AMP_PHY.H"

#include "STM32F10x_BitBand.H"
#include "STM32_GPIO.H"
#include "STM32_SYS.H"
#include "STM32_SYSTICK.H"
#include "STM32_WDG.H"
#include "STM32_PWM.H"
#include "STM32_USART.H"

#include "SWITCHID.H"

#include 	"CRC.H"




RS485Def stRS485Ly;   //usart2,pa1    //���ӿ�
RS485Def stRS485Cb;   //uart4,pc12    //����ӿ�
SwitchDef stSwitch;

stSysdef  AMP;
unsigned  long*  MCUMEMaddr = (unsigned  long*)(0x1FFFF7E0);
unsigned  short  MCUMEMsize  = 0;
unsigned  short seril=0;
unsigned  char  ackupfarme[]=
{
  0x7E,
  0x02,
  0x81,
  0x00,
  0xB0,
  0x50,
  0x7F
};
unsigned  char  ackdownfarme[]=
{
  0x7E,
  0x02,
  0x01,
  0x00,
  0xD1,
  0x90,
  0x7F
};
/*******************************************************************************
*������			:	function
*��������		:	function
*����				: 
*����ֵ			:	��
*�޸�ʱ��		:	��
*�޸�˵��		:	��
*ע��				:	wegam@sina.com
*******************************************************************************/
void AMP01_Configuration(void)
{	
  MCUMEMsize  = *MCUMEMaddr;
  if(0x0100 ==  MCUMEMsize) //256K Flash ����ư�STM32F103RC
  {
    AMP.Flag.CabBD  = 1;
    AMP.Flag.LayBD  = 0;
    AMP.Flag.SetBD  = 0;
  }
  else if(0x0080 ==  MCUMEMsize) //128K Flash ����ư�STM32F103CB
  {
    AMP.Flag.CabBD  = 0;
    AMP.Flag.LayBD  = 1;
    AMP.Flag.SetBD  = 1;
  }
	SYS_Configuration();					//ϵͳ����---��ϵͳʱ�� STM32_SYS.H	 
	
//  IWDG_Configuration(1000);													//�������Ź�����---������λms
  
  SysTick_Configuration(1000);    //ϵͳ���ʱ������72MHz,��λΪuS
  
  SwitchID_Configuration();
  
  GenyConfiguration();   //����ӿ����ã����⣬������Դ����
    
  COMM_Configuration();  
 
	PWM_OUT(TIM2,PWM_OUTChannel1,2,950);						//PWM�趨-20161127�汾

  while(1)
  {
    AMP01_Loop();
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
void AMP01_Server(void)
{  
  SwitchID_Server();
  if(0  ==  AMP.SwData.ID)
  {
    AMP.Time.runningtime++;
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
  LockServer();
  Tim_Server();
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
void AMP01_Loop(void)
{
  if(0  ==  AMP.SwData.ID)
  {
    if(AMP.Time.runningtime>=500)
    {
      GPIO_Toggle	(BackLightPort,BackLightPin);		//��GPIO��Ӧ�ܽ������ת----V20170605
      AMP.Time.runningtime  = 0;
    }
    return;
  }
  Receive_Server();
  Send_Server();
}

//=================================�����ӿ�ST=============================================================
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
void MainCabinet_IDLEServer(void)
{

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
void Send_Server(void)
{
  //----------------PC����
  if(0  ==  AMP.Time.PcSendTime)
  {
    Check_SendBuff(PcPort);
  }
  //----------------����
  if(0  ==  AMP.Time.CabSendTime)
  {
    Check_SendBuff(CabPort);
  }
  //----------------�㷢��
  if(0  ==  AMP.Time.LaySendTime)
  {
    Check_SendBuff(LayPort);
  }
  //----------------����������
  if(0  ==  AMP.Time.CardSendTime)
  {
    Check_SendBuff(CardPort);
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
unsigned short Check_SendBuff(enCCPortDef Port)
{ 
  unsigned  char  i  = 0;
  unsigned  short  SendLen  = 0;
  unsigned  char  ackflag =0;
  unsigned  char  ackdir =0;
  unsigned  char* SendAddr = NULL;  
  unsigned  char*  ReSendCount;      //PC�ϴ��ط�����
  
  unsigned  short*  SendTime=NULL;
  
  stTxdef* Txd  = NULL;
  
  if(LayPort  ==  Port) //��壺��Ҫ��鹩�����޴�
  {
    if(0  ==  AMP.Flag.LayPownOn) //����δ��
    {
      return  0;
    }
  }
  
  //------------------------------����ط�
  switch(Port)
  {
    case  NonPort   : return 0;   //������ִ��
    case  PcPort    : ReSendCount = &AMP.ReSend.PcCount;
                      Txd=AMP.buffer.PcTx;    //PC�ӿڷ��ͻ���
                      SendTime  = &AMP.Time.PcSendTime;
                      ackflag = AMP.AckQ.PcAck;
                      ackdir  = AMP.AckQ.PcDir;
      break;
    case  CabPort   : ReSendCount = &AMP.ReSend.CabCount;
                      Txd=AMP.buffer.CabTx;   //��ӿڷ��ͻ���
                      SendTime  = &AMP.Time.CabSendTime;
                      ackflag = AMP.AckQ.CabAck;
                      ackdir  = AMP.AckQ.CabDir;
      break;
    case  LayPort   : ReSendCount = &AMP.ReSend.LayCount;
                      Txd=AMP.buffer.LayTx;   //��ӿڷ��ͻ���
                      SendTime  = &AMP.Time.LaySendTime;
                      ackflag = AMP.AckQ.LayAck;
                      ackdir  = AMP.AckQ.LayDir;
      break;
    case  CardPort  : ReSendCount = &AMP.ReSend.CardCount;
                      Txd=AMP.buffer.CardTx;  //�������ӿڷ��ͻ���
                      SendTime  = &AMP.Time.CardSendTime;
                      ackflag = 0;
      break;
    default :return 0;      //������ִ�� 
  }
  if(ackflag) //��Ӧ��������Ӧ��
  {
    if(ackdir)  //����Ӧ��
      SendLen = HW_SendBuff(Port,ackupfarme,sizeof(ackupfarme));   //�����ѷ����ֽ�
    else
      SendLen = HW_SendBuff(Port,ackdownfarme,sizeof(ackdownfarme));   //�����ѷ����ֽ�
    if(SendLen)   //Ӧ���ͳɹ�---�����־����
    {
      switch(Port)
      {
        case  NonPort   : return 0;   //������ִ��
        case  PcPort    : AMP.AckQ.PcAck = 0;
          break;
        case  CabPort   : AMP.AckQ.CabAck = 0;
          break;
        case  LayPort   : AMP.AckQ.LayAck = 0;
          break;
        case  CardPort  : AMP.AckQ.CardAck  = 0;
          break;
        default :return 0;      //������ִ�� 
      }
    }
    *SendTime  = 10;
    return  0;
  }
  if(*SendTime>0)   //�����ط�ʱ�䣬�˳�
  {
    return  0;
  }
  if(*ReSendCount>=maxresendcount) //�����ط���������������
  {
    Releas_OneBuffer(Port);
    *ReSendCount  = 0;      //�ط�����
  }
  //------------------------------��鷢�ͻ���
  for(i=0;i<arrysize;i++)
  {
    if(1  ==  Txd[i].arry)
    {
      SendAddr  = Txd[i].data;    //��ʼ��ַ
      SendLen   = Txd[i].size;    //��С
    }
  }
  //-----------------------------�з����� 
  if(NULL!= SendAddr)
  {
    SendLen = HW_SendBuff(Port,SendAddr,SendLen);   //�����ѷ����ֽ�
    if(SendLen)   //�ɹ����͵�����
    {
      *ReSendCount +=1;
      *SendTime = ReSendWaitTime;
    }
    else
    {
      *SendTime = ReSendWaitTime;
    }
    return  SendLen;
  }
  return  0;
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
void Msg_Process(enCCPortDef Port,unsigned char* pBuffer,unsigned short length)
{  
  unsigned  char result       = 0; 
  unsigned  char address      = 0;  
  unsigned  short framlength  = 0;  
  unsigned  char* paddrbac    = pBuffer;         //�������ݻ�����ʼ��ַ
  
  stampphydef* ampframe=NULL;
  stcmddef    Cmd;
  //-------------------------�������˿�
  if(CardPort  == Port)   //�������ӿ���Э�飬ֻ�������͸��
  {
    unsigned  char  databuffer[64]={0};   
    //-------------------------�������˿ڽ��յ�����
    memcpy(databuffer,pBuffer,length);
    framlength  = length;
    framlength  = PaketUpMsg(databuffer,ICR,&framlength);
    //-------------------------���õ�ַ:����ư��ַ��Ϊaddress1
    ampframe  = (stampphydef*)databuffer;
    ampframe->msg.addr.address1 = AMP.SwData.ID;
    ampframe->msg.addr.address2 = 0;
    ampframe->msg.addr.address3 = 0;
    //-------------------------����CRC�ͽ�����
    SetCrc(databuffer,&framlength);
    //-------------------------��鱾���Ƿ�Ϊ����
    if(1==AMP.SwData.MainFlg)   //����--ͨ��PC�ӿ��ϴ�
    {
      PCnet_Send(databuffer,framlength);
    }
    else  //����--ͨ������ӿ��ϴ�
    {
      //PCnet_Send(databuffer,framlength);
      Cabinet_Send(databuffer,framlength);     //����������Ϣ
    }
    return;
  }
  //-------------------------Э����
  framlength	=	getframe(pBuffer,&length);    //�ж�֡��Ϣ�����Ƿ����Э��
  if(0== framlength)
  {
    memset(paddrbac,0x00,ccsize);             //�������
    return;
  }
  result  = ackcheck(pBuffer);                //����Ƿ�ΪӦ����Ϣ,Ӧ����Ϣ����1
  if(1==result)
  {
    Releas_OneBuffer(Port);        //�ͷ�һ�����ͻ���
    return;
  }
  
  
  //-------------------------���ݵ�ַת�����ݣ��㲥���ݷ��͵�����ͱ�����
  ampframe  = (stampphydef*)pBuffer;
  Cmd = ampframe->msg.cmd;
  
  //-------------------------�·�����
  if(0  ==  Cmd.dir)
  {    
    if(PcPort == Port)
    {
      ackFrame(Port,1); //����Ӧ��
      if(AMP.SwData.ID  ==  ampframe->msg.addr.address1)    //���ַ
      {
        goto CabinetSelfDownDataProcess;
      }
      else if(0xFF  ==  ampframe->msg.addr.address1)      //�㲥��ַ--�����й�
      {
        Cabinet_Send((unsigned char*)ampframe,framlength);           //����������Ϣ
        goto CabinetSelfDownDataProcess;
      }
      else
      {
        Cabinet_Send((unsigned char*)ampframe,framlength);           //����������Ϣ
        return;
      }
    }
    else if(CabPort == Port)    //��ӿڽ��յ��·�����Ҫ����ַ�ж�
    {
      if(AMP.SwData.ID  ==  ampframe->msg.addr.address1)
      {
        ackFrame(CabPort,1); //����Ӧ��
        //goto CabinetSelfDownDataProcess;
      }
      else if(0xFF  ==  ampframe->msg.addr.address1)  //�㲥����
      {
        //goto CabinetSelfDownDataProcess;
      }
      else    //���������ݣ��˳���������
      {
        return;
      }
      goto CabinetSelfDownDataProcess;
    }
    else if(LayPort == Port)
    {
      CMD_Process((unsigned char*)ampframe,framlength);
    }    
  }
  //-------------------------�ϴ�����
  else
  {    
    if(PcPort == Port)    //PC��ֻ�·���Ϣ
    {
      return;
    }
    else if(CabPort == Port)  //��ӿڽ��յ����ݣ����Ϊ��������Ӧ�����ϴ���PC�˿ڣ�����Ǹ����ϴ���PC�˿ڣ���Ӧ��
    {
      if(AMP.SwData.MainFlg)
      {
        ackFrame(Port,0);   //����Ӧ��
      }
      PCnet_Send((unsigned char*)ampframe,framlength);     //��PC������Ϣ
      return;
    }
    else if(LayPort == Port)
    {
      ackFrame(Port,0);   //����Ӧ��
      goto CabinetSelfUpDataProcess;
    }
  }
  
  return;
  
  //----------------------�·���Ϣ��Ҫ������ʱ��ִ�д˹���
  CabinetSelfDownDataProcess:     //������յ����ϼ��·���Ϣ���������ݵڶ�����ַȷ���Ƿ���Ҫת��
  
  //---------------------������Ϣ�Ƿ���Ҫת������
  if(0x00 != ampframe->msg.addr.address2)   //���ַ��Ϊ0��ʾ��Ҫת��
  {
    Laynet_Send((unsigned char*)ampframe,framlength);     //����巢����Ϣ
  }
  //---------------------����Ҫת������Ϣ������Թ���ư�
  else
  {
    CMD_Process(pBuffer,framlength);
  }
  return;
  
  //----------------------�ϱ����͵���Ϣaddress1Ϊ0ʱ��ִ�д˹���
  CabinetSelfUpDataProcess:     //���յ����ϱ�����Ϣ����Ҫ���ӹ��ַ���������Ϊ�������ϴ���PC�����Ϊ�������ϴ�������
  //----------------------��������
  ampframe->msg.addr.address1 = AMP.SwData.ID;    //����ID
  ampframe->msg.cmd.dir       = 1;                //���䷽���趨Ϊ�ϴ�ģʽ
  SetCrc((unsigned char*)ampframe,&framlength);   //���¼���CRC
  //----------------------�����Ƿ�Ϊ����ѡ����Ϣ����ӿ�
  if(AMP.SwData.MainFlg)        //����ͨ��PC�ӿ��ϴ�
  {
    PCnet_Send((unsigned char*)ampframe,framlength);     //��PC������Ϣ
  }
  else    //�����ϴ���PC�˿ں͸���ӿ�
  {
    PCnet_Send((unsigned char*)ampframe,framlength);     //��PC������Ϣ
    Cabinet_Send((unsigned char*)ampframe,framlength);  //ͨ����ӿ�����������Ϣ
  }
  return;
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
void CMD_Process(unsigned char* pBuffer,unsigned short length)
{
  unsigned  short datalen     = 0; 
  stampphydef* ampframe       = NULL;
  eucmddef*    cmd  = NULL;
  
  ampframe  = (stampphydef*)pBuffer;
  cmd = (eucmddef*)&ampframe->msg.cmd;
  //---------------------------��λ���·�����������
  if(ICR ==  (*cmd&Down)) //���λΪ0��ʾ�����·�
  {
    datalen = ampframe->msg.length-4;   //��һ����λ������ַλ����
    CardPort_Send(ampframe->msg.data,datalen);   //���������ӿڷ�����
    return;
  }
  //---------------------------��������
  if(CTL ==  (*cmd&Down)) //���λΪ0��ʾ�����·�
  {
    if(0  ==  ampframe->msg.data[0])    //0Ϊ��������
    {
      UnLock;   //����
    }
    else
    {
      ResLock;  //�ͷ���
    }
    return;
  }
  //---------------------------�����������
  if(LED ==  (*cmd&Down)) //���λΪ0��ʾ�����·�
  {
    if(0  !=  ampframe->msg.data[0])    //1Ϊ��LED
    {
      BackLightOn;   //��LED
    }
    else
    {
      BackLightOff;  //��LED
    }
    return;
  }
}
/*******************************************************************************
*������			:	function
*��������		:	function
*����				: 
*����ֵ			:	dir:0����Ӧ��1����Ӧ��
*�޸�ʱ��		:	��
*�޸�˵��		:	��
*ע��				:	wegam@sina.com
*******************************************************************************/
void ackFrame(enCCPortDef Port,unsigned char dir)
{
  switch(Port)
  {
    case  NonPort   : return;   //������ִ��
    case  PcPort    : AMP.AckQ.PcAck  = 1;
                      AMP.AckQ.PcDir  = dir;
      break;
    case  CabPort   : AMP.AckQ.CabAck  = 1;
                      AMP.AckQ.CabDir  = dir;
      break;
    case  LayPort   : AMP.AckQ.LayAck  = 1;
                      AMP.AckQ.LayDir  = dir;
      break;
    //case  CardPort  : AMP.AckQ.CardAck  = 1;
    //                    AMP.AckQ.CardDir  = dir;
      //break;
    default :return;      //������ִ�� 
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
unsigned short Releas_OneBuffer(enCCPortDef Port)
{
  unsigned  char  i  = 0;
  stTxdef* Txd  = NULL;
  unsigned  char*  ReSendCount;      //PC�ϴ��ط�����
  unsigned  short*  SendTime=NULL;
  
  switch(Port)
  {
    case  NonPort   : return 0;   //������ִ��
    case  PcPort    : ReSendCount = &AMP.ReSend.PcCount;
                      Txd=AMP.buffer.PcTx;    //PC�ӿڷ��ͻ���
                      SendTime  = &AMP.Time.PcSendTime;
      break;
    case  CabPort   : ReSendCount = &AMP.ReSend.CabCount;
                      Txd=AMP.buffer.CabTx;   //��ӿڷ��ͻ���
                      SendTime  = &AMP.Time.CabSendTime;
      break;
    case  LayPort   : ReSendCount = &AMP.ReSend.LayCount;
                      Txd=AMP.buffer.LayTx;   //��ӿڷ��ͻ���
                      SendTime  = &AMP.Time.LaySendTime;
      break;
    case  CardPort  : ReSendCount = &AMP.ReSend.CardCount;
                      Txd=AMP.buffer.CardTx;  //�������ӿڷ��ͻ���
                      SendTime  = &AMP.Time.CardSendTime;
      break;
    default :return 0;      //������ִ�� 
  }
  for(i=0;i<arrysize;i++)
  {
    if(Txd[i].arry>0)
    {
      Txd[i].arry--;
      *SendTime  = SendNopTime;   //�ͷ�һ�������ȴ�SendNopTimeʱ����ٷ���һ֡
      *ReSendCount  = 0;
    }
  }
  return  0;
}

/*******************************************************************************
*������			:	function
*��������		:	AddSendData
*����				: 
*����ֵ			:	��
*�޸�ʱ��		:	��
*�޸�˵��		:	��
*ע��				:	wegam@sina.com
*******************************************************************************/
unsigned short AddSendBuffer(enCCPortDef Port,unsigned char* pBuffer,unsigned short length)
{
  unsigned  char  i  = 0;
  unsigned  char  lastarry  = 0;
  
  stTxdef* Txd  = NULL;
  
  switch(Port)
  {
    case  NonPort   : return 0;   //������ִ��
    case  PcPort    : Txd=AMP.buffer.PcTx;    //PC�ӿڷ��ͻ���
      break;
    case  CabPort   : Txd=AMP.buffer.CabTx;   //��ӿڷ��ͻ���
      break;
    case  LayPort   : Txd=AMP.buffer.LayTx;   //��ӿڷ��ͻ���
      break;
    case  CardPort  : Txd=AMP.buffer.CardTx;  //�������ӿڷ��ͻ���
      break;
    default :return 0;      //������ִ�� 
  }
  //-------------------------����ǰ�����Ͷ��б��(��β��)
  for(i=0;i<arrysize;i++)
  {
    if(Txd[i].arry>lastarry)
    {
      lastarry  = Txd[i].arry;
      //---------------------��鷢�Ͷ������Ƿ�����ͬ��ָ�����У����˳�
      if(0  ==  memcmp(Txd[i].data,pBuffer,length)) //�Ƚ���ͬ
      {
        if(length ==  Txd[i].size)    //�����ͳ���һ��
          return  length;
      }
    }
  }
  if(lastarry>=arrysize)  //������
    return 0;     //������ִ��
  lastarry=lastarry+1;      //���Ķ��б��
  //-------------------------�����ݴ洢���ն���
  for(i=0;i<arrysize;i++)
  {
    if(0  ==  Txd[i].arry)  //0��ű�ʾ��Ϊ�ջ���
    {
      memcpy(Txd[i].data,pBuffer,length);
      Txd[i].arry = lastarry;             //�˻����ڷ��Ͷ����е�����
      Txd[i].size = length; 
      return  length;
    }
  }
  return  0;
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
  if(1  ==  AMP.Flag.LockFlg) //����״̬��δ��
  {
    UnLock;
    LayPowerOn;
    BackLightOn;
  }
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
//=================================�����ӿ�End=============================================================


//=================================Ӳ���ӿ�ST==============================================================
/*******************************************************************************
*������			:	function
*��������		:	function
*����				: 
*����ֵ			:	��
*�޸�ʱ��		:	��
*�޸�˵��		:	��
*ע��				:	wegam@sina.com
*******************************************************************************/
void Receive_Server(void)
{
  unsigned short RxNum  = 0;
  unsigned char rxd[ccsize]={0};
  //==========================================================���ղ�ѯ
  //---------------------PC�ӿ� USART1
  RxNum = USART_ReadBufferIDLE(USART1,rxd);
  if(RxNum)
  {
    Msg_Process(PcPort,rxd,RxNum);                //����Ϣ����
  }
  //---------------------����ӿ� UART4
  RxNum = RS485_ReadBufferIDLE(&stRS485Cb,rxd);
  if(RxNum)
  {
    Msg_Process(CabPort,rxd,RxNum);
  }  
  //---------------------���ӿ� USART2
  RxNum = RS485_ReadBufferIDLE(&stRS485Ly,rxd);
  if(RxNum)
  {
    Msg_Process(LayPort,rxd,RxNum);              //����Ϣ����
  }
  //---------------------�������ӿ� USART3
  RxNum = USART_ReadBufferIDLE(USART3,rxd);
  if(RxNum)
  {
    Msg_Process(CardPort,rxd,RxNum);
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
unsigned short HW_SendBuff(enCCPortDef Port,unsigned char* pBuffer,unsigned short length)
{ 
  unsigned  short   sendedlen = 0;
  switch(Port)
  {
    case  NonPort   : return 0;   //������ִ��
    case  PcPort    : sendedlen = USART_DMASend(USART1,pBuffer,length);
      break;
    case  CabPort   : sendedlen = RS485_DMASend(&stRS485Cb,pBuffer,length);	//RS485-DMA���ͳ���
      break;
    case  LayPort   : sendedlen = RS485_DMASend(&stRS485Ly,pBuffer,length);	//RS485-DMA���ͳ���
      break;
    case  CardPort  : sendedlen = USART_DMASend(USART3,pBuffer,length);
      break;
    default :return 0;      //������ִ��
  }

  return  sendedlen;
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
void SwitchID_Server(void)
{
  if(AMP.Time.swicthidtime++>2000) //2����һ�β���
  {
    unsigned  char  tempid  = 0;
    unsigned  char* tempbc  = (unsigned  char*)&AMP.SwData;
    AMP.Time.swicthidtime  = 0;
    tempid  = SWITCHID_ReadLeft(&stSwitch);
    if(*tempbc  != tempid)
    {
      *tempbc  = tempid;
//      AMP01_Configuration();    //�������ÿ��ư�
      SwitchID_Configuration();  
      GenyConfiguration();   //����ӿ����ã����⣬������Դ����    
      COMM_Configuration();
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
void LockServer(void)
{
  static unsigned  short locktime = 0;
  if(GetLockSts)    //��δ��
  {
    locktime  = 0;
    AMP.Flag.LockFlg    = 1;
    AMP.Flag.LayPownOn  = 0;
    BackLightOff;
    LayPowerOff;
  }
  else
  {
    LayPowerOn;
    BackLightOn;
    if(locktime++>50) //�ӳ�50ms�ͷ�������
    {
      ResLock;
    }
    if(locktime++>500)  //�ӳ�100ms�򿪲㹩��
    {
      AMP.Flag.LockFlg    = 0;
      AMP.Flag.LayPownOn  = 1;
      locktime  = 0;
      BackLightOn;      //�򿪱���      
    }
  }    
}
//=================================Ӳ���ӿ�End=============================================================


//=================================���ú���ST==============================================================

/*******************************************************************************
*������			:	function
*��������		:	function
*����				: 
*����ֵ			:	��
*�޸�ʱ��		:	��
*�޸�˵��		:	��
*ע��				:	wegam@sina.com
*******************************************************************************/
void COMM_Configuration(void)
{
  //-----------------------------PC�ӿ�USART1
  USART_DMA_ConfigurationNR	(USART1,19200,ccsize);	//USART_DMA����--��ѯ��ʽ�������ж�
  
  //-----------------------------�������ӿ�USART3
  if(0==AMP.SwData.ICreadFlg) //sw2δ���룬Ĭ��19200
    USART_DMA_ConfigurationNR	(USART3,19200,ccsize);	//USART_DMA����--��ѯ��ʽ�������ж�
  else
    USART_DMA_ConfigurationNR	(USART3,9600,ccsize);	//USART_DMA����--��ѯ��ʽ�������ж�

  //-----------------------------���ӿ�USART2
  stRS485Ly.USARTx  = USART2;
  stRS485Ly.RS485_CTL_PORT  = GPIOA;
  stRS485Ly.RS485_CTL_Pin   = GPIO_Pin_1;
  RS485_DMA_ConfigurationNR			(&stRS485Ly,19200,ccsize);	//USART_DMA����--��ѯ��ʽ�������ж�,������Ĭ��Ϊ����״̬
  //-----------------------------����ӿ�UART4
  stRS485Cb.USARTx  = UART4;
  stRS485Cb.RS485_CTL_PORT  = GPIOC;
  stRS485Cb.RS485_CTL_Pin   = GPIO_Pin_12;
  RS485_DMA_ConfigurationNR			(&stRS485Cb,19200,ccsize);	//USART_DMA����--��ѯ��ʽ�������ж�,������Ĭ��Ϊ����״̬
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
void SwitchID_Configuration(void)
{
  unsigned  char* tempsw = NULL;
  if(AMP.Flag.CabBD)  //����ư�
  {
    stSwitch.NumOfSW	=	8;
    
    stSwitch.SW1_PORT	=	GPIOC;
    stSwitch.SW1_Pin	=	GPIO_Pin_0;
    
    stSwitch.SW2_PORT	=	GPIOC;
    stSwitch.SW2_Pin	=	GPIO_Pin_1;
    
    stSwitch.SW3_PORT	=	GPIOC;
    stSwitch.SW3_Pin	=	GPIO_Pin_2;
    
    stSwitch.SW4_PORT	=	GPIOC;
    stSwitch.SW4_Pin	=	GPIO_Pin_3;
    
    stSwitch.SW5_PORT	=	GPIOC;
    stSwitch.SW5_Pin	=	GPIO_Pin_4;
    
    stSwitch.SW6_PORT	=	GPIOC;
    stSwitch.SW6_Pin	=	GPIO_Pin_5;
    
    stSwitch.SW7_PORT	=	GPIOC;
    stSwitch.SW7_Pin	=	GPIO_Pin_6;
    
    stSwitch.SW8_PORT	=	GPIOC;
    stSwitch.SW8_Pin	=	GPIO_Pin_7;
  }
  else if(AMP.Flag.LayBD) //����ư�
  {
    stSwitch.NumOfSW	=	8;
    
    stSwitch.SW1_PORT	=	GPIOA;
    stSwitch.SW1_Pin	=	GPIO_Pin_7;
    
    stSwitch.SW2_PORT	=	GPIOA;
    stSwitch.SW2_Pin	=	GPIO_Pin_6;
    
    stSwitch.SW3_PORT	=	GPIOA;
    stSwitch.SW3_Pin	=	GPIO_Pin_5;
    
    stSwitch.SW4_PORT	=	GPIOA;
    stSwitch.SW4_Pin	=	GPIO_Pin_4;
    
    stSwitch.SW5_PORT	=	GPIOB;
    stSwitch.SW5_Pin	=	GPIO_Pin_11;
    
    stSwitch.SW6_PORT	=	GPIOB;
    stSwitch.SW6_Pin	=	GPIO_Pin_10;
    
    stSwitch.SW7_PORT	=	GPIOB;
    stSwitch.SW7_Pin	=	GPIO_Pin_2;
    
    stSwitch.SW8_PORT	=	GPIOB;
    stSwitch.SW8_Pin	=	GPIO_Pin_1;
  }
	SwitchIdInitialize(&stSwitch);						//

	
  tempsw  = (unsigned  char*)&AMP.SwData;
  *tempsw  = SWITCHID_ReadLeft(&stSwitch);
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
void GenyConfiguration(void)
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
  LayPowerOn;
}
//=================================���ú���End=============================================================


//=================================ʱ�亯��ST==============================================================

/*******************************************************************************
*������			:	function
*��������		:	function
*����				: 
*����ֵ			:	��
*�޸�ʱ��		:	��
*�޸�˵��		:	��
*ע��				:	wegam@sina.com
*******************************************************************************/
void Tim_Server(void)
{
  //----------------PC����
  if(AMP.Time.PcSendTime>0)
  {
    AMP.Time.PcSendTime--;
  }
  //----------------����
  if(AMP.Time.CabSendTime>0)
  {
    AMP.Time.CabSendTime--;
  }
  //----------------�㷢��
  if(AMP.Time.LaySendTime>0)
  {
    AMP.Time.LaySendTime--;
  }
  //----------------����������
  if(AMP.Time.CardSendTime>0)
  {
    AMP.Time.CardSendTime--;
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
void AMPdelaymS(unsigned  short time)
{
  SysTick_DeleymS(time);				//SysTick��ʱnmS
}
#endif