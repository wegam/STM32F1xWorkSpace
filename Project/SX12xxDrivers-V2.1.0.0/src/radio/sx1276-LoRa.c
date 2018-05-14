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
 * \file       sx1276-LoRa.c
 * \brief      SX1276 RF chip driver mode LoRa
 *
 * \version    2.0.0 
 * \date       May 6 2013
 * \author     Gregory Cristian
 *
 * Last modified by Miguel Luis on Jun 19 2013
 */
#include <string.h>

#include "platform.h"

#if defined( USE_SX1276_RADIO )

#include "radio.h"

#include "sx1276-Hal.h"
#include "sx1276.h"

#include "sx1276-LoRaMisc.h"
#include "sx1276-LoRa.h"

/*!
 * Constant values need to compute the RSSI value
 */
#define RSSI_OFFSET_LF                              -164.0
#define RSSI_OFFSET_HF                              -157.0

/*!
 * Frequency hopping frequencies table	//跳频频率列表
 */
const int32_t HoppingFrequencies[] =		//跳频频率
{
    436500000,
    433500000,
    436500000,
    437500000,
    437500000,
    439000000,
    433000000,
    436000000,
    432500000,
    436000000,
    435000000,
    439500000,
    433000000,
    438500000,
    438500000,
    432500000,
    431500000,
    436500000,
    432500000,
    432000000,
    434000000,
    433500000,
    433000000,
    432000000,
    436000000,
    430000000,
    430000000,
    432500000,
    431000000,
    432000000,
    439500000,
    436000000,
    432000000,
    438000000,
    435500000,
    438000000,
    437500000,
    436500000,
    428500000,
    426000000,
    425500000,
    426000000,
    23000000,
    425000000,
    425000000,
    423000000,
    427000000,
    420000000,
    426500000,
    425500000,
    421000000,
};

///*!
// * Frequency hopping frequencies table	//跳频频率列表
// */
//const int32_t HoppingFrequencies[] =		//跳频频率
//{
//    916500000,
//    923500000,
//    906500000,
//    917500000,
//    917500000,
//    909000000,
//    903000000,
//    916000000,
//    912500000,
//    926000000,
//    925000000,
//    909500000,
//    913000000,
//    918500000,
//    918500000,
//    902500000,
//    911500000,
//    926500000,
//    902500000,
//    922000000,
//    924000000,
//    903500000,
//    913000000,
//    922000000,
//    926000000,
//    910000000,
//    920000000,
//    922500000,
//    911000000,
//    922000000,
//    909500000,
//    926000000,
//    922000000,
//    918000000,
//    925500000,
//    908000000,
//    917500000,
//    926500000,
//    908500000,
//    916000000,
//    905500000,
//    916000000,
//    903000000,
//    905000000,
//    915000000,
//    913000000,
//    907000000,
//    910000000,
//    926500000,
//    925500000,
//    911000000,
//};

// Default settings
tLoRaSettings LoRaSettings =
{
    433000000,        // RFFrequency无线频率：SX1276-137~1020MHz；SX1277-137~1020MHz；SX1278-137~525MHz
    20,               // Power
    9,                // SignalBw信号带宽 [0: 7.8kHz, 1: 10.4 kHz, 2: 15.6 kHz, 3: 20.8 kHz, 4: 31.2 kHz,
                      // 5: 41.6 kHz, 6: 62.5 kHz, 7: 125 kHz, 8: 250 kHz, 9: 500 kHz, other: Reserved]
    7,                // SpreadingFactor扩频因子 [6: 64, 7: 128, 8: 256, 9: 512, 10: 1024, 11: 2048, 12: 4096  chips]
    2,                // ErrorCoding误差编码 [1: 4/5, 2: 4/6, 3: 4/7, 4: 4/8]
    true,             // CrcOn [0: OFF, 1: ON]
    false,            // ImplicitHeaderOn序头模式 [0: OFF, 1: ON]
    1,                // RxSingleOn接收模式中的single模式开关，0代表continue模式 [0: Continuous, 1 Single]
    0,                // FreqHopOn跳频开关 [0: OFF, 1: ON]
    4,                // HopPeriod Hops every frequency hopping period symbols跳频周期
    100,              // TxPacketTimeout	发送超时时间
    100,              // RxPacketTimeout	接收超时时间
    128,              // PayloadLength (used for implicit header mode)	负载数据长度
};

