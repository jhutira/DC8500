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
#ifndef __BACKLIGHT_H
#define __BACKLIGHT_H

#ifdef __cplusplus
extern "C" {
#endif


/* Includes ------------------------------------------------------------------*/
#include "stm32u5xx_ll_tim.h"
#include "stm32u5xx_ll_bus.h"
#include "stm32u5xx_ll_rcc.h"
#include "stm32u5xx_ll_gpio.h"


/* Defines -------------------------------------------------------------------*/

#define BKL_PIN          LL_GPIO_PIN_0
#define BKL_GPIO_PORT    GPIOB
#define BKL_GPIO_CLK()   LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOB)

#define BKL_TIM          TIM3
#define BKL_TIM_CLK()    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM3)

/* Constants ------------------------------------------------------------------*/


/* Variables ------------------------------------------------------------------*/

/* Functions ------------------------------------------------------------------*/
void backlight_init(void);

void backlight_on(void);
void backlight_off(void);
void backlight_pwm(uint8_t pwm);



#ifdef __cplusplus
}
#endif

#endif

/****************************** End File ********************************/
