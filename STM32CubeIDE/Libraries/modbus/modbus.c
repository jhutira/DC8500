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
#include "modbus.h"

#include "modbus_server_rtu.h"
#include "modbus_server_tcp.h"

//#include "delay.h"

/******************************************************************************
** Constants
*******************************************************************************/
/* Table of CRC16 values for high-order byte */
static const uint8_t table_crc16_hi[] = {
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,
    0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40,
    0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1,
    0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,
    0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1,
    0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
    0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40,
    0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,
    0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40 };

/* Table of CRC16 values for low-order byte */
static const uint8_t table_crc16_lo[] = {
    0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06, 0x07, 0xC7, 0x05, 0xC5,
    0xC4, 0x04, 0xCC, 0x0C, 0x0D, 0xCD, 0x0F, 0xCF, 0xCE, 0x0E, 0x0A, 0xCA, 0xCB, 0x0B,
    0xC9, 0x09, 0x08, 0xC8, 0xD8, 0x18, 0x19, 0xD9, 0x1B, 0xDB, 0xDA, 0x1A, 0x1E, 0xDE,
    0xDF, 0x1F, 0xDD, 0x1D, 0x1C, 0xDC, 0x14, 0xD4, 0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6,
    0xD2, 0x12, 0x13, 0xD3, 0x11, 0xD1, 0xD0, 0x10, 0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3,
    0xF2, 0x32, 0x36, 0xF6, 0xF7, 0x37, 0xF5, 0x35, 0x34, 0xF4, 0x3C, 0xFC, 0xFD, 0x3D,
    0xFF, 0x3F, 0x3E, 0xFE, 0xFA, 0x3A, 0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38, 0x28, 0xE8,
    0xE9, 0x29, 0xEB, 0x2B, 0x2A, 0xEA, 0xEE, 0x2E, 0x2F, 0xEF, 0x2D, 0xED, 0xEC, 0x2C,
    0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26, 0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21,
    0x20, 0xE0, 0xA0, 0x60, 0x61, 0xA1, 0x63, 0xA3, 0xA2, 0x62, 0x66, 0xA6, 0xA7, 0x67,
    0xA5, 0x65, 0x64, 0xA4, 0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F, 0x6E, 0xAE, 0xAA, 0x6A,
    0x6B, 0xAB, 0x69, 0xA9, 0xA8, 0x68, 0x78, 0xB8, 0xB9, 0x79, 0xBB, 0x7B, 0x7A, 0xBA,
    0xBE, 0x7E, 0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C, 0xB4, 0x74, 0x75, 0xB5, 0x77, 0xB7,
    0xB6, 0x76, 0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71, 0x70, 0xB0, 0x50, 0x90, 0x91, 0x51,
    0x93, 0x53, 0x52, 0x92, 0x96, 0x56, 0x57, 0x97, 0x55, 0x95, 0x94, 0x54, 0x9C, 0x5C,
    0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E, 0x5A, 0x9A, 0x9B, 0x5B, 0x99, 0x59, 0x58, 0x98,
    0x88, 0x48, 0x49, 0x89, 0x4B, 0x8B, 0x8A, 0x4A, 0x4E, 0x8E, 0x8F, 0x4F, 0x8D, 0x4D,
    0x4C, 0x8C, 0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 0x82, 0x42, 0x43, 0x83,
    0x41, 0x81, 0x80, 0x40 };


/******************************************************************************
** Variables
*******************************************************************************/
volatile uint16_t modbus_watchdog = MODBUS_TIMEOUT;

/******************************************************************************
** Functions
*******************************************************************************/
uint8_t modbus_decode_mbap_header(modbus_t *mb);
void modbus_insert_mbap_header(modbus_t *mb, uint8_t nb);

void modbus_send_message(modbus_t *mb, uint8_t nb);
uint8_t modbus_read_response(modbus_t *mb);

uint16_t modbus_crc16(uint8_t *buffer, uint16_t buffer_length);