/*!
 * SX1276 LoRa registers variable
 */
tSX1276LR* SX1276LR;		//Lora模式寄存器结体体---全局变量

/*!
 * Local RF buffer for communication support
 */
static uint8_t RFBuffer[RF_BUFFER_SIZE];		//RF收发缓冲区

/*!
 * RF state machine variable
 */
static uint8_t RFLRState = RFLR_STATE_IDLE;		//初始化无线状态--空闲状态

/*!
 * Rx management support variables
 */
static uint16_t RxPacketSize = 0;
static int8_t RxPacketSnrEstimate;
static double RxPacketRssiValue;
static uint8_t RxGain = 1;
static uint32_t RxTimeoutTimer = 0;
/*!
 * PacketTimeout Stores the Rx window time value for packet reception
 */
static uint32_t PacketTimeout;

/*!
 * Tx management support variables
 */
static uint16_t TxPacketSize = 0;
/*******************************************************************************
*函数名			:	function
*功能描述		:	Lora初始化
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
void SX1276LoRaInit( void )		//Lora初始化 //LoRa模式参数配置
{
    RFLRState = RFLR_STATE_IDLE;		//状态值：空闲

    SX1276LoRaSetDefaults( );				//默认配置--读版本ID
    
    SX1276ReadBuffer( REG_LR_OPMODE, SX1276Regs + 1, 0x70 - 1 );	//Lora模式获取寄存器地址，存入SX1276Regs
    
    SX1276LR->RegLna = RFLR_LNA_GAIN_G1;													//G1最大增益，SX1276LR指针指向SX1276Regs

    SX1276WriteBuffer( REG_LR_OPMODE, SX1276Regs + 1, 0x70 - 1 );	//更新增益值

    // set the RF settings 
    SX1276LoRaSetRFFrequency( LoRaSettings.RFFrequency );					//设置射频频率--将频率参数写入指定寄存器
    SX1276LoRaSetSpreadingFactor( LoRaSettings.SpreadingFactor ); // SF6 only operates in implicit header mode.
    SX1276LoRaSetErrorCoding( LoRaSettings.ErrorCoding );
    SX1276LoRaSetPacketCrcOn( LoRaSettings.CrcOn );
    SX1276LoRaSetSignalBandwidth( LoRaSettings.SignalBw );

    SX1276LoRaSetImplicitHeaderOn( LoRaSettings.ImplicitHeaderOn );
    SX1276LoRaSetSymbTimeout( 0x3FF );
    SX1276LoRaSetPayloadLength( LoRaSettings.PayloadLength );
    SX1276LoRaSetLowDatarateOptimize( true );

#if( ( MODULE_SX1276RF1IAS == 1 ) || ( MODULE_SX1276RF1KAS == 1 ) )
    if( LoRaSettings.RFFrequency > 860000000 )
    {
        SX1276LoRaSetPAOutput( RFLR_PACONFIG_PASELECT_RFO );
        SX1276LoRaSetPa20dBm( false );
        LoRaSettings.Power = 14;
        SX1276LoRaSetRFPower( LoRaSettings.Power );
    }
    else
    {
        SX1276LoRaSetPAOutput( RFLR_PACONFIG_PASELECT_PABOOST );
        SX1276LoRaSetPa20dBm( true );
        LoRaSettings.Power = 20;
        SX1276LoRaSetRFPower( LoRaSettings.Power );
    } 
#elif( MODULE_SX1276RF1JAS == 1 )
    if( LoRaSettings.RFFrequency > 860000000 )
    {
        SX1276LoRaSetPAOutput( RFLR_PACONFIG_PASELECT_PABOOST );
        SX1276LoRaSetPa20dBm( true );
        LoRaSettings.Power = 20;
        SX1276LoRaSetRFPower( LoRaSettings.Power );
    }
    else
    {
        SX1276LoRaSetPAOutput( RFLR_PACONFIG_PASELECT_RFO );
        SX1276LoRaSetPa20dBm( false );
        LoRaSettings.Power = 14;
        SX1276LoRaSetRFPower( LoRaSettings.Power );
    } 
#endif

    SX1276LoRaSetOpMode( RFLR_OPMODE_STANDBY );				//配置完成进入待机模式
}

/*******************************************************************************
*函数名			:	function
*功能描述		:	函数功能说明
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
void SX1276LoRaSetDefaults( void )			//默认配置--读版本SX1276芯片ID和版本信息
{
    // REMARK: See SX1276 datasheet for modified default values.

    SX1276Read( REG_LR_VERSION, &SX1276LR->RegVersion );
}
/*******************************************************************************
*函数名			:	SX1276LoRaReset
*功能描述		:	复位SX1276
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
void SX1276LoRaReset( void )		//复位SX1276---未使用
{
	uint32_t startTick;
    SX1276SetReset( RADIO_RESET_ON );
    
    // Wait 1ms
		startTick = GET_TICK_COUNT( );
    while( ( GET_TICK_COUNT( ) - startTick ) < TICK_RATE_MS( 1 ) );    

    SX1276SetReset( RADIO_RESET_OFF );
    
    // Wait 6ms
    startTick = GET_TICK_COUNT( );
    while( ( GET_TICK_COUNT( ) - startTick ) < TICK_RATE_MS( 6 ) );    
}
/*******************************************************************************
*函数名			:	SX1276LoRaSetOpMode
*功能描述		:	设置SX1276在LoRa模式下的工作模式
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
void SX1276LoRaSetOpMode( uint8_t opMode )		//设置SX1276在LoRa模式下的工作模式
{
    static uint8_t opModePrev = RFLR_OPMODE_STANDBY;		//待机模式// Default
    static bool antennaSwitchTxOnPrev = true;
    bool antennaSwitchTxOn = false;

    opModePrev = SX1276LR->RegOpMode & ~RFLR_OPMODE_MASK;			//获取原寄存器值，取bit0~bit2（查看RegOpMode）

    if( opMode != opModePrev )
    {
        if( opMode == RFLR_OPMODE_TRANSMITTER )		//发送模式
        {
            antennaSwitchTxOn = true;							//发射器开启标志
        }
        else
        {
            antennaSwitchTxOn = false;
        }
        if( antennaSwitchTxOn != antennaSwitchTxOnPrev )		//未开启
        {
            antennaSwitchTxOnPrev = antennaSwitchTxOn;
            RXTX( antennaSwitchTxOn ); // Antenna switch control		//无线开关控制SX1276WriteRxTx( txEnable );
        }
        SX1276LR->RegOpMode = ( SX1276LR->RegOpMode & RFLR_OPMODE_MASK ) | opMode;		//设置新的参数值

        SX1276Write( REG_LR_OPMODE, SX1276LR->RegOpMode ); 		//写寄存器参数，寄存器地址+数据//将新的参数值写入寄存器       
    }
}
/*******************************************************************************
*函数名			:	SX1276LoRaGetOpMode
*功能描述		:	获取SX1276在LoRa模式下的工作模式
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
uint8_t SX1276LoRaGetOpMode( void )		//获取SX1276在LoRa模式下的工作模式
{
    SX1276Read( REG_LR_OPMODE, &SX1276LR->RegOpMode );
    
    return SX1276LR->RegOpMode & ~RFLR_OPMODE_MASK;
}
/*******************************************************************************
*函数名			:	SX1276LoRaReadRxGain
*功能描述		:	函数功能说明
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
uint8_t SX1276LoRaReadRxGain( void )
{
    SX1276Read( REG_LR_LNA, &SX1276LR->RegLna );
    return( SX1276LR->RegLna >> 5 ) & 0x07;
}
/*******************************************************************************
*函数名			:	SX1276LoRaReadRssi
*功能描述		:	函数功能说明
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
double SX1276LoRaReadRssi( void )
{
    // Reads the RSSI value
    SX1276Read( REG_LR_RSSIVALUE, &SX1276LR->RegRssiValue );

    if( LoRaSettings.RFFrequency < 860000000 )  // LF
    {
        return RSSI_OFFSET_LF + ( double )SX1276LR->RegRssiValue;
    }
    else
    {
        return RSSI_OFFSET_HF + ( double )SX1276LR->RegRssiValue;
    }
}
/*******************************************************************************
*函数名			:	SX1276LoRaGetPacketRxGain
*功能描述		:	获取增益
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
uint8_t SX1276LoRaGetPacketRxGain( void )		//获取增益
{
    return RxGain;
}
/*******************************************************************************
*函数名			:	SX1276LoRaGetPacketSnr
*功能描述		:	获取信噪比（SNR）值
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
int8_t SX1276LoRaGetPacketSnr( void )			//获取信噪比（SNR）值
{
    return RxPacketSnrEstimate;
}
/*******************************************************************************
*函数名			:	SX1276LoRaGetPacketRssi
*功能描述		:	获取RSSI值
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
double SX1276LoRaGetPacketRssi( void )		//获取RSSI值
{
    return RxPacketRssiValue;
}
/*******************************************************************************
*函数名			:	SX1276LoRaStartRx
*功能描述		:	准备接收--设置LoRa状态为接收准备状态
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
void SX1276LoRaStartRx( void )			//准备接收--设置LoRa状态为接收准备状态
{
    SX1276LoRaSetRFState( RFLR_STATE_RX_INIT );
}
/*******************************************************************************
*函数名			:	SX1276LoRaGetRxPacket
*功能描述		:	获取接收的数据包
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
void SX1276LoRaGetRxPacket( void *buffer, uint16_t *size )		//获取接收的数据包
{
    *size = RxPacketSize;
    RxPacketSize = 0;
    memcpy( ( void * )buffer, ( void * )RFBuffer, ( size_t )*size );
}
/*******************************************************************************
*函数名			:	SX1276LoRaSetTxPacket
*功能描述		:	设置待发送数据包
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
void SX1276LoRaSetTxPacket( const void *buffer, uint16_t size )	//设置待发送数据包
{
    TxPacketSize = size;
    memcpy( ( void * )RFBuffer, buffer, ( size_t )TxPacketSize ); 

    RFLRState = RFLR_STATE_TX_INIT;
}
/*******************************************************************************
*函数名			:	SX1276LoRaGetRFState
*功能描述		:	获取SX1276工作在LoRa模式下的状态
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
uint8_t SX1276LoRaGetRFState( void )				//获取SX1276工作在LoRa模式下的状态
{
    return RFLRState;
}
/*******************************************************************************
*函数名			:	SX1276LoRaSetRFState
*功能描述		:	设置SX1276工作在LoRa模式下的状态
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
void SX1276LoRaSetRFState( uint8_t state )	//设置SX1276工作在LoRa模式下的状态
{
    RFLRState = state;
}
/*******************************************************************************
*函数名			:	SX1276LoRaProcess
*功能描述		:	SX1276在LoRa工作模式下的接收和发送状态处理程序
*输入				: 
*返回值			:	无
*修改时间		:	无
*修改说明		:	无
*注释				:	wegam@sina.com
*******************************************************************************/
/*!
 * \brief Process the LoRa modem Rx and Tx state machines depending on the
 *        SX1276 operating mode.
 *
 * \retval rfState Current RF state [RF_IDLE, RF_BUSY, 
 *                                   RF_RX_DONE, RF_RX_TIMEOUT,
 *                                   RF_TX_DONE, RF_TX_TIMEOUT]
 */
