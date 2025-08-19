/*******************************************************************************
** Modbus
********************************************************************************
*
* MODBUS driver:
*
*
* v1.0
*
* 26.11.2022
*******************************************************************************/

#ifndef __MODBUS_SERVER_RTU_H
#define __MODBUS_SERVER_RTU_H

/******************************************************************************
** Includes
*******************************************************************************/
#include "modbus.h"



/******************************************************************************
** Defines
*******************************************************************************/
#define MODBUS_RTU_TIMEOUT              2      /* 10 * 10ms */


#define MODBUS_RTU_MAX_ADU_LENGTH       256


#define MODBUS_RTU_HEADER_LENGTH        1
#define MODBUS_RTU_PRESET_REQ_LENGTH    6
#define MODBUS_RTU_PRESET_RSP_LENGTH    2

#define MODBUS_RTU_CHECKSUM_LENGTH      2


/******************************************************************************
** Variables
*******************************************************************************/

/******************************************************************************
** Functions
*******************************************************************************/
void modbus_server_rtu_init(modbus_t *mb);

#define modbus_rtu_restart_receiver() rs485_restartReceiver()

#define modbus_rtu_sendDataBlock(len) rs485_sendBlock(len)

#define modbus_rtu_waitForReadyRead(numRead, timeout) rs485_waitForReadyRead(numRead, timeout)

#define modbus_rtu_recv_bytes_available() rs485_bytesAvailable()


#endif /* __MODBUS_SERVER_RTU_H */
