/*******************************************************************************
** main definitions
********************************************************************************
*
* Main definitions
*
*
* v1.0
*
* (c) 7.1.2025
*
*
*******************************************************************************/
#ifndef __MAIN_DEF_H
#define __MAIN_DEF_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

#include "stm32u5xx_hal.h"

/* Defines -------------------------------------------------------------------*/
typedef struct
{
	uint8_t WeekDay;
	uint8_t Date;
	uint8_t Month;
	uint8_t Year;
	uint8_t Hours;
	uint8_t Minutes;
	uint8_t Seconds;
} datetime_st;

union ui32_to_ui8_t {
    float floatVal;
    uint32_t uin32Val;
    uint16_t ui16Val[2];
    uint8_t ui8Val[4];
};

#define LANG_COUNT 2

extern const char TAB_WEEKDAY_S[LANG_COUNT][7][3];




/* Constants ------------------------------------------------------------------*/


/* Variables ------------------------------------------------------------------*/
extern uint16_t fClock_change;
extern uint16_t fRTC_Tick_1sec;
extern uint16_t tick_1ms;
extern uint16_t tick2_1ms;
extern uint32_t buzzer_timer;

extern uint8_t fBlink_eff;
extern uint8_t fTick_100ms;
extern uint8_t fTick_1sec;
extern uint8_t fTick_1min;
extern uint8_t fTick_15min;
extern uint8_t fNew_day;

extern uint16_t userTimer1;
extern uint16_t userTimer2;
extern uint16_t doorTimer;


extern datetime_st datetime;

extern union ui32_to_ui8_t ui32_to_ui8;

/* Functions ------------------------------------------------------------------*/
extern void LED_G_On(void);
extern void LED_G_Toggle(void);

extern datetime_st RTC_GetCalendar(void);
extern void RTC_SetTime(uint8_t h, uint8_t m, uint8_t s);
extern void RTC_SetDate(uint8_t d, uint8_t m, uint8_t y);

extern uint8_t daysInMonth(uint8_t year, uint8_t month);

extern uint8_t dayInWeek(uint8_t date, uint8_t month, uint8_t year);

#define getUserTimer1() userTimer1
#define setUserTimer1(t) userTimer1 = t

#define getUserTimer2() userTimer2
#define setUserTimer2(t) userTimer2 = t

#define getDoorTimer() doorTimer
#define setDoorTimer(t) doorTimer = t


#ifdef __cplusplus
}
#endif


#endif

/****************************** End File ********************************/
