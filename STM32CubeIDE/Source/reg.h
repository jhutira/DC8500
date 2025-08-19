/*******************************************************************************
** reg
********************************************************************************
*
* regulation routines
*
*
* v1.0
*
* (c) 2.3.2025
*******************************************************************************/

#ifndef __REG_H
#define __REG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <system.h>
#include "pid_reg.h"
#include "fireplace.h"




/******************************************************************************
** Defines
*******************************************************************************/

#define DS_WATER     	0
#define DS_HEAT        	1
#define DS_WATER_HEAT   2
#define DS_P_WATER_HEAT 3

/* Accumulator */
#define ACCUM_A     	0
#define ACCUM_B     	1
#define ACCUM_NONE  	2

#define CO_M_10V      	0
#define CO_M_PWM      	1
#define CO_M_IPWM      	2

/* Modus */

#define mUSE_FLAP2  	0x1000
#define mUSE_WATER_EXCH 0x0800
#define mUSE_2LOOPS 	0x0400
#define mUSE_BOILER 	0x0200
#define mUSE_ACCUM  	0x0100

#define mUSE_VAL_MIX 	0x0020
#define mUSE_VAL_AB 	0x0010
#define mUSE_PUMP3  	0x0004
#define mUSE_PUMP2  	0x0002
#define mUSE_PUMP1  	0x0001




/* Accum. state */
#define sACCUM_PUMP_ON     0x0001
#define sACCUM_FULL        0x8000      /* accumulator if full */
#define sACCUM_LEVEL80     0x0800      /* accumulator warnings */

/* Boiler mode */
#define mBOILER_EN         0x0001

/* Boiler state */
#define sBOILER_PUMP_ON    0x0001

/* Water exchanger status */
#define sON        0x01
#define sTMAX      0x02
#define sTMIN      0x04
#define sDON       0x08
#define sDOFF      0x10

/* Aux Output */
#define mAO_UNUSED      0
#define mAO_EXTSRC      1
#define mAO_DOOR        2
#define mAO_REG         3



typedef struct
{
    uint8_t mode;
    uint8_t value;
    uint8_t minVal;
    uint8_t maxVal;
} contPump_st;

typedef struct
{
    uint16_t rqTemp;
    uint8_t hyst;
    uint8_t deltaOn;
    uint8_t deltaOff;
} accum_setup_st;

typedef struct
{
	accum_setup_st setup;
	uint8_t mode;
    int16_t temp;
    uint16_t level;             /* [0..100], accumulator level in percent */
    uint8_t pump_pwm;
    uint16_t status;
} accum_st;


typedef struct
{
    uint16_t rqTemp;
    uint8_t hyst;
    uint8_t deltaOn;
    uint8_t deltaOff;
    uint8_t sen_src;
    uint8_t pump_cnt;
} boiler_setup_st;

typedef struct
{
	boiler_setup_st setup;
	uint8_t mode;
    int16_t temp;
    uint16_t level;             /* [0..100], accumulator level in percent */
    uint8_t pump_pwm;
    uint16_t status;
} boiler_st;

typedef struct
{
    uint8_t mode;
    uint8_t on;
} st_auxOut;


/******************************************************************************
** Constants
*******************************************************************************/


/******************************************************************************
** Variables
*******************************************************************************/
extern uint8_t regSch;

extern uint16_t modus;

extern uint8_t distrib;

extern uint8_t selAccum;

extern contPump_st contPump;

extern accum_st accum;

extern boiler_st boiler;

extern st_auxOut auxOut;

extern uint8_t extHeatSrcOn;
extern uint8_t fAntiBlockFunStart;


/******************************************************************************
** Functions
*******************************************************************************/
extern void reg_init(void);
extern void reg_process(void);


extern void waterExch_regProcess(void);

extern void contPump_setDefault(void);
extern void contPump_loadSettings(void);
extern void contPump_saveSettings(void);

extern void accum_install(void);
extern void accum_setDefault(void);
extern void accum_loadSettings(void);
extern void accum_saveSettings(void);
extern void accum_check(void);
extern void accum_regProcess(uint8_t en);

extern void boiler_install(uint8_t s_src, uint8_t pump_cnt);
extern void boiler_setDefault(void);
extern void boiler_loadSettings(void);
extern void boiler_saveSettings(void);
extern void boiler_check(void);
extern void boiler_regProcess(uint8_t en);

extern void auxout_install(uint8_t mode);
extern void auxout_setDefault(void);
extern void auxout_loadSettings(void);
extern void auxout_saveSettings(void);

extern void io_service(void);

extern void reg_setRegScheme(uint8_t init);

#ifdef __cplusplus
}
#endif


#endif
