/*******************************************************************************
** HW defn
********************************************************************************
*
* HW definition
*
*
* v1.0
*
* (c) 12.4.2025
*
* use
*******************************************************************************/
#ifndef __HW_DEFN_H
#define __HW_DEFN_H

#ifdef __cplusplus
extern "C" {
#endif


/******************************************************************************
** Defines
*******************************************************************************/
#define LED_G1_Pin GPIO_PIN_2
#define LED_G1_GPIO_Port GPIOC
#define ESP32_DI1_Pin GPIO_PIN_1
#define ESP32_DI1_GPIO_Port GPIOA
#define ESP32_TX_Pin GPIO_PIN_2
#define ESP32_TX_GPIO_Port GPIOA
#define ESP32_RX_Pin GPIO_PIN_3
#define ESP32_RX_GPIO_Port GPIOA
#define LCD_BKL_Pin GPIO_PIN_0
#define LCD_BKL_GPIO_Port GPIOB
#define LCD_ON_Pin GPIO_PIN_15
#define LCD_ON_GPIO_Port GPIOB
#define TP_IRQ_Pin GPIO_PIN_6
#define TP_IRQ_GPIO_Port GPIOC
#define TP_IRQ_EXTI_IRQn EXTI6_IRQn
#define TP_RST_Pin GPIO_PIN_7
#define TP_RST_GPIO_Port GPIOC
#define DEBUG_TX_Pin GPIO_PIN_9
#define DEBUG_TX_GPIO_Port GPIOA
#define DEBUG_RX_Pin GPIO_PIN_10
#define DEBUG_RX_GPIO_Port GPIOA
#define BUZZ_Pin GPIO_PIN_11
#define BUZZ_GPIO_Port GPIOA


/******************************************************************************
** Constants
*******************************************************************************/

/******************************************************************************
** Variables
*******************************************************************************/


/******************************************************************************
** Functions
*******************************************************************************/

/******************************************************************************
** Functions
*******************************************************************************/


#ifdef __cplusplus
}
#endif

#endif
