/*******************************************************************************
** Analog service
********************************************************************************
*
* Analog service
*
*
* v1.0
*
* (c) 10.2.2025
*
* use
*******************************************************************************/
#ifndef __ANALOG_H
#define __ANALOG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>


/******************************************************************************
** Defines
*******************************************************************************/
#define AIN_COUNT   9
#define AOUT_COUNT  1


#define AIN_RN      10000                       /* reference resistor */

#define TS1       	0
#define TS2       	1
#define TS3       	2
#define TS4       	3
#define TS5       	4
#define TS6       	5
#define TS7       	6
#define TS8       	7
#define TS9       	8


#define TS_KTY83    0
#define TS_PT1000   1

#define TS_INIT     0x00
#define TS_OK       0x01
#define TS_SHORT    0x02
#define TS_OPEN     0x04
#define TS_ERROR    (TS_SHORT | TS_OPEN)

#define TS_USED     0x80

// analog output mode
#define mAOUT_10V       0
#define mAOUT_PWM       1
#define mAOUT_IPWM      2

typedef struct
{
    int16_t t;
    uint8_t config;
    uint8_t status;
    int8_t offset;
    uint8_t min;
    uint8_t max;
} ain_st;

typedef struct
{
    uint8_t mode;
    uint8_t status;
    uint8_t value;
} aout_st;

/******************************************************************************
** Constants
*******************************************************************************/

/******************************************************************************
** Variables
*******************************************************************************/
extern uint8_t  ain_count;
extern uint16_t ain_rn;
extern uint8_t  sensor_type;
extern uint8_t  ain_filter_const;

extern ain_st   ain[AIN_COUNT];
extern aout_st  aout[AOUT_COUNT];

/******************************************************************************
** Functions
*******************************************************************************/

/******************************************************************************
** Functions
*******************************************************************************/
void analog_init(void);
void analog_initSensorValues(void);
void analog_setDefault(void);
void analog_setDefaultCalib(void);
void analog_service(void);

#define sensorStatus(ai)     (ain[ai].status)
#define sensorErr(ai)        (ain[ai].status & (TS_OPEN | TS_SHORT))
#define sensorOk(ai)         (ain[ai].status & TS_OK)
#define sensorIsUsed(ai)     (ain[ai].config & TS_USED)
#define _setSensorIsUsed(ai) (ain[ai].config |= TS_USED)
#define _clrSensorIsUsed(ai) (ain[ai].config &= ~TS_USED)

#ifdef __cplusplus
}
#endif

#endif
