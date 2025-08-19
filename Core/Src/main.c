/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "jpeg_utils_conf.h"
#include "cmsis_os2.h"
#include "crc.h"
#include "dcache.h"
#include "dma2d.h"
#include "gpdma.h"
#include "gpu2d.h"
#include "hspi.h"
#include "i2c.h"
#include "icache.h"
#include "jpeg.h"
#include "ltdc.h"
#include "memorymap.h"
#include "rtc.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "app_touchgfx.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "hw_defn.h"
#include <main_util.h>
#include <uart_log.h>
#include "mx25lm51245g.h"
#include "buzzer.h"
#include "stdio.h"
#include "string.h"
#include "rs485.h"

#include "backlight.h"
#include "system.h"
#include "reg.h"
#include "fireplace.h"
#include "energy.h"
#include "modbus_server_rtu.h"

#include "debug.h"



/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

#define PIP_TIME 2       /* 10 * 10ms */


/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

volatile uint8_t main_touchAct = 0;

const int32_t tabBuzzerEff1[10] = {50, -50, 0, 0, 0, 0, 0, 0, 0, 0};
const int32_t tabBuzzerEff2[10] = {10, -60000, 0, 0, 0, 0, 0, 0, 0, 0};
const int32_t tabBuzzerEff3[10] = {10, -10, 10, -60000, 0, 0, 0, 0, 0, 0};

uint8_t pBuzzerEff = 0;
uint8_t fBuzzOn = 0;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void SystemPower_Config(void);
void MX_FREERTOS_Init(void);
/* USER CODE BEGIN PFP */



/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

int __io_putchar(int ch)
{
	// Write character to ITM ch.0
	//ITM_SendChar(ch);
	return(ch);
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the System Power */
  SystemPower_Config();

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_GPDMA1_Init();
  MX_I2C1_Init();
  MX_USART3_UART_Init();
  MX_LTDC_Init();
  MX_HSPI1_Init();
  MX_TIM3_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  MX_CRC_Init();
  MX_GPU2D_Init();
  MX_ICACHE_Init();
  MX_DCACHE1_Init();
  MX_DCACHE2_Init();
  MX_DMA2D_Init();
  MX_JPEG_Init();
  MX_I2C4_Init();
  MX_RTC_Init();
  MX_TouchGFX_Init();
  /* Call PreOsInit function */
  MX_TouchGFX_PreOSInit();
  /* USER CODE BEGIN 2 */

  // RTC backup
  __HAL_RCC_PWR_CLK_ENABLE();
  HAL_PWR_EnableBkUpAccess();

  /* LCD On */
  HAL_GPIO_WritePin(LCD_ON_GPIO_Port, LCD_ON_Pin, GPIO_PIN_SET);

  backlight_init();
  backlight_pwm(80);

  buzzer_init();
  buzzer_off();

  modbus_server_rtu_init(&mb);

  system_init();

  setvbuf(stdout, NULL, _IONBF, 0); // Disables buffering in the printf function


  /* USER CODE END 2 */

  /* Init scheduler */
  osKernelInitialize();

  /* Call init function for freertos objects (in app_freertos.c) */
  MX_FREERTOS_Init();

  uart_log_init();

  /* Start scheduler */
  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */


  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure LSE Drive Capability
  */
  HAL_PWR_EnableBkUpAccess();
  __HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_LOW);

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE|RCC_OSCILLATORTYPE_LSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMBOOST = RCC_PLLMBOOST_DIV1;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 80;
  RCC_OscInitStruct.PLL.PLLP = 2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLLVCIRANGE_0;
  RCC_OscInitStruct.PLL.PLLFRACN = 0;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2
                              |RCC_CLOCKTYPE_PCLK3;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief Power Configuration
  * @retval None
  */
static void SystemPower_Config(void)
{
  HAL_PWREx_EnableVddIO2();

  PWR_PVDTypeDef sConfigPVD = {0};

  /*
   * PVD Configuration
   */
  sConfigPVD.PVDLevel = PWR_PVDLEVEL_0;
  sConfigPVD.Mode = PWR_PVD_MODE_NORMAL;
  HAL_PWR_ConfigPVD(&sConfigPVD);

  /*
   * Enable the PVD Output
   */
  HAL_PWR_EnablePVD();

  /*
   * Disable the internal Pull-Up in Dead Battery pins of UCPD peripheral
   */
  HAL_PWREx_DisableUCPDDeadBattery();

  /*
   * Switch to SMPS regulator instead of LDO
   */
  if (HAL_PWREx_ConfigSupply(PWR_SMPS_SUPPLY) != HAL_OK)
  {
    Error_Handler();
  }
/* USER CODE BEGIN PWR */
/* USER CODE END PWR */
}

