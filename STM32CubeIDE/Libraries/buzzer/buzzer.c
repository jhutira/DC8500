/*******************************************************************************
** Buzzer driver
********************************************************************************
*
* Buzzer driver
*
*
* v1.0
*
* (c) 7.6.2025
*
* use TIM1 (pwm_ch4)
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "buzzer.h"
#include "tim.h"


/* Defines -------------------------------------------------------------------*/


/* Constants ------------------------------------------------------------------*/


/* Variables ------------------------------------------------------------------*/
static uint8_t buzz_pwm = 25;
TIM_HandleTypeDef htim1;

/* Functions ------------------------------------------------------------------*/


/******************************************************************************
** buzzer_init
*******************************************************************************
 * Description    : Initialize BUZZER (PWM FREQ = 2kHz)
 * Input          : None
 * Return         : None
*******************************************************************************/
void buzzer_init(void)
{
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_TIM1_CLK_ENABLE();

	// GPIO
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = GPIO_PIN_11;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF1_TIM1;  // AF1 pre TIM1_CH4
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);


	htim1.Instance = TIM1;
	htim1.Init.Prescaler = 1599;
	htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim1.Init.Period = 49;
	htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim1.Init.RepetitionCounter = 0;
	htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
	HAL_TIM_PWM_Init(&htim1);

	TIM_OC_InitTypeDef sConfigOC = {0};
	sConfigOC.OCMode = TIM_OCMODE_PWM1;
	sConfigOC.Pulse = 25; // 50 % duty cycle
	sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
	sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
	sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
	sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
	sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
	HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_4);

	// Break & Dead-Time (nevyhnutné pre advanced timer)
	TIM_BreakDeadTimeConfigTypeDef sBreakConfig = {0};
	sBreakConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_ENABLE;
	HAL_TIMEx_ConfigBreakDeadTime(&htim1, &sBreakConfig);

	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4);
}

/******************************************************************************
** buzzer_on
*******************************************************************************
 * Description    : BUZZER ON
 * Input          : None
 * Return         : None
*******************************************************************************/
void buzzer_on(void)
{
	uint32_t pulse = ((htim1.Init.Period + 1) * buzz_pwm) / 100;
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, pulse);
}

/******************************************************************************
** buzzer_off
*******************************************************************************
 * Description    : BUZZER OFF
 * Input          : None
 * Return         : None
*******************************************************************************/
void buzzer_off(void)
{
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, 0);
}

/******************************************************************************
** buzzer_pwm
*******************************************************************************
 * Description    : BUZZER PWM
 * Input          : pwm
 * Return         : None
*******************************************************************************/
void buzzer_set_pwm(uint8_t pwm)
{
	if (pwm > 100) pwm = 100;
	buzz_pwm = pwm;
	buzzer_on();
}

/*********************************************************************************************************
** End of File
*********************************************************************************************************/
