/*
 * THE FOLLOWING FIRMWARE IS PROVIDED: (1) "AS IS" WITH NO WARRANTY; AND 
 * (2)TO ENABLE ACCESS TO CODING INFORMATION TO GUIDE AND FACILITATE CUSTOMER.
 * CONSEQUENTLY, SEMTECH SHALL NOT BE HELD LIABLE FOR ANY DIRECT, INDIRECT OR
 * CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE CONTENT
 * OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING INFORMATION
 * CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
 * 
 * Copyright (C) SEMTECH S.A.
 */
/*! 
 * \file       sx1276.c
 * \brief      SX1276 RF chip driver
 *
 * \version    2.0.0 
 * \date       May 6 2013
 * \author     Gregory Cristian
 *
 * Last modified by Miguel Luis on Jun 19 2013
 */
#include "platform.h"
#include "radio.h"

#if defined( USE_SX1276_RADIO )

#include "sx1276.h"

#include "sx1276-Hal.h"
#include "sx1276-Fsk.h"
#include "sx1276-LoRa.h"

/*!
 * SX1276 registers variable
 */
uint8_t SX1276Regs[0x70];		//�Ĵ�������

static bool LoRaOn = false;
static bool LoRaOnState = false;


/*******************************************************************************
*������			:	function
*��������		:	��������˵��
*����				: 
*����ֵ			:	��
*�޸�ʱ��		:	��
*�޸�˵��		:	��
*ע��				:	wegam@sina.com
*******************************************************************************/
void SX1276Init( void )		//��ʼ��SX1276--GPIO��ʼ�����Ĵ�����ʼ��������ģʽ��ʼ����оƬ�������á�������ɺ�������״̬
{
    // Initialize FSK and LoRa registers structure
    SX1276 = ( tSX1276* )SX1276Regs;				//FSKģʽ�Ĵ����ṹ��
    SX1276LR = ( tSX1276LR* )SX1276Regs;		//LoRaģʽ�Ĵ����ṹ��

    SX1276InitIo( );			//SX1276 GPIO����		sx1276-Hal.c	NSS��DIO0~DIO5����
    
    SX1276Reset( );				//��λSX1276������NREST��100uSȻ�����ߣ��ȴ�5mSоƬ�ȶ�

    // REMARK: After radio reset the default modem is FSK
		
		//���ݹ���ģʽ������Ӧ����
#if ( LORA == 0 ) 	//FSKģʽ

    LoRaOn = false;
    SX1276SetLoRaOn( LoRaOn );	//����ΪLoRaģʽ����FSKģʽ
    // Initialize FSK modem
    SX1276FskInit( );						//��������

#else

    LoRaOn = true;
    SX1276SetLoRaOn( LoRaOn );	//����ΪLoRaģʽ����FSKģʽ
    // Initialize LoRa modem
    SX1276LoRaInit( );					//LoRaģʽ��������---������ɺ�������״̬
    
#endif

}
/*******************************************************************************
*������			:	function
*��������		:	SX1276��λ
							������NREST ����100uS,Ȼ������NREST����λ���
							��λ��ɺ���Ҫ�ȴ�����5mSоƬ�ȶ��ٿ�ʼʹ��оƬ
*����				: 
*����ֵ			:	��
*�޸�ʱ��		:	��
*�޸�˵��		:	��
*ע��				:	wegam@sina.com
*******************************************************************************/
void SX1276Reset( void )		//��λSX1276������NREST��100uSȻ�����ߣ��ȴ�5mSоƬ�ȶ�
{
	uint32_t startTick;
	
    SX1276SetReset( RADIO_RESET_ON );		//SX1276��λ--����NREST���ƹܽż���������оƬNREST�ţ�  ����7(NREST) �ĵ�ƽ����100΢��
    
    // Wait 1ms
		startTick = GET_TICK_COUNT( );			//��ȡSYSTICK��ʱ����ֵ
    while( ( GET_TICK_COUNT( ) - startTick ) < TICK_RATE_MS( 1 ) );  	//�ȴ�1MS��ʱ  

    SX1276SetReset( RADIO_RESET_OFF );	//�رո�λ---��λ���
    
    // Wait 6ms
    startTick = GET_TICK_COUNT( );			//�ȴ�оƬ�ȶ���ʹ��оƬ
    while( ( GET_TICK_COUNT( ) - startTick ) < TICK_RATE_MS( 6 ) );    
}
/*******************************************************************************
*������			:	function
*��������		:	��������˵��
*����				: 
*����ֵ			:	��
*�޸�ʱ��		:	��
*�޸�˵��		:	��
*ע��				:	wegam@sina.com
*******************************************************************************/
void SX1276SetLoRaOn( bool enable )		//����ΪLoRaģʽ����FSKģʽ
{
    if( LoRaOnState == enable )
    {
        return;
    }
    LoRaOnState = enable;
    LoRaOn = enable;

    if( LoRaOn == true )			//=====================LoRaģʽ
    {
        SX1276LoRaSetOpMode( RFLR_OPMODE_SLEEP );				//����Ϊ˯��ģʽ��ֻ����˯��/����ģʽ��д���üĴ�����
        
        SX1276LR->RegOpMode = ( SX1276LR->RegOpMode & RFLR_OPMODE_LONGRANGEMODE_MASK ) | RFLR_OPMODE_LONGRANGEMODE_ON;		//����ΪLoRaģʽ
        SX1276Write( REG_LR_OPMODE, SX1276LR->RegOpMode );		//д�Ĵ����������Ĵ�����ַ+���ݣ�д�����ò���
        
        SX1276LoRaSetOpMode( RFLR_OPMODE_STANDBY );
                                        // RxDone               RxTimeout                   FhssChangeChannel           CadDone
        SX1276LR->RegDioMapping1 = RFLR_DIOMAPPING1_DIO0_00 | RFLR_DIOMAPPING1_DIO1_00 | RFLR_DIOMAPPING1_DIO2_00 | RFLR_DIOMAPPING1_DIO3_00;
                                        // CadDetected          ModeReady
        SX1276LR->RegDioMapping2 = RFLR_DIOMAPPING2_DIO4_00 | RFLR_DIOMAPPING2_DIO5_00;
        SX1276WriteBuffer( REG_LR_DIOMAPPING1, &SX1276LR->RegDioMapping1, 2 );
        
        SX1276ReadBuffer( REG_LR_OPMODE, SX1276Regs + 1, 0x70 - 1 );
    }
    else												//=====================FSKģʽ
    {
        SX1276LoRaSetOpMode( RFLR_OPMODE_SLEEP );
        
        SX1276LR->RegOpMode = ( SX1276LR->RegOpMode & RFLR_OPMODE_LONGRANGEMODE_MASK ) | RFLR_OPMODE_LONGRANGEMODE_OFF;
        SX1276Write( REG_LR_OPMODE, SX1276LR->RegOpMode );
        
        SX1276LoRaSetOpMode( RFLR_OPMODE_STANDBY );
        
        SX1276ReadBuffer( REG_OPMODE, SX1276Regs + 1, 0x70 - 1 );
    }
}
/*******************************************************************************
*������			:	function
*��������		:	��������˵��
*����				: 
*����ֵ			:	��
*�޸�ʱ��		:	��
*�޸�˵��		:	��
*ע��				:	wegam@sina.com
*******************************************************************************/
bool SX1276GetLoRaOn( void )		//��ȡLoRaģʽ״̬
{
    return LoRaOn;
}
/*******************************************************************************
*������			:	function
*��������		:	��������˵��
*����				: 
*����ֵ			:	��
*�޸�ʱ��		:	��
*�޸�˵��		:	��
*ע��				:	wegam@sina.com
*******************************************************************************/
void SX1276SetOpMode( uint8_t opMode )	//����SX1276����ģʽ
{
    if( LoRaOn == false )
    {
        SX1276FskSetOpMode( opMode );
    }
    else
    {
        SX1276LoRaSetOpMode( opMode );
    }
}
/*******************************************************************************
*������			:	function
*��������		:	��������˵��
*����				: 
*����ֵ			:	��
*�޸�ʱ��		:	��
*�޸�˵��		:	��
*ע��				:	wegam@sina.com
*******************************************************************************/
uint8_t SX1276GetOpMode( void )			//��ȡSX1276����ģʽ
{
    if( LoRaOn == false )
    {
        return SX1276FskGetOpMode( );
    }
    else
    {
        return SX1276LoRaGetOpMode( );
    }
}

