/*******************************************************************************
** System
********************************************************************************
*
* System routines
*
*
* v1.0
*
* (c) 5.5.2016
*******************************************************************************/

#ifndef __SYSTEM_H
#define __SYSTEM_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#include "modbus_server_rtu.h"

#include "analog.h"
#include "digital.h"
#include "air_flap.h"
#include "lambda_sen.h"


/******************************************************************************
** Defines
*******************************************************************************/

#define SW_VER      10
#define SW_SUBVER   ' '

#define LANG_ENG	0
#define LANG_SVK	1

/* Errors code */
#define eSEN        0x01
#define eMAN        0x04
#define eOVERHEAT   0x08

#define eCOMM_IO    0x40
#define eHW         0x80



#define SN_W    TS1
#define SN_A    TS2
#define SN_X    TS3
#define SN_E    TS4
#define SN_H    TS5
#define SN_M    TS6
#define SN_R    TS7
#define SN_B    TS8
#define SN_O    TS9


#define ds_WATER     	0
#define ds_HEAT        	1
#define ds_WATER_HEAT   2

#define SCH_COUNT	8

#define SCH_01	0
#define SCH_02	1
#define SCH_03	2
#define SCH_04	3
#define SCH_05	4
#define SCH_06	5
#define SCH_07	6
#define SCH_08	7
#define SCH_09	8


#define amALARM		0x01
#define amWARN		0x02
#define amTOUCH		0x04

typedef struct
{
    uint8_t h;
    uint8_t m;
} stime_st;

typedef struct
{
	stime_st mute_time_on;
	stime_st mute_time_off;
	uint8_t announ_msg;
} sound_sett_st;

typedef struct
{
	sound_sett_st sett;
    uint8_t mute;
    uint8_t on;
} sound_st;


typedef struct
{
	uint8_t saver_backlight;
	uint8_t saver_time;
	uint8_t saver_en;
	uint8_t backlight;
} disp_sett_st;


typedef struct
{
	disp_sett_st sett;
	uint16_t timer;
} display_st;


typedef struct
{
    uint8_t ser_number[3];
    uint8_t address;
    uint8_t com_speed;
    display_st display;
    sound_st sound;
    uint8_t err_state;
    uint8_t change_scheme;
    uint8_t service_mode;
    uint8_t exservice_mode;
} system_st;



/******************************************************************************
** Constants
*******************************************************************************/


/******************************************************************************
** Variables
*******************************************************************************/
extern system_st mSystem;
extern modbus_t mb;

extern uint8_t lang_id;

extern uint8_t service_mode;
extern uint8_t exservice_mode;



/******************************************************************************
** Functions
*******************************************************************************/
extern void system_init(void);

extern void system_loadData(void);

extern void system_saveData(void);

extern void system_setDefault(void);

extern void system_checkErrWarnState(void);

#ifdef __cplusplus
}
#endif

#endif
