/*******************************************************************************
** Backlight driver
********************************************************************************
*
* Backlight driver
*
*
* v1.0
*
* (c) 1.12.2024
*
* use TIM3 (pwm_ch3)
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include <display/backlight.h>

/* Defines -------------------------------------------------------------------*/


/* Constants ------------------------------------------------------------------*/


/* Variables ------------------------------------------------------------------*/
uint8_t bkl_pwm = 25;

/* Functions ------------------------------------------------------------------*/


/******************************************************************************
** backlight_init
*******************************************************************************
 * Description    : Initialize BACKLIGHT (PWM FREQ = 1kHz)
 * Input          : None
 * Return         : None
*******************************************************************************/
void backlight_init(void)
{
	BKL_GPIO_CLK();
	BKL_TIM_CLK();

	// GPIO
	LL_GPIO_SetPinMode(BKL_GPIO_PORT, BKL_PIN, LL_GPIO_MODE_ALTERNATE);
	LL_GPIO_SetAFPin_0_7(BKL_GPIO_PORT, BKL_PIN, LL_GPIO_AF_2);
	LL_GPIO_SetPinSpeed(BKL_GPIO_PORT, BKL_PIN, LL_GPIO_SPEED_FREQ_HIGH);
	LL_GPIO_SetPinPull(BKL_GPIO_PORT, BKL_PIN, LL_GPIO_PULL_NO);


	LL_TIM_SetPrescaler(BKL_TIM, 159);  	// Prescaler: Freq_timer = Freq_APB2 / (Prescaler + 1)
	LL_TIM_SetAutoReload(BKL_TIM, 99);
    LL_TIM_OC_SetMode(BKL_TIM, LL_TIM_CHANNEL_CH3, LL_TIM_OCMODE_PWM1);
    LL_TIM_OC_EnablePreload(BKL_TIM, LL_TIM_CHANNEL_CH3);

    LL_TIM_OC_SetCompareCH3(BKL_TIM, 0);

    LL_TIM_CC_EnableChannel(BKL_TIM, LL_TIM_CHANNEL_CH3);

	// (MOE - Main Output Enable)
	LL_TIM_EnableUpdateEvent(BKL_TIM);

	// Timer enable
	LL_TIM_EnableCounter(BKL_TIM);
}

/******************************************************************************
** backlight_on
*******************************************************************************
 * Description    : BACKLIGHT ON
 * Input          : None
 * Return         : None
*******************************************************************************/
void backlight_on(void)
{
	LL_TIM_OC_SetCompareCH3(BKL_TIM, bkl_pwm);
}

/******************************************************************************
** backlight_off
*******************************************************************************
 * Description    : BACKLIGHT OFF
 * Input          : None
 * Return         : None
*******************************************************************************/
void backlight_off(void)
{
	LL_TIM_OC_SetCompareCH3(BKL_TIM, 0);
}

/******************************************************************************
** backlight_pwm
*******************************************************************************
 * Description    : BACKLIGHT PWM
 * Input          : pwm
 * Return         : None
*******************************************************************************/
void backlight_pwm(uint8_t pwm)
{
	bkl_pwm = pwm;
	LL_TIM_OC_SetCompareCH3(BKL_TIM, bkl_pwm);
}

/*********************************************************************************************************
** End of File
*********************************************************************************************************/
