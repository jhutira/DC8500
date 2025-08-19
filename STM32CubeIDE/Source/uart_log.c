/*******************************************************************************
** UART Log
********************************************************************************
*
* uart log routines
*
*
* v1.0
*
* (c) 18.6.2025
*******************************************************************************/
#include "uart_log.h"
#include "main.h"
#include "usart.h"
#include <stdio.h>
#include <stdarg.h>
#include <string.h>



/******************************************************************************
** Defines
*******************************************************************************/
#define LOG_QUEUE_LENGTH 2
#define LOG_LINE_MAX_LEN 64


typedef struct {
    char text[LOG_LINE_MAX_LEN];
} log_msg_t;

/******************************************************************************
** Constants
*******************************************************************************/

/******************************************************************************
** Variables
*******************************************************************************/
static osMessageQueueId_t logQueueHandle;
static osThreadId_t logTaskHandle;


/******************************************************************************
** Functions
*******************************************************************************/

/* UART Log Task */
static void uart_log_task(void *argument)
{
    log_msg_t msg;
    for (;;)
    {
    	if (osMessageQueueGet(logQueueHandle, &msg, NULL, 10) == osOK)  // osWaitForever
        {
            HAL_UART_Transmit(&huart1, (uint8_t *)msg.text, strnlen(msg.text, LOG_LINE_MAX_LEN), HAL_MAX_DELAY);
        }
        osDelay(1);
    }
}


/* Init Function */
void uart_log_init(void)
{
    /* Create queue */
    logQueueHandle = osMessageQueueNew(LOG_QUEUE_LENGTH, sizeof(log_msg_t), NULL);
    if (logQueueHandle == NULL)
    {
        Error_Handler(); // Queue error
    }

    /* Create task */
    const osThreadAttr_t logTaskAttr = {
            .name = "uartLogTask",
            .priority = (osPriority_t) osPriorityHigh,
            .stack_size = 2048
        };

    logTaskHandle = osThreadNew(uart_log_task, NULL, &logTaskAttr);
    if (logTaskHandle == NULL)
    {
        Error_Handler(); // Task error
    }
}

/* Logging function */
void uart_log_printf(const char *fmt, ...)
{
    log_msg_t msg = {0};
    va_list args;

    va_start(args, fmt);
    vsnprintf(msg.text, LOG_LINE_MAX_LEN, fmt, args);
    va_end(args);

    osStatus_t status = osMessageQueuePut(logQueueHandle, &msg, 0, 0);
    if (status != osOK)
    {
        // Optional: drop or signal error

    }
}

