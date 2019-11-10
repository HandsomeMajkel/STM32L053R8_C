/** \file config.h
 * \brief Basic configuration of the project
 * \author Freddie Chopin, http://www.freddiechopin.info/
 * \date 2012-01-08
 */

/******************************************************************************
* project: lpc1114_blink_led
* chip: LPC1114
* compiler: arm-none-eabi-gcc (Sourcery CodeBench Lite 2011.09-69) 4.6.1
******************************************************************************/
#include "../../hdr/hdr_gpio_masked_access.h"
#include <stdint.h>
#include "../../inc/stm32l053xx.h"
#include "../../hdr/hdr_syscon.h"
#ifndef CONFIG_H_
#define CONFIG_H_




extern void delay_ms(int ms);
extern volatile uint16_t Timer1,Timer2;
void system_init(void);
void rcc_config (void);
void tim6_init(void);
void tim2_init(void);
//void delay_ms(uint16_t time);
#define CRYSTAL								8000000	///< quartz crystal resonator which is connected to the chip
#define FREQUENCY							8000000	// HSE
//#define FREQUENCY							16000000 // HSI 16
//#define FREQUENCY							2100000 // MSI


#define GPIO_OW_PORT				GPIOB
#define GPIO_OW_RX_pin				7
#define GPIO_OW_TX_pin				6
#define MAX_DS						3

//klawiatura
#define KLAWIATURA_GPIO						GPIOB
#define BUTTON1								5
#define BUTTON2								6
#define BUTTON3								7

#endif