/* USER CODE BEGIN 4 */

/******************************************************************************
** timer_synchro
*******************************************************************************
* Description    :  Synchronize timers
* Input          :  none
* Return         :  none
*******************************************************************************/
void timer_syncho(void)
{
	static uint8_t cnt_100ms = 0;
	//static uint8_t last_sec = 0;
	static uint8_t last_day = 0;
	static uint8_t last_month = 0;
	static uint8_t last_year = 0;
	static uint8_t tick_sec = 0;


	fTick_100ms = 0;
	fTick_1sec = 0;
	//fTick_1min = 0;
	fTick_15min = 0;
	fNew_day = 0;

	if (tick_1ms > 99 )
	{
		tick_1ms = 0;
		fTick_100ms = 1;
		if ((++cnt_100ms) > 9)
		{
			cnt_100ms = 0;
			fTick_1sec = 1;
			if (userTimer1)
			{
				userTimer1--;
			}
			if (userTimer2)
			{
				userTimer2--;
			}
			if (doorTimer)
			{
				doorTimer--;
			}
		}
	}

	if (tick2_1ms > 9 )
	{
		tick2_1ms = 0;
		if (buzzer_timer)
		{
			buzzer_timer--;
		}
		else
		{
			buzzer_off();
		}
	}

	if (fRTC_Tick_1sec)
	{
		fRTC_Tick_1sec = 0;
		datetime = RTC_GetCalendar();
		fClock_change = 1;
		tick_sec++;
		energy_update();
		//debug32 = tick_sec;
//		if (last_sec > datetime.Seconds)
//		{
//			fTick_1min = 1;
//		}
//		last_sec = datetime.Seconds;

		if (tick_sec > 59)
		{
			tick_sec = 0;
			fTick_1min = 1;
			//debug32++;
		}
		//uart_log_printf("A");

	}
	if (fTick_1min)
	{
		if (!(datetime.Minutes % 15))
		{
			fTick_15min = 1;
		}
	}

	if ((last_day != datetime.Date) || (last_month != datetime.Month) || (last_year != datetime.Year))
	    {
	        last_day = datetime.Date;
	        last_month = datetime.Month;
	        last_year = datetime.Year;
	        fNew_day = 1;
	    }
}