/*******************************************************************************
*������			:	function
*��������		:	��������˵��
*����				: 
*����ֵ			:	��
*�޸�ʱ��		:	��
*�޸�˵��		:	��
*ע��				:	wegam@sina.com
*******************************************************************************/
uint8_t SX1276ReadRxGain( void )		//��ȡ��ǰ��RX��������
{
    if( LoRaOn == false )
    {
        return SX1276FskReadRxGain( );
    }
    else
    {
        return SX1276LoRaReadRxGain( );
    }
}
/*******************************************************************************
*������			:	function
*��������		:	��������˵��
*����				: 
*����ֵ			:	��
*�޸�ʱ��		:	��
*�޸�˵��		:	��
*ע��				:	wegam@sina.com
*******************************************************************************/
double SX1276ReadRssi( void )		//�����Ͷ�ȡ��ǰRSSIֵ
{
    if( LoRaOn == false )
    {
        return SX1276FskReadRssi( );
    }
    else
    {
        return SX1276LoRaReadRssi( );
    }
}
/*******************************************************************************
*������			:	function
*��������		:	��������˵��
*����				: 
*����ֵ			:	��
*�޸�ʱ��		:	��
*�޸�˵��		:	��
*ע��				:	wegam@sina.com
*******************************************************************************/
uint8_t SX1276GetPacketRxGain( void )			//��ȡ���հ�ʱ������RX����ֵ��
{
    if( LoRaOn == false )
    {
        return SX1276FskGetPacketRxGain(  );
    }
    else
    {
        return SX1276LoRaGetPacketRxGain(  );
    }
}
/*******************************************************************************
*������			:	function
*��������		:	��������˵��
*����				: 
*����ֵ			:	��
*�޸�ʱ��		:	��
*�޸�˵��		:	��
*ע��				:	wegam@sina.com
*******************************************************************************/
int8_t SX1276GetPacketSnr( void )		//��ȡ���հ�ʱ������SNR(�����)ֵ��
{
    if( LoRaOn == false )
    {
         while( 1 )
         {
             // Useless in FSK mode
             // Block program here
         }
    }
    else
    {
        return SX1276LoRaGetPacketSnr(  );
    }
}
/*******************************************************************************
*������			:	function
*��������		:	��������˵��
*����				: 
*����ֵ			:	��
*�޸�ʱ��		:	��
*�޸�˵��		:	��
*ע��				:	wegam@sina.com
*******************************************************************************/
double SX1276GetPacketRssi( void )			//��ȡ���հ�ʱ������RSSIֵ��
{
    if( LoRaOn == false )
    {
        return SX1276FskGetPacketRssi(  );
    }
    else
    {
        return SX1276LoRaGetPacketRssi( );
    }
}
/*******************************************************************************
*������			:	function
*��������		:	��������˵��
*����				: 
*����ֵ			:	��
*�޸�ʱ��		:	��
*�޸�˵��		:	��
*ע��				:	wegam@sina.com
*******************************************************************************/
uint32_t SX1276GetPacketAfc( void )				//��ȡ���հ�ʱ������AFCֵ��
{
    if( LoRaOn == false )
    {
        return SX1276FskGetPacketAfc(  );
    }
    else
    {
         while( 1 )
         {
             // Useless in LoRa mode
             // Block program here
         }
    }
}
/*******************************************************************************
*������			:	function
*��������		:	��������˵��
*����				: 
*����ֵ			:	��
*�޸�ʱ��		:	��
*�޸�˵��		:	��
*ע��				:	wegam@sina.com
*******************************************************************************/
void SX1276StartRx( void )				//������Ƶ����Ϊ����ģʽ���ȴ�һ�����ݰ�
{
    if( LoRaOn == false )
    {
        SX1276FskSetRFState( RF_STATE_RX_INIT );
    }
    else
    {
        SX1276LoRaSetRFState( RFLR_STATE_RX_INIT );
    }
}
/*******************************************************************************
*������			:	function
*��������		:	��������˵��
*����				: 
*����ֵ			:	��
*�޸�ʱ��		:	��
*�޸�˵��		:	��
*ע��				:	wegam@sina.com
*******************************************************************************/
void SX1276GetRxPacket( void *buffer, uint16_t *size )	//��ȡ��ǰ���ջ������ĸ���
{
    if( LoRaOn == false )
    {
        SX1276FskGetRxPacket( buffer, size );
    }
    else
    {
        SX1276LoRaGetRxPacket( buffer, size );
    }
}
/*******************************************************************************
*������			:	function
*��������		:	��������˵��
*����				: 
*����ֵ			:	��
*�޸�ʱ��		:	��
*�޸�˵��		:	��
*ע��				:	wegam@sina.com
*******************************************************************************/
void SX1276SetTxPacket( const void *buffer, uint16_t size )	//����Ҫ����Ļ������ĸ�������ʼ���䡣
{
    if( LoRaOn == false )
    {
        SX1276FskSetTxPacket( buffer, size );
    }
    else
    {
        SX1276LoRaSetTxPacket( buffer, size );
    }
}
/*******************************************************************************
*������			:	function
*��������		:	��������˵��
*����				: 
*����ֵ			:	��
*�޸�ʱ��		:	��
*�޸�˵��		:	��
*ע��				:	wegam@sina.com
*******************************************************************************/
uint8_t SX1276GetRFState( void )		//��ȡ��ǰ��Ƶ״̬
{
    if( LoRaOn == false )
    {
        return SX1276FskGetRFState( );
    }
    else
    {
        return SX1276LoRaGetRFState( );
    }
}
/*******************************************************************************
*������			:	function
*��������		:	��������˵��
*����				: 
*����ֵ			:	��
*�޸�ʱ��		:	��
*�޸�˵��		:	��
*ע��				:	wegam@sina.com
*******************************************************************************/
void SX1276SetRFState( uint8_t state )		//�����µ���Ƶ״̬��
{
    if( LoRaOn == false )
    {
        SX1276FskSetRFState( state );
    }
    else
    {
        SX1276LoRaSetRFState( state );
    }
}
/*******************************************************************************
*������			:	function
*��������		:	��������˵��
*����				: 
*����ֵ			:	��
*�޸�ʱ��		:	��
*�޸�˵��		:	��
*ע��				:	wegam@sina.com
*******************************************************************************/
uint32_t SX1276Process( void )					//����SX1276�Ĺ���ģʽ����RX��Tx��״̬
{
    if( LoRaOn == false )
    {
        return SX1276FskProcess( );			//FSKģʽ
    }
    else
    {
        return SX1276LoRaProcess( );		//LoRaģʽ
    }
}

#endif // USE_SX1276_RADIO