/******************************************************************************
** modbus_init
*******************************************************************************
* Description    : MODBUS init 
* Input          : *mb: pointer to a modbus structure
*                : mode: MODBUS_TCP_MODE, MODBUS_RTU_MODE
*                : rxBuf: pointer to receiver data buffer
*                : txBuf: pointer to transmiter data buffer
* Return         : None
*******************************************************************************/
void modbus_init(modbus_t *mb, uint8_t mode, uint8_t *rxBuf, uint8_t *txBuf)
{ 
    mb->mode = mode;
    mb->rBuf = rxBuf;
    mb->tBuf = txBuf;
    mb->cnt_errTO = 0;
    mb->cnt_errID = 0;
    mb->cnt_errIV = 0;
    mb->id = MODBUS_DEF_SLAVE_ID;
    mb->recv_mbap = 0;
    mb->recv_data = 0;
    mb->reply_mode = MODBUS_REPLY_NORMAL;
    mb->mbap.t_id = 0;
    mb->mbap.prot_id = 0;
    mb->mbap.nb = 0;
    mb->mbap.unit_id = 0;

    mb->mbap_r.t_id = 0;
    mb->mbap_r.prot_id = 0;
    mb->mbap_r.nb = 0;
    mb->mbap_r.unit_id = 0;

    mb->nb = 0;
    mb->err_num = MODBUS_ERR_NONE;
    if (mode == MODBUS_TCP_MODE)
    {    
        mb->hdr_len = MODBUS_TCP_MBAP_HEADER_LENGTH;     /* start PDU block */
        modbus_tcp_restart_receiver();
    }
    else
    {
    	mb->hdr_len = MODBUS_RTU_HEADER_LENGTH;
    }

    mb->dataB.addr = 0;
    mb->dataB.fun_code = 0;
    mb->dataB.nb = 0;
    mb->dataB.parm1 = 0;
    mb->dataB.parm2 = 0;
    mb->dataB.parm3 = 0;
    mb->dataB.available = 0;
    mb->dataB.availableForWrite = 0;
    mb->dataB.read = 0;
    mb->dataB.written = 0;
}

/******************************************************************************
** modbus_decode_mbap_header
*******************************************************************************
* Description    : Decode MBAP Header
* Input          : *mb: pointer to a modbus structure
* Return         : error code: MODBUS_ERR_NONE, MODBUS_ERR_INVALID_UID, MODBUS_ERR_ILLEGAL_PROT, MODBUS_ERR_ILLEGAL_VALUE
*******************************************************************************/
uint8_t modbus_decode_mbap_header(modbus_t *mb)
{
    mb->mbap.t_id = mb->rBuf[0];                    /* Transaction identifier */
    mb->mbap.t_id <<= 8;
    mb->mbap.t_id |= mb->rBuf[1];
    mb->mbap.prot_id = mb->rBuf[2];                 /* Protocol identifier */
    mb->mbap.prot_id <<= 8;
    mb->mbap.prot_id |= mb->rBuf[3];
    mb->mbap.nb = mb->rBuf[4];                      /* Number of following bytes */
    mb->mbap.nb <<= 8;
    mb->mbap.nb |= mb->rBuf[5];
    mb->mbap.unit_id = mb->rBuf[6];                 /* Device id */

    if (mb->mbap.prot_id != 0)
    {
        return MODBUS_ERR_ILLEGAL_PROT;
    }
    
    if (mb->nb > MODBUS_MAX_PDU_LENGTH)
    {
        return MODBUS_ERR_ILLEGAL_VALUE;
    }
    
    if ((mb->mbap.unit_id != 0xFF) && (mb->mbap.unit_id != MODBUS_DEF_SLAVE_ID))
    {
        return MODBUS_ERR_INVALID_UID;
    }
    
    if (mb->mbap.unit_id == 0xFF) 
    {
        mb->reply_mode = MODBUS_REPLY_OFF;          /* No reply to Broadcasts */
    }
    else
    {
        mb->reply_mode = MODBUS_REPLY_NORMAL;
    }
    return MODBUS_ERR_NONE;
}

/******************************************************************************
** modbus_insert_mbap_header
*******************************************************************************
* Description    : Insert MBAP Header to message
* Input          : *mb: pointer to a modbus structure
*                : nb: number of following bytes
* Return         : None
*******************************************************************************/
void modbus_insert_mbap_header(modbus_t *mb, uint8_t nb)
{
    mb->tBuf[0] = (mb->mbap.t_id >> 8);
    mb->tBuf[1] = mb->mbap.t_id & 0xFF;
    mb->tBuf[2] = (mb->mbap.prot_id >> 8);
    mb->tBuf[3] = mb->mbap.prot_id & 0xFF;
    mb->tBuf[4] = 0;
    mb->tBuf[5] = nb + 1;
    mb->tBuf[6] = mb->mbap.unit_id;
}

