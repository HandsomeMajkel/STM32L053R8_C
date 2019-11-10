/*
 * gpio.h
 *
 *  Created on: 26 paü 2015
 *      Author: Micha≥
 */
#include "config.h"


#ifndef GPIO_GPIO_H_
#define GPIO_GPIO_H_



//
#define GPIO_MODER_GENERAL_PURPOSE 			1
#define GPIO_MODER_ALTERNATE_FUNCTION		2
#define GPIO_MODER_INPUT					0
#define GPIO_MODER_ANALOG_IO				3

#define GPIO_OTYPE_PP						0
#define GPIO_OTYPE_OD						1

#define GPIO_SPEED_2MHz						0
#define GPIO_SPEED_10MHz					1
#define GPIO_SPEED_50MHz					2

#define GPIO_PUPDR_NO_PULL					0
#define GPIO_PUPDR_PULL_UP					1
#define GPIO_PUPDR_PULL_DOWN				2

#define GPIO_AF0							0
#define GPIO_AF1							1
#define GPIO_AF2							2
#define GPIO_AF3							3
#define GPIO_AF4							4
#define GPIO_AF5							5
#define GPIO_AF6							6
#define GPIO_AF7							7


void gpio_config(GPIO_TypeDef * GPIO, uint16_t pin, uint8_t moder, uint8_t otype, uint8_t speed, uint8_t pupdr, uint8_t af);

#endif /* GPIO_GPIO_H_ */
