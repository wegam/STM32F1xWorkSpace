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
 * \file       sx1276-LoRaMisc.h
 * \brief      SX1276 RF chip high level functions driver
 *
 * \remark     Optional support functions.
 *             These functions are defined only to easy the change of the
 *             parameters.
 *             For a final firmware the radio parameters will be known so
 *             there is no need to support all possible parameters.
 *             Removing these functions will greatly reduce the final firmware
 *             size.
 *
 * \version    2.0.B2 
 * \date       May 6 2013
 * \author     Gregory Cristian
 *
 * Last modified by Miguel Luis on Jun 19 2013
 */
#ifndef __SX1276_LORA_MISC_H__
#define __SX1276_LORA_MISC_H__


#include	"stdint.h"
#include	"stdbool.h"

/*!
 * \brief Writes the new RF frequency value
 *
 * \param [IN] freq New RF frequency value in [Hz]
 */
void SX1276LoRaSetRFFrequency( uint32_t freq );		//������ƵƵ��--��Ƶ�ʲ���д��ָ���Ĵ���

/*!
 * \brief Reads the current RF frequency value
 *
 * \retval freq Current RF frequency value in [Hz]
 */
uint32_t SX1276LoRaGetRFFrequency( void );		//��ȡ��ƵƵ��

/*!
 * \brief Writes the new RF output power value
 *
 * \param [IN] power New output power value in [dBm]
 */
void SX1276LoRaSetRFPower( int8_t power );		//������Ƶ����

/*!
 * \brief Reads the current RF output power value
 *
 * \retval power Current output power value in [dBm]
 */
int8_t SX1276LoRaGetRFPower( void );					//��ȡ��Ƶ����

/*!
 * \brief Writes the new Signal Bandwidth value
 *
 * \remark This function sets the IF frequency according to the datasheet
 *
 * \param [IN] factor New Signal Bandwidth value [0: 125 kHz, 1: 250 kHz, 2: 500 kHz]
 */
void SX1276LoRaSetSignalBandwidth( uint8_t bw );	//���ô���

/*!
 * \brief Reads the current Signal Bandwidth value
 *
 * \retval factor Current Signal Bandwidth value [0: 125 kHz, 1: 250 kHz, 2: 500 kHz] 
 */
uint8_t SX1276LoRaGetSignalBandwidth( void );		//��ȡ�������

/*!
 * \brief Writes the new Spreading Factor value
 *
 * \param [IN] factor New Spreading Factor value [7, 8, 9, 10, 11, 12]
 */
void SX1276LoRaSetSpreadingFactor( uint8_t factor );	//������Ƶ����

/*!
 * \brief Reads the current Spreading Factor value
 *
 * \retval factor Current Spreading Factor value [7, 8, 9, 10, 11, 12] 
 */
uint8_t SX1276LoRaGetSpreadingFactor( void );					//��ȡ��Ƶ���Ӳ���

/*!
 * \brief Writes the new Error Coding value
 *
 * \param [IN] value New Error Coding value [1: 4/5, 2: 4/6, 3: 4/7, 4: 4/8]
 */
void SX1276LoRaSetErrorCoding( uint8_t value );			//���þ�����

/*!
 * \brief Reads the current Error Coding value
 *
 * \retval value Current Error Coding value [1: 4/5, 2: 4/6, 3: 4/7, 4: 4/8]
 */
uint8_t SX1276LoRaGetErrorCoding( void );

/*!
 * \brief Enables/Disables the packet CRC generation
 *
 * \param [IN] enaable [true, false]
 */
void SX1276LoRaSetPacketCrcOn( bool enable );		//CRCУ������--ʹ��/�ر�

/*!
 * \brief Reads the current packet CRC generation status
 *
 * \retval enable [true, false]
 */
bool SX1276LoRaGetPacketCrcOn( void );					//��ȡCRCУ������״̬--ʹ��/�ر�

/*!
 * \brief Enables/Disables the Implicit Header mode in LoRa
 *
 * \param [IN] enable [true, false]
 */
void SX1276LoRaSetImplicitHeaderOn( bool enable );		//����ͷ����Ϊ��ʽģʽ--ʹ��/�ر�

/*!
 * \brief Check if implicit header mode in LoRa in enabled or disabled
 *
 * \retval enable [true, false]
 */
bool SX1276LoRaGetImplicitHeaderOn( void );		//����ͷ����Ϊ��ʽģʽ--��ȡ����״̬

/*!
 * \brief Enables/Disables Rx single instead of Rx continuous
 *
 * \param [IN] enable [true, false]
 */
void SX1276LoRaSetRxSingleOn( bool enable );	//����RXΪ��һģʽ--ʹ��/�ر�

/*!
 * \brief Check if LoRa is in Rx Single mode
 *
 * \retval enable [true, false]
 */
bool SX1276LoRaGetRxSingleOn( void );					//����RXΪ��һģʽ--ʹ��/�رգ���ȡ����״̬)

/*!
 * \brief Enables/Disables the frequency hopping 
 *
 * \param [IN] enable [true, false]
 */
 
void SX1276LoRaSetFreqHopOn( bool enable );		//����LoRaTM���ƽ��������Ƶģʽ--ʹ��/�ر�

/*!
 * \brief Get the frequency hopping status 
 *
 * \param [IN] enable [true, false]
 */
bool SX1276LoRaGetFreqHopOn( void );			//����LoRaTM���ƽ��������Ƶģʽ--ʹ��/�رգ���ȡ����״̬)

