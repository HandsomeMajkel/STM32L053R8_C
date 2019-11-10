/*
 * gpio.c
 *
 *  Created on: 26 paŸ 2015
 *      Author: Micha³
 */
#include "include/gpio.h"


void gpio_config(GPIO_TypeDef * GPIO, uint16_t pin, uint8_t moder, uint8_t otype, uint8_t speed, uint8_t pupdr, uint8_t af)
{
	uint32_t pind = pin*2;
	GPIO->MODER = (GPIO->MODER & ~(3<<pind)) | moder<<(pind);
	if(moder == GPIO_MODER_ALTERNATE_FUNCTION || moder == GPIO_MODER_GENERAL_PURPOSE)
	{
		GPIO->OTYPER = (GPIO->OTYPER & ~(1<<pin)) | otype<<pin;
		GPIO->OSPEEDR = (GPIO->OSPEEDR & ~(3<<pind)) | speed<<pind;
	}
	GPIO->PUPDR = (GPIO->PUPDR & ~(3<<pind)) | pupdr<<pind;
	if(moder == GPIO_MODER_ALTERNATE_FUNCTION)
	{
		if(pin<8)
		{
			pind = (pin)*4;
			GPIO->AFR[0] = (GPIO->AFR[0] & ~(15<<pind)) | af<<pind;
		}
		else
		{
			pind = (pin-8)*4;
			GPIO->AFR[1] = (GPIO->AFR[1] & ~(15<<pind)) | af<<pind;
		}
	}
}


