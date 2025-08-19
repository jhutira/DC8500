/*******************************************************************************
** Lambda sensor service
********************************************************************************
*
* Lambda sensor service
*
*
* v1.0
*
* (c) 30.4.2025
*
* use
*******************************************************************************/
#ifndef __LAMBDA_SEN_H
#define __LAMBDA_SEN_H

#ifdef __cplusplus
extern "C" {
#endif


#include <stdint.h>


/******************************************************************************
** Defines
*******************************************************************************/

/* Status LS */
#define sLS_INIT     0x00
#define sLS_OK       0x01
#define sLS_SHORT    0x02
#define sLS_OPEN     0x04
#define sLS_ST_HEAT  0x80

/* Mode LS */
#define mLS_HEATING  0x80

typedef struct
{
    uint16_t value;
    uint16_t ux;
    uint8_t status;
    uint8_t mode;
    uint8_t heat_pwr;
} lambda_st;





/******************************************************************************
** Constants
*******************************************************************************/


/******************************************************************************
** Variables
*******************************************************************************/
extern lambda_st lambda;


/******************************************************************************
** Functions
*******************************************************************************/



/******************************************************************************
** Functions
*******************************************************************************/
extern void lambda_init(void);
#define lambda_heatingOn() lambda.mode |= mLS_HEATING
#define lambda_heatingOff() lambda.mode &= ~mLS_HEATING
#define lambda_heating() (lambda.mode & mLS_HEATING)

#ifdef __cplusplus
}
#endif


#endif
