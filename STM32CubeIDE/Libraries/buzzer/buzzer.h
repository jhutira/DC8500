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
#ifndef __BUZZER_H
#define __BUZZER_H

#ifdef __cplusplus
extern "C" {
#endif


/* Includes ------------------------------------------------------------------*/
#include "stm32u5xx_ll_tim.h"
#include "stm32u5xx_ll_bus.h"
#include "stm32u5xx_ll_rcc.h"
#include "stm32u5xx_ll_gpio.h"

#include "stm32u5xx_hal.h"


/* Defines -------------------------------------------------------------------*/

#define BUZZ_PIN        	GPIO_PIN_11
#define BUZZ_GPIO_PORT    	GPIOA
#define BUZZ_GPIO_CLK()   	__HAL_RCC_GPIOA_CLK_ENABLE()

#define BUZZ_TIM          	TIM1
#define BUZZ_TIM_CLK()    	__HAL_RCC_TIM1_CLK_ENABLE()

/* Constants ------------------------------------------------------------------*/


/* Variables ------------------------------------------------------------------*/


/* Functions ------------------------------------------------------------------*/
void buzzer_init(void);

void buzzer_on(void);
void buzzer_off(void);
void buzzer_set_pwm(uint8_t pwm);



#ifdef __cplusplus
}
#endif

#endif

/****************************** End File ********************************/
