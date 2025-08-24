/*******************************************************************************
** Variant
********************************************************************************
*
* Energy routines
*
*
* v1.0
*
* (c) 24.6.2025
*******************************************************************************/

#ifndef __ENERGY_H
#define __ENERGY_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>


/******************************************************************************
** Defines
*******************************************************************************/
typedef enum {
    FM_TYPE_NONE = 0,
    FM_TYPE_PULSE = 1,
    FM_TYPE_YFB3 = 2
} FlowMeterType;

//#define FM_YFB3_PULSE_PER_1_L_MIN  	11     // pulses per 1 l/min
//#define FM_YFB3_PULSE_PER_LITRE    660     // pulses per 1 liter
#define FM_YFB3_DEF_QFACTOR   	   660     // pulses per 1 liter
#define FM_PULSE_DEF_QFACTOR   		10     // liters per 1 pulse

typedef struct
{
	uint8_t meter_type;
	uint16_t qFactor;
	uint8_t view;
} flowmeter_sett_st;


typedef struct
{
	flowmeter_sett_st sett;
	uint16_t flow;
	float volume;
	uint32_t timeInterval;
} flowmeter_st;


typedef struct
{
	uint8_t view;
} energy_sett_st;

typedef struct
{
	energy_sett_st sett;

	float aPower;
	float accEng;
} energy_st;
/******************************************************************************
** Constants
*******************************************************************************/


/******************************************************************************
** Variables
*******************************************************************************/
extern flowmeter_st flowmeter;
extern energy_st energy;


/******************************************************************************
** Functions
*******************************************************************************/

extern void flowmeter_install(void);
extern void flowmeter_setDefault(void);
extern void flowmeter_loadSettings(void);
extern void flowmeter_saveSettings(void);

extern void energy_setDefault(void);
extern void energy_loadSettings(void);
extern void energy_saveSettings(void);

extern void energy_saveAccEng(void);
extern void energy_loadAccEng(void);

extern void energy_update();


#ifdef __cplusplus
}
#endif

#endif