/******************************************************************************
** MainReg_process
*******************************************************************************
* Description    : MainReg process
* Input          : None
* Return         : None
*******************************************************************************/
void MainReg_process(void)
{
	int32_t iVal;
	uint16_t atime,timeOn, timeOff;
	bool fSound_msg = false;

	timer_syncho();

	if (fTick_100ms)
	{
		//LED_G_Toggle();

		if ((fireplace.door.usedSwitch == 0) && (fireplace.door.status == DOOR_OPENED) && (getDoorTimer() == 0))
		{
			fireplace.door.status = DOOR_CLOSED;
			fireplace_startBurning();
		}

		reg_process();
		io_service();
		system_checkErrWarnState();

		atime = 60 * datetime.Hours + datetime.Minutes;
		timeOn = 60 * mSystem.sound.sett.mute_time_on.h + mSystem.sound.sett.mute_time_on.m;
		timeOff = 60 * mSystem.sound.sett.mute_time_off.h + mSystem.sound.sett.mute_time_off.m;


		/* Buzzer Mute Timer */
		if (mSystem.sound.mute == 0)
		{
			if (timeOn > timeOff)
			{
				if ((atime >= timeOn) || (atime < timeOff))
				{
					mSystem.sound.on = 0;
				}
				else
				{
					mSystem.sound.on = 1;
				}
			}
			else
			{
				if ((atime >= timeOn) && (atime < timeOff))
				{
					mSystem.sound.on = 0;
				}
				else
				{
					mSystem.sound.on = 1;
				}
			}
		}
		else
		{
			mSystem.sound.on = 0;
		}

		/* Display */
		if (mSystem.display.sett.saver_en)
		{
			if (main_touchAct)
			{
				mSystem.display.timer = 0;
				backlight_pwm(mSystem.display.sett.backlight);
			}
			if (mSystem.display.timer < (10 * mSystem.display.sett.saver_time))
			{
				mSystem.display.timer++;
			}
			else
			{
				backlight_pwm(mSystem.display.sett.saver_backlight);
			}
		}
	}

	/* Buzzer */
	if (mSystem.sound.on == 1)
	{
		fSound_msg = false;
		if ((buzzer_timer == 0) && (fTick_100ms))
		{
			if ((mSystem.sound.sett.announ_msg & amALARM) && (mSystem.err_state))
			{
				iVal = tabBuzzerEff1[pBuzzerEff];
				fSound_msg = true;
			}
			else
			if (mSystem.sound.sett.announ_msg & amWARN)
			{
				if (accum.status & sACCUM_LEVEL80)
				{
					iVal = tabBuzzerEff2[pBuzzerEff];
					fSound_msg = true;
				}
				else
				if (fireplace.burning.status == BS_LOW_FUEL)
				{
					iVal = tabBuzzerEff3[pBuzzerEff];
					fSound_msg = true;
				}
			}

			if (fSound_msg)
			{
				if (++pBuzzerEff > 9)
				{
					pBuzzerEff = 0;
				}

				if (iVal > 0)
				{
					buzzer_timer = iVal;
					buzzer_on();
				}
				else
				if (iVal < 0)
				{
					buzzer_timer = -(iVal);
					buzzer_off();
				}
				else
				{
					pBuzzerEff = 0;
				}
			}
			else
			{
				pBuzzerEff = 0;
				buzzer_timer = 0;
			}
		}
		if ((mSystem.sound.sett.announ_msg & amTOUCH) && (fSound_msg == false) && (main_touchAct))
		{
			if (fBuzzOn == 0)
			{
				buzzer_timer = PIP_TIME;
				fBuzzOn = 1;
				buzzer_on();
			}
		}
		else
		{
			fBuzzOn = 0;
		}
	}
	else
	{
		pBuzzerEff = 0;
		buzzer_timer = 0;
		buzzer_off();
	}



}


/******************************************************************************
 ** Modbus_process
 *******************************************************************************
 * Description    : Modbus process
 * Input          : None
 * Return         : None
 *******************************************************************************/
