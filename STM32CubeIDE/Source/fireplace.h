/*******************************************************************************
** fireplace.h
********************************************************************************
*
* fireplace regulation routines
*
*
* v1.0
*
* (c) 5.3.2025
*******************************************************************************/
#ifndef FIREPLACE_H_
#define FIREPLACE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "stdint.h"

/******************************************************************************
** Defines
*******************************************************************************/

#define DOOR_CLOSED 0
#define DOOR_OPENED 1

#define BP0_ESTOP		0
#define BP0_STOP		1
#define BP1_STBURN		2
#define BP2_BURNING		3
#define BP3_BURN_OUT	4
#define BP4_GLOW_EMBERS	5
#define BP5_VENTIL		6


#define BP1_STEP_INIT  		  0
#define BP1_STEP_WAIT_PREHEAT 1
#define BP1_STEP_WAIT_MINTEMP 2

#define BP2_STEP_INIT         0
#define BP2_STEP_WAIT_TEMP    1

#define BP3_STEP_INIT         0
#define BP3_STEP_WAIT_TEMP    1

#define BP4_STEP_INIT         0
#define BP4_STEP_WAIT_TIME 	  1

#define BP5_STEP_INIT         0
#define BP5_STEP_WAIT_TIME 	  1


#define BS_STOP     	0
#define BS_START_BURN   1
#define BS_BURNING     	2
#define BS_LOW_FUEL 	3

/* Water exchanger */
#define sWEXCH_PUMP_ON     0x01
#define sWEXCH_TS_ERR      0x80

#define PSW_S_INIT     	0
#define PSW_S_WAITRUN  	1
#define PSW_S_WAITPER  	2

#define PSW_PH_START_BURN 	0x01
#define PSW_PH_BURN 		0x02
#define PSW_PH_BURN_OUT 	0x04




typedef struct
{
	uint16_t rqFlueTemp;
	uint16_t minFlueTemp;
	uint16_t maxFlueTemp;

} burn_profile_st;


typedef struct
{
    uint16_t timeout;			// [1..90]min 	- timeout for this phase
    uint16_t minTempForBurn;	// [30..400]°C 	- minimal temperature for enter to Burning phase
} phStartBurning_st;

typedef struct
{
    uint16_t o2;				// [2..15]% 	- required O2
    uint16_t tempForBurnOut;	// [30..400]°C 	- minimal temperature for enter to Burning Out phase
    uint16_t timeoutForBurnOut;	// [1..90]min 	- timeout for enter to Burning Out phase
} phBurning_st;

typedef struct
{
	uint16_t tempForGlowEmb;	// [30..400]°C 	- minimal temperature for enter to Glowing Embers phase
	uint16_t timeoutForGlowEmb;	// [1..90]min 	- timeout for enter to Glowing Embers phase
    uint16_t pflap;				// [0..100]% 	- required primary flap position
} phBurningOut_st;

typedef struct
{
	uint16_t timeout;			// [1..12]hod 	- timeout for this phaset
    uint16_t pflap;				// [0..100]% 	- required primary flap position
    uint16_t sflap;				// [0..100]% 	- required secondary flap position
} phGlowingEmbers_st;

typedef struct
{
	uint16_t timeout;			// [1..90]min 	- timeout for this phaset
    uint16_t pflap;				// [0..100]% 	- required primary flap position
    uint16_t sflap;				// [0..100]% 	- required secondary flap position
} phVentilation_st;

typedef struct
{
	phStartBurning_st phStartBurning;
	phBurning_st phBurning;
	phBurningOut_st phBurningOut;
	phGlowingEmbers_st phGlowingEmbers;
	phVentilation_st phVentilation;
} burnPhases_st;

typedef struct
{
    uint8_t  usedSwitch;
    uint8_t  timeout;
    uint8_t  status;
    uint8_t  status_prev;
} door_st;


typedef struct
{
    uint8_t enable;         /* enable function */
    uint8_t period;         /* [0..30]min */
    uint8_t runTime;        /* [5..30]s */
    uint8_t step;           /* {0,1,2} step function */
    uint8_t fRun;
    uint8_t phaseEn;
} exchPerStirr_st;

typedef struct
{
    uint16_t temp;
    uint8_t hyst;
} exchMinTemp_st;

typedef struct
{
    uint16_t temp;
    uint8_t hyst;
    uint8_t flap;
} exchCritTemp_st;

typedef struct
{
	exchPerStirr_st perStirr;
	exchMinTemp_st minTemp;
	exchCritTemp_st critTemp;
	uint8_t status;
	uint8_t pumpPwm;
} waterExch_st;

typedef struct
{
	uint16_t status;
	uint16_t mode;
	uint8_t phase;
	uint8_t phase_prev;
	uint8_t  step;

	int16_t  flueTemp;
    uint16_t rqFlueTemp;

    uint16_t primFlapPos;
    uint16_t secFlapPos;
    uint8_t fRestartProcess;
    uint8_t fCriticTemp;
} burning_st;

typedef struct
{
	burn_profile_st burnProfile;
    burnPhases_st burnPhases;
    waterExch_st waterExch;
    door_st  door;
    burning_st burning;

} fireplace_st;

/******************************************************************************
** Constants
*******************************************************************************/


/******************************************************************************
** Variables
*******************************************************************************/
extern fireplace_st fireplace;

//extern waterExch_st waterExch;


extern uint16_t userTimer1;
extern uint16_t userTimer2;
extern uint16_t doorTimer;
extern uint16_t burnOutTimer;





/******************************************************************************
** Functions
*******************************************************************************/
extern void fireplace_setDefault(void);
extern void fireplace_loadSettings(void);
extern void fireplace_saveSettings(void);
extern void fireplace_install(void);

extern void fireplace_setBurnProfil();
extern void fireplace_startBurning(void);
extern void fireplace_stopBurning(void);

extern void fireplace_regProcess(void);

extern void fireplace_secAirRegProcess(void);

extern void waterExch_install(void);
extern void waterExch_setDefault(void);
extern void waterExch_loadSettings(void);
extern void waterExch_saveSettings(void);


extern void burnProf_setDefault(void);
extern void burnProf_loadSettings(void);
extern void burnProf_saveSettings(void);

extern void burnPhases_setDefault(void);
extern void burnPhases_loadSettings(void);
extern void burnPhases_saveSettings(void);






#ifdef __cplusplus
}
#endif

#endif /*FIREPLACE_H_ */
