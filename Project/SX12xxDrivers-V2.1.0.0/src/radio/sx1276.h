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
 * \file       sx1276.h
 * \brief      SX1276 RF chip driver
 *
 * \version    2.0.B2 
 * \date       May 6 2013
 * \author     Gregory Cristian
 *
 * Last modified by Miguel Luis on Jun 19 2013
 */
#ifndef __SX1276_H__
#define __SX1276_H__

#include	"stdint.h"
#include	"stdbool.h"

/*!
 * \brief SX1276 registers array
 */
extern uint8_t SX1276Regs[0x70];



/*!
 * \brief Initializes the SX1276
 */
void SX1276Init( void );	//初始化SX1276--GPIO初始化，寄存器初始化，工作模式初始化，芯片参数配置。配置完成后进入待机状态

/*!
 * \brief Resets the SX1276
 */
void SX1276Reset( void );	//复位SX1276，拉低NREST脚100uS然后拉高，等待5mS芯片稳定

/*!
 * \brief Enables LoRa modem or FSK modem
 *
 * \param [IN] opMode New operating mode
 */
void SX1276SetLoRaOn( bool enable );	//设置为LoRa模式或者FSK模式

/*!
 * \brief Gets the LoRa modem state
 *
 * \retval LoraOn Current LoRa modem mode
 */
bool SX1276GetLoRaOn( void );		//获取LoRa模式状态
/*!
 * \brief Sets the SX1276 operating mode
 *
 * \param [IN] opMode New operating mode
 */
void SX1276SetOpMode( uint8_t opMode );	//设置SX1276操作模式

/*!
 * \brief Gets the SX1276 operating mode
 *
 * \retval opMode Current operating mode
 */
uint8_t SX1276GetOpMode( void );	//获取SX1276操作模式

/*!
 * \brief Reads the current Rx gain setting
 *
 * \retval rxGain Current gain setting
 */
uint8_t SX1276ReadRxGain( void );		//读取当前的RX增益设置 

/*!
 * \brief Trigs and reads the current RSSI value
 *
 * \retval rssiValue Current RSSI value in [dBm]
 */
double SX1276ReadRssi( void );	//触发和读取当前RSSI值 

/*!
 * \brief Gets the Rx gain value measured while receiving the packet
 *
 * \retval rxGainValue Current Rx gain value
 */
uint8_t SX1276GetPacketRxGain( void );	//获取接收包时测量的RX增益值。

/*!
 * \brief Gets the SNR value measured while receiving the packet
 *
 * \retval snrValue Current SNR value in [dB]
 */
int8_t SX1276GetPacketSnr( void );		//获取接收包时测量的SNR(信噪比)值。

/*!
 * \brief Gets the RSSI value measured while receiving the packet
 *
 * \retval rssiValue Current RSSI value in [dBm]
 */
double SX1276GetPacketRssi( void );		//获取接收包时测量的RSSI值。

/*!
 * \brief Gets the AFC value measured while receiving the packet
 *
 * \retval afcValue Current AFC value in [Hz]
 */
uint32_t SX1276GetPacketAfc( void );		//获取接收包时测量的AFC值。

/*!
 * \brief Sets the radio in Rx mode. Waiting for a packet
 */
void SX1276StartRx( void );		//将收射频设置为接收模式。等待一个数据包

/*!
 * \brief Gets a copy of the current received buffer
 *
 * \param [IN]: buffer     Buffer pointer
 * \param [IN]: size       Buffer size
 */
void SX1276GetRxPacket( void *buffer, uint16_t *size );		//获取当前接收缓冲区的副本

/*!
 * \brief Sets a copy of the buffer to be transmitted and starts the
 *        transmission
 *
 * \param [IN]: buffer     Buffer pointer
 * \param [IN]: size       Buffer size
 */
void SX1276SetTxPacket( const void *buffer, uint16_t size );		//设置要传输的缓冲区的副本并开始传输。

/*!
 * \brief Gets the current RFState
 *
 * \retval rfState Current RF state [RF_IDLE, RF_BUSY, 
 *                                   RF_RX_DONE, RF_RX_TIMEOUT,
 *                                   RF_TX_DONE, RF_TX_TIMEOUT]
 */
uint8_t SX1276GetRFState( void );		//获取当前射频状态

/*!
 * \brief Sets the new state of the RF state machine
 *
 * \param [IN]: state New RF state machine state
 */
void SX1276SetRFState( uint8_t state );		//设置新的射频状态。

/*!
 * \brief Process the Rx and Tx state machines depending on the
 *       SX1276 operating mode.
 *
 * \retval rfState Current RF state [RF_IDLE, RF_BUSY, 
 *                                   RF_RX_DONE, RF_RX_TIMEOUT,
 *                                   RF_TX_DONE, RF_TX_TIMEOUT]
 */
uint32_t SX1276Process( void );		//根据SX1276的工作模式处理RX和Tx的状态

#endif //__SX1276_H__

