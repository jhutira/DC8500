/*******************************************************************************
** Memory map
********************************************************************************
*
* Memory map
*
*
* v1.0
*
* (c) 24.3.2025
*******************************************************************************/

#ifndef __MEM_MAP_H
#define __MEM_MAP_H

#ifdef __cplusplus
extern "C" {
#endif


/******************************************************************************
** Defines
*******************************************************************************/
/* EEPROM */
#define aLANG_ID        0

#define aSOUND_SETT   	35  /* 6B */
#define aSOUND_MUTE   	45

#define aDISP_SETT   	50	/* 4B */


#define aOUT_MODE       100
#define aDIN_MODE       120
#define aCONT_PUMP      130

#define aAUX_OUT		190

#define aREG_SCH     	200

#define aDISTRIB     	250

#define aPFLAP     		300
#define aSFLAP      	310


#define aDOOR_SW     	395
#define aDOOR_TIMEOUT  	396		/* 2B */
#define aBURN_PROFIL  	400
#define aBPROF_MINT		401		/* 2B */
#define aBPROF_MAXT		403		/* 2B */
#define aBPROF_RQT		405		/* 2B */

#define aBURN_PHASES_S 	450		/* 28B */


#define aEXCH_PSW_PERIOD  	550
#define aEXCH_PSW_RUNTIME  	551
#define aEXCH_PSW_PHASEEN  	552
#define aEXCH_MT_TEMP  		553		/* 2B */
#define aEXCH_MT_HYST  		555
#define aEXCH_CT_TEMP  		556		/* 2B */
#define aEXCH_CT_HYST  		558
#define aEXCH_CT_FLAP  		559

#define aPFLAP_PID			600		/* 32B */
#define aSFLAP_PID			650		/* 32B */

#define aACCUM_SETUP		700		/* 8B */
#define aBOILER_SETUP		710		/* 8B */


#define aFLOWM_SETT			800		/* 4B */

#define aENERGY_SETT		850		/* 4B */


#ifdef __cplusplus
}
#endif

#endif