extern void Modbus_process(void) {
	uint8_t res, i;
	osDelay(500);
	//LED_G_Toggle();
	/* AIN value */
	res = modbus_read_holding_registers(&mb, HOLDREG_AIN_VALUE_ADR,	HOLDREG_AIN_VALUE_COUNT);
	if (res == MODBUS_RECV_DATA)
	{
		ain[TS1].t = holdreg[HOLDREG_AIN_VALUE_ADR];
		ain[TS2].t = holdreg[HOLDREG_AIN_VALUE_ADR + 1];
		ain[TS3].t = holdreg[HOLDREG_AIN_VALUE_ADR + 2];
		ain[TS4].t = holdreg[HOLDREG_AIN_VALUE_ADR + 3];
		ain[TS5].t = holdreg[HOLDREG_AIN_VALUE_ADR + 4];
		ain[TS6].t = holdreg[HOLDREG_AIN_VALUE_ADR + 5];
		ain[TS7].t = holdreg[HOLDREG_AIN_VALUE_ADR + 6];
		ain[TS8].t = holdreg[HOLDREG_AIN_VALUE_ADR + 7];
		ain[TS9].t = holdreg[HOLDREG_AIN_VALUE_ADR + 8];
	}
	/* AIN status */
	res = modbus_read_holding_registers(&mb, HOLDREG_AIN_STATUS_ADR, HOLDREG_AIN_STATUS_COUNT);
	if (res == MODBUS_RECV_DATA)
	{
		ain[TS1].status = holdreg[HOLDREG_AIN_STATUS_ADR] & 0xFF;
		ain[TS2].status = holdreg[HOLDREG_AIN_STATUS_ADR + 1] & 0xFF;
		ain[TS3].status = holdreg[HOLDREG_AIN_STATUS_ADR + 2] & 0xFF;
		ain[TS4].status = holdreg[HOLDREG_AIN_STATUS_ADR + 3] & 0xFF;
		ain[TS5].status = holdreg[HOLDREG_AIN_STATUS_ADR + 4] & 0xFF;
		ain[TS6].status = holdreg[HOLDREG_AIN_STATUS_ADR + 5] & 0xFF;
		ain[TS7].status = holdreg[HOLDREG_AIN_STATUS_ADR + 6] & 0xFF;
		ain[TS8].status = holdreg[HOLDREG_AIN_STATUS_ADR + 7] & 0xFF;
		ain[TS9].status = holdreg[HOLDREG_AIN_STATUS_ADR + 8] & 0xFF;
	}
	/* DIN value */
	res = modbus_read_holding_registers(&mb, HOLDREG_DIN_STATUS_ADR, HOLDREG_DIN_STATUS_COUNT);
	if (res == MODBUS_RECV_DATA)
	{
		din[DI1].status = holdreg[HOLDREG_DIN_STATUS_ADR];
		din[DI2].status = holdreg[HOLDREG_DIN_STATUS_ADR + 1];
	}
	/* LAMBDA SENSOR */
	res = modbus_read_holding_registers(&mb, HOLDREG_LSEN_VALUE_ADR, 2);
	if (res == MODBUS_RECV_DATA)
	{
		lambda.value = holdreg[HOLDREG_LSEN_VALUE_ADR] / 10;
		lambda.status = holdreg[HOLDREG_LSEN_VALUE_ADR + 1];
	}
	/* FLOWMETER */
	res = modbus_read_holding_registers(&mb, HOLDREG_FM_FLOW_L_MIN_ADR, 5);
	if (res == MODBUS_RECV_DATA)
	{
		flowmeter.flow = holdreg[HOLDREG_FM_FLOW_L_MIN_ADR]/10;
		ui32_to_ui8.ui16Val[1] = holdreg[HOLDREG_FM_VOLUME_HI_ADR];
		ui32_to_ui8.ui16Val[0] = holdreg[HOLDREG_FM_VOLUME_LO_ADR];
		flowmeter.volume = ui32_to_ui8.floatVal;
		ui32_to_ui8.ui16Val[1] = holdreg[HOLDREG_FM_INVERVAL_HI_ADR];
		ui32_to_ui8.ui16Val[0] = holdreg[HOLDREG_FM_INVERVAL_LO_ADR];
		flowmeter.timeInterval = ui32_to_ui8.uin32Val;
	}

	/**** WRITE *****/
	/* Outputs */
	for (i = 0; i < OUT_COUNT; i++)
	{
		holdreg[HOLDREG_OUT_STATUS_ADR + i] = out[i].mode & oON;
	}
	res = modbus_write_multiple_registers(&mb, HOLDREG_OUT_STATUS_ADR, HOLDREG_OUT_STATUS_COUNT);
	// Lambda sensor */
	holdreg[HOLDREG_LSEN_MODE_ADR] = lambda.mode;
	res = modbus_write_multiple_registers(&mb, HOLDREG_LSEN_MODE_ADR, HOLDREG_LSEN_MODE_COUNT);
	/* AOUT */
	holdreg[HOLDREG_AOUT_MODE_ADR] = aout[0].mode;
	res = modbus_write_multiple_registers(&mb, HOLDREG_AOUT_MODE_ADR, HOLDREG_AOUT_MODE_COUNT);
	holdreg[HOLDREG_AOUT_VALUE_ADR] = aout[0].value;
	res = modbus_write_multiple_registers(&mb, HOLDREG_AOUT_VALUE_ADR, HOLDREG_AOUT_VALUE_COUNT);
	/* FLAPS*/
	holdreg[HOLDREG_FLAP_POS_ADR] = airflap[PRIM_F].pos;
	holdreg[HOLDREG_FLAP_POS_ADR + 1] = airflap[SEC_F].pos;
	res = modbus_write_multiple_registers(&mb, HOLDREG_FLAP_POS_ADR, 2);

	/* FLOWMETER */
	holdreg[HOLDREG_FM_TYPE_ADR] = flowmeter.sett.meter_type;
	holdreg[HOLDREG_FM_QFACTOR_ADR] = flowmeter.sett.qFactor;
	res = modbus_write_multiple_registers(&mb, HOLDREG_FM_TYPE_ADR, 2);

	//debug32 = mb.cnt_errIV;
}


/******************************************************************************
** HAL_RTC_AlarmAEventCallback
*******************************************************************************
* Description    : Set RTC Time
* Input          : hrtc : RTC handle
* Return         : None
*******************************************************************************/
void HAL_RTC_AlarmAEventCallback(RTC_HandleTypeDef *hrtc)
{
	if(hrtc->Instance == RTC)
	{
		fRTC_Tick_1sec = 1;
	}
}




/* USER CODE END 4 */

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM6 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM6)
  {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */
  tick_1ms++;
  tick2_1ms++;

  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