uint32_t SX1276LoRaProcess( void )	//SX1276在LoRa工作模式下的接收和发送状态处理程序
{
    uint32_t result = RF_BUSY;
    
    switch( RFLRState )							//查询RF当前状态
    {
    case RFLR_STATE_IDLE:						//空闲状态
        break;
    case RFLR_STATE_RX_INIT:				//准备接收
        
        SX1276LoRaSetOpMode( RFLR_OPMODE_STANDBY );		//进入待机模式---只有睡眠和待机模式可写
				////中断屏蔽标志位----先关闭/清除中断
        SX1276LR->RegIrqFlagsMask = RFLR_IRQFLAGS_RXTIMEOUT |							//接收超时中断
                                    //RFLR_IRQFLAGS_RXDONE |							//数据包接收完成中断
                                    //RFLR_IRQFLAGS_PAYLOADCRCERROR |			//负载CRC 错误中断
                                    RFLR_IRQFLAGS_VALIDHEADER |						//Rx 模式下接收到的有效报文 
                                    RFLR_IRQFLAGS_TXDONE |								//FIFO 负载发送完成中断 
                                    RFLR_IRQFLAGS_CADDONE |								//CAD 完成 
                                    //RFLR_IRQFLAGS_FHSSCHANGEDCHANNEL |	//FHSS 改变信道中断 
                                    RFLR_IRQFLAGS_CADDETECTED;						//CAD 操作中检测到有效Lora 信号
        SX1276Write( REG_LR_IRQFLAGSMASK, SX1276LR->RegIrqFlagsMask );

        if( LoRaSettings.FreqHopOn == true )		//开启跳频
        {
            SX1276LR->RegHopPeriod = LoRaSettings.HopPeriod;		//跳频周期

            SX1276Read( REG_LR_HOPCHANNEL, &SX1276LR->RegHopChannel );		//获取FHSS 起始信道
            SX1276LoRaSetRFFrequency( HoppingFrequencies[SX1276LR->RegHopChannel & RFLR_HOPCHANNEL_CHANNEL_MASK] );		//根据信道//从//跳频频率列表获取新频率
        }
        else
        {
            SX1276LR->RegHopPeriod = 255;
        }
        
        SX1276Write( REG_LR_HOPPERIOD, SX1276LR->RegHopPeriod );
				//DIO0~DIO5管脚映射
                                    // RxDone                    RxTimeout                   FhssChangeChannel           CadDone
        SX1276LR->RegDioMapping1 = RFLR_DIOMAPPING1_DIO0_00 | RFLR_DIOMAPPING1_DIO1_00 | RFLR_DIOMAPPING1_DIO2_00 | RFLR_DIOMAPPING1_DIO3_00;
                                    // CadDetected               ModeReady
        SX1276LR->RegDioMapping2 = RFLR_DIOMAPPING2_DIO4_00 | RFLR_DIOMAPPING2_DIO5_00;
        SX1276WriteBuffer( REG_LR_DIOMAPPING1, &SX1276LR->RegDioMapping1, 2 );
    
        if( LoRaSettings.RxSingleOn == true ) // Rx single mode	//单次接收（RXSINGLE）
        {

            SX1276LoRaSetOpMode( RFLR_OPMODE_RECEIVER_SINGLE );		
        }
        else // Rx continuous mode										//持续接收（RXCONTINUOUS）								
        {
            SX1276LR->RegFifoAddrPtr = SX1276LR->RegFifoRxBaseAddr;
            SX1276Write( REG_LR_FIFOADDRPTR, SX1276LR->RegFifoAddrPtr );
            
            SX1276LoRaSetOpMode( RFLR_OPMODE_RECEIVER );
        }
        
        memset( RFBuffer, 0, ( size_t )RF_BUFFER_SIZE );		//清空接收缓冲区

        PacketTimeout = LoRaSettings.RxPacketTimeout;
        RxTimeoutTimer = GET_TICK_COUNT( );
        RFLRState = RFLR_STATE_RX_RUNNING;
        break;
    case RFLR_STATE_RX_RUNNING:			//正在接收
        
        if( DIO0 == 1 ) // RxDone
        {
            RxTimeoutTimer = GET_TICK_COUNT( );
            if( LoRaSettings.FreqHopOn == true )
            {
                SX1276Read( REG_LR_HOPCHANNEL, &SX1276LR->RegHopChannel );
                SX1276LoRaSetRFFrequency( HoppingFrequencies[SX1276LR->RegHopChannel & RFLR_HOPCHANNEL_CHANNEL_MASK] );
            }
            // Clear Irq
            SX1276Write( REG_LR_IRQFLAGS, RFLR_IRQFLAGS_RXDONE  );
            RFLRState = RFLR_STATE_RX_DONE;
        }
        if( DIO2 == 1 ) // FHSS Changed Channel
        {
            RxTimeoutTimer = GET_TICK_COUNT( );
            if( LoRaSettings.FreqHopOn == true )
            {
                SX1276Read( REG_LR_HOPCHANNEL, &SX1276LR->RegHopChannel );
                SX1276LoRaSetRFFrequency( HoppingFrequencies[SX1276LR->RegHopChannel & RFLR_HOPCHANNEL_CHANNEL_MASK] );
            }
            // Clear Irq			//清除中断
            SX1276Write( REG_LR_IRQFLAGS, RFLR_IRQFLAGS_FHSSCHANGEDCHANNEL );
            // Debug
            RxGain = SX1276LoRaReadRxGain( );
        }

        if( LoRaSettings.RxSingleOn == true ) // Rx single mode
        {
            if( ( GET_TICK_COUNT( ) - RxTimeoutTimer ) > PacketTimeout )
            {
                RFLRState = RFLR_STATE_RX_TIMEOUT;
            }
        }
        break;
    case RFLR_STATE_RX_DONE:				//接收完成
        SX1276Read( REG_LR_IRQFLAGS, &SX1276LR->RegIrqFlags );
        if( ( SX1276LR->RegIrqFlags & RFLR_IRQFLAGS_PAYLOADCRCERROR ) == RFLR_IRQFLAGS_PAYLOADCRCERROR )
        {
            // Clear Irq
            SX1276Write( REG_LR_IRQFLAGS, RFLR_IRQFLAGS_PAYLOADCRCERROR  );
            
            if( LoRaSettings.RxSingleOn == true ) // Rx single mode
            {
                RFLRState = RFLR_STATE_RX_INIT;
            }
            else
            {
                RFLRState = RFLR_STATE_RX_RUNNING;
            }
            break;
        }
        
        {
            uint8_t rxSnrEstimate;
            SX1276Read( REG_LR_PKTSNRVALUE, &rxSnrEstimate );
            if( rxSnrEstimate & 0x80 ) // The SNR sign bit is 1
            {
                // Invert and divide by 4
                RxPacketSnrEstimate = ( ( ~rxSnrEstimate + 1 ) & 0xFF ) >> 2;
                RxPacketSnrEstimate = -RxPacketSnrEstimate;
            }
            else
            {
                // Divide by 4
                RxPacketSnrEstimate = ( rxSnrEstimate & 0xFF ) >> 2;
            }
        }
        
        SX1276Read( REG_LR_PKTRSSIVALUE, &SX1276LR->RegPktRssiValue );
    
        if( LoRaSettings.RFFrequency < 860000000 )  // LF
        {    
            if( RxPacketSnrEstimate < 0 )
            {
                RxPacketRssiValue = RSSI_OFFSET_LF + ( ( double )SX1276LR->RegPktRssiValue ) + RxPacketSnrEstimate;
            }
            else
            {
                RxPacketRssiValue = RSSI_OFFSET_LF + ( 1.0666 * ( ( double )SX1276LR->RegPktRssiValue ) );
            }
        }
        else                                        // HF
        {    
            if( RxPacketSnrEstimate < 0 )
            {
                RxPacketRssiValue = RSSI_OFFSET_HF + ( ( double )SX1276LR->RegPktRssiValue ) + RxPacketSnrEstimate;
            }
            else
            {    
                RxPacketRssiValue = RSSI_OFFSET_HF + ( 1.0666 * ( ( double )SX1276LR->RegPktRssiValue ) );
            }
        }

        if( LoRaSettings.RxSingleOn == true ) // Rx single mode
        {
            SX1276LR->RegFifoAddrPtr = SX1276LR->RegFifoRxBaseAddr;
            SX1276Write( REG_LR_FIFOADDRPTR, SX1276LR->RegFifoAddrPtr );

            if( LoRaSettings.ImplicitHeaderOn == true )
            {
                RxPacketSize = SX1276LR->RegPayloadLength;
                SX1276ReadFifo( RFBuffer, SX1276LR->RegPayloadLength );
            }
            else
            {
                SX1276Read( REG_LR_NBRXBYTES, &SX1276LR->RegNbRxBytes );
                RxPacketSize = SX1276LR->RegNbRxBytes;
                SX1276ReadFifo( RFBuffer, SX1276LR->RegNbRxBytes );
            }
        }
        else // Rx continuous mode
        {
            SX1276Read( REG_LR_FIFORXCURRENTADDR, &SX1276LR->RegFifoRxCurrentAddr );

            if( LoRaSettings.ImplicitHeaderOn == true )
            {
                RxPacketSize = SX1276LR->RegPayloadLength;
                SX1276LR->RegFifoAddrPtr = SX1276LR->RegFifoRxCurrentAddr;
                SX1276Write( REG_LR_FIFOADDRPTR, SX1276LR->RegFifoAddrPtr );
                SX1276ReadFifo( RFBuffer, SX1276LR->RegPayloadLength );
            }
            else
            {
                SX1276Read( REG_LR_NBRXBYTES, &SX1276LR->RegNbRxBytes );
                RxPacketSize = SX1276LR->RegNbRxBytes;
                SX1276LR->RegFifoAddrPtr = SX1276LR->RegFifoRxCurrentAddr;
                SX1276Write( REG_LR_FIFOADDRPTR, SX1276LR->RegFifoAddrPtr );
                SX1276ReadFifo( RFBuffer, SX1276LR->RegNbRxBytes );
            }
        }
        
        if( LoRaSettings.RxSingleOn == true ) // Rx single mode
        {
            RFLRState = RFLR_STATE_RX_INIT;
        }
        else // Rx continuous mode
        {
            RFLRState = RFLR_STATE_RX_RUNNING;
        }
        result = RF_RX_DONE;
        break;
    case RFLR_STATE_RX_TIMEOUT:			//接收超时
        RFLRState = RFLR_STATE_RX_INIT;
        result = RF_RX_TIMEOUT;
        break;
    case RFLR_STATE_TX_INIT:				//准备发送

        SX1276LoRaSetOpMode( RFLR_OPMODE_STANDBY );

        if( LoRaSettings.FreqHopOn == true )
        {
            SX1276LR->RegIrqFlagsMask = RFLR_IRQFLAGS_RXTIMEOUT |
                                        RFLR_IRQFLAGS_RXDONE |
                                        RFLR_IRQFLAGS_PAYLOADCRCERROR |
                                        RFLR_IRQFLAGS_VALIDHEADER |
                                        //RFLR_IRQFLAGS_TXDONE |
                                        RFLR_IRQFLAGS_CADDONE |
                                        //RFLR_IRQFLAGS_FHSSCHANGEDCHANNEL |
                                        RFLR_IRQFLAGS_CADDETECTED;
            SX1276LR->RegHopPeriod = LoRaSettings.HopPeriod;

            SX1276Read( REG_LR_HOPCHANNEL, &SX1276LR->RegHopChannel );
            SX1276LoRaSetRFFrequency( HoppingFrequencies[SX1276LR->RegHopChannel & RFLR_HOPCHANNEL_CHANNEL_MASK] );
        }
        else
        {
            SX1276LR->RegIrqFlagsMask = RFLR_IRQFLAGS_RXTIMEOUT |
                                        RFLR_IRQFLAGS_RXDONE |
                                        RFLR_IRQFLAGS_PAYLOADCRCERROR |
                                        RFLR_IRQFLAGS_VALIDHEADER |
                                        //RFLR_IRQFLAGS_TXDONE |
                                        RFLR_IRQFLAGS_CADDONE |
                                        RFLR_IRQFLAGS_FHSSCHANGEDCHANNEL |
                                        RFLR_IRQFLAGS_CADDETECTED;
            SX1276LR->RegHopPeriod = 0;
        }
        SX1276Write( REG_LR_HOPPERIOD, SX1276LR->RegHopPeriod );
        SX1276Write( REG_LR_IRQFLAGSMASK, SX1276LR->RegIrqFlagsMask );

        // Initializes the payload size
        SX1276LR->RegPayloadLength = TxPacketSize;
        SX1276Write( REG_LR_PAYLOADLENGTH, SX1276LR->RegPayloadLength );
        
        SX1276LR->RegFifoTxBaseAddr = 0x00; // Full buffer used for Tx
        SX1276Write( REG_LR_FIFOTXBASEADDR, SX1276LR->RegFifoTxBaseAddr );

        SX1276LR->RegFifoAddrPtr = SX1276LR->RegFifoTxBaseAddr;
        SX1276Write( REG_LR_FIFOADDRPTR, SX1276LR->RegFifoAddrPtr );
        
        // Write payload buffer to LORA modem
        SX1276WriteFifo( RFBuffer, SX1276LR->RegPayloadLength );
                                        // TxDone               RxTimeout                   FhssChangeChannel          ValidHeader         
        SX1276LR->RegDioMapping1 = RFLR_DIOMAPPING1_DIO0_01 | RFLR_DIOMAPPING1_DIO1_00 | RFLR_DIOMAPPING1_DIO2_00 | RFLR_DIOMAPPING1_DIO3_01;
                                        // PllLock              Mode Ready
        SX1276LR->RegDioMapping2 = RFLR_DIOMAPPING2_DIO4_01 | RFLR_DIOMAPPING2_DIO5_00;
        SX1276WriteBuffer( REG_LR_DIOMAPPING1, &SX1276LR->RegDioMapping1, 2 );

        SX1276LoRaSetOpMode( RFLR_OPMODE_TRANSMITTER );

        RFLRState = RFLR_STATE_TX_RUNNING;
        break;
    case RFLR_STATE_TX_RUNNING:			//正在发送
        if( DIO0 == 1 ) // TxDone
        {
            // Clear Irq
            SX1276Write( REG_LR_IRQFLAGS, RFLR_IRQFLAGS_TXDONE  );
            RFLRState = RFLR_STATE_TX_DONE;   
        }
        if( DIO2 == 1 ) // FHSS Changed Channel
        {
            if( LoRaSettings.FreqHopOn == true )
            {
                SX1276Read( REG_LR_HOPCHANNEL, &SX1276LR->RegHopChannel );
                SX1276LoRaSetRFFrequency( HoppingFrequencies[SX1276LR->RegHopChannel & RFLR_HOPCHANNEL_CHANNEL_MASK] );
            }
            // Clear Irq
            SX1276Write( REG_LR_IRQFLAGS, RFLR_IRQFLAGS_FHSSCHANGEDCHANNEL );
        }
        break;
    case RFLR_STATE_TX_DONE:				//发送完成
        // optimize the power consumption by switching off the transmitter as soon as the packet has been sent
        SX1276LoRaSetOpMode( RFLR_OPMODE_STANDBY );

        RFLRState = RFLR_STATE_IDLE;
        result = RF_TX_DONE;
        break;
    case RFLR_STATE_CAD_INIT:    		//准备信道活动检测（CAD-Channel activity detection）
        SX1276LoRaSetOpMode( RFLR_OPMODE_STANDBY );
    
        SX1276LR->RegIrqFlagsMask = RFLR_IRQFLAGS_RXTIMEOUT |
                                    RFLR_IRQFLAGS_RXDONE |
                                    RFLR_IRQFLAGS_PAYLOADCRCERROR |
                                    RFLR_IRQFLAGS_VALIDHEADER |
                                    RFLR_IRQFLAGS_TXDONE |
                                    //RFLR_IRQFLAGS_CADDONE |
                                    RFLR_IRQFLAGS_FHSSCHANGEDCHANNEL; // |
                                    //RFLR_IRQFLAGS_CADDETECTED;
        SX1276Write( REG_LR_IRQFLAGSMASK, SX1276LR->RegIrqFlagsMask );
           
                                    // RxDone                   RxTimeout                   FhssChangeChannel           CadDone
        SX1276LR->RegDioMapping1 = RFLR_DIOMAPPING1_DIO0_00 | RFLR_DIOMAPPING1_DIO1_00 | RFLR_DIOMAPPING1_DIO2_00 | RFLR_DIOMAPPING1_DIO3_00;
                                    // CAD Detected              ModeReady
        SX1276LR->RegDioMapping2 = RFLR_DIOMAPPING2_DIO4_00 | RFLR_DIOMAPPING2_DIO5_00;
        SX1276WriteBuffer( REG_LR_DIOMAPPING1, &SX1276LR->RegDioMapping1, 2 );
            
        SX1276LoRaSetOpMode( RFLR_OPMODE_CAD );
        RFLRState = RFLR_STATE_CAD_RUNNING;
        break;
    case RFLR_STATE_CAD_RUNNING:		//信道活动检测（CAD-Channel activity detection）
        if( DIO3 == 1 ) //CAD Done interrupt
        { 
            // Clear Irq
            SX1276Write( REG_LR_IRQFLAGS, RFLR_IRQFLAGS_CADDONE  );
            if( DIO4 == 1 ) // CAD Detected interrupt
            {
                // Clear Irq
                SX1276Write( REG_LR_IRQFLAGS, RFLR_IRQFLAGS_CADDETECTED  );
                // CAD detected, we have a LoRa preamble
                RFLRState = RFLR_STATE_RX_INIT;
                result = RF_CHANNEL_ACTIVITY_DETECTED;
            } 
            else
            {    
                // The device goes in Standby Mode automatically    
                RFLRState = RFLR_STATE_IDLE;
                result = RF_CHANNEL_EMPTY;
            }
        }   
        break;
    
    default:
        break;
    } 
    return result;
}

#endif // USE_SX1276_RADIO
