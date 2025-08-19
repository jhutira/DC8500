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
#ifndef __UART_LOG_H
#define __UART_LOG_H

#include "cmsis_os2.h"

#ifdef __cplusplus
extern "C" {
#endif


void uart_log_init(void);
void uart_log_printf(const char *fmt, ...);


#ifdef __cplusplus
}
#endif

#endif /* __UART_LOG_H */

