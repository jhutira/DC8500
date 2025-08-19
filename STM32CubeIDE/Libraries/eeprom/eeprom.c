/*******************************************************************************
** EEPROM driver
********************************************************************************
*
* EEPROM driver: (I2C) 24C128, 24C26, 24C512
*
*
* v1.0
*
* (c) 14.2.2025
*
*
*******************************************************************************/

#include "eeprom.h"

#include "stm32u5xx_hal.h"
#include "i2c.h"
#include <string.h>


static union {
    float f;
    uint32_t i;
    uint8_t b[4];
} cdata;

/******************************************************************************
** eem_writePage
*******************************************************************************
* Description    : EEPROM Write Page
* Input          : addr: address
*                  numByteToWrite:
*                  pData: pointer to buffer
* Return         : Error code
*******************************************************************************/
uint8_t eem_writePage(uint16_t addr, uint16_t numByteToWrite, uint8_t *pBuffer)
{
	uint8_t buf[numByteToWrite + 2];

	/* address HI */
	buf[0] = (uint8_t)(addr >> 8);
	/* address LO */
	buf[1] = (uint8_t)(addr & 0xFF);

	memcpy(&buf[2], pBuffer, numByteToWrite);

	if (HAL_I2C_Master_Transmit(hI2C, EEM_I2C_ADDR, &buf[0], numByteToWrite + 2, EEM_TIMEOUT) != HAL_OK)
	{
		return HAL_ERROR;
	}

	HAL_Delay(5);  // Delay 5ms

	return HAL_OK;
}

/******************************************************************************
** eem_fillPage
*******************************************************************************
* Description    : EEPROM Fill Page
* Input          : addr: address
*                  NumByteToWrite:
*                  Data: data to filling
* Return         : Error code
*******************************************************************************/
uint8_t eem_fillPage(uint16_t addr, uint8_t numByteToWrite, uint8_t data)
{
	uint8_t buf[numByteToWrite + 2];

	/* address HI */
	buf[0] = (uint8_t)(addr >> 8);
	/* address LO */
	buf[1] = (uint8_t)(addr & 0xFF);

	memset(&buf[2], data, numByteToWrite);

	if (HAL_I2C_Master_Transmit(hI2C, EEM_I2C_ADDR, buf, numByteToWrite + 2, EEM_TIMEOUT) != HAL_OK)
	{
		return HAL_ERROR;
	}

	HAL_Delay(5);  // Delay 5ms

	return HAL_OK;
}



/******************************************************************************
** eem_writeBlock
*******************************************************************************
* Description    : EEPROM Write Block
* Input          : addr: address
*                  length: number byte to write
*                  pData: pointer to buffer
* Return         : Error code
*******************************************************************************/
uint8_t eem_writeBlock(uint16_t addr, uint16_t length, uint8_t *pBuffer)
{
	uint8_t err = 0;
	uint16_t bytesWritten = 0;

	while (bytesWritten < length)
	{
		uint8_t pageOffset = addr % EEPROM_PAGE_SIZE;
		uint8_t bytesToWrite = EEPROM_PAGE_SIZE - pageOffset;

		// check size
		if (bytesToWrite > (length - bytesWritten))
		{
			bytesToWrite = length - bytesWritten;
		}

		err+= eem_writePage(addr, bytesToWrite, &pBuffer[bytesWritten]);

		bytesWritten += bytesToWrite;
		addr += bytesToWrite;
	}
	return err;
}

/******************************************************************************
** eem_readBlock
*******************************************************************************
* Description    : EEPROM Read Block
* Input          : addr: address
*                  length: number byte to read
*                  pBuffer: pointer to buffer
* Return         : Error code
*******************************************************************************/
uint8_t eem_readBlock(uint16_t addr, uint16_t length, uint8_t *pBuffer)
{
	uint8_t address[2];

	address[0] = (uint8_t)(addr >> 8);
	address[1] = (uint8_t)(addr & 0xFF);

	if (HAL_I2C_Master_Transmit(hI2C, EEM_I2C_ADDR, address, 2, EEM_TIMEOUT) != HAL_OK)
	{
		return HAL_ERROR;
	}

	if (HAL_I2C_Master_Receive(hI2C, EEM_I2C_ADDR, pBuffer, length, EEM_TIMEOUT) != HAL_OK)
	{
		return HAL_ERROR;
	}

	return HAL_OK;
}

