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
#include "digital.h"
#include "eeprom.h"
#include "mem_map.h"
#include "system.h"


/******************************************************************************
** Defines
*******************************************************************************/


/******************************************************************************
** Constants
*******************************************************************************/

/******************************************************************************
** Variables
*******************************************************************************/
out_st out[OUT_COUNT];

din_st din[DIN_COUNT];

/******************************************************************************
** Functions
*******************************************************************************/

/******************************************************************************
** digital_init
*******************************************************************************
* Description    : Initialization digital part
* Input          : None
* Return         : None
*******************************************************************************/
void digital_init(void)
{
    /* Setting default values */
    digital_setDefault();
}

/******************************************************************************
** digital_initValues
*******************************************************************************
* Description    : Initialization values
* Input          : None
* Return         : None
*******************************************************************************/
//void digital_initValues(void)
//{
//    uint8_t n;
//
//    for (n = 0; n < OUT_COUNT; n++)
//    {
//        out[n].value = 0;
//        out[n].status &= ~oSTAT;
//    }
//
//    for (n = 0; n < DIN_COUNT; n++)
//	{
//		din[n].mode = 0;
//		din[n].status &= ~oSTAT;
//	}
//}

/******************************************************************************
** digital_setDefault
*******************************************************************************
* Description    : Setting to default values
* Input          : None
* Return         : None
*******************************************************************************/
void digital_setDefault(void)
{
    uint8_t i;

    for (i = 0; i < OUT_COUNT; i++)
    {
    	out[i].mode = 0;
    	out[i].value = 0;
    	out[i].out_value = 0;
    }

    for (i = 0; i < DIN_COUNT; i++)
	{
    	din[i].mode = 0;
    	din[i].status = 0;
	}
}

/******************************************************************************
** fan_loadSettings
*******************************************************************************
* Description    : Load Settings
* Input          : None
* Return         : None
*******************************************************************************/
void digital_loadSettings(void)
{
	uint8_t i;

	for (i = 0; i < OUT_COUNT; i++)
	{
		eem_readInt8(aOUT_MODE + i, &out[i].mode);
	}

	for (i = 0; i < DIN_COUNT; i++)
	{
		eem_readInt8(aDIN_MODE + i, &din[i].mode);
	}
}

/******************************************************************************
** digital_saveSettings
*******************************************************************************
* Description    : Save Settings
* Input          : None
* Return         : None
*******************************************************************************/
void digital_saveSettings(void)
{
    uint8_t i;

    for (i = 0; i < OUT_COUNT; i++)
    {
        eem_writeInt8(aOUT_MODE + i, out[i].mode);
    }

    for (i = 0; i < DIN_COUNT; i++)
	{
		eem_writeInt8(aDIN_MODE + i, din[i].mode);
	}
}

/******************************************************************************
** digital_saveOneOutputMode
*******************************************************************************
* Description    : Save One Output mode
* Input          : number of output
* Return         : None
*******************************************************************************/
void digital_saveOneOutputMode(uint8_t n)
{
	eem_writeInt8(aOUT_MODE + n, out[n].mode);
}

/******************************************************************************
** digital_saveOneInputMode
*******************************************************************************
* Description    : Save One Input mode
* Input          : number of Input
* Return         : None
*******************************************************************************/
void digital_saveOneInputMode(uint8_t n)
{
	eem_writeInt8(aDIN_MODE + n, din[n].mode);
}



/******************************************************************************
** digital_install
*******************************************************************************
* Description    : Install Input/Output (set default value and save to EEM )
* Input          : None
* Return         : None
*******************************************************************************/
void digital_install(void)
{
	digital_setDefault();
	digital_saveSettings();
}

