/*******************************************************************************
** MODBUS bank of registers 
********************************************************************************
*
* MODBUS bank of registers 
*
*
* v1.0
*
* 28.11.2022
*******************************************************************************/
#include "modbus_bankreg.h"

/******************************************************************************
** Constants
*******************************************************************************/



/******************************************************************************
** Variables
*******************************************************************************/
uint16_t coilreg[COILREG_COUNT];
uint16_t dinreg[DINREG_COUNT];
uint16_t inputreg[INPUTREG_COUNT];
uint16_t holdreg[HOLDREG_COUNT];

bankreg_t bank_coil;
bankreg_t bank_din;
bankreg_t bank_inputreg;
bankreg_t bank_holdreg;

/******************************************************************************
** Functions
*******************************************************************************/
extern void powerSlider_update(void);


/******************************************************************************
** modbus_bankreg_init
*******************************************************************************
* Description    :  Initializing default values
* Input          :  none
* Return         :  none
*******************************************************************************/
void modbus_bankreg_init(void)
{
    uint16_t i;

    /* COIL */
    bank_coil.start = COILREG_START_ADDR;
    bank_coil.count = COILREG_COUNT;
    bank_coil.reg = &coilreg[0];

    for (i = 0; i < COILREG_COUNT; i++)
    {
        coilreg[i] = 0;
    }

    /* DISCRETE INPUTS */
    bank_din.start = DINREG_START_ADDR;
    bank_din.count = DINREG_COUNT;
    bank_din.reg = &dinreg[0];

    for (i = 0; i < DINREG_COUNT; i++)
    {
        dinreg[i] = 0;
    }

    /* INPUT REGISTERS */
    bank_inputreg.start = INPUTREG_START_ADDR;
    bank_inputreg.count = INPUTREG_COUNT;
    bank_inputreg.reg = &inputreg[0];
    for (i = 0; i < INPUTREG_COUNT; i++)
    {
        inputreg[i] = 0;
    }

    /* HOLD REGISTERS */
    bank_holdreg.start = HOLDREG_START_ADDR;
    bank_holdreg.count = HOLDREG_COUNT;
    bank_holdreg.reg = &holdreg[0];
    for (i = 0; i < HOLDREG_COUNT; i++)
    {
        holdreg[i] = 0;
    }
}



