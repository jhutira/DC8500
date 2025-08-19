/*******************************************************************************
** RS485 driver
********************************************************************************
*
* RS485 driver:
*
* v1.0
*
* (c) 10.8.2022
*
* CPU: STM32F051
* USART1: RXD= PA10, TXD= PA9, TE= PA12
*******************************************************************************/

#ifndef __RS485_H
#define __RS485_H

/******************************************************************************
** Includes
*******************************************************************************/
#include "usart.h"

/******************************************************************************
** Defines
*******************************************************************************/
#define RS485_UART   		&huart3

#define RS485_BUADRATE    	19200

#define RS485_PARITY_NONE  UART_PARITY_NONE
#define RS485_PARITY_ODD   UART_PARITY_ODD
#define RS485_PARITY_EVEN  UART_PARITY_EVEN

#define RX1_SIZE 256
#define TX1_SIZE 256

#define ERR_NONE	0
#define ERR_TIMEOUT	1

/******************************************************************************
** Constants
*******************************************************************************/

/******************************************************************************
** Variables
*******************************************************************************/
extern volatile uint16_t tx1_counter;
extern volatile uint16_t rx1_counter;

extern uint8_t tx1_buf[TX1_SIZE];
extern volatile uint16_t tx1_p;

extern uint8_t rx1_buf[RX1_SIZE];
extern volatile uint16_t rx1_p;

/******************************************************************************
** Functions
*******************************************************************************/

//#define RS485_Enable() ( USART_Cmd(USART1, ENABLE) )

void rs485_init(void);
void rs485_sendChar(uint8_t ch);
void rs485_sendBlock(uint8_t len);
void rs485_sendString(char *str);
void rs485_clearBufTX(void);
void rs485_clearBufRX(void);

void rs485_restartReceiver(void);
uint16_t rs485_bytesAvailable(void);

uint8_t rs485_waitForReadyRead(uint16_t numRead, uint32_t timeout);

//--------------------------------------------------------------
#endif // __RS485_H
