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

#include "rs485.h"
#include "stdio.h"



/******************************************************************************
** Defines
*******************************************************************************/

/******************************************************************************
** Constants
*******************************************************************************/

/******************************************************************************
** Variables
*******************************************************************************/
volatile uint16_t tx1_counter = 0;
volatile uint16_t rx1_counter = 0;

uint8_t tx1_buf[TX1_SIZE];
volatile uint16_t tx1_p = 0;

uint8_t rx1_buf[RX1_SIZE];
volatile uint16_t rx1_p = 0;

/******************************************************************************
** Functions
*******************************************************************************/

/******************************************************************************
** rs485_init
*******************************************************************************
* Description    : Configure USART4.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void rs485_init(void)
{
	HAL_UART_Receive_IT(RS485_UART, &rx1_buf[rx1_p], 1);
}


/******************************************************************************
** rs485_sendChar
*******************************************************************************
* Description    : Send char
* Input          : ch: char
* Output         : None
* Return         : None
*******************************************************************************/
void rs485_sendChar(uint8_t ch)
{
    tx1_buf[0] = ch;
	HAL_UART_Transmit(RS485_UART, &tx1_buf[0], 1, HAL_MAX_DELAY);
}

/******************************************************************************
** rs485_sendBlock
*******************************************************************************
* Description    : Send block data
* Input          : len: length of data
* Output         : None
* Return         : None
*******************************************************************************/
void rs485_sendBlock(uint8_t len)
{
	HAL_UART_Transmit_IT(RS485_UART, &tx1_buf[0], len);
}

/******************************************************************************
** rs485_sendString
*******************************************************************************
* Description    : Send String
* Input          : *str: pointer to string
* Output         : None
* Return         : None
*******************************************************************************/
void rs485_sendString(char *str)
{
//    while (*str)
//    {
//        while (!LL_USART_IsActiveFlag_TC(RS485_USART))
//        {
//        }
//        LL_USART_TransmitData8(RS485_USART, *str);
//        str++;
//    }
}

/******************************************************************************
** rs485_clearBufTX
*******************************************************************************
* Description    : Clear TX buffer
* Input          : None
* Return         : None
*******************************************************************************/
void rs485_clearBufTX(void)
{
    uint16_t i;

    tx1_p = 0;
    for (i = 0; i < TX1_SIZE; i++)
    {
        tx1_buf[i] = 0;
    }
}

/******************************************************************************
** rs485_clearBufRX
*******************************************************************************
* Description    : Clear RX buffer
* Input          : None
* Return         : None
*******************************************************************************/
void rs485_clearBufRX(void)
{
    uint16_t i;

    rx1_p = 0;
    for (i = 0; i < RX1_SIZE; i++)
    {
        rx1_buf[i] = 0;
    }
}

/******************************************************************************
** rs485_restartReceiver
*******************************************************************************
* Description    : restart receiver
* Input          : None
* Return         : None
*******************************************************************************/
void rs485_restartReceiver(void)
{
    rx1_p = 0;
}

/******************************************************************************
** rs485_bytesAvailable
*******************************************************************************
* Description    : Return number available bytes for reading
* Input          : None
* Return         : number available bytes
*******************************************************************************/
uint16_t rs485_bytesAvailable(void)
{
    return rx1_p;
}

/******************************************************************************
** rs485_waitForReadyRead
*******************************************************************************
* Description    : Wait for ready read
* Input          : numRead: requested count bytes
* 				 : timeout
* Return         : ERR_TIMEOUT, ERR_NONE
*******************************************************************************/
uint8_t rs485_waitForReadyRead(uint16_t numRead, uint32_t timeout)
{
	uint16_t total_received = 0;
	uint32_t start_time = HAL_GetTick();
	uint32_t elapsed_time;
	uint16_t start_p = rx1_p;


	while (total_received < numRead)
	{
        elapsed_time = HAL_GetTick() - start_time;
        if (elapsed_time >= timeout)
        {
        	return ERR_TIMEOUT;
	    }
        total_received = rx1_p - start_p;
	}
	return ERR_NONE;
}

/******************************************************************************
** HAL_UART_RxCpltCallback
*******************************************************************************
* Description    : HAL UART RxCpltCallback
* Input          : None
* Return         : None
*******************************************************************************/
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart == RS485_UART)
    {
    	rx1_p++;

        if (rx1_p >= RX1_SIZE)
        {
        	rx1_p = 0;
        }
        HAL_UART_Receive_IT(RS485_UART, &rx1_buf[rx1_p], 1);
    }
}

/******************************************************************************
** HAL_UART_TxCpltCallback
*******************************************************************************
* Description    : USART1_IRQHandler
* Input          : None
* Return         : None
*******************************************************************************/
//void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart) {
//    if (huart == &huart1) {
//        //printf("UART Transmission Complete!\n");
//    }
//}

