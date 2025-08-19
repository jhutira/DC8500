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
#ifndef __EEPROM_H
#define __EEPROM_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "i2c.h"

/******************************************************************************
** Defines
*******************************************************************************/
//#define EEPROM_24C128  1
//#define EEPROM_24C256  1
#define EEPROM_24C512 1

#ifdef EEPROM_24C128
    #define EEPROM_PAGE_SIZE 64
#endif

#ifdef EEPROM_24C256
    #define EEPROM_PAGE_SIZE 64
#endif

#ifdef EEPROM_24C512
    #define EEPROM_PAGE_SIZE 128
#endif

/* 1 0 1 0 A2 A1 A0 R/W */
//#define AT24C128 0xA0
#define AT24C128 0xA0

#define EEM_I2C_ADDR AT24C128

#define EEM_TIMEOUT 1000

#define hI2C	&hi2c4

/******************************************************************************
** Constants
*******************************************************************************/

/******************************************************************************
** Variables
*******************************************************************************/

/******************************************************************************
** Functions
*******************************************************************************/
uint8_t eem_writeBlock(uint16_t addr, uint16_t length, uint8_t *pBuffer);
uint8_t eem_readBlock(uint16_t addr, uint16_t length, uint8_t *pBuffer);

uint8_t eem_fillBlock(uint16_t addr, uint16_t length, uint8_t data);

uint8_t eem_writeInt8(uint16_t addr, uint8_t data);
uint8_t eem_readInt8(uint16_t addr, uint8_t *pData);

uint8_t eem_writeInt16(uint16_t addr, uint16_t data);
uint8_t eem_readInt16(uint16_t addr, uint16_t *pData);

uint8_t eem_writeInt32(uint16_t addr, uint32_t data);
uint8_t eem_readInt32(uint16_t addr, uint32_t *pData);

uint8_t eem_writeFloat(uint16_t addr, float data);
uint8_t eem_readFloat(uint16_t addr, float *pData);

#ifdef __cplusplus
}
#endif

//--------------------------------------------------------------
#endif // __EEPROM_H