/*!
 * \brief Set symbol period between frequency hops
 *
 * \param [IN] value
 */
void SX1276LoRaSetHopPeriod( uint8_t value );		//������Ƶֵ

/*!
 * \brief Get symbol period between frequency hops
 *
 * \retval value symbol period between frequency hops
 */
uint8_t SX1276LoRaGetHopPeriod( void );		//��ȡ��Ƶֵ

/*!
 * \brief Set timeout Tx packet (based on MCU timer, timeout between Tx Mode entry Tx Done IRQ)
 *
 * \param [IN] value timeout (ms)
 */
void SX1276LoRaSetTxPacketTimeout( uint32_t value );		//���÷��ͳ�ʱʱ��

/*!
 * \brief Get timeout between Tx packet (based on MCU timer, timeout between Tx Mode entry Tx Done IRQ)
 *
 * \retval value timeout (ms)
 */
uint32_t SX1276LoRaGetTxPacketTimeout( void );		//��ȡ���ͳ�ʱʱ��

/*!
 * \brief Set timeout Rx packet (based on MCU timer, timeout between Rx Mode entry and Rx Done IRQ)
 *
 * \param [IN] value timeout (ms)
 */
void SX1276LoRaSetRxPacketTimeout( uint32_t value );		//���ý��ճ�ʱʱ��

/*!
 * \brief Get timeout Rx packet (based on MCU timer, timeout between Rx Mode entry and Rx Done IRQ)
 *
 * \retval value timeout (ms)
 */
uint32_t SX1276LoRaGetRxPacketTimeout( void );			//��ȡ���ճ�ʱʱ��

/*!
 * \brief Set payload length
 *
 * \param [IN] value payload length
 */
void SX1276LoRaSetPayloadLength( uint8_t value );		//������Ч����

/*!
 * \brief Get payload length
 *
 * \retval value payload length
 */
uint8_t SX1276LoRaGetPayloadLength( void );			//��ȡ��Ч����

/*!
 * \brief Enables/Disables the 20 dBm PA
 *
 * \param [IN] enable [true, false]
 */
void SX1276LoRaSetPa20dBm( bool enale );		//����/�ر� 20dBm PA

/*!
 * \brief Gets the current 20 dBm PA status
 *
 * \retval enable [true, false]
 */
bool SX1276LoRaGetPa20dBm( void );			//��ȡ 20dBm PA״̬

/*!
 * \brief Set the RF Output pin 
 *
 * \param [IN] RF_PACONFIG_PASELECT_PABOOST or RF_PACONFIG_PASELECT_RFO
 */
void SX1276LoRaSetPAOutput( uint8_t outputPin );	//����PA_BOOST�ܽ�

/*!
 * \brief Gets the used RF Ouptut pin
 *
 * \retval RF_PACONFIG_PASELECT_PABOOST or RF_PACONFIG_PASELECT_RFO
 */
uint8_t SX1276LoRaGetPAOutput( void );		//��ȡPA_BOOST�ܽ�����״̬

/*!
 * \brief Writes the new PA rise/fall time of ramp up/down value
 *
 * \param [IN] value New PaRamp value
 */
void SX1276LoRaSetPaRamp( uint8_t value );		//д���µ�PA����/�½�ʱ���б������/�½�ֵ��

/*!
 * \brief Reads the current PA rise/fall time of ramp up/down value
 *
 * \retval freq Current PaRamp value
 */
uint8_t SX1276LoRaGetPaRamp( void );		//��ȡ��ǰPA����/�½�ʱ�������/�½�ֵ��

/*!
 * \brief Set Symbol Timeout based on symbol length
 *
 * \param [IN] value number of symbol
 */
void SX1276LoRaSetSymbTimeout( uint16_t value );		//���ڷ��ų������÷��ų�ʱ

/*!
 * \brief  Get Symbol Timeout based on symbol length
 *
 * \retval value number of symbol
 */
uint16_t SX1276LoRaGetSymbTimeout( void );		//���ڷ��ų��Ȼ�ȡ���ų�ʱ 

/*!
 * \brief  Configure the device to optimize low datarate transfers
 *
 * \param [IN] enable Enables/Disables the low datarate optimization
 */
void SX1276LoRaSetLowDatarateOptimize( bool enable );		//�����豸�Ż����������ʴ���--ʹ��/�ر� 

/*!
 * \brief  Get the status of optimize low datarate transfers
 *
 * \retval LowDatarateOptimize enable or disable
 */
bool SX1276LoRaGetLowDatarateOptimize( void );		//��ȡ���������ʴ�������״̬ 

/*!
 * \brief Set the preamble length
 *
 * \param [IN] value preamble length
 */
void SX1276LoRaSetPreambleLength( uint16_t value );		//����ǰ���볤��

/*!
 * \brief Get the preamble length
 *
 * \retval value preamble length
 */
uint16_t SX1276LoRaGetPreambleLength( void );		//��ȡǰ���볤��

/*!
 * \brief Set the number or rolling preamble symbol needed for detection
 *
 * \param [IN] value number of preamble symbol
 */
void SX1276LoRaSetNbTrigPeaks( uint8_t value );	//���ü����������������ǰ�����š�

/*!
 * \brief Get the number or rolling preamble symbol needed for detection
 *
 * \retval value number of preamble symbol
 */
uint8_t SX1276LoRaGetNbTrigPeaks( void );	//��ȡ�����������������ǰ�����š�
#endif //__SX1276_LORA_MISC_H__

