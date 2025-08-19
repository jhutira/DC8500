/*******************************************************************************
** Variant
********************************************************************************
*
* Variant routines
*
*
* v1.0
*
* (c) 5.6.2025
*******************************************************************************/

#ifndef __VARIANT_H
#define __VARIANT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>


/******************************************************************************
** Defines
*******************************************************************************/

#define SCH_IN_COUNT   	9
#define SCH_OUT_COUNT 	5

#define OT_NONE			0
#define OT_PUMP			1
#define OT_VALVE_AB		2
#define OT_VALVE_MIX 	3
#define OT_AUX 			4


typedef struct
{
	uint8_t v;
	uint16_t x;
	uint16_t y;
} objIn_st;


typedef struct
{
	uint8_t v;
	uint16_t x;
	uint16_t y;
	uint8_t oType;
} objOut_st;


/******************************************************************************
** Constants
*******************************************************************************/
extern const objIn_st TAB_OBJ_IN[SCH_COUNT][SCH_IN_COUNT];
extern const objOut_st TAB_OBJ_OUT[SCH_COUNT][SCH_OUT_COUNT];
extern const objIn_st TAB_OBJ_LS[SCH_COUNT];

/******************************************************************************
** Variables
*******************************************************************************/



/******************************************************************************
** Functions
*******************************************************************************/


#ifdef __cplusplus
}
#endif

#endif
