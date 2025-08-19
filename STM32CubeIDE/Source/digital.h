/*******************************************************************************
** Digital service
********************************************************************************
*
* Digital service
*
*
* v1.0
*
* (c) 13.2.2025
*
* use
*******************************************************************************/
#ifndef __DIGITAL_H
#define __DIGITAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>


/******************************************************************************
** Defines
*******************************************************************************/
#define DIN_COUNT   2

#define OUT_COUNT   5


#define OUT_P1      0
#define OUT_P2      1
#define OUT_Y1 	    2
#define OUT_Y2  	3
#define OUT_Y3      4
#define OUT_LH      5
#define OUT_M1      6

#define DI1         0
#define DI2         1

//input status:
#define iSTAT       0x01
#define iINV        0x02

//output mode
#define oON       	0x01
#define oINV        0x02
#define oMAN        0x40




typedef struct
{
    uint8_t mode;
    uint8_t value;
    uint8_t out_value;
} out_st;

typedef struct
{
	uint8_t mode;
	uint8_t status;
} din_st;


/******************************************************************************
** Constants
*******************************************************************************/

/******************************************************************************
** Variables
*******************************************************************************/
extern out_st  out[OUT_COUNT];
extern din_st  din[DIN_COUNT];

/******************************************************************************
** Functions
*******************************************************************************/

/******************************************************************************
** Functions
*******************************************************************************/
extern void digital_init(void);
//extern void digital_initValues(void);

extern void digital_setDefault(void);
extern void digital_loadSettings(void);
extern void digital_saveSettings(void);
extern void digital_saveOneOutputMode(uint8_t n);
extern void digital_saveOneInputMode(uint8_t n);

extern void digital_install(void);

#ifdef __cplusplus
}
#endif

#endif
