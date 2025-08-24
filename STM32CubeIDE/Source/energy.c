/*******************************************************************************
** Variant
********************************************************************************
*
* Energy routines
*
*
* v1.0
*
* (c) 24.6.2025
*******************************************************************************/

#include "system.h"
#include "energy.h"
#include "mem_map.h"
#include "eeprom.h"
#include "debug.h"

#include "rtc.h"

/******************************************************************************
** Defines
*******************************************************************************/

/******************************************************************************
** Constants
*******************************************************************************/


/******************************************************************************
** Variables
*******************************************************************************/
flowmeter_st flowmeter;

energy_st energy;

float last_volume = 0;
uint32_t last_timeInterval = 0;

uint8_t fInitEngCnt = 1;

/******************************************************************************
** Functions
*******************************************************************************/

float Get_Temperature_IN()
{
	return (float)ain[SN_X].t / 10;
}

float Get_Temperature_OUT()
{
	return (float)ain[SN_W].t / 10;
}

/******************************************************************************
 ** flowmeter_install
 *******************************************************************************
 * Description    : Install flowmeter
 * Input          : None
 * Return         : None
 *******************************************************************************/
void flowmeter_install(void)
{
	flowmeter_setDefault();
	flowmeter_saveSettings();
}

/******************************************************************************
 ** flowmeter_setDefault
 *******************************************************************************
 * Description    : Setting to default values
 * Input          : None
 * Return         : None
 *******************************************************************************/
void flowmeter_setDefault(void)
{
	flowmeter.sett.meter_type = FM_TYPE_YFB3;
	flowmeter.sett.qFactor = FM_YFB3_DEF_QFACTOR;
	flowmeter.sett.view = 1;
}


/******************************************************************************
** flowmeter_loadSettings
*******************************************************************************
* Description    : Load Settings
* Input          : None
* Return         : None
*******************************************************************************/
void flowmeter_loadSettings(void)
{
	eem_readBlock(aFLOWM_SETT, sizeof(flowmeter_sett_st), (uint8_t*)&flowmeter.sett);

}

/******************************************************************************
** flowmeter_saveSettings
*******************************************************************************
* Description    : Save Settings
* Input          : None
* Return         : None
*******************************************************************************/
void flowmeter_saveSettings(void)
{
	eem_writeBlock(aFLOWM_SETT, sizeof(flowmeter_sett_st), (uint8_t*)&flowmeter.sett);
}



/******************************************************************************
** energy_loadAccEng
*******************************************************************************
* Description    : Load Acc Eng
* Input          : None
* Return         : None
*******************************************************************************/
void energy_loadAccEng(void)
{
	ui32_to_ui8.uin32Val = HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR0);
	energy.accEng = ui32_to_ui8.floatVal;

}

/******************************************************************************
** energy_saveAccEng
*******************************************************************************
* Description    : Save to backup
* Input          : None
* Return         : None
*******************************************************************************/
void energy_saveAccEng(void)
{
	ui32_to_ui8.floatVal = energy.accEng;
	HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR0, ui32_to_ui8.uin32Val);
}

/******************************************************************************
 ** energy_setDefault
 *******************************************************************************
 * Description    : Setting to default values
 * Input          : None
 * Return         : None
 *******************************************************************************/
void energy_setDefault(void)
{
	energy.sett.view = 1;
	energy.aPower = 0;
	energy.accEng = 0;
}


/******************************************************************************
** energy_loadSettings
*******************************************************************************
* Description    : Load Settings
* Input          : None
* Return         : None
*******************************************************************************/
void energy_loadSettings(void)
{
	eem_readBlock(aENERGY_SETT, sizeof(energy_sett_st), (uint8_t*)&energy.sett);
}

/******************************************************************************
** energy_saveSettings
*******************************************************************************
* Description    : Save Settings
* Input          : None
* Return         : None
*******************************************************************************/
void energy_saveSettings(void)
{
	eem_writeBlock(aENERGY_SETT, sizeof(energy_sett_st), (uint8_t*)&energy.sett);
}


