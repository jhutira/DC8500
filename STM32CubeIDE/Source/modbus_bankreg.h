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

#ifndef __MODBUS_BANKREG_H
#define __MODBUS_BANKREG_H

/******************************************************************************
** Includes
*******************************************************************************/

#include "stdint.h"


/******************************************************************************
** Defines
*******************************************************************************/
#define BANKREG_DATA_OK              0
#define BANKREG_ILLEGAL_DATA_ADDRESS 1
#define BANKREG_ILLEGAL_DATA_VALUE   2
#define BANKREG_INTERNAL_ERROR       3

typedef struct
{
    uint16_t start;
    uint16_t count;
    uint16_t* reg;
} bankreg_t;


#define COILREG_START_ADDR  0
#define COILREG_COUNT       128

extern uint16_t coilreg[COILREG_COUNT];


#define DINREG_START_ADDR   0
#define DINREG_COUNT        64

extern uint16_t dinreg[DINREG_COUNT];


#define INPUTREG_START_ADDR  0
#define INPUTREG_COUNT       128

extern uint16_t inputreg[INPUTREG_COUNT];

#define HOLDREG_START_ADDR  0
#define HOLDREG_COUNT       1024

extern uint16_t holdreg[HOLDREG_COUNT];

extern bankreg_t bank_coil;
extern bankreg_t bank_din;
extern bankreg_t bank_inputreg;
extern bankreg_t bank_holdreg;


#define COIL_OUT_STATE_ADR      0
#define COIL_OUT_STATE_COUNT    OUT_COUNT   

#define DIN_DIN_STATE_ADR       30
#define DIN_DIN_STATE_COUNT     DIN_COUNT

#define HOLDREG_OUT_STATUS_ADR      0
#define HOLDREG_OUT_STATUS_COUNT    5

#define HOLDREG_AIN_VALUE_ADR       20
#define HOLDREG_AIN_VALUE_COUNT     9

#define HOLDREG_AIN_STATUS_ADR      40
#define HOLDREG_AIN_STATUS_COUNT    9

#define HOLDREG_DIN_STATUS_ADR      60
#define HOLDREG_DIN_STATUS_COUNT    2

#define HOLDREG_AIN_RN_ADR          81
#define HOLDREG_AIN_RN_COUNT        1

#define HOLDREG_FLAP_POS_ADR        100
#define HOLDREG_FLAP_POS_COUNT      2

#define HOLDREG_PFLAP_STATUS_ADR    110
#define HOLDREG_PFLAP_STATUS_COUNT  2

#define HOLDREG_LSEN_VALUE_ADR      120
#define HOLDREG_LSEN_VALUE_COUNT    1

#define HOLDREG_LSEN_STATUS_ADR     121
#define HOLDREG_LSEN_STATUS_COUNT   1

#define HOLDREG_LSEN_MODE_ADR       122
#define HOLDREG_LSEN_MODE_COUNT     1

#define HOLDREG_LSEN_HEAT_ADR       123
#define HOLDREG_LSEN_HEAT_COUNT     1

#define HOLDREG_AOUT_VALUE_ADR      130
#define HOLDREG_AOUT_VALUE_COUNT    1

#define HOLDREG_AOUT_MODE_ADR       140
#define HOLDREG_AOUT_MODE_COUNT     1

#define HOLDREG_FM_FLOW_L_MIN_ADR   160
#define HOLDREG_FM_FLOW_L_MIN_COUNT 1

#define HOLDREG_FM_VOLUME_HI_ADR    161
#define HOLDREG_FM_VOLUME_HI_COUNT  1

#define HOLDREG_FM_VOLUME_LO_ADR    162
#define HOLDREG_FM_VOLUME_LO_COUNT  1

#define HOLDREG_FM_INVERVAL_HI_ADR  163
#define HOLDREG_FM_INTERVAL_HI_COUNT  1

#define HOLDREG_FM_INVERVAL_LO_ADR  164
#define HOLDREG_FM_INTERVAL_LO_COUNT  1

#define HOLDREG_FM_TYPE_ADR         165
#define HOLDREG_FM_TYPE_COUNT       1

#define HOLDREG_FM_QFACTOR_ADR      166
#define HOLDREG_FM_QFACTOR_COUNT    1

#define HOLDREG_HW_STATE_ADR        200
#define HOLDREG_HW_STATE_COUNT      1

#define HOLDREG_ID_DEVICE_ADR       210
#define HOLDREG_ID_DEVICE_COUNT     1

#define HOLDREG_SW_VERSION_ADR      211
#define HOLDREG_SW_VERSION_COUNT    1





/******************************************************************************
** Variables
*******************************************************************************/


/******************************************************************************
** Functions
*******************************************************************************/
void modbus_bankreg_init(void);



//--------------------------------------------------------------
#endif // __MODBUS_BANKREG_H