/******************************************************************************
** modbus_send_response
*******************************************************************************
* Description    : Send response
* Input          : *mb: pointer to a modbus structure
*                : nb: Number of response bytes
* Return         : None
*******************************************************************************/
void modbus_send_message(modbus_t *mb, uint8_t nb)
{
    uint16_t crc;

    mb->mbap.t_id++;

    if (mb->mode == MODBUS_TCP_MODE)
    {
        modbus_insert_mbap_header(mb, nb);
        modbus_tcp_restart_receiver();
        modbus_tcp_sendDataBlock(MODBUS_TCP_MBAP_HEADER_LENGTH + nb);
    }
    else
    {
        mb->tBuf[0] = mb->id;

        crc = modbus_crc16(mb->tBuf, MODBUS_RTU_HEADER_LENGTH + nb);
        mb->tBuf[MODBUS_RTU_HEADER_LENGTH + nb] = crc >> 8;
        mb->tBuf[MODBUS_RTU_HEADER_LENGTH + nb + 1] = crc & 0xFF;
        modbus_tcp_restart_receiver();
        modbus_rtu_sendDataBlock(MODBUS_RTU_HEADER_LENGTH + nb + MODBUS_RTU_CHECKSUM_LENGTH);
    }
}

/******************************************************************************
** read response
*******************************************************************************
* Description    : read response
* Input          : None
* Return         : State:
*******************************************************************************/
uint8_t modbus_read_response(modbus_t *mb)
{
	uint16_t nb;
//	uint8_t res;
//	uint8_t numRead, numReadTotal;
	uint16_t crc;


	if (mb->mode == MODBUS_TCP_MODE)
	{
		/* MBAP_HEADER */
//		if ( modbus_rtu_waitForReadyRead(mb->header_len, MODBUS_TIMEOUT) == ERR_TIMEOUT )
//		{
//			mb->err_num = MODBUS_ERR_TIMEOUT;
//			return MODBUS_ERR_TIMEOUT;
//		}
//		res = decode_mbap_header();
	}
	else
	{
		if ( modbus_rtu_waitForReadyRead(mb->hdr_len+4, MODBUS_TIMEOUT) == ERR_TIMEOUT )
		{
			mb->cnt_errTO++;
			return MODBUS_ERR_TIMEOUT;
		}

		if (mb->rBuf[0] != mb->id)
		{
			mb->err_num = MODBUS_ERR_NONE;
			return MODBUS_ERR_NONE;
		}

		if ( mb->rBuf[1] & 0x80 )		// error message
		{
			crc = ((uint16_t) mb->rBuf[3] << 8) | mb->rBuf[4];
			if (crc == modbus_crc16(mb->rBuf, 3))
			{
				mb->err_num = mb->rBuf[2];		// error code
				if (mb->err_num == MODBUS_EXCEPTION_ILLEGAL_DATA_ADDRESS) mb->cnt_errIV++;
				if (mb->err_num == MODBUS_EXCEPTION_ILLEGAL_DATA_ADDRESS) mb->cnt_errID++;
			}
			else
			{
				mb->cnt_errTO++;
				mb->err_num = MODBUS_ERR_IO;
			}
			return mb->err_num;
		}
		/* Data*/
		while (1)
		{
			if ( modbus_rtu_waitForReadyRead(1, MODBUS_TIMEOUT) == ERR_TIMEOUT )
			{
				mb->err_num = MODBUS_ERR_TIMEOUT;
				mb->cnt_errTO++;
				return mb->err_num;
			}
			nb = modbus_rtu_recv_bytes_available();

			crc = ((uint16_t) mb->rBuf[nb-2] << 8) | mb->rBuf[nb-1];
			// Check CRC
			if (crc == modbus_crc16(mb->rBuf, nb - 2))
			{
				mb->err_num = MODBUS_RECV_DATA;
				return mb->err_num;
			}
		}
	}
	return MODBUS_ERR_NONE;
}

/******************************************************************************
** modbus_crc16
*******************************************************************************
* Description    : Calculate CRC16
* Input          : *buffer
*                : buffer_length
* Return         : crc16
*******************************************************************************/
uint16_t modbus_crc16(uint8_t *buffer, uint16_t buffer_length)
{
	uint8_t crc_hi = 0xFF; /* high CRC byte initialized */
	uint8_t crc_lo = 0xFF; /* low CRC byte initialized */
	uint16_t i;        /* will index into CRC lookup */

	/* pass through message buffer */
	while (buffer_length--)
	{
		i = crc_lo ^ *buffer++; /* calculate the CRC  */
		crc_lo = crc_hi ^ table_crc16_hi[i];
		crc_hi = table_crc16_lo[i];
	}
	return (crc_lo << 8 | crc_hi);
}

