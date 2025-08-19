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

#ifndef __MODBUS_H
#define __MODBUS_H

/******************************************************************************
** Includes
*******************************************************************************/
#include "stdint.h"

#include "rs485.h"

#include "modbus_bankreg.h"


/******************************************************************************
** Defines
*******************************************************************************/
#define MODBUS_RTU_MODE         0
#define MODBUS_TCP_MODE         1


#define MODBUS_DEF_SLAVE_ID     1

#define MODBUS_TIMEOUT 1000      /* 200 * 1ms */



extern void serial_sendBlock(uint16_t len);


#define MODBUS_REPLY_OFF                    0
#define MODBUS_REPLY_NORMAL                 1

/* Modbus function codes */
#define MODBUS_FC_READ_COILS                0x01
#define MODBUS_FC_READ_DISCRETE_INPUTS      0x02
#define MODBUS_FC_READ_HOLDING_REGISTERS    0x03
#define MODBUS_FC_READ_INPUT_REGISTERS      0x04
#define MODBUS_FC_WRITE_SINGLE_COIL         0x05
#define MODBUS_FC_WRITE_SINGLE_REGISTER     0x06
#define MODBUS_FC_READ_EXCEPTION_STATUS     0x07
#define MODBUS_FC_WRITE_MULTIPLE_COILS      0x0F
#define MODBUS_FC_WRITE_MULTIPLE_REGISTERS  0x10
#define MODBUS_FC_REPORT_SLAVE_ID           0x11
#define MODBUS_FC_MASK_WRITE_REGISTER       0x16
#define MODBUS_FC_WRITE_AND_READ_REGISTERS  0x17


#define MODBUS_BROADCAST_ADDRESS            0
#define MODBUS_MAX_SLAVE_ADDRESS            247

#define MODBUS_MAX_READ_BITS                2000
#define MODBUS_MAX_WRITE_BITS               1968

#define MODBUS_MAX_READ_REGISTERS           125
#define MODBUS_MAX_WRITE_REGISTERS          123
#define MODBUS_MAX_WR_WRITE_REGISTERS       121
#define MODBUS_MAX_WR_READ_REGISTERS        125


/* The size of the MODBUS PDU is limited by the size constraint inherited from
 * the first MODBUS implementation on Serial Line network (max. RS485 ADU = 256
 * bytes). Therefore, MODBUS PDU for serial line communication = 256 - Server
 * address (1 byte) - CRC (2 bytes) = 253 bytes.
 */
#define MODBUS_MAX_PDU_LENGTH 253

/* Consequently:
 * - RTU MODBUS ADU = 253 bytes + Server address (1 byte) + CRC (2 bytes) = 256
 *   bytes.
 * - TCP MODBUS ADU = 253 bytes + MBAP (7 bytes) = 260 bytes.
 * so the maximum of both backend in 260 bytes. This size can used to allocate
 * an array of bytes to store responses and it will be compatible with the two
 * backends.
 */
#define MODBUS_MAX_ADU_LENGTH 260

/* Random number to avoid errno conflicts */
#define MODBUS_ENOBASE 112345678


/* Protocol exceptions */
enum {
    MODBUS_EXCEPTION_ILLEGAL_FUNCTION = 0x01,
    MODBUS_EXCEPTION_ILLEGAL_DATA_ADDRESS,
    MODBUS_EXCEPTION_ILLEGAL_DATA_VALUE,
    MODBUS_EXCEPTION_SLAVE_OR_SERVER_FAILURE,
    MODBUS_EXCEPTION_ACKNOWLEDGE,
    MODBUS_EXCEPTION_SLAVE_OR_SERVER_BUSY,
    MODBUS_EXCEPTION_NEGATIVE_ACKNOWLEDGE,
    MODBUS_EXCEPTION_MEMORY_PARITY,
    MODBUS_EXCEPTION_NOT_DEFINED,
    MODBUS_EXCEPTION_GATEWAY_PATH,
    MODBUS_EXCEPTION_GATEWAY_TARGET,
    MODBUS_EXCEPTION_MAX
};

/* Error code */
#define MODBUS_ERR_NONE          0
#define MODBUS_ERR_IO            5
#define MODBUS_ERR_INVALID_UID   18
#define MODBUS_ERR_ILLEGAL_VALUE 22
#define MODBUS_ERR_ILLEGAL_PROT  109
#define MODBUS_ERR_CONN_REFUSED  111
#define MODBUS_ERR_TIMEOUT       116
#define MODBUS_ERR_NOT_SUPPORTED 134

#define MODBUS_RECV_DATA         1

typedef struct  
{
    uint16_t t_id;      /* Transaction identifier */
    uint16_t prot_id;   /* Protocol identifier */
    uint16_t nb;        /* Number of following bytes */
    uint8_t unit_id;    /* Unit Identifier */
} mbap_header_t;

typedef struct  
{
    uint16_t errorStatus;
    uint16_t fun_code;
    uint16_t addr;
    uint8_t *values;
    uint16_t nb;        /* Number of following bytes */
    uint16_t parm1;
    uint16_t parm2;
    uint16_t parm3;
    uint16_t checksum;
    int available;
    int read;
    int availableForWrite;
    int written;
} modbus_data_t;

typedef struct
{
    uint8_t mode;
    uint8_t id;
    uint8_t recv_mbap;
    uint8_t recv_data;
    uint8_t reply_mode;
    uint16_t nb;        /* Number of following bytes */
    uint16_t err_num;   /* Number of error */
    uint8_t *rBuf;
    uint8_t *tBuf;
    uint32_t cnt_errTO;
    uint32_t cnt_errID;
    uint32_t cnt_errIV;
    uint8_t hdr_len;
    mbap_header_t mbap;
    mbap_header_t mbap_r;
    modbus_data_t dataB;
} modbus_t;


/******************************************************************************
** Variables
*******************************************************************************/
extern volatile uint16_t modbus_watchdog;



/******************************************************************************
** Functions
*******************************************************************************/
void modbus_init(modbus_t *mb, uint8_t mode, uint8_t *rxBuf, uint8_t *txBuf);

uint8_t modbus_read_holding_registers(modbus_t *mb, uint16_t addr, uint8_t nr);
uint8_t modbus_write_single_register(modbus_t *mb, uint16_t addr);
uint8_t modbus_write_multiple_registers(modbus_t *mb, uint16_t addr, uint8_t nr );




//--------------------------------------------------------------
#endif /* __MODBUS_H */