void energy_update(void)
{
	float dV_l;
	uint32_t dt_ms;
	//float flow_l_min = (float)flowmeter.flow / 10;

	if ((fInitEngCnt != 0) && (flowmeter.volume > 0))
	{
		last_volume = flowmeter.volume;
		last_timeInterval = flowmeter.timeInterval;
		fInitEngCnt = 0;
		return;
	}

	// Volume behind the window
	dV_l = flowmeter.volume - last_volume;
	last_volume = flowmeter.volume;
	dt_ms = flowmeter.timeInterval - last_timeInterval;
	last_timeInterval = flowmeter.timeInterval;

	if (dV_l < 0.0f) dV_l = 0.0f;           // ochrana po wrap/reset-e
	if (dt_ms == 0) return; 				// ochrana proti deleniu nulou

	// Temperatures
	float T_in  = Get_Temperature_IN();
	float T_out = Get_Temperature_OUT();

	// Energy
	float delta_T = T_out - T_in;              // [K]
	//if (delta_T < 0.0f) delta_T = 0.0f; 		// only positive
	float T_avg   = 0.5f * (T_in + T_out);

	float Cwater  = 4235.26f - 2.465778f * T_avg + 0.00517638f * T_avg * T_avg; // Cwater [kJ/(K*m^3)]

	// Actual power
	//float flow_m3_s = (flow_l_min / 1000.0f) / 60.0f;  		// l/min -> m^3/s
	float flow_m3_s     = (dV_l / 1000.0f) / (dt_ms / 1000.0f); // m³/s
	float power_kW_inst = Cwater * delta_T * flow_m3_s;     // kJ/(K·m^3)*K*m^3/s = kJ/s = kW
	energy.aPower = power_kW_inst	;

	float V_m3    = dV_l / 1000.0f;           // [m^3]
	float Q_kJ    = Cwater * V_m3 * delta_T;
	float dE_kWh  = Q_kJ / 3600.0f;

	if (dE_kWh > 0.0f && isfinite(dE_kWh))
	{
		energy.accEng += dE_kWh;
	}


	/*

	// 1) surový prietok z periódy
	    float flow_raw = Flow_FromPeriods_Lmin();

	    // 2) IIR filter prietoku
	    static uint8_t filt_init = 0u;
	    if (!filt_init) { flowMeter.flow_l_min = flow_raw; filt_init = 1u; }
	    else {
	        flowMeter.flow_l_min = IIR_ALPHA * flowMeter.flow_l_min
	                             + (1.0f - IIR_ALPHA) * flow_raw;
	    }

	    // 3) objem za okno (presne z pulzov)
	    float dV_l;
	    Flow_LockISR();
	    dV_l = vol_acc_l;
	    vol_acc_l = 0.0f;
	    Flow_UnlockISR();

	    flowMeter.volume = dV_l;
	    flowMeter.timeInterval = dt_ms;

	    // 4) teploty
	    float T_in  = Get_Temperature_IN();
	    float T_out = Get_Temperature_OUT();

	    // 5) energia za okno
	    float delta_T = T_out - T_in;              // [K]
	    float T_avg   = 0.5f * (T_in + T_out);
	    float V_m3    = dV_l / 1000.0f;           // [m^3]
	    float dt_s    = (float)dt_ms / 1000.0f;   // [s]

	    // Cwater [kJ/(K*m^3)]
	    float Cwater  = 4235.26f - 2.465778f * T_avg + 0.00517638f * T_avg * T_avg;
	    float Q_kJ    = Cwater * V_m3 * delta_T;
	    float P_kW    = (dt_s > 0.0f) ? (Q_kJ / dt_s / 1000.0f) : 0.0f;
	    float dE_kWh  = Q_kJ / 3600.0f;
	    E_total_kWh  += dE_kWh;

	    // debug/telemetria
	    printf("FlowRAW: %.3f l/min | Flow: %.3f l/min | dV: %.4f l | Tin: %.2f | Tout: %.2f | P: %.3f kW | EΣ: %.4f kWh\r\n",
	           flow_raw, flowMeter.flow_l_min, dV_l, T_in, T_out, P_kW, E_total_kWh);

	           */
}