/******************************************************************************
** eem_fillBlock
*******************************************************************************
* Description    : EEPROM fill Block
* Input          : addr: address
*                  length: number byte to fill
*                  data: data to filling
* Return         : Error code
*******************************************************************************/
uint8_t eem_fillBlock(uint16_t addr, uint16_t length, uint8_t data)
{
    uint8_t err = 0;
    uint16_t bytesWritten = 0;

     while (bytesWritten < length)
     {
        uint8_t pageOffset = addr % EEPROM_PAGE_SIZE;
        uint8_t bytesToWrite = EEPROM_PAGE_SIZE - pageOffset;

        // check size
        if (bytesToWrite > (length - bytesWritten))
        {
            bytesToWrite = length - bytesWritten;
        }

        err+= eem_fillPage(addr, bytesToWrite, data);

        bytesWritten += bytesToWrite;
        addr += bytesToWrite;
    }
    return err;
}

/******************************************************************************
** eem_writeInt8
*******************************************************************************
* Description    : EEPROM Write Integer
* Input          : addr: address
*                  data: data to write
* Return         : Error code
*******************************************************************************/
uint8_t eem_writeInt8(uint16_t addr, uint8_t data)
{
	uint8_t buf[3];

	/* address HI */
	buf[0] = (uint8_t)(addr >> 8);
	/* address LO */
	buf[1] = (uint8_t)(addr & 0xFF);
	/* Data */
	buf[2] = data;

	if (HAL_I2C_Master_Transmit(hI2C, EEM_I2C_ADDR, &buf[0], 3, EEM_TIMEOUT) != HAL_OK)
	{
		return HAL_ERROR;
	}

	HAL_Delay(5);  // Delay 5ms

	return HAL_OK;
}

/******************************************************************************
** eem_readInt8
*******************************************************************************
* Description    : EEPROM Read Integer
* Input          : addr: address
*                  pData: pointer to buffer
* Return         : Error code
*******************************************************************************/
uint8_t eem_readInt8(uint16_t addr, uint8_t *pData)
{
	uint8_t address[2];

	address[0] = (uint8_t)(addr >> 8);
	address[1] = (uint8_t)(addr & 0xFF);

	if (HAL_I2C_Master_Transmit(hI2C, EEM_I2C_ADDR, address, 2, EEM_TIMEOUT) != HAL_OK)
	{
		return HAL_ERROR;
	}

	if (HAL_I2C_Master_Receive(hI2C, EEM_I2C_ADDR, pData, 1, EEM_TIMEOUT) != HAL_OK)
	{
		return HAL_ERROR;
	}

	return HAL_OK;
}

/******************************************************************************
** eem_readInt16
*******************************************************************************
* Description    : EEPROM Read Integer
* Input          : addr: address
*                  pData: pointer to buffer
* Return         : Error code
*******************************************************************************/
uint8_t eem_readInt16(uint16_t addr, uint16_t *pData)
{
    uint8_t err;

    err = eem_readBlock(addr, 2, &cdata.b[0]);
    *pData = cdata.i;
    return err;
}

/******************************************************************************
** eem_writeInt16
*******************************************************************************
* Description    : EEPROM Write Integer
* Input          : addr: address
*                  data: data to write
* Return         : Error code
*******************************************************************************/
uint8_t eem_writeInt16(uint16_t addr, uint16_t data)
{
    uint8_t err;

    cdata.i = data;
    err = eem_writeBlock(addr, 2, &cdata.b[0]);
    return err;
}

/******************************************************************************
** eem_readInt32
*******************************************************************************
* Description    : EEPROM Read Integer
* Input          : addr: address
*                  pData: pointer to buffer
* Return         : Error code
*******************************************************************************/
uint8_t eem_readInt32(uint16_t addr, uint32_t *pData)
{
    uint8_t err;

    err = eem_readBlock(addr, 4, &cdata.b[0]);
    *pData = cdata.i;
    return err;
}

/******************************************************************************
** eem_writeInt32
*******************************************************************************
* Description    : EEPROM Write Integer
* Input          : addr: address
*                  data: data to write
* Return         : Error code
*******************************************************************************/
uint8_t eem_writeInt32(uint16_t addr, uint32_t data)
{
    uint8_t err;

    cdata.i = data;
    err = eem_writeBlock(addr, 4, &cdata.b[0]);
    return err;
}

/******************************************************************************
** eem_readFloat
*******************************************************************************
* Description    : EEPROM Read Float
* Input          : addr: address
*                  pData: pointer to buffer
* Return         : Error code
*******************************************************************************/
uint8_t eem_readFloat(uint16_t addr, float *pData)
{
    uint8_t err;

    err = eem_readBlock(addr, 4, &cdata.b[0]);
    *pData = cdata.f;
    return err;
}

/******************************************************************************
** eem_writeFloat
*******************************************************************************
* Description    : EEPROM Write Float
* Input          : addr: address
*                  data: data to write
* Return         : Error code
*******************************************************************************/
uint8_t eem_writeFloat(uint16_t addr, float data)
{
    uint8_t err;

    cdata.f = data;
    err = eem_writeBlock(addr, 4, &cdata.b[0]);
    return err;
}
