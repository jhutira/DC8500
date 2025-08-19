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

/* Includes ------------------------------------------------------------------*/
#include <main_util.h>

//#include "main.h"

#include "rtc.h"
#include "hw_defn.h"

/* Defines -------------------------------------------------------------------*/


/* Constants ------------------------------------------------------------------*/
const uint8_t DayOfMonth[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

const uint8_t MonthOfs[12] = {0, 3, 3, 6, 1, 4, 6, 2, 5, 0, 3, 5};



/* Variables ------------------------------------------------------------------*/
const char TAB_WEEKDAY_S[LANG_COUNT][7][3] =
{
    {"Mo", "Tu", "We", "Th", "Fr", "Sa", "Su"},
    {"Po", "Ut", "St", "Sv", "Pi", "So", "Ne"}
};



uint16_t fClock_change;
uint16_t fRTC_Tick_1sec = 0;
uint16_t tick_1ms = 0;
uint16_t tick2_1ms = 0;
uint32_t buzzer_timer = 0;


uint8_t fBlink_eff = 0;
uint8_t fTick_100ms = 0;
uint8_t fTick_1sec = 0;
uint8_t fTick_1min = 0;
uint8_t fTick_15min = 0;
uint8_t fNew_day = 0;

uint16_t userTimer1 = 0;
uint16_t userTimer2 = 0;
uint16_t doorTimer = 0;


datetime_st datetime;

union ui32_to_ui8_t ui32_to_ui8;

/* Functions ------------------------------------------------------------------*/

/******************************************************************************
** LED_G_On
*******************************************************************************
* Description    : Led Green On
* Input          : None
* Return         : None
*******************************************************************************/
void LED_G_On(void)
{
	HAL_GPIO_WritePin(LED_G1_GPIO_Port, LED_G1_Pin, GPIO_PIN_SET);
}

/******************************************************************************
** LED_G_Toggle
*******************************************************************************
* Description    : Led Green Toggle
* Input          : None
* Return         : None
*******************************************************************************/
void LED_G_Toggle(void)
{
	HAL_GPIO_TogglePin(LED_G1_GPIO_Port, LED_G1_Pin);
}


/******************************************************************************
** RTC_GetCalendar
*******************************************************************************
* Description    : Get RTC calendar
* Input          : None
* Return         : None
*******************************************************************************/
datetime_st RTC_GetCalendar(void)
{
	RTC_TimeTypeDef mTime = {0};
	RTC_DateTypeDef mDate = {0};
	datetime_st mDatetime;


	HAL_RTC_GetTime(&hrtc, &mTime, RTC_FORMAT_BIN);
	HAL_RTC_GetDate(&hrtc, &mDate, RTC_FORMAT_BIN);
	//printf("Data: %.2d-%.2d-%.2d-%.2d\r\n", mDate.Date, mDate.Month, mDate.Year, mDate.WeekDay);
	//printf("Time: %.2d:%.2d:%.2d\r\n", mTime.Hours, mTime.Minutes, mTime.Seconds);
	//printf("\x1b[1F");
	//printf("\x1b[1F");
	mDatetime.WeekDay = mDate.WeekDay;
	mDatetime.Date = mDate.Date;
	mDatetime.Month = mDate.Month;
	mDatetime.Year = mDate.Year;
	mDatetime.Hours = mTime.Hours;
	mDatetime.Minutes = mTime.Minutes;
	return mDatetime;
}

/******************************************************************************
** RTC_SetTime
*******************************************************************************
* Description    : Set RTC Time
* Input          : h, m, s
* Return         : None
*******************************************************************************/
void RTC_SetTime(uint8_t h, uint8_t m, uint8_t s)
{
	RTC_TimeTypeDef mTime = {0};

	mTime.Hours = h;
	mTime.Minutes = m;
	mTime.Seconds = s;
	HAL_RTC_SetTime(&hrtc, &mTime, RTC_FORMAT_BIN);
}

/******************************************************************************
** RTC_SetDate
*******************************************************************************
* Description    : Set RTC DAte
* Input          : d, m, y
* Return         : None
*******************************************************************************/
void RTC_SetDate(uint8_t d, uint8_t m, uint8_t y)
{
	RTC_DateTypeDef mDate = {0};

	mDate.Date = d;
	mDate.Month = m;
	mDate.Year = y;
	mDate.WeekDay = dayInWeek(d, m, y);
	HAL_RTC_SetDate(&hrtc, &mDate, RTC_FORMAT_BIN);
}

/******************************************************************************
** leapYear
*******************************************************************************
* Description    : Calculate if leap year
* Input          : year
* Return         : None
*******************************************************************************/
uint8_t leapYear(uint8_t year)
{
    if (!(year % 4) && (year % 100))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/******************************************************************************
** mrtc4_daysInMonth
*******************************************************************************
* Description    : Calculate days in month
* Input          : year
* Return         : None
*******************************************************************************/
uint8_t daysInMonth(uint8_t year, uint8_t month)
{
    uint8_t days;

    days = DayOfMonth[month - 1];
    if (leapYear(year) == 0) 		// no leat year
    {
        if (month == 2)
        {
            days--;
        }
    }
    return days;
}

/******************************************************************************
** mrtc4_calcWeekday
*******************************************************************************
* Description    : day in week
* Input          : date, month, year
* Return         : Weekday
*******************************************************************************/
/* century offset = 20 for 20xx */
/* weekday = (20 + dayOff + monthOff + yearOff) % 7; */
uint8_t dayInWeek(uint8_t date, uint8_t month, uint8_t year)
{
    uint8_t dayOff;
    uint8_t monthOff;
    uint8_t yearOff;
    uint8_t weekday;

    dayOff = date % 7;
    monthOff = MonthOfs[month - 1];
    yearOff = (year + (year / 4)) % 7;
    weekday = 20 + dayOff + monthOff + yearOff;

    if ((year % 4) == 0)
    {
        if (month < 3)
        {
            weekday--;
        }
    }
    weekday = weekday % 7;
    if (weekday == 0)
    {
        weekday = 7;            /* correct (0..6) to (1..7) */
    }
    return weekday;
}


/*********************************************************************************************************
** End of File
*********************************************************************************************************/
