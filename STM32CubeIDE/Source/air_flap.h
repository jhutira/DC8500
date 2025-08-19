/*******************************************************************************
** Air flap
********************************************************************************
*
* air flap routines
*
*
* v1.0
*
* (c) 13.2.2025
*******************************************************************************/

#ifndef AIRFLAP_H_
#define AIRFLAP_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <float.h>
#include <pid_reg.h>

/******************************************************************************
** Defines
*******************************************************************************/
#define FLAP_COUNT  2

#define PRIM_F          0
#define SEC_F           1
#define MIX_F           1


#define mAUT          	0x00
#define mMAN          	0x01

#define mNORM           0
#define mINV            1


#define mSTOP          	0
#define mMOVE_CLOSE    	1
#define mMOVE_OPEN     	2
#define mOPENED        	3
#define mCLOSED        	4

#define oFAULT        0x80




typedef struct
{
    uint8_t pos;
    uint8_t mode;
    uint8_t status;
    uint16_t updateTimer;
    pid_st pid;
} flap_st;

/******************************************************************************
** Variable
*******************************************************************************/
extern flap_st airflap[FLAP_COUNT];

/******************************************************************************
** Functions
*******************************************************************************/

void airflap_init(uint8_t ch);


#define airflap_setAutoMode(ch) airflap[ch].mode = mAUT
#define airflap_setManualMode(ch) airflap[ch].mode = mMAN

void airflap_movePosition(uint8_t ch, uint16_t pos);


uint16_t airflap_compute(uint8_t ch, int16_t iVal, int16_t rVal);

void airflap_setDefault(uint8_t ch);

void airflap_loadSettings(uint8_t ch);
void airflap_saveSettings(uint8_t ch);
void airflap_saveMode(uint8_t ch);

#ifdef __cplusplus
}
#endif

#endif /* AIRFLAP_H_ */