/******************************************************************************
** modbus_read_holdreg
*******************************************************************************
* Description    : Get Holding register values
* Input          : *mb: pointer to a modbus structure
*                : addr: address of first register to readings
*                : nr: number of following registers
* Return         : None
*******************************************************************************/
uint8_t modbus_read_holding_registers(modbus_t *mb, uint16_t addr, uint8_t nr)
{
    uint8_t res = 0;
    uint16_t i;
    uint16_t pDataB = mb->hdr_len;

	mb->dataB.fun_code = MODBUS_FC_READ_HOLDING_REGISTERS;
	mb->dataB.addr = addr;
	mb->dataB.nb = nr;

    mb->tBuf[pDataB] = mb->dataB.fun_code;
	mb->tBuf[pDataB+1] = (uint8_t)(mb->dataB.addr >> 8);
	mb->tBuf[pDataB+2] = (uint8_t)(mb->dataB.addr & 0xFF);
	mb->tBuf[pDataB+3] = (uint8_t)(mb->dataB.nb >> 8);
	mb->tBuf[pDataB+4] = (uint8_t)(mb->dataB.nb & 0xFF);

	modbus_send_message(mb, 5);

	res = modbus_read_response(mb);
	if (res == MODBUS_RECV_DATA)
	{
		pDataB = mb->hdr_len+2;
		for (i = addr; i < addr + nr; i++)
		{
			holdreg[i] = (mb->rBuf[pDataB++]);                    /* Transaction identifier */
			holdreg[i] <<= 8;
			holdreg[i] |= (mb->rBuf[pDataB++]);
		}
	}
    return res;

}

/******************************************************************************
** modbus_write_single_register
*******************************************************************************
* Description    : Set single register value
* Input          : *mb: pointer to a modbus structure
*                : addr: address of register to write
*                * Return         : None
*******************************************************************************/
uint8_t modbus_write_single_register(modbus_t *mb, uint16_t addr)
{
    uint8_t res = 0;
    uint16_t pDataB = mb->hdr_len;

	mb->dataB.fun_code = MODBUS_FC_WRITE_SINGLE_REGISTER;
	mb->dataB.addr = addr;

    mb->tBuf[pDataB] = mb->dataB.fun_code;
	mb->tBuf[pDataB+1] = (uint8_t)(mb->dataB.addr >> 8);
	mb->tBuf[pDataB+2] = (uint8_t)(mb->dataB.addr & 0xFF);
	mb->tBuf[pDataB+3] = (uint8_t)(holdreg[addr] >> 8);
	mb->tBuf[pDataB+4] = (uint8_t)(holdreg[addr] & 0xFF);

	modbus_send_message(mb, 5);

	res = modbus_read_response(mb);
    return res;

}

/******************************************************************************
** modbus_write_multiple_registers
*******************************************************************************
* Description    : Set multiple register values
* Input          : *mb: pointer to a modbus structure
*                : addr: address of register to write
*                : nr: number of following registers
*                * Return         : None
*******************************************************************************/
uint8_t modbus_write_multiple_registers(modbus_t *mb, uint16_t addr, uint8_t nr )
{
    uint8_t res = 0;
    uint16_t pDataB = mb->hdr_len;
    uint16_t i;

	mb->dataB.fun_code = MODBUS_FC_WRITE_MULTIPLE_REGISTERS;
	mb->dataB.addr = addr;
	mb->dataB.nb = nr;

    mb->tBuf[pDataB++] = mb->dataB.fun_code;
	mb->tBuf[pDataB++] = (uint8_t)(mb->dataB.addr >> 8);
	mb->tBuf[pDataB++] = (uint8_t)(mb->dataB.addr & 0xFF);
	mb->tBuf[pDataB++] = (uint8_t)(mb->dataB.nb >> 8);
	mb->tBuf[pDataB++] = (uint8_t)(mb->dataB.nb & 0xFF);
	mb->tBuf[pDataB++] = (uint8_t)(2 * mb->dataB.nb);
	for (i = addr; i < addr+nr; i++)
	{
		mb->tBuf[pDataB++] = (holdreg[i] >> 8) & 0xFF;
		mb->tBuf[pDataB++] = holdreg[i] & 0xFF;
	}
	modbus_send_message(mb, 6 + 2 * nr);

	res = modbus_read_response(mb);
    return res;

}
